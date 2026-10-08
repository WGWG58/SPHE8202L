/**********************************************************
**  Description: for virtual keyboard
**  Creater:liweihua
**  Date:03-8-15 21:09
**  Modify Record
**	1. liweihua 2004-2-21 21:37 
**	   change the mode of call ircmd_xxx to the mode of call the function of call_ir_func(IRC_xxx)
**	2. WSLEE    2005-05-18 AM10:30
** 	   add new virtual GUI for user
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
#include "keyboard_bmp.h"
#include "ircode.h"
#include "osd_api.h"    

#ifdef VIRTUAL_KEYBOARD

extern void osd_init_keyboard(void);
extern UINT8 *get_osdbuf_region_ptr(int _region, int _field);

#define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) ) 
#ifdef CD_PLAYER
#define KEY_R  4    //define the region of drawing keyboard
#else
#define KEY_R  3    
#endif
BYTE KeyID=0;//Define ID variable for the keys on virtual keyboard

static int cox;
static int coy;
static int ff,bk;

static char keyboard_icon[3][3]={
	{5,6,1},
	{100,0,100},
	{4,3,2},	
};
void BG_redraw(void)
{

    dimension bmp_dimension;
    coordinate  start;

    bmp_dimension.x_length = bmp_key_BG[0];
    bmp_dimension.y_length = bmp_key_BG[1]; 
    start.x = 0;
    start.y = 0;

    osd_draw_bitmap(KEY_R, &start, (bmp_key_BG+2), &bmp_dimension, 4, 1, NULL);
}
//Draw virtual keyboard on osd region r
//The bmp image of virtual keyboard was made by image processing software.

#ifdef OSD_SUPPORT_256_COLOR	//WSLEE for 256 color virtual keyboard 
void osd_draw_virtual_keyboard(int xStart, int yStart,BYTE r)
{
	//BYTE    *pIcon;
    UINT32  *pTopLine, *pBtmLine;
    UINT32  iDispLoc;
    
    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[r].osd_w;

    //osd_tog_region(r, OSD_ON);
    osd_tog_region(r, OSD_OFF); //20040225

	iRegionWidth = region[r].osd_w;
    //initialize buffer start
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(r,0);   // region r top
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(r,1);   // region r bot
   
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    yStart+=2;

	UINT32 pixel4;
    UINT32 pos;

    //get Keyboard bmp information
    iFontWidth  = bmp_key[0];
    iFontHigh   = bmp_key[1];

    //start to process
    pos = 2;    
        
    for (j=0; j<iFontHigh; j++)
    {
        int yy;
        UINT32 *pp;
        yy = (p_scan) ? yStart : yStart>>1;
        pp = (yStart&1) ? pBtmLine : pTopLine;

        iDispLoc = (yy*iRegionWidth*2/8) + (xStart);
        for (i=0; i<(iFontWidth/4); i++) // every 4-bytes a time, every 1-pixel a byte
        {
        	pixel4=0;
            // 0x12345678  ==>  0x78563412
            for (k=0;k<4;k++)
            {
            	unsigned curByte = bmp_key[pos++];
	            pixel4 = pixel4 | (curByte<<8*k);
            }
            pp[iDispLoc+i] =  pixel4;
        }
        yStart++;
    }//for key heigh
    osd_tog_region(r, OSD_ON);//20040225
    timeout_osd[r] = 0;
}

//Set all keys of keyboard the default color
//The keys of virtual keyboard are draw in different colors
//The numbers,"201, 70, 200, 185, 187, 127", are the positions of keys in color palette. 
void set_button_color(void)
{
	// alan, 2003/8/27 10:43AM
	SetOsdCol(KEY_R,KEY_R,201, __palette4F(0,160,0,0xff));//set the play/pause key color
	SetOsdCol(KEY_R,KEY_R,70, __palette4F(0,160,0,0xff));//set the forward key color
	SetOsdCol(KEY_R,KEY_R,200, __palette4F(0,160,0,0xff));//set the next key color
	SetOsdCol(KEY_R,KEY_R,185, __palette4F(0,160,0,0xff));//set the stop key color
	SetOsdCol(KEY_R,KEY_R,187, __palette4F(0,160,0,0xff)); //set the prev key color
	SetOsdCol(KEY_R,KEY_R,127, __palette4F(0,160,0,0xff));//set the backward key color
}
#endif

//=====================================
// set the selected key highlight color
// SelectID=0: select play/pause key
// SelectID=1: select forward key
// SelectID=2: select next key
// SelectID=3: select stop key
// SelectID=4: select prev key
// SelectID=5: select backward key 
//=====================================

void hl_keyboard_button(BYTE SelectID)
{
	BG_redraw();//main BG redraw
	//set_button_color();

    dimension bmp_dimension;
    coordinate  start;
    const BYTE *pbmp=NULL;    
	switch(SelectID)
	{
		case 0:
			start.x =62 ;
    			start.y = 52;
                     bmp_dimension.x_length = bmp_key_PLAY[0];
                     bmp_dimension.y_length = bmp_key_PLAY[1];
                     pbmp = bmp_key_PLAY + 2;
								
			//SetOsdCol(KEY_R,KEY_R,201, __palette4F(0x0,0x0,0x0,0xff));	// alan, 2003/8/27 10:43AM

			break;		
		case 1:
			start.x =108 ;
    			start.y = 34;	
                     bmp_dimension.x_length = bmp_key_FF[0];
                     bmp_dimension.y_length = bmp_key_FF[1];
                     pbmp = bmp_key_FF + 2;
                
			
			//SetOsdCol(KEY_R,KEY_R,70, __palette4F(0x21,0x84,0x8,0xff));	// alan, 2003/8/27 10:43AM
			break;
		case 2:
			start.x =110 ;
    			start.y = 74;	
                     bmp_dimension.x_length = bmp_key_NEXT[0];
                     bmp_dimension.y_length = bmp_key_NEXT[1];
                     pbmp = bmp_key_NEXT + 2;
                
			
			//SetOsdCol(KEY_R,KEY_R,200, __palette4F(0xa6,0xdc,0x49,0xff));	// alan, 2003/8/27 10:43AM
			break;
		case 3:
			start.x = 64;
    			start.y = 94;	
                     bmp_dimension.x_length = bmp_key_STOP[0];
                     bmp_dimension.y_length = bmp_key_STOP[1];
                     pbmp = bmp_key_STOP + 2;
                
			
			//SetOsdCol(KEY_R,KEY_R,185, __palette4F(0x75,0xc0,0x3c,0xff));	// alan, 2003/8/27 10:43AM
			break;
		case 4:
			start.x = 16;
    			start.y = 74;
                     bmp_dimension.x_length = bmp_key_PREV[0];
                     bmp_dimension.y_length = bmp_key_PREV[1];
                     pbmp = bmp_key_PREV + 2;
                
			
			//SetOsdCol(KEY_R,KEY_R,187,__palette4F(0xa2,0xd3,0x76,0xff));	// alan, 2003/8/27 10:43AM
			break;
		case 5:
			start.x =10 ;
    			start.y = 34;
                     bmp_dimension.x_length = bmp_key_BK[0];
                     bmp_dimension.y_length = bmp_key_BK[1];
                     pbmp = bmp_key_BK + 2;
                
			
			//SetOsdCol(KEY_R,KEY_R,127, __palette4F(0xba,0xfc,0x31,0xff));	// alan, 2003/8/27 10:43AM
			break;
		case 6:
			start.x =64 ;
    			start.y = 16;
                     bmp_dimension.x_length = bmp_key_PAUSE[0];
                     bmp_dimension.y_length = bmp_key_PAUSE[1];
                     pbmp = bmp_key_PAUSE + 2;
                
			break;	
		default:
			break;
	}
    osd_draw_bitmap(KEY_R, &start, pbmp, &bmp_dimension, 4, 1, NULL);     
}

//Show virtual keyboard on osd region KEY_R in default state
void show_virtual_keyboard(void)
{
	KeyID=0;
	osd_init_keyboard();
	//osd_draw_virtual_keyboard(0,0,KEY_R);	
	
	//2005.2.21 joshua, replace osd_draw_virtual_keyboard() by osd_draw_bmp() for using osd driver
	//20050518 WSLEE init the center icon coordinations
        cox=1;
        coy=1;
  
        osd_tog_region(KEY_R, OSD_ON);
        timeout_osd[KEY_R] = 0;
    
        hl_keyboard_button(KeyID);		
}


//Run the related function of selected key 
//WSLEE redefine the key 20050518
extern int is_menu(void);
void virtual_keyboard_select(void)
{
       if(is_menu()){
            invalid_key();
            return;
       }//wangap add 2004/3/3	
	if(KeyID==0)
    {
/*
    	if ( (adv_search_time!=0) && (adv_search_time!=1) )	// alan, 2003/8/26 04:23PM
    		ircmd_play();
    	else
		if((play_state==VCD_STATE_PAUSE)||(play_state==VCD_STATE_STOP))
		{
			if (resumeMSF==0)
				ircmd_play();
			else
				ircmd_resume();
		} else {
			ircmd_pause();
		}
*/
		//WSLEE add this for pause/ff/bk resume 20050518
		if ((play_state==VCD_STATE_PAUSE) | (ff == 1) | (bk == 1))
			call_ir_func(IRC_PLAY_RESUME);
		else
			invalid_key();
		ff = 0; bk = 0;	
    }
    else if(KeyID==1)
    {
    	/*
    	if (play_state!=VCD_STATE_STOP)
    		ircmd_forward();
    	else
    		invalid_key();
    	*/
    	ff = 1;
    	call_ir_func(IRC_FORWARD);
    }
    else if(KeyID==2)
    {
    	/*
    	if (play_state!=VCD_STATE_STOP)
    		ircmd_next();
    	else
    		invalid_key();
    	*/
    	call_ir_func(IRC_NEXT);
    }
    else if(KeyID==3)
    {
    	//ircmd_stop();
    	call_ir_func(IRC_STOP);
    }
    else if(KeyID==4)
    {
    	/*
    	if (play_state!=VCD_STATE_STOP)
    		ircmd_prev();
    	else
    		invalid_key();
    	*/
    	call_ir_func(IRC_PREV);
    }
    else if(KeyID==5)
    {
    	/*
    	if (play_state!=VCD_STATE_STOP)
    		ircmd_backward();
    	else
    		invalid_key();
    	*/
    	bk = 1;
    	call_ir_func(IRC_BACKWARD);
    }
        else if(KeyID==6)
    {
    	/*
    	if (play_state!=VCD_STATE_STOP)
    		ircmd_backward();
    	else
    		invalid_key();
    	*/
    	call_ir_func(IRC_PAUSE);
    }
}

