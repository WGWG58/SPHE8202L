// 
// FILE
// sdram.h
//
// SDRAM interface timing setting
// used in init0.S
//


//
// the way to define SDRAM parameter:
//
// non-bypass mode:
// please define 
// #define CFG_SDRAM_OUT     CFGOUT(a,b)
// #define CFG_SDRAM_IN      CFGIN0(c,d)
// #define CFG_SDRAM_IN_DLY  CFGIN0(0,0,0)
// #define CFG_SDRAM_PADCTRL 0x****
//
// bypass mode:
// #define CFG_SDRAM_OUT     CFGOUT(a,b)
// #define CFG_SDRAM_IN      CFGIN0(0,0)         /* no-use */
// #define CFG_SDRAM_IN_DLY  CFGIN0(1,c,d)
// #define CFG_SDRAM_PADCTRL 0x****
//
// You can SDRAM test result to setup (a,b,c,d)
// 
// (a,b) defines the output interface delay.
// b -> output interface clock select.
// a -> extra inserted delay with respect to the selected clock source
// (b=0) will choose the invert of system clock.
// usually we choose (b=0).  choose a minimum value with margin for (a) 
//
// (c,d) defines the input interface clock delay.
// d -> input interface clock select.
// c -> extra inserted delay with respect to the selected clock source
// (d=1) will choose the system clock.
// usually we choose (d=1).  choose a minimum value with margin for (c) 
//
// For example, if test sdram testing result is:
// >> sdram_test config  OUT 0002-0000 IN 0005-0001 passed
// then, a=2,b=0,c=5,d=1
// and in this file you should define:
// #define CFG_SDRAM_OUT     CFGOUT(2,0)
// #define CFG_SDRAM_IN      CFGIN0(5,1)
//
//

#define CFGOUT(dly, mode)           (((dly)<<3)|(mode))
#define CFGIN0(dly, mode)           (((dly)<<3)|(mode))
#define CFGIN1(dly, mode, bypass)   (((bypass)<<7)|((dly)<<3)|(mode))

#if defined(IC_1002)
	#define CFG_SDRAM_OUT		CFGOUT(6 ,0)
	#define CFG_SDRAM_IN		CFGIN0(11,0)
	#define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)
	#define CFG_SDRAM_PADCTRL	(0x0002)	
//	#define CFG_SDRAM_OUT		CFGOUT(0 ,0)
//	#define CFG_SDRAM_IN		CFGIN0(4,0)
//	#define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)
//	#define CFG_SDRAM_PADCTRL	(0x5555)
#elif defined(IC_8202L) //rbhung,2006/4/13
    #if defined(EMU_BOARD_128_PIN)
        #define CFG_SDRAM_OUT	    CFGOUT(6,2)				//0~15, 0~1
        #define CFG_SDRAM_IN        CFGIN0(8,0)			    //0~15, 0~1
        #define CFG_SDRAM_IN_DLY    CFGIN1(2,0,0)           //no bypass 
        #define CFG_SDRAM_PADCTRL   (0x5557)				//0x5555~0xffff
    #elif defined(MP_BOARD_128_PIN)
        #define CFG_SDRAM_OUT	    CFGOUT(8,2)				//0~15, 0~1
        #define CFG_SDRAM_IN        CFGIN0(8,0)			    //0~15, 0~1
        #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)           //no bypass 
        #define CFG_SDRAM_PADCTRL   (0x5557)				//0x5555~0xffff
    #endif            
#elif defined(IC_8203A)
    #define CFG_SDRAM_OUT	    CFGOUT(5,0)				//0~15, 0~1
    #define CFG_SDRAM_IN        CFGIN0(4,1)			//0~15, 0~1
    #define CFG_SDRAM_IN_DLY    CFGIN1(1,0,0)       // 
    #define CFG_SDRAM_PADCTRL   (0x555b)				// 0x5555~0xffff
#elif defined(SPHE1000)
    #define CFG_SDRAM_OUT       CFGOUT(1,0)	
    #define CFG_SDRAM_IN        CFGIN0(3,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0x565A)    

#ifndef CFG_SDRAM_OUT_PS21
    #define CFG_SDRAM_OUT_PS21       CFGOUT(2,0)
    #define CFG_SDRAM_IN_PS21        CFGIN0(1,6)
    #define CFG_SDRAM_IN_DLY_PS21    CFGIN1(0,0,0)       // no-bypass
    #define CFG_SDRAM_PADCTRL_PS21   (0x555A)
#endif

#else

#if     defined(EMU_216_SOCKET_STD_CORNER)
    // 216-pin socket
     #if 1//def IC_8202_B    ////kenny 2004/4/21//NONO 5-3-14 22:56 IC_8202_B->1
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0xAAAF)    
    #else
    #define CFG_SDRAM_OUT       CFGOUT(3,0)
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)       // no-bypass
    #define CFG_SDRAM_PADCTRL   (0xFFFF)
    #endif
