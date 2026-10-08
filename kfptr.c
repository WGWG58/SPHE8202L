//
// FILE
// kfptr.c
//
// kernel functional-pointer value
//
#include "config.h"
#include "regmap.h"


//#define SUPPORT_FULLPEL   //mark it, for PS2.1
#if !defined(SDRAM_16Mb_Mode) && !defined(MAKE_ONLY_UPDATE_CODE) //terry,2004/12/3 07:19PM
//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
#define SUPPORT_CVDOGT
#define SUPPORT_SVCDOGT
//2006-04-12, mimitsai add for IC_8202xx relative
/* //move to cust_def.h
#if !defined(IC_8202D)&&!defined(IC_8202E)&& !defined(IC_8202L) && !defined(IC_8203A)
#define SUPPORT_FULLPEL   //mark it, for PS2.1 ,terry,2005/3/21 08:57¤U¤È
#endif
*/
#endif

extern  int nullfunc();
extern  int do_system_drop();

//
// CVD
//
extern  int do_system_private1_70();
extern  int spd_decode_dcsq_cvd_func();
extern  int sup_update_cvd_func();

#ifdef  SUPPORT_CVDOGT
const UINT8 kernel_support_svcdogt          = 1;
const void * const do_system_parse_cvdogt_fptr    = do_system_private1_70;
const void * const spd_decode_dcsq_cvd_fptr       = spd_decode_dcsq_cvd_func;
const void * const sup_update_cvd_fptr            = sup_update_cvd_func;
#else
const UINT8 kernel_support_svcdogt          = 0;
const void * const do_system_parse_cvdogt_fptr    = do_system_drop;
const void * const spd_decode_dcsq_cvd_fptr       = nullfunc;
const void * const sup_update_cvd_fptr            = nullfunc;
#endif


//
// SVCD
//
extern  int spd_create_svcdsph_header_func();
extern  int spd_decode_dcsq_svcd_func();
extern  int sup_update_svcd_func();

#ifdef  SUPPORT_SVCDOGT
const void * const spd_create_svcdsph_header_fptr = spd_create_svcdsph_header_func;
const void * const spd_decode_dcsq_svcd_fptr      = spd_decode_dcsq_svcd_func;
const void * const sup_update_svcd_fptr           = sup_update_svcd_func;
#else
const void * const spd_create_svcdsph_header_fptr = nullfunc;
const void * const spd_decode_dcsq_svcd_fptr      = nullfunc;
const void * const sup_update_svcd_fptr           = nullfunc;
#endif


extern  int do_video_dumping_fixfullpel();
extern  int reset_video_dumping_fixfullpel();
extern  int do_video_dumping_orig();
extern  int reset_video_dumping_orig();

#ifdef  HW_SUPPORT_FULLPEL
const BYTE          fix_fullpel  = 1;
const void * const reset_video_dumping_fptr         = reset_video_dumping_fixfullpel;
const void * const do_video_dumping_fptr            = do_video_dumping_fixfullpel;
#else
const BYTE          fix_fullpel  = 0;
const void * const reset_video_dumping_fptr         = reset_video_dumping_orig;
const void * const do_video_dumping_fptr            = do_video_dumping_orig;
#endif
