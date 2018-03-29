/* STM32f0discovery embedded essentials course project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#define ADC_BASE 0x40012400

#include <board.h>

//13.12.1 ADC interrupt and status register (ADC_ISR)
typedef union {
	struct {
		uint32_t ADRDY:1;
		uint32_t EOSMP:1;
		uint32_t EOC:1;
		uint32_t EOSEQ:1;
		uint32_t OVR:1;
		uint32_t :2;
		uint32_t AWD:1;
		uint32_t :24;
	} bit;
	uint32_t reg;
} ADC_ISR;

//13.12.2 ADC interrupt enable register (ADC_IER)
typedef union {
	struct {
		uint32_t ADRDYIE:1;
		uint32_t EOSMPIE:1;
		uint32_t EOCIE:1;
		uint32_t EOSEQIE:1;
		uint32_t OVRIE:1;
		uint32_t :2;
		uint32_t AWDIE:1;
		uint32_t :24;
	} bit;
	uint32_t reg;
} ADC_IER;

//13.12.3 ADC control register (ADC_CR)
typedef union {
	struct {
		uint32_t ADEN:1;
		uint32_t ADDIS:1;
		uint32_t ADSTART:1;
		uint32_t :1;
		uint32_t ADSTP:1;
		uint32_t :26;
		uint32_t ADCAL:1;
	} bit;
	uint32_t reg;
} ADC_CR;

///13.12.4 ADC configuration register 1 (ADC_CFGR1)
typedef union {
	struct {
		uint32_t DMAEN:1;
		uint32_t DMACFG:1;
		uint32_t SCANDIR:1;
		uint32_t RES:2;
		uint32_t ALIGN:1;
		uint32_t EXTSEL:3;
		uint32_t :1;
		uint32_t EXTEN:2;
		uint32_t OVRMOD:1;
		uint32_t CONT:1;
		uint32_t WAIT:1;
		uint32_t AUTOFF:1;
		uint32_t DISCEN:1;
		uint32_t :5;
		uint32_t AWDSGL:1;
		uint32_t AWDEN:1;
		uint32_t :2;
		uint32_t AWDCH:5;
		uint32_t :1;
	} bit;
	uint32_t reg;
} ADC_CFGR1;

//13.12.5 ADC configuration register 2 (ADC_CFGR2)
typedef union {
	struct {
		uint32_t :30;
		uint32_t CKMODE:2;
	} bit;
	uint32_t reg;
} ADC_CFGR2;

//13.12.6 ADC sampling time register (ADC_SMPR)
typedef union {
	struct {
		uint32_t SMP:3;
		uint32_t :29;
	} bit;
	uint32_t reg;
} ADC_SMPR;

//13.12.7 ADC watchdog threshold register (ADC_TR)
typedef union {
	struct {
		uint32_t LT:12;
		uint32_t :4;
		uint32_t HT:12;
		uint32_t :4;
	} bit;
	uint32_t reg;
} ADC_TR;

//13.12.8 ADC channel selection register (ADC_CHSELR)
typedef union {
	struct {
		uint32_t CHSEL:19;
		uint32_t :13;
	} bit;
	uint32_t reg;
} ADC_CHSELR;

//13.12.9 ADC data register (ADC_DR)
typedef union {
	struct {
		uint32_t DATA:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} ADC_DR;

//13.12.10 ADC common configuration register (ADC_CCR)
typedef union {
	struct {
		uint32_t :22;
		uint32_t VREFEN:1;
		uint32_t TSEN:1;
		uint32_t VBATEN:1;
		uint32_t :7;
	} bit;
	uint32_t reg;
} ADC_CCR;

//(!!!) ALSO SEE 13.12.11 table showing the reserved areas
typedef struct
{
	ADC_ISR ISR; //13.12.1 ADC interrupt and status register (ADC_ISR)
	ADC_IER IER; //13.12.2 ADC interrupt enable register (ADC_IER)
	ADC_CR CR; //13.12.3 ADC control register (ADC_CR)
	ADC_CFGR1 CFGR1; //13.12.4 ADC configuration register 1 (ADC_CFGR1)
	ADC_CFGR2 CFGR2; //13.12.5 ADC configuration register 2 (ADC_CFGR2)
	ADC_SMPR SMPR; //13.12.6 ADC sampling time register (ADC_SMPR) //0x14
	unsigned int res1[2];
	ADC_TR TR; //13.12.7 ADC watchdog threshold register (ADC_TR)
	unsigned int res2;
	ADC_CHSELR CHSELR; //13.12.8 ADC channel selection register (ADC_CHSELR) 0x28
	unsigned int res3[5];
	ADC_DR DR; //13.12.9 ADC data register (ADC_DR) //0x40
	unsigned int res4[0xb1]; //177 = 0xB1 ; (0x308 - 0x40)/4 - 1 (use calculator in programmer mode in hex)
	ADC_CCR CCR; //13.12.10 ADC common configuration register (ADC_CCR) //0x308
} ADC_Type;

#define ADC1 ((volatile ADC_Type*)ADC_BASE)

#define ADC_ISR_ADRDY (1<<0)
#define ADC_ISR_EOC (1<<2)
#define ADC_CR_ADEN (1<<0)
#define ADC_CR_ADSTART (1<<2)
#define ADC_CFGR2_CK (2<<30) //using 10: PCLK/4 (Synchronous clock mode)


#define ADC_CHSELR_CHSEL0 (1<<0)


//setup the ADC peripheral
void setupADC(void);

//start a conversion on channel ADC_IN0 which is on PA0 see datasheet table 13
unsigned int convertADC(void);

#endif /* INCLUDE_ADC_H_ */
