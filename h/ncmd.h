#ifndef __NCMD_H__
#define __NCMD_H__

//Jump Option
#define EXIT 			1
#define JUMP_TT 		2
#define JUMP_VTS_TT 	3
#define JUMP_VTS_PTT	5
#define JUMP_SS			6
#define CALL_SS			8

/*alan 2002/10/18 02:07¤U¤È, Jump option for DVD_AUDIO */
#define JUMP_TT_GR		9
#define JUMP_TK			10
#define AMSM_RSM		11

#define FP_DOM				(0)
#define VMGM_DOM			(1)
#define VTSM_DOM			(2)
#define VMGM_DOM_PGCN	(3)
#define TT_DOM				(4)
#define STOP_STATE		(5)

//Menu ID , VI4-218
#define TITLE_MENU			(2)
#define ROOT_MENU				(3)
#define SUB_PICTURE_MENU	(4)
#define AUDIO_MENU			(5)
#define ANGLE_MENU			(6)
#define PTT_MENU				(7)





extern t_NCMD d_NCMD;

void NCMD_decode(void);

void NCMD_exec_GoTo(UINT8 GoTo_Option, UINT16 GoTo_Operand);
void NCMD_exec_Compare(UINT8 Compare_Option, UINT8 CP1, UINT16 C2, UINT8 I_flag);
void NCMD_exec_Link(UINT8 Link_Option, UINT16 Link_Operand);

void NCMD_exec_Jump(UINT8 Jump_Option, UINT32 Jump_Operand);
void NCMD_exec_SetSystem(UINT8 SetSystem_Option, UINT32 SetSystem_Operand, UINT8 I_flag);
void NCMD_exec_Set(UINT8 Set_Option, UINT8 SG, UINT16 SS, UINT8 I_flag);
void NCMD_exec_JumpTT(UINT8);
void NCMD_exec_JumpVTS_PTT(UINT8, UINT16);

// alan 2002/10/22 04:34¤U¤È
void NCMD_exe_JumpTT_GR_TK(UINT8, UINT8);

void NCMD_exec_LinkPrevPGC(void);
void NCMD_exec_RSM(int);
#endif /* __NCMD_H__ */
