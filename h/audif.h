#ifndef __AUDIF_H
#define __AUDIF_H

//2004AUDDRV Oliver 20041006   
//  for using audio driver purpose, put on auddrv.h instead of 
//  the following 3 includes
//#include "types.h"
//#include "audclk.h"
//#include "audcodec.h"
#include "auddrv.h"
/*
#define FS_32K      0x0001
#define FS_44K      0x0002
#define FS_48K      0x0004
#define FS_64K      0x0010
#define FS_88K      0x0020
#define FS_96K      0x0040
#define FS_128K     0x0100
#define FS_176K     0x0200
#define FS_192K     0x0400

#define FS_16K      0x1000
#define FS_22K      0x2000
#define FS_24K      0x4000

#define FS_MAX      0x8000


#define FS_DEFAULT  FS_48K

UINT32 pl2_init_val;
*/
void    audif_set_SPDIF_BITSTREAM();

#ifdef SUPPORT_SPDIF_IN  // benson add 2004/3/18 02:18¤W¤È
void spdif_in_init(void);
#endif
#endif
