/********************************************
*  setup_newstyle_ui.h
*
*  include  in setup_tab.c   
*  when normal setup menu.
* 
*  UI function:
*     LEFT,RIGHT, UP, DOWN,  SELECT, ShowSetupPage. 
* 
* Creator: zhaoyanhua 
* Date:  3-7-25 17:12
*******************************************/

//--------------------------------------
//Modefied by wangfeng,
//
//For new setup menu 	"#ifdef	SETUP_COLOR_TYPE1",
//
//2003-08-29 15:18
//--------------------------------------


//--------------------------------------
//Modefied by zhangyu,
//
//For new setup menu 	"#ifdef	SETUP_COLOR_TYPE2",
//
//3-9-1 4:42张宇P
//--------------------------------------


void ShowCUSTMMsg(void);
void setup_SetDTSDOWNMIXConfig();

#ifdef SETUP_PASSWORD_GUI
BYTE passwdGUI_state = NO_GUI_STATE;//record the current state in password GUI
#endif//SETUP_PASSWORD_GUI


#include "one_key_pass.h"


#ifdef SCART_TV_5	//wangfeng 2003-12-3 16:49
extern void SetScartTV5();
extern void ReSetScartTV5();
#endif
#ifdef TONIC_DVD
int ShowPasswordErr;
#endif//TONIC

#ifdef PROLOGICII_3D_MUTEX
extern BYTE soundGetSurroundType(void);
extern BYTE soundGetEQType(void);
extern BYTE soundGetEQType(void);
#endif//PROLOGICII_3D_MUTEX

#ifdef SHOW_STANDBY_TIMER  //suqiaoli  add 8-13
extern void exe_standby_timer(void);
extern void polling_setup_standby_timer(void);
extern void reset_standby_timer_pos(void);
#endif

void setup_func_down(void)
{
    const char *str;
    int     i;
    //UINT16 line=SETUP_MAX_WIDTH*16-20;//wanghaoying 2003-8-12 19:45 marked for not used

#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 11:15
 		//in PASSWORD GUI, LEFT/RIGHT/UP/DOWN has no use.
		if(passwdGUI_state != NO_GUI_STATE)
			return;
#endif       	

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         

	if(main_setup)
	{
		draw_setup_Btn_HL( 1, ONE_KEY_PASS_X*11, ONE_KEY_PASS_Y*4, 8* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);	
		draw_setup_Btn_HL( 1,SETUP_X*14+28, SETUP_Y*4, 8* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);
		index_x = EXIT_SETUP_MENU_X;
		draw_setup_Btn_HL( 1,EXIT_SETUP_MENU_X*14+32, EXIT_SETUP_MENU_Y*4, 9* 24, 1*32,4,SETUP_HL_COLOR);		
		return;
	}
#endif
    
    reset_passwd_cnt();

    #ifdef SHOW_STANDBY_TIMER  //suqiaoli add 8-8
		reset_standby_timer_pos();
	#endif

	#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
	SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);//a8a8a8ff);//gray white
       #elif defined(SETUP_COLOR_TYPE2)  //zhangyu  3-9-1 4:38张宇P
          //SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
          SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
	#else
	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
	#endif


    if (setupLevel==0) { //main menu page
    	setupLevel=1;
    	id=setup_item[page][index_y][1];
		setup_DrawItem(1, SETUP_MENU_YSTART+1, 1);
		// highlight : draw a frame to identify which tab is enable
		/*osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SBGCOLOR,1);
		osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SBGCOLOR,1);
		osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SBGCOLOR,1);
		osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SBGCOLOR,1);*/
		
                #if  !defined(SETUP_COLOR_TYPE1) &&    !defined(SETUP_COLOR_TYPE2)// zhangyu 2003-08-29 17:28		
		setup_Showredframe(page);
		#endif

		draw_3rd_menu();
		return;
    } else
		if (setupLevel==1) {
			//second level menu page

		#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE          //calculate setupItemNum[1] true value.zhaoyanhua add 03-11-7 14:03
		int iItemType;
		
		for (i=0; i<MAX_PAGE_ITEM; i++)
		{		
    		iItemType=setup_item[page][i][0];
    		if (iItemType == SET_SPACE) continue;
    		if (iItemType == SET_NE) break;		
		}
		setupItemNum[1] = i;
		#endif
			if ( (index_y+index_y_start) < (setupItemNum[1]-1)) {
				if (full_scrn&CUSTM) {
					//CUSTM menu page
					//clear third-level menu
#ifdef  RATING_8
                    if (index_y == 3) 
                    {
                      #if defined(SETUP_COLOR_TYPE2)||defined(SETUP_COLOR_TYPE1)    //zhangyu 3-9-1 4:38张宇P
                                osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                                              SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
                                              (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                                              (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
                                               SBGCOLOR);
                      #else
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						//SETUP_MENU_YSTART,
						SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT-68,
						SBGCOLOR);
						#endif

						ShowCUSTMMsg();
					}
					else
#endif//end RAGING_8
                #ifdef SUPER_DEFAULT_OSD_LANG
                if ((index_y == CUSTMOSDITEM)&&((8-N_OSD_LANGS)<=1))
                {
                    #if defined(SETUP_COLOR_TYPE2)||defined(SETUP_COLOR_TYPE1)    //zhangyu 3-9-1 4:38张宇P
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,SBGCOLOR);
                    #else
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT-68,SBGCOLOR);
					#endif

					ShowCUSTMMsg();
                }
                else
                #endif
					{

						osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
						SBGCOLOR);

					}
					
					id = setup_item[page][index_y][1];

					setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

					index_y++;

					id = setup_item[page][index_y][1];

					setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);

				//the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
                #ifdef RCD_GPIO_CONTROL            // alan 2002/7/26 02:08と
				if (index_y < (4)) {
				#elif defined(SUPER_DEFAULT_OSD_LANG)       //freyman add 2004-2-7 17:50
				if (index_y < (7-1)) {
                #else
				if (index_y < (6-1)) {
                #endif
				    //draw ">>" between sub-mean and it's corresponding selection area
					//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
					#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:03
					if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
					#endif 							
                    {
                        #ifdef SETUP_COLOR_TYPE2   //zhangyu 3-9-1 4:39张宇P
                        osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SANTIBGCOLOR );
                        #else
					    osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
                        #endif
					}
					submenuStart = index_y+SETUP_MENU_YSTART;

					if (setup_item[page][index_y][0]==SET_NM) {
					    char buf[8];
					    
                        #ifdef RATING_8								
						#if !defined(SETUP_COLOR_TYPE1)&&!defined(SETUP_COLOR_TYPE2)	//wangfeng 2003-08-29 17:28		
						osd_draw_rect((SETUP_SUB_XSTART-1)*16,
									   (SETUP_MENU_YSTART+4)*SETUP_BUTTON_HEIGHT,
									   (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
									   5*SETUP_BUTTON_HEIGHT,
									   SBGCOLOR);
                        #endif								
                        #endif								
							
							#ifdef SETUP_6_DIGIT_PASSWORD //zhaoyanhua add 03-10-14 14:53
                        	psprintf(buf, "%06d", UserSet.parent_passwd);
                    		#else //4 digit password 
								psprintf(buf, "%04d", UserSet.parent_passwd);
                    		#endif   //end SETUP_6_DIGIT_PASSWORD

								osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
								osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, SDEFAULTCOLOR, SBGCOLOR);//张宇标记颜色
								
							} else {
								//get select item
							#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
								if(one_key_pass_flag)
								{
									sel = GetOneKeyPageSel(index_y);
									printf("+++++++++++++ 12222sel = %d,index_y = %d--\n",sel,index_y);
								}
								else
							sel = setup_sel[page][index_y];
								#else
								sel = setup_sel[page][index_y];
							#endif
#ifdef RATING_8
							if((page == CUSTMPAGEINDEX) && (index_y == 3))
								{
							    submenuStart = SETUP_MENU_YSTART;
							}
						#ifdef SUPER_DEFAULT_OSD_LANG		//freyman add 2004-2-7 19:15				
						else if(index_y==CUSTMOSDITEM)
						    submenuStart = SETUP_MENU_YSTART  + (8-N_OSD_LANGS);
						#endif
								else
								{
									submenuStart = index_y+SETUP_MENU_YSTART;
								}
#else
						#ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-7 19:16
						if(index_y==CUSTMOSDITEM)
						    submenuStart = SETUP_MENU_YSTART + (8-N_OSD_LANGS);
						else
                                                #endif
								submenuStart = index_y+SETUP_MENU_YSTART;
#endif

								//draw third-level menu
								for (i=2; i<MAX_ITEM_SEL; i++)
								{
									id = setup_item[page][index_y][i];
									if (id==0) break;
									ShowSel(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,sel == i);
								}
								setupItemNum[2] = i - 2;
							}
						}
					#if (!defined (SETUP_COLOR_TYPE1))&&(!defined (SETUP_COLOR_TYPE2))//zhaoyanhua add for BBK 03-11-5 18:49
						//wanghaoying add 2003-10-24 16:16
						//redraw the bottom horizontal line that is deleted by user operation
					   if (p_scan==1)
            			{
            				//draw top horizontal line
            				osd_DrawLine(12, SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
            				//draw bottom horizontal line
            				osd_DrawLine(10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 2);
            			}
						else
						{
            				osd_DrawLine(12, SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);
            				osd_DrawLine(10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
            			}
					#endif
					} else {
						//normal setup second-level page

						if (index_y > (SETUP_MAX_LINE-5)) {
							index_y = SETUP_MAX_LINE-5;
							index_y_start++;
							ShowSetupPage(1);
						}

						//clear third-level menu
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 19:42
				if(page == VIDEOPAGE)	
					osd_draw_rect((SETUP_SUB_XSTART-1)*16,(index_y +SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT+30,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,SETUP_BUTTON_HEIGHT,SBGCOLOR);
				else	
#endif	//VIDEO_SETUP_NEW_GUI					
						osd_draw_rect((SETUP_SUB_XSTART-1)*16,
					#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
							SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+30,
							(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
							(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-65,
							SBGCOLOR);
                                        #elif defined(SETUP_COLOR_TYPE2)  //zhangyu   3-9-1 4:39张宇P
								SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
								(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
								(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-68,
								SBGCOLOR);						

					#else
							SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
							(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
							(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT,
							SBGCOLOR);
#endif   //张宇标记

                    #if !defined(  SETUP_COLOR_TYPE1)&& !defined( SETUP_COLOR_TYPE2)
						if (p_scan==1)
							osd_DrawLine(250, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 2);
						else
							osd_DrawLine(250, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
					#endif	
						id = setup_item[page][index_y+index_y_start][1];
						setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

    #if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE) ||defined(SET_FCR_SPEAKER)     //xulf 2004-01-07              
						//special case//nonotest 2003-9-5 17:44
						if ( (page==MULTISPKPAGE) &&
							(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)
							)
						{
							index_y++;

							if ( (index_y+index_y_start) == SPKSTART && (index_y+index_y_start) != SPKEND)
							 {
                                if (index_y_start==0) {
									index_y += (SPKEND-SPKSTART+1);
                                } else {
									index_y = SPKEND+1;
									index_y_start--;
									ShowSetupPage(1);
									return;
                                }
							}

					}
					
					#if defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)
					else 
					#endif//ONLY_DOWNMIXOFF_CAN_SET_CE_RE
					
					
#endif//ONLY_DOWNMIXOFF_CAN_SET_CE_RE
                    
#ifdef PROLOGICII_3D_MUTEX//4-2-12 1:23
			if((page==AUDPAGE)&&is_EQ_SOUND_set()&&(index_y==(PROLOGIC_II-1) )  )
          		index_y+=2;	//Maoyong 2004.03.09 skip PROGLIC-II
			else 
#endif//PROLOGICII_3D_MUTEX


                    #ifdef  SETUP_ALL_VALID
                    #ifdef KARAOKE_MENU     

                    if((page==AUDPAGE)&&(index_y>4)&&(KARAOKE_MENU_FLAG))
                    {
            	        index_y=1;
                    }
                    #ifdef PROLOGIC_ON_51CH
                    else if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG==0)
                    &&(setup_IsSpkDownmixOff()&&(index_y==1)|| !setup_IsSpkDownmixOff()&&(index_y==0))
                    )
                    #else
                    else if((page==AUDPAGE)&&(index_y==1)&&(KARAOKE_MENU_FLAG==0))
                    #endif
                        index_y=6;//wangfeng 2003-11-11 13:55
                    #endif
                    #else//SETUP_ALL_VALID
			        //#ifndef SETUP_ALL_VALID
		        if (page==AUDPAGE) 
		        {
                            if ( (SETUP_SPDIF==SPDIFBITSTREAM) &&
									(index_y==DIGIOUTITEM) &&
									( ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
									//AUDIF_CODING_MODE_PCM|   //DTSCD-BITSTREAM MODE, Jeff 20020719
									AUDIF_CODING_MODE_DTS)
									)||(cd_subtype==CD_DTS) )//nono 2-7-25 17:29
									)
                            {
                                index_y += (VOLCTRLEND-VOLCTRLSTART+2);
                        } 
                        else
                            {
                                index_y++;

                                if ( (
										(
										(SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) &&
										( coding_mode_now&(AUDIF_CODING_MODE_AC3|
										AUDIF_CODING_MODE_DTS|
										AUDIF_CODING_MODE_DTSCD)
										)
										)
										||(coding_mode_now==AUDIF_CODING_MODE_LPCM)//terry,0512,currently ,we are not surport LPCM key shift
										)
										&&(index_y==KEYITEM)
										)
                                {
                                    index_y++;
                                }
                            }
                        #ifndef NO_AC3_DYNAMIC_RANGE
						} else if ( (page==AC3DIGITALPAGE) && //Jeff 20020621
								(index_y==(AC3DYNAMICITEM1-1)) &&
								( (SETUP_AC3DIGITAL_OUTMODE!=AC3DYNAMICITEM2)
//								 ||(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)
								)
								)
						{
							index_y++;
//						    index_y=AC3DYNAMICITEM1+1;
                        #endif //NO_AC3_DYNAMIC_RANGE
						} else
                    #endif //SETUP_ALL_VALID
							{
    			    #if !defined(SETUP_ALL_VALID)||defined(SET_FCR_SPEAKER)     //xulf 2004-01-07   
    			    if((page!=MULTISPKPAGE)||((page==MULTISPKPAGE)&&(SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF)))
    			    #endif
								index_y++;
							}
					#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE          //zhaoyanhua 03-11-7 11:19
					while(setup_item[page][index_y+index_y_start][0]==SET_SPACE)
					{
						index_y++;
					}
					#else	
							if (setup_item[page][index_y+index_y_start][0]==SET_SPACE)    index_y++;
					#endif
                
                #ifdef ONLY_DOWNMIX_IN_SPEAKER_PAGE//liweihua add 2004-1-2 15:05
                            if((page==MULTISPKPAGE) && (index_y!=0))
                            {            		
                                for (i=0; i<MAX_PAGE_ITEM; i++)
	                    		{
			                        int iItemType;		
                            		iItemType=setup_item[page][i][0];
                            		if (iItemType == SET_SPACE) continue;
                            		if (iItemType == SET_NE) break;		
                        		}
                        		setupItemNum[1] = i;
                                index_y = setupItemNum[1]-1;//jump to downmix item
                            }
                #endif   
				
							id = setup_item[page][index_y+index_y_start][1];

							setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);

							//the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
							if ((index_y+index_y_start) < (setupItemNum[1]-1)) {
								//draw ">>" between sub-mean and it's corresponding selection area
					//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
					#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:04
								if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
								#endif 							
					    osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
								
								submenuStart = index_y+SETUP_MENU_YSTART;

								//special item(PASSWORD), page-0, item-4
								if (setup_item[page][index_y+index_y_start][0]==SET_NM) {
									if (UserSet.parental_ststus==C_LOCK) {
										setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL;
										str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
									} else {
										setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL + 1;
										str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
									}
                                                        #ifdef  SETUP_COLOR_TYPE2   //zhangyu 3-9-1 4:40张宇P
								osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, SANTIBGCOLOR );		
								osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, 4, SBGCOLOR);
							#else							
									osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
									
									osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, SDEFAULTCOLOR,SBGCOLOR);//wangfeng 3-8-27 22:57	
                                                        #endif																
								} else
									if (setup_item[page][index_y+index_y_start][0]==SET_SCALE) {
							#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 18:36
									if(page != VIDEOPAGE)
							#endif//VIDEO_SETUP_NEW_GUI
										setup_PrepareScaleItem(id, 0);
								
									} 
									else 
									{
										//special item(LANGUAGE)
                                    #ifdef RATING_8
										if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) 
										{
											// if (page==LANGPAGE||(SETUP_GRADE==STR_OS_RATING )) {
                                    #else
											if (page==LANGPAGE) {
                                    #endif
												submenuStart = SETUP_MENU_YSTART; //from 0
											}

											//draw third-level menu
											for (i=2; i<MAX_ITEM_SEL; i++) {
												//get select item
											#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
												if(one_key_pass_flag)
												{
													sel = GetOneKeyPageSel(index_y);
													printf("+++++++++++++ 333331sel = %d,index_y = %d--\n");
												}
												else
												sel = setup_sel[page][index_y];
											#else	
												sel = setup_sel[page][index_y];
											#endif
							
												id = setup_item[page][index_y][i];
												if (id==0) break;

												ShowSel(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,sel == i);
											}
											setupItemNum[2] = i - 2;
										}
									}
							}
        }
        else
		{
			if (full_scrn&CUSTM) return;

			if (setup_item[page][index_y][1]==STR_OS_RETURN_MAIN_SETUP)
			{
				// highlight : draw a frame to identify which tab is enable
				#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
				SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
                                    #elif defined(SETUP_COLOR_TYPE2)				
                                     SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
				#else
				SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
				#endif
				/*osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SANTIBGCOLOR,1);
				osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SANTIBGCOLOR,1);
				osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SANTIBGCOLOR,1);
				osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SANTIBGCOLOR,1);*/
				
			        #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)  //zhangyu  2003-08-29 17:28
				setup_Showredframe(page);
				#endif


				id = setup_item[page][index_y+index_y_start][1];
				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);
				setupLevel=0;
/*			
			#ifdef ONE_KEY_PASS
				if(one_key_pass_flag )
					one_key_pass_flag = 0;
			#endif
*/ //fengjl marked it
				index_y_start=0;
				index_y=0;
				return;
			}
		}
    } else
		if (setupLevel==2) {
			if (setup_item[page][index_y][0]==SET_SCALE) {
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 16:54
				if(page == VIDEOPAGE)
					return;
#endif//VIDEO_SETUP_NEW_GUI				
				setup_CookScaleItem(id, 0);
				run_save_sel_cmd(page,index_y);
			} else
				if ( (index_y2 < (setupItemNum[2]-1)) && (setup_item[page][index_y][0]!=SET_NM) ) {
					//third-level menu page
			#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
					if(one_key_pass_flag)
					{
						sel = GetOneKeyPageSel(index_y);
						printf("+++++++++++++ 44444sel = %d,index_y = %d--\n");
					}
					else
					sel = setup_sel[page][index_y];
				#else	
					sel = setup_sel[page][index_y];
				#endif

					id = setup_item[page][index_y][index_y2+2];

					ShowSel(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,(index_y2+2) == sel);
					index_y2++;
//#ifndef  SE
#ifndef SETUP_COLOR_TYPE2
					ShowSel(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,(index_y2+2) == sel);
#endif
					if ((index_y2+2) == sel) {
						osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
					} else {
						osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 0);
					}
					id = setup_item[page][index_y][index_y2+2];
					str = setup_SetItemString();
					
					osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SANTIFONTCOLOR, SANTIBGCOLOR);
					
				}
		}
    #ifdef SETUP_COLOR_TYPE2 //3-10-28 1:43张宇P
    if (!(full_scrn&CUSTM))
osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/18, 13);//SBGCOLOR);
    #endif

}


void setup_func_up(void)
{
    BYTE    upperbound;
    const char *str;
    int     i;
	
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 11:15
 		//in PASSWORD GUI, LEFT/RIGHT/UP/DOWN has no use.
		if(passwdGUI_state != NO_GUI_STATE)
			return;
#endif       	
	
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE                //zhaoyanhua add 03-11-7 16:02
	if(main_setup)
	{
	   switch(index_x)
	   {
	        case EXIT_SETUP_MENU_X:
	            draw_setup_Btn_HL( 1,EXIT_SETUP_MENU_X*14+32, EXIT_SETUP_MENU_Y*4, 9* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);		
		        index_x = ONE_KEY_PASS_X;
		        draw_setup_Btn_HL( 1, ONE_KEY_PASS_X*11, ONE_KEY_PASS_Y*4, 8* 24, 1*32,4,SETUP_HL_COLOR);	
		        break;
		    case ONE_KEY_PASS_X:
		        break;
		    case SETUP_X:
		        break;
		}
		return;
	}
#endif
    
	
	#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
//    UINT16 line=SETUP_MAX_WIDTH*16;	
    SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
         #elif defined(SETUP_COLOR_TYPE2)	
        //SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
        SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
//    UINT16 line=SETUP_MAX_WIDTH*16-20;
    #else
//    UINT16 line=SETUP_MAX_WIDTH*16-20;	
    SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
    #endif

    reset_passwd_cnt();


    if (full_scrn&CUSTM) {
        upperbound=2;
    } else {
        upperbound=0;
    }

    if (setupLevel==0) {
    	setupLevel=1;
    	index_y_start=0;
    	for (i=7;i>=0;i--)
    	{
    		if (setup_item[page][i][1]==STR_OS_RETURN_MAIN_SETUP)
    		{
    			index_y=i;
    			break;
    		}
    	}
    	// highlight : draw a frame to identify which tab is enable
		/*osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SBGCOLOR,1);
		osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SBGCOLOR,1);
		osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SBGCOLOR,1);
		osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SBGCOLOR,1);*/
//		#ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
                  #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)//zhangyu
		setup_Showredframe(page);
		#endif
		id = setup_item[page][index_y+index_y_start][1];
		setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);
		return;
    } else
		if (setupLevel==1) {
		
		#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE               //calculate setupItemNum[1] true value.zhaoyanhua add 03-11-7 14:03
		int iItemType;
		
		for (i=0; i<MAX_PAGE_ITEM; i++)
		{
    		iItemType=setup_item[page][i][0];
    		if (iItemType == SET_SPACE) continue;
    		if (iItemType == SET_NE) break;
		}
		setupItemNum[1] = i;
		#endif
			
			if (index_y==0)
			{
#ifdef 	VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 10:41
				if(page == VIDEOPAGE)
					osd_draw_rect((SETUP_SUB_XSTART-1)*16,(index_y +SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT+30,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,SETUP_BUTTON_HEIGHT,SBGCOLOR);	
				else
#endif//VIDEO_SETUP_NEW_GUI			
				#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
				//wangfeng 3-8-27 23:36
				osd_draw_rect((SETUP_SUB_XSTART-1)*16,
							   SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+30,
							   (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
							   (SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT-30,
							   SBGCOLOR);
                #elif defined(SETUP_COLOR_TYPE2)	
                osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                			   SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
                			   (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                			   (SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT,
                			   SBGCOLOR);
				#else
				osd_draw_rect((SETUP_SUB_XSTART-1)*16,
							   SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
							   (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
							   (SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT-30,
							   SBGCOLOR);
				#endif

			setupLevel=0;
			id=setup_item[page][index_y][1];
			setup_DrawItem(1, SETUP_MENU_YSTART+1, 0);

				// highlight : draw a frame to identify which tab is enable
				#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
				SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
                                #elif defined(SETUP_COLOR_TYPE2)
                                SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
				#else
				SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
				#endif
			/*	osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SANTIBGCOLOR,1);
				osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SANTIBGCOLOR,1);
				osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SANTIBGCOLOR,1);
				osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SANTIBGCOLOR,1);*/
				//#ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
                                      #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
				setup_Showredframe(page);
				#endif

			} else
			if ( (index_y+index_y_start) > upperbound) {
				if (full_scrn&CUSTM) {
					//clear third-level menu
#ifdef  RATING_8
                    if (index_y == 3) 
                    {
                  //  #ifndef	SETUP_COLOR_TYPE1	//zhangyu mark wangfeng 2003-08-29 17:28
//#ifndef SETUP_COLOR_TYPE1
                    #ifdef SETUP_COLOR_TYPE2
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                    			   SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
                    			   (SETUP_MAX_WIDTH-SETUP_SUB_XSTART)*16+16,
                    			   (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT-68,
                    			   SBGCOLOR);
                    #elif defined(SETUP_COLOR_TYPE1)
			        osd_draw_rect((SETUP_SUB_XSTART-1)*16,
			        			   SETUP_MENU_YSTART,
			        			   (SETUP_MAX_WIDTH-SETUP_SUB_XSTART)*16+60,
			        			   (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
			        			   SBGCOLOR);
                    #else
				    osd_draw_rect((SETUP_SUB_XSTART-1)*16,
				    			   SETUP_MENU_YSTART,
				    			   (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
				    			   (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
				    			   SBGCOLOR);
				    #endif
//#endif
					ShowCUSTMMsg();					
				}
				else
#endif//end RAGING_8
                #ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:09
                if(index_y==CUSTMOSDITEM)
                {
                    #ifdef SETUP_COLOR_TYPE2
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART)*16+16, (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT-68,SBGCOLOR);					
                    #elif defined(SETUP_COLOR_TYPE1)
        			osd_draw_rect((SETUP_SUB_XSTART-1)*16,SETUP_MENU_YSTART+32,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART)*16+60,(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,SBGCOLOR);	
                    #else
   					osd_draw_rect((SETUP_SUB_XSTART-1)*16,(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,SBGCOLOR);
					#endif
					if((8-N_OSD_LANGS)<=1)
					    ShowCUSTMMsg();
                }
                #endif  //SUPER_DEFAULT_OSD_LANG
					//wanghaoying mark 2003-10-24 16:16
					//this rectangle delete the bottom horizontal line
					{
				/*	osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
						SBGCOLOR);
			    */
			    }
					id = setup_item[page][index_y][1];
					setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

					index_y--;

					id = setup_item[page][index_y][1];
					setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);
					//draw ">>" between sub-mean and it's corresponding selection area
				#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
 
				if((id != STR_OS_)&&(!(one_key_pass_flag)))
				#else
				//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
				#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:04
					if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
				#endif//SAME_DISC_RESUME
				#endif//end BBK'S NEW_SETUP 							

					osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
					submenuStart = index_y+SETUP_MENU_YSTART;

					if (setup_item[page][index_y][0]==SET_NM) {
						char buf[8];
              	    
                  	#ifdef SETUP_6_DIGIT_PASSWORD //zhaoyanhua add 03-10-14 14:53
                    psprintf(buf, "%06d", UserSet.parent_passwd);
                    #else //4 digit password 
                        psprintf(buf, "%04d", UserSet.parent_passwd);
                    #endif   //end SETUP_6_DIGIT_PASSWORD
                    
                        osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                        
                        osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, SDEFAULTCOLOR,SBGCOLOR);

					} else {
                        //get select item
                        sel = setup_sel[page][index_y];
#ifdef RATING_8
                    if((page == CUSTMPAGEINDEX) && (index_y == 3))
                    {
                            submenuStart = SETUP_MENU_YSTART;
                        }
                    #ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:09
					else if(index_y==CUSTMOSDITEM)
						    submenuStart = SETUP_MENU_YSTART + (8-N_OSD_LANGS);
                    #endif
                        else{
                            submenuStart = index_y+SETUP_MENU_YSTART;
                        }
#else
					#ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:10
					if(index_y==CUSTMOSDITEM)
					    submenuStart = SETUP_MENU_YSTART + (8-N_OSD_LANGS);
					else
                    #endif
						submenuStart = index_y+SETUP_MENU_YSTART;
#endif
                        //draw third-level menu
                        for (i=2; i<MAX_ITEM_SEL; i++) {
                            id = setup_item[page][index_y][i];
                            if (id==0) break;
                            ShowSel(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,sel == i);
                        }
                        setupItemNum[2] = i - 2;
					}
				} else {
					//normal setup second-level menu page

					if ( (index_y==0) && (index_y_start>0) ) {
						index_y_start--;
						ShowSetupPage(1);
						return;
					}

					//clear third-level menu
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 10:15
				if(page == VIDEOPAGE)
					osd_draw_rect((SETUP_SUB_XSTART-1)*16,(index_y +SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT+30,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,SETUP_BUTTON_HEIGHT,SBGCOLOR);
				else	
#endif//VIDEO_SETUP_NEW_GUI							
					#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
					osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+30,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-65,
						SBGCOLOR);
#elif defined(SETUP_COLOR_TYPE2)
						osd_draw_rect((SETUP_SUB_XSTART-1)*16,
								SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
								(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
								(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-68,
								SBGCOLOR);
					#else
					osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT,
						SBGCOLOR);
                #endif

#if !defined( SETUP_COLOR_TYPE2)&& !defined(SETUP_COLOR_TYPE1)
					if (p_scan==1)
						osd_DrawLine(250, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 2);
					else
						osd_DrawLine(250, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
					#endif	

					id = setup_item[page][index_y+index_y_start][1];
					setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

					index_y--;

				#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE          //zhaoyanhua 03-11-7 11:19
					while(setup_item[page][index_y+index_y_start][0]==SET_SPACE)
					{
						index_y--;
					}
				#else	
					if (setup_item[page][index_y+index_y_start][0]==SET_SPACE)    index_y--;
				#endif	

#if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE) ||defined(SET_FCR_SPEAKER) //xulf 2004-01-07               
					//special case//nonotest 2003-9-5 17:49
					if (page==MULTISPKPAGE) {
						if (SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF) {
							if ( (index_y+index_y_start) == SPKEND) {
                                if (index_y_start==0) {
									index_y -= (SPKEND-SPKSTART+1);
                                } else {
									index_y = SPKSTART-1;
									index_y_start--;
									ShowSetupPage(1);

									return;
                                }
							}
						}
					} 
				#if !defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)
				else 
                #endif//ONLY_DOWNMIXOFF_CAN_SET_CE_RE
                
#endif//    #if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)                
                
#ifdef PROLOGICII_3D_MUTEX//4-2-12 1:23
			if((page==AUDPAGE)&&is_EQ_SOUND_set()&&(index_y==(PROLOGIC_II) )  )
          	index_y--;
#endif//PROLOGICII_3D_MUTEX                    
                
                #ifdef ONLY_DOWNMIX_IN_SPEAKER_PAGE//liweihua add 2004-1-2 15:05
                            id = setup_item[page][index_y][1];
                            if((page==MULTISPKPAGE) && (id != STR_OS_RETURN_MAIN_SETUP))
			    {
                                index_y = 0;//jump to downmix item
                            }
                #endif                
                
                #ifdef  SETUP_ALL_VALID
                #ifdef KARAOKE_MENU     
                //wangfeng 2003-10-29 21:37
                if((page==AUDPAGE)&&(index_y<2)&&(KARAOKE_MENU_FLAG))
                {
                	index_y=5;
                }
                else if((page==AUDPAGE)&&(index_y==5)&&(KARAOKE_MENU_FLAG==0))
                #ifdef PROLOGIC_ON_51CH
                	if(setup_IsSpkDownmixOff()){
                		index_y=1;
                		}
                	else
                		index_y=0;
                #else
                    index_y=1;//wangfeng 2003-11-11 13:55
                #endif
	            #endif
                #else
                    //#ifndef SETUP_ALL_VALID
				if (page==AUDPAGE) {
                        if ( (SETUP_SPDIF==SPDIFBITSTREAM) &&
							//(index_y==KEYITEM) &&
							(index_y==VOLCTRLEND) && //Jeff 20020723
							( ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
							//AUDIF_CODING_MODE_PCM|   //DTSCD-BITSTREAM MODE, Jeff 20020719
							AUDIF_CODING_MODE_DTS)
							)||(cd_subtype==CD_DTS) )//nono 2-7-25 17:29
							)
                        {
							index_y -= (VOLCTRLEND-VOLCTRLSTART+1);
                    } 
                        //else
                        //#endif

	                //#ifndef SETUP_ALL_VALID
                    else
                        {
							if (
								(
								( (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) &&
								(coding_mode_now&(AUDIF_CODING_MODE_AC3|
								AUDIF_CODING_MODE_DTS|
								AUDIF_CODING_MODE_DTSCD)
								)
								)
								||(coding_mode_now==AUDIF_CODING_MODE_LPCM)//terry,0512,currently ,we are not surport LPCM key shift
								)
								&&(index_y==KEYITEM)
								)
							{
								index_y--;
							}

                        }
					}
#ifndef NO_AC3_DYNAMIC_RANGE
					else if ( (page==AC3DIGITALPAGE) && //Jeff 20020621
						(index_y==(AC3DYNAMICITEM1)) &&
					( (SETUP_AC3DIGITAL_OUTMODE==AC3OUTMODEITEM)//AC3DYNAMICITEM2) //wanghaoying 2003-11-26 20:00
//						||(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)
						)
						)
					{
						index_y--;
//						index_y=AC3DYNAMICITEM1-1;
					}
#endif //NO_AC3_DYNAMIC_RANGE

#endif //#ifndef SETUP_ALL_VALID

					id = setup_item[page][index_y+index_y_start][1];

					setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);

					//the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
					if ( (index_y+index_y_start) < (setupItemNum[1]-1)) {
						//draw ">>" between sub-mean and it's corresponding selection area
				//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
				#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:05
						if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
						#endif 							
						osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
				
						submenuStart = index_y+SETUP_MENU_YSTART;

						//special item(PASSWORD), page-0, item-4
						if (setup_item[page][index_y+index_y_start][0]==SET_NM) {
							if (UserSet.parental_ststus==C_LOCK) {
								setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL;
								str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
							} else {
								setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL + 1;
								str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
							}
							osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
							
							osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, SDEFAULTCOLOR,SBGCOLOR);
							
						} else
							if (setup_item[page][index_y+index_y_start][0]==SET_SCALE) {
						#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 18:36
							if(page != VIDEOPAGE)
						#endif//VIDEO_SETUP_NEW_GUI
								setup_PrepareScaleItem(id, 0);
							} else {
								//special item(LANGUAGE)
#ifdef RATING_8
								if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) {
#else
									if (page==LANGPAGE) {
#endif
										submenuStart = SETUP_MENU_YSTART; //from 0
									}

									//get select item
						#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
								if(one_key_pass_flag)//OENKEYPASSPAGE
								{
									sel = GetOneKeyPageSel(index_y);
								}
								else
								sel=setup_sel[page][index_y+index_y_start];
						#else		
									sel = setup_sel[page][index_y+index_y_start];
						#endif
									//draw third-level menu
									for (i=2; i<MAX_ITEM_SEL; i++) {
										const char *str;
										id = setup_item[page][index_y+index_y_start][i];
										if (id==0) break;

										str = setup_SetItemString();

										if (sel == i) {
											osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
											osd_DrawString(SETUP_SUB_XSTART+1, (i-2+submenuStart)+1, str, SDEFAULTCOLOR, SBGCOLOR);
										} else {
											osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
											osd_DrawString(SETUP_SUB_XSTART+1, (i-2+submenuStart)+1, str, SFONTCOLOR, SBGCOLOR);
										}
									
									}
									setupItemNum[2] = i - 2;
								}
							}
					}
        }
    } else
		if (setupLevel==2) {
			upperbound=0;
			if (setup_item[page][index_y][0]==SET_SCALE) {
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 16:54
				if(page == VIDEOPAGE)
					return;
				else
#endif//VIDEO_SETUP_NEW_GUI		
				setup_CookScaleItem(id, 1);
				run_save_sel_cmd(page,index_y);
			} else
				if ( (index_y2 > upperbound) && (setup_item[page][index_y][0]!=SET_NM) ) {
					//third-level menu page
					#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
					if(one_key_pass_flag)
					{
						sel = GetOneKeyPageSel(index_y);
					printf("+++++++++++++ 6666sel = %d,index_y = %d--\n");
					}
					else
			sel = setup_sel[page][index_y];
					#else	
					sel = setup_sel[page][index_y];
					#endif

					id = setup_item[page][index_y][index_y2+2];
					str = setup_SetItemString();

					if ((index_y2+2) == sel) {
						//keep upper button to UP mode with SANTIBGCOLOR
						osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
						osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SDEFAULTCOLOR, SBGCOLOR);
					} else {
						//normal UP button
						osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
						osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SFONTCOLOR, SBGCOLOR);
					}

					index_y2--;

					if ((index_y2+2) == sel) {
						osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
					} else {
						osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 0);
					}

					id = setup_item[page][index_y][index_y2+2];
					str = setup_SetItemString();
					osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SANTIFONTCOLOR, SANTIBGCOLOR);
				}
		}
    #ifdef SETUP_COLOR_TYPE2   //3-10-28 1:43张宇P
    if (!(full_scrn&CUSTM))
osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/18, 13);//SBGCOLOR);
    #endif			
}

