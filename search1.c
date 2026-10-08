/**********************************************************************\
Creater: Kenny
Date   : 2002/4/10 02:39PM
Description: Search menu using 
Record:  2004.04.28 Maoyong
    ***Marked MP3_DIRECT_PLAY definiton so that MP3 can be choosed ranged 
       in all tracks no matter whether defined MP3_DIRECT_SELECT.
    ***Just for no DIV_GOTO_DISPLAY
         void search_func_right(void)
         void search_func_input(void) 
         void search_add_num(int *v,int pos)
\***********************************************************************/

#include "global.h"
#include "osd.h"
#include "func.h"
#include "cfont.h"
#include "util.h"
#include "ircmd.h"
#include "user_if.h" //add by shawn 20020219
#include "asf_if.h"
#ifdef SUPPORT_DISPLAY_MENU
#include "setup_def.h"
#endif
#ifdef SUPPORT_JPEG_GOTO //Just as the name.Jack added 04/11/16
#include "fsNAV.h"
#endif
#ifdef SUPPORT_MP4
#include "file_if.h"    //ycwen 2005/12/8
#endif
#include "cardfs.h"

#define DISCTIME_SEARCH     1
#define TRACKTIME_SEARCH    2

#ifdef  MP3_SEARCH_FAST2NORM        //Maoyong 2004.02.25
#define FAST2NORM           0x01<<0     //Maoyong 2004.02.25
#define NOT_REALPLAY        0
extern void chg2normal_play(UINT8 md,UINT8 realplay);
extern UINT16 Is_JPEG_STATE(void);
#endif
#ifdef DIV_GOTO_DISPLAY
extern BYTE SearchPage;
#endif

#ifdef SUPPORT_JPEG_GOTO
extern void FSGUI_JpgUpdateOSD(void);//for warning
extern void set_rtc_val(UINT32);
#endif

#ifdef SUPPORT_CDG //Jeff 20020824
#include "cdg.h"
extern UINT8   bReadSubChannel;
#endif

extern UINT32 myTime,_myTime;//terry,2003/6/24 10:53上午
extern UINT32 oldmp3ReadLen,_mp3ReadLen;
extern UINT8 is_ptt_search(void);       // 2005/06/28 yltseng
extern UINT8 is_time_search(void);
extern void tm2hms(UINT32 time,UINT8 *h,UINT8 *m,UINT8 *s); // in disp.c
extern UINT16 mp3_file_count(void);
extern BYTE GetCurrentFileType();
extern void ShowSearchPage(BYTE page,BYTE need_hi);
extern UINT8 GetTotalTrk(UINT8);
extern int AUDIF_Set_Stop();

#ifdef PMP_DVD //kenny 2005/7/29
extern void HDDCard_number_input(int num);
extern void pmp_enable_user_flag(UINT32 i);//kenny 2005/8/3
#include "fsNAV.h"
#endif

#if defined(MP3_GOTO_FILE_IN_AREA_DIR)//chenzhao 2006-4-10 20:35 .
#include "fsNAV.h"
#endif


void preDealGoto_time(void)//xyy 2003-7-29 13:16
{
    goto_time=(goto_hour*3600+goto_min*60+goto_sec);
    //disp_time=goto_time;//20040228
    //terry,2002/7/17 02:13PM, bad disc show time err
    if(cd_type_loaded==CDSVCD)
        goto_time=goto_time*PLAY_SPEED;
#ifdef NEWSTYLE_WINDOW
    if(full_scrn&MESSAGE)
        if((goto_time>disc_time)||(goto_min>60)||(goto_sec>60))//axel 2004/1/27 10:00pm return while min>60 or sec>60
            goto_time = 0;
#endif
#ifdef DIV_GOTO_DISPLAY
    if(full_scrn&GOTO)
        if((goto_time>disc_time)||(goto_min>60)||(goto_sec>60))//axel 2004/1/27 10:00pm return while min>60 or sec>60
            goto_time = 0;
#endif
   
    
    tm2hms(goto_time,&goto_hour,&goto_min,&goto_sec);                
}

#if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
extern UINT32 nGotoPck;
#endif


#if !defined( NEW_SEARCH_OSD ) && !defined( DIV_GOTO_DISPLAY )

enum
{
    SEARCH_POSITION_INIT,
    SEARCH_DIRECTION_RIGHT,
    SEARCH_DIRECTION_LEFT,
};

#ifdef SUPPORT_DIVX6
extern UINT32 is_divx6_file;
#endif  //#ifdef SUPPORT_DIVX6

int  srhGetSearchPosition( UINT32 uiType, UINT32 uiDir, int iIdx )
{   // 2005/07/05 yltseng
    if( uiDir == SEARCH_POSITION_INIT )
    {
    #ifdef SUPPORT_DIVX6
        if(is_divx6_file)
        {
            iIdx = 5; //allow goto time only
        }else
    #endif  //#ifdef SUPPORT_DIVX6
    #ifdef ORITRON_HK_DVD
	 	if (cd_type_loaded == CDROM)//libing 2005-7-19 17:10
	        iIdx = 2; 
	    else
	#endif    
        iIdx = 0;
        
        if( uiType == CDDVD )
        {
            if( UOP_check(UOP_TT_P) )
            {
                if( is_ptt_search() )
                    iIdx = 2;
                else if( is_time_search() )
                    iIdx = 5;
            }
        }

        return iIdx;
    }
    else if( uiDir == SEARCH_DIRECTION_RIGHT )
    {
        iIdx++;
        if( iIdx > 10 )
        {
        #ifdef SUPPORT_DIVX6
            if(is_divx6_file)
            {
                iIdx = 5;  //do not goto chapter selection
            }
            else
        #endif  //#ifdef SUPPORT_DIVX6
        #ifdef ORITRON_HK_DVD
            if (cd_type_loaded == CDROM)//libing 2005-7-19 17:10 
                iIdx = 2;     
            else
        #endif    
            {
                iIdx = 0;    
            }
        }
    }
    else
    {
        iIdx--;
    #ifdef SUPPORT_DIVX6
        if(is_divx6_file)
        {
            if( iIdx < 5 ) //do not goto chapter
                iIdx = 10; //to the last digit of time display
        }
        else
    #endif  //#ifdef SUPPORT_DIVX6
    #ifdef ORITRON_HK_DVD
	    if (cd_type_loaded == CDROM)//libing 2005-7-19 17:10
	    {
            if(iIdx < 2)
                iIdx = 5;
        }
	    else
	#endif    
        {	
            if( iIdx < 0 )
                iIdx = 5;
        }
    } 
    
    switch( uiType )
    {
    case CDDVD:
    {
        UINT32 uiTitleProhibit  = UOP_check(UOP_TT_P);
        UINT32 uiPttProhibit    = !is_ptt_search();
#ifdef DVD_AUDIO
        UINT32 uiTimeProhibit   = ( !is_time_search() ) && ( dAMG_LSN == 0 );
#else
        UINT32 uiTimeProhibit   = !is_time_search();
#endif
    
        if( uiTitleProhibit && uiPttProhibit && uiTimeProhibit )
            return 0;
    
        if( uiDir == SEARCH_DIRECTION_RIGHT )
        {
            if( iIdx == 0 && uiTitleProhibit )
                iIdx = 2;
        
            if( iIdx == 2 && uiPttProhibit )
                iIdx = 5;
        
            if( iIdx == 5 && uiTimeProhibit )
                iIdx = 0;
        
            if( iIdx == 0 && uiTitleProhibit )
                iIdx = 2;
        }
        else
        {
    
            if( iIdx == 1 && uiTitleProhibit )
                iIdx = 5;
        
            if( iIdx == 5 && uiTimeProhibit )
                iIdx = 4;

            
            if( iIdx == 4 && uiPttProhibit )
                iIdx = 1;   
        
            if( iIdx == 1 && uiTitleProhibit )
                iIdx = 5;
        }
    }    
        break;

    case CDROM:
    {
#ifdef SUPPORT_JPEG_GOTO
        if( pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG && iIdx > 3 )
        {
            iIdx = ( uiDir == SEARCH_DIRECTION_RIGHT ) ? 0 : 3;
        }
        else
#endif
        {
            if( ( iIdx == 4 ) && ( uiDir == SEARCH_DIRECTION_RIGHT ) )
                iIdx = 5;
            #ifdef ORITRON_HK_DVD                   
	            else
	            if( ( iIdx == 11 ) && ( uiDir == SEARCH_DIRECTION_RIGHT ) ) //libing 2005-7-26 13:58
	            					iIdx = 2;
	        #endif    					        
            goto CHECK_LEFT;
        }
    }
        break;

#ifdef SUPPORT_CDG
    case CDDA:
    {
        if( ( iIdx == 2 ) && ( uiDir == SEARCH_DIRECTION_RIGHT ) )
        {
            if( ( CDG_IsCDGNow() && ( cd_subtype != CD_DTS ) ) )
                iIdx = 0;
            else
                iIdx = 5;
        }
        else
        {
            goto CHECK_LEFT;
        }
    }
        break;
#endif

    default:
    {
        if( ( iIdx == 2 ) && ( uiDir == SEARCH_DIRECTION_RIGHT ) )
            iIdx = 5;

CHECK_LEFT:
        if( ( iIdx == 4 ) && ( uiDir == SEARCH_DIRECTION_LEFT ) )
        {
        	#ifdef ORITRON_HK_DVD
	            if (cd_type_loaded == CDROM)//libing 2005-7-19 17:10
	            	iIdx = 2; 
	            else
                #endif
            iIdx = 0;
    }
    } 
    break;        
    }

    return iIdx;
}

