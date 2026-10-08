
#ifndef __FS_MIDI_UI__ 
#define __FS_MIDI_UI__

#include "memmap.h"
#include "memmap0.h"
#include "user_init.h"
#include "fsmidi.h"

#ifdef SUPPORT_MIDI_MENU_SEL
#ifdef EXTERN_MIDIUI_HERE
#define EXTERN_FSMIDI_UI
#else
#define EXTERN_FSMIDI_UI extern 
#endif //end #ifdef EXTERN_MIDIUI_HERE
//#define SUPPORT_DISPQXQ_STOP
#define SUPPORT_SCANMODE_SWITCH         //xlluo add 04-6-14 
#ifdef SUPPORT_SCANMODE_SWITCH
#define MENU_REGION_PAL_X       (20)
#define MENU_REGION_PAL_Y       (36)
#define LYRIC_REGION_PAL_X      (20)
#define LYRIC_REGION_PAL_Y      (280)
#define MENU_REGION_PAL_W       (MIDI_MENU_REGION)
#define MENU_REGION_PAL_H       (MIDI_MENU_HEIGHT)
#define LYRIC_REGION_PAL_W      (MIDI_LYRIC_REGION)
#define LYRIC_REGION_PAL_H      (MIDI_LYRIC_HEIGHT)
EXTERN_FSMIDI_UI void SwitchRegionTVformat();
#endif//SUPPORT_SCANMODE_SWITCH



#define SUPPORT_VFD_SONGCODE
#ifdef SUPPORT_VFD_SONGCODE
typedef struct _stCurPlaySong{
                    BYTE bIsNeedRefresh;//1//1: need reflesh 0:no need
                    BYTE songCode[6];
                 }stCurPlaySong;
EXTERN_FSMIDI_UI void CleanCurplaySongCode(void);
EXTERN_FSMIDI_UI stCurPlaySong curPlayingSong;
EXTERN_FSMIDI_UI void GetCurplaySongCode(void);   //wsf 20040603
#endif

// *****************************************************************
// *** Define the discontiguous serial number FUNCTION for the midi songcode
// *****************************************************************
#define MIDI_SONGCODE_DISCON_NO
// *****************************************************************
// ***user for play sequence songs for none discontiguous serial number
// *****************************************************************

#ifdef MIDI_SONGCODE_DISCON_NO
#define MIDI_SEQUENCE_SEARCHLIST
UINT32 filecode2int(BYTE * );
#endif

// *************************************************************
// *** if dont support the Menu Font , mark the Multi Menu Code
// *** if dont need the Multi Index to search the song, mark it
// *************************************************************
#define MIDI_MULTI_MENU

//as parament of Menu_Draw_Attentiontip(BYTE AttentionType)
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

enum
{
    MENU_TOPTIP_TYPE_SONGNAME =0,
    MENU_TOPTIP_TYPE_SELECTSONG,
    MENU_TOPTIP_TYPE_NOMENUINFO,
    MENU_TOPTIP_TYPE_NOPREVPAGE,
    MENU_TOPTIP_TYPE_NONEXTPAGE,
    MENU_TOPTIP_TYPE_SELECTPLAY,
    MENU_TOPTIP_TYPE_SONGLISTFULL,
    MENU_TOPTIP_TYPE_DELITEM,
    MENU_TOPTIP_TYPE_MOVEITEM,
    MENU_TOPTIP_TYPE_DONTDEL,
    MENU_TOPTIP_TYPE_PROGRAM,
};


// define Menu state 
enum
{
    MENU_INIT                           = 0,
    MENU_SEL,
    MENU_SEL_QXQ,
    MENU_SEL_PROG,
    MENU_SEL_PROGLIST,
    MENU_MULTI_INDEX_SEL,
    MENU_MULTI_INDEX_SEL_PLAYLIST,
    #ifdef SUPPORT_MIDIUI_IME
    MENU_MULTI_INDEX_SEL_IME_SEARCH,
    #endif
    MENU_OTHER,
};

