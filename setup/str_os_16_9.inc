#include "user_init.h"
#include "global.h"
#include "osd.h"
//2004AUDDRV #include "audif.h"

static void
str_os_16_9(void)
{
    UserSet.P_V_CFG = 0x0c00;
    set_vpp_tv_aspect(1);


#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
        SET_SCART_GPIO_SFT_CFG_CTRL();
        SET_SCART_TO_DISPLAY_16B9();
#endif//#ifdef SUPPORT_SCART_TV//SPHE8202//nono 4-3-27 21:35
#ifdef SUPPORT_D_TERMINAL  //jwk 5-9-28 16:00
        SET_D_TERMINAL_TO_DISPLAY_16B9();
#endif
#if defined(SCART_TV)||defined(SCART_TV_2)     //wanghaoying 2003-8-13 23:11 added
    #ifdef NIN_SCART_TV  //fangang added 4-2-11 17:07
    SET_SCART_SW(1);
    #elif defined(THAKRAL_DVD)
    SET_SCART_SW(1);
    #else
    SET_SCART_SW(0);
    #endif
    
    #ifdef ORI_SCART_TV
    SET_SCART_TV(0);
    #endif//ORI_SCART_TV
#endif //#ifdef SCART_TV
        
#if defined(SCART_TV_3)&&defined(SKYWORTH_DVD)
        SET_SCART_SW(0);
        SET_SCART_SW1(0);
#elif defined(SCART_TV_3)
        SET_SCART_SW(1);
        SET_SCART_SW1(0);
#endif

#if defined(SCART_TV_4)||defined(SCART_TV_5)//wangfeng 2003-12-2 23:03
        SET_SCART_SW(1);
        SET_SCART_SW1(0);
#endif

#if defined(XQ_SCART_TV)//xyy 2004-4-22
        SET_SCART_SW(0);
        SET_SCART_TV(0);
#endif
}

