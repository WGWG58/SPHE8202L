/*
*  languange code
*/
enum {
    LCD_EN=1,   //              S:英文
    LCD_JA=2,   //              S:日文
    LCD_FR,     //              S:法文
    LCD_PT,     //              S:葡萄牙文
    LCD_DE,     //              S:德文
    LCD_LA,     //              S:拉丁文
    LCD_ES,     //              S:西班牙文
    LCD_ZH,     //              S:中文
    LCD_PL,     //T:猧孽粂      S:波兰文
    LCD_CS,     //T:倍粂      S:捷克
    LCD_HU,     //T:粂    S:匈牙利
    LCD_IS,     //T:畄粂      S:冰岛
    LCD_HI,     //T:粂      S:印地
    LCD_NL,     //T:颤孽粂      S:荷兰
    LCD_TR,     //T:φㄤ粂     S:土耳其
    LCD_DA,     //T:う沉粂      S:丹麦
    LCD_SV,     //T:风ㄥ粂      S:瑞典
    LCD_FI,     //T:孽粂      S:芬兰
    LCD_EL,     //T:镁粂      S:希腊
    LCD_NO,     //T:粂      S:挪威
    LCD_KO,     //T:龙粂        S:韩文
    LCD_TH,     //T:粂        S:泰国
    LCD_IT, //S:意大利语Italian
#ifndef MAX_OSD_LANG_STR_ID_25//nono 20030307
    LCD_RU,     //T:(玐粂)S:(俄文)Russian
    LCD_IN,     //T:(ェ粂)S:(印尼语)Indonesian
    LCD_ID,     //T:(ェ粂)S:(印尼语)Indonesian_new
    LCD_AR,     //T:(┰粂)S:(阿拉伯语)Arabic
    LCD_HE,     //T:(︹粂)S:(希伯来语)Hebrew_new
    LCD_IW,     //T:(︹粂)S:(希伯来语)Hebrew
    LCD_RO,     //T:(        )S:(罗马尼亚语)Romanian
    LCD_BG,     //            S:保加利亚
    LCD_HR,     //            S:克罗地亚
    LCD_ET,     //            S:爱沙尼亚
    LCD_LT,     //            S:立陶宛
    LCD_LV,     //            S:拉脱维亚
	LCD_BR,     //            S:巴西－葡萄牙//nono mark.20050925
    LCD_SL,      //           S:斯洛文尼亚
#endif
    LCD_NON,
};

/*
** OSD palette header
*/
enum
{
    NORMAL_HEADER = 0,
    EQ_HEADER,
    SETUP_HEADER,
    NES_HEADER,
    #ifdef REALCOLOR_SCREENSAVER
    SCREENSAVER_HEADER,
    #endif
    #ifdef VIRTUAL_KEYBOARD
    KEYBOARD_HEADER,
    #endif
    #ifdef SUPPORT_DVB_GUI_NEW
    NONOSDVBS_HEADER, //ydwang add 2005-4-19 for dvbGUI
    INFO_HEADER, //sunzhh add for Program Info display 20051027
    #endif
    #ifdef SUPPORT_TELETEXT
    TTX_HEADER,
    #endif
    #ifdef SUPPORT_SUBTITLE
    SUBTITLE_HEADER,   
    #endif
    #ifdef BBK_DVD//NEW_SETUP
    BBK_SETUP_256HEADER,
    #endif
    #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-5 9:37
    QSI_SETUP_HEADER,
    #endif
    #ifdef OSD_BMP_DISPLAY
    BMP_DISPLAY_HEADER,
    #endif
    #ifdef OSD_BMP_REGION1
    BMP_REGION1_HEADER,
    #endif
    #ifdef OSD_BMP
    BMP_REGION_A_HEADER,
    BMP_REGION_B_HEADER,
    BMP_REGION_C_HEADER,
    BMP_REGION_D_HEADER,
    BMP_REGION_E_HEADER,
    BMP_REGION_F_HEADER,
    #endif
    SIMPLE_HEADER,              // 2005/04/12 yltseng
    #ifdef GPS_KEYBOARD
    GPS_BOARD_HEADER,
    #endif
#ifdef INDIGO_STYLE_OSDUI //2006-03-20, mimitsai add for display color
	DISPLAY_HEADER,
#endif
	
};
/*
#ifdef OSD_BMP
enum
{
	DISPLAY_REGION0_HEADER = 0,
	DISPLAY_REGION1_HEADER = 1,
};
#endif
*/
/*
** CD format supported
*/
enum    {
    CDUNKNOWN=0,
    CDDA=1,
    CDROM,
    CDVCD10,
    CDVCD20,
    CDSVCD,
    CDDVD,
#ifdef USE_HDD
    CDHD,
#endif
    CDJPEG,
    CDTXT,
#ifdef MP3_TXT_DISPLAY
    CDMP3LRC,
#endif
    CDMIDI,
};


