#include "delay.h"

#define SYSTEM_SUPPORT_OS	1

#if SYSTEM_SUPPORT_OS==0

	static uint32_t  fac_us=0;							//us延时倍乘数			   
	static uint32_t fac_ms=0;							//ms延时倍乘数,在os下,代表每个节拍的ms数

	void delay_init(void)
	{
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
		fac_us=SystemCoreClock/8000000;						
		fac_ms=(uint32_t)fac_us*1000;				
	}

	void delay_us(uint32_t nus)
	{		
		uint32_t temp;	    	 
		SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
		SysTick->VAL=0x00;        				//清空计数器
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //开始倒数 	 
		do
		{
			temp=SysTick->CTRL;
		}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   temp&0x01 判断Systick是否使能，temp&(1<<16) 判断CTRL的第16位（Systic已经记到0了，该位为1），是否计数结束
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //关闭计数器
		SysTick->VAL =0X00;       				//清空计数器 
	}


	/*延时nms
	注意nms的范围
	SysTick->LOAD为24位寄存器,所以,最大延时为:
	nms<=0xffffff*8*1000/SYSCLK
	SYSCLK单位为Hz,nms单位为ms
	对168M条件下,nms<=798ms*/
	void delay_xms(uint16_t nms)
	{	 		  	  
		uint32_t temp;		   
		SysTick->LOAD=(uint32_t)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
		SysTick->VAL =0x00;           			//清空计数器
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数 
		do
		{
			temp=SysTick->CTRL;
		}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
		SysTick->VAL =0X00;     		  		//清空计数器	  	    
	} 

	/*延时nms 
	nms:0~65535*/
	void delay_ms(uint16_t nms)
	{	 	 
		uint8_t repeat=nms/540;						//这里用540,是考虑到某些客户可能超频使用,
												//比如超频到248M的时候,delay_xms最大只能延时541ms左右了
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
		Timer.TIM_Prescaler = 84;	//系统时钟168M，APB1时钟为84M，分频系数为8400，所以TIM2的频率为84M/8400=10000Hz，计数1000*10次为1Hz，即1s
		Timer.TIM_ClockDivision = TIM_CKD_DIV1;
		Timer.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &Timer);

	}

	void delay_us(u32 nus)
	{
			uint32_t differ=0xffffffff-nus-5;
		/*为防止因中断打断延时，造成计数错误.
			 如从0xfffE开始延时1us,但由于中断打断
			（此时计数器仍在计数），本因计数至0xffff）
			便停止计数，但由于错过计数值，并重载arr值，
			导致实际延时(0xffff+1)us
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


