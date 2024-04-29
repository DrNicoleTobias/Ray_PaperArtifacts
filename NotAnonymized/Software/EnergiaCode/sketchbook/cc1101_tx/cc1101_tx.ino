#include <cc1101.h>
#include <registers.h>
#include <pins.h>
#include <stdint.h>

void setup() {

	/* 1. Disable the watchdog timer and the GPIO *
	 *	  power-on default high-impedance mode.   */
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	/* 2. Enable the green LED and set it to off. */
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

	/* 3. Initialize the CC1101 Radio module. */
	Radio.Init();
	Radio.SetDataRate(4);			// 38.313 kBaud
	Radio.SetLogicalChannel(1);		// Set the radio to channel 105
	Radio.SetTxPower(7);			// 11.9 mA
	Radio.Wakeup();
}

void loop() {

	/* Transmit the integer 8, blink the LED, and delay. */
	uint8_t txData[1] = {8};
	volatile uint16_t counter;
	Radio.SendData(txData, 1);
	P1OUT ^= BIT0;
	counter = 50000;
	do counter--;
	while(counter != 0);
}