/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)

For understanding the following declarations
Please see the document [STM32F051C8 Datasheet.pdf] section 3.7 
					and	[STM32F0 Reference Manual.pdf] sections 
					section 2.2.2, table
					section 8
*/
#ifndef GPIO_H
#define GPIO_H

//The base of the GPIO_C register. Note the C in the GPIOC_BASE it comes from the periferal C, where we have our LED
//See section 2.2.2 or search for GPIOC
#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800
#define GPIOD_BASE 0x48000C00
#define GPIOE_BASE 0x48001000
#define GPIOF_BASE 0x48001400

typedef struct
{
	unsigned int MODER ;//8.4.1 GPIO port mode register GPIOx_MODER offset 0x00
	unsigned int OTYPER; //8.4.2 GPIO port output type register GPIOx_OTYPER offset 0x04
	unsigned int OSPEEDR; //8.4.3 GPIO port output speed register (GPIOx_OSPEEDR)
	unsigned int PUPDR; //8.4.4 GPIO port pull-up/pull-down register (GPIOx_PUPDR)
	unsigned int IDR; //8.4.5 GPIO port input data register (GPIOx_IDR)
	unsigned int ODR; //8.4.6 GPIO port output data register (GPIOx_ODR)
	unsigned int BSRR; //8.4.7 GPIO port bit set/reset register (GPIOx_BSRR)
	unsigned int LCKR; //8.4.8 GPIO port configuration lock register (GPIOx_LCKR)
	unsigned int AFRL; //8.4.9 GPIO alternate function low register (GPIOx_AFRL)
	unsigned int AFRH; //8.4.10 GPIO alternate function high register (GPIOx_AFRH)
	unsigned int BRR; //8.4.11 GPIO port bit reset register (GPIOx_BRR)
}GPIO_Type;

//define POINTERS to GPIO port structures
#define GPIOA ((volatile GPIO_Type *) GPIOA_BASE)
#define GPIOB ((volatile GPIO_Type *) GPIOB_BASE)
#define GPIOC ((volatile GPIO_Type *) GPIOC_BASE)
#define GPIOD ((volatile GPIO_Type *) GPIOD_BASE)
#define GPIOE ((volatile GPIO_Type *) GPIOE_BASE)
#define GPIOF ((volatile GPIO_Type *) GPIOF_BASE)

//See 8.4.1
/*
00: Input mode (reset state)
01: General purpose output mode
10: Alternate function mode
11: Analog mode
*/
typedef enum
{
	ePin_Input = 0x0,
	ePin_Output = 0x1,
	ePin_AlternateFunction = 0x2,
	ePin_Analog = 0x3
} ePinMode;

typedef enum
{
	ePin_AF0 = 0, //alternate function zero
	ePin_AF1, //alternate function 1
	ePin_AF2,
	ePin_AF3,
	ePin_AF4,
	ePin_AF5,
	ePin_AF6,
	ePin_AF7
} ePinAlternateFunc;

//Offset of the mode setting for pin p in the GPIOx_MODER register is p*2
#define MODERPOS(x) ((x)<<1)

/*GPIO driver functions*/
/*
 * Sets the pin "pinNumber" of port "port" mode
 * */
void setPinMode(volatile GPIO_Type * port, unsigned int pinNumber, ePinMode pinMode);

/*
 * Writes 1/0 to the corresponding pinNumber of port "port"
 * */
void writePin(volatile GPIO_Type * port, unsigned int pinNumber, unsigned int value);

/*
 * Returns 1 if pin "pinNumber" in port "port" is set and 0 if the pin is not set
 * */
unsigned int readPin(volatile GPIO_Type * port, unsigned int pinNumber);

/*
 * Sets the pin "pinNumber" of port "port" alternate function "pinFunction"
 * For corresponding alternate function number to actual function see chapters
 * Table 14 & Table 15 in [STM32F051C8_Datasheet] -
 * 	Alternate functions selected through GPIOx_AFR registers
 * */
void setPinAlternateFunction(volatile GPIO_Type * port, unsigned int pinNumber, ePinAlternateFunc pinFunction);


#endif //GPIO_H

