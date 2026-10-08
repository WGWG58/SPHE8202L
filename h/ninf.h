//
// FILE
// ninf.h
//
// navigation interface
//
#ifndef __NINF_H
#define __NINF_H

#include "types.h"
extern  UINT32  PlayBackStartLBA;
extern  UINT32  PlayBackLength;

extern  UINT32  ninf_get_dvd_sup_clut(int n);
extern  UINT32  ninf_get_dvd_CPM(void);
extern  UINT32  ninf_get_dvd_CGMS(void);

extern  int     is_dvdaudio_aob();

#endif