void srhProcessDirection( UINT32 uiDir )
{   // 2005/06/28 yltseng
    index_x = srhGetSearchPosition( cd_type_loaded, uiDir, index_x );
    
    if( index_x < 5 )
    {
        goto_time   = 0;        
    }
    else    
    {
#ifndef GOTO_TIME_DNOT_CLEAR_TITLE_CHAP
        dvd_title   = 0;
        dvd_chapter = 0;
#endif
    }

#ifdef SUPPORT_JPEG_GOTO
    if( pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG )
    {
        //if( !pFsJpeg->gbfsSlide )
            FSGUI_JpgUpdateOSD();
        if(pFsJpeg->gbfsSlide)
            set_rtc_val(0);
            
    }
#endif
#ifdef PMP_DVD //kenny 2005/8/3
extern void PMP_UpdateGotoOSD(void);
PMP_UpdateGotoOSD();
#endif
    
}
#endif

/*
 * Function name:
 *         exe_timesearch_func
 *
 * NOTE:
 *    inital function form is void exe_timesearch_func(UINT32 goto_ff,UINT32 fail)
 *
 *    to make VCD time search function  more effect I modify the function 
 *
 *  INPUT :(for VCD)
 *     
 *     mode = 1:  disc time  search 
 *          = 2:  track time search
 * zhaoyanhua 2003-12-6 14:51
 */
void exe_timesearch_func(UINT32 goto_ff,BYTE mode __attribute__((unused)))
{
    UINT16 leadin_ff = 0;
    UINT16 leadout_ff= 0;
    BYTE   fail = 0;
    BYTE   temp_goto_time;
    
    printf("---------------exe TIME SEARCH-------------------\n");
    temp_goto_time = goto_time;
    //Steven 2006/6/1 add (GetCurrentFileType() == CDROM_AAC) for aac audio time search func//
    if ((GetCurrentFileType() == CDROM) || (GetCurrentFileType() == CDROM_AAC))
    {//terry,2003/6/24 10:53上午
        extern UINT32 PlayBackLength;
        UINT32 totaltime,len;

        #ifdef PMP_DVD //kenny 2005/8/3
        totaltime = PlayBackLength * 4/ Mp3_kbitrate;
    #else   //!PMP_DVD
        #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
        if(media_type == MEDIA_CARD)
        {
            extern CARD_INFO   cardP;
            totaltime = PlayBackLength * cardP.bytePerSec * 8 /1024 / Mp3_kbitrate;
        }else
        #endif  //#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
        {
            totaltime = PlayBackLength * 16/ Mp3_kbitrate;
        }
    #endif  //#ifdef PMP_DVD

        if(goto_time>totaltime)
        {
            fail = 1;
            goto_time = 0;
        }else
        {
            _myTime = goto_time<<16;
            len = (goto_time*Mp3_kbitrate)/16;
            goto_time = len;
            //printf("_myTime:%d\n",_myTime);
        }
    }
#if defined (SUPPORT_FILE_SYSTEM_MODE) && defined (SUPPORT_MP4)
    else if (GetCurrentFileType() == CDROM_MP4)
    {
		if(!IS_FILE_TYPE_ASF())
		{    
	        extern UINT32 file_len;
	        if ((goto_time > file_len) || (adv_search_time) || (play_state == VCD_STATE_MP3_FILELIST))
	        {
	            goto_time = 0;
	            fail = 1;
	            printf("#####--GOTo_TIME to big,goto_time %d fail: %d!\n",goto_time,fail);
	        }
	        else
	            nGotoPck = goto_time;
    	}
    #if defined(SUPPORT_WMA) || defined(SUPPORT_ASF)
		else			
		//now wma file use GetCurrentFileType() is CDROM_MP4
		//add by roger 06-04-18
		{
	//        printf("asf_file_duration: %d\n",asf_file_duration);//unit: 100 nano sec
	        
	        if (goto_time > (asf_file_duration / (1000*10000)))
	        {
	            goto_time = 0;
	            fail = 1;
	            printf("#####--GOTo_TIME to big,goto_time %d fail: %d!\n",goto_time,fail);
	        }
	        else
	        {
	            if (!asf_pck_count)
	            {
	                fail = 1;
	                goto_time = 0;
	            }
	            else
	            {
	            	nGotoPck = goto_time;
	            }
			}
		}
    #endif  //#ifdef SUPPORT_ASF
    }
#endif
#ifdef SUPPORT_WMA//zhaoyanhua add 2003-11-18 9:11
    else if (GetCurrentFileType() == CDROM_WMA)
    {
        UINT32 one_packet_time = 0;
        
        //printf("asf_pck_count: %d\n",asf_pck_count);
        //printf("goto_time: %d\n",goto_time);
        //printf("asf_file_duration: %d\n",asf_file_duration);
        
        if (goto_time > (asf_file_duration / 1000))
        {
            goto_time = 0;
            fail = 1;
            printf("#####--GOTo_TIME to big,goto_time %d fail: %d!\n",goto_time,fail);
        }
        else
        {
            if (!asf_pck_count)
            {
                fail = 1;
                goto_time = 0;
            }
            else
            {
                one_packet_time = asf_file_duration / asf_pck_count;
                printf("one_packet_time: %d\n", one_packet_time);

                //goto_time/one_packet_time: goto_time -> WMA packet
                nGotoPck = goto_time * 1000 / one_packet_time;
                printf("nGotoPck = %d\n", nGotoPck);
            }
        }
    }
#endif
    else if(cd_type_loaded!=CDDVD)
    {
        //printf("1.GOTO hh=%d, mm=%d, ss=%d, ff=%d,lin=%d, lout=%d\n",goto_hour,goto_min,goto_sec,goto_ff,leadin_ff,leadout_ff);
#if defined(DIV_GOTO_DISPLAY)||defined(MODIFY_OSD_SHOW_NEW_STYLE_WINDOW)
        if((full_scrn&GOTO)||(full_scrn&MESSAGE))
        {
        switch(mode)
        {
            case DISCTIME_SEARCH: //select time in charpter
                leadin_ff  = msf_mm(gettrkmsf(1))*60 \
                        +msf_ss(gettrkmsf(1));
                leadout_ff = msf_mm(gettrkmsf_leadout())*60 \
                        +msf_ss(gettrkmsf_leadout());   
                goto_time=MSF(((UINT32)goto_hour*60+(UINT32)goto_min),goto_sec,0x0)+(gettrkmsf(cd_trk_lo_now)&0x00ffffff);
                printf("--exe_func cd_trk_lo_now = %d  ,goto_time = %d--\n",cd_trk_lo_now,goto_time);
                break;
            case TRACKTIME_SEARCH://
                leadin_ff =msf_mm(gettrkmsf(cd_trk_now))*60 \
                        +msf_ss(gettrkmsf(1));  
                leadout_ff =msf_mm(gettrkmsf(cd_trk_now+1))*60 \
                        +msf_ss(gettrkmsf(cd_trk_now+1));   
                goto_time=MSF(((UINT32)goto_hour*60+(UINT32)goto_min),goto_sec,0x0)+(gettrkmsf(cd_trk_now)&0x00ffffff);             
                break;
            default:break;
        }
        }
        else
        {
#endif//end DIV_GOTO_DISPLAY and MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
            leadin_ff  = msf_mm(gettrkmsf(1))*60 \
                        +msf_ss(gettrkmsf(1));
            leadout_ff = msf_mm(gettrkmsf_leadout())*60 \
                        +msf_ss(gettrkmsf_leadout());   
                    
        #ifdef VCD_GOTO_FROM_MENU_END//Jack added!!!!!
        if((cd_type_loaded==CDVCD20) || (cd_type_loaded==CDVCD10))
            goto_time = MSF(((UINT32)goto_hour*60+(UINT32)goto_min),goto_sec,0x0)+(gettrkmsf(cd_trk_lo_now+1)&0x00ffffff); 
        else
        #endif					
        goto_time = MSF(((UINT32)goto_hour*60+(UINT32)goto_min),goto_sec,0x0)+(gettrkmsf(cd_trk_lo_now)&0x00ffffff);
#if defined(DIV_GOTO_DISPLAY)||defined(MODIFY_OSD_SHOW_NEW_STYLE_WINDOW)    
        }
#endif//DIV_GOTO_DISPLAY
            
        goto_ff = ((goto_time>>16)&0xffff)*60+msf_ss(goto_time);
                    
                    if(  goto_ff > leadout_ff ||goto_ff <leadin_ff   )       // leadout area
        {
            //printf("2.GOTO hh=%d, mm=%d, ss=%d, ff=%d, lin=%d, lout=%d\n",goto_hour,goto_min,goto_sec,goto_ff,leadin_ff,leadout_ff);
            fail=1;
            goto_time=0;//  fengjl add 3-12-24 10:30 to clear random digits when input error time
        }
                    
                    
    } //if(cd_type_loaded==CDDVD)
    
    if(!fail)
    {
        {//auto pbc off
            pbcoff_init();
        }
#if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
        if ((GetCurrentFileType() != CDROM_WMA) && (GetCurrentFileType() != CDROM_MP4)) // Robert 031119, don't leave mediamainloop when WMA
#endif
           ircmd_post_func(CMD_FUNC | CMD_FUNC_GOTO);
    //disp_time = temp_goto_time;
    disp_time = 0xffff; // 
    /* axel 20041130
    Note: DVD time_search, disp_time might show garbage.
          Some circumstance made disp_time showed garbage second information when DVD time_searching.
          disp_time sets 0xffff is just setting a flag to DVD_show_time(void) in nav.c .
     */     
    /*Maoyong 2004.02.26 
     Note:  for consistence operation of DVD/VCD/CD/MP3.In FF/FB play mode, do
            time and track search play should change to normal play state
     Maybe, it will be treated as a BUG sometimes!!!      
    */
    #ifdef  MP3_SEARCH_FAST2NORM
    if((cd_type_loaded == CDROM) && (!Is_JPEG_STATE()) )   
            chg2normal_play(FAST2NORM, NOT_REALPLAY);
    #endif  //#ifdef    MP3_SEARCH_FAST2NORM
    }
    
}