void setup_func_left(void)
{
    const char *str;
    UINT16 line = 0;
    
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 11:15
 		//in PASSWORD GUI, LEFT/RIGHT/UP/DOWN has no use.
		if(passwdGUI_state != NO_GUI_STATE)
			return;
#endif       	    
	#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
	line=SETUP_MAX_WIDTH*16;
	SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
#elif defined(SETUP_COLOR_TYPE2)	

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         //zhaoyanhua add 2003-11-30 21:38		
    if(!main_setup)
    {
#endif	
 //SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
 SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
        line=SETUP_MAX_WIDTH*16-20;
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         //zhaoyanhua add 2003-11-30 21:38		    
    }
#endif	
	#else
    line=SETUP_MAX_WIDTH*16-20;
	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
	#endif
	
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         //zhaoyanhua add 03-11-7 15:31left
	if (main_setup)
	{
		switch(index_x)
		{
			case ONE_KEY_PASS_X :
				draw_setup_Btn_HL( 1, ONE_KEY_PASS_X*11, ONE_KEY_PASS_Y*4, 8* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);	
				index_x = EXIT_SETUP_MENU_X;
				draw_setup_Btn_HL( 1,EXIT_SETUP_MENU_X*14+32, EXIT_SETUP_MENU_Y*4, 9* 24, 1*32,4,SETUP_HL_COLOR);		
				break;
			case SETUP_X:
				draw_setup_Btn_HL( 1,SETUP_X*14+28, SETUP_Y*4, 8* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);
				index_x = ONE_KEY_PASS_X;
				draw_setup_Btn_HL( 1, ONE_KEY_PASS_X*11, ONE_KEY_PASS_Y*4, 8* 24, 1*32,4,SETUP_HL_COLOR);	
				break;
			case EXIT_SETUP_MENU_X:
				draw_setup_Btn_HL( 1,EXIT_SETUP_MENU_X*14+32, EXIT_SETUP_MENU_Y*4, 9* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);		
				index_x = ONE_KEY_PASS_X;
				draw_setup_Btn_HL( 1, ONE_KEY_PASS_X*11, ONE_KEY_PASS_Y*4, 8* 24, 1*32,4,SETUP_HL_COLOR);	
				break;
		}
		return;	
	}
	
#endif
	
    if ( (setupLevel==0)
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
		&&(!one_key_pass_flag)
#endif  
    )
    {
    	// make tab disable
    	//#ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
      #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
    	osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+9, 1);
    	if (p_scan==1)
   			osd_DrawLine((line*page)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
   		else
   		//wangfeng 3-8-27 20:53
   			osd_DrawLine((line*page)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);
		#endif
		//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
		#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:05
		if(page==SysNextPage) page=0;
    	#endif

#ifdef NO_AUDIO_PAGE
   		if (page>0)
   		{
   			page--;
   			if(page==AUDPAGE)page--;
   		}
#else
   		if (page>0)
   			page--;
#endif
   		else
   			page=MAX_SHOW_PAGE;

#ifndef SETUP_ALL_VALID		// alan, 2003/7/18 10:49と
        if ( (page==AC3DIGITALPAGE) && 	( (SETUP_SPDIF==SPDIFBITSTREAM) || (coding_mode_now!=AUDIF_CODING_MODE_AC3) )  )
        {
			page--;
		}

        if ( (page==MULTISPKPAGE) &&  (cd_type_loaded!=CDDVD) && ( coding_mode_now&(~(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD)) ) )
        {
			page--;
        } else if ( (page==MULTISPKPAGE) && (SETUP_SPDIF!=SPDIFSIMULATE) )
        {
			page--;
        }
#endif

        #ifdef TWO_CHANNEL_ONLY
        if (page==MULTISPKPAGE)     page--;
        #endif

        // make tab enable
//        #ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
 #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
  		osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
		#endif
   		
   		// highlight : draw a frame to identify which tab is enable
   		#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
   		SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
   		#endif
        
#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
   		SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
   		#endif
		/*osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SANTIBGCOLOR,1);*/
		#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
		setup_Showredframe(page);
		#endif
   		setupLevel=1;
   		ShowSetupPage(0);
   		setupLevel=0;
    }
    else
    if (setupLevel==2) { //left operation only active when switch to selection area of sub-menu
        if (full_scrn&CUSTM) {
            if (setup_item[page][index_y][0]==SET_NM) {
                
				char buf[8];
                
                osd_draw_setup_button(SETUP_SUB_XSTART, submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
			
			#ifdef SETUP_6_DIGIT_PASSWORD//zhaoyanhua add 03-10-14 14:50
                psprintf(buf, "%06d", UserSet.parent_passwd);
            #else
                psprintf(buf, "%04d", UserSet.parent_passwd);
            #endif
            
                osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, SFONTCOLOR, SBGCOLOR);
            } else {
                id = setup_item[page][index_y][index_y2+2];
                
                #ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:10
	            if((page==CUSTMPAGEINDEX)&&(index_y==CUSTMOSDITEM))
	                str = lang_names[osd_font_mode][id];
	            else
                #endif 
                
                str = _OsdMessegeFont1[osd_font_mode][id];
        	    
        	#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
				if(one_key_pass_flag)
				{
					sel = GetOneKeyPageSel(index_y);
				}
				else
				sel=setup_sel[page][index_y];
			#endif		
                
                if ((index_y2+2) == sel) {
                	osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                    
                	osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SDEFAULTCOLOR, SBGCOLOR);
                   
                } else {
                    setup_DrawItem(2, index_y2+submenuStart+1, 0);
                }
            }
        } else {
#ifdef RATING_8
	#ifdef NO_DIGIT_VIDEO_MENU			
			if ( page!=SYSPAGE&&index_y==3&&page!=AUDPAGE )
	#else//NO_DIGIT_VIDEO_MENU
			//if ( page!=SYSPAGE&&index_y==3 )//zhaoyanhua modify 2003-11-30 13:42
			if((page == SYSPAGE) && (index_y == GRADEITEM))
	#endif//NO_DIGIT_VIDEO_MENU
			{
				submenuStart = SETUP_MENU_YSTART;
			}
			else
			{
				submenuStart = index_y+SETUP_MENU_YSTART;
			}
#else
			submenuStart = index_y+SETUP_MENU_YSTART;
#endif
            //change string color of current selection item in selection area

            //special item(PASSWORD), page-0, item-4
            if (setup_item[page][index_y][0]==SET_NM) {
                osd_draw_setup_button(SETUP_SUB_XSTART, submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
                show_lock(UserSet.parental_ststus,0);
            } else if (setup_item[page][index_y][0]==SET_SCALE) {
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 16:31
				if(page == VIDEOPAGE)
				{
					setup_CookScaleItem(id, 0);
					run_save_sel_cmd(page,index_y);
					return;
				}
				else
				{
#endif//VIDEO_SETUP_NEW_GUI
					setup_PrepareScaleItem(id, 0);

					if ((id == STR_OS_BRIGHTNESS) ||
						(id == STR_OS_CONTRAST) ||
						(id == STR_OS_HUE) ||
						(id == STR_OS_SATURATION)
#ifdef DIP_CFG_ENABLE
						||(id == STR_OS_DEINTLC)
#endif//#ifdef DIP_CFG_ENABLE
					   ) // robert 030214
						{
							osd_replace_rect_color(SBGCOLOR,SBGCOLOR);
						}
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 16:31
				}
#endif//VIDEO_SETUP_NEW_GUI
				} else {
					//special item(LANGUAGE)
#ifdef RATING_8
					//if (page==LANGPAGE||(setup_sel[page][index_y]==SETUP_GRADE )) {
					if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) {
#else
						if (page==LANGPAGE) {
#endif
							submenuStart = SETUP_MENU_YSTART; //from 0
						}

						id = setup_item[page][index_y][index_y2+2];
						str = setup_SetItemString();

						if ((index_y2+2) == sel) {
							osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
							osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SDEFAULTCOLOR,SBGCOLOR);
						} else {
							osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
							osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SFONTCOLOR, SBGCOLOR);
						}
				
					}
				}

				//change string color of current item in sub-menu
				id = setup_item[page][index_y][1];
				str = _OsdMessegeFont1[osd_font_mode][id];
				osd_draw_setup_button(SETUP_MENU_XSTART, index_y+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, SANTIBGCOLOR, 1);
				osd_DrawString(SETUP_MENU_XSTART+1, index_y+SETUP_MENU_YSTART+1, str, SANTIFONTCOLOR, SANTIBGCOLOR);
				setupLevel = 1;
		}
