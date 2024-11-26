/*
 * Copyright (c) Bridgetek Pte Ltd
 * Copyright (c) Riverdi Sp. z o.o. sp. k. <riverdi@riverdi.com>
 * Copyright (c) Skalski Embedded Technologies <contact@lukasz-skalski.com>
 *
 * THIS SOFTWARE IS PROVIDED BY BRIDGETEK PTE LTD "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BRIDGETEK PTE LTD BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES
 * LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * BRIDGETEK DRIVERS MAY BE USED ONLY IN CONJUNCTION WITH PRODUCTS BASED ON
 * BRIDGETEK PARTS.
 *
 * BRIDGETEK DRIVERS MAY BE DISTRIBUTED IN ANY FORM AS LONG AS LICENSE
 * INFORMATION IS NOT MODIFIED.
 *
 * IF A CUSTOM VENDOR ID AND/OR PRODUCT ID OR DESCRIPTION STRING ARE USED,
 * IT IS THE RESPONSIBILITY OF THE PRODUCT MANUFACTURER TO MAINTAIN ANY CHANGES
 * AND SUBSEQUENT WHQL RE-CERTIFICATION AS A RESULT OF MAKING THESE CHANGES.
 */

#include "platform.h"
#include "App_Common.h"

#ifdef BT81X_ENABLE
static uint8_t COUNT_ARGS(const char* str)
{
  uint8_t count = 0;
  const char *tmp = str;

  while ((tmp = strstr(tmp, "%")))
    {
      if (*(tmp + 1) == '%')
        {
          tmp += 2;
        }
      else
        {
          count++;
          tmp++;
        }
    }
  return count;
}
#endif

void Gpu_CoCmd_Text(Gpu_Hal_Context_t *phost, int16_t x, int16_t y, int16_t font, uint16_t options, const char8_t* s, ...)
{
  va_list args;
  uint8_t i, num=0;
  uint8_t len = strlen(s);

  va_start(args, s);

#ifdef BT81X_ENABLE
  num = (options & OPT_FORMAT) ? (COUNT_ARGS(s)) : (0);
#endif

  Gpu_CoCmd_StartFunc(phost, CMD_SIZE * (3+ num) + ((len + 1 + 3) & ~3));
  Gpu_Copro_SendCmd(phost, CMD_TEXT);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y << 16) | (x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options << 16) | (font & 0xffff)));
  Gpu_CoCmd_SendStr(phost, s);

  for (i = 0; i < num; i++)
    Gpu_Copro_SendCmd(phost, (uint32_t)va_arg(args, uint32_t));

  Gpu_CoCmd_EndFunc(phost, CMD_SIZE * (3+ num) + ((len + 1 + 3) & ~3));
  va_end(args);
}

void Gpu_CoCmd_Number(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t font, uint16_t options, int32_t n)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_NUMBER);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options<<16)|(font&0xffff)));
  Gpu_Copro_SendCmd(phost, n);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_LoadIdentity(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_LOADIDENTITY);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_Toggle(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t font, uint16_t options, uint16_t state, const char8_t* s, ...)
{
  va_list args;
  uint8_t i, num = 0;

  va_start(args, s);

#ifdef BT81X_ENABLE
  num = (options & OPT_FORMAT) ? (COUNT_ARGS(s)) : (0);
#endif

  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*(4 + num) + strlen(s) + 1);
  Gpu_Copro_SendCmd(phost, CMD_TOGGLE);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)font<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)state<<16)|options));
  Gpu_CoCmd_SendStr(phost, s);

  for (i = 0; i < num; i++)
    Gpu_Copro_SendCmd(phost, (uint32_t)va_arg(args, uint32_t));

  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*(4 + num) + strlen(s) + 1));
  va_end(args);
}

void Gpu_CoCmd_Gauge(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_GAUGE);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options<<16)|(r&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)minor<<16)|(major&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)range<<16)|(val&0xffff)));
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_RegRead(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t result)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_REGREAD);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, 0);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_GetProps(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t w, uint32_t h)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_GETPROPS);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, w);
  Gpu_Copro_SendCmd(phost, h);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_Memcpy(Gpu_Hal_Context_t *phost,uint32_t dest, uint32_t src, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_MEMCPY);
  Gpu_Copro_SendCmd(phost, dest);
  Gpu_Copro_SendCmd(phost, src);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_Spinner(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, uint16_t style, uint16_t scale)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_SPINNER);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)scale<<16)|(style&0xffff)));
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_BgColor(Gpu_Hal_Context_t *phost,uint32_t c)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_BGCOLOR);
  Gpu_Copro_SendCmd(phost, c);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Swap(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_SWAP);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_Inflate(Gpu_Hal_Context_t *phost,uint32_t ptr)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_INFLATE);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Translate(Gpu_Hal_Context_t *phost,int32_t tx, int32_t ty)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_TRANSLATE);
  Gpu_Copro_SendCmd(phost, tx);
  Gpu_Copro_SendCmd(phost, ty);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_Stop(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_STOP);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_Slider(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t range)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_SLIDER);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)val<<16)|(options&0xffff)));
  Gpu_Copro_SendCmd(phost, range);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_TouchTransform(Gpu_Hal_Context_t *phost,int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t tx0, int32_t ty0, int32_t tx1, int32_t ty1, int32_t tx2, int32_t ty2, uint16_t result)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*6*2+CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_TOUCH_TRANSFORM);
  Gpu_Copro_SendCmd(phost, x0);
  Gpu_Copro_SendCmd(phost, y0);
  Gpu_Copro_SendCmd(phost, x1);
  Gpu_Copro_SendCmd(phost, y1);
  Gpu_Copro_SendCmd(phost, x2);
  Gpu_Copro_SendCmd(phost, y2);
  Gpu_Copro_SendCmd(phost, tx0);
  Gpu_Copro_SendCmd(phost, ty0);
  Gpu_Copro_SendCmd(phost, tx1);
  Gpu_Copro_SendCmd(phost, ty1);
  Gpu_Copro_SendCmd(phost, tx2);
  Gpu_Copro_SendCmd(phost, ty2);
  Gpu_Copro_SendCmd(phost, result);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*6*2+CMD_SIZE*2));
}

