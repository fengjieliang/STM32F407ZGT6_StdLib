#include "main.h"


uint8_t key_num=0;

int main(void)
{
	//Peripheral Init
	DelayInit();
	BSP_UART_Init(115200);
	BSP_LED_Init();
	BSP_Button_Init();
	BSP_EEPROM_Init();
	//Application
	printf("STM32F407 Project\r\n");
	while(1)
	{
		
	}





}
