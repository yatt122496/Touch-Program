/***************************************************************************
*Copyright(c) 2018,�������ֵ������޹�˾
*All rights reserved.
*
*�ļ����ƣ�EEPROM.c
*ժ    Ҫ��
*
*
*��ǰ�汾��V1.0
*��    �ߣ�yehuoyan
*������ڣ�2019��7��18��10:48:20
*
*
*ȡ���汾��
*��    �ߣ�
*������ڣ�
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
