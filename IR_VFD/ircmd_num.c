/*
*  Terry,2004/1/14 02:36PM
*/


/*******************************************************
** FUNCTION
**    ircmd_select_number
**
** DESCRIPTION:
** Function for IR number-key
**
** In:
**    num: numer 0~10
** Out:
**    None
************************************************************/
#ifdef OPEN_STATE_USE_3333_CHANGE_TV_SYSTEM//shenyj add for alco 11/22
extern void update_tv_format_sel(void);
#endif
//xulf added temporary here 2004-2-12 11:53
#if defined(SUPPORT_BASS_TREBLE)//xyy 2004-3-8
extern BYTE flag_BassAdjust,flag_TrebleAdjust;       //xulf 2004-01-12
#endif
//extern void ddx_ircmd_BassAdjust(int updown);
//extern void ddx_ircmd_TrebleAdjust(int updown);
#if defined(AMP_SUPPORT_EQ)
extern void ddx_EQ_Toggle(void);
#endif

#ifdef SUPPORT_MP3_ENCODER  //qinhua ,add 2005-11-29 21:52
extern void stop_current_ripping(void);
extern UINT32 recNew;
#endif 

#if defined(SUPPORT_REVERBERATION)
extern void ddx_Revb_Toggle(void);
#endif

#ifdef  MP3_DIRECT_SELECT_FAST2NORM     //Maoyong 2004.02.28 15:54
#define FAST2NORM           0x01<<0     
#define NOT_REALPLAY        0
extern void chg2normal_play(UINT8 md,UINT8 realplay);
extern UINT16 Is_JPEG_STATE(void);
#endif

#ifdef PMP_DVD //kenny 2005/7/29
extern void HDDCard_number_input(int num);
#endif


#ifdef CONTINUOUS_NUM_KEY_SELECT//Jack added 04/11/13
#define psdList        (pFsJpeg->List)

void ir_continuous_num_clr(void)
{
    ir_num1 = 0;
    ir_num2 = 0;
    ir_num3 = 0;
    ir_num4 = 0;
    ir_num_timer = 0;
    ir_select_number = 0;
    ir_num_state = NUM_STATE0;
}
#endif

