

/**
  ******************************************************************************

  CLOCK Setup For STM32F446RE
  Author:   ControllersTech
  Updated:  2nd Aug 2020

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 4
  *            PLL_N                          = 180
  *            PLL_P                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */

#include "RccConfig.h"

void SysClockConfig (void)
{
		/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	
	1. ENABLE HSE and wait for the HSE to become Ready
	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the Clock Source and wait for it to be set
	
	********************************************************/
	
	
	#define PLL_M 	4
	#define PLL_N 	180
	#define PLL_P 	0  // PLLP = 2

	// 1. ENABLE HSE and wait for the HSE to become Ready
	RCC->CR |= RCC_CR_HSEON;  
	while (!(RCC->CR & RCC_CR_HSERDY));
	
	// 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS; 
	
	
	// 3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	
	// 4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	// AHB PR
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	
	// APB1 PR
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	
	// APB2 PR
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
	
	
	// 5. Configure the MAIN PLL
	RCC->PLLCFGR = (PLL_M <<0) | (PLL_N << 6) | (PLL_P <<16) | (RCC_PLLCFGR_PLLSRC_HSE);

	// 6. Enable the PLL and wait for it to become ready
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY));
	
	// 7. Select the Clock Source and wait for it to be set
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

