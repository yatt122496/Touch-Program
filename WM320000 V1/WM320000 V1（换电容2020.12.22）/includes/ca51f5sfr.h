#ifndef __CA51F2_SFR_H__
#define __CA51F2_SFR_H__

sfr P0              = 0x80;
sfr SP              = 0x81;
sfr DP0L            = 0x82;
sfr DP0H            = 0x83;
sfr DP1L            = 0x84;
sfr DP1H            = 0x85;
sfr PWCON           = 0x86;
sfr PCON            = 0x87;
sfr TCON            = 0x88;
sfr TMOD            = 0x89;
sfr TL0             = 0x8a;
sfr TL1             = 0x8b;
sfr TH0             = 0x8c;
sfr TH1             = 0x8d;
sfr IDLST           = 0x8e;
sfr STPST           = 0x8f;

sfr PWMEN           = 0x90;
sfr PWM2DUTH        = 0x91;
sfr PWM3DUTL        = 0x92;
sfr PWM3DUTH        = 0x93;
sfr PWM4DUTL        = 0x94;
sfr PWM4DUTH        = 0x95;
sfr PWM5DUTL        = 0x96;
sfr PWM5DUTH        = 0x97;
sfr S0CON           = 0x98;
sfr S0BUF           = 0x99;
sfr PWM5DIVH        = 0x9a;
sfr PWM0DUTL        = 0x9b;
sfr PWM0DUTH        = 0x9c;
sfr PWM1DUTL        = 0x9d;
sfr PWM1DUTH        = 0x9e;
sfr PWM2DUTL        = 0x9f;

sfr WDCON           = 0xa0;
sfr WDFLG           = 0xa1;
sfr WDVTHL          = 0xa2;
sfr WDVTHH          = 0xa3;
sfr PWM3DIVH        = 0xa4;
sfr PWM4DIVL        = 0xa5;
sfr PWM4DIVH        = 0xa6;
sfr PWM5DIVL        = 0xa7;
sfr IE              = 0xa8;
sfr PWM0DIVL        = 0xa9;
sfr PWM0DIVH        = 0xaa;
sfr PWM1DIVL        = 0xab;
sfr PWM1DIVH        = 0xac;
sfr PWM2DIVL        = 0xad;
sfr PWM2DIVH        = 0xae;
sfr PWM3DIVL        = 0xaf;

sfr P3              = 0xb0;
sfr PWM0CKD         = 0xb1;
sfr PWM1CKD         = 0xb2;
sfr PWM2CKD         = 0xb3;
sfr PWM3CKD         = 0xb4;
sfr PWM4CKD         = 0xb5;
sfr PWM5CKD         = 0xb6;
sfr PWMIF           = 0xb7;
sfr IP              = 0xb8;
sfr PWM0CON         = 0xb9;
sfr PWM1CON         = 0xba;
sfr PWM2CON         = 0xbb;
sfr PWM3CON         = 0xbc;
sfr PWM4CON         = 0xbd;
sfr PWM5CON         = 0xbe;
sfr LEFLG           = 0xbf;

sfr I2CCON          = 0xc0;
sfr I2CADR          = 0xc1;
sfr I2CADM          = 0xc2;
sfr I2CCR           = 0xc3;
sfr I2CDAT          = 0xc4;
sfr I2CSTA          = 0xc5;
sfr I2CFLG          = 0xc6;
sfr LEDAT1          = 0xc7;
sfr T2CON           = 0xc8;
sfr T2MOD           = 0xc9;
sfr T2CL            = 0xca;
sfr T2CH            = 0xcb;
sfr TL2             = 0xcc;
sfr TH2             = 0xcd;
sfr LEDWTML         = 0xce;
sfr LEDWTMH         = 0xcf;

sfr PSW             = 0xd0;
sfr EP0CON          = 0xd1;
sfr EP1CON          = 0xd2;
sfr EP2CON          = 0xd3;
sfr EPIF            = 0xd4;
sfr TMCON           = 0xd5;
sfr TMSNU           = 0xd6;
sfr LEDAT0          = 0xd7;
sfr UDCKS           = 0xd8;
sfr TK3MSH          = 0xd9;
sfr TK4MSL          = 0xda;
sfr TK4MSH          = 0xdb;
sfr TK5MSL          = 0xdc;
sfr TK5MSH          = 0xdd;
sfr AK0CON          = 0xde;
sfr AK1CON          = 0xdf;

