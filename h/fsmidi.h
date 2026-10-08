//
// fsmidi.h
//
// notes:
//
// history:
//  2003/04/09  : create(Jeff)
//

#ifndef __FS_MIDI_H  
#define __FS_MIDI_H

#include "memmap.h"
#include "memmap0.h"
#include "user_init.h"

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif


//*************************************************************************
//*****                  BEGIN :       The following is main function define                    ******
//*************************************************************************
//***********************************************
//**Add Extern VolFile For D9 MidiDVD DISK
//**xlluo 2005/05/23
//***********************************************
#ifdef SUPPORT_MIDI_VOCAL
#define SUPPORT_DOUBLE_MANVOCALFILE
#ifdef SUPPORT_DOUBLE_MANVOCALFILE
#define DGB_DBLVOLFILE
#endif//SUPPORT_DOUBLE_MANVOLFILE
#endif//SUPPORT_MIDI_VOCAL

//***********************************************
//**Load Midi Multi Font
//**without multilang show in same time
//***********************************************
#define MIDI_MULTIFONT_LIB
#ifdef MIDI_MULTIFONT_LIB
#define DBG_MULTIFONT_LIB
#endif

//***********************************************
//**xlluo add 05/04/22
//**for customer request the ar
//***********************************************
#ifdef SUPPORT_OSDLYRIC
//#define SUPPORT_REVERSE_DISPLAY
#endif//SUPPORT_OSDLYRIC

//***********************************************
//**xlluo add 05/04/26
//**for customer request to clear played song 
//***********************************************
#ifdef SUPPORT_MIDI_MENU_SEL
//#define SUPPORT_CLEAR_INVALUECODE
#endif//SUPPORT_MIDI_MENU_SEL

//*************************************************************************
//***                                  END   :    main function define                                      ****
//*************************************************************************


//added by dtb in 200307022
#ifdef EXTERN_MIDI_HERE
    #define EXTERN_FSMIDI
#else
    #define EXTERN_FSMIDI extern 
#endif

//xlluo 04-9-2
#define SUPPORT_DISPQXQ_STOP
#define SUPPORT_ONTIME_CAPTIONCLEAR
#ifdef SUPPORT_ONTIME_CAPTIONCLEAR
#define CLEAR_DELAYTIMES    (90000<<3)
#define CLEAR_DELAYTIMES_MP3    (90000<<3)
EXTERN_FSMIDI BYTE bIsCaptionDisp;
#endif

#define SUPPORT_INITDELAY
//#define SUPPORT_PLAYTITLE_OPEN_POWER_VALID

//xlluo add 060514
//forbid ir control when read mp3
//for pure music play
EXTERN_FSMIDI BYTE bIsPureMusic;
EXTERN_FSMIDI int cCntClsMusicTitle;
extern void ClsPureMUCaption(void);
#if 0
//xlluo add for 8202 to read from cardreader midi file
#ifdef SPHE8202_CARD_STORAGE
#define SUPPORT_CARDREADER_TEST
#endif//SPHE8202_CARD_STORAGE
#endif//move to cfg.h 04.19

#ifdef SUPPORT_CARDREADER_TEST
EXTERN_FSMIDI BYTE    bIsCardFile;//xlluo add only for test 04-1-21
#endif//SUPPORT_CARDREADER_TEST

// for the midi state for midi player
enum {
    MIDI_STATE_INIT=0,
    MIDI_STATE_PREPARSE,
    MIDI_STATE_PAYLOAD,
    MIDI_STATE_DONE, 
    MIDI_STATE_PLAY_ONLYVIDEO,
};

// recording the location and size of the fs9660 file
typedef struct
{
    UINT32  loc;    // mmssff 
    UINT32  size;   // in Bytes
} PLF_REC;

//midi module variables for external reference
extern UINT32   iByteRemain;
extern UINT32   iMidiPos;
extern BYTE     *pMidi;
extern PLF_REC  *melody, *rhythm;           //melody[128], rhythm[47]
extern PLF_REC  midiMovie[10]; //midiMovie[10]
extern PLF_REC  allPLF;

