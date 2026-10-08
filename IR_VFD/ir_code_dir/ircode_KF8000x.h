#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define	IR_NEC
#define IR_ADDR_PATT	0x00FF
#include "irconfig.h"

#define IR_RETURN		(GetReverse(IRC_RETURN))
#define IR_EJECT		(GetReverse(IRC_EJECT))
#define IR_STOP			(GetReverse(IRC_STOP))
#define IR_POWER		(GetReverse(IRC_POWER))
#define IR_VOLUME_UP	(GetReverse(IRC_VOLUME_UP))
#define IR_VOLUME_DOWN	(GetReverse(IRC_VOLUME_DN))

#endif/*__IRCODE_N700_H*/


