/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

//This file contains soft SPI related function declarations

#ifndef SPISOFT_H_
#define SPISOFT_H_

#include <gpio.h>

/*
 * Setsup GPIO pins fopr a software SPI
 * */
void spiSoftSetup(volatile GPIO_Type * port,
				  unsigned char pinSS,   //slave select pin
				  unsigned char pinSCK,  //clock signal pin
				  unsigned char pinMOSI, //master out slave in pin
				  unsigned char pinMISO //master in slave out pin
				  );
//Before 'talking' to the slave we must enable it by pulling the SS line low
void spiSoftEnableSlave(unsigned char enable);
//send a byte to the slave using the SPI in software (known also as bit banging)
void spiSoftSendByte(unsigned char byte);


#endif /* SPISOFT_H_ */
