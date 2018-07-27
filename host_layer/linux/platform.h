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
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

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

/* type definitions for EVE HAL library */

#define TRUE		(1)
#define FALSE		(0)

typedef char		bool_t;
typedef char		char8_t;
typedef unsigned char	uchar8_t;
typedef signed char	schar8_t;
typedef float		float_t;

/*****************************************************************************/

bool_t platform_init (void);
void platform_sleep_ms (uint32_t);

bool_t platform_spi_init (void);
void platform_spi_deinit (void);

uchar8_t platform_spi_send_recv_byte (uchar8_t);
uint16_t platform_spi_send_data (uchar8_t *data, uint16_t size);
void platform_spi_recv_data (uchar8_t *data, uint16_t size);

bool_t platform_gpio_init (gpio_name);
bool_t platform_gpio_value (gpio_name, gpio_val );

/*****************************************************************************/

/* Predefined Riverdi modules */
#include "modules.h"

/* EVE inclusions */
#include "Gpu_Hal.h"
#include "Gpu.h"
#include "CoPro_Cmds.h"
#include "Hal_Utils.h"

#endif /*_PLATFORM_H_*/
