

#ifndef INC_LCD_LVGL_H_
#define INC_LCD_LVGL_H_

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include "../../lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define DISP_HOR_RES 240
#define DISP_VER_RES 320


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void Display_init(int rotation);

void DMA_Handler (void);
#endif /* INC_LCD_LVGL_H_ */
