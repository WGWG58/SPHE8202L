/*
*    Terry,2005/4/16 01:48¤U¤È
*/

#ifndef __NAV_H
#define __NAV_H
//#define NAV_ALL_DBG

//#define NAV_DELAY_MSG
//#include "user_if.h"
//#include "types.h"
#include "misc.h"
#include "navdata.h"
#include "image.h"
#include "sup_drv.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#include "dvdpe.h"
#include "lbaif.h"
#include "func.h"
#include "ircmd.h"
#include "stdlib.h"
#include "global.h"
#include "util.h"
#include "memmap0.h"


//dvd navigation define option
//#define NEW_SEL_AUDIO_WAY  //user_if.c

/**************************************************
   Arguments for PreFetchNextVobuAddr()
**************************************************/
//=== switches of PreFetchNextVobuAddr() behavior ===
    //execute cell post command while searching next cell
#define DVDNAV_FETCHVOBU_EXE_CELL_POST_CMD              (0x00000001)
    //return 0x3FFFFFFF when stc discontinuity flag is set
#define DVDNAV_FETCHVOBU_ABORT_ON_STC_DISCONTINUITY     (0x00000010)

//=== some preset configuration for PreFetchNextVobuAddr() arguments ===
    //behavior of original code (original code means code before modification
    //by kevinmonkey adding all this argument stuff on 2006/09/11)
#define DVDNAV_FETCHVOBU_NEXT_PE_PROC_CELL   \
        DVDNAV_FETCHVOBU_EXE_CELL_POST_CMD   \
        |DVDNAV_FETCHVOBU_ABORT_ON_STC_DISCONTINUITY  
    //kevinmonkey 20060911 fixing when stc discontinuity flag set, PreFetchNextVobuAddr() returns
    //0x3FFFFFFF and can't goto correct cell (see how PG_Search() using PreFetchNextVobuAddr())
#define DVDNAV_FETCHVOBU_GOTO_NEXT_CELL   \
        0

// nav
//void navStartUp(void);
//void navTest(void);
int dvd_navigation(void);


#ifdef MINUS_VR_AUTH_PLAYBACK
int DVD_Minus_VR_Navigation(void);	//Added By Gary For DVD-VR Navigation 93.1.26
void VR_Check_C_EPI();
void VR_Set_Chapter_PTM();
//VMG.C
void VMG_Load_RTR_VMGI();
//PGC.C
void VR_PGC_Load();
void VR_PGC_Play();		//Added By Gary Lin For DVD-VR Naviagation 93.1.27
void VR_PG_Play();
void VR_CELL_Play();

void VR_PE_play();

UINT16 VR_Find_PTTN(UINT32 time);
UINT32 VR_Find_PTM_By_Entry(UINT16 ENTRY);
UINT32 VR_Find_VOBU_EA_By_Entry(UINT16 ENTRY);
UINT32 VR_Find_VOBU_Addr(UINT32 PTM,UINT8 bset);
UINT32 VRPreFetchNextVobuAddr(void);

void Play_PL_N(UINT8 PL_PGCN);

void VR_Clear_RDI();


#define VR_MOVIE_PAL	((pDSV->dV_ATR>>12)&0x0003)
#define VR_MOVIE_NTSC	(!VR_MOVIE_PAL)	

#define Is_Playlist_Title	(!pDSV->dPGC_PG_Ns)	//Added By Gary 92.02.23 PG_Ns is 0 in Playlist Titles.

#define VR_MENU_ORIGINAL 0x00
#define VR_MENU_PLAYLIST 0x01

UINT32 VR_Menu_callback_check(UINT32 func);

#endif//#ifdef MINUS_VR_AUTH_PLAYBACK


// 0: continue loop
#define LOOP_END_TERMINATION  (1)
#define LOOP_END_PE_PROC      (2)



void decode_tm(UINT8 *, PlayBack_Time *);



void PGC_load(void);
void PGC_play(void);
void PGC_post(void);
void PG_play(void);
void PGC_idle(void);
void CELL_play(void);
void CELL_post(void);
void PE_proc(void);

// PE
void PE_init(UINT8);
void PE_play(void);
void PE_show(UINT32, UINT32);

int do_HLI(UINT32 nowtime);

// Global
void GLB_loc_PGC(void);


// PGPlayed
UINT8 IS_PGPlayed(UINT8);
void SET_PGPlayed(UINT8);
void RESET_PGPlayed(void);
UINT8 SELECT_PGPlayed(void);


// nav_rpt.c
//extern char rpt_buf[128];
#ifdef TEST_REPORT
void rpt_init(void);
void rpt_status(void);
void rpt_cell(void);

void pgcn_report(int n);
void pg_report(int n);
void cell_report(int n);
void ncmd_report(char *s);
#else
#define rpt_init()               ((void)(0))
#define rpt_status()             ((void)(0))
#define rpt_cell()               ((void)(0))

