/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <system.h>

//declare the extern projectInit() function. Will be called after system is init
extern void projectInit();

void enablePeripheral(ePeripherals peripheral, eEnableState enable)
{
	volatile unsigned int *pRCCRegister;

	if(	ePerif_GPIOA == peripheral || ePerif_GPIOB == peripheral ||
		ePerif_GPIOC == peripheral || ePerif_GPIOD == peripheral ||
		ePerif_GPIOE == peripheral || ePerif_GPIOF == peripheral )
	{
		pRCCRegister = &RCC_AHBENR;
	}
	else if(ePerif_TIM1 == peripheral || ePerif_TIM15 == peripheral ||
			ePerif_SPI1EN == peripheral)
	{
		pRCCRegister = &RCC_APB2ENR;
	}
	
	if(enable == eEnabled)
	{
		*pRCCRegister |= 1 << peripheral;
	}
	else
	{
		*pRCCRegister &= ~(1 << peripheral);
	}
}

//rename function to main so the debugger sets the breakpoint correctly
void main()
{
	//init the system

	//after system is inited, call the projectInit 
	projectInit();
}
