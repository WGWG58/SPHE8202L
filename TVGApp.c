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
|  File Name   :  TVGApp.c
|
|  Description :  TV Guardian communication interface implementation
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2005/03/23      yltseng         Creating
|  0.2  2005/12/15		linrc 			update cowork with TVG martell...
|--------------------------------------------------------------------------------*/ 
#include "user_init.h"
#include "global.h"

#ifdef SUPPORT_TVG
#include "TVG\TVG.h"
#include "TVG\TVGExtern.h"
#include "TVG\TVGAPI.h"
#include "osd_palette.h"

// **************************************************************************************** //
#ifndef DVDRELEASE
#define TVG_DBG
#endif

#ifdef TVG_DBG
    #define TVG_DBG_FLOW
    #define TVG_DBG_ACTIVATION
#endif

#ifndef TVG_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif

/************************************************************************************
    TVG Activation
************************************************************************************/
    #ifdef SUPPORT_TVG_ACTIVATION

        #if !defined( NEW_OSD_DRIVER ) || !defined( DVD_SETUP_REENG ) || !defined( SUPPORT_WINDOW_PROC ) || !defined( SETUP_EXTENSION_TABLE )
        #error "Must define NEW_OSD_DRIVER && DVD_SETUP_REENG && SUPPORT_WINDOW_PROC && SETUP_EXTENSION_TABLE\n"
        #endif

#include "osd_WndAPI.h"
#include "ircode.h"
#include "memmap_I2C.h"
#include "setup_VA.h"

//linrc move to memmap_I2C.h 2006-2-28 10:18
//#define     TVG_UNIT_ID_ADDR    ( sizeof(UINT32) + sizeof(setup_VA) + 2 + sizeof(t_USER_SET) )
//#define     TVG_SHOWAD_COUNTER_ADDR    ( sizeof(UINT32) + sizeof(setup_VA) + 2 + sizeof(t_USER_SET) +sizeof(UINT16))

extern void TVGInitSystem( UINT8 uiCmd );
// **************************************************************************************** //
static inline UINT32 ReadTVGUnitID( UINT16* pUnitID )
{
#if 0//ndef DVDRELEASE
    if( !pUnitID )
        return FALSE;
#endif

    if( ReadFromI2c( 0xa0, TVG_UNIT_ID_ADDR, (UINT8*) pUnitID, 2 ) )
        return TRUE;

    return FALSE;
}

// **************************************************************************************** //
/*static inline*/ UINT32 WriteTVGUnitID( UINT16 uiUnitID )
{
    return WriteToI2c( 0xa0, TVG_UNIT_ID_ADDR, (UINT8*) &uiUnitID, TVG_UNIT_ID_SIZE );
}

// **************************************************************************************** //
extern void TVGClearUnitID()
{
    WriteTVGUnitID( 0 );
}

// **************************************************************************************** //
static inline UINT8* GetRegistrationKey()
{
    UINT16 uiUnitID;
#if 0//ndef DVDRELEASE
    if( !ReadTVGUnitID( &uiUnitID ) )
        return NULL;
#else
    ReadTVGUnitID( &uiUnitID );
#endif

    ProcessMessageEx( PI_SET_USER_SETTING, TVG_PLAYER_SETTINGS_MANUFACTURER_ID,	VENDOR_CERTIFICATE_MANUFACTURER_ID );
    ProcessMessageEx( PI_SET_USER_SETTING, TVG_PLAYER_SETTINGS_VENDOR_ID,		VENDOR_CERTIFICATE_VENDOR_ID );
    ProcessMessageEx( PI_SET_USER_SETTING, TVG_PLAYER_SETTINGS_MODEL_ID,		VENDOR_CERTIFICATE_MODEL_ID );
    ProcessMessageEx( PI_SET_USER_SETTING, TVG_PLAYER_SETTINGS_REVISION_ID,		VENDOR_CERTIFICATE_REVISION_ID );
    ProcessMessageEx( PI_GET_USER_SETTING, TVG_PLAYER_SETTINGS_UNIT_ID,         uiUnitID );
    UINT32 uiChkSum = ProcessMessage (PI_GET_CHECKSUM,		0);
    
    psprintf( linebuf, "%d-%d-%d-%d-%d-%d\n", VENDOR_CERTIFICATE_MANUFACTURER_ID, VENDOR_CERTIFICATE_VENDOR_ID, VENDOR_CERTIFICATE_MODEL_ID, VENDOR_CERTIFICATE_REVISION_ID, uiUnitID, uiChkSum );

#ifdef TVG_DBG_ACTIVATION
    printf( linebuf );
#endif

    return linebuf;
}

