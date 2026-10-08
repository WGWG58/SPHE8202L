#include "config.h"
#include "misc.h"
#include "global.h"
#include "ata.h"
#include "fs.h"
#include "cderr.h"
#include "drv.h"
#include "sinf.h"

#include "atapi_if.h"
#include "pu8560.h"
#include "emuio.h"
#include "lbaif.h"
#include "osd.h"//5-4-7 9:12

#ifdef SUPPORT_CD_TEXT
    #include "CDTextUtil.h"
    #include "memmap0.h"
#endif

#ifndef	DVDRELEASE
#define DBG_ATAPI
#endif

#ifndef DBG_ATAPI
#undef	printf
#undef	print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif



extern void ServoDecMainLoop(void);



//terry,2004/2/6 05:43PM
#ifdef DVD_SERVO
//
// FUNCTION
// atapi_dvddsp_busy_waiting()
//
// DESCRIPTION
// compatible atapi 
//

void atapi_dvddsp_busy_waiting(int seek __attribute__((unused)))
{
   set_host_request();
   ServoDecMainLoop();	  // DVD_SERVO
}
#endif

//detect tray function subroutin
UINT8 is_user_opened(void)
{
    //printf("no_disk_cnt:%x s:%x p:%x\n",no_disk_cnt,system_state,play_state);

    if( (no_disk_cnt==DETECT_TIMES)||(system_state==SYSTEM_POWER) )
        return TRUE;
    else
    {
        return FALSE;
    }
}

/*
*   for 8202D use , Terry,2005/4/6 08:24¤U¤È
*/
void display_IC_bug(void)
{
        //psprintf(RegionValStr[REGION1], "IC BUG");
        //PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);
        printf("decode busy!!\n");
}



