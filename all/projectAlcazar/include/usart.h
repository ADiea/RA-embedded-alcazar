/* STM32f0discovery embedded essentials project
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery]
*/

#ifndef INCLUDE_USART_H_
#define INCLUDE_USART_H_

#include "board.h"
//For USART functionality see chapter 27 especially 27.5.2, 27.5.3 and 27.5.4
//see section 2.2.2 table 1
#define USART2_BASE 0x40004400

#if __MSB_FIRST__

//27.8.1 Control register 1 (USART_CR1)
typedef union {
	struct {
		uint32_t :3;
		uint32_t M1:1;
		uint32_t EOBIE:1;
		uint32_t RTOIE:1;
		uint32_t DEAT:5;
		uint32_t DEDT:5;
		uint32_t OVER8:1;
		uint32_t CMIE:1;
		uint32_t MME:1;
		uint32_t M0:1;
		uint32_t WAKE:1;
		uint32_t PCE:1;
		uint32_t PS:1;
		uint32_t PEIE:1;
		uint32_t TXEIE:1;
		uint32_t TCIE:1;
		uint32_t RXNEIE:1;
		uint32_t IDLEIE:1;
		uint32_t TE:1;
		uint32_t RE:1;
		uint32_t UESM:1;
		uint32_t UE:1;
	} bit;
	uint32_t reg;
} USART_CR1;

//27.8.2 Control register 2 (USART_CR2)
typedef union {
	struct {
		uint32_t ADD:8;
		uint32_t RTOEN:1;
		uint32_t ABRMOD:2;
		uint32_t ABREN:1;
		uint32_t MSBFIRST:1;
		uint32_t DATAINV:1;
		uint32_t TXINV:1;
		uint32_t RXINV:1;
		uint32_t SWAP:1;
		uint32_t LINEN:1;
		uint32_t STOP:2;
		uint32_t CLKEN:1;
		uint32_t CPOL:1;
		uint32_t CPHA:1;
		uint32_t LBCL:1;
		uint32_t :1;
		uint32_t LBDIE:1;
		uint32_t LBDL:1;
		uint32_t ADDM7:1;
		uint32_t :4;
	} bit;
	uint32_t reg;
} USART_CR2;

//27.8.3 Control register 3 (USART_CR3)
typedef union {
	struct {
		uint32_t :9;

		uint32_t WUFIE:1;
		uint32_t WUS:2;
		uint32_t SCARCNT:3;
		uint32_t :1;

		uint32_t DEP:1;
		uint32_t DEM:1;
		uint32_t DDRE:1;
		uint32_t OVRDIS:1;
		uint32_t ONEBIT:1;
		uint32_t CTSIE:1;
		uint32_t CTSE:1;
		uint32_t RTSE:1;

		uint32_t DMAT:1;
		uint32_t DMAR:1;
		uint32_t SCEN:1;
		uint32_t NACK:1;
		uint32_t HDSEL:1;
		uint32_t IRLP:1;
		uint32_t IREN:1;
		uint32_t EIE:1;
	} bit;
	uint32_t reg;
} USART_CR3;

//27.8.4 Baud rate register (USART_BRR)
typedef union {
	struct {
		uint32_t :16;
		uint32_t BRR:16;
	} bit;
	uint32_t reg;
} USART_BRR;

//27.8.5 Guard time and prescaler register (USART_GTPR)
typedef union {
	struct {
		uint32_t :16;
		uint32_t GT:8;
		uint32_t PSC:8;
	} bit;
	uint32_t reg;
} USART_GTPR;

//27.8.6 Receiver timeout register (USART_RTOR)
typedef union {
	struct {
		uint32_t BLEN:8;
		uint32_t RTO:24;
	} bit;
	uint32_t reg;
} USART_RTOR;

//27.8.7 Request register (USART_RQR)
typedef union {
	struct {
		uint32_t :27;
		uint32_t TXFRQ:1;
		uint32_t RXFRQ:1;
		uint32_t MMRQ:1;
		uint32_t SBKRQ:1;
		uint32_t ABRRQ:1;
	} bit;
	uint32_t reg;
} USART_RQR;

