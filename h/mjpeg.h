//---------------------------------------------------------------------------
// mjpeg.h
// 
// Purpose: Motion JPEG Decoding Function Library Include file
//
//---------------------------------------------------------------------------

#ifndef MJPEG_H

#define MJPEG_H

int mjpeg_init(int width, int height);
void mjpeg_chunk_init();
int mjpeg_goto(int skip_vop_number);

extern void reset_mjpeg_video_buffer();
extern int intr_decode_mjpeg(int will_be_top_field);

#endif /* MJPEG_H */



