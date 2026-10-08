#include "user_init.h"
#include "update_info.h"

#ifdef SETUP_TAB
	#ifdef DVD_SETUP_REENG
		#include "setup_tab_reeng.c"
	#else
		#include "setup_tab.c"
	#endif
#else
	#include "setup_ori.c"
#endif





