/*
*  Terry,2004/3/28 05:03PM
*/

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
static inline void bbk_down_main_setup_menu(void)
{
    draw_setup_Btn_HL( 1, ONE_KEY_PASS_X*11, ONE_KEY_PASS_Y*4, 8* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);  
    draw_setup_Btn_HL( 1,SETUP_X*14+28, SETUP_Y*4, 8* 24, 1*32,4,MAIN_SETUP_PAGE_BGCOLOR);
    index_x = EXIT_SETUP_MENU_X;
    draw_setup_Btn_HL( 1,EXIT_SETUP_MENU_X*14+32, EXIT_SETUP_MENU_Y*4, 9* 24, 1*32,4,SETUP_HL_COLOR);       
}
static inline void down_2nd_main_page(void)
{
    int iItemType;
    BYTE i;
    for (i=0; i<MAX_PAGE_ITEM; i++)
    {       
        iItemType=setup_item[page][i][0];
        if (iItemType == SET_SPACE) continue;
        if (iItemType == SET_NE) break;     
    }
  
    setupItemNum[1] = i;    
}

#endif
    
static inline void down_main_setup_menu(void)
{
    ui_printf("main menu page\n");

    setupLevel=1;
    id=setup_item[page][index_y][1];
    setup_DrawItem(1, SETUP_MENU_YSTART+1, 1);
    
    #if  !defined(SETUP_COLOR_TYPE1) &&    !defined(SETUP_COLOR_TYPE2) && !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-5 10:04// zhangyu 2003-08-29 17:28 
#ifndef DVB_MENU_SETUP_STYLE
        setup_Showredframe(page);
#else
        setup_Showredframe(dvbpage);
#endif
    #endif

#if !defined(DVB_MENU_SETUP_STYLE)&&!defined(DVB_MENU_TYPE1)  //sunzhh modify
    draw_3rd_menu();
#else
	//if((page != INSTALLPAGE)&&(page != CHANNELPAGE))
	if( (setup_item[page][index_y][0] == SET_FUNC))//&&(setup_item[page][i][0] == SET_SH) )//sunzhh 20050430
	    draw_3rd_menu();
#endif
    
}

static inline void down_cust_menu(void)
{//CUSTM menu page , clear third-level menu
    int i;
#ifdef OP_CUST_UI// libing 2005-5-8 16:26
    BYTE buf[20];
#endif
  
#ifdef  RATING_8
    if (index_y == 3) 
    { 
        osd_draw_rect(mn_r_pm1);
        ShowCUSTMMsg();
    }else
#endif//end RAGING_8
#ifdef SUPER_DEFAULT_OSD_LANG
    if ((index_y == CUSTMOSDITEM)&&((8-N_OSD_LANGS)<=1))
    {
        osd_draw_rect(mn_r_pm2);
        ShowCUSTMMsg();
    }else
#endif
    {
    	//WSLEE fix the clear problem 20050526 PM2:00, old menu can't refresh
#ifdef CUSTM_MENU_REVISE    	
        osd_draw_rect((SETUP_SUB_XSTART-1)*16,(SETUP_MENU_YSTART+4)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART-4)*SETUP_BUTTON_HEIGHT,SBGCOLOR);
#else 
        osd_draw_rect((SETUP_SUB_XSTART-1)*16,(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART-3)*SETUP_BUTTON_HEIGHT,SBGCOLOR);
#endif
    }

    id = setup_item[page][index_y][1];
    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);
    index_y++;

    id = setup_item[page][index_y][1];
#ifdef OP_CUST_UI// libing 2005-5-8 16:26
    if (id==STR_OS_RETURN_MAIN_SETUP)    
    id=STR_OS_EXIT_MENU;
