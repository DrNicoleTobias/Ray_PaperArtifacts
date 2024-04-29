#include<msp430fr6989.h>

void set_pins_input_pulldown();

int main(void){

  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;

  PM5CTL0 &= ~LOCKLPM5;

  set_pins_input_pulldown();

  while(1){
    _BIS_SR(LPM4_bits);
    // P3OUT ^= 0x40;
  }
  return 0;
}

void set_pins_input_pulldown(){

  P1SEL0 = 0x00;
  P1SEL1 = 0x00;
  P1DIR = 0x00;
  P1REN = 0xff;
  P1OUT = 0x00;

  P2SEL0 = 0x00;
  P2SEL1 = 0x00;
  P2DIR = 0x00;
  P2REN = 0xf0;
  P2OUT = 0x01;

  P3SEL0 = 0x00;
  P3SEL1 = 0x00;
  P3DIR = 0x40;
  P3REN = 0xff;
  P3OUT = 0x40;

  P4SEL0 = 0x00;
  P4SEL1 = 0x00;
  P4DIR = 0x00;
  P4REN = 0xff;
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
