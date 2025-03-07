/*
 * stm32f103x6_exti_driver.h
 *
 *  Created on: Oct 19, 2024
 *      Author: Mohamed Hakeem
 */

#ifndef INC_STM32F103X6_EXTI_DRIVER_H_
#define INC_STM32F103X6_EXTI_DRIVER_H_



//-----------------------------
//Includes
#include <STM32F103X6.h>
#include "stm32_F103C6_gpio_driver.h"
//-----------------------------







//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{

	uint16_t EXTI_Line_Number ;     	//Specifies the EXTI_Line_Number
										//This Parameter can be a value of @ref EXTI_Line_Define


	GPIO_TypedDef* GPIOX;   			//Specifies the Port of the required pin
										//This Parameter can be a value of @ref //Peripheral Instants
										//in STM32F103X6.h

	uint16_t EXTI_Pin_Number;           //Specifies the EXTI_Pin_Number that receives external interrupt
										//This Parameter can be a value of @ref GPIO_PINS_Define ,In GPIO Driver



	uint8_t IVT_EXTI_IRQn;              //Specifies the IRQ Number of the EXTI according IVT[Interrupt Vector Table]
										//This Parameter can be a value of @ref EXTI-------IVT In STM32F103X6.h

}EXTI_AFIO_MAPPING_t;



typedef struct
{

	EXTI_AFIO_MAPPING_t EXTI_Map_Pin;	//@EXTI_ALTERNATIVE_PIN , For Example :
										//EXTI_Map_Pin = EXTI0PA0;

	uint8_t EXTI_Trigger_State;         //Specifies the State of Triggering  that receives of External Interrupt
										//This Parameter can be selected by a value that is in @EXTI_Trigger_Defin


	uint8_t   IRQ_EN;                   //This Parameter enable or disable the EXTI_IRQ,
										// EXTI_MASK in EXTI Peripheral and Also on the  NVIC Controller
										// you can set this Parameter by @ref EXTI_IRQ_Define


	void (* PF_IRQ_CALLBACK)(void);   	//This Pointer allows you that calls IRQ_Handler of the required EXTIx
										// by only  giving this pointer address of your function.

}EXTI_PINCONFIG_t;


//@ref EXTI_Line_Define
#define EXTI0            0
#define EXTI1            1
#define EXTI2            2
#define EXTI3            3
#define EXTI4            4
#define EXTI5            5
#define EXTI6            5
#define EXTI7            7
#define EXTI8            8
#define EXTI9            9
#define EXTI10           10
#define EXTI11           11
#define EXTI12           12
#define EXTI13           13
#define EXTI14           14
#define EXTI15           15




//@EXTI_ALTERNATIVE_PIN
#define EXTI0PA0  (EXTI_AFIO_MAPPING_t){EXTI0, GPIOA, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PB0  (EXTI_AFIO_MAPPING_t){EXTI0, GPIOB, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PC0  (EXTI_AFIO_MAPPING_t){EXTI0, GPIOC, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PD0  (EXTI_AFIO_MAPPING_t){EXTI0, GPIOD, GPIO_PIN_0, EXTI0_IRQ}

#define EXTI1PA1  (EXTI_AFIO_MAPPING_t){EXTI1, GPIOA, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PB1  (EXTI_AFIO_MAPPING_t){EXTI1, GPIOB, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PC1  (EXTI_AFIO_MAPPING_t){EXTI1, GPIOC, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PD1  (EXTI_AFIO_MAPPING_t){EXTI1, GPIOD, GPIO_PIN_1, EXTI1_IRQ}

#define EXTI2PA2  (EXTI_AFIO_MAPPING_t){EXTI2, GPIOA, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PB2  (EXTI_AFIO_MAPPING_t){EXTI2, GPIOB, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PC2  (EXTI_AFIO_MAPPING_t){EXTI2, GPIOC, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PD2  (EXTI_AFIO_MAPPING_t){EXTI2, GPIOD, GPIO_PIN_2, EXTI2_IRQ}

#define EXTI3PA3  (EXTI_AFIO_MAPPING_t){EXTI3, GPIOA, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PB3  (EXTI_AFIO_MAPPING_t){EXTI3, GPIOB, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PC3  (EXTI_AFIO_MAPPING_t){EXTI3, GPIOC, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PD3  (EXTI_AFIO_MAPPING_t){EXTI3, GPIOD, GPIO_PIN_3, EXTI3_IRQ}

#define EXTI4PA4  (EXTI_AFIO_MAPPING_t){EXTI4, GPIOA, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PB4  (EXTI_AFIO_MAPPING_t){EXTI4, GPIOB, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PC4  (EXTI_AFIO_MAPPING_t){EXTI4, GPIOC, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PD4  (EXTI_AFIO_MAPPING_t){EXTI4, GPIOD, GPIO_PIN_4, EXTI4_IRQ}

#define EXTI5PA5  (EXTI_AFIO_MAPPING_t){EXTI5, GPIOA, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PB5  (EXTI_AFIO_MAPPING_t){EXTI5, GPIOB, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PC5  (EXTI_AFIO_MAPPING_t){EXTI5, GPIOC, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PD5  (EXTI_AFIO_MAPPING_t){EXTI5, GPIOD, GPIO_PIN_5, EXTI5_IRQ}

