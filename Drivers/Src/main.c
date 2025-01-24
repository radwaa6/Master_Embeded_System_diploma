





#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "stm32f103x6.h"
#include "stm32_F103C6_EXTI_driver.h"
#include "stm32_F103C6_gpio_driver.h"
#include "gps.h"
#include "uart.h"
#include "string.h"

void init_clk(void){
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();




}




unsigned char ch;
void callback(void){

	MCAL_UART_ReceiveData(USART1, &ch, Disable);
	MCAL_UART_SendData(USART1, &ch, Enable);




}
void UART_Print(USART_typedef* USARTx, const char* str) {
    while (*str) {
        MCAL_UART_TransmitData(USARTx, (uint8_t)*str);
        str++;
    }
}


int main(void)
{
    GPS_Init(USART1);

    while (1)
    {
        GPS_ReadData(USART1);
        GPS_ParseData();

        for (volatile int i = 0; i < 1000000; i++);
    }







}
