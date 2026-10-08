/*************************************************************
** FILE
** fsmidiui_prog.h
**
** DESCRIPTION
** the headfile of fsmidiui_prog.c 
**
**
** Create:   xlluo
** Maintain:
**             xlluo 2005/05/31: create
**             
***************************************************************/

#ifndef __INCLUDE_FSMIDIUI_PROG_H__
#define __INCLUDE_FSMIDIUI_PROG_H__

#ifdef EXTERN_MIDIUI_PROG_HERE
#define EXTERN_FSMIDI_PROG
#else
#define EXTERN_FSMIDI_PROG extern 
#endif //end #ifdef EXTERN_MIDIUI_HERE
//include

//marco
#ifdef SUPPORT_MIDI_MENU_SEL
#define SUPPPORT_MANVOL_FLAG    //disp voltip when disp songname
#endif//SUPPORT_MIDI_MENU_SEL

#ifndef SUPPORT_MULTILANGUAGE_MIDIMENU
#define STR_SEARCHSONGFAIL  "ÎÞ´Ë¸èÇú"  //xlluo 
#endif
//global

//function
EXTERN_FSMIDI_PROG void Clear_TopTip(void);

#ifdef SUPPORT_DISPQXQ_STOP  
EXTERN_FSMIDI_PROG void Disp_SelectSongFlag(void);
#endif

EXTERN_FSMIDI_PROG void SJScroeMenuSelect(BYTE cursel);
EXTERN_FSMIDI_PROG void DrawDKSUI();
EXTERN_FSMIDI_PROG void DrawLTSUI();
EXTERN_FSMIDI_PROG char * SetScoreGalaStr(int score);
EXTERN_FSMIDI_PROG int ScoreDelay(void);
EXTERN_FSMIDI_PROG void SJShowScoreNum(void);
EXTERN_FSMIDI_PROG inline int SetPinyingDelay(void);
EXTERN_FSMIDI_PROG void Disp_Programme(UINT32 Num);
EXTERN_FSMIDI_PROG void DispLineNum(UINT16 StartX, UINT16 StartY, UINT32 DispNum, BYTE regNo,
                                                 BYTE FontColor, BYTE BgColor);
EXTERN_FSMIDI_PROG void MidiUI_Draw_NUM_Sel(UINT8 num);
EXTERN_FSMIDI_PROG void MidiUI_Draw_QXQ(void);
#ifdef SUPPORT_CARDREADER_TEST
EXTERN_FSMIDI_PROG BYTE DispSongName(int IsSong);
#else
EXTERN_FSMIDI_PROG BYTE DispSongName(BYTE IsSong);
#endif
EXTERN_FSMIDI_PROG void Disp_TopTip(UINT16 uTimeOut);


#endif//__INCLUDE_FSMIDIUI_PROG_H__

