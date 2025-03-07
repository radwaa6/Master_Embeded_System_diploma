/*
 * stm32f103x6_usart_driver.c
 *
 *  Created on: Nov 6, 2024
 *      Author: Mohamed Abd El Hakeem El Said Ali
 */



#include "uart.h"



/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
USART_Config* Global_config = NULL;

/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */


/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */

/**================================================================
 * @Fn				-MCAL_UART_Init
 * @brief 			- Initializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- UART_Config: All UART Configuration EXTI_PinConfig_t
 * @retval 			-none
 * Note				-Support for Now Asynch mode & Clock 8 MHZ S
 */
void MCAL_UART_Init (USART_TypeDef *USARTx, USART_Config* UART_Config)
{
	Global_config = UART_Config ;
	uint32_t pclk ,BRR  ;
	//	enable the Clock for given USART peripheral

	if ( USARTx == USART1 )
		RCC_USART1_CLK_EN();

	else if ( USARTx == USART2 )
		RCC_USART2_CLK_EN();

	else if ( USARTx == USART3 )
		RCC_USART3_CLK_EN();



	//Enable USART Module
	//	USART_CR1  Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13 ;

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	//	USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_Config->USART_Mode ;

	//PAYLOAD Width
	// USARTx->CR1  Bit 12 M: Word length
	USARTx->CR1 |= UART_Config->Payload_Length ;

	//Configuration of parity control bit fields
	// USARTx->CR1 	Bit 10 PCE: Parity control enable     Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->Parity ;

	//configure the number of stop bits
	//USART_CR2  Bits 13:12 STOP: STOP bits
	USARTx->CR2 |= UART_Config->Stop_bits ;


	//USART hardware flow control
	//USART_CR3  Bit 9 CTSE: CTS enable   Bit 8 RTSE: RTS enable
	USARTx->CR3 |= UART_Config->Flow_Control;
 ;


	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2, 3
	//PCLK2 for USART1
	if ( USARTx == USART1 )
	{
		pclk = MCAL_RCC_GETPCLK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_GETPCLK1Freq();
	}

	BRR = USART_BRR_Register(pclk,UART_Config->Baud_Rate);

	USARTx->BRR = BRR ;


	//ENABLE / DISABLE Interrupt
	//USART_CR1
	if (UART_Config->IRQ_Enable  != USART_IRQ_Disable)
	{
		USARTx->CR1 |= (UART_Config->IRQ_Enable) ;
		//		Enable NVIC For USARTx IRQ
		if ( USARTx == USART1 )
			NVIC_IRQ37_USART1_Enable ;

		else if ( USARTx == USART2 )
			NVIC_IRQ38_USART2_Enable ;

		else if ( USARTx == USART3 )
			NVIC_IRQ39_USART3_Enable ;
	}

}
/**================================================================
 * @Fn				-MCAL_UART_DEInit
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 */
void MCAL_UART_DeInit (USART_TypeDef *USARTx)
{
	if ( USARTx == USART1 )
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable ;

	}

	else if ( USARTx == USART2 )
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_Disable ;


	}

	else if ( USARTx == USART3 )
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_Disable ;

	}


}





/*********************************************************************
 * @fn      		  - MCAL_UART_SendData
 *
 * @brief             -Send Buffer on UART
 *
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param[in]         -pTxBuffer Buffer
 * @param[in]         -PollingEn   Enable pooling or dsable it
 *
 * @return            -

 * @Note              - Should initialize UART First
 * 		//			When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
			//			the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
			//			because it is replaced by the parity.
			//			When receiving with the parity enabled, the value read in the MSB bit is the received parity
			//			bit

 */

void MCAL_UART_SendData	(USART_TypeDef *USARTx, uint16_t *pTxBuffer,enum Polling_mechanism PollingEnable )
{
	//uint16_t *pdata;

	// wait until TXE flag is set in the SR
	if (PollingEnable  == Enable)
		while(! (USARTx->SR & 1<<7 ) );

	//Check the USART_WordLength item for 9BIT or 8BIT in a frame
	if (Global_config->Payload_Length == USART_9_DATA_Bits)
	{
		//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits

		//			When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
		//			the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
		//			because it is replaced by the parity.
		//			When receiving with the parity enabled, the value read in the MSB bit is the received parity
		//			bit.
		//
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);

	}else
	{
		//This is 8bit data transfer
		USARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);
	}




}



void MCAL_UART_WAIT_TC (USART_TypeDef *USARTx )
{
	// wait till TC flag is set in the SR
	while( ! (USARTx->SR & 1<<6 ));
}



