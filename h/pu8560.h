#ifndef	__PU8560_H
#define	__PU8560_H

#include "set.h"
#include "user_init.h"

//
// 720 version
//
//#define	SPCA720A	0
//#define	SPCA720B	1
//#define	SPCA720C	2
//#define	SPCA720D	3


//#ifdef  DVD_2_0 
//#define SDRAM_32MB //2 pcs 1X16 Mb SDRAM
//#elif defined(DVD_2_4)
//#define SDRAM_32MB
//#else
//#define SDRAM_64MB //1 pcs 4X16 Mb SDRAM
//#endif

//#define	SPCA720_VER	SPCA720D

//
// system configuration
// ATAPI/UDE/AVB/..
//
#define	DISC_SYSTEM_ATAPI	0
#define	DISC_SYSTEM_UDE		1
#define	DISC_SYSTEM_AVB		2
#define	DISC_SYSTEM_NONE	9

#define	DISC_SYSTEM	DISC_SYSTEM_ATAPI
//#define	DISC_SYSTEM	DISC_SYSTEM_AVB     //  alan add 02-05-28

//
// system debug configuration
//
#define	DEBUG_SYSTEM_UART	0
#define	DEBUG_SYSTEM_EPP	1

//#define	DEBUG_SYSTEM	DEBUG_SYSTEM_UART

#define	CHIP_TVENC_721		0
#define	CHIP_TVENC_711		1
#define	CHIP_TVENC	CHIP_TVENC_721

#define	TVENC_MODE_MASTER	0
#define TVENC_MODE_656		1
#define	TVENC_MODE		TVENC_MODE_MASTER

//
// behavior control
//
#define	FF_DIS_PIC	8
#define	FB_DIS_PIC	1


#endif/*__PU8560_H*/

