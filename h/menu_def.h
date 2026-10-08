/*--------------------------------------------------------------------------
|  File Name   : menu_def.h
|
|  Description : This file include just the following as
|
|                 1)  COLOR definition
|                 2)  Button Definition
|  
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	20040227        zhaoyanhua      creating
|
*/

#ifndef MENU_DEF_H
#define MENU_DEF_H



//--------------MENU------------------------------------------
//HL position
#define PARENT_MENU   			0
#define SUB_MENU				1

//string coordinate
//x: i-th English character with 16 pixel
//y: j-th line with SETUP_BUTTON_HEIGHT pixel
#define MENU_XSTART       		1       //string start at x-axis
#define MENU_YSTART       		1       //string start at y-axis
#define SUBMENU_XSTART        	17
#define SUBMENU_YSTART			2
#define MENU_BTN_XLEN			14

//unit: pixels
#define NORMAL_BUTTON_YLEN		40
#define BUTTON_Y_DIFF			44 //distance between prev button and next button

//MENU Color
#define GRAY_WHITE				9
#define YELLOW_GREEN			12
#define BLACK					15
#define BRIGHT_BLUE				12
#define GRAY					13
#define WHITE					14
#define RED 				    11
#define BLUE                    11
#define BRIGHT_YELLOW			10


//--------------BUTTON-----------------------------------------
//Button state
#define BUTTON_UNSELECTED		0
#define BUTTON_SELECTED 		1
#define BUTTON_TRANS			2
#define BUTTON_RESUME_NORMAL	4


//Button color
#define BTN_SELECTED_COLOR		YELLOW_GREEN
#define BTN_UNSELECTED_COLOR	GRAY
#define BTN_TRANS_COLOR			0
#define FONT_SEL_COLOR			BLACK
#define FONT_UNSEL_COLOR		WHITE

//RATINE GUI color
#define GRADE_SEL_COLOR			YELLOW_GREEN
#define GRADE_UNSEL_COLOR		BRIGHT_YELLOW

//Button type
//for PATH_BUTTON
#define BLANK_BUTTON            0//button without any icon
#define SUB_BUTTON 				1//only has sub dir with left arrow
#define PARENT_BUTTON			2//only has the parent dir with right arrow
#define PARENT_AND_SUB_BUTTON	3//both parent and sub dir. with left and right arrow at the same time
#define RADIO_BUTTON            4//button with radio icon
#define CHECKBOX_BUTTON         5//button with check box icon


//------------------------for PASSWD GUI----------------------------------------------------
//for background
#define PASSWD_BKRECT_XLEN		(MENU_BTN_XLEN+4)*16+10
#define PASSWD_BKRECT_YLEN		BUTTON_Y_DIFF*3
#define PASSWD_BK_COLOR			GRAY

//for GUI positon
//for new password GUI
#define NEW_PASSWDGUI_XSTART	(SUBMENU_XSTART+1)*16 
#define NEW_PASSWDGUI_YSTART	(MENU_YSTART+1)*BUTTON_Y_DIFF-10 
//for Check passwd GUI
#define CHK_PASSWDGUI_XSTART 	 NEW_PASSWDGUI_XSTART
#define CHK_PASSWDGUI_YSTART 	 NEW_PASSWDGUI_YSTART
//for valid passwd GUI
#define CONFIRM_PASSWDGUI_XSTART	 NEW_PASSWDGUI_XSTART
#define CONFIRM_PASSWDGUI_YSTART	 NEW_PASSWDGUI_YSTART+PASSWD_BKRECT_YLEN


//for draw button(unit : pixels)
#define PASSWD_BTN_XLEN			36
#define PASSWD_BTN_DIFF			40// distance between xstart of two button
#define PASSWD_BTN_YLEN			36					 

//#define PASSWD_BTN1_X			PASSWD_BKRECT_X + 4  //first button xstart
//#define PASSWD_BTN1_Y			(MENU_YSTART+2)*40				  //first button ystart
//OK button xstart
//#define PASSWD_BTNOK_X			PASSWD_BTN1_X + PASSWD_BTN_DIFF*4 + 8

//show string (Unit: char)
//#define PASSWD_NUM1_X			PASSWD_BTN1_X/16+3 //string xstart draw in the first button. 
//#define PASSWD_NUM1_Y			(3+1)//PASSWD_BTN1_Y/PASSWD_BTN_YLEN
#define PASSWD_NUM_DIFF			PASSWD_BTN_DIFF/16//distance between two string	
//string "OK" xstart
#define PASSWD_OK_X				SUBMENU_XSTART+14//PASSWD_BTNOK_X	/16+4

//show  title prompt
#define PASSWD_TITLE_X			SUBMENU_XSTART+3
#define PASSWD_TITLE_Y			2


//-----------------------------------------------------------------------------------
//other define
#define PASSWD_BTN0_INDEX		0
#define PASSWD_BTN1_INDEX		1
#define PASSWD_BTN2_INDEX		2
#define PASSWD_BTN3_INDEX		3
#define PASSWD_BTNOK_INDEX		4

#define PASSWD_NUM_FLAG			1
#define PASSWD_NONE_FLAG		0
#define PASSWD_HL_FLAG 			2
#define PASSWD_OK_FLAG			3

//GUI state
#define NONE_STATE				0
#define INPUT_NEW_PASSWD_STATE	1
#define NEWPASSWD_ERR_STATE		2
#define CHKPASSWD_ERR_STATE		3
#define INPUT_CHK_PASSWD_STATE 	4
#define CONFIRM_NEW_PASSWD_STATE 	5
#define GRADE_STATE			6
#define PSCAN_STATE                 7
 
#define GUI_REFRESH				1
#define GUI_UNREFRESH			0
 
#define PLAYER_LOCK				0
#define PLAYER_UNLOCK			1

#define HL_TRUE					1
#define NO_HL					0

//for GRADE GUI
#define GRADE_RECT_XSTART		(SUBMENU_XSTART+ 15)*16
#define GRADE_RECT_YSTART		(SUBMENU_YSTART+1)*16-10
#define GRADE_RECT_XLEN			36
#define GRADE_RECT_STEP			32
#define GRADE_RECT_YLEN			8*GRADE_RECT_STEP+16

#define GRADE_UP				0
#define GRADE_DOWN				1
#endif//ifdef MENU_DEF_H






