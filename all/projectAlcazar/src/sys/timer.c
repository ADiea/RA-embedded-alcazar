/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/
#include <timer.h>

//sets the timer counter register to value. value must be max 65535 (16bits)
void setTimerCounter(volatile Timer_Type* timer, unsigned int value)
{
	timer->CNT = value & 0xFFFF; //force the value given to be max 65535
}

//sets timer prescaler. a prescaler of 2 divides the cpu clk by 2
//making the counter count 2 times slower than cpu frequency
void setTimerPrescaler(volatile Timer_Type* timer, unsigned int value)
{
	//TODO: implement function based on reference manual
}

//stops the timer from counting
void stopTimer(volatile Timer_Type* timer)
{
	timer->CR1 &= ~(1<<TIM_CR1_CEN);
}

//start the timer to count in the up or down direction
void startTimer(volatile Timer_Type* timer, eTimerDirection direction)
{
	//first clear the direction bit
	timer->CR1 &= ~(1<<TIM_DIR);
	//then set together the enable and direction bits
	timer->CR1 |= (1<<TIM_CR1_CEN) | (direction<<TIM_DIR);
}

//reads the timer counter register value, which is the value the timer has counted to until now
unsigned int getTimerValue(volatile Timer_Type* timer)
{
	return timer->CNT;
}

/*
 * Sets up the PWM fucntion on this timer. See section 17.3.10 from reference manual
 * This is a helper function it sets
 * 		- PWM mode 1 edge aligned,
 * 		- upcounting,
 * 		- enables first three channels, with normal polarity
 *
 * For different behavior, you should individually set the registers as needed
 * instead of using this function.
 *
 *
 *
 * */
