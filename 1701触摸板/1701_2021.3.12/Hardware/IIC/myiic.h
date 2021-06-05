#ifndef __MYIIC_H
#define __MYIIC_H
	  
#include "Config.h"	


//IO��������
#define SDA_IN()  {P1UR = 0X00;P1 |= 0X01;P1M &= 0X7e;}
#define SDA_OUT() {P1UR = 0X00;P1 |= 0X01;P1M |= 0X7f;}

//IO��������	 
#define IIC_SCL    P07 //SCL0
#define IIC_SDA    P10 //SDA	 
#define READ_SDA   P10  //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(unsigned char txd);			//IIC����һ���ֽ�
unsigned char IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
unsigned char IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(unsigned char daddr,unsigned char addr,unsigned char dat);
unsigned char IIC_Read_One_Byte(unsigned char daddr,unsigned char addr);	 
unsigned char IIC_Read_Byte1(void);
#endif
















