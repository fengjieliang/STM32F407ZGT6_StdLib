#ifndef DELAY_H
#define DELAY_H

#include "stm32f4xx.h"


void DelayInit(void);
void delay_us(u32 nus);
void delay_xms(u16 nms);
void delay_ms(u16 nms);







#endif
