#ifndef _PWM_C_
#define _PWM_C_

/*********************************************************************************************************************/
#include "../../includes/ca51f5sfr.h"
#include "../../includes/ca51f5xsfr.h"

#include "../../Library/includes/pwm.h"
#include <intrins.h>
/*********************************************************************************************************************/
/******************************************************************************
函数名：PWM0_init
功能描述：PWM0通道功能初始化
输入参数: ie				PWM0中断开关设置
					cks				PWM0时钟源设置
					toggle		PWM0是否反相输出设置
					Prescal		PWM0时钟分频设置				
返回值： 无					

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
函数名：PWM1_init
功能描述：PWM1通道功能初始化
输入参数: ie				PWM1中断开关设置
					cks				PWM1时钟源设置
					toggle		PWM1是否反相输出设置
					Prescal		PWM1时钟分频设置	
					pwmmod		pwmmod=0:PWM模式，pwmmod>0:级联LED驱动模式，同时pwmmod表示发送pwmmod个字节插入延时时间
返回值： 无					
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
函数名：PWM2_init
功能描述：PWM2通道功能初始化
输入参数: ie				PWM2中断开关设置
					cks				PWM2时钟源设置
					toggle		PWM2是否反相输出设置
					Prescal		PWM2时钟分频设置	
					pwmmod		pwmmod=0:PWM模式，pwmmod>0:级联LED驱动模式，同时pwmmod表示发送pwmmod个字节插入延时时间
返回值： 无					
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
函数名：PWM3_init
功能描述：PWM3通道功能初始化
输入参数: ie				PWM3中断开关设置
					cks				PWM3时钟源设置
					toggle		PWM3是否反相输出设置
					Prescal		PWM3时钟分频设置				
返回值： 无					

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
函数名：PWM4_init
功能描述：PWM4通道功能初始化
输入参数: ie				PWM4中断开关设置
					cks				PWM4时钟源设置
					toggle		PWM4是否反相输出设置
					Prescal		PWM4时钟分频设置				
返回值： 无					

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
函数名：PWM5_init
功能描述：PWM5通道功能初始化
输入参数: ie				PWM5中断开关设置
					cks				PWM5时钟源设置
					toggle		PWM5是否反相输出设置
					Prescal		PWM5时钟分频设置				
返回值： 无					

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
函数名：	PWM0_CfgDivDuty
功能描述：设置PWM0周期和占空比
输入参数: DIV				PWM周期设置
					DUT				PWM占空比设置
返回值：  无					
******************************************************************************/
void PWM0_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM0DIVH	= (unsigned char)(DIV>>8);
	PWM0DIVL	= (unsigned char)(DIV);
	PWM0DUTH	= (unsigned char)(DUT>>8);
	PWM0DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
函数名：	PWM1_CfgDivDuty
功能描述：设置PWM1周期和占空比
输入参数: DIV				PWM周期设置
					DUT				PWM占空比设置
返回值：  无					
******************************************************************************/
void PWM1_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM1DIVH	= (unsigned char)(DIV>>8);
	PWM1DIVL	= (unsigned char)(DIV);
	PWM1DUTH	= (unsigned char)(DUT>>8);
	PWM1DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
函数名：	PWM2_CfgDivDuty
功能描述：设置PWM2周期和占空比
输入参数: DIV				PWM周期设置
					DUT				PWM占空比设置
返回值：  无					
******************************************************************************/
void PWM2_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM2DIVH	= (unsigned char)(DIV>>8);
	PWM2DIVL	= (unsigned char)(DIV);
	PWM2DUTH	= (unsigned char)(DUT>>8);
	PWM2DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
函数名：	PWM3_CfgDivDuty
功能描述：设置PWM0周期和占空比
输入参数: DIV				PWM周期设置
					DUT				PWM占空比设置
返回值：  无					
******************************************************************************/
void PWM3_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM3DIVH	= (unsigned char)(DIV>>8);
	PWM3DIVL	= (unsigned char)(DIV);
	PWM3DUTH	= (unsigned char)(DUT>>8);
	PWM3DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
函数名：	PWM4_CfgDivDuty
功能描述：设置PWM4周期和占空比
输入参数: DIV				PWM周期设置
					DUT				PWM占空比设置
返回值：  无					
******************************************************************************/
void PWM4_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM4DIVH	= (unsigned char)(DIV>>8);
	PWM4DIVL	= (unsigned char)(DIV);
	PWM4DUTH	= (unsigned char)(DUT>>8);
	PWM4DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
函数名：	PWM5_CfgDivDuty
功能描述：设置PWM5周期和占空比
输入参数: DIV				PWM周期设置
					DUT				PWM占空比设置
返回值：  无					
******************************************************************************/
void PWM5_CfgDivDuty(unsigned int DIV,unsigned int DUT)
{
	PWM5DIVH	= (unsigned char)(DIV>>8);
	PWM5DIVL	= (unsigned char)(DIV);
	PWM5DUTH	= (unsigned char)(DUT>>8);
	PWM5DUTL	= (unsigned char)(DUT);	
}
/******************************************************************************
函数名：	PWM_CfgLedut
功能描述：PWM1/2为级联LED驱动模式时，设置发送位为1时PWM占空比
输入参数: Ledut				发送位为1时PWM占空比
返回值：  无					
******************************************************************************/
void PWM_CfgLedut(unsigned int Ledut)
{
	LEDUTH	= (unsigned char)(Ledut>>8);
	LEDUTL	= (unsigned char)(Ledut);	
}
/******************************************************************************
函数名：	PWM_CfgLedwtm
功能描述：PWM1/2为级联LED驱动模式时，设置延时时间
输入参数: Ledwtm				延时的PWM时钟周期数
返回值：  无					
******************************************************************************/
void PWM_CfgLedwtm(unsigned int Ledwtm)
{
	LEDWTMH	= (unsigned char)(Ledwtm>>8);
	LEDWTML	= (unsigned char)(Ledwtm);	
}
/******************************************************************************
函数名：	PWM1_WriteLedat
功能描述：PWM1为级联LED驱动模式时，发送1字节数据
输入参数: Ledat				待发送的数据
返回值：  无					
******************************************************************************/
void PWM1_WriteLedat(unsigned char Ledat)
{
	while(LEFLG & LEBSY0);
	LEDAT0 = Ledat;
}
/******************************************************************************
函数名：	PWM2_WriteLedat
功能描述：PWM2为级联LED驱动模式时，发送1字节数据
输入参数: Ledat				待发送的数据
返回值：  无					
******************************************************************************/
void PWM2_WriteLedat(unsigned char Ledat)
{
	while(LEFLG & LEBSY1);
	LEDAT1 = Ledat;
}
/******************************************************************************
函数名：	PWM_Enable
功能描述：PWM使能
输入参数: Pwmch	，使能的PWM通道
返回值：  无					
******************************************************************************/
void PWM_Enable(PWM_Channel_TypeDef Pwmch)
{
	PWMEN |= 1<<Pwmch;
}
/******************************************************************************
函数名：	PWM_Disable
功能描述：PWM禁能
输入参数: Pwmch	，禁能的PWM通道
返回值：  无					
******************************************************************************/
void PWM_Disable(PWM_Channel_TypeDef Pwmch)
{
	PWMEN &= ~(1<<Pwmch);
}
#endif