// **************************************************************************************** //
//input uiCode, verify this code, if right, get the uiUnitID,and store back to E2prom

static inline UINT32 IsValidCode( UINT32 uiCode )
{
#ifdef TVG_DBG_ACTIVATION
    printf( "Activation code %d\n", uiCode );
#endif

    ProcessMessage( SM_ACTIVATE_UNIT, uiCode );
    if( ProcessMessage( PI_GET_ACTIVATION_STATUS, 0 ) )
    {
        UINT16 uiUnitID = ProcessMessage( PI_GET_USER_SETTING, TVG_PLAYER_SETTINGS_UNIT_ID );

#ifdef TVG_DBG_ACTIVATION
        printf( "TVG Activation success %d\n", uiUnitID );
#endif
        return WriteTVGUnitID( uiUnitID );
    }

    return FALSE;
}

// **************************************************************************************** //
static UINT32 TVGCallbackFunc( UINT32 uiMsg )
{
    static UINT32   uiActivationCode;
    static UINT32   uiActivation_cnt;
    static UINT8    uiCount;
    static UINT8	uiHelpFlg = 0;
       
    switch( uiMsg )
    {
    case IRC_ACTIVATE:
        uiCount = 0;
        uiActivationCode = 0;
        uiActivation_cnt = 0;

		#ifdef INDIGO_STYLE_OSDUI
        ShowWindowText( "  REDUCES OFFENSIVE LANG. BY 95%", 15, 2, 5, 6 );
        ShowWindowText( "    VISIT WWW.TVGUARDIAN.COM"    , 15, 2 + 1*ROW_HEI, 5, 6 );
        ShowWindowText( "     OR CALL [886]884-3458"      , 15, 2 + 2 * ROW_HEI, 5, 6 );
        ShowWindowText( "REG KEY:"                        , 30, 2 + 3 * ROW_HEI, 5, 6 );
        UINT8* pBuf = GetRegistrationKey();
        ShowWindowText( pBuf                              , 180, 2 + 3 * ROW_HEI, 5, 6 );    
        ShowWindowText( "ACTIVATION CODE:"                , 30, 2 + 4 * ROW_HEI, 5, 6 );
        ShowWindowText( "  -----  "                       , 300, 2 + 4 * ROW_HEI, 5, 5 );
		#else
        ShowWindowText( "  TVGUARDIAN REDUCES OFFENSIVE ", 2, 2, 2, 6 );
        ShowWindowText( "        LANGUAGE BY 95%", 2, 2 + ROW_HEI, 2, 6 );
        ShowWindowText( "    VISIT WWW.TVGUARDIAN.COM", 2, 2 + 2*ROW_HEI, 2, 6 );
        ShowWindowText( "     OR CALL [886]884-3458", 2, 2 + 3 * ROW_HEI, 2, 6 );
        
        ShowWindowText( "REG KEY:", 2, 2 + 4 * ROW_HEI, 2, 6 );
        UINT8* pBuf = GetRegistrationKey();
        ShowWindowText( pBuf, 200, 2 + 4 * ROW_HEI, 2, 6 );    
        
        ShowWindowText( "ACTIVATION CODE:", 2, 2 + 5 * ROW_HEI, 2, 6 );
        ShowWindowText( "  -----  ", 300, 2 + 5 * ROW_HEI, 2, 5 );
		#endif
        break;
        
        case IRC_TVGHELP:
		uiHelpFlg = 0xfb;
		#ifdef INDIGO_STYLE_OSDUI
        ShowWindowText( "  FOR THE BEST TVG EXPERIENCE"      , 15, 2, 5, 6 );
        ShowWindowText( "   PLEASE SET YOUR TV CLOSED"		 , 15, 2 + ROW_HEI, 5, 6 );
        ShowWindowText( "      CAPTION OPTION TO CC2        ", 15, 2 + 2 *ROW_HEI, 5, 6 );
        ShowWindowText( "     FOR MORE INFORMATION:      "	 , 15, 2 + 3 * ROW_HEI, 5, 6 ); 
        ShowWindowText( "    VISIT WWW.TVGUARDIAN.COM     "	 , 15, 2 + 4 * ROW_HEI, 5, 6 );           
        ShowWindowText( "  BACK  "							 , 200, 2 + 5 * ROW_HEI, 5, 5 );
		#else			
        ShowWindowText( "  FOR THE BEST TVG EXPERIENCE", 2, 2, 2, 6 );
        ShowWindowText( "   PLEASE SET YOUR TV CLOSED", 2, 2 + ROW_HEI, 2, 6 );
        ShowWindowText( "      CAPTION OPTION TO CC2        ", 2, 2 + 2 *ROW_HEI, 2, 6 );
        ShowWindowText( "     FOR MORE INFORMATION:      ", 2, 2 + 3 * ROW_HEI, 2, 6 ); 
        ShowWindowText( "   REFER TO THE USER MANUAL OR    ", 2, 2 + 4 * ROW_HEI, 2, 6 );        
        ShowWindowText( "    VISIT WWW.TVGUARDIAN.COM     ", 2, 2 + 5 * ROW_HEI, 2, 6 );           
        ShowWindowText( "  BACK  ", 200, 2 + 6 * ROW_HEI, 2, 5 );
		#endif
        break;
        
        case IRC_TVGSHOW:
		uiHelpFlg = 0xfb;
		uiActivationCode = 10;
		uiActivation_cnt = 10;
		#ifdef INDIGO_STYLE_OSDUI
        ShowWindowText( "  START USING YOUR TVGUARDIAN "  , 15, 2, 5, 6 );
        ShowWindowText( "  FOUL LANGUAGE FILTER TODAY. "  , 15, 2 + ROW_HEI, 5, 6 );
        ShowWindowText( "    PRESS THE SETUP BUTTON    "  , 15, 2 + 2 * ROW_HEI, 5, 6 ); 
        ShowWindowText( "  AND SELECT TVG TO ACTIVATE. "  , 15, 2 + 3 * ROW_HEI, 5, 6 );        
        ShowWindowText( "[THIS WILL BE DISPLAYED 5 TIMES]", 15, 2 + 4 * ROW_HEI, 5, 6 );
		#else		
        ShowWindowText( "  START USING YOUR TVGUARDIAN ", 2, 2, 2, 6 );
        ShowWindowText( "  FOUL LANGUAGE FILTER TODAY. ", 2, 2 + ROW_HEI, 2, 6 );
        ShowWindowText( "                              ", 2, 2 + 2 *ROW_HEI, 2, 6 );
        ShowWindowText( "    PRESS THE SETUP BUTTON    ", 2, 2 + 3 * ROW_HEI, 2, 6 ); 
        ShowWindowText( "  AND SELECT TVG TO ACTIVATE. ", 2, 2 + 4 * ROW_HEI, 2, 6 );        
        ShowWindowText( "                             ", 2, 2 + 5 * ROW_HEI, 2, 6 );           
        ShowWindowText( "[THIS WILL BE DISPLAYED 5 TIMES]", 2, 2 + 6 * ROW_HEI, 2, 6 );
		#endif
        break;

    case IRC_DESTROY:
        break;
        
    case IRC_SELECT:
    case IRC_PLAY_SELECT:
        if(uiCount == 0xff||uiHelpFlg == 0xfb )
        {
            ExitWindow( uiMsg );
            uiHelpFlg = 0;
        }
        break;

    case IRC_SETUP:        
    case IRC_LEFT:
    case IRC_RIGHT:
        ExitWindow( uiMsg );
        uiHelpFlg = 0;
        break;

    case IRC_TIMER:
        //uiActivationCode--; //huziqin 2006-1-25
        uiActivation_cnt --;
        #ifdef TVG_DBG_ACTIVATION
        printf("---- uiActivationCode=%d -uiActivation_cnt %d---\n",uiActivationCode,uiActivation_cnt);
        #endif
        //if( uiActivationCode == 0 )
        if( uiActivation_cnt == 0 )
        {
            KillTimer();
            ExitWindow( IRC_SELECT );
            uiHelpFlg = 0;
        }
        break;
    
    case IRC_0 ... IRC_9 :
    	if(uiHelpFlg!=0xfb)
    {
        if( uiCount == 0 )
	    {
			#ifdef INDIGO_STYLE_OSDUI
	            ShowWindowText( "                        ", 65, 2 + 5 * ROW_HEI, 1, 6 );
			#else
            ShowWindowText( "                        ", 65, 2 + 6 * ROW_HEI, 2, 6 );
			#endif
        }

        UINT8 aTmp[2] = { uiMsg - IRC_0 + '0', '\0' };

        printf("IRC0-9: %d %d\n",uiActivationCode,( uiMsg - IRC_0 ));

        uiActivationCode = uiActivationCode * 10 + ( uiMsg - IRC_0 );

        printf("uiActivationCode = %d\n",uiActivationCode);

		#ifdef INDIGO_STYLE_OSDUI
	        ShowWindowText( aTmp, 300 + ( 2 + uiCount ) * 16, 2 + 4 * ROW_HEI, 7, 5 );
		#else
        ShowWindowText( aTmp, 300 + ( 2 + uiCount ) * 16, 2 + 5 * ROW_HEI, 2, 5 );
#endif
        uiCount++;
        if( uiCount == 5 )
        {
            if( !IsValidCode( uiActivationCode ) )
            {
#ifdef TVG_DBG_ACTIVATION
                printf( "Activation fail, invalid code %d\n",uiActivationCode );
#endif
 				#ifdef INDIGO_STYLE_OSDUI
	                ShowWindowText( "  -----  ", 300, 2 + 5 * ROW_HEI, 1, 5 );
	                ShowWindowText( "INVALID CODE. TRY AGAIN.", 65, 2 + 5 * ROW_HEI, 1, 5 );
				#else				
                ShowWindowText( "  -----  ", 300, 2 + 5 * ROW_HEI, 2, 5 );
                ShowWindowText( "INVALID CODE. TRY AGAIN.", 65, 2 + 6 * ROW_HEI, 2, 5 );
				#endif
                uiCount = 0;
                uiActivationCode = 0;
            }
            else
            {
#ifdef TVG_DBG_ACTIVATION
                printf( "Activation success\n" );
#endif
 				#ifdef INDIGO_STYLE_OSDUI
					ShowWindowText( "TVG ACTIVATED...", 30, 2 + 5 * ROW_HEI, 1, 5 );
				#else
                ShowWindowText( "TVG ACTIVATED...", 30, 2 + 6 * ROW_HEI, 2, 5 );
				#endif
                uiCount = 0xff;
                uiActivationCode = 2;
                uiActivation_cnt = 2; //huziqin 2006-1-25
                SetTimer( 100 );
            }
        }
    }
        break;
    }
    
    return TRUE;
}