#define EXTI6PA6  (EXTI_AFIO_MAPPING_t){EXTI6, GPIOA, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PB6  (EXTI_AFIO_MAPPING_t){EXTI6, GPIOB, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PC6  (EXTI_AFIO_MAPPING_t){EXTI6, GPIOC, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PD6  (EXTI_AFIO_MAPPING_t){EXTI6, GPIOD, GPIO_PIN_6, EXTI6_IRQ}

#define EXTI7PA7  (EXTI_AFIO_MAPPING_t){EXTI7, GPIOA, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PB7  (EXTI_AFIO_MAPPING_t){EXTI7, GPIOB, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PC7  (EXTI_AFIO_MAPPING_t){EXTI7, GPIOC, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PD7  (EXTI_AFIO_MAPPING_t){EXTI7, GPIOD, GPIO_PIN_7, EXTI7_IRQ}

#define EXTI8PA8  (EXTI_AFIO_MAPPING_t){EXTI8, GPIOA, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PB8  (EXTI_AFIO_MAPPING_t){EXTI8, GPIOB, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PC8  (EXTI_AFIO_MAPPING_t){EXTI8, GPIOC, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PD8  (EXTI_AFIO_MAPPING_t){EXTI8, GPIOD, GPIO_PIN_8, EXTI8_IRQ}

#define EXTI9PA9  (EXTI_AFIO_MAPPING_t){EXTI9, GPIOA, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PB9  (EXTI_AFIO_MAPPING_t){EXTI9, GPIOB, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PC9  (EXTI_AFIO_MAPPING_t){EXTI9, GPIOC, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PD9  (EXTI_AFIO_MAPPING_t){EXTI9, GPIOD, GPIO_PIN_9, EXTI9_IRQ}

#define EXTI10PA10  (EXTI_AFIO_MAPPING_t){EXTI10, GPIOA, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PB10  (EXTI_AFIO_MAPPING_t){EXTI10, GPIOB, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PC10  (EXTI_AFIO_MAPPING_t){EXTI10, GPIOC, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PD10  (EXTI_AFIO_MAPPING_t){EXTI10, GPIOD, GPIO_PIN_10, EXTI10_IRQ}

#define EXTI11PA11  (EXTI_AFIO_MAPPING_t){EXTI11, GPIOA, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PB11  (EXTI_AFIO_MAPPING_t){EXTI11, GPIOB, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PC11  (EXTI_AFIO_MAPPING_t){EXTI11, GPIOC, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PD11  (EXTI_AFIO_MAPPING_t){EXTI11, GPIOD, GPIO_PIN_11, EXTI11_IRQ}

#define EXTI12PA12  (EXTI_AFIO_MAPPING_t){EXTI12, GPIOA, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PB12  (EXTI_AFIO_MAPPING_t){EXTI12, GPIOB, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PC12  (EXTI_AFIO_MAPPING_t){EXTI12, GPIOC, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PD12  (EXTI_AFIO_MAPPING_t){EXTI12, GPIOD, GPIO_PIN_12, EXTI12_IRQ}

#define EXTI13PA13  (EXTI_AFIO_MAPPING_t){EXTI13, GPIOA, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PB13  (EXTI_AFIO_MAPPING_t){EXTI13, GPIOB, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PC13  (EXTI_AFIO_MAPPING_t){EXTI13, GPIOC, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PD13  (EXTI_AFIO_MAPPING_t){EXTI13, GPIOD, GPIO_PIN_13, EXTI13_IRQ}

#define EXTI14PA14  (EXTI_AFIO_MAPPING_t){EXTI14, GPIOA, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PB14  (EXTI_AFIO_MAPPING_t){EXTI14, GPIOB, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PC14  (EXTI_AFIO_MAPPING_t){EXTI14, GPIOC, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PD14  (EXTI_AFIO_MAPPING_t){EXTI14, GPIOD, GPIO_PIN_14, EXTI14_IRQ}

#define EXTI15PA15  (EXTI_AFIO_MAPPING_t){EXTI15, GPIOA, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PB15  (EXTI_AFIO_MAPPING_t){EXTI15, GPIOB, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PC15  (EXTI_AFIO_MAPPING_t){EXTI15, GPIOC, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PD15  (EXTI_AFIO_MAPPING_t){EXTI15, GPIOD, GPIO_PIN_15, EXTI15_IRQ}


//@EXTI_Trigger_Define
#define EXTI_Rising_Trigger               0
#define EXTI_Falling_Trigger              1
#define EXTI_Rising_Falling_Trigger       2


//@ref EXTI_IRQ_Define
#define EXTI_IRQ_ENABLE                   1
#define EXTI_IRQ_DISABLE                  0




/*
 * ===============================================
 * APIs Supported by "MCAL EXTI DRIVER"
 * ===============================================
 */

void MCAL_EXTI_DEInit(void);
void MCAL_EXTI_Init(EXTI_PINCONFIG_t* EXTI_Config);







#endif /* INC_STM32F103X6_EXTI_DRIVER_H_ */