#ifdef SETUP_COLOR_TYPE2     //3-10-28 1:43张宇P
if (!(full_scrn&CUSTM))
osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/18, 13);//SBGCOLOR);
#endif	
}

void setup_func_right(void)
{
#ifdef SETUP_DONGLI459			//dingzhy  for  tonic  2004-2-10 22:56
if(ShowPasswordErr)
ShowPasswordErr=0;
#endif

	const char *str;
	UINT16 line = 0;
	
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 11:15
 		//in PASSWORD GUI, LEFT/RIGHT/UP/DOWN has no use.
		if(passwdGUI_state != NO_GUI_STATE)
			return;
#endif       		
	
	/*#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
	UINT16 line=SETUP_MAX_WIDTH*16;
	SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
        #elif defined(SETUP_COLOR_TYPE2)	
        UINT16 line=SETUP_MAX_WIDTH*16-20;	
        SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);	
	#else
	UINT16 line=SETUP_MAX_WIDTH*16-20;
	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
	#endif*/
	
	#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
	line=SETUP_MAX_WIDTH*16;
	SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
	#elif defined(SETUP_COLOR_TYPE2)	
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         //zhaoyanhua add 2003-11-30 21:38		
 	if(!main_setup)
 	{
#endif
 	//SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
 	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
 	line=SETUP_MAX_WIDTH*16-20;
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
    }
#endif	
	#else
	line=SETUP_MAX_WIDTH*16-20;
	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
	#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         //right
	if (main_setup)
	{
		switch(index_x)
		{
			case ONE_KEY_PASS_X :
				draw_setup_Btn_HL( 1, ONE_KEY_PASS_X*11, ONE_KEY_PASS_Y*4, 8* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);	
				index_x = SETUP_X;
				draw_setup_Btn_HL( 1,SETUP_X*14+28, SETUP_Y*4, 8* 24, 1*32,4,SETUP_HL_COLOR);
				break;
			case SETUP_X:
				draw_setup_Btn_HL( 1,SETUP_X*14+28, SETUP_Y*4, 8* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);
				index_x = EXIT_SETUP_MENU_X;
				draw_setup_Btn_HL( 1,EXIT_SETUP_MENU_X*14+32, EXIT_SETUP_MENU_Y*4, 9* 24, 1*32,4,SETUP_HL_COLOR);		
				break;
			case EXIT_SETUP_MENU_X:
			draw_setup_Btn_HL( 1,EXIT_SETUP_MENU_X*14+32, EXIT_SETUP_MENU_Y*4, 9* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);		
				index_x = SETUP_X;
				draw_setup_Btn_HL( 1,SETUP_X*14+28, SETUP_Y*4, 8* 24, 1*32,4,SETUP_HL_COLOR);
				break;
		}
		return;
	}
#endif
	
    if ((setupLevel==0)
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
		&&(!one_key_pass_flag)
#endif  
		)  
    {
    	//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
    	#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:06
		if(page==SysNextPage) page=0;
    	#endif

    	// make tab disable
#ifndef	SETUP_COLOR_TYPE1
#ifdef SETUP_COLOR_TYPE2
osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+7, 13);
#else
    	osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+9, 1);
#endif
#endif

//    	#ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)

    	osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+9, 1);
    	if (p_scan==1)
    		osd_DrawLine((line*page)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
    	else
    		osd_DrawLine((line*page)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);
		#endif
        
#ifdef NO_AUDIO_PAGE
    	if (page<=MAX_SHOW_PAGE)
    	{
    		page++;
            if(page==AUDPAGE)page++;
        }
#else
    	if (page<=MAX_SHOW_PAGE)
			page++;
#endif

#ifndef SETUP_ALL_VALID		// alan, 2003/7/18 10:49と
        if ( (page==MULTISPKPAGE)&&(cd_subtype!=CD_DTS) &&  (cd_type_loaded!=CDDVD) && ( coding_mode_now&(~(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD)) ) )
        {
			page++;
        } else if ( (page==MULTISPKPAGE) && (SETUP_SPDIF!=SPDIFSIMULATE) )
        {
			page++;
		}

        if ( (page==AC3DIGITALPAGE) && 	( (SETUP_SPDIF==SPDIFBITSTREAM) || (coding_mode_now!=AUDIF_CODING_MODE_AC3) )  )
        {
			page++;
		}
#endif

        #ifdef TWO_CHANNEL_ONLY
        if (page==MULTISPKPAGE)     page++;
        #endif

    	if (page>MAX_SHOW_PAGE)
    		page=0;
		//wangfeng 3-8-27 22:11
		//#ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
    	osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
		#endif
//#ifndef SETUP_COLOR_TYPE2		
#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
    	osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
		#endif
    	// highlight : draw a frame to identify which tab is enable
    	#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
    	SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
    	#elif defined(SETUP_COLOR_TYPE2)
    	 SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
    	#else
    	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
    	#endif
		/*osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SANTIBGCOLOR,1);*/
		//#ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
		setup_Showredframe(page);
		#endif
    	setupLevel=1;
    	ShowSetupPage(0);
    	setupLevel=0;
    }
    else
	//right operation only active when switch to menu of sub-menu
	if (setupLevel==1) {

	if (index_y==(setupItemNum[1]-1)) return;

#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 16:31
	if(page == VIDEOPAGE)//when setupLevel =1 RIGHT has no use.
		return;
#endif//VIDEO_SETUP_NEW_GUI		

#ifndef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 9:43
	//check GRADE
	if ( (page==SYSPAGE) && (index_y==GRADEITEM) ) {
		if (UserSet.parental_ststus==C_LOCK) return;
	}
#endif//SETUP_PASSWORD_GUI

    id = setup_item[page][index_y][1];
        
	    //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
	    #if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:06
	if (id==STR_OS_NEXT_PAGE) return;
	if (id==STR_OS_PREV_PAGE) return;
	#endif
	    
	#ifdef	VGA_CTRL_FORMAT	//wangfeng,2003-10-20 23:07
	if (setup_IsVGAOn()) return;
	#endif
	
	//change string color of current item in sub-menu
	osd_draw_setup_button(SETUP_MENU_XSTART, index_y+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, SBGCOLOR, 1);
	id = setup_item[page][index_y][1];
	str = _OsdMessegeFont1[osd_font_mode][id];
	osd_DrawString(SETUP_MENU_XSTART+1, index_y+SETUP_MENU_YSTART+1, str, SDEFAULTCOLOR,SBGCOLOR);

	//change string color of current selection item in selection area
	submenuStart = index_y + SETUP_MENU_YSTART;
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
		if(one_key_pass_flag)
		{
			sel = GetOneKeyPageSel(index_y);
		}
		else
	sel = setup_sel[page][index_y];
#else		

		sel=setup_sel[page][index_y];
#endif
	
	index_y2 = sel-2;

	if (full_scrn&CUSTM) {
		//special item(PASSWORD), page-0, item-4
		if (setup_item[page][index_y][0]==SET_NM) {
			char buf[8];
			osd_draw_setup_button(SETUP_SUB_XSTART, submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
		    #ifdef SETUP_6_DIGIT_PASSWORD //zhaoyanhua add 03-10-14 14:52
			psprintf(buf, "%06d", UserSet.parent_passwd);
		    #else  //4 digit  password
			psprintf(buf, "%04d", UserSet.parent_passwd);
		    #endif //end SETUP_6_DIGIT_PASSWORD
			osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, SANTIFONTCOLOR, SANTIBGCOLOR);
		} 
		else 
		{
			id = setup_item[page][index_y][index_y2+2];
			    
#ifdef RATING_8
			if ( page!=SYSPAGE&&index_y==3 ) 
			{
				submenuStart = SETUP_MENU_YSTART;
			}
			    #ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:10
				else if(index_y==CUSTMOSDITEM)
					    submenuStart = SETUP_MENU_YSTART +(8-N_OSD_LANGS);
                #endif
			else
			{
                submenuStart = index_y+SETUP_MENU_YSTART;
			}
                #else   //RATING_8
                #ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:10
				if(index_y==CUSTMOSDITEM)
					    submenuStart = SETUP_MENU_YSTART + (8-N_OSD_LANGS);
                else
                #endif
			submenuStart = index_y+SETUP_MENU_YSTART;
                #endif  //RATING_8

#ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:10
   				if(index_y==CUSTMOSDITEM)
   				{
   				    id = setup_item[page][index_y][index_y2+2];
				    str = setup_SetItemString();
				    osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
				    osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SANTIFONTCOLOR, SANTIBGCOLOR);
                }
                else
#endif
			setup_DrawItem(2, index_y2+submenuStart+1, 1);
		}
	} else {
		//special item(PASSWORD), page-0, item-4
		if (setup_item[page][index_y][0]==SET_NM) {
			osd_draw_setup_button(SETUP_SUB_XSTART, submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
			show_lock(UserSet.parental_ststus,1);
		} else
			if (setup_item[page][index_y][0]==SET_SCALE) {
				if ((id == STR_OS_BRIGHTNESS) ||
					(id == STR_OS_CONTRAST) ||
					(id == STR_OS_HUE) ||
					(id == STR_OS_SATURATION)
                #ifdef DIP_CFG_ENABLE
					||(id == STR_OS_DEINTLC)
                #endif//#ifdef DIP_CFG_ENABLE
				   ) // robert 030214
				{
					//osd_replace_rect_color(0, 0, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), SBGCOLOR, 12);
					osd_replace_rect_color(SBGCOLOR, SBGCOLOR);//15);
				}
				setup_PrepareScaleItem(id, 1);
			} else {
				//special item(LANGUAGE)
#ifdef RATING_8
				if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) {
#else
					if (page==LANGPAGE) {
#endif
						submenuStart = SETUP_MENU_YSTART; //from 0
					}

					id = setup_item[page][index_y][index_y2+2];
					str = setup_SetItemString();
					osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
					osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SANTIFONTCOLOR, SANTIBGCOLOR);
				}
			}
	#ifdef SHOW_STANDBY_TIMER//suqiaoli add 2003-8-5 
	if (setup_item[page][index_y][1]==STR_OS_VFD_TIME)	
	{	
		reset_standby_timer_pos();
	}
	#endif

			setupLevel = 2;
	}
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 16:31
	else if(setupLevel == 2)
	{
		if(page == VIDEOPAGE)
		{
			setup_CookScaleItem(id, 1);
			run_save_sel_cmd(page,index_y);
			return;
		}
	}
#endif	//VIDEO_SETUP_NEW_GUI			
#ifdef SETUP_COLOR_TYPE2   //3-10-28 1:44张宇P
if (!(full_scrn&CUSTM))	
osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/18, 13);//SBGCOLOR);
#endif
}

