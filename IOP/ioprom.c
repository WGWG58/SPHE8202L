#include "h/set.h"
#include "user_init.h"
#ifdef IR_HKOP_NOMCU
#ifdef USE_TOSHIBA//kingslon 20051024
#define  IR_NEC
#else
#define  IR_ORITRON
#endif
#elif defined(IR_MALATA_GPS)
#define IR_MRC2222//frank.huang 050801
#else
#define  IR_NEC
//#define IR_THOMSON_ANGUS
//#define  IR_PHILIPS
//#define  IR_THOMSON
//#define  IR_M50560
//#define  IR_AS1213
//#define  IR_KONKA
//#define  IR_TDP101
//#define		IR_MRC2222//frank.huang 050801	
#endif
/*
  lijd 2005-3-18 9:43
  In order to make clear that we include the iop code.
  I make several folder for include 8200/8202/8202s/other,
  and every folder include normal and reset folder.
  Please try it. if it has any questions ,please contact me.
*/

#if defined(IC_8202L)//terry,2006/4/7 05:10¤U¤È
  #include ".\\IOP_8202L\ioprom_8202L_reset_inc.c"  //SPHE8202L    
#elif defined(IC_8203A)
  #include ".\\IOP_8202L\ioprom_8203A_reset_inc.c"  //SPHE8203A    
#elif defined(SPHE8202)
    #if defined(MP_BOARD_216_PIN_NON_SHARE)||defined(MP_BOARD_256_PIN_NON_SHARE)//caoh
   	    #ifdef IC_8202D//lijd 2005-5-16 10:47
    	    #include ".\\IOP_8202D\ioprom_8202D_reset_inc.c"  //SPHE8202D    	
       	#else
            #include ".\\IOP_8202S\ioprom_8202s_reset_inc.c"  //SPHE8202S
        #endif
    #else
        #include ".\\IOP_8202\ioprom_8202_reset_inc.c"    //SPHE8202
    #endif  
#elif defined(SPHE1000)
	 #include ".\\IOP_1000\ioprom_1000_reset_inc.c"     //SPHE100X
#else	//SPHE8200
    #include ".\\IOP_8200\ioprom_8200_reset_inc.c"    //SPHE8200
#endif//SPHE8202



