#include<msp430fr6989.h>
#include "cc1101.h"

// Macro Declaration
#define TX_BUFFER_SIZE 2            // Size of Data Packet to send on Radio
#define TIMER_THRESHOLD 15000       // TIMER_THRESHOLD = 5 -> Timer interrupt at 1ms , set accordingly

// Variable Declaration
uint8_t tx_buffer[61]={0};
volatile unsigned char total_number_of_readings, length_of_reading, state_variable, interrupt_channel, timerA_flag, timerB_flag;
volatile unsigned short int timer_count, timer_start;
volatile int time_since_last[2], time;
unsigned char *FRAM_write_ptr;
volatile int tempCSCTL3, interrupt_flag, lpm_flag, timer_flag, channel_1_start, channel_2_start, channel_1_end, channel_2_end, channel_1_length, channel_2_length;

// Function Declaration
void setup_clock_module();          // To set up the clock sources and frequency
void initial_pin_setup();           // To set up interrupt pins and GPIOs
void set_pins_input_pulldown();     // To set all other pins to input pulldown to minimize power draw
void delay_timerA(int);             // Delay using Timer A
void delay_timerB(int);             // Delay using Timer B
void call_radio(unsigned char length, unsigned char data);

int main(void){
  WDTCTL = WDTPW | WDTHOLD;         // stop watchdog timer

  PM5CTL0 &= ~LOCKLPM5;             // Unlock LOCKLPM5 bit

  setup_clock_module();             // Set clock source and frequency

  set_pins_input_pulldown();        // Set all input pins to input pulldown

  // delay_timerA(400);             // Start up delay; Enter value in ms

  initial_pin_setup();              // Setup pins as interrupts and GPIOs

  // Set initial variables

  interrupt_flag = 0;               // Checks if any Port interrupt has fired
  lpm_flag = 1;                     // 1: LPM4  |   0: LPM3
  interrupt_channel = 0;            // Indicates which port fired the interrupt
  length_of_reading = 0;            // Length of each reading
  timerA_flag = 0;
  timer_start = 0;                  // 1: Timer has already been started by some process | 0: Timer not started

  // Start and end times and signal width for both channels wrt first interrupt ie all times are from when the
  // first channel starts (one start value will be equal or close to zero)
  channel_1_start = channel_1_end = -1;
  channel_2_start = channel_2_end = -1;
  channel_1_length = channel_2_length = 0;



  while(1){
    if (lpm_flag){
      _BIS_SR(LPM4_bits+GIE);
    }
    else{
      _BIS_SR(LPM3_bits+GIE);
    }

    if (timerA_flag){

      // Update total number of readings as stored in FRAM
      // *FRAM_write_ptr = ++total_number_of_readings;

      // Store data in FRAM
      // FRAM_write_ptr[2 * total_number_of_readings - 1] = length_of_reading;
      // FRAM_write_ptr[2 * total_number_of_readings] = state_variable;

      // Compute width of Hi-Lo signals
      channel_1_length = channel_1_end - channel_1_start;
      channel_2_length = channel_2_end - channel_2_start;

      if( channel_1_start >= 0 && channel_2_start >= 0 ){
        if( channel_1_start - channel_2_start > 1 ){      //
          P7OUT |= BIT0;
          __delay_cycles(1600);
          P7OUT &= ~BIT0;
          // call_radio(1, 'i');
        }
        else if (channel_2_end - channel_1_end <= 1){
          P7OUT |= BIT1;
          __delay_cycles(1600);
          P7OUT &= ~BIT1;
          // call_radio(1, 'o');
        }
      }

      // Reset variables
      length_of_reading = 0;
      lpm_flag = 1;
      interrupt_channel = 0;
      interrupt_flag = 0;
      timerA_flag = 0;
      timer_start = 0;
      channel_1_start = channel_1_end = -1;
      channel_2_start = channel_2_end = -1;
      // delay_timerA(1500);
      channel_1_length = channel_2_length = 0;
      P2IES |= (BIT0 + BIT2);
    }

    if (interrupt_flag){                  // Triggers only when ISR sets interrupt_flag

      timerA_flag = 0;
      if (interrupt_channel == 1){

        if(!timer_start){

          // Start Timer_A
          TA0CTL |= TACLR + MC__STOP;

          TA0CCTL0 = CCIE;                                // CCR0 interrupt enabled
          TA0CCR0 =  TIMER_THRESHOLD;                     // Set timer for 5s
          TA0CTL = TASSEL__ACLK + MC__UP + ID__2;         // ACLK, upmode, /8
          TA0CTL |= TAIE;

          timer_start = 1;
          channel_1_start = 0;

          P1IES &= ~BIT1;
        }
        else if(channel_1_start == -1){
          channel_1_start = TA0R;
          P1IES &= ~BIT1;
        }
        else{
          channel_1_end = TA0R;
        }
      }
      else if(interrupt_channel == 2){

        if(!timer_start){

          // Start Timer_A
          TA0CTL |= TACLR + MC__STOP;

          TA0CCTL0 = CCIE;                                // CCR0 interrupt enabled
          TA0CCR0 =  TIMER_THRESHOLD;                     // Set timer for 100 ms
          TA0CTL = TASSEL__ACLK + MC__UP + ID__2;         // ACLK, upmode, /2
          TA0CTL |= TAIE;
          timerA_flag = 0;

          timer_start = 1;
          channel_2_start = 0;

          P4IES &= ~BIT6;
        }
        else if(channel_2_start == -1){
          channel_2_start = TA0R;
          P4IES &= ~BIT6;
        }
        else{
          channel_2_end = TA0R;
        }
      }

      interrupt_channel = 0;
      interrupt_flag = 0;
    }


}
  return 0;
}

