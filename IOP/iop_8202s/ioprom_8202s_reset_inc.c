/*--------------------------------------------------------------------------
|  File Name   : iop_8202s_reset_inc.c
|
|  Purposes:   Make more clear for including the iop code.
|
|  Description : This file include 8202s standby reset iop code.
|
|  
|  2005-3-18 9:34      Lijd   create         
|--------------------------------------------------------------------------------*/
#ifdef IR_NEC 
    #ifdef RISC_ALIVE_STANDBY
        #include ".\\8202s_reset\ioprom_reset_8202s_16312_RISC_POWER_ON.inc"  //SPHE8202S
    #else
		#include ".\\8202s_reset\ioprom_reset_8202s_16312.inc"
	#endif	  
#elif defined (IR_THOMSON_ANGUS)
    #ifdef RISC_ALIVE_STANDBY
    	 #include ".\\8202s_reset\ioprom_reset_8202s_16312_RISC_POWER_ON_thomson.inc"  //SPHE8202S
    #else
		#include ".\\8202s_reset\ioprom_reset_8202s_16312.inc"
    #endif	 	  
#endif



