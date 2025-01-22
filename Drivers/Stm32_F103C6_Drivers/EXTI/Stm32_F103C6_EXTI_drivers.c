
/*
 * Stm32_F103C6_gpio_drivers.c
 *
 *  Created on: Sep 11, 2024
 *      Author: Younis Tamer
 */



#include "Stm32_F103C6_EXTI_drivers.h"
#include "Stm32_F103C6_gpio_drivers.h"


/*
 * ===================================================================================================
 * 										Generic Variables
 * ===================================================================================================
 */

	void(*GPtr_IRQ_CallBack[15])(void);


/*
 * ===================================================================================================
 * 										Generic Macros
 * ===================================================================================================
 */

#define AFIO_GPIO_EXTI_Mapping(x)	(	(x==GPIOA)?0:\
										(x==GPIOB)?1:\
										(x==GPIOC)?2:\
										(x==GPIOD)?3:0	)

/*
 * ===================================================================================================
 * 										Generic Functions
 * ===================================================================================================
 */

void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		break;
	}
}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;
	}
}







void Update_EXTI(EXTI_PinConfig_t* EXTI_Config)
{
	//1- Cinfig  to be AF input -> Floating input
	GPIO_Pin_Config_t PinConfig;
	PinConfig.GPIO_Pin_Num = EXTI_Config->EXTI_Pin.GPIO_Pin;
	PinConfig.GPIO_Mode = GPIO_Mode_Input_Flo;
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.GPIO_Port, &PinConfig);

	//==============================================================
	//2-Update AFIO to route betn EXTI line with Port A,B,C,D
	uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number/4; //index 0 1 2 3
	uint8_t AFIO_EXTICR_position = (EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number%4)*4;//Position 0 4 8 12

	//Clear the 4 bits
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_position);

	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_Pin.GPIO_Port) & 0xF) << AFIO_EXTICR_position);

	//==============================================================
	//3- Update rising or falling edge
	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);


	if(EXTI_Config->Trigger_Case == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_Trigger_BOTH)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
	}

	//==============================================================
	//4- Update IRQ Handling CALLBACK
	GPtr_IRQ_CallBack[EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number] = EXTI_Config->Ptr_IRQ_CallBack;

	//==============================================================
	//5- Enable/Disable IRQ EXTI & NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
		Enable_NVIC(EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
	}
	else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
		Disable_NVIC(EXTI_Config->EXTI_Pin.EXTI_Input_Line_Number);
	}


}


/*
 * ===================================================================================================
 * 										APIs Functions Definitions
 * ===================================================================================================
 */

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Init
 * @brief 		-This is used to initialize EXTI from specific GPIO pin and specify the Msk/Trigger condition and IRQ CallBack
 * @param [in] 	-EXTI_Config set by @ref EXTI_define , EXTI_Trigger_define and EXTI_IRQ_define
 * @returnval 	-None
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				But LQFP48 Package has only GPIO A,B,Part of C,D exported as external pins from the
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_DeInit
 * @brief 		-reset EXTI Registers and NVIC corresponding IRQ Mask
 * @returnval 	-None
 * Note			-None
 */
void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->IMR 	= 0x00000000;
	EXTI->EMR 	= 0x00000000;
	EXTI->RTSR  = 0x00000000;
	EXTI->FTSR 	= 0x00000000;
	EXTI->SWIER = 0x00000000;

	//	This bit is
	//	cleared by writing a ‘1’ into the bit.
	EXTI->PR	= 0xFFFFFFFF;

	//Disable EXTI IRQ From NVIC
	NVIC_IRQ6_EXTI0_Disable		;
	NVIC_IRQ7_EXTI1_Disable		;
	NVIC_IRQ8_EXTI2_Disable		;
	NVIC_IRQ9_EXTI3_Disable		;
	NVIC_IRQ10_EXTI4_Disable	;
	NVIC_IRQ23_EXTI5_9_Disable	;
	NVIC_IRQ40_EXTI10_15_Disable;
}

/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Update
 * @brief 		-This is used to initialize EXTI from specific GPIO pin and specify the Msk/Trigger condition and IRQ CallBack
 * @param [in] 	-EXTI_Config set by @ref EXTI_define , EXTI_Trigger_define and EXTI_IRQ_define
 * @returnval 	-None
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				But LQFP48 Package has only GPIO A,B,Part of C,D exported as external pins from the
 */
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)//Converting from rising to falling and vice versa
{
	Update_EXTI(EXTI_Config);
}



/*
 * ===================================================================================================
 * 										ISR Functions
 * ===================================================================================================
 */


void EXTI0_IRQHandler (void)
{
	//clear by writing '1' into the bit pending register "EXTI_PR" as to not bee in infinite loop
	EXTI->PR |= 1<<0;
	//Call IRQ_CALL
	GPtr_IRQ_CallBack[0]();
}

void EXTI1_IRQHandler (void)
{
	//clear by writing '1' into the bit pending register "EXTI_PR" as to not bee in infinite loop
	EXTI->PR |= 1<<1;
	//Call IRQ_CALL
	GPtr_IRQ_CallBack[1]();
}

void EXTI2_IRQHandler (void)
{
	//clear by writing '1' into the bit pending register "EXTI_PR" as to not bee in infinite loop
	EXTI->PR |= 1<<2;
	//Call IRQ_CALL
	GPtr_IRQ_CallBack[2]();
}

void EXTI3_IRQHandler (void)
{
	//clear by writing '1' into the bit pending register "EXTI_PR" as to not bee in infinite loop
	EXTI->PR |= 1<<3;
	//Call IRQ_CALL
	GPtr_IRQ_CallBack[3]();
}

void EXTI4_IRQHandler (void)
{
	//clear by writing '1' into the bit pending register "EXTI_PR" as to not bee in infinite loop
	EXTI->PR |= 1<<4;
	//Call IRQ_CALL
	GPtr_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler (void)
{
	if(EXTI->PR & 1<<5) {EXTI->PR |= 1<<5;		GPtr_IRQ_CallBack[5]();}
	if(EXTI->PR & 1<<6) {EXTI->PR |= 1<<6;		GPtr_IRQ_CallBack[6]();}
	if(EXTI->PR & 1<<7) {EXTI->PR |= 1<<7;		GPtr_IRQ_CallBack[7]();}
	if(EXTI->PR & 1<<8) {EXTI->PR |= 1<<8;		GPtr_IRQ_CallBack[8]();}
	if(EXTI->PR & 1<<9) {EXTI->PR |= 1<<9;		GPtr_IRQ_CallBack[9]();}
}

void EXTI15_10_IRQHandler (void)
{
	if(EXTI->PR & 1<<10) {EXTI->PR |= 1<<10;		GPtr_IRQ_CallBack[10]();}
	if(EXTI->PR & 1<<11) {EXTI->PR |= 1<<11;		GPtr_IRQ_CallBack[11]();}
	if(EXTI->PR & 1<<12) {EXTI->PR |= 1<<12;		GPtr_IRQ_CallBack[12]();}
	if(EXTI->PR & 1<<13) {EXTI->PR |= 1<<13;		GPtr_IRQ_CallBack[13]();}
	if(EXTI->PR & 1<<14) {EXTI->PR |= 1<<14;		GPtr_IRQ_CallBack[14]();}
	if(EXTI->PR & 1<<15) {EXTI->PR |= 1<<15;		GPtr_IRQ_CallBack[15]();}
}
