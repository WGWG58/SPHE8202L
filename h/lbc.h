#ifndef __LBC_H
#define __LBC_H

#ifdef DVD728
#include "regmap.h"
static	inline	void	MIPS_flush_LBC_cache()
{
    regs0->lbc_control = 1;
    while (regs0->lbc_control == 0);
}
#else
#include "memmap.h"
static	inline	void	MIPS_flush_LBC_cache()
{
    volatile UINT32 *p = (volatile UINT32 *)SDRAM_BASE_UNCACHED;
    (void) p[0];
    (void) p[8];
}
#endif

#endif/*__LBC_H*/

