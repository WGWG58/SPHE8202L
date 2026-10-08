#ifndef __CARDFS_H
#define __CARDFS_H

//liweihua upadte 2004-12-10

#ifdef HOST_UHCI 
 #include "uhci.h"
#elif defined(USB_HOST_DRV)
 #include "usb_host_drv.h"
#endif  
#include "fs_new.h"

#define IDE_MASTER_ID       0
#define NO_EXTRA_FDB    0

//Card status
enum {
    CARD_STATUS_NORMAL=0,
    CARD_STATUS_NG=1,
};

//kenny add GPIO definition
#ifdef GBM_CARD_READER
    #define CARD_RESET_PIN        3 //GPIO 3 ca8200 pin28
    #define CF_CARD_DETECT_PIN    2 //GPIO 2 ca8200 pin29
    #define CD_CARD_DETECT_PIN    4 //GPIO 4 ca8200 pin31
#elif defined(HJ023_CARD_READER)//wangfeng 2003-12-3 18:11
    #define CARD_RESET_PIN        3 //GPIO 3 ca8200 pin29	//Card-Reset
    #define CF_CARD_DETECT_PIN    2 //GPIO 2 ca8200 pin28	//CF-SENSE
    #define CD_CARD_DETECT_PIN    4 //GPIO 4 ca8200 pin31	//CD-SENSE
#elif defined(MIDI_4_FSLOADER_CARD)
    #define CARD_RESET_PIN        3     //GPIO  2 SPHE8200-pin29
    #define CF_CARD_DETECT_PIN    2     //GPIO  3 SPHE8200-pin28
    #define CD_CARD_DETECT_PIN    57    //GPIO 57 SPHE8200-pin163
#elif defined(QSI_PORTABLE_DVD)
    #define CARD_RESET_PIN        3     //GPIO  2 SPHE8200-pin29
    #define CF_CARD_DETECT_PIN    2     //GPIO  3 SPHE8200-pin28
    #define CD_CARD_DETECT_PIN    18    //GPIO 18 SPHE8200-pin151    
#else
    #define CARD_RESET_PIN        3 //GPIO 17 ca720 pin29
    #define CF_CARD_DETECT_PIN    2 //GPIO 18 ca720 pin28
    #define CD_CARD_DETECT_PIN    14 //GPIO 19 ca720 pin163
#endif

//card plug state //kenny 2002/11/12
#define     CARD_HAD_PLUGGED_IN   0x01  //Bit0 means card had plug-in(bit0 =1) 
#define     USER_DO_PLUG_IN       0x02  //Bit1 means user do plug-in action(bit1=1)
#define     USER_DO_PLUG_OUT      0x04 //Bit2 means user do plug-out action


#ifndef FS_REPLACE_OLD
    #ifdef INCLUDE_FAT
    #define FSFAT_ENABLE_FRAGMENT_ANCHOR_TABLE
    #endif  //#ifdef INCLUDE_FAT
#endif  //#ifndef FS_REPLACE_OLD

//if not define FSFAT_ENABLE_FRAGMENT_ANCHOR_TABLE, file fragmentation will not be handled!
//or jumping in file will be slow.
#ifdef FSFAT_ENABLE_FRAGMENT_ANCHOR_TABLE
// return code definition   //kevinmonkey 2005/9/15
#define FSFAT_SUCCESSFUL                   (0)
#define FSFAT_ERROR                        (1)
#define FSFAT_NOT_IN_FILE_RANGE            (2)
#define FSFAT_VOID_CLUSTER_LINKING         (3)
#define FSFAT_END_OF_FILE_STREAM           (4)
    
#define FSFAT_MAX_ANCHOR_POINT_OCCUPIER   (10)
#define FSFAT_UNDEFINED_ANCHOR_TABLE       (0)
#define FSFAT_TYPE1_ANCHOR_TABLE           (1)
#define FSFAT_TYPE2_ANCHOR_TABLE           (2)
#define FSFAT_TYPE3_ANCHOR_TABLE           (3)
//if too many entry, type 3 will outperformance type 2
        #if 1//(FSFAT_MAX_ANCHOR_POINT_OCCUPIER <= 50)