#endif
    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);

    //the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
    #ifdef RCD_GPIO_CONTROL            // alan 2002/7/26 02:08と
    if (index_y < (4))           
    #elif defined(SUPER_DEFAULT_OSD_LANG)||defined(OP_CUST_UI)//libing       //freyman add 2004-2-7 17:50
    if (index_y < (7-1))           
    #elif defined(CORTROL_VCD_ONF) //wangap add 2004/5/27
    if (index_y < 6)
    #else
    if (index_y < (6-1))           
    #endif
    {      
        //draw ">>" between sub-mean and it's corresponding selection area
        //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
        #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:04
        if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
        #endif                          
        {
#ifndef EASTECH_NEW_SETUP_MENU
            osd_DrawString(mn_r_pm3);
#endif
        }
          
        submenuStart = index_y+SETUP_MENU_YSTART;
#ifdef OP_CUST_UI        
        if(index_y==5)
        {
        	psprintf(buf, "05-02-22");
		    osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+6, buf, SFONTCOLOR, SBGCOLOR);
        }  
#endif        
        if (setup_item[page][index_y][0]==SET_NM) 
        {
            char buf[8];
                        
            #ifdef RATING_8                             
            #if !defined(SETUP_COLOR_TYPE1)&&!defined(SETUP_COLOR_TYPE2)    //wangfeng 2003-08-29 17:28     
            #ifdef SPE_SETUP       //linrc add 2004-5-10 10:19 for SPE_SETUP
            osd_draw_rect((SETUP_SUB_XSTART)*16,(SETUP_MENU_YSTART+4)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,5*SETUP_BUTTON_HEIGHT,SBGCOLOR);
            #else
            osd_draw_rect((SETUP_SUB_XSTART)*16,(SETUP_MENU_YSTART+4)*SETUP_BUTTON_HEIGHT,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,5*SETUP_BUTTON_HEIGHT,SBGCOLOR);
            #endif
            #endif                              
            #endif                              
                            
            #ifdef SETUP_6_DIGIT_PASSWORD //zhaoyanhua add 03-10-14 14:53
            psprintf(buf, "%06d", UserSet.parent_passwd);
            #else //4 digit password 
            psprintf(buf, "%04d", UserSet.parent_passwd);
            #endif   //end SETUP_6_DIGIT_PASSWORD

            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
            osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
            #endif
            osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, SDEFAULTCOLOR, SBGCOLOR);//张宇标记颜色                             
        } else 
        {//get select item
            #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
            if(one_key_pass_flag)
            {
                sel = GetOneKeyPageSel(index_y);
                printf("+++++++++++++ 12222sel = %d,index_y = %d--\n",sel,index_y);
            }else
            #endif
                sel = setup_sel[page][index_y];
    
            #ifdef RATING_8
            if((page == CUSTMPAGEINDEX) && (index_y == 3))
            {
                submenuStart = SETUP_MENU_YSTART;
            }else
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
            {
                submenuStart = index_y+SETUP_MENU_YSTART;
            }      
    
            //draw third-level menu
            for (i=2; i<MAX_ITEM_SEL; i++)
            {
                id = setup_item[page][index_y][i];
                if (id==0) break;
                #ifdef SPE_SETUP    //2004-5-10 9:30 linrc add for when show the CUSTMOSD,the "]"not clear. 
                ShowSel(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART,sel == i);
                #else
                ShowSel(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,sel == i);
                #endif
            }
    
            setupItemNum[2] = i - 2;
        }
    }

    #if (!defined (SETUP_COLOR_TYPE1))&&(!defined (SETUP_COLOR_TYPE2))//zhaoyanhua add for BBK 03-11-5 18:49
    //wanghaoying add 2003-10-24 16:16
    //redraw the bottom horizontal line that is deleted by user operation
    #ifndef SPE_SETUP   //linrc add2004-5-9 21:04 if define SPE_SETUP,not show the top and bottom line  
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
    #endif //end SPE_SETUP
    #endif
}

