#ifndef _TS_SERVICE_H_
#define _TS_SERVICE_H_

void TS_IO_init(void);
void TS_ScanStart(void);
void TS_ScanContinue(void);
void TSKey_DataDeal(void);
void TS_RunInit(void);
void TS_CheckRefCh(void);
void TS_AreaConfirmTimerSet(unsigned char ts_ch, unsigned char area);
void TS_MS_ISR(void);
void TS_HS_ISR(void);
void TS_CfgPinFunc(unsigned char idx,unsigned char Func);
unsigned char TS_GetDataArea(unsigned char ts_ch,unsigned int ts_data,int noise_thd,bit key_pressed_flag);
unsigned char TS_AreaDeviateDetection(unsigned int cmp_data,unsigned int real_data,int range);
void TS_BaseLineForceUpdate(void);
void SetWheelSliderRefCh(unsigned char SliderNum);
int WheelTouchJudge(unsigned char WHEEL_SLIDER0_CH_COUNT_V,unsigned int WHEEL_SLIDER0_TOUCH_THD_V);
int SliderTouchJudge(unsigned char WHEEL_SLIDER0_CH_COUNT_V,unsigned int WHEEL_SLIDER0_TOUCH_THD_V);
#endif
