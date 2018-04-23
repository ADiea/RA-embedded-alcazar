/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <system.h>

//declare the extern projectInit() function. Will be called after system is init
extern void projectInit();

void enableAHBPeripheral(eAHBPeripherals peripheral, eEnableState enable)
{
	if (enable == eEnabled)
	{
		RCC->AHBENR.reg |= 1 << peripheral;
	}
	else
	{
		RCC->AHBENR.reg &= ~(1 << peripheral);
	}
}

void enableAPB1Peripheral(eAPB1Peripherals peripheral, eEnableState enable)
{
	if (enable == eEnabled)
	{
		RCC->APB1ENR.reg |= 1 << peripheral;
	}
	else
	{
		RCC->APB1ENR.reg &= ~(1 << peripheral);
	}
}

void enableAPB2Peripheral(eAPB2Peripherals peripheral, eEnableState enable)
{
	if (enable == eEnabled)
	{
		RCC->APB2ENR.reg |= 1 << peripheral;
	}
	else
	{
		RCC->APB2ENR.reg &= ~(1 << peripheral);
	}
}


//rename function to main so the debugger sets the breakpoint correctly
void main()
{
	//init the system
	int a = 0xFF00FF00;
	//after system is inited, call the projectInit 
	projectInit();
}
