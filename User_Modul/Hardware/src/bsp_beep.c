#include "bsp_beep.h"


void bsp_beep_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;				//PF8
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOF,&GPIO_InitStructure);

}

void bsp_beep_off(void)
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}


void bsp_beep_on(void)
{
	GPIO_SetBits(GPIOF, GPIO_Pin_8);
}


void bsp_alarm(uint8_t num)
{
	for(int i=0;i<num;i++)
	{
		bsp_beep_on();
		delay_ms(300);
		bsp_beep_off();
		delay_ms(300);
	}

}
