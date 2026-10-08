#ifndef __OSD_H
#define __OSD_H


//extern const char _OsdMessegeFont1[][N_OSD_LANGS][14];
extern const char *const _OsdMessegeFont1[N_OSD_LANGS][MAX_OSD_STR_ID];//nono 2-7-8 17:43
//extern const char *const _OsdMessegeFont1[N_OSD_LANGS][256];
extern const char *const osd_err_str[N_OSD_LANGS][3];
extern const char *const lang_names[N_OSD_LANGS][MAX_OSD_LANG_STR_ID];
extern const UINT16 lang_639code[];

#ifdef USE_SETUP_SELECT_FONT
#ifdef ALCO_DVD_UI
extern const char *const divx_sutitle_osd_langs[N_DIVX_FONT_LANGS+2];
#else
#define MAX_N_DIVX_FONT_LANGS 21
extern const char *const divx_sutitle_osd_langs[MAX_N_DIVX_FONT_LANGS+2];
#endif
#endif

#ifdef NEW_SETUP_OSD            // majinping 2002-05-02 for new setup menu

#define STR_OS_SYS              5
#define STR_OS_LAN              6
#define STR_OS_AUD              7
#define STR_OS_SPK              8
#define STR_OS_DGT              9
#define STR_OS_EXT              10
#endif

#define REGION0                 0
#define REGION1                 1
#define REGION2                 2
#define REGION3                 3
#define REGION4                 4
#define REGION5                 5

#define STR_OS_DISC             0
#define STR_OS_NODISC           1
#define STR_OS_NO               2
#define STR_OS_TRACK            3
#define STR_OS_SVCD             4
//#define STR_OS_CHINESE          5//not used nono 3-3-22 14:20
#define STR_OS_DEINTLC          5
#define STR_OS_OPEN             6

#ifdef TOP_DOOR_LOADER
#define STR_OS_CLOSE            STR_OS_READ
#else
#define STR_OS_CLOSE            7
#endif

#define STR_OS_PLAY             8
#define STR_OS_REGION_5         9
#define STR_OS_PAUSE            10
#define STR_OS_RANDOM           11
#define STR_OS_RESUME           12
#define STR_OS_STOP             13
#define STR_OS_STEP             14
#define STR_OS_SELECT           15
#define STR_OS_READ             16
#define STR_OS_REGION_6         17
#define STR_OS_SIMULATE         18
#define STR_OS_FF               19
#define STR_OS_FB               20
#define STR_OS_NEXT             21

#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
#define STR_OS_PASSWD_EDIT       22
#else
//#define STR_OS_NEXT_PAGE        22         
#define STR_OS_SERVO_DEBUG      22      //joshua, 20050711, modified for servo-debug function on OSD
#endif

#define STR_OS_PREV             23

#define  STR_OS_DIR               24

#define STR_OS_RETURN           25
#define STR_OS_ICON_REP0        26
#define STR_OS_ICON_REP1        27
#define STR_OS_ICON_REPD        28
#define STR_OS_NONE             29
#define STR_OS_MENU             30
#define STR_OS_SCORE            31
//Jeff 20020411
#define STR_OS_MARK             32

#define STR_OS_BROWSE           33
#define STR_OS_PROG             34
//#define STR_OS_SLOW             35          //not use
#define STR_OS_SAVELOGO         35
#define STR_OS_BASS_MODE_1      36
#define STR_OS_REP              37
#define STR_OS_REP_DIR          38
#define STR_OS_REP_1            39
#define STR_OS_REP_ALL          40
#define STR_OS_REP_CNL          41
#define STR_OS_BASS_MODE_2      42
#define STR_OS_RATING_8         43
#define STR_OS_RATING_7         44

#define STR_OS_GOTO             45
#define STR_OS_MUTE             46
#define STR_OS_CHL              47
#define STR_OS_CHR              48
#define STR_OS_STEREO           49
#ifdef HANYANG_MUTEOFF   //caohui 2004-5-13 16:05
#define STR_OS_MUTEOFF           50
#elif defined(ORITRON_HK_DVD) || defined(OP_PLAYMODE)
#define STR_OS_MODE             50
#else
#define STR_OS_DEMUTE           50
#endif
#define STR_OS_LIVE             51
//#ifdef	KARAOKE_MENU
#if defined(KARAOKE_MENU)||defined(QSI_SETUP_MENU)//liweihua 2004-6-15
#define STR_OS_KARAOKE_SETUP    52  //S:KARAOKE设定
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
#define STR_OS_AC3_DIGITAL      52
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
#define STR_OS_MEDIA_DISC       52
#elif defined( SANJING_MIDI_DVD)   //ouyang 2004-11-2 15:50
#define STR_OS_MELODY_ON        52
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-23 22:03zhoulin
#define STR_OS_KARAOKE_SETUP    52
#endif

