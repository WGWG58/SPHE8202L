/**********************************************************
**  Description: Switch interface for CDROM & CF Card
**  Creater:wuxiaofeng
**  Date:03-09-01 16:33
**  Maintain Date: 03-09-15  18:14
**  Modified: let COPY button gray at CF Card side
**  Maintain Date: 03-09-15  11:54
**  Modified: delete the wrong color define
**  Maintain Date: 03-09-17  15:36
**  Modified: if deleting the last file in card, then turn to CDROM side.
***********************************************************/
#include "user_init.h"
#include "global.h"
#include "memmap0.h"
#include "ircmd.h"
#include "types.h"
#include "memcfg.h"
#include "framebuf.h"
#include "memmap.h"
#include "osd.h"
#include "cardfs.h"
#include "fsNav.h"

#ifdef	CF_CARD_WRITE

#define	FUNCTION_REGION	3
#define	MESSAGE_REGION	2

#define	COLOR_WHITE	2
#define	COLOR_GRAY		3
#define	COLOR_DBLUE	4
#define	COLOR_LBLUE	6
#define	COLOR_YELLOW	7
#define	COLOR_GREEN	9
#define	COLOR_RED		12

#define	BUTTON_UP		0
#define	BUTTON_DOWN	1
#define	BUTTON_LEN		18

#define	BUTTON_CD2CF		1
#define	BUTTON_CF2CD		2
#define	BUTTON_COPY		3
#define	BUTTON_DELETE		4
#define	BUTTON_FORMAT		5
#define	BUTTON_CREADIR	6

#define	ERROR_MESSAGE	0
#define	CFFUN_WRITE	1
#define	CFFUN_DELETE	2
#define	CFFUN_FORMAT	3
#define	CFFUN_CREADIR	4
#define	CFFUN_COPYING	5
#define	CF_CARDFULL 	6
#define	CF_CARDEMPTY 	7

#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 

extern void osd_init_cardswitch(void);
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void osd_draw_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown, BYTE r);
extern int AVD_SetMediaInterrupt(void);
//extern int CardSchedule(void);
extern int FSSchedule(void);

//Ö¸ÕëÊý×é: int *p[4];
BYTE 	*string[]={" ","CDROM TO CARD","CARD TO CDROM","COPY THE FILE","DELETE THE FILE","FORMAT CARD","CREATE DIR"};
BYTE	KeyID;

BYTE read_card_sign=0;
BYTE flag_cd2cf=0, flag_cf2cd=0;
BYTE sign_cfFun=0;

/***************************************************************
**Function: Set_Button()
**Description: Draw the button in the region 3.
**return value:   none
**Create: wuxiaofeng, 2003-9-4 
***************************************************************/
void Set_Button(void)
{
	BYTE item;
	if(media_type==MEDIA_CD)
	{
		for(item=BUTTON_CD2CF; item<=BUTTON_COPY; item++)//normal display former three
		{
			osd_draw_button(2, item, BUTTON_LEN, COLOR_LBLUE, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, item*8+3, string[item], COLOR_DBLUE, COLOR_LBLUE, FUNCTION_REGION);		//draw string on button
		}
		for(item=BUTTON_DELETE; item<=BUTTON_CREADIR; item++)//invalidate the latter three
		{
			osd_draw_button(2, item, BUTTON_LEN, COLOR_LBLUE, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, item*8+3, string[item], COLOR_GRAY, COLOR_LBLUE, FUNCTION_REGION);		//draw string on button
		}
	}
	if(media_type==MEDIA_CARD)
	{
		for(item=BUTTON_CD2CF; item<=BUTTON_CF2CD; item++)//all six are ok
		{
			osd_draw_button(2, item, BUTTON_LEN, COLOR_LBLUE, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, item*8+3, string[item], COLOR_DBLUE, COLOR_LBLUE, FUNCTION_REGION);		//draw string on button
		}
		//for copy gray
		osd_draw_button(2, BUTTON_COPY, BUTTON_LEN, COLOR_LBLUE, BUTTON_UP, FUNCTION_REGION);
		osd_DrawRegionString(3, BUTTON_COPY*8+3, string[BUTTON_COPY], COLOR_GRAY, COLOR_LBLUE, FUNCTION_REGION);		//draw string on button

		for(item=BUTTON_DELETE; item<=BUTTON_CREADIR; item++)//all six are ok
		{
			osd_draw_button(2, item, BUTTON_LEN, COLOR_LBLUE, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, item*8+3, string[item], COLOR_DBLUE, COLOR_LBLUE, FUNCTION_REGION);		//draw string on button
		}
	}
	
}


