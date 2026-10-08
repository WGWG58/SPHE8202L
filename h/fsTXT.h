#include "global.h"
#include "fsGUI1.h"
#include "fs96602.h"
#include "osd.h"
#include "fsGUI.h"
#include "func.h"
#include "util.h"
#include "emuio.h"

#ifdef  SUPPORT_FILE_SYSTEM_MODE

#define SCROLL_BAR_X   	328  // x-axis of left-up corner
#define SCROLL_BAR_Y   	40   // y-axis of left-up corner


UINT32 fsTXT_callback_check(UINT32);
void FS_TXTMainLoop(UINT32, UINT32);
UINT32 parse_file(UINT8);

#endif

