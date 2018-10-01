#include "delay.h"

static uint32_t  fac_us=0;							//us延时倍乘数			   
static uint32_t fac_ms=0;							//ms延时倍乘数,在os下,代表每个节拍的ms数

void DelayInit(void)
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




