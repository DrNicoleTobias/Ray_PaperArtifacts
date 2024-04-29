#include "cc1101.h"

/****************************************************************/
#define 	WRITE_BURST     	0x40						//write burst
#define 	READ_SINGLE     	0x80						//read single
#define 	READ_BURST      	0xC0						//read burst
#define 	BYTES_IN_RXFIFO     0x7F  						//uint8_t number in RXfifo

#define PAYLOAD_LENGTH 320    //Total OOK bytes to be sent by radio

/**
 * Type of register
 */
#define CC1101_CONFIG_REGISTER   READ_SINGLE
#define CC1101_STATUS_REGISTER   READ_BURST

/****************************************************************/

uint8_t PaTabel[8] = {0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0};

uint8_t mrfiRadioState = 0;
uint8_t rfPowerNdx = 0;
uint8_t dataRateNdx = 9;
uint8_t packetLength = 61;

static const uint8_t rfPowerTable[] = {
	/* 10 dBm */	0xC0, // 29.1 mA
	/* 7 dBm */		0xC8, // 24.2 mA
	/* 5 dBm */		0x84, // 19.4 mA
	/* 0 dBm */		0x60, // 15.9 mA
	/* -10 dBm */	0x34, // 14.4 mA
	/* -15 dBm */	0x1D, // 13.1 mA
	/* -20 dBm */	0x0E, // 12.4 mA
	/* -30 dBm */	0x12, // 11.9 mA
};

/** If clocking in a lot of data over SPI bus, clock speed of MCU needs to be higher */
/** Otherwise data will be lost */
// 0-10 data rates, 0-2 only use if in high speed mode on MCU
static const uint8_t rate_MDMCFG3[] = {
	0x3b, // 499.590 kBaud
	0x3b, // 249.795 kBaud
	0x83, // 153.252 kBaud
	0x83, //  76.626 kBaud /* This setting works well, and any data rates below it */
	0x83, //  38.313 kBaud
	0x8b, //  19.355 kBaud
	0x83, //   9.288 kBaud
	0x83, //   4.644 kBaud
	0x83, //   2.322 kBaud
	0x83, //   1.161 kBaud
	0x43  //   0.969 kBaud
};

static const uint8_t rate_MDMCFG4[] = {
	0x8e, // 499.590 kBaud
	0x8d, // 249.795 kBaud
	0x8c, // 153.252 kBaud
	0x8b, //  76.626 kBaud
	0x8a, //  38.313 kBaud
	0x89, //  19.355 kBaud
	0x88, //   9.288 kBaud
	0x87, //   4.644 kBaud
	0x86, //   2.322 kBaud
	0x85, //   1.161 kBaud
	0x85  //   0.969 kBaud
};

#define __mrfi_NUM_LOGICAL_CHANS__      25
static const uint8_t mrfiLogicalChanTable[] = // randomized version
{
   90, 105,  40,  45,  70,
   80, 100,   5,  60, 115,
   15, 125, 120,  50,  95,
   30,  75,  10,  25,  55,
  110,  65,  85,  35,  20
};

/****************************************************************
*FUNCTION NAME:SpiInit
*FUNCTION     :spi communication initialization
*INPUT        :none
*OUTPUT       :none
****************************************************************/
void SpiInit(void)
{
	// initialize the SPI pins

    /* configure all SPI related pins */
    SPI_CONFIG_CSN_PIN_AS_OUTPUT();
    SPI_CONFIG_SCLK_PIN_AS_OUTPUT();
    SPI_CONFIG_SI_PIN_AS_OUTPUT();
    SPI_CONFIG_SO_PIN_AS_INPUT();

    /* set CSn to default high level */
    SPI_DRIVE_CSN_HIGH();

    /* initialize the SPI registers */
	SPI_INIT();
}


/****************************************************************
*FUNCTION NAME:SpiTransfer
*FUNCTION     :spi transfer
*INPUT        :value: data to send
*OUTPUT       :data to receive / status byte
****************************************************************/
uint8_t SpiTransfer(uint8_t value)
{
	uint8_t statusByte;
	/* send the command strobe, wait for SPI access to complete */
	SPI_WRITE_BYTE(value);
	SPI_WAIT_DONE();

	/* read the readio status uint8_t returned by the command strobe */
	statusByte = SPI_READ_BYTE();
	//debug_stats[debug_index] = statusByte;
	//debug_index++;
	return statusByte;
}

/****************************************************************
*FUNCTION NAME: GDO_Set()
*FUNCTION     : set GDO0,GDO2 pin
*INPUT        : none
*OUTPUT       : none
****************************************************************/
void GDO_Set (void)
{
	CONFIG_GDO0_PIN_AS_INPUT();
	CONFIG_GDO2_PIN_AS_INPUT();
}