#define STR_OS_BASS_MODE_3      53


#define STR_OS_CDROM            54

#ifdef OP_CUST_UI//libing 2005-5-11 11:39
#define STR_OS_JPG_TIME             55
#else
#define STR_OS_TIME             55
#endif

#ifdef SHOW_MP4_INIT_STR    //wangwei-2004/4/28
    #define   STR_OS_MP4_INIT       56
#elif defined(RECORD_KEY)
    #ifdef NINTAUS_OSD_STR
		#define  STR_OS_RECORD_1           56
    #else
		#define STR_OS_RECORD_1SENTENCE    56 
	#endif
#elif defined(SUPPORT_ANGLE_MARK) //liweihua add 20031118
	#define STR_OS_ANGLE_MARK       56
#else
//#define STR_OS_9FRAME           56          //not use
#endif//#ifdef SHOW_MP4_INIT_STR    //wangwei-2004/4/28
#ifdef SANJING_MIDI_DVD           //ouyang 2004-11-2 15:50
#define STR_OS_MELODY_OFF        56
#endif

#ifndef NO_ZOOM_FUNCTION
#define STR_OS_ZOOM             57
#else //shenyj add for alco use 2006-9-4 03:47下午
#define STR_OS_HD_1080I         57
#endif

#ifdef RECORD_KEY
#ifdef NINTAUS_OSD_STR
#define STR_OS_RECORD_2     58
#else
#define STR_OS_RECORD_2SENTENCE    58 
#endif
#elif defined(SUPPORT_CC_ONOFF) //liweihua add 20031118
#define STR_OS_CLOSED_CAPTION       58
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
#define STR_OS_VOL_SR                58
#elif defined(DEFAULT_YES_NO_SELECT)
#define STR_OS_YES_YES              58

#else
//#define STR_OS_CANCEL           58          //not use
#if defined (DOWNMIX_OFF_DISP_5CH_ON)//zxb2005-5-8 14:46
#define STR_OS_5CH_ON	58
#elif defined(SUPPORT_HD_RESOLUTION) 
#define STR_OS_HD_OFF          58
#endif
#endif
#define STR_OS_AUDIO            59
#if defined(DEFAULT_YES_NO_SELECT)
#define STR_OS_NO_NO            60
#else
#define STR_OS_INTRO            60
#endif
#define STR_OS_SURR             61
#define STR_OS_PBC              62

#ifdef RECORD_KEY
#ifdef NINTAUS_OSD_STR
#define STR_OS_RECORD_3  63
#else
#define STR_OS_RECORD_3SENTENCE    63 
#endif
#elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
#define STR_OS_DTS_DIGITAL         63

#elif defined(ICON_REPEAT_FOLDER)
#define STR_OS_ICON_REPF            63  //zhuyf  2004-8-10

#else
//#define STR_OS_PBC_OFF          63            //=STR_OS_SEQUENCE
#endif

#define STR_OS_RAN_CNL          64
#define STR_OS_BASS_MANAGEMENT  65

#ifdef SUPPORT_TESTSPK
#define STR_OS_TESTSPK_MENU     66
#else
#define STR_OS_ALL              66//DISC ALL//S:全碟            
#endif
//#define STR_OS_POWER            66      


#define STR_OS_REP_A            67
#define STR_OS_PC_VGA           68          //not use
#define STR_OS_REP_AB           69
#define STR_OS_REP_AB_CNL       70
#define STR_OS_PROG_CNL         71

#define STR_OS_SPACE            72

#ifdef ONE_KEY_PASS//zhaoyanhua add 03-11-5 9:34
#define STR_OS_ONEKEY     73
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
#define STR_OS_VOL_CT               73
#elif defined(EASTECH_NO_PARENTAL_CONTROL)
#define STR_OS_NO_PARENTAL 73
#elif defined(SHOW_NO_AUDIO_INIT_STR)  //qinhua ,2005-10-10 14:18
#define STR_OS_NO_AUDIO          73            //not use 3-3-22 14:26
#else 

