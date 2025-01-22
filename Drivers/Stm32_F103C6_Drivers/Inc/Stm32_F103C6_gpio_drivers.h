
/*
 * Stm32_F103C6_gpio_drivers.h
 *
 *  Created on: Sep 11, 2024
 *      Author: Younis
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVERS_H_
#define INC_STM32_F103C6_GPIO_DRIVERS_H_

//-----------------------------
//Includes
//-----------------------------

#include "stm32f103x6.h"

//==============================================================//


//-----------------------------
//Config structure
//-----------------------------
typedef struct
{
	/*Specifies the gpio pins to be configured
	 *This parameter must be set based on @ref GPIO_Pin_define*/
	uint16_t GPIO_Pin_Num;

	/*Specifies the operating mode for the selected pins
	 *This parameter can be a value of @ref GPIO_Mode_define*/
	uint8_t GPIO_Mode;

	/*Specifies the speed for the selected pins
	 *This parameter can be a value of @ref GPIO_Speed_define*/
	uint8_t GPIO_Output_Speed;

}GPIO_Pin_Config_t;//t->typedef



//-----------------------------
//Macros Configuration Refrences
//-----------------------------


// @ref GPIO_Return_Lock
#define GPIO_Return_Lock_Enabled		1
#define GPIO_Return_Lock_Error			0

// @ref GPIO_Pin_State
#define GPIO_Pin_Set					1
#define GPIO_Pin_Reset					0

// @ref GPIO_Pin_define
#define GPIO_Pin_0						((uint16_t)0x0001) /*Pin 0 selected*/
#define GPIO_Pin_1						((uint16_t)0x0002) /*Pin 1 selected->10*/
#define GPIO_Pin_2						((uint16_t)0x0004) /*Pin 2 selected->100*/
#define GPIO_Pin_3						((uint16_t)0x0008) /*Pin 3 selected->1000*/
#define GPIO_Pin_4						((uint16_t)0x0010) /*Pin 4 selected->10000*/
#define GPIO_Pin_5						((uint16_t)0x0020) /*Pin 5 selected*/
#define GPIO_Pin_6						((uint16_t)0x0040) /*Pin 6 selected*/
#define GPIO_Pin_7						((uint16_t)0x0080) /*Pin 7 selected*/
#define GPIO_Pin_8						((uint16_t)0x0100) /*Pin 8 selected*/
#define GPIO_Pin_9						((uint16_t)0x0200) /*Pin 9 selected*/
#define GPIO_Pin_10						((uint16_t)0x0400) /*Pin 10 selected*/
#define GPIO_Pin_11						((uint16_t)0x0800) /*Pin 11 selected*/
#define GPIO_Pin_12						((uint16_t)0x1000) /*Pin 12 selected*/
#define GPIO_Pin_13						((uint16_t)0x2000) /*Pin 13 selected*/
#define GPIO_Pin_14						((uint16_t)0x4000) /*Pin 14 selected*/
#define GPIO_Pin_15						((uint16_t)0x8000) /*Pin 15 selected*/
#define GPIO_Pin_All					((uint16_t)0xFFFF) /*All Pins selected*/

#define GPIO_Pin_Mask					0x0000FFFFu		   /*Pin mask for assert test*/


//@ref ////GPIO_Mode_define////
/*In input mode (MODE[1:0]=00):
00: Analog mode							->0
01: Floating input (reset state)		->1
10: Input with pull-up / pull-down		->2
11: Reserved->fa momken a5leha pul down	->3
In output mode (MODE[1:0] > 00):
4: General purpose output push-pull
5: General purpose output Open-drain
6: Alternate function output Push-pull
7: Alternate function output Open-drain
8: Alternate function input*/

#define GPIO_Mode_Analog				0x00000000u //Analog mode
#define GPIO_Mode_Input_Flo				0x00000001u //Floating input
#define GPIO_Mode_Input_PU				0x00000002u //Input with pull-up
#define GPIO_Mode_Input_PD				0x00000003u //Input with pull-down
#define GPIO_Mode_Output_PP				0x00000004u //General purpose output push-pull
#define GPIO_Mode_Output_OD				0x00000005u //General purpose output Open-drain
#define GPIO_Mode_Output_AF_PP			0x00000006u //Alternate function output Push-pull
#define GPIO_Mode_Output_AF_OD			0x00000007u //Alternate function output Open-drain
#define GPIO_Mode_AF_Input				0x00000008u //Alternate function input


//@ref GPIO_Speed_define
/*
00: Input mode (reset state)		->0
01: Output mode, max speed 10 MHz.	->1
10: Output mode, max speed 2 MHz.	->2
11: Output mode, max speed 50 MHz	->3
*/

#define GPIO_Speed_10MHz				0x00000001u	//Output mode, max speed 10 MHz
#define GPIO_Speed_2MHz					0x00000002u	//Output mode, max speed 2 MHz
#define GPIO_Speed_50MHz				0x00000003u	//Output mode, max speed 50 MHz


/*
 * ==============================================================================
 * 							APIs Supported by "MCAL GPIO Driver"
 * ==============================================================================
 */

void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx , GPIO_Pin_Config_t* PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx , uint16_t PinNumber);//PinN(0->15) so its 2 bytes
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx);//Contains 16 bit (0->15)so 2 bytes

void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx , uint16_t PinNumber , uint8_t Value);//PinN(0->15) so its 2 bytes
void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx , uint16_t Value);//Contains 16 bit (0->15)so 2 bytes

void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx , uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef* GPIOx , uint16_t PinNumber);



#endif /* INC_STM32_F103C6_GPIO_DRIVERS_H_ */
