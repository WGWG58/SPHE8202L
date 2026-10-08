#include "user_init.h"
#include "global.h"
#include "osd.h"
#include "func.h"
#include "navdata.h"
#include "kernel.h"
#include "vpp.h"
#include "user_if.h"
#include "dsp3_if.h"
#include "cchar.h"
#include "ircmd.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
#include "tvif.h"
#include "memmap.h"
#include "stdlib.h"
#include "kinf.h"

#include "setup_def.h"
#include "one_key_pass.h"
extern UINT8 setup_sel[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM];
extern const UINT8 setup_item[MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE][MAX_PAGE_ITEM][MAX_ITEM_SEL];
#include "setup_page.h"

extern	UINT8	setup_page;
extern 	UINT8	setup_id __attribute__((unused));
extern  UINT8   setup_sel_item;

#define	page	setup_page
#define	id	setup_id
#define sel     setup_sel_item

extern BYTE    passwdGUI_state;//record the current state in password GUI
extern BYTE    index_y;          //item index for 1st-level page, 2nd-level page
extern BYTE    index_y2;         //item index for 3rd-level page
extern BYTE    index_y_start;
extern BYTE    index_y2_start;
extern BYTE    submenuStart;
extern BYTE    setupLevel;       //0:main menu, 1:sub-menu, 2:selection-menu(menu of sub-menu)
extern BYTE    setupItemNum[];



#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         

//#ifdef BBK_NEW_SETUP//zhaoyanhua add 03-11-7 16:03
/*
 * Show main page.
 */
void ShowSetupMainPage()
{
	const char   *str;
	int fontColor = 0;
	int bgColor = 0;
	
	fontColor = 6;
	bgColor = 0;
	SetOsdCol(1,1,SETUP_HL_COLOR,0xa346ffff);
	//clear rect to show correctly.

	osd_draw_region_rect(ONE_KEY_PASS_X, ONE_KEY_PASS_Y, 20*24, 14*24,0, 1);
		
	switch(index_x)
	{
	 	case ONE_KEY_PASS_X:
			draw_setup_Btn_HL( 1, ONE_KEY_PASS_X*11, ONE_KEY_PASS_Y*4, 8* 24, 1*32,4,SETUP_HL_COLOR);	
			break;
		case SETUP_X:
		    draw_setup_Btn_HL( 1,SETUP_X*14+28, SETUP_Y*4, 8* 24, 1*32,4,SETUP_HL_COLOR);
			break;
		case EXIT_SETUP_MENU_X:
		    draw_setup_Btn_HL( 1,EXIT_SETUP_MENU_X*14+32, EXIT_SETUP_MENU_Y*4, 9* 24, 1*32,4,SETUP_HL_COLOR);		
			break;	
	}
	

	str = _OsdMessegeFont1[osd_font_mode][STR_OS_ONEKEY_SETUP];	
	osd_DrawRegionString(ONE_KEY_PASS_X, ONE_KEY_PASS_Y, str, fontColor,bgColor, 1);
	
	str = _OsdMessegeFont1[osd_font_mode][STR_OS_PROFESSION_SETUP];	
	osd_DrawRegionString(SETUP_X+1, SETUP_Y, str, fontColor,bgColor, 1);
	
	str = _OsdMessegeFont1[osd_font_mode][STR_OS_EXIT_MENU];	
	osd_DrawRegionString(EXIT_SETUP_MENU_X+2, EXIT_SETUP_MENU_Y, str, fontColor,bgColor, 1);
}

/*
**FUNC : draw a rect border to show which button is select.
**
** zhaoyanhua 
** Date: 03-11-7 15:00
*/
void draw_setup_Btn_HL(BYTE r,UINT32 xStart, UINT32 yStart,UINT32 xLen,UINT32 yLen, int LineWidth,BYTE color)
{
	//top line
	osd_draw_hline_region(xStart, xStart+xLen, yStart, color,LineWidth, r);
	//bottom Line
	osd_draw_hline_region(xStart, xStart+xLen, yStart+yLen-LineWidth, color,LineWidth, r);
	//left line
	osd_draw_vline_region(xStart, yStart, yStart+yLen, color,LineWidth, r);
	//right line
	osd_draw_vline_region(xStart+xLen-LineWidth, yStart, yStart+yLen, color,LineWidth, r);
}

