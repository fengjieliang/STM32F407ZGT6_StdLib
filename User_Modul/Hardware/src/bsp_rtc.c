#include "bsp_rtc.h"

void BSP_RTC_Init(void)
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
 
		BSP_RTC_Set_Time(15,45,20,RTC_H12_AM);	//����ʱ��
		BSP_RTC_Set_Date(18,10,3,3);		//��������
	 
		RTC_WriteBackupRegister(RTC_BKP_DR0,0x5051);	//����Ѿ���ʼ������
	} 

}



void BSP_RTC_Set_Time(uint8_t hour,uint8_t min,uint8_t sec,uint8_t ampm)
{
	RTC_TimeTypeDef RTC_TimeTypeInitStructure;
	
	RTC_TimeTypeInitStructure.RTC_Hours=hour;
	RTC_TimeTypeInitStructure.RTC_Minutes=min;
	RTC_TimeTypeInitStructure.RTC_Seconds=sec;
	RTC_TimeTypeInitStructure.RTC_H12=ampm;
	
	RTC_SetTime(RTC_Format_BIN,&RTC_TimeTypeInitStructure);
	
}

void BSP_RTC_Set_Date(uint8_t year,uint8_t month,uint8_t date,uint8_t week)
{
	
	RTC_DateTypeDef RTC_DateTypeInitStructure;
	RTC_DateTypeInitStructure.RTC_Date=date;
	RTC_DateTypeInitStructure.RTC_Month=month;
	RTC_DateTypeInitStructure.RTC_WeekDay=week;
	RTC_DateTypeInitStructure.RTC_Year=year;
	
	RTC_SetDate(RTC_Format_BIN,&RTC_DateTypeInitStructure);
}




void BSP_RTC_GetDate(uint8_t *year,uint8_t *month,uint8_t *date,uint8_t *weekday)
{
	RTC_DateTypeDef RTC_DateStruct;

	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
	
	*year		= RTC_DateStruct.RTC_Year;
	*month	=	RTC_DateStruct.RTC_Month;
	*date		=	RTC_DateStruct.RTC_Date;
	*weekday=	RTC_DateStruct.RTC_WeekDay;
}



void BSP_RTC_GetTime(uint8_t *hour,uint8_t *min,uint8_t *sec)
{
	RTC_TimeTypeDef RTC_TimeStruct;

	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	
	*hour	=	RTC_TimeStruct.RTC_Hours;
	*min	=	RTC_TimeStruct.RTC_Minutes;
	*sec	=	RTC_TimeStruct.RTC_Seconds;
	
}

