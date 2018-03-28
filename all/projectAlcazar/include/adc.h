/* STM32f0discovery embedded essentials course project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#define ADC_BASE 0x40012400

//(!!!) ALSO SEE 13.12.11 table showing the reserved areas
typedef struct
{
	unsigned int ISR; //13.12.1 ADC interrupt and status register (ADC_ISR)
	unsigned int IER; //13.12.2 ADC interrupt enable register (ADC_IER)
	unsigned int CR; //13.12.3 ADC control register (ADC_CR)
	unsigned int CFGR1; //13.12.4 ADC configuration register 1 (ADC_CFGR1)
	unsigned int CFGR2; //13.12.5 ADC configuration register 2 (ADC_CFGR2)
	unsigned int SMPR; //13.12.6 ADC sampling time register (ADC_SMPR) //0x14
	unsigned int res1[2];
	unsigned int TR; //13.12.7 ADC watchdog threshold register (ADC_TR)
	unsigned int res2;
	unsigned int CHSELR; //13.12.8 ADC channel selection register (ADC_CHSELR) 0x28
	unsigned int res3[5];
	unsigned int DR; //13.12.9 ADC data register (ADC_DR) //0x40
	unsigned int res4[0xb1]; //177 = 0xB1 ; (0x308 - 0x40)/4 - 1 (use calculator in programmer mode in hex)
	unsigned int CCR; //13.12.10 ADC common configuration register (ADC_CCR) //0x308
}ADC_Type;

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
