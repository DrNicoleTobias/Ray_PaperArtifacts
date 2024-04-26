#include <cc1101.h>
#include <registers.h>
#include <pins.h>
#include <stdint.h>

uint16_t sensorValue;

void setup() {

	/* 1. Disable the watchdog timer and the GPIO   *
	 *	  power-on default high-impedance mode. */
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	/* 4. Enable both LEDs and turn them off. */
	P1DIR |= BIT0;
	P4DIR |= BIT6;
	P1OUT &= ~BIT0;
	P4OUT &= ~BIT6;

	/* 5. Initialize the CC1101 Radio module. */
	Radio.Init();
	Radio.SetDataRate(4);			// 38.313 kBaud
	Radio.SetLogicalChannel(1);		// Set the radio to channel 105
	Radio.SetTxPower(7);			// 11.9 mA
	Radio.Wakeup();

}

void loop() {

	/* 1. You must remember to turn RxOn every SEPERATE time you want to *
	 *	  receive. After you call ReceiveData(), the radio is no longer  *
	 *	  in receive mode, and your program will hang if you try to call *
	 *	  ReceiveData() again without first calling RxOn again.	   		 */
	Radio.RxOn();
	uint8_t rxData[2] = {0};

	/* 2. Check to see if the radio has received anything. If so,  *
	 *	  grab the data and check to see that it is correct. If it *
	 *	  is, blink the green LED, otherwise blink the red one.	   */
	if(Radio.CheckReceiveFlag()) {
		Radio.ReceiveData(rxData);
		P1OUT ^= BIT0;
		sensorValue = (rxData[0] << 8) | rxData[1];
//		Serial1.begin(9600);
//		Serial1.println(sensorValue);
/*		Radio.Init();
		Radio.SetDataRate(4);			// 38.313 kBaud
		Radio.SetLogicalChannel(1);		// Set the radio to channel 105
		Radio.SetTxPower(7);			// 11.9 mA
		Radio.Wakeup();
*/
	}

}
