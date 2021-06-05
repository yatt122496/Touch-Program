#ifndef _TK_API_C_
#define _TK_API_C_

/*********************************************************************************************************************/
#include "ca51f5_config.h"
#include "includes\ca51f5sfr.h"
#include "includes\ca51f5xsfr.h"
#include "includes\gpiodef_f5.h"

#include "Library\Includes\tmc.h"		
#include "Library\Includes\system_clock.h"		
#include "Library\includes\uart.h"
#include "includes\system.h"

#include "Library\includes\delay.h"
#include <intrins.h>
/*********************************************************************************************************************/
#include "TS_Lib\Includes\ts_configuration.h"
#include "TS_Lib\Includes\ts_def.h"
#include "TS_Lib\Includes\ts_api.h"
#include "TS_Lib\Includes\ts_service.h"		   
/*********************************************************************************************************************/
void Debug_init(void);
void Debug_ParamLoad(void);
#if SUPPORT_KEY
#if TK_SENSITIVE_AUTO_TRIM_EN
void TK_TouchThdTrim(unsigned char ch);
#endif
code unsigned int TS_KEY_CH_INFO_SEQ[][2]=
{
	KEY_SEQ
};
#if TK_SENSITIVE_AUTO_TRIM_EN
code unsigned int TK_BASELINE_VALUE_INFO_SEQ[]=
{
	TK_BASELINE_VALUE_SEQ
};
#endif
#endif
#if SUPPORT_WHEEL_SLIDER
code unsigned char TS_WHEEL_SLIDER_CH_SEQ[]=
{
	WHEEL_SLIDER0_SEQ,
};
code unsigned char WHEEL_SLIDER0_MAX_MIN_TAB[]={WHEEL_SLIDER0_CH_MIN_RATE};
#else
code unsigned char WHEEL_SLIDER0_MAX_MIN_TAB[1]={0};
#endif	
#if SUPPORT_KEY	
code TYPE_SN MASK_TAB[]=
{
	0x0001,
#if (KEY_CH_COUNT > 1)
	0x0002,
#endif
#if (KEY_CH_COUNT > 2)
	0x0004,
#endif
#if (KEY_CH_COUNT > 3)
	0x0008,
#endif
#if (KEY_CH_COUNT > 4)
	0x0010,
#endif
#if (KEY_CH_COUNT > 5)
	0x0020,
#endif
#if (KEY_CH_COUNT > 6)
	0x0040,
#endif
#if (KEY_CH_COUNT > 7)
	0x0080,
#endif
#if (KEY_CH_COUNT > 8)
	0x0100,
#endif
#if (KEY_CH_COUNT > 9)
	0x0200,
#endif
#if (KEY_CH_COUNT > 10)
	0x0400,
#endif
#if (KEY_CH_COUNT > 11)
	0x0800,
#endif
#if (KEY_CH_COUNT > 12)
	0x1000,
#endif

};
code unsigned char AREA_CONFIRM_TIME_TAB[]=
{
	FINGER_TOUCH_CONFIRM_TIME,
	AREA_PNOISE_PLUS_CONFIRM_TIME,
	AREA_PNOISE_CONFIRM_TIME,
	AREA_NNOISE_CONFIRM_TIME,
	AREA_OVERLOW_CONFIRM_TIME,
};
#else
code unsigned char AREA_CONFIRM_TIME_TAB[1]={0};
code unsigned int MASK_TAB[1]={0};
#endif
void TS_MS_ISR (void)
{
	static unsigned char xdata ms_cnt = 0;
	unsigned char i;
 
	ms_cnt++;
	if(ms_cnt >= 4)
	{
		ms_cnt = 0;
		for(i = 0; i < TS_Cnt; i++)
		{
			if(TS_AreaConfirmTimer[i])
			{
				TS_AreaConfirmTimer[i]--;
			}
		}
#if SUPPORT_WHEEL_SLIDER	
		if(TSWheelSlider_TouchConfirmTimer)
		{
			TSWheelSlider_TouchConfirmTimer--;
		}
#endif
#if SUPPORT_KEY
#if SUPPORT_COVER_PANAL_AFTER_POWERON
		if(PanalCoverJudgeTimer) PanalCoverJudgeTimer--;
#endif
#endif
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
		if(RefChDataTimer) RefChDataTimer--;
#endif
#endif
	}	
}
void TS_HS_ISR (void)
{
#if SUPPORT_KEY
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
	unsigned char i;
#endif
#endif
	TS_HalfSecCnt++;
	
#if SUPPORT_KEY
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(TSKey_LongTouchLimitTimer[i])
		{
			TSKey_LongTouchLimitTimer[i]--;
		}
	}		
#endif
#endif
#if SUPPORT_WHEEL_SLIDER	
#if (WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT > 0)
	if(TSWheelSlider_LongTouchLimitTimer)
	{
		TSWheelSlider_LongTouchLimitTimer--;
	}
#endif
#endif
	if(TS_RefCHBaseLineAdjuTimer)
	{
		TS_RefCHBaseLineAdjuTimer--;
	}	
	if(EnterStopScanTimer)
	{
		EnterStopScanTimer--;
	}	
}
void TS_ISR (void)
{	
	unsigned char i;
	WORD_UNION TS_Data[6];
#if TK_FREQ_JUMP_EN
	static unsigned int xdata TSDataTemp[2][OPENED_TS_COUNT+1];
	unsigned int xdata delta[2];
	unsigned int min_delta;
	unsigned char min_index;
	unsigned char j;
#endif
	if(TLFLG & (TLERR|TLKOV|TLLOV))
	{
		TLFLG |= TLERR|TLKOV|TLLOV;
	}

	if(TKIF & TKIF0)
	{
		TKIF = TKIF0; 
		TS_Data[0].bVal[0] = TK0MSH;
		TS_Data[0].bVal[1] = TK0MSL;
	}
	if(TKIF & TKIF1)
	{
		TKIF = TKIF1; 	
		TS_Data[1].bVal[0] = TK1MSH;
		TS_Data[1].bVal[1] = TK1MSL;	
	}
	if(TKIF & TKIF2)
	{
		TKIF = TKIF2; 	
		TS_Data[2].bVal[0] = TK2MSH;
		TS_Data[2].bVal[1] = TK2MSL;
	}
	if(TKIF & TKIF3)
	{
		TKIF = TKIF3; 	
		TS_Data[3].bVal[0] = TK3MSH;
		TS_Data[3].bVal[1] = TK3MSL;	
	}
	if(TKIF & TKIF4)
	{
		TKIF = TKIF4; 	
		TS_Data[4].bVal[0] = TK4MSH;
		TS_Data[4].bVal[1] = TK4MSL;
	}
	if(TKIF & TKIF5)
	{
		TKIF = TKIF5; 	
		TS_Data[5].bVal[0] = TK5MSH;
		TS_Data[5].bVal[1] = TK5MSL;
	}
	
	for(i = 0; i < 6; i++)
	{
#if TK_FREQ_JUMP_EN
		if(TS_State == TS_DEAL)
		{
			TSDataTemp[NowTKFreqIndex][TS_Index+i] = TS_Data[i].wVal;	
			
			if(NowTKFreqIndex == 1)
			{
				min_delta = 0xFFFF;
				for(j = 0; j < 2; j++)
				{
					if(TSDataTemp[j][TS_Index+i] > TS_JumpFreqData[j][TS_Index+i]/TS_ACQ_TIMES)
					{
						delta[j] = TSDataTemp[j][TS_Index+i] - TS_JumpFreqData[j][TS_Index+i]/TS_ACQ_TIMES;
					}
					else
					{
						delta[j] = TS_JumpFreqData[j][TS_Index+i]/TS_ACQ_TIMES - TSDataTemp[j][TS_Index+i];
					}
					if(delta[j] < min_delta)
					{
						min_delta = delta[j];
						min_index = j;
					}
				}
				TS_Data[i].wVal = TSDataTemp[min_index][TS_Index+i] + TS_JumpFreqData[1][TS_Index+i]/TS_ACQ_TIMES - TS_JumpFreqData[min_index][TS_Index+i]/TS_ACQ_TIMES;	
			}	
			
		}
#endif	
#if TK_FREQ_JUMP_EN
		if(((TS_State == TS_DEAL)&&(NowTKFreqIndex == 1)) ||(TS_State != TS_DEAL))
#endif
		{
#if (TS_ACQ_TIMES == 1)
			TS_RawData[TS_Index+i] = TS_Data[i].wVal;
#else
			TS_DataSum[TS_Index+i] += TS_Data[i].wVal;	
#endif		
		}
		if(TS_Index+i == TS_Cnt)
		{			
			break;
		}	

	}
#if TK_FREQ_JUMP_EN
	if(TS_State == TS_DEAL)
	{
		if(NowTKFreqIndex == 1)
		{
			NowTKFreqIndex = 0;
			TKCFG = TKDIV(TKDIV_VAL2)|TKTMS(TKTMS_VAL);		
			TKCON |= TKST(1);	
			return;
		}
		else
		{
			NowTKFreqIndex = 1;
			TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);	
		}
	}