void    ircmd_input_number(int num)
{
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
    UINT8 invalid=0;
#ifdef INVALID_WHEN_WRONG_REGION
    if((dvd_error == REGION_ERR) && !(full_scrn&SETUP) && !(full_scrn&CUSTM))
    {
       invalid_key();
       return;
    } 
#endif

#ifdef CONTINUOUS_NUM_KEY_SELECT
    if((!(full_scrn&PROGRAM))&&(!(full_scrn&SETUP))&&(!(full_scrn&GOTO)))
    {
      if(((cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD)) && IsPBCOn() && (is_menu()==0))       //wanghaoying 2003-8-25 23:01
    {
        invalid_key();
        return;
     }
    }
#endif 

#ifdef SUPPORT_MIDIDISK_TITLE
        if (bIsPlayMidiTitle)
        {
        invalid_key();
        return;
        }
#endif

#ifdef INVALID_NUMBER_IN_DVD_MENU     //XLJ2004-3-31
//invaild number keys during the short film in DVD menu, but need them available 
//in choosing Menu, so use both is_menu()  and HL_exist. heqiang, 2004-4-23 9:52
    if(/*is_menu()&&*/(HL_exist!=1)&&(cd_type_loaded==CDDVD)&&(!(full_scrn&PROGRAM))&&(!(full_scrn&SETUP))&&(!(full_scrn&GOTO)))    
    {//Jack mark is_menu() 04/11/29
        invalid_key();
        return;
    }
#endif//INVALID_NUMBER_IN_DVD_MENU


#ifdef INVALID_NUMBER_IN_REPEAT//wuxiaofeng 2004-03-05
    if(cd_type_loaded==CDDVD)//only for DVD use
    {
        if((rep_mode!=REPEAT_IDLE)||(rep_mode!=REPEAT_AB_IDLE))
        {
            invalid_key();
            return;
        }
    }
#endif
    
#ifdef JPG_OLD_PARSER_FLOW //winking.J  for num select 2006-6-29 11:32 
#ifndef JPG_EFFECT  
#ifndef ALCO_DVD_UI    
    if ( Is_JPEG_SlideMode() ) return;
#endif
#endif
#endif//JPG_OLD_PARSER_FLOW
    
//3-12-9 19:04 NONO MARKED.uopdate dsp code.  
//    if((cd_type_loaded == CDDVD) && (coding_mode_now == AUDIF_CODING_MODE_DTS))
//    setup_SetDTSDOWNMIXConfig();//3-11-25 22:55 zhangyu

#ifdef JPG_EFFECT
    num_sel_in_jpg = 1;
#endif  

#if defined(FAT_Write_UI)||defined(CF_CARD_WRITE)//||defined(WRITE_USB)//liweihua 2003-10-30 10:32
    extern void input_name(int num);
    extern BYTE input_flag;
    if((full_scrn & PERIPHERAL) && (input_flag == 1))
    {
        if(num ==10)
            invalid_key();
        else
            input_name(num);
        return;
    }
#endif

    switch(play_state)//kenny 891009
    {
    case VCD_STATE_IDLE://for no disc
    case VCD_STATE_OPEN:
        if(!full_scrn)
            invalid=1;
        break;
    case VCD_STATE_PREVIEW:
#ifdef DVD_PREVIEW_FUNCTION//terry,2004/2/7 07:11PM    
        if(cd_type_loaded!=CDDVD)        
#endif        
        {
            int max=cd_trk_hi-cd_trk_lo_now+1;

            if(v11_trk_now >= cd_trk_lo_now+9*((int)(max/9)))
            {
                if(num> max%9)
                    invalid=1;
            }
        }
    case VCD_STATE_9FRAMES:
        if(num==0 || num==10)
            invalid=1;
        break;
    } //end case

//huziqin 2006-4-24 removed

#if defined(SUPPORT_POWER_OFF_CLOCK_FUNC)//xyy 2004-10-12
    if(system_state==SYSTEM_DOING_CLOCK_FUNC)
    {
        ir_select_number = num;
        if(ir_select_number == 10)
            ir_select_number = 0;
        ClockFuncInput();
        return; 
    }
#endif

    if(shuffle_flag)
        invalid=1;

    if(invalid)
    {
        invalid_key();
    }else  if(full_scrn&PROGRAM)
    {
        ir_select_number=num;
        prog_func_input(num);
//  }else if(full_scrn&READ)
//  {
//      read_func_input(num);
    }else if(full_scrn&SETUP)
    {
#ifdef SCRN_SAVER_WHEN_PAUSE//zhaoyanhua add 2004-2-17 17:48        
        //NOTE:
        // add these code there to avoid the BUG:
        // when Slide Show JPEG, ROTATE,then SETUP,enter password GUI
        // when the number is more than two(such as "01"), it will excute SELECT 01
        // OR appear the SCREEN saver.
        // I don't know  whether adding these codes like this is reasonable.
        // But the result is correct.
        // zhaoyanhua add 2004-2-17 17:53
        
        extern UINT32 save_srn_start_t;
        save_srn_start_t = get_rtc_val();//axel 2004/3/11 02:44pm
        
       // save_srn_start_t = 0;
#endif//ifdef  SCRN_SAVER_WHEN_PAUSE  
        ir_select_number=num;

        
        setup_password();

#ifdef SHOW_STANDBY_TIMER //suqiaoli  add 2003-8-5
        setup_standby_timer_input();
#endif      
    }else if(full_scrn&GOTO) //kenny 2001/5/16
    {
        OSD1000ISP_STATUS(OSDISP_NUMGOTO, num);

#ifdef NEW_SEARCH_OSD
        if(t_disp%10 ==1) // ren 910725
        {            // ren 910725
            ir_select_number=num;
            search_func_input();
        }
#else
      #ifdef NEW_GOTO_TIME  //wangfeng 2003-11-15 21:47
        if((index_x==7)||(index_x==9)){
            if(num<6)
        ir_select_number=num;
            else
            return;
        }
        else 
      #endif  
        ir_select_number=num;
        search_func_input();
#endif
    }
#ifdef SUPPORT_FUNCTION_MENU
    #ifdef SUPPORT_DISPLAY_MENU
    else if(In_Goto_Menu() && (full_scrn&SETUP_PLUS))
    {
        setup_menu_plus_timer = DISPLAY_MENU_SHOW_TIME;
        ir_select_number = num;
        search_func_input();
        ShowSetupPage_plus(MENU_REFRESH);
        ir_select_number = 0;
    }
    #endif//end #ifdef SUPPORT_DISPLAY_MENU
#endif//#ifdef SUPPORT_FUNCTION_MENU
#ifdef NEWSTYLE_WINDOW            //xiongyuyue 20030703
    else if(full_scrn&MESSAGE)
    {
        ir_select_number=num;
        browse_func_input();
    }
#endif


#ifdef SUPPORT_REP_READ //Maoyong 2004.06.07
    else if(IsReadSetPBTimes()){
        ir_select_number = num;
        read_func_input();        
    }
#endif
    else
#ifndef IR_10_PLUS
	{
		{
            #ifdef STOP_NO_DIR_SELECT//libing 2005-4-28 9:18
	        if(play_state==VCD_STATE_STOP)
	        {
		        invalid_key();
		        return;
	        }
            #endif
			UINT8 max=2;
			UINT8 f[10]={" ---"};
			UINT8 jp=1;
          #if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
           if (media_type!=MEDIA_CARD)  //wthsin, 2004/7/7 02:34pm
          #endif
            if(IsPBCOn() && (is_menu()==0))       //wanghaoying 2003-8-25 23:01
            {
                invalid_key();
                return;
            }

            now_num_ns++;

            ir_select_number=ir_select_number*10+num;

            //printf("now_num_ns:%x num:%x ir_select_number:%x\n",now_num_ns,num,ir_select_number);
            if(cd_type_loaded==CDROM)
            {
                UINT16 tt=mp3_file_count();

                if(tt>=1000)//nono 2-7-15 9:47
                    max=4;
                else if(tt>=100)
                    max=3;
                else
                    max=2;
            }

            jp+=(max-now_num_ns);

            if(jp>1)
            {
                f[jp]='%';
                f[jp+1]='0';
                f[jp+2]='0'+now_num_ns;
                f[jp+3]='d';
                f[jp+4]=0;
                psprintf(RegionValStr[REGION1],f,ir_select_number);
                PrintOsdMsg(STR_OS_SELECT,REGION1,1,1);
#ifdef SUPPORT_TUNER       // add tuner 2-6-14 23:17
                if(play_state!=VCD_STATE_POWER)
#endif
                    timeout_osd[REGION1]=150;//terry,0508, avoid waiting too long
            }else
            {
                ir_num_select(ir_select_number);
            }


            return;
        }
    }
#else
    {
        if(num==10)
        {
            int max;

            if(IsPBCOn() && (is_menu()==0)&&(play_state!=VCD_STATE_STOP)
                #if defined(SUPPORT_CARD_STORAGE) || defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)//liweihua add 2004-3-26
                && (media_type != MEDIA_CARD)
                #endif
                )       //wanghaoying 2003-8-25 23:01
            {
                invalid_key();
                return;
            }
            
            ir_10p=1;
            ir_select_number+=10;
            if (cd_type_loaded==CDROM)//nono 20040226 for nintaus
                max=10000;
            else if(cd_type_loaded==CDDVD)
                max=1000;
            else
                max=100;

            if(ir_select_number>=max)
                ir_select_number=ir_select_number%max;

            #ifdef SUPPORT_IR10P_LIMIT//tianye 200607
	     int sel_num  =  ir_select_number;	
            

            if(ir_select_number > 10)
            {
                 flag_input   = 1 ;
                ir_num_select(sel_num)  ;
		  flag_input   = 0 ;		
	         if( ir_select_number  == 0)
	         {
                       ir_select_number =  sel_num -10;
		  }
	     }
	     #endif//#ifdef  SUPPORT_IR10P_LIMIT		


#ifdef OSD_SPECIAL_MENU             
            if(num==0)
                  OSD1000ISP_STATUS(ir_select_number/10,num+0xfa);      
            else
#endif
            OSD1000ISP_STATUS(ir_select_number/10, num);
#ifdef SHOW_NUM_AND_UNDERLINE
            psprintf(RegionValStr[REGION1],"%01d-",ir_select_number/10);
#else
            psprintf(RegionValStr[REGION1],"%02d+",ir_select_number);
#endif 
            #ifdef PUSH_P10_LONG_DISPLAY
            if(ir_select_number == 10)                  //zxb 2005-5-8 13:48
                PrintOsdMsg(STR_OS_SELECT,REGION1,5,1); 
            else        
            #endif
            PrintOsdMsg(STR_OS_SELECT,REGION1,1,1);
        }
        else
        {
            int x;
            if(num==0)
            {
                if(ir_select_number>0)
                    x = ir_select_number+num;
                else
                {
#ifdef ONLY_0//for "0" &"10" not in a key.
                    x = 0;
#else
                    x = 10;
#endif
                }
            }
            else
            {
                if(ir_select_number<10)
                    ir_select_number = 0;

                x = ir_select_number + num;
            }

            #ifdef SUPPORT_MIDI_MENU_SEL 
            if(gIsMidiSelMenu) 
            {
                ircmd_post_func(CMD_SELECT | (num));
                return;
            }
            #endif

            OSD1000ISP_STATUS(x/10, num);
            
            #ifdef CONTINUOUS_NUM_KEY_SELECT 
            ir_num_timer = IR_NUM_TIMER; 
            
            {
              if(ir_num_state == NUM_STATE0)
              {
                ir_num1 = x;
                x = ir_num1;
                ir_num_state = NUM_STATE1;
                psprintf(RegionValStr[REGION1]," %d",ir_num1);
              }
              else if(ir_num_state == NUM_STATE1)
              {
                ir_num2 = x;
                x = ir_num1*10+ir_num2;
                ir_num_state = NUM_STATE2;
                psprintf(RegionValStr[REGION1]," %d%d",ir_num1,ir_num2);
              }
              else if(ir_num_state == NUM_STATE2)
              {
                ir_num3 = x;
                x = ir_num1*100+ir_num2*10+ir_num3;
                ir_num_state = NUM_STATE3;
                psprintf(RegionValStr[REGION1]," %d%d%d",ir_num1,ir_num2,ir_num3);
              }
              else if(ir_num_state == NUM_STATE3)
              {
                ir_num4 = x;
                x = ir_num1*1000+ir_num2*100+ir_num3*10+ir_num4;
#ifdef ALCO_DVD_UI
			    if(!x)
			    {
			        ir_continuous_num_clr();
			        invalid_key();
			        return;
			    }
			    else
#endif
			    {
                ir_num_state = NUM_STATE4;
                psprintf(RegionValStr[REGION1]," %d%d%d%d",ir_num1,ir_num2,ir_num3,ir_num4);
              }
			  }
              else
              {
                ir_continuous_num_clr();
                invalid_key();
                return;
              }  
            }
            
            PrintOsdMsg(STR_OS_SELECT,REGION1,1,1);
            
            //psprintf(RegionValStr[REGION2]," %d%d%d----%d",ir_num1,ir_num2,ir_num3 ,x);
            //PrintOsdMsg(STR_OS_OPEN,REGION2,1,1);
            if(x)
            #endif //end #ifdef CONTINUOUS_NUM_KEY_SELECT
            
            #ifdef PMP_DVD
            { //kenny 2005/8/3
            if(pFsJpeg->gifsState == FS_STATE_OTHER||pFsJpeg->gifsState == FS_STATE_JPEG)
            {
                if(x <= mp3_file_count())
                 {
                 dvd_title=x;  
                 pmp_enable_user_flag(PMP_USER_ENTER_SEARCH_TRACK); 
                 ircmd_post_func(CMD_FUNC | CMD_FUNC_TIMEOUT);
                } 
                else
                {
                ir_select_number=0;
                invalid_key();
                }
            }    
            else
            HDDCard_number_input(x);
            }
            #else
            ir_num_select(x);
            #endif
            
            #ifdef CONTINUOUS_NUM_KEY_SELECT 
            if(ir_num_timer)
              return;
            #endif
            
            resumeMSF=0;//wanghaoying 2003-11-5 10:40
        }
        return;
    }
#endif
    ir_select_number = 0;
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}


