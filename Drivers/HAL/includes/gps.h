#ifndef GPS_H_
#define GPS_H_

#include "uart.h"

typedef struct {
    float latitude;
    float longitude;
    float speed;
} GPS_Data;

void GPS_ReadData(USART_typedef* USARTx);
void GPS_ParseData(void);
void GPS_Init(USART_typedef* USARTx);

#endif /* GPS_H_ */

