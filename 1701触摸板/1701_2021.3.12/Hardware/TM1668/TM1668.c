#include "TM1668.h"
#include "delay.h"

const unsigned char SegCode[]=
{	
	0x3f,	// 0
	0x06,	// 1
	0x5B,	// 2
	0x4F,	// 3
	0x66,	// 4
	0x6D,	// 5
	0x7D,	// 6
	0x07,	// 7
	0x7F,	// 8
	0x6f, //9
	0x79,  //E  10
	0X5C,//字母O  11
	0x78,//t  12 
	0x7c,//b  13
	0x76,//h  14
	0x71,//f  15
	0x54,//n  16
	0x00,
};

/******************************************************************************
* 时        间：2018年4月11日14:58:23
 * 函数名称：   void delay_TM1618(unsigned char x)
 * 函数功能：   lcd初始化延时
 * 备       注：
 * 修       改：无
 ********************************************************************************/

void delay_TM1668(unsigned char x)
{
    unsigned char i, j;
    for(i=x; i>0; i--)
        for(j =1; j>0; j--);
}


void writeTM1668_byte(unsigned char byte)
{
    unsigned char i;
    for(i=0; i<8; i++)
    {
        if(byte>>i & 0x01)
            SIO = 1;
        else
            SIO =0;

        CLK = 0;
        delay_TM1668(1);
        CLK =  1;
        delay_TM1668(1);
    }
}


void writeTM1668_com(unsigned char com)
{
    STB = 0;
    delay_TM1668(3);
    writeTM1668_byte(com);
    delay_TM1668(3);
    STB = 1;
}

/******************************************************************************
* 时    间：2018年4月11日14:58:23
* 函数名称：void delay_TM1618(unsigned char x)
* 函数功能：lcd初始化延时
* 备    注：D9 = 0；RB灭;
						D9 = 1；B亮；
						D9 = 2；R亮；
						D9 = 3；RB亮
* 修    改：无
 ********************************************************************************/
void writeTM1668_data(unsigned char shi, unsigned char ge,unsigned char D7,unsigned char D8,unsigned char D9,unsigned char D10,unsigned char D11)
{
//	u8 ShiWei,GeWei;
	
	STB = 0;
	delay_TM1668(3);
	
	writeTM1668_byte(0xc0);
	writeTM1668_byte((SegCode[shi] & 0x01)| (SegCode[ge] & 0x01)<<1);//c0
	writeTM1668_byte(0);//c1
	writeTM1668_byte((SegCode[shi] & 0x02)>>1 | (SegCode[ge] & 0x02));//c2
	writeTM1668_byte(D9 & 0x01);//c3  LED9 b
	writeTM1668_byte((SegCode[shi] & 0x04)>>2 | (SegCode[ge] & 0x04)>>1);//c4
	writeTM1668_byte(D10 & 0x01);//c5  LED10 b
	writeTM1668_byte((SegCode[shi] & 0x08)>>3 | (SegCode[ge] & 0x08)>>2);//c6
	writeTM1668_byte(D11 & 0x01);//c7 LED11 b
	writeTM1668_byte((SegCode[shi] & 0x10)>>4 | (SegCode[ge] & 0x10)>>3 | D7<<7);//c8
	writeTM1668_byte((D9 & 0x02)>>1);//c9 //LED9 R
	writeTM1668_byte((SegCode[shi] & 0x20)>>5 | (SegCode[ge] & 0x20)>>4 | D8<<7);//ca
	writeTM1668_byte((D10 & 0x02)>>1);//cb  LED10 R
	writeTM1668_byte((SegCode[shi] & 0x40)>>6 | (SegCode[ge] & 0x40)>>5 );//cc
	writeTM1668_byte((D11 & 0x02)>>1);//cd LED11 R
	delay_TM1668(3);
	STB = 1;
	writeTM1668_com(0x89);//传显示控制命令设置最高亮度
//	delay_TM1668(3);	
}





void TM1668_Init(void)
{
	P1UR = 0X00;//禁止上拉
	P1   = 0X00;
	P1M  |= 0X0E;//设置输出模式

	CLK = 1;
	STB = 1;
	SIO = 1;
	writeTM1668_com(0x03);//设置显示模式（ 03H）7位10段
	delay_TM1668(10);
	writeTM1668_com(0x40);// 自动地址增加 
	delay_TM1668(10);	
	
}


