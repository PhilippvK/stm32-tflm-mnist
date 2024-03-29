/**
 ******************************************************************************
 * @file      sysmem.c
 * @author    Auto-generated by STM32CubeIDE
 * @author    Philipp v. K. <philipp.van-kempen@tum.de>
 * @brief     STM32CubeIDE Minimal System Memory calls file
 *
 *            For more information about which c-functions
 *            need which of these lowlevel functions
 *            please consult the Newlib libc-manual
 ******************************************************************************
 * @attention
 *
 * [Copyright (c) 2020 STMicroelectronics]
 *
 * Modifications by @PhilippvK:
 * - Renamed to sysmem.cc
 * - Changed formatting according to cpplint
 *
 ******************************************************************************
 */

/* Includes */
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

/* Variables */
extern int errno;
register char * stack_ptr asm("sp");

/* Functions */

/**
 _sbrk
 Increase program data space. Malloc and related functions depend on this
**/
caddr_t _sbrk(int incr) {
  extern char end asm("end");
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0) {
    heap_end = &end;
  }

  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr) {
    errno = ENOMEM;
    return (caddr_t) -1;
  }

  heap_end += incr;

  return (caddr_t) prev_heap_end;
}