static inline void down_osd_clear_3th_menu(void)
{
    ui_printf("clear 3th menu page in\n");
    
    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS)
    {
      #ifdef DEBUG_FUNCTION_MENU
      printf("clear the sub menu.....index_y:%d\n",index_y);
      #endif
      //将子菜单关掉！
      #ifdef SUPPORT_DISPLAY_MENU
      if(Out_Display_Menu())
      #endif//end #ifdef SUPPORT_DISPLAY_MENU
      osd_draw_rect(second_menu_region_plus);   
      
      //将反显的菜单项转成未选中显示状态
      id = setup_item_plus[page][index_y][1]; 
      setup_DrawItem(1, index_y+SETUP_MENU_YSTART_PLUS, 0);
    }
    else
    {
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    //clear third-level menu 
    #ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 19:42
    if(page == VIDEOPAGE)   
      osd_draw_rect((SETUP_SUB_XSTART-1)*16,(index_y +SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT+30,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,SETUP_BUTTON_HEIGHT,SBGCOLOR);
    else    
    #endif//VIDEO_SETUP_NEW_GUI         
    
#ifdef HANYANG_SETUPMENU //2004-6-24 05:10?宇P
        if(page==3)
             osd_draw_rect((SETUP_SUB_XSTART-1)*16,SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT+31,(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,(SETUP_MAX_LINE-SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT-93, 1);
         else
#endif
    osd_draw_rect(mn_r_pm4);
    
    //ui_printf("<1>\n");delay_srv_10ms(100);
    
    #if !defined(  SETUP_COLOR_TYPE1)&& !defined( SETUP_COLOR_TYPE2)
    if (p_scan==1)

    { printf("---------no draw line----------\n");
       #ifndef SPE_SETUP
      osd_DrawLine(250, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 2);
#endif
    }    

    else
{
   printf("---------no draw line---------\n");
#ifndef SPE_SETUP       
       osd_DrawLine(250, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
#endif
}
    #endif  
    
    //ui_printf("<2>\n");delay_srv_10ms(100);
    
    id = setup_item[page][index_y+index_y_start][1];
    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    //ui_printf("<3>\n");delay_srv_10ms(100);
    ui_printf("clear 3th menu page out\n");
}

static inline int down_adj_page_invalid_item(void)
{
    
    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS)
    {
        #ifdef DEBUG_FUNCTION_MENU
        printf("adjust index_y:%d\n",index_y);
        #endif
        //index_y递加
        #ifdef SUPPORT_DISPLAY_MENU
        if( ((In_Display_Menu())&&(index_y >= (MAX_PAGE_ITEM_PLUS-2)))\
             ||((Out_Display_Menu())&& (index_y>=(MAX_PAGE_ITEM_PLUS-5))) )
        #else
        if(index_y>=(MAX_PAGE_ITEM_PLUS-1))
        #endif//end #ifdef SUPPORT_DISPLAY_MENU
          index_y = 0;
        else         
          index_y ++;
        
        //we must skip the invalid item! 
        #ifdef SUPPORT_DISPLAY_MENU
        if(In_Display_Menu())
        {
          if(display_item_invalid[index_y] == ITEM_INVALID_FLAG)
          {
            for(;display_item_invalid[index_y]==ITEM_INVALID_FLAG;index_y++)
              ;           
          }
        }
        #endif
        //将菜单项目反显
        id = setup_item_plus[page][index_y][1]; 
        setup_DrawItem(1, index_y+SETUP_MENU_YSTART_PLUS, 1);
    }
    else
    {
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    #if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE) ||defined(SET_FCR_SPEAKER)//delete by xyy 2004-10-23      //xulf 2004-01-07              
    if ( (page==MULTISPKPAGE)&&(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF) )
    {
        index_y++;
        if ( (index_y+index_y_start) == SPKSTART && (index_y+index_y_start) != SPKEND)
        {
            if (index_y_start==0) 
            {
              index_y += (SPKEND-SPKSTART+1);
            }else
            {
              index_y = SPKEND+1;
              index_y_start--;
              ShowSetupPage(1);
              return 1;
            }
        }
    }   
    #if defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)
    else 
    #endif//ONLY_DOWNMIXOFF_CAN_SET_CE_RE
    #endif//ONLY_DOWNMIXOFF_CAN_SET_CE_RE
    
    #ifdef PROLOGICII_3D_MUTEX//4-2-12 1:23
    if((page==AUDPAGE)&&is_EQ_SOUND_set()&&(index_y==(PROLOGIC_II-1) )  )
        index_y+=2;//Maoyong 2004.03.09 skip PROGLIC-II
    else 
    #endif//PROLOGICII_3D_MUTEX
    
    #ifdef  SETUP_ALL_VALID
    #ifdef KARAOKE_MENU     
    if((page==AUDPAGE)&&(index_y>4)&&(KARAOKE_MENU_FLAG))
    {
        index_y=1;
    }
    #ifdef PROLOGIC_ON_51CH
    else if((page==AUDPAGE)&&(KARAOKE_MENU_FLAG==0)&&(setup_IsSpkDownmixOff()&&(index_y==1)|| !setup_IsSpkDownmixOff()&&(index_y==0)))
    #else
    else if((page==AUDPAGE)&&(index_y==1)&&(KARAOKE_MENU_FLAG==0))
    #endif //PROLOGIC_ON_51CH
    
    index_y=6;//wangfeng 2003-11-11 13:55
    #endif//KARAOKE_MENU     
    #else//SETUP_ALL_VALID
    if (page==AUDPAGE) 
    {
        if ( (SETUP_SPDIF==SPDIFBITSTREAM) &&(index_y==DIGIOUTITEM) &&( ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
            //AUDIF_CODING_MODE_PCM|   //DTSCD-BITSTREAM MODE, Jeff 20020719
            AUDIF_CODING_MODE_DTS))||(cd_subtype==CD_DTS) )//nono 2-7-25 17:29
            )
        {
            index_y += (VOLCTRLEND-VOLCTRLSTART+2);
        } 
        else
        {
            index_y++;
            if ( (((SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) &&( coding_mode_now&(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD)))
                    ||(coding_mode_now==AUDIF_CODING_MODE_LPCM)//terry,0512,currently ,we are not surport LPCM key shift
                    )&&(index_y==KEYITEM))
            {
                index_y++;
            }
        }
    }
    
    #ifndef NO_AC3_DYNAMIC_RANGE
    else if ( (page==AC3DIGITALPAGE) && (index_y==(AC3DYNAMICITEM1-1)) &&( (SETUP_AC3DIGITAL_OUTMODE!=AC3DYNAMICITEM2)))
    {
        index_y++;
    }
    #endif //NO_AC3_DYNAMIC_RANGE
    else
    #endif //SETUP_ALL_VALID
    {
        #if !defined(SETUP_ALL_VALID)||defined(SET_FCR_SPEAKER)  ///xulf 2004-01-07   
        if((page!=MULTISPKPAGE)||((page==MULTISPKPAGE)&&(SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF)))
        #endif
        index_y++;
    }
    
    /*#ifdef DVB_MENU_SETUP_STYLE //Maoyong 2004-12-22 11:39 for skip some invalid item
    GetDownValidDvbMenuItem();
    #endif*/
    
    #if (defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD))||defined(QSI_SETUP_MENU)//liweihua 2004-6-15 for QSI//axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE          //zhaoyanhua 03-11-7 11:19
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
        int i = 0;
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
    
    #ifdef DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF //zxb 2005-5-8 13:03
	do{			
    id = setup_item[page][index_y+index_y_start][1];
		if(!(
		((id == STR_OS_ECHO)||(id == STR_OS_MIC_VOL)) && 
		(setup_item[page][MIC_SETUP_ITEM_INDEX][(setup_sel[page][MIC_SETUP_ITEM_INDEX])] == STR_OS_OFF)
		))
			break;
		index_y++ ;
 	}while(1);    	
    #endif //DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF
    
    id = setup_item[page][index_y+index_y_start][1];
#ifdef OP_CUST_UI //libing 2005-5-8 16:26
    if (id==STR_OS_RETURN_MAIN_SETUP)
    id=STR_OS_EXIT_MENU; 
#endif
    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    return 0;
}

static inline void down_draw_action_item(void)
{//draw ">>" between sub-mean and it's corresponding selection area
    int i;
    const char *str;
    
    #if 0//def SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS) //与按"往上"按键的功能是共用的。
    {                       
      #ifdef DEBUG_FUNCTION_MENU
      printf("Draw down item\n");
      #endif
      //绘制箭头
      #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:12
      osd_DrawString(SETUP_SUB_XSTART_PLUS-1, index_y+SETUP_MENU_YSTART_PLUS, Ch_arrorR, SANTIFONTCOLOR, SBGCOLOR);
      #else
      osd_DrawString(SETUP_SUB_XSTART_PLUS-1, index_y+SETUP_MENU_YSTART_PLUS, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
      #endif
      
      submenuStart = index_y+SETUP_MENU_YSTART_PLUS;
       
      
      if(setup_item_plus[page][index_y+index_y_start][0] == SET_SCALE) 
      {////brightness
        setup_PrepareScaleItem(id, 0);
      }
      else if (setup_item_plus[page][index_y+index_y_start][0] == SET_FUNC)
      {//draw second-level menu
        for (i=2; i<MAX_ITEM_SEL_PLUS; i++) 
        {//get select item
            
            sel = setup_sel_plus[page][index_y];
            id = setup_item_plus[page][index_y][i];
            if (id==0) break;
            
            ShowSel(SETUP_SUB_XSTART_PLUS, (i-2+submenuStart), SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS,sel == i);
        }
      }
    }
    else
    {
    #endif //end #ifdef SUPPORT_FUNCTION_MENU

    //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
    #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:04
    if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
    #endif                          
    #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 17:12
    osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SANTIFONTCOLOR, SBGCOLOR);
    #elif defined(DVB_MENU_SETUP_STYLE)||defined(DVB_MENU_TYPE1)    //sunzhh modify 20050430                            
        if(IsDvbSubMenuPageItem())
    		osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
    #else//#ifdef QSI_SETUP_MENU_DESIGN
    osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
    #endif//#ifdef QSI_SETUP_MENU_DESIGN
    
    #ifdef DVB_MENU_SETUP_STYLE
    if(IsDvbSetupTimezone())
        submenuStart = index_y + SETUP_MENU_YSTART - 1;
    else                            
    #endif
    submenuStart = index_y+SETUP_MENU_YSTART;
    
    //special item(PASSWORD), page-0, item-4
    if (setup_item[page][index_y+index_y_start][0]==SET_NM) 
    {
        if (UserSet.parental_ststus==C_LOCK) 
        {
          setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL;
          str = _OsdMessegeFont1[osd_font_mode][STR_OS_LOCK];
        }else
        {
          setup_sel[page][index_y+index_y_start] = MIN_ITEM_SEL + 1;
          str = _OsdMessegeFont1[osd_font_mode][STR_OS_UNLOCK];
        }
        
        #ifdef  SETUP_COLOR_TYPE2   //zhangyu 3-9-1 4:40张宇P
        osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, SANTIBGCOLOR );     
        osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, 4, SBGCOLOR);
        #else                           
            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39                                
            osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
            #endif
        osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, SDEFAULTCOLOR,SBGCOLOR);//wangfeng 3-8-27 22:57   
        #endif                                                              
    }else if (setup_item[page][index_y+index_y_start][0]==SET_SCALE) 
    {
        #ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-7 18:36
        if(page != VIDEOPAGE)
        #endif//VIDEO_SETUP_NEW_GUI
        setup_PrepareScaleItem(id, 0);
    }
    #ifdef SUPPORT_FUNCTION_MENU
    //#ifdef SUPPORT_SPI
    else if (setup_item[page][index_y+index_y_start][0] == SET_SHOW) 
    {
        //printf("down show mcu version.....\n");
        show_FW_MCU_servoV();
    }
    //#endif//end #ifdef SUPPORT_SPI
    #endif//end #ifdef SUPPORT_FUNCTION_MENU
    else 
    {//special item(LANGUAGE)
        #ifdef RATING_8
        if(page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) 
        #else
        if(page==LANGPAGE) 
        #endif
        {
          submenuStart = SETUP_MENU_YSTART; //from 0
        }
        
        //draw third-level menu
        for (i=2; i<MAX_ITEM_SEL; i++) 
        {//get select item
            #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
            if(one_key_pass_flag)
            {
              sel = GetOneKeyPageSel(index_y);
              printf("+++++++++++++ 333331sel = %d,index_y = %d--\n");
            }else
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
    #if 0//def SUPPORT_FUNCTION_MENU
}
#endif //end #ifdef SUPPORT_FUNCTION_MENU
}


static inline void down_return_main_menu(void)
{
    // highlight : draw a frame to identify which tab is enable          
    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:38        
    SetOsdCol(mn_osd_col2 );          
    #endif       
    #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)  //zhangyu  2003-08-29 17:28
#ifndef DVB_MENU_SETUP_STYLE
        setup_Showredframe(page);
#else
        setup_Showredframe(dvbpage);
#endif
    #endif
    
    id = setup_item[page][index_y+index_y_start][1];
#ifdef OP_CUST_UI //libing 2005-5-8 16:26    
    if (id==STR_OS_RETURN_MAIN_SETUP)
    id=STR_OS_EXIT_MENU; 
#endif    
    setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);
    setupLevel=0;
    index_y_start=0;
    index_y=0;
}

