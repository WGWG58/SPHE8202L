/*
** FILE
** init0.S
**
** DESCRIPTION
** the bootstrap ROM code for VCD/SVCD/DVD systems.
** it located in several places and serves as the 
** exception-handler, also.
*/

#include "regdef.h"
#include "regmapa.h"
#include "intdef.h"
#include "pu8560.h"
#include "user_init.h"

#include "rommap_rom.h" //terry,2005/3/6 09:34PM


#ifdef	IC_1002
	#include "init0_1002.S"
#else	// !IC_1002
	#include "init0_8202.S"
#endif	// IC_1002
