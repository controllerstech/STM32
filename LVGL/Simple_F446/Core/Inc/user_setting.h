

#ifndef USER_SETTING_H_
#define USER_SETTING_H_

#include "stm32f4xx_hal.h"


#define RD_PORT GPIOA
#define RD_PIN  GPIO_PIN_0

#define WR_PORT GPIOA
#define WR_PIN  GPIO_PIN_1

#define CD_PORT GPIOA
#define CD_PIN  GPIO_PIN_4

#define CS_PORT GPIOB
#define CS_PIN  GPIO_PIN_0

#define RESET_PORT GPIOC
#define RESET_PIN  GPIO_PIN_1

#define D0_PORT GPIOA
#define D0_PIN GPIO_PIN_9

#define D1_PORT GPIOC
#define D1_PIN GPIO_PIN_7

#define D2_PORT GPIOA
#define D2_PIN GPIO_PIN_10

#define D3_PORT GPIOB
#define D3_PIN GPIO_PIN_3

#define D4_PORT GPIOB
#define D4_PIN GPIO_PIN_5

#define D5_PORT GPIOB
#define D5_PIN GPIO_PIN_4

#define D6_PORT GPIOB
#define D6_PIN GPIO_PIN_10

#define D7_PORT GPIOA
#define D7_PIN GPIO_PIN_8


void lcd_delay (uint16_t t);



// configure macros for the data pins.

#define write_8(d) { \
 GPIOA->BSRR = 0x0700 << 16; \
 GPIOB->BSRR = 0x0438 << 16; \
 GPIOC->BSRR = 0x0080 << 16; \
 GPIOA->BSRR = (((d) & (1<<0)) << 9) \
             | (((d) & (1<<2)) << 8) \
             | (((d) & (1<<7)) << 1); \
 GPIOB->BSRR = (((d) & (1<<3)) << 0) \
             | (((d) & (1<<4)) << 1) \
             | (((d) & (1<<5)) >> 1) \
             | (((d) & (1<<6)) << 4); \
 GPIOC->BSRR = (((d) & (1<<1)) << 6); \
}


#define read_8() (          (((GPIOA->IDR & (1<<9)) >> 9) \
                           | ((GPIOC->IDR & (1<<7)) >> 6) \
                           | ((GPIOA->IDR & (1<<10)) >> 8) \
                           | ((GPIOB->IDR & (1<<3)) >> 0) \
                           | ((GPIOB->IDR & (1<<5)) >> 1) \
                           | ((GPIOB->IDR & (1<<4)) << 1) \
                           | ((GPIOB->IDR & (1<<10)) >> 4) \
                           | ((GPIOA->IDR & (1<<8))  >> 1))\
				 )



/********************* For 180 MHz *****************************/
//#define WRITE_DELAY { WR_ACTIVE8; }
//#define READ_DELAY  { RD_ACTIVE16;}


/************************** For 72 MHZ ****************************/
#define WRITE_DELAY { }
#define READ_DELAY  { RD_ACTIVE;  }


/************************** For 100 MHZ ****************************/
//#define WRITE_DELAY { WR_ACTIVE2; }
//#define READ_DELAY  { RD_ACTIVE4; }


/************************** For 216 MHZ ****************************/
//#define WRITE_DELAY { WR_ACTIVE8; WR_ACTIVE8; } //216MHz
//#define IDLE_DELAY  { WR_IDLE4;WR_IDLE4; }
//#define READ_DELAY  { RD_ACTIVE16;RD_ACTIVE16;RD_ACTIVE16;}


/************************** For 48 MHZ ****************************/
//#define WRITE_DELAY { }
//#define READ_DELAY  { }


/*****************************  DEFINES FOR DIFFERENT TFTs   ****************************************************/

//#define SUPPORT_0139              //S6D0139 +280 bytes
//#define SUPPORT_0154              //S6D0154 +320 bytes
//#define SUPPORT_05A1              //for S6D05A1
//#define SUPPORT_1289              //SSD1289,SSD1297 (ID=0x9797) +626 bytes, 0.03s
//#define SUPPORT_1580              //R61580 Untested
//#define SUPPORT_1963              //only works with 16BIT bus anyway
//#define SUPPORT_4532              //LGDP4532 +120 bytes.  thanks Leodino
//#define SUPPORT_4535              //LGDP4535 +180 bytes
//#define SUPPORT_68140             //RM68140 +52 bytes defaults to PIXFMT=0x55
//#define SUPPORT_7735
//#define SUPPORT_7781              //ST7781 +172 bytes
//#define SUPPORT_8230              //UC8230 +118 bytes
#define SUPPORT_8347D             //HX8347-D, HX8347-G, HX8347-I, HX8367-A +520 bytes, 0.27s
//#define SUPPORT_8347A             //HX8347-A +500 bytes, 0.27s
//#define SUPPORT_8352A             //HX8352A +486 bytes, 0.27s
//#define SUPPORT_8352B             //HX8352B
//#define SUPPORT_8357D_GAMMA       //monster 34 byte
//#define SUPPORT_9163              //
//#define SUPPORT_9225              //ILI9225-B, ILI9225-G ID=0x9225, ID=0x9226, ID=0x6813 +380 bytes
//#define SUPPORT_9320              //ID=0x0001, R61505, SPFD5408, ILI9320
//#define SUPPORT_9325              //RM68090, ILI9325, ILI9328, ILI9331, ILI9335
//#define SUPPORT_9326_5420         //ILI9326, SPFD5420 +246 bytes
//#define SUPPORT_9342              //costs +114 bytes
//#define SUPPORT_9806              //UNTESTED
#define SUPPORT_9488_555          //costs +230 bytes, 0.03s / 0.19s
//#define SUPPORT_B509_7793         //R61509, ST7793 +244 bytes
#define OFFSET_9327 32            //costs about 103 bytes, 0.08s


#if (defined(USES_16BIT_BUS))   //only comes from SPECIALs
#define USING_16BIT_BUS 1
#else
#define USING_16BIT_BUS 0
#endif


#endif /* USER_SETTING_H_ */
