#include "i2c_ctl.h"
#include <msp430.h>

void i2c_init(uint8_t address) {
	// Software reset enabled
	UCB1CTLW0 |= UCSWRST | UCSSEL_2;
	UCB1CTLW0 |= UCMODE_3 | UCMST | UCSYNC;   // I2C mode, Master mode, sync
	// Baud rate
	UCB1BR0 = 32;
	UCB1I2CSA = address;                         // Slave address for AB0815
	UCB1CTL1 &= ~UCSWRST;
	__delay_cycles(100);
	UCB1IE |= UCTXIE0 | UCRXIE0 | UCSTPIE;
}

void i2c_change_address(uint8_t address) {
	// Software reset enabled
	UCB1CTLW0 |= UCSWRST;
	UCB1I2CSA = address;                         // Slave address for AB0815
	UCB1CTL1 &= ~UCSWRST;
}

uint8_t is_i2c_bus_busy() {
  return (UCB1STAT & UCBBUSY);
}

void i2c_read_register_sequence(uint8_t start_offset, uint8_t num_reads, uint8_t values[]) {
	if(num_reads < 2) num_reads = 2;
	while(is_i2c_bus_busy());
	UCB1CTL1 |= UCTR + UCTXSTT;
	// TX buf empty
	while(!(UCB1IFG & UCTXIFG0));
	UCB1TXBUF = start_offset;
	while(!(UCB1IFG & UCTXIFG0));

	// Start condition again (a restart)
	UCB1CTL1 &= ~(UCTR);
	UCB1CTL1 |= UCTXSTT;
	// Wait for start
	while(UCB1CTL1 & UCTXSTT);

	uint8_t bytes_read = 0;
	while(bytes_read < (num_reads-1)) {
	// Byte rxed
	while(!(UCB1IFG & UCRXIFG0));
	values[bytes_read++] = UCB1RXBUF;
	}
	UCB1CTL1 |= UCTXSTP;
	while(!(UCB1IFG & UCRXIFG0));
	values[bytes_read] = UCB1RXBUF;
	while(UCB1CTL1 & UCTXSTP);
}

/**
 * Returns the 8-bit value of the AB0805 register specified.
 * @param  offset [description]
 * @return        [description]
 */
uint8_t i2c_read_register(uint8_t offset) {
	uint8_t values[2];
	i2c_read_register_sequence(offset, 2, values);
	return values[0];
}

void i2c_write_register(uint8_t offset, uint8_t value) {
	while(!(UCB1STAT & UCSCLLOW));
	P7OUT &= ~BIT0;

	// Wait for bus to be free
	while((UCB1STAT & UCBBUSY));
	P7OUT &= ~BIT0;
	// Send start
	UCB1CTL1 |= UCTR + UCTXSTT;
	// Wait for start
	while(UCB1CTL1 & UCTXSTT);
	// TX buf empty
	while(!(UCB1IFG & UCTXIFG0));
	UCB1TXBUF = offset;
	while(!(UCB1IFG & UCTXIFG0));
	UCB1TXBUF = value;
	while(!(UCB1IFG & UCTXIFG0));
	UCB1CTL1 |= UCTXSTP;
	while(UCB1CTL1 & UCTXSTP);
}