void Gpu_CoCmd_Interrupt(Gpu_Hal_Context_t *phost,uint32_t ms)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_INTERRUPT);
  Gpu_Copro_SendCmd(phost, ms);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_FgColor(Gpu_Hal_Context_t *phost,uint32_t c)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_FGCOLOR);
  Gpu_Copro_SendCmd(phost, c);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Rotate(Gpu_Hal_Context_t *phost,int32_t a)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_ROTATE);
  Gpu_Copro_SendCmd(phost, a);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Button(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, int16_t font, uint16_t options, const char8_t* s, ...)
{
  va_list args;
  uint8_t i, num = 0;

  va_start(args, s);

#ifdef BT81X_ENABLE
  num = (options & OPT_FORMAT) ? (COUNT_ARGS(s)) : (0);
#endif

  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*(4 + num) + strlen(s) + 1);
  Gpu_Copro_SendCmd(phost, CMD_BUTTON);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options<<16)|(font&0xffff)));
  Gpu_CoCmd_SendStr(phost, s);

  for (i = 0; i < num; i++)
    Gpu_Copro_SendCmd(phost, (uint32_t)va_arg(args, uint32_t));

  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*(4 + num) + strlen(s) + 1));
  va_end(args);
}

void Gpu_CoCmd_MemWrite(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_MEMWRITE);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_Scrollbar(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t size, uint16_t range)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_SCROLLBAR);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)val<<16)|(options&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)range<<16)|(size&0xffff)));
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_GetMatrix(Gpu_Hal_Context_t *phost,int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*7);
  Gpu_Copro_SendCmd(phost, CMD_GETMATRIX);
  Gpu_Copro_SendCmd(phost, a);
  Gpu_Copro_SendCmd(phost, b);
  Gpu_Copro_SendCmd(phost, c);
  Gpu_Copro_SendCmd(phost, d);
  Gpu_Copro_SendCmd(phost, e);
  Gpu_Copro_SendCmd(phost, f);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*7));
}

void Gpu_CoCmd_Sketch(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t ptr, uint16_t format)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_SKETCH);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, format);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_MemSet(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t value, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_MEMSET);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, value);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_GradColor(Gpu_Hal_Context_t *phost,uint32_t c)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_GRADCOLOR);
  Gpu_Copro_SendCmd(phost, c);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_BitmapTransform(Gpu_Hal_Context_t *phost,int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t tx0, int32_t ty0, int32_t tx1, int32_t ty1, int32_t tx2, int32_t ty2, uint16_t result)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*6*2+CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_BITMAP_TRANSFORM);
  Gpu_Copro_SendCmd(phost, x0);
  Gpu_Copro_SendCmd(phost, y0);
  Gpu_Copro_SendCmd(phost, x1);
  Gpu_Copro_SendCmd(phost, y1);
  Gpu_Copro_SendCmd(phost, x2);
  Gpu_Copro_SendCmd(phost, y2);
  Gpu_Copro_SendCmd(phost, tx0);
  Gpu_Copro_SendCmd(phost, ty0);
  Gpu_Copro_SendCmd(phost, tx1);
  Gpu_Copro_SendCmd(phost, ty1);
  Gpu_Copro_SendCmd(phost, tx2);
  Gpu_Copro_SendCmd(phost, ty2);
  Gpu_Copro_SendCmd(phost, result);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*6*2+CMD_SIZE*2));
}

void Gpu_CoCmd_Calibrate(Gpu_Hal_Context_t *phost,uint32_t result)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_CALIBRATE);
  Gpu_Copro_SendCmd(phost, result);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
  Gpu_Hal_WaitCmdfifo_empty(phost);
}

void Gpu_CoCmd_SetFont(Gpu_Hal_Context_t *phost,uint32_t font, uint32_t ptr)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_SETFONT);
  Gpu_Copro_SendCmd(phost, font);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_Logo(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_LOGO);
  Gpu_CoCmd_EndFunc(phost,CMD_SIZE*1);
}

