#include "main.h"


uint8_t key_num=0;

int main(void)
{
	//Peripheral Init
	BSP_UART_Init(115200);
	BSP_LEDInit();
	BSP_ButtonInit();
	
	//Application
	printf("STM32F407 Project\r\n");
	
	while(1)
	{
		key_num=BSP_KeyScan(1);
		if(key_num!=0)
			printf("key %d is pressed\r\n",key_num);
	}





}