#define FSFAT_ENABLE_TYPE2_ANCHOR_TABLE
        #endif  //FSFAT_MAX_ANCHOR_POINT_OCCUPIER <= 50

//fragment cache adding entry policy definition.
#define FSFAT_FRAGMENT_CACHE_REPLACE       (1)
#define FSFAT_FRAGMENT_CACHE_INSERT        (2)
#define FSFAT_FRAGMENT_CACHE_ADD_BY_TYPE   (3)

typedef struct _FSFAT_tClusterAnchor
{
    UINT32 uLogicalCluster;
    UINT32 uPhysicalCluster;
} FSFAT_tClusterAnchor;
#endif  //#ifdef FSFAT_ENABLE_FRAGMENT_ANCHOR_TABLE

//temporary fixing reading files other than main media file.
extern UINT32 FS_g_uOutOfFileReading;
#define FS_SetOutOfFileReading()        (FS_g_uOutOfFileReading = 1);
#define FS_ResetOutOfFileReading()      (FS_g_uOutOfFileReading = 0);
#define FS_IsOutOfFileReading()         (FS_g_uOutOfFileReading == 1)

//sector size fix
#define CARDFS_LARGE_SECTOR_SUPPORT

typedef struct _CARD_INFO {
    UINT32  sAddBootSec;    //boot sector start address(in LBA)
    UINT32  sAddFAT;        //FAT start address(in LBA)
    UINT32  sAddFDB;        //root FDB start address, FAT16 only(in LBA)
    UINT32  sAddData;       //data start address(in LBA)
#ifdef CARDFS_LARGE_SECTOR_SUPPORT
    UINT16  bytePerSec;     //always 512
    UINT16  realBytePerSec; //actual bytes/sector
#else
    union
    {
        UINT16 bytePerSec;
        UINT16 realBytePerSec;
    };
#endif
    UINT16  secPerClus;     //sectors/Cluster
    UINT16  secPerFAT;      //sectors/FAT
    UINT16  nFDBinRoot;     //#FDB in root dir
    BYTE    nHeadMax;       //max head
    BYTE    nSecMax;        //max sector
    BYTE    typeFAT;        //FAT16/FAT32
    BYTE    nItemSizeFAT;   //2x item size in FAT(in Bytes)
    int     bFATCacheCluster;//1:cache in cluster, 0:cache in LBA
    UINT32	totalClus;		// total cluster in FAT
} CARD_INFO;

typedef struct _CARD_FILE_ {
    UINT32  stLBA;          //start LBA
    UINT32  stClus;         //start Cluster
    UINT32  iFileSize;      //file size
    UINT32  curLBA;         //current LBA
    UINT32  curClus;        //current Cluster
    int     iLeaveSize;     //file leave size
#ifdef FSFAT_ENABLE_FRAGMENT_ANCHOR_TABLE
    UINT32  uFragmentGapCount;
    UINT32  uFragmentStartCache;
    UINT32  uFragmentEndCache;
    UINT32  uFragmentClusterCache;
    FSFAT_tClusterAnchor aClusterAnchorTable[FSFAT_MAX_ANCHOR_POINT_OCCUPIER];
#endif  //#ifdef FSFAT_ENABLE_FRAGMENT_ANCHOR_TABLE
    BYTE    status;
} CARD_FILE;

#if 1//def SUPPORT_MP3_ENCODER	// here we better use "SUPPORT_WRITE_HANDLER" or something like that
typedef struct
{
    UINT32   LBA;
    UINT16   SectorNum;
    UINT32   Address;
    UINT32   Device_Read_Addr;
    UINT32	 DOSFAT_Read_Addr;
    UINT32	 Source_Write_Addr;	
	UINT8    state;
	UINT8	 status;	
}DOSWRITE_HANDLE,*pDOSWRITE_HANDLE;

