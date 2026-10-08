// 2005/09/05 yltseng, Fix bug for new osd driver
// 2005/09/12 yltseng, Add new structure for font
//2006/04/17 linrc add Mp3 Encoder message show function
/****************************************************
linrc move FS(MP4/ID3...) OSD Display Message Here
Move From:fs_nav_other.c/fs_nav_id3.c/fs_nav_mp3.c..
*****************************************************/
#include "global.h"
#include "func.h"
#include "file_if.h"
#include "osd.h"
#include "fsNAV.h"
#include "fs_show.h"

#ifdef RIPPING_MODE_SELECT//qinhua,add,060603
#include "ircmd.h"
#include "fs_new_app.h"
#include "ir_filter.h"
#endif

#ifdef SUPPORT_OSDID3
#include "Vpp.h"
#endif

#ifdef SUPPORT_MP4

/***********************************************************
Functon:ShowMP4Message()
Input: Diplay message type:1:MP4 initializing message...
                          2:MP4 A/V Unsupport message...
                          3:Mp4 format unsupport message...
Output: viod...
Description: It move from fs_nav_other
Creat time:2004-11-6 10:46 linrc creat...                          
************************************************************/

void ShowMP4Message(UINT8 message)
{
    #ifdef AUDIO_EXTENSION_USE_MP3_LIST //chenzhao on 2006-10-9 15:19 .
    if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
        return;
    #endif
    switch(message)
    {
        case MP4_INI:
            #ifdef SHOW_MP4_INIT_STR    //wangwei-2004/4/28
            {
			    PrintOsdMsg(STR_OS_MP4_INIT, REGION1, 0, 0);  //mode 0:	clear pre string						
		    }
            #else
		    {
			    psprintf(RegionValStr[REGION1], "INITIALIZING...");		
			    PrintOsdMsg(STR_OS_SPACE, REGION1, 0, 1);							
		    }
		    #endif
		    break;
		    
	    case UNSUPPORT_MESSAGE:
	    
            if( !FILE_HAS_AUDIO() )
               #ifdef SHOW_NO_AUDIO_INIT_STR //qinhua ,2005-10-10 14:18
               PrintOsdMsg(STR_OS_NO_AUDIO, REGION1, 0, 0);   
              #else 
                osdshow( REGION1, "NO AUDIO" );
               #endif 
            else if( !FILE_HAS_VIDEO() )
                osdshow( REGION1, "NO VIDEO" );
            else if( FILE_UNSUPPORT_AUDIO() ) 
                osdshow( REGION1, "UNSUPPORT AUDIO" );
            else if( FILE_UNSUPPORT_VIDEO() )
                osdshow( REGION1, "UNSUPPORT VIDEO" );
            else
                PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 0);

            timeout_osd[ REGION1 ] = 1 * OSD_TIMEOUT;
            break;
            
        case UNSUPPORT_FORMAT:
             if ( FILE_UNSUPPORT_AUDIO() && FILE_UNSUPPORT_VIDEO() )
                #ifdef ALCO_DIVX_UI//shenyj add for alco 12/30
                osdshow( REGION1, "NO SUPPORT" );
                #else
                osdshow( REGION1, "UNSUPPORT FORMAT" );
                #endif
             else
                osdshow( REGION1, "FILE ERROR" );                     
             timeout_osd[ REGION1 ] = 2 * OSD_TIMEOUT;   // 2004/09/29 yltseng 
             break;	 

#ifdef SUPPORT_QUICKTIME
        case UNSUPPORT_DRM:
        	osdshow( REGION1, "FILE CANNOT BE PLAYED" );
        	timeout_osd[ REGION1 ] = 2 * OSD_TIMEOUT;
        	break;
#endif	// SUPPORT_QUICKTIME

        default : break;            
    }
}

#endif  //end SUPPORT_MP4

/***************************************************************
Function:DrawID3_GUI()
Input: void
Output: void
Description: It move from fs_nav_mp3.c,in order to Draw ID3 GUI
             some content...
creat time: 2004-11-6 11:29 linrc creat...             
***************************************************************/