#if 1//david test 2006-1-25

unsigned long TVG_RandomSeed (void)
{
	return get_rtc_val();
}


//=============================================================================
// Check to see if unit has been branded, basically it has been branded if
// it is not zero.
//=============================================================================
BOOL TempCheckBranded (WORD unit_id)
{
	// Has our unit been branded?
	return (BOOL)  (unit_id != 0);
}

WORD SimpleCrypt16 (WORD value, WORD offset);

#define XOR_ID_MASK	0xC0DA

//=============================================================================
//
// Brand our machine with hard to duplicate identifier that is
// Calculated by a seeding a random number with the program counter
//
// Return:			FALSE	- Our system has already been branded
//					TRUE	- System has now been branded
//
//=============================================================================


BOOL TempBrandUNITID (void)
{
	BOOL	fRet = FALSE;
	WORD	unit_id;

	// Check if we have already branded this
	unit_id = (WORD) ProcessMessage (PI_GET_UNIT_ID, 0);

	// Check if this has been branded
	if (!CheckBranded (unit_id))
	{
		// Do the calculation for our Unit ID
		unit_id = (WORD) RandomNumber (TVG_RandomSeed ());

		// Pass through the encryption routine
		unit_id	= SimpleCrypt16 (unit_id, XOR_ID_MASK);

		
		// Force the unit_id to within our target range
		// This is to guarantee a minimum and maximum number of digits for our unit_id
		unit_id = (WORD) (unit_id % ((WORD) VENDOR_CERTIFICATE_UNITID_MAX - (WORD) VENDOR_CERTIFICATE_UNITID_MIN));
		unit_id = (WORD) (unit_id + VENDOR_CERTIFICATE_UNITID_MIN);

		ProcessMessage (PI_SET_UNIT_ID, unit_id);

		fRet = TRUE;
	}

	return (fRet);
}

