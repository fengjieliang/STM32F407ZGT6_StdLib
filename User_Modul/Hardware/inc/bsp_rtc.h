#ifndef BSP_RTC_H
#define BSP_RTC_H

#include "stm32f4xx.h"



void bsp_rtc_init(void);
void bsp_rtc_set_time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t ampm);
void bsp_rtc_set_date(uint8_t year,uint8_t month,uint8_t day,uint8_t week);

void bsp_rtc_getdate(uint8_t *year,uint8_t *month,uint8_t *day,uint8_t *weekday);
void bsp_rtc_gettime(uint8_t *hour,uint8_t *min,uint8_t *sec);





#endif
