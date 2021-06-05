#ifndef __ADKEY_H
#define __ADKEY_H
/*************************************************************************************************************/
void adkey_init(void);
void ad_out(unsigned char value);

#define KEY1	P04
#define KEY2	P03
#define KEY3	P07
#define KEY4	P01
#define KEY5	P30
#define KEY6	P00

//#define TOUCH1	0x01
//#define TOUCH2	0x02
//#define TOUCH3	0x04
//#define TOUCH4	0x08
//#define TOUCH5	0x10
//#define TOUCH6	0x20

#define TOUCH1	0x10
#define TOUCH2	0x08
#define TOUCH3	0x02
#define TOUCH4	0x04
#define TOUCH5	0x01
#define TOUCH6	0x20

/*************************************************************************************************************/
#endif