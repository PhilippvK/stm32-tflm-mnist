/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
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
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern SAI_HandleTypeDef haudio_out_sai;
extern DFSDM_Filter_HandleTypeDef       hAudioInTopLeftFilter;
extern DFSDM_Filter_HandleTypeDef       hAudioInTopRightFilter;
extern DFSDM_Filter_HandleTypeDef       hAudioInButtomLeftFilter;
extern DFSDM_Filter_HandleTypeDef       hAudioInButtomRightFilter;

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
  * @brief  This function handles DMA2 Stream 0 interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Stream0_IRQHandler(void) {
  HAL_DMA_IRQHandler(hAudioInTopLeftFilter.hdmaReg);
}

/**
  * @brief  This function handles DMA2 Stream 5 interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Stream5_IRQHandler(void) {
  HAL_DMA_IRQHandler(hAudioInTopRightFilter.hdmaReg);
}

/**
  * @brief  This function handles DMA2 Stream 1 interrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_OUT_SAIx_DMAx_IRQHandler(void) {
  HAL_DMA_IRQHandler(haudio_out_sai.hdmatx);
}

/**
  * @brief  This function handles DMA2 Stream 6 interrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_DFSDMx_DMAx_BUTTOM_LEFT_IRQHandler(void) {
  HAL_DMA_IRQHandler(hAudioInButtomLeftFilter.hdmaReg);
}

/**
  * @brief  This function handles DMA2 Stream 7 interrupt request.
  * @param  None
  * @retval None
  */
void AUDIO_DFSDMx_DMAx_BUTTOM_RIGHT_IRQHandler(void) {
  HAL_DMA_IRQHandler(hAudioInButtomRightFilter.hdmaReg);
}
