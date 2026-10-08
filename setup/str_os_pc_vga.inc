#include "user_init.h"
#include "global.h"
#include "osd.h"
//2004AUDDRV #include "audif.h"

static void
str_os_pc_vga(void)
{

//#ifdef TVOUT6_4DAC_ON //terry,2003-8-19 17:44,mark it,move to ircmd_util.c
//              tv_dacoff( (0x01<<1)|(0x01<<2) );  // dac off
//#endif
    setup_tv_out(PC_VGA);//set RGB output(composited+component)(0x00:D0-D1-D2-D3=CVBS-V-Y-U)
    //ap_tv_out_id=PC_VGA;//nono 2003-8-1 18:05
    search_ap_tv_out_id();//terry,2003/8/19 03:21PM

#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
    SET_SCART_GPIO_SFT_CFG_CTRL();
    SET_SCART_TO_CVBS();
#endif//#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35

#if defined(SCART_TV)||defined(KSD_SCART_TV)||defined(SCART_TV_4)||defined(SCART_TV_5)//wangfeng 2003-12-2 23:03
    //SET_SCART_RGB(1);
    SET_SCART_RGB(0);//nono 2003-8-24 21:08
#endif //#ifdef SCART_TV

#if defined(SCART_TV_2)
    #if defined(THAKRAL_DVD)
    SET_SCART_RGB(1);
    #else
    SET_SCART_RGB(0);
    #endif
#endif

#if defined(SCART_TV_3)&& defined(SKYWORTH_DVD)     //wanghaoying 2003-9-12 11:28
    SET_SCART_RGB(0);
#elif defined(SCART_TV_3)     //wanghaoying 2003-9-12 11:29
    SET_SCART_RGB(1);
#endif
}
