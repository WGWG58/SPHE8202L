#ifndef	__TIMER_H
#define __TIMER_H

#include "types.h"

#include "stc.h"

void   set_stc_val(INT64);
void   set_rtc_val(UINT32);

#define	get_stc_val_32()	get_stc_32()
#define	get_stc_val()		get_stc()
UINT32 get_rtc_val(void);		// 100Hz

#endif