extern DOSWRITE_HANDLE DosWrite_handle;
#endif

extern CARD_FILE       cardFile;

#ifdef  IDE_CF_SW//liulifeng define for read multi partition 2004.8.6
typedef struct _IDE_INFO_
{
    BYTE typeFAT;
    UINT32 sAddBootSec;
} IDE_INFO;
    
IDE_INFO    ide[8];
extern UINT8 max_part;
extern UINT8 read_sequence;
//liweihua mov here 2004-11-2 21:22
//kenny add for CF and HDD siwtch
//define CF, HDD device head
#define CF_DEV		0 	//0:mean master, 1 mean slave
#define HDD_DEV		1

//liweihua add set sequence
#define HD1     1
#define HD2     2
#define HD3     3
#define HD4     4
#define HD      HD1
#define CF      0
#endif 


BYTE    FSIsExist();
UINT32  FSGetRoot(); //get ROOT directory LBA
UINT32  FSGetFDB(UINT32 lba, UINT32 index, BYTE *buf); //get index-th FDB data structure(buf), length=32
UINT32  FSGetNextClus(UINT32 clus); //get next Cluster Link(from FAT table)
UINT32  FSGetNextLBA(UINT32 lba); //get next LBA(from FAT table)
UINT32  FSClus2LBA(UINT32 clus); //transfer cluster to lba
UINT32  FSLBA2Clus(UINT32 lba); //transfer lba to cluster
UINT32  FSLBAinClus(UINT32 lba); //get leave sectore # in the same cluster
UINT8   CardDoPacket(UINT32 wait_time, UINT8 *pck);
UINT8   CardBlockRead(UINT32 lba, UINT32 len);
int     FSReadSector(UINT32 lba, UINT32 nSec, BYTE *buf);
BYTE    FSReadStream(CARD_FILE *cfFile, UINT32 nSec, BYTE *buf); //continuous read nSec sectors from cfFile.curLBA, and put data to *buf
BYTE    FSFileSeek(CARD_FILE *cfFile, int nSec); //seek file, move pointer(curLBA) in nSec(>0:FF, <0:BF) sectors step.
BYTE    FSGetStatus(); //get current CARD status
void    CardReset(); //reset card
void    SetCardCs1Cs2Enable(void);
void    polling_card_plug(void);
void    CardDisable(void);

void    CardTestReady();
int     CARDIsPlugIn(); //check whether card is plugged in(1) or not(0)
void    CardSetBrowse();//make system to play card media 
void    polling_storage();

//kevinmonkey 050915 API functions
int FSFAT_Rewind(CARD_FILE* cfFile);
int FSFAT_SetFilePositionByLBA(CARD_FILE *cfFile, UINT32 uTargetLBAPosition);

#ifdef FSFAT_ENABLE_FRAGMENT_ANCHOR_TABLE
int FSFAT_BuildClusterAnchorTable(CARD_FILE* cfFile);
//kevinmonkey 050915 internal used function prototype
UINT32 FSFAT_CurrentAnchorTableType(CARD_FILE *cfFile);
int FSFAT_InvalidateFragmentCache(CARD_FILE *cfFile);
int FSFAT_CacheFragment(CARD_FILE *cfFile, UINT32 uLogicalCluster);
UINT32 FSFAT_CurrentAnchorTableType(CARD_FILE *cfFile);
int FSFAT_GetPhysicalClusterByLogicalCluster(const CARD_FILE *cfFile,UINT32 uTargetLogicalCluster,UINT32 *pResultCluster);
int FSFAT_GetPhysicalClusterByLBA(const CARD_FILE *cfFile,UINT32 uLBA,UINT32 *pResultCluster);
int FSFAT_GetNearestClusterAnchor(const CARD_FILE *cfFile, UINT32 uTargetLogicalCluster,
                                  UINT32 *pResultLogicalCluster,UINT32 *pResultPhysicalCluster);
