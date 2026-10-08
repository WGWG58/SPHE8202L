//
// FILE
// hwif.c
//

#include "config.h"
#include "regmap.h"

#include "uart.h"
#include "cpu.h"
#include "sdctrl.h"

#include "hwif.h"
#include "hw.h"

//
// FUNCTION
// hwif_reset
// DESCRIPTION
// reset all but global
//
void hwif_reset(int sel)
{
    unsigned v = 0;
    switch (sel)
    {
    case HWIF_RESET_GLOBAL:     v = HW_RESET_GLOBAL;    break;
    case HWIF_RESET_RISC:       v = HW_RESET_RISC;      break;
    case HWIF_RESET_BR:         v = HW_RESET_BOOTROM;   break;
    case HWIF_RESET_FLASHIF:    v = HW_RESET_FLASHIF;   break;
    case HWIF_RESET_RI:         v = HW_RESET_RI;        break;
    case HWIF_RESET_SDCTRL:     v = HW_RESET_SDCTRL;    break;
    case HWIF_RESET_AGDC:       v = HW_RESET_AGDC;      break;
    case HWIF_RESET_GRFX:       v = HW_RESET_GRFX;      break;
    case HWIF_RESET_PARM:       v = HW_RESET_PARM;      break;
    case HWIF_RESET_IDCT:       v = HW_RESET_IDCT;      break;
    case HWIF_RESET_INVQ:       v = HW_RESET_INVQ;      break;
    case HWIF_RESET_VLD:        v = HW_RESET_VLD;       break;
    case HWIF_RESET_MC:         v = HW_RESET_MC;        break;
    case HWIF_RESET_TRANS:      v = HW_RESET_TRANS;     break;
    case HWIF_RESET_MMU:        v = HW_RESET_MMU;       break;
    case HWIF_RESET_BUFCTL:     v = HW_RESET_BUFCTL;    break;
    }

    if (v != 0)
    {
        regs0->reset = v;
        return;
    }
    
    switch (sel)
    {
    case HWIF_RESET_OGT:        v = HW_RESET_OGT;       break;
    case HWIF_RESET_VPP:        v = HW_RESET_VPP;       break;
    case HWIF_RESET_OSD:        v = HW_RESET_OSD;       break;
    case HWIF_RESET_TV:         v = HW_RESET_TV;        break;
    case HWIF_RESET_IOP:        v = HW_RESET_IOP;       break;
    case HWIF_RESET_DSP:        v = HW_RESET_DSP;       break;
    case HWIF_RESET_STC:        v = HW_RESET_STC;       break;
    case HWIF_RESET_CD:         v = HW_RESET_CD;        break;
    case HWIF_RESET_CSS:        v = HW_RESET_CSS;       break;
    case HWIF_RESET_HOST:       v = HW_RESET_HOST;      break;
    case HWIF_RESET_LPT:        v = HW_RESET_LPT;       break;
    case HWIF_RESET_UA0:        v = HW_RESET_UA0;       break;
    case HWIF_RESET_UA1:        v = HW_RESET_UA1;       break;
    case HWIF_RESET_TDM:        v = HW_RESET_TDM;       break;
    case HWIF_RESET_BT:         v = HW_RESET_BRIDGE;        break;
    case HWIF_RESET_SRV:        v = HW_RESET_SRV;       break;
    }
    regs0->reset2 = v;
}

