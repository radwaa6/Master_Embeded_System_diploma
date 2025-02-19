/*
 * stm32f103x6_spi_driver.c
 *
 *  Created on: Nov 19, 2024
 *      Author: Mohamed Abd El Hakeem El Said Ali
 */




#include "stm32f103x6_spi_driver.h"

SPI_Config_t *G_SPI_Config[2] = {NULL, NULL};


void MCAL_SPI_Init(SPI_TypeDef *SPIx, SPI_Config_t* SPI_Config)
{
	//Safety for register, Using this technique for protect the peripheral form working before the full configurations
	//uint16_t tempCR1_reg = 0 ;
	//uint16_t tempCR2_reg = 0 ;

	if (SPIx == SPI1) {
		G_SPI_Config[0] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else if (SPIx == SPI2) {
		G_SPI_Config[1] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}

	//Set Master or Slave
	SPIx->CR1 |= SPI_Config->SPI_Mode ;

	//Set Communication Mode
	SPIx->CR1 |= SPI_Config->Communication_Mode ;

	//Set Data size
	SPIx->CR1 |= SPI_Config->Data_Size ;

	//Set Data format
	SPIx->CR1 |= SPI_Config->Data_Order ;

	//Set Clock Polarity
	SPIx->CR1 |= SPI_Config->CLKPolarity ;

	//Set Clock Phase
	SPIx->CR1 |= SPI_Config->CLKPhase ;

	//Set Slave Select Management NSS
	if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable) {
		SPIx->CR2 |= SPI_Config->NSS ;
	}
	else if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_disable) {
		SPIx->CR2 &= SPI_Config->NSS ;
	}
	else {
		SPIx->CR1 |= SPI_Config->NSS ;
	}

	//Set BoudRate Pre-scaler
	SPIx->CR1 |= SPI_Config->BaudRate_Prescaler ;

	if (SPI_Config->IRQ_Enable != SPI_IRQ_Disable) {

		SPIx->CR2 |= SPI_Config->IRQ_Enable ;

		if (SPIx == SPI1) {
			NVIC_IRQ35_SPI1_Enable();
		}
		else if (SPIx == SPI2) {
			NVIC_IRQ36_SPI2_Enable();
		}
	}


	// SPE enable
	SPIx->CR1 |= (uint16_t)(1 << 6) ;

	//SPIx->CR1 = tempCR1_reg ;
	//SPIx->CR2 = tempCR2_reg ;
}




void MCAL_SPI_DeInit (SPI_TypeDef* SPIx)
{
	if (SPIx == SPI1) {
		RCC_SPI1_RESET() ;
		NVIC_IRQ35_SPI1_Disable() ;
	}
	else if (SPIx == SPI2) {
		RCC_SPI2_RESET() ;
		NVIC_IRQ36_SPI2_Disable() ;
	}
}