#endif
	if(TS_Index+6 > TS_Cnt)
	{
#if (TS_ACQ_TIMES == 1)
		TS_CycleScanDoneFlag = 1;	
#else
		TS_Acq_Counter++;
		if(TS_Acq_Counter >= TS_ACQ_TIMES)
		{
			for(i = 0; i < TS_Cnt+1; i++)
			{
				TS_RawData[i] = TS_DataSum[i];
				TS_DataSum[i] = 0;
			}
			TS_CycleScanDoneFlag = 1;		
			TS_Acq_Counter = 0;
		}	
#endif		
		TS_Index = 0;
	}
	else 
	{
		TS_Index += 6;
	}
	TS_ScanStart();	
	if(TS_HalfSecCnt) TS_HalfSecCnt--;
	if(MainLoopCnt1 != MainLoopCnt2)
	{
		MainLoopCnt2 = MainLoopCnt1;
		WDFLG = 0xA5;
	}
}
void TS_DataFiltering(void)
{
	unsigned char i;
#if (FILTER_COUNT > 1)
	unsigned char j;
	unsigned int DataSum,DataMax,DataMin;
#endif
	for(i = 0; i < TS_Cnt+1; i++)
	{
#if (FILTER_COUNT == 1)
		TS_PostData[i] = TS_RawData[i];
#else
		TS_FilterPosIdx[i]++;
		if(TS_FilterPosIdx[i] >= FILTER_COUNT) 
		{
			TS_FilterPosIdx[i] = 0;
		}
		INT3EN = 0;
		TS_FilterBuf[i][TS_FilterPosIdx[i]] = TS_RawData[i];
		INT3EN = 1; 
		
		DataSum = 0;
		DataMax = 0;
		DataMin = 0xFFFF;
	 	for(j = 0; j < FILTER_COUNT; j++)
		{
			DataSum += TS_FilterBuf[i][j];
#if (FILTER_COUNT > 2)
			if(TS_FilterBuf[i][j] > DataMax)
			{
				DataMax = TS_FilterBuf[i][j];
			}
			if(TS_FilterBuf[i][j] < DataMin)
			{
				DataMin = TS_FilterBuf[i][j];
			}
#endif
		}
#if (FILTER_COUNT == 2)
		TS_PostData[i] = (DataSum)/(FILTER_COUNT);	
#else
		TS_PostData[i] = (DataSum - DataMax - DataMin)/(FILTER_COUNT-2);	
#endif
#endif		
 	}		
}
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
bit TS_RefChAbnormalJudge(void)
{
	unsigned int ref_value,crt_value,delta;
	
	if(RefChDataBufIdx == (REF_CH_DATA_BUF_SIZE-1)) 
	{
		ref_value = RefChDataBuf[0];
	}
	else
	{
		ref_value = RefChDataBuf[RefChDataBufIdx + 1];
	}
	crt_value = TS_PostData[OPENED_TS_COUNT];
	if(ref_value > crt_value)
	{
		delta = ref_value - crt_value;
	}
	else
	{
		delta = crt_value - ref_value;
	}
	if(delta >= REF_CH_ABNORMAL_THD)			
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void TS_RefChCheck(void)
{
	if(!RefChDataTimer)
	{
		RefChDataTimer = 3;
		RefChDataBufIdx++;
		if(RefChDataBufIdx >= REF_CH_DATA_BUF_SIZE)
		{
			RefChDataBufIdx = 0;
		}
		RefChDataBuf[RefChDataBufIdx] = TS_PostData[OPENED_TS_COUNT];
	}
}
#else
bit TS_RefChAbnormalJudge(void)
{
	return 0;
}
#endif
#endif
void TS_RunInit(void)
{
	unsigned char i,j;
	static unsigned char TS_ScanTimes=0;
#if (POWER_ON_WAIT_TK_STABLE_EN || TK_FREQ_JUMP_EN)
	static unsigned char TS_Init_Step_Sub;
#endif
	if(TS_Init_Step == 0)
	{
#if (TS_ACQ_TIMES > 1)
		for(i = 0; i < TS_Cnt; i++)
		{	
			TS_DataSum[i] = 0;
		}
		TS_Acq_Counter = 0;
#endif
#if TK_FREQ_JUMP_EN
		NowTKFreqIndex = 0;
		TKCFG = TKDIV(TKDIV_VAL2)|TKTMS(TKTMS_VAL);	
		TS_Init_Step_Sub = 0;
#endif
		TS_CycleScanDoneFlag = 0;
		TS_HalfSecCnt = 0;
		TS_Index = 0;
		TS_ScanStart();	
#if POWER_ON_WAIT_TK_STABLE_EN
		TS_Init_Step = 1;		
		TS_Init_Step_Sub = 0;
		TS_ScanTimes = 5;
#else
		TS_Init_Step = 2;
		TS_ScanTimes = 50;			
#endif
	}
#if POWER_ON_WAIT_TK_STABLE_EN
	else if(TS_Init_Step == 1)
	{
		if(TS_CycleScanDoneFlag)
		{
			TS_CycleScanDoneFlag = 0;
			if(TS_Init_Step_Sub == 0)
			{
				if(--TS_ScanTimes)
				{				
					return;
				}
				for(i = 0; i < TS_Cnt+1; i++)
				{
					TS_PostData[i] = TS_RawData[i];
				}
				TS_Init_Step_Sub = 1;
				TS_AreaConfirmTimer[0] = 40;
			}			
			else if(TS_Init_Step_Sub == 1)
			{
				if(!TS_AreaConfirmTimer[0])
				{
					int delta;
					for(i = 0; i < TS_Cnt+1; i++)
					{
						delta = (int)TS_PostData[i] - (int)TS_RawData[i];
						if((delta > NOISE_THRESHOLD) || (delta < -NOISE_THRESHOLD))
						{
							TS_Init_Step_Sub = 0;
							return;
						}
					}			
					TS_Init_Step = 2;
					TS_ScanTimes = 10;	
				}
			}
		}
	}
#endif
	else if(TS_Init_Step == 2)
	{
		if(TS_CycleScanDoneFlag)
		{
			TS_CycleScanDoneFlag = 0;
			if(--TS_ScanTimes)
			{				
				return;
			}
#if TK_FREQ_JUMP_EN
			if(TS_Init_Step_Sub == 0)
			{
				for(i = 0; i < TS_Cnt+1; i++)
				{
					TS_JumpFreqData[0][i] = TS_RawData[i];
				}
				TS_Init_Step_Sub++;

				NowTKFreqIndex = 1;
				TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);			
				TS_ScanTimes = 3;						
				return;
			}
#endif
			TS_RefCHBaseLineAdjuTimer = 0;
			for(i = 0; i < TS_Cnt+1; i++)
			{	
				for(j = 0; j < FILTER_COUNT; j++)
				{
					TS_FilterBuf[i][j] = TS_RawData[i];
				}
				TS_FilterPosIdx[i] = 0;
				
#if TK_FREQ_JUMP_EN
				TS_JumpFreqData[1][i] = TS_RawData[i];
#endif
				
				if(i == TS_Cnt) break;
				TS_BaseLineData[i] = TS_RawData[i];			
				TS_FirstAreaData[i] = TS_RawData[i]; 
#if TK_BASE_TRIM_WHILE_KEY_PRESSED
				RefChDataBak[i] = TS_RawData[OPENED_TS_COUNT];
				TS_BaseLineDataBak[i] = TS_BaseLineData[i];
#endif					
#if (SUPPORT_KEY && SUPPORT_WHEEL_SLIDER)
				if(i < KEY_CH_COUNT)
				{
#if TK_SENSITIVE_AUTO_TRIM_EN
					TK_TouchThdTrim(i);
#else
					TSKey_FingerThd[i] = TS_KEY_CH_INFO_SEQ[i][1];
#endif
					TS_AreaConfirmTimerSet(i,AREA_PNOISE);
				}
				else
				{
					TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
				}
#elif SUPPORT_KEY
#if TK_SENSITIVE_AUTO_TRIM_EN
				TK_TouchThdTrim(i);
#else
				TSKey_FingerThd[i] = TS_KEY_CH_INFO_SEQ[i][1];
#endif
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);				
#elif SUPPORT_WHEEL_SLIDER
				TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
#endif
			}	
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
			for(i = 0; i < REF_CH_DATA_BUF_SIZE; i++)
			{
				RefChDataBuf[i] = TS_PostData[OPENED_TS_COUNT];
			}
			RefChDataBufIdx = 0;
#endif		
#endif			
#if (DEBUG)
			Debug_ParamLoad();
#endif		
			TS_State = TS_DEAL;	
		}
	}
}
#if SUPPORT_KEY
#if TK_SHARE_LED_EN
void TKLED_Set(unsigned char ch,unsigned char mode)
{
	unsigned char real_ch,idx,mask_bit;
	switch(mode)
	{
		case LED_ON:
		case LED_OFF:
			real_ch = TS_KEY_CH_INFO_SEQ[ch][0];
			idx = real_ch>>3;
			mask_bit = (real_ch&0x07);
			if(mode == LED_ON)
			{
				if(idx == 0)  TLDAT0 |= 1<<mask_bit;
				else					TLDAT1 |= 1<<mask_bit;	
			}
			else
			{
				if(idx == 0)  TLDAT0 &= ~(1<<mask_bit);
				else					TLDAT1 &= ~(1<<mask_bit);
			}
			break;
		case LED_ALL_OFF:
			TLDAT0 = 0;
			TLDAT1 = 0;
			break;
	}
}
void TKLED_Update(void)
{
	static TYPE_SN xdata PrevTKSN = 0;
	unsigned char i;
	if(PrevTKSN == KeysFlagSN) return;
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(KeysFlagSN & MASK_TAB[i])
		{
			TKLED_Set(i,LED_ON);
		}
		else
		{
			TKLED_Set(i,LED_OFF);
		}
	}
	PrevTKSN = KeysFlagSN;
}
#endif
#if TK_SENSITIVE_AUTO_TRIM_EN
void TK_TouchThdTrim(unsigned char ch)
{
	unsigned int b1,b2,th1,c;
	unsigned long int cal_tmp1;
	unsigned int cal_tmp2;
		
	b1 = TK_BASELINE_VALUE_INFO_SEQ[ch];
	th1 = TS_KEY_CH_INFO_SEQ[ch][1];
	b2 = TS_BaseLineData[ch];
	cal_tmp1 = ((unsigned long int)b1*(unsigned long int)b2);
	c = (unsigned int)(cal_tmp1/(b1-th1)) - b2;
	cal_tmp2 = (unsigned int)(cal_tmp1/(b1+c));
 	TSKey_FingerThd[ch] = b2 - cal_tmp2;
}
#endif
#if SUPPORT_ANTI_WATER_FUNCTION
unsigned char AntiWaterModeGetMaxDeltaCh(void)
{
	unsigned char i;
	unsigned long int CalcTemp1;
	unsigned int CalcTemp2,CalcTemp3;
	int Delta;
	int max_delta;
	char max_index;
	max_delta = 0;
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(i == 0)
		{
			Delta = (int)TS_BaseLineData[i] - (int)TS_PostData[i];
		}
		else
		{
			CalcTemp1 = 	(unsigned long int)TS_PostData[i] * (unsigned long int)TS_BaseLineData[0];
			CalcTemp2 =  	(unsigned int)(CalcTemp1/TS_BaseLineData[i]);
			CalcTemp3 = 	TS_PostData[i] + TS_BaseLineData[0] - CalcTemp2;
			CalcTemp2 = 	(unsigned int)(CalcTemp1/CalcTemp3);	
			Delta 		= 	(int)TS_BaseLineData[0] - (int)CalcTemp2;						
		}
		if(max_delta < Delta)
		{
			max_delta = Delta;
			max_index = i;
		}
	}
	return max_index;
}
#endif
#endif
#if SUPPORT_KEY
void TSKey_DataDeal(void)
{
	unsigned char i;
	unsigned char  TouchArea,NowArea;		
#if SUPPORT_COVER_PANAL_AFTER_POWERON
	unsigned char PanalToggleCount = 0;
#endif
	for(i = 0; i < KEY_CH_COUNT; i++)
	{	
#if SUPPORT_ANTI_WATER_FUNCTION
		if(KeyPressedFlag)
		{
			if(PressedKeyIndex != i)
			{
				TS_FirstAreaData[i] = TS_BaseLineData[i];
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
				continue;		
			}
		}
#endif
		TouchArea = TS_GetDataArea(i,TS_FirstAreaData[i],NOISE_THRESHOLD,(bit)(PreKeysFlagSN & MASK_TAB[i]));
		NowArea   = TS_GetDataArea(i,TS_PostData[i],NOISE_THRESHOLD,(bit)(PreKeysFlagSN & MASK_TAB[i]));
		
		if((NowArea != AREA_PNOISE)&&(NowArea != AREA_NNOISE))
		{
			TS_StableFlag = 0;		
		}
#if SUPPORT_COVER_PANAL_AFTER_POWERON
		if((NowArea == AREA_PNOISE_PLUS) || (NowArea == AREA_FINGER_TOUCH))
		{
			PanalToggleCount++;
		}
#endif
		if(TouchArea == AREA_FINGER_TOUCH)
		{
			if(NowArea == AREA_FINGER_TOUCH)
			{
				if(!(PreKeysFlagSN & MASK_TAB[i]))
				{
					if(!TS_AreaConfirmTimer[i])
					{		
						PreKeysFlagSN |= MASK_TAB[i];		
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
						TSKey_LongTouchLimitTimer[i] = FINGER_LONG_TOUCH_TIME_LIMIT;
#endif
						TS_AreaConfirmTimer[i] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;	
					}
				}
				else
				{	
#if SUPPORT_ANTI_WATER_FUNCTION		
					if(i != AntiWaterModeGetMaxDeltaCh())
					{
						goto ANTI_WATER_MODE_KEY_RELEASE;
					}
#endif
					
#if TK_BASE_TRIM_WHILE_KEY_PRESSED					
					TS_BaseLineData[i] = ((unsigned long int)TS_BaseLineDataBak[i]*TS_PostData[OPENED_TS_COUNT])/RefChDataBak[i];
#endif		
					
					TS_AreaConfirmTimer[i] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
					if(!TSKey_LongTouchLimitTimer[i])
					{
						PreKeysFlagSN &= ~MASK_TAB[i];
						TS_FirstAreaData[i] = TS_PostData[i];
						TS_BaseLineData[i] 	= TS_PostData[i];
#if TK_SENSITIVE_AUTO_TRIM_EN
						TK_TouchThdTrim(i);
#endif
						TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
#if SUPPORT_ANTI_WATER_FUNCTION
						KeyPressedFlag = 0;
						break;
#endif						
					}							
#endif					
				}				
			}
			else
			{
				if(PreKeysFlagSN & MASK_TAB[i]) 
				{
					if(!TS_AreaConfirmTimer[i])
					{
#if SUPPORT_ANTI_WATER_FUNCTION
ANTI_WATER_MODE_KEY_RELEASE:						
						KeyPressedFlag = 0;
#endif
						PreKeysFlagSN &= ~MASK_TAB[i];

						TS_FirstAreaData[i] = TS_BaseLineData[i];
						TS_AreaConfirmTimerSet(i,AREA_PNOISE);
#if SUPPORT_ANTI_WATER_FUNCTION
						break;
#endif
					}					
				}			
				else
				{
					TS_FirstAreaData[i] = TS_PostData[i];
					TS_AreaConfirmTimerSet(i,NowArea);
				}	
			}	
			continue;						
		}	
		else
		{
			if(NowArea == AREA_FINGER_TOUCH)
			{
				TS_FirstAreaData[i] = TS_PostData[i];
				TS_AreaConfirmTimerSet(i,AREA_FINGER_TOUCH);
				continue;		
			}	
		}
		if(PreKeysFlagSN != 0) 
		{
			TS_FirstAreaData[i] = TS_BaseLineData[i];
			TS_AreaConfirmTimerSet(i,AREA_PNOISE);		
			continue;			
		}
		if(TS_AreaDeviateDetection(TS_FirstAreaData[i],TS_PostData[i],NOISE_THRESHOLD))	   //判断偏差是否在允许范围内
		{	
			if(!TS_AreaConfirmTimer[i])
			{
				TS_FirstAreaData[i] = TS_PostData[i];
				TS_BaseLineData[i] 	= TS_PostData[i];

#if TK_SENSITIVE_AUTO_TRIM_EN
				TK_TouchThdTrim(i);
#endif
				
#if TK_BASE_TRIM_WHILE_KEY_PRESSED
				RefChDataBak[i] = TS_PostData[OPENED_TS_COUNT];
				TS_BaseLineDataBak[i] = TS_BaseLineData[i];
#endif				
				TS_AreaConfirmTimerSet(i,AREA_PNOISE);	
			}	
		}
		else
		{
			TS_FirstAreaData[i] = TS_PostData[i];	
			TS_AreaConfirmTimerSet(i,NowArea);		
		}
	}	 	
#if SUPPORT_ANTI_WATER_FUNCTION
	if(KeysFlagSN == 0)
	{
		if(PreKeysFlagSN != 0)
		{
			PressedKeyIndex = AntiWaterModeGetMaxDeltaCh();
			PreKeysFlagSN = MASK_TAB[PressedKeyIndex];
#if (FINGER_LONG_TOUCH_TIME_LIMIT > 0)
			TSKey_LongTouchLimitTimer[PressedKeyIndex] = FINGER_LONG_TOUCH_TIME_LIMIT;
#endif
			TS_AreaConfirmTimer[PressedKeyIndex] = FINGER_TOUCH_RELEASE_CONFIRM_TIME;	
			KeyPressedFlag = 1;
		}
	}
#endif
#if SUPPORT_COVER_PANAL_AFTER_POWERON
	if(!PanalCoverJudgeFlag)
	{
		if(PreKeysFlagSN != 0)
		{
			if(KeysFlagSN == 0)
			{
				PanalCoverJudgeFlag = 1;
				PanalCoverJudgeTimer = PANAL_COVER_JUDGE_TIME; 		
			}
			else
			{
				if((PanalToggleCount >= JUDGE_TK_NUM)||(TS_RefChAbnormalJudge()))
				{
					PreKeysFlagSN = 0;
					PanalCoverJudgeFlag = 0;
					TS_BaseLineForceUpdate();
				}
				KeysFlagSN  = PreKeysFlagSN;
			}
		}
		else
		{
			KeysFlagSN  = PreKeysFlagSN;
		}
	}
	else
	{
		if(!PanalCoverJudgeTimer)
		{
			PanalCoverJudgeFlag = 0;
			KeysFlagSN = PreKeysFlagSN;
		}
		else
		{
			if((PanalToggleCount >= JUDGE_TK_NUM)||(TS_RefChAbnormalJudge()))
			{
				PreKeysFlagSN = 0;
				PanalCoverJudgeFlag = 0;
				TS_BaseLineForceUpdate();
			}			
		}
	}
#else
#if ANTI_SPEAKER_EN
	if((PreKeysFlagSN != 0)&&(KeysFlagSN == 0))
	{
		if(TS_RefChAbnormalJudge())
		{
			PreKeysFlagSN = 0;
			
#if SUPPORT_ANTI_WATER_FUNCTION
			KeyPressedFlag = 0;
#endif
			TS_BaseLineForceUpdate();		
		}
	}
#endif
	KeysFlagSN  = PreKeysFlagSN;

#endif
	if(KeysFlagSN != 0) 
	{
		ActiveTouchType = 1;
	}
	else
	{
		ActiveTouchType = 0;
	}
}
#endif
#if SUPPORT_WHEEL_SLIDER
void TS_WheelSliderDeal(void)
{
	unsigned char i;
	unsigned int   Delta,Position;
	bit WheelSliderTogFlag = 0;
	TS_BaseCh = KEY_CH_COUNT; 
	if(!W_S_RefChSet)
	{
		W_S_RefChSet = 1;		
		SetWheelSliderRefCh(WHEEL_SLIDER0_CH_COUNT);
	}
	
#if PRINT_WHEEL_SLIDER_DATA_EN
	TK_Debug_UartPutChar(0xaa);
	for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
	{						
		if(TS_BaseLineData[i] > TS_PostData[i])
		{
			Delta = (int)TS_BaseLineData[i] - (int)TS_PostData[i];	
		}
		else
		{
			Delta = 0;
		}						
		TK_Debug_UartPutChar(i);
		TK_Debug_UartPutChar(TS_PostData[i]>>8);
		TK_Debug_UartPutChar(TS_PostData[i]);			
		TK_Debug_UartPutChar(TS_BaseLineData[i]>>8);
		TK_Debug_UartPutChar(TS_BaseLineData[i]);	
		TK_Debug_UartPutChar(Delta>>8);	
		TK_Debug_UartPutChar(Delta);								
	}				
#endif
#if (WHEEL_OR_SLIDER_DEF0	== SLIDER)
	Position = SliderTouchJudge(WHEEL_SLIDER0_CH_COUNT,WHEEL_SLIDER0_TOUCH_THD);
#elif (WHEEL_OR_SLIDER_DEF0	== WHEEL)
	Position = WheelTouchJudge(WHEEL_SLIDER0_CH_COUNT,WHEEL_SLIDER0_TOUCH_THD);
#endif
	if(Position != -1)
	{
		TS_StableFlag = 0;
	}
	if(WheelSliderState == WHEEL_SLIDER_NO_TOUCH)
	{
		if(!WheelSliderTouchFlag)
		{
			if(Position != -1)
			{
				WheelSliderTouchFlag = 1;	
				TSWheelSlider_TouchConfirmTimer = WHEEL_SLIDER_TOUCH_CONFIRM_TIME;				
			}
			else
			{
				for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
				{						
					if(TS_FirstAreaData[i] > TS_PostData[i]) 
					{
						Delta 	= TS_FirstAreaData[i] - TS_PostData[i];
					}
					else
					{
						Delta 	= TS_PostData[i] - TS_FirstAreaData[i];
					}					
					if(Delta <= WHEEL_SLIDER0_NOISE_THD) 
					{
						if(!TS_AreaConfirmTimer[i])
						{
							TS_FirstAreaData[i] = TS_PostData[i];
							TS_BaseLineData[i] 	= TS_PostData[i];
							TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
						}							
					}
					else
					{
						TS_FirstAreaData[i] = TS_PostData[i];
						TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
					}
				}
			}			
		}	
		else
		{	
			if(Position != -1)
			{
				if(!TSWheelSlider_TouchConfirmTimer)
				{
						WheelSliderState = WHEEL_SLIDER_TOUCH;	
#if (WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT > 0)
						TSWheelSlider_LongTouchLimitTimer = WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT;
#endif
				}	
			}
			else
			{
				WheelSliderTouchFlag = 0;
				for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
				{
					TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
				}
			}
		}				
	}
	else if(WheelSliderState == WHEEL_SLIDER_TOUCH)
	{		
#if (WHEEL_SLIDER_LONG_TOUCH_TIME_LIMIT > 0)
		if(!TSWheelSlider_LongTouchLimitTimer)
		{
			for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
			{
				TS_FirstAreaData[i] = TS_PostData[i];
				TS_BaseLineData[i] 	= TS_PostData[i];
			}
			WheelSliderTouchFlag = 0;
			goto WHEEL_SLIDER_RELEASE;
		}
#endif
		if(WheelSliderTouchFlag)
		{
			if(Position == -1)	
			{
				WheelSliderTouchFlag = 0;
				TSWheelSlider_TouchConfirmTimer = WHEEL_SLIDER_TOUCH_RELEASE_CONFIRM_TIME;		
			}
		}
		else						 
		{
			if(Position == -1)	
			{
				if(!TSWheelSlider_TouchConfirmTimer)
				{
WHEEL_SLIDER_RELEASE:
					WheelSliderState = WHEEL_SLIDER_NO_TOUCH;	
					WheelSliderCapRateFilter = 0;
					WheelSliderPosition = -1;
					for(i = TS_BaseCh; i < TS_BaseCh + WHEEL_SLIDER0_CH_COUNT; i++)
					{
						TS_AreaConfirmTimer[i] = WHEEL_SLIDER_BASELINE_UPDATE_TIME;
					}
				}
			}
			else
			{
				WheelSliderTouchFlag = 1;				
			}
		}		
	}		
	if(WheelSliderState == WHEEL_SLIDER_TOUCH)
	{
		if(Position != -1)
		{
			WheelSliderPosition = Position;
		}	
#if PRINT_WHEEL_SLIDER_POSITION_EN
		TK_Debug_UartPutChar(WheelSliderPosition/100+0x30);		
		TK_Debug_UartPutChar((WheelSliderPosition%100)/10+0x30);		
		TK_Debug_UartPutChar((WheelSliderPosition%10)+0x30);	

		TK_Debug_UartPutChar('\r');	
		TK_Debug_UartPutChar('\n');	
#endif
#if PRINT_WHEEL_SLIDER_RATE_EN
		{
			unsigned char DeltaRate;
			DeltaRate = WheelSliderCapRateFilter/4;
			TK_Debug_UartPutChar(WheelSliderMaxIdx + 0x30);	
			TK_Debug_UartPutChar(' ');
				
			TK_Debug_UartPutChar(DeltaRate/100+0x30);		
			TK_Debug_UartPutChar((DeltaRate%100)/10+0x30);		
			TK_Debug_UartPutChar((DeltaRate%10)+0x30);	
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');					
		}
#endif
	}
	else
	{
		WheelSliderPosition = -1;	
	}

	if(WheelSliderPosition != -1)
	{
		ActiveTouchType = 2;
	}
	else
	{
		ActiveTouchType = 0;
	}
}
#endif	

