#include "bsp_uart.h"


void bsp_uart_init(u32 baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/******************USART1 for debug*********************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_100MHz;

  
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate						=	baudrate;
	USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode								=	USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity							=	USART_Parity_No;
	USART_InitStructure.USART_StopBits						=	USART_StopBits_1;
	USART_InitStructure.USART_WordLength					=	USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel										=	USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd									=	ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=	3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority					=	3;
	
	NVIC_Init(&NVIC_InitStructure);
	
	
	/******************UART4 for ESP01 module*********************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4);
	
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_100MHz;

  
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate						=	baudrate;
	USART_InitStructure.USART_HardwareFlowControl	=	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode								=	USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity							=	USART_Parity_No;
	USART_InitStructure.USART_StopBits						=	USART_StopBits_1;
	USART_InitStructure.USART_WordLength					=	USART_WordLength_8b;
	
	USART_Init(UART4,&USART_InitStructure);
	USART_Cmd(UART4,ENABLE);
	
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel										=	UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd									=	ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	=	3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority					= 2;
	
	NVIC_Init(&NVIC_InitStructure);
	
}


void USART_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData( pUSARTx, (uint16_t)ch);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}




void USART_SendString(USART_TypeDef * pUSARTx, char *Data)
{
  while(*Data!='\0')
  {
      USART_SendData(pUSARTx, *Data);
      while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);//¶ÁÈ¡´®¿Ú×´Ì¬
      Data++;
  }
}





int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (u8) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return (ch);
}



