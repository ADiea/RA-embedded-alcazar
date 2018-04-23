/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <spi.h>

//Inits a SPI peripheral in master mode
/*
 * We will use SPI master mode which means that MCU controls the SPI clock so
 * the MCU controls the communication(hence MCU is master)
 * The other device is called slave.
 * */
void initSPIMaster(volatile SPI_Type* spi)
{
	//Based on A.17.1 SPI master configuration code example

	/* (1) Master selection, BR: Fpclk/256
	 *  CPOL and CPHA at zero (rising first edge) */
	/* (2) Slave select output enabled, 8-bit Rx fifo */
	/* (3) Enable SPI1 */

	spi->CR1.bit.MSTR = 1;
	spi->CR1.bit.BR = 1;
	spi->CR1.reg = 1<<9; /* (1) */

	spi->CR2.bit.DS = 0x7;
	spi->CR2.bit.SSOE = 1;

	spi->CR1.bit.SPE = 1; /* (3) */
}

//send a byte to the slave using the SPI
//based on A.17.3 SPI full duplex communication code example
void sendSPIByte(volatile SPI_Type* spi, unsigned char byte)
{
	while (!spi->SR.bit.TXE) /* Wait for Tx empty */
	{
		;
	}

	/* Will inititiate 8-bit transmission if TXE */
	*(unsigned char *)&(spi->DR.reg) = byte;
}
