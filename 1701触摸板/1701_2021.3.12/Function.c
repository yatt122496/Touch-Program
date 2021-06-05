/***************************************************************************
*Copyright(c) 2019,�������ֵ������޹�˾
*All rights reserved.
*
*Ӳ    ����SN8F5703
*�ļ����ƣ�Function.c
*
*��ǰ�汾��V1.0
*��    �ߣ�yehuoyan
*������ڣ�2019��8��17��13:41:10
*
*ȡ���汾��V1.0
*��    �ߣ�yehuoyan
*������ڣ�


******************************************************************************/
#include "Function.h"

bit POWKEY_Flag = 0;//��Դ������־
bit ECOKEY_Flag = 0;//ECO������־
bit K6_Flag = 0;//K6������־
bit Test_Flag = 0;//���Ա�־
u8 Step_Flag = 0;
bit Alam_Flag;//������־
extern bit Alam10S_Flag;//����10S����
extern u16 T0Count,T1Count;
u8 PWR_ON_OFF_Times;//�������ػ���������
bit PWR_ON_OFF_Flag;
bit FirstStart_Flag;
u8 DangWeiTemp;//��λ����
u8 Times3S = 0;//3s��־
u8 Times10S ;
extern bit AOG_Flag;
extern bit IDLE_flag;
extern bit TestMode10S_Flag;//����ģʽ10S��־
extern u16 HeapTime;//�V�Wʱ��
extern u16 NCCOTime;//���۽ⷴӦ��ʱ��
extern unsigned char idata ISP_RAM[16]; // IRAM 0Xe0 to 0Xff
extern unsigned char code  ISP_ROM[16]_at_ 0x1720; // IRAM 0Xe0 to 0Xff

/******************************************************************************
* ʱ    �䣺2019��8��22��14:09:04
* �������ƣ�void Normal_Mode(void)
* �������ܣ���������ģʽ
* ��    ע��
* ��    �ģ���
 ********************************************************************************/
