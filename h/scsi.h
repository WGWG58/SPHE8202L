////////////////////////////////////////////////////////////////////////////////
// SUNPLUS---WORLDPLUS
////////////////////////////////////////////////////////////////////////////////
// File:		scsi.h
// Purpose:	    SPHE8200 firmware to master SL811 Embedded Host. 
//              Contains SL811-related control firmware.This file
//              describes the scsi data structure!  
//              
// H/W Target:  SL811HST + SPHE8200 DVD SYSTEM
// IMPORTANT :  
//              the hardware could sustain USB host and USB slave. 
//
// Creator:     Liweihua and Zhaoyanhua 2003-9-20
////////////////////////////////////////////////////////////////////////////////
#ifndef   SCSI_H
#define   SCSI_H

#include "config.h"
#include "global.h"
#include "macro.h"
#include "regmap.h"
#include "emuio.h"
#include "Types.h"

//*****************************************************************************************
// Constant and data structue  Defines
//*****************************************************************************************
//----define the max sector number when send scci read/write command-----------
//liweihua 2004-5-28 15:47
#define SCSIREAD_MAX_SECTOR     0x10
#define SCSIWRITE_MAX_SECTOR    0x10

//----define the CBW constant----------------
#define CBWSignature        0x43425355
#define CBWOut              0x00
#define CBWIn               0x80
#define CBWSix              0x06
#define CBWTen              0x0A
#define CBWTwel             0x0C
#define CBWLen              0x1F

//----define the CSW constant----------------
#define CSWSignature    0x53425355
#define CSWLen          0x0D

//---- define SCSI-2 Commands ----------------
#define SCSICMD_TEST_UNIT_READY                 0x00
#define SCSICMD_REZERO_UNIT                     0x01
#define SCSICMD_REQUEST_SENSE                   0x03
#define SCSICMD_FORMAT_UNIT                     0x04
#define SCSICMD_READ_BLOCK_LIMITS               0x05

#define SCSICMD_REASSIGN_BLOCKS                 0x07
#define SCSICMD_READ_06                         0x08

#define SCSICMD_WRITE_06                        0x0a
#define SCSICMD_SEEK_06                         0x0b

#define SCSICMD_READ_REVERSE                    0x0f
#define SCSICMD_WRITE_FILEMARKS                 0x10
#define SCSICMD_SPACE                           0x11
#define SCSICMD_INQUIRY                         0x12
#define SCSICMD_VERIF06                         0x13
#define SCSICMD_RECOVER_BUFFERED_DATA           0x14
#define SCSICMD_MODE_SELECT_06                  0x15
#define SCSICMD_RESERVE                         0x16
#define SCSICMD_RELEASE                         0x17
#define SCSICMD_COPY                            0x18
#define SCSICMD_ERASE                           0x19
#define SCSICMD_MODE_SENSE_06                   0x1a
#define SCSICMD_START_STOP_UNIT                 0x1b
#define SCSICMD_RECEIVE_DIAGNOSTIC_RESULTS      0x1c
#define SCSICMD_SEND_DIAGNOSTIC                 0x1d
#define SCSICMD_PREVENT_ALLOW_MEDIUM_REMOVAL    0x1e

#define SCSICMD_READ_FORMAT_CAPACITIES          0x23
#define SCSICMD_SET_WINDOW                      0x24
#define SCSICMD_READ_CAPACITY                   0x25

#define SCSICMD_READ_10                         0x28
#define SCSICMD_READ_GENERATION                 0x29
#define SCSICMD_WRITE_10                        0x2a
#define SCSICMD_SEEK_10                         0x2b
#define SCSICMD_ERASE_10                        0x2c
#define SCSICMD_READ_UPDATED_BLOCK              0x2d
#define SCSICMD_WRITE_AND_VERIFY_10             0x2e
#define SCSICMD_VERIFY_10                       0x2f
#define SCSICMD_SEARCH_DATA_HIGH_10             0x30
#define SCSICMD_SEARCH_DATA_EQUAL_10            0x31
#define SCSICMD_SEARCH_DATA_LOW_10              0x32
#define SCSICMD_SET_LIMITS                      0x33
#define SCSICMD_PREFETCH                        0x34
#define SCSICMD_SYNCHRONIZE_CACHE               0x35
#define SCSICMD_LOCK_UNLOCK_CACHE               0x36
#define SCSICMD_READ_DEFECT_DATA_10             0x37
#define SCSICMD_MEDIUM_SCAN                     0x38
#define SCSICMD_COMPARE                         0x39
#define SCSICMD_COPAND_VERIFY                   0x3a
#define SCSICMD_WRITE_BUFFER                    0x3b
#define SCSICMD_READ_BUFFER                     0x3c
#define SCSICMD_UPDATE_BLOCK                    0x3d
#define SCSICMD_READ_LONG                       0x3e
#define SCSICMD_WRITE_LONG                      0x3f
#define SCSICMD_CHANGE_DEFINITION               0x40
#define SCSICMD_WRITE_SAME                      0x41
#define SCSICMD_READ_SUBCHANNEL                 0x42
#define SCSICMD_READ_TOC                        0x43
#define SCSICMD_READ_HEADER                     0x44
#define SCSICMD_PLAY_AUDIO_10                   0x45