void setup_func_select(void)
{
	const char *str;
	UINT8   md=setup_item[page][index_y][0];

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
	if(main_setup)
	{
		switch(index_x)
		{
			case ONE_KEY_PASS_X :
				one_key_pass_flag = 1;  
				main_setup = 0;
				ShowOneKeyPassPage();	
				break;
			case SETUP_X:
				one_key_pass_flag = 0; 
				main_setup = 0; 
				ShowProfessionalSetup();
				break;
			case EXIT_SETUP_MENU_X:
				index_x = 0;
				one_key_pass_flag = 0;
				main_setup = 0;  
				ExitSetupPage(1);
				break;
		}
		
		return;
	}
    #endif  //defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)

#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 14:56
    if(new_parental_gui)
    {
        check_parent_password();
        new_parental_gui = 0;

        return;    
    }
#endif
    
#if defined(DVD_AUDIO)//20040302
	if(pDSV->hid_gp_chk_pwd==2)
	{
	    check_dvd_audio_password();//nono 2004/3/2 05:40PM
              return; 
	}
#endif//#if defined(DVD_AUDIO)
    
	if (setupLevel == 1)
	{
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
		if(one_key_pass_flag)//zhaoyanhua add 2003-11-18 17:26
		{
			sel = GetOneKeyPageSel(index_y);
		}
		else
			sel=setup_sel[page][index_y];
#else		

		sel=setup_sel[page][index_y+index_y_start];
#endif
		
		id=setup_item[page][index_y+index_y_start][1];

		if (id == STR_OS_RETURN_MAIN_SETUP)
		{
			if (full_scrn&CUSTM)
			{
				ExitSetupPage(1);
			}
		#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         

		//exit to main page
			else 
			{
				main_setup = 1;
				if(index_x == ONE_KEY_PASS_X)
					one_key_pass_flag = 0;
				
				 osd_init_bbk_setup();			 
			
				ShowSetupMainPage();
			}
		#else
            #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP			//gerry,2004-3-12 13:19
			if (page==SysNextPage)		//in fact it is Prev-Page,2004-2-2 20:35
			{
    			page=0;
    			setupLevel=1;
    			index_y = 0;
    			index_y_start=0;
    			ShowSetupPage(1);
    			ShowSetupPage(2);
    			return;
			}
		    #endif//NEXT_PAGE_SHOW_ADVANCED_SETUP
			else
			{
				ExitSetupPage(1);
			}
		#endif//BBK_DVD
		}
		else
#ifdef SHOW_STANDBY_TIMER  //suqiaoli add 2003-8-8 
		if (setup_item[page][index_y][1]==STR_OS_VFD_TIME)	
			setup_func_right();
		else
#endif		
		{
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:07
			if (id==STR_OS_NEXT_PAGE)
			{
			page=SysNextPage;
			setupLevel=1;
			index_y = 0;
			index_y_start=0;
			ShowSetupPage(1);
			ShowSetupPage(2);
			printf("======      clead next       ======\n\n");
			return;
		}else 
			if (id==STR_OS_PREV_PAGE)
			{
			page=0;
			setupLevel=1;
			index_y = 0;
			index_y_start=0;
			ShowSetupPage(1);
			ShowSetupPage(2);
			printf("======      clead PREV       ======\n\n");
			return;
			}else 
#endif 

#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 17:03
		if(page == VIDEOPAGE)
		{	
			setupLevel = 2;
			setup_ShowVideoGUI(id);
		}
		else
#endif//VIDEO_SETUP_NEW_GUI
			setup_func_right();
		}
	}
	else if (setupLevel == 2)
	{
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
		if(one_key_pass_flag)//OENKEYPASSPAGE
		{
			sel = GetOneKeyPageSel(index_y);
		}
		else
		sel=setup_sel[page][index_y];
#else		
		sel=setup_sel[page][index_y];
#endif		
		
		id=setup_item[page][index_y][1];

#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 9:58
		//if pasword ITEM,show  password GUI
		if((page == SYSPAGE) && (index_y == PASSWDITEM) && (passwdGUI_state == NO_GUI_STATE))
		{
			UserSet.parental_ststus = C_LOCK;
			passwdGUI_state = INPUT_OLD_PASSWD_STATE;
			setup_ShowPasswdGUI();
			return;
		}
#endif//SETUP_PASSWORD_GUI
        
		//PASSWORD item
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 9:58
		//in password GUI,then can input password
		if(((passwdGUI_state != NO_GUI_STATE) && (full_scrn & SETUP))//SETUP state
		  || ((md == SET_NM) && (full_scrn & CUSTM)) )//CUSTM state
#else		
		if (md==SET_NM)
#endif//SETUP_PASSWORD_GUI	
		{
			if(digit_cnt == PASSWORD_LENGTH)
			{
				if (UserSet.parental_ststus==C_LOCK && (tmp_passwd==UserSet.parent_passwd 
				    #ifdef USER_SUPER_PASSWORD
				    ||tmp_passwd==USER_SUPER_PASSWORD 
				    #endif
				    ))
				{
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 14:20
					if(passwdGUI_state == INPUT_OLD_PASSWD_STATE)
					{
						//input old password
						passwdGUI_state = INPUT_NEW_PASSWD_STATE;
						setup_PasswdGUIRefresh(passwdGUI_state);
						UserSet.parental_ststus =C_UNLOCK;
						digit_cnt = 0;
					}
					else if(passwdGUI_state == INPUT_GRADE_PASSWD_STATE)
					{
						passwdGUI_state = SHOW_OK_STATE;
						setup_PasswdGUIRefresh(passwdGUI_state);
						UserSet.parental_ststus = C_LOCK ;
						digit_cnt = 0;
					}
					else if(passwdGUI_state == NO_GUI_STATE)
#endif//SETUP_PASSWORD_GUI					
					show_lock(C_UNLOCK,1);
				}
				else
				{
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-30 11:25
					//old password error.
					//refresh passwd GUI
					if((passwdGUI_state == INPUT_OLD_PASSWD_STATE)
					   ||(passwdGUI_state == INPUT_GRADE_PASSWD_STATE))
					{
						BYTE tmp_state = passwdGUI_state;
						
						passwdGUI_state = SHOW_ERROR_STATE;
						setup_PasswdGUIRefresh(passwdGUI_state);
						passwdGUI_state = tmp_state;
					}
#endif//SETUP_PASSWORD_GUI
					if(UserSet.parental_ststus==C_UNLOCK)
					{
						UserSet.parent_passwd=tmp_passwd;
#ifdef	SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 16:18
						if(passwdGUI_state == INPUT_NEW_PASSWD_STATE)
						{		
						//old password is correct.
						//so permit input new password
						passwdGUI_state = SHOW_OK_STATE;
						setup_PasswdGUIRefresh(passwdGUI_state);
						digit_cnt = 0;
						}
#endif//SETUP_PASSWORD_GUI					
					}
#ifdef TONIC_DVD
					if(UserSet.parental_ststus==C_LOCK)
					ShowPasswordErr=1;
#endif

#ifndef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 14:19
					if (!(full_scrn&CUSTM))//zhaoyanhua tmep mask 2004-1-15 15:00
						show_lock(C_LOCK,1);
#endif//SETUP_PASSWORD_GUI				
				}

			#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         

				if(one_key_pass_flag)
				{
					switch(index_y)
					{
						case 0:
							SETUP_TV_FORMAT = sel;//to make ONEKEYPAGE and SYSPAGE same.
							break;
						case 1:	
							SETUP_SPK_DOWNMIX = sel;// to make ONEKEYPAGE and MULTISPKPAGE same. 
							break;
					}
				}
			#endif
				
				if(user_input_pwd!=1)//2002-6-13 for huajia
					run_save_sel_cmd(page,index_y);
			}
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 14:21
			else if((passwdGUI_state == SHOW_OK_STATE) && (digit_cnt==0))
			{
				passwdGUI_state = NO_GUI_STATE; //exit PASSWORD GUI, return main setup
				UserSet.parental_ststus = C_LOCK ;
				//for GRADE ITEM, save level
				if ( (page==SYSPAGE) && (index_y==GRADEITEM) ) 
				{	
					SETUP_GRADE = index_y2 + 2;
					sel = index_y2+2;
					SETUP_CUSTM_GRADE = SETUP_GRADE;
					exe_setup_function(setup_item[page][index_y][1],setup_item[page][index_y][sel],1);//zhaoyanhua add 2004-2-9 15:47
			    	run_save_sel_cmd(page, index_y); 
				}
				//reset SANTIBGCOLOR.
				//before enter GUI , make SANTIBGCOLOR not trantent
				//when exit GUI, must reset SANTIBGCOLOR
				SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
				setupLevel = 1;
				ShowSetupPage(2);
				return;
			}
#endif//SETUP_PASSWORD_GUI

#ifdef ENTER_USE_OLD_PASSWD			
			else if( (UserSet.parental_ststus==C_UNLOCK)&&(digit_cnt==0) )
			{//terry,2003/8/29 12:10AM,auto lock
			    show_lock(C_LOCK,1);
			    run_save_sel_cmd(page,index_y);
			}
#endif

			reset_passwd_cnt();
			
#ifdef 	SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 14:43
			if(passwdGUI_state == NO_GUI_STATE)
#endif		
			
			setup_func_left();
			return;
		}
		else
		if (setup_item[page][index_y][0]==SET_SCALE)
		{
			// run_save_sel_cmd(page,index_y);
			//    setup_func_left();
		}
		else
#ifdef SHOW_STANDBY_TIMER  //suqiaoli  add 2003-8-8 
		if (setup_item[page][index_y][1]==STR_OS_VFD_TIME)
		{
			if(index_x!=0)
				exe_standby_timer();
			else
				setup_func_left();
		}
		else
#endif		
		if ((index_y2+2) != sel)
		{
#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 9:48
			if ( (page==SYSPAGE) && (index_y == GRADEITEM) && (passwdGUI_state == NO_GUI_STATE)) 
			{
				UserSet.parental_ststus = C_LOCK;
				passwdGUI_state = INPUT_GRADE_PASSWD_STATE;
				printf("### --- GRADE :passwdGUI_state--%d-\n",passwdGUI_state);
				setup_ShowPasswdGUI();
				
				return;
			}
            #endif//SETUP_PASSWORD_GUI			
            
			//UP origional
			id = setup_item[page][index_y][sel];
			osd_draw_setup_button(SETUP_SUB_XSTART, (sel-2)+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
			str = setup_SetItemString();
			osd_DrawString(SETUP_SUB_XSTART+1, (sel-2)+submenuStart+1, (char *)str, SFONTCOLOR, SBGCOLOR);
			//DOWN current
			id = setup_item[page][index_y][index_y2+2];
			osd_draw_setup_button(SETUP_SUB_XSTART, (index_y2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
			str = setup_SetItemString();
			osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, (char *)str, SANTIFONTCOLOR, SANTIBGCOLOR);
			setup_sel[page][index_y] = index_y2 + 2;

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         

			if(one_key_pass_flag)
			{
				switch(index_y)
				{
					case 0:
						SETUP_SPK_DOWNMIX = index_y2+2;// to make ONEKEYPAGE and MULTISPKPAGE same. 
						break;
					case 1:	
						SETUP_TV_FORMAT = index_y2+2;//to make ONEKEYPAGE and SYSPAGE same.
						break;
					default: sel = 2;
				}
				sel = index_y2+2;
			}
			else
			{
				setup_sel[page][index_y] = index_y2 + 2;
			sel = setup_sel[page][index_y];
			}
#else
			setup_sel[page][index_y] = index_y2 + 2;
			sel = setup_sel[page][index_y];
#endif
			
			id = setup_item[page][index_y][1];

			if ( (page==CUSTMPAGEINDEX) && (id==STR_OS_RATING) )
			{
				SETUP_GRADE = SETUP_CUSTM_GRADE;
				run_save_sel_cmd(SYSPAGE, GRADEITEM);
			}
			//zhaoyanhua add these sentence 2003-12-2 11:13
			//to avoid the bug when set rating in SYSPAGE ,then excute"DEFAULT VALUE"
			//can not lock the disc.
			else if((page == SYSPAGE)&&(id == STR_OS_RATING))
			{
			    SETUP_CUSTM_GRADE = SETUP_GRADE;
			    run_save_sel_cmd(CUSTMPAGEINDEX, CUSTMRATEITEM); //20040325
//			    run_save_sel_cmd(CUSTMPAGEINDEX, CUSTMPASSWDITEM); 
			}
            

			if (md==SET_FUNC)
			{

#ifdef SET_PARENTAL_STS_AUTO_LOCK	
				if( (UserSet.parental_ststus==C_UNLOCK)&& (page==SYSPAGE)&&(id==STR_OS_RATING)  )
				{//nono,2003-11-21 12:06,auto lock
	
				    UserSet.parental_ststus=C_LOCK;
				    SETUP_PASSWORD = MIN_ITEM_SEL+C_LOCK;
				    run_save_sel_cmd(SYSPAGE,PASSWDITEM);
				}
#endif //SET_PARENTAL_STS_AUTO_LOCK

				exe_setup_function(setup_item[page][index_y][1],setup_item[page][index_y][sel],1);
/*
#ifdef  OFF_PROLOGIC_WHEN_NOT_DOWNMIXOFF//zhaoyanhua 2003-12-10 9:37
                //if PROLOGIC_II is NOT OFF ,DOWNMIX MODE is not DOWNMIXOFF, must turn PRLOGIC OFF. 
                //zhaoyanhua add 2003-12-10 9:48
                if((SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)&&(SETUP_PROLOGIC_II != 4))
                {
                     SETUP_PROLOGIC_II =4;
                     exe_setup_function(STR_OS_PROLOGIC,STR_OS_OFF,0);   
                    
                }
#endif*/

#if defined(SUPPORT_PROLOGIC_II)// && !defined(TEMP_TWO_CHANNEL)//terry,2004/1/9 10:58AM
				if ( (setup_item[page][index_y][1]==STR_OS_PROLOGIC) &&
					 (setup_item[page][index_y][sel]!=STR_OS_OFF)
				   )
				{
					SETUP_SPK_DOWNMIX=AC3DOWNMIXOFF;
                    //exe_setup_function(STR_OS_DOWNMIX_SETUP,setup_sel[MULTISPKPAGE][AC3DOWNMIXOFF],1);
                    exe_setup_function(STR_OS_DOWNMIX_SETUP,STR_OS_OFF,0);//nono 2004-2-16 11:04
                    run_save_sel_cmd(MULTISPKPAGE, AC3DOWNMIXITEM);//nono 2004-2-16 15:04
				}
				
				if ( (setup_item[page][index_y][1]==STR_OS_DOWNMIX_SETUP) &&
					 (setup_item[page][index_y][sel]!=STR_OS_OFF)
				   )
				{
					SETUP_PROLOGIC_II=PROLOGIC_OFF;    // alan, 2003/8/11 01:56PM							
					exe_setup_function(STR_OS_PROLOGIC,STR_OS_OFF,0);
					run_save_sel_cmd(AUDPAGE, PROLOGIC_II);//nono 20031117
				}				
#endif//SUPPORT_PROLOGIC_II

#ifdef VGA_CTRL_FORMAT	//wangfeng,2003-10-20 22:47
				if ( (setup_item[page][index_y][1]==STR_OS_VIDEO) &&
					 (setup_item[page][index_y][sel]==STR_OS_PC_VGA)
				   )
				{
					temp_format=SETUP_TV_FORMAT;//wangfeng 2003-12-18 15:59
					SETUP_TV_FORMAT=2;
					exe_setup_function(STR_OS_TV_SYS,STR_OS_NTSC,1);
					//run_save_sel_cmd(SYSPAGE,TV_FORMAT);
					
				}
				else if(temp_format)//wangfeng 2003-12-18 16:44			
				{
					UINT8 temp;
					switch(temp_format){
					case 2:
						temp=STR_OS_NTSC;
						break;
					case 3:
						temp=STR_OS_PAL60;
						break;
					case 4:
						temp=STR_OS_PAL;
						break;
					case 5:
						temp=STR_OS_AUTO;
						break;
					default:
						break;
					}
					SETUP_TV_FORMAT=temp_format;
					temp_format=0;
					exe_setup_function(STR_OS_TV_SYS,temp,1);
					//run_save_sel_cmd(SYSPAGE,TV_FORMAT);
				}
					run_save_sel_cmd(SYSPAGE,TV_FORMAT);
				WriteToI2c(0xa0, ADDR_I2C_VGA,(BYTE *)&temp_format,sizeof(temp_format));
/*				
				if ( (setup_item[page][index_y][1]==STR_OS_VIDEO) &&
					 (setup_item[page][index_y][sel]==STR_OS_YCbCr)
				   )
				{
					SETUP_TV_FORMAT=4;							
					exe_setup_function(STR_OS_TV_SYS,STR_OS_PAL,1);
					run_save_sel_cmd(SYSPAGE,TV_FORMAT);
					
				}
				if ( (setup_item[page][index_y][1]==STR_OS_VIDEO) &&
					 (setup_item[page][index_y][sel]==STR_OS_P_SCAN_YUV)
				   )
				{
					SETUP_TV_FORMAT=4;							
					exe_setup_function(STR_OS_TV_SYS,STR_OS_PAL,1);
					run_save_sel_cmd(SYSPAGE,TV_FORMAT);
				}	
*/
#endif//VGA_CTRL_FORMAT
			}

#ifdef	SCART_TV_5	//wangfeng 2003-12-2 11:43 for himage HJ-023 
if(setup_item[page][index_y][1]==STR_OS_VIDEO){
	if (setup_item[page][index_y][sel]==STR_OS_PC_VGA)
	{
		//printf("is vga out put------\n");
		ReSetScartTV5();
	}	
	else
	{
		SetScartTV5();
		//printf("is not vga out put------\n");
	}
	
}	
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
	if(one_key_pass_flag)
	{
		switch(index_y)
		{
			case 0:
				run_save_sel_cmd(MULTISPKPAGE,0);// to make ONEKEYPAGE and MULTISPKPAGE same. 
				break;
			case 1:	
				run_save_sel_cmd(SYSPAGE,0);//to make ONEKEYPAGE and SYSPAGE same.
				break;
		}
	}
	else
#endif		
			run_save_sel_cmd(page,index_y);
			//  setup_func_left();
		}

        //ShowSetupPage(2);
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 11:29		
		if((page == VIDEOPAGE) && (setup_item[page][index_y][0] == SET_SCALE))
		{	
			//setup_ShowVideoGUI(setup_item[page][index_y][1]);
			setupLevel = 1;
			ShowSetupPage(2);
		}
		else
#endif//VIDEO_SETUP_NEW_GUI				
		setup_func_left();

		if (id==STR_OS_DEFAULT_SETUP)
		{
			set_default_value();
			run_set_variable();
#if defined(YUV_DEFAULT_OUTPUT) && defined(DELETE_VIDEO_ITEM)
        #ifdef S_VIDEO_OUT
       regs0->emu_cfg[1]|=0x100;
        #endif //#ifdef S_VIDEO_OUT
		setup_tv_out(INTERLACE);//set S-video output(composited+component)(0x00:D0-D1-D2-D3=CVBS-V-Y-U)
		search_ap_tv_out_id();//terry,2003/8/19 03:21PM
#endif		
		
			run_save_total_sel();

            #if defined(DELETE_VIDEO_ITEM)&&defined(SYBER_DVD)//liweihua add 20031218
            page=0;
            #endif

			setupLevel = 1;
			
	    #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
			if(one_key_pass_flag)
			{	
				page = ONEKEYPASSPAGE;
			}
		#endif
			ShowSetupPage(2);

//3-12-9 19:04 NONO MARKED.uopdate dsp code.
			//nono 2003-8-26 1:42 for DTS mute after setup_default
//			exe_setup_function(setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][1],
//			        setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][ SETUP_SPK_DOWNMIX ],0);//nono 2003-8-26 0:50

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
        ExitSetupPage(0);
#endif

		#ifdef IR_KEY_SET_VIDEO_MODE
		video_mode_val=VIDEO_MODE_VAL_DEFAULT;
		set_video_val(video_mode_val);
		//WriteToI2c(0xa0, 220,(BYTE *)&video_mode_val,1);
		#endif

            #ifdef VOLUME_RECODE
			{
				int volume;
				int i=0;
				#ifdef CNTR_5SPK_VOLUME//wangfeng 2003-11-11 21:27
				for (i=0; i<7; i++){
				#ifdef SW_VOL_63    
				if(i==6)
				{
				audio_volume = SUB_DEFAULT;       //set to max volume when we default gerry 2-11-6 9:26;
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME+6, (BYTE *)&audio_volume,sizeof(audio_volume));
				}else
				#endif
				{
				#endif    
				audio_volume = DEFAULT_VOL;
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME+i, (BYTE *)&audio_volume,sizeof(audio_volume));
				#ifdef CNTR_5SPK_VOLUME//wangfeng 2003-11-11 21:26
				}
				
				volume_5SPK[i]      = audio_volume;//VOL_VALUE; //set to maximum volume
                		if(i==0)
                		idVolume_5SPK[i]    = Volume_Font_ID;
                		else
                		idVolume_5SPK[i]    = VOL_FL_ID+i-1;
				//DSPReset();
			}
		
	            volume_Switch=0;

			    audio_volume = volume_5SPK[0] ;//wangfeng 2003-11-07 15:41
			    #endif//#else
			}
			    #ifndef CNTR_5SPK_VOLUME
			AUDIF_Set_Volume(audio_volume);//AudioSetVolume(audio_volume);
			    #endif
            #endif //#ifdef VOLUME_RECODE

            #ifdef Ti3001_OSD_UI_1    // jason 2-10-5 15:30
			    reset_amplifier_default_setup();
			    AUDIF_Set_Volume(audio_volume);//AudioSetVolume(audio_volume);
			    ti_set_volume(SET_ALL_VALUE); //ti_set_volume(SET_ALL_VALUE,TI_VOL_VALUE);
            #endif //#ifdef Ti3001_OSD_UI_1

			#if 0//ndef DOWNMIX_DEFAULT_OFF//nono 3-12-23 21:00 //def	TWO_CHANNEL_ONLY//wangfeng 2003-12-17 14:40
			if ((cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) //nono 2-11-9 9:19
				AudioSetOutputMode(0x09, 0); //Set Output mode(9:2 channel, surround effect)
			#endif
       
//3-12-23 21:02 NONO for dts-cd
		setup_SetDTSDOWNMIXConfig();
			//nono 2003-8-26 1:42 for DTS mute after setup_default
//			exe_setup_function(setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][1],
//			        setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][ SETUP_SPK_DOWNMIX ],0);//nono 2003-8-26 0:50

       

#ifndef SETUP_DONT_PAUSE    // alan, 3-8-5 17:47
#ifdef  SETUP_DEFAULT_DONT_PAUSE  
//terry,2003/12/12 04:16PM
//bbk ,empty
#else
			AUDIF_Set_Pause();//2004AUDDRV AudioSetPause(); //Jeff 20021017
#endif			
#endif
        } //if (id==STR_OS_DEFAULT_SETUP)
	}
	#ifdef SETUP_DONGLI459			//oujx for tonic auto down when press select
	if(setupLevel==0)
	{
		setup_func_down();
	}
	#endif
}

void ShowSetupPage(BYTE refresh)
{
	int     i;
	BYTE    fontColor, bgColor;
	BYTE    upDown;
	const char   *str;
	#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
	UINT16 line=SETUP_MAX_WIDTH*16;
	#else
	UINT16 line=SETUP_MAX_WIDTH*16-20;
	#endif

	reset_passwd_cnt();

	if (full_scrn&CUSTM)
	{ //set to CUSTM mode
		osd_init_setup();
		setupLevel = 1;
		
		#ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:11
		if(id==STR_OS_OSD)		
		    index_y = CUSTMOSDITEM;				
		else
		#endif        
		index_y = 2;
        
		index_y_start = 0;
	}

	if (refresh)
	{
		//draw main rect
		#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
		//to move the main rect down for 22 pixels
		osd_draw_rect(0, 0, line, 22, SSHEER);
		osd_draw_rect(0, 0+22, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), SBGCOLOR);//wangfeng 3-8-27 21:44	
                #elif defined(SETUP_COLOR_TYPE2)		
                osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), SBGCOLOR);				
		#else
		osd_draw_rect(0, 0, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), SBGCOLOR);

		if (p_scan==1)
		{
			//draw top horizontal line
			osd_DrawLine(12, SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
			//draw bottom horizontal line
			osd_DrawLine(10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 2);
	}
        else
        {
        	
			osd_DrawLine(12, SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);
			osd_DrawLine(10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
		}

		//draw left vertical line
		osd_DrawLine(10, SETUP_BUTTON_HEIGHT+20, 10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SWHITECOLOR, 1);
		//draw right vertical line
		osd_DrawLine((SETUP_MAX_WIDTH*16-12), SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-12), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
		//osd_DrawLine((SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+12, (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SWHITECOLOR, 1);
        #endif
        
		if (refresh==2)
		{
			#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)	//wangfeng 2003-08-29 17:28
			osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+10, SBARCOLOR);//张宇不会

			#endif
			#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
			//draw blue bar for main pages of the menu
			osd_draw_rect(0, 22, line, SETUP_BUTTON_HEIGHT+10, SBARCOLOR);//wangfeng 3-8-27 21:47	
			//draw black bar for the output of main page  
			osd_draw_rect(0, SETUP_BUTTON_HEIGHT+10+10+10+2, line, SETUP_BUTTON_HEIGHT-2, 0);//wangfeng 3-8-27 21:47
			//draw blue bar at the bottom of the menu
			osd_draw_rect(0, SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-SETUP_BUTTON_HEIGHT, line, SETUP_BUTTON_HEIGHT, SBARCOLOR);
                        #elif defined(SETUP_COLOR_TYPE2)
                        osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+12,13);	
            #ifndef SKYWORTH_DVD	//3-10-28 3:33张宇P
			osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/18, 13);//SBGCOLOR);
			#endif
			osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT+20, line+20, SETUP_BUTTON_HEIGHT+1, 0);//3-8-25 2:26张宇P
                        #else
			osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+10, 1);
			#endif
            
            //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
            #if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:10
			#if!defined(SETUP_COLOR_TYPE1)&&!defined(SETUP_COLOR_TYPE2)	//wangfeng 2003-08-29 17:28
			if(page==SysNextPage)
			osd_draw_rect((line*0)/6+10, 10, line/6, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
			else
#endif 
#endif 
//			#ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
                        #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
			osd_draw_rect((line*page)/6+10, 10, line/6, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
			
			for (i=0;i<6;i++)
			{
				if (p_scan==1)
					osd_DrawLine((line*i)/6+11, 10, (line*(i+1))/6+10, 10, SWHITECOLOR, 2);	// top
				else
				//wangfeng 3-8-27 21:50
					osd_DrawLine((line*i)/6+11, 10, (line*(i+1))/6+10, 10, SWHITECOLOR, 1);	// top
				osd_DrawLine((line*i)/6+11, 10, (line*i)/6+11, SETUP_BUTTON_HEIGHT+21, SWHITECOLOR, 1); // left
				osd_DrawLine((line*(i+1))/6+8, 10, (line*(i+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBLACKCOLOR, 1); // right
			}
            //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
            #if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:10
			if(page==SysNextPage)
			osd_DrawLine((line*0)/6+12, SETUP_BUTTON_HEIGHT+20, (line*(0+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBGCOLOR, 2);
			else
#endif 
            #endif//#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
            
#ifdef SETUP_COLOR_TYPE2
 osd_DrawLine((line*page)/6+12, SETUP_BUTTON_HEIGHT+20, line/6-25/*(line*(page+1))/6+8*/, 1, /*SBGCOLOR*/13, 13);
#elif defined(SETUP_COLOR_TYPE1)
printf("==========Delete this line!!");
#else
			osd_DrawLine((line*page)/6+12, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBGCOLOR, 2);
#endif
		}
    }
    else
    {
    	#ifdef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
     	//refresh the 5 rects
    	osd_draw_rect(0, 0+22+SETUP_BUTTON_HEIGHT+10+SETUP_BUTTON_HEIGHT-2, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-(22+SETUP_BUTTON_HEIGHT+10+SETUP_BUTTON_HEIGHT-2)-(SETUP_BUTTON_HEIGHT), SBGCOLOR);
       // osd_draw_rect(0, 0, line, 22, SSHEER);
		//osd_draw_rect(0, 22, line, SETUP_BUTTON_HEIGHT+10, SBARCOLOR);
        osd_draw_rect(0, SETUP_BUTTON_HEIGHT+10+10+10+2, line, SETUP_BUTTON_HEIGHT-2, 0);//wangfeng 3-8-27 21:47
	
		//osd_draw_rect(0, SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-SETUP_BUTTON_HEIGHT, line, SETUP_BUTTON_HEIGHT, SBARCOLOR);
#elif defined(SETUP_COLOR_TYPE2)    
        osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT+20, line+20, SETUP_BUTTON_HEIGHT+1, 0);//3-8-25 2:26张宇P
    	osd_draw_rect(20, SETUP_BUTTON_HEIGHT+24+40, (SETUP_MAX_WIDTH*15), 10*SETUP_BUTTON_HEIGHT-12, SBGCOLOR);
    
        #else
        osd_draw_rect(20, SETUP_BUTTON_HEIGHT+24, (SETUP_MAX_WIDTH*15), 10*SETUP_BUTTON_HEIGHT-12, SBGCOLOR);
        #endif
        
    }


	if (!(full_scrn&CUSTM)
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         

	&& (!one_key_pass_flag)//no draw ICON. zhaoyanhua add 03-11-7 10:17
#endif		
#ifdef	KARAOKE_MENU	
	&&(KARAOKE_MENU_FLAG==0)//WANGFENG 2003-10-29 18:06
#endif
        )
	{
//            int icon_y = (p_scan) ? 13 : 7;
#ifdef SETUP_COLOR_TYPE1 //|| defined(SETUP_COLOR_TYPE2)	//wangfeng 2003-08-29 17:28
            osd_DrawIcon(4, 26,0,page);
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:11
        if (page==SysNextPage)	osd_DrawIcon(4,26,0,0);
#endif
            osd_DrawIcon(16,26,1,page);
            osd_DrawIcon(27,26,2,page);
            osd_DrawIcon(38,26,3,page);
            osd_DrawIcon(50,26,4,page);
            osd_DrawIcon(61,26,5,page);
#else            
            osd_DrawIcon(4, 13,0,page);

#ifdef SETUP_ON_OPEN_VALID			//dingzhy for yili 12/26/2003 9:34PM

	//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
	#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:11
	    if (page==SysNextPage)	osd_DrawIcon(10,13,0,0);
	#endif
        osd_DrawIcon(23,13,1,page);
        osd_DrawIcon(43,13,2,page);
        osd_DrawIcon(62,13,3,page);
#else
        //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
        #if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:12
if (page==SysNextPage)	osd_DrawIcon(4,13,0,0);
#endif
            osd_DrawIcon(16,13,1,page);
            osd_DrawIcon(27,13,2,page);
            #ifndef SETUP_DONGLI459
            osd_DrawIcon(38,13,3,page);
            #endif
#endif	//end dingzhy

#ifndef NO_DIGIT_VIDEO_MENU
    #ifndef SETUP_DONGLI459
            osd_DrawIcon(50,13,4,page);
    #ifndef NO_AUDIO_PAGE//liweihua add for syber 2003-12-30 20:40
            osd_DrawIcon(61,13,5,page);
    #endif
    #else//#ifndef SETUP_DONGLI459
            osd_DrawIcon(38,13,3,page);//SPEAKER PAGE
            osd_DrawIcon(50,13,4,page);//DOBLY PAGE
    #endif//#ifndef SETUP_DONGLI459
#endif//NO_DIGIT_VIDEO_MENU
#endif//SETUP_COLOR_TYPE1
	}

	if (setupLevel == 0)
    {
    	BYTE    iItemType;
    	
    	show_main_title(setup_MainP[page][0]);
		//draw item strings in sub menu
		for (i=index_y_start; i<setupItemNum[1]; i++)
		{
			if ( (i-index_y_start+1) > (SETUP_MAX_LINE-3) ) break;

			iItemType=setup_item[page][i][0];
			if (iItemType == SET_SPACE) continue;
			if (iItemType == SET_NE) break;

			id = setup_item[page][i][1];

        	#ifdef BBK_NEW_SETUP    //fengjl edit 4-1-29 13:02
        	#if defined(BBK_DSS_555_DVD)||defined(BBK_DV911S)
        	if (id==STR_OS_RETURN_MAIN_SETUP)
        	    id=STR_OS_EXIT_MENU;
        	#endif
        	#else		
        	if (id==STR_OS_RETURN_MAIN_SETUP)	 // no main page, so this item changes to exit_setup_menu
        		id=STR_OS_EXIT_MENU;
        	#endif 

			str = _OsdMessegeFont1[osd_font_mode][id];
			
			bgColor = SBGCOLOR;
			upDown = 0;
			fontColor = SFONTCOLOR;
			
			osd_draw_setup_button(SETUP_MENU_XSTART, i-index_y_start+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, bgColor, upDown);
			osd_DrawString(SETUP_MENU_XSTART+1, i-index_y_start+SETUP_MENU_YSTART+1, str, fontColor, bgColor);			
		} //end of for each item
		// highlight : draw a frame to identify which tab is enable
	#if !defined(SETUP_COLOR_TYPE2) && !defined(SETUP_COLOR_TYPE1)
		SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
         #endif
    				#if!defined(SETUP_COLOR_TYPE1)&&!defined(SETUP_COLOR_TYPE2)//#ifndef	SETUP_COLOR_TYPE1	//wangfeng 2003-08-29 17:28
//#ifndef	SETUP_COLOR_TYPE1     
		setup_Showredframe(page);
		#endif
	} else
	{ //second(or third)-level page menu
		BYTE    iItemType;

		//find max items in this page
		for (i=0; i<MAX_PAGE_ITEM; i++)
		{
			iItemType=setup_item[page][i][0];
			if (iItemType == SET_SPACE) continue;
			if (iItemType == SET_NE) break;
		}
		setupItemNum[1] = i;

		//draw menu title
		if (full_scrn&CUSTM)
#ifdef BBK_NEW_CUSTM     //fengjl add 2004-03-27 10:58
{	
	BYTE    buf[15];

	psprintf(buf, "%s", VERSION_STRING1);
	osd_DrawString(SETUP_MENU_XSTART+1, SETUP_MENU_YSTART, buf, SFONTCOLOR, SBGCOLOR);
}
#else
			show_main_title(STR_OS_MENU);
#endif
//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:12
		else if (page==SysNextPage)
    #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP			//gerry for gbm,2004-3-12 13:12
        {
    		if(IsOSDChinese())
			show_main_title(setup_item[0][6][1]);
			else
			show_main_title(STR_OS_PREV_PAGE);
        }
    #else//NEXT_PAGE_SHOW_ADVANCED_SETUP
			show_main_title(setup_MainP[0][0]);
    #endif//NEXT_PAGE_SHOW_ADVANCED_SETUP
#endif 
        
#ifdef	KARAOKE_MENU
		else if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG))
		 	show_main_title(STR_OS_KARAOKE_SETUP);
#endif
		else
		#ifdef SETUP_ON_OPEN_VALID		//dingzhy for yili 12/26/2003 9:37PM
			#ifdef NO_DIGIT_VIDEO_MENU
		         if(page==3)
			show_main_title(setup_MainP[4][0]);
			else
			show_main_title(setup_MainP[page][0]);
		    #endif
		#else
			show_main_title(setup_MainP[page][0]);
		#endif


		//draw item strings in sub menu
		for (i=index_y_start; i<setupItemNum[1]; i++)
		{
			if ( (i-index_y_start+1) > (SETUP_MAX_LINE-3) ) break;

			iItemType=setup_item[page][i][0];
			if (iItemType == SET_SPACE) continue;
			if (iItemType == SET_NE) break;

			id = setup_item[page][i][1];
#ifdef ONLY_DOWNMIX_IN_SPEAKER_PAGE//liweihua add 2004-1-2 15:05
            if(page == MULTISPKPAGE)
            {
                if((i>0) && (id!=STR_OS_RETURN_MAIN_SETUP)) 
                    continue;  
            }
#endif
	        /*
	#ifndef  BBK_NEW_SETUP//zhaoyanhua add 2003-11-18 17:14
			if (id==STR_OS_RETURN_MAIN_SETUP)  // no main page, so this item changes to exit_setup_menu
				id=STR_OS_EXIT_MENU;
			#endif
            */
            
        	#ifdef BBK_NEW_SETUP    //fengjl edit 4-1-29 13:02
        	#if defined(BBK_DSS_555_DVD)||defined(BBK_DV911S)
        	if (id==STR_OS_RETURN_MAIN_SETUP)
        	    id=STR_OS_EXIT_MENU;
        	#endif
        	#else		
        	if (id==STR_OS_RETURN_MAIN_SETUP)	 // no main page, so this item changes to exit_setup_menu
        		id=STR_OS_EXIT_MENU;
        	#endif 

			str = _OsdMessegeFont1[osd_font_mode][id];
			if ( (index_y+index_y_start) == i)
			{
				#ifdef SETUP_COLOR_TYPE1
				if (setupLevel)
				#else
				if (setupLevel==1)
				#endif
				{
                     fontColor = SANTIFONTCOLOR;
				} else
				{
                     fontColor = SFONTCOLOR;
				}
				bgColor = SANTIBGCOLOR;
				upDown = 1;
			}else
			{
				bgColor = SBGCOLOR;
				upDown = 0;

    #if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)||defined(SET_FCR_SPEAKER)//xulf 2004-01-07                                           
                //special case////nonotest 2003-9-5 17:44
                if ( (page==MULTISPKPAGE) && (SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF) &&
                            ( (i>=SPKSTART) && (i<=SPKEND) ))
                {
                    fontColor = SGRAYCOLOR;
                } else
#endif//    #if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)                        
                
    #ifdef PROLOGICII_3D_MUTEX//nono 4-2-12 0:58
    	
    if ((page==AUDPAGE) && is_EQ_SOUND_set()&&(i==PROLOGIC_II))
    //if (i==PROLOGIC_II)
    {
          fontColor = SGRAYCOLOR;
    }else
    
    #endif//PROLOGICII_3D_MUTEX
                
	#ifdef PROLOGIC_ON_51CH                            
                 if ((page==AUDPAGE)&&(KARAOKE_MENU_FLAG==0)
                    && !setup_IsSpkDownmixOff()&&(i==1))
                {
                    fontColor = SGRAYCOLOR;
                } else
	#endif              
                
        #ifndef SETUP_ALL_VALID
                if ( (page==AUDPAGE) &&
                            (
							((SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) &&
							( coding_mode_now&(AUDIF_CODING_MODE_AC3|
							AUDIF_CODING_MODE_DTS|
							AUDIF_CODING_MODE_DTSCD)
							)
							)
							||(coding_mode_now==AUDIF_CODING_MODE_LPCM)//terry,0512,currently ,we are not surport LPCM key shift
                            ) &&
                            (i==(KEYITEM) )
							)
                {
                        #ifdef SETUP_COLOR_TYPE2
                                   fontColor = SGRAYCOLOR;
                        #elif defined(SETUP_COLOR_TYPE1)
                        	fontColor = SGRAYCOLOR;
                           #else                	
                    //wanghaoying 2003-11-26 20:05 changed               	
                    //fontColor = SFONTCOLOR;
                    fontColor = SGRAYCOLOR;
                           #endif
                }
				else if ( (page==AUDPAGE) &&
                            (SETUP_SPDIF==SPDIFBITSTREAM) &&
                            ( ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
							AUDIF_CODING_MODE_DTS|
							//AUDIF_CODING_MODE_PCM|   //DTSCD-BITSTREAM MODE, Jeff 20020719
							AUDIF_CODING_MODE_DTSCD)
                            )||(cd_subtype==CD_DTS) )&&      //NONO 2-7-25 17:26
                            ( (i>=VOLCTRLSTART) && (i<=VOLCTRLEND) )
							)
				{
					//fontColor = SGRAYCOLOR;
#ifdef SETUP_COLOR_TYPE2
fontColor = SGRAYCOLOR;		
#elif defined(SETUP_COLOR_TYPE1)
fontColor = SGRAYCOLOR;		
#else					
                    //wanghaoying 2003-11-26 20:05 changed
                    //fontColor = SFONTCOLOR;
                    fontColor = SGRAYCOLOR;
#endif
                #ifndef NO_AC3_DYNAMIC_RANGE
				} else if ( (page==AC3DIGITALPAGE) && //Jeff 20020621
                            (i==AC3DYNAMICITEM1) &&
                            ( (SETUP_AC3DIGITAL_OUTMODE!=AC3DYNAMICITEM2) 
//                            ||(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)
                            )
							)
				{
					fontColor = SFONTCOLOR;
//					fontColor = SGRAYCOLOR;
                #endif //NO_AC3_DYNAMIC_RANGE
				} else
            #endif //SETUP_ALL_VALID
				{
					fontColor = SFONTCOLOR;
				}
				}
				if (!refresh)
				{
					bgColor=SBGCOLOR;
					upDown=0;
					//marked by wangfeng 2003-09-01 19:42
					if (i==index_y_start) 
					fontColor=SFONTCOLOR;
				}
            #ifdef KARAOKE_MENU	//wangfeng 2003-10-30 10:19
			if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG)&&((i<2)||(i>5)))//((i<1)||(i>4)))
			{
				fontColor = SBGCOLOR;
				
			}
			//wangfeng 2003-11-11 14:06
			else if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG==0)&&((i>=2)&&(i<=5)))
			{
			    fontColor = SBGCOLOR;
			}
			else
			#endif
				osd_draw_setup_button(SETUP_MENU_XSTART, i-index_y_start+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, bgColor, upDown);
				osd_DrawString(SETUP_MENU_XSTART+1, i-index_y_start+SETUP_MENU_YSTART+1, str, fontColor, bgColor);
			#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 19:26			
				if((page == VIDEOPAGE) &&(setup_item[page][i][0] == SET_SCALE))//not draw "EXIT" item,
				{	
					setup_VideoItemValue(i,SFONTCOLOR,SBGCOLOR );//show value with HL color.			
				}
			#endif//VIDEO_SETUP_NEW_GUI
			} //end of for each item

			//some special system information shown in selection area
			if (full_scrn&CUSTM)
			{
				#if 0
				BYTE    buf[40];
				BYTE    *pVersion;
				extern const UINT8 ServoVersion[];

				pVersion = (BYTE *)(ROM_BASE_UNCACHED);

				//show ROM code checksum
				buf[0]= '[';
				for (i=0x40; i<0x44; i++)
				{
					BYTE    ch[3];
					psprintf(ch,"%02x",*(pVersion+i));
					buf[2*i-126]=ch[1];
					buf[2*i-127]=ch[0];
				}

				buf[9]= ']';
				buf[10]= 0;
				osd_DrawString(SETUP_SUB_XSTART+6, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);

				//ServoVersion[16]=0; can't write to const data
				osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART, ServoVersion, SFONTCOLOR, SBGCOLOR);
				//show some "codes" strings
				for (i=0x50; i<0x58; i++) { //Extend version string length to 8 Bytes, Jeff 20020715
					buf[i-0x50] = *(pVersion+i);
				}

				buf[8]= 0; //Extend version string length to 8 Bytes, Jeff 20020715
				osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
				//add build version, Jeff 20021008
				psprintf(buf, "%s", VERSION_STRING);
				osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
				psprintf(buf, "%c SUM:", regs0->stamp+'A');
				osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);
				#endif
				
				ShowCUSTMMsg();
			
			#ifdef SUPER_DEFAULT_OSD_LANG       //freyman add 2004-2-11 9:11
			id = setup_item[page][index_y][1];			
			if(id==STR_OS_OSD)
			    index_y = CUSTMOSDITEM;
			else
			#endif
				index_y = 2;
			}

			if (refresh)
			{
				draw_3rd_menu();
			}
			return;

			//draw ">" between sub-mean and it's corresponding selection area
		//#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
		#if defined(NEXTPAGE_SYS)		//freyman 2004-3-26 0:13
			if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
			#endif 							
			osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
			//show first selection menu of third-level menu
