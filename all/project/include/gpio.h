/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery/]

For understanding the following declarations
Please see the document [STM32F051C8 Datasheet.pdf] section 3.7 
					and	[STM32F0 Reference Manual.pdf] sections 
					section 2.2.2, table, bus AHB1 => 0x40021000  RCC
					section 6.4.6 RCC_AHBENR note the offset from the RCC base which is 0x14
*/

//The base of the GPIO_C register. Note the C in the GPIOC_BASE it comes from the periferal C, where we have our LED
//See section 2.2.2 or search for GPIOC
#define GPIOC_BASE 0x48000800
//Offset of the GPIOx_MODER register relative to the GPIOx_BASE. 
//All port registers A to F are the same distance/offset from their coresponding base 
#define GPIOx_MODER_OFFSET 0x0
//Offset of the GPIOx_ODR register relative to the GPIOx_BASE. 
//All port registers A to F are the same distance/offset from their coresponding base 
#define GPIOx_ODR_OFFSET 0x14

//see section 8.1
/* From the documentation:
Each general-purpose I/O port has four 32-bit configuration registers (GPIOx_MODER,
GPIOx_OTYPER, GPIOx_OSPEEDR and GPIOx_PUPDR), two 32-bit data registers
(GPIOx_IDR and GPIOx_ODR) and a 32-bit set/reset register (GPIOx_BSRR). 

GPIOx_MODER register is used to select the I/O mode (input, output, AF, analog). The
GPIOx_OTYPER and GPIOx_OSPEEDR registers are used to select the output type (pushpull or open-drain) and speed. The GPIOx_PUPDR register is used to select the pull-
up/pull-down whatever the I/O direction.

*/
//This port controls the pin mode see 8.4
#define GPIOC_MODER (*((volatile unsigned int *)( GPIOC_BASE + GPIOx_MODER_OFFSET )))

//See 8.4.1
/*
00: Input mode (reset state)
01: General purpose output mode
10: Alternate function mode
11: Analog mode
*/
#define PORT_MODE_INPUT 0x0
#define PORT_MODE_OUTPUT 0x1
#define PORT_MODE_ALTERNATE 0x2
#define PORT_MODE_ANALOG 0x3

//Offset of the mode setting for pin x in the GPIOx_MODER register
#define MODERx(x) ((x)<<1)

//This port controls the output value of its pins see 8.4.6
#define GPIOC_ODR (*((volatile unsigned int *)( GPIOC_BASE + GPIOx_ODR_OFFSET )))