void TS_init(void)
{
	unsigned char i,ch_idx;
#if (DEBUG)
	Debug_init();
#endif

	TS_Cnt 		= OPENED_TS_COUNT;
	ch_idx = 0;
	for(i = 0;i < OPENED_TS_COUNT; i++)
	{
#if (SUPPORT_KEY && SUPPORT_WHEEL_SLIDER)
		if(i < KEY_CH_COUNT)
		{
			TS_CH[ch_idx++] = TS_KEY_CH_INFO_SEQ[i][0];
		}
		else
		{
			TS_CH[ch_idx++] = TS_WHEEL_SLIDER_CH_SEQ[i-KEY_CH_COUNT];
		}
#elif SUPPORT_KEY
		TS_CH[ch_idx++] = TS_KEY_CH_INFO_SEQ[i][0];
#elif SUPPORT_WHEEL_SLIDER
		TS_CH[ch_idx++] = TS_WHEEL_SLIDER_CH_SEQ[i];
#endif
	}
	CKCON |= ILCKE;
	TMCON = TME(1);
	TMSNU = 0;	
	INT3EN =1;
	
	TS_IO_init();
	
	
	TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);		
#if (TK_CHARGE_REF_SELECT == SOURCE_VDD)
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(VRS_VAL);
	TKPWC = TKPC(TK_PC_VAL)|VDS(0)|VIRS(0)|TKPWS(0)|TKCVS(0);		