static inline void down_3th_page(void)
{//third-level menu page
    
    const char *str;
    
    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS)
    {
      #ifdef DEBUG_FUNCTION_MENU
      printf("draw the second page,y2:%d y:%d\n",index_y2,index_y);
      #endif
      
      submenuStart = index_y + SETUP_MENU_YSTART_PLUS;
      
      sel = setup_sel_plus[page][index_y];
    
      id = setup_item_plus[page][index_y][index_y2+2];
      ShowSel(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS,(index_y2+2) == sel);
      

      ShowSel(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS,(index_y2+2) == sel);
    
      index_y2++;
      
      if ((index_y2+2) == sel) 
      {
        osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SANTIBGCOLOR, 1);
      }
      else
      {
        osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SANTIBGCOLOR, 0);
      }
    
      id = setup_item_plus[page][index_y][index_y2+2];
      str = setup_SetItemString();
      osd_DrawString(SETUP_SUB_XSTART_PLUS+1, index_y2+submenuStart, str, SANTIFONTCOLOR, SANTIBGCOLOR);
    }
    else
    {
    #endif //end #ifdef SUPPORT_FUNCTION_MENU  
    
    #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
    if(one_key_pass_flag)
    {
      sel = GetOneKeyPageSel(index_y);
    }else
    #endif
      sel = setup_sel[page][index_y];
    
    id = setup_item[page][index_y][index_y2+2];
    ShowSel(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,(index_y2+2) == sel);
    #ifdef SELECT_MEDIA_IN_SETUPMENU
    if( setup_item[page][index_y][1] == STR_OS_MEDIA_TYPE)
    	down_skip_media_sub_item();
    else	
    #endif
    index_y2++;
    
    
    #ifndef SETUP_COLOR_TYPE2
    ShowSel(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,(index_y2+2) == sel);
    #endif
    
    if ((index_y2+2) == sel) 
    {
      osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
    }else
    {
      osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 0);
    }
    
    id = setup_item[page][index_y][index_y2+2];
    str = setup_SetItemString();
    osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SANTIFONTCOLOR, SANTIBGCOLOR);
    
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU

}

