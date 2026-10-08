#ifndef	__SIG_H
/*
** FILE 
** sig.h
**
** DESCRIPTION
** we will implement a reliable signaling scheme here.
**
** NOTE:
**
** a typical system should be like this..
**
**	do 
**	{
**	  srv_...
**	  if (soft_intr_flag)
**	  {
*8	    interrupt-handler();
**	  }
**	} while (!finished);
**
**
*/


/*
** SIGNALs
**
** INTR_SEQ_HEADER:	sequence header found
** INTR_SEQ_END:	sequence end found
** INTR_GOP:		gop header found
** INTR_I_PIC:		I-picture found
** INTR_A_PIC:		any picture found
** INTR_AUTOPAUSE:	auto pausing found
** INTR_EOF:		END-OF-FILE found (CD-XA flag)
** INTR_VFD:		VFD input
** INTR_IRKEY:		IR input
** INTR_TRAYIN:		IR input
*/
#define	INTR_SKIP_INTRO		(1<<17)
#define	INTR_PROG_END		(1<<16)
#define	INTR_SEQ_HEADER		(1<<15)
#define	INTR_SEQ_END		(1<<14)
#define	INTR_GOP		(1<<13)
#define	INTR_I_PIC		(1<<12)
#define	INTR_A_PIC		(1<<11)
#define	INTR_CD_FAILURE		(1<<9)
#define	INTR_AUTOPAUSE		(1<<8)
#define	INTR_EOF		(1<<7)
#define	INTR_TIMEOUT		(1<<6)
#define	INTR_TRACK_CHANGE	(1<<5)
#define	INTR_FOUND		(1<<4)
#define	INTR_VFD		(1<<3)
#define	INTR_IRKEY		(1<<2)
#define	INTR_TRAYIN		(1<<1)
#define	INTR_TRAYOUT		(1<<0)

EXTERN	UINT32	softintr_mask;
//EXTERN	UINT32	softintr_flag;

#define	SetIntrMask(x)		(softintr_mask = (x))
#define	GetIntrMask()		(softintr_mask)
//#define	SetIntrFlag(x)		(softintr_flag = (x))
//#define	GetIntrFlag()		(softintr_flag)

#define	INTR_MASK_CDROM		\
				( INTR_TIMEOUT \
				| INTR_TRAYOUT | INTR_TRAYOUT)

#define	INTR_MASK_NORMAL	\
				( INTR_TIMEOUT \
				| INTR_PROG_END \
				| INTR_TRACK_CHANGE \
				| INTR_AUTOPAUSE \
				| INTR_VFD \
				| INTR_IRKEY \
				| INTR_TRAYOUT | INTR_TRAYOUT)

#define	INTR_MASK_NORMAL_LINEAR	\
				( INTR_TIMEOUT \
				| INTR_PROG_END \
				| INTR_TRACK_CHANGE)
		
#define	INTR_MASK_NORMAL_CDDA	( INTR_TIMEOUT \
				| INTR_TRACK_CHANGE \
				| INTR_VFD \
				| INTR_IRKEY \
				| INTR_TRAYOUT | INTR_TRAYOUT)

#define	INTR_MASK_NORMAL_MP3	( INTR_TIMEOUT \
				| INTR_TRACK_CHANGE \
				| INTR_EOF \
				| INTR_VFD \
				| INTR_IRKEY \
				| INTR_TRAYOUT | INTR_TRAYOUT)

#define	INTR_MASK_READTOC	( INTR_TIMEOUT \
				| INTR_VFD \
				| INTR_PROG_END \
				| INTR_IRKEY \
				| INTR_TRAYOUT | INTR_TRAYOUT)

#define	INTR_MASK_IDLE		( INTR_TIMEOUT \
				| INTR_PROG_END \
				| INTR_VFD \
				| INTR_IRKEY \
				| INTR_TRAYOUT | INTR_TRAYOUT)


#define	INTR_MASK_NORMAL_ROM	( INTR_EOF	\
				| INTR_PROG_END \
				| INTR_SEQ_END	\
				| INTR_TIMEOUT	\
				| INTR_VFD	\
				| INTR_IRKEY )

#endif/*__SIG_H*/