#endif //if 1
// **************************************************************************************** //
// tell us whether unit id is branded.we will send the id to TVG lib,then the lib return the 
// status.
static inline UINT32 IsTVGBranded()
{
    UINT16  uiUnitID;
    
#if 0//ndef DVDRELEASE
    if( !ReadTVGUnitID( &uiUnitID ) )
        return FALSE;
#else
    ReadTVGUnitID( &uiUnitID );
#endif

#ifdef TVG_DBG_ACTIVATION
    printf( "TVG UnitID from EEPROM %d\n", uiUnitID );
#endif

    ProcessMessageEx( PI_SET_USER_SETTING, TVG_PLAYER_SETTINGS_UNIT_ID,	uiUnitID );
    return ProcessMessageEx( SM_GET_BRANDED_STATUS, 0, 0 );
}

// **************************************************************************************** //
static inline UINT32 TVGBrand()
{
    UINT16 uiUnitID;

	TempBrandUNITID (); //david 2006-1-25

	//ProcessMessage( SM_BRAND_UNIT, 0 );

    //uiUnitID = (get_rtc_val()&9999)|1000; 
	//WriteTVGUnitID(uiUnitID);
	uiUnitID =  ProcessMessage( PI_GET_USER_SETTING, TVG_PLAYER_SETTINGS_UNIT_ID );

    //uiUnitID = (get_rtc_val()&9999)|1000;    

#ifdef TVG_DBG_ACTIVATION
    printf( "TVG UnitID write to EEPROM %d\n", uiUnitID );
#endif

	return WriteTVGUnitID( uiUnitID );
}

