#ifndef	__STC_H
#define	__STC_H

#include "types.h"
#include "regmap.h"

//
// inline
#define get_stc_16_inline()    (regs0->stc_15_0)
#define get_stc_32_inline()    (regs0->stc_15_0 | (regs0->stc_31_16<<16))

//
// kernel function
extern	UINT32	_get_stc_32(void);
extern	INT64	_get_stc(void);
extern	UINT32	_get_rtc(void);


#define get_stc_16()    get_stc_16_inline()
#define	get_stc_32()	_get_stc_32()
#define	get_stc()	_get_stc()
#define	get_rtc()	_get_rtc()


#define	set_astc(stc)   \
	do {                                    \
            UINT32 __sl = (stc);	        \
            UINT32 __sh = (UINT64)(stc)>>32;    \
            regs0->stc_32       = __sh;         \
            regs0->stc_31_16    = __sl>>16;     \
            regs0->stc_15_0     = __sl;         \
	} while (0)


#define	set_stc(stc)    \
        do {                \
            set_astc(stc);  \
        } while (0) 


#define	set_sstc(n,stc) \
        do {                \
            set_astc(stc);  \
        } while (0) 


#define	set_rtc(v)  \
        do {                                \
            regs0->rtc_31_16 = ((v)>>16);   \
            regs0->rtc_15_0  = ((v));       \
        } while (0)


#define	reset_rtc()	(regs0->rtc_31_16=0)

extern	UINT8   STC_state;

#define	STCST_INIT	0
#define STCST_TRACKVPTS	1
#define	STCST_LOCKED	3

#define set_stc_valid()	(STC_state=STCST_LOCKED)
#define set_stc_init()	(STC_state=STCST_INIT)
#define set_stc_track()	(STC_state=STCST_TRACKVPTS)

#define	is_stc_valid()	(STC_state==STCST_LOCKED)
#define is_stc_track()	(STC_state==STCST_TRACKVPTS)
#define is_stc_init()	(STC_state==STCST_INIT)

#endif/*__STC_H*/