//27.8.8 Interrupt and status register (USART_ISR)
typedef union {
	struct {
		uint32_t :9;
		uint32_t REACK:1;
		uint32_t TEACK:1;
		uint32_t WUF:1;
		uint32_t RWU:1;
		uint32_t SBKF:1;
		uint32_t CMF:1;
		uint32_t BUSY:1;
		uint32_t ABRF:1;
		uint32_t ABRE:1;
		uint32_t :1;
		uint32_t EOBF:1;
		uint32_t RTOF:1;
		uint32_t CTS:1;
		uint32_t CTSIF:1;
		uint32_t LBDF:1;
		uint32_t TXE:1;
		uint32_t TC:1;
		uint32_t RXNE:1;
		uint32_t IDLE:1;
		uint32_t ORE:1;
		uint32_t NF:1;
		uint32_t FE:1;
		uint32_t PE:1;
	} bit;
	uint32_t reg;
} USART_ISR;

//27.8.9 Interrupt flag clear register (USART_ICR)
typedef union {
	struct {
		uint32_t :11;
		uint32_t WUCF:1;
		uint32_t :2;
		uint32_t CMCF:1;
		uint32_t :4;
		uint32_t EOBCF:1;
		uint32_t RTOCF:1;
		uint32_t :1;
		uint32_t CTSCF:1;
		uint32_t LBDCF:1;
		uint32_t :1;
		uint32_t TCCF:1;
		uint32_t :1;
		uint32_t IDLECF:1;
		uint32_t ORECF:1;
		uint32_t NCF:1;
		uint32_t FECF:1;
		uint32_t PECF:1;
	} bit;
	uint32_t reg;
} USART_ICR;

//27.8.10 Receive data register (USART_RDR)
typedef union {
	struct {
		uint32_t reserved:23;
		uint32_t RDR:9;
	} bit;
	uint32_t reg;
} USART_RDR;

//27.8.11 Transmit data register (USART_TDR)
typedef union {
	struct {
		uint32_t reserved:23;
		uint32_t TDR:9;
	} bit;
	uint32_t reg;
} USART_TDR;

#else

//27.8.1 Control register 1 (USART_CR1)
typedef union {
	struct {
		uint32_t UE:1;
		uint32_t UESM:1;
		uint32_t RE:1;
		uint32_t TE:1;
		uint32_t IDLEIE:1;
		uint32_t RXNEIE:1;
		uint32_t TCIE:1;
		uint32_t TXEIE:1;
		uint32_t PEIE:1;
		uint32_t PS:1;
		uint32_t PCE:1;
		uint32_t WAKE:1;
		uint32_t M0:1;
		uint32_t MME:1;
		uint32_t CMIE:1;
		uint32_t OVER8:1;
		uint32_t DEDT:5;
		uint32_t DEAT:5;
		uint32_t RTOIE:1;
		uint32_t EOBIE:1;
		uint32_t M1:1;
		uint32_t :3;
	} bit;
	uint32_t reg;
} USART_CR1;

//27.8.2 Control register 2 (USART_CR2)
typedef union {
	struct {
		uint32_t :4;
		uint32_t ADDM7:1;
		uint32_t LBDL:1;
		uint32_t LBDIE:1;
		uint32_t :1;
		uint32_t LBCL:1;
		uint32_t CPHA:1;
		uint32_t CPOL:1;
		uint32_t CLKEN:1;
		uint32_t STOP:2;
		uint32_t LINEN:1;
		uint32_t SWAP:1;
		uint32_t RXINV:1;
		uint32_t TXINV:1;
		uint32_t DATAINV:1;
		uint32_t MSBFIRST:1;
		uint32_t ABREN:1;
		uint32_t ABRMOD:2;
		uint32_t RTOEN:1;
		uint32_t ADD:8;
	} bit;
	uint32_t reg;
} USART_CR2;

//27.8.3 Control register 3 (USART_CR3)
typedef union {
	struct {
		uint32_t EIE:1;
		uint32_t IREN:1;
		uint32_t IRLP:1;
		uint32_t HDSEL:1;
		uint32_t NACK:1;
		uint32_t SCEN:1;
		uint32_t DMAR:1;
		uint32_t DMAT:1;

		uint32_t RTSE:1;
		uint32_t CTSE:1;
		uint32_t CTSIE:1;
		uint32_t ONEBIT:1;
		uint32_t OVRDIS:1;
		uint32_t DDRE:1;
		uint32_t DEM:1;
		uint32_t DEP:1;

		uint32_t :1;
		uint32_t SCARCNT:3;
		uint32_t WUS:2;
		uint32_t WUFIE:1;

		uint32_t :9;
	} bit;
	uint32_t reg;
} USART_CR3;

