/*
 * Copyright (c) Riverdi Sp. z o.o. sp. k. <riverdi@riverdi.com>
 * Copyright (c) Skalski Embedded Technologies <contact@lukasz-skalski.com>
 */

#include "platform.h"

static void
pabort (const char *msg)
{
  perror (msg);
  abort();
}


/*
 * platform_init()
 */
bool_t
platform_init (Gpu_HalInit_t *halinit)
{
  /* init lib */
  if (bcm2835_init() != 1)
    return FALSE;

  return TRUE;
}


/*
 * platform_sleep_ms()
 */
void
platform_sleep_ms (uint32_t ms)
{
  bcm2835_delay(ms);
}


/*
 * platform_spi_init()
 */
bool_t
platform_spi_init (Gpu_Hal_Context_t *host)
{
  /* init spi module */
  if (bcm2835_spi_begin() != 1)
    return FALSE;

  /* set spi bit order */
  bcm2835_spi_setBitOrder (BCM2835_SPI_BIT_ORDER_MSBFIRST);

  /* set spi to mode 0 - CPOL = 0, CPHA = 0 */
  bcm2835_spi_setDataMode (BCM2835_SPI_MODE0);

  /* sets the SPI clock divider */
  //bcm2835_spi_setClockDivider (BCM2835_SPI_CLOCK_DIVIDER_16); /* for RPi 3 */
  bcm2835_spi_setClockDivider (BCM2835_SPI_CLOCK_DIVIDER_32);   /* for RPi 4 */

  return TRUE;
}


/*
 * platform_spi_deinit()
 */
void
platform_spi_deinit (Gpu_Hal_Context_t *host)
{
  bcm2835_spi_end();
  bcm2835_close();
}


/*
 * platform_spi_send_recv_byte();
 */
uchar8_t
platform_spi_send_recv_byte (Gpu_Hal_Context_t  *host,
                             uchar8_t            data,
                             uint32_t            opt)
{
  int ret;
  uint8_t recv;

  bcm2835_spi_transfernb ((char*)&data, (char*)&recv, 1);

  return recv;
}


/*
 * platform_spi_send_data()
 */
uint16_t
platform_spi_send_data (Gpu_Hal_Context_t  *host,
                        uchar8_t           *data,
                        uint16_t            size,
                        uint32_t            opt)
{
   bcm2835_spi_transfern ((char*)data, size);
   return size;
}


/*
 * platform_spi_recv_data()
 */
void
platform_spi_recv_data (Gpu_Hal_Context_t  *host,
                        uchar8_t           *data,
                        uint16_t            size,
                        uint32_t            opt)
{
  char *dummy;

  dummy = calloc (size, 1);
  bcm2835_spi_transfernb ((char*)dummy, (char*)data, size);
  free (dummy);
}


/*
 * platform_gpio_init()
 */
bool_t
platform_gpio_init (Gpu_Hal_Context_t *host,
                    gpio_name          ngpio)
{
  bcm2835_gpio_fsel (ngpio, BCM2835_GPIO_FSEL_OUTP);
  return TRUE;
}


/*
 * platform_gpio_value()
 */
bool_t
platform_gpio_value (Gpu_Hal_Context_t  *host,
                     gpio_name           ngpio,
                     gpio_val            vgpio)
{
  bcm2835_gpio_write (ngpio, vgpio);
  return TRUE;
}
