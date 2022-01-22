
#include "../../lv_conf.h"
#include "../../lvgl/lvgl.h"

#include "lcd_lvgl.h"

#include "tft.h"
#include "user_setting.h"
#include "string.h"
//#include "functions.h"

#define MAX(a,b) ((a)>(b) ? (a):(b))

uint16_t DISP_fb[(MAX(DISP_VER_RES,DISP_HOR_RES))]; // LCD FRAME Buffer for 1 ROW



static lv_disp_drv_t disp_drv;
//static int32_t x1_flush;
//static int32_t y1_flush;
//static int32_t x2_flush;
//static int32_t y2_fill;
//static int32_t y_fill_act;
//static const lv_color_t * buf_to_flush;

static lv_color_t disp_buf1[DISP_HOR_RES * 10];
static lv_color_t disp_buf2[DISP_HOR_RES * 10];

static volatile uint32_t t_saved = 0;
void monitor_cb(lv_disp_drv_t * d, uint32_t t, uint32_t p)
{
	t_saved = t;
}


/*These 3 functions are needed by LittlevGL*/
static void tft_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p);


void Display_init(int rotation)
{

	static lv_disp_draw_buf_t buf;

	lv_disp_draw_buf_init(&buf, disp_buf1, disp_buf2, DISP_HOR_RES * 10);

	lv_disp_drv_init(&disp_drv);

	uint16_t ID = readID();
	tft_init(ID);
	setRotation(rotation);

	fillScreen(BLACK);

	disp_drv.draw_buf = &buf;
	disp_drv.flush_cb = tft_flush;
	disp_drv.monitor_cb = monitor_cb;
	disp_drv.hor_res = DISP_HOR_RES;
	disp_drv.ver_res = DISP_VER_RES;
	disp_drv.rotated = rotation;
	lv_disp_drv_register(&disp_drv);
}



/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Flush a color buffer
 * @param x1 left coordinate of the rectangle
 * @param x2 right coordinate of the rectangle
 * @param y1 top coordinate of the rectangle
 * @param y2 bottom coordinate of the rectangle
 * @param color_p pointer to an array of colors
 */
static void tft_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_p)
{
	/*Return if the area is out the screen*/

	if(area->x2 < 0) return;
	if(area->y2 < 0) return;
	if(area->x1 > DISP_HOR_RES - 1) return;
	if(area->y1 > DISP_VER_RES - 1) return;


	int indx = 0;
//	setAddrWindow(area->x1, area->y1, area->x2, area->y2);
    for(int y=area->y1;y<=area->y2;y++)
    {
        for(int x=area->x1;x<=area->x2;x++)
        {
//        	drawPixel(x, y, color_p->full);
            DISP_fb[indx] = color_p->full;
            color_p++;
            indx++;
        }

        indx = 0;
        fillFB(area->x1, y, area->x2, y, DISP_fb);

    }

    lv_disp_flush_ready(drv);
}
