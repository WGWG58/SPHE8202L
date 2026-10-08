/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 *                                                                        *
 *  Author:                                                     *
 *                                                                        *
 **************************************************************************/
#define	MS_DEBUG
#ifdef	__MS_COMMON__
#define	EXTERN
#else
#define	EXTERN	extern
#endif

#include "cardfs.h"   //kevinmonkey050715 for NORMAL_FAT_CACHE_YA

//#define FAIL            1
//#define SUCCESS         0
#define	YES             1

#define	MEMORY_STICK_STD

//#define	MS_CARD_OK		1
#define	MS_CMD_OK		0
#define	MS_CMD_FAIL		1
#define	MS_CMD_TIMEOUT	2
#define	MS_INT_ERROR	3
#define	MS_CARD_ERROR	0xFF
#define	MS_CARD_WP		4
#define MS_DTER_ERROR  5

#define	MS_WP			0x80000000
#define	MS_WIDE_BUS		0x40000000
#define	MS_NORMAL		0x00000000
#define	MS_HIGH_SPEED	0x00010080
#define	MS_PRO			0x00010000

/* Memory Stick	(Pro) :	Type List */
/* b31=WP, b27=WIDE_BUS	*/
/* MemoryStick,	Low	Speed */
#define	MS_N		(0x00000000)		/* T=00/FF,	C=00/FF, C=00/FF */
#define	MS_N_ROM	(0x00000001+MS_WP)	/* T=00/FF,	C=00/FF, C=01 */
#define	MS_N_R		(0x00000002+MS_WP)	/* T=00/FF,	C=00/FF, C=02 */
#define	MS_N_OTHER	(0x00000003+MS_WP)	/* T=00/FF,	C=00/FF, C=03 */
/* MemoryStick,	High Speed */
#define	MS_H		(0x00010080+MS_WP)	/* T=01, C=00, C=80	*/
#define	MS_H_ROM	(0x00010081+MS_WP)	/* T=01, C=00, C=81	*/
#define	MS_H_R		(0x00010082+MS_WP)	/* T=01, C=00, C=82	*/
#define	MS_H_OTHER	(0x00010083+MS_WP)	/* T=01, C=00, C=83	*/
/* MemoryStick Pro */
#define	MS_P		(0x00010000)		/* T=01, C=00, C=00	*/
#define	MS_P_ROM	(0x00010001+MS_WP)	/* T=01, C=00, C=01	*/
#define	MS_P_R		(0x00010002+MS_WP)	/* T=01, C=00, C=02	*/
#define	MS_P_OTHER	(0x00010003+MS_WP)	/* T=01, C=00, C=03	*/

/* MemoryStick(Pro)	Command	Sets */
#define	READ_LONG_DATA		0x02
#define	READ_SHORT_DATA		0x03
#define	READ_REG			0x04
#define	GET_INT				0x07
#define	SET_RW_REG_ADRS		0x08
#define	EX_SET_CMD			0x09
#define	WRITE_REG			0x0B
#define	WRITE_SHORT_DATA	0x0C
#define	WRITE_LONG_DATA		0x0D
#define	SET_CMD				0x0E
/* MSPRO FLASH COMMAND */
#define	MSPRO_READ_DATA		0x20
#define	MSPRO_WRITE_DATA	0x21
#define	MSPRO_READ_INFO		0x22
#define	MSPRO_WRITE_INFO	0x23
#define	MSPRO_READ_ATRB		0x24
#define	MSPRO_STOP			0x25
#define	MSPRO_ERASE			0x26
#define	MSPRO_CHG_CLASS		0x27
#define	MSPRO_FORMAT		0x10
#define	MSPRO_SLEEP			0x11

/* MS FLASH	COMMAND	*/
#define	MS_READ_DATA	 0x20
#define	MS_WRITE_DATA	 0x21
#define	MS_READ_INFO	 0x22
#define	MS_WRITE_INFO	 0x23
#define	MS_STOP			 0x25
#define	MS_ERASE		 0x26
#define	MS_CHG_CLASS	 0x27
#define	MS_FORMAT		 0x10

#define	MS_BLOCK_READ	0xAA
#define	MS_BLOCK_WRITE	0x55
#define	MS_BLOCK_END	0x33
#define	MS_BLOCK_ERASE	0x99
#define	MS_FLASH_STOP	0xCC
#define	MS_SLEEP		0x5A
#define	MS_CLEAR_BUF	0xC3
#define	MS_RESET		0x3C

/* MemoryStick(Pro)	Register List */
/* read	only */
#define	REG_INT			0x01	/* interrupt factors */
#define	REG_STATUS		0x02	/* status of the system	*/
#define	REG_STATUS2		0x03	/* cmd execution status	*/
#define	REG_TYPE		0x04	/* media type */
#define	REG_CATEGORY	0x06	/* media categoary */
#define	REG_CLASS		0x07	/* media class */

