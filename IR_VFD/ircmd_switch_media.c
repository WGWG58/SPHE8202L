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
/*-------------------------------------------------------------------------
|  File Name   : ircmd_switch_media.c
|
|  Description : This file was created for switching media.
| 
|  Rev	Date	        Author(s)                       Status & Comments
|--------------------------------------------------------------------------
|  0.1	2006/6/13       WangWei                         Creating
|-------------------------------------------------------------------------*/


#ifdef DIRECT_ACCESS_MEDIA

/****************************************************************************************\
**                                     Includes                                         **
\****************************************************************************************/
#include "atapi_if.h"
#include "func.h"
#include "cardfs.h"
#include "ircmd_switch_media.h"


/****************************************************************************************\
**                                    Constants                                         **
\****************************************************************************************/
const BYTE* bMediaStr[] = 
{
    #ifndef NO_DVD_SERVO
    "DISC",
    #endif//NO_DVD_SERVO
    
    #ifdef SPHE8202_CARD_STORAGE
    "CARD",
    #endif//SPHE8202_CARD_STORAGE
    
    #ifdef SUPPORT_USB
    "USB",
    #endif//SUPPORT_USB
};

/****************************************************************************************\
**                                    Functions                                         **
\****************************************************************************************/

/****************************************************************************************\
**  Function Name : is_card_media_exists                                                **
**  Purposes      : Check if card is pluged in the socket.                              **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : card is in : ture / card is out : false                             **
**  See also      :                                                                     **
\****************************************************************************************/
#if 1//wangw open it.20061013
UINT32 is_card_media_exists( void )
{
    Detect_Card_Storage();
    
    if( (detect_type & MS_CARD_DEVICE)
    ||(detect_type & SD_CARD_DEVICE)
    #ifdef CARD_SETUP_TYPE_3// All in 1
    ||(detect_type & CF_CARD_DEVICE)
    ||(detect_type & SMC_CARD_DEVICE)
    #endif//CARD_SETUP_TYPE_3
    )
    {
        return TRUE;
    }
    else
    {
        return FALSE;    
    }
}
#endif


/****************************************************************************************\
**  Function Name : is_usb_media_exists                                                 **
**  Purposes      : Check if USB device is pluged in host.                              **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : USB device is in : ture / USB device is out : false                 **
**  See also      :                                                                     **
\****************************************************************************************/
#if 1//wangw open it.20061013
UINT32 is_usb_media_exists( void )
{
    uhci_slaveDetect();
    
    if( detect_type & USB_DEVICE )
        return TRUE;
    else
        return FALSE;    
}
#endif


