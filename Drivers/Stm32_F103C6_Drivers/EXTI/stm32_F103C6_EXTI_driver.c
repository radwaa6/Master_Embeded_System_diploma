/*
 * stm32_F103C6_gpio_driver.c
 *
 *  Created on: Feb 9, 2024
 *      Author: hassan
 */





#include "stm32_F103C6_EXTI_driver.h"







/*
 *
 * =======================================
 * 				Generic Macros
 * =======================================
 *
 */

//This Macro for which Port will be selected to act as input to the selected EXTI line (ex:PA[x]pin, PB[x]pin ,PC[x]pin ...etc)
#define AFIO_GPIO_EXTI_PORT_Routing(GPIO) (	(GPIO == GPIOA)?0:\
											(GPIO == GPIOB)?1:\
											(GPIO == GPIOC)?2:\
											(GPIO == GPIOD)?3:0	)






/*
 *
 * =======================================
 * 				Generic Functions
 * =======================================
 *
 * */







void (* GPTF_IRQ_Callback[16])(void);
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
	//1- Configuring GPIO pin to be AFIO input ->Floating input
	GPIO_PinConfig_t Exti_GPIO_pincfg;
	Exti_GPIO_pincfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_PIN;
	Exti_GPIO_pincfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Input;
	MCAL_GPIO_INIT(EXTI_Config->EXTI_PIN.GPIO_PORT, &Exti_GPIO_pincfg);
	//============================================================


	//2- Update AFIO to Route between EXTI Line with PORTS A,B,C,D
	uint8_t AFIO_EXTI_CR_index = EXTI_Config->EXTI_PIN.EXTI_InputLineNumber/4;
	uint8_t AFIO_EXTI_bit_position = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber % 4)*4;

	//Clearing EXTICR 4-bits to avoid any abnormal behaviors
	AFIO->EXTICR [AFIO_EXTI_CR_index] &= ~(0xF<<AFIO_EXTI_bit_position);
	//Set EXTICR 4-bits
	AFIO->EXTICR [AFIO_EXTI_CR_index] |=  ((AFIO_GPIO_EXTI_PORT_Routing(EXTI_Config->EXTI_PIN.GPIO_PORT) & 0xF) << AFIO_EXTI_bit_position);


	//3-Update Rising/Falling Edge Register

	EXTI->RTSR &= ~(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	if(EXTI_Config->Trigger_type == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}else if(EXTI_Config->Trigger_type == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}else if(EXTI_Config->Trigger_type == EXTI_Trigger_Rising_and_Falling)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}


	//4- Update IRQ Handling Callback
	GPTF_IRQ_Callback[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->PTF_IRQ_Callback;


	//5- Enable/Disable IRQ & NVIC

	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	}


}




/*=======================================================================================================
 *
 * @Fn    			-MCAL_EXTI_GPIO_Init
 * @brief			-This is used to initialize EXTI from specific GPIO Pin and specify the Mask/Trigger condition and IRQ Callback
 * @Param[in]		-EXTI_Config set by @ref EXTI_define,EXTI_Trigger_define,_EXTI_IRQ_define
 * @retval			-None
 * @Note			-STM32F103C6 MCU has GPIO A,B,C,D,and E Modules
 * 						But the fabrication model (LQFP48) has only GPIO A,B, and part of C/D exported as external PINS from MCU
 * 					-It's mandatory to Enable RCC clock for AFIO and the corresponding GPIO
 *
 * */



void MCAL_EXTI_GPIO_Init (EXTI_PinConfig_t* EXTI_Config)
{


	Update_EXTI(EXTI_Config);

}





/*
 * =============================================
 * 					ISR FUNCTIONS
 * =============================================
 *
 */

