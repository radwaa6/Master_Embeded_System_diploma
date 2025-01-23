/*
 * stm32f103x6.h
 *
 *  Created on: Feb 9, 2024
 *      Author: hassa
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-------------------
//Includes
//-------------------

#include "stdlib.h"
#include "stdint.h"


//-------------------------------
//Base Addresses For memories
//-------------------------------
#define SRAM_MEMORY_BASE						0x20000000UL
#define FLASH_MEMORY_BASE						0x08000000UL
#define SYSTEM_MEMORY_BASE						0x1FFFF000UL

#define PERIPHERALS_BASE						0x40000000UL
#define CORTEX_M3_INTERNAL_PERIPHERALS			0xE0000000UL
#define M3_NVIC									0xE000E100UL
#define NVIC_ISER0								*( volatile uint32_t*)(M3_NVIC + 0x000UL)
#define NVIC_ISER1								*( volatile uint32_t*)(M3_NVIC + 0x004UL)
#define NVIC_ISER2								*( volatile uint32_t*)(M3_NVIC + 0x008UL)
#define NVIC_ICER0								*( volatile uint32_t*)(M3_NVIC + 0x080UL)
#define NVIC_ICER1								*( volatile uint32_t*)(M3_NVIC + 0x084UL)
#define NVIC_ICER2								*( volatile uint32_t*)(M3_NVIC + 0x088UL)
//-------------------------------
//Base addresses for AHB Peripherals
//-------------------------------

//RCC

#define RCC_BASE	0x40021000UL


//-------------------------------
//Base addresses for APB2 Peripherals
//-------------------------------

//GPIO


//A,B are fully included in LQFP48 Package

#define GPIOA_BASE	0x40010800UL
#define GPIOB_BASE	0x40010C00UL

//C,D are partial included in LQFP48 Package


#define GPIOC_BASE	0x40011000UL
#define GPIOD_BASE	0x40011400UL


//E isn't include in LQFP48 Package

#define GPIOE_BASE	0x40011800UL


//EXTI
#define EXTI_BASE	0x40010400UL


//AFIO
#define AFIO_BASE	0x40010000UL


#define USART1_BASE	0x40013800UL

//-------------------------------
//Base addresses for APB1 Peripherals
//-------------------------------
//USART 2,3
#define USART2_BASE	0x40004400UL

#define USART3_BASE	0x40004800UL



//==============================================================





//************************************************
//Peripheral Registers
//************************************************





//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*
//Peripheral Register: GPIO
//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*




typedef struct
{

	volatile uint32_t	CRL;
	volatile uint32_t	CRH;
	volatile uint32_t	IDR;
	volatile uint32_t	ODR;
	volatile uint32_t	BSRR;
	volatile uint32_t	BRR;
	volatile uint32_t	LCKR;




}GPIO_typedef;





//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*
//Peripheral Register: RCC
//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*




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
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;



}RCC_typedef;




//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*
//Peripheral Register: EXTI
//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*



typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;



}EXTI_typedef;




//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*
//Peripheral Register: AFIO
//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*



typedef struct
{

	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4] ;//EXTI configuration register (1,2,3,4) but in one array
	uint32_t RESERVED0;//0x18
	volatile uint32_t MAPR2;


}AFIO_typedef;


//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*
//Peripheral Register: USART
//-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*-*-*-*_*
typedef struct{

	volatile uint32_t	SR;
	volatile uint32_t	DR;
	volatile uint32_t	BRR;
	volatile uint32_t	CR1;
	volatile uint32_t	CR2;
	volatile uint32_t	CR3;
	volatile uint32_t	GTPR;


}USART_typedef;




//==============================================================






//************************************************
//Peripheral Instants
//************************************************


//GPIO

#define GPIOA		((GPIO_typedef*)GPIOA_BASE)
#define GPIOB		((GPIO_typedef*)GPIOB_BASE)
#define GPIOC		((GPIO_typedef*)GPIOC_BASE)
#define GPIOD		((GPIO_typedef*)GPIOD_BASE)
#define GPIOE		((GPIO_typedef*)GPIOE_BASE)


//RCC

#define RCC			((RCC_typedef*)RCC_BASE)


//EXTI

#define EXTI		((EXTI_typedef*)EXTI_BASE)

//AFIO

#define AFIO		((AFIO_typedef*)AFIO_BASE)


//USART

#define USART1		 ((USART_typedef *)USART1_BASE)
#define USART2		 ((USART_typedef *)USART2_BASE)
#define USART3		 ((USART_typedef *)USART3_BASE)




//************************************************
//Clock Enable Macros
//************************************************

//GPIO
#define	RCC_GPIOA_CLK_EN()	(RCC->APB2ENR|= 1<<2)

#define	RCC_GPIOB_CLK_EN()	(RCC->APB2ENR|= 1<<3)

#define	RCC_GPIOC_CLK_EN()	(RCC->APB2ENR|= 1<<4)

#define	RCC_GPIOD_CLK_EN()	(RCC->APB2ENR|= 1<<5)

#define	RCC_GPIOE_CLK_EN()	(RCC->APB2ENR|= 1<<6)

//AFIO

#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR|= 1<<0)


//USART

#define RCC_USART1_CLK_EN()	(RCC->APB2ENR |= (1<<14))
#define RCC_USART2_CLK_EN()	(RCC->APB1ENR |= (1<<17))
#define RCC_USART3_CLK_EN()	(RCC->APB1ENR |= (1<<18))


//************************************************
//Clock Disable Macros
//************************************************

#define RCC_USART1_CLK_DIS() (RCC->APB2RSTR |= (1<<14))
#define RCC_USART2_CLK_DIS() (RCC->APB1RSTR |= (1<<17))
#define RCC_USART3_CLK_DIS() (RCC->APB1RSTR |= (1<<18))



//-*-*-*-*-*-*-*-*
//IVT
//-*-*-*-*-*-*-*-*
//EXTI
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40


//USART
#define USART1_IRQ  37
#define USART2_IRQ  38
#define USART3_IRQ  39



//---------------------------------------
//NVIC Enable/Disable Macros
//---------------------------------------

//=======EXTI Enable=======
//ICER0
#define NVIC_IRQ6_EXTI0_Enable		(NVIC_ISER0|= 1<<6)
#define NVIC_IRQ7_EXTI1_Enable		(NVIC_ISER0|= 1<<7)
#define NVIC_IRQ8_EXTI2_Enable		(NVIC_ISER0|= 1<<8)
#define NVIC_IRQ9_EXTI3_Enable		(NVIC_ISER0|= 1<<9)
#define NVIC_IRQ10_EXTI4_Enable		(NVIC_ISER0|= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable	(NVIC_ISER0|= 1<<23)
//ICER1
#define NVIC_IRQ40_EXTI10_15_Enable	(NVIC_ISER1|= 1<<8)//40-32

//=========EXTI Disable===========
//ICER0
#define NVIC_IRQ6_EXTI0_Disable			(NVIC_ICER0|= 1<<6)
#define NVIC_IRQ7_EXTI1_Disable			(NVIC_ICER0|= 1<<7)
#define NVIC_IRQ8_EXTI2_Disable			(NVIC_ICER0|= 1<<8)
#define NVIC_IRQ9_EXTI3_Disable			(NVIC_ICER0|= 1<<9)
#define NVIC_IRQ10_EXTI4_Disable		(NVIC_ICER0|= 1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable		(NVIC_ICER0|= 1<<23)
//ICER1
#define NVIC_IRQ40_EXTI10_15_Disable	(NVIC_ICER1|= 1<<8)//40-32

//=======USART Enable=======
#define NVIC_IRQ37_USART1_Enable		(NVIC_ISER1 |= 1<< (USART1_IRQ - 32))
#define NVIC_IRQ38_USART2_Enable		(NVIC_ISER1 |= 1<< (USART2_IRQ - 32))
#define NVIC_IRQ39_USART3_Enable		(NVIC_ISER1 |= 1<< (USART3_IRQ - 32))
//=========USART Disable===========
#define NVIC_IRQ37_USART1_RESET		(NVIC_ICER1 |= 1<< (USART1_IRQ - 32))
#define NVIC_IRQ38_USART2_RESET		(NVIC_ICER1 |= 1<< (USART2_IRQ - 32))
#define NVIC_IRQ39_USART3_RESET		(NVIC_ICER1 |= 1<< (USART3_IRQ - 32))


//-------------------------------
//Some useful Macros
//-------------------------------
#define checkbit(data,bit)	((data>>bit)&1)

//-------------------------------
//Includes
//-------------------------------





#endif /* INC_STM32F103X6_H_ */
