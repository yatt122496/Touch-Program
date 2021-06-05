#ifndef WDT_H
#define WDT_H
/*************************************************************************************************************/
//WDCON定义
#define WDTS(N)				(N<<6)		//N=0~2
#define WDRE(N)				(N<<0)		//N=0~1


//WDFLG定义
#define WDIF			(1<<1)
#define WDRF			(1<<0)


typedef enum {
  WDTS_DISABLE  	= 0,
  WDTS_IRCH  			= 1,
  WDTS_IRCL  			= 2,
} WDTS_TypeDef;

typedef enum {
  WDRE_int  	= 0,
  WDRE_reset  	= 1,
} WDRE_TypeDef;

void WDT_init(WDTS_TypeDef wdts,WDRE_TypeDef wdre,unsigned int wdtvh);
void WDT_FeedDog(void);
/*************************************************************************************************************/
#endif