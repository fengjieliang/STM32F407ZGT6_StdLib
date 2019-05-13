#include "delay.h"

#define SYSTEM_SUPPORT_OS	1

#if SYSTEM_SUPPORT_OS==0

	static uint32_t  fac_us=0;							//us��ʱ������			   
	static uint32_t fac_ms=0;							//ms��ʱ������,��os��,����ÿ�����ĵ�ms��

	void delay_init(void)
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

#else

	void delay_init(void)
	{
		TIM_TimeBaseInitTypeDef Timer;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		
		Timer.TIM_Period = 1;
		Timer.TIM_Prescaler = 84;	//ϵͳʱ��168M��APB1ʱ��Ϊ84M����Ƶϵ��Ϊ8400������TIM2��Ƶ��Ϊ84M/8400=10000Hz������1000*10��Ϊ1Hz����1s
		Timer.TIM_ClockDivision = TIM_CKD_DIV1;
		Timer.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &Timer);

	}

	void delay_us(u32 nus)
	{
			uint32_t differ=0xffffffff-nus-5;
		/*Ϊ��ֹ���жϴ����ʱ����ɼ�������.
			 ���0xfffE��ʼ��ʱ1us,�������жϴ��
			����ʱ���������ڼ����������������0xffff��
			��ֹͣ�����������ڴ������ֵ��������arrֵ��
			����ʵ����ʱ(0xffff+1)us
			*/
		
		TIM_Cmd(TIM2,ENABLE);
		
		TIM_SetCounter(TIM2,differ);
		
		while(differ<0xffffffff-5)
			{
					differ=TIM_GetCounter(TIM2);
			}

			TIM_Cmd(TIM2,DISABLE);
	
	
	
	}

	void delay_ms(u16 nms)
	{
		delay_us(nms*1000);
	}








#endif