#define SCSICMD_PLAY_AUDIO_MSF                  0x47
#define SCSICMD_PLAY_AUDIO_TRACK_INDEX          0x48
#define SCSICMD_PLAY_TRACK_RELATIVE             0x49

#define SCSICMD_PAUSE_RESUME                    0x4b
#define SCSICMD_LOG_SELECT                      0x4c
#define SCSICMD_LOG_SENSE                       0x4d
     
#define SCSICMD_MODE_SELECT_10                  0x55        
   
#define SCSICMD_MODE_SENSE_10                   0x5a        
   
#define SCSICMD_READ_12                         0xa8
#define SCSICMD_WRITE_12                        0xaa
//*****************************************************************************************
// data struct Type Definition
//*****************************************************************************************
//Standard CBW package
typedef struct
{
    UINT32 dCBWSignature;           //identify CBW
    UINT32 dCBWTag;                 //a command block tag ,echo with dCSWTag
	UINT32 dCBWDataTransferLength;  //expect to transfer data length 
	UINT8   bmCBWFlags;             //direction
	UINT8   bCBWLUN;                //the device logical unit number
	UINT8   bCBWCBLength;           //the valid length of CBWCB 
	UINT8   CBWCB[16];              //the command block
}sCBW,*pCBW;

//Standard CSW package
//define CSW status constant
#define CSWStatePhaseErr        0x02
#define CSWStateCommandFailed   0x01
#define CSWStateCommandGood     0x00
typedef struct
{ 
    UINT32 dCSWSignature;                  //identify CSW
    UINT32 dCSWTag;                            //echo dCBWTag
    UINT32 dCSWDataResidue;              //the remainder data length 
    UINT8   bCSWStatus;                       //indicate the success or failure of the command
}sCSW,*pCSW;

//---- SCSI-2 Commands ----------------
//6-byte Command
typedef struct 
{
    UINT8    operationCode;
    UINT8    serviceAction; 
    UINT16  logicalBlockAddress;
    UINT8    dataLength;
    UINT8    controlByte;
} SCSICMD_06BYTE, *PSCSICMD_06BYTE;

//10-byte Command
typedef struct 
{
    UINT8   operationCode;
    UINT8   serviceAction;
    UINT32 logicalBlockAddress;
    UINT8   reserved;
    UINT8   dataLength;
    UINT8   controlByte;
} SCSICMD_10BYTE, *PSCSICMD_10BYTE;

//12-byte Command
typedef struct 
{
    UINT8   operationCode;
    UINT8   serviceAction;
    UINT32 logicalBlockAddress;
    UINT32 dataLength;
    UINT8   reserved;
    UINT8   controlByte;
} SCSICMD_12BYTE, *PSCSICMD_12BYTE;

//16-byte Command
typedef struct 
{
    UINT8   operationCode;
    UINT8   serviceAction;
    UINT32 logicalBlockAddress;
    UINT32 addtionalCdbData;
    UINT32 dataLength;
    UINT8   reserved;
    UINT8   controlByte;
} SCSICMD_16BYTE, *PSCSICMD_16BYTE;

//----the returned data after  SCSI-2 Commands  ----------------
//Test UINT Ready
#define SCSIDATA_TEST_SIZE                      0x00
#define SCSICMD_TEST_CBWTag                     0x10300120
//INQUIRY
#define SCSIDATA_INQUIRY_SIZE                       0x24
#define SCSICMD_INQUIRY_CBWTag                      0x00000120
typedef struct 
{
      UINT8  peripheralDeviceType;//the bit0--bit5 represent the peripheral device type
      UINT8  RMB;                             //bit7 represent RBM
      UINT8  Version;                       //bit6-bit7 show ISOversion, bit3--bit5 show ECMA version,bit0--bit2 show ANSI version
      UINT8  responseDataFormat; //bit0--bit3 show response data format 
      UINT8  additionalLength; //0x1f                              
      UINT8  reserved0[3];
      UINT8  vendorInformation[8];
      UINT8  productIdentification[16];
      UINT8  productRevisionLevel[4];
} SCSIDATA_INQUIRY, *PSCSIDATA_INQUIRY;

