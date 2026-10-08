#include "misc.h"
#include "gpio.h"

#define AVB_OK    (0)
#define AVB_FAIL  (1)

#define ack_OK    (0xa0)
#define ack_Ctx   (0xa4)
#define ack_Que   (0xa5)
#define ack_Cmd   (0xa8)
#define ack_Arg   (0xa9)
#define ack_Sum   (0xaa)

#define AVB_NO_DISC		(0)
#define AVB_UNKNOWN_DISC	(1)
#define AVB_DVD_SINGLE_LAYER	(2)
#define AVB_DVD_DUAL_LAYER	(3)
#define AVB_CDDA		(4)
#define AVB_CDROM		(5)

#define AVB_DVD_RAW		(0<<1)
#define AVB_DVD_COOKED		(1<<1)

#define AVB_DVD_LOGICAL		(0<<2)
#define AVB_DVD_PHYSICAL	(1<<2)

void avbInit(void);
int avbGetDisctype(void);
int avbPlayDVD(UINT32 start, UINT32 end, UINT8 mode);
