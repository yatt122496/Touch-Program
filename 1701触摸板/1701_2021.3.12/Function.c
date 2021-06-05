/***************************************************************************
*Copyright(c) 2019,深圳鹏林电子有限公司
*All rights reserved.
*
*硬    件：SN8F5703
*文件名称：Function.c
*
*当前版本：V1.0
*作    者：yehuoyan
*完成日期：2019年8月17日13:41:10
*
*取代版本：V1.0
*作    者：yehuoyan
*完成日期：


******************************************************************************/
#include "Function.h"

bit POWKEY_Flag = 0;//电源按键标志
bit ECOKEY_Flag = 0;//ECO按键标志
bit K6_Flag = 0;//K6按键标志
bit Test_Flag = 0;//测试标志
u8 Step_Flag = 0;
bit Alam_Flag;//报警标志
extern bit Alam10S_Flag;//报警10S变量
extern u16 T0Count,T1Count;
u8 PWR_ON_OFF_Times;//连续开关机次数变量
bit PWR_ON_OFF_Flag;
bit FirstStart_Flag;
u8 DangWeiTemp;//档位变量
u8 Times3S = 0;//3s标志
u8 Times10S ;
extern bit AOG_Flag;
extern bit IDLE_flag;
extern bit TestMode10S_Flag;//测试模式10S标志
extern u16 HeapTime;//濾網时间
extern u16 NCCOTime;//氧聚解反应层时间
extern unsigned char idata ISP_RAM[16]; // IRAM 0Xe0 to 0Xff
extern unsigned char code  ISP_ROM[16]_at_ 0x1720; // IRAM 0Xe0 to 0Xff

/******************************************************************************
* 时    间：2019年8月22日14:09:04
* 函数名称：void Normal_Mode(void)
* 函数功能：正常工作模式
* 备    注：
* 修    改：无
 ********************************************************************************/