// ISR for Port 1
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1(void)
{
  interrupt_flag = 1;

  P1IFG &= ~BIT1;
  interrupt_channel = 1;

  // Wake up from LPM
  if(lpm_flag)
    __bic_SR_register_on_exit(LPM4_bits+GIE);
  else
    __bic_SR_register_on_exit(LPM3_bits+GIE);

}

// ISR for Port 4
void __attribute__ ((interrupt(PORT4_VECTOR))) Port_4(void)
{
  interrupt_flag = 1;

  P4IFG &= ~BIT6;
  interrupt_channel = 2;

  // Wake up from LPM
  if(lpm_flag)
    __bic_SR_register_on_exit(LPM4_bits+GIE);
  else
    __bic_SR_register_on_exit(LPM3_bits+GIE);

}

// ISR for Timer A
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A(void){
  // Stop Timer
  TA0CCTL0 = ~CCIE;
  TA0CTL |= TACLR + MC__STOP;
  TA0CTL &= ~TAIE;
  TA0CTL &= ~TAIFG;
  timer_start = 0;

  timerA_flag = 1;

  //P8OUT ^= BIT0;

  // Wake up from LPM
  __bic_SR_register_on_exit(LPM3_bits + GIE);
}

// ISR for Timer B
void __attribute__ ((interrupt(TIMER0_B0_VECTOR))) Timer_B(void){
  // Stop Timer
  TB0CCTL0 = ~CCIE;
  TB0CTL |= TBCLR + MC__STOP;
  TB0CTL &= ~TBIE;
  TB0CTL &= ~TBIFG;

  timerB_flag = 1;

  //P2IE |= BIT2;
  //P2IES ^= BIT2;
  // Wake up from LPM
  __bic_SR_register_on_exit(LPM3_bits + GIE);
}


void setup_clock_module(){
  // Configure one FRAM waitstate as required by the device datasheet for MCLK
  // operation beyond 8MHz _before_ configuring the clock system.
  FRCTL0 = FRCTLPW | NWAITS_1;

  CSCTL0 = CSKEY;

  CSCTL4 &= ~VLOOFF;
  CSCTL1 = DCORSEL | DCOFSEL_0;             // Set DCO to 16MHz
  __delay_cycles(60);                       // Let it settle

  CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;  // Set SMCLK = MCLK = DCO
                                                        // ACLK = VLOCLK @ 10kHz
  CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers to 1

  // CSCTL3 = tempCSCTL3;
  CSCTL0_H = 0x00;
}

void initial_pin_setup(){

  // Port 2 Setup

  P1IE |= BIT1;            // HL1 Interrupt Enable
  P4IE |= BIT6;            // HL2 Interrupt Enable
  P1IES |= BIT1;            // Trigger on Hi-Lo
  P4IES |= BIT6;
  P1IFG &= ~BIT1;            // Trigger on Hi-Lo
  P4IFG &= ~BIT6;

  // Port 3 Setup

  P7DIR |= (BIT0 + BIT1);           // GPIOs
  P7OUT &= (~BIT1 + ~BIT1);

  // Port 6 Setup
/*
  P6DIR |= (BIT2+BIT6);                    // Radio UFoP Gate pin
  P6OUT &= ~BIT2;
  P6OUT &= ~BIT6;
  P6REN &= ~BIT3;                   // Disable pullup/pulldown for Radio Interrupt

  // Port 8 Setup

  P8DIR |= BIT0;
  P8OUT &= ~BIT0;

  // Port 10 Setup

  P10DIR |= BIT2;                   // Turn off Echo Gate
  P10OUT &= ~BIT2;
*/
}

