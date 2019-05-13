#include "uart_menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

uint8_t CMD_HELP[]="help";
uint8_t CMD_TIME[]="time";
uint8_t CMD_SETTIME[]="settime";
uint8_t CMD_SETDATE[]="setdate";
uint8_t CMD_RESTART[]="restart";

void UART_Menu_Handler(void)
{
	if(memcmp(rx_data,CMD_HELP,strlen((char*)CMD_HELP))==0)
		UART_Menu_Help();
	else if(memcmp(rx_data,CMD_TIME,strlen((char*)CMD_TIME))==0)
		UART_Menu_Time();
	else if(memcmp(rx_data,CMD_SETTIME,strlen((char*)CMD_SETTIME))==0)
		UART_Menu_Set_Time();
	else if(memcmp(rx_data,CMD_SETDATE,strlen((char*)CMD_SETDATE))==0)
		UART_Menu_Set_Date();
	else if(memcmp(rx_data,CMD_RESTART,strlen((char*)CMD_RESTART))==0)
		UART_Menu_Restart();
	
}

void UART_Main_Menu(void)
{
	printf("********************STM32F407 IoT Device********************\r\n");
	printf("欢迎使用STM32F407 IoT 开发板\r\n");
	
	printf("当前时间为 ");
	UART_Menu_Time();
	
	printf("如果需要帮助，请输入help\r\n");


}

void UART_Menu_Help(void)
{
	UART_Menu_Clear_RXData();
	
	printf("-------STM32F407 IoT Device Help Menu-------\r\n");

	printf("查询帮助------->help\r\n");
	printf("查询时间------->time\r\n");
	
	printf("更改时间------->settime\r\n");
	printf("更改日期------->setdate\r\n");
	
	printf("重启设备------->restart\r\n");

}


void UART_Menu_Time(void)
{
		UART_Menu_Clear_RXData();
	
		uint8_t hour=0;
		uint8_t min=0;
		uint8_t sec=0;

		uint8_t year=0;
		uint8_t month=0;
		uint8_t date=0;
		uint8_t weekday=0;
	
		bsp_rtc_getdate(&year,&month,&date,&weekday);
		printf("20%d年%d月%d日 星期%d ",year,month,date,weekday);
		bsp_rtc_gettime(&hour,&min,&sec);
		printf("%d点%d分%d秒\r\n",hour,min,sec);

}


void UART_Menu_Set_Time(void)
{
	uint8_t hour=0;
	uint8_t min=0;
	uint8_t sec=0;
	
	bool flag_hour=false;
	bool flag_min=false;
	bool flag_sec=false;
	
	UART_Menu_Clear_RXData();						//清空串口接收的数据
	
	printf(">-----现在开始更改时间\r\n");
	printf("  >-----请输入小时\r\n");
	
	while(flag_hour==false)				//循环，直到数据有效
	{
		while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
		{}
		hour=atoi((char *)rx_data);	//将串口接收的数据转换为数字
		UART_Menu_Clear_RXData();		//清空串口接收的数据
		if(hour>=24)								//判断数据有效性
			printf("数据无效，请重新输入\r\n");
		else
			flag_hour=true;						//标志置为1
	}
	printf("   >-----%d点\r\n",hour);
	
	printf("  >-----请输入分钟\r\n");
	
	while(flag_min==false)
	{
		while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
		{}
		min=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(min>=60)
			printf("数据无效，请重新输入\r\n");
		else
			flag_min=true;
	}
	printf("   >-----%d分\r\n",min);	
		
	printf("  >-----请输入秒\r\n");
	
	while(flag_sec==false)
	{
		while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
		{}
		sec=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(sec>=60)
			printf("数据无效，请重新输入\r\n");
		else
			flag_sec=true;
	}
	printf("   >-----%d秒\r\n",sec);
		
	printf(">-----修改后的时间为：%d点%d分%d秒 \r\n",hour,min,sec);
	
	printf(">-----请确定(y/n)\r\n");
	while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
	{}
	if(rx_data[0]=='y'||rx_data[0]=='Y')
	{
		bsp_rtc_set_time(hour,min,sec,RTC_H12_AM);
		printf(">-----设置完成，请输入time查看日期\r\n");
	}
	else
		hour=min=sec=0;
		
		
}

void UART_Menu_Set_Date(void)
{
	uint8_t year=0;
	uint8_t month=0;
	uint8_t day=0;
	uint8_t week=0;
	
	bool flag_year=false;
	bool flag_month=false;
	bool flag_day=false;
	bool flag_week=false;
	
	UART_Menu_Clear_RXData();						//清空串口接收的数据
	
	printf(">-----现在开始更改年份\r\n");
	printf("  >-----请输入年份(0-99)\r\n");
	
	while(flag_year==false)				//循环，直到数据有效
	{
		while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
		{}
		year=atoi((char *)rx_data);	//将串口接收的数据转换为数字
		UART_Menu_Clear_RXData();		//清空串口接收的数据
		if(year>99)								//判断数据有效性
			printf("数据无效，请重新输入\r\n");
		else
			flag_year=true;						//标志置为1
	}
	printf("   >-----20%d年\r\n",year);
	
	printf("  >-----请输入月份\r\n");
	
	while(flag_month==false)
	{
		while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
		{}
		month=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(month>12)
			printf("数据无效，请重新输入\r\n");
		else
			flag_month=true;
	}
	printf("   >-----%d月\r\n",month);	
		
	printf("  >-----请输入日期\r\n");
	
	while(flag_day==false)
	{
		while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
		{}
		day=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(day>31)
			printf("数据无效，请重新输入\r\n");
		else
			flag_day=true;
	}
	printf("   >-----%d日\r\n",day);
	
	
	printf("  >-----请输入星期\r\n");
	
	while(flag_week==false)
	{
		while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
		{}
		week=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(week>7||week==0)
			printf("数据无效，请重新输入\r\n");
		else
			flag_week=true;
	}
	printf("   >-----星期%d\r\n",week);
	
	
	
	
		
	printf(">-----修改后的日期为：20%d年%d月%d日  星期%d \r\n",year,month,day,week);
	
	printf(">-----请确定(y/n)\r\n");
	while(rx_data_length<1)			//收到的长度大于1，表示有数据输入
	{}
	if(rx_data[0]=='y'||rx_data[0]=='Y')
	{
		bsp_rtc_set_date(year,month,day,week);
		printf(">-----设置完成，请输入time查看日期\r\n");
	}
	else
		year=month=day=week=0;
	
	
}




void UART_Menu_Restart(void)
{
	printf(">-----设备即将重启\r\n");
	printf(" >-----5\r\n");
	delay_ms(1000);
	printf(" >-----4\r\n");
	delay_ms(1000);
	printf(" >-----3\r\n");
	delay_ms(1000);
	printf(" >-----2\r\n");
	delay_ms(1000);
	printf(" >-----1\r\n");
	delay_ms(1000);
	NVIC_SystemReset();
}






static void UART_Menu_Clear_RXData(void)
{
	memset(rx_data,0,sizeof(rx_data));
	rx_data_length=0;

}


