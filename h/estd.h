#ifndef	__ESTD_H
#define	__ESTD_H

void ESTD_reset(void);
void ESTD_timing_T1(INT64 STC_offset);
void ESTD_timing_T4(void);

//
// SW1/SW4 get/set
//
extern	UINT8	ESTD_SW1_minus;
extern	UINT32	ESTD_STC_offset;
#define	get_estd_stc_offset()	((UINT32)ESTD_STC_offset)
#define	set_estd_stc_offset(s)	(ESTD_STC_offset = ((UINT32)(s)))

static inline unsigned	ESTD_in_T1()
{
  return ESTD_SW1_minus;
}

#include "stc.h"

static inline INT64 ESTD_get_stc_SW1()
{
  INT64 stc;
  stc = get_stc();
  if (ESTD_SW1_minus) stc-=get_estd_stc_offset();
  return stc;
}

static	inline	INT64	ESTD_get_stc_SW4()
{
  return get_stc();
}

void  ESTD_set_stc_SW1(INT64 stc_val);
void  ESTD_set_stc_SW4(INT64 stc_val);

#endif
