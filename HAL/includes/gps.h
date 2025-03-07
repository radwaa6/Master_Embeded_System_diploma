#ifndef GPS_H_
#define GPS_H_

#include "uart.h"

typedef struct {
    float latitude;
    float longitude;
    float speed;
} GPS_Data;

void GPS_ReadData(USART_TypeDef* USARTx);
void GPS_ParseData(USART_TypeDef* USARTx);
void GPS_Init(USART_TypeDef* USARTx);

extern GPS_Data gps_data;

#endif /* GPS_H_ */