#elif   defined(EMU_216_SOCKET_FAST_CORNER)    
	#if 1//def IC_8202_B    ////kenny 2004/4/21//NONO 5-3-14 22:56 IC_8202_B->1
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0xAAAF)    
    #else
    #define CFG_SDRAM_OUT       CFGOUT(5,0)	   
    #define CFG_SDRAM_IN        CFGIN0(6,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(1,4,1)    // bypass
    #define CFG_SDRAM_PADCTRL   (0x555B)
    #endif
    
#elif   defined(EMU_216_REAL_FAST_CORNER)
    // 216-pin EMU PCB for real chip
	#if 1//def IC_8202_B    //terry,2004/4/8 03:58PM//NONO 5-3-14 22:56 IC_8202_B->1
    //#define CFG_SDRAM_OUT       CFGOUT(3,0)
    //#define CFG_SDRAM_IN        CFGIN0(0,6)
    //#define CFG_SDRAM_IN_DLY    CFGIN1(3,1,1)       // no-bypass
    //#define CFG_SDRAM_PADCTRL   (0xaaFF)
    
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	//kenny 2004/4/21
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0xAAAF)    
 	#else
    #define CFG_SDRAM_OUT       CFGOUT(2,0)
    #define CFG_SDRAM_IN        CFGIN0(0,6)
    #define CFG_SDRAM_IN_DLY    CFGIN1(4,1,1)       // no-bypass
    #define CFG_SDRAM_PADCTRL   (0xaaFF)
 	#endif
    
#elif   defined(EMU_216_REAL_STD_CORNER)
    // 216-pin EMU PCB for real chip
    #define CFG_SDRAM_OUT       CFGOUT(2,0)	//2002/2/24
    #define CFG_SDRAM_IN        CFGIN0(4,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)   // no-bypass
    #define CFG_SDRAM_PADCTRL   (0xAAFF)
#elif   defined(EMU_256_SHARE_SOCKET_FAST_CORNER)
    // 256-pin socket
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0xAAAF)          
#elif   defined(EMU_256_SHARE_SOCKET_STD_CORNER)
    // 256-pin socket
    #if 1//def IC_8202_B    ////kenny 2004/4/21//NONO 5-3-14 22:56 IC_8202_B->1
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0xAAAF)    
    #else
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	   //kenny 2004/2/13
    #define CFG_SDRAM_IN        CFGIN0(4,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(1,4,1)    // bypass
    #define CFG_SDRAM_PADCTRL   (0x555B)
	#endif
#elif   defined(MP_BOARD_256_NON_SHARE_STD_CORNER)
     // 256-pin non-shared
     
    #define CFG_SDRAM_OUT_PS21       CFGOUT(2,0)
    #define CFG_SDRAM_IN_PS21        CFGIN0(1,6)
    #define CFG_SDRAM_IN_DLY_PS21    CFGIN1(0,0,0)       // no-bypass
    #define CFG_SDRAM_PADCTRL_PS21   (0x555A)
    
	#ifdef IC_8202E      //8202E                 //chyeh 2005/01/05
        #define CFG_SDRAM_OUT       CFGOUT(2,0)
        #define CFG_SDRAM_IN        CFGIN0(2,1)
        #define CFG_SDRAM_IN_DLY    CFGIN1(4,1,1)    // bypass
        #define CFG_SDRAM_PADCTRL   (0x4444) 
    #elif defined(IC_8104A) // chyeh 2005/03/16   temporary parameter
        //kevinmonkey 050520, move 8104 up, see VSS ver37 also
        #define CFG_SDRAM_OUT       CFGOUT(3,0)	    
        #define CFG_SDRAM_IN        CFGIN0(2,1)
        #define CFG_SDRAM_PADCTRL   (0xFFFF)    
        #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)               
    #elif defined(IC_8202D) // tomcat 2005/02/16   
        //#define CFG_SDRAM_OUT       CFGOUT(6,0)	
        //#define CFG_SDRAM_IN        CFGIN0(6,7)
        //#define CFG_SDRAM_PADCTRL   (0xafff)    
        //#define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass 
        #if defined(ALCO_PORTABLE)&&defined(SDRAM_16Mb_Mode)
        #define CFG_SDRAM_OUT       CFGOUT(4,0)//rbhung for alco
        #else
        #define CFG_SDRAM_OUT       CFGOUT(6,0)
        #endif
		#define CFG_SDRAM_IN        CFGIN0(0,0)
		#define CFG_SDRAM_PADCTRL   (0xA5FF)
		#if defined(ALCO_PORTABLE)&&defined(SDRAM_16Mb_Mode)
		#define CFG_SDRAM_IN_DLY    CFGIN1(2,1,1)
		#else
		#define CFG_SDRAM_IN_DLY    CFGIN1(3,1,1)
		#endif
	#else        //8202X
        #define CFG_SDRAM_OUT       CFGOUT(2,0)
        #define CFG_SDRAM_IN        CFGIN0(2,1)
        #define CFG_SDRAM_IN_DLY    CFGIN1(1,4,1)       // bypass
        #define CFG_SDRAM_PADCTRL   (0x555B)
	#endif   
