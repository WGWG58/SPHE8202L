/***********************************************
 *
 * File Name : USBfs.h
 *
 * Description : 
 *      
 *      some FAT structure and function declaration
 *
 * Creator : zhaoyanhua 
 * Date    : 2003-9-24 11:19
 *
 ***********************************************/
#ifndef USBFS_H 
#define USBFS_H
 
#define USB_ADDR      0x02
#define MBR_SECTOR    0x00 //LBA-0:MBR(Master Boot Record)
#define FDB_SIZE      0x20 //File Description Block size

//for function USBGetFDB() return value
#define NO_EXTRA_FDB    0
#define READ_FDB_FAILED 1
//File System support
enum 
{
    USB_FAT_UNKNOWN=0,
    USB_FAT12=1,
    USB_FAT16=2,
    USB_FAT32=3,
};
//USB status
enum 
{
    USB_STATUS_NORMAL=0,
    USB_STATUS_NG=1,
};

//USB plug state //liweihua 2003-9-25 17:13
#define     USB_HAD_PLUGGED_IN   0x01  //Bit0 means USB had plug-in(bit0 =1) 
#define     USB_USER_DO_PLUG_IN       0x02  //Bit1 means user do plug-in action(bit1=1)
#define     USB_USER_DO_PLUG_OUT      0x04 //Bit2 means user do plug-out action


// 
typedef struct _USB_INFO {
    UINT32  sAddBootSec;    //boot sector start address(in LBA)
    UINT32  sAddFAT;        //FAT start address(in LBA)
    UINT32  sAddFDB;        //root FDB start address, FAT16 only(in LBA)
    UINT32  sAddData;       //data start address(in LBA)
    UINT16  bytePerSec;     //bytes/sector
    UINT16  secPerClus;     //sectors/Cluster
    UINT16  secPerFAT;      //sectors/FAT
    UINT16  nFDBinRoot;     //#FDB in root dir
    BYTE    nHeadMax;       //max head
    BYTE    nSecMax;        //max sector
    BYTE    typeFAT;        //FAT16/FAT32
    BYTE    nItemSizeFAT;   //2x item size in FAT(in Bytes)
} USB_INFO;
 
typedef struct _USB_FILE_ {
    UINT32  stLBA;          //start LBA
    UINT32  stClus;         //start Cluster
    UINT32  iFileSize;      //file size
    UINT32  curLBA;         //current LBA
    UINT32  curClus;        //current Cluster
    int     iLeaveSize;     //file leave size
    BYTE    status;
} USB_FILE; 
 
//Partition Table structure
typedef struct _USB_PARTITION_ 
{
    UINT8   ActiveStatus;
    UINT8   StartHead;
    UINT16  StartSectorCylinder;
    UINT8   OSType;//operate system type
    UINT8   EndHead;
    UINT16  EndSectorCylinder;
    UINT32  OppsitePositon;
    UINT32  SectorNum;
}USB_PARTITION, *pUSB_PARTITION;
//==============================================================  
//READ RELATED FUNCTIONS
//============================================================
int USBReadMBR(UINT8 usbaddr);
int USBReadBoot(UINT8 usbaddr);
UINT32 USBClus2LBA(UINT32 clus);
UINT32 USBLBA2Clus(UINT32 lba);
UINT32 USBGetRootDir(UINT8 usbaddr);
UINT32  USBGetNextLBA(UINT8 usbaddr,UINT32 lba);
UINT32 USBGetNextClus(UINT8 usbaddr, UINT32 clus);
UINT32 USBGetFDB(UINT8 usbaddr,UINT32 lba, UINT16 index, BYTE *buf);
UINT32 USBFAT12NextClus(UINT8 usbaddr, UINT32 clus);
BYTE USBReadStream(USB_FILE *UFile, UINT32 nSec, BYTE *buf);
void USBTestReady();
BYTE ReadCDROMFile(BYTE *buf);
BYTE USBFileSeek(USB_FILE *UFile, int nSec);
BYTE USBGetStatus();
int USBIsPlugIn();

//==============================================================
//WRITE RELATED FUNCTIONS
//============================================================== 
#ifdef SPHE8202_USB_Write//WRITE_USB 
BYTE USBWriteStream(USB_FILE *UFile, UINT32 nSec, BYTE *buf);
UINT16 USBCreateFATLink(UINT32 nNum, BYTE sign);
void USBWriteData(UINT16 startClus);
int USBWriteFDB(UINT32 lba);
UINT32 USBSearchDir(UINT32 lba, char *foldername);
void USBRenameFile(char *foldername);
UINT32 USBNewFolder(char *foldername);
int USBSchedule(BYTE copymod);
void USBJudgeFAT(void);
void USBFormat(void);
int USBDeleteData(void);
UINT16 USBCreateDir(void);
#endif //end SPHE8202_USB_Write//WRITE_USB
#endif //end USBFS_H
 