void Gpu_CoCmd_Append(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_APPEND);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_MemZero(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_MEMZERO);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_Scale(Gpu_Hal_Context_t *phost,int32_t sx, int32_t sy)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_SCALE);
  Gpu_Copro_SendCmd(phost, sx);
  Gpu_Copro_SendCmd(phost, sy);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_Clock(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t h, uint16_t m, uint16_t s, uint16_t ms)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_CLOCK);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options<<16)|(r&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)m<<16)|(h&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)ms<<16)|(s&0xffff)));
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_Gradient(Gpu_Hal_Context_t *phost,int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_GRADIENT);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y0<<16)|(x0 & 0xffff)));
  Gpu_Copro_SendCmd(phost, rgb0);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y1<<16)|(x1 & 0xffff)));
  Gpu_Copro_SendCmd(phost, rgb1);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_SetMatrix(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_SETMATRIX);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_Track(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, int16_t tag)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_TRACK);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, tag);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_GetPtr(Gpu_Hal_Context_t *phost,uint32_t result)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_GETPTR);
  Gpu_Copro_SendCmd(phost, result);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Progress(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t range)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_PROGRESS);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)val<<16)|(options&0xffff)));
  Gpu_Copro_SendCmd(phost, range);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_ColdStart(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_COLDSTART);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_Keys(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, int16_t font, uint16_t options, const char8_t* s)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4 + strlen(s) + 1);
  Gpu_Copro_SendCmd(phost, CMD_KEYS);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options<<16)|(font&0xffff)));
  Gpu_CoCmd_SendStr(phost, s);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4 + strlen(s) + 1));
}

void Gpu_CoCmd_Dial(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t val)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_DIAL);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options<<16)|(r&0xffff)));
  Gpu_Copro_SendCmd(phost, val);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_LoadImage(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t options)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_LOADIMAGE);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, options);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_Dlstart(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_DLSTART);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_Snapshot(Gpu_Hal_Context_t *phost,uint32_t ptr)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_SNAPSHOT);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_ScreenSaver(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_SCREENSAVER);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_MemCrc(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t num, uint32_t result)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_MEMCRC);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_Copro_SendCmd(phost, result);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

uint32_t GET_ASTC_FORMAT(uint16_t w, uint16_t h)
{
#ifdef BT81X_ENABLE
  if ((w == 4) && (h == 4))  return COMPRESSED_RGBA_ASTC_4x4_KHR;
  else if ((w == 5) && (h == 4))  return COMPRESSED_RGBA_ASTC_5x4_KHR;
  else if ((w == 5) && (h == 5))  return COMPRESSED_RGBA_ASTC_5x5_KHR;
  else if ((w == 6) && (h == 5))  return COMPRESSED_RGBA_ASTC_6x5_KHR;
  else if ((w == 6) && (h == 6))  return COMPRESSED_RGBA_ASTC_6x6_KHR;
  else if ((w == 8) && (h == 5))  return COMPRESSED_RGBA_ASTC_8x5_KHR;
  else if ((w == 8) && (h == 6))  return COMPRESSED_RGBA_ASTC_8x6_KHR;
  else if ((w == 8) && (h == 8))  return COMPRESSED_RGBA_ASTC_8x8_KHR;
  else if ((w == 10) && (h == 5))  return COMPRESSED_RGBA_ASTC_10x5_KHR;
  else if ((w == 10) && (h == 6))  return COMPRESSED_RGBA_ASTC_10x6_KHR;
  else if ((w == 10) && (h == 8))  return COMPRESSED_RGBA_ASTC_10x8_KHR;
  else if ((w == 10) && (h == 10))  return COMPRESSED_RGBA_ASTC_10x10_KHR;
  else if ((w == 12) && (h == 10))  return COMPRESSED_RGBA_ASTC_12x10_KHR;
  else if ((w == 12) && (h == 12))  return COMPRESSED_RGBA_ASTC_12x12_KHR;
  else return 0;
#else
  return 0;
#endif
}

void astc_tile2(uint8_t *iData, uint16_t bw, uint16_t bh, uint32_t size, uint8_t *oData)
{
  uint32_t i, j, next;
  uint8_t *d, *r;

  d = iData;
  r = oData;

  for (j = 0; j < bh - 1; j += 2)
    {
      for (i = 0; i < bw; i += 2)
        {
          if (i < (bw - 1))
            {
              next = 16 * (bw * j + i);
              memcpy(r, d + next, 16);
              r += 16;

              next = 16 * (bw * (j + 1) + i);
              memcpy(r, d + next, 16);
              r += 16;

              next = 16 * (bw * (j + 1) + (i + 1));
              memcpy(r, d + next, 16);
              r += 16;

              next = 16 * (bw * j + (i + 1));
              memcpy(r, d + next, 16);
              r += 16;
            }
          else
            {
              next = 16 * (bw * j + i);
              memcpy(r, d + next, 16);
              r += 16;

              next = 16 * (bw * (j + 1) + i);
              memcpy(r, d + next, 16);
              r += 16;
            }
        }
    }

  if (bh & 1)
    {
      for (i = bw * (bh - 1); i < (size)/16 ; i += 1)
        {
          next = 16 * i;
          memcpy(r, d + next, 16);
          r += 16;
        }
    }
}

