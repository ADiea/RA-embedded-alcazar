/* STM32f0discovery simple blink example
 Author: Andrei Diea (github.com/ADiea)
 Based on work by Frank Duignan [http://eleceng.dit.ie/frank/arm/BareMetalSTM32F0Discovery/blinky.html]
 */

		.thumb /*Cortex micros only understand thumb(2) code	*/
		.global Vector_Table, ResetVector	
/* Set up interrupt vector table */
		.text
Vector_Table:    
		.word     0x20002000          /* Top of Stack */
/* The interrupt vectors that follow are manually forced to be aligned along
   odd addresses.  The reason for this is that the address for a Thumb instruction
   must always have its LSB set to 1.  This does not mean that the instruction 
   is stored at an odd number address.  The LSB is used as a flag to indicate
   that an ARM (LSB=0) or a Thumb (LSB=1) instruction is being addressed. */

ResetVector:    .word     Reset_Handler+1     /* Reset Handler */
                .word     Default_Handler+1   /* NMI */
                .word     Default_Handler+1   /* Hard Fault */
                .word     0                   /* Reserved */
                .word     0                   /* Reserved */
                .word     0                   /* Reserved */
                .word     0                   /* Reserved */
                .word     0                   /* Reserved */
                .word     0                   /* Reserved */
                .word     0                   /* Reserved */
                .word     Default_Handler+1   /* SVC */
                .word     0                   /* Reserved */
                .word     0                   /* Reserved */
                .word     Default_Handler+1   /* PendSV */
                .word     Default_Handler+1   /* SysTick */
		
/* External interrupt handlers follow */
		.word	  Default_Handler + 1 /* WWDG */
		.word	  Default_Handler + 1 /* PVD */
		.word	  Default_Handler + 1 /* RTC */
		.word	  Default_Handler + 1 /* FLASH */
 		.word	  Default_Handler + 1 /* RCC */
		.word	  Default_Handler + 1 /* EXTI0_1 */
		.word	  Default_Handler + 1 /* EXTI2_3 */
		.word	  Default_Handler + 1 /* EXTI4_15 */
		.word	  Default_Handler + 1 /* TSC */
		.word	  Default_Handler + 1 /* DMA_CH1 */
		.word	  Default_Handler + 1 /* DMA_CH2_3 */
		.word	  Default_Handler + 1 /* DMA_CH4_5 */
		.word	  Default_Handler + 1 /* ADC_COMP */
		.word	  Default_Handler +1  /* TIM1_BRK_UP_TRG_COM */
		.word	  Default_Handler + 1 /* TIM1_CC */
		.word	  Default_Handler + 1 /* TIM2 */
		.word	  Default_Handler + 1 /* TIM3 */
		.word	  Default_Handler + 1 /* TIM6_DAC */
		.word	  Default_Handler + 1 /* RESERVED */
		.word	  Default_Handler + 1 /* TIM14 */
		.word	  Default_Handler + 1 /* TIM15 */
  		.word	  Default_Handler + 1 /* TIM16 */
		.word	  Default_Handler + 1 /* TIM17 */
		.word	  Default_Handler + 1 /* I2C1 */
		.word	  Default_Handler + 1 /* I2C2 */
		.word	  Default_Handler + 1 /* SPI1 */
		.word	  Default_Handler + 1 /* SPI2 */
		.word	  Default_Handler + 1 /* USART1 */
		.word	  Default_Handler + 1 /* USART2 */
		.word	  Default_Handler + 1 /* RESERVED */
		.word	  Default_Handler + 1 /* CEC */
 		.word	  Default_Handler + 1 /* RESERVED */

/* Reset handler - this is called immediately after power is applied */
		.thumb
Reset_Handler:
	.global Reset_Handler, Default_Handler
    .extern  main
/* Stack pointer is already set to the value at entry 0 in the interrupt vector table  */
/* Clock speed is set by default to the internal factory calibrated 8MHz RC oscillator */
/* The PLL is configured to run at twice the RC clock speed so the default system      */
/* operating speed is 16MHz							       */
/* All that is left to do is to call main					       */
		bl	main
		b	.	/* If main returns enter a loop */
Default_Handler:
		b       .	/* Default handler just enters a loop.  Note the dot */