#ifdef SUPPORT_MIDI_VOCAL
EXTERN_FSMIDI BYTE      bIsMp3LyricSyn;
EXTERN_FSMIDI PLF_REC   *pMidiVocal; //Jeff 20031015
#endif
//EXTERN_FSMIDI UINT8    LyricSyn;//axelchen for midi MP3 sync 2005/9/15

EXTERN_FSMIDI UINT32    midi_timenow,midi_polling_time;
EXTERN_FSMIDI UINT8     Midi_pause_flag;
EXTERN_FSMIDI BYTE      midiState;

//xlluo add for disable the irinput when load disk
//will crash                                                            //04-11-23
EXTERN_FSMIDI BYTE      bHoldInput;
#ifdef SUPPORT_INITDELAY        
EXTERN_FSMIDI BYTE      bInitStatus;//ouyang add for delay 2m show "qing xuan qu"2005.04.20
#endif
EXTERN_FSMIDI BYTE      bLyricSyn;//axelchen//ouyang add 20050922
//**********************************************************************
//******define the interface buffer between the MIDI RISC and MIDI DSP
//**********************************************************************
#define MIDIDSP_INTERFACE_SIZE ((AUDSIZE)-12)
#define MIDIDSP_INTERFACE_BUFFER_ADDR   (SDRAM_BASE + A_AUDYA*1024 + 12*1024)   //put .mid file content, with AUDYA-offset 12KBytes


//**********************************************************************************
//****** define the read buffer on reading the midi file and converting the format1 into format0 
//****** Use the JPEG Buffer as the temporary buffer
//**********************************************************************************
#define MIDIREAD_BUFFER                 (SDRAM_BASE + 1024*(JPEG_YA))
#define MIDIREAD_BUFFER_SIZE            (1024*(JPEG_CDBUF_SIZE))


#ifdef SUPPORT_OSDLYRIC
//define Menu&Lyric Region X and Y
#define MENU_REGION_X   (20)
#define MENU_REGION_Y   (60)
#define LYRIC_REGION_X  (20)
#define LYRIC_REGION_Y  (180)

//define the font base NO. 0: the Lyric font  (40*48)
//                                    1: the Menu font (30*30)
#define MIDI_LYRIC_FONTDEBASE (0)
#define MIDI_MENU_FONTDEBASE (1)
#ifdef SUPPORT_REVERSE_DISPLAY
#define MIDI_REVERDISP_LYRIC    (2)
#endif//SUPPORT_REVERSE_DISPLAY


//define the Lyric font Para for OSD
#define OTHER_FONT_WIDTH                (20)
#define LYRIC_FONT_HIGHT                (40)
#define LYRIC_FONT_WIDTH                (48)
#define LYRIC_FONT_MARGIN               (2)
#define LYRIC_ABC_WIDTH                 (30)
#define LYRIC_NUMFONT_WIDTH             (30)
#define LYRIC_ABC_CAP_WIDTH             (28)
#define MIDI_LYRIC_REGION               (640)

//define these parameter including the OSD region partition
#define MIDI_LYRIC_HEIGHT               (140-50)
#define MIDI_MENU_REGION                (640)
#define MIDI_MENU_HEIGHT                (190+50)
#define LYRIC_YY_LINE0                  (0) 
#define LYRIC_YY_LINE1                  (LYRIC_YY_LINE0+LYRIC_FONT_HIGHT+4)
#define DISP_DOT_REGION                 (REGION2)
#define DISP_DOT_XPOS                   (20)
#define DISP_DOT_LINE                   (200)
#define DISP_LYRIC_REGION               (REGION3)
#define DISP_CAPTION_REGION             (REGION2)

//define midi lyric osd colour table
//----------------------lyric colour--------------------
#define LYRIC_INIT_COLOUR                 2	        //white
#define MAN_REV_COLOUR                       6          //blue
#define WOMAN_REV_COLOUR                10        //red
#define CHROUS_REV_COLOUR               8           //green
//----------------------lyric colour end-----------------

#define TITLE_COLOUR                    10
#define FONT_FIGURE_COLOUR              11
#define FONT_FIGURE_REV_COLOUR          2
#define FONT_BACKGROUND_COLOUR          0
#define DOT_CUE_COLOUR                  2
#define DOT_CUE_REV_COLOUR              10

