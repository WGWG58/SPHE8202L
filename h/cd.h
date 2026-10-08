#ifndef	__CD_H
#define	__CD_H

#define CDST_OPEN       (1<<0)
#define CDST_STOP       (1<<1)
#define CDST_PLAY       (1<<2)
#define CDST_PAUSE      (1<<3)
#define CDST_CHKCRC     (1<<4)

//#define	CDSTATE_START	(CDST_STOP)
//#define	CDSTATE_STOP	(CDST_STOP)
//#define	CDSTATE_OPEN	(CDST_OPEN)
//#define	CDSTATE_TRACK	(0)
//#define	CDSTATE_SEGMENT	(CDST_CHKCRC)
//#define	CDSTATE_CDROM	(CDST_CHKCRC)

#define	CDChkCRC()		(cd_state & CDST_CHKCRC)
#define	CDOpened()		(cd_state & CDST_OPEN)
#define	CDStopped()		(cd_state & CDST_STOP)
#define	CDPaused()		(cd_state & CDST_PAUSE)
#define	CDActive()		(cd_state & CDST_PLAY)

#define	CDSetOpen()		(cd_state = CDST_OPEN)
#define	CDSetStop()		(cd_state = CDST_STOP)
#define	CDSetPause()		(cd_state |= CDST_PAUSE)
#define	CDSetPauseRelease()	(cd_state &= ~CDST_PAUSE)
#define	CDSetPlay()		(cd_state = CDST_PLAY)
#define	CDSetPlayCRC()		(cd_state = CDST_PLAY | CDST_CHKCRC)

//
// MSF 
#define	IsValidMSF(msf)		(((UINT32)(msf)>>24)!=0x00ff)

void	restart_cdlayer(void);
int	is_cd_eof(void);

#endif/*__CD_H*/


