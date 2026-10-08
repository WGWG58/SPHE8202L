/*************************************************************
** FILE
** fsmidiui_menu.h
**
** DESCRIPTION
** the headfile of fsmidiui_menu.c 
**
**
** Create:   xlluo
** Maintain:
**             xlluo 2005/05/31: create
**             
***************************************************************/
#ifndef __FSMIDIUI_MENU_H__
#define __FSMIDIUI_MENU_H__

#ifdef EXTERN_MIDIUI_MENU_HERE
#define EXTERN_FSMIDI_MENU
#else
#define EXTERN_FSMIDI_MENU extern 
#endif //end #ifdef EXTERN_MIDIUI_HERE
//include

//macro
//*********************************************************
//***********custom function*********************************
//*********************************************************
//enable power and open when play title
#ifdef SUPPORT_MIDIDISK_TITLE
#define SUPPORT_TITLEPLAY_BREAK
#endif

//sanjin request don't disp the played song code
//#define DISABLE_PLAYEDCODEDISP 


#ifdef MIDI_MULTIFONT_LIB //ouyang add 050819
#define ABROADSINGERTYPE
#define ABORADSINGERTYPENUM   (1)
extern BYTE ViteSinger[ABORADSINGERTYPENUM][2];//define in fsmidi_global.c
#endif//MIDI_MULTIFONT_LIB//xlluo 050817
//extern

//global

//function
EXTERN_FSMIDI_MENU void Draw_SelectFlag(BYTE line, BYTE Enable, UINT16 xOffset);
EXTERN_FSMIDI_MENU void Menu_Draw_TopTip(BYTE AttentionType, UINT32 NUM);
EXTERN_FSMIDI_MENU void Menu_Clear_BottomExtraTip(void);
EXTERN_FSMIDI_MENU void Menu_Draw_BottomExtraTip(void);
EXTERN_FSMIDI_MENU int   Draw_PlayList(UINT16 uCodePos);
EXTERN_FSMIDI_MENU void Menu_Draw_ListItem(const Search_S* dispmsg);
EXTERN_FSMIDI_MENU void Menu_Draw_BottomTip(BYTE TYPE, BYTE En);
EXTERN_FSMIDI_MENU void MultiSel_DrawMenuTip(BYTE iTipType);
EXTERN_FSMIDI_MENU void Midi_MultiSel_MenuFrame(void);
EXTERN_FSMIDI_MENU void MultiLanguage_CheckLang(BYTE * szName,BYTE type,BYTE lang);
EXTERN_FSMIDI_MENU void Menu_Clear_ListArea(void);
EXTERN_FSMIDI_MENU void Draw_SelectFlag(BYTE line, BYTE Enable, UINT16 xOffset);
#ifdef  SEQ_PLAY_SONGID_INTERFACE
EXTERN_FSMIDI_MENU UINT32  MidiGetSeqPlayPos(UINT32 a);
#endif //SEQ_PLAY_SONGID_INTERFACE

#endif//__FSMIDIUI_MENU_H__

