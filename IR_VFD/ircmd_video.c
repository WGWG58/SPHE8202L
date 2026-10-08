/*
*  Terry,2003/8/20 08:21PM
*  
*/
#include    "pic_mainproc.h"    
#include	"vpp.h"

//#define P_SCAN_ONLY_CHG_INT_MODE]
#ifdef ADD_DVI311_SETUP
#include "spv301.h"
#endif
#ifdef DVD_SETUP_REENG
#include "setup_VA.h"
#include "setup_def.h"

extern void run_save_sel_cmd(BYTE page,BYTE index);
extern BYTE dvi311_tv_mode;
extern void scaler_6500_main(void);
extern void exe_setup_function(UINT8 tt_id, UINT8 sub_id, UINT8 exe);
#endif
#ifdef QSI_PLATFORM //qsi: merge by johnson 20040712
void ircmd_tvout(void);
//qsi: add by sharon
#endif

#if defined(DVB_MENU_SETUP_STYLE)||(defined(SUPPORT_DVB_GUI_NEW)&&defined(DVB_IR_PSCAN_ON))            //sunzhh add 2005-3-7
UINT8 rem_format_id;
#endif

const UINT8 tv_out_map[MODE_MAX_PSCAN] = {VIDEO_SET_MODE};//{INTERLACE,TV_SVIDEO,TV_RGB,P_SCAN,PC_VGA};
const UINT8 video_setup_id[] = {VIDEO_SETUP_STRING};//nono 2003-7-14 10:12

#define MODE_MAX_FORMAT TV_FORMAT_MAX
UINT8 ap_tv_out_id = 0;
//UINT8 is_ap_svideo;

#ifdef  DYNAMIC_SPECTRUM  //fengjl  3-10-30 15:04
void Show3dspectrum(void);
#endif    

#ifdef BBK_DVD//zhaoyanhua add 3-11-26 16:41
#define VIDEO_OUTPUT_ADDR   240
#define VIDEO_VFD_DELAY_TIME  100
int  tv_output_vfd_time = 0;
#endif

#ifdef SUPPORT_OSDID3//suqiaoli add 2004-3-26 
extern void osd_init_OSDID3(void);
extern void show_id3(void);
#endif
#ifdef DISPLAY_CD_TEXT//lizhx add 2004/08/24
#include"CDTextUtil.h"
#endif
#ifdef SUPPORT_MP4_SUBTITLE  // David 2004-5-12
extern void osd_init_OSDSRT(void);
#endif

#ifdef SUPPORT_DVB_GUI_NEW //wangcj 2005-9-8 15:20
#include "..\dvb_h\dvb_menu.h"
#include "..\dvb_h\Dvb_Macro_Def.h"
extern ReturnResult_E SysConfig_Init(BYTE iSecondSelect);
#endif

#ifdef SCALER_6500
extern UINT8 HDVD_MOD;     //helm 050627
extern UINT8 Ksetup_tv_format;
#endif

//========================== Decleration the Functions ========================
static inline void    ircmd_TV_format_toggle(void);

