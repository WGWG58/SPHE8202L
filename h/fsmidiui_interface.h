//
// fsmidi.h
//
// notes:
//
// history:
//  2005/01/23  : create(xlluo)
//

#ifndef __FSMIDIUI_INTERFACE_H__
#define __FSMIDIUI_INTERFACE_H__

#ifdef SUPPORT_MIDI_MENU_SEL
#ifdef EXTERN_MIDIUI_INTERFACE_HERE
#define EXTERN_FSMIDI_INTERFACE
#else
#define EXTERN_FSMIDI_INTERFACE extern 
#endif //end #ifdef EXTERN_MIDIUI_HERE

//relase modules

#ifdef SUPPORT_FSMIDIUI_RELEASE
#ifdef MIDI_MENU_FONT
EXTERN_FSMIDI_INTERFACE void Clear_TopTip(void);
EXTERN_FSMIDI_INTERFACE void Menu_Draw_TopTip(BYTE AttentionType, UINT32 NUM);
#endif

#ifdef SUPPORT_RELEASE_NUMINPUTUI
#ifdef SUPPORT_DISPQXQ_STOP  
EXTERN_FSMIDI_INTERFACE void Disp_SelectSongFlag(void);
#endif
EXTERN_FSMIDI_INTERFACE void MidiUI_Draw_QXQ(void);
EXTERN_FSMIDI_INTERFACE void MidiUI_Draw_NUM(UINT32 DispNum);
#endif

#ifdef MIDI_MULTI_MENU
#ifdef SUPPORT_RELEASE_DRAWBOTTOMEXTRATIP
EXTERN_FSMIDI_INTERFACE void Menu_Clear_BottomExtraTip(void);
EXTERN_FSMIDI_INTERFACE void Menu_Draw_BottomExtraTip(void);
#endif

#ifdef SUPPORT_RELEASE_MAINMENUCONTENT
EXTERN_FSMIDI_INTERFACE void Menu_Draw_ListItem(const Search_S* dispmsg);
#endif

#ifdef SUPPORT_SANJING_SCORE
#ifdef SUPPORT_RELEASE_SCOREFRAME
EXTERN_FSMIDI_INTERFACE void SJScroeMenuSelect(BYTE cursel);
#endif
#endif

#ifdef SUPPORT_MIDIUI_IME
#ifdef SUPPORT_RELEASE_IMEINTERFACE
EXTERN_FSMIDI_INTERFACE void Ime_DrawRunTimePy(BYTE* pinyin);
//#ifdef SUPPORT_PINYINGDELAY//xlluo delete this releasefunc
//EXTERN_FSMIDI_INTERFACE void Ime_StartInputDelay(const char * strpy);
//#endif//SUPPORT_PINYINGDELAY
#endif//SUPPORT_PINYINGDELAY
#endif//SUPPORT_MIDIUI_IME

#ifdef SUPPORT_RELEASE_MENUFRAME
EXTERN_FSMIDI_INTERFACE void Menu_Draw_BottomTip(BYTE TYPE, BYTE En);
EXTERN_FSMIDI_INTERFACE void MultiSel_DrawMenuTip(BYTE iTipType);
EXTERN_FSMIDI_INTERFACE void Midi_MultiSel_MenuFrame(void);
#endif
#endif//MIDI_MULTI_MENU
#endif

#define STR_SEARCHSONGFAIL  "Œﬁ¥À∏Ë«˙"  //xlluo 

#ifdef SUPPORT_FSMIDIUI_RELEASE

//all use defined
#define MENU_TITLE_FONT_WIDTH   (0x40)
#define MENU_TITLE_FONT_HIGHT   (0x40)
#define MENU_TITLE_NUM_WIDTH    (0x2f)
#define MENU_TITLE_NUM_HIGHT    (0x60)
#define MENU_TITILE_X_START     ((MIDI_MENU_REGION-(3*MENU_TITLE_FONT_WIDTH))>>1)
#define MENU_TITILE_Y_START     (180-((MENU_TITLE_FONT_HIGHT)<<1))
#define MENU_NUM_X_END          ((MIDI_MENU_REGION-(MENU_TITLE_NUM_WIDTH*5))>>1)+(MENU_TITLE_NUM_WIDTH*5)
#define MENU_NUM_Y_START        (180) 


