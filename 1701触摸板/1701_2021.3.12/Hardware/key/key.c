#include "key.h"

extern u8 DangWeiTemp;
extern u16 T0Count,T1Count;
u8  IICRecvBuff[2] = {0};
extern u8 Times3S ;//3s标志
extern bit K6_Flag;//K6按键标志
extern bit POWKEY_Flag;
extern bit ECOKEY_Flag;
extern bit IDLE_flag;
extern bit FirstStart_Flag;

u8 bTemp = 0;
u8 RecvData(u8 Add)
{
	u8 bRes = 0;
		IIC_Start();
		IIC_Send_Byte(Add);                  //发送器件地址0Xab,写数据
		IIC_Wait_Ack();
		IICRecvBuff[0] = IIC_Read_Byte(1);           //接收到第一个字节数据
		IICRecvBuff[1] = IIC_Read_Byte(0);		   //接收到第二个字节数据
		IIC_Stop();                          //产生一个停止条件
	
	if (IICRecvBuff[0] != IICRecvBuff[1]) {
		bRes++;
	}
	return bRes;
}

#if 1
u8 ScanKey1(void)
{
	static u8 bOld_key;
	u8 bRes = 0;
	if (RecvData(0x55)) {
		return bOld_key;
	}
//	writeTM1668_data(IICRecvBuff[0] >> 4, IICRecvBuff[0] & 0xf, 0,0,0,0,0);
	if(IICRecvBuff[0] == POWKEY)
	{
			bRes = POWKEY;
	}
	else if(IICRecvBuff[0] == ECOKEY)
	{
			bRes = ECOKEY;
	}	
	else if(IICRecvBuff[0] == K1)
	{
			bRes = K1;
	}
	else if(IICRecvBuff[0] == K2)
	{
			bRes = K2;
	}	
	else if(IICRecvBuff[0] == K3)
	{
			bRes = K3;
	}	
	 else if(IICRecvBuff[0] == K4)
	{
			bRes = K4;
	}	
	 else if(IICRecvBuff[0] == K5)
	{	
			bRes = K5;
	}	
	 else if(IICRecvBuff[0] == K6)		
	{
			bRes = K6;
	}
	 else if(IICRecvBuff[0] == K1K2)
	{
			bRes = K1K2;
	}
	 else if(IICRecvBuff[0] == K2K3)
	{
			bRes = K2K3;
	}
	else if(IICRecvBuff[0] == K3K4)
	{
			bRes = K3K4;
	}
	 else if(IICRecvBuff[0] == K4K5)
	{
			bRes = K4K5;
	}
	 else if(IICRecvBuff[0] == K5K6)
	{
			bRes = K5K6;
	}	
	 else if(IICRecvBuff[0] == K2K5)
	{
			bRes = K2K5;
	}else if(IICRecvBuff[0] == 0)
	{
			bRes = 0;
	} else 
	{
		return bOld_key;
	}
	bOld_key = bRes;
	
	return bRes;
}


