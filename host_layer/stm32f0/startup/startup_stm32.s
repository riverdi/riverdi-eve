/**
  ******************************************************************************
  * @file      startup_stm32.s dedicated to STM32F031C6Tx device
  * @author    Ac6
  * @version   V1.0.0
  * @date      2018-07-25
  ******************************************************************************
  */

.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The STM32F031C6Tx vector table.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word	0
  .word	0
  .word	0
  .word	0
  .word	0
  .word	0
  .word	0
  .word	SVC_Handler
  .word	0
  .word	0
  .word	PendSV_Handler
  .word	SysTick_Handler
  .word	WWDG_IRQHandler                       			/* Window Watchdog interrupt                                         */
  .word	PVD_IRQHandler                        			/* PVD and VDDIO2 supply comparator interrupt                        */
  .word	RTC_IRQHandler                        			/* RTC interrupts                                                    */
  .word	FLASH_IRQHandler                      			/* Flash global interrupt                                            */
  .word	RCC_CRS_IRQHandler                    			/* RCC and CRS global interrupts                                     */
  .word	EXTI0_1_IRQHandler                    			/* EXTI Line[1:0] interrupts                                         */
  .word	EXTI2_3_IRQHandler                    			/* EXTI Line[3:2] interrupts                                         */
  .word	EXTI4_15_IRQHandler                   			/* EXTI Line15 and EXTI4 interrupts                                  */
  .word	TSC_IRQHandler                        			/* Touch sensing interrupt                                           */
  .word	DMA1_CH1_IRQHandler                   			/* DMA1 channel 1 interrupt                                          */
  .word	DMA1_CH2_3_DMA2_CH1_2_IRQHandler      			/* DMA1 channel 2 and 3 and DMA2 channel 1 and 2 interrupt           */
  .word	DMA1_CH4_5_6_7_DMA2_CH3_4_5_IRQHandler			/* DMA1 channel 4, 5, 6 and 7 and DMA2 channel 3, 4 and 5 interrupts */
  .word	ADC_COMP_IRQHandler                   			/* ADC and comparator interrupts                                     */
  .word	TIM1_BRK_UP_TRG_COM_IRQHandler        			/* TIM1 break, update, trigger and commutation interrupt             */
  .word	TIM1_CC_IRQHandler                    			/* TIM1 Capture Compare interrupt                                    */
  .word	TIM2_IRQHandler                       			/* TIM2 global interrupt                                             */
  .word	TIM3_IRQHandler                       			/* TIM3 global interrupt                                             */
  .word	TIM6_DAC_IRQHandler                   			/* TIM6 global interrupt and DAC underrun interrupt                  */
  .word	TIM7_IRQHandler                       			/* TIM7 global interrupt                                             */
  .word	TIM14_IRQHandler                      			/* TIM14 global interrupt                                            */
  .word	TIM15_IRQHandler                      			/* TIM15 global interrupt                                            */
  .word	TIM16_IRQHandler                      			/* TIM16 global interrupt                                            */
  .word	TIM17_IRQHandler                      			/* TIM17 global interrupt                                            */
  .word	I2C1_IRQHandler                       			/* I2C1 global interrupt                                             */
  .word	I2C2_IRQHandler                       			/* I2C2 global interrupt                                             */
  .word	SPI1_IRQHandler                       			/* SPI1_global_interrupt                                             */
  .word	SPI2_IRQHandler                       			/* SPI2 global interrupt                                             */
  .word	USART1_IRQHandler                     			/* USART1 global interrupt                                           */
  .word	USART2_IRQHandler                     			/* USART2 global interrupt                                           */
  .word	USART3_4_5_6_7_8_IRQHandler           			/* USART3, USART4, USART5, USART6, USART7, USART8 global interrupt   */
  .word	CEC_CAN_IRQHandler                    			/* CEC and CAN global interrupt                                      */
  .word	USB_IRQHandler                        			/* USB global interrupt                                              */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  	.weak	NMI_Handler
	.thumb_set NMI_Handler,Default_Handler

  	.weak	HardFault_Handler
	.thumb_set HardFault_Handler,Default_Handler

	.weak	SVC_Handler
	.thumb_set SVC_Handler,Default_Handler

	.weak	PendSV_Handler
	.thumb_set PendSV_Handler,Default_Handler

	.weak	SysTick_Handler
	.thumb_set SysTick_Handler,Default_Handler

	.weak	WWDG_IRQHandler
	.thumb_set WWDG_IRQHandler,Default_Handler
	
	.weak	PVD_IRQHandler
	.thumb_set PVD_IRQHandler,Default_Handler
	
	.weak	RTC_IRQHandler
	.thumb_set RTC_IRQHandler,Default_Handler
	
	.weak	FLASH_IRQHandler
	.thumb_set FLASH_IRQHandler,Default_Handler
	
	.weak	RCC_CRS_IRQHandler
	.thumb_set RCC_CRS_IRQHandler,Default_Handler
	
	.weak	EXTI0_1_IRQHandler
	.thumb_set EXTI0_1_IRQHandler,Default_Handler
	
	.weak	EXTI2_3_IRQHandler
	.thumb_set EXTI2_3_IRQHandler,Default_Handler
	
	.weak	EXTI4_15_IRQHandler
	.thumb_set EXTI4_15_IRQHandler,Default_Handler
	
	.weak	TSC_IRQHandler
	.thumb_set TSC_IRQHandler,Default_Handler
	
	.weak	DMA1_CH1_IRQHandler
	.thumb_set DMA1_CH1_IRQHandler,Default_Handler
	
	.weak	DMA1_CH2_3_DMA2_CH1_2_IRQHandler
	.thumb_set DMA1_CH2_3_DMA2_CH1_2_IRQHandler,Default_Handler
	
	.weak	DMA1_CH4_5_6_7_DMA2_CH3_4_5_IRQHandler
	.thumb_set DMA1_CH4_5_6_7_DMA2_CH3_4_5_IRQHandler,Default_Handler
	
	.weak	ADC_COMP_IRQHandler
	.thumb_set ADC_COMP_IRQHandler,Default_Handler
	
	.weak	TIM1_BRK_UP_TRG_COM_IRQHandler
	.thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler,Default_Handler
	
	.weak	TIM1_CC_IRQHandler
	.thumb_set TIM1_CC_IRQHandler,Default_Handler
	
	.weak	TIM2_IRQHandler
	.thumb_set TIM2_IRQHandler,Default_Handler
	
	.weak	TIM3_IRQHandler
	.thumb_set TIM3_IRQHandler,Default_Handler
	
	.weak	TIM6_DAC_IRQHandler
	.thumb_set TIM6_DAC_IRQHandler,Default_Handler
	
	.weak	TIM7_IRQHandler
	.thumb_set TIM7_IRQHandler,Default_Handler
	
	.weak	TIM14_IRQHandler
	.thumb_set TIM14_IRQHandler,Default_Handler
	
	.weak	TIM15_IRQHandler
	.thumb_set TIM15_IRQHandler,Default_Handler
	
	.weak	TIM16_IRQHandler
	.thumb_set TIM16_IRQHandler,Default_Handler
	
	.weak	TIM17_IRQHandler
	.thumb_set TIM17_IRQHandler,Default_Handler
	
	.weak	I2C1_IRQHandler
	.thumb_set I2C1_IRQHandler,Default_Handler
	
	.weak	I2C2_IRQHandler
	.thumb_set I2C2_IRQHandler,Default_Handler
	
	.weak	SPI1_IRQHandler
	.thumb_set SPI1_IRQHandler,Default_Handler
	
	.weak	SPI2_IRQHandler
	.thumb_set SPI2_IRQHandler,Default_Handler
	
	.weak	USART1_IRQHandler
	.thumb_set USART1_IRQHandler,Default_Handler
	
	.weak	USART2_IRQHandler
	.thumb_set USART2_IRQHandler,Default_Handler
	
	.weak	USART3_4_5_6_7_8_IRQHandler
	.thumb_set USART3_4_5_6_7_8_IRQHandler,Default_Handler
	
	.weak	CEC_CAN_IRQHandler
	.thumb_set CEC_CAN_IRQHandler,Default_Handler
	
	.weak	USB_IRQHandler
	.thumb_set USB_IRQHandler,Default_Handler
	
	.weak	SystemInit

/************************ (C) COPYRIGHT Ac6 *****END OF FILE****/
