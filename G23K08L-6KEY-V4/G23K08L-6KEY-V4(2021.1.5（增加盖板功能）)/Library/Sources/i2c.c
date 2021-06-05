#ifndef _I2C_C_
#define _I2C_C_

/*********************************************************************************************************************/
#include "ca51f5_config.h"
#include "../../../includes/ca51f5sfr.h"
#include "../../../includes/ca51f5xsfr.h"
#include "../../../includes/gpiodef_f5.h"

#include "../../../includes/system.h"
#include "../../../Library/includes/i2c.h"
#include <intrins.h>
/*********************************************************************************************************************/
void I2C_init(I2CE_TypeDef i2ce,I2CIE_TypeDef i2cie,STFE_TypeDef stfe,unsigned char i2cadr,unsigned char i2ccr)
{
	I2CCON = I2CE(i2ce) | I2CIE(i2cie) | STA(0) | STP(0)| CKHD(1) | AAK(1)| CBSE(0) | STFE(stfe);		
	I2CADR = GCE(0)|(i2cadr>>1);
	I2CCR = (i2ccr>>1);
}

void I2C_SelectComPin(I2CIOS_TypeDef i2cios)
{
	I2CIOS = i2cios;
	if(i2cios == I2C_SEL_P30_P31)
	{
		GPIO_Init(P30F,P30_I2C_SDA_SETTING | PU_EN);
		GPIO_Init(P31F,P31_I2C_SCL_SETTING | PU_EN);		
	}
	else if(i2cios == I2C_SEL_P03_P02)
	{
		GPIO_Init(P03F,P03_I2C_SDA_SETTING | PU_EN);
		GPIO_Init(P02F,P02_I2C_SCL_SETTING | PU_EN);		
	}
}
#endif