#elif (TK_CHARGE_REF_SELECT == SOURCE_INNER) 
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(0);
	TKPWC = TKPC(TK_PC_VAL)|VDS(VDS_VAL)|VIRS(VIRS_VAL)|TKPWS(1)|TKCVS(1);		
#endif
 	
#if SUPPORT_KEY
#if TK_SHARE_LED_EN
	TLEN0 	= 0xFF;
	TLDAT0 = 0x00;
	TLEN1 	= 0x1F;
	TLDAT1 = 0x00;

	TLCON = TLEIE(0)|TLKIE(0)|TLLIE(0)|TLLVS(0)|TLPOL(0);
	TLCKS = TLCKS(2);

	TLCNTKH = 0x00;		
	TLCNTKL = 0x20;

	TLCNTLH = LED_DRV_CNT/256;		
	TLCNTLL = LED_DRV_CNT%256;

	TLDIV = 0;
	TLCOMS = 0x01;
	P01F 	 = 6;
	P01C		&= (1<<5);
#endif
#endif
	INT3EN = 1; 
	
	TS_CycleScanDoneFlag = 0;
#if SUPPORT_KEY
	KeysFlagSN = 0;
	PreKeysFlagSN = 0;
#endif	
	ActiveTouchType = 0;
#if SUPPORT_KEY
#if SUPPORT_COVER_PANAL_AFTER_POWERON
	PanalCoverJudgeFlag = 0;