/*
 * show onekey setup page
 */
void ShowOneKeyPassPage()
{
	osd_init_setup();  
    index_y=0;
    index_y_start=0;
    setupItemNum[1]= MAX_PAGE_ITEM;	// ALAN, 2003/9/9 03:32PM, to initial setupItemNum
    setupLevel=0;	// alan
	page = ONEKEYPASSPAGE;
	ShowSetupPage(2);
}

/*
 * show main
 */
void ShowProfessionalSetup()
{
	osd_init_setup();
	page = 0;
    index_y=0;
    index_y_start=0;
    setupItemNum[1]=MAX_PAGE_ITEM;	// ALAN, 2003/9/9 03:32PM, to initial setupItemNum

    setupLevel=0;	// alan
    ShowSetupPage(2);
}

/*
 *   get sel ITEM of ONEKEYPASSPAGE
 *   to make the ONEKEYPASSPAGE has the same change with special SETUP PAGE 
 */
int GetOneKeyPageSel(int index_y)
{
	int sel_item ;
	
	switch(index_y)
	{
		case 0: // audio output(MULTISPKPAGE)
			sel_item=SETUP_SPK_DOWNMIX;
			break;
		case 1:// TV format(SYSPAGE)
			sel_item = SETUP_TV_FORMAT;
			break;
		default:
			sel_item = 2;//DEFAULT VALUE ITEM
	}	
	return sel_item;
}

#endif//  end for bbk's new setup

#ifdef VIDEO_SETUP_NEW_GUI
/*
 *Function Description:
 *    get the video current value to show in SETUP VIDEO PAGE 
 * 
 *  INPUT:
 *    id ---> video osd string id type
 *    
 *  RETURN :
 *    video value.
 *  
 * zhaoyanhua 2004-1-7 17:01
 */

int GetVideoSetValue(int str_id)
{
	int iValue = 0;

	switch (str_id)
	{
		case STR_OS_BRIGHTNESS:
			iValue = SETUP_BRIGHTNESS-2;
			break;
		case STR_OS_CONTRAST:
			iValue = SETUP_CONTRAST-2;
			break;
		case STR_OS_HUE:
			iValue = SETUP_HUE-2-6;//must do like this!
			//printf("#####  ---setup_hue --%d--\n",iValue);
			break;
		case STR_OS_SATURATION:
			iValue = SETUP_SATURATION-2;
			break;
#ifdef DIP_CFG_ENABLE
		case STR_OS_DEINTLC:
			iValue = SETUP_DE_INTERLACE-2;
			break;
#endif		
	default:break;	
	}
	//printf("###### ----in GetVideoSetValue %d---\n",iValue);
	return iValue;

}
/*
 *Function Description:
 *    Draw Video Item(Brightness/hue/contrast ,ect) value in SETUP OSD.
 *   
 * INPUT:
 *    ItemIndex ---> y_postion in level 1
 *    
 * zhaoyanhua 2004-1-7 19:22
 */
void setup_VideoItemValue(int ItemIndex,int fontColor,int bgColor)
{
	BYTE buf[4];	
		
	//draw ">" between sub-mean and it's corresponding selection area
	//osd_DrawString(SETUP_SUB_XSTART-1, ItemIndex+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
	id = setup_item[page][ItemIndex][1];
	psprintf(buf,"%02d",GetVideoSetValue(id));	
	//str = buf;
	//str = buf;
	osd_DrawString(SETUP_SUB_XSTART+1, ItemIndex+SETUP_MENU_YSTART+1, buf, fontColor, bgColor); 
}

/*
 * Funciton Description:
 *   
 *    draw GUI to adjust video value 
 * 
 * INPUT:
 *    id : video type :brightness/contrast/hue,ect
 *
 */
