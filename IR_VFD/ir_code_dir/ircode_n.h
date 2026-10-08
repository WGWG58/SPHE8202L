#ifndef	__IRCODE_N_H
#define	__IRCODE_N_H

/*
** Shinco SVCD player RC-16A
**
** TYPE:	NEC
** ADDR:	0xff
*/
#define	IR_NEC
#define	IR_ADDR_PATT	0x0099
#include "irconfig.h"

#define	IRC_MASK	0x00ff

#ifdef NES_GAME
#define IR_RETURN       0x50   /*summer 2001/4/17 07:55PM*/
#define IR_EJECT        0x08   /*summer 2001/4/17 07:55PM*/
#endif

#define	IRC_PLAY	0x28
#define	IRC_STOP	0xf0
#define	IRC_PAUSE	0xc8
#define	IRC_FORWARD	0x58
#define	IRC_BACKWARD	0x70
#define	IRC_NEXT	0xda
#define	IRC_PREV	0x78
#define	IRC_RETURN	0x50
#define	IRC_EJECT	0x08
#define	IRC_SCREEN	0x00
#define	IRC_PREVIEW	0xd0
#define	IRC_PREV_DISC	0x00
#define	IRC_NEXT_DISC	0x00
#define	IRC_CLOSE	IRC_EJECT
#define	IRC_SLOW	0xea

#define	IRC_DISK1	0xf2
#define	IRC_DISK2	0x0a
#define	IRC_DISK3	0x8a

#define	IRC_PLAY_IS_DEFAULT

#define	IRC_PLAYMODE	0x00

#define	IRC_POWER	0xdf

#define	IRC_REPEAT	0x80
#define	IRC_AB		0x20
#define	IRC_DISPLAY	0x72
//#define	IRC_SUBTITLE	0x6a

#define	IRC_MUTE	0x60
#define	IRC_CHANNEL	0x18
#define	IRC_VOLUME_UP	0x12
#define	IRC_VOLUME_DN	0xe2
#define	IRC_KEY_UP	0x1a
#define	IRC_KEY_DN	0x9a
#define	IRC_EFFECT	0x4a
//#define	IRC_LANGUAGE	0xca
#define IRC_PAUSEPLAY  0xfd   //for VFD call //zyf 2000/10/25
#define	IRC_1		0x90
#define	IRC_2		0xb8
#define	IRC_3		0xf8
#define	IRC_4		0xb0
#define	IRC_5		0x98
#define	IRC_6		0xd8
#define	IRC_7		0x88
#define	IRC_8		0xa8
#define	IRC_9		0xe8
#define	IRC_10		0x48
#define	IRC_P10		0x68

#define	IRC_FORMAT	0x02
#define	IRC_FOCUS	0xaa

#define	IRC_ZOOM	IRC_FOCUS

#endif/*__IRCODE_N_H*/