/****************************************************************
*FUNCTION NAME:Reset
*FUNCTION     :CC1101 reset //details refer datasheet of CC1101/CC1100//
*INPUT        :none
*OUTPUT       :none
****************************************************************/
void Reset (void)
{
	SPI_DRIVE_CSN_LOW();
	__delay_cycles(1);
	SPI_DRIVE_CSN_HIGH();
	__delay_cycles(1);
	SPI_DRIVE_CSN_LOW();
	while (SPI_SO_IS_HIGH());
	SpiTransfer(CC1101_SRES);
	while (SPI_SO_IS_HIGH());
	SPI_DRIVE_CSN_HIGH();
}

/****************************************************************
*FUNCTION NAME:Init
*FUNCTION     :CC1101 initialization
*INPUT        :none
*OUTPUT       :none
****************************************************************/
void Init(void)
{
	SpiInit();										//spi initialization
	GDO_Set();										//GDO set
	Reset();										//CC1101 reset
	RegConfigSettings();							//CC1101 register config
	SpiWriteBurstReg(CC1101_PATABLE,PaTabel,8);		//CC1101 PATABLE config
	mrfiRadioState = RADIO_STATE_IDLE;
}

/****************************************************************
*FUNCTION NAME:OOKInit
*FUNCTION     :CC1101 initialization
*INPUT        :none
*OUTPUT       :none
****************************************************************/
void OOKInit(void)
{
	SpiInit();										//spi initialization
	GDO_Set();										//GDO set
	Reset();											//CC1101 reset
	OOkRegsConfig();							//CC1101 register config
	uint8_t PA_TABLE[]= {0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00}; //Max transmit power
	SpiWriteBurstReg(CC1101_PATABLE,PA_TABLE,8);		//CC1101 PATABLE config
}


/****************************************************************
*FUNCTION NAME:SpiWriteReg
*FUNCTION     :CC1101 write data to register
*INPUT        :addr: register address; value: register value
*OUTPUT       :none
****************************************************************/
void SpiWriteReg(uint8_t addr, uint8_t value)
{
	SPI_DRIVE_CSN_LOW();
	while (SPI_SO_IS_HIGH());
	SpiTransfer(addr);
	SpiTransfer(value);
	SPI_DRIVE_CSN_HIGH();
}

/****************************************************************
*FUNCTION NAME:SpiWriteBurstReg
*FUNCTION     :CC1101 write burst data to register
*INPUT        :addr: register address; buffer:register value array; num:number to write
*OUTPUT       :none
****************************************************************/
void SpiWriteBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num)
{
	uint8_t i, temp;
	temp = addr | WRITE_BURST;

	SPI_TURN_CHIP_SELECT_OFF();
	SPI_TURN_CHIP_SELECT_ON();

	while (SPI_SO_IS_HIGH());
	SpiTransfer(temp);
	for (i = 0; i < num; i++)
	{
	    SpiTransfer(buffer[i]);
	}
	SPI_TURN_CHIP_SELECT_OFF();
}

/****************************************************************
*FUNCTION NAME:SpiStrobe
*FUNCTION     :CC1101 Strobe
*INPUT        :strobe: command; //refer define in CC1101.h//
*OUTPUT       :status byte
****************************************************************/
uint8_t SpiStrobe(uint8_t strobe)
{
	SPI_TURN_CHIP_SELECT_ON();
	while (SPI_SO_IS_HIGH());
	uint8_t statusByte = SpiTransfer(strobe);
	SPI_TURN_CHIP_SELECT_OFF();
	return statusByte;
}

/****************************************************************
*FUNCTION NAME:SpiReadReg
*FUNCTION     :CC1101 read data from register
*INPUT        :addr: register address
*OUTPUT       :register value
****************************************************************/
uint8_t SpiReadReg(uint8_t addr)
{
	uint8_t temp, value;

  temp = addr|READ_SINGLE;
	SPI_DRIVE_CSN_LOW();
	while (SPI_SO_IS_HIGH());
	SpiTransfer(temp);
	value=SpiTransfer(0);
	SPI_DRIVE_CSN_HIGH();

	return value;
}


/****************************************************************
*FUNCTION NAME:SpiReadStatusReg
*FUNCTION     :CC1101 read data from status register
*INPUT        :addr: register address
*OUTPUT       :register value
****************************************************************/
uint8_t SpiReadStatusReg(uint8_t addr)
{
	uint8_t temp, value;

  temp = addr|READ_BURST;
	SPI_DRIVE_CSN_LOW();
	while (SPI_SO_IS_HIGH());
	SpiTransfer(temp);
	value=SpiTransfer(0);
	SPI_DRIVE_CSN_HIGH();

	return value;
}

/****************************************************************
*FUNCTION NAME:SpiReadBurstReg
*FUNCTION     :CC1101 read burst data from register
*INPUT        :addr: register address; buffer:array to store register value; num: number to read
*OUTPUT       :none
****************************************************************/
void SpiReadBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num)
{
	uint8_t i,temp;

	temp = addr | READ_BURST;
	SPI_DRIVE_CSN_LOW();
	while (SPI_SO_IS_HIGH());
	SpiTransfer(temp);
	for(i=0;i<num;i++)
	{
		buffer[i]=SpiTransfer(0);
	}
	SPI_DRIVE_CSN_HIGH();
}

