#ifndef	__IRCODE_M_H
#define	__IRCODE_M_H

#undef _IRCODE_INC_V

/*
** MTK 42 key
**
** TYPE:	NEC
** ADDR:        0x866b
*/
#define	IR_NEC
#define IR_ADDR_PATT    0x866b
#include "irconfig.h"

//the following keys must be re-defined
#define IR_RETURN		0xf0
#define IR_EJECT		0xb8
#define IR_STOP			0x20
#define IR_POWER		0xff
#define IR_VOLUME_UP	0x98
#define IR_VOLUME_DOWN	0xf8


#endif/*__IRCODE_M_H*/
