
#ifndef _ALPHA_H
#define _ALPHA_H
#include "user_init.h"

#ifndef U32
typedef unsigned int    U32;
#endif
#ifndef U16
typedef unsigned short  U16;
#endif
#ifndef U08
typedef unsigned char   U08;
#endif
#ifndef S32
typedef int             S32;
#endif
#ifndef S16
typedef short           S16;
#endif
#ifndef S08
typedef char            S08;
#endif

#ifndef NULL
#define	NULL (void *)0
#endif/*NULL*/


#ifdef SUPPORT_MIDIUI_IME

/*
#define  PY_CMD_SELECT      0x48
#define  PY_CMD_STOP          0xA8
#define  PY_CMD_UP              0x29
#define  PY_CMD_DOWN         0x2a
#define  PY_CMD_LEFT           0x2b
#define  PY_CMD_RIGHT         0x2c

#define  PY_CMD_PAUSE        0xA0
#define  PY_CMD_RESUME      0xD0
#define  PY_CMD_COPY          0x0A
#define  PY_CMD_PASTE        0x82
#define  PY_CMD_SLOW         0x1A
#define  PY_CMD_RETURN         0xF0
#define  PY_CMD_MUTE         0x38
#define  PY_CMD_PREV         0x2A
#define  PY_CMD_NEXT         0x32
#define  PY_CMD_NAME         0x10
#define  PY_CMD_FORMAT         0xC8
#define  PY_CMD_DEL       0x70
#define  PY_CMD_ENTER   0x30
#define  PY_CMD_CLEAR    0x90
#define  PY_CMD_CUTE    0xBA
#define  PY_CMD_CHANGE  0x9A
#define  PY_CMD_RECORD   0xB8
#define  PY_CMD_AUDIO_LANGUAGE   0xB2
#define  PY_CMD_SUB_PICTURE  0xA2
#define  PY_CMD_FORWARD    0xC0
#define  PY_CMD_BACKWARD    0x3A
#define  PY_CMD_PLAY     0x50
#define  PY_CMD_VOLUME_UP  0x98
#define  PY_CMD_VOLUME_DOWN  0xF8
#define  PY_CMD_INSERTPLAY   0x02
#define  PY_CMD_3DSOUND  0X6A
*/

#define  PY_CMD_1  0x01
#define  PY_CMD_2  0x02
#define  PY_CMD_3  0x03
#define  PY_CMD_4  0x04
#define  PY_CMD_5  0x05
#define  PY_CMD_6  0x06
#define  PY_CMD_7  0x07
#define  PY_CMD_8  0x08
#define  PY_CMD_9  0x09
#define  PY_CMD_0  0x00

#define  PY_IR_CODE_MAX_NUM  42


#define MAX_PINYIN_NUM  16//xlluo add 04-11-25//20
extern void  Init_alpha(void);
extern U08 *Alpha_Input_YX(U08 keyno);
extern void Code_Input(U08 , U08 , U08 );	
#endif//#ifdef SUPPORT_MIDIUI_IME

#endif

