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

void Gpu_CoCmd_Text(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t font, uint16_t options, const char8_t* s)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*3 + strlen(s) + 1);
  Gpu_Copro_SendCmd(phost, CMD_TEXT);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options<<16)|(font&0xffff)));
  Gpu_CoCmd_SendStr(phost, s);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*3 + strlen(s) + 1));
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

void Gpu_CoCmd_Toggle(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t font, uint16_t options, uint16_t state, const char8_t* s)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4 + strlen(s) + 1);
  Gpu_Copro_SendCmd(phost, CMD_TOGGLE);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)font<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)state<<16)|options));
  Gpu_CoCmd_SendStr(phost, s);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4 + strlen(s) + 1));
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

void Gpu_CoCmd_Button(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, int16_t font, uint16_t options, const char8_t* s)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*4 + strlen(s) + 1);
  Gpu_Copro_SendCmd(phost, CMD_BUTTON);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)options<<16)|(font&0xffff)));
  Gpu_CoCmd_SendStr(phost, s);
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*4 + strlen(s) + 1));
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

#ifdef FT801_ENABLE
void Gpu_CoCmd_CSketch(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t ptr, uint16_t format,uint16_t freq)
{
  Gpu_CoCmd_StartFunc(phost,CMD_SIZE*5);
  Gpu_Copro_SendCmd(phost, CMD_CSKETCH);
  Gpu_Copro_SendCmd(phost, (((uint32_t)y<<16)|(x & 0xffff)));
  Gpu_Copro_SendCmd(phost, (((uint32_t)h<<16)|(w&0xffff)));
  Gpu_Copro_SendCmd(phost, ptr);
  Gpu_Copro_SendCmd(phost, (((uint32_t)freq<<16)|(format&0xffff)));
  Gpu_CoCmd_EndFunc(phost,(CMD_SIZE*5));
}
#endif

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

#endif /* FT81X_ENABLE */

void Gpu_Copro_SendCmd(Gpu_Hal_Context_t *phost,uint32_t cmd)
{
#if defined (LINUX_PLATFORM) || defined (FT232H_MINGW_PLATFORM)
#ifdef BUFFER_OPTIMIZATION
  App_WrCoCmd_Buffer(phost,cmd);
#else
  Gpu_Hal_Transfer32(phost,cmd);
#endif
#endif

#ifdef STM32_PLATFORM
#ifdef STM32_PLATFORM_COCMD_BURST
   Gpu_Hal_Transfer32(phost,cmd);
#else
   Gpu_Hal_WrCmd32(phost,cmd);
#endif
#endif
}

void Gpu_CoCmd_SendStr(Gpu_Hal_Context_t *phost,const char8_t *s)
{
#if defined (LINUX_PLATFORM) || defined (FT232H_MINGW_PLATFORM)
#ifdef BUFFER_OPTIMIZATION
  App_WrCoStr_Buffer(phost,s);
#else
  Gpu_Hal_TransferString(phost,s);
#endif
#endif

#ifdef STM32_PLATFORM
#ifdef STM32_PLATFORM_COCMD_BURST
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
#if defined (LINUX_PLATFORM) || defined (FT232H_MINGW_PLATFORM)
#ifndef BUFFER_OPTIMIZATION
  Gpu_Hal_CheckCmdBuffer(phost,count);
  Gpu_Hal_StartCmdTransfer(phost,GPU_WRITE,count);
#endif
#endif

#ifdef STM32_PLATFORM
#ifdef STM32_PLATFORM_COCMD_BURST
  Gpu_Hal_CheckCmdBuffer(phost,count);
  Gpu_Hal_StartCmdTransfer(phost,GPU_WRITE,count);
#endif
#endif
}

void Gpu_CoCmd_EndFunc(Gpu_Hal_Context_t *phost,uint16_t count)
{
#if defined (LINUX_PLATFORM) || defined (FT232H_MINGW_PLATFORM)
#ifndef BUFFER_OPTIMIZATION
  Gpu_Hal_EndTransfer(phost);
  Gpu_Hal_Updatecmdfifo(phost,count);
#endif
#endif

#ifdef STM32_PLATFORM
#ifdef STM32_PLATFORM_COCMD_BURST
  Gpu_Hal_EndTransfer(phost);
  Gpu_Hal_Updatecmdfifo(phost,count);
#endif
#endif
}
