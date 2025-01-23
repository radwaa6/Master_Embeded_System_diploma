





#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "stm32f103x6.h"
#include "stm32_F103C6_EXTI_driver.h"
#include "stm32_F103C6_gpio_driver.h"
#include "uart.h"

void init_clk(void){
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();




}




unsigned char ch;
void hassan_callback(void){

	MCAL_UART_ReceiveData(USART1, &ch, Disable);
	MCAL_UART_SendData(USART1, &ch, Enable);




}



int main(void)
{
	USART_Config uartCFG;

	init_clk();
	 uartCFG.Baud_Rate = USART_BAUDRATE_115200;
	 uartCFG.Flow_Control = USART_FLOW_CONTROL_None;
	 uartCFG.IRQ_Enable = USART_IRQ_Enable_RXNEIE;
	 uartCFG.Parity = USART_Parity_Type_None;
	 uartCFG.Stop_bits = USART_STOP_Bits_one;
	 uartCFG.Payload_Length = USART_8_DATA_Bits;
	 uartCFG.USART_Mode = USART_MODE_TX_RX;
	 uartCFG.P_IRQ_Callback = hassan_callback;
MCAL_UART_Init(USART1, &uartCFG);
MCAL_UART_GPIO_Set_Pins(USART1);





    /* Loop forever */
while(1){
//	MCAL_UART_ReceiveData(USART1, &ch, Enable);
//	MCAL_UART_SendData(USART1, &ch, Enable);


}







}
