/*
 * stm32f103x8_i2c_driver.c
 *
 *  Created on: Dec 4, 2024
 *  Mohamed Abd El Hakeem El Said Ali
 */




#include "stm32f103x8_i2c_driver.h"




//-----------------------------------------------------------------
//*****************************************************************
//-----------------------------------------------------------------

//========================================================
//						Generic Variables
//========================================================


I2C_Config_t GL_I2C_Config[2] = {NULL,NULL};




/*================================================================
 * @Fn			-MCAL_I2C_Init
 * @brief		-Initializes the I2Cx  according to the specified parameters of I2C_Config
 * @param [in] 	-I2Cx : where x can be (1,2 depending on device used) to select which I2C Instant
 * @param [in]	-I2C_Config : Pointer to SPI_Config_t which contains the configuration info for specified I2C
 * @retval 		-None
 * Note 		-None
 */
void MCAL_I2C_Init(I2C_TypeDef* I2Cx , I2C_Config_t* I2C_Config)
{
	uint16_t temp_REG = 0;
	uint32_t temp_Freq;
	uint32_t Result = 0;
	uint32_t Pclk1 = 8000000;
	//Enable RCC Clock
	if(I2Cx == I2C1)
	{
		GL_I2C_Config[0] = *I2C_Config;
		RCC_I2C1_CLK_EN();
	}
	else if (I2Cx == I2C2)
	{
		GL_I2C_Config[1] = *I2C_Config;
		RCC_I2C2_CLK_EN();
	}

	if(I2C_Config->I2C_Mode == I2C_Mode_I2C)
	{
		//Init Timing
		//Get CR2 Vales in temp reg;
		temp_REG = I2Cx->CR2;
		//Clear Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		temp_REG &= ~(I2C_CR2_FREQ);
		//Get Pclk1 Frequency
		Pclk1 = MCAL_RCC_GetPCLK1Freq();

		temp_Freq = (uint16_t) (Pclk1 / 1000000) ;
		temp_REG |= temp_Freq;
		I2Cx->CR2 = temp_REG;
		temp_REG = 0;

		I2Cx->CR1 &= ~(I2C_CR1_PE);

		if(I2C_Config->I2C_ClockSpeed == I2C_SCLK_SM_50KHz || I2C_Config->I2C_ClockSpeed == I2C_SCLK_SM_100KHz)
		{
			Result = (uint16_t)(Pclk1 / ( I2C_Config->I2C_ClockSpeed>>1 )); //I2C_ClockSpeed * 2
			temp_REG |= Result;
			I2Cx->CCR = temp_REG;

			I2Cx->TRISE = temp_Freq +1;
		}

		else
		{
			//Fast Mode to be done
		}

		//I2C CR1 Config
		temp_REG = I2Cx->CR1 ;

		temp_REG |= (I2C_Config->ACK_Control | I2C_Config->General_Call | I2C_Config->I2C_Mode | I2C_Config->Stretch_Mode );

		I2Cx->CR1 = temp_REG;
		temp_REG = 0;

		//I2C OAR1 & OAR2 Config
		if(I2C_Config ->I2C_Slave_Address_Mode.Enable_DUAL_Address == 1)
		{
			temp_REG = I2C_OAR2_ENDUAL;

			//			Bits 7:1 ADD2[7:1]: Interface address
			//			bits 7:1 of address in dual addressing mode
			temp_REG = I2C_Config->I2C_Slave_Address_Mode.Secondary_Slave_Address << I2C_OAR2_ADD2_Pos ;
			I2Cx->OAR2 = temp_REG;
		}
		temp_REG = 0;

		//		Bits 7:1 ADD[7:1]: Interface address
		//		bits 7:1 of address
		temp_REG |= I2C_Config->I2C_Slave_Address_Mode.Primary_Slave_Address<<1;
		temp_REG |= I2C_Config->I2C_Slave_Address_Mode.I2C_Addressing_Slave_Mode;

		I2Cx->OAR1 = temp_REG;



	}
	else
	{
		//SMBUS To be Supported later
	}

	//If slave mode it must work in interrupt not polling
	//Check if Callback pointer != NULL
	if (I2C_Config->Ptr_Slave_EV_IRQ_CallBack != NULL)
	{
		//Enable IRQ
		I2Cx->CR2 |= I2C_CR2_ITERREN;
		I2Cx->CR2 |= I2C_CR2_ITEVTEN;
		I2Cx->CR2 |= I2C_CR2_ITBUFEN;
		if (I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable();
			NVIC_IRQ32_I2C1_ER_Enable();
		}
		else if (I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable();
			NVIC_IRQ34_I2C2_ER_Enable();
		}
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}

	//Enable I2C Peripheral
	I2Cx->CR1 |= I2C_CR1_PE;

}





