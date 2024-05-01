#include <msp430fr5994.h>
#include <string.h>
#include "cc1101.h"

// ****** Macro Declaration ******
#define TX_BUFFER_SIZE        40 //key + 13*3         // Size of Data Packet to send on Radio
//#define TIMER_HZ          1250                    //if VLO, use 1250 (this gives ~1.2s);           
#define TIMER_HZ              4096                    //if LFXT, use 4096 
#define TIMER_THRESHOLD       24576//(6*Timer_hz)//20480//(5*TIMER_HZ)      // TIMER_THRESHOLD = 4096 -> Timer interrupt at 1s , set accordingly
#define TIMERA1_THRESHOLD     40960//(10*TIMER_HZ)
#define FRAM_START_ADDRESS    0x10000
#define FRAM_BUF_SIZE         50
#define NUMEVENTS             3    //number of event that are being kept up with at a given time.
#define EVENTBYTES            9   //number of items being stored for each event (startx2, endx2, CRC = 5 items @ 10 bytes, plus an additional 1 byte for event # => totaling 11 bytes)
#define PKTTBYTES             9
#define WAITTIME              5
#define WALDO_ID              50
//#define BLIP_THRESHOLD        2

// ****** Variable Declaration ******
uint8_t tx_buffer[61]={0};
volatile unsigned char state_variable, interrupt_channel, timerA0_flag, timerA1_flag, timerB0_flag;
volatile unsigned short int timer_start;
const unsigned int CRC_Init = 0xFFFF;
unsigned int CRC_Result;                    // Holds results obtained through the CRC16 module

uint8_t FRAM_buffer[FRAM_BUF_SIZE] __attribute__((section(".nv")));

volatile uint8_t event_count = 0, interrupt_flag, /*lpm_flag,*/ radio_flag, iet_ct = 0, 
                shamt = 0, ins = 0, outs = 0, passbys = 0, restarts = 0, other = 0, result = 0, 
                flipB = 0, flipC = 0, accumBdown = 0, accumCdown = 0 ;
volatile int ch1_start, ch2_start, ch1_end, ch2_end, ct_Bdown, ct_Cdown, ct_Bup, ct_Cup,
                ch1_len, ch2_len, dist_st, dist_end, rel_dist_st, rel_dist_end, comB, comC, ch1_st_temp, ch2_st_temp;

// ****** Function Declaration ******
void initialize_system_clock();  // To set up the clock sources and frequency
void optimize_unused_pins();     // To set all other pins to input pulldown to minimize power draw
void initialize_system_pins();   // To set up interrupt pins and GPIOs

void delay_timerA0(int);         // Delay using Timer A0, 1s = 32768/8 = 4096
void delay_timerB0(int);         // Delay using Timer B0, 1s = 32768/8 = 4096
void start_timerA0();            // Start Timer A0 for time specified by value of TIMER_THRESHOLD
void start_timer_A1();           // Start Timer A1 for time specified by value of TIMERA1_THRESHOLD
void stop_timer_A1();

void go_to_sleep();
void enable_detectorISRs();
void disable_detectorISRs();
uint8_t evaluate_event();           // What to do when timer A fires signaling end of event
void send_radio_pkt(uint8_t *tx_data, uint8_t size);  //void call_radio(unsigned char length, unsigned char data);  //void pin_setup_after_radio_charged();

