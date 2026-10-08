/*--------------------------------------------------------------------------
|  File Name   : iop_8202s_normal_inc.c
|
|  Purposes:   Make more clear for including the iop code.
|
|  Description : This file include 8202s normal work iop code.
|
|  
|  2005-3-18 9:34      Lijd   create         
|--------------------------------------------------------------------------------*/
#ifdef IC_8202E_216_PIN_NON_SHARE_CD_DVD_MP_BOARD
     #include ".\\8202s_normal\ioprom22_8202E_216pin_ns_16bit_game.inc"
#elif defined(IR_KONKA)//LIJD 2005-2-4 13:38
	 #include ".\\8202s_normal\ioprom22_v_8202S_16bit_konka_16312_5b8.inc"
#elif defined(IR_M3004)
	 #include ".\\8202s_normal\ioprom22_v_8202S_16bit_m3004_16312_588.inc"		 
#elif defined(TEAC_PORTABLE_DVD)//TEAC 
	 #include ".\\8202s_normal\ioprom_spi_teac_8202_216.inc"//TEAC
#elif defined(HT1621_PANNEL)//lijd 2005-5-16 11:09
	 #include ".\\8202s_normal\ioprom22_v_8202s_216pin_ht1621_game_588.inc"
#elif defined(IR_THOMSON_ANGUS)//lijd 2005-5-16 11:09
	 #include ".\\8202s_normal\ioprom22_v_8202S_216pin_thomson_angus_16312.inc"//lijd 2005-3-17 14:27 
#else     
     #include ".\\8202s_normal\ioprom22_v_8202s_216pin_game_16312_588.inc"//lijd 2005-3-17 14:27 
#endif