//the folowing is tip's coordinate
#define MENU_TOPTIP_TOPLINE             (0)
#define MENU_TOPTIP_BOTTOMLINE      (30)
#define MENU_BOTTOMTIP_LINE             (210)
#define MENU_BOTTOMTIP_PREVPAGESTARTX   (160)
#define MENU_BOTTOMTIP_NEXTPAGESTARTX   (260)
#define MENU_BOTTOMTIO_EXTRASTRATX          (360)



#ifdef SUPPORT_MIDIUI_IME

#define IME_PY_STR_MAX (16)

#ifndef SUPPORT_MULTILANGUAGE_MIDIMENU
#ifdef SUPPORT_SANJING_LYRIC_SPEC
#define IME_SEARCH_STR ("«Î ‰»Î∏Ë«˙ ◊◊÷ƒ∏")
#else
#define IME_SEARCH_STR ("«Î ‰»Î£∫")
#endif
#endif
#if 0 //def SUPPORT_MIDIUI_IME
UINT8 nManMenuTitle = MENU_ITEM_NUM;
#endif
#endif

enum
{
    MENU_SEARCH_RECORDTYPE_SONGINFO             = 0x01,
    MENU_SEARCH_RECORDTYPE_SONGNAMENUM          = 0x02,
    MENU_SEARCH_RECORDTYPE_SINGERNAMENUM        = 0x04,
    MENU_SEARCH_RECORDTYPE_SINGERCODE           = 0x08,
    MENU_SEARCH_RECORDTYPE_SINGERTYPE           = 0x10,
    MENU_SEARCH_RECORDTYPE_LANGUAGETYPE         = 0x20,
    MENU_SEARCH_RECORDTYPE_SONGTYPE             = 0x40,
    MENU_SEARCH_RECORDTYPE_MENUTYPE             = 0x80,
};

enum
{
    MENU_SEARCH_MENUDGREE_MAINMENU      = 1,
    MENU_SEARCH_MENUDGREE_MENU1,
    MENU_SEARCH_MENUDGREE_MENU2,
    MENU_SEARCH_MENUDGREE_MENU3,
    MENU_SEARCH_MENUDGREE_MENU4,
    MENU_SEARCH_MENUDGREE_MENU5,
    MENU_SEARCH_MENUDGREE_MENU6,
    MENU_SEARCH_MENUDGREE_MENU7,
};

enum
{
    MENUTIP_MAINMENU        = 0,
    MENUTIP_PLAYLIST,
    MENUTIP_ADVANCE_SEARCH,
    #ifdef SUPPORT_MIDIUI_IME
    MENUTIP_IME_SEL,
    #endif
    #ifdef SUPPORT_SANJING_SCORE
    MENUTIP_SANJIN_SCORE,
    #endif
    #ifdef SUPPORT_MULTILANGUAGE_MIDIMENU
    MENUTIP_LANG_SEL,
    #endif
    #ifdef SUPPORT_CARDREADER_TEST
    MENUTIP_CARDREADER,            
    #endif 
    MENUTIP_OTHER,
};

enum
{
    MENU_BOTTOMTIP_NEXTPAGE,
    MENU_BOTTOMTIP_PREVPAGE,
};

//for the xoffset of the ICON
#define FOLDER_XOFFSET (14)
#define MIDI_XOFFSET (0)
#define MP3_XOFFSET (2)

//the following is for main menu frame macro
#define FOR_PLAYLIST (50)
#define FOR_DOT_OFFSET (20)
#define MENU_CHAR_COLOR         (2)
#define MENU_BACKGROUND_COLOR  (13)
#define MENU_LINE_COLOR             (1)
#define MENU_MENU_STARTX       (FOR_PLAYLIST+FOR_DOT_OFFSET) 
#define MENU_MENU_STARTY       (0)
#define MENU_MENU_WIDTH         (MIDI_MENU_REGION -(100+((FOR_DOT_OFFSET)<<1)))
#define MENU_MENU_HEIGHT        (MIDI_MENU_HEIGHT)
#define MENU_HELPAREA_WIDTH         (90-FOR_DOT_OFFSET)
#define MENU_STATICAREA_HIGHT       (LYRIC_FONT_HIGHT-38)
#define MENU_LISTARET_WIDTH           (428)
#define MENU_FONT_WIDTH (30)
#define MENU_STATICAREA_STARTX    (MENU_HELPAREA_WIDTH+MENU_MENU_STARTX)
#define MENU_LISTAREA_STARTX        (MENU_STATICAREA_STARTX)
#define MENU_LISTAREA_STARTY        (MENU_STATICAREA_HIGHT)