/****** Main Function ******/
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;         // stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;             // Unlock LOCKLPM5 bit

  //Initialize all the pins and clock settings at start-up
  optimize_unused_pins();           // Set all appropriate input pins to input pulldown to optimize energy consumption
  initialize_system_pins();                // Setup pins as interrupts and GPIOs
  disable_detectorISRs();
  initialize_system_clock();        // Set clock source and frequency to 16MHz

  P1DIR |= BIT0;
  P1OUT &= ~BIT0;
  P4DIR |= BIT0;
  P4OUT &= ~BIT0;

  delay_timerA0(5);       // Start up delay (~5 seconds); This allows system to settle during power-up before checking for events    
  //go_to_sleep(-1);  //for debugging only

  enable_detectorISRs(); 
  
  // Set initial flags and variables
  interrupt_flag = 0;               // Checks if any Port interrupt has fired
  //lpm_flag = 1;                     // 1: LPM4  |   0: LPM3
  radio_flag = 0;                   // 1: Radio Interrupt Triggered
  interrupt_channel = 0;            // Indicates which port fired the interrupt
  timerA0_flag = 0;                 // 1: Timer A ISR has fired
  timer_start = 0;                  // 1: Timer has already been started by some process | 
                                    //     0: Timer not started

  memset(FRAM_buffer, 0, FRAM_BUF_SIZE); //initialize FRAM_buffer to zero (for now, at least.)

  // Start, end times and signal width for both channels wrt first interrupt ie all times are from when the
  // first channel starts (one start value will be equal or close to zero)
  ch1_start = ch1_end = -1;
  ch2_start = ch2_end = -1;
  ch1_len = ch2_len = 0;
  dist_st = dist_end = 0;
  ct_Bup = ct_Bdown = 0;
  ct_Cup = ct_Cdown = 0;
  comB = comC = 0;
  accumBdown = accumCdown = 0;
    
  uint8_t ref_idx = 0, cur_idx = 0;

  //start_timer_A1();
  while(1)
  {
    go_to_sleep();

      // ****** The following part of the code runs only when some interrupt (Port or timer) wakes up the MCU ******
      // ****** Otherwise, the MCU always remains in LPM4 (LPM3 is used when start the timer for event_eval) ******
    
    if(timerA0_flag) //inter-event interval or timerA1_flag
    {
      event_count++;
      result = evaluate_event();
      if((P1IN & BIT2))
      {
        disable_detectorISRs();
        tx_buffer[0] = 57;
        tx_buffer[1] = WALDO_ID;
        tx_buffer[2] = event_count;  //inter-event time count
        tx_buffer[3] = result;
        tx_buffer[4] = ch1_start & 0xFF;    tx_buffer[5] = ch1_start >> 8;
        tx_buffer[6] = ch1_end & 0xFF;      tx_buffer[7] = ch1_end >> 8;
        tx_buffer[8] = ch2_start & 0xFF;    tx_buffer[9] = ch2_start >> 8;
        tx_buffer[10] = ch2_end & 0xFF;     tx_buffer[11] = ch2_end >> 8;
        tx_buffer[12] = 0;
        //tx_buffer[12] = comB & 0xFF;       tx_buffer[13] = comB >> 8;
        //tx_buffer[14] = comC & 0xFF;       tx_buffer[15] = comC >> 8;
        //tx_buffer[16] = accumBdown;         tx_buffer[17] = accumCdown;
        //send to pkt
        send_radio_pkt(tx_buffer, TX_BUFFER_SIZE);
        delay_timerB0(TIMER_HZ);   // 1s = 4096, /8 seem to work well here.
        //delay_timerB(1 * TIMER_HZ);   // 1s = 4096,
      }
      
      iet_ct = 0;  ///moved out of send loop       
      timerA0_flag = 0;
      
      ch1_start = ch1_end = -1;
      ch2_start = ch2_end = -1;
      ch1_st_temp = ch2_st_temp = -1;
      ch1_len = ch2_len = 0;
      dist_end = dist_st = 0;
      //ct_Bdown = ct_Cdown = 0;
      //ct_Bup = ct_Cup = 0;
      //flipB = flipC = 0;
      //accumBdown = accumCdown = 0;
      //comB = comC = 0;
      
      P1OUT ^= BIT0;
      enable_detectorISRs();
    }//*/
    
    if(interrupt_flag)
    {                  // Triggers only when Port ISR sets interrupt_flag
      if(!timer_start)
      {                  // If it's the first one to trigger (timer hasn't been started yet)
          start_timerA0();                  // Start Timer_A
          timerA0_flag = 0; /// this flag may need to be moved
          //timerA1_flag = 0;  //added
          P1OUT ^= BIT0; 
      }
          
      if(interrupt_channel == 1)
      {         // Hi-Lo Channel 1 interrupt triggered  //B
        if(ch1_start == -1)
        {
          ch1_start = TA0R;
          //ch1_st_temp = ch1_start;
          P3IES &= ~BIT2;                 // Invert triggering edge to Lo-Hi
          //flipB = 1;
        }
        /*else if(flipB == 0)
        {     // Hi-Lo Channel 1 interrupt triggered
          ch1_st_temp = TA0R;
          P3IES &= ~BIT2;                 // Invert triggering edge to Lo-Hi
          flipB = 1;
          ct_Bup += (ch1_st_temp - ch1_end);
        }//*/
        else
        {
          ch1_end = TA0R;
          //P3IES |= BIT2;                  // Trigger on Hi-Lo
          /*flipB = 0;
          ct_Bdown += (ch1_end - ch1_st_temp);

          if(ch1_end - ch1_st_temp < BLIP_THRESHOLD //2 or 488microseconds  
            && ct_Bdown < 12) //Reset for blip
            {
              accumBdown = ct_Bdown;
              ch1_start = ch1_st_temp;
            }//*/
        }
      }
      else if(interrupt_channel == 2)  //C
      {
        if(ch2_start == -1)
        {
          ch2_start = TA0R;
          //ch2_st_temp = ch2_start;
          P3IES &= ~BIT5;                 // Invert triggering edge to Lo-Hi
          //flipC = 1;
        }
        /*else if(flipC == 0)
        {     // Hi-Lo Channel 1 interrupt triggered
          ch2_st_temp = TA0R;
          P3IES &= ~BIT5;                 // Invert triggering edge to Lo-Hi
          flipC = 1;
          ct_Cup += (ch2_st_temp - ch2_end);
        }//*/
        else
        {
          ch2_end = TA0R;
          //P3IES |= BIT5;                  // Trigger on Hi-Lo
          /*flipC = 0;
          ct_Cdown += (ch2_end - ch2_st_temp);
          
          if(ch2_end - ch2_st_temp < BLIP_THRESHOLD //2 or 488microseconds  
            && ct_Cdown < 12) //Reset for blip
            {
              accumCdown = ct_Cdown;
              ch2_start = ch2_st_temp;
            }//*/
        }
      }//end if-else
      
      interrupt_channel = 0;
      interrupt_flag = 0;
    }//end if//*/
  }//end while

  return 0;
}//end main

