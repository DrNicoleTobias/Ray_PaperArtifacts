#include <cc1101.h>
#include <registers.h>
#include <pins.h>
#include <stdint.h>

/* TODO: Look at clock settings for radio, time module, and  *
 *		 Backchannel UART. Modify them so that they all work *
 *		 together and dont get in each other's way.			 *
 *		 Put the RTC in the basestation						 *
 * TODO: Implement FRAM data logging.						 *
 * TODO: Enable pushbutton 1 so that the board will dump all *
 * TODO: of the data to the serial port when pushed.		 *
 * TODO: Modularize the code (i.e. use some functionss brah) */
const uint8_t rawLen = 3;
const uint8_t stampLen = 6;

void RTCToSerial(uint8_t *time);
void CharToSerial(char *data);
void DumpDataToSerial();
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
	P2SEL1 |= BIT0 | BIT1;              // USCI_A0 UART operation
  	P2SEL0 &= ~(BIT0 | BIT1);
	PJSEL0 |= BIT5 | BIT4;				// Enable PJ.4 and PJ.5 for XT1

	/* 5. Initialize the CC1101 Radio module. */
	Radio.Init();
	Radio.SetDataRate(4);			// 38.313 kBaud
	Radio.SetLogicalChannel(1);		// Set the radio to channel 105
	Radio.SetTxPower(7);			// 11.9 mA
	Radio.Wakeup();
	Radio.RxOn();

	/* 5. Enable the correct pins for XT1 and set the DCO to 8MHz. *
	 *    Then set ACLK = XT1 and MCLK = SMCLK = DCO / 8 = 1MHz.   */
	CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
	CSCTL1 = DCOFSEL_0;                       // Set DCO to 1MHz
	CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers
	CSCTL4 &= ~LFXTOFF;                       // Enable LFXT1
	do {
		CSCTL5 &= ~LFXTOFFG;                    // Clear XT1 fault flag
		SFRIFG1 &= ~OFIFG;
	} while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
	CSCTL0_H = 0;

	/* 7. Configure USCI_A0 for UART mode */
	UCA0CTL1 |= UCSWRST;
	UCA0CTL1 = UCSSEL__ACLK;            // Set ACLK = 32768 as UCBRCLK
	UCA0BR0 = 3;                        // 9600 baud
	UCA0MCTLW |= 0x5300;                // 32768/9600 - INT(32768/9600)=0.41
	                                    // UCBRSx value = 0x53 (See UG)
	UCA0BR1 = 0;
	UCA0CTL1 &= ~UCSWRST;               // release from reset
}

void loop() {

	/* 1. You must remember to turn RxOn every SEPERATE time you want to *
	 *	  receive. After you call ReceiveData(), the radio is no longer  *
	 *	  in receive mode, and your program will hang if you try to call *
	 *	  ReceiveData() again without first calling RxOn again.	   		 */
	uint8_t rxData[3] = {0};

	/* 2. Check to see if the radio has received anything. If so,  *
	 *	  grab the data and check to see that it is correct. If it *
	 *	  is, blink the green LED, otherwise blink the red one.	   */
	if(Radio.CheckReceiveFlag()) {
		Radio.ReceiveData(rxData);
		RTCToSerial(rxData);
		Radio.RxOn();
	}

}

void RTCToSerial(uint8_t *rawTime) {
	char timeStamp[stampLen];
	uint8_t rawCount, stampCount;
	for(rawCount = 0, stampCount = 0; rawCount < rawLen; rawCount++) {
		timeStamp[stampCount++]   = (rawTime[rawCount] & 0xF0) >> 4;
		timeStamp[stampCount++]   = (rawTime[rawCount] & 0x0F);
	}
	for(stampCount = 0; stampCount < stampLen; stampCount++) {
	    switch(timeStamp[stampCount]) {
	    	case 0x00:	timeStamp[stampCount] = '0';
	    		break;
	    	case 0x01:	timeStamp[stampCount] = '1';
	    		break;
	    	case 0x02:	timeStamp[stampCount] = '2';
	    		break;
	    	case 0x03:	timeStamp[stampCount] = '3';
	    		break;
	    	case 0x04:	timeStamp[stampCount] = '4';
	    		break;
	    	case 0x05:	timeStamp[stampCount] = '5';
	    		break;
	    	case 0x06:	timeStamp[stampCount] = '6';
	    		break;
	    	case 0x07:	timeStamp[stampCount] = '7';
	    		break;
	    	case 0x08:	timeStamp[stampCount] = '8';
	    		break;
	    	case 0x09:	timeStamp[stampCount] = '9';
	    		break;	
	    	default:	CharToSerial("No-Match");
	    		break;
	    }
	}
	for(rawCount = 0, stampCount = 0; rawCount < rawLen; rawCount++) {
		while(!(UCA0IFG & UCTXIFG));
	    UCA0TXBUF = timeStamp[stampCount++];
	  	while(!(UCA0IFG & UCTXIFG));
	   	UCA0TXBUF = timeStamp[stampCount++];
	   	while(!(UCA0IFG & UCTXIFG));
	   	UCA0TXBUF = ':';
	}
	while(!(UCA0IFG & UCTXIFG));
	UCA0TXBUF = '\r';
	while(!(UCA0IFG & UCTXIFG));
	UCA0TXBUF = '\n';
}

void CharToSerial(char *data) {
	while(*data != '\0') {
	    while(!(UCA0IFG & UCTXIFG));
	    UCA0TXBUF = *data;
	    data++;
	}
}

void DumpDataToSerial() {

}