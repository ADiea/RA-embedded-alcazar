/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery/blinky.html]
 Flashes the blue LED on the STM32F0Disovery board 

The application's task is to blink the blue led. By looking in the [STM32F0Discovery Board User Manual.pdf] document
we see that the Blue LED is connected to the PC8 pin this is (PORTC C, PIN 8)
In order to blink the led we have to do the following
1. enable the PORTC clock so that the portC subsystem will operate
2. configure pin 8 from portC as an output
3. turn on the LED. Wait a certain amount of time. Turn off the LED. wait a certain amount of time and repeat

For understanding the following declarations
Please see the document [STM32F051C8 Datasheet.pdf] section 3.7 
					and	[STM32F0 Reference Manual.pdf] sections 
					section 2.2.2, table, bus AHB1 => 0x40021000  RCC
					section 6.4.6 RCC_AHBENR note the offset from the RCC base which is 0x14
*/

#define RCC_BASE 			0x40021000
#define RCC_AHBENR_OFFSET 	0x14

//This macrodefinition means that we take the base address we add the offset and the resulting address we cast to a pointer to a unsigned int
//We return the dereferenced opinter to that address so that we can assign values to it
//Think of it as 
//	unsigned int *pRCC_AHBENR = (0x40021000 + 0x14); 
//	Now instead of writing to that adress always as *pRCC_AHBENR = value, we define a RCC_AHBENR to be #define RCC_AHBENR (*pRCC_AHBENR) 
//	so we can write in code directly RCC_AHBENR = value 
#define RCC_AHBENR (*((volatile unsigned int *)( RCC_BASE + RCC_AHBENR_OFFSET )))

//In section 6.4.6 you see that bit 19 controls the clock for peripheral portC so we define this constant to be the bit position (19)
#define IOPC_EN 19

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

//Offset of the mode setting for pin 8 in the GPIOx_MODER register
#define MODER8 16 

//Offset of the mode setting for pin 9 in the GPIOx_MODER register
#define MODER9 18 

//This port controls the output value of its pins see 8.4.6
#define GPIOC_ODR (*((volatile unsigned int *)( GPIOC_BASE + GPIOx_ODR_OFFSET )))