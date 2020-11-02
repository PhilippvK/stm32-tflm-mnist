 /**
  ******************************************************************************
  * File Name          : msic.h
  * Author             : Philipp v. K. <philipp.van-kempen@tum.de>
  * Description        : Contains for helper functions for the mnist example
  ******************************************************************************
  * @attention
  *
  * Copyright 2020 <TODO>
  *
  ******************************************************************************
  */

#ifndef SRC_MISC_MISC_H_
#define SRC_MISC_MISC_H_

#include "tensorflow/lite/c/common.h"

#define TOUCH_DOT_RADIUS 8
#define INPUT_IMAGE_SIZE 28
#define INPUT_BOX_THICKNESS 2
#define INPUT_IMAGE_SIZE_PIXEL 224
#define INPUT_BOX_TOP_MARGIN                                             \
    ((BSP_LCD_GetYSize() - INPUT_IMAGE_SIZE_PIXEL -                      \
    2 * INPUT_BOX_THICKNESS) / 2)
#define INPUT_BOX_LEFT_MARGIN                                            \
    ((BSP_LCD_GetXSize() - INPUT_IMAGE_SIZE_PIXEL -                      \
    2 * INPUT_BOX_THICKNESS) / 2)
#define INPUT_BOX_SIDE_Y_MARGIN INPUT_BOX_TOP_MARGIN
#define INPUT_BOX_SIDE_X_MARGIN INPUT_BOX_LEFT_MARGIN
#define INPUT_BOX_X_OUTER INPUT_BOX_SIDE_X_MARGIN
#define INPUT_BOX_X_INNER INPUT_BOX_SIDE_X_MARGIN + INPUT_BOX_THICKNESS
#define INPUT_BOX_Y_OUTER INPUT_BOX_SIDE_Y_MARGIN
#define INPUT_BOX_Y_INNER INPUT_BOX_SIDE_Y_MARGIN + INPUT_BOX_THICKNESS
#define INPUT_BOX_WIDTH (INPUT_IMAGE_SIZE_PIXEL + 2 * INPUT_BOX_THICKNESS)


void MNISTReset(void);
uint8_t* MNISTGetNNInputImage(void);
uint16_t AverageImageBlock(uint32_t block_size, uint32_t x, uint32_t y);
void PreprocessImage(void);
uint8_t Convert565RGBToGS(uint16_t pixel);
uint8_t Convert8888RGBToGS(uint16_t pixel);
void DrawInputBox(void);
void SaveMNISTInput(void);
void DrawInputScreen(void);
char determine_char(int8_t *out_array);
void printPercentages(int8_t *output_array);
uint8_t DrawInBox(uint32_t x, uint32_t y, uint32_t dot_radius);
void PrintMNISTHint(void);
bool GetTouchInput(void);
void MNISTHandleOutput(int8_t* output_array);

#endif  // SRC_MISC_MISC_H_
