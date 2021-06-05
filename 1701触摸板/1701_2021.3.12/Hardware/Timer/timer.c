/***************************************************************************
*Copyright(c) 2018,深圳鹏林电子有限公司
*All rights reserved.
*
*文件名称：timer.c
*摘    要：
*
*
*当前版本：V1.0
*作    者：yehuoyan
*完成日期：2018年6月8日17:08:06
*
*
*取代版本：
*作    者：yehuoyan
*完成日期：
******************************************************************************/
#include "timer.h"
u16 HeapTime;//濾網时间
u16 NCCOTime;//氧聚解反应层时间
u16 EEPROMWriteTime;//
u16 HH,MM,SS;//时分秒
u16 T0Count,T1Count;
extern bit POWKEY_Flag;
extern bit Test_Flag;
extern bit Alam_Flag;
extern u8 Times3S ;
extern u8 Times10S ;
extern u8 DangWeiTemp;
extern u8 PWR_ON_OFF_Times;
extern bit PWR_ON_OFF_Flag;
extern bit FirstStart_Flag;
bit AOG_Flag;
bit Sleep_Flag;
bit TestMode10S_Flag;
bit Alam10S_Flag;
bit IDLE_flag;
extern bit ECOKEY_Flag;//ECO按键标志
extern bit K6_Flag;//K6按键标志
extern unsigned char idata ISP_RAM[16]; // IRAM 0Xe0 to 0Xff
extern unsigned char code  ISP_ROM[16]_at_ 0x1720; // IRAM 0Xe0 to 0Xff
/******************************************************************************
* 时    间：2018年6月8日17:00:15
* 函数名称：void Timer0_Init(void)
* 函数功能：定时器0,1初始化函数
* 备    注：    
* 修    改：无
 ********************************************************************************/
void Timer_Init(void)
{
	TR0  = 0;//启动定时器0
	TR1  = 0;//启动定时器1

	TMOD = 0x11;//定时器0,1，16位向上计数模式
	TH0  = (65536-50000) / 256;
	TL0  = (65536-50000) % 256;
	TH1  = (65536-50000) / 256;
	TL1  = (65536-50000) % 256;
	ET0  = 1;//允许定时器0溢出中断
	ET1  = 1;//允许定时器0溢出中断
	EAL   = 1;//允许所有中断
}
/******************************************************************************
* 时    间：2018年6月8日17:00:15
* 函数名称：void timer0_ISR(void) interrupt 1
* 函数功能：定时器0中断服务函数
* 备    注：50ms中断 
* 修    改：无
 ********************************************************************************/
void timer0_ISR(void) interrupt 1
{
	TR0  = 0;//关闭定时器
	TH0  = (65536-50000) / 256;
	TL0  = (65536-50000) % 256;
	T0Count++;
	Times3S++;//
  Times10S++;
    
	if(FirstStart_Flag && POWKEY_Flag && !FILTER_DET)
	{
			if(Times10S >= 150  && !PWR_ON_OFF_Flag)
			{ 
					Times10S = 0;
					FirstStart_Flag = 0;
					if(ECOKEY_Flag)
					{
						SetMotorSpeed(3);//风机3挡
					}
					else if(K6_Flag)
					{
						 SetMotorSpeed(DangWeiTemp);//疾风模式  
					}
					else
					{
							SetMotorSpeed(DangWeiTemp);
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
					}         
			}
	}
	if(Times3S >= 60)//3S时间计时
	{
		PWR_ON_OFF_Times = 0;
	}
	if(Times3S >= 200 && PWR_ON_OFF_Flag)//10S后开机
	{									
		Times3S = 0;
		PWR_ON_OFF_Flag =0;
		PWR_ON_OFF_Times = 0;
		SetMotorSpeed(DangWeiTemp);						
	}
	if(FILTER_DET && POWKEY_Flag)//没有检测到滤网执行 RB闪烁
	{
		if(T0Count <= 20)
		{
			writeTM1668_data(10,10,1,0,2,2,2);
		}
		else 
		{
			writeTM1668_data(17,17,1,0,1,1,1);  
		}
		if(T0Count >= 40 )
		{
			T0Count = 0;			
		}
	}
	if(T0Count >= 1200 && POWKEY_Flag && !Alam_Flag)//60秒后所有指示灯熄灭 
	{
		IDLE_flag = 1;
		writeTM1668_data(17,17,0,0,0,0,0);
	}
	if(T0Count >= 200 && Test_Flag && !POWKEY_Flag)//测试模式10s计时
	{
		TestMode10S_Flag = 1;
		T0Count = 0;
		TR0  = 0;//关闭定时器
	}
	if(T0Count >= 200  && !POWKEY_Flag)//报警10s计时
	{
		Alam10S_Flag = 1;
	}	
//		LED0 = !LED0;

	TR0  = 1;//启动定时器
}
/******************************************************************************
* 时    间：2018年6月8日17:00:15
* 函数名称：void timer1_ISR(void) interrupt 3
* 函数功能：定时器0中断服务函数
* 备    注：50ms中断 
* 修    改：无
 ********************************************************************************/
