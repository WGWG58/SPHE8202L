
#include "misc.h"
#include "global.h"
#include "ata.h"
#include "atapi_if.h"
#include "image.h"
#include "fs.h"
#include "func.h"
#include "cderr.h"
#include "avd.h"
#include "hdd_info.h"

// cyue 2002/11/2 11:36¤W¤È
// The HDD is Master or slave device?
// All in LBA access

//#define HDD_MASTER
#ifdef HDD_MASTER
#define HDD_DEV 0x40 // DEV_HEAD default: HDD is MASTER
#define DVD_DEV 0x50 // DEV_HEAD default: DVD is slave
#else
#define DVD_DEV 0x40 // DEV_HEAD default: DVD is MASTER
#define HDD_DEV 0x50 // DEV_HEAD default: HDD is slave
#endif


// The DVD_ROM is Master or slave device?
//#define DVD_DEV 0x50 // DEV_HEAD default: LBA access, slave mode


//UINT32 HDD_GetMaxLBA();
//	Get the MAX LBA Number of the HDD (LBA0,...LBAMAX)
// 	ARGUEMENTS  : NONE
//	RETURN VALUE: The LBA Number of Last LBA. 
//                Thus the valid LBA number is 0,1,...HDD_GetMaxLBA()
extern UINT32 HDD_GetMaxLBA();

//void HDD_Reset(void);
//	Reset the HDD device
// 	ARGUEMENTS  : NONE
//	RETURN VALUE: NONE
extern void HDD_Reset(void);

//int HDD_ReadSec(UINT8 *buff,UINT32 lba,int seccnt);
//	Read Sectors (issue CMD 0x20 'read and verify' to get sector data)
// 	ARGUEMENTS  :
//	 	UINT8 *buff: pointer of buffer to put data
//		UINT32  LBA: Start LBA of the sectors
//		int  seccnt: Sector count. valid value is 0..255. 0 means 256 sectors.
//	RETURN VALUE: 0: Success

extern int HDD_ReadSec(UINT8 *buff,UINT32 lba,int seccnt);
extern UINT8 *FS_ReadInfoSec(UINT32 lba,int seccnt);

//int HDD_WriteSec(UINT8 *buff,UINT32 lba,int seccnt);
// 	ARGUEMENTS  :
//		Write Sectors (issue CMD 0x30 'write and verify' to save sector data)
//	 	UINT8 *buff: pointer of buffer to put data
//		UINT32  LBA: Start LBA of the sectors
//		int  seccnt: Sector count. valid value is 0..255. 0 means 256 sectors.
//	RETURN VALUE: 0: Success
extern int HDD_WriteSec(UINT8 *buff,UINT32 lba,int seccnt);




//extern int HDD_GetCHS(UINT16 *cyl, UINT8 *head,UINT8 *sec);
extern int HDD_GetCHS(UINT8* buff);



extern UINT8 HDD_DEV_Existence(void);
extern int HDD_MakeInfo(HDD_INFO*, UINT8*);
extern int FS_check_BootSec(UINT8*);
