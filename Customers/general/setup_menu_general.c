/***************************************************************
*  setup_menu_content.c
*  include  in setup_item.c   when defined DVD_SETUP_REENG
* 
* Creator: 	JSLin 
* Date:  		2004/07/28
*
* Description :	
*			the content of setup menu (setup_item[Page][Item][Selection]) 
*			can be transform into graphical presentation (GUI)
*				
****************************************************************/


#define	setup_max_icon		6
#define	setup_page_SYS		0
#define	setup_page_LAN		1
#define	setup_page_AUD		2
#define	setup_page_VID		3
#define	setup_page_SPE		4
#define	setup_page_DIG		5
#define	setup_page_CUS		6
//#define	setup_page_SYS2		7

enum
{
	SETUP_ML0 = 0,
	SETUP_ML1 = 1,	//page level
	SETUP_ML2,		//item level
	SETUP_ML3 		//select level
};					//setup menu moving level

enum
{
	SETUP_ENTER = 0,
	SETUP_SELECTION = 1,
	SETUP_UP = 2,
	SETUP_DOWN,
	SETUP_LEFT,
	SETUP_RIGHT
};					// setup moving direction

enum
{
	SETUP_itemNormal = 0,
	SETUP_itemMark = 1,
	SETUP_itemSelected = 2,
	SETUP_itemTitle = 3,
    #ifdef USE_SETUP_ITEM_ENABLE_FLAG //Added by chenzhao
    SETUP_itemDisnable,
    #endif

};					//GUI item type 


UINT8 setup_pos[4] = {0,0,0,0};
UINT8 setup_last_pos[4] = {0,0,0,0};
UINT8 setup_mLevel, setup_mDir, setup_itemType;
UINT32 setup_refresh = 0;



//======================================================================================