#endif 
//#define STR_OS_ENGLISH          73            //not use 3-3-22 14:26
#define STR_OS_VCD10            74

//zhaoyanhua add 03-10-28 19:15
#ifdef BBK_DVD
#define STR_OS_LIGHT_MUSIC      75
#elif defined (NINTAUS_DVD)
#define STR_OS_RESTORE_SETUP1   75
#elif defined (MIDI_EJECT_PASSWORD)    //ouyang add for eject pwd in midi04-11-20
#define STR_OS_EJECT_PASSWORD    75 
#elif defined(EASTECH_PHILIPS_SETUP_MENU)
#define  STR_OS_UPDATA_NAME         75   
#elif defined(SHOW_DIVX_WEB_INIT_STR)//qinhua ,2005-10-10 14:18
#define STR_OS_DIVX_WEB    75  
#else

#endif


//#define STR_OS_VCD11            75          //not use
//#define STR_OS_VCD20            76          //not use
#if defined(SHOW_VCD_VER_INFO)||defined(SYBER_DVD)  //yaowh modify 04-08-03
#define STR_OS_VCD20            76          //xulf 2003-11-17
#elif defined(SHOW_DIVX_WEB_INIT_STR) //qinhua ,2005-10-10 14:18
#define STR_OS_REGISTER_CODE    76  
#elif defined(EASTECH_PHILIPS_SETUP_MENU)
#define STR_OS_OPU_TYPE        76
#else
#define STR_OS_ELECTRON         76
#endif

#ifdef EASTECH_PHILIPS_SETUP_MENU
#define STR_OS_FLASH              77
#elif defined(SCALER_6500)
   #ifdef HDMI_FMT_RESTORE
          #define STR_OS_FMT_CFM          77        //helm to confirm format
   #endif  
#else
#define STR_OS_CVBS             77
//#define STR_OS_MP3              77      //not use
#endif

#define STR_OS_CDDA             78

#define STR_OS_48K              79
#define STR_OS_96K              80
#define STR_OS_192K             81

#define STR_OS_PIC_UP           82
#define STR_OS_PIC_DN           83
#define STR_OS_PIC_L            84
#define STR_OS_PIC_R            85
#define STR_OS_CHP              86
#define STR_OS_ECHO             87
#define STR_OS_TT               88
#define STR_OS_BAND             89
#define STR_OS_VOL              90
#define STR_OS_FREQ_MASK     91
#define STR_OS_KEY              92
#define STR_OS_S_VIDEO          93

#define STR_OS_9FRAME_1         94
#define STR_OS_AUTO_L           95
#define STR_OS_AUTO_R           96
#define STR_OS_LOW_SHARP        97      // for VIDEO SETUP

#define STR_OS_SEQUENCE         98
#define STR_OS_MENUPLAY         99
#define STR_OS_DISCTIME         100  
//#define STR_OS_SFE_OUT          100//not use
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)  // fengjl  3-11-24 13:44
#define STR_OS_ONEKEY_SETUP     101
#define STR_OS_PROFESSION_SETUP 102
#elif defined(NINTAUS_DVD)
#define STR_OS_PICTURE_UD       101
#define STR_OS_PICTURE_LR       102
#elif defined(SHOW_STANDBY_TIMER)//suqiaoli add 2003-7-30
#define  STR_OS_VFD_TIME_NUM      101
#define  STR_OS_VFD_TIME          102
#elif defined(SELECT_MEDIA_IN_SETUPMENU)
#define STR_OS_MEDIA_USB		101
#define STR_OS_MEDIA_CARD		102
#elif defined(SLEEP_CONTROL_COUNTER)
#define STR_OS_SLEEP_120MIN      101
#define STR_OS_SLEEP_90MIN      102
#elif defined(AUTO_LOAD_MODE_SETUP)
#define STR_OS_MODE_1           101
#define STR_OS_MODE_2           102
#else
//#define STR_OS_SFE_STD          101//not use
//#define STR_OS_SFE_ENHANCE      102//not use
#endif

