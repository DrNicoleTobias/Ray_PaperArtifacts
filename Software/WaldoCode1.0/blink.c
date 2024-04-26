// Demo app to blink/toggle an LED/pin

// Use the microcontroller specific to your application
#include <msp430fr6989.h>

// Pin number : P7.0
#define PIN BIT0

int main(void) {
  volatile int i;
  int tempCSCTL3;

  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;

  // Unlock LPM5
  PM5CTL0 &= ~LOCKLPM5;

/*
  CSCTL0 = CSKEY;
  tempCSCTL3 = CSCTL3;
  CSCTL3 &= (~(0x77)) | DIVS1 | DIVM1;
  CSCTL1 |= DCORSEL;
  CSCTL1 |= DCOFSEL_4;
  __delay_cycles(60);
  CSCTL3 = tempCSCTL3;
  CSCTL0_H = 0x00;
*/
  // set up bit 0 of P1 as output
  P7DIR |= pin;
  // intialize bit 0 of P1 to 0
  P7OUT &= ~pin;

  // loop forever
  for (;;) {
    // toggle bit 0 of P1
    // delay for a while
    for (i = 0; i < 0x1000; i++);
    P7OUT ^= pin;

  }
}
