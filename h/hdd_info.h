/*=================================================================

hdd_info.h: Header for Some FileSystem Info Function for HDD

2002-04-28 10:00AM Created  by Verdure
2002-06-12 08:42AM Modified by cyue

Copyright(c)2000-2002 by Worldplus Technology (ShenZhen) Co., Ltd.
                   ALL RIGHTS RESERVED
=================================================================*/
#ifndef __HDD_INFO_H
#define __HDD_INFO_H

#define   HD_NO         0
#define   HD_IDLE       1
#define   HD_READ       2
#define   HD_WRITE      3

#define   PI_USE_MATRIX    1
#define   MAX_PART_INFO   10

/* these assume sizeof(short)==2 and sizeof(long)==4*/
#define	read_le16(X)	*(UINT16 *)(X)
#define	read_le32(X)	*(UINT32 *)(X)


// MBR test
typedef struct _partitionentry{
	UINT8 act,starthead;
	UINT16 startcs;
	UINT8 type,endhead;
	UINT16 endcs;
	UINT16 secfrommbr_lo,secfrommbr_hi;
	UINT16 seccnt_lo,seccnt_hi;
}PARTITION_ENTRY;


typedef struct _PARTITION_INFO{
	UINT32 startlba,seccnt;
	UINT8 type,act;
	struct _PARTITION_INFO *next;
}PARTITION_INFO;


typedef struct _HDD_INFO{
	UINT32 seccnt;
	UINT16 cyl;
	UINT8 sec,head;
#ifdef PI_USE_MATRIX
	PARTITION_INFO part[MAX_PART_INFO];
#else
	*partition_list;
#endif
}HDD_INFO;

/*
** FAT32 Boot Sector (BR32) located at sector 0 of a FAT32 volume
** (partition).
**
** FAT32 BSs are stored in 3 sectors -- 1536 bytes
*/
typedef struct _BPB_INFO{
	// Items in ExtBPB or by cyue
	UINT32	 Data_Area_Start; // Start LBA of Data Area 
	UINT32   FAT1_Start,FAT2_Start;
	UINT32 FATSize32;
    UINT32 RootClus;        //first cluster of root directory,usually 2
    UINT32 CurrDirClus;     //first cluster of current directory
	UINT32 curr_fdb_lba;
	UINT32 curr_fdb_offset;
	
	// Items in Current BPB
//  UINT32   HiddenSecCnt;   //offset from MBR to first Boot Sector
//  UINT32   TolSec32;       //must non-0 on FAT32,same as in partition table
    UINT16   BytesPerSec;    //usually 512
    UINT16   ReserSecCnt;    //typically 32 for FAT32
//  UINT16   RootEntries;    //must 0 on FAT32
//  UINT16   TolSec16;       //must 0 on FAT32
//  UINT16   FATSize16;      //must 0 on FAT32
//  UINT16   SecPerTrack;
//  UINT16   NumHeads;
    UINT8    NumFATs;        //number of FAT copies (usually 2)
    UINT8    SecPerClus;     //must be a power of 2
	UINT8    SecPerClusPwr;
    UINT8    BytesPerSecPwr;
//  UINT8    MediaDescriptor;//F8h for hard disks
}BPB_INFO;


#if 0 // cyue make BPB info  in the same structor 2002-06-14 08:37AM
typedef struct _FAT32_ExtBPB{
    UINT32   FATSize32;
    UINT16   ExtFlags;        //FAT mirroring flags
    UINT16   FSVersion;
    UINT32   RootClus;        //first cluster of root directory,usually 2
    UINT16   FSInfo;
    UINT16   BootSecBakupSec; //sector containing backup of boot sector
    UINT8    Reserved2[12];   //RESERVED,set 0
    UINT8    DriveNum;        //0x80 for hard disk,0x00 for floppy disk
    UINT8    Reserved3;       //-- RESERVED -- set this byte to 0
    UINT8    ExtBootSig;      //extended boot sector signature (29h)
    UINT32   VolumeID;
    UINT8    VolumeLabel [11];
    UINT8    FileSysType [8];     //"FAT32   "

}FAT32_ExtBPB;
extern FAT32_ExtBPB  ExtBPB;
#endif

