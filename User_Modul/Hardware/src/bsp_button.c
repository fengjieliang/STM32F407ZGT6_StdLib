#include "bsp_button.h"


void BSP_ButtonInit(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Mode	=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin		=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd	=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_PuPd	=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_High_Speed;	
	GPIO_Init(GPIOE,&GPIO_InitStructure);


}


uint8_t BSP_KeyScan(uint8_t mode)			//mode=1 连续按		mode=0 单独按
{
	static uint8_t key_up=1;		//key_up=1	连续按	key_up=0 单独按
	if (mode==1)
	{key_up=1;}
	
	if(key_up==1	&&	(KEY1==1||KEY2==0||KEY3==0))
	{
		for(int i=0;i<50000;i++)
		{}
		key_up=0;
		if(KEY1==1){
			return 1;
		}
		if(KEY2==0){
			return 2;
		}
		if(KEY3==0){
			return 3;
		}
		
	}
	else if(KEY1==0&&KEY2==1&&KEY3==1)
	{key_up=1;}
	return 0;
	
}
