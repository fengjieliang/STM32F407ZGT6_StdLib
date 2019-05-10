#include "rtos_task.h"

TaskHandle_t xHandleTaskLED1;
TaskHandle_t xHandleTaskLED2;


uint32_t uIdleCycleCounter=0;

void vApplicationIdleHook(void)
{
	uIdleCycleCounter++;

}


void vTaskLED(void *pvParameters)
{
	int *piParameters;
	piParameters=(int *)pvParameters;
	while(1)
	{
		if(*piParameters==1)
		{
			BSP_LED_Toggle(LED1);
    /* ������ʱ����λms */        
       vTaskDelay( 100 );
		
		}
		else if (*piParameters==2)
		{
			BSP_LED_Toggle(LED2);
    /* ������ʱ����λms */        
       vTaskDelay( 100 );
		
		}
	
	}

}




void vTaskLed1(void *pvParameters)
{
    /* ������һ�����ޣ����ܷ��� */
    while(1)
    {
       BSP_LED_On(LED1);
			BSP_LED_Off(LED2);
//			 printf("LED1\r\n");
    /* ������ʱ����λms */        
//       vTaskDelay(500);
			
			
    }    
}


void vTaskLed2(void *pvParameters)
{
    /* ������һ�����ޣ����ܷ��� */
    while(1)
    {
       BSP_LED_On(LED2);
			 
    /* ������ʱ����λms */        
//        vTaskDelay(100);
//			portTickType xLastWakeTime;
//			xLastWakeTime=xTaskGetTickCount();
//			vTaskDelayUntil( &xLastWakeTime, (500/portTICK_RATE_MS));
			vTaskPrioritySet(xHandleTaskLED1,4);
    }    
}



void AppTaskCreate(void)
{
    xTaskCreate(vTaskLed1,           /* �������� */
                "Task Led1",         /* ���������ַ�����ʽ��������� */
                 512,                /* ջ��С����λΪ�֣���4���ֽ� */
                 NULL,               /* �����β� */
                 2,                  /* ���ȼ�����ֵԽ�����ȼ�Խ�� */
                 &xHandleTaskLED1);  /* ������ */
	
	
	xTaskCreate(vTaskLed2,           /* �������� */
                "Task Led2",         /* ���������ַ�����ʽ��������� */
                 512,                /* ջ��С����λΪ�֣���4���ֽ� */
                 NULL,               /* �����β� */
                 3,                  /* ���ȼ�����ֵԽ�����ȼ�Խ�� */
                 &xHandleTaskLED2);  /* ������ */
	
	
//	xTaskCreate(vTaskLED,           /* �������� */
//                "Task LED",         /* ���������ַ�����ʽ��������� */
//                 512,                /* ջ��С����λΪ�֣���4���ֽ� */
//                 (void *)&task_led1,               /* �����β� */
//                 2,                  /* ���ȼ�����ֵԽ�����ȼ�Խ�� */
//                 NULL);  /* ������ */

}