void Normal_Mode(void)
{
    u8 temp;
	if(POWKEY_Flag)//已经开机
	{
		if(FILTER_DET && POWKEY_Flag)//没有检测到滤网
		{
				BUZ_ERR_TONE();
				SetMotorSpeed(0);//风机关机
				AOG_CTL = 0;//开启AOG
				FirstStart_Flag = 0;
				while(FILTER_DET && POWKEY_Flag)//检测FILTER_DET, 没有磁铁执行			
				{												
					if(ScanKey1() == POWKEY)//按下电源键关机
					{
						TR0 = 0;//关闭定时器0
						TR1  = 0;//关闭定时器1
						POWKEY_Flag = !POWKEY_Flag;
						BUZ_KEY_TONE();
						writeTM1668_data(17,17,0,0,0,0,0);
						SetMotorSpeed(0);//关机
						while(ScanKey1() == POWKEY);
						return;
					}								
					if(!FILTER_DET && POWKEY_Flag)//检测到滤网
					{
						Times10S = 0;
						FirstStart_Flag = 1;
						BUZ_ERR_TONE();
						if(ECOKEY_Flag)
						{
							writeTM1668_data(10,11,1,1,1,1,1);
							writeTM1668_com(0x88);//数码管变暗
						}
						else  if(K6_Flag)//风机最大档位SS模式执行
						{
								K6_Flag = !K6_Flag;//疾风模式标志 
								DangWeiTemp = 10;
								writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档 
						}                          
						else
						{							
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档
						}
					}					
				}
		}
	}
//电源按键			
		if(ScanKey1() == POWKEY)//电源按键
		{
				if(IDLE_flag)
				{
						T0Count = 0;
						BUZ_KEY_TONE();
						IDLE_flag = 0;
						if(ECOKEY_Flag)
						{
							writeTM1668_data(10,11,1,1,1,1,1);
							writeTM1668_com(0x88);//数码管变暗    
						}
						else if(K6_Flag)
						{
							 writeTM1668_data(5,5,1,0,1,1,1);//显示03档   
						}
						else 
						{
								writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档 
						} 
						while(ScanKey1() == POWKEY);
						return;                     
				}
				if(ScanKey1() == POWKEY && !POWKEY_Flag)//判读是否进入滤网解除模式
				{
						TR0 = 1;//启动定时器0
						T0Count = 0;
						Alam10S_Flag = 0;                    
						while(ScanKey1() == POWKEY)
						{
								if(Alam10S_Flag)
								{
										Alam_Flag = 1;
										BUZ_KEY_TONE();
										while(ScanKey1() == POWKEY);
										return;
								}                        
						}	                   
				}
//				K6_Flag = 0;
				while(ScanKey1() == POWKEY ); 
				PWR_ON_OFF_Times++;
				TR0 = 1;//启动定时器0
				TR1 = 1;//启动定时器1
				T0Count = 0;
				Times3S = 0;
                Times10S = 0;
				BUZ_KEY_TONE();
				POWKEY_Flag = !POWKEY_Flag;					
				if(!POWKEY_Flag)//先判断是否已经开机
				{
					TR0 = 0;//关闭定时器0
					TR1 = 0;//关闭定时器1
					Alam_Flag = 0;
					FirstStart_Flag = 1;
					writeTM1668_data(17,17,0,0,0,0,0);
					SetMotorSpeed(0);//风机关机
					while(ScanKey1() == POWKEY);
					return;
				}
				else if(!FILTER_DET)//没有开机执行
				{
					if(!FirstStart_Flag)
					{                                              
							SetMotorSpeed(DangWeiTemp);
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档
							FirstStart_Flag = 1;                             
					}
					else if(ECOKEY_Flag)//上次关机是ECO模式执行
					{
							writeTM1668_data(10,11,1,1,1,1,1);
							writeTM1668_com(0x88);//数码管变暗
					}
					 else if(K6_Flag)//风机最大档位SS模式执行
					{
							K6_Flag = !K6_Flag;//疾风模式标志 
							DangWeiTemp = 10;
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档
	//                        SetMotorSpeed(DangWeiTemp);
	//                        writeTM1668_data(5,5,1,0,1,1,1);//显示SS档
					}
					
					else if(PWR_ON_OFF_Times >= 6)//连续开关机3次						
					{	
							Times3S = 0;
							PWR_ON_OFF_Flag = 1;
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档                        
					}					
					else 
					{
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档
					}
                    					
				}                                 			                                
        }
//ECO按键
		else if(ScanKey1() == ECOKEY && POWKEY_Flag)//ECO
		{
//			HeapTime = 1999;//测试用
//			NCCOTime = 21999;//测试用
				if(IDLE_flag)//唤醒空闲
				{
					T0Count = 0;
					BUZ_KEY_TONE();
					IDLE_flag = 0;
					if(ECOKEY_Flag)
					{
						writeTM1668_data(10,11,1,1,1,1,1);
						writeTM1668_com(0x88);//数码管变暗    
					}
					else if(K6_Flag)
					{
						writeTM1668_data(5,5,1,0,1,1,1);//显示03档   
					}
					else
					{
						writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档 
					}  
					while(ScanKey1() == ECOKEY);
					return;                
				}            
			T0Count = 0;
			ECOKEY_Flag = !ECOKEY_Flag;
			BUZ_KEY_TONE();
            
			if(ECOKEY_Flag)
			{
				if(!FirstStart_Flag)
				SetMotorSpeed(3);//风机3挡
				writeTM1668_data(10,11,1,1,1,1,1);
				writeTM1668_com(0x88);//数码管变暗
			}
			else if(K6_Flag)//风机最大档位SS模式执行
			{				
					writeTM1668_data(5,5,1,0,1,1,1);//显示SS档
					if(!FirstStart_Flag)
					SetMotorSpeed(11);//疾风模式

			}
			else//风机回到原来的挡位执行
			{				
				writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
				if(!FirstStart_Flag)
				SetMotorSpeed(DangWeiTemp);
			}
			while(ScanKey1() == ECOKEY);
		}
//增加按键	

	else if(ScanKey1() == K6 && POWKEY_Flag  && !FILTER_DET)//增加
	{
			if(IDLE_flag)
			{
					T0Count = 0;
					IDLE_flag = 0;
					if(ECOKEY_Flag)
					{
						writeTM1668_data(10,11,1,1,1,1,1);
						writeTM1668_com(0x88);//数码管变暗    
					}
					else if(K6_Flag)
					{
						 writeTM1668_data(5,5,1,0,1,1,1);//显示03档   
					}
					else
					{
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示03档 
					}
					while(ScanKey1() == K6);
					return;                     
			}
		
			while((ScanKey1() == K6 || ScanKey1() == K5K6) && !ECOKEY_Flag)
			{	
				Times3S = 0;
				T0Count = 0;
				
				temp = ScanKey1();	
				if(temp == K5K6 && !K6_Flag)
				{
					DangWeiTemp--;
					if(DangWeiTemp == 0)
							DangWeiTemp =1;
					writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
					if(!FirstStart_Flag)
							SetMotorSpeed(DangWeiTemp);//设置风机挡位
//					while(temp == K6 );
					return;
				}				
				else if(temp == K6  && DangWeiTemp >= 10 )//疾风模式	
				{
						Times3S = 0;
						while(ScanKey1() == K6 &&  POWKEY_Flag && !ECOKEY_Flag && DangWeiTemp >= 10 )//疾风模式
						{
								if(Times3S >= 60)
								{
										BUZ_KEY_TONE();						
										K6_Flag = !K6_Flag;//疾风模式标志
										if(K6_Flag)//风机最大档位SS执行
										{
												DangWeiTemp = 11;
												writeTM1668_data(5,5,1,0,1,1,1);//显示SS档
												if(!FirstStart_Flag)
												{                                        
														SetMotorSpeed(DangWeiTemp);//疾风模式
												}
										}
										else//风机从SS档退回档位10
										{
												DangWeiTemp = 10;
												writeTM1668_data(1,0,1,0,1,1,1);//显示10档
												if(!FirstStart_Flag)
												{                                    
														SetMotorSpeed(10);//疾风模式
												}
										}	
										while(ScanKey1() == K6);
										return;
								}	
						}
				}	
				else if(!K6_Flag)
				{	
								while(ScanKey1() == K6);
								while(ScanKey1() == K5K6)
								{
										DangWeiTemp--;
										if(DangWeiTemp == 0)
														DangWeiTemp =1;
										writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
										if(!FirstStart_Flag)
										SetMotorSpeed(DangWeiTemp);//设置风机挡位
										return;
								}
								BUZ_KEY_TONE();	
								DangWeiTemp++;
								if(DangWeiTemp >= 11)
								{
										DangWeiTemp = 10;
								}		
								 if(!K6_Flag)
								{
										writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
										if(!FirstStart_Flag)
										SetMotorSpeed(DangWeiTemp);//设置风机挡位
								}
								return;
				}													
			}		
	}

		
//滑动按键检测		
		if(POWKEY_Flag  && !FILTER_DET )
		{
			SlideKey();
		}
//滤网滤芯提示功能	
		if(POWKEY_Flag && !FILTER_DET)
		{
				if(HeapTime >= 6000 && HeapTime != 0xffff)//3000小时
				{

					writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,2,2,2);//显示红灯
				}
				if(NCCOTime >= 22000 && NCCOTime != 0xffff)//11000小时
				{
					BUZ_ERR_TONE();
					writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,2,2,2);//显示红灯
					Delay_MS(500);
					BUZ_ERR_TONE();
					writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,0,0,0);//显示红灯
					Delay_MS(500);
				}
		}
}

