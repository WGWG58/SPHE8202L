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
|  File Name   :  ms.h
|
|  Description :  Memory Stick Interface
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/2/27        kenny         Creating
|--------------------------------------------------------------------------------*/

//Hardware return success,fail,timeout flag
#define HW_CMD_SUCCESS  0x00
#define HW_CMD_FAIL     0x01
#define HW_CMD_TIMEOUT  0x02
#define HW_INT_ERROR    0x04
#define HW_DTER_ERROR	0x05

//MS or MS-PRO Type define
#define MS_MEDIA	0x00
#define MS_PRO_MEDIA	0x08

//define Clock speed
#define MS_CLK_60M      0x00 // 121MHZ/2
#define MS_CLK_30M      0x01 // 121MHZ/4
#define MS_CLK_20M      0x02 // 121MHZ/6

//define MS error clear //for reg 0x0070 bit 4,5,6
#define RST_STATE_MACHINE  0x10
#define CLR_CRC_BUF        0x20
#define CLR_ERR_STATE      0x40

/* MemoryStick(Pro)	// TPC Code  Command	Sets */
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
/* MSPRO FLASH COMMAND for SET_CMD */
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

/* MS FLASH	for SET_CMD COMMAND	*/
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


/*Card Type*/
#define  MS_CARD_NOT_EXIST  0x05
#define  MS_TYPE            0x00/*standard MS card*/
#define  MS_PRO_TYPE_FAIL   0x07
#define  MS_PRO_TYPE        0x08


#if 0
#define	MSRWAdrLR	0x7f5a		// The starting offset of MS Data Registers to be used 
// for data transfer
#define	MSRWAdrHR	0x7f5b		// must be zero
#define	MSC01R		0x7f5c		// MS Config Register 01 bit0~1 SCLK Time Range
#define	MSC02R		0x7f5d		// MS Config Register 02 (MSDTxBCR+TPC)
#define	MSITOLR		0x7f5e		// MS Interrupt Time Out Register
#define	MSITOHR		0x7f5f
#define	MS1R		0x7f60		// MS control and status register
#define	MSTBRLR		0x7f61		// BUSY timeout low counter
#define	MSTBRHR		0x7f62		// BUSY timeout high counter
#define	MSDTxBCR	0x7f63		// TX byte count

#define	MSDT00R		0x7f64        // MS Data Register 0
#define	MSDT01R		0x7f65        // MS Data Register 1
#define	MSDT02R		0x7f66        // MS Data Register 2
#define	MSDT03R		0x7f67        // MS Data Register 3
#define	MSDT04R		0x7f68        // MS Data Register 4
#define	MSDT05R		0x7f69        // MS Data Register 5
#define	MSDT06R		0x7f6a        // MS Data Register 6
#define	MSDT07R		0x7f6b        // MS Data Register 7
#define	MSDT08R		0x7f6c        // MS Data Register 8
#define	MSDT09R		0x7f6d        // MS Data Register 9
#define	MSDT0AR		0x7f6e        // MS Data Register A
#define	MSDT0BR		0x7f6f        // MS Data Register B
#define	MSDT0CR		0x7f70        // MS Data Register C
#define	MSDT0DR		0x7f71        // MS Data Register D
#define	MSDT0ER		0x7f72        // MS Data Register E
#define	MSDT0FR		0x7f73        // MS Data Register F
                     
#define	MSDT10R		0x7f74        // MS Data Register 0
#define	MSDT11R		0x7f75        // MS Data Register 1
#define	MSDT12R		0x7f76        // MS Data Register 2
#define	MSDT13R		0x7f77        // MS Data Register 3
#define	MSDT14R		0x7f78        // MS Data Register 4
#define	MSDT15R		0x7f79        // MS Data Register 5
#define	MSDT16R		0x7f7a        // MS Data Register 6
#define	MSDT17R		0x7f7b        // MS Data Register 7
#define	MSDT18R		0x7f7c        // MS Data Register 8
#define	MSDT19R		0x7f7d        // MS Data Register 9
#define	MSDT1AR		0x7f7e        // MS Data Register A
#define	MSDT1BR		0x7f7f        // MS Data Register B
#define	MSDT1CR		0x7f80        // MS Data Register C
#define	MSDT1DR		0x7f81        // MS Data Register D
#define	MSDT1ER		0x7f82        // MS Data Register E
#define	MSDT1FR		0x7f83        // MS Data Register F

#define	PIO_EN		0x80		// for OR operation
#define DMA_EN		0x40		// for OR operation
#define REG_EN		0x3f		// for AND operation

#define CLK2		0x00		// clk/2, 24M
#define CLK3		0x01		// clk/3, 16M
#define CLK4		0x02		// clk/4, 12M
#define CLK8		0x03		// clk/8,  6M
#endif

//define MSC register mapping
//Status Registers
#define INT_R		0x01
#define STS_R0		0x02
#define STS_R1		0x03

//Parameter Registers
#define SYS_P		0x10
#define BLK_ADR_2   	0x11
#define BLK_ADR_1   	0x12
#define BLK_ADR_0	0x13
#define CMD_P		0x14


extern UINT32 msWaitPollingIdle(UINT32 );
extern UINT32 msWaitPollingCedInt(UINT32 );
extern UINT32 msProWaitPollingInt(UINT32 );
extern void hwMsInit(UINT32 );
extern UINT32 hwMsCmdSet(UINT32 );
extern UINT32 hwMsCrcRead();
extern UINT32 hwMsCrcStatus();
extern void hwMsErrClr(UINT32 );
extern void hwMsReset(void);
extern UINT32 hwMsIntGet(UINT32 *);
extern UINT32 hwMsRegRead(UINT8 , UINT8 *);
extern UINT32 hwMsRegWrite(UINT8 *,UINT32 );
extern UINT32 hwMsSetRwAddr(UINT8 ,UINT8 , UINT8 , UINT8 );
extern UINT32 hwMsStatusRead(UINT32 *);
extern UINT32 hwMsDmaWrite(UINT32 ,UINT32 , UINT32 ,UINT32 ,UINT32 ,UINT8  *,UINT32 ,UINT8  *);
extern UINT32 hwMsDmaRead(UINT32 ,UINT32 ,UINT32 ,UINT32 ,UINT32 ,UINT8  *,UINT32 ,UINT8  *,UINT32 );
extern UINT32 hwMsBlockErase(UINT32 ,UINT32 );
extern UINT32 hwMsReadAtrb(UINT32 ,	UINT32 ,UINT8  *);

