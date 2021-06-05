#ifndef __ADKEY_H
#define __ADKEY_H
/*************************************************************************************************************/
void adkey_init(void);
void ad_out(unsigned char value);

#define KEY1	P33
#define KEY2	P34
#define KEY3	P01
#define KEY4	P03
#define KEY5	P02
#define KEY6	P00

#define TOUCH1	0x01
#define TOUCH2	0x02
#define TOUCH3	0x04
#define TOUCH4	0x08
#define TOUCH5	0x10
#define TOUCH6	0x20

/*************************************************************************************************************/
#endif