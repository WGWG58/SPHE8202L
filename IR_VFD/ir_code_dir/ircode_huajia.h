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
#define IR_ADDR_PATT    0x00ff
#include "irconfig.h"

#define IR_RETURN       0x40
#define IR_EJECT        0xa0
#define IR_STOP         0x58
#define IR_VOLUME_UP    0xda
#define IR_VOLUME_DOWN  0x5a
#define IR_POWER	0xd2

#endif/*__IRCODE_M_H*/
