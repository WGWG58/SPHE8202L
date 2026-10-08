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
|  File Name   :  book.c
|
|  Description :  it's book mark function Interface,must define SUPPORT_BOOK,
|                 it can be used;  
|                  
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2001/5/15s        Kenny        Creating
|--------------------------------------------------------------------------------*/


/*****************************************************\
Creater: Kenny
Date   : 2001/5/15 02:39PM
Description: Search menu using 
\*****************************************************/

#include "user_init.h"

#ifdef SUPPORT_BOOK

#include "global.h"
#include "osd.h"
#include "func.h"
#include "cfont.h"
#include "util.h"
#include "user_if.h"
#include "stdlib.h"

//#define   BOOK_DBG    1

//#define BOOK_MODE		2
//#define BOOK_Y_ITEM		2
//#define BOOK_X_ITEM		3
//#define NO_ANTI			0
//#define ANTI			2
//#define ST_REGION REGION2

extern void DispUpdateMark(BYTE xStart, BYTE *pStr, BYTE bFocus);
extern int is_menu(void);

void mark_UpdateOSD();
void mark_GetValidString(BYTE *strBook);

BYTE    bookIndex;      //Jeff 20020518
/**************************************************************************
 *                                                                        *
 *  Function Name: record_book                                            *
 *                                                                        *
 *  Purposes:                                                             *
 *    record information                                                  *
 *  Descriptions:                                                         *
 *    record some useful information ,for example                         *
      tiele and chapter for dvd                                           *
 *  Arguments:    NONE                                                    *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void record_book()
{
        BYTE i;

        i = bookIndex;    	
  	
        if (i<BOOK_MAX_ITEM) {
                book_tm[i]=disp_time;        
                if (cd_type_loaded==CDDVD) {
                        book[i][0]=get_tt_info(DISP_TT);//dvd_title
                        book[i][1]=get_tt_info(DISP_CH);//dvd_chapter;	        	        	        
                } else if ( psd_state!=(PSD_SEL_LIST|PSD_PLAY_SEG)) {        
                        book[i][0]=cd_trk_now;		        
                }
	    
                RSM_save(0xff,i+1);
        }
}

//Jeff 20020411
void book_cancel(void)
{
}
/*
void book_func_up(void)
{
        //printf("book_func_up\n");
}

void book_func_down(void)
{
        //printf("book_func_down\n");
}*/
/**************************************************************************
 *                                                                        *
 *  Function Name: mark_func_right                                        *
 *                                                                        *
 *  Purposes:                                                             *
 *    HL turn right                                                       *
 *  Descriptions:                                                         *
 *    HL turn right                                                       *
 *  Arguments: NONE                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void mark_func_right()
{
        if (bookIndex < (BOOK_MAX_ITEM-1) ) {
                bookIndex++;
                mark_UpdateOSD();
        }
        //printf("mark_func_right:bookIndex=%d\n", bookIndex);
}

void mark_func_left()
{
        if (bookIndex > 0) {
                bookIndex--;
                mark_UpdateOSD();
        }

        //printf("mark_func_left:bookIndex=%d\n", bookIndex);
}

extern void invalid_key(void); // in ircmd.c
//Jeff 200204112
/**************************************************************************
 *                                                                        *
 *  Function Name: book_func_select                                       *
 *                                                                        *
 *  Purposes:                                                             *
 *    book function was select that use enter key                         * 
 *  Descriptions:                                                         *
 *     according to the different states ,the                             *
 *     book function was select that use enter key                        * 
 *  Arguments: VOID                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void book_func_select(void)
{
	//printf("book_func_select:bookIndex=%d, play_state=%x\n", bookIndex, play_state);
#ifdef PULIANG_DVD  //yaowh add 04-12-17
    if(book[bookIndex][0]) 
    {
        if(play_state==VCD_STATE_PAUSE)
            {ircmd_play();}
        else
        {
            book_func_play();
            book_func_clear();
		}
        return;
    }
#endif
	//terry,2004/1/30 03:11PM
	if( (play_state == VCD_STATE_STOP)||is_menu()||((cd_type_loaded!=CDDVD)&&((cd_trk_now<cd_trk_lo_now)||(cd_trk_now>cd_trk_hi))) )
	{
		invalid_key();
		return;
	}
#ifdef SHOW_BOOKMARK_TIME//libing 2005-6-16 23:55
	if(book[bookIndex][0]==0) 	
	{	
#endif
		record_book();
		mark_UpdateOSD();
#ifdef SHOW_BOOKMARK_TIME	
	}	
	else
	{
		book_func_play();
	}
#endif		
}

#ifdef FUSS_DVD
#if defined(FUSS_PANEL)||defined(FUSS2_PANEL)
extern BYTE book_flag;
#endif
#endif
//Jeff 200204112
/**************************************************************************
 *                                                                        *
 *  Function Name: book_func_play                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    use play key to play the book mark                                  *
 *  Descriptions:                                                         *
 *    use play key to play the book mark                                  *
 *  Arguments: NONE                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void book_func_play()
{
        UINT32 c;

        //printf("book_func_play\n");

        if(book[bookIndex][0]) {
            
                #ifdef CANCEL_PRG_WHEN_BOOKMARK     //linrc 2004-6-9 13:37
                if (prog_cnt)
                {
                    prog_func_clear();
                    prog_func_off();                  
                    prog_cnt = 0; 
                    ircmd_book();   //I call this function again in order to build the bookmark parameter again.
                }
                #endif 
                if(rep_ab_mode != REPEAT_IDLE) // 2004-5-10 15:34 linrc add for when bookmark play that REPEAT=IDLE
                {
		            rep_ab_mode = REPEAT_AB_IDLE;
		            show_repeatAB(1);
	            }
                
                NCMD_exec_RSM(bookIndex+1);       //Jeff 20020411
                if(cd_type_loaded==CDDVD) {
                        c=CMD_FUNC | CMD_FUNC_BOOK;
                } else {
                        if ( IsPBCOn() ) {
                                pbcoff_init();	       	       
                        }/* else {	//Jeff 20020418
                        	psd_state=0;
                        }*///2002-4-26
                        resumeTRK=book[bookIndex][0];
                        c=CMD_FUNC | CMD_FUNC_RESUME;            
                        goto_active = 1;//nono 2003-10-27 13:48 avoid ntsc->pal pic size error.            
                #ifdef FUSS_DVD        
	            #if defined(FUSS_PANEL)||defined(FUSS2_PANEL)
	                book_flag=bookIndex+1; //2002-6-24 for fuss          
                    #endif
                #endif
                }

                ircmd_post_func(c);

                if (user_mute) {    //restore MUTE OSD, Jeff 20020522
                    PrintOsdMsg(STR_OS_MUTE,REGION1,0,0);
                }
        }
}

