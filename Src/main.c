





#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "stm32f103x6.h"
#include "stm32_F103C6_EXTI_driver.h"
#include "stm32_F103C6_gpio_driver.h"
#include "gps.h"
#include "uart.h"
#include "string.h"
#include "stdio.h"
#include "RCC.h"
#include "CAN.h"
CAN_HandleTypeDef hcan;

int __io_putchar(int ch) {
    MCAL_UART_SendData(USART1, (uint16_t*)&ch, Enable);
    return ch;
}
int main(void)
{
	//MCAL_RCC_SetSystemClockTo16MHz();
	GPIOA_CLOCK_ENABLE;
	AFIO_CLOCK_ENABLE;
	RCC_USART1_CLK_EN();
	    GPS_Init(USART1);
	  //  printf("GPS Initialized!\n");
//	uint8_t c;
//	 USART_Config gps_config;
//	    gps_config.USART_Mode = USART_MODE_TX_RX;
//	    gps_config.Payload_Length = USART_8_DATA_Bits;
//	    gps_config.Parity = USART_Parity_Type_None;
//	    gps_config.Stop_bits = USART_STOP_Bits_one;
//	    gps_config.Flow_Control = USART_FLOW_CONTROL_None	;
//	    gps_config.Baud_Rate = 9600;
//	    gps_config.IRQ_Enable = USART_IRQ_Disable;
//	    MCAL_UART_Init(USART2, &gps_config);
//	       MCAL_UART_GPIO_Set_Pins(USART2);
	    while (1) {
	        GPS_ReadData(USART1);

	    	    //    printf("Latitude: %.6f, Longitude: %.6f, Speed: %.2f km/h\n",
	    	       //        gps_data.latitude, gps_data.longitude, gps_data.speed);

	       // for (volatile int i = 0; i < 1000000; i++);
//	    	MCAL_UART_ReceiveData(USART2, &c, Enable);
//	    	MCAL_UART_SendData(USART2, &c, Enable);
	    }







}
