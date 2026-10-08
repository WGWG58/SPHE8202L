/***************************************************************
 *
 * File Name :  periphGUI.c
 * 
 * Discription:
 *     Provide an interface for operations related with peripheral
 *     Especially for UDisk and CF card 
 *
 * Creator:  liweihua
 * Date   :  2003-10-29 20:18
 * Update :  sunzhh 2004-11-15 
 * modify :  linrc  20041204 rename Card*->FS*
 ***************************************************************/

#include "user_init.h"
#include "global.h"
#include "memmap0.h"
#include "ircmd.h"
#include "types.h"
#include "memcfg.h"
#include "framebuf.h"
#include "memmap.h"
#include "osd.h"
#include "fsNav.h"

#define NEW_INPUT_MENU //lijd 2004-12-20 16:15 

#ifdef SPHE8202_ALL_TYPE_CARD_WRITE
BYTE card_browse_sign = 1;
#endif

#if defined(FAT_Write_UI)||defined(CF_CARD_WRITE)
#include "cardfs.h"
//extern int CardSchedule(BYTE copy_mode);
extern int FSSchedule(BYTE copy_mode);
extern int CARDIsPlugIn(void);
extern CARD_INFO   cardP;
BYTE read_card_sign=0;
BYTE flag_cd2cf=0, flag_cf2cd=0;
BYTE InfoGui_flag=0;
int remain_capacity;
extern UINT32	zeroFAT_cnt;

#ifdef FAT_Write_File_System  //added by wangwei,2004-11-15 13:29
extern void StorageGetCapacityInfo(void);
extern UINT32 uiTotalCapacity;
extern UINT32 uiUsedCapacity;
extern UINT32 uiRemainCapacity;
#endif //FAT_WRITE_FILE_SYSTEM

#ifdef STORAGE_WRITE_GUI
    #ifdef CARD_SETUP_TYPE_3  
BYTE 	*stringMediaswitch[]={" ","UDISK","CF CARD","SD/MMC","MS/MS PRO","SMC"};
#else 
BYTE 	*stringMediaswitch[]={" ","UDISK","SD/MMC","MS/MS PRO"};
#endif
#elif defined(CARD_WRITE_GUI)
    #if defined(CARD_SETUP_TYPE_3)   
    BYTE 	*stringMediaswitch[]={" ","CF CARD","SD/MMC","MS/MS PRO","SMC"};
    #else 
    BYTE 	*stringMediaswitch[]={" ","SD/MMC","MS/MS PRO"};
    #endif
#endif

#ifdef STORAGE_WRITE_GUI
BYTE 	*string[]={"NO UDISK/CARD","CDROM TO UDISK","UDISK TO CDROM","COPY FILE TO","DELETE FILE","FORMAT","RENAME FILE","CAPACITY INFO"};
#elif defined(CF_CARD_WRITE)||defined(CARD_WRITE_GUI)
BYTE 	*string[]={"NO CARD","CDROM TO CARD","CARD TO CDROM","COPY THE FILE","DELETE FILE","FORMAT","RENAME FILE","CAPACITY INFO"};
#else
BYTE 	*string[]={"NO UDISK","CDROM TO UDISK","UDISK TO CDROM","COPY FILE TO","DELETE FILE","FORMAT","RENAME FILE","CAPACITY INFO"};
#endif

#define OSD_FONT_HEIGHT 24
#define	FUNCTION_REGION	3
#define	MESSAGE_REGION	2

#define	COLOR_WHITE	        2
#define	COLOR_GRAY		    3
#define	COLOR_GRAYWHITE     14
#define	COLOR_YELLOW	    7
#define	COLOR_YELLOWGREEN   9
#define	COLOR_DBLUE		    4
#define COLOR_LBLUE         0
#define COLOR_GREEN         13

#define	BUTTON_UP		0
#define	BUTTON_DOWN	    1
#define	BUTTON_LEN		18

#define	NO_PERIPHRAL	0
#define	BUTTON_CD2P		1
#define	BUTTON_P2CD		2
#define	BUTTON_COPY		3
#define	BUTTON_DELETE	4
#define	BUTTON_FORMAT	5
#define	BUTTON_RENAME	6
#define	BUTTON_CAPACITY 7

#ifdef FAT_Write_UI
BYTE Switch_flag=0;
BYTE SwitchID;
BYTE Select_Media;
#define Media_UDISK     1
#define	Media_CF		2
#define	Media_SD		3
#define	Media_MS		4
#define	Media_SMC		5
#ifdef CARD_SETUP_TYPE_3
#define	BUTTON_UDISK	1
#define	BUTTON_CF		2
#define	BUTTON_SD		3
#define	BUTTON_MS		4
#define	BUTTON_SMC		5
#else//if defined(CARD_SETUP_TYPE_4)
#define	BUTTON_UDISK	1
#define	BUTTON_SD		2
#define	BUTTON_MS		3
#endif
#endif

#define COPY_ROOTDIR   1   //copy file to root dir
#define COPY_EXISTING   2   //copy file to existing dir
#define COPY_NEWDIR   3   //created new dir and copy file to the new dir

#define	ERROR_MESSAGE	0
#define	PFUN_WRITE	1
#define	PFUN_DELETE	2
#define	PFUN_FORMAT	3
#define	PFUN_RENAME	4
#define	PFUN_COPYING	5
#define	P_SPACEFULL 	6
#define	P_SPACEEMPTY 	7
#define	P_INPUT 	8
#define P_NOMATCH    9
#define P_DIREXISTING	    10//add 2003-12-22

#define 	COPY_ROOTDIR   	1   //copy file to root dir
#define 	COPY_EXSITING   2   //copy file to existing dir
#define 	COPY_NEWDIR   	3   //created new dir and copy file to the new dir

#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 

extern void osd_init_MediaswitchGUI(void);
extern void osd_init_periphGUI(void);
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void osd_draw_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown, BYTE r);
extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);
extern int AVD_SetMediaInterrupt(void);

BYTE sign_PFun=0;
BYTE    *stringcopy[]={" ","ROOT DIR","EXISTING DIR","CREATE DIR"};
BYTE	KeyID;
BYTE	CopyID=0;

BYTE level=0;
BYTE input_flag=0;
BYTE pressnum=10, PressID=5,pressnum_flag=0,xoffset=0;
char *temp;
char getstring[8]={};

/***************************************************************************
 *  Function Name: Set_Button                                              *
 *  Purposes: Only for drawing the function button                         *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void Set_Button(void)
{
	BYTE item;
    if(media_type==MEDIA_CD)
	{
        osd_DrawRegionString(2, BUTTON_CD2P*8+3, string[BUTTON_CD2P], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button
        osd_DrawRegionString(2, BUTTON_P2CD*8+3, string[BUTTON_P2CD], COLOR_GRAY, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button
		osd_DrawRegionString(2, BUTTON_COPY*8+3, string[BUTTON_COPY], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button
		for(item=BUTTON_DELETE; item<=BUTTON_RENAME; item++)//invalidate the latter three
		{
			osd_DrawRegionString(2, item*8+3, string[item], COLOR_GRAY, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button
		}
		osd_DrawRegionString(2, BUTTON_CAPACITY*8+3, string[BUTTON_CAPACITY], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button		
	}
    if(media_type==MEDIA_CARD)
	{
        //for copy gray
        osd_DrawRegionString(2, BUTTON_CD2P*8+3, string[BUTTON_CD2P], COLOR_GRAY, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button
		osd_DrawRegionString(2, BUTTON_COPY*8+3, string[BUTTON_COPY], COLOR_GRAY, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button
        osd_DrawRegionString(2, BUTTON_P2CD*8+3, string[BUTTON_P2CD], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button
    	for(item=BUTTON_DELETE; item<=BUTTON_RENAME; item++)//all six are ok
    	{
    	    osd_DrawRegionString(2, item*8+3, string[item], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button
        }
		osd_DrawRegionString(2, BUTTON_CAPACITY*8+3, string[BUTTON_CAPACITY], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);		//draw string on button		        
    }
}

/***************************************************************************
 *  Function Name: Set_MediaSwitch_Button                                  *
 *  Purposes: Only for drawing the meia button to switch                   *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Create:  sunzhh 2004-11-10                                             *
 **************************************************************************/
