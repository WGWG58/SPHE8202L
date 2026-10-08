#ifndef __IRCODE_M_H
#define	__IRCODE_M_H

/*
** soujia remote controller
**
** TYPE:	NEC
** ADDR:	0xff
*/
#define	IR_NEC
#define IR_ADDR_PATT    0x00ff
#include "irconfig.h"

#define IRC_MASK        0x00ff

#ifdef NES_GAME
#define IR_RETURN       0x43   /*summer 2001/4/17 07:55PM*/
#define IR_EJECT        0x10   /*summer 2001/4/17 07:55PM*/
#endif

#ifdef SUPPORT_COMBO
#define	IRC_0		0x12
#define IRC_1		0x09
#define IRC_2		0x1d
#define IRC_3		0x1f
#define IRC_4		0x0d
#define IRC_5		0x19
#define IRC_6		0x1b
#define IRC_7		0x11
#define IRC_8		0x15
#define IRC_9		0x17
#define	IRC_10		0xff
#define IRC_P10		0x16	// 100
#define IRC_EJECT	0x10	// Help幫助
#define IRC_MUTE	0x4a	// 靜音
#define IRC_KEY_UP	0xff	// 音量+
#define IRC_KEY_RESET	0xff	// 音量+
#define IRC_KEY_DN	0xff	// 音量-
#define IRC_LANGUAGE    0xff 
#define IRC_VOLUME_UP	0x03	// 音量+
#define IRC_VOLUME_DN	0x02	// 音量-
#define IRC_SLOW	0x18
#define IRC_STEP	0xff
#define IRC_PAUSE	0x51	// Background 背景
#define IRC_PLAY	0x07	// Enter 輸入
#define IRC_RETURN	0x43	// Leave 離開
#define IRC_STOP	0x14
#define IRC_BACKWARD	0x47	// Picture- 畫面-
#define IRC_FORWARD	0x40	// Picture+ 畫面+
#define IRC_PREV	0x06	// Channel- 頻道-
#define IRC_NEXT	0x44	// Channel+ 頻道+
#define IRC_DISPLAY	0x50	// Display 顯示
#define IRC_AB		0x0f	// B
#define IRC_REPEAT	0x55	// A
#define IRC_PBC		0x05	// Manu 選單
#define IRC_GOTO	0x08	// SetTime定時
#define IRC_RANDOM 	0x48
#define IRC_RESUME	0xff
#define IRC_TIME	0x00
#define IRC_POWER	0xff	// Power 電源
#define IRC_ZOOM	0x57
#define IRC_UP	0xff
#define IRC_DOWN	0xff
#define IRC_LEFT	0xff
#define IRC_RIGHT	0xff
//#define	IRC_PLAY_IS_DEFAULT
#define	IRC_FREEZE	0x42
#define	IRC_CHANNEL	0xff
#define	IRC_EFFECT	0xff    // sound mode
#define	IRC_PREVIEW	0x53
#define	IRC_9FRAMES	0x01
#define	IRC_PROGRAM	0x49
#define	IRC_FORMAT	0x13
// internal tetris key definition
#define IRC_INTRO       0x41
#define IRC_GAME_L	IRC_4
#define IRC_GAME_R	IRC_6
#define IRC_GAME_UP	IRC_2
#define IRC_GAME_DN	IRC_8
#define IRC_GAME_TN	IRC_5
#define IRC_GAME_UL	IRC_0
#define IRC_PAUSEPLAY  0xfd   //for VFD call //zyf 2000/10/25
#else
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
#define IRC_MUTE	0x52	// 靜音
#define IRC_KEY_UP	0xff	// 音量+
#define IRC_KEY_RESET	0xff	// 音量+
#define IRC_KEY_DN	0xff	// 音量-
#define IRC_VOLUME_UP	0xc0	// 音量+
#define IRC_VOLUME_DN	0x40	// 音量-
#define IRC_SLOW	0x18
#define IRC_STEP	0xff
#define IRC_PAUSE	0x8a	// Background 背景
#define IRC_PLAY	0xe0	// Enter 輸入
#define IRC_RETURN	0xc2	// Leave 離開
#define IRC_STOP	0xea
#define IRC_BACKWARD	0xe2	// Picture- 畫面-
#define IRC_FORWARD	0x02	// Picture+ 畫面+
#define IRC_PREV	0x60	// Channel- 頻道-
#define IRC_NEXT	0x22	// Channel+ 頻道+
#define IRC_DISPLAY	0x0a	// Display 顯示
#define IRC_AB		0xf0	// B
#define IRC_REPEAT	0xaa	// A
#define IRC_PBC		0xa0	// Manu 選單
#define IRC_GOTO	0x10	// SetTime定時
#define IRC_RANDOM 	0x12
#define IRC_RESUME	0xff
#define IRC_TIME	0x00
#define IRC_POWER	0xff	// Power 電源
#define IRC_ZOOM	0x7a
#define IRC_UP	0xff
#define IRC_DOWN	0xff
#define IRC_LEFT	0xff
#define IRC_RIGHT	0xff
//#define	IRC_PLAY_IS_DEFAULT
#define	IRC_FREEZE	0x42
#define	IRC_CHANNEL	0xff
#define	IRC_EFFECT	0xff    // sound mode
#define	IRC_PREVIEW	0x62
#define	IRC_9FRAMES	0x80
#define	IRC_PROGRAM	0x92
#define	IRC_FORMAT	0xc8
// internal tetris key definition
#define IRC_INTRO       0x82
#define IRC_GAME_L	IRC_4
#define IRC_GAME_R	IRC_6
#define IRC_GAME_UP	IRC_2
#define IRC_GAME_DN	IRC_8
#define IRC_GAME_TN	IRC_5
#define IRC_GAME_UL	IRC_0

#endif //SUPPORT_COMBO

#endif/*__IRCODE_M_H*/
