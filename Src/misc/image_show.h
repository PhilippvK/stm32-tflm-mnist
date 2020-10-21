/**
  ******************************************************************************
  * @file           : audio.h
  * @brief          : Header for audio.c file.
  *                   This file contains the exported function prototypes for audio
  ******************************************************************************
  * @attention
  *
  * Copyright 2020 <TODO>
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SRC_MISC_IMAGE_SHOW_H_
#define SRC_MISC_IMAGE_SHOW_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void ImageShow(uint8_t* data, uint16_t x, uint16_t y);

#ifdef __cplusplus
}
#endif

#endif  // SRC_MISC_IMAGE_SHOW_H_
