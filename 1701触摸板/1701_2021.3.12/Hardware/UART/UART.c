/***************************************************************************
*Copyright(c) 2018,�������ֵ������޹�˾
*All rights reserved.
*
*�ļ����ƣ�UART.c
*ժ    Ҫ��
*
*
*��ǰ�汾��V1.0
*��    �ߣ�yehuoyan
*������ڣ�2018��6��8��17:08:06
*
*
*ȡ���汾��
*��    �ߣ�yehuoyan
*������ڣ�
******************************************************************************/
#include "UART.h"

u8 uartTxBuf, uartRxBuf;
/******************************************************************************
* ʱ    �䣺2018��6��8��17:00:15
* �������ƣ�void ADC(void)
* �������ܣ���ʱ��0,1��ʼ������
* ��    ע��    
* ��    �ģ���
 ********************************************************************************/

void UART_Init(u32 Baud)
{
    S0CON = 0x50;//ģʽ1����ʹ��
    S0CON2 = 0x80;//�����ʲ������ɼĴ��� S0RELH/S0RELL ����    
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
    IEN0 = 0x90;//ʹ�� UART �ж�
    
    P0M = P0M | 0x01 & ~0x02;
    P00 = 1; 
   
}
//�ض���printf����
char putchar(char c) 
{ 
    ES0 = 0; 
    TI0 = 0; //��շ������ж������־λ 
    S0BUF = c; //�����ݷ���Ĵ������� 
    while(TI0 == 0);//�ȴ�������ϣ��������TI == 1 
    TI0 = 0; //��շ������ж������־λ     
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


