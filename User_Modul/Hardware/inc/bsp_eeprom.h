#ifndef BSP_EEPROM_H
#define BSP_EEPROM_H

#include "stm32f4xx.h"
#include "bsp_uart.h"
#include "delay.h"

#define ADDR_24Cxx 0xA0

#define EEPROM_PageSize 8

void BSP_EEPROM_Init(void);

void BSP_EEPROM_WriteOneByte(uint16_t MemAddress, uint8_t Data);
void BSP_EEPROM_WritePage(uint16_t MemAddress, uint8_t *pData, uint8_t size);
void BSP_EEPROM_WriteBuffer(uint16_t MemAddress, uint8_t *pData, uint16_t size);
void EEPROM_ReadOneByte(uint16_t MemAddress, uint8_t *pData);
void EEPROM_ReadBuffer(uint16_t MemAddress, uint8_t *pData,uint16_t size);



#endif
