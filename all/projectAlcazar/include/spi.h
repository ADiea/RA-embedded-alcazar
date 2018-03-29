/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

//This file contains SPI related function declarations

#ifndef SPI_H
#define SPI_H

#include <board.h>

//see 2.2.2 in reference manual
#define SPI1_BASE 0x40013000
#define SPI2_BASE 0x40003800

//Chapter 28 in the reference manual deals with SPI. Please study it


//28.9.1 SPI control register 1 (SPIx_CR1)
typedef union {
	struct {
		uint32_t CPHA:1;
		uint32_t CPOL:1;
		uint32_t MSTR:1;
		uint32_t BR:3;
		uint32_t SPE:1;
		uint32_t LSBFIRST:1;
		uint32_t SSI:1;
		uint32_t SSM:1;
		uint32_t RXONLY:1;
		uint32_t CRCL:1;
		uint32_t CRCNEXT:1;
		uint32_t CRCEN:1;
		uint32_t BIDIOE:1;
		uint32_t BIDIMODE:1;
		uint32_t :16;
	} bit;
	uint32_t reg;
} SPIx_CR1;

//SPI control register 2 (SPIx_CR2)
typedef union {
	struct {
		uint32_t RXDMAEN:1;
		uint32_t TXDMAEN:1;
		uint32_t SSOE:1;
		uint32_t NSSP:1;
		uint32_t FRF:1;
		uint32_t ERRIE:1;
		uint32_t RXNEIE:1;
		uint32_t TXEIE:1;
		uint32_t DS:4;
		uint32_t FRXTH:1;
		uint32_t LDMA_RX:1;
		uint32_t LDMA_TX:1;
		uint32_t :17;
	} bit;
	uint32_t reg;
} SPIx_CR2;

//28.9.3 SPI status register (SPIx_SR)
typedef union {
	struct {
		uint32_t RXNE:1;
		uint32_t TXE:1;
		uint32_t CHSIDE:1;
		uint32_t UDR:1;
		uint32_t CRCERR:1;
		uint32_t MODF:1;
		uint32_t OVR:1;
		uint32_t BSY:1;
		uint32_t FRE:1;
		uint32_t FRLVL:2;
		uint32_t FTLVL:2;
		uint32_t :19;
	} bit;
	uint32_t reg;
} SPIx_SR;

//28.9.4 SPI data register (SPIx_DR)
typedef union {
	struct {
		uint32_t DR:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} SPIx_DR;

//28.9.5 SPI CRC polynomial register (SPIx_CRCPR)
typedef union {
	struct {
		uint32_t CRCPOLY:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} SPIx_CRCPR;

//28.9.6 SPI Rx CRC register (SPIx_RXCRCR)
typedef union {
	struct {
		uint32_t RxCRC:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} SPIx_RXCRCR;

//28.9.7 SPI Tx CRC register (SPIx_TXCRCR)
typedef union {
	struct {
		uint32_t TxCRC:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} SPIx_TXCRCR;

//28.9.8 SPIx_I2S configuration register (SPIx_I2SCFGR)
typedef union {
	struct {
		uint32_t CHLEN:1;
		uint32_t DATLEN:2;
		uint32_t CKPOL:1;
		uint32_t I2SSTD:2;
		uint32_t :1;
		uint32_t PCMSYNC:1;
		uint32_t I2SCFG:2;
		uint32_t I2SE:1;
		uint32_t I2SMOD:1;
		uint32_t :20;
	} bit;
	uint32_t reg;
} SPIx_I2SCFGR;

//28.9.9 SPIx_I2S prescaler register (SPIx_I2SPR)
typedef union {
	struct {
		uint32_t I2SDIV:8;
		uint32_t ODD:1;
		uint32_t MCKOE:1;
		uint32_t :22;
	} bit;
	uint32_t reg;
} SPIx_I2SPR;


//organize all spi registers in a struct to make is easier to use them
typedef struct
{
	SPIx_CR1     CR1;//Offset 0x00:  28.9.1 SPI control register 1 (SPIx_CR1)
	SPIx_CR2     CR2;// 28.9.2 SPI control register 2 (SPIx_CR2)
	SPIx_SR      SR;//28.9.3 SPI status register (SPIx_SR)
	SPIx_DR      DR;//28.9.4 SPI data register (SPIx_DR)
	SPIx_CRCPR   CRCPR;//28.9.5 SPI CRC polynomial register (SPIx_CRCPR)
	SPIx_RXCRCR  RXCRCR;//28.9.6 SPI Rx CRC register (SPIx_RXCRCR)
	SPIx_TXCRCR  TXCRCR;//28.9.7 SPI Tx CRC register (SPIx_TXCRCR)
	SPIx_I2SCFGR I2SCFGR;//28.9.8 SPIx_I2S configuration register (SPIx_I2SCFGR)
	SPIx_I2SPR   I2SPR;//28.9.9 SPIx_I2S prescaler register (SPIx_I2SPR)
}SPI_Type;

#define SPI1 ((volatile SPI_Type*)SPI1_BASE)
#define SPI2 ((volatile SPI_Type*)SPI2_BASE)

//Inits a SPI peripheral in master mode
/*
 * We will use SPI master mode which means that MCU controls the SPI clock so
 * the MCU controls the communication(hence MCU is master)
 * The other device is called slave.
 * */
void initSPIMaster(volatile SPI_Type* spi);

//send a byte to the slave using the SPI
void sendSPIByte(volatile SPI_Type* spi, unsigned char byte);

#endif //SPI_H