const UINT8 setup_item[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM+1][MAX_ITEM_SEL+1+1+1]=
{
    //page 0-SYSTEM SETUP
    {
        {SET_SHOW, STR_OS_SYS_SETUP, setup_page_SYS, 2, 8,0,0,0,0,0,0,0,0},	//page 0
        #ifdef SELECT_MEDIA_IN_SETUPMENU //Maoyong 2004.08.09
        //item0
        #ifndef SUPPORT_USB
        {SET_FUNC,STR_OS_MEDIA_TYPE,STR_OS_MEDIA_DISC,STR_OS_MEDIA_CARD,0,0, 0, 0, 0, 0,0, SETUP_VA_MEDIA_TYPE, 0},
        #elif !defined(SPHE8202_CARD_STORAGE)
        {SET_FUNC,STR_OS_MEDIA_TYPE,STR_OS_MEDIA_DISC,STR_OS_MEDIA_USB,0,0, 0, 0, 0, 0,0, SETUP_VA_MEDIA_TYPE, 0},
        #else
        {SET_FUNC,STR_OS_MEDIA_TYPE,STR_OS_MEDIA_DISC,STR_OS_MEDIA_USB,STR_OS_MEDIA_CARD,0, 0, 0, 0, 0,0,SETUP_VA_MEDIA_TYPE, 0},
        #endif
        //item1
        {SET_FUNC, STR_OS_TV_SYS, TV_SYS_SETUP_STRING, 0, 1, SETUP_VA_TV_SYS, DEFAULT_TV_SYS},//can use DEFAULT_TV_SYS hongfeng 2005-03-09 
        #else   //#endif SELETC_MEDIA_IN_SETUPMENU      
      
    	//item0
        {SET_FUNC, STR_OS_TV_SYS, TV_SYS_SETUP_STRING, 0, 0, SETUP_VA_TV_SYS,  DEFAULT_TV_SYS},
        //item1
        {SET_FUNC,STR_OS_SSAVER_SETUP,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0, 1, SETUP_VA_SSAVER, 0},
        #endif
        //item2
        {SET_FUNC,STR_OS_VIDEO,VIDEO_SETUP_STRING, 0, 2, SETUP_VA_VIDEO, 0},
        //item3
        {SET_FUNC,STR_OS_TV_RATIO,STR_OS_4_3PS,STR_OS_4_3LB,STR_OS_16_9,0, 0, 0,0,0, 3, SETUP_VA_TV_RATIO, 0},        
        //item4
        {SET_NM,STR_OS_PASSWORD,STR_OS_LOCK,STR_OS_UNLOCK,0,0,0, 0, 0,0, 0, SETUP_VA_PASSWORD, 0},
        //item5
        #ifdef RATING_8   //denghg add 2005-1-25 22:53
       {SET_FUNC,STR_OS_RATING,STR_OS_RATING_1,STR_OS_RATING_2,STR_OS_RATING_3,STR_OS_RATING_4,STR_OS_RATING_5, STR_OS_RATING_6,STR_OS_RATING_7,STR_OS_RATING_8, 0, SETUP_VA_RATING, 7},
    	  #else
    	{SET_FUNC,STR_OS_RATING,STR_OS_NO_ADULT,STR_OS_KID_ONLY,STR_OS_VIEW_ALL,0,0, 0,0,0, 5, SETUP_VA_RATING, 2},
    	  #endif
    	//item6
    	{SET_FUNC,STR_OS_DEFAULT_SETUP,STR_OS_RESTORE_SETUP,0,0,0,0, 0, 0,0, 6, SETUP_VA_DEFAULT, 0},
    	//item7    

#ifndef INDIGO_STYLE_OSDUI
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
#endif       
    },
	//=========================================================================================	


    //page 1-LANGUAGE SETUP
    {
        {SET_SHOW, STR_OS_LANG_SETUP, setup_page_LAN, 2, 18,0,0,0,0,0,0,0,0},	//page 1
    	//item0
        {SET_FUNC,STR_OS_OSD, OSD_LAGN_SETUP_STRING, 0, SETUP_VA_OSD_LANG, 0},
        //item1
        {SET_FUNC,STR_OS_AUDIO_LANG_SETUP,OSD_AUDIO_LAGN_SETUP_STRING, 0, SETUP_VA_AUDIO_LANG, 0},
	 	//item2
        {SET_FUNC,STR_OS_SUBTITLE_LANG_SETUP,OSD_SUBT_LAGN_SETUP_STRING, 0, SETUP_VA_SUBTITLE_LAN, 0},
        //item3
        {SET_FUNC,STR_OS_MENU_LANG_SETUP,OSD_MENU_LAGN_SETUP_STRING, 0, SETUP_VA_MENU_LANG, 0},
#ifdef SHOW_DRM_REGISTRATION_CODE_IN_SETUP
#ifdef DRM_CODE //WSLEE for drm code 050615
        {SET_FUNC,STR_OS_DRM_REGISTRATION_CODE,1,0,0,0,0,0,0,0,0, SETUP_VA_NONE, 0}, //helm 050622
#else
        {SET_SH,STR_OS_DRM_REGISTRATION_CODE,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
#endif

#else
        //item4
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
#endif
        //item5
 #ifndef INDIGO_STYLE_OSDUI        
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
#endif        
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
    },
    //=========================================================================================
     //page 2-AUDIO SETUP //ycwen 2005/3/29 modified for freq_mask and prologicII
    {
    	{SET_SHOW, STR_OS_AUD_SETUP, setup_page_AUD, 2, 28,0,0,0,0,0,0,0,0},	//page 2		
    	
    	#ifdef HDMI//Modifed by chenzhao on 2004-11-24 16:28   
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0, 0, SETUP_VA_AUD_OUT, 2},
        #else//HDMI
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0, 0, SETUP_VA_AUD_OUT, 0},
        #endif//HDMI
		        
        #ifndef NO_MIC    //DENGHG  ADD  2005-2-25 10:35                
        {SET_FUNC,STR_OS_MIC_ONOFF,STR_OS_AUTO,STR_OS_OFF,0,0,0, 0, 0,0, 1, SETUP_VA_MIC_ONOFF, 0},
        #endif
        
        #ifdef USE_FREQ_MASK
        {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0, 1, SETUP_VA_FREQ_MASK, 0},
        #endif    

        #if defined (SUPPORT_PROLOGIC_II) && !defined (SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //ycwen 2005/5/17 PrologicII adv function
        {SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0,1,SETUP_VA_PROLOGIC,2},
        #endif        
        
        #ifndef HJ_APEX_NO_KEY
        {SET_SCALE,STR_OS_KEY,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_KEY, 6},        
        #endif     
        
        #ifndef NO_MIC
        {SET_SCALE,STR_OS_ECHO,5,0,8,0,0, 0, 0,0, 1, SETUP_VA_ECHO, 4},
        {SET_SCALE,STR_OS_MIC_VOL,5,0,8,0,0, 0, 0,0, 2, SETUP_VA_MIC_VOL, 6},        
        #endif
        
        #ifdef HJ_APEX_NO_KEY
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        #endif        

        #ifdef NO_MIC
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        #endif
        
        #ifndef USE_FREQ_MASK
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        #endif
        
        #ifndef SUPPORT_PROLOGIC_II
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        #endif

       //item7
#ifndef INDIGO_STYLE_OSDUI       
       {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},      
#endif       
    },
  	//=========================================================================================


    //page 3-VIDEO SETUP
    {
    	{SET_SHOW, STR_OS_VIDEO_SETUP, setup_page_VID, 2, 38,0,0,0,0,0,0,0,0},	//page 3
	    //item0
        {SET_SCALE,STR_OS_BRIGHTNESS,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_BRIGHTNESS, 6},
        //item1
        {SET_SCALE,STR_OS_CONTRAST,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_CONTRAST, 6},
        //item2
        {SET_SCALE,STR_OS_HUE,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_HUE, 6},
        //item3
        {SET_SCALE,STR_OS_SATURATION,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_SATURATION, 0},
        //item4
        #ifdef ADD_DVI311_SETUP//Modifed by chenzhao on 2004-11-23 13:32   
            #ifdef DVI311_NO_PC_MODE
            {SET_FUNC,STR_SPHE6500_FMT, STR_OS_720P, STR_OS_480P576P,0,0,0,0,0,0, 3, SETUP_VA_SPV311MODE, 1},
            #else
            {SET_FUNC,STR_SPHE6500_FMT,STR_OS_1080I, STR_OS_720P, STR_OS_480P576P,STR_OS_SXGA,STR_OS_XGA,STR_OS_SVGA,STR_OS_VGA,0, 0, SETUP_VA_SPV311MODE, 4},
            #endif
        #elif defined(ADJUST_JPEG_SLIDE_TIME)  ////lyc 2005/8/12
      			{SET_FUNC,STR_OS_TIME,STR_OS_15_SEC,STR_OS_30_SEC,STR_OS_45_SEC,0,0, 0,0,0,0,SET_VA_TIME,0},
        #elif defined(DIP_CFG_ENABLE)  //nono 5-9-23 0:22
      		{SET_SCALE,STR_OS_DEINTLC,4,0,6,0,0, 0, 0,0, 0, SETUP_VA_DE_INTERLACE, 0},
        #else
		{SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        #endif
        //item5
#ifndef INDIGO_STYLE_OSDUI        
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
#endif
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},        
     },
	//=========================================================================================


	//page 4-SPEAKER SETUP
    {
    	{SET_SHOW, STR_OS_SPK_SETUP, setup_page_SPE, 2, 48,0,0,0,0,0,0,0,0},	//page 4
#ifdef TEMP_TWO_CHANNEL
		//item0
        {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,0, 0, 0, 0,0, 0, SETUP_VA_DOWNMIX, 2},
#else
        {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_OFF,0, 0, 0,0, 0, SETUP_VA_DOWNMIX, 2},
        #endif

#ifndef ONLY_DOWNMIX
        //item1      
        {SET_FUNC,STR_OS_SUBWOOFER,STR_OS_OFF,STR_OS_ON,0,0,0, 0, 0,0, 1, SETUP_VA_SUBWOOFER, 1},     //set subwoofer on/off
    	 //item2
        {SET_SCALE,STR_OS_CSPK_DELAY,4,0,5,0, 0, 0, 0,0, 2, SETUP_VA_CSPK_DELAY, 0},   //set c-speaker delay
        //item3
        {SET_SCALE,STR_OS_SSPK_DELAY,4,0,5,0, 0, 0, 0,0, 2, SETUP_VA_SSPK_DELAY, 2},   //set s-speaker delay
#endif//#ifndef ONLY_DOWNMIX

    #ifdef SPEAKER_CONFIG //ycwen 2005/5/17 BASS_MANAGEMENT
        //item4
        {SET_FUNC,STR_OS_FSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,0,0,0, 0, 0,0, 4, SETUP_VA_FSPK, 0},
        //item5
        {SET_FUNC,STR_OS_CSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_OFF,0,0, 0, 0,0, 4, SETUP_VA_CSPK, 0},
        //item6
        {SET_FUNC,STR_OS_SSPK,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_OFF,0,0, 0, 0,0, 4, SETUP_VA_SSPK, 0},
    #elif defined(AC3_BASS_MANAGEMENT)//nono add.2006-5-24 20:24
        //item4
        {SET_FUNC,STR_OS_BASS_MANAGEMENT,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_BASS_MODE_3,0,0, 0, 0,0, 2, SETUP_VA_BASE_MODE, 0},
        //item5
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
    #else
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},        
    #endif


