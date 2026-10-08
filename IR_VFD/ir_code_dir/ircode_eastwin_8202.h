#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004
//#define IR_THOMSON     //2004-5-22 11:56 LIJD
//#define IR_ADDR_PATT	0x0A
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

#define IR_RETURN		(GetReverse(IRC_RETURN))
#define IR_EJECT		(GetReverse(IRC_EJECT))
#define IR_STOP			(GetReverse(IRC_STOP))
#define IR_POWER		(GetReverse(IRC_POWER))
#define IR_VOLUME_UP	(GetReverse(IRC_VOLUME_UP))
#define IR_VOLUME_DOWN	(GetReverse(IRC_VOLUME_DN))

#endif/*__IRCODE_N700_H*/
