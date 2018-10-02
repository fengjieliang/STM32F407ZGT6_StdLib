#include "bsp_led.h"


void BSP_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;				//PF9 PF10
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOF,&GPIO_InitStructure);

	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	
}



void BSP_LED_On(uint16_t GPIO_Pin)
{
	if (GPIO_Pin==LED1)
	GPIO_ResetBits(GPIOF,LED1);
	
	if (GPIO_Pin==LED2)
	GPIO_ResetBits(GPIOF,LED2);

}


void BSP_LED_Off(uint16_t GPIO_Pin)
{
	if (GPIO_Pin==LED1)
	GPIO_SetBits(GPIOF,LED1);
	
	if (GPIO_Pin==LED2)
	GPIO_SetBits(GPIOF,LED2);

}


void BSP_LED_Toggle(uint16_t GPIO_Pin)
{
	if (GPIO_Pin==LED1)
	GPIO_ToggleBits(GPIOF,LED1);
	
	if (GPIO_Pin==LED2)
	GPIO_ToggleBits(GPIOF,LED2);

}
