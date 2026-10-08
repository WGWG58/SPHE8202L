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
 **************************************************************************/
/*--------------------------------------------------------------------------
|  File Name   :  sd.c
|
|  Description :  SD and MMC Interface
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/2/9        wthsin         Creating
|--------------------------------------------------------------------------------*/
#ifndef _HWSD_H_
#define _HWSD_H_

#define SD_SUCCESS					0
#define SD_FAIL 					1

#define SD_MODE      0
#define MMC_MODE     1

#define SD_1BIT_MODE 0
#define SD_4BIT_MODE 1

//define clk=108MHz
#define SD_18MHz     2
#define SD_16MHz     3
#define SD_11MHz     4 
#define SD_6MHz      8 
#define SD_375KHz    143

#define RSP_TYPE_R1  0
#define RSP_TYPE_R2  1
#define RSP_TYPE_R3  2
#define RSP_TYPE_R6  3

#define SD_STATE_IDLE    0
#define SD_STATE_READY   1
#define SD_STATE_IDENT   2
#define SD_STATE_STBY    3
#define SD_STATE_TRAN    4
#define SD_STATE_DATA    5
#define SD_STATE_RCV     6
#define SD_STATE_PRG     7
#define SD_STATE_DIS     8
#define SD_STATE_TIMEOUT 9


#define  SD_RSP_TIMEOUT     0x02

#define hwSdCardCrcState()   ( ( (regs0->sdStatus1 & 0xf0) >>4) == 0x02) 
#define hwSdDat0Check()      ( (regs0->sdStatus0&0x20)>>5 )
#define hwSdRxCRC()          (regs0->sdCtrl=0x10)
#define hwSdTimeOut()        ( (regs0->sdStatus0 & 0xC0) >> 6 )

 
/**************************************************************************
 *                          D A T A    T Y P E S                          *
 **************************************************************************/
typedef struct   
{
	UINT32    rca32bit;
	UINT8     sdOCR[4]; 
	UINT8     sdRCA[2]; 
	UINT8     sdCID[16];
	UINT8     sdCSD[16];
	UINT32    nrSects;
	UINT32    notSd;
} sdDev_t;

enum SD_HANDLE_STATE
{
    SD_WRITE_HANDLE_IDLE=0,
    SD_WAIT_TRAN_STATE0,
    SD_SEND_WRITE_CMD,
    SD_WRITE_DATA,
    SD_SEND_END_CMD,
	SD_WAIT_TRAN_STATE1,
    SD_WAIT_READY,
 };
/**************************************************************************
 *               F U N C T I O N    D E C L A R A T I O N S               *
 **************************************************************************/
 
extern void   hwSdInit(UINT32);
extern void   hwSdConfig(UINT32  ,UINT32  ,UINT32  );
extern void   hwSdBlockSizeSet(UINT32);
extern UINT32 hwSdRxResponse(UINT8 *, UINT32);
extern void   hwSdTxDummy();
extern UINT32 hwSdCmdSend(UINT32, UINT32, UINT32, UINT8 *);
extern UINT32 sdIdentify(UINT32, UINT32);
extern UINT32 sdStateCheck();
extern UINT32 sdBusModeSet(UINT32, UINT32, UINT32);
extern UINT32 hwSdIdleWait(void);
extern UINT32 sdStateGet();
extern UINT32 sdTranStateWait();
extern UINT32 sdReadyBitWait(); 
extern UINT32 sdDetect(void);
extern UINT32 sdRead( UINT32, UINT32, UINT8 *);
//extern UINT32 sdWrite(UINT32, UINT32, UINT8 *);

#if 1//def SUPPORT_MP3_ENCODER
extern int sdWrite_Handler(pDOSWRITE_HANDLE handle);
#endif
#endif   //_HWSD_H_