void search_func_select(void)
{
    UINT32 goto_ff=0,fail=0;        //wanghaoying 2003-8-12 19:48 initialize the parameter "goto_ff"
    
    printf("index_x = %d , goto_time = %d, search_func_select in s1\n", index_x, goto_time);
#ifdef NEW_SEARCH_OSD  //yw 021004
    if(t_disp%10 == 1)
    {
#endif

        if(index_x>=5)      //For time search
        {           
#ifdef NEW_SEARCH_OSD
            goto_time = disp_goto_time;
#endif
            {
/*
                goto_time=(goto_hour*3600+goto_min*60+goto_sec);
                disp_time=goto_time;
                //terry,2002/7/17 02:13PM, bad disc show time err
                if(cd_type_loaded==CDSVCD)
                    goto_time=goto_time*PLAY_SPEED;   
                
                tm2hms(goto_time,&goto_hour,&goto_min,&goto_sec);                
*/
                preDealGoto_time(); //xyy 2003-7-29 13:16 
                
            #ifdef DIV_GOTO_DISPLAY 
                BYTE search_mode = 0;
                
                if(!goto_time)
                    fail = 1;
                else //only goto_time!= 0, to excute.            
                {
                    
                    //if(  (cd_type_loaded == CDVCD10)||(cd_type_loaded ==CDVCD20)||(cd_type_loaded == CDSVCD))zhaoyanhua mask it 2004-2-3 15:48
                    //all disc support DISCTIME_SEARCH and TRACKTIME_SEARCH
                    {
                        switch(SearchPage)
                        {
                            case 1:
                                search_mode  = DISCTIME_SEARCH;    
                                break;
                            case 2:
                                search_mode =  TRACKTIME_SEARCH;                               
                                break;    
                        }               
                    }
          
                    exe_timesearch_func(goto_ff,search_mode);
                }               
            #else
                exe_timesearch_func(goto_ff,fail);//xyy 2003-7-29 13:24
                #endif
           
           
            #if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
                //WMA does not excute in exe_timesearch_func immediately,
                //but it deal with goto_time,so need check if GOTO is valid.
                if(!goto_time)
                    fail = 1;                
            #endif
                              
            } //if(goto_hour!=0xff)
            
#ifdef NEW_SEARCH_OSD
            // YW Modify 020808
            disp_goto_time = 0;
#endif 
            
        }else
        {
            if(cd_type_loaded==CDDVD)
            {

#ifdef DIV_GOTO_DISPLAY 
                if((!dvd_title) && (index_x == 1))
#else//#ifdef DIV_GOTO_DISPLAY  
                if(!dvd_title)
#endif//#ifdef DIV_GOTO_DISPLAY 
                {
#ifdef DVD_AUDIO                                // alan, 2002/11/11 02:23下午
                    if ((pDSV->tt_info.dTT_PB_TY)&0x80)
                        dvd_title=NP_ATT_GRN;
                    else
#endif
                        dvd_title=NP_TTN;                   
#ifdef DIV_GOTO_DISPLAY                 
                    fail = 1;
#endif//end DIV_GOTO_DISPLAY 
                }

#ifdef DIV_GOTO_DISPLAY              //zhaoyanhua add 03-11-6 11:44
                if((!dvd_chapter) && (index_x ==4))
                {//terry,3-8-23 19:35
#ifdef DVD_AUDIO                                // alan, 2002/11/11 02:23下午
                    if ((pDSV->tt_info.dTT_PB_TY)&0x80)
                        dvd_chapter=NP_TKN;
                    else
#endif
                        dvd_chapter=NP_PTTN;
                    fail = 1;
                }
#endif
                if(UOP_check(UOP_PTT_PS)&&(dvd_chapter==1))
                  dvd_chapter = 0;//TT play,terry,3-8-23 19:35
                  
#ifdef DIV_GOTO_DISPLAY              //zhaoyanhua add 03-11-6 11:45
                if(!fail)
#endif
                {
                    #if 0 //zhaoyanhua mask it 2004-2-24 16:10
                    //to solve the problem: when panasonic disc, can not select title.
                    // so mask these sentence.
                    if((index_x == 1)&&(dvd_title))
                        dvd_chapter = 1;//to avoid the bug when TITLE:CHAPTER,not excute PTT_PLAY zhaoyanhua 2003-11-29 19:38                    
        #endif
                    
          
                ircmd_post_func(CMD_FUNC|CMD_PTT_PLAY);
    
                }

            } else 
#ifdef NEW_SEARCH_OSD//terry,2003/6/24 10:53上午
                if(!((index_x>1)&&(index_x<5)))
#endif //NEW_SEARCH_OSD             
                {
                    
                    //terry,2002/5/9 10:24下午
                    //current track play
                    if((!dvd_title)
                #ifdef DIV_GOTO_DISPLAY 
                    &&(index_x == 1)
                #endif
                    )
                    {   
                    	#ifdef GOTO_TRK_0_INVLIDE_KEY //zxb 2005/09/20
                    	invalid_key();
                    	return;
                    	#endif
                    	
                        dvd_title=disp_trk_now;
                    #ifdef DIV_GOTO_DISPLAY     
                        fail = 1;
                    #endif
                    }
                    if(cd_type_loaded==CDROM)
                    {//terry,2003/6/24 10:53上午
                        //printf("==>dvd_title:%d\n",dvd_title);
                        if(dvd_title <= mp3_file_count())
                        {
                            //printf("dvd_title:%d\n",dvd_title);
                             /*Maoyong 2004.02.26 
                            Note:  for consistence operation of DVD/VCD/CD/MP3.In FF/FB play mode, do
                            time and track search play should change to normal play state
                            Maybe, it will be treated as a BUG sometimes!!!
                            */
                            #ifdef  MP3_SEARCH_FAST2NORM
                            if((cd_type_loaded == CDROM) && (!Is_JPEG_STATE()) )  
                            chg2normal_play(FAST2NORM, NOT_REALPLAY);
                            #endif  //#ifdef    MP3_SEARCH_FAST2NORM
                                            
                           //kenny 2005/8/3
                            #ifdef PMP_DVD
                            if(GetCurrentFileType() != CDROM_MP4)
                            {
                            ircmd_post_func(CMD_SELECT | dvd_title); 
                            HDDCard_number_input(dvd_title);
                            }
                            else
                            {
                                
                            pmp_enable_user_flag(PMP_USER_ENTER_SEARCH_TRACK); 
                            ircmd_post_func(CMD_FUNC | CMD_FUNC_TIMEOUT);    
                                
                            }   
                            #else
                            {
                                #if defined(MP3_GOTO_FILE_IN_AREA_DIR)&& !defined(MP3_DIRECT_SELECT)//chenzhao 2006-4-10 20:35 .
                                if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
                                     pFsJpeg->ControlArea = CNT_AREA_FILE;
                                #endif
                             ircmd_post_func(CMD_SELECT | dvd_title); 
                            }
                            #endif
                            
                        }
            #if 0//def SUPPORT_MP4//nono 4-9-3 20:03 when normal-play, GOTO track will show "INVALID KEY".
                        if ((GetCurrentFileType() == CDROM_MP4) && (play_state != VCD_STATE_MP3_FILELIST))
                            fail = 1;
            #endif
                    }else if( (dvd_title<=cd_total_trk()) && (dvd_title>=cd_trk_lo) )  
                    {                   
                        {//auto pbc off
                            pbcoff_init();
                        }
                        
                    #ifdef DIV_GOTO_DISPLAY
                        if(!fail)
                    #endif  
                        ircmd_post_func(CMD_SELECT | dvd_title);
                    }
                    else
                    {
                        fail=1;
                    }
                }
        }
        
        #ifdef SUPPORT_DISPLAY_MENU
        if(In_Goto_Menu())
          return;
        #endif//end #ifdef SUPPORT_DISPLAY_MENU

#ifndef NEW_SEARCH_OSD
        //#else
    #ifndef DIV_GOTO_DISPLAY
#ifdef NEW_DISPLAY_GOTO_OSD
            t_disp=2;
#endif
        ircmd_goto();
        #ifdef  MP4_PAUSE_OR_STEP_STATE_PRESS_GOTO_CAN_NOT_CHG2PLAYMODE  //wangshf  2005-7-25 23:17
        if((play_state == VCD_STATE_PAUSE) && ( cd_type_loaded == CDROM ) && ( GetCurrentFileType() == CDROM_MP4 )){
            chg2normal_play( 0x07, 0 ); 
            play_state = VCD_STATE_NORMAL;
        }   
        #endif  
    #endif//zhaoyanhua add 03-10-23 17:19
        
#endif
        
#if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
    //when playing WMA, has no CMD.
    // to avoid show time error.
    if ((GetCurrentFileType() == CDROM_WMA) || (GetCurrentFileType() == CDROM_MP4))
    {
        printf("In judge :fail = %d ",fail);
        if(fail)
        {
#ifdef DIV_GOTO_DISPLAY//not show invlid
            ShowSearchPage(SearchPage,1);
#else
            invalid_key();
#endif
        }
        else
		{
		    #ifdef GOTO_CANCEL_FORBACKWARD
            if(adv_search_time)
              Chg2PlayMd();  
            #endif
            
		    if ((GetCurrentFileType()==CDROM_MP4) 
		#ifdef SUPPORT_MP4
		    && IS_FILE_TYPE_AVI()
		#endif
		    )//ycwem 20050925
		        AUDIF_Set_Stop(); //ycwen 2005/8/15 Set audio stop here. To prevent mp4 GOTO from "remaining sound"
            PrintOsdMsg(STR_OS_GOTO,REGION1,1,0); 
			#ifdef SUPPORT_GOTO_CANCEL_REPEAT//tianye 200607
			if(rep_mode)
      			 {
           			   rep_mode=0;
           			   ShowRepInfo();
       		}
			#endif//end=>  #ifdef SUPPORT_GOTO_CANCEL_REPEAT

			
		}
        
    }
    else//not WMA
    {
#endif//end SUPPORT_WMA
        
        if (fail||IS_CMD_NONE())
        {
#ifdef DIV_GOTO_DISPLAY//not show invlid
            ShowSearchPage(SearchPage,1);
#else
            invalid_key();
#endif
        }
        else {
#ifdef FUSS_DVD
            //terry,2002/6/24 08:49PM
            //fuss response , goto -> remain time fail
            if(cd_type_loaded!=CDDVD)
                remain=DISC_TIME;
            else
                remain=0;
#endif        
            #ifdef GOTO_CANCEL_FORBACKWARD
            if(adv_search_time)
              Chg2PlayMd();  
            #endif
	        #ifdef NEW_DISPLAY_METHOD
            if((t_disp) /*|| (cd_type_loaded==CDDA)*/)//shenyj modify for alco 177w
                DispPolling(0);
            #endif
            PrintOsdMsg(STR_OS_GOTO,REGION1,1,0);   

		#ifdef SUPPORT_GOTO_CANCEL_REPEAT//tianye 200607
		if(rep_mode)
  			 {
       			   rep_mode=0;
       			   ShowRepInfo();
   		}
		#endif//end=>  #ifdef SUPPORT_GOTO_CANCEL_REPEAT

        }
        
        
#if defined(SUPPORT_MP4) || defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
    }//end else{
#endif      
        
#ifdef NEW_SEARCH_OSD  
  }  
#endif 
#ifdef DIV_GOTO_DISPLAY
    timeout_osd[2]= 1*OSD_TIMEOUT;
#endif
}


