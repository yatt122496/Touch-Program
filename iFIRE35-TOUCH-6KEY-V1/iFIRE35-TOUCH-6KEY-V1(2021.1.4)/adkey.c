#ifndef __ADKEY_C_
#define __ADKEY_C_

/*********************************************************************************************************************/
#include "ca51f5_config.h"
#include "includes\ca51f5sfr.h"
#include "includes\ca51f5xsfr.h"
#include "includes\gpiodef_f5.h"
#include "includes\system.h"
#include "Library\includes\uart.h"
#include "Library\Includes\tmc.h"	

#include <intrins.h>

#include "includes\adkey.h"
/*********************************************************************************************************************/

void adkey_init(void)
{
	P01F = OP_EN | OUTPUT;	//P33设置为推挽输出模式
	P01 = 1;
	P02F = OP_EN | OUTPUT;
	P02 = 1;
	P03F = OP_EN | OUTPUT;
	P03 = 1;
	P04F = OP_EN | OUTPUT;
	P04 = 1;
	P05F = OP_EN | OUTPUT;
	P05 = 1;
	P06F = OP_EN | OUTPUT;
	P06 = 1;
}

void ad_out(unsigned char value)
{
	switch(value) {
	case 1: {
		KEY1 = 0;
		break;
	}
	case 2: {
		KEY1 = 1;
		KEY2 = 0;
		break;
	}
	case 3: {
		KEY1 = 1;
		KEY2 = 1;
		KEY3 = 0;
		break;
	}
	case 4: {
		KEY1 = 1;
		KEY2 = 1;
		KEY3 = 1;
		KEY4 = 0;
		break;
	}
	case 5: {
		KEY1 = 1;
		KEY2 = 1;
		KEY3 = 1;
		KEY4 = 1;
		KEY5 = 0;
		break;
	}
	case 6: {
		KEY1 = 1;
		KEY2 = 1;
		KEY3 = 1;
		KEY4 = 1;
		KEY5 = 1;
		KEY6 = 0;
		break;
	}
	default: {
		KEY1 = 1;
		KEY2 = 1;
		KEY3 = 1;
		KEY4 = 1;
		KEY5 = 1;
		KEY6 = 1;
		break;
	}
	}
}

#endif
