//
// FILE
// cpu.h
//
// DESCRIPTION
// CPU related control
//
#ifndef	__CPU_H
#define	__CPU_H

#include "types.h"

int	cpu_intr_config(int);
int	cpu_intr_enable(void);
int	cpu_intr_disable(void);

UINT32	cpu_set_intr_mask(UINT32 mask);
UINT32	cpu_get_intr_mask(void);

UINT32	cpu_get_status(void);
UINT32	cpu_get_cause(void);
UINT32	cpu_get_epc(void);
UINT32	cpu_get_badva(void);

#define	CRITICAL_ENTER()	cpu_intr_disable()
#define	CRITICAL_LEAVE()	cpu_intr_enable()

#endif/*__CPU_H*/

