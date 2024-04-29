#include <msp430fr5994.h>
#include "cc1101.h"

// ****** Macro Declaration ******
#define TX_BUFFER_SIZE    2             // Size of Data Packet to send on Radio
#define TIMER_THRESHOLD   25000         // TIMER_THRESHOLD = 5000 -> Timer interrupt at 1s , set accordingly
#define PERIPHERAL_1_ADDR 0b0101000
#define WRITE_VREG_BOTH   0b00010011
#define WRITE_NVREG_BOTH  0b00100011
#define WRITE_A_VREG      0b00010001
#define WRITE_A_NVREG     0b00100001
#define WRITE_B_VREG      0b00010010
#define WRITE_B_NVREG     0b00100010
#define FRAM_TEST_START   0x10000

// ****** Variable Declaration ******
uint8_t tx_buffer[61]={0};
volatile unsigned char total_number_of_readings, length_of_reading, state_variable, interrupt_channel, timerA_flag, timerB_flag;
volatile unsigned short int timer_count, timer_start;
volatile int time_since_last[2], time;
unsigned char *FRAM_write_ptr;
volatile int tempCSCTL3, interrupt_flag, lpm_flag, timer_flag, radio_flag, channel_1_start, channel_2_start, channel_1_end, channel_2_end, channel_1_length, channel_2_length;

// ****** Function Declaration ******
void setup_clock_module();          // To set up the clock sources and frequency
void initial_pin_setup();           // To set up interrupt pins and GPIOs
void set_pins_input_pulldown();     // To set all other pins to input pulldown to minimize power draw
void delay_timerA(int);             // Delay using Timer A; Takes input in steps of 0.8 ms where delay_time = 1 means a delay of 0.8ms
void start_timerA();                // Start Timer A for time specified by value of TIMER_THRESHOLD
void delay_timerB(int);             // Delay using Timer B
void pin_setup_after_radio_charged();
void call_radio(unsigned char length, unsigned char data);
void timeout();                     // What to do when timer A fires signaling end of event

/****** Main Function ******/
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;         // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;             // Unlock LOCKLPM5 bit

    setup_clock_module();             // Set clock source and frequency
    set_pins_input_pulldown();        // Set all input pins to input pulldown
    delay_timerA(12500);              // Start up delay; Takes input in steps of 0.8 ms 
                                      //      where delay_time = 1 means a delay of 0.8ms
    initial_pin_setup();              // Setup pins as interrupts and GPIOs

    // Indicate that detectors are on with P4.0 toggle (GPIO-1)
    P4OUT |= BIT0;
    __delay_cycles(3000);
    P4OUT &= ~BIT0;

    // Set initial variables
    interrupt_flag = 0;               // Checks if any Port interrupt has fired
    lpm_flag = 1;                     // 1: LPM4  |   0: LPM3
    radio_flag = 0;                   // 1: Radio Interrupt Triggered
    interrupt_channel = 0;            // Indicates which port fired the interrupt
    length_of_reading = 0;            // Length of each reading
    timerA_flag = 0;                  // 1: Timer A ISR has fired
    timer_start = 0;                  // 1: Timer has already been started by some process | 
                                      //     0: Timer not started
    FRAM_write_ptr = (unsigned char *)FRAM_TEST_START;              // Sets start address for FRAM pointer at 0x10000
    FRAM_write_ptr[0] = FRAM_write_ptr[1] = FRAM_write_ptr[2] = 0;  // Clears the values at these three locations in FRAM
    // #readings,           #ins,                 #outs

    // Start, end times and signal width for both channels wrt first interrupt ie all times are from when the
    // first channel starts (one start value will be equal or close to zero)
    channel_1_start = channel_1_end = -1;
    channel_2_start = channel_2_end = -1;
    channel_1_length = channel_2_length = 0;
    
    while(1)
    {

      if (lpm_flag)
        _BIS_SR(LPM4_bits+GIE);
      else
        _BIS_SR(LPM3_bits+GIE);

      // ****** The following part of the code runs only when some interrupt (Port ot timer) wakes up the MCU ******
      // ****** Otherwise, the MCU always remains in LPM4 (LPM3 is used when start the timer for timeout) ******
      if(timerA_flag)
      {  //only after timer fires
        timeout();
      }

      if(interrupt_flag)
      {                  // Triggers only when Port ISR sets interrupt_flag

        timerA_flag = 0;
        if (interrupt_channel == 1)
        {         // Hi-Lo Channel 1 interrupt triggered

          if(!timer_start)
          {                  // If it's the first one to trigger (timer hasn't been started yet)
            start_timerA();                  // Start Timer_A
            channel_1_start = 0;             //
            P3IES &= ~BIT2;                  // Invert the triggering edge of the signal (it triggered on falling edge before, now on rising edge)
          }
          else if(channel_1_start == -1)
          {    // If channel fires and it hasn't started timing yet (indicates first falling edge)
            channel_1_start = TA0R;          // Record start time of the channel
            P3IES &= ~BIT2;                  // Invert triggering edge
          }
          else
          {                                  // If channel fires and its the rising edge
            channel_1_end = TA0R;            // Record end time of the channel
          }
        }
        else if(interrupt_channel == 2)
        {
          if(!timer_start)
          {
            start_timerA();
            channel_2_start = 0;
            P3IES &= ~BIT5;
          }
          else if(channel_2_start == -1)
          {     // Hi-Lo Channel 1 interrupt triggered
            channel_2_start = TA0R;
            P3IES &= ~BIT5;
          }
          else
          {
            channel_2_end = TA0R;
          }
        }//end if-else
      
      interrupt_channel = 0;
      interrupt_flag = 0;
      
      }//end if
    }//end while
  
    return 0;

}//end main

