/*
 * ili9341.c
 *
 *  Created on: 2019/12/26
 *      Author: Kotetsu Yamamoto
 *      Copyright [Kotetsu Yamamoto]

I refer https://github.com/dtnghia2206/TFTLCD/blob/master/TFTLCD/ILI9341/ILI9341_Driver.c

from Original source:

MIT License

Copyright (c) 2019 NghiaDT

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

#include "ili9341.h"
#include "main.h" // Hardware setting

// This function is for compatible HiLetgo ILI9341

typedef enum {
	ROTATE_0,
	ROTATE_90,
	ROTATE_180,
	ROTATE_270
} LCD_Horizontal_t;

extern void Error_Handler(void);
extern SPI_HandleTypeDef hspi1;
static __IO uint8_t spiDmaTransferComplete;

void ILI9341_Reset(void);
void ILI9341_SoftReset(void);

void LCD_WR_REG(uint8_t data);
static void LCD_WR_DATA(uint8_t data);
static void LCD_direction(LCD_Horizontal_t direction);
static void RESET_L(void);
static void RESET_H(void);
static void CS_L(void);
static void DC_L(void);
static void DC_H(void);
static void LED_H(void);

// Initialization
void ILI9341_Init(void)
{
	ILI9341_Reset();
	ILI9341_SoftReset();

	/* Power Control A */
	LCD_WR_REG(0xCB);
	LCD_WR_DATA(0x39);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x02);
	/* Power Control B */
	LCD_WR_REG(0xCF);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC1);
	LCD_WR_DATA(0x30);
	/* Driver timing control A */
	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x85);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x78);
	/* Driver timing control B */
	LCD_WR_REG(0xEA);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	/* Power on Sequence control */
	LCD_WR_REG(0xED);
	LCD_WR_DATA(0x64);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x81);
	/* Pump ratio control */
	LCD_WR_REG(0xF7);
	LCD_WR_DATA(0x20);
	/* Power Control 1 */
	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0x10);
	/* Power Control 2 */
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0x10);
	/* VCOM Control 1 */
	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x3E);
	LCD_WR_DATA(0x28);
	/* VCOM Control 2 */
	LCD_WR_REG(0xC7);
	LCD_WR_DATA(0x86);
	/* VCOM Control 2 */
	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x48);
	/* Pixel Format Set */
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);    //16bit
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x18);
#if 0
	// Little Endian for TouchGFX
	LCD_WR_REG(0xF6);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x20); // Little Endian
#endif
	/* Display Function Control */
	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x82);
	LCD_WR_DATA(0x27);
	/* 3GAMMA FUNCTION DISABLE */
	LCD_WR_REG(0xF2);
	LCD_WR_DATA(0x00);
	/* GAMMA CURVE SELECTED */
	LCD_WR_REG(0x26); //Gamma set
	LCD_WR_DATA(0x01); 	//Gamma Curve (G2.2)
	//Positive Gamma  Correction
	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x4E);
	LCD_WR_DATA(0xF1);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x00);
	//Negative Gamma  Correction
	LCD_WR_REG(0xE1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x14);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0xC1);
	LCD_WR_DATA(0x48);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x31);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x0F);
	//EXIT SLEEP
	LCD_WR_REG(0x11);

	HAL_Delay(120);

	//TURN ON DISPLAY
	LCD_WR_REG(0x29);
	LCD_WR_DATA(0x2C);

	LCD_direction(ROTATE_270);

}

void ILI9341_SetWindow(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
	// Set Window
	LCD_WR_REG(0x2a);
	LCD_WR_DATA(start_x >> 8);
	LCD_WR_DATA(0xFF & start_x);
	LCD_WR_DATA(end_x >> 8);
	LCD_WR_DATA(0xFF & end_x);

	LCD_WR_REG(0x2b);
	LCD_WR_DATA(start_y >> 8);
	LCD_WR_DATA(0xFF & start_y);
	LCD_WR_DATA(end_y >> 8);
	LCD_WR_DATA(0xFF & end_y);

}

