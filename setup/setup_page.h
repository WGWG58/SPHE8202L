//special page index
#if  0//eastech
//page index-0
#define SYSPAGE         0
#ifdef AUTO_ADJUST_TV_TYPE  //lijd 2004-9-15 13:34
#define  SETUP_TV_TYPE           setup_sel[SYSPAGE][3]
#endif
#define TV_FORMAT       0
#define SSAVERITEM      1       //Screen Saver item index
	//#define VIDEOITEM      MODE_MAX_PSCAN//not use nono mark it. 2003-10-20 21:50
#define PASSWDITEM      4
#define GRADEITEM       5
#define SysNextPage		7
#define SAME_DISC_RESUME_ITEM	1
#define NEXTPAGEITEM	6
#define PREVPAGEITEM	3




//page index-1
#define LANGPAGE        1
#define LANGITEM        0

//page index-2
#define AUDPAGE         2
#define DIGIOUTITEM     0

 
#define SPDIFBITSTREAM  2
#define SPDIFPCM        3
#define SPDIFSIMULATE   4
#define MICONOFFITEM    4		//gerry,3-10-25 10:30
#define ECHOITEM        2
#define MICITEM         3
#define VOLCTRLSTART    1    
#define VOLCTRLEND      1//4   
#define MICAUTO         2

#define MICOFF          2
//page index-3
#define VIDEOPAGE		3



#define AC3DOWNMIXITEM  0    
#define SPKSTART        3
#define SPKEND          4
#define DOWNMIXLTRT     2   //Jeff 20020822
#define DOWNMIXSTEREO   3
#define DOWNMIXVSRND    4
#define AC3DOWNMIXOFF   5


//page index-4
#define MULTISPKPAGE    4      //valid when AC3 or DTS



//page index-5
#define AC3DIGITALPAGE  5      //valid when AC3
//CUSTM page index(for system admin use)

#define CUSTMPAGEINDEX  6
#define KEYITEM         1
#define CUSTMPASSWDITEM 4
#define CUSTMRATEITEM	3			// Maoyong 2004.03.25
#define C_UNLOCK    1
#define C_LOCK      0

#ifdef  TEST_BASS_MANAGEMENT 
    #define BASS_CONFIG_X   0   //no bass management necessary
    #define BASS_CONFIG_1   1   //bass management config1
    #define BASS_CONFIG_S   2   //simplified bass management
    #define BASS_CONFIG_3   3   //bass management config3
    #define BASS_CONFIG_CAR_S   4   //car audio,modification of simplified bass management
#endif


//defition for special items

#define SETUP_TV_FORMAT             setup_sel[SYSPAGE][0]
#define SETUP_SSAVER                	setup_sel[SYSPAGE][1]
#define SETUP_VIDEO_FORMAT       setup_sel[SYSPAGE][2]
#define SETUP_PASSWORD              setup_sel[SYSPAGE][4]
#define SETUP_GRADE                 	setup_sel[SYSPAGE][5]

#define SETUP_OSD_LANG              setup_sel[LANGPAGE][0]

#define SETUP_SPDIF                 	setup_sel[AUDPAGE][0]
#define SETUP_DOWN_SAMPLE		setup_sel[AUDPAGE][1]

#define SETUP_MIC_ONF               	setup_sel[AUDPAGE][6]//[4]//setup_sel[AUDPAGE][1]
#define SETUP_ECHO                  	setup_sel[AUDPAGE][6]//[5]//setup_sel[AUDPAGE][2]
#define SETUP_MIC_VOL               	setup_sel[AUDPAGE][6]//[3]//setup_sel[AUDPAGE][3]

	#define SETUP_KEY                   setup_sel[4][5]
	  
/*
*  Prologic-2  and Freq. mask
*/
#define PROLOGIC_OFF                            4//terry,2004/1/9 10:57AM	        
#define LPCM_ITEM                                       5//terry,2004/2/4 02:43PM	       
#define SETUP_FREQ_MASK				setup_sel[AUDPAGE][LPCM_ITEM]//setup_sel[AUDPAGE][5]
		
#define SETUP_BRIGHTNESS			setup_sel[VIDEOPAGE][0]
#define SETUP_CONTRAST				setup_sel[VIDEOPAGE][1]
#define SETUP_HUE					setup_sel[VIDEOPAGE][2]
#define SETUP_SATURATION			setup_sel[VIDEOPAGE][3]


#define SETUP_SPK_DOWNMIX           	setup_sel[MULTISPKPAGE][0]
#define SETUP_SPK_SUBWOOFER         	setup_sel[MULTISPKPAGE][1]
#define SETUP_BASS_MODE             	setup_sel[MULTISPKPAGE][2]
#define SETUP_SPK_CENTER_DELAY      setup_sel[MULTISPKPAGE][3]
#define SETUP_SPK_SURROUND_DELAY    setup_sel[MULTISPKPAGE][4]
#define ITEM_SPK_DOWNMIX            	setup_item[MULTISPKPAGE][0]


#define SETUP_AC3DIGITAL_DYNA       setup_sel[AC3DIGITALPAGE][1]    
#define SETUP_AC3DIGITAL_LnR        setup_sel[AC3DIGITALPAGE][2]    
#define ITEM_AC3DIGITAL_LnR         setup_item[AC3DIGITALPAGE][2]
#define SETUP_AC3DIGITAL_OUTMODE    setup_sel[AC3DIGITALPAGE][0]
#define ITEM_AC3DIGITAL_OUTMODE     setup_item[AC3DIGITALPAGE][0]

