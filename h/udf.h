#ifndef __UDF_H
#define __UDF_H

#include "fs.h"
#include "fs96602.h"

// error ID
enum {
	ERROR_GET_DATA        = -1,
	ERROR_DISC_CONTENT    = -2,
	ERROR_TRAY_OPEN       = -3
};

//
UINT16 ReadICB(UINT32 sector, short_ad* pShort_AD);

// 
int ReadUDFVolume(void);

//
int ReadUDFDir(void);

//
int TakeCareUDFDir(UINT32 nSector);

// Read files in certain directory
int ReadUDFFile(UINT32 nSector, int nDirIndex);

// 
UINT32 LookupVAT(int index);

//
void UDFGetFileName(char *psrc, char *pdst, int namelen );


#endif /* __UDF_H */

