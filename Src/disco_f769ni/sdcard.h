/**
  ******************************************************************************
  * @file           : sdcard.h
  * @brief          : Header for sdcard.c file.
  *                   TODO
  ******************************************************************************
  * @attention
  *
  * Copyright 2020 <TODO>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SRC_DISCO_F413ZH_SDCARD_H_
#define SRC_DISCO_F413ZH_SDCARD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include "ff_gen_drv.h"
#include "sd_diskio.h"


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
uint32_t get_files(const char* path, const char* extension, char* files[],
                   FSIZE_t sizes[]);
uint8_t* get_data(const char* path, char* file, FSIZE_t size);
uint32_t test_txt_file(void);

/* Private defines -----------------------------------------------------------*/
#define MAX_FILES 16
#define MAX_FILENAME_LEN 32
#define MAX_PATH_LEN 64

#ifdef __cplusplus
}
#endif

#endif  // SRC_DISCO_F413ZH_SDCARD_H_
