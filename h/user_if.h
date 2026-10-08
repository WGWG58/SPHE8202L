#ifndef __USER_IF_H
#define __USER_IF_H


#include "types.h"
#include "navdata.h"
//#include "misc.h"

enum {
	DISP_CH=0,
	DISP_CH_Ns=1,
	DISP_TT,
	DISP_TT_Ns,	
};
//========================================================================
//Playback time define
//========================================================================
#define TT_TIME		 		0
#define RM_TT_TIME			1
#define CH_TIME				2
#define RM_CH_TIME			3
#define DISPLAY_MAX_MODE	4

//========================================================================
//Playback time Compare define
//========================================================================
#define LESS		0
#define GREATER 	1
#define EQUAL		2
#define ERROR		0xffffffff
//========================================================================
//User Operation Prohibited Checking Set
//========================================================================
//#define UOP_DISABLE	//disable user operation prohibited check 
#define UOP_PERMIT		(0)
#define UOP_PROHIBIT	(1)

#define UOP_TM_PS 		0
#define UOP_PTT_PS		1
#define UOP_TT_P		2
#define UOP_STOP		3
#define UOP_GOUP		4
#define UOP_TM_PTT_S	5
#define UOP_PPG_S		6			
#define UOP_NPG_S		7
#define UOP_FW			8
#define UOP_BW			9
#define UOP_TT_M		10
#define UOP_RT_M		11
#define UOP_SP_M		12//LINRC open it.20060414
//#define UOP_AU_M		13
//#define UOP_AG_M		14
//#define UOP_PTT_M		15
#define UOP_RSM			16
#define UOP_BTN			17
#define UOP_ST_OFF		18
#define UOP_PAUSE		19
#define UOP_ASTN_CHG	20
#define UOP_SPSTN_CHG	21
#define UOP_AG_CHG		22
#define UOP_KOK_CHG		23
#define UOP_V_MD_CHG	24

//========================================================================
//Scan mode define
//========================================================================
#define STEP_SCAN	UOP_PAUSE
#define STOP_SCAN	UOP_STOP
#define FW_SCAN 	UOP_FW
#define BW_SCAN		UOP_BW


//======================================================================
//user_if.c function declare
//======================================================================
#ifdef  UI_FUNC_HERE
#define EXTERN_FUNC
#else
#define EXTERN_FUNC      extern
#endif

EXTERN_FUNC UINT8 Stop(void);
EXTERN_FUNC UINT8 Subp_stream_Chg(UINT8,int);
//EXTERN_FUNC UINT8 Subp_stream_Chg_SVCD(UINT8);  //Jeff 20010816
EXTERN_FUNC UINT16 Audio_stream_Chg(UINT8,int);
EXTERN_FUNC UINT16 Audio_stream_Chg_SVCD(UINT8);    //Jeff 20010816
EXTERN_FUNC UINT16 Audio_stream_Chg_MediaContainerFile(UINT8);		//zhongshan 2006-2-28 10:27
#ifdef VOB_SUBTITLE
EXTERN_FUNC UINT16 Audio_stream_Chg_VOB(UINT8);    //Paul 20041126
EXTERN_FUNC UINT16 Subp_stream_Chg_VOB(UINT8);    //Paul 20041126
#endif
EXTERN_FUNC UINT8 Angle_Chg(UINT8,int);
EXTERN_FUNC UINT8 Resume(void);
EXTERN_FUNC UINT8 Menu_Call(UINT8 MenuID);
EXTERN_FUNC UINT8 PTT_Play(UINT8 ttn,UINT16 pttn,UINT8 checkUOP);
EXTERN_FUNC UINT8 PG_Search(UINT8 n_p);
EXTERN_FUNC UINT8 Time_Play(void/*UINT16 ttn*/);

EXTERN_FUNC UINT32 DesignationCN(UINT8 *cn,UINT32 ts);
EXTERN_FUNC UINT32 TM2S(PlayBack_Time *s);
EXTERN_FUNC void S2TM(UINT32 s,PlayBack_Time *d);
EXTERN_FUNC UINT8 CmpTM(PlayBack_Time *s,PlayBack_Time *d);
EXTERN_FUNC void AddTM(PlayBack_Time *s,PlayBack_Time *d);
EXTERN_FUNC UINT8 SubTM(PlayBack_Time *s,PlayBack_Time *d);
EXTERN_FUNC UINT8 UOP_check(UINT8 dUOP_code);
EXTERN_FUNC UINT32 GetDisplayTime(UINT8 get_md);
EXTERN_FUNC void GetCellTime(UINT8 cn,UINT32 *s);
EXTERN_FUNC void GetCellTm(UINT8 cn,PlayBack_Time *CellTime);
EXTERN_FUNC void AddTM3(PlayBack_Time *s,PlayBack_Time *d1,PlayBack_Time *d2);
EXTERN_FUNC UINT32 AddTM2S(PlayBack_Time *s,PlayBack_Time *d,UINT32 offset);//terry,2-5-15 18:21
EXTERN_FUNC void nav_param_by_user(void);
EXTERN_FUNC UINT8 get_angle_Ns(void);
EXTERN_FUNC UINT16 get_tt_info(UINT8 md);

EXTERN_FUNC UINT8 *get_audio_mode(void);
EXTERN_FUNC UINT8 *get_lang_name(int mode);
#ifdef NO_DTS_AUDIO_STREAM //axel 2005/6/3 
EXTERN_FUNC void dvdn_chg_dts2ac3(void);//axelchen 2005/6/3 
#endif
// RSM
void RSM_clear(void);
void RSM_save(UINT8,int);
void RSM_restore(void);
#ifdef ONE_KEY_PASS//zhaoyanhua add 03-10-18 16:50
UINT16 SearchMainTitle(void);
#endif//end ONE_KEY_PASS

#endif //__USER_IF_H

