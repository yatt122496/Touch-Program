#include "PWM.h"
#define PW1Inv1 (1 << 2) //PWM10/11/12 output inverse
#define PW1Inv2 (1 << 3) //PWM20/21/22 output inverse
#define PW1CMPTri (1 << 1) //PW1 output Control by Comparator trigger
#define PW1OnePu (1 << 0) //Enable PW1 pulse output function
#define PWM10En (1 << 0) //Enable PWM10 output function
#define PWM11En (2 << 0) //Enable PWM11 output function
#define PWM12En (4 << 0) //Enable PWM12 output function
#define PWM20En (1 << 4) //Enable PWM20 output function
#define PWM21En (2 << 4) //Enable PWM21 output function
#define PWM22En (4 << 4) //Enable PWM22 output function
#define PW1En (1 << 5) //Enable PWM1 output function


const unsigned char code  PWMValue[15] = {0,32,34,38,42,45,48,51,54,58,61,71};
/******************************************************************************
* ʱ    �䣺2019��8��19��17:52:02
* �������ƣ�void PWM_Init(void)
* �������ܣ�PWM��ʼ������
* ��    ע��    
* ��    �ģ���
 ********************************************************************************/

void PWM_Init(void)
{
	//PWM1_Initial
		PW1YH = 0x00;//��������
		PW1YL = 0x4b;
		PW1DH = 0x00;//����ռ�ձ�
		PW1DL = 0x00;
		PW1BH = 0x60;
		PW1BL = 0x00;
		PW1A = 0x80;
		//PW10/11/12/20/21/22 channel enable
		PW1CH = PWM11En;
		//PWM1 enable,P10/11/12 output inverse, clock = Fosc/32
//		PW1M = PWM10En | PWM21Inv1;
		PW1M |= 0xc0;
		// Enable PWM1 interrupt & clear PWM1F
		IEN4 |= 0x80;
		//Enable total interrupt
		IEN0 |= 0x80;

		P2 = 0x00;
		P2M |= 0x10;//����PWM11Ϊ���ģʽ

}

void SetMotorSpeed(u8 DangWei)
{
    u8 i;
    static u8  Last_DangWei = 0;
    
    if(DangWei > Last_DangWei)
    {
        for(i=Last_DangWei; i<=DangWei; i++)
        {
            PW1DH = 0x00;//����ռ�ձ�
            PW1DL = PWMValue[i];
        }
    }
    else 
    {
       PW1DH = 0x00;//����ռ�ձ�
       PW1DL = PWMValue[DangWei]; 
    }
    Last_DangWei = DangWei;
}

void PW1Interrupt(void) interrupt ISRPwm1 //0x83
{ //PWM1F clear by software
	if ((IEN4 & 0x08) == 0x08)
	{
		IEN4 &= 0Xf7; //Clear PWM1F
//		LED1 = !LED1;
	}
}

