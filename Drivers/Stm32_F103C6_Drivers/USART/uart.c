/*
 * uart.c
 *
 *  Created on: Apr 13, 2024
 *      Author: hassa
 */


/*
 * USART.c
 *
 *  Created on: Apr 13, 2024
 *      Author: hassa
 */




#include "uart.h"




//=====================================================
//		                 Generic Variables
//=====================================================


USART_Config* GP_UART_config = NULL;






//=====================================================
//		                  Generic Functions
//=====================================================








//=====================================================
//		                  APIs
//=====================================================






/*=======================================================================================================
 *
 * @Fn    			-MCAL_UART_Init
 * @brief			-Initializes USART (note:this only supports Asynchronous mode only)
 * @Param[in]		-USARTx: where x can be (1..3 depending on which USART will be used )
 * @Param[in]		-UART_Config: pointer to a  USART_Config_t structure that contains the
 * 					   the configuration info for the specified USART PIN.
 * @retval			-None
 * @Note			-Support Asynchronous Mode and HSI 8MHz Clock speed only
 *
 * */







void MCAL_UART_Init(USART_typedef* USARTx, USART_Config* UART_Config)
{

	uint32_t pclk, BRR;

	GP_UART_config = UART_Config;

	//Enable the Clock for selected USART
	if(USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if (USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if (USARTx == USART3)
		RCC_USART3_CLK_EN();


	//Enable USART Module
	//	Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13;

	//Enable USART Tx & Rx according
	//	Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_Config->USART_Mode;

	//Payload Width
	//	Bit 12 M: Word length
	USARTx->CR1 |= UART_Config->Payload_Length;

	//Parity Enable & Width
	//	Bit 10 PCE: Parity control enable & Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->Parity;

	//number of Stop Bits
	//	Bits 13:12 STOP: STOP bits
	USARTx->CR2 |= UART_Config->Stop_bits;

	//Flow Control (CTS/RTS)
	//	Bit 9 CTSE: CTS enable & Bit 8 RTSE: RTS enable
	USARTx->CR3 |= UART_Config->Flow_Control;

	//Baud Rate Speed;

	//Getting Crystal Speed
	if(USARTx == USART1){

		//PCLK2 for USART1
		pclk = MCAL_RCC_GETPCLK2Freq();

	}
	else
	{	//PCLK1 for USART2,3
		pclk = MCAL_RCC_GETPCLK1Freq();

	}
	//baud rate calculation
	BRR = USART_BRR_Register(pclk,UART_Config->Baud_Rate);

	//	Bits 3:0 DIV_Fraction[3:0]: fraction of USARTDIV Bits & 15:4 DIV_Mantissa[11:0]: mantissa of USARTDIV

	USARTx->BRR = BRR;

	//USART IRQ Enbale & IRQ Call back

	if(UART_Config->IRQ_Enable != USART_IRQ_Disable){

		USARTx->CR1 |= UART_Config->IRQ_Enable;


		//Enable NVIC For USARTx IRQ
		if(USARTx == USART1){

			NVIC_IRQ37_USART1_Enable;


		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_Enable;
		}
		else if(USARTx == USART3){
			NVIC_IRQ39_USART3_Enable;
		}



	}



}






/*=======================================================================================================
 *
 * @Fn    			-MCAL_UART_DeInit
 * @brief			-Reset USART(note:this only supports Asynchronous mode only).
 * @Param[in]		-USARTx: where x can be (1..3 depending on which USART will be used )
 * @retval			-None
 * @Note			-Reset the model by RCC register
 *
 * */





void MCAL_UART_DeInit(USART_typedef* USARTx)
{
	if( 	USARTx == USART1	)
	{
		RCC_USART1_CLK_DIS();
		NVIC_IRQ37_USART1_RESET;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_DIS();
		NVIC_IRQ38_USART2_RESET;

	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_DIS();
		NVIC_IRQ39_USART3_RESET;

	}


}






/*=======================================================================================================
 *
 * @Fn    			-MCAL_UART_SendData
 * @brief			-Send the buffer on UART
 * @Param[in]		-USARTx:where x can be (1..3 depending on which USART will be used )
 * @Param[in]		-pTxBuffer Buffer
 * @Param[in]		-PollingEnable: Enabling/Disabling pooling mechanism
 * @retval			-None
 * @Note			-You should initialize UART first
 *					//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
					//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
					//	because it is replaced by the parity.
					//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
					//	bit.
 * */


void MCAL_UART_SendData (USART_typedef* USARTx, uint16_t*pTxBuffer,enum Polling_mechanism PollingEnable)
{	//Wait until TXE flag is set in the SR	->SR: Status Register
	if(PollingEnable == Enable)
	{
		while(!	 (USARTx->SR & 1<<7 )	);

	}

	//Check the USART_wordlength item for 9Bit	or 8Bit in a frame


	if( GP_UART_config->Payload_Length == USART_9_DATA_Bits)
	{

		USARTx-> DR = (*pTxBuffer & (uint16_t)(0x01FF));



	}else
	{

		//This is 8bit data transfer
		USARTx-> DR = (*pTxBuffer & (uint8_t)(0x0FF));



	}






}



/*=======================================================================================================
 *
 * @Fn    			-MCAL_UART_ReceiveData
 * @brief			-Receive the buffer from UART
 * @Param[in]		-USARTx:where x can be (1..3 depending on which USART will be used )
 * @Param[in]		-pTxBuffer Buffer
 * @Param[in]		-PollingEnable: Enabling/Disabling pooling mechanism
 * @retval			-None
 * @Note			-You should initialize UART first
 *					//	When receiving with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
					//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
					//	because it is replaced by the parity.
					//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
					//	bit.
 * */


void MCAL_UART_ReceiveData(USART_typedef* USARTx, uint16_t*pRxBuffer,enum Polling_mechanism PollingEnable){

	//Wait until RXNE flag is set in the SR
	if(PollingEnable == Enable){

		while(!(USARTx->SR & 1<<5));

	}

	//9-bits payload length

	if(GP_UART_config->Payload_Length == USART_9_DATA_Bits)
	{
		if(GP_UART_config->Parity == USART_Parity_Type_None){

			//No parity so we consider all 9bits are data
			*((uint16_t*) pRxBuffer) = USARTx->DR;

		}
		else{

			//Parity is enabled and the payload will be considered as following(8-bits for data & 1-bit for parity)
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );


		}



	}else // 8-bit payload length
	{
		//No parity so we consider all 8-bits are data
		if(GP_UART_config->Parity == USART_Parity_Type_None)
		{

			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF );

		}
		else//Parity is enabled and the payload will be considered as following(7-bits for data & 1-bit for parity)
		{

			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);

		}


	}



}








