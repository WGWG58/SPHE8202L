//nono split from setup_item.c 5-5-9 15:07

const UINT8 setup_item[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM][MAX_ITEM_SEL]=
{
	
#if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)
	//Install
	{
        //item0        
        {SET_SH,STR_OS_DVBT_CONFIG,0,0,0,0, 0, 0,0,0},   
        //item1          
        //{SET_SH,STR_OS_AUTO_SCAN,0,0,0,0,0, 0, 0,0},   
        //item2
        //{SET_SH,STR_OS_MANUAL_SCAN,0,0,0,0,0, 0, 0,0}, 
        //item3
    	{SET_FUNC,STR_OS_OSD, OSD_LAGN_SETUP_STRING},  	
        //item4
        {SET_FUNC,STR_OS_TIME_ZONE,STR_OS_TIME_ZONE1,STR_OS_TIME_ZONE2,STR_OS_TIME_ZONE3,STR_OS_TIME_ZONE4,STR_OS_TIME_ZONE5, 0, 0,0},
        //item5
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        
        //item6
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
    },
    
    //Channel
	{
        //item0        
        {SET_SH,STR_OS_TV_CHANNEL,0,0,0,0, 0, 0,0,0},   
        //item1          
        {SET_SH,STR_OS_RADIO_CHANNEL,0,0,0,0,0, 0, 0,0},   
        //item2
        //{SET_SH,STR_OS_EDIT_LIST,0,0,0,0,0, 0, 0,0}, 
        //item3
    	{SET_SH,STR_OS_ADD_CHANNEL,0,0,0,0,0, 0, 0,0},
        //item4
        //{SET_SH,STR_OS_EDIT_CHANNEL,0,0,0,0,0, 0, 0,0},
        //item5
        {SET_SH,STR_OS_DEL_CHANNEL,0,0,0,0,0, 0, 0,0},   
        //item6
        {SET_SH,STR_OS_LOCK_CHANNEL,0,0,0,0,0, 0, 0,0},  //haoy 2005-04-14  for lock channel menu
        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        
        //{SET_NE,0,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
    },
    
#endif
	
    //page 0-SYSTEM SETUP
    {
#ifdef SELECT_MEDIA_IN_SETUPMENU //Maoyong 2004.08.09
        //item0
        #ifndef SUPPORT_USB
        {SET_FUNC,STR_OS_MEDIA_TYPE,STR_OS_MEDIA_DISC,STR_OS_MEDIA_CARD,0,0, 0, 0, 0, 0},
        #elif !defined(SPHE8202_CARD_STORAGE)
        {SET_FUNC,STR_OS_MEDIA_TYPE,STR_OS_MEDIA_DISC,STR_OS_MEDIA_USB,0,0, 0, 0, 0, 0},
        #else
        {SET_FUNC,STR_OS_MEDIA_TYPE,STR_OS_MEDIA_DISC,STR_OS_MEDIA_USB,STR_OS_MEDIA_CARD,0, 0, 0, 0, 0},
        #endif
        //item1
        {SET_FUNC, STR_OS_TV_SYS, TV_SYS_SETUP_STRING},
#else   //#endif SELETC_MEDIA_IN_SETUPMENU
        #if !defined(NO_TV_FORMAT)
        //item0
        {SET_FUNC, STR_OS_TV_SYS, TV_SYS_SETUP_STRING},
        #endif//NO_TV_FORMAT

        //item1
#if defined(SUPPORT_CC_ONOFF)&&defined(USE_SSAVER_ITEM_AS_CC_ONOFF)//nono 2004-4-11 19:04
        {SET_FUNC,STR_OS_CLOSED_CAPTION,STR_OS_OFF,STR_OS_ON,0,0,0, 0, 0,0},
#else//USE_SSAVER_ITEM_AS_CC_ONOFF
        #ifdef QSI_SETUP_MENU//liweihua 2004-6-15
        {SET_FUNC,STR_OS_SSAVER_SETUP,STR_OS_1_MIN,STR_OS_5_MIN,STR_OS_10_MIN,STR_OS_30_MIN,STR_OS_OFF,0,0,0},
        #elif defined(NO_SCREEN_SAVER)
        //{SET_FUNC,STR_OS_SSAVER_SETUP,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
        #else
        {SET_FUNC,STR_OS_SSAVER_SETUP,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
        #endif
#endif//USE_SSAVER_ITEM_AS_CC_ONOFF
#endif //#ifdef SELETC_MEDIA_IN_SETUPMENU

#if !defined(DELETE_VIDEO_ITEM)
            //item2
#ifdef ADD_P_SCAN_ONOFF
            {SET_FUNC,STR_OS_P_SCAN_YUV,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},      
#else
            {SET_FUNC,STR_OS_VIDEO,VIDEO_SETUP_STRING},
#endif
        
#endif
        
        #ifndef ARGUS_PORTABLE_DVD //Jack added for argus portable 04/07/02
            //item3
            {SET_FUNC,STR_OS_TV_RATIO,STR_OS_4_3PS,STR_OS_4_3LB,STR_OS_16_9,0, 0, 0,0,0},

        //item4
#ifndef GBM_FULL_FUNCTION
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 11:09
        {SET_FUNC,STR_OS_PASSWORD,STR_OS_PASSWD_EDIT,0,0,0,0, 0, 0,0},
#else//NOT SETUP_PASSWORD_GUI
        {SET_NM,STR_OS_PASSWORD,STR_OS_LOCK,STR_OS_UNLOCK,0,0,0, 0, 0,0},
#endif//SETUP_PASSWORD_GUI
#else//GBM_FULL_FUNCTION
        {SET_FUNC,STR_OS_DEFAULT_SETUP,STR_OS_RESTORE_SETUP,0,0,0,0, 0, 0,0},
#endif//GBM_FULL_FUNCTION
        //item5
#ifndef GBM_FULL_FUNCTION
        #ifdef RATING_8
            {SET_FUNC,STR_OS_RATING,STR_OS_RATING_1,STR_OS_RATING_2,STR_OS_RATING_3,STR_OS_RATING_4,STR_OS_RATING_5,STR_OS_RATING_6,STR_OS_RATING_7,STR_OS_RATING_8},
        #else
            {SET_FUNC,STR_OS_RATING,STR_OS_NO_ADULT,STR_OS_KID_ONLY,STR_OS_VIEW_ALL,0,0, 0,0,0},
        #endif
#endif//GBM_FULL_FUNCTION
        //item6
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)       //freyman 2004-3-25 22:42
        {SET_SH,STR_OS_NEXT_PAGE,0,0,0,0,0, 0, 0,0},
#ifdef GBM_FULL_FUNCTION
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
#endif//GBM_FULL_FUNCTION
#else         
        #ifdef BBK_NEW_SETUP    //fengjl   3-10-21 20:40
            {SET_FUNC,STR_OS_BAND,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
            {SET_FUNC,STR_OS_DEFAULT_SETUP,STR_OS_RESTORE_SETUP,0,0,0,0, 0, 0,0},      
        #else  
        {SET_FUNC,STR_OS_DEFAULT_SETUP,STR_OS_RESTORE_SETUP,0,0,0,0, 0, 0,0},
#endif 
#endif 
        #ifndef  BBK_NEW_SETUP               //fengjl  3-11-5 14:00
        #if defined(DELETE_VIDEO_ITEM)||defined(NO_TV_FORMAT)
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        #endif
        #endif
        
        #if defined(NO_TV_FORMAT)&&!defined(DELETE_VIDEO_ITEM)
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif
        #ifdef NO_SCREEN_SAVER
	{SET_SPACE,0,0,0,0,0,0, 0, 0,0},  //wsf  for eastech  item6
        #endif
        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
//      {SET_SH,0,0,0,0,0,0, 0, 0,0},
        #if defined(HIMAGE_CANADA_CUS)&& !defined(INCLUDE_YUV)
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif

        #else //argus portable need to show mcu version
        //item3
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 11:09
        {SET_FUNC,STR_OS_PASSWORD,STR_OS_PASSWD_EDIT,0,0,0,0, 0, 0,0},
#else//NOT SETUP_PASSWORD_GUI
        {SET_NM,STR_OS_PASSWORD,STR_OS_LOCK,STR_OS_UNLOCK,0,0,0, 0, 0,0},
#endif//SETUP_PASSWORD_GUI

        //item4
        #ifdef RATING_8
            {SET_FUNC,STR_OS_RATING,STR_OS_RATING_1,STR_OS_RATING_2,STR_OS_RATING_3,STR_OS_RATING_4,STR_OS_RATING_5,STR_OS_RATING_6,STR_OS_RATING_7,STR_OS_RATING_8},
        #else
            {SET_FUNC,STR_OS_RATING,STR_OS_NO_ADULT,STR_OS_KID_ONLY,STR_OS_VIEW_ALL,0,0, 0,0,0},
        #endif

        //item5 
        {SET_FUNC,STR_OS_DEFAULT_SETUP,STR_OS_RESTORE_SETUP,0,0,0,0, 0, 0,0},
        
        //item 6
        {SET_SHOW,STR_OS_FW_VERSION,STR_OS_SPACE,0,0,0,0, 0, 0,0},
        
        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        
        //{SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif //end #ifndef ARGUS_PORTABLE_DVD


    },
    //page 1-LANGUAGE SETUP
    {
        //item0
        {SET_FUNC,STR_OS_OSD, OSD_LAGN_SETUP_STRING},

    #if !defined(HJ_APEX_NO_AUDIO_LANG)
        //item1
        //{SET_FUNC,STR_OS_AUDIO_LANG_SETUP,LCD_ZH,LCD_EN,LCD_JA,LCD_FR,LCD_ES,LCD_PT, LCD_DE, LCD_LA},
        {SET_FUNC,STR_OS_AUDIO_LANG_SETUP,OSD_AUDIO_LAGN_SETUP_STRING},
    #endif//#ifndef !defined(HJ_APEX_NO_AUDIO_LANG)
        //item2
        {SET_FUNC,STR_OS_SUBTITLE_LANG_SETUP,OSD_SUBT_LAGN_SETUP_STRING},
#ifdef SETUP_MENU_TWO_BUTTON_SELECT_TWO_SUBTITLE  //added by wangwei,2004-10-24 22:58
        {SET_FUNC,STR_OS_SUBTITLE_LANG_2ND_SETUP,OSD_SUBT_LAGN_2ND_SETUP_STRING},
#endif
        //item3
        {SET_FUNC,STR_OS_MENU_LANG_SETUP,OSD_MENU_LAGN_SETUP_STRING},
        //item4
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item5
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
    #ifdef HJ_APEX_NO_AUDIO_LANG   
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
    #endif//#ifndef defined(HJ_APEX_NO_AUDIO_LANG)
    },
    //page 2-AUDIO SETUP
    //Please don't change the item sequence of this page
   #ifdef SETUP_DONGLI459
      {
          {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0},
            {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
             {SET_NE,0,0,0,0,0,0, 0, 0,0},
        },
   #elif defined(QSI_SETUP_MENU)//liweihua 2004-6-15
     {
        //item0
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0},
        //item1
        {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_OFF,0, 0, 0,0},
        //item2
        {SET_SCALE,STR_OS_DYNAMICRANGE,0,0,0,0,0, 0, 0,0},
        //item3
        {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0},
        //item4
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item5
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
     },
#elif defined(EASTECH_NEW_SETUP_MENU)//#ifdef SETUP_DONGLI459
    //Please don't change the item sequence of this page
    {
        //item0        
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0, 0, 0,0,0},     //STR_OS_SIMULATE   
        //item1          
        {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0},   
        //item2
        {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_OFF,0, 0, 0,0},  // add by TOM 
        //item3
    {SET_FUNC,STR_OS_DUAL_MONO_SETUP,STR_OS_STEREO,STR_OS_CHL,STR_OS_CHR,STR_OS_MIX_MONO_SETUP,0, 0, 0,0},
        //item4
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item5
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},   
        //item6
         {SET_NE,0,0,0,0,0,0, 0, 0,0},
         //item7
          {SET_NE,0,0,0,0,0,0, 0, 0,0},
//            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        
    },
   
