#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x1067
#include "irconfig.h"
/*
#define IR_RETURN	0x28
#define IR_EJECT	0x80
#define IR_STOP		0xa8
#define IR_POWER	0x00
#define IR_VOLUME_UP	0xa0
#define IR_VOLUME_DOWN	0x90
*/

#define IR_RETURN		(0xf7)//(GetReverse(IRC_RETURN))	//0x08
#define IR_EJECT		(0xff)//(GetReverse(IRC_EJECT))		//0x00
#define IR_STOP			(0xf5)//(GetReverse(IRC_STOP))		//0x0a
#define IR_POWER		(0xfc)//(GetReverse(IRC_POWER))		//0x03
#define IR_VOLUME_UP		(0xdf)//(GetReverse(IRC_VOLUME_UP))		//0x20
#define IR_VOLUME_DOWN		(0xde)//(GetReverse(IRC_VOLUME_DN))		//0x21

#endif/*__IRCODE_N700_H*/