#endif
#endif
#if SUPPORT_TOUCH_SLEEP_MODE
	EnterStopScanTimer = ENTER_STOP_MODE_TIME;
  TS_SleepEn = 1;
	TS_SleepMode = 0;
#endif
#if SUPPORT_WHEEL_SLIDER
	W_S_RefChSet = 0;

	WheelSliderState = WHEEL_SLIDER_NO_TOUCH;
	WheelSliderTouchFlag = 0;
	WheelSliderPosition = -1;		
	WheelSliderCapRateFilter = 0;
#endif
	TS_State = TS_INIT;
	TS_Init_Step = 0;
	
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN	
	RefChDataTimer = 0;
#endif
#endif

	MainLoopCnt1 = MainLoopCnt2 = 0;
#if SUPPORT_KEY	
#if GENERATE_TS_KEY_EN
	TK_State = TK_STATE_RELEASE;
	TS_Key = 0;
#endif
#endif
}

void TS_Action(void)
{
	switch(TS_State)
	{
		case TS_INIT:
			TS_RunInit();			
			break;
		case TS_DEAL:		
			if(TS_CycleScanDoneFlag)
			{			
				TS_CycleScanDoneFlag = 0;
				
				MainLoopCnt1 = MainLoopCnt2 + 1;
				
#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
				TS_RefChCheck();
#endif
#endif
				TS_DataFiltering();
				TS_StableFlag = 1;
#if SUPPORT_KEY	
				if(ActiveTouchType != 2)
				{
					TSKey_DataDeal();	
				}
#endif
#if (DEBUG)
				Debug_ParamLoad();
#endif		
#if SUPPORT_WHEEL_SLIDER
				if(ActiveTouchType != 1)
				{
					TS_WheelSliderDeal();
				}
#endif				
#if SUPPORT_TOUCH_SLEEP_MODE
				if(!TS_StableFlag || !TS_SleepEn || (PCON & BIT2))	// 在仿真模式不进入STOP模式
				{
					EnterStopScanTimer = ENTER_STOP_MODE_TIME;
				}			
				if(!EnterStopScanTimer&&TS_SleepEn)
				{
#if ENTER_SLEEP_PRINT_EN
					TK_Debug_UartPutChar('s');	
					TK_Debug_UartPutChar('l');	
					TK_Debug_UartPutChar('e');	
					TK_Debug_UartPutChar('e');	
					TK_Debug_UartPutChar('p');	
					TK_Debug_UartPutChar('\r');	
					TK_Debug_UartPutChar('\n');		
					Delay_ms(1);
#endif
					TS_EnterSleepMode();		
#if ENTER_SLEEP_PRINT_EN					
					TK_Debug_UartPutChar('e');	
					TK_Debug_UartPutChar('x');	
					TK_Debug_UartPutChar('i');	
					TK_Debug_UartPutChar('t');	
					TK_Debug_UartPutChar('\r');	
					TK_Debug_UartPutChar('\n');		
#endif
				}
#endif										
			}
			if(TS_HalfSecCnt >= 5)
			{
				TKCON = 0;
				TKIF = 0x3F;
				TS_init();
			}
			break;
		default:
			break;
	}
#if SUPPORT_KEY	
#if TK_SHARE_LED_EN
	TKLED_Update();
#endif
#if GENERATE_TS_KEY_EN
	TS_GetKey();
#endif
#endif
}
#if SUPPORT_TOUCH_SLEEP_MODE
void TS_SetChannel(unsigned char index,unsigned char ch);
void TS_SleepScanStart(void)
{	
	unsigned char i;	 
	for(i = 0; i < 6; i++)					
	{
		if(TS_Index + i < TS_Cnt)
		{
			TS_SetChannel(i,(TS_CH[TS_Index+i])+1);
		}
		else
		{
			TS_SetChannel(i,0);
		}
	}
	TKCON |= TKST(1);
}
void TS_EnterSleepMode(void)
{
//省电模式参数配置
	#define STOP_TKDIV_VAL			0
	#define STOP_TKTMS_VAL			15		//放电时间
	#define STOP_VRS_VAL				7			//比较器阈值	
	unsigned char TS_SampleComplete = 0,i;
	unsigned int xdata WakeUp_PThdVal[OPENED_TS_COUNT];
	unsigned int xdata WakeUp_NThdVal[OPENED_TS_COUNT];	
	WORD_UNION TS_Data;

	TKCON = 0;
	TKIF = 0x3F;
	
	TS_SleepMode = 1;
#if SUPPORT_KEY	
#if TK_SHARE_LED_EN
	TLEN0 	= 0x00;
	TLDAT0  = 0x00;
	TLEN1 	= 0x00;
	TLDAT1 	= 0x00;
	P01F 	 	= HIGH_Z|PU_EN;
	P01C		&= (1<<5);	//选择弱上拉
#endif	
#endif	
	TMCON &= ~TME(1);
	TMCON |= TMF;	
	
	TKCON = (TKCON&0xF8) | VRS(STOP_VRS_VAL);
	TKCON &= ~TKIE(1);
	TKCFG = TKDIV(STOP_TKDIV_VAL)|TKTMS(STOP_TKTMS_VAL);		

#if (OPENED_TS_COUNT%6 == 0)
	TKMTS = (SLEEP_MODE_SCAN_INTERVAL_TIME*6)/(OPENED_TS_COUNT);
#else
	TKMTS = (SLEEP_MODE_SCAN_INTERVAL_TIME)/((OPENED_TS_COUNT/6)+1);
#endif
	
	TKPWC = TKPC(1)|VDS(0)|VIRS(0)|TKPWS(0)|TKCVS(0);		//省电设为VDD充电
	
#ifdef LVD_RST_ENABLE
	LVDCON = 0;	
#endif		
	I2CCON = 0;
	CKCON = 0;
		
	MECON |= BIT6;
	PWCON = (PWCON&0xF0)|0x07;	

	TS_Index = 0;
	TS_SleepScanStart();
	WDFLG = 0xA5;
			
	TMCON = TME(1);
	TMSNU = 127;	
	
	while(1)
	{
		if(TS_SampleComplete)
		{
			CKCON &= ~IHCKE;		
			CKCON = (CKCON&0xFE) | CKSEL_IRCL;	
			EA = 0;
			PCON |= (1<<1);
			_nop_();
			_nop_();
			_nop_();
			CKCON |= IHCKE;													
			CKCON = (CKCON&0xFE) | CKSEL_IRCH;	
			EA = 1;
		}
		if(TS_HalfSecCnt >= 5)
		{
			break;
		}
		if(TKIF != 0)
		{
			if(TS_HalfSecCnt) TS_HalfSecCnt--;
			for(i = 0; i < 6; i++)
			{
				if(TKIF & (1<<i))
				{
					TKIF = (1<<i);	
					if(i == 0) 
					{
						TS_Data.bVal[0] = TK0MSH;
						TS_Data.bVal[1] = TK0MSL;
					}
					else if(i == 1) 
					{
						TS_Data.bVal[0] = TK1MSH;
						TS_Data.bVal[1] = TK1MSL;
					}
					else if(i == 2) 
					{
						TS_Data.bVal[0] = TK2MSH;
						TS_Data.bVal[1] = TK2MSL;
					}
					else if(i == 3) 
					{
						TS_Data.bVal[0] = TK3MSH;
						TS_Data.bVal[1] = TK3MSL;
					}
					else if(i == 4) 
					{
						TS_Data.bVal[0] = TK4MSH;
						TS_Data.bVal[1] = TK4MSL;
					}
					else if(i == 5) 
					{
						TS_Data.bVal[0] = TK5MSH;
						TS_Data.bVal[1] = TK5MSL;
					}
					if(TS_SampleComplete == 0)
					{
						WakeUp_PThdVal[TS_Index+i] = TS_Data.wVal - SLEEP_TOUTH_THD;
						WakeUp_NThdVal[TS_Index+i] = TS_Data.wVal + SLEEP_TOUTH_THD;
					}
					else 
					{
						if((TS_Data.wVal <= WakeUp_PThdVal[TS_Index+i])||(TS_Data.wVal >= WakeUp_NThdVal[TS_Index+i]))
						{
							goto SLEEP_EXIT;			
						}
					}
				}
			}
			if(TS_Index+6 < TS_Cnt)
			{
				TS_Index += 6;
			}
			else 
			{
				TS_Index = 0;
				if(TS_SampleComplete == 0)
				{
					TS_SampleComplete = 1;				
					TKCON |= TMEN(1);					
				}
			}
			TS_SleepScanStart();	
			WDFLG = 0xA5;
		}
	}
SLEEP_EXIT:
	TKCON = 0;
	TKIF = 0x3F;
	PWCON = (PWCON&0xF0)|0x0D;	

	TKCFG = TKDIV(TKDIV_VAL)|TKTMS(TKTMS_VAL);		
#if (TK_CHARGE_REF_SELECT == SOURCE_VDD)
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(VRS_VAL);
	TKPWC = TKPC(TK_PC_VAL)|VDS(0)|VIRS(0)|TKPWS(0)|TKCVS(0);		
#elif (TK_CHARGE_REF_SELECT == SOURCE_INNER) 
	TKCON = TKST(0)|TKIE(1)|TMEN(0)|TWKE(0)|VRS(0);
	TKPWC = TKPC(TK_PC_VAL)|VDS(VDS_VAL)|VIRS(VIRS_VAL)|TKPWS(1)|TKCVS(1);		
#endif
#if SUPPORT_KEY	
#if TK_SHARE_LED_EN
	TLEN0 	= 0xFF;
	TLEN1 	= 0x1F;
	P01F 	 = 6;
#endif
#endif
	CKCON |= ILCKE;
	TMCON &= ~TME(1);
	TMCON |= TMF;
	Delay_50us(1);
	TMCON = TME(1);
	TMSNU = 0;	
	TS_Index = 0;
	TS_ScanStart();
	EnterStopScanTimer = ENTER_STOP_MODE_TIME;
	TS_SleepMode = 0;
#ifdef LVD_RST_ENABLE
	LVDCON = 0xE3;	//设置LVD复位电压为2V
#endif							
}
#endif
/*********************************************************************************************************************/
#if SUPPORT_KEY	
#if GENERATE_TS_KEY_EN
#if GENERATE_DOUBLE_KEY_EN
typedef struct 
{	
	unsigned char 	TogKeyNum;
	unsigned char 	TogKeyList[2];
}
T_TogKeyInfo;
#endif
code unsigned char TS_KEY_TAB[]=
{
	K1,K2,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13
};
#if GENERATE_DOUBLE_KEY_EN
void TS_GetTogKeyInfor(T_TogKeyInfo *pKeyInfo)
{
	unsigned char i,index;
	pKeyInfo->TogKeyNum = 0;
	index = 0;
	for(i = 0; i < KEY_CH_COUNT; i++)
	{
		if(KeysFlagSN & MASK_TAB[i])
		{
			pKeyInfo->TogKeyNum++;
			
			if(pKeyInfo->TogKeyNum <= 2)
			{
				pKeyInfo->TogKeyList[index++] = TS_KEY_TAB[i];
			}
		}
	}
}
#endif
#if PRINT_TS_KEY_EN
void Hex2CharPrint(unsigned int integar)
{
	unsigned char CharBuf[4];
	unsigned char i, temp;
	for(i = 0; i < 4; i++)
	{
		temp = (unsigned char)(integar&0x0F);
		if(temp >= 0x0A)
		{
			CharBuf[i] = (temp - 0x0A) + 'A';
		}
		else
		{
			CharBuf[i] = temp + '0';
		}
		integar >>= 4;
	}
	TK_Debug_UartPutChar('0');	
	TK_Debug_UartPutChar('x');	
	TK_Debug_UartPutChar(CharBuf[2]);
	TK_Debug_UartPutChar(CharBuf[1]);
	TK_Debug_UartPutChar(CharBuf[0]);
}
#endif
void TS_GetKey(void)
{
	static unsigned int KeyBak;	
	static bit LongFlag;
#if GENERATE_DOUBLE_KEY_EN
	T_TogKeyInfo KeyInfo;
	TS_GetTogKeyInfor(&KeyInfo);
#else
	static unsigned char KeyidxBak;
	unsigned char i;
#endif
	TS_Key = 0;	
	if(TK_State == TK_STATE_RELEASE)
	{
#if GENERATE_DOUBLE_KEY_EN
		if(KeyInfo.TogKeyNum != 0)
		{			
			if(KeyInfo.TogKeyNum == 1)
			{
				KeyBak = (unsigned int)KeyInfo.TogKeyList[0];
				TK_State = TK_STATE_SINGLE_KEY_PRESS;				
			}
			else if(KeyInfo.TogKeyNum == 2)
			{
				KeyBak = ((unsigned int)KeyInfo.TogKeyList[0]<<5)|(unsigned int)KeyInfo.TogKeyList[1];
				TK_State = TK_STATE_DOUBLE_KEY_PRESS;
			}
			TS_Key = KeyBak;
			LongFlag = 0;
			TS_LongKeyTimer = TS_LONG_START_TIME;
		}
#else
		if(KeysFlagSN != 0)
		{
			for(i = 0; i < KEY_CH_COUNT; i++)
			{
				if(KeysFlagSN & MASK_TAB[i])
				{
					KeyidxBak = i;
					KeyBak = TS_KEY_TAB[i];
					break;
				}		
			}				
			TS_Key = KeyBak;
			LongFlag = 0;
			TS_LongKeyTimer = TS_LONG_START_TIME;
			TK_State = TK_STATE_SINGLE_KEY_PRESS;		
		}
#endif
	}
	else if(TK_State == TK_STATE_SINGLE_KEY_PRESS)
	{
#if GENERATE_DOUBLE_KEY_EN	
		if(KeyInfo.TogKeyNum == 1)
		{
			if(KeyBak == (unsigned int)KeyInfo.TogKeyList[0])
			{
				if(!TS_LongKeyTimer)
				{
					if(!LongFlag)
					{
						LongFlag = 1;
						TS_Key = KeyBak | KEY_LONG_START;
					}
					else
					{
						TS_Key = KeyBak | KEY_LONG;
					}
					TS_LongKeyTimer = TS_LONG_TIME;
				}				
			}
			else 
			{
				if(!LongFlag)
				{
					TS_Key = KeyBak | KEY_BREAK;
				}
				else
				{
					TS_Key = KeyBak | KEY_LONG_BREAK;
				}
				TK_State = TK_STATE_RELEASE;
			}
		}
		else if(KeyInfo.TogKeyNum == 2)
		{
			KeyBak = ((unsigned int)KeyInfo.TogKeyList[0]<<5) | (unsigned int)KeyInfo.TogKeyList[1];
			TK_State = TK_STATE_DOUBLE_KEY_PRESS;
			TS_Key = KeyBak;
			LongFlag = 0;
			TS_LongKeyTimer = TS_LONG_START_TIME;
		}
		else if(KeyInfo.TogKeyNum == 0)
		{
			if(!LongFlag)
			{
				TS_Key = KeyBak | KEY_BREAK;
			}
			else
			{
				TS_Key = KeyBak | KEY_LONG_BREAK;
			}
			TK_State = TK_STATE_RELEASE;
		}
#else
		if(KeysFlagSN & MASK_TAB[KeyidxBak])
		{
				if(!TS_LongKeyTimer)
				{
					if(!LongFlag)
					{
						LongFlag = 1;
						TS_Key = KeyBak | KEY_LONG_START;
					}
					else
					{
						TS_Key = KeyBak | KEY_LONG;
					}
					TS_LongKeyTimer = TS_LONG_TIME;
				}					
		}
		else
		{
			if(!LongFlag)
			{
				TS_Key = KeyBak | KEY_BREAK;
			}
			else
			{
				TS_Key = KeyBak | KEY_LONG_BREAK;
			}
			TK_State = TK_STATE_RELEASE;			
		}
#endif
	}
#if GENERATE_DOUBLE_KEY_EN	
	else if(TK_State == TK_STATE_DOUBLE_KEY_PRESS)
	{
		if(KeyInfo.TogKeyNum == 2)
		{
			if(KeyBak == ((unsigned int)KeyInfo.TogKeyList[0]<<5)|(unsigned int)KeyInfo.TogKeyList[1])
			{
				if(!TS_LongKeyTimer)
				{
					if(!LongFlag)
					{
						LongFlag = 1;
						TS_Key = KeyBak | KEY_LONG_START;
					}
					else
					{
						TS_Key = KeyBak | KEY_LONG;
					}
					TS_LongKeyTimer = TS_LONG_TIME;
				}					
			}
		}
		else if(KeyInfo.TogKeyNum == 0)
		{
			if(!LongFlag)
			{
				TS_Key = KeyBak | KEY_BREAK;
			}
			else
			{
				TS_Key = KeyBak | KEY_LONG_BREAK;
			}
			TK_State = TK_STATE_RELEASE;		
		}
	}
#endif
#if PRINT_TS_KEY_EN
	if(TS_Key != 0)
	{
		if((TS_Key & 0xFF00) == 0)
		{
#if GENERATE_DOUBLE_KEY_EN	
			if(TS_Key > 0x1F)
			{
				TK_Debug_UartPutChar('d');	
				TK_Debug_UartPutChar('o');	
				TK_Debug_UartPutChar('u');	
				TK_Debug_UartPutChar('b');	
				TK_Debug_UartPutChar('l');	
				TK_Debug_UartPutChar('e');			
			}
			else
			{
				TK_Debug_UartPutChar('s');	
				TK_Debug_UartPutChar('i');	
				TK_Debug_UartPutChar('n');	
				TK_Debug_UartPutChar('g');	
				TK_Debug_UartPutChar('l');	
				TK_Debug_UartPutChar('e');		
			}
			TK_Debug_UartPutChar(' ');	
#endif
			TK_Debug_UartPutChar('k');	
			TK_Debug_UartPutChar('e');	
			TK_Debug_UartPutChar('y');	
			TK_Debug_UartPutChar(' ');	
			TK_Debug_UartPutChar('=');	
			TK_Debug_UartPutChar(' ');	
			Hex2CharPrint(TS_Key);
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');	
		}
		else if(TS_Key & KEY_BREAK)
		{
			TK_Debug_UartPutChar('k');	
			TK_Debug_UartPutChar('e');	
			TK_Debug_UartPutChar('y');	
			TK_Debug_UartPutChar(' ');	
			TK_Debug_UartPutChar('u');	
			TK_Debug_UartPutChar('p');	
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');				
		}
		else if(TS_Key & KEY_LONG_START)
		{
			TK_Debug_UartPutChar('l');	
			TK_Debug_UartPutChar('o');	
			TK_Debug_UartPutChar('n');	
			TK_Debug_UartPutChar('g');	
			TK_Debug_UartPutChar(' ');	
			TK_Debug_UartPutChar('s');	
			TK_Debug_UartPutChar('t');	
			TK_Debug_UartPutChar('a');	
			TK_Debug_UartPutChar('r');	
			TK_Debug_UartPutChar('t');	
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');			
		}
		else if(TS_Key & KEY_LONG)
		{
			TK_Debug_UartPutChar('l');	
			TK_Debug_UartPutChar('o');	
			TK_Debug_UartPutChar('n');	
			TK_Debug_UartPutChar('g');	
			TK_Debug_UartPutChar('\r');	
			TK_Debug_UartPutChar('\n');			
		}
	}
#endif
}
#endif
#endif
/*********************************************************************************************************************/

/*********************************************************************************************************************/
#endif