//
// fsGUI.h
//
//      fs9660-GUI module external include
//
// notes:
//
// history:
//  2002/02/26  : create
//

#ifndef __FS_NAV_H
#define __FS_NAV_H

#include "bufloc.h"
#include "types.h"
#include "fs96602.h"

//define file type
enum 
{
    FS_FUNC_IDLE        = 0,
    FS_FUNC_MP3         = 1,
    FS_FUNC_JPEG        = 2,
#if defined(SUPPORT_NESGAME)||defined(SUPPORT_SPG_GAME)
    FS_FUNC_GAME,
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
    FS_FUNC_OTHER,   // .dat, .mpg and .txt files. Robert 020930
#endif
#ifdef SUPPORT_MIDI
    FS_FUNC_MIDI,  //.mid
#endif
    FS_FUNC_OKO_MENU,
#ifdef FILE_MODE_WRITE     //SUNZHH 20041225
    FS_FUNC_COPYING,
    FS_FUNC_DELETE,
    FS_FUNC_NEW,
    FS_FUNC_RENAME,
    FS_FUNC_FORMAT,
    FS_FUNC_CAPACITY,
#endif          
#ifdef SUPPORT_PLAYLIST
    FS_FUNC_PLAYLIST,
#endif
};

enum 
{
    FS_STATE_INIT       = 0,
    FS_STATE_LIST       = 1,
    FS_STATE_MP3        = 2,
    FS_STATE_JPEG       = 3,
    FS_STATE_GAME       = 4,
    FS_STATE_OTHER,  // Robert 021001
    FS_STATE_MIDI,
#ifdef SUPPORT_MULTI_PARTITION
    FS_STATE_HDD,
#ifdef FAT_FILE_MODE
    FS_STATE_MODE,
#endif
#ifdef PMP_UI//liweihua mod 2005-3-15
    FS_STATE_COPY,
    FS_STATE_SETUP,
    FS_STATE_ICON_SEL,//kenny 2005/6/15 add for icon select state
    FS_STATE_PLAY,//kenny add state 2005/6/16 for play file 
#endif
#endif
#ifdef FILE_MODE_WRITE
    FS_STATE_MEDIA,       //SUNZHH 2004-12-24 15:25
    FS_STATE_COPY,
#endif    

};

// Added by Robert. 2002/05/08
// The flag is used to identify which state it is while FS_STATE_JPEG

#ifdef JPG_OLD_PARSER_FLOW
    enum
    {
        JPEG_NORMAL_MODE    = 0,
        JPEG_MIDDLE_MODE, // This mode is just for escaping main loop.
        JPEG_THUMBNAIL_MODE,
    };
#else//#ifdef JPG_OLD_PARSER_FLOW
enum
{
    JPEG_NORMAL_MODE    = 0,
    JPEG_MIDDLE_MODE, // This mode is just for escaping main loop.
    JPEG_THUMBNAIL_MODE,
        JPEG_PREVIEW_MODE,
        JPEG_FULL_SCREEN_MODE,  
};
#endif//#ifdef JPG_OLD_PARSER_FLOW

EXTERN_FS  UINT32  mp3ReadLen;

/*
EXTERN_FS  UINT16  g_nJpegMode;

EXTERN_FS  UINT16  file_specify_in_dir;     // number of specify style file in current directory

EXTERN_FS  UINT16  count_dir[4];
EXTERN_FS  UINT16  first_dir[4];
EXTERN_FS  UINT16  count_file[4];

EXTERN_FS  UINT16  Dir_entry[ISO_DIR_MAX];  // map to real track number
EXTERN_FS  UINT16  dir_current;
EXTERN_FS  UINT16  file_current;            // index of current file in current page
EXTERN_FS  UINT16  file_will;               // index of file will in current page,panxing,2002-4-13

EXTERN_FS  BYTE     gifsFuncBtn;            // indicate which button that we choose(FS_FUNC_MP3, FS_FUNC_JPEG, FS_FUNC_GAME)
EXTERN_FS  BYTE     gifsState;

EXTERN_FS  UINT16  gifsMP3Count;            // # of MP3 files in current disc
EXTERN_FS  UINT16  gifsJPEGCount;           // .jpg
EXTERN_FS  UINT16  gifsGAMECount;           // .nes
EXTERN_FS  UINT16  gifsOtherCount;          // .dat, .mpg, and .txt. Robert 020930

EXTERN_FS  UINT32  gifsMSFDVDRom;           //system upgrade image
EXTERN_FS  UINT32  gifsDVDRomSize;          //system-image file size
EXTERN_FS  UINT32  gifsMSFNESDrv;           //NES driver image
EXTERN_FS  UINT32  gifsNESDrvSize;          //NES-driver-image file size

EXTERN_FS  BYTE    gbfsSlide;
EXTERN_FS  BYTE    gifsbPreview;
EXTERN_FS  BYTE    gifsbZoomOK;
EXTERN_FS  BYTE    gfsnot2NormalSpeed;
EXTERN_FS  BYTE    iGraphMode;              //0:small graph, 1:NTSC graph
EXTERN_FS  BYTE    bNesDrvError;

EXTERN  UINT16      iso9660_dir_cnt;
EXTERN  UINT16      iso9660_file_cnt;       //huo 891108, Jeff 20010709 BYTE->UINT16


*/