void EXTI0_IRQHandler(void)
{
	//Clearing PR to avoid interrupt overhead
	EXTI->PR |= (1<<0);
	GPTF_IRQ_Callback[0]();
}
void EXTI1_IRQHandler(void)
{
	//Clearing PR to avoid interrupt overhead
	EXTI->PR |= (1<<1);
	GPTF_IRQ_Callback[1]();

}
void EXTI2_IRQHandler(void)
{
	//Clearing PR to avoid interrupt overhead
	EXTI->PR |= (1<<2);
	GPTF_IRQ_Callback[2]();

}
void EXTI3_IRQHandler(void)
{
	//Clearing PR to avoid interrupt overhead
	EXTI->PR |= (1<<3);
	GPTF_IRQ_Callback[3]();

}
void EXTI4_IRQHandler(void)
{
	//Clearing PR to avoid interrupt overhead
	EXTI->PR |= (1<<4);
	GPTF_IRQ_Callback[4]();


}
void EXTI9_5_IRQHandler(void)
{
	/*	if(EXTI->PR & (1<<5)){EXTI->PR | (1<<5);	GPTF_IRQ_Callback[5]();}
	if(EXTI->PR & (1<<6)){EXTI->PR | (1<<6);    GPTF_IRQ_Callback[6]();}
	if(EXTI->PR & (1<<7)){EXTI->PR | (1<<7);    GPTF_IRQ_Callback[7]();}
	if(EXTI->PR & (1<<8)){EXTI->PR | (1<<8);    GPTF_IRQ_Callback[8]();}
	if(EXTI->PR & (1<<9)){EXTI->PR | (1<<9);    GPTF_IRQ_Callback[9]();}*/


	if(EXTI->PR & 1<< 5)
	{
		EXTI->PR |= 1<<5;
		GPTF_IRQ_Callback[5]();

	}


	if(EXTI->PR & 1<< 6)
	{
		EXTI->PR |= 1<<6;
		GPTF_IRQ_Callback[6]();

	}



	if(EXTI->PR & 1<< 7)
	{
		EXTI->PR |= 1<<7;
		GPTF_IRQ_Callback[7]();

	}



	if(EXTI->PR & 1<< 8)
	{
		EXTI->PR |= 1<<8;
		GPTF_IRQ_Callback[8]();

	}


	if(EXTI->PR & 1<< 9)
		{
			EXTI->PR |= 1<<9;
			GPTF_IRQ_Callback[9]();

		}




}


void EXTI15_10_IRQHandler(void)
{
/*
	if(EXTI->PR & (1<<10)){EXTI->PR | (1<<10);	  GPTF_IRQ_Callback[10]();}
	if(EXTI->PR & (1<<11)){EXTI->PR | (1<<11);    GPTF_IRQ_Callback[11]();}
	if(EXTI->PR & (1<<12)){EXTI->PR | (1<<12);    GPTF_IRQ_Callback[12]();}
	if(EXTI->PR & (1<<13)){EXTI->PR | (1<<13);    GPTF_IRQ_Callback[13]();}
	if(EXTI->PR & (1<<14)){EXTI->PR | (1<<14);    GPTF_IRQ_Callback[14]();}
	if(EXTI->PR & (1<<15)){EXTI->PR | (1<<15);    GPTF_IRQ_Callback[15]();}

*/



	if(EXTI->PR & 1<< 10)
	{
		EXTI->PR |= 1<<10;
		GPTF_IRQ_Callback[10]();

	}



	if(EXTI->PR & 1<< 11)
	{
		EXTI->PR |= 1<<11;
		GPTF_IRQ_Callback[11]();

	}



	if(EXTI->PR & 1<< 12)
	{
		EXTI->PR |= 1<<12;
		GPTF_IRQ_Callback[12]();

	}



	if(EXTI->PR & 1<< 13)
	{
		EXTI->PR |= 1<<13;
		GPTF_IRQ_Callback[13]();

	}


	if(EXTI->PR & 1<< 14)
	{
		EXTI->PR |= 1<<14;
		GPTF_IRQ_Callback[14]();

	}



	if(EXTI->PR & 1<< 15)
	{
		EXTI->PR |= 1<<15;
		GPTF_IRQ_Callback[15]();

	}


}




/*
 *
 * @Fn    			-MCAL_EXTI_GPIO_Deinit
 * @brief			-Reset EXTI Registers & NVIC corresponding IRQ Mask.
 * @Param[in]		-None
 * @retval			-None
 * @Note			-None
 *
 */



void MCAL_EXTI_GPIO_Deinit (void)
{
	EXTI->IMR   = 	0x00000000;
	EXTI->EMR   = 	0x00000000;
	EXTI->RTSR  = 	0x00000000;
	EXTI->FTSR  = 	0x00000000;
	EXTI->SWIER = 	0x00000000;
	//Pending Register is cleared by W1C
	EXTI->PR    =	0xFFFFFFFF;

	//NVIC Reset
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ40_EXTI10_15_Disable;


}


/*=======================================================================================================
 *
 * @Fn    			-MCAL_EXTI_GPIO_Update
 * @brief			-This is used to initialize EXTI from specific GPIO Pin and specify the Mask/Trigger condition and IRQ Callback
 * @Param[in]		-EXTI_Config set by @ref EXTI_define,EXTI_Trigger_define,_EXTI_IRQ_define
 * @retval			-None
 * @Note			-STM32F103C6 MCU has GPIO A,B,C,D,and E Modules
 * 						But the fabrication model (LQFP48) has only GPIO A,B, and part of C/D exported as external PINS from MCU
 * 					-It's mandatory to Enable RCC clock for AFIO and the corresponding GPIO
 *
 * */



void MCAL_EXTI_GPIO_Update (EXTI_PinConfig_t* EXTI_Config){


	Update_EXTI(EXTI_Config);


}
