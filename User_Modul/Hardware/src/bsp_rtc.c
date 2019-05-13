#include "bsp_rtc.h"

void bsp_rtc_init(void)
{
	RTC_InitTypeDef RTC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//ʹ��PWRʱ��
	PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ������� 

	if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0x5051)		//�Ƿ��һ������?
	{
		RCC_LSEConfig(RCC_LSE_ON);//LSE ����    
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);	//���ָ����RCC��־λ�������,�ȴ����پ������
			
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��    
		RCC_RTCCLKCmd(ENABLE);	//ʹ��RTCʱ�� 

    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;//RTC�첽��Ƶϵ��(1~0X7F)
    RTC_InitStructure.RTC_SynchPrediv  = 0xFF;//RTCͬ����Ƶϵ��(0~7FFF)
    RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;//RTC����Ϊ,24Сʱ��ʽ
    RTC_Init(&RTC_InitStructure);
 
		bsp_rtc_set_time(15,45,20,RTC_H12_AM);	//����ʱ��
		bsp_rtc_set_date(18,10,3,3);		//��������
	 
		RTC_WriteBackupRegister(RTC_BKP_DR0,0x5051);	//����Ѿ���ʼ������
	} 

}



void bsp_rtc_set_time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t ampm)
{
	RTC_TimeTypeDef RTC_TimeTypeInitStructure;
	
	RTC_TimeTypeInitStructure.RTC_Hours=hour;
	RTC_TimeTypeInitStructure.RTC_Minutes=min;
	RTC_TimeTypeInitStructure.RTC_Seconds=sec;
	RTC_TimeTypeInitStructure.RTC_H12=ampm;
	
	RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructure);
	
}

void bsp_rtc_set_date(uint8_t year,uint8_t month,uint8_t day,uint8_t week)
{
	
	RTC_DateTypeDef RTC_DateTypeInitStructure;
	RTC_DateTypeInitStructure.RTC_Date=day;
	RTC_DateTypeInitStructure.RTC_Month=month;
	RTC_DateTypeInitStructure.RTC_WeekDay=week;
	RTC_DateTypeInitStructure.RTC_Year=year;
	
	RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeInitStructure);
}




void bsp_rtc_getdate(uint8_t *year,uint8_t *month,uint8_t *day,uint8_t *weekday)
{
	RTC_DateTypeDef RTC_DateStruct;

	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
	
	*year		= RTC_DateStruct.RTC_Year;
	*month	=	RTC_DateStruct.RTC_Month;
	*day		=	RTC_DateStruct.RTC_Date;
	*weekday=	RTC_DateStruct.RTC_WeekDay;
}



void bsp_rtc_gettime(uint8_t *hour,uint8_t *min,uint8_t *sec)
{
	RTC_TimeTypeDef RTC_TimeStruct;

	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	
	*hour	=	RTC_TimeStruct.RTC_Hours;
	*min	=	RTC_TimeStruct.RTC_Minutes;
	*sec	=	RTC_TimeStruct.RTC_Seconds;
	
}