#elif defined(ORITRON_SETUP)	//xyy add for Oritron 2004-11-11
	{
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0},   
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
	},   
 #else//#ifdef SETUP_DONGLI459
   //#if !(defined(SETUP_DONGLI459) || defined(QSI_SETUP_MENU))//liweihua mod 2004-06-14
    {
        //item0
        #if defined(NO_SPDIF) //nono 20031027
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,0,0,0,0, 0, 0,0},
        #elif defined(DELETE_SPDIF_OFF_ITEM)   //zhaoyanhua add 2003-12-9 20:26
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0},   
        #elif defined(SOUND_EFFECT_MENU)        //sunzhh add 2004-4-22 20:01
        {SET_FUNC,STR_OS_EQ,STR_OS_STANDARD,STR_OS_CLASSIC,STR_OS_ROCK,STR_OS_JAZZ,STR_OS_POP, STR_OS_ELECTRON,STR_OS_LIGHT_MUSIC,0,0},
        #elif defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)//2004-6-16 18:46
        {SET_FUNC,STR_OS_AC3_DIGITAL,STR_OS_SIMULATE,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0},
        #else
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0},
        #endif//NO_SPDIF
        
        //item1
#ifdef  MIC_2CHANNEL    //wangfeng 2003-09-12 22:19
        #include "setup_tab_mic2.h"