//xlluo add for gray back on region0
#define SUPPORT_REPREGIONCOL
#ifdef SUPPORT_REPREGIONCOL
void osd_updataRegion_Color(BYTE R,BYTE G,BYTE B,BYTE A,BYTE code,BYTE regNum);
#endif

//the following is the memory allocation for the Midi Player
//should be 4N for memory allocation
#define MAXLYRICDATALEN                 (5120)
//define the max ff05 event number
#define MAXLYRICEVENT                   (2500)

//sizeof(LyricPos)
#define LYRIC_DATA_BUFFER_SIZE          (((MAXLYRICEVENT)*(sizeof(LyricPos)))+(MAXLYRICDATALEN)+1024)               //1000*20+2048+1024
#ifdef SUPPORT_TWENTY_THOUSAND_DISC  //ouyang add for support 20k disc 05.09.07
#define MIDI_INDEX_BUFFER_SIZE          ((600)<<(10))
#else
#define MIDI_INDEX_BUFFER_SIZE          ((500)<<(10))
#endif
#ifdef SUPPORT_MIDI_VOCAL
#define MIDI_MAX_MP3_FILES              (1)
#else // for other schemes in future
#define MIDI_MAX_MP3_FILES              (1)
#endif

//#define MIDI_VOCAL_INDEX_ADDR           (SDRAM_BASE+0x800000) //store vocal file, Jeff 20031015

#define MIDI_VOCAL_INDEX_ADDR           (SDRAM_BASE+(A_PCMYA+PCMSIZE)*1024) //2004/01/04 yltseng
//Jeff 20040916
//#define MIDI_VOCAL_INDEX_ADDR           (SDRAM_BASE+0x8c0000) //store vocal file, Jeff 20031015
//#define MIDI_VOCAL_INDEX_ADDR           (SDRAM_BASE+0x8b0000) //store vocal file, Jeff 20031015
//#ifdef SUPPORT_CARDREADER_TEST
//#define MIDICARD_INDEXBUFFERADDR (MIDI_VOCAL_INDEX_ADDR+MIDICARD_INDEXBUFFER*1024)
//#define MIDI_OSDFONT_ADDR               (MIDICARD_INDEXBUFFERADDR+sizeof(PLF_REC)*MIDI_MAX_MP3_FILES)
//#else
#define MIDI_OSDFONT_ADDR               (MIDI_VOCAL_INDEX_ADDR+sizeof(PLF_REC)*MIDI_MAX_MP3_FILES)
//#endif
#define SUPPORT_GB_FONTBASE3
// 1039837
#define MIDI_INDEX_SEARCH_STACK_SIZE    (4096)
#define MIDI_LYRIC_FONT_GB1SIZE         (2208490) 
#define MIDI_LYRIC_FONT_GB2SIZE         (1443850)

#define MIDI_MENU_FONT_GB1SIZE          (519916)
#define MIDI_MENU_FONT_GB2SIZE          (339907)

#ifdef SUPPORT_GB_FONTBASE3
//Jeff 20040916
#define MIDI_FONT_GB3SIZE                    (50000)        //xlluo redefine 04-10-21 for some midifiles play error
//#define MIDI_FONT_GB3SIZE                    (200000)
#else
#define MIDI_FONT_GB3SIZE                    (0)
#endif

#define MIDI_OSDFONT_LYRIC_SIZE         ((((MIDI_LYRIC_FONT_GB1SIZE+MIDI_LYRIC_FONT_GB2SIZE+MIDI_FONT_GB3SIZE+MIDI_MENU_FONT_GB1SIZE+MIDI_MENU_FONT_GB2SIZE)+3)>>2)<<2)
#define MIDI_OSDFONT_ADDR_SIZE          (MIDI_OSDFONT_LYRIC_SIZE+MIDI_INDEX_SEARCH_STACK_SIZE)  
#define MIDI_INDEX_SEARCH_STACK_ADDR    (MIDI_OSDFONT_ADDR+MIDI_OSDFONT_LYRIC_SIZE)
#define MIDI_INDEX_SEARCH_STACK_ADDR_END (MIDI_INDEX_SEARCH_STACK_ADDR+MIDI_INDEX_SEARCH_STACK_SIZE)

