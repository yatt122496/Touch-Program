#ifndef __I2C_C_
#define __I2C_C_

/*********************************************************************************************************************/
#include "ca51f5_config.h"
#include "includes\ca51f5sfr.h"
#include "includes\ca51f5xsfr.h"
#include "includes\gpiodef_f5.h"
#include "includes\system.h"
#include "Library\includes\uart.h"
#include "Library\Includes\tmc.h"	

#include <intrins.h>

#include "includes/i2c.h"
#include "includes/led.h"
/*********************************************************************************************************************/

/*********************************************************************************************************************/
//  ������ΪI2C�����ӻ�ͨ�ŵĴӻ�����
//   ____________            _____________
//  |            |   SDA    |             |
//  |            |<-------->|             |
//  |            |          |             |
//  |  CA51F5(M) |          | CA51F5(S)   |
//  |(I2C_Master)|          | (I2C_Slave) |
//  |            |   SCL    |             |
//  |            |--------->|             |
//  |____________|          |_____________|
//
#if DEBUG == 0
/*********************************************************************************************************************/
#define I2C_ADDR		0x54		//����I2C�ӻ���ַ
/*********************************************************************************************************************/
unsigned char I2CDataIndex = 0;
unsigned char regAddr = 0;
bit iicReadMode;
unsigned char read_Buffer[10]={0,0,0};//�������ݼĴ�����ֵΪ0~19
unsigned char write_Buffer[10]={0,1,2};//�������ݼĴ�����ֵΪ0~19

void I2C_ISR(void) interrupt 6
{
	unsigned char Sta_Temp;

	if(I2CFLG & I2CF)					 			//IIC  interrupt
	{
		Sta_Temp = I2CSTA;
//		#ifdef UART0_EN
//		Uart0_PutChar(Sta_Temp);
//		#endif
		if(Sta_Temp == 0x60) {			    //���յ��ӻ���ַ+дλ
			I2CDataIndex = 0;				//����Ϊ0xFF��ʾ������յ��ĵ�һ���ֽ�Ϊ��ַ
			regAddr = 0;
			iicReadMode = 0;						//����Ϊ�ӻ�����״̬
			I2CCON |= AAK(1);
		} else if(Sta_Temp == 0x80) {			//���ͻ����һ�ֽ����ݣ��Ѽ�⵽Ӧ���ź�
//		#ifdef UART0_EN
//			Uart0_PutChar(I2CDAT);
//		#endif
			if(iicReadMode) {	 						//����һ�ֽ�����
//				I2CDataIndex++;
//				if ((I2CDataIndex) > 2) {
//					I2CDataIndex = 0;
//				}
				I2CDAT = read_Buffer[0];			//������װ�ص����ͼĴ������ȴ�������ȡ
//				Uart0_PutChar(read_Buffer[I2CDataIndex]);
			} else {										//���յ�һ�ֽ�����
				if(I2CDataIndex == 0xFF) { 	//��ַ
					regAddr = I2CDAT;	 					//���յ��ĵ�һ���ֽ���Ϊ�ǵ�ַ
					if (regAddr > 19) {
						regAddr = 0;
					}
			   		I2CDataIndex = 0;																	//��������ֵΪ0
					I2CCON |= AAK(1);
				} else {				   						//����
					write_Buffer[I2CDataIndex + regAddr] = I2CDAT;		//���յ�������װ�ص����ݼĴ���
//					Uart0_PutChar(write_Buffer[I2CDataIndex + regAddr]);
					I2CDataIndex++;									//����ֵ�ۼ�
					I2CCON |= AAK(1);
					if ((I2CDataIndex + regAddr) > 19) {
						I2CDataIndex--;
					} else if (I2CDataIndex == 3) {
						Sta_Temp = write_Buffer[0];
					}
				}
			}
		} else if(Sta_Temp==0xA8) {				//���յ��ӻ���ַ+��λ������ACK�ź�
//			regAddr = 0;
//			I2CDataIndex = 0;
			I2CDAT = read_Buffer[0];		//������װ�ص����ͼĴ������ȴ�������ȡ
//			Uart0_PutChar(read_Buffer[I2CDataIndex + regAddr]);
			iicReadMode = 1;						//����Ϊ�ӻ�����״̬
		} else if(Sta_Temp == 0x88) {			//���ͻ����һ�ֽ����ݣ��޼�⵽Ӧ���ź�
//			I2CDataIndex++;
//				if ((I2CDataIndex) > 2) {
//					I2CDataIndex = 0;
//				}
				I2CDAT = read_Buffer[0];			//������װ�ص����ͼĴ������ȴ�������ȡ
//				Uart0_PutChar(read_Buffer[I2CDataIndex]);
		}
		I2CFLG  |= I2CF;					//����жϱ�־
	}
}

void i2c_init(void)
{
	/**********ѡ��I2C�˿�************************************************************/
// 	I2CIOS = 0;
// 	P30F = P30_I2C_SDA_SETTING | PU_EN;
// 	P31F = P31_I2C_SCL_SETTING | PU_EN;

	I2CIOS = 1;
	P03F = P03_I2C_SDA_SETTING | OP_EN;
	P02F = P02_I2C_SCL_SETTING | OP_EN;

//��������˿ڶ�ѡһ
/***************************************************************************************/

	I2CCON |= AAK(1);
	I2CCON = I2CE(1) | I2CIE(1) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(0);
	I2CADR = GCE(0)|(I2C_ADDR>>1);		//����I2C�ӻ���ַ
//	I2CADM = 0x80; 
	I2CCR = 0x20;										//����I2Cʱ�Ӳ���ʱ��
	INT4EN = 1;	 											//I2C�жϿ���
}
#endif
#endif
