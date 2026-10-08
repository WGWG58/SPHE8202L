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
#define IR_ADDR_PATT    0x00f3
#include "irconfig.h"

//need to be modified
#define IR_RETURN       0xd8
#define IR_EJECT        0x80
#define IR_STOP         0x58
#define IR_POWER        0xff
#define IR_VOLUME_UP    0xa0
#define IR_VOLUME_DOWN  0x90


#endif/*__IRCODE_M_H*/