#elif   defined(MP_BOARD_216_PIN_STD_CORNER)
    // 216-pin PP PCB
    #define CFG_SDRAM_OUT_PS21       CFGOUT(2,0)
    #define CFG_SDRAM_IN_PS21        CFGIN0(1,6)
    #define CFG_SDRAM_IN_DLY_PS21    CFGIN1(0,0,0)       // no-bypass
    #define CFG_SDRAM_PADCTRL_PS21   (0x555A)
    
    #ifdef IC_8202E      //8202E                 //chyeh 2005/02/24
        #define CFG_SDRAM_OUT       CFGOUT(2,0)    // add for 8202E 216 pin define
        #define CFG_SDRAM_IN        CFGIN0(2,1)
        #define CFG_SDRAM_IN_DLY    CFGIN1(4,1,1)    // bypass
        #define CFG_SDRAM_PADCTRL   (0x4444) 
    #elif defined(IC_8202D)
//        #define CFG_SDRAM_OUT       CFGOUT(6,0)	
//        #define CFG_SDRAM_IN        CFGIN0(6,7)
//        #define CFG_SDRAM_PADCTRL   (0xafff)    
//        #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
		#if defined(ALCO_PORTABLE)&&defined(SDRAM_16Mb_Mode)
		#define CFG_SDRAM_OUT       CFGOUT(4,0)
		#else
		#define CFG_SDRAM_OUT       CFGOUT(6,0)
		#endif
		#define CFG_SDRAM_IN        CFGIN0(0,0)
		#define CFG_SDRAM_PADCTRL   (0xA5FF)
		#if defined(ALCO_PORTABLE)&&defined(SDRAM_16Mb_Mode)
		#define CFG_SDRAM_IN_DLY    CFGIN1(2,1,1)
		#else
		#define CFG_SDRAM_IN_DLY    CFGIN1(3,1,1)
		#endif
    #else
        #if 1//def IC_8202_B    ////kenny 2004/4/21//NONO 5-3-14 22:56 IC_8202_B->1
        #define CFG_SDRAM_OUT       CFGOUT(4,0)	
        #define CFG_SDRAM_IN        CFGIN0(2,1)
        #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
        #define CFG_SDRAM_PADCTRL   (0xAAAF)    
        #else    
        #define CFG_SDRAM_OUT       CFGOUT(2,0)	//2002/2/24
        #define CFG_SDRAM_IN        CFGIN0(4,1)
        #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)       // no-bypass
        #define CFG_SDRAM_PADCTRL   (0xAAFF)
        #endif
    #endif 	
#elif   defined(MP_BOARD_216_PIN_FAST_CORNER)
    // 216-pin PP PCB
    #if 1//def IC_8202_B    ////kenny 2004/4/21//NONO 5-3-14 22:56 IC_8202_B->1
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0xAAAF)    
    #else
    #define CFG_SDRAM_OUT       CFGOUT(3,0)	//2002/2/24
    #define CFG_SDRAM_IN        CFGIN0(5,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)       // no-bypass
    #define CFG_SDRAM_PADCTRL   (0xAAFF)
    #endif

#elif   defined(MP_BOARD_256_SHARE_STD_CORNER)
    // 256-pin PP PCB share mode
    #if 1//def IC_8202_B    ////kenny 2004/4/21//NONO 5-3-14 22:56 IC_8202_B->1
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0xAAAF)    
    #else
    #define CFG_SDRAM_OUT       CFGOUT(3,0)
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(1,4,1)       // bypass
    #define CFG_SDRAM_PADCTRL   (0x555B)
    #endif
        
#else
    #if 1//def IC_8202_B    ////kenny 2004/4/21//NONO 5-3-14 22:56 IC_8202_B->1
    #define CFG_SDRAM_OUT       CFGOUT(4,0)	
    #define CFG_SDRAM_IN        CFGIN0(2,1)
    #define CFG_SDRAM_IN_DLY    CFGIN1(0,0,0)    // bypass
    #define CFG_SDRAM_PADCTRL   (0xAAAF)    
    #else
    #define CFG_SDRAM_OUT       CFGOUT(2,0)
    #define CFG_SDRAM_IN        CFGIN0(0,6)
    #define CFG_SDRAM_IN_DLY    CFGIN1(4,1,1)       // no-bypass
    #define CFG_SDRAM_PADCTRL   (0xaaFF)
    #endif
#endif
#endif // SPHE1000


#ifndef CFG_SDRAM_OUT_PS21
    #define CFG_SDRAM_OUT_PS21       CFGOUT(2,0)
    #define CFG_SDRAM_IN_PS21        CFGIN0(1,6)
    #define CFG_SDRAM_IN_DLY_PS21    CFGIN1(0,0,0)       // no-bypass
    #define CFG_SDRAM_PADCTRL_PS21   (0x555A)
#endif


