#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x00ff
#include "irconfig.h"

#define IR_RETURN		0x3a//0xf0
#define IR_EJECT		0x00//0xb8
#define IR_STOP			0xda//0x20
#define IR_POWER		0xff    //No POWER button in NINTAUS_DVD, Jeff 20020524
#define IR_VOLUME_UP	0x0a//0x98
#define IR_VOLUME_DOWN	0x2a//0xf8


#endif/*__IRCODE_N700_H*/