/*
*  disc sub-type
*/
enum {
    UDF_MP3=1,
    CD_CDI=2,
    CD_OKO=3,
    CD_CVD=4,
    // for supporting 718 game disc
    NES_DISC,
    NES_DISC_CHKSUM,
};

//When cd_type_loaded=CDROM, cd_subtype indicate it's extension file type
enum    {
    CDROM_UNSUPPORT=10,
    CDROM_MP3=11,
    CDROM_JPEG,
    CDROM_GAME,
    CDROM_BIN,      //for smart upgrade
    CDROM_WMA,
    CDROM_DAT,
    CDROM_MPG,
    CDROM_WAV,
    CDROM_VID,
    CD_DA,          //Jeff 20020415
    CD_HD,
    CD_DTS,
    CDROM_MIDI,
    CDROM_NES,
    CDROM_NESGUN,
    CD_AC3,     //Jeff 20040102
    CDROM_MP4,
    CDROM_DIV,
#ifdef SUPPORT_QUICKTIME
    CDROM_M4A,
#endif //SUPPORT_QUICKTIME
//#ifdef TELL_FROM_MP4_EXT_NAME    //Maoyong 2004.06.25 CDROM_MP4 just for DIVX
    CDROM_AVI,
//#endif
#ifdef SUPPORT_GIF //suqiaoli 20040224
    CDROM_GIF,
#endif
#ifdef SUPPORT_BMP //suqiaoli 20040220
    CDROM_BMP,
#endif

#ifdef SUPPORT_SPG_GAME 
    CDROM_SPG,
#endif
	CDROM_AAC,
	CDROM_SWD,

#ifdef SUPPORT_SMF  //xlluo //2005-7-27//for flash game support, (*.SWF)
        CDROM_SMF,
#endif//SUPPORT_SMF
#ifdef SUPPORT_PLAYLIST
    CDROM_PLAYLIST,
#endif
#ifdef SUPPORT_OGG
    CDROM_OGG,
#endif    
};

#ifdef SUPPORT_MIDI
    //UINT8 bNoteState[2][128];
    UINT8 NotaBuffer[256]; //ouyang 2004.07.31
    UINT8 bLapNoteState[2][128];
    UINT8 bNoteState[128];
    BYTE    cLyricBuff1[128];
    //BYTE tempwords[128];
    BYTE Captionbuf[256];
    BYTE DispTmp[128];      //for IOP is covered by memory .ouyang2004.08.10
#endif

/*
*  Card reader
*/
enum {
    MEDIA_CD=0,
    MEDIA_HD=1,
    MEDIA_CARD=2,
    MEDIA_NET=3,
    MEDIA_LINUX=4,
    #ifdef DIRECT_ACCESS_MEDIA//added by wangwei,2005-11-15 14:10
    MEDIA_NOTHING=5,
    #endif//DIRECT_ACCESS_MEDIA
};

#ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-11 14:49
enum {//media_status
    #ifdef DVD_SERVO
    STATUS_DISC,
    #endif
    
    #ifdef SPHE8202_CARD_STORAGE
    STATUS_CARD,
    #endif//SPHE8202_CARD_STORAGE
    
    #ifdef SUPPORT_USB
    STATUS_USB,
    #endif//SUPPORT_USB
    
    STATUS_NON,
};
#endif//DIRECT_ACCESS_MEDIA

enum {
    CARD2CD = 0,
    CD2CARD = 1,
    CARD2CARD,
};

#define USB_DEVICE       0x01
#define CF_CARD_DEVICE   0x02
#define SD_CARD_DEVICE   0x04
#define MS_CARD_DEVICE   0x08
#define SMC_CARD_DEVICE  0x10

//Maoyong 2004.05.26 for show_card_reading_osd(BYTE type)
#define SHOW_MEDIA          0   //card number/meida type
#define SHOW_READ_PERCENT   1   //reading files percent
#define SHOW_OFF            2   //turn off

//Maoyong 2004.08.09 index for select media type in setupmenu or hot detect device GUI
#ifdef SELECT_MEDIA_IN_SETUPMENU
#ifdef SUPPORT_USB
#define DISC_ITEM          0
#define USB_ITEM           1
#define CARD_ITEM          2
#else
#define DISC_ITEM          0
#define USB_ITEM           2
#define CARD_ITEM          1
#endif
#endif
/*
*  vpp zoom
*/
#ifdef TWELVE_ZOOMFACTORS//axel2004/5/3 12:35pm
#define ZOOM_LB       0
#define ZOOM_PS       1
#define ZOOMIN_BASE   2
#define ZOOMIN_MAX    9
#define ZOOMOUT_BASE  10
#define ZOOMOUT_MAX   12
#else
#define ZOOM_LB       0
#define ZOOM_PS       1
#define ZOOMIN_BASE   2
#define ZOOMIN_MAX    4
#define ZOOMOUT_BASE  6

