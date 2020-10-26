/**
  ******************************************************************************
  * @file    ts_calibration.h
  * @author  (partially) MCD Application Team
  * @author  Philipp v. K. <philipp.van-kempen@tum.de>
  * @brief   This file contains the headers of the ts_calibration file.
  ******************************************************************************
  * @attention
  *
  * [Copyright (c) 2020 STMicroelectronics]
  *
  * Modifications by @PhilippvK
  * - Changed formatting according to cpplint
  *
  ******************************************************************************
  */

#ifndef SRC_DISCO_F413ZI_TS_CALIBRATION_H_
#define SRC_DISCO_F413ZI_TS_CALIBRATION_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
uint8_t  Touchscreen_Calibration(void);
uint16_t TouchScreen_Get_Calibrated_X(uint16_t x);
uint16_t TouchScreen_Get_Calibrated_Y(uint16_t y);
uint8_t  TouchScreen_IsCalibrationDone(void);
#ifdef __cplusplus
}
#endif

#endif  // SRC_DISCO_F413ZI_TS_CALIBRATION_H_
