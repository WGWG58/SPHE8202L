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
|  File Name   :  ircmd_zoom.c
|
|  Description :  zoom function realization in remoter.
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/1/14        Terry         Creating
|--------------------------------------------------------------------------------*/
/**************************************************************************
 *  Function Name: show_zoom                           
 *  Purposes:                                                             
 *    show word "zoom x" in region1.note:"x" is zoom multiple.                          
 *  Descriptions:                                                         
 *   
 *  Arguments:                                                            
 *    t=1: seconds for time out
 *    t=0: show information at all times
 *    mode(8:5) : 0 sw region on, 1 sw region off, 2 sw region anti
 *    mode(3:0) : Methods to cat some information to output string
 *
 *  Returns:     NONE
 *  See also:    NONE                                                          
 *    
 **************************************************************************/
void show_zoom(int t)
{//terry, 2004/1/14 03:17PM
#ifndef NO_ZOOM_FUNCTION       
  int zoom,id,md;
  
#ifdef NEWSTYLE_WINDOW
  if(full_scrn&MESSAGE)//xiongyuyue
	return;
  else
#endif
  {
     if(vpp_zoom==ZOOM_PS) zoom=ZOOM_LB;//zoom 0
     else zoom=vpp_zoom;
       
     id = STR_OS_ZOOM;
     if(zoom <= ZOOMIN_MAX)
     {
       #ifdef TWELVE_ZOOMFACTORS     //fengjl add 2004-05-05 23:41  
        switch (zoom)
        {
        case 2:strcpy(RegionValStr[REGION1]," 1.2");  break;
        case 3:strcpy(RegionValStr[REGION1]," 1.3");  break;
        case 4:strcpy(RegionValStr[REGION1]," 1.5");  break;
        case 5:strcpy(RegionValStr[REGION1]," 2");    break;
        case 6:strcpy(RegionValStr[REGION1]," 2.5");  break;
        case 7:strcpy(RegionValStr[REGION1]," 3");    break;
        case 8:strcpy(RegionValStr[REGION1]," 3.5");  break;
        case 9:strcpy(RegionValStr[REGION1]," 4");    break;
        }
        printf(" **************ZOOM=%d **************\n",zoom);
       #endif
       md = 8;
       #ifndef SHOW_ZOOM1       
       zoom++;       
       #endif
       
     }
     else
     {
#ifdef OP_JPEG_ZOOM_LEVEL       
	   md = 9;       
       switch (zoom)//libing 2005-6-9 13:57
       {       	       	
       	case 6:strcpy(RegionValStr[REGION1]," 3/4");  break;
       	case 7:strcpy(RegionValStr[REGION1]," 2/3");  break;
       	case 8:strcpy(RegionValStr[REGION1]," 1/2");  break;
      }
#else
       md = 7;
       zoom = vpp_zoom-ZOOMOUT_BASE+2;
       #ifdef BBK_DVD  
       id = STR_OS_NO_ZOOM;       
       #endif
#endif       
     }

     OSD1000ISP_STATUS(vpp_zoom, OSDIR_ZOOM);

     PrintOsdMsg(id|(zoom<<OSDSTR_ID_TOTL_BIT),REGION1,t,md);
  }
#endif//#ifndef NO_ZOOM_FUNCTION       
}

/*
*   zoom in/out
*   vpp_zoom  0 :  LB or Normal
*             1 :  PS
*             2 :  zoom in x1.3
*             3 :  zoom in x1.5
*             4 :  zoom in x2
*             5 :  zoom in x3
*             6 :  zoom out x0.75
*             7 :  zoom out x0.67
*             8 :  zoom out x0.5
*/
/**************************************************************************
 *  Function Name: ircmd_zoom                           
 *  Purposes:                                                             
 *      realize zoom function using zoom key.
 *  Descriptions:                                                         
 *   
 *  Arguments:                                                            
 *      vpp_zoom:   2~4: zoom in; 1/4~1/2:zoom out.
 *      ZOOMIN_BASE~ZOOMIN_MAX   : zoom in, zoom ratio>1,at normal state ,
 *                                there are there value 2,3,4.
 *      ZOOMOUT_BASE~ ZOOMOUT_MAX: zoom out,zoom ratio<1, at normal state ,
 *                                there are there value 1/2,1/3,1/4.
 *      If minish ZOOMOUT_MAX value,corresponding,
 *       zoom ratio value amount reduce.(zoom in/out)
 *      for example ,ZOOMOUT_MAX value be changed from 8 to 6, 
 *       there are only zoom ratio value 2,3,4,1/2 .
 * 
 *  Returns:     NONE
 *  See also:    NONE                                                          
 *    
 **************************************************************************/