#ifdef FT81X_ENABLE
void Gpu_CoCmd_SetBitmap(Gpu_Hal_Context_t *phost,uint32_t source, uint16_t fmt, uint16_t w, uint16_t h)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_SETBITMAP);
  Gpu_Copro_SendCmd(phost, source);
  Gpu_Copro_SendCmd(phost, (((uint32_t)w<<16)|(fmt & 0xffff)));
  Gpu_Copro_SendCmd(phost, h);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_SetScratch(Gpu_Hal_Context_t *phost,uint32_t handle)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_SETSCRATCH);
  Gpu_Copro_SendCmd(phost, handle);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_VideoStart(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_VIDEOSTART);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_SetBase(Gpu_Hal_Context_t *phost,uint32_t base)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_SETBASE);
  Gpu_Copro_SendCmd(phost, base);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_VideoFrame(Gpu_Hal_Context_t *phost,uint32_t dst, uint32_t ptr)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_VIDEOFRAME);
  Gpu_Copro_SendCmd(phost, dst);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_RomFont(Gpu_Hal_Context_t *phost,uint32_t font, uint32_t romslot)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_ROMFONT);
  Gpu_Copro_SendCmd(phost, font);
  Gpu_Copro_SendCmd(phost, romslot);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_PlayVideo(Gpu_Hal_Context_t *phost,uint32_t options)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_PLAYVIDEO);
  Gpu_Copro_SendCmd(phost, options);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Sync(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*1);
  Gpu_Copro_SendCmd(phost, CMD_SYNC);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*1));
}

void Gpu_CoCmd_Int_RAMShared(Gpu_Hal_Context_t *phost,uint32_t ptr)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_INT_RAMSHARED);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Int_SWLoadImage(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t options)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_INT_SWLOADIMAGE);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, options);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_MediaFifo(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t size)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_MEDIAFIFO);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, size);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_Snapshot2(Gpu_Hal_Context_t *phost,uint32_t fmt, uint32_t ptr, int16_t x, int16_t y, int16_t w, int16_t h)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_SNAPSHOT2);
  Gpu_Copro_SendCmd(phost, fmt);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_SetFont2(Gpu_Hal_Context_t *phost,uint32_t font, uint32_t ptr, uint32_t firstchar)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_SETFONT2);
  Gpu_Copro_SendCmd(phost, font);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, firstchar);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_SetRotate(Gpu_Hal_Context_t *phost,uint32_t r)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_SETROTATE);
  Gpu_Copro_SendCmd(phost, r);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Set_GpuClock(Gpu_Hal_Context_t *phost)
{
  static uint32_t x = 1;

  Gpu_CoCmd_Sync(phost);
  Gpu_CoCmd_Memcpy(phost, x * 4, REG_CLOCK, 4);
  App_Flush_Co_Buffer(phost);
  Gpu_Hal_WaitCmdfifo_empty(phost);

  x = x ^ 1;
}

uint32_t Get_GpuClock(Gpu_Hal_Context_t *phost)
{
  uint32_t a = Gpu_Hal_Rd32(phost, 0);
  uint32_t b = Gpu_Hal_Rd32(phost, 4);

  return (a < b) ? (b - a) : (a - b);
}
#endif /* FT81X_ENABLE */

#ifdef BT81X_ENABLE
void Gpu_CoCmd_VideoStartF(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE * 1);
  Gpu_Copro_SendCmd(phost, CMD_VIDEOSTARTF);
  Gpu_CoCmd_EndFunc(phost, (CMD_SIZE * 1));
}

void Gpu_CoCmd_FillWidth(Gpu_Hal_Context_t *phost, uint32_t s)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_FILLWIDTH);
  Gpu_Copro_SendCmd(phost, s);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Nop(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE);
  Gpu_Copro_SendCmd(phost, CMD_NOP);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE));
}

void Gpu_CoCmd_GetPoint(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, uint32_t sx, uint32_t sy)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_GETPOINT);
  Gpu_Copro_SendCmd(phost, ((uint32_t)y<<16) |(x & 0xFFFF));
  Gpu_Copro_SendCmd(phost, sx);
  Gpu_Copro_SendCmd(phost, sy);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_Inflate2(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t options)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_INFLATE2);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, options);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_RotateAround(Gpu_Hal_Context_t *phost,int32_t x, int32_t y, int32_t a, int32_t s)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost,CMD_ROTATEAROUND);
  Gpu_Copro_SendCmd(phost,x);
  Gpu_Copro_SendCmd(phost,y);
  Gpu_Copro_SendCmd(phost,a);
  Gpu_Copro_SendCmd(phost,s);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}

void Gpu_CoCmd_FlashErase(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE);
  Gpu_Copro_SendCmd(phost, CMD_FLASHERASE);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE));
}

/*
 * Write data to flash. Constraints:
 *   - destination flash address must be virgin (not used before)
 *   - data array must be aligned 256-bit
 */
void Gpu_CoCmd_FlashWriteExt(Gpu_Hal_Context_t *phost,uint32_t dest, uint32_t num, uint8_t *data)
{
  uint32_t i, send_data32=0, totalnum = (num+3)/4;

  Gpu_CoCmd_StartFunc(phost, CMD_SIZE*(3+totalnum));
  Gpu_Copro_SendCmd(phost,CMD_FLASHWRITE);
  Gpu_Copro_SendCmd(phost,dest);
  Gpu_Copro_SendCmd(phost, num);

  for (i = 0; i < num; i=i+4)
    {
      send_data32 = *data++;
      send_data32 |= (*data++) << 8;
      send_data32 |= (*data++) << 16;
      send_data32 |= (*data++) << 24;
      Gpu_Copro_SendCmd(phost, send_data32);
    }

  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*(3+totalnum)));
}

