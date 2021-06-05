
//I2CCON定义
#define I2CE(N)		(N<<7)
#define I2CIE(N)	(N<<6)
#define STA(N)		(N<<5)
#define STP(N)		(N<<4)
#define CKHD(N)		(N<<3)
#define AAK(N)		(N<<2)
#define CBSE(N)		(N<<1)
#define STFE(N)		(N<<0)

//I2CADR定义
#define   GCE(N)		(N<<7) //N = 0~1

//I2CFLG定义
#define I2CF		(1<<0)


typedef enum {
  I2CE_disable  	= 0,
  I2CE_enable  	= 1,
} I2CE_TypeDef;

typedef enum {
  I2CIE_disable  	= 0,
  I2CIE_enable  	= 1,
} I2CIE_TypeDef;

typedef enum {
  STFE_disable  	= 0,
  STFE_enable  	= 1,
} STFE_TypeDef;


typedef enum {
  I2C_SEL_P30_P31  	= 0,
	I2C_SEL_P03_P02  	= 1,
} I2CIOS_TypeDef;
void I2C_init(I2CE_TypeDef i2ce,I2CIE_TypeDef i2cie,STFE_TypeDef stfe,unsigned char i2cadr,unsigned char i2ccr);
void I2C_SelectComPin(I2CIOS_TypeDef i2cios);