#if defined(SDRAM16M_ZOOMOUT_6)//nono 2004-6-16 17:42
#define ZOOMOUT_MAX   6//8
#elif defined(SDRAM16M_ZOOMOUT_5)
#define ZOOMOUT_MAX   5
#else
#define ZOOMOUT_MAX   8
#endif

#endif//#ifdef TWELVE_ZOOMFACTORS

/*
*  define program state
*/
enum{
  PROG_IDLE=0,
  STORE_PROGRAM=1,
  PLAY_PROGRAM=5
};

/*
*  define flow control state
*/
enum {
  CLEAR_ALL=0,
  GOTO,
  PROGRAM,
  SHUFFLE,
  REPEAT_ALL,
  REPEAT_AB,
  RESUME,               //keep resume
};


/*
**  repeat-mode of playing
*/

enum {
  REPEAT_IDLE   = 0,
  REPEAT_TRACK  = 1,//DVD,repeat chapter
  REPEAT_DIRECTORY = 2, // only for mp3, panxing,2002-3-11
  REPEAT_DISC      = 3,//DVD,repeat title
  REPEAT_DVDDISC   = 4,//terry,2003/10/18 06:29PM
  #ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT //chenzhao20060206
  REPEAT_ALL_DISCS ,
  #endif
  REPEAT_MAX       //= 4
};


enum {
  REPEAT_AB_IDLE    = 0,
  REPEAT_FIND_A,
  REPEAT_FIND_B,
  REPEAT_AB_MAX
};

/*
*  define random state
*/
enum {
  SHUFFLE_IDLE  = 0,
  SHUFFLE_RAN,
  SHUFFLE_ALL,
  SHUFFLE_MAX,
  //REPEAT_FIRST,
  //REPEAT_AGAIN,
};

/*
** define system state
*/
enum {
  SYSTEM_IDLE=0,
  SYSTEM_NODISC=1,
  SYSTEM_OPEN,
  SYSTEM_STOP,

  SYSTEM_READ_TITLE,
  SYSTEM_SETUP_BROWSER,
  SYSTEM_POWER,
  SYSTEM_BROWSE,
  SYSTEM_PLAYGAME,
  SYSTEM_FINISH,
#ifdef SUPPORT_RECEIVER //huziqin 2004-2-26
  SYSTEM_MODE_CHANGE,
  SYSTEM_DOING_AV1,
  SYSTEM_DOING_AV2,
  SYSTEM_DOING_SPDIF,
#ifdef SUPPORT_COAXIAL_IN//xyy 2004-5-26
  SYSTEM_DOING_COAXIAL,
#endif
  SYSTEM_DOING_TUNER,
  SYSTEM_DOING_NOISE,
  SYSTEM_EJECT_CHANGE,
#endif
#if defined(SPHE1000)||defined(SUPPORT_8202_DVB)  //sunzhh 20050430
  SYSTEM_DVD,
  SYSTEM_TS,
  SYSTEM_FILESTREAM,
  #ifdef SUPPORT_DVB_NATIVE_GAME
  SYSTEM_DVBGAME,
  #endif
#endif

  #ifdef SUPPORT_DVD_NATIVE_GAME	//linrc add for NATIVE_GAME 2005-10-18 14:42
  SYSTEM_DVDGAME,
  #endif

#ifdef QSI_SHOW_ERR_RATE
  SYSTEM_QSI_PIPO_TEST,
#endif

/*
define two system state for power off clock function
*/
#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11
  SYSTEM_MODE_CLOCK_FUNC,
  SYSTEM_DOING_CLOCK_FUNC,
#endif

#ifdef PMP_DVD  //wthsin add for PMP  2004/11/8
  SYSTEM_PC_USB_MODE,
#endif

#ifdef AV_IN_THROUGH_EXT_ADC
    SYSTEM_AVIN,
    SYSTEM_AVIN_DOING,
#endif
};


/*
* define vcd 2.0/svcd psd state
*/
enum {
  PSD_SEL_LIST   = 0x10,
  PSD_PLAY_LIST  = 0x20,
  PSD_END_LIST   = 0x40,
  PSD_MP3_DIRLIST= 0x80,
  PSD_PLAY_TRACK = 0x1,
  PSD_PLAY_SEG   = 0x2,
  PSD_PLAY_ENTRY = 0x4,
};



/*
*  define play state
*/
enum {
  VCD_STATE_IDLE              =0,
  VCD_STATE_READTOC           =1,
  VCD_STATE_NORMAL            =2,
  VCD_STATE_FASTFORWARD       ,
  VCD_STATE_FASTBACKWARD      ,
  VCD_STATE_PAUSE             ,
  VCD_STATE_SLOW              ,
  VCD_STATE_PREVIEW           ,
  VCD_STATE_9FRAMES           ,
  VCD_STATE_POWER             ,
  VCD_STATE_MP3_FILELIST      ,
  VCD_STATE_OPEN              ,
  VCD_STATE_CLOSE             ,
  VCD_STATE_STOP              ,
  VCD_STATE_MAX               ,
};


