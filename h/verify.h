#ifndef	__VERIFY_H
#define	__VERIFY_H

//#define VERIFY_LBC
//#define VERIFY_REFRESH
//#define VERIFY_VFD
//#define VERIFY_FRAMEBUF
//#define VERIFY_FONT
//#define VERIFY_DITHER

#ifdef	VERIFY_LBC
void	VerifyLBC(void);
#endif/*VERIFY_LBC*/

#ifdef	VERIFY_REFRESH
void	VerifyRefreshFill(void);
void	VerifyRefreshCheck(void);
#endif/*VERIFY_REFRESH*/

#ifdef	VERIFY_VFD
void	VerifyVFD(void);
#endif

#ifdef	VERIFY_FONT
void	VerifyFont(void);
#endif

#ifdef	VERIFY_DITHER
void	verify_dither(void);
#endif

#endif/*__VERIFY_H*/

