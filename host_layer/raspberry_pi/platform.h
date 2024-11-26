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
#include <bcm2835.h>

/*****************************************************************************/

/* type definitions for EVE HAL library */
#define TRUE    (1)
#define FALSE   (0)

typedef char          bool_t;
typedef char          char8_t;
typedef unsigned char uchar8_t;
typedef signed char   schar8_t;
typedef float         float_t;

/* Predefined Riverdi modules */
#include "modules.h"

/* EVE inclusions */
#include "Gpu_Hal.h"
#include "Gpu.h"
#include "CoPro_Cmds.h"
#include "Hal_Utils.h"

/*****************************************************************************/

typedef enum {
  GPIO_CS   = 26,
  GPIO_PD   = 13,
  GPIO_INT  = 19
} gpio_name;

typedef enum {
  GPIO_HIGH = HIGH,
  GPIO_LOW  = LOW
} gpio_val;

/*****************************************************************************/

bool_t
platform_init                  (Gpu_HalInit_t      *halinit);

void
platform_sleep_ms              (uint32_t            ms);

bool_t
platform_spi_init              (Gpu_Hal_Context_t  *host);

void
platform_spi_deinit            (Gpu_Hal_Context_t  *host);

uchar8_t
platform_spi_send_recv_byte    (Gpu_Hal_Context_t  *host,
                                uchar8_t            data,
                                uint32_t            opt);

uint16_t
platform_spi_send_data         (Gpu_Hal_Context_t  *host,
                                uchar8_t           *data,
                                uint16_t            size,
                                uint32_t            opt);

void
platform_spi_recv_data         (Gpu_Hal_Context_t  *host,
                                uchar8_t           *data,
                                uint16_t            size,
                                uint32_t            opt);

bool_t
platform_gpio_init             (Gpu_Hal_Context_t  *host,
                                gpio_name           ngpio);

bool_t
platform_gpio_value            (Gpu_Hal_Context_t  *host,
                                gpio_name           ngpio,
                                gpio_val            vgpio);

/*****************************************************************************/

#endif /*_PLATFORM_H_*/
