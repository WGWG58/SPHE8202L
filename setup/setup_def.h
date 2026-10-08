#ifdef Ti3001_OSD_UI_2
    #define MAX_SETUP_PAGE          8
#elif defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //fengjl edit 2004-06-22 18:55
    #define MAX_SETUP_PAGE        7
    //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#elif defined(NEXTPAGE_SYS)     //freyman 2004-3-25 22:39
    #define MAX_SETUP_PAGE          7       //max. pages(# of level-1 selection items)
#elif defined(QSI_SETUP_MENU)//liweihua 2004-6-15
    #define MAX_SETUP_PAGE          6//4  one page as background
#elif defined(EASTECH_NEW_SETUP_MENU)   
    #define MAX_SETUP_PAGE          4
#elif defined(EASTECH_DP3240_SETUP_MENU)   //add xrh 2004_12_08
    #define MAX_SETUP_PAGE          4	
#elif defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)  
    #define MAX_SETUP_PAGE          8
#elif defined(PULIANG_SETUP_MENU)
    #define MAX_SETUP_PAGE          5   //yaowh 04-12-15
#elif defined(ALCO_PORTABLE_SETUP_MENU)&&defined(DVD_SETUP_REENG)&&!defined(USE_ITEM_HIDE_LAYOUT)//mark 05/08/06 for use hide menu
    #ifdef NO_SPDIF_OUTPUT
    #define MAX_SETUP_PAGE          3
    #else
    #define MAX_SETUP_PAGE          4
    #endif
#else
    #define MAX_SETUP_PAGE          6       //max. pages(# of level-1 selection items)
#endif
    
#define MAX_CUSTM_SETUP_PAGE    1       //max. pages of engerineering page(press 8561 to enter)

//yanlb added 2004/07/15,modify 07/21,modify 09/10
//#define SAVE_NUM 2
#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ
#define MAX_BAND    5
#else
#define MAX_BAND 7
#endif
#define MAX_3D_PAGE_ITEM   4
extern UINT8 sound_sel[MAX_3D_PAGE_ITEM];
extern UINT8 user_osd_set[MAX_BAND];

#ifdef REMB_3DSOUND
extern void run_sound_save(BYTE *p);
extern int load_3Dsound(UINT8 *sound_save,UINT8 *user_osd_set);
extern void exe_3Dsound(UINT8 *sound_save,UINT8 *user_osd_set);
#endif

#ifdef SETUP_RESTORE_ALSO_RESTORE_3D  //added by wangwei,2004-9-17 16:05
extern void restore_3Dsound(void);
#endif

#if defined(SOUND_EFFECT_MENU)||defined(REMB_3DSOUND)         // sunzhh add 2004-4-30 10:52
#ifdef SEVEN_OPTIONS_IN_EQ
#define MAX_MUSIC       7
#else
#define MAX_MUSIC       5
#endif
BYTE EQ_type;
BYTE surround_type;
extern const UINT8 music_osd_set[MAX_MUSIC][MAX_BAND];
void SettingEqLevel(BYTE *);
void SettingEQType(BYTE type);
void SetEQ(void);
void SetSurround(void);
#endif             //#ifdef SOUND_EFFECT_MENU

#ifdef SETUP_6_DIGIT_PASSWORD
#define PASSWORD_LENGTH         6
#else
#define PASSWORD_LENGTH         4
#endif
//define selection items count

#define MAX_PAGE_ITEM           8       //max. selection items in page(# of level-2 selection items)
#ifdef EASTECH_NO_PARENTAL_CONTROL
#define MAX_ITEM_SEL            11      
#else
#define MAX_ITEM_SEL            10      //selected value from MIN_ITEM_SEL to MAX_ITEM_SEL
#endif
#define MIN_ITEM_SEL            2       //min. selected value, 0th:item-function, 1st:item-string-id

//define GUI setting
#define SETUP_MAX_WIDTH         35      //English-characters-width

#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-8 17:38 WP
#define SETUP_MAX_LINE          10      //lines
#elif defined(SOFT_MENU_REENG) //chenzhao
#define SETUP_MAX_LINE          10      //lines
#else
#define SETUP_MAX_LINE          12      //lines
#endif
#ifdef INDIGO_STYLE_OSDUI
	#define SETUP_BUTTON_HEIGHT     (24+4)  //24:font height, 4:top and bottom border
#else	
#define SETUP_BUTTON_HEIGHT     (24+8)  //24:font height, 4:top and bottom border
#endif

