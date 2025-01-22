
/*
 * Stm32_F103C6_gpio_drivers.c
 *
 *  Created on: Sep 11, 2024
 *      Author: Younis Tamer
 */



#include "Stm32_F103C6_gpio_drivers.h"


uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_Pin_0 ://Because Pin 0 starts from bit 0
		return 0;
		break;
	case GPIO_Pin_1 ://Because Pin 1 starts from bit 4
		return 4;
		break;
	case GPIO_Pin_2 ://Because Pin 2 starts from bit 8
		return 8;
		break;
	case GPIO_Pin_3 ://Because Pin 3 starts from bit 12
		return 12;
		break;
	case GPIO_Pin_4 ://Because Pin 4 starts from bit 16
		return 16;
		break;
	case GPIO_Pin_5 ://Because Pin 5 starts from bit 20
		return 20;
		break;
	case GPIO_Pin_6 ://Because Pin 6 starts from bit 24
		return 24;
		break;
	case GPIO_Pin_7 ://Because Pin 7 starts from bit 28
		return 28;
		break;
	case GPIO_Pin_8 ://Because Pin 8 starts from bit 0
		return 0;
		break;
	case GPIO_Pin_9 ://Because Pin 9 starts from bit 4
		return 4;
		break;
	case GPIO_Pin_10 ://Because Pin 10 starts from bit 8
		return 8;
		break;
	case GPIO_Pin_11 ://Because Pin 11 starts from bit 12
		return 12;
		break;
	case GPIO_Pin_12 ://Because Pin 12 starts from bit 16
		return 16;
		break;
	case GPIO_Pin_13 ://Because Pin 13 starts from bit 20
		return 20;
		break;
	case GPIO_Pin_14 ://Because Pin 14 starts from bit 24
		return 24;
		break;
	case GPIO_Pin_15 ://Because Pin 15 starts from bit 28
		return 28;
		break;
	}
	return 0;
}



/**================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initializes the GPIOx Piny peripheral according to the specified parameters in PinConfig
 * @param [in] 	-GPIOx: x(A...E)
 * @param [in] 	-PinConfig ptr to GPIO_Pin_Config_t struct that contains the configuration info for the specified GPIO peripheral
 * @returnval 	-None
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				But LQFP48 Package has only GPIO A,B,Part of C,D exported as external pins from the
 */
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx , GPIO_Pin_Config_t* PinConfig)
{
	//Port configuration register low (GPIOx_CRL) configure pins from (0->7)
	//Port configuration register High (GPIOx_CRH) configure pins from (8->15)
	volatile uint32_t* configRegister	= NULL;
	uint8_t Pin_Config = 0;

	configRegister = (PinConfig->GPIO_Pin_Num < GPIO_Pin_8)? &GPIOx->CRL: &GPIOx->CRH;
	//Clear CNF8[1:0] MODE8[1:0]
	(*configRegister) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_Pin_Num));

	//If pin is Output
	if((PinConfig->GPIO_Mode == GPIO_Mode_Output_AF_OD) || (PinConfig->GPIO_Mode == GPIO_Mode_Output_AF_PP) || (PinConfig->GPIO_Mode == GPIO_Mode_Output_OD) || (PinConfig->GPIO_Mode == GPIO_Mode_Output_PP))
	{
		//Set CNF8[1:0] MODE8[1:0]
		Pin_Config = ( (((PinConfig->GPIO_Mode -4) << 2 | (PinConfig->GPIO_Output_Speed)) & 0x0f));//I did minus 4 because i defined the output from 4->7 and then shifted by 2 because Cnf is the upper 2 bits then anded by 0x0f cause i need only those 4 bits
		//		(*configRegister) |= ((Pin_Config) << Get_CRLH_Position(PinConfig->GPIO_Pin_Num));
	}

	//If pin is input
	else //Input is 00 by default Mode = 00
	{
		if((PinConfig->GPIO_Mode == GPIO_Mode_Input_Flo) || (PinConfig->GPIO_Mode == GPIO_Mode_Analog))
		{
			//Set CNF8[1:0] MODE8[1:0]00
			Pin_Config = ( (((PinConfig->GPIO_Mode) << 2 | (0x0)) & 0x0f));//I did minus 4 because i defined the output from 4->7 and then shifted by 2 because Cnf is the upper 2 bits then anded by 0x0f causei need only those 4 bits
			//				(*configRegister) |= ((Pin_Config) << Get_CRLH_Position(PinConfig->GPIO_Pin_Num));
		}
		else if(PinConfig->GPIO_Mode == GPIO_Mode_AF_Input)//Consider it as input floating
		{
			//Set CNF8[1:0] MODE8[1:0]00
			Pin_Config = ( (((GPIO_Mode_Input_Flo) << 2 | (0x0)) & 0x0f));
			//				(*configRegister) |= ((Pin_Config) << Get_CRLH_Position(PinConfig->GPIO_Pin_Num));
		}
		else //PU PD Input
		{
			Pin_Config = ((((GPIO_Mode_Input_PU) << 2) | 0x0) &0x0f);
			if(PinConfig->GPIO_Mode == GPIO_Mode_Input_PU)
			{
				//Table 20 Port bit configuration table PxODR = 1
				GPIOx->ODR |= PinConfig->GPIO_Pin_Num;
			}
			else//PD //Table 20 Port bit configuration table PxODR = 0
			{
				GPIOx->ODR &= ~(PinConfig->GPIO_Pin_Num);
			}
		}
	}
	//Write on CRL or CRH
	(*configRegister) |= ((Pin_Config) << Get_CRLH_Position(PinConfig->GPIO_Pin_Num));
}

