#include "config.h"
#include "regmap.h"
#include "global.h"
#include "func.h"
#include "cfont.h"
#include "epp.h"
#include "macro.h"
#include "user_init.h"
#include "osd.h"
#include "vfdfunc.h"
#include "util.h"
#include "func.h"
#include "stdlib.h"

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
        #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif    

//#define     OSDUTIL_DBG     1
#ifdef SUPPORT_MIDI
#include "fsmidi.h"
#ifdef SUPPORT_MIDI_MENU_SEL
#include "fsMidiUI.h"
#endif
#endif


extern  BYTE bin2asc(BYTE pp);  /*jhuang 2000/11/27 reduce warning*/ 
extern  void osd_init4(void);
void    region_update_empty(BYTE ,BYTE ,BYTE);
void    region_clear_arrow(BYTE,BYTE);
void    region_update_item(BYTE ,BYTE,BYTE);

#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 18:15
extern int GetVideoSetValue(int id);
#endif//VIDEO_SETUP_NEW_GUI

#ifdef MIC_FUNCTION_KEY
extern BYTE bFuncStep;//nono 20040107
#endif//MIC_FUNCTION_KEY

#include "osd_jpg_rotate.c" //Maoyong 2004.06.30

//
// show_level
//
void show_level(int id,INT8 level,BYTE total_level) 
{ 
	BYTE i;
	int pos;

    PatternMode=id;
	if (id==Echo_Font_ID) {
		linebuf[0] = ' ';
		linebuf[1] = '[';
		pos = 2;
		
		for(i=pos;i<level+pos;i++) {
			linebuf[i] = N_longbar; //long bar 
		}
		
		for(i=level+pos;i<total_level-1+pos;i++) {
			linebuf[i] = N_shortbar; //short bar  
		}
		
		linebuf[total_level-1+pos] = 0;
		
		psprintf(RegionValStr[REGION1],"] %02d",level);
		strcat1(linebuf,RegionValStr[REGION1]);
		
		strcpy(RegionValStr[REGION1], linebuf);
		PrintOsdMsg(STR_OS_ECHO, REGION1, 1, 1);
	} else if (id==Mic_Font_ID) {
		linebuf[0] = ' ';
		linebuf[1] = '[';
		pos = 2;
		
		for(i=pos;i<level+pos;i++) {
			linebuf[i] = N_longbar; //long bar 
		}
		
		for(i=level+pos;i<total_level-1+pos;i++) {
			linebuf[i] = N_shortbar; //short bar  
		}
		
		linebuf[total_level-1+pos] = 0;
		
		psprintf(RegionValStr[REGION1],"] %02d",level);
		strcat1(linebuf,RegionValStr[REGION1]);
		
		strcpy(RegionValStr[REGION1], linebuf);

#if defined(MIC_2CHANNEL)&&defined(MIC_FUNCTION_KEY)
		if(bFuncStep==1)
			PrintOsdMsg(STR_OS_MIC_VOL_1, REGION1, 1, 1);
		else
			PrintOsdMsg(STR_OS_MIC_VOL_2, REGION1, 1, 1);
#else//MIC_2CHANNEL
		PrintOsdMsg(STR_OS_MIC_VOL, REGION1, 1, 1);
#endif//MIC_2CHANNEL


	}
	/*        // jason ych mark it 2-9-30 15:36
	else if (id==Volume_Font_ID) {
	linebuf[0] = ' ';
	linebuf[1] = '[';
	pos = 2;
	
	  for(i=pos;i<level+pos;i++) {
	  linebuf[i] = N_longbar; //long bar 
	  }
	  
		for(i=level+pos;i<total_level-1+pos;i++) {
		linebuf[i] = N_shortbar; //short bar  
		}
		
		  linebuf[total_level-1+pos] = 0;
		  
			psprintf(RegionValStr[REGION1],"] %02d",level);
			strcat1(linebuf,RegionValStr[REGION1]);
			
			  strcpy(RegionValStr[REGION1], linebuf);
			  PrintOsdMsg(STR_OS_VOL, REGION1, 1, 1);
			  } 
	*/
#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
	else if (id==Volume_Font_ID||id==VOL_DRC_ID||id==AMP_F_VOL_ID \
        ||id==AMP_S_VOL_ID||id==AMP_C_VOL_ID||id==AMP_SW_VOL_ID)
#else 
        else if ( (id==Volume_Font_ID) 
                #ifdef CNTR_5SPK_VOLUME
                ||(id==VOL_FL_ID)||(id==VOL_FR_ID) ||(id==VOL_SL_ID) ||(id==VOL_SR_ID) ||(id==VOL_C_ID) ||(id==VOL_SW_ID) //Jeff 20031028
                #endif //CNTR_5SPK_VOLUME
                )
#endif
	{
        #ifdef CNTR_5SPK_VOLUME//wangfeng 2003-11-12 13:54
        {
            int i;
            linebuf[0] = ' ';
            pos = 2+5;
            for (i=1; i<5; i++) {
                linebuf[i] = ' ';
            }
            if (id==VOL_FL_ID) {
                linebuf[2] = 'F';
                linebuf[4] = 'L';
            } else if (id==VOL_FR_ID) {
                linebuf[2] = 'F';
                linebuf[4] = 'R';
            } else if (id==VOL_SL_ID) {
                linebuf[2] = 'S';
                linebuf[4] = 'L';
            } else if (id==VOL_SR_ID) {
                linebuf[2] = 'S';
                linebuf[4] = 'R';
            } else if (id==VOL_C_ID) {
                linebuf[2] = 'C';
            } else if (id==VOL_SW_ID) {
                linebuf[2] = 'S';
                linebuf[4] = 'W';
            } else {
                linebuf[1] = 'M';
                linebuf[2] = 'A';
                linebuf[3] = 'I';
                linebuf[4] = 'N';
            }
        }
        #elif defined(OSD_BMP_REGION1)
            pos = 1;
        #else
		    pos = 2;
        #endif
    //#ifndef CNTR_5SPK_VOLUME    
	#ifdef	NEW_VOL_DISP_MODE

		linebuf[pos-2] = ':';
		linebuf[pos-1] = ' ';
		linebuf[pos] = 0;
		
	#else
        #ifdef OSD_BMP_REGION1
        	linebuf[pos-1] = ' ';
        #else
        linebuf[pos-2] = ' ';
		linebuf[pos-1] = '[';
        #endif
		
		//haoy add 2005-04-25 18:24
		#ifdef DVB1000_NON_OS
			total_level+=level;
			level=level*2;
		#endif
		for(i=pos;i<level+pos;i++) {
			
			#ifdef DVB1000_NON_OS
				linebuf[i] ='\r'; //table 2
				i++;
				linebuf[i]='\xa6'; //long bar
			#else
				linebuf[i] = N_longbar; //long bar 
			#endif
			
		}
		//haoy end 2005-04-25 18:24
		for(i=level+pos;i<total_level-1+pos;i++) {
			linebuf[i] = N_shortbar; //short bar  
		}
		
		linebuf[total_level-1+pos] = 0;
	#endif	//NEW_VOL_DISP_MODE
    //#endif
#ifdef Ti3001_OSD_UI_1
		if (id==Volume_Font_ID)
			psprintf(RegionValStr[REGION1],"] %02d DB",(level*4-60)); // MAX vol==0db and level=15
		else if(id==VOL_DRC_ID)
			psprintf(RegionValStr[REGION1],"] %02d DB",(level*2-36)); 
		else
			psprintf(RegionValStr[REGION1],"]%02dDB",level-10); 
		
#elif defined(Ti5026_OSD_UI_1)
		if (id==Volume_Font_ID)
			psprintf(RegionValStr[REGION1],"] %02d DB",(level-10)*2); // MAX vol==0db and level=15
		if( (id==AMP_F_VOL_ID)||(id==AMP_S_VOL_ID)||(id==AMP_SW_VOL_ID)||(id==AMP_C_VOL_ID))
			psprintf(RegionValStr[REGION1],"] %02d DB",(level-10)*2); // MAX vol==0db and level=15
		
		else if(id==VOL_DRC_ID)
			psprintf(RegionValStr[REGION1],"] %02d DB",(level*2-36)); 
		else
			psprintf(RegionValStr[REGION1],"]%02dDB",level-10); 
		
		
#else
	#ifdef	NEW_VOL_DISP_MODE
	    if (id==VOL_FL_ID) {
            psprintf(RegionValStr[REGION1],"FRONT_L VOL: %02d",level); 
        } else if (id==VOL_FR_ID) {
        	psprintf(RegionValStr[REGION1],"FRONT_R VOL: %02d",level); 
               
            } else if (id==VOL_SL_ID) {
               psprintf(RegionValStr[REGION1],"REAR_L VOL: %02d",level); 
                
            } else if (id==VOL_SR_ID) {
              
              psprintf(RegionValStr[REGION1],"REAR_R VOL: %02d",level);
            } else if (id==VOL_C_ID) {
                psprintf(RegionValStr[REGION1],"CENTER VOL: %02d",level);
            } else if (id==VOL_SW_ID) { //Jeff 20031028
                psprintf(RegionValStr[REGION1],"SUBWOOFER VOL: %02d",level);
            } else
            psprintf(RegionValStr[REGION1],"MAIN VOL: %02d",level);
	#else
		    #ifdef OSD_BMP_REGION1
                psprintf(RegionValStr[REGION1]," %02d",level);
	        #else
		    {
	        	#ifdef DVB1000_NON_OS
				psprintf(RegionValStr[REGION1],"] %02d",level/2);
			    #else
				#ifdef NODISC_SHOW_IN_DIFF_REGION
		        if(system_state == SYSTEM_NODISC)
		            psprintf(RegionValStr[REGION0],"] %02d",level);
		        else
                #endif
				psprintf(RegionValStr[REGION1],"] %02d",level);
                #endif
	        }
#endif
#endif
#endif
	#ifndef NEW_VOL_DISP_MODE//CNTR_5SPK_VOLUME
		#ifdef NODISC_SHOW_IN_DIFF_REGION
	    if(system_state == SYSTEM_NODISC)
		{
		    strcat1(linebuf,RegionValStr[REGION0]);
		    strcpy(RegionValStr[REGION0], linebuf);
        }
        else
		#endif
        {
		strcat1(linebuf,RegionValStr[REGION1]);
		
		strcpy(RegionValStr[REGION1], linebuf);
	    }
		#endif
		
#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
		if (id==Volume_Font_ID)
			PrintOsdMsg(STR_OS_AMP_MAINVOLUME, REGION1, 2, 1); // jason change t=2 2-9-30 15:12
		else  if(id==VOL_DRC_ID)
			PrintOsdMsg(STR_OS_AMP_DYNAMICRANGE, REGION1, 2, 1);
		else  if(id==AMP_F_VOL_ID)
			PrintOsdMsg(STR_OS_AMP_FSPK, REGION1, 2, 1);
		else  if(id==AMP_S_VOL_ID)
			PrintOsdMsg(STR_OS_AMP_SSPK, REGION1, 2, 1);
		else  if(id==AMP_C_VOL_ID)
			PrintOsdMsg(STR_OS_AMP_CSPK, REGION1, 2, 1);
		else  if(id==AMP_SW_VOL_ID)
			PrintOsdMsg(STR_OS_AMP_SUBWOOFER, REGION1, 2, 1);                                                                         
#else
	//avoid twinkling when adjust volume, wangfeng 2003-09-29 14:01
	#ifdef	NEW_VOL_DISP_MODE
		PrintOsdMsg(STR_OS_SPACE, REGION1, 2, 1);
	#else	
	    #ifdef NODISC_SHOW_IN_DIFF_REGION
		if(system_state == SYSTEM_NODISC)
		    PrintOsdMsg(STR_OS_VOL, REGION0, 1, 1);
		else
		#endif	
		PrintOsdMsg(STR_OS_VOL, REGION1, 1, 1);
#endif
#endif
	}  else if (id==AudKey_Font_ID) {
		linebuf[0] = ' ';
		linebuf[1] = '[';
		linebuf[2] = N_dkey; //b 
		pos = 2;
		
		for(i=pos+1;i<pos+6;i++) {
			linebuf[i] = N_dot; //.
		}
		linebuf[pos+6] = N_rkey; //key reset
		for(i=pos+7;i<pos+12;i++) {
			linebuf[i] = N_dot; //.
		}
		
		linebuf[pos+12] = N_ukey; //#
		linebuf[pos+level+6] = N_music; //music key
		
		linebuf[total_level+pos] = 0;
		
		psprintf(RegionValStr[REGION1],"] %02d",level);
		strcat1(linebuf,RegionValStr[REGION1]);
		
		strcpy(RegionValStr[REGION1], linebuf);
		PrintOsdMsg(STR_OS_KEY, REGION1, 1, 1);
	} else if (id==Score_Font_ID) { //Jeff 20020416
		linebuf[0] = ' ';
		linebuf[1] = '[';
		pos = 2;
		
		for(i=pos;i<(level/10+pos);i++) {
			linebuf[i] = N_longbar; //long bar 
		}
		
		for(i=(level/10+pos);i<total_level-1+pos;i++) {
			linebuf[i] = N_shortbar; //short bar  
		}
		
		linebuf[total_level-1+pos] = 0;
#ifdef MIDI_SCORE_TEST
                extern BYTE gb_showScore;
                if (gb_showScore)
                {
                    psprintf(RegionValStr[REGION1],"] %d",level);
                    strcat1(linebuf,RegionValStr[REGION1]);
		
                    strcpy(RegionValStr[REGION1], linebuf);
                    PrintOsdMsg(STR_OS_SCORE, REGION1, 0, 1);
                }else    
#endif        
                {
		psprintf(RegionValStr[REGION2],"] %2d",level);//axel for dynamically updating scoring 2005/6/7 
		strcat1(linebuf,RegionValStr[REGION2]);
		
		strcpy(RegionValStr[REGION2], linebuf);
		PrintOsdMsg(STR_OS_SCORE, REGION2, 0, 1);
	}
}//else if (id==Score_Font_ID) { //Jeff 20020416
/* freyman marked 2004-3-23 15:10 for no use
#ifdef SVA_SAMPLE
	else if (id==AMP_VOL_ID) {
		linebuf[0] = ' ';
		linebuf[1] = '[';
		pos = 2;
		
		for(i=pos;i<level+pos;i++) {
			linebuf[i] = N_longbar; //long bar 
		}
		
		for(i=level+pos;i<total_level-1+pos;i++) {
			linebuf[i] = N_shortbar; //short bar  
		}
		
		linebuf[total_level-1+pos] = 0;
		
		psprintf(RegionValStr[REGION1+3],"] %02d",level);
		strcat1(linebuf,RegionValStr[REGION1+3]);
		
		strcpy(RegionValStr[REGION1+3], linebuf);
		PrintOsdMsg(STR_OS_AMPVOL, REGION1+3, 0, 1);
		//PrintOsdMsg(STR_OS_VOL, REGION1+3, 0, 1);
	}
#endif*/
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 13:59
	else if((id == VIDEO_BIGHT_ID) ||
			(id == VIDEO_CONTRAST_ID) ||
			(id == VIDEO_HUE_ID) ||
			(id == VIDEO_SATURATION_ID)
#ifdef DIP_CFG_ENABLE
			||(id == VIDEO_DEINTERLACE_ID)
#endif//#ifdef DIP_CFG_ENABLE
			) 
	{
		//only SETUP valid.
		if(!(full_scrn & SETUP))		
			return;
		
		int region = 0;//SETUP use reigon 0
		BYTE TempStr[20];
		int iValue = 0;
		int str_id = 0;
		//printf("#### ----AAAAAAAAAAAAAAAAAAa  id :%d -\n",id);
		//linebuf[0] = ' ';
		linebuf[0] = '[';
		pos = 1;
		
		for(i=pos;i<level+pos;i++) 
		{
			linebuf[i] = N_longbar; //long bar 
		}
		
		for(i=level+pos;i<total_level-1+pos;i++) 
		{
			linebuf[i] = N_shortbar; //short bar  
		}
		
		linebuf[total_level-1+pos] = 0;
		
		
		switch(id)
		{
		    case VIDEO_BIGHT_ID:
		        str_id = STR_OS_BRIGHTNESS;
		        break;
		    case VIDEO_CONTRAST_ID:
		        str_id = STR_OS_CONTRAST;
		        break;
		    case VIDEO_HUE_ID:
		        str_id = STR_OS_HUE;
		        break;
		    case VIDEO_SATURATION_ID:
		        str_id = STR_OS_SATURATION;
		        break;
#ifdef 	DIP_CFG_ENABLE	    
		    case VIDEO_DEINTERLACE_ID:
		        str_id = STR_OS_DEINTLC;
		        break;
#endif//DIP_CFG_ENABLE		            
	        default: break;
	    }
		//get video value.
		psprintf(RegionValStr[region],"] %02d",GetVideoSetValue(str_id));
		strcat1(linebuf,RegionValStr[region]);
		strcpy(TempStr, linebuf);
		
		//get video string
		strcpy(linebuf,_OsdMessegeFont1[osd_font_mode][str_id]);
		strcat1(linebuf, TempStr);
		//linebuf value will be shown in SETUP OSD in setup_ShowVideoGUI (setup_tab_ui.c)
	}			
#endif//VIDEO_SETUP_NEW_GUI
#if defined(Ti3001_OSD_UI_1)||defined(Ti5026_OSD_UI_1)
	else if(id==VOL_TREBLE_ID||id==VOL_BASS_ID)
	{
		linebuf[0] = ' ';
		linebuf[1] = '[';
		pos = 2;
		
		for(i=pos;i<level/2+pos;i++) {      //clead 20020911
			linebuf[i] = N_shortbar; //short bar 
		}
		linebuf[i] = N_longbar; //long bar 
		for(i=level/2+pos+1;i<total_level/2+pos;i++) {      //clead 20020911
			linebuf[i] = N_shortbar; //short bar  
		}
		
		linebuf[total_level/2-1+pos] = 0;
		
		psprintf(RegionValStr[REGION1],"] %02d DB",level-18);
		strcat1(linebuf,RegionValStr[REGION1]);
		
		strcpy(RegionValStr[REGION1], linebuf);
		if(id==VOL_BASS_ID)
			PrintOsdMsg(STR_OS_AMP_BASS, REGION1, 2, 1);
		else
			PrintOsdMsg(STR_OS_AMP_TREMBLE, REGION1, 2, 1);
		
	}
	else if(id==AMP_F_BAL_ID||id==AMP_S_BAL_ID)
    {
        //linebuf[0] = ' ';
        //linebuf[1] = '[';
        linebuf[0] = '[';
        pos = 1;  //2
		
        for(i=pos;i<total_level+pos-1;i++) 
			linebuf[i] = N_shortbar; //short bar  
        if(level >total_level/2)
        {
			
			for(i=pos+(total_level/2);i<=level+pos;i++) 
				linebuf[i] = N_longbar; //long bar 
		}   
        else
        {
			
			for(i=level+pos;i<=total_level/2+pos;i++) 
				linebuf[i] = N_longbar; //short bar  
			
        }
		linebuf[total_level-1+pos] = 0;
		
		psprintf(RegionValStr[REGION1],"]%02dDB",level-10);
		strcat1(linebuf,RegionValStr[REGION1]);
		
		strcpy(RegionValStr[REGION1], linebuf);
		if(id==AMP_F_BAL_ID)
			PrintOsdMsg(STR_OS_AMP_FSPK_BALANCE, REGION1, 2, 1); 
		else
			PrintOsdMsg(STR_OS_AMP_SSPK_BALANCE, REGION1, 2, 1); 
    }
    
#endif

#ifdef BRIGHTNESS_COLOR_KEY
	else if(id==BRIGHTNESS_PLUS_ID)
	{
		BYTE i;                                                                         
    	                                                                           
    	linebuf[0] = '[';		                                                   
		                                                                           
        for(i=1;i<=level;i++)                                                   
		  linebuf[i] = N_longbar;                                                  
    	for(i=level+1;i<=total_level;i++)                                          
    	  linebuf[i] = N_shortbar;                                                 
    	                                                                           
        linebuf[total_level+1] = 0;                                             
		                                                                           
    	psprintf(RegionValStr[REGION1],"]%d",level);                               
    	                                                                           
    	strcat1(linebuf,RegionValStr[REGION1]);                                    
    	                                                                           
    	strcpy(RegionValStr[REGION1], linebuf);                                    
    	                                                                           
    	PrintOsdMsg(STR_OS_BRIGHTNESS, REGION1, 6, 1); //10 seconds to close osd   
	}
	else if(id==COLOR_PLUS_ID)
	{
		BYTE i;                                                                     
    	                                                                       
    	linebuf[0] = '[';		                                               
		                                                                       
        for(i=1;i<=total_level;i++)                                         
		  linebuf[i] = N_shortbar;		                                       
		linebuf[level] = N_longbar;                                            
    	linebuf[total_level+1] = 0;                                            
		if(level > 8)
    		psprintf(RegionValStr[REGION1],"]+%d",level-8);
    	else if (level < 8) 
    		psprintf(RegionValStr[REGION1],"]-%d",8-level);
    	else 
    		psprintf(RegionValStr[REGION1],"]%d",0);
    	                                                                       
    	strcat1(linebuf,RegionValStr[REGION1]);                                
    	                                                                       
    	strcpy(RegionValStr[REGION1], linebuf);                                
    	                                                                       
    	PrintOsdMsg(STR_OS_COLOR, REGION1, 6, 1); //10 seconds to close osd    
	}		
#endif //end #ifdef BRIGHTNESS_COLOR_KEY


#ifdef SUPPORT_FUNCTION_MENU
	else if(id == BRIGHTNESS_PLUS_ID)
	{
		//if(full_scrn&SETUP_PLUS)
        {
    	   BYTE i;
    	   
    	   #ifdef DEBUG_FUNCTION_MENU
		   printf("show brightness,:%d\n",level);
		   #endif
		   
		   linebuf[0] = '[';		   
		   for(i=1;i<=level;i++)
    	     linebuf[i] = N_longbar;
    	   
    	   for(i=level+1;i<=total_level;i++)
    	     linebuf[i] = N_shortbar;
    	   
    	   linebuf[total_level+1] = 0;
    	   
    	   if(level<7)
    	     psprintf(RegionValStr[REGION1],"]-%d",(total_level/2-level));
    	   else
    	     psprintf(RegionValStr[REGION1],"]%d",(level-total_level/2));
    	   
    	   strcat1(linebuf,RegionValStr[REGION1]);   
    	   
    	   strcpy(RegionValStr[REGION1], linebuf);
    	   PrintOsdMsg(STR_OS_BRIGHTNESS, REGION1, 5, 1); //10 seconds to close osd   
    	}
	}
#endif //end #ifdef SUPPORT_FUNCTION_MENU
#ifdef MP4_SHOW_PARSING_PROGRESS
	else if(id == SHOW_LEVEL_NO_ID)
	{
        BYTE i;

        #ifdef DEBUG_FUNCTION_MENU
	    printf("only show level (%d), no other stuff,:%d\n",level);
        #endif  //#ifdef DEBUG_FUNCTION_MENU

        linebuf[0] = '[';		   

        for(i=1;i<=level;i++)
            linebuf[i] = N_longbar;
    	   
        for(i=level+1;i<=total_level;i++)
            linebuf[i] = N_shortbar;

        linebuf[total_level+1] = ']';
        linebuf[total_level+2] = 0;

        strcpy(RegionValStr[REGION1], linebuf);
        PrintOsdMsg(STR_OS_SPACE, REGION1, 5, 1);
	}
#endif  //#ifdef MP4_SHOW_PARSING_PROGRESS
	/*
	switch(id)
	{    
	case  Echo_Font_ID:
	case  Volume_Font_ID:
	if(id==Echo_Font_ID) {
	if (osd_font_mode==1) { //Chinese
	strcpy(linebuf,OS_ECHO);
	strcat1(linebuf," [");
	} else {
	strcpy(linebuf,"ECHO [" );        
	}
	} else {
	if(osd_font_mode==1) {
	strcpy(linebuf,OS_VOL);
	strcat1(linebuf," [");
	} else 
	strcpy(linebuf,"VOL [");
	}
	
	  pos = strlen(linebuf);
	  
		for(i=pos;i<level+pos;i++) {
		linebuf[i] = N_longbar; //long bar 
		}
		
		  for(i=level+pos;i<total_level-1+pos;i++) {
		  linebuf[i] = N_shortbar; //short bar  
		  }
		  
			linebuf[total_level-1+pos] = 0;  
			break;
			
			  case  AudKey_Font_ID:
			  if(osd_font_mode==1) {
			  strcpy(linebuf,OS_KEY);
			  strcat1(linebuf," [");
			  } else
			  strcpy(linebuf,"KEY [");
			  
				pos = strlen(linebuf);
				
				  linebuf[pos] = N_dkey; //b 
				  
					for(i=pos+1;i<pos+6;i++) {
					linebuf[i] = N_dot; //.
					}
					
					  linebuf[pos+6] = N_rkey; //key reset
					  
                        for(i=pos+7;i<pos+12;i++) {
						linebuf[i] = N_dot; //.
                        }
						
						  linebuf[pos+12] = N_ukey; //#
						  linebuf[pos+level+6] = N_music; //music key
						  
							linebuf[total_level+pos] = 0;
							break;
							}
							
							  psprintf(RegionValStr[REGION1],"] %02d",level);
							  strcat1(linebuf,RegionValStr[REGION1]);
							  
								strcpy(RegionValStr[REGION1], linebuf);
								PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1); 
	*/
}