/*=======================================================================================================
 *
 * @Fn    			-MCAL_UART_GPIO_Set_Pins
 * @brief			-
 * @Param[in]		-USARTx:where x can be (1..3 depending on which USART will be used )
 * @retval			-None
 * @Note			-
 *					-Look @ GPIO configurations for device peripherals
 * */


void MCAL_UART_GPIO_Set_Pins(USART_typedef* USARTx){


	GPIO_PinConfig_t USART_PinCfg;
	if(USARTx == USART1)
	{
		//TX->PA9
		//RX->PA10
		//CTS->PA11
		//RTS->PA12

		//TX->PA9
		USART_PinCfg.GPIO_PinNumber = GPIO_PINS_9;
		USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Output_PP;
		USART_PinCfg.GPIO_Mode_config = GPIO_MODE_Output_10MHz;
		MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);


		//RX->PA9
		USART_PinCfg.GPIO_PinNumber = GPIO_PINS_10;
		USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Input;
		MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);



		//CTS->PA11
		if(GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS || GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS_RTS){
			USART_PinCfg.GPIO_PinNumber = GPIO_PINS_11;
			USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Input;
			MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);
		}


		//RTS->PA12
		if(GP_UART_config->Flow_Control == USART_FLOW_CONTROL_RTS || GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS_RTS){
			USART_PinCfg.GPIO_PinNumber = GPIO_PINS_12;
			USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Output_PP;
			USART_PinCfg.GPIO_Mode_config = GPIO_MODE_Output_10MHz;
			MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);
		}


	}
	else if(USARTx == USART2){


		//TX->PA2
		//RX->PA3
		//CTS->PA0
		//RTS->PA1

		//TX->PA2
		USART_PinCfg.GPIO_PinNumber = GPIO_PINS_2;
		USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Output_PP;
		USART_PinCfg.GPIO_Mode_config = GPIO_MODE_Output_10MHz;
		MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);


		//RX->PA3
		USART_PinCfg.GPIO_PinNumber = GPIO_PINS_3;
		USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Input;
		MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);



		//CTS->PA0
		if(GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS || GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS_RTS){
			USART_PinCfg.GPIO_PinNumber = GPIO_PINS_0;
			USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Input;
			MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);
		}


		//RTS->PA1
		if(GP_UART_config->Flow_Control == USART_FLOW_CONTROL_RTS || GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS_RTS){
			USART_PinCfg.GPIO_PinNumber = GPIO_PINS_1;
			USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Output_PP;
			USART_PinCfg.GPIO_Mode_config = GPIO_MODE_Output_10MHz;
			MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);
		}













	}
	else if (USARTx == USART3){


		//TX->PB10
		//RX->PB11
		//CTS->PB13
		//RTS->PB14

		//TX->PB10
		USART_PinCfg.GPIO_PinNumber = GPIO_PINS_10;
		USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Output_PP;
		USART_PinCfg.GPIO_Mode_config = GPIO_MODE_Output_10MHz;
		MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);


		//RX->PB11
		USART_PinCfg.GPIO_PinNumber = GPIO_PINS_11;
		USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Input;
		MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);



		//CTS->PB13
		if(GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS || GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS_RTS){
			USART_PinCfg.GPIO_PinNumber = GPIO_PINS_13;
			USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Input;
			MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);
		}


		//RTS->PB14
		if(GP_UART_config->Flow_Control == USART_FLOW_CONTROL_RTS || GP_UART_config->Flow_Control == USART_FLOW_CONTROL_CTS_RTS){
			USART_PinCfg.GPIO_PinNumber = GPIO_PINS_14;
			USART_PinCfg.GPIO_Pin_Config = GPIO_CONFIG_Alternate_Output_PP;
			USART_PinCfg.GPIO_Mode_config = GPIO_MODE_Output_10MHz;
			MCAL_GPIO_INIT(GPIOA, &USART_PinCfg);
		}








	}






}


/*=======================================================================================================
 *
 * @Fn    			-MCAL_UART_Wait_TC
 * @brief			-
 * @Param[in]		-
 * @retval			-None
 * @Note			-
 *
 * */



void MCAL_UART_Wait_TC(USART_typedef* USARTx)
{
	//Wait till TC flag is set in the SR
	while(! (USARTx->SR & 1<<6) );


}




//ISR FOR USARTx where x can be (1..3 depending on which USART will be used )


void USART1_IRQHandler(void){

	GP_UART_config->P_IRQ_Callback();

}       			//USART1 global interrupt


void USART2_IRQHandler(void){
	GP_UART_config->P_IRQ_Callback();

}       			// USART2 global interrupt



void USART3_IRQHandler(void){
	GP_UART_config->P_IRQ_Callback();
}         			// USART3 global interrupt
