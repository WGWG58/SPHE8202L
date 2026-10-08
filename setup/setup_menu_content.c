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
#define	setup_page_SYS2	7

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
        {SET_SHOW, STR_OS_SYS_SETUP, setup_page_SYS, 2, 0,0,0,0,0,0,0,0,0},	//page 0
    	//item0
        {SET_FUNC, STR_OS_TV_SYS, TV_SYS_SETUP_STRING, 0, 0, SETUP_VA_TV_SYS, 0},
        //item1
        {SET_FUNC,STR_OS_SSAVER_SETUP,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0, 1, SETUP_VA_SSAVER, 0},
        //item2
        {SET_FUNC,STR_OS_VIDEO,VIDEO_SETUP_STRING, 0, 2, SETUP_VA_VIDEO, 0},
        //item3
        {SET_FUNC,STR_OS_TV_RATIO,STR_OS_4_3PS,STR_OS_4_3LB,STR_OS_16_9,0, 0, 0,0,0, 3, SETUP_VA_TV_RATIO, 0},        
        //item4
        {SET_NM,STR_OS_PASSWORD,STR_OS_LOCK,STR_OS_UNLOCK,0,0,0, 0, 0,0, 0, SETUP_VA_PASSWORD, 0},
        //item5
    	{SET_FUNC,STR_OS_RATING,STR_OS_NO_ADULT,STR_OS_KID_ONLY,STR_OS_VIEW_ALL,0,0, 0,0,0, 5, SETUP_VA_RATING, 2},
    	//item6
    	{SET_FUNC,STR_OS_DEFAULT_SETUP,STR_OS_RESTORE_SETUP,0,0,0,0, 0, 0,0, 6, SETUP_VA_DEFAULT, 0},
    	//item7    
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
    },
	//=========================================================================================	


    //page 1-LANGUAGE SETUP
    {
        {SET_SHOW, STR_OS_LANG_SETUP, setup_page_LAN,6, 0,0,0,0,0,0,0,0,0},	//page 1
    	//item0
        {SET_FUNC,STR_OS_OSD, OSD_LAGN_SETUP_STRING, 0, SETUP_VA_OSD_LANG, 0},
        //item1
        {SET_FUNC,STR_OS_AUDIO_LANG_SETUP,OSD_AUDIO_LAGN_SETUP_STRING, 0, SETUP_VA_AUDIO_LANG, 0},
	 	//item2
        {SET_FUNC,STR_OS_SUBTITLE_LANG_SETUP,OSD_SUBT_LAGN_SETUP_STRING, 0, SETUP_VA_SUBTITLE_LAN, 0},
        //item3
        {SET_FUNC,STR_OS_MENU_LANG_SETUP,OSD_MENU_LAGN_SETUP_STRING, 0, SETUP_VA_MENU_LANG, 0},
        //item4
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item5
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
    },
    //=========================================================================================

        
    //page 2-AUDIO SETUP
    {
    	{SET_SHOW, STR_OS_AUD_SETUP, setup_page_AUD, 10, 0,0,0,0,0,0,0,0,0},	//page 2
		//item0
        {SET_FUNC,STR_OS_AUD_OUT,STR_OS_SIMULATE,STR_OS_BITSTREAM,STR_OS_STEREO_PCM,0,0, 0, 0,0, 0, SETUP_VA_AUD_OUT, 0},
        //item1
        {SET_FUNC,STR_OS_MIC_ONOFF,STR_OS_AUTO,STR_OS_OFF,0,0,0, 0, 0,0, 1, SETUP_VA_MIC_ONOFF, 0},
        //item2
        {SET_SCALE,STR_OS_ECHO,5,0,8,0,0, 0, 0,0, 0, SETUP_VA_ECHO, 4},
        //item3
        {SET_SCALE,STR_OS_MIC_VOL,5,0,8,0,0, 0, 0,0, 1, SETUP_VA_MIC_VOL, 6},
        //item4
        {SET_SCALE,STR_OS_KEY,7,0,12,0,0, 0, 0,0, 1, SETUP_VA_KEY, 6},
        //item5
        {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0, 5, SETUP_VA_FREQ_MASK, 0},
        //item6
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
    },
  	//=========================================================================================


    //page 3-VIDEO SETUP
    {
    	{SET_SHOW, STR_OS_VIDEO_SETUP, setup_page_VID, 16, 0,0,0,0,0,0,0,0,0},	//page 3
	    //item0
        {SET_SCALE,STR_OS_BRIGHTNESS,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_BRIGHTNESS, 6},
        //item1
        {SET_SCALE,STR_OS_CONTRAST,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_CONTRAST, 6},
        //item2
        {SET_SCALE,STR_OS_HUE,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_HUE, 6},
        //item3
        {SET_SCALE,STR_OS_SATURATION,7,0,12,0,0, 0, 0,0, 0, SETUP_VA_SATURATION, 0},
        //item4
		{SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item5
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},        
    },
	//=========================================================================================


	//page 4-SPEAKER SETUP
    {
    	{SET_SHOW, STR_OS_SPK_SETUP, setup_page_SPE, 20, 0,0,0,0,0,0,0,0,0},	//page 4
		//item0
        {SET_FUNC,STR_OS_DOWNMIX_SETUP,STR_OS_LTRT_SETUP,STR_OS_STEREO,STR_OS_VSURROUND_SETUP,STR_OS_OFF,0, 0, 0,0, 0, SETUP_VA_DOWNMIX, 2},
        //item1      
        {SET_FUNC,STR_OS_SUBWOOFER,STR_OS_OFF,STR_OS_ON,0,0,0, 0, 0,0, 1, SETUP_VA_SUBWOOFER, 1},     //set subwoofer on/off
    	 //item2
        {SET_FUNC,STR_OS_BASS_MANAGEMENT,STR_OS_BASS_MODE_1,STR_OS_BASS_MODE_2,STR_OS_BASS_MODE_3,0,0, 0, 0,0, 2, SETUP_VA_BASE_MODE, 0},
        //item3
        {SET_SCALE,STR_OS_CSPK_DELAY,4,0,5,0, 0, 0, 0,0, 2, SETUP_VA_CSPK_DELAY, 0},   //set c-speaker delay
        //item4
        {SET_SCALE,STR_OS_SSPK_DELAY,4,0,5,0, 0, 0, 0,0, 2, SETUP_VA_SSPK_DELAY, 2},   //set s-speaker delay
        //item5
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item6
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
    },
	//==============================================================================================	


    //page 5-DIGITAL SETUP
    {
        {SET_SHOW, STR_OS_DIGTAL_SETUP, setup_page_DIG, 22, 0,0,0,0,0,0,0,0,0},	//page 5
		//item0
        {SET_FUNC,STR_OS_DOLBY_OP_SETUP,STR_OS_DOLBY_LINE_SETUP,STR_OS_DOLBY_RF_SETUP,0,0,0, 0, 0,0, 0, SETUP_VA_DOLBY_OP, 0},
        //item1
        {SET_SCALE,STR_OS_DYNAMICRANGE,5,0,8,0,0, 0, 0,0, 0, SETUP_VA_DYNAMCRANGE, 0},
        //item2
        {SET_FUNC,STR_OS_DUAL_MONO_SETUP,STR_OS_STEREO,STR_OS_CHL,STR_OS_CHR,STR_OS_MIX_MONO_SETUP,0, 0, 0,0, 2, SETUP_VA_DUAL_MONO, 3},
        //item3
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item4
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item5
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        
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
        {SET_FUNC,STR_OS_RATING,STR_OS_NO_ADULT,STR_OS_KID_ONLY,STR_OS_VIEW_ALL,0,0, 0, 0,0, 3, SETUP_VA_RATING, 2},
        //item4
        {SET_NM,STR_OS_PASSWORD,STR_OS_LOCK,STR_OS_UNLOCK,0,0,0, 0, 0,0, 4, SETUP_VA_NONE, 0},
        //item5
        {SET_SH,STR_OS_EXIT_MENU,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item6
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0, 0, SETUP_VA_NONE, 0},
	},
	//====================================================================================================
};


//===========================================ending=================================