void call_radio(unsigned char transmit_length, unsigned char transmit_byte){
  P6DIR |= (BIT2);
  P6OUT |= (BIT2);

  P2IE &= (~BIT0 & ~BIT2);

// Create a packet of data
  tx_buffer[0] = transmit_length;
  tx_buffer[1] = transmit_byte;

  // Radio startup
  RadioInit();
  RadioSetDataRate(3); // Needs to be the same in Tx and Rx
  RadioSetLogicalChannel(0); // Needs to be the same in Tx and Rx
  RadioSetTxPower(7);
  RadioSendData(tx_buffer, TX_BUFFER_SIZE);
  // P6OUT ^= BIT6;

  P6OUT &= ~BIT2;
  P2IE |= (BIT0 + BIT2);
}

void delay_timerA(int delay_time){
  // Takes input in ms
  // Start Timer_A
  TA0CCTL0 = CCIE;                                  // CCR0 interrupt enabled
  TA0CCR0 =  5 * delay_time;                        // 1s = 5000, 1ms = 5,  max = 65536/5000 = 13s
  TA0CTL = TASSEL__ACLK + MC__UP + ID__2;           // ACLK, upmode, /2
  TA0CTL |= TAIE;

  // P2REN &= (~BIT0 & ~BIT1 & ~BIT2 & ~BIT3);

  _BIS_SR(LPM3_bits+GIE);

  // Stop timer
  TA0CCTL0 = ~CCIE;
  TA0CTL |= TACLR + MC__STOP;
  TA0CTL &= ~TAIE;
  // P3OUT ^= BIT7;

}

void delay_timerB(int delay_time){
  // Takes input in us
  // Start Timer_B
  TB0CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TB0CCR0 =  16 * delay_time;                   // 1s = 16000000, 1uS = 16,
                                               // max = 65536/16000000 = 4.096ms
  TB0CTL = TBSSEL__SMCLK + MC__UP + ID__1;           // SMCLK, upmode, /1
  TB0CTL |= TBIE;

  _BIS_SR(LPM3_bits+GIE);

  // Stop timer
  TB0CCTL0 = ~CCIE;
  TB0CTL |= TBCLR + MC__STOP;
  TB0CTL &= ~TBIE;
}

void set_pins_input_pulldown(){

  P1SEL0 = 0x00;
  P1SEL1 = 0x00;
  P1DIR = 0x00;
  P1REN = 0xfc;
  P1OUT = 0x00;

  P2SEL0 = 0x00;
  P2SEL1 = 0x00;
  P2DIR = 0x00;
  P2REN = 0xff;
  P2OUT = 0x00;

  P3SEL0 = 0x00;
  P3SEL1 = 0x00;
  P3DIR = 0x00;
  P3REN = 0xf9;
  P3OUT = 0x00;

  P4SEL0 = 0x00;
  P4SEL1 = 0x00;
  P4DIR = 0x00;
  P4REN = 0x3f;
  P4OUT = 0x00;

  P5SEL0 = 0x00;
  P5SEL1 = 0x00;
  P5DIR = 0x00;
  P5REN = 0xff;
  P5OUT = 0x00;

  P6SEL0 = 0x00;
  P6SEL1 = 0x00;
  P6DIR = 0x00;
  P6REN = 0xff;
  P6OUT = 0x00;

  P7SEL0 = 0x00;
  P7SEL1 = 0x00;
  P7DIR = 0x00;
  P7REN = 0xff;
  P7OUT = 0x00;

  P8SEL0 = 0x00;
  P8SEL1 = 0x00;
  P8DIR = 0x00;
  P8REN = 0xff;
  P8OUT = 0x00;

  P9SEL0 = 0x00;
  P9SEL1 = 0x00;
  P9DIR = 0x00;
  P9REN = 0xff;
  P9OUT = 0x00;

  P10SEL0 = 0x00;
  P10SEL1 = 0x00;
  P10DIR = 0x00;
  P10REN = 0xff;
  P10OUT = 0x00;

  PJSEL0 = 0x00;
  PJSEL1 = 0x00;
  PJDIR = 0x00;
  PJREN = 0xff;
  PJOUT = 0x00;
}
