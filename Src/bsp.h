/**
  ******************************************************************************
  * File Name          : bsp.h
  * Author             : Philipp v. K. <philipp.van-kempen@tum.de>
  * Description        : This file is used to init the Board Support Packages
  ******************************************************************************
  * @attention
  *
  * Copyright 2020 <TODO>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SRC_DISCO_F769NI_BSP_H_
#define SRC_DISCO_F769NI_BSP_H_
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

void BSP_Init(void);

#ifdef __cplusplus
}
#endif
#endif  // SRC_DISCO_F769NI_BSP_H_
