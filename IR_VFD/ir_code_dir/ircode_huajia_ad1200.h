#ifndef __IRCODE_M_H
#define	__IRCODE_M_H

/*
** MTK 42 key
**
** TYPE:	NEC
** ADDR:	0xff
*/
#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT    0x20df
#include "irconfig.h"

#define IR_RETURN       0xa0
#define IR_EJECT        0xb0
#define IR_STOP         0xf8
#define IR_VOLUME_UP    0x10
#define IR_VOLUME_DOWN  0x50
#define IR_POWER	0x30

#endif/*__IRCODE_M_H*/
