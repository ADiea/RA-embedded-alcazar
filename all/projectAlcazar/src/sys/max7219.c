/* STM32f0discovery embedded essentials course project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <max7219.h>
#include <max7219_font.h>
#include <delay.h>
#include <gpio.h>

#define USE_SOFT_SPI 1

#if !USE_SOFT_SPI
//this is a global variable
volatile SPI_Type* gDisplaySPI;
#endif

//initializes the display
void initMAX7219Display(volatile SPI_Type* spiToBeUsed)
{

#if !USE_SOFT_SPI
	if(!spiToBeUsed)
		return;
	gDisplaySPI = spiToBeUsed;
#endif

	//send commands to setup the display the way we want
	setIntensity(MAX7219_MAX_INTENSITY);
	setScanLimit(7);// display all 8 digits

	//set decode mode for using internal font
	setDecodeMode(eDecode_allCharactersInternalFont);
	clearDisplay();

	//set decode mode for using custom font
	//setDecodeMode(eDecode_allCharactersCustomFont);
	//clearDisplayCustomFont();

	//enable the display
	enableDisplay(eDisplay_Enabled);
}

//sends data to a specific address, this is the essential part
//please see the max7219 datasheet page 5 to see how data and
//address are sent as successive bytes
void sendMAX7219Data(unsigned char registerAddress, unsigned char data)
{
#if !USE_SOFT_SPI
	//enable the slave
	GPIOA->ODR &= ~(1<<4);
#else
	spiSoftEnableSlave(1);
#endif

#if !USE_SOFT_SPI
	//First we send the address coded in the lsb nibble of the byte
	sendSPIByte(gDisplaySPI, registerAddress);

	//Next we send the user data
	sendSPIByte(gDisplaySPI, data);
#else
	//First we send the address coded in the lsb nibble of the byte
	spiSoftSendByte(registerAddress);

	//Next we send the user data
	spiSoftSendByte(data);
#endif

#if !USE_SOFT_SPI
	//disable the slave
	GPIOA->ODR |= (1<<4);
#else
	spiSoftEnableSlave(0);
#endif

}

//displays character ch to the pos position
void putChar(char ch, unsigned char pos)
{
	//we send the ch character to the corresponding register
	if(pos <= 7)
	{
		sendMAX7219Data(MAX7219_REG_POS_0 + pos, ch);
	}
}

//important: set decode mode to eDecode_allCharactersCustomFont before using this function
//displays string stringDisplayed with length of stringLen
void putString(char stringDisplayed[], unsigned int stringLen)
{
	int i, j, string_pos;
	for (string_pos = 0; string_pos < stringLen; string_pos++) // for a whole pass of the string
	{
		busyDelayMs(750); //delay before sending each char
		putChar(MAX7219_font[stringDisplayed[string_pos]-32], 0); //send each char to first position of display

		for (i=string_pos-1, j=1; i>=0 && j<=7; i--, j++) //update display with previous sent characters from string
		{
			putChar(MAX7219_font[stringDisplayed[i]-32], j);
		}
	}
	busyDelayMs(1000); //delay before clear
	clearDisplayCustomFont(); //clear the display
}

//sets the intensity from 0 to 15
void setIntensity(unsigned char intensity)
{
	sendMAX7219Data(MAX7219_REG_INTENSITY, intensity);
}

//enable or disable the display. This can also be used for blinking
void enableDisplay(eEnableDisplay enable)
{
	sendMAX7219Data(MAX7219_REG_SHUTDOWN, (unsigned char)enable);
}

//sets the number of characters
void setScanLimit(unsigned char numCharacters)
{
	sendMAX7219Data(MAX7219_REG_SCANLIMIT, numCharacters);
}

//sets the way the chip decodes the characters.
//We can create a custom font for it or use the internal font. See the datasheet
void setDecodeMode(eDisplayDecodeMode decodeMode)
{
	sendMAX7219Data(MAX7219_REG_DECODEMODE, (unsigned char)decodeMode);
}

//clear the display by showing only blank characters
void clearDisplay(void)
{
	putChar(MAX7219_BLANK, 0);
	putChar(MAX7219_BLANK, 1);
	putChar(MAX7219_BLANK, 2);
	putChar(MAX7219_BLANK, 3);
	putChar(MAX7219_BLANK, 4);
	putChar(MAX7219_BLANK, 5);
	putChar(MAX7219_BLANK, 6);
	putChar(MAX7219_BLANK, 7);
}

//clear the display in custom font decode mode
//by setting all bits to 0
void clearDisplayCustomFont(void)
{
	putChar(0, 0);
	putChar(0, 1);
	putChar(0, 2);
	putChar(0, 3);
	putChar(0, 4);
	putChar(0, 5);
	putChar(0, 6);
	putChar(0, 7);
}
