#ifndef BSP_LED_H
#define BSP_LED_H

#include "stm32f4xx.h"


#define LED1 GPIO_Pin_9
#define LED2 GPIO_Pin_10



void bsp_led_init(void);
void bsp_led_on(uint16_t GPIO_Pin);
void bsp_led_off(uint16_t GPIO_Pin);
void bsp_led_toggle(uint16_t GPIO_Pin);
void bsp_led_flash(uint16_t GPIO_Pin,uint16_t flash_num, uint16_t interval);






#endif
