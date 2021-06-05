#ifndef _UART_C_
#define _UART_C_
#include "ca51f5_config.h"
#include "../../includes/ca51f5sfr.h"
#include "../../includes/ca51f5xsfr.h"
#include "../../includes/gpiodef_f5.h"
#include "../../includes/system.h"

#include "../../Library/includes/uart.h"
#include <intrins.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <absacc.h>
/*********************************************************************************************************************/
/*********************************************************************************************************************/
#ifdef UART0_EN
/*********************************************************************************************************************
注意：以下波特率配置参数前提条件是系统时钟为16MHz，如果修改系统时钟频率，波特率配置参数须另行计算。
***********************************************************************************************************************/
void Uart0_Initial(unsigned long int baudrate)
{
	code unsigned long int BR_TAB[]=
	{
		1200,
		2400,
		4800,
		9600,
		19200,
		38400,
		57600,
		115200,
	};
	code unsigned int BR_SET_TAB[][2]=
	{
		{416,31},
		{208,31},
		{104,31},
		{52,31},
		{26,31},
		{13,31},
		{10,27},
		{5,27},
	};
	unsigned int value_temp;
	unsigned char i;
	
	uart0_send.head = 0;
	uart0_send.tail = 0;
	uart0_rev.head = 0;
	uart0_rev.tail = 0;
	uart0_tx_flag = 0;
	
	GPIO_Init(P31F,P31_UART0_RX_SETTING);
	GPIO_Init(P30F,P30_UART0_TX_SETTING);
	
	for(i=0;i<sizeof(BR_TAB)/4;i++)
	{
		if(baudrate == BR_TAB[i])
		{
			value_temp = 0x10000 - BR_SET_TAB[i][0];
			UDCKS = 0x80 | BR_SET_TAB[i][1]; 
			break;
		}
	}
	if(i == sizeof(BR_TAB)/4) return;	//如果所设置的波特率不在表格中，可自行添加。
	
	T2CON = 	0x24;
	T2CH  = 	(unsigned char)(value_temp>>8);
	T2CL  = 	(unsigned char)(value_temp);
	TH2   = 	(unsigned char)(value_temp>>8);
	TL2   = 	(unsigned char)(value_temp);;	
	TR2   = 	1;

	S0CON = 0x50;	 
	ES0 = 1;
}
void Uart0_PutChar(unsigned char bdat)
{
	unsigned char free_space;
	unsigned char tail_tmp;
	while(1)
	{				
		tail_tmp = uart0_send.tail;	
		if(uart0_send.head < tail_tmp)
		{
			free_space = tail_tmp - uart0_send.head;
		}
		else
		{
			free_space = UART0_TX_BUF_SIZE + tail_tmp - uart0_send.head;
		}		
		if(free_space > 1)
		{
			ES0 = 0; 
			uart0_send.head++;
			uart0_send.head %= UART0_TX_BUF_SIZE;
			uart0_tx_buf[uart0_send.head] = bdat;			
			if(!uart0_tx_flag)
			{
				ES0 = 1;				
				uart0_send.tail++;
				uart0_send.tail %= UART0_TX_BUF_SIZE;		
				S0BUF=uart0_tx_buf[uart0_send.tail];				
				uart0_tx_flag = 1;		
			}
			else
			{
				ES0 = 1;	
			}			
			break;
		}
	}
}
void UART0_RX_ISR (void)
{
	RI0 = 0;
	uart0_rev.head++;
	uart0_rev.head %= UART0_RX_BUF_SIZE;
	uart0_rx_buf[uart0_rev.head]=S0BUF;
}
void UART0_TX_ISR (void)
{
	TI0 = 0;		
	if(uart0_send.head!=uart0_send.tail)
	{
		uart0_send.tail++;
		uart0_send.tail %= UART0_TX_BUF_SIZE;
		S0BUF=uart0_tx_buf[uart0_send.tail];				
	}
	else
	{
		uart0_tx_flag=0;
	}		
}
#endif
/*********************************************************************************************************************/
#endif