/*================================================================
 * @Fn			-MCAL_I2C_Reset
 * @brief		-Resets the I2Cx  according to the specified parameters of I2C_Config
 * @param [in] 	-I2Cx : where x can be (1,2 depending on device used) to select which I2C Instant
 * @retval 		-None
 * Note 		-None
 */
void MCAL_I2C_Reset(I2C_TypeDef* I2Cx )
{
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable();
		NVIC_IRQ32_I2C1_ER_Disable();
		RCC_I2C1_CLK_RESET();
	}
	else if (I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_Disable();
		NVIC_IRQ34_I2C2_ER_Disable();
		RCC_I2C2_CLK_RESET();
	}
}
/**================================================================
 * @Fn			-MCAL_I2C_GPIO_Set_Pins
 * @brief		-Configure GPIO Pins to work as I2C
 * @param [in] 	-I2Cx : where x can be (1,2 depending on device used) to select which I2C Instant
 * @retval 		-None
 * Note 		-None
 */
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx)
{
	GPIOB_CLOCK_ENABLE;
	AFIO_CLOCK_ENABLE;
	GPIO_PinConfig_t I2C_PinConfig;

	if(I2Cx == I2C1)
	{
		//I2C1
		//PB6 SCL
		//PB7 SDA
		I2C_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
		I2C_PinConfig.GPIO_Mode = GPIO_Mode_Out_AF_Open_drain;
		I2C_PinConfig.GPIO_Speed = GPIO_Speed_10MHz;
		MCAL_GPIO_Init(GPIOB, &I2C_PinConfig);

		I2C_PinConfig.GPIO_PinNumber = GPIO_PIN_7;
		I2C_PinConfig.GPIO_Mode = GPIO_Mode_Out_AF_Open_drain;
		I2C_PinConfig.GPIO_Speed = GPIO_Speed_10MHz;
		MCAL_GPIO_Init(GPIOB, &I2C_PinConfig);
	}
	else if (I2Cx == I2C2)
	{
		//I2C2
		//PB10 SCL
		//PB11 SDA
		I2C_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
		I2C_PinConfig.GPIO_Mode = GPIO_Mode_Out_AF_Open_drain;
		I2C_PinConfig.GPIO_Speed = GPIO_Speed_10MHz;
		MCAL_GPIO_Init(GPIOB, &I2C_PinConfig);

		I2C_PinConfig.GPIO_PinNumber = GPIO_PIN_11;
		I2C_PinConfig.GPIO_Mode = GPIO_Mode_Out_AF_Open_drain;
		I2C_PinConfig.GPIO_Speed = GPIO_Speed_10MHz;
		MCAL_GPIO_Init(GPIOB, &I2C_PinConfig);

	}


}



/**================================================================
 * @Fn			-MCAL_I2C_MASTER_TX
 * @brief		-Master Sending Data Send data
 * @param [in] 	-I2Cx : where x can be (1,2 depending on device used) to select which I2C Instant
 * @param [in] 	-device_Address : Address of slave to receive the sent data
 * @param [in] 	-Data : Buffer containing the data to be sent
 * @param [in] 	-Data_Length : Length of data to be sent
 * @param [in] 	-Stop : Contain stop condition or not
 * @param [in] 	-Start : Contain Repeated start condition or not
 * @retval 		-None
 * Note 		-todo Adding Timeout Implementation as an argument
				 Timer_Interrupt(){flag=1}
				 while condition (Flag && Time);
 */

void MCAL_I2C_MASTER_TX (I2C_TypeDef* I2Cx ,uint16_t device_Address,uint8_t* Data ,  uint32_t Data_Length , E_STOP_CONDITION Stop ,E_Repeated_Start Start )
{
	volatile uint32_t i;
	//Transit Sequence :
	//1-Send Start Bit:
	I2C_GenerateSTART(I2Cx, i2c_enable, Start);

	//2-Check EV5
	//EV5: SB=1, cleared by reading SR1 register
	while(!I2C_Get_Status(I2Cx, EV5));

	//3-Writing DR register with Address
	I2C_SendAddress(I2Cx, device_Address, Transmitter);

	//4-Check EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_Get_Status(I2Cx, EV6));

	//5- Check TRA , BUSY, MSL , TXE Flags
	while(!I2C_Get_Status(I2Cx, MASTER_BYTE_TRANSMITTER));

	//6-Write Data
	for (i= 0;i<Data_Length;i++)
	{
		I2Cx->DR = Data[i];
		//7-Wait EV8
		//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while(!I2C_Get_Status(I2Cx, EV8));

	}

	//8-Send Stop Condition
	if(Stop == withSTOP)
	{
		I2C_GenerateSTOP(I2Cx,i2c_enable);
	}



}

