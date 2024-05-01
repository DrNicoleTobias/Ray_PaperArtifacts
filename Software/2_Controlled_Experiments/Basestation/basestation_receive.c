/* Pin connection between MSP430FR5994 luanchpad and CC1101 radio
 *  MSP430FR5994       cc1101
 *  VCC		             VCC
 *  GND		             GND
 *  P3.4               GDO0
 *  P3.6	             GDO2
 *  P4.3               CSN
 *  P5.0               MOSI
 *  P5.1               MISO
 *  P5.2               SCK 
 */

#include <msp430fr5994.h>
#include <stdlib.h>
#include "include/cc1101.h"
#include "include/serialmonitor.h"

#define RX_BUFFER_SIZE       50
#define TIMERA2_THRESHOLD     4    // 4 for 1 ms used for timer delay

/*------------------Function prototypes-------------------------------------*/
void ConfigureMCUSpeed();                // Located in CC1101.c
void delayMilliss(unsigned long millis);

/*------------------Other config--------------------------------------------*/
uint8_t RX_buffer[RX_BUFFER_SIZE]={0};
volatile uint8_t GDOFlag = 0;          // Confirm packet has been received on interrupt

int main()
{
  WDTCTL = WDTPW | WDTHOLD;           //stop the watchdog timer
  PM5CTL0 &= ~LOCKLPM5;               //Free or unlock pins from high Impedance
	ConfigureMCUSpeed();                // Set clock source and frequency in cc1101.c
  led_init();
  configureUART();                    // Initial serial monitor debugging in serialmonitor.c

  printStr("RX Initialization completed!\n\r");
  P1DIR |= BIT1;
  P1OUT &= ~BIT1;

  while(1)
  {
    //configureRadio();         // Initialize radio in CC1101.c
    Init();
  	SetDataRate(3); 			// Needs to be the same in Tx and Rx
  	SetLogicalChannel(2); // Needs to be the same as receiver
	  SetTxPower(1); 				// Set transmit power to 10 dBm (29.1 mA)

    GDOFlag = 0;              // Clear GDO0 flag
    RxOn();                   // Set to receive mode
    setGDO0Interrupt();       // Enable interrupt on GDO0 pin in cc1101.h
    delayMilliss(1000);       // Wait for pakect for 1sec (change this as you like)
    
    if(GDOFlag)
    {
      //printNum(P3IN & BIT4);
      //printStr("\n");
      for(int j = 0; j < RX_BUFFER_SIZE; j++)
      {
        RX_buffer[j] = 0;
      }
      ReceiveData(RX_buffer);  // Located in cc101.h
      if(RX_buffer[0] == 57)  //57 is just a random value to be used as a key
      {
        //if(RX_buffer[1] == 1)
        {
          P1OUT ^= BIT1;
          printNum(RX_buffer[1]); //ID
          printStr(", ");
          printNum(RX_buffer[2]); //event_count
          printStr(", ");
          
          if(RX_buffer[3] == 0)
            printStr("close_door0, ");
          else if(RX_buffer[3] == 1)
            printStr("pbout1, ");
          else if(RX_buffer[3] == 2)
            printStr("pbin2, ");
          else if(RX_buffer[3] == 3)
            printStr("pbin3, ");
          else if(RX_buffer[3] == 4)
            printStr("in4, ");
          else if(RX_buffer[3] == 5)
            printStr("out5, ");
          else if(RX_buffer[3] == 6)
            printStr("out6, ");
          else if(RX_buffer[3] == 7)
            printStr("pbin7, ");
          else if(RX_buffer[3] == 8)
            printStr("in8, ");
          else if(RX_buffer[3] == 9)
            printStr("in9, ");
          else if(RX_buffer[3] == 10)
            printStr("other, ");
          else if(RX_buffer[3] == 11)
            printStr("+in11, ");
          else if(RX_buffer[3] == 12)
            printStr("+in12, ");
          else if(RX_buffer[3] == 13)
            printStr("+out13, ");
          else if(RX_buffer[3] == 14)
            printStr("+out14, ");
          else
            printStr("error, ");

          printsignedNum(RX_buffer[4] | (RX_buffer[5] << 8)); //ch1_st;
          printStr(", ");
          printsignedNum(RX_buffer[6] | (RX_buffer[7] << 8)); //ch1_end;
          printStr(", ");
          printsignedNum(RX_buffer[8] | (RX_buffer[9] << 8)); //ch2_st;
          printStr(", ");
          printsignedNum(RX_buffer[10] | (RX_buffer[11] << 8)); //ch2_end;
          printStr(", ");
          printsignedNum(RX_buffer[12]);
          //printStr(", ");
          //printsignedNum(RX_buffer[14] | (RX_buffer[15] << 8)); //comC;
          //printStr(", ");
          //printNum(RX_buffer[16]); //accumBdown;
          //printStr(", ");
          //printNum(RX_buffer[17]); //accumCdown;
          printStr("\n\r");
          delayMilliss(500);
          P1OUT ^= BIT1;
        }
      }
      led_toggle();
    }

  } // End of while loop

  return 0;
}	// End of main



// GDO0 interrupt service routine, Radio packet is available
// after interrupt is received on P3.4
void __attribute__ ((interrupt(PORT3_VECTOR))) Port_3(void)
{
  __bic_SR_register_on_exit(LPM3_bits);
  GDOFlag = 1;                      // Packet arrived
  P3IFG &= ~BIT4;                   // P3.4 IFG cleared

  //---------- Stop timer, packet already recieved --------------------
  TA2CCTL0 = ~CCIE;
  TA2CTL |= TACLR + MC__STOP;
  TA2CTL &= ~(TAIFG | TAIE);        // Clear interrupt flag and disable timer interrupt
}

// ISR for Timer A2
void __attribute__ ((interrupt(TIMER2_A0_VECTOR))) Timer_A2(void)  // Don't use pragma for mspdebug
{
  __bic_SR_register_on_exit(LPM3_bits);   // Wake up from LPM3
}

void delayMilliss(unsigned long millis)
{
  TA2R = 0;                               // Reset TimerA2 register
  // Start timer from here -------------------------------------------------
  TA2CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TA2CCR0 =  TIMERA2_THRESHOLD * millis;    // 4.125 = 4 steps give 1ms
  TA2CTL = TASSEL__ACLK + MC__UP + ID__8;   // ACLK=32768Hz, upmode,divide by 8
  TA2CTL |= TAIE;                           // Enable TimerA interrupt
  __bis_SR_register(LPM3_bits+GIE);         // Go to sleep and enable interrupts

  // Stop timer, it's work is done ------------------------------------------
  TA2CCTL0 = ~CCIE;
  TA2CTL |= TACLR + MC__STOP;
  TA2CTL &= ~(TAIFG | TAIE);            // Clear interrupt flag and disable timer interrupt
}