#ifdef OP_CUST_UI
#define STR_OS_DIVX         103
#else
#define STR_OS_MID_SHARP        103     // for VIDEO SETUP
#endif
#define STR_OS_PROGPLAY         104
#define STR_OS_HIGH_SHARP       105     // for VIDEO SETUP
#define STR_OS_DYNAMICRANGE     106
#define STR_OS_DVD              107
#define STR_OS_OSD              108
#define STR_OS_SUBTITLE         109
#ifdef TONIC_DVD
#define STR_OS_TV_SYS         	110
#define STR_OS_TV_RATIO         111
#else
#define STR_OS_TV_RATIO         110
#define STR_OS_TV_SYS           111
#endif
#define STR_OS_EXIT_MENU        112
#define STR_OS_AUD_OUT          113
#define STR_OS_VIDEO            114
#define STR_OS_PASSWORD         115
#define STR_OS_RATING           116
#define STR_OS_BITSTREAM        117

#ifdef SUPPORT_PALN //4-1-12 10:54
#define STR_OS_PALN             118
#elif defined(PASSWORD_IN_CH)
#define STR_OS_PASSWORD_ERROR   118
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
#define  STR_OS_VOL_SW          118
#else
#define STR_OS_ANALOG_6CH       118
#endif

#define STR_OS_STEREO_PCM       119

#ifdef SUPPORT_PALM         //gerry,2004-1-8 13:52
#define STR_OS_PALM             120
#elif defined(PASSWORD_IN_CH)
#define STR_OS_PASSWORD_RIGHT   120
#elif defined(SLEEP_CONTROL_COUNTER)
#define STR_OS_SLEEP_45MIN    120
#elif defined(AUTO_LOAD_MODE_SETUP)
#define STR_OS_MODE_3           120
#else
//#define STR_OS_ANALOG_2CH       120
#endif

#define STR_OS_YCbCr            121
#define STR_OS_AUTO             122
#define STR_OS_OFF              123
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
#define STR_OS_TRACKTIME       124//zhaoyanhua add for NEW_SYTLE_WINDOW2003-12-6 14:06
//#define STR_OS_T_C_T            124
#elif defined(SLEEP_CONTROL_COUNTER)
#define STR_OS_SLEEP_60MIN    124
#elif defined(SHOW_DRM_REGISTRATION_CODE_IN_SETUP)
#define STR_OS_DRM_REGISTRATION_CODE 124
#endif

#define STR_OS_CHAPTER          125
#define STR_OS_TITLE            126
#define STR_OS_ANGLE            127
#define STR_OS_P_SCAN_YUV       128
#define STR_OS_16_9             129
#define STR_OS_4_3LB            130
#define STR_OS_4_3PS            131
#define STR_OS_PAL              132
#define STR_OS_NTSC             133
#define STR_OS_PAL60            134

#ifdef  RATING_8
#define STR_OS_RATING_3         135
#define STR_OS_RATING_2         136
#define STR_OS_RATING_1         137
#else
#define STR_OS_NO_ADULT         135
#define STR_OS_KID_ONLY         136
#define STR_OS_VIEW_ALL         137
#endif

#ifdef USE_SETUP_SELECT_FONT
#define STR_OS_DIVX_FONT_CODE 138
#else
#define STR_OS_6CH_SETUP        138
#endif

#define STR_OS_SUBWOOFER        139
#define STR_OS_SATURATION       140     // for VIDEO SETUP
#define STR_OS_ON               141
#define STR_OS_DOBLY            142
#define STR_OS_ICON_CLOCK       143
#define STR_OS_ICON_SPK         144
#define STR_OS_CLEAR            145
#define STR_OS_T_C              146
#define STR_OS_                 147
#define STR_OS_F                148
#define STR_OS_EDIT             149

#ifdef RECORD_KEY 
#define STR_OS_RECORD_RESUME    150
#elif defined(SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE)  //added by wangwei,2004-10-24 23:15
#define STR_OS_SUBTITLE_LANG_2ND_SETUP  150
#elif defined(SCALER_6500)
#else
//#define STR_OS_DIR1             150//not use nono 2003-11-16 23:16
#endif

#ifdef QSI_SETUP_MENU//for Screensaver time in QSI setup menu,liweihua add 2004-6-15
#define STR_OS_1_MIN            151
#define STR_OS_5_MIN            152
#define STR_OS_10_MIN           153
#define STR_OS_30_MIN           154
#elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/2/18
   #define STR_OS_15_SEC            151
   #define STR_OS_30_SEC            152
   #define STR_OS_45_SEC            153
   #define STR_OS_60_SEC            154
