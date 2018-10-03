#include "main.h"

uint8_t hour=0;
uint8_t min=0;
uint8_t sec=0;

uint8_t year=0;
uint8_t month=0;
uint8_t date=0;
uint8_t weekday=0;

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
	printf("********************STM32F407 Project********************\r\n");
	
	while(1)
	{
		BSP_RTC_GetDate(&year,&month,&date,&weekday);
		printf("20%d年%d月%d日 星期%d ",year,month,date,weekday);
		BSP_RTC_GetTime(&hour,&min,&sec);
		printf("%d点%d分%d秒\r\n",hour,min,sec);
		
		delay_ms(1000);
		
	}





}
