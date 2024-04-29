#include <msp430fr5994.h>
#include "../include/cc1101.h"

#define TX_BUFFER_SIZE 5
#define DEVICE_KEY 57

uint8_t tx_buffer[TX_BUFFER_SIZE]={0};

int main(void){
	uint16_t temp = 0;

	//Stop watchdog timer
	WDTCTL = WDTPW + WDTHOLD;
  	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= BIT0;

	// Init results
	tx_buffer[0] = DEVICE_KEY;

	// Radio startup
	Init();
	SetDataRate(4); // Needs to be the same in Tx and Rx
	SetLogicalChannel(2); // Needs to be the same in Tx and Rx
	SetTxPower(3);
	//Sleep();

	// Main loop
	while(1) 
	{
		P1OUT ^= BIT0;
    	tx_buffer[1] = 1;
    	tx_buffer[2] = 5;

  		// Turn on radio, for speed, don't sleep / wakeup
		//Wakeup();
		__delay_cycles(100);
		SendData(tx_buffer, TX_BUFFER_SIZE);
		//Sleep();

    	__delay_cycles(100000);
	}

	return 1;
}