void search_func_clear(void)
{
    if(index_x==0||index_x==1)
        dvd_title=0;
    else if((index_x>=2)&&(index_x<=4))
        dvd_chapter=0;
    else
        goto_time=0;
#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 2004-2-14 14:26
    //clear the item value.
    switch(SearchPage)
    {
        case  0://page 1
            if(cd_type_loaded == CDDVD)
            {
                if(index_x > 2)
                    index_x = 2;//charpter
                else
                    index_x = 0;//title
            }
            else//NOT DVD 
                index_x = 0;   
            break;
        case  1://page 2
            if(cd_type_loaded == CDDVD)
            {   
                if(index_x < 2)//title
                    index_x = 0;
                else//time
                    index_x = 5;
            }
            else//VCD only has time goto
                index_x = 5;
            break;
        case  2:
            if(cd_type_loaded == CDDVD)
            {
                if(index_x< 5)//charpter
                    index_x = 2;
                else//time
                    index_x = 5;
            }   
            else//VCD only has time goto
                index_x = 5;
            break;
    }
    ShowSearchPage(SearchPage,1);
#endif        
    
}   

//terry, 2002/5/9 10:10上午
//fixed incorrect cls
#if defined DIV_GOTO_DISPLAY
void search_func_right(void)
{
    //correct pos.    
    index_x++;
    //printf("----Right index_x = %d--\n",index_x);

    switch(SearchPage)
    {
        case 0:
            if(cd_type_loaded ==CDDVD)
            {
                if(index_x>=4)
                    index_x =4;
            }
        #ifdef MP3_DIRECT_SELECT//zhaoyanhua add 2004-2-16 11:41
            else if(cd_type_loaded == CDROM)
            {
                if(index_x > 3)
                    index_x = 3;
            }
        #endif//MP3_DIRECT_SELECT 
            else//VCD
            {
                if(index_x > 1) 
                    index_x = 1;
            }
            break;
        case 1:
            if(cd_type_loaded == CDDVD)
            {
                if((index_x>1) &&(index_x<=5 ))
                    index_x = 5;
                else if(index_x>=10)
                    index_x=10;
            }
            else//VCD
            {
                if(index_x> 10)
                    index_x = 10;   
            }
            break;
        case 2:
            if(index_x >=10)
                index_x =10;
            
            break;          
    }
    ShowSearchPage(SearchPage,1);
}

