#ifndef __MP3TEST_H__
#define __MP3TEST_H__

#include "mpgaudio.h"

//#define __TEST_MP3_SYN
//#define __TEST_MP3_SYN_IN
//#define __TEST_IMDCT_IN
//#define __TEST_AA_IN
//#define __TEST_SINGLE_IMDCT
//#define __TEST_SINGLE_L3_SYN
#ifdef __STREAM_FROM_CDROM
//# define __CDROM_PCM_CHECK
#endif

#ifdef __TEST_MP3_SYN
void test_mp3_syn(int frame_number);
#endif

#ifdef __TEST_MP3_SYN_IN
void test_mp3_syn_in(int frame_number);
#endif

#ifdef __TEST_IMDCT_IN
void test_imdct_int(int frame_number, int gr, int ch);
#endif

#ifdef __TEST_AA_IN
void test_aa_in(short aa[32][18], int fr_num, int gr, int ch);
#endif

#ifdef __TEST_SINGLE_IMDCT
void test_hw_IMDCT(void);
#endif

#ifdef __TEST_SINGLE_L3_SYN
void test_single_L3_SYN(void);
#endif

#ifdef __CDROM_PCM_CHECK
void test_mp3_PCM_underflow(void);
void test_mp3_PCM_FIFO_CNT(void);
#else
static __inline void test_mp3_PCM_underflow(void) {}
static __inline void test_mp3_PCM_FIFO_CNT(void) {}
#endif

#endif
