/*
 * Copyright (c) Riverdi Sp. z o.o. sp. k. <riverdi@riverdi.com>
 * Copyright (c) Skalski Embedded Technologies <contact@lukasz-skalski.com>
 */

#include "platform.h"

int fd;

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
  /* intentionally empty */
  return TRUE;
}


/*
 * platform_sleep_ms()
 */
void
platform_sleep_ms (uint32_t ms)
{
  usleep (ms*1000);
}


/*
 * platform_spi_init()
 */
bool_t
platform_spi_init (Gpu_Hal_Context_t *host)
{
  int ret;
  uint8_t mode;
  uint8_t bits;
  uint32_t speed;

  mode = SPI_MODE;
  bits = SPI_BITS;
  speed = SPI_SPEED_HZ;

  /* open spi device */

  fd = open(SPI_DEVICE, O_RDWR);
  if (fd < 0)
    pabort ("can't open spi device");

  /* set and check spi mode */

  ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
  if (ret == -1)
    pabort ("can't set spi mode");

  ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
  if (ret == -1)
    pabort ("can't get spi mode");

  /* bits per word */

  ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
  if (ret == -1)
    pabort ("can't set spi speed");


  ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
  if (ret == -1)
    pabort ("can't get spi speed");

  /* max speed hz */

  ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
  if (ret == -1)
    abort();

  ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
  if (ret == -1)
    abort();

  return TRUE;
}


/*
 * platform_spi_deinit()
 */
void
platform_spi_deinit (Gpu_Hal_Context_t *host)
{
  close (fd);
  fd = -1;
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

  struct spi_ioc_transfer tr = {
    .tx_buf = (unsigned long)&data,
    .rx_buf = (unsigned long)&recv,
    .len = 1,
  };

  ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  if (ret < 1)
    pabort ("can't send spi message");

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
  size = write (fd, data, size);
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
  read (fd, data, size);
}

#define GPIO_DIR        "/sys/class/gpio"
#define GPIO_IN         0
#define GPIO_OUT        1
#define BUF_SIZE        64

static int
gpio_export (unsigned int gpio)
{
  int fd, len;
  char buf[BUF_SIZE];

  fd = open (GPIO_DIR "/export", O_WRONLY);
  if (fd < 0)
    pabort ("gpio/export");

  len = snprintf (buf, sizeof(buf), "%d", gpio);
  write (fd, buf, len);
  close (fd);

  return 0;
}

static int
gpio_set_direction (unsigned int gpio,
                    unsigned int direction)
{
  int fd;
  char buf[BUF_SIZE];

  snprintf (buf, sizeof(buf), GPIO_DIR "/gpio%d/direction", gpio);

  fd = open (buf, O_WRONLY);
  if (fd < 0)
    pabort ("gpio/direction");

  if (direction)
    write (fd, "out", sizeof("out"));
  else
    write (fd, "in", sizeof("in"));

  close (fd);
  return 0;
}


static int
gpio_set_value (unsigned int gpio,
                unsigned int value)
{
  int fd;
  char buf[BUF_SIZE];

  snprintf (buf, sizeof(buf), GPIO_DIR "/gpio%d/value", gpio);

  fd = open (buf, O_WRONLY);
  if (fd < 0)
    pabort ("gpio/set-value");

  if (value)
    write (fd, "1", 2);
  else
    write (fd, "0", 2);

  close (fd);
  return 0;
}


/*
 * platform_gpio_init()
 */
bool_t
platform_gpio_init (Gpu_Hal_Context_t *host,
                    gpio_name          ngpio)
{
 if (gpio_export (ngpio) < 0)
   return FALSE;

  if (gpio_set_direction (ngpio, GPIO_OUT) < 0)
   return FALSE;

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
  return gpio_set_value (ngpio, vgpio);
}