#define pgcn_report(n)           ((void)(0))
#define pg_report(n)             ((void)(0))
#define cell_report(n)           ((void)(0))
#define ncmd_report(s)           ((void)(0))
#endif

// vmg.c
UINT32 VMG_Find_LU(UINT32 lsn);
UINT8 VMG_Find_Menu(UINT16 dPGCN, UINT8 dMenuID);
void VMG_Load_PTL_MAIT(void);
void VMG_Load_TT_SRPT(void);
UINT8 VMG_Load_VMGI(void);
// dVMG_LSN => load VMGI
UINT8 VMG_Load_VMGI(void);

// LSN => LU SA
UINT32 VMG_Find_LU(UINT32);

// LSN, PGCN, MenuID => PGC location
// search type: PGCN != 0 ==> find PGC; PGCN == 0 ==> find Menu 
//void VMG_Find_Menu(UINT16, UINT8);

// TTN => VTS_SA, VTSN, VTS_TTN
// -VTSN => VTS_SA
void VMG_Find_TT(INT16);

// vts.c

// VMGI, dVTS_SA => load VTSI
UINT8 VTS_Load_VTSI(void);
void VMG_Load_ASVI(UINT8 ASVUN);

// VTSI, VTS_TTN, PTTN => PGCN
void VTS_Find_PTT(UINT8 SearchPGN);

// VTSI, TT_PGCN => PGC location
void VTS_Find_PGC(UINT8 get_new_vts_info);


//nav.c
void clr_param(UINT8 p);
void CounterGPRM(void);
void DumpAudioInfo(void);
void DumpPGC(void);
int  dvd_navigation(void);
#if defined(FORCE_REWRITE_WHEN_UPGRADE)||defined(FORCE_REWRITE_DRM_WHEN_UPGRADE)//terry,2004/1/8 05:32PM
void load_user_setup(UINT8);
#else
void load_user_setup(void);
#endif
void  param_init(void);
void UI_Polling(void);
UINT32	dvd_callback_check(UINT32 func);
UINT8 DVD_show_time(void);
void DVD_get_time(int);
void dvd_hl_force_action(void);
void GetOffsetLba(UINT32 *lba,UINT32 abs);


//pgc.c
void get_subp_plt(UINT8 *p);
void CELL_play(void);
void CELL_post(void);
int CellShift(int cn,UINT8 *angle);
void CorrectAngleCell(UINT8 shift);
void decode_tm(UINT8 *p, PlayBack_Time *tm);
int do_HLI(UINT32 nowtime);
void GetPrgTime(void);
UINT8 IS_PGPlayed(UINT8 n);
UINT8 Parental_BMg(UINT8 *p);
UINT16 Parental_ID_Acq(UINT8);
void PE_play(void);
void PE_proc(void);
void PG_play(void);
void PGC_load(void);
void PGC_play(void);
void PGC_post(void);
UINT32 PreFetchNextVobuAddr(UINT32 uArgument);
void RESET_PGPlayed(void);
UINT8 RunNvCmd(UINT16 state);
void Select_ASTN(BYTE selmode);
UINT8 SELECT_PGPlayed(void);
UINT8 RunNvCmd(UINT16 state);
void Select_ASTN(BYTE selmode);
UINT8 SELECT_PGPlayed(void);
void Select_SPSTN(BYTE selmode);
void SET_PGPlayed(UINT8 n);
void SetAPS(UINT16 APSTB);
void TestIsPGPlayed(void);
void SearchPG(void);
void sel_disp_sp_ch(UINT16 id);
void sel_audio_language(UINT8 *level,UINT16 *id,UINT8 selmode);

//sysmain.c
int	dvd_auth_lba(UINT32 LBA);
//user_if.c
void TM2TM(UINT8 *s,UINT8 *d);
UINT32 AddTM2S(PlayBack_Time*, PlayBack_Time*, UINT32);
UINT8 Time_Play_2(void);
UINT8 Time_Play(void);
UINT8 PTT_Play(UINT8, UINT16, UINT8);
UINT8 PG_Search(UINT8);
UINT8 UOP_func_Menu_Call(UINT8);
UINT32 DesignationCN(UINT8*,UINT32);
UINT8 Resume(void);
UINT8 Stop(void);
UINT8 Resume(void);
UINT8 Menu_Call(UINT8);
void GetCellTime(UINT8,UINT32*);
void GetCellTm(UINT8,PlayBack_Time*);
void S2TM(UINT32,PlayBack_Time*);
UINT8 get_angle_Ns(void);
extern void reset_sup(void);
extern void setDVD_A_V(UINT8);
UINT8 force_rep_all_search_next_trk(UINT16 *ptt,UINT8 *chg_tt);//terry,2004/2/17 11:09AM
#endif/*__NAV_H*/

