#ifndef BSP_EEPROM_H
#define BSP_EEPROM_H

#include "stm32f4xx.h"
#include "bsp_uart.h"
#include "delay.h"

#define ADDR_24Cxx 0xA0

#define EEPROM_PageSize 8

void BSP_EEPROM_Init(void);

void bsp_eeprom_writeonebyte(uint16_t MemAddress, uint8_t Data);
void bsp_eeprom_writepage(uint16_t MemAddress, uint8_t *pData, uint8_t size);
void bsp_eeprom_writebuffer(uint16_t MemAddress, uint8_t *pData, uint16_t size);
void eeprom_readonebyte(uint16_t MemAddress, uint8_t *pData);
void eeprom_readbuffer(uint16_t MemAddress, uint8_t *pData,uint16_t size);



#endif