#define MENU_LISTMENU_LINEHEIGHT (32)
#define MENU_LISTMENU_STRROW_STARTX (MENU_LISTAREA_STARTX+3+MENU_FONT_WIDTH)
#define MENU_LISTMENU_STRROW_STARTY (MENU_LISTAREA_STARTY+5)

#define MENU_PLAYLIST_BUTTON_XSTART (MENU_LISTMENU_STRROW_STARTX + 200-2)
#define MENU_PLAYLIST_BUTTON_XEND (MENU_PLAYLIST_BUTTON_XSTART+180+2)
#define MENU_PLAYLIST_BUTTON_YSTART  (206)
#define MENU_PLAYLIST_BUTTON_YEND (238)

extern const BYTE listRectLineY[MAX_SEL_LIST];
#ifdef JIEKE_LINEFLAG
extern const  char flag_left[];
extern const  char flag_right[];
#endif
#ifdef SUPPORT_SANJING_SCORE
enum{
            SCORE_SW =0,
            SCORE_LEVEL,
            SCORE_VOLUME,
#ifdef  SUPPORT_SPICALSCORE
            SCORE_LTS,
            SCORE_DKS,
#endif
#ifdef  SUPPORT_RANDOMSCORE                       //xlluo 04-11-12
            SCORE_READOM,
#endif
            SJSCORETITLENUM,
        };


//#ifdef SUPPORT_SPICALSCORE
//#define SCOREMENUITEMS              (5)
//#else
//#define SCOREMENUITEMS              (3)
//#endif

extern int SJCurCnt;
extern BYTE* SJScoreMenuTitle[SJSCORETITLENUM];//xlluo  modify SCOREMENUITEMS];
extern BYTE *SJStartScoreLine[];
#endif
//#endif //MIDI_MULTI_MENU

//extern BYTE ran_read(UINT8* ptr, UINT32 msf, UINT32 len);
//extern UINT32 get_rtc_val();
//extern void LyricSetColor(BYTE color, BYTE regNum);
//extern void osd_midi_init(void);
extern int Disp_Text_OSD(int xx, int yy, BYTE* Lyric, BYTE regNum, int margin,
    BYTE uFontBase, BYTE FontType,int endXEdge);
//extern void Disp_one_vertline(int xx, int yy, UINT16 height, UINT16 columns,
 //   BYTE regNum);
//extern void ClearOsdMsg(int i);
extern void ClearOSDStrLine(UINT16 fwidth, UINT16 Xstart, UINT16 Ystart,
    BYTE regNum);
extern void draw_midi_bitmap_HZnew(const BYTE* pFont, int xStart, int yStart,
    BYTE fontcolor, BYTE bgcolor, BYTE  FigureColor, BYTE FontType,
    BYTE number);
//extern void osd_midi_DrawHZ_Mem(int xStart, int yStart, UINT16 c,
 //   BYTE fontcolor, BYTE bgcolor, BYTE FigureColor, BYTE FontType,
//BYTE number, BYTE FontBaseNo) ; 
extern void osd_Clear_Region(BYTE reg, BYTE bkColor);
extern void Osd_Clear_Rect(int xx, int yy, int xlen, int ylen, BYTE colour,
    BYTE regNum);
//extern void SetIDETimeOut(UINT32);
//extern void init_midi(void);
//extern UINT16 Is_MIDI_STATE(void);
//extern void invalid_key(void);

#ifdef MIDI_MENU_FONT
extern void MidiSetMenuFontColor(BYTE FontColor, BYTE BgColor,
    BYTE FigureColor);
#ifdef MIDI_MULTI_MENU
//int Draw_PlayList(UINT16 uCodePos);
void Draw_SelectFlag(BYTE line, BYTE Enable, UINT16 xOffset);
#endif//MIDI_MULTI_MENU
#endif//MIDI_MENU_FONT

#ifdef MIDI_MULTI_MENU
extern void midi_menu_draw_arc_region(int xStart, int yStart, int xLen,
    int yLen, BYTE regNum, BYTE Enable);
extern void Midi_Draw_Rect(int xx, int yy, UINT16 xLen, UINT16 yLen,
    BYTE BgColor, BYTE FrontC, BYTE FigC, BYTE regNum);
//extern void osd_draw_button_outline(int x1, int y1, int x2, int y2, int bDown,
 //   unsigned mask, int r);
extern void osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd,
    UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r);
#endif//MIDI_MULTI_MENU


