#include "user_init.h"
#include "global.h"
#include "osd.h"
//2004AUDDRV #include "audif.h"

static void
str_os_pscan_yuv(void)
{
//#ifdef TVOUT6_4DAC_ON //terry,2003-8-19 17:44,mark it,move to ircmd_util.c
//                tv_dacoff( (0x01<<1)|(0x01<<2) );  // dac off
//#endif
    setup_tv_out(P_SCAN);//set S-video output(composited+S-Video)(0x00:D0-D1-D2-D3=CVBS-C-Y-CVBS)
    //ap_tv_out_id=P_SCAN;//nono 2003-8-1 18:05
    search_ap_tv_out_id();//terry,2003/8/19 03:21PM

#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
    SET_SCART_GPIO_SFT_CFG_CTRL();
    SET_SCART_TO_CVBS();
#endif//#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
#ifdef SUPPORT_D_TERMINAL    //jwk 5-9-28 16:00 
     SET_D_TERMINAL_VFORMAT_CTRL_PSCAN();
#endif

    #if defined(SCART_TV)||defined(KSD_SCART_TV)||defined(SCART_TV_4)||defined(SCART_TV_5)//wangfeng 2003-12-2 23:03    
    SET_SCART_RGB(0);
    #endif //#ifdef SCART_TV
    
    #if defined(SCART_TV_2)
    #if defined(THAKRAL_DVD)
    SET_SCART_RGB(1);
    #else
    SET_SCART_RGB(0);
    #endif
    #endif
    
    #if defined(SCART_TV_3)&& defined(SKYWORTH_DVD)
    SET_SCART_RGB(0);
    #elif defined(SCART_TV_3)
    SET_SCART_RGB(1);
    #elif defined(XQ_SCART_TV)
    SET_SCART_RGB(0);        
    #endif
}

