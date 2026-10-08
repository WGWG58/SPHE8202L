#ifndef	__SPHE8200_H
#define	__SPHE8200_H

#include "set.h"
#include "user_init.h"

//
// 8200 versions
//
#define	SPHE8200A	0
#define SPHE8200_VER    SPHE8200A

//
// system configuration
// ATAPI/UDE/AVB/..
//
#define	DISC_SYSTEM_ATAPI	0
#define	DISC_SYSTEM_UDE		1
#define	DISC_SYSTEM_AVB		2
#define	DISC_SYSTEM_NONE	9

#define	DISC_SYSTEM	DISC_SYSTEM_ATAPI
//#define DISC_SYSTEM	DISC_SYSTEM_AVB     //  alan add 02-05-28

//
// system debug configuration
//
#define	DEBUG_SYSTEM_UART	0
#define	DEBUG_SYSTEM_EPP	1

#define	DEBUG_SYSTEM	        DEBUG_SYSTEM_UART

#define	CHIP_TVENC_721	        0
#define	CHIP_TVENC_711	        1
#define	CHIP_TVENC              CHIP_TVENC_721

#define	TVENC_MODE_MASTER	0
#define TVENC_MODE_656		1
#define	TVENC_MODE		TVENC_MODE_MASTER


//
// behavior control
//
#define	FF_DIS_PIC	8
#define	FB_DIS_PIC	1

#endif/*__SPHE8200_H*/

