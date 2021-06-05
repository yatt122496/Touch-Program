/***************************************************************************
*Copyright(c) 2019,�������ֵ������޹�˾
*All rights reserved.
*
*Ӳ    ����SN8F5703
*�ļ����ƣ�main.c
*
*��ǰ�汾��V1.0
*��    �ߣ�yehuoyan
*������ڣ�2019��8��17��13:41:10
*
*ȡ���汾��
*��    �ߣ�
*������ڣ�


******************************************************************************/

#include "Config.h"	
extern unsigned char idata ISP_RAM[16]; // IRAM 0Xe0 to 0Xff
extern unsigned char code  ISP_ROM[16]_at_ 0x1720; // IRAM 0Xe0 to 0Xff
extern u16 HeapTime;//�V�Wʱ��
extern u16 NCCOTime;//���۽ⷴӦ��ʱ��
extern u8 DangWeiTemp;

//ϵͳʱ�ӳ�ʼ��Fosc/4
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
	TM1668_Init();//TM1668��ʼ��
	IIC_Init();
	Buz_Init();
	Timer_Init();
	PWM_Init();	
	BUZ_PWR_TONE();//��������	
	ISP_RAM_INIT();//EPPROM��ʼ��
	DangWeiTemp = 3;//��ʼ��λ
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
//	writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ���		
		
//		Delay_MS(100);//1S
	}
	while(1);
}