void init_ir_num(void)
{
    ir_10p=0;
    ir_select_number=0;
    now_num_ns=0;
}



void ir_num_select(int x)
{
#ifdef SUPPORT_MP3_ENCODER  //qinhua ,add,because at this time must switch DSP code when close file,2005-11-29 21:52
if(cd_type_loaded == CDDA)  
 {
 if((pre_ripping_flag)||((mp3_encoder_state == test_write_data)&&(recNew<1)))
  { 
   invalid_key();
    return;
   }
 #ifndef CD_DIRECT_RIPPING
   ripping_flag=0;   
 #endif 
 stop_current_ripping(); 
 }        
 
#endif 


#ifdef STOP_NO_DIR_SELECT//libing 2005-4-28 9:18
    if(play_state==VCD_STATE_STOP)
    {
        invalid_key();
        return;
    }
#endif  
#ifndef MAKE_ONLY_UPDATE_CODE//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
    #ifdef MOVE_HIGH_LIGHT_IN_PROG_MODE
     if((!full_scrn)&&(cd_type_loaded== CDROM)){     //wsf  2004-7-20 14:55  changed for cancel program when select other ,just in CDROM DISC
        if(!Is_OTHER_STATE()){              
            prog_cnt=0;
            prog_func_off();
            prog_func_clear();        
        }
    }
    #endif
    int dir_num;
#ifdef IRCMD_DBG
    printf("================= ir_num_select (%x) =================\n",x);
#endif

#ifdef SUPPORT_TUNER       // add tuner 2-6-14 23:17
    if(play_state==VCD_STATE_POWER)
    {
        ir_select_number= x;
        psprintf(RegionValStr[REGION1]," %02d",ir_select_number);
        PrintOsdMsg(STR_OS_SELECT,REGION1,1,1);
    }
    else
#endif
    {
        if (cd_type_loaded==CDROM)
        {
            ir_select_number = x;
            //wangap add if the dir_num is mp3 or jpeg or game 2003/12/22 
            // yltseng 2004/04/12, use relative method to access pFsJpeg->count_dir
            if( pFsJpeg->gifsFuncBtn != FS_FUNC_IDLE )
                dir_num = pFsJpeg->count_dir[ pFsJpeg->gifsFuncBtn - FS_FUNC_MP3 ];
            else
                dir_num = 0;

            //wanghaoying changed 2003-12-4 17:14
            //Focus in dir-area, the number must be less than the total dir count
            //Focus in file-area, the number must be less than the total file count of the dir
            if((pFsJpeg->ControlArea==CNT_AREA_FILE)&&(ir_select_number > mp3_file_count()))
                ir_select_number = 0;
            if((pFsJpeg->ControlArea==CNT_AREA_DIR)&&(ir_select_number > dir_num))
                ir_select_number = 0; 

            if (play_state==VCD_STATE_STOP)
            {
                if (ir_select_number > mp3_file_count())    //Maoyong 2004.03.10
                    ir_select_number = 0;
                else
                {
                    resumeMSF = 0;
                    pFsJpeg->file_current = ir_select_number;
                }
            }

// 2004/04/13 yltseng mark, it's no need now
/*
#ifdef SUPPORT_FILE_SYSTEM_MODE  // Robert 021007
            if (IsOtherStatePlayMode())
                ir_select_number = 0;
#endif
*/
        }else
        {
           #ifdef MIX_CDMP3_DISC_DISPLAY_REAL_CD_TRK    //linrc add 2004-10-29 11:20
           /*when play the cd+mp3 disc(ABEX TEST CD 786),it display the real CD TRK*/
            if((cd_type_loaded == CDDA)&&((pFsJpeg->cdrom.track_info[1]&0x40000000) == 0x40000000))
            {
                ir_select_number = x-1;
                x += (cd_trk_lo_now-2); 
            }
            else
            #endif
            {
            ir_select_number = x;
            x += (cd_trk_lo_now-1);
            }
            if(cd_type_loaded!=CDDVD)
            {
                if(!IsPBCOn()||(play_state==VCD_STATE_STOP))
                {
                    if(((x<cd_trk_lo_now)||(x>cd_trk_hi))&&(play_state!=VCD_STATE_9FRAMES))
                    {
                        ir_select_number=0;
                    }
                }
            }
            
            #ifdef CONTINUOUS_NUM_KEY_SELECT
            if((!(full_scrn&PROGRAM))&&(!(full_scrn&SETUP))&&(!(full_scrn&GOTO)))
            {
                if(((cd_type_loaded==CDVCD20)||(cd_type_loaded==CDSVCD)) && IsPBCOn())
                {
                  if(((psdList.s.bsn==1)&&x<psdList.s.bsn) || (x>(psdList.s.bsn+psdList.s.nos)))
                  {
                    ir_continuous_num_clr();
                    //ir_select_number = 0;//jack mark it.when merge alco code.
                  }
                }
                else if(cd_type_loaded==CDDVD)
                {
                  //if(is_menu()&&(HL_exist==1))
                  {
                    if((x>get_tt_info(DISP_CH_Ns)) && (x>get_tt_info(DISP_TT_Ns)))
                    {
                      ir_continuous_num_clr();
                      //ir_select_number = 0;  
                    }
                  }
                }
            }
            #endif
             
        }
/***************************/
//Add the code for judge the input and the file count in the dir(when repeat dir and repeat 1!!).
#ifdef  NUMBER_SELECTION_WHEN_REPEAT    //wuxiaofeng add for Minton 2004-03-10
        if(cd_type_loaded == CDROM)
        {
            if( ( (rep_mode==REPEAT_TRACK)//prevent inputing other track
                    &&(ir_select_number!=disp_trk_now) )//except the current track
                ||((rep_mode==REPEAT_DIRECTORY)//prevent inputing other directory
                    &&((ir_select_number > pFsJpeg->first_mp3_seq+pFsJpeg->file_specify_in_dir)//except the current directory
                    ||(ir_select_number < pFsJpeg->first_mp3_seq+1)) )
                )
                ir_select_number=0;
        }
#endif//#ifdef  NUMBER_SELECTION_WHEN_REPEAT
/***************************/
#ifdef SUPPORT_IR10P_LIMIT//tianye 200607
		if (flag_input)
		{
		   //printf( "SUPPORT_IR10P_LIMIT   return  /n"     );
		    return ;
		}
#endif//#ifdef  SUPPORT_IR10P_LIMIT		

        if(ir_select_number)
        {
#ifdef TCL_DIRECT_SELECT_CHAPTER// 2004-3-22 14:20 lijd
            if(cd_type_loaded==CDDVD)
            {
                dvd_title = get_tt_info(DISP_TT);
                dvd_chapter=get_tt_info(DISP_CH_Ns);
                
	            if(ir_select_number<=dvd_chapter)
	            {
	                dvd_chapter = ir_select_number; 
	                if(dvd_title == 0)
	                {
						dvd_title =  1;
						ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY );
	                }
	                else
	                {
	                    ircmd_post_func(CMD_FUNC|CMD_FUNC_PLAY );
	                }
	            }
	            else
				{
	                invalid_key();
	                return;
				}

            }

            else

#elif defined(DVD_DIRECT_SELECT_CHAPTER)&&defined(ONLY_ONE_CHAPTER_SELECT_TITLE) //yaowh add.2005-10-9 11:12
            static int title_cnt;	
            if(is_menu()!=1 && cd_type_loaded==CDDVD )  
            {
			
				title_cnt=get_tt_info(DISP_TT_Ns);
				dvd_chapter=get_tt_info(DISP_CH_Ns);
				
				if((ir_select_number<=title_cnt)||(ir_select_number<=dvd_chapter))
				{
					ircmd_post_func(CMD_SELECT | (ir_select_number));
				}else		 	
				{
					invalid_key();
					return;
				}

			}
            else

#endif
            /*Maoyong 2004.02.28
              When select MP3
             */
            #ifdef  MP3_DIRECT_SELECT_FAST2NORM     
            if( (cd_type_loaded == CDROM) && (!Is_JPEG_STATE()) )
                chg2normal_play(FAST2NORM, NOT_REALPLAY);
            #endif
            
            #ifdef CONTINUOUS_NUM_KEY_SELECT
            if(ir_num_timer)
                ir_select_number = 0;
            else
                ircmd_post_func(CMD_SELECT | (ir_select_number));
            #else
            ircmd_post_func(CMD_SELECT | (ir_select_number));
            #endif
            if(ir_select_number)
            {

#ifdef ZOOM_DIRECT_STOP_SLIDE//nono 4-8-21 11:07
                if(jpg_slide_time == 0xffffffff)
                {
                    if(Is_JPEG_SlideMode())
                    {
                        jpg_slide_time = JPEG_SLIDE_TIME;
                    }
                 
                }
#endif

                if(!bIntro)
                {
                    #if (defined(JIEKE_DVD)||defined(AD_TCL))//2004-3-22 13:09 lijd
                                if(Is_JPEG_STATE())//wangfeng 2003-12-22 9:18                 
                        disp_trk_now = ir_select_number; 
                            #endif
                    #ifdef MIX_CDMP3_DISC_DISPLAY_REAL_CD_TRK  //linrc add 2004-10-29 11:20
                    /*when play the cd+mp3 disc(ABEX TEST CD 786),it display the real CD TRK*/
                    if((cd_type_loaded == CDDA)&&((pFsJpeg->cdrom.track_info[1]&0x40000000) == 0x40000000))
                    psprintf(RegionValStr[REGION1]," %02d",ir_select_number+1);
                    else
                    #endif

                    /* wanghaoying delete this block 2005-6-23 11:59, for a better method used in search1.c
                    #if 0//def DVD_DIRECT_SELECT_CHAPTER    //when it open,the osd may display wrong    zhjg  05/07/13
                    if ((cd_type_loaded == CDDVD ) && ( pDSV->dTT_SRP[NP_TTN].vtt.PTT_Ns < ir_select_number))
                    {//liulifeng 2005/02/25
                     //correct the error : when the select number overrange the total capter in current title
                        invalid_key();
                    }
                    else
                    #endif*/
                {
                    psprintf(RegionValStr[REGION1]," %02d",ir_select_number);//zhujg
                    PrintOsdMsg(STR_OS_SELECT,REGION1,1,1);
                }
                }
                if(rep_mode)
                {//terry,2002/5/2 03:26PM
                    //cancel repeat status ,avoiding dvd/vcd difference in repeat mode.

 
#ifdef MINTON_DVD       //wanghaoying 2003-8-4 16:24 added the limitation
                    //if((cd_type_loaded==CDDVD) //Marked by Wuxiaofeng for support DVD repeat
                    if(Is_JPEG_PLAY_STATE()&&pFsJpeg->gbfsSlide==0)//if not JPEG slide then cancel repeat
#endif
#ifndef NUMBER_SELECT_REPEAT_MODE_OFF   //clead 
                    #ifdef NUMBER_SELECT_NOT_CANCEL_DISC_REPEAT //chenzhao 2006-4-19 18:3 .
                    if((rep_mode!=REPEAT_DVDDISC)&&(rep_mode!=REPEAT_DISC)&&(rep_mode!=REPEAT_DIRECTORY)
                        #ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT
                        &&(rep_mode!=REPEAT_ALL_DISCS)
                        #endif
                        )
                    #endif
                    {
                        rep_mode=0;//only cancel in (JPEG & !slide) mode
                    	ShowRepInfo();
                    }
#endif //clead                  
#ifdef  NUMBER_SELECTION_WHEN_REPEAT    //wuxiaofeng add for Minton 2004-03-12
                    psprintf(RegionValStr[REGION2]," %02d",ir_select_number);
                    PrintOsdMsg(STR_OS_SELECT,REGION2,1,1);//display select info in region 2
#endif//#ifdef  NUMBER_SELECTION_WHEN_REPEAT
                }
            }
        }else
            invalid_key();

        init_ir_num();
    }
