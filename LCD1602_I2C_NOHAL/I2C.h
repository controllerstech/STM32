

/**
  ******************************************************************************

  I2C Setup For STM32F446RE
  Author:   ControllersTech
  Updated:  31st Jan 2020

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/

#include <stdint.h>

void I2C_Config (void);

void I2C_Start (void);

void I2C_Write (uint8_t data);

void I2C_Address (uint8_t Address);

void I2C_Stop (void);

void I2C_WriteMulti (uint8_t *data, uint8_t size);

void I2C_Read (uint8_t Address, uint8_t *buffer, uint8_t size);