#define CMD_NONE         0x0000
#define CMD_SELECT       0x1000
#define CMD_FUNC         0x2000
#define CMD_MODE         0xf000
#define CMD_MASK         0x0fff
#define IS_CMD_MODE()    (sys_cmd&CMD_MODE)
#define IS_CMD_SELECT()  (sys_cmd&CMD_SELECT)
#define IS_CMD_FUNC()    (sys_cmd&CMD_FUNC)
#define IS_CMD_NONE()    (sys_cmd==CMD_NONE)
#define GET_CMD_SELECT() (sys_cmd&CMD_MASK)
#define GET_CMD_MODE()   (sys_cmd&CMD_MODE)

#define PostCommand(n)  (sys_cmd=(n))
#define ClearCommand()  (sys_cmd=CMD_NONE)

#define CMD_FUNC_NONE       0x00
#define CMD_FUNC_FORWARD    0x01
#define CMD_FUNC_BACKWARD   0x02
#define CMD_FUNC_NEXT       0x03
#define CMD_FUNC_PREV       0x04
#define CMD_FUNC_PLAY       0x05
#define CMD_FUNC_STOP       0x06
#define CMD_FUNC_OPEN       0x07
#define CMD_FUNC_CLOSE      0x09
#define CMD_FUNC_CLOSED     0x0a
#define CMD_FUNC_RETURN     0x0b
#define CMD_FUNC_TIMEOUT    0x0c
#define CMD_FUNC_DISC_PRESENT   0x0d
#define CMD_FUNC_PREVIEW    0x0e        /* select preview.. */
#define CMD_FUNC_DEFAULT    0x0F
#define CMD_FUNC_GAME       0x10
#define CMD_FUNC_PBC        0x11
#define CMD_FUNC_REPAB      0x12
#define CMD_FUNC_RESUME     0x13
#define CMD_FUNC_9FRAMES    0x14
//#define   CMD_FUNC_INTRO      0x15
#define CMD_FUNC_GOTO       0x16
#define CMD_FUNC_SHUFFLE    0x19
#define CMD_FUNC_PRG        0x1a
#define CMD_FUNC_POWER      0x1b    /*jhuang add 891010*/
#define CMD_FUNC_BOOK       0x1c
#define CMD_FUNC_PAUSE      0x1d

#define CMD_FUNC_GAME_L     0xffb
#define CMD_FUNC_GAME_R     0xffc
#define CMD_FUNC_GAME_DN    0xffd
#define CMD_FUNC_GAME_TN    0xffe
#define CMD_FUNC_GAME_UL    0xfff

#define CMD_FUNC_NEXT_PAGE      0x25 //kenny add it 2001/4/26 for mp3 next page
#define CMD_FUNC_PRE_PAGE       0x26 //kenny add it 2001/4/26 for mp3 next page


//DVD new add
#define CMD_PTT_PLAY        0x27
#define CMD_FUNC_MENU       0x28
#define CMD_FUNC_TITLE      0x29
#define CMD_FUNC_SELECT     0x2a

#ifdef SUPPORT_8202_DVB
//DVB navigation
#define CMD_FUNC_INSTALL_START     		0x2b
#define CMD_FUNC_SET_DEFAULT     		0x2c
#define CMD_FUNC_FINISH_NAVIGATION     	0x2d
#endif

#ifdef FILE_MODE_WRITE//frank.huang 050831 
#define CMD_FUNC_FILE_MODE				0x2e
#endif

#define KEYDOWN_LEFT        CMD_FUNC_GAME_L
#define KEYDOWN_RIGHT       CMD_FUNC_GAME_R
#define KEYDOWN_DOWN        CMD_FUNC_GAME_DN
#define KEYDOWN_TURN        CMD_FUNC_GAME_TN
#define KEYDOWN_UPLEVEL     CMD_FUNC_GAME_UL

/*
**  packed-address operation
*/
#define addr_vxvy(vx,vy)    (((vy)<<5) | (((vx)>>5) & 0x1f))
#define addr_vy(X)      ((X)>>5)
#define addr_vx(X)      (((X)&0x1f)<<5)

#define BITSTREAM_VIDEO     (1<<0)
#define BITSTREAM_AUDIO     (1<<1)
#define BITSTREAM_OGT       (1<<2)
#define BITSTREAM_MP3       (1<<3)
#define BITSTREAM_CDDA      (1<<7)

#define VCD_VIDEO   BITSTREAM_VIDEO
#define VCD_AUDIO   BITSTREAM_AUDIO
#define VCD_OGT     BITSTREAM_OGT
#define VCD_MP3     BITSTREAM_MP3
#define VCD_CDDA    BITSTREAM_CDDA