#define AC3OUTMODEITEM              0
#define AC3DYNAMICITEM1             1
#define AC3DYNAMICITEM2             2 //(2+2)

#define SETUP_CUSTM_REGION          setup_sel[CUSTMPAGEINDEX][2]

#define SETUP_CUSTM_GRADE           setup_sel[CUSTMPAGEINDEX][3]

#endif   //#IF  1//eastech

//special page index
//page index-0
#if !defined(DVB_MENU_SETUP_STYLE) && !defined(DVB_MENU_TYPE1)
#define SYSPAGE         0
#else
#define INSTALLPAGE     0
#define CHANNELPAGE     1
#define SYSPAGE         2

#define SETUP_DVB_LANG              setup_sel[INSTALLPAGE][1]
#define SETUP_DVB_TIME_ZONE         setup_sel[INSTALLPAGE][2]

#endif

#ifdef DP3240_SETUP_MENU
#define TV_FORMAT       0
#define  SETUP_TV_TYPE   1       
#define SLEEEP_CONTROLLER 2
#ifdef SETUP_ITEM_NO_SCREEN_SAVER_AND_DEFAULT_ON
#define PASSWDITEM      3
#define GRADEITEM       4
#define SysNextPage		7
#define NEXTPAGEITEM	6
#define PREVPAGEITEM	3
#define SAME_DISC_RESUME_ITEM	1
#else //#ifdef SETUP_ITEM_NO_SCREEN_SAVER_AND_DEFAULT_ON
#define SSAVERITEM      3     //Screen Saver item index
#define PASSWDITEM      4
#define GRADEITEM       5
#define SysNextPage		7
#define NEXTPAGEITEM	6
#define PREVPAGEITEM	3
#define SAME_DISC_RESUME_ITEM	1
#endif //#ifdef SETUP_ITEM_NO_SCREEN_SAVER_AND_DEFAULT_ON

#else//#ifdef DP3240_SETUP_MENU
#ifdef FUSS_TV_DVD//nono 2-8-20 13:05
    #define SSAVERITEM      0//3       //Screen Saver item index
    #define PASSWDITEM      1//4
    #define GRADEITEM       2//5
#else
    #ifdef NO_TV_FORMAT
    #define SSAVERITEM      0       //Screen Saver item index
    #elif defined(SELECT_MEDIA_IN_SETUPMENU)    //Maoyonng 2004-8-10 14:52
    #define ITEM_MEDIA_TYPE 0
    #define TV_FORMAT       1
    #else//NO_TV_FORMAT
    #define TV_FORMAT       0
#ifdef NO_SCREEN_SAVER
    #define SSAVERITEM      7       //Screen Saver item index
#else
    #define SSAVERITEM      1       //Screen Saver item index
#endif
    //#define VIDEOITEM      MODE_MAX_PSCAN//not use nono mark it. 2003-10-20 21:50
    #endif//NO_TV_FORMAT

    #if defined(HIMAGE_CANADA_CUS)&& !defined(INCLUDE_YUV)
        #define PASSWDITEM      3//4
        #define GRADEITEM       4//5
    #elif ( defined(DELETE_VIDEO_ITEM)&&defined(NO_TV_FORMAT)  )||defined(GBM_FULL_FUNCTION)
        #define PASSWDITEM      2
        #define GRADEITEM       3
    #elif defined(DELETE_VIDEO_ITEM)||defined(NO_TV_FORMAT)
        #define PASSWDITEM      3
        #define GRADEITEM       4
    #elif defined(ARGUS_PORTABLE_DVD)
        #define PASSWDITEM      3
        #define GRADEITEM       4    
    #elif defined(NO_SCREEN_SAVER)
        #define PASSWDITEM      3
        #define GRADEITEM       4
    #else
        #define PASSWDITEM      4
        #define GRADEITEM       5
    #endif
#endif
#endif//#ifdef DP3240_SETUP_MENU

//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)       //freyman 2004-3-25 23:57
#define SysNextPage     7

#ifdef GBM_FULL_FUNCTION
#define SAME_DISC_RESUME_ITEM   0
#elif defined(NOT_SHOW_SAME_DISC_RESUME)//GBM_FULL_FUNCTION
#define SAME_DISC_RESUME_ITEM   7
#else//GBM_FULL_FUNCTION
#define SAME_DISC_RESUME_ITEM   1
#endif//GBM_FULL_FUNCTION


#ifdef GBM_FULL_FUNCTION
#define NEXTPAGEITEM    5
#define PREVPAGEITEM    4
#elif defined(NOT_SHOW_SAME_DISC_RESUME)//GBM_FULL_FUNCTION
#define NEXTPAGEITEM    6
#define PREVPAGEITEM    2
#else//GBM_FULL_FUNCTION
#define NEXTPAGEITEM    6
#define PREVPAGEITEM    3
#endif//GBM_FULL_FUNCTION
#endif 

#ifdef USER_MPEG_LOGO

#define MPEG_LOGO_ON    3

    #ifdef NOT_SHOW_SAME_DISC_RESUME
    #define MPEG_LOGO_ITEM      1
    #else//NOT_SHOW_SAME_DISC_RESUME
    #define MPEG_LOGO_ITEM      2
    #endif//NOT_SHOW_SAME_DISC_RESUME
