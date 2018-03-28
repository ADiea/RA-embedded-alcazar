/* STM32f0discovery embedded essentials course project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include<adc.h>

//setup the ADC peripheral
void setupADC(void)
{
	/* (1) Ensure that ADRDY = 0 */
	/* (2) Clear ADRDY */
	/* (3) Enable the ADC */
	/* (4) Wait until ADC ready */

	//configure clock while adc is disabled
	ADC1->CFGR2 |= ADC_CFGR2_CK;

	if ((ADC1->ISR & ADC_ISR_ADRDY) != 0) /* (1) */
	{
	ADC1->ISR |= ADC_ISR_ADRDY; /* (2) */
	}
	ADC1->CR |= ADC_CR_ADEN; /* (3) */
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) /* (4) */
	{
	/* For robust implementation, add here time-out management */
	}

}

//start a conversion on channel ADC_IN1 which is on PA1 see datasheet table 13
unsigned int convertADC(void)
{
	unsigned int ADC_Result = 0;
	/* (2) Select CHSEL0, CHSEL9, CHSEL10 andCHSEL17 for VRefInt */
	/* (3) Select a sampling mode of 111 i.e. 239.5 ADC clk to be greater
	than 17.1us */
	/* (4) Wake-up the VREFINT (only for VBAT, Temp sensor and VRefInt) */

	ADC1->CHSELR =  ADC_CHSELR_CHSEL0; /* (2) */

	//don't care about sampling ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* (3) */
	//ADC->CCR |= ADC_CCR_VREFEN; /* (4) */

	/* Performs the AD conversion */
	ADC1->CR |= ADC_CR_ADSTART; /* Start the ADC conversion */

	while ((ADC1->ISR & ADC_ISR_EOC) == 0) /* Wait end of conversion */
	{
	/* For robust implementation, add here time-out management */
	}

	ADC_Result = ADC1->DR; /* Store the ADC conversion result */

	return ADC_Result;
}