/*
*  define preview initial value
*/
#define MSF_PREVIEW_INIT    ((UINT32)(-1))


/*
*  option define
*/
#ifdef NEW_SEARCH_OSD
    #define OSD_Goto_Disable // yw 020913
#endif
#define VCD_MODE_NUM 2
#define DVD_MODE_NUM 1


/*
*  modual define
*/
#define RESET_MODE           0x80
enum
{
    MODUAL_DVD  = 0,
    MODUAL_MPEG = 1,
    MODUAL_JPEG = 2,
    MODUAL_AP,
    MODUAL_CDROM,
    MODUAL_IOP,
    MODUAL_IOP_RESET,
    MODUAL_OTHER,
    MODUAL_SRVDSP,
    MODUAL_AP2,
    MODUAL_AP3,
    MODUAL_FREE,
    MODUAL_ROM3,
    MODUAL_MP4,
    MODUAL_WMA,
#ifdef SPHE1000
    MODUAL_LWIP, 
#else
    MODUAL_DVB,  //terry,2005/10/13 01:33と
#endif
    MODUAL_Ns
};


/*
* define display time type
*/
#define NO_REMAIN_TIME          0
#define TRK_REMAIN_TIME         1
#ifdef NO_DISC_TIME
#define DISC_REMAIN_TIME        2
#define DISC_TIME               3
#define TIME_MAX_MODE           3
#else//#ifdef NO_DISC_TIME
#define DISC_REMAIN_TIME        3//2
#define DISC_TIME               2//3
#define TIME_MAX_MODE           4
#endif//#ifdef NO_DISC_TIME

/*
* define Highlight action
*/
#define HL_ACTION   0
#define HL_DIR      1

#define HL_BM_U 0
#define HL_BM_D 1
#define HL_BM_L 2
#define HL_BM_R 3
#define BM_MASK 0x3f


/*
*  video output
*/

#define INTERLACE  0x00
#define TV_RGB     0x01
#define P_SCAN     0x02


#define PC_VGA     0x03   // 2005/05/03 yltseng
#define TV_SVIDEO  0x04
#ifdef SETUP_CVBS_OUTPUT        //wanghaoying 2003-11-6 22:55
#define CVBS       0x05
#endif

/*
*  HD FLOW & HD OSD 
*/
    #define SD_480      0x00
    #define SD_576      0x01
    #define HD_720      0x02
    #define HD_1080    0x03

#define SET_TV_RESOLUTION(x)               (tv_resolution = (x))
#define GET_TV_RESOLUTION()                 (tv_resolution)
#define SET_OSD_SCALE_BUF_FLAG(x)      (osd_scale_buf_flag=(x))
#define IS_OSD_SCALE_BUF_OK()             (osd_scale_buf_flag)

/*
* Card reader
*/
#define CARD_HAD_PLUGGED_IN   0x01  //Bit0 means card had plug-in(bit0 =1)
#define USER_DO_PLUG_IN       0x02  //Bit1 means user do plug-in action(bit1=1)

/*
* program unit
*/
#define SHOW_PROG_NO        20
/*
*  cd info
*/
#define CD_TRK_CHANGED      1
#define CD_MM_CHANGED       2
#define CD_SS_CHANGED       3

#define gettrkmsf(tno)          (pFsJpeg->cdrom.track_info[tno])
#define settrkmsf(tno, msf)     (pFsJpeg->cdrom.track_info[tno]=(msf))
#define gettrkcna(tno)          (gettrkmsf(tno)>>24)

#define TRACK_INFO_FIRSTTRACK   0x64
#define TRACK_INFO_LASTTRACK    0x65
#define TRACK_INFO_LEADOUT  0x66

//#define   gettrk_first()      msf_mm(gettrkmsf(TRACK_INFO_FIRSTTRACK))
//#define   gettrk_last()       msf_mm(gettrkmsf(TRACK_INFO_LASTTRACK))
#define gettrkmsf_leadout() gettrkmsf(TRACK_INFO_LEADOUT)&0xffffff
#define cd_total_trk()          (cd_trk_hi - cd_trk_lo_now +1)

/*
*  2005/01/14 yltseng, for 16M setup & program osd don't exit to logo
*/
#define OSD_FULL_SCREEN_STATUS_NONE                         0
#define OSD_FULL_SCREEN_STATUS_WAIT_ATAPI_CMD_FINISH        (0x01 << 0)
#define OSD_FULL_SCREEN_STATUS_WAIT_KERNEL_DECODE_FINISH    (0x01 << 1)
#define OSD_FULL_SCREEN_STATUS_ACTIVE                       (0x01 << 2)

#define OSD_FULL_SCREEN_STATUS_SETUP                        (0x01 << 4)
#define OSD_FULL_SCREEN_STATUS_PROGRAM                      (0x01 << 5)

/*
*  osd full page
*/
#define READ            0
#define PROGRAM         0x01<<0
#define GOTO            0x01<<1
#define SETUP           0x01<<2


