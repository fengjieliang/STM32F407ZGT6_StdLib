#include "bsp_eeprom.h"


void bsp_eeprom_init(void)
{
	I2C_InitTypeDef I2C_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_I2C1);
	
	GPIO_InitStructure.GPIO_Mode	=	GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType	=	GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_9|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_PuPd	=	GPIO_PuPd_NOPULL;		//GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed	=	GPIO_Speed_50MHz;

	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	
		
	I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed=100000;
	I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1=0x00;		//We are the master. We don't need this
	
	
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);
	I2C_AcknowledgeConfig(I2C1, ENABLE); 

}



void bsp_eeprom_writeonebyte(uint16_t MemAddress, uint8_t Data)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));
	
	I2C_Send7bitAddress(I2C1,ADDR_24Cxx,I2C_Direction_Transmitter);
	
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));

	I2C_SendData(I2C1,MemAddress);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
	
	I2C_SendData(I2C1,Data);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	delay_ms(5);
	
}



void bsp_eeprom_writepage(uint16_t MemAddress, uint8_t *pData, uint8_t size)
{
	if(size>EEPROM_PageSize)
	{
		printf("eeprom can max write 8 Bytes pro page,please check it!");
		return;
	}

	I2C_GenerateSTART(I2C1,ENABLE);
	
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));
	
	I2C_Send7bitAddress(I2C1,ADDR_24Cxx,I2C_Direction_Transmitter);
	
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));
	
	I2C_SendData(I2C1,MemAddress);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
	
	while(size--)
	{
		I2C_SendData(I2C1,*pData);
		while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
		
		pData++;
	}
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
	delay_ms(5);
	
	
}



void bsp_eeprom_writebuffer(uint16_t MemAddress, uint8_t *pData, uint16_t size)
{
	if((MemAddress+size)>256)
	{
		printf("24c02 can max save 256 Bytes, please check it!");
		return;
	}
	
	uint8_t number_of_page=0;
	uint8_t remainder=0;
	
	if(MemAddress%EEPROM_PageSize==0)	//地址和Page对齐
	{
		number_of_page=size/EEPROM_PageSize;
		remainder=size%EEPROM_PageSize;

		while(number_of_page--)
		{
			bsp_eeprom_writepage(MemAddress,pData,EEPROM_PageSize);
			MemAddress+=EEPROM_PageSize;
			pData+=EEPROM_PageSize;
		}
		bsp_eeprom_writepage(MemAddress,pData,remainder);
	}
	else //地址没有对齐
	{
		uint8_t number_of_bytes = EEPROM_PageSize-MemAddress%EEPROM_PageSize;
		
		bsp_eeprom_writepage(MemAddress,pData,number_of_bytes);
		MemAddress+=number_of_bytes;
		pData+=number_of_bytes;
		size-=number_of_bytes;
		
		number_of_page=size/EEPROM_PageSize;
		remainder=size%EEPROM_PageSize;
		
		while(number_of_page--)
		{
			bsp_eeprom_writepage(MemAddress,pData,EEPROM_PageSize);
			MemAddress+=EEPROM_PageSize;
			pData+=EEPROM_PageSize;
		}
		bsp_eeprom_writepage(MemAddress,pData,remainder);
		
	}
	
	
}






void eeprom_readonebyte(uint16_t MemAddress, uint8_t *pData)
{
	I2C_GenerateSTART(I2C1,ENABLE);

	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));
	
	I2C_Send7bitAddress(I2C1,ADDR_24Cxx,I2C_Direction_Transmitter);

	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)))
	{};
	
	I2C_SendData(I2C1,MemAddress);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
	
	I2C_GenerateSTART(I2C1,ENABLE);

	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));
	
	I2C_Send7bitAddress(I2C1,ADDR_24Cxx,I2C_Direction_Receiver);
	
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)));
	
	
	I2C_AcknowledgeConfig(I2C1,DISABLE);
	
	
	
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)));
	
	*pData=I2C_ReceiveData(I2C1);
	
	
	I2C_GenerateSTOP(I2C1,ENABLE);
	
//	I2C_AcknowledgeConfig(I2C1,ENABLE);
	
}



void eeprom_readbuffer(uint16_t MemAddress, uint8_t *pData,uint16_t size)
{
	I2C_GenerateSTART(I2C1,ENABLE);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));
	
	I2C_Send7bitAddress(I2C1,ADDR_24Cxx,I2C_Direction_Transmitter);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)))
	{};
	
	I2C_SendData(I2C1,MemAddress);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
	
	I2C_GenerateSTART(I2C1,ENABLE);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));

	I2C_Send7bitAddress(I2C1,ADDR_24Cxx,I2C_Direction_Receiver);
	while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)));	
		
	while(size--)
	{
		if(size==0)
		{
			//作出非应答信号
			I2C_AcknowledgeConfig(I2C1, DISABLE);
		}
		else
		{
			//作出应答信号
			I2C_AcknowledgeConfig(I2C1, ENABLE);
		}
		while((!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)));
		
		*pData=I2C_ReceiveData(I2C1);
		pData++;
	
	}
	I2C_GenerateSTOP(I2C1,ENABLE);	
}




