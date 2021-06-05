#ifndef TM1668_H
#define	TM1668_H

#define SIO  P11
#define CLK  P12
#define STB  P13




void writeTM1668_com(unsigned char com);
void TM1668_Init(void);
//void display_LED(unsigned char  data);
void writeTM1668_data(unsigned char shi, unsigned char ge,unsigned char D7,unsigned char D8,unsigned char D9,unsigned char D10,unsigned char D11);

#endif


