//EPxCON寄存器定义
#define EPIE(N)	(N<<7)	  //N=0-1
#define EPPL(N)	(N<<6)	  //N=0-1

//EPIF定义
#define EPIF2		(1<<2)
#define EPIF1		(1<<1)
#define EPIF0		(1<<0)
enum 
{
	P00_INDEX = 0,
	P01_INDEX = 1,
	P02_INDEX = 2,
	P03_INDEX = 3,
	P04_INDEX = 4,
	P05_INDEX = 5,
	P06_INDEX = 6,
	P07_INDEX = 7,

	P30_INDEX = 8,
	P31_INDEX = 9,
	P32_INDEX = 10,
	P33_INDEX = 11,
	P34_INDEX = 12,
	P35_INDEX = 13,
};