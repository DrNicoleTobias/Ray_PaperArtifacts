#include <cc1101.h>
#include <registers.h>
#include <pins.h>
#include <stdint.h>

/* TODO: Implement SD Card data logging.					 *
 * TODO: Enable pushbutton 1 so that the board will dump all *
 *       of the data to the serial port when pushed.		 *
 * TODO: Comment and Organize								 */
const uint8_t ID_LENGTH = 8;
const uint8_t POWER_LENGTH = 15;
const uint8_t PACKET_LENGTH = ID_LENGTH + POWER_LENGTH;
const uint8_t TIMESTAMP_LENGTH = 23;

void CharToSerial(char *data);
void DumpSDToSerial();
void GetTimeStamp(char *timestamp);

void setup() {

	/* 1. Disable the watchdog timer and the GPIO   *
	 *	  power-on default high-impedance mode. */
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	/* 2. Configure the pins. */
	P1DIR |= BIT0;				// Led1 configure
	P4DIR |= BIT6;				// Led2 configure
	P1OUT &= ~BIT0;				// Led1 configure
	P4OUT &= ~BIT6;				// Led2 configure
	P2SEL1 |= BIT0 | BIT1;      // Configure Rx/Tx pins for UART
  	P2SEL0 &= ~(BIT0 | BIT1);	// Configure Rx/Tx pins for UART
	PJSEL0 |= BIT5 | BIT4;		// Enable PJ.4 and PJ.5 for LFXT

	/* 3. Initialize the CC1101 Radio module. */
	Radio.Init();
	Radio.SetDataRate(4);		// 38.313 kBaud
	Radio.SetLogicalChannel(1);	// Set the radio to channel 105
	Radio.SetTxPower(7);		// 11.9 mA
	Radio.Wakeup();
	Radio.RxOn();

	/* 4. Set the DCO to 1MHz, and then set ACLK = XT1 *
	 *	  and MCLK = SMCLK = DCO / 1 = 1MHz.   		   */
	CSCTL0_H = CSKEY >> 8;		// Unlock CS registers
	CSCTL1 = DCOFSEL_0;         // Set DCO to 1MHz
	CSCTL2 = SELA__LFXTCLK |	// ACLK  = LFXT1
			 SELS__DCOCLK  |	// SMCLK = DCO
			 SELM__DCOCLK;		// MCLK  = DCO
	CSCTL3 = DIVA__1 |			// Set all clock dividers = 1
			 DIVS__1 |
			 DIVM__1;
	CSCTL4 &= ~LFXTOFF;			// Enable LFXT1
	do {						// Wait for the crystal to settle
		CSCTL5 &= ~LFXTOFFG;    // Clear LFXT1 fault flag
		SFRIFG1 &= ~OFIFG;
	} while (SFRIFG1&OFIFG);    // Test oscillator fault flag
	CSCTL0_H = 0;				// Lock CS registers

	/* 5. Configure USCI_A0 for UART mode. This will *
	 *	  be used to print data to the computer.	 */
	UCA0CTL1 |= UCSWRST;		// Unlock USCI_A0 registers
	UCA0CTL1 = UCSSEL__ACLK;	// Set ACLK = 32768 as UCBRCLK
	UCA0BR0 = 3;				// 9600 baud
	UCA0MCTLW |= 0x5300;		// 32768/9600 - INT(32768/9600)=0.41
								// UCBRSx value = 0x53 (See UG)
	UCA0BR1 = 0;
	UCA0CTL1 &= ~UCSWRST;		// Lock USCI_A0 registers

	/* 6. Configure the Real Time Clock. */
	RTCCTL01 = RTCBCD | RTCHOLD;// RTC enable, BCD mode, RTC hold
    RTCYEAR = 0x2016;			// Year = 0x2016
    RTCMON = 0x03;				// Month = 0x03 = March
    RTCDAY = 0x22;				// Day = 0x22 = 22nd
    RTCDOW = 0x02;				// Day of week = 0x02 = Tuesday
    RTCHOUR = 0x23;				// Hour = 0x22 = 10pm
    RTCMIN = 0x30;				// Minute = 0x30 = 10:30pm
    RTCSEC = 0x00;				// Seconds = 0x00 = 10:30:00pm
    RTCCTL01 &= ~(RTCHOLD);		// Start RTC
}

void loop() {

	/* 1. You must remember to turn RxOn every SEPERATE time you want to *
	 *	  receive. After you call ReceiveData(), the radio is no longer  *
	 *	  in receive mode, and your program will hang if you try to call *
	 *	  ReceiveData() again without first calling RxOn again.	   		 */
	uint8_t rxData[PACKET_LENGTH] = {0};

	/* 2. Check to see if the radio has received anything. If so,  *
	 *	  grab the data and check to see that it is correct. If it *
	 *	  is, blink the green LED, otherwise blink the red one.	   */
	if(Radio.CheckReceiveFlag()) {
		Radio.ReceiveData(rxData);
		CharToSerial((char *)rxData);
		Radio.RxOn();
	}

}

void CharToSerial(char *data) {
	char buf[TIMESTAMP_LENGTH] = {0};
	char *timestamp = buf;
	GetTimeStamp(timestamp);

	while(*timestamp != '\0') {
	    while(!(UCA0IFG & UCTXIFG));
	    UCA0TXBUF = *timestamp;
	    timestamp++;
	}
	while(*data != '\0') {
	    while(!(UCA0IFG & UCTXIFG));
	    UCA0TXBUF = *data;
	    data++;
	}
	while(!(UCA0IFG & UCTXIFG));
	UCA0TXBUF = '\r';
	while(!(UCA0IFG & UCTXIFG));
	UCA0TXBUF = '\n';
}


void DumpSDToSerial() {

}

void GetTimeStamp(char *timestamp) {
	uint8_t index = 0;
	timestamp[index++] = '(';
	timestamp[index++] = ((RTCYEAR & 0xF000) >> 12) + 48;
	timestamp[index++] = ((RTCYEAR & 0x0F00) >>  8) + 48;
	timestamp[index++] = ((RTCYEAR & 0x00F0) >>  4) + 48;
	timestamp[index++] =  (RTCYEAR & 0x000F) + 48;
	timestamp[index++] = '-';
	timestamp[index++] = ((RTCMON & 0xF0) >> 4) + 48;
	timestamp[index++] =  (RTCMON & 0x0F) + 48;
	timestamp[index++] = '-';
	timestamp[index++] = ((RTCDAY & 0xF0) >> 4) + 48;
	timestamp[index++] =  (RTCDAY & 0x0F) + 48;
	timestamp[index++] = ' ';
	timestamp[index++] = ((RTCHOUR & 0xF0) >> 4) + 48;
	timestamp[index++] =  (RTCHOUR & 0x0F) + 48;
	timestamp[index++] = ':';
	timestamp[index++] = ((RTCMIN & 0xF0) >> 4) + 48;
	timestamp[index++] =  (RTCMIN & 0x0F) + 48;
	timestamp[index++] = ':';
	timestamp[index++] = ((RTCSEC & 0xF0) >> 4) + 48;
	timestamp[index++] =  (RTCSEC & 0x0F) + 48;
	timestamp[index++] = ')';
	timestamp[index++] = ' ';
	timestamp[index++] = '\0';
}