#endif  //#ifdef FSFAT_ENABLE_FRAGMENT_ANCHOR_TABLE


// Memory space define
#ifdef IDE_CF_SW
#define     HD_FAT_CACHE_ADDR       SDRAM_BASE + ((HD_FAT_TABLE_YA)<<10)
#define     CF_FAT_CACHE_ADDR       SDRAM_BASE + (CF_FAT_TABLE_YA<<10)
#define     HD_FAT_INFO_ADDR        SDRAM_BASE_UNCACHED + CF_HDD_INFO_YA*1024
//#define     CF_FAT_INFO_ADDR        SDRAM_BASE_UNCACHED + CF_HDD_INFO_YA*1024+sizeof(cardP)
#else
#define     NORMAL_FAT_CACHE_YA     (A_JPEG_SERVO_YA+36)
#define     NORMAL_FAT_CACHE_ADDR   SDRAM_BASE + (NORMAL_FAT_CACHE_YA<<10)  
            //kevinmonkey 050629 to avoid overlapping with AVI internal subtitle, +36 is to avoid MS/SMC table.
            //originally at A_SUPYA, where AVI internal subtitle lies.
#endif


//----------------------------------------------------
// Fat write related,liweihua add 2004-12-10
//----------------------------------------------------
#ifdef SPHE8202_FAT_WRITE_API

// flag for creat file or dir fat table link 
#define	WRITE_FILE		1
#define	CREATE_DIR		2

// Memory space define
#define     FAT_WRITE_TEMP_ADDR     SDRAM_BASE_UNCACHED + FAT_WRITE_TEMP_YA*1024
#define     FAT_COPY_ADDR           SDRAM_BASE_UNCACHED + FAT_COPY_YA*1024


//function
int FSWriteSector(UINT32 lba,UINT32 nSec,UINT8 *buf);
BYTE FSWriteStream(CARD_FILE *cfFile, UINT32 nSec, BYTE *buf);
void FSJudgeFAT(void);
BYTE WriteSpeedControl(void);
UINT16 FSCreateFATLink(UINT32 nNum, BYTE sign);
int FSSearchDir(UINT32 lba, char *foldername);
int FSCreateDir(UINT32 lba, char *foldername);
void FSCopyData(UINT32 startClus, DIR_REC *CopyFileInfo);
int FSCopyFile(UINT32 lba, DIR_REC *CopyFileInfo);
int ReadFileFDB(BYTE *buf, DIR_REC *CopyFileInfo);
int CopyCDROMData(UINT32 msf, CARD_FILE *desFile, UINT32 len, BYTE *buf);
int CopyFATData(CARD_FILE *srcFile, CARD_FILE *desFile, UINT32 len, BYTE *buf);
int CopyMediaData(DIR_REC *CopyFileInfo, CARD_FILE *desFile, UINT32 len, BYTE *buf, UINT32 Block);
int FSDeleteData(DIR_REC *DeleteInfo);
void FSRenameFile(char *foldername, DIR_REC *OriFileInfo);
void FSFormat(void);
UINT16 FSEditFATLink(UINT32 nClus, UINT32 value);

// for SUPPORT_MP3_ENCODER ============================================================
// here are some USB/CARD WRITE API
#ifdef SUPPORT_MP3_ENCODER
int FSWriteSector_nonBlock(UINT32 lba,UINT32 nSec,UINT8 *buf);
int FSWriteSector_handler(pDOSWRITE_HANDLE handle);
#define FATBufferAddr			(SDRAM_BASE + 1024*MP3ENC_FAT_BUF_YA)//(SDRAM_BASE + 1024*REF0_LUMA)
#define FATupdateRecordAddr		(SDRAM_BASE + 1024*MP3ENC_UPDATE_REC_YA)//(FATBufferAddr + 1024 * 1024)