#endif//USER_MPEG_LOGO

//page index-1
#if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)          //sunzhh 20050430
#define LANGPAGE        3
#else
#define LANGPAGE        1
#endif

#define LANGITEM        0

//page index-2
#if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)          //sunzhh 20050430
#define AUDPAGE         4
#else
#define AUDPAGE        2
#endif


#define DIGIOUTITEM     0
//axel,2003/12/12 05:46PM
#if defined(BBK_DVD)||defined(EASTECH_NEW_SETUP_MENU)||defined(DP3240_SETUP_MENU)
 /*#ifdef BBK_DV961_DVD*/
#define SPDIFBITSTREAM  2
#define SPDIFPCM        3
#define SPDIFSIMULATE   4
 /*#elif defined(BBK_DSS_555_DVD)
  #define SPDIFBITSTREAM  2
  #define SPDIFPCM        3
 #endif*/
#else
#define SPDIFSIMULATE   2
#define SPDIFBITSTREAM  3
#define SPDIFPCM        4
#endif


#ifdef NO_MIC
#define MICONOFFITEM    4       //gerry,3-10-25 10:30
#define ECHOITEM        2
#define MICITEM         3
#if defined(HJ_APEX_NO_KEY)&&!defined(SUPPORT_PROLOGIC_II)//20040617
#define KEYITEM         7
#else//#if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
#define KEYITEM         1
#endif//#if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)

#elif defined(NO_MIC_VOL)
#define MICONOFFITEM    1       //gerry,3-10-23 15:43
#define ECHOITEM        2
#define MICITEM         7
#define KEYITEM         6

#elif defined(KARAOKE_MENU)
    #define MICONOFFITEM    2   //wangfeng 2003-11-11 15:06
    #define ECHOITEM        3
    #define MICITEM         4
    #define KEYITEM         5
#elif defined(NOT_SHOW_MIC_SETUP_DAFAULT_AUTO)
    #define MICONOFFITEM    7   //wangfeng 2003-11-11 15:06
    #define ECHOITEM        1
    #define MICITEM         2
    #define KEYITEM         3
#else
#define MICONOFFITEM    1       //gerry,3-10-23 15:43
#define ECHOITEM        2
#define MICITEM         3
#define KEYITEM         4
#endif

#define VOLCTRLSTART    1

    #ifdef NO_MIC
        #define VOLCTRLEND      1//4
    #elif defined(NO_MIC_VOL)
        #define VOLCTRLEND      2
    #else
        #define VOLCTRLEND      4
    #endif

#define MICAUTO         2

#ifdef DVDRELEASE
    #define MICOFF          2
#else
    #define MICOFF          3
#endif

#if defined(NO_DIGIT_VIDEO_MENU)&&!defined(EASTECH_NEW_SETUP_MENU)

#define VIDEOPAGE       4
//page index-3
#define MULTISPKPAGE    3      //valid when AC3 or DTS
#elif defined(QSI_SETUP_MENU)//liweihua 2004-6-15
#define KARAOKPAGE      3
#define VIDEOPAGE       5
#elif defined(SETUP_DONGLI459)
#define VIDEOPAGE       3
#define MULTISPKPAGE    3     //valid when AC3 or DTS
#elif defined(EASTECH_NEW_SETUP_MENU)
#define VIDEOPAGE       3
#define MULTISPKPAGE       3
#elif defined(DVB_MENU_SETUP_STYLE)||defined(DVB_MENU_TYPE1)            //sunzhh 20050430
#define VIDEOPAGE      5
#define MULTISPKPAGE    6 
#else//#endif//NO_DIGIT_VIDEO_MENU
//page index-3
#define VIDEOPAGE       3
//page index-4
#define MULTISPKPAGE    4 
#endif//NO_DIGIT_VIDEO_MENU

#if defined(EASTECH_NEW_SETUP_MENU)
#define AC3DOWNMIXITEM  2//0//4-8-30 10:30
#else
#define AC3DOWNMIXITEM  0
#endif

#ifndef AC3_BASS_MANAGEMENT
    #define SPKSTART        2
    #define SPKEND          6
#else
    #if defined(TEMP_TWO_CHANNEL)&&!defined(ONLY_DOWNMIX)//nono 4-3-11 18:34
    #define SPKSTART        3
    #define SPKEND          3
    #elif defined(ONLY_DOWNMIX)
    #define SPKSTART        1
    #define SPKEND          1
    #elif defined(ONLY_DOWNMIX_SUBW)
    #define SPKSTART        2
    #define SPKEND          2
    #elif defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH)
    #define SPKSTART       	1//zxb 2005-5-8 13:12 GRAY the 4 item  
    #define SPKEND          4//when downmix is not selected off
    #else
    #define SPKSTART        3
    #define SPKEND          4
#endif
#endif

#define DOWNMIXLTRT     2   //Jeff 20020822
#define DOWNMIXSTEREO   3

#if defined(JIEKE_DVD)|defined(MINTON_DVD)//wangfeng 2003-12-12 14:40
#define AC3DOWNMIXOFF   4
#define DOWNMIXVSRND    5
#else
#define DOWNMIXVSRND    4
#define AC3DOWNMIXOFF   5
#endif

