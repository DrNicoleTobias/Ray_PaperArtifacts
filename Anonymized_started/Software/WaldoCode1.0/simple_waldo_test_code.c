#include<msp430fr6989.h>

void setup_clock_module();
void set_pins_for_interrupts_and_toggle();
void set_pins_input_pulldown();
void delay_for_setup_time(int);

int main(void){
  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;

  // Unlock LOCKLPM5 bit
  PM5CTL0 &= ~LOCKLPM5;

  // Setup Clock Module
  setup_clock_module();

  // Set all input pins to input pulldown
  set_pins_input_pulldown();

  // Start up delay
  delay_for_setup_time(100);

  // Set the pins needed for enabling interrupts
  set_pins_for_interrupts_and_toggle();

  _BIS_SR(LPM4_bits+GIE);

  while(1){};
  return 0;
}

void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2(void)
{
  if(P2IFG & BIT0 ){
    P2OUT ^= BIT0;
    P2IES ^= BIT0;
    P3OUT ^= BIT6;                      // Toggle P3.6
    P2IFG &= ~BIT0;

  }
  if(P2IFG & BIT1){
    P2OUT ^= BIT1;
    P2IES ^= BIT1;
    P3OUT ^= BIT7;                      // Toggle P3.7
    P2IFG &= ~BIT1;
  }
  if( P2IFG & BIT2){
    P2OUT ^= BIT2;
    P2IES ^= BIT2;
    // P3OUT ^= BIT6;                      // Toggle P3.6
    P2IFG &= ~BIT2;
  }
  if( P2IFG & BIT3){
    P2OUT ^= BIT3;
    P2IES ^= BIT3;
    // P3OUT ^= BIT6;                      // Toggle P3.6
    P2IFG &= ~BIT3;
  }

}

void set_pins_for_interrupts_and_toggle(){
  // P2REN |= (BIT0 + BIT1 + BIT2 + BIT3);
  P2OUT |= (BIT0 | BIT2);
  P2OUT &= (~BIT1 & ~BIT3);

  P2IE |= (BIT0 | BIT1 | BIT2 | BIT3);
  P2IES |= (BIT0 | BIT2);
  P2IES &= (~BIT1 & ~BIT3);
  P2IFG &= (~BIT0 & ~BIT1 & ~BIT2 & ~BIT3);

  P3DIR |= (BIT6 + BIT7);
  P3OUT &= (~BIT6 + ~BIT7);

}

void setup_clock_module(){
  // Configure one FRAM waitstate as required by the device datasheet for MCLK
  // operation beyond 8MHz _before_ configuring the clock system.
  FRCTL0 = FRCTLPW | NWAITS_1;

  CSCTL0 = CSKEY;

  CSCTL4 &= ~VLOOFF;
  CSCTL1 = DCORSEL | DCOFSEL_4;             // Set DCO to 16MHz
  __delay_cycles(60);

  CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;  // Set SMCLK = MCLK = DCO
                                            // ACLK = VLOCLK @ 10kHz
  CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers to 1

  // CSCTL3 = tempCSCTL3;
  CSCTL0_H = 0x00;
}

void delay_for_setup_time(int time){
  // Start Timer_A
  TA0CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TA0CCR0 =  5 * time;                           // 1s = 5000, max = 65536/5000 = 13s
  TA0CTL = TASSEL__ACLK + MC__UP + ID__2;           // ACLK, upmode, /8
  TA0CTL |= TAIE;

  P3OUT ^= BIT7;
  P2REN &= (~BIT0 & ~BIT1 & ~BIT2 & ~BIT3);

  _BIS_SR(LPM3_bits+GIE);

  // Stop timer
  TA0CCTL0 = ~CCIE;
  TA0CTL |= TACLR + MC__STOP;
  TA0CTL &= ~TAIE;
  P3OUT ^= BIT7;

}

void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A(void){
  TA0CTL &= ~TAIFG;
  // Wake up from LPM
  __bic_SR_register_on_exit(LPM4_bits + GIE);

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
  P2REN = 0xff;
  P2OUT = 0x00;

  P3SEL0 = 0x00;
  P3SEL1 = 0x00;
  P3DIR = 0x00;
  P3REN = 0xff;
  P3OUT = 0x00;

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