#ifdef  Ti3001_OSD_UI_2
			if(page!=5&&page!=6)
			{
				for (i=2; i<MAX_ITEM_SEL; i++)
				{
					//get select item
					sel = setup_sel[page][index_y+index_y_start];

					id = setup_item[page][index_y+index_y_start][i];
					if (id==0) break;

					str = setup_SetItemString();
					if (sel == i) {
						fontColor = SFONTCOLOR;
						bgColor = SANTIBGCOLOR;
						upDown = 1;
					} else {
						fontColor = SFONTCOLOR;
						bgColor = SBGCOLOR;
						upDown = 0;
					}
					//special item(PASSWORD), page-0, item-4
					if (setup_item[page][index_y+index_y_start][0]==SET_NM) {
						if (UserSet.parental_ststus==C_LOCK) {
							setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL;
							str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
						} else {
							setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL + 1;
							str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
						}
						osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart), SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
						osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart), str, SANTIFONTCOLOR, SANTIBGCOLOR);
					} else {
						osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+index_y)+SETUP_MENU_YSTART, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, bgColor, upDown);
						osd_DrawString(SETUP_SUB_XSTART+1, (i-2+index_y)+SETUP_MENU_YSTART, str, fontColor, bgColor);
					}
				}
				setupItemNum[2] = i-2;
			}
			else
			{
				for (i=1; i<MAX_ITEM_SEL; i++)
				{


					//get select item
					sel = setup_sel[page][index_y+index_y_start];

					id = setup_item[page][index_y+index_y_start][i];
					if (id==0) break;

					str = setup_SetItemString();

					if (sel == i)
					{
						fontColor = SFONTCOLOR;
						bgColor = SANTIBGCOLOR;
						//bgColor = SBGCOLOR;
						upDown = 1;
					} else
					{
						fontColor = SFONTCOLOR;
						bgColor = SBGCOLOR;
						upDown = 0;
					}
					if (setup_item[page][index_y+index_y_start][0]==SET_SCALE)
					{
						setup_PrepareScaleItem(id,upDown);
					}
				}
				setupItemNum[2] = i-2;
			}