/****************************************************************
*FUNCTION NAME:SpiReadStatus
*FUNCTION     :CC1101 read status register
*INPUT        :addr: register address
*OUTPUT       :status value
****************************************************************/
uint8_t SpiReadStatus(uint8_t addr)
{
	uint8_t value,temp;

	temp = addr | READ_BURST;
	SPI_DRIVE_CSN_LOW();
	while (SPI_SO_IS_HIGH());
	SpiTransfer(temp);
	value=SpiTransfer(0);
	SPI_DRIVE_CSN_HIGH();

	return value;
}

/****************************************************************
*FUNCTION NAME:RegConfigSettings
*FUNCTION     :CC1101 register config //details refer datasheet of CC1101/CC1100//
*INPUT        :none
*OUTPUT       :none
****************************************************************/
void RegConfigSettings(void)
{
    SpiWriteReg(CC1101_FSCTRL1,  0x08);
    SpiWriteReg(CC1101_FSCTRL0,  0x00);
    SpiWriteReg(CC1101_FREQ2,    0x10);
    SpiWriteReg(CC1101_FREQ1,    0xA7);
    SpiWriteReg(CC1101_FREQ0,    0x62);
    SpiWriteReg(CC1101_MDMCFG4,  rate_MDMCFG4[dataRateNdx]); // CHANBW_E[1:0], CHANBW_M[1:0], DRATE_E[3:0], Reset is B10001100, 0x56 is 1.5kBaud, 0x55 is around 0.6kBaud
    SpiWriteReg(CC1101_MDMCFG3,  rate_MDMCFG3[dataRateNdx]); // DRATE_M[7:0], Reset is 0x22, 0x00 with above setting is 1.5kBaud
    SpiWriteReg(CC1101_MDMCFG2,  0x03);
    SpiWriteReg(CC1101_MDMCFG1,  0x22);
    SpiWriteReg(CC1101_MDMCFG0,  0xF8);
    SpiWriteReg(CC1101_CHANNR,   0x00);
    SpiWriteReg(CC1101_DEVIATN,  0x47);
    SpiWriteReg(CC1101_FREND1,   0xB6);
    SpiWriteReg(CC1101_FREND0,   0x10);
    SpiWriteReg(CC1101_MCSM0 ,   0x18);
    SpiWriteReg(CC1101_FOCCFG,   0x1D);
    SpiWriteReg(CC1101_BSCFG,    0x1C);
    SpiWriteReg(CC1101_AGCCTRL2, 0xC7);
		SpiWriteReg(CC1101_AGCCTRL1, 0x00);
    SpiWriteReg(CC1101_AGCCTRL0, 0xB2);
    SpiWriteReg(CC1101_FSCAL3,   0xEA);
		SpiWriteReg(CC1101_FSCAL2,   0x2A);
		SpiWriteReg(CC1101_FSCAL1,   0x00);
    SpiWriteReg(CC1101_FSCAL0,   0x11);
    SpiWriteReg(CC1101_FSTEST,   0x59);
    SpiWriteReg(CC1101_TEST2,    0x81);
    SpiWriteReg(CC1101_TEST1,    0x35);
    SpiWriteReg(CC1101_TEST0,    0x09);
    SpiWriteReg(CC1101_IOCFG2,   0x0B); 	//serial clock.synchronous to the data in synchronous serial mode
    SpiWriteReg(CC1101_IOCFG0,   0x06);  	//asserts when sync word has been sent/received, and de-asserts at the end of the packet
    SpiWriteReg(CC1101_PKTCTRL1, 0x04);		//two status uint8_ts will be appended to the payload of the packet,including RSSI LQI and CRC OK, no address check
    SpiWriteReg(CC1101_PKTCTRL0, 0x05);		//whitening off;CRC Enable��fixed length packets set by PKTLEN reg
    SpiWriteReg(CC1101_ADDR,     0x00);		//address used for packet filtration.
    SpiWriteReg(CC1101_PKTLEN,   0x3D); 	//61 uint8_ts max length
}