#elif defined NEW_SEARCH_OSD
void search_func_right(void)
{
    //correct pos.
    index_x++;
    
    switch(t_disp%10)
    {
    case 1:
        if(index_x>10) // Goto Page 2
        {
            // Rest dvd_title,dvd_chapter
            disp_goto_time=0;
            if(cd_type_loaded == CDDVD)
                dvd_chapter=0;
            
            index_x=0;
            if(cd_type_loaded!=CDDA)
            {
                t_disp++;
            }
        }
        else if(index_x>=5)
        {
        /*
        if((cd_type_loaded==CDDVD)&&(!is_time_search()))
        {
        index_x=0;
        
          }
          else
          {
            */
            dvd_chapter=0;
            dvd_title=0;
            //}
        }
        else 
        {
            //if( (index_x > 1) && (cd_type_loaded!=CDDVD))
            if(index_x > 1)
            {
                dvd_title=0;
            }  
        }
        break;
    case 2:
        if(cd_type_loaded==CDDVD)
        {
            //#ifdef OSD_Function_Disable
            //    if(index_x > 2)
            //    {
            //      t_disp = 1;
            //      index_x = 0;
            //    }  
            //#else
            if(index_x > 3) //yw 021007
            {
                t_disp ++;
                index_x = 0;  
            }
            //#endif
        }
        else // != CDDVD GoBack Page 1 ,index_x = 0
        {
            if(index_x > 0)
            {
                t_disp = 1;
                index_x = 0;
            }
        }
        break;
        
        //#ifndef OSD_Function_Disable
    case 3: // For CDDVD Case 
        if( (index_x > 1) && (cd_type_loaded==CDDVD) )
        {
            t_disp = 1;
            index_x = 0;
        }
        break;
        //#endif
    }
    
}

#else //no NEW_SEARCH_OSD and no DIV_GOTO_DISPLAY

void search_func_right(void)
{   // 2005/06/28 yltseng
    srhProcessDirection( SEARCH_DIRECTION_RIGHT );
}

#endif //NEW_SEARCH_OSD


#if defined DIV_GOTO_DISPLAY//zhaoyanhua 03-10-21 18:49
void search_func_left(void)
{
    //correct pos.
    index_x--;
    switch(SearchPage)
    {
        case 0:
            if(index_x<0)
                index_x=0;
            break;
        case 1:
            if(cd_type_loaded == CDDVD)
            {
                if((index_x<5) &&(index_x >=1))
                             #ifdef NINTAUS_DVD     //2004-2-24 09:13桲迻M          
                                 index_x = 5;
                            #else
                    index_x = 1;
                            #endif
                else if(index_x<0)
                    index_x=0;
            }
            else//VCD
            {
                if(index_x<5)
                    index_x = 5;
            }
            if(index_x >= 9)
                goto_time = 0;
            break;
                
        case 2:
            
            if(cd_type_loaded == CDDVD)
            {
                 #ifdef NINTAUS_DVD   //2004-2-24 11:04桲迻M
                              if(index_x<5)             
                                index_x = 5;
                    #else
                if(index_x<2)
                    index_x = 2;
                  #endif
            }
            else//VCD
            {
                if(index_x < 5)
                    index_x = 5;
            }       
            if(index_x >= 9)
                goto_time = 0;
                
            break;
    }
    ShowSearchPage(SearchPage,1);
}
#elif defined  NEW_SEARCH_OSD
//terry , 2002/5/9 10:09上午
//fix incorrect cls 
void search_func_left(void)
{
    //correct pos.
    index_x--;
    
    switch(t_disp%10)
    {
    case 1:
        if(index_x<0)
        {
            // Rest dvd_title,dvd_chapter
            dvd_title=0;
            if(cd_type_loaded == CDDVD)
                dvd_chapter=0;
            
            if(cd_type_loaded == CDDVD)
            {
                //#ifdef OSD_Function_Disable
                //  t_disp = 2;
                //  index_x = 2;
                //#else
                t_disp = 3;
                index_x = 1;
                //#endif  
            }
            else if(cd_type_loaded != CDDA)
            {
                t_disp = 2;
                index_x = 0;
            }
            else
            {
                t_disp = 1; 
                index_x= 9; 
                
            }
        }
        else if((index_x < 5) && (index_x >= 4))
        {//ptt play
            disp_goto_time=0;        
        }
        else if((index_x < 2) && (index_x >= 1))
        { 
            if(cd_type_loaded == CDDVD)
                dvd_chapter=0;
        }
        else    
        {//time search
            //dvd_title=0;
            //dvd_chapter=0;
            
        }
        break;   
        
    case 2:
        if(cd_type_loaded!=CDDA)
        {
            if(index_x < 0)
            {
                t_disp = 1;
                index_x = 10;
            }
        }
        break;
    case 3: // For CDDVD Case 
        if( (index_x < 0) && (cd_type_loaded==CDDVD) )
        {
            t_disp = 2;
            index_x = 3; //yw 021007
        }
        break;
    }
    
}

#else

void search_func_left(void)
{   // 2005/06/28 yltseng
    srhProcessDirection( SEARCH_DIRECTION_LEFT );
}

#endif //NEW_SEARCH_OSD


