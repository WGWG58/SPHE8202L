/*
*   Terry,2005/7/13 08:22¤U¤È
*/
#include "nav.h"
#include "ncmd.h"
#include "dvdpe_d.h"
#include "dvdpe.h"
#include "osd.h"
#include "cfont.h"
#include "avd.h"
#include "supfunc.h"
#include "user_if.h"

#ifdef SUPPORT_REP_READ  //Maoyong 2004.06.07
#include "read.h"
#endif


#ifdef UNLINK_DVD_NAV_CODE//reduce nav. code. add "dvd_vr_func.c"( = dvd virtual function code file)20050715
/*
*  pgc.c
*/
void PGC_load(void) {};
void load_vts_tmapti(void){};
void get_subp_plt(__UNUSED UINT8 *p){};
UINT32 PreFetchNextVobuAddr(UINT32 uArgument) {return 0;}
UINT8 RunNvCmd(__UNUSED UINT16 state) {return 0;}
void PGC_play(void){};
void PGC_post(void){};
UINT8 IS_PGPlayed(__UNUSED UINT8 n){return 0;}
void SET_PGPlayed(__UNUSED UINT8 n) {};
void RESET_PGPlayed(void){};
void TestIsPGPlayed(void){};
UINT8 SELECT_PGPlayed(void){return 0;};
void GetPrgTime(void){};
void PG_play(void){};
int CellShift(__UNUSED int cn,__UNUSED UINT8 *angle) {return 0;};
void CorrectAngleCell(__UNUSED UINT8 shift) {};
void SearchPG(void){};
void CELL_play(void){};
void CELL_post(void){};
void PE_init(__UNUSED UINT8 load_pgc){};
void decode_tm(__UNUSED UINT8 *p,__UNUSED PlayBack_Time *tm){};
void is_exist_hl(void){};
void sel_subtitle2(__UNUSED UINT8 *level,__UNUSED BYTE selmode){};
UINT16 Parental_ID_Acq(__UNUSED UINT8 vtsn) {return 0; };
void Select_ASTN(__UNUSED BYTE selmode){};
UINT8 Parental_BMg(__UNUSED UINT8 *p)  {return 0;};
void Select_SPSTN(__UNUSED BYTE selmode){};
void sel_audio_language(__UNUSED UINT8 *level,__UNUSED UINT16 *id,__UNUSED UINT8 selmode){};
void PE_play(void){};
void sel_disp_sp_ch(__UNUSED UINT16 id){};

/*
*  vmg.c
*/
UINT8 VMG_Find_Menu(__UNUSED UINT16 dPGCN,__UNUSED  UINT8 dMenuID) {return 0;};
void VMG_Find_TT(__UNUSED INT16 dTTN) {};
UINT8 VMG_Load_VMGI(void) {return 0;};
void VMG_Load_TT_SRPT(void) {};
void VMG_Load_PTL_MAIT(void){};


/*
*  user_if.c
*/
int is_dvd_menu(void) {return 0;}
int is_aspect_menu(void) {return 0;}
void rep_run_the_menu(void) {};
UINT16 get_tt_info(__UNUSED UINT8 md) {return 0;}
UINT8 get_tt(void){return 0;}
UINT8 get_angle_Ns(void) {return 1;};
UINT8 Stop(void) {return 1;}
int get_current_angle_no(void) {return 1;}
UINT8 Angle_Chg(__UNUSED UINT8 action,__UNUSED int step){return 1;}
UINT8 PG_Search(__UNUSED UINT8 n_p){return 0;}
UINT8 force_rep_all_search_next_trk( __UNUSED UINT16 *ptt, __UNUSED UINT8 *chg_tt) {return 0;};
UINT8 is_ptt_search(void){return 0;}
UINT8 is_time_search(void){return 0;}
UINT32 get_play_start_address(void) {return 0;}
UINT8 Time_Play(void){return 0;}
UINT8 ChkPTTRange(__UNUSED UINT8 *tt,__UNUSED UINT16 *ptt) {return 0;}
UINT8 PTT_Play(__UNUSED UINT8 ttn,__UNUSED UINT16 pttn,__UNUSED UINT8 checkUOP){return 0;}
UINT8 Menu_Call(__UNUSED UINT8 MenuID) {return 0;}
UINT8 Resume(void) {return 0;}
UINT32 DesignationCN(__UNUSED UINT8 *cn,__UNUSED UINT32 ts){return 0;}
UINT8 CmpTM(__UNUSED PlayBack_Time *s,__UNUSED PlayBack_Time *d){return 0;}
void AddTM(__UNUSED PlayBack_Time *s,__UNUSED PlayBack_Time *d){};
UINT32 AddTM2S(__UNUSED PlayBack_Time *s,__UNUSED PlayBack_Time *d,__UNUSED UINT32 offset) {return 0;}
UINT32 TM2S(__UNUSED PlayBack_Time *s){return 0;}
void S2TM(__UNUSED UINT32 s,__UNUSED PlayBack_Time *d){};
void TM2TM(__UNUSED UINT8 *s,__UNUSED UINT8 *d){};
void GetCellTime(__UNUSED UINT8 cn,__UNUSED UINT32 *s){}
void GetCellTm(__UNUSED UINT8 cn,__UNUSED PlayBack_Time *CellTime){}
UINT16 Audio_stream_Chg(__UNUSED UINT8 action,__UNUSED int step) {return 0;};
void get_dvd_audio_mode(void){};
UINT8 *get_dvd_lang_name(__UNUSED int mode) {return 0;};

/*
* nav.c
*/
void dvd_hl_force_action(void) {};
int dvd_navigation(void){return 0;};
void polling_dvd_timer(void){};
void nav_param_by_user(void){};
UINT8 DVD_show_time(void){return 0;};
void DVD_get_time(__UNUSED int i) {};
void GetOffsetLba(__UNUSED UINT32 *lba,__UNUSED UINT32 abs){};

/*
* vts.c
*/ 
void VTS_Find_PGC(__UNUSED UINT8 get_new_vts_info){};
UINT8 VTS_Load_VTSI(void){return 0;};
void VTS_Find_PTT(__UNUSED UINT8 SearchPGN){};

/*
* ncdm_exe.c
*/
void NCMD_exec_RSM(int i)
{
    resumeMSF = pDSV->rsm_info[i].dRSM_NV_PCK;
}

void RSM_save(UINT8 domain,int i)
{
    pDSV->rsm_info[i].dRSM_NV_PCK = s_msf;
}


#endif // 8104
