#ifndef _UART_H
#define _UART_H

#include "stm32f4xx.h"
#include <stdio.h>

void bsp_uart_init(u32 baudrate);
void USART_SendByte(USART_TypeDef * pUSARTx, uint8_t ch);
void USART_SendString(USART_TypeDef * pUSARTx, char *Data);










#endif
