#include <msp430fr6989.h>

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT

  PM5CTL0 &= ~LOCKLPM5;
  P2OUT &= 0x00;               // Shut down everything
  P2DIR &= 0x00;
  // P2DIR |= BIT0 + BIT6;            // P1.0 and P1.6 pins output the rest are input
  P2REN |= BIT0;                   // Enable internal pull-up/down resistors
  P2OUT |= BIT0;                   //Select pull-up mode for P1.3
  P2IE |= BIT0;                       // P1.3 interrupt enabled
  P2IES |= BIT0;                     // P1.3 Hi/lo edge
  P2IFG &= ~BIT0;

  P3SEL0 = 0x00;
  P3SEL1 = 0x00;
  P3DIR = 0x40;
  P3REN = 0xff;
  P3OUT = 0x40;
                    // P1.3 IFG cleared
  _BIS_SR(LPM4_bits + GIE);          // Enter LPM0 w/ interrupt
  while(1)                          //Loop forever, we work with interrupts!
  {}
}

// Port 1 interrupt service routine

void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2(void)
{
   P3OUT ^= BIT6;                      // Toggle P1.6
   P2IFG &= ~BIT0;                     // P1.3 IFG cleared
}
