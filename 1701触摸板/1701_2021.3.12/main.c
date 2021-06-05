/***************************************************************************
*Copyright(c) 2019,深圳鹏林电子有限公司
*All rights reserved.
*
*硬    件：SN8F5703
*文件名称：main.c
*
*当前版本：V1.0
*作    者：yehuoyan
*完成日期：2019年8月17日13:41:10
*
*取代版本：
*作    者：
*完成日期：


******************************************************************************/

#include "Config.h"	
extern unsigned char idata ISP_RAM[16]; // IRAM 0Xe0 to 0Xff
extern unsigned char code  ISP_ROM[16]_at_ 0x1720; // IRAM 0Xe0 to 0Xff
extern u16 HeapTime;//濾網时间
extern u16 NCCOTime;//氧聚解反应层时间
extern u8 DangWeiTemp;

//系统时钟初始化Fosc/4
void SystemInit(void)
{
		CKCON = 0x70;
		CLKSEL = 0x07;				//Fcpu=Fosc/1
		CLKCMD = 0x69;
		CKCON = 0x00;
}



//--------------------------------------------------------------------------
//subroutine	: main()
//Function		: 
//--------------------------------------------------------------------------
u8 bKey = 0;
void main(void)
{
//	u8 temp;
	SystemInit();
	IO_Init();
	TM1668_Init();//TM1668初始化
	IIC_Init();
	Buz_Init();
	Timer_Init();
	PWM_Init();	
	BUZ_PWR_TONE();//开机声音	
	ISP_RAM_INIT();//EPPROM初始化
	DangWeiTemp = 3;//初始档位
	HeapTime = (u16)ISP_RAM[0] | (u16)(ISP_RAM[1]<<8);
	NCCOTime = (u16)ISP_RAM[2] | (u16)(ISP_RAM[3]<<8);    
	Delay_MS(1000);//1S
    IDLE();
	while(1)
	{
//		ScanKey();
//		bKey = ScanKey1();
//		Delay_MS(100);
		Normal_Mode();
		Test_Mode();
		RemoveALam();
//	writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示红灯		
		
//		Delay_MS(100);//1S
	}
	while(1);
}