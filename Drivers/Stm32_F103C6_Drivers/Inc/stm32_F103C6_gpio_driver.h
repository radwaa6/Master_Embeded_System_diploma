/*
 * stm32_F103C6_gpio_driver.h
 *
 *  Created on: Feb 9, 2024
 *      Author: hassan
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_

//Includes

#include "stm32f103x6.h"


//Configuration Structure



typedef struct{


	uint16_t GPIO_PinNumber;  //this member Specifies which GPIO Pin to be configured.
							  //This member must be set based on @ref GPIO_PINS_define


	uint8_t GPIO_Pin_Config;	//This member specifies what configuration will be applied on the selected pin
								//This member must be set based on @ref GPIO_CONFIG_define

	uint8_t GPIO_Mode_config;	//This member configures the speed of the selected pin
								//This member must be set based on @ref GPIO_MODE_define & when configuring the pin as an output



}GPIO_PinConfig_t;


//@ref GPIO_PINS_define

#define GPIO_PINS_0			((uint16_t)0x0001)// Pin 1 selected
#define GPIO_PINS_1			((uint16_t)0x0002)// Pin 2 selected
#define GPIO_PINS_2			((uint16_t)0x0004)// Pin 3 selected
#define GPIO_PINS_3			((uint16_t)0x0008)// Pin 4 selected
#define GPIO_PINS_4			((uint16_t)0x0010)// Pin 5 selected
#define GPIO_PINS_5			((uint16_t)0x0020)// Pin 6 selected
#define GPIO_PINS_6			((uint16_t)0x0040)// Pin 7 selected
#define GPIO_PINS_7			((uint16_t)0x0080)// Pin 8 selected
#define GPIO_PINS_8			((uint16_t)0x0100)// Pin 9 selected
#define GPIO_PINS_9			((uint16_t)0x0200)// Pin 10 selected
#define GPIO_PINS_10		((uint16_t)0x0400)// Pin 11 selected
#define GPIO_PINS_11		((uint16_t)0x0800)// Pin 12 selected
#define GPIO_PINS_12		((uint16_t)0x1000)// Pin 13 selected
#define GPIO_PINS_13		((uint16_t)0x2000)// Pin 14 selected
#define GPIO_PINS_14		((uint16_t)0x4000)// Pin 15 selected
#define GPIO_PINS_15		((uint16_t)0x8000)// Pin 16 selected
#define	GPIO_PINS_ALL		((uint16_t)0xFFFF)// All pins selected

#define GPIO_PIN_MASK		0x0000FFFFU	//PIN mask for assert test



//@ref GPIO_CONFIG_define

#define GPIO_CONFIG_Analog									((uint8_t)0x00U) //0 For Analog mode
#define GPIO_CONFIG_Floating_Input							((uint8_t)0x01U) //1 For Floating input (reset state)
#define GPIO_CONFIG_Input_PU								((uint8_t)0x02U) //2 For Input with pull-up
#define GPIO_CONFIG_Input_PD								((uint8_t)0x03U) //3 For Input with  pull-down
#define GPIO_CONFIG_Output_PP 								((uint8_t)0x04U) //4 For General purpose output push-pull
#define GPIO_CONFIG_Output_OD								((uint8_t)0x05U) //5 For General purpose output Open-drain
#define GPIO_CONFIG_Alternate_Output_PP						((uint8_t)0x06U) //6 For Alternate function output Push-pull
#define GPIO_CONFIG_Alternate_Output_OD						((uint8_t)0x07U) //7 For Alternate function output Open-drain*/
#define GPIO_CONFIG_Alternate_Input							((uint8_t)0x08U) //8 For Alternate function INPUT



//@ref GPIO_MODE_define


#define GPIO_MODE_Output_10MHz			((uint8_t)0x01U) 	//1 For 10MHz max speed
#define GPIO_MODE_Output_2MHz			((uint8_t)0x02U) 	//2 For 2MHz  max speed
#define GPIO_MODE_Output_50MHz			((uint8_t)0x03U)	//3 For 50MHz max speed






//@ref GPIO_Pin_State


#define GPIO_PIN_SET 	(1U)
#define GPIO_PIN_RESET	(0U)

//@ref GPIO_RETURN_LOCK

#define GPIO_RETURN_LOCK_OK		1U
#define GPIO_RETURN_LOCK_ERROR	0U



/*
 * =================================================================================
 *
 * 							APIs Supported by "MCAL GPIO DRIVER"
 *
 * =================================================================================
 *
 */

void MCAL_GPIO_INIT (GPIO_typedef* GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DeInit (GPIO_typedef* GPIOx);
//Read APIs
uint8_t		MCAL_GPIO_ReadPin 	(GPIO_typedef* GPIOx, uint16_t PinNumber);
uint16_t	MCAL_GPIO_ReadPort 	(GPIO_typedef* GPIOx);

//Write APIs
void		MCAL_GPIO_WritePin 	(GPIO_typedef* GPIOx, uint16_t PinNumber, uint8_t value);
void		MCAL_GPIO_WritePort (GPIO_typedef* GPIOx, uint16_t value);
void		MCAL_GPIO_TogglePin	(GPIO_typedef* GPIOx, uint16_t PinNumber);
uint8_t		MCAL_GPIO_LockPin   (GPIO_typedef* GPIOx, uint16_t PinNumber);


#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