#endif//MAKE_ONLY_UPDATE_CODE:20050305 linrc only for make romA.bin(BootLoad).
}

#if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)
//Maoyong 2004.05.26, just for record test on DVD platform
void TestRecordCmd(BYTE cmd)
{
    switch(cmd)
    {
        case 0: //stop
            printf("\nRecord test: Press KEY 1 as STOP button\n");
            break;
        case 1: //record
            printf("\nRecord test: Press KEY 2 as RECORD button\n");
            break;
        case 2: //play
            printf("\nRecord test: Press KEY 3 as PLAY button\n");
            break;
        case 3: //pause
            printf("\nRecord test: Press KEY 4 as PAUSE button\n");
            break;
        case 4: //set record quality High
            printf("\nRecord test: Press KEY 5 to set High quality \n");
            break;
        case 5: //set record quality High
            printf("\nRecord test: Press KEY 6 to set Middle quality\n");
            break;
        case 6: //set record quality High
            printf("\nRecord test: Press KEY 7 to set Low quality\n");
            break;
        default:
            break;
    }
    DSP_AudioIOControl(RECORDMIC,cmd,0);//2004AUDDRV AudioIOControl(RECORDMIC,cmd,0);
}
#endif //#if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)


#ifdef QSI_SHOW_ERR_RATE
#include "ircmd_QSI.c"
#endif

