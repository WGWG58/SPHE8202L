/*****************************************************************************
** FILE
** ir_parse.c
**
** DESCRIPTION
** process IR keys and send to ir_cmd_xxx for actual process
**
**   creater: Terry
**   2005/09/12 yltseng, Add new structure for font
**
**
****************************************************************************/

#include "config.h"
#include "regmap.h"
#include "global.h"

#ifdef PMP_UI    //////////////////////yangli   2005/5/20
#include "fsNAV.h"
#endif

#include "jpeg_parser.h"
#include "fsNav_util.h"
#include "cfont.h"
#include "func.h"
#include "sio.h"
#include "ircmd.h"
#include "ircode.h"
#include "user_init.h"
#include "iop.h"
#include "atapi_if.h"
#include "macro.h"
#include "osd.h"
#include "bitop.h"
#include "timer.h"
#include "kernel.h"
#include "memcfg.h"
#ifdef SUPPORT_MIDI
#include "fsmidi.h"                //ouyang  2004.08.13 take apart the function of "up" key
#ifdef SUPPORT_MIDI_MENU_SEL     //xlluo 2004.11.23
#include "fsmidiUI.h"
#endif
#endif
#ifdef AD_TCL//2004-3-22 13:11 lijd
#include "user_if.h"
#endif
#ifdef NEWSTYLE_WINDOW
#include "vpp.h"
#include "osd_arc.h"
#endif
#if defined(EASTWIN)||defined(TOP_DOOR_LOADER)
#include "gpio.h"//tulijuan040908
#include "cd.h"
#endif

#ifdef TAS3001_AMP
#include "ti3001.h"
#endif

#ifdef TAS5026_AMP
#include "ti5026.h"
#endif

#ifdef DIVX_DRM
#include "DRM_UI.h"
#endif

//#define ssc_watch_ir_code   1

#ifndef DVDRELEASE
#define IR_DBG  //terry,2004/2/19 05:04PM,pls don't mark it.
#define MONE_DSP24_SHOW_CODEC_NAME_BY_ANGLE_KEY         // 2004/12/21 yltseng
#define MONE_SHOW_JPEG_RESOLUTION_BY_ANGLE_KEY          // 2006/08/1 Joshua          
#endif

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif

#ifdef SUPPORT_REP_READ
#include "read.h"
#endif

#ifdef SUPPORT_DISPLAY_MENU
#include "setup_def.h"
#endif

#ifdef QSI_SHOW_ERR_RATE
#include "uart.h"
#endif

#ifdef SUPPORT_RECEIVER  //chenzhao20050620
#include "amp_gui.h"
#endif

#ifdef SUPPORT_VFD_MENU
BYTE call_ir_func_vfd_menu(BYTE key);
#endif

#if defined( SUPPORT_MP3_ENCODER) 
#include "audcodec.h"
extern void fs_mp3_encoder_main(void);
extern void fs_mp3_encoder_restart(void);
extern void change_encode_speed(void);
extern void do_close_file(void);
extern UINT32 recNew;
extern void stop_current_ripping(void);
extern int is_cdg_disc(int show __UNUSED); //qinhua ,add for warning,2006-3-1 02:14下午
#endif

//Simon 2006.6.30
#ifdef CD_RIPPING_NO_GUI
extern BYTE new_parental_gui;
#include "fs_new_app.h"
#include "fs_new.h"
#endif

#ifdef CD_RIPPING_USE_GUI
#include "cd_ripping.h"
#endif

#ifdef USE_IR_FILTER
#include "ir_filter.h"
#endif
#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2004-2-9 13:02
extern BYTE new_parental_gui;
#elif defined(MODIFY_PARENTAL_GUI)
extern BYTE parental_gui_flag;
#endif//NEW_PARENTAL_GUI

#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI) 
extern void ExitParentalGUI(void);
#endif

#define CLS_ERR_KEY

#ifdef PRE_NEXT_FLAG        
UINT8 PRE_FLAG;
UINT8 NEXT_FLAG;
#endif  //axel, for invalid IRC_NEXT in bad discs 2004/7/12 

//extern void osd_restore();
extern UINT32 save_srn_start_t;
extern int is_dvd_prohibit_key(void);
extern int is_menu(void); // in cderr.c
extern void init_ir_num(void);
extern void osdshow(UINT8 r,char *buf);
extern void DispPolling(BYTE bReset);

#ifdef TP6317_PANNEL   //yaowh add 04-10-25
   BYTE TP6317_Power = 0 ;
#endif

#ifdef NEW_UART_COMMAND            //lijinhai for fuss new request
extern BYTE nCurrentVolMode;
#endif

#ifdef NEWSTYLE_WINDOW
extern void exit_browse_func(void);
#endif

#ifdef JPG_EFFECT
extern void FSGUI_Menu(void);
#endif

#ifdef SUPPORT_TUNER
extern void tuner_key(BYTE key);
#endif

#ifdef DOUBLE_TITLE //susu add 2003-8-27 13:55
extern void exit_double_title(void);
#endif

#ifdef  ROTARY_VOLUME
extern void RotaryStateChk(void);
#endif

extern BYTE setup_IsSettingPassword(void);

#ifdef SUPPORT_8202_DVB//Jack clear warning msg 05/09/29
#if defined(SUPPORT_DVB_GUI_NEW)&&defined(DVB_IR_3D_ON)
#include "..\dvb_h\dvb_func.h"
#endif
#endif

#ifdef HELP_BMP_GUI
    #define HELP_PAGE_COUNT 4
#else
    #define HELP_PAGE_COUNT 3
#endif

#ifdef OP_PLAYMODE
extern int u;
extern int r;//libing for display&OP_MENU 
void exit_op_menu(void);
#endif
#ifdef MODE_SWITCH_DELAY
extern UINT32 read_iso_file_state;
#endif

#ifdef MUSTEK_PORTABLE_DVD
extern void DispPolling(BYTE bReset);
#endif

#ifdef ALCO_DVD_UI
extern void DispPolling(BYTE bReset);
#ifdef DVD_SETUP_REENG
extern void setup_ExitPage(void);
#endif
#endif

#ifdef PAUSE_PREV_DISPLAY_MACROVISION_VERSION
extern BYTE MACVersion_count;
#endif

#ifdef SUPPORT_FILE_SYSTEM_MODE
extern UINT16	IsOtherStatePlayMode(void);
#endif

void ircmd_null(){}

#ifdef QSI_PLATFORM //qsi: added by johnson 20040812
extern void spi_cmd_switch_media_to_card(void);
extern void spi_cmd_switch_media_to_dvd(void);

void ircmd_card_cd_select(void)
{
#ifdef SUPPORT_CARD_STORAGE
    if( source_type_now == source_disc)
    {
        spi_cmd_switch_media_to_card();
    }
    else
    {
        spi_cmd_switch_media_to_dvd();
    }
#endif
}
#endif

//nono 5-5-9 12:48 move it to irc_function_name_tbl.c
#include "irc_function_name_tbl.c"

//nono 5-5-9 12:48 move it to irc_function_name_tbl_spi_qsi.c
#include "irc_function_name_tbl_spi_qsi.c"


//Marked by maoyong 2004-9-24 10:50, now just use a function to set proc func pointer

#ifdef SUPPORT_NESGAME
BYTE Game_GetBreakIr(BYTE i)
{
    switch(i)
    {
        case 0:return IR_EJECT;
        case 1:return IR_POWER;
        case 2:return IR_STOP;
        case 3:return IR_RETURN;
        case 4:return IR_POWER2; 
        case 5:return IR_RETURN2;        
        case 6:return IR_VOLUME_DOWN;
        case 7:return IR_VOLUME_UP;
        default: return 0xff;//terry,2004/2/2 04:35PM
    }
}

#ifdef SUPPORT_IR_GAME
BYTE Game_GetControlIr(BYTE i)
{
    switch(i)
    {
        case 0:return IR_RIGHT;
        case 1:return IR_LEFT;
        case 2:return IR_DOWN;
        case 3:return IR_UP;
        case 4:return IR_START; //terry,mark it,2004/2/2 04:35PM
        case 5:return IR_SELECT;
        case 6:return IR_A_KEY;
        case 7:return IR_B_KEY;
        case 8:return IR_RIGHT_UP;
        case 9:return IR_LEFT_UP;
        case 10:return IR_RIGHT_DOWN;
        case 11:return IR_LEFT_DOWN;        
        case 12:return IR_RIGHT2;
        case 13:return IR_LEFT2;
        case 14:return IR_DOWN2;
        case 15:return IR_UP2;
        case 16:return IR_START2; //terry,mark it,2004/2/2 04:35PM
        case 17:return IR_SELECT2;
        case 18:return IR_A_KEY2;
        case 19:return IR_B_KEY2;        
        default: return 0xff;//terry,2004/2/2 04:35PM
    }
}
#endif

#endif


//nono 5-5-9 12:37 move to ir_inv_tbl_include.c
#include "ir_inv_tbl_include.c"

int user_input_pwd=0;

void cancel_rep(void)
{
     
     if((rep_mode != REPEAT_IDLE)||(rep_ab_mode != REPEAT_AB_IDLE))
     {
        OSD1000ISP_STATUS(OSDISP_REP_IDLE, OSDIR_REPEAT);

        #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        if(usb_card_state != SWITCH_TO_USB_BUT_HAS_NO_USB)
        #endif
        
        //2005.3.23, joshua, this string is too long for osd region2 on 16m platform
        #ifdef OP_PLAYMODE//libing 2005-5-26 20:45
        	PrintOsdMsg(STR_OS_REP_CNL,REGION2,1,0);
        #endif	
        #ifndef  SDRAM_16Mb_Mode
            PrintOsdMsg(STR_OS_REP_CNL,REGION2,1,0);
        #endif
        
        rep_mode    = REPEAT_IDLE;
        rep_ab_mode= REPEAT_AB_IDLE;
     }
}

#ifdef NEW_STYLE_SETUP
extern UINT8 logo_type;//NEW STYLE SETUP FOR GBM 
#endif//NEW_STYLE_SETUP

#if defined( SUPPORT_FONT_UTIL ) && defined( SUPPORT_MULTI_FONT_SWITCH )   // 2005/03/10 yltseng
#include "fsNav.h"
#include "fsGUI.h"
#include "LanguageUtil.h"

static UINT8   s_uiNeedReadFileInformation = FALSE;

void ReadFileInformation()
{
    if( !s_uiNeedReadFileInformation )
        return;

    #define FSJPEG_BUF_OFFSET  ( ( sizeof( FSJPEGDATA ) >> 2 ) << 2 )
    
    FSJPEGDATA* pTmp = (FSJPEGDATA*) ( (UINT32)pFsJpeg + FSJPEG_BUF_OFFSET );
    memcpy( pTmp, pFsJpeg, sizeof( FSJPEGDATA ) );

    int iRes = 0;
    ReadFile( &iRes );

    memcpy( pFsJpeg, pTmp, sizeof( FSJPEGDATA ) );
    
    s_uiNeedReadFileInformation = FALSE;
}

