/**
  ******************************************************************************

  Timer2 Setup for Delay in STM32F103C8T6
  Author:   ControllersTech
  Updated:  26th FEB 2021

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/


#include "stm32f10x.h"                  // Device header

void TIM2_Config (void);

void Delay_us (uint16_t us);

void Delay_ms (uint16_t ms);