/**************************************************************************
 *                                                                        *
 *  Function Name: book_func_clear                                        *
 *                                                                        *
 *  Purposes:                                                             *
 *    clear the book mark information and refresh  the osd display        *
 *  Descriptions:                                                         *
 *    clear the book mark information and refresh  the osd display        *
 *  Arguments: void                                                       *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void book_func_clear(void)
{
        //printf("book_func_clear\n");
        book[bookIndex][0]=0;   
        book_tm[bookIndex]=0;//LIBING 2005-6-21 15:44  
        mark_UpdateOSD();
}
/**************************************************************************
 *                                                                        *
 *  Function Name: mark_UpdateOSD                                         *
 *                                                                        *
 *  Purposes:                                                             *
 *    display book function bar on screen                                 *
 *  Descriptions:                                                         *
 *    display book function bar on screen                                 *
 *  Arguments:    NONE                                                    *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void mark_UpdateOSD()
{
        BYTE    strBook[20];
        BYTE    strTemp[20];

        mark_GetValidString(strBook);

        if (bookIndex > 0) {
                strcpy(strTemp, strBook);
                strTemp[bookIndex]=0;
                DispUpdateMark(0, strTemp, 0);
        }

        strTemp[0] = strBook[bookIndex];
        strTemp[1] = 0;
        DispUpdateMark(bookIndex, strTemp, 1);

        if (bookIndex < (BOOK_MAX_ITEM-1) ) {
                strcpy(strTemp, strBook+bookIndex+1);
                DispUpdateMark(bookIndex+1, strTemp, 0);
        }
}
/**************************************************************************
 *                                                                        *
 *  Function Name: mark_GetValidString                                    *
 *                                                                        *
 *  Purposes:                                                             *
 *    draw the "_" on the book bar                                        *
 *  Descriptions:                                                         *
 *    draw the "_" on the book bar                                        *
 *  Arguments:    array address strBook                                   *
 *  Returns:   NONE                                                       *
 *                                                                        *
 *  See also:  NONE                                                       *
 *                                                                        *
 **************************************************************************/
void mark_GetValidString(BYTE *strBook)//LIBING 2005-4-26 23:41
{
        int     i;
        #ifndef SHOW_12_BOOKMARK
		for (i=0; i<BOOK_MAX_ITEM; i++) {
                if (book[i][0]) {
                        strBook[i] = i+'1';
                } else {
                        strBook[i] = '-';
                }
        }
        #else//#ifndef SHOW_12_BOOKMARK
        for (i=0; i<BOOK_MAX_ITEM; i++) {
                if (book[i][0]) {
                	if(i<9)
                    {
                        strBook[i] = i+'1';
                    }else if(i==9)
                    {
                    	strBook[i] = 'A';
                    }	
                    else if(i==10)
                    {
                    	strBook[i] = 'B';
                    }	
                    else if(i==11)
                    {
                    	strBook[i] = 'C';
                    }	
                        
                } else {
                        strBook[i] = '-';
                }
        }
        #endif//#ifndef SHOW_12_BOOKMARK
        strBook[i] = 0;
}
#ifdef SHOW_12_BOOKMARK//libing 2005-6-29 21:59
void cancel_bookmark()
{
	int e;
	for(e=0;e<12;e++)
	{
		book[e][0]=0;
		book_tm[e]=0;
		mark_UpdateOSD();
	}
}
#else	//hongfeng 2005-08-22
void cancel_bookmark()
{
	int e;
	for(e=0;e<5;e++)
	{
		book[e][0]=0;
		book_tm[e]=0;
		mark_UpdateOSD();
	}
}
#endif//#ifdef SHOW_12_BOOKMARK//libing 2005-6-29 21:59
//#ifdef support_book
#else	//support_book
//void mark_GetValidString(BYTE *strBook) {}
void mark_UpdateOSD() {}
void book_func_clear() {}
void book_func_play() {}
void mark_func_right() {}
void mark_func_left() {}
void book_func_select() {}
#endif	//support_book


