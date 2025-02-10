/*
 * RCC.h
 *
 *  Created on: Apr 9, 2024
 *      Author: hassa
 */

#ifndef RCC_DRIVER_RCC_H_
#define RCC_DRIVER_RCC_H_

#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"

#define HSE_CLK		(uint32_t)16000000
#define HSI_RC_CLK	(uint32_t)8000000


uint32_t	MCAL_RCC_GETSYSCLKfreq(void);
uint32_t	MCAL_RCC_GETHCLKfreq(void);
uint32_t	MCAL_RCC_GETPCLK1Freq(void);
uint32_t 	MCAL_RCC_GETPCLK2Freq(void);










#endif /* RCC_DRIVER_RCC_H_ */
