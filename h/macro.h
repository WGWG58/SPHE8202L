#ifndef	__MACRO_H
#define	__MACRO_H

#include "sig.h"
#include "avd.h"

void    MacroSaveHeader(void);
void 	MacroRestoreHeader();
void	MacroSync(void);
void	MacroAbort(void);
void	MacroContinue(void);
void	MacroPause(void);
void	MacroPlay(void);
void	MacroPlayLBA(void);
//void	MacroPlayOneSlide(void);
void	MacroPlayRomSlide(void);
//void	MacroPlaySector(void);
void	MacroPlayMP3(void);
void	MacroPlayTrack();
void	MacroPlayEntry();
void	MacroPlaySegment();
void	MacroSelectStream(void);


#define Save_header()	MacroSaveHeader()
#define Restore_header() MacroRestoreHeader()
#define	Abort()			MacroAbort()
#define	Sync()			MacroSync()
#define Continue()		MacroContinue()
#define	Pause()			MacroPause()
#define Play()			MacroPlay()
#define PlayLBA(a,b)		do {					\
	MacroParam.PlayLBA.lba=(a);		\
	MacroParam.PlayLBA.len=(b);		\
	MacroPlayLBA();			\
				} while (0)
#define FindFirstNav(a,b)	do {					\
	MacroParam.FindFirstNav.lba=(a);		\
	MacroParam.FindFirstNav.len=(b);		\
	MacroFindFirstNav();			\
				} while (0)
#define PlayTrack(trk)		do {					\
	MacroParam.PlayTrack.track=(trk);	\
	MacroPlayTrack();			\
				} while (0)
#define PlayEntry(ent)		do {					\
	MacroParam.PlayEntry.entry=(ent);	\
	MacroPlayEntry();			\
				} while (0)
#define PlaySegment(seg)	do {					\
	MacroParam.PlaySegment.segment=(seg);	\
	MacroPlaySegment();			\
				} while (0)
#define	PlayMP3(msf,len)	do {					\
	MacroParam.PlayMP3.address_msf=(msf);	\
	MacroParam.PlayMP3.length=(len);	\
	MacroPlayMP3();			\
				} while (0)

#define PlayRomSlide(RomAddr)	do { \
	MacroParam.PlayRomSlide.rom_addr=(RomAddr); \
	MacroPlayRomSlide(); \
				} while (0)

#define SelectStream(A,V)	do { \
	MacroParam.SelectStream.audio = (A); \
	MacroParam.SelectStream.video = (V); \
	MacroSelectStream();	\
				} while (0)

//Maoyong 2004.05.19 move from mainproc.c to here
#if defined(SETUP_DONT_PAUSE)&&!defined(PROG_DONT_PAUSE)
	#define is_setup_prog_menu()		(full_scrn&PROGRAM)
#elif defined(PROG_DONT_PAUSE)&&!defined(SETUP_DONT_PAUSE)
	#define is_setup_prog_menu()		(full_scrn&SETUP)
#elif (defined(SETUP_DONT_PAUSE)&&defined(PROG_DONT_PAUSE))||defined(SDRAM_16Mb_Mode)||defined(NEW_STYLE_SETUP)
	#define is_setup_prog_menu()		(0)
#else
	#define is_setup_prog_menu()	(full_scrn&(SETUP|PROGRAM))
#endif

typedef	struct
{
	BYTE video;
	BYTE audio;
} t_SelectStream;

typedef	struct
{
	BYTE *rom_addr;
} t_PlayRomSlide;

typedef	struct
{
	UINT32 lba;
	UINT32 len;
} t_PlayLBA;

typedef	struct
{
	UINT32 lba;
	UINT32 len;
} t_FindFirstNav;

typedef	struct
{
	BYTE track;
} t_PlayTrack;
typedef	struct
{
	UINT16 entry;
} t_PlayEntry;
typedef	struct
{
	UINT16 segment;
} t_PlaySegment;
typedef	struct
{
	UINT32 address_msf;
	UINT32 length;
} t_PlayMP3;

EXTERN	union
{
	//t_ReadCD		ReadCD;
	//t_SetOsdColor		SetOsdColor;
	//t_OSD_OnOff		OSD_OnOff;
	//t_SetVideoFormat	SetVideoFormat;
	t_SelectStream	SelectStream;
	t_PlayRomSlide	PlayRomSlide;
	t_PlayTrack		PlayTrack;
	t_PlayLBA		PlayLBA;
	t_PlayEntry		PlayEntry;
	t_PlaySegment		PlaySegment;
	t_PlayMP3		PlayMP3;
	//t_SetVolume		SetVolume;
	t_FindFirstNav	FindFirstNav;
} MacroParam;


#endif/*__MACRO_H*/
				
