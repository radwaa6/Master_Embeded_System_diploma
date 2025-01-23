/*
 * stm32_F103C6_gpio_driver.c
 *
 *  Created on: Feb 9, 2024
 *      Author: hassan
 */




#include "stm32_F103C6_gpio_driver.h"

uint8_t Get_CRLH_Position(uint16_t	PinNumber){


	switch(PinNumber){


	case GPIO_PINS_0:
		return 0;
		break;
	case GPIO_PINS_1:
		return 4;
		break;
	case GPIO_PINS_2:
		return 8;
		break;
	case GPIO_PINS_3:
		return 12;
		break;
	case GPIO_PINS_4:
		return 16;
		break;
	case GPIO_PINS_5:
		return 20;
		break;
	case GPIO_PINS_6:
		return 24;
		break;
	case GPIO_PINS_7:
		return 28;
		break;
	case GPIO_PINS_8:
		return 0;
		break;
	case GPIO_PINS_9:
		return 4;
		break;
	case GPIO_PINS_10:
		return 8;
		break;
	case GPIO_PINS_11:
		return 12;
		break;
	case GPIO_PINS_12:
		return 16;
		break;
	case GPIO_PINS_13:
		return 20;
		break;
	case GPIO_PINS_14:
		return 24;
		break;
	case GPIO_PINS_15:
		return 28;
		break;



	}


	return 0;




}








/*=======================================================================================================
 *
 * @Fn    			-MCAL_GPIO_INIT
 * @brief			-Initializes the GPIOx PINy according to the specified parameters in the PinConfig.
 * @Param[in]		-GPIOx: where x can be (A..E depending on used Port ) to select the GPIO peripheral
 * @Param[in]		-PinConfig: pointer to a  GPIO_PinConfig_t structure that contains the
 * 					   the configuration info for the specified GPIO PIN.
 * @retval			-None
 * @Note			-STM32F103C6 MCU has GPIO A,B,C,D,and E Modules
 * 						But the fabrication model (LQFP48) has only GPIO A,B, and part of C/D exported as external PINS from MCU
 *
 * */






