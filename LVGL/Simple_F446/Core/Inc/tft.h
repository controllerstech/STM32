
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TFT_H
#define __TFT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

#define  WIDTH    ((uint16_t)240)
#define  HEIGHT   ((uint16_t)320)
   
#define true	1
#define false	0

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


#define MIPI_DCS_REV1   (1<<0)
#define AUTO_READINC    (1<<1)
#define READ_BGR        (1<<2)
#define READ_LOWHIGH    (1<<3)
#define READ_24BITS     (1<<4)
#define XSA_XEA_16BIT   (1<<5)
#define READ_NODUMMY    (1<<6)
#define INVERT_GS       (1<<8)
#define INVERT_SS       (1<<9)
#define MV_AXIS         (1<<10)
#define INVERT_RGB      (1<<11)
#define REV_SCREEN      (1<<12)
#define FLIP_VERT       (1<<13)
#define FLIP_HORIZ      (1<<14)




void tft_init(uint16_t ID);

void reset(void);

uint16_t readID(void);

void setRotation(uint8_t r);
void invertDisplay(uint8_t i);

void setAddrWindow(int16_t x, int16_t y, int16_t x1, int16_t y1);

void pushColors16b(uint16_t * block, int16_t n, uint8_t first);

void fillFB(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t *color);

void fillScreen(uint16_t color);

#ifdef __cplusplus
}
#endif

#endif /* __HX8347G_H */

