#include "gps.h"
#include "string.h"
#include <stdlib.h>

#define GPS_BUFFER_SIZE  100

char gps_buffer[GPS_BUFFER_SIZE];
int gps_index = 0;

GPS_Data gps_data;

void GPS_ReadData(USART_TypeDef* USARTx) {
    uint16_t data;

    MCAL_UART_ReceiveData(USARTx, &data, Enable);
   // MCAL_UART_SendData(USARTx, &data, Enable);
    if (gps_index < GPS_BUFFER_SIZE - 1) {
        gps_buffer[gps_index++] = (char)data;
    }

    if (data == '\n' || gps_index >= GPS_BUFFER_SIZE - 1) {
        gps_buffer[gps_index] = '\0';
        GPS_ParseData(USARTx);
        gps_index = 0;
    }
}

void GPS_ParseData(USART_TypeDef* USARTx)
{
    // Check if we have "$GPRMC" at the start
    if (strncmp(gps_buffer, "$GPRMC", 6) == 0)
    {
        char *token;
        int field_index = 0;

        // Temporary arrays to hold each piece of text
        char timeField[12]  = {0};
        char latField[16]   = {0};
        char nsField[2]     = {0};
        char lonField[16]   = {0};
        char ewField[2]     = {0};
        char speedField[8]  = {0};

        // Use strtok to split by commas
        token = strtok(gps_buffer, ","); // First call
        while (token != NULL)
        {
            switch (field_index)
            {
            // field_index = 1 => Time (hhmmss.sss)
            case 1:
                strncpy(timeField, token, sizeof(timeField)-1);
                break;

            // field_index = 3 => Latitude (e.g. 4807.038)
            case 3:
                strncpy(latField, token, sizeof(latField)-1);
                break;

            // field_index = 4 => 'N' or 'S'
            case 4:
                strncpy(nsField, token, sizeof(nsField)-1);
                break;

            // field_index = 5 => Longitude (e.g. 01131.000)
            case 5:
                strncpy(lonField, token, sizeof(lonField)-1);
                break;

            // field_index = 6 => 'E' or 'W'
            case 6:
                strncpy(ewField, token, sizeof(ewField)-1);
                break;

            // field_index = 7 => Speed in knots
            case 7:
                strncpy(speedField, token, sizeof(speedField)-1);
                break;

            default:
                break;
            }

            field_index++;
            token = strtok(NULL, ","); // Next split
        }

        // Now send them out via UART
        MCAL_UART_SendString(USARTx, (uint8_t*)"\r\n[GPRMC Data]\r\n");

        MCAL_UART_SendString(USARTx, (uint8_t*)"Time: ");
        MCAL_UART_SendString(USARTx, (uint8_t*)timeField);
        MCAL_UART_SendString(USARTx, (uint8_t*)"\r\n");

        MCAL_UART_SendString(USARTx, (uint8_t*)"Latitude: ");
        MCAL_UART_SendString(USARTx, (uint8_t*)latField);
        MCAL_UART_SendString(USARTx, (uint8_t*)" ");
        MCAL_UART_SendString(USARTx, (uint8_t*)nsField);
        MCAL_UART_SendString(USARTx, (uint8_t*)"\r\n");

        MCAL_UART_SendString(USARTx, (uint8_t*)"Longitude: ");
        MCAL_UART_SendString(USARTx, (uint8_t*)lonField);
        MCAL_UART_SendString(USARTx, (uint8_t*)" ");
        MCAL_UART_SendString(USARTx, (uint8_t*)ewField);
        MCAL_UART_SendString(USARTx, (uint8_t*)"\r\n");

        MCAL_UART_SendString(USARTx, (uint8_t*)"Speed(knots): ");
        MCAL_UART_SendString(USARTx, (uint8_t*)speedField);
        MCAL_UART_SendString(USARTx, (uint8_t*)"\r\n");
    }
    // If it's not $GPRMC, we simply ignore it in this example
}

void GPS_Init(USART_TypeDef* USARTx) {
    USART_Config gps_config;
    gps_config.USART_Mode = USART_MODE_TX_RX;
    gps_config.Payload_Length = USART_8_DATA_Bits;
    gps_config.Parity = USART_Parity_Type_None;
    gps_config.Stop_bits = USART_STOP_Bits_one;
    gps_config.Flow_Control = USART_FLOW_CONTROL_None	;
    gps_config.Baud_Rate = 9600;
    gps_config.IRQ_Enable = USART_IRQ_Disable;

    MCAL_UART_Init(USARTx, &gps_config);
    MCAL_UART_GPIO_Set_Pins(USARTx);
}