void MCAL_GPIO_INIT (GPIO_typedef* GPIOx, GPIO_PinConfig_t* PinConfig){

	//Port configuration register low (GPIOx_CRL) : Configure pins from 0>>>7
	//Port configuration register low (GPIOx_CRH) : Configure pins from 8>>>15
	volatile	uint32_t* Config_Register = NULL;
	uint8_t Pin_config = 0 ;
	// 0->7 CRL ... 8->15 CRH
	Config_Register = (PinConfig->GPIO_PinNumber < GPIO_PINS_8)?	&GPIOx->CRL : &GPIOx->CRH;
	//clear clear CNF8[1:0] MODE8[1:0]
	(*Config_Register) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	//if pin configured as output
	if((PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Output_PP)||(PinConfig->GPIO_Pin_Config  == GPIO_CONFIG_Output_OD)||(PinConfig->GPIO_Pin_Config  == GPIO_CONFIG_Alternate_Output_OD)||(PinConfig->GPIO_Pin_Config  == GPIO_CONFIG_Alternate_Output_PP))
	{
		//(Mode - 4) = true configuration position in data sheet --> see @ref GPIO_CONFIG_define and datasheet difference
		Pin_config = ( ( ( (PinConfig->GPIO_Pin_Config - 4 ) << 2 ) | (PinConfig->GPIO_Mode_config)) & 0x0F );
		(*Config_Register) |= ( Pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );

	}

	//if pin configured as input
	else
	{

		if((PinConfig->GPIO_Pin_Config  == GPIO_CONFIG_Floating_Input) || (PinConfig->GPIO_Pin_Config  == GPIO_CONFIG_Analog))
		{
			Pin_config = ((((PinConfig -> GPIO_Pin_Config) << 2) | (0)) & 0x0F );
			(*Config_Register) |= ( Pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );

		}
		else if((PinConfig->GPIO_Pin_Config  == GPIO_CONFIG_Input_PU)||(PinConfig->GPIO_Pin_Config  == GPIO_CONFIG_Input_PD ))
		{
			switch(PinConfig->GPIO_Pin_Config)
			{
			case  GPIO_CONFIG_Input_PU :
				GPIOx->ODR |= (PinConfig->GPIO_PinNumber);
				Pin_config = (((PinConfig->GPIO_Pin_Config << 2 )|(0))&0x0F);
				break;
			case GPIO_CONFIG_Input_PD :
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
				Pin_config = ((((PinConfig->GPIO_Pin_Config-1) << 2 )|(0))&0x0F);
				break;


			}

			( *Config_Register ) |= ( Pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );

		}
		else if(PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Alternate_Input)
		{ 	//pin is alternative input (same as input floating)
			Pin_config = ( (((PinConfig->GPIO_Pin_Config-7) << 2) | (0)) & 0x0F	);
			(*Config_Register) |= ( Pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );

		}




	}





















	/*

	if(PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Analog)
	{
		(*Config_Register) |= 0b0000 << Get_CRLH_Position(PinConfig->GPIO_PinNumber);

	}

	else if(PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Floating_Input)
	{
		(*Config_Register) |= 0b0100 << Get_CRLH_Position(PinConfig->GPIO_PinNumber);

	}
	else if(PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Input_PU){

		(*Config_Register) |= 0b1000 << Get_CRLH_Position(PinConfig->GPIO_PinNumber);
		GPIOx->ODR |= 1<<(PinConfig->GPIO_PinNumber);


	}

	else if(PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Input_PD){

		(*Config_Register) |= 0b1000 << Get_CRLH_Position(PinConfig->GPIO_PinNumber);
		GPIOx->ODR &= ~(1<<PinConfig->GPIO_PinNumber);
	}

	else if(PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Output_PP)
	{
		Pin_config = ((0b0000 | PinConfig->GPIO_Mode_config) & 0x0f);
	 *(Config_Register) |= (Pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
	}
	else if(PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Output_OD)
	{
		Pin_config = ((0b0100 | PinConfig->GPIO_Mode_config) & 0x0f);
	 *(Config_Register) |= (Pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
	}
	else if(PinConfig->GPIO_Pin_Config == GPIO_CONFIG_Alternate_Output_PP)
	{ 	Pin_config = ((0b1000 | PinConfig->GPIO_Mode_config) & 0x0f);
	 *(Config_Register) |= (Pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	}
	else//Alternative Output Open-Drain
	{
		Pin_config = ((0b1100 | PinConfig->GPIO_Mode_config) & 0x0f);
	 *(Config_Register) |= (Pin_config << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	}

	 */


}




/*
 *
 * @Fn    			-MCAL_GPIO_DeInit
 * @brief			-Reset All GPIO Registers.
 * @Param[in]		-GPIOx: where x can be (A..E depending on used Port ) to select the GPIO peripheral
 * @retval			-None
 * @Note			-None
 *
 * */



void MCAL_GPIO_DeInit (GPIO_typedef* GPIOx)
{

	//Deinit via RCC module
	//note: you can reset GPIO instants manually by putting reset value for each GPIOx register
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);

	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);

	}
	else if(GPIOx == GPIOD)
	{

		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);


	}
	else if (GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);

	}




}





/*=======================================================================================================
 *
 * @Fn    			-MCAL_GPIO_ReadPin
 * @brief			-Read a specific Pin.
 * @Param[in]		-GPIOx: where x can be (A..E depending on used Port ) to select the GPIO peripheral
 * @Param[in]		-PinNumber: Set Pin number according @ref GPIO_PINS_define
 * @retval			-the input pin values will be (two values based on @ref GPIO_Pin_State)
 * @Note			-None
 *
 * */




uint8_t	 MCAL_GPIO_ReadPin (GPIO_typedef* GPIOx, uint16_t PinNumber){

	uint8_t bit_status;
	if(((GPIOx->IDR) & PinNumber ) != GPIO_PIN_RESET)
	{
		bit_status = GPIO_PIN_SET;


	}
	else {

		bit_status = GPIO_PIN_RESET;

	}

	return bit_status;
}






/*=======================================================================================================
 *
 * @Fn    			-MCAL_GPIO_ReadPort
 * @brief			-Read a specific PORT.
 * @Param[in]		-GPIOx: where x can be (A..E depending on used Port ) to select the GPIO peripheral
 * @retval			-the input PORT value
 * @Note			-None
 *
 * */




