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
#define IOPF 22
#define IOPE 21
#define IOPD 20
#define IOPC 19
#define IOPB 18
#define IOPA 17

//In section 6.4.7 you see what bit controls which peripheral
#define TIM1EN 11

//Enumerate all used peripferals
typedef enum
{
	ePerif_GPIOA,
	ePerif_GPIOB,
	ePerif_GPIOC,
	ePerif_GPIOD,
	ePerif_GPIOE,
	ePerif_GPIOF,
	ePerif_TIM1,
} ePeripherals;

//define enable/disable values
typedef enum
{
	eDisabled,
	eEnabled
} eEnableState;

//Enable a specific peripheral
void enablePeriferal(ePeripherals which, eEnableState enable);

#endif // SYSTEM__H //
