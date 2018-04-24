/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

//This file contains timer related function declarations

#ifndef TIMER_H
#define TIMER_H

#include <board.h>

//see 2.2.2 in reference manual
#define TIM1_BASE 0x40012C00
#define TIM3_BASE 0x40000400
#define TIM15_BASE 0x40014000

//17.4.1 TIMx control register 1 (TIMx_CR1)
typedef union {
	struct {
		uint32_t CEN:1;
		uint32_t UDIS:1;
		uint32_t URS:1;
		uint32_t OPM:1;
		uint32_t DIR:1;
		uint32_t CMS:2;
		uint32_t ARPE:1;
		uint32_t CKD:2;
		uint32_t :22;
	} bit;
	uint32_t reg;
} TIMx_CR1;

//17.4.2 TIM1 control register 2 (TIMx_CR2)
typedef union {
	struct {
		uint32_t CCPC:1;
		uint32_t :1;
		uint32_t CCUS:1;
		uint32_t CCDS:1;
		uint32_t MMS:3;
		uint32_t TI1S:1;
		uint32_t OIS1:1;
		uint32_t OIS1N:1;
		uint32_t OIS2:1;
		uint32_t OIS2N:1;
		uint32_t OIS3:1;
		uint32_t OIS3N:1;
		uint32_t OIS4:1;
		uint32_t :17;
	} bit;
	uint32_t reg;
} TIMx_CR2;

