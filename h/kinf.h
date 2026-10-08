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

#ifndef	__KINF_H
#define	__KINF_H

//swpong 2006 0526
#include "kern_if.h"
#include "kern_def.h"

#include "kdisp_if.h"
#include "kdisp_def.h"
////////////////////////

//Query information flag
#define KINFO_FRAME_RATE                         0
#define KINFO_ASPECT_RATIO                      1
#define KINFO_HORIZONTAL_SIZE                 2
#define KINFO_VERTICAL_SIZE                      3

//Information 
//For KINFO_FRAME_RATE
#define KINF_FRAMERATE_60                       0x8
#define KINF_FRAMERATE_59                       0x7
#define KINF_FRAMERATE_50                       0x6

//For KINFO_ASPECT_RATIO
#define KINF_ASPECTRATIO_FORB                0x0
#define KINF_ASPECTRATIO_SQUARE           0x1        
#define KINF_ASPECTRATIO_43                    0x2
#define KINF_ASPECTRATIO_169                  0x3
#define KINF_ASPECTRATIO_2211                0x4


int Kcall_seq_info(UINT32 uReqInfo);

#endif/*__KINF_H*/

