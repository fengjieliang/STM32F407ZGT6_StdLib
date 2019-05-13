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
	printf("��ӭʹ��STM32F407 IoT ������\r\n");
	
	printf("��ǰʱ��Ϊ ");
	UART_Menu_Time();
	
	printf("�����Ҫ������������help\r\n");


}

void UART_Menu_Help(void)
{
	UART_Menu_Clear_RXData();
	
	printf("-------STM32F407 IoT Device Help Menu-------\r\n");

	printf("��ѯ����------->help\r\n");
	printf("��ѯʱ��------->time\r\n");
	
	printf("����ʱ��------->settime\r\n");
	printf("��������------->setdate\r\n");
	
	printf("�����豸------->restart\r\n");

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
		printf("20%d��%d��%d�� ����%d ",year,month,date,weekday);
		bsp_rtc_gettime(&hour,&min,&sec);
		printf("%d��%d��%d��\r\n",hour,min,sec);

}


void UART_Menu_Set_Time(void)
{
	uint8_t hour=0;
	uint8_t min=0;
	uint8_t sec=0;
	
	bool flag_hour=false;
	bool flag_min=false;
	bool flag_sec=false;
	
	UART_Menu_Clear_RXData();						//��մ��ڽ��յ�����
	
	printf(">-----���ڿ�ʼ����ʱ��\r\n");
	printf("  >-----������Сʱ\r\n");
	
	while(flag_hour==false)				//ѭ����ֱ��������Ч
	{
		while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
		{}
		hour=atoi((char *)rx_data);	//�����ڽ��յ�����ת��Ϊ����
		UART_Menu_Clear_RXData();		//��մ��ڽ��յ�����
		if(hour>=24)								//�ж�������Ч��
			printf("������Ч������������\r\n");
		else
			flag_hour=true;						//��־��Ϊ1
	}
	printf("   >-----%d��\r\n",hour);
	
	printf("  >-----���������\r\n");
	
	while(flag_min==false)
	{
		while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
		{}
		min=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(min>=60)
			printf("������Ч������������\r\n");
		else
			flag_min=true;
	}
	printf("   >-----%d��\r\n",min);	
		
	printf("  >-----��������\r\n");
	
	while(flag_sec==false)
	{
		while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
		{}
		sec=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(sec>=60)
			printf("������Ч������������\r\n");
		else
			flag_sec=true;
	}
	printf("   >-----%d��\r\n",sec);
		
	printf(">-----�޸ĺ��ʱ��Ϊ��%d��%d��%d�� \r\n",hour,min,sec);
	
	printf(">-----��ȷ��(y/n)\r\n");
	while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
	{}
	if(rx_data[0]=='y'||rx_data[0]=='Y')
	{
		bsp_rtc_set_time(hour,min,sec,RTC_H12_AM);
		printf(">-----������ɣ�������time�鿴����\r\n");
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
	
	UART_Menu_Clear_RXData();						//��մ��ڽ��յ�����
	
	printf(">-----���ڿ�ʼ�������\r\n");
	printf("  >-----���������(0-99)\r\n");
	
	while(flag_year==false)				//ѭ����ֱ��������Ч
	{
		while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
		{}
		year=atoi((char *)rx_data);	//�����ڽ��յ�����ת��Ϊ����
		UART_Menu_Clear_RXData();		//��մ��ڽ��յ�����
		if(year>99)								//�ж�������Ч��
			printf("������Ч������������\r\n");
		else
			flag_year=true;						//��־��Ϊ1
	}
	printf("   >-----20%d��\r\n",year);
	
	printf("  >-----�������·�\r\n");
	
	while(flag_month==false)
	{
		while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
		{}
		month=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(month>12)
			printf("������Ч������������\r\n");
		else
			flag_month=true;
	}
	printf("   >-----%d��\r\n",month);	
		
	printf("  >-----����������\r\n");
	
	while(flag_day==false)
	{
		while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
		{}
		day=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(day>31)
			printf("������Ч������������\r\n");
		else
			flag_day=true;
	}
	printf("   >-----%d��\r\n",day);
	
	
	printf("  >-----����������\r\n");
	
	while(flag_week==false)
	{
		while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
		{}
		week=atoi((char *)rx_data);
		UART_Menu_Clear_RXData();
		if(week>7||week==0)
			printf("������Ч������������\r\n");
		else
			flag_week=true;
	}
	printf("   >-----����%d\r\n",week);
	
	
	
	
		
	printf(">-----�޸ĺ������Ϊ��20%d��%d��%d��  ����%d \r\n",year,month,day,week);
	
	printf(">-----��ȷ��(y/n)\r\n");
	while(rx_data_length<1)			//�յ��ĳ��ȴ���1����ʾ����������
	{}
	if(rx_data[0]=='y'||rx_data[0]=='Y')
	{
		bsp_rtc_set_date(year,month,day,week);
		printf(">-----������ɣ�������time�鿴����\r\n");
	}
	else
		year=month=day=week=0;
	
	
}




void UART_Menu_Restart(void)
{
	printf(">-----�豸��������\r\n");
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


