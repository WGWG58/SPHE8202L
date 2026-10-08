#ifndef __FS_H
#define __FS_H

#include "udf_167.h"

#ifdef DVD_SERVO
extern BYTE gbSrvDiscStatus;
#define DISC_IS_DVD()		(gbSrvDiscStatus&0x40)
#else
#define DISC_IS_DVD()		(0)
#endif


enum {
	UDF_FILE_OPENED = 1
};

enum {
	ERROR_FILE_NOT_FOUND          = -100,
		ERROR_FILE_ENTRY_FULL         = -101,
		ERROR_FILE_ENTRY_INVALID      = -102,
		ERROR_FILE_PATH               = -103,
		ERROR_FILE_SUBPATH_TOO_LONG   = -105,
		ERROR_FILE_MSF_INVALID        = -3,
		ERROR_PARAMETER               = -2,
		ERROR_GENERIC                 = -1
};

typedef struct {
    int bIsVAT;
    UINT32 FSD_Location; // File Set Descriptor Location
    UINT32 Partition_Location; // Partition Location
    UINT32 RootICB_Location;
    UINT32 DIR_Location;
    UINT32 VAT_Location;
    int nVATCount;
    int nVATOffset;
} UDFVolumeVariable;

extern UDFVolumeVariable UDFVol;
extern short_ad *pshort_ad;
extern UINT32 dVMG_LSN,dAMG_LSN;


// primitive
UINT16 udf_crc(UINT8 *data, UINT32 size, UINT16 crc);

int read_volume(void);
int  read_dir(UINT32 dir_icb, char *fn, UINT32 *picb);
int read_icb(UINT32 sector);
int read_cgms(void); // read copyright management information from cd or cddvd, robert.chang, 2006/04/04

// top level
int fs_init(void);


#define  DVD_LBA    (0)
#define  DVD_VMGI   (1)
#define  DVD_VMGM   (2)
#define  DVD_VTSI   (3)
#define  DVD_VTSM   (4)
#define  DVD_VTSTT  (5)

int read_disc(UINT8, UINT8, UINT32);
void InitVariable();

#ifdef __SIM__
UINT8 *read_disc_loc(UINT8, UINT32, UINT32);
int read_disc_next(void);

#define read_disc_check(p)	\
	((((UINT8 *)(p)) - ((UINT8 *)(pwb)) > 2048) ? \
((p) -= 2048, read_disc_next()) : TRUE)

#endif //#ifdef __SIM__


#endif /* __FS_H */

