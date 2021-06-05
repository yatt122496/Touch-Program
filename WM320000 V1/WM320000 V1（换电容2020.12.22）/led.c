#ifndef __LED_C_
#define __LED_C_

/*********************************************************************************************************************/
#include "ca51f5_config.h"
#include "includes\ca51f5sfr.h"
#include "includes\ca51f5xsfr.h"
#include "includes\gpiodef_f5.h"
#include "includes\system.h"
#include "Library\includes\uart.h"
#include "Library\Includes\tmc.h"	

#include <intrins.h>

#include "includes/led.h"
/*********************************************************************************************************************/

/*********************************************************************************************************************/
void led_init(void)
{
	P04F = 2;
	P04 = 1;
	P07F = 2;
	P07 = 1;
	P34F = 2;
	P34 = 1;
	P32F = 2;
	P32 = 1;
}

#endif