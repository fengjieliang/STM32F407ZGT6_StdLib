/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "bsp_uart.h"
#include "uart_menu.h"
#include "DS18B20.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//  
//}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
uint8_t rx_data[256];
uint8_t rx_data_length;

void USART1_IRQHandler(void)
{
	static uint8_t temp[256];
	static uint8_t i=0;
	
	
	if (USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET) 
	{
		temp[i] = USART_ReceiveData(USART1);
		i++;
	}
	if(i>=2)
	{
		if(temp[i-2]==0x0D&&temp[i-1]==0x0A)
		{
			memcpy(rx_data,temp,sizeof(temp));
			i=0;
			memset(temp,0,sizeof(temp));
			
			for(int i=0;i<256;i++)
			{
				if(rx_data[i]==0x0D&&rx_data[i+1]==0x0A)
				{
					rx_data_length=i;
//					printf("rx_data_length=%d\r\n",rx_data_length);
//					printf("rx_data: %s",rx_data);
				}
			}
		}
	}
}


uint8_t esp01_rx_data[1024];
uint8_t esp01_rx_data_length;
void UART4_IRQHandler(void)
{
	static uint8_t esp_temp[1024];
	static uint8_t i=0;
	
	
	if (USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET) 
	{
		esp_temp[i] = USART_ReceiveData(UART4);
		i++;
	}
	
	if(esp_temp[i-2]==0x0D&&esp_temp[i-1]==0x0A)
	{
		memcpy(esp01_rx_data,esp_temp,sizeof(esp_temp));
		i=0;
		memset(esp_temp,0,sizeof(esp_temp));
		
		for(int i=0;i<1024;i++)
		{
			if(esp01_rx_data[i]==0x0D&&esp01_rx_data[i+1]==0x0A)
			{
				esp01_rx_data_length=i;
//					printf("esp01_rx_data_length=%d\r\n",esp01_rx_data_length);
				printf("%s",esp01_rx_data);
			}
		}
	}


}


void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) == SET)
	{
		static float temperature;
		temperature=ReadTemperature_DS18B20();
		printf("temperature=%f\r\n",temperature);
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	}
	
	
	
}



/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
