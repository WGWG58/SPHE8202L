//
// FILE
// intdrv.S
//
// DESCRIPTION
// interrupt service routines.
//

#include "ver.h"
#include "regdef.h"
#include "intdef.h"
#include "user_init.h"
#include "set.h"
#include "rommap_rom.h"  //terry,2005/3/6 11:24PM
#include "regmapa.h"


#ifdef	IC_1002
	#include "intdrv_1002.S"
#else	// !IC_1002
	#include "intdrv_8202.S"
#endif	// IC_1002
