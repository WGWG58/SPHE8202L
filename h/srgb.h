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
|  File Name   :  srgb.h
|
|  Description :  8202 Serial RGB interface
|
|  Version    :  0.1  
| 
| 
|  Rev  Date            Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1  2005/1/5        wthsin         Creating
|--------------------------------------------------------------------------------*/
#include "config.h"
#include "regmap.h"
 
#ifdef SERIAL_RGB     

#define  SRGB_OFF            0 
#define  SRGB_ON             1 

#define SRGB_UPS051         0
#define SRGB_UPS052         1

#define SRGB_NTSC           0
#define SRGB_PAL            1

#define SRGB_HMODE_280      0
#define SRGB_HMODE_480      1
#define SRGB_HMODE_528      2
#define SRGB_HMODE_960      3
#define SRGB_HMODE_1152     4
#define SRGB_HMODE_1440     5

/* Serial RGB Mode Control Register 0 */
#define SRGB_CONFIG_MASK_BIT                            0x01FE  /* bit-mask for F_S,HV_NEG,CP,VBEN,VAEN,UHEN,MODE */
#define SRGB_SWITCH_MASK_BIT                            0x0001  /* bit-mask for SW */
#define SRGB_ENCODE_EVEN_LINE_FROM_SECOND_PIXEL_BIT     (0 << 7)
#define SRGB_ENCODE_ODD_LINE_FROM_SECOND_PIXEL_BIT      (1 << 7)
#define SRGB_ENCODE_ALL_LINE_FROM_FIRST_PIXEL_BIT       (2 << 7)
#define SRGB_HV_NEGATIVE_PULSE_BIT                      (0 << 6)
#define SRGB_HV_POSTIVE_PULSE_BIT                       (1 << 6)
#define SRGB_DCLK_INVERSE_BIT                           (0 << 5)
#define SRGB_DCLK_INPHASE_BIT                           (1 << 5)
#define SRGB_DCLK_IS_NORMAL_IN_BLANKING_BIT             (0 << 4)
#define SRGB_DCLK_EQUAL_VCLK_IN_BLANKING_BIT            (1 << 4)
#define SRGB_DCLK_IS_NORMAL_IN_ACTIVE_BIT               (0 << 3)
#define SRGB_DCLK_EQUAL_VCLK_IN_ACTIVE_BIT              (1 << 3)
#define SRGB_USER_DEFINE_HACTIVE_REGION_DISABLE_BIT     (0 << 2)
#define SRGB_USER_DEFINE_HACTIVE_REGION_ENABLE_BIT      (1 << 2)
#define SRGB_UPS051_MODE_BIT                            (0 << 1)
#define SRGB_UPS052_MODE_BIT                            (1 << 1)
#define SRGB_SWITCH_OFF_BIT                             (0 << 0)
#define SRGB_SWITCH_ON_BIT                              (1 << 0)

/* Serial RGB Mode Control Register 1 */
#define SRGB_RGB_PERIOD_MASK_BIT        0x000F  /* bit-mask for RGB_PERIOD_1 */
#define SRGB_ORDER_MASK_BIT             0x03F0  /* bit-mask for ORDER_EVEN,ORDER_ODD */
#define SRGB_ORDER_RGB                  0
#define SRGB_ORDER_RBG                  1
#define SRGB_ORDER_GBR                  2
#define SRGB_ORDER_GRB                  3
#define SRGB_ORDER_BRG                  4
#define SRGB_ORDER_BGR                  5


extern void SRGB_Config_Parameter(UINT16 parameters);
extern void SRGB_Output_Switch(UINT8 SRGB_SWITCH);
extern void SRGB_Set_RGB_Order(UINT16 order_odd, UINT16 order_even);
extern void SRGB_Config_Display(UINT8 LCD_TCON_MODE, UINT16 SRGB_H_MODE);
extern void SRGB_Config_HV(UINT8 PAL_NTSC, UINT8 LCD_TCON_MODE, UINT16 SRGB_H_MODE, UINT16 SRGB_V_RES);
extern void SRGB_Setup(UINT8 SRGB_SWITCH, UINT8 PAL_NTSC, UINT8 LCD_TCON_MODE, UINT16 SRGB_H_MODE, UINT16 SRGB_V_RES, UINT16 parameters);
 
#endif    //#ifdef SERIAL_RGB 