void Gpu_CoCmd_FlashWrite(Gpu_Hal_Context_t *phost, uint32_t ptr, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_FLASHWRITE);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

/*
 * Writes the given data to flash.
 * If the data matches the existing contents of flash, nothing is done.
 * Otherwise the flash is erased in 4K units, and the data is written.
 */
void Gpu_CoCmd_FlashUpdate(Gpu_Hal_Context_t *phost, uint32_t dest, uint32_t src, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE * 4);
  Gpu_Copro_SendCmd(phost, CMD_FLASHUPDATE);
  Gpu_Copro_SendCmd(phost, dest);
  Gpu_Copro_SendCmd(phost, src);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost, (CMD_SIZE * 4));
}

/* Read data from flash into main memory */
void Gpu_CoCmd_FlashRead(Gpu_Hal_Context_t *phost,uint32_t dest, uint32_t src, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_FLASHREAD);
  Gpu_Copro_SendCmd(phost, dest);
  Gpu_Copro_SendCmd(phost, src);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_FlashSource(Gpu_Hal_Context_t *phost,uint32_t ptr)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost,CMD_FLASHSOURCE);
  Gpu_Copro_SendCmd(phost,ptr);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_FlashSpiTx(Gpu_Hal_Context_t *phost,uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost,CMD_FLASHSPITX);
  Gpu_Copro_SendCmd(phost,num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_FlashFast(Gpu_Hal_Context_t *phost,uint32_t result)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost,CMD_FLASHFAST);
  Gpu_Copro_SendCmd(phost,result);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_FlashSpiRx(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3);
  Gpu_Copro_SendCmd(phost, CMD_FLASHSPIRX);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3));
}

void Gpu_CoCmd_FlashAttach(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE);
  Gpu_Copro_SendCmd(phost, CMD_FLASHATTACH);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE));
}

void Gpu_CoCmd_FlashDetach(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE);
  Gpu_Copro_SendCmd(phost,CMD_FLASHDETACH);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE));
}

void Gpu_CoCmd_FlashSpiDesel(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE);
  Gpu_Copro_SendCmd(phost, CMD_FLASHSPIDESEL);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE));
}

void Gpu_CoCmd_ClearCache(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE);
  Gpu_Copro_SendCmd(phost,CMD_CLEARCACHE);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE));
}

void Gpu_CoCmd_Int_RamShared(Gpu_Hal_Context_t *phost,uint32_t ptr)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_INT_RAMSHARED);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
}

void Gpu_CoCmd_Sha1(Gpu_Hal_Context_t *phost,uint32_t src, uint32_t num, uint32_t hash)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4);
  Gpu_Copro_SendCmd(phost, CMD_SHA1);
  Gpu_Copro_SendCmd(phost, src);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_Copro_SendCmd(phost, hash);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4));
}

void Gpu_CoCmd_ResetFonts(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE);
  Gpu_Copro_SendCmd(phost,CMD_RESETFONTS);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE));
}

void Gpu_CoCmd_AnimStart(Gpu_Hal_Context_t *phost, int32_t ch, uint32_t aoptr, uint32_t loop)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE * 4);
  Gpu_Copro_SendCmd(phost, CMD_ANIMSTART);
  Gpu_Copro_SendCmd(phost, ch);
  Gpu_Copro_SendCmd(phost, aoptr);
  Gpu_Copro_SendCmd(phost, loop);
  Gpu_CoCmd_EndFunc(phost, (CMD_SIZE * 4));
}

void Gpu_CoCmd_GradientA(Gpu_Hal_Context_t *phost, int16_t x0, int16_t y0, uint32_t argb0, int16_t x1, int16_t y1, uint32_t argb1)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE * 5);
  Gpu_Copro_SendCmd(phost, CMD_GRADIENTA);
  Gpu_Copro_SendCmd(phost, ((uint32_t)y0<<16) |(x0 & 0xFFFF));
  Gpu_Copro_SendCmd(phost, argb0);
  Gpu_Copro_SendCmd(phost, ((uint32_t)y1<<16) |(x1 & 0xFFFF));
  Gpu_Copro_SendCmd(phost, argb1);
  Gpu_CoCmd_EndFunc(phost, (CMD_SIZE * 5));
}

void Gpu_CoCmd_AnimStop(Gpu_Hal_Context_t *phost, int32_t ch)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE * 2);
  Gpu_Copro_SendCmd(phost, CMD_ANIMSTOP);
  Gpu_Copro_SendCmd(phost, ch);
  Gpu_CoCmd_EndFunc(phost, CMD_SIZE * 2);
}

void Gpu_CoCmd_AnimXY(Gpu_Hal_Context_t *phost, int32_t ch, int16_t x, int16_t y)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE * 3);
  Gpu_Copro_SendCmd(phost, CMD_ANIMXY);
  Gpu_Copro_SendCmd(phost, ch);
  Gpu_Copro_SendCmd(phost, ((uint32_t)y<<16) |(x & 0xFFFF));
  Gpu_CoCmd_EndFunc(phost, (CMD_SIZE * 3));
}