//string coordinate
//x: i-th English character with 16 pixel
//y: j-th line with SETUP_BUTTON_HEIGHT pixel
#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-16 10:26 WP
#define SETUP_MENU_XSTART       (ITEM_XSTART/8)//string start at x-axis
#define SETUP_MENU_YSTART       (TITLE_HEIGHT/SETUP_BUTTON_HEIGHT)       //string start at y-axis
#define SETUP_SUB_XSTART        (SELECT_XSTART/8+1)
#elif defined(INDIGO_STYLE_OSDUI) // mimitsai add for new ui 2005.11.01
	#define SETUP_MENU_XSTART       2       //string start at x-axis
	#define SETUP_MENU_YSTART       3       //string start at y-axis
	#define SETUP_SUB_XSTART        18
#elif !defined(SOFT_MENU_REENG)//chenzhao 20050523 //move to setup_def_sfm_reeng.h
#ifdef USE_SETUP_SELECT_FONT
#define SETUP_MENU_XSTART       1       //string start at x-axis
#define SETUP_MENU_YSTART       2       //string start at y-axis
#define SETUP_SUB_XSTART        16
#elif defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
	#define SETUP_MENU_XSTART       4       //string start at x-axis
	#define SETUP_MENU_YSTART       2       //string start at y-axis
	#define SETUP_SUB_XSTART        20
#else
#define SETUP_MENU_XSTART       2       //string start at x-axis
#define SETUP_MENU_YSTART       2       //string start at y-axis
#define SETUP_SUB_XSTART        18
#endif

#endif//SOFT_MENU

#ifdef DVD_SETUP_REENG
//JSLin 20040908	
//move setup menu color setting to ..\\customers\XXXX\setup_menu_XXXX.c
//after setup_item
#else
//16-Color table:see palette_16color_setup() in osd1.c
    #if defined(SETUP_COLOR_TYPE2) && !defined(PULIANG_SETUP_MENU)//yaowh modify 04-12-15//zhangyu 3-9-2 4:49张宇P
#define STITLECOLOR             7
#define SFONTCOLOR              10
#ifdef SELECT_MEDIA_IN_SETUPMENU
#define SGRAYCOLOR              12      //Maoyong 2004/8/11 disable item in red
#elif defined(DVB_MENU_SETUP_STYLE)     //Maoyong 2004-12-22 10:51
#define SGRAYCOLOR              8
#else
#define SGRAYCOLOR              13
#endif       
#define SRECTCOLOR              14
#define SANTIBGCOLOR            6  //14
#define SBGCOLOR                14
#define SANTIFONTCOLOR          1
#define SBLACKCOLOR             0
#define SWHITECOLOR             2
#define SDEFAULTCOLOR       4
#define SBARCOLOR       14

#elif defined(SETUP_COLOR_TYPE1)
    #define SFONTCOLOR              2
#define SBARCOLOR       1
#define SSHEER          15
#define SRECTCOLOR              4
    #define SANTIBGCOLOR            10//12//13//5
#define SBGCOLOR        10//12
    #define SBLACKCOLOR             0
#define SWHITECOLOR             2
#define SANTIFONTCOLOR          7//11//2
#define SDEFAULTCOLOR       0//4
#define SGRAYCOLOR              3

#elif defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-2 17:14
    #define SFONTCOLOR              6//肅︹瞏:计禫肅︹禫瞏
    #define SBARCOLOR               0//1
    #define SSHEER                  0//15
    #define SRECTCOLOR              0//4
    #define SANTIBGCOLOR            0//6//10//12//13//5
    #define SBGCOLOR                0//10//12
    #define SBLACKCOLOR             0
    #define SWHITECOLOR             0
    #define SANTIFONTCOLOR          12//7//11//2
    #define SDEFAULTCOLOR           13//4
    #define SGRAYCOLOR              0//3
    #define STITLECOLOR             12////org 0
    #else//#ifdef SETUP_COLOR_TYPE2
#define STITLECOLOR             11
#ifdef SPE_SETUP            //linrc modify for hanyang 2004-4-28 19:06
#define SFONTCOLOR              2//11
#define SANTIFONTCOLOR          11//2
#define SBARCOLOR       6//1
#define SBGCOLOR                1//6
#else//#ifdef SPE_SETUP         //linrc modify for hanyang 2004-4-28 19:06
#define SFONTCOLOR              11
    #define SANTIFONTCOLOR          2
