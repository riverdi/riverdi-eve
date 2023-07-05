#include "platform.h"
#include "App_Common.h"

/* global used for buffer optimization */
Gpu_Hal_Context_t host, *phost;

static void SAMAPP_GPU_Ball_Stencil();

/* main */
int main(int argc, char *argv[])
{
  phost = &host;

  /* Init HW Hal */
  App_Common_Init(&host);

  /* Screen Calibration*/
  //App_Calibrate_Screen(&host);

  /* Show Bridgetek logo */
  App_Show_Logo(&host);

  /* Main application - endless loop */
  SAMAPP_GPU_Ball_Stencil();

  /* Close all the opened handles */
  Gpu_Hal_Close(phost);
  Gpu_Hal_DeInit();

  return 0;
}

static void
SAMAPP_GPU_Ball_Stencil()
{
  uint8_t xflag, yflag;
  int16_t xball, yball, rball, pixel_precision, gridsize;
  int32_t displ, dispr, dispa, dispb;

  /* grid margins */
  displ = 10;
  dispr = (DispWidth - 10);
  dispa = 50;
  dispb = (DispHeight - 10);

  /* grid size */
  gridsize = 20;

  /* ball dimensions */
  xball = (DispWidth/2);
  yball = (DispHeight/2);
  rball = (DispWidth/8);
  xflag = 1;
  yflag = 1;

  dispr -= ((dispr - displ)%gridsize);
  dispb -= ((dispb - dispa)%gridsize);

  /* endless loop */
  while(1)
    {
      /* ball movement */
      if(((xball + rball + 2) >= dispr) || ((xball - rball - 2) <= displ))
        xflag ^= 1;

      if(((yball + rball + 8) >= dispb) || ((yball - rball - 8) <= dispa))
        yflag ^= 1;

      if(xflag)
        xball += 2;
      else
        xball -= 2;

      if(yflag)
        yball += 8;
      else
        yball -= 8;

      /* set the precision of VERTEX2F coordinates */
#if defined (IPS_70) || (IPS_101)
      /* VERTEX2F range: -2048 to 2047 */
      App_WrDl_Buffer(phost, VERTEX_FORMAT(3));
      pixel_precision = 8;
#else
      /* use default VERTEX_FORMAT(3) with VERTEX2F range: -1024 to 1023 */
      pixel_precision = 16;
#endif

      /* init and set background */
      App_WrDl_Buffer(phost, CLEAR_COLOR_RGB(255, 255, 255));
      App_WrDl_Buffer(phost, CLEAR(1, 1, 1));
      App_WrDl_Buffer(phost, STENCIL_OP(INCR,INCR));
      App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 0));

      /* draw grid */
      App_WrDl_Buffer(phost, LINE_WIDTH(pixel_precision));
      App_WrDl_Buffer(phost, BEGIN(LINES));

      for(uint16_t i=0; i<=((dispr - displ)/gridsize); i++)
        {
          App_WrDl_Buffer(phost, VERTEX2F((displ + i*gridsize)*pixel_precision,dispa*pixel_precision));
          App_WrDl_Buffer(phost, VERTEX2F((displ + i*gridsize)*pixel_precision,dispb*pixel_precision));
        }

      for(uint16_t i=0; i<=((dispb - dispa)/gridsize); i++)
        {
          App_WrDl_Buffer(phost, VERTEX2F(displ*pixel_precision,(dispa + i*gridsize)*pixel_precision));
          App_WrDl_Buffer(phost, VERTEX2F(dispr*pixel_precision,(dispa + i*gridsize)*pixel_precision));
        }
      App_WrDl_Buffer(phost, END());

      /* add simple text using built-in fonts */
      {
        Gpu_Fonts_t   font;
        uint8_t       font_size;
        uint32_t      font_table;
        uint32_t      text_hoffset, text_voffset;

#if defined (NTP_35) || (RTP_35) || (CTP_35) || (IPS_35) || (NTP_43) || (RTP_43) || (CTP_43) || (IPS_43)
        const uint8_t text[] = "Riverdi EVE Demo";
#elif defined (NTP_50) || (RTP_50) || (CTP_50) || (IPS_50) || (NTP_70) || (RTP_70) || (CTP_70) || (IPS_70)
        const uint8_t text[] = "Riverdi EVE Demo - https://www.riverdi.com";
#elif defined (IPS_101)
        const uint8_t text[] = "Riverdi EVE Demo - https://www.riverdi.com - contact@riverdi.com";
#endif

        text_hoffset = displ; /* set the same offset like for grid */
        text_voffset = 5;

        font_size = 30;
        font_table = Gpu_Hal_Rd32(phost, ROMFONT_TABLEADDRESS);

        Gpu_Hal_RdMem(phost, (font_table + (font_size-16) * GPU_FONT_TABLE_SIZE),
                      (uint8_t*)&font, GPU_FONT_TABLE_SIZE);

        App_WrDl_Buffer(phost, COLOR_RGB(0, 96, 169));
        App_WrDl_Buffer(phost, BEGIN(BITMAPS));
        App_WrDl_Buffer(phost, BITMAP_HANDLE((font_size%32)));

        for (uint8_t cnt = 0; cnt < sizeof(text)-1; cnt++)
          {
            App_WrDl_Buffer(phost, CELL(text[cnt]));
            App_WrDl_Buffer(phost, VERTEX2F(text_hoffset*pixel_precision, text_voffset*pixel_precision));
            text_hoffset += font.FontWidth[text[cnt]];
          }
        App_WrDl_Buffer(phost, END());
      }

      /* draw ball and shadow */
      App_WrDl_Buffer(phost, COLOR_MASK(1,1,1,1));
      App_WrDl_Buffer(phost, STENCIL_FUNC(ALWAYS,1,255));
      App_WrDl_Buffer(phost, STENCIL_OP(KEEP,KEEP));
      App_WrDl_Buffer(phost, COLOR_RGB(255, 255, 255));
      App_WrDl_Buffer(phost, POINT_SIZE(rball*16));
      App_WrDl_Buffer(phost, BEGIN(FTPOINTS));
      App_WrDl_Buffer(phost, VERTEX2F((xball - 1)*pixel_precision,(yball - 1)*pixel_precision));
      App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 0));
      App_WrDl_Buffer(phost, COLOR_A(160));
      App_WrDl_Buffer(phost, VERTEX2F((xball+pixel_precision)*pixel_precision,(yball+8)*pixel_precision));
      App_WrDl_Buffer(phost, COLOR_A(255));
      App_WrDl_Buffer(phost, COLOR_RGB(254, 172, 0));
      App_WrDl_Buffer(phost, VERTEX2F(xball*pixel_precision,yball*pixel_precision));
      App_WrDl_Buffer(phost, COLOR_RGB(255, 255, 255));
      App_WrDl_Buffer(phost, STENCIL_FUNC(GEQUAL,1,1));
      App_WrDl_Buffer(phost, STENCIL_OP(KEEP,KEEP));
      App_WrDl_Buffer(phost, VERTEX2F(xball*pixel_precision,yball*pixel_precision));
      App_WrDl_Buffer(phost, END());

      /* display */
      App_WrDl_Buffer(phost, DISPLAY());

      /* download display list into DL RAM */
      App_Flush_DL_Buffer(phost);

      /* do a swap */
      Gpu_Hal_DLSwap(phost, DLSWAP_FRAME);

    } /* while */
}