void SlideKey(void)//滑动按键
{	
		u8 temp;

		temp = ScanKey1();
		if(temp == K1)
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
						while(ScanKey1() == K1);
						return;                     
				}            
				while((ScanKey1() == K1 || ScanKey1() == K1K2) && !K6_Flag && !ECOKEY_Flag)
				{
						while(ScanKey1() == K1);
						if(ScanKey1() == K2 || ScanKey1() == K1K2)
						{				
								DangWeiTemp++;
								if(DangWeiTemp >= 11)
								{
										DangWeiTemp = 10;
								}		
								writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
								if(!FirstStart_Flag)
									SetMotorSpeed(DangWeiTemp);//设置风机挡位
//					while(temp == K1 );
								break;
						}
						else
						{
								T0Count = 0;					
								while(ScanKey1() == K1);						
								DangWeiTemp--;
								if(DangWeiTemp == 0)
								{
										DangWeiTemp =1;
										return;
								}
								BUZ_KEY_TONE();	
								writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
								if(!FirstStart_Flag)
								SetMotorSpeed(DangWeiTemp);//设置风机挡位
						}	
				}
		}
		else if(temp == K2)
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
							while(ScanKey1() == K2);
							return;                     
					}             
					while((ScanKey1() == K2 || ScanKey1() == K2K3 || ScanKey1() == K1K2) && !K6_Flag && !ECOKEY_Flag)
					{
						if(ScanKey1() == K3 || ScanKey1() == K2K3)
						{				
							DangWeiTemp++;
							if(DangWeiTemp >= 11)
							{
								DangWeiTemp = 10;
							}		
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
							if(!FirstStart_Flag)
								SetMotorSpeed(DangWeiTemp);//设置风机挡位
		//					while(ScanKey1() == K2K3);
							break;
						}
						else if(ScanKey1() == K1 ||ScanKey1() == K1K2)
						{
							DangWeiTemp--;
							if(DangWeiTemp == 0)
									DangWeiTemp =1;
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
							if(!FirstStart_Flag)
								SetMotorSpeed(DangWeiTemp);//设置风机挡位
		//					while(ScanKey1() == K1K2 );
							break;
						}								
					}
		}
		else if(temp == K3)
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
							while(ScanKey1() == K3);
							return;                     
					}             
					while((ScanKey1() == K3 || ScanKey1() ==K3K4 || ScanKey1() ==K2K3) && !K6_Flag && !ECOKEY_Flag)
					{
						if(ScanKey1() == K4 ||ScanKey1() == K3K4)
						{				
							DangWeiTemp++;
							if(DangWeiTemp >= 11)
							{
								DangWeiTemp = 10;
							}		
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
							if(!FirstStart_Flag)
								SetMotorSpeed(DangWeiTemp);//设置风机挡位
		//					while(ScanKey1() == K3K4);
							break;
						}
						else if(ScanKey1() == K2 ||ScanKey1() == K2K3)
						{
							DangWeiTemp--;
							if(DangWeiTemp == 0)
									DangWeiTemp =1;
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
							if(!FirstStart_Flag)
								SetMotorSpeed(DangWeiTemp);//设置风机挡位
		//					while(ScanKey1() == K2K3 );
							break;
				}								
			}
		}
		else if(temp == K4)
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
						while(ScanKey1() == K4);
						return;                     
				}             
				while((ScanKey1() == K4 || ScanKey1() == K4K5 || ScanKey1() == K3K4) && !K6_Flag && !ECOKEY_Flag)
				{
					if(ScanKey1() == K5 ||ScanKey1() == K4K5)
					{				
						DangWeiTemp++;
						if(DangWeiTemp >= 11)
						{
							DangWeiTemp = 10;
						}		
						writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
						if(!FirstStart_Flag)
							SetMotorSpeed(DangWeiTemp);//设置风机挡位
	//					while(ScanKey1() == K4K5  );
						break;
					}
					else if(ScanKey1() == K3 ||ScanKey1() == K3K4)
					{
						DangWeiTemp--;
						if(DangWeiTemp == 0)
								DangWeiTemp =1;
						writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
						if(!FirstStart_Flag)
							SetMotorSpeed(DangWeiTemp);//设置风机挡位
	//					while(ScanKey1() == K3K4 );
						break;
					}								
				}
		}
		else if(temp == K5)
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
							while(ScanKey1() == K5);
							return;                     
					}             
					while((ScanKey1() == K5 || ScanKey1() == K5K6 || ScanKey1() == K4K5) && !K6_Flag && !ECOKEY_Flag)
					{
						if(ScanKey1() == K6 ||ScanKey1() == K5K6)
						{				
							DangWeiTemp++;
							if(DangWeiTemp >= 11)
							{
								DangWeiTemp = 10;
							}		
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
							if(!FirstStart_Flag)
								SetMotorSpeed(DangWeiTemp);//设置风机挡位
		//					while(ScanKey1() == K5K6  );
							break;
						}
						else if(ScanKey1() == K4 ||ScanKey1() == K4K5)
						{
							DangWeiTemp--;
							if(DangWeiTemp == 0)
									DangWeiTemp =1;
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//显示01档
							if(!FirstStart_Flag)
								SetMotorSpeed(DangWeiTemp);//设置风机挡位
		//					while(ScanKey1() == K4K5 );
							break;
						}								
					}
		}
}
//#endif


		



