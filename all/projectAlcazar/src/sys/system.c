/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <system.h>

//declare the extern projectInit() function. Will be called after system is init
extern void projectInit();

void enablePeripheralRCC_AHBENR(ePeripheralsRCC_AHBENR peripheral, eEnableState enable)
{
	volatile unsigned int *pRCCRegister;

	if(	ePerif_GPIOA == peripheral || ePerif_GPIOB == peripheral ||
		ePerif_GPIOC == peripheral || ePerif_GPIOD == peripheral ||
		ePerif_GPIOE == peripheral || ePerif_GPIOF == peripheral )
	{
		pRCCRegister = &RCC_AHBENR;
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


void enablePeripheralRCC_APB1ENR(ePeripheralsRCC_APB1ENR peripheral, eEnableState enable)
{
	volatile unsigned int *pRCCRegister2;

	if(ePerif_USART2EN == peripheral)
	{
		pRCCRegister2 = &RCC_APB1ENR;
	}
	else if(ePerif_TIM3EN == peripheral)
	{
		pRCCRegister2 = &RCC_APB1ENR;
	}

	if(enable == eEnabled)
	{
		*pRCCRegister2 |= 1 << peripheral;
	}
	else
	{
		*pRCCRegister2 &= ~(1 << peripheral);
	}
}


void enablePeripheralRCC_APB2ENR(ePeripheralsRCC_APB2ENR peripheral, eEnableState enable)
{
	volatile unsigned int *pRCCRegister3;

	if(ePerif_TIM1 == peripheral)
	{
		pRCCRegister3 = &RCC_APB1ENR;
	}
	else if(ePerif_SPI1EN == peripheral)
	{
		pRCCRegister3 = &RCC_APB1ENR;
	}
	else if(ePerif_TIM15 == peripheral)
	{
		pRCCRegister3 = &RCC_APB1ENR;
	}

	if(enable == eEnabled)
	{
		*pRCCRegister3 |= 1 << peripheral;
	}
	else
	{
		*pRCCRegister3 &= ~(1 << peripheral);
	}
}


//rename function to main so the debugger sets the breakpoint correctly
void main()
{
	//init the system

	//after system is inited, call the projectInit 
	projectInit();
}