void Normal_Mode(void)
{
    u8 temp;
	if(POWKEY_Flag)//�Ѿ�����
	{
		if(FILTER_DET && POWKEY_Flag)//û�м�⵽����
		{
				BUZ_ERR_TONE();
				SetMotorSpeed(0);//����ػ�
				AOG_CTL = 0;//����AOG
				FirstStart_Flag = 0;
				while(FILTER_DET && POWKEY_Flag)//���FILTER_DET, û�д���ִ��			
				{												
					if(ScanKey1() == POWKEY)//���µ�Դ���ػ�
					{
						TR0 = 0;//�رն�ʱ��0
						TR1  = 0;//�رն�ʱ��1
						POWKEY_Flag = !POWKEY_Flag;
						BUZ_KEY_TONE();
						writeTM1668_data(17,17,0,0,0,0,0);
						SetMotorSpeed(0);//�ػ�
						while(ScanKey1() == POWKEY);
						return;
					}								
					if(!FILTER_DET && POWKEY_Flag)//��⵽����
					{
						Times10S = 0;
						FirstStart_Flag = 1;
						BUZ_ERR_TONE();
						if(ECOKEY_Flag)
						{
							writeTM1668_data(10,11,1,1,1,1,1);
							writeTM1668_com(0x88);//����ܱ䰵
						}
						else  if(K6_Flag)//������λSSģʽִ��
						{
								K6_Flag = !K6_Flag;//����ģʽ��־ 
								DangWeiTemp = 10;
								writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03�� 
						}                          
						else
						{							
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03��
						}
					}					
				}
		}
	}
//��Դ����			
		if(ScanKey1() == POWKEY)//��Դ����
		{
				if(IDLE_flag)
				{
						T0Count = 0;
						BUZ_KEY_TONE();
						IDLE_flag = 0;
						if(ECOKEY_Flag)
						{
							writeTM1668_data(10,11,1,1,1,1,1);
							writeTM1668_com(0x88);//����ܱ䰵    
						}
						else if(K6_Flag)
						{
							 writeTM1668_data(5,5,1,0,1,1,1);//��ʾ03��   
						}
						else 
						{
								writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03�� 
						} 
						while(ScanKey1() == POWKEY);
						return;                     
				}
				if(ScanKey1() == POWKEY && !POWKEY_Flag)//�ж��Ƿ�����������ģʽ
				{
						TR0 = 1;//������ʱ��0
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
				TR0 = 1;//������ʱ��0
				TR1 = 1;//������ʱ��1
				T0Count = 0;
				Times3S = 0;
                Times10S = 0;
				BUZ_KEY_TONE();
				POWKEY_Flag = !POWKEY_Flag;					
				if(!POWKEY_Flag)//���ж��Ƿ��Ѿ�����
				{
					TR0 = 0;//�رն�ʱ��0
					TR1 = 0;//�رն�ʱ��1
					Alam_Flag = 0;
					FirstStart_Flag = 1;
					writeTM1668_data(17,17,0,0,0,0,0);
					SetMotorSpeed(0);//����ػ�
					while(ScanKey1() == POWKEY);
					return;
				}
				else if(!FILTER_DET)//û�п���ִ��
				{
					if(!FirstStart_Flag)
					{                                              
							SetMotorSpeed(DangWeiTemp);
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03��
							FirstStart_Flag = 1;                             
					}
					else if(ECOKEY_Flag)//�ϴιػ���ECOģʽִ��
					{
							writeTM1668_data(10,11,1,1,1,1,1);
							writeTM1668_com(0x88);//����ܱ䰵
					}
					 else if(K6_Flag)//������λSSģʽִ��
					{
							K6_Flag = !K6_Flag;//����ģʽ��־ 
							DangWeiTemp = 10;
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03��
	//                        SetMotorSpeed(DangWeiTemp);
	//                        writeTM1668_data(5,5,1,0,1,1,1);//��ʾSS��
					}
					
					else if(PWR_ON_OFF_Times >= 6)//�������ػ�3��						
					{	
							Times3S = 0;
							PWR_ON_OFF_Flag = 1;
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03��                        
					}					
					else 
					{
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03��
					}
                    					
				}                                 			                                
        }
//ECO����
		else if(ScanKey1() == ECOKEY && POWKEY_Flag)//ECO
		{
//			HeapTime = 1999;//������
//			NCCOTime = 21999;//������
				if(IDLE_flag)//���ѿ���
				{
					T0Count = 0;
					BUZ_KEY_TONE();
					IDLE_flag = 0;
					if(ECOKEY_Flag)
					{
						writeTM1668_data(10,11,1,1,1,1,1);
						writeTM1668_com(0x88);//����ܱ䰵    
					}
					else if(K6_Flag)
					{
						writeTM1668_data(5,5,1,0,1,1,1);//��ʾ03��   
					}
					else
					{
						writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03�� 
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
				SetMotorSpeed(3);//���3��
				writeTM1668_data(10,11,1,1,1,1,1);
				writeTM1668_com(0x88);//����ܱ䰵
			}
			else if(K6_Flag)//������λSSģʽִ��
			{				
					writeTM1668_data(5,5,1,0,1,1,1);//��ʾSS��
					if(!FirstStart_Flag)
					SetMotorSpeed(11);//����ģʽ

			}
			else//����ص�ԭ���ĵ�λִ��
			{				
				writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ01��
				if(!FirstStart_Flag)
				SetMotorSpeed(DangWeiTemp);
			}
			while(ScanKey1() == ECOKEY);
		}
//���Ӱ���	

	else if(ScanKey1() == K6 && POWKEY_Flag  && !FILTER_DET)//����
	{
			if(IDLE_flag)
			{
					T0Count = 0;
					IDLE_flag = 0;
					if(ECOKEY_Flag)
					{
						writeTM1668_data(10,11,1,1,1,1,1);
						writeTM1668_com(0x88);//����ܱ䰵    
					}
					else if(K6_Flag)
					{
						 writeTM1668_data(5,5,1,0,1,1,1);//��ʾ03��   
					}
					else
					{
							writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ03�� 
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
					writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ01��
					if(!FirstStart_Flag)
							SetMotorSpeed(DangWeiTemp);//���÷����λ
//					while(temp == K6 );
					return;
				}				
				else if(temp == K6  && DangWeiTemp >= 10 )//����ģʽ	
				{
						Times3S = 0;
						while(ScanKey1() == K6 &&  POWKEY_Flag && !ECOKEY_Flag && DangWeiTemp >= 10 )//����ģʽ
						{
								if(Times3S >= 60)
								{
										BUZ_KEY_TONE();						
										K6_Flag = !K6_Flag;//����ģʽ��־
										if(K6_Flag)//������λSSִ��
										{
												DangWeiTemp = 11;
												writeTM1668_data(5,5,1,0,1,1,1);//��ʾSS��
												if(!FirstStart_Flag)
												{                                        
														SetMotorSpeed(DangWeiTemp);//����ģʽ
												}
										}
										else//�����SS���˻ص�λ10
										{
												DangWeiTemp = 10;
												writeTM1668_data(1,0,1,0,1,1,1);//��ʾ10��
												if(!FirstStart_Flag)
												{                                    
														SetMotorSpeed(10);//����ģʽ
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
										writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ01��
										if(!FirstStart_Flag)
										SetMotorSpeed(DangWeiTemp);//���÷����λ
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
										writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,1,1,1);//��ʾ01��
										if(!FirstStart_Flag)
										SetMotorSpeed(DangWeiTemp);//���÷����λ
								}
								return;
				}													
			}		
	}

		
//�����������		
		if(POWKEY_Flag  && !FILTER_DET )
		{
			SlideKey();
		}
//������о��ʾ����	
		if(POWKEY_Flag && !FILTER_DET)
		{
				if(HeapTime >= 6000 && HeapTime != 0xffff)//3000Сʱ
				{

					writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,2,2,2);//��ʾ���
				}
				if(NCCOTime >= 22000 && NCCOTime != 0xffff)//11000Сʱ
				{
					BUZ_ERR_TONE();
					writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,2,2,2);//��ʾ���
					Delay_MS(500);
					BUZ_ERR_TONE();
					writeTM1668_data(DangWeiTemp/10,DangWeiTemp%10,1,0,0,0,0);//��ʾ���
					Delay_MS(500);
				}
		}
}

/******************************************************************************
* ʱ    �䣺2019��8��23��14:09:04
* �������ƣ�void Test_Mode(void)
* �������ܣ�����ģʽ
* ��    ע��
* ��    �ģ���
 ********************************************************************************/
void Test_Mode(void)
{
	if(!POWKEY_Flag) //�ػ�״̬�½�����Գ���
	{
			if(ScanKey1() == ECOKEY ||ScanKey1() == K2K5)
			{
				TR0 = 1;//������ʱ��0				
				T0Count = 0;
				Test_Flag = 1;
				TestMode10S_Flag = 0;
				while((ScanKey1() == ECOKEY||ScanKey1() == K2K5) && Test_Flag)
				{
					if(TestMode10S_Flag)//��⵽����10Sʱ�䵽
					{
						BUZ_KEY_TONE();
						break;
					}
					if((ScanKey1() == K2K5) && (T0Count >= 30))
							TestMode10S_Flag = 1;
				}
				if(!TestMode10S_Flag && Test_Flag)//û�е�10s���ɿ�����
				{
					TR0 = 0;//�رն�ʱ��0				
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
								TR0 = 0;//�رն�ʱ��0				
								T0Count = 0;
								Test_Flag = 0;
								TestMode10S_Flag = 0;
								Step_Flag = 0;
								return;
						}
				}
                    //�ȴ�����K1				
				BUZ_KEY_TONE();
				while(!(ScanKey1() == K6 && TestMode10S_Flag))	//�ȴ�����k6	
				{
						if(ScanKey1() == POWKEY)
						{
								TR0 = 0;//�رն�ʱ��0				
								T0Count = 0;
								Test_Flag = 0;
								TestMode10S_Flag = 0;
								Step_Flag = 0;
								return;
						}
				}                    
				BUZ_KEY_TONE();

				writeTM1668_data(12,13,0,0,0,0,0);//��ʾtb��
				Delay_MS(1000);
				Delay_MS(1000);
				writeTM1668_data(8,8,1,1,3,3,3);//���е�ȫ��
				AOG_CTL = 1;//���� AOG
				Delay_MS(1000);
				Delay_MS(1000);
				writeTM1668_data(17,17,0,0,0,0,0);//���е�ȫ��
				Delay_MS(1000);
				Delay_MS(1000);
				AOG_CTL = 0;//AOG����ر�
				BUZ_PWR_TONE();//��������
				writeTM1668_data(0,7,1,1,3,3,3);//����07
				Delay_MS(1000);
				Delay_MS(1000);
				writeTM1668_data(0,8,0,0,0,0,0);//����08
				BUZ_KEY_TONE();
				Delay_MS(1000);
				Delay_MS(1000);
				writeTM1668_data(0,9,1,0,0,0,0);//���е�ȫ��
				BUZ_ERR_TONE();
				Delay_MS(1000);
				BUZ_ERR_TONE();
                 
				while(1)
				{
						if(ScanKey1() == K1)
						{
								writeTM1668_data(0,1,0,0,0,0,0);//���е�ȫ��
								SetMotorSpeed(1);//���÷����λ
								BUZ_KEY_TONE();
								while(ScanKey1() == K1);
						}
						if(ScanKey1() == K2)
						{
								writeTM1668_data(0,2,0,0,0,0,0);//���е�ȫ��
								SetMotorSpeed(2);//���÷����λ
								BUZ_KEY_TONE();
								while(ScanKey1() == K2);
						}
						if(ScanKey1() == K3)
						{
								writeTM1668_data(0,3,0,0,0,0,0);//���е�ȫ��
								SetMotorSpeed(3);//���÷����λ
								BUZ_KEY_TONE();
								while(ScanKey1() == K3);
						}
						if(ScanKey1() == K4)
						{
								writeTM1668_data(0,4,0,0,0,0,0);//���е�ȫ��
								SetMotorSpeed(4);//���÷����λ
								BUZ_KEY_TONE();
								while(ScanKey1() == K4);
						}
						if(ScanKey1() == K5)
						{
								writeTM1668_data(0,5,0,0,0,0,0);//���е�ȫ��
								SetMotorSpeed(5);//���÷����λ
								BUZ_KEY_TONE();
								while(ScanKey1() == K5);
						}
						if(ScanKey1() == K6)
						{
								writeTM1668_data(0,6,0,0,0,0,0);//���е�ȫ��
								SetMotorSpeed(6);//���÷����λ
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
										writeTM1668_data(5,5,0,0,0,0,0);//���е�ȫ��
										SetMotorSpeed(11);//���÷����λ
										BUZ_KEY_TONE();								
								}
								while(ScanKey1() == K6);
						}

						if(ScanKey1() == POWKEY && Test_Flag)
						{
								writeTM1668_data(17,17,0,0,0,0,0);//���е�ȫ��		
								SetMotorSpeed(0);//���÷����λ
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
* ʱ    �䣺2019��8��23��18:08:56
* �������ƣ�void RemoveALam(void)
* �������ܣ�����ģʽ
* ��    ע��
* ��    �ģ���
 ********************************************************************************/
void RemoveALam(void)
{
		
//�������
    if(Alam10S_Flag)
    {
        if(ScanKey1() == K1 )						
        {
            BUZ_KEY_TONE();
            writeTM1668_data(14,15,1,0,0,0,0);///��ʾHF                       
            Delay_MS(500);
            writeTM1668_data(17,17,1,0,0,0,0);///��HF  
            Delay_MS(500);
            writeTM1668_data(14,15,1,0,0,0,0);///��ʾHF                       
            Delay_MS(500);
            writeTM1668_data(17,17,1,0,0,0,0);///��HF  
            Delay_MS(500);
            writeTM1668_data(14,15,1,0,0,0,0);///��ʾHF                       
            Delay_MS(500);
            writeTM1668_data(17,17,1,0,0,0,0);///��HF  
            Delay_MS(500);
            BUZ_KEY_TONE();
            writeTM1668_data(17,17,0,0,0,0,0);//�ر�����
            HeapTime = 0;
            ISP_RAM[0] = 0;// HeapTimeʱ����0
            ISP_RAM[1] = 0;//HeapTimeʱ����0
            SYSIspStart(0x1720);
            TR0 = 0;//������ʱ��0
            T0Count = 0;
            Alam10S_Flag = 0;
            return;
        }

//���۽ⷴӦ����
        else if(ScanKey1() == K6  )
        {
                BUZ_KEY_TONE();
                writeTM1668_data(16,15,0,0,0,0,0);//��ʾnF	
                Delay_MS(500);
                writeTM1668_data(17,17,1,0,0,0,0);///�Ա�nF  
                Delay_MS(500);
                writeTM1668_data(16,15,1,0,0,0,0);///��ʾnF                       
                Delay_MS(500);
                writeTM1668_data(17,17,1,0,0,0,0);///�Ա�nF  
                Delay_MS(500);
                writeTM1668_data(16,15,1,0,0,0,0);///��ʾnF                       
                Delay_MS(500);
                writeTM1668_data(17,17,1,0,0,0,0);///�ر�nF  
                Delay_MS(500);
                BUZ_KEY_TONE();
                writeTM1668_data(17,17,0,0,0,0,0);//�ر�����	
                NCCOTime = 0;
                ISP_RAM[2] = 0;// NCCOTimeʱ����0
                ISP_RAM[3] = 0;//NCCOTimeʱ����0
                SYSIspStart(0x1720);
                TR0 = 0;//������ʱ��0
                T0Count = 0;
                Alam10S_Flag = 0;
                return;							
        }
    }
}

				
