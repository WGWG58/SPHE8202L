#ifndef	__IRCODE_M_H
#define	__IRCODE_M_H

/*
** MTK 42 key
**
** TYPE:	NEC
** ADDR:	0xff
*/
#define	IR_NEC
#define	IR_ADDR_PATT	0x00ff
#include "irconfig.h"

#define	IRC_MASK	0x00ff

#ifdef NES_GAME
#define IR_RETURN       0x82   /*summer 2001/4/17 07:55PM*/
#define IR_EJECT        0x08   /*summer 2001/4/17 07:55PM*/
#endif

#define	IRC_0		0x48
#define IRC_1		0x90
#define IRC_2		0xb8
#define IRC_3		0xf8
#define IRC_4		0xb0
#define IRC_5		0x98
#define IRC_6		0xd8
#define IRC_7		0x88
#define IRC_8		0xa8
#define IRC_9		0xe8
#define	IRC_10		0xff
#define IRC_P10		0x68	// 100
#define IRC_EJECT	0x08	// Help幫助
#define IRC_MUTE	0x3a	// 靜音
#define IRC_KEY_UP	0x60	// 音量+
#define IRC_KEY_RESET	0x80	// 音量+
#define IRC_KEY_DN	0xc0	// 音量-
#define IRC_VOLUME_UP	0xa0	// 音量+
#define IRC_VOLUME_DN	0x40	// 音量-
#define IRC_SLOW	0x20
#define IRC_STEP	0xba
#define IRC_PAUSE	0x28	// Background 背景
#define IRC_PLAY	0x28	// Enter 輸入
#define IRC_RETURN	0x82	// Leave 離開
#define IRC_STOP	0xf0
#define IRC_BACKWARD	0x50	// Picture- 畫面-
#define IRC_FORWARD	0x78	// Picture+ 畫面+
#define IRC_PREV	0x70	// Channel- 頻道-
#define IRC_NEXT	0x58	// Channel+ 頻道+
#define IRC_DISPLAY	0x72	// Display 顯示
#define IRC_AB		0xa2	// B
#define IRC_REPEAT	0x12	// A
#define IRC_PBC		0xb2	// Manu 選單
#define IRC_GOTO	0x32	// SetTime定時
#define IRC_RANDOM	0x22
#define IRC_RESUME	0x0a
#define IRC_TIME	0x1a
#define IRC_POWER	0x28	// Power 電源
#define IRC_ZOOM	0x7a
#define IRC_UP	0xff
#define IRC_DOWN	0xff
#define IRC_LEFT	0xff
#define IRC_RIGHT	0xff
//#define	IRC_PLAY_IS_DEFAULT
#define	IRC_FREEZE	0x5a
#define	IRC_CHANNEL	0x38
#define	IRC_EFFECT	0x52    // sound mode
#define	IRC_PREVIEW	0x92
#define	IRC_9FRAMES	0x00
#define	IRC_INTRO	0x8a
#define	IRC_PROGRAM	0x02
#define	IRC_FORMAT	0x30
#define IRC_PAUSEPLAY  0xfd   //for VFD call //zyf 2000/10/25
// internal tetris key definition
#define IRC_GAME        0xaa
#define IRC_GAME_L	IRC_4
#define IRC_GAME_R	IRC_6
#define IRC_GAME_UP	IRC_2
#define IRC_GAME_DN	IRC_8
#define IRC_GAME_TN	IRC_5
#define IRC_GAME_UL	IRC_0

#endif/*__IRCODE_M_H*/
