/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <system.h>
#include <gpio.h>
#include <delay.h>
#include <timer.h>

//The Blue LED is on bit 8 of port C
#define LED_PIN 8

//define a led on delay time of 1s = 1000ms
#define LED_ON_TIME 100

//define a led on delay time of 0.5s = 500ms
#define LED_OFF_TIME 500

//let's define how to connect the RGB led pins to the MCU
//because we decided we'll use TIMER 1 for pwm generation,
//we search the datasheet to see on what pins the outputs of TIM1 are located
//We find that they are on PA8 PA9 and PA10,
//Next we choose(convention) what color should be on which pin
#define LED_RGB_RED 10
#define LED_RGB_GREEN 9
#define LED_RGB_BLUE 8

//Also we should define which PWM channel corresponds to what color
//For ex CH1 corresponds to PA8 which we defined as BLUE
#define LED_RGB_RED_CH 2
#define LED_RGB_GREEN_CH 1
#define LED_RGB_BLUE_CH 0

void initPWMrgbLED(void)
{
	//We'll use first three output compare channels from timer1 to output 3 PWM
	//signals for our rgb led. If we look in the datasheet section 4 table 13
	//we see that pins PA8 PA9 and PA10 have alternate functions TIM1_CH1,
	//TIM1_CH2 and TIM1_CH3
	//Next if we look in the following table, table 14 we see that for PA8 PA9 and PA10
	//TIM1_CHx channels are mapped on alternate function 2 (AF2)

	//enable GPIOA peripheral to have access to PA8, PA9 and PA10
	enablePeripheral(ePerif_GPIOA, eEnabled);

	//setup alternate functions for the three pins
	//After this step, value of the three pins are
	//no longer controlled by the OutputDataRegister like a normal GPIO pin, but by timer 1
	setPinAlternateFunction(GPIOA, LED_RGB_RED, ePin_AF2);
	setPinAlternateFunction(GPIOA, LED_RGB_GREEN, ePin_AF2);
	setPinAlternateFunction(GPIOA, LED_RGB_BLUE, ePin_AF2);

	//enable timer 1 to use it as hardware PWM generator
	enablePeripheral(ePerif_TIM1, eEnabled);

	//we setup pwm on first 3 channels for timer1.
	//Please see function implementation in timer.c
	/*
	 Prescaler is set to 799 clock is divided by 799+1 = 800 => timer counts with 10kHz frequency

	 We set the autoload value to 100 means that counter counts to 100 then restarts from zero
	 If timer counts with 10kHz, means that timer counts to 100 once every 10ms, or 100 times per second
	 This means that PWM period is 0.01s, or we can say PWM frequency is 1/0.01s = 100Hz

	 The duty cycle is from zero to ARR and we set the ARR to 100 so we can directly set the cycle
	 from 0% to 100% by setting the value from 0 to 100

	 Initially dutycycle is set to zero, so all 3 channels will be 0
	 */
	setupPWMConfiguration(TIM1, 100, 799);

	/*[Homework]
	 Pins PC8 and PC9 which have our onboard green and blue leds
		connected are also connected to TIM3_CH3 and TIM3_CH4
	 Make another function in timer.c that activates only last 2 channels
		ch3 and ch4 as PWM outputs and use it to control onboard green
		and blue led as seen in this example
	 */

}

//This is the entry-point of our application.
//This is the "main" function for the project
// main is actually a convention we can use any function name, so we choose projectInit
int projectInit(void)
{
  enablePeripheral(ePerif_GPIOC, eEnabled);

  //TODO: replace with setPinMode(GPIOC, LED_PIN, ePin_Output);
  GPIOC->MODER |= ePin_Output << MODERPOS(LED_PIN); // Make bit 8 an output on GPIO C
  
  initPWMrgbLED();

  int state = 0, i=0;

  while(1)// Repeat the following forever
  {

	//TODO: replace with writePin(GPIOC, LED_PIN, 1);
    GPIOC->ODR |= (1<<LED_PIN);// set Bit 8 (turn on LED)
    
    busyDelayMs(LED_ON_TIME);
    
	//TODO: replace with writePin(GPIOC, LED_PIN, 0);
	GPIOC->ODR &= ~(1<<LED_PIN); // clear Bit 8 (turn off LED)
    
	busyDelayMs(LED_OFF_TIME);

	//we make a "game" by enabling different color transitions depending on a state variable
	switch(state)
	{
		case 0: //ramp up red color
			for(i=0; i<=100; i++)
			{
				setPWMDuty(TIM1, LED_RGB_RED_CH, i);
				busyDelayMs(10);
			}
			break;
		case 1: //ramp up green while keeping red at 100%
			for(i=0; i<=100; i++)
			{
				setPWMDuty(TIM1, LED_RGB_GREEN_CH, i);
				busyDelayMs(10);
			}
			break;
		case 2://ramp up blue channel while keeping red and green at maximum from previous state
			for(i=0; i<=100; i++)
			{
				setPWMDuty(TIM1, LED_RGB_BLUE_CH, i);
				busyDelayMs(10);
			}
			break;
		case 3://ramp down all 3 channels slowly in 5 seconds to turn off the led
			for(i=100; i>=0; i--)
			{
				setPWMDuty(TIM1, LED_RGB_RED_CH, i);
				setPWMDuty(TIM1, LED_RGB_GREEN_CH, i);
				setPWMDuty(TIM1, LED_RGB_BLUE_CH, i);
				busyDelayMs(50);
			}
			break;
		case 4:
			for(i=0; i<=100; i++)
			{
				setPWMDuty(TIM1, LED_RGB_RED_CH, i);
				setPWMDuty(TIM1, LED_RGB_BLUE_CH, i);
				busyDelayMs(10);
			}
			break;
		case 5: //ramp up blue while ramping down blue in 3 seconds (30*100 ms)
			for(i=0; i<=100; i++)
			{
				setPWMDuty(TIM1, LED_RGB_GREEN_CH, i);
				setPWMDuty(TIM1, LED_RGB_BLUE_CH, 100 - i);
				busyDelayMs(30);
			}
			break;
		default:
			//reset state to start over the game
			state = -1;
			break;
	};

	state++;
  }
  
  //will never reach this point
  return 0;
}
