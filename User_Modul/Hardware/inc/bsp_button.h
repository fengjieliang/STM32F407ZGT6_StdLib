#ifndef BSP_BUTTON_H
#define BSP_BUTTON_H


#include "stm32f4xx.h"


#define KEY1	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY2	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define KEY3	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)


void bsp_button_init(void);
uint8_t bsp_keyscan(uint8_t mode);			//mode=1 ������		mode=0 ������






#endif