#ifdef SUPPORT_MULTILANGUAGE_MIDIMENU
//int         current_midi_osd_lang;
//do not modify xlluo 050303
//xlluo add for submenutitle 
#define MULTILANG_OTHERMENUTITLE_NUM    24
extern const int MULTILANGOTHERMENUTITLENUM;// = MULTILANG_OTHERMENUTITLE_NUM;
extern const  BYTE *MultiLang_OtherSubMenuTitle[][MULTILANG_OTHERMENUTITLE_NUM];


#define NONE_ITEM           18 
#define LANGUAGEITEMS                               2
#define MULTILANG_SUNMENUTITLE_NUM    19
#define MENU_WORD_NUM   65+4//+4 add by xlluo 05-3-17 for caption disp
#define RANDOM_PLAY         1
#define SEQUENCE_PLAY       2
#define PY_INPUT                    64
#define WORD_MULTISORTFLAG  47
#define SONGNAME            5
#define ADD                 6
#define INVALID             7
#define NO_PREPAGE          8
#define NO_NEXTPAGE         9
#define SEL_PLAYING         10
#define SONGLIST_FULL       11
#define DEL_SONG            12
#define SHIFT_SONG          13
#define NO_DEL_PLAYINGSONG  14
#define LEVER_BINGGER           58
#define LEVER_FAMILIARITY   59
#define LEVER_NORMAL            60
#define LEVER_EXPERT            61
#define LEVER_MASTER            62
#define PRE_PAGE            15
#define NEXT_PAGE           16
#define MAIN_MENU_M         21
#define MAIN_MENU_E         22
#define RANDOM_PLAY_OPEN    19
#define SEQ_PLAY_CLOSE      20
#define MAIN_MENU_N         23 
#define MAIN_MENU_U         24
#define PLAYLIST_L          25
#define PLAYLIST_I          26
#define PLAYLIST_S          27
#define PLAYLIST_T          28
#define ADV_SEARCH_S        29
#define ADV_SEARCH_E        30
#define ADV_SEARCH_A        31
#define ADV_SEARCH_R        32
#define ADV_SEARCH_C        33
#define ADV_SEARCH_H        34
#define PINYING_FIND_F      35
#define PINYING_FIND_I      36
#define PINYING_FIND_N      37
#define PINYING_FIND_D      38
#define SCORE_SET_S         39
#define SCORE_SET_C         40
#define SCORE_SET_O         41
#define SCORE_SET_R         42
#define SCORE_SET_E         43
#define WORD_INVIALIDNUM    49
#define CAPTION_MELODY                    65
#define CAPTION_LYRIC                        66
#define CAPTION_SINGER                    67
#define CAPTION_PERFORMER              68

enum{
    CHINESE = 0,
    ENGLISH,
};

#define MAINMENU_ITEM_SONGNAME  0
#define MAINMENU_ITEM_SINGERNAME 1

#define MAINMENU_ITEM_PYSEARCH 2

#define MAINMENU_ITEM_SINGERTYPE 3
#define MAINMENU_ITEM_LANGUAGE 4
   
#define MAINMENU_ITEM_SONGTYPE 5

#define MAINMENU_ITEM_SONGWITHVOICE 6
#define MAINMENU_ITEM_ADVSEARCH 7
#define MAINMENU_ITEM_ALLSONG 8
  
#define MAINMENU_ITEM_PLAYSHUFF 9
#define MAINMENU_ITEM_PLAYORDER 10
#define MAINMENU_ITEM_PLAYBYLIST 11

#define MAINMENU_ITEM_SELECTSONGNUM 12
   

#define MAINMENU_ITEM_SCORESET 13

#define MAINMENU_ITEM_LANGUAGESET 14
#define MAINMENU_ITEM_READCARD 15
//#define  MENU_ITEM_NUM 15

extern const BYTE* LangSelMenuTip[LANGUAGEITEMS][4];
extern const BYTE* LanguageMenuTitle[LANGUAGEITEMS][LANGUAGEITEMS];//xlluo modify//xlluo modify again 05-2-28
//extern const BYTE MainMenuTitleCode[MENU_ITEM_NUM];
extern const BYTE* MainMenuTitle[][MENU_ITEM_NUM];
extern const BYTE* MainTitle[LANGUAGEITEMS][MENU_WORD_NUM];
extern const BYTE *MultiLang_SubMenuTitle[LANGUAGEITEMS][MULTILANG_SUNMENUTITLE_NUM];

#endif//SUPPORT_MULTILANGUAGE_MIDIMENU

#endif//SUPPORT_FSMIDIUI_RELEASE
#endif //SUPPORT_MIDI_MENU_SEL
#endif //__FSMIDIUI_INTERFACE_H__

