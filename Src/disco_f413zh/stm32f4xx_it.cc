/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern I2S_HandleTypeDef               haudio_i2s;
extern DFSDM_Filter_HandleTypeDef      hAudioInDfsdmFilter[];

/******************************************************************************/
/*           Cortex-M7 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void) {
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void) {
  while (1) {
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void) {
  while (1) {
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void) {
  while (1) {
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void) {
  while (1) {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void) {
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void) {
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void) {
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
  HAL_IncTick();
#ifdef FAKE_MIC
  AudioLoop();
#endif /* FAKE_MIC */
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
  * @brief  This function handles DFSDM MIC1 DMA interrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_DFSDM_DMAx_MIC1_IRQHandler(void) {
    HAL_DMA_IRQHandler(hAudioInDfsdmFilter[POS_VAL(
                       INPUT_DEVICE_DIGITAL_MIC1)].hdmaReg);
}

/**
  * @brief  This function handles DFSDM MIC2 DMA interrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_DFSDM_DMAx_MIC2_IRQHandler(void) {
  HAL_DMA_IRQHandler(hAudioInDfsdmFilter[POS_VAL(
                     INPUT_DEVICE_DIGITAL_MIC2)].hdmaReg);
}

/**
  * @brief  This function handles I2S DMA interrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_OUT_I2Sx_DMAx_IRQHandler(void) {
  HAL_DMA_IRQHandler(haudio_i2s.hdmatx);
}
