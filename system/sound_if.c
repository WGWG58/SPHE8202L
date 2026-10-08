
#include "global.h"
#include "osd.h"
#include "func.h"
#include "ircmd.h"
#include "memmap.h"
#include "dsp3_if.h"
#include "stdlib.h"
#include "cchar.h"

#define MAX_PAGE_ITEM   4

extern UINT8 sound_sel[MAX_PAGE_ITEM];

#ifdef SUPPORT_3DSOUND

BYTE soundGetSurroundType()
{
	BYTE iVal = 0;
	iVal = sound_sel[0] - 2;
	return iVal;
}

BYTE soundGetEQType()  //ycwen 2005/10/3 restore EQ when DSP_Reset is also needed.
{
	BYTE iVal = 0;
	iVal = sound_sel[1]; //ycwen : Decreasing 2 later.
	return iVal;
}

#else

BYTE soundGetSurroundType()	{return 0;}
BYTE soundGetEQType()	{return 0;} //ycwen 2005/10/3 restore EQ when DSP_Reset is also needed.

#endif