/* WSLEE add new up/down/left/right function for new virutal keyboard 20050518 20:00
*	matrix is like the following structure
*
*	 6
*      / | \
*     5  |  1
*     |  0  |
*     4  |  2
*      \ | /  	
*        3
*/

void virtual_keyboard_up(void)
{

	if(!(keyboard_icon[cox][coy] - 5))
		coy++;
	 else if(!(keyboard_icon[cox][coy] - 1))
		coy--;
	 else if(!(keyboard_icon[cox][coy] - 0) | !(keyboard_icon[cox][coy] - 3))
		cox--;
	 else if(!(keyboard_icon[cox][coy] - 4) | !(keyboard_icon[cox][coy] - 2))	
		cox-=2;
				
	KeyID = keyboard_icon[cox][coy];
	hl_keyboard_button(KeyID);
}

void virtual_keyboard_down(void)
{	
	if(!(keyboard_icon[cox][coy] - 5) | !(keyboard_icon[cox][coy] - 1))
		cox+=2;
	 else if(!(keyboard_icon[cox][coy] - 0) | !(keyboard_icon[cox][coy] - 6))
		cox++;
	 else if(!(keyboard_icon[cox][coy] - 4))
		coy++;
	 else if(!(keyboard_icon[cox][coy] - 2))
		coy--;	
					
	KeyID = keyboard_icon[cox][coy];	
	hl_keyboard_button(KeyID);
}


