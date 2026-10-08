#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x00ff
#include "irconfig.h"
/*
#define IR_RETURN	0x28
#define IR_EJECT	0x80
#define IR_STOP		0xa8
#define IR_POWER	0x00
#define IR_VOLUME_UP	0xa0
#define IR_VOLUME_DOWN	0x90
*/

#define IR_RETURN		0x02//(GetReverse(IRC_TITLE_RETURN))
#define IR_EJECT		0xe8//(GetReverse(IRC_EJECT))
#define IR_STOP			0x40//(GetReverse(IRC_STOP))
#define IR_POWER		0xb0//(GetReverse(IRC_POWER))
#define IR_VOLUME_UP	0x08//(GetReverse(IRC_VOLUME_UP))
#define IR_VOLUME_DOWN	0x28//(GetReverse(IRC_VOLUME_DN))

#endif/*__IRCODE_N700_H*/
