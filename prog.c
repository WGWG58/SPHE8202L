/*****************************************************\
Creater: Terry
Date   : 2001/5/14 05:30PM
Description: Program menu using
\*****************************************************/
#include "user_init.h"
#include "global.h"
#include "osd.h"
#include "sio.h"
#include "func.h"
#include "ircmd.h"
#include "vfd.h"
#include "vfdfunc.h"
#include "fs.h"		// alan 2002/11/7 08:58¤U¤È, in order to reference dAMG_LSN

#ifdef SUPPORT_WMA        //nono 4-9-3 20:36    
#include "asf_if.h"
#endif

//#define NOT_SUPPORT_PROG
#ifdef NOT_SUPPORT_PROG
#include "prog_null_func.c"
#else

//#define MONE_PROG

#define MAX_PROG_PAGE       2

#define MAX_PROG_ITEM       8
#define MAX_PROG_SEL        8

#ifdef PROG_12_ITEMS
#define MAX_FUNC_X          2
#define MIN_FUNC_X          1
#else // 16 items
#define MAX_FUNC_X          4
#define MIN_FUNC_X          3
#endif

#ifdef OSD_BMP_PROG
#define MAX_NM_Y            5
#else
#define MAX_NM_Y            4
#endif

#define MIN_NM_Y            2


//extern void osd_restore();
extern void add_input_num(int *v) ;
/***********   Item description  **********************\

BYTE	function
0		mode(MSB 4bits)  ==>show direction picture
	0x0:no effect
	0x1:basic select function
	0x2:can enter number
	0x3:need run function by osd id
\******************************************************/
enum
{
SET_NE=0,
SET_NM=0x1,
SET_FUNC=0x2,
SET_TT,
};

const UINT8 prog_item[MAX_PROG_PAGE][MAX_PROG_ITEM][MAX_PROG_SEL] =
{
	{
		//page 1
		{SET_TT,STR_OS_PROG,STR_OS_SPACE,STR_OS_SPACE,STR_OS_SPACE},
		{SET_TT,STR_OS_T_C,STR_OS_T_C,STR_OS_T_C,STR_OS_T_C},
		{SET_NM,STR_OS_,STR_OS_,STR_OS_,STR_OS_},
		{SET_NM,STR_OS_,STR_OS_,STR_OS_,STR_OS_},
		{SET_NM,STR_OS_,STR_OS_,STR_OS_,STR_OS_},
		{SET_NM,STR_OS_,STR_OS_,STR_OS_,STR_OS_},
#ifdef OSD_BMP_PROG
		{SET_NM,STR_OS_,STR_OS_,STR_OS_,STR_OS_},
		{SET_FUNC,0,STR_OS_PLAY,STR_OS_CLEAR,0},
#else
		{SET_FUNC,0,STR_OS_PLAY,STR_OS_CLEAR,0},
		{0,0,0,0,0}
#endif		
	},
	{
		//page 2
		{SET_TT,STR_OS_PROG,STR_OS_EDIT,0,0},
		{SET_TT,STR_OS_SPACE,STR_OS_SPACE,STR_OS_SPACE,STR_OS_SPACE},
		{SET_NM,STR_OS_F,STR_OS_F,STR_OS_F,STR_OS_F},
		{SET_NM,STR_OS_F,STR_OS_F,STR_OS_F,STR_OS_F},
		{SET_NM,STR_OS_F,STR_OS_F,STR_OS_F,STR_OS_F},
		{SET_NM,STR_OS_F,STR_OS_F,STR_OS_F,STR_OS_F},
#ifdef OSD_BMP_PROG
		{SET_NM,STR_OS_,STR_OS_,STR_OS_,STR_OS_},
		{SET_FUNC,0,STR_OS_PLAY,STR_OS_CLEAR,0},
#else
		{SET_FUNC,0,STR_OS_PLAY,STR_OS_CLEAR,0},
		{0,0,0,0,0}
#endif		
	}
};

#define SW_REGION1          0x10
#define SW_REGION2          0x20
#define SW_REGION3          0x30
#define SW_REGION4          0x40
#define SW_REGION_ANTI      0x20
//#define SW_REGION_F_ANTI    0x30
//#define SW_REGION_B_ANTI    0x40
//#define SW_REGION_OFF       0x10

UINT8 id,sel,page,offset;

extern UINT8 ChkPTTRange(UINT8 *tt,UINT16 *ptt);    //Jeff 20010717
extern UINT8 ChkTrkRange(UINT8 *gp,UINT16 *trk);	// alan 2002/11/8 11:34¤W¤È
extern void InitSW_region(void);

extern int FSChkProg(BYTE iPage, BYTE iItem);   //Jeff 20010808

#ifdef MP3_DIRECT_SELECT
#include "prog_mp3dir.c"
#else
#include "prog_mp3undir.c"
#endif

#endif//#ifdef NOT_SUPPORT_PROG
//---------------------------------------ending--------------------------------------

