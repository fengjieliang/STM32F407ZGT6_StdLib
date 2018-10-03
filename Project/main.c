#include "main.h"


int main(void)
{
	//Peripheral Init
	DelayInit();
	BSP_UART_Init(115200);
	BSP_LED_Init();
	BSP_Button_Init();
	BSP_EEPROM_Init();
	BSP_SPI_FLASH_Init();
	BSP_BEEP_Init();
	//Application
	printf("--------------------STM32F407 Project--------------------\r\n");
	printf("*********************************************************\r\n");
	BSP_Alarm(3);
	
	while(1)
	{
		
	}





}