#if 1
void Timer1_ISR(void) interrupt	3
{
//	TR1  = 0;//关闭定时器
	TH1  = (65536-50000) / 256;
	TL1  = (65536-50000) % 256;
	T1Count++;	
	SS++;
//EEPROM写入时间30分钟	
	EEPROMWriteTime++;

	if(35550 == EEPROMWriteTime) //30分钟计时到
	{
		EEPROMWriteTime = 0;
		HeapTime++;//濾網时间,半小时自加一次
		NCCOTime++;//氧聚解反应层时间,半小时自加一次
		ISP_RAM[0] = (u8)(HeapTime & 0x00ff);// HeapTime时间低8位写入EEPROM
		ISP_RAM[1] = (u8)(HeapTime >> 8);//HeapTime时间高8位写入EEPROM
		ISP_RAM[2] = (u8)(NCCOTime & 0x00ff);// NCCOTime时间低8位写入EEPROM
		ISP_RAM[3] = (u8)(NCCOTime >> 8);//NCCOTime时间高8位写入EEPROM
		SYSIspStart(0x1720);			
	}
	//AOG模式
	if(35500 == T1Count && !FILTER_DET && !Sleep_Flag) //30分钟计时到
	{
		T1Count = 0;	
		AOG_Flag = 1;
		AOG_CTL = 1;//打开AOG
	}
	if(AOG_Flag)
	{
		if(200 == T1Count)//10s
		{
			AOG_CTL = 0;
		}
		if(1800 == T1Count)//80s
		{
			T1Count = 0;
			AOG_CTL = 1;
		}
	}
//休眠模式	
	if(1190== SS && !FILTER_DET)//1分钟
	{        
		SS = 0;
		MM++;
		if(59 == MM && !Sleep_Flag)//1小时
		{
			MM = 0;
			HH++;						
			if(8 == HH) //开机8小时
			{
				MM = 0;
				SS = 0;
				HH = 0;
				Sleep_Flag = !Sleep_Flag;
				writeTM1668_data(17,17,0,0,0,0,0);//所有指示灯熄灭 
				SetMotorSpeed(0);//风机停止
				AOG_Flag = 0;
				AOG_CTL = 0;//开启AOG
			}
		}
		if((30 == MM) && Sleep_Flag)//休息30分钟
		{
//            AOG_Flag = 1;
//            AOG_CTL = 1;//开启AOG
			T1Count = 0;
			SS = 0;
			MM = 0;
			HH = 0;
			Sleep_Flag = !Sleep_Flag;
			SetMotorSpeed(DangWeiTemp);//设置风机挡位开启风机
		}		
	}
	TR1  = 1;//启动定时器
}
#endif







