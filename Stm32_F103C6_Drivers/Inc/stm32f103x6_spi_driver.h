/*
 * stm32f103x6_spi_driver.h
 *
 *  Created on: Nov 19, 2024
 *      Author: Mohamed Abd El Hakeem El Said Ali
 */

#ifndef INC_STM32F103X6_SPI_DRIVER_H_
#define INC_STM32F103X6_SPI_DRIVER_H_


//Includes
#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"


//-*-*-*-*-*-*-*-*-*-*-*-
//User Type Definitions
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	uint8_t TXE	:1;
	uint8_t RXNE:1;
	uint8_t ERRI:1;
	uint8_t RES:5;

}IRQ_SOURCE;



typedef struct
{
	uint16_t  SPI_Mode;			     //config the pins either to be master or slave
	// This parameter must be set based on @ref SPI_MODE_define

	uint16_t  Communication_Mode;	//set the SPI to be a bidirectional mode
	// This parameter must be set based on @ref SPI_Communication_Mode

	uint16_t  Data_Order;			//config which bit will be send first
	// This parameter must be set based on @ref SPI_DATAORDER_define

	uint16_t  Data_Size;  			//config size of data to be sent
	// This parameter must be set based on @ref SPI_DATASIZE_define

	uint16_t  CLKPolarity;			//choosing the clock polarity
	// This parameter must be set based on @ref SPI_CLkPOL_define

	uint16_t  CLKPhase;				//choosing the clock polarity
	// This parameter must be set based on @ref SPI_CLKPhase_define

	uint16_t  NSS;					//Specifies whether the NSS signal is managed by H.W or S.W
	// This parameter must be set based on @ref SPI_NSS_define

	uint16_t  BaudRate_Prescaler;	//setting frequency for tp control SCK rate /clock getting out of the master
	// This parameter must be set based on @ref SPI_FREQUENCY_define

	uint16_t  IRQ_Enable;			//config to enable/disable interrupt
	// This parameter must be set based on @ref SPI_INTERRUPT_define

	void(*IRQ_CallBack)(IRQ_SOURCE irq);

}SPI_Config_t;


typedef enum
{
	SPIdisable,
	SPIenable
}Polling_MECH;

//---------------------------------------
//-*-*-*-*-*-*-*-*-*-*-*-
//Macros for Configurations
//-*-*-*-*-*-*-*-*-*-*-*

//@ref SPI_MODE_define
#define SPI_SLAVE_MODE    						((uint16_t)0)
#define SPI_MASTER_MODE    						((uint16_t)(1<<2))//MSTR

//@ref SPI_Communication_Mode
#define SPI_DIRECTION_2LINES   					((uint16_t)0)
#define SPI_DIRECTION_2LINES_RXONLY   			((uint16_t)(1<<10))//RXONLY
#define SPI_DIRECTION_1LINES_RECEIVEONLY  		((uint16_t)(1<<15))//BIDIMODE Bidirectional data mode enable
#define SPI_DIRECTION_1LINES_TRANSMITONLY   	(uint16_t)((1<<15)|(1<<14))//BIDIMODE and BIDIOE Output enable in bidirectional mode

//@ref SPI_DATAORDER_define
#define SPI_MSB_TRANSMITTED_FIRST				((uint16_t)0)
#define SPI_LSB_TRANSMITTED_FIRST				((uint16_t)(1<<7))//LBSFIRST


//@ref SPI_DATASIZE_define
#define SPI_8BIT_DATASIZE						((uint16_t)0)
#define SPI_16BIT_DATASIZE						((uint16_t)(1<<11))//DFF

//@ref SPI_CLkPOL_define
#define SPI_CLKPOLARITY_LOW_IDLE				((uint16_t)0)
#define SPI_CLKPOLARITY_HIGH_IDLE				((uint16_t)(1<<1))//CPOL

//@ref SPI_CLKPhase_define
#define SPI_CLKPHASE_FIRSTEDGE					((uint16_t)0)
#define SPI_CLKPHASE_SECONDEDGE					((uint16_t)(1<<0))//CPHA

//@ref SPI_NSS_define
//HARDWARE
#define SPI_NSS_Hard_Slave 						((uint16_t)0)
#define SPI_NSS_Hard_Master_SS_output_enable 	((uint16_t)(1<<2))
#define SPI_NSS_Hard_Master_SS_output_disable  ~((uint16_t)(1<<2))
//SOFTWARE
#define SPI_NSS_Soft_NSSInternalSoft_Reset		((uint16_t)(1<<9))
#define SPI_NSS_Soft_NSSInternalSoft_Set 		(uint16_t)((1<<9)|(1<<8))


//@ref SPI_FREQUENCY_define
#define SPI_BAUDRATEPRESCALER_2         ((uint16_t)(0 << 3))
#define SPI_BAUDRATEPRESCALER_4         ((uint16_t)(1 << 3))
#define SPI_BAUDRATEPRESCALER_8         ((uint16_t)(2 << 3))
#define SPI_BAUDRATEPRESCALER_16        ((uint16_t)(3 << 3))
#define SPI_BAUDRATEPRESCALER_32        ((uint16_t)(4 << 3))
#define SPI_BAUDRATEPRESCALER_64        ((uint16_t)(5 << 3))
#define SPI_BAUDRATEPRESCALER_128       ((uint16_t)(6 << 3))
#define SPI_BAUDRATEPRESCALER_256       ((uint16_t)(7 << 3))


//@ref SPI_INTERRUPT_define
#define SPI_IRQ_Disable             	((uint16_t)(0))
#define SPI_IRQ_Enable_TXEIE            ((uint16_t)(1<<7))
#define SPI_IRQ_Enable_RXNEIE           ((uint16_t)(1<<6))
#define SPI_IRQ_Enable_ERRIE			((uint16_t)(1<<5))




//API
void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Config_t* SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx);

void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *data_buffer,Polling_MECH Polling);
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *data_buffer ,Polling_MECH Polling);

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t *data_buffer,Polling_MECH Polling);



#endif /* INC_STM32F103X6_SPI_DRIVER_H_ */
