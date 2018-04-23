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

#include <board.h>

//6.4.1 Clock control register (RCC_CR)
typedef union {
	struct {
		uint32_t HSION:1;
		uint32_t HSIRDY:1;
		uint32_t :1;
		uint32_t HSITRIMP:5;
		uint32_t HSICAL:8;
		uint32_t HSEON:1;
		uint32_t HSERDY:1;
		uint32_t HSEBYP:1;
		uint32_t CSSON:1;
		uint32_t :4;
		uint32_t PLLON:1;
		uint32_t PLLRDY:1;
		uint32_t :6;
	} bit;
	uint32_t reg;
} RCC_CR;

//6.4.1 Clock control register (RCC_CR)
typedef union {
	struct {
		uint32_t :6;
		uint32_t PLLRDY:1;
		uint32_t PLLON:1;
		uint32_t :4;
		uint32_t CSSON:1;
		uint32_t HSEBYP:1;
		uint32_t HSERDY:1;
		uint32_t HSEON:1;
		uint32_t HSICAL:8;
		uint32_t HSITRIMP:5;
		uint32_t :1;
		uint32_t HSIRDY:1;
		uint32_t HSION:1;
	} bit;
	uint32_t reg;
} RCC_CFGR;

//6.4.3 Clock interrupt register (RCC_CIR)
typedef union {
	struct {
		uint32_t LSIRDYF:1;
		uint32_t LSERDYF:1;
		uint32_t HSIRDYF:1;
		uint32_t HSERDYF:1;
		uint32_t PLLRDYF:1;
		uint32_t HSI14RDYF:1;
		uint32_t HSI48RDYF:1;
		uint32_t CSSF:1;
		uint32_t LSIRDYIE:1;
		uint32_t LSERDYIE:1;
		uint32_t HSIRDYIE:1;
		uint32_t HSERDYIE:1;
		uint32_t PLLRDYIE:1;
		uint32_t HSI14RDYIE:1;
		uint32_t HSI48RDYIE:1;
		uint32_t :1;
		uint32_t LSIRDYC:1;
		uint32_t LSERDYC:1;
		uint32_t HSIRDYC:1;
		uint32_t HSERDYC:1;
		uint32_t PLLRDYC:1;
		uint32_t HSI14RDYC:1;
		uint32_t HSI48RDYC:1;
		uint32_t CSSC:1;
		uint32_t :8;
	} bit;
	uint32_t reg;
} RCC_CIR;

//6.4.4 APB peripheral reset register 2 (RCC_APB2RSTR)
typedef union {
	struct {
		uint32_t SYSCFGRST:1;
		uint32_t :4;
		uint32_t USART6RST:1;
		uint32_t USART7RST:1;
		uint32_t USART8RST:1;
		uint32_t :1;
		uint32_t ADCRST:1;
		uint32_t :1;
		uint32_t TIM1RST:1;
		uint32_t SPI1RST:1;
		uint32_t :1;
		uint32_t USART1RST:1;
		uint32_t :1;
		uint32_t TIM15RST:1;
		uint32_t TIM16RST:1;
		uint32_t TIM17RST:1;
		uint32_t :3;
		uint32_t DBGMCURST:1;
		uint32_t :9;
	} bit;
	uint32_t reg;
} RCC_APB2RSTR;

//6.4.5 APB peripheral reset register 1 (RCC_APB1RSTR)
typedef union {
	struct {
		uint32_t TIM2RST:1;
		uint32_t TIM3RST:1;
		uint32_t :2;
		uint32_t TIM6RST:1;
		uint32_t TIM7RST:1;
		uint32_t :2;
		uint32_t TIM14RST:1;
		uint32_t :2;
		uint32_t WWDGRST:1;
		uint32_t :2;
		uint32_t SPI2RST:1;
		uint32_t :2;
		uint32_t USART2RST:1;
		uint32_t USART3RST:1;
		uint32_t USART4RST:1;
		uint32_t USART5RST:1;
		uint32_t I2C1RST:1;
		uint32_t I2C2RST:1;
		uint32_t USBRST:1;
		uint32_t :1;
		uint32_t CANRST:1;
		uint32_t :1;
		uint32_t CRSRST:1;
		uint32_t PWRRST:1;
		uint32_t DACRST:1;
		uint32_t CECRST:1;
		uint32_t :1;
	} bit;
	uint32_t reg;
} RCC_APB1RSTR;

//6.4.6 AHB peripheral clock enable register (RCC_AHBENR)
typedef union {
	struct {
		uint32_t DMAEN:1;
		uint32_t DMA2EN:1;
		uint32_t SRAMEN:1;
		uint32_t :1;
		uint32_t FLITFEN:1;
		uint32_t :1;
		uint32_t CRCEN:1;
		uint32_t :10;
		uint32_t IOPAEN:1;
		uint32_t IOPBEN:1;
		uint32_t IOPCEN:1;
		uint32_t IOPDEN:1;
		uint32_t IOPEEN:1;
		uint32_t IOPFEN:1;
		uint32_t :1;
		uint32_t TSCEN:1;
		uint32_t :7;
	} bit;
	uint32_t reg;
} RCC_AHBENR;

//6.4.7 APB peripheral clock enable register 2 (RCC_APB2ENR)
typedef union {
	struct {
		uint32_t SYSCFGCOMPEN:1;
		uint32_t :4;
		uint32_t USART6EN:1;
		uint32_t USART7EN:1;
		uint32_t USART8EN:1;
		uint32_t :1;
		uint32_t ADCEN:1;
		uint32_t :1;
		uint32_t TIM1EN:1;
		uint32_t SPI1EN:1;
		uint32_t :1;
		uint32_t USART1EN:1;
		uint32_t :1;
		uint32_t TIM15EN:1;
		uint32_t TIM16EN:1;
		uint32_t TIM17EN:1;
		uint32_t :3;
		uint32_t DBGMCUEN:1;
		uint32_t :9;
	} bit;
	uint32_t reg;
} RCC_APB2ENR;