#else
#ifdef BBK_DVD
#define STR_OS_5_1_CHANNEL        151
#elif defined(NINTAUS_DVD)
#define STR_OS_PICTURE_ROTATE_LEFT 151
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-23 19:04 zhoulin
#define STR_OS_5_1_CHANNEL        151
#else
//#define STR_OS_DIR2             151//not use nono 2003-11-16 23:16
#endif

#define STR_OS_DIR3             152
#define STR_OS_DIR4             153

#if defined(SUPPORT_PALNc)//4-1-12 10:54
#define STR_OS_PALNc                154
#elif defined(SLEEP_CONTROL_COUNTER)
#define STR_OS_SLEEP_30MIN    154
#elif defined(AUTO_LOAD_MODE_SETUP)
#define STR_OS_MODE_6           154
#else
//#define STR_OS_DIR5             154//not use nono 3-12-3 10:10
#endif
#endif//#ifdef QSI_SETUP_MENU

#define STR_OS_LOCK             155
#define STR_OS_UNLOCK           156
#define STR_OS_HUE              157     // for VIDEO SETUP

#define STR_OS_PROLOGIC         158

#ifdef DISPLAY_INDIVIDUAL_SPK_VOLUME//2005-4-27 10:01 zhoulin
#define STR_OS_PL_MOVIE         141
#else
#define STR_OS_PL_MOVIE         159
#endif

#define STR_OS_PL_MUSIC         160

#ifdef SUPPORT_IR_I2P_KEY
#define STR_OS_INTERLACE        161//NONO 4-1-13 11:01
#elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
#define STR_OS_PL_PANORAMA      161
#elif defined(SUPPORT_HD_RESOLUTION) 
#define STR_OS_HD_720P             161 
#else//SUPPORT_IR_I2P_KEY
//#define STR_OS_TT_CH            161
#endif//SUPPORT_IR_I2P_KEY

//#ifdef FUSS_DVD//nono 20020713
#if defined(REMAIN_TIME)
#define STR_OS_ICON_T           162
#elif defined(SUPPORT_HD_RESOLUTION)&& !defined(ALCO_DVD_UI) //shenyj modify 2006-9-4 03:46下午
#define STR_OS_HD_1080I              162
#else
//#define STR_OS_BOOKMARK         162
#endif

#define STR_OS_DIR0             163
#define STR_OS_CONTRAST         164     // for VIDEO SETUP
#define STR_OS_DIR7             165
#define STR_OS_DIR8             166
#define STR_OS_DIR9             167
#define STR_OS_CH               168
#define STR_OS_BRIGHTNESS       169     // for VIDEO SETUP
#define STR_OS_FIRMWARE_ID      170
#ifdef OP_CUST_UI
#define STR_OS_CHECK          171
#else
#define STR_OS_CHIP_ID          171
#endif
#define STR_OS_REGION_CODE      172
//#define STR_OS_FUNCTION         173
//#define STR_OS_MODE             174
#define STR_OS_MEMORY             173
#define STR_OS_DYNAMIC             174

#ifdef  DISPLAY_INDIVIDUAL_SPK_VOLUME
#define STR_OS_VOL_L           175
#define STR_OS_VOL_R        176
#define STR_OS_VOL_SL             177
#else
#define STR_OS_LIVELY           175
#define STR_OS_SHOWPLACE        176
#define STR_OS_MILD             177
#endif

#define STR_OS_MIC_VOL_1          178
#define STR_OS_MIC_VOL_2          179
//#define STR_OS_COMPARE          178
//#define STR_OS_COUNTER          179

#ifdef FUSS_DVD_AVD276
#define STR_TOS_PREV_CHAPTER    180
#define STR_TOS_NEXT_CHAPTER    181
//#elif defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)
#define STR_OS_NEXT_PAGE        180
#define STR_OS_PREV_PAGE        181
#elif defined(SUPPORT_FUNCTION_MENU) 
#define STR_OS_BATTERY_STATUS   180
#define STR_OS_SETUP            181      
#elif defined(DISPLAY_INDIVIDUAL_SPK_VOLUME)//2005-4-19 17:13 zhoulin
#define        STR_OS_BASS       180
#define        STR_OS_TREMBLE    181
#elif defined(ORITRON_HK_DVD) || defined(OP_PLAYMODE)//libing 2005-8-19 19:07
#define STR_OS_PLAYMODE		180
#define STR_OS_REPEAT           181
#else
//#define STR_OS_LEVEL            180
//#define STR_OS_HIGH             181
#endif

