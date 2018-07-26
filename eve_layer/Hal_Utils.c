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
#include "Hal_Utils.h"
#include "App_Common.h"


/* fadeout effect by changing the display PWM from 100 till 0 */
void fadeout(Gpu_Hal_Context_t *phost)
{
    int32_t i;

    for (i = 100; i >= 0; i -= 3)
    {
        Gpu_Hal_Wr8(phost,REG_PWM_DUTY,i);
        Gpu_Hal_Sleep(2);
    }
}


/* fadein effect by changing the display PWM from 0 till 100 and finally 128 */
void fadein(Gpu_Hal_Context_t *phost)
{
    int32_t i;

    for (i = 0; i <=100 ; i += 3)
    {
        Gpu_Hal_Wr8(phost,REG_PWM_DUTY,i);
        Gpu_Hal_Sleep(2);//sleep for 2 ms
    }
    /* Finally make the PWM 100% */
    i = 128;
    Gpu_Hal_Wr8(phost,REG_PWM_DUTY,i);
}


float_t cal_average(float_t * ptr_elements , uint16_t elements)
{
    float_t average = 0.0, sum = 0.0;
    uint16_t i = 0;

    for (i = 0; i < elements; i++)
    sum += *(ptr_elements + i);

    average = sum / elements;

    return(average);
}

#ifdef POLAR_UTIL

const uint16_t sintab[] = {
    0, 402, 804, 1206, 1607, 2009, 2410, 2811, 3211, 3611, 4011, 4409, 4807,
    5205, 5601, 5997, 6392, 6786, 7179, 7571, 7961, 8351, 8739, 9126, 9511,
    9895, 10278, 10659, 11038, 11416, 11792, 12166, 12539, 12909, 13278,
    13645, 14009, 14372, 14732, 15090, 15446, 15799, 16150, 16499, 16845,
    17189, 17530, 17868, 18204, 18537, 18867, 19194, 19519, 19840, 20159,
    20474, 20787, 21096, 21402, 21705, 22004, 22301, 22594, 22883, 23169,
    23452, 23731, 24006, 24278, 24546, 24811, 25072, 25329, 25582, 25831,
    26077, 26318, 26556, 26789, 27019, 27244, 27466, 27683, 27896, 28105,
    28309, 28510, 28706, 28897, 29085, 29268, 29446, 29621, 29790, 29955,
    30116, 30272, 30424, 30571, 30713, 30851, 30984, 31113, 31236, 31356,
    31470, 31580, 31684, 31785, 31880, 31970, 32056, 32137, 32213, 32284,
    32350, 32412, 32468, 32520, 32567, 32609, 32646, 32678, 32705, 32727,
    32744, 32757, 32764, 32767, 32764};


int16_t qsin(uint16_t a)
{
    uint8_t f;
    int16_t s0,s1;

    if (a & 32768)
    return -qsin(a & 32767);
    if (a & 16384)
    a = 32768 - a;
    f = a & 127;
    s0 = *(uint16_t *)(sintab + (a >> 7));
    s1 = *(uint16_t *)(sintab + (a >> 7) + 1);
    return (s0 + ((int32_t)f * (s1 - s0) >> 7));
}


int16_t qcos(uint16_t a)
{
    return (qsin(a + 16384));
}

void polarxy(int32_t r, float_t th, int32_t *x,
             int32_t *y, int32_t ox, int32_t oy)
{
    *x = (16 * ox) + (((long)r * qsin(th)) >> 11) + 16 ;
    *y = (16 * oy) - (((long)r * qcos(th)) >> 11);
}


void polar(Gpu_Hal_Context_t *phost, int32_t r,
           float_t th, int32_t ox, int32_t oy)
{
    int32_t x, y;
    polarxy(r, th, &x, &y, ox, oy);
    App_WrCoCmd_Buffer(phost,VERTEX2F(x,y));

}

float_t da(float_t i, int16_t degree)
{
    return (i - degree)* 32768 /360 ;
}

#endif /* POLAR_UTIL */