#define SBARCOLOR       1
#define SBGCOLOR                6
#endif//#ifdef SPE_SETUP            //linrc modify for hanyang 2004-4-28 19:06
#define SGRAYCOLOR              3
    
#define SSHEER          15
#define SRECTCOLOR              4
#define SANTIBGCOLOR            5
#define SBLACKCOLOR             11

        #ifdef PULIANG_SETUP_MENU    //yaowh add 04-12-15
            #define S16WHITEFONT        11
        #else
#define S16WHITEFONT            2  //2004-4-16 09:41张宇P
        #endif

#ifdef S16BM_SETUP_STR
#ifdef SPE_SETUP        //linrc modify for hanyang 2004-4-28 19:06
#define SWHITECOLOR             6//1//11//2 
#define SDEFAULTCOLOR       4//1//4  2004-4-16 09:17张宇P
#define SDEFAULTCOLOR1       6
#else
#define SWHITECOLOR             1//11//2 
#define SDEFAULTCOLOR       1//4
#endif
#else
#define SWHITECOLOR             2
#define SDEFAULTCOLOR           4  //2004-4-16 09:17张宇P
#endif
    #endif  //#ifdef SETUP_COLOR_TYPE2      //zhangyu 3-9-1 4:34张宇P
//////////////////////////
#endif //end of DVD_SETUP_REENG

#ifdef SCART_TV
    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[39 / 16] |= (0x1 << (39 % 16))) : (regs0->gpio_out[39 / 16] &= ~(0x1 << (39 % 16))))
    #define SET_SCART_SW(d)     ((d) ? (regs0->gpio_out[38 / 16] |= (0x1 << (38 % 16))) : (regs0->gpio_out[38 / 16] &= ~(0x1 << (38 % 16))))
    #define SET_SCART_TV(d)     ((d) ? (regs0->gpio_out[37 / 16] |= (0x1 << (37 % 16))) : (regs0->gpio_out[37 / 16] &= ~(0x1 << (37 % 16))))
#elif defined(KSD_SCART_TV)

    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16))) : (regs0->gpio_out[57 / 16] &= ~(0x1 << (57 % 16))))
    //#define SET_SCART_SW(d)       ((d) ? (regs0->gpio_out[18 / 16] |= (0x1 << (18 % 16))) : (regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16))))
#elif defined(SCART_TV_2)    //wanghaoying 2003-8-13 15:11 added 
    #ifdef THAKRAL_DVD
        #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[18 / 16] |= (0x1 << (18 % 16))) : (regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16))))
        #define SET_SCART_SW(d)     ((d) ? (regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16))) : (regs0->gpio_out[57 / 16] &= ~(0x1 << (57 % 16))))
    #else
    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16))) : (regs0->gpio_out[57 / 16] &= ~(0x1 << (57 % 16))))
    #define SET_SCART_SW(d)     ((d) ? (regs0->gpio_out[18 / 16] |= (0x1 << (18 % 16))) : (regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16))))
    #endif
    
    #ifdef NIN_SCART_TV  //fangang added 4-2-11 17:04
           #define SET_SCART_TV(d)      ((d) ? (regs0->gpio_out[2 / 16] |= (0x1 << (2 % 16))) : (regs0->gpio_out[2 / 16] &= ~(0x1 << (2 % 16))))
    #endif

    #ifdef YILI_SCART_TV  //hq add, use 31 pin control  TV-AV switch, 4-2-17 9:40 
           #define SET_SCART_TV(d)      ((d) ? (regs0->gpio_out[4 / 16] |= (0x1 << (4 % 16))) : (regs0->gpio_out[4 / 16] &= ~(0x1 << (4 % 16))))
    #endif

#elif defined(SCART_TV_3)   //wanghaoying 2003-9-12 11:28 added
    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[57 / 16] |= (0x1 << (57 % 16))) : (regs0->gpio_out[57 / 16] &= ~(0x1 << (57 % 16))))
    #define SET_SCART_SW(d)     ((d) ? (regs0->gpio_out[18 / 16] |= (0x1 << (18 % 16))) : (regs0->gpio_out[18 / 16] &= ~(0x1 << (18 % 16))))
    
    #define SET_SCART_SW1(d)    ((d) ? (regs0->gpio_out[14 / 16] |= (0x1 << (14 % 16))) : (regs0->gpio_out[14 / 16] &= ~(0x1 << (14 % 16))))

