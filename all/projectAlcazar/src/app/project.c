/* STM32f0discovery embedded essentials course project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <system.h>
#include <gpio.h>
#include <delay.h>
#include <timer.h>
#include <spi.h>
#include <max7219.h>
#include <usart.h>



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

//These pins are alternate function for SPI1 peripheral on port A
//we will not use these pins directly, the SPI peripheral will use them for communication
#define SPI1_NSS_PIN 4
#define SPI1_SCK_PIN 5
#define SPI1_MISO_PIN 6
#define SPI1_MOSI_PIN 7

//USART1 on PORTA
#define USART2_TX 2
#define USART2_RX 3


void initSegmentDisplayHardwareSPI(void)
{
	//we will attach a LED segment display based on MAX7219 chip
	//(see documentation folder for the datasheet)
	//The MAX7219 can be controlled via the SPI communication protocol
	//It then directly controls the LED display

	//enable the SPI peripheral inside the MCU to help with the SPI communication
	enableAPB2Peripheral(ePerif_SPI1, eEnabled);

	//configure pins on the MCU as special SPI pins (alternate functions)
	//see the datasheet of STM32f0 (Table 14. Alternate functions selected through GPIOA_AFR registers for port A)
	//the pins we are interested are
	/*
		PA4 SPI1_NSS Slave select, will be output, alternate function 0
		PA5 SPI1_SCK Clock signal will be output (clock is generated by mcu) alternate function zero
		PA6 SPI1_MISO Master in slave out, will be input, but we will not read anything from the display so we ignore it
		PA7 SPI1_MOSI Master out slave in output the MCU will send commands Alternate function 0
	 * */
	//enable GPIOA peripheral to have access to PA 4,5,6,7
	enableAHBPeripheral(ePerif_GPIOA, eEnabled);

	//setPinAlternateFunction(GPIOA, SPI1_NSS_PIN, ePin_AF0);
	setPinAlternateFunction(GPIOA, SPI1_SCK_PIN, ePin_AF0);
	setPinAlternateFunction(GPIOA, SPI1_MISO_PIN, ePin_AF0);
	setPinAlternateFunction(GPIOA, SPI1_MOSI_PIN, ePin_AF0);

	GPIOA->MODER.reg |= ePin_Output << MODERPOS(SPI1_SCK_PIN);
	GPIOA->MODER.reg |= ePin_Output << MODERPOS(SPI1_MOSI_PIN);

	//we will manually toggle the SS pin
	GPIOA->MODER.reg |= ePin_Output << MODERPOS(SPI1_NSS_PIN);
	GPIOA->ODR.reg |= (1<<SPI1_NSS_PIN);

	//configure the SPI1 peripheral
	initSPIMaster(SPI1);

	//init the MAX7219 device by sending specific commands
	initMAX7219Display(SPI1);
}

void initSegmentDisplaySoftwareSPI(void)
{
	//we will attach a LED segment display based on MAX7219 chip
	//(see documentation folder for the datasheet)
	//The MAX7219 can be controlled via the SPI communication protocol
	//It then directly controls the LED display

	//We will use software SPI where we control the GPIO pins in software
	//Will we use the following pins which are the same as SPI1 pins but this is not important
	//(!) With software SPI we can use ANY pins since we control them in software
	/*
		PA4 NSS Slave select, will be output
		PA5 SCK Clock signal will be output (clock is generated by mcu)
		PA6 MISO Master in slave out, will be input, but we will not read anything from the display so we ignore it
		PA7 MOSI Master out slave in output the MCU will send commands
	 * */

	//enable GPIOA peripheral to have access to PA 4,5,6,7
	enableAHBPeripheral(ePerif_GPIOA, eEnabled);

	//configure the GPIO pins for software SPI
	spiSoftSetup(GPIOA, SPI1_NSS_PIN, SPI1_SCK_PIN, SPI1_MOSI_PIN, SPI1_MISO_PIN);

	//init the MAX7219 device by sending specific commands
	initMAX7219Display(0);
}

void initPWMrgbLED(void)
{
	//We'll use first three output compare channels from timer1 to output 3 PWM
	//signals for our rgb led. If we look in the datasheet section 4 table 13
	//we see that pins PA8 PA9 and PA10 have alternate functions TIM1_CH1,
	//TIM1_CH2 and TIM1_CH3
	//Next if we look in the following table, table 14 we see that for PA8 PA9 and PA10
	//TIM1_CHx channels are mapped on alternate function 2 (AF2)

	//enable GPIOA peripheral to have access to PA8, PA9 and PA10
	enableAHBPeripheral(ePerif_GPIOA, eEnabled);

	//setup alternate functions for the three pins
	//After this step, value of the three pins are
	//no longer controlled by the OutputDataRegister like a normal GPIO pin, but by timer 1
	setPinAlternateFunction(GPIOA, LED_RGB_RED, ePin_AF2);
	setPinAlternateFunction(GPIOA, LED_RGB_GREEN, ePin_AF2);
	setPinAlternateFunction(GPIOA, LED_RGB_BLUE, ePin_AF2);

	//enable timer 1 to use it as hardware PWM generator
	enableAPB2Peripheral(ePerif_TIM1, eEnabled);

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

void initUSART2(void)
{
	//enable GPIOA peripheral to have access to PA2 PA3
	enableAHBPeripheral(ePerif_GPIOA, eEnabled);

	//setup alternate functions for the three pins
	//After this step, value of the three pins are
	//no longer controlled by the OutputDataRegister like a normal GPIO pin, but by usart2
	setPinAlternateFunction(GPIOA, USART2_TX, ePin_AF1);
	setPinAlternateFunction(GPIOA, USART2_RX, ePin_AF1);

	//enable USART2 to use it as hardware PWM generator
	enableAPB1Peripheral(ePerif_USART2, eEnabled);

	//setup usart peripheral
	setupUSART(9600);
}

//This is the entry-point of our application.
//This is the "main" function for the project
// main is actually a convention we can use any function name, so we choose projectInit
int projectInit(void)
{
  enableAHBPeripheral(ePerif_GPIOC, eEnabled);

  setPinMode(GPIOC, LED_PIN, ePin_Output);  // Make bit 8 an output on GPIO C
  
  initPWMrgbLED();

  //initSegmentDisplay();
  initSegmentDisplaySoftwareSPI();

  initUSART2();

  int state = 0, i=0;

  while(1)// Repeat the following forever
  {
	writePin(GPIOC, LED_PIN, 1); // set Bit 8 (turn on LED)
    busyDelayMs(LED_ON_TIME);
    
    writePin(GPIOC, LED_PIN, 0);  // clear Bit 8 (turn off LED)
	busyDelayMs(LED_OFF_TIME);

	txUSARTch('s');
	txUSARTch(state + '0');
	txUSARTch(' ');

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

			//also clear the display
			clearDisplay();
			break;
	};

	state++;

	//display current state to the MAX7219 connected display to position state
	putChar((char)state, //print state value
				(unsigned char)state); //print it to the 'state' position

  }
  
  //will never reach this point
  return 0;
}