/****************************************************************
*FUNCTION NAME:RegConfigSettings for OOK modulation
*FUNCTION     :CC1101 register config //details refer datasheet of CC1101/CC1100//
*INPUT        :none
*OUTPUT       :none
****************************************************************/
void OOkRegsConfig(void)
{
	SpiWriteReg(CC1101_IOCFG2,   0x2E);  	//GDO0 Output Pin Configuration
	SpiWriteReg(CC1101_IOCFG1,   0x2E);
	SpiWriteReg(CC1101_IOCFG0,   0x06);  	//GDO0 Output Pin Configuration
  SpiWriteReg(CC1101_FIFOTHR,  0x47);   //RX FIFO and TX FIFO Thresholds
	SpiWriteReg(CC1101_PKTLEN, 	 0xFF);
	SpiWriteReg(CC1101_PKTCTRL1, 0x04);
	SpiWriteReg(CC1101_PKTCTRL0, 0x02);		//Packet Automation Control
	setSyncWord(0xD3, 0x91);							// Set default synchronization word
	SpiWriteReg(CC1101_ADDR, 		 0x11);
	SpiWriteReg(CC1101_CHANNR, 	 0x00);
	SpiWriteReg(CC1101_FSCTRL1,  0x06);
	SpiWriteReg(CC1101_FSCTRL0,  0x00);		//Frequency Synthesizer Control
	SpiWriteReg(CC1101_FREQ2,    0x10);
	SpiWriteReg(CC1101_FREQ1,    0xA7);
	SpiWriteReg(CC1101_FREQ0,    0x62);
	SpiWriteReg(CC1101_MDMCFG4,  0xFD); 	// CHANBW_E[1:0], CHANBW_M[1:0], DRATE_E[3:0], Reset is B10001100, 0x56 is 1.5kBaud, 0x55 is around 0.6kBaud
  SpiWriteReg(CC1101_MDMCFG3,  0x3B); 	// DRATE_M[7:0], Reset is 0x22, 0x00 with above setting is 1.5kBaud
  SpiWriteReg(CC1101_MDMCFG2,  0x30);
	SpiWriteReg(CC1101_MDMCFG1,  0x22);
	SpiWriteReg(CC1101_MDMCFG0,  0xF8);
	SpiWriteReg(CC1101_DEVIATN,  0x15);
	SpiWriteReg(CC1101_MCSM2 ,   0x07);		//Main Radio Control State Machine Configuration
	SpiWriteReg(CC1101_MCSM1 ,   0x20);
	SpiWriteReg(CC1101_MCSM0 ,   0x18);
	SpiWriteReg(CC1101_FOCCFG,   0x16);
	SpiWriteReg(CC1101_BSCFG,    0x6C);
	SpiWriteReg(CC1101_AGCCTRL2, 0x03);
	SpiWriteReg(CC1101_AGCCTRL1, 0x00);
	SpiWriteReg(CC1101_AGCCTRL0, 0x91);
	SpiWriteReg(CC1101_WOREVT1,  0x87);
	SpiWriteReg(CC1101_WOREVT0,  0x6B);
	SpiWriteReg(CC1101_WORCTRL,  0xFB);		//Wake On Radio Control
	SpiWriteReg(CC1101_FREND1,   0x56);
	SpiWriteReg(CC1101_FREND0,   0x11);
	SpiWriteReg(CC1101_FSCAL3,   0xE9);
  SpiWriteReg(CC1101_FSCAL2,   0x2A);
  SpiWriteReg(CC1101_FSCAL1,   0x00);
  SpiWriteReg(CC1101_FSCAL0,   0x1F);
	SpiWriteReg(CC1101_RCCTRL1,  0x41);
	SpiWriteReg(CC1101_RCCTRL0,  0x00);
	SpiWriteReg(CC1101_FSTEST,   0x59);
	SpiWriteReg(CC1101_PTEST,    0x7F);
	SpiWriteReg(CC1101_AGCTEST,  0x3F);
	SpiWriteReg(CC1101_TEST2,    0x88);
  SpiWriteReg(CC1101_TEST1,    0x31);
  SpiWriteReg(CC1101_TEST0,    0x0B);
}


/****************************************************************
*FUNCTION NAME:SendData
*FUNCTION     :use CC1101 send data
*INPUT        :txBuffer: data array to send; size: number of data to send, no more than packet length
*OUTPUT       :none
****************************************************************/
void SendData(uint8_t *txBuffer,uint8_t size)
{
	//txBuffer[0] = 57;
	//txBuffer[1] = 3;
	//txBuffer[2] = 7;
	SpiWriteReg(CC1101_TXFIFO,size); // Send size first in variable length mode (always be in var length mode)
	SpiWriteBurstReg(CC1101_TXFIFO,txBuffer,size);			//write data to send
	SpiStrobe(CC1101_STX);									//start send
	while (!GDO0_PIN_IS_HIGH());
	while (GDO0_PIN_IS_HIGH());
	SpiStrobe(CC1101_SFTX);									//flush TXfifo
}

/****************************************************************
*FUNCTION NAME:SendDataNoWait
*FUNCTION     :use CC1101 send data but don't wait for the GDO0 pins
*INPUT        :txBuffer: data array to send; size: number of data to send, no more than packet length
*OUTPUT       :none
****************************************************************/
void SendDataNoWait(uint8_t *txBuffer,uint8_t size)
{
	SpiWriteReg(CC1101_TXFIFO,size); // Send size first in variable length mode (always be in var length mode)
	SpiWriteBurstReg(CC1101_TXFIFO,txBuffer,size);			//write data to send
	SpiStrobe(CC1101_STX);									//start send
	__delay_cycles(1000);
	SpiStrobe(CC1101_SFTX);									//flush TXfifo
}

/****************************************************************
*FUNCTION NAME:SetReceive
*FUNCTION     :set CC1101 to receive state
*INPUT        :none
*OUTPUT       :none
****************************************************************/
void RxOn(void)
{
	SpiStrobe(CC1101_SRX);
	mrfiRadioState = RADIO_STATE_RX;
}

