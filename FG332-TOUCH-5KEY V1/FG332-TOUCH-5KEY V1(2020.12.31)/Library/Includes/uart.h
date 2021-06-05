
#define UART0_TX_BUF_SIZE		20
#define UART0_RX_BUF_SIZE		20

typedef struct
{
	unsigned char head;
	unsigned char tail;
}T_Buf_Info;


#ifdef _UART_C_
#ifdef UART0_EN
	T_Buf_Info xdata	uart0_send;
	T_Buf_Info xdata	uart0_rev;
	unsigned char  uart0_tx_buf[UART0_TX_BUF_SIZE];
	unsigned char xdata uart0_rx_buf[UART0_RX_BUF_SIZE];
	bit uart0_tx_flag;
#endif
#else
#ifdef UART0_EN
	extern T_Buf_Info xdata	uart0_send;
	extern T_Buf_Info xdata	uart0_rev;
	extern unsigned char  uart0_tx_buf[UART0_TX_BUF_SIZE];
	extern unsigned char xdata uart0_rx_buf[UART0_RX_BUF_SIZE];
	extern bit uart0_tx_flag;	
#endif	
#endif
#ifndef UART0_EN
	  #define Uart0_PutChar(n)
#endif

#ifdef UART0_EN
void Uart0_PutChar(unsigned char bdat);
void Uart0_Initial(unsigned long int baudrate);
void UART0_RX_ISR(void);
void UART0_TX_ISR(void);
#endif	

#ifdef PRINT_EN
void uart_printf(char *fmt,...);
#endif