/**
  ******************************************************************************
  * @file    stm32f7xx_it.cc
  * @author  (partially) MCD Application Team
  * @author  Philipp v. K. <philipp.van-kempen@tum.de>
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * [Copyright (c) 2020 STMicroelectronics]
  *
  * Modifications by @PhilippvK
  * - Renamed to `stm32f7xx_it.cc`
  * - Cleaned up to have a minimal config
  * - Changed formatting according to cpplint
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
extern SD_HandleTypeDef uSdHandle;

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
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
 * @brief Handles SDMMC2 DMA Rx transfer interrupt request.
 * @retval None
 */
void BSP_SDMMC2_DMA_Rx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(uSdHandle.hdmarx);
}

/**
 * @brief Handles SDMMC2 DMA Tx transfer interrupt request.
 * @retval None
 */
void BSP_SDMMC2_DMA_Tx_IRQHandler(void)
{
  HAL_DMA_IRQHandler(uSdHandle.hdmatx);
}

/**
 * @brief Handles SD1 card interrupt request.
 * @retval None
 */
void BSP_SDMMC2_IRQHandler(void)
{
  HAL_SD_IRQHandler(&uSdHandle);
}