#else
			for (i=2; i<MAX_ITEM_SEL; i++)
			{
				//get select item
                       #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
				if(one_key_pass_flag)
				{
					sel = GetOneKeyPageSel(index_y);
					printf("+++++++++++++ 111111111sel = %d,index_y = %d--\n");
				}
				else
				sel = setup_sel[page][index_y+index_y_start];
			#else
				sel = setup_sel[page][index_y+index_y_start];
			#endif	
				id = setup_item[page][index_y+index_y_start][i];
				if (id==0) break;

				str = setup_SetItemString();
				if (sel == i)
				{
					fontColor = SFONTCOLOR;
					bgColor = SANTIBGCOLOR;
					upDown = 1;
				}
				else
				{
					fontColor = SFONTCOLOR;
					bgColor = SBGCOLOR;
					upDown = 0;
				}
				//special item(PASSWORD), page-0, item-4
				if (setup_item[page][index_y+index_y_start][0]==SET_NM)
				{
					if (UserSet.parental_ststus==C_LOCK)
					{
                        setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL;
                        str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
					} else
					{
                        setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL + 1;
                        str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
					}
					osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart), SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
					osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart), str, SANTIFONTCOLOR, SANTIBGCOLOR);
				}
				else
				{
					osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+index_y)+SETUP_MENU_YSTART, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, bgColor, upDown);
					osd_DrawString(SETUP_SUB_XSTART+1, (i-2+index_y)+SETUP_MENU_YSTART, str, fontColor, bgColor);
				}
			}

			setupItemNum[2] = i-2;
