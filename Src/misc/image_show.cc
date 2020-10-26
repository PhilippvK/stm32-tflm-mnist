/**
  ******************************************************************************
  * @file    image_show.cc
  * @author  Philipp v. K. <philipp.van-kempen@tum.de>
  * @brief   Contains Routines for drawing BMP images on the LCD
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2020 <TODO>
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "image_show.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  TODO
  * @param  None
  * @retval None
  */
void ImageShow(uint8_t* data, uint16_t x, uint16_t y) {
  BSP_LCD_DrawBitmap(x, y, data);
}
