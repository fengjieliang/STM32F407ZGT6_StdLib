#include "bsp_led.h"
#include "delay.h"
#include "stdio.h"
void bsp_led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;				//PF9 PF10
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOF,&GPIO_InitStructure);

	bsp_led_off(LED1);
	bsp_led_off(LED2);
	
}



void bsp_led_on(uint16_t GPIO_Pin)
{
	if (GPIO_Pin==LED1)
	GPIO_ResetBits(GPIOF,LED1);
	
	if (GPIO_Pin==LED2)
	GPIO_ResetBits(GPIOF,LED2);

}


void bsp_led_off(uint16_t GPIO_Pin)
{
	if (GPIO_Pin==LED1)
	GPIO_SetBits(GPIOF,LED1);
	
	if (GPIO_Pin==LED2)
	GPIO_SetBits(GPIOF,LED2);

}


void bsp_led_toggle(uint16_t GPIO_Pin)
{
	if (GPIO_Pin==LED1)
	GPIO_ToggleBits(GPIOF,LED1);
	
	if (GPIO_Pin==LED2)
	GPIO_ToggleBits(GPIOF,LED2);

}



void bsp_led_flash(uint16_t GPIO_Pin,uint16_t flash_num, uint16_t interval)
{
	for(int i=0;i<flash_num;i++)
	{
		printf("i=%d\r\n",i);
		bsp_led_toggle(GPIO_Pin);
		delay_ms(interval);
	}
}