#endif
    }

}






/*
** FUNC: to rewrite the infomation in CUSM when Rating_8.
**
**  zhaoyanhua 
**  Date: 3-7-25 17:55 
*/
void ShowCUSTMMsg(void)
{
	BYTE    buf[40];
	BYTE    *pVersion;
#ifdef DVD_SERVO
	extern const UINT8 ServoVersion[];
#endif
	int i=0;

	pVersion = (BYTE *)(ROM_BASE_UNCACHED);

	//show ROM code checksum
	buf[0]= '[';
	for (i=0x40; i<0x44; i++)
	{
		BYTE    ch[3];
		psprintf(ch,"%02x",*(pVersion+i));			
		buf[2*i-126]=ch[1];
		buf[2*i-127]=ch[0];
	}

	buf[9]= ']';
	buf[10]= 0;

#ifdef  SETUP_COLOR_TYPE2
	printf("use showcustmmesg\n");
	osd_DrawString(SETUP_SUB_XSTART+6, SETUP_MENU_YSTART+2, buf,/* SFONTCOLOR*/7, SBGCOLOR);
#else	
	osd_DrawString(SETUP_SUB_XSTART+6, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);
#endif

#ifdef DVD_SERVO
	//ServoVersion[16]=0; can't write to const data
	osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART, ServoVersion, SFONTCOLOR, SBGCOLOR);
#endif
	//show some "codes" strings
	for (i=0x50; i<0x58; i++) { //Extend version string length to 8 Bytes, Jeff 20020715
		buf[i-0x50] = *(pVersion+i);
	}

	buf[8]= 0; //Extend version string length to 8 Bytes, Jeff 20020715
	osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
	//add build version, Jeff 20021008
	psprintf(buf, "%s", VERSION_STRING);
	osd_DrawString(SETUP_SUB_XSTART+8, SETUP_MENU_YSTART+1, buf, SFONTCOLOR, SBGCOLOR);
	psprintf(buf, "%c SUM:", regs0->stamp+'A');
	osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);
}





extern void wait_v_blank(void); // in vpp+dvd.c
extern BYTE rem_osd_id;//nono 2-7-15 21:34

#ifdef SUPPORT_OSDID3//suqiaoli add 2004-3-26 
extern void osd_init_OSDID3(void);
extern void show_id3(void);
#endif

void ExitSetupPage(BYTE save) //jhuang 2001/5/18 10:30PM
{
    int play=0;
    //save==1 save and exit setup menu
    //save==-1 NOT save and exit setup menu

    //In CUSTM page, we set UserSet.parental_ststus=C_UNLOCK, so we resync UserSet.parental_ststus here
    //if (setup_sel[0][1] == (MIN_ITEM_SEL+1) ) {
    if (SETUP_PASSWORD == (MIN_ITEM_SEL+1) ) {
        UserSet.parental_ststus=C_UNLOCK;
    } else {
        UserSet.parental_ststus=C_LOCK;
        SETUP_PASSWORD=MIN_ITEM_SEL;
    }

#ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 9:58
		//if in PASSWORD GUI state,must set it to NO_GUI_STATE
		passwdGUI_state = NO_GUI_STATE;
#endif	
    safe_srn_forceOFF();
    safe_srn_off();
    osd_disable();

//#ifndef QISHENG_DVD // alan marked, 3-8-9 0:10
    if( (old_play_state==VCD_STATE_NORMAL)&&(play_state==VCD_STATE_PAUSE) )
        play|=0x01;
//#endif

    if(NP_P_CFG_for_Video != UserSet.P_V_CFG)
    {
        if(cd_type_loaded==CDDVD)
        {
            set_video_aspect();
            play|=is_aspect_menu();
        }
    }

    if(save==1) {
        setup_save_exit();//run_save_cmd();
    }

    #ifdef SDRAM_16Mb_Mode
        if (prog_state==2)
        {
            #include "memmap0.h"

            regs0->osd_base_addr=GetOSDBackUpAddress();
            osd_init();

//nono 20031202
	        full_scrn=0;

            ClearOsdMsg(0);
            psprintf(RegionValStr[REGION1], "");
            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
	
            if ((cd_type_loaded == CDROM) && (pFsJpeg->gifsFuncBtn == 2))
            {
                prog_state=255;
                ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);
            } else {
                prog_state=0;
                ircmd_resume();
            }

//            full_scrn=0;

//            ClearOsdMsg(0);
//            psprintf(RegionValStr[REGION1], "");
//            PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
            return;
        }
    #endif

    //Terry,2002/4/29 01:16AM
    //Note: Don't revise the seq. .
    full_scrn=0;
    //terry,2002/5/10 02:52と
    //move to osd1.c
    //ClearOsdMsg(0);
    //wait_v_blank();

    #ifdef SDRAM_16Mb_Mode
        regs0->osd_base_addr=GetOSDBackUpAddress();
    #endif

#ifdef CD_PLAYER        //liweihua add 2003-9-11
    if(cd_type_loaded == CDDA)
        osd_init_cdplayer();
    else
        osd_init();
#else		
	#ifdef DYNAMIC_SPECTRUM    //fengjl  3-10-21 21:33
  	if (band_onoff)  		
  	{	
	#ifdef LPCM_NO_SHOW_BAND  //fengjl edit 2004-03-19 18:51  
  		if(coding_mode_now!=AUDIF_CODING_MODE_LPCM)  
  	#endif
  		bEqDisplay=1;
  		Show3dspectrum();
	}
  	else
  	#endif 
    osd_init();
#endif

#ifdef SHOW_STANDBY_TIMER
		reset_standby_timer_pos();//suqiaoli  add 2003-8-5
#endif

    if(play&0x01)
    {   
#ifdef JPEG_PAUSE_WHEN_SETUP//zhaoyanhua add 2003-12-2 16:30
        if(Is_JPEG_SlideMode())
            play_state = VCD_STATE_NORMAL;      
#endif
        ircmd_play();
    }
    else
    {
    #ifdef MP3_STOP_IN_GUI_START//zhaoyanhua add 03-10-14 11:39 keep inital state for MP3
		if((Is_MP3_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
		{
			play_state = old_play_state;
			return ;
		}
		else
    #elif defined(MP4_GUI_FF_INVALID)  //wsf 2004-9-15 20:22
        if((Is_OTHER_STATE()) && (old_play_state == VCD_STATE_MP3_FILELIST))
        {
            play_state = old_play_state;
            return ;
        }
        else
	#endif
        if ((play_state!=VCD_STATE_STOP)&&(play_state!=VCD_STATE_IDLE))
            PrintOsdMsg(rem_osd_id,REGION1,1,0);//show "PAUSE" & "STEP"...after "setup" 2-7-15 21:44

//I think it will not excute correctly.
            //zhaoyanhua add 2003-12-10 12:17
            //PrintOsdMsg(rem_osd_id,REGION1,0,0);//PrintOsdMsg(rem_osd_id,REGION1,1,0);//show "PAUSE" & "STEP"...after "setup" 2-7-15 21:44
           //if(old_play_state == VCD_STATE_PAUSE)//zhaoyanhua add 2003-12-10 13:26
           //     PrintOsdMsg(STR_OS_PAUSE,REGION1,0,0); 

    }
    #ifdef SUPPORT_OSDID3//liweihua add 2004-1-9 10:21
        if(Is_MP3_STATE() && (play_state != VCD_STATE_STOP))
        {
            osd_init_OSDID3();
            show_id3();
        }
    #endif 
    if(play&0x02) {
        rep_run_the_menu();
    }

   
    
    #ifdef USER_MPEG_LOGO
    if (
           (need_show_logo==1) &&
           (
               (play_state==VCD_STATE_STOP) || (play_state==VCD_STATE_OPEN) || (system_state==SYSTEM_NODISC)
           )
       )	// alan, 2003/9/8 06:02と
    {
    	ShowTitle();
    	need_show_logo=0;
    }
    #endif//#ifdef USER_MPEG_LOGO
    
    #ifdef ALWAYS_DISPLAY_OPEN                   //fengjl  add 3-12-1 20:20
    
    
	#ifdef SETUP_ON_OPEN_VALID			//dingzhy 12/26/2003 9:05PM
	extern BYTE OpenFlag;
    if ((system_state==SYSTEM_OPEN)&&(OpenFlag == 1))
    {
    PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);//1
	}
///	
	else
	if((play_state !=VCD_STATE_NORMAL)&&(!Is_JPEG_STATE())&&(dvd_error==0)
	&&(play_state != VCD_STATE_FASTFORWARD)&&(play_state !=  VCD_STATE_FASTBACKWARD)&&(play_state != VCD_STATE_STOP))
    {
    PrintOsdMsg(STR_OS_READ,REGION1,0,0);//1
    }
///
	#else
    if (system_state==SYSTEM_OPEN)
    PrintOsdMsg(STR_OS_OPEN,REGION1,0,0);
    #endif
    
#endif
    
    #ifdef ALWAYS_DISPLAY_NODISK
    if (system_state==SYSTEM_NODISC)
    PrintOsdMsg(STR_OS_NODISC,REGION1,0,0);
    #endif
        
#ifdef SETUP_DONGLI459
UserSet.parental_ststus=C_LOCK;
#endif
      
}



