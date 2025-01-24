#include "uart.h"
#include "gps.h"

#define GPS_BUFFER_SIZE  100

char gps_buffer[GPS_BUFFER_SIZE];
int gps_index = 0;

void GPS_ReadData(USART_typedef* USARTx) {
    uint16_t data;

    MCAL_UART_ReceiveData(USARTx, &data, Enable);

    if (gps_index < GPS_BUFFER_SIZE) {
        gps_buffer[gps_index++] = (char)data;
    }

    if (gps_index >= GPS_BUFFER_SIZE) {
        gps_index = 0;
    }
}

void GPS_ParseData(void) {
    if (strstr(gps_buffer, "$GPRMC") != NULL) {
        char* latitude = strstr(gps_buffer, "Latitude: ");
        char* longitude = strstr(gps_buffer, "Longitude: ");
    }
}

void GPS_Init(USART_typedef* USARTx) {
    USART_Config gps_config;
    gps_config.USART_Mode = USART_MODE_RX;
    gps_config.Payload_Length = USART_8_DATA_Bits;
    gps_config.Parity = USART_Parity_Type_None;
    gps_config.Stop_bits = USART_STOP_Bits_one;
    gps_config.Flow_Control = USART_FLOW_CONTROL_None	;
    gps_config.Baud_Rate = 9600;
    gps_config.IRQ_Enable = USART_IRQ_Disable;

    MCAL_UART_Init(USARTx, &gps_config);
    MCAL_UART_GPIO_Set_Pins(USARTx);
}
