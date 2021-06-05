#ifndef _TS_API_H
#define _TS_API_H

#ifdef _TK_API_C_
/***************************************************************************************************************/
/***************************************************************************************************************/											
TSState_T 	  idata TS_State;

TYPE_SN idata PreKeysFlagSN;	
TYPE_SN xdata KeysFlagSN;	
#if TK_FREQ_JUMP_EN
unsigned char xdata NowTKFreqIndex;
#endif
unsigned int  TS_Key;	
unsigned int 	TS_LongKeyTimer;
unsigned char TK_State;	

bit TS_CycleScanDoneFlag;
unsigned char idata 	TS_Cnt;			
unsigned int 	xdata 	TS_RawData[OPENED_TS_COUNT+1];
unsigned int 	xdata 	TS_BaseLineData[OPENED_TS_COUNT];
unsigned int 	xdata 	TS_FirstAreaData[OPENED_TS_COUNT];
unsigned char xdata 	TS_AreaConfirmTimer[OPENED_TS_COUNT];
unsigned int 	xdata 	TS_PostData[OPENED_TS_COUNT+1];
#if TK_FREQ_JUMP_EN
unsigned int 	xdata 	TS_JumpFreqData[2][OPENED_TS_COUNT+1];
#endif
#if (TS_ACQ_TIMES > 1)
unsigned char xdata		TS_Acq_Counter = 0;
unsigned int  xdata		TS_DataSum[OPENED_TS_COUNT+1];
#endif
#if SUPPORT_KEY
unsigned int 	xdata 	TSKey_FingerThd[KEY_CH_COUNT];
unsigned char xdata 	TSKey_LongTouchLimitTimer[KEY_CH_COUNT];
#if SUPPORT_ANTI_WATER_FUNCTION
	bit KeyPressedFlag;
	unsigned char xdata PressedKeyIndex;
#endif
#if TK_BASE_TRIM_WHILE_KEY_PRESSED
	unsigned int xdata RefChDataBak[KEY_CH_COUNT];
	unsigned int xdata TS_BaseLineDataBak[KEY_CH_COUNT];
#endif
#else
unsigned int 	xdata 	TSKey_FingerThd[1];
#endif
/***************************************************************************************************************/
/***************************************************************************************************************/
unsigned int  xdata TS_FilterBuf[OPENED_TS_COUNT+1][FILTER_COUNT];	
unsigned char xdata TS_FilterPosIdx[OPENED_TS_COUNT+1];	


unsigned char xdata TS_Init_Step;
unsigned char idata TS_RefCHBaseLineAdjuTimer;
unsigned char TS_Index;

unsigned char idata TS_CH[OPENED_TS_COUNT];	

unsigned char xdata EnterStopScanTimer;
unsigned char xdata MainLoopCnt1;
unsigned char xdata MainLoopCnt2;

#if SUPPORT_KEY
#if ANTI_SPEAKER_EN
#define REF_CH_DATA_BUF_SIZE		10
unsigned int xdata RefChDataBuf[REF_CH_DATA_BUF_SIZE];
unsigned char xdata RefChDataBufIdx;
unsigned char xdata RefChDataTimer;
#endif
#endif

bit TS_StableFlag;

#if SUPPORT_TOUCH_SLEEP_MODE
bit TS_SleepEn;
bit TS_SleepMode;
#endif

unsigned char xdata TS_HalfSecCnt;

#if SUPPORT_KEY
#if DEBUG
unsigned char 			xdata 	Key_Cnt_Debug;	
TSState_T 	  			xdata 	TS_State_Debug;
unsigned char 			xdata 	TS_CH_Debug[OPENED_TS_COUNT];	
unsigned int  			xdata 	TS_RefChBaseLineData;
unsigned int 				xdata 	TS_RefPostData;
unsigned int   xdata 	KeysFlagSN_Debug;
#endif

#if SUPPORT_COVER_PANAL_AFTER_POWERON
unsigned char PanalCoverJudgeTimer;
bit PanalCoverJudgeFlag;
#endif
#endif
#if SUPPORT_WHEEL_SLIDER
unsigned char xdata TSWheelSlider_TouchConfirmTimer;
unsigned char xdata TSWheelSlider_LongTouchLimitTimer;
unsigned char xdata WheelSliderState;
unsigned char xdata WheelSliderTouchFlag;
int xdata WheelSliderPosition;
unsigned char xdata WheelSliderRefCh;
unsigned int xdata WheelSliderCapRateFilter;
unsigned char xdata WheelSliderMaxIdx;
bit W_S_RefChSet;
#else
unsigned char xdata WheelSliderRefCh;
unsigned int xdata WheelSliderCapRateFilter;
unsigned char xdata WheelSliderMaxIdx;
#endif
unsigned char TS_BaseCh;
unsigned char ActiveTouchType;
#else
/***************************************************************************************************************/
/***************************************************************************************************************/											
extern TSState_T 	  idata TS_State;
#ifndef TS_SERVICE_C
extern TYPE_SN idata PreKeysFlagSN;	
extern TYPE_SN xdata KeysFlagSN;	
#endif
extern unsigned int  TS_Key;	
extern unsigned int 	TS_LongKeyTimer;
extern unsigned char TK_State;	

extern bit TS_CycleScanDoneFlag;
extern unsigned char 	idata 	TS_Cnt;			
extern unsigned int  	xdata 	TS_RefChRawData;					  
extern unsigned int 	xdata 	TS_RawData[];

extern unsigned int 	xdata 	TS_BaseLineData[];
extern unsigned int 	xdata 	TS_FirstAreaData[];
extern unsigned char 	xdata 	TS_AreaConfirmTimer[];
extern unsigned int 	xdata 	TS_PostData[];

extern unsigned int 	xdata 	TSKey_FingerThd[];
extern unsigned char 	xdata 	TSKey_LongTouchLimitTimer[];

/***************************************************************************************************************/
/***************************************************************************************************************/
extern unsigned char xdata TS_Init_Step;
extern unsigned char idata TS_RefCHBaseLineAdjuTimer;
extern unsigned char TS_Index;

extern unsigned char idata TS_CH[];	
extern unsigned char  TS_AcqCnt;
extern unsigned char xdata EnterStopScanTimer;

extern code unsigned int TS_CH_INFO_SEQ[][2];
extern bit TS_StableFlag;
extern bit TS_SleepEn;
extern bit TS_SleepMode;

extern unsigned char xdata TSWheelSlider_TouchConfirmTimer;
extern unsigned char xdata TSWheelSlider_LongTouchLimitTimer;

extern unsigned char xdata WheelSliderState;
extern unsigned char xdata WheelSliderTouchFlag;
extern int xdata WheelSliderPosition;
extern unsigned int xdata WheelSliderCapRateFilter;
extern unsigned char TS_BaseCh;
extern unsigned char ActiveTouchType;
extern unsigned char xdata WheelSliderRefCh;
extern bit W_S_RefChSet;
extern unsigned char xdata WheelSliderMaxIdx;
extern code unsigned int 	TS_KEY_CH_INFO_SEQ[][2];

extern code unsigned char WHEEL_SLIDER0_MAX_MIN_TAB[];
extern code unsigned char AREA_CONFIRM_TIME_TAB[];
extern code unsigned int MASK_TAB[];

#endif

void TS_init(void);
void TS_Action(void);
void TS_GetKey(void);
void TS_EnterSleepMode(void);		
void TS_ISR(void);
#endif