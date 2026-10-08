//
// FILE
// kdef.h
//
// DESCRIPTION
// This file is to provide an definition used between kernel programs
// and upper software.  Don't place anything other than kernel
// definitions.
// Also always make sure this file is coherent with the kernel
// program.
//

#ifndef	KDISPDEF_H
#define	KDISPDEF_H

#include "types.h"

#include "cpu.h"
#include "framebuf_def.h" //swpong 2006 0530
#include "vpp_def.h"





// chip part number & version






/*
**      VPP     VPP     VPP     VPP     VPP     VPP     VPP
*/
// Pixel Aspect Ratio
#define VPP_PAR_MP_FORCE_SQUARE		(1<<0)
#define VPP_PAR_MP4_FORCE_SQUARE	(1<<1)
#define VPP_PAR_MP4_GUESS_43TV		(1<<2)
#define VPP_PAR_MP4_REVERSE_169TV	(1<<3)
#define VPP_PAR_MP4_PARTIAL_169TV	(1<<4)



#endif/*__K_DISP_DEF_H*/

