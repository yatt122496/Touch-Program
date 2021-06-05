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
//  本例程为I2C主机从机通信的从机程序。
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
/*********************************************************************************************************************/
#define I2C_ADDR		0xAA		//定义I2C从机地址
/*********************************************************************************************************************/
unsigned char I2CDataIndex;
unsigned char regAddr;
bit iicReadMode;
unsigned char read_Buffer[10]={0,0xff,0xa5};//设置数据寄存器初值为0~19
unsigned char write_Buffer[10]={0,1,2};//设置数据寄存器初值为0~19

void I2C_ISR(void) interrupt 6
{
	unsigned char Sta_Temp;

	if(I2CFLG & I2CF)					 			//IIC  interrupt
	{
		Sta_Temp = I2CSTA;
//		Uart0_PutChar(Sta_Temp);
		if(Sta_Temp == 0x60) {			    //接收到从机地址+写位
			I2CDataIndex = 0;				//设置为0xFF表示后面接收到的第一个字节为地址
			regAddr = 0;
			iicReadMode = 0;						//设置为从机接收状态
			I2CCON |= AAK(1);
		} else if(Sta_Temp == 0x80) {			//发送或接收一字节数据，已检测到应答信号
			if(iicReadMode) {	 						//发送一字节数据
				I2CDataIndex++;
				if ((I2CDataIndex + regAddr) > 9) {
					I2CDataIndex--;
				}
				I2CDAT = read_Buffer[I2CDataIndex + regAddr];			//把数据装载到发送寄存器，等待主机读取
			} else {												//接收到一字节数据
				if(I2CDataIndex == 0xFF) { 	//地址
					regAddr = I2CDAT;	 					//接收到的第一个字节认为是地址
					if (regAddr > 19) {
						regAddr = 0;
					}
			   		I2CDataIndex = 0;																	//设置索引值为0
					I2CCON |= AAK(1);
				} else {				   						//数据
					write_Buffer[I2CDataIndex + regAddr] = I2CDAT;		//接收到的数据装载到数据寄存器
//					Uart0_PutChar(write_Buffer[I2CDataIndex + regAddr]);
					I2CDataIndex++;									//索引值累加
					I2CCON |= AAK(1);
					if ((I2CDataIndex + regAddr) > 19) {
						I2CDataIndex--;
					} else if (I2CDataIndex == 3) {
						Sta_Temp = write_Buffer[0];
						if ((Sta_Temp == (unsigned char)~write_Buffer[1]) && (write_Buffer[2] == 0x5a)) {
							switch (Sta_Temp) {
							case 0:
								LED_HEATER = 1;
								LED_OFF0 = 1;
								LED_HIGH = 1;
								LED_LOW = 1;
								break;
							case 1:
								LED_HEATER = 0;
								LED_OFF0 = 1;
								LED_HIGH = 1;
								LED_LOW = 1;
								break;
							case 2:
								LED_HEATER = 1;
								LED_OFF0 = 0;
								LED_HIGH = 1;
								LED_LOW = 1;
								break;
							case 4:
								LED_HEATER = 1;
								LED_OFF0 = 1;
								LED_HIGH = 0;
								LED_LOW = 1;
								break;
							case 8:
								LED_HEATER = 1;
								LED_OFF0 = 1;
								LED_HIGH = 1;
								LED_LOW = 0;
								break;
							case 3:
								LED_HEATER = 0;
								LED_OFF0 = 0;
								LED_HIGH = 1;
								LED_LOW = 1;
								break;
							case 5:
								LED_HEATER = 0;
								LED_OFF0 = 1;
								LED_HIGH = 0;
								LED_LOW = 1;
								break;
							case 9:
								LED_HEATER = 0;
								LED_OFF0 = 1;
								LED_HIGH = 1;
								LED_LOW = 0;
								break;
							case 6:
								LED_HEATER = 1;
								LED_OFF0 = 0;
								LED_HIGH = 0;
								LED_LOW = 1;
								break;
							case 10:
								LED_HEATER = 1;
								LED_OFF0 = 0;
								LED_HIGH = 1;
								LED_LOW = 0;
								break;
							case 12:
								LED_HEATER = 1;
								LED_OFF0 = 1;
								LED_HIGH = 0;
								LED_LOW = 0;
								break;
							case 7:
								LED_HEATER = 0;
								LED_OFF0 = 0;
								LED_HIGH = 0;
								LED_LOW = 1;
								break;
							case 11:
								LED_HEATER = 0;
								LED_OFF0 = 0;
								LED_HIGH = 1;
								LED_LOW = 0;
								break;
							case 13:
								LED_HEATER = 0;
								LED_OFF0 = 1;
								LED_HIGH = 0;
								LED_LOW = 0;
								break;
							case 14:
								LED_HEATER = 1;
								LED_OFF0 = 0;
								LED_HIGH = 0;
								LED_LOW = 0;
								break;
							case 15:
								LED_HEATER = 0;
								LED_OFF0 = 0;
								LED_HIGH = 0;
								LED_LOW = 0;
								break;
							default:
								break;
							}
						}
					}
				}
			}
		} else if(Sta_Temp==0xA8) {				//接收到从机地址+读位，发送ACK信号
			regAddr = 0;
			I2CDataIndex = 0;
			I2CDAT = read_Buffer[I2CDataIndex + regAddr];		//把数据装载到发送寄存器，等待主机读取
			iicReadMode = 1;						//设置为从机发送状态
		} else if(Sta_Temp == 0x88) {			//发送或接收一字节数据，无检测到应答信号

		}
		I2CFLG  |= I2CF;					//清除中断标志
	}
}

void i2c_init(void)
{
	/**********选择I2C端口************************************************************/
// 	I2CIOS = 0;
// 	P30F = P30_I2C_SDA_SETTING | PU_EN;
// 	P31F = P31_I2C_SCL_SETTING | PU_EN;

	I2CIOS = 1;
	P03F = P03_I2C_SDA_SETTING | PU_EN;
	P02F = P02_I2C_SCL_SETTING | PU_EN;

//以上两组端口二选一
/***************************************************************************************/


	I2CCON = I2CE(1) | I2CIE(1) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(0);
	I2CADR = GCE(0)|(I2C_ADDR>>1);		//设置I2C从机地址
	I2CCR = 0x20;										//设置I2C时钟采样时钟
	INT4EN = 1;	 											//I2C中断开启
}

#endif
