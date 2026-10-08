#ifndef __IRCODE_M_H
#define	__IRCODE_M_H

/*
** MTK 42 key
**
** TYPE:	NEC
** ADDR:	0xff
*/


#define	_IRCODE_INC_V //shawn add at 910130 (samsung)
#define	IR_NEC
#define IR_ADDR_PATT	0x00ff
#include "irconfig.h"

//need to be modified
#define IR_RETURN       0xca
#define IR_EJECT        0x08
#define IR_STOP         0x28
#define IR_VOLUME_UP    0xc0
#define IR_VOLUME_DOWN  0x40


#endif/*__IRCODE_M_H*/
