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
	BSP_RTC_Init();
	
	//Application
	UART_Main_Menu();
	
	while(1)
	{

//		
//		delay_ms(1000);
		UART_Menu_Handler();
		
	}





}