/*Standard Memory Stick card*/
#define MS_BLK_AVG      0
#define MS_DEV_ID_4M    0x00000004//0x408
#define MS_DEV_ID_8M    0x00000008//0x808
#define MS_DEV_ID_16M   0x00000106 //0x1616
#define MS_DEV_ID_32M   0x00000302//0x3216
#define MS_DEV_ID_64M   0x00000604//0x6416
#define MS_DEV_ID_128M  0x00010208//0x2816  
#define MS_DEV_ID_256M	0x00020506//0x0256
#define MS_DEV_ID_512M	0x00050102//0x0512
#define MS_DEV_ID_1G	0x01000204//0x1024	
#define MS_BOOT_BlOCK   0
#define MS_CIS_PAGE    	2
#define MS_IDI_OFFSET   256 + 54

#define MS_DEV_CAP_4M    0x00001EE0 
#define MS_DEV_CAP_8M    0x00003DE0 
#define MS_DEV_CAP_16M   0x00007BC0  
#define MS_DEV_CAP_32M   0x0000F7C0 
#define MS_DEV_CAP_64M   0x0001EF80 
#define MS_DEV_CAP_128M  0x0003DF00 

#define MS_LOG_BLKS_FRIST_ZONE 494
#define MS_MAX_LOG_BLKS_PER_ZONE 496
#define MS_MAX_PHY_BLKS_PER_ZONE 512
#if 0 /* 0625 */
#define MS_MAX_LOG_BLKS          8000 //for 128M
#else
#define MS_MAX_LOG_BLKS          16000//for 256M
#define MS_MAX_DISABLE_BLKS      1024//1600
#endif
#define MS_MAX_LOG_ZONE          (MS_MAX_LOG_BLKS / MS_MAX_LOG_BLKS_PER_ZONE)
#if 0 /* 0625 */
#define MS_MAX_PHY_BLKS          8192
#else
#define MS_MAX_PHY_BLKS          16384
#endif
#define MS_BLK_STS_GOOD_ONES     6
#define MS_DATA_STS_GOOD_ONES    4


//define ms clock sysclk/(2*(1+n))
#define	MS_18MHZ	0x02
#define MS_13p5MHZ  0x03 
#define MS_10p8MHZ	0x04
#define MS_9MHZ		0x05
#define MS_7p7MHZ	0x06
//#define MS_9MHZ		0x07
#define MS_6p75MHZ	0x08
#define MS_6MHZ		0x09


//macro
#define READ8(_reg_)            (*((volatile UINT8  *)(_reg_)))
#define READ16(_reg_)           (*((volatile UINT16 *)(_reg_)))
#define READ32(_reg_)           (*((volatile UINT32 *)(_reg_)))

#define WRITE8(_reg_, _value_)  (*((volatile UINT8  *)(_reg_)) = (_value_))
#define WRITE16(_reg_, _value_) (*((volatile UINT16 *)(_reg_)) = (_value_))
#define WRITE32(_reg_, _value_) (*((volatile UINT32 *)(_reg_)) = (_value_))



//address definition   zhongshan modify for ms write 04/12/11
#define MsAllocTableAdr                 (SDRAM_BASE_UNCACHED + (A_JPEG_SERVO_YA)*1024)  //(SDRAM_BASE_UNCACHED + CARD_YA*1024)   
#define MsAllocTableAdrSize 	    	0x00008000//0x00000800 	// 2K

#define MsextraDataAreaAdr	            (MsAllocTableAdr + MsAllocTableAdrSize)
#define MsextraDataAreaSize             0x00000048 //72 bytes

#define MsDataBufAdr	                (MsextraDataAreaAdr + MsextraDataAreaSize)
#define MsDataBufAdrSIZE                0x00000200 //512 bytes

#define MsBadBlkAdr	                    (MsDataBufAdr + MsDataBufAdrSIZE)
#define MsBadBlkAdrSize                 0x00000080 //128 bytes

#define MsWriteTableAdr      (SDRAM_BASE_UNCACHED + (CARD_YA)*1024) 
#define MsWriteTableAdrSize		0x00000800// 992bytes*2

#define msFreePhyAdr                   (MsWriteTableAdr+MsWriteTableAdrSize)
#define msFreePhyAdrSize		 0x00000080//128bytes

#define MsAllocTableLogBlkSize			(MsAllocTableAdrSize/2)
#define MsWriteTableLogBlkSize			(MsWriteTableAdrSize/2)

#define MsDataTempBuf					(msFreePhyAdr +msFreePhyAdrSize)
#define MsDataTempBufSize				0x00000200//512 bytes

#define mspStart							(MsDataTempBuf +MsDataTempBufSize)

/**************************************************************************
 *                          D A T A    T Y P E S                          *
 **************************************************************************/
 
 typedef struct list_s{
	struct list_s *pprev; /* previous entry or que's head */
	struct list_s *pnext; /* previous entry or que's tail */
} list_t;
 
 typedef struct {
	UINT8  makerId;
	UINT8  hwDevId;
	UINT8  active;      /* Inserted: 1, pulled-out: 0           */
	UINT16 megaByte;    /* Device capacity in unit of MB        */
	UINT8* pdevName;    /* ASCII name of this device            */
	UINT32 nrSects;     /* How many sectors of this device      */
	UINT32 nrFreeBytes; /* Free space in byte                   */
	UINT32 fsDepend;    /* For FAT, fsDepend = byte per cluster */ 
} devInfo_t;



