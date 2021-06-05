#ifndef _PWM_C_
#define _PWM_C_

/*********************************************************************************************************************/
#include "../../includes/ca51f5sfr.h"
#include "../../includes/ca51f5xsfr.h"

#include "../../Library/includes/pwm.h"
#include <intrins.h>
/*********************************************************************************************************************/
/******************************************************************************
��������PWM0_init
����������PWM0ͨ�����ܳ�ʼ��
�������: ie				PWM0�жϿ�������
					cks				PWM0ʱ��Դ����
					toggle		PWM0�Ƿ����������
					Prescal		PWM0ʱ�ӷ�Ƶ����				
����ֵ�� ��					

******************************************************************************/
void PWM0_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal)
{
		PWM0CON = PWMIE(ie) | PWMTOG(toggle) | cks;
		PWM0CKD = Prescal;
}
/******************************************************************************
��������PWM1_init
����������PWM1ͨ�����ܳ�ʼ��
�������: ie				PWM1�жϿ�������
					cks				PWM1ʱ��Դ����
					toggle		PWM1�Ƿ����������
					Prescal		PWM1ʱ�ӷ�Ƶ����	
					pwmmod		pwmmod=0:PWMģʽ��pwmmod>0:����LED����ģʽ��ͬʱpwmmod��ʾ����pwmmod���ֽڲ�����ʱʱ��
����ֵ�� ��					
******************************************************************************/
void PWM1_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal,
								unsigned char pwmmod)
{
		PWM1CON = PWMIE(ie) | PWMTOG(toggle) | PWMMOD(pwmmod) | PWMPOL(0) | cks;
		PWM1CKD = Prescal;
}
/******************************************************************************
��������PWM2_init
����������PWM2ͨ�����ܳ�ʼ��
�������: ie				PWM2�жϿ�������
					cks				PWM2ʱ��Դ����
					toggle		PWM2�Ƿ����������
					Prescal		PWM2ʱ�ӷ�Ƶ����	
					pwmmod		pwmmod=0:PWMģʽ��pwmmod>0:����LED����ģʽ��ͬʱpwmmod��ʾ����pwmmod���ֽڲ�����ʱʱ��
����ֵ�� ��					
******************************************************************************/
void PWM2_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal,
								unsigned char pwmmod)
{
		PWM2CON = PWMIE(ie) | PWMTOG(toggle) | PWMMOD(pwmmod) | PWMPOL(0) | cks;
		PWM2CKD = Prescal;
}
/******************************************************************************
��������PWM3_init
����������PWM3ͨ�����ܳ�ʼ��
�������: ie				PWM3�жϿ�������
					cks				PWM3ʱ��Դ����
					toggle		PWM3�Ƿ����������
					Prescal		PWM3ʱ�ӷ�Ƶ����				
����ֵ�� ��					

******************************************************************************/
void PWM3_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal)
{
		PWM3CON = PWMIE(ie) | PWMTOG(toggle) | cks;
		PWM3CKD = Prescal;
}
/******************************************************************************
��������PWM4_init
����������PWM4ͨ�����ܳ�ʼ��
�������: ie				PWM4�жϿ�������
					cks				PWM4ʱ��Դ����
					toggle		PWM4�Ƿ����������
					Prescal		PWM4ʱ�ӷ�Ƶ����				
����ֵ�� ��					

******************************************************************************/
void PWM4_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal)
{
		PWM4CON = PWMIE(ie) | PWMTOG(toggle) | cks;
		PWM4CKD = Prescal;
}
/******************************************************************************
��������PWM5_init
����������PWM5ͨ�����ܳ�ʼ��
�������: ie				PWM5�жϿ�������
					cks				PWM5ʱ��Դ����
					toggle		PWM5�Ƿ����������
					Prescal		PWM5ʱ�ӷ�Ƶ����				
����ֵ�� ��					

******************************************************************************/
void PWM5_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal)
{
		PWM5CON = PWMIE(ie) | PWMTOG(toggle) | cks;
		PWM5CKD = Prescal;
}
/******************************************************************************
��������	PWM0_CfgDivDuty
��������������PWM0���ں�ռ�ձ�
�������: DIV				PWM��������
					DUT				PWMռ�ձ�����
����ֵ��  ��					
******************************************************************************/
void PWM0_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM0DIVH	= (unsigned char)(DIV>>8);
	PWM0DIVL	= (unsigned char)(DIV);
	PWM0DUTH	= (unsigned char)(DUT>>8);
	PWM0DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
