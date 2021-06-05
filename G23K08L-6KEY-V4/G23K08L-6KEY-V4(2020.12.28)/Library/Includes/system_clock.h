#ifndef SYS_CLOCK_H
#define SYS_CLOCK_H

//CKCON¼Ä´æÆ÷¶¨Òå
#define IHCKE		(1<<7)
#define ILCKE		(1<<6)

#define SCKS		(1<<0)		 //0-IH,1-IL

#define CKSEL_IRCH	0	
#define CKSEL_IRCL	1


void Sys_Clk_Set_IRCH(void);
void Sys_Clk_Set_IRCL(void);
#endif
