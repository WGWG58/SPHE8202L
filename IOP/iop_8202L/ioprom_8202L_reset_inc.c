/*--------------------------------------------------------------------------
|  File Name   : iop_8202D_reset_inc.c
|
|  Purposes:   Make more clear for including the iop code.
|
|  Description : This file include 8202D standby reset iop code.
|
|  
|  2005-5-16 10:51     Lijd   create         
|--------------------------------------------------------------------------------*/
#ifdef IR_PHILIPS_EASTECH    //jwk 2005-11-11 16:23
    #ifdef RISC_ALIVE_STANDBY
       #include ".\\8202L_reset\ioprom_reset_8202L_philips_16312_RISC_POWER_ON.inc" 
      #else
      #include ".\\8202L_reset\ioprom_reset_8202L_philips_16312.inc"   
  #endif
#elif defined(IR_NEC) 
    #ifdef RISC_ALIVE_STANDBY
        #include ".\\8202L_reset\ioprom_reset_8202L_NEC_16312_RISC_POWER_ON.inc"  
    #else
		#include ".\\8202L_reset\ioprom_reset_8202L_NEC_16312.inc"
	#endif	  
#endif



