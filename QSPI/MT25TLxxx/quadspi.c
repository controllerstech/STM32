/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 26;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_3_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_QSPI;
    PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PG9     ------> QUADSPI_BK2_IO2
    PG14     ------> QUADSPI_BK2_IO3
    PG6     ------> QUADSPI_BK1_NCS
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF10     ------> QUADSPI_CLK
    PF9     ------> QUADSPI_BK1_IO1
    PH2     ------> QUADSPI_BK2_IO0
    PH3     ------> QUADSPI_BK2_IO1
    PD11     ------> QUADSPI_BK1_IO0
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PG9     ------> QUADSPI_BK2_IO2
    PG14     ------> QUADSPI_BK2_IO3
    PG6     ------> QUADSPI_BK1_NCS
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF10     ------> QUADSPI_CLK
    PF9     ------> QUADSPI_BK1_IO1
    PH2     ------> QUADSPI_BK2_IO0
    PH3     ------> QUADSPI_BK2_IO1
    PD11     ------> QUADSPI_BK1_IO0
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_9|GPIO_PIN_14|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_2|GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_11);

  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

static int32_t QSPI_Init(uint32_t Instance, QSPI_Init_t *Init);
static int32_t QSPI_DeInit(uint32_t Instance);
static int32_t QSPI_Read(uint32_t Instance, uint8_t *pData, uint32_t ReadAddr, uint32_t Size);
static int32_t QSPI_Write(uint32_t Instance, uint8_t *pData, uint32_t WriteAddr, uint32_t Size);
static int32_t QSPI_EraseBlock(uint32_t Instance, uint32_t BlockAddress, QSPI_Erase_t BlockSize);
static int32_t QSPI_EraseChip(uint32_t Instance);
static int32_t QSPI_EnableMemoryMappedMode(uint32_t Instance);
static int32_t QSPI_DisableMemoryMappedMode(uint32_t Instance);
static int32_t QSPI_ConfigFlash(uint32_t Instance, QSPI_Interface_t Mode, QSPI_Transfer_t Rate);
static HAL_StatusTypeDef PMX_QSPI_Init(QSPI_HandleTypeDef *hQspi, MX_QSPI_Init_t *Config);



QSPI_HandleTypeDef hqspi;
QSPI_Ctx_t     QSPI_Ctx[QSPI_INSTANCES_NUMBER];

static int32_t QSPI_ResetMemory(uint32_t Instance);
static int32_t QSPI_DummyCyclesCfg(uint32_t Instance, QSPI_Interface_t Mode);

