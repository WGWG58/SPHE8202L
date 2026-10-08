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


#ifdef IC_8104A 
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


UINT32 get_play_start_address(void){return 0;}






#endif // 8104

