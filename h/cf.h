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
|  File Name   :  cf.c
|
|  Description :  CF Interface
|
|  Version    :  0.1  
| 
| 
|  Rev  Date            Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1  2004/2/9        wthsin         Creating
|--------------------------------------------------------------------------------*/  
#ifndef _CF_H_
#define _CF_H_

/**************************************************************************
 *                           C O N S T A N T S                            *
 **************************************************************************/
#define CF_SUCCESS                  0
#define CF_FAIL                     1 
 
#define  CF_NOT_EXIST   0x00
#define  CF_EXIST       0x01

#define  CF_IRQ_LOW     0x00
#define  CF_IRQ_HIGH    0x01

#define  CF_MEM_MODE    0x00
#define  CF_IDE_MODE    0x01

/* CF status register (offset 7 & eh) */
#define CF_STATUS_BUSY (1 << 7)
#define CF_STATUS_RDY  (1 << 6)
#define CF_STATUS_DWF  (1 << 5)
#define CF_STATUS_DSC  (1 << 4)
#define CF_STATUS_DRQ  (1 << 3)
#define CF_STATUS_CORR (1 << 2)
#define CF_STATUS_ERR  (1 << 0)

#define CF_RW_ERROR  0x01
#define CF_DRQ_ERROR 0x02

/**************************************************************************
 *                          D A T A    T Y P E S                          *
 **************************************************************************/
typedef struct   
{
    UINT32    nrSects;   
} cfDev_t;
/**************************************************************************
 *                              M A C R O S                               *
 **************************************************************************/
#define hwCfRdyCheck() (regs0->cfCtrl&0x01)  //reg: 0x0031  /* 0/1: busy/ready */

/**************************************************************************
 *               F U N C T I O N    D E C L A R A T I O N S               *
 **************************************************************************/
void   hwCfInit(UINT32, UINT32, UINT32,UINT32,UINT32);
void   hwCfReset(UINT32);
void   hwCfCsASet(UINT32);
void   hwCfWordCsaWriteSet(UINT32, UINT32);
UINT16   hwCfWordCsaReadSet(UINT32);
UINT32 cfIdeDetect();
UINT32 cfIdentify();
extern UINT32 cfRead(UINT32 ,UINT32 ,UINT8 *);
extern UINT32 cfWrite(UINT32 ,UINT32 ,UINT8 *);
#ifdef  IDE_CF_SW  //liulifeng add for read HD and CF
extern void cfSetDevHead(UINT8 );
//extern void hwCfCardStandby(UINT8 );//kenny 2005/5/12 unmark
void cfDevSetFeature(UINT32 );
#endif
#endif /* _CF_H_ */