void initialize_system_pins()
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
  P1DIR &= ~BIT2;     // radio int
  P1DIR |= BIT1;      // radio gate

  P1DIR |= (BIT1 + BIT3 + BIT5);     // 1.3: GDO0 | 1.1: Radio Gate | 1.5: Radio CSN
  //P1OUT |= BIT3;                            // Set GDO0
  P1OUT &= ~BIT1;                     // Reset Radio Gate
}//end initialize_pins function

void initialize_system_clock()
{
  // Configure one FRAM waitstate as required by the device datasheet for MCLK
  // operation beyond 8MHz _before_ configuring the clock system.
  FRCTL0 = FRCTLPW | NWAITS_1;
  PJSEL0 = BIT4 | BIT5;                     // For XT1
  // Clock System Setup
  //CSCTL0 = CSKEY;
  CSCTL0_H = CSKEY >> 8;
  
  CSCTL1 = DCORSEL | DCOFSEL_4;             // Set DCO to 16MHz
  //__delay_cycles(60);                       // Let it settle

  CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;  // Set SMCLK = DCO/2; MCLK = DCO
                                                        // ACLK = LFXTCLK @ 32.768kHz
  CSCTL3 = DIVA__1 | DIVS__32 | DIVM__1;     // Set all dividers to 1, smclk div by 32
  CSCTL4 &= ~LFXTOFF;

  /* Start timerA2 that interrupts every 50ms. Clock is from SMCLK. 1ms=250, since
	   SMCLK was divided by 32 (16MHz/32) and we will again divide by 2 here (so 16MHz/64) above */
  TA2R = 0;
  TA2CCTL0 = CCIE;                          /* CCR0 interrupt enabled */
  TA2CCR0 =  12500;             						/* Set timer for 50ms = 12500 */
  TA2CTL = TASSEL__SMCLK + MC__UP + ID__2;  /* SMCLK, upmode, /2 */
  TA2CTL |= TAIE;                           /* Enable Timer A2 interrupt */

  do
  {
    __bis_SR_register(LPM1_bits+GIE);       /* Go to sleep and enable interrupts */

    CSCTL5 &= ~LFXTOFFG;                    // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG;
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  // Stop timer
  TA2CCTL0 = ~CCIE;                 /* CCR0 interrupt disabled */
  TA2CCR0 = 0;
  TA2CTL = TACLR + MC__STOP;     		/* clear TAR, the clock divider logic and count direction remains unchanged */

  // Now that osc is running enable fault interrupt
  SFRIE1 |= OFIE;
  CSCTL0_H = 0;     // Lock CS registers
  //*/
}//end setup_clock_module function

void optimize_unused_pins()
{
  P1SEL0 = P2SEL0 = P3SEL0 = P4SEL0 = PJSEL0 = 0x00;
  P1SEL1 = P2SEL1 = P3SEL1 = P4SEL1 = PJSEL1 = 0x00; 
  
  P1DIR = 0x02;        //zero is input/ one is output
  P1REN = 0b11111010;  //one is pull-up/pull-down, zero is floating
  P1OUT = 0x00;        //value one is pull up or zero is pull down; output high or output low if dir is set to output

  P2DIR = 0x00;
  P2REN = 0xff;
  P2OUT = 0x00;

  P3DIR = 0b00000000;
  P3REN = 0b11011011; //pins connected to hi-lo need to be left unpulled down. 
  P3OUT = 0b00000000;

  P4DIR = 0x00;
  P4REN = 0xff;  
  P4OUT = 0x00;

  PJDIR = 0x00;
  PJREN = 0b11001111;
  PJOUT = 0x00;
}//end optimize_unused_pins function

void delay_timerA0(int delay_time)
{
  // Start Timer_A0
  TA0R = 0;
  TA0CCTL0 = CCIE;                              // CCR0 interrupt enabled
  TA0CCR0 = delay_time * TIMER_HZ;              // TIMER_HZ = timer_cycles per second.  
                                                    //If VLO, it is 1s = 1250 (10kHz/8); 
                                                    //else if XTAL, 1s = 4096 (32.768kHz / 8), 1ms = 1.25,  max = 65536/4096 = 16s
  TA0CTL = TASSEL__ACLK + MC__UP + ID__8;       // ACLK, upmode, /8
  TA0CTL |= TAIE;

  _BIS_SR(LPM3_bits+GIE);     //go to sleep

  // Stop timer
  TA0CCTL0 = ~CCIE;
  TA0CTL |= TACLR + MC__STOP;
  TA0CTL &= ~TAIE;
}//end delay_timerA0 function

void delay_timerB0(int delay_time)
{
  // Start Timer_B0
  TB0R = 0;
  TB0CCTL0 = CCIE;                              // CCR0 interrupt enabled
  TB0CCR0 =  delay_time;                        // 1s = 4096 (32.768kHz / 8), 1ms = 1.25,  max = 65536/4096 = 16s
  TB0CTL = TBSSEL__ACLK + MC__UP + ID__8;       // ACLK, upmode, /8
  TB0CTL |= TBIE;

  _BIS_SR(LPM3_bits+GIE);

  // Stop timer
  TB0CCTL0 = ~CCIE;
  TB0CTL &= ~TBIE;
}//end delay_timerB0 function

void send_radio_pkt(uint8_t *tx_data, uint8_t size)//unsigned char transmit_length, unsigned char transmit_byte)
{
  //P1OUT |= BIT1;                           // Set Radio Gate: Turns on power to the radio
  
  // Turn off signal interrupts so that the power dip caused by radio isn't recorded as an event
  //disable_detectorISRs();
  
  // Radio startup
  P1DIR &= ~BIT2;								// Set radio_int pin as input
  if(P1IN & BIT2)
  {							// Confirm that radio is fully charged, takes at least 150ms
    
    P1OUT |= BIT1;							// Turn on radio
    P1DIR |= BIT1;
    __delay_cycles(64);
    Init();
    SetDataRate(3); 			// Needs to be the same in Tx and Rx
    SetLogicalChannel(2); // Needs to be the same as receiver
    SetTxPower(3);				// 7 dBm 11.9 mA
    SendData(tx_data, size);
    P1OUT &= ~BIT1;		// Open radio's gate to cut power
    
    // // Set Radio SPI bus to input
    P1DIR &= ~(BIT3 | BIT4 | BIT5 | BIT6 | BIT7);
    P2DIR &= ~BIT2;

    P1REN &= ~(BIT3 | BIT4 | BIT5 | BIT6 | BIT7);
    P2REN &= ~BIT2;
    P1DIR |= BIT0;

    //delay_timerB(2*TIMER_HZ);   // 1s = 1205
  }

  //enable_detectorISRs();
}//end send_radio_pkt function

uint8_t evaluate_event()
{
  uint8_t event_res = -1;
  // Compute width of Hi-Lo signals
  ch1_len = ch1_end - ch1_start;
  ch2_len = ch2_end - ch2_start;
  dist_st = (ch1_start - ch2_start);
  dist_st = dist_st * ((dist_st>0) - (dist_st<0));
  dist_end = (ch1_end - ch2_end);
  dist_end = dist_end * ((dist_end>0) - (dist_end<0));
  //rel_dist_st = (dist_st * 100) / ch2_len;
  //rel_dist_end = (dist_st * 100) / ch2_len;
  //comB = ct_Bup - ct_Bdown;
  //comC = ct_Cup - ct_Cdown;

  FRAM_buffer[0]++;  //increment event total seen so far

  if(event_count == 1)
  {
      restarts++;  //reboot
  }

  //Thresholds calculated using a decision tree trained on data minus major outliers (max depth = 3)
  if(ch1_len == 1 && ch2_len == 0)
  {
    event_res = 0; //close_door;
  }
  else if(ch1_start == -1 || ch2_start == -1 || ch1_end <= 561)
  {
    event_res = 1; //passby_out;
  }
  else if(ch1_end > 6710 && ch1_start > 2)
  {
    event_res = 9; //ins_9; confident
  }
  else if(ch1_end > 6710 && ch1_start <= 2 && dist_end > 393 && ch1_end > 7576)
  {
    if(ch1_end > ch2_end)
    {
      event_res = 8; //ins_8; confident
    }
    else
    {
      event_res = 13; //out; confident
    }
  }
  else if(ch1_end > 6710 && ch1_start <= 2 && dist_end > 393 && ch1_end <= 7576)
  {
    if(ch1_end > ch2_end)
    {
      event_res = 12; //ins
    }
    else
    {
      event_res = 6; //out; confident
    }
  }
  else if(ch1_end > 6710 && ch1_start <= 2 && dist_end <= 393)
  {
    event_res = 7; //pbin; confident
  }
  else if(ch1_end <= 6710 && ch1_end > 561 && dist_end > 427 && ch2_end > 4847)
  {
    if(ch1_start > 1000 || ch1_end > ch2_end)
    {
      event_res = 11; //ins
    }
    else
    {
      event_res = 5; //out; mostly******
    }
  }
  else if(ch1_end <= 6710 && ch1_end > 561 && dist_end > 427 && ch2_end <= 4847)
  {
    if(dist_st < 2 && ch2_end > ch1_end)
    {
      event_res = 14; //out; maybe******
    }
    else
    {
      event_res = 4; //in; maybe******
    }
  }
  else if(ch1_end <= 6710 && ch1_end > 561 && dist_end <= 427 && dist_end > 1)
  {
    event_res = 3; //pbin; confident
  }
  else if(ch1_end <= 6710 && ch1_end > 561 && dist_end <= 427 && dist_end <= 1)
  {
    event_res = 2; //pbin; maybe******
  }
  else
  {
    event_res = 10; //other++;
  }
  
  // Reset variables
  //lpm_flag = 1;
  interrupt_channel = 0;
  interrupt_flag = 0;
  timerA0_flag = 0;
  timer_start = 0;
  
  /*ch1_start = ch1_end = -1;
  ch2_start = ch2_end = -1;
  ch1_len = ch2_len = 0;
  dist_end = dist_st = 0;*/
  
  P3IES |= BIT2;            // Revert Trigger edge back to Hi-Lo for next event detection
  P3IES |= BIT5;

  return event_res;
}//end evaluate_event function

void start_timerA0()
{
  TA0CTL |= TACLR + MC__STOP;
  TA0R = 0;
  TA0CCTL0 = CCIE;                                // CCR0 interrupt enabled
  TA0CCR0 =  TIMER_THRESHOLD;                     // Set timer for 5s
  TA0CTL = TASSEL__ACLK + MC__UP + ID__8;         // ACLK, upmode, /8
  TA0CTL |= TAIE;

  timer_start = 1;
  //lpm_flag = 0;
}//end start_timerA0 function

void start_timer_A1()  //Setup 10s timer
{
  //TA1CTL |= TACLR + MC__STOP;
  TA1R = 0;
  TA1CCTL0 = CCIE;                                // CCR0 interrupt enabled
  TA1CCR0  = TIMERA1_THRESHOLD;                   // Set timer for 10s   Largest able to have is (2^16 = 65,536)
  TA1CTL   = TASSEL__ACLK + MC__UP + ID__8;       // ACLK, upmode, /8
  TA1CTL  |= TAIE;
}//end start_timerA1 function//*/

void stop_timer_A1()
{
  TA1CTL |= TACLR + MC__STOP;
  TA1R = 0;
  TA1CCTL0 = CCIE;                                // CCR0 interrupt enabled
  TA1CCR0 =  TIMERA1_THRESHOLD;                     // Set timer for ??
  TA1CTL = TASSEL__ACLK + MC__STOP + ID__8;         // ACLK, stop, /8
  TA1CTL &= ~TAIE;
  timerA1_flag = 0;
}//*/

void disable_detectorISRs()
{
  P3IE &= ~BIT2;            // HL1 Interrupt Disable (P3.2)
  P3IE &= ~BIT5;            // HL2 Interrupt Disable (P3.5)
}

void enable_detectorISRs()
{
  P3IFG &= ~BIT2;
  P3IE |= BIT2;            // HL1 Interrupt Enable
  P3IFG &= ~BIT5;
  P3IE |= BIT5;            // HL2 Interrupt Enable
  interrupt_flag = 0;
}

void go_to_sleep()
{
    _BIS_SR(LPM3_bits+GIE);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

/****** ISR Definitions ******/
void __attribute__ ((interrupt(PORT3_VECTOR))) Port_3(void)  // ISR for Port 3
{
  interrupt_flag = 1;

  if( P3IFG & BIT2 ) //B
  {
    P3IFG &= ~BIT2;
    interrupt_channel = 1;
  }
  else if( P3IFG & BIT5 )  //C
  {
    P3IFG &= ~BIT5;
    interrupt_channel = 2;
  }

  // Wake up from LPM3
  __bic_SR_register_on_exit(LPM3_bits+GIE);
}//end Port 4 ISR*/

void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A0(void)  // ISR for Timer A
{
  disable_detectorISRs();

  // Stop Timer
  TA0CCTL0 = ~CCIE;
  TA0CTL |= TACLR + MC__STOP;
  TA0R = 0;
  TA0CTL &= ~TAIE;
  TA0CTL &= ~TAIFG;
  
  timer_start = 0;
  timerA0_flag = 1;
  timerA1_flag = 0;

  __bic_SR_register_on_exit(LPM3_bits + GIE);  // Wake up from LPM3
}//end Timer A0 ISR

/* ISR for Timer A1 used for inter-event timing*/
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) Timer_A1(void)  // ISR for Timer A
{
  TA1CTL |= TACLR;
  TA1CTL &= ~TAIFG;
  
  //P1OUT ^= BIT0;
  iet_ct++;

  if(iet_ct % WAITTIME == 0)
  {
    timerA1_flag = 1;
    __bic_SR_register_on_exit(LPM3_bits + GIE);
  }
}//end Timer A1 ISR//*/

/* ISR for Timer A2 used in System LFXT Clock setup*/
void __attribute__ ((interrupt(TIMER2_A0_VECTOR))) Timer_A2(void)
{
  __bic_SR_register_on_exit(LPM1_bits);
  TA2CTL |= TACLR;                  /* clear TAR, the clock divider logic and count direction remains unchanged */
  TA2CTL &= ~TAIFG;                 /* clear TimerA2 interrupt flag */
}//end Timer A2 ISR//*/

void __attribute__ ((interrupt(TIMER0_B0_VECTOR))) Timer_B0(void)  // ISR for Timer B
{
  // Stop Timer
  TB0CCTL0 = ~CCIE;
  TB0CTL |= TBCLR + MC__STOP;
  TB0CTL &= ~TBIE;
  TB0CTL &= ~TBIFG;

  __bic_SR_register_on_exit(LPM3_bits + GIE);  // Wake up from LPM3
}//end Timer B0 ISR*/

////////////////////////////////////////////////////////////////////////////////////////////////////////


