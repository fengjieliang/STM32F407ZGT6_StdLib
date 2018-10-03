#ifndef BSP_BEEP_H
#define BSP_BEEP_H

#include "stm32f4xx.h"
#include "delay.h"



void BSP_BEEP_Init(void);
void BSP_BEEP_On(void);
void BSP_BEEP_Off(void);
void BSP_Alarm(uint8_t num);






#endif