#else   //MIC_2CHANNEL
        #ifdef KARAOKE_MENU//wangfeng 2003-11-11 14:36
            #ifdef SUPPORT_PROLOGIC_II
            {SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0},
            #endif
        #endif
        
        //terry,2004/3/22 03:30PM,clear debug mode
        #if !defined(NO_MIC)&&!defined(NOT_SHOW_MIC_SETUP_DAFAULT_AUTO)
           #if defined(HIMAGE_CANADA_CUS)||defined(MIC_SETUP_NO_AUTO)||defined(JIEKE_DVD)   //add JIEKE_DVD by wangfeng,2003-10-12 09:53
           {SET_FUNC,STR_OS_MIC_ONOFF,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
           #else
           {SET_FUNC,STR_OS_MIC_ONOFF,STR_OS_AUTO,STR_OS_OFF,0,0,0, 0, 0,0},
           #endif
        #endif
        
#if defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)//2004-6-16 18:46
        {SET_FUNC,STR_OS_DTS_DIGITAL,STR_OS_SIMULATE,STR_OS_BITSTREAM,0,0,0, 0, 0,0},
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,STR_OS_STEREO_PCM,0,0,0, 0, 0,0},
#endif
#ifdef DIG_AND_AUD   //2004-6-22 07:22?宇P
        //{SET_FUNC,STR_OS_DOLBY_OP_SETUP,STR_OS_DOLBY_LINE_SETUP,STR_OS_DOLBY_RF_SETUP,0,0,0, 0, 0,0},
        {SET_SCALE,STR_OS_DYNAMICRANGE,0,0,0,0,0, 0, 0,0},
        {SET_FUNC,STR_OS_DUAL_MONO_SETUP,STR_OS_STEREO,STR_OS_CHL,STR_OS_CHR,STR_OS_MIX_MONO_SETUP,0, 0, 0,0},
#endif        
        
        #ifndef NO_MIC
            //item2
            {SET_SCALE,STR_OS_ECHO,0,0,0,0,0, 0, 0,0},
        #ifndef NO_MIC_VOL          //gerry for PANDA_DVD,3-8-22 13:42
            //item3
            {SET_SCALE,STR_OS_MIC_VOL,0,0,0,0,0, 0, 0,0},
        #endif      //#ifndef NO_MIC_VOL
        #endif

        #if  !defined(HJ_APEX_NO_KEY)//after define NO_MIC.//nono 20031020
        //item4
        #ifndef BBK_NEW_SETUP  //fengjl  add 3-12-3 17:16
        #ifdef SOUND_EFFECT_MENU  //sunzhh add 2004-4-22 16:38
        {SET_FUNC,STR_OS_SURR,STR_OS_CONCERT,STR_OS_CHURCH,STR_OS_PASSIVE,STR_OS_WIDE, STR_OS_LIVE,STR_OS_OFF,0,0,0},         
        #else                                                     
