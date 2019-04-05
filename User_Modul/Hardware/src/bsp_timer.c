#include "bsp_timer.h"

void BSP_Timer2_Init(uint32_t period)
{
	TIM_TimeBaseInitTypeDef Timer;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
	Timer.TIM_Period = period;
  Timer.TIM_Prescaler = 8400-1;	//系统时钟168M，APB1时钟为84M，分频系数为8400，所以TIM2的频率为84M/8400=10000Hz，计数10000次为1Hz，即1s
  Timer.TIM_ClockDivision = TIM_CKD_DIV1;
  Timer.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &Timer);
	
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	
//	TIM_OCInitStructure.TIM_Pulse = 1*period/4;
//  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
//	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	
	/* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
	
	
}

