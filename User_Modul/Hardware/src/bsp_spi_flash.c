#include "bsp_spi_flash.h"


void BSP_SPI_FLASH_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC, ENABLE);


  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//使用软件控制CS引脚
	GPIO_InitStructure.GPIO_Pin = SPI1_CS_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStructure);


	//SPI Init
	SPI_InitTypeDef  SPI_InitStructure; 
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4 ;
	
	//mode 0
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = 0;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b  ;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex ;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB ;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master ;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft ;

  SPI_Init(SPI1, &SPI_InitStructure);	                                      /* SPI1 初始化 */
  SPI_Cmd(SPI1, ENABLE);

}



uint8_t SPI_FLASH_ByteWrite(uint8_t data)
{
	uint8_t re_data;
	
	//等待TXE标志
	
  while(SPI_I2S_GetFlagStatus (SPI1, SPI_I2S_FLAG_TXE) == RESET );   
	
	SPI_I2S_SendData(SPI1, data);
	
	//等待RXNE标志 来确认发送完成，及准备读取数据
	while(SPI_I2S_GetFlagStatus (SPI1, SPI_I2S_FLAG_RXNE) == RESET );   
	
	re_data = SPI_I2S_ReceiveData(SPI1);
	return re_data;
}



uint8_t SPI_FLASH_Read_ID(void)
{
	uint8_t id;
	//控制片选引脚
	W25X128_Enable();
	
	//指令代码
	SPI_FLASH_ByteWrite(READ_ID_CMD);
	
	SPI_FLASH_ByteWrite(DUMMY);
	SPI_FLASH_ByteWrite(DUMMY);
	SPI_FLASH_ByteWrite(DUMMY);
	
	//接收读取到的内容
	id = SPI_FLASH_ByteWrite(DUMMY);
	W25X128_Disable();
	return id;

}

static uint8_t BSP_W25Qx_GetStatus(void)
{
	uint8_t status1;
	
	W25X128_Enable();
	SPI_FLASH_ByteWrite(READ_STATUS_REG1_CMD);
	status1=SPI_FLASH_ByteWrite(DUMMY);
	W25X128_Disable();
	
	if((status1 & W25Q128FV_FSR_BUSY) != 0)
  {
    return W25Qx_BUSY;
  }
	else
	{
		return W25Qx_OK;
	}	
	
	
}	



void W25X128_WaitForWriteEnd(void)
{
	while(BSP_W25Qx_GetStatus()==W25Qx_BUSY)
	{}
}


void W25X128_WriteEnable(void)
{
	W25X128_Enable();
	
	SPI_FLASH_ByteWrite(WRITE_ENABLE_CMD);
	
	W25X128_Disable();
	
	W25X128_WaitForWriteEnd();

}


void W25X128_WriteDisable(void)
{
	W25X128_Enable();
	
	SPI_FLASH_ByteWrite(WRITE_DISABLE_CMD);
	
	W25X128_Disable();
	
	W25X128_WaitForWriteEnd();
}


void W25X128_ChipErase(void)
{
	W25X128_WriteEnable();
	
	W25X128_Enable();
	SPI_FLASH_ByteWrite(CHIP_ERASE_CMD);
	W25X128_Disable();
	W25X128_WaitForWriteEnd();
	printf("Chip Erase finish.\r\n");
}



void W25X128_SectorErase(uint32_t flashAddr)
{
	
	
	uint8_t cmd[4]={0};
	
	cmd[0]=SECTOR_ERASE_CMD;
	cmd[1]=((flashAddr & 0xFF0000) >> 16);
	cmd[2]=((flashAddr & 0xFF00) >> 8);
	cmd[3]=(flashAddr & 0xFF);
	
	W25X128_WriteEnable();
	W25X128_Enable();
	SPI_FLASH_ByteWrite(cmd[0]);
	SPI_FLASH_ByteWrite(cmd[1]);
	SPI_FLASH_ByteWrite(cmd[2]);
	SPI_FLASH_ByteWrite(cmd[3]);
	W25X128_Disable();
	
	W25X128_WaitForWriteEnd();
	
}


void W25X128_BlockErase(uint8_t BlockNum)
{
	if(BlockNum>255)
		printf("BlockNum must be between 0 and 255. Please check it.");
	
	uint32_t flashAddr=0;
	
	flashAddr=BlockNum*(0x10000);
	
	W25X128_WriteEnable();
	
	uint8_t cmd[4]={0};
	
	cmd[0]=BLOCK_ERASE_CMD;
	cmd[1]=((flashAddr & 0xFF0000) >> 16);
	cmd[2]=((flashAddr & 0xFF00) >> 8);
	cmd[3]=(flashAddr & 0xFF);
	
	
	W25X128_Enable();
	SPI_FLASH_ByteWrite(cmd[0]);
	SPI_FLASH_ByteWrite(cmd[1]);
	SPI_FLASH_ByteWrite(cmd[2]);
	SPI_FLASH_ByteWrite(cmd[3]);
	W25X128_Disable();
	
	W25X128_WaitForWriteEnd();
	
}