#ifdef EASTWIN
#else
        {SET_SCALE,STR_OS_KEY,0,0,0,0,0, 0, 0,0},
#endif
        #endif//#ifdef SOUND_EFFECT_MENU  //sunzhh add  2004-4-22 16:38
        #endif//#ifndef(BBK_NEW_SETUP)  //fengjl  add 3-12-3 17:16                           
        #endif//#ifdef HJ_APEX_NO_KEY
        
        
#ifdef USE_FREQ_MASK
   #ifdef SUPPORT_PROLOGIC_II       
        #ifdef BBK_NEW_SETUP  //axel,2003/12/15 01:18PM
          //item5 
      {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,0,0,0, 0, 0,0},
      //item6
      {SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0},
          {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
      #else //#ifdef BBK_NEW_SETUP BBK_NEW_SETUP
          //item5
      #ifdef DOWN_SAMPLE_NO_192K    //maoyong 2004.04.21
      {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,0,0,0, 0, 0,0},
        #else
      {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0},
      #endif //ifdef DOWN_SAMPLE_NO_192K
      //item6
      {SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0},
      #endif //#ifdef BBK_NEW_SETUP BBK_NEW_SETUP

        #ifdef NOT_SHOW_MIC_SETUP_DAFAULT_AUTO
        //item6
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        #endif//#ifdef NOT_SHOW_MIC_SETUP_DAFAULT_AUTO

        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
   #else
        #if defined(BBK_NEW_SETUP) || defined(DOWN_SAMPLE_NO_192K)  //axel,2003/12/15 01:18PM, maoyong 2004.04.21 changed
        //item5
        {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,0,0,0, 0, 0,0},
        #else
        //item5
        {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0},
        #endif
   #ifdef SOUND_EFFECT_MENU                  //sunzhh add 2004-4-22 20:05
        //item5
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item6
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
    #endif     //#ifdef SOUND_EFFECT_MENU                 
        //item6
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
   #endif
#else
    #ifdef SUPPORT_PROLOGIC_II
        #ifndef KARAOKE_MENU
        //item5
        {SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0},
        #endif
        //item6
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
    #else
        //item5
    
    #ifdef SUPPORT_TESTSPK    //jiangxl 2005-5-24 10:38
        {SET_FUNC,STR_OS_TESTSPK_MENU,STR_OS_OFF,STR_OS_ON,0,0,0, 0, 0,0},  
    #else
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
    #endif   
        //item6
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
    #endif
#endif
#endif  //MIC_2CHANNEL

        #ifdef NO_MIC
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
//            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #elif defined(NO_MIC_VOL)       //gerry for PANDA_DVD,3-8-22 13:43
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #elif defined(NO_MIC)&&defined(HJ_APEX_NO_KEY)      //nono 2003-10-18 14:38
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif
    },
    #endif//#ifndef SETUP_DONGLI459

    #ifdef QSI_SETUP_MENU//liweihua 2004-6-15
    //page 3-KARAOKE SETUP
    {
        //item0
        {SET_FUNC,STR_OS_MIC_ONOFF,STR_OS_AUTO,STR_OS_OFF,0,0,0, 0, 0,0},
         //item1
        {SET_SCALE,STR_OS_ECHO,0,0,0,0,0, 0, 0,0},
         //item2
        {SET_SCALE,STR_OS_MIC_VOL,0,0,0,0,0, 0, 0,0},
        //item3                                   
        {SET_SCALE,STR_OS_KEY,0,0,0,0,0, 0, 0,0},   
        //item4
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item5
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
    },
    #endif
