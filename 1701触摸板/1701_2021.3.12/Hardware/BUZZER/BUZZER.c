/***************************************************************************
*Copyright(c) 2018,深圳鹏林电子有限公司
*All rights reserved.
*
*文件名称：BUZZER.c
*摘    要：
*
*
*当前版本：V1.0
*作    者：yehuoyan
*完成日期：2018年6月8日17:08:06
*
*
*取代版本：
*作    者：
*完成日期：
******************************************************************************/
#include "BUZZER.h"

void Buz_Init(void)
{
		
		P2UR = 0X00;
		P2 = 0X00;
		P2M |= 0X0e;//设置ERR_TONE KEY_TONE PWR_TONE为输出模式
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