void    ircmd_0(void)
{
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(0);
else    
#endif
    ircmd_input_number(0);

}
#ifdef MIDI_CHECK_PASSWORD_PASS_MCU    //Midi encrypt  test //lijd 2005-2-25 14:24
#include "check_midi_password.c"
#endif

void    ircmd_1(void)
{
    
  #ifdef MIDI_CHECK_PASSWORD_PASS_MCU    //Midi encrypt  test //lijd 2005-2-25 14:24
  int  Res=0;
  char *password="123";
  Res=CheckMIDIPassWordPassMCU(password);   
  if( Res==0)   printf("\n====sucessful!========\n");
  return ;
  #endif
  
  
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(1);
else    
#endif
    #if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)
    TestRecordCmd(0);   //stop
    #else
        ircmd_input_number(1);
        #endif
}

void    ircmd_2(void)
{
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(2);
else    
#endif
    #if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)
    TestRecordCmd(1);   //record
        #else
    ircmd_input_number(2);
        #endif
}

void    ircmd_3(void)
{
#ifdef OPEN_STATE_USE_3333_CHANGE_TV_SYSTEM//shenyj add for alco 11/22
    static int flag_3333;
if(play_state==VCD_STATE_OPEN) 
{
    old_key = IRC_3;
    if(old_key == IRC_3)
    {
        flag_3333++;
    }
    if(flag_3333==4)
    {
        setup_tv_format(MODE_AUTO);
        setup_SetTV_format(STR_OS_AUTO);
        update_tv_format_sel();
        tv_format = MODE_AUTO;
        PrintOsdMsg(STR_OS_TV_SYS|(STR_OS_AUTO<<OSDSTR_ID_TOTL_BIT),REGION1,1,4);
        flag_3333=0;
        return;
    }
}   
#endif//OPEN_STATE_USE_3333_CHANGE_TV_SYSTEM
    
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(3);
else    
#endif
    #if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)
    TestRecordCmd(2);   //play
    #else
        ircmd_input_number(3);
        #endif
}

