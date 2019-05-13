#ifndef DS18B20_H
#define DS18B20_H
#include "delay.h"


void ds18b20_init(void);
void DS18B20_Write(uint8_t data);
uint8_t DS18B20_Read(void);
float ds18b20_read_temperature(void);















#endif
