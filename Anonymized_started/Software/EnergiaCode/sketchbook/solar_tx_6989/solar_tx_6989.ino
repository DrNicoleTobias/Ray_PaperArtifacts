#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

/* NOTE: You are currently using orange-orange-red-gold resistors as a 		*
 *		 voltage divider on the solar cells. Maybe try a smaller one.		*/
/****************************************************************************/
/* Global Variable Definitions												*/
/****************************************************************************/
Enrf24 radio(P2_3, P3_1, P3_0);  // P2.3=CE, P3.1=CSN, P3.0=IRQ
const uint8_t txaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
uint8_t numOfSensors = 4;
uint8_t smoothFactor = 50;
uint8_t solar0 = A4;			// P8.7
uint8_t solar1 = A5;			// P8.6
uint8_t solar2 = A6;			// P8.5
uint8_t solar3 = A7;			// P8.4

/****************************************************************************/
/* Initializations 															*/
/****************************************************************************/
void setup() {
	SPI.begin();
	SPI.setDataMode(SPI_MODE0);
	SPI.setBitOrder(MSBFIRST);
	radio.begin();  			// Defaults 1Mbps, channel 0, max TX power
	radio.setTXaddress((void*)txaddr);
}

/****************************************************************************/
/* Execution Loop 	 														*/
/****************************************************************************/
void loop() {

	/* 1. Read values from sensors. Repeat this process *
	 *    smoothFactor times and keep a running sum.    */
	uint8_t i;
	uint16_t sensorValue[4] = {0};
	for(i = 0; i < smoothFactor; i++) {
		sensorValue[0] += analogRead(solar0);
		sensorValue[1] += analogRead(solar1);
		sensorValue[2] += analogRead(solar2);
		sensorValue[3] += analogRead(solar3);
	}

	/* 2. For each sensor, divide the sum calculated in part 1 to get an *
	 *	  average reading for the period of time that it took to read 	 *
	 *	  smoothFacter readings. Write to the radio a byte at a time.	 *
	 *	  Sending order is highest byte first. Send data afterwards.	 */
	for(i = 0; i < numOfSensors; i++) {
		sensorValue[i] /= smoothFactor;
		radio.write((uint8_t) ((sensorValue[i] & 0xff00) >> 8));
		radio.write((uint8_t) (sensorValue[i] & 0x00ff));
		radio.flush();
	}

	/* 3. It is important to delay before repeating this process. The *
	 *	  board that is receiving the data needs enough time to read  *
	 *	  and print it to the terminal. Otherwise, it will become 	  *
	 *	  bogged down and stop working.								  */
	delay(50);
}