void    ircmd_4(void)
{
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(4);
else    
#endif
    #if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)
    TestRecordCmd(3);   //pause
    #else
        ircmd_input_number(4);
        #endif
}

void    ircmd_5(void)
{
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(5);
else    
#endif
    #if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)
    TestRecordCmd(4);   //quality H
    #else
        ircmd_input_number(5);
        #endif
}

void    ircmd_6(void)
{
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(6);
else    
#endif
    #if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)
    TestRecordCmd(5);   //quality M
        #else
    ircmd_input_number(6);
        #endif
}

void    ircmd_7(void)
{
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(7);
else    
#endif
    #if defined(SUPPORT_REP_READ) && defined(REP_READ_TEST_RECORD)
    TestRecordCmd(6);   //quality L
        #else
    ircmd_input_number(7);
        #endif
}

void    ircmd_8(void)
{
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(8);
else    
#endif
    ircmd_input_number(8);
}

void    ircmd_9(void)
{
#ifdef QSI_SHOW_ERR_RATE
if(QSI_PIPO_TEST==0x1)    
    QSI_setMSF(9);
else    
#endif
    ircmd_input_number(9);
}

void    ircmd_p10(void)
{
#ifdef SUPPORT_MIDI_MENU_SEL 
    if(gIsMidiSelMenu) 
    {
        return;
    }           
#endif   

#if defined(QSI_SHOW_ERR_RATE) && defined(SUPPORT_SPI_QSI)
    if(QSI_PIPO_TEST==0x1)    
    {
        if(QSI_PIPO_FLAG!=0)
        {
            MSF_trigger=2;
            QSI_PIPO_FLAG = 0;
            psprintf(linebuf, "QSI_PIPO> STOP testing!\n<Pressed any num key to continue> Or \n<Second press to finish phase of run-in.>\n");
            UART0_puts(linebuf);
        }
        else if(MSF_trigger==2)
        {
            spi_cmd_run_in_final();
        }
        else
        {
            psprintf(linebuf, "<Pressed NUM 0-9 to start PIPO testing>\n");
            UART0_puts(linebuf);
        }
    }
    else    
#endif
    ircmd_input_number(10);
}

void    ircmd_10(void)
{
    ircmd_input_number(0);
}





//============================ending===========================================

