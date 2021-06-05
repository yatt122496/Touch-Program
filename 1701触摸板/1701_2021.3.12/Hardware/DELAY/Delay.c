#include "Delay.h"


void Delay_MS(unsigned int ms)
{
	unsigned int x = 0;
	unsigned int y = 0; 
	
	for(x=0; x<730; x++)
	{
		for(y=0; y<ms; y++);
	}

}
//		Delay_us(5);//10us

void Delay_us(unsigned int us)
{
	unsigned int x = 0;
	unsigned int y = 0; 	

	for(y=0; y<us*3; y++);	

}

