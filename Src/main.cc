/**
  ******************************************************************************
  * @file           : main.cc
  * @author         : Philipp v. K. <philipp.van-kempen@tum.de>
  * @brief          : Main program for mnist example
  *                   Initializes Peripherals and calls Setup- and
  *                   Loop-Routines of TFLite Model
  ******************************************************************************
  * @attention
  *
  * The file was originally generated with
  * STM32CubeIDE [Copyright (c) 2020 STMicroelectronics]
  * but modified intensively.
  *
  * Copyright 2020 <TODO>
  *
  ******************************************************************************
  */

/* STM32Cube Includes --------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "clock.h"
#ifdef FAKE_TOUCH
#include "sdcard.h"
#endif /* FAKE_TOUCH*/


/* TFLM Includes -------------------------------------------------------------*/
#include "main_functions.h"

/* Private includes ----------------------------------------------------------*/
#include <string.h>
#include <math.h>
#include <cstdio>

#ifdef BENCHMARKING
#include "benchmarking.h"
#endif /* BENCHMARKING */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define HEADBAND_HEIGHT    48

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#ifdef FAKE_TOUCH
char* filenames[MAX_FILES];
FSIZE_t filesizes[MAX_FILES];
uint8_t* data;
#endif /* FAKE_TOUCH */

/* Private function prototypes -----------------------------------------------*/
static void BSP_Welcome(void);
#ifdef FAKE_TOUCH
void displayFileName(char* name);
#endif /* FAKE_TOUCH*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
  /* Local Variables */
#ifdef FAKE_TOUCH
  const uint32_t tick_limit = 5000;
  uint32_t last_ticks = 0;
  uint32_t file_index = 0;
  uint32_t file_count;
#endif /* FAKE_TOUCH*/

  /* Reset of all peripherals, Initializes interfaces and Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  MX_UART_Init();

  /* Setup BSP Components */
  BSP_Init();

  /* Show Welcome Screen */
  BSP_Welcome();

#ifdef FAKE_TOUCH
  while (BSP_SD_IsDetected() != SD_PRESENT) {  // TODO(PhilippvK): Fix this
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(5, BSP_LCD_GetYSize()-15,
                            (uint8_t *)"SD Not Connected", LEFT_MODE);
  }
  file_count = get_files(TFLM_EXAMPLE, TFLM_FILE_EXT, filenames, filesizes);
  if (file_count > 0) {
    file_index = 0;
  } else {
    Error_Handler();
  }
#endif /* FAKE_TOUCH */

  /* Infinite loop */
  fprintf(stderr, "--- TFLM Demo for STM32 Boards ---\n\r");
  setup();
  fprintf(stderr, "Setup done! Main loop starts now!\n\r");
  while (true) {
#ifdef FAKE_TOUCH
    if (data) {
      free(data);
    }
    data = get_data(TFLM_EXAMPLE, filenames[file_index],
                    filesizes[file_index]);
    if (data) {
      displayFileName(filenames[file_index]);
      ImageShow(data, BSP_LCD_GetXSize() / 2 - INPUT_IMAGE_SIZE / 2,
                BSP_LCD_GetYSize() / 2 - INPUT_IMAGE_SIZE / 2);
      HAL_Delay(1000);
    } else {
      Error_Handler();
    }
    file_index = (file_index + 1) % file_count;
#endif /* FAKE_TOUCH*/

    loop();

#ifdef BENCHMARKING
    print_summary(TICKS_POPULATE|TICKS_INVOKE|TICKS_RESPOND);
#endif /* BENCHMARKING */
  }

  return 0;
}


/**
  * @brief TODO
  * @retval uint8_t (1 when button clicked)
  *
  */
uint8_t CheckForUserInput(void) {
  if (BSP_PB_GetState(BUTTON_WAKEUP) != GPIO_PIN_RESET) {
    while (BSP_PB_GetState(BUTTON_WAKEUP) != GPIO_PIN_RESET) {}
    return 1;
  }
  return 0;
}

/**
  * @brief Show Welcome Message on LCD
  * @retval None
  *
  */
void BSP_Welcome() {
  /* Local Variables */
  const uint16_t delay_ms = 1000;

  /* Save old Display Configuration */
  sFONT* old_font = BSP_LCD_GetFont();
  uint32_t old_text_color = BSP_LCD_GetTextColor();
  uint32_t old_back_color = BSP_LCD_GetTextColor();
  char str[32];

  /* Clear the LCD */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Draw Banner */
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), HEADBAND_HEIGHT);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);

  /* Add Text to banner */
  BSP_LCD_SetFont(&Font16);
  BSP_LCD_DisplayStringAt(0, 5, (uint8_t *)"TFLM Demo", CENTER_MODE);
  BSP_LCD_SetFont(&Font12);
  BSP_LCD_DisplayStringAt(0, 25, (uint8_t *)"for STM32 Boards", CENTER_MODE);
  BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  sprintf(str, "Board: %16s", TFLM_BOARD);  // TODO(PhilippvK): Use snprintf
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2-20, (uint8_t *)str,
                          CENTER_MODE);
  sprintf(str, "Example: %16s", TFLM_EXAMPLE);  // TODO(PhilippvK): snprintf
  BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize()/2+10, (uint8_t *)str,
                          CENTER_MODE);

  /* Wait a moment */
  HAL_Delay(delay_ms);

  /* Restore Font and Colors*/
  BSP_LCD_SetTextColor(old_text_color);
  BSP_LCD_SetBackColor(old_back_color);
  BSP_LCD_SetFont(old_font);
}


#ifdef FAKE_TOUCH
void displayFileName(char* name) {
  char str[64];
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  sprintf(str, "<%s>", name);  // TODO(PhilippvK): snprintf
  BSP_LCD_DisplayStringAt(0, 9*BSP_LCD_GetYSize()/10, (uint8_t *)str, CENTER_MODE);
}
#endif /* FAKE_TOUCH*/

/**
  * @brief  Function used by printf tto write to the serial terminal
  * @retval int
  */
int __io_putchar(int ch) {
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
  /* User can add his own implementation to report the HAL error return state */
  fprintf(stderr, "Error_Handler called! Waiting for reset...\n\r");
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line) {
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
