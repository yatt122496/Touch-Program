/***************************************************************************
*Copyright(c) 2018,�������ֵ������޹�˾
*All rights reserved.
*
*�ļ����ƣ�BUZZER.c
*ժ    Ҫ��
*
*
*��ǰ�汾��V1.0
*��    �ߣ�yehuoyan
*������ڣ�2018��6��8��17:08:06
*
*
*ȡ���汾��
*��    �ߣ�
*������ڣ�
******************************************************************************/
#include "BUZZER.h"

void Buz_Init(void)
{
		
		P2UR = 0X00;
		P2 = 0X00;
		P2M |= 0X0e;//����ERR_TONE KEY_TONE PWR_TONEΪ���ģʽ
}


void BUZ_PWR_TONE(void)
{
	PWR_TONE = 1;
	Delay_MS(50);
	PWR_TONE = 0;

}

void BUZ_KEY_TONE(void)
{
	KEY_TONE = 1;
	Delay_MS(20);
	KEY_TONE = 0;

}

void BUZ_ERR_TONE(void)
{
	ERR_TONE = 1;
	Delay_MS(20);
	ERR_TONE = 0;

}