#ifdef ONLY_DOWNMIX
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
#endif
        //item7
#ifndef INDIGO_STYLE_OSDUI        
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
#endif        
    },
	//==============================================================================================	


    //page 5-DIGITAL SETUP
    {
        {SET_SHOW, STR_OS_DIGTAL_SETUP, setup_page_DIG, 2, 58,0,0,0,0,0,0,0,0},	//page 5
        //item0
        {SET_FUNC,STR_OS_DOLBY_OP_SETUP,STR_OS_DOLBY_LINE_SETUP,STR_OS_DOLBY_RF_SETUP,0,0,0, 0, 0,0, 0, SETUP_VA_DOLBY_OP, 0},
        //item1
        {SET_SCALE,STR_OS_DYNAMICRANGE,5,0,8,0,0, 0, 0,0, 0, SETUP_VA_DYNAMCRANGE, 0},
        //item2
        {SET_FUNC,STR_OS_DUAL_MONO_SETUP,STR_OS_STEREO,STR_OS_CHL,STR_OS_CHR,STR_OS_MIX_MONO_SETUP,0, 0, 0,0, 2, SETUP_VA_DUAL_MONO, 3},
        
#if defined(SUPPORT_PROLOGIC_II) && defined (SUPPORT_PROLOGIC_II_ADVANCE_SETTING) //ycwen 2005/5/17 PrologicII adv function
        {SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0,3,SETUP_VA_PROLOGIC,2},
        {SET_FUNC,STR_OS_PL_PANORAMA,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0, 4, SETUP_VA_PL_PANORAMA, 1},        
        {SET_SCALE,STR_OS_PL_CENTER_WIDTH,5,0,8,0,0, 0, 0,0, 3, SETUP_VA_PL_CENTER_WIDTH, 0},        
        {SET_SCALE,STR_OS_PL_DIMENSION,4,0,6,0,0, 0, 0,0, 4, SETUP_VA_PL_DIMENSION, 3},
#else 
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
		{SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
		{SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
		{SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
#endif                      
#ifndef INDIGO_STYLE_OSDUI        
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},        
#endif        
    },
	//==============================================================================================



    //custm setup page
    {
        {SET_SHOW, 0, 0, 0, 0,0,0,0,0,0,0,0,0},  //CSTUM page
	    //item0
        {SET_SHOW, STR_OS_FIRMWARE_ID, STR_OS_SPACE,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item1
        {SET_SHOW,STR_OS_CHIP_ID,STR_OS_SPACE,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item2
        {SET_FUNC,STR_OS_REGION_CODE,STR_OS_REGION_0,STR_OS_REGION_1,STR_OS_REGION_2,STR_OS_REGION_3,STR_OS_REGION_4, STR_OS_REGION_5, STR_OS_REGION_6,0, 2, SETUP_VA_REGION_CODE, 0},
        //item3
         #ifdef RATING_8   //denghg  add  2005-1-25 22:53
        {SET_FUNC,STR_OS_RATING,STR_OS_RATING_1,STR_OS_RATING_2,STR_OS_RATING_3,STR_OS_RATING_4,STR_OS_RATING_5, STR_OS_RATING_6,STR_OS_RATING_7,STR_OS_RATING_8, 0, SETUP_VA_RATING, 7},
    	  #else
        {SET_FUNC,STR_OS_RATING,STR_OS_NO_ADULT,STR_OS_KID_ONLY,STR_OS_VIEW_ALL,0,0, 0, 0,0, 3, SETUP_VA_RATING, 2},
        #endif
        //item4
        {SET_NM,STR_OS_PASSWORD,STR_OS_LOCK,STR_OS_UNLOCK,0,0,0, 0, 0,0, 4, SETUP_VA_NONE, 0},
        //item5
        #ifdef HDCP_CUSTOM//Modifed by chenzhao on 2004-11-23 13:32   
        {SET_FUNC,STR_OS_HDCP,STR_OS_ON, STR_OS_OFF, 0,0,0,0,0,0, 5, SETUP_VA_HDCP, 0},
        #elif defined(SERVO_DEBUG_MSG_ON_OSD)
        {SET_FUNC,STR_OS_SERVO_DEBUG,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0, 5, SETUP_VA_SERVO_DBG, 1}, //joshua, 20050711, modified for servo-debug function on OSD
        #else
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        #endif
       
        
        //item6
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
	},
	//====================================================================================================
};

#include "setup_color_index.h"

