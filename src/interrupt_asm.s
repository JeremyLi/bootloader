
.equ REGISTER_SIZE, 4
.equ STACK_FRAME_REGISTER_NUM, 8
.equ STACK_FRAME_SIZE, (REGISTER_SIZE * STACK_FRAME_REGISTER_NUM)

.equ NVIC_INT_CTRL, 0xE000ED04
.equ NVIC_SYSPRI14, 0xE000ED22
.equ NVIC_PENDSV_PRI, 0xFFFF
.equ NVIC_PENDSVSET, 0x10000000

.syntax unified
.thumb

.global __isr_vectors
.global __isr_vectors_end

//.org 0x08000000
.section .isr_vector
.align 4
__isr_vectors:
					.word		_estack               	    //# The initial stack pointer
    				.word		Reset_Handler         	    //# The reset handler
    				.word		NMI_Handler           	    //# The NMI handler
    				.word		HardFault_Handler	  	    //# The hard fault handler
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    				.word		MemManage_Handler		    //# The MPU fault handler
    				.word		BusFault_Handler		    //# The bus fault handler
    				.word		UsageFault_Handler		    //# The usage fault handler
#else
    				.word		0						    //# Reserved
    				.word		0						    //# Reserved
    				.word		0						    //# Reserved
#endif
    				.word		0						    //# Reserved
    				.word		0						    //# Reserved
    				.word		0						    //# Reserved
    				.word		0						    //# Reserved
    			    .word		SVC_Handler				    //# SVCall handler
#if defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
    			    .word		DebugMon_Handler		    //# Debug monitor handler
#else
    			    .word		0						    //# Reserved
