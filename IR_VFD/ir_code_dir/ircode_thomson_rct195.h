#ifndef __IRCODE_M_H
#define	__IRCODE_M_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_THOMSON_ANGUS
#define IR_ADDR_PATT	0x0008

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

#ifdef SUPPORT_EX_IR
#define IR_UP2   	revn(0x47, 8)	
#define IR_DOWN2 	revn(0x4b, 8)	
#define IR_RIGHT2	revn(0x42, 8)	
#define IR_LEFT2 	revn(0x4e, 8)
#define IR_START2    	revn(0x1e, 8)
#define IR_SELECT2   	revn(0x1a, 8)
#define IR_A_KEY2    	revn(0x17, 8)
#define IR_B_KEY2    	revn(0x11, 8)
#else
#define IR_UP2   	0xff
#define IR_DOWN2 	0xff
#define IR_RIGHT2	0xff
#define IR_LEFT2 	0xff
#define IR_START2    	0xff
#define IR_SELECT2   	0xff
#define IR_A_KEY2    	0xff
#define IR_B_KEY2    	0xff
#endif

#endif/*__IRCODE_N700_H*/
