/*
 * Copyright (c) Riverdi Sp. z o.o. sp. k. <riverdi@riverdi.com>
 * Copyright (c) Skalski Embedded Technologies <contact@lukasz-skalski.com>
 */

#include "platform.h"

int fd;

/*
 * platform_init()
 */
bool_t
platform_init (Gpu_HalInit_t *halinit)
{
  /* initialize the libmpsse */
  Init_libMPSSE();

  SPI_GetNumChannels((uint32*)&halinit->TotalChannelNum);

  /* assuming only one mpsse cable is connected to PC */
  if (halinit->TotalChannelNum > 0)
    {
      FT_DEVICE_LIST_INFO_NODE devList;

      SPI_GetChannelInfo(0, &devList);
      printf(" Information on channel number %d:\n", 0);
      printf(" Flags=0x%x\n", devList.Flags);
      printf(" Type=0x%x\n", devList.Type);
      printf(" ID=0x%x\n", devList.ID);
      printf(" LocId=0x%x\n", devList.LocId);
      printf(" SerialNumber=%s\n", devList.SerialNumber);
      printf(" Description=%s\n", devList.Description);
      printf(" ftHandle=0x%x\n", devList.ftHandle);
    }

    return TRUE;
}


/*
 * platform_sleep_ms()
 */
void
platform_sleep_ms (uint32_t ms)
{
  Sleep(ms);
}


/*
 * platform_spi_init()
 */
bool_t
platform_spi_init (Gpu_Hal_Context_t *host)
{
  ChannelConfig channelConf;
  FT_STATUS status;

  /* configure the spi settings */
  channelConf.ClockRate = 30000 * 1000; /* SPI clock = 30MHZ */
  channelConf.LatencyTimer= 2;
  channelConf.configOptions = SPI_CONFIG_OPTION_MODE0 | SPI_CONFIG_OPTION_CS_DBUS3 | SPI_CONFIG_OPTION_CS_ACTIVELOW;
  channelConf.Pin = 0x00000000;

  /* open the first available channel */
  SPI_OpenChannel(0, (FT_HANDLE *)&host->hal_handle); /* channel 0 */
  status = SPI_InitChannel((FT_HANDLE)host->hal_handle,&channelConf);

  printf(" handle=0x%x status=0x%x\n",host->hal_handle,status);
  host->spichannel = 0;

  return TRUE;
}


/*
 * platform_spi_deinit()
 */
void
platform_spi_deinit (Gpu_Hal_Context_t *host)
{
  SPI_CloseChannel(host->hal_handle);
  Cleanup_libMPSSE();
}


/*
 * platform_spi_send_recv_byte();
 */
uchar8_t
platform_spi_send_recv_byte (Gpu_Hal_Context_t  *host,
                             uchar8_t            data,
                             uint32_t            opt)
{
  uint32_t size_transfered;

  if (opt == GPU_HAL_WRITING)
    {
      SPI_Write ((FT_HANDLE)host->hal_handle, &data, sizeof(data),
                 (uint32*)&size_transfered, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES);
    }
  else
    {
      SPI_Read ((FT_HANDLE) host->hal_handle, &data, sizeof(data),
                (uint32*)&size_transfered, SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES);
    }

  return data;
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
  FT_STATUS status;
  uint32_t size_transfered;
  uint32_t size_total;
  uint16_t per_write;

  size_total = 0;

  while (size)
    {
      if (size <= LIBMPSSE_MAX_WR_BYTES_PER_CALL_IN_SINGLE_CH)
        per_write = size;
      else
        per_write = LIBMPSSE_MAX_WR_BYTES_PER_CALL_IN_SINGLE_CH;

      status = SPI_Write ((FT_HANDLE)host->hal_handle, data, per_write,
                          (uint32*)&size_transfered,
                          SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES | opt);

      if ((FT_OK != status) || (size_transfered != per_write))
        {
          printf ("[error] spi write failed with status %d\n", status);
          exit (EXIT_FAILURE);
        }

      size_total += size_transfered;
      data += size_transfered;
      size -= size_transfered;
    }

  return size_total;
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
  FT_STATUS status;
  uint32_t size_transfered;
  uint16_t per_read;

  while (size)
    {
      if (size <= LIBMPSSE_MAX_RD_BYTES_PER_CALL_IN_SINGLE_CH)
        per_read = size;
      else
        per_read = LIBMPSSE_MAX_RD_BYTES_PER_CALL_IN_SINGLE_CH;

      status = SPI_Read ((FT_HANDLE)host->hal_handle, data, per_read,
                          (uint32*)&size_transfered,
                          SPI_TRANSFER_OPTIONS_SIZE_IN_BYTES | opt);

      if ((FT_OK != status) || (size_transfered != per_read))
        {
          printf ("[error] spi read failed with status %d\n", status);
          exit (EXIT_FAILURE);
        }

      data += size_transfered;
      size -= size_transfered;
    }

  return;
}


/*
 * platform_gpio_init()
 */
bool_t
platform_gpio_init (Gpu_Hal_Context_t *host,
                    gpio_name          ngpio)
{
  /* intentionally empty */
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
  if (ngpio == GPIO_PD)
    FT_WriteGPIO (host->hal_handle, ngpio, vgpio);

  return TRUE;
}