#ifdef SELECT_MEDIA_IN_SETUPMENU //Maoyong 2004-8-9 21:42
BYTE IsMediaItemDownValid(void)
{
    BYTE iRes = 0;
    if(index_y2 == DISC_ITEM){
        if(!IsNoPluggedUSB() || !IsNoPluggedCARD() )
            iRes = 1;
    }else if( (index_y2 == USB_ITEM) && !IsNoPluggedCARD() )
        iRes = 1;

    return iRes;
}
void down_skip_media_sub_item(void)
{
    if(index_y2 == DISC_ITEM)  {
        if( IsNoPluggedUSB() ){
            index_y2 += 2;
            return;
        }
    }
    index_y2 ++;
}
#endif //#ifdef SELECT_MEDIA_IN_SETUPMENU

void setup_func_down(void)
{ 
    ui_printf("setupLevel:%d\n",setupLevel);
    
    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS)
    {
      #ifdef DEBUG_FUNCTION_MENU
      printf("down key press,setupLevel:%d,index_y:%d index_y2:%d\n",setupLevel,index_y,index_y2);
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
        if(index_x != 6)
        {
          if(ir_select_number >0)
            ir_select_number--;
        }
        
        search_func_input();
        ShowSetupPage_plus(MENU_REFRESH);
        #ifdef DEBUG_DISPLAY_MENU
        printf("down...index_x:%d goto_time:%d ir:%d.....\n",index_x,goto_time,ir_select_number);
        #endif
        return;
      }
      #endif//end #ifdef SUPPORT_DISPLAY_MENU
      
      if(setupLevel == 1) 
      {//the first level menu page  
        
        #ifdef DEBUG_FUNCTION_MENU
        printf("---down in the first menu,index_y2:%d\n",index_y2);
        #endif
        #ifdef SUPPORT_DISPLAY_MENU
        if( ((In_Display_Menu())&&(index_y < MAX_PAGE_ITEM_PLUS))
             ||((Out_Display_Menu())&&(index_y < MAX_PAGE_ITEM_PLUS-4)) )
        #else 
        if(index_y < MAX_PAGE_ITEM_PLUS) 
        #endif//end #ifdef SUPPORT_DISPLAY_MENU
        {
            //clear third-level menu
            down_osd_clear_3th_menu();
            //adust the index_y
            down_adj_page_invalid_item(); 
            
            #if 0 //need to press "select" or "right" key to show the 2nd menu!!!! 
            if(index_y < MAX_PAGE_ITEM_PLUS) 
            {
                if((index_y != 0) && (index_y != 4))
                  down_draw_action_item();
            }     
            #endif     
         }
      }
      else if(setupLevel == 2)
      {//in the 2nd page
         
         #ifdef DEBUG_FUNCTION_MENU
         printf("---down in 2th menu,index_y2:%d\n",index_y2);
         #endif
         /*
         if (setup_item_plus[page][index_y][0]==SET_SCALE) 
         {                      
            //亮度减1且将其显示出来
            setup_CookScaleItem(id, 0);             
            //记忆？
            //run_save_sel_cmd(page,index_y);
         }
         else 
         */
         if(setup_item_plus[page][index_y][0] == SET_FUNC)
         {
           setup_menu_plus_timer = MENU_PLUS_SHOW_TIME;
           
           if (index_y2 < (MAX_ITEM_SEL_PLUS-3)) 
         {
            if(setup_item_plus[page][index_y][index_y2+3] == 0)
              return;
            down_3th_page();
         }
       }
    }
    }
    else
    {
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    
    #ifdef SHOW_SETUPMENU_SETUP     //linrc add 2004-5-1 21:18          
    if(setupLevel!=2 && !(full_scrn&CUSTM))
    {
        if(page!=3) //2004-6-24 06:10?宇P
        osd_draw_rect(300, 75, 250, 350, 1);    
    }
    #endif //end SHOW_SETUPMENU_SETUP   
    #ifdef SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-16 11:15
    //in PASSWORD GUI, LEFT/RIGHT/UP/DOWN has no use.
    if(passwdGUI_state != NO_GUI_STATE) return;
    #endif

    #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
    ui_printf("main_setup:%d\n",main_setup);   
    if(main_setup)
    {
        bbk_down_main_setup_menu();     
        return;
    }
    #endif

    reset_passwd_cnt();
  
    #ifdef SHOW_STANDBY_TIMER  //suqiaoli add 8-8
    reset_standby_timer_pos();
    #endif

    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:38   
    #ifdef SETUPMENU_NOT_TRANSPARENT
    SetOsdCol(mn_osd_col2);  //2004-4-17 01:45张宇P
    #else
    SetOsdCol(mn_osd_col1);
    #endif//SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
    #endif//#ifndef QSI_SETUP_MENU_DESIGN
    
    
  
    if (setupLevel==0) 
    {//main menu page
        down_main_setup_menu();
        return;
    }else if (setupLevel==1) 
    {//second level menu page
        ui_printf("2nd menu page\n");    
  
        #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE          //calculate setupItemNum[1] true value.zhaoyanhua add 03-11-7 14:03
        down_2nd_main_page();
        #endif
    
        ui_printf("index_y:%d index_y_start:%d setupItemNum[1]:%d\n",index_y,index_y_start,setupItemNum[1]);

        if ( (index_y+index_y_start) < (setupItemNum[1]-1)) 
        {
            if (full_scrn&CUSTM) 
            {
                down_cust_menu();
            }
            else 
            {//normal setup second-level page
                if (index_y > (SETUP_MAX_LINE-5)) 
                {
                    index_y = SETUP_MAX_LINE-5;
                    index_y_start++;
                    ShowSetupPage(1);
                }
         
                //clear third-level menu
                down_osd_clear_3th_menu();
         
                //special case//nonotest 2003-9-5 17:44
                if(down_adj_page_invalid_item()) return;
                
			#if !defined(DVB_MENU_SETUP_STYLE)&&!defined(DVB_MENU_TYPE1)   //sunzhh modify 20050430
                //the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
                if ((index_y+index_y_start) < (setupItemNum[1]-1)) 
                {
                    down_draw_action_item();
                }
            #else
                //the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
                if(system_state == SYSTEM_TS)
                {
                	//if((page != INSTALLPAGE) && (page != CHANNELPAGE))
                	if( IsDvbSubMenuPageItem() )
                	{
		                if ((index_y+index_y_start) < (setupItemNum[1]-1)) 
		                {
		                    down_draw_action_item();
		                }
		            }
            	}
            	else if((index_y+index_y_start) < (setupItemNum[1]-1)) 
                {
                    down_draw_action_item();
                }
            	
            
            #endif
                 
            }
        }else
        {
            if (full_scrn&CUSTM) return;
       
            if (setup_item[page][index_y][1]==STR_OS_RETURN_MAIN_SETUP)
            {
                down_return_main_menu();
            #ifdef SHOW_SETUPMENU_SETUP
                show_setupmenu();
                #endif //SHOW_SETUPMENU_SETUP
                return;
            }
        }
    }else if (setupLevel==2) 
    {//3th page
        if (setup_item[page][index_y][0]==SET_SCALE) 
        {
            #ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 16:54
            if(page == VIDEOPAGE) return;
            #endif//VIDEO_SETUP_NEW_GUI             

            setup_CookScaleItem(id, 0);
            run_save_sel_cmd(page,index_y);
        }else if ( (index_y2 < (setupItemNum[2]-1)) && (setup_item[page][index_y][0]!=SET_NM) ) 
        {
            #ifdef SELECT_MEDIA_IN_SETUPMENU
            if( (setup_item[page][index_y][1] == STR_OS_MEDIA_TYPE) && !IsMediaItemDownValid() )
                return;
            #endif
            down_3th_page();
        }
    
    }
  
    #ifdef SETUP_COLOR_TYPE2
    if (!(full_scrn&CUSTM)) osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/16, 13);//SBGCOLOR);
    #endif
   
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
}