#ifdef SUPPORT_MIDIUI_IME
enum
{
    IME_SEL_INIT   = 0,
    IME_SEL_INPUT ,
    IME_SEL_ENTER,
};
#endif

// define the special play state
enum 
{
    MIDI_NOMAL_PLAY = 0,
    MIDI_RANDOM_PLAY = 9, //set up the value acording to the variable MainMenuTitle
    MIDI_SEQUENCE_PLAY = 10, //set up the value acording to the variable MainMenuTitle
};

#ifdef SUPPORT_MIDIUI_IME
#define IME_PY_STR_MAX (16)

typedef struct {
//	BYTE* startPos;		//the current search start pos
//	BYTE* EndPos;		
	UINT32 startSongID;   // the song id of the first search
       UINT32 EndSongID;  //the song ID follow the current search pos
       BYTE HasPrePage;
       BYTE HasNextPage;
	int  curStrLen;	//the num of according 
	unsigned char PyString[IME_PY_STR_MAX+1];	//cur pystring input by ircontrol
}ImeSearch_S;
#endif

#ifdef SUPPORT_MIDIUI_IME
extern ImeSearch_S stImeSearch;  
#endif

EXTERN_FSMIDI_UI BYTE MenuState;  // menu state
EXTERN_FSMIDI_UI BYTE SpecialPlayState; // special play state

//fsmidi UI osd Color
EXTERN_FSMIDI_UI BYTE LyricFontcolor, LyricBgcolor;
EXTERN_FSMIDI_UI BYTE LyricRevcolour, LyricFigureColor;//osd disp color
EXTERN_FSMIDI_UI BYTE MenuFontcolor, MenuBgcolor, MenuFigureColor;

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


#define MIDIUI_SEL_QXQ_COLOR                6
#define MIDIUI_SEL_QXQNUM_COLOR             6
#define MIDIUI_SEL_QXQCUE_COLOR             6
#define MIDIUI_SEL_PROGRAM_COLOR            5

#ifdef SANJING_MIDI_DVD  //ouyang 2004-12-8 14:44
#define MIDIUI_SEL_PRGNUM_NEXTPLAY_COLOR    4//__
#define MIDIUI_SEL_PRGNUM_WILLING_COLOR     12//7
#define MIDIUI_SEL_PY_BOTTOMTIP_COLOR        7
#define MIDIUI_SEL_PRGNUM_PERV_COLOR        2//6
#else
#define MIDIUI_SEL_PRGNUM_NEXTPLAY_COLOR    2
#define MIDIUI_SEL_PRGNUM_WILLING_COLOR     7
#define MIDIUI_SEL_PRGNUM_PERV_COLOR        6
#endif

#define MIDIUI_SEL_MOVE_BGCOLOR             4
#define MIDIUI_SEL_MOVE_FONTCOLOR           2
#define MIDIUI_SEL_BGCOLOR                  0


#ifdef SANJING_MIDI_DVD  //ouyang 2004-12-8 14:44
#define MIDIUI_SEL_TOPTIPCOLOUR              6// 7
#define MIDIUI_SEL_PROGRAMNUM                6//7
#else
#define MIDIUI_SEL_TOPTIPCOLOUR               7
#define MIDIUI_SEL_PROGRAMNUM                 7
#endif

#define MIDIMULTIUI_SEL_PALYEDFILE          3

//for menu color 
#define MENU_BACKGROUND_COLOR  (13)
#define MENU_LINE_COLOR             (1)


#define MAX_SEL_LIST (6)
#define MAX_SEARCH_PAGE (50)  //equal to the total num of SongInfo record