//6.4.8 APB peripheral clock enable register 1 (RCC_APB1ENR)
typedef union {
	struct {
		uint32_t TIM2EN:1;
		uint32_t TIM3EN:1;
		uint32_t :2;
		uint32_t TIM6EN:1;
		uint32_t TIM7EN:1;
		uint32_t :2;
		uint32_t TIM14EN:1;
		uint32_t :2;
		uint32_t WWDGEN:1;
		uint32_t :2;
		uint32_t SPI2EN:1;
		uint32_t :2;
		uint32_t USART2EN:1;
		uint32_t USART3EN:1;
		uint32_t USART4EN:1;
		uint32_t USART5EN:1;
		uint32_t I2C1EN:1;
		uint32_t I2C2EN:1;
		uint32_t USBEN:1;
		uint32_t :1;
		uint32_t CANEN:1;
		uint32_t :1;
		uint32_t CRSEN:1;
		uint32_t PWREN:1;
		uint32_t DACEN:1;
		uint32_t CECEN:1;
		uint32_t :1;
	} bit;
	uint32_t reg;
} RCC_APB1ENR;

//6.4.9 RTC domain control register (RCC_BDCR)
typedef union {
	struct {
		uint32_t LSEON:1;
		uint32_t LSERDY:1;
		uint32_t LSEBYP:1;
		uint32_t LSEDRV:2;
		uint32_t :3;
		uint32_t RTCSEL:2;
		uint32_t :5;
		uint32_t RTCEN:1;
		uint32_t BDRST:1;
		uint32_t :15;
	} bit;
	uint32_t reg;
} RCC_BDCR;

//6.4.10 Control/status register (RCC_CSR)
typedef union {
	struct {
		uint32_t LSION:1;
		uint32_t LSIRDY:1;
		uint32_t :21;
		uint32_t V18PWRRSTF:1;
		uint32_t RMVF:1;
		uint32_t OBLRSTF:1;
		uint32_t PINRSTF:1;
		uint32_t PORRSTF:1;
		uint32_t SFTRSTF:1;
		uint32_t IWDGRSTF:1;
		uint32_t WWDGRSTF:1;
		uint32_t LPWRRSTF:1;
	} bit;
	uint32_t reg;
} RCC_CSR;

//6.4.11 AHB peripheral reset register (RCC_AHBRSTR)
typedef union {
	struct {
		uint32_t :17;
		uint32_t IOPARST:1;
		uint32_t IOPBRST:1;
		uint32_t IOPCRST:1;
		uint32_t IOPDRST:1;
		uint32_t IOPERST:1;
		uint32_t IOPFRST:1;
		uint32_t :1;
		uint32_t TSCRST:1;
		uint32_t :7;
	} bit;
	uint32_t reg;
} RCC_AHBRSTR;

//6.4.12 Clock configuration register 2 (RCC_CFGR2)
typedef union {
	struct {
		uint32_t PREDIV:4;
		uint32_t :28;
	} bit;
	uint32_t reg;
} RCC_CFGR2;

//6.4.13 Clock configuration register 3 (RCC_CFGR3)
typedef union {
	struct {
		uint32_t USART1SW:2;
		uint32_t :2;
		uint32_t I2C1SW:1;
		uint32_t :1;
		uint32_t CECSW:1;
		uint32_t USBSW:1;
		uint32_t ADCSW:1;
		uint32_t :7;
		uint32_t USART2SW:2;
		uint32_t USART3SW:2;
		uint32_t :12;
	} bit;
	uint32_t reg;
} RCC_CFGR3;

//6.4.14 Clock control register 2 (RCC_CR2)
typedef union {
	struct {
		uint32_t HSI14ON:1;
		uint32_t HSI14RDY:1;
		uint32_t HSI14DIS:1;
		uint32_t HSI14TRIM:5;
		uint32_t HSI14CAL:8;
		uint32_t HSI48ON:1;
		uint32_t HSI48RDY:1;
		uint32_t :6;
		uint32_t HSI48CAL:8;
	} bit;
	uint32_t reg;
} RCC_CR2;


//6.4 RCC registers
typedef struct {
	RCC_CR CR;
	RCC_CFGR CFGR;
	RCC_CIR CIR;
	RCC_APB2RSTR APB2RSTR;
	RCC_APB1RSTR APB1RSTR;
	RCC_AHBENR AHBENR;
	RCC_APB2ENR APB2ENR;
	RCC_APB1ENR APB1ENR;
	RCC_BDCR BDCR;
	RCC_CSR CSR;
	RCC_AHBRSTR AHBRSTR;
	RCC_CFGR2 CFGR2;
	RCC_CFGR3 CFGR3;
	RCC_CR2 CR2;
} RCC_TYPE;

#define RCC ((volatile RCC_TYPE *) RCC_BASE)



//Enable a specific peripheral
//Each peripheral is on another BUS, we need to decide depending on that
void enableAHBPeripheral(eAHBPeripherals peripheral, eEnableState enable);
void enableAPB1Peripheral(eAPB1Peripherals peripheral, eEnableState enable);
void enableAPB2Peripheral(eAPB2Peripherals peripheral, eEnableState enable);
//Tried to overload enablePeripheral but no luck in C

#endif // SYSTEM__H //
