/*
 * stm32f103x8_i2c_driver.h
 *
 *  Created on: Dec 4, 2024
 * Mohamed Abd El Hakeem El Said Ali
 */

#ifndef INC_STM32F103X8_I2C_DRIVER_H_
#define INC_STM32F103X8_I2C_DRIVER_H_



//========================================================
//						INCLUDES
//========================================================

#include "stm32f103x6.h"
#include "stm32_F103C6_gpio_driver.h"
#include "RCC.h"


//-----------------------------------------------------------------
//*****************************************************************
//-----------------------------------------------------------------

typedef struct
{
	uint16_t Enable_DUAL_Address; 		//1 = Enable , 0 = Disable
	uint16_t Primary_Slave_Address;
	uint16_t Secondary_Slave_Address;
	uint32_t I2C_Addressing_Slave_Mode;	//Specifies the Addressing Mode of I2C Slave
										//This Parameter must be set with value
										//from Macro Configuration Manual @ref I2C_Addressing_Slave_Mode_Define

}S_I2C_Slave_Device_Address;

typedef enum
{
	I2C_EV_STOP,
	I2C_ER_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,		//Application Layer Should send data in this state (MCAL_I2C_SlaveSendData)
	I2C_EV_DATA_RCV			//Application Layer Should read data in this state (MCAL_I2C_SlaveReadData)

}E_Slave_State;


typedef enum
{
	withSTOP,
	withoutSTOP
}E_STOP_CONDITION;


typedef enum
{
	Repeated_Start,
	No_Repeated_Start
}E_Repeated_Start;

typedef enum
{
	i2c_enable,
	i2c_disable
}E_Functional_State;

typedef enum
{
	RESET,
	SET
}E_I2C_Flag_Status;




#define I2C_EV_MASTER_BYTE_TRANSMITTER 						((uint32_t)0x00070080) //TRA, BUSY, MSL , TXE FLAGS
typedef enum
{
	I2C_FLAG_BUSY,
	EV5, 	//EV5: SB=1, cleared by reading SR1 register
	EV6, 	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV8,	//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_2,	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	EV7,	//EV7: RxNE=1 Cleared by Reading DR Register
	MASTER_BYTE_TRANSMITTER = ((uint32_t)0x00070080),




}E_Status;




typedef enum
{
	Transmitter,
	Reciever
}E_Direction;



//========================================================
//				Configuration Structure
//========================================================

typedef struct
{
	uint32_t I2C_ClockSpeed ;	//Specifies I2C Operation Clock Speed
								//This Parameter must be set with value
								//from Macro Configuration Manual @ref I2C_ClockSpeed_Define

	uint32_t I2C_Mode ;			//Specifies the I2C  Mode
								//This Parameter must be set with value
								//from Macro Configuration Manual @ref I2C_Mode_Define

	uint32_t Stretch_Mode ;  	//Specifies Mode of I2C Clock Stretching (Enabled / Disabled)
								//This Parameter must be set with value
								//from Macro Configuration Manual @ref Stretch_Mode_Define

	uint32_t ACK_Control;		//Specifies Mode of I2C Ack respond (Enabled / Disabled)
								//This Parameter must be set with value
								//from Macro Configuration Manual @ref ACK_Control_Define

	uint32_t General_Call;		//Specifies Mode of General Call Address Detection (Enabled / Disabled)
								//This Parameter must be set with value
								//from Macro Configuration Manual @ref General_Call_Define


	S_I2C_Slave_Device_Address I2C_Slave_Address_Mode;

	void (* Ptr_Slave_EV_IRQ_CallBack)(E_Slave_State state); //Set C function to be called once IRQ Happens


}I2C_Config_t;




//-----------------------------------------------------------------
//*****************************************************************
//-----------------------------------------------------------------

//========================================================
//			Macros Configuration References
//========================================================

//@ref I2C_ClockSpeed_Define

//Standard Mode up to 100Khz
//Fast Mode up to 400Khz

//To config clk before Enabling the peripheral:
//1- FREQ[5:0]: Peripheral clock frequency
//2- Config the clock control Registers
//		T.high = CCR * T.Clk1
//3- Config the Rise Time Register
//TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
//= FREQ +1

#define I2C_SCLK_SM_50KHz							(50000)
#define I2C_SCLK_SM_100KHz							(100000)

#define I2C_SCLK_FM_200KHz							(200000) 	//To be supported
#define I2C_SCLK_FM_400KHz							(400000)	//To be supported


//-------------------------------------------------------------
//@ref I2C_Mode_Define

//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode

#define I2C_Mode_I2C								(0x0)
#define I2C_Mode_SMBus								I2C_CR1_SMBUS


//-------------------------------------------------------------

//@ref Stretch_Mode_Define
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, until
//it is reset by software.
//0: Clock stretching enabled
//1: Clock stretching disabled

#define I2C_Stretch_Mode_Enable						(0x0)
#define I2C_Stretch_Mode_Disable					I2C_CR1_NOSTRETCH

//-------------------------------------------------------------
//@ref I2C_Addressing_Slave_Mode_Define
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Slave_7Bit_Address						(0x0)
#define I2C_Slave_10Bit_Address						I2C_OAR1_ADDMODE


//-------------------------------------------------------------
//@ref ACK_Control_Define
//Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or dat

#define I2C_ACK_Disable								(0x0)
#define I2C_ACK_Enable								I2C_CR1_ACK


//-------------------------------------------------------------
//@ref General_Call_Define
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.
#define I2C_General_Call_Enabled					I2C_CR1_ENGC
#define I2C_General_Call_Disabled					(0x0)



//-----------------------------------------------------------------
//*****************************************************************
//-----------------------------------------------------------------


//========================================================
//			APIs Supported by "MCAL I2C DRIVER"
//========================================================

void MCAL_I2C_Init(I2C_TypeDef* I2Cx , I2C_Config_t* I2C_Config);
void MCAL_I2C_Reset(I2C_TypeDef* I2Cx );

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx);

void MCAL_I2C_MASTER_TX (I2C_TypeDef* I2Cx ,uint16_t device_Address,uint8_t* Data ,  uint32_t Data_Length , E_STOP_CONDITION Stop ,E_Repeated_Start Start );
void MCAL_I2C_MASTER_RX (I2C_TypeDef* I2Cx ,uint16_t device_Address,uint8_t* Data ,  uint32_t Data_Length , E_STOP_CONDITION Stop ,E_Repeated_Start Start );

void MCAL_I2C_SLAVE_TX (I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t MCAL_I2C_SLAVE_RX (I2C_TypeDef* I2Cx);






//========================================================
//					Generic APIs
//========================================================
void I2C_GenerateSTART(I2C_TypeDef* I2Cx,E_Functional_State State ,E_Repeated_Start Start );

E_I2C_Flag_Status I2C_Get_Status ( I2C_TypeDef* I2Cx , E_Status flag);

void I2C_SendAddress (I2C_TypeDef* I2Cx , uint16_t Address, E_Direction I2C_Direction);

void I2C_GenerateSTOP(I2C_TypeDef* I2Cx,E_Functional_State State);

void I2C_AckConfig (I2C_TypeDef* I2Cx, E_Functional_State State);





#endif /* INC_STM32F103X8_I2C_DRIVER_H_ */