//page index-4
#ifdef SETUP_DONGLI459
#define AC3DIGITALPAGE  4      //valid when AC3
#else//#ifdef SETUP_DONGLI459
#if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)      //sunzhh 20050430
#define AC3DIGITALPAGE  7
#else
#define AC3DIGITALPAGE  5      //valid when AC3
#endif
#endif//#ifdef SETUP_DONGLI459

//page index-5
//CUSTM page index(for system admin use)
#ifdef Ti3001_OSD_UI_2
    #define  CUSTMPAGEINDEX  8
#elif defined(QSI_SETUP_MENU)//liweihua 2004-6-15
    #define  CUSTMPAGEINDEX  4
#elif defined(EASTECH_NEW_SETUP_MENU)||defined(EASTECH_DP3240_SETUP_MENU)
    #define CUSTMPAGEINDEX  4
#elif defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)     //20050430
    #define CUSTMPAGEINDEX  8    
#else
    #define CUSTMPAGEINDEX  6
#endif

#ifdef RCD_GPIO_CONTROL                 // alan 2002/7/26 02:07¤U¤È
    #define CUSTMPASSWDITEM 3
    #define CUSTMRATEITEM   2           // Maoyong 2004.03.25
#else
    #define CUSTMPASSWDITEM 4
    #define CUSTMRATEITEM   3           // Maoyong 2004.03.25
#endif

#ifdef NEW_STYLE_SETUP
//page index-6
#define EXITPAGE        7      //zhaoyanhua add 3-7-14 11:23
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)           //axel2004/1/26 04:50
//page index_6           
#define ONEKEYPASSPAGE   7     //show ONE_KEY_PASS page

#define EXITPAGE         8

#endif//BBK_DVD

#if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)    //sunzhh 20050430
#define ITEM_DVBT_CONFIG      0
//#define ITEM_AUTO_SCAN        1
//#define ITEM_MANUAL_SCAN      2
#define ITEM_LANGUAGE         1
#define ITEM_TIME_ZONE        2

#define ITEM_TV_CHANNEL       0
#define ITEM_RADIO_CHANNEL    1
#define ITEM_ADD_CHANNEL      2
//#define ITEM_EDIT_CHANNEL     3
#define ITEM_DEL_CHANNEL      3
#endif

#define C_UNLOCK    1
#define C_LOCK      0

//defition for special items
#ifdef NO_TV_FORMAT
#define SETUP_TV_FORMAT             setup_sel[SYSPAGE][7]
#define SETUP_SSAVER                setup_sel[SYSPAGE][0]
#elif defined(SELECT_MEDIA_IN_SETUPMENU)   //Maoyong 2004-8-10 14:49
#define SETUP_TV_FORMAT             setup_sel[SYSPAGE][1]
#define SETUP_MEDIA_TYPE            setup_sel[SYSPAGE][0]
#define SETUP_SSAVER                setup_sel[SYSPAGE][0] //in fact no use.
#else//NO_TV_FORMAT
#define SETUP_TV_FORMAT             setup_sel[SYSPAGE][0]
//#ifdef NO_SCREEN_SAVER

#ifdef SETUP_ITEM_NO_SCREEN_SAVER_AND_DEFAULT_ON
#define SETUP_SSAVER                setup_sel[SYSPAGE][7]
#else
#define SETUP_SSAVER                setup_sel[SYSPAGE][SSAVERITEM]//nono 4-10-25 23:41
#endif

//#else
//#define SETUP_SSAVER                setup_sel[SYSPAGE][7]
//#endif
#endif//NO_TV_FORMAT

#ifdef  DYNAMIC_SPECTRUM    //fengjl 3-10-30 13:23
#define SETUP_BAND                 setup_sel[SYSPAGE][5]   
#endif

#if defined(DELETE_VIDEO_ITEM)
#define SETUP_VIDEO_FORMAT          setup_sel[SYSPAGE][7]
#elif defined(NO_TV_FORMAT)&&!defined(DELETE_VIDEO_ITEM)
#define SETUP_VIDEO_FORMAT          setup_sel[SYSPAGE][1]
#elif defined(DP3240_SETUP_MENU)
#define SETUP_VIDEO_FORMAT          setup_sel[VIDEOPAGE][4]
#else
#define SETUP_VIDEO_FORMAT          setup_sel[SYSPAGE][2]
#endif

#if defined(HIMAGE_CANADA_CUS)&& !defined(INCLUDE_YUV)
    #define SETUP_PASSWORD              setup_sel[SYSPAGE][3]
    #define SETUP_GRADE                 setup_sel[SYSPAGE][4]
#elif defined(DELETE_VIDEO_ITEM)&&defined(NO_TV_FORMAT)
    #define SETUP_PASSWORD              setup_sel[SYSPAGE][2]
    #define SETUP_GRADE                 setup_sel[SYSPAGE][3]

#elif defined(GBM_FULL_FUNCTION)
    #define SETUP_PASSWORD              setup_sel[SysNextPage][2]
    #define SETUP_GRADE                 setup_sel[SysNextPage][3]

#elif defined(NO_TV_FORMAT)||defined(DELETE_VIDEO_ITEM)
    #define SETUP_PASSWORD              setup_sel[SYSPAGE][3]
    #define SETUP_GRADE                 setup_sel[SYSPAGE][4]
