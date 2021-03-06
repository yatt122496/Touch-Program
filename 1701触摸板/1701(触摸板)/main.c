#ifndef _MAIN_C_
#define _MAIN_C_
/*********************************************************************************************************************/
#include "ca51f5_config.h"
#include "includes\ca51f5sfr.h"
#include "includes\ca51f5xsfr.h"
#include "includes\gpiodef_f5.h"
#include "includes\i2c.h"
#include "includes\led.h"

#include "Library\includes\uart.h"
#include "Library\includes\system_clock.h"
#include "Library\Includes\tmc.h"	
#include "includes\system.h"
#include "Library\includes\wdt.h"
/*********************************************************************************************************************/
#include "TS_Lib\Includes\ts_configuration.h"
#include "TS_Lib\Includes\ts_def.h"
#include "TS_Lib\Includes\ts_api.h"
#include "TS_Lib\Includes\ts_service.h"

void Delay_ms(unsigned int n);
/*********************************************************************************************************************/
/*******************************************************************************************************************************************
说明：
------------------------------------------------------------------------------------------------------------
1.ts_configuration.h是触摸的配置文件，可在配置文件中设置触摸通道、灵敏度等。详见ts_configuration.h中的说明。
------------------------------------------------------------------------------------------------------------
2.如果需要使用UART来调试，可在ca51f5_config.h中打开宏定义UART0_EN
------------------------------------------------------------------------------------------------------------
3.触摸库对外的数据接口为KeysFlagSN，用户可根据KeysFlagSN的值来判断触摸键是否按下（如果触摸键按下，KeysFlagSN
的对应位一直为1，触摸键松开，对应位变为0），TS_Key是根据KeysFlagSN的值生成的按键消息，用户如不使用可忽略。
------------------------------------------------------------------------------------------------------------
4.使能了触摸省电模式后，在无按键时，在定义的时间后会进入省电模式，进入省电模式前会关闭TMC中断和触摸中断（注意，总
中断仍是开启的），在触摸省电模式下，CPU会进入STOP模式，在被触摸唤醒后，程序在省电函数（TS_EnterSleepMode）的循环内运行（注意，触摸省电模式程序不
会在主循环内运行），在触摸省电模式下如果还要响应其他中断，用户需在进入触摸省电模式前自行开启其他中断，
如果需要退出省电模式，用户只需要在省电函数循环内加入条件判断，跳出循环即可。

变量TS_SleepEn是控制触摸省电模式的开关，如果希望程序在某些条件下不进入省电模式，只需在此条件下设置TS_SleepEn = 0；


------------------------------------------------------------------------------------------------------------
5.触摸外挂电容(即TK_CAP引脚连接电容)范围：6nF~50nF,建议值：20nF（即203）
------------------------------------------------------------------------------------------------------------
6.触摸引脚串联电阻范围：0~5K，建议值：1K欧姆，如果有抗对讲机等电磁干扰要求， 此电阻至少3K以上。
*******************************************************************************************************************************************/

#if DEBUG
static unsigned char read_Buffer[3];
#endif
void main(void)
{
	unsigned char *pKey = read_Buffer;
	unsigned int dwCnt = 0;
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE3;	//设置LVD复位电压为2.0V
#endif
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);
#endif

//看门狗时钟源为IRCL
	CKCON |= ILCKE;									//使能IRCL
	WDCON  = WDTS(WDTS_IRCL) | WDRE(WDRE_reset);   	//设置看门狗时钟源为ILCKE，模式为复位模式
	WDVTHH = 0;										//看门狗复位阈值高八位设置 当前值为5s	
	WDVTHL = 75;									//看门狗复位阈值低八位设置
	WDFLG = 0xA5;
	
	EA = 1;

	TS_init();
//	led_init();
#if DEBUG == 0
	i2c_init();