//27.8.4 Baud rate register (USART_BRR)
typedef union {
	struct {
		uint32_t BRR:16;
		uint32_t :16;
	} bit;
	uint32_t reg;
} USART_BRR;

//27.8.5 Guard time and prescaler register (USART_GTPR)
typedef union {
	struct {
		uint32_t PSC:8;
		uint32_t GT:8;
		uint32_t :16;
	} bit;
	uint32_t reg;
} USART_GTPR;

//27.8.6 Receiver timeout register (USART_RTOR)
typedef union {
	struct {
		uint32_t RTO:24;
		uint32_t BLEN:8;
	} bit;
	uint32_t reg;
} USART_RTOR;

//27.8.7 Request register (USART_RQR)
typedef union {
	struct {
		uint32_t ABRRQ:1;
		uint32_t SBKRQ:1;
		uint32_t MMRQ:1;
		uint32_t RXFRQ:1;
		uint32_t TXFRQ:1;
		uint32_t :27;
	} bit;
	uint32_t reg;
} USART_RQR;

//27.8.8 Interrupt and status register (USART_ISR)
typedef union {
	struct {
		uint32_t PE:1;
		uint32_t FE:1;
		uint32_t NF:1;
		uint32_t ORE:1;
		uint32_t IDLE:1;
		uint32_t RXNE:1;
		uint32_t TC:1;
		uint32_t TXE:1;
		uint32_t LBDF:1;
		uint32_t CTSIF:1;
		uint32_t CTS:1;
		uint32_t RTOF:1;
		uint32_t EOBF:1;
		uint32_t :1;
		uint32_t ABRE:1;
		uint32_t ABRF:1;
		uint32_t BUSY:1;
		uint32_t CMF:1;
		uint32_t SBKF:1;
		uint32_t RWU:1;
		uint32_t WUF:1;
		uint32_t TEACK:1;
		uint32_t REACK:1;
		uint32_t :9;
	} bit;
	uint32_t reg;
} USART_ISR;

//27.8.9 Interrupt flag clear register (USART_ICR)
typedef union {
	struct {
		uint32_t PECF:1;
		uint32_t FECF:1;
		uint32_t NCF:1;
		uint32_t ORECF:1;
		uint32_t IDLECF:1;
		uint32_t :1;
		uint32_t TCCF:1;
		uint32_t :1;
		uint32_t LBDCF:1;
		uint32_t CTSCF:1;
		uint32_t :1;
		uint32_t RTOCF:1;
		uint32_t EOBCF:1;
		uint32_t :4;
		uint32_t CMCF:1;
		uint32_t :2;
		uint32_t WUCF:1;
		uint32_t :11;
	} bit;
	uint32_t reg;
} USART_ICR;

//27.8.10 Receive data register (USART_RDR)
typedef union {
	struct {
		uint32_t RDR:9;
		uint32_t reserved:23;
	} bit;
	uint32_t reg;
} USART_RDR;

//27.8.11 Transmit data register (USART_TDR)
typedef union {
	struct {
		uint32_t TDR:9;
		uint32_t reserved:23;
	} bit;
	uint32_t reg;
} USART_TDR;

#endif

typedef struct
{
	USART_CR1 CR1; //27.8.1 Control register 1 (CR1)
	USART_CR2 CR2; //27.8.2 Control register 2 (CR2)
	USART_CR3 CR3; //27.8.3 Control register 3 (CR3)
	USART_BRR BRR; //27.8.4 Baud rate register (BRR)
	USART_GTPR GTPR; //27.8.5 Guard time and prescaler register (GTPR)
	USART_RTOR RTOR; //27.8.6 Receiver timeout register (RTOR)
	USART_RQR RQR; //27.8.7 Request register (RQR)
	USART_ISR ISR; //27.8.8 Interrupt and status register (ISR)
	USART_ICR ICR; //27.8.9 Interrupt flag clear register (ICR)
	USART_RDR RDR; //27.8.10 Receive data register (RDR)
	USART_TDR TDR; //27.8.11 Transmit data register (TDR)
} USART_Type;

#define USART2 ((volatile USART_Type*)USART2_BASE)

//setup USART communication with baudRate bits per second
void setupUSART(unsigned int baudRate);

//transmit a character
void txUSARTch(char ch);
/*
//transmit a string
void txUSARTstr(char *string);

//returns 1 if char received, and 0 if no char is available
//if a chracter was received it is found in outChar variable
unsigned char charReceivedUSART(char* outChar);
*/
#endif /* INCLUDE_USART_H_ */