#elif defined(NO_SCREEN_SAVER)||defined(SETUP_ITEM_NO_SCREEN_SAVER_AND_DEFAULT_ON)
    #define SETUP_PASSWORD              setup_sel[SYSPAGE][3]
    #define SETUP_GRADE                 setup_sel[SYSPAGE][4]
#else
    #define SETUP_PASSWORD              setup_sel[SYSPAGE][4]
    #define SETUP_GRADE                 setup_sel[SYSPAGE][5]
#endif

#ifdef USER_MPEG_LOGO
    #define SETUP_MPEG_LOGO             setup_sel[SysNextPage][MPEG_LOGO_ITEM]
#endif//#ifdef USER_MPEG_LOGO

#ifdef USE_IR_TO_CHANGE_TVTYPE//nono 2003-11-12 21:20 ONLY use in himage 1125.if use in other model,"2" must be changed.
#define SETUP_TV_TYPE           setup_sel[SYSPAGE][2]
#define ITEM_TV_TYPE            setup_item[SYSPAGE][2]
#endif//USE_IR_TO_CHANGE_TVTYPE

#define SETUP_OSD_LANG              setup_sel[LANGPAGE][0]

#define SETUP_SPDIF                 setup_sel[AUDPAGE][0]

#ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-5 11:38
    #define SETUP_MIC_ONF               setup_sel[KARAOKPAGE][0]
    #define SETUP_ECHO                  setup_sel[KARAOKPAGE][1]
    #define SETUP_MIC_VOL               setup_sel[KARAOKPAGE][2]
    #define SETUP_KEY                   setup_sel[KARAOKPAGE][3]

#else
#ifdef NO_MIC_VOL
#define SETUP_MIC_ONF               setup_sel[AUDPAGE][1]
    #define SETUP_ECHO                  setup_sel[AUDPAGE][2]
    #define SETUP_MIC_VOL               setup_sel[AUDPAGE][6]//setup_sel[AUDPAGE][3]
    #if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
    #define SETUP_KEY                   setup_sel[AUDPAGE][7]//setup_sel[AUDPAGE][4]
    #else//defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
    #define SETUP_KEY                   setup_sel[AUDPAGE][3]//setup_sel[AUDPAGE][4]
    #endif//defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
#elif defined(NO_MIC)
   /*   to avoid no mic voilume   fengjl add
    #ifdef BBK_NEW_SETUP  //fengjl add 3-12-1 23:31,  "7" stand for invalid digit here
    #define SETUP_MIC_ONF               setup_sel[AUDPAGE][7]//setup_sel[AUDPAGE][1]
    #define SETUP_ECHO                  setup_sel[AUDPAGE][7]//setup_sel[AUDPAGE][2]
    #define SETUP_MIC_VOL               setup_sel[AUDPAGE][7]//setup_sel[AUDPAGE][3]
    #else
   */
#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
    #define SETUP_SPDIF_DTS                 setup_sel[AUDPAGE][1]//[4]//setup_sel[AUDPAGE][1]
    #define SETUP_SPDIF_PCM                 setup_sel[AUDPAGE][2]//[5]//setup_sel[AUDPAGE][2]
#endif//DIVIDE_AC3_DTS_SPDIF_OUTPUTS

    #define SETUP_MIC_ONF               setup_sel[AUDPAGE][6]//[4]//setup_sel[AUDPAGE][1]
    #define SETUP_ECHO                  setup_sel[AUDPAGE][6]//[5]//setup_sel[AUDPAGE][2]
    #define SETUP_MIC_VOL               setup_sel[AUDPAGE][6]//[3]//setup_sel[AUDPAGE][3]
//  #endif
    
    #if defined(HJ_APEX_NO_KEY)&&!defined(SUPPORT_PROLOGIC_II)//20040617
    #define SETUP_KEY                   setup_sel[AUDPAGE][7]//setup_sel[AUDPAGE][4]
    #else//#if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
        #ifdef  NO_KEY_ITEM//zhaoyanhua add 2003-12-10 11:07
            #define SETUP_KEY                   setup_sel[AUDPAGE][7]//setup_sel[AUDPAGE][4]
        #else 
    #define SETUP_KEY                   setup_sel[AUDPAGE][1]//setup_sel[AUDPAGE][4]
        #endif
    #endif//#if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
#elif defined(KARAOKE_MENU)//NO_MIC_VOL

        #define SETUP_MIC_ONF               setup_sel[AUDPAGE][2]
        #define SETUP_ECHO                  setup_sel[AUDPAGE][3]

        #ifndef MIC_2CHANNEL    //wangfeng 2003-09-12 22:19
        #define SETUP_MIC_VOL               setup_sel[AUDPAGE][4]
        #endif

        #if defined(MIC_2CHANNEL)&& !defined(SUPPORT_PROLOGIC_II)
        #define SETUP_KEY                   setup_sel[AUDPAGE][4]
#else
        #define SETUP_KEY                   setup_sel[AUDPAGE][5]
        #endif
#elif defined(NOT_SHOW_MIC_SETUP_DAFAULT_AUTO)