#ifdef SUPPORT_IR_I2P_KEY
#define STR_OS_PROGRESSIVE        182//NONO 4-1-13 11:01
#elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
#define STR_OS_PL_CENTER_WIDTH      182
#else//#ifdef SUPPORT_IR_I2P_KEY
//#define STR_OS_NORMAL           182
#endif//#ifdef SUPPORT_IR_I2P_KEY

#ifdef NEWSTYLE_WINDOW
#define STR_OS_PLAYTIME             183
#define STR_OS_TITLETIME            184
#define STR_OS_CHPTIME              185
#else//#ifdef NEWSTYLE_WINDOW

#ifdef SCALER_6500  //helm for 6500 scaler 050707
    #define STR_OS_VGA				102//22	//chenzhao20060206 for avoid conflict with SELECT_MEDIA_IN_SETUPMENU
    #define STR_OS_SVGA				56//101
    #define STR_OS_XGA				101//56
           #define STR_OS_SXGA				58
           #define STR_OS_480P				185
           #define STR_OS_480P576P			73
           #define STR_OS_720P		   	        75
    #define STR_OS_1080I            22//102
    #ifdef CD_INTRO_IN_PLAYMODE //chenzhao20060124
        #define STR_OS_CD_INTRO  183
    #else
           #define STR_OS_HDCP_FAIL                    183
    #endif
    #if defined(SUPPORT_ALL_CDDA_DISCS_REPEAT) //chenzhao20060206
        #define STR_OS_REP_DISCS  184
    #endif
#else//#ifdef SCALER_6500
      #if defined(BRIGHTNESS_COLOR_KEY)||defined(VIEW_MODE_KEY)
          #define STR_OS_COLOR				183
          #define STR_OS_VIEW_MODE_NORMAL		184
          #define STR_OS_VIEW_MODE_FULL   	        185
      #elif defined(SUPPORT_DVD_NATIVE_GAME)	//linrc for NATIVE_GAME 2005-10-18 14:44
          #define STR_OS_GAME 183
          #define STR_OS_GAME_BOXMAN 184
          #define STR_OS_GAME_TETRIS 185
    #else
        #if defined( CD_INTRO_IN_PLAYMODE) //chenzhao20060124
		  #define STR_OS_CD_INTRO                     183
        #endif
        #if defined(SUPPORT_ALL_CDDA_DISCS_REPEAT) //chenzhao20060206
            #define STR_OS_REP_DISCS  184
        #endif
	  #endif//#if defined(BRIGHTNESS_COLOR_KEY)||defined(VIEW_MODE_KEY)
#endif//#ifdef SCALER_6500

#endif//#ifdef NEWSTYLE_WINDOW


#define STR_OS_DIR10            186
#define STR_OS_DIR11            187
#define STR_OS_CONCERT          188
#define STR_OS_CHURCH           189
#define STR_OS_PASSIVE          190
#define STR_OS_WIDE             191
#ifdef USER_MPEG_LOGO
#define STR_OS_SELECT_LOGO          192
#define STR_OS_MPEG_LOGO            193
#else

#ifdef SCALER_6500 //helm for 6500 scaler 050707
        #ifndef HDCP_CUSTOM//Modifed by chenzhao on 2004-12-1 11:43   
               #define STR_OS_DVI311_FORMAT    192
        #else
               #define STR_OS_HDCP             192
        #endif
        #define STR_SPHE6500_FMT	       193
#elif defined(PULIANG_DVD)  //yaowh add 04-12-17
        #define FIRM_WARE_VER            192
        #define REGION_CODE              193
#elif defined(SLEEP_CONTROL_COUNTER)
        #define STR_OS_SLEEP_15MIN       192
        #define STR_OS_SLEEP_OFF         193
#elif defined(AUTO_LOAD_MODE_SETUP)
        #define STR_OS_MODE_4            192
        #define STR_OS_MODE_5            193
#elif defined(SUPPORT_DVD_NATIVE_GAME)
        #define STR_OS_GAME_HITRAT       192
#else
#endif //SCALER_6500
#endif //USER_MPEG_LOGO


#define STR_OS_EQ               194
#define STR_OS_STANDARD         195
#define STR_OS_CLASSIC          196
#define STR_OS_ROCK             197
#define STR_OS_JAZZ             198
#define STR_OS_POP              199
#define STR_OS_USER             200
#define STR_OS_ATTRIB           201
#define STR_OS_SF               202
#define STR_OS_SB               203