/****************************************************************
*FUNCTION NAME:CheckReceiveFlag
*FUNCTION     :check receive data or not
*INPUT        :none
*OUTPUT       :flag: 0 no data; 1 receive data
****************************************************************/
uint8_t CheckReceiveFlag(void)
{
	if(GDO0_PIN_IS_HIGH())			//receive data
	{
		while (GDO0_PIN_IS_HIGH());
		return 1;
	}
	else							// no data
	{
		return 0;
	}
}


/****************************************************************
*FUNCTION NAME:ReceiveData
*FUNCTION     :read data received from RXfifo
*INPUT        :rxBuffer: buffer to store data
*OUTPUT       :size of data received
****************************************************************/
uint8_t ReceiveData(uint8_t *rxBuffer)
{
	uint8_t size;
	uint8_t status[2];

	if(SpiReadStatus(CC1101_RXBYTES) & BYTES_IN_RXFIFO)
	{
		size=SpiReadReg(CC1101_RXFIFO);
		SpiReadBurstReg(CC1101_RXFIFO,rxBuffer,size);
		SpiReadBurstReg(CC1101_RXFIFO,status,2);
		SpiStrobe(CC1101_SFRX);    //maybe move this to after the next statement-NT
		//RxOn(); // ???? I this bad????
		mrfiRadioState = RADIO_STATE_IDLE;
		return size;
	}
	else
	{
		SpiStrobe(CC1101_SFRX);
		//RxOn(); // ???? I this bad????
		mrfiRadioState = RADIO_STATE_IDLE;
		return 0;
	}
}

/****************************************************************
* ReceiveData
* FUNCTION     :set the data rate, i.e. how fast we send data in terms of bytes (baud rate)
* INPUT        :rate_ndx: the ndx in the MDMCFG registers to set to, refer to rate_MDMCFGX arrays
* OUTPUT       :none
****************************************************************/
void SetDataRate(uint8_t rate_ndx) {
	dataRateNdx = rate_ndx;
	RxModeOff();
	SpiWriteReg(CC1101_MDMCFG4, rate_MDMCFG4[rate_ndx]);
	SpiWriteReg(CC1101_MDMCFG3, rate_MDMCFG3[rate_ndx]);
	if(mrfiRadioState == RADIO_STATE_RX) {
		RxOn();
	}
}

// Sets ALL harmonics to the same power, which could be undesirable
void SetTxPower(uint8_t powrset) {
	rfPowerNdx = powrset;
	RxModeOff();
	for(uint8_t i=0;i<8;i++)
		PaTabel[i] = rfPowerTable[powrset];
	SpiWriteBurstReg(CC1101_PATABLE,PaTabel,8);		//CC1101 PATABLE config
	if(mrfiRadioState == RADIO_STATE_RX) {
		RxOn();
	}
}

// This idles but does not change here
void RxModeOff() {
	SpiStrobe(CC1101_SIDLE);
	while (SpiStrobe(CC1101_SNOP) & 0xF0);
	SpiStrobe(CC1101_SFRX);
}

// Idle mode probably should be avoided, as 1mA draw
// Only voltage regulator to digital part and crystal oscillator running
void Idle() {
	//if(mrfiRadioState == RADIO_STATE_RX) {
		RxModeOff();
		mrfiRadioState = RADIO_STATE_IDLE;
	//}
}

// Voltage regulator to digital part off, register values retained (SLEEP state).
// All GDO pins programmed to 0x2F (HW to 0)
// Lowest power state for radio, should draw ~200nA
void Sleep() {
	Idle();
	delay(1);
	SpiStrobe(CC1101_SPWD);
	mrfiRadioState = RADIO_STATE_OFF;
}

void Wakeup() {
	/* if radio is already awake, just ignore wakeup request */
	if(mrfiRadioState != RADIO_STATE_OFF) {
		return;
	}

    /* drive CSn low to initiate wakeup */
    SPI_DRIVE_CSN_LOW();

    /* wait for MISO to go high indicating the oscillator is stable */
    while (SPI_SO_IS_HIGH());

    /* wakeup is complete, drive CSn high and continue */
    SPI_DRIVE_CSN_HIGH();

	/*
	*  The test registers must be restored after sleep for the CC1100 and CC2500 radios.
	*  This is not required for the CC1101 radio.
	*/
	// #ifndef MRFI_CC1101/
	//  mrfiSpiWriteReg( TEST2, SMARTRF_SETTING_TEST2 );
	//  mrfiSpiWriteReg( TEST1, SMARTRF_SETTING_TEST1 );
	//  mrfiSpiWriteReg( TEST0, SMARTRF_SETTING_TEST0 );
	// #endif

	 /* enter idle mode */
	 mrfiRadioState = RADIO_STATE_IDLE;
}

uint8_t GetState() {
	return	mrfiRadioState;
}

uint8_t GetMARCState() {
	//return	SpiReadReg(CC1101_MARCSTATE);
	//return SpiStrobe(0xF5);
	return SpiReadStatusReg(CC1101_MARCSTATE) & 0x1F;
}