#define SETUP_MIC_ONF               setup_sel[AUDPAGE][MICONOFFITEM]//7
#define SETUP_ECHO                  setup_sel[AUDPAGE][ECHOITEM]//1

    #ifndef MIC_2CHANNEL    //wangfeng 2003-09-12 22:19
    #define SETUP_MIC_VOL               setup_sel[AUDPAGE][MICITEM]//2
    #endif
    
    #if defined(MIC_2CHANNEL)&& !defined(SUPPORT_PROLOGIC_II)
    #define SETUP_KEY                   setup_sel[AUDPAGE][3]
    #else
    #define SETUP_KEY                   setup_sel[AUDPAGE][KEYITEM]//3
    #endif
#else//NO_MIC_VOL

#define SETUP_MIC_ONF               setup_sel[AUDPAGE][1]
#define SETUP_ECHO                  setup_sel[AUDPAGE][2]

    #ifndef MIC_2CHANNEL    //wangfeng 2003-09-12 22:19
#define SETUP_MIC_VOL               setup_sel[AUDPAGE][3]
#endif

    
#if defined(MIC_2CHANNEL)&& !defined(SUPPORT_PROLOGIC_II)
    #define SETUP_KEY                   setup_sel[AUDPAGE][3]
#else
#define SETUP_KEY                   setup_sel[AUDPAGE][4]
#endif

#endif//#ifdef NO_MIC_VOL
#endif//#ifdef QSI_SETUP_MENU_DESIGN

/*
*  Prologic-2  and Freq. mask
*/
#define PROLOGIC_OFF                            4//terry,2004/1/9 10:57AM
#if defined(USE_FREQ_MASK)&&defined(SUPPORT_PROLOGIC_II)
    #ifdef NO_MIC_VOL
        #define SETUP_FREQ_MASK             setup_sel[AUDPAGE][4]//setup_sel[AUDPAGE][5]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][5]//setup_sel[AUDPAGE][6]
        #define PROLOGIC_II                 5   //clead 2003-10-21 
    #elif defined(NO_MIC)
        #ifdef BBK_DVD//NEW_SETUP axel modify 4-1-10 15:09       //fengjl  add 3-12-3 17:20
            #define LPCM_ITEM                                       1
            #define SETUP_FREQ_MASK             setup_sel[AUDPAGE][LPCM_ITEM]//setup_sel[AUDPAGE][5]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][3]//setup_sel[AUDPAGE][6]
          #ifdef SUPPORT_PROLOGIC_II
        #define PROLOGIC_II                 2   //clead 2003-10-21      
          #endif  //axel  4-1-10 15:09  
        #else       
         #define LPCM_ITEM                                       1
        #define SETUP_FREQ_MASK             setup_sel[AUDPAGE][2]//setup_sel[AUDPAGE][5]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][3]//setup_sel[AUDPAGE][6]
        #define PROLOGIC_II                 3   //clead 2003-10-21 
        #endif
    #elif defined(NOT_SHOW_MIC_SETUP_DAFAULT_AUTO)
        #define LPCM_ITEM                                       4
        #define SETUP_FREQ_MASK             setup_sel[AUDPAGE][LPCM_ITEM]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][6]
        #define PROLOGIC_II                 5   //clead 2003-10-21 
    #else
        #define LPCM_ITEM                                       5
        #define SETUP_FREQ_MASK             setup_sel[AUDPAGE][LPCM_ITEM]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][6]
        #define PROLOGIC_II                 6   //clead 2003-10-21 
    #endif          
#define SETUP_PROLOGIC_II           setup_sel[AUDPAGE][PROLOGIC_II] //clead 2003-10-21 

#elif defined(USE_FREQ_MASK)&& !defined(SUPPORT_PROLOGIC_II)
            #ifdef QSI_SETUP_MENU//liweihua 2004-6-16
            #define LPCM_ITEM                                       3
            #elif defined(EASTECH_NEW_SETUP_MENU)
            #define LPCM_ITEM                                       1
            #else
            #define LPCM_ITEM                                       5//terry,2004/2/4 02:43PM
            #endif
            #define SETUP_FREQ_MASK             setup_sel[AUDPAGE][LPCM_ITEM]//setup_sel[AUDPAGE][5]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][3]//setup_sel[AUDPAGE][6]

#else//#if defined(USE_FREQ_MASK)&&defined(SUPPORT_PROLOGIC_II)
    #ifdef NO_MIC_VOL
        //#define SETUP_FREQ_MASK               setup_sel[AUDPAGE][4]//setup_sel[AUDPAGE][5]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][4]//setup_sel[AUDPAGE][5]
        #if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
        #define PROLOGIC_II                 3   //clead 2003-10-21 
        #else       
        #define PROLOGIC_II                 4   //clead 2003-10-21 
        #endif
    #elif defined(NO_MIC)
        //#define SETUP_FREQ_MASK               setup_sel[AUDPAGE][7]//setup_sel[AUDPAGE][5]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][2]//setup_sel[AUDPAGE][5]
        #if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
            #define PROLOGIC_II                 1   //clead 2003-10-21 
        #else//#if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
        #define PROLOGIC_II                 2   //clead 2003-10-21 
        #endif//#if defined(HJ_APEX_NO_KEY)&&defined(SUPPORT_PROLOGIC_II)
        
    #else//#ifdef NO_MIC_VOL
        
        #if defined(MIC_2CHANNEL)&&defined(SUPPORT_PROLOGIC_II)
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][3]
        #define PROLOGIC_II                 3
        
        #define SETUP_MIC_VOL               setup_sel[AUDPAGE][5]
        #define SETUP_MIC_VOL_2             setup_sel[AUDPAGE][6]

        
        #elif defined(MIC_2CHANNEL)&&!defined(SUPPORT_PROLOGIC_II)
        
        #define SETUP_MIC_VOL               setup_sel[AUDPAGE][4]
        #define SETUP_MIC_VOL_2             setup_sel[AUDPAGE][5]
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][6]
        #define PROLOGIC_II                 6   //clead 2003-10-21 
        #elif !defined(MIC_2CHANNEL)&&defined(SUPPORT_PROLOGIC_II)
        
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][5]
        #ifdef HJ_APEX_NO_KEY
        #define PROLOGIC_II                 4   //clead 2003-10-21 
        #elif defined(KARAOKE_MENU)
        #define PROLOGIC_II                 1
        #else    
        #define PROLOGIC_II                 5   //clead 2003-10-21 
        #endif
        
        #else//#if defined(MIC_2CHANNEL)&&defined(SUPPORT_PROLOGIC_II)
        
        //#define SETUP_PROLOGIC_II         setup_sel[AUDPAGE][6]
        #define PROLOGIC_II                 6   //clead 2003-10-21 
        
        #endif//#if defined(MIC_2CHANNEL)&&defined(SUPPORT_PROLOGIC_II)
        
        #define SETUP_FREQ_MASK             setup_sel[AUDPAGE][7]
        
    #endif//#ifdef NO_MIC_VOL