void setup_ShowVideoGUI(int id)
{
    const char   *str;
    
#define MSG_STRING_X  0//message string xstart
#define MSG_STRING_Y  11//message string ystart

	int GUI_x= 0,GUI_y= 0,GUI_h= 0,GUI_w = 0;//xstart/ystart/ylen/xlen
	int GUI_Backx = 0,GUI_Backy = 0, GUI_Backh= 0,GUI_Backw = 0;//background Rect xstart/ystart/ylen/xlen
	int GUI_Msgx= 0,GUI_Msgy= 0, GUI_Msgw =0, GUI_Msgh = 0;

	SetOsdCol(0,0,VIDEO_GUI_TRANS_COLOR,0x1e1e1e00);
	GUI_Backx = 0;
	GUI_Backy = SETUP_BUTTON_HEIGHT+24+40 - 2;
	//GUI_Backh = 9*SETUP_BUTTON_HEIGHT;
	GUI_Backh = 10*SETUP_BUTTON_HEIGHT-12;
	GUI_Backw = SETUP_MAX_WIDTH*15+40-4;
	//GUI_Backw = SETUP_MAX_WIDTH*15+40;
	//osd_draw_rect(20, SETUP_BUTTON_HEIGHT+24+40, (SETUP_MAX_WIDTH*15), 10*SETUP_BUTTON_HEIGHT-12, 10);
	//osd_draw_rect(0, SETUP_BUTTON_HEIGHT+24+40, (SETUP_MAX_WIDTH*15+40), 10*SETUP_BUTTON_HEIGHT-12, VIDEO_GUI_TRANS_COLOR);		

	//draw background 
	//draw a big transparent rect .
	osd_draw_rect(GUI_Backx, GUI_Backy, GUI_Backw, GUI_Backh, VIDEO_GUI_TRANS_COLOR);
	
	//draw operation message rect
	GUI_Msgh = 70;
	GUI_Msgw = GUI_Backw;
	GUI_Msgx = GUI_Backx;
	GUI_Msgy = GUI_Backy+GUI_Backh-GUI_Msgh;
	osd_draw_rect(GUI_Msgx, GUI_Msgy, GUI_Msgw, GUI_Msgh, VIDEO_GUI_MSG_BGCOLOR);
	
	//draw video GUI
	GUI_h = (GUI_Backh - GUI_Msgh)/2 ;//GUI height
	GUI_w = GUI_Backw/2+120+70;//GUI width
	GUI_x = GUI_Backx + (GUI_Backw - GUI_w)/2;//GUI xstart
	GUI_y = GUI_Backy + (GUI_Backh - GUI_h - GUI_Msgh)/2; //GUI ystart

	osd_draw_rect(GUI_x, GUI_y, GUI_w, GUI_h, SBGCOLOR);
	//draw rect frame
	//I don't know why in SETUP_COLOR_TYPE2, SBLACKCOLOR -> WHITE
	//                                       SWHITECOLOR -> BLACK ?
	osd_DrawLine(GUI_x-2, GUI_y-1, GUI_x-2, GUI_y-1+GUI_h,SFONTCOLOR, 2);//left line
	osd_DrawLine(GUI_x, GUI_y-2, GUI_x+GUI_w, GUI_y-2,SFONTCOLOR, 2);//top line
	osd_DrawLine(GUI_x-1, GUI_y-2+GUI_h, GUI_x+1+GUI_w, GUI_y-2+GUI_h,SWHITECOLOR, 2);//bottom line
	osd_DrawLine(GUI_x-1+GUI_w, GUI_y-2, GUI_x-1+GUI_w, GUI_y+GUI_h,SWHITECOLOR, 2);//right line
	//show id string
	setup_CookVideoGUIString(id);
	//show operation Message about this id
	str = _OsdMessegeFont1[osd_font_mode][STR_OS_ENTER_RETURN];
	osd_DrawString(MSG_STRING_X, MSG_STRING_Y, str, SFONTCOLOR, VIDEO_GUI_MSG_BGCOLOR);///13	
	//osd_DrawString(MSG_STRING_X, MSG_STRING_Y, "ENTER SELECT TO RETURN MAIN SETUP",SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13
	
	
}

