#include "myiic.h"

	  
//��ʼ��IIC
void IIC_Init(void)
{	
	//SDA
	P1UR = 0X00;
	P1 = 0X00;
	P1M |= 0X7F;	
	//SCL
	P0UR = 0X00;
	P0 |= 0X00;
	P0M |= 0X80;
//	P0OC = 0X00;
	
	IIC_SCL = 1;
	IIC_SDA = 1;

}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	Delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
//	Delay_us(5);
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_us(4);
	IIC_SCL=1;    
	IIC_SDA=1;//����I2C���߽����ź�
	Delay_us(4);
//	Delay_us(5);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;Delay_us(2);	   
	IIC_SCL=1;Delay_us(2);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	Delay_us(4);
	IIC_SCL=1;
	Delay_us(4);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	Delay_us(4);
	IIC_SCL=1;
	Delay_us(4);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
        Delay_us(4);   //��TEA5767��������ʱ���Ǳ����
        IIC_SCL=1;
        Delay_us(4); 
        IIC_SCL=0;	
        Delay_us(4);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
	for(i=0;i<8;i++ )
	{
			IIC_SCL=0; 
			Delay_us(4);
			IIC_SCL=1;
			receive<<=1;
			Delay_us(4);
			if(READ_SDA)receive++;
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

u8 IIC_Read_Byte1(void)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
	for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        Delay_us(5);
        IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
        Delay_us(5); 
    }					  
    return receive;
}


