/***************************************************************
**Function: highlight_button()
**Description: highlight the cursor assigned button.
**return value:   none
**Create: wuxiaofeng, 2003-9-4 
***************************************************************/
void highlight_button(BYTE selectID)
{
	Set_Button();// back to the default color
	switch(selectID)
	{
		case BUTTON_CD2CF:
			osd_draw_button(2, BUTTON_CD2CF, BUTTON_LEN, COLOR_GREEN, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, BUTTON_CD2CF*8+3, string[BUTTON_CD2CF], COLOR_DBLUE, COLOR_GREEN, FUNCTION_REGION); 	//draw string on button
			break;
		case BUTTON_CF2CD:
			osd_draw_button(2, BUTTON_CF2CD, BUTTON_LEN, COLOR_GREEN, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, BUTTON_CF2CD*8+3, string[BUTTON_CF2CD], COLOR_DBLUE, COLOR_GREEN, FUNCTION_REGION); 	//draw string on button
			break;
		case BUTTON_COPY:
			osd_draw_button(2, BUTTON_COPY, BUTTON_LEN, COLOR_GREEN, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, BUTTON_COPY*8+3, string[BUTTON_COPY], COLOR_DBLUE, COLOR_GREEN, FUNCTION_REGION); 	//draw string on button
			break;
		case BUTTON_DELETE:
			osd_draw_button(2, BUTTON_DELETE, BUTTON_LEN, COLOR_GREEN, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, BUTTON_DELETE*8+3, string[BUTTON_DELETE], COLOR_DBLUE, COLOR_GREEN, FUNCTION_REGION); 	//draw string on button
			break;
		case BUTTON_FORMAT:
			osd_draw_button(2, BUTTON_FORMAT, BUTTON_LEN, COLOR_GREEN, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, BUTTON_FORMAT*8+3, string[BUTTON_FORMAT], COLOR_DBLUE, COLOR_GREEN, FUNCTION_REGION); 	//draw string on button
			break;
		case BUTTON_CREADIR:
			osd_draw_button(2, BUTTON_CREADIR, BUTTON_LEN, COLOR_GREEN, BUTTON_UP, FUNCTION_REGION);
			osd_DrawRegionString(3, BUTTON_CREADIR*8+3, string[BUTTON_CREADIR], COLOR_DBLUE, COLOR_GREEN, FUNCTION_REGION);	//draw string on button
			break;
	
	}

}

/***************************************************************
**Function: show_card_switch()
**Description: draw the OSD region.
**return value:   none
**Create: wuxiaofeng, 2003-9-4 
***************************************************************/
void show_card_switch(void)
{
	osd_init_cardswitch();
	BYTE	*title_str="USER OPERATION";
	osd_DrawRegionString(1, 0, title_str, COLOR_YELLOW, COLOR_GRAY, FUNCTION_REGION);		//draw the note
	SetOsdCol(FUNCTION_REGION, FUNCTION_REGION, 0, __palette4F( 128, 255, 128, 0xff));		//draw background of the region
	Set_Button();

	KeyID=BUTTON_CD2CF;
	highlight_button(KeyID);	

}

void card_switch_left()
{
}
void card_switch_right()
{
}
void card_switch_down(void)
{
	if(media_type==MEDIA_CD)
	{
		if(KeyID>=BUTTON_COPY)
		{
			KeyID=BUTTON_CD2CF;
		}
		else
		{
			KeyID++;
		}
	}
	else if(media_type==MEDIA_CARD)
	{
		if(KeyID>=BUTTON_CREADIR)
		{
			KeyID=BUTTON_CD2CF;
		}
		else
		{
			KeyID++;
		}
		if(KeyID==BUTTON_COPY)//add 09/15 disable COPY
		{
			KeyID=BUTTON_DELETE;
		}
	}
	highlight_button(KeyID);
}
void card_switch_up(void)
{
	if(media_type==MEDIA_CD)
	{
		if(KeyID<=BUTTON_CD2CF)
		{
			KeyID=BUTTON_COPY;
		}
		else
		{
			KeyID--;
		}
	}
	else if(media_type==MEDIA_CARD)
	{
		if(KeyID<=BUTTON_CD2CF)
		{
			KeyID=BUTTON_CREADIR;
		}
		else
		{
			KeyID--;
		}
		if(KeyID==BUTTON_COPY)//add 09/15  disable COPY
		{
			KeyID=BUTTON_CF2CD;
		}
	}	
	highlight_button(KeyID);

}

