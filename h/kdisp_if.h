//
// FILE
// kinf.h
//
// DESCRIPTION
// This file is to provide an interface between kernel programs
// and upper software.  Don't place anything other than kernel
// definitions.
// Also always make sure this file is coherent with the kernel
// program.
//

#ifndef	KDISP_INF_H
#define	KDISP_INF_H

#include "types.h"

#include "cpu.h"
#include "framebuf_def.h" //swpong 2006 0530
#include "vpp_def.h" //swpong 2006 0530
#include "framebuf_if.h" //swpong 2006 0530
#include "vpp_if.h" //swpong 2006 0530



// FRAMEBUF
// framebuf_mb_width    macroblock-mode
// framebuf_line_width
extern  UINT16  framebuf_mb_width;
extern  UINT16  framebuf_line_width;


static  inline  void    set_framebuf_mb_mode_width(unsigned v)
{
    framebuf_mb_width=v;
}

static  inline  void    set_framebuf_linear_mode_width(unsigned v)
{
    framebuf_line_width=v;
}

static  inline  int     get_framebuf_linear_mode_width()
{
    return framebuf_line_width;
}


/*
**      VPP     VPP     VPP     VPP     VPP     VPP     VPP
*/


extern void		setup_vpp_par_mode(int flag);

extern  void    setup_vpp_mapping(int mapping, int sdram_reorder);
extern  int     get_vpp_mapping(void);
extern  void    vpp_set_bg_color(int y, int cb_cr);



#endif/*__K_DISP_INF_H*/

