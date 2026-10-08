/*
*  AVIQ new search function
*  <note:> system performance too bad ,and have some bugs... we must fine tune , terry
*/
#include "memmap0.h"

//
// DispCookOSD0
//      Prepare the content of OSD0 to temp buffer
//      (from OSD0_TEMP_YA-th KBytes in DRAM, size=38*16*1*24*4/8=7104 Bytes)
//
//      input   : bChange
//                  1 : re-generate all content
//                  0 : only update timing display parts
//                dwTime :
//                  < 0 : remain time (-00:00:00)
//                  > 0 : elapsed time( 00:00:00)
//
//      output  : none
//
//      side-effect : none
//
//      notes:
//      0     5          15  18   22  25
//      CD    TRACK      SPK PBC  REP TIME
//      VCD   TRACK      SPK PBC  REP TIME
//      SVCD  TRACK      SPK PBC  REP TIME
//      DVD   TITLE      CHAPTER      TIME
//      MP3   TRACK      SPK      REP TIME
//
//      Color table
//          palette_16color_setup(defined in osd1.c)
//


void hi_light_time(int pos)
{
    int time=0,shift_base=0;
	
    if((index_x-5)<=1)
    {
        time=goto_hour;
        shift_base=4;
    }
    else if((index_x-5)<=3)
    {
        time=goto_min;
        shift_base=3;
    }
    else if((index_x-5)<=5)
    {
        time=goto_sec;
        shift_base=2;
    }
    
    if((index_x-5)%2==0)//even
    {
        psprintf(linebuf, "%01d", time/10); 
        io_write("p");
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf,DISP_SHADOW,DISP_YGREEN); 
    }    
    else
    {
        psprintf(linebuf, "%01d", time%10); 
        io_write("o");
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf,DISP_SHADOW,DISP_YGREEN);  
        
    }   
}

void hi_light_chapter(int id,int pos)//kenny 2002/4/13
{
    if(index_x==2)
    {
        psprintf(linebuf, "%01d",id/100);  
        io_write("n");
        do_DispOSD0String(pos, 0, linebuf,DISP_SHADOW,DISP_YGREEN);
    }
    else if(index_x==3)
    {
        psprintf(linebuf, "%01d",(id%100)/10);     
        io_write("m");
        do_DispOSD0String(pos+1, 0, linebuf,DISP_SHADOW,DISP_YGREEN);
    }
    else if(index_x==4)
    {
        psprintf(linebuf, "%01d",id%10);       
        io_write("l");
        do_DispOSD0String(pos+2, 0, linebuf,DISP_SHADOW,DISP_YGREEN);    
    }
}   

void hi_light_title(int id, int pos)
{
    if(index_x==0)
    {
        psprintf(linebuf, "%01d",id/10);    
        io_write("k");
        do_DispOSD0String(pos, 0, linebuf,DISP_SHADOW,DISP_YGREEN);
    }
    else if(index_x==1)
    {
        psprintf(linebuf, "%01d",id%10);        
        io_write("j");
        do_DispOSD0String(pos+1, 0, linebuf,DISP_SHADOW,DISP_YGREEN);
    }
}



