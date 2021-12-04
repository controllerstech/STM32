/*
 * xpt2046.c
 *
 *  Created on: Jan 6, 2020
 *      Author: Kotetsu Yamamoto
 *      Copyright [Kotetsu Yamamoto]

I refer https://github.com/PaulStoffregen/XPT2046_Touchscreen/blob/master/XPT2046_Touchscreen.cpp

from Original source:

 * Copyright (c) 2015, Paul Stoffregen, paul@pjrc.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "xpt2046.h"

#define T_IRQ XPT2046_ReadIRQ()
#define T_CS_ON XPT2046_SetCS()
#define T_CS_OFF XPT2046_ResetCS()

#define READ_TIMES 	5
#define LOST_VAL 	1
#define ERR_RANGE 50
#define Z_THRESHOLD     400
#define Z_THRESHOLD_INT	75
#define MSEC_THRESHOLD  3

extern SPI_HandleTypeDef hspi2;
extern void Error_Handler(void);
static uint8_t XPT2046_initilazed = 0;

static void XPT2046_SetCS(void)
{
	HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_SET);
}

static void XPT2046_ResetCS(void)
{
	HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_RESET);
}

static void XPT2046_Write_Byte(uint8_t num)
{
	hspi2.Instance->CR2 &= ~(SPI_DATASIZE_16BIT); // Set 8 bit mode
	__HAL_SPI_ENABLE(&hspi2);
	if (HAL_SPI_Transmit(&hspi2, &num, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
	__HAL_SPI_DISABLE(&hspi2);
}

static uint16_t XPT2046_Read_AD(uint8_t CMD)
{
	uint8_t num[2];
	uint16_t ret;

	T_CS_OFF;
	XPT2046_Write_Byte(CMD);
	HAL_Delay(6);

	hspi2.Instance->CR2 |= SPI_DATASIZE_16BIT; // Set 16 bit mode
	__HAL_SPI_ENABLE(&hspi2);
	if (HAL_SPI_Receive(&hspi2, num, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
	__HAL_SPI_DISABLE(&hspi2);
	T_CS_ON;

	ret = num[0] << 8 | num[1];
	ret >>= 3;
	ret &= (1<<12)-1;

	return ret;
}

static int16_t besttwoavg( int16_t x , int16_t y , int16_t z ) {
  int16_t da, db, dc;
  int16_t reta = 0;
  if ( x > y ) da = x - y; else da = y - x;
  if ( x > z ) db = x - z; else db = z - x;
  if ( z > y ) dc = z - y; else dc = y - z;

  if ( da <= db && da <= dc ) reta = (x + y) >> 1;
  else if ( db <= da && db <= dc ) reta = (x + z) >> 1;
  else reta = (y + z) >> 1;   //    else if ( dc <= da && dc <= db ) reta = (x + y) >> 1;

  return (reta);
}

void XPT2046_Init(void)
{
	XPT2046_initilazed = 1;
}

void XPT2046_Update(uint16_t *x, uint16_t *y)
{
	int16_t data[6];
	static uint32_t ptime = 0;

	if (XPT2046_initilazed == 0) {
		return;
	}

	if (HAL_GetTick() - ptime < MSEC_THRESHOLD) {
		return;
	}

	int16_t z1 = XPT2046_Read_AD(0xb1); // z1
	int32_t z = z1 + 4095;
	int16_t z2 = XPT2046_Read_AD(0xc1); // z2
	z -= z2;
	if (z >= Z_THRESHOLD) {
		XPT2046_Read_AD(0x91);  // dummy 1st X measure
		data[0] = XPT2046_Read_AD(0x91);
		data[1] = XPT2046_Read_AD(0xd1);
		data[2] = XPT2046_Read_AD(0x91);
		data[3] = XPT2046_Read_AD(0xd1);
	} else {
		data[0] = data[1] = data[2] = data[3] = 0;
	}
	data[4] = XPT2046_Read_AD(0x91);
	data[5] = XPT2046_Read_AD(0xd0);
	ptime = HAL_GetTick();
	if (z < 0) z = 0;
	int16_t intx = besttwoavg( data[0], data[2], data[4] );
	int16_t inty = besttwoavg( data[1], data[3], data[5] );
	if (z >= Z_THRESHOLD) {
		*x = intx;
		*y = inty;
	}
}

uint8_t XPT2046_IsReasonable(uint16_t x, uint16_t y)
{
	if (x >= XPT_XMIN && x <= XPT_XMAX && y >= XPT_YMIN && y <= XPT_YMAX) {
		return 1;
	}
	return 0;
}
