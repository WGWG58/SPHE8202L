#ifndef __FRAMEBUF_DEF_H
#define	__FRAMEBUF_DEF_H

#include "types.h"

// framebuffer location definition
#define	REF0_LUMA	(regs0->ref0_luma)
#define	REF0_CHROMA	(regs0->ref0_chroma)
#define	REF1_LUMA	(regs0->ref1_luma)
#define	REF1_CHROMA	(regs0->ref1_chroma)
#define	BIDIR_LUMA	(regs0->bidir_luma)
#define	BIDIR_CHROMA	(regs0->bidir_chroma)

#define	SDRAM_PTR()	(SDRAM_BASE)
#define	FRM0L_PTR()	(SDRAM_BASE + 1024*REF0_LUMA   )
#define	FRM0C_PTR()	(SDRAM_BASE + 1024*REF0_CHROMA )
#define	FRM1L_PTR()	(SDRAM_BASE + 1024*REF1_LUMA   )
#define	FRM1C_PTR()	(SDRAM_BASE + 1024*REF1_CHROMA )
#define	FRM2L_PTR()	(SDRAM_BASE + 1024*BIDIR_LUMA  )
#define	FRM2C_PTR()	(SDRAM_BASE + 1024*BIDIR_CHROMA)

#define FRAME_REF0      (1<<0)
#define FRAME_REF1      (1<<1)
#define FRAME_BIDIR    	(1<<2)
#define	FRAME_720	(1<<3)
#define FRAME_REF0_FILL	(1<<6)
#define FRAME_REF1_FILL	(1<<7)
#define FRAME_B_FILL	(1<<8)
#define	FRAME_FILL_BLUE		(1<<10)		// default 0x8080
#define	FRAME_FILL_LIGHTGRAY	(1<<11)		// luma: 0xa0
#define	FRAME_FILL_DARKGRAY	(1<<12)		// luma: 0x40


typedef	struct	{
    INT16  dx, dy;	// destination location
    UINT16 dly, dcy;	// destination luma/chroma rows		
    UINT16 sly, scy;	// source luma/chroma rows
    INT16  w, h;		// source w, h
    INT16  zx, zy;	// zoom factor (x,y);
} t_bitblt_op;

#endif/*__FRAMEBUF_DEF_H*/
