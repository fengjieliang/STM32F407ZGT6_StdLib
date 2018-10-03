#include "bsp_beep.h"


void BSP_BEEP_Init(void)
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

void BSP_BEEP_Off(void)
{
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}


void BSP_BEEP_On(void)
{
	GPIO_SetBits(GPIOF, GPIO_Pin_8);
}


void BSP_Alarm(uint8_t num)
{
	for(int i=0;i<num;i++)
	{
		BSP_BEEP_On();
		delay_ms(300);
		BSP_BEEP_Off();
		delay_ms(300);
	}

}
