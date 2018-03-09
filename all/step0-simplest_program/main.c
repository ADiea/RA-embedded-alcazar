/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery/blinky.html]
 Flashes the blue LED on the STM32F0Disovery board 

The application's task is to blink the blue led. By looking in the [STM32F0Discovery Board User Manual.pdf] document
we see that the Blue LED is connected to the PC8 pin this is (PORTC C, PIN 8)
In order to blink the led we have to do the following
1. enable the PORTC clock so that the portC subsystem will operate
2. configure pin 8 from portC as an output
3. turn on the LED. Wait a certain amount of time. Turn off the LED. wait a certain amount of time and repeat

For understanding the following declarations
Please see the document [STM32F051C8 Datasheet.pdf] section 3.7 
					and	[STM32F0 Reference Manual.pdf] sections 
					section 2.2.2, table, bus AHB1 => 0x40021000  RCC
					section 6.4.6 RCC_AHBENR note the offset from the RCC base which is 0x14
*/

//Let's include the architecture defines. This way we will have access to all the register adresses needed
//for controlling the pins
#include "stm32f0_architecture.h"

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
int main()
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
