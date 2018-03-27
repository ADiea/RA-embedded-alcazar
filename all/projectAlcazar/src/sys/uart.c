/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

//this file contains UART related functionality

#include <uart.h>

//will use USART2 by default

//setup UART communication with baudRate bits per second
void setupUART(unsigned int baudRate)
{

	/*
	 To figure out the value of the BRR register that sets the baudrate please see 27.5.4
	 baud = fCK / USARTDIV
	 => USARTDIV = fCK / baud

	 In our case fCK is 8Mhz and we also have an example in section 27.5.4
	--------------------------------
	Example 1
	To obtain 9600 baud with fCK = 8 MHz.
	• In case of oversampling by 16:
	USARTDIV = 8 000 000/9600
	BRR = USARTDIV = 833d = 0341h
	*/

	//todo define word lenth in CR1

	/* (1) Oversampling by 16, 9600 baud */
	/* (2) 8 data bit, 1 start bit, 1 stop bit, no parity */
	USART2->BRR = 8000000/9600;//8000000 / baudRate; /* (1) */
	USART2->CR1 = USART_CR1_TE | USART_CR1_UE; /* (2) */
	//USART2->CR1 = USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_UE; /* (2) */
}

//transmit a character
void txUARTch(char ch)
{
	USART2->TDR = ch;
	while(USART2->ISR & USART_ISR_TC)
	{
		;
	}
}
/*
//transmit a string
void txUARTstr(char *string)
{
	while(string && *string)
	{
		txUARTch(*string);
		string++;
	}
}
*/

//returns 1 if char received, and 0 if no char is available
//if a chracter was received it is found in outChar variable
unsigned char charReceivedUART(char* outChar)
{
	if(outChar)
	{
		if ((USART2->ISR & USART_ISR_RXNE))
		{
			*outChar = (char)(USART2->RDR); // Receive data, clear flag
			return 1;
		}
	}
	return 0;
}
