/**
  ******************************************************************************
  * @file    stm32f7xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
 ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SRC_DISCO_F769NI_STM32F7XX_IT_H_
#define SRC_DISCO_F769NI_STM32F7XX_IT_H_

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

void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void AUDIO_DFSDMx_DMAx_BUTTOM_LEFT_IRQHandler(void);
void AUDIO_DFSDMx_DMAx_BUTTOM_RIGHT_IRQHandler(void);
void AUDIO_OUT_SAIx_DMAx_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif  // SRC_DISCO_F769NI_STM32F7XX_IT_H_