#elif defined(SCART_TV_4)   //nono 2003-9-26 1:44 for himage HJ-018

    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[3 / 16] |= (0x1 << (3 % 16))) : (regs0->gpio_out[3 / 16] &= ~(0x1 << (3 % 16))))
        #ifdef HJ_021_SCART
        #define SET_SCART_SW1(d)        ((d) ? (regs0->gpio_out[4 / 16] |= (0x1 << (4 % 16))) : (regs0->gpio_out[4 / 16] &= ~(0x1 << (4 % 16))))
        #define SET_SCART_SW(d) ((d) ? (regs0->gpio_out[2 / 16] |= (0x1 << (2 % 16))) : (regs0->gpio_out[2 / 16] &= ~(0x1 << (2 % 16))))
        #else//#ifdef HJ_021_SCART
    #define SET_SCART_SW(d)     ((d) ? (regs0->gpio_out[4 / 16] |= (0x1 << (4 % 16))) : (regs0->gpio_out[4 / 16] &= ~(0x1 << (4 % 16))))
    #define SET_SCART_SW1(d)    ((d) ? (regs0->gpio_out[2 / 16] |= (0x1 << (2 % 16))) : (regs0->gpio_out[2 / 16] &= ~(0x1 << (2 % 16))))
        #endif//#ifdef HJ_021_SCART
#elif defined(SCART_TV_5)//wangfeng 2003-12-2 11:43 for himage HJ-023
    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[63 / 16] |= (0x1 << (63 % 16))) : (regs0->gpio_out[63 / 16] &= ~(0x1 << (63 % 16))))
    #define SET_SCART_SW(d)     ((d) ? (regs0->gpio_out[62 / 16] |= (0x1 << (62 % 16))) : (regs0->gpio_out[62 / 16] &= ~(0x1 << (62 % 16))))    
    #define SET_SCART_SW1(d)    //((d) ? (regs0->gpio_out[2 / 16] |= (0x1 << (2 % 16))) : (regs0->gpio_out[2 / 16] &= ~(0x1 << (2 % 16))))
#elif defined(XQ_SCART_TV)//xyy 2004-4-22
    #define SET_SCART_RGB(d)    ((d) ? (regs0->gpio_out[SCART_SIG / 16] |= (0x1 << (SCART_SIG % 16))) : (regs0->gpio_out[SCART_SIG / 16] &= ~(0x1 << (SCART_SIG % 16))))
    #define SET_SCART_SW(d)     ((d) ? (regs0->gpio_out[SCART_DISPLAY / 16] |= (0x1 << (SCART_DISPLAY % 16))) : (regs0->gpio_out[SCART_DISPLAY / 16] &= ~(0x1 << (SCART_DISPLAY % 16))))
    #define SET_SCART_TV(d)     ((d) ? (regs0->gpio_out[SCART_RELEASE / 16] |= (0x1 << (SCART_RELEASE % 16))) : (regs0->gpio_out[SCART_RELEASE / 16] &= ~(0x1 << (SCART_RELEASE % 16))))
#endif



#ifdef IR_KEY_SET_VIDEO_MODE
#ifdef SET_4_VIDEO_MODE
#define VIDEO_MODE_VAL_DEFAULT      3
#else//#ifdef SET_4_VIDEO_MODE
#define VIDEO_MODE_VAL_DEFAULT      0
#endif//#ifdef SET_4_VIDEO_MODE
#endif//#ifdef IR_KEY_SET_VIDEO_MODE

#ifdef NO_DIGIT_MENU
#define MAX_SHOW_PAGE 4
#elif defined(NO_DIGIT_VIDEO_MENU)
#define MAX_SHOW_PAGE 3
#elif defined(HANYANG_SETUPMENU)//caoh 2004-6-18 11:13
#define MAX_SHOW_PAGE 3
#else//NO_DIGIT_MENU
  #ifdef SETUP_DONGLI459
#define MAX_SHOW_PAGE 4
#elif defined(BBK_SIMPLE_SETUP)             //sunzhh add for bbk_dv911s 2004-4-22 15:04
    #define MAX_SHOW_PAGE          3 
    #elif defined(QSI_SETUP_MENU)//liweihua 2004-6-15
    #define MAX_SHOW_PAGE           3
	#elif defined(SOFT_MENU)//Modifed by ChenZhao on 2004-9-1 14:12 WP
	    #if defined(EASTECH_SETUPMENU)||defined(EASTECH_DP3240_SETUP_MENU)
        #define MAX_SHOW_PAGE 3
        #else 
        #define MAX_SHOW_PAGE 5
        #endif
    #elif defined(PULIANG_SETUP_MENU)  //yaowh add 04-12-15
        #define MAX_SHOW_PAGE       4
  #else