#ifdef SUPPORT_CARDREADER_TEST
#define MENU_ITEM_NUM 16
#else
#define MENU_ITEM_NUM (15)
#endif
#define MIDINDEX_SONGINFO_FLAG      (0x01)
#define MIDINDEX_SONGNAMEWORDSUM_FLAG     (0x02)
#define MIDINDEX_SINGERNAMEWORDSUM_FLAG     (0x03)
#define MIDINDEX_SONGTYPE_FLAG      (0x04)
#define MIDINDEX_SINGERCODE_FLAG   (0x05)
#define MIDINDEX_SINGERTYPE_FLAG   (0x06)
#define MIDINDEX_LANGUAGE_FLAG      (0x07)

#ifdef SUPPORT_MULTILANGUAGE_MIDIMENU
//int         current_midi_osd_lang;
//do not modify xlluo 050303
//xlluo add for submenutitle 
#define MULTILANG_OTHERMENUTITLE_NUM    24
extern const int MULTILANGOTHERMENUTITLENUM;// = MULTILANG_OTHERMENUTITLE_NUM;
extern const  BYTE *MultiLang_OtherSubMenuTitle[][MULTILANG_OTHERMENUTITLE_NUM];


#define NONE_ITEM           18 
#ifdef MIDI_MULTIFONT_LIB
#define LANGUAGEITEMS          3//hz fb + extfb = wLibcnt
#else
#define LANGUAGEITEMS                               2
#endif//MIDI_MULTIFONT_LIB    
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

enum {
                STR_OTHER =0,
                //songname
                SONGNAME_ONE_CHAR,
                SONGNAME_TWO_CHAR,
                SONGNAME_THREE_CHAR,
                SONGNAME_FOUR_CHAR,
                SONGNAME_FIVE_CHAR,
                SONGNAME_SIX_CHAR,
                SONGNAME_SEVEN_CHAR,
                SONGNAME_EIGHT_CHAR,
                SONGNAME_NINE_CHAR,
                //singer name
                SINGERNAME_ONE_CHAR,
                SINGERNAME_TWO_CHAR,
                SINGERNAME_THREE_CHAR,
                SINGERNAME_FOUR_CHAR,
                SINGERNAME_FIVE_CHAR,
                SINGERNAME_SIX_CHAR,
                SINGERNAME_SEVEN_CHAR,
                SINGERNAME_EIGHT_CHAR,
                SINGERNAME_NINE_CHAR,
            };

enum{
        CHINESE = 0,
        ENGLISH,
        //JAPANESE,        //not support current
        //RUSSIAN,         //not support current
#ifdef MIDI_MULTIFONT_LIB
        VITENAM,//S:Ô½ÄÏÎÄ
#endif//MIDI_MULTIFONT_LIB    
};


#ifdef  MIDI_MULTIFONT_LIB
#define GETCUROSDLANG()      ((current_midi_osd_lang > 1)?1:0)
#define  LANGINGBLIB    2
#define  LANGLISTCNT    3//6//hz+eg +ext
extern const BYTE SongLangLib[LANGLISTCNT][2];
#define DEFAULT_EXTLANG              (VITENAM)//for test
#endif

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

#define IME_SEARCH_STR      0
#define PLAYLIST_VOID       3
#define NO_SONG             4
#define BEGIN_SEARCH        17
#define PROGRAME_TOPTIP     44
#define DISP_SINGER_NAME         45
#define DISP_SONG_NAME       46
#define WORD_STARTSEARCH    48
#define WORD_SCORE_SWITCH            50
#define WORD_SCORE_LEVEL                 51
#define WORD_VOICE_SWITCH                52
#define RANDOM_SCORE            53
#define WORD_BEGIN_LTS                   54
#define BEGIN_DKS                   55
#define CLOSE_LTG                   56
#define CLOSE_DKG                   57
#define SCORE_STR_YOUNUM    63



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
#ifdef SUPPORT_SANJING_SAVIOP
#define SCOREINFO_ADDR    237          //ouyang change 2005-2-1 11:28 //xlluo add for save score status 
#endif

