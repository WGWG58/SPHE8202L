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
|  File Name   :  srgb.c
|
|  Description :  8202 Serial RGB interface
|
|  Version     :  0.1  
| 
| 
|  Rev  Date            Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1  2005/1/5        wthsin         Creating
|--------------------------------------------------------------------------------*/
#include "config.h"
#include "global.h"
#include "macro.h"
#include "regmap.h"
#include "emuio.h"
 

#ifdef SERIAL_RGB       

#ifndef DVDRELEASE
 #define SERIAL_RGB_DBG       1
#endif

#define D   printf("INFO: __%d__(%s:%s)\n",__LINE__,__FILE__,__FUNCTION__);

#ifndef SERIAL_RGB_DBG
 #undef printf
 #undef print_block
 #define printf(f, a...) do {} while (0)
 #define print_block(x,y) do {} while (0)
#endif

    
/**************************************************************************
 *                                                                        *
 *  Function Name: SRGB_Config_Parameter                                  *
 *                                                                        *
 *  Purposes:                                                             *
 *      Configure SRGB parameters (TV2_SRGB_MODE[0])                      *
 *  Descriptions:                                                         *
 *      Configure SRGB parameters (TV2_SRGB_MODE[0])                      *
 *  Arguments:                                                            *
 *      parameters: (may select several and OR them together)             *
 *                 SRGB_ENCODE_EVEN_LINE_FROM_SECOND_PIXEL_BIT            *
 *                 SRGB_ENCODE_ODD_LINE_FROM_SECOND_PIXEL_BIT             *
 *                 SRGB_ENCODE_ALL_LINE_FROM_FIRST_PIXEL_BIT              *
 *                 SRGB_HV_NEGATIVE_PULSE_BIT                             *
 *                 SRGB_HV_POSTIVE_PULSE_BIT                              *
 *                 SRGB_DCLK_INVERSE_BIT                                  *
 *                 SRGB_DCLK_INPHASE_BIT                                  *
 *                 SRGB_DCLK_IS_NORMAL_IN_BLANKING_BIT                    *
 *                 SRGB_DCLK_EQUAL_VCLK_IN_BLANKING_BIT                   *
 *                 SRGB_DCLK_IS_NORMAL_IN_ACTIVE_BIT                      *
 *                 SRGB_DCLK_EQUAL_VCLK_IN_ACTIVE_BIT                     *
 *                 SRGB_USER_DEFINE_HACTIVE_REGION_DISABLE_BIT            *
 *                 SRGB_USER_DEFINE_HACTIVE_REGION_ENABLE_BIT             *
 *                 SRGB_UPS051_MODE_BIT                                   *
 *                 SRGB_UPS052_MODE_BIT                                   *
 *                 SRGB_SWITCH_OFF_BIT                                    *
 *                 SRGB_SWITCH_ON_BIT                                     *
 *  Returns:                                                              *
 *      None                                                              *
 *  See also:                                                             *
 *      None                                                              *
 **************************************************************************/
void SRGB_Config_Parameter(UINT16 parameters)
{
    regs0->tv2_srgb_mode0 = (regs0->tv2_srgb_mode0 & ~SRGB_CONFIG_MASK_BIT) | (parameters & SRGB_CONFIG_MASK_BIT);
}

/**************************************************************************
 *                                                                        *
 *  Function Name: SRGB_Output_Switch                                     *
 *                                                                        *
 *  Purposes:                                                             *
 *      Enable/Disable SRGB output                                        *
 *  Descriptions:                                                         *
 *      Enable/Disable SRGB output                                        *
 *  Arguments:                                                            *
 *      SRGB_SWITCH:                                                      *
 *                 SRGB_OFF            0                                  *
 *                 SRGB_ON             1                                  *
 *  Returns:                                                              *
 *      None                                                              *
 *  See also:                                                             *
 *      None                                                              *
 **************************************************************************/
void SRGB_Output_Switch(UINT8 SRGB_SWITCH)
{
    UINT16 on_off;

    if (SRGB_SWITCH)
        on_off = SRGB_SWITCH_ON_BIT;
    else
        on_off = SRGB_SWITCH_OFF_BIT;

    regs0->tv2_srgb_mode0 = (regs0->tv2_srgb_mode0 & ~SRGB_SWITCH_MASK_BIT) | on_off;
}

