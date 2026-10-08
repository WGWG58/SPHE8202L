#include    "user_init.h"

#if     defined(DVB_DVD_8202)
extern void sp_DemuxISR(void);
#endif  /* defined(DVB_DVD_8202) */

void	intr_risc0()
{
    #if     defined(DVB_DVD_8202)
	sp_DemuxISR();
	#endif  /* defined(DVB_DVD_8202) */
	
}


