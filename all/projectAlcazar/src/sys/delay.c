/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <delay.h>
#include <timer.h>
#include <system.h>

//#define TIMER_COUNT_PER_MS (CPU_FREQ / 1000)

//delay for ms miliseconds. keeps the cpu busy
//this function uses the TIM15 timer to measure time
//Read more about the TIM15 timer in section 20 of the reference manual
void busyDelayMs(unsigned int ms)
{
	//enable timer 15
	enablePeripheral(ePerif_TIM15, eEnabled);

	unsigned int value;

	//for every milisecond
	while(ms--)
	{
		//must wait for 1ms

		//first stop the timer in case it is counting
		stopTimer(TIM15);

		//set counter to zero
		setTimerCounter(TIM15, 0);

		//set prescaler 1 so counter will count using
		//the same frequency as the cpu, undivided
		setTimerPrescaler(TIM15, 0);

		//start counting up
		startTimer(TIM15, eTimerDirection_Up);

		// wait for timer to reach TIMER_COUNT_PER_MS
		while(1)
		{
			value = getTimerValue(TIM15);
			if(value >   TIMER_COUNT_PER_MS)
			{
				break;
			}
		}
	}
	//disable timer 15
	enablePeripheral(ePerif_TIM15, eDisabled);
}
