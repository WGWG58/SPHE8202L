/*--------------------------------------------------------------------------
|  File Name   : menu_page.h
|
|  Description : This file is for menu page definition
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	20040226        liweihua        
|                       zhaoyanhua      creating
|--------------------------------------------------------------------------------*/

//page index-0
#define PLAYPAGE            0

#define DISCSTATEITEM       0


//page index-1
#define PLAYMODEPAGE        1

#define STANDARDITEM        0
#define RANDOMITEM          1
#define PROGRAMITEM         2
#define DISCPLAYLISTITEM    3
#define INTROSCANITEM       4
#define BONUSGROUPITEM      5

//page index-2,the item is not sure!
#define LOCKPAGE            2

#define LOCKPLAYERITEM		0
#define CHGPASSWDITEM      	1
#define RATINGLIMITS        2


//page index-3
#define DISPLAYPAGE         3

#define TVRATIOITEM         0
#define TVFORMATITEM        1
#define PSCANITEM           2
#define VIDEOUTITEM           3

//page index-4
#define SOUNDPAGE           4

#define DRCITEM             0
#define DIGITALOUTITEM      1
#define SPEAKERSETITEM      2
#define STEREOITEM          3
#define PROLMODEITEM        4
#define PROLCONTROLITEM     5

//page index-5
#define LANGUAGEPAGE        5

#define PLAYERMENUITEM      0
#define DISCMENUITEM        1
#define AUDIOITEM           2
#define SUBTITLEITEM        3


//page index_6
#define SPKSETUPPAGE		6
#define SPKSITEM			0
#define SPKDISTITEM			1
#define SPKVOLITEM			2

//page index - 7
#define PLCTLPAGE			7
#define PLCTLDIMEITEM		0
#define PLCTLPANOITEM		1
#define PLCTLCWITEM			2


//page index-8
#define SPKSPAGE			8
#define FRITEM				0
#define CENTERITEM			1
#define SUBWITEM			2
#define SURRITEM			3
#define BACKSURRITEM		4

//page index-9
#define DISTANCEPAGE		9
#define FRITEM				0
#define CENTERITEM			1
#define DISSURRITEM			2

//page index-10 for volume NOTe it not displayed in menu
#define VOLPAGE				0x0a
//for speaker volume	


//for speaker id
#define FRONT_SPK_ID			0
#define CENTER_SPK_ID			1
#define SW_SPK_ID				2
#define SURR_SPK_ID				3
#define NONE_SPK_ID				4//draw background box




//sel definition

#define MENU_GRADE				menu_sel[LOCKPAGE][RATINGLIMITS]
#define MENU_TV_FORMAT			menu_sel[DISPLAYPAGE][TVFORMATITEM]
#define MENU_TV_RATIO			menu_sel[DISPLAYPAGE][TVRATIOITEM]
#define MENU_TV_PSCAN			menu_sel[DISPLAYPAGE][PSCANITEM]
#define MENU_TV_VIDEO_OUT		menu_sel[DISPLAYPAGE][VIDEOUTITEM]	

#define MENU_SOUND_DRC			menu_sel[SOUNDPAGE][DRCITEM]
#define MENU_SOUND_DIGIT_OUT	menu_sel[SOUNDPAGE][DIGITALOUTITEM]
#define SOUND_STEREO			menu_sel[SOUNDPAGE][STEREOITEM]
#define PL_MODE					menu_sel[SOUNDPAGE][PROLMODEITEM]

#define SPK_VOL					menu_sel[SPKSETUPPAGE][SPKVOLITEM]

#define PL_CTL_DIME				menu_sel[PLCTLPAGE][PLCTLDIMEITEM]
#define PL_CTL_PANO				menu_sel[PLCTLPAGE][PLCTLPANOITEM]
#define PL_CTL_CW				menu_sel[PLCTLPAGE][PLCTLCWITEM]

#define SPK_FRONT_SIZE			menu_sel[SPKSPAGE][FRITEM]
#define SPK_CENTER_SIZE			menu_sel[SPKSPAGE][CENTERITEM]
#define SPK_SUBW_SIZE			menu_sel[SPKSPAGE][SUBWITEM]
#define SPK_SURR_SIZE			menu_sel[SPKSPAGE][SURRITEM]
#define SPK_BACK_SURR_SIZE		menu_sel[SPKSPAGE][BACKSURRITEM]

#define SPK_DIST_FR				menu_sel[DISTANCEPAGE][FRITEM]
#define SPK_DIST_CETNER			menu_sel[DISTANCEPAGE][CENTERITEM]
#define SPK_DIST_SURR			menu_sel[DISTANCEPAGE][DISSURRITEM]


#define LANG_PLAYER_MENU		menu_sel[LANGUAGEPAGE][PLAYERMENUITEM]
#define LANG_DISCMENU			menu_sel[LANGUAGEPAGE][DISCMENUITEM]
#define LANG_AUDIO				menu_sel[LANGUAGEPAGE][AUDIOITEM]
#define LANG_SUBTITLE			menu_sel[LANGUAGEPAGE][SUBTITLEITEM]



#define SPK_FRONT_VOL					menu_sel[VOLPAGE][FRONT_SPK_ID]
#define SPK_CENTER_VOL					menu_sel[VOLPAGE][CENTER_SPK_ID]
#define SPK_SW_VOL						menu_sel[VOLPAGE][SW_SPK_ID]
#define SPK_SURR_VOL					menu_sel[VOLPAGE][SURR_SPK_ID]



//for distance setup
#define SPK_DISTANCE_MIN		3
#define SPK_DISTANCE_MAX		20
#define SPK_DISTANCE_STEP		1
//for volume setup
#define SPK_VOL_MIN				-12
#define SPK_VOL_MAX		 		8
#define SPK_VOL_STEP			1

//sel value define

#define VIDEO_SCART				4
#define PSCAN_OFF				2
#define TV_FORMAT_PAL			2
#define TV_FORMAT_NTSC			3
#define STEREO_ON				2
#define DIGIT_DOBLY				2
#define DIGIT_DTS				3
//for TV ratio
#define RATIO_4_3_LB			2
#define RATIO_4_3_STAND			3
#define RATIO_16_9				4
//for speakers
//for sel
#define NONE_SPEAKER			2
#define SPEAKER_SMALL			3
#define SPEAKER_LARGE			4			

//PL II mode
#define PL_MODE_PROLOGIC        2
#define PL_MODE_VIRTUAL         3
#define PL_MODE_MUSIC			4
#define PL_MODE_MOVIE           5
#define PL_MODE_MATRIX          6