void search_func_down(void)
{
    //adjust_val(-1);
#ifdef NEW_SEARCH_OSD
    // YW_Modify 020809 
    int LimtMax;
    
    if(t_disp%10 == 1)
    {
        switch(index_x)
        {
        case 0 :
            LimtMax = (cd_type_loaded==CDDVD) ? get_tt_info(DISP_TT_Ns) : cd_total_trk(); 
            if(LimtMax >= 10)
            {
                if((disp_dvd_title-10) >= 1)
                    disp_dvd_title -= 10; 
                else
                    disp_dvd_chapter += ((disp_dvd_chapter%10) <= (LimtMax%10)) ? (LimtMax  - (LimtMax%10)) : ((LimtMax - 10) - (LimtMax%10));
                dvd_title = disp_dvd_title; 
            }
            break;
        case 1 :
            LimtMax = (cd_type_loaded==CDDVD) ? get_tt_info(DISP_TT_Ns) : cd_total_trk();
            if(LimtMax > 1)
            {
                if(disp_dvd_title > 1)
                    disp_dvd_title --; 
                else
                    disp_dvd_title = LimtMax;
                dvd_title = disp_dvd_title;  
            }
            
            break;
            //  For DVD
        case 2:
        case 3:
        case 4:
            if(cd_type_loaded==CDDVD)
            {
                LimtMax = get_tt_info(DISP_CH_Ns);
                if((index_x == 2) && (LimtMax >= 100))
                {
                    if((disp_dvd_chapter-100) >= 1)
                        disp_dvd_chapter -= 100; 
                    else
                        disp_dvd_chapter += ((disp_dvd_chapter%100) <= (LimtMax%100)) ? (LimtMax  - (LimtMax%100)) : ((LimtMax - 100) - (LimtMax%100));
                }
                else if((index_x == 3) && (LimtMax >= 10))
                {
                    if((disp_dvd_chapter-10) >= 1)
                        disp_dvd_chapter -= 10; 
                    else
                        disp_dvd_chapter += ((disp_dvd_chapter%10) <= (LimtMax%10)) ? (LimtMax  - (LimtMax%10)) : ((LimtMax - 10) - (LimtMax%10));
                }
                else if((index_x == 4) && (LimtMax > 1))
                {
                    if(disp_dvd_chapter > 1)
                        disp_dvd_chapter --; 
                    else
                        disp_dvd_chapter = LimtMax;
                }
                
                dvd_chapter = disp_dvd_chapter;
            }
            
            break;
            
        }
    }
    // YW_Modify 020809
    
    if(cd_type_loaded==CDDA)
    {
        switch(index_x)
        {
        case 2:
            ircmd_mute();
            break;
        case 3:
            action_click = 0;
            if(audio_channel==0)
            {
                audio_channel=2;
            }
            else
            {
                audio_channel--;
            }
            ircmd_channel();
            break;
        case 4:
            action_click = 0;
            key_up_down = 0;
            ircmd_repeat_all();
            break;
        }
    }
    else if(cd_type_loaded==CDDVD)
    {
        if(t_disp%10 == 2)
        {
            if(index_x == 0)
            {
                ircmd_mute();
            }
            else if(index_x == 1)
            {
                action_click = 0;
                key_up_down = 0;
                ircmd_repeat_all();
            }
            else if(index_x == 2) //yw 021007 -[top]- "angle"
            {
                action_click = 1;
                key_up_down = 0; 
                ircmd_angle();
            }                    //yw 021007 -[bottom]- "angle"
            else if(index_x == 3)
            {
                action_click = 1;
                key_up_down = 0;
                ircmd_3dsound();
            }
        }
        
        else if(t_disp%10 == 3)
        {
            //  yw 021004
            if(index_x == 0)
            {
                action_click = 1;
                key_up_down = 0;  
                ircmd_audio_language();
            }
            else if(index_x == 1)
            {
                action_click = 1;
                key_up_down = 0; 
                ircmd_sub_picture();
            }  
        }
        //#endif
    }
    else
    {
        if(t_disp%10 == 1)
        {
            switch(index_x)
            {
            case 2:
                ircmd_mute();
                break;
            case 3:
                action_click = 0;
                audio_channel--;
                ircmd_channel();
                break;
            case 4:
                action_click = 0;
                key_up_down = 0;
                ircmd_repeat_all();
                break;
            }
        }
        else if(t_disp%10 == 2)
        {
            if(index_x==0)
            {
                action_click = 1;
                ircmd_playmode_toggle();
            }
        }
    }
#endif
}   


void search_func_up(void)
{
    //adjust_val(1);
    // YW_Modify 020809 
#ifdef NEW_SEARCH_OSD
    int LimtMax;
    
    if(t_disp%10 == 1)
    {
        switch(index_x)
        {
        case 0 :
            LimtMax = (cd_type_loaded==CDDVD) ? get_tt_info(DISP_TT_Ns) : cd_total_trk(); 
            if(LimtMax >= 10)
            {
                if((disp_dvd_title+10) <= LimtMax)
                    disp_dvd_title += 10; 
                else
                    disp_dvd_title -= ((disp_dvd_chapter%10) <= (LimtMax%10)) ? (LimtMax  - (LimtMax%10)) : ((LimtMax - 10) - (LimtMax%10));
                dvd_title = disp_dvd_title;
            }
            break;
        case 1 :
            LimtMax = (cd_type_loaded==CDDVD) ? get_tt_info(DISP_TT_Ns) : cd_total_trk();       
            if(LimtMax > 1)
            {
                if(disp_dvd_title < LimtMax)
                    disp_dvd_title ++; 
                else
                    disp_dvd_title = 1;
                dvd_title = disp_dvd_title;  
            }
            break;
            //  For DVD
        case 2:
        case 3:
        case 4:
            if(cd_type_loaded==CDDVD)
            {
                LimtMax = get_tt_info(DISP_CH_Ns);
                
                if( (index_x == 2) && (LimtMax >= 100) )
                {
                    if((disp_dvd_chapter+100) <= LimtMax)
                        disp_dvd_chapter += 100; 
                    else
                        disp_dvd_chapter -= ((disp_dvd_chapter%100) <= (LimtMax%100)) ? (LimtMax  - (LimtMax%100)) : ((LimtMax - 100) - (LimtMax%100));
                }
                else if( (index_x == 3) && (LimtMax >= 10) )
                {
                    if((disp_dvd_chapter+10) <= LimtMax)
                        disp_dvd_chapter += 10; 
                    else
                        disp_dvd_chapter -= ((disp_dvd_chapter%10) <= (LimtMax%10)) ? (LimtMax  - (LimtMax%10)) : ((LimtMax - 10) - (LimtMax%10));
                }
                else if( (index_x == 4) && (LimtMax > 1) )
                {
                    
                    if(disp_dvd_chapter < LimtMax)
                        disp_dvd_chapter ++; 
                    else
                        disp_dvd_chapter = 1;
                }
                dvd_chapter = disp_dvd_chapter;
            }
            
            break;
            
        }
    }
    
    // YW_Modify 020809 
    
    if(cd_type_loaded==CDDA)
    {
        switch(index_x)
        {
        case 2:
            ircmd_mute();
            break;
        case 3:
            action_click = 0;
            audio_channel++;
            ircmd_channel();
            break;
        case 4:
            action_click = 0;
            key_up_down = 1;
            ircmd_repeat_all();
            break;
        }
    }
    else if(cd_type_loaded==CDDVD)
    {
        if(t_disp%10 ==2)
        {
            if(index_x == 0)
            {
                ircmd_mute();
            }
            else if(index_x == 1)
            {
                action_click = 0;
                key_up_down = 1;
                ircmd_repeat_all();
            }
            else if(index_x == 2) //yw 021007 -[top]- "angle"
            {
                action_click = 1;
                key_up_down = 1; 
                ircmd_angle();
            }                    //yw 021007 -[bottom]- "angle"
            else if(index_x == 3)
            {
                action_click = 1;
                key_up_down = 1;
                ircmd_3dsound();
            }
        }
        //#ifndef OSD_Function_Disable
        else if(t_disp%10 ==3)
        {
            //  yw 021004
            if(index_x == 0)
            {
                action_click = 1;
                key_up_down = 1;
                ircmd_audio_language();
            }
            else if(index_x == 1)
            {
                action_click = 1;
                key_up_down = 1;
                ircmd_sub_picture();
            }  
        }
        //#endif
    }
    else
    {
        if(t_disp%10 ==1)
        {
            switch(index_x)
            {
            case 2:
                ircmd_mute();
                break;
            case 3:
                action_click = 0;
                audio_channel++;
                ircmd_channel();
                break;
            case 4:
                action_click = 0;
                key_up_down = 1;
                ircmd_repeat_all();
                break;
            }
        }
        else if(t_disp%10 ==2)
        {
            if(index_x==0)
            {
                action_click = 1;
                ircmd_playmode_toggle();
            }
        }
    }
#endif
}   


void add_input_num(int *v)
{
    //printf("v:%d ir_select_number:%d flag3S_digit_10:%d\n",*v,ir_select_number,flag3S_digit_10);
    if(ir_select_number!=10)        
    {
        if(ir_10p==0)           
            *v*=10;
        else
        {
            *v=(*v/10)*10;
            ir_10p=0;
        }
#ifdef TEN_AND_ZERO_IN_A_KEY 
        if(ir_select_number==0)
            if(ir_select_number > 0)// previous is 10+
                ir_select_number += *v;
            else
                ir_select_number = 10; 
#endif
            
    }else
        ir_10p=1;
    
    
    *v+=ir_select_number;       
}