#define MIDI_INDEX_SEARCH_STACK_ADDR    (MIDI_OSDFONT_ADDR+MIDI_OSDFONT_LYRIC_SIZE)
#define MIDI_INDEX_SEARCH_STACK_ADDR_END (MIDI_INDEX_SEARCH_STACK_ADDR+MIDI_INDEX_SEARCH_STACK_SIZE)
 
#define LYRIC_DATA_BUFFER_ADDR          (MIDI_OSDFONT_ADDR + MIDI_OSDFONT_ADDR_SIZE)   //3652340
#define MIDI_INDEX_BUFFER_ADDR          ((LYRIC_DATA_BUFFER_ADDR)+(LYRIC_DATA_BUFFER_SIZE))
#define MIDI_INDEX_BUFFER_ADDR_END      ((MIDI_INDEX_BUFFER_ADDR)+(MIDI_INDEX_BUFFER_SIZE))

#define MIDI_MP3_FILE_ADDR              (((MIDI_INDEX_BUFFER_ADDR_END+1023)>>10)<<10)
//#define MIDI_MP3_PREBUFFER_SIZE         (3072)
#define MIDI_MP3_PREBUFFER_SIZE         (((SDRAM_BASE+0x1000000-MIDI_MP3_FILE_ADDR)>>10)&0xfff0)


#ifdef SUPPORT_REVERSE_DISPLAY
extern BYTE g_bIsReverDisp;   //xlluo for add reverdisp 05/04/25 
#endif//SUPPORT_REVERSE_DISPLAY



#ifdef MIDI_EJECT_PASSWORD    //ouyang add for eject password 2004-11-20 15:10
EXTERN_FSMIDI UINT8 midi_open_pwd_start;    
EXTERN_FSMIDI UINT8 midi_open_pwd_finished; 
#endif


// these variable for external reference
EXTERN_FSMIDI BYTE      bMidiPlayerBoolean;
EXTERN_FSMIDI BYTE      cIsCHSSong;      //is chinese song?
EXTERN_FSMIDI UINT8     *upMidiGB2FontAddr; 
#ifdef SUPPORT_GB_FONTBASE3
EXTERN_FSMIDI BYTE     *upGB3FontAddr; 
EXTERN_FSMIDI BYTE     *upGB3FontEndPtr; 
#endif
EXTERN_FSMIDI PLF_REC   MidiFont[2]; //  4
EXTERN_FSMIDI UINT8     *upMenuGB2FontAddr,*upMenuGB1FontAddr;


//define the struct to OSD the Midi Title
typedef struct
{
    BYTE    *pInfoStar;
    UINT32  uInfoLen;
} MidiSongInfo_S;

EXTERN_FSMIDI MidiSongInfo_S stMidiTitleInfo;


//Lyric player state
enum
{
    MIDI_STATE_LYRICINIT = 0,
    MIDI_STATE_OSDLYRIC,
    MIDI_STATE_SYNSTART,
    MIDI_STATE_SYNING,
    MIDI_STATE_NOLYRIC,
};  


//The english alphabet and number width in pixel
extern BYTE abc_width[26];
extern BYTE ABC_width[26];
extern BYTE num_width[10];
extern BYTE midiState;
extern BYTE bMidiSynSate;
extern BYTE dotnum,cDotRev,cEnLyric;

typedef struct
{
    UINT32  DeltaLyricSTCno;
    UINT32  LyricDiplaySTCno;	//use it in order to better scheme in future
    BYTE    *RealTimeLyricData;
//    BYTE    *iPMidi;				//use it in order to better scheme in future
    BYTE    LyricEventLen;
    BYTE    c[3]; //dummy data to keep data structure size = 4N
}LyricPos;


extern void MidiSetLyricStopState(void);
extern void MidiOSDLyricPolling(void);
extern UINT16   GetStrColumns(BYTE *tmpbuff);
extern void MidiDispCaption(BYTE * CaptionStr,UINT16 len);
extern void DotSwitch(BYTE Type);

#endif  // end #ifdef SUPPORT_OSDLYRIC