#define STR_OS_ICON_C           204

#define STR_OS_CSPK             205
#define STR_OS_SSPK             206
#define STR_OS_TV_RGB           207

#define STR_OS_RATING_4         208

#define STR_OS_CSPK_DELAY       209
#define STR_OS_SSPK_DELAY       210
#define STR_OS_FSPK             211
#define STR_OS_VIDEO_SETUP      212     // for VIDEO SETUP
#define STR_OS_SHARPNESS        213     // for VIDEO SETUP
#define STR_OS_SYS_SETUP        214
#ifdef PULIANG_DVD  //yaowh add 04-12-17
    #define STR_OS_DIGTAL_SETUP     215
#else
#define STR_OS_SPK_SETUP        215
#endif
#define STR_OS_AUD_SETUP        216
#define STR_OS_DEFAULT_SETUP    217

#ifdef SELECT_MEDIA_IN_SETUPMENU
#define STR_OS_MEDIA_TYPE       218
#elif defined(SLEEP_CONTROL_COUNTER)
#define STR_OS_SLEEP_SETUP    218
#elif defined(AUTO_LOAD_MODE_SETUP)
#define STR_OS_MODE           218
#elif defined(ALCO_DIVX_UI)//0//defined(DRM_CODE) 
#define STR_OS_DRM_CODE         218     //WSLEE for generate drm code 050615
#else
#define STR_OS_GROUP            218
#endif

#define STR_OS_SSAVER_SETUP     219

#ifdef ORITRON_PASSWORD//libing 2005-4-29 9:53
#define STR_OS_SET_DEFAULT    220
#define STR_OS_CLAER_PWD         221
#define STR_OS_LAD_LOCK       222
#else
#define STR_OS_SSAVER_1         220
#define STR_OS_SSAVER_2         221
#define STR_OS_SSAVER_3         222
#endif
#define STR_OS_RATING_5         223
#define STR_OS_RATING_6         224

#define STR_OS_ERR_DISC         225
#ifdef PULIANG_DVD  //yaowh add 04-12-17
#define STR_OS_SPK_SETUP        226
#else
#define STR_OS_DIGTAL_SETUP     226
#endif
#ifdef SUPPORT_FUNCTION_MENU
#define STR_OS_FW_VERSION      	227
#define STR_OS_MIC_VOL          228
#else
#define STR_OS_MIC_ONOFF        227
#define STR_OS_MIC_VOL          228
#endif

#if !defined(ONLY_HAVE_RGB_RGBOFF)
#define STR_OS_CD_DEBUG         229
#else
#define STR_OS_TV_RGB_OFF        229
#endif
#define STR_OS_SMART_UPGRADE    230
#define STR_OS_UPGRADE_TO       231
#define STR_OS_UPGRADING        232
#define STR_OS_NOT_POWEROFF     233
#define STR_OS_REGION_0         234
#define STR_OS_REGION_1         235
#define STR_OS_REGION_2         236
#define STR_OS_REGION_3         237
#define STR_OS_REGION_4         238
#define STR_OS_LANG_SETUP       239
//#define STR_OS_SURROUND_SETUP   240     //not use
#ifdef JIEKE_DVD
#define STR_OS_JIEKE_SETUP    240
#elif defined(BBK_DVD)
#define STR_OS_NO_ZOOM        240 
#elif defined(BAT_DETECT)||defined(GBM_PORTABLE_DVD)||defined(SUNPLUS_8202P_DEMOBOARD) //Jack move to here
#define STR_OS_LOWBAT           240     //rbhung for GBM Portable DVD
#elif defined(NINTAUS_DVD)
#define  STR_OS_PICTURE_ROTATE_RIGHT  240
#elif defined(SUPPORT_FUNCTION_MENU)
#define STR_OS_DISPLAY          240
#elif defined(SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //chenzhao 2005-5-12
#define STR_OS_PL_DIMENSION     240
#elif defined(AUTO_LOAD_MODE_SETUP)
#define STR_OS_MODE_7                240
#elif defined(SUPPORT_HD_RESOLUTION)     
#define STR_OS_HD_OUTPUT             240                         //added for supporting HD, by robert.chang, 2006/04/10
#endif


