#ifndef CC1101_h
#define CC1101_h

#include <stdint.h>
#include <msp430fr5994.h>
#include "macros.h"
#include "registers.h"
#include "pins.h"


/* Helper functions */
#define SPI_TURN_CHIP_SELECT_ON()        SPI_DRIVE_CSN_LOW()
#define SPI_TURN_CHIP_SELECT_OFF()       SPI_DRIVE_CSN_HIGH()
#define SPI_CHIP_SELECT_IS_OFF()         SPI_CSN_IS_HIGH()

/* Radio States */
#define RADIO_STATE_UNKNOWN  0
#define RADIO_STATE_OFF      1
#define RADIO_STATE_IDLE     2
#define RADIO_STATE_RX       3

void SpiInit(void);
uint8_t SpiTransfer(uint8_t value);
void GDO_Set (void);
void RadioReset (void);
void SpiWriteReg(uint8_t addr, uint8_t value);
void SpiWriteBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num);
uint8_t SpiStrobe(uint8_t strobe);
uint8_t SpiReadReg(uint8_t addr);
void SpiReadBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num);
uint8_t SpiReadStatus(uint8_t addr);
void RegConfigSettings(void);
void RadioRxModeOff(void);
uint8_t SpiReadStatusReg(uint8_t addr);

void RadioInit(void);
void RadioRxOn(void);
void RadioIdle(void);
void RadioSleep(void);
void RadioWakeup(void);
void RadioSendData(uint8_t *txBuffer, uint8_t size);
void RadioSendDataNoWait(uint8_t *txBuffer, uint8_t size);
void RadioSetDataRate(uint8_t rate_ndx);
void RadioSetTxPower(uint8_t powrset_ndx);
void RadioSetLogicalChannel(uint8_t channel);
void RadioSetMaxPacketLength(uint8_t pkt_length);
uint8_t RadioGetMARCState();
uint8_t RadioCheckReceiveFlag(void);
uint8_t RadioReceiveData(uint8_t *rxBuffer);
uint8_t RadioGetState(void);
int8_t RadioRssi(void);

#endif
