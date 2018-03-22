/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/
#include <spisoft.h>
#include <delay.h>

//We implement a master soft SPI

//remember these for later use
volatile GPIO_Type * gSPIport;
volatile unsigned char gPinSS, gPinSCK, gPinMOSI, gPinMISO;

/*
 * Setsup GPIO pins fopr a software SPI
 * */
void spiSoftSetup(volatile GPIO_Type * port,
				  unsigned char pinSS,   //slave select pin
				  unsigned char pinSCK,  //clock signal pin
				  unsigned char pinMOSI, //master out slave in pin
				  unsigned char pinMISO //master in slave out pin
				  )
{
	if(!port)
		return;

	gSPIport = port;
	gPinSS = pinSS;
	gPinSCK = pinSCK;
	gPinMOSI = pinMOSI;
	gPinMISO = pinMISO;

	setPinMode(gSPIport, pinSS, ePin_Output); //configure ss as output
	writePin(gSPIport, pinSS, 1); //set to high to disable peripheral

	setPinMode(gSPIport, pinSCK, ePin_Output);
	writePin(gSPIport, pinSCK, 0); //set clock to zero. This usually depends on how you want SPI configured. Should be configurable.

	setPinMode(gSPIport, pinMOSI, ePin_Output); //we don't care to set a value because peripheral is disabled

	setPinMode(gSPIport, pinMISO, ePin_Input);

}

//Before 'talking' to the slave we must enable it by pulling the SS line low
void spiSoftEnableSlave(unsigned char enable)
{
	//by using ! enable we will send zero when enable is 1 => enable the slave
	//and send 1 when enable is zero => disable the slave
	writePin(gSPIport, gPinSS, !enable);
}

//send a byte to the slave using the SPI in software (known also as bit banging)
void spiSoftSendByte(unsigned char byte)
{
	unsigned char i=0;
	//we will send the 8 bits MSB first. This should be configurable

	//the slave should be already enabled by calling the enableSlave first

	//we will design this funciton explicitly for the max7219 slave device
	//hence we study its datasheet and take care to respect the TIMINGS
	//Figure 1. Timing diagram
	//tDS = tCSS 25ns => 1ms should be enough
	//tCL = tCH = 50 ns => T CL(tCP=tCL+tCH) = 100ns = 0.1ms => 1ms per clock VALUE delay should be enough (20x more)

	for(i=7; i>=0; i--)
	{
		//set the MOSI line based on current bit
		writePin(gSPIport, gPinMOSI, byte & (1<<i));

		//give time to settle
		busyDelayMs(1);

		//rise clock line; peripheral max7219 will sample on clock rising edge
		writePin(gSPIport, gPinSCK, 1);

		//keep clock in '1' for 1ms
		busyDelayMs(1);

		//drop clock line
		writePin(gSPIport, gPinSCK, 0);
	}
	//at the end clock will be low
}
