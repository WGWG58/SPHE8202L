#ifndef _GB_STRUCT_H_
#define _GB_STRUCT_H_

#include "navdata.h"

//
// structures
//
typedef INT64   t_PTS;
typedef int (*ifunc)();
typedef int (*ifunc2)(int);
typedef	int	(*ifunc3)(UINT32*);
typedef	int	(*ifunc4)(int, UINT32*);
typedef int	(*ifunc5)(BYTE*, UINT32);
typedef void    (*vfunc)();
typedef	UINT32	(*u32func1)(UINT32);
typedef	UINT32	(*u32func2)(int);
typedef UINT32	(*u32func3)();

/*
** VARIABLE
** psd_list_now
**
** DESCRIPTION
** currently used psd-list, 0xffff if PSD disabled.
*/
typedef struct  {
  BYTE      psd_offset_multiplier;
  UINT32    psd_first_segment_msf;
  UINT16    psd_list_id;
  BYTE      psd_item_loop;
} t_psd_state;

/*
* setup menu
*/
typedef struct {    
    UINT16 ParentalLvl;//parental level
    UINT16 P_RCD;//player region code
    UINT16 AST_LCD;//audio stream language code
    UINT16 SPST_LCD;//sub-picture language code
    UINT16 SPSTN;
    UINT16 M_LCD;//menu language code
    UINT16 CTY_CD;//country code
    UINT16 P_V_CFG;//player video config
    UINT16 P_A_CFG;//player audio config
    UINT32 parent_passwd;
    UINT8  parental_ststus;
    #ifdef SUPER_DEFAULT_OSD_LANG
    UINT8  setup_default_osd_lang;
    #endif
    #ifdef ADD_DVI311_SETUP
    UINT8 SETUP_output_mode;		
    //UINT8 SETUP_311_power;		
    #endif
    #ifdef ADJUST_JPEG_SLIDE_TIME  //lyc  2005-8-12 17:38
      BYTE  SETUP_JpegSlideTimeFlag;
    #endif
} t_USER_SET;

#endif
