#ifndef __IRCODE_VTREK_mini_H
#define	__IRCODE_VTREK_mini_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT	0x00df
#include "irconfig.h"

#define IR_RETURN	0x9c
#define IR_EJECT	0x94
#define IR_STOP		0x06
#define IR_POWER	0x14
#define IR_VOLUME_UP	0x1c
#define IR_VOLUME_DOWN	0xc2

/*
#define IR_RETURN		(GetReverse(IRC_RETURN))
#define IR_EJECT		(GetReverse(IRC_EJECT))
#define IR_STOP			(GetReverse(IRC_STOP))
#define IR_POWER		(GetReverse(IRC_POWER))
#define IR_VOLUME_UP	(GetReverse(IRC_VOLUME_UP))
#define IR_VOLUME_DOWN	(GetReverse(IRC_VOLUME_DN))
*/
#endif/*__IRCODE_VTREK_H*/
