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

#include <board.h>


//8.4.1 GPIO port mode register (GPIOx_MODER) (x =A..F)
typedef union {
	struct {
		uint32_t MODER0:2;
		uint32_t MODER1:2;
		uint32_t MODER2:2;
		uint32_t MODER3:2;
		uint32_t MODER4:2;
		uint32_t MODER5:2;
		uint32_t MODER6:2;
		uint32_t MODER7:2;
		uint32_t MODER8:2;
		uint32_t MODER9:2;
		uint32_t MODER10:2;
		uint32_t MODER11:2;
		uint32_t MODER12:2;
		uint32_t MODER13:2;
		uint32_t MODER14:2;
		uint32_t MODER15:2;
	} bit;
	uint32_t reg;
} GPIOx_MODER;
//8.4.2 GPIO port output type register (GPIOx_OTYPER)
typedef union {
	struct {
		uint32_t OTYPER0:1;
		uint32_t OTYPER1:1;
		uint32_t OTYPER2:1;
		uint32_t OTYPER3:1;
		uint32_t OTYPER4:1;
		uint32_t OTYPER5:1;
		uint32_t OTYPER6:1;
		uint32_t OTYPER7:1;
		uint32_t OTYPER8:1;
		uint32_t OTYPER9:1;
		uint32_t OTYPER10:1;
		uint32_t OTYPER11:1;
		uint32_t OTYPER12:1;
		uint32_t OTYPER13:1;
		uint32_t OTYPER14:1;
		uint32_t OTYPER15:1;
		uint32_t reserved:16;
	} bit;
	uint32_t reg;
} GPIOx_OTYPER;
//8.4.3 GPIO port output speed register (GPIOx_OSPEEDR)
typedef union {
	struct {
		uint32_t OSPEEDR0:2;
		uint32_t OSPEEDR1:2;
		uint32_t OSPEEDR2:2;
		uint32_t OSPEEDR3:2;
		uint32_t OSPEEDR4:2;
		uint32_t OSPEEDR5:2;
		uint32_t OSPEEDR6:2;
		uint32_t OSPEEDR7:2;
		uint32_t OSPEEDR8:2;
		uint32_t OSPEEDR9:2;
		uint32_t OSPEEDR10:2;
		uint32_t OSPEEDR11:2;
		uint32_t OSPEEDR12:2;
		uint32_t OSPEEDR13:2;
		uint32_t OSPEEDR14:2;
		uint32_t OSPEEDR15:2;
	} bit;
	uint32_t reg;
} GPIOx_OSPEEDR;
//8.4.4 GPIO port pull-up/pull-down register (GPIOx_PUPDR)
typedef union {
	struct {
		uint32_t PUPDR0:2;
		uint32_t PUPDR1:2;
		uint32_t PUPDR2:2;
		uint32_t PUPDR3:2;
		uint32_t PUPDR4:2;
		uint32_t PUPDR5:2;
		uint32_t PUPDR6:2;
		uint32_t PUPDR7:2;
		uint32_t PUPDR8:2;
		uint32_t PUPDR9:2;
		uint32_t PUPDR10:2;
		uint32_t PUPDR11:2;
		uint32_t PUPDR12:2;
		uint32_t PUPDR13:2;
		uint32_t PUPDR14:2;
		uint32_t PUPDR15:2;
	} bit;
	uint32_t reg;
} GPIOx_PUPDR;
//8.4.5 GPIO port input data register (GPIOx_IDR)
typedef union {
	struct {
		uint32_t IDR0:1;
		uint32_t IDR1:1;
		uint32_t IDR2:1;
		uint32_t IDR3:1;
		uint32_t IDR4:1;
		uint32_t IDR5:1;
		uint32_t IDR6:1;
		uint32_t IDR7:1;
		uint32_t IDR8:1;
		uint32_t IDR9:1;
		uint32_t IDR10:1;
		uint32_t IDR11:1;
		uint32_t IDR12:1;
		uint32_t IDR13:1;
		uint32_t IDR14:1;
		uint32_t IDR15:1;
		uint32_t reserved:16;
	} bit;
	uint32_t reg;
} GPIOx_IDR;
//8.4.6 GPIO port output data register (GPIOx_ODR)
typedef union {
	struct {
		uint32_t ODR0:1;
		uint32_t ODR1:1;
		uint32_t ODR2:1;
		uint32_t ODR3:1;
		uint32_t ODR4:1;
		uint32_t ODR5:1;
		uint32_t ODR6:1;
		uint32_t ODR7:1;
		uint32_t ODR8:1;
		uint32_t ODR9:1;
		uint32_t ODR10:1;
		uint32_t ODR11:1;
		uint32_t ODR12:1;
		uint32_t ODR13:1;
		uint32_t ODR14:1;
		uint32_t ODR15:1;
		uint32_t reserved:16;
	} bit;
	uint32_t reg;
} GPIOx_ODR;
//8.4.7 GPIO port bit set/reset register (GPIOx_BSRR)
typedef union {
	struct {
		uint32_t BS0:1;
		uint32_t BS1:1;
		uint32_t BS2:1;
		uint32_t BS3:1;
		uint32_t BS4:1;
		uint32_t BS5:1;
		uint32_t BS6:1;
		uint32_t BS7:1;
		uint32_t BS8:1;
		uint32_t BS9:1;
		uint32_t BS10:1;
		uint32_t BS11:1;
		uint32_t BS12:1;
		uint32_t BS13:1;
		uint32_t BS14:1;
		uint32_t BS15:1;
		uint32_t BR0:1;
		uint32_t BR1:1;
		uint32_t BR2:1;
		uint32_t BR3:1;
		uint32_t BR4:1;
		uint32_t BR5:1;
		uint32_t BR6:1;
		uint32_t BR7:1;
		uint32_t BR8:1;
		uint32_t BR9:1;
		uint32_t BR10:1;
		uint32_t BR11:1;
		uint32_t BR12:1;
		uint32_t BR13:1;
		uint32_t BR14:1;
		uint32_t BR15:1;
	} bit;
	uint32_t reg;
} GPIOx_BSRR;
//8.4.8 GPIO port configuration lock register (GPIOx_LCKR)
typedef union {
	struct {
		uint32_t LCK0:1;
		uint32_t LCK1:1;
		uint32_t LCK2:1;
		uint32_t LCK3:1;
		uint32_t LCK4:1;
		uint32_t LCK5:1;
		uint32_t LCK6:1;
		uint32_t LCK7:1;
		uint32_t LCK8:1;
		uint32_t LCK9:1;
		uint32_t LCK10:1;
		uint32_t LCK11:1;
		uint32_t LCK12:1;
		uint32_t LCK13:1;
		uint32_t LCK14:1;
		uint32_t LCK15:1;
		uint32_t LCKK:1;
		uint32_t reserved:15;
	} bit;
	uint32_t reg;
} GPIOx_LCKR;
//8.4.9 GPIO alternate function low register (GPIOx_AFRL)
typedef union {
	struct {
		uint32_t AFSEL0:4;
		uint32_t AFSEL1:4;
		uint32_t AFSEL2:4;
		uint32_t AFSEL3:4;
		uint32_t AFSEL4:4;
		uint32_t AFSEL5:4;
		uint32_t AFSEL6:4;
		uint32_t AFSEL7:4;
	} bit;
	uint32_t reg;
} GPIOx_AFRL;
//8.4.10 GPIO alternate function high register (GPIOx_AFRH)
typedef union {
	struct {
		uint32_t AFSEL8:4;
		uint32_t AFSEL9:4;
		uint32_t AFSEL10:4;
		uint32_t AFSEL11:4;
		uint32_t AFSEL12:4;
		uint32_t AFSEL13:4;
		uint32_t AFSEL14:4;
		uint32_t AFSEL15:4;
	} bit;
	uint32_t reg;
} GPIOx_AFRH;
//8.4.11 GPIO port bit reset register (GPIOx_BRR)
typedef union {
	struct {
		uint32_t BR0:1;
		uint32_t BR1:1;
		uint32_t BR2:1;
		uint32_t BR3:1;
		uint32_t BR4:1;
		uint32_t BR5:1;
		uint32_t BR6:1;
		uint32_t BR7:1;
		uint32_t BR8:1;
		uint32_t BR9:1;
		uint32_t BR10:1;
		uint32_t BR11:1;
		uint32_t BR12:1;
		uint32_t BR13:1;
		uint32_t BR14:1;
		uint32_t BR15:1;
		uint32_t reserved:16;
	} bit;
	uint32_t reg;
} GPIOx_BRR;

typedef struct {
	GPIOx_MODER MODER;
	GPIOx_OTYPER OTYPER;
	GPIOx_OSPEEDR OSPEEDR;
	GPIOx_PUPDR PUPDR;
	GPIOx_IDR IDR;
	GPIOx_ODR ODR;
	GPIOx_BSRR BSRR;
	GPIOx_LCKR LCKR;
	GPIOx_AFRL AFRL;
	GPIOx_AFRH AFRH;
	GPIOx_BRR BRR;
} GPIO_Type;


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

typedef enum
{
	ePin_NoPull = 0x00,
	ePin_PullUp = 0x01,
	ePin_PullDown = 0x10
} ePUPDType;

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

/*
 * Sets the pin Pull-up Pull-Down
 */
void setPUPD(GPIO_Type * port, unsigned int pinNumber, ePUPDType PinPUPD);


#endif //GPIO_H

