#ifndef	__TASK_H
#define	__TASK_H

#include "types.h"
#include "regloc.h"

#define	REG_SAVED	REGLOC_NUM

typedef	struct	{
  UINT32  reg[REG_SAVED];
  BYTE	  frac;
} t_task;

typedef	struct	{
  BYTE	task_now;
  BYTE	task_num;
  BYTE	task_len;
  BYTE	task_busy;
  void *task_entry;
} t_taskstate;


#include "bufloc.h"
#include "set.h"

#ifdef	DVDRELEASE	    
#define			TASKNO_MAX	1
#else
#define			TASKNO_MAX	2

EXTERN_DATABUF		t_taskstate	task_state;
EXTERN_DATABUF		t_task		task_table[TASKNO_MAX];


#define SET_TASK(n)     {       \
                        task_state.task_now     = n;                    \
                        task_state.task_entry   = &task_table[n];       \
                        task_state.task_len     = task_table[n].frac;   \
                        }
#endif

void	reset_task(void);
#define NextTask()      asm volatile("syscall 0");

#endif/*__TASK_H*/