#if defined(STORAGE_WRITE_GUI)||defined(CARD_WRITE_GUI)
void Set_MediaSwitch_Button(void)
{ 	  
  		//draw string on button           	    	        
        if(detect_type & USB_DEVICE)   //&&(detect_type & SD_CARD_DEVICE)) 
            osd_DrawRegionString(1, BUTTON_UDISK*8+5, stringMediaswitch[BUTTON_UDISK], COLOR_WHITE, COLOR_GRAYWHITE,3);		//draw string on button        
        else 
            osd_DrawRegionString(1, BUTTON_UDISK*8+5, stringMediaswitch[BUTTON_UDISK], COLOR_GRAY, COLOR_GRAYWHITE,3);		//draw string on button        
        #ifdef CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card. 
        if(detect_type & CF_CARD_DEVICE) 
            osd_DrawRegionString(1, BUTTON_CF*8+5, stringMediaswitch[BUTTON_CF], COLOR_WHITE, COLOR_GRAYWHITE,3);		//draw string on button                       
        else
            osd_DrawRegionString(1, BUTTON_CF*8+5, stringMediaswitch[BUTTON_CF], COLOR_GRAY, COLOR_GRAYWHITE,3);		//draw string on button                       
        #endif
        if(detect_type & SD_CARD_DEVICE) 
            osd_DrawRegionString(1, BUTTON_SD*8+5, stringMediaswitch[BUTTON_SD], COLOR_WHITE, COLOR_GRAYWHITE,3);		//draw string on button        
        else 
            osd_DrawRegionString(1, BUTTON_SD*8+5, stringMediaswitch[BUTTON_SD], COLOR_GRAY, COLOR_GRAYWHITE,3);		//draw string on button        
        if(detect_type & MS_CARD_DEVICE)
            osd_DrawRegionString(1, BUTTON_MS*8+5, stringMediaswitch[BUTTON_MS], COLOR_WHITE, COLOR_GRAYWHITE,3);		//draw string on button        
        else
            osd_DrawRegionString(1, BUTTON_MS*8+5, stringMediaswitch[BUTTON_MS], COLOR_GRAY, COLOR_GRAYWHITE,3);		//draw string on button         
        #ifdef CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card.       
        if(detect_type & SMC_CARD_DEVICE) 
            osd_DrawRegionString(1, BUTTON_SMC*8+5, stringMediaswitch[BUTTON_SMC], COLOR_WHITE, COLOR_GRAYWHITE,3);		//draw string on button        
        else
            osd_DrawRegionString(1, BUTTON_SMC*8+5, stringMediaswitch[BUTTON_SMC], COLOR_GRAY, COLOR_GRAYWHITE,3);		//draw string on button                     
        #endif 
}
#endif        

/***************************************************************************
 *  Function Name: highlight_button                                              *
 *  Purposes: highlight the mainmenu button that will select               *
 *  Arguments: selectID                                                        *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void highlight_button(BYTE selectID)
{
    #if defined(STORAGE_WRITE_GUI)||defined(CARD_WRITE_GUI)
    if(Switch_flag==1)
    {
        Set_MediaSwitch_Button();
	    switch(selectID)
	    {
		    case BUTTON_UDISK:
                osd_DrawRegionString(1, BUTTON_UDISK*8+5, stringMediaswitch[BUTTON_UDISK], COLOR_WHITE, COLOR_YELLOWGREEN,3);		//draw string on button		    
			    break;                
            #ifdef CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card. 
		    case BUTTON_CF:
                osd_DrawRegionString(1, BUTTON_CF*8+5, stringMediaswitch[BUTTON_CF], COLOR_WHITE, COLOR_YELLOWGREEN,3);		//draw string on button	        
			    break;
            #endif
            case BUTTON_SD:
                osd_DrawRegionString(1, BUTTON_SD*8+5, stringMediaswitch[BUTTON_SD], COLOR_WHITE, COLOR_YELLOWGREEN,3);		//draw string on button        
			    break;
            case BUTTON_MS:
                osd_DrawRegionString(1, BUTTON_MS*8+5, stringMediaswitch[BUTTON_MS], COLOR_WHITE, COLOR_YELLOWGREEN,3);		//draw string on button         
			    break;
            #ifdef CARD_SETUP_TYPE_3   //256Pin 16bit Non_share mode All card.       
            case BUTTON_SMC:
                osd_DrawRegionString(1, BUTTON_SMC*8+5, stringMediaswitch[BUTTON_SMC], COLOR_WHITE, COLOR_YELLOWGREEN,3);		//draw string on button        
			    break;
            #endif 
	    }        
    }
    else
    #endif 
    {      
    int y;
	Set_Button();// back to the default color
	switch(selectID)
	{
		case BUTTON_CD2P:
			osd_DrawRegionString(2, BUTTON_CD2P*8+3, string[BUTTON_CD2P], COLOR_WHITE, COLOR_YELLOWGREEN, FUNCTION_REGION); 	//draw string on button
            for(y=0;y<3;y++)
                osd_DrawRegionString(17,(3+y)*8+3,"              ",COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);
			break;
		case BUTTON_P2CD:
			osd_DrawRegionString(2, BUTTON_P2CD*8+3, string[BUTTON_P2CD], COLOR_WHITE, COLOR_YELLOWGREEN, FUNCTION_REGION); 	//draw string on button
            for(y=0;y<3;y++)
                osd_DrawRegionString(17,(3+y)*8+3,"              ",COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);
			break;
		case BUTTON_COPY:
			osd_DrawRegionString(2, BUTTON_COPY*8+3, string[BUTTON_COPY], COLOR_WHITE, COLOR_YELLOWGREEN, FUNCTION_REGION); 	//draw string on button
            for(y=0;y<3;y++)
            {
                osd_DrawRegionString(17,(3+y)*8+3,"--",COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);
                osd_DrawRegionString(19,(3+y)*8+3,stringcopy[y+1],COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);
            }
			break;
		case BUTTON_DELETE:
			osd_DrawRegionString(2, BUTTON_DELETE*8+3, string[BUTTON_DELETE], COLOR_WHITE, COLOR_YELLOWGREEN, FUNCTION_REGION); 	//draw string on button
			break;
		case BUTTON_FORMAT:
			osd_DrawRegionString(2, BUTTON_FORMAT*8+3, string[BUTTON_FORMAT], COLOR_WHITE, COLOR_YELLOWGREEN, FUNCTION_REGION); 	//draw string on button
			break;
		case BUTTON_RENAME:
			osd_DrawRegionString(2, BUTTON_RENAME*8+3, string[BUTTON_RENAME], COLOR_WHITE, COLOR_YELLOWGREEN, FUNCTION_REGION);	//draw string on button
			break;
		case BUTTON_CAPACITY:
			osd_DrawRegionString(2, BUTTON_CAPACITY*8+3, string[BUTTON_CAPACITY], COLOR_WHITE, COLOR_YELLOWGREEN, FUNCTION_REGION);	//draw string on button
                for(y=0;y<3;y++)
                    osd_DrawRegionString(17,(3+y)*8+3,"              ",COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);
			break;	
	}
    }
}

/***************************************************************************
 *  Function Name: highlight_button_all                                              *
 *  Purposes: highlight all the button containing submenu that will select *
 *  Arguments: selectID,  copyID                                                      *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void highlight_button_all(BYTE selectID,BYTE copyID)
{
    if(copyID==0) 
        highlight_button(selectID);
    else 
    {
        highlight_button(selectID);
        osd_DrawRegionString(2, BUTTON_COPY*8+3, string[BUTTON_COPY], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);
        osd_DrawRegionString(19,(2+copyID)*8+3,stringcopy[copyID],COLOR_WHITE, COLOR_YELLOWGREEN, FUNCTION_REGION);
    }
}

/***************************************************************************
 *  Function Name: show_mediaswitch                                        *
 *  Purposes: show the media switch menu                                   *
 *  Descriptions:                                                          * 
 *     If there is two media detected at one time,the menu is showing.     * 
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Create:  sunzhh 2004-11-10                                             *
 **************************************************************************/
