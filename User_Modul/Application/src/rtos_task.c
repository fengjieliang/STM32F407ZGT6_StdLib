#include "rtos_task.h"

void vTaskLed1(void *pvParameters)
{
    /* 任务都是一个无限，不能返回 */
    while(1)
    {
       BSP_LED_Toggle(LED1);
    /* 阻塞延时，单位ms */        
       vTaskDelay( 100 );
    }    
}


void vTaskLed2(void *pvParameters)
{
    /* 任务都是一个无限，不能返回 */
    while(1)
    {
       BSP_LED_Toggle(LED2);
			
    /* 阻塞延时，单位ms */        
        vTaskDelay( 500 );
    }    
}


void AppTaskCreate(void)
{
    xTaskCreate(vTaskLed1,           /* 任务函数名 */
                "Task Led1",         /* 任务名，字符串形式，方便调试 */
                 512,                /* 栈大小，单位为字，即4个字节 */
                 NULL,               /* 任务形参 */
                 1,                  /* 优先级，数值越大，优先级越高 */
                 NULL);  /* 任务句柄 */
	
	
	xTaskCreate(vTaskLed2,           /* 任务函数名 */
                "Task Led2",         /* 任务名，字符串形式，方便调试 */
                 512,                /* 栈大小，单位为字，即4个字节 */
                 NULL,               /* 任务形参 */
                 2,                  /* 优先级，数值越大，优先级越高 */
                 NULL);  /* 任务句柄 */
}