extern void MidiServMP3(void);
extern void MidiUI_Sel_Clear_OSD(void);    //ouyang  2004.08.13 take apart the function of "up" key
//midi module functions for external reference
extern void     MidiInit();
extern void     MidiCreate();
extern int      MidiPolling();
extern void     MidiPlaySet(UINT32 msf, UINT32 iLBA);
extern int      MidiPreParse(UINT32 msf, UINT32 len);

#ifdef HDD_INDEX_TEST

//UINT16 Hdd_fsnav_trk_now;
extern  int HDD_ReadSec(UINT8 *buff,UINT32 lba,int seccnt);
extern int wb_init(UINT32 lsn);

#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)//liweihua mod 20031219
#include "cardfs.h"
extern CARD_FILE       cardFile;
extern CARD_INFO       cardP;
#if defined(CF_CARD_WRITE) ||defined(SPHE8202_FAT_Write_Function) //|| defined(WRITE_USB)
extern BYTE read_card_sign,flag_cf2cd,flag_cd2cf;
#endif //#if defined(CF_CARD_WRITE) ||defined(SPHE8202_FAT_Write_Function) //|| defined(WRITE_USB)
#endif //#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)
#endif //end #ifdef HDD_INDEX_TEST

//modify xlluo 2004-5-27 for two Men or two Women singing together
#define CHORUS_TWO_HOMOMAN
#ifdef CHORUS_TWO_HOMOMAN
EXTERN_FSMIDI   BYTE ca_Singer1Name[2];
EXTERN_FSMIDI   BYTE ca_Singer2Name[2];
EXTERN_FSMIDI   BYTE bIsExterSingerTip;
#endif

#ifdef  SUPPORT_MIDIDISK_TITLE
int MidiPlayTitle(void);
EXTERN_FSMIDI   BYTE bIsPlayMidiTitle;
#endif


#define SUPPORT_SANJING_SCORE
#ifdef SUPPORT_SANJING_SCORE
#define SUPPORT_SANJING_SAVIOP
#endif //SUPPORT_SANJING_SCORE
#ifdef SUPPORT_SANJING_SCORE                 //xlluo for sanjin score system   2004-10-15
extern const char *Score_Str_LTS[3];
extern const char *Score_Str_DKS[3];


//#define SUPPORT_SPICALSCORE                     //add for score for sanjing xlluo 05-3-10 move from fsmidiui.c
#define SUPPORT_RANDOMSCORE                     //only for customer request xlluo 05-3-10 move from fsmidiui.c
#ifdef  SUPPORT_RANDOMSCORE                       //xlluo 04-11-12
BYTE bIsRANDOMSCORE;          //it's not a good idea,I think.
#endif

EXTERN_FSMIDI int SJScoreLine[10];

EXTERN_FSMIDI BYTE bIsSJScoreInvaild;     //False: close score show    True: show scroe system
EXTERN_FSMIDI BYTE cScoreStatus;            // 0~4:score low limit   5:close human voice ON(0)/OFF(1)
                                                                    //   6/7: 00: normal  01:dks 11:lts
                                                                    //+-------------------------------+
                                                                    //+ bit       0  1    2    3    4      5      6    7    +
                                                                    //+  score 0  20  40  60  80  voice  lts  dks +
                                                                    //+-------------------------------+
                                                                    //init code is 0x01 if is 0x00 will be set to 0x01 
                                                                    //when use macro GETSCORELIMITENUM
enum{
            SANJINSCORE_START0 =0X01,                //lowlimit is zero
            SANJINSCORE_START1 =0X02,                //lowlimit is 20
            SANJINSCORE_START2 =0X04,                //lowlimit is 40
            SANJINSCORE_START3 =0X08,                //lowlimit is 60
            SANJINSCORE_START4 =0X10,                //lowlimit is 80
            SANJINSCORE_DISABLEVOICE =0X20,    //is close human voice
            SANJINSCORE_MODE_DKS =0x80,          //is dks
            SANJINSCORE_MODE_LTS =0xc0,            //is lts
            SANJINSCORE_MODE_NML =0x00,          //normal status
         }emSjScrBitTest;

#define BITTEST(x,y)                   ((x & (0x01 << y)) && 1)       

