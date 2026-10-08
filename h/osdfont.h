#ifndef __OSDFONT_H
#define	__OSDFONT_H
/*
#if 0
extern  const   BYTE    *fn_12x24gbst[];
extern  const   BYTE    *fn_8x16gbfs[];
extern  const   BYTE    *fn_8x16gbst[];

  // non-proportional font
  extern  const   BYTE    *fn_helvR08[];
  extern  const   BYTE    *fn_helvR10[];
  extern  const   BYTE    *fn_helvr12[];
  extern  const   BYTE    *fn_helvR14[];
  extern  const   BYTE    *fn_courR08[];
  extern  const   BYTE    *fn_courR10[];
  extern  const   BYTE    *fn_courR12[];
  extern  const   BYTE    *fn_courR14[];
  extern  const   BYTE    *fn_timR08[];
  extern  const   BYTE    *fn_timR10[];
  extern  const   BYTE    *fn_timR12[];
  extern  const   BYTE    *fn_timR14[];
  
	//#define font_table      fn_12x24gbst
	#define font_table fn_8x16gbst
	#define	fn_DEFAULT font_table
	#endif
*/

#include "user_init.h"

#ifdef OSD_FONT_COMPRESS

extern  const UINT16 fn_table700[];	/* alan 020417 */
extern  const UINT16 fn_table700_2[]; //Jeff 20010830  /* alan 020417 */

#ifdef USE_NEW_SCHINESE_OSD //liyl add 20060116
extern  const UINT16 fn_table700_3[];
#endif  //end=> #ifdef USE_NEW_SCHINESE_OSD

extern  const UINT16 Icon_table[];
extern  const UINT16 fn_icon[];

#else

extern  const BYTE *fn_table700[];
extern  const BYTE *fn_table700_2[];

#ifdef USE_NEW_SCHINESE_OSD //liyl add 20060116
extern  const BYTE *fn_table700_3[];
#endif    //end=> #ifdef USE_NEW_SCHINESE_OSD

extern  const BYTE *Icon_table[];
extern  const BYTE *fn_icon[];

#endif

#define font_table      fn_table700
#define font_table2     fn_table700_2 //Jeff 20010830

#ifdef USE_NEW_SCHINESE_OSD //liyl add 20060116
#define font_table3     fn_table700_3
#endif    //end=> #ifdef USE_NEW_SCHINESE_OSD

#define setup_icon      Icon_table
#define play_icon       fn_icon

#define	fn_DEFAULT		font_table

#endif/*__OSDFONT_H*/


