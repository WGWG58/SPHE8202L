//
// FILE
// pt2320.c
//
// DESCRIPTION
// pt2320 chip control
//
// freyman  20020520
//
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "gpio.h"
#include "iop.h"
#include "user_init.h"
#include "epp.h"
#if defined(PT2322)

#include "pt2322.c"

#elif defined(PT2320)

#include "pt2320.c"

#elif defined(TAS3001_AMP)     //use TI 3001 5001 5100 amplifier  / ych add 2-8-9 10:10
#include "ti3001.c"

#endif 


#if defined(SUPPORT_APOGEE_AMP) && defined(SUPPORT_DDX8000) && defined(XINGQIU_DVD_RECEIVER)
		#include "amp_gui_xq.c"
#elif defined(ORITRON_DVD_RECEIVER)
		#include "amp_gui_oritron.c"  
#elif defined(SUPPORT_EXT_MCU)//xyy add 2004-11-17
		#include "amp_gui_mcu.c"  
#elif defined(SUPPORT_APOGEE_AMP)||defined(TAS_5026_PWM)||defined(TAS_5508_PWM)||defined(PT2258)||defined(TDA7448)||defined(DOLBY_AMP_VOLUME_CTRL)
        #include "amp_gui.c"	 	  
#endif



