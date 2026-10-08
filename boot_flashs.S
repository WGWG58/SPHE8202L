#include "regdef.h"
#include "regmapa.h"
#include "config.h"
#include "user_init.h"

#ifdef SPHE1000
#define STATUS_ENDIAN_LITTLE    (0<<25)
#define STATUS_SETUP            STATUS_COP0|STATUS_ENDIAN_LITTLE|STATUS_BEV
#endif //#ifdef SPHE1000

.text
		.global init_gp_sp
		.extern	s_gp
		.extern	_gp

		.global	_cpu_set_intr_mask
		.global	_cpu_get_intr_mask
		.global	_cpu_intr_config
		.global	_cpu_intr_enable
		.global	_cpu_intr_disable
		.global	_cpu_invalidate_dcache

		.global	_cpu_get_status
		.global	_cpu_get_cause
		.global	_cpu_get_epc
		.global	_cpu_get_badva

.text
		.ent	init_gp_sp

init_gp_sp:

#ifdef SPHE1000
                // ENABLE COP0/3
                mfc0    t1, C0_STATUS
                li      t0, STATUS_SETUP
				//or      t1, t0
                mtc0    t0, C0_STATUS
                nop
                nop
                nop
#endif //#ifdef SPHE1000


		// setup register-file pointer
		li		s6, RGST_OFFSET

		la		sp, _stkptr         		    // set up stack pointer

		//lw		gp, s_gp						// set up GP
		la		gp, _gp						// set up GP

		j		boot_flash_main

		.end	init_gp_sp          


/*
** FUNCTION
** UINT32	cpu_set_intr_mask(UINT32 mask[7:0]);
**
** DESCRIPTION
** set r3k CP0 interrupt mask, 1 to enable.
*/
		.ent	_cpu_set_intr_mask
_cpu_set_intr_mask:
                mfc0    t0, C0_STATUS		/* get STATUS[31:0] in t0	*/
		andi	a0, 0x00ff		/* clip a0 (new mask)		*/
		sll	a0, 8			/* {IM[7:0], 8'b0}		*/
		andi	t1, t0, 0xff00		/* get current IM in t1		*/
		xor	t0, t1			/* toggle mask bits for t0	*/
		or	t0, a0			/* insert new intr_mask to t0	*/
                mtc0    t0, C0_STATUS		/* write to STATUS		*/
		srl	v0, t1, 8		/* return last IM		*/
		jr	ra
		.end	_cpu_set_intr_mask

/*
** FUNCION
** UINT32	cpu_get_intr_mask(void);
**
** DESCRIPTION
** get r3k CP0 interrupt mask, 1:enabled, 0:disabled
*/
		.ent	_cpu_get_intr_mask
_cpu_get_intr_mask:
		mfc0	v0, C0_STATUS
		srl	v0, 8
		andi	v0, 0x00ff
		jr	ra
		.end	_cpu_get_intr_mask


/*
** FUNCION
** void		cpu_intr_disable(void);
**
** DESCRIPTION
** disable R3000 interrupt (globally)
*/
		.ent	_cpu_intr_config
_cpu_intr_config:
		beqz	a0, _cpu_intr_disable
		/* fall thru if 1 */
/*
** FUNCION
** int		cpu_intr_enable(void);
**
** DESCRIPTIN
** enable R3000 interrupt (globally) 
*/
_cpu_intr_enable:
		mfc0	v0, C0_STATUS
		ori	a0, v0, STATUS_IEc		/* enable STATUS_IEc	*/
_cpu_intr_status_set:
		mtc0	a0, C0_STATUS
		andi	v0, 1				/* get last status	*/
		jr	ra


/*
** FUNCION
** int		cpu_intr_disable(void);
**
** DESCRIPTION
** disable R3000 interrupt (globally)
*/
_cpu_intr_disable:
		mfc0	v0, C0_STATUS
		li	a0, ~STATUS_IEc
		and	a0, v0
		b	_cpu_intr_status_set
		.end	_cpu_intr_config


/*
** FUNCTION
** void		cpu_invalidate_dcache
**
** DESCRIPTION
** invalidate data cache
*/
		.global	_cpu_invalidate_dcache
		.ent	_cpu_invalidate_dcache
_cpu_invalidate_dcache:
		//
		// invalidate/reset cache
		//
		.set	noreorder
		mtc0	zero, C0_CCTL		//
		li	v0, CCTL_DIvl		// 0 to 1 transition
		mtc0	v0, C0_CCTL		//
		mtc0	zero, C0_CCTL		//
		.set	reorder
		nop
		nop
		nop
		nop
		jr 	ra
		.end	_cpu_invalidate_dcache


/*
** cpu_get_status
*/
_cpu_get_status:
		mfc0	v0, C0_STATUS
		jr	ra

/*
** cpu_get_cause
*/
_cpu_get_cause:
		mfc0	v0, C0_CAUSE
		jr	ra

/*
** cpu_get_epc
*/
_cpu_get_epc:
		mfc0	v0, C0_EPC
		jr	ra

/*
** cpu_get_badva
*/
_cpu_get_badva:
		mfc0	v0, C0_BADVA
		jr	ra

