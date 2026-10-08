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
 *  Author:         modify by wthsin ,040106                              *
 *                                                                        *
 **************************************************************************/
/*--------------------------------------------------------------------------
|  File Name   :  smc.h
|
|  Description :  SmartMedia Card Interface
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/3/3         wthsin         Creating
|--------------------------------------------------------------------------------*/  
#ifndef _SMC_H_
#define _SMC_H_

#define SMC_SUCCESS	  0
#define SMC_FAIL 	  1 

#define IS_ERASE      1
#define NOT_ERASE     0

#define NAND_TIMEOUT  0x02
#define NAND_READY    0x01 
#define MAND_DATA_RD  0x200
#define MAND_DATA_WR  0x100

#define SMC_BLK_STS_GOOD_ONES     6
#define NAND_BLK_STS_GOOD_ONES    8
#define SMC_DATA_STS_GOOD_ONES    4

#define IS_NAND_SMALL_BLKS        0
#define IS_NAND_UNKNOWN           1
#define IS_NAND_BIG_BLKS          2

#define SMC_DEV_ID_4M_1           0xe3
#define SMC_DEV_ID_4M_2           0xe5
#define SMC_DEV_ID_8M             0xe6
#define SMC_DEV_ID_16M            0x73
#define SMC_DEV_ID_32M            0x75
#define SMC_DEV_ID_64M            0x76
#define SMC_DEV_ID_128M           0x79
#define NAND_DEV_ID_128M_1        0xa1
#define NAND_DEV_ID_128M_2        0xf1
#define NAND_DEV_ID_256M_1        0xaa
#define NAND_DEV_ID_256M_2        0xda
#define NAND_DEV_ID_512M_1        0xac
#define NAND_DEV_ID_512M_2        0xdc
#define XD_DEV_ID_256M            0x71
#define XD_DEV_ID_512M            0xDC
#define XD_DEV_ID_1G              0xD3
#define XD_DEV_ID_2G              0xD5

#define LOG_BLOCK_NUM_PER_ZONE    1000
#define PHY_BLOCK_NUM_PER_ZONE    1024

const UINT8 CIS_Page[]={0x01, 0x03, 0xD9, 0x01, 0xFF, 0x18, 0x02, 0xDF, 0x01, 0x20}; //Card Information System
const UINT8 smcOnesLookupTable[16] = {
	          /* 0b00 0b01 0b10 0b11 */
	/* 0b00 */      0,   1,   1,   2,
	/* 0b01 */      1,   2,   2,   3,
	/* 0b10 */      1,   2,   2,   3,
	/* 0b11 */      2,   3,   3,   4
};

typedef struct   
{
	UINT8     makerId;
    UINT8     devId;
	UINT16    pageSize; 
	UINT8     pageBit;
	UINT32    blkSize;	 
	UINT8     nrBitPagesPerBlk;
	UINT32    nrBlks;	 
	UINT8     addrCycle;	 
	UINT8     eccCnt;	 
	UINT8     redundBytes;
	UINT8     isXD; 
} smcDev_t;

typedef struct 
{
	UINT8 reserved[4];
	UINT8 dataSts;
	UINT8 blkSts;
	UINT8 blkAddr1[2];
	UINT8 ecc2[3];
	UINT8 blkAddr2[2];
	UINT8 ecc1[3];
} redundArea_t;

//-------------------------------------------------------------------------------------------------
// Memory space define
//-------------------------------------------------------------------------------------------------
#define SMC_TABLE_ADDR                 (SDRAM_BASE_UNCACHED + (A_JPEG_SERVO_YA)*1024)   
#define SMC_TABLE_BUF_SIZE		    	0x00008000 	// 32k

#define SMC_ZONE_TABLE_ADDR            (SDRAM_BASE_UNCACHED + CARD_YA*1024)   
#define SMC_ZONE_TABLE_BUF_SIZE		   	0x00000800 	// 2k

#define SMC_BAD_BLOCK_TABLE_ADDR       (SMC_TABLE_ADDR + SMC_TABLE_BUF_SIZE)  
#define SMC_BAD_BLOCK_TABLE_BUF_SIZE	0x00000080 	// 128 Byte

#define SMC_SMALL_TABLE_ADDR           (SMC_BAD_BLOCK_TABLE_ADDR + SMC_BAD_BLOCK_TABLE_BUF_SIZE)  
#define SMC_SMALL_TABLE_BUF_SIZE		0x00000020 	// 16*2 Byte

#define SMC_REDUNDANT_BUF_POINTER	   (SMC_SMALL_TABLE_ADDR + SMC_SMALL_TABLE_BUF_SIZE)
#define SMC_REDUNDANT_BUF_SIZE		    0x00000010  // 16 byte


/**************************************************************************
 *                              M A C R O S                               *
 **************************************************************************/
#define hwNandPioReady()            while((regs0->ndData&0x100) != 0x100) 
#ifndef HDMI_SMC_CLE 
#define hwDisableNandInterface()    (regs0->ndCtrl[0] = 0x03) // CLE:0  ALE:0  /WP:1  /CE:1
#endif
#define HW_ECC_MODE_SET(mode)       (regs0->eccMode = mode)  
#define HW_ECC_CLEAR()              (regs0->eccReset = 0x01)  
/**************************************************************************
 *               F U N C T I O N    D E C L A R A T I O N S               *
 **************************************************************************/
extern void   hwNandTimeInit(UINT32  ,UINT32  ,UINT32 ,UINT32);
extern void   hwNandCmdSend(UINT8  );
extern UINT32 hwNandRdyCheck();
extern void   hwNandAddrSend(UINT8  ,UINT32  ,UINT32  );
extern void   hwNandIdRead();
extern UINT8  hwNandPortRead();
extern UINT32 smcDetect();
extern UINT32 smcLbaFieldCalc(UINT32);
extern UINT32 smcLbaCalc(UINT8 ,UINT8 );
extern UINT8  smcParityCheck(UINT8 ,UINT8);
extern void   smcRedundRead(UINT32 ,UINT8 *);
extern UINT32 smcDmaRead(UINT32 ,UINT32 ,UINT8 *);
extern UINT32 hwNandEccVerify(UINT8 *);
extern UINT32 smcPageCorrect(UINT8 *,UINT8 *,UINT8 *);
extern UINT32 smcBlkErase(UINT32);
extern UINT32 smcDmaWrite(UINT32 ,UINT32 ,UINT8 *,UINT32);
//extern void   smcMakeZoneTable(UINT8);
extern void   smcMakeTable();
extern void   hwNandEccFill();
extern UINT32 smcRead(UINT32,UINT32,UINT8 *);

#endif /* _SMC_H_ */