// **************************************************************************************** //
static UINT8 MessageBox_TVGActivation()
{
	UINT16 unit_id = 0xff;
	
	ReadTVGUnitID( &unit_id );
	printf("MessageBox_TVGActivation unit id %d\n",unit_id);
	if(unit_id==0)
	{
        unit_id = (get_rtc_val()&9999)|1000;
        printf("unit id %d\n",unit_id);
		WriteTVGUnitID(unit_id);
	}
    RegisterCallback( TVGCallbackFunc );
#ifdef INDIGO_STYLE_OSDUI
    CreateWindow( 0, "TVG ACTIVATION", (WS_CAPTION|WS_THICKFRAME|WS_SYSMENU), 20, 96, 532, 234 );
#else
    CreateWindow( 0, "TVG ACTIVATION", (WS_CAPTION|WS_THICKFRAME|WS_SYSMENU), 10, 96, 532, 234 );
#endif	
    ShowWindow();
    return WindowMain(IRC_ACTIVATE);
}

//*****************************************************************************************
UINT8 MessageBox_TVGHelp()
{

    RegisterCallback( TVGCallbackFunc );
#ifdef INDIGO_STYLE_OSDUI
    CreateWindow( 0, "TVG SETUP HELP", (WS_CAPTION|WS_THICKFRAME|WS_SYSMENU), 20, 96, 532, 234 );
#else
    CreateWindow( 0, "TVG SETUP HELP", (WS_CAPTION|WS_THICKFRAME|WS_SYSMENU), 10, 96, 532, 234 );
#endif
    ShowWindow();
    return WindowMain(IRC_TVGHELP);
}