//called by iso9660 module
void FSNav_Init();
void FSNav_MP3Init();
void FSNav_JPEGInit();
void FSNav_GameInit();
void FSNav_OtherInit(); // Robert 021014
void ReturnFromOtherModeToMenu(); // Robert 021014

#ifdef SUPPORT_QUICKTIME
BYTE IsM4AFileType();
#endif //SUPPORT_QUICKTIME

BYTE GetCurrentFileType(); // Robert 021015
void FSNav_MainLoop();
int  FSNav_DoUpgrade(BYTE* strVersion);

void ShowMP3Reading(BYTE offset);

#ifdef FS_FILE_POWER_RESUME //qinhua,2006-6-13 05:03ÏÂÎç 
extern UINT8 IsTheSameDisc(void);
#endif 


void FS_MoveCD2RAM(BYTE *dest, UINT32 lba, UINT32 size);
void FS_NesDeScramble(int *pData, int iSize);

//extern function could be used
//DSP audio related
//2004AUDDRV extern void init_mp3(void);
//2004AUDDRV extern void init_jpg(void);
//2004AUDDRV extern void  InitWma(void);

//OSD related
extern void     DispCookOSD0(BYTE bChange);
extern void     DispPolling(BYTE bReset);

#ifdef AUDIO_SHOW_SAVER
extern BYTE    bDisableGUI;
#endif

#ifdef  MP3_JPEG_COWORK
#include    "lbc.h"
#include    "drv.h"
UINT32 check_mp3_boundary(UINT32 nLBA);
BYTE    check_input_interval(void);
BYTE feed_data(UINT32 nLBA);//susu add 2003-11-4 21:32
UINT16  anchor_convert_mp3;
UINT16  mp3_increase_count;
BYTE        back_sign;//add 2004-01-15 wuxiaofeng
UINT32  old_time;

BYTE feed_new_data(UINT32 offset);
BYTE polling_feed_new_data(UINT32 nLBA);
void read_data(UINT32 nLBA);

//wuxiaofeng 2004-04-19
#include "memmap0.h"
UINT32  feed_ptr;
UINT32  read_ptr;
UINT8   *MP3_START;//=(UINT8 *)(SDRAM_BASE + (MP3_BUFFER_START) * 1024);
BYTE ReadMP3fromBuffer();
void FeedMP3toBuffer(UINT32 nLBA);
BYTE polling_read_data();
void polling_feed_read_data(UINT32 nLBA);
int ReadJPEG(UINT32 msf, UINT32 iFrame, UINT8* buf);
extern UINT16  refresh_file_page;
extern UINT16  refresh_dir_page;

int mp3_loop_lock; //ycwen 2005/1/21
#endif

/**********************************************************
**  Description: declaration and definition
**  Creater:wuxiaofeng
**  Date:03-09-16 17:53
***********************************************************/
#if defined(CF_CARD_WRITE)||defined(SPHE8202_FAT_Write_Function) //||defined(WRITE_USB)
extern  BYTE    sign_PFun;
extern  BYTE read_card_sign,flag_cf2cd,flag_cd2cf;            //xulf0826
extern  void Message_Show(BYTE strID);
//extern    int CardSchedule(BYTE copy_mode);
extern  int FSSchedule(BYTE copy_mode);
#define PFUN_WRITE          1
#define P_SPACEFULL         6
#define PFUN_COPYING        5
#define P_NOMATCH           9
#define P_DIREXISTING       10//add 2003-12-22
extern  BYTE    CopyID;
#endif

#if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) //kenny 2005/6/16 define pmp user special flag
#define PMP_USER_PRESS_NEXT_PREV_KEY        (1)
#define PMP_USER_AUTO_PLAY                  (2)
#define PMP_USER_PRESS_UP_DOWN__KEY         (4)
#define PMP_USER_PRESS_RETURN_KEY           (8)
#define PMP_USER_PRESS_SELECT_KEY           (16)
#define PMP_USER_ENTER_VIDEO_AUDIO_PHOTO    (32)
#define PMP_USER_ENTER_SEARCH_TRACK         (64)

#endif//#if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) //kenny 2005/6/16 define pmp user special flag

#endif