#endif
    			    .word		0						    //# Reserved
    			    .word		PendSV_Handler			    //# The PendSV handler
    			    .word		SysTick_Handler			    //# The SysTick handler
    //# ----------------------------------------------------------------------
    //# External Interrupts
    			    .word		WWDG_IRQHandler			    //# Window WatchDog
    			    .word		PVD_IRQHandler			    //# PVD through EXTI Line detection
				    .word		TAMP_STAMP_IRQHandler	    //# Tamper and TimeStamps through the EXTI line
				    .word		RTC_WKUP_IRQHandler		    //# RTC Wakeup through the EXTI line
				    .word		FLASH_IRQHandler		    //# FLASH
				    .word		RCC_IRQHandler			    //# RCC
				    .word		EXTI0_IRQHandler		    //# EXTI Line0
				    .word		EXTI1_IRQHandler		    //# EXTI Line1
				    .word		EXTI2_IRQHandler		    //# EXTI Line2
				    .word		EXTI3_IRQHandler		    //# EXTI Line3
				    .word		EXTI4_IRQHandler		    //# EXTI Line4
				    .word		DMA1_Stream0_IRQHandler	    //# DMA1 Stream 0
				    .word		DMA1_Stream1_IRQHandler	    //# DMA1 Stream 1
				    .word		DMA1_Stream2_IRQHandler	    //# DMA1 Stream 2
				    .word		DMA1_Stream3_IRQHandler	    //# DMA1 Stream 3
				    .word		DMA1_Stream4_IRQHandler	    //# DMA1 Stream 4
				    .word		DMA1_Stream5_IRQHandler	    //# DMA1 Stream 5
				    .word		DMA1_Stream6_IRQHandler	    //# DMA1 Stream 6
				    .word		ADC_IRQHandler			    //# ADC1, ADC2 and ADC3s
				    .word		CAN1_TX_IRQHandler		    //# CAN1 TX
				    .word		CAN1_RX0_IRQHandler		    //# CAN1 RX0
				    .word		CAN1_RX1_IRQHandler		    //# CAN1 RX1
				    .word		CAN1_SCE_IRQHandler		    //# CAN1 SCE
				    .word		EXTI9_5_IRQHandler		    //# External Line[9:5]s
				    .word		TIM1_BRK_TIM9_IRQHandler	    //# TIM1 Break and TIM9
				    .word		TIM1_UP_TIM10_IRQHandler	    //# TIM1 Update and TIM10
				    .word		TIM1_TRG_COM_TIM11_IRQHandler	    //# TIM1 Trigger and Commutation and TIM11
				    .word		TIM1_CC_IRQHandler		    //# TIM1 Capture Compare
				    .word		TIM2_IRQHandler			    //# TIM2
				    .word		TIM3_IRQHandler			    //# TIM3
				    .word		TIM4_IRQHandler			    //# TIM4
				    .word		I2C1_EV_IRQHandler		    //# I2C1 Event
				    .word		I2C1_ER_IRQHandler		    //# I2C1 Error
				    .word		I2C2_EV_IRQHandler		    //# I2C2 Event
				    .word		I2C2_ER_IRQHandler		    //# I2C2 Error
				    .word		SPI1_IRQHandler			    //# SPI1
				    .word		SPI2_IRQHandler			    //# SPI2
				    .word		USART1_IRQHandler		    //# USART1
				    .word		USART2_IRQHandler		    //# USART2
				    .word		USART3_IRQHandler		    //# USART3
				    .word		EXTI15_10_IRQHandler	    //# External Line[15:10]s
				    .word		RTC_Alarm_IRQHandler	    //# RTC Alarm (A and B) through EXTI Line
				    .word		OTG_FS_WKUP_IRQHandler	    //# USbOTG FS Wakeup through EXTI line
				    .word		TIM8_BRK_TIM12_IRQHandler	    //# TIM8 Break and TIM12
				    .word		TIM8_UP_TIM13_IRQHandler	    //# TIM8 Update and TIM13
				    .word		TIM8_TRG_COM_TIM14_IRQHandler	    //# TIM8 Trigger and Commutation and TIM14
				    .word		TIM8_CC_IRQHandler		    //# TIM8 Capture Compare
				    .word		DMA1_Stream7_IRQHandler	    //# DMA1 Stream7
				    .word		FMC_IRQHandler			    //# FMC
				    .word		SDIO_IRQHandler			    //# SDIO
				    .word		TIM5_IRQHandler			    //# TIM5
				    .word		SPI3_IRQHandler			    //# SPI3
				    .word		UART4_IRQHandler		    //# UART4
				    .word		UART5_IRQHandler		    //# UART5
				    .word		TIM6_DAC_IRQHandler		    //# TIM6 and DAC1&2 underrun errors
				    .word		TIM7_IRQHandler			    //# TIM7
				    .word		DMA2_Stream0_IRQHandler	    //# DMA2 Stream 0
				    .word		DMA2_Stream1_IRQHandler	    //# DMA2 Stream 1
				    .word		DMA2_Stream2_IRQHandler	    //# DMA2 Stream 2
				    .word		DMA2_Stream3_IRQHandler	    //# DMA2 Stream 3
				    .word		DMA2_Stream4_IRQHandler	    //# DMA2 Stream 4
				    .word		ETH_IRQHandler			    //# Ethernet
				    .word		ETH_WKUP_IRQHandler		    //# Ethernet Wakeup through EXTI line
				    .word		CAN2_TX_IRQHandler		    //# CAN2 TX
				    .word		CAN2_RX0_IRQHandler		    //# CAN2 RX0
				    .word		CAN2_RX1_IRQHandler		    //# CAN2 RX1
				    .word		CAN2_SCE_IRQHandler		    //# CAN2 SCE
				    .word		OTG_FS_IRQHandler		    //# USbOTG FS
				    .word		DMA2_Stream5_IRQHandler	    //# DMA2 Stream 5
				    .word		DMA2_Stream6_IRQHandler	    //# DMA2 Stream 6
				    .word		DMA2_Stream7_IRQHandler	    //# DMA2 Stream 7
				    .word		USART6_IRQHandler		    //# USART6
				    .word		I2C3_EV_IRQHandler		    //# I2C3 event
				    .word		I2C3_ER_IRQHandler		    //# I2C3 error
				    .word		OTG_HS_EP1_OUT_IRQHandler	    //# USbOTG HS End Point 1 Out
				    .word		OTG_HS_EP1_IN_IRQHandler	    //# USbOTG HS End Point 1 In
				    .word		OTG_HS_WKUP_IRQHandler		    //# USbOTG HS Wakeup through EXTI
				    .word		OTG_HS_IRQHandler		    //# USbOTG HS
				    .word		DCMI_IRQHandler			    //# DCMI
				    .word		0						    //# Reserved
				    .word		HASH_RNG_IRQHandler		    //# Hash and Rng
				    .word		FPU_IRQHandler			    //# FPU
__isr_vectors_end:

.section .after_vectors
//.align 4

# .global _start
# _start:
.thumb_func
.type       Reset_Handler, %function
Reset_Handler:
                .global  Reset_Handler 
   				ldr r0, =_boot
				bx r0

NMI_Handler:
                .weak  NMI_Handler                
                b      .

