#ifndef BSP_BUTTON_H
#define BSP_BUTTON_H


#include "stm32f4xx.h"


#define KEY1	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY2	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define KEY3	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)


void BSP_Button_Init(void);
uint8_t BSP_KeyScan(uint8_t mode);			//mode=1 ������		mode=0 ������






#endif
