#ifndef _MEMCFG_DSP3_H_
#define _MEMCFG_DSP3_H_

#include "user_init.h"

#if defined(IC_8202D)||defined(IC_8202L)||defined(IC_8203A)
    #include "memmap_dsp3_8202D.h"
#else
    #include "memmap_dsp3_82XX.h"
#endif

#endif

