/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <system.h>
#include <gpio.h>

//The Blue LED is on bit 8 of port C
#define LED_PIN 8

//Define a convenien delay value. A formula could be setup to convert from CPU frequency to actual time units
#define DELAY_VALUE 500000

//This will keep the CPU busy in a loop thus creating a delay.
//This is the simplest way to implement a delay and is called busy-loop delay
//The disadvantage is that the CPU cannot do anything useful for the duration of the delay
//By taking into account the CPU frequency and how many instructions it takes to execute 
// the loop it is possible to determine a formula to calculate the number of cycles needed 
// for a given amount of time expressed in seconds or ms, us 
void delay(int dly)
{
// This is a simple software delay. It stays in the while loop until the dly variable reaches zero 
  while( dly--)
  {
	  ; //do nothing
  }
}

//This is the entry-point of our application. This fucntion is explicitly called (by a branch instruction)
// from within the statup.s file after a reset
int projectInit()
{
  RCC_AHBENR |= 1<<IOPC_EN; // Turn on the clock source for GPIO C
  GPIOC_MODER |= PORT_MODE_OUTPUT << MODER8; // Make bit 8 an output on GPIO C
  
  while(1)// Repeat the following forever
  {
    GPIOC_ODR |= (1<<LED_PIN);// set Bit 8 (turn on LED)
    
	delay(DELAY_VALUE);// Hang around for a bit
    
	GPIOC_ODR &= ~(1<<LED_PIN); // clear Bit 8 (turn off LED)
    
	delay(DELAY_VALUE);// Wait for a while again
  }
  
  //will never reach this point
  return 0;
} 

//Homework: 
//1. Modify the above example to blink the green led instead. Hint: look in the board manual to see on what pin the green led is connected.
//2. Make the LED to stay on 2 times more than off (on_time = 2 * off_time)
