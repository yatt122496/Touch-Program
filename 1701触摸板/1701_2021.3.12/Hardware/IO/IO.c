#include "IO.h"

/***************************************	
PxUR		   
0: 禁止上拉
1: 使能上拉
PxM
0:输入模式
1:输出模式
****************************************/

void IO_Init(void)
{
//		P0UR = 0X00;
//		P0 = 0X00;
//		P0M = 0XFF;
		
		P1UR = 0X00;//p17设置成输入
		P1   = 0x00;
		P1M  |= 0X7f;
		
		P2UR = 0X00;
		P2 = 0X00;
		P2M |= 0X0F;
}