#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
#define SET_AMP         0x01<<3   // ych 2-9-21 11:30
#elif defined(SUPPORT_FUNCTION_MENU)
#define SETUP_PLUS      0x01<<3
#elif 1//defined(NEWSTYLE_WINDOW)
#define MESSAGE            0x01<<3
#endif
#define MARK            0x01<<4
#define SOUND           0x01<<5
#define CUSTM           0x01<<6
#define SCORE           0x01<<7

#define ALL             0xff
#define MAX_FULL_PAGE   8
#define FULLOSD_MASK    0x100

#ifdef ORITRON_TRAY_PASSWORD//libing 2005-4-25 10:07
#define TRAY_PWD        0x01<<8
#elif defined(VIRTUAL_KEYBOARD)
#define KEYBOARD        0x01<<8 //liweihua add 03-8-15
#elif defined DVB_SETUP_MENU//Maoyong 2004-10-25 17:36
#define DVB_MENU 0x1<<8
#define PROGRAMINFO 0x1<<9 //eric add 2004-11-05 14:36
#elif defined(SUPPORT_8202_DVB)
#define DVB_T_SETUP_MENU   0x1<<8
#define DVB_MENU 0x1<<8
#define PROGRAMINFO 0x1<<9 //eric add 2004-11-05 14:36
#endif

#ifdef GPS_KEYBOARD//liweihua add 2005-6-1 11:21
    #define TOUCH_KEYBOARD  0x01<<9
#else
#ifdef SUPPORT_REP_READ
#undef  READ
#define READ            0X01<<9
#elif defined ( SUPPORT_OP_REGION_UI )||defined(SUPPORT_OP_SW_VERSION_UI)//libing 2005-8-24 9:24
#define OP_REGION_UI    0x01<<9
#endif
#endif

#ifdef GPS_MENU
    #define TOUCH_MENU      0x01<<10
#elif defined(RIPPING_MODE_SELECT)//qinhua for rip ui,2006-5-30 03:13下午
    #define RIP_GUI         0x01<<10
#else
#ifdef DOUBLE_TITLE
#undef  DOUBLETITLE
#define DOUBLETITLE     0x01<<10
#endif
#endif//GPS_MENU

#if defined(FAT_Write_UI)||defined(CF_CARD_WRITE)//||defined(WRITE_USB)
#define PERIPHERAL      0x01<<11
#elif defined(FILE_MODE_WRITE)//for show input table,added by wangwei,2005-1-13 10:05
#define INPUT_TBL       0x01<<11
#else// defined(DIRECT_ACCESS_MEDIA)//added by wangwei, 2006-4-12 14:19
#define SW_MEDIA        0x01<<11
#endif

#ifdef SUPPORT_APOGEE_AMP //xyy 2003-10-10 13:05
#define APOGEEAMPVOL    0x01<<12
#elif defined(OP_PLAYMODE)//libing 2005-4-12 10:11 for Op_Menu
#define OP_MENU         0x01<<12
#endif


#ifdef DIVX_DRM
#define DIVX_DRM_MENU   0x01<<14
#endif

#ifdef SWITCH_CD_CARD_USB//liweihua 2004-6-8
#define SWITCH_GUI  0x01<<15
#elif defined(FILE_MODE_WRITE)//for show storage information,added by wangwei,2005-1-13 10:03
#define STRG_INFO       0x01<<15
#endif

#if defined(OP_PLAYMODE)||defined(VIRTUAL_KEYBOARD)||defined(SUPPORT_REP_READ)||defined(DOUBLE_TITLE)||defined(CF_CARD_WRITE)||defined(SPHE8202_FAT_Write_Function) || defined(SUPPORT_APOGEE_AMP)||defined(DIVX_DRM)||defined(SWITCH_CD_CARD_USB)||defined(DVB_MENU)||defined(FILE_MODE_WRITE)||defined(SUPPORT_8202_DVB)||defined(GPS_KEYBOARD)||defined(GPS_MENU)||defined(DIRECT_ACCESS_MEDIA)//||defined(WRITE_USB)

#undef  ALL
#undef  MAX_FULL_PAGE
#undef  FULLOSD_MASK
#ifndef DOUBLE_TITLE
#define DOUBLETITLE     0
#endif
#define ALL             0xffff
#define MAX_FULL_PAGE   16
#define BIT16MODE       0xffff
#define FULLOSD_MASK    0x10000
#endif

