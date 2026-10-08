/*--------------------------------------------------------------------------
|  File Name   : iop_8202D_normal_inc.c
|
|  Purposes:   Make more clear for including the iop code.
|
|  Description : This file include 8202D normal work iop code.
|
|  
|  2005-5-16 10:37      Lijd   create         
|--------------------------------------------------------------------------------*/
#ifdef IR_M3004


#elif defined(IR_PHILIPS_EASTECH)
        #include".\\8202L_normal\ioprom_8202L_philips_eastech.inc"
        
#elif defined(HT1621_PANNEL)//lijd 2005-5-16 11:09
		#include ".\\8202L_normal\ioprom_8202L_NEC_ht1621_588.inc"	 

#elif defined(F141_75)
	   	#include ".\\8202L_normal\ioprom_8202L_NEC_16312_588_141MHz.inc" 
    	   
#elif defined(F148_5)
	    #include ".\\8202L_normal\ioprom_8202L_NEC_16312_588_148MHz.inc"
             
#elif defined(PORTABLE_DVD)&&!defined(SUPPORT_VFD)//Jack added 06/03/13
        #include ".\\8202L_normal\ioprom_8202L_NEC_no_vfd_portable.inc"
    
#else    
		#include ".\\8202L_normal\ioprom_8202L_NEC_16312_588.inc"
#endif

