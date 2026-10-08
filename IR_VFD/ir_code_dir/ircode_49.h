#ifndef	__IRCODE_M_H
#define	__IRCODE_M_H

/*
** MTK 42 key
**
** TYPE:	NEC
** ADDR:        0x866b
*/
#define	IR_NEC
#define IR_ADDR_PATT    0x00ff
#include "irconfig.h"
#define	IRC_MASK	0x00ff

#ifdef NES_GAME
#define IR_RETURN  0x53   /*summer 2001/4/17 07:55PM*/
#define IR_EJECT   0x10   /*summer 2001/4/17 07:55PM*/
#endif

// MTK 42 keys (new)
//#define IRC_0		0xff
#define IRC_1           0x09
#define IRC_2           0x1d
#define IRC_3           0x1f
#define IRC_4           0x0d
#define IRC_5           0x19
#define IRC_6           0x1b
#define IRC_7           0x11
#define IRC_8           0x15
#define IRC_9           0x17
#define IRC_10          0x12
#define IRC_P10         0x59    // 100
#define IRC_EJECT       0x10    // Help幫助
#define IRC_MUTE        0x4a    // 靜音
#define IRC_KEY_UP      0x46    // 音量+
#define IRC_KEY_DN      0x57    // 音量-
#define IRC_KEY_RESET   0x42
#define IRC_VOLUME_UP   0x03    // 音量+
#define IRC_VOLUME_DN   0x02    // 音量-
#define IRC_SLOW        0x18
#define IRC_STEP        0x4b
#define IRC_PAUSE       0x13    // Background 背景
#define IRC_PLAY        0x51    // Enter 輸入
#define IRC_RETURN      0x53    // Leave 離開
#define IRC_STOP        0x0f//0x4c
#define IRC_BACKWARD    0x0a    // Picture- 畫面-
#define IRC_FORWARD     0x1e    // Picture+ 畫面+
#define IRC_PREV        0x0e    // Channel- 頻道-
#define IRC_NEXT        0x1a    // Channel+ 頻道+
#define IRC_DISPLAY     0x50    // Display 顯示
#define IRC_AB          0x60//0x61    // B
#define IRC_REPEAT      0x55    // A
#define IRC_PBC         0x48    // Manu 選單
//#define IRC_CODE_GOTO	0x2f	// SetTime定時
//#define IRC_CODE_RANDOM	0xdd
#define IRC_POWER       0x14    // Power 電源
#define IRC_ZOOM        0x07
//#define IRC_CODE_FASTCD	0x1d
#define IRC_DISK1       0x63
#define IRC_DISK2       0x64
#define IRC_DISK3       0x65
#define IRC_PLAY_IS_DEFAULT  0x66
#define IRC_PLAYMODE    0x67
//#define IRC_SUBTITLE    0x68

#define IRC_CHANNEL     0x5e
#define	IRC_EFFECT	    0x42//0x08    // sound mode
#define IRC_PREVIEW     0x01//0x43
#define	IRC_9FRAMES	    0x14
#define IRC_INTRO       0x43
#define IRC_FORMAT      0x05
#define IRC_FOCUS       0x6a
#define IRC_FREEZE      0x56
#define IRC_RANDOM	    0x45
#define IRC_TIME	    0x00
#define IRC_GOTO	    0x52
	
// internal tetris key definition
#define IRC_GAME        0x92
#define IRC_GAME_L	IRC_4
#define IRC_GAME_R	IRC_6
#define IRC_GAME_UP	IRC_2
#define IRC_GAME_DN	IRC_8
#define IRC_GAME_TN	IRC_5
#define IRC_GAME_UL	IRC_0

#endif/*__IRCODE_M_H*/
