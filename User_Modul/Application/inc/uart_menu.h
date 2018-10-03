#ifndef UART_MENU_H
#define UART_MENU_H

#include "stm32f4xx.h"
#include "bsp_uart.h"
#include "bsp_rtc.h"
#include "delay.h"

extern uint8_t rx_data[256];
extern uint8_t rx_data_length;





void UART_Menu_Handler(void);
void UART_Main_Menu(void);

static void UART_Menu_Clear_RXData(void);

void UART_Menu_Help(void);
void UART_Menu_Time(void);

void UART_Menu_Set_Time(void);
void UART_Menu_Set_Date(void);

void UART_Menu_Restart(void);

#endif