typedef struct _FAT32_BOOT_SECTOR{
    /* SECTOR 1 OF 3 */
//    UINT8     OEMName[8];            //OEM Name and version ("MSWIN4.1")
    struct    _BPB_INFO  *BPB;
//    UINT16    Signature1;            //boot sector signature (AA55h)
    //UINT32   FirstSignature;     //always 41615252h
    //UINT32   FSInfoSignature;    //61417272h
    UINT32   FreeClusters;       //number of free clusters
    UINT32   NextCluster;        //next free cluster??
    //UINT16   Signature2;         //boot sector signature (AA55h)

}FAT32_BOOT_RECORD;
#define FAT_ATTR_R 0x01
#define FAT_ATTR_H 0x02
#define FAT_ATTR_S 0x04
#define FAT_ATTR_V 0x08
#define FAT_ATTR_D 0x010
#define FAT_ATTR_A 0x020
//Long Name ATTR:
#define FAT_ATTR_L (FAT_ATTR_R|FAT_ATTR_H|FAT_ATTR_S|FAT_ATTR_V)

#if 0
typedef struct _FAT32_FDB{
    UINT8   fname[8], fext[3];
    UINT8   attrib;
    UINT8   LNFcase;
    UINT8   creat_time_ms;  
    UINT16  creat_time;
    UINT16  creat_date;
    UINT16  access_date;
    UINT16  start_hi;
    UINT16  edit_time;
    UINT16  edit_date;
    UINT16  start_lo;
    UINT32  fsize;
    
}FAT32_FDB;
#else
typedef struct _FAT32_FDB{
    UINT8   fname[8], fext[3];
    UINT8   attrib;
    UINT8   unused[8];
    UINT16  start_hi;
    UINT16  edit_time;
    UINT16  edit_date;
    UINT16  start_lo;
    UINT32  fsize;
}FAT32_FDB;
#endif

typedef struct _FILE_INFO{
	UINT32 start_lba;
	UINT32 start_clus;
	UINT32 fsize;
	UINT32 fdb_lba,fdb_offset; // prepare to write info back
	//UINT8  name[12];
	UINT8  attrib;
	UINT8   l_time[4];  //jichuan_add 2003.4.21
	UINT16   time[2];   //jichuan_add 2003.4.15
#ifdef MIKEY_PTR
#else
	UINT32 read_ptr;
	UINT32 read_lba;
	UINT32 read_clus;
	UINT32 write_ptr;
	UINT32 write_lba;
	UINT32 write_clus;
	UINT32 f_need_new_clus;
#endif
}FILE_INFO;

typedef struct _file_link_item{
	UINT32 lba,len;
}FILE_LINK_ITEM;

#define MAX_FILE_LINK_ITEM 60
typedef struct _play_block{
	FILE_LINK_ITEM block[MAX_FILE_LINK_ITEM];
	UINT32 curr_blk,curr_lba;
}PLAY_BLOCK;

typedef struct  _Long_Name{        //jichuan_add  2002.10.10
	UINT16   name[50];
	UINT8   checksum;
}Long_Name;

#define LBA_COUNT(size) (((size)-1+BPB.BytesPerSec)>>BPB.BytesPerSecPwr)

#define FS_Clus2LBA(st) ((((st)-2)<<BPB.SecPerClusPwr)+BPB.Data_Area_Start)

extern UINT32  FS_Get_NextClus(UINT32 currClus);

extern UINT8  HD_EXIST;
#ifdef MIKEY
#define MAX_INFO_BUFF 512*64   //jichuan_modify   MAX_INFO_BUFF (512*2)   2002.9.29
extern UINT8  Info_buff[MAX_INFO_BUFF]; //reserved 4.5k?
#else
#define MAX_INFO_BUFF 512*64   //jichuan_modify   MAX_INFO_BUFF (512*2)   2002.9.29
extern UINT8  *Info_buff; //reserved 4.5k?
#endif
extern HDD_INFO HDD_Info;
extern BPB_INFO BPB;
//extern FAT32_FDB* FDB;


extern UINT32 Start_LBA;
extern UINT32 Data_Start_Clus;
extern UINT32 File_FDB_Lba;
extern UINT32 Data_Curr_Clus;
extern UINT32 Data_Next_Clus;
#endif/*__HDD_INFO_H*/