/**================================================================
 * @Fn			-MCAL_I2C_MASTER_RX
 * @brief		-Master Receiving Data
 * @param [in] 	-I2Cx : where x can be (1,2 depending on device used) to select which I2C Instant
 * @param [in] 	-device_Address : Address of slave to receive the sent data
 * @param [in] 	-Data : Buffer containing the data to be Received
 * @param [in] 	-Data_Length : Length of data to be Received
 * @param [in] 	-Stop : Contain stop condition or not
 * @param [in] 	-Start : Contain Repeated start condition or not
 * @retval 		-None
 * Note 		-None
 */

void MCAL_I2C_MASTER_RX (I2C_TypeDef* I2Cx ,uint16_t device_Address,uint8_t* Data ,  uint32_t Data_Length , E_STOP_CONDITION Stop ,E_Repeated_Start Start )
{
	volatile uint32_t i;
	//Receive Sequence :
	//1-Send Start Bit:
	I2C_GenerateSTART(I2Cx, i2c_enable, Start);

	//2-Check EV5
	//EV5: SB=1, cleared by reading SR1 register
	while(!I2C_Get_Status(I2Cx, EV5));

	//3-Writing DR register with Address
	I2C_SendAddress(I2Cx, device_Address, Reciever);

	//4-Check EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_Get_Status(I2Cx, EV6));

	I2C_AckConfig(I2Cx,i2c_enable);

	if(Data_Length)
	{
		//Read data until data length Becomes zero
		for (i= Data_Length; i>1 ;i--)
		{
			//5-Wait EV7
			//EV7: RxNE=1 Cleared by Reading DR Register
			while(!I2C_Get_Status(I2Cx, EV7));
			//Read data
			*Data = I2Cx->DR;
			Data++;
		}
		I2C_AckConfig(I2Cx,i2c_disable);

	}

	//6-Send Stop Condition
	if(Stop == withSTOP)
	{
		I2C_GenerateSTOP(I2Cx,i2c_enable);
	}

	//Re-enable Ack
	if(I2Cx==I2C1)
	{
		if(GL_I2C_Config[0].ACK_Control== I2C_ACK_Enable)
		{
			I2C_AckConfig(I2Cx,i2c_enable);
		}
	}
	else if (I2Cx==I2C2)
	{
		if(GL_I2C_Config[1].ACK_Control== I2C_ACK_Enable)
		{
			I2C_AckConfig(I2Cx,i2c_enable);
		}
	}


}


/**================================================================
 * @Fn			-MCAL_I2C_SLAVE_TX
 * @brief		-Slave Sending Data
 * @param [in] 	-I2Cx : where x can be (1,2 depending on device used) to select which I2C Instant
 * @param [in] 	-Data : Buffer containing the data to be Sent
 * @retval 		-None
 * Note 		-None
 */
void MCAL_I2C_SLAVE_TX (I2C_TypeDef* I2Cx, uint8_t Data)
{
	I2Cx->DR = Data;
}
/**================================================================
 * @Fn			-MCAL_I2C_SLAVE_RX
 * @brief		-Slave Receiving Data
 * @param [in] 	-I2Cx : where x can be (1,2 depending on device used) to select which I2C Instant
 * @retval 		-Data received
 * Note 		-None
 */
uint8_t MCAL_I2C_SLAVE_RX (I2C_TypeDef* I2Cx)
{
	return (uint8_t) I2Cx->DR ;
}








void I2C1_EV_IRQHandler(void)
{

}
void I2C1_ER_IRQHandler (void)
{

}



void I2C2_EV_IRQHandler(void)
{

}
void I2C2_ER_IRQHandler(void)
{

}












void I2C_GenerateSTART(I2C_TypeDef* I2Cx,E_Functional_State State ,E_Repeated_Start Start )
{
	//Check Repeated or regular start
	if (Start == No_Repeated_Start)
	{
		//Check if Bus is idle i.e. check if it's taken by any other master
		while(I2C_Get_Status(I2Cx, I2C_FLAG_BUSY));

	}
	//If its a repeated start , bus already taken by this master
	if(State != i2c_disable)
	{
		//Gen Start Condition
		//		Bit 8 START: Start generation
		//		This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
		//		In Master Mode:
		//		0: No Start generation
		//		1: Repeated start generation
		//		In Slave mode:
		//		0: No Start generation
		//		1: Start generation when the bus is free
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else
	{
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}



}
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx,E_Functional_State State)
{
	//	Bit 9 STOP: Stop generation
	//	The bit is set and cleared by software, cleared by hardware when a Stop condition is
	//	detected, set by hardware when a timeout error is detected.
	//	In Master Mode:
	//	0: No Stop generation.
	//	1: Stop generation after the current byte transfer or after the current Start condition is sent.
	//	In Slave mode:
	//	0: No Stop generation.
	//	1: Release the SCL and SDA lines after the current byte transfer.
	if(State != i2c_disable)
	{
		I2Cx->CR1 |= I2C_CR1_STOP;
	}
	else
	{
		I2Cx->CR1 &= ~(I2C_CR1_STOP);

	}

}

