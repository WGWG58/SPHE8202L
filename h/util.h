#ifndef __UTIL_H
#define __UTIL_H

#include "types.h"
#include "endian.h"

#ifndef	__GNUC__
#define	__attribute__(x)	/**/
#endif

BYTE adjust_trk_num(BYTE trk);
/*
** BCD processing 
*/
int bin2bcd(BYTE x)	__attribute__ ((const));
int bcd2bin(BYTE x)	__attribute__ ((const));

#define	MSF(mm,ss,ff)	(((UINT32)(mm)<<16) | ((UINT32)(ss)<<8) | (BYTE)(ff))

#define	MSF2l(mm,ss,ff)	(((mm)*60+(ss))*75+(ff)-150)

#define	MSFC(cna,mm,ss,ff)	( ((UINT32)(cna)<<24) \
				| ((UINT32)(mm) <<16) \
				| ((UINT32)(ss)<<8) \
				| (BYTE)(ff))

UINT32	l2msf(UINT32);
UINT32	msf2l(UINT32);

UINT32	addmsf(UINT32, int)	__attribute__ ((const));
UINT32	addmsf_ss(UINT32, int)	__attribute__ ((const));

#define	msf_cna(msf)	(((msf)>>24) & 0x00ff)//kenny

#define	msf_mm(msf)	(((msf)>>16) & 0xff)

#define	msf_ss(msf)	(((msf)>>8) & 0xff)
#define	msf_ff(msf)	(((msf)>>0) & 0xff)
//#define M2I(msf)			( msf_mm(msf)*60+msf_ss(msf) )
UINT32 M2I(UINT32 msf);//terry,2003/8/20 01:23AM

#ifdef gcc
static	inline	int min(int x, int y)	{return (x)>(y) ? (y) : (x);}
static	inline	int max(int x, int y)	{return (x)>(y) ? (x) : (y);}
#else
#define	min(x,y) ((x)>(y) ? (y) : (x))
#define	max(x,y) ((x)>(y) ? (x) : (y))
#endif

#endif/*__UTIL_H*/

