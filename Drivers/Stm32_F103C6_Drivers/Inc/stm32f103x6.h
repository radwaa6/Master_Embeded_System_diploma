
/*
 * stm32f103x6.h
 *
 *  Created on: Sep 11, 2024
 *      Author: Younis
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_


//-----------------------------
//Includes
//-----------------------------

#include "stdlib.h"
#include "stdint.h"


//==============================================================//


//-----------------------------
//Base addresses for Memories
//-----------------------------

#define Flash_Memory_Base						0x08000000UL //As it is constant so we put UL->unsigned long
#define System_Memory_Base						0x1FFFF000UL
#define Sram_Memory_Base						0x20000000UL

#define Peripherals_Base						0x40000000UL
#define Cortex_M3_Internal_Peripherals_Base		0xE0000000UL

//NVIC Register map
#define NVIC_Base								0xE000E100UL
#define NVIC_ISER0								*(volatile uint32_t*)(NVIC_Base + 0x000)
#define NVIC_ISER1								*(volatile uint32_t*)(NVIC_Base + 0x004)
#define NVIC_ISER2								*(volatile uint32_t*)(NVIC_Base + 0x008)
#define NVIC_ICER0								*(volatile uint32_t*)(NVIC_Base + 0x080)
#define NVIC_ICER1								*(volatile uint32_t*)(NVIC_Base + 0x084)
#define NVIC_ICER2								*(volatile uint32_t*)(NVIC_Base + 0x088)

//-----------------------------
//Base addresses for AHB-BUS Peripherals
//-----------------------------
//RCC
#define RCC_Base								0x40021000UL
//Howa howa bas bnsbali mn 8eer offset as.hal
//#define RCC_Base								(Peripherals_Base+ 0x00021000UL)


//==============================================================//


//-----------------------------
//Base addresses for APB2-BUS Peripherals
//-----------------------------

//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_Base									0x40010800UL
#define GPIOB_Base									0x40010C00UL

//C,D partially included in LQFP48 Package
#define GPIOC_Base									0x40011000UL
#define GPIOD_Base									0x40011400UL

//E not included in LQFP48 Packagec
#define GPIOE_Base									0x40011800UL

//EXTI
#define EXTI_Base									0x40010400UL

//AFIO
#define AFIO_Base									0x40010000UL

//-----------------------------
//Base addresses for APB1-BUS Peripherals
//-----------------------------

//==============================================================//

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//-*-*-*-*-*-*-*-*-*-*
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	//Ay element hyb2a volatile dah tabe3y 3ashan h3mllo ptr 3ala 7aga tanya
	volatile uint32_t CRL;//homa mt2smeen kol 4 bytes fa bel taly uint32
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;



//-*-*-*-*-*-*-*-*-*-*
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
//	volatile uint32_t AHBRSTR;
//	volatile uint32_t CFGR2;
}RCC_TypeDef;

//-*-*-*-*-*-*-*-*-*-*
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
//	volatile uint32_t EXTICR1;
//	volatile uint32_t EXTICR2;
//	volatile uint32_t EXTICR3;
//	volatile uint32_t EXTICR4;
			 uint32_t RESERVED0;
	volatile uint32_t MAPR2;
}AFIO_TypeDef;

//==============================================================//


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIO
#define GPIOA					((GPIO_TypeDef*)GPIOA_Base)//GPIO_TypeDef *GPIOA = (GPIO_TypeDef*)GPIOA_Base
#define GPIOB					((GPIO_TypeDef*)GPIOB_Base)
#define GPIOC					((GPIO_TypeDef*)GPIOC_Base)
#define GPIOD					((GPIO_TypeDef*)GPIOD_Base)
#define GPIOE					((GPIO_TypeDef*)GPIOE_Base)

//RCC
#define RCC						((RCC_TypeDef*)RCC_Base)

//EXTI
#define EXTI					((EXTI_TypeDef*)EXTI_Base)

//AFIO
#define AFIO					((AFIO_TypeDef*)AFIO_Base)


//==============================================================//


//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//GPIO
#define RCC_GPIOA_Clk_En()		(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_Clk_En()		(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_Clk_En()		(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_Clk_En()		(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_Clk_En()		(RCC->APB2ENR |= 1<<6)

//AFIO
#define RCC_AFIO_Clk_En()		(RCC->APB2ENR |= 1<<0)

//-*-*-*-*-*-*-*-*-*-*-*-
//IVT:
//-*-*-*-*-*-*-*-*-*-*-*
//EXTI
#define EXTI0_IRQ			6
#define EXTI1_IRQ			7
#define EXTI2_IRQ			8
#define EXTI3_IRQ			9
#define EXTI4_IRQ			10
#define EXTI5_IRQ			23
#define EXTI6_IRQ			23
#define EXTI7_IRQ			23
#define EXTI8_IRQ			23
#define EXTI9_IRQ			23
#define EXTI10_IRQ			40
#define EXTI11_IRQ			40
#define EXTI12_IRQ			40
#define EXTI13_IRQ			40
#define EXTI14_IRQ			40
#define EXTI15_IRQ			40



//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC IRQ enable/disable Macros
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_IRQ6_EXTI0_Enable			(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Enable			(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable			(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable			(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable			(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable		(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Enable		(NVIC_ISER1 |= 1<<8) //40-32 See the range of ISER

#define NVIC_IRQ6_EXTI0_Disable			(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXTI1_Disable			(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXTI2_Disable			(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXTI3_Disable			(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable		(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable		(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable	(NVIC_ICER1 |= 1<<8) //40-32 See the range of ICER

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*



#endif /* INC_STM32F103X6_H_ */