void W25X128_BufferRead(uint8_t *pData, uint16_t length, uint32_t read_addr)
{
    uint8_t cmd[4];
    cmd[0] = READ_CMD;
    cmd[1] = ((read_addr & 0xFF0000) >> 16);
    cmd[2] = ((read_addr & 0xFF00) >> 8);
    cmd[3] = (read_addr & 0xFF);
		
		W25X128_WriteEnable();
		W25X128_Enable();
		SPI_FLASH_ByteWrite(cmd[0]);
		SPI_FLASH_ByteWrite(cmd[1]);
		SPI_FLASH_ByteWrite(cmd[2]);
		SPI_FLASH_ByteWrite(cmd[3]);
	
		for(int i=0;i<length;i++)
		{
			*pData=SPI_FLASH_ByteWrite(DUMMY);
			pData++;
		}
	
		
		W25X128_Disable();

    W25X128_WaitForWriteEnd();
	
		
}



void W25X128_PageWrite(uint8_t *pData, uint16_t length, uint32_t page_addr)
{
	if (length > 256) {
        printf("data length must be between 0 and 256. Please check it.");
        return;
    }
	uint8_t cmd[4]={0};
	
	cmd[0]=PAGE_PROG_CMD;
	cmd[1]=((page_addr & 0xFF0000) >> 16);
	cmd[2]=((page_addr & 0xFF00) >> 8);
	cmd[3]=(page_addr & 0xFF);	
		
	W25X128_WriteEnable();	
	W25X128_Enable();
	SPI_FLASH_ByteWrite(cmd[0]);
	SPI_FLASH_ByteWrite(cmd[1]);
	SPI_FLASH_ByteWrite(cmd[2]);
	SPI_FLASH_ByteWrite(cmd[3]);
	
	for(int i=0;i<length;i++)
	{
		SPI_FLASH_ByteWrite(*pData);
		pData++;
	}
		
	W25X128_Disable();	

	W25X128_WaitForWriteEnd();	
}


void W25X128_BufferWrite(uint8_t *pData, uint16_t data_length, uint32_t write_addr)
{
		uint8_t Num_of_Page = 0;
    uint8_t Num_of_Single = 0;
    uint8_t count = 0;      //lack count data, to align page address
    uint8_t Addr = 0;
    uint8_t temp = 0;
	
		Addr    = write_addr % W25Q128FV_PAGE_SIZE;
		count   = W25Q128FV_PAGE_SIZE - Addr;

		Num_of_Page = data_length / W25Q128FV_PAGE_SIZE;

    Num_of_Single = data_length % W25Q128FV_PAGE_SIZE;

	
		if (Addr == 0) {
        //data_length<Page Size
        if (Num_of_Page == 0)
            W25X128_PageWrite(pData, data_length, write_addr);
        else {      //data_length>Page Size
            while (Num_of_Page--) {
                W25X128_PageWrite(pData, W25Q128FV_PAGE_SIZE, write_addr);
                pData += W25Q128FV_PAGE_SIZE;
                write_addr += W25Q128FV_PAGE_SIZE;
            }
            W25X128_PageWrite(pData, Num_of_Single, write_addr);

        }

    }
		else {
        if (Num_of_Page == 0) {
            if (Num_of_Single > count) {
                temp = Num_of_Single - count;
                W25X128_PageWrite(pData, count, write_addr);
                pData += count;
                write_addr += count;

                W25X128_PageWrite(pData, temp, write_addr);
            } else {
                W25X128_PageWrite(pData, data_length, write_addr);
            }
        } else {
            data_length -= count;
            Num_of_Page = data_length / W25Q128FV_PAGE_SIZE;
            Num_of_Single = data_length % W25Q128FV_PAGE_SIZE;

            W25X128_PageWrite(pData, count, write_addr);
            write_addr += count;
            pData += count;

            while (Num_of_Page--) {
                W25X128_PageWrite(pData, W25Q128FV_PAGE_SIZE, write_addr);
                write_addr += W25Q128FV_PAGE_SIZE;
                pData += W25Q128FV_PAGE_SIZE;
            }

            if (Num_of_Single != 0) {
                W25X128_PageWrite(pData, Num_of_Single, write_addr);
            }

        }

    }


	

}

