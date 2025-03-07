/*
 * uart.h
 *
 *  Created on: Apr 13, 2024
 *      Author: hassa
 */

#ifndef USART_UART_H_
#define USART_UART_H_


//Includes

#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"
#include "stm32_F103C6_EXTI_driver.h"
#include "RCC.h"

//Configuration structure


typedef struct
{
	uint8_t		USART_Mode;	//Specifies the TX/RX Enable/Disable
							//This member must be set based on @ref USART_MODE_DEFINE

	uint32_t	Baud_Rate; 		//This member configure USART communication baud rate
								//This member must be set based on @ref USART_BaudRate_DEFINE

	uint8_t		Payload_Length;	//This member specify how much data will be transmitted
								//This member must be set based on @ref	USART_Payload_Length_define


	uint8_t		Parity;			//This member specify	type of parity to choose
								//This member must be set based on @ref	USART_Parity_Type_define


	uint8_t		Stop_bits;		//This member Specify how many stop bits will be used
								//This member must be set based on @ref	USART_STOP_Bits_Define

	uint8_t		Flow_Control;	//This member Specify if the flow control(CTS/RTS) will be enabled or not
								//This member must be set based on @ref USART_FLOW_CONTROL_Define

	uint8_t		IRQ_Enable;		//This member made to Enable/Disable UART IRQ TX/RX & other parameters
								//This member must be set based on @ref USART_IRQ_Enable_Define

	void(*  P_IRQ_Callback)(void);		//Set the C Function() which will be called once the IRQ happen


}USART_Config;





//------------------------------------------
//=======USART REFERENCE MACROS======
//------------------------------------------

//@ref USART_MODE_DEFINE


#define	USART_MODE_TX	(uint32_t)(1<<3)//TE: Transmitter enable
#define	USART_MODE_RX	(uint32_t)(1<<2)//RE: Receiver enable
#define	USART_MODE_TX_RX (uint32_t)((1<<2)|(1<<3))


//@ref USART_BaudRate_DEFINE



#define USART_BAUDRATE_2400				2400
#define USART_BAUDRATE_9600				9600
#define USART_BAUDRATE_19200			19200
#define USART_BAUDRATE_57600			57600
#define USART_BAUDRATE_115200			115200
#define USART_BAUDRATE_230400			230400
#define USART_BAUDRATE_460800			460800
#define USART_BAUDRATE_921600			921600
#define USART_BAUDRATE_2250000			2250000
#define USART_BAUDRATE_4500000			4500000


//@ref	USART_Payload_Length_define


#define USART_8_DATA_Bits		(uint32_t)(0)
#define USART_9_DATA_Bits		(uint32_t)(1<<12)


//@ref	USART_Parity_Type_define

#define	USART_Parity_Type_None	(uint32_t)(0)
#define	USART_Parity_Type_Even	((uint32_t)1<<10)
#define	USART_Parity_Type_Odd	((uint32_t)(1<<10|1<<9))




//@ref	USART_STOP_Bits_Define

#define	USART_STOP_Bits_Half		((uint32_t)1<<12)
#define	USART_STOP_Bits_one			((uint32_t)0)
#define	USART_STOP_Bits_One_Half	((uint32_t)3<<12)
#define	USART_STOP_Bits_Two			((uint32_t)2<<12)



//@ref USART_FLOW_CONTROL_Define

#define USART_FLOW_CONTROL_None			((uint32_t)0)
#define USART_FLOW_CONTROL_CTS			((uint32_t)1<<9)
#define USART_FLOW_CONTROL_RTS			((uint32_t)1<<8)
#define USART_FLOW_CONTROL_CTS_RTS		((uint32_t)(1<<8|1<<9))




//@ref USART_IRQ_Enable_Define

#define USART_IRQ_Disable				((uint32_t)0)
#define USART_IRQ_Enable_PEIE			((uint32_t)1<<8)
#define USART_IRQ_Enable_TXEIE			((uint32_t)1<<7)
#define USART_IRQ_Enable_TCIE			((uint32_t)1<<6)
#define USART_IRQ_Enable_RXNEIE 		((uint32_t)1<<5)



//Enums

enum Polling_mechanism
{
	Enable,
	Disable
};



//=====================================================
//		APIs Supported by "MCAL USART DRIVER"
//=====================================================


void MCAL_UART_Init (USART_TypeDef* USARTx, USART_Config* UART_Config);
void MCAL_UART_DeInit (USART_TypeDef* USARTx);
void MCAL_UART_SendData (USART_TypeDef* USARTx, uint16_t*pTxBuffer,enum Polling_mechanism PollingEnable);
void MCAL_UART_ReceiveData (USART_TypeDef* USARTx, uint16_t*RTxBuffer,enum Polling_mechanism PollingEnable);
void MCAL_UART_GPIO_Set_Pins (USART_TypeDef* USARTx);
void MCAL_UART_Wait_TC (USART_TypeDef* USARTx);

void MCAL_UART_SendString(USART_TypeDef *USARTx, uint8_t *str);




//Useful Macros to Calculate exact baudrate


#define USARTDIV(_PCLK_, _BAUD_)							(unsigned int)(_PCLK_ / (16* _BAUD_))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(unsigned int)( ( 25 * _PCLK_ ) / ( 4 * _BAUD_) )
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(unsigned int)( ( USARTDIV(_PCLK_, _BAUD_) ) * 100 )
#define Mantissa(_PCLK_, _BAUD_)							(unsigned int)(USARTDIV(_PCLK_, _BAUD_))
#define DIV_Fraction(_PCLK_, _BAUD_)						(unsigned int)( ( (  USARTDIV_MUL100(_PCLK_, _BAUD_)   -  Mantissa_MUL100(_PCLK_, _BAUD_) ) *  16 ) /100 )
#define USART_BRR_Register(_PCLK_, _BAUD_)					( (Mantissa(_PCLK_, _BAUD_) << 4) | ( ( DIV_Fraction(_PCLK_, _BAUD_) & 0xF ) )	)


#endif /* USART_UART_H_ */
