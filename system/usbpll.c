//
// FILE
// usbpll.c
//
// DESCRIPTION
// USB PLL driver
//

#include "config.h"
#include "regmap.h"

#ifdef  SPHE8202
//
// FUNCTION
// set_usbpll_reg(s, ns)
//
// DESCRIPTION
// Setup USB PLL
//
// Fosc = 27MHz
// Fosc / N(s) = 3MHz = Fclkx2 / (2*M(ns))
// (N(s)=9 if Fosc=27MHz)
//
// N(s)  =  s2*4 +  s1*2 +  s0*1 + 1
// M(ns) = ns2*4 + ns1*2 + ns0*1 + 1
//
void
set_usbpll_reg(unsigned s, unsigned ns)
{
    unsigned cfg9;
    cfg9 = regs0->sft_cfg9;
    regs0->sft_cfg9 = (cfg9 & ~0xfff) | ((ns<<6)|(s));
}
#endif

