#ifndef __AUCTRL_H__
#define __AUCTRL_H__

void au_mute(int enable);  // true if mute
void au_keyshift(int key); // key ranges from -6 to +6
void au_volume(unsigned v);// 0~255

#define SE_STEREO  0
#define SE_HALL    1
#define SE_LIVE    2
#define SE_THEATER 3
#define SE_ROOM    4  /*jhuang add 5th sound effect mode 2001/3/3 03:28PM*/

void au_sound_effect(int se_mode);

#define CH_LR 0
#define CH_LL 1
#define CH_RR 2
#define CH_RL 3

void au_select_channel(int ch_mode);

//2004AUDDRV int init_audio(void);  // initialize audio decoder upon bootup
//2004AUDDRV void init_audio_dsp_coding_mode(void);
int reset_audio(void); // reset audio decoder before decoding begin
int stop_audio(void);  // stop audio decoding and mute until reset_audio() is called.

void au_main(void);    // VCD audio decoder main function
void mp3_main(void);   // CDROM audio file decoder main function
void cdda_main(void);  // CDDA audio player main function

#endif //__AUCTRL_H__
