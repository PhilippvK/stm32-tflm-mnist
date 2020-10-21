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
#ifndef SRC_MISC_AUDIO_PLAYBACK_H_
#define SRC_MISC_AUDIO_PLAYBACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef FAKE_MIC
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

typedef enum {
  AUDIO_ERROR_NONE = 0,
  AUDIO_ERROR_NOTREADY,
  AUDIO_ERROR_IO,
  AUDIO_ERROR_EOF,
} AUDIO_ErrorTypeDef;
void AudioPlay_demo(void);
uint8_t AUDIO_Process(void);
void AudioInit(void);
void AudioDeinit(void);
void AudioPlay(uint8_t* data, uint32_t size);
void AudioLoop(void);
void AudioSamples(uint8_t* buf);

#endif /* FAKE_MIC */

#ifdef __cplusplus
}
#endif

#endif  // SRC_MISC_AUDIO_PLAYBACK_H_