#define	updateSDRAMonly					1
#define	updateThisSectorToDevice			2
#define updateAllChangedSectorToDevice	3

UINT32 FSSearchInDir(UINT32 dirLBA, char *pFilename, BYTE *pTargetFDB);
UINT32 FSLoadFAT(UINT32 lba,UINT32 nSec,UINT8 *buf);
UINT32 FSCreateInDir(UINT32 dirLBA, char *pTargetname, BYTE *pTargetFDB, BYTE sign);
UINT32 FSUpdateFAT(UINT32 clusterIndex, UINT32 clusterValue, BYTE updateFlag);
UINT32 FSUpdateFDB(UINT32 dirLBA, BYTE *pTargetFDB);
UINT32 FSGetZeroClusterIndex(void);
#endif
//=====================================================================================
#endif//#ifdef SPHE8202_FAT_WRITE_API

#ifdef  SPHE8202_FAT_Write_Function //lijd 2005-1-5 18:11
#include "memmap0.h"
#include "fsNav.h"	
#define	PFUN_DEFAULT	0
#define	PFUN_WRITE		1
#define	PFUN_DELETE	    2
#define	PFUN_FORMAT	    3
#define	PFUN_RENAME	    4
#define	PFUN_COPYING	5
#define	P_SPACEFULL 	6
#define	P_SPACEEMPTY 	7
#define	P_UDISK_PROTECT	11   //lijd 2004-11-17 16:47
#define	P_UDISK_PLUGOUT	12   //lijd 2004-11-19 16:17
#define P_DIT_EXIST     13
#define	WRITE_FILE		1
#define	CREATE_DIR		2
void FSFormat(void);
void FSRenameFile(char *foldername);
int FSWriteData(UINT32 startClus,UINT16 copy_index);
int FSWriteFDB(UINT32 lba,UINT16 copy_index);
int FSDeleteData(void);
void FSJudgeFAT(void);
int FSCreateDir(UINT32 lba, char *foldername);
int FSSearchDir(UINT32 lba, char *foldername);
int CardWriteSector(UINT32 lba, UINT32 nSec, BYTE *buf);
BYTE FSWriteStream(CARD_FILE *cfFile, UINT32 nSec, BYTE *buf);
UINT16 FSCreateFATLink(UINT32 nNum, BYTE sign);
int ReadCDROMFile(BYTE *buf, UINT16 copy_index);
int  CopyDirCheckPolling(void);
int FSCopyDir2Storage(UINT32 lba);
void FSGUI_UpdataCopyFileName(void);
BYTE  FSInitiBat(BYTE StorageType);
int FSStorageCopy(UINT32 lba);
void GetAllFileNameFromCopyDir(void);
void GetOriginalFileMainName(int num);
int FSCheckExistsFile(UINT32 lba, UINT32 index, BYTE *pCDROMFileInfoBuf);
#endif//SPHE8202_FAT_Write_Function

