/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <gpio.h>

/*
 * Sets the pin "pinNumber" of port "port" mode
 * */
void setPinMode(volatile GPIO_Type * port, unsigned int pinNumber, ePinMode pinMode)
{
	if (!port || pinNumber > 15)
		return;

	port->MODER |= pinMode << MODERPOS(pinNumber);
}

/*
 * Writes 1/0 to the corresponding pinNumber of port "port"
 * */
void writePin(volatile GPIO_Type * port, unsigned int pinNumber, unsigned int value)
{
	if (!port || pinNumber > 15)
		return;

	if (value)
	{
		port->ODR |= (1<<pinNumber);
	}
	else
	{
		port->ODR &= ~(1<<pinNumber);
	}
}

/*
 * Returns 1 if pin "pinNumber" in port "port" is set and 0 if the pin is not set
 * */
unsigned int readPin(volatile GPIO_Type * port, unsigned int pinNumber)
{
	if(!port || pinNumber > 15)
		return 0;

	unsigned int pinValue = 0;

	if(port->IDR & (1<<pinNumber))
	{
		pinValue = 1;
	}

	return pinValue;
}

/*
 * Sets the pin "pinNumber" of port "port" alternate function "pinFunction"
 * For corresponding alternate function number to actual function see chapters
 * Table 14 & Table 15 in [STM32F051C8_Datasheet] -
 * 	Alternate functions selected through GPIOx_AFR registers
 * */
void setPinAlternateFunction(volatile GPIO_Type * port, unsigned int pinNumber, ePinAlternateFunc pinFunction)
{
	if(!port || pinNumber > 15)
		return;

	//First configure MODER register for this pin as alternate function
	//	clear mode bits corresponding to this pin
	port->MODER &= ~(0x3 << MODERPOS(pinNumber));
	//  set mode bits to alternate function mode
	port->MODER |=  (ePin_AlternateFunction << MODERPOS(pinNumber));

	//Next set the desired alternate function
	//address of needed Alternate Function register (will be decided based on pin number)
	//See 8.4.9 & 8.4.10 in reference manual
	volatile unsigned int* pAFRegister;

	if(pinNumber <= 7)
	{
		//pins 0-7 are controlled by AFRL (low)
		pAFRegister = &(port->AFRL);
	}
	else
	{
		//subtract 8 from pin number to make pin 8 become 0
		//in order to index correctly into AFRH
		pinNumber -= 8;
		//pins 8-15 by AFRH (high)
		pAFRegister = &(port->AFRH);
	}

	//TODO set breakpoint here to see pAFRegister value which is the needed AF register address

	//multiply pin by 4 to compute position in register
	//see 8.4.9 & 8.4.10 in reference manual
	pinNumber <<= 2;

	//first clear the 4 bits to clear any previous AF setting
	*pAFRegister &= ~(0xF << pinNumber);

	//set the current AF setting
	*pAFRegister |= (pinFunction << pinNumber);
}
