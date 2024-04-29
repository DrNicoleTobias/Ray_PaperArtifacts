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
#include "../include/cc1101.h"
#include "../include/serialmonitor.h"

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

    Init();
  	SetDataRate(3); 			// Needs to be the same in Tx and Rx
  	SetLogicalChannel(2); // Needs to be the same as receiver
	  SetTxPower(1); 				// Set transmit power to 10 dBm (29.1 mA)

  while(1)
  {
    RxOn();                   // Set to receive mode
    //delayMilliss(1000);       // Wait for pakect for 1sec (change this as you like)
    
    if(CheckReceiveFlag())
    {
        ReceiveData(RX_buffer);  // Located in cc101.h
        printStr("Packet Received:  Key: ");
        printNum(RX_buffer[0]); //packet key
        printStr(" WALDO: ");
        printNum(RX_buffer[1]); //Waldo ID
        for(uint8_t actionItem = 1; actionItem <= 1; actionItem++)
        {
          printStr(" IETcount: ");
          printNum(RX_buffer[actionItem*2]); //TimerB_count
          printStr(" Sent B/c: ");//What sent it
          if(RX_buffer[actionItem*2+1] == 99)
            printStr("Nothing to report"); 
          else if(RX_buffer[actionItem*2+1] == 6)
            printStr("Detected an event"); 
          else
            printStr("ERROR"); 
          printStr(" \n\r");
        }
      led_toggle();
      RX_buffer[RX_BUFFER_SIZE]={0}; //Clear buffer
    }
    //tx_buffer[0] = 57;//WALDO_ID + 57;   //key for receiver
	          //tx_buffer[1] = WALDO_ID;
            //tx_buffer[2] = timer_b_count;
            //tx_buffer[3] = 166;  //B fired - nothing happened

  } // End of while loop

  return 0;
}	// End of main

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