void SetLogicalChannel(uint8_t channel) {
    /* logical channel is not valid? */
   if (channel >= __mrfi_NUM_LOGICAL_CHANS__) return;

    /* make sure radio is off before changing channels */
    RxModeOff();

	SpiWriteReg(CC1101_CHANNR, mrfiLogicalChanTable[channel]);
    /* turn radio back on if it was on before channel change */

	if(mrfiRadioState == RADIO_STATE_RX) {
		RxOn();
	}
}

void SetMaxPacketLength(uint8_t pkt_length) {
	packetLength = pkt_length;
	SpiWriteReg(CC1101_PKTLEN, pkt_length);
}

/**
 * setSyncWord
 *
 * Set synchronization word
 *
 * 'syncH'	Synchronization word - High byte
 * 'syncL'	Synchronization word - Low byte
 * 'save' If TRUE, save parameter in EEPROM
 */
void setSyncWord(uint8_t syncH, uint8_t syncL)
{
	SpiWriteReg(CC1101_SYNC1, syncH);
	SpiWriteReg(CC1101_SYNC0, syncL);
}


/**
 * sendnbytes
 *
 * Send n bytes packet via RF
 *
 * 'fullpayload'  Packet to be transmitted.
 * 'numbytes'     number of bytes to send
 * 'sentinel'     tracks the position of the next byte to transmit in the payload
 *
 *  Return:       Nothing
 */
void sendnbytes(uint8_t * fullpayload, uint8_t numbytes, int * sentinel)
{
    uint8_t data[numbytes];
    for(uint8_t i=0; i<numbytes; i++){
      data[i] = fullpayload[i + *sentinel];
    }
    // Write data into the TX FIFO
    SpiWriteBurstReg(CC1101_TXFIFO, data, numbytes);

    // CCA enabled: (Strobe TX)
		SpiStrobe(CC1101_STX);									//start send

    //update sentinel value
    (*sentinel) += numbytes;
}


/**
 * sendBulkOOKData
 *
 * Send more than 64bytes packet via RF
 *
 * 'payload'  Packet to be transmitted.
 *
 *  Return:
 *    True if the transmission succeeds
 *    False otherwise
 */
int sendBulkOOKData(uint8_t * payload, int length)
{
  uint8_t marcState;
  int res = 0;
  int sentinel = 0;

  // Declare to be in Tx state. This will avoid receiving packets whilst transmitting
  mrfiRadioState = RADIO_STATE_TX;

  // Enter RX state
  SpiStrobe(CC1101_SRX);

  // Check that the RX state has been entered
  while (((marcState = SpiReadStatusReg(CC1101_MARCSTATE)) & 0x1F) != 0x0D)
  {
    if (marcState == 0x11)        // RX_OVERFLOW
      SpiStrobe(CC1101_SFRX);              // flush receive queue
  }

  __delay_cycles(50);

  //Send the first 64 bytes
  sendnbytes(payload, 64, &sentinel);

  // Check that TX state is being entered (state = RXTX_SETTLING)
  marcState = SpiReadStatusReg(CC1101_MARCSTATE) & 0x1F;
  if((marcState != 0x13) && (marcState != 0x14) && (marcState != 0x15))
  {
    SpiStrobe(CC1101_SIDLE);       // Enter IDLE state
    SpiStrobe(CC1101_SFTX);        // Flush Tx FIFO
    SpiStrobe(CC1101_SRX);         // Back to RX state

    // Declare to be in Rx state
    mrfiRadioState = RADIO_STATE_RX;
    return 0;
  }

  //Transmit remaining packets as space become available
  while(sentinel < length){
    uint8_t remainingpkt =  (SpiReadStatusReg(CC1101_TXBYTES) & 0x7F);
    if(remainingpkt < 64){
      uint8_t freebytes = 64 - remainingpkt;
      sendnbytes(payload, freebytes, &sentinel);
    }
  }

  // Wait for the sync word to be transmitted
  while (!GDO0_PIN_IS_HIGH());

  // Wait until the end of the packet transmission
  while (GDO0_PIN_IS_HIGH());

  // Check that the TX FIFO is empty
  if((SpiReadStatusReg(CC1101_TXBYTES) & 0x7F) == 0)
    res = 1;

  SpiStrobe(CC1101_SIDLE);       // Enter IDLE state
  SpiStrobe(CC1101_SFTX);       // Flush Tx FIFO

  // Enter back into RX state
  SpiStrobe(CC1101_SRX);

  // Declare to be in Rx state
  mrfiRadioState = RADIO_STATE_RX;

  return res;
}

/*
 * transformPattern
 * converts 5bytes pattern to 320bytes for transmission
 * Takes in the pattern array and the array to be filled up
 * Return: Nothing
 */
void transformPattern(uint8_t * pattern, uint8_t * transformed)
{
  int index = 0;

  //Loop through each byte of the pattern
  for(uint8_t i=0; i<5; i++){
    //select each byte of the pattern
    uint8_t oneByte = pattern[i];
    //Loop through each bits(8) of the byte from MSB to LSB
    for(uint8_t j=0; j<8; j++){
      //Check if each bit is set i.e. 1
      if(oneByte & (128 >> j)){
        uint8_t k=0;
        //assign the next 8bytes to 0xAA
        while(k<8){
          transformed[index] = 0xAA;
          k++;
          index++;
        }
      }else{
        uint8_t k=0;
        //When bit is not set i.e. 0, set next 8bytes to 0x00
        while(k<8){
          transformed[index] = 0x00;
          k++;
          index++;
        }
      }
    }
  }
}