static inline   ChangeFontByAngleKey( BYTE rx )
{
    #ifndef USE_SETUP_SELECT_FONT//shenyj add for alco 11/28
    if( rx == IRC_ANGLE )
    {
        if( cd_type_loaded == CDROM )
        {
            langNextFont();

            #ifdef PMP_UI ////////////////////////yangli mod for angle key change font,sys will reread dir list,sys can't find subtitle file.2005/11/18
            s_uiNeedReadFileInformation = FALSE;
            #else
            s_uiNeedReadFileInformation = TRUE;
            #endif 
            
            if( !IsOtherStatePlayMode() )
            {
            	#ifndef PMP_UI
                ReadFileInformation();
                #endif                             
                extern BYTE JPEG_Preview_drawed;
    
                if( ( IsOtherStatePlayMode() && GetCurrentFileType() == CDROM_MP4 ) ||
                    ( ( pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG ) && 
                      ( ( pFsJpeg->gifsState == FS_STATE_JPEG ) 
#if defined( FS_BMP_GUI ) || defined( NEW_MP3_GUI ) || defined(INDIGO_STYLE_FSGUI)
                        || ( pFsJpeg->g_nJpegMode == JPEG_THUMBNAIL_MODE )
#endif
                      ) ) )
                {
                    // do nothing
                }
                else
                {
                    if( Is_JPEG_STATE() && JPEG_Preview_drawed == JPEG_PREVIEW_IN_DIR_AREA )
                        FSGUI_Menu();
                   #ifdef PMP_UI
                   if((pFsJpeg->gifsState == FS_STATE_INIT)||
                      (pFsJpeg->gifsState == FS_STATE_MP3))
                    {
                        if(pFsJpeg->gifsState == FS_STATE_MP3)
                        update_current_file_index();
                     FSGUI_Refresh_PMP();
                     FSGUI_DirList(pFsJpeg->hdd_dir_current);
                     ShowHL(); 
                    }
                   #else
                    FSGUI_Refresh();
                   #endif
                   
                   
                    
                        
                }
            }
        }
        else
        {
            s_uiNeedReadFileInformation = FALSE;
        }
    }
    #endif//#ifndef USE_SETUP_SELECT_FONT//shenyj add for alco 11/28
}
#else
#define ChangeFontByAngleKey( rx )
#endif

#ifdef MONE_DSP24_SHOW_CODEC_NAME_BY_ANGLE_KEY  // 2005/02/18 yltseng
static inline void ShowDSPCodecNameByAngleKey( BYTE rx )
{
    if( rx == IRC_ANGLE )
    {     
        extern void DSP_GetCodecIDString( char* pBuf );
        extern void DSP_GetCodecVersionString( char* pBuf );
        
        char aID[32];
        DSP_GetCodecIDString( aID );
    
        char aVer[4];
        DSP_GetCodecVersionString( aVer );
        
        char aBuf[36];
        psprintf( aBuf, "%s %s", aID, aVer );
        
        psprintf(linebuf, "dsp info : %s\n", aBuf );
        io_write_wait(linebuf);
        ConvertLowerCaseToUpperCase( aBuf );
        osdshow( REGION1, aBuf );
    }
}
#else
#define ShowDSPCodecNameByAngleKey( rx )
#endif

#ifdef MONE_SHOW_JPEG_RESOLUTION_BY_ANGLE_KEY
static inline void ShowJpegResolutionByAngleKey( BYTE rx )
{
    if( rx == IRC_ANGLE )
    {   
        UINT16 w, h;  
        
        jpg_get_actual_resoluation(&w, &h);
        delay_1ms(20);
        
        char wBuf[12];
        psprintf( wBuf, "%d %c", w, 'X');
        
        char hBuf[6];
        psprintf( hBuf, "%d [%d %d]", h, jpg_get_downsample_rate()>>16, jpg_get_downsample_rate()&0xffff);
        
        strcat1(wBuf, hBuf);
        
        osdshow( REGION1, wBuf );
    }
}
#else
#define ShowJpegResolutionByAngleKey( rx )
#endif
static inline UINT32 RejectBySWD( BYTE rx __attribute__((unused)))
{
    BYTE res;
    res = FALSE;
    #ifdef SUPPORT_PLAY_SWD
    extern BYTE SWD_CheckIrcmd(BYTE rx);

    if( START_POLLING_SWD )
    {
        res = SWD_CheckIrcmd(rx);
    }
    #endif

    return res;
}
extern BYTE GetCurrentFileType();

#ifdef SUPPORT_DIVX6
//#include "divx6_if.h"
extern UINT32 divx6_menu_exist;
extern UINT32 divx6_menu_playback;
int    (*pfnIR_IRFilter1)(BYTE);
#endif    


#ifdef   SUPPORT_MALATA_INVALID_KEY//tianye 200607
#include "user_if.h"  

int mlata_ircmd_pre_paser(BYTE rx);
int mlata_ircmd_pre_paser(BYTE rx)
{
	 int check_result = 0;
   
	#ifdef  CDROM_TITLE_MENU_INVALID_KEY  
	if((cd_type_loaded == CDROM)&&(
		(rx == IRC_TITLEMENU)||((rx == IRC_PBC)) ))
    	{
		check_result  = 1;
    	}
    	#endif//end=> #ifdef  CDROM_TITLE_MENU_INVALID_KEY

       #ifdef  SOME_KEY_INVALID_WHEN_WRONG_REGION
       else  if((dvd_error==REGION_ERR)&&
	   	       ((rx == IRC_PAUSEPLAY)||(rx == IRC_GOTO)||(rx == IRC_TITLEMENU)
	   	       ||(rx == IRC_DISPLAY)||(rx == IRC_P10)||(rx == IRC_PBC)))
    	{
       	check_result  = 1;
    	}
	#endif//end=> #ifdef  SOME_KEY_INVALID_WHEN_WRONG_REGION   

       #ifdef  SOME_KEY_INVALID_WHEN_TITLE_MENU
       else  if(cd_type_loaded==CDDVD)
    	{
       	if(((disp_time ==0)||(get_tt_info(DISP_TT) == 0)||(get_tt_info(DISP_CH)==0)||(HL_exist))
			&&((rx == IRC_PREV)||(rx == IRC_GOTO)||(rx == IRC_AB)/*||(rx == IRC_STOP)*/
	   	       ||(rx == IRC_SLOW)||(rx == IRC_ZOOM)))
    		{
       		check_result  = 1;
    		}
    	}
	#endif//end=> #ifdef  SOME_KEY_INVALID_WHEN_TITLE_MENU   

   	return   check_result;

}
#endif//endif=> #ifdef   SUPPORT_MALATA_INVALID_KEY


