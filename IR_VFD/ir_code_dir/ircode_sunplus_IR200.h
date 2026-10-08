#ifndef __IRCODE_M_H
#define	__IRCODE_M_H

/*
** MTK 42 key
**
** TYPE:	NEC
** ADDR:	0xff
*/
#define _IRCODE_INC_V //kenny add it 891004
#define	IR_NEC
#define IR_ADDR_PATT    0x00fe
#include "irconfig.h"

//need to be modified
#define IR_RETURN		(GetReverse(IRC_RETURN))
#define IR_EJECT		(GetReverse(IRC_EJECT))
#define IR_STOP			(GetReverse(IRC_STOP))
#define IR_POWER		(GetReverse(IRC_POWER))
#define IR_VOLUME_UP	(GetReverse(IRC_VOLUME_UP))
#define IR_VOLUME_DOWN	(GetReverse(IRC_VOLUME_DN))
#define IR_POWER2		revn(0x9f, 8)
#define IR_RETURN2		revn(0x97, 8)


#ifdef SUPPORT_IR_GAME        
#define IR_UP   		(GetReverse(IRC_2))
#define IR_DOWN 		(GetReverse(IRC_8))
#define IR_RIGHT		(GetReverse(IRC_6))
#define IR_LEFT 		(GetReverse(IRC_4))
#define IR_START    	(GetReverse(IRC_SUBP))
#define IR_SELECT   	(GetReverse(IRC_ANGLE))
#define IR_A_KEY    	(GetReverse(IRC_AUD_LANGUAGE))
#define IR_B_KEY    	(GetReverse(IRC_MUTE))
#define IR_RIGHT_UP   		(GetReverse(IRC_3))
#define IR_LEFT_UP 		(GetReverse(IRC_1))
#define IR_RIGHT_DOWN		(GetReverse(IRC_9))
#define IR_LEFT_DOWN 		(GetReverse(IRC_7))

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


#endif


#endif/*__IRCODE_M_H*/




