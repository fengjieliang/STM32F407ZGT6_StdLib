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
    /* 阻塞延时，单位ms */        
       vTaskDelay( 100 );
		
		}
		else if (*piParameters==2)
		{
			BSP_LED_Toggle(LED2);
    /* 阻塞延时，单位ms */        
       vTaskDelay( 100 );
		
		}
	
	}

}




void vTaskLed1(void *pvParameters)
{
    /* 任务都是一个无限，不能返回 */
    while(1)
    {
       BSP_LED_On(LED1);
			BSP_LED_Off(LED2);
//			 printf("LED1\r\n");
    /* 阻塞延时，单位ms */        
//       vTaskDelay(500);
			
			
    }    
}


void vTaskLed2(void *pvParameters)
{
    /* 任务都是一个无限，不能返回 */
    while(1)
    {
       BSP_LED_On(LED2);
			 
    /* 阻塞延时，单位ms */        
//        vTaskDelay(100);
//			portTickType xLastWakeTime;
//			xLastWakeTime=xTaskGetTickCount();
//			vTaskDelayUntil( &xLastWakeTime, (500/portTICK_RATE_MS));
			vTaskPrioritySet(xHandleTaskLED1,4);
    }    
}



void AppTaskCreate(void)
{
    xTaskCreate(vTaskLed1,           /* 任务函数名 */
                "Task Led1",         /* 任务名，字符串形式，方便调试 */
                 512,                /* 栈大小，单位为字，即4个字节 */
                 NULL,               /* 任务形参 */
                 2,                  /* 优先级，数值越大，优先级越高 */
                 &xHandleTaskLED1);  /* 任务句柄 */
	
	
	xTaskCreate(vTaskLed2,           /* 任务函数名 */
                "Task Led2",         /* 任务名，字符串形式，方便调试 */
                 512,                /* 栈大小，单位为字，即4个字节 */
                 NULL,               /* 任务形参 */
                 3,                  /* 优先级，数值越大，优先级越高 */
                 &xHandleTaskLED2);  /* 任务句柄 */
	
	
//	xTaskCreate(vTaskLED,           /* 任务函数名 */
//                "Task LED",         /* 任务名，字符串形式，方便调试 */
//                 512,                /* 栈大小，单位为字，即4个字节 */
//                 (void *)&task_led1,               /* 任务形参 */
//                 2,                  /* 优先级，数值越大，优先级越高 */
//                 NULL);  /* 任务句柄 */

}

