//
// FILE
// crt0.S
// 
// DESCRIPTION
// initialize system and jump to C program
//

#include "regdef.h"
#include "gpio.h"
#include "config.h"
#include "regmapa.h"
#include "user_init.h"


#ifdef	IC_1002
	#include "crt0_1002.S"
#else	// ! IC_1002
	#include "crt0_8202.S"
#endif	// IC_1002