int32_t QSPI_Init(uint32_t Instance, QSPI_Init_t *Init)
{
  int32_t ret = HAL_OK;
  QSPI_Info_t pInfo;
  MX_QSPI_Init_t qspi_init;
  /* Table to handle clock prescalers:
  1: For STR mode to reach max 108Mhz
  3: For DTR mode to reach max 54Mhz
  */
  static const uint32_t PrescalerTab[2] = {1, 3};

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    /* Check if instance is already initialized */
    if(QSPI_Ctx[Instance].IsInitialized == QSPI_ACCESS_NONE)
    {
      /* Msp QSPI initialization */
    	HAL_QSPI_MspInit(&hqspi);

      if(ret == HAL_OK)
      {
        /* STM32 QSPI interface initialization */
        (void)MT25TL01G_GetFlashInfo(&pInfo);
        qspi_init.ClockPrescaler = PrescalerTab[Init->TransferRate];
        qspi_init.DualFlashMode  = Init->DualFlashMode;
        uint32_t Flashsize = (Init->DualFlashMode == QSPI_DUALFLASH_ENABLE) ? (uint32_t)pInfo.FlashSize : (uint32_t)pInfo.FlashSize/2;
        qspi_init.FlashSize      = (uint32_t)POSITION_VAL(Flashsize) - 1U;
        qspi_init.SampleShifting = (Init->TransferRate == QSPI_STR_TRANSFER) ? QSPI_SAMPLE_SHIFTING_HALFCYCLE : QSPI_SAMPLE_SHIFTING_NONE;

        if(PMX_QSPI_Init(&hqspi, &qspi_init) != HAL_OK)
        {
          ret = HAL_ERROR;
        }

        /* QSPI memory reset */
        else if(QSPI_ResetMemory(Instance) != HAL_OK)
        {
          ret = HAL_ERROR;
        }

        /* Force Flash enter 4 Byte address mode */
        else if(MT25TL01G_Enter4BytesAddressMode(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
        {
          ret = HAL_ERROR;
        }

      	/* Configuration of the dummy cycles on QSPI memory side */
        else if(MT25TL01G_AutoPollingMemReady(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
        {
          ret = HAL_ERROR;
        }

        else if(QSPI_DummyCyclesCfg(Instance, QSPI_Ctx[Instance].InterfaceMode) != HAL_OK)
        {
          ret = HAL_ERROR;
        }
        else
        {
          /* Configure Flash to desired mode */
          if(QSPI_ConfigFlash(Instance, Init->InterfaceMode, Init->TransferRate) != HAL_OK)
          {
            ret = HAL_ERROR;
          }
        }
      }
    }
  }

  /* Return BSP status */
  return ret;
}

int32_t QSPI_DeInit(uint32_t Instance)
{
  int32_t ret = HAL_OK;

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    if(QSPI_Ctx[Instance].IsInitialized == QSPI_ACCESS_MMP)
    {
      if(QSPI_DisableMemoryMappedMode(Instance) != HAL_OK)
      {
        ret = HAL_ERROR;
      }
    }

    if(ret == HAL_OK)
    {
      /* Set default QSPI_Ctx values */
      QSPI_Ctx[Instance].IsInitialized = QSPI_ACCESS_NONE;
      QSPI_Ctx[Instance].InterfaceMode = QSPI_SPI_MODE;
      QSPI_Ctx[Instance].TransferRate  = QSPI_STR_TRANSFER;
      QSPI_Ctx[Instance].DualFlashMode = QSPI_DUALFLASH_ENABLE;

#if (USE_HAL_QSPI_REGISTER_CALLBACKS == 0)
      HAL_QSPI_MspDeInit(&hqspi);
#endif /* (USE_HAL_QSPI_REGISTER_CALLBACKS == 0) */

      /* Call the DeInit function to reset the driver */
      if (HAL_QSPI_DeInit(&hqspi) != HAL_OK)
      {
        ret = HAL_ERROR;
      }
    }
  }

  /* Return BSP status */
  return ret;
}

HAL_StatusTypeDef PMX_QSPI_Init(QSPI_HandleTypeDef *hQspi, MX_QSPI_Init_t *Config)
{
  /* QSPI initialization */
  /* QSPI freq = SYSCLK /(1 + ClockPrescaler) Mhz */
  hQspi->Instance                = QUADSPI;
  hQspi->Init.ClockPrescaler     = Config->ClockPrescaler;
  hQspi->Init.FifoThreshold      = 1;
  hQspi->Init.SampleShifting     = Config->SampleShifting;
  hQspi->Init.FlashSize          = Config->FlashSize;
  hQspi->Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_4_CYCLE; /* Min 50ns for nonRead */
  hQspi->Init.ClockMode          = QSPI_CLOCK_MODE_0;
  hQspi->Init.FlashID            = QSPI_FLASH_ID_1;
  hQspi->Init.DualFlash          = Config->DualFlashMode;

  return HAL_QSPI_Init(hQspi);
}

int32_t QSPI_Read(uint32_t Instance, uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
  int32_t ret = HAL_OK;

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    if(QSPI_Ctx[Instance].TransferRate == QSPI_STR_TRANSFER)
    {
      if(MT25TL01G_ReadSTR(&hqspi, QSPI_Ctx[Instance].InterfaceMode, pData, ReadAddr, Size) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }
    }
    else
    {
      if(MT25TL01G_ReadDTR(&hqspi, QSPI_Ctx[Instance].InterfaceMode, pData, ReadAddr, Size) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }
    }
  }

  /* Return BSP status */
  return ret;
}

/**
  * @brief  Writes an amount of data to the QSPI memory.
  * @param  Instance   QSPI instance
  * @param  pData      Pointer to data to be written
  * @param  WriteAddr  Write start address
  * @param  Size       Size of data to write
  * @retval BSP status
  */
int32_t QSPI_Write(uint32_t Instance, uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
  int32_t ret = HAL_OK;
  uint32_t end_addr, current_size, current_addr;
  uint8_t *write_data;

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    /* Calculation of the size between the write address and the end of the page */
    current_size = MT25TL01G_PAGE_SIZE - (WriteAddr % MT25TL01G_PAGE_SIZE);

    /* Check if the size of the data is less than the remaining place in the page */
    if (current_size > Size)
    {
      current_size = Size;
    }

    /* Initialize the address variables */
    current_addr = WriteAddr;
    end_addr = WriteAddr + Size;
    write_data = pData;

    /* Perform the write page by page */
    do
    {
      /* Check if Flash busy ? */
      if(MT25TL01G_AutoPollingMemReady(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }/* Enable write operations */
      else if(MT25TL01G_WriteEnable(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }/* Issue page program command */
      else if(MT25TL01G_PageProgram(&hqspi, QSPI_Ctx[Instance].InterfaceMode, write_data, current_addr, current_size) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }/* Configure automatic polling mode to wait for end of program */
      else if (MT25TL01G_AutoPollingMemReady(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }
      else
      {
        /* Update the address and size variables for next page programming */
        current_addr += current_size;
        write_data += current_size;
        current_size = ((current_addr + MT25TL01G_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : MT25TL01G_PAGE_SIZE;
      }
    } while ((current_addr < end_addr) && (ret == HAL_OK));
  }

  /* Return BSP status */
  return ret;
}

/**
  * @brief  Erases the specified block of the QSPI memory.
  *         MT25TL01G support 4K, 32K, 64K size block erase commands for each Die.
  *           i.e 8K, 64K, 128K at BSP level (see QSPI_Erase_t type definition)
  * @param  Instance     QSPI instance
  * @param  BlockAddress Block address to erase
  * @param  BlockSize    Erase Block size
  * @retval BSP status
  */
int32_t QSPI_EraseBlock(uint32_t Instance, uint32_t BlockAddress, QSPI_Erase_t BlockSize)
{
  int32_t ret = HAL_OK;

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    /* Check Flash busy ? */
    if(MT25TL01G_AutoPollingMemReady(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
    {
      ret = HAL_ERROR;
    }/* Enable write operations */
    else if(MT25TL01G_WriteEnable(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
    {
      ret = HAL_ERROR;
    }
    else
    {
      /* Issue Block Erase command */
      if(MT25TL01G_BlockErase(&hqspi, QSPI_Ctx[Instance].InterfaceMode, BlockAddress, (MT25TL01G_Erase_t)BlockSize) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }
    }
  }

  /* Return BSP status */
  return ret;
}

/**
  * @brief  Erases the entire QSPI memory.
  * @param  Instance  QSPI instance
  * @retval BSP status
  */
int32_t QSPI_EraseChip(uint32_t Instance)
{
  int32_t ret = HAL_OK;

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    /* Check Flash busy ? */
    if(MT25TL01G_AutoPollingMemReady(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
    {
      ret = HAL_ERROR;
    }/* Enable write operations */
    else if (MT25TL01G_WriteEnable(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
    {
      ret = HAL_ERROR;
    }
    else
    {
      /* Issue Chip erase command */
      if(MT25TL01G_ChipErase(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }
    }
  }

  /* Return BSP status */
  return ret;
}

/**
  * @brief  Configure the QSPI in memory-mapped mode
  *         Only 1 Instance can running MMP mode. And it will lock system at this mode.
  * @param  Instance  QSPI instance
  * @retval BSP status
  */
int32_t QSPI_EnableMemoryMappedMode(uint32_t Instance)
{
  int32_t ret = HAL_OK;

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    if(QSPI_Ctx[Instance].TransferRate == QSPI_STR_TRANSFER)
    {
      if(MT25TL01G_EnableMemoryMappedModeSTR(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }
      else /* Update QSPI context if all operations are well done */
      {
        QSPI_Ctx[Instance].IsInitialized = QSPI_ACCESS_MMP;
      }
    }
    else
    {
      if(MT25TL01G_EnableMemoryMappedModeDTR(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }
      else /* Update QSPI context if all operations are well done */
      {
        QSPI_Ctx[Instance].IsInitialized = QSPI_ACCESS_MMP;
      }
    }
  }

  /* Return BSP status */
  return ret;
}

/**
  * @brief  Exit form memory-mapped mode
  *         Only 1 Instance can running MMP mode. And it will lock system at this mode.
  * @param  Instance  QSPI instance
  * @retval BSP status
  */
int32_t QSPI_DisableMemoryMappedMode(uint32_t Instance)
{
  uint8_t Dummy;
  int32_t ret = HAL_OK;

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    if(QSPI_Ctx[Instance].IsInitialized != QSPI_ACCESS_MMP)
    {
      ret = HAL_ERROR;
    }/* Abort MMP back to indirect mode */
    else if(HAL_QSPI_Abort(&hqspi) != HAL_OK)
    {
      ret = HAL_ERROR;
    }
    else
    {
      /* Force QSPI interface Sampling Shift to half cycle */
      hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;

      if(HAL_QSPI_Init(&hqspi)!= HAL_OK)
      {
        ret = HAL_ERROR;
      }
      /* Dummy read for exit from Performance Enhance mode */
      else if(MT25TL01G_ReadSTR(&hqspi, QSPI_Ctx[Instance].InterfaceMode, &Dummy, 0, 1) != MT25TL01G_OK)
      {
        ret = HAL_ERROR;
      }
      else /* Update QSPI context if all operations are well done */
      {
        QSPI_Ctx[Instance].IsInitialized = QSPI_ACCESS_INDIRECT;
      }
    }
  }
  /* Return BSP status */
  return ret;
}

/**
  * @brief  Set Flash to desired Interface mode. And this instance becomes current instance.
  *         If current instance running at MMP mode then this function isn't work.
  *         Indirect -> Indirect
  * @param  Instance  QSPI instance
  * @param  Mode      QSPI mode
  * @param  Rate      QSPI transfer rate
  * @retval BSP status
  */
int32_t QSPI_ConfigFlash(uint32_t Instance, QSPI_Interface_t Mode, QSPI_Transfer_t Rate)
{
  int32_t ret = HAL_OK;

  /* Check if the instance is supported */
  if(Instance >= QSPI_INSTANCES_NUMBER)
  {
    ret = HAL_ERROR;
  }
  else
  {
    /* Check if MMP mode locked ************************************************/
    if(QSPI_Ctx[Instance].IsInitialized == QSPI_ACCESS_MMP)
    {
      ret = HAL_ERROR;
    }
    else
    {
      /* Setup MCU transfer rate setting ***************************************************/
      hqspi.Init.SampleShifting = (Rate == QSPI_STR_TRANSFER) ? QSPI_SAMPLE_SHIFTING_HALFCYCLE : QSPI_SAMPLE_SHIFTING_NONE;

      if(HAL_QSPI_Init(&hqspi)!= HAL_OK)
      {
        ret = HAL_ERROR;
      }
      else
      {
        /* Setup Flash interface ***************************************************/
        switch(QSPI_Ctx[Instance].InterfaceMode)
        {
        case MT25TL01G_QPI_MODE :               /* 4-4-4 commands */
          if(Mode != MT25TL01G_QPI_MODE)
          {
            if(MT25TL01G_ExitQPIMode(&hqspi) != MT25TL01G_OK)
            {
              ret = HAL_ERROR;
            }
          }
          break;

        case QSPI_SPI_MODE :               /* 1-1-1 commands, Power on H/W default setting */
        case QSPI_SPI_2IO_MODE :           /* 1-2-2 read commands */
        case QSPI_SPI_4IO_MODE :           /* 1-4-4 read commands */
        default :
          if(Mode == MT25TL01G_QPI_MODE)
          {
            if(MT25TL01G_EnterQPIMode(&hqspi) != MT25TL01G_OK)
            {
              ret = HAL_ERROR;
            }
          }
          break;
        }

        /* Update QSPI context if all operations are well done */
        if(ret == HAL_OK)
        {
          /* Update current status parameter *****************************************/
          QSPI_Ctx[Instance].IsInitialized = QSPI_ACCESS_INDIRECT;
          QSPI_Ctx[Instance].InterfaceMode = Mode;
          QSPI_Ctx[Instance].TransferRate  = Rate;
        }
      }
    }
  }

  /* Return BSP status */
  return ret;
}

/**
  * @brief  This function reset the QSPI Flash memory.
  *         Fore QPI+SPI reset to avoid system come from unknown status.
  *         Flash accept 1-1-1, 1-1-2, 1-2-2 commands after reset.
  * @param  Instance  QSPI instance
  * @retval BSP status
  */
static int32_t QSPI_ResetMemory(uint32_t Instance)
{
  int32_t ret = HAL_OK;

  /* Send RESET ENABLE command in QPI mode (QUAD I/Os, 4-4-4) */
  if(MT25TL01G_ResetEnable(&hqspi, MT25TL01G_QPI_MODE) != MT25TL01G_OK)
  {
    ret =HAL_ERROR;
  }/* Send RESET memory command in QPI mode (QUAD I/Os, 4-4-4) */
  else if(MT25TL01G_ResetMemory(&hqspi, MT25TL01G_QPI_MODE) != MT25TL01G_OK)
  {
    ret = HAL_ERROR;
  }/* Wait Flash ready */
  else if(MT25TL01G_AutoPollingMemReady(&hqspi, QSPI_Ctx[Instance].InterfaceMode) != MT25TL01G_OK)
  {
    ret = HAL_ERROR;
  }/* Send RESET ENABLE command in SPI mode (1-1-1) */
  else if(MT25TL01G_ResetEnable(&hqspi, QSPI_SPI_MODE) != MT25TL01G_OK)
  {
    ret = HAL_ERROR;
  }/* Send RESET memory command in SPI mode (1-1-1) */
  else if(MT25TL01G_ResetMemory(&hqspi, QSPI_SPI_MODE) != MT25TL01G_OK)
  {
    ret = HAL_ERROR;
  }
  else
  {
    QSPI_Ctx[Instance].IsInitialized = QSPI_ACCESS_INDIRECT;  /* After reset S/W setting to indirect access   */
    QSPI_Ctx[Instance].InterfaceMode = QSPI_SPI_MODE;     /* After reset H/W back to SPI mode by default  */
    QSPI_Ctx[Instance].TransferRate  = QSPI_STR_TRANSFER; /* After reset S/W setting to STR mode          */

  }

  /* Return BSP status */
  return ret;
}

/**
  * @brief  This function configure the dummy cycles on memory side.
  *         Dummy cycle bit locate in Configuration Register[7:6]
  * @param  Instance  QSPI instance
  * @retval BSP status
  */
static int32_t QSPI_DummyCyclesCfg(uint32_t Instance, QSPI_Interface_t Mode)
{
    int32_t ret= HAL_OK;
    QSPI_CommandTypeDef s_command;
  uint16_t reg=0;

  /* Initialize the read volatile configuration register command */
  s_command.InstructionMode   = (Mode == MT25TL01G_QPI_MODE) ? QSPI_INSTRUCTION_4_LINES : QSPI_INSTRUCTION_1_LINE;
  s_command.Instruction       = MT25TL01G_READ_VOL_CFG_REG_CMD;
  s_command.AddressMode       = QSPI_ADDRESS_NONE;
  s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
  s_command.DataMode          = (Mode == MT25TL01G_QPI_MODE) ? QSPI_DATA_4_LINES : QSPI_DATA_1_LINE;
  s_command.DummyCycles       = 0;
  s_command.NbData            = 2;
  s_command.DdrMode           = QSPI_DDR_MODE_DISABLE;
  s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
  s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

  /* Configure the command */
  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reception of the data */
  if (HAL_QSPI_Receive(&hqspi, (uint8_t *)(&reg), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Enable write operations */
  if (MT25TL01G_WriteEnable(&hqspi, Mode) != MT25TL01G_OK)
  {
    return HAL_ERROR;
  }

  /* Update volatile configuration register (with new dummy cycles) */
  s_command.Instruction = MT25TL01G_WRITE_VOL_CFG_REG_CMD;
  MODIFY_REG(reg, 0xF0F0, ((MT25TL01G_DUMMY_CYCLES_READ_QUAD << 4) |
                               (MT25TL01G_DUMMY_CYCLES_READ_QUAD << 12)));

  /* Configure the write volatile configuration register command */
  if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Transmission of the data */
  if (HAL_QSPI_Transmit(&hqspi, (uint8_t *)(&reg), HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Return BSP status */
  return ret;
}

/**
  * @}
  */


uint8_t CSP_QUADSPI_Init(void)
{
	hqspi.Instance = QUADSPI;
    if (QSPI_DeInit(0) != HAL_OK) {
        return HAL_ERROR;
    }

    QSPI_Init_t qspi_Init;

    qspi_Init.InterfaceMode = QSPI_QPI_MODE;
    qspi_Init.TransferRate = QSPI_STR_TRANSFER;
    qspi_Init.DualFlashMode = QSPI_DUALFLASH_DISABLE;

    if (QSPI_Init(0, &qspi_Init) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

uint8_t CSP_QSPI_Erase_Chip(void)
{
	return QSPI_EraseChip(0);
}

uint8_t CSP_QSPI_WriteMemory(uint8_t* buffer, uint32_t address, uint32_t buffer_size)
{
	return QSPI_Write(0, buffer, address, buffer_size);
}

uint8_t CSP_QSPI_EnableMemoryMappedMode(void)
{
	return QSPI_EnableMemoryMappedMode(0);
}


/*   MT25TL01G support 4K, 32K, 64K size block erase commands.
     QSPI_ERASE_8K   =  MT25TL01G_ERASE_4K ,  8K size Sector erase = 2 x 4K if Dual flash mode is used
  	 QSPI_ERASE_64K  =  MT25TL01G_ERASE_32K , 64K size Sector erase = 2 x 32K as Dual flash mode is used
  	 QSPI_ERASE_128K =  MT25TL01G_ERASE_64K , 128K size Sector erase = 2 x 64K as Dual mode is used
  	 QSPI_ERASE_4K   =  MT25TL01G_ERASE_4K ,  4K size Sector erase if DULA FLASH is Disabled
  	 QSPI_ERASE_32K  =  MT25TL01G_ERASE_32K , 32K size Sector erase if DULA FLASH is Disabled
  	 QSPI_ERASE64K =  MT25TL01G_ERASE_64K ,  64K size Sector erase if DULA FLASH is Disabled
*/
uint8_t CSP_QSPI_EraseBlock(uint32_t BlockAddress, QSPI_Erase_t BlockSize)
{

	return QSPI_EraseBlock(0, BlockAddress, BlockSize);
}

uint8_t CSP_QSPI_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
	return QSPI_Read(0, pData, ReadAddr, Size);
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
