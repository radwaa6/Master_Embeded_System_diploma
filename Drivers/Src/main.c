





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
#include "CAN.h"
CAN_HandleTypeDef hcan;

int main(void)
{
	    GPS_Init(USART1);

	    while (1) {
	        GPS_ReadData(USART1);

	        printf("Latitude: %.6f, Longitude: %.6f, Speed: %.2f km/h\n",
	               gps_data.latitude, gps_data.longitude, gps_data.speed);

	        for (volatile int i = 0; i < 1000000; i++);
	    }







}