void virtual_keyboard_left(void)
{
	 if(!(keyboard_icon[cox][coy] - 0)){
		cox--;coy--;
	}	
	 else if(!(keyboard_icon[cox][coy] - 1) | !(keyboard_icon[cox][coy] - 2) | \
	         !(keyboard_icon[cox][coy] - 3) | !(keyboard_icon[cox][coy] - 6))
		coy--;
		
	KeyID = keyboard_icon[cox][coy];
	hl_keyboard_button(KeyID);
}

void virtual_keyboard_right(void)
{
	 if(!(keyboard_icon[cox][coy] - 0)){
		cox--;coy++;
	}	
	 else if(!(keyboard_icon[cox][coy] - 3) | !(keyboard_icon[cox][coy] - 4) | \
	 	 !(keyboard_icon[cox][coy] - 5) | !(keyboard_icon[cox][coy] - 6))
		coy++;
		
	KeyID = keyboard_icon[cox][coy];
	hl_keyboard_button(KeyID);
}
//change selected color in
/*WSLEE mark old left and right functions
void virtual_keyboard_left()
{
	if(KeyID<=0)
		KeyID=6;
	else
		KeyID--;
	hl_keyboard_button(KeyID);
}

void virtual_keyboard_right()
{
	if(KeyID>=6)
		KeyID=0;
	else
		KeyID++;
	//osd_init_key();
	hl_keyboard_button(KeyID);
}
*/

#endif


