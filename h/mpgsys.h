#ifndef __MPGSYS_H
#define	__MPGSYS_H



#define	MPG_PROGRAM_STREAM_MAP		0xbc	/* MPEG2 */
#define	MPG_PRIVATE_STREAM_1		0xbd	/* MPEG2 */
#define	MPG_PADDING_STREAM		0xbe	
#define	MPG_PRIVATE_STREAM_2		0xbf

#define	MPG_ECM_STREAM			0xf0
#define	MPG_EMM_STREAM			0xf1
#define	MPG_DSM_CC_STREAM		0xf2
#define	MPG_ISO13522_STREAM		0xf3

#define	MPG_RESERVED_STREAM_0		0xf4
#define	MPG_RESERVED_STREAM_1		0xf5
#define	MPG_RESERVED_STREAM_2		0xf6
#define	MPG_RESERVED_STREAM_3		0xf7

#define	MPG_RESERVED_STREAM_4		0xf8
#define	MPG_RESERVED_STREAM_5		0xf9
#define	MPG_RESERVED_STREAM_6		0xfa
#define	MPG_RESERVED_STREAM_7		0xfb

#define	MPG_RESERVED_STREAM_8		0xfc
#define	MPG_RESERVED_STREAM_9		0xfd
#define	MPG_RESERVED_STREAM_A		0xfe
#define	MPG_PROGRAM_STREAM_DIRECTORY	0xff


#define	MPG_AUDIO_STREAM_0		0xc0
#define	MPG_AUDIO_STREAM_1		0xc1

#define	MPG_NORM_RES_VIDEO_STREAM	0xe0
#define	MPG_HIGH_RES_VIDEO_STREAM	0xe1

int	do_cd_sector(tFifo *cdfifo);

#endif/*__MPGSYS_H*/

