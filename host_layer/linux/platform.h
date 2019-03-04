/*
 * Copyright (c) Riverdi Sp. z o.o. sp. k. <riverdi@riverdi.com>
 * Copyright (c) Skalski Embedded Technologies <contact@lukasz-skalski.com>
 */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/* C library inclusions */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

/*****************************************************************************/

/* type definitions for EVE HAL library */

#define TRUE		(1)
#define FALSE		(0)

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

#define SPI_DEVICE	"/dev/spidev0.0"
#define SPI_MODE	0
#define SPI_BITS	8
#define SPI_SPEED_HZ	30000000

typedef enum {
  GPIO_CS   = 13,
  GPIO_PD   = 19,
  GPIO_INT  = 26
} gpio_name;

typedef enum {
  GPIO_HIGH = 1,
  GPIO_LOW  = 0
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
