/***************************************************************************
*Copyright(c) 2018,�������ֵ������޹�˾
*All rights reserved.
*
*�ļ����ƣ�timer.c
*ժ    Ҫ��
*
*
*��ǰ�汾��V1.0
*��    �ߣ�yehuoyan
*������ڣ�2018��6��8��17:08:06
*
*
*ȡ���汾��
*��    �ߣ�yehuoyan
*������ڣ�
******************************************************************************/
#include "timer.h"
u16 HeapTime;//�V�Wʱ��
u16 NCCOTime;//���۽ⷴӦ��ʱ��
u16 EEPROMWriteTime;//
u16 HH,MM,SS;//ʱ����
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
extern bit ECOKEY_Flag;//ECO������־
extern bit K6_Flag;//K6������־
extern unsigned char idata ISP_RAM[16]; // IRAM 0Xe0 to 0Xff
extern unsigned char code  ISP_ROM[16]_at_ 0x1720; // IRAM 0Xe0 to 0Xff
/******************************************************************************
* ʱ    �䣺2018��6��8��17:00:15
* �������ƣ�void Timer0_Init(void)
* �������ܣ���ʱ��0,1��ʼ������
* ��    ע��    
* ��    �ģ���
 ********************************************************************************/
void Timer_Init(void)
{
	TR0  = 0;//������ʱ��0
	TR1  = 0;//������ʱ��1

	TMOD = 0x11;//��ʱ��0,1��16λ���ϼ���ģʽ
	TH0  = (65536-50000) / 256;
	TL0  = (65536-50000) % 256;
	TH1  = (65536-50000) / 256;
	TL1  = (65536-50000) % 256;
	ET0  = 1;//����ʱ��0����ж�
	ET1  = 1;//����ʱ��0����ж�
	EAL   = 1;//���������ж�
}
/******************************************************************************
* ʱ    �䣺2018��6��8��17:00:15
* �������ƣ�void timer0_ISR(void) interrupt 1
* �������ܣ���ʱ��0�жϷ�����
* ��    ע��50ms�ж� 
* ��    �ģ���
 ********************************************************************************/
void timer0_ISR(void) interrupt 1
{
	TR0  = 0;//�رն�ʱ��
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
						SetMotorSpeed(3);//���3��
					}
					else if(K6_Flag)
					{
						 SetMotorSpeed(DangWeiTemp);//����ģʽ  
					}
					else
					{
							SetMotorSpeed(DangWeiTemp);
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ01��
					}         
			}
	}
	if(Times3S >= 60)//3Sʱ���ʱ
	{
		PWR_ON_OFF_Times = 0;
	}
	if(Times3S >= 200 && PWR_ON_OFF_Flag)//10S�󿪻�
	{									
		Times3S = 0;
		PWR_ON_OFF_Flag =0;
		PWR_ON_OFF_Times = 0;
		SetMotorSpeed(DangWeiTemp);						
	}
	if(FILTER_DET && POWKEY_Flag)//û�м�⵽����ִ�� RB��˸
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
	if(T0Count >= 1200 && POWKEY_Flag && !Alam_Flag)//60�������ָʾ��Ϩ�� 
	{
		IDLE_flag = 1;
		writeTM1668_data(17,17,0,0,0,0,0);
	}
	if(T0Count >= 200 && Test_Flag && !POWKEY_Flag)//����ģʽ10s��ʱ
	{
		TestMode10S_Flag = 1;
		T0Count = 0;
		TR0  = 0;//�رն�ʱ��
	}
	if(T0Count >= 200  && !POWKEY_Flag)//����10s��ʱ
	{
		Alam10S_Flag = 1;
	}	
//		LED0 = !LED0;

	TR0  = 1;//������ʱ��
}
/******************************************************************************
* ʱ    �䣺2018��6��8��17:00:15
* �������ƣ�void timer1_ISR(void) interrupt 3
* �������ܣ���ʱ��0�жϷ�����
* ��    ע��50ms�ж� 
* ��    �ģ���
 ********************************************************************************/
#if 1
void Timer1_ISR(void) interrupt	3
{
//	TR1  = 0;//�رն�ʱ��
	TH1  = (65536-50000) / 256;
	TL1  = (65536-50000) % 256;
	T1Count++;	
	SS++;
//EEPROMд��ʱ��30����	
	EEPROMWriteTime++;

	if(35550 == EEPROMWriteTime) //30���Ӽ�ʱ��
	{
		EEPROMWriteTime = 0;
		HeapTime++;//�V�Wʱ��,��Сʱ�Լ�һ��
		NCCOTime++;//���۽ⷴӦ��ʱ��,��Сʱ�Լ�һ��
		ISP_RAM[0] = (u8)(HeapTime & 0x00ff);// HeapTimeʱ���8λд��EEPROM
		ISP_RAM[1] = (u8)(HeapTime >> 8);//HeapTimeʱ���8λд��EEPROM
		ISP_RAM[2] = (u8)(NCCOTime & 0x00ff);// NCCOTimeʱ���8λд��EEPROM
		ISP_RAM[3] = (u8)(NCCOTime >> 8);//NCCOTimeʱ���8λд��EEPROM
		SYSIspStart(0x1720);			
	}
	//AOGģʽ
	if(35500 == T1Count && !FILTER_DET && !Sleep_Flag) //30���Ӽ�ʱ��
	{
		T1Count = 0;	
		AOG_Flag = 1;
		AOG_CTL = 1;//��AOG
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
//����ģʽ	
	if(1190== SS && !FILTER_DET)//1����
	{        
		SS = 0;
		MM++;
		if(59 == MM && !Sleep_Flag)//1Сʱ
		{
			MM = 0;
			HH++;						
			if(8 == HH) //����8Сʱ
			{
				MM = 0;
				SS = 0;
				HH = 0;
				Sleep_Flag = !Sleep_Flag;
				writeTM1668_data(17,17,0,0,0,0,0);//����ָʾ��Ϩ�� 
				SetMotorSpeed(0);//���ֹͣ
				AOG_Flag = 0;
				AOG_CTL = 0;//����AOG
			}
		}
		if((30 == MM) && Sleep_Flag)//��Ϣ30����
		{
//            AOG_Flag = 1;
//            AOG_CTL = 1;//����AOG
			T1Count = 0;
			SS = 0;
			MM = 0;
			HH = 0;
			Sleep_Flag = !Sleep_Flag;
			SetMotorSpeed(DangWeiTemp);//���÷����λ�������
		}		
	}
	TR1  = 1;//������ʱ��
}
#endif