/***************************************************************
**Function: Message_Show()
**Description: display some message in region 2.
**return value:   none
**Create: wuxiaofeng, 2003-9-4 
***************************************************************/
void Message_Show(BYTE strID)
{
	BYTE *str[]={"CARD ERROR","WRITE FILE OK","DELETE FILE OK","CARD FORMATED","DIR CREATED","FILE COPYING","CARD FULL","CARD EMPTY"};
	osd_init_cardswitch();
	SetOsdCol(MESSAGE_REGION, MESSAGE_REGION, 0, 0);
	osd_DrawRegionString(6, 1, str[strID], COLOR_RED, COLOR_LBLUE, MESSAGE_REGION);	//draw the error
	delay_1ms(2000);
}

/***************************************************************
**Function: card_switch_select()
**Description: perform the actual function by selecting the assigned button.
**return value:   none
**Create: wuxiaofeng, 2003-9-4 
***************************************************************/
void card_switch_select(void)
{
	switch(KeyID)
	{
		case	BUTTON_COPY:
//			if(CardIdentify()!=0)//very important!!!
			if(FSIdentify()!=0)//very important!!!
			{
				Message_Show(ERROR_MESSAGE);
				show_card_switch();
			}
			else
			{
				if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
				{
					sign_cfFun=CFFUN_WRITE;//write cf card
					AVD_SetMediaInterrupt();//stop the current mp3, Can't be used for JPEG!!
					Message_Show(CFFUN_COPYING);
				}
				else if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
				{
					sign_cfFun=CFFUN_WRITE;//write JPEG
					Message_Show(CFFUN_COPYING);
//					if(CardSchedule()==-1)
					if(FSSchedule()==-1)
					{
						Message_Show(CF_CARDFULL);
					}
					else
					{
						Message_Show(CFFUN_WRITE);
					}
					full_scrn &= (~CARDOSDSHOW);//for release the IR
					osd_init();
				}
			}
			break;

		case	BUTTON_DELETE://share the break with BUTTON_CD2CF!!
//			if(CardIdentify()!=0)//very important!!!
			if(FSIdentify()!=0)//very important!!!
			{
				Message_Show(ERROR_MESSAGE);
				show_card_switch();
			}
			else
			{
				sign_cfFun=CFFUN_DELETE;//delete data
//				if(CardSchedule()==-1)
				if(FSSchedule()==-1)
				{
					Message_Show(CF_CARDEMPTY);
					full_scrn &= (~CARDOSDSHOW);//for release the IR
					osd_init();
					//turn to CDROM
					flag_cd2cf=0;															   //xulf
					flag_cf2cd=1;
					media_type=MEDIA_CD;
					ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);
					bDiscType=CDUNKNOWN;
					sys_cmd=CMD_FUNC_PLAY;
					break;
				}
				else
				{
					Message_Show(CFFUN_DELETE);
				}
			}

		case	BUTTON_CD2CF://cdrom to card
			full_scrn &= (~CARDOSDSHOW);//for release the IR
			osd_init();
		
			read_card_sign=1;												   //xulf0827
			flag_cd2cf=1;
			flag_cf2cd=0;
			media_type=MEDIA_CARD;
			ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);
			break;

		case	BUTTON_FORMAT://share the break with BUTTON_CF2CD!!
//			if(CardIdentify()!=0)//very important!!!
			if(FSIdentify()!=0)//very important!!!
			{
				Message_Show(ERROR_MESSAGE);
				show_card_switch();
			}
			else
			{
				sign_cfFun=CFFUN_FORMAT;//format card
//				CardSchedule();
				FSSchedule();
				Message_Show(CFFUN_FORMAT);
			}

		case	BUTTON_CF2CD://card to cdrom
			full_scrn &= (~CARDOSDSHOW);//for release the IR
			osd_init();
		
			flag_cd2cf=0;															   //xulf
			flag_cf2cd=1;
			media_type=MEDIA_CD;
			ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);
			bDiscType=CDUNKNOWN;
			sys_cmd=CMD_FUNC_PLAY;
			break;

		case	BUTTON_CREADIR:
//			if(CardIdentify()!=0)//very important!!!
			if(FSIdentify()!=0)//very important!!!
			{
				Message_Show(ERROR_MESSAGE);
				show_card_switch();
			}
			else
			{
				sign_cfFun=CFFUN_CREADIR;//Create Dir
//				CardSchedule();
				FSSchedule();
				Message_Show(CFFUN_CREADIR);
				full_scrn &= (~CARDOSDSHOW);//for release the IR
				osd_init();
			}
			break;
	
	}
}


#endif	//#ifdef	CF_CARD_WRITE

