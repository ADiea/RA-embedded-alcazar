/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#include <system.h>

//declare the extern projectInit() function. Will be called after system is init
extern void projectInit();

void enablePeriferal(ePeripherals which, eEnableState enable)
{
	unsigned int *pEnableRegister;
	unsigned int enableMask
	switch(which)
	{
	
	};
}

void systemInit()
{
	//init the system

	//after system is inited, call the projectInit 
	projectInit();
}
