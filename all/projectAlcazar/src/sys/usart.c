/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

//this file contains USART related functionality

#include <usart.h>

//will use USART2 by default

//setup USART communication with baudRate bits per second
void setupUSART(unsigned int baudRate)
{

	USART2->BRR.reg = 8000000/9600;
	USART2->CR1.bit.TE = 1;
	USART2->CR1.bit.UE = 1;

	//USART2->CR1 = USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_UE; /* (2) */
}

//transmit a character
void txUSARTch(char ch)
{
	USART2->TDR.bit.TDR = ch;
	while(USART2->ISR.bit.TC)
	{
		;
	}
}


//returns 1 if char received, and 0 if no char is available
//if a chracter was received it is found in outChar variable
unsigned char charReceivedUSART(char* outChar)
{
	if(outChar)
	{
		if (USART2->ISR.bit.RXNE)
		{
			*outChar = (char)(USART2->RDR.bit.RDR); // Receive data, clear flag
			return 1;
		}
	}
	return 0;
}