void Gpu_CoCmd_AnimDraw(Gpu_Hal_Context_t *phost, int32_t ch)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE *2);
  Gpu_Copro_SendCmd(phost, CMD_ANIMDRAW);
  Gpu_Copro_SendCmd(phost, ch);
  Gpu_CoCmd_EndFunc(phost, CMD_SIZE * 2);
}

void Gpu_CoCmd_AnimFrame(Gpu_Hal_Context_t *phost, int16_t x, int16_t y, uint32_t aoptr, uint32_t frame)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE * 4);
  Gpu_Copro_SendCmd(phost, CMD_ANIMFRAME);
  Gpu_Copro_SendCmd(phost, ((uint32_t)y << 16) | (x & 0xFFFF));
  Gpu_Copro_SendCmd(phost, aoptr);
  Gpu_Copro_SendCmd(phost, frame);
  Gpu_CoCmd_EndFunc(phost, CMD_SIZE * 4);
}

void Gpu_CoCmd_AppendF(Gpu_Hal_Context_t *phost, uint32_t ptr, uint32_t num)
{
  Gpu_CoCmd_StartFunc(phost, CMD_SIZE *3);
  Gpu_Copro_SendCmd(phost, CMD_APPENDF);
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, num);
  Gpu_CoCmd_EndFunc(phost, CMD_SIZE * 3);
}

void Gpu_CoCmd_FlashHelper_Init(Gpu_Hal_Context_t *phost)
{
  while (FLASH_STATUS_DETACHED == Gpu_Hal_Rd8(phost, REG_FLASH_STATUS))
    Gpu_CoCmd_FlashAttach(phost);
}

/*
 * Switch to other flash state
 * Error code:
 *  - 0x0    command succeeds
 *  - 0xffff command fails (invalid transition state)
 *  - 0xe001 flash is not attached
 *  - 0xe002 no header detected in sector 0 - is flash blank?
 *  - 0xe003 sector 0 data failed integrity check
 *  - 0xe004 device/blob mismatch - was correct blob loaded?
 *  - 0xe005 failed full-speed test - check board wiring
 */
uint32_t Gpu_CoCmd_FlashHelper_SwitchState(Gpu_Hal_Context_t *phost, uint8_t nextState)
{
  uint32_t ret = 0;
  uint8_t curr_flash_state = Gpu_Hal_Rd8(phost, REG_FLASH_STATUS);
  uint16_t ret_addr = 0;

  if (curr_flash_state != nextState)
    {
      if (FLASH_STATUS_DETACHED == nextState)
        {
          Gpu_CoCmd_FlashDetach(phost);
          App_Flush_Co_Buffer(phost);
        }
      else if (FLASH_STATUS_BASIC == nextState)
        {
          if (FLASH_STATUS_FULL == curr_flash_state)
            {
              do
                {
                  Gpu_CoCmd_FlashDetach(phost);
                  App_Flush_Co_Buffer(phost);
                } while (FLASH_STATUS_DETACHED != Gpu_Hal_Rd8(phost, REG_FLASH_STATUS));
            }

          Gpu_CoCmd_FlashAttach(phost);
          App_Flush_Co_Buffer(phost);
        }
      else if (FLASH_STATUS_FULL == nextState)
        {
          if (FLASH_STATUS_BASIC != curr_flash_state)
            {
              do
                {
                  Gpu_CoCmd_FlashAttach(phost);
                  App_Flush_Co_Buffer(phost);
                } while (FLASH_STATUS_BASIC != Gpu_Hal_Rd8(phost, REG_FLASH_STATUS));
            }

          Gpu_CoCmd_FlashFast(phost, 0);
          App_Flush_Co_Buffer(phost);

          /* read the return code in CMD_BUFFER */
          ret_addr = (phost->cmd_fifo_wp - 4) & FIFO_SIZE_MASK;
          ret_addr = (ret_addr + 3) & FIFO_BYTE_ALIGNMENT_MASK;

          ret = Gpu_Hal_Rd32(phost, RAM_CMD + ret_addr);
        }
      else
        {
          ret = 0xffff;
        }
    }
  return ret;
}

uint32_t Gpu_CoCmd_FlashHelper_SwitchFullMode(Gpu_Hal_Context_t *phost)
{
  uint8_t val;

  Gpu_CoCmd_FlashDetach(phost);
  App_Flush_Co_Buffer(phost);
  Gpu_Hal_WaitCmdfifo_empty(phost);
  val = Gpu_Hal_Rd8(phost, REG_FLASH_STATUS);

  if (FLASH_STATUS_DETACHED != val)
    {
      /* error, flash is not able to detatch */
      return 0;
    }

  Gpu_CoCmd_FlashAttach(phost);
  App_Flush_Co_Buffer(phost);
  Gpu_Hal_WaitCmdfifo_empty(phost);
  val = Gpu_Hal_Rd8(phost, REG_FLASH_STATUS);

  if (FLASH_STATUS_BASIC != val)
    {
      /* error, flash is not able to attach */
      return 0;
    }

  Gpu_CoCmd_FlashFast(phost, 0);
  App_Flush_Co_Buffer(phost);
  Gpu_Hal_WaitCmdfifo_empty(phost);
  val = Gpu_Hal_Rd8(phost, REG_FLASH_STATUS);

  if (FLASH_STATUS_FULL != val)
    {
      /* error, flash is not able to get into full mode */
      return 0;
    }

  return 1;
}