// YW ------- osd ---------- [Top]
// Modify 020725
void Print2OSDmem(int id,int val,UINT8 pos)
{
	BYTE    fontColor, bkColor; 
    
	bkColor = DISP_SHADOW; //OSD shadow color
	fontColor = DISP_GREEN; //green
    
	if(val) {       
		fontColor = DISP_YGREEN; //yellow-green                       
		if((full_scrn&GOTO) && !(val&COOK_S_LANG) && !(val&COOK_S_MODE)) {    
			
#ifdef NEW_GOTO//kenny 2002/4/13
			if(val&COOK_S_TIMER) {
				if(index_x>=5)
				{
					
					UINT32 time=disp_goto_time;
					disp_goto_time=disp_goto_time%10000000;
					goto_sec=time%100;            
					time=time/100;
					goto_min=time%100;
					time=time/100;
					goto_hour=time%100;   
					psprintf(linebuf, " %02d:%02d:%02d",goto_hour, goto_min, goto_sec);            
				} else {
					psprintf(linebuf, " %02d:%02d:%02d",show_time_hh, show_time_mm, show_time_ss);
					if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME)) // terry 2002/6/4 09:48PM : solve time in goto mode without '-'
 
					linebuf[0]='-';
				}
			} else 
			{
				if(pos!=COOK_CHP_VAL) 
				{//title            
					
					// yw0809	
					if(dvd_title)
						id=dvd_title;
					disp_dvd_title = id;                              
					psprintf(linebuf, "%02d/%02d",id,val);
					
					
					if(t_disp%10 == 3)
					{
						if(((index_x == 0) && (pos == COOK_AUDIO_VAL)) || ((index_x == 1) && (pos == COOK_SUBTITLE_VAL)))
						{
							fontColor = DISP_SHADOW;
							bkColor = DISP_YGREEN;
						}	
						else
						{
							bkColor = DISP_SHADOW; 
							fontColor = DISP_YGREEN; 
						}
					}
				} else {
					if(dvd_chapter) 
						id=dvd_chapter;
					disp_dvd_chapter = id;  
					psprintf(linebuf, "%03d/%03d",id,val);          
				}
			}   
#else   //#ifdef NEW_GOTO
			if(val&COOK_S_TIMER) {
				if(index_x==2) {
					UINT32 time=disp_goto_time;
                    
					bkColor = DISP_GBLUE;                        
					fontColor = DISP_WHITE; 
					disp_goto_time=disp_goto_time%10000000;
					goto_sec=time%100;            
					time=time/100;
					goto_min=time%100;
					time=time/100;
					goto_hour=time%100;             
					psprintf(linebuf, " %02d:%02d:%02d",goto_hour, goto_min, goto_sec);            
				} else {
                    psprintf(linebuf, " %02d:%02d:%02d", show_time_hh,show_time_mm, show_time_ss);
				}
			} else {
				if(pos!=COOK_CHP_VAL) {//title          
					if(index_x==0) {
						bkColor = DISP_GBLUE;                                
						fontColor = DISP_WHITE; 
					}
                    
					if(index_x!=2) {
						if(dvd_title) {
							if(dvd_title>val)
								dvd_title=dvd_title%10;
                            
							id=dvd_title;
						}
					}
					
					psprintf(linebuf, "%02d",id);                   
				} else {
					if(index_x==1) {
						bkColor = DISP_GBLUE;    
						fontColor = DISP_WHITE; 
					}
					
					if(index_x!=2) {
						if(dvd_chapter) {
							if(dvd_chapter>val)
								dvd_chapter=dvd_chapter%10;
                            
							id=dvd_chapter;
						}
					}
					psprintf(linebuf, "%03d",id);   
				}
                
                io_write("b");
				do_DispOSD0String(pos, 0, linebuf, fontColor,bkColor); 
				bkColor = DISP_SHADOW; //OSD shadow color                
				
				if(pos==COOK_CHP_VAL) {
					pos+=3;
					psprintf(linebuf, "/%03d",val); 
				} else {
					pos+=2;
					psprintf(linebuf, "/%02d",val);
				}
			}               
#endif//NEW_GOTO
			
			
        }else if(val&COOK_S_TIMER)
        {
            psprintf(linebuf, " %02d:%02d:%02d", show_time_hh, show_time_mm,show_time_ss);         
            if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME)) // terry 2002/6/4 09:48PM : solve time in goto mode without '-'
			linebuf[0]='-';
            
        }else if(val&COOK_S_LANG)
        {           	
			
        				/* alan modifide 2002/5/30 09:53PM to cut SUP-LAN fit in display */
        				UINT8 *str=get_lang_name(id);
						BYTE len=strlen(str);
						
						if(len == 1)
							str = "  "; 	               
        				        				
						strcpy(linebuf,str);//nono 2-11-22 18:20
						
						if (!IsOSDChinese()||((str[0]>='A')&&(str[0]<='Z'))) 
                        {   
							str[MAX_ENG_WORDS]='\0';
                        } else {
							//if (len>4){
							if (len>6){//nono 2-11-22 11:06
								
#if defined(USE_TCHINESE_OSD)//2-10-9 17:51
						psprintf(linebuf+2,"%s",TCh_yu);
#else
						psprintf(linebuf+2,"%s",Ch_yu2);
#endif								
								/*
								str[2]='\r';
								str[3]='\x32';
								str[4]='\0';
								*/
							}
                        }                        
                        //psprintf(linebuf,"%s",str);
                        
						//#ifndef OSD_Function_Disable
						if((((index_x == 0) && (pos == COOK_AUDIO_LANG)) || ((index_x == 1) && (pos == COOK_SUBTITLE_LANG)) ) && (full_scrn&GOTO))
						{
							fontColor = DISP_SHADOW;
							bkColor = DISP_YGREEN;
						}	
						else
						{
							bkColor = DISP_SHADOW; 
							fontColor = DISP_YGREEN; 
						}
						//#endif  
		} else if(val&COOK_S_MODE)
		{
			//#ifndef OSD_Function_Disable
			if((index_x == 0) && (pos == COOK_AUDIO_TYPE) && (full_scrn&GOTO)) 
			{
				fontColor = DISP_SHADOW;
				bkColor = DISP_YGREEN;
			}	
			else
			{
				bkColor = DISP_SHADOW; 
				fontColor = DISP_YGREEN; 
			}
			//#endif 
			psprintf(linebuf,"%s",get_audio_mode());
			
		}       
		else 
		{
			psprintf(linebuf, "%d/%d",id,val);
		}
        } else {
			if(id==STR_OS_ICON_REP0) {
				id+=rep_mode; 
				if(rep_mode == REPEAT_DISC)         // maybe add another icon for repeat directory,panxing, 2002-3-13
					id--;
			}
			
			
			psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][id]);
			
			
			if( (pos==COOK_CD)&&((t_disp%10==1)||(t_disp%10==2)) ) { 
				fontColor = DISP_ORANGE;
			}
			
			
			switch(id)
			{
			case STR_OS_ICON_SPK :
				// CDDA,CDROM,SVCD,VCD SPK position on page 1,index = 2
				// DVD position on page 2,index = 0
				
				if((full_scrn&GOTO) && ((index_x == 2 && t_disp%10==1)||(index_x == 0 && t_disp%10==2)) )
				{
					fontColor = (user_mute !=0 ) ? DISP_GRAY : DISP_GBLUE;			
					bkColor = DISP_YGREEN;		
				}
				else
				{
					bkColor = DISP_SHADOW;
					fontColor = (user_mute !=0 ) ? DISP_GRAY : DISP_YGREEN;		
				}
				break;
				
			case STR_OS_PBC :
				// CDDA,CDROM,SVCD,VCD SPK position on page 2,index = 0
				if((full_scrn&GOTO) && (index_x == 0 && t_disp%10 ==2))
				{
					fontColor = (IsPBCOn()!=0) ? DISP_GBLUE : DISP_GRAY;			
					bkColor = DISP_YGREEN;		
				}
				else
				{
					bkColor = DISP_SHADOW;        
					fontColor = (IsPBCOn()!=0) ? DISP_YGREEN : DISP_GRAY;		
				}
				break;
				
				
			case STR_OS_ICON_REP0 :
			case STR_OS_ICON_REP1 :
			case STR_OS_ICON_REPD :
				// CDDA,CDROM,SVCD,VCD SPK position on page 1,index = 4
				// DVD position on page 2,index = 1
				if((full_scrn&GOTO) && ((index_x == 4 && t_disp%10==1)||(index_x == 1 && t_disp%10==2)) ) //index_x == 4)
				{
					fontColor = DISP_GBLUE;
					bkColor = DISP_YGREEN;
				}	
				else
				{
					bkColor = DISP_SHADOW;
					
					if(id == STR_OS_ICON_REP0)
						fontColor = DISP_GRAY;	
					else if(id == STR_OS_ICON_REP1)
						fontColor = DISP_YGREEN;
					else
						fontColor = DISP_ORANGE; 
				}
				break;
				
			case STR_OS_CHL :
			case STR_OS_CHR :
			case STR_OS_AUTO_L :
			case STR_OS_AUTO_R :
				// CDDA,CDROM,SVCD,VCD SPK position on page 1,index = 3
			case STR_OS_STEREO :
				// CDDA,CDROM,SVCD,VCD SPK position on page 1,index = 3
				// DVD position on page 2,index = 2               
				switch(audio_channel) 
				{
				case 0: // STEREO
					fontColor = DISP_YGREEN;
					break;
				case 1:
					fontColor = DISP_ORANGE;
					break;
				case 2:
					fontColor = DISP_GREEN;                       	
					break;
				case 3:
				case 4:
					fontColor = DISP_WHITE;  	
					break;
				}
				
				if(full_scrn&GOTO && ((index_x == 3 && t_disp%10 ==1) ||(index_x == 3 && t_disp%10 ==2 && cd_type_loaded==CDDVD))) //yw 021007
				{
					fontColor = DISP_GBLUE;
					bkColor = DISP_YGREEN;  
				}
				else
					bkColor = DISP_SHADOW;  
				break;
				
				case STR_OS_VSURROUND_SETUP :
				case STR_OS_OFF :
				case STR_OS_LTRT_SETUP :
                    // DVD position on page 2,index = 3  
					//#ifdef OSD_Function_Disable
    	           	   //   if((full_scrn&GOTO) && (index_x == 2) && (cd_type_loaded==CDDVD))	
					//#else
					if((full_scrn&GOTO) && (index_x == 3) && (cd_type_loaded==CDDVD))	
						//#endif
					{
						fontColor = DISP_GBLUE;
						bkColor = DISP_YGREEN;
					}	
					else
					{
						bkColor = DISP_SHADOW;
						if(id == STR_OS_VSURROUND_SETUP)
							fontColor = DISP_WHITE;
						else if(id == STR_OS_OFF)
							fontColor = DISP_GRAY;
						else
      	           	    	    fontColor = DISP_ORANGE;			
					}	
					
					//#ifndef OSD_Function_Disable
					if((index_x == 1) && (pos == COOK_SUBTITLE_VAL) && (id == STR_OS_OFF) && (t_disp%10 ==3) && (full_scrn&GOTO))
					{
						fontColor = DISP_SHADOW;
						bkColor = DISP_YGREEN;
					}	
					//#endif
					
					break;
				case STR_OS_SPACE :
					bkColor = DISP_WHITE;	
					fontColor = 0;
					break;
				case STR_OS_NONE :
					//#ifdef OSD_Function_Disable
					//  if((index_x == 0) && (pos == COOK_AUDIO_VAL) && (full_scrn&GOTO))
					//#else
					if((((index_x == 0) && (pos == COOK_AUDIO_VAL))||((index_x == 2) && (pos == COOK_ANGLE_VAL))) && (full_scrn&GOTO))
						//#endif
					{
						fontColor = DISP_SHADOW;
						bkColor = DISP_YGREEN;
					}	
					else
					{
						bkColor = DISP_SHADOW; 
						fontColor = DISP_YGREEN; 
					}
					break;
                }
				
        }
		
        {//bad designed , we maybe try other way.
			//int len=strlen(linebuf);
			//if((len+pos)>=37)
			//linebuf[len-1]=0;
			//bkColor = 0;
			io_write("a");
			do_DispOSD0String(pos, 0, linebuf, fontColor, bkColor);
#ifdef NEW_GOTO//kenny 2002/4/13
			if(full_scrn&GOTO) {
				
				if((index_x>=5)&&(val&COOK_S_TIMER))
					hi_light_time(pos);
				else if(pos==COOK_CHP_VAL) 
				{
					if(!(cd_type_loaded!=CDDVD))//VCD
					{
						hi_light_chapter(id,pos);
					}
					
				}
				else if(pos==COOK_TRK_VAL)
					hi_light_title(id,pos);
				
			}
#endif
        }
}




