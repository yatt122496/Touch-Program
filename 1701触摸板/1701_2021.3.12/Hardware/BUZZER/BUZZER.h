#ifndef BUZZER_H
#define BUZZER_H
//#include "Config.h"
#include <SN8F5703.h>
#include "Delay.h"

#define ERR_TONE P21
#define KEY_TONE P22
#define PWR_TONE P23

void Buz_Init(void);
void BUZ_PWR_TONE(void);
void BUZ_KEY_TONE(void);
void BUZ_ERR_TONE(void);

#endif