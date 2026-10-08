#ifndef __JPEGEFFECT_H
#define __JPEGEFFECT_H


#ifdef JPG_OLD_PARSER_FLOW

#include "memmap.h"
#include "memmap0.h"

#include "types.h"


//extern BYTE FSIsZoomOK(); //Jeff 20010822
//extern UINT16 Is_MP3_STATE(void);
//extern UINT16 Is_JPEG_SlideMode(void);
//extern UINT16 mp3_file_count(void);

//#ifdef SUPPORT_NESGAME
//extern UINT16 Is_GAME_STATE(void);
//#endif

UINT8 rotate_V_flag;
UINT8 rotate_H_flag;
UINT8 rotate_flag; 
UINT8 clockwise_flag;


UINT8 Jpg_Show_Usage_Flag;
UINT8 Jpg_Show_Usage_Page;
UINT8 pause_flag;
UINT8 rotate_mode;

int   Jpg_effect_mode;
UINT8 Jpg_effect_random;
UINT8 num_sel_in_jpg;


#define LINE_HEIGHT         4
#define LINE_GAP            64

#define X_GAP               48
#define Y_GAP               48

void jpeg_call_help(void);
void jpeg_effect_draw_help(void);
void jpeg_effect_init(void);
void jpeg_effect_temp_interrupt(void);
void jpeg_effect_toggle(void);
void jpeg_use_key_to_call_help(void);
void JPG_Effect();
void Jpg_Show_Usage();
void jpeg_slide_rotate();

#ifdef JPG_EFFECT
#ifdef JPEG_EFFECT_OFFITEM	//linrc move from jpegeffect.c 2005-1-20 17:09			
#define EFFECT_MODE_NUM  18	//in order to move jpeg effect osd to osd_jpg_ratate.c
#else
#define EFFECT_MODE_NUM  17
#endif
#endif


#endif  //JPG_OLD_PARSER_FLOW

#endif//__JPEGEFFECT_H
