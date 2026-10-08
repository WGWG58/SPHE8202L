#ifndef __MEMMAP_H
#define __MEMMAP_H

//
// GLOBAL mapping
#define	ROM_BASE_CACHED		0x88000000
#define	ROM_BASE_UNCACHED	0xa8000000
#define	SDRAM_BASE_CACHED	0x80000000
#define	SDRAM_BASE_UNCACHED	0xa0000000
#define DATA_RAM_BASE       0xbfff0000

#define	ROM_BASE		ROM_BASE_CACHED
#define	SDRAM_BASE		SDRAM_BASE_CACHED

/*
** anchors
*/
#include "types.h"
#include "regmap.h"

#ifdef SPHE1000   //kevinmonkey 060530 move the section to each IC regmap, but I can't access "regmap_1000.h"
    #define	MEM_SUPYA	(regs0->supya)
    #define	MEM_EVBYA	(regs0->evbya)
    #define	MEM_IOPYA	(regs0->iopya)
    
    #ifdef DVD728
    // 728
    extern	UINT16	dsp24ya, audya, pcmya;
    #define	MEM_DSP24YA	dsp24ya
    #define	MEM_AUDYA	audya
    #define	MEM_PCMYA	pcmya
    #define	MEM_CDYA	(regs0->cdwya)
    #define MEM_EVBYA_LIMIT	(regs0->evbya_limit)
    #else
    // 720
    #define MEM_EABYA	(regs0->eabya)
    #define	MEM_DSP24YA     (regs0->dsp24ya)
    #define	MEM_AUDYA       (regs0->audya)
    #define MEM_PCMYA       (regs0->pcmya)
    #define MEM_EVBYA2	(regs0->evbya2)
    #define	MEM_CDYA	(regs0->cdya)
    #endif
    
    /*
    ** starts
    */
    #define	CBV_YS		MEM_CDYA
    #define	OBV_YS		MEM_OSDYA
    #define	SBV_YS		MEM_SUPYA
    #define	DSP24_YS	MEM_DSP24YA
    #define	PCM_YS		MEM_PCMYA
    #define AWV_YS 		MEM_AUDYA
    
    #ifdef DVD728
    #define	VBV_YS		MEM_EVBYA
    #else
    #define	VBV_YS          0
    #define ABV_YS          MEM_EABYA
    #endif
    
    /*
    ** ends
    */
    //#define	VBV_YE		(MEM_EABYA)
    #define	ABV_YE		(MEM_CDYA)
    #define	CBV_YE		(MEM_CDYA+CBV_H)
    #define	OBV_YE		(MEM_SUPYA)
    #define	SBV_YE		(MEM_DSP24YA)
    //#define	DSP24_YE	(MEM_DSP16YA)
    #define	IOP_YE		(MEM_PCMYA)
    #define PCM_YE 		(MEM_AUDYA)
    
    /*
    ** HEIGHT
    */
    #define	VBV_H		(VBV_YE - 0)
    #define	ABV_H		(ABV_YE - ABV_YS)
    #define	SBV_H		(SBV_YE - SBV_YS)
    #define	CBV_H		(regs0->cdwya_limit)
    #define	OBV_H		(OBV_YE - OBV_YS)
    
    #ifdef DVD728
    #undef VBV_H
    #define	VBV_H		(MEM_EVBYA_LIMIT)
    #endif
#endif  //#ifdef SPHE1000   //kevinmonkey 060530 move to each IC regmap

#define	get_cbv_ptr(x,y)	((BYTE *)(SDRAM_BASE+1024*(CBV_YS+(y))+(x)))
#define	get_dram_ptr()	    ((BYTE *)(DATA_RAM_BASE))
#define	get_cbv_ptr_uc(x,y)	((BYTE *)(SDRAM_BASE_UNCACHED+1024*(CBV_YS+(y))+(x)))
#define	get_sbv_ptr(x,y)	((BYTE *)(SDRAM_BASE+1024*(SBV_YS+(y))+(x)))

#define get_dsp_im_ptr(x,y)	((BYTE *)(SDRAM_BASE+1024*(DSP24_YS+(y))+(x)))
#define get_dsp_aud_ptr(x,y)	((BYTE *)(SDRAM_BASE+1024*(AWV_YS+(y))+(x)))
#define	get_dsp_pcm_ptr(x,y)	((BYTE *)(SDRAM_BASE+1024*(PCM_YS+(y))+(x)))

#define get_dsp_im_uptr(x,y)	((BYTE *)(SDRAM_BASE_UNCACHED+1024*(DSP24_YS+(y))+(x)))
#define get_dsp_aud_uptr(x,y)	((BYTE *)(SDRAM_BASE_UNCACHED+1024*(AWV_YS+(y))+(x)))
#define	get_dsp_pcm_uptr(x,y)	((BYTE *)(SDRAM_BASE_UNCACHED+1024*(PCM_YS+(y))+(x)))

#endif/*__MEMMAP_H*/

