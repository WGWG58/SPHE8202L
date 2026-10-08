#ifndef __IRCODE_M_H
#define	__IRCODE_M_H

/*
** MTK 42 key
**
** TYPE:	PHILIPS
** ADDR:	0x001b
*/
#define _IRCODE_INC_V //kenny add it 891004
#define IR_PHILIPS //kenny add it 2001/1/15
#define IR_ADDR_PATT    0x001b
#include "irconfig.h"

//the following keys must be re-defined
#define IR_RETURN		0xf0
#define IR_EJECT		0xb8
#define IR_STOP			0x20
#define IR_POWER		0xff
#define IR_VOLUME_UP	0x98
#define IR_VOLUME_DOWN	0xf8


#endif/*__IRCODE_M_H*/