UINT8 MessageBox_TVGSTART()
{

    RegisterCallback( TVGCallbackFunc );
#ifdef INDIGO_STYLE_OSDUI
    CreateWindow( 0, "TVGUARDIAN INFORMATION", (WS_CAPTION|WS_THICKFRAME|WS_SYSMENU), 20, 30, 532, 234 );
#else
    CreateWindow( 0, "TVGUARDIAN INFORMATION", (WS_CAPTION|WS_THICKFRAME|WS_SYSMENU), 10, 30, 532, 234 );
#endif

    ShowWindow();
    SetTimer(100);
    return WindowMain(IRC_TVGSHOW);
}

/***************************************************************
== linrc create 2005-12-15 15:43
***************************************************************/
void osd_init_Wnd(void)
{
    
    __osd_init();

    header_id = SETUP_HEADER;
          	
    region[0].osd_w = 35*8;                  //35 English Characters
    region[0].osd_h = 10*SETUP_BTN_HEIGHT;   //10 lines
                
    osd_create_region1(0, 38,  30, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
 
    osd_active_regions = 1;
    ENABLE_OSD();
}

void ShowTVG_INFO_UI(void)
{
	UINT8 Counter;
	ReadFromI2c( 0xa0, TVG_SHOWAD_COUNTER_ADDR, &Counter, 1 );
	if(Counter!=0&&Counter>5)
	{
		Counter = 0;
		WriteToI2c( 0xa0, TVG_SHOWAD_COUNTER_ADDR, &Counter, TVG_SHOWAD_COUNTER_SIZE );
	}
	#ifdef TVG_DBG_ACTIVATION
	printf("ReadFromI2c%x=%d \n",TVG_SHOWAD_COUNTER_ADDR,Counter);
	#endif
	if(Counter<5)
	{
		Counter++;
		WriteToI2c( 0xa0, TVG_SHOWAD_COUNTER_ADDR, &Counter, TVG_SHOWAD_COUNTER_SIZE );
		osd_init_Wnd();
		MessageBox_TVGSTART();
		osd_init();
	}
}
/**************************************************************/
//*****************************************************************************************
// indicate whether TVG is activated or not.
// By the way, check whether unit id is branded, if not branded,call TVGBrand() 
// **************************************************************************************** //
static UINT32 IsTVGActivated()
{
    if( !IsTVGBranded() )
    {
#ifdef TVG_DBG_ACTIVATION
        printf( "TVG not branded\n" );
#endif
        if(full_scrn & SETUP)	//Because sysman.c call this function in same time,so we can't get a random id,so I modify 2006-3-14 14:58
        {
        if( !TVGBrand() )
            return FALSE;
        }else return FALSE;
    }
#ifdef TVG_DBG_ACTIVATION
    else
        printf( "TVG branded\n" );
#endif

	return ProcessMessageEx( PI_GET_ACTIVATION_STATUS, 0, 0 );
}

// **************************************************************************************** //
UINT32 TVGActivationProcess()
{
    if(IsTVGActivated())
    {
#ifdef TVG_DBG_ACTIVATION
        printf( "TVG activated\n" );
#endif
        return TRUE;
    }
    
    UINT8 uiRes = MessageBox_TVGActivation();
    if( uiRes == IRC_SELECT )
    {
        TVGInitSystem( 0 );
#ifdef TVG_DBG_ACTIVATION
        printf( "TVG activated\n" );
#endif
        return TRUE;
    }

    call_ir_func( uiRes );
    return FALSE;
}
    #else
#define IsTVGActivated()    TRUE
    #endif

/************************************************************************************
    TVG Filtering Function
************************************************************************************/

#include "auddrv.h"
UINT8   s_uiMuteControlByTVG;

void    TVGProcessData( UINT8 *ccdata, UINT8 field );
void    (*l21_callback_func)( UINT8* ccdata, UINT8 field ) = TVGProcessData;

// **************************************************************************************** //
extern void TVGSetMode( UINT8 uiMode )
{
    SetTVGMode( uiMode );
    
#ifdef TVG_DBG_FLOW
    printf( "GetTVGMode %d\n", GetTVGMode() );
#endif
}

// **************************************************************************************** //
extern void TVGSetWordSets( UINT8 uiMode, UINT8 uiFlag )
{
    UINT8 uiWordSet = GetTVGWordset();
    if( uiFlag )
        uiWordSet |= uiMode;
    else
        uiWordSet &= ~uiMode;
        
    SetTVGWordset( uiWordSet );

#ifdef TVG_DBG_FLOW
    printf( "GetTVGWordset %d %d\n", uiMode, GetTVGWordset() );    
#endif
}

// **************************************************************************************** //
extern void TVGSetCCOperation( UINT8 uiMode )
{
    SetTVGCCOperation( uiMode );
    
#ifdef TVG_DBG_FLOW
    printf( "GetTVGCCOperation %d\n", GetTVGCCOperation() );
#endif
}

// **************************************************************************************** //
extern void TVGSetCCChannel( UINT8 uiMode )
{
    SetCCShiftValue( uiMode );
    
#ifdef TVG_DBG_FLOW
    printf( "GetCCShiftValuee %d\n", GetCCShiftValue() );
#endif
}

// **************************************************************************************** //
extern void TVGInitSystem( UINT8 uiCmd )
{
    if( IsTVGActivated() )
    {
        s_uiMuteControlByTVG = FALSE;
        tvg_init( uiCmd );

#ifdef TVG_DBG_FLOW
        printf( "***** TVGInitSystem *****\n" );
        printf( "GetTVGMode %d\n", GetTVGMode() );
        printf( "GetTVGCCOperation %d\n", GetTVGCCOperation() );
        printf( "GetCCShiftValuee %d\n", GetCCShiftValue() );
        printf( "GetTVGWordset %d\n", GetTVGWordset() );
#endif
    }
}

// **************************************************************************************** //
extern void TVGProcessData( UINT8 *ccdata, UINT8 field )
{
    tvg_process( ccdata, ccdata, field );
}

// **************************************************************************************** //
extern UINT8 TVGControlMute()
{
    return s_uiMuteControlByTVG;
}

// **************************************************************************************** //
extern void TVGRequestMute( int mute_flg )
{
    // mute_flg == 1, means it needs to mute
    // mute_flg == 0, means it needs to demute
#ifdef TVG_DBG_FLOW
    printf( "***** TVGRequestMute %d *****\n", mute_flg );
#endif

    if( mute_flg )
    {
        if( !user_mute )
        {
            AUDIF_Set_Volume(0);
            s_uiMuteControlByTVG = TRUE;
        }
    }
    else
    {
        if( !user_mute )
        {
            AUDIF_Demute();
            s_uiMuteControlByTVG = FALSE;
        }
    }
    
    //extern void ircmd_mute();
    //ircmd_mute();
}
#else
void (*l21_callback_func)( UINT8* ccdata __UNUSED, UINT8 field __UNUSED ) = NULL;
#endif