/****************************************************************************************\
**  Function Name : switch_2_des_media                                                  **
**  Purposes      : Switch to destination.                                              **
**  Limitations   : (none)                                                              **
**  Arguments     : uiDestination : DES_USB / DES_CARD / DES_DISC                       **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void switch_2_des_media(UINT32 uiDestination)
{
    //interrupt AV
    AVD_SetMediaTimeout();
    //stop loader
    atapi_p_start_stop_unit( Immed_1, START_STOP_DO_STOP );
    //init variable, treat it as open tray
    InitVar();

    switch( uiDestination )
    {
        #ifdef SPHE8202_CARD_STORAGE
        case DES_CARD://switch to CARD

            GPIO_O_SET( CARD_POWER_RESET, 0 );//card power on, lighting the CARD LED.
            media_status = STATUS_CARD;
            
            #ifdef SUPPORT_USB
            SLAVE_ENUMERATED = FALSE;
            #endif//SUPPORT_USB
            
            detect_type = 0;
    
            if( atapi_p_mechanism_status() == ATAPI_DOOR_OPEN )
                ircmd_trayin();
            else
                atapi_p_start_stop_unit( Immed_1,START_STOP_DO_STOP );
        
            break;
        #endif//SPHE8202_CARD_STORAGE
    
        #ifdef SUPPORT_USB
        case DES_USB://switch to USB device
        
            #ifdef SPHE8202_CARD_STORAGE
            GPIO_O_SET( CARD_POWER_RESET, 1 );//CARD power off.
            #endif//SPHE8202_CARD_STORAGE
    
            media_status = STATUS_USB;
            SLAVE_ENUMERATED = FALSE;
            detect_type = 0;
    
            if( atapi_p_mechanism_status() == ATAPI_DOOR_OPEN )
                ircmd_trayin();
            else
                atapi_p_start_stop_unit( Immed_1, START_STOP_DO_STOP );
            
            break;
        #endif//SUPPORT_USB
        
        #ifndef NO_DVD_SERVO
        case DES_DISC://switch to DISC
        
            #ifdef SPHE8202_CARD_STORAGE
            GPIO_O_SET( CARD_POWER_RESET, 1 );//CARD power off.
            #endif
            media_status = STATUS_DISC;
            no_disk_cnt = DETECT_TIMES;
            system_state = SYSTEM_OPEN;
            media_type = MEDIA_CD;
            adv_search_time = 0;
            atapi_open_tray();
            atapi_close_tray(0);
            detect_type = 0;
            storage_type = 0;
            
            break;
        #endif//NO_DVD_SERVO
        
        default:
            break;
    }

    ircmd_post_func( CMD_FUNC | CMD_FUNC_OPEN );
    system_state = SYSTEM_OPEN;
    play_state = VCD_STATE_CLOSE;
    ClearOsdMsg(0);
    full_scrn = 0;
    t_disp = 0;
    osd0_state = OSD0_STATE_INIT;
    osd_init();
}


/****************************************************************************************\
**  Function Name : osd_print_storage_detect_info                                       **
**  Purposes      : Print switch media debug message.                                   **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void osd_print_storage_detect_info( void )
{
    psprintf( RegionValStr[REGION2], "DET-%x STO-%x MED-%x MES-%x SYS-%x PS-%x",detect_type, storage_type, media_type, media_status, system_state, play_state );
    PrintOsdMsg( STR_OS_SPACE, REGION2, 1, 1 );
}


/****************************************************************************************\
**  Function Name : card_test_ready                                                     **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
#ifdef SPHE8202_CARD_STORAGE
void card_test_ready( void )
{
    UINT8 media_exist = 0;

    if( storage_type != 0 )
    {
        if( storage_type != USB_DEVICE )
            Card_power_reset();

        switch( storage_type )
        {
            #if defined(COMPACT_FLASH)
            case CF_CARD_DEVICE:

                #ifdef CARD_SETUP_TYPE_2
                regs0->fm_gpio_mode = 8;
                #elif defined(CARD_SETUP_TYPE_3)||defined(CARD_SETUP_TYPE_5)
                regs0->gpio_mode_B = 2;
                regs0->fm_gpio_mode = 3;
                #endif

                cfIdeDetect();
                media_exist = 1;
                break;
            #endif

            #if defined(SD_MMC_CARD)
            case SD_CARD_DEVICE:

                #ifdef CARD_SETUP_TYPE_2
                regs0->fm_gpio_mode = 3;
                #elif defined(CARD_SETUP_TYPE_3)||defined(CARD_SETUP_TYPE_4)
                regs0->gpio_mode_B=0;
                regs0->fm_gpio_mode = 3;
                #endif

                if( sdDetect() )
                {
                    psprintf( RegionValStr[REGION1], "SD Err" );
                    PrintOsdMsg( STR_OS_SPACE, REGION1, 0, 1 );
                }
                else
                    media_exist = 1;
                break;
            #endif

            #if defined(MEMORY_STICK)
            case MS_CARD_DEVICE:

                #ifdef CARD_SETUP_TYPE_2
                regs0->fm_gpio_mode = 4;
                #elif defined(CARD_SETUP_TYPE_3)||defined(CARD_SETUP_TYPE_4)
                regs0->gpio_mode_B = 0;
                regs0->fm_gpio_mode = 4;
                #endif

                msDetect();
                media_exist = 1;
                break;
            #endif

            #if defined(SMART_MEDIA)
            case SMC_CARD_DEVICE:
                #ifdef CARD_SETUP_TYPE_2
                regs0->fm_gpio_mode = 8;
                #elif defined(CARD_SETUP_TYPE_3)
                regs0->fm_gpio_mode = 3;
                regs0->gpio_mode_B = 1;
                #endif

                if( smcDetect() )
                {
                    psprintf( RegionValStr[REGION1], "SMC Err" );
                    PrintOsdMsg( STR_OS_SPACE, REGION1, 0, 1 );
                }
                else
                    media_exist = 1;
                break;
            #endif

            default:
                break;
        }
    }

    if( media_exist )
    {
        CardSetBrowse();
    }
}
#endif//SPHE8202_CARD_STORAGE


/****************************************************************************************\
**  Function Name : usb_test_ready                                                      **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
#ifdef SUPPORT_USB
void usb_test_ready( void )
{
    if( storage_type != USB_DEVICE )
        return;

    if( UsbTestReady() )
    {
        CardSetBrowse();
    }
}
#endif//SUPPORT_USB


/****************************************************************************************\
**  Function Name : switch_media_up                                                     **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void switch_media_up( void )
{
    last_hl_item = hl_item;
    
    if( hl_item > 0 )
        hl_item--;
    else
        hl_item = SWGUI_MAX_ITEM - 1;

    switch_media_show_HL();
}


/****************************************************************************************\
**  Function Name : switch_media_down                                                   **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void switch_media_down( void )
{
    last_hl_item = hl_item;
    
    if( hl_item < (SWGUI_MAX_ITEM - 1) )
        hl_item++;
    else
        hl_item = 0;
    
    switch_media_show_HL();
}


/****************************************************************************************\
**  Function Name : switch_media_select                                                 **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void switch_media_select( void )
{
    exit_switch_media_gui();

    switch( hl_item )//media_status == hl_item
    {
        #ifndef NO_DVD_SERVO
        case STATUS_DISC:
            ircmd_key_disc();
            break;
        #endif//NO_DVD_SERVO
        
        #ifdef SPHE8202_CARD_STORAGE
        case STATUS_CARD:
            ircmd_key_card();
            break;
        #endif//SPHE8202_CARD_STORAGE
        
        #ifdef SUPPORT_USB
        case STATUS_USB:
            ircmd_key_usb();
            break;
        #endif//SUPPORT_USB
        
        default:
            break;
    }
}


/****************************************************************************************\
**  Function Name : switch_media_show_HL                                                **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void switch_media_show_HL( void )
{
    coordinate string;

    //clear last hl
    string.x = 10 + 56; 
    string.y = 10 + last_hl_item*50 + 8;
    osd_draw_region_rect( 10, 10 + last_hl_item*50, 180, 40, SWGUI_MAIN_BG_COLOR, SWITCH_GUI_REGION );
    osd_draw_string( &string, bMediaStr[last_hl_item], SWGUI_FONT_COLOR, SWGUI_MAIN_BG_COLOR, SWITCH_GUI_REGION, 0 );

    //mark current playing media item
    string.x = 10 + 56; 
    string.y = 10 + media_status*50 + 8;
    osd_draw_region_rect( 10, 10 + media_status*50, 180, 40, SWGUI_MARK_BG_COLOR, SWITCH_GUI_REGION );
    osd_draw_string( &string, bMediaStr[media_status], SWGUI_FONT_COLOR, SWGUI_MARK_BG_COLOR, SWITCH_GUI_REGION, 0 );

    //show current hl
    string.x = 10 + 56; 
    string.y = 10 + hl_item*50 + 8;
    osd_draw_region_rect( 10, 10 + hl_item*50, 180, 40, SWGUI_HL_BG_COLOR, SWITCH_GUI_REGION );
    osd_draw_string( &string, bMediaStr[hl_item], SWGUI_HL_FONT_COLOR, SWGUI_HL_BG_COLOR, SWITCH_GUI_REGION, 0 );
}


/****************************************************************************************\
**  Function Name : draw_switch_gui_background                                          **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void draw_switch_gui_background( void )
{
    coordinate string;
    int i = 0;
    
    //draw main background
    osd_fill_region( SWITCH_GUI_REGION, 15 );//clear background color
    osd_draw_region_rect( 0, 0, 200, SWGUI_MAX_ITEM*40 + (SWGUI_MAX_ITEM + 1)*10, SWGUI_MAIN_BG_COLOR, SWITCH_GUI_REGION );

    //draw items
    for( i=0;i<SWGUI_MAX_ITEM;i++ )
    {
        string.x = 10 + 56; 
        string.y = i*40 + (i + 1)*10 + 8;
        osd_draw_string( &string, bMediaStr[i], SWGUI_FONT_COLOR, SWGUI_MAIN_BG_COLOR, SWITCH_GUI_REGION, 0 );
    }

    osd_tog_region( SWITCH_GUI_REGION, OSD_ON );
}


/****************************************************************************************\
**  Function Name : ircmd_source                                                        **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void ircmd_source( void )
{
    if( full_scrn & SW_MEDIA )
    {
        exit_switch_media_gui();
    }
    else
    {
        full_scrn = SW_MEDIA;
        t_disp = 0;
        osd0_state = OSD0_STATE_INIT;
        ClearOsdMsg(0);
        osd_init_media_switch_gui();
        draw_switch_gui_background();
        osd_tog_region( SWITCH_GUI_REGION, OSD_ON );

        hl_item = media_status;
        switch_media_show_HL();

        SetFullscrnCmdFuncPtr( switch_media_up, switch_media_down, invalid_key, invalid_key, switch_media_select);
    }
}


/****************************************************************************************\
**  Function Name : exit_switch_media_gui                                               **
**  Purposes      :                                                                     **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
void exit_switch_media_gui( void )
{
    full_scrn &= ( ~SW_MEDIA );
    osd_tog_region( SWITCH_GUI_REGION, OSD_OFF );
    osd_init();

    #ifdef SUPPORT_MP4_SUBTITLE
    if( IS_EXT_SUP_ACTIVATED() )
        osd_init_OSDSRT();
    #endif//SUPPORT_MP4_SUBTITLE
}


/****************************************************************************************\
**  Function Name : ircmd_key_disc                                                      **
**  Purposes      : Switch to play disc.                                                **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
#ifndef NO_DVD_SERVO
void ircmd_key_disc( void )
{
    printf("\n======================> TO DISC <======================\n");

    if( media_status == STATUS_DISC )
    {
        psprintf( RegionValStr[REGION1], "[DISC MODE]" );
        PrintOsdMsg( STR_OS_SPACE, REGION1, 1, 1 );
        return;
    }

    switch_2_des_media( DES_DISC );
}
#endif//NO_DVD_SERVO


/****************************************************************************************\
**  Function Name : ircmd_key_usb                                                       **
**  Purposes      : Switch to play USB device.                                          **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
#ifdef SUPPORT_USB
void ircmd_key_usb( void )
{
    printf("\n======================> TO USB <======================\n");

    if( media_status == STATUS_USB )
    {
        psprintf( RegionValStr[REGION1], "[USB MODE]" );
        PrintOsdMsg( STR_OS_SPACE, REGION1, 1, 1 );
        return;
    }

    switch_2_des_media( DES_USB );
}
#endif//SUPPORT_USB


/****************************************************************************************\
**  Function Name : ircmd_key_card                                                      **
**  Purposes      : Switch to play CARD device.                                         **
**  Limitations   : (none)                                                              **
**  Arguments     : (none)                                                              **
**  Returns       : (none)                                                              **
**  See also      :                                                                     **
\****************************************************************************************/
#ifdef SPHE8202_CARD_STORAGE
void ircmd_key_card( void )
{
    printf("\n======================> TO CARD <======================\n");

    if( media_status == STATUS_CARD )
    {
        psprintf( RegionValStr[REGION1], "[CARD MODE]" );
        PrintOsdMsg( STR_OS_SPACE, REGION1, 1, 1 );
        return;
    }

    switch_2_des_media( DES_CARD );
}
#endif//SPHE8202_CARD_STORAGE


#endif//DIRECT_ACCESS_MEDIA