// YW ------- osd ---------- [Top]
// Modify 020725
void DispCookOSD0(BYTE bChange)
{
	UINT8  *buf;
	//UINT32  i;  
	
	if (t_disp==0) return;
	
	buf = (UINT8 *)(SDRAM_BASE + (OSD0_TEMP_YA*1024));
	
	if (bChange) 
	{
		if((cd_type_loaded==CDDA) && (rep_ab_mode==REPEAT_AB_IDLE))
		{ 
            //when cd_type_loaded=CDDA, system will check which cddaType(CDDA/DTSCD/HDCD),
            //to reduce " " ,  "HD/DTS" string(on OSD) change
            //we add this checking
			cddaType = 0;            		
		} 
		
		
		//clear all temp-buf
		memset(buf,0,8*1024);		
		
		switch(t_disp%10)
		{
			
		case 1:
			Print2OSDmem(osd_cd_id[cd_type_loaded],0,COOK_CD);
			
			//Print2OSDmem(STR_OS_ICON_CLOCK,0,COOK_CLOCK); 
			switch(cd_type_loaded)
			{
			case CDSVCD:
			case CDVCD20:
			case CDVCD10:
				Print2OSDmem(STR_OS_TRACK,0,COOK_TRK); 
				Print2OSDmem(disp_trk_now,cd_total_trk(),COOK_TRK_VAL);
				
				switch(audio_channel)
				{
				case 0:
					Print2OSDmem(STR_OS_STEREO,0,COOK_PBC+1);
					break;
				case 1:
					Print2OSDmem(STR_OS_CHL,0,COOK_PBC+1);
					break;
				case 2:
					Print2OSDmem(STR_OS_CHR,0,COOK_PBC+1);
					break;
					
				case 3:
					Print2OSDmem(STR_OS_AUTO_L,0,COOK_PBC-1);
					
					break;
				case 4:
					Print2OSDmem(STR_OS_AUTO_R,0,COOK_PBC-1);
					break;
				}
				Print2OSDmem(STR_OS_ICON_SPK,0,COOK_SPK);
				Print2OSDmem(STR_OS_ICON_REP0,0,COOK_CLOCK+2);
				break;
				
				case CDROM:
					Print2OSDmem(STR_OS_TRACK,0,COOK_TRK);
					Print2OSDmem(STR_OS_ICON_SPK,0,COOK_SPK);
					Print2OSDmem(STR_OS_ICON_REP0,0,COOK_REP);
					if(play_state==VCD_STATE_STOP)
						Print2OSDmem(mp3_file_count(),mp3_file_count(),COOK_TRK_VAL);     
					else
						Print2OSDmem(disp_trk_now,mp3_file_count(),COOK_TRK_VAL);
					Print2OSDmem(STR_OS_ICON_CLOCK,0,COOK_CLOCK); 
					break;
					
				case CDDA:
					Print2OSDmem(STR_OS_TRACK,0,COOK_TRK); 
					Print2OSDmem(STR_OS_ICON_SPK,0,COOK_SPK);
					Print2OSDmem(STR_OS_ICON_REP0,0,COOK_CLOCK);
					Print2OSDmem(disp_trk_now,cd_total_trk(),COOK_TRK_VAL);
					
					switch(audio_channel)
					{
					case 0:
               			    		Print2OSDmem(STR_OS_STEREO,0,COOK_PBC);
									break;
					case 1:
               			    		Print2OSDmem(STR_OS_CHL,0,COOK_PBC);
									break;
					case 2:
               			    		Print2OSDmem(STR_OS_CHR,0,COOK_PBC);
									break;
					case 3:
               			    		Print2OSDmem(STR_OS_CHL,0,COOK_PBC);
									//Print2OSDmem(STR_OS_AUTO_L,0,COOK_PBC);
									break;
					case 4:
						Print2OSDmem(STR_OS_CHR,0,COOK_PBC);
               			    		//Print2OSDmem(STR_OS_AUTO_R,0,COOK_PBC);
						break;
					}
					Print2OSDmem(STR_OS_ICON_CLOCK,0,COOK_CLOCK+2); 
					break;
					
					case CDDVD:
#ifdef DVD_AUDIO	// alan, 2002/11/13 01:41下午
						if (dAMG_LSN)
							Print2OSDmem(STR_OS_GROUP,0,COOK_TRK);        
						else
#endif						
							Print2OSDmem(STR_OS_TT,0,COOK_TRK);     
						Print2OSDmem(get_tt_info(DISP_TT),get_tt_info(DISP_TT_Ns),COOK_TRK_VAL);                
						
#ifdef DVD_AUDIO	// alan, 2002/11/13 01:41下午
						if (dAMG_LSN)
							Print2OSDmem(STR_OS_TRACK,0,COOK_CHP);        
						else
#endif						
							Print2OSDmem(STR_OS_CHP,0,COOK_CHP);        
						Print2OSDmem(get_tt_info(DISP_CH),get_tt_info(DISP_CH_Ns),COOK_CHP_VAL);                
						
						Print2OSDmem(STR_OS_ICON_CLOCK,0,COOK_CLOCK_VAL); 
						break;
			}
			
			break;
			case 2:
				switch(cd_type_loaded)
				{
					
				case CDDVD:
					{
						int pos;            
						
						Print2OSDmem(osd_cd_id[cd_type_loaded],0,COOK_CD);
						pos = COOK_TRK+1;
						Print2OSDmem(STR_OS_ICON_SPK,0,pos);
						pos = pos+4;
						Print2OSDmem(STR_OS_ICON_REP0,0,pos);
						
						Print2OSDmem(STR_OS_ANGLE,0,COOK_ANGLE);
						if(get_angle_Ns())
							Print2OSDmem(NP_AGLN,get_angle_Ns(),COOK_ANGLE_VAL);          
						else
							Print2OSDmem(STR_OS_NONE,0,COOK_ANGLE_VAL);   
						
						pos = 6+COOK_ANGLE_VAL;   
						
						Print2OSDmem(STR_OS_SURR,0,pos);
						
						if(IsOSDChinese())
						{	
							pos = pos+4;
							//do_DispOSD0String(pos+11,0,"         ",DISP_WHITE,0);
						}
						else
						{
							pos = pos+9; 
							//do_DispOSD0String(pos+8,0,"       ",DISP_WHITE,0);
						}
						
						switch(sound_type)
						{
						case STR_OS_LTRT_SETUP : // LT/RT
							Print2OSDmem(STR_OS_LTRT_SETUP,0,pos);
							break;
						case STR_OS_VSURROUND_SETUP : // 虛敻擬蘌?							Print2OSDmem(STR_OS_VSURROUND_SETUP,0,pos);
							break;
						case STR_OS_OFF : // 關
							Print2OSDmem(STR_OS_OFF,0,pos);
							break;
						case STR_OS_STEREO : //  立體聲
							Print2OSDmem(STR_OS_STEREO,0,pos);					  
							break;
						}
						
					}
					
					break;
					
				case CDSVCD:
				case CDVCD20:
				case CDVCD10:
					Print2OSDmem(osd_cd_id[cd_type_loaded],0,COOK_CD); 
					Print2OSDmem(STR_OS_PBC,0,COOK_TRK); 
					io_write("7");
					do_DispOSD0String(COOK_TRK+6,0,"                           ",DISP_WHITE,0);
					break;
				case CDROM:
					
					break;
				case CDDA:
					
					break;
					
				}
               	break;
            case 3:
				{
					int id,show; 
					Print2OSDmem(osd_cd_id[cd_type_loaded],0,COOK_CD);
					if( (cd_type_loaded == CDDVD) || (cd_type_loaded == CDSVCD))
					{
						if(cd_type_loaded!=CDSVCD) 
						{
							if(pDSV->CurrDomain==TT_DOM)
								show=1;
							else
								show=0;
						} else
							show=1;
							
						Print2OSDmem(STR_OS_AUDIO,0,COOK_AUDIO); 
						Print2OSDmem(STR_OS_SUBTITLE,0,COOK_SUBTITLE);

#ifdef DVD_AUDIO
						if (dAMG_LSN && (pDSV->tt_info.dTT_PB_TY&0x80))
						{
							if( show&&(pDSV->dAv_AST_Ns) )
								Print2OSDmem((NP_ASLN&0x0001)+1,pDSV->dAv_AST_Ns,COOK_AUDIO_VAL);
							else
								Print2OSDmem(STR_OS_NONE,0,COOK_AUDIO_VAL);
							Print2OSDmem(STR_OS_AUDIO,COOK_S_LANG,COOK_AUDIO_LANG);
							Print2OSDmem(NP_ASTN,COOK_S_MODE,COOK_AUDIO_TYPE);								
						} else
#endif
						if( ((NP_ASTN&0xf)<=8)&&show&&(pDSV->dAv_AST_Ns) ) 
						{
							/* alan 02-05-27 modified */
							if (((NP_ASTN+1)>pDSV->dAv_AST_Ns)&&(pDSV->dAv_AST_Ns==1))
								Print2OSDmem(1,pDSV->dAv_AST_Ns,COOK_AUDIO_VAL);
							else 
								Print2OSDmem(NP_ASTN+1,pDSV->dAv_AST_Ns,COOK_AUDIO_VAL);
									
							Print2OSDmem(STR_OS_AUDIO,COOK_S_LANG,COOK_AUDIO_LANG);
							Print2OSDmem(NP_ASTN,COOK_S_MODE,COOK_AUDIO_TYPE);
						} else {
							Print2OSDmem(STR_OS_NONE,0,COOK_AUDIO_VAL);
						}
							
						id=NP_SPSTN&0x3f;
						if( (NP_SPSTN&0x40)&&(id<=pDSV->dAv_SPST_Ns)&&show ) {                
							Print2OSDmem(id+1,pDSV->dAv_SPST_Ns,COOK_SUBTITLE_VAL);     
							Print2OSDmem(STR_OS_SUBTITLE,COOK_S_LANG,COOK_SUBTITLE_LANG);
						} else {
							Print2OSDmem(STR_OS_OFF,0,COOK_SUBTITLE_VAL);                
						}              
					}
				}
				break;
            }
        }   
		
		
		
        //  bChange = 0 : only update timing display parts
        if (t_disp%10==1) 
        { 
			Print2OSDmem(0,COOK_S_TIMER,COOK_CLOCK_VAL+2);
            if ((cd_type_loaded==CDDA) && (coding_mode_now!=AUDIF_CODING_MODE_DTSCD))
            {
				int     myCDDAType;
                myCDDAType = getCDDAType();
                //if (myCDDAType!=cddaType) //Jeff mark 20021112
                {
					cddaType = myCDDAType; //Jeff 20020617
                    if (myCDDAType==0) 
                    {	//CDDA ICON
						//strcpy(linebuf, "    "); //Jeff 20020617
                        strcpy(linebuf, "       "); //Jeff 20020617
                    } 
                    else 
                    {   //HDCD ICON
						//strcpy(linebuf, "HDCD"); //Jeff 20020413
                        strcpy(linebuf, "HDCD   "); //Jeff 20020413
                    }
                    io_write("6");
                    do_DispOSD0String(COOK_PBC, 0, linebuf,DISP_YGREEN,DISP_SHADOW); //Jeff 20020413
                }                        
			}
			if((cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) && ((coding_mode_now==AUDIF_CODING_MODE_DTSCD)||(coding_mode_now==AUDIF_CODING_MODE_PCM))) 
			{ 
				//strcpy(linebuf, "DTS");
				io_write("5");
                strcpy(linebuf, "DTS    ");
				do_DispOSD0String(COOK_PBC, 0, linebuf,DISP_YGREEN,DISP_SHADOW); //Jeff20020413
			}
			
        } 
        /*
        else if (t_disp%10==3) 
        { 
		Print2OSDmem(0,COOK_S_TIMER,COOK_CLOCK_VAL);
        }
        */
}

// YW ------- osd ---------- [Bottom]