/**================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-Reset all the GPIO Registers
 * @param [in] 	-GPIOx: x(A...E)
 * @returnval 	-None
 * Note			-None
 * */
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
//	GPIOx->CRL = 	0x44444444;
//	GPIOx->CRH = 	0x44444444;
//	//GPIOx->IDR = 0x0000XXXX; (Read only)
//	GPIOx->ODR = 	0x00000000;
//	GPIOx->BSRR = 	0x00000000;
//	GPIOx->BRR = 	0x00000000;
//	GPIOx->LCKR = 	0x00000000;

	/*Or you can use the reset controller
	 *APB2 peripheral reset register (RCC_APB2RSTR)---> This is better
	 *Set and cleared by SW */
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2); //Bit 2 IOPARST: IO Port A Reset
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1<<3); //Bit 3 IOPBRST: IO Port B Reset
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1<<4); //Bit 4 IOPCRST: IO Port C Reset
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1<<5); //Bit 5 IOPDRST: IO Port D Reset
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1<<6); //Bit 6 IOPERST: IO Port E Reset
		RCC->APB2RSTR &= ~(1<<6);
	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Read Specifi Pin
 * @param [in] 	-GPIOx: x(A...E)
 * @param [in] 	-PinNumber: Set pin number according @ref GPIO_Pins_define
 * @returnval 	-The input pin value (two values based on @ref GPIO_Pin_state)
 * Note			-None
 * */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx , uint16_t PinNumber)
{
	uint8_t BitStatus;

	if(((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_Pin_Reset) //Cast 3ashan bkrnno be 7aga uint32_t
	{
		BitStatus = GPIO_Pin_Set;
	}
	else
	{
		BitStatus = GPIO_Pin_Reset;
	}
	return BitStatus;
}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-Read Specific input Port value
 * @param [in] 	-GPIOx: x(A...E)
 * @returnval 	-The input Port value
 * Note			-None
 * */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx)//uint16_t because the pin is 16 bit-> 2 bytes
{
	uint16_t PortVal ;
	PortVal = (uint16_t)GPIOx->IDR;//Input data register
	return PortVal;
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief 		-Write Specific input Port value
 * @param [in] 	-GPIOx: x(A...E)
 * @param [in] 	-PinNumber: From 0->15 Specifies the port bit to read. set by @ref GPIO_Pins_define
 * @param [in] 	-Value: pin value
 * @returnval 	-None
 * Note			-None
 * */
void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx , uint16_t PinNumber , uint8_t Value)
{
	if(Value != GPIO_Pin_Reset)
	{
		//	GPIOx->ODR |= PinNumber;
		//OR
		//		BSy: Port x Set bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Set the corresponding ODRx bi
		GPIOx->BSRR = PinNumber;
	}
	else
	{
		//		Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Reset the corresponding ODRx bit
		GPIOx->BRR = PinNumber;
	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-Write on Output port
 * @param [in] 	-GPIOx: x(A...E)
 * @returnval 	-None
 * Note			-None
 * */
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx , uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}

/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-Toggle bit on specific pin
 * @param [in] 	-GPIOx: x(A...E)
 * @param [in] 	-PinNumber: Specifies the port bit to read. set by @ref GPIO_Pins_define
 * @returnval 	-None
 * Note			-None
 * */
void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx , uint16_t PinNumber)
{
	GPIOx->ODR ^= (PinNumber);
}

/**================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-The locking mechanism allows the IO configuration to be frozen
 * @param [in] 	-GPIOx: x(A...E)
 * @param [in] 	-PinNumber: Specifies the port bit to read. set by @ref GPIO_Pins_define
 * @returnval 	-OK if pin config is locked or ERROR if pin is not locked (Ok & ERROR are defined @ ref GPIO_Return_Lock)
 * Note			-None
 * */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx , uint16_t PinNumber)
{
	/*Bit 16 LCKK[16]: Lock key
	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	0: Port configuration lock key not active
	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1 (this read is optional but confirms that the lock is active)
	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	Any error in the lock sequence will abort the lock.
	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	These bits are read write but can only be written when the LCKK bit is 0.
	0: Port configuration not locked
	1: Port configuration locked.
	 */

	//Set Lck 16
	volatile uint32_t temp = 1<<16;

	//Set the Lcky
	temp |= PinNumber;

	//	Write 1
	GPIOx->LCKR = temp;
	//	Write 0
	GPIOx->LCKR = PinNumber;
	//	Write 1
	GPIOx->LCKR = temp;
	//	Read 0
	temp = GPIOx->LCKR;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOx->LCKR & 1<<16))
	{
		return GPIO_Return_Lock_Enabled;
	}
	else
	{
		return GPIO_Return_Lock_Error;
	}
}
