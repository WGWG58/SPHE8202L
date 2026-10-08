/*
*  Terry,2004/3/29 03:44PM 
*  Board setting
*/

//Sdram timing define
#if defined(EMU_BOARD_216_PIN)
//#define EMU_216_REAL_STD_CORNER
#define EMU_216_REAL_FAST_CORNER
//#define EMU_216_REAL_FAST_CORNER_B//4-4-7 23:29
//#define EMU_216_SOCKET_STD_CORNER
//#define EMU_216_SOCKET_FAST_CORNER
#endif 

#if defined(EMU_BOARD_256_SHARE)
#define EMU_256_SHARE_REAL_STD_CORNER
//#define EMU_256_SHARE_SOCKET_STD_CORNER
//#define EMU_256_SHARE_SOCKET_FAST_CORNER
//#define EMU_256_NON_SHARE_SOCKET_STD_CORNER
#endif

#if defined(MP_BOARD_216_PIN)
//#define MP_BOARD_216_PIN_STD_CORNER
#define MP_BOARD_216_PIN_FAST_CORNER
#endif

#if defined(MP_BOARD_256_PIN_SHARE)
#define MP_BOARD_256_SHARE_STD_CORNER
#endif

#if defined(MP_BOARD_256_PIN_NON_SHARE)||defined( MP_BOARD_216_PIN_NON_SHARE)
//ronnie 2004/8/4//nono restore "2004/8/4" on 2005/3/14
#define MP_BOARD_256_NON_SHARE_STD_CORNER

//#elif defined( MP_BOARD_216_PIN_NON_SHARE)//FanGang added 2005-1-12 19:32
//#define MP_BOARD_216_PIN_STD_CORNER
#endif




#if defined(EMU_BOARD_216_PIN) ||defined(EMU_BOARD_256_SHARE)||defined(EMU_BOARD_256_NON_SHARE)
#define USE_8_CH_DAC //define for emulation board, for using 10 ch audio, data0~data3

#endif

#if defined( MP_BOARD_256_PIN_NON_SHARE)||defined( MP_BOARD_216_PIN_NON_SHARE)//kenny 2004/7/14
#define SPHE8202_NONSHARED
#endif

#if defined(IC_8202L) || defined(IC_8203A) //terry,2006/4/7 05:23¤U¤È
#define SPHE8202_NONSHARED
#endif

