#ifndef __IRCODE_SAM_H
#define	__IRCODE_SAM_H

#define	_IRCODE_INC_V //shawn add at 910130 (samsung)
#define	IR_NEC
#define IR_ADDR_PATT	0x14EB
#include "irconfig.h"

//need to be modified
#define IR_RETURN		0xf0
#define IR_EJECT		0xb8
#define IR_STOP			0x20
#define IR_POWER        0xff    //Jeff 20020524
#define IR_VOLUME_UP	0x98
#define IR_VOLUME_DOWN	0xf8


#endif/*__IRCODE_SAM_H*/