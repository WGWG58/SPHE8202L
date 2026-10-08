#ifndef DIVX6_ATOM_PARSER_H
#define DIVX6_ATOM_PARSER_H

#include "stc.h"

int divx6_parse_tran_Atom(void);
int divx6_parse_trlk_Atom(void);
int divx6_parse_trtb_Atom(void);
int divx6_parse_chap_Atom(void);
int divx6_parse_titl_Atom(void);
int divx6_parse_mntk_Atom(void);
int divx6_parse_asac_Atom(void);
int divx6_parse_stac_Atom(void);
int divx6_parse_actn_Atom(void);
int divx6_parse_medt_Atom(void);
int divx6_parse_meds_Atom(void);
int divx6_parse_mdia_Atom(void);
int divx6_parse_bntx_Atom(void);
int divx6_parse_mntx_Atom(void);
int divx6_parse_ply0_Atom(void);
int divx6_parse_play_Atom(void);
int divx6_parse_mrec_Atom(void);
int divx6_parse_bmen_Atom(void);
int divx6_parse_wmen_Atom(void);
int divx6_parse_lgmn_Atom(void);
int divx6_parse_menu_Atom(void);
int divx6_parse_Atom_ExtractID(UINT32 uCurrentFCC,UINT32 uSearchingID);

#endif

