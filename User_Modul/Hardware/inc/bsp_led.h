#ifndef BSP_LED_H
#define BSP_LED_H

#include "stm32f4xx.h"


#define LED1 GPIO_Pin_9
#define LED2 GPIO_Pin_10



void BSP_LEDInit(void);
void BSP_LED_On(uint16_t GPIO_Pin);
void BSP_LED_Off(uint16_t GPIO_Pin);
void BSP_LED_Toggle(uint16_t GPIO_Pin);







#endif
