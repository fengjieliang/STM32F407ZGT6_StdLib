#include "DS18B20.h"



void DS18B20_Pin_Out_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;				//PG9
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOG,&GPIO_InitStructure);

}


void DS18B20_Pin_In_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;				//PG9
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOG,&GPIO_InitStructure);

}







void DS18B20_Init()
{
		DS18B20_Pin_Out_Init();
    GPIO_SetBits(GPIOG,GPIO_Pin_9);
		delay_us(50);
		GPIO_ResetBits(GPIOG,GPIO_Pin_9);
		delay_us(600);
		GPIO_SetBits(GPIOG,GPIO_Pin_9);
		delay_us(70);
	
		DS18B20_Pin_In_Init();
		delay_us(240);
		DS18B20_Pin_Out_Init();
		GPIO_SetBits(GPIOG,GPIO_Pin_9);
}



/**
 * @brief write 1 byte data to temperature sensor DS18B20.
 */
void DS18B20_Write(uint8_t data)
{
	DS18B20_Pin_Out_Init();	
	for (int i = 0; i < 8; i++)
	{
			GPIO_SetBits(GPIOG,GPIO_Pin_9);
			delay_us(10);
			GPIO_ResetBits(GPIOG,GPIO_Pin_9);
			if (data & 0x01)
					GPIO_SetBits(GPIOG,GPIO_Pin_9);
			else
					GPIO_ResetBits(GPIOG,GPIO_Pin_9);

			delay_us(80);
			data >>= 1;
	}
}



/**
 * @brief read 1 byte data from temperature sensor DS18B20.
 */
uint8_t DS18B20_Read()
{
    uint8_t data = 0;

    for (int i = 0; i < 8; i++)
    {
        DS18B20_Pin_Out_Init();	
        GPIO_SetBits(GPIOG,GPIO_Pin_9);
        delay_us(10);
        GPIO_ResetBits(GPIOG,GPIO_Pin_9);
        delay_us(1);
        GPIO_SetBits(GPIOG,GPIO_Pin_9);
        data >>= 1;
        DS18B20_Pin_In_Init();
        if (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_9))
            data |= 0x80;
        delay_us(60);


    }
    DS18B20_Pin_Out_Init();	
    GPIO_SetBits(GPIOG,GPIO_Pin_9);

    return data;
}



/**
 * @brief Function for reading temperature from sensor DS18B20.
 * @param[out] temperature.
 */
float ReadTemperature_DS18B20(void)
{
    float temp_DS18B20 = 0;
		uint8_t temp_L, temp_H;
		int16_t temp_int16;
	
    DS18B20_Init();
    DS18B20_Write(0xcc);                        //skip rom
    DS18B20_Write(0x44);                        //convert temperature
    delay_us(20);
    DS18B20_Init();
    DS18B20_Write(0xcc);                        //skip rom
    DS18B20_Write(0xbe);                        //Read Scratchpad
    temp_L = DS18B20_Read();
    temp_H = DS18B20_Read();
    temp_int16 = ((temp_H << 8) | temp_L);
    temp_DS18B20 = temp_int16 * 0.0625;            //resolution 12bit
    delay_us(100);

    return temp_DS18B20;

}