//typedef struct msDev_s {
typedef struct  {
	//devInfo_t common; /* Common information for all cards */
	UINT16    megaByte;    /* Device capacity in unit of MB        */
	UINT32    nrSects;     /* How many sectors of this device      */
	UINT16    nrGoodOnes;
	UINT16    pageSize;
	UINT16    blkSize;
	UINT8     pageBit;
	UINT8     nrBitPagesPerBlk;
	UINT16    nrBlks;
	UINT8     addrCycle;
	UINT8     eccCnt;
	UINT8     extraDataBytes;
	UINT16*   pallocTable;
	UINT16*   pwriteTable;
	//UINT16*   pbadBlk;
	UINT8*    pbadBlk;
	#if 0
	UINT32*   pbitTable;
	#else
	//list_t    freeList[MS_MAX_LOG_ZONE];
	//list_t*   pfreeBlkBuf;
	#endif
	UINT8*    pbuf;
	UINT8*    ptemp;
	UINT8*    predund;
	UINT16*   pfreeBlk;
	UINT16*  pstart;
	UINT32    BootBlk0;
	UINT32    BootBlk1;
	UINT32    writeProtect;
	UINT32    cardType;
	
} msDev_t;	

	
typedef struct {
	UINT8 overwriteflag;
	UINT8 managementflag;
	UINT8 blkAddr[2];
	UINT8 formatreserve[5];
} extraDataArea_t;



 

/**************************************************************************
 *               G L O B A L       D E C L A R A T I O N S                *
 **************************************************************************/
msDev_t msDev;
//extraDataArea_t extraDataArea_t;

//extern	flashReg_t *pflashReg;
//extern	UINT32	msCardType;
//extern	UINT32	msBlockSize, msBlock;
//extern	dispReg_t *pdispReg;
/**************************************************************************
 *               F U N C T I O N    D E C L A R A T I O N S               *
 **************************************************************************/
 
extern UINT32 msIdentify(UINT32);
extern UINT32 msDetect(void);
extern UINT32 msStateCheck();
//UINT32 msBusModeSet(UINT32, UINT32, UINT32);
//UINT32 msStateGet(msDev_t *);
//UINT32 msRead(void *, UINT32, UINT32, UINT8 *);
extern UINT32 msRead(UINT32, UINT32, UINT8 *);
//UINT32 msWrite(void *, UINT32, UINT32, UINT8 *);
//UINT32 msFormat(void *, UINT32);
//UINT32 msProFormat(void *, UINT32);
//UINT32 msTypeDetect(void);
//UINT32 msSendCmd(UINT32 cmd);
//UINT32 msBlockErase(UINT32	block);
//UINT32 msCheckInt(UINT32 mask, UINT32 timeout);
extern void msBufInit(msDev_t *);
//void msLibVersionGet(UINT8 *pbuf);
extern void hwMsReset(void);
extern UINT32 msCardTypeMS(msDev_t *);
extern UINT32 msCardTypeMSPRO(msDev_t *);
//void msFmgpioSetLow(void);

extern UINT32 msTableMake(UINT32 );
extern UINT32 msWriteTableMake(UINT32 );
extern void msTableWrite(UINT32,UINT32);
extern UINT32 msLbaCalc(UINT8, UINT8);
//UINT8 msParityCheck(UINT8, UINT8);
UINT32 msLpaToPpaRead(UINT32);
UINT32 msLpaToPpaWrite(UINT32 );
//extern void msBadBlkMark(UINT32 ,UINT32);
//extern UINT32 msPageRead(extraDataArea_t *,UINT32 ,UINT32 ,UINT32 ,UINT8 *,UINT32);
extern UINT32 msPageRead(UINT32 ,UINT32 ,UINT32 ,UINT8 *,UINT32);
//UINT32 msPageWrite(	extraDataArea_t *,UINT32 ,UINT32 ,UINT32 ,UINT8 *,	UINT32);
extern UINT32 msPageWrite(	UINT32 ,UINT32 ,UINT32 ,UINT8 *,	UINT32);
extern UINT32 msFreePhyBlkSearch(UINT32 );
extern void msFreePhyBlkMark(UINT32 );
//UINT32 msTest(UINT8* param);
extern UINT32 msExtarDataRead(UINT32, UINT32);
//UINT32 msExtarDataWrite(msDev_t *, UINT32, UINT32, extraDataArea_t *,UINT32);
//UINT32 msWriteProtectInfoGet(void);
//UINT32 msBootRescue(void);
//void msBootInfoSet(UINT32,UINT8 *,UINT8 *);
extern UINT32 msProDeviceInfoConfirm(UINT8 *);
extern void msFlashModePreSet(UINT8 flashMode);
extern void msFlashModePostSet(UINT8 flashMode);
//UINT32 msWaitPolling(UINT32 *);



//void debugDisplaymatrix(UINT32,UINT32,UINT32,UINT32 ,UINT8 *);/*debug use*/

