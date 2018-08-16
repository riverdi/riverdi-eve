/*
 * Copyright (c) Riverdi Sp. z o.o. sp. k. <riverdi@riverdi.com>
 * Copyright (c) Skalski Embedded Technologies <contact@lukasz-skalski.com>
 */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/* C library inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>

/* D2xx and SPI from BRIDGETEK inclusions */
#include "ftd2xx.h"
#include "LibMPSSE_spi.h"

#define LIBMPSSE_MAX_RD_BYTES_PER_CALL_IN_SINGLE_CH    65535
#define LIBMPSSE_MAX_WR_BYTES_PER_CALL_IN_SINGLE_CH    65535

/*****************************************************************************/

/* type definitions for EVE HAL library */

typedef char		bool_t;
typedef char		char8_t;
typedef unsigned char	uchar8_t;
typedef signed char	schar8_t;
typedef float		float_t;

/* Predefined Riverdi modules */
#include "modules.h"

/* EVE inclusions */
#include "Gpu_Hal.h"
#include "Gpu.h"
#include "CoPro_Cmds.h"
#include "Hal_Utils.h"

/*****************************************************************************/

/* FT232H platform controls CS/INT lines automatically */
typedef enum {
  GPIO_CS   = 0,
  GPIO_PD   = 0xBB,
  GPIO_INT  = 0
} gpio_name;

typedef enum {
  GPIO_HIGH = 0x88,
  GPIO_LOW  = 0x08
} gpio_val;

/*****************************************************************************/

bool_t platform_init (Gpu_HalInit_t*);
void platform_sleep_ms (uint32_t);

bool_t platform_spi_init (Gpu_Hal_Context_t*);
void platform_spi_deinit (Gpu_Hal_Context_t*);

uchar8_t platform_spi_send_recv_byte (Gpu_Hal_Context_t*, uchar8_t, uint32_t);
uint16_t platform_spi_send_data (Gpu_Hal_Context_t*, uchar8_t*, uint16_t, uint32_t);
void platform_spi_recv_data (Gpu_Hal_Context_t*, uchar8_t*, uint16_t, uint32_t);

bool_t platform_gpio_init (Gpu_Hal_Context_t*, gpio_name);
bool_t platform_gpio_value (Gpu_Hal_Context_t*, gpio_name, gpio_val);

/*****************************************************************************/

#endif /*_PLATFORM_H_*/
