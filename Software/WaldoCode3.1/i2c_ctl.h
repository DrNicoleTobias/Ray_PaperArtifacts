/**
 *
 * @author Josiah Hester
 * Edited by Harsh Desai for Waldo
 */
#ifndef I2C_CTL_H
#define I2C_CTL_H
#include <stdint.h>
#include <stdbool.h>
/*
		I2C functions
 */

// P3.2/UCB1SOMI/UCB1SCL -- AUX_SCL
// P3.1/UCB1SIMO/UCB1SDA -- AUX_SDA
// P3.5                  -- AUX2 / FOUT / IRQ1
void i2c_init(uint8_t address);
uint8_t is_i2c_bus_busy();
void i2c_read_register_sequence(uint8_t start_offset, uint8_t num_reads, uint8_t values[]);

/**
 * Returns the 8-bit value of the AB0805 register specified.
 * @param  offset [description]
 * @return        [description]
 */
uint8_t i2c_read_register(uint8_t offset);
void i2c_write_register(uint8_t offset, uint8_t value);

void i2c_change_address(uint8_t address);

#endif // I2C_CTL_H
