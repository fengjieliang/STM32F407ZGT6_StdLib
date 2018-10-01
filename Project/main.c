#include "main.h"


uint8_t key_num;

int main(void)
{
	//Peripheral Init
	BSP_LEDInit();
	BSP_ButtonInit();
	while(1)
	{
		key_num=BSP_KeyScan(0);
	}





}
