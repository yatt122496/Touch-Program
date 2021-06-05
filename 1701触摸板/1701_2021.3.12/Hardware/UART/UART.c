/***************************************************************************
*Copyright(c) 2018,深圳鹏林电子有限公司
*All rights reserved.
*
*文件名称：UART.c
*摘    要：
*
*
*当前版本：V1.0
*作    者：yehuoyan
*完成日期：2018年6月8日17:08:06
*
*
*取代版本：
*作    者：yehuoyan
*完成日期：
******************************************************************************/
#include "UART.h"

u8 uartTxBuf, uartRxBuf;
/******************************************************************************
* 时    间：2018年6月8日17:00:15
* 函数名称：void ADC(void)
* 函数功能：定时器0,1初始化函数
* 备    注：    
* 修    改：无
 ********************************************************************************/

void UART_Init(u32 Baud)
{
    S0CON = 0x50;//模式1接收使能
    S0CON2 = 0x80;//波特率产生器由寄存器 S0RELH/S0RELL 控制    
    S0RELH = 0x03;
    switch(Baud)
    {
        case 4800:
            PCON = 0x00;
            S0RELL = 0xe6;
        break;
        case 9600:
            PCON = 0x00;
            S0RELL = 0xf3;
        break;
        case 19200:
            PCON = 0x80;
            S0RELL = 0xf3;
        break;
        case 38400:
            PCON = 0x80;
            S0RELL = 0xf9;
        break;
        case 56000:
            PCON = 0x80;
            S0RELL = 0xfb;
        break;
        case 57600:
            PCON = 0x80;
            S0RELL = 0xfc;
        break;
        case 115200:
            PCON = 0x80;
            S0RELL = 0xfe;
        break;
    }
    IEN0 = 0x90;//使能 UART 中断
    
    P0M = P0M | 0x01 & ~0x02;
    P00 = 1; 
   
}
//重定义printf函数
char putchar(char c) 
{ 
    ES0 = 0; 
    TI0 = 0; //清空发送完中断请求标志位 
    S0BUF = c; //将数据放入寄存器发送 
    while(TI0 == 0);//等待发送完毕，发送完毕TI == 1 
    TI0 = 0; //清空发送完中断请求标志位     
    ES0 = 1; 
    
    return c; 
}

void SYSUartInterrupt(void) interrupt ISRUart
{
    if (TI0 == 1) 
    {
        S0BUF = uartTxBuf;
        TI0 = 0;
    } 
    else if (RI0 == 1) 
    {
        uartRxBuf = S0BUF;
        RI0 = 0;
    }
}