/*
 * Write data to flash, and align byte if needed.
 * Note:
 *  - Destination flash address must be virgin (not used before).
 *    Otherwise, users have to perform flash erase before using.
 *  - Destination address must be 256-byte aligned.
 *  - Automatically padding 0xFF to non-aligned num.
 */
Flash_Cmd_Status_t Gpu_CoCmd_FlashHelper_Write(Gpu_Hal_Context_t *phost, uint32_t dest_flash, uint32_t num, uint8_t *write_data)
{
  uint32_t i;
  uint8_t padding_arr[FLASH_WRITE_ALIGN_BYTE]; /* write_data must be 256-byte aligned */
  uint32_t aligned_length = num % FLASH_WRITE_ALIGN_BYTE;

  if (dest_flash % FLASH_WRITE_ALIGN_BYTE != 0)
    return FLASH_CMD_ALIGNED_ERR;

  if (aligned_length == 0) /* write_data is already aligned */
    {
      Gpu_CoCmd_FlashWriteExt(phost, dest_flash, num, write_data);
      App_Flush_Co_Buffer(phost);
      Gpu_Hal_WaitCmdfifo_empty(phost);
    }
  else
    {
      /* write first aligned chunks of write_data */
      if (num - aligned_length > 0)
        {
          Gpu_CoCmd_FlashWriteExt(phost, dest_flash, num - aligned_length, write_data);
          App_Flush_Co_Buffer(phost);
          Gpu_Hal_WaitCmdfifo_empty(phost);
        }

      /* write the rest write_data */
      write_data = write_data + num - aligned_length;
      for (i = 0; i < FLASH_WRITE_ALIGN_BYTE; i++)
        {
          if (i < aligned_length)
            padding_arr[i] = *write_data++;
          else
            padding_arr[i] = 0xFF; /* should use 0xFF instead of 0x00 to avoid writing overhead */
        }

      Gpu_CoCmd_FlashWriteExt(phost, dest_flash + num - aligned_length, FLASH_WRITE_ALIGN_BYTE, padding_arr);
      App_Flush_Co_Buffer(phost);
      Gpu_Hal_WaitCmdfifo_empty(phost);
    }

  return FLASH_CMD_SUCCESS;
}

/*
 * Writes the given data to flash.
 * If the data matches the existing contents of flash, nothing is done.
 * Otherwise the flash is erased in 4K units, and the data is written.
 *   @dest_flash: destination address in flash memory. Must be 4096-byte aligned
 *   @src_ram: source data in main memory. Must be 4-byte aligned
 *   @num: number of bytes to write, should be multiple of 4096, otherwise, dummy data will be padded
 */
Flash_Cmd_Status_t Gpu_CoCmd_FlashHelper_Update(Gpu_Hal_Context_t *phost, uint32_t dest_flash, uint32_t src_ram, uint32_t num)
{
  /* must be multiple of 4096. Cut off the extended data */
  uint32_t last_chunk =  (num%4096);

  if ((dest_flash % FLASH_UPDATE_ALIGN_BYTE != 0)||((src_ram % 4) != 0))
    return FLASH_CMD_ALIGNED_ERR;

  if (num < FLASH_UPDATE_ALIGN_BYTE)
    {
      Gpu_CoCmd_FlashUpdate(phost, dest_flash, src_ram, FLASH_UPDATE_ALIGN_BYTE);
      App_Flush_Co_Buffer(phost);
      Gpu_Hal_WaitCmdfifo_empty(phost);
    }
  else if (last_chunk == 0) /* num is multiple of 4k */
    {
      Gpu_CoCmd_FlashUpdate(phost, dest_flash, src_ram, num);
      App_Flush_Co_Buffer(phost);
      Gpu_Hal_WaitCmdfifo_empty(phost);
    }
  else /* num is not fit in multiple of 4k */
    {
      Gpu_CoCmd_FlashUpdate(phost, dest_flash, src_ram, num - last_chunk);
      App_Flush_Co_Buffer(phost);
      Gpu_Hal_WaitCmdfifo_empty(phost);

      Gpu_CoCmd_FlashUpdate(phost, dest_flash + num - last_chunk, src_ram + num - last_chunk, FLASH_UPDATE_ALIGN_BYTE);
      App_Flush_Co_Buffer(phost);
      Gpu_Hal_WaitCmdfifo_empty(phost);
    }

  return FLASH_CMD_SUCCESS;
}

/* Read date from flash to array
 *   @dest_ram: address in ram where the flash copy data to
 *   @src_flash: source address in flash memory. Must be 64-byte aligned. From 0 to 64*1024 for 64MB flash
 *   @num: number of bytes would be read
 *   @read_data: pointer to user read data
 */