#if defined(SUPPORT_ID3)||defined(SUPPORT_OSDID3)
extern BYTE GetCurrentFileType();
extern void FSGUI_FillFrameBuf();
extern void osd_ClearOneRegion();
extern void OSD_ShowString();
extern void FSGUI_ShowString(); 
extern ID3_TAG *pId3;
extern LYR *lyr;// = (LYR *)ID3_MEM_START;

#ifdef SUPPORT_OSDID3//liweihua and zhaoyanhua add 2004-1-9 18:12
int osd_id3_flag=0;
void show_id3(void)
{
    	
    #ifdef VIRTUAL_KEYBOARD // for fixed keyboard show id3 jiangxl
     if(full_scrn & KEYBOARD)
     return ;
    #endif 
	
    if(full_scrn& SOUND)
        return;
    #ifdef PMP_UI
    if(osd_id3_flag==0)//yangli 20050721
    return;
    osd_init_OSDID3();
    #endif

    if((lyr->id3_exist) && (full_scrn==0))  //hongfeng add for aviod Region move at PAL 2006/9/6 9:51
    {
        if(getVPP_TVsystem())  //PAL
            osd_set_region_position(3,26,172);
        else                   //NTSC
            osd_set_region_position(3,26,134);
    }

    osd_ClearOneRegion(REGION3,0);
    if(lyr->id3_exist)
    {
    #if ( defined( SUPPORT_FONT_CP_950 ) || defined( SUPPORT_FONT_CP_950_COMPRESSED ) || defined( SUPPORT_FONT_CP_950_COMMON ) || defined( SUPPORT_FONT_CP_950_COMMON_COMPRESSED ) || \
          defined( SUPPORT_FONT_CP_936 ) || defined( SUPPORT_FONT_CP_936_COMPRESSED ) || defined( SUPPORT_FONT_CP_936_COMMON ) || defined( SUPPORT_FONT_CP_936_COMMON_COMPRESSED ) )
        #ifdef NEW_OSD_DRIVER
            #define X_POS_1     (5*2)
            #define X_POS_2     (48*2)
            #define X_POS_3     (48*2)
        #else
            #define X_POS_1     5
            #define X_POS_2     48
            #define X_POS_3     48    
        #endif
    #else
        #ifdef NEW_OSD_DRIVER
            #define X_POS_1     (5*2)
            #define X_POS_2     (54*2)
            #define X_POS_3     (68*2)
        #else
            #define X_POS_1     5
            #define X_POS_2     54
            #define X_POS_3     68    
        #endif
    #endif

    #if defined( SUPPORT_FONT_CP_950 ) || defined( SUPPORT_FONT_CP_950_COMPRESSED ) || defined( SUPPORT_FONT_CP_950_COMMON ) || defined( SUPPORT_FONT_CP_950_COMMON_COMPRESSED )
    OSD_ShowString(X_POS_1, 20, "∫q¶±: ", 2,3);
    OSD_ShowString(X_POS_1, 50, "∫q§‚: ", 2,3);
    OSD_ShowString(X_POS_2, 20,  lyr->song, 2,3);
    OSD_ShowString(X_POS_3, 50,  lyr->artist, 2,3);	
    #elif defined( SUPPORT_FONT_CP_936 ) || defined( SUPPORT_FONT_CP_936_COMPRESSED ) || defined( SUPPORT_FONT_CP_936_COMMON ) || defined( SUPPORT_FONT_CP_936_COMMON_COMPRESSED )
    OSD_ShowString(X_POS_1, 20,  "∏Ë«˙£∫", 2,3);
    OSD_ShowString(X_POS_1, 50,  "—›≥™£∫", 2,3);
    OSD_ShowString(X_POS_2, 20,  lyr->song, 2,3);
    OSD_ShowString(X_POS_3, 50,  lyr->artist, 2,3);
    #else
        #ifdef ADD_ID3_ALBUM  //denghg  add for ADD_ID3_ALBUM 2006-1-11 09:31     
        OSD_ShowString(X_POS_1, 20,  "ALBUM:", 2,3);
        OSD_ShowString(X_POS_1, 50,  "SONG:", 2,3);
        OSD_ShowString(X_POS_1, 80,  "ARTIST:", 2,3);
        OSD_ShowString(X_POS_3, 20,  lyr->album, 2,3);
        OSD_ShowString(X_POS_2, 50,  lyr->song, 2,3);
        OSD_ShowString(X_POS_3, 80,  lyr->artist, 2,3);
        #else
        OSD_ShowString(X_POS_1, 20,  "SONG:", 2,3);
        OSD_ShowString(X_POS_1, 50,  "ARTIST:", 2,3);
        OSD_ShowString(X_POS_2, 20,  lyr->song, 2,3);
        OSD_ShowString(X_POS_3, 50,  lyr->artist, 2,3);    
        #endif
    #endif//#if defined( SUPPORT_FONT_CP_950 ) || defined( SUPPORT_FONT_CP_950_COMPRESSED ) || defined( SUPPORT_FONT_CP_950_COMMON ) || defined( SUPPORT_FONT_CP_950_COMMON_COMPRESSED )
    }  
    else//ID3 not exit , toggle off region3
    {
         osd_tog_region(REGION3, OSD_OFF);
    }
}
#endif