#define SETUP_PROLOGIC_II           setup_sel[AUDPAGE][PROLOGIC_II] //clead 2003-10-21 

#endif//#if defined(USE_FREQ_MASK)&&defined(SUPPORT_PROLOGIC_II)

//#define SETUP_SHARPNESS               setup_sel[VIDEOPAGE][0]
#define SETUP_BRIGHTNESS            setup_sel[VIDEOPAGE][0]
#define SETUP_CONTRAST              setup_sel[VIDEOPAGE][1]
#define SETUP_HUE                   setup_sel[VIDEOPAGE][2]
#define SETUP_SATURATION            setup_sel[VIDEOPAGE][3]
#ifdef ADD_DVI311_SETUP//Modifed by ChenZhao on 2004-10-19 13:51  
#define SETUP_DVI_MODE_INDEX        4
#define SETUP_DVI_MODE              setup_sel[VIDEOPAGE][SETUP_DVI_MODE_INDEX]
#endif //ADD_DVI311_SETUP
#ifdef DIP_CFG_ENABLE
    #define SETUP_DE_INTERLACE          setup_sel[VIDEOPAGE][4]
#endif//#ifdef DIP_CFG_ENABLE

#ifdef EASTECH_NEW_SETUP_MENU//nono 4-8-31 16:04
#define SETUP_SPK_DOWNMIX           setup_sel[2][AC3DOWNMIXITEM]
#else
#define SETUP_SPK_DOWNMIX           setup_sel[MULTISPKPAGE][AC3DOWNMIXITEM]
#endif

#define SETUP_SPK_SUBWOOFER         setup_sel[MULTISPKPAGE][1]

#ifndef AC3_BASS_MANAGEMENT
    #define SETUP_SPK_FRONT             setup_sel[MULTISPKPAGE][2]
    #define SETUP_SPK_CENTER            setup_sel[MULTISPKPAGE][3]
    #define SETUP_SPK_SURROUND          setup_sel[MULTISPKPAGE][4]
    #define SETUP_SPK_CENTER_DELAY      setup_sel[MULTISPKPAGE][5]
    #define SETUP_SPK_SURROUND_DELAY    setup_sel[MULTISPKPAGE][6]
#elif defined(NO_BASS_MODE)
    #define SETUP_BASS_MODE             setup_sel[MULTISPKPAGE][7]
    #define SETUP_SPK_CENTER_DELAY      setup_sel[MULTISPKPAGE][2]
    #define SETUP_SPK_SURROUND_DELAY    setup_sel[MULTISPKPAGE][3]
#elif defined(SET_FCR_SPEAKER)
    #define SETUP_FRONT_SPEAKER     setup_sel[MULTISPKPAGE][2]    //xulf 2004-01-05
    #define SETUP_CENTER_SPEAKER        setup_sel[MULTISPKPAGE][3]
    #define SETUP_REAR_SPEAKER      setup_sel[MULTISPKPAGE][4]
    #define SETUP_SPK_CENTER_DELAY      setup_sel[MULTISPKPAGE][5]
    #define SETUP_SPK_SURROUND_DELAY    setup_sel[MULTISPKPAGE][6]
#elif defined (TEST_BASS_MANAGEMENT)     //Andrew Wen 20040803
    #define SETUP_SPK_FRONT             setup_sel[MULTISPKPAGE][2]
    #define SETUP_SPK_CENTER            setup_sel[MULTISPKPAGE][3]
    #define SETUP_SPK_SURROUND          setup_sel[MULTISPKPAGE][4]
    #define SETUP_SPK_CENTER_DELAY      setup_sel[MULTISPKPAGE][5]
    #define SETUP_SPK_SURROUND_DELAY    setup_sel[MULTISPKPAGE][6]		
#else
    #define SETUP_BASS_MODE             setup_sel[MULTISPKPAGE][2]
    #define SETUP_SPK_CENTER_DELAY      setup_sel[MULTISPKPAGE][3]
    #define SETUP_SPK_SURROUND_DELAY    setup_sel[MULTISPKPAGE][4]
