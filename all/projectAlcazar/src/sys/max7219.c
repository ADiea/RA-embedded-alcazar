/* STM32f0discovery embedded essentials course project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <max7219.h>
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
	setDecodeMode(eDecode_allCharactersInternalFont);
	clearDisplay();

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
void setDecodeMode(eDisaplayDecodeMode decodeMode)
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
