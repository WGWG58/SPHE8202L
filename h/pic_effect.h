#ifndef __PIC_EFFECT_H
#define __PIC_EFFECT_H


#include "types.h"
#include "jpeg_parser.h"


#ifdef JPEG_EFFECT_OFFITEM
#define EFFECT_MODE_NUM  18
#else
#define EFFECT_MODE_NUM  17
#endif

extern UINT8 Jpg_effect_is_valid;
extern UINT8 Jpg_fullexpansion_is_valid;
extern UINT8 Jpg_rotation_is_valid;

extern UINT8 Jpg_is_rotate_state;
extern UINT8 Jpg_rotate_mode;
extern UINT8 Jpg_effect_mode;
extern UINT8 Jpg_effect_random;
extern UINT8 Jpg_pic_post_processing;

//Functions in pic_effect_api.c
extern void pic_effect_init(void);
extern void JPGRotate(int mode);
extern INT32 jpg_rotation_get_mode(UINT8 mode, UINT32 input_key);
extern void jpg_framebuf_copy(pd_structure *ptr, UINT8 src_framebuffer, UINT8 des_framebuffer);
extern void jpeg_effect_toggle(void);

//Functions in pic_effect.c
extern void jpg_framebuf_copy_NonExpansion(pd_structure *ptr, UINT8 src_framebuffer, UINT8 des_framebuffer);
extern void jpg_framebuf_copy_FullExpansion(pd_structure *ptr, UINT8 src_framebuffer, UINT8 des_framebuffer);
extern void jpg_rotation_NonExpansion(int mode);
extern void jpg_rotation_FullExpansion(int mode);
extern INT8 jpg_rotation_get_mode_NonExpansion(UINT8 mode, UINT32 input_key);
extern INT8 jpg_rotation_get_mode_FullExpansion(UINT8 mode, UINT32 input_key);
extern void jpeg_effect_toggle_invalid(void);
extern void jpeg_effect_toggle_valid(void);


//extern functions 

extern void DispJpgRotateStr(void);
#endif  //__PIC_EFFECT_H


