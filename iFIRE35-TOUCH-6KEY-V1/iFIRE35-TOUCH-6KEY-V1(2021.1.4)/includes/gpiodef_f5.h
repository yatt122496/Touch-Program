#ifndef _GPIODEF_H_
#define _GPIODEF_H_
enum
{
	HIGH_Z		= 0,					
	INPUT			= 1,          
	OUTPUT		= 2,          
                        
	P31_TK0_SETTING			= 4,
	P30_TK1_SETTING			= 4,
	P07_TK2_SETTING			= 4,
	P06_TK3_SETTING			= 4,
	P05_TK4_SETTING			= 4,
	P04_TK5_SETTING			= 4,
	P03_TK6_SETTING			= 4,
	P02_TK7_SETTING			= 4,
	P01_TK8_SETTING			= 4,
	P00_TK9_SETTING			= 4,
	P34_TK10_SETTING		= 4,
	P33_TK11_SETTING		= 4,
	P32_TK12_SETTING		= 4,
	P35_CAP_SETTING			= 4,
                     
	P32_PWM0_SETTING		= 5,
	P33_PWM1_SETTING		= 5,
	P34_PWM2_SETTING		= 5,
	P01_PWM3_SETTING		= 5,
	P04_PWM4_SETTING		= 5,
	P05_PWM5_SETTING		= 5,

	P00_DAK0_SETTING		= 3,
	P01_DAK1_SETTING		= 3,                        
                       
	P30_UART0_TX_SETTING	= 5,      
	P31_UART0_RX_SETTING	= 5,       
                                           
	P30_I2C_SDA_SETTING		= 3,      
	P31_I2C_SCL_SETTING		= 3,      
	P03_I2C_SDA_SETTING		= 3,      
	P02_I2C_SCL_SETTING		= 3,  	
                        
	P32_T0_SETTING			= 3,        
	P35_T1_SETTING			= 3,        
	P06_T2_SETTING			= 3,        
                        
	P07_RESET_SETTING		= 3,			  
	        
	
	P04_T2CP_SETTING		= 3,  
	P05_T2EX_SETTING		= 3,  

	PU_EN				= 0x80,
	PD_EN				= 0x40,
	OP_EN				= 0x20,
};	
#define  GPIO_Init(reg,val)	reg = val

/******************************************************************************/

#endif
