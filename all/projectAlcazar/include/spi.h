/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

//This file contains SPI related function declarations

#ifndef SPI_H
#define SPI_H

//see 2.2.2 in reference manual
#define SPI1_BASE 0x40013000

//Chapter 28 in the reference manual deals with SPI. Please study it

//organize all spi registers in a struct to make is easier to use them
typedef struct
{
	unsigned int CR1;//Offset 0x00:  28.9.1 SPI control register 1 (SPIx_CR1)
	unsigned int CR2;// 28.9.2 SPI control register 2 (SPIx_CR2)
	unsigned int SR;//28.9.3 SPI status register (SPIx_SR)
	unsigned int DR;//28.9.4 SPI data register (SPIx_DR)
	unsigned int CRCPR;//28.9.5 SPI CRC polynomial register (SPIx_CRCPR)
	unsigned int RXCRCR;//28.9.6 SPI Rx CRC register (SPIx_RXCRCR)
	unsigned int TXCRCR;//28.9.7 SPI Tx CRC register (SPIx_TXCRCR)
	unsigned int I2SCFGR;//28.9.8 SPIx_I2S configuration register (SPIx_I2SCFGR)
	unsigned int I2SPR;//28.9.9 SPIx_I2S prescaler register (SPIx_I2SPR)
}SPI_Type;

#define SPI1 ((volatile SPI_Type*)SPI1_BASE)

//You will notice that we no longer use bit place defines but rather incorporate the "1<<"
//with the definition. This way we already create the bitmask
//and the final code is easier to read

//Syntax is SPI_Registername_bit
//you can find more or doublecheck by reading the ref manual Registername
#define SPI_CR1_MSTR (1<<2) //already shift here to make code easier to write
#define SPI_CR1_BR (0x7<<3) //set lowest possible baudrate
#define SPI_CR1_SPE (1<<6)

#define SPI_CR2_DS 8 //bit from which DATA size starts
#define SPI_CR2_SSOE (1<<2)

#define SPI_SR_TXE (1<<1) //tx buffer empty
#define SPI_SR_BSY (1<<7)//SPI busy (communication in progress)

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
