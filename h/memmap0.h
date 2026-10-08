//
// FILE
// memmap0.h
//
// DESCRIPTION
// allocate sdram memory space
//
#ifndef	__MEMMAP0_H
#define __MEMMAP0_H

#include "SET.H" //Oliver : the on/off switch of following defines is located here

#if defined(SDRAM_16Mb_Mode)
    #ifdef TURBO_DECODE
        #include "memmap0s_tb.h"
    #else
        #include "memmap0s.h"
    #endif

#else
// 32mb version
    #if defined(IC_8202L) || defined(IC_8203A)
        #include "memmap0b_8202L.h"  //adopt new memory layout which provide continuous buffer extent.
    #else
        #include "memmap0b.h"
    #endif  //#ifdef CUSTOMERS_8202L_64_DVD
#endif

#ifdef SUPPORT_HIGH_DEFINITION_VIDEO
#include "memmap0_HD.h"
#endif

#ifdef PMP_DVD //kenny  2005/8/18
#include "memmap0_pmp.h"
#endif
#endif

#ifdef SUPPORT_TELETEXT 
#include "..\dvb_h\ttx_mmap.h"	//tcf added 2006-1-23 16:30
#endif
