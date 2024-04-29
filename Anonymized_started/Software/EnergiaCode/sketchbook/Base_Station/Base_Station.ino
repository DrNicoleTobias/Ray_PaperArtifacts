#include <cc1101.h>
#include <pins.h>
#include "pfatfs.h"
#include <registers.h>
#include "SPI.h" 
#include <stdint.h>
#include <time.h>

const uint8_t CS_PIN = 18;
const uint8_t ID_LENGTH = 5;
const uint8_t POWER_LENGTH = 6;
const uint8_t PACKET_LENGTH = ID_LENGTH + POWER_LENGTH;
const uint8_t TIMESTAMP_LENGTH = 21;
uint8_t sdError;
uint8_t data[512] = {0};
uint8_t *dataptr = data;
uint32_t dataReceived = 0;
uint32_t writeBlock = 0;
unsigned short int bw;

void setup() {

	/* 1. Disable the watchdog timer and the GPIO   *
	 *	  power-on default high-impedance mode. */
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	/* 2. Configure the pins. */
	P1DIR |= BIT0;				// Led1 configure as output
	P4DIR |= BIT6;				// Led2 configure as output
	P1OUT &= ~BIT0;				// Led1 set to off
	P4OUT &= ~BIT6;				// Led2 set to off

	/* 3. Initialize the CC1101 Radio module. */
	Radio.Init();
	Radio.SetDataRate(4);		// 38.313 kBaud
	Radio.SetLogicalChannel(1);	// Set the radio to channel 105
	Radio.SetTxPower(7);		// 11.9 mA
	Radio.Wakeup();				// Make sure that the radio is awake

	/* 4. Configure the Real Time Clock. MAKE SURE TO SET THIS */
	RTCCTL01 = RTCBCD | RTCHOLD;// RTC enable, BCD mode, RTC hold
	RTCYEAR = 0x2016;			// Year = 0x2016
	RTCMON = 0x03;				// Month = 0x03 = March
	RTCDAY = 0x22;				// Day = 0x22 = 22nd
	RTCDOW = 0x02;				// Day of week = 0x02 = Tuesday
	RTCHOUR = 0x23;				// Hour = 0x22 = 10pm
	RTCMIN = 0x30;				// Minute = 0x30 = 10:30pm
	RTCSEC = 0x00;				// Seconds = 0x00 = 10:30:00pm
	RTCCTL01 &= ~(RTCHOLD);		// Start RTC

    /* 5. Initialize the SD card and enable receiving. */
	if((sdError = FatFs.begin(CS_PIN))) { die(sdError); }
	Radio.RxOn();
}

void loop() {

	/* 1. Check to see if the radio has received anything. If so,  *
	 *	  store the current timestamp into the data buffer.		   */
	if(Radio.CheckReceiveFlag()) {
		GetTimeStamp((char*) dataptr);	
		dataptr += TIMESTAMP_LENGTH;

		/* 2a. Make sure that the radio ACTUALLY received something *
		 *     and didn't just return zero bytes worth of data.		*/
		if(Radio.ReceiveData(dataptr)) {
			dataptr += PACKET_LENGTH;
			dataReceived += TIMESTAMP_LENGTH + PACKET_LENGTH;

			/* FatFs.lseek() ONLY seeks by blocks of size 512. Thus, *
			 * to ensure we don't waste space, only write data to 	 *
			 * the SD card when the 512 byte data block is full.	 */
	   		if((dataReceived + TIMESTAMP_LENGTH + PACKET_LENGTH) > 512) {
				if((sdError = FatFs.open("DATA2.csv"))) { die(sdError); }		// Open data file
		   		if((sdError = FatFs.lseek(writeBlock))) { die(sdError); }		// Seek to next write block
		   		dataptr -= dataReceived;										// Reset dataptr so we can write all data
		        if((sdError = FatFs.write(dataptr,512,&bw))) { die(sdError); }	// Write data block
		        if((sdError = FatFs.close())) { die(sdError); }					// Finalize write														
		        writeBlock += 512;												// Increment writeBlock
		        memset(data, 0, dataReceived);									// Clear data buffer
		        dataReceived = 0;												// Reset bytes received
	   		}
   		}

   		/* 2b. If the radio does return zero bytes of data, don't bother *
   		 *	   saving the "data". Simply reset the pointer and move on.  */
   		else {
   			dataptr -= TIMESTAMP_LENGTH;
   		}

		/* 3. After you call ReceiveData() the radio is no longer in Rx mode *
		 *	  and will hang if you try to call ReceiveData() again. Thus,	 *
		 *	  make sure you enable Rx before your next call to ReceiveData().*/
		Radio.RxOn();
		P1OUT ^= BIT0;
	}
}

void GetTimeStamp(char *timestamp) {
	uint8_t index = 0;
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
	timestamp[index++] = ',';
	timestamp[index++] = ' ';
}

/* Blinks pff_err times and then sleep for 5 seconds. Repeat. */
void die (int pff_err) {
	Time.init_crystal();
	uint8_t i;
	for(;;) {
		for(i = 0; i < pff_err; i++) {
			P4OUT ^= BIT6;
			Time.lpm_wait_seconds(1, LPM3_bits);
		}
		Time.lpm_wait_seconds(5, LPM3_bits);
	}
}