// ============================================================================
// Video  Video  Video  Video  Video
// ============================================================================
void setup_tv_out(UINT8 id)
{
    #ifdef SUPPORT_HD_RESOLUTION
    int old_tv_resolution = GET_TV_RESOLUTION();
    SET_TV_RESOLUTION(SD_576);
    #endif
    
    int old_mode=p_scan;
    extern UINT8 srv_on;
    #ifdef SUPPORT_D_TERMINAL     //jwk 2005-9-29 14:51
	   if(tv_out_id==P_SCAN)
	   	{
         SET_D_TERMINAL_VFORMAT_CTRL_PSCAN();
	   	}
	   else
	   	{
	   	     SET_D_TERMINAL_VFORMAT_CTRL_INTERRACE();
	   	}
     #endif    
#ifdef TVOUT6_4DAC_ON   //terry,2003-8-19 17:44
    if(id==TV_SVIDEO)
    #ifdef SPHE1000 //MIKEY 2004.07.06
        tv_dacoff( (0x01<<4)|(0x01<<5) );  // dac off        //SPHE1000 use DAC C as C signal in S-Video 
    #else 
        #ifdef MP_BOARD_216_PIN_NON_SHARE   // ronnie 2004/09/09
        	tv_dacoff( (0x01<<1)|(0x01<<2) );
        #else	
        	tv_dacoff( (0x01<<3)|(0x01<<4)|(0x01<<5) );  // dac off
        #endif
    #endif 
#ifdef P_SCAN_TURNOFF_CVBS_SVIDEO
    else if( (id==P_SCAN)||(id==PC_VGA)||(id==INTERLACE)||(id==TV_RGB) )//nono 20030920
    #ifdef SPHE1000
        tv_dacoff( (0x01<<1) );  // dac off
    #else
        tv_dacoff( (0x01<<1)|(0x01<<2) );  // dac off
    #endif
#endif
#ifdef S_VIDEO_RGB_OUT_IN_THE_SAME_TIME//4-1-15 16:05
    else if(id==TV_RGB)
        tv_dacoff( (0x00<<1)|(0x00<<2)|(0x00<<3)|(0x00<<4)|(0x00<<5) );  // dac off
#endif//S_VIDEO_RGB_OUT_IN_THE_SAME_TIME
    else
    #ifdef SPHE1000	//wrwu, 2004/11/03, fix a bug of the SPHE100X changing video output
    	tv_dacoff(0);
    #else
        tv_dacoff( (0x01<<1)|(0x01<<2) );  // dac off
	#endif
    

#endif//#ifdef TVOUT6_4DAC_ON   //terry,2003-8-19 17:44 

#ifdef ADD_PC_VGA_OUT//PC_VGA_OUT//nono change the name of the definition.5-8-22 21:14
	//axelchen 2005/8/10 ////yangli mov form mainproc.c 2005/9/5
    extern UINT8 eTITLEKEY[5]; 
    extern void cssx_set_titlekey(UINT8 title_key[5]);//nono 5-8-29 18:05 del warning msg.
    if (id != PC_VGA)//(tv_out_id != PC_VGA) 
        cssx_set_titlekey(eTITLEKEY);
#endif  

//wanghaoying 2003-11-6 22:54
#ifdef TV_USE_4_DAC
#ifdef SETUP_CVBS_OUTPUT        
    if (id == CVBS )
    {//terry,2003/12/25 09:19PM
        tv_dacoff( (0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<5) );
    }
	 else if(id==TV_RGB)   //zhongshan for rgb not output in the define
        tv_dacoff( (0x00<<1)|(0x00<<2)|(0x00<<3)|(0x00<<4)|(0x00<<5) );  // dac off
#endif
#endif
    
//gerry add for gbm,when we set to S-VIDEO,tv dac3 will be off,2004-5-13 15:44
//#define S_VIDEO_SET_TV_DAC3_OFF
#if defined(TV_USE_4_DAC)&&defined(S_VIDEO_SET_TV_DAC3_OFF)
    if(id==TV_SVIDEO)
        tv_dacoff( (0x01<<3) );  // dac off
    else
        tv_dacoff( (0x00<<3) );  // dac on    
#endif//#if defined(TV_USE_4_DAC)&&defined(S_VIDEO_SET_TV_DAC3_OFF)
    
#if defined(TV_USE_4_DAC)&&defined(S_VIDEO_SET_TV_DAC2_OFF)
    if(id==TV_SVIDEO)
        tv_dacoff( (0x01<<2) );  // dac off
    else
        tv_dacoff( (0x00<<2) );  // dac on    
#endif//#if defined(TV_USE_4_DAC)&&defined(S_VIDEO_SET_TV_DAC2_OFF)
    
    if( (id==INTERLACE)||(id==TV_RGB)||(id==TV_SVIDEO) )//terry,2003/8/3 05:30PM
    {
        tv_setup_int();             
        p_scan=0;
    }
#ifdef SETUP_CVBS_OUTPUT        //wanghaoying 2003-11-6 22:55
    else if( id==CVBS )//terry,2003/8/3 05:30PM
    {
        tv_setup_int();             
        p_scan=0;
    }
    #endif
    else
    {
#ifdef ADD_DVI311_SETUP
        if(id==P_SCAN)
        {
            #ifdef For_TsingHua//Modifed by chenzhao on 2004-12-14 15:34  
            if(dvi311_tv_mode>0x84)
                dvi311_mode=Mode_480P;           //576P   @kevin 2k40708
            else if(dvi311_tv_mode==0x84)
                dvi311_mode=Mode_576P;           //480P @kevin 2k406708
            #ifdef DVD_SETUP_REENG//Modifed by chenzhao on 2004-11-24 21:8   
                setup_VA[SETUP_VA_SPV311MODE]=dvi311_mode+MIN_ITEM_SEL;
            #endif
            #endif
            #ifdef For_TsingHua
            tv_setup_nint();                
            p_scan=1;
            #endif
        }    
        if(id==PC_VGA)
        {
            //dvi311_mode=5;           //SVGA @kevin 2k406708
            if(Power_off_311==1)   //setoutput   @kevin0710
            {
                close_pll(0xff);
            
            }//reset 311  kevin0710
            #ifdef For_TsingHua
            setup_tv_out(1);
            #endif
        }    
        scaler_main();
#else
        tv_setup_nint();                
        p_scan=1; //kevin forbid it for HDDVD @2k40706
 #endif

} 


/* 
** don't mark this, because
** HDMI need progressive input, helm 051205
*/
#ifdef SCALER_6500
    tv_setup_nint();
    p_scan=1; 
#endif
 
#ifdef ADD_DVI311_SETUP
    HD_display(id);
#endif

 #ifdef SUPPORT_HD_RESOLUTION
    if((p_scan!=old_mode) || (old_tv_resolution != GET_TV_RESOLUTION() ))
 #else 
    if(p_scan!=old_mode)
 #endif
    {
        if (full_scrn & SETUP)
        {
            //printf("show setup page\n");
            osd_init_setup();

#ifdef SETUP_TAB
            ShowSetupPage(2);
#else
            ShowSetupPage();
#endif
        }else if(srv_on)
        {
            #if defined(SUPPORT_DVB_GUI_NEW)
            if(Is_Dvb_State())
            {
                if(g_CurScreenType == SCREEN_TYPE_MENU)
                {
                    UINT32 index1 = 0;
                    UINT32 index2 = 0;
                    index1 = GetFourthCurrentSelect();
                    index2 = GetThirdCurrentSelect();
                    DVBMenu_Init();
                    SetFirstCurrentSelect(1);
                    SetSecondCurrentSelect(0);
                    DVBMenu_InitMainMenu(0);
                    full_scrn = DVB_T_SETUP_MENU;//temp use!!!
                    SetFourthCurrentSelect(index1);
                    SetThirdCurrentSelect(index2);
                    SysConfig_Init(DVB_TV_SETTING);
                    full_scrn = 0;
            }
            else      
            {
                    DVBMenu_Init(); 
                }    
            }
            else      
            {
            osd_init();
       		}
            #else
           osd_init();     
            #endif 
          
        }
    }
    tv_setup_output(id);
    tv_out_id=id;
    

#ifdef  DYNAMIC_SPECTRUM        
    if(bEqDisplay)
        Show3dspectrum();           
#endif


//initializing infomation displaying OSD
#ifdef SUPPORT_MP4_SUBTITLE
    if(IS_EXT_SUP_ACTIVATED())
        osd_init_OSDSRT();
    else
#endif
{
#ifdef SUPPORT_OSDID3
////jiangxl for stop state executing restore show id3 in title. 
    if((Is_MP3_STATE())&&(!(full_scrn & SETUP)&&(play_state!=VCD_STATE_STOP))) //lyc add 2005-10-7 for executing restore when showing setup_menu 
    {
            osd_init_OSDID3();
            show_id3();
    }    
#endif
     
}


#ifdef SUPPORT_CD_TEXT//lizhx add 2004/08/24
    if( cd_type_loaded == CDDA )
    {
        osd_init_CDText();
        show_CDText( v11_trk_now );
    }
#endif  
    
#ifdef GBM_USE_VFD_CONTROL_P_SCAN_LED       //gerry,2004-2-20 14:23
    if(full_scrn==SETUP)
    {
    if(p_scan==0)
    write_vfd_led(0xf);     //3 led are all off,2004-2-19 21:03
    else//GBM_USE_VFD_CONTROL_P_SCAN_LED
    write_vfd_led(0xe);     //only p-san led on,2004-2-19 21:03
    }
#endif//GBM_USE_VFD_CONTROL_P_SCAN_LED    
#ifdef ORITRON_RECEIVER_6001
    scart_pin_change();		//OP fcr 2005-9-27 3:22 
#endif
}