/**************************************************************************
 *                                                                        *
 *  Function Name: SRGB_Set_RGB_Order                                     *
 *                                                                        *
 *  Purposes:                                                             *
 *      setup RGB order for even/odd lines (TV2_SRGB_MODE[1])             *
 *  Descriptions:                                                         *
 *      setup RGB order for even/odd lines (TV2_SRGB_MODE[1])             *
 *  Arguments:                                                            *
 *      order_odd, order_even:                                            *
 *                 SRGB_ORDER_RGB      0                                  *
 *                 SRGB_ORDER_RBG      1                                  *
 *                 SRGB_ORDER_GBR      2                                  *
 *                 SRGB_ORDER_GRB      3                                  *
 *                 SRGB_ORDER_BRG      4                                  *
 *                 SRGB_ORDER_BGR      5                                  *
 *  Returns:                                                              *
 *      None                                                              *
 *  See also:                                                             *
 *      None                                                              *
 **************************************************************************/
void SRGB_Set_RGB_Order(UINT16 order_odd, UINT16 order_even)
{
    UINT16 rgb_order;
    rgb_order = ((order_even & 0x07) << 7) | ((order_odd & 0x07) << 4);
    regs0->tv2_srgb_mode1 = (regs0->tv2_srgb_mode1 & ~SRGB_ORDER_MASK_BIT) | rgb_order;
}

/**************************************************************************
 *                                                                        *
 *  Function Name: SRGB_Config_Display                                    *
 *                                                                        *
 *  Purposes:                                                             *
 *      Configure SRGB output RGB order and timing (TV2_SRGB_MODE[2:1])   *
 *  Descriptions:                                                         *
 *      Configure SRGB output RGB order and timing (TV2_SRGB_MODE[2:1])   *
 *  Arguments:                                                            *
 *      LCD_TCON_MODE:                                                    *
 *                 SRGB_UPS051         0                                  *
 *                 SRGB_UPS052         1                                  *
 *      SRGB_H_MODE:                                                         *
 *                 SRGB_HMODE_280      0                                  *
 *                 SRGB_HMODE_480      1                                  *
 *                 SRGB_HMODE_528      2                                  *
 *                 SRGB_HMODE_960      3                                  *
 *                 SRGB_HMODE_1152     4                                  *
 *                 SRGB_HMODE_1440     5                                  *
 *  Returns:                                                              *
 *      None                                                              *
 *  See also:                                                             *
 *      None                                                              *
 **************************************************************************/
void SRGB_Config_Display(UINT8 LCD_TCON_MODE, UINT16 SRGB_H_MODE)
{
    UINT16 rgb_period = 0;
    UINT16 sample_seq = 0;
    UINT16 order_odd = 0;
    UINT16 order_even = 0;

    if (LCD_TCON_MODE == SRGB_UPS051)
    {
        switch (SRGB_H_MODE)
        {
            case SRGB_HMODE_280:
                rgb_period = 4;
                sample_seq = 0x01;
                order_odd = SRGB_ORDER_RGB;
                order_even = SRGB_ORDER_GBR;
                break;
            case SRGB_HMODE_480:
                rgb_period = 2;
                sample_seq = 0x01;
                order_odd = SRGB_ORDER_RGB;
                order_even = SRGB_ORDER_GBR;
                break;
            case SRGB_HMODE_528:
                rgb_period = 7;
                sample_seq = 0x49;
                order_odd = SRGB_ORDER_RGB;
                order_even = SRGB_ORDER_GBR;
                break;
            case SRGB_HMODE_960:
                rgb_period = 2;
                sample_seq = 0x05;
                order_odd = SRGB_ORDER_RGB;
                order_even = SRGB_ORDER_RGB;
                break;
            case SRGB_HMODE_1152:
                rgb_period = 4;
                sample_seq = 0x0F;
                order_odd = SRGB_ORDER_RGB;
                order_even = SRGB_ORDER_RGB;
                break;
            case SRGB_HMODE_1440:
                rgb_period = 14;
                sample_seq = 0x7FFF;
                order_odd = SRGB_ORDER_RGB;
                order_even = SRGB_ORDER_RGB;
                break;
        }
    }
    else //SRGB_UPS052
    {
        switch (SRGB_H_MODE)
        {
            case SRGB_HMODE_280: //require 280 * 4 = 1120 dots
                //Joy: generate 1440 * 6/7 = 1234 dots (outnumbered samples to work around bug?)
                rgb_period = 6;
                sample_seq = 0x03F; // xRGBDRG
                order_odd = SRGB_ORDER_RGB;
                order_even = SRGB_ORDER_RGB;
                break;
            case SRGB_HMODE_528:
                rgb_period = 7; //Joy: to be confirmed
                sample_seq = 0x49;
                order_odd = SRGB_ORDER_RGB;
                order_even = SRGB_ORDER_RGB;
                break;
        }
    }

    /* Update RGB Order */
    SRGB_Set_RGB_Order(order_odd, order_even);
    /* Update RGB Period */
    regs0->tv2_srgb_mode1 = (regs0->tv2_srgb_mode1 & ~SRGB_RGB_PERIOD_MASK_BIT) | (rgb_period & rgb_period);
    /* Update Sample Sequence */
    regs0->tv2_srgb_mode2 = sample_seq;
}