/*
liweihua mark for USB/CARD/PMP use the same fat write API 2004-12-10
#if defined(CF_CARD_WRITE)||defined(SPHE8202_USB_Write)//||defined(WRITE_USB)//sunzhh 20041120
#include "memmap0.h"
#include "fsNav.h"	
#define	PFUN_DEFAULT	0
#define	PFUN_WRITE		1
#define	PFUN_DELETE	    2
#define	PFUN_FORMAT	    3
#define	PFUN_RENAME	    4
#define	PFUN_COPYING	5
#define	P_SPACEFULL 	6
#define	P_SPACEEMPTY 	7
#define	P_UDISK_PROTECT	11   //lijd 2004-11-17 16:47
#define	P_UDISK_PLUGOUT	12   //lijd 2004-11-19 16:17
#define P_DIT_EXIST     13
//void CardFormat(void);
//void CardRenameFile(char *foldername);
//int CardWriteData(UINT16 startClus);
void FSFormat(void);
void FSRenameFile(char *foldername);


#endif

#ifdef SPHE8202_CARD_WRITE//liweihua mod 2004-11-2 21:22
#define	WRITE_FILE		1
#define	CREATE_DIR		2
//void CardWriteData(UINT32 startClus,UINT16 copy_index);
	
//int CardWriteFDB(UINT32 lba,UINT16 copy_index);
//int CardDeleteData(UINT16 del_index);
//void CardJudgeFAT(void);
//int CardCreateDir(UINT32 lba,char *foldername);
//int CardSearchDir(UINT32 lba, char *foldername);
//int CardWriteSector(UINT32 lba, UINT32 nSec, BYTE *buf);
//BYTE CardWriteStream(CARD_FILE *cfFile, UINT32 nSec, BYTE *buf);
//UINT16 CardCreateFATLink(UINT32 nNum, BYTE sign);
void FSWriteData(UINT32 startClus,UINT16 copy_index);
	
int FSWriteFDB(UINT32 lba,UINT16 copy_index);
int FSDeleteData(UINT16 del_index);
void FSJudgeFAT(void);
int FSCreateDir(UINT32 lba,char *foldername);
int FSSearchDir(UINT32 lba, char *foldername);
int CardWriteSector(UINT32 lba, UINT32 nSec, BYTE *buf);
BYTE FSWriteStream(CARD_FILE *cfFile, UINT32 nSec, BYTE *buf);
UINT16 FSCreateFATLink(UINT32 nNum, BYTE sign);
int ReadCDROMFile(BYTE *buf, UINT16 copy_index);

#ifdef  IDE_CF_SW  //kenny add for CF and HDD siwtch
void IdeSetSequence(UINT8 );
UINT8 IdeGetSequence(void );
#endif

#elif defined(SPHE8202_USB_Write)
#define	WRITE_FILE		1//sunzhh
#define	CREATE_DIR		2//sunzhh

//void CardWriteData(UINT32 startClus);
//int CardWriteFDB(UINT32 lba);
//int CardDeleteData(void);
//void CardJudgeFAT(void);
//int CardCreateDir(char *foldername);
//int CardSearchDir(UINT32 lba, char *foldername);
//int CardWriteSector(UINT32 lba, UINT32 nSec, BYTE *buf);
//BYTE CardWriteStream(CARD_FILE *cfFile, UINT32 nSec, BYTE *buf);
//UINT16 CardCreateFATLink(UINT32 nNum, BYTE sign);
//void FSWriteData(UINT32 startClus);
int FSWriteData(UINT32 startClus,UINT16 copy_index);
int FSWriteFDB(UINT32 lba,UINT16 copy_index);
int FSDeleteData(void);
void FSJudgeFAT(void);
int FSCreateDir(UINT32 lba, char *foldername);
int FSSearchDir(UINT32 lba, char *foldername);
int CardWriteSector(UINT32 lba, UINT32 nSec, BYTE *buf);
BYTE FSWriteStream(CARD_FILE *cfFile, UINT32 nSec, BYTE *buf);
UINT16 FSCreateFATLink(UINT32 nNum, BYTE sign);
int ReadCDROMFile(BYTE *buf, UINT16 copy_index);
int  CopyDirCheckPolling(void);
int FSCopyDir2Storage(UINT32 lba);
void FSGUI_UpdataCopyFileName(void);
BYTE  FSInitiBat(BYTE StorageType);
int FSStorageCopy(UINT32 lba);
void GetAllFileNameFromCopyDir(void);
void GetOriginalFileMainName(int num);
int FSCheckExistsFile(UINT32 lba, UINT32 index, BYTE *pCDROMFileInfoBuf);
#endif

#endif//#if defined(CF_CARD_WRITE)||defined(SPHE8202_USB_Write)||defined(SPHE8202_CARD_WRITE)
*/
#endif //__CARDFS_H
