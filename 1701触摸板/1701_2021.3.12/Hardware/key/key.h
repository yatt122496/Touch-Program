#ifndef KEY_H
#define KEY_H
#include "Config.h"

void ScanKey(void);
unsigned char ScanKey1(void);
void SlideKey(void);//»¬¶¯°´¼ü
#define POWKEY 0x01 //sw7
#define ECOKEY 0x80 //A
#define K1 0x40  //K1
#define K2 0x20
#define K3 0x10
#define K4 0x08
#define K5 0x04
#define K6 0x02
#define K1K2 0x60
#define K2K3 0x30
#define K3K4 0x18
#define K4K5 0x0c
#define K5K6 0x06
#define K2K5 0x24
#endif