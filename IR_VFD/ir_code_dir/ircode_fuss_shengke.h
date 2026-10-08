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
#define IR_ADDR_PATT    0x00ff//xiaosan for new IR 2-7-1 21:40
#include "irconfig.h"

//need to be modified
#define IR_RETURN       0x60
#define IR_EJECT        0x68
#define IR_STOP         0x70
#define IR_POWER        0xff
#define IR_VOLUME_UP    0xe0
#define IR_VOLUME_DOWN  0x20


#endif/*__IRCODE_M_H*/