void ircmd_pre_paser(BYTE rx)
{
    UINT8 need_run_cmd=1,display_again=0;//terry,0513 
    UINT32 invalid=ir_invalid_state[rx];
    #ifdef IR_DBG
    //printf("ir pre-parser in\n");    
    #endif

#ifdef  ALCO_DIVX_UI//shenyj add for alco 12/22
    if(full_scrn ==DIVX_DRM_MENU)
        rx=IRC_SELECT;
#endif

#ifdef CD_RIPPING_USE_GUI   //Simon, 2006.5.26
    if ((cd_type_loaded == CDDA) && (rx == IRC_SUBP))
    {
        if (!is_cd_ripping_active())
        {
            #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-10-10 17:10( for CD RIPPING )
            if( is_usb_media_exists() )
            {
                storage_type = USB_DEVICE;
            }
            #endif//DIRECT_ACCESS_MEDIA
            
            cd_ripping_start();
            AVD_SetMediaInterrupt();
        }
        return;
    }
    else if (is_cd_ripping_active())
    {
        cd_ripping_ir_handler(rx);
        return;
    }
#endif

#ifdef SUPPORT_MP3_ENCODER   //qinhua,2005-12-2 0:10
      if(rx == IRC_SUBP)
	{
	  if(is_cdg_disc(1)||(Is_JPEG_STATE()))  
          {  
            invalid_key();
            return;
           }  
       }
if(cd_type_loaded == CDDA)   
{
if((pre_ripping_flag)||((mp3_encoder_state == test_write_data)&&(recNew<1)))  //qinhua,add for abruptly stop ripping,2005-12-16 21:28
  { 
     if((rx ==IRC_NEXT)||(rx == IRC_PREV)||(rx == IRC_STOP)||(rx == IRC_SUBP)
     #if defined(ORITRON_HK_DVD)||defined(OP_MP3_ENCODER_UI)//chenzhao20060208
      ||(rx == IRC_ANGLE)
      #else
      ||(rx == 0x62)
     #endif  
      )
     {
      invalid_key();
       return;
     }  
}
  
    if(mp3_encoder_state == test_write_data)
    {
      if( (rx == IRC_BOOK)||(rx == IRC_GOTO)||(rx == IRC_FORWARD)||(rx == IRC_BACKWARD)||(rx == IRC_AB)
      #ifdef OP_PLAYMODE
      ||(rx==IRC_MODE)
      #endif 
      #ifdef CD_RIPPING_SETUP_INVALID//chenzhao20060124
          #ifdef EXIT_KEY
      ||(rx == IRC_EXIT)
          #else
      ||(rx == IRC_SETUP)
          #endif
      #endif
      )	
       {
    	   invalid_key();
           return;	   		
        }
    if((rx ==IRC_NEXT)||(rx == IRC_PREV)) //qinhua ,add,because some disc at this time must switch DSP code and betimes close file,2005-11-29 21:52
       {
       printf("=================ENCODER SKIP XXXXXXX\n\n");
        change_speed_flag=0;
        #ifndef CD_DIRECT_RIPPING
        ripping_flag=0;   
        #endif 
       stop_current_ripping();
        }
    }
}
#endif  

#ifdef   SUPPORT_MALATA_INVALID_KEY//tianye 200607
	if(mlata_ircmd_pre_paser(rx))
	{
   		invalid_key();
              return;
	}
#endif//endif=> #ifdef   SUPPORT_MALATA_INVALID_KEY

#ifdef AUTO_INTO_STANDBY
        extern int auto_standby_timer;
        auto_standby_timer=0;
#endif		
	
#ifdef SUPPORT_SMF	//add by xjliu for input device of flash driver 05-06-29
	extern UINT16 FlashKeyValue;
	extern UINT32  flash_break;
	if (FlashKeyValue == 0 && FlashIsEnable && (flash_break != 1))//(FlashIsEnable)
	{
		switch(rx)
		   {
		        case IRC_UP:
				printf("xjliu:UP\n");
				FlashKeyValue = 1;
				//break;
				return;
		        case IRC_DOWN:
				printf("xjliu:DOWN\n");
				FlashKeyValue = 2;
				//break;
				return;
		        case IRC_LEFT:
				printf("xjliu:LEFT\n");
				FlashKeyValue = 3;
				//break;
				return;
		        case IRC_RIGHT:
				printf("xjliu:RIGHT\n");
				FlashKeyValue = 4;
				//break;
				return;
		        case IRC_TITLEMENU:
				printf("xjliu:SPACE\n");
				FlashKeyValue = 5;
				//break;
				return;
		        case IRC_RETURN:
				//printf("xjliu:ENTER\n");
				//FlashKeyValue = 6;
				break;
				//return;
			 case IRC_STOP:
			 	printf("xjliu:STOP flash\n");
			 	FlashKeyValue = 7;
			 	return;
			 case IRC_EJECT:
			 case IRC_POWER:
			 	break;
		        default:
				return;
		   }
	}
    #endif
#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)   
#ifdef AFTER_RECORD_DELAY
if(((need_record)&&(need_record<=AFTER_RECORD_DELAY_CNT2)) || (need_record==PRE_STOP_FLAG))
#else
 if(need_record == PRE_STOP_FLAG)
#endif//#ifdef AFTER_RECORD_DELAY
    {
        return;
	}
#endif
   
#ifdef MP4_INIT_STATE_INVALID_KEY
    if(MP4_init_state)
    {
        if((rx!=IRC_POWER) && (rx!=IRC_EJECT))
        {
            if(( invalid & DRM_MENU ) && ( full_scrn & DIVX_DRM_MENU ) )
            //if(full_scrn !=DIVX_DRM_MENU)
            //printf_w("MP4_init_state,return\n");
            return;
        }    
    }    
#endif
   
    #if (defined(OP_PLAYMODE)&&!defined(EXIT_KEY)) //chenzhao20060124//modify hongfeng 2005-12-6//libing 2005-4-13 01:10
       if(full_scrn==OP_MENU)
    {
        if(!((rx==IRC_SELECT)||(rx==IRC_UP)||(rx==IRC_DOWN)
        ||(rx==IRC_LEFT)||(rx==IRC_RIGHT)||(rx==IRC_MODE)))
        {            	
            	exit_op_menu();
            	 
     }
    }
    #endif
   
   #ifdef FILE_MODE_WRITE//added by wangwei,2005-1-25 16:21
   if(rx == IRC_FM_WRITE)
        play_state = VCD_STATE_NORMAL;
   #endif

#ifdef SUPPORT_HD_RESOLUTION
    if((GET_TV_RESOLUTION() == HD_720) || (GET_TV_RESOLUTION() == HD_1080))
    {
        if(rx == IRC_P_SCAN) {
            invalid_key();
            return;
        }    
    }
#endif

#ifdef SUPPORT_MIDI_MENU_SEL
   printf("polling_rotary bHoldInput %d\n",bHoldInput);
        //may be I should set a critical section      
    if (gIsMidiSelMenu&&bHoldInput )                                      //xlluo 04-11-26
          return;                                                          //xlluo for irdebug 04-11-23
#endif   

#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)
    irc_func_table[rx]();   
#endif
    
    if(show_logo)
    {
        return;
    }
        
#ifdef MIDI_EJECT_PASSWORD    //ouyang add for eject password 2004-11-20 15:10
extern UINT8 midi_open_pwd_start;    
extern UINT8 midi_open_pwd_finished; 
#endif        
#ifdef MIDI_EJECT_PASSWORD   //xlluo 04-12-06
    if (midi_open_pwd_start&&(!midi_open_pwd_finished)) 
    {
       switch(rx)
       {
            case IRC_0:     
            case IRC_1:
            case IRC_2:
            case IRC_3:
            case IRC_4:
            case IRC_5:
            case IRC_6:
            case IRC_7:
            case IRC_8:
            case IRC_9:
            case IRC_SELECT:
            case IRC_POWER:
                printf("haha\n");
                break;
            default:
                printf("forbidden\n");
                return;
       }
    }
#endif//#ifdef MIDI_EJECT_PASSWORD    //ouyang add for eject password 2004-11-20 15:10
       
    #ifdef RECORD_KEY//zhaoyanhua add  2003-11-19 16:37      
    //NOTE:
    // if you want change the RECORD_OSD_SHOW_TIME value, 
    // must change it in file sysmain2.c at the same time.
    //zhaoyanhua  2003-12-12 15:18  
    #define RECORD_OSD_SHOW_TIME  14   
    
    //when show RECORD OSD message, other keys except IR_RECORD will
    // break out the OSD message and excute its function.
    if(same_disc_flag!= 0)
    {
        if(rx != IRC_RECORD)
        {

            same_disc_flag = RECORD_OSD_SHOW_TIME;
            //to keep this IR code.
            //excute IR function after exit RECORD OSD message.

#ifdef MODIFY_RECORD_KEY//2004-3-30 19:16
            if(rx == IRC_EJECT||rx == IRC_POWER)//2004-3-30 19:14
#endif         
            keep_cmd_code = rx;
            //regs0->iop_data[IR_PORT]|=IR_RDY;



            return;
    }
    }
    #endif
        
#ifdef MIC_FUNCTION_KEY
    #ifdef BBK_DVD//zhaoyanhua add 2003-11-30 12:29
    extern BYTE bFuncStep;
    //if user enter other keys except IRC_MIX__FUNCTION/UP/DOWN,
    // it will excute its corresponding function.
    if((rx !=IRC_MIX_FUNC ) && (rx != IRC_UP) && (rx != IRC_DOWN)&&(bFuncStep))
    {
        osd_tog_region(REGION1, OSD_OFF);
        bFuncStep = 0;    
    }     
    #endif
        
#endif //MIC_FUNCTION_KEY   
        
    if(user_input_pwd==1)//nono 20020604
    {
        if( (rx<=IRC_10)||(rx==IRC_SELECT)||
            (rx==IRC_CLEAR)||(rx==IRC_PLAY_RESUME)||
            (rx==IRC_POWER)||(rx==IRC_EJECT)||
            #ifdef SUPPORT_OP_FIVE_DISC
            (rx>=IRC_DISC_1 && rx<=IRC_DISC_3)||
            (rx>=IRC_DISC_4 && rx<=IRC_DISC_5)||
            #endif
            (rx==IRC_PLAY_SELECT)||(rx==IRC_PAUSEPLAY) )
        {
            if((rx==IRC_EJECT)||(rx==IRC_POWER))
            {
                user_input_pwd=2;
#ifdef DVD_AUDIO//2004-3-5 17:48
                if(pDSV->hid_gp_chk_pwd==2)
                {
                    regs0->iop_data[IR_PORT]|=IR_RDY;
                    //full_scrn=0; //t_disp=disp_mode;
                    osd_init();
                    return;
                }
#endif//DVD_AUDIO
            }    
                        
            //Maoyong 2004.03.06 , Record disc check Level SYSTEM_SETUP_BROWSER, 
            //Avoid 2 times "ircmd_eject_toggle" and then can't do right TRAY OUT           
            #ifdef  CHECK_RECORD_DISK_PARENT_LVL
            if( !((system_state == SYSTEM_SETUP_BROWSER) && (rx== IRC_EJECT)) )
            #endif          
            #ifdef SUPPORT_SPI_QSI
            if( /*(rx == IRC_STOP) || */(rx == IRC_PLAY) /*|| (rx == IRC_PAUSE)*/ )
                spi_cmd_func_table[uSpiRxData]();
            else
            #endif
            irc_func_table[rx]();
            
            if( (rx==IRC_SELECT)||(rx==IRC_PLAY_RESUME)||
                (rx==IRC_PLAY_SELECT)||(rx==IRC_PAUSEPLAY))
                user_input_pwd=0;
            
              
        }
        if((rx!=IRC_EJECT)&&(rx!=IRC_POWER))
            return;
    }
    
    if( RejectBySWD( rx ) )
        return;
        
#ifdef USE_IR_FILTER    
    if(pfnIR_IRFilter1 == NULL)
    {
        pfnIR_IRFilter1 = IRFilter_All_Pass;
    }
    switch(pfnIR_IRFilter1(rx))
    {
	    case IR_FILTER_REJECT:
	        return;
	        break;
	    case IR_FILTER_NOP:
	        break;
	    case IR_FILTER_EXCEPTION:
	        break;
	    default:
	        break;
    }

    #ifdef SUPPORT_DIVX6
    extern UINT32 is_divx6_file;
    extern int divx6_AdjustState(BYTE rx);
    if(is_divx6_file)
    {    
        divx6_AdjustState(rx);
    }
    #endif  //#ifdef SUPPORT_DIVX6

#endif//USE_IR_FILTER
extern UINT8 gIsMidiSelMenu __attribute__((unused)); //mimitsai add 2004-12-03 17:13
    
#ifdef DIVX_DRM
    if( ( invalid & DRM_MENU ) && ( full_scrn & DIVX_DRM_MENU ) )
    {
    #ifdef IR_DBG
        printf( "Disable key in DRM_MENU\n" );
    #endif
    #ifdef ALCO_DVD_UI        
        osd_init();
        full_scrn=0;
    #else
        return;
    #endif
    }
    else
#endif
#ifdef SUPPORT_MIDI         //axel add for "FF"、“pause”etc.are invalid when press "PREVIEW"2004.09.21

    if ((gIsMidiSelMenu)&&(rx==IRC_PREVIEW))
    {
        need_run_cmd=0;
        #ifdef IR_DBG            
          printf("<ir_invalid 15>\n");
        #endif
    }
    else
#endif

#if defined(SUPPORT_MIDI)&&defined(NEW_SEARCH_OSD)   //axelchen add for "display"
        extern UINT8 gIsMidiSelMenu;
        if (gIsMidiSelMenu)
           {
            if((rx==IRC_GOTO)||(rx==IRC_DISPLAY))
            need_run_cmd=0;
            }
        else 
#endif// defined(SUPPORT_MIDI)&&defined(NEW_SEARCH_OSD)

    if(rx==IRC_RANDOM)
    {
        #if !defined(PRESS_RANDOM_IF_INVID_DERECT_SHOW)//ZXB 2005-5-16 15:36
        if(action_click)
        #endif
        {
            if((invalid&(0x01<<play_state))
            #ifdef WHEN_PROG_PLAYING_PUSH_RANDOM_SHOW_INVALID //ZXB 2005-5-16 15:36
                ||((invalid&PROG_PLAY)&&prog_cnt && (!setup_IsSettingPassword()))
            #endif
                )
            {
                #ifdef IR_DBG            
                printf("<ir_invalid 13>\n");
                #endif

                need_run_cmd=0;
            }
        }

    }else if(invalid&(0x01<<play_state))
    {
#ifdef WINGSUM_DVD  
	//suxin add 2005-10-19    for not display "INVIALID KEY" when IRC_NULL
	//wingsum TVComBo, some IR button used by TV but can be detected by DVD.
	//					so we can receive IRC_NULL 

    	return;

#endif

        need_run_cmd=0;
        #ifdef IR_DBG            
        printf("<ir_invalid 12>\n");
        #endif                    
        #ifdef PMP_UI        /////////////////yangli
       // if(pFsJpeg->gifsState == FS_STATE_INIT)
        need_run_cmd=1;
        #endif

#ifndef SUPPORT_8202_DVB   //if don't add define,DVB will compile error!
        if(rx == IRC_DEFAULT_SETUP) // jiangxl  for default key 2006-7-21 01:13下午
        {
            need_run_cmd = 1;
        }
#endif        
        
        #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-12 17:56
        if(rx == IRC_SW_MEDIA)
        {
            need_run_cmd = 1;
        }
        #endif//DIRECT_ACCESS_MEDIA

#if defined(ALCO_8200P_MULTIKEY)&& defined(NEED_DIFF_IR_PANEL_KEY)
    if(((play_state==VCD_STATE_OPEN)||(play_state==VCD_STATE_IDLE)) && (rx==IRC_PAUSE))
    {
        if(panel_key_flag && (!(panel_key_flag&(0x01<<2))))
            need_run_cmd = 1;
    }
#endif

        /* alan added 02-05-13 for FUSS : return to main setup menu when press IRC_RETURN */        
        //terry,0516, 
        //setup ->3d
        #ifdef  FUSS_DVD                        
        if( (full_scrn&SETUP)&&(rx==IRC_RETURN) ) need_run_cmd=1;
        #endif          
        
        #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        if(rx == IRC_DVD_USB_CARD_AVIN_DVB)
        {
           need_run_cmd = 1; 
        }
        #endif
                  
        #ifdef DVB_IR_3D_ON
        if((full_scrn&SOUND) && (rx==IRC_3D))
            need_run_cmd = 1;
        #endif
        #if defined(SUPPORT_RECEIVER)//chenzhao20060117
        if(((current_rcvr_mode!=RECEIVER_MODE_DVD)&&(0
            ||(rx == IRC_VOLUME_DN)
            ||(rx == IRC_VOLUME_UP)
            ||(rx == IRC_MUTE)
            #if defined(SUPPORT_PRO_LOGIC_IN_RECEIVRR_MODE)
            ||(rx == IRC_PROLOGIC)
            #endif
            #if defined(SUPPORT_RECEIVER_EQ)//chenzhao20060117
            ||(rx == IRC_EQ)
            #endif
            #ifdef SUPPORT_EX_BASS_FUNC//chenzhao20060117
            ||(rx == IRC_EX_BASS)
            #endif
            #ifdef IR_SLEEP//chenzhao20060208
            ||(rx == IRC_SLEEP)
            #endif
            ))
            #ifdef ADJUST_VOLUME_WHEN_NODISC//chenzhao20060208
            ||((system_state == SYSTEM_NODISC)&&((rx == IRC_VOLUME_DN)||(rx == IRC_VOLUME_UP)))
            #endif
            )
            need_run_cmd = 1;
        #endif
        
        #ifdef  TITLE_RETURN_CANCEL_SETUP
        if((full_scrn&SETUP)&&((rx==IRC_RETURN)||(rx==IRC_TITLE_RETURN)))
            need_run_cmd=1;
        #endif
              
    }
    else if( (invalid&HL)&&HL_exist)
    {
        #ifdef IR_DBG            
        printf("<ir_invalid 11>\n");
        #endif            

        need_run_cmd=0;
        #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        if(rx == IRC_DVD_USB_CARD_AVIN_DVB)
            need_run_cmd = 1; 
        #endif
    }else if((invalid&STILL)&&still_timer)
    {
        #ifdef IR_DBG            
        printf("<ir_invalid 10>\n");
        #endif                  
        #ifdef NEED_DIFF_IR_PANEL_KEY
        if(!((rx==IRC_PAUSE) && (panel_key_flag&(0x01<<0))))
        #endif
        need_run_cmd=0;
        #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        if(rx == IRC_DVD_USB_CARD_AVIN_DVB)
            need_run_cmd = 1; 
        #endif
        
        #ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-12 17:56
        if(rx == IRC_SW_MEDIA)
        {
            need_run_cmd = 1;
        }
        #endif//DIRECT_ACCESS_MEDIA
    }
    #if defined(NINTAUS_DVD)
    else if( (invalid&MENU)&&(is_menu()))//( psd_state==(PSD_SEL_LIST|PSD_PLAY_SEG)) )
    #else
    else if( (invalid&MENU)&&( psd_state==(PSD_SEL_LIST|PSD_PLAY_SEG)) )
    #endif 
    {//terry,2002/9/11 04:08PM
     //I'm not sure whether has bug.But I'm sure DVD non-hl menu may be pause/ff/bw/...
        #ifdef IR_DBG            
        printf("<ir_invalid 9>\n");
        #endif                  

        need_run_cmd=0;
    }
    
#ifdef CD_RIPPING_NO_GUI
    if ((rx == IRC_SUBP) && (cd_type == CDDA))
    {
        //if (!fs_is_activated_rip())
#ifdef RIPPING_MODE_SELECT//qinhua add,2006-5-30 10:59下午
       if(new_app_state!=NEW_APP_STATE_WRITE)
       	{
       	 if (full_scrn!=RIP_GUI)
           show_rip_gui();
       	 else
        	rip_func_exit();
        
         return;
        }
#endif         
        {
            fs_activate_rip();
            if (fs_is_activated_rip())
            {
                //printf("activate ripping\n");
                ircmd_post_func(CMD_SELECT | v11_trk_now);

                //make sure media status is reset in InitializeCDPlayback()
                program_end = 1;
            }
        }
        return;
    }
 else if(((rx==IRC_EJECT)||(rx==IRC_POWER))&&(new_app_state == NEW_APP_STATE_WRITE) )//qinhua add,maybe close file first,2006-5-27 01:51下午
    	  {
    	    fs_file_close(pWriteFile); 
    	  	}
    else if ((rx == IRC_ANGLE) && fs_is_activated_rip())
    {
        printf("speed=%d\n", fs_get_rip_speed());
        if (fs_get_rip_speed() == 1)
        {
            //single->double speed
            fs_set_rip_speed(2);
            //psprintf(RegionValStr[REGION1], "RECORDER 2X");
        }
        else
        {
            //double->single speed
            fs_set_rip_speed(1);
            //psprintf(RegionValStr[REGION1], "RECORDER NORMAL");
        }
      }
 else if ((new_app_state==NEW_APP_STATE_WRITE)&&((rx==IRC_AB)||(rx==IRC_FORWARD)||(rx==IRC_BACKWARD) ))
	{
    	     invalid_key();        
        //PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
        return;
    }
#endif //CD_RIPPING_NO_GUI

#ifdef SUPPORT_FILE_COPYING
    if ((rx == IRC_SUBP) && (cd_type_loaded == CDROM) && (media_type == MEDIA_CD))
    {
        fs_activate_copy();
        if (fs_is_activated_copy())
        {
            ircmd_post_func(CMD_FUNC | CMD_FUNC_SELECT);
        }
        return;
    }
#endif
    else if(invalid&(0x01<<(VCD_STATE_MAX-1+cd_type_loaded)))
    {
        #ifdef IR_DBG            
        printf("<ir_invalid 8>\n");
        #endif                  

        need_run_cmd=0;

        #ifdef SUPPORT_HDD_ACCESS
        if(rx==IRC_SUBP || IRC_TITLEMENU) {
            extern int do_copy_file();
            printf("<SUB-TITLE>\n");
            do_copy_file();
            return;
        }
        #endif //SUPPORT_HDD_ACCESS
        
        #if defined(SUPPORT_DVB_GUI_NEW)&&defined(DVB_IR_3D_ON)
	    if(Is_Dvb_State() && (full_scrn&SOUND))
	    {
	       need_run_cmd = 1; 
	    }
	    #endif
	    
	    #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
        if(rx == IRC_DVD_USB_CARD_AVIN_DVB)
        {
           need_run_cmd = 1; 
        }
        #endif
        #if defined(SUPPORT_FONT_SWITCH_BY_ANGLE)&&defined(PMP_UI)    //ADD BY YANGLI FOR CHANGE FONT ,2005-10-17 10:50
        if(rx == IRC_ANGLE)
        {
           need_run_cmd = 1; 
        }
        #endif

        #ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
        if((rx==IRC_ANGLE) && cd_type_loaded)
        {
            need_run_cmd = 1;
        }
        #endif
	    
    }else if( (invalid&PROG_PLAY)&&prog_cnt && (!setup_IsSettingPassword()) )
    {        
        #ifdef IR_DBG            
        printf("<ir_invalid 7>\n");
        #endif                  
        need_run_cmd=0;
    }
#ifndef SUPPORT_GOTO_IN_JPEG_STATE//suqiaoli add 2003-11-20
    else if( (invalid&JPEG)&&(Is_JPEG_STATE()) )
    {
        #ifdef IR_DBG            
        printf("<ir_invalid 4>\n");
        #endif                  

        need_run_cmd=0;
    }
#endif
    else if(keep_cmd_code != IR_CODE_MAX_NUM)//2004-3-30 19:19
    {
        #ifdef IR_DBG            
        printf("<ir_invalid 3>\n");
        #endif                  

        need_run_cmd=0;
    }else if(dev_status_flag&DEV_DETECT_CSS)
    {
        #ifdef IR_DBG            
        printf("<ir_invalid 2>\n");
        #endif                  
#ifdef PRE_NEXT_FLAG  //axel, for invalid IRC_NEXT in bad discs 2004/7/12      
        if(rx==IRC_PREV) 
        {
          PRE_FLAG=1;
        #ifdef IR_DBG            
        printf("<PRE_FLAG>\n");
        #endif                  
        }
        else if(rx==IRC_NEXT) 
        {
          NEXT_FLAG=1;
        #ifdef IR_DBG            
        printf("<NEXT_FLAG>\n");
        #endif                  
        }
#endif //#ifdef PRE_NEXT_FLAG    

        need_run_cmd=0;
    }else if((invalid&DVD_PROHIBIT)&&(is_dvd_prohibit_key()||(goto_active==1)) )
    {
        #ifdef IR_DBG            
        printf("<ir_invalid 1>\n");
        #endif  
#ifdef PRE_NEXT_FLAG     //axel, for invalid IRC_NEXT in bad discs 2004/7/12   

        if(rx==IRC_PREV) 
        {
          PRE_FLAG=1;
        #ifdef IR_DBG            
        printf("<PRE_FLAG>\n");
        #endif                  
        }
        else if(rx==IRC_NEXT) 
        {
          NEXT_FLAG=1;
        #ifdef IR_DBG            
        printf("<NEXT_FLAG>\n");
        #endif                  
        }
#endif //PRE_NEXT_FLAG
        if(rep_ab_mode!=REPEAT_FIND_B)
            need_run_cmd=0;
            
        /*if [invalid 1] and SETUP, the setup menu wouldn't be clean, helm 051108*/ 
        if ((full_scrn & SETUP) && (pe_run == 0))   
            need_run_cmd = 1;

    }

    //else if((invalid&BOOKMARK)&&(t_disp==3))//NONO 2-4-29 18:41
     //need_run_cmd=0;
    //else if( (invalid&GAME)&&(Is_GAME_STATE()) )//NONO 2-4-29 18:41
    //need_run_cmd=0;
    
    if(need_run_cmd!=2) {                   //terry,2002/5/16 10:37PM,
#ifdef SETUP_PROGRAM_IN_PLACE_UNDER_16M     // 2004/01/14 yltseng
        extern UINT8   g_uiOSDStatus;
        if( g_uiOSDStatus & OSD_FULL_SCREEN_STATUS_WAIT_ATAPI_CMD_FINISH || 
            g_uiOSDStatus & OSD_FULL_SCREEN_STATUS_WAIT_KERNEL_DECODE_FINISH )
            return;
#endif
            
        if(full_scrn)
        {
            if(StateChkKey[rx] & full_scrn)
            {                               
                //printf("State:%x rx:%d full_scrn:%x\n",StateChkKey[rx],rx,full_scrn);
                #ifdef NEWSTYLE_WINDOW
                if(full_scrn==MESSAGE)
                {
                    //printf("StateChkKey[%d]: %d   full_scrn=:%d\n",rx,StateChkKey[rx],full_scrn);
                    //if(rx == IRC_ZOOM)
                    //{
                    //    invalid_key();
                    //    return;
                    //}

                    exit_browse_func();
                }
                #endif

				#ifdef GPS_DVD//frank.huang 050928 
				extern void GPS_key_board();
				extern void GPS_key_menu();
                if(full_scrn==TOUCH_MENU)
                {
                   	GPS_key_menu();//exit the GPS_TOUCH_MENU
                }
         							
                if(full_scrn==TOUCH_KEYBOARD)
                {
                   	GPS_key_board();//exit the GPS_TOUCH_MENU
                }
                #endif

                #ifdef DOUBLE_TITLE //susu add 2003-8-27 13:55
                if (full_scrn & DOUBLETITLE)
                {   
                    exit_double_title();
                }
                #endif

                if (full_scrn & SOUND)
                {
                    #ifdef RETAIN_3D_IN_PREV_NEXT
                    if(!(rx==IRC_PREV || rx==IRC_NEXT)) //wuxiaofeng 2004-5-24                    
                    #endif
                    cancel_sound();//liweihua 2004-1-13 10:04
                    #ifdef MUSTEK_MULTI_FUNCTION_DIRECTION_KEY
                    if(rx == IRC_ANGLE)
                        return;
                    #endif
                }
                else if (full_scrn & PROGRAM)  //add by shawn 20020218
                {                        
                    #ifdef SDRAM_16Mb_Mode                  
                        #ifdef SDRAM_16MB_IRCMD_RETURN_WHEN_PROGRAM    //linrc 2004-6-10 11:19
                            #ifdef ALCO_DVD_UI
                            if(/*(rx==IRC_ANGLE)||*/(rx==IRC_SUBP)||(rx==IRC_CHANNEL)||(rx==IRC_AUD_LANGUAGE)||
                            #else
                            if((rx==IRC_ANGLE)||(rx==IRC_SUBP)||(rx==IRC_CHANNEL)||
                            #endif
                                (rx==IRC_PREV)||(rx==IRC_NEXT)||(rx==IRC_BACKWARD)||
                                (rx==IRC_FORWARD)||(rx==IRC_RETURN)||(rx==IRC_ZOOM) || 
                                (rx==IRC_SLOW)||(rx==IRC_REPEAT)||(rx==IRC_AB)||(rx==IRC_PAUSE)) 
                                {
                                    #ifdef NEED_DIFF_IR_PANEL_KEY
                                    panel_key_flag = 0;
                                    #endif
                                    return;
                                }
                        #endif                 
                        #ifdef NEW_STYLE_SETUP
                        
                        if (rx ==IRC_SETUP)//zhaoyanhua add 2003-8-8 13:42
                            prog_state = 6;
                        #elif defined ( OP_PLAYMODE )//LIBING 2005-7-14 15:56    
                        if(rx==IRC_MODE)
                        	prog_state = 6;
                        #else
                    prog_state=3;   // 3 means that ircmd_stop pressed when full_scrn==PROGRAM
                    prog_cnt = 0;	//dingzhy add for 1x16 
                    prog_func_clear();	//dingzhy add for 1x16
                        #endif//NEW_STYLE_SETUP                  
                   #ifdef OP_PLAYMODE
                    if (rx ==IRC_ZOOM)
                    {
                    ircmd_clear();
                    return;
                   }
                        #endif               
                    #endif//SDRAM_16Mb_Mode 
                    //#ifdef JIEKE_DVD
                    //return;
                    //#else
                    #ifdef JIEKE_DVD
                    prog_cnt = 0;
                    #endif
                   
                   #ifdef OP_PLAYMODE
                    if (rx ==IRC_ZOOM)
                    { 
                    	ircmd_clear();
                   return;
                    }
                   #endif 
                 
                   #ifndef EXIT_KEY//chenzhao20060124  //hongfeng 2005-12-06
                    prog_func_off();
                   #endif 
#ifdef SDRAM_16Mb_Mode                    
#ifndef ALCO_DVD_UI      
                    resumeMSF=0;//nono 4-1-16 15:27
#endif
#endif//SDRAM_16Mb_Mode                    
            //#endif    
                    // re-load setup module
                    //LoadModual(MODUAL_AP2);
                }
                else if ((full_scrn & SETUP) || (full_scrn & CUSTM))
                {
                    #ifdef NEW_STYLE_SETUP//2003-8-13 18:16
                    if(rx == IRC_TITLEMENU) return;
                    #endif//NEW_STYLE_SETUP
                    
                    #if defined(SDRAM_16Mb_Mode)&& !defined(ALCO_DVD_UI)
                        #ifdef NEW_STYLE_SETUP//zhaoyanhua add 2003-8-8 10:07
                        //In SETUP, enter PROGRAM
                        if (rx == IRC_PROGRAM)
                            prog_state =6;
                        
                        #else
                    prog_state=3;   // 3 means that ircmd_stop pressed when full_scrn==SETUP
                        #endif// NEW_STYLE_SETUP                     
                    #endif //SDRAM_16Mb_Mode 

                    //#ifdef JIEKE_DVD
                    //return;
                    //#else
                    #ifdef KARAOKE_MENU
                    if(rx!=IRC_KARAOKE)
                    KARAOKE_MENU_FLAG=0;
                    #endif
                    
#if defined(NEW_PARENTAL_GUI)||defined(MODIFY_PARENTAL_GUI)
                    //avoid the error:when TRAY OUT enter SETUP ,show error infomation. 
                    //zhaoyanhua add 2004-2-9 11:24
#if defined(NEW_PARENTAL_GUI)
                    if(new_parental_gui)
#elif defined(MODIFY_PARENTAL_GUI)
                    if(parental_gui_flag)
#endif//defined(MODIFY_PARENTAL_GUI)
                    {
#if defined(DVD_AUDIO)//&&defined(NEW_PARENTAL_GUI)//20040302
                         if(pDSV->hid_gp_chk_pwd==2)
                               ExitDVDAudioGUI();
                         else
#endif
                       ExitParentalGUI(); 

                    }else 
                    #endif//NEW_PARENTAL_GUI
#ifdef SETUP_SOME_KEY_NO_RESPONSE//eastech2030
                     //printf("pre test6\n");
                #if defined(ALCO_8200P_MULTIKEY)&&defined(NEED_DIFF_IR_PANEL_KEY)
                if(((play_state==VCD_STATE_OPEN)||(play_state==VCD_STATE_IDLE)) 
                   && (rx==IRC_PAUSE)
                   &&(panel_key_flag && (!(panel_key_flag&(0x01<<2)))))
                {
                    if(panel_key_flag&(0x01<<0))
                    {
                        panel_key_flag = 0;
                        #if defined(ALCO_DVD_UI)&&defined(DVD_SETUP_REENG)  
                        setup_ExitPage();
                        #else
                        ExitSetupPage(1);
                        #endif
                        rx=IRC_NULL;
                        return;
                    }
                }
                else
                #endif//#if defined(ALCO_8200P_MULTIKEY)&&defined(NEED_DIFF_IR_PANEL_KEY)
                    
                #ifdef EXIT_KEY//chenzhao20060208
                if(rx==IRC_EXIT||rx==IRC_POWER||rx==IRC_EJECT)   //add by TOM
                #else
                if(rx==IRC_SETUP||rx==IRC_POWER||rx==IRC_EJECT)   //add by TOM
                #endif
                {
                    #ifdef EXIT_KEY//chenzhao20060210    //hongfeng 2005-12-07
                    if(rx!=IRC_EXIT)
                    #endif
                    #if defined(ALCO_DVD_UI)&&defined(DVD_SETUP_REENG)  
	                    setup_ExitPage();
                    #else
	                    ExitSetupPage(1);
                    #endif
                        
                }
                else
                {
                    #ifdef ALCO_DVD_UI
                    if((play_state==VCD_STATE_OPEN) || (play_state==VCD_STATE_IDLE))
                    {
                        rx=IRC_NULL;
                        #if defined(DVD_SETUP_REENG)  
                        setup_ExitPage();
                        #else
                        ExitSetupPage(1);
                        #endif
                        panel_key_flag = 0;
                        #ifdef PAUSE_PREV_DISPLAY_MACROVISION_VERSION
                        if(MACVersion_count)
                            MACVersion_count=0;
                        #endif
                        return;
                    }
                    else
                        #if defined(DVD_SETUP_REENG)  
                        setup_ExitPage();
                        #else
                        ExitSetupPage(1);    
                        #endif
                        
                    #if defined(ALCO_8200P_MULTIKEY)&&defined(NEED_DIFF_IR_PANEL_KEY)
                    if(rx == IRC_PAUSE)   
                    {
                    if((play_state==VCD_STATE_STOP) && (resumeMSF))
                    {
                        PrintOsdMsg(STR_OS_PRE_STOP,REGION1,0,0);
                        return;
                    }
                        else if(play_state == VCD_STATE_STOP)
                        {
                            PrintOsdMsg(STR_OS_STOP,REGION1,0,0);
                            return;
                        }
                    }
                    #endif//#if defined(ALCO_8200P_MULTIKEY)&&defined(NEED_DIFF_IR_PANEL_KEY)
         
                    
                    #else//#ifdef ALCO_DVD_UI
                    if(rx!=IRC_STOP)
                    {
                        rx=IRC_NULL;
                        return;
                    }
                    else
                    {
                        if(full_scrn & CUSTM)
                    ExitSetupPage(1);
                        if(full_scrn & SETUP)
                        {
                            rx=IRC_NULL;
                            return;
                        }
                    }
                    #endif////#ifdef ALCO_DVD_UI
                }
#else
                    #ifdef EXIT_KEY//chenzhao20060124    //hongfeng 2005-12-07
                    if(rx!=IRC_EXIT)
                    #endif
                    ExitSetupPage(1);

			#ifdef STOP_KEY_ONLY_CANCLE_SETUPMENU_AT_SETUPMENU//tianye 200607
                	 extern UINT8 DVD2DVB_switch_flag;

                   	if((rx == IRC_STOP)&&(DVD2DVB_switch_flag == 0))
                   	 {
                        rx=IRC_NULL;
                        return;
                  	  }
			#endif//end=> #ifdef STOP_KEY_ONLY_CANCLE_SETUPMENU_AT_SETUPMENU

#endif//SETUP_SOME_KEY_NO_RESPONSE
                    
                    #if defined(SDRAM_16Mb_Mode) && !defined(STOP_SHOW_SETUP)//libing modify it 2005-6-17 13:17
                    //avoid the bug when otherIR key (except SETUP),
                    //"DISPLAY" cause error.
                    //zhaoyanhua add 2003-11-13 11:36
                    #ifdef ALCO_DVD_UI		//zhongshan for warning 2006-3-1 11:16
                    if(old_t_disp)
                    {
                        t_disp=old_t_disp;
                        DispPolling(3);
                    }
                    #endif
                    #ifndef ALCO_DVD_UI                    
                    resumeMSF=0;//nono 4-1-16 15:28
                    #endif
                    #endif

                    #ifdef MUSTEK_PORTABLE_DVD
                    if (old_t_disp)
                    {
                        t_disp=old_t_disp;
                        DispPolling(2);
                    }
                    #endif
                    
                    //#endif
                }
                #ifdef SUPPORT_FUNCTION_MENU
                else if(full_scrn & SETUP_PLUS)
                {
                    ExitSetupPage(0);
                }
                #endif
                else if(full_scrn & GOTO)
                #ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-11-5 22:39
                    ExitGOTOPage(); 
                #else
                    ircmd_goto();
                #endif

                #ifdef SUPPORT_REP_READ
                else if(full_scrn & READ)
                {           
                    CancelRead();      
                }
                #endif
                
                else if(full_scrn & MARK)     //Jeff 20020416
                {
                    // alan 0429 solve goto fade out and fade in again  when full_scrn in mark mode
                    if (rx != IRC_GOTO)
                        ircmd_book();
                }
#if (defined VIRTUAL_KEYBOARD) && (defined DIV_GOTO_DISPLAY) //zhaoyanhua add 2004-2-16 16:58
                else if (full_scrn & KEYBOARD)
                {
                    ircmd_virtual_keyboard();
                }
#endif
#ifdef SWITCH_CD_CARD_USB//liweihua 2004-6-13 14:51
                else if(full_scrn & SWITCH_GUI)
                {
                    ircmd_switch_cd_card_usb();   
                }
#endif
                else
                    ClearOsdMsg(1);
#ifdef RETAIN_3D_IN_PREV_NEXT
         if((full_scrn&SOUND) && !((rx==IRC_PREV || rx==IRC_NEXT))    //wuxiaofeng 2004-5-24
    #ifdef  CF_CARD_WRITE
                || (!(full_scrn & PERIPHERAL))      //wuxiaofeng if define card, use preview for IR input
    #endif
                )
#else 
    #ifdef  CF_CARD_WRITE
        if(!(full_scrn & PERIPHERAL))       //wuxiaofeng if define card, use preview for IR input
    #endif
#endif
                //wanghaoying changed 2003-12-9 14:21
                #ifndef EXIT_KEY  //chenzhao20060124  //hongfeng 2005-12-06
                full_scrn = 0;            
                #endif
                #ifdef SOUND_NO_KEYPAGE                
                bEqDisplay = 0;  
                #endif
                //terry,0513,yuxing , 
                //bug1: cdda , display->goto->step or slow            
                //bug2: cdda , goto->step , goto highlight isn't cleared.
                display_again=1;
            } //if(StateChkKey[rx] & full_scrn)
            
            #ifdef  TITLE_RETURN_CANCEL_SETUP
            if((full_scrn&SETUP)&&((rx==IRC_RETURN)||(rx==IRC_TITLE_RETURN)))
            {
                #ifdef DVD_SETUP_REENG  
                setup_ExitPage();
                #else
                ExitSetupPage(1);    
                #endif
                
                rx=IRC_NULL;
                return;
            }
            #endif
            
        } //if(full_scrn)
    } //if(need_run_cmd!=2)
#ifndef IR_TOOL
    #ifdef IR_DBG
    printf("invalid:%x need_run_cmd:%x play_state:%x\n",invalid,need_run_cmd,play_state);
    #endif
#endif
    if((rx > IRC_P10) && (rx != IRC_SELECT)) {
        #ifdef SUPPORT_DISPLAY_MENU
        if(!In_Goto_Menu())
        #endif//end #ifdef SUPPORT_DISPLAY_MENU
        init_ir_num();
    }
#ifdef USER_VERSION_INFORMATION
    extern BYTE check_password_flag;
#endif
    if(need_run_cmd==1)
    {
        //nono 2-6-2 15:09
        //#ifndef FUSS_DVD
        if(invalid&CN_REP)
	 #ifdef VCD_SHOW_MENU_INFO_NOT_CANCEL_REPEAT
	 if(rx != IRC_PBC)  
	#endif//#ifdef VCD_SHOW_MENU_INFO_NOT_CANCEL_REPEAT	
            cancel_rep();
        //#endif

        if( (invalid&CN_INTRO)&&bIntro )
        {
        #ifdef GOTO_BOOK_KEY_NOT_CANCEL_INTRO
          if((rx==IRC_BOOK)||(rx==IRC_GOTO))
				bIntro=1;
			else
	   	#endif
            bIntro=0;
        }
        if( (rx==IRC_EJECT)&&(dev_status_flag&ATAPI_WAIT_TIME_OUT))
        {
            keep_cmd_code=rx;
            if(!is_user_opened()) {
                OSD1000ISP_STATUS(OSDISP_OC_OPEN, OSDIR_OPEN);

                PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
            }
        } else
        {
            //terry,0512 , avoid show error osd msg
            ir_osd_post_show=1;
            #ifdef SUPPORT_SPI_QSI
            if( /*(rx == IRC_STOP) || */(rx == IRC_PLAY) /*|| (rx == IRC_PAUSE)*/ )
                spi_cmd_func_table[uSpiRxData]();
            else
            #endif
            irc_func_table[rx]();
            #ifdef NEED_DIFF_IR_PANEL_KEY
            if((rx == IRC_PREV) || (rx == IRC_NEXT)||((play_state!=VCD_STATE_STOP) /*&& (play_state!=VCD_STATE_PAUSE)*/))
            {
              if(panel_key_flag & (0x01<<2))
                 panel_key_flag = 0;
            }
            #endif
#ifdef USER_VERSION_INFORMATION        //sunzhh add for after showing USER_VERSION_INFORMATION,there is hand showing (east)
            if(((RegionOnOff[1][2]== STR_OS_NO)&&(check_password_flag == 1))||((rx==IRC_SETUP)&&(play_state==VCD_STATE_OPEN)))//||(rx==IRC_SETUP)))//(play_state==VCD_STATE_OPEN))
            {
                ir_osd_post_show = 0;
                check_password_flag =0;
            }
#endif
            if(ir_osd_post_show>1) {
                //#ifdef DVDRELEASE//2-7-29 16:00
                osdshow(1,osd_buf);//2-8-1 20:15
                //#else
                //osd_tog_region(1,OSD_ON); 
                //#endif 
            }
            ir_osd_post_show=0;  
        }

        //terry,0513,reduce code
        display_again=1;            
    } else if(need_run_cmd!=2)
    {
        #ifdef NEED_DIFF_IR_PANEL_KEY
        if(panel_key_flag & (0x01<<2))
          panel_key_flag &= ~(0x01<<2);
        #endif
        
        #ifdef PAUSE_PREV_DISPLAY_MACROVISION_VERSION
        //#ifdef SDRAM_16Mb_Mode
        if(MACVersion_count>=2)
          MACVersion_count = 0;
        else if(!(MACVersion_count && (rx==IRC_PAUSE)))
        //#endif
        #endif
        invalid_key();
    }
   
#ifdef SUPPORT_MP3_ENCODER
	if(rx == IRC_SUBP)
	{
	    
	 if((cd_type == CDDA) && (detect_type) && !(IS_AUDIF_CODING_MODE_CD_MP3_ENCODER)&&(ripping_flag==0) )
		{
			// flow restart
	       ripping_flag=1;
	       cancel_rep(); 
	  
	   if(shuffle_flag==1)
	   {
	      shuffle_flag = 0;
	      psprintf(RegionValStr[REGION2], "RANDOM OFF");
	      PrintOsdMsg(STR_OS_SPACE, REGION2, 1, 1);
	    }
        #ifdef CD_RIPPING_CANCEL_CD_INTRO//chenzhao 2006-3-24 17:56 .
        if(bIntro)
        {
            ircmd_preview();
        }
        #endif
	  
			if(mp3_encoder_state == test_stop)
			{
				fs_mp3_encoder_restart();
			}

			if(mp3_encoder_state == test_device_exist)
			{
				printf("\n\nMP3_ENCODER init device\n\n");
				fs_mp3_encoder_main();
				printf("\n\nMP3_ENCODER init FS\n\n");
				fs_mp3_encoder_main();
				printf("\n\nMP3_ENCODER test DIR\n\n");
				fs_mp3_encoder_main();
			}

			if(mp3_encoder_state == test_wait_command)
			{

				mp3_encoder_state = test_target_file;
				ircmd_post_func(CMD_SELECT | v11_trk_now);
			}

			if(mp3_encoder_state == test_stop)
			{
				fs_mp3_encoder_main();
			}
		}
		else if((ripping_flag==1))
		{
	  
		 ripping_flag=0;
		 change_speed_flag=0;
	  
        #if defined(ORITRON_HK_DVD)||defined(OP_MP3_ENCODER_UI)//chenzhao20060208
	     call_ir_func(IRC_NEXT);
	    #else 
	     stop_current_ripping(); //qinhua,use it close file 060225
	     psprintf(RegionValStr[REGION1], "CLOSE FILE ");
	     PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	    #endif
	}

	}
    #if defined(ORITRON_HK_DVD)||defined(OP_MP3_ENCODER_UI)//chenzhao20060208
	if(rx == IRC_ANGLE)
      #else
	if(rx == 0x62)
      #endif 	
	{
		if((IS_AUDIF_CODING_MODE_CD_MP3_ENCODER)&&(change_speed_flag==0))
		{
			change_encode_speed();
		  change_speed_flag=1;
		  psprintf(RegionValStr[REGION1], "RECODER 2X ");
	      PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
		
		}
		else if (change_speed_flag==1)  //qinhua ,2005-11-9 11:11
		
		{  change_encode_speed();
		   change_speed_flag=0;
		   psprintf(RegionValStr[REGION1], "RECODER NORMAL ");
	       PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
		}
	}
#endif//#ifdef SUPPORT_MP3_ENCODER
    
    if(Is_JPEG_PLAY_STATE())
    {
        ShowJpegResolutionByAngleKey( rx );     // 2006/08/1 Joshua        
    }
    else
    {
        ShowDSPCodecNameByAngleKey( rx );       // 2005/02/18 yltseng
        ChangeFontByAngleKey( rx );             // 2005/03/10 yltseng    
    }    
    
    
    
    if( (display_again)&&(t_disp) )
    {//terry,0513 ,reduce code
        t_disp=t_disp%10;
        t_disp+=10;     
    }

    #ifdef NEW_STYLE_SETUP    
    printf("===>logo_type:%x sys_cmd:%x setup_state:%x full_scrn:%x\n",logo_type,sys_cmd,setup_state,full_scrn & SETUP);
    //if (full_scrn & SETUP)//terry,2003/9/13 01:04AM
    {
        #ifdef SDRAM_16Mb_Mode
        if( (logo_type == 1)&&(play_state!=VCD_STATE_NORMAL)&&(prog_state==0)&&((cd_type_loaded!=CDROM)||(Is_MP3_STATE()==1)) )
        #else
    if( (logo_type == 1)&&(play_state!=VCD_STATE_NORMAL)&&(setup_state==0)&&((cd_type_loaded!=CDROM)||(Is_MP3_STATE()==1)) )
        #endif //SDRAM_16Mb_Mode  
        ShowTitle();
    }
    #endif// NEW_STYLE_SETUP    
}


/* wanghaoying marked 2004-7-1 16:51, for not use any more
#if defined(SUPPORT_TUNER)  //freyman add 2002-8-28 21:40
void ircmd_power_volume(BYTE rx)
{   
    extern void set_volume(BYTE x);
    if(rx==IRC_VOLUME_UP)
        if(audio_volume<15)
            audio_volume++;
    if(rx==IRC_VOLUME_DN)
        if(audio_volume>0)
            audio_volume--;
    set_volume(2*audio_volume+50);

    #ifdef VFD_VOLUME_DISPLAY
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_volume(0);
    #endif
}
#endif
*/

#include "password.c"
#ifdef SUPPORT_APOGEE_AMP  //huziqin
extern BYTE amp_enter_flag;
#endif


#ifdef SUPPORT_RECEIVER //huziqin 2004-2-26
/*
BYTE call_ir_func_receiver_hook(BYTE rx)
  I seperate this function from call_ir_func(),to make code
  easy to read.
  return 0-->don't return
  return 1-->return
*/

//huziqin 2006-4-19 removed


#ifdef AVOID_READDISC_WHEN_STARTUP  //xyy add for Oritron
extern UINT16 uStartCounter;
extern UINT16 uCounterFlag;
#endif
#include "radio.h"

BYTE call_ir_func_receiver_hook(BYTE rx)
{
    #ifndef SUPPORT_NO_DVD_MODE_TO_EJECT //chenzhao20060120
	if((system_state == SYSTEM_DOING_AV1)||(system_state == SYSTEM_DOING_AV2)\
	   ||(system_state == SYSTEM_DOING_SPDIF) 
	   || (system_state == SYSTEM_DOING_TUNER))//xyy add for Oritron 2004-11-8 15:14
       #ifdef SUPPORT_SCART_IN 	   
	   || (system_state == SYSTEM_DOING_SCART_IN)
       #endif	   
       #ifdef XM_MODEL
	   || (system_state == SYSTEM_DOING_XM)
       #endif
	{   
		if(rx == IRC_EJECT)
		{
			return 1;
		}
	}
   #endif//#ifndef SUPPORT_NO_DVD_MODE_TO_EJECT //chenzhao20060120
        //for invalid state hongfeng 2005-07-14
    if(0
    #if !defined(SELECT_DVD_NEXT_DISC_IN_A_KEY) && !defined(SELECT_DVD_MEDIA_IN_A_KEY) //chenzhao 20060112
    ||((current_rcvr_mode == RECEIVER_MODE_DVD)&&(rx == IRC_RCVR_SELECT_DVD))
    #endif
    ||((current_rcvr_mode == RECEIVER_MODE_AV1)&&(rx == IRC_RCVR_SELECT_AV1))
    ||((current_rcvr_mode == RECEIVER_MODE_AV2)&&(rx == IRC_RCVR_SELECT_AV2))
    ||((current_rcvr_mode == RECEIVER_MODE_TUNER)&&(rx == IRC_RCVR_SELECT_TUNER))
    ||((current_rcvr_mode == RECEIVER_MODE_SPDIF)&&(rx == IRC_RCVR_SELECT_SPDIF))
    )
        {
        invalid_key();
        return 1;
        }

 #ifdef TREBLE_BASS_EQ_MENU_INTERFACE
    if(call_ir_func_tone_menu(rx))
        return 1;
 #endif
 
 #ifdef SUPPORT_VFD_MENU//chenzhao 20060118
     if(current_rcvr_mode!=RECEIVER_MODE_DVD)
        if(call_ir_func_vfd_menu(rx))
            return 1;
 #endif
 
 #ifdef RECEIVER_USE_PSCAN_BUTTON
    if (rx == IRC_P_SCAN)
    {
        rx = IRC_RCVR_NEXT_MODE;
    }
 #endif

    //remove RECEIVER_USE_GAME_KEY_SWITCH_MODE.chenzhao20060120
 #ifdef HAS_TUNER_AM_MODE            
 if((rx == IRC_RCVR_FUNCTION_KEY)||(rx == IRC_RCVR_NEXT_MODE))
 {
     if(current_rcvr_mode==RECEIVER_MODE_TUNER && !tuner.bandswitch)
         rx = IRC_GAME;
     else if(current_rcvr_mode==RECEIVER_MODE_TUNER && tuner.bandswitch) //AM MODD SWITCH av1
    {
          tuner.bandswitch=0;
          save_tuner_E2PROM();//chenzhao20051102
         printf("switch to next not tuner Mode \n");
     }
    }
 #endif

#if  1 //TAS_5026_PWM//wuzhj 2004/10/09
  
  #ifndef SUPPORT_Radio_NEW_UI  //wuzhj  2004/12/10   
  if(IRC_ANGLE==rx)
    {
    #ifdef MONE_DSP24_SHOW_CODEC_NAME_BY_ANGLE_KEY  //hongfeng add for receiver 2005-06-16
        ShowDSPCodecNameByAngleKey( rx );       // 2005/02/18 yltseng
        return 1;
    #elif defined(RECEIVER_USE_ANGLE_KEY_ADJUST_VOLUME)
        subvol_next_channel();
        return 1;
    #else
        return 0;
    #endif
    }  

  #else
   if(IRC_ANGLE==rx)
    {
      if(system_state == SYSTEM_DOING_TUNER)
        {
            return 1;
        }
        else
        {
            #ifdef MONE_DSP24_SHOW_CODEC_NAME_BY_ANGLE_KEY  //hongfeng add for receiver 2005-06-16
                ShowDSPCodecNameByAngleKey( rx );       // 2005/02/18 yltseng
                return 1;
            #elif defined(RECEIVER_USE_ANGLE_KEY_ADJUST_VOLUME)
                subvol_next_channel();
                return 1;
            #else
                return 0;
            #endif
         }
       
      }  
   #endif
#endif  

 
 #ifdef RECEIVER_USE_DISPLAY_BUTTON
    if (rx == IRC_DISPLAY)
    {
        rx = IRC_RCVR_ANALOG_DIGITAL;
    }
 #endif
#ifdef SUPPORT_RECEIVER//DOLBY_AMP_VOLUME_CTRL
//wuzhj 2004/12/1
#ifndef SUPPORT_Radio_NEW_UI  //wuzhj  2004/12/10
    if((rx == IRC_VOLUME_DN)||(rx == IRC_VOLUME_UP)||(rx == IRC_MUTE))
        {
        //ircmd_prologic();
        return 0;
    }
#endif
#ifdef SUPPORT_BASS_TREBLE
    if(rx == IRC_SET_BASS)
    {
        ircmd_set_bass();
        return 1;
    }

    if(rx == IRC_SET_TRE)
    {
        ircmd_set_treble();
        return 1;
    }
    
#endif
#endif
#ifdef USE_PROLOGIC_II_KEY
//wuzhj 2004/12/1
#ifndef SUPPORT_Radio_NEW_UI  //wuzhj  2004/12/10
    if(rx == IRC_PROLOGIC)
        {
        //ircmd_prologic();
        return 0;
    }
#endif
#endif
 
#if defined(AMP_SUPPORT_EQ)
if(rx == IRC_3D)
   {
      amp_toggle_EQ();
       return 1;
   }
#endif
#if 0//def SUPPORT_RECEIVER_EQ     //chenzhao marked it.20060107//hongfeng 2005-02-19
if((current_rcvr_mode!=RECEIVER_MODE_DVD)&&(rx == IRC_3D))
{
    ircmd_EQ();
    return 1;
}
#endif
#ifdef SUPPORT_RECEIVER_3D     //hongfeng 2005-02-19
if(current_rcvr_mode!=RECEIVER_MODE_DVD)
{
 if(rx == IRC_3D)
        {
       ircmd_3dsound();
        return 1;
    }
if(full_scrn == SOUND)
{
if(rx == IRC_RIGHT)
        {
       ircmd_right();
        return 1;
    }
if(rx == IRC_LEFT)
        {
       ircmd_left();
        return 1;
    }
if(rx == IRC_UP)
        {
       ircmd_up();
        return 1;
    }
if(rx == IRC_DOWN)
        {
       ircmd_down();
        return 1;
    }
if(rx == IRC_SELECT)
        {
       ircmd_select();
        return 1;
    }
}
}
#endif
  // Simon:  1/7/2004
 // If we eject, switch automatically back to DVD mode
  if ((rx == IRC_EJECT) && (current_rcvr_mode != RECEIVER_MODE_DVD))
 {
    system_state = SYSTEM_EJECT_CHANGE;
    return 1;
 }

    if(0
        #if defined(SUPPORT_RECEIVER_EQ)
        ||(rx == IRC_EQ)
        #endif
        #ifdef SUPPORT_EX_BASS_FUNC
        ||(rx == IRC_EX_BASS)
        #endif
        #ifdef IR_SLEEP//chenzhao20060208
        ||(rx == IRC_SLEEP)
        #endif
        )//chenzhao20060208 add for active click function.
    {
        return 0;
    }
    #ifdef SUPPORT_NO_DVD_MODE_TO_PLAY
    if ((rx == IRC_PLAY_RESUME) && (current_rcvr_mode != RECEIVER_MODE_DVD))
    {
        rx = IRC_RCVR_SELECT_DVD;
    }
    #endif
//xyy delete 2004-8-17 
/*
#if defined(BAND_SWITCH_KEY)
    if((system_state!= SYSTEM_DOING_TUNER)&&(rx==IRC_RCVR_BAND))
    {
        invalid_key();
        return 1;   
    }
#endif
*/
    if ((rx == IRC_RCVR_NEXT_MODE)
        || (rx == IRC_RCVR_FUNCTION_KEY)//chenzhao20060120
     #ifdef SUPPORT_VIDEO_WITH_SPDIF  //xyy 2004-8-11
     || (rx == IRC_RCVR_ANALOG_DIGITAL)
     #endif
    #if defined(EQ_SWITCH_KEY)
		||((rx == IRC_RCVR_EQ)&&(current_rcvr_mode == RECEIVER_MODE_DVD))
    #endif
    #if defined(BASS_SWITCH_KEY)
        ||(rx == IRC_RCVR_LEVEL)
    #endif
    #if defined(TREBLE_SWITCH_KEY)
    ||(rx == IRC_RCVR_TONE)
#endif
        ) //end if condition sentence
 {
#ifdef AVOID_READDISC_WHEN_STARTUP  //xyy add for Oritron
 		if((rx==IRC_RCVR_NEXT_MODE && uCounterFlag==0)/*||(system_state==SYSTEM_OPEN)*/)
 		{
 			return 1;
 		}
#endif
    irc_func_table[(BYTE)rx]();
    return 1;
 }

 // If one of the specific mode buttons is pressed, call ircmd_rcvr_select_mode
    //xulf  modified 2004-3-7
    else if ((rx >= IRC_RCVR_SELECT_DVD) && (rx <= IRC_RCVR_SELECT_DUMMY))  // mode buttons
    {
        rx = rx - IRC_RCVR_SELECT_DVD;      // mode button values start at 0x6f
        if (rcvr_support_bits & (1 << rx))  // check to see if mode is enabled
            ircmd_rcvr_select_mode(rx);
        else
        {
            invalid_key();          // unsupported mode
        }
        return 1;
    }
    #ifdef XM_MODEL //chenzhao20060120//fcr 2005-11-2 19:51
	else if (current_rcvr_mode == RECEIVER_MODE_XM)
	{
		if(Send_XM_key(rx))return 1;
 
		invalid_key(); //fixed by joke
		return 1;
	}
    #endif//#ifdef XM_MODEL
 // Don't let user press any other button other than power if we aren't in DVD mode
    else if ((current_rcvr_mode != RECEIVER_MODE_DVD) && (rx != IRC_POWER))
    {
    
#if defined(RADIO_2006) //huziqin 2006-4-19
        call_ir_func_tuner(rx);   
                return 1;
#endif     
    
        invalid_key();
		return 1;
	}
	return 0;
}
#endif//SUPPORT_RECEIVER
#ifdef SUPPORT_DVB_BOOKING
extern UINT8 iCountTime;
#endif 

#ifdef SCALER_6500
#ifdef SUPPORT_LOADER_OPEN_TV_SYSTEM
BYTE load_is_open=0, Eject_operate = 0;
#endif
#endif

void call_ir_func(BYTE rx)
{   
//gerry,to avoid gpio key bugs,2004-6-3 9:36
    extern UINT32 save_srn_start_t;
    save_srn_start_t = get_rtc_val();
	//Qiaohuilin:2005-9-1
	#ifdef MUSTEK_LCD_DRIVE_BITEK
	{
		rx=LCD_DISPATCH_Go(rx);
		if(rx==IRC_NULL)
			return;
	}
	#endif

    #ifdef AD_TCL//2004-3-22 13:12 lijd
    jpg_ps=1;
    menu_id=0;
    #endif 
#ifdef TP6317_PANNEL   //yaowh add 04-10-25
   if(TP6317_Power == 2)
   {
      return ;
   }
#endif

#ifdef LINE_IN_ENCODE
       if(rx == IRC_1)
       {
        if(line_in_flag == 0)
        {
      //      printf("==========  line in  ==========\n");
           rx = IRC_STOP;
            linein_state=1;
            line_in_flag = 1;
            encoder_type = line_in_encoder;
    //io_write_wait("wmwmwmwm546789...\n");
            if (t_disp) 
            {
              DispFadeOut();
              disp_mode=0;
            }       
             //ircmd_rcvr_select_mode(RECEIVER_MODE_AV1);
             //return;
        }
        else if(line_in_flag == 1)
        {
            if(IS_AUDIF_CODING_MODE_CD_MP3_ENCODER)
            {
            //printf("==========  normal  ============\n");
            linein_state=2;
            line_in_flag = 0;
            encoder_type = real_time_encoder;
           // ircmd_rcvr_select_mode(RECEIVER_MODE_DVD);
            //return;
            }

       }
       }
#endif //LINE_IN_ENCODE


#ifdef SUPPORT_DVB_BOOKING
    if(iCountTime>0)
    {
        invalid_key();
         return;
    }
#endif 
    #ifdef MODE_SWITCH_DELAY
   #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB	
    if(mode_key_delay_cnt && (rx==IRC_DVD_USB_CARD_AVIN_DVB))
    #else//else=>#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    if(mode_key_delay_cnt && (rx==IRC_DVB_DVD))	
    #endif//end=> #ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
    {
        //printf_w("mode_key_delay_cnt:%d,return............\n",mode_key_delay_cnt);
        invalid_key();
        return;
    }
    
    if((read_iso_file_state) && (rx!=IRC_POWER))
    {
        //printf_w("read iso file now,return............\n");
        if(cd_type_loaded  ==  CDROM)//20060421 tiany add fix SVCD ir  err
        return;
    }
    #endif
    
    #ifdef VIDEO_IN_CONTROL
    if(AVin_step && (rx!=IRC_POWER))
      return IRC_NULL;
    #endif

    
    //printf("call ir in\n");    
    if(rx<IR_CODE_MAX_NUM)
    {
#ifdef AUDIO_SHOW_SAVER
        ir_cmd_temp = rx;   //yw 020904
#endif

/*
temporary used for oritron receiver
*/
#ifdef SUPPORT_POWER_OFF_CLOCK_FUNC  //xyy 2004-10-12
	if(rx==IRC_SET_CLOCK)
	{
		if(system_state==SYSTEM_DOING_CLOCK_FUNC)
			ircmd_set_clock();
		else
			invalid_key();
		return;
	}
#endif

#ifdef AD_TCL//2004-3-22 13:12 lijd     
   if((rx==IRC_CHANNEL||rx==IRC_EFFECT||rx==IRC_3D)&&(Is_JPEG_STATE()))
       rx=IRC_NULL;
   if((play_state==VCD_STATE_OPEN)&&(rx==IRC_CHANNEL))
       rx=IRC_P_SCAN;    
   else if((Is_JPEG_SlideMode())&&(rx==IRC_ROOT_MENU))
   {
        menu_id=1;
        rx==IRC_STOP;   
   }    
#endif

#ifdef SUPPORT_RECEIVER  //huziqn 2004-2-26
    if(call_ir_func_receiver_hook(rx))
        return;
#endif  // End:  #ifdef SUPPORT_RECEIVER


#ifdef SCALER_6500 // benson 2005/11/23 11:49下午 for op
//#include "setup_VA.h"

        extern BYTE hdcp_auth_fail;//libing 2006/4/1 for DVI-TV play CSS problem
        extern BYTE CSSEnable;
        
        //unsigned decfmt = get_decode_format();

     if(rx==IRC_EJECT){ 
		 if(CSSEnable!=0)//libing 2006/4/1 for DVI-TV play CSS problem
		 {
		 	//printf("\n ************* hdcp_auth_fail = %d ************* \n",hdcp_auth_fail);
     	      CSSEnable=0;     
		 	hdcp_auth_fail = 0;
		 }     

#ifdef SUPPORT_LOADER_OPEN_TV_SYSTEM      	      
extern BYTE X, Y, TV_MODE     	     
extern BYTE AUTO_Setup_Position, PAL_Setup_Position, NTSC_Setup_Position;      	      
     	      if(load_is_open == 0){
     	      	  load_is_open = 1;

                  /* 
                  ** for OP AUTO operation, the TV system return to default setting
                  ** while ejection.
                  */
                  if ( ((TV_MODE == STR_OS_NTSC) && (setup_VA[SETUP_VA_TV_SYS] != NTSC_Setup_Position)) ||
                       ((TV_MODE == STR_OS_PAL) && (setup_VA[SETUP_VA_TV_SYS] != PAL_Setup_Position))
                         &&(setup_VA[SETUP_VA_TV_SYS] == AUTO_Setup_Position)){
                       Eject_operate = 1;
                       dvi311_tv_mode = TV_MODE;                                                       
                       exe_setup_function (STR_OS_TV_SYS, dvi311_tv_mode, 1); 
                  }  
              }
              else
                  load_is_open = 0;
#endif //SUPPORT_LOADER_OPEN_TV_SYSTEM             
    }        	     	
#endif		

    #ifdef ZOOM_CLEAR_IN_ONE_KEY//chenzhao20060220
    if((IRC_ZOOM==rx)&&((full_scrn&GOTO)||(full_scrn&PROGRAM)||(full_scrn&MARK)||(full_scrn & SETUP) || (full_scrn & CUSTM)))
        rx=IRC_CLEAR;
    #endif

#ifdef AD_TCL
    if((cd_type_loaded==CDDVD)&&(get_tt_info(DISP_TT)==0)&&(rx==IRC_NEXT||rx==IRC_PREV))
        rx=IRC_NULL;
#endif  

#if defined(JPG_EFFECT)
        //qinhua,mark because at jpeg list select "PAUSE->PLAY",
        // then after slide jpeg ,play state can been switched PAUSE,2006-2-18 15:26
        if(( (rx == IRC_PAUSE)||(rx == IRC_ONLY_PAUSE) )&&(Is_JPEG_SlideMode()))
        {
            //printf("Now pause");
            pause_flag=1;
        }
#endif

#if defined(JPG_EFFECT)&&defined(CALL_JPGEFFECT_HELP)
//      jpeg_call_help();
        if(Jpg_Show_Usage_Flag)
        {
        #ifdef HELP_BMP_GUI
            if((rx!=IRC_POWER)&&(rx!=IRC_EJECT)&&(rx!=IRC_STOP)&&(rx!=IRC_SELECT)&&(rx != IRC_PLAY_SELECT)&&(rx!=IRC_NEXT)&&(rx != IRC_PREV)&&(rx !=IRC_PREVIEW))
        #else
            if((rx!=IRC_POWER)&&(rx!=IRC_EJECT)&&(rx!=IRC_STOP)&&(rx!=IRC_SELECT)&&(rx != IRC_PLAY_SELECT))
        #endif
                return;

#ifdef HELP_BMP_GUI
            if (rx == IRC_NEXT)
            {
                if (Jpg_Show_Usage_Page < 4)
                {    
                    Jpg_Show_Usage_Page ++;
                    Jpg_Show_Usage();
                    return;
                }
                else
                {
                    help_stop_flag = 1;
                    rx = IRC_STOP;
                }                
            }
            
            if (rx == IRC_PREV)
            {
                if (Jpg_Show_Usage_Page > 0)
                {    
                    Jpg_Show_Usage_Page --;
                    Jpg_Show_Usage();
                return;
                }
                else
                {
                    help_stop_flag = 1;
                    rx = IRC_STOP;
                }                
            }
            if (rx == IRC_PREVIEW)//when select "preview" button continully,show Mp3 Gui
            {
                    help_stop_flag = 1;
                    rx = IRC_STOP;                
            }               
#endif      
        

            if( (rx == IRC_SELECT)||(rx == IRC_PLAY_SELECT) )
            {
                if(Jpg_Show_Usage_Page < HELP_PAGE_COUNT)
                {
                    Jpg_Show_Usage_Page++;
                    Jpg_Show_Usage();
                    return;
                }
                else if(Jpg_Show_Usage_Page == HELP_PAGE_COUNT)
                {
//wanghaoying marked below 2004-7-1 14:01, for it is repetitive
//              #if !defined(MP3_JPEG_COWORK)//2004-05-18 Clear the flag in fs_nav_jpg.c
              Jpg_Show_Usage_Flag=0;//nono open it.4-7-26 15:41
//              #endif  
                    Jpg_Show_Usage_Page=0;
                    
                    #ifdef FS_BMP_GUI
                    help_stop_flag = 1;
                    #endif

                    rx = IRC_STOP;
                }
            }

            if(rx == IRC_STOP)
            {
//wanghaoying marked below 2004-7-1 14:01, for it is repetitive
//          #ifndef  MP3_JPEG_COWORK//2004-05-18 Clear the flag in fs_nav_jpg.c
              Jpg_Show_Usage_Flag=0;//nono open it.4-7-26 15:41
//          #endif  
                    Jpg_Show_Usage_Page=0;

#ifdef  SDRAM_16Mb_Mode                 
                 ircmd_stop();
#else// SDRAM_16Mb_Mode
                            if(pFsJpeg->gifsState!=3)   //2003/10/27 axelchen for HELP screen flickering
                            {
                    delay_srv_10ms(2);
				   	#ifdef MEM_GRAPH_LARGE //2006-06-02, mimitsai add for HD ui.
                    config_memory(MEMORY_GRAPH_NTSC);    //Large , not SMALL, but NTSC 
                    #else
                    config_memory(MEMORY_GRAPH_SMALL);
                    #endif
                    setup_tv_format(tv_format);
                    play_state = VCD_STATE_MP3_FILELIST;
                    FSGUI_Menu();
                    delay_srv_10ms(2);
            }
#endif//SDRAM_16Mb_Mode
                         }
        }
    #endif //#ifdef JPG_EFFECT

        if(play_state==VCD_STATE_POWER)
        {   
 
//huziqin removed it 2006-4-19

            //if(rx==IRC_POWER)
            //    irc_func_table[(BYTE)rx]();


            irc_func_table[(BYTE)rx]();

        }    
        else
        {//move to password.c,terry,2003/8/20 06:47PM
            chk_password(rx);
        }
    }
}


extern const BYTE ir_mapcode[256];

BYTE GetReverse(BYTE bIRCode)
{
    BYTE i;

    for (i = 0; i < 256; i++)
    {
        if (ir_mapcode[i] == bIRCode)
            break;
    }

    if (bIRCode == 255)
        return 0xff;

    return revn(i, 8);
}

//nono 5-5-9 15:03 move to ir_parser_special_func.c
#include "ir_parser_special_func.c"



extern UINT16 Jpeg_GetIRCode()//wurh add for all IR types when jpeg break ir code
{
    UINT16 rx = regs0->iop_data[IR_PORT];
    #if defined(IR_PHILIPS)||defined(IR_THOMSON_6BIT)
        rx = rx & 0x003f;
	#elif defined(IR_PHILIPS_EASTECH)||defined(IR_THOMSON)||defined(IR_KONKA)||defined(IR_TDP101)||defined(IR_HT220MCU)
        rx = rx & 0x00ff;
    #else
        rx = reverse_fun(rx);
    #endif
    return rx;    
}


extern UINT16 GetIRCode()
{
    // 2004/09/23 yltseng
    extern const BYTE ir_mapcode[256];
    UINT16 rx = regs0->iop_data[IR_PORT];
    
    #ifndef SUPPORT_SPI
    if( rx & IR_RDY )
    #endif
    {
        #if defined(IR_NEC)||defined(IR_M3004)||defined(IR_ORITRON)||defined(IR_ORITRON_RCVR)//LIJD 2005-6-16 22:27
        rx = reverse_fun(rx);
	#elif defined(IR_PHILIPS_EASTECH)       //wurh add for philips rc6
        rx = rx & 0x00ff;
        #else
        rx = rx&0x003f;
        #endif

        #if defined(IR30)
        if(regs0->iop_data[6] == IR_ADDR_PATT)
        {
            switch(rx)
            {
            case 0x30:
            case 0x32:
            case 0x33:
            case 0x34:
                rx+=0x10;
                break;
            default:
                break;
            }
        }
        if(regs0->iop_data[6] == IR_ADDR_PATT2)
        {
            switch(rx)
            {
            case 0x30:
            case 0x32:
            case 0x33:
            case 0x34:
                rx+=0x15;
                break;
            default:
                break;
            }
        }
        #endif //#if defined(IR30)

        #ifdef SUPPORT_SPI
        rx = ir_mapcode[(BYTE)spi_mem[5]];
        #else
        rx = ir_mapcode[(BYTE) rx];
        #endif

        regs0->iop_data[IR_PORT] &= (~IR_RDY);
                
        return rx;
    }
    
    return IR_CODE_MAX_NUM;
}

#ifdef TOP_DOOR_LOADER//Jack added 05/11/29
UINT16  get_top_loader_state()
{
    UINT16 iRet = IR_CODE_MAX_NUM;
    
    bDoorStatus = GPIO_GET_DOOR_STATUS();
    if((!CDOpened()) && (bDoorStatus==DOOR_OPEN))
        iRet = IRC_EJECT;
            
    return iRet;
}        
#endif

void PollingSpecifiedKeys( UINT16* pKeyArray, UINT32 uiArraySize )  // 2004/10/14 yltseng
{
    UINT16 rx = GetIRCode();
    if( rx == IR_CODE_MAX_NUM )
    {
#ifdef SUPPORT_VFD
        extern UINT32 CheckVFDkey();
        rx = CheckVFDkey();
#endif

#ifdef TOP_DOOR_LOADER//Jack added 05/11/29 for Top Loader and Portable DVD
        if((rx!=IRC_POWER) && (rx!=IRC_EJECT))
            rx = get_top_loader_state();
#endif
    
#if (defined(PORTABLE_DVD)||defined(CHECK_PORTABLE_OPCLSW)||defined(ALCO_PORTABLE))&&defined(PDVD_USE_IO_SCAN_KEY)//shenyj modify 2006-8-24 02:33下午
        extern UINT16 get_portable_panel_key();
        if((rx!=IRC_POWER) && (rx!=IRC_EJECT))
            rx = get_portable_panel_key();
#endif

        if( rx == IR_CODE_MAX_NUM )
            return;
    }
    
    UINT32 i = 0;
    for( i = 0; i < uiArraySize; i++ )
    {
        if( rx == pKeyArray[i] )
        {
            irc_func_table[rx]();
            break;
        }
    }
}

#ifdef SUPPORT_SPI_QSI
extern void spi_cmd_production_reset(void);
extern void spi_cmd_run_in(void);
extern void spi_cmd_run_in_final(void);
extern void spi_cmd_mecha_test(void);
extern void spi_cmd_slot_test(void);
extern void spi_cmd_invalid_key(void);
void spicmd_pre_parse(BYTE spi_cmd)
{
    UINT8 uRx;
    uSpiRxData=spi_cmd;//tmp usage
    
    switch(uSpiRxData)//special cmd
    {
        case 0x00:
            spi_cmd_wakeup(); return;
        case 0x80:
            spi_cmd_production_reset(); return;
        case 0x81:
            spi_cmd_run_in(); return;
        case 0x82:
            spi_cmd_run_in_final(); return;
        case 0x83: //qsi: added by johnson 20040715
            spi_cmd_mecha_test(); return;
        case 0x84: //qsi: added by johnson 20040715
            spi_cmd_slot_test(); return;
            
        case 0xF0:
            spi_cmd_invalid_key(); return;
    }
    
    if(uSpiRxData < MAX_SPI_CMD_NUM)//boundry control
        uRx = SPI_IR_TRANS_TABLE[uSpiRxData];
    else
        return;

    //if( uRx == IRC_NULL)
       //spi_cmd_func_table[spi_cmd]();
    //else

    call_ir_func(uRx);
        //ircmd_pre_paser(uRx);
}
#endif //#ifdef SUPPORT_SPI_QSI

//Maoyong 2004-9-24 8:59 call after full scrn menu initialization 
void SetFullscrnCmdFuncPtr( void (*up), void (*down), void (*left), void (*right),void (*sel))
{
    ircmd_full_scrn_up = up;
    ircmd_full_scrn_down = down;
    ircmd_full_scrn_left = left;
    ircmd_full_scrn_right = right;
    ircmd_full_scrn_select = sel;
}

