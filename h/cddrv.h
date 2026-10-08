#ifndef __CDDRV_H
#define __CDDRV_H

#include "stdtype.h"

typedef	struct {
  BYTE	mm, ss, ff;
} MSF;

int	initCdDrv(char *);

extern	int	trk[100][4];
extern	int	trkno;

int	getRawSect(BYTE *,long);
int	getSect(BYTE *,long);
int	getRawSectMSF(BYTE *, MSF);
int	getSectMSF(BYTE *, MSF);

#endif/*__CDDRV_H*/
