/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

//For USART functionality see chapter 27 especially 27.5.2, 27.5.3 and 27.5.4
//see section 2.2.2 table 1
#define USART2_BASE 0x40004400

typedef struct
{
	unsigned int CR1; //27.8.1 Control register 1 (CR1)
	unsigned int CR2; //27.8.2 Control register 2 (CR2)
	unsigned int CR3; //27.8.3 Control register 3 (CR3)
	unsigned int BRR; //27.8.4 Baud rate register (BRR)
	unsigned int GTPR; //27.8.5 Guard time and prescaler register (GTPR)
	unsigned int RTOR; //27.8.6 Receiver timeout register (RTOR)
	unsigned int RQR; //27.8.7 Request register (RQR)
	unsigned int ISR; //27.8.8 Interrupt and status register (ISR)
	unsigned int ICR; //27.8.9 Interrupt flag clear register (ICR)
	unsigned int RDR; //27.8.10 Receive data register (RDR)
	unsigned int TDR; //27.8.11 Transmit data register (TDR)
}USART_Type;

#define USART2 ((volatile USART_Type*)USART2_BASE)


#define USART_CR1_TE (1<<3) //transmitter submodule enable
#define USART_CR1_RE (1<<2)//receiver submodule enable
#define USART_CR1_UE (1<<0)//usart module(peripheral) enable
#define USART_ISR_TC (1<<6)//transmission is completed, we can transmit another ch
#define USART_ISR_RXNE (1<<5)//rdr register has valid character

//setup UART communication with baudRate bits per second
void setupUART(unsigned int baudRate);

//transmit a character
void txUARTch(char ch);
/*
//transmit a string
void txUARTstr(char *string);

//returns 1 if char received, and 0 if no char is available
//if a chracter was received it is found in outChar variable
unsigned char charReceivedUART(char* outChar);
*/
#endif /* INCLUDE_UART_H_ */
