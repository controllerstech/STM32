/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "mt25tl01g.h"
/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */

#define QSPI_Info_t                 MT25TL01G_Info_t
#define QSPI_Interface_t            MT25TL01G_Interface_t
#define QSPI_Transfer_t             MT25TL01G_Transfer_t
#define QSPI_DualFlash_t            MT25TL01G_DualFlash_t
#define QSPI_ODS_t                  MT25TL01G_ODS_t

typedef enum
{
  QSPI_ERASE_8K   =  MT25TL01G_ERASE_4K ,       /*!< 8K size Sector erase = 2 x 4K as Dual flash mode is used for this board   */
  QSPI_ERASE_64K  =  MT25TL01G_ERASE_32K ,      /*!< 64K size Sector erase = 2 x 32K as Dual flash mode is used for this board */
  QSPI_ERASE_128K =  MT25TL01G_ERASE_64K ,      /*!< 128K size Sector erase = 2 x 64K as Dual mode is used for this board      */
  QSPI_ERASE_4K   =  MT25TL01G_ERASE_4K ,       /*!< 4K size Sector erase if DULA FLASH is Disabled   */
  QSPI_ERASE_32K  =  MT25TL01G_ERASE_32K ,      /*!< 32K size Sector erase if DULA FLASH is Disabled*/
  QSPI_ERASE64K =  MT25TL01G_ERASE_64K ,      /*!< 64K size Sector erase if DULA FLASH is Disabled     */
  QSPI_ERASE_CHIP =  MT25TL01G_ERASE_CHIP       /*!< Whole chip erase */

} QSPI_Erase_t;

typedef enum
{
  QSPI_ACCESS_NONE = 0,          /*!<  Instance not initialized,             */
  QSPI_ACCESS_INDIRECT,          /*!<  Instance use indirect mode access     */
  QSPI_ACCESS_MMP                /*!<  Instance use Memory Mapped Mode read  */
} QSPI_Access_t;

typedef struct
{
  QSPI_Access_t    IsInitialized;   /*!<  Instance access Flash method     */
  QSPI_Interface_t InterfaceMode;   /*!<  Flash Interface mode of Instance */
  QSPI_Transfer_t  TransferRate;    /*!<  Flash Transfer mode of Instance  */
  uint32_t             DualFlashMode;   /*!<  Flash dual mode                  */
  uint32_t             IsMspCallbacksValid;
} QSPI_Ctx_t;

typedef struct
{
  QSPI_Interface_t        InterfaceMode;   /*!<  Current Flash Interface mode */
  QSPI_Transfer_t         TransferRate;    /*!<  Current Flash Transfer mode  */
  QSPI_DualFlash_t        DualFlashMode;   /*!<  Dual Flash mode              */
} QSPI_Init_t;

typedef struct
{
  uint32_t FlashSize;
  uint32_t ClockPrescaler;
  uint32_t SampleShifting;
  uint32_t DualFlashMode;
}MX_QSPI_Init_t;


/* QSPI instances number */
#define QSPI_INSTANCES_NUMBER         1U

/* Definition for QSPI modes */
#define QSPI_SPI_MODE            (QSPI_Interface_t)MT25TL01G_SPI_MODE      /* 1 Cmd Line, 1 Address Line and 1 Data Line    */
#define QSPI_SPI_1I2O_MODE       (QSPI_Interface_t)MT25TL01G_SPI_1I2O_MODE /* 1 Cmd Line, 1 Address Line and 2 Data Lines   */
#define QSPI_SPI_2IO_MODE        (QSPI_Interface_t)MT25TL01G_SPI_2IO_MODE  /* 1 Cmd Line, 2 Address Lines and 2 Data Lines  */
#define QSPI_SPI_1I4O_MODE       (QSPI_Interface_t)MT25TL01G_SPI_1I4O_MODE /* 1 Cmd Line, 1 Address Line and 4 Data Lines   */
#define QSPI_SPI_4IO_MODE        (QSPI_Interface_t)MT25TL01G_SPI_4IO_MODE  /* 1 Cmd Line, 4 Address Lines and 4 Data Lines  */
#define QSPI_DPI_MODE            (QSPI_Interface_t)MT25TL01G_DPI_MODE      /* 2 Cmd Lines, 2 Address Lines and 2 Data Lines */
#define QSPI_QPI_MODE            (QSPI_Interface_t)MT25TL01G_QPI_MODE      /* 4 Cmd Lines, 4 Address Lines and 4 Data Lines */

/* Definition for QSPI transfer rates */
#define QSPI_STR_TRANSFER        (QSPI_Transfer_t)MT25TL01G_STR_TRANSFER /* Single Transfer Rate */
#define QSPI_DTR_TRANSFER        (QSPI_Transfer_t)MT25TL01G_DTR_TRANSFER /* Double Transfer Rate */

/* Definition for QSPI dual flash mode */
//#define QSPI_DUALFLASH_DISABLE   (QSPI_DualFlash_t)MT25TL01G_DUALFLASH_DISABLE   /* Dual flash mode enabled  */
/* Definition for QSPI Flash ID */
#define QSPI_FLASH_ID            QSPI_FLASH_ID_1

/* QSPI block sizes for dual flash */
#define QSPI_BLOCK_8K            MT25TL01G_SECTOR_4K
#define QSPI_BLOCK_64K           MT25TL01G_BLOCK_32K
#define QSPI_BLOCK_128K          MT25TL01G_BLOCK_64K




/* MT25TL01G Micron memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE            26     /* Address bus width to access whole memory space */
#define QSPI_PAGE_SIZE             256


uint8_t CSP_QUADSPI_Init(void);
uint8_t CSP_QSPI_Erase_Chip(void);
uint8_t CSP_QSPI_WriteMemory(uint8_t* buffer, uint32_t address, uint32_t buffer_size);
uint8_t CSP_QSPI_EnableMemoryMappedMode(void);


uint8_t CSP_QSPI_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size);

/*   MT25TL01G support 4K, 32K, 64K size block erase commands.
     QSPI_ERASE_8K   =  MT25TL01G_ERASE_4K ,  8K size Sector erase = 2 x 4K if Dual flash mode is used
  	 QSPI_ERASE_64K  =  MT25TL01G_ERASE_32K , 64K size Sector erase = 2 x 32K as Dual flash mode is used
  	 QSPI_ERASE_128K =  MT25TL01G_ERASE_64K , 128K size Sector erase = 2 x 64K as Dual mode is used
*/
uint8_t CSP_QSPI_EraseBlock(uint32_t BlockAddress, QSPI_Erase_t BlockSize);



/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