////////////////////////////////////////////////////////////////////////////////////////////////////////

/****** ISR Definitions ******/
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1(void)  // ISR for Port 1 (Radio Interrupt on P1.2)
{
  if( P1IFG & BIT2 )
  {
    radio_flag = 1;
    P1IFG &= ~BIT2;
  }
  
  // Wake up from LPM
  if(lpm_flag)
    __bic_SR_register_on_exit(LPM4_bits+GIE);
  else
    __bic_SR_register_on_exit(LPM3_bits+GIE);

}//end Port 1 ISR

void __attribute__ ((interrupt(PORT3_VECTOR))) Port_3(void)  // ISR for Port 3
{
  if( P3IFG & BIT2 )
  {
    interrupt_flag = 1;
    P3IFG &= ~BIT2;
    interrupt_channel = 1;
  }
  else if( P3IFG & BIT5 )
  {
    interrupt_flag = 1;
    P3IFG &= ~BIT5;
    interrupt_channel = 2;
  }

  // Wake up from LPM
  if(lpm_flag)
    __bic_SR_register_on_exit(LPM4_bits+GIE);
  else
    __bic_SR_register_on_exit(LPM3_bits+GIE);

}//end Port 4 ISR

void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A(void)  // ISR for Timer A
{
  // Stop Timer
  TA0CCTL0 = ~CCIE;
  TA0CTL |= TACLR + MC__STOP;
  TA0CTL &= ~TAIE;
  TA0CTL &= ~TAIFG;
  
  timer_start = 0;
  timerA_flag = 1;

  __bic_SR_register_on_exit(LPM3_bits + GIE);  // Wake up from LPM
}//end Timer A ISR

void __attribute__ ((interrupt(TIMER0_B0_VECTOR))) Timer_B(void)  // ISR for Timer B
{
  // Stop Timer
  TB0CCTL0 = ~CCIE;
  TB0CTL |= TBCLR + MC__STOP;
  TB0CTL &= ~TBIE;
  TB0CTL &= ~TBIFG;

  timerB_flag = 1;

  __bic_SR_register_on_exit(LPM3_bits + GIE);  // Wake up from LPM
}//end Timer B ISR

