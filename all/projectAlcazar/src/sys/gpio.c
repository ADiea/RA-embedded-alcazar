/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <gpio.h>

/*
 * Sets the pin Pull-up Pull-Down
 */
void setPUPD(GPIO_Type * port, unsigned int pinNumber, ePUPDType PinPUPD)
{
	port->PUPDR |= PinPUPD << (2*pinNumber);
}

/*
 * Sets the pin "pinNumber" of port "port" mode
 * */
void setPinMode(GPIO_Type * port, unsigned int pinNumber, ePinMode pinMode)
{
	//TODO: write function
	port->MODER |= pinMode << (2*pinNumber);
}

/*
 * Writes 1/0 to the corresponding pinNumber of port "port"
 * */
void writePin(GPIO_Type * port, unsigned int pinNumber, unsigned int value)
{
	port->ODR &= ~(1UL << pinNumber); //clear the bit
	port->ODR |= value << pinNumber;  // set the bit
}

/*
 * Returns 1 if pin "pinNumber" in port "port" is set and 0 if the pin is not set
 * */
unsigned int readPin(GPIO_Type * port, unsigned int pinNumber)
{
	if(!port || pinNumber > 15)
		return 0;

	unsigned int pinValue = 0;

	if(port->IDR & 1<<pinNumber)
	{
		pinValue = 1;
	}

	return pinValue;
}
