#ifndef _INTERRUPT_C_
#define _INTERRUPT_C_

/*********************************************************************************************************************/
#include "ca51f5_config.h"
#include "includes\ca51f5sfr.h"
#include "includes\ca51f5xsfr.h"
#include "includes\gpiodef_f5.h"
#include "includes\system.h"
#include "Library\includes\uart.h"
#include "Library\Includes\tmc.h"	

#include "TS_Lib\Includes\ts_configuration.h"
#include "TS_Lib\Includes\ts_def.h"
#include "TS_Lib\Includes\ts_api.h"
#include "TS_Lib\Includes\ts_service.h"
#include <intrins.h>
#if DEBUG
#include "Library\Includes\i2c.h"		
void I2C_ISR(void);
#endif
/*********************************************************************************************************************/
extern unsigned char xdata TS_HalfSecCnt;
void INT2_Handler (void) interrupt 4 
{
#ifdef UART0_EN
	if(RI0)
	{
		UART0_RX_ISR();
	}
	if(TI0)
	{
		UART0_TX_ISR();
	}
#endif
}
void INT3_ISR (void) interrupt 5 	 
{
	static unsigned char TmCnt = 0;
	if(TMCON & TMF)			//ºÁÃëÖÐ¶Ï
	{
		TMCON |= TMF;	
#if SUPPORT_TOUCH_SLEEP_MODE	
		if(TS_SleepMode)
		{
			TS_HalfSecCnt++;
			return;
		}
		else
		{
			TS_MS_ISR();
		}
#else		
		TS_MS_ISR();
#endif
		if(TS_LongKeyTimer)
		{
			TS_LongKeyTimer--;		
		}	
		TmCnt++;
		if(TmCnt >= 128)
		{
			TmCnt = 0;
			TS_HS_ISR();
		}
	}
#if SUPPORT_TOUCH_SLEEP_MODE	
	if(TS_SleepMode)
	{
		return;
	}
#endif
	if(TKIF != 0)
	{
		TS_ISR();
	}
}
void INT4_ISR(void) interrupt 6 
{
#if DEBUG
	if(I2CFLG & I2CF)		
	{
		I2C_ISR();
	}
#endif
}
#endif
