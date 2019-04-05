#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx.h"

#include "delay.h"
#include "uart_menu.h"


#include "bsp_led.h"
#include "bsp_button.h"
#include "bsp_uart.h"
#include "bsp_eeprom.h"
#include "bsp_spi_flash.h"
#include "bsp_beep.h"
#include "bsp_rtc.h"
#include "bsp_timer.h"

#include "DS18B20.h"

#include "rtos_task.h"

#include "FreeRTOS.h"
#include "task.h"

extern uint8_t rx_data[256];
extern uint8_t rx_data_length;










#endif
