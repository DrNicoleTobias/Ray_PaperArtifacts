#include <msp430fr6989.h>
#include <string.h>
#include <stdint.h>
#include "i2c_ctl.h"

#define PERIPHERAL_1_ADDR 0b0101001
#define PERIPHERAL_2_ADDR 0b0101010
#define PERIPHERAL_3_ADDR 0b0101000

#define MAX5477_ADDR 0b0101000
#define WRITE_VREG_BOTH 0b00010011
#define WRITE_NVREG_BOTH 0b00100011
int main(void) {
  // Stop WDT
  WDTCTL = WDTPW | WDTHOLD;

  // LED pins
  P7DIR |= BIT0;
  P7OUT |= BIT0;
  P9DIR |= BIT7;
  P9OUT &= ~BIT7;

  // Set peripheral gate pin
  P6DIR |= BIT2;
  P6OUT &= ~BIT2;

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;


  // I2C Pins
  // P3DIR |= (BIT1 | BIT2);
  //P3OUT |= (BIT1 | BIT2);
  __delay_cycles(100);

  P3SEL1 |= (BIT1 | BIT2);
  P3SEL0 &= ~(BIT1 | BIT2);

  // Write level to both the digpots
  i2c_init(PERIPHERAL_3_ADDR);
  __delay_cycles(100);


  // Write digipot nvreg and vreg
  uint8_t value = 0;
  i2c_write_register(WRITE_VREG_BOTH, value);
  i2c_write_register(WRITE_NVREG_BOTH, value);
  P9OUT |= BIT7;
  P7OUT |= BIT0;
  while(1);
  while(1) {
    i2c_write_register(WRITE_VREG_BOTH, value);
    P9OUT ^= BIT7;
    P7OUT ^= BIT0;
    value-=32;
    __delay_cycles(1000000);
    //P4OUT |= BIT0;
  }

}
