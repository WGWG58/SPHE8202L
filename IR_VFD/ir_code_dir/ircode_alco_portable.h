#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004

#define	IR_NEC  //2004-7-27 20:09 LIJD MODIFY
//#define IR_PHILIPS
//#define IR_THOMSON     
//#define IR_M50560 
#ifdef  IR_NEC
#define IR_ADDR_PATT	0x59A6//0x00f3
#endif

#ifdef  IR_PHILIPS
#define IR_ADDR_PATT	0x00FF
#endif

#ifdef  IR_THOMSON
#define IR_ADDR_PATT	0x000A
#endif

#ifdef  IR_M50560
#define IR_ADDR_PATT	0x00A8
#endif


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
