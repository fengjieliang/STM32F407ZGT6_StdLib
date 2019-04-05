#include "main.h"

int main(void)
{
	//Peripheral Init
	DelayInit();
	BSP_UART_Init(115200);
	printf("Hello World\r\n");
	BSP_LED_Init();
//	BSP_Button_Init();
//	BSP_EEPROM_Init();
//	BSP_SPI_FLASH_Init();
//	BSP_BEEP_Init();
	BSP_RTC_Init();
	BSP_Timer2_Init(10000);
	//Application
	UART_Main_Menu();
	
//	AppTaskCreate();
//	
//	vTaskStartScheduler();

//	USART_SendString(UART4,"+++");
//	USART_SendString(UART4,"AT+GMR\r\n");
//	delay_ms(500);
//	USART_SendString(UART4,"AT+CWMODE=1\r\n");
//	delay_ms(500);
////		USART_SendString(UART4,"AT+CWLAP\r\n");
////		delay_ms(500);
//	USART_SendString(UART4,"AT+CWJAP=\"FRITZ!Box 7530 RS\",\"16677266609436439722\"\r\n");


//			delay_ms(5000);	
//		USART_SendString(UART4,"AT+CIPMUX=0\r\n");
//			delay_ms(500);
//		USART_SendString(UART4,"AT+CIPSTART=\"TCP\",\"192.168.70.25\",8888\r\n");
//			delay_ms(3000);
//		USART_SendString(UART4,"AT+CIPMODE=1\r\n");
//			delay_ms(500);
//		USART_SendString(UART4,"AT+CIPSEND\r\n");
//			delay_ms(500);
//		USART_SendString(UART4,"Hello World1\r\n");
//			delay_ms(500);
//		USART_SendString(UART4,"Hello World2\r\n");
//			delay_ms(500);
//		USART_SendString(UART4,"Hello World3\r\n");
//			delay_ms(500);
//		USART_SendString(UART4,"Hello World4\r\n");
//			delay_ms(500);
//		USART_SendString(UART4,"Hello World5\r\n");
//			delay_ms(500);
//		USART_SendString(UART4,"Hello World6\r\n");
		
	while(1)
	{
//		UART_Menu_Handler();
		
	}





}