#define STR_OS_RETURN_MAIN_SETUP        241
#define STR_OS_AUDIO_LANG_SETUP         242
#define STR_OS_SUBTITLE_LANG_SETUP      243
#define STR_OS_MENU_LANG_SETUP  244
#define STR_OS_DOWNMIX_SETUP    245
#define STR_OS_RESTORE_SETUP    246
#define STR_OS_LTRT_SETUP       247
#define STR_OS_VSURROUND_SETUP  248
#define STR_OS_DOLBY_OP_SETUP   249
#define STR_OS_DOLBY_LINE_SETUP 250
#define STR_OS_DOLBY_RF_SETUP   251
#define STR_OS_DUAL_MONO_SETUP  252
#define STR_OS_MIX_MONO_SETUP   253
#define STR_OS_SURROUND_MODE    254
#define STR_OS_PRE_STOP         255

#if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)   //sunzhh 20050430
#define STR_OS_INSTALL_SETUP      197
#define STR_OS_CHANNEL_SETUP      198

#define STR_OS_DVBT_CONFIG      186
#define STR_OS_AUTO_SCAN        187
#define STR_OS_MANUAL_SCAN      188
#define STR_OS_DVB_LANGUAGE     189
#define STR_OS_TIME_ZONE        190

#define STR_OS_TV_CHANNEL       191
#define STR_OS_RADIO_CHANNEL    192
#define STR_OS_ADD_CHANNEL      193
#define STR_OS_EDIT_CHANNEL     194
#define STR_OS_DEL_CHANNEL      195
#define STR_OS_LOCK_CHANNEL     196  //haoy 2005-04-14

#define STR_OS_TIME_ZONE1       196
#define STR_OS_TIME_ZONE2       197
#define STR_OS_TIME_ZONE3       198
#define STR_OS_TIME_ZONE4       199
#define STR_OS_TIME_ZONE5       200
#define STR_DVB_BASE_INDEX      STR_OS_TIME_ZONE1        
#endif

//=========================================================================
#ifdef EXCEED_MAX_NUMBER //fengjl add 4-3-11 23:10  
// NOTE: If your string's number exceed 255, you must add the define 

#ifdef GBM_PORTABLE_DVD
#define STR_OS_LOWBAT           256     //rbhung for GBM Portable DVD
#else
#define STR_OS_PICTURE_ROTATE   256  
#endif

#define STR_OS_PICTURE_UPTURN   257

#ifdef VIDEO_SETUP_NEW_GUI   //fengjl add 4-1-9 13:02
#define STR_OS_ENTER_RETURN     258
#else
#define STR_OS_REP_TITLE        258
#endif

#ifdef SETUP_PASSWORD_GUI      //fengjl add  4-1-19 17:09
#define STR_OS_PASSWD_ERROR     259
#define STR_OS_PASSWD_SENTENCE1 260
#else
#define STR_OS_REP_CHAPTER      259
#define STR_OS_REP_GROUP        260
#endif

#define STR_OS_PASSWD_SENTENCE2 261
#define STR_OS_OLD_PASSWD       262
#define STR_OS_NEW_PASSWD       263 
#endif  //EXCEED_MAX_NUMBER 

#endif/*__OSD_H*/

#ifdef CORTROL_VCD_ONF
#define STR_OS_VCD              264
#endif



#if defined(MUSTEK_PORTABLE_DVD)&&!defined(MUSTEK_K100D_MODEL)
#define STR_OS_MAIN_PAGE			226
#define	STR_OS_ANGLE_MARK		220
#define	STR_OS_NIGHT_MODE		221
//#define STR_OS_TV_TUNER_SETUP		215
//#define	STR_OS_DIGITAL_OUT		113
//#define	STR_OS_DOWNMIX_SETUP	245
//#define STR_OS_TV_RATIO			110
//#define	STR_OS_VIDEO_OUTPUT	114
//#define STR_OS_PARENTAL_CTRL		116
//#define STR_OS_TV_SIGNAL			249
//#define STR_OS_AUTO_SEARCH		250
//#define STR_OS_FINE_TUNE			251
//#define STR_OS_FAVORITE_LIST		252
//#define STR_OS_CHANNEL				253
//#define STR_OS_ADD					205
//#define STR_OS_DEL					206
//#define STR_OS_ANTENNA				209
//#define STR_OS_CATV					210
//#define STR_OS_START				211
#endif

