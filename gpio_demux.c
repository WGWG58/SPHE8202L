/*
----->included&called by gpio.c
----->only for Demux 6600 use.
----->created it on 05/10/21
*/
#include "..\dvb_h\dmx_6600_gpio.h"


void demux_gpio_reset(void)
{
    
#ifdef MUSTEK_K100D_MODEL
    //LED control
    DMX_GPIO_E_SET(LED_CONTROL_GPIO,1);
    DMX_GPIO_O_SET(LED_CONTROL_GPIO,1);
    
    #ifdef ADD_OP_MUTE
    DMX_GPIO_E_SET(OP_MUTE_GPIO,1);
    DMX_GPIO_O_SET(OP_MUTE_GPIO,1);
    #endif
    
    //close 4052!
#if defined(MUSTEK_K100D_USE_SOME_6600_GPIO)&&!defined(PLAY_IN_SUNPLUS_PORTABLE_6600_DEMO_BOARD)
    //control 74HC4052(6600 GPIO12 and GPIO13 output 1)
    DMX_GPIO_E_SET(AV_IN_4052_CTL_GPIO1,1);
    DMX_GPIO_O_SET(AV_IN_4052_CTL_GPIO1,1);
    DMX_GPIO_E_SET(AV_IN_4052_CTL_GPIO2,1);
    DMX_GPIO_O_SET(AV_IN_4052_CTL_GPIO2,0);
#endif    
    
#endif

}