#ifdef GPS_MP3_UI		//suxin 050920,for GPS_MP3_UI
 #define	GPS_MP3_ARTIST_LEN		14
void DrawID3_GUI(void)
{       
 	extern const BTNAREA fsArea[];
    #if defined( SUPPORT_FONT_CP_950 ) || defined( SUPPORT_FONT_CP_950_COMPRESSED ) || defined( SUPPORT_FONT_CP_950_COMMON ) || defined( SUPPORT_FONT_CP_950_COMMON_COMPRESSED )
		FSGUI_ShowString(fsArea[FS_AREA_ARTIST_INFO].xStart+40, fsArea[FS_AREA_ARTIST_INFO].yStart+3, "ARTIST : ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		FSGUI_ShowString(fsArea[FS_AREA_ARTIST_INFO].xStart+150, fsArea[FS_AREA_ARTIST_INFO].yStart+3, lyr->artist, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
	#elif defined( SUPPORT_FONT_CP_936 ) || defined( SUPPORT_FONT_CP_936_COMPRESSED ) || defined( SUPPORT_FONT_CP_936_COMMON ) || defined( SUPPORT_FONT_CP_936_COMMON_COMPRESSED )
		FSGUI_ShowString(fsArea[FS_AREA_ARTIST_INFO].xStart+40, fsArea[FS_AREA_ARTIST_INFO].yStart+3, "ARTIST: ", FS_FONTCOLOR_PATH_Y, FS_FONTCOLOR_PATH_CrCb);
		FSGUI_ShowString(fsArea[FS_AREA_ARTIST_INFO].xStart+150, fsArea[FS_AREA_ARTIST_INFO].yStart+3, lyr->artist, FS_FONTCOLOR_PATH_Y, FS_FONTCOLOR_PATH_CrCb);
	#else
		if((strlen(lyr->artist))>GPS_MP3_ARTIST_LEN)
		{
			lyr->artist[GPS_MP3_ARTIST_LEN]='\0';
		}
		FSGUI_ShowString(fsArea[FS_AREA_ARTIST_INFO].xStart+40, fsArea[FS_AREA_ARTIST_INFO].yStart+3, "ARTIST: ", FS_FONTCOLOR_PATH_Y, FS_FONTCOLOR_PATH_CrCb);
		FSGUI_ShowString(fsArea[FS_AREA_ARTIST_INFO].xStart+150, fsArea[FS_AREA_ARTIST_INFO].yStart+3, lyr->artist, FS_FONTCOLOR_PATH_Y, FS_FONTCOLOR_PATH_CrCb);
    #endif                          
 
}

#else// #ifdef GPS_MP3_UI 
void DrawID3_GUI(void)
{
    #ifdef FSGUI_CUT_ID3_SONGNAME//added by wangwei,2005-3-29 20:05
    UINT8 i;
    char cutSongName[26] = {"                         "};
    char cutArtistName[26] = {"                         "};
    #endif//FSGUI_CUT_ID3_SONGNAME
    
    #if !defined(SUPPORT_OSDID3)&&!defined(NO_LIRIC_ID3)	//2004-5-5 02:33?”ÓP
	FSGUI_FillFrameBuf(36, 8, 316, 50, BK_GROUNDY, BK_GROUNDCRCB);
    #endif
    
    //#ifdef SUPPORT_MIX_MP3_CDDA   //linrc change "SUPPORT_MIX_MP3_CDDA" to "SUPPORT_MIX_DATA_CDDA_DISC"
    #ifdef SUPPORT_MIX_DATA_CDDA_DISC //because we not only support this type mix mode disc 2004-12-15 15:53
	if (GetCurrentFileType() != CDDA)
    #endif 
	{
        #ifdef NO_LIRIC_ID3  //2004-5-5 12:44?”ÓP
	    FSGUI_FillFrameBuf(36, 240,320,40, BK_GROUNDY, BK_GROUNDCRCB);
        #endif
        
    #ifdef SUPPORT_OSDID3//liweihua add 20040107
        show_id3();
    #elif defined(SUPPORT_ID3)
		if (lyr->id3_exist)
		{
        #if defined( SUPPORT_FONT_CP_950 ) || defined( SUPPORT_FONT_CP_950_COMPRESSED ) || defined( SUPPORT_FONT_CP_950_COMMON ) || defined( SUPPORT_FONT_CP_950_COMMON_COMPRESSED )
			FSGUI_ShowString(36, 8, "∫q¶± : ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36, 24, "∫q§‚ : ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36 + 56, 8, lyr->song, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36 + 56, 24, lyr->artist, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
	#elif defined( SUPPORT_FONT_CP_936 ) || defined( SUPPORT_FONT_CP_936_COMPRESSED ) || defined( SUPPORT_FONT_CP_936_COMMON ) || defined( SUPPORT_FONT_CP_936_COMMON_COMPRESSED )
			FSGUI_ShowString(36, 8, "∏Ë«˙ : ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36, 24, "∏Ë ÷ : ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36 + 56, 8, lyr->song, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36 + 56, 24, lyr->artist, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);    
	#else
            
            #ifdef NO_LIRIC_ID3   //2004-4-22 03:42’≈”ÓP
            
            //FSGUI_FillFrameBuf(96, 244, 250, 50, BK_GROUNDY, BK_GROUNDCRCB);
            FSGUI_ShowString(36, 240, "SONG: ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb); 
                #ifdef FSGUI_CUT_ID3_SONGNAME//added by wangwei,2005-3-29 20:05
            if(strlen( lyr->song ) > 25)
            {
                for(i=0;i<22;i++)
                {
                    cutSongName[i] = lyr->song[i];
                }
                //cutSongName[22] = '.';
                //cutSongName[23] = '.';
                //cutSongName[24] = '.';
                FSGUI_ShowString(36 + 64, 240, cutSongName, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb); 
            }
            else
                #endif//FSGUI_CUT_ID3_SONGNAME
			FSGUI_ShowString(36 + 64, 240, lyr->song, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb); 
			
			FSGUI_ShowString(36, 260, "ARTIST: ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb); 
                #ifdef FSGUI_CUT_ID3_SONGNAME//added by wangwei,2005-3-29 20:30
            if(strlen( lyr->artist ) > 25)
            {
                for(i=0;i<22;i++)
                {
                    cutArtistName[i] = lyr->artist[i];
                }
                //cutSongName[22] = '.';
                //cutSongName[23] = '.';
                //cutSongName[24] = '.';
                FSGUI_ShowString(36 + 64, 260, cutArtistName, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb); 
            }
            else
                #endif//FSGUI_CUT_ID3_SONGNAME
            FSGUI_ShowString(36 + 64, 260, lyr->artist, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
            #else//#ifdef NO_LIRIC_ID3   //2004-4-22 03:42’≈”ÓP
			FSGUI_ShowString(36, 8+10, "SONG: ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36 + 64, 8+10, lyr->song, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36, 24+10, "ARTIST: ", FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			FSGUI_ShowString(36 + 64, 24+10, lyr->artist, FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
            #endif//#ifdef NO_LIRIC_ID3   //2004-4-22 03:42’≈”ÓP
            
        #endif
		}
    #endif//#ifdef SUPPORT_OSDID3//liweihua add 20040107
	}
}
#endif	//end #ifdef GPS_MP3_UI 
#endif  //end defined(SUPPORT_ID3)||defined(SUPPORT_OSDID3)

#if defined(SUPPORT_MP3_ENCODER)||defined(SUPPORT_CD_RIPPING)
//linrc 2006-4-17 19:40
extern UINT32 recNew;
void Mp3_Encoder_message_show(Message_type message)
{
    #if defined(ORITRON_HK_DVD)||defined(OP_MP3_ENCODER_UI) //chenzhao 2006-4-20 10:51 .
	char Message_buf[29];
	#else
	char Message_buf[20];
	#endif
	
	switch(message)
	{
		case NO_DEVICE:
			strcpy(Message_buf,"NO DEVICE");
			break;
		case USB_READY:
			strcpy(Message_buf,"USB READY");
			break;
		case USB_ERROR:
			strcpy(Message_buf,"SUB ERROR");
			break;
		case USB_FULL:
			strcpy(Message_buf,"USB FULL");
			break;
		case DEVICE_FULL:
			strcpy(Message_buf,"DEVICE FULL");
			break;
		case SD_MMC_READY:
			strcpy(Message_buf,"SD MMC READY");
			break;
		case SD_MMC_ERROR:
			strcpy(Message_buf,"SD MMC ERROR");
			break;
		case UNSUPPORT_DEVICE:
			strcpy(Message_buf,"UNSUPPORT DEVICE");
			break;
		case DEVICE_WRITE_PROTECT:
			strcpy(Message_buf,"DEVICE WRITE PROTECT");
			break;
		case OPEN_FILE:
			strcpy(Message_buf,"OPEN FILE");
			break;
		case CLOSE_FILE:
			strcpy(Message_buf,"CLOSE FILE");
			break;
	  #ifdef SUPPORT_CD_RIPPING
	  case RECODER_NOMARL:
			strcpy(Message_buf,"RECODER NOMARL");
			break;	
	  case RECODER_2X:
			strcpy(Message_buf,"RECODER 2X");
			break;	
	  case FOLDER_ERROR:
			strcpy(Message_buf,"FOLDER ERROR");
		  break;	
	  case FILE_ERROR:
			strcpy(Message_buf,"FILE ERROR");
			break;	
	  case DEVICE_READY:
			strcpy(Message_buf,"DEVICE READY");
			break;	
	  case ERROR:
			strcpy(Message_buf,"ERROR");
		  break;	
	 #endif 
		     
	 #ifdef SUPPORT_MP3_ENCODER	
		case REC_MESSAGE:
            #if defined(ORITRON_HK_DVD)||defined(OP_MP3_ENCODER_UI) //chenzhao 2006-4-20 10:51 .
		 	psprintf(Message_buf, "CD RIPPING  TRACK %2d %2d %3d   ",v11_trk_now,cd_trk_hi,recNew);
	        Message_buf[20] = '/';
	        Message_buf[27] = '%';
	    	#else
			psprintf(Message_buf, "REC  %3d", recNew);
			Message_buf[8] = '%';
			Message_buf[9] = '\0';
	    	#endif 
	    	break;
    #endif 
		
		default:
			return;
		
	}
	osdshow( REGION1, Message_buf);
	
}
#endif

#ifdef RIPPING_MODE_SELECT //qinhua,add 2006-5-30 11:01œ¬ŒÁ
	
 /************GUI COLOR***************/
 #define SELECT_COLOR    5
 #define WIDTH           170
 #define HEIGHT          75
 #define FONT_COLOR      10
  
/************STEP COLOR***************/
 #define COLOR_BLUE      6
 #define STEP_COLOR      5
 #define STEP_WIDTH      500
 #define STEP_REIGON_HEIGHT 65
 #define STEP_HEIGHT     35
 #define GUI_REGION      2
 #define STEP_REGION     3
	
 #define __palette4F(G,B,R,A) \
        ( ((UINT32)((G)&0xff)<<24)|((UINT32)((B)&0xff)<<16)|((UINT32)((R)&0xff)<<8)|(A&0xff) )   
 
 static BYTE rip_leave=0;

void show_rip_gui(void)	
 {
	
	  osd_init_ripGUI();
	  rip_leave=1;
	  full_scrn=RIP_GUI;
	  
	  SetOsdCol(2,2,0,__palette4F(  179, 255, 0x88,0xe0)); 
	  
	  osd_DrawRegionLine(0, 0, WIDTH-1, 0, 2, 1, GUI_REGION);
	  osd_DrawRegionLine(0, 0, 0, HEIGHT-1, 2, 1, GUI_REGION);
	  
	  osd_DrawRegionLine(16, 8, WIDTH-20, 8, SELECT_COLOR, 24, GUI_REGION);
	  osd_DrawRegionString(1, 1, "RIP 1",FONT_COLOR,SELECT_COLOR,GUI_REGION); 
    
    osd_DrawRegionString(1, 9, "RIP ALL",FONT_COLOR,COLOR_BLUE,GUI_REGION); 
    
    SetFullscrnCmdFuncPtr(rip_func_up, rip_func_down,  ircmd_null,
                         ircmd_null, rip_func_select);
  }

void rip_func_up(void)	
 {
 	printf("----rip up-----\n\n");
 	
	if(rip_leave==2)
	{
	 rip_leave=1;
	 osd_DrawRegionLine(16, 8, WIDTH-20, 8, SELECT_COLOR, 26, GUI_REGION);
	 osd_DrawRegionString(1, 1, "RIP 1",FONT_COLOR,SELECT_COLOR,GUI_REGION); 
		 
	 osd_DrawRegionLine(16, 39, WIDTH-20, 39, COLOR_BLUE, 26, GUI_REGION);
	 osd_DrawRegionString(1, 9, "RIP ALL",FONT_COLOR,COLOR_BLUE,GUI_REGION); 
	 
	 }
	else 
	 {
	  rip_leave=2;
	  osd_DrawRegionLine(16, 39, WIDTH-20, 39, SELECT_COLOR, 26, GUI_REGION);
	  osd_DrawRegionString(1, 9, "RIP ALL",FONT_COLOR,SELECT_COLOR,GUI_REGION); 
	 
	  osd_DrawRegionLine(16, 8, WIDTH-20, 8, COLOR_BLUE, 26, GUI_REGION);
	  osd_DrawRegionString(1, 1, "RIP 1",FONT_COLOR,COLOR_BLUE,GUI_REGION); 
	  
	  }	
	}
	
void rip_func_down(void)	
 {
 	printf("----rip down-----\n\n");
 	 
 	if(rip_leave==1)
	 {
	  rip_leave=2;
	  osd_DrawRegionLine(16, 39, WIDTH-20, 39, SELECT_COLOR, 26, GUI_REGION);
	  osd_DrawRegionString(1, 9, "RIP ALL",10,SELECT_COLOR,GUI_REGION); 
	 
	  osd_DrawRegionLine(16, 8, WIDTH-20, 8, COLOR_BLUE, 26, GUI_REGION);
	  osd_DrawRegionString(1, 1, "RIP 1",10,COLOR_BLUE,GUI_REGION); 
	 }
	else 
	 {
	  rip_leave=1;
	  osd_DrawRegionLine(16, 8, WIDTH-20, 8, SELECT_COLOR, 26, GUI_REGION);
	  osd_DrawRegionString(1, 1, "RIP 1",10,SELECT_COLOR,GUI_REGION); 
	  
	  osd_DrawRegionLine(16, 39, WIDTH-20, 39, COLOR_BLUE, 26, GUI_REGION);
	  osd_DrawRegionString(1, 9, "RIP ALL",10,COLOR_BLUE,GUI_REGION); 
	 }		 
 }

void rip_func_select(void)	
{
    if(rip_leave==1)
      {
	   		fs_activate_rip();
       if (fs_is_activated_rip())
        ircmd_post_func(CMD_SELECT | v11_trk_now);
      
      //Show_Rip_Step_GUI();
       rip_func_exit();
       ripping_all_flag=0;
      }
    else if(rip_leave==2)		
      {
				fs_activate_rip();
      if (fs_is_activated_rip())
         ircmd_post_func(CMD_SELECT | v11_trk_now);
      
      //Show_Rip_Step_GUI(); 
      rip_func_exit();
      ripping_all_flag=1;
     }
}

void rip_func_exit(void)
 {
   osd_tog_region(2, OSD_OFF);
   osd_tog_region(3, OSD_OFF);
   full_scrn = 0;
 }

void Show_Rip_Step_GUI(void)
 {
   osd_init_ripGUI();
   SetOsdCol(3,3,0,__palette4F(  132,132, 132, 0xbf));//(G,B,R,A)
	
   osd_DrawRegionLine(0, 0, STEP_WIDTH, 0, 15, STEP_HEIGHT-1, STEP_REGION); 
  
	
  osd_DrawRegionLine(0, STEP_HEIGHT, STEP_WIDTH-1, STEP_HEIGHT, 8, 1, STEP_REGION);      
  osd_DrawRegionLine(0, STEP_HEIGHT, 0, STEP_REIGON_HEIGHT-1, 8, 1, STEP_REGION);   
  osd_DrawRegionLine(0, STEP_REIGON_HEIGHT-4, STEP_WIDTH-1, STEP_REIGON_HEIGHT-4, 8, 1, STEP_REGION);         
  osd_DrawRegionLine(STEP_WIDTH-1, STEP_HEIGHT, STEP_WIDTH-1, STEP_REIGON_HEIGHT-1, 8, 1, STEP_REGION); 
 
  
 // Show_Rip_Step();
 }
	
void Show_Rip_Step(void)
	{
	   #include "util.h"
	   UINT8 linetemp[32];
	   static   UINT32 recNew; 
	   recNew = ((M2I(p_msf) - M2I(st_msf)) * 100) / (M2I(e_msf) - M2I(st_msf));
  
   	#ifdef ORITRON_HK_DVD
	    psprintf(linetemp, "CD RIPPING  TRACK %2d %2d %3d  ",v11_trk_now,cd_trk_hi,recNew);
	    linetemp[20] = '/';
	    linetemp[27] = '%';
	    linetemp[28] = 0;
	  #else
	    psprintf(linetemp, "REC  %3d", recNew);
	    linetemp[8] = '%';
	    linetemp[9] = 0;
	  #endif
  
   osd_DrawRegionString(0, 0, linetemp,12,15,STEP_REGION); 
  
   osd_DrawRegionLine(4, 37, (STEP_WIDTH-2)*recNew/100, 37, SELECT_COLOR, 22, STEP_REGION);
	 
	 #ifdef USE_IR_FILTER  
	 if (recNew>0)
	   pfnIR_IRFilter1=IRFilter_All_Pass;
	 #endif   
	 
	 }
	
#endif //#ifdef RIPPING_MODE_SELECT //qinhua,add 2006-5-30 11:01œ¬ŒÁ



