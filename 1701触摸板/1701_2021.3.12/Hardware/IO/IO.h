#ifndef IO_H
#define IO_H
//#include "Config.h"
#include <SN8F5703.h>

#define LED0 P14
#define LED1 P15
#define MOTOR_ON P06
#define AOG_CTL  P20

#define PM25_TR  P25
#define FILTER_DET  P17
//#define PM25_AD  P16


void IO_Init(void);

#endif