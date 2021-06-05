#ifndef PWM_H
#define PWM_H

//PWMxCON
#define PWMIE(N)			(N<<7)	  //N=0-1
#define PWMTOG(N)			(N<<6)	  //N=0-1
#define PWMMOD(N)			(N<<3)	  //N=0-7
#define PWMPOL(N)			(N<<2)	  //N=0-1
#define PWMCKS_SYS		0 
#define PWMCKS_IL			1	  
#define PWMCKS_IH			2	 


//PWMIF  
#define  PWM5IF	(1<<5)
#define  PWM4IF	(1<<4)
#define  PWM3IF	(1<<3)
#define  PWM2IF	(1<<2)
#define  PWM1IF	(1<<1)
#define  PWM0IF	(1<<0)	

//LEFLG
#define LEBSY1	(1<<6)
#define LEBSY0	(1<<2)

//PWMCON
#define TIE(N)			(N<<7)
#define ZIE(N)			(N<<6)
#define PIE(N)			(N<<5)
#define NIE(N)			(N<<4)
#define MS(N)				(N<<3)		//中心对齐模式
#define MOD(N)			(N<<0)	    //互补模式

#define CKS(N)			(N)	//N=0~6


//PWMCFG
#define TOG(N)			(N<<7)


typedef enum {
	PWM_CH0 = 0,
	PWM_CH1 = 1,
	PWM_CH2 = 2,
	PWM_CH3 = 3,
	PWM_CH4 = 4,
	PWM_CH5 = 5,
} PWM_Channel_TypeDef;

typedef enum {
	PWMIE_off = 0,
	PWMIE_on = 1,
} PWMIE_TypeDef;

typedef enum {
	CKS_SYS	= 0,
	CKS_IL	= 1,
	CKS_IH	= 2,
} PWM_CKS_TypeDef;

typedef enum {
	Toggle_Off = 0,
	Toggle_On = 1,
} PWM_Toggle_TypeDef;




void PWM0_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal);
void PWM1_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal,
								unsigned char pwmmod);
void PWM2_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal,
								unsigned char pwmmod);
void PWM3_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal);
void PWM4_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal);
void PWM5_init(	PWMIE_TypeDef ie,
								PWM_CKS_TypeDef cks,
								PWM_Toggle_TypeDef toggle,
								unsigned char Prescal);
void PWM0_CfgDivDuty(unsigned int DIV,unsigned int DUT);
void PWM1_CfgDivDuty(unsigned int DIV,unsigned int DUT);
void PWM2_CfgDivDuty(unsigned int DIV,unsigned int DUT);
void PWM3_CfgDivDuty(unsigned int DIV,unsigned int DUT);
void PWM4_CfgDivDuty(unsigned int DIV,unsigned int DUT);
void PWM5_CfgDivDuty(unsigned int DIV,unsigned int DUT);
void PWM_CfgLedut(unsigned int Ledut);
void PWM_CfgLedwtm(unsigned int Ledwtm);
void PWM1_WriteLedat(unsigned char Ledat);
void PWM2_WriteLedat(unsigned char Ledat);
void PWM_Enable(PWM_Channel_TypeDef Pwmch);
void PWM_Disable(PWM_Channel_TypeDef Pwmch);

#endif