#define MAX_SHOW_PAGE 5
    #endif//#ifdef SETUP_DONGLI459
#endif//NO_DIGIT_MENU

#ifdef  DYNAMIC_SPECTRUM  //fengjl  3-10-21 20:38
#undef SAME_DISC_RESUME
extern void Show3dspectrum(void); 
#define EQ_R                3
#define BAND_R              3
#define SWHITECOLOR         2
#define PAGE_WIDTH    (29*16)
#endif

//to show "INPUT PASSWORD"
#define MESSAGE_XSTART  2
#define MESSAGE_YSTART  4 

#ifdef SETUP_DONGLI459    //dingzhy  
#define MESSAGE_BK_COLOR  2
#define MESSAGE_FONT_COLOR 0 //zhaoyanhua modfiy 2004-1-16 14:19
#else
#define MESSAGE_BK_COLOR  0
#define MESSAGE_FONT_COLOR 7//11 zhaoyanhua modfiy 2004-1-16 14:19
#endif

//to show PASSWORD
#define PASSWORD_XSTART  MESSAGE_XSTART+ 12
#define PASSWORD_YSTART  MESSAGE_YSTART
#define PASSWORD_BK_COLOR  2
#define PASSWORD_FONT_COLOR 0
//to show OK or ERROR
#define OKERROR_XSTART  PASSWORD_XSTART + 2
#define OKERROR_YSTART  PASSWORD_YSTART+16

#ifdef SETUP_DONGLI459    //dingzhy
#define OKERROR_BK_COLOR  2//4
#define OKERROR_FONT_COLOR 0//5
#else
#define OKERROR_BK_COLOR  4
#define OKERROR_FONT_COLOR 5
#endif

//to show HL
#ifndef ALCO_PORTABLE_SETUP_MENU
#define PASSWORD_FONT_HL_COLOR  SANTIFONTCOLOR//5 //zhaoyanhua 2004-1-16 14:24
#define PASSWORD_BK_HL_COLOR    SANTIBGCOLOR//4//zhaoyanhua 2004-1-16 14:24
#endif

#define PASSWD_BUTTON_XSTART  (PASSWORD_XSTART-2)*16
#define PASSWD_BUTTON_YSTART  PASSWORD_YSTART+10
#define PASSWD_BUTTON_XLEN    9*16
#define PASSWD_BUTTON_YLEN    1*32+8
#define OKERROR_BUTTON_XLEN   9*16
#define OKERROR_BUTTON_YLEN   40
#define OKERROR_BUTTON_XSTART  PASSWD_BUTTON_XSTART
#define OKERROR_BUTTON_YSTART  PASSWD_BUTTON_YSTART+ PASSWD_BUTTON_YLEN + 20


#ifdef SETUP_PASSWORD_GUI

//color define 
//NOTE:
//these color is in SETUP_COLOR_TYPE2
//if you use other type, please change color yourself.
#define  PASSWD_GUI_TRANS_COLOR     3//to make it transparent.
#define  PASSWD_GUI_BKCOLOR         SBGCOLOR
#define  PASSWD_GUI_MSG_BGCOLOR     0
#define  PASSWD_SELECTED_COLOR      SANTIBGCOLOR
#define  PASSWD_UNSELECTED_COLOR    2//10//black color  I dont't know why change 2 (white )to black ?????

#define  BUTTON_UP                  0
#define  BUTTON_DOWN                1

//GUI state: 5 state
#define NO_GUI_STATE            0//not in GUI state.
#define INPUT_OLD_PASSWD_STATE      1
#define INPUT_NEW_PASSWD_STATE      2
#define SHOW_OK_STATE               3
#define INPUT_GRADE_PASSWD_STATE    4
#define SHOW_ERROR_STATE            5//zhaoyanhua add 2004-1-30 11:39

