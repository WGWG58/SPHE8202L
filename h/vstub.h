#ifndef	__VSTUB_H
#define	__VSTUB_H

extern	UINT32		__save_r00[];
extern	UINT32		__save_stk[];

#define	C0_STATUS	32
#define	C0_CAUSE	33
#define	C0_EPC		34

#define	__reg(n)	(__save_r00[(n)])
#define	__c0_status	(__save_r00[C0_STATUS])
#define	__c0_cause	(__save_r00[C0_CAUSE])
#define	__c0_epc	(__save_r00[C0_EPC])

extern	void		__swap(void *func);

#endif/*__VSTUB_H*/