E_I2C_Flag_Status I2C_Get_Status ( I2C_TypeDef* I2Cx , E_Status flag)
{
	uint32_t flag1 = 0 ,flag2=0,lastevent = 0;
	E_I2C_Flag_Status Value = RESET;
	switch(flag)
	{
	case I2C_FLAG_BUSY:
	{
		//		Bit 1 BUSY: Bus busy
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		//		It indicates a communication in progress on the bus. This information is still updated when
		//		the interface is disabled (PE=0).
		if((I2Cx->SR2) & (I2C_SR2_BUSY))
		{
			Value = SET;
		}
		else
		{
			Value = RESET;
		}
		break;
	}
	case EV5:
	{
		//		Bit 0 SB: Start bit (Master mode)
		//		0: No Start condition
		//		1: Start condition generated.
		//		– Set when a Start condition generated.
		//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//		hardware when PE=0
		if((I2Cx->SR1) & (I2C_SR1_SB))
		{
			Value = SET;
		}
		else
		{
			Value = RESET;
		}
		break;
	}
	case EV6 :
	{
		//		Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		if((I2Cx->SR1) & (I2C_SR1_ADDR))
		{
			Value = SET;
		}
		else
		{
			Value = RESET;
		}
		//Temp = I2Cx->SR2;
		break;
	}

	case MASTER_BYTE_TRANSMITTER :
	{
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2<<16;
		//Get last event value from I2C Status Reg
		lastevent = (flag1 | flag2) & ((uint32_t) 0x00FFFFFF);
		if((lastevent & flag) == flag)
		{
			Value = SET;
		}
		else
		{
			Value = RESET;
		}
		break;
	}
	case EV8:
	{
		//		Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		//		– Set when DR is empty in transmission. TxE is not set during address phase.
		//		– Cleared by software writing to the DR register or by hardware after a start or a stop condition
		//		or when PE=0.
		//		TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
		//		Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
		//		BTF is set, as in both cases the data register is still empty.
		if((I2Cx->SR1) & (I2C_SR1_TXE))
		{
			Value = SET;
		}
		else
		{
			Value = RESET;
		}
		break;
	}
	case EV8_2:
	{

		//		Bit 2 BTF: Byte transfer finished
		//		0: Data byte transfer not done
		//		1: Data byte transfer succeeded
		//		– Set by hardware when NOSTRETCH=0 and:
		//		– In reception when a new byte is received (including ACK pulse) and DR has not been read
		//		yet (RxNE=1).
		//		– In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
		//		– Cleared by software reading SR1 followed by either a read or write in the DR register or by
		//		hardware after a start or a stop condition in transmission or when PE=0.
		//		Note: The BTF bit is not set after a NACK reception
		//		The BTF bit is not set if next byte to be transmitted is the PEC (TRA=1 in I2C_SR2
		//		register and PEC=1 in I2C_CR1 register)
		if((I2Cx->SR1) & (I2C_SR1_BTF))
		{
			Value = SET;
		}
		else
		{
			Value = RESET;
		}
		break;
	}
	case EV7:
	{

		//		Bit 6 RxNE: Data register not empty (receivers)
		//		0: Data register empty
		//		1: Data register not empty
		//		– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//		– Cleared by software reading or writing the DR register or by hardware when PE=0.
		//		RxNE is not set in case of ARLO event.
		//		Note: RxNE is not cleared by reading data when BTF is set, as the data register is still full.
		if((I2Cx->SR1) & (I2C_SR1_RXNE))
		{
			Value = SET;
		}
		else
		{
			Value = RESET;
		}
		break;
	}

	}



	return Value;
}




void I2C_SendAddress (I2C_TypeDef* I2Cx , uint16_t Address, E_Direction I2C_Direction)
{
	//Todo Support 10 Bit Addressing
	Address = (Address<<1);
	if (I2C_Direction == Reciever)
	{
		//Address bit 0 = 1 for Read
		Address |= (1<<0);
	}
	else
	{
		//Address bit 0 = 0 for Write
		Address &= ~(1<<0);
	}

	I2Cx->DR = Address;

}

void I2C_AckConfig (I2C_TypeDef* I2Cx, E_Functional_State State)
{
	//	Bit 10 ACK: Acknowledge enable
	//	This bit is set and cleared by software and cleared by hardware when PE=0.
	//	0: No acknowledge returned
	//	1: Acknowledge returned after a byte is received (matched address or data)

	if(State == i2c_enable)
	{
		I2Cx->CR1 |= (I2C_CR1_ACK);
	}
	else
	{
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}
}
