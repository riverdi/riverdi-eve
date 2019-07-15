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
#else
  #error "Please choose generation of Embedded Video Engine (EVE_1, EVE_2, EVE_3)"
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
  #define DispPCLK       5
  #define DispSwizzle    0
  #define DispPCLKPol    1
  #define DispCSpread    0
  #define DispDither     1
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
#elif defined (NTP_70) || defined (RTP_70) || defined (CTP_70)
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
#else
  #error "Please define timings in riverdi/modules.h file for custom displays"
  #define DispWidth      xxxL
  #define DispHeight     xxxL
  #define DispHCycle     xxxL
  #define DispHOffset    xxxL
  #define DispHSync0     xxxL
  #define DispHSync1     xxxL
  #define DispVCycle     xxxL
  #define DispVOffset    xxxL
  #define DispVSync0     xxxL
  #define DispVSync1     xxxL
  #define DispPCLK       x
  #define DispSwizzle    x
  #define DispPCLKPol    x
  #define DispCSpread    x
  #define DispDither     x
#endif

#endif /*_MODULES_H_*/