uint16_t MCAL_GPIO_ReadPort (GPIO_typedef* GPIOx)
{
	uint16_t port_status ;

	port_status = ((uint16_t)(GPIOx->IDR));

	return port_status;



}







/*=======================================================================================================
 *
 * @Fn    			-MCAL_GPIO_WritePin
 * @brief			-Write  on a specific output Pin.
 * @Param[in]		-GPIOx: where x can be (A..E depending on used Port ) to select the GPIO peripheral
 * @Param[in]		-PinNumber: Set Pin number according @ref GPIO_PINS_define
 * @Param[in]		-Value:Pin value
 * @retval			-None
 * @Note			-None
 *
 * */








void MCAL_GPIO_WritePin (GPIO_typedef* GPIOx, uint16_t PinNumber, uint8_t Value)
{
	if(Value != (GPIO_PIN_RESET))
	{

		//GPIOx->ODR |= PinNumber;
		//or
		//you can use atomic bit (BSRR )set/reset instead of using ODR register

		/*	Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Set the corresponding ODRx bit*/
		GPIOx->BSRR = (uint32_t)PinNumber;


	}

	else
	{	//GPIO->ODR &= PinNumber;
		//or
		/*
		Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Reset the corresponding ODRx bit*/

		GPIOx->BRR = (uint32_t)PinNumber;

	}



}







/*=======================================================================================================
 *
 * @Fn    			-MCAL_GPIO_WritePort
 * @brief			-Write on a specific output PORT.
 * @Param[in]		-GPIOx: where x can be (A..E depending on used Port ) to select the GPIO peripheral
 * @Param[in]		-Value: Port value
 * @retval			-None
 * @Note			-None
 *
 * */





void MCAL_GPIO_WritePort (GPIO_typedef* GPIOx, uint16_t Value)
{

	GPIOx->ODR = (uint32_t)Value;

}







/*=======================================================================================================
 *
 * @Fn    			-MCAL_GPIO_WritePort
 * @brief			-Toggle a specific GPIO Pin.
 * @Param[in]		-GPIOx: where x can be (A..E depending on used Port ) to select the GPIO peripheral
 * @Param[in]		-PinNumber: Set Pin number according @ref GPIO_PINS_define
 * @retval			-None
 * @Note			-None
 *
 * */




void MCAL_GPIO_TogglePin	(GPIO_typedef* GPIOx, uint16_t PinNumber)
{

	GPIOx->ODR ^= (PinNumber);


}






/*=======================================================================================================
 *
 * @Fn    			-MCAL_GPIO_LockPin
 * @brief			-Lock or freeze a specific GPIO Pin so, you can't make apply any configuration on this specific pin.
 * @Param[in]		-GPIOx: where x can be (A..E depending on used Port ) to select the GPIO peripheral
 * @Param[in]		-PinNumber: Set Pin number according @ref GPIO_PINS_define
 * @retval			-OK if the selected pin is locked OR ERROR if the selected Pin isn't locked (OK or ERROR can be found @ref GPIO_RETURN_LOCK)
 * @Note			-When you lock a specific pin, The pin will retain its last configuration.
 *
 * */



uint8_t MCAL_GPIO_LockPin   (GPIO_typedef* GPIOx, uint16_t PinNumber)
{	//to lock any pin, you should apply lock sequence on bit 16(LCKK)
	volatile uint32_t tmp_lock_profile = 0;

	tmp_lock_profile |= (1<<16);

	tmp_lock_profile = PinNumber;

	//Write 1
	GPIOx->LCKR = tmp_lock_profile;
	//write 0
	GPIOx->LCKR = PinNumber;
	//write 1
	GPIOx->LCKR = tmp_lock_profile;
	//Read 0
	tmp_lock_profile= GPIOx->LCKR;
	//Read 1 (this read is optional but confirms that the lock is active)
	if(  (uint32_t)(GPIOx->LCKR & 1<<16)  )
	{

		return (uint8_t)GPIO_RETURN_LOCK_OK;

	}
	else
	{
		return (uint8_t)GPIO_RETURN_LOCK_ERROR;

	}







}