#define MOVESCORELIMITERIGHT() (cScoreStatus =(cScoreStatus&0xe0)|(0x1f&(cScoreStatus<<1))) //ouyang add for score level influence voiceSW 2005-4-4 9:22
#define MOVESCORELIMITELEFT()   (cScoreStatus =(cScoreStatus&0xe0)|((cScoreStatus&0x1f)>>1))
#define SETSCOREMODE(x)         (cScoreStatus =((cScoreStatus&0x3f)^(x)))   
#define GETSCOREMODE( )          (cScoreStatus&0xc0)                                                                     
#define SETSCORELIMITE(x)        (cScoreStatus = ((cScoreStatus&0xe0)^(x)))
#define GETSCORELIMITE( )         (cScoreStatus&0x1f)

#define ISCLOSEHUMANVOICE()          (cScoreStatus&SANJINSCORE_DISABLEVOICE)                                                   
#define DISABLE_HUMANVOICE()        (cScoreStatus =cScoreStatus|SANJINSCORE_DISABLEVOICE)     
#define ENABLE_HUMANVOICE()         (cScoreStatus =cScoreStatus&0xdf)
#define SWITCH_HUMANVOICE()        (cScoreStatus =(cScoreStatus&0xdf)|(cScoreStatus^SANJINSCORE_DISABLEVOICE))
#endif //SUPPORT_SANJING_SCORE



#define SUPPORT_MIDI_STAUSTEST                              //xlluo 04-12-09
#ifdef SUPPORT_MIDI_STAUSTEST
typedef enum {
                        MIDI_STATUS_ISPROGRAM =0,                  //program
                        MIDI_STATUS_ISFIRSTPAGE,                //firstpage
                        MIDI_STATUS_ISSCORE,                      //score
                        MIDI_STATUS_ISRANDOM,                   //random
                        //please add more status here
                        
                    }statusType;
EXTERN_FSMIDI   BYTE Midi_PlayStatusTest(statusType type);
#endif//SUPPORT_MIDI_STAUSTEST

#ifdef SUPPORT_MIDIUI_IME                       //xlluo add for customer
#define SUPPORT_PINYINGDELAY
#endif//SUPPORT_MIDIUI_IME

#ifdef SUPPORT_PINYINGDELAY
#define MIDI_PINYINGINPUT_DELAY             (3)         //about 1.5 s
#endif//SUPPORT_PINYINGDELAY




#ifdef MIDI_MULTIFONT_LIB
#define EXTRAN_FONT_ADDR                       (SDRAM_BASE + A_DEINTLACE_YA*1024)//(SDRAM_BASE+0x1000000 - EXTRANFONT_SIZE)
#define EXTRANFONT_SIZE                          (DEINTLACE_BUF_SIZE*1024)//(51200)//(524288)//0 KB//it enough to the wordtype lib
 
 

#define READWORD(d,p)   (memcpy((BYTE *)(&d),(BYTE *)(p),2))
#define READLONG(d,p)    (memcpy((BYTE *)(&d),(BYTE *)(p),4))

#define FONTLIB_STRUCTSIZE       10
#define FONTTBALE_STRUCTSIZE   8
#include "types.h"
typedef struct {
           UINT32 ulLibCnt;// __attribute__ ((packed));
            
            UINT32 dwOffsetHead __attribute__ ((packed)); //ignore when in a *.bin file, used in a *.fnt file
            WORD  wFontCount __attribute__ ((packed));
            WORD  wLibSize __attribute__ ((packed));    //the times of 2048 bytes!
            BYTE  byLanguage __attribute__ ((packed));  //chinese, english, etc..
            BYTE  byFontFlg __attribute__ ((packed)); 
                                  //bit 0  0, wide char;  1, none wide char
                                  //bit 1  0, left to right;  1, right to left
                                  //bit 2, 0, address using call back; 1, address using index
            //pfont start
            BYTE *    pFontStart __attribute__ ((packed));
}FontLib_S; 

typedef struct {
    struct {
            union{
                    UINT32 data;
                    struct{
                        unsigned pos:24;
                        unsigned sharp:4;
                        unsigned type:4;
                    }context;
            }dwData;
            WORD    wCharCode; 
            BYTE    bySizeX;
            BYTE    bySizeY;
        }stFontPtr;
        //font array
        BYTE *     pfont; 
}Font_S;