/*
*  Book define
*/
#if 0//def SDRAM_16Mb_Mode//NONO mark it.2004-4-11 18:12
#undef SUPPORT_BOOK
#endif
#ifdef  SUPPORT_BOOK
#ifdef SHOW_12_BOOKMARK
#define BOOK_MAX_ITEM   12//libing 2005-4-25 18:21
#else
#define BOOK_MAX_ITEM   5
#endif
#define BOOK_MAX_RECORD 2
EXTERN BYTE book[BOOK_MAX_ITEM][BOOK_MAX_RECORD];//vcd: track //dvd: title,chapter
EXTERN UINT32 book_tm[BOOK_MAX_ITEM];
    #ifdef DVD_PRESTOP_SEPARATE_MENU_RESUME_INFO //chenzhao 2006-9-13 11:36 .
    #define DVD_PRESTOP_RSM_ITEM (BOOK_MAX_ITEM+1)
    #endif
#else
#define BOOK_MAX_ITEM   1
    #ifdef DVD_PRESTOP_SEPARATE_MENU_RESUME_INFO //chenzhao 2006-9-13 11:36 .
    #define DVD_PRESTOP_RSM_ITEM BOOK_MAX_ITEM
    #endif
#endif

#ifndef DVD_PRESTOP_SEPARATE_MENU_RESUME_INFO //chenzhao 2006-9-13 11:36 .
#define DVD_PRESTOP_RSM_ITEM 0
#endif

/*
*  Work Buffer Size in byte for each navigation data access
*/
#define WB_SIZE   (2048*2)

/*
*define DVD error code
*/
#define DVD_NORMAL      0
#define PARENTAL_ERR    1
#define REGION_ERR      2
#define FLASH_ID_ERR    3


#ifdef SUPPORT_RECEIVER  //huziqin 2004-2-26

#ifdef ONLY_SUPPORT_DVD_TUNER //xyy 2004-8-12
 enum
 {
    RECEIVER_MODE_DVD = 0,
    RECEIVER_MODE_TUNER,
    RECEIVER_MODE_DUMMY
 };

#else//#ifdef ONLY_SUPPORT_DVD_TUNER //xyy 2004-8-12
 enum
// Keep these, even if some are disabled
// You can change the mode cycling order by changing the order
// in the enum.  However, make sure the first one starts at ZERO.
// Changing this requires irconfig.h to be updated also
 {
    RECEIVER_MODE_DVD = 0,
    RECEIVER_MODE_AV1,
    RECEIVER_MODE_AV2,
    RECEIVER_MODE_SPDIF,
#ifdef SUPPORT_COAXIAL_IN//xyy 2004-4-29  for XQ
    RECEIVER_MODE_COAXIAL,
#endif
    RECEIVER_MODE_TUNER,
    RECEIVER_MODE_DUMMY
 };
 #endif//#ifdef ONLY_SUPPORT_DVD_TUNER //xyy 2004-8-12
    //variable move to global.h chenzhao20060120
#endif  //SUPPORT_RECEIVER

#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11
/*
Because the power off clock function is temporary only used
by oritron, especially defined two system mode.
*/
enum
{
	NORMAL_PLAY_MODE = 0,
	CLOCK_FUNC_MODE
};

int current_mode;
int next_mode;
int switch_to_clockmode;

#endif

/*
*  amp
*/
enum
{
    MODE_AV1 = 0,
    MODE_AV2,
    MODE_TUNER,
    MODE_DVD
};

enum
{
    VOL_MODE_MAIN = 5,
    VOL_MODE_FRONT,
    VOL_MODE_CENTER,
    VOL_MODE_REAR,
#ifndef NEW_UART_COMMAND
    VOL_MODE_MAIN_LR_BALANCE,
    VOL_MODE_SUR_LR_BALANCE,
#else
    VOL_MODE_SUBWOOFER,
    VOL_MODE_MAIN_BALANCE_L,
    VOL_MODE_MAIN_BALANCE_R,
    VOL_MODE_SUR_BALANCE_L,
    VOL_MODE_SUR_BALANCE_R,
#endif
    VOL_MODE_QS_EFFECT,
    VOL_MODE_TREBLE,
    VOL_MODE_BASS
};

/*
*  spectial define
*/
#define VCD_STATE_TUNER  VCD_STATE_POWER//to add tunner 2-6-16 22:09
#define IsPlayerPause()  (play_state==VCD_STATE_PAUSE)
#define pbcoff()         (psd_st.psd_list_id= 0xffff)
#define IsPBCOn()        (psd_st.psd_list_id!=0xffff)
#define CLREAR_PASSWD    (0x0F)
#define DSP_WD_INIT      (-1)


/*
* servo timeout define
*/
#define NORM_TMOUT  500
#define PLAY_TMOUT  300
#define ERR_TMOUT   100
#define SHORT_TMOUT  50

#ifdef BRIGHTNESS_COLOR_KEY
//state
#define IDLE_STATE              0
#define BRIGHTNESS_STATE        1
#define COLOR_STATE             2

//timer
#define dBRICOL_TIMER           100 //100*100ms = 10s

//address in 24C02 used to store bri and col
#define BRIGHTNESS_ADDR         180
#define COLOR_ADDR              181

//total class
#define BRI_TOTAL_CLASS         15 //
#define COLOR_TOTAL_CLASS       15 //

