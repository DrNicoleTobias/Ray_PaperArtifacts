#include<msp430fr6989.h>

int main(void){

  int tempCSCTL3;

  WDTCTL = WDTPW | WDTHOLD;

  PM5CTL0 &= ~LOCKLPM5;

  // Set up ACLK
  CSCTL0 = CSKEY;
  tempCSCTL3 = CSCTL3;

  CSCTL4 &= ~VLOOFF;          // Turn on VLO
  CSCTL2 |= SELA__VLOCLK;     // Select source of ACLK as VLO
  CSCTL3 |= DIVA__8;          // Divide source of ACLK

  CSCTL3 = tempCSCTL3;
  CSCTL0_H = 0x00;

  P5SEL0 |= BIT2;
  P5SEL1 |= BIT2;
  P5DIR |= BIT2;

  // Set up timer
  TA0CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TA0CCR0 =  10000;
  TA0CTL = TASSEL__ACLK + MC__UP + ID__2;           // ACLK, upmode, ID = input divider
  TA0CTL |= TAIE;

  P1DIR |= BIT0;
  P1OUT |= BIT0;

  _BIS_SR(LPM3_bits + GIE);

  while(1){
  }
}

void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A(void){
  P1OUT ^= BIT0;
  TA0CTL |= TACLR;
  TA0CTL &= ~TAIFG;
}
