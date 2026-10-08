//
// FILE
// sysmain2_showtitle.inc
//
// DESCRIPTION
// Main entry of DVD system firmware
//
// 20030307 Maintain by terry
// 20050928 Reorganized by potatooo
//

extern  char    _stextf[];
extern  char    _text_drv[], _text_drv_dvd[], _text_drv_ap[], _text_drv_iop[], _text_drv_cdrom[];
extern  char    _text_drv_srvdp[], _text_drv_ap2[], _text_drv_free[];
extern  char    _text_other[];

#include "kernel.h"


#define CUSTM_LOGO 0                // Default startup logo
#define SETUP_LOGO 1                // Setup background 
UINT8 logo_type=CUSTM_LOGO;         
extern const unsigned char Setup_Logo[];


#ifdef USER_MPEG_LOGO
extern  UINT8 Is_User_Mpeg_Logo();
#define USER_MPEG_LOGO_PTR  (ROM_BASE_UNCACHED+768*1024)        // Flash offset addr 0x90000(for 080)
#endif


#ifdef  MONE_LOGO
#define logo_printf         printf
#else
#define logo_printf(s...)   ((void)0)
#endif

//
// FUNCTION
// ShowTitle
//
// DESCRIPTION
// Show logo
//
// Terry,2003/9/13 12:20AM
// integration mpeg logo/new style setup logo function
//
void    ShowTitle(void)
{
    BYTE    *p;

    #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO
    if(!flag_check_mcu_info) 
    {
      return;
    }
    #endif//end=> #ifdef  SUPPORT_SYS_POWER_ON_WAITING_MCUINFO

    
#ifdef NEW_STYLE_SETUP                  // terry,2004/2/17 11:09AM
    UINT8   setup=0;
#endif

    logo_printf("logo in\n");

    p=NULL;                             // DEFAULT

    LoadModual(MODUAL_MPEG);
    show_logo=1;
    Abort();

    //set_vpp_disp_size(0,0);             //joshua mark it.200607 ????

    // LOWEST PRIORITY
#if defined(PMP_UI)&&(!defined(HDD_PLAYER))
    extern FSNAVUI fsPmp;
    if (fsPmp.main_icon_index==SETUP_ICON) p=SETUPTitle;
#endif

#ifdef SHOW_DOUBLE_LOGO  
    if (system_state==SYSTEM_READ_TITLE) p=DVDTitle1;        
#endif

#ifdef DOUBLE_LOGO
    if (OsdIsEnglish()) p=DVDTitle1;
#endif

#ifdef CD_PLAYER  
    if ((cd_type_loaded==CDDA)&&(play_state!=VCD_STATE_OPEN)) p=CDPlayerTitle;
#endif

#ifdef USER_MPEG_LOGO
    if (Is_User_Mpeg_Logo()) p=(UINT8 *)USER_MPEG_LOGO_PTR; 
#endif

    // HIGHEST PRIORITY
#ifdef NEW_STYLE_SETUP
    #ifdef SDRAM_16Mb_Mode//zhaoyanhua add 2003-8-7 10:12
    if ((prog_state==4)||(prog_state==5))
    #else
    if ((setup_state==1)||(setup_state==3))
    #endif//SDRAM_16Mb_Mode
       setup =1;
    else
       setup =0;
    if (setup)
    {
        set_video_aspect();
        p = Setup_Logo;
        logo_type = SETUP_LOGO;
        printf("==============>display setup logo\n");
    }
#endif

    // DEFAULT FALLBACK
    if (p==NULL) p=DVDTitle;

	#ifdef  SUPPORT_TWO_LOGO_FOR_DVD_DVB
	if((Is_Dvb_State())||(DVD2DVB_switch_flag == 1)) 
	{
	 	p = DVBTitle;
	}
	else
	{
       		p = DVDTitle;
	}
	#endif//end=> #ifdef SUPPORT_TWO_LOGO_FOR_DVD_DVB


    // actual playback
    PlayRomSlide(p);
    #ifdef SLEEP_CONTROL_COUNTER    //jwk add 2005-11-5 11:37
   counter_sleep_control = 0;
   #endif
    
#ifdef LOGO_STARTUP_VPP_NOW
    startup_vpp_now();//nono 4-6-10 0:25 for ZOOMING IN,show logo startup_vpp_now.
#endif  //LOGO_STARTUP_VPP_NOW
    MediaMainLoop();
    PlayRomSlide(p);
    MediaMainLoop();

#ifdef INCLUDE_MP3_ENCODER
    //kevinmonkey 051117 for 32M config since mp3 encoding needs using frame buffer to load a large FAT
    //table for writing device, therefore we make sure displaying ref0 and ref1 is used as FAT buffer.
    //for 16M, ref0 is also used as FAT buffer, so title picture will have some artifact
    #include "framebuf.h"
    if(GetDisplayingFrameBuffer() == FRAME_REF1)
    {
        PlayRomSlide(p);
        MediaMainLoop();
    }
#endif

#ifdef NEW_STYLE_SETUP  // alan, 2003/8/13 11:44PM
    if (setup)
    {      
        if(getVPP_TVsystem()) set_vpp_disp_size(720,540);       
        else set_vpp_disp_size(0,0);
    }
#endif

#ifdef NEW_STYLE_SETUP
    if (logo_type==CUSTM_LOGO)
#endif
    tv_setup_misc(0);

#ifdef NEW_STYLE_SETUP
    if(setup==0) logo_type=CUSTM_LOGO;
#endif 

    reset_sup();
    Sync();

    show_logo=0;

    set_video_default_offset();
    startup_vpp();

    logo_printf("logo out\n");
}

