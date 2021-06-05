#ifndef _CA51F2_XRAM_H_
#define _CA51F2_XRAM_H_

/*********************************************************************************************************************/
#ifdef _MAIN_C_
#define XRAM_U8										volatile unsigned char xdata
#define XRAM_U16									volatile unsigned int xdata
#define XRAM_AT_(x)									_at_ x		
#else
#define XRAM_U8										extern volatile unsigned char xdata
#define XRAM_U16									extern volatile unsigned int xdata
#define XRAM_AT_(x)
#endif

XRAM_U8 P00F     	XRAM_AT_(0x8000);
XRAM_U8 P01F        XRAM_AT_(0x8001);
XRAM_U8 P02F        XRAM_AT_(0x8002);
XRAM_U8 P03F        XRAM_AT_(0x8003);
XRAM_U8 P04F        XRAM_AT_(0x8004);
XRAM_U8 P05F        XRAM_AT_(0x8005);
XRAM_U8 P06F        XRAM_AT_(0x8006);
XRAM_U8 P07F        XRAM_AT_(0x8007);
                      
                           
XRAM_U8 P30F        XRAM_AT_(0x8018);
XRAM_U8 P31F        XRAM_AT_(0x8019);
XRAM_U8 P32F        XRAM_AT_(0x801a);
XRAM_U8 P33F        XRAM_AT_(0x801b);
XRAM_U8 P34F        XRAM_AT_(0x801c);
XRAM_U8 P35F        XRAM_AT_(0x801d);

                        
XRAM_U8 CKCON       XRAM_AT_(0x8030);
XRAM_U8 CKDIV       XRAM_AT_(0x8031);
XRAM_U8 IHCFG      	XRAM_AT_(0x8032);
XRAM_U8 ILCFGL      XRAM_AT_(0x8033);
XRAM_U8 ILCFGH     	XRAM_AT_(0x8034);


XRAM_U8 ATK0NL     	XRAM_AT_(0x8050);
XRAM_U8 ATK0NH     	XRAM_AT_(0x8051);
XRAM_U8 ATK1NL     	XRAM_AT_(0x8052);
XRAM_U8 ATK1NH     	XRAM_AT_(0x8053);
XRAM_U8 ATK2NL     	XRAM_AT_(0x8054);
XRAM_U8 ATK2NH     	XRAM_AT_(0x8055);
XRAM_U8 ATK3NL     	XRAM_AT_(0x8056);
XRAM_U8 ATK3NH     	XRAM_AT_(0x8057);
XRAM_U8 ATK4NL     	XRAM_AT_(0x8058);
XRAM_U8 ATK4NH     	XRAM_AT_(0x8059);
XRAM_U8 ATK5NL     	XRAM_AT_(0x805a);
XRAM_U8 ATK5NH     	XRAM_AT_(0x805b);
XRAM_U8 TKMAXF     	XRAM_AT_(0x805c);
XRAM_U8 TKMINF     	XRAM_AT_(0x805d);

XRAM_U8 LEDUTL      XRAM_AT_(0x8060);
XRAM_U8 LEDUTH     	XRAM_AT_(0x8061);

XRAM_U8 SPMAX      	XRAM_AT_(0x8100);
XRAM_U8 I2CIOS      XRAM_AT_(0x8101);
XRAM_U8 TKCKS      	XRAM_AT_(0x8102);
XRAM_U8 TKPWC      	XRAM_AT_(0x8103);

XRAM_U8 LVDCFG      XRAM_AT_(0x8105);
XRAM_U8 TLEN0      	XRAM_AT_(0x8106);
XRAM_U8 TLDAT0      XRAM_AT_(0x8107);
XRAM_U8 TLCON      	XRAM_AT_(0x8108);
XRAM_U8 TLFLG      	XRAM_AT_(0x8109);
XRAM_U8 TLCKS      	XRAM_AT_(0x810a);
XRAM_U8 TLCNTKL     XRAM_AT_(0x810b);
XRAM_U8 TLCNTKH     XRAM_AT_(0x810c);
XRAM_U8 TLCNTLL     XRAM_AT_(0x810d);
XRAM_U8 TLCNTLH     XRAM_AT_(0x810e);
XRAM_U8 TLDIV     	XRAM_AT_(0x810f);

XRAM_U8 TLCOMS      XRAM_AT_(0x8110);
XRAM_U8 TLEN1      	XRAM_AT_(0x8111);
XRAM_U8 TLDAT1      XRAM_AT_(0x8112);


XRAM_U8 P00C      	XRAM_AT_(0x8120);
XRAM_U8 P01C      	XRAM_AT_(0x8121);
XRAM_U8 P02C      	XRAM_AT_(0x8122);
XRAM_U8 P03C      	XRAM_AT_(0x8123);
XRAM_U8 P04C      	XRAM_AT_(0x8124);
XRAM_U8 P05C      	XRAM_AT_(0x8125);
XRAM_U8 P06C      	XRAM_AT_(0x8126);
XRAM_U8 P07C      	XRAM_AT_(0x8127);

XRAM_U8 P30C      	XRAM_AT_(0x8138);
XRAM_U8 P31C      	XRAM_AT_(0x8139);
XRAM_U8 P32C      	XRAM_AT_(0x813a);
XRAM_U8 P33C      	XRAM_AT_(0x813b);
XRAM_U8 P34C      	XRAM_AT_(0x813c);
XRAM_U8 P35C      	XRAM_AT_(0x813d);
                            
XRAM_U8 MECON       XRAM_AT_(0xfc00);
XRAM_U8 FSCMD       XRAM_AT_(0xfc01);
XRAM_U8 FSDAT       XRAM_AT_(0xfc02);
XRAM_U8 LOCK        XRAM_AT_(0xfc03);
XRAM_U8 PADRD       XRAM_AT_(0xfc04);
XRAM_U8 PTSL        XRAM_AT_(0xfc05);
XRAM_U8 PTSH        XRAM_AT_(0xfc06);
XRAM_U8 MEMPTEC     XRAM_AT_(0xfc0d);

/*********************************************************************************************************************/

#endif