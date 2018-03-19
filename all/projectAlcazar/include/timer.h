/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

//This file contains timer related function declarations

#ifndef TIMER_H
#define TIMER_H

//see 2.2.2 in reference manual
#define TIM1_BASE 0x40012C00
#define TIM15_BASE 0x40014000

//! Because timers are not all the same, some offer slightly different functions
//	we cannot treat them all the same as the GPIOs, because some of them have different
//  registers and register offsets
// Therefore we must make sure from the refernece manual that we use the correct register order
//	=> we will define different structure for registers for every used timer

//Update 17/03/2018: The above comment is only partially correct. It looks like the architecture is
//well designed so that even if certain timers do not have all the registers still their other
//registers are at the same offsets. This means we can define one struct with all the registers
//and for each timer only use the registrs present on that specific timer (see the reference manual
//for each timer)

typedef struct
{
	//although registers are 16 bit wide if we look at the offsets they are spaced 4 bytes apart
	//so we define them as 32 bit but will only use the lower 16bits
	unsigned int CR1; //17.4.1 TIM1 control register 1 (TIM15_CR1)
	unsigned int CR2; //17.4.2 TIM1 control register 2 (TIM15_CR2)
	unsigned int SMCR; //17.4.3 TIM1 slave mode control register (TIM15_SMCR)
	unsigned int DIER; //17.4.4 TIM1 DMA/interrupt enable register (TIM15_DIER)
	unsigned int SR; //17.4.5 TIM1 status register (TIM15_SR)
	unsigned int EGR; //17.4.6 TIM1 event generation register (TIM15_EGR)
	unsigned int CCMR1; //17.4.7 TIM1 capture/compare mode register 1 (TIM15_CCMR1)
	unsigned int CCMR2; //17.4.8 TIM1 capture/compare mode register 2 (TIM15_CCMR2)
	unsigned int CCER; //17.4.9 TIM1 capture/compare enable register (TIM15_CCER)
	unsigned int CNT; //17.4.10 TIM1 counter (TIM15_CNT)
	unsigned int PSC; //17.4.11 TIM1 prescaler (TIM15_PSC)
	unsigned int ARR; //17.4.12 TIM1 auto-reload register (TIM15_ARR)
	unsigned int RCR; //17.4.13 TIM1 repetition counter register (TIM15_RCR)
	unsigned int CCR1; //17.4.14 TIM1 capture/compare register 1 (TIM15_CCR1)
	unsigned int CCR2; //17.4.15 TIM1 capture/compare register 2 (TIM15_CCR2)
	unsigned int CCR3; //17.4.16 TIM1 capture/compare register 1 (TIM15_CCR3)
	unsigned int CCR4; //17.4.17 TIM1 capture/compare register 2 (TIM15_CCR4)
	unsigned int BDTR; //17.4.18 TIM1 break and dead-time register (TIM1_BDTR)
	unsigned int DCR; //17.4.19 TIM1 DMA control register (TIM1_DCR)
	unsigned int DMAR; //17.4.20 TIM1 DMA address for full transfer (TIM1_DMAR)
}Timer_Type;

#define TIM1 ((volatile Timer_Type*)TIM1_BASE)
#define TIM15 ((volatile Timer_Type*)TIM15_BASE)

typedef enum
{
	eTimerDirection_Up = 0,
	eTimerDirection_Down = 1
} eTimerDirection;

//Useful bits for controlling timers are in TIMx_CR1 register
#define TIM_ARPE 7 //Bit 7 ARPE: Auto-reload preload enable
#define TIM_DIR 4 //Bit 4 DIR: Direction
#define TIM_CR1_CEN 0 //Bit 0 CEN: Counter enable
#define TIM_CC1E 0// see 17.4.9
#define TIM_CC2E 4// see 17.4.9
#define TIM_CC3E 8// see 17.4.9
#define TIM_CC4E 12// see 17.4.9

#define TIM_OCxM 4 //bits from CCMRx register
#define TIM_OCxPE 3

#define TIM_BDTR_MOE 15 //see 17.4.18

#define TIM_EGR_UG 0 //see 17.4.6

#define TIM_MODE_PWM1 0x06 //110: (=0x6) PWM mode 1, see 17.4.7

//sets the timer counter register to value. value must be max 65536 (16bits)
void setTimerCounter(volatile Timer_Type* timer, unsigned int value);

//sets timer prescaler. a prescaler of 2 divides the cpu clk by 2
//making the counter count 2 times slower than cpu frequency
void setTimerPrescaler(volatile Timer_Type* timer, unsigned int value);

//stops the timer from counting
void stopTimer(volatile Timer_Type* timer);

//start the timer to count in the up or down direction
void startTimer(volatile Timer_Type* timer, eTimerDirection direction);

//reads the timer counter register value, which is the value the timer has counted to until now
unsigned int getTimerValue(volatile Timer_Type* timer);

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
							unsigned int pwmPeriodPrescaler);

/*
 * Sets PWM duty cycle
  pwmDuty: value between 0 and ARR that will set a dutycycle from 0 to 100%
  channel: value between 0 and 3 that selects the channel to which the duty is applied
 */
void setPWMDuty(volatile Timer_Type* timer, unsigned int channel, unsigned int pwmDuty);

#endif //TIMER_H