//position define
#define OLD_PASSWD_X            6//unit:char
#define OLD_PASSWD_Y            4//unit:char
#define NEW_PASSWD_X            OLD_PASSWD_X//unit:char
#define NEW_PASSWD_Y            OLD_PASSWD_Y+2//unit:char
#define OK_BUTTON_WORD_X        16
#define OK_BUTTON_WORD_Y        NEW_PASSWD_Y+2
#define PASSWD_MSG_STRING_X  0//message string xstart
#define PASSWD_MSG_STRING_Y  11//message string ystart
//show password box
#define PASSWD_BOX_XLEN         9*16//unit:pixels
#define PASSWD_BOX_YLEN         1*32+8//unit: pixels
#define OLD_PASSWD_BOX_X        280//unit:pixels
#define OLD_PASSWD_BOX_Y        125 //unit:pixels
#define NEW_PASSWD_BOX_X        OLD_PASSWD_BOX_X//unit:pixels
#define NEW_PASSWD_BOX_Y        OLD_PASSWD_BOX_Y+PASSWD_BOX_YLEN+20//unit:pixels

#define PASSWD_BOX_XLEN         9*16//unit:pixels
#define PASSWD_BOX_YLEN         1*32+8//unit: pixels

//show "ok"
#define OK_BUTTON_XLEN          9*10//unit:chars
#define OK_BUTTON_YLEN          1*32+8//unit: pixels

#define OK_BUTTON_X             (OLD_PASSWD_BOX_X-(OK_BUTTON_XLEN/2))//unit:chars
#define OK_BUTTON_Y             NEW_PASSWD_BOX_Y + PASSWD_BOX_YLEN+40-10//unit:chars

void setup_PasswdGUIRefresh(int state);
void setup_ShowPasswdGUI(void);
#endif//SETUP_PASSWORD_GUI

#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 11:49
//NOTE:
//these color is in SETUP_COLOR_TYPE2
//if you use other type, please change color yourself.
#define  VIDEO_GUI_TRANS_COLOR   3//to make it transparent.
#define  VIDEO_GUI_BKCOLOR       SBGCOLOR
#define  VIDEO_GUI_MSG_BGCOLOR   0

int GetVideoSetValue(int id);
void setup_VideoItemValue(int ItemIndex,int fontColor,int bgColor);
void setup_ShowVideoGUI(int id);
void setup_CookVideoGUIString(int id);
#endif//end VIDEO_SETUP_NEW_GUI

#ifdef SELECT_MEDIA_IN_SETUPMENU    //Maoyong 2004-8-9 16:50 for CARD_SETUP_TYPE_3 of eastech
#define IsNoPluggedUSB()        ( !(detect_type & USB_DEVICE ) )
#define IsNoPluggedCARD()       ( !(detect_type & SD_CARD_DEVICE ) && !(detect_type & MS_CARD_DEVICE )  && !(detect_type & SMC_CARD_DEVICE) && !(detect_type & CF_CARD_DEVICE)) //zhongshan modified for CF detect 2005-8-31 17:19
#define IsUSBItemDisable(i)     ( IsNoPluggedUSB() && (i == (USB_ITEM + 2))  )
#define IsCARDItemDisable(i)    ( IsNoPluggedCARD() && (i == (CARD_ITEM + 2)) )
#ifndef DVD_SETUP_REENG     //denghg add  for  DVD_SETUP_REEN  2005-2-15 10:01
#define IsSetupMediaItemDisable(i) ( (page == SYSPAGE) && (index_y == 0) && (IsUSBItemDisable(i) || IsCARDItemDisable(i)) )
#else
#define IsSetupMediaItemDisable()  (((itemID==STR_OS_MEDIA_USB)&&IsNoPluggedUSB())||((itemID==STR_OS_MEDIA_CARD)&&IsNoPluggedCARD()))
#define IsSetupMediaItemDisableSel() ((IsNoPluggedUSB()&&setup_item[setup_pos[1]][setup_pos[2]][setup_pos[SETUP_ML3]]==STR_OS_MEDIA_USB)||(IsNoPluggedCARD()&&setup_item[setup_pos[1]][setup_pos[2]][setup_pos[SETUP_ML3]]==STR_OS_MEDIA_CARD))
#endif                  //DENGHG  end DVD_SETUP_REENG 2005-2-15 10:02
#endif


#ifdef SUPPORT_FUNCTION_MENU
#include "setup_plus_def.h"
#endif
#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-23 9:56  
#include "setup_def_SFM.h"
#elif  defined(SOFT_MENU_REENG)//chenzhao 20050520
#include "setup_def_sfm_reeng.h"
#endif

