//TKCON����
#define TKST(N)		(N<<7)	 //N=0-1
#define TKIE(N)		(N<<6)	 //N=0-1
#define TMEN(N)		(N<<5)	 //N=0-1	//RTC����TKST
#define TWKE(N)		(N<<4)	 //N=0-1	//ʡ���Զ�����	  0��TKST=0������TKIF, 1: TKST=0������Ƚ�������Ų���TKIF 

#define VRS(N)		(N<<0)	 //N=0-7	//�Ƚ����ο���ѹѡ��

//TKCFG����
#define TKDIV(N)	(N<<5)	 //N=0-7	//ʱ�ӷ�Ƶ		��Ƶϵ�� ��TKDIV+1����0������Ƶ
#define TKTMS(N)	(N<<0)	 //N=0-31	//�ŵ�ʱ������   �ŵ�ʱ�䣺 (TKTMS)*32*Ttk  , TKTMS�������0�����Ϊ0���ŵ� 

//TKxCHS����				   		//x=0-5
#define MPOL(N)      (N<<7) 	 	//N=0-1	   //0- TKxMS <  ATKxM; 1-  TKxMS >=  ATKxM
#define NPOL(N)      (N<<6) 	 	//N=0-1	   //0- TKxMS <  ATKxN; 1-  TKxMS >=  ATKxN
#define TKPS(N)    	(N<<0) 			//N=0-14   0����ѡ    1-13��ӦTK0-TK12; 14��ӦTKCAP

//TKIF����					  //TKST=0��һ����λ
#define TKIF5		(1<<5)
#define TKIF4		(1<<4)
#define TKIF3		(1<<3)
#define TKIF2		(1<<2)
#define TKIF1		(1<<1)
#define TKIF0		(1<<0)

//TKPWC����
#define TKPC(N)		(N<<6)	 //N=0-3
#define VDS(N)		(N<<4)	 //N=0-3
#define VIRS(N)		(N<<2)	 //N=0-3
#define TKPWS(N)	(N<<1)	 //N=0-1
#define TKCVS(N)	(N<<0)	 //N=0-1

//TLCON����
#define TLEIE(N)		(N<<7)	 //N=0-1
#define TLKIE(N)		(N<<6)	 //N=0-1
#define TLLIE(N)		(N<<5)	 //N=0-3
#define TLLVS(N)		(N<<1)	 //N=0-3
#define TLPOL(N)		(N<<0)	 //N=0-1


//TLFLG����					  //TKST=0��һ����λ
#define TLERR		(1<<7)
#define TLKOV		(1<<6)
#define TLLOV		(1<<5)

//TLCKS??
#define TLCKS(N)		(N<<0)	 //N=0-7

//TLCKS??
#define TLCOMS(N)		(N<<0)	 //N=0-7


typedef union 
{	
	unsigned long int 	dwVal;
	unsigned int 		wVal[2];
	unsigned char 		bVal[4];
}
DWORD_UNION;

typedef union 
{	
	unsigned int 	wVal;
	unsigned char 	bVal[2];
}
WORD_UNION;

typedef enum
{
	 TS_INIT,
	 TS_DEAL
} TSState_T;

enum 
{
	AREA_FINGER_TOUCH,
	AREA_PNOISE_PLUS,
	AREA_PNOISE,
	AREA_NNOISE,
	AREA_OVER_LOW		
};
enum 
{
	WHEEL_SLIDER_NO_TOUCH,
	WHEEL_SLIDER_TOUCH,	
};

#define WHEEL 	0
#define SLIDER  1
enum
{
	TS_CH0,
	TS_CH1,
	TS_CH2,
	TS_CH3,
	TS_CH4,
	TS_CH5,
	TS_CH6,
	TS_CH7,
	TS_CH8,
	TS_CH9,
	TS_CH10,
	TS_CH11,
	TS_CH12,
};
enum
{
	LED_ON,
	LED_OFF,
	LED_ALL_OFF,
};
#ifndef TS_SERVICE_C
#if (KEY_CH_COUNT <= 8)
	#define TYPE_SN		unsigned char 
#elif (KEY_CH_COUNT <= 16)
	#define TYPE_SN		unsigned int
#else
	#define TYPE_SN		unsigned long int
#endif
#endif

#define 	KEY_BREAK					0x1000     	//�̰�̧��
#define 	KEY_LONG					0x2000     	//����
#define 	KEY_LONG_BREAK		0x3000			//����̧��
#define 	KEY_LONG_START		0x4000			//������ʼ   

#define K1					0x0001
#define K2					0x0002
#define K3					0x0003
#define K4					0x0004
#define K5					0x0005
#define K6					0x0006
#define K7					0x0007
#define K8					0x0008
#define K9					0x0009
#define K10					0x000a
#define K11					0x000b
#define K12					0x000c
#define K13					0x000d
#define K14					0x000e
#define K15					0x000f
#define K16					0x0010
#define K17					0x0011
#define K18					0x0012
#define K19					0x0013
#define K20					0x0014
#define K21					0x0015
#define K22					0x0016
#define K23					0x0017
#define K24					0x0018
#define K25					0x0019
#define K26					0x001a
#define K27					0x001b
#define K28					0x001c
#define K29					0x001d
#define K30					0x001e
#define K31					0x001f

enum 
{
	TK_STATE_RELEASE,
	TK_STATE_SINGLE_KEY_PRESS,	
	TK_STATE_DOUBLE_KEY_PRESS,
};

#define TS_LONG_START_TIME	250
#define TS_LONG_TIME				70



