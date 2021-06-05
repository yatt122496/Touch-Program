/***************************************************************************
*Copyright(c) 2018,深圳鹏林电子有限公司
*All rights reserved.
*
*文件名称：EEPROM.c
*摘    要：
*
*
*当前版本：V1.0
*作    者：yehuoyan
*完成日期：2019年7月18日10:48:20
*
*
*取代版本：
*作    者：
*完成日期：
******************************************************************************/
#include "EEPROM.h"
 
unsigned char idata ISP_RAM[32]; // IRAM 0Xe0 to 0Xff
unsigned char code  ISP_ROM[32]_at_ 0x1720; // IRAM 0Xe0 to 0Xff

void SYSIspStart(unsigned int pageAddress)
{
	ISP(pageAddress, ISP_RAM);
}

void ISP_RAM_INIT(void)
{
	u8 i;
	for(i=0; i<20; i++)
	{
		ISP_RAM[i] = ISP_ROM[i];
	}
}