void search_add_num(int *v,int pos)
{
    int hi,i,time10=1; 
    int tmp;
    //terry,2002/5/8 11:27下午
    //cls val when user input first digital
#ifdef NEWSTYLE_WINDOW  
    if(!(full_scrn&MESSAGE))//xyy 2003-7-31 16:28
#endif
    {
//Maoyong 2004.04.28 marked "#ifdef MP3_DIRECT_SELECT"
//#ifdef MP3_DIRECT_SELECT //zhaoyanhua add 3-7-16 14:55
    if (cd_type_loaded == CDROM)
    {
		#ifdef ALCO_DVD_UI
		if( /*(index_x==0)||*/(index_x==5) )//trk has 4 digital.
		#else
        if( (index_x==0)||(index_x==5) )//trk has 4 digital.
		#endif
            *v = 0;
    }
    else
    {
		#ifdef ALCO_DVD_UI
		if( /*(index_x==0)||*/((cd_type_loaded!=CDDVD)&&(index_x==2))||(index_x==5) )
		#else
        if( (index_x==0)||(index_x==2)||(index_x==5) )
		#endif
            *v=0;

    }
//#else
//  if( (index_x==0)||(index_x==2)||(index_x==5) )
//      *v=0;
//#endif
    }
#ifdef NEWSTYLE_WINDOW   //xyy 2003-7-29 11:03
    extern int bInputIndex;
    if(full_scrn&MESSAGE)
    {
        if(cd_type_loaded==CDDVD)
        {
            if( ((info_index<=1) && (bInputIndex==0))||((info_index==2) && (index_x==0)) )
                *v=0;
        }
        else
        {
            if( ((info_index<1) && (bInputIndex==0))||((info_index==1) && (index_x==0)) )
                *v=0;
        }   
    }
#endif
        

    for(i=0;i<pos;i++)
        time10=time10*10;
    
    hi=time10*10;
    tmp=ir_select_number*time10;
    
#ifdef DIV_GOTO_DISPLAY     
    //NOTE:
    //I don't know why when I input time number (index= 6),it will cause "((*v)/hi)*hi" error.
    //So I have to do this.
    //zhaoyanhua note 03-10-24 19:13
    if(full_scrn&GOTO)
    {
        UINT32 temp1;
    
        temp1 = (*v)/hi;    
        switch(pos)
        {
            case 5:
                temp1 = temp1*1000000;
                break;
            case 4:
                temp1 = temp1*100000;
                break;
            case 3:
                temp1 = temp1*10000;            
                break;
            case 2:
                temp1 = temp1*1000;
                break;
            case 1:
                temp1 = temp1*100;
                break;
            case 0:
                temp1 = temp1*10;
                break;
        }                   
    
        temp1 = temp1+tmp;
        temp1 = temp1 + (*v)%time10;
        *v = temp1; 
        
        return;
    }
#endif//end DIV_GOTO_DISPLAY
    
    if(pos==0)
        *v=(*v/hi)*hi+tmp; 
    else
        *v=(*v/hi)*hi+tmp+*v%time10;  
}   

#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 2004-2-24 11:13
void  div_search_input_check(void)
{
    int temp_index = 0;
    //printf("------11111   index-x = %d\n",index_x);
    if((SearchPage == 1)&&(index_x == 2))
    {
        index_x = 5;    
    }
    
    ShowSearchPage(SearchPage,1);
    
    temp_index = index_x-1;
    
    if(cd_type_loaded == CDDVD)
    {
        if(   ((SearchPage == 1)&&( (temp_index == 4) || (temp_index == 10)))//title:time MODE
            ||((SearchPage == 2) &&( (temp_index == 4) || (temp_index == 10)))//charpter:time MODE
            ||((SearchPage == 0) &&( (temp_index == 1) || (temp_index == 4)))//title:charpter MODE
          )
        {
 
            //NOTE: 
            //because search_func_select only  deal this:
            //title :index_x 0~1
            //charpter:index_x : 2~4
            //time :index_x : 5~10
            index_x = temp_index;
            printf("++++++++++-----index_x : %d---\n",index_x);
            search_func_select();
            index_x = temp_index+1;
            if(SearchPage != 0)
            {
                    if(index_x <= 5)
                        index_x = 5;
                    else if(index_x >10)
                    index_x = 10;
            }       
                
        }
        
    }
    else
    {
        if( 
    #ifdef  MP3_DIRECT_SELECT       
            ((SearchPage == 0) && (temp_index == 1) && (cd_type_loaded != CDROM))//for VCD
            ||((SearchPage == 0) && (temp_index == 3) && (cd_type_loaded == CDROM))//for MP3//zhaoyanhua add 2004-2-16 10:35
    #else           
            ((SearchPage == 0) && (temp_index == 1))
    #endif// ifdef MP3_DIRECT_SELECT           
            ||((SearchPage == 1) && (temp_index == 10))
            ||((SearchPage == 2) && (temp_index == 10))
            )
        {
            index_x = temp_index;
            search_func_select();
            index_x = temp_index +1;
            
            switch(SearchPage)
            {
                case 0:
            #ifdef  MP3_DIRECT_SELECT//zhaoyanhua add 2004-2-24 11:22               
                    if(cd_type_loaded == CDROM)
                        index_x = 3;
                    else
            #endif//#ifdef MP3_DIRECT_SELECT                    
                    index_x = 1;
                    break;
                case 1:
                case 2:
                    index_x = 10;
                    break;          
            }
        }
    
    }       
    
}
#endif//ifdef DIV_GOTO_DISPLAY


