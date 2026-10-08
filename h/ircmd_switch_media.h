#ifndef __DIRECT_ACCESS_MEIDA_H__
#define __DIRECT_ACCESS_MEIDA_H__


/****************************************************************************************\
**                                       Micros                                         **
\****************************************************************************************/
//region
#define SWITCH_GUI_REGION  (3)

//color
#ifdef INDIGO_STYLE_OSDUI
#define SWGUI_FONT_COLOR      (5)
#define SWGUI_MAIN_BG_COLOR   (6)
#define SWGUI_HL_FONT_COLOR   (1)
#define SWGUI_HL_BG_COLOR     (7)
#define SWGUI_MARK_BG_COLOR   (1)
#define SWGUI_TRANS_COLOR     (15)
#elif defined(NEW_MP3_GUI)
#define SWGUI_FONT_COLOR      (2)
#define SWGUI_MAIN_BG_COLOR   (6)
#define SWGUI_HL_FONT_COLOR   (1)
#define SWGUI_HL_BG_COLOR     (5)
#define SWGUI_MARK_BG_COLOR   (4)
#define SWGUI_TRANS_COLOR     (15)
#endif

//item
#if (defined(SUPPORT_USB) && defined(SPHE8202_CARD_STORAGE) && defined(DVD_SERVO)&& !defined(NO_DVD_SERVO))
#define SWGUI_MAX_ITEM        (3)    //DISC + USB + CARD
#elif (defined(SUPPORT_USB) && !defined(SPHE8202_CARD_STORAGE) && defined(DVD_SERVO)&& !defined(NO_DVD_SERVO))
#define SWGUI_MAX_ITEM        (2)    //DISC + USB
#elif (!defined(SUPPORT_USB) && defined(SPHE8202_CARD_STORAGE) && defined(DVD_SERVO)&& !defined(NO_DVD_SERVO))
#define SWGUI_MAX_ITEM        (2)    //DISC + CARD
#elif (defined(SUPPORT_USB) && defined(SPHE8202_CARD_STORAGE) && defined(NO_DVD_SERVO) && !defined(DVD_SERVO))
#define SWGUI_MAX_ITEM        (2)    //USB + CARD
#endif


/****************************************************************************************\
**                                 External References                                  **
\****************************************************************************************/
#ifdef SUPPORT_USB
extern  UINT8  SLAVE_ENUMERATED;
#endif//SUPPORT_USB

extern  BYTE   osd0_state;


/****************************************************************************************\
**                                     Enumrations                                      **
\****************************************************************************************/
//media destinations
enum {
    DES_CARD = 0,
    DES_USB,
    DES_DISC,
};

enum {
    OSD0_STATE_INIT = 0,
	OSD0_STATE_HIDE,
	OSD0_STATE_FADE_IN,
	OSD0_STATE_FULL_SHOW,
	OSD0_STATE_FADE_OUT,
};


/****************************************************************************************\
**                               Function Declarations                                  **
\****************************************************************************************/
extern void	Card_power_reset( void );
extern UINT32 sdDetect( void );
extern UINT32 msDetect( void );
extern UINT32 smcDetect( void );
extern UINT32 cfIdeDetect( void );
extern void InitVar( void );


extern void osd_print_storage_detect_info( void );
extern void switch_media_show_HL( void );

#ifdef SUPPORT_USB
extern void usb_test_ready( void );
#endif//SUPPORT_USB

#ifdef SPHE8202_CARD_STORAGE
extern void card_test_ready( void );
#endif//SPHE8202_CARD_STORAGE

extern void switch_media_up( void );
extern void switch_media_down( void );
extern void switch_media_select( void );
extern void exit_switch_media_gui( void );

//#if 0//wangw mark.20061013
extern UINT32 is_usb_media_exists( void );
extern UINT32 is_card_media_exists( void );
//#endif


#endif //__DIRECT_ACCESS_MEIDA_H__


