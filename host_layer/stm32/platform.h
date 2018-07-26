/*
 * Copyright (c) Riverdi Sp. z o.o. sp. k. <riverdi@riverdi.com>
 * Copyright (c) Skalski Embedded Technologies <contact@lukasz-skalski.com>
 */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/* C library inclusions */
#include <string.h>

/* STM32 library inclusions */
#include "stm32f0xx.h"

/*****************************************************************************/

/* type definitions for EVE HAL library */

#define TRUE		(1)
#define FALSE		(0)

typedef char		bool_t;
typedef char		char8_t;
typedef unsigned char	uchar8_t;
typedef signed char	schar8_t;
typedef float		float_t;

typedef enum {
  GPIO_CS   = GPIO_PIN_4,
  GPIO_PD   = GPIO_PIN_2,
  GPIO_INT  = GPIO_PIN_1
} gpio_name;

typedef enum {
  GPIO_HIGH = GPIO_PIN_SET,
  GPIO_LOW  = GPIO_PIN_RESET
} gpio_val;

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