/******************************************************************************
* 时    间：2019年8月23日14:09:04
* 函数名称：void Test_Mode(void)
* 函数功能：测试模式
* 备    注：
* 修    改：无
 ********************************************************************************/
void Test_Mode(void)
{
	if(!POWKEY_Flag) //关机状态下进入测试程序
	{
			if(ScanKey1() == ECOKEY ||ScanKey1() == K2K5)
			{
				TR0 = 1;//启动定时器0				
				T0Count = 0;
				Test_Flag = 1;
				TestMode10S_Flag = 0;
				while((ScanKey1() == ECOKEY||ScanKey1() == K2K5) && Test_Flag)
				{
					if(TestMode10S_Flag)//检测到测试10S时间到
					{
						BUZ_KEY_TONE();
						break;
					}
					if((ScanKey1() == K2K5) && (T0Count >= 30))
							TestMode10S_Flag = 1;
				}
				if(!TestMode10S_Flag && Test_Flag)//没有到10s，松开按键
				{
					TR0 = 0;//关闭定时器0				
					T0Count = 0;
					Test_Flag = 0;
					TestMode10S_Flag = 0;
					return;
				}				
				while(ScanKey1() == ECOKEY);
				
				while(!(ScanKey1() == K1 && TestMode10S_Flag))
				{
						if(ScanKey1() == POWKEY)
						{
								TR0 = 0;//关闭定时器0				
								T0Count = 0;
								Test_Flag = 0;
								TestMode10S_Flag = 0;
								Step_Flag = 0;
								return;
						}
				}
                    //等待按下K1				
				BUZ_KEY_TONE();
				while(!(ScanKey1() == K6 && TestMode10S_Flag))	//等待按下k6	
				{
						if(ScanKey1() == POWKEY)
						{
								TR0 = 0;//关闭定时器0				
								T0Count = 0;
								Test_Flag = 0;
								TestMode10S_Flag = 0;
								Step_Flag = 0;
								return;
						}
				}                    
				BUZ_KEY_TONE();

				writeTM1668_data(12,13,0,0,0,0,0);//显示tb档
				Delay_MS(1000);
				Delay_MS(1000);
				writeTM1668_data(8,8,1,1,3,3,3);//所有灯全亮
				AOG_CTL = 1;//啟動 AOG
				Delay_MS(1000);
				Delay_MS(1000);
				writeTM1668_data(17,17,0,0,0,0,0);//所有灯全灭
				Delay_MS(1000);
				Delay_MS(1000);
				AOG_CTL = 0;//AOG输出关闭
				BUZ_PWR_TONE();//开机声音
				writeTM1668_data(0,7,1,1,3,3,3);//所有07
				Delay_MS(1000);
				Delay_MS(1000);
				writeTM1668_data(0,8,0,0,0,0,0);//所有08
				BUZ_KEY_TONE();
				Delay_MS(1000);
				Delay_MS(1000);
				writeTM1668_data(0,9,1,0,0,0,0);//所有灯全灭
				BUZ_ERR_TONE();
				Delay_MS(1000);
				BUZ_ERR_TONE();
                 
				while(1)
				{
						if(ScanKey1() == K1)
						{
								writeTM1668_data(0,1,0,0,0,0,0);//所有灯全灭
								SetMotorSpeed(1);//设置风机挡位
								BUZ_KEY_TONE();
								while(ScanKey1() == K1);
						}
						if(ScanKey1() == K2)
						{
								writeTM1668_data(0,2,0,0,0,0,0);//所有灯全灭
								SetMotorSpeed(2);//设置风机挡位
								BUZ_KEY_TONE();
								while(ScanKey1() == K2);
						}
						if(ScanKey1() == K3)
						{
								writeTM1668_data(0,3,0,0,0,0,0);//所有灯全灭
								SetMotorSpeed(3);//设置风机挡位
								BUZ_KEY_TONE();
								while(ScanKey1() == K3);
						}
						if(ScanKey1() == K4)
						{
								writeTM1668_data(0,4,0,0,0,0,0);//所有灯全灭
								SetMotorSpeed(4);//设置风机挡位
								BUZ_KEY_TONE();
								while(ScanKey1() == K4);
						}
						if(ScanKey1() == K5)
						{
								writeTM1668_data(0,5,0,0,0,0,0);//所有灯全灭
								SetMotorSpeed(5);//设置风机挡位
								BUZ_KEY_TONE();
								while(ScanKey1() == K5);
						}
						if(ScanKey1() == K6)
						{
								writeTM1668_data(0,6,0,0,0,0,0);//所有灯全灭
								SetMotorSpeed(6);//设置风机挡位
								BUZ_KEY_TONE();
								Delay_MS(500);
								if(ScanKey1() != K6)
										continue;
								Delay_MS(500);
								if(ScanKey1() != K6)
										continue;
								Delay_MS(500);
								if(ScanKey1() != K6)
										continue;
								Delay_MS(500);
								if(ScanKey1() != K6)
										continue;
								Delay_MS(500);
								if(ScanKey1() != K6)
										continue;
								Delay_MS(500);
								if(ScanKey1() == K6)
								{
										writeTM1668_data(5,5,0,0,0,0,0);//所有灯全灭
										SetMotorSpeed(11);//设置风机挡位
										BUZ_KEY_TONE();								
								}
								while(ScanKey1() == K6);
						}

						if(ScanKey1() == POWKEY && Test_Flag)
						{
								writeTM1668_data(17,17,0,0,0,0,0);//所有灯全灭		
								SetMotorSpeed(0);//设置风机挡位
								while(ScanKey1() == POWKEY);
								Test_Flag = 0;
								TestMode10S_Flag = 0;
								Step_Flag = 0;
								return;	//				
						}                        
				}
			 
		}				
	}
}