#if defined(STORAGE_WRITE_GUI)||defined(CARD_WRITE_GUI)
void show_mediaswitch(void)
{
    Switch_flag=1;
    osd_init_MediaswitchGUI();
    BYTE	*title_str="MEDIA SWITCH";
    osd_draw_region_rect(0, 0, 64*4, 40, COLOR_GREEN, 3);
    osd_DrawRegionString(2, 1, title_str, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);
    SetOsdCol(FUNCTION_REGION, FUNCTION_REGION, 0,__palette4F(192,192, 192, 0xe0));		//draw background of the region
	if(storage_type==0)
	{
		osd_DrawRegionString(8, 1, string[NO_PERIPHRAL], COLOR_DBLUE, COLOR_LBLUE, MESSAGE_REGION); 	//draw string on button
		delay_1ms(2000);
		full_scrn &= (~PERIPHERAL);//for release the IR
		osd_init();
                //if you want not interrupt current play,you can use the followed method//dingzhy
                //psprintf(RegionValStr[REGION1], "USB/CARD NOT FOUND");  
		//PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);    
	}
	else
	{
        Set_MediaSwitch_Button();
        level=1;
        input_flag=0;
        xoffset=0;
        CopyID=0;
        InfoGui_flag=0;
        if(detect_type&USB_DEVICE)
        SwitchID=BUTTON_UDISK;
        #ifdef CARD_SETUP_TYPE_3 
        else if(detect_type&CF_CARD_DEVICE)
        SwitchID=BUTTON_CF;
        #endif
    	highlight_button(SwitchID);        

    }
}
#endif
/***************************************************************************
 *  Function Name: show_switch                                             *
 *  Purposes: show the function switch menu                                *
 *  Arguments: Select_Media                                                        *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void show_switch(BYTE Select_Media)
{
    BYTE i;
    BYTE Select_Media; 

    if(Switch_flag==0) 
    {     
        if(detect_type==USB_DEVICE)
        Select_Media=Media_UDISK;
        else if(detect_type==CF_CARD_DEVICE) 
        Select_Media=Media_CF;
        else if(detect_type==SD_CARD_DEVICE)
        Select_Media=Media_SD;         
        else if(detect_type==MS_CARD_DEVICE)
        Select_Media=Media_MS;             
        else if(detect_type==SMC_CARD_DEVICE) 
        Select_Media=Media_SMC;
    }
    if(Select_Media==Media_UDISK)
    {      
        string[1]="CDROM TO UDISK";
        string[2]="UDISK TO CDROM";       
    }
    else if(Select_Media==Media_CF)      
    {
        string[1]="CDROM TO CF";
        string[2]="CF TO CDROM";
        string[5]="FORMAT CF";
    }
    else if(Select_Media==Media_SD)
    {      
        string[1]="CDROM TO SD/MMC";
        string[2]="SD/MMC TO CDROM";
        string[5]="FORMAT SD/MMC";
    }
    else if(Select_Media==Media_MS) 
    {     
        string[1]="CDROM TO MS/MS PRO";
        string[2]="MS/MS PRO TO CDROM";
        string[5]="FORMAT MS/MS";
    }
    else if(Select_Media==Media_SMC)
    {      
        string[1]="CDROM TO SMC";
        string[2]="SMC TO CDROM";
        string[5]="FORMAT SMC";
    }                                           
    osd_init_periphGUI();
    osd_draw_region_rect(0, 0, 64*8, 40, COLOR_GREEN, 3);
    osd_draw_region_rect(0, 278, 64*8, 10, COLOR_GREEN, 3);
	BYTE	*title_str="USER OPERATIONS";
	if(storage_type==0)
	{
		osd_DrawRegionString(8, 1, string[NO_PERIPHRAL], COLOR_DBLUE, COLOR_LBLUE, MESSAGE_REGION); 	//draw string on button
		delay_1ms(2000);
		full_scrn &= (~PERIPHERAL);//for release the IR
		osd_init();
                //if you want not interrupt current play,you can use the followed method//dingzhy
		//psprintf(RegionValStr[REGION1], "USB/CARD NOT FOUND");  
		//PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);    
	}
	else
	{
    	osd_DrawRegionString(8, 1, title_str, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);		//draw the note
    	SetOsdCol(FUNCTION_REGION, FUNCTION_REGION, 0,__palette4F(192,192, 192, 0xe0));		//draw background of the region
    
    	Set_Button();
        level=1;
        input_flag=0;
        xoffset=0;
        CopyID=0;
        Switch_flag=0;
        InfoGui_flag=0;
        if(media_type==MEDIA_CARD)
    	    KeyID=BUTTON_P2CD;
        else if(media_type==MEDIA_CD)
            KeyID=BUTTON_CD2P;
    	highlight_button(KeyID);
        for(i=0;i<8;i++)	
            getstring[i]=32;//initialize the getstring for rename,every element is space
    }
}

/***************************************************************************
 *  Function Name: show_CapacityInfo                                       *
 *  Purposes:                                                              *
 *   show the capacity infomation if the "CapacityInfo" button is select   *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Create:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void show_CapacityInfo(void)
{
    #ifdef SPHE8202_ALL_TYPE_CARD_WRITE
    card_browse_sign = 0;	//dingzhy add for not into CardSetBrowse
    #endif
    InfoGui_flag=1;
    StorageGetCapacityInfo();
    osd_init_MediaswitchGUI();
    BYTE *title_str="CAPACITY INFO";
    osd_draw_region_rect(0, 0, 64*4, 40, COLOR_GREEN, 3);
    osd_DrawRegionString(2, 1, title_str, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);
    SetOsdCol(FUNCTION_REGION, FUNCTION_REGION, 0,__palette4F(192,192, 192, 0xe0));		//draw background of the region
    osd_DrawRegionString(2, 1, title_str, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);
    psprintf(linebuf, "TOTAL: %5dM", uiTotalCapacity);
    osd_DrawRegionString(1,8+5,linebuf, COLOR_WHITE, COLOR_GRAYWHITE,3);		//draw string on button        
    psprintf(linebuf, "USED: %6dM", uiUsedCapacity);
    osd_DrawRegionString(1,2*8+5,linebuf, COLOR_WHITE, COLOR_GRAYWHITE,3);		//draw string on button        
    psprintf(linebuf, "REMAIN: %4dM", uiRemainCapacity);
    osd_DrawRegionString(1,3*8+5,linebuf, COLOR_WHITE, COLOR_GRAYWHITE,3);		//draw string on button        
}
/***************************************************************************
 *  Function Name: switch_left                                             *
 *  Purposes: shift highlight using the left key on the switch menu        *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void switch_left()
{
    if(InfoGui_flag==1)
    {
        invalid_key();
	    return;    
    }
    
    if(input_flag==0)
    {
        if((level == 2))
        {    level=1;
            CopyID=0;
        }
        highlight_button_all(KeyID,CopyID);
    }
    #ifndef NEW_INPUT_MENU 
    else if(input_flag==1)
    {
        pressnum_flag=0;
        if(xoffset==7)
        {
            if(getstring[xoffset]!=32)
            {
            getstring[xoffset]=32;
            osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION); 
            }
            else
            {
            getstring[xoffset-1]=32;
            osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION); 
            xoffset--;
            osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
            }
            
        }
        else if((xoffset>0)&&(xoffset<7))
        {
            getstring[xoffset]=32;
            getstring[xoffset-1]=32;
            osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION); 
            xoffset--;
            osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
        }
        else if(xoffset==0)
        {   
            getstring[xoffset]=32;
//            getstring[xoffset-1]=32;
            osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION);          
           
        }
    }
    #endif
}
/***************************************************************************
 *  Function Name: switch_right                                            *
 *  Purposes: shift highlight using the right key on the switch menu       *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void switch_right()
{
    if(InfoGui_flag==1)
    {
        invalid_key();
	    return;    
    }
    
    if(input_flag==0)
    {
        if((level == 1)&&(KeyID == BUTTON_COPY))
        {
            level=2;
            CopyID=1;
        }
        highlight_button_all(KeyID,CopyID);
    }
   #ifndef NEW_INPUT_MENU 
    else if(input_flag==1)
    {
        if(xoffset<7)
        {
		        getstring[xoffset]=32;//char " "
            osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION); 
            xoffset++;
            osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
        }
    }
    #endif
}

/***************************************************************************
 *  Function Name: switch_down                                             *
 *  Purposes: shift highlight using the down key on the switch menu        *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void switch_down(void)
{
    if(InfoGui_flag==1)
    {
        invalid_key();
	    return;    
    }
    if(Switch_flag==1)
    {
       #ifdef CARD_SETUP_TYPE_4
       if(SwitchID==BUTTON_UDISK)    
           {
               if(detect_type & SD_CARD_DEVICE)
                   SwitchID=BUTTON_SD;
               else if(detect_type & MS_CARD_DEVICE)
                   SwitchID=BUTTON_MS;   
            }    
        else
            SwitchID=BUTTON_UDISK ;
        #elif defined(CARD_SETUP_TYPE_3)
        if(detect_type&USB_DEVICE)
        {
            if(SwitchID==BUTTON_UDISK)
            {
                if(detect_type & CF_CARD_DEVICE) 
                    SwitchID=BUTTON_CF;
                else if(detect_type & SD_CARD_DEVICE)
                    SwitchID=BUTTON_SD;         
                else if(detect_type & MS_CARD_DEVICE)
                    SwitchID=BUTTON_MS;             
                else if(detect_type & SMC_CARD_DEVICE) 
                    SwitchID=BUTTON_SMC;
            }
            else
                SwitchID=BUTTON_UDISK ;
         }
         else if((detect_type & CF_CARD_DEVICE)&&!(detect_type&USB_DEVICE))
         {
            if(SwitchID==BUTTON_CF)
            {
                if(detect_type & SD_CARD_DEVICE)
                    SwitchID=BUTTON_SD;         
                else if(detect_type & MS_CARD_DEVICE)
                    SwitchID=BUTTON_MS;             
                else if(detect_type & SMC_CARD_DEVICE) 
                    SwitchID=BUTTON_SMC;
            }
            else
                SwitchID=BUTTON_CF ;
         }                                 
        #endif              
    highlight_button(SwitchID);    
    }
    else
    {    
    if(input_flag==0)
    {
    if(media_type==MEDIA_CD)
	{
        if(level==1)
        {
    		if(KeyID==BUTTON_COPY)
    		        {
    		    KeyID=BUTTON_CAPACITY;
    		            CopyID=0;
    		        }
    		else if(KeyID==BUTTON_CD2P)
    		    KeyID=BUTTON_COPY;
    		else if(KeyID==BUTTON_CAPACITY)
    		    KeyID=BUTTON_CD2P;    		   		    
        }
        else if(level ==2)
        {
            if(CopyID>=COPY_NEWDIR)
                CopyID=COPY_ROOTDIR;
            else
                CopyID++;
        }

	}
	else 
    if(media_type==MEDIA_CARD)
	{
		if(KeyID>=BUTTON_CAPACITY)
		{
			KeyID=BUTTON_P2CD;
		}
		else
		{
			KeyID++;
		}
		if(KeyID==BUTTON_COPY)
		{
			KeyID=BUTTON_DELETE;
		}
	}
    highlight_button_all(KeyID,CopyID);
    }
}
}
/***************************************************************************
 *  Function Name: switch_up                                             *
 *  Purposes: shift highlight using the up key on the switch menu          *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void switch_up(void)
{
    if(InfoGui_flag==1)
    {
        invalid_key();
	    return;    
    }    
    
    if(Switch_flag==1)
    {
        #ifdef CARD_SETUP_TYPE_4
        if(SwitchID==BUTTON_UDISK)    
            {
                if(detect_type & SD_CARD_DEVICE)
                    SwitchID=BUTTON_SD;
                else if(detect_type & MS_CARD_DEVICE)
                    SwitchID=BUTTON_MS;   
             }    
         else
            SwitchID=BUTTON_UDISK ;
        #elif defined(CARD_SETUP_TYPE_3)
        if(detect_type&USB_DEVICE)
        {
            if(SwitchID==BUTTON_UDISK)
            {
                if(detect_type & CF_CARD_DEVICE) 
                    SwitchID=BUTTON_CF;
                else if(detect_type & SD_CARD_DEVICE)
                    SwitchID=BUTTON_SD;         
                else if(detect_type & MS_CARD_DEVICE)
                    SwitchID=BUTTON_MS;             
                else if(detect_type & SMC_CARD_DEVICE) 
                    SwitchID=BUTTON_SMC;
            }
            else
                SwitchID=BUTTON_UDISK ;
         }
         else if((detect_type & CF_CARD_DEVICE)&&!(detect_type&USB_DEVICE))
         {
            if(SwitchID==BUTTON_CF)
            {
                if(detect_type & SD_CARD_DEVICE)
                    SwitchID=BUTTON_SD;         
                else if(detect_type & MS_CARD_DEVICE)
                    SwitchID=BUTTON_MS;             
                else if(detect_type & SMC_CARD_DEVICE) 
                    SwitchID=BUTTON_SMC;
            }
            else
                SwitchID=BUTTON_CF ;  
        }                                
         #endif     
    highlight_button(SwitchID);    
    }
    else
    {    
    if(input_flag==0)
    {
    if(media_type==MEDIA_CD)
	{
        if(level==1)
        {
    		if(KeyID==BUTTON_COPY)
    		{
    			KeyID=BUTTON_CD2P;
    		}
    		else if(KeyID==BUTTON_CD2P)
    		{
                KeyID=BUTTON_CAPACITY;
    		}
    		else if(KeyID==BUTTON_CAPACITY)
    		{
                KeyID=BUTTON_COPY;
    		}
        }
        else if(level ==2)
        {
            if(CopyID<=COPY_ROOTDIR)
                CopyID=COPY_NEWDIR;
            else
                CopyID--;
        }
	}
	else 
    if(media_type==MEDIA_CARD)
	{
		if(KeyID<=BUTTON_P2CD)
		{
			KeyID=BUTTON_CAPACITY;
		}
		else
		{
			KeyID--;
		}
		if(KeyID==BUTTON_COPY)
		{
			KeyID=BUTTON_P2CD;
		}
	}	
    highlight_button_all(KeyID,CopyID);
    }
}
}

/***************************************************************************
 *  Function Name: Message_Show                                            *
 *  Purposes:      show the message when the function is selected          *
 *                  or fineshed                                            *
 *  Arguments:     strID                                                    *
 *  Returns:       none                                                    *
 *  Update:        sunzhh 2004-11-10                                       *
 **************************************************************************/
