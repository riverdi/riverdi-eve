/*
 * Copyright (c) Riverdi Sp. z o.o. sp. k. <riverdi@riverdi.com>
 * Copyright (c) Skalski Embedded Technologies <contact@lukasz-skalski.com>
 */

#ifndef _MODULES_H_
#define _MODULES_H_

/*
 * Embedded Video Engine Series
 */

#if defined (EVE_1)
  #define FT80X_ENABLE
#elif defined (EVE_2)
  #define FT81X_ENABLE
#elif defined (EVE_3)
  #define BT81X_ENABLE
  #define FT81X_ENABLE
#elif defined (EVE_4)
  #define BT81X_ENABLE

#else
  #error "Please choose generation of Embedded Video Engine (EVE_1, EVE_2, EVE_3, EVE_4)"
#endif

/*
 * Definitions for Riverdi Intelligent Modules
 */

#if defined (EVE_1)
#if defined (NTP_50) || defined (RTP_50) || defined (CTP_50) || \
    defined (NTP_70) || defined (RTP_70) || defined (CTP_70)
  #error "Not supported configuration - please contact Riverdi support <support@riverdi.com"
#endif

#endif
#if defined (EVE_2)
#if defined (NTP_35) || defined (RTP_35) || defined (CTP_35) || \
    defined (NTP_43) || defined (RTP_43) || defined (CTP_43)
  #error "Not supported configuration - please contact Riverdi support <support@riverdi.com"
#endif
#endif

#if defined (NTP_35) || defined (RTP_35) || defined (CTP_35)
  #define DispWidth      320L
  #define DispHeight     240L
  #define DispHCycle     408L
  #define DispHOffset    70L
  #define DispHSync0     0L
  #define DispHSync1     10L
  #define DispVCycle     263L
  #define DispVOffset    13L
  #define DispVSync0     0L
  #define DispVSync1     2L
  #define DispPCLK       6
  #define DispSwizzle    2
  #define DispPCLKPol    1
  #define DispCSpread    0
  #define DispDither     1
#elif defined (IPS_35)
  #define DispWidth      320L
  #define DispHeight     240L
  #define DispHCycle     371L
  #define DispHOffset    43L
  #define DispHSync0     0L
  #define DispHSync1     4L
  #define DispVCycle     260L
  #define DispVOffset    12L
  #define DispVSync0     0L
  #define DispVSync1     4L
  #define DispPCLK       1
  #define DispSwizzle    0
  #define DispPCLKPol    1
  #define DispCSpread    0
  #define DispDither     0
  #define DispPLCLKFREQ  0x22
  #define DispPCLK2x	 0
#elif defined (NTP_43) || defined (RTP_43) || defined (CTP_43)
  #define DispWidth      480L
  #define DispHeight     272L
  #define DispHCycle     548L
  #define DispHOffset    43L
  #define DispHSync0     0L
  #define DispHSync1     41L
  #define DispVCycle     292L
  #define DispVOffset    12L
  #define DispVSync0     0L
  #define DispVSync1     10L
  #define DispPCLK       3
  #define DispSwizzle    0
  #define DispPCLKPol    1
  #define DispCSpread    0
  #define DispDither     1
#elif defined (IPS_43)
  #define DispWidth      480L
  #define DispHeight     272L
  #define DispHCycle     531L
  #define DispHOffset    43L
  #define DispHSync0     0L
  #define DispHSync1     4L
  #define DispVCycle     292L
  #define DispVOffset    12L
  #define DispVSync0     0L
  #define DispVSync1     4L
  #define DispPCLK       1
  #define DispSwizzle    0
  #define DispPCLKPol    1
  #define DispCSpread    0
  #define DispDither     0
  #define DispPLCLKFREQ  0x232
  #define DispPCLK2x	 0
#elif defined (NTP_50) || defined (RTP_50) || defined (CTP_50)
  #define DispWidth      800L
  #define DispHeight     480L
  #define DispHCycle     1056L
  #define DispHOffset    46L
  #define DispHSync0     0L
  #define DispHSync1     10L
  #define DispVCycle     525L
  #define DispVOffset    23L
  #define DispVSync0     0L
  #define DispVSync1     10L
  #define DispPCLK       2
  #define DispSwizzle    0
  #define DispPCLKPol    0
  #define DispCSpread    0
  #define DispDither     1
#elif defined (IPS_50)
  #define DispWidth      800L
  #define DispHeight     480L
  #define DispHCycle     816L
  #define DispHOffset    8L
  #define DispHSync0     0L
  #define DispHSync1     4L
  #define DispVCycle     496L
  #define DispVOffset    8L
  #define DispVSync0     0L
  #define DispVSync1     4L
  #define DispPCLK       1
  #define DispSwizzle    0
  #define DispPCLKPol    1
  #define DispCSpread    0
  #define DispDither     0
  #define DispPLCLKFREQ  0xD14
  #define DispPCLK2x	 0
#elif defined (NTP_70) || defined (RTP_70) || defined (CTP_70)
  #define DispWidth      800L
  #define DispHeight     480L
  #define DispHCycle     1056L
  #define DispHOffset    16L
  #define DispHSync0     0L
  #define DispHSync1     30L
  #define DispVCycle     525L
  #define DispVOffset    10L
  #define DispVSync0     0L
  #define DispVSync1     13L
  #define DispPCLK       2
  #define DispSwizzle    0
  #define DispPCLKPol    0
  #define DispCSpread    0
  #define DispDither     0
#elif defined (IPS_70)
  #define DispWidth      1024L
  #define DispWidth_hsf      1076L
  #define DispHeight     600L
  #define DispHCycle     1344L
  #define DispHOffset    160L
  #define DispHSync0     0L
  #define DispHSync1     70L
  #define DispVCycle     635L
  #define DispVOffset    23L
  #define DispVSync0     0L
  #define DispVSync1     10L
  #define DispPCLK       1
  #define DispSwizzle    0
  #define DispPCLKPol    1
  #define DispCSpread    0
  #define DispDither     0
  #define DispPLCLKFREQ  0xD12
  #define DispPCLK2x	 0
#elif defined (IPS_101)
  #define DispWidth      1280L
  #define DispHeight     800L
  #define DispHCycle     1440L
  #define DispHOffset    88L
  #define DispHSync0     0L
  #define DispHSync1     20L
  #define DispVCycle     838L
  #define DispVOffset    23L
  #define DispVSync0     0L
  #define DispVSync1     10L
  #define DispPCLK       1
  #define DispSwizzle    0
  #define DispPCLKPol    1
  #define DispCSpread    0
  #define DispDither     0
  #define DispPLCLKFREQ  0x8c1
  #define DispPCLK2x	 1
#endif

#endif /*_MODULES_H_*/
