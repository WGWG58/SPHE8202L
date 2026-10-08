/*************************************************************
** FILE
** fsmidiui_progctrl.h
**
** DESCRIPTION
** This file contains simple ui control function
**
**
** Create:   xlluo
** Maintain:
**             xlluo 2005/06/01: create
**             
***************************************************************/

#ifndef __FSMIDIUI_PROGCTRL_H__
#define __FSMIDIUI_PROGCTRL_H__
//include

//marco
#ifdef EXTERN_FSMIDIUI_PROGCTRL_HERE
#define EXTERN_FSMIDIUI_PROGCTRL
#else
#define EXTERN_FSMIDIUI_PROGCTRL extern
#endif//EXTERN_FSMIDIUI_MENUCTRL_HERE

#ifdef EXTERN_FSMIDIUI_PROGCTRL_QUEUE_HERE
#define EXTERN_FSMIDIUI_PROGCTRL_QUEUE
#else
#define EXTERN_FSMIDIUI_PROGCTRL_QUEUE extern
#endif//EXTERN_FSMIDIUI_MENUCTRL_HERE
//global

//function
//file: fsmidiui_progctrl.c

//file:fsmidui_prog_queue.c
EXTERN_FSMIDIUI_PROGCTRL_QUEUE void InitRingQueue(void);
EXTERN_FSMIDIUI_PROGCTRL_QUEUE void CursorMoveRight(void);
EXTERN_FSMIDIUI_PROGCTRL_QUEUE void CursorMoveLeft(void);
EXTERN_FSMIDIUI_PROGCTRL_QUEUE BYTE bIsQueueEmpty(void);
EXTERN_FSMIDIUI_PROGCTRL_QUEUE BYTE bQueueNextPlayAvail(void);
EXTERN_FSMIDIUI_PROGCTRL_QUEUE BYTE bQueueIsFull(void);
EXTERN_FSMIDIUI_PROGCTRL_QUEUE UINT32 GetNextSongCode(void);
EXTERN_FSMIDIUI_PROGCTRL_QUEUE void OutputQueueSongCode(void);
EXTERN_FSMIDIUI_PROGCTRL_QUEUE BYTE ClearCursorSongCode(void);


#endif//__FSMIDIUI_PROGCTRL_H__


