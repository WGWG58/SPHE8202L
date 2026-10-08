#ifndef __TYPES_H
#define __TYPES_H

#ifndef __GNUC__ 
#define __attribute__(x)
#define __alignof__(x) 		sizeof(x)
#endif

//
// standard types
//
typedef unsigned char   BYTE;
typedef unsigned short  HWORD;
typedef unsigned short  WORD;
typedef unsigned int    LONG;

#define W64     long long
#define W32     int
#define W16     short
#define W8      char

typedef W64             INT64;
typedef W32             INT32;
typedef W16             INT16;
typedef signed  W8      INT8;

typedef unsigned W64    UINT64;
typedef unsigned W32    UINT32;
typedef unsigned W16    UINT16;
typedef unsigned W8     UINT8;


// attribute
#define __UNUSED        __attribute__ ((unused))
#define __PACKED        __attribute__ ((packed))
#define __ALIGNED(n)    __attribute__ ((aligned(n))
#define __WEAK          __attribute__((weak))

/* bcd */
#define	getBCD(p)	(((((UINT8 *)(p))[0])>>4)*10 + ((((UINT8 *)(p))[0])&0x0f))

//
// ...
#define	getUINT16_bi(p)	((UINT16) (((UINT8 *)(p))[1] | ((UINT16)((UINT8 *)(p))[0]<<8)))
#define	getUINT16_li(p)	((UINT16) (((UINT8 *)(p))[0] | ((UINT16)((UINT8 *)(p))[1]<<8)))

#define	getUINT24_bi(p)	((UINT32) (((UINT8 *)(p))[2] | ((UINT32)((UINT8 *)(p))[1]<<8) | ((UINT32)((UINT8 *)(p))[0]<<16)))

#define	getUINT32_bi(p)	((UINT32) (((UINT8 *)(p))[3] | ((UINT32)((UINT8 *)(p))[2]<<8) | ((UINT32)((UINT8 *)(p))[1]<<16) | ((UINT32)((UINT8 *)(p))[0]<<24)))
#define	getUINT32_li(p)	((UINT32) (((UINT8 *)(p))[0] | ((UINT32)((UINT8 *)(p))[1]<<8) | ((UINT32)((UINT8 *)(p))[2]<<16) | ((UINT32)((UINT8 *)(p))[3]<<24)))


//
// endian support
//
#include "endian.h"
#undef  getUINT16_li
#undef  getUINT16_bi
#undef  getUINT32_li
#undef  getUINT32_bi

#define getUINT16_li    lle16
#define getUINT16_bi    lbe16
#define getUINT32_li    lle32
#define getUINT32_bi    lbe32


#define	getUINT64_bi(p)	((((UINT64) getUINT32_bi(p)) << 32) | ((UINT64) getUINT32_bi(p+4)))

#define	BIG_ENDIAN

/* endian-less taste */
#ifdef	BIG_ENDIAN
#define	getUINT16(p)	getUINT16_bi((BYTE *)p)
#define	getUINT32(p)	getUINT32_bi((BYTE *)p)
#else
#define	getUINT16(p)	getUINT16_li((BYTE *)p)
#define	getUINT32(p)	getUINT32_li((BYTE *)p)
#endif

#define	getBiUINT32(p)	getUINT32_li((BYTE *)p)
#define	getBiUINT16(p)	getUINT16_li((BYTE *)p)


#ifndef  TRUE
#define  TRUE  1
#endif

#ifndef  FALSE
#define  FALSE 0
#endif


#define IS_B7_ONE(p)        ( ((p) & 0x80) == 0x80 )
#define IS_B7_ZERO(p)	    ( ((p) & 0x80) == 0x00 )

#define GET_LOW_NIBBLE(p)   ((p) & 0x0F)

#ifndef NULL
#define NULL    ((void *)0)
#endif

#endif/*__TYPES_H*/