HardFault_Handler:
                .weak  HardFault_Handler          
                b      .

MemManage_Handler:
                .weak  MemManage_Handler          
                b      .

BusFault_Handler:
                .weak  BusFault_Handler           
                b      .

UsageFault_Handler:
                .weak  UsageFault_Handler         
                b      .

SVC_Handler:
                .weak  SVC_Handler                
				b		.
DebugMon_Handler:
                .weak  DebugMon_Handler           
                b      .

PendSV_Handler:
                .weak  PendSV_Handler  
				b		.

SysTick_Handler:
                .weak  SysTick_Handler 
                b		.

Default_Handler:
    			    .weak		WWDG_IRQHandler			    //# Window WatchDog
    			    .weak		PVD_IRQHandler			    //# PVD through EXTI Line detection
				    .weak		TAMP_STAMP_IRQHandler	    //# Tamper and TimeStamps through the EXTI line
				    .weak		RTC_WKUP_IRQHandler		    //# RTC Wakeup through the EXTI line
				    .weak		FLASH_IRQHandler		    //# FLASH
				    .weak		RCC_IRQHandler			    //# RCC
				    .weak		EXTI0_IRQHandler		    //# EXTI Line0
				    .weak		EXTI1_IRQHandler		    //# EXTI Line1
				    .weak		EXTI2_IRQHandler		    //# EXTI Line2
				    .weak		EXTI3_IRQHandler		    //# EXTI Line3
				    .weak		EXTI4_IRQHandler		    //# EXTI Line4
				    .weak		DMA1_Stream0_IRQHandler	    //# DMA1 Stream 0
				    .weak		DMA1_Stream1_IRQHandler	    //# DMA1 Stream 1
				    .weak		DMA1_Stream2_IRQHandler	    //# DMA1 Stream 2
				    .weak		DMA1_Stream3_IRQHandler	    //# DMA1 Stream 3
				    .weak		DMA1_Stream4_IRQHandler	    //# DMA1 Stream 4
				    .weak		DMA1_Stream5_IRQHandler	    //# DMA1 Stream 5
				    .weak		DMA1_Stream6_IRQHandler	    //# DMA1 Stream 6
				    .weak		ADC_IRQHandler			    //# ADC1, ADC2 and ADC3s
				    .weak		CAN1_TX_IRQHandler		    //# CAN1 TX
				    .weak		CAN1_RX0_IRQHandler		    //# CAN1 RX0
				    .weak		CAN1_RX1_IRQHandler		    //# CAN1 RX1
				    .weak		CAN1_SCE_IRQHandler		    //# CAN1 SCE
				    .weak		EXTI9_5_IRQHandler		    //# External Line[9:5]s
				    .weak		TIM1_BRK_TIM9_IRQHandler	    //# TIM1 Break and TIM9
				    .weak		TIM1_UP_TIM10_IRQHandler	    //# TIM1 Update and TIM10
				    .weak		TIM1_TRG_COM_TIM11_IRQHandler	    //# TIM1 Trigger and Commutation and TIM11
				    .weak		TIM1_CC_IRQHandler		    //# TIM1 Capture Compare
				    .weak		TIM2_IRQHandler			    //# TIM2
				    .weak		TIM3_IRQHandler			    //# TIM3
				    .weak		TIM4_IRQHandler			    //# TIM4
				    .weak		I2C1_EV_IRQHandler		    //# I2C1 Event
				    .weak		I2C1_ER_IRQHandler		    //# I2C1 Error
				    .weak		I2C2_EV_IRQHandler		    //# I2C2 Event
				    .weak		I2C2_ER_IRQHandler		    //# I2C2 Error
				    .weak		SPI1_IRQHandler			    //# SPI1
				    .weak		SPI2_IRQHandler			    //# SPI2
				    .weak		USART1_IRQHandler		    //# USART1
				    .weak		USART2_IRQHandler		    //# USART2
				    .weak		USART3_IRQHandler		    //# USART3
				    .weak		EXTI15_10_IRQHandler	    //# External Line[15:10]s
				    .weak		RTC_Alarm_IRQHandler	    //# RTC Alarm (A and B) through EXTI Line
				    .weak		OTG_FS_WKUP_IRQHandler	    //# USbOTG FS Wakeup through EXTI line
				    .weak		TIM8_BRK_TIM12_IRQHandler	    //# TIM8 Break and TIM12
				    .weak		TIM8_UP_TIM13_IRQHandler	    //# TIM8 Update and TIM13
				    .weak		TIM8_TRG_COM_TIM14_IRQHandler	    //# TIM8 Trigger and Commutation and TIM14
				    .weak		TIM8_CC_IRQHandler		    //# TIM8 Capture Compare
				    .weak		DMA1_Stream7_IRQHandler	    //# DMA1 Stream7
				    .weak		FMC_IRQHandler			    //# FMC
				    .weak		SDIO_IRQHandler			    //# SDIO
				    .weak		TIM5_IRQHandler			    //# TIM5
				    .weak		SPI3_IRQHandler			    //# SPI3
				    .weak		UART4_IRQHandler		    //# UART4
				    .weak		UART5_IRQHandler		    //# UART5
				    .weak		TIM6_DAC_IRQHandler		    //# TIM6 and DAC1&2 underrun errors
				    .weak		TIM7_IRQHandler			    //# TIM7
				    .weak		DMA2_Stream0_IRQHandler	    //# DMA2 Stream 0
				    .weak		DMA2_Stream1_IRQHandler	    //# DMA2 Stream 1
				    .weak		DMA2_Stream2_IRQHandler	    //# DMA2 Stream 2
				    .weak		DMA2_Stream3_IRQHandler	    //# DMA2 Stream 3
				    .weak		DMA2_Stream4_IRQHandler	    //# DMA2 Stream 4
				    .weak		ETH_IRQHandler			    //# Ethernet
				    .weak		ETH_WKUP_IRQHandler		    //# Ethernet Wakeup through EXTI line
				    .weak		CAN2_TX_IRQHandler		    //# CAN2 TX
				    .weak		CAN2_RX0_IRQHandler		    //# CAN2 RX0
				    .weak		CAN2_RX1_IRQHandler		    //# CAN2 RX1
				    .weak		CAN2_SCE_IRQHandler		    //# CAN2 SCE
				    .weak		OTG_FS_IRQHandler		    //# USbOTG FS
				    .weak		DMA2_Stream5_IRQHandler	    //# DMA2 Stream 5
				    .weak		DMA2_Stream6_IRQHandler	    //# DMA2 Stream 6
				    .weak		DMA2_Stream7_IRQHandler	    //# DMA2 Stream 7
				    .weak		USART6_IRQHandler		    //# USART6
				    .weak		I2C3_EV_IRQHandler		    //# I2C3 event
				    .weak		I2C3_ER_IRQHandler		    //# I2C3 error
				    .weak		OTG_HS_EP1_OUT_IRQHandler	    //# USbOTG HS End Point 1 Out
				    .weak		OTG_HS_EP1_IN_IRQHandler	    //# USbOTG HS End Point 1 In
				    .weak		OTG_HS_WKUP_IRQHandler		    //# USbOTG HS Wakeup through EXTI
				    .weak		OTG_HS_IRQHandler		    //# USbOTG HS
				    .weak		DCMI_IRQHandler			    //# DCMI
				    .weak		HASH_RNG_IRQHandler		    //# Hash and Rng
				    .weak		FPU_IRQHandler			    //# FPU

