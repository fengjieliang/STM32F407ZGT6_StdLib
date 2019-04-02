#include "rtos_task.h"

void vTaskLed1(void *pvParameters)
{
    /* ������һ�����ޣ����ܷ��� */
    while(1)
    {
       BSP_LED_Toggle(LED1);
    /* ������ʱ����λms */        
       vTaskDelay( 100 );
    }    
}


void vTaskLed2(void *pvParameters)
{
    /* ������һ�����ޣ����ܷ��� */
    while(1)
    {
       BSP_LED_Toggle(LED2);
			
    /* ������ʱ����λms */        
        vTaskDelay( 500 );
    }    
}


void AppTaskCreate(void)
{
    xTaskCreate(vTaskLed1,           /* �������� */
                "Task Led1",         /* ���������ַ�����ʽ��������� */
                 512,                /* ջ��С����λΪ�֣���4���ֽ� */
                 NULL,               /* �����β� */
                 1,                  /* ���ȼ�����ֵԽ�����ȼ�Խ�� */
                 NULL);  /* ������ */
	
	
	xTaskCreate(vTaskLed2,           /* �������� */
                "Task Led2",         /* ���������ַ�����ʽ��������� */
                 512,                /* ջ��С����λΪ�֣���4���ֽ� */
                 NULL,               /* �����β� */
                 2,                  /* ���ȼ�����ֵԽ�����ȼ�Խ�� */
                 NULL);  /* ������ */
}

