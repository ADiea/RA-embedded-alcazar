/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <system.h>
#include <gpio.h>
#include <delay.h>

//The Blue LED is on bit 8 of port C
#define LED_PIN 8

//define a led on delay time of 1s = 1000ms
#define LED_ON_TIME 100

//define a led on delay time of 0.5s = 500ms
#define LED_OFF_TIME 500

//This is the entry-point of our application.
//This is the "main" function for the project
// main is actually a convention we can use any function name, so we choose projectInit
int projectInit()
{
  enablePeripheral(ePerif_GPIOC, eEnabled);

  //TODO: replace with setPinMode(GPIOC, LED_PIN, ePin_Output);
  GPIOC->MODER |= ePin_Output << MODERPOS(LED_PIN); // Make bit 8 an output on GPIO C
  
  while(1)// Repeat the following forever
  {

	//TODO: replace with writePin(GPIOC, LED_PIN, 1);
    GPIOC->ODR |= (1<<LED_PIN);// set Bit 8 (turn on LED)
    
    busyDelayMs(LED_ON_TIME);
    
	//TODO: replace with writePin(GPIOC, LED_PIN, 0);
	GPIOC->ODR &= ~(1<<LED_PIN); // clear Bit 8 (turn off LED)
    
	busyDelayMs(LED_OFF_TIME);



  }
  
  //will never reach this point
  return 0;
}
