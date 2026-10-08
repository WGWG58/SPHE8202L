#ifndef __IRCODE_N700_H
#define	__IRCODE_N700_H

#define _IRCODE_INC_V //kenny add it 891004

//#define	IR_NEC  //2004-7-27 20:09 LIJD MODIFY
//#define IR_PHILIPS
//#define IR_THOMSON     
//#define IR_M50560 
//#define  IR_AS1213
//#define  IR_M3004 //lijd 2004-12-27 14:24 for ORITRON
//#define IR_KONKA
//#define IR_TDP101 //lijd 2005-3-25 10:17
#define	IR_MRC2222 

#ifdef  IR_MRC2222
#define IR_ADDR_PATT	0xac04
#endif


#ifdef  IR_NEC
#define IR_ADDR_PATT	0xac04

//#define IR_ADDR_PATT	0x00f3
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

#ifdef  IR_AS1213
#define IR_ADDR_PATT	0x7070
#endif


#ifdef  IR_M3004
#define IR_ADDR_PATT	0x0005
#endif

#ifdef  IR_KONKA
#define IR_ADDR_PATT	0x0006
#endif

#ifdef  IR_TDP101
#define IR_ADDR_PATT	0x00FF
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
#define IR_UP2   	revn(0x98, 8)	
#define IR_DOWN2 	revn(0x9a, 8)	
#define IR_RIGHT2	revn(0x95, 8)	
#define IR_LEFT2 	revn(0x9d, 8)
#define IR_START2    	revn(0x8f, 8)
#define IR_SELECT2   	revn(0x8b, 8)
#define IR_A_KEY2    	revn(0x86, 8)
#define IR_B_KEY2    	revn(0x83, 8)
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






#endif/*__IRCODE_N700_H*/