//Read10
#define SCSICMD_READ10_CBWTag                     0x22000120
typedef struct
{
     UINT8  Read10OpCode;
     UINT8  Read10LUNDPRelAdr;//bit5--bit7:LUN,bit4:DP0,bit3:FUA,bit1--bit2:Reserved,bit0:RelAddr
     UINT32 Read10LBA;
     UINT8   Read10Reserved;
     UINT16  Read10BlockNum;
     UINT8   Read10Control;
}Read10Comm,*PRead10Comm;
//Write 10
#define  SCSICMD_WRITE10_CBWTag    0x22030120
//MODE SENSE 06
//MODE SELECT 06
//Mode Parameter Header
#define SCSIDATA_MODE_PARAMETER_HEADER_SIZE     0x08
#define SCSICMD_MODE_CBWTag                     0x00303120
typedef struct 
{
    UINT16  DataLength;
    UINT8    mediumTypeCode;
    UINT8    WPDPOFUA;//bit7 show WP,bit4 show DPOFUA,bit0--bir3 and bit5---bit6 is reserved
    UINT8    reserved[4];
} SCSIDATA_MODE_PARAMETER_HEADER, *PSCSIDATA_MODE_PARAMETER_HEADER;

//READ CAPACITY
#define SCSIDATA_READ_CAPACITY_SIZE                     0x08
#define SCSICMD_READ_CAPACITY_CBWTag                    0x40303120
typedef struct 
{
    UINT32  lastLogicalBlockAddress;
    UINT32  blockLengthInBytes;
} SCSIDATA_READ_CAPACITY, *PSCSIDATA_READ_CAPACITY;

//READ FORMAT CAPACITY
#define SCSIDATA_READ_FORMAT_CAPACITY_LIST_HEADER_SIZE          0x04
//SCSICMD_READ_FORMAT_CAPACITIES
#define SCSIDATA_READ_FORMAT_CAPACITIES_SIZE                    0xfc

#if defined(HOST_UHCI)  //wthsin 2005/6/6 03:16pm
 #define SCSIDATA_FORMAT_CAPACITIES_SIZE                         12
#elif  defined(USB_HOST_DRV)
  #define SCSIDATA_FORMAT_CAPACITIES_SIZE                         0 //Fix 8202D Ver C short packet bug
#endif

#define SCSICMD_READ_FORMAT_CAPACITIES_CBWTag                   0x02000120
typedef struct
{
    UINT8    reserved0;
    UINT8    reserved1;
    UINT8    reserved2;
    UINT8    capacityListLength;
} SCSIDATA_READ_CAPACITY_LIST_HEADER, *PSCSIDATA_READ_CAPACITY_LIST_HEADER;


#define SCSIDATA_READ_FORMAT_MAXIMUM_SIZE                       0x08
typedef struct 
{
    UINT32    numberOfBlocks;
    UINT8      descCode;             //bit0-bit1 represent the desciptor code 
    UINT8      blockLength[3];    
} SCSIDATA_READ_FORMAT_MAXIMUM, *PSCSIDATA_READ_FORMAT_MAXIMUM;

//Request Sense
#define SCSIDATA_REQUESTSENSE_SIZE                              0x12
#define SCSICMD_REQUESTSENSE_CBWTag                             0x02030120
typedef struct
{
    UINT8    VErrCode;//bit7---valid;bit0--6:Error Code
    UINT8    Reserved;
    UINT8    SenseKey;//bit0--bit3:Sense Key
    UINT32   Information;
    UINT8    AdditionalSenseLen;
    UINT8    Reserved1[4];
    UINT8    ASC;//Additional Sense Code(Mandatory)
    UINT8    ASCQ;//Additional Sense Code Qualifier(Mandatory)
    UINT8    Reserver2[4];
}SCSIDATA_REQUEST_SENSE,*pSCSIDATA_REQUEST_SENSE;

//system state
typedef struct
{
    UINT8 MainState;	// main state
    UINT8 SubState;	// upper nibble: sub-state; lower nibble: extension state
}STATE;