void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx)
{
	GPIO_PinConfig_t SPI_GPIO_Config ;
	AFIO_CLOCK_ENABLE;
	if (SPIx == SPI1)
	{
		/*
			SPI1_NSS 	PA4
			SPI1_SCK 	PA5
			SPI1_MISO 	PA6
			SPI1_MOSI	PA7
		 */
		GPIOA_CLOCK_ENABLE;

		if (G_SPI_Config[0]->SPI_Mode == SPI_MASTER_MODE) {
			// MASTER
			/*
			SPI1_NSS 	PA4		Hardware master /slave >> Input floating/ Input pull-up / Input pull-down
								Hardware master/ NSS output enabled >> Alternate function push-pull
								Software >> Not used. Can be used as a GPIO
			SPI1_SCK 	PA5		Alternate function push-pull
			SPI1_MISO 	PA6		Input floating / Input pull-up
			SPI1_MOSI	PA7		Alternate function push-pull
			 */

			// SPI1_NSS
			switch (G_SPI_Config[0]->NSS) {
			case SPI_NSS_Hard_Master_SS_output_disable :
				SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_4;
				SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
				SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);
				break ;

			case SPI_NSS_Hard_Master_SS_output_enable :
				SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_4;
				SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
				SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_10MHz;
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);
				break ;
			}

			// SPI1_SCK
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_5;
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_10MHz;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			/* PA6 : SPI1_MISO */
			/* Full duplex / master Input floating / Input pull-up */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_6;
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			/* PA7 : SPI1_MOSI */
			/* Full duplex / master Alternate function push-pull */
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_7;
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_10MHz;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);
		}
		else {
			// SLAVE
			/*
			SPI1_NSS 	PA4		Hardware master /slave >> Input floating/ Input pull-up / Input pull-down
								Hardware master/ NSS output enabled >> Alternate function push-pull
								Software >> Not used. Can be used as a GPIO
			SPI1_SCK 	PA5		Input floating
			SPI1_MISO 	PA6		Alternate function push-pull
			SPI1_MOSI	PA7		Input floating / Input pull-up
			 */

			// SPI1_NSS
			if (G_SPI_Config[0]->NSS == SPI_NSS_Hard_Slave) {
				/* Hardware Master/Slave Input Floating */
				SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_4;
				SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
				SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
				MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);
			}

			// SPI1_SCK
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_5;
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);


			// SPI1_MISO
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_6;
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Out_AF_push_pull;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_10MHz;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);

			// SPI1_MOSI
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_7;
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOA, &SPI_GPIO_Config);
		}

	}
	else if (SPIx == SPI2)
	{
		/*
			SPI2_NSS 	PB12
			SPI2_SCK 	PB13
			SPI2_MISO 	PB14
			SPI2_MOSI	PB15
		 */
		GPIOB_CLOCK_ENABLE;

		if (G_SPI_Config[1]->SPI_Mode == SPI_MASTER_MODE) {
			// MASTER
			// SPI2_NSS
			switch (G_SPI_Config[1]->NSS) {
			case SPI_NSS_Hard_Master_SS_output_disable :
				SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
				SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_12 ;
				SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
				MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);
				break ;

			case SPI_NSS_Hard_Master_SS_output_enable :
				SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Out_AF_push_pull ;
				SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_12 ;
				SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_10MHz ;
				MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);
				break ;
			}

			// SPI2_SCK
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Out_AF_push_pull ;
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_13 ;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_10MHz ;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			// SPI2_MISO
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_14 ;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			// SPI2_MOSI
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Out_AF_push_pull ;
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_15 ;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_10MHz ;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);
		}
		else {
			// SLAVE

			// SPI2_NSS
			if (G_SPI_Config[1]->NSS == SPI_NSS_Hard_Slave) {
				SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
				SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_12 ;
				SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
				MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);
			}

			// SPI2_SCK
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_13 ;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			// SPI2_MISO
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Out_AF_push_pull ;
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_14 ;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_10MHz ;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);

			// SPI2_MOSI
			SPI_GPIO_Config.GPIO_Mode = GPIO_Mode_Inp_Floating;
			SPI_GPIO_Config.GPIO_PinNumber = GPIO_PIN_15 ;
			SPI_GPIO_Config.GPIO_Speed = GPIO_Speed_Reset_State;
			MCAL_GPIO_Init(GPIOB, &SPI_GPIO_Config);
		}

	}
}


void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *data_buffer,Polling_MECH Polling)
{
	if (Polling == SPIenable) {
		/*
		 *  TXE: Transmit buffer empty
			0: Tx buffer not empty
			1: Tx buffer empty
		 */
		while (!(SPIx->SR & (uint16_t)(1 << 1))) ;
	}
	SPIx->DR = *data_buffer ;
}

void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *data_buffer ,Polling_MECH Polling)
{
	if (Polling == SPIenable) {
		/*
		 *  RXNE: Receive buffer not empty
			0: Rx buffer empty
			1: Rx buffer not empty
		 */
		while (!(SPIx->SR & (uint16_t)(1 << 0))) ;
	}
	*data_buffer = SPIx->DR ;
}


void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t *data_buffer,Polling_MECH Polling)
{
	if (Polling == SPIenable) {
		/*
		 *  TXE: Transmit buffer empty
				0: Tx buffer not empty
				1: Tx buffer empty
		 */
		while (!(SPIx->SR & (uint16_t)(1 << 1))) ;
	}
	SPIx->DR = *data_buffer ;

	if (Polling == SPIenable) {
		/*
		 *  RXNE: Receive buffer not empty
					0: Rx buffer empty
					1: Rx buffer not empty
		 */
		while (!(SPIx->SR & (uint16_t)(1 << 0))) ;
	}
	*data_buffer = SPIx->DR ;
}





//---ISR-------

void SPI1_IRQHandler (void) {
	IRQ_SOURCE irq_src ;
	irq_src.TXE = ( (SPI1->SR & (1 << 1)) >> 1 ) ;
	irq_src.RXNE = ( (SPI1->SR & (1 << 0)) >> 0 ) ;
	irq_src.ERRI = ( (SPI1->SR & (1 << 4)) >> 4 ) ;
	G_SPI_Config[0]->IRQ_CallBack(irq_src) ;
}

void SPI2_IRQHandler (void) {
	IRQ_SOURCE irq_src ;
	irq_src.TXE = ( (SPI2->SR & (1 << 1)) >> 1 ) ;
	irq_src.RXNE = ( (SPI2->SR & (1 << 0)) >> 0 ) ;
	irq_src.ERRI = ( (SPI2->SR & (1 << 4)) >> 4 ) ;
	G_SPI_Config[1]->IRQ_CallBack(irq_src) ;

}
