## Using the UFoP Peripheral Breakout


### Pre-requisites
- View this document using a markdown editor like [MacDown](http://macdown.uranusjr.com/) on your desktop.

- Make sure you have [EAGLE](https://cadsoft.io/) installed to view the schematic and board. [Sparkfun has a handy setup guide.](https://learn.sparkfun.com/tutorials/how-to-install-and-setup-eagle)

- The actual breakout board.
- Programmable power supply which can output 0.15V
- 2x 20-47k pullup resistors for [I2C](https://learn.sparkfun.com/tutorials/i2c)
- Breadboard and wire / jumpers for prototyping


### Breadboard
- Make sure you connect the pullup resistors to the SDA and SCL lines, and connect the GND and VCC lines.
- Connect the SCL and SDA lines to the MSP430
- Set the output of the programmable voltage supply to 0.15V
- Set the I2C address of the digital potentiometers by connceting A0, A1 to GND and / or VCC, [refer to the datasheet for the adress this makes](http://datasheets.maximintegrated.com/en/ds/MAX5477-MAX5479.pdf)
- Connect to the REF pin (loo at schematic in EAGLE)
- Connect the INT pin if used, to the msp430
- Connect the GATE pin to the msp430, this alows power to flow to the peripheral through the PERIPH_VCC pin.


### Code
Type make in the peripheral_code directory. Make sure the address is correct, this is just an example of how to write a value to the digital potentiometer. It shows writing four values, which set four different voltage levels on the peripheral to charge up to. 