Flash_Cmd_Status_t Gpu_CoCmd_FlashHelper_Read(Gpu_Hal_Context_t *phost, uint32_t dest_ram, uint32_t src_flash, uint32_t num, uint8_t *read_data)
{
  num = num - (num%4);

  if ((src_flash % FLASH_READ_ALIGN_BYTE != 0) || ((dest_ram % 4) != 0))
    return FLASH_CMD_ALIGNED_ERR;

  Gpu_CoCmd_FlashRead(phost, dest_ram, src_flash, num);
  App_Flush_Co_Buffer(phost);
  Gpu_Hal_WaitCmdfifo_empty(phost);

  Gpu_Hal_RdMem(phost, dest_ram, read_data, num);
  return FLASH_CMD_SUCCESS;
}

/* Erase entire flash */
void Gpu_CoCmd_FlashHelper_Erase(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_FlashErase(phost);
  App_Flush_Co_Buffer(phost);
  Gpu_Hal_WaitCmdfifo_empty(phost);
}

/*
 * Clears the graphics system's flash cache. It should be executed after
 * modifying graphics data in flash, otherwise bitmaps from flash may render
 * "stale" data. This command must be executed when the display list is in use,
 * immediately after a CMD SWAP command.
 */
void Gpu_CoCmd_FlashHelper_ClearCache(Gpu_Hal_Context_t *phost)
{
  Gpu_CoCmd_ClearCache(phost);
  App_Flush_Co_Buffer(phost);
  Gpu_Hal_WaitCmdfifo_empty(phost);
}

/*
 * Flash state/status:
 *   - FLASH_STATUS_BASIC    2UL
 *   - FLASH_STATUS_DETACHED 1UL
 *   - FLASH_STATUS_FULL     3UL
 *   - FLASH_STATUS_INIT     0UL
 */
uint8_t Gpu_CoCmd_FlashHelper_GetState(Gpu_Hal_Context_t *phost)
{
  return Gpu_Hal_Rd8(phost, REG_FLASH_STATUS);
}
#endif /* BT81X_ENABLE */

void Gpu_Copro_SendCmd(Gpu_Hal_Context_t *phost,uint32_t cmd)
{
#ifdef FT232H_MINGW_PLATFORM
#ifdef BUFFER_OPTIMIZATION
  App_WrCoCmd_Buffer(phost,cmd);
#else
  Gpu_Hal_Transfer32(phost,cmd);
#endif
#endif

#if defined (RPI_PLATFORM) || defined (STM32_PLATFORM)
#if defined (RPI_PLATFORM_COCMD_BURST) || defined (STM32_PLATFORM_COCMD_BURST)
   Gpu_Hal_Transfer32(phost,cmd);
#else
   Gpu_Hal_WrCmd32(phost,cmd);
#endif
#endif
}

void Gpu_CoCmd_SendStr(Gpu_Hal_Context_t *phost,const char8_t *s)
{
#ifdef FT232H_MINGW_PLATFORM
#ifdef BUFFER_OPTIMIZATION
  App_WrCoStr_Buffer(phost,s);
#else
  Gpu_Hal_TransferString(phost,s);
#endif
#endif

#if defined (RPI_PLATFORM) || defined (STM32_PLATFORM)
#if defined (RPI_PLATFORM_COCMD_BURST) || defined (STM32_PLATFORM_COCMD_BURST)
  Gpu_Hal_TransferString(phost,s);
#else
  Gpu_Hal_WrCmdBuf(phost,(uint8_t*)s,length);
#endif

  /* align 4 byte in coprocessor command buffer */
  uint8_t i=0;
  uint16_t length = 0;
  length = strlen(s) + 1;
  for (i=0; i< (4-length%4)%4 ;i++)
    Gpu_Hal_Transfer8(phost,0);
#endif
}

void Gpu_CoCmd_StartFunc(Gpu_Hal_Context_t *phost,uint16_t count)
{
#ifdef FT232H_MINGW_PLATFORM
#ifndef BUFFER_OPTIMIZATION
  Gpu_Hal_CheckCmdBuffer(phost,count);
  Gpu_Hal_StartCmdTransfer(phost,GPU_WRITE,count);
#endif
#endif

#if defined (RPI_PLATFORM) || defined (STM32_PLATFORM)
#if defined (RPI_PLATFORM_COCMD_BURST) || defined (STM32_PLATFORM_COCMD_BURST)
  Gpu_Hal_CheckCmdBuffer(phost,count);
  Gpu_Hal_StartCmdTransfer(phost,GPU_WRITE,count);
#endif
#endif
}

void Gpu_CoCmd_EndFunc(Gpu_Hal_Context_t *phost,uint16_t count)
{
#ifdef FT232H_MINGW_PLATFORM
#ifndef BUFFER_OPTIMIZATION
  Gpu_Hal_EndTransfer(phost);
  Gpu_Hal_Updatecmdfifo(phost,count);
#endif
#endif

#if defined (RPI_PLATFORM) || defined (STM32_PLATFORM)
#if defined (RPI_PLATFORM_COCMD_BURST) || defined (STM32_PLATFORM_COCMD_BURST)
  Gpu_Hal_EndTransfer(phost);
  Gpu_Hal_Updatecmdfifo(phost,count);
#endif
#endif
}

void Gpu_CoCmd_Hsf(Gpu_Hal_Context_t *phost,uint32_t w)
{
#if defined (EVE_3)
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*2);
  Gpu_Copro_SendCmd(phost, CMD_HSF);
  Gpu_Copro_SendCmd(phost, w);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*2));
#endif
}