extern int SJCurCnt;
extern BYTE* SJScoreMenuTitle[SJSCORETITLENUM];//xlluo  modify SCOREMENUITEMS];
extern BYTE *SJStartScoreLine[];
#endif
//extern const BYTE* MainTitle[LANGUAGEITEMS][MENU_WORD_NUM];
//extern const BYTE* LangSelMenuTip[LANGUAGEITEMS][4];
//extern const BYTE* LanguageMenuTitle[LANGUAGEITEMS][LANGUAGEITEMS];

extern const BYTE* LangSelMenuTip[LANGUAGEITEMS][4];
extern const BYTE* LanguageMenuTitle[LANGUAGEITEMS][LANGUAGEITEMS];//xlluo modify//xlluo modify again 05-2-28
//extern const BYTE MainMenuTitleCode[MENU_ITEM_NUM];
extern const BYTE* MainMenuTitle[][MENU_ITEM_NUM];
extern const BYTE* NonSingerStr[LANGUAGEITEMS]; //ouyang add 2005.07.18
extern const BYTE* MainTitle[LANGUAGEITEMS][MENU_WORD_NUM];
extern const BYTE *MultiLang_SubMenuTitle[LANGUAGEITEMS][MULTILANG_SUNMENUTITLE_NUM];

extern const int MULTILANGOTHERMENUTITLENUM;
#endif//SUPPORT_MULTILANGUAGE_MIDIMENU

extern const BYTE listRectLineY[MAX_SEL_LIST];


//for disp menu

//This is the header of the midi index file
typedef struct
{
    BYTE* pSingerType;
    BYTE* pLonguageType;
    BYTE* pSongType;
    BYTE* pSingerCode;
    BYTE* pSongInfo;
    BYTE* pSongWord;     //new
    BYTE* pSingerWord;  //new
    UINT16 SingerNum;   
    UINT16 SongNum;
    UINT16 SongWordNum;    //new
    UINT16 SingerWordNum;    //new
    UINT16 SongNameNumFlag;
    UINT16 SingerNameNumFlag;

    BYTE* pSingerPos;
    BYTE* pSongPos;
    #ifdef MIDI_SONGCODE_DISCON_NO
    BYTE *pNumIndexPos ; 
    #endif
    BYTE* pIndexStart;                 //index start
}MidiIndexTable_S;


//Midi index song info record
typedef struct
{
    BYTE recordFlag;
    BYTE recordLen;
    unsigned songType : 8;
    unsigned languageType : 7;
    unsigned bIsMP3 : 1;
    unsigned songerNo : 12;
    unsigned wordNum : 4;
    UINT16 MidiFileSize;
    UINT32 MidiMsfPos;
    union
    {
        struct
        {
            //UINT32 Mp3MsfPos;//xlluo modify for multifile volfilesupport
#ifdef SUPPORT_DOUBLE_MANVOCALFILE
            union
            {
                struct
                {
                    unsigned pos   : 24;
                    unsigned type : 4;
                }stPos;
                UINT32 msfpos;
            }Mp3MsfPos;
#else
            UINT32 Mp3MsfPos;
#endif
            UINT16 Mp3FileSize;
            char Mp3SongName[58];
        }Mp3Info;
        char MidiSongName[64];
    }SongName;
}SongInfo_S;

typedef struct
{
	BYTE sign;
	BYTE recordlen;
	BYTE wordNum;//
	BYTE c;//
	UINT16 TheSongNum;
	char TypeName[8]; //"(x×Ö¸èÇú)"(8BYTE)
}WordSel_A;

//singer code record
typedef struct
{
    BYTE recordFlag;
    BYTE recordLen;  
    UINT16 SingerSum:12;
    UINT16 wordNum:4;
    BYTE singerType;
    char singerName[1];
}SingerCode_S;

//singer type record
typedef struct
{
    BYTE recordFlag;
    BYTE recordLen;
    UINT16 TypeSum;
    char singerType[1];
}SingerType_S;

//language type record 
typedef struct
{
    BYTE recordFlag;
    BYTE recordLen;
    UINT16 TypeSum;
    char languageType[1];
}LanguageType_S;

