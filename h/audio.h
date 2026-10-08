#ifndef	AUDIO_H
#define AUDIO_H

//2004AUDDRV int init_audio(void);
void init_audio_dsp_coding_mode(void);
int	reset_audio(void);
void	au_main(void);

enum	{
	AUD_CMD_VOL_L	= 0x01,		/* left-channel-vol 0-255	*/
	AUD_CMD_VOL_R	,		/* right-channel-vol 0-255	*/
	AUD_CMD_CHANNEL = 0x10,		/* channel mask			*/
	AUD_CMD_EFFECT	,
	AUD_CMD_KEY			/* key-shift ctrl in half-keys	*/
};

/*
**	output channel control.
*/
#define	AUD_CHN_LEFT	(0x01<<0)
#define	AUD_CHN_RIGHT	(0x01<<1)
#define	AUD_CHN_LS	(0x01<<2)
#define	AUD_CHN_RS	(0x01<<3)
#define	AUD_CHN_CENTER	(0x01<<4)
#define	AUD_CHN_LFE	(0x01<<5)

/*
**	spatial effect
*/
#define	AUD_EFF_NONE	(0)
#define	AUD_EFF_HALL	(1)
#define	AUD_EFF_PUB	(2)
#define	AUD_EFF_	(3)

int	ctl_audio(UINT32 cmd, UINT32 param);

#endif/*AUDIO_H*/

