/**
  ******************************************************************************
  * @file           : main.h
  * @author         : Philipp v. K. <philipp.van-kempen@tum.de>
  * @brief          : Header for main.cc file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * The file was originally generated with
  * STM32CubeIDE [Copyright (c) 2020 STMicroelectronics]
  * but modified intensively.
  *
  * Copyright 2020 <TODO>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SRC_DISCO_F413ZH_MAIN_H_
#define SRC_DISCO_F413ZH_MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* STM32 Board related Includes */
#include "stm32f4xx_hal.h"
#include "stm32f413h_discovery.h"
#include "stm32f413h_discovery_lcd.h"
#include "stm32f413h_discovery_ts.h"
#include "stm32f413h_discovery_audio.h"
#include "stm32f413h_discovery_sd.h"

/* Touchscreen Includes */
#include "ts_calibration.h"

/* FatFs/SD Includes */
#include "ff_gen_drv.h"
#include "sd_diskio.h"

#ifdef FAKE_TOUCH
/* ImageViewer Includes */
#include "image_show.h"
#endif /* FAKE_TOUCH */

// TODO(PhilippvK): Comment
#include "misc.h"
#include "bsp.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define MX_UART_Init MX_USART6_UART_Init

/* Exported macro ------------------------------------------------------------*/
// 565 - 16 bit
#define GS2RGB(x) (uint16_t)(((x >> 3) << 11)|((x >> 2) << 5)|(x >> 3))

/* Exported functions prototypes ---------------------------------------------*/
int __io_putchar(int ch);
void Error_Handler(void);
uint8_t CheckForUserInput(void);

/* Private defines -----------------------------------------------------------*/
#define B_USER_Pin GPIO_PIN_0
#define B_USER_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_14
#define VCP_TX_GPIO_Port GPIOG
#define VCP_RX_Pin GPIO_PIN_9
#define VCP_RX_GPIO_Port GPIOG
#define UartHandle huart6

#ifdef __cplusplus
}
#endif

#endif  // SRC_DISCO_F413ZH_MAIN_H_
