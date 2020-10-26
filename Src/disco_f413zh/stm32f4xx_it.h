/**
  ******************************************************************************
  * @file    stm32f4xx_it.h
  * @author  (partially) MCD Application Team
  * @author  Philipp v. K. <philipp.van-kempen@tum.de>
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * [Copyright (c) 2020 STMicroelectronics]
  *
  * Modifications by @PhilippvK
  * - Cleaned up to have a minimal config
  * - Changed formatting according to cpplint
  *
 ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SRC_DISCO_F413ZH_STM32F4XX_IT_H_
#define SRC_DISCO_F413ZH_STM32F4XX_IT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif  // SRC_DISCO_F413ZH_STM32F4XX_IT_H_