//#ifdef MP3_DIRECT_SELECT  //zhaoyanhua add 3-7-16 16:38
void search_func_input(void)//2004-2-11 01:20桲迻P
{
    //printf("ir_select_number:%x x=%d time=%d",ir_select_number,index_x,goto_time);
    
    if(ir_select_number == 10)
        ir_select_number = 0;


    if (cd_type_loaded == CDROM)
    {
        if(index_x >= 5)
        {
            #ifdef SUPPORT_DISPLAY_MENU
            if(In_Goto_Menu())
              search_add_num(&goto_time, (11 - index_x));
            else
            #endif
            search_add_num(&goto_time, (10 - index_x));

        }
        else if(index_x < 5)
        {
            int tt = dvd_title;

            search_add_num(&tt, 3 - index_x);
            dvd_title=tt;
            //printf("Search _INPUT  dvd_title= %d\n",tt);
            //lyc add 2006-1-9 for NERO DIGITAL GOTO
            #if defined(SUPPORT_GOTO_NERODIGITAL)&&defined(SUPPORT_NERODIGITAL)
	          if(((IS_FILE_TYPE_QT())||(IS_FILE_TYPE_ND()))&&(pFsJpeg->g_uiFileChangeChapter == 3))
	           { 
	           	 extern UINT32  QT_get_num_of_chapter();
	           	 if(dvd_title > QT_get_num_of_chapter())
	           	    dvd_title = 0;
	           }
	     else 	 
	     #endif
	     
        #if 1 //liumzh 2006-6-13 15:34,total 100 tracks, play 1st track, then we can't input 1xx track
	        switch(index_x)
	        {
	            case 0: 
	            	dvd_title = dvd_title - dvd_title % 1000;
	                break;
	            case 1:
	            	dvd_title = dvd_title - dvd_title % 100;
	                break;
	            case 2:
	            	dvd_title = dvd_title - dvd_title % 10;
	                break;
	            case 3:
	                break;
	            default:
	            	break;
	        }
        #endif
        
            if(dvd_title > mp3_file_count())//add by shawn 20020219
                 dvd_title = 0;

        }
#ifndef DIV_GOTO_DISPLAY//zhaoyanhua add 2004-2-16 11:36
        if((index_x != 3) && (index_x != 10))
#endif              
                index_x++;
    }
    else // (cd_type_loaded != CDROM)
    {

        if(index_x >= 5)
        {
            #ifdef SUPPORT_DISPLAY_MENU
            if(In_Goto_Menu())
              search_add_num(&goto_time, (11 - index_x));
            else
            #endif//end #ifdef SUPPORT_DISPLAY_MENU
            search_add_num(&goto_time, (10 - index_x));

        }
        else //index_x < 5
        {
            if(index_x >= 2 && index_x <= 4)//dvd chapter input
            {
                int iChapter,ch=dvd_chapter;
                iChapter = get_tt_info(DISP_CH_Ns);

                search_add_num(&ch, 4 - index_x);
                dvd_chapter = ch;

                if(dvd_chapter > iChapter) { //add by shawn 20020219
            #ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-11-6 13:16
                dvd_chapter = 0;
        #else
                    if (dvd_chapter>99) { //xxx:3 digits
                        dvd_chapter = (dvd_chapter/100) * 100;
                    } else if (dvd_chapter>9) { //xx:2digits
                        dvd_chapter = (dvd_chapter/10) * 10;
                    }else {
                        dvd_chapter = 0;//dvd_chapter=dvd_chapter%10;//add by shawn 20020219
                    }
                if (dvd_chapter>iChapter) {
                   dvd_chapter = 0;
                    }
            #endif
                }
            }
            else
            {
                int tt = dvd_title;

                search_add_num(&tt, 1 - index_x);
                dvd_title=tt;
                dvd_chapter = 1;//TT play,terry,3-8-23 19:35

                if(cd_type_loaded == CDDVD)
                {
                    if(dvd_title > get_tt_info(DISP_TT_Ns))//add by shawn 20020219
                    dvd_title = 0;
                }
                else
                {
                    if(dvd_title > cd_total_trk())//add by shawn 20020219
                        dvd_title = 0;
                }
            }
        }//end if else (index_x<5)
#ifndef DIV_GOTO_DISPLAY
        if((index_x != 1) && (index_x != 4) && (index_x != 10))
#endif
         #ifdef SUPPORT_DISPLAY_MENU
         if(!In_Goto_Menu())
         #endif//end #ifdef SUPPORT_DISPLAY_MENU
            index_x++;
   }//else( cd_type_loaded!= CDROM)
   
#ifdef DIV_GOTO_DISPLAY
    div_search_input_check();//zhaoyanhua add 2004-2-24 11:19  
#endif
         //printf("dvd_title:%d dvd_chapter:%d\n",dvd_title,dvd_chapter);
        //printf("\n search(653) get_tt_info(DISP_TT_NS)=%d, get_tt_info(DISP_CH_NS)=%d,index_x=%d,cd_total_trk()=%d \n",get_tt_info(DISP_TT_Ns),get_tt_info(DISP_CH_Ns),index_x,cd_total_trk());

#ifdef SUPPORT_JPEG_GOTO
    if((cd_type_loaded==CDROM) && (pFsJpeg->gifsFuncBtn==FS_FUNC_JPEG))
    {
        //if(!pFsJpeg->gbfsSlide)
            FSGUI_JpgUpdateOSD();
        if(pFsJpeg->gbfsSlide)
            set_rtc_val(0);
    }
#endif

#ifdef PMP_DVD //kenny 2005/8/3
extern void PMP_UpdateGotoOSD(void);
PMP_UpdateGotoOSD();


#endif

}

/*#else   //not MP3_DIRECT_SELECT

void search_func_input(void)
{
    //printf("ir_select_number:%x x=%d time=%d",ir_select_number,index_x,goto_time);

    if(ir_select_number == 10)
        ir_select_number = 0;

    if(index_x >= 5)
    {
        //terry,2002/5/9 10:23上午
        //dvd_chapter = 0;
        //dvd_title = 0;
#ifdef NEW_SEARCH_OSD
        search_add_num(&disp_goto_time, (10 - index_x));
#else
        search_add_num(&goto_time, (10 - index_x));
#endif
    }
    else if(index_x < 5)
    {
        //terry,2002/5/9 10:24上午
        //goto_time = 0;

        //Jeff 20020520
        if(index_x >= 2 && index_x <= 4)//dvd chapter input
        {
            int iChapter,ch=dvd_chapter;
            iChapter = get_tt_info(DISP_CH_Ns);

            search_add_num(&ch, 4 - index_x);
            dvd_chapter = ch;

            if(dvd_chapter > iChapter) { //add by shawn 20020219
            #ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-11-6 13:16
                dvd_chapter = 0;
        #else
                if (dvd_chapter>99) { //xxx:3 digits
                    dvd_chapter = (dvd_chapter/100) * 100;
                } else if (dvd_chapter>9) { //xx:2digits
                    dvd_chapter = (dvd_chapter/10) * 10;
                } else {
                    dvd_chapter = 0;//dvd_chapter=dvd_chapter%10;//add by shawn 20020219
                }
                if (dvd_chapter>iChapter) {
                    dvd_chapter = 0;
                }
            #endif
            }
        }
        else
        {
            int tt = dvd_title;

            search_add_num(&tt, 1 - index_x);
            dvd_title=tt;
            dvd_chapter = 1;//TT play,terry,3-8-23 19:35

            if(cd_type_loaded == CDDVD)
            {
                if(dvd_title > get_tt_info(DISP_TT_Ns))//add by shawn 20020219
                    dvd_title = 0;
            }
            else if(cd_type_loaded==CDROM)
            {//terry,2003/6/24 10:54上午
                if(dvd_title > mp3_file_count())//add by shawn 20020219
                    dvd_title = 0;
            }else
            {
                if(dvd_title > cd_total_trk())//add by shawn 20020219
                    dvd_title = 0;
            }
        }
    }
#ifndef DIV_GOTO_DISPLAY
    if((index_x != 1) && (index_x != 4) && (index_x != 10))
#endif
#ifdef NEW_SEARCH_OSD
    {
        if(!((cd_type_loaded!=CDDVD)&&(index_x>1)&&(index_x<5)))
        {
            index_x++;
        }
    }
#else
    index_x++;
#endif
    
#ifdef DIV_GOTO_DISPLAY
    div_search_input_check();//zhaoyanhua add 2004-2-24 11:19       
#endif
    //printf("dvd_title:%d dvd_chapter:%d\n",dvd_title,dvd_chapter);
    //printf("\n search(653) get_tt_info(DISP_TT_NS)=%d, get_tt_info(DISP_CH_NS)=%d,index_x=%d,cd_total_trk()=%d \n",get_tt_info(DISP_TT_Ns),get_tt_info(DISP_CH_Ns),index_x,cd_total_trk());
}
#endif //End MP3_DIRECT_SELECT
*/

#if defined(DVD_DIRECT_SELECT_CHAPTER)
//terry,2004/2/26 06:57PM
UINT32 ir_sel_search(int c)
{
    UINT8 ttn = NP_TTN;
    UINT16 tt_pg,uop;
    
#ifdef DVD_AUDIO    //terry,2004/2/18 01:17PM
    if(dAMG_LSN)
    {
		ttn = NP_ATT_GRN;
		tt_pg = GetTotalTrk(ttn);
		uop=2;
    }
    else
#endif  
	{
		tt_pg = pDSV->dTT_SRP[ttn].vtt.PTT_Ns;
		uop=0;
    }
    
    if(tt_pg==1)
    {//terry,2004/2/23 11:18AM
		ttn=c;
		c=0;
    }
    
    if((pDSV->dTT_SRP[ttn].vtt.TT_PTL_ID_FLD>=NP_PTL_LVL)&&(pDSV->CurrDomain==VMGM_DOM)) //(PLVL_Lock_Status==0)
    {//linrc add for bug fix 2005-4-21 17:47
        invalid_key();
        return 0;
    }
    
	#ifndef ONLY_ONE_CHAPTER_SELECT_TITLE	//yaowh add,2005-10-21 15:09
    if ((cd_type_loaded == CDDVD ) && ( pDSV->dTT_SRP[NP_TTN].vtt.PTT_Ns < ir_select_number))//caoh 2005-7-27 15:58
	{ //correct the error : when the select number overrange the total capter in current title
		invalid_key();
		return 0;
	}
	#endif

    return PTT_Play(ttn,c,uop);//terry,2004/2/23 02:23PM
}
#else
UINT32 ir_sel_search(int c)
{//terry,2004/2/18 01:17PM
    return PTT_Play(c,0,2);
}
#endif