void Message_Show(BYTE strID)
{
#ifdef FAT_Write_UI
	BYTE *str[]={"UDISK ERROR","COPY FILE OK","DELETE FILE OK","UDISK FORMATED","RENAMING FILE","PLEASE WAIT ...","UDISK FULL","UDISK EMPTY","PLEASE INPUT","NO MATCHED DIR","DIR EXISTING","UDISK PROTECT","UDISK PLUG OUT","ALREADY EXISTS"};

    if(storage_type==USB_DEVICE)
    {      
        str[0]="UDISK ERROR";
        str[3]="UDISK FORMATED";       
        str[6]="UDISK FULL";
        str[7]="UDISK EMPTY";
        str[11]="UDISK PROTECT";
        str[12]="UDISK PLUG OUT";       
    }
    else if(storage_type==CF_CARD_DEVICE)      
    {
        str[0]="CF CARD ERROR";
        str[3]="CF CARD FORMATED";
        str[6]="CF CARD FULL";
        str[7]="CF CARD EMPTY";
        str[11]="CF CARD PROTECT";
        str[12]="CF CARD PLUG OUT";            
    }
    else if(storage_type==SD_CARD_DEVICE)
    {      
        str[0]="SD CARD ERROR";
        str[3]="SD CARD FORMATED";
        str[6]="SD CARD FULL";
        str[7]="SD CARD EMPTY";
        str[11]="SD CARD PROTECT";
        str[12]="SD CARD PLUG OUT";            
    }
    else if(storage_type==MS_CARD_DEVICE) 
    {     
        str[0]="MS CARD ERROR";
        str[3]="MS CARD FORMATED";
        str[6]="MS CARD FULL";
        str[7]="MS CARD EMPTY";
        str[11]="MS CARD PROTECT";
        str[12]="MS CARD PLUG OUT";            
    }
    else if(storage_type==SMC_CARD_DEVICE)
    {      
        str[0]="SMC CARD ERROR";
        str[3]="SMC CARD FORMATED";
        str[6]="SMC CARD FULL";
        str[7]="SMC CARD EMPTY";
        str[11]="SMC CARD PROTECT";
        str[12]="SMC CARD PLUG OUT";        
    }                                           
#elif defined(CF_CARD_WRITE)
	BYTE *str[]={"CARD ERROR","COPY FILE OK","DELETE FILE OK","CARD FORMATED","RENAMING FILE","FILE COPYING","CARD FULL","CARD EMPTY","PLEASE INPUT","NO MATCH DIR","DIR EXISTING"};//add 2003-12-22
#endif
    osd_init_periphGUI();
	osd_DrawRegionString(6, 1, str[strID], COLOR_DBLUE, COLOR_LBLUE, MESSAGE_REGION);	//draw the error
	delay_1ms(2000);
}
#ifdef NEW_INPUT_MENU
int Str_Index_x,Str_Index_y;
BYTE Exit_Enter_flag;
BYTE Max_input_flag;
BYTE Max_left_flag;
int  input_xoffset;
char *StrExit="EXIT";
char *StrEnter="ENTER";
char *Str_temp;
char GetString[8]={};
UINT8 Item_Num[5][8]={ 
                    {0,1,2,3,4,5,6,7},
                    {8,9,10,11,12,13,14,15},
                    {16,17,18,19,20,21,22,23},
                    {24,25,26,27,28,29,30,31},
                    {32,33,34,35,36,37,38,39}
                    };