////////////////////////////////////////////////////////////////////////////////////////////////////////

/****** Function Definitions ******/
void setup_clock_module()
{
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

  CSCTL0_H = 0x00;
}//end setup_clock_module function

void initial_pin_setup()
{
  // Port Interrupt Setup
  P3IE |= BIT2;            // HL1 Interrupt Enable
  P3IE |= BIT5;            // HL2 Interrupt Enable
  P3IES |= BIT2;            // Trigger on Hi-Lo
  P3IES |= BIT5;
  P3IFG &= ~BIT2;            // Clear Interrupt Flag
  P3IFG &= ~BIT5;

  // GPIO Setup
  P4DIR |= (BIT0 + BIT1);           // GPIOs P4.0 and P4.1
  P4OUT &= (~BIT1 + ~BIT1);

  // Radio Port Setup - Radio_UFOP_Int P1.2
  P1DIR &= ~BIT2;
  // P1IE |= BIT2;             // Enable Radio charged interrupt : Triggers HIGH when radio is charged upto 3.3V
  // P1IES &= ~BIT2;           // Triggers on Low - High edge
  // P1IFG &= ~BIT2;           // Clear Interrupt Flag

  P6DIR |= ( BIT1 + BIT3 + BIT5);     // 1.3: GDO0 | 1.1: Radio Gate | 1.5: Radio CSN
  //P1OUT |= BIT3;                            // Set GDO0
  P1OUT &= ~BIT1;                            // Reset Radio Gate
  //P1OUT |= BIT5;                            // Set Radio CSN
  // P1REN &= ~BIT2;                           // Disable pullup/pulldown for Radio Interrupt

}//end initial_pin_setup function

void call_radio(unsigned char transmit_length, unsigned char transmit_byte)
{
  P1OUT |= (BIT1);                           // Set Radio Gate: Turns on power to the radio

  // Turn off signal interrupts so that the power dip caused by radio isn't recorded as an event
  P3IE &= ~BIT2;            // HL1 Interrupt Enable (P3.2)
  P3IE &= ~BIT5;            // HL2 Interrupt Enable (P3.5)

  // Create a packet of data
  tx_buffer[0] = transmit_length;
  tx_buffer[1] = transmit_byte;

  // Radio startup
  RadioInit();
  RadioSetDataRate(3); // Needs to be the same in Tx and Rx
  RadioSetLogicalChannel(0); // Needs to be the same in Tx and Rx
  RadioSetTxPower(7);

  RadioSendData(tx_buffer, TX_BUFFER_SIZE);

  // delay_timerA(5000);        // Delay to let power settle before enabling interrupts; 
                                // Takes input in steps of 0.8 ms where delay_time = 1 means a delay of 0.8ms
  P1OUT &= ~BIT1;

  P3IE |= BIT2;            // HL1 Interrupt Enable
  P3IE |= BIT5;            // HL2 Interrupt Enable
}//end call_radio function

void delay_timerA(int delay_time)
{
  // Takes input in steps of 0.8 ms where delay_time = 1 means a delay of 0.8ms
  // Start Timer_A
  TA0CCTL0 = CCIE;                              // CCR0 interrupt enabled
  TA0CCR0 =  delay_time;                        // 1s = 1250, 1ms = 1.25,  max = 65536/5000 = 52s
  TA0CTL = TASSEL__ACLK + MC__UP + ID__8;       // ACLK, upmode, /8
  TA0CTL |= TAIE;

  _BIS_SR(LPM3_bits+GIE);

  // Stop timer
  TA0CCTL0 = ~CCIE;
  TA0CTL |= TACLR + MC__STOP;
  TA0CTL &= ~TAIE;
}//end delay_timerA function

