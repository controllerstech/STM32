/*
 * touch.h
 *
 *  Created on: Jan 6, 2020
 *      Author: Kotetsu Yamamoto
 *      Copyright [Kotetsu Yamamoto]

MIT License

Copyright (c) 2020 Kotestu Yamamoto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */

#ifndef INC_TOUCH_H_
#define INC_TOUCH_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define TP_PRES_DOWN 0x80
#define TP_CATH_PRES 0x40
#define CMD_RDX 0xD0
#define CMD_RDY 0x90
#define XPT_XMIN 350
#define XPT_YMIN 350
#define XPT_XMAX 3800
#define XPT_YMAX 3600
#define XPT_WIDTH (XPT_XMAX - XPT_XMIN)
#define XPT_HEIGHT (XPT_YMAX - XPT_YMIN)

void XPT2046_Init(void);
void XPT2046_Update(uint16_t *x, uint16_t *y);
uint8_t XPT2046_IsReasonable(uint16_t x, uint16_t y);

#ifdef __cplusplus
}
#endif

#endif /* INC_TOUCH_H_ */