typedef struct{
            BYTE ucCurLyricLang;
            BYTE ucCurMenuLang;
}Lang_S;

EXTERN_FSMIDI   Lang_S      g_CurLangStatus;
EXTERN_FSMIDI   FontLib_S   g_stCurFontLibHead;
EXTERN_FSMIDI   UINT8        g_bIsExtFontEnable;    

#define SETLYRICLANG(p)   do{\
                                                    if (g_CurLangStatus.ucCurLyricLang !=(p))\
                                                        g_CurLangStatus.ucCurLyricLang = p;\
                                                    }while(0)
#endif//MIDI_MULTIFONT_LIB

// ************************************************************************
// ***  Define to ensure the multilanguage menu for midi
// ************************************************************************
#define SUPPORT_MULTILANGUAGE_MIDIMENU  //xlluo add 05-02-24


// ************************************************************************
// ***  Define the Midi data conveted from the Cus/tom Lyric Spec Data
// ************************************************************************


#define SUPPORT_YUXING_LYRIC_SPEC
#ifdef SUPPORT_YUXING_LYRIC_SPEC
#define CUSTOMER_MIDI_FLAG   ("YXMidiSrc-SM Karaoke")
/****************************
new function start
*****************************/
#define DISABLE_PLAYEDCODEDISP  //sanjin request don't disp the played song code
#define SELECT_CONV_PROGRAM       //ouyang add for sel convert prg 2005.06.22
#ifndef SELECT_CONV_PROGRAM
//#define SUPPORT_SANJIN_SELECTPLAY               //xlluo add for sanjin select play
#endif
#define SUPPORT_AUTOMENUCLOSE
#ifdef SUPPORT_AUTOMENUCLOSE
#define MENUAUTOCLOSE_DLEAY    20//20*500ms
BYTE g_ucMenuCloseDelay;//set when menu on or key down when menu on and clear in 
#endif//#ifdef SUPPORT_AUTOMENUCLOSE
#define SUPPORT_SELNUM_CLEARSTEP
#define SUPPORT_SCORESW
#define SUPPORT_PRIORITY_KEY
#define DISP_PROGNUM_FIFTY_SECONDS
/****************************
new function end
*****************************/


#define SUPPORT_JKDISKSTATUS        //xlluo for jieke score 04-12-2
#if (defined(SUPPORT_JKDISKSTATUS)&defined(MIDI_EJECT_PASSWORD))
#include "IOP.h"
#define DISK_STATUS    255          
#endif
#endif//SUPPORT_PINYINGDELAY


#ifndef SUPPORT_YUXING_LYRIC_SPEC
#define SUPPORT_SANJING_LYRIC_SPEC 

#ifdef SUPPORT_SANJING_LYRIC_SPEC
#define CUSTOMER_MIDI_FLAG       ("SJMidiSrc-SJM Karaoke")

#if 0
#define SUPPORT_SANJING_DOTS

#define SUPPORT_SANJING_PARADELAY

#define SUPPORT_SANJING_WIDESAPCE           //xlluo for sj space 04-10-15

#define SUPPORT_SANJIN_SELECTPLAY               //xlluo add for sanjin select play

#define SUPPORT_SANJIN_MONOSPACEDFONT   //xlluo add for sanjin monospacedfont xlluo 04-10-21
//#ifdef SUPPORT_SANJIN_MONOSPACEDFONT
//#define SANJIN_MONOFONTWIDTH            (24)
//#endif
#define SUPPORT_SANJING_STOP

#define SUPPORT_SANJIN_DEBUG_UNSURE     //xlluoadd for some test bug

#define SUPPORT_SANJIN_NO_DEFAULTNAME

#define SUPPORT_SANJING_SCORE
//#define SUPPORT_CLEAR_INVALUECODE  // add for clear have played song 2005-4-28 15:52
#ifdef SUPPORT_SANJING_SCORE
#define SUPPORT_SANJING_SAVIOP
#endif //SUPPORT_SANJING_SCORE

#endif
#define SUPPORT_SANJING_DISPLAY
#ifdef SUPPORT_SANJING_DISPLAY
EXTERN_FSMIDI BYTE bIsDispTitleEnable;
#endif

BYTE bIsSanJingMidi;
#endif
#endif
#endif


