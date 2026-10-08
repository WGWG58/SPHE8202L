#ifdef SELECT_MEDIA_IN_SETUPMENU //Maoyong 2004-8-9 21:42
BYTE IsMediaItemUpValid(void)
{
    BYTE iRes = 0;
    if(index_y2 == CARD_ITEM){
        if(!IsNoPluggedUSB() )
            iRes = 1;
    }

    return iRes;
}
void up_skip_media_sub_item(void)
{
    if(index_y2 == CARD_ITEM)  {
        if( IsNoPluggedUSB() ){
            index_y2 -= 2;
            return;
        }
    }
    index_y2 --;
}
#endif //#ifdef SELECT_MEDIA_IN_SETUPMENU


void setup_func_up(void)
{
    BYTE    upperbound;
    const char *str;
    int     i;
    
    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS)
    {
      #ifdef DEBUG_FUNCTION_MENU
      printf("up key press, setupLevel:%d,index_y:%d index_y2:%d\n",setupLevel,index_y,index_y2);
      #endif
      
      if(setupLevel==1) 
      {//in the first level menu page  
        
        #ifdef DEBUG_FUNCTION_MENU
        printf("---up in the first menu,index_y2:%d\n",index_y2);
        #endif
        #ifdef SUPPORT_DISPLAY_MENU
        if(In_Display_Menu())
          setup_menu_plus_timer = DISPLAY_MENU_SHOW_TIME;
        else
        #endif//end #ifdef SUPPORT_DISPLAY_MENU
        setup_menu_plus_timer = MENU_PLUS_SHOW_TIME;
        
        #ifdef SUPPORT_DISPLAY_MENU
        if(In_Goto_Menu())
        {
          #ifdef DEBUG_DISPLAY_MENU
          printf("up...ir:%d.....\n",ir_select_number);
          #endif
          
          if(index_x != 6)
          {
            if(index_x>=10)
            {
            	if((index_x == 10) && (ir_select_number<6))
            	  ir_select_number++;
            	else if(ir_select_number < 9)
            	{
            	  if(((goto_time%100)/10) != 6)
            	    ir_select_number++;
            	}
            	
            } 
            else if(ir_select_number < 9)
              ir_select_number++;
            
          }
          
          search_func_input();
          printf(" after ser ir:%d...........\n",ir_select_number);
          ShowSetupPage_plus(MENU_REFRESH); 
          #ifdef DEBUG_DISPLAY_MENU
          printf("up...index_x:%d goto_time:%d ir:%d.....\n",index_x,goto_time,ir_select_number);
          #endif
          return;
        }
        #endif//end #ifdef SUPPORT_DISPLAY_MENU
            
        if(index_y < MAX_PAGE_ITEM_PLUS) 
        {
            //clear the 2nd level menu
            down_osd_clear_3th_menu();
            
            //调整内容的上升
            {
              if(index_y == 0)
               #ifdef SUPPORT_DISPLAY_MENU
               if(In_Display_Menu())
                 index_y = MAX_PAGE_ITEM_PLUS-2;
               else
               #endif
                index_y = 4;
              else       
                index_y --;
        
              //we must skip the invalid item! 
              #ifdef SUPPORT_DISPLAY_MENU
              if(In_Display_Menu())
              {
                if(display_item_invalid[index_y] == ITEM_INVALID_FLAG)
                {
                  for(;display_item_invalid[index_y]==ITEM_INVALID_FLAG;index_y--)
                    ;           
                }
              }
              #endif  
              
              //将菜单项目反显
               id = setup_item_plus[page][index_y][1]; 
               setup_DrawItem(1, index_y+SETUP_MENU_YSTART_PLUS, 1);
             }
             
            #if 0 
            if(index_y < MAX_PAGE_ITEM_PLUS) 
            {
                if((index_y != 0) && (index_y != 4))
                 down_draw_action_item();
                
            }     
            #endif     
         }
      }
      else if(setupLevel == 2)
      {//in the 2th level menu page
         #ifdef DEBUG_FUNCTION_MENU
         printf("---up in the 2th menu,index_y2:%d\n",index_y2);
         #endif
         
         /*
         if (setup_item_plus[page][index_y][0]==SET_SCALE) 
         {
            //亮度加1且将其显示出来
            setup_CookScaleItem(id, 1);
            //记忆？
            //run_save_sel_cmd(page,index_y);
         }
         else 
         */
         if(setup_item_plus[page][index_y][0] == SET_FUNC)
         {
           setup_menu_plus_timer = MENU_PLUS_SHOW_TIME;
           
           if (index_y2 > 0) 
         {
            sel = setup_sel_plus[page][index_y];
        
            id = setup_item_plus[page][index_y][index_y2+2];
            str = setup_SetItemString();

            if ((index_y2+2) == sel) 
            {
                //keep upper button to UP mode with SANTIBGCOLOR
                #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39 
                osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SBGCOLOR, 1);
                #endif
                osd_DrawString(SETUP_SUB_XSTART_PLUS+1, index_y2+submenuStart, str, SDEFAULTCOLOR, SBGCOLOR);
            }
            else 
            {
                //normal UP button
                #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39 
                osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SBGCOLOR, 0);
                #endif
                osd_DrawString(SETUP_SUB_XSTART_PLUS+1, index_y2+submenuStart, str, SFONTCOLOR, SBGCOLOR);
            }

            index_y2--;

            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
            if ((index_y2+2) == sel) 
            {
                osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SANTIBGCOLOR, 1);
            } 
            else 
            {
                osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SANTIBGCOLOR, 0);
            }
            #endif

            id = setup_item_plus[page][index_y][index_y2+2];
            str = setup_SetItemString();
            osd_DrawString(SETUP_SUB_XSTART_PLUS+1, index_y2+submenuStart, str, SANTIFONTCOLOR, SANTIBGCOLOR);
         }
       }
    }
    }
    else
    {
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
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
    
    
    #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
//    UINT16 line=SETUP_MAX_WIDTH*16;   
    SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
         #elif defined(SETUP_COLOR_TYPE2)   
        //SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
        SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
//    UINT16 line=SETUP_MAX_WIDTH*16-20;
    #else
//    UINT16 line=SETUP_MAX_WIDTH*16-20;    
         #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:38    
         SetOsdCol(mn_osd_col2);   //2004-4-17 01:45张宇P
         #endif
    #endif

    reset_passwd_cnt();


    if (full_scrn&CUSTM) {
#ifdef CUSTM_MENU_REVISE
	upperbound = REGION_REMOVE -1; //WSLEE for customer menu region remove 20050526
#else           
        upperbound = 2;
#endif 
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
//      #ifndef SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
        #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-5 10:04//zhangyu
#ifndef DVB_MENU_SETUP_STYLE
        setup_Showredframe(page);
#else
        setup_Showredframe(dvbpage);
#endif
        #endif
        
        id = setup_item[page][index_y+index_y_start][1];
#ifdef OP_CUST_UI// libing 2005-5-8 16:30
        if (id==STR_OS_RETURN_MAIN_SETUP)    
        id=STR_OS_EXIT_MENU;
#endif
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
#ifdef  VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 10:41
                if(page == VIDEOPAGE)
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,(index_y +SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT+30,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,SETUP_BUTTON_HEIGHT,SBGCOLOR);    
                else
#endif//VIDEO_SETUP_NEW_GUI         
                #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
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
                 #ifdef HANYANG_SETUPMENU //2004-6-24 05:10?宇P
                    if(page==3)
                osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                               SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
                               (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-90,
                               SBGCOLOR);
                     else
                #endif
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
                #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
                SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
                                #elif defined(SETUP_COLOR_TYPE2)
                                SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
                #else
            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:38
                SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
                #endif
            #endif
            /*  osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SANTIBGCOLOR,1);
                osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SANTIBGCOLOR,1);
                osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SANTIBGCOLOR,1);
                osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SANTIBGCOLOR,1);*/
                //#ifndef   SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
            #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-5 10:04
#ifndef DVB_MENU_SETUP_STYLE
        setup_Showredframe(page);
#else
        setup_Showredframe(dvbpage);
#endif
                #endif
                #ifdef SHOW_SETUPMENU_SETUP
                show_setupmenu();
        #endif //end SHOW_SETUPMENU_SETUP
            } else
            if ( (index_y+index_y_start) > upperbound) {
                if (full_scrn&CUSTM) {
                	
#ifdef CUSTM_MENU_REVISE //WSLEE for clean 3-th level menu 20050526 PM 11:00    	
        osd_draw_rect((SETUP_SUB_XSTART-1)*16,(SETUP_MENU_YSTART+4)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART-4)*SETUP_BUTTON_HEIGHT,SBGCOLOR);
#else 
        osd_draw_rect((SETUP_SUB_XSTART-1)*16,(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART-3)*SETUP_BUTTON_HEIGHT,SBGCOLOR);
                if ((index_y+index_y_start) == (upperbound+1)) 
                	osd_draw_rect(16*16,6*SETUP_BUTTON_HEIGHT,2*16,1*SETUP_BUTTON_HEIGHT,SBGCOLOR);
#endif                  	
                    //clear third-level menu
#ifdef  RATING_8
                    if (index_y == 3) 
                    {
                  //  #ifndef   SETUP_COLOR_TYPE1   //zhangyu mark wangfeng 2003-08-29 17:28
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
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART)*16+16, (SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT-68,SBGCOLOR);                    
                    #elif defined(SETUP_COLOR_TYPE1)
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,SETUP_MENU_YSTART+32,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART)*16+60,(SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT,SBGCOLOR); 
                    #else
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT,SBGCOLOR);
                    #endif
                    if((8-N_OSD_LANGS)<=1)
                        ShowCUSTMMsg();
                }
                #endif  //SUPER_DEFAULT_OSD_LANG
                    //wanghaoying mark 2003-10-24 16:16
                    //this rectangle delete the bottom horizontal line
                    {
                     /* osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                        (SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,
                        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
                        SBGCOLOR);
                     */
                         #ifdef SPE_SETUP    //2004-5-10 10:53 linrc add for SPE_SETUP  
                                 //if not use this rectangle,it can't reflesh the setup menu 
                          osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                         (SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,
                         (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                         (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
                         SBGCOLOR);         
                         #endif   //end SPE_SETUP
                    }
                    //wanghaoying add 2004-6-8 22:15 to clear the >> icon
                    #ifdef OP_CUST_UI// libing 2005-5-8 16:30
                    if(index_y>0)
                    #else
                    if(index_y==CUSTMPASSWDITEM)
                    #endif
                        osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                             (SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,
                             (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                             (SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
                             SBGCOLOR);
                             
                    id = setup_item[page][index_y][1];
			#ifdef OP_CUST_UI// libing 2005-5-8 16:30
        			if (id==STR_OS_RETURN_MAIN_SETUP)
        			id=STR_OS_EXIT_MENU;
			#endif
                    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

#ifdef EASTECH_NEW_SETUP_MENU
					osd_draw_rect(mn_r_pm5);  // add by TOM  20040520
#endif
                    index_y--;

                    id = setup_item[page][index_y][1];
                    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);
                    //draw ">>" between sub-mean and it's corresponding selection area
                #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
 
                if((id != STR_OS_)&&(!(one_key_pass_flag)))
                #else
                //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
                #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:04
                    if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
                #endif//SAME_DISC_RESUME
                #endif//end BBK'S NEW_SETUP                             

                #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:12
                osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SANTIFONTCOLOR, SBGCOLOR);
                #else
                osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
                #endif
                    submenuStart = index_y+SETUP_MENU_YSTART;

                    if (setup_item[page][index_y][0]==SET_NM) {
                        char buf[8];
                    
                    #ifdef SETUP_6_DIGIT_PASSWORD //zhaoyanhua add 03-10-14 14:53
                    psprintf(buf, "%06d", UserSet.parent_passwd);
                    #else //4 digit password 
                        psprintf(buf, "%04d", UserSet.parent_passwd);
                    #endif   //end SETUP_6_DIGIT_PASSWORD
                    
                    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
                        osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                    #endif
                        
                        osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, SDEFAULTCOLOR,SBGCOLOR);

                    } else {
                        //get select item
                        sel = setup_sel[page][index_y];
#ifdef RATING_8
                    if((page == CUSTMPAGEINDEX) && (index_y == 3))
                    {
                            submenuStart = SETUP_MENU_YSTART;
                        }
                    else
#endif
#ifdef SUPER_DEFAULT_OSD_LANG
                    if(index_y==CUSTMOSDITEM)
                    {
                        if((8-N_OSD_LANGS)>=4)
                            submenuStart = index_y + SETUP_MENU_YSTART;
                        else
                            submenuStart = SETUP_MENU_YSTART + (8-N_OSD_LANGS) + 1;
                    }else
#endif
                    submenuStart = index_y+SETUP_MENU_YSTART;

                        //draw third-level menu
                        for (i=2; i<MAX_ITEM_SEL; i++) {
                            id = setup_item[page][index_y][i];
                            if (id==0) break;
                            #ifdef SPE_SETUP    //2004-5-10 9:49 linrc add for when show the CUSTMOSD,the "]"not clear. 
                            ShowSel(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART,sel == i);
                            #else
                            ShowSel(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,sel == i);
                            #endif
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
                    #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                        SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+30,
                        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-65,
                        SBGCOLOR);
#elif defined(SETUP_COLOR_TYPE2)
						#ifdef ADD_DVI311_SETUP
						osd_draw_rect((SETUP_SUB_XSTART-1)*16,
								SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
								(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
								(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-60,
								SBGCOLOR);//Modifed by ChenZhao on 2004-9-23 14:35	-68 >> -60 to clear a big scale in hddvd menu
						#else
						osd_draw_rect((SETUP_SUB_XSTART-1)*16,
								SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
								(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
								(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-68,
								SBGCOLOR);
						#endif //ADD_DVI311_SETUP
                    #else
                    #ifdef HANYANG_SETUPMENU   //2004-6-24 05:10?宇P
                    if(page==3)
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                        SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
                        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-93,
                        SBGCOLOR);
                        else
                        
                     #endif
                     osd_draw_rect((SETUP_SUB_XSTART-1)*16,
                        SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,
                        (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
                        (SETUP_MAX_LINE-SETUP_MENU_YSTART-1)*SETUP_BUTTON_HEIGHT,
                        SBGCOLOR);
                        
                        
                #endif

#if !defined( SETUP_COLOR_TYPE2)&& !defined(SETUP_COLOR_TYPE1)
                    if (p_scan==1)
                    {   printf("---------no draw line----------\n");
                        #ifndef SPE_SETUP
                        osd_DrawLine(250, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 2);
                        #endif                  
                    }
                    else
                    {
                        printf("---------no draw line----------\n");
                        #ifndef SPE_SETUP
                        osd_DrawLine(250, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
                    #endif  
                    }
                    #endif 
                    
                    
                    #ifdef DVB_NEW_OSD_DRIVER   //wangchengjiang 2005-4-12 14:35
                    osd_draw_rect(mn_r_pm4);
                    #endif                     //end ifdef DVB_NEW_OSD_DRIVER

                    id = setup_item[page][index_y+index_y_start][1];
             #ifdef OP_CUST_UI// libing 2005-5-8 16:30
        			if (id==STR_OS_RETURN_MAIN_SETUP)
        			id=STR_OS_EXIT_MENU;
             #endif
                    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

                    index_y--;

                #if (defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD))||defined(QSI_SETUP_MENU)//liweihua 2004-6-15 for QSI //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE          //zhaoyanhua 03-11-7 11:19
                    while(setup_item[page][index_y+index_y_start][0]==SET_SPACE)
                    {
                        index_y--;
                    }
                #else   
                    if (setup_item[page][index_y+index_y_start][0]==SET_SPACE)    index_y--;
                #endif  

#if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE) ||defined(SET_FCR_SPEAKER)  //xulf 2004-01-07               
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
	#ifdef DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF //zxb 2005-5-8 12:52
	do{			
		id = setup_item[page][index_y+index_y_start][1];
		if(!(
		((id == STR_OS_ECHO)||(id == STR_OS_MIC_VOL)) && 
		(setup_item[page][MIC_SETUP_ITEM_INDEX][(setup_sel[page][MIC_SETUP_ITEM_INDEX])] == STR_OS_OFF)
		))
			break;
		index_y-- ;
 	}while(1);    	
    #endif //DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF
/*#ifdef DVB_MENU_SETUP_STYLE //Maoyong2004-12-22 11:39
            GetUpValidDvbMenuItem();
#endif                */
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
//                      ||(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)
                        )
                        )
                    {
                        index_y--;
//                      index_y=AC3DYNAMICITEM1-1;
                    }
#endif //NO_AC3_DYNAMIC_RANGE

#endif //#ifndef SETUP_ALL_VALID

                    printf("idd");
                    
                    id = setup_item[page][index_y+index_y_start][1];

                    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);

                    //the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
                    if ( (index_y+index_y_start) < (setupItemNum[1]-1)) {
                        //draw ">>" between sub-mean and it's corresponding selection area
                //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
                #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:05
                        if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
                        #endif                          
                        #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:12
                        osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SANTIFONTCOLOR, SBGCOLOR);
                        #else                           
#if !defined(DVB_MENU_SETUP_STYLE)&&!defined(DVB_MENU_TYPE1)   //sunzhh 20050430
                        osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
#else
                        if(IsDvbSubMenuPageItem())
                        	osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
#endif

                        #endif
                        
                        #ifdef DVB_MENU_SETUP_STYLE
                        if(IsDvbSetupTimezone() )
                            submenuStart = index_y + SETUP_MENU_YSTART - 1;
                        else                            
                        #endif
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
                            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
                            osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                            #endif
                            
                            osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, SDEFAULTCOLOR,SBGCOLOR);
                            
                        } else
                            if (setup_item[page][index_y+index_y_start][0]==SET_SCALE) {
                        #ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 18:36
                            if(page != VIDEOPAGE)
                        #endif//VIDEO_SETUP_NEW_GUI
                                setup_PrepareScaleItem(id, 0);
                            } 
                            #ifdef SUPPORT_FUNCTION_MENU
                            //#ifdef SUPPORT_SPI
                            else if (setup_item[page][index_y+index_y_start][0] == SET_SHOW) 
                            {
                              //printf("up show mcu version.....\n");
                              show_FW_MCU_servoV();
                            }
                            //#endif
                            #endif//end #ifdef SUPPORT_FUNCTION_MENU
                            else {
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
                                            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
                                            osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                                            #endif
                                            osd_DrawString(SETUP_SUB_XSTART+1, (i-2+submenuStart)+1, str, SDEFAULTCOLOR, SBGCOLOR);
                                        } else {
                                            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
                                            osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
                                            #endif
                                            #ifdef SELECT_MEDIA_IN_SETUPMENU //Maoyong 2004-8-10 20:57
                                            if( IsSetupMediaItemDisable(i) )
                                                osd_DrawString(SETUP_SUB_XSTART+1, (i-2+submenuStart)+1, str, SGRAYCOLOR, SBGCOLOR);
                                            else
                                            #endif
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
                        #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
                        osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                        #endif
                        osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SDEFAULTCOLOR, SBGCOLOR);
                    } else {
                        //normal UP button
                        #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
                        osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
                        #endif
                        osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SFONTCOLOR, SBGCOLOR);
                    }
                    #ifdef SELECT_MEDIA_IN_SETUPMENU
    		    	if( setup_item[page][index_y][1] == STR_OS_MEDIA_TYPE)
                        up_skip_media_sub_item();
    				else
    				#endif
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
osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/16, 13);//SBGCOLOR);
    #endif          
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU        
}