void ILI9341_WritePixel(uint16_t x, uint16_t y, uint16_t color)
{
	uint8_t data[2];
	data[0] = color >> 8;
	data[1] = color;
	ILI9341_SetWindow(x, y, x, y);
	// Enable to access GRAM
	LCD_WR_REG(0x2c);
	DC_H();
	if (HAL_SPI_Transmit(&hspi1, data, 2, 1000) != HAL_OK) {
		Error_Handler();
	}
}

static void ConvHL(uint8_t *s, int32_t l)
{
	uint8_t v;
	while (l > 0) {
		v = *(s+1);
		*(s+1) = *s;
		*s = v;
		s += 2;
		l -= 2;
	}
}

// Call this function after ILI9341_SetWindow
// This function is non blocked
// The variable for Callback is open. User should set by himself
void ILI9341_DrawBitmap(uint16_t w, uint16_t h, uint8_t *s)
{
	// Enable to access GRAM
	LCD_WR_REG(0x2c);

	DC_H();
#if 0
	__HAL_SPI_DISABLE(&hspi1);
	hspi1.Instance->CR2 |= SPI_DATASIZE_16BIT; // Set 16 bit mode
	__HAL_SPI_ENABLE(&hspi1);
#endif
	ConvHL(s, (int32_t)w*h*2);
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)s, w * h *2);
#if 0
	__HAL_SPI_DISABLE(&hspi1);
	hspi1.Instance->CR2 &= ~(SPI_DATASIZE_16BIT); // Set 8 bit mode
	__HAL_SPI_ENABLE(&hspi1);
#endif
}

// User should call it at callback
void ILI9341_EndOfDrawBitmap(void)
{
#if 0
	__HAL_SPI_DISABLE(&hspi1);
	hspi1.Instance->CR2 &= ~(SPI_DATASIZE_16BIT); // Set 8 bit mode
	__HAL_SPI_ENABLE(&hspi1);
#endif
}

void ILI9341_Reset(void)
{
	RESET_L();
	HAL_Delay(100);
	RESET_H();
	HAL_Delay(100);
	CS_L();
	LED_H();
}

void ILI9341_SoftReset(void)
{
	uint8_t cmd;
	cmd = 0x01; //Software reset
	DC_L();
	if (HAL_SPI_Transmit(&hspi1, &cmd, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
}


void LCD_WR_REG(uint8_t data)
{
	DC_L();
	if (HAL_SPI_Transmit(&hspi1, &data, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
}

static void LCD_WR_DATA(uint8_t data)
{
	DC_H();
	if (HAL_SPI_Transmit(&hspi1, &data, 1, 1000) != HAL_OK) {
		Error_Handler();
	}
}

void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size)
{
	/* Swap endianes */
	ConvHL(pData, (int32_t)Size*2);

	DC_H();
//	HAL_SPI_Transmit(&hspi1, (uint8_t*)pData, Size * 2, HAL_MAX_DELAY);
	spiDmaTransferComplete = 0;
	HAL_SPI_Transmit_DMA(&hspi1, pData, Size*2 );
	//HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)pData, Size );
	while(spiDmaTransferComplete == 0);
}
/*
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	spiDmaTransferComplete = 1;
}
*/

static void LCD_direction(LCD_Horizontal_t direction)
{
	switch (direction) {
	case ROTATE_0:
		LCD_WR_REG(0x36);
		LCD_WR_DATA(0x48);
		break;
	case ROTATE_90:
		LCD_WR_REG(0x36);
		LCD_WR_DATA(0x28);
		break;
	case ROTATE_180:
		LCD_WR_REG(0x36);
		LCD_WR_DATA(0x88);
		break;
	case ROTATE_270:
		LCD_WR_REG(0x36);
		LCD_WR_DATA(0xE8);
		break;
	}
}

static void RESET_L(void)
{
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_RESET);
}

static void RESET_H(void)
{
	HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET);
}

static void CS_L(void)
{
	HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
}

static void DC_L(void)
{
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
}

static void DC_H(void)
{
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
}

static void LED_H(void)
{
	//HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}