��������	PWM1_CfgDivDuty
��������������PWM1���ں�ռ�ձ�
�������: DIV				PWM��������
					DUT				PWMռ�ձ�����
����ֵ��  ��					
******************************************************************************/
void PWM1_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM1DIVH	= (unsigned char)(DIV>>8);
	PWM1DIVL	= (unsigned char)(DIV);
	PWM1DUTH	= (unsigned char)(DUT>>8);
	PWM1DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
��������	PWM2_CfgDivDuty
��������������PWM2���ں�ռ�ձ�
�������: DIV				PWM��������
					DUT				PWMռ�ձ�����
����ֵ��  ��					
******************************************************************************/
void PWM2_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM2DIVH	= (unsigned char)(DIV>>8);
	PWM2DIVL	= (unsigned char)(DIV);
	PWM2DUTH	= (unsigned char)(DUT>>8);
	PWM2DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
��������	PWM3_CfgDivDuty
��������������PWM0���ں�ռ�ձ�
�������: DIV				PWM��������
					DUT				PWMռ�ձ�����
����ֵ��  ��					
******************************************************************************/
void PWM3_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM3DIVH	= (unsigned char)(DIV>>8);
	PWM3DIVL	= (unsigned char)(DIV);
	PWM3DUTH	= (unsigned char)(DUT>>8);
	PWM3DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
��������	PWM4_CfgDivDuty
��������������PWM4���ں�ռ�ձ�
�������: DIV				PWM��������
					DUT				PWMռ�ձ�����
����ֵ��  ��					
******************************************************************************/
void PWM4_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM4DIVH	= (unsigned char)(DIV>>8);
	PWM4DIVL	= (unsigned char)(DIV);
	PWM4DUTH	= (unsigned char)(DUT>>8);
	PWM4DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
��������	PWM5_CfgDivDuty
��������������PWM5���ں�ռ�ձ�
�������: DIV				PWM��������
					DUT				PWMռ�ձ�����
����ֵ��  ��					
******************************************************************************/
void PWM5_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM5DIVH	= (unsigned char)(DIV>>8);
	PWM5DIVL	= (unsigned char)(DIV);
	PWM5DUTH	= (unsigned char)(DUT>>8);
	PWM5DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
��������	PWM_CfgLedut
����������PWM1/2Ϊ����LED����ģʽʱ�����÷���λΪ1ʱPWMռ�ձ�
�������: Ledut				����λΪ1ʱPWMռ�ձ�
����ֵ��  ��					
******************************************************************************/
void PWM_CfgLedut(unsigned int Ledut)
{
	LEDUTH	= (unsigned char)(Ledut>>8);
	LEDUTL	= (unsigned char)(Ledut);	
}
/******************************************************************************
��������	PWM_CfgLedwtm
����������PWM1/2Ϊ����LED����ģʽʱ��������ʱʱ��
�������: Ledwtm				��ʱ��PWMʱ��������
����ֵ��  ��					
******************************************************************************/
void PWM_CfgLedwtm(unsigned int Ledwtm)
{
	LEDWTMH	= (unsigned char)(Ledwtm>>8);
	LEDWTML	= (unsigned char)(Ledwtm);	
}
/******************************************************************************
��������	PWM1_WriteLedat
����������PWM1Ϊ����LED����ģʽʱ������1�ֽ�����
�������: Ledat				�����͵�����
����ֵ��  ��					
******************************************************************************/
void PWM1_WriteLedat(unsigned char Ledat)
{
	while(LEFLG & LEBSY0);
	LEDAT0 = Ledat;
}
/******************************************************************************
��������	PWM2_WriteLedat
����������PWM2Ϊ����LED����ģʽʱ������1�ֽ�����
�������: Ledat				�����͵�����
����ֵ��  ��					
******************************************************************************/
void PWM2_WriteLedat(unsigned char Ledat)
{
	while(LEFLG & LEBSY1);
	LEDAT1 = Ledat;
}
/******************************************************************************
��������	PWM_Enable
����������PWMʹ��
�������: Pwmch	��ʹ�ܵ�PWMͨ��
����ֵ��  ��					
******************************************************************************/
void PWM_Enable(PWM_Channel_TypeDef Pwmch)
{
	PWMEN |= 1<<Pwmch;
}
/******************************************************************************
��������	PWM_Disable
����������PWM����
�������: Pwmch	�����ܵ�PWMͨ��
����ֵ��  ��					
******************************************************************************/
void PWM_Disable(PWM_Channel_TypeDef Pwmch)
{
	PWMEN &= ~(1<<Pwmch);
}
#endif