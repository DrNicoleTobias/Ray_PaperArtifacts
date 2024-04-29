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

#define RX_BUFFER_SIZE       30
#define TIMERA2_THRESHOLD     4    // 4 for 1 ms used for timer delay
#define NUMPKTEVENTS          3    //number of event that are being kept up with at a given time.
#define PKTTBYTES            9    //number of items being stored for each event (startx2, endx2, CRC = 5 items @ 10 bytes, plus an additional 1 byte for event # => totaling 11 bytes)

/*------------------Function prototypes-------------------------------------*/
void ConfigureMCUSpeed();                // Located in CC1101.c
void delayMilliss(unsigned long millis);

/*------------------Other config--------------------------------------------*/
uint8_t RX_buffer[RX_BUFFER_SIZE]={0};
volatile uint8_t GDOFlag = 0;          // Confirm packet has been received on interrupt
uint8_t shamt = 0, time_be = 0, event_class = 0;
uint16_t crc = 0;
const unsigned int CRC_Init = 0xFFFF;
uint16_t CRC_Result;                    // Holds results obtained through the CRC16 module

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
      if(RX_buffer[0] == 59 || RX_buffer[0] == 58 || RX_buffer[0] == 63 || RX_buffer[0] == 60)  //58 is just a random value to be used as a key, subtracting this value gives you waldoidnum
      {
        printStr("Packet Received: W");
        printNum((RX_buffer[0] - 58));
        printStr("\n\r");
          P1OUT ^= BIT1;
        //printStr("Reading#: \t\t WaldoID: \t\t PktID: \t\t CRC: \t\t\t Totevents: \t\t e1time: \t\t\t e1class: \t\t e2time: \t\t\t e2class: \t\te3time: \t\t\t e3class: \t\te4time: \t\t\t e4class: \t\te5time: \t\t\t e5class: \t\t: \n");
        for(int id = 0; id < NUMPKTEVENTS; id++)
        {
          shamt = id * PKTTBYTES;
          crc = RX_buffer[shamt + 2] | (RX_buffer[shamt + 3] << 8);
          //Calculate CRC
          // First, use the CRC16 hardware module to calculate the CRC...
          CRC16INIRESW0 = CRC_Init;               // Init CRC16 HW module
          for(int i = 4; i <= 9; i+=1)
          {
            // Input random values into CRC Hardware
            CRC16DIRBW0 = (RX_buffer[shamt + i]);// | (RX_buffer[shamt + (i+1)] << 8);         // Input data in CRC
            __no_operation();
          }
          CRC_Result = CRC16INIRESW0;             // Save results (per CRC-CCITT standard)
          
          printNum((RX_buffer[0] - 58));  //WaldoID
          printStr("\t");
          printNum(RX_buffer[shamt + 1]); //reading PKT number
          printStr("\t");
          
          if(crc == CRC_Result)
            printStr("Valid \t\t");
          else
            printStr("Invalid \t");

          printNum(RX_buffer[shamt + 4]); //event count
          printStr("\t");

          for(int g = 5; g <= PKTTBYTES; g++)
          {
            event_class = RX_buffer[shamt + g] & 0b00000111;
            time_be = RX_buffer[shamt + g] >> 3;
            printbinNum(time_be);
            printStr("\t");

            if(event_class == 0)
              printStr("<3\t");
            else if(event_class == 1)
              printStr("out\t");
            else if(event_class == 2)
              printStr("close_door\t");
            else if(event_class == 3)
              printStr("pbout\t");
            else if(event_class == 4)
              printStr("in\t");
            else if(event_class == 5)
              printStr("NaN\t");
            else if(event_class == 6)
              printStr("pbin\t");
            else if(event_class == 7)
              printStr("other\t");
            printStr("   ");
          }
          printStr("\n\r");
        }//*/
          
          delayMilliss(500);
          P1OUT ^= BIT1;
        //}
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