//song type record 
typedef struct
{
    BYTE recordFlag;
    BYTE recordLen;
    BYTE songTypeCode;
    UINT16 TypeSum;
    char songTypeName[1];
}SongType_S;

//The following is data struct for search 
//************************************************
//***The following struct must keep data structure size = 4N 
//************************************************
typedef struct
{
    BYTE *pStackBottom ;  //align at the edge of memory addr == 4n
    BYTE *pStackTop ;
    BYTE *pStackEnd ;
}SearchStack_S;


typedef struct 
{
    UINT16 cPageSum;  
    UINT16 cPageNum;
    // the current term for search list
    unsigned TermSongType   : 8;
    unsigned TermLanguageType : 7;
    unsigned TermbIsMP3 : 1;
    unsigned TermSongerNo : 12;
    unsigned TermWordNum  : 4;
    BYTE TermSingerType;
    BYTE TermSingerWordNum;
    BYTE TermValidate; // d0:TermSongType  d1:TermLanguageType d2: TermbIsMP3 d3: TermSongerNo
                                    // d4: TermWordNum d5:TermSingerType d6: TermSingerWordNum
    BYTE bAdvanceItem; //dummy element
}SearchTerm_S;

typedef struct
{
    UINT32 *pPageStart;    //the bottom stack of the current menu,and is the first pos of menu state ;
    BYTE uMaxPage;//*pPageEnd;
    BYTE uOutputQueue;
    BYTE uInputQueue;
    BYTE uRecordType;  //d0: SongInfo d1:songWord d2:singerWord d3:SongType d4: SingerCode 
                                        //d5:SingerType d6:LanguageType  d7:Menu
    BYTE uMenuDegree; //when uRecordType->d5==1 : validate-->d0~d7:the degree of the current menu state
    BYTE uCurPage;        //the current page 
    BYTE uCurPos;          //the current pos in the current list
    BYTE uCurPageItemNum;

    UINT16 cPageSum;  
    UINT16 cPageNum;

    // the current term for search list
    unsigned TermSongType   : 8;
    unsigned TermLanguageType : 7;
    unsigned TermbIsMP3 : 1;
    unsigned TermSongerNo : 12;
    unsigned TermWordNum  : 4;
    BYTE TermSingerType;
    BYTE TermSingerWordNum;
    BYTE TermValidate; // d0:TermSongType  d1:TermLanguageType d2: TermbIsMP3 d3: TermSongerNo
                                    // d4: TermWordNum d5:TermSingerType d6: TermSingerWordNum
                                    
    BYTE bAdvanceItem;     //see enum emMidiMULTIMenuADVItem        //xlluo 04-1-21
#if 0
//00: no advitems
                                          //01: the advsearch invalid
                                          //02: the score menu is showwing   // xlluo redefine for sjscore 04-10-15
 #endif    
    BYTE * CurPageList[MAX_SEL_LIST];   // the current list
    UINT32 uPageItemCode[MAX_SEL_LIST]; //(((MAX_SEL_LIST+3)>>2)<<2)];

    #ifdef SUPPORT_MIDIUI_IME
    UINT8 IsEnablePYsel ;
    UINT8 uImeSelState;
    UINT16 c;   //dummy element
    #endif
}Search_S;  //when push stack , this struct copy to the top stack ;when pop ,copy to this struct 

enum emMidiMULTIMenuADVItem{
                                                    MULTIMIDIADVITEM_NONE =0,
                                                    MULTIMIDIADVITEM_ADVSEARCH,
#ifdef SUPPORT_SANJING_SCORE
                                                    MULTIMIDIADVITEM_SCOREMENU,
#endif                           
#ifdef SUPPORT_MULTILANGUAGE_MIDIMENU
                                                    MULTIMIDIADVITEM_LANGUAGESET,
#endif
#ifdef SUPPORT_CARDREADER_TEST
                                                    MULTIMIDIADVITEM_CARDFILEMENU,
#endif
                                                };

