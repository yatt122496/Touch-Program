#ifndef __MYIIC_H
#define __MYIIC_H
	  
#include "Config.h"	


//IO方向设置
#define SDA_IN()  {P1UR = 0X00;P1 |= 0X01;P1M &= 0X7e;}
#define SDA_OUT() {P1UR = 0X00;P1 |= 0X01;P1M |= 0X7f;}

//IO操作函数	 
#define IIC_SCL    P07 //SCL0
#define IIC_SDA    P10 //SDA	 
#define READ_SDA   P10  //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(unsigned char txd);			//IIC发送一个字节
unsigned char IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
unsigned char IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(unsigned char daddr,unsigned char addr,unsigned char dat);
unsigned char IIC_Read_One_Byte(unsigned char daddr,unsigned char addr);	 
unsigned char IIC_Read_Byte1(void);
#endif
















