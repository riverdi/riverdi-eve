#include "platform.h"
#include "App_Common.h"

/* Global used for buffer optimization */
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

static float
lerp (float t, float a, float b)
{
  return (float)((1 - t) * a + t * b);
}

static float
smoothlerp (float t, float a, float b)
{
  float lt = 3 * t * t - 2 * t * t * t;
  return lerp(lt, a, b);
}

static void
SAMAPP_GPU_Ball_Stencil()
{
  int16_t xball = (DispWidth/2),yball = (DispHeight/2),rball = (DispWidth/8);
  int16_t pixel_precision, numpoints = 6,numlines = 8,i,asize,aradius,gridsize = 20;
  int32_t asmooth,dispr = (DispWidth - 10),displ = 10,dispa = 10,dispb = (DispHeight - 10),xflag = 1,yflag = 1;

  dispr -= ((dispr - displ)%gridsize);
  dispb -= ((dispb - dispa)%gridsize);

  /* endless loop */
  while(1)
    {
      if(((xball + rball + 2) >= dispr) || ((xball - rball - 2) <= displ))
        {
          xflag ^= 1;
          Gpu_Hal_Wr8(phost, REG_PLAY,1);
        }

      if(((yball + rball + 8) >= dispb) || ((yball - rball - 8) <= dispa))
        {
          yflag ^= 1;
          Gpu_Hal_Wr8(phost, REG_PLAY,1);
        }

      if(xflag)
        xball += 2;
      else
        xball -= 2;

      if(yflag)
        yball += 8 ;
      else
        yball -= 8;

      App_WrDl_Buffer(phost, CLEAR_COLOR_RGB(128, 128, 0) );
      App_WrDl_Buffer(phost, CLEAR(1, 1, 1));
      App_WrDl_Buffer(phost, STENCIL_OP(INCR,INCR) );
      App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 0) );

      /* set the precision of VERTEX2F coordinates */
#if defined (IPS_70) || (IPS_101)
      /* VERTEX2F range: -2048 to 2047 */
      App_WrDl_Buffer(phost, VERTEX_FORMAT(3));
      pixel_precision = 8;
#else
      /* use default VERTEX_FORMAT(3) with VERTEX2F range: -1024 to 1023 */
      pixel_precision = 16;
#endif

      /* draw grid */
      App_WrDl_Buffer(phost, LINE_WIDTH(pixel_precision));
      App_WrDl_Buffer(phost, BEGIN(LINES));

      for(i=0;i<=((dispr - displ)/gridsize);i++)
        {
          App_WrDl_Buffer(phost, VERTEX2F((displ + i*gridsize)*pixel_precision,dispa*pixel_precision));
          App_WrDl_Buffer(phost, VERTEX2F((displ + i*gridsize)*pixel_precision,dispb*pixel_precision));
        }

      for(i=0;i<=((dispb - dispa)/gridsize);i++)
        {
          App_WrDl_Buffer(phost, VERTEX2F(displ*pixel_precision,(dispa + i*gridsize)*pixel_precision));
          App_WrDl_Buffer(phost, VERTEX2F(dispr*pixel_precision,(dispa + i*gridsize)*pixel_precision));
        }

      App_WrDl_Buffer(phost, END());
      App_WrDl_Buffer(phost, COLOR_MASK(0,0,0,0) );
      App_WrDl_Buffer(phost, POINT_SIZE(rball*16));
      App_WrDl_Buffer(phost, BEGIN(FTPOINTS));
      App_WrDl_Buffer(phost, VERTEX2F(xball*pixel_precision,yball*pixel_precision));
      App_WrDl_Buffer(phost, STENCIL_OP(INCR,ZERO) );
      App_WrDl_Buffer(phost, STENCIL_FUNC(GEQUAL,1,255));

      for(i=1;i<=numpoints;i++)
        {
          asize = i*rball*2/(numpoints + 1);
          asmooth = (int16_t)smoothlerp((float)((float)(asize)/(2*(float)rball)),0,2*(float)rball);

          if(asmooth > rball)
            {
              int32_t tempsmooth;

              tempsmooth = asmooth - rball;
              aradius = (rball*rball + tempsmooth*tempsmooth)/(2*tempsmooth);
              App_WrDl_Buffer(phost, POINT_SIZE(aradius*16));
              App_WrDl_Buffer(phost, VERTEX2F((xball - aradius + tempsmooth)*pixel_precision,yball*pixel_precision));
            }
          else
            {
              int32_t tempsmooth;

              tempsmooth = rball - asmooth;
              aradius = (rball*rball + tempsmooth*tempsmooth)/(2*tempsmooth);
              App_WrDl_Buffer(phost, POINT_SIZE(aradius*16));
              App_WrDl_Buffer(phost, VERTEX2F((xball+ aradius - tempsmooth)*pixel_precision,yball*pixel_precision));
            }
          }

        App_WrDl_Buffer(phost, END());
        App_WrDl_Buffer(phost, BEGIN(LINES));

        /* draw lines - line should be at least radius diameter */
        for(i=1;i<=numlines;i++)
          {
            asize = (i*rball*2/numlines);
            asmooth = (int16_t)smoothlerp((float)((float)(asize)/(2*(float)rball)),0,2*(float)rball);
            App_WrDl_Buffer(phost, LINE_WIDTH(asmooth * 16));
            App_WrDl_Buffer(phost, VERTEX2F((xball - rball)*pixel_precision,(yball - rball)*pixel_precision));
            App_WrDl_Buffer(phost, VERTEX2F((xball + rball)*pixel_precision,(yball - rball)*pixel_precision));
          }
        App_WrDl_Buffer(phost, END());

        App_WrDl_Buffer(phost, COLOR_MASK(1,1,1,1) );//enable all the colors
        App_WrDl_Buffer(phost, STENCIL_FUNC(ALWAYS,1,255));
        App_WrDl_Buffer(phost, STENCIL_OP(KEEP,KEEP));
        App_WrDl_Buffer(phost, COLOR_RGB(255, 255, 255));
        App_WrDl_Buffer(phost, POINT_SIZE(rball*16));
        App_WrDl_Buffer(phost, BEGIN(FTPOINTS));
        App_WrDl_Buffer(phost, VERTEX2F((xball - 1)*pixel_precision,(yball - 1)*pixel_precision));
        App_WrDl_Buffer(phost, COLOR_RGB(0, 0, 0));//shadow
        App_WrDl_Buffer(phost, COLOR_A(160));
        App_WrDl_Buffer(phost, VERTEX2F((xball+pixel_precision)*pixel_precision,(yball+8)*pixel_precision));
        App_WrDl_Buffer(phost, COLOR_A(255));
        App_WrDl_Buffer(phost, COLOR_RGB(255, 255, 255) );
        App_WrDl_Buffer(phost, VERTEX2F(xball*pixel_precision,yball*pixel_precision));
        App_WrDl_Buffer(phost, COLOR_RGB(255, 0, 0) );
        App_WrDl_Buffer(phost, STENCIL_FUNC(GEQUAL,1,1));
        App_WrDl_Buffer(phost, STENCIL_OP(KEEP,KEEP));
        App_WrDl_Buffer(phost, VERTEX2F(xball*pixel_precision,yball*pixel_precision));

        App_WrDl_Buffer(phost, END());
        App_WrDl_Buffer(phost,DISPLAY());

        /* Download the DL into DL RAM */
        App_Flush_DL_Buffer(phost);

        /* Do a swap */
        Gpu_Hal_DLSwap(phost,DLSWAP_FRAME);
      } /* while */
}

