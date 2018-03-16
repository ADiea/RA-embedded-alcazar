/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/
#include <timer.h>

//sets the timer counter register to value. value must be max 65535 (16bits)
void setTimerCounter(eTimerPeripheral timer, unsigned int value)
{
	switch(timer)
	{
		case eTimer_TIM1:
			TIM1->CNT = value & 0xFFFF; //force the value given to be max 65535
			break;
		case eTimer_TIM15:
			TIM15->CNT = value & 0xFFFF; //force the value given to be max 65535
			break;
	};
}

//sets timer prescaler. a prescaler of 2 divides the cpu clk by 2
//making the counter count 2 times slower than cpu frequency
void setTimerPrescaler(eTimerPeripheral timer, unsigned int value)
{
	//TODO: implement function based on reference manual
}

//stops the timer from counting
void stopTimer(eTimerPeripheral timer)
{
	switch(timer)
	{
		case eTimer_TIM1:
			TIM1->CR1 &= ~(1<<TIM_CEN);
			break;
		case eTimer_TIM15:
			TIM15->CR1 &= ~(1<<TIM_CEN);
			break;
	};
}

//start the timer to count in the up or down direction
void startTimer(eTimerPeripheral timer, eTimerDirection direction)
{
	switch(timer)
	{
		case eTimer_TIM1:
			//first clear the direction bit
			TIM1->CR1 &= ~(1<<TIM_DIR);
			//then set together the enable and direction bits
			TIM1->CR1 |= (1<<TIM_CEN) | (direction<<TIM_DIR);
			break;
		case eTimer_TIM15:
			//first clear the direction bit
			TIM15->CR1 &= ~(1<<TIM_DIR);
			//then set together the enable and direction bits
			TIM15->CR1 |= (1<<TIM_CEN) | (direction<<TIM_DIR);
			break;
	};
}

//reads the timer counter register value, which is the value the timer has counted to until now
unsigned int getTimerValue(eTimerPeripheral timer)
{
	unsigned int value;
	switch(timer)
	{
		case eTimer_TIM1:
			value = TIM1->CNT;
			break;
		case eTimer_TIM15:
			value = TIM15->CNT;
			break;
	};

	return value;
}
