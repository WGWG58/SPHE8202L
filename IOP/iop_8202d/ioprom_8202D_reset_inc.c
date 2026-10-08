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
       #include ".\\8202D_reset\ioprom_reset_8202d_216pin_philips_riscalive.inc" 
      #else
      #include ".\\8202D_reset\ioprom_reset_8202d_216pin_philips_16312.inc"   
  #endif
#elif defined(IR_NEC) 
    #ifdef RISC_ALIVE_STANDBY
        #include ".\\8202D_reset\ioprom_reset_8202D_16312_RISC_POWER_ON.inc"  
    #elif  defined(IR_MALATA_PORTABLE)
	 	#include ".\\8202D_reset\ioprom_reset_8202D_malata_portable.inc"		
    #else
		#include ".\\8202D_reset\ioprom_reset_8202D_16312.inc"
	#endif	  
#elif defined(IR_ORITRON)||defined(IR_ORITRON_RCVR)
     #ifdef RISC_ALIVE_STANDBY
		#if defined(ORITRON_8202D_3111_DVD)
        #include ".\\8202D_reset\ioprom_reset_8202D_16312_M3004_RISC_POWER_ON.inc"  
        #elif defined(ORITRON_8202D_5121_DVD)||defined(ORITRON_8202D_5122_DVD)||defined(ORITRON_8202D_6122_DVD)
        #include ".\\8202D_reset\ioprom_reset_8202D_IR_ORITRON_RISC_POWER_ON.inc"        
        #elif defined(ORITRON_8202D_4110_DVD)||defined(ORITRON_8202D_5112_DVD)||defined(ORITRON_8202D_4119_DVD)||defined(ORITRON_RECEIVER_5105)
        #include ".\\8202D_reset\ioprom_reset_8202D_OP_GPIO_RISC_POWER_ON.inc"  
        #endif
     #else
		 #include ".\\8202D_reset\ioprom_reset_8202d_216pin_16312_OPIR_no_mcu.inc"
	 #endif	    
#endif