sfr ACC             = 0xe0;
sfr TK0MSL          = 0xe1;
sfr TK0MSH          = 0xe2;
sfr TK1MSL          = 0xe3;
sfr TK1MSH          = 0xe4;
sfr TK2MSL          = 0xe5;
sfr TK2MSH          = 0xe6;
sfr TK3MSL          = 0xe7;
sfr LVDCON          = 0xe8;
sfr ATK2CH          = 0xe9;
sfr ATK3CL          = 0xea;
sfr ATK3CH          = 0xeb;
sfr ATK4CL          = 0xec;
sfr ATK4CH          = 0xed;
sfr ATK5CL          = 0xee;
sfr ATK5CH          = 0xef;

sfr B               = 0xf0;
sfr TK4CHS          = 0xf1;
sfr TK5CHS          = 0xf2;
sfr ATK0CL          = 0xf3;
sfr ATK0CH          = 0xf4;
sfr ATK1CL          = 0xf5;
sfr ATK1CH          = 0xf6;
sfr ATK2CL          = 0xf7;
sfr TKCON           = 0xf8;
sfr TKCFG           = 0xf9;
sfr TKMTS           = 0xfa;
sfr TKIF            = 0xfb;
sfr TK0CHS          = 0xfc;
sfr TK1CHS          = 0xfd;
sfr TK2CHS          = 0xfe;
sfr TK3CHS          = 0xff;
/*  BIT Register  */
/*	PSW	*/
sbit CY   		= 0xD7;
sbit AC   		= 0xD6;
sbit F0   		= 0xD5;
sbit RS1  		= 0xD4;
sbit RS0  		= 0xD3;
sbit OV   		= 0xD2;
sbit DPS   		= 0xD1;
sbit P    		= 0xD0;
		  		
/*	TCON	*/
sbit TF1  		= 0x8F;
sbit TR1  		= 0x8E;
sbit TF0  		= 0x8D;
sbit TR0  		= 0x8C;
sbit IE1  		= 0x8B;
sbit IT1  		= 0x8A;
sbit IE0  		= 0x89;
sbit IT0  		= 0x88;

/*	S0CON   */
sbit SM0  		= 0x9F;
sbit SM1  		= 0x9E;
sbit SM2  		= 0x9D;
sbit REN  		= 0x9C;
sbit TB8  		= 0x9B;
sbit RB8  		= 0x9A;
sbit TI0  		= 0x99;
sbit RI0  		= 0x98;

/*	IE	*/
sbit EA   		= 0xAF;
sbit INT4EN  		= 0xAE;
sbit INT3EN  		= 0xAD;
sbit ES0	   	= 0xAC;
sbit ET1  		= 0xAB;
sbit EX1  		= 0xAA;
sbit ET0  		= 0xA9;
sbit EX0  		= 0xA8;

/*	IP	*/ 
sbit PS1  		= 0xBE;
sbit PT2  		= 0xBD;
sbit PS0   		= 0xBC;
sbit PT1  		= 0xBB;
sbit PX1  		= 0xBA;
sbit PT0  		= 0xB9;
sbit PX0  		= 0xB8;

/*	T2CON	*/
sbit TF2   		= 0xCF;
sbit TR2  		= 0xCE;
sbit T2R1  		= 0xCD;
sbit T2R0  		= 0xCC;
sbit T2IE     = 0xCB;
sbit UCKS  		= 0xCA;
sbit T2P1  		= 0xC9;
sbit T2P0  		= 0xC8;


/*	P0	*/
sbit P00		= P0^0;
sbit P01		= P0^1;
sbit P02		= P0^2;
sbit P03		= P0^3;
sbit P04		= P0^4;
sbit P05		= P0^5;
sbit P06		= P0^6;
sbit P07		= P0^7;

/*	P3	*/
sbit P30		= P3^0;
sbit P31		= P3^1;
sbit P32		= P3^2;
sbit P33		= P3^3;
sbit P34		= P3^4;
sbit P35		= P3^5;




#endif  
