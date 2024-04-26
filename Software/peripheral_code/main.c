#include <msp430fr5989.h>
#include <string.h>
#include <stdint.h>
#include "i2c_ctl.h"

#define PERIPHERAL_1_ADDR 0b0101001
#define PERIPHERAL_2_ADDR 0b0101010
#define PERIPHERAL_3_ADDR 0b0101000

#define WRITE_VREG_BOTH 0b00010011
#define WRITE_NVREG_BOTH 0b00100011

#define WRITE_A_VREG    0b00010001
#define WRITE_A_NVREG   0b00100001

#define WRITE_B_VREG    0b00010010
#define WRITE_B_NVREG   0b00100010
int main(void) {
  // Stop WDT
  WDTCTL = WDTPW | WDTHOLD;

  // Set peripheral gate pins
  P4DIR |= BIT1;
  P4OUT &= ~BIT1;

  P5DIR |= BIT0;
  P5OUT &= ~BIT0;

  PJDIR |= BIT1;
  PJOUT &= ~BIT1;

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;


  // I2C Pins
  P1DIR |= (BIT1 | BIT2);
  P1OUT |= (BIT1 | BIT2);
  __delay_cycles(100);

  P1SEL0 |= (BIT1 | BIT2);
  P1SEL1 &= ~(BIT1 | BIT2);

  // Write calibration values for each peripheral
  uint16_t p1_int_val = 0;
  uint16_t p1_charge_val = 255;
  i2c_init(PERIPHERAL_1_ADDR);
  i2c_write_register(WRITE_A_VREG,  p1_charge_val);
  i2c_write_register(WRITE_A_NVREG, p1_charge_val);
  i2c_write_register(WRITE_B_VREG,  p1_int_val);
  i2c_write_register(WRITE_B_NVREG, p1_int_val);
  __delay_cycles(100);

  uint16_t p2_int_val = 0;
  uint16_t p2_charge_val = 255;
  i2c_init(PERIPHERAL_2_ADDR);
  i2c_write_register(WRITE_A_VREG,  p2_charge_val);
  i2c_write_register(WRITE_A_NVREG, p2_charge_val);
  i2c_write_register(WRITE_B_VREG,  p2_int_val);
  i2c_write_register(WRITE_B_NVREG, p2_int_val);
  __delay_cycles(100);

  uint16_t p3_int_val = 0;
  uint16_t p3_charge_val = 255;
  i2c_init(PERIPHERAL_3_ADDR);
  i2c_write_register(WRITE_A_VREG,  p3_charge_val);
  i2c_write_register(WRITE_A_NVREG, p3_charge_val);
  i2c_write_register(WRITE_B_VREG,  p3_int_val);
  i2c_write_register(WRITE_B_NVREG, p3_int_val);
  __delay_cycles(100);


  while(1);
}