extern UINT32 save_srn_start_t;
void ircmd_zoom(void)
{
#ifdef ZOOM_CLEAR_IN_ONE_KEY//libing 2005-6-21 11:12
{
    if((full_scrn&GOTO)||(full_scrn&PROGRAM)||(full_scrn&MARK))
    {
        ircmd_clear();
        return;
    }
}     
#endif 
if(cd_type_loaded==CDDA)//libing 2005-6-29 15:27 for zoom_clear_in_one
    {
    	invalid_key();
    	return;
    }      
    
    #ifdef SUPPORT_CDG    //Jack added for Alco:CDG can zoom in/out
    if((cd_type_loaded==CDDA) && !is_cdg_disc(1))
    {
      invalid_key();
      return; 
    }
    #endif

    #ifdef SUPPORT_HD_RESOLUTION
    if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
    {
        if((GET_TV_RESOLUTION()==HD_720)||(GET_TV_RESOLUTION()==HD_1080))
        {
            invalid_key();
            return;        
        }
    }    
    #endif
    
#ifndef NO_ZOOM_FUNCTION

  #ifdef ALCO_8200P_MULTIKEY 
    if(IS_STOP_OPEN_IDLE_STATE())
    {
       #ifdef NEED_DIFF_IR_PANEL_KEY
       if(panel_key_flag & (0x01<<0))
       {
         invalid_key();
         panel_key_flag = 0;
       }
       else
       #endif
       ircmd_display_format_toggle();
       return; 
    }
    
    #ifdef SUPPORT_CDG    //Jack added for Alco:CDG can zoom in/out
    if((cd_type_loaded==CDDA) && !is_cdg_disc(1))
    {
      invalid_key();
      return; 
    }
    #endif
  #endif//#ifdef ALCO_8200P_MULTIKEY 

#ifdef ZOOM_ROTATE_RESET_SLIDE_TIME//lijd 2005-5-30 10:42
	 if(Is_JPEG_SlideMode())
        set_rtc_val(0);
#endif 
#ifdef	INVALID_ZOOM_IN_DVD_MENU//XLJ2004-3-26
//invaild zoom key during the short film in DVD menu. Zoom key is invailable
//in choosing Menu too, but through inv_tbl. heqiang, 2004-4-23 9:52
	if(is_menu()&&(HL_exist!=1)&&(cd_type_loaded==CDDVD))	

	{
		invalid_key();
		return;
	}
#endif//INVALID_ZOOM_IN_DVD_MENU



#ifndef DVB1000_NON_OS
    //check invalid state
    if (cd_type_loaded == CDROM)
    {
       #ifdef JPEG_ZOOM_ROTATE_RESET_PLAY_TIME
       if(Is_JPEG_SlideMode())
          set_rtc_val(0);
       #endif
           
#ifdef ZOOM_DIRECT_STOP_SLIDE		//wanghaoying 2003-08-25 20:17
    if(Is_JPEG_SlideMode())//nono 4-8-19 1:05
		jpg_slide_time = 0xffffffff;
#endif
#ifdef SUPPORT_FILE_SYSTEM_MODE
        //if ((GetCurrentFileType() != CDROM_MPG)|| (pFsJpeg->gifsState == FS_STATE_LIST))
        //Steven 2006/10/11 add audio_only == 1 to avoid zooming when there is no vedio media//
        if ((audio_only == 1) || ((GetCurrentFileType() != CDROM_MPG) && (GetCurrentFileType() != CDROM_MP4)) || (pFsJpeg->gifsState == FS_STATE_LIST))   //hq, 2004-4-15 11:45
#endif
        if (!FSIsZoomOK())
        {
            invalid_key();
            return;
        }
#ifdef  ROTATE_NOT_ZOOM//zhaoyanhua add 2003-12-9 16:34
    if(Is_Rotate_State())
    {    
        invalid_key();
        return;
    }
 
     //printf("######## ZOOM-------rotate_mode:%d---\n",Is_Rotate_State());

#endif 
    }
#endif  //DVB1000_NON_OS

    #ifndef ZOOM_ROTATE_RESET_SLIDE_TIME
    //stop slide show atfer rotation
    pFsJpeg->gbfsSlide = 0;
    #endif

    //set zoom ratio parameter
    if(vpp_zoom<ZOOMIN_BASE)
    {
        vpp_zoom=ZOOMIN_BASE;
    }
    else if(vpp_zoom==ZOOMIN_MAX)  
    {
        vpp_zoom=ZOOMOUT_BASE;
    }
    else
    {
        vpp_zoom++;
    }
    
    if (vpp_zoom>ZOOMOUT_MAX)
    {
        set_video_aspect();     // also reset zoom
        show_zoom(1);
        #ifdef JPEG_ZOOM_OFF_SEQ_PLAY     //Liumzh    05/04/21
        jpg_slide_time = JPEG_SLIDE_TIME;
        #endif
    }
    else if (vpp_zoom>=ZOOMIN_BASE && vpp_zoom<=ZOOMIN_MAX)
    {
        vpp_zoom_offset_mode = OFFSET_USER_CENTER;
        show_zoom(0);
    }
    else if (vpp_zoom>=ZOOMOUT_BASE && vpp_zoom<=ZOOMOUT_MAX)
    {
        vpp_zoom_offset_mode = OFFSET_CENTER;
        show_zoom(0);
    }
#ifdef SCRN_SAVER_WHEN_PAUSE    //sunzhh 20050802
    if(Is_JPEG_SlideMode())
    {
        save_srn_start_t=0; // mimitsai add 20050726, for aviod zoom and rapidly go in screen saver.
    }
#endif
    //pass parameter to vpp
    startup_vpp();
    setVPP_DoItNow();
#endif//end #ifndef NO_ZOOM_FUNCTION 
}

#ifdef ZOOM_DIRECT_STOP_SLIDE       //wanghaoying 2003-08-25 21:30
//Maoyong 2004.07.05 make it a function for calling
void ForceStopJpgSlide(void)
{
    if( Is_JPEG_SlideMode() )
    {
        jpg_slide_time = JPEG_SLIDE_TIME;
        if(vpp_zoom!=0)
        {
            vpp_zoom = 0;
            show_zoom(1);
        }
    }
}
#endif //#ifdef ZOOM_DIRECT_STOP_SLIDE













//=================================ending====================================
