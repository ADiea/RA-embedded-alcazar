/*
 * board.h
 *
 *  Created on: Mar 28, 2018
 *      Author: doru
 */

#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_

typedef unsigned int uint32_t;
//typedef unsigned short uint16_t;
//typedef unsigned char uint8_t;

//The Blue LED is on bit 8 of port C
#define LED_PIN 8
#define RCC_BASE 		0x40021000

//The base of the GPIO_C register. Note the C in the GPIOC_BASE it comes from the periferal C, where we have our LED
//See section 2.2.2 or search for GPIOC
#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800
#define GPIOD_BASE 0x48000C00
#define GPIOE_BASE 0x48001000
#define GPIOF_BASE 0x48001400

//define enable/disable values
typedef enum
{
	eDisabled,
	eEnabled
} eEnableState;

//In section 6.4.6 you see what bit controls which peripheral
//In section 6.4.7 you see what bit controls which peripheral
//Enumerate all used peripherals
typedef enum
{
	ePerif_DMA1  = 0,
	ePerif_DMA2  = 1,
	ePerif_SRAM  = 2,
	ePerif_FLITF = 4,
	ePerif_CRC   = 6,
	ePerif_GPIOA = 17,
	ePerif_GPIOB = 18,
	ePerif_GPIOC = 19,
	ePerif_GPIOD = 20,
	ePerif_GPIOE = 21,
	ePerif_GPIOF = 22,
	ePerif_TSC   = 24, //touch sensing controller
} eAHBPeripherals;

typedef enum
{
	ePerif_TIM2   = 0,
	ePerif_TIM3   = 1,
	ePerif_TIM6   = 4,
	ePerif_TIM7   = 5,
	ePerif_TIM14  = 8,
	ePerif_WWD    = 11,
	ePerif_SPI2   = 14,
	ePerif_USART2 = 17,
	ePerif_USART3 = 18,
	ePerif_USART4 = 19,
	ePerif_USART5 = 20,
	ePerif_I2C1   = 21,
	ePerif_I2C2   = 22,
	ePerif_USB    = 23,
	ePerif_CAN    = 25,
	ePerif_CRS    = 27,
	ePerif_PWR    = 28,
	ePerif_DAC    = 29,
	ePerif_CEC    = 30,
} eAPB1Peripherals;

typedef enum
{
	ePerif_SYSCFG   = 1,
	ePerif_USART6   = 5,
	ePerif_USART7   = 6,
	ePerif_USART8   = 7,
	ePerif_ADC      = 9,
	ePerif_TIM1     = 11,
	ePerif_SPI1     = 12,
	ePerif_USART1   = 14,
	ePerif_TIM15    = 16,
	ePerif_TIM16    = 17,
	ePerif_TIM17    = 18,
	ePerif_DBGMCU   = 22,
} eAPB2Peripherals;


#endif /* INCLUDE_BOARD_H_ */
