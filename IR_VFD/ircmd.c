/*************************************************************
** FILE
** ircmd.c
**
** DESCRIPTION
** splitted from ir.c, now all the IR (or global) functions
** are implemented here.
**
**   Create:   JJ
**   Maintain:   Kenny 2000/09/29
**               Terry 2003.02.24   move file header to ircmd_h.h
**                                  move util code to ircmd_util.c
**                                  move amp. code to ircmd_amp.c
**               Terry 2005.04.07   correct PrintOsdMsg 4th parameter error bug.
****************************************************************/
#include "ircmd_h.h"
#include "gpio.h"
#include "asf_if.h"
#include "lbaif.h"
#include "sinf.h"
#include "timer.h"
#include "Subtitle.h"
#include "user_if.h"   // 2005/06/28 yltseng

#ifdef SUPPORT_CD_RIPPING //qinhua,add 060602
extern  int new_app_state;
#include "fs_new_app.h"
#endif

#include "memmap_I2C.h"
#include "..\setup\setup_VA.h"

#ifdef DISPLAY_CD_TEXT          //lizhx add 2004/09/06
#include "CDTextUtil.h"
#endif

//QiaoHuilin:2005-10-24:
#ifdef MUSTEK_LCD_DRIVE_BITEK
extern void LCD_Show_Volume (BYTE volume);
extern void	LCD_ShowDemuteIcon(void);
extern void LCD_ShowMuteIcon(void);
#endif
////////////////////////////////////////////////////

#ifdef SUPPORT_UNICODE_FONT//2005/9/2 joshua
#include "font_unicode.h"
#endif

#ifdef PMP_UI           ///yangli 2005/7/5
#include "fsNAV_PMP.h"
extern FSNAVUI fsPmp;
#endif

#ifdef SUPPORT_QUICKTIME
#include "QT_if.h"
#endif
#ifdef SUPPORT_OGG
#include "ogg_if.h"
#endif        

#ifdef OP_DVD5121_PANEL  //qinhua ,add 2005-9-5 22:34
BYTE    pressed_flag;
#endif 

#define D   printf("INFO: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);

#ifdef FILE_MODE_WRITE//nono add 20050224
#include "memcfg.h"
#endif//#ifdef FILE_MODE_WRITE

#ifdef SUPPORT_RECEIVER /*2005-6-7 10:42 huziqin*/
#include "e2prom_map.h"
#endif

//#ifdef OP_UI
//#include "menu_func.h"
//#include "infobanner_func.h"
//#include "infobanner_def.h"
//#endif//


#ifdef STOP_LOADER
extern int atapi_standby_mode(void);
#endif

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif

#ifdef USER_LOGO
#include "userlogo.h"
#endif

#ifdef SDRAM_16Mb_Mode
#include "memmap.h"
#include "memmap0.h"
#endif

#ifdef SPHE8202_ALL_TYPE_CARD_WRITE
extern BYTE card_browse_sign;//dingzhy 4-11-18 9:40
#endif

#ifdef SHOW_12_BOOKMARK//libing 2005-6-29 21:59
extern void cancel_bookmark();
#endif

#ifdef OP_PLAYMODE//libing 2005-9-29 10:53
extern void exit_op_menu(void);
extern void exit_tray_menu(void);
extern void play_mode_cancel(void);
#endif

//dtb in 20030915
#ifdef SUPPORT_MIDI
#include "fsmidi.h"
#ifdef SUPPORT_MIDI_MENU_SEL
#include "fsMidiUI.h"
#endif
#endif

#if(defined(SUPPORT_ID3) || defined(SUPPORT_OSDID3))
#include "fs_show.h"
#endif

#ifdef SUPPORT_MP4
//#include "drm.h"
    #ifdef DIVX_DRM
    #include "DRM_UI.h"
    #include "drm.h"
    #endif

#include "avi_if.h"

#endif

#ifdef SUPPORT_TVG
#include "TVGApp.h"
#endif

#ifdef SUPPORT_MULTI_PARTITION//liweihua 2004-11-2 20:45
#include "playmode.h"
#endif

#ifdef SUPPORT_8202_DVB     //Maoyong 2004-10-19 14:32
#include "..\dvb_h\sp_dtv.h"
#include "..\dvb_h\dvb_simgr.h"
#ifdef SUPPORT_DVB_PREVIEW_9FRAMES
extern UINT8 dvb_preview_state;
extern UINT8 DvbPreviewNavigationFirstFlag;
extern UINT8 DvbPreviewSlideShowFinish;
extern void dvb_preview_navigation(void);
extern void DvbDvdSwitch(void);
#endif
#endif
#ifdef POWER_OFF_ONLY_VIDEO_DAC_OFF     //2005-01-13 wjzhang ,fix the power un sync bug for twinhan
#include "../driver/message.h"
#endif

#ifdef SPHE8202_CARD_STORAGE    //dingzhy 05-3-22 10:48
#include "card_main.h"
#endif

#ifdef SHUFFLE_ACCOMPLISH_BY_ARITHMETIC
#include "shuffle_new.c"
 #endif

#ifdef DISP_TIME_AFTER_STATE
int vfd_disp_ab_flag;
int vfd_disp_rep_flag;
int vfd_disp_mute_flag;
//int vfd_disp_play_flag;
#endif
#ifdef VOL_LED//HIMAGE1251
BYTE nLed_index=0;
#endif

#ifdef  UPGRADE_TRAYOUT //joshua add    04-07-13
extern  int trayout_flag;
#endif

#ifdef ONLY_SOUND_FIELD_KEY//zhaoyanhua add 03-10-29 15:37
#include "dsp3_if.h"
#define MAX_PAGE_ITEM   4
#define MAX_ITEM_SEL    11
BYTE surround_type = 0;
extern  const UINT8 sound_item[MAX_PAGE_ITEM][MAX_ITEM_SEL];//include in sound.c
#endif

#if defined(ONLY_EQ_KEY)||defined(SUPPORT_RECEIVER_EQ)//chenzhao20051017//zhaoyanhua add 03-10-29 15:34
#include "dsp3_if.h"
#define MAX_PAGE_ITEM_S   4
#define MAX_ITEM_SEL_S    11
#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ
#define MAX_BAND    5
#else
#define MAX_BAND        7
#endif
#define MAX_MUSIC       7
BYTE EQ_type = 0;
extern  const UINT8 sound_item[MAX_PAGE_ITEM_S][MAX_ITEM_SEL_S];//include in sound.c
extern  const UINT8 music_osd_set[MAX_MUSIC][MAX_BAND];
extern void SettingEqLevel(BYTE *);
extern void SettingEQType(BYTE type);
void SetEQ(void);
#endif

#ifdef SUPPORT_APOGEE_AMP
extern void    ddx_disableEPAD();
extern void    ddx_masterMute(BYTE);
#endif

#if 0//def  CNTR_5SPK_VOLUME
static int tVolumeL,tVolumeR;   //wangfeng 2004-2-9 16:16
#endif

// mimitsai merge from dp2070/dp3240
#ifdef  USER_VERSION_INFORMATION//eastech   
extern  BYTE    custm_count;
extern  BYTE    enter_display_flag;
#endif  //#ifdef  USER_VERSION_INFORMATION

#ifdef SUPPORT_NEXT_PREV_AUTO_PLAY_MP3 //////////yangli add for in filemode next/prev/autoplay function
       extern int auto_play_flag;
       extern int next_flag;
       extern int prev_flag;
#endif
 
#ifdef FILE_MODE_WRITE
extern void FileModeGUI_select(void);
#endif

#ifdef SCORE_IN_PLAYMODE_MENU//libing
extern int score_flag;
#endif 

extern void FSChangeGraphMode(void); // in fsNAV.c

#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
extern void osd_init_newstyle_window_NTSC(void);
extern void osd_init_newstyle_window_PAL(void);
#endif

#ifdef IR_SWITCH_CD_USB_CF_OTHER  //dingzhy 04-10-22
EXTERN  BYTE now_valid_type;
#endif

#ifdef SUPPORT_PROLOGIC_II//zhaoyanhua add 2004-2-11 13:51
extern void setup_OffPrologic_II(void);    //setup_tab.c
extern int setup_IsPrologicOn();    
#endif// ifdef SUPPORT_PROLOGIC_II
   
#ifdef AUDIO_2CH_5_1CH//zhaoyanhua add 03-10-29 15:30
#define AUDIO_2CH  1
#define AUDIO_5_1CH  2
BYTE  ChannelFlag = AUDIO_2CH;
extern void AudioSet2chOutput(void);//setup_tab.c
extern void AudioSet5_1chOutput(void);//setup_tab.c
extern void AudioSetPrologic_IIOutput(void);//setup_tab.c
extern int setup_IsSpkDownmixOff(void);
extern int setup_IsSpkStereo(void);
extern UINT8 setup_GetPrologicII(void);
#endif

#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-24 20:12
BYTE SearchPage = 0;
extern void ShowSearchPage(BYTE page,BYTE need_hi);
#endif

#ifdef HANYANG_LR_CHANGE_PAGE
extern void FSGUI_File2DirArea(void);
#endif

#ifdef SETUP_ON_OPEN_VALID
BYTE OpenFlag=0;    //dingzhy for real open sign
#endif
 
#ifdef OFF_PROLIGIC_WHEN_TURN_KEY//zhaoyanhua add 2003-12-11 11:14
extern UINT8 setup_GetPrologicII(void);
#endif

#ifdef TWO_KEY_SWITCH_TWO_SUBTITLE  //added by wangwei,2004-9-29 13:47
extern void sup_select_subtitles(int n);
extern void sup_select_channel_2(int chn);
int twoSubTTFlag = 0;
int IDTWO = 0;
#endif  //TWO_KEY_SWITCH_TWO_SUBTITLE

#ifdef DYNAMIC_SPECTRUM    //fengjl 3-10-29 20:56
extern BYTE band_onoff;  
#endif

#ifdef NEW_PARENTAL_GUI//zhaoyanhua 2003-11-29 9:40
BYTE one_key_pass_play = 0;
#endif

#ifdef ROTATE_NOT_ZOOM//zhaoyanhua 2003-12-9 16:38
extern UINT8  Is_Rotate_State(void);
#endif

#if defined(SUPPORT_BASS_TREBLE)//xyy 2004-3-8
extern void ddx_ircmd_BassAdjust(int updown);
extern void ddx_ircmd_TrebleAdjust(int updown);
#endif

#ifdef JPEG_THUMBNAIL_MENU  //Maoyong 2004-8-13 20:09
extern BYTE ThunmnailChkValidPrevNext(BYTE rx);
#endif

#ifdef USER_MPEG_LOGO       //maoyong 2004.02.20
extern  BYTE    mpeg_logo_onoff;
#endif

#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 13:54
extern void TestVFDEveryDot(void);
extern BYTE     Test_Stop_flag;
#endif

#ifdef  POLLING_10MS_SAVE_RESUME    //Maoyong 2004.03.01
#define DVD_RSM_WRITE_SIZE  (sizeof(same_disc_vob11_pos) + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeMSF) )
BYTE    rsm_I2c_write_cnt = DVD_RSM_WRITE_SIZE;     
#endif


#ifdef ADD_DVI311_SETUP
extern void close_pll(unsigned char num);
#endif

#ifdef SCALER_6500
extern void SCA_DAC_HDMI_PwDown(void);
#endif

#ifdef MULTIDISC_LOADER  //chenzhao20060111
    #include "multidisc_loader.h"
#endif

#ifndef DVDRELEASE
//#define IRCMD_DBG       1
#endif

#ifndef IRCMD_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif

#include "ircmd_util.c"
#include "rsm_util.h"

#ifdef SUPPORT_REP_READ    //Maoyong 2004.06.07
#include "read.h"
#include "func.h"
#endif

#ifdef  DYNAMIC_SPECTRUM //zhaoyanhua add 03-11-1 15:30
void ClearShowSpectrum(void);
#endif

#ifdef NEWSTYLE_WINDOW
#include "osd_arc.h"
#endif

#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
#include "cardfs.h"
extern CARD_FILE    cardFile;//liweihua 2004-4-5
extern CARD_INFO    cardP;
#if defined(CF_CARD_WRITE) || defined(FAT_Write_UI)//|| defined(WRITE_USB)//liweihua mod 20031219
BYTE Select_Media;
BYTE pressnum_flag;
extern void show_switch(BYTE Select_Media);  //wuxiaofeng
extern void FS_Return2Menu();
//extern void show_switch(void);  //wuxiaofeng
#endif
#endif

#ifdef FAT_FILE_MODE
extern UINT16 fat_play_mode;
extern BYTE mode_menu_id;
#endif

#ifdef SUPPORT_SPI
#include "spi.h"
#endif

#ifdef SUPPORT_RECEIVER  //chenzhao20050620
#include "amp_gui.h"
#endif

/**********************************************************************
for 8104/8202D MP3 encoder
20050824 jslin
**********************************************************************/
#ifdef SUPPORT_MP3_ENCODER
//extern void fs_mp3_encoder_main(void);
extern void stop_current_ripping(void);
#endif
//huziqin removed 2006-4-19

extern int setup_IsSpkDownmixOff(void);
extern void osd_init_prog(void);
extern void sound_init(void);
extern void sound_init_2(void);//wanghaoying 20030910
extern void run_save_total_sel(void);
extern void run_set_variable(void);
extern void run_set_variable(void);
extern void set_default_value(void);
extern void setup_SetPScan(void);
extern void SetIDETimeOut(UINT);    //wanghaoying 2003-8-12 16:08 to declaration
extern void setup_eq_display(UINT8 val);
extern void sound_set_EQ_again(void);//nono 4-7-22 18:09
#ifdef SUPPORT_HD_RESOLUTION
extern void setup_SetHD(void);
#endif

#ifdef NEWSTYLE_WINDOW
extern void browse_DrawRightItem(void);
extern void osd_draw_region_arc(ARC_REGION_LOC *loc_var,BYTE updown);
extern void osd_init_newstyle_window(void);
extern void exe_show_time(void);
extern void osd_draw_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor);
extern void exit_browse_func(void);
//zhaoyanhua add 2003-12-7 19:01
extern void updateAudioLanguage(void);
extern void updateSubtitle(void);
extern void updateRepeatMode(void);
extern void UpdateAngleInfo(void);
#ifdef  CLEAR_KEY_IN_WINDOW         //Maoyong add 2004.02.18
extern void browse_func_clear(void);
#endif
#endif

#ifdef CD_PLAYER        //liweihua add 2003-8-19 20:25
extern void show_cdplayer(void);
extern void osd_init_cdplayer(void);
#endif

#ifdef VIRTUAL_KEYBOARD     //liweihua 2003-9-16
extern void show_virtual_keyboard(void);
extern void hl_keyboard_button(BYTE SelectID);
extern void osd_draw_virtual_keyboard(int xStart, int yStart,BYTE r);
#endif

#ifdef USE_PROLOGIC_II_KEY
//extern BYTE prologic_val;//clead 2003-8-7 
void set_prologic_val(BYTE prologic_mode);
#endif

#ifdef IR_KEY_SET_VIDEO_MODE
extern void set_video_val(BYTE video_mode);
#endif//IR_KEY_SET_VIDEO_MODE

#ifdef CF_GPIO_CONTROL_COLOR
BYTE vfd_color; //wangap 20031031
#endif

#if defined(DISPLAY_REMAIN_TIME) //shawn 0227
int display_and_time=0;
BYTE display_flag = 0;
#endif

#ifdef SUPPORT_MIDI
extern int     iMidiSpeed;
extern UINT16 Is_MIDI_STATE(void);
extern void osd_Clear_Region(BYTE reg, BYTE bkColor);
extern void draw_midi_bitmap_HZnew(const BYTE* pFont, int xStart, int yStart,
                BYTE fontcolor, BYTE bgcolor, BYTE  FigureColor, BYTE FontType,BYTE number);
extern void Disp_TopTip(UINT16 uTimeOut);
#endif


#ifdef DVD_SEQ_PLAY
extern  BYTE   dvd_menu_play;//wanghaoying for warning msg//terry,2002/5/2 04:02PM,new dvd play mode
#endif

#ifdef DOUBLE_TITLE//susu add 2003-8-22 9:03
extern void exe_double_title(void);
extern void exit_double_title(void);
#endif

#ifdef MINUS_VR_AUTH_PLAYBACK
extern INT8		bDVDminusVR;
#endif

#ifdef SPHE1000
extern BYTE from4189;
extern BYTE support_dvb_flag;
#endif

#ifdef DVB_SETUP
extern void SP_SetVolume(UINT8 volume);
#endif

#ifdef EASTWIN
extern UINT8 bINVERTER_POWER , bAMP_IS_ON, bPOWER_ON_MUTE_EXE;
#endif
/*Here deleted by xyy 2004-8-5*/

#if defined(NEXT_FORWARD_IN_A_KEY)||defined(NEW_NEXT_FORWARD_IN_A_KEY)
extern int rep_ir_times;
extern BYTE key_data_flag;
#endif


#ifdef SUPPORT_FILE_CHAPTER
extern UINT32          g_uChapterListAvailable;
#endif //SUPPORT_FILE_CHAPTER

#if defined(SUPPORT_DVB_GUI_NEW)&&(defined(DVB_IR_3D_ON)||defined(DVB_IR_PSCAN_ON))//Jack added 05/07/27
#include "..\dvb_h\dvb_func.h"
extern void DVBMenu_Init(void);
extern BYTE g_CurScreenType;
#endif  

#ifdef REM_JPEG_DECODE_STATE
extern BYTE jpeg_in_decode;
#endif

#ifdef SUPPORT_MP4

#include "irconfig.h"

#ifdef PMP_DVD_ONE_DIR_SELECT //kenny 2005/5/16
extern void pmp_enable_user_flag(UINT32 i);
extern void pmp_disable_user_flag(UINT32 i);//2005/7/12
#endif

int IsUserControlDisabledByTrickyPlay( UINT32 uiKey )
{   // 2004/10/07 yltseng
    if( ( GetCurrentFileType() == CDROM_MP4 ) && ( !file_support_tricky_play() ) &&
        ( ( play_state >= VCD_STATE_NORMAL ) && ( play_state <= VCD_STATE_SLOW ) ) )
    {       
        UINT16 aInvalidKey[] = { 
            IRC_BK_SLOW, IRC_AB, IRC_GOTO
            #ifdef TWO_FUN_IN_ONE_VFD_KEY
            IRC_VFD_NEXT, IRC_VFD_PREV, 
            #endif 
        };

        int i = 0;
        for( ; i <(int)(sizeof( aInvalidKey ) / sizeof( UINT16 )); i++ )
        {
            if( uiKey == aInvalidKey[i] )
                return 1;
        }
    }

    return 0;
}
#endif

/*Marked by maoyong 2004-9-24 9:51
//terry,2004/1/30 03:14PM
void call_full_scrn_fun(IRCMDFUNC *fun)
{
    UINT32 i = 0x01, j;

    for(j = 0; i < FULLOSD_MASK;)
    {
      #ifdef SUPPORT_FUNCTION_MENU
      if((full_scrn & SETUP_PLUS) || (setup_menu_plus_timer))
      {
          fun[2]();
          return;
      }
      else
      #endif //end #ifdef SUPPORT_FUNCTION_MENU
      if(full_scrn & i)
      {
        fun[j]();
        return;
      }
      j++;
      i <<= 1;
    }
}
*/

/*
** IRCMD
*/
UINT32  ircmd_callback_check_generic(UINT32 func)
{
    return func;
}
/*
** FUNCTION
** ircmd_post_func(UINT32 func)
**
** DESCRIPTION
** post a system command.
*/
//static    void    ircmd_post_func(UINT32 func)//kenny 2001/5/16 mark it
void    ircmd_post_func(UINT32 func)
{
    SetIDETimeOut(SHORT_TMOUT);//printf("set srv timeout tm = %d\n",SHORT_TMOUT);//terry,2003/7/17 11:17PM
#ifdef DISP_REGION_BOTTOM// feeling ,these funcs would change the disp region 
    if(func == ( (CMD_FUNC|CMD_FUNC_SELECT) )//these func would cause the display bottom to up, or  up to bottom
            ||(func == (CMD_FUNC|CMD_FUNC_PLAY)) 
            ||(func == (CMD_FUNC|CMD_FUNC_MENU)) 
            ||(func == (CMD_FUNC|CMD_FUNC_STOP)) 
            ||(func == (CMD_FUNC|CMD_FUNC_RETURN)) )
        {

        /*if ((pFsJpeg->ControlArea == CNT_AREA_FILE) && 
            ((pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
                #ifdef SUPPORT_NESGAME
                        || (pFsJpeg->gifsFuncBtn == FS_FUNC_GAME)
                #endif
                #ifdef SUPPORT_FILE_SYSTEM_MODE
                        || (pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER) 
                #endif
                #ifdef SUPPORT_MIDI
                        || (pFsJpeg->gifsFuncBtn==FS_FUNC_MIDI)
                #endif
            ))*/
            {
                    if(t_disp)
                    {
                        osd_init();
                        DispCookOSD0(1);
                    }
                }
            }//end if(func == ( (CMD_FUNC|CMD_FUNC_SELECT) )
#endif    
    if (func)
    {
        if (ircmd_callback_check==NULL)
            ircmd_callback_check = ircmd_callback_check_generic;
        func = ircmd_callback_check(func);
		#ifdef USE_FSGUI_TO_PLAY_CD
		if(cd_type_loaded==CDDA)//frank.huang add 051014
		{
			if((ircmd_callback_check==FSGUI_CmdUp)||(ircmd_callback_check==FSGUI_CmdDown))
				ircmd_callback_check=NULL;
		}
		
		#endif

        #ifdef SUPPORT_MIDI_MENU_SEL   //dtb
        if(gIsMidiSelMenu) //(Is_MIDI_STATE())&&
        {
            //xlluo add for show invaild flag 04-5-9
            extern BYTE bIsShowInvalid; 
            if(bIsShowInvalid==TRUE)
            {
                ir_select_number=0;
                bIsShowInvalid =0;    
                invalid_key();
                show_dvd_err();
            }else if (bIsShowInvalid ==2)
            {//show nothing
                    ir_osd_post_show =0;
                    bIsShowInvalid =0;    
                  return;
            }
           // ;//null      //ouyang 2004.07.31
        } else
        #endif
        if(func==0)
        {
            ir_select_number=0;
            invalid_key();
            show_dvd_err();
        }
    }

    if( (func)&&(!(func&0x20000)) )
    {
        if(cd_type_loaded==CDROM)
        {
        #ifdef VIRTUAL_KEYBOARD  // for cdrom exit keyboard still have effect jiangxl
        	if(full_scrn & KEYBOARD)
        		full_scrn =0;  
        #endif
            e_msf=0;
        }

        #ifdef SUPPORT_WMA
        #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua 2004-9-7 11:27
        if((GetCurrentFileType() == CDROM_WMA) && (media_type == MEDIA_CARD))
            AVD_SetMediaTimeout();
        #endif
        if (GetCurrentFileType() != CDROM_WMA)
        #endif
        {
            #ifdef PMP_UI
            if(pFsJpeg->gifsState == FS_STATE_OTHER&& (func&CMD_FUNC_REPAB))//kenny 2005/7/9
            {
                 //printf("not ircmd_post_func timeout\n");
            }
            else
            {
                
            AVD_SetMediaTimeout();
            //printf("ircmd_post_func timeout\n");
            }
            
            
            #else
            
            #ifdef JPG_OLD_PARSER_FLOW
            AVD_SetMediaTimeout();//terry,2001/6/8 03:15PM ,we wait kernel code finish
            #else
                if (pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG)
                    AVD_SetMediaTimeout();
            #endif    
                        
            #endif
         }   

#ifdef MONE_TIMEOUR_SRC
        printf("ircmd_post_func timeout\n");
#endif
        if(play_state==VCD_STATE_PAUSE){ //Jeff 20011004
            chg2normal_play(PAUSE2NORM,TRANSFER);
        }


        if(!(func&0x10000))
            PostCommand(func);
    }
    SetIDETimeOut(PLAY_TMOUT);//printf("set srv timeout tm = %d\n",PLAY_TMOUT);//terry,2003/7/17 11:17PM
}

//terry,2004/4/6 07:44PM
//void ircmd_sub_picture(void)
#include "ircmd_subtitle.c"

#ifdef NEW_INPUT_MENU
extern void input_str_clear_variable(void);
#endif

#ifdef CNTR_5SPK_VOLUME     //linrc add 2004-10-11 11:02 -->when main volume change,other volume change too
#ifdef CNTR_5SPK_TYPE_2     //but the other volume can change to big sound
inline void Set_5SPK(void)  //ESS is like this type 
{
    if(IS_AUDIF_CODING_MODE_LPCM || IS_AUDIF_CODING_MODE_DTS 
        || IS_AUDIF_CODING_MODE_PCM || IS_AUDIF_CODING_MODE_WMA
        || IS_AUDIF_CODING_MODE_DTSCD)
    {
        AUDIF_Set_Volume(volume_5SPK[0]);//2004AUDDRV AudioSetVolume(volume_5SPK[0]);
    }   
    else  AUDIF_Set_Volume(15);//2004AUDDRV AudioSetVolume(15);  
}
#endif
#endif

#ifdef OP_PLAYMODE
extern int u;
extern int r;//libing for display&OP_MENU 
void exit_op_menu(void);
void play_mode_cancel(void);
void ircmd_mode(void)//libing 2005-4-21 21:25
{
    //  printf("===================ircmd_mode=============\n");
   
   if((play_state==VCD_STATE_STOP)||(system_state==SYSTEM_NODISC))  //hongfeng add 2005-10-24
        {
            invalid_key();
            return;
        } 
   
   
    if(full_scrn & OP_MENU)
    {
        
        exit_op_menu();
        //osd_init();       
    }else
    {                                     
#if 0//SDRAM_16Mb_Mode
        if(play_state==VCD_STATE_STOP)
        {
            if((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))
            {
                if(IsPBCOn())
                {
                    show_op_menu();    
                    SetFullscrnCmdFuncPtr(op_func_up, op_func_down,  op_func_left,
                             op_func_right, op_func_select);
                }
                else
                {
                    invalid_key();
                    return;
                }   
            }   
            else if(resumeMSF)
            {
                show_op_menu();    
                SetFullscrnCmdFuncPtr(op_func_up, op_func_down,  op_func_left,
                         op_func_right, op_func_select);
            }   
            else
            {       
                show_op_menu();    
                SetFullscrnCmdFuncPtr(op_func_up, op_func_down,  op_func_left,
                         op_func_right, op_func_select);
            }
        }
        else
        {
            invalid_key();
        }
#else//#ifdef SDRAM_16Mb_Mode
#ifdef SDRAM_16Mb_Mode
    if((full_scrn==MARK)||(full_scrn==GOTO))
    {
        old_t_disp=t_disp;
        osd_tog_region(0,OSD_OFF);
        DispFadeOut();
        t_disp=0;
        return;  
    }  
if(t_disp==1)//libing for display&OP_MENU  
{
    u=1;
    DispFadeOut();
    r=1;
    //t_disp=1;
}
else if(t_disp==2)
{    
    u=1;
    DispFadeOut();
    r=2;
    //t_disp=2;
}
else
{
    r=0;
    u=0;
} 
#endif 
        if(cd_type_loaded==CDDVD)
        {
            if(is_menu())//dont'n show op_menu when is_menu on DVD disc
            {
                invalid_key();
            }
            else
            {
                show_op_menu();    
                SetFullscrnCmdFuncPtr(op_func_up, op_func_down,  op_func_left,
                         op_func_right, op_func_select);
            }   
        }
        else if((cd_type_loaded==CDVCD20)||(cd_type_loaded==CDVCD10)||(cd_type_loaded==CDSVCD))
        {
            if(!IsPBCOn())
            {
                show_op_menu();    
                SetFullscrnCmdFuncPtr(op_func_up, op_func_down,  op_func_left,
                         op_func_right, op_func_select);
            }
            else
            {
                #ifdef SCORE_IN_PLAYMODE_MENU
                if(Micflag)
            		Show_Op_Menu_When_PBC_On();
            	else	
            	#endif	
                invalid_key();
            }
        }
        else    
        {       
            //if(play_state==VCD_STATE_STOP)
            show_op_menu();    
            SetFullscrnCmdFuncPtr(op_func_up, op_func_down,  op_func_left,
                         op_func_right, op_func_select);
        }
#endif//#ifdef SDRAM_16Mb_Mode
    }
}
#endif//OP_PLAYMODE

void ircmd_angle(void)
{
#ifdef USE_ANGLE_AND_DISPLAY_SHOW_FW_VERSION
    if(play_state==VCD_STATE_OPEN) 
    {
    old_key=IRC_ANGLE;
        return;//shenyj add for display invalid
    }
#endif
#if defined(SUPPORT_FONT_SWITCH_BY_ANGLE)&&defined(PMP_UI)   /////////ADD FOR SAMBOO CHANGE FONT,YANGLI ,2005-10-17 10:56 
    static BYTE font_language=0;
    font_language++;
    if(font_language == FONT_LANG_NUM)
    {
        font_language = 0;
    }
    switch(font_language)
    {
        case 0:
        psprintf(RegionValStr[REGION1], "Central Europe");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1); 
        break;
        case 1:
        psprintf(RegionValStr[REGION1], "Cyrillic");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        break;
        case 2:
        psprintf(RegionValStr[REGION1], "Latin I");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        break;
        case 3:
        psprintf(RegionValStr[REGION1], "Greek");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        break;
        case 4:
        psprintf(RegionValStr[REGION1], "Turkish");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        break;
        case 5:
        psprintf(RegionValStr[REGION1], "Hebrew");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        break;
        case 6:
        psprintf(RegionValStr[REGION1], "Arabic");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        break;
        case 7:
        psprintf(RegionValStr[REGION1], "Baltic");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        break;
        case 8:
        psprintf(RegionValStr[REGION1], "Vietnam");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        break;
        default:
             break; 
    }    
    return;  
    
#endif 
#ifdef SUPPORT_UNICODE_FONT
    osd_fill_region(2, 1);
    coordinate start;
    start.x = 0;
    start.y = 0;   //This is a legacy-formula for back-compatible
            
    uni_subtitle_language++;
    
    if(uni_subtitle_language>3)
    {
        uni_subtitle_language =0;
    }    
    
    printf_w("<uni_subtitle_language=%d>\n",uni_subtitle_language);
    
    if(uni_subtitle_language==0)
    {
        char2uni_translation = char2uni_cp950;
        osd_draw_string(&start, "BIG5", 2, 1, 2, 0);
        osd_tog_region(2, OSD_ON);
    }
    else if(uni_subtitle_language==1)
    {
        char2uni_translation = char2uni_cp949;
        osd_draw_string(&start, "KSC", 2, 1, 2, 0);
        osd_tog_region(2, OSD_ON);
    }
    else if(uni_subtitle_language==2)
    {
        char2uni_translation = char2uni_cp932;
        osd_draw_string(&start, "JIS", 2, 1, 2, 0);
        osd_tog_region(2, OSD_ON);
    }
    else if(uni_subtitle_language==3)
    {
        char2uni_translation = char2uni_cp936;
        osd_draw_string(&start, "GB", 2, 1, 2, 0);
        osd_tog_region(2, OSD_ON);
    }
    
    timeout_osd[2]=OSD_TIMEOUT;
    
    return;
#endif    
     
#ifdef ANGLE_PBC_IN_ONE_KEY//libing 2005-4-21 20:52
if((cd_type_loaded==CDVCD10 ||cd_type_loaded==CDVCD20||cd_type_loaded==CDSVCD))
{
    ircmd_playmode_toggle();
    return;
}
#endif
    
#ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
    #ifdef SUPPORT_FILE_SYSTEM_MODE
    if((cd_type_loaded!=CDDVD) && !Is_OTHER_STATE())
    #else
    if(cd_type_loaded != CDDVD)
    #endif
    {
        ircmd_3dsound();
        return;
    }
#endif
    
#ifdef OP_IR//LIBNIG 2005-7-6 22:02    
#ifdef ANGLE_ROTATE_IN_ONE_KEY//libing 2005-6-28 14:47
if(pFsJpeg->gifsState == FS_STATE_JPEG)
    {
        OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_RIGHT);

        ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R);  
        return; 
    }else 
#endif  
    if(cd_type_loaded==CDROM)
    {   
        invalid_key();
        return;
    }
#endif
    
#ifndef MAKE_ONLY_UPDATE_CODE
//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
//  printf("===================ircmd_angle=============\n");

#ifdef ALCO_8200P_MULTIKEY 
      
    /*
    if(IS_STOP_STATE()
        #ifdef NEED_DIFF_IR_PANEL_KEY
        &&(!(panel_key_flag && (panel_key_flag&(0x01<<0))))
        #endif
      )
    {
       ircmd_prog();
       return; 
    }
    else */
    if((cd_type_loaded!=CDDVD) && (cd_type_loaded!=CDROM))
    {
       invalid_key();
       #ifdef NEED_DIFF_IR_PANEL_KEY
       panel_key_flag = 0;   
#endif
       return; 
    }
    #ifdef NEED_DIFF_IR_PANEL_KEY
    else
        panel_key_flag = 0;   
    #endif
    
#endif//#ifdef ALCO_8200P_MULTIKEY 

#ifdef JPEG_USE_ANGLE_KEY //Jack for Alco 8200 portable
    if(cd_type_loaded == CDROM) //&& ((play_state == VCD_STATE_NORMAL) || (play_state == VCD_STATE_MP3_FILELIST)))
    {
        if(Is_JPEG_SlideMode())
        {
          #ifdef JPG_ROTATE_DELAY
          if(angle_key_timer)
          {
            return;
          }  
          angle_key_timer = DELAY_CNTTT;
          #endif
          
          if(vpp_zoom)
            vpp_zoom = 0;
          
          set_rtc_val(0);
         
          ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R);
          //ircmd_right(); 
          //set_rtc_val(0);
        }
        else
          invalid_key();
          
        return;   
    }
#endif//#ifdef JPEG_USE_ANGLE_KEY //Jack for Alco 8200 portable

#ifdef ANGLE_GOTO_IN_A_KEY
    
    if( (bIrSkipState1!=1) )//2004-5-5 15:16
    {
         bIrSkipState1 = 1;
         rep_ir_times = 0;
         bIrSkipCnt1 = 0;
         return;
    }
    else
    {
         bIrSkipState1 = 0;
         rep_ir_times = 0;
         bIrSkipCnt1 = 0;
    }
#endif//NEXT_FORWARD_IN_A_KEY

#ifdef PROGRAM_ANGLE_IN_ONE_KEY
 if ((cd_type_loaded == CDROM)||(cd_type_loaded == CDVCD10)
    ||(cd_type_loaded == CDVCD20)||(cd_type_loaded == CDSVCD)
     ||(cd_type_loaded == CDDA))
    {
    invalid_key();
    return;
    }
#endif 

#if defined(DIVX_DRM) && !defined(DIVX_DRM_AES_ONLY)
    if( cd_type_loaded == CDROM )
    {
        if( ( play_state == VCD_STATE_MP3_FILELIST )&&(GetCurrentFileType()== CDROM_MP4) )
        {
            osd_divx_drm_display(1,0);
            return;
        }else
        {
            invalid_key();
            return;
        }
    }

#endif  

#ifdef ANGLE_PAGE_DOWN   //zhongshan 050718 action:divx angle for register
     if(( cd_type_loaded == CDROM )&&((play_state == VCD_STATE_MP3_FILELIST)||(Is_MP3_STATE())))
     {
        FSGUI_UpdownFilePage(1);
        return;
     }
#endif

    UINT16 id; 

#ifdef USE_ANGLE_SWITCH_CHANNEL//xyy 2004-8-5 
/*huziqin 2004-4-29.set channel volume*/
#ifdef SUPPORT_APOGEE_AMP
#ifdef DOLBY_AMP_VOLUME_CTRL
    subvol_next_channel();
    return;
#endif  //DOLBY_AMP_VOLUME_CTRL
#endif
#endif

#if defined(FAT_Write_UI)||defined(CF_CARD_WRITE)//||defined(WRITE_USB)//liweihua 2003-10-30 10:30
    if((cd_type_loaded==CDROM)&&(pFsJpeg->ControlArea == CNT_AREA_FILE))
    {
        if (full_scrn & PERIPHERAL)
        {
            #ifdef NEW_INPUT_MENU
            input_str_clear_variable();
            #endif
            
            full_scrn &= (~PERIPHERAL);
            osd_init();
            pressnum_flag=0;
            #ifdef SPHE8202_ALL_TYPE_CARD_WRITE
            card_browse_sign = 1;   //dingzhy
            #endif
        }
        else
        {
            full_scrn |= PERIPHERAL;
            #if defined(SUPPORT_FILE_SYSTEM_MODE)||defined(SUPPORT_MP4)  //sunzhh add 041124
            if(IsOtherStatePlayMode())            
                ircmd_return();
            #endif 
#if defined(FAT_Write_UI)//sunzhh 20041126
            if ((pFsJpeg->gbfsSlide)&& (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))
            {
  
                ircmd_return();
                FSChangeGraphMode();                     
                FS_Return2Menu();

            }                         
#endif
            #if defined(STORAGE_WRITE_GUI)||defined(CARD_WRITE_GUI)            
                if((((detect_type&USB_DEVICE)&&(detect_type&0x1E))   //||((detect_type&CF_CARD_DEVICE!=0)&&(detect_type&0x1C!=0)))&&(media_type == MEDIA_CD))
                #ifdef CARD_SETUP_TYPE_3
                    ||((detect_type&CF_CARD_DEVICE)&&(detect_type&0x1C))
                #endif
               )&&(media_type != MEDIA_CARD)) 
            {
                     show_mediaswitch();
            }
            else
            #endif    
                show_switch(Select_Media);
            //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:54
            SetFullscrnCmdFuncPtr( switch_up, switch_down, switch_left,
                                   switch_right, switch_select);
        }
        return;
    }
#endif

    /*
    #if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)
        #ifdef NEWSTYLE_WINDOW
            if ( (full_scrn&MESSAGE) && (action_click==2) ) // alan, 2003/8/28 05:32PM
                action_click = 0;
            else
        #endif
        action_click = 1; //Jeff 20030506
    #endif
    */
    #if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)
        #ifdef NEWSTYLE_WINDOW
            if ( (full_scrn&MESSAGE) && (action_click==2) )  
                action_click = 0;
            else
        #endif
        action_click = 1; //Jeff 20030506
    #else
        #ifdef NEWSTYLE_WINDOW
            if ( (full_scrn&MESSAGE) && (action_click==2) ) // alan, 2003/8/28 05:32PM
                action_click = 0;
        #endif
    #endif

    if(get_angle_Ns()>1)
    {//terry,2005/4/5 01:58と
    #ifdef NEW_SEARCH_OSD  //yw 021007
        if(key_up_down==0)
            id=Angle_Chg(action_click,-1); //Jeff 20021008
        else
    #endif
            id=Angle_Chg(action_click,1);
    }
    else
    id =0;

    if(id)
    {
//wanghaoying marked 2004-7-13 10:39, for they are the same
//#if defined(MUSTEK_ESS_DVD)||defined(GBM_DVD)
        OSD1000ISP_STATUS(Angle_Chg(0,1), OSDIR_ANGLE);
        PrintOsdMsg(STR_OS_ANGLE|(0x0a<<OSDSTR_ID_TOTL_BIT),REGION1,1|(((Angle_Chg(0,1)-1)<<8)),4);
//#else
//        PrintOsdMsg(STR_OS_ANGLE|(0x0a<<OSDSTR_ID_TOTL_BIT),REGION1,1|(((Angle_Chg(0,1)-1)<<8)),4);
//#endif
    }
    else {
    #ifdef NEWSTYLE_WINDOW
        if(full_scrn&MESSAGE)//xyy 2003-7-29 15:08
            psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_NONE]);
        else
    #endif
     
      #if defined(SUPPORT_MP3_ENCODER)&& defined(ORITRON_HK_DVD )//qinhua,2005-11-9 9:26
         if((cd_type == CDDA) && (detect_type))   
          return;
         else  if (cd_type == CDDA)
         {
            invalid_key();
            return;
         }         
         else
    #endif    
        invalid_key();
    }
    #ifdef NEWSTYLE_WINDOW
        if(full_scrn&MESSAGE)//xyy 2003-7-29 15:08
        UpdateAngleInfo();
#endif //not apogee amplifier
#endif////MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

#ifdef EXIT_KEY
void ircmd_exit(void)
{
    if(full_scrn==SETUP)
    {
        ExitSetupPage(0);
    }
    #ifdef OP_PLAYMODE//libing 2005-4-12 13:23
    else if(full_scrn==OP_MENU)
    {
        exit_op_menu();
    }
    #endif
    else if(full_scrn==PROGRAM)
    {
        prog_cnt = 0; //disable prog function when we enter program page again
        full_scrn = 0;
        prog_func_off();
    }
    else if((full_scrn==SETUP)||(full_scrn==TRAY_PWD))
    {
        exit_tray_menu();
    }   
    #ifdef SUPPORT_SCORE
    else if(full_scrn==SCORE)
    {
    	osd_init();
    	full_scrn = 0;
    	#ifdef SCORE_IN_PLAYMODE_MENU
    	score_flag = 0;
    	#endif
    }	 
    #endif
    else
    {   
        DispFadeOut();
        osd_init();
        full_scrn=0;
    }       
}
#endif//#ifdef EXIT_KEY



#ifndef USE_PROLOGIC_II_KEY_FOR_SURROUND /*2005-6-7 14:38 huziqin*/
#ifdef USE_PROLOGIC_II_KEY      //clead 2003-8-7
void ircmd_prologic(void)
{
    UINT8 id=0;

        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);  // cmhuang, 2003/8/28 11:58PM

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW    // alan, 2003/8/27 11:36AM
    if(action_click)
#endif
        prologic_val++;
    if(prologic_val>2) 
        prologic_val=0;
    
    switch(prologic_val)
    {
    case 0:
        id=STR_OS_PL_MOVIE;
        break;
    case 1:
        id=STR_OS_PL_MUSIC;
        break;
    case 2:
        id=STR_OS_OFF;
        break;
    }

    OSD1000ISP_STATUS(OSDISP_IGNORE, OSDIR_GLOBAL);

    PrintOsdMsg(STR_OS_PROLOGIC|(id<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
    set_prologic_val(prologic_val);
    AUDIF_Demute();//2004AUDDRV AudioDemute();  // cmhuang, 2003/8/28 11:58PM    
}
#endif//#ifdef USE_PROLOGIC_II_KEY      //clead 2003-8-7
#endif //USE_PROLOGIC_II_KEY_FOR_SURROUND


#ifdef IR_KEY_SET_VIDEO_MODE
#ifndef SET_4_VIDEO_MODE
void ircmd_set_video_mode(void)
{
    UINT8 id=0;

    ReadFromI2c(0xa0, VIDEO_MODE_I2C_ADDRESS,(BYTE *)&video_mode_val,1);//CLEAD_VIDEO_MODE

    switch(video_mode_val)
    {
    case 0:
        id=STR_OS_DEFAULT_SETUP;
        break;
    case 1:
        id=STR_OS_STANDARD;
        break;
    case 2:
        id=STR_OS_LIVELY;
        break;
    case 3:
        id=STR_OS_SHOWPLACE;
        break;
    case 4:
        id=STR_OS_BRIGHTNESS;
        break;
    case 5:
        id=STR_OS_MILD;
        break;
    case 6:
        id=STR_OS_RESUME;
        break;
    }

    OSD1000ISP_STATUS(OSDISP_IGNORE, OSDIR_GLOBAL);

    PrintOsdMsg(id,REGION1,1,0);
    set_video_val(video_mode_val);

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if(action_click)
#endif//ADJUSTING_ACTION_VALID_RIGHT_NOW

    video_mode_val++;

    if(video_mode_val>6) video_mode_val=0;

    WriteToI2c(0xa0, VIDEO_MODE_I2C_ADDRESS,(BYTE *)&video_mode_val,1);
}

#else//#ifndef SET_4_VIDEO_MODE
void ircmd_set_video_mode(void)
{
    UINT8 id=0;

    ReadFromI2c(0xa0, VIDEO_MODE_I2C_ADDRESS,(BYTE *)&video_mode_val,1);//CLEAD_VIDEO_MODE

    switch(video_mode_val)
    {
#if 0
    case 0:
        id=STR_OS_DEFAULT_SETUP;
        break;
#endif
    case 0:
        id=STR_OS_STANDARD;
        break;

    case 1:
        id=STR_OS_DYNAMIC;//STR_OS_LIVELY;
        break;
#if 0
    case 3:
        id=STR_OS_SHOWPLACE;
        break;

    case 4:
        id=STR_OS_BRIGHTNESS;
        break;
#endif

    case 2:
        id=STR_OS_MILD;
        break;
    case 3:
        id=STR_OS_MEMORY;//STR_OS_RESUME;
        break;
    }

    OSD1000ISP_STATUS(OSDISP_IGNORE, OSDIR_GLOBAL);

    PrintOsdMsg(id,REGION1,1,0);
    set_video_val(video_mode_val);

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if(action_click)
#endif//ADJUSTING_ACTION_VALID_RIGHT_NOW

    video_mode_val++;

    if(video_mode_val>3) video_mode_val=0;

    WriteToI2c(0xa0, VIDEO_MODE_I2C_ADDRESS,(BYTE *)&video_mode_val,1);
}
#endif//#ifndef SET_4_VIDEO_MODE
#endif//#ifdef IR_KEY_SET_VIDEO_MODE

//void ircmd_audio_language(void);
#include "ircmd_audio.c"

//
#ifdef USER_MPEG_LOGO
//#include "..\\setup\\setup_page.h"//20040217
void ircmd_mpeg_logo(void)
{
         osd_init();//If you saving logo when play mp4,the OSD have a problem. caoh 2005.3.16
#ifdef SUPPORT_MIDI_MENU_SEL    //ouyang add for not ircmd_mpeg_logo in midi2004-10-13 15:16
        if (Is_MIDI_STATE())
        {
        invalid_key();
        return;
        }
#endif

#ifdef JIEKE_MIDI_STATE   //ouyang add for jieke state 2005-1-6 9:43
   if((system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN))
   {
    invalid_key();
      return;
    }
    #endif
//extern UINT8 setup_sel[SysNextPage][MPEG_LOGO_ITEM];//Item number
//    extern UINT8 setup_sel[7][8];   // alan, 2003/9/16 05:03PM
//    extern BYTE   mpeg_logo_onoff;
//nono mark It can add in inv_tbl_nintaus.h 2004-3-8 20:36
#if 0//def MENU_CAPTURE_LOGO_INVALID        //Maoyong 2004.02.20
    if(is_menu()){
        invalid_key();
        return;
    }
    
#endif
    
#ifdef JIEKE_DVD//wangfeng 2003-12-16 16:53    
    if(setup_GetMPEGLogoItem()==2){
//    if(setup_sel[7][2]==2){
        invalid_key();
        return;
    }
    if((full_scrn&SETUP)||(full_scrn&PROGRAM)){
        //invalid_key();
        return;
    }
#endif    
    counter_down = 100;//terry,2003/9/12 03:55PM
    if(pFsJpeg->gifsState == FS_STATE_JPEG)
    {
#if 0//def STOP_LOADER//nono 3-12-4 13:35
        abort_play();
        delay_srv_10ms(100);//nono 3-12-4 13:35
#endif//#ifdef STOP_LOADER//terry,2003/8/23 08:58PM

        OSD1000ISP_STATUS(OSDISP_SAVELOGO, OSDIR_GLOBAL);

        //psprintf(RegionValStr[REGION2], "");//wangfeng 2003/12/12
        PrintOsdMsg(STR_OS_SAVELOGO, REGION2, 1, 0);    
        Save_Mpeg_Logo();
        printf("Save logo...\n");
    }
    else
    {
        watchdog_onoff(0);  // alan, 2003/9/23 03:05PM
        run_pause_setting();

        OSD1000ISP_STATUS(OSDISP_SAVELOGO, OSDIR_GLOBAL);

//      psprintf(RegionValStr[REGION2], "SAVING LOGO...");  // alan, 2003/9/22 02:13PM
        //psprintf(RegionValStr[REGION2], "");//wangfeng 2003/12/12
        PrintOsdMsg(STR_OS_SAVELOGO, REGION2, 1, 0);    

#if 0//def STOP_LOADER//nono 3-12-4 13:32
        abort_play();
#endif//#ifdef STOP_LOADER//terry,2003/8/23 08:58PM
        //delay(2500);
        delay_srv_10ms(250);//nono 3-12-4 13:32
        
        LoadModual(MODUAL_CDROM);
        Save_Mpeg_Logo();
        delay_srv_10ms(100);//terry,2003/9/12 04:33PM
        ircmd_play();
    }

    setup_SetMPEGLogo();

    //exe_setup_function(STR_OS_SELECT_LOGO,STR_OS_DEFAULT_SETUP,0);  // alan, 2003/9/16 05:03PM
//  exe_setup_function(STR_OS_SELECT_LOGO,STR_OS_MPEG_LOGO,0);  //NONO 2004-2-17 17:02
    //setup_sel[7][2]=3;
    //SETUP_MPEG_LOGO=3;//nono 2004-2-17 17:02
//  setup_sel[SysNextPage][MPEG_LOGO_ITEM]=3;
//  run_save_sel_cmd(SysNextPage, MPEG_LOGO_ITEM);//nono 2004-2-17 17:02
    
    counter_down = 10;//terry,2003/9/12 03:55PM
}
#endif
//

/***********************************************/
/*     Kenny add it for selection key          */
/*                                             */
/***********************************************/
void ircmd_select(void)
{
    

#if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) ////kenny add 2005/6/16
if(pFsJpeg->gifsState == FS_STATE_JPEG||pFsJpeg->gifsState == FS_STATE_OTHER)
{
              if(!full_scrn)//kenny 2005/8/3
              return;
              
 }             
#endif
#ifdef OP_STOP_PANEL_DISPLAY//lijd 2005-6-30 11:33
    StopTimes=0;     
#endif           
#ifdef SEL_PLAY_FILE_LIST//libing 2005-5-27 20:48   
    if((pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)&&(pFsJpeg->gifsState == FS_STATE_LIST)&&(full_scrn==0))
    {
        ircmd_play();
        return;
    }
#endif  
    
#ifdef FILE_MODE_WRITE //lijd 2005-1-5 19:22
if(pFsJpeg->gifsState  ==  FS_STATE_MEDIA)
{
    FileModeGUI_select();
        return;
        }
#endif

#ifdef SUPPORT_NEXT_PREV_AUTO_PLAY_MP3  //////////////////yangli add for in filemode next/prev/autoplay function
        auto_play_flag=1;
#endif
#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif
    #ifdef MOVE_HIGH_LIGHT_IN_PROG_MODE
    if((!full_scrn)&&(cd_type_loaded== CDROM)){     //wsf  2004-7-20 14:55  changed for cancel program when select other ,just in CDROM DISC
        if(!Is_OTHER_STATE()){              
            prog_cnt=0;
            prog_func_off();
            prog_func_clear();        
        }
    }
    #endif
#ifdef PROGRAM_SHOW_DISPLAY    //dingzhy    
if ((full_scrn & PROGRAM)&&(t_disp))
            DispFadeOut();
#endif  
    
#ifdef CARD_VCD_DISPLAY_GOTO_FIRST_TIME_PAGE    //liumzh 2004-9-4 2:24
  if((pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)&&(media_type==MEDIA_CARD))     
  {
   remain = 0;
  }
#endif

    #ifdef IRCMD_DBG
    printf("=================================ircmd_select========================\n");
#endif
	if((UOP_check(UOP_ST_OFF))&&(!is_menu()))//zhangyu add for FLLC and xiaolaosu dvd  20060323
	{
		invalid_key();
        return;
	}

//lyc add 2006-1-9 for NERO DIGITAL GOTO 
#if defined(SUPPORT_GOTO_NERODIGITAL)&&defined(SUPPORT_NERODIGITAL)
	 if(((IS_FILE_TYPE_QT())||(IS_FILE_TYPE_ND()))&&(pFsJpeg->g_uiFileChangeChapter == 3))
        {
        	if(index_x<5)
        	 pFsJpeg->g_uiFileChangeChapter = 4;
        	else
        	{    		
            #if defined(SUPPORT_MP4)
             extern UINT32 nGotoPck;
            #endif
        		 goto_time=(goto_hour*3600+goto_min*60+goto_sec);
        		 nGotoPck = goto_time;
        		 pFsJpeg->g_uiFileChangeChapter = FALSE;
          }	
          //pFsJpeg->g_uiCurChapter = dvd_title-1;
          cancel_disp_mode();
          return;
        } 
#endif

#ifndef IR_10_PLUS
    //printf("now_num_ns:%x\n",now_num_ns);
    if(now_num_ns)
    {
        ir_num_select(ir_select_number);
    }else
#endif

#ifdef IR_10_PLUS 
//printf_w("ir_10p:%d, ir_select_number:%d, now_num_ns:%d\n",ir_10p,ir_select_number,now_num_ns); 
if(ir_select_number!=0 && ir_10p==1) // mimitsai add for clear 10_plus num 
    ir_select_number=0; 
#endif 


//#ifdef USER_MPEG_LOGO

//  if(pFsJpeg->gifsState == FS_STATE_JPEG)
//  {
//      Save_Mpeg_Logo();
//      printf("Save logo...\n");
//      return;
//  }
//#endif
    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn || setup_menu_plus_timer)
    #else
    if(full_scrn

    #ifdef GPS_DVD//frank.huang 050801
    &&(full_scrn!=TOUCH_MENU)&&(full_scrn!=TOUCH_KEYBOARD)
    #endif

    )
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    {
        //call_full_scrn_fun((IRCMDFUNC *)ircmd_select_table);
        ircmd_full_scrn_select();   //Maoyong marked above line and chg 2004-9-24 11:02
        #ifdef PMP_DVD //kenny 2005/7/27
        return;
        #endif
        //terry,2002/6/17 11:06PM
        //panasonic test disc, title 8 ,hl select on pasue stae
        //prohibit it!!
    }
    else if( (HL_exist)&&(!is_dvd_prohibit_key())&&(play_state!=VCD_STATE_PAUSE) )
    {//terry,2002/5/22 07:10PM,
        ircmd_post_func(CMD_FUNC|CMD_FUNC_SELECT);

        //3-12-9 19:04 NONO MARKED.uopdate dsp code.
        //setup_SetDTSDOWNMIXConfig();//NONO force set downmix 2003-11-24 14:23
        //terry,2002/6/3 10:38AM
        //bug:Press select 2nd times quickly on Panasonic's menu
        //Sol:Waiting for new vobu data
        if(IsAVDMediaTimeout())
            HL_exist=0;
    }
#ifdef ENABLE_SELECT_IN_FF_FB_SLOW//tianye 200607

   else if((play_state==VCD_STATE_SLOW)||(play_state==VCD_STATE_PAUSE)||
            (play_state==VCD_STATE_FASTBACKWARD)||(play_state==VCD_STATE_FASTFORWARD)
            ||(play_state==VCD_STATE_STOP))  //alex, Linkconcept. 20030219
    {
   
            ircmd_play_resume();
	     return;
    }
#endif//end=> #ifdef ENABLE_SELECT_IN_FF_FB_SLOW



 else if ( cd_type_loaded == CDROM ) //Jeff 20010802
    {
        #ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
        if((play_state==VCD_STATE_PAUSE) && (pFsJpeg->ControlArea<=CNT_AREA_DIR))
        #else
        if( play_state == VCD_STATE_PAUSE )//nono 2003-9-12 10:07
        #endif
        {
          #ifdef SUPPORT_MIDI  //ouyang 2004-8-16 11:00  first enter "pause" then "select",lyric stop 
             if((midiState == MIDI_STATE_PAYLOAD)||(gIsMidiSelMenu)) 
                ircmd_play();            
          #endif     
            chg2normal_play( PAUSE2NORM, REALPLAY );
        }
#ifdef ZOOM_DIRECT_STOP_SLIDE       //wanghaoying 2003-08-25 21:56
        else if(Is_JPEG_PLAY_STATE())
        {
            jpg_slide_time = JPEG_SLIDE_TIME;
/*
            // marked by Robert 031021.
            if(vpp_zoom!=0)
            {
                vpp_zoom = 0;
                show_zoom(1);
            }
*/
            ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY);
        }
#endif  // 2004/04/16 yltseng, in order to prevent showing "Invalid Key" when Pause -> Select
        else
        {
            #ifdef EASTWIN_PORTABLE_DVD
            if( (cd_type_loaded==CDROM )&&( Is_MP3_STATE()) )//tulijuan040907 from other states back not FF/FR
            {
                adv_search_time = 0;
                play_state = VCD_STATE_NORMAL;
            }
            #endif  
            
            #ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
            if((play_state==VCD_STATE_PAUSE) && (pFsJpeg->ControlArea>CNT_AREA_DIR))
                chg2normal_play(PAUSE2NORM, REALPLAY);
            #endif
            
            #ifdef SELECT_INVALID_WHEN_IN_JPEGBOTTON
            if(Is_JPEG_STATE() && (pFsJpeg->ControlArea==CNT_AREA_JPEGBUTTON))
                invalid_key();
            else
            #endif
            ircmd_post_func(CMD_FUNC|CMD_FUNC_SELECT);  //Jeff 20010814
        }

    }
	#ifdef USE_FSGUI_TO_PLAY_CD//frank.huang add 051014
	else if(cd_type_loaded == CDDA)
	{
		extern UINT8 enable_polling_fsgui;
            {
                FSGUI_CmdEnter();
				enable_polling_fsgui=0;
				FSGUI_Refresh();
			}
            return;
	
	}
	#endif
	else if( psd_state==(PSD_SEL_LIST|PSD_PLAY_SEG) )
    {
        #ifdef CONTINUOUS_NUM_KEY_SELECT//Jack added 04/11/13
        ircmd_post_func(CMD_SELECT | (1));  
        #else
        //ircmd_1();
        ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY);//axel for correcting commands for PSD_Nav 2005/4/8 
        #endif
    }else if( (play_state==VCD_STATE_PREVIEW) ||(play_state==VCD_STATE_9FRAMES) )
    {
        ircmd_play();
    }else if( (cd_type_loaded==CDDVD)&& (play_state!=VCD_STATE_STOP)&&still_timer )
    {
        AVD_SetMediaTimeout();
        timeout_playback=0;
#ifdef  VALID_SELECT_IN_SOME_MODES
    }else if((play_state==VCD_STATE_SLOW)||(play_state==VCD_STATE_PAUSE)||
            (play_state==VCD_STATE_FASTBACKWARD)||(play_state==VCD_STATE_FASTFORWARD))  //alex, Linkconcept. 20030219
    {
            ircmd_play();
    }else if(play_state==VCD_STATE_STOP)   //alex, Linkconcept. 20030219
    {
            ircmd_resume();
#endif                  
    }
#ifdef MINUS_VR_AUTH_PLAYBACK
	else if(bDVDminusVR&& (play_state == VCD_STATE_MP3_FILELIST))
	{
		ircmd_post_func(CMD_FUNC | CMD_FUNC_SELECT);
	}
	
#endif

   #ifdef SUPPORT_MULTI_PARTITION//liweihua mod 2004-11-2 21:46
   if(!(full_scrn&SETUP))//kenny 2005/6/27
   {
    if((pFsJpeg->gifsState == FS_STATE_HDD)
        #ifdef FAT_FILE_MODE
        ||(pFsJpeg->gifsState == FS_STATE_MODE)
        ||(fat_play_mode == 1)
        #endif
        )
    {
        #if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) ////kenny add 2005/6/16
         
         pmp_enable_user_flag(PMP_USER_PRESS_SELECT_KEY);
    #endif

        HDDCard_select();
            return;
    }
    }//if(!(full_scrn&SETUP))
    #endif

    else
//#ifndef USER_MPEG_LOGO
        invalid_key();
//#else
//          {
//
//              run_pause_setting();
//              LoadModual(MODUAL_CDROM);
//              Save_Mpeg_Logo();
//              ircmd_play();
//          }

//#endif
            /* alan marked 02-05-13 */
            //if( (RegionOnOff[1][2]==STR_OS_NO)&&(timeout_osd[1])&&IsAVDMediaTimeout() )
            //{//terry,cls invalid osd msg , 0511
            //  timeout_osd[1]=1;
            //}
}



void ircmd_title_menu(void)
{
#ifdef VCD_TITLE_RETURN          //jwk add for eastech
if(((cd_type_loaded == CDVCD20)||(cd_type_loaded == CDSVCD))&&(IsPBCOn())&&(play_state ==VCD_STATE_NORMAL))
	{
	ircmd_return();
      return;
      }
if(((cd_type_loaded == CDVCD20)||(cd_type_loaded == CDSVCD))&&(!IsPBCOn()))
       {
                 invalid_key();
			return;
		}
#endif
#ifdef TITLE_RETURN_IN_A_KEY //ZXB 2006-3-20 22:54
    if(cd_type_loaded == CDROM)
    {
    	invalid_key();
    	return;	
    }
#endif
#ifdef  VCD_TITLE_INVALID_KEY//tianye 200607
	if((cd_type_loaded == CDVCD20)||(cd_type_loaded == CDSVCD))
       {
                 invalid_key();
			return;
	}
#endif//#ifdef  VCD_TITLE_INVALID_KEY

    #ifdef OP_IR//LIBING 2005-7-6 21:57
     #ifdef OP_GOTO_WHEN_MENU  //caoh 2005-7-13 20:12
      if(full_scrn&GOTO)
      ircmd_goto();
      #endif    
        
    #ifdef TITLE_RATATE_ONE_KEY//libing 2005-5-27 15:36
    if(pFsJpeg->gifsState == FS_STATE_JPEG)
    {
        OSD1000ISP_STATUS(OSDISP_DIR_ROTATE, OSDIR_RIGHT);

        ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_R);  
        #ifdef ROTATE_DIRECT_STOP_SLIDE//hongfeng add 2005-11-10
        if(Is_JPEG_SlideMode())
            jpg_slide_time = 0xffffffff;
        #endif
        return; 
    }
    else
    #endif
    if(cd_type_loaded==CDROM)
    {   
        invalid_key();
        return;
    }

    #ifdef DISC_MENU_CANCEL_SHUFFLE //hongfeng add 2005-10-19
    if(shuffle_flag)
    {
        shuffle_flag = 0;
        //PrintOsdMsg(STR_OS_RAN_CNL,REGION1,1,0);
    }
    #endif
    #ifdef TITLE_MENU_CANCEL_PROGAM //hongfeng add 2005-10-31
    if((prog_cnt)||(full_scrn & PROGRAM))
        {
        prog_func_clear();
        prog_func_off();                  
        prog_cnt = 0;
        } 
    #endif  
    #endif//#ifdef OP_IR//LIBING 2005-7-6 21:57
    
 
#ifdef ORITRON_HK_DVD    
 if(cd_type_loaded==CDSVCD)   //qinhua,2005-11-1 0:06
  {   
    invalid_key();
    return;
   }
#endif   
 
    
#ifdef PUSH_TITLE_IN_PROGRAM_NO_RESPONSE
    //ZXB2005-4-27 23:35
    if(full_scrn & PROGRAM)
    {       
        return;
        }
#endif  
#ifndef MAKE_ONLY_UPDATE_CODE////MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef SUPPORT_MIDI_MENU_SEL//xlluo for midi title
        if (Is_MIDI_STATE())
        {
        invalid_key();
        return;
        }
#endif
#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif
#ifdef TITLE_PBC_IN_ONE_KEY     //wanghaoying 2003-8-28 2:36 added
    if(cd_type_loaded!=CDDVD)
    {
        ircmd_playmode_toggle();
        return;
    }
#endif
#if defined(USE_TITLEMENU_TO_JPG_RETURN)

#ifdef SUPPORT_FILE_SYSTEM_MODE // nono 20030807
    if( (Is_MP3_STATE())||(Is_OTHER_STATE()) )
#else
    if(Is_MP3_STATE())
#endif
    {
        invalid_key();  
        return;
    }
    
    if(pFsJpeg->gifsState == FS_STATE_JPEG||Is_JPEG_STATE())
    {
        ircmd_return();
    }
    if(Is_JPEG_STATE())
    return;
#endif//USE_TITLEMENU_TO_JPG_RETURN

#if defined(JPG_EFFECT)&&defined(USE_TITLE_KEY_TO_CALL_JPGEFFECT_HELP)&&defined(CALL_JPGEFFECT_HELP)
//  jpeg_use_key_to_call_help();

#ifdef SUPPORT_FILE_SYSTEM_MODE // nono 20030807
    if( (Is_MP3_STATE())||(Is_OTHER_STATE()) )
#else
    if(Is_MP3_STATE())
#endif
    {
        invalid_key();  
        return;
    }
    
#ifdef SUPPORT_GIF//when play GIF pic, cannot display "USE_TITLE_KEY_TO_CALL_JPGEFFECT_HELP "effect ,suqiaoli add 2004-2-27
    if( GetCurrentFileType() == CDROM_GIF)
    {
        invalid_key();
        return;
    }
#endif  
    
    if(pFsJpeg->gifsState == FS_STATE_JPEG||Is_JPEG_STATE())
    {
        if (pFsJpeg->gbfsSlide == 1)
        return;

        Jpg_Show_Usage_Flag=1;
        //ircmd_post_func(CMD_FUNC | CMD_FUNC_PREVIEW);
        Jpg_Show_Usage();
        return;
    }
    if(Is_JPEG_STATE())
    return;
#endif

#ifdef JPG_LOGO // 2004/10/07 yltseng
    if(Is_JPEG_STATE())
    {
        Fetch_Jpg_Logo();
        return;
    }

#endif

#ifdef SUPPORT_MP4              //sunzhh add 2004-9-10
#ifndef TITLE_MENU_RETURN_MP4    //zhongshan add 050718     //lyc 2005/11/13 add for MPG FILE 
if ((GetCurrentFileType() == CDROM_MP4)||((GetCurrentFileType() == CDROM_MPG)))
    {
        invalid_key();
        return;
    }
#else
if ((GetCurrentFileType() == CDROM_MP4)||((GetCurrentFileType() == CDROM_MPG)))
{
        ircmd_return();
        return;
}   
#endif
#endif  

    #if defined(JIEKE_DVD) && defined(DVD_SEQ_PLAY)//add by wangfeng 2003-11-28 18:01
    if((dvd_menu_play==0)&&(cd_type_loaded==CDDVD)){
    invalid_key();  
    }
    else
    #endif

#if defined(USE_TITLE_RESUME)&& !defined(DVD_PRESTOP_SEPARATE_MENU_RESUME_INFO)//2004-6-2 22:48 //chenzhao 2006-9-13 12:43 .
    if(is_menu()==1 && cd_type_loaded==CDDVD && resumeMSF) //chenzhao 2006-6-20 11:16 .Aviod invaild title key when no resume data available.
    {
        ircmd_post_func(CMD_FUNC | CMD_FUNC_RESUME);
        #ifdef RESUME_ANGLE_RESET//aviod after resume some multi-angle disc system reset  hongfeng 2006/4/12
        if(get_angle_Ns()>1)
            pDSV->CurrCell=1;//hongfeng 2005-12-12            
        #endif
        PrintOsdMsg(STR_OS_RESUME, REGION1, 1, 0);//zhangyu add for FLLC 2006-3-20 12:58
        return;
    }
    else
#endif//USE_TITLE_RESUME

    {
    OSD1000ISP_STATUS(OSDISP_TITLE, OSDIR_TITLE);

    PrintOsdMsg(STR_OS_TITLE,REGION1,1,0);
    ircmd_post_func(CMD_FUNC | CMD_FUNC_TITLE);
#ifdef  INVALID_ZOOM_IN_DVD_MENU//XLJ2004-3-26
//cancel zoom when return to short film in DVD menu by pressing title key. heqiang, 2004-4-23 9:52
    ircmd_cancel(C_SHOW | C_PLAY | C_ZOOM);
#endif//INVALID_ZOOM_IN_DVD_MENU    

    }

#if 1//def FUSS_DVD
    if(RegionOnOff[REGION1][2]==STR_OS_TITLE)
    {
        #ifdef IRCMD_DBG
        printf("rep cancel\n");
        #endif

        cancel_rep();
    }
#endif

#ifdef EASTWIN
#if defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua add 20040129
           if((media_type != MEDIA_CARD)&&(cd_type_loaded!=CDDVD ))//tulijuan040909 
                ircmd_9frames();
#else
           ircmd_9frames();//tulijuan
#endif
#endif
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}



#if defined(TAS3001_AMP)||defined(NO_AMP_ONLY_TUNER)
void ircmd_clear(void)
{
    //dvd-6-0 con1 pin2 ddxcs (ca720 pin 112 gpio22 )set high  for power off
    ircmd_power();//2002 0918
    // regs0->gpio_sel|=(3<<0);

    regs0->gpio_out[22/16]|=(1<<(22%16));
    // regs0->gpio_oe[22/16]|=(1<<(22%16));
}
#elif defined(USE_CLEAR_KEY_AS_ONLY_P_SCAN)       //gerry,2004-1-30 20:02
void ircmd_clear(void)
{   
//  printf("-----------P_SCAN---\n");
/*
        //tv_out_id = P_SCAN;
        //if(tv_out_id== P_SCAN) 
               setup_tv_out(TV_SVIDEO);
        //else  
           setup_tv_out(P_SCAN);        
        //setup_tv_out(P_SCAN);
        
        setup_SetPScan();
*/
        extern UINT8 ap_tv_out_id;
        extern const UINT8 tv_out_map[MODE_MAX_PSCAN];
        if(full_scrn&SETUP)
            return;

        if(MODE_MAX_PSCAN==0x02)
        {
            ap_tv_out_id=P_SCAN-1;
        }
        else
        {
            ap_tv_out_id=P_SCAN;            
        }   
        if (ap_tv_out_id>=MODE_MAX_PSCAN) ap_tv_out_id=0;

        tv_out_id=tv_out_map[ap_tv_out_id];
        setup_tv_out(tv_out_id);
        setup_SetPScan();
    
        PrintOsdMsg(STR_OS_P_SCAN_YUV, REGION1, 1, 0);
    }
#else//#elif defined(USE_CLEAR_KEY_AS_ONLY_P_SAN)       //gerry,2004-1-30 20:02
void ircmd_clear(void)
{
    extern UINT8 bMouseDown __attribute__((unused));   //xlluo add for midi 2004.09.24
#ifdef IRCMD_DBG
    printf("================= clear =================\n");
#endif

    if(!full_scrn)
    {
        if(ir_select_number)
        {
            ir_select_number=0;
            osd_tog_region(REGION1, OSD_OFF);
        }else
#ifdef SUPPORT_MIDI//axel for seprate clear function from UP/0 keys 2004/9/4
        if(gIsMidiSelMenu)
        {
            if (!bMouseDown)
            {
                if (MenuState >= MENU_MULTI_INDEX_SEL)
                {
                    extern void MultiSel_DelCurSong(void); //ouyang add 2005.07.04
                    MultiSel_DelCurSong();
                }
                else
        MidiUI_Sel_Clear_OSD();
            }
      #ifdef SUPPORT_MIDIUI_IME
        if(MenuState==MENU_MULTI_INDEX_SEL)
            {
            extern void Ime_RefreshFirstPage(UINT32 uNumKey);  //ouyang add 2005.07.04
            Ime_RefreshFirstPage(0);
            }
      #endif//SUPPORT_MIDIUI_IME
        }else
#endif//SUPPORT_MIDI
        {
            invalid_key();
        }
        return;
    }
    #ifdef CLEAR_KEY_QUIT_CUST_SETUP    // linrc 2004-6-10 21:40
    if((full_scrn&CUSTM)||(full_scrn&SETUP))
    {
       ExitSetupPage(1); 
    }    
    #endif 
#ifdef  SUPPORT_BOOK
    if(full_scrn&MARK)
    {
        book_func_clear();
        return;
    }
    else
#endif
    if(full_scrn&GOTO)
    {
        search_func_clear();
        return;
    }else if(full_scrn&PROGRAM)
    {
//    #ifdef OP_UI//zhaoyanhua add 2004-4-12 15:51
//        prog_func_clear();
//    #else
        prog_func_input(11); //clear
//    #endif
    }
    else if(full_scrn&SETUP)
    {

        #ifdef KONKA_DVD    //clead 20020904
        setup_func_clear();
        #endif

        if(digit_cnt!=0)
            show_password(CLREAR_PASSWD);
    }
    #if defined(CLEAR_KEY_IN_WINDOW) && defined(NEWSTYLE_WINDOW)    //Maoyong 2004.02.18
    else if(full_scrn & MESSAGE)
    {       
        browse_func_clear();
    }
    #endif
}

#endif


//void ircmd_setup(void)
#include "ircmd_setup.c"


void ircmd_karaoke(void)//2-7-6 16:02
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef KARAOKE_USE_IR_CRT

#ifdef SDRAM_16Mb_Mode
    invalid_key();
    return;
#endif

#ifdef ADJUSTING_ACTION_VALID_RIGHT_NOW
    setup_MIC(1);
#elif defined(KARAOKE_MENU)//wangfeng 2003-10-31 11:36
printf("<>:full_scrn=>%d\n",full_scrn);
    if(full_scrn&SETUP)
    return;
    else
    setup_KARAOKE();
printf("<>:full_scrn2=>%d\n",full_scrn);
#else
setup_MIC(action_click);
#endif

#endif// KARAOKE_USE_IR_CRT
#endif
}


void ircmd_bk_slow(void)
{//need to implement
#ifndef MAKE_ONLY_UPDATE_CODE////MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef SUPPORT_MP4  // 2004/07/27 yltseng   
    if( IsUserControlDisabledByTrickyPlay( IRC_BK_SLOW ) )
    {
        invalid_key();
        return;
    }
#endif

#if defined(SUPPORT_SLOWBACKWARD) || defined(SUPPORT_SLOWBACKWARD2) //terry,2005/6/30 07:58と
   if(UOP_check(UOP_BW))//chenzhao add for UOP access restricted 20051229
   {   
       invalid_key();
       return;
   }
   
   if(rep_ab_mode != REPEAT_AB_IDLE)
    {
        invalid_key();
        return;
    }

   //if( (cd_type_loaded!=CDDVD)||PE_DSI_novideo() )
    if(cd_type_loaded!=CDDVD)
    {
        invalid_key();
        return;
    }

    if(pre_slowmotion())
        return;

#ifdef SLOW_BACKWORD_TO_PLAY //caoh 2005-5-27 21:44
if(video_slow>0)
    {
      ircmd_play();
      return;
    }
#endif

#ifdef SF_PLAY_SR
    if(video_slow<0)  //wsf add 040205
    {
        video_slow=0;
      ircmd_play();
      return;
    }
#endif
    //add DVD multiple slow backward, Jeff 20030417
    if (video_slow >= 0) {//zhaoyanhua modify 2003-4-18 15:08
        video_slow = -2;
    } else {

#ifdef FUSS_DVD
        video_slow-=2;
#elif defined(SLOW_FIVE_LEVEL) //caoh 2005-4-21 20:14
    video_slow= video_slow*2;
#else
    video_slow--;
#endif

    }
    #ifdef FUSS_DVD
    if (video_slow >= -8)
    #elif defined(SLOW_FIVE_LEVEL)
    if (video_slow > -33)//caoh 2005-4-21 20:15
    #elif defined(USE_BW_SR)      //zhongshan add for thomson use slowback after pause 050725
     if (video_slow > -6)
    #else
    if (video_slow >= -8)
    #endif
    {
        int idSlow;
     #ifdef USE_BW_SR
     if(video_slow == -2)
        idSlow = (-1) * video_slow;
    if(video_slow == -3)
        idSlow = 4;
    if(video_slow == -4)
        idSlow = 8;
    if(video_slow == -5)
        idSlow = 16;
    #else
        idSlow = (-1) * video_slow;
    #endif
        avd_slow_state(video_slow+1);
        #ifdef ALWAYSE_SHOW_SLOW    //dingzhy for TONIC 
        PrintOsdMsg(STR_OS_SB|(idSlow<<OSDSTR_ID_TOTL_BIT),REGION1,0,7);
        #else
        PrintOsdMsg(STR_OS_SB|(idSlow<<OSDSTR_ID_TOTL_BIT),REGION1,1,7);
        #endif
    }
    else
    {
            video_slow=0;
            ircmd_play();
        }
#endif      //SUPPORT_SLOWBACKWARD
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

void ircmd_reading(void)
{
#ifdef SUPPORT_REP_READ
#ifdef IRCMD_DBG
    printf("============== ircmd_reading ================\n");
#endif
    //if in no volume state not, can't do repeat read
    if(user_mute || (audio_volume == 0) ){
        invalid_key();
        return;
    }
    
    if(full_scrn&READ){
        CancelRead();       
        if(rep_ab_mode == REPEAT_FIND_B)
            ircmd_post_func(CMD_FUNC|CMD_FUNC_REPAB);   
    }else{
        full_scrn=READ;
        ShowReadPage();
        
        //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:19
        SetFullscrnCmdFuncPtr(read_func_up, read_func_down, read_func_left,
                              read_func_right, read_func_select);
    }
#endif  //SUPPORT_REP_READ
}


void ircmd_resume(void)
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef SUPPORT_CDG
        UINT8 cdg=0;

    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DA) && bReadSubChannel )
    {
        cdg=1;

#if defined(CDG_TRACK_RESUME)//||defined(CDG_RESUME_PLAY_TO_TRACK) //CDG_RESUME_PLAY_TO_TRACK use resumeMSF resume.chenzhao 2006-4-20 10:9 .
        if(is_cdg_disc(1) && resumeTRK)
        {
          resumeMSF = 0;
          ir_num_select(resumeTRK);
          resumeTRK = 0;    
          PrintOsdMsg(STR_OS_RESUME,REGION1,2,0);        
          return;
        }
#endif      
          
#ifndef CDG_RESUME_PLAY_TO_TRACK//CDG_RESUME_PLAY_TO_TRACK use resumeMSF resume.chenzhao 2006-4-20 10:9 .
        if ( CDG_IsCDGNow() ) {
#if defined(NEW_STYLE_SETUP)||defined(SDRAM_16Mb_Mode)
        ircmd_play();
#else
            invalid_key();
#endif//NEW_STYLE_SETUP
            return;
        }
#endif
    }
#endif
#ifdef DISABLE_PLAY_AT_DVDREGIONERR   //oujx for tonic
    if(cd_type_loaded==CDDVD)
    if(dvd_error==REGION_ERR)
    {
        invalid_key();
        return;
    }
#endif
    if( resumeMSF == 0 )
    {
#if defined(NEW_STYLE_SETUP)||defined(SDRAM_16Mb_Mode)
        ircmd_play();
#else
        invalid_key();
#endif//NEW_STYLE_SETUP
        return;
    }

    if((cd_type_loaded != CDDA)&&(cd_type_loaded !=CDROM)&&(cd_type_loaded !=CDDVD))
    {
        if(IsPBCOn())
        {
            if ( (pFsJpeg->List.s.header!=LIST_PLAY) && (pFsJpeg->List.s.header!=LIST_SELECTION) )       //Jeff 20020520
            {
                invalid_key();
                return;
            }
        }
    }

#ifdef SUPPORT_CDG
        if(cdg)
    if ( CDG_IsCDGNow() && bReadSubChannel ) {
        CDG_Pause();
    }
#endif

    OSD1000ISP_STATUS(OSDISP_RESUME, OSDIR_GLOBAL);

    //PrintOsdMsg(STR_OS_RESUME,REGION0,2,0);
    PrintOsdMsg(STR_OS_RESUME,REGION1,2,0);
    #if 1//ndef OP_PLAYMODE//libing 2005-4-6 11:32
    cancel_rep();
    #endif

    ircmd_post_func(CMD_FUNC | CMD_FUNC_RESUME);
    if (!user_mute) { //Jeff 20010904
        AUDIF_Demute();//2004AUDDRV AudioDemute();
    }
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

#include "ircmd_num.c" //terry,2004/1/14 02:42PM
#include "ircmd_zoom.c"//terry,2004/1/14 02:40PM
//void ircmd_zoom(void)

#ifdef CF_GPIO_CONTROL_COLOR
#include "ircmd_vfd_gpio.c"
#endif

//void ircmd_up(void)
//void ircmd_down(void)
//void ircmd_left(void)
//void ircmd_right(void)
#include "ircmd_dir.c" //terry,2004/1/30 04:14PM

void pbcoff_init()
{
    if( (cd_type_loaded==CDROM)||(cd_type_loaded==CDDVD) )
        return;

    if(!IsPBCOn())
        return;

    //pbc_black_enable=0;//jhuang 891108
    psd_st.psd_list_id = 0xffff;
    ircmd_callback_check = NULL;

    if((play_state!=VCD_STATE_STOP)&&((psd_state&PSD_PLAY_SEG)!=PSD_PLAY_SEG)&&(timeout_playback==0))
        bPbcOff=1;
    else
        ircmd_post_func(CMD_FUNC | CMD_FUNC_PBC);

    psd_state = 0;
}


void pbcon_init()
{
    psd_st.psd_list_id = 0x0;

    ircmd_cancel(C_SHOW|C_PLAY);

    playmode_sel(CLEAR_ALL); //0-11-17 12:15

    ircmd_post_func(CMD_FUNC | CMD_FUNC_PBC);

    //    DispCookOSD0(1);
}

/*
** playmode.
*/
#ifdef FUSS_DVD
void    ircmd_playmode_toggle(void)
{//pbc on/off
    int id;

#ifdef SUPPORT_MIDI_MENU_SEL
    extern UINT8 gIsMidiSelMenu;

    if((gIsMidiSelMenu)) 
    {
         ircmd_post_func(CMD_FUNC | CMD_FUNC_MENU);
        return ;
    }
#endif

    ircmd_cancel(C_SHOW|C_PLAY);

    if((cd_type_loaded!=CDDVD)&&(action_click))//nono 20020708
    {
        #ifdef IRCMD_DBG
        printf("rep cancel\n");
        #endif

        cancel_rep();
    }

    if(cd_type_loaded!=CDDVD)
    {
        if(action_click)
        {
            if (IsPBCOn())
            {
                disc_st_time = M2I(gettrkmsf(cd_trk_lo_now));
                pbcoff_init();
            }
            else
            {
                shuffle_flag = 0;
                pbcon_init();

                AVD_SetMediaTimeout();
#ifdef MONE_TIMEOUR_SRC
                printf(__FUNCTION__" timeout\n");
#endif
            }
        }

        if (IsPBCOn())
            id=STR_OS_ON;
        else
            id=STR_OS_OFF;

        OSD1000ISP_STATUS(OSDISP_MENUPLAY, OSDIR_MENU);

        //PrintOsdMsg(STR_OS_MENUPLAY|(id<<8),REGION1,1,4);
        PrintOsdMsg(STR_OS_MENUPLAY|(id<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);

    }else
    {

#ifdef ONLY_PBC//nono 20020708
        {
            invalid_key();
            return;
        }
#else
        ircmd_root_menu();      //terry,0508, revise seq.
#endif

    }
}
#else
void ircmd_playmode_toggle(void)
{
    //pbc on/off
    int id;
    
#ifdef MENU_CANCEL_PROG   //yaowh add 2005-3-28 20:52
    if ( (prog_cnt)&&(cd_type_loaded==CDDA)||(prog_cnt)&&(cd_type_loaded==CDROM)
        ||(prog_cnt)&&(cd_type_loaded==CDVCD10)||(prog_cnt)&&(cd_type_loaded==CDVCD20)
        ||(prog_cnt)&&(cd_type_loaded==CDSVCD)||(prog_cnt)&&(cd_type_loaded==CDDVD) )
    {
        prog_cnt=0;
        prog_func_clear();
        prog_func_off();

        PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);
        return;
    }
    
    if ( (cd_type_loaded==CDDA)||(cd_type_loaded==CDVCD10)||(cd_type_loaded==CDDVD) )
    {
        invalid_key();
        return;
    }
#endif  //MENU_CANCEL_PROG
    
#ifdef REPEAT_AB_REPEAT_IN_ONE_EKY
extern int repeat_key;
#endif

#ifdef MENUKEY_INVALID_WHEN_REGION_WRONG
    if(dvd_error == REGION_ERR)
    {
        invalid_key();
        return;
    }
#endif
#ifdef SUPPORT_MIDIDISK_TITLE
    if (bIsPlayMidiTitle)//xlluo for midi title
    {
        invalid_key();
        return;
    }
#endif

#ifdef SUPPORT_MP4              //zhongshan 050718
    #ifdef SUPPORT_DIVX6
    //#include "divx6_if.h"
    extern UINT32	divx6_menu_exist;
    #endif

    #ifndef MENU_RETURN_MP4  //zhongshan 050718 call return funtion for thomson
    if (GetCurrentFileType() == CDROM_MP4)
    {
        #ifdef SUPPORT_DIVX6
        if(divx6_menu_exist)
        {
            ircmd_post_func(CMD_FUNC | CMD_FUNC_MENU);//should flows to divx6 callback
        }
        else
        #endif  //#ifdef SUPPORT_DIVX6
        {
            invalid_key();
        }
        return;
    }
    #else  //defined MENU_RETURN_MP4
    if (GetCurrentFileType() == CDROM_MP4)
    {
        #ifdef SUPPORT_DIVX6
        if(divx6_menu_exist)
        {
            ircmd_post_func(CMD_FUNC | CMD_FUNC_MENU);//should flows to divx6 callback
        }
        else
        #endif  //#ifdef SUPPORT_DIVX6
        {
            ircmd_return();
        }
        return;
    }   
    #endif  //#ifndef MENU_RETURN_MP4
#endif   //#ifdef SUPPORT_MP4

#ifdef INVALID_MENUKEY_WHEN_PROG_PLAY
    if(prog_cnt)                  //hq,for ngailik, 2004-3-6 22:07
    {
        invalid_key();  
        return;
    }    
#endif//INVALID_MENUKEY_WHEN_PROG_PLAY  
#ifdef SUPPORT_MIDI_MENU_SEL
    extern UINT8 gIsMidiSelMenu;

    if((gIsMidiSelMenu)) 
    {
         ircmd_post_func(CMD_FUNC | CMD_FUNC_MENU);
        return ;
    }
#endif

#ifdef MENU_STOP_EXCHANGE        //xulf 2003-12-06 for menu and PBC 2-key.
    if(cd_type_loaded == CDROM) // Added by Robert for JPEG thumbnail previewing mode. 2002/05/07
    {
        if(JPEG_NORMAL_MODE == pFsJpeg->g_nJpegMode)
        { 
            OSD1000ISP_STATUS(OSDISP_MENUPLAY, OSDIR_MENU);

            PrintOsdMsg(STR_OS_MENUPLAY,REGION1,1,0);
            return;
        }
    }
#endif

#if defined(USE_PBC_TO_JPG_RETURN)//add by wangfeng 2003-12-13 10:49

#ifdef SUPPORT_FILE_SYSTEM_MODE // nono 20030807
    if( (Is_MP3_STATE())||(Is_OTHER_STATE()) )
#else
    if(Is_MP3_STATE())
#endif
    {
        invalid_key();  
        return;
    }
    
    //if(pFsJpeg->gifsState == FS_STATE_JPEG||Is_JPEG_STATE())
    if(Is_JPEG_PLAY_STATE()==1)//nono 3-12-17 19:42
    {
        ircmd_return();
#ifdef ALCO_DVD_UI 
        PrintOsdMsg(STR_OS_SPACE,REGION1,1,0);
#endif//ALCO_DVD_UI
    return;
    }
//  if(Is_JPEG_STATE())

#endif//USE_PBC_TO_JPG_RETURN)

#ifdef  INVALID_ZOOM_IN_DVD_MENU//XLJ2004-3-26
//cancel zoom when return to choosing Menu by pressing menu key. heqiang, 2004-4-23 9:52
    ircmd_cancel(C_SHOW | C_PLAY | C_ZOOM);
#else//INVALID_ZOOM_IN_DVD_MENU
    ircmd_cancel(C_SHOW | C_PLAY);
#endif//INVALID_ZOOM_IN_DVD_MENU  

#if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)
    action_click = 1;
#endif

    #if defined(SUPPORT_FILE_SYSTEM_MODE)
    if((cd_type_loaded!=CDDVD)&&(action_click)&&(Is_MP3_STATE()==0)&&(Is_OTHER_STATE()==0)&&(Is_JPEG_STATE()==0) )//nono  edit it  2004-03-01 13:41
    #else
    if((cd_type_loaded!=CDDVD)&&(action_click)&&(Is_MP3_STATE()==0) )//nono 20020708
    #endif//#if defined(SUPPORT_FILE_SYSTEM_MODE)
    #ifdef SKYWORTH_DVD
     if(cd_type_loaded!=CDROM)
    #endif 
    {
        #ifdef IRCMD_DBG
        printf("rep cancel\n");
        #endif

        cancel_rep();
      
    }    

    if (cd_type_loaded == CDROM) // Added by Robert for JPEG thumbnail previewing mode. 2002/05/07
    {
        if (Is_JPEG_STATE())
        {
            #ifdef STOP_2LIST_MENU_2MENU
            if(pFsJpeg->gbfsSlide)
            {
               menu_key_timer = 0x0f;
               ircmd_stop();
               PrintOsdMsg(STR_OS_SPACE,REGION1,1,0);
               menu_key_timer = 0;
               return;
            }
            #endif
            
            #ifdef JPG_OLD_PARSER_FLOW
            ircmd_callback_check = fs_callback_check;
            #endif
            ircmd_post_func(CMD_FUNC | CMD_FUNC_MENU);
        }
        else
            invalid_key();
    }
    else if (cd_type_loaded != CDDVD)
    {
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
        if (action_click)
#endif
        {
            if (IsPBCOn())
            {
                disc_st_time = M2I(gettrkmsf(cd_trk_lo_now));
                pbcoff_init();
            }else
            {
                shuffle_flag = 0;
                pbcon_init();
        #ifdef PBC_ON_NO_REPEAT
          repeat_key=0;
        #endif
                AVD_SetMediaTimeout();
#ifdef MONE_TIMEOUR_SRC
                printf(__FUNCTION__" timeout\n");
#endif
            }
        }

        if (IsPBCOn())
        {
            OSD1000ISP_STATUS(OSDISP_MENUON, OSDIR_MENU);

            id = STR_OS_ON;
        }
        else
        {
            OSD1000ISP_STATUS(OSDISP_MENUOFF, OSDIR_MENU);

            id = STR_OS_OFF;
        }
        //PrintOsdMsg(STR_OS_MENUPLAY | (id << 8), REGION1, 1, 4);
#ifdef VCD_SHOW_PBC_NOT_MENUPLAY
        PrintOsdMsg(STR_OS_PBC | (id << OSDSTR_ID_TOTL_BIT),REGION1,1,4);
#else
        PrintOsdMsg(STR_OS_MENUPLAY | (id << OSDSTR_ID_TOTL_BIT), REGION1, 1, 4);
#endif
    }
    else
    {

//zxb add for when press menu directly jump to dvd menu and show "MENU"
//if JMP2MENUPLAY_DIRECTLY is defined ,only ircmd_root_menu(); will be run.
//2005-4-30 1:06
#if  !defined(DVD_SEQ_PLAY)||defined(JMP2MENUPLAY_DIRECTLY)
#if defined(ONLY_PBC)||defined(SETUP_DONGLI459)//nono 20020708
        {
            invalid_key();      //2-6-18 23:04 for jcg_dvd
            return;
        }
#else
        ircmd_root_menu();      //terry,0508, revise seq.
#endif

#else
        //terry,2002/5/2 04:09PM
        //add new dvd play mode
        //use pbc key to toggle play mode
        UINT32 cmd;

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
        if(action_click)//toggle to on/off
#endif
            dvd_menu_play = (++dvd_menu_play) % 2;

        if(dvd_menu_play)
        {
            id = STR_OS_ON;
            cmd = CMD_FUNC | CMD_FUNC_MENU;
        }
        else
        {
            id = STR_OS_OFF;
            cmd = CMD_FUNC | CMD_FUNC_PLAY;
        }
        //PrintOsdMsg(STR_OS_MENUPLAY | (id << 8), REGION1, 1, 4);

#ifdef VCD_SHOW_PBC_NOT_MENUPLAY
        PrintOsdMsg(STR_OS_PBC | (id << OSDSTR_ID_TOTL_BIT),REGION1,1,4);
#else
{
        OSD1000ISP_STATUS(OSDISP_MENUPLAY, OSDIR_MENU);

        PrintOsdMsg(STR_OS_MENUPLAY | (id << OSDSTR_ID_TOTL_BIT), REGION1, 1, 4);
}
#endif

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
        if(action_click)//toggle to on/off
#endif
        {
            dvd_title = 1;
            dvd_chapter = 1;
            ircmd_post_func(cmd);
        }
#endif
    }
}
#endif

#ifdef DEACTIVATE_PSCAN
extern BYTE    enter_deactivate_pscan;   
extern BYTE    pscan_count;
extern BYTE Pscan_on;
#endif

void ircmd_root_menu(void)
{

#ifdef OP_GOTO_WHEN_MENU  //caoh 2005-7-13 20:13
    if(full_scrn&GOTO)
      ircmd_goto();
#endif
#if defined(DVD_RTN_MENU_RESUME)
printf("=============ircmd_root_menu ZYZYZY=================\n");
    if((pDSV->dMenuPgc_flag == 0)&&(resumeMSF)&&(!full_scrn)&&((play_state==VCD_STATE_STOP)||((cd_type_loaded==CDDVD)&&(is_menu()==1) )) )
    {
        if(pDSV->CurrDomain == VTSM_DOM)
        {
            ircmd_resume();
            return;
        }
    }
#endif   //axel for Philips VTSM menu resume in NF_250, Parental control
         // Only for Philips FLLC special operation
#ifdef MENU_PBC_IN_ONE_KEY//libing for op dvd4110 2005-6-27 15:00
     if((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))
    {
       ircmd_playmode_toggle();
       return;
    }
#endif    
// mimitsai merge from dp2070/dp3240
#ifdef  USER_VERSION_INFORMATION
    if( (play_state==VCD_STATE_OPEN))
    {
            custm_count=0;          
            enter_display_flag=2;
            ClearOsdMsg(2);         
            return;
    }
#endif  //#ifdef  USER_VERSION_INFORMATION
    
#ifdef DEACTIVATE_PSCAN
if((play_state==VCD_STATE_OPEN)&&(Pscan_on==1))
{
   enter_deactivate_pscan=1;
   pscan_count=0;
}
#endif

 #ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif

#ifdef SUPPORT_MP4              
#ifndef ROOT_MENU_RETURN_MP4    //zhongshan  add 050718 for thomson return function
if (GetCurrentFileType() == CDROM_MP4)
    {
        invalid_key();
        return;
    }
#else
if (GetCurrentFileType() == CDROM_MP4)
{
        ircmd_return();
        return;
}   
#endif
#endif  

    #if defined(USE_ROOTMENU_TO_JPG_RETURN)

#if defined(SUPPORT_FILE_SYSTEM_MODE)&&!defined(MENU_RETURN_INONE) // nono 20030807
    if( (Is_MP3_STATE())||(Is_OTHER_STATE()) )
#elif defined(MENU_RETURN_INONE)//nono 4-8-7 3:37 for eastech
    if(Is_MP3_STATE()||(play_state == VCD_STATE_STOP))
#else
    if(Is_MP3_STATE())
#endif
    {
        invalid_key();  
        return;
    }
    
    if(pFsJpeg->gifsState == FS_STATE_JPEG||Is_JPEG_STATE()||Is_OTHER_STATE())  //wsf 0802
    {
        ircmd_return();
        return;    //wsf 0802
    }
    if(Is_JPEG_STATE())
    return;
#endif//USE_TITLEMENU_TO_JPG_RETURN

#ifdef SDRAM_16Mb_Mode              //gerry,2004-4-7 15:00
    if((full_scrn==SETUP)||(full_scrn==PROGRAM))
    {
        invalid_key();
        return;    
    }

#endif//SDRAM_16Mb_Mode

    //printf("1.ROOT MENU\n");
    ircmd_cancel(C_SHOW|C_PLAY);

#ifdef DVD_AUDIO    // alan, 2002/11/13 02:58と
    if ( (cd_type_loaded==CDDVD) && (!dAMG_LSN) )
#else
    if(cd_type_loaded==CDDVD)
#endif
    {


#if defined(USE_MENU_RESUME)&& !defined(DVD_PRESTOP_SEPARATE_MENU_RESUME_INFO)//2004-6-2 22:48 //chenzhao 2006-9-13 12:43 .
        if((is_menu()==1)&&(pDSV->CurrDomain == VTSM_DOM) && resumeMSF) //chenzhao 2006-6-20 11:16 .Aviod invaild menu key when no resume data available.
        {
            ircmd_post_func(CMD_FUNC | CMD_FUNC_RESUME);
            #ifdef RESUME_ANGLE_RESET//aviod after resume some multi-angle disc system reset  hongfeng 2006/4/12
            if(get_angle_Ns()>1)
                pDSV->CurrCell=1;//hongfeng 2005-12-12            
            #endif
            return;
        }
        else
#endif//USE_TITLE_RESUME
        {
        OSD1000ISP_STATUS(OSDISP_MENUPLAY, OSDIR_MENU);

        //terry,0511 , use ir osd post msg
        PrintOsdMsg(STR_OS_MENUPLAY,REGION1,1,0);
        ircmd_post_func(CMD_FUNC | CMD_FUNC_MENU);
        }
    }
#ifdef MENU_STOP_EXCHANGE        //xulf 2003-12-06 for menu and PBC 2-key.
    else if (cd_type_loaded == CDROM) // Added by Robert for JPEG thumbnail previewing mode. 2002/05/07
    {
        if(JPEG_NORMAL_MODE == pFsJpeg->g_nJpegMode)
        { 
            PrintOsdMsg(STR_OS_MENUPLAY,REGION1,1,0);
            return;
        }
        ircmd_playmode_toggle();
    }
#endif

#if 0//def MENU_PBC_IN_ONE_KEY//libing for op dvd4110 2005-6-27 15:00
     else if((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))
    {
       ircmd_playmode_toggle();
    } 
#elif defined(MENU_KEY_DIR_TO_DISC_MENU)//libing 2005-6-29 17:46
     else if((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))//libing 2005-7-5 9:26
    {
        if(IsPBCOn())
         { 
            ircmd_return();
            PrintOsdMsg(STR_OS_MENUPLAY,REGION1,1,0);
            if(RegionOnOff[REGION1][2]==STR_OS_MENUPLAY)
            rep_mode = REPEAT_IDLE;
            return;
         }else{
            invalid_key();
            return;
        }
    }   
#elif defined(MENU_RETURN_INONE) //jacky 2003/12/6 05:04PM
     else if((cd_type_loaded==CDVCD10 ||cd_type_loaded==CDVCD20||cd_type_loaded==CDSVCD)&&(is_menu()==0))
    {
        ircmd_return();
    } 

#endif  


    else
        invalid_key();

#ifdef VCD_SHOW_PBC_NOT_MENUPLAY
    if( (RegionOnOff[REGION1][2]==STR_OS_PBC)||(RegionOnOff[REGION1][2]==STR_OS_MENUPLAY) )//nono 2004-3-9 11:44
#else
    if(RegionOnOff[REGION1][2]==STR_OS_MENUPLAY)
#endif
    {
        //printf("rep cancel\n");
        cancel_rep();
    }
}

/*
** display remain time
*/
void ircmd_remaintime(void)
{
#ifdef IRCMD_DBG
    printf("============================= ircmd_remaintime ==================\n");
#endif

#ifdef REMAIN_TIME//nono 2-7-13 11:27
    #ifdef NO_DISC_TIME
    int max=2;
    #else
    int max=3;
    #endif

#ifndef DISPLAY_REMAIN_TIME//nono 2003-8-11 23:38   
    if (full_scrn!=GOTO) full_scrn=0;  // alan 0429
#endif

//    printf("disp:%d   remain:%d\n",t_disp,remain);
#ifdef DISPLAY_REMAIN_TIME  //shawn 910227
    //  {
    display_and_time++;
    //printf("display_and_time:%d\n",display_and_time);
    //      if(cd_type_loaded==CDDVD)
    //      {
    if(cd_type_loaded==CDROM)
    {
        if(Is_JPEG_STATE())
            max = 0;
        else
            max=1;//nono 2003-7-31 21:12
    }

    if(display_and_time>max)
    {
        #if defined(DVD_DEFAULT_SHOW_TITLE_TIME)//chenzhao 2005-07-18
        if(cd_type_loaded==CDDVD)
            remain= DISC_TIME;
        else
            remain = 0;
        #else 
            remain = 0;
        #endif
#ifdef ALCO_DVD_UI
        osd_tog_region(0,OSD_OFF);
#else 
        DispFadeOut();
#endif
        display_and_time=0;
        remain = 0; t_disp = 0; display_flag = 0;
        #ifdef ALCO_DVD_UI
        polling_clock=0;
        #endif
        return;
    }
    /*      }
    else
    {
    if(display_and_time > 3)
    {
    DispFadeOut();
    display_and_time=0;
    remain = 0; t_disp = 0; display_flag = 0;
    return;
    }
    }
    }
    */
#endif
    #ifdef ALCO_DVD_UI
    polling_clock=1;
    #else
    polling_clock=0;
    #endif

    if(t_disp==0)
    {
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
        if(action_click)//nono 2-7-12 17:11
#endif//ADJUSTING_ACTION_VALID_RIGHT_NOW
            remain++;
    }else
        remain++;

    if (t_disp==0)
    {
        t_disp=1;//terry,2002/7/1 10:59AM
        DispFadeIn();
        //remain=2;
    }  // alan 0428 to solve time don't fade in when power up

    t_disp=1;

    //if(action_click)//nono 2-7-12 17:11
    //remain++;

    if(cd_type_loaded==CDDVD)
        max=4;//3;//nono 2-7-12 17:38
    else if(cd_type_loaded!=CDROM)
        max=4;
    else
        max=2;

    if(remain>=max)        /* alan 2002/6/12 11:30と modified */
        remain=0;
        
    if( remain > NO_REMAIN_TIME )   // yltseng 2004/07/28
        Mp3_kbitrate    = Mp3_kbitrate_PreCalc;
/* wanghaoying marked 2004-7-13 10:40, for no use any more
#ifdef MUSTEK_ESS_DVD  //shawn 910227
    {
        display_and_time++;

        if(display_and_time>2)
        {
            DispFadeOut();
            display_and_time=0;
        }
    }
#endif
*/
#endif
}

void disp_fade_in(void)
{
    if(t_disp==1)
        DispFadeIn();

    DispCookOSD0(1);

#ifdef SDRAM_16Mb_Mode
    //DispPolling(0);   //fade in effect
    DispPolling(3); 
#else//SDRAM_16Mb_Mode
    DispPolling(0);
#endif

}

//___________________________________________//
#ifdef SUPPORT_DISPLAY_MENU
#include "ircmd_DisplayMenu.c" //Jack added for argus portable dvd 04/07/10
#endif//end #ifdef SUPPORT_DISPLAY_MENU
//___________________________________________//

/*
** display time
*/
#if defined(NEW_SEARCH_OSD)

//#ifdef NEW_SEARCH_OSD
// YW 020809 Modify
void ircmd_display(void)
{
    int max_page=1;

#ifdef DISPLAY_PSCAN_IN_A_KEY
    //if(system_state == SYSTEM_OPEN)
    if(CDOpened())
    {
        ircmd_p_scan(); 
        return;    
    }    
#endif

#ifdef INVALID_WHEN_WRONG_REGION
    if(dvd_error==REGION_ERR){
            invalid_key();
            return;
        } 
#ifdef DISABLE_DISPLAY_AT_JPEG
if(pFsJpeg->gbfsPictureCD == 1||Is_JPEG_STATE())
{
    invalid_key();
    return;
}
#endif  
#ifdef DISABLE_DISPLAY_AT_PREVIEW
    if(play_state==VCD_STATE_PREVIEW)
    {
        invalid_key();
        return;
    }
#endif
#endif//#ifdef INVALID_WHEN_WRONG_REGION
#ifdef IRCMD_DBG
    printf("\n =================== display ===================\n");
#endif

    if (( (cd_type_loaded==CDROM)
#ifdef SUPPORT_USB         //sunzhh add 2005-3-16    
    ||(detect_type==USB_DEVICE) 
#endif    
    )&& (Mp3ReadFinish==0) ){ //Jeff 20020614
        invalid_key();
        return;
    }


    if(cd_type_loaded==CDDVD)
    {
#ifndef OSD_Function_Disable
        max_page=3;
#else
        max_page=2;
#endif
    }
    else if((cd_type_loaded==CDDA) || (cd_type_loaded==CDROM))
    {
        max_page=1;
    }
    else
    {
        max_page=2;
    }


    if( (full_scrn==GOTO)||(full_scrn==MARK) )
    {
        t_disp=disp_mode;
        disp_mode=0;
        full_scrn=0;
    }

    t_disp=t_disp%10;
    if( t_disp>=max_page )
    {
//wanghaoying marked 2004-7-13 10:41, for no use any more
//#ifdef MUSTEK_ESS_DVD //shawn 910227
//        {
//            ircmd_remaintime();
//        }
//#else
        DispFadeOut();
//#endif

    }else
    {
        t_disp++;
        disp_fade_in();
    }
}

#else //NEW_SEARCH_OSD

  #ifdef SUPPORT_MIDI
  int displayswitch=0;             //ouyang add for display in midi 04-11-26
  #endif
void ircmd_display(void)
{

    counter_down = 2;  // slow down the speed of switching between the page1 and page2
                                 // of display by delaying the IR key. by robert.chang,2006-09-11

#if defined(SUPPORT_DISPLAY_GOTO)&& defined(DISPLAY_REMAIN_TIME)
	if(full_scrn&GOTO){
		//display_flag++;
		DispFadeOut();
		display_flag = 0;
		full_scrn = 0;
		return;
	}
    if(((display_flag == 5)&&(cd_type_loaded ==CDDVD))\
    ||((cd_type_loaded != CDDVD)&&((display_flag == 4))))	
{
		//printf_w("22chgdisp2goto:%d\n",chgdisp2goto);
		//display_flag = 5;
		DispFadeOut();
		remain = 0; 
		t_disp = 0;
		display_and_time=0;
		ircmd_goto();
		return;
	}
#endif

#ifdef MODIFY_FOR_DISPLAY_DBG//shenyj add for alco 1108
    if(full_scrn == GOTO)
    {
        disp_mode=0;
        polling_clock=0;
        remain = 0; 
        t_disp = 0; 
        display_flag = 0;
        display_and_time=0;
    }
#endif

#ifdef USE_ANGLE_AND_DISPLAY_SHOW_FW_VERSION//shenyj add for alco 1107
    if(play_state==VCD_STATE_OPEN)
    {
        if(old_key==IRC_ANGLE)
        {                 
            #if defined(SM0SM0_STD)||defined(SM1SM1_STD)||defined(PLAY_IN_SUNPLUS_PLATFORM)//shenyj modify2006-8-24 05:03下午
            if(UserSet.P_RCD == 0)
                psprintf(linebuf,"%s9",FWVERSION_STRING_SAM);  
            else 
                psprintf(linebuf,"%s%d",FWVERSION_STRING_SAM,UserSet.P_RCD);  
            #elif defined(SA0SA0_STD)||defined(SA2SA0_STD)||defined(SA3SO2_STD)
            #ifdef TEST_VERSION_ALL_OPEN
            if(1)
            #else
            if(UserSet.P_RCD == 0)
            #endif
                psprintf(linebuf,"%s9",FWVERSION_STRING_SAY);  
            else
                psprintf(linebuf,"%s%d",FWVERSION_STRING_SAY,UserSet.P_RCD);  
            #endif

            strcpy(RegionValStr[REGION0], linebuf);
            PrintOsdMsg(STR_OS_SPACE, REGION0, 5, 1); 
            osd_tog_region(1,OSD_OFF);         //shenyj add for alco 11/15          
            return; 
        }
        else
        {
            invalid_key();
            return;
        }
   }
#endif//#ifdef USE_ANGLE_AND_DISPLAY_SHOW_FW_VERSION//shenyj add for alco 1107

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    if((source_play_mode==USB_PLAY_MODE) || (source_play_mode==CARD_PLAY_MODE))
    {
        if((cd_type_loaded==CDUNKNOWN) || (usb_card_state==SWITCH_TO_USB_BUT_HAS_NO_USB) || (usb_card_state==SWITCH_TO_CARD_BUT_HAS_NO_CARD))
        {
            invalid_key();
        return;    
    }    
    } 
#endif

#ifdef DISPLAY_PSCAN_IN_A_KEY
    //if(system_state == SYSTEM_OPEN)
    if(CDOpened())
    {
        ircmd_p_scan();
        return;    
    }    
#endif

#ifdef STOP_SHOW_SETUP//libing 2005-4-21 20:14
    if((play_state==VCD_STATE_STOP)||(play_state==VCD_STATE_IDLE)||(system_state==SYSTEM_OPEN)||(system_state==SYSTEM_NODISC))
    {
        DispFadeOut();
        #ifdef DVD_5_DISC_RESUME_8202S_1X16//LIJD 2005-4-14 16:50 
        LoadModual(MODUAL_CDROM); 
        #endif
        ircmd_setup();
        return;
    }
#endif  
            
#ifdef SUPPORT_MIDI
//    extern char *DiskRun[3];     //ouyang add for display in midi 04-11-26
   BYTE curRundiskIcon = 0;
#endif
    int max_page=1;

    
    #ifdef SUPPORT_DISPLAY_MENU //Jack added for argus portable dvd 04/07/10
    ircmd_display_menu();
    return;
    #endif//end #ifdef SUPPORT_DISPLAY_MENU

#ifdef DISPLAY_DISPLAY_FW_VERSION //Jack added for Alco Portable
    if(play_state==VCD_STATE_OPEN)
    {
               
                {
                    //printf_w("show FW version!");
                 
                    #if defined(SM0SM0_STD)||defined(SM1SM1_STD)
                    if(UserSet.P_RCD == 0)
                        psprintf(linebuf,"%s9",FWVERSION_STRING_SAM);  
                    else 
                        psprintf(linebuf,"%s%d",FWVERSION_STRING_SAM,UserSet.P_RCD);  
                    #elif defined(SA0SA0_STD)||defined(SA2SA0_STD)||defined(SA3SO2_STD)
                    #ifdef TEST_VERSION_ALL_OPEN
                    if(1)
                    #else
                    if(UserSet.P_RCD == 0)
                    #endif
                        psprintf(linebuf,"%s9",FWVERSION_STRING_SAY);  
                    else
                        psprintf(linebuf,"%s%d",FWVERSION_STRING_SAY,UserSet.P_RCD);  
                    #endif
                   
                    //strcat1(linebuf,RegionValStr[REGION1]);
              strcpy(RegionValStr[REGION1], linebuf);
          PrintOsdMsg(STR_OS_SPACE, REGION1, 5, 1); 
                   
                    return; 
             }
     }
      #endif//#ifdef DISPLAY_DISPLAY_FW_VERSION //Jack added for Alco Portable
    
    #ifdef ANGLE_DISPLAY_SUPER_PASSWARD
    if((play_state==VCD_STATE_OPEN) || (full_scrn&SETUP))
      return;
    #endif

    
#ifdef NEW_DISPLAY_GOTO_OSD
    max_page=2;//unify each type of disc display page as TWO.
#endif

#ifdef SDRAM_16Mb_Mode      //gerry,2004-6-7 21:43
    if(full_scrn==SETUP)
        return;
#endif//SDRAM_16Mb_Mode

    #ifdef PROGRAM_SHOW_DISPLAY  //dingzhy
    if(full_scrn ==PROGRAM)
    {
        return;
}
#endif
        
#ifdef INVALID_WHEN_WRONG_REGION
    if((dvd_error==REGION_ERR)||(play_state == VCD_STATE_PREVIEW)||(play_state == VCD_STATE_9FRAMES))
    {
            invalid_key();          
            return;
        }  
        
#ifdef DISABLE_DISPLAY_AT_JPEG      //liansi for tonic  2004-2-4 14:31
if(cd_type_loaded==CDROM)
if(pFsJpeg->gbfsPictureCD == 1)
{
    invalid_key();
    return;
}
#endif   
#endif//#ifdef INVALID_WHEN_WRONG_REGION

  #ifdef SUPPORT_MIDI
   #if defined(SUNPLUS_DVD)
    //if (bMidiPlayerBoolean) { //Jeff 20031029
        #ifdef SUPPORT_MIDI_MENU_SEL
        if(gIsMidiSelMenu) //xlluo mod for status reset
        {
        #endif                  //ouyang 2004.07.31
	        if(midiState == MIDI_STATE_PAYLOAD){ // dtb 20040109
	            printf("call ircmd_key_up\n\n");
    	        ircmd_key_up();
                return;
	        }else
	        {//xlluo 04-6-15
		        if (audio_key)
		        {
		            printf("audio_key is set to zero\n\n");
			        audio_key  =0;           //ouyang 2004.07.31
			    }
			    printf("now not MIDI_STATE_PAYLOAD \n\n");
            }
        #ifdef SUPPORT_MIDI_MENU_SEL
        }
        if(gIsMidiSelMenu)  return;
        #endif
    #elif defined(SANJING_MIDI_DVD)||defined(SHINCO_DVD) //ouyang add for DISPLAY 2004-11-26 22:18  
        if(gIsMidiSelMenu)
        {
            if(midiState == MIDI_STATE_PAYLOAD){

            if(displayswitch)
                displayswitch=0;
            else
                displayswitch=1;

           if(displayswitch)
            {
            bIsShowProgList = 0;
            osd_Clear_Region(REGION0, 0); 
            }
           else
            {
                bIsShowProgList = 0x1;
                stRingBuffer.uLastDispStaus = 0;
                if (((((UINT16)
                    (stRingBuffer.uInput + PROG_MAX - stRingBuffer.uOutput)) %
                    (PROG_MAX)) >
                    DISP_PROG_MAX) &&
                    (stRingBuffer.uNextPlay != stRingBuffer.uOutput))
                {
                    stRingBuffer.uDispWindowPos = stRingBuffer.uNextPlay - 1;
                }
                else
                {
                    stRingBuffer.uDispWindowPos = stRingBuffer.uOutput;
                }
                DispLine(0, stRingBuffer.uDispWindowPos, 0);
            draw_midi_bitmap_HZnew(DiskRun[curRundiskIcon],10,60, 6, 0, 2, 1, REGION0);
                Disp_TopTip(1);
            }
        }
           return;
      }
         #endif    
#endif//#ifdef SUPPORT_MIDI

#ifdef IRCMD_DBG
    printf("=================== display ===================\n");
#endif

    if ( (cd_type_loaded==CDROM) && (Mp3ReadFinish==0) ) { //Jeff 20020614
        invalid_key();
        return;        
    }
    //nono 2003-11-21 16:59
#if defined(JPG_EFFECT)&&!defined(JPG_EFFECT_ONLY_ROTATE)&&!defined(IR_KODAK_EFFECT_KEY)&&defined(IR_KODAK_EFFECT_KEY_USE_DISPLAY)
        if(Is_JPEG_STATE())
        {
            if (t_disp) 
            {
                DispFadeOut();
                disp_mode=0;     
            }

             if (Is_JPEG_PLAY_STATE())
            {
            if(full_scrn&PROGRAM)//nono 3-12-22 23:24
            {
                prog_func_off();            
            }
            jpeg_effect_toggle();
            return;

            }else
            {
        invalid_key();
        return;
        }       
    }
#endif


#ifdef DISPLAY_REMAIN_TIME
    display_flag++;
    if(display_flag >= 3)
        if((t_disp % 10) >= max_page)
            t_disp++;
#endif

        if( (cd_type_loaded==CDDVD)
#ifndef SVCD_ONLY_SHOW_ONE_DISP_PAGE//libing 2005-7-5 10:42        
        ||(cd_type_loaded==CDSVCD)
#endif        
        #if defined(DISPLAY_MP4_VER_PI) || defined(DISPLAY_MP4_AV_INFO)   //Maoyong 2004.06.29, just for MP4 type file in playing state
        ||( (GetCurrentFileType() == CDROM_MP4) && (pFsJpeg->gifsState == FS_STATE_OTHER) )
        #endif
         )
        {
            max_page=2;
        }
    #ifdef NO_REMAIN_TIME_JPEG_STATE  // kevinmonkey 20050712
        else if(Is_JPEG_STATE())
        {
            max_page=1;
        }
    #endif  //#ifdef NO_REMAIN_TIME_JPEG_STATE
#ifndef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-22 13:32
        if( (full_scrn==GOTO)||(full_scrn==MARK) )
        {
            t_disp=disp_mode;
            disp_mode=0;
            full_scrn=0;
        }
#endif
        //remain = DISC_REMAIN_TIME;
        //printf("disp:%d\n",t_disp);
        t_disp=t_disp%10;
        if( t_disp>=max_page )
        {
#if defined(DISPLAY_REMAIN_TIME)
            {
            #if defined(NO_REMAIN_TIME_MP3_STATE)     //fengjl add 2004-02-06 5:31PM
                if( (Is_MP3_STATE()))   
            #elif defined (CARD_NO_OTHER_STATE_REMAIN_TIME) //axel USB not display remain time while playback video in FSGUI
                if((media_type==MEDIA_CARD) && (Is_OTHER_STATE()))   
                    DispFadeOut();
                else
            #elif defined (NO_REMAIN_TIME_JPEG_STATE) //kevinmonkey 050712 no remain time page when jpeg
                if(Is_JPEG_STATE())
                    DispFadeOut();
                else
            #endif
                //#ifdef DISPLAY_MP4_VER_PI
                //page_flag=0;//wangap add
                //#endif
                ircmd_remaintime();
            }
#else

            OSD1000ISP_STATUS(OSDISP_DIS_OFF, OSDIR_DISPLAY);

            DispFadeOut();
            #ifdef MUSTEK_K100D_MODEL
            old_t_disp=0;  //by justin 2005/11/23  you prees setup and this time lcd  show info.  you will change "old_t_disp"  (ircmd_setup.c)
                                   //so next time ,though  nothing display on lcd ,you press setup twice , info. will show again.
            #endif
#endif

        }else
        {
            t_disp++;

//-----------2004/10/21 wjzhang , sphe1000B(stb-dvd): osd display for osdisp
#ifdef SPHE1000_DVDSTATE_CALLBACK
    switch(t_disp)
    {
        case 0:
            //OSD1000ISP_STATUS(OSDISP_DIS_VFD,OSDIR_DISPLAY);
            //dprintf("<<vfd_display>>\n");
            break;
        case 1:
            OSD1000ISP_STATUS(OSDISP_DIS_FIR,OSDIR_DISPLAY);
            break;
        case 2:
            OSD1000ISP_STATUS(OSDISP_DIS_SED,OSDIR_DISPLAY);
            break;
        default :
            break;
    }
#endif //#ifdef SPHE1000_DVDSTATE_CALLBACK

            disp_fade_in();
    }
}

#endif //NEW_SEARCH_OSD

//terry,2002/5/8 04:47と
//Fuss loader response is slowly , so we must move the tray close to sysyem_sleep
void run_close_tray(UINT8 nStatus)
{
    //check whether CD-ROM door is open, Jeff 20020506
    if (atapi_p_mechanism_status()==ATAPI_DOOR_OPEN) {
        UINT32  iTimeOut=0;
        UINT8   cStatus;

        close_tray(nStatus);
        do {
            cStatus = atapi_p_mechanism_status();
            iTimeOut++;
            delay_srv_10ms(1);
        } while ( (cStatus==ATAPI_DOOR_OPEN) || (iTimeOut > 500) ); // Robert 030630
        //} while ( (cStatus==ATAPI_DOOR_OPEN) || (iTimeOut > 0x00010000) );
    }
    //force to stop atapi
    //atapi_p_start_stop_unit(Immed_1,0);//terry,2003/8/23 08:59PM
    //#define STOP_LOADER            
#ifdef STOP_LOADER//terry,2003/8/23 08:58PM
    drv_standby(); 
#else
    abort_play();            
#endif
    
}


#ifdef BRIGHTNESS_COLOR_KEY
void ircmd_brightness_color(void)
{
    if(BriCol_state == IDLE_STATE)
    {//first time 
      BriCol_timer = dBRICOL_TIMER;
      BriCol_state = BRIGHTNESS_STATE;
      
      //read from 24c02
      ReadFromI2c(I2C_ID_MEMORY, BRIGHTNESS_ADDR,&brightness_value,1);
      
      if(brightness_value > BRI_TOTAL_CLASS)
         brightness_value = BRI_TOTAL_CLASS;
      if(brightness_value < 0)
         brightness_value = 0;
         
      show_level(BRIGHTNESS_PLUS_ID,brightness_value,BRI_TOTAL_CLASS);
      
    }
    else if(BriCol_state == BRIGHTNESS_STATE)
    {//second time 
      BriCol_timer = dBRICOL_TIMER;
      BriCol_state = COLOR_STATE;
      
      //read from 24c02
      ReadFromI2c(I2C_ID_MEMORY, COLOR_ADDR,&color_value,1);
      
      if(color_value > COLOR_TOTAL_CLASS)
         color_value = COLOR_TOTAL_CLASS;
      if(color_value < 1)
         color_value = 1;
      
      show_level(COLOR_PLUS_ID,color_value,COLOR_TOTAL_CLASS);
      
    }
    else if(BriCol_state == COLOR_STATE)
    {//third time
      ClearOsdMsg(1);
      BriCol_timer = 0; 
      BriCol_state = IDLE_STATE;
      
      //******************tell MCU**********************
      
      //write to 24C02
      //WriteToI2c(I2C_ID_MEMORY,BRIGHTNESS_ADDR,&brightness_value,1);
      //WriteToI2c(I2C_ID_MEMORY,COLOR_ADDR,&color_value,1);
    }
}

void BriCol_value_up(void)
{
    if(BriCol_timer)
    {
      BriCol_timer = dBRICOL_TIMER;
    
      if(BriCol_state == BRIGHTNESS_STATE)
      {
        if(brightness_value == BRI_TOTAL_CLASS)
          brightness_value = BRI_TOTAL_CLASS;
        else
          brightness_value++;
        
        show_level(BRIGHTNESS_PLUS_ID,brightness_value,BRI_TOTAL_CLASS);
        
        //******************tell MCU**********************
        WriteToI2c(I2C_ID_MEMORY,BRIGHTNESS_ADDR,&brightness_value,1);
        an2526h_value_change(BRIGHTNESS_ADJ, brightness_value);
        an2526h_send_data();        
      }
      else
      {
        if(color_value == COLOR_TOTAL_CLASS)
          color_value = COLOR_TOTAL_CLASS;
        else
          color_value++;
        
        show_level(COLOR_PLUS_ID,color_value,COLOR_TOTAL_CLASS);
        
        //******************tell MCU**********************
        WriteToI2c(I2C_ID_MEMORY,COLOR_ADDR,&color_value,1);
        an2526h_value_change(COLOR_ADJ, color_value);
        an2526h_send_data();
      }
    }
    else
    {
        invalid_key();
    }
}

void BriCol_value_down(void)
{
    if(BriCol_timer)
    {
      BriCol_timer = dBRICOL_TIMER;
    
      if(BriCol_state == BRIGHTNESS_STATE)
      {
        if(brightness_value == 0)
          brightness_value = 0;
        else
          brightness_value--;
        
        show_level(BRIGHTNESS_PLUS_ID,brightness_value,BRI_TOTAL_CLASS);
        
        //******************tell MCU**********************
        WriteToI2c(I2C_ID_MEMORY,BRIGHTNESS_ADDR,&brightness_value,1);
        an2526h_value_change(BRIGHTNESS_ADJ, brightness_value);
        an2526h_send_data();        
      }
      else
      {
        if(color_value == 1)
          color_value = 1;
        else
          color_value--;
        
        show_level(COLOR_PLUS_ID,color_value,COLOR_TOTAL_CLASS);
        
        //******************tell MCU**********************
        WriteToI2c(I2C_ID_MEMORY,COLOR_ADDR,&color_value,1);
        an2526h_value_change(COLOR_ADJ, color_value);
        an2526h_send_data();        
      }
    }
    else
    {
        invalid_key();
    }
}
#endif //end #ifdef BRIGHTNESS_COLOR_KEY

#ifdef VIEW_MODE_KEY
void ircmd_view_mode(void)
{
    unsigned char view_mode;
    ReadFromI2c(I2C_ID_MEMORY,VIEWMODE_ADDR,&view_mode,1);
        
    if( view_mode == FULL_MODE )                             
    {                                                        
        PrintOsdMsg(STR_OS_VIEW_MODE_NORMAL,REGION2,1,0);    
        view_mode = NORMAL_MODE;                             
        WriteToI2c(I2C_ID_MEMORY,VIEWMODE_ADDR,&view_mode,1); 
        LCD_VIEW_MODE_NORMAL();                              
    }                                                        
    else                                                     
    {                                                        
        PrintOsdMsg(STR_OS_VIEW_MODE_FULL,REGION2,1,0);      
        view_mode = FULL_MODE;                               
        WriteToI2c(I2C_ID_MEMORY,VIEWMODE_ADDR,&view_mode,1);    
        LCD_VIEW_MODE_FULL();                                
    }                                                        
}
#endif

#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11
/*    only for Oritron
when user press power key, the system enter into fake
standby mode, that is to say, stop the servo and turn
off the tv dac. 8200 read the time information from 
PCF8563 via I2C bus. 
*/
void ircmd_power(void)
{
  #if defined(CE2746)||defined(CE2766) //FanGang added 2005-4-28 16:49,solved the noise issue when standby status
  int i;
  WriteI2c(0x6a,0x01,0x07,1);  
  //ircmd_stop();  //zxb 2005-9-14 0:37 maybe no use//power_resume fail, so mark it.
  //for(i = 0; i < 0x2ffffff;i++);
  #endif    
    if (t_disp) {
          DispFadeOut();
          disp_mode=0;
        }
    
    next_mode = current_mode + 1;
    
    if(next_mode == 2)
        next_mode = 0;
    switch_to_clockmode = 1;
    if (current_mode == NORMAL_PLAY_MODE)
    {
        ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
        play_state = VCD_STATE_STOP;
        playmode_sel(CLEAR_ALL);
        //open_tray();
        stop_loader();  
    }
    else
    {
        system_state = SYSTEM_OPEN;
    }

}

#else//#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11

#ifdef SUPPORT_POWER_ON_SLEEP    //oujx for tonic 
BYTE PowerStatus=0;
#endif
//the false power function for the special problem that hardware err power supply can't power on  //zhuyanfeng add 
//use the false power function should define STOP_LOADER at the same time
#ifdef FALSE_POWER//zhuyanfeng 20041008 
BYTE i=0;
BYTE j=1;
#endif

void ircmd_power(void)
{

 #ifdef SUPPORT_MP3_ENCODER //qinhua,20051221
    stop_current_ripping();
    #endif
    
   #ifdef FS_FILE_POWER_RESUME	//qinhua,2006-6-16 01:49下午
     RsmInfo2Flash(0);
   #endif 
    
  #ifdef ORITRON_HK_DVD//lijd 2005-7-13 17:19 
  if(play_state==VCD_STATE_CLOSE)
        return;
  #endif    
    
#ifdef SUPPORT_DVB_TIMER              //SUNZHH ADD 20051025
    int sel = 2;
    WriteToI2c(0xa0, 0xBC+1, (BYTE *) &sel, 1);		  
#endif
    
  #if defined(CE2746)||defined(CE2766) //FanGang added 2005-4-28 16:49,solved the noise issue when standby status
  int i;
  WriteI2c(0x6a,0x01,0x07,1);  
  //ircmd_stop(); //zxb 2005-9-14 0:37 maybe no use//power_resume fail, so mark it.
  //for(i = 0; i < 0x2ffffff;i++);
  #endif
  
#if defined(PORTABLE_DVD)&& defined(SUNPLUS_8202P_DEMOBOARD)
regs0->gpio_out[CTR_GLED_GPIO/16]|= (1 << (CTR_GLED_GPIO % 16));      //CTR_GLED->H,GREEN LED OFF
regs0->gpio_out[DSP_RLED_GPIO/16]&= ~(1 << (DSP_RLED_GPIO % 16));     //DSP_RLED->L,RED LED ON
#endif
/*
#ifdef SUPPORT_EPG //Maoyong 2005.01.14 
    if(change_to_schedule_EPG())
        return;
#endif
*/  
#ifdef FALSE_POWER 
    if(!i)
    {     
      j = 0;
      pFsJpeg->gifsbPreview = 0;     
      DispFadeOut();
      ircmd_stop(); 
      tv_dacoff(TV_DAC_A|TV_DAC_B|TV_DAC_C|TV_DAC_D|TV_DAC_E|TV_DAC_F);
      i = 1;          
      return;
    }    
   else 
    {   
      //InitVar();
      ircmd_trayout();      
      ircmd_trayin();
      tv_dacoff(0);
      ShowTitle();
      PrintOsdMsg(STR_OS_READ,REGION1,0,0);                
      ircmd_play();      
      i = 0;
      return;
    } 
#endif  
#ifdef EASTWIN
    INVERTER_POWER_OFF();
    bINVERTER_POWER = 0;        
    POWER_LED_ON();         
    LCD_POWER_OFF();    
    DISABLE_AMP();  
    bAMP_IS_ON = 0;
    AUDIO_MUTE_ON();        // Kevin Sep 22,04 
    bPOWER_ON_MUTE_EXE = 0; // Kevin Sep 22,04    
#endif
    #ifdef DP30H0_KEY_SCAN
          GPIO_O_SET(PANEL_LED_PLAY, 1);
          GPIO_O_SET(PANEL_LED_POWER, 0);
          GPIO_O_SET(PANEL_LED_CLOCK, 0);
          GPIO_O_SET(IR_LED, 1);
    #endif
  #ifdef DP3240_KEY_SCAN     
          GPIO_O_SET(PLAY_LED_1, 1);     //jwk 2005-8-17 10:27
          #ifdef EAST_3240_POWER_LED     //jwk 2005-8-19 14:39
          GPIO_O_SET(POWER_LED_2, 0);         
          #else
          GPIO_O_SET(POWER_LED_2, 1); 
          #endif       
    #endif
    
    // mimitsai merge from dp2070/dp3240
        #ifdef DP2070_KEY_SCAN
        GPIO_O_SET(PLAY_LED_1, 0);
        GPIO_O_SET(POWERON_LED_0, 1);    
        #endif

#ifdef ADD_DVI311_SETUP
close_pll(0x00);
#endif

#ifdef MTC_DVD_DVB_8202D_6600   /////ADD BY YANGLI,FOR mtc DVB STANDBY2005-12-20 20:45
    GPIO_O_SET(CONTROL_STANDBY_GPIO, 0);
#endif  
/*
** helm for scaler, tvdac, and hdmi power down 050727
** if we don't power down them, the screen will be disturbed.
*/
#ifdef SCALER_6500         
         SCA_DAC_HDMI_PwDown();
#endif
 
/*huziqin 2004-4-29.avoid terible noise!!!*/
#ifdef SUPPORT_APOGEE_AMP
    //printf("power\n");
    ddx_disableEPAD();
        ddx_masterMute(1);
#endif
#ifdef DP2030_SCAN_KEY
    GPIO_O_SET(PANEL_LED_POWER,0);  //POWER
    GPIO_O_SET(PANEL_LED_PLAY,1);   //PLAY  
#endif
#ifdef TONIC_DVD
    #ifdef SUPPORT_VFD_SHOW_P_SCAN  //oujx for tonic
    extern int vfd_intr_timer;
    vfd_intr_timer=0;
    #endif
    write_vfd_led(0xff);
#endif  
#ifdef SKYWORTH_DVD
    GPIO_O_SET(3,1);
    GPIO_O_SET(2,1);
    GPIO_O_SET(4,1);
#endif  
#ifdef SHINCO_DVD
    //wanghaoying 2005-9-15 16:12 add to light the led
    // when standby mode, pull high; or pull low.
    regs0->sft_cfg1 &= ~(0x1 << 3);//GPIO16
    GPIO_M_SET(16,1);
    GPIO_E_SET(16,1);
    GPIO_O_SET(16,1);
#endif 
#ifdef CNTR_5SPK_VOLUME     
    AUDIF_Demute();//2004AUDDRV AudioDemute();//wangfeng 2003-11-10 22:43
#endif

#ifdef VOL_LED
write_vfd_led(0x00);
#endif      
#ifdef POWER_OFF_ONLY_VIDEO_DAC_OFF
    bSleepFlag ^= 1;
#else
    bSleepFlag = 1;
#endif
#ifdef MICO_DVD
    write_vfd_led(0); //chen0625
    bCharTemp01[0]='A'; //chen0627
    bCharTemp01[1]='B'; //chen0627
    write_vfd_led(0); //chen0625
    bCharTemp01[0]='A'; //chen0627
    bCharTemp01[1]='B'; //chen0627
    power_off_state=0; //chen0625
#endif
#ifdef SUPPORT_VIDEO_BUFFER_STANDBY //kenny 2003/5/13
extern void system_wakeup();
    if (bSleepFlag) 
    {
        #ifdef MODIFY_FOR_MONITOR_CHANGE_MUTE//shenyj modify alco 19261 1018
        if((GPIO_I_GET(INT_EXT_VIDEO_GPIO1)+GPIO_I_GET(INT_EXT_VIDEO_GPIO2))==1)
        #endif
            video_buff_power_off();
    }
    else 
    {
        system_wakeup();
        return;
    }
#endif

#ifdef SLEEP_WHEN_POWER_ON
#ifdef AD_TCL//2004-3-31 14:28 lijd
    {
        volatile int *iMagic=(int *)(DATA_RAM_BASE|0x80);
        *iMagic = 0x1234abcd;

         #ifdef YADAI_PT6554_PANNEL
              regs0->gpio_master[4 / 16] |= (0x1 << (4 % 16));
                 regs0->gpio_oe[ 4/16 ] |= (0x1 << (4%16));//output
                 regs0->gpio_out[4/16 ] |= (0x1 << (4%16));
         #endif

    }

#else
    {
        volatile int *iMagic=(int *)(DATA_RAM_BASE|0x90);
        *iMagic = 0x1234abcd;
    }
#endif    
#endif
#ifdef POWER_RESUME
    //terry,2002/6/25 05:22PM
    //power on resume function
    //1.This way can be argue by customer.
    //2.We may use polling to save data. eg.ACER machine.
    //3.If use polling then must revise WriteToI2c function.
        
//  #ifndef SAME_DISC_RESUME        //terry,2003/12/20 06:53PM,move up
    
    #ifndef BBK_DVD     //still has some customer define POWER_RESUME but not need, Maoyong2004.02.20        
    if(system_state != SYSTEM_POWER )
                        
    #ifdef  NINTAUS_POWER_RESUME    //Maoyong 2004.02.20 for NINTAUS    
    {
        if(play_state == VCD_STATE_NORMAL)
        {
            #ifdef DVD_AUDIO        //Not record DVD Audio for NINTAUS
            if( (((cd_type_loaded == CDDVD)&&(dAMG_LSN ==0 ))||(cd_type_loaded != CDDVD))&& 
            (!is_menu()) )      
                RsmInfo2Flash(0);
            #else                       
            if( !is_menu() )
            RsmInfo2Flash(0);
            #endif
        }
    } 
    #else   
   		 #if !defined(DVD_5_DISC_RESUME)&&!defined(STOP_RESUME_DVD_VCD)//lijd 2005-4-19 15:16 ////shenyj add for alco 1950 0303
		 #ifdef SUPPORT_LAST_MEMERY
         if(memery_resumeflag)
         #endif//end=> #ifdef SUPPORT_LAST_MEMERY

            RsmInfo2Flash(0);
         #endif
    #endif  //end #ifdef NINTAUS_POWER_RESUME
    #endif  //end #ifnef BBK_DVD    
//#endif
#endif  //endif POWER_RESUME

/* marked by Robert 030806
#if defined(USE_SBA1_AS_GPIO_MUTE)&&defined(KSD_DVD)
    #ifdef LOW_MUTE
    GPIO_O_SET(15,0);//mute
    #else
    GPIO_O_SET(15,1);//mute
    #endif
#endif
*/
#if defined(SCART_TV_3)&& defined(DESAY_DVD)        //wanghaoying 2003-9-12 11:16
    regs0->gpio_out[18 / 16] |= 0x1 << (18 % 16);       //PIN151
    regs0->gpio_out[14 / 16] |= 0x1 << (14 % 16);       //PIN109
#elif defined(SCART_TV_3)&& defined(SKYWORTH_DVD)
    regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16));       //PIN151
    regs0->gpio_out[14 / 16] |= 0x1 << (14 % 16);       //PIN109
#elif defined(SCART_TV_2)&& defined(THAKRAL_DVD)
    regs0->gpio_out[18 / 16] |= 0x1 << (18 % 16);       //PIN151
    regs0->gpio_out[57 / 16] |= 0x1 << (57 % 16);        //PIN163
    //wanghaoying modified 2004-9-23 12:33, for temp method
    regs0->sft_cfg6 &= ~(0x1 << 4);//PIN109 use as SCART_SW1 gpio14
    regs0->gpio_master[14 / 16] |= (0x1 << (14 % 16));
    regs0->gpio_oe[14/16] |= (0x1<<(14%16));
    regs0->gpio_out[14 / 16] |= 0x1 << (14 % 16);         //PIN109
#elif defined(SCART_TV_2)&&defined(YILI_SCART_TV)
    regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16));       //PIN151
    regs0->gpio_out[4 / 16] |= 0x1 << (4 % 16);       //PIN31 alex, Linkconcept. 20030217
#endif

#ifdef KSD_DVD // for 1606 audio DAC, Robert 030806
    GPIO_MUTE();
#endif

    // for other solution

#ifdef SUPPORT_TUNER

    init_vfd_clear();
    if(system_state!=SYSTEM_POWER)
    {

        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0); //Jeff 20020522
        AUDIF_Set_Stop();//2004AUDDRV AudioSetStop(); //Jeff 20020522

        // disable audio-dac (?by turn off XCK?)
        //dac_turn_off();

#if defined(TUNER_T988)||defined(TUNER_T988A)
        radio_mute(1);
#endif

#ifndef TUNER_USE_GAME_PORT //jinping 2002-7-7 21:39
        //Set UART interface to 10 GPIO when change to tuner status
        // so we can upgrade flash and debug at dvd player status;
        regs0->gpio_sel = regs0->gpio_sel|(0x3<<0);
        // GPIO controller defined in iop.c file.
#endif

        if(system_state>SYSTEM_OPEN)
        {
            AVD_SetMediaTimeout();
            printf(__FUNCTION__" timeout\n");
        }

        reset_sup();
        ircmd_post_func(CMD_FUNC | CMD_FUNC_POWER);
        system_state=SYSTEM_POWER;
        play_state=VCD_STATE_POWER;

    }else
    {
        // disable tv-encoder
        //tv_sleep();
#ifdef TUNER_T988 //kenny
        radio_mute(1);
#endif

        tuner_mute(1);  // mute tuner when power off 2-6-15 10:08

        WaitIopFunRdy(IOP_RDY_WAIT);//2-7-9 9:32
        init_vfd_clear();

        system_sleep();
    }

#else

#ifdef SUPPORT_UART_COMMAND // robert 020808
    // send power-off command to 8051
    UART_PUTC_EXACT(COMMAND_START);
    UART_PUTC_EXACT(POWER_OFF);
    UART_PUTC_EXACT(POWER_OFF_OK);
    UART_PUTC_EXACT(COMMAND_END);

    //psprintf(RegionValStr[REGION3], "SEND 8051 POWER OFF");
    //PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
    delay(1);
#endif
#ifndef POWER_OFF_ONLY_VIDEO_DAC_OFF
    AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0); //Jeff 20020522
    AUDIF_Set_Stop();//2004AUDDRV AudioSetStop(); //Jeff 20020522
    system_state=SYSTEM_POWER;//terry,2-5-14 22:55

#if defined(TOP_DOOR_LOADER) ||defined(CHECK_PORTABLE_OPCLSW) 
    old_play_state = play_state; //Jack added for portable power off 05/01/24
#endif
        
    play_state=VCD_STATE_POWER;//2-7-8 18:16
    WaitIopFunRdy(IOP_RDY_WAIT);//2-7-9 9:32
    init_vfd_clear();
#endif //POWER_OFF_ONLY_VIDEO_DAC_OFF
#ifdef OURMIND_VFDPORT_TO_BUTTON
    check_ourmind_light_status();
#endif

    #ifdef NO_AMP_ONLY_TUNER    //lijinhai
    regs0->gpio_out[22/16]|=(1<<(22%16));
#endif
#ifdef TONIC_DVD
write_vfd_led(0xff);
WaitIopFunRdy(IOP_RDY_WAIT);//2-7-9 9:32
#endif//TONIC_DVD
    #ifndef SPHE1000  //wrwu, 2004/11/03, fixed bug for SPHE100X standby mode.
        system_sleep();
    #endif
#endif

    system_sleep();
#ifdef POWER_OFF_ONLY_VIDEO_DAC_OFF     //2005-01-13 wjzhang ,fix the power un sync bug for twinhan
    notify_lx4189(RPT_STATE, GetStateIntr_OK); 
#endif
    /*AudioSetVolume(0);
    user_mute=0;
    resumeMSF = 0;
    resumeTRK = 0;
    t_disp=0;

      if(system_state!=SYSTEM_POWER)
      {
      printf("power off\n");
      if(play_state == VCD_STATE_OPEN)
      ircmd_trayin();

        if(system_state>SYSTEM_OPEN)
        {
        AVD_SetMediaTimeout();
        #ifdef MONE_TIMEOUR_SRC
        printf(__FUNCTION__" timeout\n");
        #endif
        }
        #ifdef FUSS_DVD
        erase_vfd_mem(); //nono 2-4-15 15:39
        #endif
        reset_sup();
        ircmd_post_func(CMD_FUNC | CMD_FUNC_POWER);
        system_state=SYSTEM_POWER;
        play_state=VCD_STATE_POWER;


            //tv_sleep();

              //stop atapi
              //atapi_p_start_stop_unit(Immed_1,0);
              //we stop ATAPI in sysmain2.c, when case SYSTEM_POWER

                } else
                {
                //Jeff 20020415
                //printf("power on\n");
                tv_resume();

                  //delay_1ms(20);
                  atapi_p_start_stop_unit(Immed_1,1);
                  close_tray_init();
                  system_state=SYSTEM_OPEN;
                  ShowTitle();
                  enable_video();

                    }
                    no_disk_cnt=DETECT_TIMES;
    printf("<power>\n");*/
}

#endif//#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-11

void sleep_when_power_on(void)
{
#ifndef VOLUME_RECODE
    AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0); //Jeff 20020522
#endif

    AUDIF_Set_Stop();//2004AUDDRV AudioSetStop(); //Jeff 20020522
    system_state=SYSTEM_POWER;//terry,2-5-14 22:55
    play_state=VCD_STATE_POWER;//2-7-8 18:16
    WaitIopFunRdy(IOP_RDY_WAIT);//2-7-9 9:32
    init_vfd_clear();
    system_sleep();
}

//wanghaoying 2003-8-19 23:10 moved SF_SR_IN_A_KEY defination to user_init.h


#ifdef SF_SR_IN_A_KEY
void    ircmd_slowmotion(void)
{

#ifdef SLOW_ZOOM_IN_A_KEY
    if( (bIrSkipState2!=1) )//2004-5-5 15:16
    {
         bIrSkipState2 = 1;
         rep_ir_times = 0;
         bIrSkipCnt2 = 0;
         return;
    }
    else
    {
         bIrSkipState2 = 0;
         rep_ir_times = 0;
         bIrSkipCnt2 = 0;
    }
#endif

    if((video_slow>=0) && UOP_check(UOP_FW))//chenzhao add for UOP access restricted 20051229
{
        invalid_key();
        return;
    }
    
    #ifdef SUPPORT_MP4 
    if(GetCurrentFileType() == CDROM_MP4)   //dingzhy cancel BK_SLOW for mp4 04-4-30 10:58
    {
        if(video_slow==8)
        {
           //invalid_key();
           ircmd_play();
           video_slow=0;
           return;
        }
    }
    #endif

    #ifdef DVD_AUDIO    // fangang added 4-2-10 19:58
    if (cd_type_loaded==CDDVD)  
    {
        if (dAMG_LSN!=0){
           invalid_key();
           return;
           }
           
    }
#endif 
    #ifdef SUPPORT_MIDI_MENU_SEL
        if(gIsMidiSelMenu)  return;
    #endif

    //terry , 0510
    //1.We should tell to yuxing , cancel this bad ideal
    //2.potatooo, PE_DSI_novideo has bug when user often input
    //    if (cd_type_loaded==CDDVD&&PE_DSI_novideo()) {
    //        invalid_key(); return;
    //    }

    if (cd_type_loaded == CDROM)
    {
#ifdef SUPPORT_FILE_SYSTEM_MODE
        // 2004/04/15 yltseng, add CDROM_MP4 for slowmotion
        if ( ( GetCurrentFileType() != CDROM_MPG && GetCurrentFileType() != CDROM_MP4 ) || 
             ( pFsJpeg->gifsState == FS_STATE_LIST ) )
#endif
        {
            invalid_key();
            return;
        }
#ifdef SUPPORT_FILE_SYSTEM_MODE
        else if (video_slow==0)
        {
            delay_srv_10ms(100);
        }
#endif
    }

#if defined(FUSS_DVD)||defined(GBM_DVD)
    if(video_slow<=(-8))
#elif defined(MINTON_DVD)  //wthsin 030818 ,cancel slow back function on MINTON DVD 
    if((video_slow<=(-1))||(video_slow>=(7)))
#else
    if(video_slow<=(-7))
#endif
    {
      ircmd_play();
      return;
    }

    if(pre_slowmotion()) return;

    if (video_slow==0)
        video_slow=2;
    else if(video_slow>0)

#if defined(FUSS_DVD)||defined(GBM_DVD)
        video_slow+=2;
#else
    video_slow++;
#endif

#if defined(SDRAM_16Mb_Mode)//only for SDRAM_16Mb_Mode nono 5-7-4 14:39

#if defined(FUSS_DVD)||defined(GBM_DVD)
 if (video_slow == 10) 
#else
 if (video_slow == 8) 
#endif
 {

#if defined(SUPPORT_SLOWBACKWARD2)
    if(cd_type_loaded!=CDDVD)
#endif    
    {
         ircmd_play();
         return;
    } 
 }
#endif//SUPPORT_SLOWBACKWARD2

#ifdef SUPPORT_FILE_SYSTEM_MODE//nono 4-7-22 23:44
    if  ( GetCurrentFileType() == CDROM_MPG || GetCurrentFileType() == CDROM_MP4 ) 
    {
#if defined(FUSS_DVD)||defined(GBM_DVD)
        if (video_slow == 10) 
#else
        if (video_slow == 8) 
#endif
        {
            ircmd_play();
            return;
        } 
    }
#endif//#ifdef SUPPORT_FILE_SYSTEM_MODE

#if defined(FUSS_DVD)||defined(GBM_DVD)
    if( (video_slow<=8)&&(video_slow>0) )
#else
        if( (video_slow<8)&&(video_slow>0) )
#endif
        {
            OSD1000ISP_STATUS(video_slow, OSDIR_SLOW);

            avd_slow_state(video_slow);
            PrintOsdMsg(STR_OS_SF|(video_slow<<OSDSTR_ID_TOTL_BIT),REGION1,1,7);
        } else {

#if defined(FUSS_DVD)||defined(GBM_DVD)
        if (video_slow == 10) //zhaoyanhua modify 2003-4-18 15:08
#else
        if (video_slow == 8) //zhaoyanhua modify 2003-4-18 15:08
#endif
        {
        	video_slow = -2;
        } else
        {

        #if defined(FUSS_DVD)||defined(GBM_DVD)
        video_slow-=2;
    #elif defined(SLOW_FIVE_LEVEL)//caoh 2005-4-21 20:14
        video_slow = video_slow*2;
    #else
        video_slow--;
    #endif

        }
    #if defined(FUSS_DVD)||defined(GBM_DVD)
    if( (video_slow >= -8) && (video_slow<0) )
    #elif defined(SLOW_FIVE_LEVEL) //caoh 2005-4-21 20:14
    if( (video_slow > -33)&& (video_slow<0) )
    #else
    if( (video_slow > -8)&& (video_slow<0) )
    #endif
    {
        int idSlow;

        idSlow = (-1) * video_slow;

        OSD1000ISP_STATUS(idSlow|(1<<4), OSDIR_SLOW);

        avd_slow_state(video_slow+1);
        PrintOsdMsg(STR_OS_SB|(idSlow<<OSDSTR_ID_TOTL_BIT),REGION1,1,7);
    }


   }

}
#else//#ifdef SF_SR_IN_A_KEY
void    ircmd_slowmotion(void)
{
    //terry , 0510
    //1.We should tell to yuxing , cancel this bad ideal
    //2.potatooo, PE_DSI_novideo has bug when user often input
    //    if (cd_type_loaded==CDDVD&&PE_DSI_novideo()) {
    //        invalid_key(); return;
    //    }
    
#ifdef SLOW_ZOOM_IN_A_KEY
    if( (bIrSkipState2!=1) )//2004-5-5 15:16
    {
         bIrSkipState2 = 1;
         rep_ir_times = 0;
         bIrSkipCnt2 = 0;
         return;
    }
    else
    {
         bIrSkipState2 = 0;
         rep_ir_times = 0;
         bIrSkipCnt2 = 0;
    }
#endif

#ifdef DVD_AUDIO    // fangang added 4-2-10 19:58
    if (cd_type_loaded==CDDVD)  
    {
        if (dAMG_LSN!=0){
           invalid_key();
           return;
           }

    }
#endif 
#ifdef SUPPORT_MIDI_MENU_SEL 
    if(gIsMidiSelMenu) 
    {
        BYTE    cmd;
        if (!((bMidiPlayerBoolean)&&(midiState == MIDI_STATE_PAYLOAD)))
        {
            invalid_key();
            return;
        }                 //ouyang 2004.07.31
        if(Midi_pause_flag)
        {
//ouyang add for invalid forward when press pause 2004-9-28 15:192004-9-28 15:19
            invalid_key();
            return;


/*            Midi_pause_flag =0;
            set_stc(midi_timenow);
            ircmd_play();
*/
        }

        if (iMidiSpeed>=0) { 
            //slow or normal speed, change to SF2X
            iMidiSpeed = -1;
            cmd = AUDIOSF1_25X;

            psprintf(RegionValStr[REGION1], ">");
            #ifdef SETUP_DONGLI459
            PrintOsdMsg(STR_OS_SF, REGION1, 0, 1);
            #else
            PrintOsdMsg(STR_OS_SF, REGION1, 5, 1);
            #endif
        } else if (iMidiSpeed<= -4) { 
            //change to play mode
            ircmd_play();
            return;
        } else {
            BYTE    buf[10];
            int     i, j;

            iMidiSpeed--;

            j = -1 * iMidiSpeed;

            for (i=0; i<j; i++) {
                buf[i] = '>';
            }
            buf[i] = '\0';

            cmd = AUDIOSF1_25X + j - 1;

            psprintf(RegionValStr[REGION1], buf);
            #ifdef SETUP_DONGLI459
            PrintOsdMsg(STR_OS_SF, REGION1, 0, 1);
            #else
            PrintOsdMsg(STR_OS_SF, REGION1, 5, 1);
            #endif
        }

        OSD1000ISP_STATUS(-iMidiSpeed, OSDIR_SLOW);

      #ifdef MESSAGE_QUEUE
        DSP_AudioIOControl(FLOW, cmd, 0);
      #else        
        DSP_Midi_AudioIOControl(FLOW, cmd, 0); // MidiAudioCtrl
      #endif 

        if (play_state != VCD_STATE_PAUSE) {
            return;
        }
    }           
#endif

    if (cd_type_loaded == CDROM)
    {
#ifdef SUPPORT_FILE_SYSTEM_MODE
        // 2004/04/15 yltseng, add CDROM_MP4 for slowmotion
        if ( ( GetCurrentFileType() != CDROM_MPG && GetCurrentFileType() != CDROM_MP4 ) || 
             ( pFsJpeg->gifsState == FS_STATE_LIST ) )
#endif
        {
            invalid_key();
            return;
        }
#if 0//def SUPPORT_FILE_SYSTEM_MODE     // 2005/05/04 yltseng undefine
        else if (video_slow==0)
        {
            delay_srv_10ms(100);
        }
#endif
    }

    if(UOP_check(UOP_FW))//chenzhao add for UOP access restricted 20051229
    {   
        invalid_key();
        return;
    }
    
    if(video_slow<0)
    {
      ircmd_play();
      return;
    }
    if(pre_slowmotion()) return;

    /*
    if(video_slow<2) {
    video_slow=8;
    avd_slow_state(video_slow);
    }

      if(video_slow>2)
      {
      video_slow--;
      avd_slow_state(video_slow);
      PrintOsdMsg(STR_OS_SF|(video_slow<<8),REGION1,1,7);
      }else
      ircmd_play();
    */

    if (video_slow==0)
        video_slow=2;
    else

#ifdef FUSS_DVD
        video_slow+=2;
#elif defined(EASTECH_NO_MORE_SF)
         video_slow+=2;
#elif defined(SLOW_FIVE_LEVEL) //caoh 2005-4-21 20:14
    video_slow= video_slow*2;
#elif defined(EASTECH_DVD_PHILIPS) //jwk add for philips 2005-12-13
        video_slow+=2;
#else
    video_slow++;
#endif

    #ifdef FBS_NOT_PLAY
    if(video_slow >= 8)
      video_slow = 2;
    #endif
    
#ifdef FUSS_DVD
    if (video_slow<=8)
#elif defined(EASTECH_NO_MORE_SF)
    if (video_slow<=6)      
#elif defined(USE_FW_SF)//zhongshan add for thomson slowforward after pause 2005-7-25 18:32
    if (video_slow<6)   
#elif defined(SLOW_FIVE_LEVEL)
    if (video_slow < 33)//caoh 2005-4-21 20:15
#elif defined(EASTECH_DVD_DP2070_D) // mimitsai 20050712
        if (video_slow<5) // 1/2, 1/3, 1/4,
  #elif defined(EASTECH_DVD_PHILIPS)  //jwk add for philips 2005-12-13
        if(video_slow<7)
#else
        if (video_slow<8)
#endif
        {
    int idSlow;
    #ifdef USE_FW_SF
        if(video_slow == 2)
                idSlow = video_slow;
        if(video_slow == 3)
                idSlow = 4;
        if(video_slow == 4)
                idSlow = 8;
        if(video_slow == 5)
                idSlow = 16;
    #else
            idSlow = video_slow;
    #endif
            OSD1000ISP_STATUS(idSlow, OSDIR_SLOW);

            avd_slow_state(video_slow);
            #ifdef SETUP_DONGLI459
            PrintOsdMsg(STR_OS_SF|(idSlow<<OSDSTR_ID_TOTL_BIT),REGION1,0,7);
            #else
            PrintOsdMsg(STR_OS_SF|(idSlow<<OSDSTR_ID_TOTL_BIT),REGION1,1,7);
            #endif
        } else {
            video_slow=0;
            ircmd_play();
        }
}


#endif//#ifdef SF_SR_IN_A_KEY


#ifdef TAS3001_AMP

void    ircmd_preview(void)
{
    //dvd-6-0 con1 pin3 aux3 (ca720 pin 113 gpio23  )high for tuner on
    ircmd_power();//2002 0918

    regs0->gpio_out[23/16]|=(1<<(23%16));
    //regs0->gpio_oe[23/16]|=(1<<(23%16));
}
#elif defined(IR_KODAK_EFFECT_KEY)

void    ircmd_preview(void)
{

    
    if (Is_JPEG_PLAY_STATE())
    {
        jpeg_effect_toggle();
    }else
    {
        invalid_key();
        return; 
    }

}

#else

/*
** preview
*/
void    ircmd_preview(void)
{
#ifdef SUPPORT_DVB_PREVIEW_9FRAMES
    if(system_state == SYSTEM_TS)
    {
        if(dvb_preview_state == 0)
        {
            DvbPreviewNavigationFirstFlag = 1;
            dvb_preview_navigation();
            return;
        }   
        else
        {
            ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);
            avd_play_state();
            play_state = VCD_STATE_NORMAL;
            DvbPreviewSlideShowFinish = 0;
            dvb_preview_state = 0;
        }
        return;
    }
#endif  
    
#ifdef SUPPORT_MIDI
        if (Is_MIDI_STATE())//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif
#ifdef DISABLE_DISPLAY_WHEN_9FRAME      //dingzhy for TONIC
if(( cd_type_loaded == CDVCD10)||( cd_type_loaded == CDVCD20)||( cd_type_loaded == CDSVCD))//zhongshan 20050721
    DispFadeOut();
#endif
    
#ifdef RECORD_PER_SECOND            //avoid bug  gerry  2-12-4 9:49
    resumeMSF=0;
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE
    if (Is_OTHER_STATE())
    {
        invalid_key();
        return;
    }
#endif

#if (defined(JPG_EFFECT)&&defined(CALL_JPGEFFECT_HELP)&&defined(USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP))//||defined(KSD_DVD)    //gerry mark it,3-8-19 21:22
//  jpeg_use_key_to_call_help();

    if ((cd_type_loaded==CDROM)&&(!Is_JPEG_STATE())&&(sys_cmd ==(CMD_FUNC|CMD_FUNC_STOP)))      //gerry for JPG_EFFECT invalid when not in JPG state,3-8-14 19:06
    {
        invalid_key();
        return;
    }

#ifdef SUPPORT_GIF //when play GIF pic, cannot display "USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP "effect ,suqiaoli add 2004-2-27
    if( GetCurrentFileType() == CDROM_GIF)
    {
        invalid_key();
        return;
    }
#endif  


#if defined(JPG_EFFECT)&&defined(SDRAM_16Mb_Mode)//nono 2004-3-16 22:00
    if(pFsJpeg->gifsState == FS_STATE_JPEG&&Is_JPEG_STATE())
#else
    if(pFsJpeg->gifsState == FS_STATE_JPEG||Is_JPEG_STATE())
#endif

    {
        if (pFsJpeg->gbfsSlide == 1)
        return;

        Jpg_Show_Usage_Flag=1;
        //ircmd_post_func(CMD_FUNC | CMD_FUNC_PREVIEW);
        Jpg_Show_Usage();
        return;
    }
    if(Is_JPEG_STATE())
        return;
#endif
    ircmd_cancel(C_SHOW|C_PLAY);

#ifdef PREVIEW_PBC_IN_ONE_KEY       //gerry for PANDA_DVD,3-8-22 14:58
    if(cd_type_loaded==CDDVD)
    {
        #ifdef SKYWORTH_DVD
         ircmd_root_menu();
        #else 
        ircmd_playmode_toggle();
        #endif
        return;
    }
#endif
    if ( (audio_only==1) && (cd_type_loaded==CDDA) )
        ircmd_intro();
    else
    {
        switch(play_state)
        {
        case VCD_STATE_STOP:
            //#ifdef IR_PLAY_RESUME_PAUSE
#if defined(IR_PLAY_RESUME) ||defined(IR_PLAY_RESUME_PAUSE)//nono 2-5-14 16:52 11:34 for fuss
            if(resumeMSF==0)
            {
                OSD1000ISP_STATUS(OSDISP_BROWSE, OSDIR_GLOBAL);

                PrintOsdMsg(STR_OS_BROWSE,REGION1,1,0);
                if(shuffle_flag==1) {
                    shuffle_flag = 0;

                    OSD1000ISP_STATUS(OSDISP_RAN_CNL, OSDIR_GLOBAL);

                    PrintOsdMsg(STR_OS_RAN_CNL,REGION2,1,0);
                }
                bIntro=0;
                ircmd_post_func(CMD_FUNC | CMD_FUNC_PREVIEW);
                play_state = VCD_STATE_PREVIEW;
            } else {
                invalid_key();
            }
#else

            OSD1000ISP_STATUS(OSDISP_BROWSE, OSDIR_GLOBAL);

            PrintOsdMsg(STR_OS_BROWSE,REGION1,1,0);
            if(shuffle_flag==1) {
                shuffle_flag = 0;

                OSD1000ISP_STATUS(OSDISP_RAN_CNL, OSDIR_GLOBAL);

                PrintOsdMsg(STR_OS_RAN_CNL,REGION2,1,0);
            }
            bIntro=0;
            ircmd_post_func(CMD_FUNC | CMD_FUNC_PREVIEW);
            play_state = VCD_STATE_PREVIEW;
#endif

            break;
        case VCD_STATE_PREVIEW:
            //#ifdef IR_PLAY_RESUME_PAUSE   //nono 2002-3-12 cancel intro
#if defined(IR_PLAY_RESUME) ||defined(IR_PLAY_RESUME_PAUSE)//nono 2-5-14 16:52 11:34 for fuss
            playmode_sel(RESUME);
            ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);

            OSD1000ISP_STATUS(OSDISP_SEQPLAY, OSDIR_GLOBAL);

            PrintOsdMsg(STR_OS_SEQUENCE,REGION1,1,0);
#else
            ircmd_intro();
#endif
            break;
        default:
#ifdef DVD_PREVIEW_FUNCTION//terry,2004/2/7 07:11PM
            if(cd_type_loaded==CDDVD)
            {
                ircmd_play();               

                OSD1000ISP_STATUS(OSDISP_BROWSE, OSDIR_GLOBAL);

                PrintOsdMsg(STR_OS_BROWSE,REGION1,1,0);//terry,2004/2/9 12:55PM
                ircmd_post_func(CMD_FUNC | CMD_FUNC_PREVIEW);
                play_state = VCD_STATE_PREVIEW;
                break;
            }
#endif

            if (IsPBCOn())
            {       /* alan 2002/7/22 01:04PM modified for ircmd_preview fail */
                if( (  (cd_trk_now>=cd_trk_lo_now) &&
                    (cd_trk_now<=cd_trk_hi)
                    )
                    ||
                    ( (bDiscType == CD_OKO) &&
                    (psd_state != (PSD_SEL_LIST|PSD_PLAY_SEG) )
                    )
                    )
                {
                    pbcoff_init();

                    OSD1000ISP_STATUS(OSDISP_SEQPLAY, OSDIR_GLOBAL);

                    PrintOsdMsg(STR_OS_SEQUENCE,REGION1,1,0);
                } else {
                    invalid_key();
                    return;
                }
            }
            
            #ifdef PREVIEW_TO_THUMBNAIN_MENU    //Maoyong 2004.05.12
            if( Is_JPEG_STATE() )
            {
                ircmd_callback_check = fs_callback_check;
                ircmd_post_func(CMD_FUNC | CMD_FUNC_MENU);
                return;
            }
            #endif 
            
            //Maoyong 2004.06.24
#if !defined(CALL_JPGEFFECT_HELP)
            if( Is_JPEG_STATE() )
            {
                invalid_key();
                return;
            }
#endif

#if defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua add 20040129
            if(media_type != MEDIA_CARD)
                ircmd_9frames();
#else
            ircmd_9frames();
#endif
            break;
        }
    }
}

#endif
/*
** 9 frames
*/
void    ircmd_9frames(void)
{
    //Maoyong 2004.04.23 Marked for common use. 
    //When repeat ab in MP3/WMA, it will normally play,but osd still show "REPEAT AB"
//#ifdef    INVALID_9FRAMES_IN_MP3  //wuxiaofeng 2004-03-17
    if(Is_MP3_STATE())
    {
        invalid_key();
        return ;
    }
//#endif//#ifdef    INVALID_9FRAMES_IN_MP3

#ifdef DISABLE_DISPLAY_WHEN_9FRAME      //dingzhy for TONIC
    DispFadeOut();
#endif

#ifdef SUPPORT_PREVIEW_9FRAMES
    if(bIntro)
    {
        bIntro=0;

        OSD1000ISP_STATUS(OSDISP_SEQPLAY, OSDIR_GLOBAL);

        PrintOsdMsg(STR_OS_SEQUENCE,REGION1,1,0);
        return;
    }

    ircmd_cancel(C_SHOW|C_PLAY|C_ZOOM);
    chg2normal_play(FAST2NORM|SLOW2NORM|PAUSE2NORM,DEMUTE);

    shuffle_flag = 0;
    playmode_sel(RESUME);
    ircmd_post_func(CMD_FUNC | CMD_FUNC_9FRAMES);
    play_state = VCD_STATE_9FRAMES;
#endif//#ifdef SUPPORT_PREVIEW_9FRAMES
}

/*
** intro
*/
void    ircmd_intro(void)
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef SUPPORT_PREVIEW_9FRAMES
    extern void show_intro_info(void);//v11.c

    if (cd_type_loaded==CDROM) { //Jeff 20020716
        invalid_key();
        return;
    }

    if(IsPBCOn())
    {
        if(play_state!=VCD_STATE_STOP)
        {
            invalid_key();
            return;
        }
    }

    if(bIntro==1)
    {
        //bIntro=0;
        ircmd_play();
    }else
    {
        bIntro=1;
        resumeMSF=0;//hq,2004-3-8 9:40
        if(play_state!=VCD_STATE_NORMAL)
            ircmd_play();
    #if defined (JIEKE_CD_PREVIEW)||defined (TONIC_THOMSON_MODEL) ||defined(CD_INTRO_RESET_TRACK) //zhongshan for thomson intro from track 1 050720 
    if(cd_type_loaded==CDDA)
    {   
        v11_trk_now=1;
        cd_trk_now=0;
    }
    #endif  
        show_intro_info();
    }
#endif//#ifdef SUPPORT_PREVIEW_9FRAMES
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}
/*
** tray-out
*/

#ifdef ADD_AUDIO_PLAY_WHEN_OPEN
#include "open_tray_audio.c"
#endif

#ifdef AUTO_CLOSE_LOADER
    extern  UINT16 auto_close_timer;
#endif

void    ircmd_trayout(void)
{
    
    #ifdef MULTIDISC_LOADER //chenzhao 20060111
    if(! is_multidisc_trayout_only())
        if(! multidisc_loader_post_cmd(MULTIDISC_CMD_EJECT))
        {
            if(! multidisc_loader_post_cmd(MULTIDISC_CMD_EXCHANGE))//change trayout to exchange
                invalid_key();
            return;
        }
        #ifdef NEW_PARENTAL_GUI//chenzhao20060214
        extern int user_input_pwd;
        extern BYTE new_parental_gui;
        extern void ExitParentalGUI(void); 
        if(new_parental_gui)
        {
           ExitParentalGUI(); 
           user_input_pwd=2;
        }
        #endif//#ifdef NEW_PARENTAL_GUI
    #endif
    #ifdef MP3_JPEG_COWORK  //aviod output some mp3's sound hongfeng 2006/4/14 13:30
    AUDIF_Set_Stop(); 
    #endif

#ifdef UNLOCK_STATE_NOT_CHECK_PASSWD//shenyj add for alco 11/19
disc_has_unlock=0;
#endif

#ifdef ADD_AUDIO_PLAY_WHEN_OPEN
    if(Is_JPEG_STATE())
    {
        LoadModual(MODUAL_MPEG);
        //AUDIF_Reset_DSP();
        //AUDIF_Set_Stop();
    }
    mem_play_mp3(1,qry_mp3_len());
    mem_play_mp3(0,qry_mp3_len());
#endif
    
#ifdef IR_SWITCH_CD_USB_CF_OTHER  //dingzhy for init 04-10-22
    now_valid_type = 0;
#endif  
    
#ifdef QSI_PLATFORM //qsi: added by johnson 20040811
    #ifdef SUPPORT_CARD_STORAGE
    if( source_type_now == source_card)
    {
        invalid_key();
        return;
    }
    #endif
#endif

#ifdef CrYCb16_GRAPHIC_MODE
    regs0->display_mode = 0x0;
    
#endif    

#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
    if((cd_type_loaded==CDDVD) && (play_state!=VCD_STATE_STOP))
    {
        need_record = 1;
        ircmd_stop();
        ShowTitle();
        LoadModual(MODUAL_CDROM);
        need_record = 0;
    }    
    if(IS_DVD_VCD_DISC())
        need_record = CLEAR_RECORD_FLAG; //added 05/07/23              
#endif

#ifdef AUDIO_AND_SUBTITLE_SAME2_OSD
    osd_has_chaned = 0;
#endif

 //dingzhiyong  mark  it  04-02-10 11:01AM    
    
#ifdef SHOW_SPECIAL_DISC_TYPE //Jack added 04/11/16
    read_disc_state = 0; 
#endif

    #if defined(REMAIN_TIME)&&defined(ALCO_DVD_UI)
    polling_clock=0;
    #endif
            
//===========================================
//for QSI disc\card switch  //added by JS   //20040728
#ifdef SUPPORT_QSI_SOURCE_SWITCH
    source_type_now = source_disc;
#endif
//===========================================
    
#if defined(SUPPORT_USB)//liweihua add 20031223
    if(card_plug_state&USER_DO_PLUG_IN){
        card_plug_state &= ~USER_DO_PLUG_IN;
    }
#endif
//    printf("ircmd_tray_out\n");
    SetIDETimeOut(SHORT_TMOUT);//printf("set srv timeout tm = %d\n",SHORT_TMOUT);//terry,2003/7/17 11:17PM
/*Mark by David 030924 update code(wthsin)
#ifdef CD_PLAYER        //liweihua  2003-9-3
    if(cd_type_loaded==CDDA)
    {
       osd_init();
    }
#endif
*/
#ifdef ONE_KEY_PASS
    #ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-29 19:51
    one_key_pass_play = 0;
    #endif
    dvd_title = 0;
#endif

#ifndef RECORD_KEY//zhaoyanhua add 03-10-19 11:49
#ifdef  SAME_DISC_RESUME    //Maoyong changed 2004.03.18

#ifdef DVD_5_DISC_RESUME//lijd 2005-6-9 14:56
    if((cd_type_loaded==CDDVD)&&(StopTimes==0))//lijd 2005-6-30 13:31  
    {  
        if((pDSV->CurrDomain != VTSM_DOM)&&(pDSV->CurrDomain != VMGM_DOM)&&(pDSV->CurrDomain != FP_DOM)&&(pDSV->CurrDomain != VMGM_DOM_PGCN))//lijd 2005-7-6 21:27
        {
        ircmd_stop();
        LoadModual(MODUAL_CDROM);   
        resumeMSF = 1;  
            delay_srv_10ms(5);
        RsmInfo2Flash(0);
      }
      }
    else if((cd_type_loaded==CDDVD)&&(StopTimes==1))
    {
        if((pDSV->CurrDomain != VTSM_DOM)&&(pDSV->CurrDomain != VMGM_DOM)&&(pDSV->CurrDomain != FP_DOM))//lijd 2005-7-6 21:27
        {
        resumeMSF = 1; 
        LoadModual(MODUAL_CDROM);        
        delay_srv_10ms(5);       
        RsmInfo2Flash(0); 
    }       
    }       
    else if((cd_type_loaded==CDDVD)&&(StopTimes==2))//lijd 2005-8-1 13:56
    {
            ircmd_stop();
            resumeMSF = 0;          
            LoadModual(MODUAL_CDROM);        
        RsmInfo2Flash(0); 
    }       
#else
    if(cd_type_loaded!=CDROM)//gerry add it,CDROM disc need not resume,to avoid read JPEG reset,2004-7-20 18:16
	 #ifdef SUPPORT_LAST_MEMERY
     if(memery_resumeflag)
     #endif//end=> #ifdef SUPPORT_LAST_MEMERY
    RsmInfo2Flash(0);
#endif
    
#if 0//def SUPPORT_OP_FIVE_DISC//marked it.chenzhao 20060420 //chenzhao20060107
	ShowTitle();  //show logo 
#endif  

#ifdef USER_MPEG_LOGO   // alan, 2003/8/25 09:00PM
    if (mpeg_logo_onoff==1)
    {
        UINT8 p=0x88;       
        //WriteToI2c(0xa0,0xe0,&p,1);
        WriteToI2c(0xa0,0xd2,&p,1);         //gerry for vcd disc,2003-12-22 16:28
    }
#endif
#endif//end SAME_DISC_RESUME
#endif //end ifndef RECORD_KEY

#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
    need_record = 0;
#endif        

    #ifdef AUTO_CLOSE_LOADER
    {
        //extern  UINT16 auto_close_timer;
        auto_close_timer=0x8000;
    }
    #endif

#ifdef CALL_JPGEFFECT_HELP // alan, to clear jpeg show usage flag when tray out, 2003/8/9 02:46PM
    Jpg_Show_Usage_Flag=0;    
#endif    

//when play WMA after MP3,(they use the same BUTTON)
//must clear MP3TotalNo to disble MP3 lyrics polling.
//zhaoyanhua  2003-9-12 15:36
#ifdef MP3_TXT_DISPLAY
    extern UINT16 MP3TotalNo;
    
    MP3TotalNo = 0; 
#endif

    // it's not suitable to put these codes here, move to CheckVolumeDescriptor()
//nono 5-1-20 11:26 open it.
#if defined (SUPPORT_FONT_UTIL) || defined (SUPPORT_JOLIET_FORMAT) //nono 20031213, 2005/02/16 yltseng
{
extern BYTE supplementary_volume_descriptor_exist ;
supplementary_volume_descriptor_exist = 0;
}
#endif
    goto_time = 0;
    goto_hour = 0;
    goto_sec = 0;
    goto_min = 0;

    show_time_hh = 0;//20031204 zhaoyh_fengjl
    show_time_mm = 0;//20031204 zhaoyh_fengjl
    show_time_ss = 0;//20031204 zhaoyh_fengjl

    if (t_disp) {
        DispFadeOut();
        disp_mode=0;     /* alan 2002/6/10 05:46と */
    }

    rem_osd_id = 0;//nono 2003-9-2 20:11
    
#ifdef SUPPORT_MP4_SUBTITLE  // David 2004-5-13
    #ifdef ALCO_DVD_UI
    if(GetCurrentFileType() == CDROM_MP4) 
    #endif
        osd_init();
#endif
    
    #ifdef  RECORD_KEY  //Maoyong 2004.03.09 avoid to show DISPLAY when checking record key 
    cd_type_loaded = CDUNKNOWN;
    #endif
    
#ifdef SUPPORT_OSDID3//liweihua add 2004-1-9 
    if(Is_MP3_STATE())
         osd_init();
#endif
    //PrintOsdMsg(STR_OS_OPEN,REGION0,1,0);
#ifdef DISPLAY_CD_TEXT//lizhx add 2004/08/24
    if (cd_type_loaded == CDDA)
        osd_init();
#endif
    
#if defined(ALWAYS_DISPLAY_OPEN)||defined(SETUP_DONGLI459)      //wthsin 03/08/15; hq,for bbk,3-11-22 14:28
    #ifdef  UPGRADE_TRAYOUT
        if(trayout_flag==0)       
    #elif defined(MULTIDISC_LOADER)//chenzhao 20060111
    if(! is_multidisc_trayout_only())
    #endif
        {

        OSD1000ISP_STATUS(OSDISP_OC_OPEN, OSDIR_OPEN);

        PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);  
        }
#else
    #ifdef  UPGRADE_TRAYOUT
        if(trayout_flag==0)
    #elif defined(MULTIDISC_LOADER)//chenzhao 20060111
        if(! is_multidisc_trayout_only())
    #endif
        {

        OSD1000ISP_STATUS(OSDISP_OC_OPEN, OSDIR_OPEN);

        PrintOsdMsg(STR_OS_OPEN,REGION1,1,0);
        }
#endif 

    #ifdef TOP_DOOR_LOADER //Jeff 20031112
/*
        if ( (GPIO_GET_DOOR_STATUS() == DOOR_OPEN) &&
             (system_state==SYSTEM_IDLE) && (play_state==VCD_STATE_POWER) 
           ) {
    open_tray();
        }
*/
/*
        extern UINT8 power_on_mute;
        if (power_on_mute==0) 
        {
            printf("\n--not first open tray--\n\n");
            open_tray();
        }
*/
#ifdef MINTON_YILI_DVD1003_2CH
         if( (GPIO_GET_DOOR_STATUS() == DOOR_OPEN)&&(system_state!=SYSTEM_IDLE)&&
             (system_state!=SYSTEM_NODISC)) 
#else
         if( (GPIO_GET_DOOR_STATUS() == DOOR_OPEN)&&(system_state!=SYSTEM_NODISC)) 
#endif
            open_tray();
    #else
        #ifdef SPHE1000
        if (!from4189)
        #endif
        open_tray();
    #endif

    #if defined(SUPPORT_CDG)  //Jeff 20021108
        #ifdef SUPPORT_ECC
            bReadSubChannel=1;
        #else
            bReadSubChannel=4;
        #endif
    iBlockLen=1224;  //(2352+96)/2=1224
    #endif

    //reset audio channel to default(stereo), Jeff 20020514
    audio_channel = 0;
    AUDIF_Set_OutputMode(audio_channel+1, 0);//2004AUDDRV AudioSetOutputMode(audio_channel+1, 0);

	HL_exist=0;// 2006/03/30 libing
	           // Fix Bug:When open at dvd_menu,Then read usb & card,ircmd_dir have not effect.

#ifdef SDRAM_16Mb_Mode//nono 2003-12-13 19:17    
    AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(0); //S-PDIF off mode command to DSP(0:off)//nonotest
#endif//SDRAM_16Mb_Mode

#ifdef ZOOM_DIRECT_STOP_SLIDE       //wanghaoying 2003-08-25 21:30
        if( Is_JPEG_SlideMode() ) 
            jpg_slide_time = JPEG_SLIDE_TIME;
#endif

#ifdef SPHE1000
    if (!from4189)
#elif defined(SUPPORT_FIVE_DISC)//chenzhao20060107
    if(!is_jump_disc_mode()) //jump disc
#endif
    {
    CDSetOpen();
    }
    no_disk_cnt=DETECT_TIMES;

/*terry,2004/1/8 07:56PM,mark it
#ifdef SUPPORT_JPEG_MIC//terry,2004/1/7 07:32PM 
  if(pFsJpeg->gifsFuncBtn==FS_FUNC_JPEG)
  {
    set_aud_buf(A_DSP24YA, A_AUDYA, A_PCMYA);   
    init_audio_dsp_coding_mode();
    pFsJpeg->gifsFuncBtn=0;
  }
#endif
*/ 
    ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
 
    
#ifdef SUPPORT_WMA
   if(GetCurrentFileType() == CDROM_WMA)    
    AVD_SetMediaTimeout();//terry 3-12-26 0:06 
#endif

#if defined(SUPPORT_FIVE_DISC)//chenzhao20060107
    if(!is_jump_disc_mode()) //jump disc
#endif
    {
    play_state = VCD_STATE_OPEN;
    }
    playmode_sel(CLEAR_ALL);
#ifdef POWER_RESUME
    #ifndef SAME_DISC_RESUME
	#ifdef SUPPORT_LAST_MEMERY
    if(memery_resumeflag)
    #endif//end=> #ifdef SUPPORT_LAST_MEMERY
    RsmInfo2Flash(1);//clear memory
#endif
#endif
    //printf("ircmd_tray_out ,out\n");
#ifdef CD_PLAYER        //liweihua  2003-9-26
    if(cd_type_loaded==CDDA)
    {
        ClearOsdMsg(0);
        osd_disable();       
       osd_init();
        #define __palette4F(G,B,R,A) \
            ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 
        SetOsdCol(0,0,0,0x1e1e1e00);
        SetOsdCol(0,0,5,__palette4F(128,64,255,0xff));
        SetOsdCol(0,0,8,__palette4F(128,255,0,0xff));
        SetOsdCol(0,0,9,__palette4F(128,255,0,0xff));
        ShowTitle();
    }
#endif

#ifdef SETUP_ON_OPEN_VALID
    OpenFlag = 1;
#endif

#ifdef SPHE1000
    if (from4189)
        from4189=0;
#endif

#ifdef ALCO_PDVD_NO_DTS
    if((coding_mode_now==AUDIF_CODING_MODE_DTSCD) || (cd_subtype==CD_DTS))
    {
        cd_subtype = CDROM_UNSUPPORT;
        //printf_w("DTS CD AU0 release............\n");
        regs0->sft_cfg3|=(0x01<<1);
    }
#endif
}

// 2004/10/01 yltseng mark, move to test_atapi_drv_rdy()
//extern UINT8 old_cd_type;//TERRY,2003-8-1 15:45

/*
** tray-in
*/
void    ircmd_trayin(void)
{
    int id;

    #ifdef MULTIDISC_LOADER //chenzhao 20060111
    if(! multidisc_loader_post_cmd(MULTIDISC_CMD_CLOSE))
    {
        invalid_key();
        return;
    }
    #endif
    
    #ifdef SHOW_12_BOOKMARK//libing 2005-6-23 21:47
    cancel_bookmark();
    #endif
    #ifdef OP_PLAYMODE//libing 2005-6-30 20:07
    play_mode_cancel();
    #endif
    #ifdef AVOID_READDISC_WHEN_STARTUP  //xyy add for Oritron
     extern UINT16 uCounterFlag;
     uCounterFlag = 0;
    #endif 

#ifdef SPHE1000
    if (from4189) from4189=0;
#endif
#ifdef QSI_PLATFORM //qsi: added by johnson 20040811
    #ifdef SUPPORT_CARD_STORAGE
    if( source_type_now == source_card)
    {
        invalid_key();
        return;
    }
    #endif
#endif



#ifdef CD_PLAYER        //liweihua 2003-9-3
    if(cd_type_loaded==CDDA)
    {
        osd_init_cdplayer();
    }
#endif  
#if defined(DYNAMIC_SPECTRUM) && defined(SUPPORT_PROLOGIC_II)//axel 2004/1/28 10:45 
    if(bEqDisplay)
    {
        if((cd_type_loaded == CDROM) &&(setup_IsSpkDownmixOff()))//if((cd_type_loaded == CDROM)&&(setup_IsSpkDownmixOff()))
        {
            
            AUDIF_Set_Stop();//2004AUDDRV AudioSetStop();
            AudioSetPrologic_IIOutput();
            
        }
        ClearShowSpectrum();
        AUDIF_Set_Continue();//2004AUDDRV AudioSetContinue();
    }
#endif

#ifdef SDRAM_16Mb_Mode//nono 2003-12-13 19:16
    setup_SetDTSCDConfig();
#endif//SDRAM_16Mb_Mode

    //terry,2-5-15 0:29
    //bug: toggle open/close tray operation quickly.
    //avoid difference between vfd and osd.

#if DISC_SYSTEM==DISC_SYSTEM_ATAPI
    {   // alan added 02-05-28

#ifdef TRAY_AVAILABLE
        if(atapi_p_mechanism_status()==2)
            {
            OSD1000ISP_STATUS(OSDISP_READ, OSDIR_GLOBAL);

            id=STR_OS_READ;
            }
        else
            {
            OSD1000ISP_STATUS(OSDISP_OC_CLOSE, OSDIR_OPEN);

            id=STR_OS_CLOSE;
            }
#else
        OSD1000ISP_STATUS(OSDISP_READ, OSDIR_GLOBAL);
        id=STR_OS_READ;
#endif
    }
#else
    {
        OSD1000ISP_STATUS(OSDISP_OC_CLOSE, OSDIR_OPEN);

        id=STR_OS_CLOSE;
    }
#endif

    // 2004/10/01 yltseng mark, move to test_atapi_drv_rdy()
    //old_cd_type=0xff;//TERRY,2003-8-1 15:45

    #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-12 17:21
    #ifndef NO_DVD_SERVO
    UINT32 uiRes = 0;
    if( (media_status != STATUS_DISC) && (media_status != STATUS_NON) )
    {
        PrintOsdMsg(id,REGION1,1,0);
        uiRes = close_tray(1);//close tray stop loader.
    }
    else if (media_status == STATUS_DISC)
    {
        uiRes = close_tray(0);//close tray run loader.
        PrintOsdMsg(id,REGION1,0,0);
    }
    if (!uiRes)
    {
        CDSetStop();
        ircmd_post_func(CMD_FUNC | CMD_FUNC_CLOSE);//kenny 2001/6/11  add it
        play_state = VCD_STATE_CLOSE;
    }
    else
        invalid_key();
    #endif//NO_DVD_SERVO
    #else//DIRECT_ACCESS_MEDIA
    PrintOsdMsg(id,REGION1,0,0);
    if(!close_tray(0))
    {
        CDSetStop();
        ircmd_post_func(CMD_FUNC | CMD_FUNC_CLOSE);//kenny 2001/6/11  add it
        play_state = VCD_STATE_CLOSE;
    }else
        invalid_key();
    #endif//DIRECT_ACCESS_MEDIA

#ifdef SETUP_ON_OPEN_VALID        
        OpenFlag = 0;
#endif
}


/*
** toggle tray in/out
*/
#if (defined(SUPPORT_JKDISKSTATUS)&&defined(MIDI_EJECT_PASSWORD))    //ouyang add for eject password 2004-11-20 15:10
extern UINT8 midi_open_pwd_start;    
extern UINT8 midi_open_pwd_finished; 
static inline BYTE chk_open_pwd_state()
{
    extern void CleanSysMessage(BYTE);
    if (CDOpened())
        return 0;
    if(!gIsMidiSelMenu) 
    {
       ReadFromI2c(I2C_ID_MEMORY,DISK_STATUS,&gIsMidiSelMenu,1);
    }
     if(gIsMidiSelMenu) 
     {
        CleanSysMessage(1);   
 //psprintf(RegionValStr[REGION1], ""); //terry,2005/4/7 09:10と
        PrintOsdMsg(STR_OS_EJECT_PASSWORD, REGION1, 0, 0);
    if(play_state!=VCD_STATE_OPEN)
        midi_open_pwd_start = 1;
    else
        midi_open_pwd_start = 0;
        
    if( (!midi_open_pwd_finished) && (play_state!=VCD_STATE_OPEN) )
        return 1;
    else
    {
        midi_open_pwd_start = 0;
        midi_open_pwd_finished = 0;
            gIsMidiSelMenu =0;          
            {
                WriteI2c(I2C_ID_MEMORY,DISK_STATUS,0x00,1);
            }
        return 0;
    }
        }
        else
        return 0;
}
#endif//#ifdef MIDI_EJECT_PASSWORD    //ouyang add for eject password 2004-11-20 15:10

#ifdef SP1000_NO_DVD
void    ircmd_eject_toggle(void)
{
}
#else

void    ircmd_eject_toggle(void)
{ 
#if defined(SUPPORT_MPG_FILE_PARSER )&&defined(MODIFY_FOR_PLAY_MPG_CHANGE2_CDDA_NEXT_TRK_NOT_CHANGE)//shenyj add for alco 2006/02/17

 file_type=0;

#endif
#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    if(source_play_mode != DVD_PLAY_MODE)
        return;
    else
        mode_key_delay_cnt = 6;//MODE_DELAY_CNT;
#endif
    #ifdef SUPPORT_FIVE_DISC  //chenzhao20060107
        if(!tray_oper_finish())
        {
            #ifdef SUPPORT_FIVE_DISC_DBG
            printf("5disc:ircmd_eject_toggle>  tray no finish  over !!!  \n");
            #endif  
            return ;
        }   
    #endif  
    #ifdef SUPPORT_QUICKTIME
    extern UINT32		pre_parse_mode;
    if (pre_parse_mode)
    {
        //File preparse mode
        //printf("===========> Reject open command \n");
        return;
    }
    #endif //SUPPORT_QUICKTIME
    
    #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    if(source_play_mode != DVD_PLAY_MODE)
        return;
    #endif
    
 #ifdef SUPPORT_MP3_ENCODER
   ripping_flag=0;   
   stop_current_ripping();
 #endif 
   #ifdef OP_CD_CDG_CHANGE //caoh 2005-9-19 10:37
    op_cd_cdg_flag = 0;//caoh 2005-9-19 10:37 only for OP
   #endif
  
  #ifdef OP_DVD5121_PANEL//qinhua ,add 2005-9-5 22:34
   if (regs0->iop_data[6]==IR_ADDR_PATT)
 {
      
    if( (pressed_flag!=1) ) 
    {
         pressed_flag = 1;
        return;
    }
    else
    {
         pressed_flag = 0;
    }
 }
 #endif 
    #ifdef SUPPORT_STOP_PLAY_READ_USB_CARD //caoh 2005-8-31 9:54
        if((media_type==MEDIA_CARD)&&(play_state=VCD_STATE_STOP))
        {
          SwitchMedia(CARD2CD);
          media_change_flag =1;  
        }
    #endif
    
   
    static BYTE i=0;
    #ifdef PARENT_PWD_DEFAULT_NULL //caoh 2005-8-2 17:47
    PassWord_OK = 0;
    #endif
    
    #ifdef SCORE_IN_PLAYMODE_MENU
        score_flag = 0;
		  delay_1ms(100);  // for score osd
		  ircmd_exit();
    #endif
#ifdef ORITRON_TRAY_PASSWORD//libing 2005-4-25 14:18
    printf("tray_flag=%d\n",tray_flag);
    printf("ADDR_I2C_TRAY_PWD=%d\n",ADDR_I2C_TRAY_PWD);
    if((system_state==SYSTEM_OPEN)&&(play_state==VCD_STATE_OPEN))
    {
        ircmd_trayin();
        return;
    }   
    if(tray_flag==0x33)//0x33 means ?
    {
        PrintOsdMsg(STR_OS_LAD_LOCK,REGION1,2,0);
        return; 
    }   
#endif  


#ifdef SPHE8202_CARD_STORAGE//dingzhy 05-3-22 13:06
    GPIO_O_SET(CARD_POWER_RESET,1);    //off card light
#endif


#ifdef SUPPORT_MIDI_MENU_SEL    //ouyang 2005-4-8 14:03
    if (gIsMidiSelMenu)
    {
        if (bHoldInput)     
        {
            return;
        }
    }
#endif
#ifdef SUPPORT_SANJING_SCORE
    //xlluo close the score after eject the MidiDISK
    bIsSJScoreInvaild =0;  
   #endif 
#ifdef MIDI_EJECT_PASSWORD    //ouyang add for eject password 2004-11-20 15:10
if( chk_open_pwd_state() ) return;
#endif

#ifdef QSI_PLATFORM //qsi: added by johnson 20040811
    #ifdef SUPPORT_CARD_STORAGE
    if( source_type_now == source_card)
    {
        invalid_key();
        return;
    }
    #endif
#endif
#ifdef TONIC_DVD
        coding_mode_now=0;
#endif//TONIC_DVD
    #ifdef TEST_SERVO
    {
        extern UINT32 save_srn_start_t;
        UINT32  iTime = 0;
        static  UINT32  iTime0=0;

        if (iTestServoMode==0) {
            if (action_click>0) {
                iTime = get_rtc_val();
                if ( (iTime - iTime0) > 100) {
                    ClearOsdMsg(2);
                    iTime0 = 0;
                    action_click = 0;
                    i = 0;
                    set_rtc_val(0);
                    save_srn_start_t = 0;
                } else {
                    iTime0 = iTime;
                    save_srn_start_t = iTime;
                }
            } else {
                ClearOsdMsg(2);
                iTime0 = 0;
                set_rtc_val(0);
                save_srn_start_t = 0;
            }
        
            if (iTime>=TEST_SERVO_RUN_TIME) {
                //do open/close testing
                action_click=0;
                iTestServoMode = 1;
                iTestServoCount = 0;
                psprintf(RegionValStr[REGION2], "DO OPEN/CLOSE TESTING:%05d", iTestServoCount);
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
                return;
            } else {
                //display open/close
                if (action_click) {
                    psprintf(RegionValStr[REGION2], "OPEN/CLOSE TIME:%d SECONDS", (iTime/100));
                    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
                    return;
                }
            }
        } //if (iTestServoMode != 1) {
    }
    #endif //#ifdef TEST_SERVO

    #if (defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE))&&(defined DVD_SERVO) //ycwen 2004/08/10
    if (media_type != MEDIA_CD) {
        //drv_do_set_features();
        media_type = MEDIA_CD;
        ServoDecMainLoop();
        #if defined(HOST_UHCI)//liweihua 20040324
        uhci_reset(); 
        #elif defined(USB_HOST_DRV)
          usb_host_init();  //wthsin
        #endif
    }
    #endif
    
#ifdef TEST_VFD
    return ;            //shawn modify at 910131
#endif

#ifdef SDRAM_16Mb_Mode
            prog_state=0;
#endif

    rep_ab_mode = REPEAT_IDLE;

    if (CDOpened())
    {
        #ifdef ALWAYS_DISPLAY_OPEN     //linrc add 2004-5-13 19:54
        OSD1000ISP_STATUS(OSDISP_OC_OPEN, OSDIR_OPEN);

        PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
        #endif  //end ALWAYS_DISPLAY_OPEN
        if( (system_state!=SYSTEM_BROWSE)||(i>2) ) //terry,00/12/02
        {
            i=0;
            ircmd_trayin();
            
            #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, for don't read DISC when close tray.
            detect_type = 0;
            storage_type = 0;
            media_type = MEDIA_NOTHING;
            #endif//DIRECT_ACCESS_MEDIA
            
            printf("after ircmd_trayin\n");


            if (!user_mute){
#ifdef CNTR_5SPK_VOLUME
                //AudioSetVolume(audio_volume);
        {//wangfeng 2003-11-08 03:26
        int i,read_volume;
        for (i=0; i<7; i++) {
        
        read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
        if(i==0)
        {
            #ifdef CNTR_5SPK_TYPE_2  //linrc add 2004-10-13 9:17 -->ESS is like this type
            Set_5SPK();
            #else
        AUDIF_Set_Volume(volume_5SPK[0]);//2004AUDDRV AudioSetVolume(volume_5SPK[0]);
            #endif
        }
        else
                            DSP_AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);//2004AUDDRV AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);
    }
    }
#else
                AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
#endif
                }
        }else
            i++;
    }else
    {
        user_mute = 0;

#if defined(USE_GAMEPORT_TO_DISCLIGHT)
        init_light_io_out();//init_light_io();
#endif

        ircmd_trayout();
        
#ifdef EJECT_DISP_FADE_OUT
        DispFadeOut();        //liumzh 2004-9-24 18:47
#endif

        printf("after ircmd_trayout\n");
         #ifdef DISPLAY_CD_TEXT  //LIZHX ADD 2004/08/23
            osd_disable();
            printf("display here########################\n");
         #endif //DISPLAY_CD_TEXT
        // clear prog content
        //LoadModual(MODUAL_AP3);
//  #ifndef OP_UI//zhaoyanhua add 2004-4-14 13:27
    //we need not clear the prog content
        prog_func_clear();
//  #endif//
        //LoadModual(MODUAL_AP2);
    }
    #ifdef USE_AMP_MUTE//chenzhao20060114
    user_amp_mute=0;
    #endif   
    //polling_osd();

    #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, for don't read DISC when close tray.
    detect_type = 0;
    storage_type = 0;
    media_type = MEDIA_NOTHING;
    #endif//DIRECT_ACCESS_MEDIA
}

#endif //#ifdef SP1000_NO_DVD


/*
** play
*/
void ircmd_play(void)
{
#ifdef QSI_PLATFORM //qsi: added by johnson 20040811
    #ifdef SUPPORT_CARD_STORAGE
    if( (source_type_now == source_card) && (play_state == VCD_STATE_STOP))
    {
        CardReset();
        sys_cmd = (CMD_FUNC|CMD_FUNC_CLOSE);
        system_state = SYSTEM_NODISC;
        play_state = VCD_STATE_IDLE;
        cd_type_loaded = CDUNKNOWN;
        return;
    }
    #endif
#endif

    #ifdef SUPPORT_MIDI //WSF 2004-5-30 18:18  
    if(gIsMidiSelMenu){  
        if((!Midi_pause_flag)&&(!iMidiSpeed)){    
            invalid_key();
            return;
            }
        }
    #endif
    
   #ifdef VCD_CDG_PLAY_CONTROL_BY_SETUPMENU     //linrc add 2004-11-5 9:45
    extern BYTE VcdControlFlag(); 
    if(VcdControlFlag()&&resumeMSF&&(sys_cmd=CMD_FUNC|CMD_FUNC_STOP))
    {        
        ircmd_resume();
        return;
    }
    #endif
    
    extern int auto_pause;

    #ifdef PROGRAM_SHOW_DISPLAY   //dingzhy 
    if ((full_scrn & PROGRAM)&&(t_disp))
            DispFadeOut();
    #endif

    #ifdef DISABLE_PLAY_AT_DVDREGIONERR  //oujx for tonic
    if(cd_type_loaded==CDDVD)
    if(dvd_error==REGION_ERR)
    {
        invalid_key();
        return;
    }
    #endif  
    #if defined(INTECH_DVD)||defined(LINKCONCEPT_DVD)
    if(cd_type_loaded == CDVCD20 && (play_state==VCD_STATE_NORMAL)&& IsPBCOn())
    {
      ircmd_default(); 
      return; 
    }
    #endif

#ifdef ALCO_DVD_UI
    if(((Is_JPEG_STATE())&&(!pFsJpeg->gbfsSlide))&&(pFsJpeg->ControlArea==CNT_AREA_DIR))
    {
        ircmd_select();
        return;
    }
#endif



#if defined(TOP_DOOR_LOADER)||defined(CHECK_PORTABLE_OPCLSW)              //gerry,2004/2/11 02:18と
    if((CDOpened())&&(full_scrn==0)
        #ifdef  DVB_DVD_8202 //jack add 2006/08/10
        &&(system_state!=SYSTEM_TS)
	    #endif
      )
    {
        invalid_key();
        return;
    }   
#endif//TOP_DOOR_LOADER

//#ifdef SUPPORT_MP4
#if defined SUPPORT_MP4 && defined DVD_SERVO //ycwen 2004/08/10

    extern UCHAR SrvIsStopped();
    extern void SrvReStartUp();

    // Before playing MP4, we make sure that the servo is not idle, in order to keep A/V sync after long term pause.
    if ( ( GetCurrentFileType() == CDROM_MP4 ) && SrvIsStopped() 
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
        && ( media_type != MEDIA_CARD ) 
#endif
#if defined STOP_LOADER                   //zhongshan add for mp4 cause a long time to respond play 05/03/16
        && (play_state == VCD_STATE_PAUSE)
#endif    
        )
    {    
        INT64 timeout;
        SrvReStartUp();
        printf("Start up servo\n");
        
        timeout = get_stc() + 10 * 90000;   // 10 seconds timeout
        while (get_stc() < timeout)
        {
            ServoDecMainLoop();
            if ( !SrvIsStopped() )
            {
                printf("Servo has started up\n");
                break;
            }
        }       
    }
#endif

#ifdef SUPPORT_MIDI_MENU_SEL
    extern UINT8 Midi_pause_flag;
    extern UINT32 midi_timenow;

    if((gIsMidiSelMenu)) 
    {
        if(Midi_pause_flag)
        {
            Midi_pause_flag =0;
            set_stc(midi_timenow);
        }

        iMidiSpeed = 0;

        OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);

        PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
      // 2004AUDDRV::MESSAGE_QUEUE  MidiAudioCtrl(FLOW, AUDIOPLAY, 0);
      #ifdef MESSAGE_QUEUE
        if (coding_mode_now & AUDIF_CODING_MODE_MP3) {
            DSP_AudioIOControl(FLOW,MP3TONORM, 0);  //special command for Midi-MP3 change to normal play, Jeff 20031119
        } else {    
            DSP_AudioIOControl(FLOW, AUDIOPLAY, 0);
        }
      #else        
        DSP_Midi_AudioIOControl(FLOW, AUDIOPLAY, 1); // axelchen 2006/1/2  for PAUSE<->PLAY rapidly
      #endif 

        if (play_state != VCD_STATE_PAUSE) {
            OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);

            return;
        }
    }
#endif

    #ifdef TEST_SERVO
    {
        extern UINT32 save_srn_start_t;
        extern UINT32 dwLayerLBA;
        UINT32  iTime = 0;
        static  UINT32  iTime0=0;
        
        if (iTestServoMode != 2) {
            if (action_click>0) {
                iTime = get_rtc_val();
                if ( (iTime - iTime0) > 100) {
                    ClearOsdMsg(2);
                    iTime0 = 0;
                    action_click = 0;
                    set_rtc_val(0);
                    save_srn_start_t = 0;
                } else {
                    iTime0 = iTime;
                    save_srn_start_t = iTime;
                }
            } else {
                ClearOsdMsg(2);
                iTime0 = 0;
                set_rtc_val(0);
                save_srn_start_t = 0;
            }
        
            if (iTime>=TEST_SERVO_RUN_TIME) {
                extern UINT32 dwDiscLBA; //disc last LBA got from servo
                UINT32  iTestLBA;

                //do FULL STROKE testing
                action_click=0;
                iTestServoMode = 2;
                iTestServoCount = 0;
                psprintf(RegionValStr[REGION2], "1/2 FULL STROKE:%05d", iTestServoCount);
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);

                //do 200000 times full stroke
                for (iTestServoCount=0; iTestServoCount<=400000; iTestServoCount++) {
                    iTestLBA = get_stc_val_32();
                    iTestLBA %= dwDiscLBA;
                    
                    if(iTestServoCount%2 == 0)
                    ran_read(pwb, l2msf(0), 2048);
                    else
                    {
                        if(cd_type_loaded==CDDVD)
                        ran_read(pwb, l2msf(dwLayerLBA), 2048);
                        else
                        ran_read(pwb, gettrkmsf_leadout(), 2048);
                    
                    }
                    psprintf(RegionValStr[REGION2], "1/2 FULL STROKE:%06d LBA:0X%08x", iTestServoCount, iTestLBA);
                    PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
                    polling_osd(1);
                }
                iTestServoMode = 0;
                iTestServoCount = 0;
                return;
            } else {
                //display FULL STROKE
                if (action_click) {
                    psprintf(RegionValStr[REGION2], "1/2 FULL STROKE:%d SECONDS", (iTime/100));
                    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
                    return;
                }
            }
        } //if (iTestServoMode != 1) {
    }
    #endif //#ifdef TEST_SERVO

    if ( (system_state==SYSTEM_NODISC) && (play_state==VCD_STATE_STOP) ) { //Jeff 20030528
        system_state = SYSTEM_READ_TITLE;
        return;
    }

#ifdef SDRAM_16Mb_Mode
    if (prog_state)
        prog_state=0;
#endif

#ifdef  SUPPORT_BOOK
    //Jeff 200204120
    if (full_scrn&MARK) {
        if ( (adv_search_time==0) || (adv_search_time==1) ) {
            if ( (play_state!=VCD_STATE_PAUSE) &&
                (play_state!=VCD_STATE_SLOW)
                )
            {
                book_func_play();
                return;
            }
        }
    }
#endif

    if(Vobu_still)
    {
        P_vobu=1;
        return;
    }

    if(play_state==VCD_STATE_MP3_FILELIST)
    {
        OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);

        PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);         //wthsin,2004/8/10 06:09pm
        ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);    //Jeff 20010814
    }else if( (play_state==VCD_STATE_IDLE)||(play_state==VCD_STATE_NORMAL) )
    {
        if(bIntro)
        {
            bIntro=0;

            OSD1000ISP_STATUS(OSDISP_SEQPLAY, OSDIR_GLOBAL);

            PrintOsdMsg(STR_OS_SEQUENCE,REGION1,1,0);
        }else if ( ((full_scrn&PROGRAM)==0)
        #ifndef JPG_OLD_PARSER_FLOW //winking.J add For Qisheng 2006-7-14 20:17
             &&(pFsJpeg->g_nJpegMode != JPEG_FULL_SCREEN_MODE)
        #endif
        )
        {
            #ifdef SUPPORT_MIDI_MENU_SEL 
            if(gIsMidiSelMenu)
            {
                ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);
            } else
            #endif
            
        //wanghaoying 2005-1-14 17:14 delete for nobody use that
        //#ifdef PLAY_NO_SELECT_FUNC //zhaoyanhua 2004-5-18 9:33
            //play only has play function,can not change to SELECT function
          //  if (cd_type_loaded == CDROM)
           //     ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);    //Jeff 20010814
           // else
        //#endif
        
            //yw 021007
            #ifdef PMP_UI
            //printf("ircmd_play pmp_enable_user_flag(PMP_USER_AUTO_PLAY)\n");
            pmp_enable_user_flag(PMP_USER_AUTO_PLAY);
            #endif
            ircmd_select();

#ifdef    SUPPORT_INSIDE_GAME
if (system_state==SYSTEM_NODISC)
 { 
   full_scrn = 0;  //Maoyong 2004-8-11 23:02 for clear setup menu, must place before ClearOsdMsg
    ClearOsdMsg(0);
    t_disp = 0;
    browser = read_iso9660;
    cd_type_loaded=CDROM;
    cd_type=CDROM;
    play_state=VCD_STATE_CLOSE;
    Mp3ReadFinish = 0;//liweihua 2004-5-13
    memset(pFsJpeg, 0, sizeof(FSJPEGDATA));//liweihua add 2004-5-8 9:11
    system_state=SYSTEM_BROWSE;
    sys_cmd=CMD_FUNC|CMD_FUNC_CLOSE; 
    play_inside_game=1;
 } 
#endif                                
            return;

        }
        #ifndef JPG_OLD_PARSER_FLOW //winking.J add For Qisheng 2006-7-14 20:17
        else if(pFsJpeg->g_nJpegMode == JPEG_FULL_SCREEN_MODE)
		{
			ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);
        	return;
		}        
        #endif
    }else if(play_state==VCD_STATE_STOP) {
        if(!user_mute) {
            AUDIF_Demute();//2004AUDDRV AudioDemute();
        }
#if !defined(IR_PLAY_RESUME_PAUSE_SELECT)
    }else if( (play_state==VCD_STATE_PAUSE)||(play_state==VCD_STATE_SLOW)||adv_search_time) {
#else//#if !defined(IR_PLAY_RESUME_PAUSE_SELECT)
    }else if( ((play_state==VCD_STATE_PAUSE)&&(full_scrn&SETUP)!=(0x01<<2))||(play_state==VCD_STATE_SLOW)||adv_search_time) {//nono 2002-3-12 add (full_scrn&SETUP)==0) for PLAY==SELECT
#endif//#if !defined(IR_PLAY_RESUME_PAUSE_SELECT)
        if(auto_pause)
        {
            auto_pause=0;
            timeout_playback=0;
        }
        chg2normal_play(FAST2NORM|PAUSE2NORM|SLOW2NORM,REALPLAY);
        pe_run=1;
        //PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
#if !defined(IR_PLAY_RESUME_PAUSE_SELECT)
#ifndef FUSS_DVD

#ifdef OSD_Goto_Disable   //yw 020913

        OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);

        PrintOsdMsg(STR_OS_PLAY ,REGION1,1,0);
#else//#ifdef OSD_Goto_Disable   //yw 020913
        if (full_scrn&GOTO)
            search_func_select();
#endif//#ifdef OSD_Goto_Disable   //yw 020913

#endif//#ifndef FUSS_DVD
#endif//#if !defined(IR_PLAY_RESUME_PAUSE_SELECT)
    }else if( (play_state==VCD_STATE_PREVIEW)||(play_state==VCD_STATE_9FRAMES) )
    {
        
        playmode_sel(RESUME);
        ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);
        return;
    }

    else if(full_scrn&SETUP)
    {
        ircmd_select();
        return;
    }



    //special as enter key for program function
    /**********************************************/
    /*      ircmd_play()                          */
    /*      Handle with prog function             */
    /*      Modified by jjding 2001/02/17         */
    /**********************************************/
#ifdef IR_PROG_ON
    if(full_scrn & PROGRAM)
    {
#ifdef IRCMD_DBG
        printf("prog play1\n");
#endif

        prog_func_play();
        prog_func_off();
        
#ifdef DISPLAY_CD_TEXT          //lizhx add 2004/09/06
osd_init_CDText();
show_CDText( v11_trk_now );
//printf("here it is@@@@@@@@@@@\n");
#endif

#ifdef IRCMD_DBG
        printf("prog play2\n");
#endif

        if(prog_cnt)
        {
#ifdef IRCMD_DBG
            printf("prog play3,%d\n",prog_cnt);
#endif

        #if defined(ALWAYS_SHOW_PROG)    //wthsin 03/08/18  
            PrintOsdMsg(STR_OS_PROGPLAY,REGION1,0,0); 
        #else
            {
            OSD1000ISP_STATUS(OSDISP_PROG_PLAY, OSDIR_PROGRAM);

            PrintOsdMsg(STR_OS_PROGPLAY,REGION1,3,0);//nono 2-7-9 22:05
            }
        #endif   

#ifdef ALCO_DVD_UI
            resumeMSF = 0; //Jack added 04/11/08!!!
#endif
            rep_mode=REPEAT_IDLE;
            pbcoff_init();
            playmode_sel(PROGRAM);
            ircmd_post_func(CMD_FUNC | CMD_FUNC_PRG);

#ifdef IRCMD_DBG
            printf("prog play4\n");
#endif
        #ifdef NEW_DISPLAY_METHOD
        if((t_disp) || (cd_type_loaded==CDDA))
            DispPolling(0);
        #endif
        
        }

#ifdef NO_PROG_CNT_PLAY_KEY_WILL_GOTO_PLAY        
        else if((resumeMSF)&&(play_state==VCD_STATE_STOP)&&(!full_scrn))
        {
            
            ircmd_resume();
            #ifdef NEW_DISPLAY_METHOD
            if((t_disp) || (cd_type_loaded==CDDA))
            {
                old_disp_time=0;
                DispPolling(0);
            }
            #endif
            return;
        }
        else if(!((play_state==VCD_STATE_STOP)&&(!full_scrn)))
#endif//#ifdef NO_PROG_CNT_PLAY_KEY_WILL_GOTO_PLAY         

        return;
    }
#endif//IR_PROG_ON
    /****************************************************************/

    if (play_state==VCD_STATE_STOP)
    {
        int id;

#ifndef DVD_SEQ_PLAY
        if(IsPBCOn())
#else
            if(IsPBCOn()|| dvd_menu_play )
#endif
            {
                #ifdef ALCO_DVD_UI
                id=STR_OS_PLAY; 
                #else
                id=STR_OS_MENUPLAY;
                #endif
                OSD1000ISP_STATUS(OSDISP_MENUPLAY, OSDIR_MENU);
            } else if(prog_cnt) {          //zhyf 1-3-2 20:37
                id=STR_OS_PROGPLAY;

                OSD1000ISP_STATUS(OSDISP_PROG_PLAY, OSDIR_PROGRAM);
            } else if(shuffle_flag==1) {
                id=STR_OS_RANDOM;

                OSD1000ISP_STATUS(OSDISP_RANDOM, OSDIR_GLOBAL);
            } else {
                #ifdef ALCO_DVD_UI
                id=STR_OS_PLAY; 
                #else
                id=STR_OS_SEQUENCE;
                #endif 
                OSD1000ISP_STATUS(OSDISP_SEQPLAY, OSDIR_GLOBAL);
            }

#ifdef SDRAM_16Mb_Mode//for avoid stop->play "SEQ PLAY" can't fade away.nono 2004-5-6 2:42
            PrintOsdMsg(id,REGION1,2,0);
#else
            PrintOsdMsg(id,REGION1,1,0);
#endif

            if(prog_cnt)
                ircmd_post_func(CMD_FUNC | CMD_FUNC_PRG);
            else
            {
                dvd_title=1;
                dvd_chapter=1;
#ifdef ALCO_DVD_UI
                old_disp_time=0;//Jack added 04/11/02 for stop--->display then osd has a short showing error.
#endif
                ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);//jhuang 891009
            }
            
            #ifdef NEW_DISPLAY_METHOD
            if((t_disp) || (cd_type_loaded==CDDA))
                DispPolling(0);
            #endif
    }

    else if (CDOpened())
    {
        ircmd_trayin();
        //PrintOsdMsg(STR_OS_PLAY,REGION0,1,0);
        //PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
        //close_tray(0);
        //play_state = VCD_STATE_CLOSE;
    }
    else if (IsAVDPaused())
    {
        ircmd_step();
    }

    #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
    if ( (media_type==MEDIA_CARD) && CARDIsPlugIn() ) {
        if (play_state==VCD_STATE_STOP) {
            system_state = SYSTEM_BROWSE;
            ircmd_callback_check = fs_callback_check;
        }
    }
    #endif
    /*
#ifdef OP_UI  //feeling 2004-05-14
    is_change_play_state=1;
    ircmd_display();
    if(!t_disp)
            ircmd_display();
    is_change_play_state=0;
#endif
*/
}


void    ircmd_step(void)
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
    int inv=0;
  //wangap add for when dvd-audio no step   
     if(AOB){
   invalid_key();
   return;
   }

#ifdef DSI_NOVIDEO_STEP_INVALID//For hyoptics nono 2004-8-4 15:37
   if(PE_DSI_novideo())
   {
       invalid_key();
       return;
   }
#endif

    //terry,2-5-11 11:27
    //reduncy code , but yuxing use step key directly
    //I will contact yuxing : don't revise step, 0512 ,
    if ((HL_exist&& !DVD_check_state()) || UOP_check(UOP_PAUSE) )
    {
        inv=1;
    }else 
#ifdef SUPPORT_FILE_SYSTEM_MODE // nono 20030807
    if ( (cd_type_loaded==CDROM) && ( !Is_OTHER_STATE() ) ) 
#else
    if(cd_type_loaded==CDROM)
#endif
    {
            inv=2;
    }

    if(inv==0)
    {
        // 2004/12/08 yltseng, if it is in FB/FW state now, we first restore state to normal
        // 2005/04/07 tomcat, if we change from PAUSE to normal play before changing to step, 
        //                    it may decode several frames in the interval time.
        extern void chg2normal_play(UINT8 md,UINT8 realplay);
        chg2normal_play( FAST2NORM /*| PAUSE2NORM*/ | SLOW2NORM, 0 );

        // audio
        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
        AUDIF_Set_Pause();//2004AUDDRV AudioSetPause();

        // av decoder
        avd_play_frame(1);
        play_state = VCD_STATE_PAUSE;
        //terry,2002/9/13 04:04PM
        //de-still
        if(Vobu_still)
            P_vobu=1;

     OSD1000ISP_STATUS(OSDISP_STEP, OSDIR_PAUSE_STEP);

        PrintOsdMsg(STR_OS_STEP,REGION1,0,0);
    }else if(inv==1)
    {
        invalid_key();
    }
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

void    ircmd_default(void)
{
    if(pFsJpeg->List.s.header==LIST_PLAY)
        {
          invalid_key();
          return;
        }
    ircmd_post_func(CMD_FUNC | CMD_FUNC_DEFAULT);
    
    //ircmd_post_func(CMD_FUNC | CMD_FUNC_DEFAULT);
}
/*
* ircmd_stop ,move to stop.c
*/
#include "stop.c"

//ircmd_display_format_toggle
//ircmd_p_scan
//ircmd_chg_dac
//move to ircmd_video.c
#include "ircmd_video.c"

#ifdef   FIX_NOT_PAUSE_WHEN_PLAY_JPEG//tianye 200607
UINT8  flag_pause  ;
#endif// end=> #ifdef   FIX_NOT_PAUSE_WHEN_PLAY_JPEG

void    ircmd_play_pause(void)
{   

#ifdef   FIX_NOT_PAUSE_WHEN_PLAY_JPEG//tianye 200607

	if((play_state==VCD_STATE_PAUSE)&&(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))
	{
	    flag_pause  = 1;

	}
	else
	{
	    flag_pause  = 0;

	}
//printf("                                                flag_pause    :%d \n",flag_pause);//
#endif// end=> #ifdef   FIX_NOT_PAUSE_WHEN_PLAY_JPEG



#ifdef OP_DVD5121_PANEL//qinhua ,add 2005-9-5 22:34

  if (regs0->iop_data[6]==IR_ADDR_PATT)
 {   
 	if( (pressed_flag!=1) ) 
    {
         pressed_flag = 1;
        return;
    }
    else
    {
         pressed_flag = 0;
     }

}

#endif 
 // printf("5.full_scrn=%x\n",full_scrn);
#ifdef QSI_PLATFORM //qsi: added by johnson 20040811
    #ifdef SUPPORT_CARD_STORAGE
    if( (source_type_now == source_card) && (play_state == VCD_STATE_STOP))
    {
        CardReset();
        sys_cmd = (CMD_FUNC|CMD_FUNC_CLOSE);
        system_state = SYSTEM_NODISC;
        play_state = VCD_STATE_IDLE;
        cd_type_loaded = CDUNKNOWN;
        return;
    }
    #endif
#endif
#ifdef IR_PLAY_RESUME_PAUSE
    ircmd_play_resume_pause();
#else

    //  if(resumeMSF)
    //  {
    //    ircmd_resume();
    //    return;
    //  }
    //printf("5.full_scrn=%x\n",full_scrn);

    //terry,2002/9/16 03:14PM
//  if( (play_state==VCD_STATE_NORMAL)&&(full_scrn==0)&&(HL_exist==0)&&(bIntro==0)&&(Vobu_still==0) )//nono 2-7-8 13:29
    if( (play_state==VCD_STATE_NORMAL)&&(HL_exist==0)&&(bIntro==0)&&(Vobu_still==0) )//nono 2-7-8 13:29
    { //printf("7.full_scrn=%x\n",full_scrn);
        if((full_scrn==0)||(full_scrn&SCORE)	//gerry change it for score func,2004-3-9 9:15
        #ifdef GPS_DVD//frank.huang 050907
        ||(full_scrn&TOUCH_KEYBOARD)
        #endif
		)   //gerry change it for score func,2004-3-9 9:15
        ircmd_pause();
    }else if(full_scrn& GOTO)//nono 2-5-22 18:28
    { //printf("6.full_scrn=%x\n",full_scrn);
        ircmd_select();//nono 2-5-14 23:33
    }else
        ircmd_play();
    //printf("8.full_scrn=%x\n",full_scrn);

#endif
}

void ircmd_play_resume_pause(void)
{
    //printf("0.full_scrn=%x\n",full_scrn);
    //printf("resumeMSF=%d,resumeTRK=%d\n",resumeMSF,resumeTRK);
    //terry,2003/9/12 02:41PM,mark it
/*#ifdef VIRTUAL_KEYBOARD   // alan, 2003/8/16 05:02AM
    if (full_scrn&KEYBOARD)
    {
        ircmd_select();
        return;
    }
#endif*/
    //terry,2002/9/16 03:14PM
    
       #ifdef OP_STOP_PANEL_DISPLAY//lijd 2005-6-30 11:33			
		StopTimes=0;
#endif
    
    if ((play_state == VCD_STATE_NORMAL) && (is_menu() == 0)&&(bIntro==0)&&(Vobu_still==0)) //nono 2-7-8 13:29
    {
        //printf("1.full_scrn=%x\n",full_scrn);

        #ifdef VIRTUAL_KEYBOARD     //jxlan2005-1-19 16:56  for VIRTUAL_KEYBOARD IRC_PAUSE  reset
        if((cd_type_loaded == CDROM)&&(!(full_scrn & KEYBOARD)))
        #else
        if(cd_type_loaded == CDROM)
        #endif
        {
            // 2005/06/25 yltseng, in other file playing mode, FSGUI_IsSelectable is damaged in 16Mb mode,
            // so add more statement to avoid this situation
            if ( 
                 #ifdef SUPPORT_FILE_SYSTEM_MODE//nono add. for compile fail...5-7-13 1:40
                 (pFsJpeg->gifsFuncBtn != FS_FUNC_OTHER) && 
                 #endif
				#if defined GPS_DVD//frank.huang 050926 add for GPS_DVD
				(full_scrn!=TOUCH_KEYBOARD)&&
				#endif
                 (FSGUI_IsSelectable() || (full_scrn)) && (!bEqDisplay))
                ircmd_select();
            else
            {
                if (bEqDisplay)
                    cancel_sound();//NONO 2-5-19 21:00
                else if((JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode)&&(!Is_JPEG_SlideMode()))//nono 4-9-7 18:55 for eastech's bug. //kevinmonkey 050720 when slide show should execute pause
                {
                    ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY);
                }else

#ifdef ZOOM_DIRECT_STOP_SLIDE//nono 4-8-10 16:29
                if(jpg_slide_time == 0xffffffff)
                {
    
                 if(Is_JPEG_SlideMode())
                    {
                        jpg_slide_time = JPEG_SLIDE_TIME;//NONO 4-8-31 17:17
                         //ForceStopJpgSlide();
                        ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY);
                    }
                    
                }else
#endif                
#ifdef SUPPORT_MIDI// axel for FF -> play_pause execute pause 2004/8/17 
                    if (iMidiSpeed!=0)
                        ircmd_play();
                    else  
#endif //#ifdef SUPPORT_MIDI
#ifdef PMP_UI              /////////YANGLI MOD FOR PALYPAUSE 2005-7-18
                    if((pFsJpeg->gifsState != FS_STATE_MP3)
                       &&(pFsJpeg->gifsState != FS_STATE_JPEG)
                       &&(pFsJpeg->gifsState != FS_STATE_OTHER))
                    ircmd_play();
                    else
#endif /////////////#ifdef PMP_UI
                    ircmd_pause();
                
                //printf("2.full_scrn=%x\n",full_scrn);
            }
        }
#ifdef SUPPORT_BOOK     //wanghaoying 2003-8-13 12:11 added for idall
        else if (full_scrn&MARK) 
        {
            if ( (adv_search_time==0) || (adv_search_time==1) ) {
                if ( (play_state!=VCD_STATE_PAUSE) &&
                    (play_state!=VCD_STATE_SLOW)
                    )
                {
                    book_func_play();
                    return;
                }
            }
        }
#endif
#ifdef VIRTUAL_KEYBOARD
        else if( ((full_scrn)&& (!(full_scrn & KEYBOARD)) )||( (HL_exist)  && (!bEqDisplay)) ) //nono 02-05-11 for yuxing
#else//VIRTUAL_KEYBOARD
        else if ((((full_scrn)&&(!(full_scrn & SCORE))) || (HL_exist)) && (!bEqDisplay)//nono 02-05-11 for yuxing
				#ifdef GPS_DVD//frank.huang 050926 add for GPS_DVD
				&&full_scrn!=TOUCH_KEYBOARD
				#endif
				)
#endif//VIRTUAL_KEYBOARD
        {
           // printf("2.full_scrn=%x\n",full_scrn);
            ircmd_select();
        }
        else
        {
            if (bEqDisplay)
                cancel_sound();//NONO 2-5-14 18:11
            //printf("3.full_scrn=%x\n",full_scrn);
            ircmd_pause();
        }//nono 2-4-2 20:27
    }
//gerry modified it for select func,2004-5-25 16:34
        else if (((resumeMSF)&&(resumeMSF != 0xffffffff)) &&
        (play_state != VCD_STATE_FASTFORWARD) &&
        (play_state != VCD_STATE_FASTBACKWARD) &&
        (play_state != VCD_STATE_PAUSE) &&
        (Is_JPEG_STATE() == 0) &&
        #ifdef SUPPORT_NESGAME
        (Is_GAME_STATE() == 0) &&
        #endif
        (play_state != VCD_STATE_SLOW))
    {
//        printf("4.full_scrn=%x\n",full_scrn);
#ifndef VIRTUAL_KEYBOARD
        if (((HL_exist) && (is_menu() == 1)) || ((full_scrn) && (!(full_scrn & PROGRAM))))//nono 2-5-10 16:04
#else//VIRTUAL_KEYBOARD
        if (( HL_exist && (is_menu() == 1)) || ( full_scrn && (!(full_scrn & (PROGRAM|KEYBOARD) ))))//nono 2-5-10 16:04
#endif//VIRTUAL_KEYBOARD
        {
  //        printf("6.full_scrn=%x\n",full_scrn);
            ircmd_select();
            
        }
        else if ((full_scrn & PROGRAM) == 0x01)
            ircmd_play();
        //wanghaoying 2005-3-7 16:34, delete the 'EASTWIN_PORTABLE_DVD' limitation,
        //correct the error : define IRC_PAUSEPLAY to resume when play mp4 files pre-stop.
        //Notice: mpg files no pre-stop state and function now.
        else
        //#ifdef EASTWIN_PORTABLE_DVD
            if ((GetCurrentFileType() == CDROM_MP4)&&(cd_type_loaded == CDROM))
                ircmd_select();//tulijuan040827for divx stop press play display forbid
            else
        //#endif
            ircmd_resume();
             return;
    }
    else if ((!resumeMSF) && (play_state == VCD_STATE_STOP) && (full_scrn & GOTO))//nono 2-5-15 14:51
        ircmd_select();
    #ifdef IR_PLAY_RESUME_PAUSE_SELECT//NONO 20021205
    else if((full_scrn>PROGRAM)||((full_scrn&PROGRAM)&&(is_clear_pos())))
    {
        ircmd_select();
    }
    #endif
    else
        ircmd_play();
}

void    ircmd_play_resume(void)
{

#ifdef ALCO_DIVX_UI//shenyj add for alco 12/12
if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4))
{
    if((system_state==SYSTEM_SETUP_BROWSER)||(play_state==VCD_STATE_READTOC))
    {
        invalid_key();
	    return; 
    }
}
#endif 

#ifdef DIVX_STOP_TO_PLAY_DELAY
if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4))
{
    if(divx_stop_to_play_delay_timer!=DIVX_STOP_TO_PLAY_DELAY_CNTTT)
    {
        //invalid_key();
        return;
    }  
}
#endif

#ifdef ALCO_DVD_UI//shenyj add for alco 11/29//hope it can be move to invalidkey_tbl...
if(((cd_type_loaded==CDROM)&&(Is_MP3_STATE()))&&(play_state==VCD_STATE_NORMAL))
{   
    invalid_key();
    return;
}
#endif

#ifdef OP_STOP_PANEL_DISPLAY//lijd 2005-6-30 11:33          
        StopTimes=0;
#endif
#ifdef TEST_VFD_PANNEL_AND_KEY//lijd 2005-5-8 13:59   
    if((Test_Front_Panel_flag==1)&&(Test_Stop_flag==0))
        {               
            TestVFDEveryDot();
            return;
        }        
    else if((Test_Front_Panel_flag==1)&&(Test_Stop_flag==2)) 
       {
            Test_Front_Panel_flag=0;
            Test_Stop_flag=0;   
            return;
       }
#endif  
    
#ifdef INVALID_WHEN_WRONG_REGION            //dingzhy for dongli  2/2/2004 12:44PM
if((dvd_error==REGION_ERR)&&(system_state!=SYSTEM_OPEN))
{
            invalid_key();
            return;
        }
#endif

#ifdef AUDIO_SHOW_SAVER
    if((bDisableGUI)&&(cd_type_loaded==CDROM) && (cd_subtype ==CDROM_MP3))
    {
        return;
    }
#endif
/*	if(UOP_check(UOP_ST_OFF))//linrc add it.for philips FLLC test.2006-4	
	{							//linrc mark for 8202L 2006-6-13 13:31
		invalid_key();
        return;
	}*/

    //printf("resumeMSF=%d,resumeTRK=%d\n",resumeMSF,resumeTRK);
    //if((resumeMSF)&&(play_state==VCD_STATE_STOP)&&(!full_scrn))//&&(is_menu()==0))           
#if defined(DVD_RTN_MENU_RESUME)//2004.03.02 Maoyong for all customers to use Menu resume
    if((pDSV->dMenuPgc_flag == 0)&&(resumeMSF)&&(!full_scrn)&&((play_state==VCD_STATE_STOP)||((cd_type_loaded==CDDVD)&&(is_menu()==1) )) )//hq add for Ngailik, add resume play when pressing the PLAY key in DVD Menu 2004-2-24 19:53
#else    
    if((resumeMSF)&&(play_state==VCD_STATE_STOP)&&(!full_scrn))//&&(is_menu()==0))   
#endif  
    {
        ircmd_resume();
        return;
    }
#ifdef FUSS_DVD
    else if((full_scrn& GOTO)&&((play_state == VCD_STATE_NORMAL)||(play_state == VCD_STATE_STOP)))
        ircmd_select();//nono 2-5-14 23:33
#else

#ifndef  OSD_Goto_Disable
    else if(full_scrn& GOTO)
        ircmd_select();//nono 2-5-14 23:33
#endif
#endif


    else
        ircmd_play();
}

#if 0//def SUPPORT_USB
BYTE usb_card_pause_flag;// lijd 2004-9-29 11:25 //sunzhh modify 2005-3-11 because it results in many bugs and it no use now.
#endif
void run_pause(int show)
{

#ifdef CONTINUOUS_NUM_KEY_SELECT //Jack added 04/11/13
    if(ir_num_timer)
      ir_continuous_num_clr();
#endif

#ifdef REM_JPEG_DECODE_STATE
    if(jpeg_in_decode)
    {
        invalid_key();
        return; 
    }
#endif
    
    chg2normal_play(FAST2NORM|SLOW2NORM,TRANSFER);
    if(play_state==VCD_STATE_PAUSE)
    {
#if 0//def SUPPORT_USB//LIJD 20041008 //sunzhh modify 2005-3-11 because it results in many bugs and it no use now.
         usb_card_pause_flag=0;
#endif
#ifdef DVD_AUDIO
        if ( (pDSV->CurrDomain==TT_DOM) && (pDSV->tt_info.dTT_PB_TY&0x80) )
        {
            ircmd_play();
        } else
#endif
        {
#ifdef ONLY_PAUSE//nono 2-7-7 17:27
            {;}
#else
       #if defined(PAUSE_FOR_AUDIO_ONLY)     //kubby,to cancel PLAY when only audio,but cancel STEP unexpectedly,3-9-15 23:43       
       //#if defined(MINTON_DVD)     //wthsin 03/08/18, 
       //   if(Is_MP3_STATE())
       if(audio_only==1)
            {;}
            else
       #endif
            {   
//        #if defined(DESAY_DVD)      //wanghaoying 2003-8-20 20:18
//                ircmd_play();
//        #else
                #ifdef SUPPORT_USB//liweihua add 2004-1-15 10:56
                if(media_type == MEDIA_CARD)
                    ircmd_play();
                else
                #endif
                if(audio_only==1)
                    #if defined(ALCO_DVD_UI)
                    invalid_key();
                    #else    
                    ircmd_play();
                    #endif
                else
                    ircmd_step();
//        #endif
            }
#endif
        }
    }else
    {
        #if 0//def SUPPORT_USB//lijd 20041008 //sunzhh modify 2005-3-11 because it results in many bugs and it no use now.
         usb_card_pause_flag=1;
        #endif
        if(show)
        {
            OSD1000ISP_STATUS(OSDISP_PAUSE, OSDIR_PAUSE_STEP);
        #ifndef PLAYMODE_RUN_PAUSE//libing 2005-5-16 14:55
            PrintOsdMsg(STR_OS_PAUSE,REGION1,0,0);
        #endif    
        }
     #ifdef EASTECH_DVD_DP2070_D
        pause_flag = 1; //kevinmonkey 050720, when we press vfd button, we call ir function directly without run through ir 
                        //parser, and setting pause_flag for JPEG slide show is done in ir parserxxxxx what?
     #endif  //#ifdef EASTECH_DVD_DP2070_D
        
        if(!Is_JPEG_STATE()) //ycwen 2005/8/9 don't change AV State when JPEG, may cause bug
            Pause();
            
        play_state = VCD_STATE_PAUSE;
    }
}


void run_only_pause(int show)
{
    chg2normal_play(FAST2NORM|SLOW2NORM,TRANSFER);
    if(play_state==VCD_STATE_PAUSE)
    {

#ifdef DVD_AUDIO
        if ( (pDSV->CurrDomain==TT_DOM) && (pDSV->tt_info.dTT_PB_TY&0x80) )
        {
            ircmd_play();
        } else
#endif
        {
#if defined(ONLY_PAUSE)||defined(MP3_CD_ONLY_PAUSE)//nono 2-7-7 17:27
            {;}
#else
            if(audio_only==1)
                ircmd_play();

#endif
        }
    }else
    {

        if(show)
        {
            OSD1000ISP_STATUS(OSDISP_PAUSE, OSDIR_PAUSE_STEP);

            PrintOsdMsg(STR_OS_PAUSE,REGION1,0,0);
        }
        
       if (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)    //jiangxl  2005-3-1 9:28  when playing JPEG,can not audio pause.   
       {}
       else
       {   
           Pause();
       }
        play_state = VCD_STATE_PAUSE;
    }
}

/*
** only_pause
*/
void ircmd_only_pause(void)
{
        #ifdef AD_TCL//2004-3-22 13:18 lijd
            jpg_ps=0;
        #endif
        #ifdef TEST_SERVO
    {
        extern UINT32 save_srn_start_t;
        UINT32  iTime = 0;
        static  UINT32  iTime0=0;
        
        if (iTestServoMode != 3) {
            if (action_click>0) {
                iTime = get_rtc_val();
                if ( (iTime - iTime0) > 100) {
                    ClearOsdMsg(2);
                    iTime0 = 0;
                    action_click = 0;
                    set_rtc_val(0);
                    save_srn_start_t = 0;
                } else {
                    iTime0 = iTime;
                    save_srn_start_t = iTime;
                }
            } else {
                ClearOsdMsg(2);
                iTime0 = 0;
                set_rtc_val(0);
                save_srn_start_t = 0;
            }
        
            if (iTime>=TEST_SERVO_RUN_TIME) {
                //do MTBM testing
                action_click=0;
                iTestServoMode = 3;
                iTestServoCount = 0;
                psprintf(RegionValStr[REGION2], "MTBM:%010d", iTestServoCount);
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
                ircmd_eject_toggle();
                polling();
                ShowTitle();
                polling();
                return;
            } else {
                //display FULL STROKE
                if (action_click) {
                    psprintf(RegionValStr[REGION2], "MTBM:%d SECONDS", (iTime/100));
                    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
                    return;
                }
            }
        } //if (iTestServoMode != 3) {
    }
    #endif //#ifdef TEST_SERVO
    
#ifdef IRCMD_DBG
    printf("=================pause===================\n");
    //printf("1.IsAVDPaused()=%d\n",IsAVDPaused());
#endif
    if ((HL_exist&& !DVD_check_state()) || UOP_check(UOP_PAUSE))
        invalid_key();
    else
    {

#ifdef AUDIO_SHOW_SAVER //kono 1007 2001
        if( bDisableGUI) return;
#endif
        run_only_pause(1);
    //printf("2.IsAVDPaused()=%d\n",IsAVDPaused());
    }
    /*
#ifdef OP_UI  //feeling 2004-05-14
    is_change_play_state=1;
    ircmd_display();
    if(!t_disp)
        ircmd_display();
    is_change_play_state=0;
#endif*/
}

/*
** pause
*/
void ircmd_pause(void)
{

#if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) ////kenny add 2005/6/16
if(pFsJpeg->gifsState == FS_STATE_INIT)
              return;
#endif

#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef SUPPORT_MIDI_MENU_SEL
    extern UINT8 Midi_pause_flag;
    extern UINT32 midi_timenow;

    if((gIsMidiSelMenu)) 
    {
        if (!((bMidiPlayerBoolean)&&(midiState == MIDI_STATE_PAYLOAD)))
        {
            invalid_key();
            return;
        }                    //ouyang 2004.07.31
        midi_timenow = get_stc_32();
        Midi_pause_flag =1;
    }
#endif
#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif

#ifdef AD_HL_USE   // lxg 2006-7-25 07:41
if((play_state==VCD_STATE_PAUSE)&&
	(( cd_type_loaded == CDROM )&&( !(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER) )||(cd_type_loaded==CDDA)))
{
	 invalid_key();
    return;
}
#endif

#if defined(ALCO_8200P_MULTIKEY)&&defined(NEED_DIFF_IR_PANEL_KEY)
    if(((play_state==VCD_STATE_STOP)||(play_state==VCD_STATE_OPEN)||(play_state==VCD_STATE_IDLE)) ||
      ((play_state==VCD_STATE_MP3_FILELIST)&&Is_JPEG_STATE()&&(!pFsJpeg->gbfsSlide))
      /*|| (play_state==VCD_STATE_PAUSE)*/)
    {
        panel_key_flag = 0;
        if(play_state != VCD_STATE_OPEN)//for Macrovision display!!!
            invalid_key();
        return;
    }
#endif

    #ifdef TEST_SERVO
    {
        extern UINT32 save_srn_start_t;
        UINT32  iTime = 0;
        static  UINT32  iTime0=0;
        
        if (iTestServoMode != 3) {
            if (action_click>0) {
                iTime = get_rtc_val();
                if ( (iTime - iTime0) > 100) {
                    ClearOsdMsg(2);
                    iTime0 = 0;
                    action_click = 0;
                    set_rtc_val(0);
                    save_srn_start_t = 0;
                } else {
                    iTime0 = iTime;
                    save_srn_start_t = iTime;
                }
            } else {
                ClearOsdMsg(2);
                iTime0 = 0;
                set_rtc_val(0);
                save_srn_start_t = 0;
            }
        
            if (iTime>=TEST_SERVO_RUN_TIME) {
                //do MTBF testing
                action_click=0;
                iTestServoMode = 3;
                iTestServoCount = 0;
                psprintf(RegionValStr[REGION2], "MTBF:%010d", iTestServoCount);
                PrintOsdMsg(STR_OS_SPACE, REGION2, 0, 1);
                //ircmd_eject_toggle();
                polling();
                ShowTitle();
                polling();
                return;
            } else {
                //display FULL STROKE
                if (action_click) {
                    psprintf(RegionValStr[REGION2], "MTBF:%d SECONDS", (iTime/100));
                    PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
                    return;
                }
            }
        } //if (iTestServoMode != 3) {
    }
    #endif //#ifdef TEST_SERVO

#ifdef IRCMD_DBG
    printf("=================pause===================\n");
    //printf("1.IsAVDPaused()=%d\n",IsAVDPaused());
#endif
    
    #ifndef JPG_OLD_PARSER_FLOW                
        if(Is_JPEG_STATE())
        {
            ircmd_post_func(CMD_FUNC|CMD_FUNC_PAUSE);
			//jiangxl mark it. on 2006-8-9
            //PrintOsdMsg(STR_OS_PAUSE,REGION1,0,0);//jiangxl for for fixing the bug that showing pause all time after set next command at pause state  
            return;    
        }
    #endif
    
#ifdef   FIX_NOT_PAUSE_WHEN_PLAY_JPEG

if((flag_pause  ==  1 )&&(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))
{
      #ifdef IRCMD_DBG
        printf("=================       FIX_NOT_PAUSE_WHEN_PLAY_JPEG      ===============\n");
        //printf("1.IsAVDPaused()=%d\n",IsAVDPaused());
	#endif
       return;    
}
#endif// end=> #ifdef   FIX_NOT_PAUSE_WHEN_PLAY_JPEG


#if 1//def VOBU_STILL_NO_PAUSE    //nono open it.20050203
    if(Vobu_still)  //when vobu still play,if pause,we can not use play key 
    {               //play again,so linrc modify it 2005-1-29 13:45
        invalid_key();
        return;
    }
#endif
    
#ifdef DVD_HL_SUPPORT_PAUSE    //terry,2004/1/7 11:57AM
    if ( (HL_exist&& (pe_run==0)) || UOP_check(UOP_PAUSE))
#else
        if ( (HL_exist&& !DVD_check_state()) || UOP_check(UOP_PAUSE))
#endif  
        invalid_key();
    else
    {
#ifdef AUDIO_SHOW_SAVER //kono 1007 2001
        if( bDisableGUI) return;
#endif
        run_pause(1);
    }
    //printf("2.IsAVDPaused()=%d\n",IsAVDPaused());
/*
#ifdef OP_UI  //feeling 2004-05-14
    is_change_play_state=1;
    ircmd_display();
    if(!t_disp)
        ircmd_display();
    is_change_play_state=0;
#endif*/
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

void show_skip_osd(UINT8 show,UINT8 id)
{
    //wanghaoying 2003-9-6 added,单曲重复时上/下一曲OSD闪烁
    if(rep_mode==REPEAT_TRACK)
        return;

    // 2004/04/15 yltseng mark, in order to let ( cd_type_loaded == CDROM ) can call this function
    //if(cd_type_loaded !=CDROM)
    //{
#ifdef SHOW_PROG_ITEM                
        if(prog_cnt)
        {           
            OSD1000ISP_STATUS(OSDISP_PROG_PLAY, OSDIR_PROGRAM);

            psprintf(RegionValStr[REGION1]," %02d",prog_index);
            PrintOsdMsg(STR_OS_PROGPLAY,REGION1,1,1);
            return;
        }
#endif        
        if(IsPBCOn() || show || prog_cnt) PrintOsdMsg(id,REGION1,1,0);      /* alan 02-05-27 modified */
    //}
}


// 2004/09/10 yltseng, add this function to find out if this Next/Prev is invalid
int IsInvalidInNextPrev()
{

#ifdef SKYWORTH_DVD    //3-10-23 1:47张宇P
    if( rep_mode == REPEAT_TRACK )
    {
        invalid_key();
        return 1;
    }
#endif

    if( ( cd_type_loaded == CDROM ) && (
#ifdef SUPPORT_NESGAME
        ( pFsJpeg->gifsFuncBtn == FS_FUNC_GAME ) ||
#endif
        ( ( pFsJpeg->gifsFuncBtn != FS_FUNC_MP3 ) && ( pFsJpeg->gifsState == FS_STATE_LIST ) &&( JPEG_THUMBNAIL_MODE != pFsJpeg->g_nJpegMode ) ) ) )
    {
        invalid_key();
        return 1;
    }

    return 0;
}

#ifdef SUPPORT_DIVX6
//#include "divx6_if.h"
extern UINT32 divx6_menu_exist;
#endif

#ifdef SUPPORT_FILE_CHAPTER
UINT32  fileChangeChapter( UINT32 uiAction )
{
    UINT32 uiCurFileType;
    uiCurFileType = GetCurrentFileType();	//zhongshan for warning 2006-2-28 18:14
    int iCheckChangeChapter;

    iCheckChangeChapter = 0;

    //conditions checking if we should do chapter change checking...
    if(g_uChapterListAvailable != 0)
        iCheckChangeChapter = 1;

    #ifdef SUPPORT_QUICKTIME
    //qinhua,modify for m4a file reset,2006-2-18 11:39
    if(((IS_FILE_TYPE_QT())||(IS_FILE_TYPE_ND()))&&!(audio_only && IsM4AFileType())) 
        iCheckChangeChapter = 1;
    #endif  //#ifdef SUPPORT_QUICKTIME

    #ifdef SUPPORT_DIVX6
    if( uiCurFileType == CDROM_MP4 || uiCurFileType == CDROM_AVI )
        iCheckChangeChapter = 1;
    #endif  //#ifdef SUPPORT_DIVX6

    if(iCheckChangeChapter)
    {
        //printf_w( "*** before %d, ", pFsJpeg->g_uiCurChapter );
	#ifndef SUPPORT_DIVX6
       if ((g_uChapterListAvailable == 0)||
             ((pFsJpeg->g_uiCurChapter == (file_get_num_of_chapter()-1))&& (uiAction == CMD_FUNC_NEXT))||
             ((pFsJpeg->g_uiCurChapter == 0)&& (uiAction == CMD_FUNC_PREV)))
    #else   //SUPPORT_DIVX6 divx6 allows prev at chapter 0
        if (!divx6_menu_exist)
    #endif  //#ifndef SUPPORT_DIVX6
        {
            pFsJpeg->g_uiFileChangeChapter = 0xF;
            return FALSE;
        }
        
        switch( uiAction )
        {
        case CMD_FUNC_PREV:
            pFsJpeg->g_uiFileChangeChapter =2;
            /*if( pFsJpeg->g_uiCurChapter == 0 )
                return FALSE;
            
            pFsJpeg->g_uiCurChapter--;*/            
            break;
            
        case CMD_FUNC_NEXT:
            //printf("IR CMD NEXT \n");
            #ifdef SUPPORT_DIVX6
            if ((divx6_menu_exist == 1) && (g_uChapterListAvailable == 0))
            {
                pFsJpeg->g_uiFileChangeChapter =1;
            }
			else if( pFsJpeg->g_uiCurChapter >= file_get_num_of_chapter() )
			{
				pFsJpeg->g_uiFileChangeChapter = 0xF;
                return FALSE;
            }
            else
            #endif
            {
                pFsJpeg->g_uiFileChangeChapter =1;
	        }
            /*pFsJpeg->g_uiCurChapter++;
            
            if( pFsJpeg->g_uiCurChapter >= file_get_num_of_chapter() )
                return FALSE;*/
            break;

        default:
            return FALSE;
        }
        
        //printf_w( "after %d\n", pFsJpeg->g_uiCurChapter );

        /*pFsJpeg->g_uiFileChangeChapter   = TRUE;
        psprintf(RegionValStr[REGION1], "CHAPTER %d", pFsJpeg->g_uiCurChapter );
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);*/
            
        return TRUE;
    }
    
    return FALSE;
}
#else//#ifdef SUPPORT_FILE_CHAPTER
#define fileChangeChapter(...)  FALSE
#endif//#ifdef SUPPORT_FILE_CHAPTER


void    ircmd_next(void)
{

#ifdef ONLY_ONE_TRK_MP4_NEXT_IS_INVALID//shenyj add for alco 11/11
    if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4))
    {
        if(pFsJpeg->iso9660_file_cnt==1)
        {
            invalid_key();
            return ;
        }
    }
#endif
    
#ifdef OP_DVD5121_PANEL  //qinhua ,add 2005-9-5 22:34
  if (regs0->iop_data[6]==IR_ADDR_PATT)
 {
      
    if( (pressed_flag!=1) ) 
    {
         pressed_flag = 1;
          return;
    }
    else
    {
         pressed_flag = 0;
      }

}

#endif 

#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).

 #ifdef SUPPORT_NEXT_PREV_AUTO_PLAY_MP3 ////yangli add for in filemode next/prev/autoplay function
        auto_play_flag=1;
 #ifdef SUPPORT_MULTI_PARTITION
    if((pFsJpeg->gifsState == FS_STATE_MP3)||(pFsJpeg->gifsState == FS_STATE_JPEG)||(pFsJpeg->gifsState == FS_STATE_OTHER))
    {    
        next_flag=1; 
        osd_tog_region(1,OSD_OFF);
        HDDCard_return();       
            return;
        }
    else return;
#endif
#endif

#if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) //kenny add 2005 6/16

        
       // if((pFsJpeg->gifsState == FS_STATE_MP3) ||(pFsJpeg->gifsState == FS_STATE_JPEG) ||(pFsJpeg->gifsState == FS_STATE_OTHER))
        pmp_disable_user_flag(PMP_USER_PRESS_UP_DOWN__KEY);//kenny 2005/7/12
        pmp_enable_user_flag(PMP_USER_PRESS_NEXT_PREV_KEY);
        PMP_show_next_osd();           //////////////yangli 2005/8/10
        HDDCard_down();
       
        return;
   
#endif


#ifdef SUPPORT_MIDI_MENU_SEL   //ouyang add for invalid forward when press pause  04-9-28 15:192004-9-28 15:19
    if(gIsMidiSelMenu) 
    {
        if(Midi_pause_flag)
        {
            invalid_key();
            return;
        }
      }           
#endif

#ifdef FAT_Write_UI//SPHE8202_USB_Write     //wanghaoying 2005-7-28 11:02
    if(cd_type_loaded==CDROM)
    {
        if (full_scrn & PERIPHERAL)
        {
            full_scrn &= (~PERIPHERAL);
            osd_init();
            invalid_key();
            return;
        }
    }
#endif

#ifdef SUPPORT_MIDIDISK_TITLE
    if (bIsPlayMidiTitle)
    {
        invalid_key();
        return;
    }
#endif
#if defined(MP3_ONLY_STOP_TO_GUI)&&defined(MODIFY_MP3_ONLY_STOP_TO_GUI)//nono add 4-8-10 11:00
    if ( (Is_MP3_STATE())
      && (play_state == VCD_STATE_MP3_FILELIST) //only in FsMP3mainloop,can use "REPAB"
        )
    {
        invalid_key();
        return;
    }
#endif

    //Maoyong 2004-8-14 9:34, special process thumbnail menu for panel Prev/Next Key
    #ifdef JPEG_THUMBNAIL_MENU
    #ifdef ALCO_DVD_UI
     if(!pFsJpeg->gbfsPictureCD)
 	#endif
     {
    if(JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode){
        if(!ThunmnailChkValidPrevNext(IRC_NEXT))
            return;
    }
    }
    #endif

    if( IsInvalidInNextPrev() )
        return;

    // 2004/04/15 yltseng mark, no need now
/*
#ifdef SUPPORT_OTHER_NEXT_PREVIOUS  //wuxiaofeng 2004-03-16
        if(Is_OTHER_STATE() && pFsJpeg->gifsState==FS_STATE_LIST)
        {
            invalid_key();
            return ;
        }
#endif//#ifdef SUPPORT_OTHER_NEXT_PREVIOUS

#ifdef SKYWORTH_DVD    //3-10-23 1:47张宇P
        if(rep_mode==REPEAT_TRACK)
         {
              invalid_key();
              return;
          }
#endif         
*/

#ifdef NEXT_FORWARD_IN_A_KEY
    //if( (bIrSkipState==0)&&(key_data_flag==0) )
    if( (bIrSkipState!=2)&&(key_data_flag==0) )//2004-5-5 15:16
    {
         bIrSkipState = 2;
         rep_ir_times = 0;
         bIrSkipCnt = 0;
         return;
    }
    else
    {
         bIrSkipState = 0;
         rep_ir_times = 0;
         bIrSkipCnt = 0;
    }
#endif//NEXT_FORWARD_IN_A_KEY

    #ifdef SUPPORT_FILE_CHAPTER
    if( fileChangeChapter( CMD_FUNC_NEXT ) )
        return;
    #endif //SUPPORT_FILE_CHAPTER

#ifdef NEXT_CANCEL_ZOOM
    if(vpp_zoom!=0)  /* add by TOM */
    {
        vpp_zoom = 0;
        show_zoom(1);
    }
#endif

    //printf("v11_trk_now=%d > cd_trk_hi=%d cd_trk_lo_now=%d\n",v11_trk_now,cd_trk_hi,cd_trk_lo_now);
    if(play_state == VCD_STATE_PREVIEW)
    {
#ifdef DVD_PREVIEW_FUNCTION
        if(cd_type_loaded==CDDVD)
        {
            OSD1000ISP_STATUS(OSDISP_NEXT, OSDIR_NEXT);

            show_skip_osd(1,STR_OS_NEXT);
            AVD_SetMediaTimeout();
            PostCommand(CMD_FUNC | CMD_FUNC_NEXT);
            return;
        }else 
#endif      
        if((v11_trk_now-((v11_trk_now-cd_trk_lo_now)%9)+9) > cd_trk_hi) 
           return;
    }

        //PBC off
#ifdef IR_SHUFFLE_ON
        if(shuffle_flag)
        {
          #ifdef SHUFFLE_ACCOMPLISH_BY_ARITHMETIC                //wangmin add for the real shuffle when cd playing 051020
             if(cd_type_loaded==CDDA)
             {
               shuffle_track=shuffle_next(v11_trk_now);//,NOT_FS_SHUFFLE);
               #ifdef SHUFFLE_ABA_DEBUG                     
                   psprintf(linebuf,"shuffle_track= %d........\n",shuffle_track);
                   io_write_wait(linebuf);
               #endif
             }
          #else
            shuffle_flag=0;
            action_click=1;        // alan 0425
            ircmd_shuffle();
            return;
           #endif
        }
#endif

#ifdef KONKA_DVD//clead 20020820
        if (full_scrn&SETUP) {          //clead    20020821
            setup_func_nextpage();
            return;
        }
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT//Jack added 04/11/13
    if(ir_num_timer)
      ir_continuous_num_clr();
#endif 
            
        if(rep_mode==REPEAT_IDLE)
        #ifdef NEXT_PREV_NOT_STOP_PROG
        { 
            if(prog_cnt && (prog_index==prog_cnt))
            {
                invalid_key();
                return;
            }
            else
                prog_next();    
        }
        #else
            prog_next();
        #endif
        
#ifdef  STOP_IN_PROG_END //wuxiaofeng 2004-03-15
        if(sys_cmd==(CMD_FUNC | CMD_FUNC_STOP))
        {
            ircmd_post_func(sys_cmd);
            return;
        }
#endif//#ifdef  STOP_IN_PROG_END
#ifdef RECORD_PER_SECOND                    //avoid bug   gerry  2-12-4 9:48
        if ((cd_type_loaded==CDROM)&&(Is_MP3_STATE()))
         {
            resumeMSF=0;
         }
#endif

#ifdef FUSS_DVD_AVD276
        if(cd_type_loaded==CDDVD)
        {
            OSD1000ISP_STATUS(OSDISP_NEXT_CHAPTER, OSDIR_NEXT);

            show_skip_osd(cd_trk_now<cd_trk_hi,STR_TOS_NEXT_CHAPTER);
        }
        else
#endif  // 2004/04/15 yltseng, if cd_type_loaded is CDROM, we can use show_skip_osd to show
        // OSD next string. But there is a little BUG, when we are playing the last file, and
        // press Next, in fact we should not show OSD next string, but current method will.
        if( cd_type_loaded == CDROM )
        {
            OSD1000ISP_STATUS(OSDISP_NEXT, OSDIR_NEXT);

            show_skip_osd( 1, STR_OS_NEXT );
        }
        else
        {
            OSD1000ISP_STATUS(OSDISP_NEXT, OSDIR_NEXT);

            show_skip_osd( cd_trk_now < cd_trk_hi, STR_OS_NEXT );
        }

#ifdef ZOOM_DIRECT_STOP_SLIDE       //wanghaoying 2003-08-25 21:30

#ifdef MODIFY_ZOOM_DIRECT_STOP_SLIDE//nono 4-9-1 23:46
    if( Is_JPEG_SlideMode() )//nono 4-9-1 23:29
    {
        jpg_slide_time = JPEG_SLIDE_TIME;
    }
#else//#ifdef MODIFY_ZOOM_DIRECT_STOP_SLIDE//nono 4-9-1 23:46    
        ForceStopJpgSlide();
#endif//#ifdef MODIFY_ZOOM_DIRECT_STOP_SLIDE//nono 4-9-1 23:46

#endif
        #ifdef CIRCULARLY_PLAY//shenyj modify for alco 1950 0305
        if((!prog_cnt) && (cd_type_loaded==CDROM))
        {
            unsigned ttt=0;
            #ifdef MP3_DIRECT_SELECT//shenyj 0905
            if(FSGUI_GetDispTrack()==mp3_file_count())          
            #else
            if((pFsJpeg->dir_current==(pFsJpeg->Dir_Count)-1)&&(pFsJpeg->file_current==(pFsJpeg->File_Count)-1)&&(pFsJpeg->file_page_now==(pFsJpeg->File_Page_Count)-1))            
            #endif
                ttt=1;
            
            if(ttt)
            {            
                #if 0//def MODIFY_FOR_CHANGE_MPG_TO_AVI_BUG    
                if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
                    avi_change_to_mpg1=GetCurrentFileType();            
                #endif
            
                #ifdef ALCO_DIVX_UI
                if((GetCurrentFileType() != CDROM_AVI)&&(GetCurrentFileType() != CDROM_MP4)&&(GetCurrentFileType() != CDROM_MPG))      
                    pFsJpeg->fsnav_trk_now = 0;  
                #else
                pFsJpeg->fsnav_trk_now = 0; 
                #endif
                
                #ifdef ALCO_DIVX_UI
                if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4)||(GetCurrentFileType() == CDROM_MPG))      
                    invalid_key();
                else
                {
                    ir_num_select(pFsJpeg->fsnav_trk_now + 1);
                    PrintOsdMsg(STR_OS_NEXT,REGION1,1,0);
                }
                #else 
                ir_num_select(pFsJpeg->fsnav_trk_now + 1);
                PrintOsdMsg(STR_OS_NEXT,REGION1,1,0);
                #endif
                return;
            }
        }
        #endif//#ifdef CIRCULARLY_PLAY//shenyj modify for alco 1950 0305
        
        ircmd_post_func(CMD_FUNC | CMD_FUNC_NEXT);

#ifdef NEW_SEARCH_OSD
        // YW 020809 ADD
        dvd_title = 0;
        dvd_chapter = 0;
#endif
#ifdef SUPPORT_PRE_NEXT_GOTO_CHANGETODISPLAY
if(t_disp==1)  //lyc add 2006-2-20
     {
       	t_disp = 0;
       	disp_mode = 0;
        ircmd_display();
    }
#endif
/*
#ifdef OP_UI  //feeling 2004-05-14
    is_change_play_state=1;
    ircmd_display();
    if(!t_disp)
        ircmd_display();
    is_change_play_state=0;
#endif*/
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}


/********************   ircmd_vfd_next  ***************************/
#ifdef TWO_FUN_IN_ONE_VFD_KEY
//dingzhy for GBM 04-4-24 10:27
void    ircmd_vfd_next(void)
{
#ifdef SUPPORT_MIDI_MENU_SEL 
    if(gIsMidiSelMenu) //(Is_MIDI_STATE())&&
    {
        BYTE    cmd;
        //MidiIRCmd(1,0);

        if(Midi_pause_flag)
        {
            Midi_pause_flag =0;
            set_stc(midi_timenow);
    }

        if (iMidiSpeed<=0) { 
            //slow or normal speed, change to FF2X
            iMidiSpeed = 1;
            cmd = AUDIOFF1_25X;

            psprintf(RegionValStr[REGION1], ">");
            PrintOsdMsg(STR_OS_FF, REGION1, 1, 1);
        } else if (iMidiSpeed>=4) { 
            //change to play mode
            ircmd_play();
            return;
        } else {
            BYTE    buf[10];
            int     i;

            iMidiSpeed++;

            for (i=0; i<iMidiSpeed; i++) {
                buf[i] = '>';
        }
            buf[i] = '\0';

            cmd = AUDIOFF1_25X + iMidiSpeed - 1;

            psprintf(RegionValStr[REGION1], buf);
            PrintOsdMsg(STR_OS_FF, REGION1, 1, 1);
        }
      #ifdef MESSAGE_QUEUE
        DSP_AudioIOControl(FLOW, cmd, 0);
      #else        
        DSP_Midi_AudioIOControl(FLOW, cmd, 0); // MidiAudioCtrl
      #endif 
      
        if (play_state != VCD_STATE_PAUSE) {
            return;
        }
    }           
#endif

#ifdef RECORD_PER_SECOND                    //avoid bug   gerry  2-12-4 9:48
        if ((cd_type_loaded==CDROM)&&(Is_MP3_STATE()))
         {
            resumeMSF=0;
         }
#endif

#ifdef SUPPORT_NESGAME
    if ( Is_GAME_STATE() ) {
        invalid_key();
        return;
    }
#endif
/*
    if (GetCurrentFileType() == CDROM_MP4)  // Robert 2004/01/30, temporarily
        {
        invalid_key();
        return;
    }
*/
#ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 9:40
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //when play with normal speed,can use "FF"
        )
            {
        invalid_key();
        return; 
            }
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021015
    if(Is_OTHER_STATE() && play_state == VCD_STATE_MP3_FILELIST)
    {
        invalid_key();
        return;
        }
#endif

#ifdef SUPPORT_CDG    //terry,2003/8/7 12:37AM
    if(is_cdg_disc(1))
        return; 
#endif

    if ( Is_JPEG_STATE()) {
        invalid_key();//nono 20030804
        return;
        //ircmd_post_func(CMD_FUNC | CMD_FUNC_FORWARD);
    } else if(!chk_speed_state(UOP_FW))         /* alan 02-05-27 modified to reduce code size */
    {
        if(adv_search_time<=0) adv_search_time=1;

#ifdef CDMP3_2XMAX        //freyman 2003-8-6 10:06 added, When CD, MP3 only need 2X speed
        if((cd_type_loaded==CDDA)||(cd_type_loaded==CDROM))
        {
            if(adv_search_time==2)
            {
                ircmd_play();
                return;
            }
        }        
#endif
#ifdef BBK_DVD//zhaoyanhua add BBK need 2/4/8/16/32  
        if(adv_search_time<32)
#elif defined(FW_BW_MAX_60S)
        if(adv_search_time<60)
#else
        if(adv_search_time<20)
#endif
        {
            if((cd_type_loaded==CDDA)||(cd_type_loaded==CDROM))
            {
                if(adv_search_time<2 && !user_mute) {
                    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020614
                        AUDIF_Set_Volume(0);//AudioSetVolume(0);
                    } else {
#ifdef MP3_CD_FF1_BF1_MUTE//YX822BC//nono 2-8-21 10:43
                        AUDIF_Set_Volume(0);//AudioSetVolume(0);
#else
                        {
#ifdef CNTR_5SPK_VOLUME
                            int i,read_volume;
                            for (i=0; i<7; i++) {
                                read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
                                if(i==0)
                                {
#ifdef CNTR_5SPK_TYPE_2 //linrc add 2004-10-11 11:08-->ESS is like this type
                                    Set_5SPK();
#else
                                    AUDIF_Set_Volume(volume_5SPK[0]);//2004AUDDRV AudioSetVolume(volume_5SPK[0]);
#endif
                        }
                                else
                                    DSP_AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);//2004AUDDRV AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);
                            }
#else
                            AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
#endif
                        }
#endif
}
                } else {
                    AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
                }
            }
/*
        #ifndef BBK_DVD//zhaoyanhua add 03-11-5 15:17
            if(adv_search_time==8) 
                adv_search_time=20; 
        
            else 
        #endif//end BBK_DVD     
                adv_search_time*=2;
*/
            calculate_fw_time_param();

#ifdef SUPPORT_MP4  // 2004/07/27 yltseng   
            if( IsUserControlDisabledByTrickyPlay( IRC_VFD_NEXT ) )
            {
                ircmd_play();
                return;
            }
#endif
            play_state=VCD_STATE_FASTFORWARD;
            fast_play_post_proc();
        }else {
            ircmd_play();
        }
    }
}
#endif//#ifdef TWO_FUN_IN_ONE_VFD_KEY
/***************** end of ircmd_vfd_next **************************/



void    ircmd_prev(void)
{
    #ifdef OP_DVD5121_PANEL
  if (regs0->iop_data[6]==IR_ADDR_PATT)
 {
       if( (pressed_flag!=1) ) 
    {
         pressed_flag = 1;
          return;
    }
    else
    {
         pressed_flag = 0;
      }
 }
 #endif 
 #ifdef SUPPORT_NEXT_PREV_AUTO_PLAY_MP3//yangli add for in filemode next/prev/autoplay function
        auto_play_flag=1; 
 #ifdef SUPPORT_MULTI_PARTITION
    if((pFsJpeg->gifsState == FS_STATE_MP3)||(pFsJpeg->gifsState == FS_STATE_JPEG)||(pFsJpeg->gifsState == FS_STATE_OTHER))
    {   
        prev_flag=1;
        osd_tog_region(1,OSD_OFF);
        HDDCard_return();       
        return;
    }
    else return;
    #endif
#endif


#if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) //kenny add 2005 6/16

        
       // if((pFsJpeg->gifsState == FS_STATE_MP3) ||(pFsJpeg->gifsState == FS_STATE_JPEG) ||(pFsJpeg->gifsState == FS_STATE_OTHER))
        pmp_disable_user_flag(PMP_USER_PRESS_UP_DOWN__KEY);//kenny 2005/7/12
        pmp_enable_user_flag(PMP_USER_PRESS_NEXT_PREV_KEY);
        PMP_show_prev_osd();           //////////////yangli 2005/8/10
        HDDCard_up();
       
        
         
        return;
   
#endif


#ifdef SUPPORT_MIDI_MENU_SEL   //ouyang add for invalid forward when press pause 2004-9-28 15:192004-9-28 15:19
    if(gIsMidiSelMenu) 
    {
        if(Midi_pause_flag)
        {
            invalid_key();
            return;
        }
      }           
#endif

#ifdef FAT_Write_UI//SPHE8202_USB_Write    //wanghaoying 2005-7-28 11:02
    if(cd_type_loaded==CDROM)
    {
        if (full_scrn & PERIPHERAL)
        {
            full_scrn &= (~PERIPHERAL);
            osd_init();
            invalid_key();
            return;
        }
    }
#endif

#ifdef INVALID_PREV_WHEN_TRK1    //zhongshan add 050718
// if( cd_type_loaded == CDROM )
 if( cd_type_loaded != CDDVD )
 {
if((disp_trk_now == 1)&&(rep_mode==REPEAT_IDLE)&&(prog_cnt ==0 )&&(shuffle_flag==0))
    {
            invalid_key();
            return;
        }
if( (prog_index == 1)&&(rep_mode==REPEAT_IDLE)&&(prog_cnt !=0 ))
{   
    invalid_key();
        return;
}
    }
#endif

#ifdef SUPPORT_MIDIDISK_TITLE
    if (bIsPlayMidiTitle)
    {
        invalid_key();
        return;
    }
#endif
#if defined(MP3_ONLY_STOP_TO_GUI)&&defined(MODIFY_MP3_ONLY_STOP_TO_GUI)//nono add 4-8-10 11:00
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //only in FsMP3mainloop,can use "REPAB"
        )
    {
        invalid_key();
        return;
    }
#endif

    //Maoyong 2004-8-14 9:34, special process thumbnail menu for panel Prev/Next Key
    #ifdef JPEG_THUMBNAIL_MENU
	#ifdef ALCO_DVD_UI
     if(!pFsJpeg->gbfsPictureCD)
    #endif
     {
    if(JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode){
        if(!ThunmnailChkValidPrevNext(IRC_PREV))
            return;
    }
    }
    #endif

    if( IsInvalidInNextPrev() )
        return;

    // 2004/04/15 yltseng mark, no need now
/*
#ifdef SUPPORT_OTHER_NEXT_PREVIOUS  //wuxiaofeng 2004-03-16
            if(Is_OTHER_STATE() && pFsJpeg->gifsState==FS_STATE_LIST)
            {
                invalid_key();
                return ;
            }
#endif//#ifdef SUPPORT_OTHER_NEXT_PREVIOUS

#ifdef SKYWORTH_DVD  //3-10-23 1:47张宇P
         if(rep_mode==REPEAT_TRACK)
          { 
            invalid_key();
                return;
          }
#endif
*/

#ifdef NEXT_FORWARD_IN_A_KEY
    //if( (bIrSkipState==0)&&(key_data_flag==0) )
    if( (bIrSkipState!=1)&&(key_data_flag==0) )//2004-5-5 15:16
    {
         bIrSkipState = 1;
         rep_ir_times = 0;
         bIrSkipCnt = 0;
         return;
    }
    else
    {
         bIrSkipState = 0;
         rep_ir_times = 0;
         bIrSkipCnt = 0;
    }
#endif//NEXT_FORWARD_IN_A_KEY

 #ifdef SUPPORT_FILE_CHAPTER
 if( fileChangeChapter( CMD_FUNC_PREV ) )
        return;
 #endif //SUPPORT_FILE_CHAPTER

#ifdef NEXT_CANCEL_ZOOM
if(vpp_zoom!=0)  /* add by TOM */
    {
        vpp_zoom = 0;
        show_zoom(1);
    }
#endif

    // printf("v11_trk_now=%d > cd_trk_hi=%d\n",v11_trk_now,cd_trk_hi);
    if(play_state == VCD_STATE_PREVIEW)
    {
#ifdef DVD_PREVIEW_FUNCTION
        if(cd_type_loaded==CDDVD)
        {
            OSD1000ISP_STATUS(OSDISP_PREV, OSDIR_PREV);

            show_skip_osd(1,STR_OS_PREV);
            AVD_SetMediaTimeout();
            PostCommand(CMD_FUNC | CMD_FUNC_PREV);
            return;
        }else   
#endif      
        if(v11_trk_now-((v11_trk_now-cd_trk_lo_now)%9) <=cd_trk_lo_now)
           return;
        }
#ifdef KONKA_DVD//clead 20020820
        if (full_scrn&SETUP) {          //clead   20020820
            setup_func_prepage();
            return;
        }
#endif

#ifdef FUSS_DVD//nono 2-7-2 23:50 when CDDA STOP ,PREV need to be valid.
        if( (cd_type_loaded!=CDDA)&&(play_state==VCD_STATE_STOP) )//&&((shuffle_flag)==0) )
        {
            invalid_key();
            return;
        }
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT//Jack added 04/11/13
    if(ir_num_timer)
      ir_continuous_num_clr();
#endif

        //PBC off
#ifdef IR_SHUFFLE_ON    // alan 0506 modified to add ircmd_next when shuffle on for FUSS
        if(shuffle_flag)
        {
        #ifdef SHUFFLE_ACCOMPLISH_BY_ARITHMETIC        //wangmin add for the real shuffle when cd playing 051020
             if(cd_type_loaded==CDDA)
                 shuffle_track= shuffle_prev(v11_trk_now);//,NOT_FS_SHUFFLE);
        #else
            //  #ifdef FUSS_DVD   //nono mark 2-6-6 20:15. why define FUSS_DVD only here.not in NEXT.
            shuffle_flag=0;
            action_click=1;
            ircmd_shuffle();
            //  #else
            //     invalid_key();
            //  #endif
            return;
        #endif
        }
#endif
        
        if(rep_mode==REPEAT_IDLE)
        #ifdef NEXT_PREV_NOT_STOP_PROG
        { 
            #ifdef AFTER_P5SECONDS_PREV_2TRACK_START
            #ifdef REMAIN_TIME
                if(prog_cnt && (prog_index==1) &&(!remain) && (disp_time<5))
            #else
                if(prog_cnt && (prog_index==1) && (disp_time<5))
            #endif
            #else
            if(prog_cnt && (prog_index==1))
            #endif
                prog_index++;
            
            prog_prev();
        }
        #else
            prog_prev();
        #endif
        
#ifdef  STOP_IN_PROG_END //wuxiaofeng 2004-03-15
        if(sys_cmd==(CMD_FUNC | CMD_FUNC_STOP))
        {   
            ircmd_post_func(sys_cmd);
            return;
        }
#endif//#ifdef  STOP_IN_PROG_END
#ifdef RECORD_PER_SECOND                        //avoid bug  gerry  2-12-4 9:48
        if ((cd_type_loaded==CDROM)&&(Is_MP3_STATE()))
         {
            resumeMSF=0;
         }
#endif

#ifdef FUSS_DVD_AVD276//fuss_xinqiao
        if(cd_type_loaded==CDDVD)
        {
            OSD1000ISP_STATUS(OSDISP_PREV_CHAPTER, OSDIR_PREV);

            show_skip_osd((cd_trk_now>cd_trk_lo_now)||(cd_type_loaded==CDDVD),STR_TOS_PREV_CHAPTER);
        }
        else
#endif  // 2004/04/15 yltseng, if cd_type_loaded is CDROM, we can use show_skip_osd to show
        // OSD prev string. But there is a little BUG, when we are playing the first file, and
        // press Prev, in fact we should not show OSD prev string, but current method will.
        if( cd_type_loaded == CDROM )
        {
            OSD1000ISP_STATUS(OSDISP_PREV, OSDIR_PREV);

            show_skip_osd( 1, STR_OS_PREV );
        }
        else
        {
            OSD1000ISP_STATUS(OSDISP_PREV, OSDIR_PREV);

            show_skip_osd( (cd_trk_now>cd_trk_lo_now)||(cd_type_loaded==CDDVD),STR_OS_PREV);
        }

#ifdef ZOOM_DIRECT_STOP_SLIDE       //wanghaoying 2003-08-25 21:30
#ifdef MODIFY_ZOOM_DIRECT_STOP_SLIDE//nono 4-9-1 23:46
    if( Is_JPEG_SlideMode() )
    {
        jpg_slide_time = JPEG_SLIDE_TIME;
    }
#else//MODIFY_ZOOM_DIRECT_STOP_SLIDE
        ForceStopJpgSlide();
#endif//MODIFY_ZOOM_DIRECT_STOP_SLIDE
#endif
        #ifdef BACK_SKIP_PREV
        if((cd_type_loaded!=CDDVD) && (play_state==VCD_STATE_NORMAL))
        {

            #ifdef REMAIN_TIME
            if((!remain) && (disp_time>BACK_SKIP_TIME))
            #else
            if(disp_time>BACK_SKIP_TIME)
            #endif
            {
                if(!(((cd_type_loaded==CDSVCD)||(cd_type_loaded==CDVCD20)) && IsPBCOn()))
                {
                    if(cd_type_loaded!=CDROM)
                        v11_trk_now++;
                    else if(Is_MP3_STATE()) 
                        pFsJpeg->file_current++;
                    //pFsJpeg->fsnav_trk_now++;
                    PrintOsdMsg(STR_OS_PREV,REGION1,1,0);  
                }
            }    
        }
        #endif
        
        #ifdef CIRCULARLY_PLAY
        if((!prog_cnt) && (cd_type_loaded==CDROM))
        {
          #ifdef REMAIN_TIME
          if((!remain) && (disp_time<5))
          #else
          if(disp_time<5)
          #endif
          {
                if((pFsJpeg->file_current==0) && (pFsJpeg->dir_current==0)&&(pFsJpeg->file_page_now==0)
                #ifdef MP3_DIRECT_SELECT
                &&((FSGUI_GetDispTrack()!=mp3_file_count()) )
                #endif
                )                   //shenyj add for alco177w 0303       
                {
                                            
                    #ifdef ALCO_DIVX_UI
                    if((GetCurrentFileType() != CDROM_AVI)&&(GetCurrentFileType() != CDROM_MP4)&&(GetCurrentFileType() != CDROM_MPG))            
                        pFsJpeg->fsnav_trk_now = mp3_file_count()-1;
                    
                    if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4)||(GetCurrentFileType() == CDROM_MPG))
                        invalid_key();
                    else
                    {
                        ir_num_select(pFsJpeg->fsnav_trk_now + 1);
                        PrintOsdMsg(STR_OS_PREV,REGION1,1,0);
                    }
                    #else
                    ir_num_select(pFsJpeg->fsnav_trk_now + 1);
                    PrintOsdMsg(STR_OS_PREV,REGION1,1,0);
                    #endif
                    
                    return;
                }
            }
        }
        #endif//#ifdef CIRCULARLY_PLAY
        
        ircmd_post_func(CMD_FUNC | CMD_FUNC_PREV);

#ifdef FUSS_DVD//nono 2-6-29 12:21
        if( (cd_type_loaded==CDDA)&&(play_state==VCD_STATE_STOP) )
        {
            ircmd_input_number(cd_trk_hi-1);
            ircmd_post_func(CMD_FUNC|CMD_FUNC_SELECT);
            ir_num_select(cd_trk_hi-1);

            OSD1000ISP_STATUS(OSDISP_PREV, OSDIR_PREV);

            PrintOsdMsg(STR_OS_PREV,REGION1,1,0);
        }
#endif

#ifdef NEW_SEARCH_OSD
        // YW 020809 ADD
        dvd_title = 0;
        dvd_chapter = 0;
#endif
#ifdef SUPPORT_PRE_NEXT_GOTO_CHANGETODISPLAY
if(t_disp==1)  //lyc add 2006-2-20
     {
       	t_disp = 0;
       	disp_mode = 0;
        ircmd_display();
    }
#endif
/*
#ifdef OP_UI  //feeling 2004-05-14
    is_change_play_state=1;
    ircmd_display();
    if(!t_disp)
        ircmd_display();
    is_change_play_state=0;
#endif*/
}

/*******************  ircmd_vfd_prev  **************************/
#ifdef TWO_FUN_IN_ONE_VFD_KEY
//dingzhy for GBM 04-4-24 10:28
void    ircmd_vfd_prev(void)
{
#ifdef SUPPORT_MIDI_MENU_SEL 
    if(gIsMidiSelMenu) 
    {
        return;
    }           
#endif

#ifdef SUPPORT_MP4    // 2004/07/27 yltseng
    if( IsUserControlDisabledByTrickyPlay( IRC_VFD_PREV ) )
    {
        invalid_key();
        return;
    }
#endif

#ifdef RECORD_PER_SECOND                        //avoid bug  gerry  2-12-4 9:48
    if ((cd_type_loaded==CDROM)&&(Is_MP3_STATE()))
        {
        resumeMSF=0;
    }
#endif

#ifdef SUPPORT_NESGAME
    if ( Is_GAME_STATE() ) {
        invalid_key();
           return;
    }
#endif      
/*
    if (GetCurrentFileType() == CDROM_MP4) // Robert 2004/01/30, temporarily
    {
        invalid_key();
           return;
        }
*/
#ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 9:40
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //when play with normal speed,can use "FB"
        )
    {
        invalid_key();
            return;
        }
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021015
    if(Is_OTHER_STATE() && play_state == VCD_STATE_MP3_FILELIST)
        {
            invalid_key();
            return;
        }
#endif

#ifdef SUPPORT_CDG    //terry,2003/8/7 12:40AM
    if(is_cdg_disc(1)) return;  
#endif

    if ( Is_JPEG_STATE()) {
        invalid_key();//nono 20030804
        return;
        //ircmd_post_func(CMD_FUNC | CMD_FUNC_BACKWARD);
    } else if(!chk_speed_state(UOP_BW))         /* alan 02-05-27 modified to reduce code size */
    {
        if(adv_search_time>=0) adv_search_time=-1;

#ifdef CDMP3_2XMAX        //freyman 2003-8-6 10:06 added, When CD, MP3 only need 2X speed
        if((cd_type_loaded==CDDA)||(cd_type_loaded==CDROM))
        {
            if(adv_search_time==-2)
        {
                ircmd_play();
            return;
        }
         }
#endif

#ifdef BBK_DVD//zhaoyanhua add 03-11-5 15:18
        if(adv_search_time>(-32))
#elif defined(FW_BW_MAX_60S)
        if(adv_search_time>(-60))
#else
        if(adv_search_time>(-20))
#endif
        { 
            if((cd_type_loaded==CDDA)||(cd_type_loaded==CDROM))
            {
                if(adv_search_time>(-2) && !user_mute)
                    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020614
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
                    } else {
#if defined(MP3_CD_FF1_BF1_MUTE)//YX822BC//nono 2-8-21 10:43
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
#elif defined(CNTR_5SPK_VOLUME)
                        int i,read_volume;
                        for (i=0; i<7; i++) {
                            read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
                            if(i==0)
                            {
#ifdef CNTR_5SPK_TYPE_2 //linrc add 2004-10-11 11:08-->ESS is like this type
                                Set_5SPK();
#else
                                AUDIF_Set_Volume(volume_5SPK[0]);//2004AUDDRV AudioSetVolume(volume_5SPK[0]);
#endif
                            }
                            else
                                DSP_AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);//2004AUDDRV AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);
                    }
#else
                    AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
#endif
        }
                else
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
            }

    //wanghaoying delete 2004-07-28

            calculate_bw_time_param();

            play_state=VCD_STATE_FASTBACKWARD;
            fast_play_post_proc();
        }else
            ircmd_play();
    }
}
#endif//#ifdef TWO_FUN_IN_ONE_VFD_KEY
/*************  end of ircmd_vfd_prev  *********************/



void ircmd_title_return(void)
{
#ifdef ONLY_ONE_SUBTITLE_OPERATE_TITLE_KEY_IS_INVALID//shenyj add for alco 2006/02/28
if(pDSV->dAv_SPST_Ns==0)
{
    invalid_key();
    return;
}
#endif 
   
       #ifdef SDRAM_16Mb_Mode    //jwk fix bug, <<when press title_return button the osd will distortion2005-8-12 15:03
	if(full_scrn&SETUP)    
	  { 
	  	invalid_key();
	  	return;
	  	}
       #endif
#ifdef SUPPORT_MIDI_MENU_SEL
        if (Is_MIDI_STATE())
        {
        invalid_key();
        return;
        }
#endif
#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
#endif

#ifdef INVALID_TITLERETURN_WHEN_PROG_PLAY//Jack 04/11/01
    if(prog_cnt)
    {
        invalid_key();
        return;
    }
#endif

    if((cd_type_loaded==CDDVD)
    #if defined(SUPPORT_MP4)&&defined(ALCO_DVD_UI)//shenyj add for alco divx 1020
    ||(GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4)||(GetCurrentFileType() == CDROM_DIV)
    #endif
    )
    {
        #ifdef DESAY_DVD
        ircmd_root_menu();
#else//#ifdef DESAY_DVD

#ifdef DVD_AUDIO        //nono 4-1-10 13:56
        if ( (cd_type_loaded==CDDVD) && (prog_cnt||dAMG_LSN) )
        #else
        if ( (cd_type_loaded==CDDVD) && (prog_cnt) )
#endif
        {
            invalid_key();
            return;
        }else
        #ifdef ALCO_8200P_MULTIKEY
        ircmd_sub_picture();
        #else
        ircmd_title_menu();
        #endif
#endif//#ifdef DESAY_DVD
    }
    else if(play_state!=VCD_STATE_STOP)//nono 20030801
    {
        ircmd_return();
    }
}


void    ircmd_return(void)
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).

#ifdef TITLE_RETURN_IN_A_KEY //ZXB 2006-3-9 17:57
    if( (bIrSkipState1!=1) )
    {
         bIrSkipState1 = 1;
         bIrSkipCnt1 = 0;
         return;
    }
    else
    {
         bIrSkipState1 = 0;
         bIrSkipCnt1 = 0;
    }
    if(rep_ir_times==0) //zxb 2006-3-28 14:28 
    	return;
#endif//TITLE_RETURN_IN_A_KEY

#ifdef HANYANG_LR_CHANGE_PAGE
//use return to change file->dir and dir->button area in fsGUI
    if( (cd_type_loaded == CDROM ) &&
        ( (pFsJpeg->gifsState == FS_STATE_LIST) || (pFsJpeg->gifsState == FS_STATE_MP3) ) &&
        (JPEG_THUMBNAIL_MODE != pFsJpeg->g_nJpegMode ) ) {
            if( pFsJpeg->ControlArea == CNT_AREA_FILE ){
                FSGUI_File2DirArea();
                return;
            }else if ( pFsJpeg->ControlArea == CNT_AREA_DIR ) {
                ircmd_post_func(CMD_SELECT | CMD_FUNC_GAME_L);
                return;
            }
    }
#endif //#ifdef HANYANG_LR_CHANGE_PAGE

#ifdef IR_RETURN_RESUME
    if((cd_type_loaded>=CDVCD10)&&(cd_type_loaded<=CDDVD))
    if(is_menu())
    {
        ircmd_resume();
        return;
    }
#endif

    #ifdef SUPPORT_MIDI_MENU_SEL
        if(gIsMidiSelMenu)  
        {
        /*
            if(MenuState < MENU_MULTI_INDEX_SEL)
                return;
            else 
            */
            if(MenuState >= MENU_MULTI_INDEX_SEL)
//for other status in future
                ircmd_post_func(CMD_FUNC | CMD_FUNC_RETURN);
            return ; 
        }
    #endif

    //terry,2002/5/16 11:55AM
#ifdef  FUSS_DVD
    if (full_scrn&SETUP) {          /* alan modified 02-05-13 for FUSS : return to main setup*/
        setup_func_return_main();
        return;
    }
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE     // 2004/01/07 yltseng
    if( Is_OTHER_STATE() && pFsJpeg->gifsState != FS_STATE_OTHER )
    {
        invalid_key();    
        return;
    }
#endif

    //under PROGRAM, enable IRC_RETURN function
    //so add some invalid condition here, Jeff 20020508
#ifdef DVD_AUDIO        // alan, 2002/11/13 02:45と
        if ( (cd_type_loaded==CDDVD) && (prog_cnt||dAMG_LSN) )
#else
        if ( (cd_type_loaded==CDDVD) && (prog_cnt) )
#endif
        {
            invalid_key();
            return;
        }
 #ifdef SUPPORT_MULTI_PARTITION//liweihua mod 2004-11-2 21:46
    if((pFsJpeg->gifsState == FS_STATE_HDD)
        ||((media_type == MEDIA_CARD)&&((pFsJpeg->gifsState == FS_STATE_LIST)||(pFsJpeg->gifsState == FS_STATE_MP3)||(system_state == SYSTEM_STOP)))
        #ifdef FAT_FILE_MODE
        ||(pFsJpeg->gifsState == FS_STATE_MODE)
        ||(fat_play_mode == 1)
        #endif
        )
    {   printf("asdfjaskdjfkasdjfkjaskdf\n");
        osd_tog_region(1,OSD_OFF);
        #if defined(PMP_DVD)&& defined(PMP_DVD_ONE_DIR_SELECT) ////kenny add 2005/6/16
        if(pmp_get_user_flag()&PMP_USER_PRESS_RETURN_KEY) //zxb 2005-9-22 0:11 avoid pressing return button twice
        	return;
        pmp_enable_user_flag(PMP_USER_PRESS_RETURN_KEY);
    #endif
        HDDCard_return();       
        
        
        
        return;
    }
    #endif

#ifdef SETUP_DONGLI459    //oujx
    if( IsPBCOn()||(cd_type_loaded==CDROM) )
#else
    if( IsPBCOn()||(cd_type_loaded==CDROM)||(cd_type_loaded==CDDVD) )
#endif 
    {
        #if defined(JIEKE_DVD) && defined(DVD_SEQ_PLAY)//add by wangfeng 2003-11-28 18:01
        if((dvd_menu_play==0)&&(cd_type_loaded==CDDVD)){
        invalid_key();  
        }
        else
        #endif
        if (Is_MP3_STATE())
        {
            invalid_key();
            return; 
        }   
        else

#if defined(USE_RETURN_RESUME)&& !defined(DVD_PRESTOP_SEPARATE_MENU_RESUME_INFO)//2004-6-2 22:48 //chenzhao 2006-9-13 12:43 .
        if(is_menu()==1 && cd_type_loaded==CDDVD)
        {
            ircmd_post_func(CMD_FUNC | CMD_FUNC_RESUME);
            return;
        }
        else
#endif//USE_TITLE_RESUME

#ifdef FAT_Write_UI                     //sunzhh add 20041124
    if((full_scrn & PERIPHERAL)&&(((pFsJpeg->gbfsSlide)&& (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))||(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)))
    {
        ircmd_post_func(CMD_FUNC | CMD_FUNC_RETURN);
        return;
    }
else 
#endif     //#ifdef FAT_Write_UI
        
        {
        OSD1000ISP_STATUS(OSDISP_RETURN, OSDIR_NULL);
#ifndef MENU_KEY_DIR_TO_DISC_MENU//libing 2005-7-5 9:29
        PrintOsdMsg(STR_OS_RETURN,REGION1,1,0);//terry,0511 , use ir osd post msg
#endif        
        ircmd_post_func(CMD_FUNC | CMD_FUNC_RETURN);
        
        if(RegionOnOff[REGION1][2]==STR_OS_RETURN)  //nono 3-12-6 14:27
        rep_mode = REPEAT_IDLE;
        }
    }else
        invalid_key();

    #ifdef SUPPORT_QUICKTIME
    file_set_subp_status(0);
    #endif //SUPPORT_QUICKTIME
    
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}


UINT8 chk_speed_state(UINT8 uop)
{
    int reject=0;

    if( (HL_exist&& !DVD_check_state()) || UOP_check(uop))
        reject=1;

    if(rep_ab_mode==REPEAT_FIND_B)   // chichang 2001 6/18
        reject=1;

    if(audio_only==2)
        reject=1;

    if( IsValidMSF(s_msf) || (play_state==VCD_STATE_NORMAL) )
    {
        if(Vobu_still)
        {
            P_vobu=0;
        }
    }
    else
    {
        reject=1;
    }

    if(reject)
        invalid_key();
    else
    {
        chg2normal_play(SLOW2NORM|PAUSE2NORM,TRANSFER);
    }
    return reject;
}

/*********************************************************************
*fast_play_post_proc()
*
*Modify Record:
*2006/02/10    Robert.Chang     mark rep_ab_mode=REPEAT_AB_IDLE
*
**********************************************************************/

void fast_play_post_proc(void)
{
    int id,val;

    SetIDETimeOut(SHORT_TMOUT);//printf("set srv timeout tm = %d\n",SHORT_TMOUT);//terry,2003/7/17 11:17PM

    avd_fast_state();
    if (!audio_only)
        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);

    if(adv_search_time>0)
    {
        //Jeff 20020411
        if ( (cd_type_loaded==CDROM) ||
            (cd_subtype==CD_DTS)//nono 20020705
            //( (coding_mode_now==AUDIF_CODING_MODE_DTSCD)&&( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) )  )
            )
        {
            AUDIF_Set_FastForward(adv_search_time);//2004AUDDRV AudioFastForward(adv_search_time);
        }

        id=STR_OS_FF;


        val=adv_search_time;


        //                val=adv_search_time;
    }else
    {

//Mark by Robert.Chang for this situation that run repeat_ab when FF. 2006/02/10	
/* 
        if( rep_ab_mode == REPEAT_FIND_A) 
        {
            rep_ab_mode=REPEAT_AB_IDLE;
         }//axel 2003-12-26 cancel rep_ab while Fast Backward
*/            

        if (cd_type_loaded==CDROM) {
            AUDIF_Set_Continue();//2004AUDDRV AudioSetContinue();
        }

        if(cd_subtype==CD_DTS) {//nono 20020705
            //if( (coding_mode_now==AUDIF_CODING_MODE_DTSCD)&&(( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) )) ) {
            AUDIF_Set_FastForward(2);//2004AUDDRV AudioFastForward(2); //send FF command to DTSCD decoder to force DSP to flush buffer
        }

        id=STR_OS_FB;


        val=-adv_search_time;


        //                val=-adv_search_time;
    }

    #ifdef DISPLAY_FBWARD_OSD
    PrintOsdMsg(id|(val<<OSDSTR_ID_TOTL_BIT),REGION1,0,6);//can not be controled by polling_osd(). zhaoyanhua note 2003-4-4 11:13
    #else
    PrintOsdMsg(id|(val<<OSDSTR_ID_TOTL_BIT),REGION1,1,6);
    #endif

}


/*
**calculate adv_search_time parameter
*/
//#undef FW_BW_MAX_60S
#ifdef FASTPLAY_FIVE_LEVEL

/*
 * Description;
 *    if adv_search_time < 0, now in FB state, if enter "FF" will increase its FB rate.
 *
 *   FB rate :-2 -4 -8 -16 -32
 *   FF rate : 2  4  8  16  32 
 */
static inline void     calculate_fw_time_param()
{
    if (adv_search_time < 0)
    {    
        if (adv_search_time == -2)
            adv_search_time = 0;
        else
            adv_search_time = adv_search_time/2;
    }
    else
        adv_search_time = adv_search_time*2;        
    
}
#else
static inline   void    calculate_fw_time_param()
{
#ifdef FW_BW_MAX_60S
    if( (adv_search_time==5)||(adv_search_time==30) ) 
        adv_search_time*=2;
    else if(adv_search_time==10)
        adv_search_time*=3;
    else
        adv_search_time*=5;
        
#elif defined(BBK_DVD) || defined(BACKFORWARD_32CLASS)//zhaoyanhua add 03-11-5 15:17
        adv_search_time*=2;
#else//FW_BW_MAX_60S
        if(adv_search_time==8) 
            adv_search_time=20; 
        else 
            adv_search_time*=2;
#endif//FW_BW_MAX_60S

}
#endif//ifdef FASTPLAY_FIVE_LEVEL

/*
** fast forward
*/
void    ircmd_forward(void)
{
#ifdef ORITRON_HK_DVD //qinhua,add,2006-2-16 9:53
 #ifdef SUPPORT_QUICKTIME
 if ((iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_M4A)||(GetCurrentFileType() == CDROM_AAC))
  {
       invalid_key();
            return;	
  }
 #endif  
 #ifdef SUPPORT_WAV
 if(GetCurrentFileType() == CDROM_WAV) 
   {
   invalid_key();
   return;	
  }
#endif 
#endif //#ifdef ORITRON_HK_DVD //qinhua,add,2006-2-16 9:53

#ifdef USE_FW_SF        //zhongshan 050718
    if((play_state ==  VCD_STATE_PAUSE)||(play_state == VCD_STATE_SLOW))
    {
        ircmd_fw_sf_slowmotion();
        return;
    }
#endif

    #ifdef PMP_DVD ////kenny add 2005/7/9
    
    if(pFsJpeg->gifsState == FS_STATE_INIT)
    return;
    #endif
    
    #ifdef FORWORD_AFTER_PAUSE_SLOW//libing
if((cd_type_loaded!=CDDA)&&(cd_type_loaded!=CDROM_WMA)&&(cd_type_loaded!=CDROM_MP3)&&(cd_type_loaded!=CDROM_JPEG))
{    
            if((play_state==VCD_STATE_PAUSE)||(play_state==VCD_STATE_SLOW))//libing
    {  
        ircmd_slowmotion();
        return;
            }
  /*
            else if(play_state==VCD_STATE_SLOW)
    {
        ircmd_slowmotion();
        return;
    } 
  */
}      
    #endif
//    {
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef SUPPORT_MIDI_MENU_SEL //ouyang add for invalid forward when press pause 2004-9-28 15:19
    if(gIsMidiSelMenu) 
    {
        if(Midi_pause_flag)
        {
            invalid_key();
            return;
        }
      }           
#endif
    
#if (defined BBK_DVD) || (defined FASTPLAY_FIVE_LEVEL)//zhaoyanhua add BBK need 2/4/8/16/32  
    #define MAX_FF_RATE         32      
#elif defined(FW_BW_MAX_60S)
    #define MAX_FF_RATE         60  
#else
    #define MAX_FF_RATE         20
#endif    
 #ifdef SUPPORT_MIDI //WSF 2004-5-30 18:18    
    if(Midi_pause_flag)     ircmd_play();           
    #endif


#if defined(MP3_ONLY_STOP_TO_GUI)&&defined(MODIFY_MP3_ONLY_STOP_TO_GUI)//nono add 4-8-10 11:00
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //only in FsMP3mainloop,can use "REPAB"
        )
    {
        invalid_key();
        return; 
    }
#endif

#ifdef NEW_NEXT_FORWARD_IN_A_KEY
    //if( (bIrSkipState==0)&&(key_data_flag==0) )
    if( (bIrSkipState!=2)&&(key_data_flag==0) )//2004-5-5 15:16
    {
         bIrSkipState = 2;
         rep_ir_times = 0;
         bIrSkipCnt = 0;
         return;
    }

    if(still_timer && cd_type_loaded==CDDVD)//NONO 4-8-20 15:18
    {
        invalid_key();
        return; 
    }
    

#endif//NEXT_FORWARD_IN_A_KEY

#ifdef SUPPORT_MIDI_MENU_SEL 
    if(gIsMidiSelMenu) //(Is_MIDI_STATE())&&
    {
        BYTE    cmd;
        //MidiIRCmd(1,0);
        if (!((bMidiPlayerBoolean)&&(midiState == MIDI_STATE_PAYLOAD)))
        {
            invalid_key();
            return;
        }                     //ouyang 2004.07.31
        if(Midi_pause_flag)
        {
            Midi_pause_flag =0;
            set_stc(midi_timenow);
            ircmd_play();            
        }

        if (iMidiSpeed<=0) { 
            //slow or normal speed, change to FF2X
            iMidiSpeed = 1;
            cmd = AUDIOFF1_25X;

            psprintf(RegionValStr[REGION1], ">");
            PrintOsdMsg(STR_OS_FF, REGION1, 1, 1);
        } else if (iMidiSpeed>=4) { 
            //change to play mode
            ircmd_play();
            return;
        } else {
            BYTE    buf[10];
            int     i;

            iMidiSpeed++;

            for (i=0; i<iMidiSpeed; i++) {
                buf[i] = '>';
            }
            buf[i] = '\0';

            cmd = AUDIOFF1_25X + iMidiSpeed - 1;

            psprintf(RegionValStr[REGION1], buf);
            PrintOsdMsg(STR_OS_FF, REGION1, 1, 1);
        }
      #ifdef MESSAGE_QUEUE
        DSP_AudioIOControl(FLOW, cmd, 0);
      #else        
        DSP_Midi_AudioIOControl(FLOW, cmd, 0); // MidiAudioCtrl
      #endif 
        
        if (play_state != VCD_STATE_PAUSE) {
            return;
        }
    }           
#endif

#ifdef RECORD_PER_SECOND                            //avoid bug gerry  2-12-4 9:48
    if ((cd_type_loaded==CDROM)&&(Is_MP3_STATE()))
    {
        resumeMSF=0;
    }
#endif

#ifdef SUPPORT_NESGAME
    if ( Is_GAME_STATE() ) {
        invalid_key();
        return;
    }
#endif

#ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 9:40
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //when play with normal speed,can use "FF"
        )
    {
        invalid_key();
        return; 
    }
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021015
    if(Is_OTHER_STATE() && play_state == VCD_STATE_MP3_FILELIST)
    {
        invalid_key();
        return;
    }
#endif

#ifdef SUPPORT_CDG    //terry,2003/8/7 12:37AM
    if(is_cdg_disc(1))
        return; 
#endif

    if ( Is_JPEG_STATE()) {
        invalid_key();//nono 20030804
        return;
        //ircmd_post_func(CMD_FUNC | CMD_FUNC_FORWARD);
    } else if(!chk_speed_state(UOP_FW))         /* alan 02-05-27 modified to reduce code size */
    {
    #ifdef FASTPLAY_FIVE_LEVEL//zhaoyanhua add 2004-5-13 15:37
        if (adv_search_time == 0)
            adv_search_time = 1;
    #else
        if(adv_search_time<=0) 
            adv_search_time=1;
    #endif//ifdef FASTPLAY_FIVE_LEVEL
#ifdef CDMP3_2XMAX        //freyman 2003-8-6 10:06 added, When CD, MP3 only need 2X speed
        if((cd_type_loaded==CDDA)||(cd_type_loaded==CDROM))
        {
            if(adv_search_time==2)
            {
                ircmd_play();
                return;
            }
        }        
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT//Jack added 04/11/13
    if(ir_num_timer)
      ir_continuous_num_clr();
#endif

    #ifdef FBS_NOT_PLAY
    if(adv_search_time >= MAX_FF_RATE)
      adv_search_time = 1;      
    #endif
        if (adv_search_time < MAX_FF_RATE) {
            if((cd_type_loaded==CDDA)||(cd_type_loaded==CDROM)) {
                if(adv_search_time<2 && !user_mute) {
                    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020614
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
                    } else {
#ifdef MP3_CD_FF1_BF1_MUTE//YX822BC//nono 2-8-21 10:43
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
#elif defined(CNTR_5SPK_VOLUME)
                        int i,read_volume;
                        for (i=0; i<7; i++) {
                            read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
                            if(i==0)
                                {
#ifdef CNTR_5SPK_TYPE_2 //linrc add 2004-10-11 11:08
                                    Set_5SPK();
#else
                                AUDIF_Set_Volume(volume_5SPK[0]);//2004AUDDRV AudioSetVolume(volume_5SPK[0]);
#endif
                        }
                            else
                                DSP_AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);//2004AUDDRV AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);
                        }
#else
                        AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
#endif
                    }
                } else {
                    AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
                }
            }

            calculate_fw_time_param();
            
        #ifdef FASTPLAY_FIVE_LEVEL//zhaoyanhua 2004-5-17 17:13
            if (adv_search_time == 0)
            {   
                chg2normal_play(FAST2NORM|PAUSE2NORM|SLOW2NORM,REALPLAY);
                pe_run=1;

                OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);
                #ifndef OP_FASTPLAY_FIVE_LEVEL   //caoh 2005-5-8 10:58               
                PrintOsdMsg(STR_OS_PLAY, 0, 0,0);  
                #endif                 
                //ircmd_play_resume();
            }
            else
            {
        #endif
            play_state=VCD_STATE_FASTFORWARD;
            fast_play_post_proc();
        #ifdef FASTPLAY_FIVE_LEVEL
            }
        #endif      
            printf ("FF ----- adv_search_time :%d---\n",adv_search_time);

#ifdef SPHE1000_DVDSTATE_CALLBACK
        if(!adv_search_time)
            OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);
        else
            OSD1000ISP_STATUS(adv_search_time, OSDIR_FF);
#endif
        }
        else 
        {
            #if !defined(FASTPLAY_FIVE_LEVEL)//if more than MAX_FF_RATE, no function.
            ircmd_play();
    		#endif
            
            #if defined(SHINCO_DVD)||defined(OP_FASTPLAY_FIVE_LEVEL)
           ircmd_play();
           #endif   
        }
    }
#ifdef SUPPORT_PRE_NEXT_GOTO_CHANGETODISPLAY
    if((t_disp==1)&&(play_state==VCD_STATE_FASTFORWARD))  //lyc add 2006-2-20
     {
       	t_disp = 0;
       	disp_mode = 0;
       	ircmd_display();
    }
#endif
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
//}
}

/*
**calculate adv_search_time parameter
*/
#ifdef FASTPLAY_FIVE_LEVEL
/*
 * Description;
 *    if adv_search_time > 0, now in FF state, if enter "FB" will increase its FB rate.
 *    
 *   FB rate :-2 -4 -8 -16 -32
 *   FF rate : 2  4  8  16  32 
 *
 */
static inline   void    calculate_bw_time_param()
{
    if (adv_search_time > 0) 
    {    
        if (adv_search_time == 2)
            adv_search_time = 0;//adv_search_time = 0;
        else
            adv_search_time = adv_search_time/2;
        
    }
    else
        adv_search_time = adv_search_time*2;    
}
#else
static inline   void    calculate_bw_time_param()
{
#ifdef FW_BW_MAX_60S
    
    if( (adv_search_time==(-5))||(adv_search_time==(-30) ) ) 
        adv_search_time*=2;
    else if(adv_search_time==(-10) )
        adv_search_time*=3;
    else
        adv_search_time*=5;
#elif defined(BBK_DVD)//FW_BW_MAX_60S
        adv_search_time*=2;
#else//FW_BW_MAX_60S
        if(adv_search_time==(-8)) 
            adv_search_time=-20; 
        else
            adv_search_time*=2;
#endif//FW_BW_MAX_60S

}
#endif//ifdef FASTPLAY_FIVE_LEVEL

/*
** fast backward
*/
void    ircmd_backward(void)
{

#ifdef ORITRON_HK_DVD //qinhua,add,2006-2-16 9:53
  #ifdef SUPPORT_QUICKTIME
 if ((iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].file_type == CDROM_M4A)||(GetCurrentFileType() == CDROM_AAC))
  {
       invalid_key();
            return;	
  }
  #endif  

  #ifdef SUPPORT_WAV
   if(GetCurrentFileType() == CDROM_WAV) 
   {
   invalid_key();
   return;	
  }
  #endif 

#endif //#ifdef ORITRON_HK_DVD //qinhua,add,2006-2-16 9:53

#ifdef USE_BW_SR   //zhongshan 050718
    if((play_state ==  VCD_STATE_PAUSE)||(play_state == VCD_STATE_SLOW))
    {
        ircmd_bw_sr_slowmotion();
        return;
    }   
#endif
    
#ifdef PMP_DVD ////kenny add 2005/7/9
    
    if(pFsJpeg->gifsState == FS_STATE_INIT)
    return;
#endif    
 
//#ifndef SDRAM_16Mb_Mode//libing 2005-5-26 11:44   
#if defined( BACKWORD_AFTER_PAUSE_SLOW )//libing 2005-5-26 11:44//caoh 2005-4-21 20:18
if((cd_type_loaded!=CDDA)&&(cd_type_loaded!=CDROM_WMA)&&(cd_type_loaded!=CDROM_MP3)&&(cd_type_loaded!=CDROM_JPEG))
{
    if(play_state==VCD_STATE_PAUSE)
    {       
        ircmd_bk_slow();
        return;
    }else if(play_state==VCD_STATE_SLOW)
    {
        ircmd_bk_slow();
        return;
    }
}       
#endif
//{//if(play_state==VCD_STATE_PAUSE)
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#if defined BBK_DVD|| defined FASTPLAY_FIVE_LEVEL//zhaoyanhua add 03-11-5 15:18
    #define MAX_FB_RATE     -32
#elif defined(FW_BW_MAX_60S)
    #define MAX_FB_RATE     -60
#else
    #define MAX_FB_RATE     -20
#endif


#if defined(MP3_ONLY_STOP_TO_GUI)&&defined(MODIFY_MP3_ONLY_STOP_TO_GUI)//nono add 4-8-10 11:00
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //only in FsMP3mainloop,can use "REPAB"
        )
    {
        invalid_key();
        return;
    }
#endif

#ifdef NEW_NEXT_FORWARD_IN_A_KEY
    //if( (bIrSkipState==0)&&(key_data_flag==0) )
    if( (bIrSkipState!=1)&&(key_data_flag==0) )//2004-5-5 15:17
    {
         bIrSkipState = 1;
         rep_ir_times = 0;
         bIrSkipCnt = 0;
         return;
    }


    if(still_timer && cd_type_loaded==CDDVD)//NONO 4-8-20 15:18
    {
        invalid_key();
        return; 
    }


#endif//NEXT_FORWARD_IN_A_KEY

#ifdef SUPPORT_MIDI_MENU_SEL 
    if(gIsMidiSelMenu) 
    {
        return;
    }           
#endif

#ifdef RECORD_PER_SECOND                        //avoid bug  gerry  2-12-4 9:48
    if ((cd_type_loaded==CDROM)&&(Is_MP3_STATE()))
    {
        resumeMSF=0;
    }
#endif

#ifdef SUPPORT_NESGAME
    if ( Is_GAME_STATE() ) {
        invalid_key();
        return;
    }
#endif
/*
    if (GetCurrentFileType() == CDROM_MP4) // Robert 2004/01/30, temporarily
    {
        invalid_key();
        return;
    }
*/
#ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 9:40
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //when play with normal speed,can use "FB"
        )
    {
        invalid_key();
        return; 
    }
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE // Robert 021015
    if(Is_OTHER_STATE() && play_state == VCD_STATE_MP3_FILELIST)
    {
        invalid_key();
        return;
    }
#endif

#ifdef SUPPORT_CDG    //terry,2003/8/7 12:40AM
    if(is_cdg_disc(1)) return;  
#endif

#ifdef ALCO_DVD_UI //added 04/12/31
    if((disp_time==0) && (disp_trk_now==1))
        return;
#endif

    if ( Is_JPEG_STATE()) {
        invalid_key();//nono 20030804
        return;
        //ircmd_post_func(CMD_FUNC | CMD_FUNC_BACKWARD);
    } else if(!chk_speed_state(UOP_BW))         /* alan 02-05-27 modified to reduce code size */
    {
    #ifdef FASTPLAY_FIVE_LEVEL//zhaoyanhua add 2004-5-13 15:37
        if (adv_search_time == 0)
            adv_search_time = -1;
    #else        
        if(adv_search_time>=0) adv_search_time=-1;
    #endif//ifdef FASTPLAY_FIVE_LEVEL
#ifdef CDMP3_2XMAX        //freyman 2003-8-6 10:06 added, When CD, MP3 only need 2X speed
        if((cd_type_loaded==CDDA)||(cd_type_loaded==CDROM))
        {
            if(adv_search_time==-2)
            {
                ircmd_play();
                return;
            }
        }        
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT//Jack added 04/11/13
    if(ir_num_timer)
      ir_continuous_num_clr();
#endif

    #ifdef FBS_NOT_PLAY
    if(adv_search_time <= MAX_FB_RATE)
      adv_search_time = -1;
    #endif
        if (adv_search_time > MAX_FB_RATE)
        {
            if((cd_type_loaded==CDDA)||(cd_type_loaded==CDROM))
            {
                if(adv_search_time>(-2) && !user_mute)
                    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020614
                        AUDIF_Set_Volume(0);//AudioSetVolume(0);
                    } else {
#ifdef MP3_CD_FF1_BF1_MUTE//YX822BC//nono 2-8-21 10:43
                        AUDIF_Set_Volume(0);//AudioSetVolume(0);
#else
                        {
#ifdef CNTR_5SPK_VOLUME
                            int i,read_volume;
                            for (i=0; i<7; i++) {
                                read_volume=ReadFromI2c(0xa0,ADDR_I2C_VOLUME+i,(BYTE *)&audio_volume,sizeof(audio_volume));
                                if(i==0)
                                {
#ifdef CNTR_5SPK_TYPE_2 //linrc add 2004-10-11 11:08 -->ESS is like this type
                                    Set_5SPK();
#else
                                    AUDIF_Set_Volume(volume_5SPK[0]);//2004AUDDRV AudioSetVolume(volume_5SPK[0]);
#endif
                        }
                                else
                                    DSP_AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);//2004AUDDRV AudioIOControl(FLSPKGAIN+i-1,volume_5SPK[i],0);
                            }
#else
                            AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
#endif
                        }
#endif
                    }
                    else
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
            }

    //wanghaoying delete 2004-07-28

            calculate_bw_time_param();
            
        #ifdef FASTPLAY_FIVE_LEVEL//zhaoyanhua 2004-5-17 17:10
            if (adv_search_time == 0)
            {    
                chg2normal_play(FAST2NORM|PAUSE2NORM|SLOW2NORM,REALPLAY);
                pe_run=1;

                OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);
                #ifndef OP_FASTPLAY_FIVE_LEVEL//caoh 2005-5-8 10:59
                PrintOsdMsg(STR_OS_PLAY, 0, 0,0);  
                #endif
                //ircmd_play_resume();
            }
            else
            {
        #endif
        #ifdef SUPPORT_MP4  // 2004/10/13 yltseng
                if( GetCurrentFileType() == CDROM_MP4 && !file_support_tricky_play() )//yltseng 4-10-12 17:38
                {
                    avd_fast_state();
                }
                else
        #endif                
                {
                    play_state=VCD_STATE_FASTBACKWARD;
                    fast_play_post_proc();
                }
        
        #ifdef FASTPLAY_FIVE_LEVEL
            } //if (adv_search_time == 0) 
        #endif
            printf ("FB ----- adv_search_time :%d---\n",adv_search_time);
        
#ifdef SPHE1000_DVDSTATE_CALLBACK
    if(!adv_search_time)
        OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);
    else
        OSD1000ISP_STATUS(-adv_search_time, OSDIR_FR);
#endif
        }
        else
        { 
            #if !defined(FASTPLAY_FIVE_LEVEL)//if less than MAX_FB_RATE, no function.
            ircmd_play();
    		#endif

            #if defined(SHINCO_DVD)||defined(OP_FASTPLAY_FIVE_LEVEL)
          	ircmd_play();  
         	#endif
         }
    }
#ifdef SUPPORT_PRE_NEXT_GOTO_CHANGETODISPLAY
    if((t_disp==1)&&(play_state==VCD_STATE_FASTBACKWARD))  //lyc add 2006-2-20
     {
       	t_disp = 0;
       	disp_mode = 0;
       	ircmd_display();
    }
  #endif  
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).

}


//
// ircmd_repeat_all
//      0:off
//      1:repeat current track
//      2:repeat all track
//
void ShowRepInfo(void)
{
    int id=0,r=REGION1;     /* alan 02-05-27 modified */

    if(rep_mode==REPEAT_TRACK)
    {
        if(cd_type_loaded == CDDVD)  /* chapter */
        {
#ifdef DVD_AUDIO        // alan, 2002/11/13 03:13と
            if (dAMG_LSN)
                id=STR_OS_TRACK;
            else
#endif
#ifdef  NINTAUS_OSD_STR         //Maoyong 2004.03.05
                id=STR_OS_REP_CHAPTER;
#else           
                id=STR_OS_CHAPTER;
#endif  //NINTAUS_OSD_STR   
        }
        else
            id=STR_OS_REP_1;
    }else if(rep_mode==REPEAT_DIRECTORY)    // for mp3 repeat dir mode,panxing, 2002-3-8
    {
        if(cd_type_loaded == CDROM)  /* directory */
            id=STR_OS_REP_DIR;
    }
    #ifndef SUPPORT_REPEAT_PMP
    else if(rep_mode==REPEAT_DISC)
    {
        if(cd_type_loaded == CDDVD)    /* title */
        {
#ifdef DVD_AUDIO        // alan, 2002/11/13 03:13と
            if (dAMG_LSN)
#ifdef NINTAUS_OSD_STR  //Maoyong 2004.03.05
                id= STR_OS_REP_GROUP;
#else
                id=STR_OS_GROUP;
#endif
            else
#endif
#ifdef  NINTAUS_OSD_STR         //Maoyong 2004.03.05
                id=STR_OS_REP_TITLE;
#else           
                id=STR_OS_TITLE;
#endif  //NINTAUS_OSD_STR   
        }
        else
            id=STR_OS_REP_ALL;
    }
#endif   //////////////////////ifndef SUPPORT_REPEAT_PMP
#ifdef DVD_REP_ALL_TITLE//terry,2003/10/18 04:55PM  
    else if( (rep_mode==REPEAT_DVDDISC)&&(cd_type_loaded == CDDVD) )
    {
        #ifdef ONLY_DVD_PROG_REP_ALL//shenyj add for alco1950 0303
        if(!prog_cnt)
        {
            id=STR_OS_OFF;
            rep_mode = REPEAT_IDLE;
            rep_track = 0;
        }
        else
        #endif
        id=STR_OS_REP_ALL;
    }
#endif  
    #ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT //chenzhao 2006-4-19 17:55 .
    else if(rep_mode == REPEAT_ALL_DISCS)
    {
         id=STR_OS_REP_DISCS;
    }
    #endif
    else
    { //repeat cancel

#if defined(VALID_PROGROM_REPEAT)&&!defined(STOP_IN_PROG_END)&& !defined(ALCO_DVD_UI)//zhuyanfeng modified 2004/10/25 //to realize program repeat off function when define STOP_IN_PROG_END
        if(prog_cnt)//nono for hyoptics
        id=STR_OS_REP_ALL;
        else
#endif//VALID_PROGROM_REPEAT

        id=STR_OS_OFF;
        
        rep_mode = REPEAT_IDLE;
        rep_track = 0;
    }
    if(full_scrn&SOUND)//nono 2-6-7 22:56 to avoid repInfo cover 3D REGION2.
        r=1;

    if( (full_scrn==0)||(full_scrn&GOTO)||(full_scrn&MARK) )   //add MARK condition to show rep OSD
    {
        if( (sys_cmd==0)&&(!is_dvd_prohibit_key()) ) /* alan 02-05-27 modified */
            r=1;
        //if(RegionOnOff[REGION2][2]==STR_OS_REP)//nono 2-6-3 11:09 for fuss
        //PrintOsdMsg(STR_OS_SPACE,REGION2,0,0);
    }
    //PrintOsdMsg(STR_OS_REP|(id<<8),r,1,4);

     OSD1000ISP_STATUS(rep_mode, OSDIR_REPEAT);

#ifdef NEWSTYLE_WINDOW
    if(full_scrn&MESSAGE)//xiongyuyue 20030707
    {
        if(id==STR_OS_OFF)
            psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][id]);
        else
            psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][id]);
    }
    else
#endif
    {
    #ifdef OP_PLAYMODE
            if(shuffle_flag==0)//libing
    #endif  
    
    #ifdef  DVD_ALWAYS_SHOW_REPMODE //zxb 2005-12-30 23:06 tcl
    if(cd_type_loaded==CDDVD && id != STR_OS_OFF)
    	PrintOsdMsg(STR_OS_REP|(id<<OSDSTR_ID_TOTL_BIT),r,0,4);
    else
    #endif
    
    PrintOsdMsg(STR_OS_REP|(id<<OSDSTR_ID_TOTL_BIT),r,1,4);
    #ifdef OP_PLAYMODE
            else
    PrintOsdMsg(STR_OS_REP_CNL,r,1,0);      
    #endif
    if( 0 )//(RegionOnOff[REGION2][1]==STR_OS_REP)&&(RegionOnOff[REGION1][1]==STR_OS_REP) )//nono 2-6-24 19:09 for fuss
    {
        PrintOsdMsg(STR_OS_SPACE,REGION2,1,0);
    }
    }
}


#ifdef REPEAT_AB_REPEAT_IN_ONE_EKY
extern int repeat_key;
#endif
void ircmd_repeat_all(void)
{
    
    printf("*********pFsJpeg->gifsState=%d\n",pFsJpeg->gifsState);
    #ifdef DISP_TIME_AFTER_STATE
    	vfd_disp_rep_flag = 1;
    #endif
    
    #ifdef SUPPORT_MULTI_PARTITION//liweihua mod 2004-11-2
    if((pFsJpeg->gifsState == FS_STATE_HDD)
    #ifdef FAT_FILE_MODE
        ||(pFsJpeg->gifsState == FS_STATE_MODE)
#endif              
        ||(!(pmp_get_user_flag()&PMP_USER_AUTO_PLAY))  /////////yangli mod for rep key in auto play2005/9/26   
        )
    {
        invalid_key();
        return;
    }
    #endif
#ifdef SKYWORTH_DVD  
  if(cd_type_loaded==CDROM)
     if(shuffle_flag)
     {
        invalid_key();
        return;
     }
#endif              
    
    int id=0;

#ifdef SUPPORT_MIDI_MENU_SEL
    if(gIsMidiSelMenu)  return;
#endif

#ifdef SKYWORTH_DVD  //wangap 3-10-10 16:20
 ircmd_cancel(C_SHOW | C_PLAY);
#endif

    #ifdef IRCMD_DBG
    printf("================ repeat_all ===============\n");
    #endif

    /*
    #if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)
        #ifdef NEWSTYLE_WINDOW
            if ( (full_scrn&MESSAGE) && (action_click==2) ) // alan, 2003/8/28 05:32PM
                action_click = 0;
            else
        #endif
            action_click = 1; //Jeff 20030506
    #endif
    */
    //Jeff change, 20031006, fix press IR(GOTO) "repeat-mode" will be "automatic" toggled
    #if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW)
        #ifdef NEWSTYLE_WINDOW          //Maoyong 2004.02.14
            if ( (full_scrn&MESSAGE) && (action_click==2) ) 
                action_click = 0;
            else
        #endif
        action_click = 1; //Jeff 20030506
    #else
        #ifdef NEWSTYLE_WINDOW
            if ( (full_scrn&MESSAGE) && (action_click==2) ) // alan, 2003/8/28 05:32PM
                action_click = 0;
        #endif
    #endif

    #ifdef SUPPORT_NESGAME
    if ( Is_GAME_STATE() ) {
        rep_mode = 0;
        invalid_key();
        return;
    }
    #endif

#ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 9:40
    if ( (Is_MP3_STATE()) 
       && (play_state == VCD_STATE_MP3_FILELIST) //when play with normal speed,can use "repeat all"
        )
    {
        invalid_key();
        return; 
    }
#endif

    if (cd_type_loaded==CDDVD) {
        if(is_dvd_menu()) {
        #ifdef OP_PLAYMODE //libing  
            id=0;
        #else 
            id=1;
        #endif
        }
    } else
        if((cd_type_loaded!=CDDA)&&(cd_type_loaded!=CDROM)) {
            #ifndef SKYWORTH_DVD  //wangap 3-10-10 16:20
            if( IsPBCOn() ) {
                id=1;
            }
            #endif
        }

#if !defined(GBM_DVD)&&!defined(SKYWORTH_DVD)&&!defined(JIEKE_DVD) &&!defined(VALID_PROGROM_REPEAT)&&!defined(ORITRON_HK_DVD) //WTHSIN 031113
        if(prog_cnt)//wuxiaofeng 2004-02-26 changed to VALID_PROGROM_REPEAT for available REPEAT in PROG mode.
            id=1;
#endif


        if( (rep_ab_mode==REPEAT_FIND_B)||(id==1) )
        {
#ifdef NEWSTYLE_WINDOW  //xiongyuyue
        if(full_scrn&MESSAGE)
        {
            ShowRepInfo();  //to avoid the bug:when rep_ab & rep_mode, MESSAGE error. zhaoyanhua 2003-12-1 16:11        
            //psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_OFF]);           
        }
        else
#endif
          #ifdef REPEAT_AB_REPEAT_IN_ONE_EKY
            {
            rep_ab_mode=REPEAT_AB_IDLE;
            show_repeatAB(1);   
            }        
           #else
            {
           #ifdef REPEAT_KEY_CANCLE_REPEAT_AB//shenyj add for alco 19261 1017
           rep_ab_mode=REPEAT_AB_IDLE;
           #else
            invalid_key();
            return;
           #endif
        }
      #endif
        }
#ifdef REPEAT_SHUFFLE//nono    20021015             /* alan 0425 */
#ifndef ONLY_SHUFFLE
        if(shuffle_flag)
        {
            ircmd_shuffle();

        }else
#endif
        {
#endif

#ifdef NEW_SEARCH_OSD // ren 910725
            if(key_up_down==1)
            {
                rep_mode++;
                if((cd_type_loaded!=CDROM)&&(rep_mode==REPEAT_DIRECTORY)) rep_mode++;
            }
            else if(key_up_down==0)
            {
                rep_mode--;
                if((cd_type_loaded!=CDROM)&&(rep_mode==REPEAT_DIRECTORY)) rep_mode--;
                if(rep_mode==0xFF) rep_mode = REPEAT_DISC;
            }
#else
    //#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW  // alan, 2003/8/28 05:26PM
            if(action_click)
    //#endif
            {
            rep_mode++;
                #ifdef DISABLE_REPEAT_DIR_AT_JPEG//20040206 FOR tonic DVD
                if(cd_type_loaded==CDROM&&pFsJpeg->gbfsPictureCD == 1&&rep_mode==REPEAT_DIRECTORY)
            rep_mode++;
                #endif
                
                #if defined(DISABLE_REPEAT_DIR_AT_MP3_PROGRAM_REPEAT)||defined(VALID_PROGROM_REPEAT)      //zhuyf 2004/11/10
               if(cd_type_loaded==CDROM&&(Is_MP3_STATE()&&(prog_cnt))&&rep_mode==REPEAT_DIRECTORY)
                rep_mode++;
               #endif
                
            }
            // jump over REPEAT_DIRECTORY, panxing, 2002-3-11
           #ifdef MP4_NO_REPEAT_DIRECTORY//shenyj add for alco
            if(((GetCurrentFileType() == CDROM_MP4)||(GetCurrentFileType() == CDROM_AVI))&&(rep_mode==REPEAT_DIRECTORY))
                rep_mode++;            
            else if((cd_type_loaded!=CDROM)&&(rep_mode==REPEAT_DIRECTORY)) 
                rep_mode++;
           #else
           if((cd_type_loaded!=CDROM)&&(rep_mode==REPEAT_DIRECTORY)) 
                rep_mode++;
           #endif
            #if defined(VALID_PROGROM_REPEAT)&&!defined(ALCO_DVD_UI)   //sunzhh add for it performing "next" if you press "prev" when program play 20050705
            if((prog_cnt)&&(rep_mode == REPEAT_DISC))
                rep_mode = REPEAT_IDLE;
            #endif
            // 2004/04/14 yltseng mark, no need now
/*
#ifdef SUPPORT_FILE_SYSTEM_MODE  // Robert 021018
            if (Is_OTHER_STATE())
                if (rep_mode > REPEAT_TRACK)
                    rep_mode = 0;
#endif
*/
#endif

                if(cd_type_loaded!=CDDVD)
                    {
 rep_track=cd_trk_now; 
            #ifdef REPEAT_AB_REPEAT_IN_ONE_EKY
             if (rep_mode ==4)
                        repeat_key= 0;  
             #endif
                    }
                else 
                    rep_track=get_tt_info(DISP_TT);
            {
            #ifdef REPEAT_AB_REPEAT_IN_ONE_EKY      
                   if (rep_mode ==5)
                       repeat_key= 0;
            #endif
            }
#ifdef REPEAT_SHUFFLE //nono 20021015
#ifndef ONLY_SHUFFLE
                if ( (cd_type_loaded!=CDDVD) && (rep_mode==REPEAT_MAX) )
                {
                    rep_mode=0;
                    rep_track=0;
                    #ifdef  VALID_PROGROM_REPEAT
                    if(!prog_cnt)        //2004-5-13 19:09 linrc modify,for that when PRG_PLAY and call shuffle 
                    ircmd_shuffle();    //it random in all disc,but still dispaly PRG_PLAY
                    #else
                    ircmd_shuffle();
                    #endif
                }else
#endif
#endif
#ifdef SKYWORTH_DVD  
        if(!rep_mode)
        {
            disc_st_time = M2I(gettrkmsf(cd_trk_lo_now));//wangap 1029
            pbcoff_init();
        }
#endif     
        #if defined(VALID_PROGROM_REPEAT) && defined( DVD_PROG_DISABLE_REPEAT_TITLE)
        if((prog_cnt) && (cd_type_loaded==CDDVD) && (rep_mode==REPEAT_DISC))
            rep_mode++;
        else if((cd_type_loaded==CDDVD) && (rep_mode==REPEAT_DVDDISC))
           ;//rep_mode = 0;
        #endif
                    ShowRepInfo();
        #ifdef NEWSTYLE_WINDOW//zhaoyanhua add 2003-12-8 19:55          
        if(full_scrn&MESSAGE)       
            updateRepeatMode();
        #endif
#ifdef REPEAT_SHUFFLE //nono 20021015
        }
#endif
}

void show_repeatAB(int t)
{
    UINT8 id[]={STR_OS_REP_AB_CNL,STR_OS_REP_A,STR_OS_REP_AB};

    if(t || rep_ab_mode)
        PrintOsdMsg(id[rep_ab_mode],REGION1,t,0);
}

extern UINT32 _myTime,myTime;
extern UINT32 oldmp3ReadLen,_mp3ReadLen;
extern UINT32 asf_AB_start_pck;
extern int len_keep;

//Repeat A, B  function
//nono 4-2-6 22:28 for 108mhz dts-cd 3d disable.
#ifdef REPEAT_AB_TOO_SHORT_DISABLE_3D
BYTE repeat_ab_time_flag = 0;
#endif//REPEAT_AB_TOO_SHORT_DISABLE_3D

#ifdef REPEAT_AB_REPEAT_IN_ONE_EKY
 int repeat_key;
#endif

#ifdef MINUS_VR_AUTH_PLAYBACK
extern UINT16 pVOBU_Entry;
extern INT8	bDVDminusVR;
#endif


/************************************************************************************
* function: ircmd_repeat_ab()
* Description:
*     1th repeat_ab occur: rep_ab_mode=REPEAT_FIND_A and get_a_addr=1 and get the first time stamp
*     2th repeat_ab occur: compare repStart and repEnd. If repEnd>repStart, initiate the time stamp again.
*                                      Run ircmd_post_func().
*     3th repeat_ab occur: cancel the repeat_ab.                                
* 
*  Modify History
*     2006/02/10  robert.chang    
*
*************************************************************************************/
 
void ircmd_repeat_ab(void)    // 0:repeat off
// 1:repeat A
// 2:repeat B
{
    printf("*********pFsJpeg->gifsState=%d\n",pFsJpeg->gifsState);
    #ifdef DISP_TIME_AFTER_STATE
    	vfd_disp_ab_flag = 1;
    #endif
    
    #ifdef SUPPORT_MULTI_PARTITION//yangli  mod 05/6/3
    if((pFsJpeg->gifsState == FS_STATE_HDD)
    #ifdef FAT_FILE_MODE
        ||(pFsJpeg->gifsState == FS_STATE_MODE)
        ||(pFsJpeg->gifsState == FS_STATE_JPEG)
      //  ||(pFsJpeg->gifsState == FS_STATE_OTHER)//kenny mark 2005/7/11
        ||(pFsJpeg->gifsState == FS_STATE_INIT)
        #endif
        )
    {
        invalid_key();
        return;
    }
    #endif
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef REPEAT_AB_REPEAT_IN_ONE_EKY
      #ifdef MP3_NO_REPEAT_AB
      if(Is_MP3_STATE()&& cd_type_loaded == CDROM)
        {
          repeat_key=1;
        }     
      #endif
#if defined(EASTECH_DVD_DP3240_D)||defined(EASTECH_DVD_DP2070_D)
if( Is_JPEG_PLAY_STATE() && (cd_type_loaded == CDROM) ) // yltseng v3.1
#else
if( ((pFsJpeg->gbfsSlide != 0)||Is_JPEG_PLAY_STATE()) && (cd_type_loaded == CDROM)  )   
#endif
{
        repeat_key=1;
    // ircmd_repeat_all();  
    // return;
}
#if defined(EASTECH_DVD_DP3240_D)||defined(EASTECH_DVD_DP2070_D)
    // mimitsai merge from dp2070/dp3240

    if( IsPBCOn() )
    {
        rep_mode=0;
        repeat_key= 0;
    }
#endif

 if(repeat_key==1)
    {
     ircmd_repeat_all();    
     return;
    }
 #endif

#ifdef SUPPORT_MP4  //liumzh 2004-9-14 15:24 , due to play DivX movies,change from one to another,press A-B immediately,it will be no function
    if( ( GET_MP4_TIME() == 0 ) && (cd_type_loaded == CDROM) && (GetCurrentFileType() ==  CDROM_MP4) )  
        {
           //invalid_key();
		#if defined(SUPPORT_OGG)|| defined(SUPPORT_ASF)
		if( !IS_FILE_TYPE_OGG()&&!(IS_FILE_TYPE_ASF()&&audio_only)) // ycwen for repeat AB, 2005/12/9 
		#endif														// by roger for asf audio only 06-04-19
           return;
        }
#endif

#ifdef SUPPORT_MP4  // 2004/07/27 yltseng   
    if( IsUserControlDisabledByTrickyPlay( IRC_AB ) )
    {
        invalid_key();
        return;
    }
#endif

#ifdef  INVALID_REPEATAB_IN_DVD_MENU
    if(is_menu())
    {
        invalid_key();
        return;
    }
#endif//#ifdef  INVALID_REPEATAB_IN_DVD_MENU

/*Here deleted by xyy 2004-8-5 */

    int get_A_addr=0,tu=0, get_B_addr=0, is_ab_swap=0, abDiff;
    UINT32 addr;
    
#ifdef FF_FR_NOT_REPEATAB    //fengjl 3-12-29 11:16 bbk need not repeat ab when FORWARD or BACKWARD state
    if(adv_search_time!=0)
    {
        invalid_key();
        return;
    }
#endif

#ifdef REPEAT_AB_INVALID_WHEN_PAUSE
    if(play_state == VCD_STATE_PAUSE) 
    {
        invalid_key();
        return;
    }
#endif
    
#ifdef SUPPORT_MIDI_MENU_SEL  //ouyang add for priority key in midi prog 2005-7-1 16:38
    #ifdef SUPPORT_PRIORITY_KEY
         if(gIsMidiSelMenu)
    {
            ircmd_post_func(CMD_FUNC|CMD_FUNC_REPAB);
    return;
            }
    #endif
#endif

#ifdef IRCMD_DBG
    printf("repeat_ab in,s_msf:%x play_state:%x rep_ab_mode:%x\n",s_msf,play_state,rep_ab_mode);
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE    //nono 3-6-24 16:41
    //if (GetCurrentFileType() == CDROM_MPG)
    //if (Is_OTHER_STATE())
    //Maoyong 2004.04.22, now MP4/MPG repeat ab ok, just in play state can use repeat_ab, not in FILE_LIST
    if( Is_OTHER_STATE() && (pFsJpeg->gifsState == FS_STATE_LIST) ) 
    {
        invalid_key();
        return;
    }
#endif

#ifdef SUPPORT_NESGAME         //kubby,3-9-10 23:57
    if ( Is_GAME_STATE() ) {  
        invalid_key();
        return;
    }
#endif
#ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 9:40
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //only in FsMP3mainloop,can use "REPAB"
        )
    {
        invalid_key();
        return; 
    }
#endif

#ifdef SUPPORT_CDG    //terry,2003/8/7 12:40AM
    if(is_cdg_disc(1)) return;  
#endif

    if(cd_type_loaded==CDDVD)
        addr=play_abs_addr;
    else
        addr= s_msf;

    if(rep_ab_mode==REPEAT_AB_IDLE)
    {
        //counter_down = 10;
        get_A_addr=1;
        rep_ab_mode = REPEAT_FIND_A;
    }
    else if(rep_ab_mode==REPEAT_FIND_A)
    {
        // 2004/05/11 yltseng, change value from 10 to 5, to reduce the A-B gap delay when
        // playing WMA with low bit rate.
        // but this is not the best way, we should use bitrate to calculate the correct A-B gap delay.
        abDiff = addr - repStart;
		
        if(  (-5< abDiff) && (abDiff < 5) )
        {
            //repeatA-B too short, when repeatA-B is too short, ircmd_repeat_ab() will not be called
            return; //Jefftest
        }

#if 0//def REPEAT_AB_TOO_SHORT_DISABLE_3D        
        if ( (addr-repStart) < 100 ) { //Jeff 20021112
            //repeatA-B too short, when repeatA-B is too short, ircmd_repeat_ab() will not be called
           
           if(rep_ab_mode==REPEAT_FIND_A)//wangfeng 2004-2-18 18:06
                repeat_ab_time_flag=0;      
            else
           repeat_ab_time_flag=1;
        }
#endif//REPEAT_AB_TOO_SHORT_DISABLE_3D
	if(addr < repStart) {
			  
		repEnd = repStart;
		is_ab_swap = 1;		   
	}
	else {
		repEnd=addr;		
	}
	get_B_addr = 1;			
       rep_ab_mode = REPEAT_FIND_B;
     
    }else
    {
       #ifdef REPEAT_AB_REPEAT_IN_ONE_EKY
             #ifdef PBC_ON_NO_REPEAT
                 if(!IsPBCOn())
                        {
                        repeat_key=1;
                    }       
              #endif     
     #endif
     
        rep_ab_mode = REPEAT_AB_IDLE;
        tu=1;

        #if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
        len_keep = 0;
        #endif
        
        #ifdef SUPPORT_REP_READ //Maoyong 2004.06.11
        if(full_scrn & READ){            
            AUDIF_Demute();//2004AUDDRV AudioDemute(); 
            ClearReadMode();
        }
        #endif
    }

    OSD1000ISP_STATUS(rep_ab_mode, OSDIR_AB);

    if(get_A_addr || is_ab_swap)
    {
        if(cd_type_loaded==CDDVD)
            DVD_get_time(0);
        //Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio repeat func//
        else if ((GetCurrentFileType() == CDROM) || (GetCurrentFileType() == CDROM_AAC))
        {
            //terry,2003/6/24 10:47と
            _mp3ReadLen = mp3ReadLen;
            _myTime = myTime;
        }
#ifdef SUPPORT_WMA
        else if (GetCurrentFileType() == CDROM_WMA)
        {
            asf_AB_start_pck = asf_pck_current;
            #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua 2004-4-13
            if(media_type == MEDIA_CARD)
                len_keep = cardFile.iLeaveSize;
            else
            #endif
            len_keep = lba_st.len;
        }
#endif
#ifdef SUPPORT_MP4
        else if (GetCurrentFileType() == CDROM_MP4)
        {
            extern UINT32 nMP4timeA;
            len_keep = lba_st.len;
        #ifdef SUPPORT_MPG_FILE_PARSER    
            if( IS_FILE_TYPE_MPG12() )// axel for repeat AB, 2005/10/17 yltseng
                nMP4timeA = addr;
            else
        #endif
        #ifdef SUPPORT_OGG
            if( IS_FILE_TYPE_OGG())// ycwen for repeat AB, 2005/12/9
                nMP4timeA = GET_OGG_TIME();
            else
        #endif        
//mark by roger 2006-06-08
//using GET_MP4_TIME() replace GET_ASF_TIME() 		
//		#ifdef SUPPORT_ASF//by roger 06-04-19 enable asf audio only repeat ab
//			if(IS_FILE_TYPE_ASF())
//				nMP4timeA = GET_ASF_TIME();
//			else
//		#endif
            nMP4timeA = GET_MP4_TIME(); //disp_time;    

        }
#endif

        // Robert 2004/02/23, set A's point to prior address.
        if (cd_type_loaded == CDSVCD)
            repStart = l2msf(msf2l(addr) - 200);
        else if ((cd_type_loaded == CDVCD10) || (cd_type_loaded == CDVCD20))
            repStart = l2msf(msf2l(addr) - 60);
        else
            repStart = addr;

#ifdef MINUS_VR_AUTH_PLAYBACK
		if(bDVDminusVR)
			repStartVOBU=pVOBU_Entry;	
#endif

    }

    if(get_B_addr) 
	{        	

#if defined(SUPPORT_ASF)&& defined(SUPPORT_ASF_PTS)
		// only for asf file
		//add by roger 2006-05-25
		if (IS_FILE_TYPE_ASF())		
		{
			// bug fix with when repeat b set , stc will be set by audio buffer almost filled
			// update audio_fPTS to current time for system set 
			//add by roger 2006-05-12		
			if (audio_only)
			{
				extern UINT64 latch_audio_pts;
				audio_fPTS=latch_audio_pts;
			}
		}
#endif	

        #ifdef SUPPORT_MP4 //zxb 2006-8-11 11:55 for compile err
		//bug fix with when first set b, it will occur noise
		//add by roger 2006-07-28
		if(!audio_only)
			do_adpcm_align();
		#endif	
            //kevinmonkey 050322 for fixing repeat AB and goto keeps FF/FB playback behavior
            chg2normal_play(FAST2NORM|PAUSE2NORM|SLOW2NORM,REALPLAY);
            
        //Simon 2006.4.13
        //For mp3 and mpeg on usb/card, let fsFile.c call ircmd_post_func
        //For WMA files, don't call ircmd_post_func
        {
            int bJumpToB = 1;
            UINT32 fileType = GetCurrentFileType();

        #if defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
            bJumpToB = !((media_type == MEDIA_CARD) && ((fileType == CDROM) || (fileType == CDROM_MPG)));
        #endif  
            
        #ifdef SUPPORT_WMA
            if (fileType == CDROM_WMA)
                bJumpToB = 0;
        #endif
            
            if (bJumpToB)
                ircmd_post_func(CMD_FUNC|CMD_FUNC_REPAB);
        }

    }		
    //Maoyong delect ShowReadMode() 2004.06.09
        show_repeatAB(tu);
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}
#ifdef REPEAT_AB_TOO_SHORT_DISABLE_3D
int ircmd_repeat_ab_time_is_too_short(void)
{
    return repeat_ab_time_flag;
}
#endif//REPEAT_AB_TOO_SHORT_DISABLE_3D


//void cancel_sound(void)
//void ircmd_3d2(void)
//void ircmd_3dsound(void)
#include "ircmd_3dsound.c"


/*
**  ircmd_channel
*/
void    ircmd_channel(void)
{
    UINT32 cType=0, wParam=0;  //ycwen 2006/8/1 AC3 Karaoke
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
   
    #ifdef MP4_NO_LR    //yaowh add 2005-3-27 23:46
    if (GetCurrentFileType() == CDROM_MP4)
    {
        invalid_key();
        return;
    }
    #endif
   
   #ifdef SUPPORT_MIDI
 if (MenuState == MENU_MULTI_INDEX_SEL)
    { 
        invalid_key();
        return;
    }
   #ifdef YUXING_MIDI_DVD    //ouyang add for mic AUTO 2004-12-6 10:22
    #ifdef SUPPORT_MIDI_MENU_SEL //Jeff 20031029
    {
    if (gIsMidiSelMenu) {  // mimitsai add for midi is playing 2004-12-16
    #ifdef SUPPORT_MIDI_VOCAL
        extern BYTE bIsMp3LyricSyn;

        if (bIsMp3LyricSyn==0)  return;
    #endif
    
      //  if (gIsMidiSelMenu==0)  return;
       }
    }//if (gIsMidiSelMenu) {  // mimitsai add for midi is playing 2004-12-16
    #endif //#ifdef SUPPORT_MIDI_MENU_SEL axel open for mp3 and midi channel2004-11-10 14:13
    #endif  //#ifdef YUXING_MIDI_DVD ouyang add for mic AUTO 2004-12-6 10:22
  #endif  //SUPPORT_MIDI ouyang 05-01-27
    #ifdef DISABLE_CHANNEL_AT_PREVIEW    //oujx for tonic
    if(play_state==VCD_STATE_PREVIEW||play_state==VCD_STATE_9FRAMES)
    {
        invalid_key();
        return;
    }
    #endif

#ifdef SUPPORT_FILE_SYSTEM_MODE    
    if ( Is_OTHER_STATE()&&(mpeg_audio==0) ) {
        invalid_key();
        return;
    }
#endif


//#if defined(QISHENG_DVD)||defined(DESAY_DVD)||defined(JIEKE_DVD)||defined(BBK_DVD)          /////zhangyu 03.8.15  
#ifdef CHANNEL_KEY_CONTROL_AUDIO
    if( (cd_type_loaded == CDDVD) || (cd_type_loaded == CDSVCD) )
    {
        ircmd_audio_language();
        return;
    } 
#endif
        
#ifdef CHNNAL_OFF_PROLOGIC_II //zhaoyanhua add 2004-2-11 13:15  
    if((setup_IsPrologicOn()) && (cd_type_loaded != CDDVD) && (cd_type_loaded != CDSVCD))
    {
        setup_OffPrologic_II();
    }
#endif//ifdef CHNNAL_OFF_PROLOGIC_II            
        
#ifdef SUPPORT_UART_COMMAND// Robert 020729
    IRSwitchVolMode();
#else

    #if defined(ADJUSTING_ACTION_VALID_RIGHT_NOW) ||defined(DVB_MULTI_CHANNEL)//kehw 2005-4-1
    action_click = 1; //Jeff 20030506
    #endif

    #ifdef SUPPORT_NESGAME
    if (Is_GAME_STATE()) {
        invalid_key(); return;
    }
    #endif

    if ((coding_mode_now == AUDIF_CODING_MODE_DTSCD) || (cd_subtype == CD_DTS) ||
        ((cd_type_loaded == CDDVD) && (!(dvd_karaoke_mode))))
    {
        invalid_key();
        return;
    }

    //when user set to SPDIF-BITSTREAM mode, all volume control commands are invalid
    //if ( setup_IsSet2SPDIF_Bitstream() || setup_IsSet2SPDIF_PCM() ) {
    //        psprintf(RegionValStr[REGION1],"SPDIF %s\n", Ch_hand);
    //        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    //        return;
    //}

//wanghaoying 2003-9-6 19:24 added for Idall want demute when switch channel under mute mode
#ifdef IDALL_DVD
    if(user_mute)
    {
        AUDIF_Demute();//2004AUDDRV AudioDemute();        
        OSD_OnOffRegion(OSD_OFF,1);
        user_mute = 0;
    }
#endif

    if (action_click)
    {
#if !defined(VTREK_DVD)&& !defined(NO_MIC)       //wanghaoying 2003-9-20 18:31
        if (dvd_karaoke_mode)
        {
            if (audio_channel == 0)
                audio_channel = 2;
        }
#endif
        audio_channel++;
    }

    if (audio_only==0)
    {
        // modified by potatooo, 20020510
        int max_chn = MAX_CH_NUM;
        if (setup_IsMICoff() && max_chn>2) 
        #ifdef SUPPORT_MIX_MONO		// diya 2006/8/3 05:44と
        	max_chn=3;
        #else   
        	max_chn=2;   // when MIC off, limit channel to 2??
        #endif
#ifdef DVB_MULTI_CHANNEL//kehw 2005-04-01
       if(system_state == SYSTEM_TS) //houyiwu for USB displayer of VCD karaoke 2005/04/21
       {
            max_chn=2;
       }
    
#endif

#ifdef NEW_SEARCH_OSD
        if ((audio_channel>max_chn)&&(audio_channel != 0xFF)) audio_channel=0;  // ren 910725
        if (audio_channel == 0xFF) audio_channel = max_chn;  // ren 910725
#else
        if (audio_channel>max_chn) audio_channel=0;  // ren 910725
#endif
    }
    else
    {
		#ifdef SUPPORT_MIX_MONO
			if (audio_channel>3)
		#else
			if (audio_channel>2)
        #endif
            audio_channel=0;
    }
    
    
    if (coding_mode_now == AUDIF_CODING_MODE_AC3) //ycwen 2006/8/1 AC3 Karaoke
    {
        switch (audio_channel)
        {
            case 0: //Both Vocal
                cType=0x60; 
                wParam=0x0000;
                break;
            case 3: //AUTO L
                if (setup_IsMICoff)
                {
                cType = 0x0a;
                wParam=0x0001;
                }
                else
                {
                cType=0x40; 
                wParam=0x0001;
                }
                break;
            case 4: //AUTO R
                cType=0x50;
                wParam=0x0001;                
                break;
            default:
                cType=audio_channel+1;
                wParam=0;
                break;            
        }
        AUDIF_Set_OutputMode(cType, wParam);
    }
    else
    {        
    	#ifdef SUPPORT_MIX_MONO		// diya 2006/8/3 05:45と
		//UINT32	cType; 
		int max_chn = MAX_CH_NUM;        		
		if (audio_channel == max_chn)
		{
			cType = 0x0a;
		}
		else
		{
			cType = audio_channel+1;
		}
		
		AUDIF_Set_OutputMode(cType, 0);//2004AUDDRV AudioSetOutputMode(audio_channel+1, 0);
    	#else
    	AUDIF_Set_OutputMode(audio_channel+1, 0);//2004AUDDRV AudioSetOutputMode(audio_channel+1, 0);
    	#endif
    }
//for L/R output when playing vcd, wangfeng2004-2-9 16:16   
//------------------------------
#if 0//def  CNTR_5SPK_VOLUME
    {
        if (action_click){
            if((audio_channel==2)){
                tVolumeL=volume_5SPK[1];
                volume_5SPK[2]=tVolumeR;
                volume_5SPK[1]=volume_5SPK[2];
            }
            else if((audio_channel==1)){
                tVolumeR=volume_5SPK[2];
                volume_5SPK[2]=volume_5SPK[1];
            }
            else if((audio_channel==3)){
                //tVolumeL=volume_5SPK[1];
                volume_5SPK[2]=tVolumeL;
                volume_5SPK[1]=tVolumeL;
            }
            else if((audio_channel==4)){
                tVolumeL=volume_5SPK[1];
                volume_5SPK[2]=tVolumeR;
                volume_5SPK[1]=tVolumeR;
            }
            else{
                
                volume_5SPK[1]=tVolumeL;
                volume_5SPK[2]=tVolumeR;
            }
        }
        
    }
#endif
//------------------------------    

    OSD1000ISP_STATUS(audio_channel, OSDIR_VOL_LR);

    PrintOsdMsg(STR_OS_CH|(id_ary[audio_channel]<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
#endif // SUPPORT_UART_COMMAND
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}


void    ircmd_channel_dn(void)
{
#if 0
    //when user set to SPDIF-BITSTREAM mode, all volume control commands are invalid
    if ( setup_IsSet2SPDIF_Bitstream() || setup_IsSet2SPDIF_PCM() ) {
        psprintf(RegionValStr[REGION1],"SPDIF %s\n", Ch_hand);
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        return;
    }

    if(action_click) {
        if(audio_channel==0) {
            if(!audio_only) {
                if ( setup_IsMICoff() ) {
                    audio_channel=2;
                } else
                    audio_channel =MAX_CH_NUM;
            } else {
                audio_channel=2;
            }
        }
        else
            audio_channel--;
    }

    AudioSetOutputMode(audio_channel+1, 0);
    PrintOsdMsg(STR_OS_CH|(id_ary[audio_channel]<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
#endif//#if 0
}

#ifdef ONE_KEY_PASS//zhaoyanhua add 03-10-18 16:56
extern UINT16 SearchMainTitle(void);//include in user_if.h

/*
 *Function name : irmcd_one_key_pass()
 *
 *Description: 
 *     when play DVD,search the title which has the 
 *     most charpter,then play from this title.
 * zhaoyanhua
 */
void ircmd_one_key_pass(void)
{
    int main_title = 0;
    
    printf("------irmcd _ ONE_KEY_PASS-titile --%d\n",get_tt_info(DISP_TT));
    if (cd_type_loaded == CDDVD)
    {
        main_title = SearchMainTitle();
        
        if(main_title == get_tt_info(DISP_TT))//current title has the most charpter.
        {
            invalid_key();          
                    
        }
        else
        {
            dvd_title = main_title;
            dvd_chapter = 1;
            printf("MainTitle = %d---\n",dvd_title);
            //memset(RegionValStr[REGION1],0,14);
            PrintOsdMsg(STR_OS_ONEKEY, REGION1, 1, 0);
            ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY);
#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-29 11:08
        //when ONE_KEY_PASS ,must show PARENTAL_GUI
        #ifdef TUNR_OFF_PARENTAL_LVL        
            bTurnOffParentalLVL = 0;//terry,2002/9/20 11:40PM
        #endif          
            one_key_pass_play = 1;
#endif
        }
    }
    #ifdef VCD_ONE_KEY_PASS     //2004-2-6 03:39张宇P add support vcd one_key_pass
    else  if(cd_type_loaded == CDVCD20 && (play_state==VCD_STATE_NORMAL)&& IsPBCOn())
              {
                 pbcoff_init(); 
                 PrintOsdMsg(STR_OS_ONEKEY, REGION1, 1, 0);
               }
        #endif   //end    VCD_ONE_KEY_PASS
    else
    {
        invalid_key();
    }

}
#endif//end ONE_KEY_PASS

#if defined(DYNAMIC_SPECTRUM)||defined(SUPPORT_RECEIVER_EQ)//chenzhao20051017//zhaoyanhua add 03-11-1 16:27
/*
 *Function Description:
 *
 * when Show Spectrum, after DSPReset(),
 * should set the EQ value  again. 
 *       
 * zhaoyanhua 03-11-1 16:46
 */
void SetEQ(void)
{
    
    SettingEQType(EQ_type-1);
    SettingEqLevel((BYTE *)&music_osd_set[EQ_type-1]);
                
}
#endif

#ifdef SPECTRUM_KEY
extern BYTE band_onoff;//zhaoyanhua add 2004-1-12 15:07
void ircmd_spectrum(void)
{        
    if(band_onoff)//zhaoyanhua add 2004-1-12 15:09
    //if (full_scrn&SOUND)
    {
       bEqDisplay=0;
       band_onoff= 0;//zhaoyanhua add 2004-1-12 15:03
       osd_init(); 
       //full_scrn=0;//zhaoyanhua mask 2004-1-12 15:09
    }
    else
    {
        bEqDisplay=1;
        band_onoff= 1;//zhaoyanhua add 2004-1-12 15:03
        Show3dspectrum();
        //full_scrn=SOUND;//zhaoyanhua mask 2004-1-12 15:09
        //osd_init();
    }
   
}
#endif

#if defined(ONLY_EQ_KEY)||defined(SUPPORT_RECEIVER_EQ)//chenzhao20051017//zhaoyanhua add 03-10-29 13:30
/*
 * Description:
 *     set EQ
 */
#ifdef AMP_SUPPORT_EQ
void ircmd_EQ(void)
{
    amp_toggle_EQ();
}
#else
void ircmd_EQ(void)
{
    //amp_toggle_EQ(); //chenzhao 2006-9-28 16:59 .Only valid when #define AMP_SUPPORT_EQ
    //if(setup_IsSpkDownmixOff())    // fengjl add to turn off prologicII when turn on EQ 3-12-15 18:49     
    if( ((cd_type_loaded == CDDVD)||(cd_subtype == CD_DTS) )&&(setup_IsSpkDownmixOff())  ) // fengjl add to to make eq invalid when 5.1CH  3-12-15 18:49     
    {
        invalid_key();
        return;
        //AudioSet2chOutput();  
        //EQ_type=1;    //standard
    }else    
    EQ_type++;

    //memset(RegionValStr[REGION1],0,sizeof(RegionValStr[REGION1]));
    PrintOsdMsg(sound_item[1][EQ_type+1], REGION1, 1, 0);
    
    SetEQ();
    
    #ifdef SUPPORT_RECEIVER_EQ
    //5 mode:
    //standard/classic/rock/jazz/pop
    if(EQ_type >= 5)
        EQ_type = 0;        
    #else
    //7 mode:
    //standard/classic/rock/jazz/pop
    if(EQ_type >= 7)
        EQ_type = 0;        
    #endif
}
#endif//#ifdef AMP_SUPPORT_EQ
#endif //ONLY_EQ_CONTROL

#ifdef ONLY_SOUND_FIELD_KEY
/*
 *Description:
 *   set sound field mode
 */
void ircmd_sound_field(void)
{
    if( ((cd_type_loaded == CDDVD)||(cd_subtype == CD_DTS) )&&(setup_IsSpkDownmixOff())  ) // fengjl add to make it sound_field invalid when 5.1CH   3-12-15 18:49     
    {
        invalid_key();
        return;
//        AudioSet2chOutput();  
//        surround_type=1;   //OFF
    }else    
    surround_type++;
    
    //memset(RegionValStr[REGION1],0,14);
    PrintOsdMsg(sound_item[0][surround_type+1], REGION1, 1, 0);
    AUDIF_Set_Surround(surround_type - 1);//2004AUDDRV AudioSetSurround(surround_type - 1);
    
    //Surround is open, so we should set EQ to standard mode
    if(surround_type > 1)
    {   
        AUDIF_Set_EQType(0);//2004AUDDRV AudioSetEQType(0);
        EQ_type = 1;//Standard mode
    }
    //6 mode :
    
    if(surround_type >= 6)
        surround_type = 0;  
    
#ifdef DYNAMIC_SPECTRUM 
    if(bEqDisplay)
    {       
        SetEQ();
        AUDIF_Set_Continue();//2004AUDDRV AudioSetContinue();
    }
#endif
}
#endif// ONLY_SOUND_FIELD_CONTROL

#ifdef AUDIO_2CH_5_1CH
#include "ircmd_2ch_5_1CH.c" //terry,2004/2/10 11:55AM
#endif//AUDIO_2CH_5_1CH
/*
 * Descirption:
 *   if enter this key, record the current disc playing point,
 *   when play the same disc next time,start from this 
 *   record point. 
 *
 * zhaoyanhua 03-10-19 11:45
 */
#ifdef  RECORD_KEY
void ircmd_record(void)
{
#ifdef SUPPORT_FILE_SYSTEM_MODE    
    if ( Is_OTHER_STATE() ) {
        invalid_key();
        return;
    }
#endif

#ifdef DVD_AUDIO
    #ifdef DVD_AUDIO_RECORD_INVALID //Maoyong 2004.0218, must define DVD_AUDIO
    if ( (cd_type_loaded==CDDVD) && (dAMG_LSN!=0) )    {        
          invalid_key();
          return;             
    }
    #endif
#endif
//Maoyong 2004.02.16 for CDG not record playing info
    if( is_cdg_disc(0)) {
        invalid_key();
        return;
    }   
    //when waiting for user operation,if enter the key,will resume.
    // else sequence play after 6s.
    //zhaoyanhua note 03-11-5 13:28
    if(same_disc_flag != 0)
    {
        same_disc_flag = 0;
    #ifdef TUNR_OFF_PARENTAL_LVL
        bTurnOffParentalLVL = 1;
    #endif
        return;
    }
    
    //Maoyong 2003.03.11 Move here for Change to Record Resume Play 
    #ifdef  MENU_RECORD_INVALID     
    if(is_menu())
    {       
        invalid_key();
        return;
    }
    #endif
/*
 RsmInfo2Flash" is for all resume, so move #ifdef SAME_DISC_RESUME Maoyong 2004.03.01
*/
#ifndef POLLING_10MS_SAVE_RESUME    //Maoyong,2004.03.01    
    RsmInfo2Flash(0);   
#else   //else ifndef POLLING_10MS_SAVE_RESUME
    if(cd_type_loaded  == CDDVD)    
    {   
        RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:37 .
        clr_rsm_info();     
        rsm_I2c_write_cnt = 0;
    }   
    else
    {
    RsmInfo2Flash(0);
    }   
#endif  //end ifndef POLLING_10MS_SAVE_RESUME

    memset(RegionValStr[REGION1],0,14);
    psprintf(RegionValStr[REGION1], "........");
    PrintOsdMsg(STR_OS_MARK, REGION1, 1, 1);

#if defined (IR_PLAY_RESUME)//zhaoyanhua 2003-12-8 18:15 
#ifdef POLLING_10MS_SAVE_RESUME //Maoyong 2004.03.01
    if(cd_type_loaded != CDDVD)
#endif
    resumeMSF = 0;
#endif
}
#endif


#ifdef DIV_GOTO_DISPLAY
extern void ClearRegion2(void);
void ircmd_search(void)
{

#ifdef SUPPORT_FILE_SYSTEM_MODE    //nono 3-6-24 16:41
    if ( Is_OTHER_STATE() ) {
        invalid_key();
        return;
    }
#endif


    if(full_scrn&GOTO)
    {
        //When WMA or MP3,not show disc time page(PAGE 1)
        //NOTE: WMA use the same button with MP3.
        //zhaoyanhua add 2003-11-17 13:35
        if(Is_MP3_STATE())
        {
#if defined(MP3_STOP_SEARCH_PAGE_ONLY_ONE)
            if(play_state==VCD_STATE_STOP)//NONO 2004-3-8 19:28
            {
                if(SearchPage==0)
                SearchPage = 3;
            }
            else 
#endif  //end #if defined(MP3_STOP_SEARCH_PAGE_ONLY_ONE)
            {
            switch(SearchPage)
            {
                case 0:
                    SearchPage = 2;
                    break;
                case 2:
                    SearchPage = 3;
                    break;
            }
            }
        }else if(Is_JPEG_STATE())//nono 20040226 for nintaus
        {
            if(SearchPage==0)
                SearchPage = 3;
                    
        
        }

#if defined(DVD_AUDIO)&&defined(DVDAUDIO_STOP_SEARCH_PAGE_ONLY_ONE)//2004-3-10 17:06
        else if( (dAMG_LSN!=0)&&(play_state==VCD_STATE_STOP) )
        {
            if(SearchPage==0)
                SearchPage = 3;
        }
#endif//#if defined(MP3_STOP_SEARCH_PAGE_ONLY_ONE)

        else
        SearchPage ++;
        
        if (SearchPage == 3)//the last SearchPage exit
        {
                       ExitGOTOPage();                        
            return;
        }
    }
    else
    {
        full_scrn=GOTO;
        //must clear to be 0.
        dvd_title = 0;
        dvd_chapter = 0;
    }
    
    ClearRegion2();
    switch(SearchPage)
    {
        case 0:
        #if defined( BBK_DVD)||defined(NINTAUS_DVD)//2004-2-24 09:00张宇M zhaoyanhua 2003-12-8 16:42
        if(cd_type_loaded == CDDVD)    
            index_x = 2;//first in chapter.
        else    
        #endif          
            index_x = 0;
            break;
            
        case 1:
            #if defined(BBK_DVD)||defined(NINTAUS_DVD)//zhaoyanhua add 2003-12-8 16:43
                index_x = 5;//first set in time
            #else
            if(cd_type_loaded == CDDVD)
                index_x = 0;
            else//VCD only has time goto
                index_x = 5;
            #endif
            break;
        case 2:
            #if defined( BBK_DVD)||defined(NINTAUS_DVD)//2004-2-24 09:00张宇M zhaoyanhua 2003-12-8 16:42
                index_x = 5;//first set in time
            #else
            if(cd_type_loaded == CDDVD)
                index_x = 2;
            else//VCD only has time goto
                index_x = 5;
            #endif//zhaoyanhua add 2003-12-8 16:44
            break;
    }
    
    goto_time = 0;
    goto_hour = 0;
    goto_sec = 0;
    goto_min = 0;
    printf("-----disp_trk_now = %d: %d\n",disp_trk_now,SearchPage);
    ShowSearchPage(SearchPage,1);

    if(rep_ab_mode != REPEAT_IDLE)/*kenny add it 0929*/ /*jhuang 2001/2/18 10:53PM*/
    {
        rep_ab_mode = REPEAT_AB_IDLE;
        show_repeatAB(1);
    }


}

/*
 *Function Description:
 *   to exit GOTO mode
 *
 *zhaoyanhua add 2003-12-17 15:45
 */
void ExitGOTOPage(void)
{
    full_scrn=0; //t_disp=disp_mode;
    index_x =0;
    osd_tog_region(2,OSD_OFF);
    SearchPage = 0;
}


#endif//End DIR_GOTO_DISPLAY

#ifdef DISC_INFO_KEY
void ircmd_disc_info(void)
{
#ifdef NEWSTYLE_WINDOW
//xyy 2003-9-15 21:10
    if(cd_type_loaded >= CDDA && cd_type_loaded<=CDDVD) {
        if(full_scrn&MESSAGE) {
            // reset display outlook
            exit_browse_func();
        }else
        {
        
/////////////////////////////////////////////////////
//not into NEW-goto when TitleMenu or PBC-menu is shown.  hq,3-11-22 20:56  
            if(is_menu()||(HL_exist))   // fengjl add 3-12-19 22:06 to not show disk_info in dvd sub_menu 
            {
                invalid_key();
                return;
            }
            
            if(play_state==VCD_STATE_STOP) 
            {
                invalid_key();
                return;
            }       
//////////////////////////////////////////////////////

            full_scrn=MESSAGE;

            // setup display outlook
        #ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW //zhaoyanhua add 2003-11-30 15:32
            DrawNewWindow();
        #else
            osd_init_newstyle_window();
        
        {
            arc_region_loc.region  = 2;

                osd_draw_rect(0,0,38*16,374,4);

                arc_region_loc.xStart  = 2*16-15;
                arc_region_loc.yStart  = 6;
                arc_region_loc.xLen    = 21*16+32;
                arc_region_loc.yLen    = 24*10-20;
                arc_region_loc.bkColor = 9;
                arc_region_loc.radius  = 10;
                osd_draw_region_arc(&arc_region_loc,2);


                arc_region_loc.xStart  = 2*16-15+10;
                arc_region_loc.yStart  = 16;
                arc_region_loc.xLen    = 21*16+32-20;
                arc_region_loc.yLen    = 24*10-40;
                arc_region_loc.bkColor = 0;
                osd_draw_region_arc(&arc_region_loc,2);
            }
            exe_browse_func();
            exe_show_time();
            
        #endif
        }
    }
#endif//end NEWSTYLE_WINDOW

}
#endif//DISC_INFO_KEY

/*
**
*/
void    ircmd_mute(void)
{
#ifdef DISP_TIME_AFTER_STATE
	vfd_disp_mute_flag = 1;
#endif

#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).

#ifdef DBG_DIVX_DRM_I2C_ADDR//nono test 5-5-23 23:58 for DEBUG DRM.

 char buf[48];
    int j;

    if(ReadFromI2c(0xa0, 208, buf, 48) >= 0)
    {
        printf("ircmd: read DRM para from EEPROM data.\n");
        
        for (j=0;j<48;j++)
        printf("%08x    ", buf[j]);
    }
    printf("\n");
    return;
#endif


#ifdef IRCMD_DBG
    printf("==================mute===================\n");
#endif

#ifdef SPG_ICE //axel 2005/5/11 
    extern void FS_ICEMainLoop();
    FS_ICEMainLoop();
#endif    

#ifdef SUPPORT_TVG
    if( TVGControlMute() )
        return;
#endif

#if defined(FAT_FILE_MODE) && defined(SPHE8202_FAT_WRITE_API)//liweihua mod 2005-3-15 16:16
    if((fat_play_mode == 1)&&(media_type == MEDIA_CARD))
    {
        ircmd_card_copy();
        return;        
    }
    else if((fat_play_mode != 1)&&(play_state == VCD_STATE_CLOSE))
    {
        invalid_key();
        return;        
    }
#endif
  #ifdef MENU_PLUS_TEST //Jack added for argus portable test
   ircmd_setup_plus();
   return;
   #endif

#ifdef IRCMD_DBG
    printf("audio_volume:%d\n",audio_volume);
#endif

    #ifdef USE_AMP_MUTE //chenzhao20060114
    if (user_amp_mute)
    #else
    if (user_mute)
    #endif//#ifdef USE_AMP_MUTE
    {
        #ifdef USE_AMP_MUTE //chenzhao20060114
        user_amp_mute=0;
        sub_masterMute(AMP_DEMUTE);
        #else
        user_mute=0;
        //Jeff 20020521
        //AudioDemute();
        #endif//#ifdef USE_AMP_MUTE
#ifdef MP3_CD_FF1_BF1_MUTE//YX822BC//nono 2-8-23 15:41
        if(!adv_search_time)
            AUDIF_Demute();//2004AUDDRV AudioDemute();
#else
        if (adv_search_time>0) {
            if (adv_search_time<=2)
            {
               AUDIF_Demute();//2004AUDDRV  AudioDemute();
            }
        } else {
            if (adv_search_time>=(-2))
            {
                AUDIF_Demute();//2004AUDDRV AudioDemute();
            }
        }
#endif
#ifdef SUPPORT_UART_COMMAND // robert 020726
        // send mute-on command to 8051
        UART_PUTC_EXACT(COMMAND_START);
        UART_PUTC_EXACT(MUTE_AMP);
        UART_PUTC_EXACT(MUTE_OFF);
        UART_PUTC_EXACT(COMMAND_END);

        psprintf(RegionValStr[REGION3], "SEND 8051 MUTE ON");
        PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif

#if defined(DESAY_DVD)||defined(SETUP_DONGLI459)   //kubby 2003-8-9 10:43 added to show "MUTE CANCEL"
        PrintOsdMsg(STR_OS_DEMUTE,REGION1,1,0); 
#elif defined(HANYANG_MUTEOFF)   //caohui 2004-5-13 16:05
        PrintOsdMsg(STR_OS_MUTEOFF,REGION1,1,0); 
        #else
        OSD1000ISP_STATUS(OSDISP_DEMUTE, OSDIR_MUTE);
        OSD_OnOffRegion(OSD_OFF,1);
#endif  

//QiaoHuilin:2005-10-24:Show demute icon when av in mode
#ifdef MUSTEK_LCD_DRIVE_BITEK
	if(source_play_mode == AV_IN_MODE)
		LCD_ShowDemuteIcon();
#endif
////////////////////////////////////////////////////

    }
    else
    {
        #ifdef USE_AMP_MUTE //chenzhao20060114
        user_amp_mute=1;
        sub_masterMute(AMP_MUTE);
        #else//#ifdef USE_AMP_MUTE
        user_mute=1;
        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
        #endif//#ifdef USE_AMP_MUTE

#ifdef MUTE_EXECUTE_MIC //NONO 4-1-5 12:09
       
        AUDIF_Set_MICVol(0);//2004AUDDRV AudioSetMICVol(0);
#ifdef  MIC_2CHANNEL
        AUDIF_Set_MICVol2(0);//2004AUDDRV AudioSetMICVol_2(0);
#endif//#ifdef  MIC_2CHANNEL
#endif//#ifdef MUTE_EXECUTE_MIC

        //terry,2001/1/10 09:32PM,avoid stop->play ,show mute's postion error
        PrintOsdMsg(STR_OS_MUTE,REGION1,0,0);

#ifdef SUPPORT_UART_COMMAND // robert 020726
        // send mute-off command to 8051
        UART_PUTC_EXACT(COMMAND_START);
        UART_PUTC_EXACT(MUTE_AMP);
        UART_PUTC_EXACT(MUTE_ON);
        UART_PUTC_EXACT(COMMAND_END);

        psprintf(RegionValStr[REGION3], "SEND 8051 MUTE OFF");
        PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
#endif

        OSD1000ISP_STATUS(OSDISP_MUTE, OSDIR_MUTE);

//QiaoHuilin:2005-10-24:Show mute icon when av in mode
#ifdef MUSTEK_LCD_DRIVE_BITEK
	if(source_play_mode == AV_IN_MODE)
		LCD_ShowMuteIcon();
#endif
////////////////////////////////////////////////////


    }
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

#ifdef GBM_MIC_FUNCTION
void    ircmd_key_up(void)
{      if(Is_JPEG_STATE() || WillKeyShiftNotDo())//nono 2-5-12 20:55
    {
        invalid_key();
        bFuncStep = 0;
        return;
    }
    bFuncStep = 3;
    show_level(AudKey_Font_ID,audio_key, 13);
}

#else//#ifdef GBM_MIC_FUNCTION

void    ircmd_key_up(void)
{
    if(Is_JPEG_STATE()||WillKeyShiftNotDo())//nono 2-5-12 20:55
    {
        invalid_key();
        return;
    }

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if(action_click|| (PatternMode==AudKey_Font_ID) )
#endif

        audio_key++;
    if (audio_key>KEY_UP_MAX) 
        audio_key=KEY_UP_MAX;
/*
#ifdef MIC_FUNCTION_KEY 
#ifdef BBK_DVD
    //if playing DTS or PROLOGIC II ,then turn off PL2, set the audio default value
    //zhaoyanhua 2003-12-1 16:39    
    if(((cd_type_loaded == CDDA) && (cd_subtype == CD_DTS)) //CD_DTS
      ||((cd_type_loaded == CDDVD) && (coding_mode_now == AUDIF_CODING_MODE_DTS))//DVD_DTS
      || (setup_GetPrologicII() < 4 )//PROGIC II not off
      )
    {
        
        audio_key = 0;      
      
    }
   
#endif    
#endif
*/  
    {
        show_level(AudKey_Font_ID,audio_key,13);
        setup_SetKey();
    }
    return;
}
#endif//#ifdef GBM_MIC_FUNCTION

void    ircmd_key_down(void)
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
    if(Is_JPEG_STATE()||WillKeyShiftNotDo())//(SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) )//nono 2-5-12 20:56
    {
        invalid_key();
        return;
    }

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if(action_click|| (PatternMode==AudKey_Font_ID) )
#endif

        audio_key--;
    if (audio_key<KEY_DN_MAX) audio_key=KEY_DN_MAX;
    {
        show_level(AudKey_Font_ID,audio_key,13);
        setup_SetKey();
    }
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}


void    ircmd_key_reset(void)
{
    audio_key = 0;
    show_level(AudKey_Font_ID,audio_key,13);
    setup_SetKey();
}

#ifdef CNTR_5SPK_VOLUME
void ircmd_volume_switch(void)
{
    BYTE    iVolume;
    BYTE    idVolumeFont;

if(Is_JPEG_STATE())
    {
        
        return;
    }

    if (action_click) {
        //if(volume_5SPK[0]==0)
            //return;
        //volume_5SPK[volume_Switch]=audio_volume;
    //idVolume_5SPK[volume_Switch]=idVolumeFont;
        if(setup_IsSpkDownmixOff()&&((cd_type_loaded == CDDVD)||( (cd_type_loaded==CDDA) && 
                (cd_subtype==CD_DTS)) ))//wangfeng 2003-10-31 19:37
        {
            if(setup_IsSet2SPDIF_Bitstream()&&( (cd_type_loaded==CDDA) && 
                (cd_subtype==CD_DTS)) )
                {   
                if (++volume_Switch > 2)    volume_Switch = 0; //Jeff 20031028
                }
            else{   
        if (++volume_Switch > 6)    volume_Switch = 0; //Jeff 20031028
    }
        }
        else
  {
#ifdef CNTR_5SPK_WHEN_CD    //wangfeng 2004-2-2 11:23   
            if(setup_IsPrologicOn()){       
                if (++volume_Switch > 5)    volume_Switch = 0;
            }   
            else{
                if (++volume_Switch > 2)    volume_Switch = 0;
        }
                
#else               
                if (++volume_Switch > 2)    volume_Switch = 0;
#endif
        }
    }
    #ifdef CNTR_5SPK_TYPE_2  //linrc add 2004-10-12 9:28 -->ESS is like this type
    if(IS_AUDIF_CODING_MODE_LPCM || IS_AUDIF_CODING_MODE_DTS 
       || IS_AUDIF_CODING_MODE_PCM || IS_AUDIF_CODING_MODE_WMA
       || IS_AUDIF_CODING_MODE_DTSCD)
    {
        volume_Switch = 0;        
    } 
    #endif

    //printf("<>:volume_Switch2=%d\n",volume_Switch);
    if (volume_Switch>=0) {
        //current is under 5_speakers setting
        iVolume         = volume_5SPK[volume_Switch];
        idVolumeFont    = idVolume_5SPK[volume_Switch];
    } else {
        //under main volume setting
        iVolume         = audio_volume;
        idVolumeFont    = Volume_Font_ID;
    }


//wangfeng 2003-09-29 13:37
#ifdef  VOL_80
    #ifdef CNTR_5SPK_VOLUME//HUAJIA_DVD
    #ifdef MAIN_VOL_20
    if(volume_Switch==0)
    show_level(idVolumeFont, iVolume/4, 81);
    else
    #endif
    show_level(idVolumeFont, iVolume, 81);
#else
    show_level(idVolumeFont, iVolume, 81);
    #endif
#elif defined(VOL_20)   //fengjl add 2004-03-08 21:38
    show_level(idVolumeFont, iVolume, 21);
#elif defined(OSD_BMP_REGION1)   
    show_level(idVolumeFont, iVolume, 13);
#else
    show_level(idVolumeFont, iVolume, 16);
#endif
#ifdef VFD_VOLUME_DISPLAY
    //audio_volume = iVolume;   //wangfeng 2003-09-29 16:16
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_volume(0);
#endif
    
}

#endif


void VolumeCHKnSet(BYTE iVolume)
{
    BYTE    iSet=0;
    #ifdef CNTR_5SPK_TYPE_2  //linrc 2004-10-12 9:42
    int j = 0;
    #endif
    
    if (adv_search_time>0) 
    {
        if (adv_search_time<=2) 
        {
            iSet = 1;
        }
    } else 
    {
        if (adv_search_time>=(-2)) 
        {
            iSet = 1;
        }
    }

    if (iSet) 
    {
        #ifdef CNTR_5SPK_VOLUME
            if (volume_Switch>0) {
                AUDIF_Set_5SPKGain((FLSPKGAIN+volume_Switch-1), iVolume);//2004AUDDRV AudioSet5SPKGain((FLSPKGAIN+volume_Switch-1), iVolume);
            } else {
                #ifdef CNTR_5SPK_TYPE_2  //linrc add 2004-10-12 9:40-->ESS is like this type
                if(IS_AUDIF_CODING_MODE_LPCM || IS_AUDIF_CODING_MODE_DTS 
                 || IS_AUDIF_CODING_MODE_PCM || IS_AUDIF_CODING_MODE_WMA
                 || IS_AUDIF_CODING_MODE_DTSCD)
                {
            AUDIF_Set_Volume(iVolume);//2004AUDDRV AudioSetVolume(iVolume);
                }   
                else   AUDIF_Set_Volume(15);//2004AUDDRV AudioSetVolume(15);              
                for(j=1;j<7;j++)
                {
                    DSP_AudioIOControl(FLSPKGAIN+j-1,volume_5SPK[j],0);;//2004AUDDRV AudioIOControl(FLSPKGAIN+j-1,volume_5SPK[j],0); 
                } 
                #else
                AUDIF_Set_Volume(iVolume);//2004AUDDRV AudioSetVolume(iVolume);
                #endif
            }
        #else
            AUDIF_Set_Volume(iVolume);//2004AUDDRV AudioSetVolume(iVolume);
        #endif
    }
}

extern void disfreq(void);//xyy 2003-10-13 20:48
#ifndef NO_INTERNAL_VOLUME_CTRL
void    ircmd_volume_up(void)
{
#ifdef SUPPORT_TVG
    if( TVGControlMute() )
        return;
#endif
    
    #ifdef VOL_INVALID_WHEN_OPEN //2004-6-24 05:51?宇P
    if (system_state==SYSTEM_OPEN)
       return;
    #endif
    BYTE    iVolume;
    BYTE    idVolumeFont;

    #ifdef TEST_VFD
    update_vfd_inc();           //shawn add at 910131
    return ;
    #endif


    if(Is_JPEG_STATE())//nono 2-4-25 21:58
    {
        #ifdef ALCO_DVD_UI
        invalid_key();
        #endif
        return;
    }

    #ifdef CNTR_5SPK_VOLUME
    //if(setup_IsSpkDownmixOff())
    //{  
        if (volume_Switch>=0) {//add "=" by wangfeng 2003-11-03 15:09
            //current is under 5_speakers setting
            iVolume         = volume_5SPK[volume_Switch];
            idVolumeFont    = idVolume_5SPK[volume_Switch];
        } else {
            //under main volume setting
            iVolume         = audio_volume;
            idVolumeFont    = Volume_Font_ID;
        }

    #else
        iVolume         = audio_volume;
        idVolumeFont    = Volume_Font_ID;
    #endif


    #ifdef MIC_FUNCTION_KEY
    #ifndef BBK_DVD
#ifdef GBM_MIC_FUNCTION
    switch (bFuncStep)
    {
    case 1: 
#ifdef MIC_2CHANNEL
    case 5:
#endif//MIC_2CHANNEL

    //mic_volume(0 ~ 8)
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if (action_click || (PatternMode==Mic_Font_ID) )
#endif

#ifdef MIC_2CHANNEL
    if(bFuncStep == 1)
    {
        mic_volume=setup_GetMICVol()-2;
    }
    else if(bFuncStep == 5)
    {
        mic_volume=setup_GetMICVol2()-2;
    }
#endif//MIC_2CHANNEL

        if (mic_volume < 8)
            mic_volume++;

        setup_SetMic();
        show_level(Mic_Font_ID, mic_volume, 9);

        //ircmd_mic_up();
        return;
    
    case 2:
         //echo_level : 0 ~ 8
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if (action_click || (PatternMode==Echo_Font_ID) )
#endif
        if (echo_level < 8)
            echo_level++;

        show_level(Echo_Font_ID, echo_level, 9);
        setup_SetEcho();
        //ircmd_echo_up();
        return;

    case 3:
        
    if(Is_JPEG_STATE()||WillKeyShiftNotDo())//nono 2-5-12 20:55
    {
        invalid_key();
        return;
    }

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if(action_click|| (PatternMode==AudKey_Font_ID) )
#endif

        audio_key++;
    if (audio_key>KEY_UP_MAX) audio_key=KEY_UP_MAX;
    {
        show_level(AudKey_Font_ID,audio_key,13);
        setup_SetKey();
    }
    return;
        //ircmd_key_up();
        
    }

#else//GBM_MIC_FUNCTION

    
    switch (bFuncStep)
    {
    case 1:
        ircmd_mic_up();
        return;
    
    case 2:
        ircmd_echo_up();
        return;

    case 3:
        ircmd_key_up();
        return;
    }
#endif//GBM_MIC_FUNCTION
    
    #endif //end ifndef BBK_DVD
    #endif //#ifdef MIC_FUNCTION_KEY


    //when user set to SPDIF-BITSTREAM mode, all volume control commands are invalid
    if ( setup_IsSet2SPDIF_Bitstream() )
        if( (coding_mode_now&(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS))||(cd_subtype==CD_DTS) ){//nono 2-7-25 16:08
            //psprintf(RegionValStr[REGION1]," %s\n", Ch_hand);
            //PrintOsdMsg(STR_OS_BITSTREAM, REGION1, 1, 1);
            //wangfeng 2003/08/19
            //invalid_key();
            //return;
        }

        if (user_mute)
        {
        #ifdef SUPPORT_UART_COMMAND // robert 020726
            // send mute-on command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(MUTE_AMP);
            UART_PUTC_EXACT(MUTE_OFF);
            UART_PUTC_EXACT(COMMAND_END);
        #endif

            AUDIF_Demute();//2004AUDDRV AudioDemute();

            OSD_OnOffRegion(OSD_OFF, 1);
            user_mute=0;
        }

        #ifdef NEW_UART_COMMAND       //lijinhai 2-10-22 19:46 for fuss new request
        if(nCurrentVolMode==VOL_MODE_QS_EFFECT)
            return ;
        else
            IRAdjustVol(1);
        return ;
        #endif


#ifndef NEW_UART_COMMAND
     //wangfeng 2003-09-29 13:46    
     #ifdef VOL_80   
        else if (iVolume<80)
     #elif defined(VOL_20)   //fengjl add 2004-03-08 21:38
        else if (iVolume<20)
     #elif defined(OSD_BMP_REGION1)
        else if (iVolume<12)
     #elif defined(VOLUME_SHOW_16)
        else if (iVolume<16)
     #else
        else if (iVolume<15)
     #endif
#endif
        {

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
            if(action_click|| (PatternMode==idVolumeFont) )
#endif
                #ifdef CNTR_5SPK_VOLUME// defined(HIMAGE1251) || defined(HIMAGE1250_03_185W)//wangfeng 2003-10-31 21:44
                #ifdef MAIN_VOL_20
                if(volume_Switch==0)
                {
                    if(iVolume<=76)
                    iVolume+=4;
                    else
                    iVolume=80;
                
                }
                else
                #endif
                iVolume++;
                #else
                iVolume++;
                #endif


    #ifdef CNTR_5SPK_VOLUME
        if (volume_Switch>=0) {//add "=" by wangfeng 2003-11-03 15:08
            //current is under 5_speakers setting
            #ifdef CNTR_5SPK_TYPE_2  //linrc add 2004-10-12 9:40 -->ESS is like this type
            int j = 0;
            if(volume_Switch == 0) //This type is allow the volume is 15 step 
            {
                for(j=1;j<7;j++)
                {
                    if(volume_5SPK[j]<=14)
                    {
                        volume_5SPK[j] += 1;
                    }
                    else 
                    {
                        volume_5SPK[j] = 15;
                    }
                }
            }
            #endif
            volume_5SPK[volume_Switch] = iVolume;
        } else {
            //under main volume setting
            audio_volume = iVolume;
        }
    #else
        audio_volume = iVolume;
    #endif
	//by zongrifei  2005/10/28  save volume
#if defined(MUSTEK_K100D_MODEL)&&defined(VOLUME_RECODE_NEW)
	    WriteToI2c(0xa0, ADDR_I2C_VOLUME ,(BYTE *)(&audio_volume),sizeof(audio_volume));
#endif
            //Jeff 20030829
            VolumeCHKnSet(iVolume);
        }
        //wangfeng  2003-09-29 13:37
        #ifdef  VOL_80
            //#ifdef CNTR_5SPK_VOLUME//wangfeng 2003-10-31 21:44
            #ifdef MAIN_VOL_20
            if(volume_Switch==0)
            show_level(idVolumeFont, (iVolume/4), 81);
            else
            #endif
        show_level(idVolumeFont, iVolume, 81);
            //#endif
        #elif defined(VOL_20)   //fengjl add 2004-03-08 21:38
        show_level(idVolumeFont,iVolume,21);
        #elif defined(OSD_BMP_REGION1)
        show_level(idVolumeFont,iVolume,13);
		#elif defined(VOLUME_SHOW_16)
        show_level(idVolumeFont,iVolume,17);
        #else
        show_level(idVolumeFont,iVolume,16);
#endif
        
/*//linrc del 20041016 ??
    #ifdef CNTR_5SPK_VOLUME
        if (volume_Switch>=0) {//add "=" by wangfeng 2003-11-03 15:08
            //current is under 5_speakers setting
            volume_5SPK[volume_Switch] = iVolume;
        } else {
            //under main volume setting
            audio_volume = iVolume;
        }
    #else
        audio_volume = iVolume;
    #endif
*/    
    #ifdef VFD_VOLUME_DISPLAY
        //audio_volume = iVolume;   //wangfeng 2003-09-29 16:16
        timeout_vfd = 2*VFD_TIMEOUT;
        vfd_set_volume(0);
    #endif
  #ifdef VOL_LED    //test by wangfeng,2003-10-30 22:14
  #ifndef ROTARY_SWITCH_1251
  if ((iVolume<=80)&&(iVolume>=0))
        {
            if(nLed_index == 0)
                nLed_index=0x01;
            else if(nLed_index == 0x04)
                nLed_index=0x01;
            else
                nLed_index<<=1;
        }
    #else
    if((iVolume<=80)&&(iVolume>=0))
        {
            if(nLed_index==1||nLed_index==0)
                {
                    nLed_index=0x04;
                }
            else
                {
                    nLed_index>>=1;
                }
        }
    //do_updata_vfd_vol();
    #endif
    write_vfd_led((BYTE)nLed_index);
    //PrintOsdMsg(STR_OS_SPACE, REGION1, 4, 1);
    //timeout_vfd=4*VFD_TIMEOUT;
#endif

    OSD1000ISP_STATUS(iVolume, OSDIR_VOL_ADD);
    
    #ifdef MP3_CD_FF1_BF1_MUTE//dingzhy modify 05-1-11 17:06
    if(adv_search_time!=0) 
    AUDIF_Set_Volume(0);
    #endif

    //QiaoHuilin:2005-10-24:Show volume  at lcd when av in mode
#ifdef MUSTEK_LCD_DRIVE_BITEK
	if(source_play_mode == AV_IN_MODE)
		LCD_Show_Volume(audio_volume);
#endif
#ifdef RECODE_VOL_INFO
    WriteToI2c(0xa0, I2C_ADDR_VOL_INFO, (BYTE *)(&audio_volume), 1); 
#endif 
////////////////////////////////////////////////////

}


void    ircmd_volume_down(void)
{
#ifdef SUPPORT_TVG
    if( TVGControlMute() )
        return;
#endif

    #ifdef VOL_INVALID_WHEN_OPEN //2004-6-24 05:51?宇P
    if (system_state==SYSTEM_OPEN)
       return;
    #endif
    BYTE    iVolume;
    BYTE    idVolumeFont;

#ifdef TEST_VFD
    update_vfd_dec();           //shawn add at 910131
    return ;
#endif

    if(Is_JPEG_STATE())//nono 2-4-25 21:58
    {
        #ifdef ALCO_DVD_UI
        invalid_key();
        #endif
        return;
    }


    #ifdef CNTR_5SPK_VOLUME
        //printf("$$$$$$$$----- audio_volume before =%d\n",audio_volume);
        //printf("================ volume_Switch =%d\n",volume_Switch);
        if (volume_Switch>=0) {//add "=" by wangfeng 2003-11-03 15:05
            //current is under 5_speakers setting
            iVolume         = volume_5SPK[volume_Switch];
            idVolumeFont    = idVolume_5SPK[volume_Switch];
        } else {
            //under main volume setting
            iVolume         = audio_volume;
            idVolumeFont    = Volume_Font_ID;
        }
    #else//#ifdef CNTR_5SPK_VOLUME
        iVolume         = audio_volume;
        idVolumeFont    = Volume_Font_ID;
        //printf("$$$$$$$$----- audio_volume after =%d\n",audio_volume);
    #endif//#ifdef CNTR_5SPK_VOLUME

#ifdef MIC_FUNCTION_KEY
    #ifndef BBK_DVD//zhaoyanhua add 03-10-19 14:02
    switch (bFuncStep)
    {
    case 1:
#ifdef MIC_2CHANNEL
    case 5:
#endif//#ifdef MIC_2CHANNEL
    //mic_volume(0 ~ 8)
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if (action_click || (PatternMode==Mic_Font_ID) )
#endif//#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW

#ifdef MIC_2CHANNEL
    if(bFuncStep == 1)
    {
        mic_volume=setup_GetMICVol()-2;
    }
    else if(bFuncStep == 5)
    {
        mic_volume=setup_GetMICVol2()-2;
    }
#endif  //MIC_2CHANNEL

        if (mic_volume >0)
            mic_volume--;

        show_level(Mic_Font_ID, mic_volume, 9);
        setup_SetMic();

        //ircmd_mic_down();
        return;
    
    case 2:
         //echo_level : 0 ~ 8
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if (action_click || (PatternMode==Echo_Font_ID) )
#endif
        if (echo_level > 0)
            echo_level--;

        show_level(Echo_Font_ID, echo_level, 9);
        setup_SetEcho();
        //ircmd_echo_down();
        return;

    case 3:
        
    if(Is_JPEG_STATE()||WillKeyShiftNotDo())//(SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) )//nono 2-5-12 20:56
    {
        invalid_key();
        return;
    }

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if(action_click|| (PatternMode==AudKey_Font_ID) )
#endif

        audio_key--;
    if (audio_key<KEY_DN_MAX) audio_key=KEY_DN_MAX;
    {
        show_level(AudKey_Font_ID,audio_key,13);
        setup_SetKey();
    }return;
        //ircmd_key_down();
        
    }
    
#else//GBM_MIC_FUNCTION

    switch (bFuncStep)
    {
    case 1:
        ircmd_mic_down();
        return;
    
    case 2:
        ircmd_echo_down();
        return;

    case 3:
        ircmd_key_down();
        return;
    }
#endif//GBM_MIC_FUNCTION    

#endif//end ifndef BBK_DVD

    //when user set to SPDIF-BITSTREAM mode, all volume control commands are invalid
    if ( setup_IsSet2SPDIF_Bitstream() )
        if( (coding_mode_now&(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS))||(cd_subtype==CD_DTS) ){//nono 2-7-25 16:08
            //psprintf(RegionValStr[REGION1]," %s\n", Ch_hand);
            //PrintOsdMsg(STR_OS_BITSTREAM, REGION1, 1, 1);
            //wangfeng 2003/08/19
            //invalid_key();
            //return;
        }

        if (user_mute)
        {
#ifdef SUPPORT_UART_COMMAND // robert 020726
            // send mute-on command to 8051
            UART_PUTC_EXACT(COMMAND_START);
            UART_PUTC_EXACT(MUTE_AMP);
            UART_PUTC_EXACT(MUTE_OFF);
            UART_PUTC_EXACT(COMMAND_END);
#endif
            AUDIF_Demute();//2004AUDDRV AudioDemute();

            OSD_OnOffRegion(OSD_OFF, 1);
            user_mute=0;
        }

#ifdef NEW_UART_COMMAND       //lijinhai 2-10-22 19:46 for fuss new request
        if(nCurrentVolMode==VOL_MODE_QS_EFFECT)
            return ;
        else     IRAdjustVol(0);
        return ;
#endif
        
#if  0 // defined(TAS3001_AMP)  // jason 2-8-22 13:44 kenny mark it 2002/8/29
        else if (iVolume>  9)
#else

    #ifndef NEW_UART_COMMAND
        else if (iVolume>  0)
    #endif

#endif//#if defined(TAS3001_AMP)  // jason 2-8-22 13:44
        {

        #ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
            if(action_click|| (PatternMode==idVolumeFont) )
        #endif
            #ifdef CNTR_5SPK_VOLUME//wangfeng 2003-10-31 21:44
                #ifdef MAIN_VOL_20
                if(volume_Switch==0)
                {
                    if(iVolume>=4)
                    iVolume-=4;
                    else
                    iVolume=0;
                
                }
                else
                #endif
                {
                if((iVolume<=80)&&(iVolume>0))
                iVolume--;
                else
                iVolume=0;
                }
            #else
                iVolume--;
            #endif
                
    #ifdef CNTR_5SPK_VOLUME
        if (volume_Switch>=0) {//add "=" by wangfeng 2003-11-03 15:07
            //current is under 5_speakers setting
            #ifdef CNTR_5SPK_TYPE_2  //linrc add 2004-10-12 10:09-->ESS is like this type
            int j = 0;              //This type is allow the volume is 15 step
            if(volume_Switch == 0)
            {
                for(j=1;j<7;j++)
                {
                    if(volume_5SPK[j]>=1)
                    { 
                        volume_5SPK[j] -= 1;
                    }
                    else
                    {
                        volume_5SPK[j] = 0;
                    }
                    
                }
            }
            #endif
            volume_5SPK[volume_Switch] = iVolume;
        } else {
            //under main volume setting
            audio_volume = iVolume;
        }
    #else
        audio_volume = iVolume;
    #endif      
//by zongrifei  2005/10/28  save volume
#if defined(MUSTEK_K100D_MODEL)&&defined(VOLUME_RECODE_NEW)
            WriteToI2c(0xa0, ADDR_I2C_VOLUME ,(BYTE *)(&audio_volume),sizeof(audio_volume));
#endif
            

            //Jeff 20030829
            VolumeCHKnSet(iVolume);
            
        }
        
#if  0 //defined(TAS3001_AMP)  // jason 2-8-22 13:44
        //show_level(Volume_Font_ID,(audio_volume-40)/2,20);
        if(iVolume>9)
            psprintf(RegionValStr[REGION1]," %02d DB",iVolume-80);
        else
            psprintf(RegionValStr[REGION1]," OFF");

        PrintOsdMsg(STR_OS_VOL, REGION1, 1, 1);
#else
        //wangfeng 2003-09-29 13:37
        #ifdef  VOL_80
            //#ifdef CNTR_5SPK_VOLUME//wangfeng 2003-10-31 21:44
            #ifdef MAIN_VOL_20
            if(volume_Switch==0)
            show_level(idVolumeFont, (iVolume/4), 81);
            else
            #endif
        show_level(idVolumeFont, iVolume, 81);
            //#endif
        #elif defined(VOL_20)  //fengjl add 2004-03-08 21:38
        show_level(idVolumeFont,iVolume,21);
        #elif defined(OSD_BMP_REGION1)
        show_level(idVolumeFont,iVolume,13);
		#elif defined(VOLUME_SHOW_16)
        show_level(idVolumeFont,iVolume,17);
        #else
        show_level(idVolumeFont,iVolume,16);
        #endif
        
#endif// #if defined(TAS3001_AMP)  // jason 2-8-22 13:44;

    #ifdef VFD_VOLUME_DISPLAY
        //audio_volume = iVolume;   //wangfeng 2003-09-29 16:16
        timeout_vfd = 2*VFD_TIMEOUT;
        vfd_set_volume(0);
    #endif
    #ifdef VOL_LED//test by wangfeng,2003-10-30 22:13
    #ifndef ROTARY_SWITCH_1251
        if((iVolume<=80)&&(iVolume>=0))
        {
            if(nLed_index==1||nLed_index==0)
                {
                    nLed_index=0x04;
                }
            else
                {
                    nLed_index>>=1;
                }
        }
    #else
        if ((iVolume>=0)&&(iVolume<=80))
        {
            if(nLed_index == 0)
                nLed_index=0x01;
            else if(nLed_index == 0x04)
                nLed_index=0x01;
            else
                nLed_index<<=1;
        }
    #endif
    
    write_vfd_led((BYTE)nLed_index);
    //PrintOsdMsg(STR_OS_SPACE, REGION1, 4, 1);
    //timeout_vfd=4*VFD_TIMEOUT;
#endif

    OSD1000ISP_STATUS(iVolume, OSDIR_VOL_SUB);
    
    #ifdef MP3_CD_FF1_BF1_MUTE//dingzhy modify 05-1-11 17:06
    if(adv_search_time!=0) 
    AUDIF_Set_Volume(0);
    #endif

        //QiaoHuilin:2005-10-24:Show volume  at lcd when av in mode
#ifdef MUSTEK_LCD_DRIVE_BITEK
	if(source_play_mode == AV_IN_MODE)
		LCD_Show_Volume(audio_volume);
#endif
////////////////////////////////////////////////////
#ifdef RECODE_VOL_INFO
    WriteToI2c(0xa0, I2C_ADDR_VOL_INFO, (BYTE *)(&audio_volume), 1); 
#endif 
}
#endif  //NO_INTERNAL_VOLUME_CTRL the upper code is clip

#ifdef SETUP_PROGRAM_IN_PLACE_UNDER_16M

#ifdef NEW_STYLE_SETUP
static inline UINT32 ProgSettingForNewStyleSetup()
{   // 2004/11/26 yltseng
    #ifdef SDRAM_16Mb_Mode
    //zhaoyanhua modify  2003-8-7 18:47
    if (play_state != VCD_STATE_STOP)
    {
        if (prog_state == 0)
        {
            prog_state = 1;
            ircmd_stop();
            return FALSE;
        }
    }
    else
    {
        if (prog_state == 0)
        {
            prog_state = 2;//has in STOP state.
            ShowTitle();
        }
      
        old_t_disp = t_disp;
    }

    t_disp=0;
    DispFadeOut();            
    regs0->osd_base_addr = OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
    osd_init_prog();
    
    #else

//        #ifndef OP_UI//zhaoyanhua add 2004-4-9 10:44
    osd_init_prog();//terry,2003/12/8 11:37PM
//        #endif

        #ifndef PROG_DONT_PAUSE     //kubby 2003-8-8 23:06 added
    	if((cd_type_loaded == CDROM)&&(play_state != VCD_STATE_MP3_FILELIST)) //zhongshan modified to fix cannot play jpeg or mpeg file after use "prog" in GUI 2005-10-10 20:18 
    run_pause_setting();
        #endif

    #endif
    
    return TRUE;
}

#else

static inline UINT32 ProgSettingForNormal()
{   // 2005/01/14 yltseng
    #ifdef SDRAM_16Mb_Mode

    if( g_uiOSDStatus == OSD_FULL_SCREEN_STATUS_NONE )
    {
        if( AVD_state != STATE_IDLE )
        {
            g_uiOSDStatus = OSD_FULL_SCREEN_STATUS_PROGRAM | OSD_FULL_SCREEN_STATUS_WAIT_ATAPI_CMD_FINISH;
            return FALSE;
        }
        else if( pFsJpeg->gifsState == FS_STATE_JPEG )
        {
            OSDSetPause();
        }
    }
    
    g_uiOSDStatus   = OSD_FULL_SCREEN_STATUS_PROGRAM | OSD_FULL_SCREEN_STATUS_ACTIVE;
    full_scrn       = PROGRAM;
    osd_disable();
        
    extern void SrvStopReceiveData(void);
    SrvStopReceiveData();
    regs0->osd_base_addr = A_SERVO_YA;
    osd_init_prog();        
    
    #else

//        #ifndef OP_UI//zhaoyanhua add 2004-4-9 10:44
    osd_init_prog();//terry,2003/12/8 11:37PM
//        #endif

        #ifndef PROG_DONT_PAUSE     //kubby 2003-8-8 23:06 added
    run_pause_setting();
        #endif

    #endif

    return TRUE;
}
#endif

void ircmd_prog(void)
{
 //add xrh 
 #ifdef  PROGRAM_IN_STOP_STATE
#if defined(EASTECH_DVD_DP3240_D)||defined(EASTECH_DVD_DP2070_D)
  // mimitsai merge from dp2070/dp3240
    if(cd_type_loaded==CDDVD)
#else
  if((system_state!= SYSTEM_STOP))
#endif
    {
     ircmd_angle(); 
     return;
    }
#endif


#ifdef IR_PROG_ON

    // 2004/12/27 yltseng modify layout
    #ifdef CONTINUOUS_NUM_KEY_SELECT//Jack added 04/11/13
    if(ir_num_timer)
        return;
    #endif

    #ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
    #endif

    #if defined(MP3_ONLY_STOP_TO_GUI)&&defined(MODIFY_MP3_ONLY_STOP_TO_GUI)//nono add 4-8-10 11:00
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //only in FsMP3mainloop,can use "REPAB"
        )
    {
        invalid_key();
        return; 
    }
    #endif

    //printf("ircmd_prog\n");

    #ifdef SUPPORT_MIDI_MENU_SEL
        if(gIsMidiSelMenu) 
        {
            ircmd_post_func(CMD_FUNC|CMD_FUNC_PRG);
            return ;
        }
    #endif


    #ifdef SUPPORT_NESGAME
    if ( Is_GAME_STATE() ) {
        invalid_key();
        return;
    }
    #endif

    #ifdef SUPPORT_FILE_SYSTEM_MODE  // Robert 021007
    if (Is_OTHER_STATE())
    {
        #ifndef SUPPORT_FS_OTHER_PROG   //Maoyong 2004.04.15
        invalid_key();
        return;
        #endif
    }
    #endif

    #ifdef INVALID_WHEN_WRONG_REGION
    if(dvd_error==REGION_ERR)
        {
            invalid_key();
            return;
        } 
    #endif      

    #ifdef SUPPORT_GIF//when play GIF pic, "program" key cannot used,suqiaoli add 2004-2-27
    if(( GetCurrentFileType() == CDROM_GIF)&& Is_JPEG_PLAY_STATE())
    {
        invalid_key();
        return;
    }
    #endif
    
    if(shuffle_flag)//zhyf 2001/3/5 12:45PM
    {
        invalid_key();
        return;
    }

    //#ifdef JPEG_SLIDE_SHOW_USE_PROG
    //if (full_scrn & PROGRAM) //|| (prog_cnt && Is_JPEG_PLAY_STATE()))
    //#else
    if ((full_scrn & PROGRAM) || (prog_cnt && Is_JPEG_PLAY_STATE()))
    //#endif
    {    
    #ifdef PROGRAM_SHOW_DISPLAY   //dingzhy
        if(t_disp)
            DispFadeOut();
    #endif

        prog_cnt = 0; //disable prog function when we enter program page again
        full_scrn = 0;
        prog_func_off();
        
    #ifdef DISPLAY_CD_TEXT   //lizhx add 2004/09/06
       //printf("here it is!!!!!!!!!!!!\n");
       osd_init_CDText();
       show_CDText(v11_trk_now);
    #endif

    #ifdef SMT_DVD          //dingzhy for SMT   1/7/2004 10:51AM
        if(cd_subtype == CDROM_MP3)
    #endif
//end of SMT
        {      
    #ifdef MP3_DIRECT_SELECT//nono 3-12-24 22:51 for prog menu restored number error.
        #ifndef PROG_RESTORE_FOR_NGAILIK    //Not to clear Prog Numbers may be a better choice. I think. For there are two choices after pressing PROG Key: PROG or Play Key.
                                        //PLAY Key leads to program play, and PROG to normal play. heqiang, 2004-3-3 22:34
            prog_func_clear();
        #endif      
    #endif//MP3_DIRECT_SELECT
        }

        /*Mark by David 030924 update code(wthsin)
        #ifdef CD_PLAYER        //liweihua 2003-9-3
            if(cd_type_loaded==CDDA)
            {
                show_cdplayer();
            }
        #endif  
        */
    //#if defined(JPEG_SLIDE_SHOW_USE_PROG) || defined(STOP_IN_PROG_END)//wuxiaofeng 2004-03-16
        //PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);
    //#endif//#ifdef JPEG_SLIDE_SHOW_USE_PROG
    }
    else
    {
    //#ifndef JPEG_SLIDE_SHOW_USE_PROG
        if (Is_JPEG_PLAY_STATE())
        {
        #if defined(JPG_EFFECT)&&!defined(JPG_EFFECT_ONLY_ROTATE)&&!defined(IR_KODAK_EFFECT_KEY)&&!defined(IR_KODAK_EFFECT_KEY_USE_DISPLAY)&&!defined(JPG_EFFECT_USE_MARK_KEY)
            jpeg_effect_toggle();
        #else
            invalid_key();
            return;
        #endif
        }
        else
    //#endif//#ifndef JPEG_SLIDE_SHOW_USE_PROG
        {
    #ifdef PROGRAM_SHOW_DISPLAY    //dingzhy
            if(!t_disp)
                ircmd_display();
    #endif

            // 2004/11/26 yltseng
    #ifdef NEW_STYLE_SETUP
            if( !ProgSettingForNewStyleSetup() )
                return;
    #else
            if( !ProgSettingForNormal() )
                return;
    #endif
    
//        #ifdef OP_UI//zhaoyanhua add 2004-4-20 9:24         
//            prog_init();
//        #else   
            full_scrn = PROGRAM;
            index_x = 0;
            prog_cnt = 0;     //disable prog function when we enter program page again
            index_y = 2;
//        #endif

            ShowProgPage();

            OSD1000ISP_STATUS(OSDISP_PROG_ON, OSDIR_PROGRAM);

            //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:01                
            SetFullscrnCmdFuncPtr(prog_func_up, prog_func_down, prog_func_left,
                                  prog_func_right, prog_func_select);
        }
    }
#endif  /* IR_PROG_ON */

}

#else   // SETUP_PROGRAM_IN_PLACE_UNDER_16M

#ifdef SUPPORT_MOVE_SUBTITLE_BY_PRO_KEY   ///YANGLI ADD FOR MOVE SUBTITLE FOR 16:9,2005-11-28 11:24
int move_region_sub_flag =0;
#endif 
void ircmd_prog(void)
{
    
#if defined( SDRAM_16Mb_Mode) && defined(JPG_OLD_PARSER_FLOW) //lyc 2006-9-14
    if(Is_JPEG_STATE())   // zhangyu  2006-6-13 14:34
        prog_state=1;
#endif

#ifdef MPEG4_PROG_IS_DISALBE//Shenyj add for alco 11/11
    if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4))
    {
        invalid_key();
        return;
    }
#endif

#ifdef  PROGRAM_IN_STOP_STATE
    if(system_state!= SYSTEM_STOP)
    {
        ircmd_angle();	
        return;
    }
#endif

    #ifdef SUPPORT_MOVE_SUBTITLE_BY_PRO_KEY   ///YANGLI ADD FOR MOVE SUBTITLE FOR 16:9,2005-11-28 11:24
    if(pFsJpeg->gifsState == FS_STATE_OTHER)
    {
        if(move_region_sub_flag)
        {
            move_region_sub_flag=0;
            osd_init_OSDSRT();
        }
        else
        {
            move_region_sub_flag=1;
            osd_init_OSDSRT();
        }
    }
    else 
    invalid_key();
    return;
    #endif 

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    if((source_play_mode==USB_PLAY_MODE) || (source_play_mode==CARD_PLAY_MODE))
    {
        if((cd_type_loaded==CDUNKNOWN) || (usb_card_state==SWITCH_TO_USB_BUT_HAS_NO_USB) || (usb_card_state==SWITCH_TO_CARD_BUT_HAS_NO_CARD))
        {
            invalid_key();
            return;
        }
    }    
#endif
    
#ifdef  PROGRAM_IN_STOP_STATE
#if defined(EASTECH_DVD_DP3240_D)||defined(EASTECH_DVD_DP2070_D)
  // mimitsai merge from dp2070/dp3240
    if(cd_type_loaded==CDDVD)
#else
  if((system_state!= SYSTEM_STOP))
#endif
    {
     ircmd_angle(); 
        return;
        }
#endif

#ifdef IR_PROG_ON

#ifdef ALCO_DVD_UI  
    if(!IS_STOP_STATE())
    {
        invalid_key();
        return; 
    }       
#endif

#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
    if(need_record)//added 05/07/27 for VCD Playing--->STOP--->Quickly SETUP--->Then OSD is disordered.
        return;
#endif//end 

#ifdef CONTINUOUS_NUM_KEY_SELECT//Jack added 04/11/13
    if(ir_num_timer)
        return; 
#endif

#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)//xlluo for midi title
        {
        invalid_key();
        return;
        }
    #endif

#if defined(MP3_ONLY_STOP_TO_GUI)&&defined(MODIFY_MP3_ONLY_STOP_TO_GUI)//nono add 4-8-10 11:00
    if ( (Is_MP3_STATE()) 
      && (play_state == VCD_STATE_MP3_FILELIST) //only in FsMP3mainloop,can use "REPAB"
        )
    {
        invalid_key();
        return;
    }
#endif

    //printf("ircmd_prog\n");

    #ifdef SUPPORT_MIDI_MENU_SEL
        if(gIsMidiSelMenu) 
        {
            ircmd_post_func(CMD_FUNC|CMD_FUNC_PRG);
            return ;
    }
#endif


#ifdef SUPPORT_NESGAME
    if ( Is_GAME_STATE() ) {
            invalid_key();
            return;
        } 
#endif      

#ifdef SUPPORT_FILE_SYSTEM_MODE  // Robert 021007
    if (Is_OTHER_STATE())
    {
    #ifndef SUPPORT_FS_OTHER_PROG   //Maoyong 2004.04.15
        invalid_key();
        return;
#endif
    }
#endif

#ifdef INVALID_WHEN_WRONG_REGION
    if(dvd_error==REGION_ERR)
    {
        invalid_key();
        return;
    }
#endif      

#ifdef SUPPORT_GIF//when play GIF pic, "program" key cannot used,suqiaoli add 2004-2-27
    if(( GetCurrentFileType() == CDROM_GIF)&& Is_JPEG_PLAY_STATE())
    {
        invalid_key();
        return;
    }
#endif
#ifndef OP_PLAYMODE    
    if(shuffle_flag)//zhyf 2001/3/5 12:45PM
    {
        invalid_key();
        return;
    }
#else
    //if(shuffle_flag)
    //    PrintOsdMsg(STR_OS_RANDOM|(STR_OS_ON<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);    
    shuffle_flag = 0;//libing 2005-6-30 13:07
#endif

#ifdef PROG_ENTER_CANCEL_REPEAT 
     if(rep_mode)
     {
        rep_mode=0;
        ShowRepInfo();
     }   
#endif

    //#ifdef JPEG_SLIDE_SHOW_USE_PROG
    //if (full_scrn & PROGRAM) //|| (prog_cnt && Is_JPEG_PLAY_STATE()))
    //#else
        #if defined(ALCO_DVD_UI)&&defined(SDRAM_16Mb_Mode)
    if (prog_state)
    #else
    if ((full_scrn & PROGRAM)) //|| (prog_cnt && Is_JPEG_PLAY_STATE())) //joshua,20050605, modified for program function in JPEG_PLAY_STATE()
    #endif
    //#endif
    {
    
            #ifdef PROGRAM_SHOW_DISPLAY   //dingzhy
            if(t_disp)
            DispFadeOut();
            #endif
        prog_cnt = 0; //disable prog function when we enter program page again
        full_scrn = 0;
        #if defined(ALCO_DVD_UI)&&defined(SDRAM_16Mb_Mode)
        prog_state=0;
        #endif
        prog_func_off();
        #if defined(EASTECH_DVD_DP3240_D)||defined(EASTECH_DVD_DP2070_D)
    // mimitsai merge from dp2070/dp3240
        prog_func_clear(); // mimitsai add, clear prog function when we enter program page again
		#endif
		
#ifdef DISPLAY_CD_TEXT   //lizhx add 2004/09/06
       //printf("here it is!!!!!!!!!!!!\n");
       osd_init_CDText();
       show_CDText(v11_trk_now);
#endif

#ifdef SMT_DVD          //dingzhy for SMT   1/7/2004 10:51AM
if(cd_subtype == CDROM_MP3)
#endif
//end of SMT
{      
#ifdef MP3_DIRECT_SELECT//nono 3-12-24 22:51 for prog menu restored number error.
#ifndef PROG_RESTORE_FOR_NGAILIK    //Not to clear Prog Numbers may be a better choice. I think. For there are two choices after pressing PROG Key: PROG or Play Key.
                                    //PLAY Key leads to program play, and PROG to normal play. heqiang, 2004-3-3 22:34
        prog_func_clear();
#endif      
#endif//MP3_DIRECT_SELECT
}



        /*Mark by David 030924 update code(wthsin)
        #ifdef CD_PLAYER        //liweihua 2003-9-3
            if(cd_type_loaded==CDDA)
            {
                show_cdplayer();
            }
        #endif  
        */
        //#if defined(JPEG_SLIDE_SHOW_USE_PROG) || defined(STOP_IN_PROG_END)//wuxiaofeng 2004-03-16
        //PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);
				//#endif//#ifdef JPEG_SLIDE_SHOW_USE_PROG
    
        
#ifdef SDRAM_16Mb_Mode
        //if (old_t_disp)
        if ( 0)//( cd_type_loaded == CDDA ) && (old_t_disp) )
        {
            t_disp=old_t_disp;
            DispPolling(3);
        }
#endif
        // re-load setup module
        //LoadModual(MODUAL_AP2);
    }
    else
    {
        //#ifndef JPEG_SLIDE_SHOW_USE_PROG
        if (Is_JPEG_PLAY_STATE())
        {
            #ifdef JPG_OLD_PARSER_FLOW
                #if defined(JPG_EFFECT)&&!defined(JPG_EFFECT_ONLY_ROTATE)&&!defined(IR_KODAK_EFFECT_KEY)&&!defined(IR_KODAK_EFFECT_KEY_USE_DISPLAY)&&!defined(JPG_EFFECT_USE_MARK_KEY)
                    jpeg_effect_toggle();
                #else
                    invalid_key();
                    return;
                #endif
            #else
                
                if(Jpg_effect_is_valid==1)
                {
                    jpeg_effect_toggle();
                }
                else
                {
                    invalid_key();
                    return;                    
                }                                
            #endif    
        }
        else
        //#endif//#ifndef JPEG_SLIDE_SHOW_USE_PROG
        {
#ifdef PROGRAM_SHOW_DISPLAY    //dingzhy
if(!t_disp)
ircmd_display();
#endif
#ifdef SDRAM_16Mb_Mode
           //zhaoyanhua modify  2003-8-7 18:47
            #ifdef NEW_STYLE_SETUP   
            if (play_state != VCD_STATE_STOP)
            {
                if (prog_state == 0)
                {
                    prog_state = 1;
                    ircmd_stop();
                    return;
                }
                
            }
            else
            {
                if (prog_state == 0)
                {
                    prog_state = 2;//has in STOP state.
                    ShowTitle();
                }
              
                old_t_disp = t_disp;
            }
            #else
                #if defined(ALCO_DVD_UI)&&defined(SDRAM_16Mb_Mode)
            if (prog_state == 0)
            {
                prog_state = 2;
                old_t_disp = t_disp;
            }
            #else
            if (play_state != VCD_STATE_STOP)
            {
                if (prog_state == 0)
                {
                    prog_state = 1;
                    old_t_disp = t_disp;
                    #ifdef JPEG_MP4_FRIST_STOP_TO_GUI//caoh 2005-6-16 21:02
                       mp4_to_logo = 1 ;
                    #endif
                    ircmd_stop();
                    return;
                }
            }
                #endif//end #if defined(ALCO_DVD_UI)&&defined(SDRAM_16Mb_Mode)
            #endif//NEW_STYLE_SETUP 
            
#endif
            // load prog module first
            //LoadModual(MODUAL_AP3);
//        #ifdef OP_UI//zhaoyanhua add 2004-4-20 9:24         
//            prog_init();
//        #else   
            full_scrn = PROGRAM;
            index_x = 0;
            prog_cnt = 0;     //disable prog function when we enter program page again
            index_y = 2;
//      #endif
#ifdef SDRAM_16Mb_Mode
            t_disp=0;
            DispFadeOut();
            regs0->osd_base_addr = OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
            osd_init_prog();
#else
//    #ifndef OP_UI//zhaoyanhua add 2004-4-9 10:44
            osd_init_prog();//terry,2003/12/8 11:37PM
//    #endif
#ifndef PROG_DONT_PAUSE     //kubby 2003-8-8 23:06 added
            run_pause_setting();
#endif
#endif
            ShowProgPage();

            OSD1000ISP_STATUS(OSDISP_PROG_ON, OSDIR_PROGRAM);

            //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:01                
            SetFullscrnCmdFuncPtr(prog_func_up, prog_func_down, prog_func_left,
                                  prog_func_right, prog_func_select);
        }
    }
#endif  /* IR_PROG_ON */

}

#endif  // SETUP_PROGRAM_IN_PLACE_UNDER_16M

#ifdef GPS_DVD//frank.huang 050926 add for GPS_DVD
void ircmd_touch_menu(void)
{
	extern	void GPS_key_menu(void);
	GPS_key_menu();//frank.huang 050801
}
#endif

void ircmd_cancel(BYTE show)               //cancel program & shufle
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
    UINT8 md=show&C_PLAY;

    if(show&C_ZOOM)
    {

        if(vpp_zoom)
        {
            vpp_zoom=0;
            set_video_aspect();
            startup_vpp();
            setVPP_DoItNow();

        }

    }

    show=show&C_SHOW;
    //md 0 show 0: don't show message && STRORE program
    //          1: show cancel program && STRORE program
    //md 1      0: don't show message &&  STRORE/PLAY program
    //          1: don't show message &&  STRORE/PLAY program



#ifdef SDRAM_16Mb_Mode
    if (prog_state==0)
#endif
    if( ((prog_cnt)&&md)||((full_scrn&PROGRAM)&&!md) )
    {
        ClearOsdMsg(1);
        
        full_scrn=full_scrn&(!PROGRAM);
        prog_index=0;
        shuffle_flag=0;
        mark_cnt=0;
        prog_func_clear();
        
        if(show) {
            #ifdef SKYWORTH_DVD
            OSD1000ISP_STATUS(OSDISP_PROG_CNL, OSDIR_PROGRAM);

            PrintOsdMsg(STR_OS_PROG_CNL,REGION2,1,0);
            #else
            OSD1000ISP_STATUS(OSDISP_PROG_CNL, OSDIR_PROGRAM);

            PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);
            #endif
        }
        
    }
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}


/*
** ircmd_mark
*/
void ircmd_mark(void)
{
#ifdef IR_MARK_PLAY
    MSF t;
    if( play_state==VCD_STATE_NORMAL && (!IsPBCOn()) )
    {
        if(mark[mark_cnt]==0)
        {
            mark[mark_cnt]=MSF(bcd2bin(cd_qocde_mm),bcd2bin(cd_qcode_ss),0x0);
            /*
            mark_cnt=1;
            show_goto(10);
            mark_cnt=0;
            */
        }
        else
        {

            s_msf   = mark[mark_cnt];
            restart_video_engine();
            //do_cd_seek(-6);

            goto_number = mark[mark_cnt];
            //     mark_cnt=0;
            //show_goto(10);
            //play_sel_time(t);
            mark[mark_cnt]=0;
        }


    }
    else invalid_key();
#endif
}



/**********************************************/
/*                      */
/* ircmd_book                   */
/*                      */
/***********************************************/

void cancel_disp_mode(void)
{
    full_scrn=0;
    if(disp_mode) {
        t_disp=disp_mode;
        disp_mode=0;
        disp_fade_in();
    } else {//cancel display
        #ifdef DISPLAY_MENU_BUG_FIX
        osd_tog_region(0,OSD_OFF);
        t_disp = 0;
        #else
        DispFadeOut();
        #endif
 
        #ifdef MODIFY_FOR_DISPLAY_DBG//shenyj add for alco 1108
         disp_mode=0;
        polling_clock=0;
        remain = 0; 
        t_disp = 0; 
        display_flag = 0;
        display_and_time=0;
        #endif
    }
}

#ifdef SUPPORT_BOOK
//Jeff 20020411
void ircmd_book(void)
{



#ifdef ORITRON_HK_DVD   //qinhua add 
    if ((GetCurrentFileType() == CDROM_MP4))
    {
        invalid_key();
        return;
    }
#endif




    //printf("ircmd_book\n");
#ifdef PBCON_INVALID_GOTO_BOOK_KEY
if((cd_type_loaded == CDVCD10)||(cd_type_loaded ==CDSVCD)||(cd_type_loaded == CDVCD20))//lizhx add 2005-7-13 19:02
{
    if (IsPBCOn())
    {
        invalid_key();
        return;
    }
}
#endif
#ifdef JPG_EFFECT_USE_MARK_KEY
    if(cd_type_loaded == CDROM)
    {
        if (Is_JPEG_PLAY_STATE())
        {
        #ifdef JPG_EFFECT
                jpeg_effect_toggle();
                return;
        #else
                invalid_key();
                return;
        #endif
        }

        else
        {
            invalid_key();
            return;
        }
    
    }//if(cd_type_loaded == CDROM)
#endif//JPG_EFFECT_USE_MARK_KEY

#ifdef SUPPORT_CDG    //terry,2003/8/7 12:37AM
    if(is_cdg_disc(1)) return;  
#endif

    if (full_scrn==0 && t_disp!=1 && t_disp!=2 )
        t_disp=0; //2002-7-4

    if(shuffle_flag)//nono 2-5-15 17:50
    {
        shuffle_flag = 0;

        OSD1000ISP_STATUS(OSDISP_RAN_CNL, OSDIR_GLOBAL);

        PrintOsdMsg(STR_OS_RAN_CNL,REGION1,1,0);
    }

    if (full_scrn&MARK)
    {
        cancel_disp_mode();
    } else {
        //Jeff 20020418
    #ifdef VIRTUAL_KEYBOARD//liweihua add 20031124
     if(full_scrn==KEYBOARD)// for goto exit id3 jiangxl
        osd_init();
    #endif
        if (!(full_scrn&GOTO))    /* alan 2002/6/13 11:33と */
            disp_mode=t_disp;

        full_scrn=MARK;

        index_x=0;
        goto_time=0;

        t_disp=3;
        DispFadeIn();
        DispCookOSD0(1);
        #ifdef SDRAM_16Mb_Mode
        DispPolling(3);
        #else
        DispPolling(0);
        #endif
        
        //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:32
        SetFullscrnCmdFuncPtr( ircmd_null, ircmd_null,  mark_func_left,
                               mark_func_right, book_func_select);
    }

//linrc mark 2004-5-10 14:07 and mark it in book.c
//when call bookmark, REPEAT doesn't need as idle,when bookmark is paly,it need change as idle
/*  if(rep_ab_mode != REPEAT_IDLE) {
        rep_ab_mode = REPEAT_AB_IDLE;
        show_repeatAB(1);
    }*/
}
#else
void ircmd_book(void) 
{

#ifdef USE_IR_TO_CHANGE_TVTYPE
    setup_DVD_TVType(action_click);
#endif//#ifdef USE_IR_TO_CHANGE_TVTYPE

}
#endif



/*
** ircmd_goto
*/
void ircmd_goto(void)
{
    #ifdef PBCON_INVALID_GOTO_BOOK_KEY
    if((cd_type_loaded == CDVCD10)||(cd_type_loaded ==CDSVCD)||(cd_type_loaded == CDVCD20))//lizhx add 2005-7-13 19:02
    {
        if (IsPBCOn())
        {
            invalid_key();
            return;
        }
    }
    #endif
	
#ifdef MPEG_FILE_TELL_THE_CORRECT_EXTER_NAME//libing 2005-9-28 14:53
if(IS_FILE_TYPE_MPG12() && (cd_type_loaded!=CDDVD)&&(cd_type_loaded!=CDDA)&&(cd_type_loaded!=CDSVCD)&&(cd_type_loaded!=CDVCD10)&&(cd_type_loaded!=CDVCD20)&& (!Is_MP3_STATE())&&(GetCurrentFileType() != CDROM_WMA) )  //qinhua ,add for after MPEG not goto function,2005-10-24 13:23
{
	invalid_key();
	return;
}
#endif

#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#ifdef IRCMD_DBG
    printf("============= goto ==============\n");
#endif


    if (( (cd_type_loaded==CDROM)     
#ifdef SUPPORT_USB                  //sunzhh add 2005-3-16    
    ||((storage_type==USB_DEVICE)&&(cd_type==CDROM)) //lyc 2005-8-1 note: for play DVD/VCD and insert usb goto is invalid 
#endif    
    )&& (Mp3ReadFinish==0) ){ //Jeff 20020614
        invalid_key();
        return;
    }

#ifdef GOTO_CHECK_UOP   //linrc 2005-1-29 15:35 // 2005/06/28 yltseng
if( (cd_type_loaded==CDDVD) &&
    (UOP_check(UOP_TT_P) && !is_ptt_search() && !is_time_search()) )
{
    invalid_key();
    return;
}
#endif

#ifdef SDRAM_16Mb_Mode      //gerry,2004-6-7 21:43
    if(full_scrn==SETUP)
        return;
#endif//SDRAM_16Mb_Mode

#ifdef GOTO_CANCEL_PROG   //2004-5-20 05:24?宇P
    if (prog_cnt)
    {
        prog_cnt=0;
        prog_func_clear();
        prog_func_off();

        OSD1000ISP_STATUS(OSDISP_GOTO_PROGCNL, OSDIR_GOTO);

        PrintOsdMsg(STR_OS_PROG_CNL,REGION1,1,0);

    }
#endif

#ifdef SUPPORT_MP4  // 2004/07/27 yltseng   
    if( IsUserControlDisabledByTrickyPlay( IRC_GOTO ) )
    {
        invalid_key();
        return;
    }
#endif

#if 1
    #ifdef SUPPORT_MIDI_MENU_SEL    //modify xlluo 04-10-09
    if(gIsMidiSelMenu)                                                  
    {
        #ifdef MIDI_SCORE_TEST
        ircmd_post_func(CMD_FUNC|CMD_FUNC_POWER);
        return;
        #else //MIDI_SCORE_TEST
        return;
        #endif//MIDI_SCORE_TEST
    }
    #endif//SUPPORT_MIDI_MENU_SEL
#else//#if 1
    #ifdef SUPPORT_MIDI_MENU_SEL
    if(gIsMidiSelMenu)  return;
    #endif
#endif//#if 1

#ifdef INVALID_WHEN_WRONG_REGION
    if(dvd_error==REGION_ERR){
        invalid_key();
        return;
    }
#endif      

#ifdef NEWSTYLE_WINDOW
//xyy 2003-9-15 21:10
//    if(cd_type_loaded==CDDVD || cd_type_loaded==CDSVCD || cd_type_loaded==CDVCD20 || cd_type_loaded == CDVCD10) {
    if(cd_type_loaded >= CDDA && cd_type_loaded<=CDDVD) {
        if(full_scrn&MESSAGE) {
            // reset display outlook
            exit_browse_func();
    } else {
/*            if(is_menu()) {
                invalid_key();
                return;
            }

        if(play_state==VCD_STATE_STOP) {
                invalid_key();
                return;
            }
*/          
            full_scrn=MESSAGE;

//      disable_uop=1;

            // setup display outlook
        #ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW //zhaoyanhua add 2003-11-30 15:32
            DrawNewWindow();
        #else
            osd_init_newstyle_window();
        
        {
            arc_region_loc.region  = 2;

                osd_draw_rect(0,0,38*16,374,4);

                arc_region_loc.xStart  = 2*16-15;
                arc_region_loc.yStart  = 6;
                arc_region_loc.xLen    = 21*16+32;
                arc_region_loc.yLen    = 24*10-20;
                arc_region_loc.bkColor = 9;
                arc_region_loc.radius  = 10;
                osd_draw_region_arc(&arc_region_loc,2);


                arc_region_loc.xStart  = 2*16-15+10;
                arc_region_loc.yStart  = 16;
                arc_region_loc.xLen    = 21*16+32-20;
                arc_region_loc.yLen    = 24*10-40;
                arc_region_loc.bkColor = 0;
                osd_draw_region_arc(&arc_region_loc,2);
            }
            exe_browse_func();
            exe_show_time();
        #endif//#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
        }
    }
//xyy 2003-9-15 21:11 modified
//    else  
//#endif
#else//#ifdef NEWSTYLE_WINDOW

#if defined(SUPPORT_FILE_SYSTEM_MODE) && (defined(SUPPORT_PRECALCULATE_VIDEOBITRATE_FOR_FILE_MODE) || !defined(SUPPORT_MPG_FILE_PARSER))
//nono 3-6-24 16:41, 2006/05/03 yltseng
//shenyj add for alco 11/14
    if ((GetCurrentFileType() == CDROM_MPG) 
    #ifdef SUPPORT_MP4                                            //ycwen 2005/12/8 add OGG  //by roger 2006-04-18 add asf          
     || (GetCurrentFileType() == CDROM_MP4 && !IS_FILE_TYPE_AVI()&& !IS_FILE_TYPE_OGG() &&!IS_FILE_TYPE_ASF()
     #if defined(SUPPORT_GOTO_NERODIGITAL)&&defined(SUPPORT_NERODIGITAL)
      && !IS_FILE_TYPE_QT() && !IS_FILE_TYPE_ND()
     #endif      //lyc add 2006-1-9 for NERO DIGITAL GOTO //ouyang change "&&" 2006-1-14 16:12
     ) 
    #endif
     )
    {        
        invalid_key();
		#ifdef SUPPORT_DISPLAY_GOTO		//linrc update 2006-3-17 16:54
		display_flag = 0;
		#endif
        return;
    }
#endif

//lyc add 2006-1-9 for NERO DIGITAL GOTO 
	#if defined(SUPPORT_GOTO_NERODIGITAL)&&defined(SUPPORT_NERODIGITAL)
	 if((IS_FILE_TYPE_QT())||(IS_FILE_TYPE_ND()))
	  pFsJpeg->g_uiFileChangeChapter = 3;
#endif

#ifdef FUSS_DVD
#ifndef FUSS_LIDE_DVD//2-7-2 13:43 lide no bookmark_menu.
    // if (full_scrn==0 && t_disp!=1 ) t_disp=0;    // alan 2-6-8 0:30
    if (full_scrn==0 && t_disp!=1 && t_disp!=2 )
        t_disp=0;  //2002-7-4
    //#else
    //  if (full_scrn==0) t_disp=0;    // alan 2-6-8 0:30
#endif
#endif


#ifdef HOBO_DVD
    if(full_scrn == 0)       DispFadeOut();
#endif

    //terry,2002/5/9 10:15と,conflict
    /*if(shuffle_flag)//zhyf 2001/3/5 12:45PM//jhuang merge 3/7
    {
    invalid_key();
    return;
}*/

#ifdef IR_GOTO_ON

    if(full_scrn&GOTO)
    {
        #ifdef NEW_DISPLAY_GOTO_OSD//for the second page of GOTO
        if(disp_mode==2)
            disp_mode=0;//disappear the second page of DISPLAY
            
        if((t_disp==1))
        {
            disp_mode=0;
            t_disp=2;
        }
        else
        #endif
        {
        if (disp_mode==0)         /*  alan 2002/6/13 11:34と to make display disppear */
        {
            OSD1000ISP_STATUS(OSDISP_GOTO_CNL, OSDIR_GOTO);

            cancel_disp_mode();
        }
        else {
            OSD1000ISP_STATUS(OSDISP_GOTO_CNL, OSDIR_GOTO);

            full_scrn=0; t_disp=disp_mode;
            
            #ifdef DISPLAY_MENU_BUG_FIX    
            if(t_disp)
            {
                //printf("goto cancel...display base menu refresh............\n");
                //disp_fade_in(); 
                DispPolling(1);
            }
            #endif
            
        }
        }
    }else
    {
        OSD1000ISP_STATUS(OSDISP_GOTO_ON, OSDIR_GOTO);
        #ifdef SUPPORT_JPEG_GOTO
        if((cd_type_loaded==CDROM) && (pFsJpeg->gifsFuncBtn==FS_FUNC_JPEG))
        {
          if(pFsJpeg->gbfsSlide)
            set_rtc_val(0);
        }
        #endif

        full_scrn=GOTO;
        SetFullscrnCmdFuncPtr( search_func_up, search_func_down, search_func_left,
                                   search_func_right, search_func_select);

    #ifdef VIRTUAL_KEYBOARD//liweihua add 20031124
        osd_init();
    #endif

#ifdef REPEAT_SHUFFLE // alan 2-6-4 22:35 modified for FUSS
        if(rep_mode != REPEAT_IDLE)/*kenny add it 2002/6/4 02:48 */
        {
            rep_mode = REPEAT_IDLE;
            ShowRepInfo();

        }
#endif

        if(play_state==VCD_STATE_STOP)
        {
            resumeMSF=0;//test 2-6-4 17:43
            resumeTRK=0;
        }
        
        // 2005/06/28 yltseng
        extern int  srhGetSearchPosition( UINT32 uiType, UINT32 uiDir, int iIdx );
        index_x = srhGetSearchPosition( cd_type_loaded, 0, 0 );

        goto_time=0;
        if(cd_type_loaded==CDDVD){               //add by shawn 20020219
            dvd_title=get_tt_info(DISP_TT);  //add by shawn 20020219
            dvd_chapter=get_tt_info(DISP_CH);  //add by shawn 20020219
        }else  //add by shawn 20020219
            dvd_title=disp_trk_now;           //add by shawn 20020219


        if (!(full_scrn&MARK))     /* alan 2002/6/13 11:35と */
            disp_mode=t_disp;

        #ifdef ALCO_DVD_UI
        dvd_title = 0;
        dvd_chapter = 0;
        #endif
        
        if(t_disp!=1)
        {
            t_disp=1;
            #ifndef NEW_DISPLAY_GOTO_OSD
            disp_mode = 0;//nono 20030913 need to be modified again
            #endif
            disp_fade_in();
            #if defined(SDRAM_16Mb_Mode)&&defined(ALCO_DVD_UI)  //Jack added 04/12/10
            DispPolling(3);
            #endif
        }
    }

    if(shuffle_flag)
    {
        shuffle_flag = 0;
        #ifndef ALCO_DVD_UI
        PrintOsdMsg(STR_OS_RAN_CNL,REGION1,1,0);
        #endif
    }

    //  playmode_sel(GOTO);

    if(rep_ab_mode != REPEAT_IDLE)/*kenny add it 0929*/ /*jhuang 2001/2/18 10:53PM*/
    {
        rep_ab_mode = REPEAT_AB_IDLE;
        show_repeatAB(1);
    }
#endif//#ifdef IR_GOTO_ON
#endif //#ifdef NEWSTYLE_WINDOW
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

//terry,2-5-15 23:54
//show random osd message
void show_random_osd_msg(int id)
{
    int md=0;
   #if defined(SKYWORTH_DVD)||defined(HUAJIA_DVD)
   if(shuffle_flag)
        id = STR_OS_ON;
    else 
        id = STR_OS_OFF;
    #endif       
    if(id)
        md=4;
    #ifndef OP_PLAYMODE
    if (play_state!=VCD_STATE_STOP)
    #endif
     { //remove RANDOM OSD when STOP, Jeff 20020522
        PrintOsdMsg(STR_OS_RANDOM|(id<<OSDSTR_ID_TOTL_BIT),REGION1,1,md);
    }
}


void ircmd_shuffle(void)
{
#ifdef OP_PLAYMODE      
    if (prog_cnt)
    {
        prog_cnt=0;
        prog_func_clear();
        prog_func_off();

        OSD1000ISP_STATUS(OSDISP_GOTO_PROGCNL, OSDIR_GOTO);

        PrintOsdMsg(STR_OS_PROG_CNL,REGION2,1,0);

    }
#endif    
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
    #ifdef SETUP_DONGLI459 //1/16/2004 15:00 jasingou
    if((cd_type_loaded==CDVCD20||cd_type_loaded==CDSVCD)&&IsPBCOn())
    {
        invalid_key();
        return;
    }
    #endif
    #ifdef SUPPORT_FILE_SYSTEM_MODE    //nono 3-12-6 16:06
    if ( Is_OTHER_STATE() ) {
      invalid_key();
      return;
    }   
#endif      
    
#if defined(SKYWORTH_DVD)||defined(HUAJIA_DVD)
    ircmd_cancel(C_SHOW | C_PLAY); 
      if(is_menu())
    {
      invalid_key();
      return;
    }   
#endif      
    
#ifdef TONIC_DVD    
    if( IsPBCOn() )  pbcoff_init();    //wangshf
#endif

#ifdef IR_SHUFFLE_ON

    UINT32 id;

#if defined(INTECH_DVD)||defined(LINKCONCEPT_DVD)//nono 2-5-22 10:07
    if(cd_type_loaded==CDDVD)
    {
        invalid_key();
        return;
    }
#endif

    if(play_state==VCD_STATE_PAUSE)//NONO 2-5-20 13:51 for pause->random can't cancel VCD_STATE_PAUSE
    {
        chg2normal_play(PAUSE2NORM,REALPLAY);

    }

    if(full_scrn&MARK)
        ircmd_book();//nono 2-4-15 10:05
    if(full_scrn&GOTO)
    {   
    #ifdef DIV_GOTO_DISPLAY
        ircmd_search();
    #else
        ircmd_goto();//nono 2-5-15 11:17
    #endif
    }
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
        
    if(action_click)

#endif
    {
        shuffle_flag=(shuffle_flag+1)%2;
        if(cd_type_loaded==CDDVD)
        {
            #ifndef TEST_SERVO
            if(!DVD_check_state())
            {
                invalid_key();
                return;
            }
            #else
            ;
            #endif
        }else if((cd_type_loaded != CDDA)&&(cd_type_loaded !=CDROM))
        {
           #if !defined(SKYWORTH_DVD)&&!defined(HUAJIA_DVD)
            if( IsPBCOn() )             //test only
            {
                if(play_state!=VCD_STATE_STOP)
                {
                    invalid_key();
                    return;
                }
            }
            #endif
        }

        if (shuffle_flag) //alan 0430 : solve random play again when cancel shuffle mode
        {
            chg2normal_play(FAST2NORM|PAUSE2NORM|SLOW2NORM,TRANSFER);
            #ifdef SUPPORT_DVD_RANDOM_ALL_TITLE_CHAPTER//chenzhao20060209//hongfeng add DVD random all title and chapter 2005/12/15
            if((cd_type_loaded!=CDROM)&&(cd_type_loaded!=CDDVD))
                {
                    if (cd_type_loaded == CDDA)
                        shuffle_track = get_random_number(cd_trk_hi - 0);   //avoid when random play CD can't play the last one hongfeng 2005-04-19
                    else    
                        shuffle_track = get_random_number(cd_trk_hi - cd_trk_lo);
                }
            else if(cd_type_loaded==CDDVD)
                {
                UINT16 temp=full_scrn;
                dvd_title = get_tt_info(DISP_TT_Ns);

                shuffle_track = get_random_number( dvd_title - 0);
                dvd_title = shuffle_track;

                full_scrn=GOTO;//chenzhao 20060213 avoid to goto invalid chapter.
                dvd_chapter=get_tt_info(DISP_CH_Ns);
                full_scrn=temp;
                shuffle_track = get_random_number( dvd_chapter - 0);
                dvd_chapter = shuffle_track;
            }
            #else//SUPPORT_DVD_RANDOM_ALL_TITLE_CHAPTER
            if(cd_type_loaded!=CDROM)
            {
              
               #ifdef SHUFFLE_ACCOMPLISH_BY_ARITHMETIC         //wangmin add for the real shuffle when cd playing 051020
                shuffle_track = shuffle_new(v11_trk_now, cd_trk_hi - cd_trk_lo +1 );//,NOT_FS_SHUFFLE);
                #else
                shuffle_track = get_random_number(cd_trk_hi - cd_trk_lo);
                #endif
             }
            #endif//SUPPORT_DVD_RANDOM_ALL_TITLE_CHAPTER
            
                

             #ifdef ZOOM_DIRECT_STOP_SLIDE       //Maoyong  2004.07.05
             ForceStopJpgSlide();
             #endif
             #ifdef SUPPORT_DVD_RANDOM_ALL_TITLE_CHAPTER//chenzhao20060209//hongfeng add 2005/12/15
             if(cd_type_loaded!=CDDVD)
        		ircmd_post_func(CMD_FUNC | CMD_FUNC_SHUFFLE);
             else if(cd_type_loaded==CDDVD)
                 ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);
             #else
             ircmd_post_func(CMD_FUNC | CMD_FUNC_SHUFFLE);
             #endif
        }
    }
    #if defined(SKYWORTH_DVD)||defined(HUAJIA_DVD)
    if(shuffle_flag)
      id=STR_OS_ON;
        else
      id=STR_OS_OFF;
    #else
    if (!action_click || !shuffle_flag)                       /* alan 0425 */
    {//terry,2-5-15 23:59
    
        if(shuffle_flag)
            id=STR_OS_ON;
        else
    
            id=STR_OS_OFF;
    }
    
     else
        id=0;
    #endif
 #if defined(SKYWORTH_DVD)||defined(HUAJIA_DVD)
    if(shuffle_flag)
    {
        disc_st_time = M2I(gettrkmsf(cd_trk_lo_now));
        pbcoff_init();
    }
#endif   

    show_random_osd_msg(id);

    
    if(RegionOnOff[REGION1][2]==STR_OS_RANDOM)
    {
        //printf("rep cancel\n");
        cancel_rep();
    }

#ifdef FUSS_DVD//2-6-28 15:03
#ifdef FUSS_PANEL
    book_flag=0;//to make book_flag doesn't toggle.2-6-28 15:14
#endif
#endif

#endif
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}




void playmode_sel(BYTE flag)
{
    switch(flag)
    {
    case CLEAR_ALL:                  //clear all flag
        shuffle_flag=0;              //kenny add 891005
        prog_index = 0;
        if(!(full_scrn&PROGRAM)||(play_state==VCD_STATE_OPEN))
            #ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT //chenzhao 2006-4-19 17:56 .
            if(! is_multidisc_trayout_only() &&rep_mode!=REPEAT_ALL_DISCS)
            {
            rep_mode=REPEAT_IDLE;
            }
            #else
            rep_mode=REPEAT_IDLE;
            #endif
        rep_ab_mode = REPEAT_IDLE;
        return;
    case RESUME:                     //clear all except resume flag
        rep_mode=REPEAT_IDLE;       //clear repeat 1&ALL
        rep_ab_mode=REPEAT_IDLE;    //clear repeat A&B
        shuffle_flag=0;              //kenny add 891005
        return;

#ifdef IR_PROG_ON
    case PROGRAM:
        shuffle_flag=0;              //kenny add 891005
        prog_index=1;
        rep_mode=REPEAT_IDLE;       //clear repeat A&B
        return;
#endif
#ifdef IR_REPEAT_ALL_ON
    case REPEAT_ALL:                 //keep repeat value
        if(rep_mode!=REPEAT_IDLE)
            rep_mode=REPEAT_IDLE;
        return;
#endif

    case REPEAT_AB:
        shuffle_flag=0; //kenny add it
        rep_ab_mode=REPEAT_AB_IDLE;                 //keep rep_mode
        return;

    }
}




/*------------------------------------------------------------------------
Function: get_random_number

  Description:
  This function returns a random value between 1 and mode_number
  (included) .

    NOTE: This function only works for mode_number <= 256
------------------------------------------------------------------------*/
BYTE get_random_number(int range)
{
#ifdef IR_SHUFFLE_ON
    BYTE number;
    BYTE mod_number;

    do
    {
        mod_number=(BYTE)regs0->rtc_15_0;

        if (mod_number <= 0) return(1); /* for invalid mod_number */

        if (SeedSeed & 0x80000000)
            SeedSeed = ((SeedSeed ^ MASK) << 1) | 1;
        else
            SeedSeed <<= 1;

        number = SeedSeed >> 24;

        while (number >= mod_number)
            number -= mod_number;
        number = (number) % range;
        number++;   /* get number from 1 to mod_number */
    }while(number<=0);

    return (number);
#else
    return (BYTE)range; //terry,2004/4/8 05:35PM    
#endif
    
}



/* jjding  2000/08/25 */

void stop_init(void)
{
#ifdef  SUPPORT_BOOK
    extern BYTE    bookIndex;
    bookIndex=0;
#endif

    index_y=0;

    //printf("stop init\n");
    AUDIF_Set_Volume(0);//AudioSetVolume(0);
    adv_search_time = 0 ; //jjding 2001-03-12
    video_slow=0;
    avd_slow_state(video_slow);
    avd_play_state();
    avd_src_realtime    = 0;//nono add.20050825 to avoid logo video quality worse when open tray.
    //  cderr_clear_seqerr();
    //  cderr_clear_seekerr();
    //  cderr_clear_crcerr();
    //  RetryFlyingDisk=0;
    goto_active = 0;
    bIntro=0;                   // ych 2-1-23 13:21
    //  pbc_black_enable=0;/*jhuang 891107*/
 
    #ifndef ALWAYS_DEFAULT_DIR_REPEAT
    #ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT //chenzhao 2006-4-19 17:57 .
    if(rep_mode != REPEAT_IDLE && rep_mode != REPEAT_ALL_DISCS)
    #else
    if(rep_mode != REPEAT_IDLE)//||(rep_ab_mode != REPEAT_AB_IDLE))
    #endif
    {//zhyf for nintaus reqestion 1-3-10 11:37
        #ifdef ALCO_DVD_UI
        rep_mode = REPEAT_IDLE;
        #else//#ifdef ALCO_DVD_UI
        OSD1000ISP_STATUS(OSDISP_REP_IDLE, OSDIR_REPEAT);
        
        //joshua, 2005.4.15, i replaced following code by cancel_rep();
        cancel_rep();
        //PrintOsdMsg(STR_OS_REP_CNL,REGION2,1,0);
        //rep_mode    = REPEAT_IDLE;
        #endif//#ifdef ALCO_DVD_UI
    }
    #endif

#ifdef FUSS_DVD
    DispFadeOut();//nono 2-4-15 10:05
    if(full_scrn & MARK)
        ircmd_book();//nono 2-5-15 11:08
    if(full_scrn&GOTO)
        ircmd_goto();//nono 2-5-15 11:17
#endif

    if(play_state != VCD_STATE_OPEN)
    {
    /*terry,0516 , move to  after play_state = VCD_STATE_STOP
    if(cd_type_loaded!=CDROM)
    {
    show_time();
    }*/
        //else
        //  Display_Mp3play_Time(0);

        if( play_state!=VCD_STATE_POWER )
        {
            if(full_scrn==SOUND)
                cancel_sound();

            if(play_state!=VCD_STATE_CLOSE)//2-5-15 0:36 to avoid open<-->play quickly show "stop"
#if defined(IR_PLAY_RESUME) ||defined(IR_PLAY_RESUME_PAUSE)//nono 2-3-26 11:34 for fuss
            {
                int id;
                #ifdef DVD_5_DISC_RESUME_8202S_1X16//LIJD 2005-4-14 16:50       
                if(resumeMSF)
                    id=STR_OS_SPACE;
                #else
                if(resumeMSF)
                    id=STR_OS_PRE_STOP;
                #endif
                
                else
                {
                    id=STR_OS_STOP;
#ifdef FUSS_DVD//2-6-28 15:03
#if defined(FUSS_PANEL)||defined(FUSS2_PANEL)
                    book_flag=0;//to make book_flag doesn't toggle.2-6-28 15:14
#endif
#endif

                }

#ifdef SDRAM_16Mb_Mode
                if (prog_state==0)
#endif

#ifndef ALWAYS_DISPLAY_PRE_STOP       //fengjl added 3-11-28 22:47 
                #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
                if(usb_card_state != SWITCH_TO_USB_BUT_HAS_NO_USB)
                #endif
                PrintOsdMsg(id,REGION1,1,0);
#else
                {
                    if(id==STR_OS_PRE_STOP)//LIBING
                    {
                        OSD1000ISP_STATUS(OSDISP_PRE_STOP, OSDIR_STOP);

                        PrintOsdMsg(id,REGION1,0,0);
                    }
                    else if(id==STR_OS_STOP)
                    {
                        OSD1000ISP_STATUS(OSDISP_STOP, OSDIR_STOP);

                        PrintOsdMsg(id,REGION1,1,0);
                    }
                }
#endif
                play_state = VCD_STATE_STOP;
            }
#else
            {
                #ifdef GBM_DVD
                OSD1000ISP_STATUS(OSDISP_STOP, OSDIR_STOP);

                PrintOsdMsg(STR_OS_STOP,REGION1,0,0);
                #else 
                #ifdef SPHE1000
                if (!support_dvb_flag)
                #endif
                {
                OSD1000ISP_STATUS(OSDISP_STOP, OSDIR_STOP);

                PrintOsdMsg(STR_OS_STOP,REGION1,1,0);
                }
                #endif 
                play_state = VCD_STATE_STOP;
            }
#endif //nono 2-3-13 11:21 for yuxing
            if(cd_type_loaded!=CDROM) //terry,0518
                show_time();
        }
    }
    else
    {
        #ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT //chenzhao 2006-4-19 18:0 .
        if(rep_mode == REPEAT_ALL_DISCS)
        {
            reset_status();
            rep_mode = REPEAT_ALL_DISCS;
        }
        else
        #endif
        reset_status();  //zhyf 1-2-8 9:30

#ifndef SDRAM_16Mb_Mode
        //ClearOsdMsg(2);
#endif
//    #ifndef OP_UI//zhaoyanhua add 2004-4-14 15:33
    //we need not clear the prog content
        prog_func_clear(); //Clear program contents and count Jeff 20010919
//    #endif//ifndef OP_UI      
        resumeMSF = 0;
        resumeTRK = 0;
    }

    //vpp_zoom=1;//terry,891004
    //vpp_zoom_x = 0;
    //vpp_zoom_y = 0;
    rep_track = 0;
    /*
#ifdef OP_UI  //feeling 2004-05-14
    is_change_play_state=1;
    ircmd_display();
    if(!t_disp)
        ircmd_display();
    is_change_play_state=0;
#endif*/
}

//kenny mark it 891108, don't need again
//wanghaoying use it again 2003-10-31 16:51  for vtrek_dvd
#ifdef ONE_KEY_CONTRL_ECHO 
void  ircmd_echo(void) //zyf 891107
{

#ifdef SDRAM_16Mb_Mode
    invalid_key();
    return;
#endif

    static BYTE echo_flag=1;
    #ifdef IRCMD_DBG
    printf("echo:%d flag:%d\n",echo_level,echo_flag);
    #endif
    if ( echo_level == 8 )
        echo_flag = 0;
    else if(echo_level == 0)
        echo_flag = 1;
    
    if ( echo_flag == 1 )
        ircmd_echo_up();
    if ( echo_flag == 0 )
        ircmd_echo_down();

#if 0
    if(echo_flag==1)
    {
        echo_flag=0;

        PrintOsdMsg(STR_OS_ECHO_CNL,REGION2,1,0);

    }
    else
    {
        echo_flag=1;
        show_level(Echo_Font_ID,echo_level,16);
    }
#endif
}
#endif//#ifdef ONE_KEY_CONTRL_ECHO 

/*
** wanghaoying 2005-9-20 12:58
** Description:
** Use one ir-key to control mic volume
** default set volume up, and loop control
*/
#ifdef ONE_KEY_CONTRL_MIC
void  ircmd_mic(void) 
{

#ifdef SDRAM_16Mb_Mode
    invalid_key();
    return;
#endif

    static BYTE mic_flag=1;
    #ifdef IRCMD_DBG
    printf("mic:%d flag:%d\n",mic_level,mic_flag);
    #endif
    if ( mic_volume == 8 )
        mic_flag = 0;
    else if(mic_volume == 0)
        mic_flag = 1;
    
    if ( mic_flag == 1 )
        ircmd_mic_up();
    if ( mic_flag == 0 )
        ircmd_mic_down();
}
#endif//#ifdef ONE_KEY_CONTRL_MIC

#ifdef MIC_FUNCTION_KEY
void  ircmd_mic(void) //zyf 891107
{

#ifdef SDRAM_16Mb_Mode
    invalid_key();
    return;
#endif

#ifdef MIC_2CHANNEL 
    if(bFuncStep == 1)
    {

        bFuncStep = 5;
        show_level(Mic_Font_ID, setup_GetMICVol2()-2, 9);
    }
    else
    {
        bFuncStep = 1;
        show_level(Mic_Font_ID, setup_GetMICVol()-2, 9);
    }
#else//MIC_2CHANNEL
    bFuncStep = 1;
    show_level(Mic_Font_ID, mic_volume, 9);

#endif//MIC_2CHANNEL    

}
#endif

//Jeff 20020226
#ifdef USE_PT2257_ECHO_CONTROL    //dingzhy 2005-3-7 19:10
BYTE function_select,data_temp;
    
void  mcu_control_volume(BYTE control_id,int control_level)
{
      BYTE data1 = control_id;
      int  vol_check_level = control_level;
      BYTE data2 = 0xa0;
      BYTE data3;
      
      switch(vol_check_level)
      {
        case 0://-79 db     only echo       
            data3 = 0x37;             
            break;
        case 1://-30 db
            data3 = data1&0xf3;
            break;
        case 2://-20 db
            data3 = data1&0xf2;
            break;
        case 3://-16 db            
            data3 = data1&0xf6;
            break;
        case 4://-12 db            
            data3 = data1&0xf2;
            break;
        case 5://-8 db
            data3 = data1&0xf8;
            break;
        case 6://-4 db            
            data3 = data1&0xf4;            
            break;
        case 7://-2 db
            data3 = data1&0xf2;
            break;
        case 8://0 db
            data3 = data1&0xf0;
            break;
        default:
            break;
        }
        
      WriteToI2c(0x88, data2, &data3, 1);
}

void mcu_control_echo(int vol_echo)
{
    int mcu_echo_level=vol_echo;
     if(mcu_echo_level<=2)
        function_select = 0x3f;
    else if(2<mcu_echo_level&&mcu_echo_level<=4)  
    {
        data_temp=0x31;
        WriteToI2c(0x88, 0xa0, &data_temp, 1);
        function_select = 0x2f;
    }
    /*else if(echo_level==0)
    {
        data_temp=0x37;
        WriteToI2c(0x88, 0xa0,&data_temp, 1);
        return;
        }*/
    else
        function_select = 0x2f;
    mcu_control_volume(function_select, mcu_echo_level);//control mic echo   
}

void mcu_control_micvol(int vol_mic)
{
    int mcu_mic_volume = vol_mic;
    if(mcu_mic_volume<=2)
        function_select = 0xbf;
    else if(2<mcu_mic_volume&&mcu_mic_volume<=4)
    {
        data_temp=0xb1;
        WriteToI2c(0x88, 0xa0,&data_temp, 1);
        function_select = 0xaf;
    }
    else if(mcu_mic_volume==0)
    {
        data_temp=0xff;
        WriteToI2c(0x88, 0xa0,&data_temp, 1);
        return;
    } 
    else
        function_select = 0xaf;
    mcu_control_volume(function_select, mcu_mic_volume);//1 mean control mic volume
}
#endif//#ifdef USE_PT2257_ECHO_CONTROL

void ircmd_echo_up(void)
{
    
#ifdef SDRAM_16Mb_Mode
    invalid_key();
    return;
#endif

#ifdef GBM_MIC_FUNCTION
         bFuncStep = 2;
    show_level(Echo_Font_ID, echo_level, 9);
#else//GBM_MIC_FUNCTION 
    //echo_level : 0 ~ 8
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if (action_click || (PatternMode==Echo_Font_ID) )
#endif
        if (echo_level < 8)
            echo_level++;
    //setup_SetEcho(); 
        show_level(Echo_Font_ID, echo_level, 9);
#endif//GBM_MIC_FUNCTION

    setup_SetEcho();    //yaowh move here 04-12-03 because GBM_MIC_FUNCTION has be defined.
#ifdef USE_PT2257_ECHO_CONTROL   //dingzhy 2005-3-7 19:10
    mcu_control_echo(echo_level);
#endif
}

void ircmd_echo_down(void) //kenny 891107
{
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if (action_click || (PatternMode==Echo_Font_ID) )
#endif
        if (echo_level>0)
            echo_level--;

        show_level(Echo_Font_ID, echo_level, 9);
        setup_SetEcho();
#ifdef USE_PT2257_ECHO_CONTROL    //dingzhy 2005-3-7 19:10
    mcu_control_echo(echo_level);
#endif
}

void ircmd_mic_up(void)
{

#ifdef SDRAM_16Mb_Mode
    invalid_key();
    return;
#endif

#ifdef GBM_MIC_FUNCTION
#ifdef MIC_2CHANNEL
    ircmd_mic();
#else//MIC_2CHANNEL 
    bFuncStep = 1;
    show_level(Mic_Font_ID, mic_volume, 9);
#endif//MIC_2CHANNEL

#else//GBM_MIC_FUNCTION


#ifdef SUPPORT_UART_COMMAND // Robert 020729
    IRAdjustVol(1);
#else

    //mic_volume(0 ~ 8)
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if (action_click || (PatternMode==Mic_Font_ID) )
#endif
        if (mic_volume < 8)
            mic_volume++;

#ifdef FUSS_DVD
        if ( setup_IsMICOff() ) {
            setup_SetMICAuto();
        }
#endif

        show_level(Mic_Font_ID, mic_volume, 9);
        //setup_SetMic();
#endif // SUPPORT_UART_COMMAND
#endif//GBM_MIC_FUNCTION

    setup_SetMic();     //yaowh move here 04-12-03 because GBM_MIC_FUNCTION has be defined.
#ifdef USE_PT2257_ECHO_CONTROL     //dingzhy 2005-3-7 19:10
    mcu_control_micvol(mic_volume);
#endif
}

void ircmd_mic_down(void)
{
    
#ifdef SDRAM_16Mb_Mode
    invalid_key();
    return;
#endif

#ifdef SUPPORT_UART_COMMAND // Robert 020729
    IRAdjustVol(0);
#else

    //mic_volume(0 ~ 8)
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if (action_click || (PatternMode==Mic_Font_ID) )
#endif
        if (mic_volume>0)
            mic_volume--;

#ifdef FUSS_DVD //Jeff 20020524
        if ( setup_IsMICOff() ) {
            setup_SetMICAuto();
        }
#endif

        show_level(Mic_Font_ID, mic_volume, 9);
        setup_SetMic();
#endif // SUPPORT_UART_COMMAND

#ifdef USE_PT2257_ECHO_CONTROL    //dingzhy 2005-3-7 19:10
    mcu_control_micvol(mic_volume);
#endif
}

#ifdef VFD_DIMMING_CONTROL
extern BYTE dimming_level;
#define DIMMING_MAX     0x03
#define DIMMING_MIN     0x00

void ircmd_dimming(void)
{
    //wanghaoying 2005-9-20 15:18
    //dimming_flag to set wheather dimming_level up or down, increase or decrease.
    // now : 0 ---> decrease    1 ---> increase
    static BYTE dimming_flag = 0;
    
    if(dimming_level==DIMMING_MAX)
        dimming_flag = 0;
    else if(dimming_level==DIMMING_MIN)
        dimming_flag = 1;
    
    if(dimming_flag==1)
        ircmd_dimming_up();
    else if(dimming_flag==0)
        ircmd_dimming_down();
}
void ircmd_dimming_up(void)
{
    dimming_level++;
}
void ircmd_dimming_down(void)
{
    dimming_level--;
} 
#endif

#ifdef GBM_IRC_SHIELD_FUNCTION   //gerry,2004-1-30 19:19

UINT8 clickon_time=1;

void ircmd_shield_func(void)
{
       
switch(cd_type_loaded)
    {
    
    case CDDA:
        
        if(clickon_time)
         {
            tv_dacoff(0xff);
            clickon_time=0;
              }
        else 
         
         { 
           tv_dacoff( (0x01<<1)|(0x01<<2) );  // dac f/e/d//a on ,b,c off   
           clickon_time=1;
           
}
         break;
    case CDROM:
    case CDDVD: 
    case CDUNKNOWN:
        tv_dacoff( (0x01<<1)|(0x01<<2) );  // dac f/e/d//a on ,b,c off  
        
        break;
        
        
    default://vcd
        
        //tv_dacoff( (0x01<<1)|(0x01<<2) );  // dac f/e/d//a on ,b,c off    
        break;
        
    }
    
    
}
#endif




/*** zhyf 1-2-8 0:31 reset audio ***/
void reset_status(void)
{

#ifndef MUSTEK_K100D_MODEL//QiaoHuilin:2005-10-25:keep mute status when mode switch.
    user_mute=0;
#endif
    //audio_volume=15; //Jeff 20010904
    //audio_key =0;

    //  au_keyshift(audio_key); /*jhuang 2001/4/20 06:32PM*///reset key shift
    audio_effect=0;
    cd_type_loaded=0;
    //audio_channel=0;
    //full_scrn=0; /* alan 2002/6/11 09:22と to fix osd error when press SETUP as long as tray out */

    //if(de_mute==0)
    //   de_mute=1; //kenny add it, 891012 set de_mute flag, let continue() function work normal
    playmode_sel(CLEAR_ALL); //zhyf 1-3-2 22:51
}

void ResetAB(void)
{
    if(rep_ab_mode==REPEAT_FIND_B)
    {
        if(sys_cmd !=( CMD_FUNC|CMD_FUNC_REPAB) )
        {
            //printf("sys:%x\n",sys_cmd);
            ircmd_repeat_ab();
        } 
		else
        {
        if(!full_scrn) 
        show_repeatAB(0);   
    	}
    }
	else if(rep_ab_mode==REPEAT_FIND_A) 
    {           
#ifdef FF_FR_NOT_REPEATAB //terry,2004/1/19 02:48PM
        rep_ab_mode=REPEAT_AB_IDLE;
        show_repeatAB(1);
#else
        rep_ab_mode=REPEAT_FIND_B;
        ircmd_repeat_ab();
#endif  
    }
}


void ircmd_play_select()//IRC_PLAY_SELECT
{
#ifdef IRCMD_DBG
    printf("=================ircmd_play_select==================\n");
#endif
//  if((full_scrn>PROGRAM)||((full_scrn&PROGRAM)&&(is_clear_pos())))
    #if defined(MUSTEK_MULTI_FUNCTION_DIRECTION_KEY)
    if(((cd_type_loaded==CDROM)&&(pFsJpeg->ControlArea>=CNT_AREA_DIR))||((full_scrn != SCORE)&&(full_scrn != 0))||((full_scrn&PROGRAM)&&(is_clear_pos()))) //xyy 2003-11-18 14:27
    #else
    if(((full_scrn != SCORE)&&(full_scrn != 0))||((full_scrn&PROGRAM)&&(is_clear_pos()))) //xyy 2003-11-18 14:27
    #endif
    {
        #ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
        osd_tog_region(1,OSD_OFF);
        #endif
        //by justin 2005/11/23  press play when lcd show program , it will only miss the half of OSD of prog 
        #ifdef MUSTEK_K100D_MODEL
        if(full_scrn&PROGRAM)
	 {
	 	 ircmd_play();
		//prog_func_off();
		//OSD1000ISP_STATUS(OSDISP_PLAY, OSDIR_GLOBAL);
	    //   PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
	  }
        else
        #endif
        ircmd_select();
    }
#ifdef IR_PLAY_RESUME    
    else if((resumeMSF)&&(play_state==VCD_STATE_STOP)&&(!full_scrn))//&&(is_menu()==0))
    {
        ircmd_resume();
        return;
    }
#endif  
    else
    {
//      if (pFsJpeg->gifsState == FS_STATE_LIST)
//          ircmd_select();
//      else
#ifdef PLAY_PAUSE_SELECT_IN_ONE_KEY
    //    if((pFsJpeg->file_will == pFsJpeg->fsnav_trk_now)
     if((pFsJpeg->file_will == pFsJpeg->fsnav_trk_now-pFsJpeg->file_page_now*10)
            || (pFsJpeg->gbfsSlide != 0))
            ircmd_play_pause();
        else
    
#endif

            ircmd_play();
    }
}


void ircmd_score()
{
#ifdef SUPPORT_SCORE
    // alan, 2003/9/8 11:31と
    #ifdef SUPPORT_FILE_SYSTEM_MODE    //nono 3-6-24 16:41
    if ( Is_OTHER_STATE() ) {
        invalid_key();
        return;
    }
    #endif

#ifdef SUPPORT_DVD_SCORE
    //if(1) //wsf add for eastech_score_funtion  support dvd score  wsf  2005-6-2 16:13
    if((cd_type_loaded==CDVCD10)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD)||(cd_type_loaded==CDDVD)||((cd_type_loaded==CDDA)&&(CDG_IsCDGNow())))//libing add for cdg score//nono modify 20050721
#else
    if (coding_mode_now&(AUDIF_CODING_MODE_MP2|AUDIF_CODING_MODE_MP3|AUDIF_CODING_MODE_AC3))    //Jeff 20020518
#endif
    {
        if (full_scrn!=SCORE) {
            full_scrn = SCORE;
            osd_init();
            Score_Init();
            //libing 2005-8-2 20:31 add.  
            #ifdef SCORE_IN_PLAYMODE_MENU
            SetFullscrnCmdFuncPtr(ircmd_null, ircmd_null,  ircmd_null,
            ircmd_null, ircmd_null);
            score_flag = 1;                         
            #endif                     
        } else {
        	#ifdef SCORE_IN_PLAYMODE_MENU
        	score_flag = 0;
        	#endif
            full_scrn = 0;
            osd_init();
            //                Score_Exit();
        }
    } else {
        invalid_key();
    }
    if(play_state >= VCD_STATE_FASTFORWARD && play_state <= VCD_STATE_SLOW)  //xyy 2003-11-19 9:21
        chg2normal_play(FAST2NORM|PAUSE2NORM|SLOW2NORM,REALPLAY);
#endif//SUPPORT_SCORE
}

// move from prog.c
/*
 *  Description:
 *   return a flag .
 *   if get next prog item correctly, return TRUE, else return FALSE;
 *
 *   zhaoyanhua 2004-5-10 17:44
 */
BYTE prog_next(void)
{
    BYTE  change_flag = TRUE;

    if (prog_cnt) 
    {
#ifdef VALID_PROGROM_REPEAT
    //change the prog_next() function for any type disc use in prog/repeat mode.
    BYTE    repeat_flag1=0;
    BYTE    repeat_flag2=0;
    if(cd_type_loaded==CDDVD)// wuxiaofeng 02-26  judge the disc type and give the different value
    {
        repeat_flag1=(rep_mode == REPEAT_DISC)?1:0;
        repeat_flag2=((rep_mode == REPEAT_DVDDISC)||(rep_mode==REPEAT_IDLE))?1:0;
    }
    else if(cd_type_loaded==CDROM)
    {
        repeat_flag1=(rep_mode == REPEAT_DIRECTORY)?1:0;
        repeat_flag2=((rep_mode == REPEAT_DISC)||(rep_mode==REPEAT_IDLE))?1:0;
    }
    else if((cd_type_loaded==CDDA)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))
    {
        repeat_flag1=0;
        repeat_flag2=((rep_mode == REPEAT_DISC)||(rep_mode==REPEAT_IDLE))?1:0;
    }
    else
    {
        repeat_flag1=0;
        repeat_flag2=1;
    }
    
        if(repeat_flag1)//alex 20040224
        {   
            BYTE search_index;
            BYTE    loop_time;
            search_index=prog_index;
            for(loop_time=0;loop_time<SHOW_PROG_NO;loop_time++)
            {
                search_index++;
                if(search_index>(prog_cnt+1))
                    search_index=1;
                if(prog[prog_index][0]==prog[search_index][0])
                {
                    prog_index=search_index;
                    break;
                }
            }
        }                                                                   //alex 20040224
        else if (repeat_flag2)
        {
            prog_index++;

            //if( (prog_index > prog_cnt)&&(rep_mode==REPEAT_IDLE))
            if(prog_index > prog_cnt)//2004-6-2 23:03
            {
                prog_index = 1;
                
                //wanghaoying modified 2004-6-3 12:18
                //S:某客户要求在编程项目播放完后停止。
        #ifdef STOP_IN_PROG_END//wuxiaofeng 2004-03-16
                if(rep_mode==REPEAT_IDLE)
            {
                if(cd_type_loaded!=CDDVD)//DVD disc will clear the values in its flow
                    prog_index=prog_cnt=0;//wuxiaofeng modified 2004-03-16
#ifdef ALCO_DVD_UI
                else
                    prog_index = 0;
#endif
                #ifdef SDRAM_16Mb_Mode 
                    resumeMSF=0;  //zhuyanfeng 2004/11/10  //to avoid the bug that program end in pre stop state when program repeat off pressing next key  
                    #endif
                sys_cmd=(CMD_FUNC | CMD_FUNC_STOP);
            }
        #endif//#ifdef STOP_IN_PROG_END
        }
  }
#else
        prog_index = (prog_index>=prog_cnt) ?  1 :(prog_index+1);
#endif
    }
    return change_flag;
}

/*
 *  Description:
 *   return a flag .
 *   if get prev prog item correctly, return TRUE, else return FALSE;
 *
 *  zhaoyanhua 2004-5-10 17:44
 */
BYTE prog_prev(void)
{
    BYTE change_flag = TRUE;
    
    if (prog_cnt) {
#ifdef VALID_PROGROM_REPEAT
        //change the prog_prev() function for any type disc use in prog/repeat mode.
        BYTE    repeat_flag1=0;
        BYTE    repeat_flag2=0;
        if(cd_type_loaded==CDDVD)// wuxiaofeng 02-26  judge the disc type and give the different value
        {
            repeat_flag1=(rep_mode == REPEAT_DISC)?1:0;
            repeat_flag2=((rep_mode == REPEAT_DVDDISC)||(rep_mode==REPEAT_IDLE))?1:0;
        }
        else if(cd_type_loaded==CDROM)
        {
            repeat_flag1=(rep_mode == REPEAT_DIRECTORY)?1:0;
            repeat_flag2=((rep_mode == REPEAT_DISC)||(rep_mode==REPEAT_IDLE))?1:0;
        }
        else if((cd_type_loaded==CDDA)||(cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD))
        {
            repeat_flag1=0;
            repeat_flag2=((rep_mode == REPEAT_DISC)||(rep_mode==REPEAT_IDLE))?1:0;
        }
        else
        {
            repeat_flag1=0;
            repeat_flag2=1;
        }

        if( repeat_flag1)//alex 20040224
        {   
            BYTE search_index;
            BYTE    loop_time;
            search_index=prog_index;
            for(loop_time=0;loop_time<SHOW_PROG_NO;loop_time++)
            {
                if(search_index<=1)
                    search_index=prog_cnt;
                else
                    search_index--; 
                if(prog[prog_index][0]==prog[search_index][0])
                {
                    prog_index=search_index;
                    break;
                }
            }
        }                                                                   //alex 20040224
        else if (repeat_flag2)
        {
            #ifdef BACK_SKIP_PREV
            if((cd_type_loaded!=CDDVD) && (play_state==VCD_STATE_NORMAL))
            {
          
                #ifdef REMAIN_TIME
                if((!remain) && (disp_time>BACK_SKIP_TIME))
                #else
                if(disp_time>BACK_SKIP_TIME)
                #endif
                    prog_index++;  
                    
            }
            #endif
            
            #ifdef AFTER_P5SECONDS_PREV_2TRACK_START
            if((cd_type_loaded!=CDDVD) && (play_state==VCD_STATE_NORMAL))
            {
          
                #ifdef REMAIN_TIME
                if((!remain) && (disp_time>5))
                #else
                if(disp_time>5)
                #endif
                    prog_index++;  
                    
            }
            #endif
            
            prog_index--;

            //if ((prog_index < 1)&&(rep_mode==REPEAT_IDLE))
            if (prog_index < 1)//2004-6-2 23:02
            {
                #ifdef CD_VCD_FB_ONETIME_IN_PROGRAM     //linrc 2004-8-9 18:59
                //when FB to first program song,stop FB and replay progam
                if((rep_mode==REPEAT_DVDDISC) || (rep_mode==REPEAT_DISC))
                    prog_index = prog_cnt;
                else
                prog_index = 1;
                    
                if(!rep_mode && (play_state==VCD_STATE_FASTBACKWARD))//added rep_mode 04/12/09
                {
                    play_state = VCD_STATE_NORMAL;
                    adv_search_time = 0;
                    PrintOsdMsg(STR_OS_PLAY,REGION1,1,0);
                }
                #else
                prog_index = prog_cnt;
                
                //wanghaoying modified 2004-6-3 12:18
                //S:某客户要求在编程项目播放完后停止。
        #ifdef STOP_IN_PROG_END//wuxiaofeng 2004-03-16
                if (rep_mode==REPEAT_IDLE)
            {
                if(cd_type_loaded!=CDDVD)//DVD disc will clear the values in its flow
                    {                 
                    prog_index=prog_cnt=0;//wuxiaofeng modified 2004-03-16
#ifdef ALCO_DVD_UI
                resumeMSF = 0; //Jack added 04/11/04!!!
#endif
                sys_cmd=(CMD_FUNC | CMD_FUNC_STOP);
#ifdef ALCO_DVD_UI
                PrintOsdMsg(STR_OS_STOP,REGION1,1,0);
#endif
            }
                }
        #endif//#ifdef STOP_IN_PROG_END
                #endif//#endif CD_VCD_FB_ONETIME_IN_PROGRAM
           }
        }
#else//#ifdef VALID_PROGROM_REPEAT
        #ifdef BACK_SKIP_PREV
        if((cd_type_loaded!=CDDVD) && (play_state==VCD_STATE_NORMAL))
        {
        
            #ifdef REMAIN_TIME
            if((!remain) && (disp_time>BACK_SKIP_TIME))
            #else
            if(disp_time>BACK_SKIP_TIME)
            #endif
                prog_index++;  
                
        }
        #endif
        prog_index = ((prog_index>1) ? prog_index-1:prog_cnt);
#endif//#ifdef VALID_PROGROM_REPEAT
    }
    return change_flag;
}


void ircmd_exit_setup()//nono 20021015
{
#ifdef OP_UI//zhaoyanhua add 2004-4-13 14:19
    //system_state = SYSTEM_SETTING;
    
    if(full_scrn & PROGRAM)
    {
        full_scrn = SETUP;
        prog_func_off();
    }    
#endif//ifdef OP_UI    
#if 0
    if((full_scrn&SETUP) || (full_scrn&CUSTM)) //////////////////////////jhuang
    {
        ExitSetupPage(1);
        //xiaosan 2-7-19 13:42//for huajia
#if defined(DOUBLE_LOGO)||defined(NEW_STYLE_SETUP)
        if(play_state==VCD_STATE_STOP||system_state==SYSTEM_NODISC||system_state==SYSTEM_OPEN)
            ShowTitle();
#endif
//        printf("exit setup menu\n");
    }else
    {
        invalid_key();
//        printf("ir setup ,invalid\n");
        return;
    }
#endif//#if 0
}

void ircmd_default_setup(void)
{
#ifdef SUPPORT_MIDI_MENU_SEL   //ouyang add for midi 2004-10-20 16:25
        if (Is_MIDI_STATE())
        {
        invalid_key();
        return;
        }
#endif

#ifdef SETUP_DEFAULT_USE_IR_CRT
    int id;

    //extern UINT8 setup_sel[7][8];
//  #ifdef USER_MPEG_LOGO
//  extern UINT8 setup_sel[7][8];
//        #endif

    
    AUDIF_Set_Pause();//2004AUDDRV AudioSetPause(); //nono 3-12-22 23:25
    
    set_default_value();
    run_set_variable();
#if !defined(DISC_ID_IN_FLASH)&&!defined(SUPPORT_SPI_FLASH)
    run_save_total_sel();
    
    //3-12-23 21:02 NONO for dts-cd
    setup_SetDTSDOWNMIXConfig();
    
    ExitSetupPage(1);   //nono 3-12-17 19:37for tv type can't be set default value.
#endif//!defined(DISC_ID_IN_FLASH)&&!defined(SUPPORT_SPI_FLASH)

#ifdef USER_MPEG_LOGO   // alan, 2003/9/23 10:16AM
//  exe_setup_function(STR_OS_SELECT_LOGO,STR_OS_RESTORE_SETUP,0); 
//  setup_sel[7][2]=2;

#ifdef YUXING_MIDI_DVD  
     setup_SetDefaultLogo();   //nono 2004-10-28 14:34
#else
    setup_SetMPEGLogo();//nono 2004-2-20 0:31
#endif

    if (
           (play_state==VCD_STATE_STOP) || 
           (play_state==VCD_STATE_OPEN) || (system_state==SYSTEM_NODISC)
       )
    {
        ShowTitle();
    }
#endif

    id = STR_OS_DEFAULT_SETUP;
    PrintOsdMsg(id,REGION1,1,0);

    AUDIF_Set_Play();//2004AUDDRV AudioSetPlay();//nono 3-12-22 23:25
#endif//SETUP_DEFAULT_USE_IR_CRT
}

void ircmd_mix_func(void)
{
    
#ifdef SDRAM_16Mb_Mode
    invalid_key();
    return;
#endif

#ifdef MIC_FUNCTION_KEY 
#ifndef BBK_DVD//zhaoyanhua 03-10-19 13:50  
    if (action_click)
        bFuncStep++;
#ifdef NO_MIC_VOL
    if(bFuncStep==1)
        bFuncStep++;
#elif defined(NO_MIC)           //gerry for PANDA_DVD,3-8-23 21:30              
    if(bFuncStep==1)
        bFuncStep=bFuncStep+2;
#endif      
    if (bFuncStep > 3)
        bFuncStep = 0;
#else//if defined BBK_DVD
        
    bFuncStep++;
    printf("bFunctionStep = %d--\n",bFuncStep);     
    
    if (bFuncStep > 3)
        bFuncStep = 1;  
#endif//end ifndef BBK_DVD
    
    switch (bFuncStep)
    {
#ifndef BBK_DVD
    case 0:
        show_level(Volume_Font_ID,audio_volume,16);
        return; 
#endif//end BBK_DVD
    case 1:
        show_level(Mic_Font_ID, mic_volume, 9);
        return;

    case 2:
        show_level(Echo_Font_ID, echo_level, 9);
        return;
    default://KEY
//printf("======================##################mix_function--------\n");
#ifdef  OFF_5_1_CH_WHEN_TURN_KEY
    //if playing DTS or PROLOGIC II ,then turn off PL2, set the audio default value
    //zhaoyanhua 2003-12-1 16:39    
    if(((cd_type_loaded == CDDA) && (cd_subtype == CD_DTS)) //CD_DTS
      ||((cd_type_loaded == CDDVD) && (coding_mode_now == AUDIF_CODING_MODE_DTS))//DVD_DTS
#ifdef SUPPORT_PROLOGIC_II  //axel 2004/01/28 
      || (setup_GetPrologicII() < 4 )//PROGIC II not off
#endif
      )
    {
        audio_key = 0;      
    }
    
    if(setup_IsSpkDownmixOff())//if turn KEY in 5.1CH, must change to stereo zhaoyanhua note 2003-12-11 14:25
    {
       // printf("############### KEY-----------\n");
        AudioSet2chOutput();    
    }
#endif    
    
        show_level(AudKey_Font_ID,audio_key, 13);
        return;
    }
#endif  
}


//freyman 2002-7-27 15:26
#include "ircmd_amp.c"  //terry,2004/1/26 01:38PM

#ifdef VIRTUAL_KEYBOARD // alan, 2003/8/16 05:02AM
void ircmd_virtual_keyboard(void)
{   
#ifdef NEWSTYLE_WINDOW  // alan, 3-8-22 18:44
    if (full_scrn & MESSAGE)
    {
        invalid_key();
        return;
    }
#endif
    if (full_scrn & KEYBOARD)
    {
        full_scrn &= (~KEYBOARD);
        #ifdef CD_PLAYER        //liweihua 2003-9-3
        if(cd_type_loaded==CDDA)
        {
            osd_init_cdplayer();
        }else               
            osd_init();
        #else   
        #ifdef  NINTAUS_DVD     //Maoyong 2004.02.25 for avoid interference on screen       
        osd_tog_region(3,OSD_OFF);
        delay_1ms(2);
        #endif       
        osd_init();
        #endif
    }
    else
    {
        if((full_scrn & MARK)||(full_scrn & GOTO))//liweihua mod 20031124
        {
            invalid_key();
            return;
        }
        full_scrn |= KEYBOARD;
        #ifdef CD_PLAYER        //liweihua 2003-9-3
        if(cd_type_loaded==CDDA)
        {
            show_cdplayer();
            osd_draw_virtual_keyboard(0,0,4);   
            hl_keyboard_button(0);
        }else
        #endif
        show_virtual_keyboard();
        //Maoyong added for IR U/D/L/R/Sel proc func setting 2004-9-24 9:23
        //WSLEE add up and down function pointer for new virtual keyboard 20050518 20:00
        SetFullscrnCmdFuncPtr(virtual_keyboard_up, virtual_keyboard_down, virtual_keyboard_left,
                              virtual_keyboard_right, virtual_keyboard_select);
    }
}
#endif

#ifdef KeyLockStatus_for_TONIC
const char *const KeyLockString[4][10]=
{
    {"KEY LOCK ON",
    "KEY LOCK OFF",},
    {"TASTENSPERRE EIN",
    "TASTENSPERRE AUS",},
    {"ACTIVAR CLAVE BIOQUEO",
    "DESACTIVAR CLAVE BIOQUEO",},
    {"CL\xc9 SERRURE OUI",
    "CL\xc9 SERRURE NON",}
};
void ircmd_keylock(void)
{   
    #ifdef DISABLE_KEYLOCK_AT_PREVIEW
    if(play_state==VCD_STATE_PREVIEW||play_state==VCD_STATE_9FRAMES)
    {
        invalid_key();
        return;
    }
    #endif
    if(KeyLockStatus==0)
    {
        psprintf(RegionValStr[REGION1],KeyLockString[osd_font_mode][0]);
        PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
        KeyLockStatus=1;
        WriteToI2c(0xa0,ADDR_I2C_TRAY_PWD,&KeyLockStatus,1);//nono change 0xff->macro 20050812
    }
    else
    {
        psprintf(RegionValStr[REGION1],KeyLockString[osd_font_mode][1]);
        PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
        KeyLockStatus=0;
        WriteToI2c(0xa0,ADDR_I2C_TRAY_PWD,&KeyLockStatus,1);//nono change 0xff->macro 20050812
    }
}
#endif  // KeyLockStatus_for_TONIC

#ifdef SUPPORT_RECEIVER  //huziqin 2004-2-26
/*huziqin 2004-4-29.I move this block to the new files*/
  #include "ircmd_receiver.c"
#endif

#ifdef SUPPORT_RECEIVER//xyy 2004-8-15
#if defined(BASS_ADJUST_KEY)
//xulf 2004-3-7
void  ircmd_rcvr_bass(void)
{
    subvol_next_channel();  
}
#endif

#if defined(TREBLE_ADJUST_KEY)
void  ircmd_rcvr_treble(void)
{
    invalid_key();//xyy 2004-5-26
//  ddx_OSDTrebleAdjust();          
}
#endif

#if defined(EQ_SWITCH_KEY)
void ircmd_rcvr_EQ(void)
{
    AmpEqToggle();
    return;
}
#endif

#if defined(BAND_SWITCH_KEY)
void  ircmd_rcvr_band(void)
{
    invalid_key();
    return;
}
#endif
#endif  //SUPPORT_RECEIVER

#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
#include "ircmd_card.c"     //Maoyong 2004.05.19
#endif

#ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-5-13 13:20
#include "ircmd_switch_media.c"
#endif//DIRECT_ACCESS_MEDIA

#if defined(FAT_Write_UI) || defined(FILE_MODE_WRITE)
#include "ircmd_media_control.c" //sunzhh 2004-10-18 17:46
#endif

#ifdef SUPPORT_SPI_QSI//SH
#include "spi_cmd.c"
#endif

#ifdef IR_IRCMD_JUMP_30SEC  //wangwei 2004-7-20 22:30
void ircmd_jump_30sec(void)
{ 
    tm2hms(disp_time,&goto_hour,&goto_min,&goto_sec); 
    goto_sec  = goto_sec+30; 
    goto_time=(goto_hour*3600+goto_min*60+goto_sec); 
    goto_time = goto_time+ dPg_tm;
    exe_timesearch_func(0,0); 
    return; 
} 
#endif

/*******************************************************************\
added by wangwei,2004-10-5 11:25
note:press a key to switch the second subtitle(IRC_SW_2ND_SUBTITLE).
->twoSubTTFlag:
=0:the 2nd subtitle is closed.
=1:2nd subtitle == 1st subtitle.
=2:the 2nd subtitle is open.
IDTWO:0-CH1,1-CH2.......MAX-OFF.
\*******************************************************************/
#ifdef TWO_KEY_SWITCH_TWO_SUBTITLE
void ircmd_switch_2nd_subtitle(void)
{
    if(pDSV->dAv_SPST_Ns>1)
    {
        //printf("pDSV->dAv_SPST_Ns:%x\n",pDSV->dAv_SPST_Ns);
        if(IDTWO!=-1)
            IDTWO=IDTWO&0x3F;
        if(NP_SPSTN!=0xffbf)  //can't switch the second subtitle when main subtitle off.
        {    
            if(action_click)
            { 
                IDTWO++;
                //printf("[IDTWO]:%x\n",IDTWO);
                if(IDTWO==(NP_SPSTN&0x3f))  //same to the 1st one.
                {
                    sup_select_subtitles(1); 
                    twoSubTTFlag=1;
                }
                else if(IDTWO>=pDSV->dAv_SPST_Ns)  //close the 2nd subtitle.
                {
                    sup_select_subtitles(1);
                    twoSubTTFlag=0;
                    IDTWO=-1;
                }
                else
        {
            sup_select_subtitles(2);
                    twoSubTTFlag=2;
                }
        }
            if(IDTWO==-1)
        {    
                psprintf(RegionValStr[REGION1], "SECOND SUBTITLE:   [OFF]");
            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        }
        else
        {
                psprintf(RegionValStr[REGION1], "SECOND SUBTITLE:   [%d]",IDTWO+1);
                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        }
            if(twoSubTTFlag!=0)//=2)
        {
                sup_select_channel_2(IDTWO+0x20);
        }
    }
    else
    {
            invalid_key();
            return;
        }
    }
    else  //if(pDSV->dAv_SPST_Ns>1)
    {
        sup_select_subtitles(1);
        psprintf(RegionValStr[REGION1], "ONLY ONE SUBTITLE");
        PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
    }
}
#endif  //TWO_KEY_SWITCH_TWO_SUBTITLE

//=========================================
//for QSI disc/card switch  //added by JS   //20040726
#ifdef SUPPORT_QSI_SOURCE_SWITCH
void ircmd_source_switch(void)
{
    printf("\n=====     ircmd_source_switch     =====\n");

    source_switch_flag = 1;
    source_type_old = source_type_now;
    
    if(t_disp != 0)
    {
        ircmd_display();
    }   

#ifndef QSI_PLATFORM
    if(source_type_now == source_disc)
#else
    if(source_type_now == source_card)
#endif      
    {
        source_type_now = source_card;

        ircmd_stop();
        abort_play();

        printf("\t\tdisc  >>>>> card\n");
#ifndef QSI_PLATFORM
    }else if (source_type_now == source_card) 
#else
    }else if (source_type_now == source_disc) 
#endif  
    {
        source_type_now = source_disc;

        ircmd_stop();

        printf("\t\tcard  >>>>> disc\n");
    }

    if(system_state != SYSTEM_STOP)
    {
        system_state = SYSTEM_STOP;
    }

    printf("===>>>card switch test \n\n");
    return;     
}
#endif



#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-12
#include "clock_func.h"
void ircmd_set_clock(void)
{
    uRtcState = RTC_INPUT;
    timeout_vfd = 10000;
    vfd_set_str(0,0,0,"0000  ");
    return;
}
#endif

#if 0//def SUPPORT_MIDI_MENU_SEL //ouyang add 2005.07.04 please add for future  
void ircmd_mscore_switch(void)
{

    if(gIsMidiSelMenu)  
    { 
        #ifdef SUPPORT_SCORESW  
        if (MenuState < MENU_MULTI_INDEX_SEL)
        {
            extern BYTE * gc_pucSWStr[][2];
            extern BYTE current_midi_osd_lang;
            bIsSJScoreInvaild ^= 1;//set score sw
            psprintf(RegionValStr[REGION1]," [%s]",
            gc_pucSWStr[current_midi_osd_lang][bIsSJScoreInvaild]);        
            PrintOsdMsg(STR_OS_SCORE,REGION1,1,0);
        }
        #endif//SUPPORT_SCORESW
    return;
    }                   
}
#endif
#ifdef SANJING_MIDI_DVD   //ouyang add for Melody 2004-11-08
int MelodySwitch=1;

void ircmd_main_melody(void)
{
extern BYTE bChorus;   
#ifdef SUPPORT_SANJING_LYRIC_SPEC            //ouyang 2004.07.31
        if (bIsSanJingMidi){
            if(bChorus){
                if(MelodySwitch){ //melody is on channel 2nd
                                                    
                    AUDIF_Set_OutputMode(0x0d, 0);  //ouyang change 05-01-27
                    PrintOsdMsg(STR_OS_MELODY_ON, REGION1, 1, 0);
                    MelodySwitch=0;
                }
                else{  //melody is on channel 1st
                    AUDIF_Set_OutputMode(0x0b, 0);//(0x0a, 0);
                     //AudioSetOutputMode(0x0d, 0);
                    PrintOsdMsg(STR_OS_MELODY_OFF, REGION1, 1, 0);
                    MelodySwitch=1;
                }//end of if(bChorus)
            }
            else{//else of if(MelodySwitch)
                if(MelodySwitch){ //melody is on channel 2nd
                    AUDIF_Set_OutputMode(0x0d, 0);
                    PrintOsdMsg(STR_OS_MELODY_ON, REGION1, 1, 0);
                    MelodySwitch=0;
                }
                else{  //melody is on channel 1st
                    AUDIF_Set_OutputMode(0x0b, 0);
                    PrintOsdMsg(STR_OS_MELODY_OFF, REGION1, 1, 0);
                    MelodySwitch=1;
                }//end of if(bChorus)
            }//end of if(MelodySwitch)

        
        }else
#endif   // #ifdef SUPPORT_SANJING_LYRIC_SPEC 
        {
    if(MelodySwitch){
                AUDIF_Set_OutputMode(0x0e, 0);
        PrintOsdMsg(STR_OS_MELODY_ON, REGION1, 1, 0);
        MelodySwitch=0;
    }
    else{
                AUDIF_Set_OutputMode(0x0f, 0);
        MelodySwitch=1;
        PrintOsdMsg(STR_OS_MELODY_OFF, REGION1, 1, 0);
            }

    }
}
#endif//#ifdef SANJING_MIDI_DVD 

#if defined(DVB1000_NON_OS)||defined(SUPPORT_8202_DVB)
void ircmd_dvb_dvd(void)
{
    DvbDvdSwitch();
    return;
}

void ircmd_tv_radio(void)
{
    printf("================ ircmd_tv_radio ====================\n");
    //TV_RADIO_Switch();
    return;
}    
#endif

#ifdef HONEYWLD_DVD
void ircmd_dma_dvd(void)
{
    //psprintf(RegionValStr[1], "DMA");
    //PrintOsdMsg(72, 1, 0, 1);
    
    return;
}

void ircmd_dvd_invalid(void)
{
    invalid_key();
    return;
}
#endif

#ifdef FILE_MODE_WRITE//added by wangwei,2005-1-10 13:15
extern void FileModeMainLoop(void);
extern void Draw_FileMode_Menu(void);
extern BYTE last_access_media;
extern FSJPEGDATA  *pFsJpeg_des_buf; 

void ircmd_file_mode_write(void)//frank.huang 050831
{
	file_mode_flag=1;
	ircmd_post_func(CMD_FUNC | CMD_FUNC_FILE_MODE);
	return;
}

void file_mode_write(void)
{
    //sunzhh add for pressing this key when playing jpeg or mpeg 2005-2-19
    if ((pFsJpeg->gbfsSlide)&& (pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG))    
    {  
        FSChangeGraphMode();                     
    }  
#if defined(SUPPORT_FILE_SYSTEM_MODE)||defined(SUPPORT_MP4)
    else if(IsOtherStatePlayMode())
    {   
        adv_search_time = 0;
        video_slow = 0;
    
        #ifdef SUPPORT_MP4
        if( ( GetCurrentFileType() != CDROM_MP4 ) || ( !FILE_UNSUPPORT_VIDEO() ) )
        #endif
        {
   		#ifdef MEM_GRAPH_LARGE //2006-06-02, mimitsai add for HD ui.
            config_memory(MEMORY_GRAPH_NTSC);
            set_disbuf_now(0);
        #else
            config_memory(MEMORY_GRAPH_SMALL);
        #endif
        
            setup_tv_format(tv_format);  
        }   
    }                       
#endif 
                     
    AVD_SetMediaTimeout();
    play_state = VCD_STATE_CLOSE;   
    full_scrn = 0;     
    ClearOsdMsg(0);     
    t_disp = 0; 
    osd_init();              
    system_state = SYSTEM_OPEN;
    
    pFsJpeg = pFsJpeg_des_buf;
    memset(pFsJpeg, 0, sizeof(FSJPEGDATA));
    pFsJpeg->gifsState = FS_STATE_MEDIA;
    pFsJpeg = &(share_data.JPEG);
    memset(pFsJpeg, 0, sizeof(FSJPEGDATA));  
    pFsJpeg->gifsState = FS_STATE_MEDIA;

    //draw filemode GUI,added by sunzhh,2005-1-8 14:20
    Draw_FileMode_Menu();
    
    last_access_media = media_type;
    
    //to get key code & call related functions,added by wangwei,2005-1-7 10:11
    FileModeMainLoop();
}
#endif

//=========================================
#ifdef PMP_UI//liweihua 2004-12-26 15:39
#include "pmpkey.c"
#endif


#ifdef DIVX_DRM
// DRM memory
// Use 48-bytes non-volatile memory
// NOTE: the initial values after manufactured must be all zeros.

int get_drm_mem(BYTE* buf, int offset, int length)
{
    if(ReadFromI2c(0xa0, (256-DRM_MEMORY_SIZE)+offset, buf, length) >= 0)
    {
        return 1;   // success
    }
    else
    {
        return 0;   // fail
    }
}

int save_drm_mem(BYTE* buf, int offset, int length)
{
    if(WriteToI2c(0xa0, (256-DRM_MEMORY_SIZE)+offset, buf, length) >= 0)
    {
        return 1;   // success
    }
    else
    {
        return 0;   // fail
    }
}
#endif  // DIVX_DRM



#ifdef DISPLAY_INDIVIDUAL_SPK_VOLUME//2005-4-19 10:23 zhoulin

#define M_AMPVOL_SHOWREGION   1

void show_channel_msg(UINT16 uChannelNm,UINT16 uChannellevel)
{   
    
    coordinate start;
    start.x = 125;
    start.y = 0;  
    UINT32 j;
    const char *channel_str[]={" ",STR_OS_VOL,STR_OS_VOL_L,STR_OS_VOL_R,STR_OS_VOL_SL,STR_OS_VOL_SR,STR_OS_VOL_CT,STR_OS_VOL_SW,STR_OS_BASS,STR_OS_TREMBLE};//VOL,STR_OS_VOL,STR_OS_VOL,STR_OS_VOL,STR_OS_VOL,STR_OS_VOL,STR_OS_VOL,STR_OS_VOL,STR_OS_VOL};
    RegionValStr[M_AMPVOL_SHOWREGION][0]='\0';
    //char space1[]="                  ";
    //psprintf(RegionValStr[M_AMPVOL_SHOWREGION], "%s",space1);
    switch(uChannelNm)
    {
        
     case 1:
        PrintOsdMsg(channel_str[1], M_AMPVOL_SHOWREGION, 2, 1);
        psprintf(linebuf,"[                    ]%2d",uChannellevel);    
        osd_draw_string(&start, linebuf, 3, 0, 1, 0);
        for(j=0;j<uChannellevel;j++)
        {
            osd_draw_vertical_line(144+8*j,1,23,3,3,1);
            //osd_draw_horizontal_line(139+8*j,139+9*j+5,0,3,5,1);
        }
        
        for(;j<40;j++)
        {
            osd_draw_vertical_line(144+8*j,11,23,3,3,1);
        }
        
      //  ircmd_volume_up();
        break;
     case 2:
     case 3:
     case 4:
     case 5:
     case 6:
     case 7:
        PrintOsdMsg(channel_str[uChannelNm], M_AMPVOL_SHOWREGION, 2, 1);
        psprintf(linebuf,"[            ]%2d",uChannellevel-12);    
        osd_draw_string(&start, linebuf, 3, 0, 1, 0);
        for(j=0;j<25;j++)
        {
            osd_draw_vertical_line(142+8*j,11,23,3,2,1);
        }
        if((uChannellevel-12)>=0)
        {
            for(j=12;j<=uChannellevel;j++)
            {
                osd_draw_vertical_line(142+8*j,1,23,3,2,1);
            }
        }
        else
        {
            for(j=uChannellevel;j<=12;j++) 
            {
                osd_draw_vertical_line(142+8*j,1,23,3,2,1);
            }
        }
        
        break;
     case 8:
     case 9:
       
        PrintOsdMsg(channel_str[uChannelNm], M_AMPVOL_SHOWREGION, 2, 1);
        psprintf(linebuf,"[      ]%2d",(uChannellevel-7)*2);    
        osd_draw_string(&start, linebuf, 3, 0, 1, 0);
        for(j=0;j<13;j++)
        {
            osd_draw_vertical_line(142+8*j,1,23,3,2,1);
        }
     
        if((uChannellevel-7)>=0)
        {
            for(j=6;j<=(uChannellevel-1);j++) 
            {
                osd_draw_vertical_line(142+8*j,1,23,3,2,1);
            }
        }
        else
        {
            for(j=(uChannellevel-1);j<=6;j++) 
            {
                osd_draw_vertical_line(142+8*j,1,23,3,2,1);
            }
        }
     
        break;
     
     
     default:
        
        break;
           
    }

}
#endif//#ifdef DISPLAY_INDIVIDUAL_SPK_VOLUME


#ifdef MUTE_DEMUTE_HAVE_TWE_VALUE_IN_ONE_KEY
void ircmd_indiv_MUTE(void)
{
    

    
        user_mute=1;
        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);

/*#ifdef MUTE_EXECUTE_MIC //NONO 4-1-5 12:09
       
        AUDIF_Set_MICVol(0);//2004AUDDRV AudioSetMICVol(0);
#ifdef  MIC_2CHANNEL
        AUDIF_Set_MICVol2(0);//2004AUDDRV AudioSetMICVol_2(0);
#endif//#ifdef  MIC_2CHANNEL
#endif//#ifdef MUTE_EXECUTE_MIC
*/
        //terry,2001/1/10 09:32PM,avoid stop->play ,show mute's postion error
        PrintOsdMsg(STR_OS_MUTE,REGION1,0,0);

        OSD1000ISP_STATUS(OSDISP_MUTE, OSDIR_MUTE);
     


}

void ircmd_indiv_DEMUTE(void)
{


        user_mute=0;
        //Jeff 20020521
        //AudioDemute();
/*#ifdef MP3_CD_FF1_BF1_MUTE//YX822BC//nono 2-8-23 15:41
        if(!adv_search_time)
            AUDIF_Demute();//2004AUDDRV AudioDemute();
#else*/
        if (adv_search_time>0) {
            if (adv_search_time<=2)
            {
               AUDIF_Demute();//2004AUDDRV  AudioDemute();
            }
        } else {
            if (adv_search_time>=(-2))
            {
                AUDIF_Demute();//2004AUDDRV AudioDemute();
            }
        }
//#endif


        OSD1000ISP_STATUS(OSDISP_DEMUTE, OSDIR_MUTE);
        OSD_OnOffRegion(OSD_OFF,1);

}

#endif

#ifdef IR_SLEEP //hongfeng 2005-07-12 //chenzhao 2006-4-20 13:27 .
BYTE sleep_time =0;
BYTE sleep_flag_state =0;
#ifdef SUPPORT_VFD_SHOW_SLEEP       
void vfd_set_sleep_show(void);
#endif
extern BYTE cnt500ms;
void ircmd_sleep(void)
{
	#ifdef SLEEP_INVALID_IN_OPEN_NODISC
	if((system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN))
    {
		invalid_key();
		return;
	}
	#endif

    if (action_click)
    {
    	cnt500ms=0;
        if (sleep_time < 15 )
            sleep_time = 15;
        else if (sleep_time  <30)
            sleep_time = 30;
        else if (sleep_time <60)
            sleep_time = 60;
        else if (sleep_time <90)
            sleep_time = 90;
        else if (sleep_time <120)
            sleep_time = 120;
        else 
            sleep_time = 0;
		if(sleep_time)
			 sleep_flag_state=1;
		else
			sleep_flag_state=0;
    }
            
    #ifdef SUPPORT_VFD_SHOW_SLEEP       
    vfd_set_sleep_show();
    #endif
        if (sleep_time)
        {
                psprintf(RegionValStr[REGION1],"SLEEP: %3d MINUTES",sleep_time);
            PrintOsdMsg(STR_OS_SPACE,REGION1,2,1);
        }
        else
        {   
        psprintf(RegionValStr[REGION1],"SLEEP: OFF");
        PrintOsdMsg(STR_OS_SPACE,REGION1,2,1);
        }
}

#endif  //ir_sleep

#if defined(IR_SWITCH_DVD_USB_CARD_AVIN_DVB)||defined(AV_IN_THROUGH_EXT_ADC)
#include "ircmd_mode.c"
#endif

#ifdef SUPPORT_OP_FIVE_DISC////chenzhao20050111 SUPPORT_FIVE_DISC  //chenzhao20050107//OP joke add
void ircmd_pannel_disc(BYTE disc)
{
	if(! goto_disc(disc))
        invalid_key();
    else
    {
        #ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT//chenzhao20060206
        rep_mode = REPEAT_IDLE;
        #endif
    }
}
void ircmd_panel_disc_1(void)
{	
    ircmd_pannel_disc(1);
} 
void ircmd_panel_disc_2(void)
{
    ircmd_pannel_disc(2);
} 
void ircmd_panel_disc_3(void)
{
    ircmd_pannel_disc(3);
} 
void ircmd_panel_disc_4(void)
{
    ircmd_pannel_disc(4);
} 
void ircmd_panel_disc_5(void)
{
    ircmd_pannel_disc(5);
}

#ifndef SUPPORT_5DISC_EXCHANGE
void ircmd_panel_all_eject(void)
{
    #ifdef SUPPORT_FIVE_DISC_DBG
	printf("5disc : all ejecte is_tray_out()= %d  \n",is_tray_out());
    #endif  
	if(!tray_oper_finish())
	{
		invalid_key();
		return ;
	}
		
	if(is_tray_out())
	{
#ifndef SUPPORT_5DISC_EXCHANGE				
		if(get_is_all_eject())
			ALL_Close_Handle();
		else
#endif
			Individual_CLOSE_Handle();	
	}
	else
	{
		ircmd_trayout();
		set_all_open_command();
	}
}
#endif

void ircmd_panel_exchange(void)
{
	//Exchange_Handle();
	if(media_type == MEDIA_CARD) //playback usb 
		return ;

    if(! multidisc_loader_post_cmd(MULTIDISC_CMD_EXCHANGE))
    {
        #ifdef ORITRON_TRAY_PASSWORD//chenzhao20060209
        if(tray_flag==0x33)//0x33 means ?
        {
            PrintOsdMsg(STR_OS_LAD_LOCK,REGION1,2,0);
        }
        else
        #endif
        invalid_key();
    }
	//set_exchange_command();
} 
#endif//#ifndef SUPPORT_5DISC_EXCHANGE