WWDG_IRQHandler:			    //# Window WatchDog
PVD_IRQHandler:			    //# PVD through EXTI Line detection
TAMP_STAMP_IRQHandler:	    //# Tamper and TimeStamps through the EXTI line
RTC_WKUP_IRQHandler:		    //# RTC Wakeup through the EXTI line
FLASH_IRQHandler:		    //# FLASH
RCC_IRQHandler:			    //# RCC
EXTI0_IRQHandler:		    //# EXTI Line0
EXTI1_IRQHandler:		    //# EXTI Line1
EXTI2_IRQHandler:		    //# EXTI Line2
EXTI3_IRQHandler:		    //# EXTI Line3
EXTI4_IRQHandler:		    //# EXTI Line4
DMA1_Stream0_IRQHandler:	    //# DMA1 Stream 0
DMA1_Stream1_IRQHandler:    //# DMA1 Stream 1
DMA1_Stream2_IRQHandler:	    //# DMA1 Stream 2
DMA1_Stream3_IRQHandler:	    //# DMA1 Stream 3
DMA1_Stream4_IRQHandler:	    //# DMA1 Stream 4
DMA1_Stream5_IRQHandler:	    //# DMA1 Stream 5
DMA1_Stream6_IRQHandler:	    //# DMA1 Stream 6
ADC_IRQHandler:			    //# ADC1, ADC2 and ADC3s
CAN1_TX_IRQHandler:		    //# CAN1 TX
CAN1_RX0_IRQHandler:		    //# CAN1 RX0
CAN1_RX1_IRQHandler:		    //# CAN1 RX1
CAN1_SCE_IRQHandler:		    //# CAN1 SCE
EXTI9_5_IRQHandler:		    //# External Line[9:5]s
TIM1_BRK_TIM9_IRQHandler:	    //# TIM1 Break and TIM9
TIM1_UP_TIM10_IRQHandler:	    //# TIM1 Update and TIM10
TIM1_TRG_COM_TIM11_IRQHandler:	    //# TIM1 Trigger and Commutation and TIM11
TIM1_CC_IRQHandler:		    //# TIM1 Capture Compare
TIM2_IRQHandler:			    //# TIM2
TIM3_IRQHandler:			    //# TIM3
TIM4_IRQHandler:			    //# TIM4
I2C1_EV_IRQHandler:		    //# I2C1 Event
I2C1_ER_IRQHandler:		    //# I2C1 Error
I2C2_EV_IRQHandler:		    //# I2C2 Event
I2C2_ER_IRQHandler:		    //# I2C2 Error
SPI1_IRQHandler:			    //# SPI1
SPI2_IRQHandler:			    //# SPI2
USART1_IRQHandler:		    //# USART1
USART2_IRQHandler:		    //# USART2
USART3_IRQHandler:		    //# USART3
EXTI15_10_IRQHandler:	    //# External Line[15:10]s
RTC_Alarm_IRQHandler:	    //# RTC Alarm (A and B) through EXTI Line
OTG_FS_WKUP_IRQHandler:	    //# USbOTG FS Wakeup through EXTI line
TIM8_BRK_TIM12_IRQHandler:	    //# TIM8 Break and TIM12
TIM8_UP_TIM13_IRQHandler:	    //# TIM8 Update and TIM13
TIM8_TRG_COM_TIM14_IRQHandler:	    //# TIM8 Trigger and Commutation and TIM14
TIM8_CC_IRQHandler:		    //# TIM8 Capture Compare
DMA1_Stream7_IRQHandler:	    //# DMA1 Stream7
FMC_IRQHandler:			    //# FMC
SDIO_IRQHandler:			    //# SDIO
TIM5_IRQHandler:			    //# TIM5
SPI3_IRQHandler:			    //# SPI3
UART4_IRQHandler:		    //# UART4
UART5_IRQHandler:		    //# UART5
TIM6_DAC_IRQHandler:		    //# TIM6 and DAC1&2 underrun errors
TIM7_IRQHandler:			    //# TIM7
DMA2_Stream0_IRQHandler:	    //# DMA2 Stream 0
DMA2_Stream1_IRQHandler:	    //# DMA2 Stream 1
DMA2_Stream2_IRQHandler:	    //# DMA2 Stream 2
DMA2_Stream3_IRQHandler:	    //# DMA2 Stream 3
DMA2_Stream4_IRQHandler:	    //# DMA2 Stream 4
ETH_IRQHandler:			    //# Ethernet
ETH_WKUP_IRQHandler:		    //# Ethernet Wakeup through EXTI line
CAN2_TX_IRQHandler:		    //# CAN2 TX
CAN2_RX0_IRQHandler:		    //# CAN2 RX0
CAN2_RX1_IRQHandler:		    //# CAN2 RX1
CAN2_SCE_IRQHandler:		    //# CAN2 SCE
OTG_FS_IRQHandler:		    //# USbOTG FS
DMA2_Stream5_IRQHandler:	    //# DMA2 Stream 5
DMA2_Stream6_IRQHandler:	    //# DMA2 Stream 6
DMA2_Stream7_IRQHandler:	    //# DMA2 Stream 7
USART6_IRQHandler:		    //# USART6
I2C3_EV_IRQHandler:		    //# I2C3 event
I2C3_ER_IRQHandler:		    //# I2C3 error
OTG_HS_EP1_OUT_IRQHandler:	    //# USbOTG HS End Point 1 Out
OTG_HS_EP1_IN_IRQHandler:	    //# USbOTG HS End Point 1 In
OTG_HS_WKUP_IRQHandler:		    //# USbOTG HS Wakeup through EXTI
OTG_HS_IRQHandler:		    //# USbOTG HS
DCMI_IRQHandler:			    //# DCMI
HASH_RNG_IRQHandler:		    //# Hash and Rng
FPU_IRQHandler:			    //# FPU
                b      .