void setupPWMConfiguration(volatile Timer_Type* timer,
							unsigned int pwmPeriodCounter,
							unsigned int pwmPeriodPrescaler
							)
{
	//always check the input parameters
	if(!timer || pwmPeriodCounter > 0xFFFF || pwmPeriodPrescaler > 0xFFFF)
		return;

	/*
	 * To better understand what happens in this function please read carefully
	 * 17.3.10 PWM mode - from the reference manual
	 * and 17.4.7 describing the CCMR register
	 * We will use PWM mode 1, edge-aligned, upcounting configuration
	 *
	 * Also you should study the example in section
	 * A.9.8 Edge-aligned PWM configuration example
	 * keep in mind that in that example CPU is clocked at 48Mhz
	 *
	 * We will use the same steps as in the example numbered (x)
	 *
	 */

	/*The prescaler can divide the counter clock frequency by any factor between 1 and 65536.
	 * It is based on a 16-bit counter controlled through a 16-bit register
	 * (in the TIMx_PSC register). It can be changed on the fly as this control register
	 * is buffered. The new prescaler ratio is taken into account at the next update event.*/
	//The counter clock frequency (CK_CNT) is equal to fCK_CPU / (PSC[15:0] + 1).

	// (1) set the prescaler
	timer->PSC = pwmPeriodPrescaler;

	// (2) set the automatic reload value
	timer->ARR = pwmPeriodCounter;

	//Using CCRx registers we control the PWM dutycycle for each of the three channels
	//For PWM mode 1 - In upcounting, channel x is active (HIGH or 1)
 	// 	 as long as TIMx_CNT<TIMx_CCRx else inactive (LOW or 0).

	//Because the timer counter goes up only until it reaches ARR register
	//by setting CCRx register from 0 to ARR we get a duty cycle from 0% to 100%

	// (3) set CCRx registers for the three channels
	//this sets the duty cycle to 0%, permanent low signal (0) for all 3 channels
	timer->CCR1 = timer->CCR2 = timer->CCR3 = 0;

	//For setting the output compare mode in CCMR register,
	//must first clear the CCxE bits in CCER
	//>> Note: CC2S bits are writable only when the channel is OFF (CCxE = ‘0’ in TIMx_CCER).
	timer->CCER = 0;

	//see section 17.4.7. We set the 3 channels in output compare mode.
	//First 2 channels are set using CCMR1 and the third channel is set using CCMR2 register
	//Bits 0-7 control first channel 8-15 second channel and bits 0-7 of CCMR2 third channel
	/*
	 CCxS bits will be outputs. We want to output PWM signal. To change the dutycycle
	 we will use CCRx registers to set the compare value for each channel.
	 To be able to set CCRx registers anytime we must enable preloading
	 (The TIMx_CCRx registers can be programmed with or without preload
	 registers using the OCxPE bit in the TIMx_CCMRx register.)

	 Bits 0:1 	CCxS 	=> 00 channel is output
	 Bit  2   	OCxFE 	=> 0 normal behavior
	 Bit  3		OCxPE 	=> 1 should be 1 for PWM see 17.3.10
	 Bits 6:4	OCxM	=> 110: (=0x6) PWM mode 1 - In upcounting, channel 1 is active (HIGH or 1)
	 	 	 	 	 	 	 	 as long as TIMx_CNT<TIMx_CCR1 else inactive (LOW or 0).
	 Bit  7		OCxCE	=> 0: OC1Ref is not affected by the ETRF Input
	 */

	//we have the same configuration for all 3 channels so we can use
	//the same expression and shift it by 8 to the left for channel 2
	//so that we end up modifying bits 15 - 8

	// (4) set the capture and compare mode registers for our three channels
	timer->CCMR1 =  (TIM_MODE_PWM1 << TIM_OCxM | 1 << TIM_OCxPE) << 8 |  //configuration for channel 2
					(TIM_MODE_PWM1 << TIM_OCxM | 1 << TIM_OCxPE);      //configuration for channel 1

	timer->CCMR2 =  (TIM_MODE_PWM1 << TIM_OCxM | 1 << TIM_OCxPE);      //configuration for channel 3


	// (5) enable three channels with normal polarity. see 17.4.9
	timer->CCER = 1<<TIM_CC1E | 1<<TIM_CC2E | 1<<TIM_CC3E;

	// (6) Main output enable see 17.4.18
	timer->BDTR |= 1<<TIM_BDTR_MOE;

	// (7) Enable counter, upcounting
	timer->CR1 |= 1<<TIM_CR1_CEN;

	/* Bit 7 ARPE: Auto-reload preload enable
			0: TIMx_ARR register is not buffered
			1: TIMx_ARR register is buffered
	*/
	//See figure 66 and figure 67  in section 17.3.2
	//We are interested to synch ARR register with the overflow of the timer
	//timer->CR1 = 1 << TIM_ARPE;

	// (8) Force update generation (UG = 1)
	timer->EGR |= 1<<TIM_EGR_UG;
}

/*
 * Sets PWM duty cycle
 *
 *Using CCRx registers we control the PWM dutycycle for each of the three channels
  For PWM mode 1 - In upcounting, channel x is active (HIGH or 1)
  as long as TIMx_CNT<TIMx_CCRx else inactive (LOW or 0).

  Because the timer counter goes up only until it reaches ARR register
  by setting CCRx register from 0 to ARR we get a duty cycle from 0% to 100%

  pwmDuty: value between 0 and ARR that will set a dutycycle from 0 to 100%
  channel: value between 0 and 3 that selects the channel to which the duty is applied
 */
void setPWMDuty(volatile Timer_Type* timer, unsigned int channel, unsigned int pwmDuty)
{
	volatile unsigned int * pDutyRegister;

	//the switch bellow can be replaced with a much faster implementation
	// pDutyRegister = &timer->CCR1 + channel*sizeof(unsigned int)
	//because the manufacturer has mapped the 4 registers in order one after another
	switch(channel)
	{
		case 0:
			pDutyRegister = & (timer->CCR1);
			break;
		case 1:
			pDutyRegister = & (timer->CCR2);
			break;
		case 2:
			pDutyRegister = & (timer->CCR3);
			break;
		case 3:
			pDutyRegister = & (timer->CCR4);
			break;
	};

	//set the compare value nt the corresponding CCRx register
	*pDutyRegister = pwmDuty;
}
