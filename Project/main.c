#include "main.h"

int main(void)
{
	//Peripheral Init
	delay_init();
	bsp_uart_init(115200);
	bsp_timer_init();
	printf("Hello World\r\n");
	bsp_led_init();
//	bsp_button_init();
//	bsp_eeprom_init();
//	bsp_spi_flash_init();
//	bsp_beep_init();
//	bsp_rtc_init();
	bsp_led_flash(LED1,10,300);
	
//	AppTaskCreate();
//	
//	vTaskStartScheduler();
	

		
	while(1)
	{
//		UART_Menu_Handler();
		
	}





}
