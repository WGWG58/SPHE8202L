#ifndef RSM_UPD_H
#define RSM_UPD_H

#include "types.h"


int Resume_Info_Write_Update(UINT32 iStartAddr, BYTE *pBuf1, UINT32 iBuf1Len, BYTE *pBuf2, UINT32 iBuf2Len);
int Resume_Info_Read_Update(BYTE *pBuf1, UINT32 iLen);

#endif
