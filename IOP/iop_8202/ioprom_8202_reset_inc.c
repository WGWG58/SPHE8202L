/*--------------------------------------------------------------------------
|  File Name   : iop_8202_reset_inc.c
|
|  Purposes:   Make more clear for including the iop code.
|
|  Description : This file include 8202 standby reset iop code.
|
|  
|  2005-3-18 9:34      Lijd   create         
|--------------------------------------------------------------------------------*/
#ifdef IR_NEC 
#if  defined(HJ_8202_5401)||defined(HJ_8202_8408)                 
      #include ".\\8202_reset\ioprom_reset_HJ_ad7312.inc"	
#elif defined(DP2030_SCAN_KEY)
	  #include ".\\8202_reset\ioprom_reset_eastech_2030.inc"
#elif defined(DP30H0_KEY_SCAN)
      #include ".\\8202_reset\ioprom_reset_eastech_30H0.inc"
#elif defined(POWER_OFF_LED_FLASH)
      #include ".\\8202_reset\ioprom_reset_8202_eastwin.inc"
#elif defined(RISC_ALIVE_STANDBY)
      #include ".\\8202_reset\ioprom_reset_8202_16312_RISC_POWER_ON.inc"
#elif defined(SUPPORT_EX_IR)
      #include ".\\8202_reset\ioprom_reset_8202_ex_ir.inc"
#else              
	  #include ".\\8202_reset\ioprom_reset_8202.inc"
#endif
#elif defined(IR_KONKA)
    #include ".\\8202_reset\ioprom_reset_8202_konka_16312.inc" 
#elif defined(IR_TDP101)
    #include ".\\8202_reset\ioprom_reset_8202_TDP101.inc"     
#elif defined(IR_MRC2222)//frank.huang 050801
	#include".\\8202_reset\ioprom_reset_MRC2222.inc"

#endif