char *Item_Str[]={   "A","B","C","D","E","F","G","H","I","J",
                     "K","L","M","N","O","P","Q","R","S","T",
                     "U","V","W","X","Y","Z","1","2","3","4",
                     "5","6","7","8","9","0","~","_","-","\\"
                     };                    
void input_str_func_up(void)
{  
    input_str_clear_HL();
    Str_Index_x--;
    if(Str_Index_x<-1)
    {
        Str_Index_x=-1;        
    }
    else if(Str_Index_x==-1)
    {
        
    }   
    else if(Str_Index_x>-1)
    {
        input_HL_ItemStr(Item_Num[Str_Index_x][Str_Index_y]);
    }
}
void input_str_func_down(void)
{   
     input_str_clear_HL();
     Str_Index_x++;
     if((Str_Index_x==5)&&(Str_Index_y<4))
     {
        Exit_Enter_flag=1;
        osd_DrawRegionString(8, 7*8+5, StrExit, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
     }
     else if((Str_Index_x==5)&&(Str_Index_y>=4))
     {
        Exit_Enter_flag=2;
        osd_DrawRegionString(20, 7*8+5, StrEnter, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
     }
     else if(Str_Index_x>5)
     {     
        Str_Index_x=5;
        if(Exit_Enter_flag==1) 
        {
            osd_DrawRegionString(8, 7*8+5, StrExit, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
        }
        else if(Exit_Enter_flag==2) 
        {
            osd_DrawRegionString(20, 7*8+5, StrEnter, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
        }
        
     }
     else if(Str_Index_x<5)
     {      
         input_HL_ItemStr(Item_Num[Str_Index_x][Str_Index_y]);
     }
}
void input_str_func_left(void)
{        
     if(Str_Index_x==-1)
     {        
        Max_input_flag=0;
        input_xoffset--;
        printf("=============input_xoffset:%d=================\n",input_xoffset);
        if(input_xoffset<0)
          { 
             Max_left_flag=1;
             input_xoffset=0;
          }
        else if(Max_left_flag!=1)
          {           
             GetString[input_xoffset]=' ';
             printf("===GetString:%s========\n",GetString); 
             osd_DrawRegionString(14+input_xoffset, 1, " ", COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION); 
          }   
        return;
     }
     input_str_clear_HL();  
     if((Str_Index_x==5)&&(Exit_Enter_flag==2))
     {
         Exit_Enter_flag=1;
         osd_DrawRegionString(8, 7*8+5, StrExit, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
     }  
     else if((Str_Index_x==5)&&(Exit_Enter_flag==1))
     {       
         osd_DrawRegionString(8, 7*8+5, StrExit, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
     }  
     else if(Str_Index_x<5)
     {     
         Str_Index_y--;
         if(Str_Index_y<0) Str_Index_y=0;
         input_HL_ItemStr(Item_Num[Str_Index_x][Str_Index_y]);
     }
}
void input_str_func_right(void)
{     
     if(Str_Index_x==-1)
     {   
        if(input_xoffset>7)
        {
            Max_input_flag=1;
            input_xoffset=7;
        }
        else if((input_xoffset<=7)&&(Max_input_flag!=1))
        {
             GetString[input_xoffset]=' ';
             printf("===GetString:%s========\n",GetString); 
             osd_DrawRegionString(14+input_xoffset, 1, " ", COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION); 
        }
        input_xoffset++;
        return;
     }    
     input_str_clear_HL();  
      if((Str_Index_x==5)&&(Exit_Enter_flag==1))
     {
         Exit_Enter_flag=2;
         osd_DrawRegionString(20, 7*8+5, StrEnter, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
     }     
     else  if((Str_Index_x==5)&&(Exit_Enter_flag==2))
     {      
         osd_DrawRegionString(20, 7*8+5, StrEnter, COLOR_WHITE, COLOR_DBLUE, FUNCTION_REGION);	
     }     
     else if(Str_Index_x<5)
     {     
         Str_Index_y++;
         if(Str_Index_y>7) Str_Index_y=7;
         input_HL_ItemStr(Item_Num[Str_Index_x][Str_Index_y]);
     }
}

void input_str_func_select(void)
{
    BYTE Str_ID=0;     
    Max_left_flag=0;
    if((Str_Index_x==5)&&(Exit_Enter_flag==1))
    {
        input_str_func_exit();
        return;
    } 
    if((Str_Index_x==5)&&(Exit_Enter_flag==2))
    {
        input_str_func_enter();
        return;
    }   
    Str_ID=Item_Num[Str_Index_x][Str_Index_y];
    if(input_xoffset>7)
    {
        Max_input_flag=1;
        input_xoffset=7;
    }
    else if((input_xoffset<=7)&&(Max_input_flag!=1))
    {
        Str_temp=Item_Str[Str_ID];
        GetString[input_xoffset]=*Str_temp;
        osd_DrawRegionString(14+input_xoffset, 1, Item_Str[Str_ID], COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
    }
    input_xoffset++;
}
        
void input_str_func_exit(void)
{
     input_str_clear_variable();
     full_scrn &= (~PERIPHERAL);//for release the IR
	 osd_init();    
     
}
void input_str_func_enter(void)
{
      if(KeyID == BUTTON_COPY)
        {   
            switch(CopyID)
            {
                case COPY_EXISTING://copy to existing dir
                	card_copy(COPY_EXISTING);
        			break;    
                case COPY_NEWDIR://copy to created new folder
				    card_copy(COPY_NEWDIR);
        			break;                
            }
        }
        else if(KeyID == BUTTON_RENAME)//rename the selected file
        {
            	rename_cardfile();        
        }
      
}
void input_str_clear_variable(void)
{
    int i;
    for(i=0;i<8;i++)
       GetString[i]=' ';
    Str_Index_x=0;
    Str_Index_y=0;
    Exit_Enter_flag=0;
    Max_input_flag=0;
    Max_left_flag=0;
    input_xoffset=0;    
}
#endif

/***************************************************************************
 *  Function Name: input_page                                              *
 *  Purposes:  draw the input page after select                            * 
 *             "copy to new dir/existing dir"                              *
 *  Arguments: none                                                        *
 *  Returns:   none                                                        *
 *  Update:    sunzhh 2004-11-10                                           *
 **************************************************************************/
void input_page(void)
{
    #ifdef NEW_INPUT_MENU   
    BYTE *title_str1="INPUT DIR:";
    BYTE *title_str2="INPUT NAME:";
    osd_init_periphGUI();
    osd_draw_region_rect(0, 0, 64*8, 40, COLOR_GREEN, 3);
    osd_draw_region_rect(0, 278, 64*8, 10, COLOR_GREEN, 3);
    if(KeyID == BUTTON_COPY)
	    osd_DrawRegionString(2, 1, title_str1, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);		
    else if(KeyID == BUTTON_RENAME)
	    osd_DrawRegionString(2, 1, title_str2, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);		

    osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
	SetOsdCol(FUNCTION_REGION, FUNCTION_REGION, 0,__palette4F(192,192, 192, 0xe0));		//draw background of the region
    //init variable
    input_str_clear_variable();
    input_str_clear_HL();
    //HL first itemstr
    input_HL_ItemStr(0);
    //for IR U/D/L/R/Sel input str func setting
    SetFullscrnCmdFuncPtr(input_str_func_up, input_str_func_down, input_str_func_left,
                                  input_str_func_right, input_str_func_select);
    #else  
    int i;
    BYTE *str[]={   "      INSTRUCTION       ",
                    "1->1 A B C    2->2 D E F",
                    "3->3 G H I    4->4 J K L",
                    "5->5 M N O    6->6 P Q R",
                    "7->7 S T U    8->8 V W X",
                    "9->9 Y Z ~    0->0 _ - \\",
                    "<: CANCEL     >: SPACE"};
    BYTE *title_str1="INPUT DIR:";
    BYTE *title_str2="INPUT NAME:";
    input_flag=1;
    osd_init_periphGUI();
    osd_draw_region_rect(0, 0, 64*8, 40, COLOR_GREEN, 3);
    osd_draw_region_rect(0, 278, 64*8, 10, COLOR_GREEN, 3);
    if(KeyID == BUTTON_COPY)
	    osd_DrawRegionString(2, 1, title_str1, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);		
    else if(KeyID == BUTTON_RENAME)
	    osd_DrawRegionString(2, 1, title_str2, COLOR_YELLOW, COLOR_GREEN, FUNCTION_REGION);		

    osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
	SetOsdCol(FUNCTION_REGION, FUNCTION_REGION, 0,__palette4F(192,192, 192, 0xe0));		//draw background of the region
    for(i=0;i<=6;i++)
    osd_DrawRegionString(4, (i+1)*8+5, str[i], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);	
    #endif
}
#ifdef NEW_INPUT_MENU
void input_str_clear_HL(void)
{
    int i;
    BYTE *str[]={   " A  B  C  D  E  F  G  H ",
                    " I  J  K  L  M  N  O  P ",
                    " Q  R  S  T  U  V  W  X ",
                    " Y  Z  1  2  3  4  5  6 ",
                    " 7  8  9  0  ~  _  -  \\",
                    "                        ",                    
                    "    EXIT        ENTER   "};
   for(i=0;i<=6;i++)
   osd_DrawRegionString(4, (i+1)*8+5, str[i], COLOR_WHITE, COLOR_GRAYWHITE, FUNCTION_REGION);                     
}            
void input_HL_ItemStr(BYTE itemstr_index )
{
    BYTE itemstr_xstart = 0;
    BYTE itemstr_ystart = 0;
    BYTE x,y;   
    x=itemstr_index%8;
    y=itemstr_index/8;
    itemstr_xstart =5 + x*3;
    itemstr_ystart =13+ y*8;
    osd_DrawRegionString(itemstr_xstart, itemstr_ystart,Item_Str[itemstr_index], COLOR_WHITE, COLOR_DBLUE,FUNCTION_REGION);      
    
}

#endif

/***************************************************************************
 *  Function Name: input_name                                              *
 *  Purposes:  show the input letter on the input page                     * 
 *  Arguments: none                                                        *
 *  Returns:   none                                                        *
 *  Update:    sunzhh 2004-11-10                                           *
 **************************************************************************/
void input_name(int num)
{
    BYTE *namestring[10][4]={ 
                            {"0","_","-","\\"},
                            {"1","A","B","C"},
                            {"2","D","E","F"},
                            {"3","G","H","I"},
                            {"4","J","K","L"},
                            {"5","M","N","O"},
                            {"6","P","Q","R"},
                            {"7","S","T","U"},
                            {"8","V","W","X"},
                            {"9","Y","Z","~"}};
    if(pressnum_flag!=1)
    {        
               
    if(pressnum!=num)
    {
        PressID=0;
        pressnum=num;
    }
    else
    {
        if(PressID>=3)
            PressID=0;  
        else
            PressID++;  
    }   

    osd_DrawRegionString(14+xoffset, 1, namestring[num][PressID], COLOR_DBLUE,COLOR_LBLUE, FUNCTION_REGION);
    temp=namestring[num][PressID];
    //printf("temp=%c\n",*temp);
}
}
/***************************************************************************
 *  Function Name: polling_input_name                                      *
 *  Purposes:  called by polling_100ms in polling.c to                     * 
 *             refresh the letter inputted                                 *
 *  Arguments: none                                                        *
 *  Returns:   none                                                        *
 *  Update:    wangw 2004-11-10                                            * 
 **************************************************************************/
void polling_input_name(void)
{
    static BYTE i=0;
    static BYTE temp1=50,temp2=50;
    if((i==0)&&(pressnum!=10))
    {
        temp1=pressnum;
        temp2=PressID;
        i++;
    }
    else
    {
        if((pressnum!=temp1)||(PressID!=temp2))
        {
            i=0;   
        }
        else
        {
            if((i==10))
            {   
                if((pressnum==temp1)&&(PressID==temp2))
                {

                        getstring[xoffset]=*temp;
                        osd_DrawRegionString(14+xoffset, 1, temp, COLOR_DBLUE,COLOR_GREEN, FUNCTION_REGION); 
                        xoffset++;
                        if(xoffset>7)
                        {
                             pressnum_flag=1;    
                             xoffset=7;
                        }
                       
                        osd_DrawRegionString(14+xoffset, 1, " ", COLOR_DBLUE,COLOR_LBLUE , FUNCTION_REGION);
                }
                i=0;
                pressnum=10;
            }
            else
                i++;
        }
    }
}
/***************************************************************************
 *  Function Name: card_copy                                               *
 *  Purposes:  the entry of coping file from                               * 
 *             cdrom to card/USB and showing related GUI                   *
 *  Arguments: copy_mode                                                        *
 *  Returns:   none                                                        *
 *  Update:    wangw 2004-11-10                                            * 
 **************************************************************************/
void card_copy(BYTE copy_mode)
{
    #ifdef SPHE8202_ALL_TYPE_CARD_WRITE
    card_browse_sign = 0;
    CardTestReady();
    play_state=VCD_STATE_NORMAL;
    card_browse_sign = 1;
    #endif
	
	int copy_status;
#ifdef CF_CARD_WRITE
//	if(CardIdentify()!=0)//very important!!!
	if(FSIdentify()!=0)//very important!!!
#else
    if(!CARDIsPlugIn())
#endif
	{
	    
		Message_Show(ERROR_MESSAGE);
		show_switch(Select_Media);
	}
	else
	{
		if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
		{
			sign_PFun=PFUN_WRITE;//write cf card
			AVD_SetMediaInterrupt();//stop the current mp3, Can't be used for JPEG!!
			Message_Show(PFUN_COPYING);

		}
		else if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
		{
			sign_PFun=PFUN_WRITE;//write JPEG
			Message_Show(PFUN_COPYING);
//			copy_status=CardSchedule(copy_mode);
			copy_status=FSSchedule(copy_mode);
			StorageWriteMessageShow(copy_status);
			full_scrn &= (~PERIPHERAL);//for release the IR
			osd_init();
			#ifdef NEW_INPUT_GUI
			input_str_clear_variable();
			#endif
		}
		#ifdef FAT_Write_File_System  //added by wangwei,2004-11-5 15:42(for other media,eg:mp4,dat...)
		else if(pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER)
        {
            sign_PFun=PFUN_WRITE;//write JPEG
			Message_Show(PFUN_COPYING);
//			copy_status=CardSchedule(copy_mode);
			copy_status=FSSchedule(copy_mode);
			StorageWriteMessageShow(copy_status);
			full_scrn &= (~PERIPHERAL);//for release the IR
			osd_init();
			#ifdef NEW_INPUT_GUI
			input_str_clear_variable();
			#endif
        }
        #endif  //FAT_Write_File_System
	}
}
/********************************************************************************\
**Function      : StorageWriteMessageShow()
**Description   : show message
**Return value  : null
**Creator       : lijd 2004-12-8 17:21
\********************************************************************************/
void StorageWriteMessageShow(int copy_status)
{
    switch(copy_status)
    {
        case -1:
                Message_Show(P_SPACEFULL);
                break;
        case -2:
                Message_Show(P_NOMATCH);
                break;
        case -3:
                Message_Show(P_DIREXISTING);
                break;
        case -4:
                Message_Show(P_UDISK_PROTECT);	
                break; 
        case -5:
                Message_Show(P_UDISK_PLUGOUT);	
                break;
        case -6:
                Message_Show(P_DIT_EXIST);	
                break;
        case -7:
                
                break;
        default:
                Message_Show(PFUN_WRITE);
                break;                                               
    }
    
}
/***************************************************************************
 *  Function Name: cd2card                                                 *
 *  Purposes: the entry of changing playing cdrom to card/USB              *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 **************************************************************************/
void cd2card(void)
{
	read_card_sign=1;	//fengjl 2004-07-06 11:03
    SwitchMedia(CD2CARD);
}
/***************************************************************************
 *  Function Name: card2cd                                                 *
 *  Purposes: the entry of changing playing card/USB to cdrom              *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 **************************************************************************/
void card2cd(void)
{
    SwitchMedia(CARD2CD);

}
/***************************************************************************
 *  Function Name: card_delete                                             *
 *  Purposes: the entry of deleting the selected file                      *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 **************************************************************************/
int card_delete(void)
{
#ifdef CF_CARD_WRITE
//	if(CardIdentify()!=0)//very important!!!
	if(FSIdentify()!=0)//very important!!!
#else
    if(!CARDIsPlugIn())
#endif
	{
		Message_Show(ERROR_MESSAGE);
		show_switch(Select_Media);
	}
	else
	{
		sign_PFun=PFUN_DELETE;//delete data
//		if(CardSchedule(0)==-1)
		if(FSSchedule(0)==-1)
		{
			Message_Show(P_SPACEEMPTY);
			//turn to CDROM
			card2cd();
			return -1;
		}
		else
		{
			Message_Show(PFUN_DELETE);
		}
	}
	return 0;
}
/***************************************************************************
 *  Function Name: format_card                                             *
 *  Purposes: the entry of formating the selected storage                  *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 **************************************************************************/
void format_card(void)
{
#ifdef CF_CARD_WRITE
//	if(CardIdentify()!=0)//very important!!!
	if(FSIdentify()!=0)//very important!!!
#else
    if(!CARDIsPlugIn())
#endif
	{
		Message_Show(ERROR_MESSAGE);
		show_switch(Select_Media);
	}
	else
	{
		sign_PFun=PFUN_FORMAT;//format card
//		CardSchedule(0);
		FSSchedule(0);
		Message_Show(PFUN_FORMAT);
	}
}
/***************************************************************************
 *  Function Name: rename_cardfile                                         *
 *  Purposes: the entry of renaming the selected file                      *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 **************************************************************************/
void rename_cardfile(void)
{
#ifdef CF_CARD_WRITE
//	if(CardIdentify()!=0)//very important!!!
	if(FSIdentify()!=0)//very important!!!
#else
    if(!CARDIsPlugIn())
#endif
	{
		Message_Show(ERROR_MESSAGE);
		show_switch(Select_Media);
	}
	else
	{
		sign_PFun=PFUN_RENAME;//Create Dir
//		CardSchedule(0);
		FSSchedule(0);
		Message_Show(PFUN_RENAME);
		cd2card();//refresh the card
	}
}
/***************************************************************************
 *  Function Name: switch_select                                           *
 *  Purposes: select the function button to finish the request of the user *
 *  Arguments: none                                                        *
 *  Returns: none                                                          *
 *  Update:  sunzhh 2004-11-10                                             *
 **************************************************************************/
void switch_select(void)
{
    BYTE i;
    if(InfoGui_flag==1)
    {
        invalid_key();
	    return;    
    }    
    
    if(Switch_flag==1)
    {
        switch(SwitchID)
    	{
    		case	BUTTON_UDISK:
                    Select_Media=Media_UDISK;
                    storage_type = USB_DEVICE;
    		    break;
            #ifdef CARD_SETUP_TYPE_3    	    
    		case	BUTTON_CF:
                    Select_Media=Media_CF;
                    storage_type = CF_CARD_DEVICE;
                break;//if delete the last file, then convert to CD
            #endif                
    		case	BUTTON_SD:
                    Select_Media=Media_SD;
                    storage_type = SD_CARD_DEVICE;
    			break;  
    		case	BUTTON_MS:
                    Select_Media=Media_MS;
                    storage_type = MS_CARD_DEVICE;
    			break;
            #ifdef CARD_SETUP_TYPE_3    			                    
    		case	BUTTON_SMC:
                    Select_Media=Media_SMC;
                    storage_type = SMC_CARD_DEVICE;
    			break;
            #endif
    	}
        show_switch(Select_Media);
    }
    else
    {
    if(input_flag==0)
    {
    	switch(KeyID)
    	{
    		case	BUTTON_COPY:
                if(CopyID==1)
                {
	                	card_copy(COPY_ROOTDIR);
    			}
                if((CopyID==2)||(CopyID==3))
                {
                    input_page();
                }

    			break;
    
    		case	BUTTON_DELETE:
               	if(card_delete()==-1) 
                break;//if delete the last file, then convert to CD
    		case	BUTTON_CD2P:
                cd2card();
    			break;
    
    		case	BUTTON_FORMAT:
                format_card();
    		case	BUTTON_P2CD:
                card2cd();
    			break;
    
    		case	BUTTON_RENAME:
                input_page();
    			break;
    
    		case	BUTTON_CAPACITY:
//                    osd_init();
//                StorageGetCapacityInfo();
                show_CapacityInfo();
                	break;    			
    	}
	}
	 #ifndef NEW_INPUT_MENU 
    else if(input_flag==1)
    {
        for(i=0;i<8;i++)
        {
            if(getstring[i]!=32)
               break;
            else if(i==7)
            {
                Message_Show(P_INPUT);
                xoffset=0;
                input_page();
                return;
            }
        }
        if(KeyID == BUTTON_COPY)
        {   
            switch(CopyID)
            {
                case COPY_EXISTING://copy to existing dir
                	card_copy(COPY_EXISTING);
        			break;    
                case COPY_NEWDIR://copy to created new folder
				    card_copy(COPY_NEWDIR);
        			break;                
            }
        }
        else if(KeyID == BUTTON_RENAME)//rename the selected file
        {
            	rename_cardfile();        
        }
    }
    #endif
}
}


/***************************************************************
**Function: FSSchedule()
**Description: Schedule for getting the different function.
**return value:   if -1, then no enough space for write
**Create: wuxiaofeng, 2003-9-15
**modified: add argument for three types of copy!
**lijd  updating   2004-12-6 16:19
***************************************************************/
//int CardSchedule(BYTE copy_mode)
int FSSchedule(BYTE copy_mode)
{
#ifdef FAT_Write_File_System  //added by wangwei,2004-11-9 9:10
if(storage_type == USB_DEVICE)
    UsbTestReady();
#endif

	UINT32	lba;
	UINT32	assignlba;
	int  iRes=0;//lijd  for udisk protect 2004-11-18 16:50
	
	if (pFsJpeg->ControlArea == CNT_AREA_FILE)
	{
	    GetOriginalFileMainName(0);	//lijd 2004-12-6 16:19
	}
	else  if(pFsJpeg->ControlArea == CNT_AREA_DIR)
	{
	    GetAllFileNameFromCopyDir();
	}
	
//	lba=CardGetRoot();//get the card information	
	lba=FSGetRoot();//get the card information	
	
	if(sign_PFun==PFUN_WRITE)
	{
		switch(copy_mode)
		{
			case COPY_ROOTDIR:
//				iRes=CardWriteFDB(lba); 
				iRes=FSStorageCopy(lba); 
				switch(iRes)
                {
                    case -1:
                            return	-1;
                            break;
                    case -2:
                            return	-4;	
                            break;
                    case -3:
                            return	-5;		  
                            break;
                    case -4:
                            return	-6;		
                            break; 
                    case -5:
                            return	-7;		
                            break;   
                    default:                
                            break;                                               
                }
				break;
			case COPY_EXSITING:
//				assignlba=CardSearchDir(lba, getstring);
				#ifdef NEW_INPUT_MENU
                assignlba=FSSearchDir(lba, GetString);
                #else
				assignlba=FSSearchDir(lba, getstring);
				#endif
				if(assignlba==0)//have no matched dir
				{
					sign_PFun=PFUN_DEFAULT;//clear
					return	-2;
				}
//				iRes=CardWriteFDB(assignlba);
				iRes=FSStorageCopy(assignlba);
				switch(iRes)
                {
                    case -1:
                            return	-1;
                            break;
                    case -2:
                            return	-4;	
                            break;
                    case -3:
                            return	-5;		  
                            break;
                    case -4:
                            return	-6;		
                            break; 
                    case -5:
                            return	-7;		
                            break;   
                    default:                
                            break;                                               
                }
				break;
			case COPY_NEWDIR://only in root
//				assignlba=CardCreateDir(getstring);
				#ifdef NEW_INPUT_MENU
                assignlba=FSCreateDir(lba,GetString);
                #else
				assignlba=FSCreateDir(lba,getstring);
				#endif
				if(assignlba==-1)//have same name with the existing dir
				{
					sign_PFun=PFUN_DEFAULT;//clear
					return	-3;//add 2003-12-22
				}
//				iRes=CardWriteFDB(assignlba); 
				iRes=FSStorageCopy(assignlba); 
				switch(iRes)
                {
                    case -1:
                            return	-1;
                            break;
                    case -2:
                            return	-4;	
                            break;
                    case -3:
                            return	-5;		  
                            break;
                    case -4:
                            return	-6;		
                            break; 
                    case -5:
                            return	-7;		
                            break;   
                    default:                
                            break;                                               
                }
				break;
		}
	}
	else if(sign_PFun==PFUN_DELETE)
	{
//		if(CardDeleteData()==-1)
		if(FSDeleteData()==-1)
		{
			sign_PFun=PFUN_DEFAULT;//clear
			return	-1;
		}
	}
	else if(sign_PFun==PFUN_FORMAT)
	{
//			CardFormat();
			FSFormat();
	}
	else if(sign_PFun==PFUN_RENAME)
	{
//		CardRenameFile(getstring);//change to rename file 10-30
		#ifdef NEW_INPUT_MENU
        FSRenameFile(GetString);
        #else
		FSRenameFile(getstring);//change to rename file 10-30
		#endif
	}
	sign_PFun=PFUN_DEFAULT;//clear

	return	0;
}
#endif//defined(SPHE8202_USB_Write)||defined(CF_CARD_WRITE)