void start_timerA()
{
  TA0CTL |= TACLR + MC__STOP;

  TA0CCTL0 = CCIE;                                // CCR0 interrupt enabled
  TA0CCR0 =  TIMER_THRESHOLD;                     // Set timer for 5s
  TA0CTL = TASSEL__ACLK + MC__UP + ID__2;         // ACLK, upmode, /2
  TA0CTL |= TAIE;

  timer_start = 1;
  lpm_flag = 0;
}//end start_timerA function

void delay_timerB(int delay_time)
{  //not used at this point
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
}//end delay_timerB function

void set_pins_input_pulldown()
{
  P1SEL0 = 0x00;
  P1SEL1 = 0x00; //1111 1100
  P1DIR = 0x00;  //zero is input/ one is output
  P1REN = 0xfc;  //pins connected to hi-lo need to be left unpulled down. one is pull-up/pull-down, zero is floating
  P1OUT = 0x00;  //value one is pull or zero is pull down; output high or output low if dir is set to output

  P2SEL0 = 0x00;  //unused
  P2SEL1 = 0x00;
  P2DIR = 0x00;
  P2REN = 0xff;
  P2OUT = 0x00;

  P3SEL0 = 0x00;
  P3SEL1 = 0x00;
  P3DIR = 0x06;
  P3REN = 0xf9; //1111 1001
  P3OUT = 0x06;

  P4SEL0 = 0x00;  //unused
  P4SEL1 = 0x00;
  P4DIR = 0x00;
  P4REN = 0x37;  //0011 0111
  P4OUT = 0x00;

  PJSEL0 = 0x00;  //unused
  PJSEL1 = 0x00;
  PJDIR = 0x00;
  PJREN = 0xff;
  PJOUT = 0x00;
}//end set_pins_input_pulldown function

void timeout()
{
  // Compute width of Hi-Lo signals
  channel_1_length = channel_1_end - channel_1_start;
  channel_2_length = channel_2_end - channel_2_start;

  if( channel_1_start >= 0 && channel_2_start >= 0 )
  {
    // Going Out
    if( channel_1_start - channel_2_start > 100)
    {      // B fires after C
      // Update total number of readings as stored in FRAM
      *FRAM_write_ptr += 1;
      FRAM_write_ptr[1] += 1;

      P4OUT |= BIT0;  //GPIO-1
      __delay_cycles(1500);
      P4OUT &= ~BIT0;
            // call_radio(1, 'i');
    }
    else if (channel_1_start - channel_2_start <= 100)
    {    // B and C fire almost together
      // Coming In
      if( channel_2_end - channel_1_end > 100)
      {
        // Update total number of readings as stored in FRAM
        *FRAM_write_ptr += 1;

        FRAM_write_ptr[2] += 1;
        P4OUT |= BIT1;  //GPIO-2
        __delay_cycles(1500);
        P4OUT &= ~BIT1;
        // call_radio(1, 'o');
      }
      // Still Going Out
      else if(channel_2_end - channel_1_end <= 100)
      {
        // Update total number of readings as stored in FRAM
        *FRAM_write_ptr += 1;
        FRAM_write_ptr[1] += 1;

        P4OUT |= BIT0;  //GPIO-1
        __delay_cycles(1500);
        P4OUT &= ~BIT0;
        // call_radio(1, 'i');
      }
    }
    else if (channel_2_start == 0 && channel_1_start == 0)
    {
      state_variable = 3;
    }
  }

  // Store data in FRAM
  // FRAM_write_ptr[2 * total_number_of_readings - 1] = length_of_reading;
  // FRAM_write_ptr[total_number_of_readings] = state_variable;
  if(FRAM_write_ptr[0] >= 10 && (P4IN & BIT3))
  {
    call_radio(FRAM_write_ptr[1], FRAM_write_ptr[2]);
    FRAM_write_ptr[0] = FRAM_write_ptr[1] = FRAM_write_ptr[2] = 0;
  }
  //numbers of readings, number of ins, number of outs
  //everytime you send, you wipe out FRAM

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
  P3IES |= BIT2;            // Trigger on Hi-Lo
  P3IES |= BIT5;
}//end timeout function
