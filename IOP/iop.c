/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/
/*--------------------------------------------------------------------------
|  File Name   : iop.c
|
|  Description : This file main contains three parts.
|                1. Include 8200 and 8202 iop normal play inc.
|                2. Include iop normal and standby reset function.
|                3. Include I2C(24C02) read and write function.
|
|  Version    :  0.1  
| 
| 
|  Rev  Date            Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|       2004/12/20        Lijd           Updating
|--------------------------------------------------------------------------------*/
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "dma.h"
#include "gpio.h"
#include "iop.h"
#include "iophw.h"
#include "user_init.h"
#include "ircode.h"
#include "stdlib.h"

#include "lbc.h"

#if defined(SUPPORT_CARD_STORAGE) && defined(CARD_HOT_PLUG)
#include "cardfs.h"
#endif

#ifdef SUPPORT_RDS_FUNCTION//xyy 2003-12-4 16:05
#include "radio_rds.h"
#endif

#ifndef DVDRELEASE
//#define IOP_DEBUG_INFO        1
#endif

#ifdef  IOP_DEBUG_INFO
#include "sio.h"
#include "emuio.h"
#endif

#if defined(DVI_I2C_SET)&&defined(SPHE8202)//Modifed by ChenZhao on 2004-9-21 15:59  
//#define K_loopMax 100//move to c_i2c.h.chenzhao20050620
#include "c_i2c.h"//chenzhao20050620
#endif//defined(DVI_I2C_SET)&&defined(SPHE8202)

#define IOP_RDY_WAIT        4000000
/*
  lijd 2005-3-18 9:43
  In order to make clear that we include the iop code.
  I make several folder for include 8200/8202/8202s/other,
  and every folder include normal and reset folder.
  Please try it. if it has any questions ,please contact me.
*/
#if defined(IC_8202L) //terry,2006/4/7 05:13¤U¤È
      #include ".\\IOP_8202L\iop_8202L_normal_inc.c"
      #include "iop_8202L.c"
#elif defined(IC_8203A)
      #include ".\\IOP_8202L\iop_8202L_normal_inc.c"
      #include "iop_8203A.c"
#elif defined(SPHE8202)    
    #if defined(IC_8202D)
      #include ".\\IOP_8202D\iop_8202D_normal_inc.c" 
      #include "iop_8202.c"    
    #else
      #include ".\\IOP_8202\iop_8202_normal_inc.c"
      #include "iop_8202.c"
    #endif
#else //SPHE8200
	#include ".\\IOP_8200\iop_8200_normal_inc.c"
	#include "iop_8202.c"
#endif