/**************************************************************************
 *                                                                        *
 *  Function Name: SRGB_Config_HV                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *      Configure H/Vsync edges and active line regions (PC[9:0])         *
 *  Descriptions:                                                         *
 *      Configure H/Vsync edges and active line regions (PC[9:0])         *
 *  Arguments:                                                            *
 *      PAL_NTSC:                                                         *
 *                 SRGB_NTSC           0                                  *
 *                 SRGB_PAL            1                                  *
 *      LCD_TCON_MODE:                                                    *
 *                 SRGB_UPS051         0                                  *
 *                 SRGB_UPS052         1                                  *
 *      SRGB_H_MODE:                                                      *
 *                 SRGB_HMODE_280      0                                  *
 *                 SRGB_HMODE_480      1                                  *
 *                 SRGB_HMODE_528      2                                  *
 *                 SRGB_HMODE_960      3                                  *
 *                 SRGB_HMODE_1152     4                                  *
 *                 SRGB_HMODE_1440     5                                  *
 *      SRGB_V_RES:                                                       *
 *                 220, 234, 236, 240, ..., etc                           *
 *  Returns:                                                              *
 *      None                                                              *
 *  See also:                                                             *
 *      None                                                              *
 **************************************************************************/
void SRGB_Config_HV(UINT8 PAL_NTSC, UINT8 LCD_TCON_MODE, UINT16 SRGB_H_MODE, UINT16 SRGB_V_RES)
{
    UINT16 Display_Period;
    UINT16 Total_H_Period;
    UINT16 Total_V_Period;
    UINT16 Half_V_Period;
    UINT16 Vertical_Display_Position;
    UINT16 Vsync_Pulse_Width = 3; //TVp
    UINT16 Hsync_Pulse_Width;
    UINT16 SRGB_H_EDGE1_PNT;
    UINT16 SRGB_H_EDGE2_PNT;
    UINT16 SRGB_V_EDGE1_LT;
    UINT16 SRGB_V_EDGE2_LT;
    UINT16 SRGB_V_EDGE1_LB;
    UINT16 SRGB_V_EDGE2_LB;
    UINT16 SRGB_V_START_LT;
    UINT16 SRGB_V_END_LT;
    UINT16 SRGB_V_START_LB;
    UINT16 SRGB_V_END_LB;

    /* Video Source Resolution */
    if (PAL_NTSC)
    {
        Total_H_Period = 1728;
        Total_V_Period = 625;
        Half_V_Period = 313;
    }
    else
    {
        Total_H_Period = 1716;
        Total_V_Period = 525;
        Half_V_Period = 262;
    }

    /* Panel's Vertical Resolution */
    Display_Period = SRGB_V_RES;

    /* H-sync Pulse Width; THp */
    if (LCD_TCON_MODE == SRGB_UPS051)
        Hsync_Pulse_Width = 120; //THp ~= 4.46us for all modes
    else //SRGB_UPS052
    {
        if (SRGB_H_MODE == SRGB_HMODE_280)
            Hsync_Pulse_Width = 28; //THp = 25 * VCLK
        else //SRGB_HMODE_528
            Hsync_Pulse_Width = 53; //THp = 48 * VCLK
    }

    /* Vertical Display Position; TVs */
    switch (SRGB_H_MODE)
    {
        case SRGB_HMODE_280:
        case SRGB_HMODE_528:
            if (PAL_NTSC)
                Vertical_Display_Position = 34; //TVs = 34 for PAL, Mode 280/528
            else
                Vertical_Display_Position = 25; //TVs = 25 for NTSC, Mode 280/528
            break;
        case SRGB_HMODE_480:
        case SRGB_HMODE_960:
        case SRGB_HMODE_1152:
        case SRGB_HMODE_1440:
        default:
            if (PAL_NTSC)
                Vertical_Display_Position = 27; //TVs = 27 for PAL, Mode 480/960/1152/1440
            else
                Vertical_Display_Position = 14; //TVs = 18 for NTSC, Mode 480/960/1152/1440
            break;
    }

    ////////////////////////////////////////

    /* H-sync Start Point */
    if (PAL_NTSC)
        SRGB_H_EDGE1_PNT = 311; //Joy: to be confirmed
    else
    {
        if (LCD_TCON_MODE == SRGB_UPS051)
            SRGB_H_EDGE1_PNT = 1709;
        else //SRGB_UPS052
            //Joy: if generate 1234 dots (outnumbered samples to work around bug?) for Mode_280
            SRGB_H_EDGE1_PNT = 1699;
    }
    /* H-sync End Point */
    SRGB_H_EDGE2_PNT = (SRGB_H_EDGE1_PNT + Hsync_Pulse_Width) % Total_H_Period;

    /* V-sync Start Line for Top Field */
    if (PAL_NTSC)
        SRGB_V_EDGE1_LT = 27; //Joy: to be confirmed
    else
    {
        if (LCD_TCON_MODE == SRGB_UPS051)
            //Joy: set to 6 for 240 lines; set to 16 for 220 lines to centerize frame
            SRGB_V_EDGE1_LT = (6 + (240 - SRGB_V_RES) / 2) % Total_V_Period;
        else //SRGB_UPS052
            //Joy: set to 524 for 240 lines; set to 9 for 220 lines to centerize frame
            SRGB_V_EDGE1_LT = (524 + (240 - SRGB_V_RES) / 2) % Total_V_Period;
    }

    /* V-sync End Line for Top Field */
    SRGB_V_EDGE2_LT = (SRGB_V_EDGE1_LT + Vsync_Pulse_Width) % Total_V_Period;
    /* V-sync Start Line for Bottom Field */
    SRGB_V_EDGE1_LB = (SRGB_V_EDGE1_LT + Half_V_Period) % Total_V_Period;
    /* V-sync End Line for Bottom Field */
    SRGB_V_EDGE2_LB = (SRGB_V_EDGE1_LB + Vsync_Pulse_Width) % Total_V_Period;

    /* Active Start Line for Top Field */
    SRGB_V_START_LT = (SRGB_V_EDGE1_LT + Vertical_Display_Position) % Total_V_Period;
    /* Active End Line for Top Field */
    SRGB_V_END_LT = (SRGB_V_START_LT + Display_Period) % Total_V_Period;
    /* Active Start Line for Bottom Field */
    SRGB_V_START_LB = (SRGB_V_EDGE1_LB + Vertical_Display_Position) % Total_V_Period;
    /* Active End Line for Bottom Field */
    SRGB_V_END_LB = (SRGB_V_START_LB + Display_Period) % Total_V_Period;

    ////////////////////////////////////////

    /* Update Registers */
    regs0->tv_pccon[0] = SRGB_H_EDGE1_PNT;
    regs0->tv_pccon[1] = SRGB_H_EDGE2_PNT;
    regs0->tv_pccon[2] = SRGB_V_START_LT;
    regs0->tv_pccon[3] = SRGB_V_END_LT;
    regs0->tv_pccon[4] = SRGB_V_START_LB;
    regs0->tv_pccon[5] = SRGB_V_END_LB;
    regs0->tv_pccon[6] = SRGB_V_EDGE1_LT;
    regs0->tv_pccon[7] = SRGB_V_EDGE2_LT;
    regs0->tv_pccon[8] = SRGB_V_EDGE1_LB;                           
    regs0->tv_pccon[9] = SRGB_V_EDGE2_LB;   
}

