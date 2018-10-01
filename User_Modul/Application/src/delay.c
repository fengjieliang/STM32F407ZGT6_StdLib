#include "delay.h"

static uint32_t  fac_us=0;							//us��ʱ������			   
static uint32_t fac_ms=0;							//ms��ʱ������,��os��,����ÿ�����ĵ�ms��

void DelayInit(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SystemCoreClock/8000000;						
	fac_ms=(uint32_t)fac_us*1000;				
}

void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//ʱ�����	  		 
	SysTick->VAL=0x00;        				//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   temp&0x01 �ж�Systick�Ƿ�ʹ�ܣ�temp&(1<<16) �ж�CTRL�ĵ�16λ��Systic�Ѿ��ǵ�0�ˣ���λΪ1�����Ƿ��������
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //�رռ�����
	SysTick->VAL =0X00;       				//��ռ����� 
}


/*��ʱnms
ע��nms�ķ�Χ
SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
nms<=0xffffff*8*1000/SYSCLK
SYSCLK��λΪHz,nms��λΪms
��168M������,nms<=798ms*/
void delay_xms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*fac_ms;			//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           			//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ���� 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;     		  		//��ռ�����	  	    
} 

/*��ʱnms 
nms:0~65535*/
void delay_ms(uint16_t nms)
{	 	 
	uint8_t repeat=nms/540;						//������540,�ǿ��ǵ�ĳЩ�ͻ����ܳ�Ƶʹ��,
											//���糬Ƶ��248M��ʱ��,delay_xms���ֻ����ʱ541ms������
	uint16_t remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
} 




