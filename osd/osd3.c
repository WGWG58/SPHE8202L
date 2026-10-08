/*
** FILE
** osd1.c
**
** DESCRIPTION
** control OSD interface.
**
** Maintain by all
** History :
**      2003.03.10  terry  , check all function on disable osd mode
**      2003/9/26 03:38PM, terry,define osdbuf replacement linebuf when debug mode
**      2003-08-29 15:18, wangfeng For new setup menu
**      2005-1-18 8:48, wanghaoying moved some code about OP_UI to a file in the folder "higui"
** Note : all functions must make the same function name to osd2.c
**
*/

#include "config.h"

#ifdef SPHE1000_DISABLE_ROMCODEOSD
    #include "osd_1000isp.c"
#elif !defined( SUPPORT_OSD )
    #include "osd2.c"
#elif !defined( NEW_OSD_DRIVER )
    #include "osd1.c"
#endif
