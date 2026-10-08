/*
** FILE
** emu.c
**
** DESCRIPTION
*/
#include "config.h"
#include "global.h"
#include "regmap.h"
#include "pu8560.h"
#include "emu.h"

#ifndef DVDRELEASE

//
// emulation system clock ratio (with respect to ck27)
//
#define	EMU_CFG7_DIV_1			0
#define	EMU_CFG7_DIV_1_5		1
#define	EMU_CFG7_DIV_2			2
#define	EMU_CFG7_DIV_2_5		3
#define	EMU_CFG7_DIV_3			4
#define	EMU_CFG7_DIV_3_5		5
#define	EMU_CFG7_DIV_4			6
#define	EMU_CFG7_DIV_4_5		7
#define	EMU_CFG7_DIV_5			8
#define	EMU_CFG7_DIV_5_5		9
#define	EMU_CFG7_DIV_6			10
#define	EMU_CFG7_DIV_6_5		11
#define	EMU_CFG7_DIV_7			12
#define	EMU_CFG7_DIV_7_5		13
#define	EMU_CFG7_DIV_8			14
#define	EMU_CFG7_DIV_8_5		15

#define	EMU_CFG7_CLK_27_0		EMU_CFG7_DIV_1
#define	EMU_CFG7_CLK_40_5		EMU_CFG7_DIV_1_5
#define	EMU_CFG7_CLK_54_0		EMU_CFG7_DIV_2
#define	EMU_CFG7_CLK_67_5		EMU_CFG7_DIV_2_5
#define	EMU_CFG7_CLK_81_0		EMU_CFG7_DIV_3
#define	EMU_CFG7_CLK_94_5		EMU_CFG7_DIV_3_5
#define	EMU_CFG7_CLK_108_0		EMU_CFG7_DIV_4
#define	EMU_CFG7_CLK_121_5		EMU_CFG7_DIV_4_5
#define	EMU_CFG7_CLK_135_0		EMU_CFG7_DIV_5
#define	EMU_CFG7_CLK_148_5		EMU_CFG7_DIV_5_5
#define	EMU_CFG7_CLK_162_0		EMU_CFG7_DIV_6
#define	EMU_CFG7_CLK_175_5		EMU_CFG7_DIV_6_5
#define	EMU_CFG7_CLK_189_0		EMU_CFG7_DIV_7
#define	EMU_CFG7_CLK_202_5		EMU_CFG7_DIV_7_5
#define	EMU_CFG7_CLK_216_0		EMU_CFG7_DIV_8
#define	EMU_CFG7_CLK_229_5		EMU_CFG7_DIV_8_5

void
setup_emu(void)
{
//  regs0->emu_cfg[7] = EMU_CFG7_CLK_94_5;
//	regs0->emu_cfg[7] = EMU_CFG7_CLK_108_0;
#ifdef DTH_CFG_ENABLE
	regs0->emu_cfg[7] = EMU_CFG7_CLK_121_5;
#else
    regs0->emu_cfg[7] = EMU_CFG7_CLK_108_0;
#endif
	regs0->emu_cfg[9] = 0x1;			// reset slowmotion
}


void
setup_slowmotion(int fmt, int nint)
{
#ifdef	USE_711
	if (nint)
	{
		regs0->emu_cfg[0]	= 0x0;
		
		if(regs0->emu_cfg[1]&0x100)		
		   regs0->emu_cfg[1] = 0x3301;
		else
		   regs0->emu_cfg[1] = 0x3201;
		   
		regs0->emu_cfg[8]	= 0x20;
	}
	else
	{
		regs0->emu_cfg[0]	= 0x41;
		if(regs0->emu_cfg[1]&0x100)		
		   regs0->emu_cfg[1]	= 0x110;
		else
		      regs0->emu_cfg[1]	= 0x010;
		      
		regs0->emu_cfg[8]	= 0x00;
	}
#else
	if (nint)
	{
		regs0->emu_cfg[0] = 0x0;
		if(regs0->emu_cfg[1]&0x100)		
		   regs0->emu_cfg[1] = 0x3301;
		else
		   regs0->emu_cfg[1] = 0x3201;
		   
		if (fmt)
		{
			// 576p
//			regs0->emu_cfg[8] = 0x2c;		//real time replay
			regs0->emu_cfg[8] = 0x24;		// slow motion replay
		}
		else
		{
			// 480p
//			regs0->emu_cfg[8] = 0x28;		// real time replay
			regs0->emu_cfg[8] = 0x20;		// slow motion replay
		}
	}
	else
	{
		regs0->emu_cfg[0]		= 0x1;
		if(regs0->emu_cfg[1]&0x100)		
		   regs0->emu_cfg[1] = 0x0310;
		else
		   regs0->emu_cfg[1] = 0x0210;
		   
		if (fmt)
		{
			//regs0->emu_cfg[8]		= 0x02c;       // real time replay
			regs0->emu_cfg[8]		= 0x024;       // slow motion play
		}
		else
		{
			//regs0->emu_cfg[8] 	   = 0x028;       // real time replay
			regs0->emu_cfg[8] 	   = 0x020;       // slow motion replay
		}
	}
#endif    
}
#else
void setup_slowmotion(int fmt, int nint) 
{   //wanghaoying 2003-8-12 19:11 modified
    if(fmt)
    {
    }
    if(nint)
    {
    }
}
void setup_emu(void) {}
#endif