//An2526 adjustment id
#define COLOR_ADJ           5
#define BRIGHTNESS_ADJ      8

#endif

//for usb/card
#if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE) 
#define MEDIA_EMPTY     1
#define MEDIA_NOT_EMPTY 0
#endif

//==============================================
//for QSI source switch     //added by JS   //20040726
#ifdef SUPPORT_QSI_SOURCE_SWITCH
enum
{
    source_disc=0,
    source_card=1,
    source_other
};
#endif
//===============================================
#ifdef SPHE1000_DVDSTATE_CALLBACK
#include "osdisp.h"                   //wjzhang//Maybe only 1000 use. Nono
#endif

//joshua, 20050711, modified for servo-debug function on OSD
#ifdef DVD_SERVO 
UINT8 servo_debug_message;
#endif

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
enum
{
    DVD_PLAY_MODE=0,
    USB_PLAY_MODE=1,
    CARD_PLAY_MODE,
#ifdef AV_IN_THROUGH_EXT_ADC
    AV_IN_MODE,
#endif
    DVB_T_MODE,
};

enum
{
    USB_CARD_NO_CHANGE=0,
    SWITCH_TO_USB_BUT_HAS_NO_USB=1,
    SWITCH_TO_CARD_BUT_HAS_NO_CARD,
    HAS_USB_AND_SWITCH_TO_USB,
    HAS_CARD_AND_SWITCH_TO_CARD,
    #ifdef AV_IN_THROUGH_EXT_ADC
    FROM_CARD_TO_AV_IN,
    #endif
    USB_CARD_WAS_PLUG_OUT,
};


#endif

#ifdef SUPPORT_MP3_ENCODER
enum
{
	test_stop 				= 0,
	test_device_exist 			= 1,
	test_FS_resdy 			= 2,
	test_target_dir 			= 3,
	test_target_file 			= 4,
	test_write_preset		= 5,
	test_write_data			= 6,
	test_close_file			= 7,
	test_wait_command		= 8,
};
#endif


#ifdef LINE_IN_ENCODE
// encoder type :  qiut add 06/01/13
enum
{

  real_time_encoder = 0x00,
  fast_time_encoder = 0x01,
  line_in_encoder = 0x02,

};
#endif


#ifdef USE_SETUP_SELECT_FONT
enum
{
    CP847 = 1,
    CP932 = 2,
    CP936,
    CP949,
    CP950,
    CP1250,
    CP1251,
    CP1252,
    CP1253,
    CP1254,
    CP1255,
    CP1256,
    CP1257,
    CP1258,
    ISO88591,
    ISO88592,
    ISO88595,
    ISO88596,
    ISO88597,
    ISO88598,
    ISO88599,
};
#endif

#ifdef SUPPORT_VFD_MESSAGE //chenzhao 20060117
enum
{
    VFD_MESSAGE_IDLE=0,
        
    VFD_MESSAGE_NOUPDATE,
    
    #ifdef SHOW_VOL_ON_VFD
    VFD_MESSAGE_VOL,
    #endif
    
    #ifdef SUPPORT_VFD_SHOW_TONE
    VFD_MESSAGE_EQ,
    #endif
    
    #ifdef SUPPORT_VFD_SHOW_EXBASS
    VFD_MESSAGE_EXBASS,
    #endif
    
    #ifdef SUPPORT_VFD_MENU
    VFD_MESSAGE_MENU,
    #endif
    
    #ifdef SUPPORT_VFD_SHOW_SURROUND_MODE
    VFD_MESSAGE_SURROUND,
    #endif
    
    VFD_MESSAGE_MAX,
};
#endif

#ifdef SUPPORT_PROLOGIC_II//chenzhao 20060120.moved from global.h
#ifdef USE_PL2_3DSURROUND_KEY
enum
{
    PROLOGIC_MODE_MOVIE=0,
    PROLOGIC_MODE_MUSIC,
    PROLOGIC_MODE_OFF,
    PROLOGIC_MODE_EMU,
    PROLOGIC_MODE_VIRTUAL,
    PROLOGIC_MODE_MATRIX,
};
#else //#ifdef USE_PL2_3DSURROUND_KEY
enum
{
    PROLOGIC_MODE_EMU=0,
    PROLOGIC_MODE_MUSIC,
    PROLOGIC_MODE_MOVIE,
    PROLOGIC_MODE_VIRTUAL,
    PROLOGIC_MODE_MATRIX,
    PROLOGIC_MODE_OFF,
};
#endif //#ifdef USE_PL2_3DSURROUND_KEY

enum
{
    SURROUND_MODE_5CH,
    SURROUND_MODE_2CH,
    #ifdef USE_PL2_3DSURROUND_KEY
    SURROUND_MODE_3D,
    #endif //#ifdef USE_PL2_3DSURROUND_KEY
};
#endif //SUPPORT_PROLOGIC_II