//17.4.3 TIMx slave mode control register (TIMx_SMCR)
typedef union {
	struct {
		uint32_t SMS:3;
		uint32_t OCCS:1;
		uint32_t TS:3;
		uint32_t MSM:1;
		uint32_t ETF:4;
		uint32_t ETPS:2;
		uint32_t ECE:1;
		uint32_t ETP:1;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_SMCR;

//17.4.4 TIMx DMA/interrupt enable register (TIMx_DIER)
typedef union {
	struct {
		uint32_t UIE:1;
		uint32_t CC1IE:1;
		uint32_t CC2IE:1;
		uint32_t CC3IE:1;
		uint32_t CC4IE:1;
		uint32_t COMIE:1;
		uint32_t TIE:1;
		uint32_t BIE:1;
		uint32_t UDE:1;
		uint32_t CC1DE:1;
		uint32_t CC2DE:1;
		uint32_t CC3DE:1;
		uint32_t CC4DE:1;
		uint32_t COMDE:1;
		uint32_t TDE:1;
		uint32_t :17;
	} bit;
	uint32_t reg;
} TIMx_DIER;

//17.4.5 TIMx status register (TIMx_SR)
typedef union {
	struct {
		uint32_t UIF:1;
		uint32_t CC1IF:1;
		uint32_t CC2IF:1;
		uint32_t CC3IF:1;
		uint32_t CC4IF:1;
		uint32_t COMIF:1;
		uint32_t TIF:1;
		uint32_t BIF:1;
		uint32_t :1;
		uint32_t CC1OF:1;
		uint32_t CC2OF:1;
		uint32_t CC3OF:1;
		uint32_t CC4OF:1;
		uint32_t :19;
	} bit;
	uint32_t reg;
} TIMx_SR;

//17.4.6 TIMx event generation register (TIMx_EGR)
typedef union {
	struct {
		uint32_t UG:1;
		uint32_t CC1G:1;
		uint32_t CC2G:1;
		uint32_t CC3G:1;
		uint32_t CC4G:1;
		uint32_t COMG:1;
		uint32_t TG:1;
		uint32_t BG:1;
		uint32_t :24;
	} bit;
	uint32_t reg;
} TIMx_EGR;

//17.4.7 TIMx capture/compare mode register 1 (TIMx_CCMR1)
typedef union {
	struct {
		uint32_t CC1S:2;
		uint32_t OC1FE:1;
		uint32_t OC1PE:1;
		uint32_t OC1M:3;
		uint32_t OC1CE:1;
		uint32_t CC2S:2;
		uint32_t OC2FE:1;
		uint32_t OC2PE:1;
		uint32_t OC2M:3;
		uint32_t OC2CE:1;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_CCMR1;

//17.4.8 TIMx capture/compare mode register 2 (TIMx_CCMR2)
typedef union {
	struct {
		uint32_t CC3S:2;
		uint32_t OC3FE:1;
		uint32_t OC3PE:1;
		uint32_t OC3M:3;
		uint32_t OC3CE:1;
		uint32_t CC4S:2;
		uint32_t OC4FE:1;
		uint32_t OC4PE:1;
		uint32_t OC4M:3;
		uint32_t OC4CE:1;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_CCMR2;

//17.4.9 TIMx capture/compare enable register (TIMx_CCER)
typedef union {
	struct {
		uint32_t CC1E:1;
		uint32_t CC1P:1;
		uint32_t CC1NE:1;
		uint32_t CC1NP:1;
		uint32_t CC2E:1;
		uint32_t CC2P:1;
		uint32_t CC2NE:1;
		uint32_t CC2NP:1;
		uint32_t CC3E:1;
		uint32_t CC3P:1;
		uint32_t CC3NE:1;
		uint32_t CC3NP:1;
		uint32_t CC4E:1;
		uint32_t CC4P:1;
		uint32_t CC4NE:1;
		uint32_t CC4NP:1;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_CCER;

//17.4.10 TIMx counter (TIMx_CNT)
typedef union {
	struct {
		uint32_t CNT:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_CNT;

//17.4.11 TIMx prescaler (TIMx_PSC)
typedef union {
	struct {
		uint32_t PSC:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_PSC;

//17.4.12 TIMx auto-reload register (TIMx_ARR)
typedef union {
	struct {
		uint32_t ARR:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_ARR;

//17.4.13 TIMx repetition counter register (TIMx_RCR)
typedef union {
	struct {
		uint32_t REP:8;
		uint32_t :24;
	} bit;
	uint32_t reg;
} TIMx_RCR;

//17.4.14 TIMx capture/compare register 1 (TIMx_CCR1)
typedef union {
	struct {
		uint32_t CCR1:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_CCR1;

//17.4.15 TIMx capture/compare register 2 (TIMx_CCR2)
typedef union {
	struct {
		uint32_t CCR2:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_CCR2;

//17.4.16 TIMx capture/compare register 3 (TIMx_CCR3)
typedef union {
	struct {
		uint32_t CCR3:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_CCR3;

//17.4.17 TIMx capture/compare register 4 (TIMx_CCR4)
typedef union {
	struct {
		uint32_t CCR4:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_CCR4;

//17.4.18 TIMx break and dead-time register (TIMx_BDTR)
typedef union {
	struct {
		uint32_t DTG:8;
		uint32_t LOCK:2;
		uint32_t OSSI:1;
		uint32_t OSSR:1;
		uint32_t BKE:1;
		uint32_t BKP:1;
		uint32_t AOE:1;
		uint32_t MOE:1;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_BDTR;

//17.4.19 TIMx DMA control register (TIMx_DCR)
typedef union {
	struct {
		uint32_t DBA:5;
		uint32_t :3;
		uint32_t DBL:5;
		uint32_t :19;
	} bit;
	uint32_t reg;
} TIMx_DCR;

//17.4.20 TIMx DMA address for full transfer (TIMx_DMAR)
typedef union {
	struct {
		uint32_t DMAB:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} TIMx_DMAR;


//Define the TIMER register structure
typedef struct
{
	//although registers are 16 bit wide if we look at the offsets they are spaced 4 bytes apart
	//so we define them as 32 bit but will only use the lower 16bits
	TIMx_CR1 CR1; //17.4.1 TIM1 control register 1 (TIM15_CR1)
	TIMx_CR2 CR2; //17.4.2 TIM1 control register 2 (TIM15_CR2)
	TIMx_SMCR SMCR; //17.4.3 TIM1 slave mode control register (TIM15_SMCR)
	TIMx_DIER DIER; //17.4.4 TIM1 DMA/interrupt enable register (TIM15_DIER)
	TIMx_SR SR; //17.4.5 TIM1 status register (TIM15_SR)
	TIMx_EGR EGR; //17.4.6 TIM1 event generation register (TIM15_EGR)
	TIMx_CCMR1 CCMR1; //17.4.7 TIM1 capture/compare mode register 1 (TIM15_CCMR1)
	TIMx_CCMR2 CCMR2; //17.4.8 TIM1 capture/compare mode register 2 (TIM15_CCMR2)
	TIMx_CCER CCER; //17.4.9 TIM1 capture/compare enable register (TIM15_CCER)
	TIMx_CNT CNT; //17.4.10 TIM1 counter (TIM15_CNT)
	TIMx_PSC PSC; //17.4.11 TIM1 prescaler (TIM15_PSC)
	TIMx_ARR ARR; //17.4.12 TIM1 auto-reload register (TIM15_ARR)
	TIMx_RCR RCR; //17.4.13 TIM1 repetition counter register (TIM15_RCR)
	TIMx_CCR1 CCR1; //17.4.14 TIM1 capture/compare register 1 (TIM15_CCR1)
	TIMx_CCR2 CCR2; //17.4.15 TIM1 capture/compare register 2 (TIM15_CCR2)
	TIMx_CCR3 CCR3; //17.4.16 TIM1 capture/compare register 1 (TIM15_CCR3)
	TIMx_CCR4 CCR4; //17.4.17 TIM1 capture/compare register 2 (TIM15_CCR4)
	TIMx_BDTR BDTR; //17.4.18 TIM1 break and dead-time register (TIM1_BDTR)
	TIMx_DCR DCR; //17.4.19 TIM1 DMA control register (TIM1_DCR)
	TIMx_DMAR DMAR; //17.4.20 TIM1 DMA address for full transfer (TIM1_DMAR)
} Timer_Type;

#define TIM1 ((volatile Timer_Type*)TIM1_BASE)
#define TIM3 ((volatile Timer_Type*)TIM3_BASE)
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

void setupPWMConfigurationOnboard(volatile Timer_Type* timer,
							unsigned int pwmPeriodCounter,
							unsigned int pwmPeriodPrescaler);

/*
 * Sets PWM duty cycle
  pwmDuty: value between 0 and ARR that will set a dutycycle from 0 to 100%
  channel: value between 0 and 3 that selects the channel to which the duty is applied
 */
void setPWMDuty(volatile Timer_Type* timer, unsigned int channel, unsigned int pwmDuty);

#endif //TIMER_H
