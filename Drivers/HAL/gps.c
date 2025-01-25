#include "gps.h"
#include "string.h"
#include <stdlib.h>

#define GPS_BUFFER_SIZE  100

char gps_buffer[GPS_BUFFER_SIZE];
int gps_index = 0;

GPS_Data gps_data;

void GPS_ReadData(USART_typedef* USARTx) {
    uint16_t data;

    MCAL_UART_ReceiveData(USARTx, &data, Enable);

    if (gps_index < GPS_BUFFER_SIZE - 1) {
        gps_buffer[gps_index++] = (char)data;
    }

    if (data == '\n' || gps_index >= GPS_BUFFER_SIZE - 1) {
        gps_buffer[gps_index] = '\0';
        GPS_ParseData();
        gps_index = 0;
    }
}

void GPS_ParseData(void) {
    if (strstr(gps_buffer, "$GPRMC") != NULL) {
        char* token = strtok(gps_buffer, ",");
        int index = 0;

        while (token != NULL) {
            if (index == 3) { // Latitude
                gps_data.latitude = atof(token) / 100.0;
            } else if (index == 5) { // Longitude
                gps_data.longitude = atof(token) / 100.0;
            } else if (index == 7) { // Speed
                gps_data.speed = atof(token) * 1.852;
            }
            token = strtok(NULL, ",");
            index++;
        }
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
