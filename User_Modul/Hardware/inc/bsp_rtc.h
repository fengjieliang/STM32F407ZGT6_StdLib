#ifndef BSP_RTC_H
#define BSP_RTC_H

#include "stm32f4xx.h"



void BSP_RTC_Init(void);
void BSP_RTC_Set_Time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t ampm);
void BSP_RTC_Set_Date(uint8_t year,uint8_t month,uint8_t day,uint8_t week);

void BSP_RTC_GetDate(uint8_t *year,uint8_t *month,uint8_t *day,uint8_t *weekday);
void BSP_RTC_GetTime(uint8_t *hour,uint8_t *min,uint8_t *sec);





#endif