#endif

#define ITEM_SPK_DOWNMIX            setup_item[MULTISPKPAGE][0]


#ifdef NO_AC3_DYNAMIC_RANGE
    #define SETUP_AC3DIGITAL_DYNA       setup_sel[AC3DIGITALPAGE][4] //Yuxing doesn't support this function, so we assign a invalid item to it.
    #define SETUP_AC3DIGITAL_LnR        setup_sel[AC3DIGITALPAGE][1]
    #define ITEM_AC3DIGITAL_LnR         setup_item[AC3DIGITALPAGE][1]
#elif defined(HJ_APEX_NO_OPMODE)
    #define SETUP_AC3DIGITAL_DYNA       setup_sel[AC3DIGITALPAGE][0]
    #define SETUP_AC3DIGITAL_LnR        setup_sel[AC3DIGITALPAGE][1]
    #define ITEM_AC3DIGITAL_LnR         setup_item[AC3DIGITALPAGE][1]
#elif defined(SYBER_DVD)//liweihua add for syber 20031211
    #define SETUP_AC3DIGITAL_DYNA       setup_sel[AC3DIGITALPAGE][0]
    #define SETUP_AC3DIGITAL_LnR        setup_sel[AC3DIGITALPAGE][1]
    #define ITEM_AC3DIGITAL_LnR         setup_item[AC3DIGITALPAGE][1]
#elif defined(DIG_AND_AUD)//liweihua add for syber 20031211
    #define SETUP_AC3DIGITAL_DYNA       setup_sel[AUDPAGE][3]
    #define SETUP_AC3DIGITAL_LnR      setup_sel[AUDPAGE][4]
    #define ITEM_AC3DIGITAL_LnR         setup_item[AUDPAGE][4]
#else//#ifdef SYBER_DVD//liweihua add for syber 20031211
    #define SETUP_AC3DIGITAL_DYNA       setup_sel[AC3DIGITALPAGE][1]
    #define SETUP_AC3DIGITAL_LnR        setup_sel[AC3DIGITALPAGE][2]
    #define ITEM_AC3DIGITAL_LnR         setup_item[AC3DIGITALPAGE][2]

#endif

#ifdef HJ_APEX_NO_OPMODE
#define SETUP_AC3DIGITAL_OUTMODE    setup_sel[AC3DIGITALPAGE][4]
#define ITEM_AC3DIGITAL_OUTMODE     setup_item[AC3DIGITALPAGE][4]
#else//HJ_APEX_NO_OPMODE
#ifdef SYBER_DVD//liweihua add for syber 20031211
#define SETUP_AC3DIGITAL_OUTMODE    setup_sel[AC3DIGITALPAGE][2]
#define ITEM_AC3DIGITAL_OUTMODE     setup_item[AC3DIGITALPAGE][2]
#else//#ifdef SYBER_DVD//liweihua add for syber 20031211
#define SETUP_AC3DIGITAL_OUTMODE    setup_sel[AC3DIGITALPAGE][0]
#define ITEM_AC3DIGITAL_OUTMODE     setup_item[AC3DIGITALPAGE][0]
#endif//#ifdef SYBER_DVD//liweihua add for syber 20031211
#endif//HJ_APEX_NO_OPMODE

#ifdef  Ti3001_OSD_UI_2
    #define SETUP_AMP_VOLUME             setup_sel[6][0]
    #define SETUP_AMP_FSPK               setup_sel[6][1]
    #define SETUP_AMP_FSPK_BALANCE       setup_sel[6][2]
    #define SETUP_AMP_SSPK               setup_sel[6][3]
    #define SETUP_AMP_SSPK_BALANCE       setup_sel[6][4]
    #define SETUP_AMP_CSPK               setup_sel[6][5]
    #define SETUP_AMP_SUBWOOFER          setup_sel[6][6]

    #define SETUP_AMP_BASS               setup_sel[6][0]
    #define SETUP_AMP_TREMBLE            setup_sel[6][1]
    #define SETUP_AMP_DYNAMIC            setup_sel[6][2]
#endif

#define AC3OUTMODEITEM              0
#define AC3DYNAMICITEM1             1
#define AC3DYNAMICITEM2             2 //(2+2)

#define SETUP_CUSTM_REGION          setup_sel[CUSTMPAGEINDEX][2]

#ifdef CORTROL_VCD_ONF
#define SETUP_CUSTM_VCD_ONF         setup_sel[CUSTMPAGEINDEX][5]  //wangap add 2004/5/27
#endif

#ifdef RCD_GPIO_CONTROL                                                 // alan 2002/7/26 02:07¤U¤È
    #define SETUP_CUSTM_GRADE           setup_sel[CUSTMPAGEINDEX][2]
#else
    #define SETUP_CUSTM_GRADE           setup_sel[CUSTMPAGEINDEX][3]
#endif

#ifdef SUPER_DEFAULT_OSD_LANG
#define CUSTMOSDITEM                5
#define SETUP_CUSTM_OSDLANG         setup_sel[CUSTMPAGEINDEX][5]
#define ITEM_CUSTM_OSDLANG          setup_item[CUSTMPAGEINDEX][5]
#endif 

#ifdef SUPPORT_HD_RESOLUTION
#define SETUP_HD_OUTPUT              setup_sel[0][7]
#endif

