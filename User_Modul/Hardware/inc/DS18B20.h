#ifndef DS18B20_H
#define DS18B20_H
#include "delay.h"


void DS18B20_Init(void);
void DS18B20_Write(uint8_t data);
uint8_t DS18B20_Read(void);
float ReadTemperature_DS18B20(void);















#endif
