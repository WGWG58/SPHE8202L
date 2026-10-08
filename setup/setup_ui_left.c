void setup_func_left(void)
{
    const char *str;
    UINT16 line = 0;
    
    #if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)    //sunzhh 20050430
    //if(((page == INSTALLPAGE)||(page == CHANNELPAGE))&&(setupLevel)&&(system_state == SYSTEM_TS))
    if( IsDvbStateNoSubMenu() ) //In Dvb Mode, Level 1 has no sub item
        return;
    #endif
    
    #ifdef SUPPORT_FUNCTION_MENU
    if(full_scrn&SETUP_PLUS)
    {
        #ifdef DEBUG_FUNCTION_MENU
        printf("left key press,index_y:%d,index_y2:%d",index_y,index_y2);
        #endif
        
        #ifdef SUPPORT_DISPLAY_MENU
        if(In_Display_Menu())
          setup_menu_plus_timer = DISPLAY_MENU_SHOW_TIME;
        else
        #endif//end #ifdef SUPPORT_DISPLAY_MENU
        setup_menu_plus_timer = MENU_PLUS_SHOW_TIME;
        
        #ifdef SUPPORT_DISPLAY_MENU
        if(In_Display_Menu())
        {
          exe_display_function(0);
          return;
        }
        #endif
        
        if(setupLevel == 2)
        {

            //change string color of current selection item in selection area
            /*
            if (setup_item_plus[page][index_y][0]==SET_SCALE)
            {
                //子菜单项转为正常显示
                setup_PrepareScaleItem(id, 0);
            } 
            else 
            */
            if (setup_item_plus[page][index_y][0] == SET_FUNC)
            {
                submenuStart = index_y+SETUP_MENU_YSTART_PLUS;
                
                //sel = setup_sel_plus[page][index_y];
                
                id = setup_item_plus[page][index_y][index_y2+2];
                str = setup_SetItemString();
                
                //将刚才被选中的子菜单项(红色标中的)转为正常或是标中显示(按钮深陷且字体为蓝色)
                if ((index_y2+2) == sel)
                {//
                    #ifdef DEBUG_FUNCTION_MENU
                    printf("press left key return\n");
                    #endif
                    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
                    osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SBGCOLOR, 1);
                    #endif
                    osd_DrawString(SETUP_SUB_XSTART_PLUS+1, index_y2+submenuStart, str, SDEFAULTCOLOR,SBGCOLOR);
                } 
                else 
                {//???
                    #ifdef DEBUG_FUNCTION_MENU
                    printf("select and return\n");
                    #endif
                    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
                    osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, index_y2+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SBGCOLOR, 0);
                    #endif
                    osd_DrawString(SETUP_SUB_XSTART_PLUS+1, index_y2+submenuStart, str, SFONTCOLOR, SBGCOLOR);
                }
   
             //反显左键返回的菜单项以表示选中
             id = setup_item_plus[page][index_y][1];
             str = _OsdMessegeFont1[osd_font_mode][id];
             #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39   
             osd_draw_setup_button(SETUP_MENU_XSTART_PLUS, index_y+SETUP_MENU_YSTART_PLUS, SETUP_SUB_XSTART_PLUS-SETUP_MENU_XSTART_PLUS-1, SANTIBGCOLOR, 1);
             #endif
             osd_DrawString(SETUP_MENU_XSTART_PLUS+1, index_y+SETUP_MENU_YSTART_PLUS, str, SANTIFONTCOLOR, SANTIBGCOLOR);
             
             setupLevel = 1;
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
    
    #ifdef SUPPORT_FUNCTION_MENU
    #ifdef SUPPORT_SPI
    if (setup_item[page][index_y+index_y_start][0] == SET_SHOW) 
      return;
    #endif
    #endif              
    
    #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
    line=SETUP_MAX_WIDTH*16;
    SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
#elif defined(SETUP_COLOR_TYPE2)    
    #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         //zhaoyanhua add 2003-11-30 21:38      
    if(!main_setup)
    #endif
    {
        //SetOsdCol(0,0,SANTIBGCOLOR,0xc0c0c0e0);
        SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
        line=SETUP_MAX_WIDTH*16-20;
    }
#else
    #ifdef HANYANG_SETUPMENU//CAOHUI2004-6-18 17:12
    line=SETUP_MAX_WIDTH*16+260;
    #else
    line=SETUP_MAX_WIDTH*16-20;
    #endif    
    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:38   
    SetOsdCol(mn_osd_col2);    //2004-4-17 01:45张宇P
#endif
#endif//QSI_SETUP_MENU
    
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
        //#ifndef   SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
        #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2) && !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-4 14:17
            #ifdef  SPE_SETUP      //2004-4-21 02:04张宇P bmmm
              //osd_draw_rect((line*page)/6+12, 10, line/6-4, SETUP_BUTTON_HEIGHT+10, 6);//2004-4-20 08:51张宇P bmmm
             if(page<3)   //2004-4-28 13:18lorenc
         osd_draw_rect((line*page)/6+21, 10, line/6+2, SETUP_BUTTON_HEIGHT+10, 6);//2004-4-28 10:36lorenc osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+9, 1);
         else
        osd_draw_rect((line*page)/6+12, 10, line/6-4, SETUP_BUTTON_HEIGHT+10, 6);//2004-4-28 10:36lorenc osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+9, 1);
            #else
#ifndef DVB_MENU_SETUP_STYLE
        osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+9, 1);
#else
        osd_draw_rect(line*dvbpage/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+9, 1);
#endif
            #endif
#ifndef    SPE_SETUP        
        if (p_scan==1)
#ifndef DVB_MENU_SETUP_STYLE
          osd_DrawLine((line*page)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
#else
          osd_DrawLine((line*dvbpage)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(dvbpage+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
#endif
        else
            //wangfeng 3-8-27 20:53
#ifndef DVB_MENU_SETUP_STYLE
           osd_DrawLine((line*page)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);
#else
           osd_DrawLine((line*dvbpage)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(dvbpage+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);
#endif
#endif//#ifndef    SPE_SETUP    

#endif//#if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)
        //#if defined(SAME_DISC_RESUME)||defined(SHOW_STANDBY_TIMER)
        #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:05
        if(page==SysNextPage) page=0;
        #endif

#ifndef DVB_MENU_SETUP_STYLE
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
#else //DVB_MENU_SETUP_STYLE
	if(system_state == SYSTEM_TS)
	{
		if(page > 0)
		{
			page--;
			if(page==AUDPAGE)page--;
			if(page==LANGPAGE)page--;
		}
		else
            page=MAX_SHOW_PAGE;
        if(--dvbpage < 0)
        	dvbpage = 3;
    }
    else
    {
		if(page > 0)
		{
			page--;
			if(page==CHANNELPAGE)page--;
			if(page==INSTALLPAGE)page=MAX_SHOW_PAGE+2;
		}
		else
            page=MAX_SHOW_PAGE+2;
        if(--dvbpage < 0)
        	dvbpage = 5;
            
    }
    
#endif//#if !defined(DVB_MENU_SETUP_STYLE)&& !defined(DVB_MENU_TYPE1)  //sunzhh 20050430

#ifndef SETUP_ALL_VALID     // alan, 2003/7/18 10:49と
        if ( (page==AC3DIGITALPAGE) &&  ( (SETUP_SPDIF==SPDIFBITSTREAM) || (coding_mode_now!=AUDIF_CODING_MODE_AC3) )  )
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
//        #ifndef   SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
        #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-4 14:17
                  #ifdef    SPE_SETUP        //2004-4-21 02:04张宇P bmmm
        //osd_draw_rect(line*page/6+13, 10, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
          if(page==0)
           {
            printf("======== page=%d=======\n",page);
            osd_draw_rect(line*page/6+20, 10, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);//2004-4-28 13:02 lorenc
            }
          else if(page==1||page==2)
          { printf("======== page=%d=======\n",page);
           osd_draw_rect(line*page/6+20, 10, line/6+3, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);//2004-4-28 13:02 lorenc
         }
         else
        osd_draw_rect(line*page/6+13, 10, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
        #else
#ifndef DVB_MENU_SETUP_STYLE
        osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
#else
        osd_draw_rect(line*dvbpage/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
#endif
        #endif
                     #endif
        
        // highlight : draw a frame to identify which tab is enable
        #ifdef  SETUP_COLOR_TYPE1   //wangfeng 2003-08-29 17:28
        SetOsdCol(0,0,SANTIBGCOLOR,0x78501e90);
        #endif
        
        #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-2 17:38
        SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
        #endif
        /*osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SANTIBGCOLOR,1);
        osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SANTIBGCOLOR,1);
        osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SANTIBGCOLOR,1);
        osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SANTIBGCOLOR,1);*/
        #if !defined(SETUP_COLOR_TYPE1)&& !defined(SETUP_COLOR_TYPE2)&& !defined( QSI_SETUP_MENU_DESIGN)//liweihua 2004-7-5 10:04
#ifndef DVB_MENU_SETUP_STYLE
        setup_Showredframe(page);
#else
        setup_Showredframe(dvbpage);
#endif
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
                #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39 
                osd_draw_setup_button(SETUP_SUB_XSTART, submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
                #endif
            
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
                    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
                    osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                    #endif
                    
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
                #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39 
                osd_draw_setup_button(SETUP_SUB_XSTART, submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
                #endif
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
#endif//VIDEO_SETUP_NEW_GUI
                {
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
                }
            } else {
                //special item(LANGUAGE)
#ifdef RATING_8
                if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) {
#else
                if (page==LANGPAGE) {
#endif
                    submenuStart = SETUP_MENU_YSTART; //from 0
                }

                #if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)   //sunzhh 20050430
                if(IsDvbSetupTimezone())
                    submenuStart = index_y+SETUP_MENU_YSTART - 1;
                #endif
                
                id = setup_item[page][index_y][index_y2+2];
                str = setup_SetItemString();

                if ((index_y2+2) == sel) {
                    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
                    osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                    #endif
                    osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SDEFAULTCOLOR,SBGCOLOR);
                } else {
                    #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
                    osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
                    #endif
                    osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, SFONTCOLOR, SBGCOLOR);
                }

            }
        }

        //change string color of current item in sub-menu
        id = setup_item[page][index_y][1];
        
        #if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)   //sunzhh modify 20050430
        	str = SetDvbItemString(id);
        #else
            str = _OsdMessegeFont1[osd_font_mode][id];
        #endif	
        
        #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39    
        osd_draw_setup_button(SETUP_MENU_XSTART, index_y+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, SANTIBGCOLOR, 1);
        #endif
        osd_DrawString(SETUP_MENU_XSTART+1, index_y+SETUP_MENU_YSTART+1, str, SANTIFONTCOLOR, SANTIBGCOLOR);
        setupLevel = 1;
    }
#ifdef SETUP_COLOR_TYPE2     //3-10-28 1:43张宇P
    if (!(full_scrn&CUSTM))
        osd_draw_rect(0, 10+SETUP_BUTTON_HEIGHT*2+10+(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)-100, (SETUP_MAX_WIDTH*16), /*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/16, 13);//SBGCOLOR);
#endif
    
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    
    #ifdef HANYANG_SETUPMENU   //2004-6-21 09:43張宇M
    if(page==3)
        {
            BYTE    buf[20];
            psprintf(buf, "%s", SETUP_VERSION);
            osd_DrawString(SETUP_MENU_XSTART+1,10, buf, 6, SBGCOLOR);
            
        } 
    #endif
    #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 18:42
    osd_DrawLine(0, 86, 280*2, 86, 12, 1);
    #endif
}






