#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

/****************************************************************************/
/* Global Variable Definitions 	 											*/
/****************************************************************************/
Enrf24 radio(P2_3, P3_1, P3_0);  // P2.3=CE, P3.1=CSN, P3.0=IRQ
const uint8_t g_rxaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
uint8_t count;
uint8_t numOfSensors;
uint8_t recvBuff[2];
uint16_t sensorData;

/****************************************************************************/
/* Initializations	 														*/
/****************************************************************************/
void setup() {
	count = 0;
	numOfSensors = 4;
  	Serial.begin(9600);
	SPI.begin();
	SPI.setDataMode(SPI_MODE0);
	SPI.setBitOrder(MSBFIRST); 
	radio.begin();                       // Defaults 1Mbps, channel 0, max TX power
	radio.setRXaddress((void*)g_rxaddr); // Set the radios address
	radio.enableRX();                    // Start listening for BB controller
}

/****************************************************************************/
/* Execution Loop 	 														*/
/****************************************************************************/
void loop() {

	if(radio.available(true)) {
		radio.read(recvBuff, 2);
	    sensorData = (recvBuff[0] << 8) | recvBuff[1];
	    Serial.print(sensorData);
	    Serial.print(" ");
	    count++;
	    if(count == numOfSensors) {
	    	Serial.println();
	    	count = 0;
	    }
	}
}