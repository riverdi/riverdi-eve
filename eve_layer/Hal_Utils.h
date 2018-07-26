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

#ifndef _HAL_UTILS_H_
#define _HAL_UTILS_H_

/* Enable sin()/cos() calculator utilities */
#define POLAR_UTIL

/* Undefine RGB from wingdi.h in Visual Studio */
#ifdef RGB
#undef RGB
#endif

#define RGB(r,g,b) ((((vc_int32_t)(r)) << 16) | (((vc_int32_t)(g))<<8) | (b))
#define SQ(v) ((v) * (v))
#define MIN(x,y)  ((x) > (y) ? (y) : (x))
#define MAX(x,y)  ((x) > (y) ? (x) : (y))
#define PLAYCOLOR        0x00A0A080
#define NOTE(n, sharp)   (((n) - 'C') + ((sharp) * 128))
#define F16(s)           ((int32_t)((s) * 65536))
#define INVALID_TOUCH_XY   0x8000
#define ABS(x)  ((x) > (0) ? (x) : (-x))
#define ALIGN_TWO_POWER_N(val,alignval) (((val)+(alignval-1))&(~(alignval-1)))

void fadeout(Gpu_Hal_Context_t *phost);
void fadein(Gpu_Hal_Context_t *phost);

float_t cal_average(float_t * ptr_elements , uint16_t elements);

#ifdef POLAR_UTIL

int16_t qsin(uint16_t a);
int16_t qcos(uint16_t a);

void polarxy(int32_t r, float_t th, int32_t *x, int32_t *y, int32_t ox, int32_t oy);
void polar(Gpu_Hal_Context_t *phost, int32_t r, float_t th, int32_t ox, int32_t oy);

float_t da(float_t i, int16_t degree);

#endif /* POLAR_UTIL */

#endif /* _HAL_UTILS_H_ */