/*
 * Funciton Discription:
 *  when LEFT/RIGHT,show corresponding GUI and value.
 *
 * zhaoyanhua 2004-1-8 16:10
 */
void setup_CookVideoGUIString(int id)
{
#define  STRING_X  4//6
#define  STRING_Y  6
    int font_id = 0;
	int Level= 0;
	int totalLevel = 0;

	switch (id)
	{
		case STR_OS_BRIGHTNESS:
			Level = SETUP_BRIGHTNESS-2;
			totalLevel = 13;
			font_id = VIDEO_BIGHT_ID;
			break;
		case STR_OS_CONTRAST:
			Level = SETUP_CONTRAST-2;
			totalLevel = 13;
			font_id = VIDEO_CONTRAST_ID;
			break;
		case STR_OS_HUE:
			Level = SETUP_HUE-2;
			totalLevel = 13;
			font_id = VIDEO_HUE_ID;
			break;
		case STR_OS_SATURATION:
			Level = SETUP_SATURATION-2;
			totalLevel = 13;
			font_id = VIDEO_SATURATION_ID;
			break;
#ifdef DIP_CFG_ENABLE
		case STR_OS_DEINTLC:
			Level = SETUP_DE_INTERLACE-2;
			totalLevel = 7;
			font_id = VIDEO_DEINTERLACE_ID;
			break;
#endif		
	default:break;	
	}
	
	show_level(font_id, Level, totalLevel);//write message to "linebuf".
	osd_DrawString(STRING_X, STRING_Y, linebuf,STITLECOLOR, SBGCOLOR);
	
}
#endif//VIDEO_SETUP_NEW_GUI

#ifdef SETUP_PASSWORD_GUI //zhaoyanhua add 2004-1-14 16:54
/*
 * Function Description:
 *    in SETUP  show password GUI
 *
 */
void setup_ShowPasswdGUI(void)
{
    const char   *str;
	int GUI_x= 0,GUI_y= 0,GUI_h= 0,GUI_w = 0;//xstart/ystart/ylen/xlen
	int GUI_Backx = 0,GUI_Backy = 0, GUI_Backh= 0,GUI_Backw = 0;//background Rect xstart/ystart/ylen/xlen
	int GUI_Msgx= 0,GUI_Msgy= 0, GUI_Msgw =0, GUI_Msgh = 0;

	SetOsdCol(0,0,PASSWD_GUI_TRANS_COLOR,0x1e1e1e00);
	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
	
	GUI_Backx = 0;
	GUI_Backy = SETUP_BUTTON_HEIGHT+24+40-2;
	GUI_Backh = 10*SETUP_BUTTON_HEIGHT-12;
	GUI_Backw = SETUP_MAX_WIDTH*15+40-4;
	//draw background 
	//draw a big transparent rect .
	osd_draw_rect(GUI_Backx, GUI_Backy, GUI_Backw, GUI_Backh, PASSWD_GUI_TRANS_COLOR);

	//draw operation message rect
	GUI_Msgh = 70;
	GUI_Msgw = GUI_Backw;
	GUI_Msgx = GUI_Backx;
	GUI_Msgy = GUI_Backy+GUI_Backh-GUI_Msgh;
	osd_draw_rect(GUI_Msgx, GUI_Msgy, GUI_Msgw, GUI_Msgh, PASSWD_GUI_MSG_BGCOLOR);
	
	//draw video GUI
	GUI_h = (GUI_Backh - GUI_Msgh)/2+ 80;//+100 ;//GUI height
	GUI_w = GUI_Backw/2+120;//GUI width
	GUI_x = GUI_Backx + (GUI_Backw - GUI_w)/2;//GUI xstart
	GUI_y = GUI_Backy + (GUI_Backh - GUI_h - GUI_Msgh)/2; //GUI ystart
	
	osd_draw_rect(GUI_x, GUI_y, GUI_w, GUI_h, SBGCOLOR);
	//draw rect frame
	//I don't know why in SETUP_COLOR_TYPE2, SBLACKCOLOR -> WHITE
	//                                       SWHITECOLOR -> BLACK ?
	osd_DrawLine(GUI_x-2, GUI_y-1, GUI_x-2, GUI_y-1+GUI_h,SFONTCOLOR, 2);//left line
	osd_DrawLine(GUI_x, GUI_y-2, GUI_x+GUI_w, GUI_y-2,SFONTCOLOR, 2);//top line
	osd_DrawLine(GUI_x-1, GUI_y-2+GUI_h, GUI_x+1+GUI_w, GUI_y-2+GUI_h,SWHITECOLOR, 2);//bottom line
	osd_DrawLine(GUI_x-1+GUI_w, GUI_y-2, GUI_x-1+GUI_w, GUI_y+GUI_h,SWHITECOLOR, 2);//right line

	//nwe passwd
	str = _OsdMessegeFont1[osd_font_mode][STR_OS_OLD_PASSWD];
	osd_DrawString(OLD_PASSWD_X, OLD_PASSWD_Y, str, STITLECOLOR, SBGCOLOR);///13	
	//osd_DrawString(OLD_PASSWD_X, OLD_PASSWD_Y, "OLD PASSWD:",STITLECOLOR, SBGCOLOR);
	
	if(passwdGUI_state != INPUT_GRADE_PASSWD_STATE)//grade passwd not show new passwd
	{   
	    str = _OsdMessegeFont1[osd_font_mode][STR_OS_NEW_PASSWD];
	    osd_DrawString(NEW_PASSWD_X, NEW_PASSWD_Y, str, STITLECOLOR, SBGCOLOR);///13	
		//osd_DrawString(NEW_PASSWD_X, NEW_PASSWD_Y, "NEW PASSWD:",STITLECOLOR, SBGCOLOR);
    }
	setup_PasswdGUIRefresh(passwdGUI_state);

}
/*
 * when input password refresh PASSWORD in time
 */