#if 1//def SUPPORT_MP3_ENCODER

enum SCSIWRITE_HANDLE_STATE
{
    WRITE_HANDLE_IDLE=0,
    WRITE_HANDLE_CMD,
    WRITE_HANDLE_CMD_ACK,
    WRITE_HANDLE_DATA,
    WRITE_HANDLE_ACK,
    WRITE_HANDLE_WAIT
 };

extern UINT8 Usb_WriteProtect; 
#endif
#if defined(FAT_Write_File_System)||defined(FILE_MODE_WRITE)  //added by wangwei,2004-11-15 13:23(get total capacity of storage).
extern UINT32 uiTotalCapacity;
#endif

//*****************************************************************************************
//micro function  define
//*****************************************************************************************
#define ChangeSysMainState(x) Sys.MainState = (x); Sys.SubState = 0x00
#define ChangeSysSubState(x)   Sys.SubState = x
enum USBSys_MAIN_STATE
{
    USBSys_Init_MainState=0x01,                 //execute SCSI command :test uint ready,inquiry,read capacity
    USBSys_GetFatInfo_MainState=0x02,     //get boot record,fat table,dir information
    USBSys_GetFileData_MainState=0x03,   //get the file data in the mass storage
    USBSys_ModifyFatInfo_MainState=0x04 //realize format,del,built new file and dir and so on
};

enum USBSys_Init_SubSTATE
{
    USB_Test_SubState=0x10,
    USB_Inquiry_SubState  =0x11, 
    USB_ReadFormatCapacities_SubState=0x12,
    USB_RequestSense_SubState=0x13,
    USB_Readcapcity_SubState=0x14
 };

enum  USBSys_GetFatInfo_SubSTATE
{
    USB_GetMBR_SubState=0x20,
    USB_BootRecord_SubState  =0x21, 
    USB_GetFatTable_SubState=0x22,
    USB_GetDir_SubState=0x23
 };

enum USBSys_GetFileData_SubSTATE
{
    USB_Directory_SubState=0x30,
    USB_FindFile_SubState=0x31,
    USB_RecieveFile_SubState  =0x32
 };
#define	USB_PRINTF printf  
/*request sense error code*/
#define   SCSI_NO_ERR               510    //sense key=0
#define   SCSI_RECOVERED_ERR        511    //sense key=1
#define   SCSI_NOT_READY_ERR        512    //sense key=2
#define   SCSI_NO_REF_POS_ERR       513
#define   SCSI_COMMUN_FAIL_ERR      514
#define   SCSI_MED_NOT_PRE_ERR      515
#define   SCSI_UNKNOWN_ERR          519
#define   SCSI_MEDIUM_ERR           520    //sense key=3
#define   SCSI_HARDWARE_ERR         521    //sense key=4
#define   SCSI_ILLEGAL_REQ_ERR      522    //sense key=5
#define   SCSI_UINT_ATTEN_ERR       523   //sense key=6
#define   SCSI_DATA_PROT_ERR        524   //sense key=7
#define   SCSI_ABORT_COMM_ERR       525   //sense key=0XBh
#define   SCSI_VOL_OVERF_ERR        526  ////sense key=0XDh

typedef 	INT32	(*FUNCTION_RECERR_FUNCTION)();
//*****************************************************************************************
// function  section
//*****************************************************************************************
UINT8 CSWInXfer(UINT8 usbaddr,UINT32 Tag);
UINT8 SCSICMD_Inquiry(UINT8 usbaddr);
UINT8 SCSICMD_TestUnitReady(UINT8 ,UINT8);
UINT8 SCSICMD_ReadCapcity(UINT8 usbaddr);
UINT8 SCSICMD_ReadFormatCapcity(UINT8 usbaddr);
INT32 SCSICMD_RequestSense(UINT8 usbaddr);
UINT32  UsbTestReady();
int SCSICMD_ReadSector(UINT32 ,UINT32 ,BYTE *);
//#ifdef SPHE8202_USB_WRITE//WRITE_USB
#if defined(SPHE8202_FAT_WRITE_API)||defined(SPHE8202_USB_WRITE)//lijd 2005-1-5 18:17
int SCSICMD_WriteSector(UINT32 lba,UINT32 nSec,BYTE *buf);
 int  SCSICMD_ModeSense(UINT8 usbaddr);
#endif //#define   SPHE8202_USB_Write//WRITE_USB
#endif //#define   SCSI_H