/*
 * sendOOKWakeup
 * Send wakeup pakect for WuRx
 * Takes in the pattern array
 * Return: Nothing
 */
 void sendOOKWakeup(uint8_t pattern1, uint8_t pattern2)
{
	OOKInit();
	uint8_t wakePattern[5];											// Wake pattern size 5
	uint8_t wakeTransformed[PAYLOAD_LENGTH];		// 320 byte data

	//5bytes Wakeup Signal (Manchester Disabled) == 40bits
  wakePattern[0] = 0xFF;        //8bits carrier
  wakePattern[1] = 0xFE;        //7bit carrier + 1 separation bit(0)
  wakePattern[2] = 0xAA;        //8bits Preamable(10101010)
  wakePattern[3] = pattern1;        //1st pattern byte (R6 on AS3932)
  wakePattern[4] = pattern2;        //2nd pattern byte (R5 on AS3932)

	//Transform each bit to 64 bits. i.e. a 256us bit == 4us x 64 == 8us x 32
  transformPattern(wakePattern, wakeTransformed);
	// Send OOK wakeup packet
	sendBulkOOKData(wakeTransformed, PAYLOAD_LENGTH);
}

/**
 * configureRadio. It takes 2.4ms
 * Configures the radio for use in TX or RX mode
 * Return: Nothing
 */
void configureRadio()
{
	// Radio configuration
	Init();
  SetDataRate(4); 			// Needs to be the same in Tx and Rx
  SetLogicalChannel(1); // Needs to be the same as receiver
	SetTxPower(1); 				// Set transmit power to 10 dBm (29.1 mA)
}

/**
 * configureRadioNode
 * Configure node radio for listening
 * Return: Nothing
 */
void configureRadioNode()
{
	P8DIR &= ~BIT2;		// Set radio_int pin as input
	if(P8IN & BIT2){// Confirm that radio is fully charged
		//WKUP_SPI_DRIVE_CSN_LOW();
		__delay_cycles(1);

		P8OUT |= BIT3;							// Turn on radio gate
		P8DIR |= BIT3;
		Init();
	  SetDataRate(4); 			// Needs to be the same in Tx and Rx
	  SetLogicalChannel(5); // Needs to be the same as receiver
		SetTxPower(1); 				// Set transmit power to 10 dBm (29.1 mA)
		RxOn();								// Stay in receive mode
	}
}

/**
 * sendNormalPkt
 * sends up to 61 bytes of packets
 * Takes in the array to be sent and the size
 * Return: Nothing
 */
void sendNormalPkt(uint8_t *tx_data, uint8_t size)
{
	Wakeup();				// Wake radio up from sleep
	__delay_cycles(1);
	SendData(tx_data, size);
	Sleep();				// Go to sleep
}


/**
 * sendNormalPktNode: Batteryless node version
 * sends up to 61 bytes of packets
 * Takes in the array to be sent and the size
 * Return: Nothing
 */
void sendNormalPktNode(uint8_t *tx_data, uint8_t size)
{
	P1DIR &= ~BIT2;								// Set radio_int pin as input
	if(P1IN & BIT2)
	{							// Confirm that radio is fully charged, takes at least 150ms
		//WKUP_SPI_DRIVE_CSN_LOW();		// Disable WuRx chip
		__delay_cycles(1);

		P1OUT |= BIT1;							// Turn on radio
		P1DIR |= BIT1;
		Init();
		SetDataRate(3); 			// Needs to be the same in Tx and Rx
		SetLogicalChannel(0); // Needs to be the same as receiver
		SetTxPower(1);				// 7 dBm 24.2 mA
		SendData(tx_data, size);
		P1OUT &= ~BIT1;		// Open radio's gate to cut power
		// // Set Radio SPI bus to input
		P1DIR &= ~BIT3;
		P1DIR &= ~BIT4;
		P1DIR &= ~BIT5;
		P1DIR &= ~BIT6;
		P1DIR &= ~BIT7;
		P2DIR &= ~BIT2;

		P1REN &= ~BIT3;
		P1REN &= ~BIT4;
		P1REN &= ~BIT5;
		P1REN &= ~BIT6;
		P1REN &= ~BIT7;
		P2REN &= ~BIT2;

		__delay_cycles(1);
	}
}


/****************************************************************
* readNormalPkt
* FUNCTION     :read packets into a buffer for a sensor node
* INPUT        :rx_data: data buffer, node_id: node identifier
* OUTPUT       :1 for success 0 if no data was received
****************************************************************/
uint8_t readNormalPkt(uint8_t * rx_data, uint8_t node_id)
{
	uint8_t rx_status = 0;

	rx_status = CheckReceiveFlag();
	if(rx_status){												//Check if we receive something
		ReceiveData(rx_data);
		if(rx_data[0] != node_id){				// Confirm node's address
			rx_status = 0;
		}
		RxOn();
	}

	return rx_status;
}


