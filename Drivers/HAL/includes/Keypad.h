
/*
 * Keypad.h
 *
 *  Created on: Sep 10, 2024
 *      Author: Younis
 */

#ifndef KEYPAD_DRIVER_KEYPAD_H_
#define KEYPAD_DRIVER_KEYPAD_H_

#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_drivers.h"

#define Keypad_Port					GPIOB

extern GPIO_Pin_Config_t PinCnfg;

//Rows of Keypad--> defining pins
#define R0							GPIO_Pin_0
#define R1							GPIO_Pin_1
#define R2							GPIO_Pin_3
#define R3							GPIO_Pin_4

//Columns of Keypad--> defining pins
#define C0							GPIO_Pin_5
#define C1							GPIO_Pin_6
#define C2							GPIO_Pin_7
#define C3							GPIO_Pin_8

/************Keypad Functions************/

void Keypad_Init();
char Keypad_GetChar();
#endif /* KEYPAD_DRIVER_KEYPAD_H_ */
