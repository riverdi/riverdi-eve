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

#ifndef _COPRO_CMDS_H_
#define _COPRO_CMDS_H_

void Gpu_CoCmd_Text(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t font, uint16_t options, const char8_t* s);
void Gpu_CoCmd_Number(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t font, uint16_t options, int32_t n);
void Gpu_CoCmd_LoadIdentity(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_Toggle(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t font, uint16_t options, uint16_t state, const char8_t* s);
void Gpu_CoCmd_Gauge(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range);
void Gpu_CoCmd_RegRead(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t result);
void Gpu_CoCmd_GetProps(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t w, uint32_t h);
void Gpu_CoCmd_Memcpy(Gpu_Hal_Context_t *phost,uint32_t dest, uint32_t src, uint32_t num);
void Gpu_CoCmd_Spinner(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, uint16_t style, uint16_t scale);
void Gpu_CoCmd_BgColor(Gpu_Hal_Context_t *phost,uint32_t c);
void Gpu_CoCmd_Swap(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_Inflate(Gpu_Hal_Context_t *phost,uint32_t ptr);
void Gpu_CoCmd_Translate(Gpu_Hal_Context_t *phost,int32_t tx, int32_t ty);
void Gpu_CoCmd_Stop(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_Slider(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t range);
void Gpu_CoCmd_TouchTransform(Gpu_Hal_Context_t *phost,int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t tx0, int32_t ty0, int32_t tx1, int32_t ty1, int32_t tx2, int32_t ty2, uint16_t result);
void Gpu_CoCmd_Interrupt(Gpu_Hal_Context_t *phost,uint32_t ms);
void Gpu_CoCmd_FgColor(Gpu_Hal_Context_t *phost,uint32_t c);
void Gpu_CoCmd_Rotate(Gpu_Hal_Context_t *phost,int32_t a);
void Gpu_CoCmd_Button(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, int16_t font, uint16_t options, const char8_t* s);
void Gpu_CoCmd_MemWrite(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t num);
void Gpu_CoCmd_Scrollbar(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t size, uint16_t range);
void Gpu_CoCmd_GetMatrix(Gpu_Hal_Context_t *phost,int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f);
void Gpu_CoCmd_Sketch(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t ptr, uint16_t format);
void Gpu_CoCmd_MemSet(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t value, uint32_t num);
void Gpu_CoCmd_GradColor(Gpu_Hal_Context_t *phost,uint32_t c);
void Gpu_CoCmd_Bitmap_Transform(Gpu_Hal_Context_t *phost,int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t tx0, int32_t ty0, int32_t tx1, int32_t ty1, int32_t tx2, int32_t ty2, uint16_t result);
void Gpu_CoCmd_Calibrate(Gpu_Hal_Context_t *phost,uint32_t result);
void Gpu_CoCmd_SetFont(Gpu_Hal_Context_t *phost,uint32_t font, uint32_t ptr);
void Gpu_CoCmd_Logo(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_Append(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t num);
void Gpu_CoCmd_MemZero(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t num);
void Gpu_CoCmd_Scale(Gpu_Hal_Context_t *phost,int32_t sx, int32_t sy);
void Gpu_CoCmd_Clock(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t h, uint16_t m, uint16_t s, uint16_t ms);
void Gpu_CoCmd_Gradient(Gpu_Hal_Context_t *phost,int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1);
void Gpu_CoCmd_SetMatrix(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_Track(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, int16_t tag);
void Gpu_CoCmd_GetPtr(Gpu_Hal_Context_t *phost,uint32_t result);
void Gpu_CoCmd_Progress(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t range);
void Gpu_CoCmd_ColdStart(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_Keys(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t w, int16_t h, int16_t font, uint16_t options, const char8_t* s);
void Gpu_CoCmd_Dial(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t val);
void Gpu_CoCmd_LoadImage(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t options);
void Gpu_CoCmd_Dlstart(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_Snapshot(Gpu_Hal_Context_t *phost,uint32_t ptr);
void Gpu_CoCmd_ScreenSaver(Gpu_Hal_Context_t *phost);

#ifdef FT801_ENABLE
void Gpu_CoCmd_CSketch(Gpu_Hal_Context_t *phost,int16_t x, int16_t y, uint16_t w, uint16_t h, uint32_t ptr, uint16_t format,uint16_t freq);
#endif

#ifdef FT81X_ENABLE
void Gpu_CoCmd_SetBitmap(Gpu_Hal_Context_t *phost,uint32_t source, uint16_t fmt, uint16_t w, uint16_t h);
void Gpu_CoCmd_SetScratch(Gpu_Hal_Context_t *phost,uint32_t handle);
void Gpu_CoCmd_VideoStart(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_SetBase(Gpu_Hal_Context_t *phost,uint32_t base);
void Gpu_CoCmd_VideoFrame(Gpu_Hal_Context_t *phost,uint32_t dst, uint32_t ptr);
void Gpu_CoCmd_RomFont(Gpu_Hal_Context_t *phost,uint32_t font, uint32_t romslot);
void Gpu_CoCmd_PlayVideo(Gpu_Hal_Context_t *phost,uint32_t options);
void Gpu_CoCmd_Sync(Gpu_Hal_Context_t *phost);
void Gpu_CoCmd_Int_RAMShared(Gpu_Hal_Context_t *phost,uint32_t ptr);
void Gpu_CoCmd_Int_SWLoadImage(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t options);
void Gpu_CoCmd_MediaFifo(Gpu_Hal_Context_t *phost,uint32_t ptr, uint32_t size);
void Gpu_CoCmd_Snapshot2(Gpu_Hal_Context_t *phost,uint32_t fmt, uint32_t ptr, int16_t x, int16_t y, int16_t w, int16_t h);
void Gpu_CoCmd_SetFont2(Gpu_Hal_Context_t *phost,uint32_t font, uint32_t ptr, uint32_t firstchar);
void Gpu_CoCmd_SetRotate(Gpu_Hal_Context_t *phost,uint32_t r);
#endif

void Gpu_Copro_SendCmd(Gpu_Hal_Context_t *phost,uint32_t cmd);
void Gpu_CoCmd_SendStr(Gpu_Hal_Context_t *phost,const char8_t *s);
void Gpu_CoCmd_StartFunc(Gpu_Hal_Context_t *phost,uint16_t count);
void Gpu_CoCmd_EndFunc(Gpu_Hal_Context_t *phost,uint16_t count);

#endif  /*COPRO_CMDS_H*/