EXTERN_FSMIDI_UI MidiIndexTable_S stMidiIndexTable; 

EXTERN_FSMIDI_UI SongInfo_S stSongInfo;
//end MULTI_SEL_STRUCT



//OSD the song code in region 0
//important note : don't exceed 10

#ifndef JK_LINEFLAG
#define DISP_PROG_MAX (MAX_SEL_LIST) //(6)
#else
#define DISP_PROG_MAX (5)
#endif

//the max number of the ring queue ; 
//important note : don't exceed 0xff ; or else moidify the element uInput and so on to UIN16
 //100 ---> hold the max song code IDs == 99
 #define PROG_MAX (100)   


typedef struct
{
    UINT8 uInput; // =0;                  //queue head
    UINT8 uOutput ; //=0;                //queue tail
    UINT8 uNextPlay;// =0;             //the next song that paly 
//    UINT8 uCurPlay;
    UINT8 uCurPos; //=0;                //the location of the cursor
    UINT16 uDispWindowPos;
    
#ifdef MIDI_SONGCODE_DISCON_NO
    UINT32 buf[PROG_MAX];
#else 
    UINT16 buf[PROG_MAX];
#endif

    UINT8 uLastDispStaus;//[DISP_PROG_MAX]; uDispRecord
    UINT8 uLastDispPos;
}RingBuffer_S;


#ifdef SUPPORT_MIDIDISK_TITLE      //xlluo 09/17 add for the start of movie
EXTERN_FSMIDI_UI PLF_REC MidiTitle;      
#endif
#ifdef SUPPORT_MIDI_VOCAL
//xlluo modify 2005/05/23 add second volfile record
#ifdef SUPPORT_DOUBLE_MANVOCALFILE
EXTERN_FSMIDI_UI PLF_REC MidiIndex[4];//[0]:MEGIDX [1]:MEGMID [2]:MEGVOL [3]:MEGVOL1
#else
EXTERN_FSMIDI_UI PLF_REC MidiIndex[3];//[0]:MEGIDX [1]:MEGMID [2]:MEGVOL 
#endif//SUPPORT_DOUBLE_MANVOLFILE
#else
EXTERN_FSMIDI_UI PLF_REC MidiIndex[2];
#endif

enum{//bIsShowInvalid used
          NOTSHOWINVALID =0,
          SHOWINVALID,
          SHOWNOTHING,
};

EXTERN_FSMIDI_UI BYTE bIsShowInvalid;
EXTERN_FSMIDI_UI RingBuffer_S stRingBuffer;
EXTERN_FSMIDI_UI UINT8 gIsMidiSelMenu;
EXTERN_FSMIDI_UI UINT16 uDelayClearTips;
extern UINT32 ugMidiSelNo;
extern UINT8 ugMidiSelDegree;
extern UINT8 bIsShowProgList;
extern SearchStack_S stSearchStack;
extern Search_S stCurSearch;

extern UINT8 bMouseDown;  //   the Mouse has key down?
extern UINT32 ugMidiSelNo; //  the song ID code from IR KEY
extern UINT8 ugMidiSelDegree;  // the time of keying the NUM IR KEY
extern UINT8 bIsShowProgList ;  // 1: show the proggraming List    0: close the proggramming list
extern UINT8 bEnterAvail;          // The IR key ENTER KEY is available ?
extern UINT8 bIsSJScoreing;   
extern UINT8 current_midi_osd_lang;   
extern UINT32 iMP3loc;

//FILE:fsmidifont.c
extern const char Mp3Icon[];
extern const char MusicNote[];
extern const char *DiskRun[3];
extern const char FoldIcon[];
//extern void MidiUI_Draw_Prog_Sel(UINT8 num);