/******************************************************************************
* 时    间：2019年8月23日18:08:56
* 函数名称：void RemoveALam(void)
* 函数功能：报警模式
* 备    注：
* 修    改：无
 ********************************************************************************/
void RemoveALam(void)
{
		
//滤网解除
    if(Alam10S_Flag)
    {
        if(ScanKey1() == K1 )						
        {
            BUZ_KEY_TONE();
            writeTM1668_data(14,15,1,0,0,0,0);///显示HF                       
            Delay_MS(500);
            writeTM1668_data(17,17,1,0,0,0,0);///闭HF  
            Delay_MS(500);
            writeTM1668_data(14,15,1,0,0,0,0);///显示HF                       
            Delay_MS(500);
            writeTM1668_data(17,17,1,0,0,0,0);///闭HF  
            Delay_MS(500);
            writeTM1668_data(14,15,1,0,0,0,0);///显示HF                       
            Delay_MS(500);
            writeTM1668_data(17,17,1,0,0,0,0);///闭HF  
            Delay_MS(500);
            BUZ_KEY_TONE();
            writeTM1668_data(17,17,0,0,0,0,0);//关闭所有
            HeapTime = 0;
            ISP_RAM[0] = 0;// HeapTime时间清0
            ISP_RAM[1] = 0;//HeapTime时间清0
            SYSIspStart(0x1720);
            TR0 = 0;//启动定时器0
            T0Count = 0;
            Alam10S_Flag = 0;
            return;
        }

//氧聚解反应层解除
        else if(ScanKey1() == K6  )
        {
                BUZ_KEY_TONE();
                writeTM1668_data(16,15,0,0,0,0,0);//显示nF	
                Delay_MS(500);
                writeTM1668_data(17,17,1,0,0,0,0);///显闭nF  
                Delay_MS(500);
                writeTM1668_data(16,15,1,0,0,0,0);///显示nF                       
                Delay_MS(500);
                writeTM1668_data(17,17,1,0,0,0,0);///显闭nF  
                Delay_MS(500);
                writeTM1668_data(16,15,1,0,0,0,0);///显示nF                       
                Delay_MS(500);
                writeTM1668_data(17,17,1,0,0,0,0);///关闭nF  
                Delay_MS(500);
                BUZ_KEY_TONE();
                writeTM1668_data(17,17,0,0,0,0,0);//关闭所有	
                NCCOTime = 0;
                ISP_RAM[2] = 0;// NCCOTime时间清0
                ISP_RAM[3] = 0;//NCCOTime时间清0
                SYSIspStart(0x1720);
                TR0 = 0;//启动定时器0
                T0Count = 0;
                Alam10S_Flag = 0;
                return;							
        }
    }
}

				
