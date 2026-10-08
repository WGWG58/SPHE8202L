#ifndef	__HW_H
#define	__HW_H

#include "hwif.h"

// 
// system reset
#define	HW_RESET_GLOBAL		(1<<0)		// 1-shot global reset
#define	HW_RESET_RISC		(1<<1)
#define	HW_RESET_BOOTROM	(1<<2)
#define	HW_RESET_FLASHIF	(1<<3)
#define	HW_RESET_RI		(1<<4)		// RISC	interface
#define	HW_RESET_SDCTRL		(1<<5)		// SDRAM controller
#define	HW_RESET_AGDC		(1<<6)
#define	HW_RESET_GRFX		(1<<7)		// graphics hardware
#define	HW_RESET_PARM		(1<<8)		// video decoding parameter
#define	HW_RESET_IDCT		(1<<9)
#define	HW_RESET_INVQ		(1<<10)
#define	HW_RESET_VLD		(1<<11)
#define	HW_RESET_MC	        (1<<12)
#if     defined(IC_8202D)
#define	HW_RESET_TRANS		(0<<13)
//#error  ydebugy
#else   /* defined(IC_8202D) */
//#error  xdebugx
#define	HW_RESET_TRANS		(1<<13)
#endif  /* defined(IC_8202D) */
#define	HW_RESET_MMU		(1<<14)
#define	HW_RESET_BUFCTL		(1<<15)		// buffer control

#define	HW_RESET_OGT		(1<<0)
#define	HW_RESET_VPP		(1<<1)
#define	HW_RESET_OSD		(1<<2)
#define	HW_RESET_TV		(1<<3)
#define	HW_RESET_IOP		(1<<4)
#define	HW_RESET_DSP		(1<<5)
#define	HW_RESET_STC		(1<<6)
#define	HW_RESET_CD		(1<<7)
#define	HW_RESET_HOST_CSS	(1<<8)
#define	HW_RESET_LPT		(1<<9)
#define	HW_RESET_UA0		(1<<10)
#define	HW_RESET_UA1		(1<<11)
#define	HW_RESET_TDM		(1<<12)         // 1000
#define	HW_RESET_BOOT_STRAP	(1<<13)         // 2000
#define	HW_RESET_BRIDGE		(1<<14)         // 4000
#define	HW_RESET_SRV		(1<<15)         // 8000 useless

#define	HW_RESET_HOST           HW_RESET_HOST_CSS
#define	HW_RESET_CSS            HW_RESET_HOST_CSS

#define HW_CLKEN0_VLD           HW_RESET_VLD
#define HW_CLKEN0_INVQ          HW_RESET_INVQ
#define HW_CLKEN0_IDCT          HW_RESET_IDCT
#define HW_CLKEN0_MC            HW_RESET_MC
#define HW_CLKEN0_TRANS         HW_RESET_TRANS
#define HW_CLKEN0_BUFCTL        HW_RESET_BUFCTL
#define	HW_CLKEN0_GRFX          HW_RESET_GRFX

#define HW_CLKEN1_HOST_CSS      HW_RESET_HOST_CSS

#endif/*__HW_H*/