extern void MidiUI_Init(void);
extern UINT8 MidiUI_Play_Cmd(UINT32 msf, UINT32 len, BYTE bIsMidiFile);
extern void MidiUI_Nav_MainLoop();
extern UINT32 fsMidi_UI_callback_check(UINT32 func);
//extern void InputQueueSongCode(UINT32 q);
extern void DispLine(BYTE bMove,UINT16 uDispStartPos,BYTE bDirection);
///extern void MidiUI_Sel_Right(void);
//extern void MidiUI_Sel_Left(void);
extern void Midi_FS_Init(void); //axelchen for check szMidiLable and iMidiKey 05-01-26

extern void SetMp3FileMsf(void);

#ifdef SUPPORT_PINYINGDELAY
//int iPyDelayTime;
//void Ime_DelayTime(void);
#endif

#endif//end #ifdef SUPPORT_MIDI_MENU_SEL

#if ((defined(MIDI_SONGCODE_DISCON_NO))&(defined(HDD_MODIFY_INDEX_TEST)))
#define SUPPORT_HDD_DELETEFILE
#define USER_SONGCODE_LOWERLIMIT            50000
#define USER_SONGCODE_UPPERLIMIT             60000  
#define DISCONSTFLAG                                       0x09
#define FILEMANAGEUI_PAGEMAXITEM    5

enum{//MIDI_SONGCODE_DISCON_NO error list 
            ERROR_ERRORFLAG_DISCON =1,
            ERROR_REPEAT_CODE,
            ERROR_OVERUPPER_LIMIT,
            ERROR_OVERLOWER_LIMIT,
        };
//#define DEBUG_MIDI_SONGCODE_DISCON_NO

BYTE IsfailCode(int );
void SetDefaultFileInfo(int );
#endif


#if 0//def HDD_MODIFY_INDEX_TEST
#ifdef  SUPPORT_HDD_DELETEFILE
#define ADD_NEWFILE_SEQUENCE
int GetNextNullCell(void);
#define HDD_FILE_MANAGEERUI
void DeleteUserFile(int);
#ifdef  HDD_FILE_MANAGEERUI
#define HDD_RECLAIM_CODECELL                        //xlluo 04-05-14
int fileManageui_IrSelect(void);
int fileManageui_IrReturn(void);
void fileManageui_close(void);
void fileManagerui_IrLeft(void);
void fileManagerui_IrRight(void);
void fileManageui_IrUp(void);
void fileManageui_IrDown(void);
void fileManageui_Init(void);
void Mageui_SetNewFile(BYTE *,int);
int fileManageui_GetSongCode(void);
void Manageui_SetNewFile(BYTE * , int );
void fileManageui_DrawProcessBar(int );
#endif
#endif
#include "HDD_info.h"
#define	D	printf("INFO: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);
#define INDEXFILEPATH ("/")
#define INDEXTITLE  ("MEGIDX     ")
#define INDEXFILE ("/MEGIDX")
#define FONTFILE ("/FONT.FNT")

enum
{
            INPUT_MENU_CLOSE =0,
            INPUT_PART1,
            INPUT_PART2,
            INPUT_PART3,
            INPUT_PART4,
            INPUT_OK,
            INPUT_CANCEL,
            INPUT_COPYING,
        };

typedef struct _stNewFileInfo
{
                                            BYTE SongName[64+1];  //song name maxlen 64 char or 32 hz
                                            BYTE SingerName[24+1];//init to 24 characters/12 hzs
                                            BYTE SongLang[18+1];   //9 hz or 18 char
                                            BYTE SongType[24+1];   //songtype name 
                                            BYTE filename[8+1];       //max is 8 character auto evaluate by program
#ifdef MIDI_SONGCODE_DISCON_NO
        int     songcode;
#endif
                                        }stNewFileInfo; 

EXTERN_FSMIDI_UI stNewFileInfo stFileInfo; 
EXTERN_FSMIDI_UI BYTE cInputStatus;
EXTERN_FSMIDI_UI BYTE cCurSelItem;

EXTERN_FSMIDI_UI int nSingerwrd;
EXTERN_FSMIDI_UI int nSongwrd;