void setup_PasswdGUIRefresh(int state)
{
    const char   *str;
	int oldpswd_bgcolor = 0;
	int newpswd_bgcolor = 0;
	int ok_bgcolor = 0,bDown = 0,left_top_color = 0,right_bottom_color = 0;
		
	switch(state)
	{
		case INPUT_OLD_PASSWD_STATE:
			oldpswd_bgcolor = PASSWD_SELECTED_COLOR;
			newpswd_bgcolor = PASSWD_UNSELECTED_COLOR;
			ok_bgcolor = PASSWD_UNSELECTED_COLOR;;
			bDown = BUTTON_DOWN;
			//show operation Message about this state
			//"please input old password"
	        str = _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWD_SENTENCE1];
	        osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y, str, SFONTCOLOR, VIDEO_GUI_MSG_BGCOLOR);///13	
			//osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y	, "PLEASE INPUT OLD PASSWD",SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13		
			break;
		case INPUT_NEW_PASSWD_STATE:
			oldpswd_bgcolor = PASSWD_SELECTED_COLOR;
			newpswd_bgcolor = PASSWD_SELECTED_COLOR;
			ok_bgcolor = PASSWD_UNSELECTED_COLOR;
			bDown = BUTTON_DOWN;
			//show operation Message about this state
			//"please input new password"
			osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y	, "                       ",SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13		
	        str = _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWD_SENTENCE2];
	        osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y, str, SFONTCOLOR, VIDEO_GUI_MSG_BGCOLOR);///13	
			//osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y	, "PLEASE INPUT NEW PASSWD",SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13		

			break;
		case INPUT_GRADE_PASSWD_STATE:			
			oldpswd_bgcolor = PASSWD_SELECTED_COLOR;
			ok_bgcolor = PASSWD_UNSELECTED_COLOR;;
			bDown = BUTTON_DOWN;
			//show operation Message about this state
			//"please input old password"
        	str = _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWD_SENTENCE1];
        	osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y, str, SFONTCOLOR, VIDEO_GUI_MSG_BGCOLOR);///13	
			//osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y	, "PLEASE INPUT OLD PASSWD",SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13		
			break;
		case SHOW_OK_STATE:
			oldpswd_bgcolor = PASSWD_UNSELECTED_COLOR;
			newpswd_bgcolor = PASSWD_UNSELECTED_COLOR;
			ok_bgcolor = PASSWD_SELECTED_COLOR;;
			bDown = BUTTON_UP;
			//show operation Message about this state
			//"enter select return to main setup"
	        str = _OsdMessegeFont1[osd_font_mode][STR_OS_ENTER_RETURN];
	        osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y, str, SFONTCOLOR, VIDEO_GUI_MSG_BGCOLOR);///13	
			//osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y	, "ENTER SELECT TO RETURN MAIN SETUP",SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13		
			break;
		case SHOW_ERROR_STATE://when old password error, show error message. zhaoyanhua add 2004-1-30 11:36			
			oldpswd_bgcolor = PASSWD_SELECTED_COLOR;
			newpswd_bgcolor = PASSWD_UNSELECTED_COLOR;
			ok_bgcolor = PASSWD_UNSELECTED_COLOR;;
			bDown = BUTTON_DOWN;
			//show operation Message about this state
			//"passwd error! please input again"
			osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y	, "                       ",SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13		
            str = _OsdMessegeFont1[osd_font_mode][STR_OS_PASSWD_ERROR];
			osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y	, str,SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13		
			//osd_DrawString(PASSWD_MSG_STRING_X, PASSWD_MSG_STRING_Y	, "PASSWD ERROR. PLEASE INPUT AGAIN",SFONTCOLOR,VIDEO_GUI_MSG_BGCOLOR);///13		
			break;
					
		default:
			break;
	
	}
	//old password box
	if(passwdGUI_state != INPUT_NEW_PASSWD_STATE)//when input NEW PASSWD, not redraw OLD PASSWORD BOX
	osd_draw_rect(OLD_PASSWD_BOX_X,OLD_PASSWD_BOX_Y,PASSWD_BOX_XLEN,PASSWD_BOX_YLEN, oldpswd_bgcolor);
	
	//new password word box
	if ( !((page==SYSPAGE) && (index_y==GRADEITEM)) ) ////grade passwd not show new passwd
		osd_draw_rect(NEW_PASSWD_BOX_X,NEW_PASSWD_BOX_Y,PASSWD_BOX_XLEN,PASSWD_BOX_YLEN, newpswd_bgcolor);	
	//OK button
	osd_draw_rect(OK_BUTTON_X,OK_BUTTON_Y,OK_BUTTON_XLEN,OK_BUTTON_YLEN,ok_bgcolor);
	if(bDown)
	{
		left_top_color = SWHITECOLOR; //in fact it is black
		right_bottom_color =SFONTCOLOR; 
	}
	else
	{
		left_top_color = SFONTCOLOR;
		right_bottom_color= SWHITECOLOR;//in fact it is black
	}
	osd_DrawLine(OK_BUTTON_X, OK_BUTTON_Y, OK_BUTTON_X, OK_BUTTON_Y+OK_BUTTON_YLEN,left_top_color, 1);//left line
	osd_DrawLine(OK_BUTTON_X, OK_BUTTON_Y, OK_BUTTON_X+OK_BUTTON_XLEN, OK_BUTTON_Y,left_top_color, 1);//top line
	osd_DrawLine(OK_BUTTON_X, OK_BUTTON_Y-1+OK_BUTTON_YLEN, OK_BUTTON_X+OK_BUTTON_XLEN, OK_BUTTON_Y+OK_BUTTON_YLEN,right_bottom_color, 1);//bottom line
	osd_DrawLine(OK_BUTTON_X-1+OK_BUTTON_XLEN, OK_BUTTON_Y, OK_BUTTON_X+OK_BUTTON_XLEN, OK_BUTTON_Y+OK_BUTTON_YLEN,right_bottom_color, 1);//right line
	osd_DrawString(OK_BUTTON_WORD_X, OK_BUTTON_WORD_Y, "OK",STITLECOLOR, ok_bgcolor);
	
}


#endif//SETUP_PASSWORD_GUI 