void search_ap_tv_out_id(void)
{
    UINT8 i;
    
    for(i=0;i<=MODE_MAX_PSCAN;i++)    
    {
      if(tv_out_id == tv_out_map[i])
      {
        ap_tv_out_id = i;
        return;
      }      
    }
    ap_tv_out_id = 0;
}

//terry,2004/2/4 06:05PM
#ifndef MINTON_DVD                            //hq, let "AUTO" between "NTSC" and "PAL" for ngailik,4-2-17 1:00

const UINT8  TV_format_table[] = {
#ifdef  SUPPORT_NTSC
#ifndef PAL_VERSION
    MODE_NTSC,
#endif
#endif
#ifdef  SUPPORT_NTSCJ
    MODE_NTSCJ,
#endif
#ifdef  SUPPORT_PAL
#ifndef NTSC_VERSION    
    MODE_PAL,
#endif
#endif
#ifdef  SUPPORT_PAL60
    MODE_PAL60,
#endif
#ifdef  SUPPORT_PALM
    MODE_PALM,
#endif
#ifdef  SUPPORT_PALN
    MODE_PALN,
#endif
#ifdef  SUPPORT_PALNc
    MODE_PALNC,
#endif
    MODE_AUTO
};

#else

const UINT8  TV_format_table[] = 
{
    MODE_NTSC,
    MODE_AUTO,
    MODE_PAL
};
#endif                   //end ifndef MINTON_DVD, hq,4-2-17 1:03 
//terry,2004/2/5 12:11PM
UINT8 tv_format_sel=0;
void update_tv_format_sel(void)
{
   //int i;
   UINT8 i;//nono 2004-2-20 0:38 cancel warning...
   
   for(i=0;i<sizeof(TV_format_table)/sizeof(TV_format_table[0]);i++)
   {
    if(TV_format_table[i]==tv_format)
    {
       tv_format_sel=i;
       break;
    }
   }
}