#endif
//	Uart0_PutChar(0xff);
	while(1)
	{
		TS_Action();
		
#if SUPPORT_WHEEL_SLIDER
		if(WheelSliderPosition != -1)
		{
			//当WheelSliderPosition不等于-1时， 表示滑条或圆环有触摸事件发生。WheelSliderPosition的值表示滑条或圆环的位置。
		}
#endif
#if SUPPORT_KEY

#define IPOWKEY 0x40 //sw7
#define IECOKEY 0x80 //A
#define IK1 0x01  //K1
#define IK2 0x02
#define IK3 0x04
#define IK4 0x08
#define IK5 0x10
#define IK6 0x20
		
#define OPOWKEY 0x01 //sw7
#define OECOKEY 0x80 //A
#define OK1 0x40  //K1
#define OK2 0x20
#define OK3 0x10
#define OK4 0x08
#define OK5 0x04
#define OK6 0x02
/*************************************************************************************************
变量KeysFlagSN是触摸库对外的数据接口，KeysFlagSN的每一位对应一个触摸键的状态，为1表示触摸键触发。可多键同时触发。
*************************************************************************************************/
		dwCnt++;
		if (dwCnt > 500) {
			dwCnt = 0;
			if(KeysFlagSN != 0)
			{
	//			Uart0_PutChar(KeysFlagSN);
				switch(KeysFlagSN)
				{
					case IK1: {
						*pKey = OK1;
						break;
					}
					case IK2: {
						*pKey = OK2;
						break;
					}
					case IK3: {
						*pKey = OK3;
						break;
					}
					case IK4: {
						*pKey = OK4;
						break;
					}
					case IK5: {
#ifdef UART0_EN
						*pKey = OPOWKEY;
#else
						*read_Buffer = OK5;
#endif				
						break;
					}
					case IK6: {
#ifdef UART0_EN
						*pKey = OECOKEY;
#else
						*read_Buffer = OK6;
#endif
						break;
					}
					case IPOWKEY: {
						*pKey = OPOWKEY;
						break;
					}
					case IECOKEY: {
						*pKey = OECOKEY;
						break;
					}
					case IK1 | IK2: {
						*pKey = OK1 | OK2;
						break;
					}
					case IK2 | IK3: {
						*pKey = OK2 | OK3;
						break;
					}
					case IK3 | IK4: {
						*pKey = OK3 | OK4;
						break;
					}
					case IK4 | IK5: {
						*pKey = OK4 | OK5;
						break;
					}
					case IK5 | IK6: {
						*pKey = OK5 | OK6;
						break;
					}
					case IK2 | IK5: {
						*pKey = OK2 | OK5;
						break;
					}
					//......
					default:
//						if (KeysFlagSN & IPOWKEY) {
//							*pKey = OPOWKEY;
//						}
						break;
				}
//				*(pKey + 1) = 0;
//				Uart0_PutChar(*(pKey + 1));
	//			read_Buffer[2] = 0xa5;
			} else {
				*pKey = 0;
//				*(pKey + 1) = 0;
	//			read_Buffer[2] = 0xa5;
			}
//			#ifdef UART0_EN
//				Uart0_PutChar(*pKey);
//			#endif
		}
		
		
#if GENERATE_TS_KEY_EN
/*************************************************************************************************
变量TS_Key是根据KeysFlagSN得到的按键信息，以下为按键产生的过程：
|-----------------------------------------------------------------------------------------------------------------------------------|
|	单键：以K1为例，K1按键产生的流程如下所示：																																												|
|																																																																		|
|					 	|---> K1|KEY_BREAK(短按松开)																																														|
|	K1(按下)--|																																																												|
|					 	|---> K1|KEY_LONG_START(长按大约1秒)---> K1|KEY_LONG(一直长按，约每300ms产生一次长按键)---->K1|KEY_LONG_BREAK(长按松开)	|
|																								 ^																							    |																|
|																								 |																							    |																|
|																								 |----------<-----------<------------<--------------|																|
|-----------------------------------------------------------------------------------------------------------------------------------|

|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|																																																																																				|
|	复合键：以K1(K1=0x0001),K2(K2=0x0002)为例， 当K1，K2同时按下时，产生按键为(K1<<5)|K2，即0x22, 产生按键的流程如下所示：																								|
|																																																																																				|
|										|---> ((K1<<5)|K2)|KEY_BREAK(短按松开)																																																							|
|	(K1<<5)|K2(按下)--|																																																																										|
|										|---> ((K1<<5)|K2)|KEY_LONG_START(长按大约1秒)---> ((K1<<5)|K2)|KEY_LONG(一直长按，约每300ms产生长按键)---->((K1<<5)|K2)|KEY_LONG_BREAK(长按松开)		|
|																															 		 ^																							           |																					|
|																																 	 |																							           |																					|
|																															 		 |---------<-------------<----------------<----------------|																					|
|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
																															 
注意：由于复合键按下时，软件不一定同时检测到双键，而是先检测到单键按下，例如先检测到K1，此时会先产生K1键，等到检测到K2也按
下时，才会产生按键(K1<<5)|K2，检测到双键后，如果双键一直按下，会产生((K1<<5)|K2)|KEY_LONG_START和((K1<<5)|K2)|KEY_LONG，如果
有一个键先松手，会停止产生按键， 等到双键都松开时，才会产生((K1<<5)|K2)|KEY_BREAK(短按松开)或((K1<<5)|K2)|KEY_LONG_BREAK(长按松开)
*************************************************************************************************/
		if(TS_Key != 0)
		{
			switch(TS_Key)
			{
				//单按键消息
				case K1:									//K1短按产生的按键消息
					break;
				case (K1|KEY_BREAK):      //K1短按松手产生的按键消息
					break;
				case (K1|KEY_LONG_START):	//K1长按开始产生的消息（长按约1秒时产生）
					break;
				case (K1|KEY_LONG):				//K1长按产生的消息（每隔约300ms产生一次）
					break;
				case (K1|KEY_LONG_BREAK):	//K1长按松手产生的消息
					break;
#if GENERATE_DOUBLE_KEY_EN				
	//复合键消息
				case (K1<<5)|K2:										//K1和K2同时按下时产生的按键消息
					break;
				case ((K1<<5)|K2)|KEY_BREAK:				//K1和K2短按松手产生的按键消息
					break;
				case ((K1<<5)|K2)|KEY_LONG_START:		//K1和K2长按开始产生的按键消息（长按约1秒时产生）
					break;
				case ((K1<<5)|K2)|KEY_LONG:					//K1和K2长按产生的消息（每隔约300ms产生一次）
					break;
				case ((K1<<5)|K2)|KEY_LONG_BREAK:		//K1和K2长按松手产生的消息
					break;
#endif
			}
		}
#endif
#endif
	}
}
#endif
