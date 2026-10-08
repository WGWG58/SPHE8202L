#ifndef __IRCODE_IDALL_H
#define	__IRCODE_IDALL_H

#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#ifdef PDVD_TYPE
#define IR_ADDR_PATT    0x00df
#else
#define IR_ADDR_PATT	0x00ff
#endif
#include "irconfig.h"

#define IR_RETURN		0x12//f0
#define IR_EJECT		0xb0//b8
#define IR_STOP			0xa2//20
#define IR_POWER		0xff    //No POWER button in NINTAUS_DVD, Jeff 20020524
#define IR_VOLUME_UP	        0xca//98
#define IR_VOLUME_DOWN	        0x4a//f8


//#define IR_RETURN		(GetReverse(IRC_RETURN))
//#define IR_EJECT		(GetReverse(IRC_EJECT))
//#define IR_STOP			(GetReverse(IRC_STOP))
//#define IR_POWER		(GetReverse(IRC_POWER))
//#define IR_VOLUME_UP	(GetReverse(IRC_VOLUME_UP))
//#define IR_VOLUME_DOWN	(GetReverse(IRC_VOLUME_DN))


#endif/*__IRCODE_IDALL_H*/