static inline void    ircmd_TV_format_toggle(void)
{
    UINT8 id=STR_OS_PAL;

#ifdef SUPPORT_MIDIDISK_TITLE  //ouyang add for the lyric will move down when read title 050408
        if (bIsPlayMidiTitle)
        {
		invalid_key();
		return;
        }
#endif
#ifdef NEWSTYLE_WINDOW  // alan, 2003/8/27 10:06AM
    if (full_scrn&MESSAGE)
    {
        invalid_key();
        return;
    }
#endif  

#ifdef ALCO_8200P_MULTIKEY
    if((!IS_STOP_OPEN_IDLE_STATE()) && !((play_state==VCD_STATE_MP3_FILELIST)&&Is_JPEG_STATE()&&(!pFsJpeg->gbfsSlide)))
    {
        invalid_key();
        return;
    }
#endif
    
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    if(action_click)
#endif
    {
        tv_format_sel++;

        #ifdef SUPPORT_HD_RESOLUTION        //modify the N/P behavior for HD, by robert.chang, 2006-07-18
         if( ((GET_TV_RESOLUTION()  == HD_720)||(GET_TV_RESOLUTION()  == HD_1080)) ) {
            if(tv_format == MODE_PAL)             // if HD is active, then tv_format only have the MODE_NTSC and MODE_PAL.
                tv_format_sel = 0;
        }            
        #endif
        
        #ifdef ALCO_DVD_UI
        if((tv_format_sel==1) && (tv_format==MODE_AUTO))
            tv_format_sel = 0;
        #endif
        
        if (tv_format_sel>=sizeof(TV_format_table)/sizeof(TV_format_table[0])) {
           tv_format_sel=0;
        }
        tv_format = TV_format_table[tv_format_sel];
        
        #ifdef SUPPORT_HD_RESOLUTION  //modify the N/P behavior for HD, by robert.chang, 2006-07-18
            extern void set_vpp_disp_window(int,int,int,int);
            if(GET_TV_RESOLUTION()  == HD_720){
                if(tv_format == MODE_NTSC) {
                    sp8200tv_set_hd_mode(HD_720P_F60, 1);
                }                
                else if(tv_format == MODE_PAL) {
                    sp8200tv_set_hd_mode(HD_720P_F50, 1);
                }  
                set_vpp_disp_window(0,0,1280,720);
            }
            else if(GET_TV_RESOLUTION()  == HD_1080){
                if(tv_format == MODE_NTSC) {
                    sp8200tv_set_hd_mode(HD_1080I_F60, 1);
                }                
                else if(tv_format == MODE_PAL) {
                    sp8200tv_set_hd_mode(HD_1080I_F50, 1);
                }    
                set_vpp_disp_window(0,0,1920,1080);
            }
        #endif       
            
                setup_tv_format(tv_format);
            
#ifdef SCALER_6500          //helm for HDMI video format switch, 051017
    extern BYTE AUTO_Setup_Position;
    if (tv_format == MODE_PAL)
        exe_setup_function (STR_OS_TV_SYS, STR_OS_PAL, 1);     
    if (tv_format == MODE_NTSC)      // set default
        exe_setup_function (STR_OS_TV_SYS, STR_OS_NTSC, 1);                    

    if (tv_format == MODE_AUTO){
        setup_VA[SETUP_VA_TV_SYS] = AUTO_Setup_Position;
    	run_save_sel_cmd(setup_VA[SETUP_VA_TV_SYS], SETUP_VA_TV_SYS); 
        if (Ksetup_tv_format == TV_FORMAT_PAL){
            dvi311_tv_mode = STR_OS_PAL;
        }
        if (Ksetup_tv_format == TV_FORMAT_NTSC){
    	    dvi311_tv_mode = STR_OS_NTSC;
    	}    
    	     scaler_6500_main(); 
    }
#endif 
        osd_move_subtitle_region(); // 2005/07/12 yltseng

#ifdef ADD_DVI311_SETUP
        if(tv_format==MODE_NTSC)
            dvi311_tv_mode=0x85;    //NTSC
        else if(tv_format==MODE_PAL)
            dvi311_tv_mode=0x84;
        else if(tv_format==MODE_PAL60)
            dvi311_tv_mode=0x86;

        if(tv_out_id!=P_SCAN)                                   //not HD output  kevin@2k0708
        {
            if((dvi311_tv_mode>0x84&&dvi311_mode==Mode_576P)//576P   @kevin 2k40525
            ||(dvi311_tv_mode==0x84&&dvi311_mode==Mode_480P))//480P @kevin 2k40525 change for display correct !
            {
                #ifdef DVI311_NO_PC_MODE
                    if(dvi311_tv_mode>0x84)
                        dvi311_mode=Mode_480P;
                    else if(dvi311_tv_mode==0x84)
                        dvi311_mode=Mode_576P;                        
                #else
            dvi311_mode=Mode_VGA;//SVGA
                #endif
            }
        }
        else if(tv_out_id==P_SCAN)                                   //not HD output  kevin@2k0708
        {
            if(dvi311_tv_mode>0x84&&dvi311_mode==Mode_576P)// NTSC and 480P   @kevin 2k40708
                dvi311_mode=Mode_480P;
            if(dvi311_tv_mode==0x84&&dvi311_mode==Mode_480P)// PAL and 576P   @kevin 2k40708
        dvi311_mode=Mode_576P;
        }
        
        scaler_main();
#endif

}
#ifdef SUPPORT_SCANMODE_SWITCH
    SwitchRegionTVformat();
#endif               //ouyang2004.07.23
    switch(tv_format)
    {
    case MODE_NTSC:     id=STR_OS_NTSC;break;
    case MODE_PAL:      id=STR_OS_PAL; break;
    case MODE_AUTO:     id=STR_OS_AUTO; break;
#ifdef SUPPORT_PAL60
    case MODE_PAL60:    id=STR_OS_PAL60; break;
#endif
#ifdef SUPPORT_PALM     //gerry,2004-1-8 13:48
    case MODE_PALM:     id=STR_OS_PALM; break;
#endif//SUPPORT_PALM
#ifdef SUPPORT_PALN
    case MODE_PALN:     id=STR_OS_PALN; break;
#endif
#ifdef SUPPORT_PALNc
    case MODE_PALNC:    id=STR_OS_PALNc; break;
#endif
    }

//terry,2004/2/5 12:04PM move
#ifndef FORMAT_KEY_NOT_CHANGE_SETUP//BBK_DVD  // fengjl add for bbk   4-1-12 10:54
    setup_SetTV_format(id); //update setup menu item
#endif

    OSD1000ISP_STATUS(tv_format, OSDIR_PAL_NTSC);
    #if defined(DVB_MENU_SETUP_STYLE)||(defined(SUPPORT_DVB_GUI_NEW)&&defined(DVB_IR_PSCAN_ON))            //sunzhh add 2005-3-7
    rem_format_id = id; 
    #endif    
    #ifdef SUPPORT_MULTI_PARTITION//yangli mod 2005-7-5
        osd_init_show_setup_pmp();
    #endif
    
    #ifdef NODISC_SHOW_IN_DIFF_REGION
    if(system_state == SYSTEM_NODISC)
        PrintOsdMsg(STR_OS_TV_SYS|(id<<OSDSTR_ID_TOTL_BIT),REGION0,1,4);
    else
    #endif
    PrintOsdMsg(STR_OS_TV_SYS|(id<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);

#ifdef NEWSTYLE_WINDOW
    if(full_scrn==MESSAGE)
    {
        full_scrn = 0;
    #if defined(BBK_DVD)&&defined(DISC_INFO_KEY)  //fengjl edit 2004-04-28 11:10
        ircmd_disc_info();
    #else
        ircmd_goto();
    #endif
    }
#endif

#ifdef DIVX6_SUP_ALIGNMENT
    void sup_update_avi_sup_registers();
    if ((GetCurrentFileType() == CDROM_MP4) 
        || (GetCurrentFileType() == CDROM_AVI)
        || (GetCurrentFileType() == CDROM_DIV)
        )
    {
	    sup_update_avi_sup_registers();
    }
#endif

 #ifdef RIPPING_MODE_SELECT //qinhua, for UI region ,2006-6-1 05:14ÏÂÎç
       if(new_app_state == NEW_APP_STATE_WRITE)
        {
        Show_Rip_Step_GUI();
        Show_Rip_Step();
        }
 #endif 
}


#if defined(TV_FORMAT_CHG2_VIDEO_MODE)||defined(ADD_TV_VIDEO_MODE)
void ircmd_tv_sys_mode(void)
{   
#ifdef INVALID_TV_MODE_KEY_IN_SETUP           //hq, 2004-3-13 15:24
    if(full_scrn&SETUP)
    {       
        return;
    }
#endif  
#ifdef DVD_5_DISC_RESUME_8202S_1X16//LIJD 2005-4-14 16:50 		
    		//ircmd_stop();
		//resumeMSF = 1;
		run_pause_setting();
		LoadModual(MODUAL_CDROM); 		
#endif
    
#if !defined ( ADJUSTING_ACTION_VALID_RIGHT_NOW )&&!defined ( ADD_COMPONENT_MODE )//libing 2005-7-5 14:58    
    if(action_click)
#endif//ADJUSTING_ACTION_VALID_RIGHT_NOW
    {
//        printf("in, tv_out_id:%x ap_tv_out_id:%x\n",tv_out_id,ap_tv_out_id);
        if(tv_out_id==TV_SVIDEO)
        {
          //if(p_scan)
          //   tv_out_id=P_SCAN;
          //else
#ifdef MIN_SCART_TV_2
             tv_out_id=TV_RGB;          
#else//MIN_SCART_TV_2
             tv_out_id=INTERLACE;          
#endif//MIN_SCART_TV_2
        }
        #ifdef ADD_COMPONENT_MODE//lijd 2005-4-13 16:49
         #ifdef SCART_TV_OP//caoh 2005-6-27 13:33
        else if(tv_out_id==INTERLACE)
        {          
             tv_out_id=TV_RGB;  
        }
        else if(tv_out_id==TV_RGB)
        {          
             tv_out_id=P_SCAN;          
          }
        #else
         else if(tv_out_id==INTERLACE)
         {          
             tv_out_id=P_SCAN;  
         }
        #endif

        #endif
        
        else
        #ifdef EASTWIN_PORTABLE_DVD
        if(tv_out_id==INTERLACE)//tulijuan040805
        {
             tv_out_id=P_SCAN;          

        }else/*
        if(tv_out_id==P_SCAN )//tulijuan040908
        {
          tv_out_id=OFF;          

        }else*/
        #endif
        #ifdef SCART_TV_OP//caoh 2005-6-29 13:26
          tv_out_id=INTERLACE; 
        #elif defined(SCART_TV_OP1)
          tv_out_id=TV_RGB; 
        #else  
          tv_out_id=TV_SVIDEO;
	#endif       
        setup_tv_out(tv_out_id);
        search_ap_tv_out_id();
        setup_SetPScan();
//        printf("out, tv_out_id:%x ap_tv_out_id:%x\n",tv_out_id,ap_tv_out_id);
    }
    #ifdef EASTWIN_PORTABLE_DVD
    run_save_total_userSet();//tulijuan040825 save tv_mode
    #endif

    OSD1000ISP_STATUS(tv_out_id, OSDIR_SCAN_VGA);

    PrintOsdMsg(video_setup_id[ap_tv_out_id],REGION1,1,0);
}
#endif//#if defined(TV_FORMAT_CHG2_VIDEO_MODE)||defined(ADD_TV_VIDEO_MODE)


#if defined(TV_FORMAT_CHG2_VIDEO_MODE)||defined(ADD_TV_VIDEO_MODE)||defined(SUPPORT_IR_I2P_KEY)

static inline void ircmd_p_scan_mode(void)
{   
#ifdef MIN_SCART_TV_2
if( (tv_out_id!=TV_RGB)&&(tv_out_id!=P_SCAN) )
#else//#ifdef MIN_SCART_TV_2
if( (tv_out_id!=INTERLACE)&&(tv_out_id!=P_SCAN) )
#endif//#ifdef MIN_SCART_TV_2

{
    invalid_key();
    return; 
}

#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW    
    if(1)//action_click)
#endif//ADJUSTING_ACTION_VALID_RIGHT_NOW
    {
        //printf("in, tv_out_id:%x ap_tv_out_id:%x p_scan:%x id:%x\n",tv_out_id,ap_tv_out_id,p_scan,video_setup_id[ap_tv_out_id]);
        if(p_scan)
        {
//            if(is_ap_svideo)
//              tv_out_id=TV_SVIDEO;
//            else
#ifdef MIN_SCART_TV_2
             tv_out_id=TV_RGB;          
#else//MIN_SCART_TV_2
              tv_out_id=INTERLACE;             
#endif//MIN_SCART_TV_2      
        setup_tv_out(tv_out_id);      
#ifdef MIN_SCART_TV_2
        PrintOsdMsg(STR_OS_TV_RGB,REGION1,1,0);   
#elif defined(SUPPORT_IR_I2P_KEY)
        PrintOsdMsg(STR_OS_INTERLACE,REGION1,1,0);   
#else//#ifdef MIN_SCART_TV_2
        PrintOsdMsg(STR_OS_YCbCr,REGION1,1,0);   
#endif//#ifdef MIN_SCART_TV_2

        }else
        {

             tv_out_id=P_SCAN;             
             setup_tv_out(P_SCAN);       
	   
#if defined(SUPPORT_IR_I2P_KEY)
        PrintOsdMsg(STR_OS_PROGRESSIVE,REGION1,1,0);   
#else //#if defined(SUPPORT_IR_I2P_KEY)
             PrintOsdMsg(STR_OS_P_SCAN_YUV,REGION1,1,0);      
#endif//#if defined(SUPPORT_IR_I2P_KEY)
        }
#if defined(SUPPORT_IR_I2P_KEY)        
        search_ap_tv_out_id();
        setup_SetPScan();

#endif        
       
//        printf("out, tv_out_id:%x ap_tv_out_id:%x p_scan:%x id:%x\n",tv_out_id,ap_tv_out_id,p_scan,video_setup_id[ap_tv_out_id]);
    }

//    PrintOsdMsg(video_setup_id[ap_tv_out_id],REGION1,1,0);
}

#endif//#if defined(TV_FORMAT_CHG2_VIDEO_MODE)||defined(ADD_TV_VIDEO_MODE)

static inline void ircmd_p_scan_all_mode(void)
{   
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW    
    if(action_click)
#endif//ADJUSTING_ACTION_VALID_RIGHT_NOW
    {
        ap_tv_out_id++;

        if (ap_tv_out_id>=MODE_MAX_PSCAN) ap_tv_out_id=0;

        tv_out_id=tv_out_map[ap_tv_out_id];
        setup_tv_out(tv_out_id);         
        setup_SetPScan();   
       
    }

    OSD1000ISP_STATUS(ap_tv_out_id, OSDIR_SCAN_VGA);

    PrintOsdMsg(video_setup_id[ap_tv_out_id],REGION1,1,0);
}
UINT8 ShowingWarningMessage = 0;  //huhu

// mimitsai merge from dp2070/dp3240
//#ifdef P_SCAN_KEY_ONLY_INTERLACE_PROGRESSIVE
#ifdef EASTECH_DVD_DP2070_D
#include "Setup_def.h"
#include "Setup_page.h"
#include "setup_popup_gui.h"

extern UINT8 setup_sel[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM];
extern void show_pscan_warning();

static inline void ircmd_p_scan_two_mode(void)
{   
    printf("p_scan :%d\n\n",p_scan);    
    if(p_scan)
    {
        setup_tv_out(INTERLACE);
        setup_SetPScan();
        PrintOsdMsg(STR_OS_YCbCr,REGION1,1,0);

        setup_VA[SETUP_VA_VIDEO] = 2;
        run_save_sel_cmd(setup_VA[SETUP_VA_VIDEO], SETUP_VA_VIDEO);
        setup_VA[SETUP_VA_PSCAN_ON_OFF] = 3;
        run_save_sel_cmd(setup_VA[SETUP_VA_PSCAN_ON_OFF], SETUP_VA_PSCAN_ON_OFF);
        
printf("SETUP_VA_VIDEO:%d, setup_VA[SETUP_VA_VIDEO]:%d\n",SETUP_VA_VIDEO, setup_VA[SETUP_VA_VIDEO]);        
printf("SETUP_VA_PSCAN_ON_OFF:%d, setup_VA[SETUP_VA_PSCAN_ON_OFF]:%d\n",SETUP_VA_PSCAN_ON_OFF, setup_VA[SETUP_VA_PSCAN_ON_OFF]);        
    }
    else
    {
        //kevinmonkey 050720 fade out display when drawing warning box.
        if(t_disp != 0) //avoid showing display and warnign box at the same time, causing wrong OSD
        {
            full_scrn &= (~(UINT32)GOTO);
            disp_mode = 0;
            t_disp = 0;
            old_t_disp = 0;
            display_and_time = 0;
            extern BYTE osd0_state;
            osd0_state=0;
            display_flag = 0;
            remain=NO_REMAIN_TIME;
            DispFadeOut();
        #ifdef SHOW_DISPLAY_WHEN_GOTO
            wait_goto_diplay_time  = 0;
            goto_display_time_flag = 0;
        #endif
        }
        
        full_scrn=(SETUP|CUSTM|SCORE);  // hahaha
        ShowingWarningMessage = 1;  //huhu
/*
        if(t_disp != 0) //avoid showing display and warnign box at the same time, causing wrong OSD
        {
            full_scrn &= (~(UINT32)GOTO);
            disp_mode = 0;
            t_disp = 0;
            display_and_time = 0;
            display_flag = 0;
            remain=NO_REMAIN_TIME;
            DispFadeOut();
        #ifdef SHOW_DISPLAY_WHEN_GOTO
            wait_goto_diplay_time  = 0;
            goto_display_time_flag = 0;
        #endif
        }*/

        #if defined(SDRAM_16Mb_Mode)
            osd_tog_region(REGION1, OSD_OFF);
            RegionOnOff[REGION1][1] = 0;
            RegionOnOff[REGION1][2] = STR_OS_SPACE;
            RegionValStr[REGION1][0] = 0;   //kevinmonkey 050720 clear message so it won't appear again permanently after exit warning bax
            
            regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
        #endif

    	osd_init_setup();
		setup_gui_state = SETUPGUI_PSCAN_WARNING;
		show_pscan_warning();
        SetFullscrnCmdFuncPtr( setup_func_up, setup_func_down, setup_func_left,
                               setup_func_right,  setup_func_select);
    }
}
    //#endif  //#ifdef P_SCAN_KEY_ONLY_INTERLACE_PROGRESSIVE
#endif //EASTECH_DVD_DP2070_D    

#ifdef QSI_PLATFORM //qsi: merge by johnson 20040712
//qsi: add by sharon
extern void spi_cmd_tvout(void);
extern UINT8 uSpiRxData;
#define MAX_TVOUT_MODE  8
#define IR_TO_SPI_ADJ  0x40

void ircmd_tvout(void)
{
    ap_tv_out_id++;
       
    uSpiRxData = ap_tv_out_id + IR_TO_SPI_ADJ;
    spi_cmd_tvout();              

    if( ap_tv_out_id >= MAX_TVOUT_MODE )
    {
        ap_tv_out_id = 0;   
    }
    return;
}
#endif

#ifdef SUPPORT_VFD_SHOW_P_SCAN
void ircmd_p_scan_only(void)
{
      if(ap_tv_out_id==2)
      return;
      ap_tv_out_id=2;
      tv_out_id=tv_out_map[ap_tv_out_id];
        setup_tv_out(tv_out_id);
        //setup_SetPScan();
       OsdShowPscan(1);
}
void ircmd_yuv_only(void)
{
      if(ap_tv_out_id==0)
      return;
      ap_tv_out_id=0;
      tv_out_id=tv_out_map[ap_tv_out_id];
        setup_tv_out(tv_out_id);
        //setup_SetPScan();
       OsdShowPscan(0);
}
#endif

void ircmd_p_scan(void)
{
  #ifdef SUPPORT_MIDI
    #if !defined(IR44)
     if(midiState == MIDI_STATE_PAYLOAD) return;//axel2004.08.09
     
    #else//!defined(IR44)
        //if (bMidiPlayerBoolean) { //Jeff 20031029
        if(midiState == MIDI_STATE_PAYLOAD){ // dtb 20040109
            ircmd_key_down();
            return;
        }
        #ifdef SUPPORT_MIDI_MENU_SEL
        if (gIsMidiSelMenu)  return;
        #endif
    #endif//!defined(IR44)axel2004.08.09
   #endif//SUPPORT_MIDI

#if defined(MINTON_DVD)
    if (full_scrn&SETUP)
    {
        return;
    }   
#endif
#if defined(P_SCAN_ONLY_CHG_INT_MODE)||defined(SUPPORT_IR_I2P_KEY)
    ircmd_p_scan_mode();
#elif defined(QSI_PLATFORM) //qsi: merge by johnson 20040712
    ircmd_tvout();
//qsi: add by sharon    
#else 

    // mimitsai merge from dp2070/dp3240
    #ifdef P_SCAN_KEY_ONLY_INTERLACE_PROGRESSIVE
        ircmd_p_scan_two_mode();
    #else
    	ircmd_p_scan_all_mode();
	#endif

#endif
#ifdef CD_PLAYER        //liweihua 2003-9-3
    if((cd_type_loaded==CDDA)&&(play_state!=VCD_STATE_STOP))
    {
        show_cdplayer();
    }
#endif

//huziqin 2006-4-19 removed
}

#ifdef ONLY_INTERLACE_KEY
/*
 *video output mode :
 *      INTERLACE
 */        
void ircmd_interlace(void)
{
    tv_out_id = INTERLACE;
    setup_tv_out(tv_out_id);
//    setup_SetPScan();  //fengjl marked it  3-11-25 22:19
    
    //PrintOsdMsg(STR_OS_YCbCr, REGION1, 1, 0);
    PrintOsdMsg(STR_OS_YCbCr, REGION1, 3, 0);    
    WriteToI2c(0xa0, VIDEO_OUTPUT_ADDR, (BYTE *)&tv_out_id,sizeof(tv_out_id));
    //refresh VFD pannel
    tv_output_vfd_time = VIDEO_VFD_DELAY_TIME;

        
}
#endif

#ifdef ONLY_VGA_KEY
/*
 *video output mode :
 *      VGA
 */        
void ircmd_VGA(void)
{
    printf("---VGA---\n");
    
        tv_out_id = PC_VGA;
        setup_tv_out(tv_out_id);
//      setup_SetPScan();   //fengjl marked it  3-11-25 22:19
    
        //PrintOsdMsg(STR_OS_PC_VGA, REGION1, 1, 0);
        PrintOsdMsg(STR_OS_PC_VGA, REGION1, 3, 0);      
        
    
        //save tv_out_id_value
    WriteToI2c(0xa0, VIDEO_OUTPUT_ADDR, (BYTE *)&tv_out_id,sizeof(tv_out_id));
    //refresh VFD pannel
    tv_output_vfd_time = VIDEO_VFD_DELAY_TIME;
}
#endif//ONLY_VGA_KEY

#ifdef ONLY_P_SCAN_KEY

/*
 *video output mode :
 *      P_SCAN
 */        
#ifdef GBM_DVD
void ircmd_only_P_SCAN(void)
{
    printf("-----------P_SCAN---\n");
        tv_out_id = P_SCAN;
        setup_tv_out(tv_out_id);
        setup_SetPScan(); 

    PrintOsdMsg(STR_OS_P_SCAN_YUV, REGION1, 1, 0);     

    
}

#else//GBM_DVD
void ircmd_only_P_SCAN(void)
{
    printf("-----------P_SCAN---\n");
        tv_out_id = P_SCAN;
        setup_tv_out(tv_out_id);
//          setup_SetPScan();   //fengjl marked it  3-11-25 22:19
    
        //PrintOsdMsg(STR_OS_P_SCAN_YUV, REGION1, 1, 0);
    PrintOsdMsg(STR_OS_P_SCAN_YUV, REGION1, 3, 0);     
    WriteToI2c(0xa0, VIDEO_OUTPUT_ADDR, (BYTE *)&tv_out_id,sizeof(tv_out_id));
    //refresh VFD pannel
    tv_output_vfd_time = VIDEO_VFD_DELAY_TIME;
    
}
#endif//GBM_DVD
#endif//ONLY_P_SCAN_KEY

/*
#ifdef BBK_DVD    //fengjl marked it  3-11-25 22:19
/
 *  default TV output is "INTERLACE"
 * 
 * to avoid the bug when POWER ON, S video can not output normally.
 * zhaoyanhua add 2003-11-24 14:13
 /
void tv_init_output(void)
{
    tv_out_id = INTERLACE;
    setup_tv_out(tv_out_id);
//    setup_SetPScan();
    
}

#endif
*/


void ircmd_chg_dac(void)
{
#if 0    
    regs0->emu_cfg[1] = regs0->emu_cfg[1]^0x100;
#endif    
}


/*
** display format
*/
void    ircmd_display_format_toggle(void)
{
#ifdef USE_IR_TO_CHANGE_TVTYPE
#if defined(SDRAM_16Mb_Mode)    
    if( (full_scrn&SETUP)||(full_scrn&PROGRAM) )
    {
        return;
    }   
#endif
#ifdef ALCO_8200P_MULTIKEY
    if((!IS_STOP_OPEN_IDLE_STATE()) && !((play_state==VCD_STATE_MP3_FILELIST)&&Is_JPEG_STATE()&&(!pFsJpeg->gbfsSlide)))
    {
        invalid_key();
        return;
    }
#endif
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW
    setup_DVD_TVType(1);
#endif
#else
#ifdef INVALID_TV_FORMAT_KEY_IN_SETUP        //hq, 2004-3-13 15:24
    if(full_scrn&SETUP)
    {       
        return;
    }
#endif  

#ifdef TVFORMAT_USE_IR_CRT
#if defined(MINTON_DVD) 
    if (full_scrn&SETUP)
    {
        return;
    }   
#endif
#if defined(SDRAM_16Mb_Mode)    
    if( (full_scrn&SETUP)||(full_scrn&PROGRAM) )
    {
        return;
    }   
#endif

#if defined(TV_FORMAT_CHG2_VIDEO_MODE)&&!defined(ADD_TV_VIDEO_MODE) 
    ircmd_tv_sys_mode();
#else   
    ircmd_TV_format_toggle();
#endif
#endif//TVFORMAT_USE_IR_CRT
#endif//end #ifdef USE_IR_TO_CHANGE_TVTYPE
}

extern void str_os_hd_720p(void);
extern void str_os_hd_1080i(void);
extern void set_video_default_offset(void);
extern void startup_vpp_now(void);
extern int is_aspect_menu(void);
extern void rep_run_the_menu(void);
#ifdef SUPPORT_HD_RESOLUTION
void hd_setting_start(void)
{
    run_pause_setting();
}
void hd_setting_end(void)
{   
    int play=0;
    if( (old_play_state==VCD_STATE_NORMAL)&&(play_state==VCD_STATE_PAUSE) )
    {
        play|=0x01;
    }
    if( (NP_P_CFG_for_Video&0x0300) != (UserSet.P_V_CFG&0x0300) )
    {
        if(cd_type_loaded==CDDVD)
        {
            set_video_default_offset();//nono 4-9-3 16:07 for ZOOM4 16:9->4:3LB, picture x size error.
            startup_vpp_now();//nono add 2004-7-31 15:59 for ZOOM4 16:9->4:3LB, picture x size error.
            set_video_aspect();
            play|=is_aspect_menu();
        }
    }
    if (cd_type_loaded==CDDVD)
        nav_param_by_user();
    if(play&0x01) {   
        ircmd_play();
    }
    else if(play&0x02) {
        rep_run_the_menu();
    }
    else if((Is_OTHER_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
    {
        play_state = old_play_state;
        return ;
    }
    else if ((play_state!=VCD_STATE_STOP)&&(play_state!=VCD_STATE_IDLE))
        PrintOsdMsg(rem_osd_id,REGION1,1,0);//show "PAUSE" & "STEP"...after "setup" 2-7-15 21:44
                        
}

/*
*  for HD 720P and 1080i output
*  robert.chang, 2006-07-13
*/
void ircmd_hd(void)          
{
    static UINT8 hd_out_id = SD_576;
    char buffer[40];

    if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG) 
    {                    
        //if jpeg is decoded, then HD IR-key is invalid.
        if(jpg_is_decoding_process() == 1)
        {
            invalid_key();
            return;
        } 
    }    
    
    hd_out_id = GET_TV_RESOLUTION();
#ifndef ADJUSTING_ACTION_VALID_RIGHT_NOW    
    if(action_click)
#endif//ADJUSTING_ACTION_VALID_RIGHT_NOW
    {
            hd_setting_start();        

            hd_out_id++;
            if(hd_out_id == HD_720) {
                setup_VA_EN[SETUP_VA_VIDEO] = 2;
                str_os_hd_720p();
            }
            else if(hd_out_id == HD_1080) {
                setup_VA_EN[SETUP_VA_VIDEO] = 2;                
                str_os_hd_1080i();  
            }    
            else {
                setup_VA_EN[SETUP_VA_VIDEO] = 1;
                ap_tv_out_id=0;
                hd_out_id = SD_576;
                tv_out_id=tv_out_map[ap_tv_out_id];
                //joshua, jpeg re-decoding between SD and HD
                if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)        
                {
                    jpg_redecode_byTvResolution();
                }    
                setup_tv_out(tv_out_id);
                setup_tv_format(tv_format);
            }
            setup_SetHD();              
            setup_SetPScan();

            hd_setting_end();
    }
        
    if(hd_out_id == HD_720) {
        strcpy(buffer, "HD720P");
        timeout_osd[2]=3*OSD_TIMEOUT;   
        osdshow(2, buffer);            
    }   
    else if(hd_out_id == HD_1080) {
        strcpy(buffer, "HD1080i");
        timeout_osd[2]=3*OSD_TIMEOUT;   
        osdshow(2, buffer);            
    }              
    else {
        PrintOsdMsg(video_setup_id[ap_tv_out_id],2,1,0);
    }
            
}    

#endif //#ifdef SUPPORT_HD_RESOLUTION


