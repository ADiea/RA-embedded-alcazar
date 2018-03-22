/* STM32f0discovery embedded essentials course project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]

 partly based on https://github.com/nickgammon/MAX7219

*/

//This file contains defines for using the MAX7219 device

#ifndef MAX7219_H
#define MAX7219_H

#include <spi.h>
#include <spisoft.h>


#define MAX7219_REG_NOOP 			0x0
#define MAX7219_REG_POS_0 			0x1 // codes 1 to 8 are digit positions 1 to 8
#define MAX7219_REG_DECODEMODE  	0x9
#define MAX7219_REG_INTENSITY   	0xA
#define MAX7219_REG_SCANLIMIT   	0xB
#define MAX7219_REG_SHUTDOWN    	0xC
#define MAX7219_REG_DISPLAYTEST 	0xF

typedef enum
{
	eDisplay_Disabled = 0,
	eDisplay_Enabled = 1,
} eEnableDisplay;

typedef enum
{
	eDecode_allCharactersInternalFont = 0xff,
	eDecode_allCharactersCustomFont = 0x00
}eDisaplayDecodeMode;

#define MAX7219_BLANK 0xF //this is the blank(space) character fro internally decoded font

#define MAX7219_MAX_INTENSITY 0xF //this is the max intensity

//initializes the display
void initMAX7219Display(volatile SPI_Type* spiToBeUsed);

//sends data to a specific address, this is the essential part
//please see the max7219 datasheet page 5 to see how data and
//address are sent as successive bytes
void sendsendMAX7219DataData(unsigned char registerAddress, unsigned char data);

//displays character ch to the pos position
void putChar(char ch, unsigned char pos);

//sets the intensity from 0 to 15
void setIntensity(unsigned char intensity);

//enable or disable the display. This can also be used for blinking
void enableDisplay(eEnableDisplay enable);

//sets the number of characters
void setScanLimit(unsigned char numCharacters);

//sets the way the chip decodes the characters.
//We can create a custom font for it or use the internal font. See the datasheet
void setDecodeMode(eDisaplayDecodeMode decodeMode);

//clear the display by showing only blank characters
void clearDisplay(void);

#endif /*MAX7219_H*/