void MCAL_UART_ReceiveData	(USART_TypeDef *USARTx, uint16_t *pRxBuffer ,enum Polling_mechanism PollingEnable )
{
	//Loop over until "Len" number of bytes are transferred
	//wait until RXNE flag is set in the SR
	if (PollingEnable ==  Enable)
	{
		while( ! (USARTx->SR & 1<<5 ));
	}


	//Check the USART_WordLength item for 9BIT or 8BIT in a frame
	if (Global_config->Payload_Length == USART_9_DATA_Bits)
	{
		if (Global_config->Parity ==USART_Parity_Type_None)
		{
			//no parity So all 9bit are considered data
			*((uint16_t*) pRxBuffer) = USARTx->DR ;

		}else
		{
			//Parity is used, so, 8bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF );

		}

	}else
	{
		//This is 8bit data
		if (Global_config->Parity ==USART_Parity_Type_None)
		{
			//no parity So all 8bit are considered data
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0xFF ) ;

		}else
		{
			//Parity is used, so,7 bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = ( USARTx->DR  & (uint8_t)0X7F );

		}
	}


}



/**================================================================
 * @Fn				-MCAL_UART_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_Pins (USART_TypeDef *USARTx)
{
	GPIO_PinConfig_t PinCfg ;
	AFIO_CLOCK_ENABLE;

	if ( USARTx == USART1 )
	{
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		GPIOA_CLOCK_ENABLE;

		//PA9 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
		PinCfg.GPIO_Speed = GPIO_Speed_10MHz;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA10 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_Mode = GPIO_Mode_Inp_AF;
		PinCfg.GPIO_Speed = GPIO_Speed_Reset_State;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if (Global_config->Flow_Control   ==USART_FLOW_CONTROL_CTS   || Global_config->Flow_Control   ==USART_FLOW_CONTROL_RTS    ){
			//PA11 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_Mode = GPIO_Mode_Inp_Floating;
			PinCfg.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}


		if (Global_config->Flow_Control  ==USART_FLOW_CONTROL_RTS  || Global_config->Flow_Control  ==USART_FLOW_CONTROL_CTS  )
		{
			//PA12 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
			PinCfg.GPIO_Speed = GPIO_Speed_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
	}
	else if ( USARTx == USART2 )
	{
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS
		GPIOA_CLOCK_ENABLE;


		//PA2 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
		PinCfg.GPIO_Speed = GPIO_Speed_10MHz;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA3 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_Mode = GPIO_Mode_Inp_AF;
		PinCfg.GPIO_Speed = GPIO_Speed_Reset_State;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if (Global_config->Flow_Control  ==USART_FLOW_CONTROL_CTS  || Global_config->Flow_Control  ==USART_FLOW_CONTROL_RTS  )
		{
			//PA0 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_Mode = GPIO_Mode_Inp_Floating;
			PinCfg.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if (Global_config->Flow_Control  ==USART_FLOW_CONTROL_RTS || Global_config->Flow_Control  ==USART_FLOW_CONTROL_CTS  )
		{
			//PA1 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
			PinCfg.GPIO_Speed = GPIO_Speed_10MHz;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}
	else if ( USARTx == USART3 )
	{
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS
		GPIOA_CLOCK_ENABLE;
		GPIOB_CLOCK_ENABLE;



		//PB10 TX
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
		PinCfg.GPIO_Speed = GPIO_Speed_10MHz;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//PB11 RX
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_Mode = GPIO_Mode_Inp_AF;
		PinCfg.GPIO_Speed = GPIO_Speed_Reset_State;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		if (Global_config->Flow_Control  ==USART_FLOW_CONTROL_CTS  || Global_config->Flow_Control  ==USART_FLOW_CONTROL_RTS  )
		{
			//PB13 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_Mode = GPIO_Mode_Inp_Floating;
			PinCfg.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
		if (Global_config->Flow_Control  ==USART_FLOW_CONTROL_RTS || Global_config->Flow_Control  ==USART_FLOW_CONTROL_CTS  )
		{
			//PA14 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
			PinCfg.GPIO_Speed = GPIO_Speed_10MHz;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

		}
	}
}


void MCAL_UART_SendString(USART_TypeDef *USARTx, uint8_t *str)
{
    while(*str)
    {
        MCAL_UART_SendData(USARTx, (uint16_t*)str, Enable);
        str++;
    }
}




//ISR
void USART1_IRQHandler (void)
{

	Global_config->P_IRQ_Callback () ;

}

void USART2_IRQHandler (void)
{
	Global_config->P_IRQ_Callback () ;

}
void USART3_IRQHandler (void)
{
	Global_config->P_IRQ_Callback () ;


}