#ifndef QSI_SETUP_MENU//liweihua 2004-6-15
#if defined(NO_DIGIT_VIDEO_MENU)&&!defined(EASTECH_NEW_SETUP_MENU)


    //page 4-SPEAKER SETUP
        {
            //item0
            #if defined(SHOW_5_1CH)
                #ifdef JIEKE_DVD //wangfeng,2003-10-12 10:39
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_6CH_SETUP,0, 0, 0,0,0},
                #else
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_6CH_SETUP,0, 0, 0,0},
                #endif
            #elif defined(TEMP_TWO_CHANNEL)||defined(GBM_TEMP_TWO_CHANNEL)
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,0,0, 0, 0,0},
            #elif defined(NO_VSURROUND_CHANNEL)
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_OFF,0, 0, 0,0},
            #elif defined(SETUP_DOWNMIX_NO_VSURROUND_OFF)
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,0,0, 0, 0,0},
            
            #else
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_OFF,0, 0, 0,0},
            #endif
            
            #ifndef ONLY_DOWNMIX
            //item1
            {SET_FUNC,STR_OS_SUBWOOFER,STR_OS_OFF,STR_OS_ON,0,0,0, 0, 0,0},     //set subwoofer on/off
            #endif//#ifdef ONLY_DOWNMIX

            #ifndef AC3_BASS_MANAGEMENT
                //item2
                {SET_SCALE,STR_OS_FSPK,0,0,0,0,0, 0, 0,0},          //set front speaker gain
                //item3
                {SET_SCALE,STR_OS_CSPK,0,0,0,0, 0, 0, 0,0},         //set c-speaker gain
                //item4
                {SET_SCALE,STR_OS_SSPK,0,0,0,0, 0, 0, 0,0},         //set s-speaker gain
                //item5
                {SET_SCALE,STR_OS_CSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set c-speaker delay
                //item6
                {SET_SCALE,STR_OS_SSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set s-speaker delay
                //item7
                {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
            #else
                //item2
                
                #ifdef KSD_DVD
                {SET_FUNC,STR_OS_BASS_MANAGEMENT,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
                #elif defined(JIEKE_DVD)
                {SET_FUNC,STR_OS_BASS_MANAGEMENT,STR_OS_BASS_MODE_3,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,0,0, 0, 0,0},
                #elif !defined(ONLY_DOWNMIX)&&!defined(ONLY_DOWNMIX_SUBW)
                {SET_FUNC,STR_OS_BASS_MANAGEMENT,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_BASS_MODE_3,0,0, 0, 0,0},
                #endif
               
                
              #if defined(TEMP_TWO_CHANNEL)
                //item3
                //{SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
                //item4
                {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                #if defined(ONLY_DOWNMIX)//nono 3-8-18 18:41
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                #endif
              #elif defined(ONLY_DOWNMIX_SUBW)              
                //item3
                //{SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
                //item4
                {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                
              #else
               
                //item3
                {SET_SCALE,STR_OS_CSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set c-speaker delay
                //item4
                {SET_SCALE,STR_OS_SSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set s-speaker delay
              
                //item5
                {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
                //item6
                {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
              #endif
                //item7
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
            #endif
        },

#else//#ifdef NO_DIGIT_VIDEO_MENU
    #ifndef SETUP_DONGLI459//20040206
    //page 3-VIDEO SETUP
    {
        #ifndef ARGUS_PDVD_MENU_PLUS //Jack added for argus portable
        //item0
        //{SET_FUNC, STR_OS_SHARPNESS, STR_OS_HIGH_SHARP, STR_OS_MID_SHARP, STR_OS_LOW_SHARP, 0, 0, 0, 0,0},
        {SET_SCALE,STR_OS_BRIGHTNESS,0,0,0,0,0, 0, 0,0},
        //item1
        {SET_SCALE,STR_OS_CONTRAST,0,0,0,0,0, 0, 0,0},

        #ifndef HJ_APEX_NO_HUE_SATURATION
        //item2
        {SET_SCALE,STR_OS_HUE,0,0,0,0,0, 0, 0,0},
        //item3
        {SET_SCALE,STR_OS_SATURATION,0,0,0,0,0, 0, 0,0},
        #endif//#ifndef HJ_APEX_NO_HUE_SATURATION
        #ifdef ADJUST_JPEG_SLIDE_TIME //lijd 2005-4-21 17:14
      			{SET_FUNC,STR_OS_TIME,STR_OS_15_SEC,STR_OS_30_SEC,STR_OS_45_SEC,0,0, 0,0,0},  
      	#endif  		   
        #ifdef DIP_CFG_ENABLE
            {SET_SCALE,STR_OS_DEINTLC,0,0,0,0,0, 0, 0,0},
        #endif //#ifdef DIP_CFG_ENABLE

/*        #ifdef BBK_SIMPLE_SETUP                //sunzhh add 2004-4-22 15:04
        {SET_FUNC, STR_OS_SHARPNESS, STR_OS_HIGH_SHARP, STR_OS_MID_SHARP, STR_OS_LOW_SHARP, 0, 0, 0, 0,0},
        #endif //#ifdef  BBK_SIMPLE_SETUP      
*/
        #ifdef ADD_DVI311_SETUP //tjf add dvi311 setup 2004-5-8 10:58
        {SET_SCALE,STR_SPHE6500_FMT,0,0,0,0,0, 0, 0,0},   
        //{SET_FUNC,STR_OS_DVI311_FORMAT,STR_OS_ANOLOG_OUTPUT,STR_OS_DIGIT_OUTPUT,0,0,0, 0, 0,0},
        #endif
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},

        #ifdef HJ_APEX_NO_HUE_SATURATION
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif//#ifndef HJ_APEX_NO_HUE_SATURATION

        #ifndef DIP_CFG_ENABLE
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif//#ifdef DIP_CFG_ENABLE
        
        #else //argus portable use
        //item0
        {SET_SCALE,STR_OS_CONTRAST,0,0,0,0,0, 0, 0,0},

        //item1
        {SET_SCALE,STR_OS_HUE,0,0,0,0,0, 0, 0,0},
        
        //item2
        {SET_SCALE,STR_OS_SATURATION,0,0,0,0,0, 0, 0,0},
        //item 3  
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item 4
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item 5
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        //item 6
        {SET_NE,0,0,0,0,0,0, 0, 0,0},  
        //item 7
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        
        //{SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif //end #ifndef SUPPORT_FUNCTION_MENU
    },
    #endif //#ifndef SETUP_DONGLI459   
#endif//#ifdef NO_DIGIT_VIDEO_MENU

    #ifdef SETUP_DONGLI459
    //page 4-SPEAKER SETUP
        {
        {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,0,0,0, 0, 0,0},
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
},
#endif

       #if !defined(SETUP_DONGLI459)&&!defined(EASTECH_NEW_SETUP_MENU)//20040206
        {
            //item0
            #if defined(SHOW_5_1CH)
                #ifdef JIEKE_DVD //wangfeng,2003-10-12 10:39
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_6CH_SETUP,0, 0, 0,0,0},
                #else
                #ifdef ONLY_SHOW_LRANDSTEREO        //LINRC ADD 2004-6-7 12:46
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,0,0,0, 0, 0,0},
                #else
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_6CH_SETUP,0, 0, 0,0},
                #endif
                #endif
            #elif defined(SETUP_DOWNMIX_NO_VSURROUND_OFF)
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,0,0, 0, 0,0},    
            #elif defined(TEMP_TWO_CHANNEL)||defined(GBM_TEMP_TWO_CHANNEL)
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,0,0, 0, 0,0},
            
            #elif defined(NO_VSURROUND_CHANNEL)
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_OFF,0, 0, 0,0},
            #elif defined( DOWNMIX_OFF_DISP_5CH_ON )//zxb 2005-4-27 15:53 "DOWNMIX_OFF" is replaced by "5CH_ON"
            	{SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_5CH_ON,0, 0, 0,0},                              
            #else
                {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_OFF,0, 0, 0,0},
            #endif
            
            #ifndef ONLY_DOWNMIX
            //item1
          
            {SET_FUNC,STR_OS_SUBWOOFER,STR_OS_OFF,STR_OS_ON,0,0,0, 0, 0,0},     //set subwoofer on/off
        
            #endif//#ifdef ONLY_DOWNMIX

            #ifndef AC3_BASS_MANAGEMENT
                //item2
                {SET_SCALE,STR_OS_FSPK,0,0,0,0,0, 0, 0,0},          //set front speaker gain
                //item3
                {SET_SCALE,STR_OS_CSPK,0,0,0,0, 0, 0, 0,0},         //set c-speaker gain
                //item4
                {SET_SCALE,STR_OS_SSPK,0,0,0,0, 0, 0, 0,0},         //set s-speaker gain
                //item5
                {SET_SCALE,STR_OS_CSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set c-speaker delay
                //item6
                {SET_SCALE,STR_OS_SSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set s-speaker delay
                //item7
                {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
            #else
                //item2
               
                #ifdef KSD_DVD
                {SET_FUNC,STR_OS_BASS_MANAGEMENT,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
                #elif defined(JIEKE_DVD)
                {SET_FUNC,STR_OS_BASS_MANAGEMENT,STR_OS_BASS_MODE_3,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,0,0, 0, 0,0},
                #elif defined(SET_FCR_SPEAKER)//xyy 2004-10-23 10:50
                {SET_FUNC,STR_OS_FSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_OFF,0,0, 0, 0,0}, //xulf 2004-01-05
                #elif !defined(ONLY_DOWNMIX)
                    #ifdef TEST_BASS_MANAGEMENT
                        {SET_FUNC,STR_OS_FSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,0,0,0, 0, 0,0},                 
                    #else                   
                {SET_FUNC,STR_OS_BASS_MANAGEMENT,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_BASS_MODE_3,0,0, 0, 0,0},
                #endif
                #endif
         
                
      #if defined(TEMP_TWO_CHANNEL)||defined(ONLY_DOWNMIX_SUBW)
                //item3
                //{SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
                //item4
                {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                #if defined(ONLY_DOWNMIX)//nono 3-8-18 18:41
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
                #endif
         #elif defined(SET_FCR_SPEAKER)//xyy 2004-10-23 10:49
                //item3       //xulf 2004-01-05
                {SET_FUNC,STR_OS_CSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_OFF,0,0, 0, 0,0},   
                //item4
                {SET_FUNC,STR_OS_SSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_OFF,0,0, 0, 0,0},        
                //item5
                {SET_SCALE,STR_OS_CSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set c-speaker delay
                //item6
                {SET_SCALE,STR_OS_SSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set s-speaker delay
                //item7
                {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},          
            #else
                #ifdef TEST_BASS_MANAGEMENT
                        //item3
                        {SET_FUNC,STR_OS_CSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_BASS_MODE_3,0,0, 0, 0,0},                    
                        //item4
                        {SET_FUNC,STR_OS_SSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_BASS_MODE_3,0,0, 0, 0,0},                    
                        //item5
                        {SET_SCALE,STR_OS_CSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set c-speaker delay
                        //item6
                        {SET_SCALE,STR_OS_SSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set s-speaker delay                                       
                        //item7
                        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},  
                #else               
                //item3
                {SET_SCALE,STR_OS_CSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set c-speaker delay
                //item4
                {SET_SCALE,STR_OS_SSPK_DELAY,0,0,0,0, 0, 0, 0,0},   //set s-speaker delay
           #ifndef SYBER_DVD//liweihua add 2004-2-4    
                //item5
                {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
           #endif
                //item6
                {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
                #endif //TEST_BASS_MANAGEMENT
            #endif
                //item7
                {SET_NE,0,0,0,0,0,0, 0, 0,0},
            #endif//#ifndef AC3_BASS_MANAGEMENT
        },
        #endif//#ifndef SETUP_DONGLI459//20040206
    //page 5-DIGITAL SETUP
#ifdef SETUP_DONGLI459
{
   {SET_SCALE,STR_OS_DYNAMICRANGE,0,0,0,0,0, 0, 0,0},
    {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
    {SET_NE,0,0,0,0,0,0, 0, 0,0},
},
#endif

    #if !defined(SETUP_DONGLI459)&&!defined(EASTECH_NEW_SETUP_MENU)
    {
        //item0
    #ifndef SYBER_DVD//liweihua add 2004-2-4
            #ifdef BIG_AC3_VOICE    //terry, adjust ac3 default voice volume,2002/4/30 12:26AM
                {SET_FUNC,STR_OS_DOLBY_OP_SETUP,STR_OS_DOLBY_RF_SETUP,STR_OS_DOLBY_LINE_SETUP,0,0,0, 0, 0,0},
        #elif !defined(HJ_APEX_NO_OPMODE)//terry,2002/5/8 05:48と,fixed small voice
                {SET_FUNC,STR_OS_DOLBY_OP_SETUP,STR_OS_DOLBY_LINE_SETUP,STR_OS_DOLBY_RF_SETUP,0,0,0, 0, 0,0},
            #endif
     #endif//#ifndef SYBER_DVD//liweihua add 2004-2-4   
                //item1
        #ifndef NO_AC3_DYNAMIC_RANGE
            {SET_SCALE,STR_OS_DYNAMICRANGE,0,0,0,0,0, 0, 0,0},
        #endif
        //item2
#ifdef EASTWIN
#else

#ifdef NO_MONO_SETUP  //xyy 2004-11-8 16:12

#else
        {SET_FUNC,STR_OS_DUAL_MONO_SETUP,STR_OS_STEREO,STR_OS_CHL,STR_OS_CHR,STR_OS_MIX_MONO_SETUP,0, 0, 0,0},
#endif
#endif
        //item3
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item4
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item5
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0},

#ifdef NO_MONO_SETUP  //xyy 2004-11-8
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
#endif
        #ifdef HJ_APEX_NO_OPMODE
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif

        #ifdef NO_AC3_DYNAMIC_RANGE
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif
    },
    #endif//#ifndef SETUP_DONGLI459//20040206

    #ifdef  Ti3001_OSD_UI_2
    //page 6- AMP_SETUP1   "功放设定1"
        {
            //item0
            {SET_SCALE,STR_OS_AMP_MAINVOLUME,0,0,0, 0,0,0,0,0},
            //item1
            {SET_SCALE,STR_OS_AMP_FSPK,0,0,0,0,0,0, 0, 0},
            //item2
            {SET_SCALE,STR_OS_AMP_FSPK_BALANCE,0,0,0,0,0,0, 0, 0},
            //item3
            {SET_SCALE,STR_OS_AMP_SSPK,0,0,0,0,0,0, 0, 0},
            //item4
            {SET_SCALE,STR_OS_AMP_SSPK_BALANCE,0,0,0,0,0,0, 0, 0},
            //item5
            {SET_SCALE,STR_OS_AMP_CSPK,0,0,0,0,0,0, 0, 0},
            //item6
            {SET_SCALE,STR_OS_AMP_SUBWOOFER,0,0,0,0,0,0, 0, 0},
            //item7
            {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
            //item8
            //        {SET_NE,0,0,0,0,0,0, 0, 0,0},
            //item9
            //        {SET_NE,0,0,0,0,0,0, 0, 0,0},
            },

    //page 7-AMP-SETUP2   "功放设定2"
        {
            //item0
            {SET_SCALE,STR_OS_AMP_BASS,0,0,0, 0,0,0,0,0},
            //item1
            {SET_SCALE,STR_OS_AMP_TREMBLE,0,0,0,0,0,0, 0, 0},
            //item2
            {SET_SCALE,STR_OS_AMP_DYNAMICRANGE,0,0,0,0,0,0, 0, 0},
            //item3
            {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
            //item4
            {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
            //item5
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
            //item6
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
            //item7
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
            //item8
            //        {SET_NE,0,0,0,0,0,0, 0, 0,0},
            //item9
            //        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        },
    #endif //#ifdef  Ti3001_OSD_UI_2
    #ifdef SETUP_DONGLI459//20040206
    {
            {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
    },
    #endif
#endif//#ifdef QSI_SETUP_MENU       

    //custm setup page
    {
        //item0
        {SET_SHOW,STR_OS_FIRMWARE_ID,STR_OS_SPACE,0,0,0,0, 0, 0,0},
        //item1
        #ifdef OP_CUST_UI
        {SET_SHOW,STR_OS_CHECK,STR_OS_SPACE,0,0,0,0, 0, 0,0},
        #else
        {SET_SHOW,STR_OS_CHIP_ID,STR_OS_SPACE,0,0,0,0, 0, 0,0},
        #endif

        #ifndef RCD_GPIO_CONTROL                                            // alan 2002/7/26 02:08と
            //item2
            {SET_FUNC,STR_OS_REGION_CODE,STR_OS_REGION_0,STR_OS_REGION_1,STR_OS_REGION_2,STR_OS_REGION_3,STR_OS_REGION_4, STR_OS_REGION_5, STR_OS_REGION_6,0},
        #endif
#ifndef EASTECH_NEW_SETUP_MENU  // cancel by Tom  20040713
        //item3
        #ifdef RATING_8
            {SET_FUNC,STR_OS_RATING,STR_OS_RATING_1,STR_OS_RATING_2,STR_OS_RATING_3,STR_OS_RATING_4,STR_OS_RATING_5,STR_OS_RATING_6,STR_OS_RATING_7,STR_OS_RATING_8},
        #else
            {SET_FUNC,STR_OS_RATING,STR_OS_NO_ADULT,STR_OS_KID_ONLY,STR_OS_VIEW_ALL,0,0, 0, 0,0},
        #endif
        //item4
        #ifndef OP_CUST_UI
        {SET_NM,STR_OS_PASSWORD,STR_OS_LOCK,STR_OS_UNLOCK,0,0,0, 0, 0,0},//LIBING 2005-5-5 15:48
        #else
        {SET_SHOW,STR_OS_MICRO,STR_OS_NUB2,0,0,0,0, 0, 0,0},
        #endif
#endif        
        #ifdef CORTROL_VCD_ONF
        {SET_FUNC, STR_OS_VCD, STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
        #endif
#ifdef SUPER_DEFAULT_OSD_LANG
        {SET_FUNC,STR_OS_OSD, OSD_LAGN_SETUP_STRING},
#endif
#ifdef TEST_INTERLACE//Modifed by chenzhao on 2004-11-15 10:33   
        {SET_SHOW,STR_OS_DEINTLC,0,0,0,0,0, 0, 0,0},
#endif
        //item5
        #ifdef OP_CUST_UI
        {SET_SHOW,STR_OS_DIVX,STR_OS_NUB,0,0,0,0, 0, 0,0},
        #else
        //{SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0},
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        #endif
        //item6
        #ifdef OP_CUST_UI
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        #else
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif

#ifndef SUPER_DEFAULT_OSD_LANG
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
#endif 
        #ifdef RCD_GPIO_CONTROL                                                     // alan 2002/7/26 02:08と
            {SET_NE,0,0,0,0,0,0, 0, 0,0},
        #endif

},

#ifdef BBK_NEW_SETUP     //PAGE = 7 //zhaoyanhua add 03-11-7 10:10
    
{
        {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_OFF,0, 0, 0,0},
        {SET_FUNC, STR_OS_TV_SYS, TV_SYS_SETUP_STRING},
        {SET_FUNC,STR_OS_DEFAULT_SETUP,STR_OS_RESTORE_SETUP,0,0,0,0, 0, 0,0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},        
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
},
#endif  
    
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)//PAGE = 7
#if defined(NEXTPAGE_SYS)       //freyman 2004-3-25 22:42
    {

#ifndef GBM_FULL_FUNCTION
        {SET_FUNC,STR_OS_DEFAULT_SETUP,STR_OS_RESTORE_SETUP,0,0,0,0, 0, 0,0},
#endif//GBM_FULL_FUNCTION


#if !defined(NOT_SHOW_SAME_DISC_RESUME)&&defined(SAME_DISC_RESUME)
        {SET_FUNC,STR_OS_RESUME,STR_OS_OFF,STR_OS_ON,0,0,0, 0, 0,0},
#endif//NOT_SHOW_SAME_DISC_RESUME

#ifdef SHOW_STANDBY_TIMER           //suqiaoli add 2003-8-2
    {SET_FUNC,STR_OS_VFD_TIME,STR_OS_VFD_TIME_NUM,0,0,0,0, 0, 0,0},
#endif

#if defined(USER_MPEG_LOGO)&&!defined(NO_SHOW_MPEG_LOGO_SETUP_ITEM)     //gerry,2004-3-8 18:50
    #ifdef JIEKE_DVD
        {SET_FUNC,STR_OS_SELECT_LOGO,STR_OS_JIEKE_SETUP,STR_OS_MPEG_LOGO,0,0, 0, 0,0,0},
    #elif defined(NINTAUS_DVD)
            {SET_FUNC,STR_OS_SELECT_LOGO,STR_OS_RESTORE_SETUP1,STR_OS_MPEG_LOGO,0,0, 0, 0,0,0},
    #else
        {SET_FUNC,STR_OS_SELECT_LOGO,STR_OS_RESTORE_SETUP,STR_OS_MPEG_LOGO,0,0, 0, 0,0,0},
    #endif 
#endif 
#ifdef GBM_FULL_FUNCTION
        {SET_NM,STR_OS_PASSWORD,STR_OS_LOCK,STR_OS_UNLOCK,0,0,0, 0, 0,0},
        #ifdef RATING_8
            {SET_FUNC,STR_OS_RATING,STR_OS_RATING_1,STR_OS_RATING_2,STR_OS_RATING_3,STR_OS_RATING_4,STR_OS_RATING_5,STR_OS_RATING_6,STR_OS_RATING_7,STR_OS_RATING_8},
            
        #else
            {SET_FUNC,STR_OS_RATING,STR_OS_NO_ADULT,STR_OS_KID_ONLY,STR_OS_VIEW_ALL,0,0, 0,0,0},
        #endif
#endif//GBM_FULL_FUNCTION
#ifdef SYBER_DVD//liweihua add 2004-2-4
        //item 1
        {SET_FUNC,STR_OS_ANGLE_MARK,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
        //item 2
        {SET_FUNC,STR_OS_CLOSED_CAPTION,STR_OS_OFF,STR_OS_ON,0,0,0, 0, 0,0},
#endif

#ifdef SUPPORT_DVD_NATIVE_GAME	//linrc for NATIVE_GAME 2005-10-18 14:48
		{SET_FUNC,STR_OS_GAME,STR_OS_GAME_BOXMAN,STR_OS_GAME_TETRIS,STR_OS_GAME_HITRAT,STR_OS_GAME_HITRAT,0, 0, 0,0},
#endif

#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP            //gerry,2004-2-2 20:21
        //{SET_SH,STR_OS_PREV_PAGE,0,0,0,0,0, 0, 0,0},

        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
#else//NEXT_PAGE_SHOW_ADVANCED_SETUP
        {SET_SH,STR_OS_PREV_PAGE,0,0,0,0,0, 0, 0,0},

        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
#endif//NEXT_PAGE_SHOW_ADVANCED_SETUP

    }
#endif 
};

