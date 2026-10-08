/*--------------------------------------------------------------------------
|  File Name   : iop_8202_normal_inc.c
|
|  Purposes:   Make more clear for including the iop code.
|
|  Description : This file include 8202 normal work iop code.
|
|  
|  2005-3-18 9:34      Lijd   create         
|--------------------------------------------------------------------------------*/

#ifdef MP_BOARD_256_PIN_NON_SHARE
        #ifdef SDRAM_BUS_32BITS
                #ifdef HJ_8202_5401    //fengjl add for himage 8202 ad7312 driver 2004-07-01 13:22
                    #include ".\\8202_normal\ioprom22_v_256_ns_ad7312_key01_688.inc"
                #elif defined(HJ_8202_8408)     
                    #include ".\\8202_normal\ioprom22_256_ns_ad7312_key08_688.inc"
                #elif defined(IR_GBM_PHILIPS)||defined(IR_PHILIPS)//gbm yth add,2004-7-28 14:11
                    #include ".\\8202_normal\ioprom22_8202_256pin_ns_32bit_philips.inc"      
                #elif defined(IR_M3004) //LIJD 2004-12-27 14:27 
                    #include ".\\8202_normal\ioprom22_v_8202_256pin_ns_32bit_16312_game_m3004_5b8.inc"      
               	#elif defined(IR_KONKA) 
               		#include ".\\8202_normal\ioprom22_v_8202_256pin_ns_32bit_16312_game_konka_5b8.inc"//LIJD 2005-2-4 13:23	 
               	#elif defined(IR_TDP101) 
               		#include ".\\8202_normal\ioprom22_v_8202_256pin_ns_32bit_16312_TDP101_5b8.inc"//LIJD 2005-3-25 10:18	
               	#elif defined(HT1621_PANNEL) 
               		#include ".\\8202_normal\ioprom22_v_8202_256pin_ns_ht1621_588.inc"//LIJD 2005-4-5 9:48		    		    
                #else
            		#include ".\\8202_normal\ioprom22_8202_256pin_ns_32bit_game_588.inc"
                #endif
        #else//#ifdef SDRAM_BUS_32BITS
		        #ifdef EASTECH_DVD
		            #ifdef EASTECH_DVD_TOP_DOOR_LOADER
		                #include ".\\8202_normal\ioprom22_8202_256pin_ns_16bit_eastech_2030.inc"
		            #else
		                #include ".\\8202_normal\ioprom22_8202_256pin_ns_16bit_eastech_30H0.inc"
		            #endif
		        #elif defined(TEAC_PORTABLE_DVD)//TEAC 
	 				#include ".\\8202_normal\ioprom_spi_teac_8202.inc"//TEAC
	 			#elif defined(QSI_PORTABLE_DVD)
	 				#ifdef SUPPORT_SPI_QSI        
               		#include ".\\8202_normal\ioprom_spi_qsi_8202.inc"//QSI
            		#endif	 				
		        #elif defined(SDRAM_128Mx1)//#ifdef EASTECH_DVD //mimitsai add 2004-12-07
		        	#include ".\\8202_normal\ioprom22_8202_256pin_ns_16bit_midi_sy_m5.inc"
		        #elif defined(IR_GBM_PHILIPS)//gbm yth add,2004-7-28 14:11
		            #include ".\\8202_normal\ioprom22_8202_256pin_ns_16bit_philips.inc"
		        #elif defined(SUPPORT_IR_GAME)
		            #include ".\\8202_normal\ioprom22_8202_256pin_ns_16bit_nogame.inc"
		        #elif defined(TTE_HOST_DVD)
		            #include ".\\8202_normal\ioprom22_8202_256pin_ns_16bit_pca9564.inc"
		        #elif defined(PMP_DVD)   
		            #include  ".\\8202_normal\ioprom22_8202PMP_256_ns_16bit_MCU810_new_I2C.inc"  
		            // #include ".\\8202_normal\ioprom22_8202PMP_256_ns_16bit_MCU810.inc"                
		        #elif defined(IR_M3004)  
		            #include ".\\8202_normal\ioprom22_v_256pin_ns_16bit_m3004_121.5_5b8.inc"               
				#elif defined(IR_MRC2222)  //frank.huang 050801
		            #include ".\\8202_normal\ioprom22_normal_MRC2222.inc" 
					
		        #else//#ifdef EASTECH_DVD
		            //#include ".\\8202_normal\ioprom22_8202_256pin_ns_16bit.inc"
		            #include ".\\8202_normal\ioprom22_8202_256pin_ns_16bit_game_16312_588.inc" //2004-6-23 14:05 lijd
		        #endif//#ifdef EASTECH_DVD
        #endif//#ifdef SDRAM_BUS_32BITS 
#elif defined(MP_BOARD_216_PIN_NON_SHARE)//kenny 2004/7/14  
        #include "..\IOP_8202S\iop_8202s_normal_inc.c"
#elif defined(MP_BOARD_256_PIN_SHARE)
        #include ".\\8202_normal\ioprom22_8202_256pin.inc"
#else//MP_BOARD_256_PIN_NON_SHARE
   		#include ".\\8202_normal\ioprom22_8202.inc"
#endif//MP_BOARD_256_PIN_NON_SHARE

