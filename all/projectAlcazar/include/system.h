/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery/]


For understanding the following declarations
Please see the document [STM32F051C8 Datasheet.pdf] section 3.7 
					and	[STM32F0 Reference Manual.pdf] sections 
					section 2.2.2, table, bus AHB1 => 0x40021000  RCC
					section 6.4.6 RCC_AHBENR note the offset from the RCC base which is 0x14
*/
#ifndef SYSTEM__H
#define SYSTEM__H

#define RCC_BASE 		0x40021000
//See 6.4 in reference manual
#define RCC_AHBENR_OFFSET 	0x14
#define RCC_APB2ENR_OFFSET 	0x18

//This macrodefinition means that we take the base address we add the offset and the resulting address we cast to a pointer to a unsigned int
//We return the dereferenced opinter to that address so that we can assign values to it
//Think of it as 
//	unsigned int *pRCC_AHBENR = (0x40021000 + 0x14); 
//	Now instead of writing to that adress always as *pRCC_AHBENR = value, we define a RCC_AHBENR to be #define RCC_AHBENR (*pRCC_AHBENR) 
//	so we can write in code directly RCC_AHBENR = value 
#define RCC_AHBENR (*((volatile unsigned int *)( RCC_BASE + RCC_AHBENR_OFFSET )))

#define RCC_APB2ENR (*((volatile unsigned int *)( RCC_BASE + RCC_APB2ENR_OFFSET )))


//In section 6.4.6 you see what bit controls which peripheral
//In section 6.4.7 you see what bit controls which peripheral
//Enumerate all used peripherals
typedef enum
{
	//These are bits from the RCC_AHBENR register!
	ePerif_GPIOA = 17,
	ePerif_GPIOB = 18,
	ePerif_GPIOC = 19,
	ePerif_GPIOD = 20,
	ePerif_GPIOE = 21,
	ePerif_GPIOF = 22,

	//These are bits from the RCC_APB2RSTR register!
	ePerif_TIM1 = 11,
	ePerif_TIM15 = 16,
	ePerif_SPI1EN = 12,


} ePeripherals;

//define enable/disable values
typedef enum
{
	eDisabled,
	eEnabled
} eEnableState;

//Enable a specific peripheral
void enablePeripheral(ePeripherals peripheral, eEnableState enable);

#endif // SYSTEM__H //
