#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x00ff
#include "irconfig.h"

/*
#define IR_RETURN		0xf0
#define IR_EJECT		0xb8
#define IR_STOP			0x20
#define IR_POWER		0xff    //No POWER button in NINTAUS_DVD, Jeff 20020524
#define IR_VOLUME_UP	0x98
#define IR_VOLUME_DOWN	0xf8
*/

#define IR_RETURN		(GetReverse(IRC_RETURN))
#define IR_EJECT		(GetReverse(IRC_EJECT))
#define IR_STOP			(GetReverse(IRC_STOP))
#define IR_POWER		(GetReverse(IRC_POWER))
#define IR_VOLUME_UP		(GetReverse(IRC_VOLUME_UP))
#define IR_VOLUME_DOWN		(GetReverse(IRC_VOLUME_DN))

#endif/*__IRCODE_N700_H*/