/****************************************************************
* readNormalPkt
* FUNCTION     :read packets into a buffer for a sensor node
* INPUT        :rx_data: data buffer, node_id: node identifier
* OUTPUT       :1 for success 0 if no data was received
****************************************************************/
uint8_t recieveNormalPktNode(uint8_t * rx_data)
{
	uint8_t rx_status = 0;

	P8DIR &= ~BIT2;								// Set radio_int pin as input
	if(P8IN & BIT2)								// Confirm that radio is fully charged, takes at least 150ms
	{
		//WKUP_SPI_DRIVE_CSN_LOW();		// Disable WuRx chip
		__delay_cycles(1);

		P8OUT |= BIT3;							// Turn on radio
		P8DIR |= BIT3;
		Init();
		SetDataRate(4); 			// Needs to be the same in Tx and Rx
		SetLogicalChannel(5); // Needs to be the same as receiver
		SetTxPower(1);				// 7 dBm 24.2 mA
		RxOn();

		rx_status = CheckReceiveFlag();
		if(rx_status){												//Check if we receive something
			led_toggle();
			ReceiveData(rx_data);
		}
		// led_toggle();

		P8OUT &= ~BIT3;		// Open radio's gate to cut power

		P5DIR &= ~BIT0;		// Set Radio SPI bus to input
		P5DIR &= ~BIT1;
		P5DIR &= ~BIT2;
		P4DIR &= ~BIT3;
		P3DIR &= ~BIT4;
		P3DIR &= ~BIT6;

		P5REN &= ~BIT0;
		P5REN &= ~BIT1;
		P5REN &= ~BIT2;
		P4REN &= ~BIT3;
		P3REN &= ~BIT4;
		P3REN &= ~BIT6;

		__delay_cycles(1);
		//WKUP_SPI_DRIVE_CSN_HIGH();		// Enable WuRx chip
	}

	return rx_status;
}



void led_init()
{
	P1OUT &= ~BIT0;
	P1DIR |= BIT0;
	P5OUT &= ~BIT7;
	P5DIR |= BIT7;
}

void led_on()
{
	P1OUT |= BIT0;
	P5OUT |= BIT7;
}

void led_off()
{
	P1OUT &= ~BIT0;
	P5OUT &= ~BIT7;
}

void led_toggle()
{
	P1OUT ^= BIT0;
	P5OUT ^= BIT7;
}

/****************************************************************
* initial_pin_setup
* FUNCTION     :Port Configuration, output pull-down
* INPUT        :none
* OUTPUT       :none
****************************************************************/
void initial_pin_setup()
{
	//
  P1OUT = 0x00;
  P1DIR = 0x00;
	P1REN = 0xff;

  P2OUT = 0x00;
  P2DIR = 0x00;
	P2REN = 0xff;

  P3OUT = 0x00;
  P3DIR = 0x00;
	P3REN = 0xff;

  P4OUT = 0x00;
  P4DIR = 0x00;
	P4REN = 0xff;

  PJOUT = 0x00;
  PJDIR = 0x00;
	PJREN = 0xff;

// Radio Port Setup - Radio_UFOP_Int P1.2
  P1DIR &= ~BIT2;

  P1DIR |= BIT1; //gate

  P6DIR |= ( BIT1 + BIT3 + BIT5);     // 1.3: GDO0 | 1.1: Radio Gate | 1.5: Radio CSN
  //P1OUT |= BIT3;                            // Set GDO0
  P1OUT &= ~BIT1; 
}

/****************************************************************
* ConfigureMCUSpeed
* FUNCTION     :ACLK = LFXT1 = 32kHz, MCLK = SMCLK = 8MHz
* INPUT        :none
* OUTPUT       :none
****************************************************************/
void ConfigureMCUSpeed()
{
  //   ACLK = LFXT1 = 32kHz, MCLK = SMCLK = 8MHz
  PJSEL0 = BIT4 | BIT5;                     // For XT1

  // Clock System Setup
  CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers
  CSCTL1 = DCOFSEL_6;                       // Set DCO to 8MHz
  CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK; // ACLK = LFXT (32KHz), SMCLK = MCLK = DCO (8MHz)
  CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers
  CSCTL4 &= ~LFXTOFF;                       // Turn LFXT ON
  do
  {
    CSCTL5 &= ~LFXTOFFG;                    // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG;
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
  // Now that osc is running enable fault interrupt
  SFRIE1 |= OFIE;

  CSCTL0_H = 0;                        // Lock CS registers
}

void setGDO0Interrupt()
{
	P3REN |= BIT4;          // Enable internal pull-up/down resistors
  P3OUT |= BIT4;          // Select pull-up mode for P3.4
  P3IE |= BIT4;           // P3.4 interrupt enabled
  P3IES |= BIT4;          // P3.4 Hi/Lo edge
  P3IFG &= ~BIT4;         // P3.4 IFG cleared

	// __bis_SR_register(LPM3_bits+GIE);		// Goto sleep until packet is received
}