#ifdef MIDI_SONGCODE_DISCON_NO    //wsf  20040603
#define SUPPORT_HDD_DELETEFILE
#define USER_SONGCODE_LOWERLIMIT            50000
#define USER_SONGCODE_UPPERLIMIT             55000  
#define DISCONSTFLAG                                       0x09
        
enum{//MIDI_SONGCODE_DISCON_NO error list 
            ERROR_ERRORFLAG_DISCON =1,
            ERROR_REPEAT_CODE,
            ERROR_OVERUPPER_LIMIT,
            ERROR_OVERLOWER_LIMIT,
        };

#define DEBUG_MIDI_SONGCODE_DISCON_NO

BYTE IsfailCode(int );
void SetDefaultFileInfo(int );
#endif


extern UINT8 bMouseDown;

extern void Osd_Clear_Rect(int xx, int yy, int xlen, int ylen, BYTE colour, BYTE regNum);
extern void osd_midi_DrawHZ_Mem(int xStart, int yStart, UINT16 c, BYTE fontcolor, BYTE bgcolor, BYTE FigureColor, BYTE FontType, BYTE number, BYTE 
FontBaseNo);
extern UINT8 HDD_Mount();
extern FILE_INFO *HDD_SearchFile(UINT8 * );
extern void HDD_WriteSec(UINT8 * , UINT32 , int );

void MidiUI_Sel_Prog(void);
BYTE *get_index_pos();
int SetSingerDefType(BYTE *,int *,int *);
int CountCHSWords(BYTE* );
int UpdataUIindex(void);
BYTE *GetCurStatusStrPtr(BYTE );
void ClearFineInfoMem(BYTE );
int InputChar2NewFileInfo(char *,BYTE );
void SeIdxTypeToFileInfo(BYTE );
int GetIndexStr(BYTE *,BYTE );
UINT8 HasNextItem(BYTE );
void DispName(BYTE );
void DispInputDlg(BYTE ,stNewFileInfo );
void InitInputDlg();
void ReadFontFile();
void PYIME_Disp(BYTE );
int DelOneChFromFileInfo(BYTE );
int SaveIndexFile(int );
void DeleteUserFile(int code);

//for ime
#endif //#ifdef HDD_MODIFY_INDEX_TEST
UINT32 pos_singer[200];//max is 2000//max to 4096 singers
UINT32 pos_song[50];  //max is 5000//max to 10000 songs
#ifdef SUPPORT_CARDREADER_TEST
extern UINT8               ReadFile(int *Res);
extern int                    read_card_dir();

extern int                     iMidiEnFLNum;
extern PLF_REC            stMidiEncFile;

typedef struct{
			BYTE songNum;
			BYTE * fileList;
			}fldecode;

typedef struct  {
		UINT32	 songPos;
		UINT32     songLen;	
		UINT32	  mp3Pos;   //xlluo add mp3 support 2005-2-19
		UINT32     mp3Size;	
	//	BYTE	 songNameCnt;
	//	BYTE	 songnamelen;
		BYTE	 songName[32];		
}encSongInfo;
extern BYTE MidiCardIcon[];

EXTERN_FSMIDI_UI fldecode        stMidiCardIndex;
EXTERN_FSMIDI_UI   int MidiCard_FileRead(int flidx,BYTE * pbuf);
EXTERN_FSMIDI_UI   int MidiCard_DataRead(BYTE * ptr, UINT32 msf, UINT32 len);

EXTERN_FSMIDI_UI void MidiCardReadInit(void);
EXTERN_FSMIDI_UI int    MidiCard_GetCardFile(void);
EXTERN_FSMIDI_UI encSongInfo  stMidiCardSongInfo[13];
#endif//SUPPORT_CARDREADER_TEST//ouyang add 06.03.03
//EXTERN_FSMIDI_UI int GetCurplaySongCode(void);   //wsf 20040603
#endif  //#ifndef __FS_MIDI_UI__



