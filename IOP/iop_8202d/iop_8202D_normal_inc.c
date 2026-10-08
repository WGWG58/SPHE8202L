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
     #if defined(ORITRON_8202D_5115_DVD)||defined(ORITRON_8202D_4127_DVD)
		#include ".\\8202D_normal\ioprom22_v_8202D_16bit_m3004_16312_588_135M_NO_I2C.inc"	//LIJD 2005-6-6 11:13
	#elif defined(ORITRON_8202D_4125_DVD)||defined(OP_DVD5122_PANEL)
		#include ".\\8202D_normal\ioprom22_v_141.inc"		 
	#elif defined (OP_DVD5121_PANEL)	
		#include ".\\8202D_normal\ioprom22_v_8202D_32bit_m3004_NEC_16312_588.inc"
		
    #elif defined(ORITRON_RECEIVER_6001)||defined(ORITRON_RECEIVER_6008)||defined(ORITRON_RECEIVER_5003)||defined(ORITRON_RECEIVER_6505)||defined(ORITRON_RECEIVER_DPL937)    //hongfeng 2005-08-08
        #include ".\\8202D_normal\ioprom22_v_8202D_m3004_16312_mcu_588.inc"	
	#endif	
#elif defined(IR_ORITRON)||defined(IR_ORITRON_RCVR)
	#if defined(ORITRON_8202D_3111_DVD)||defined(ORITRON_8202D_4110_DVD)||defined(ORITRON_8202D_4119_DVD)||defined(ORITRON_8202D_5112_DVD)
		#include ".\\8202D_normal\ioprom22_v_8202D_216pin_16312_5b8_OPIR_nomcu_135MHZ.inc"	//LIJD 2005-6-6 11:13
	#elif defined(ORITRON_8202D_5121_DVD)||defined(ORITRON_8202D_5122_DVD)//caoh 2005-8-17 17:52
	#include ".\\8202D_normal\ioprom22_v_8202D_IR_ORITRON_16312_588_121_5M.inc"	//LIJD 2005-6-6 11:13
    #elif defined(ORITRON_RECEIVER_6001)||defined(ORITRON_RECEIVER_6008)||defined(ORITRON_RECEIVER_5003)||defined(ORITRON_RECEIVER_6505)||defined(ORITRON_RECEIVER_DPL937) //hongfeng 2005-07-07
            #include ".\\8202D_normal\ioprom22_v_8202D_16312_nomcu_588.inc"	//hongfeng 2005-07-07
	#endif	
#elif defined(IR_PHILIPS_EASTECH)
        #include".\\8202D_normal\ioprom22_v_philips_eastech.inc"
#elif defined(HT1621_PANNEL)//lijd 2005-5-16 11:09
		#include ".\\8202s_normal\ioprom22_v_8202s_216pin_ht1621_game_588.inc"	 
#elif defined(Tuner_6600_I2C)
        #if defined(IR_MALATA_PORTABLE)
		#include ".\\8202D_normal\\ioprom22_v_8202D_256pin_game_malata_portable_dvb.inc"  
	 #elif defined(CARD_6IN1_DVB_I2C)
	    #include ".\\8202D_normal\ioprom22_v_8202A_256pin_dvb_t_6in1.inc"
	 #else
        #include ".\\8202D_normal\ioprom22_v_8202D_256pin_dvb_t.inc"
	#endif		
 #elif defined(PMP_DVD)   
		            #include  ".\\8202D_normal\ioprom22_8202DPMP_256_ns_16bit_MCU810_new_I2C.inc"  
#elif defined(F141_75)&&defined(MP_BOARD_256_PIN_NON_SHARE)//wurh add for 8202D_256pin_HDMI_nec_16312_588_141MHz 2005-11-30 16:21
	#ifdef SDRAM_BUS_32BITS        
        #include ".\\8202D_normal\ioprom22_v_8202D_256pin_HDMI_32bit_nec_16312_588_141MHz.inc"
    #else
    	#include ".\\8202D_normal\ioprom22_v_8202D_256pin_HDMI_16bit_nec_16312_588_141MHz.inc" 
    #endif	   
#elif defined(F148_5)&&defined(MP_BOARD_256_PIN_NON_SHARE)//wurh add for 8202D_256pin_HDMI_nec_16312_588_148MHz 2005-11-30 16:21
	#ifdef SDRAM_BUS_32BITS
        #include ".\\8202D_normal\ioprom22_v_8202D_256pin_HDMI_32bit_nec_16312_588_148MHz.inc"
    #else
        #include ".\\8202D_normal\ioprom22_v_8202D_256pin_HDMI_16bit_nec_16312_588_148MHz.inc"
    #endif         
#elif (defined(PORTABLE_DVD)||defined(ALCO_PORTABLE))&&!defined(SUPPORT_VFD)//Jack added 06/03/13
    #if defined(MP_BOARD_256_PIN_NON_SHARE)
		#include ".\\8202D_normal\ioprom22_v_8202A_256pin_portable_no_game_no_vfd.inc"
    #else
        #include ".\\8202D_normal\ioprom22_v_8202D_no_vfd_portable.inc"
    #endif
#else    
		#include ".\\8202D_normal\ioprom22_v_8202D_216pin_game_16312_588.inc"
#endif