/**************************************************************************
 *                                                                        *
 *  Function Name: SRGB_Setup                                             *
 *                                                                        *
 *  Purposes:                                                             *
 *      Setup SRGB control registers                                      *
 *  Descriptions:                                                         *
 *      Entry function for upper-layer applications                       *
 *  Arguments:                                                            *
 *      SRGB_SWITCH:                                                      *
 *                 SRGB_OFF            0                                  *
 *                 SRGB_ON             1                                  *
 *      PAL_NTSC:                                                         *
 *                 SRGB_NTSC           0                                  *
 *                 SRGB_PAL            1                                  *
 *      LCD_TCON_MODE:                                                    *
 *                 SRGB_UPS051         0                                  *
 *                 SRGB_UPS052         1                                  *
 *      SRGB_H_MODE:                                                      *
 *                 SRGB_HMODE_280      0                                  *
 *                 SRGB_HMODE_480      1                                  *
 *                 SRGB_HMODE_528      2                                  *
 *                 SRGB_HMODE_960      3                                  *
 *                 SRGB_HMODE_1152     4                                  *
 *                 SRGB_HMODE_1440     5                                  *
 *      SRGB_V_RES:                                                       *
 *                 220, 234, 236, 240, ..., etc                           *
 *      parameters: (may select several and OR them together)             *
 *                 SRGB_ENCODE_EVEN_LINE_FROM_SECOND_PIXEL_BIT            *
 *                 SRGB_ENCODE_ODD_LINE_FROM_SECOND_PIXEL_BIT             *
 *                 SRGB_ENCODE_ALL_LINE_FROM_FIRST_PIXEL_BIT              *
 *                 SRGB_HV_NEGATIVE_PULSE_BIT                             *
 *                 SRGB_HV_POSTIVE_PULSE_BIT                              *
 *                 SRGB_DCLK_INVERSE_BIT                                  *
 *                 SRGB_DCLK_INPHASE_BIT                                  *
 *                 SRGB_DCLK_IS_NORMAL_IN_BLANKING_BIT                    *
 *                 SRGB_DCLK_EQUAL_VCLK_IN_BLANKING_BIT                   *
 *                 SRGB_DCLK_IS_NORMAL_IN_ACTIVE_BIT                      *
 *                 SRGB_DCLK_EQUAL_VCLK_IN_ACTIVE_BIT                     *
 *                 SRGB_USER_DEFINE_HACTIVE_REGION_DISABLE_BIT            *
 *                 SRGB_USER_DEFINE_HACTIVE_REGION_ENABLE_BIT             *
 *                 SRGB_UPS051_MODE_BIT                                   *
 *                 SRGB_UPS052_MODE_BIT                                   *
 *                 SRGB_SWITCH_OFF_BIT                                    *
 *                 SRGB_SWITCH_ON_BIT                                     *
 *  Returns:                                                              *
 *      None                                                              *
 *  See also:                                                             *
 *      None                                                              *
 **************************************************************************/
void SRGB_Setup(UINT8 SRGB_SWITCH, UINT8 PAL_NTSC, UINT8 LCD_TCON_MODE, UINT16 SRGB_H_MODE, UINT16 SRGB_V_RES, UINT16 parameters)
{
    /* turn off SRGB */
    SRGB_Output_Switch(SRGB_OFF);

    /* config parameters (TV2_SRGB_MODE[0]) */
    SRGB_Config_Parameter(parameters);
    /* config RGB order and timing (TV2_SRGB_MODE[2:1]) */
    SRGB_Config_Display(LCD_TCON_MODE,SRGB_H_MODE);
    /* config H/Vsync edges and active line regions (PC[9:0]) */
    SRGB_Config_HV(PAL_NTSC,LCD_TCON_MODE,SRGB_H_MODE,SRGB_V_RES);

    /* turn on/off SRGB */
    SRGB_Output_Switch(SRGB_SWITCH);
}

#endif    //#ifdef SERIAL_RGB 
