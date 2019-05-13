#ifndef BSP_BEEP_H
#define BSP_BEEP_H

#include "stm32f4xx.h"
#include "delay.h"



void bsp_beep_init(void);
void bsp_beep_on(void);
void bsp_beep_off(void);
void bsp_alarm(uint8_t num);






#endif

