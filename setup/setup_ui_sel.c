/*
**  Freyman, 2004-3-29 17:57
*/
#ifdef SELECT_MEDIA_IN_SETUPMENU
extern BYTE media_changed_flag;
#endif
#ifdef EASTWIN
#include "gpio.h"
#endif

#ifdef SUPPORT_DVD_NATIVE_GAME	//linrc for NATIVE_GAME 2005-10-18 14:49
#include "..\fbuf_game\Fbuf_game_Macro_Def.h"
#endif

#if defined(DVB_MENU_SETUP_STYLE) || defined(DVB_MENU_TYPE1)    //sunzhh 20050430
#include "mpgkern.h"
extern BYTE rem_osd_id; //added by liuchuanyi 05/04/21
void dvb_func_select();
#endif

#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)
static inline void bbk_sel_main_setup_menu(void)
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
}
#endif

#ifdef NEXTPAGE_SYS
static inline void sel_show_turnpage(BYTE id)
{
    if (id==STR_OS_NEXT_PAGE)
    {
        page=SysNextPage;
        printf("======      clead next       ======\n\n");
    }else
    //if (id==STR_OS_PREV_PAGE)
    {
        page=SYSPAGE;
        printf("======      clead PREV       ======\n\n");
    }
    setupLevel=1;
    index_y = 0;
    index_y_start=0;
    ShowSetupPage(1);
    ShowSetupPage(2);
    return;
}
#endif


static inline void sel_func_lock_state(void)
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
#endif
        show_lock(C_UNLOCK,1);
}

#ifdef DVB_MENU_SETUP_STYLE     //sunzhh add 2005-3-17
BYTE restore_pause_flag;
#include "memmap0.h"
#endif

void setup_func_select(void)
{
    const char *str;
    #ifdef STORE_VIDEO_PARAMETER
    BYTE res; 
    #endif 
    
    #ifdef SUPPORT_FUNCTION_MENU
    if((full_scrn&SETUP_PLUS) || (setup_menu_plus_timer))
    {
    	 #ifdef SUPPORT_DISPLAY_MENU
         if(In_Display_Menu())
         {
            setup_menu_plus_timer = DISPLAY_MENU_SHOW_TIME;
        
         	if((index_y == PBC_MENU_ITEM) && (cd_type_loaded == CDDVD))
         	{
         	  	call_ir_func(IRC_ROOT_MENU);//ircmd_root_menu();
         	  	
         	    ShowSetupPage_plus(MENU_REFRESH);  	
         	}
         	else if((index_y == TIME_ITEM))
         	{
         		if(!In_Goto_Menu())
                {
                   //printf("go into goto state at the first time.....\n");
                   goto_time = 0;
                   ir_select_number = 0;
                   index_x = 6;
                   Set_Goto_menu_flag();
                   ShowSetupPage_plus(MENU_REFRESH);
                }
                else 
                {
                   //printf("exe goto function,goto_time:%d.....\n",goto_time);
                   goto_sec = goto_time%100;            
				   goto_min = (goto_time%10000)/100;
				   goto_hour = goto_time/10000;
                   search_func_select();
                   Clear_Goto_menu_flag();
                } 
         	}
         	else
         	  return;
         }
         else
         #endif//end #ifdef SUPPORT_DISPLAY_MENU
         if((!(full_scrn&SETUP_PLUS)) && (setup_menu_plus_timer))
         {//have exited menu plus,only adjust the brightness.
             setup_menu_plus_timer = MENU_PLUS_SHOW_TIME;
             
               #ifdef DEBUG_FUNCTION_MENU
             printf("brightness ++,:%d\n",setup_sel_plus[0][1]);
                #endif
            
             //range is 0~14(-7~7)
             if(setup_sel_plus[0][1] >= BRIGHTNESS_TOTAL_CLASS)
               setup_sel_plus[0][1] = 0;
            else
               setup_sel_plus[0][1]++;
               
             #ifdef SUPPORT_SPI
             scommand = ADJUST_BRIGHTNESS; 
             #endif
             
             show_level(BRIGHTNESS_PLUS_ID,setup_sel_plus[0][1],BRIGHTNESS_TOTAL_CLASS);
             
          /*
              ExitSetupPage(0);
              
              if(setup_sel_plus[page][index_y] < 7)
                psprintf(RegionValStr[REGION1],":-%d",(7-setup_sel_plus[page][index_y]));
              else if(setup_sel_plus[page][index_y] == 7)
                psprintf(RegionValStr[REGION1],":%d",(7-setup_sel_plus[page][index_y]));
              else
                psprintf(RegionValStr[REGION1],":+%d",(setup_sel_plus[page][index_y]-7));
                
              PrintOsdMsg(STR_OS_BRIGHTNESS,REGION1,1,1);
          */
        }
        //in menu plus
        else if(setupLevel == 1)
        {
            if(setup_item_plus[page][index_y][1] == STR_OS_DISPLAY)
            {//will call the display function
                #ifdef DEBUG_FUNCTION_MENU
                printf("call display function\n");
                #endif
                //退出菜单
    	    	#ifdef SUPPORT_DISPLAY_MENU
				ircmd_display_menu();
				#else
                setup_menu_plus_timer = 0;
                ExitSetupPage(0);
                
                //call display function
                ircmd_display();
    	    	#endif
            }
            else if(setup_item_plus[page][index_y][0] == SET_SCALE) 
            {//Brightness
              //退出菜单
              ExitSetupPage(0);
              //显示亮度设定之osd
              show_level(BRIGHTNESS_PLUS_ID,setup_sel_plus[0][1],BRIGHTNESS_TOTAL_CLASS);
             
            }
            else if(setup_item_plus[page][index_y][1] == STR_OS_TV_RATIO)
            {//exe right function to show the sub menu
              setup_func_right();
            }
            else if(setup_item_plus[page][index_y][0] == SET_SHOW)
            {//Battery status
              #ifdef DEBUG_FUNCTION_MENU
              printf("Show battery status!!!\n");
              #endif
              //退出菜单
              setup_menu_plus_timer = 0;
              ExitSetupPage(0);
              //显示电池电量
              
              linebuf[0] = battery_status[setup_sel_plus[0][3]];
              linebuf[1] = NULL;
              
              strcpy(RegionValStr[REGION1], linebuf);
              PrintOsdMsg(0, REGION1, 3, 1);             
            }
            else //if(setup_item_plus[page][index_y][1] == STR_OS_SETUP)
            {//enter setup menu!!!
                #ifdef DEBUG_FUNCTION_MENU
                printf("call setup menu function\n");
                #endif
                //退出菜单
                setup_menu_plus_timer = 0;

                //call function
                ircmd_setup();
            }
        }
        else if(setupLevel == 2)
        {//只有在LCD Mode下有效
            #ifdef DEBUG_FUNCTION_MENU
            printf("select and return,y:%d y2:%d\n",index_y,index_y2);
            #endif
             
              submenuStart = index_y+SETUP_MENU_YSTART_PLUS;
              sel = setup_sel_plus[page][index_y];
             
            //将之前选中的菜单项转为正常显示
              id = setup_item_plus[page][index_y][sel];
              #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
              osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, (sel-2)+submenuStart, SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SBGCOLOR, 0);
              #endif
              str = setup_SetItemString();
              osd_DrawString(SETUP_SUB_XSTART_PLUS+1, (sel-2)+submenuStart, (char *)str, SFONTCOLOR, SBGCOLOR);
              
              //将选中的菜单项反显以表示选中
              id = setup_item_plus[page][index_y][index_y2+2];
              #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
              osd_draw_setup_button(SETUP_SUB_XSTART_PLUS, (index_y2+submenuStart), SETUP_MAX_WIDTH_PLUS-SETUP_SUB_XSTART_PLUS, SANTIBGCOLOR, 1);
              #endif
              str = setup_SetItemString();
              osd_DrawString(SETUP_SUB_XSTART_PLUS+1, index_y2+submenuStart, (char *)str, SANTIFONTCOLOR, SANTIBGCOLOR);
            
            //We need to send special command to MCU,how to do it?
            //MPEG control or MCU control?
              setup_sel_plus[page][index_y] = index_y2 + 2;
              sel = setup_sel_plus[page][index_y];
            
              #ifdef SUPPORT_SPI
              if(sel == MIN_ITEM_SEL_PLUS)
                scommand = LCD_NORMAL_FORMAT;
              else if(sel == MIN_ITEM_SEL_PLUS+1)
                scommand = LCD_WIDE_FORMAT;
              /*
              else
                scommand = LCD_FULL_FORMAT;
              */
              #else
              if(setup_item_plus[page][index_y][0] == SET_FUNC)
                exe_setup_function(setup_item_plus[page][index_y][1],setup_item_plus[page][index_y][index_y2 + 2],1);
              #endif

            //return to the first menu
              setup_func_left();
            }  
    } //if((full_scrn&SETUP_PLUS) || (setup_menu_plus_timer))
    else
    {
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
    UINT8   md=setup_item[page][index_y][0];
        
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE
    if(main_setup)
    {
        bbk_sel_main_setup_menu();
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
    
#ifdef SUPPORT_FUNCTION_MENU
    #ifdef SUPPORT_SPI
    if (setup_item[page][index_y+index_y_start][0] == SET_SHOW) 
      return;
    #endif
#endif
    
#if defined(DVD_AUDIO)//20040302
    if(pDSV->hid_gp_chk_pwd==2)
    {
        check_dvd_audio_password();//nono 2004/3/2 05:40PM
              return; 
    }
#endif//#if defined(DVD_AUDIO)
    
    if(setupLevel==0)
    {
        #ifdef SETUP_DONGLI459          //oujx for tonic auto down when press select
        setup_func_down();
        #endif
        return;
    }
    else if (setupLevel == 1)
    {
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
        if(one_key_pass_flag)//zhaoyanhua add 2003-11-18 17:26
            sel = GetOneKeyPageSel(index_y);
        else
#endif
        sel=setup_sel[page][index_y+index_y_start];
        
        id=setup_item[page][index_y+index_y_start][1];

        if (id == STR_OS_RETURN_MAIN_SETUP)
        {
            if (full_scrn&CUSTM)
            {
                ExitSetupPage(1);
            }
            else 
            {
                #if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE
                main_setup = 1;

                if(index_x == ONE_KEY_PASS_X)
                    one_key_pass_flag = 0;
                
                 osd_init_bbk_setup();           
                ShowSetupMainPage();
                return;
                #endif
            
            #ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP            //gerry,2004-3-12 13:19
                sel_show_turnpage(id);
                return;
            #endif//NEXT_PAGE_SHOW_ADVANCED_SETUP

                ExitSetupPage(1);
            }
        }
        else
        #if defined(NEXTPAGE_SYS)       //freyman 2004-3-26 0:07
        if((id==STR_OS_NEXT_PAGE)||(id==STR_OS_PREV_PAGE))
        {
            sel_show_turnpage(id);
        }
        else
#endif      
        {
#ifdef VIDEO_SETUP_NEW_GUI//zhaoyanhua add 2004-1-8 17:03
        if(page == VIDEOPAGE)
        {   
            setupLevel = 2;
            setup_ShowVideoGUI(id);
        }
        else
#endif//VIDEO_SETUP_NEW_GUI

#if !defined(DVB_MENU_SETUP_STYLE)&&!defined(DVB_MENU_TYPE1)     //sunzhh 20050430
            setup_func_right();
#else
	{
		if(system_state == SYSTEM_TS)
		{
			//if((page == INSTALLPAGE)||(page == CHANNELPAGE))
			if(IsDvbSubMenuPageItem()) {
				setup_func_right();				
			}
			else
            {
                dvb_func_select();
                printf(" page = %d \n", page);
                return;
            }
		}
		else
        setup_func_right();
	}
#endif

        }
    }
    else if (setupLevel == 2)
    {
		
		#ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for NATIVE_GAME 2005-10-18 14:49
		extern int  DVB_SetGameType(BYTE uGameType);
		if(setup_item[page][index_y][1]==STR_OS_GAME)
		{
					
			if((play_state==VCD_STATE_STOP)||(system_state==SYSTEM_NODISC))
			{
				if(setup_item[page][index_y][index_y2+2]==STR_OS_GAME_BOXMAN)
				{
					DVB_SetGameType(DVB_GAME_BOXMAN);
				}
				else if(setup_item[page][index_y][index_y2+2]==STR_OS_GAME_TETRIS)
				{
					DVB_SetGameType(DVB_GAME_TETRIS);
				}
				else if(setup_item[page][index_y][index_y2+2]==STR_OS_GAME_HITRAT)
				{
					DVB_SetGameType(DVB_GAME_HITRAT);
				}
				ExitSetupPage(1);				
			}
		}
		#endif


#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD) //axel 2004/1/26 04:01 DSS555 need not OENKEYPASSPAGE         
        if(one_key_pass_flag)//OENKEYPASSPAGE
        {
            sel = GetOneKeyPageSel(index_y);
        }
        else
#endif
        sel=setup_sel[page][index_y];

        
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
                    #ifdef ORITRON_PARENTAL_PASSWORD //libing 2005-4-28 13:48
                    ||(tmp_passwd==DEFAULT_PASSWORD && op_parent_pwd_flag==1)
                    #endif
                    #ifdef USER_SUPER_PASSWORD
                    ||tmp_passwd==USER_SUPER_PASSWORD 
                    #endif
                    ))
                {
                    sel_func_lock_state();
                    #ifdef ORITRON_PARENTAL_PASSWORD //libing 2005-4-28 13:48
                    op_parent_pwd_flag = 0;
                    #endif
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
#ifdef  SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 16:18
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
                //SetOsdCol(mn_osd_col2);  //fengjl mask 2004-06-22 23:10
                #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-2 17:38
                SetOsdCol(mn_osd_col1);
                #endif
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
            
#ifdef  SETUP_PASSWORD_GUI//zhaoyanhua add 2004-1-15 14:43
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
            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
            osd_draw_setup_button(SETUP_SUB_XSTART, (sel-2)+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
            #endif
            str = setup_SetItemString();
            osd_DrawString(SETUP_SUB_XSTART+1, (sel-2)+submenuStart+1, (char *)str, SFONTCOLOR, SBGCOLOR);
            //DOWN current
            id = setup_item[page][index_y][index_y2+2];
            #ifndef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-4 15:39
            osd_draw_setup_button(SETUP_SUB_XSTART, (index_y2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
            #endif
                        
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
//              run_save_sel_cmd(CUSTMPAGEINDEX, CUSTMPASSWDITEM); 
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

		 #ifdef SUPPORT_SPI
         if(setup_item[page][index_y][1] == STR_OS_VIDEO)
         {
           switch(setup_item[page][index_y][sel])
           {
           case STR_OS_P_SCAN_YUV:
             tv_out_id = P_SCAN;
             
         
             if(pdvd_mode == AV_OUTPUT_MODE)
             {
               sp8200tv_setup_custom_output(TV_OUT_YBRYBR);
               //printf("in output mode and YPbPr ouput\n");
             }
             else
             {//just record
               //printf("in Pdvd mode and setup YPbPr ouput ,just record...\n");
             }
           break;
           case STR_OS_YCbCr:
             tv_out_id = INTERLACE;
           
             if(pdvd_mode == AV_OUTPUT_MODE)
             {
               sp8200tv_setup_custom_output(TV_OUT_YUVRGB);
               //printf("in output mode and YCbCr ouput\n");
             }
             else
             {//just record
               //printf("in Pdvd mode and setup YCbCr ouput,just record...\n");
             }
           break;
           case STR_OS_S_VIDEO:
             tv_out_id = TV_SVIDEO;
           
             if(pdvd_mode == AV_OUTPUT_MODE)
             {
               sp8200tv_setup_custom_output(TV_OUT_CScRGB);
               //printf("in output mode and SV/CVBS ouput\n");
             }
             else
             {//just record id!!!
               //printf("in Pdvd mode and setup SV/CVBS ouput,just record...\n");
             }
            break;
            }
            search_ap_tv_out_id();
         
            #ifdef STORE_VIDEO_PARAMETER
            res = WriteToI2c(0xa0, TV_OUT_ID_ADDR,(BYTE *)&tv_out_id,1);
            if(res<0)
            {
              BYTE i=0;
              for(i=0;((i<15)&&(res<0));i++)
              {
                res = WriteToI2c(0xa0, TV_OUT_ID_ADDR, (BYTE *)&tv_out_id, 1);
                printf("sel tv_out_id store error,retry.......i%d res:%d\n",i,res);
              }
            }
            #endif
          }  
          else if(setup_item[page][index_y][1] == STR_OS_TV_SYS)
          {
            switch(setup_item[page][index_y][sel])
            {
            case STR_OS_NTSC:
              tv_format=MODE_NTSC;
            break;
            #ifdef SUPPORT_PAL60
            case STR_OS_PAL60:
              tv_format=MODE_PAL60;
            break;
            #endif//SUPPORT_PAL60
            #ifdef SUPPORT_PALM         //gerry,2004-1-8 13:49
            case STR_OS_PALM:
              tv_format=MODE_PALM;
            break;
            #endif//SUPPORT_PALM
            case STR_OS_PAL:
              tv_format=MODE_PAL;
            break;
            #ifdef SUPPORT_PALN
            case STR_OS_PALN:
              tv_format=MODE_PALN;
            break;
            #endif//SUPPORT_PAL60
            #ifdef SUPPORT_PALNc
            case STR_OS_PALNc:
              tv_format=MODE_PALNC;
            break;
            #endif//SUPPORT_PAL60
            #ifdef SUPPORT_PALNc
            case STR_OS_PALNc:
              tv_format=MODE_PALNC;
            break;
            #endif//SUPPORT_PAL60
            case STR_OS_AUTO:
              tv_format=MODE_AUTO;
            break;
            }
            
            #ifdef STORE_VIDEO_PARAMETER
            res = WriteToI2c(0xa0, TV_FORMAT_ADDR,(BYTE *)&tv_format,1);
            if(res<0)
            {
              BYTE i=0;
              for(i=0;((i<15)&&(res<0));i++)
              {
                res = WriteToI2c(0xa0, TV_FORMAT_ADDR, (BYTE *)&tv_format, 1);
                printf("tv_out_id store error,retry.......i%d res:%d\n",i,res);
              }
            }
            //printf("record tv_format:%d.....\n",tv_format);
            #endif
            setup_tv_format(tv_format);
            update_tv_format_sel();
          } 
          else
          #endif
                exe_setup_function(setup_item[page][index_y][1],setup_item[page][index_y][sel],1);
                #ifdef SELECT_MEDIA_IN_SETUPMENU    //Maoyong force to exit setup after media switch 2004-8-10 11:28
                if(media_changed_flag){
                    media_changed_flag = 0;
                    return;
                }
                #endif

                #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL //wangap add this for current in setup 2004/5/9
                if(setup_item[page][index_y][1]==STR_OS_TV_SYS){
                osd_init_setup();
                ShowSetupPage(2);
                }
                #endif//SETUP_ADJUST_LOCATION_WHEN_PAL
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

#ifdef VGA_CTRL_FORMAT  //wangfeng,2003-10-20 22:47
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

#ifdef  SCART_TV_5  //wangfeng 2003-12-2 11:43 for himage HJ-023 
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

	#ifdef DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF //zxb 2005-5-8 13:05
        if(page == AUDPAGE)		
			ShowSetupPage(AUDPAGE);
	#endif //DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF	

        if (id==STR_OS_DEFAULT_SETUP)
        {
			#ifdef DVB_MENU_SETUP_STYLE     //sunzhh add 2005-3-17
			if(system_state == SYSTEM_TS)
			{
			    if(user_mute)
		{
			user_mute=0;
			rem_osd_id=STR_OS_SPACE; //added by liuchuanyi 05/04/21
		}
                run_pause(0);  
            }                  
			#endif            
            #if (defined(SAVE_AMP_VOLUME)||defined(SUPPORT_SAVE_AMPLIFIER_STATUS))&& defined(TESTSPK_CONTROL_VOL)&& defined(SUPPORT_SETUP_POPUP_TESTSPK_GUI)
            reset_amp_variable();
            #endif
            set_default_value();
            run_set_variable();
#if defined(YUV_DEFAULT_OUTPUT) && defined(DELETE_VIDEO_ITEM)
        #ifdef S_VIDEO_OUT
       regs0->emu_cfg[1]|=0x100;
        #endif //#ifdef S_VIDEO_OUT
        setup_tv_out(INTERLACE);//set S-video output(composited+component)(0x00:D0-D1-D2-D3=CVBS-V-Y-U)
        search_ap_tv_out_id();//terry,2003/8/19 03:21PM
#endif      

#ifdef YUXING_MIDI_DVD 
        exe_setup_function( STR_OS_SELECT_LOGO, STR_OS_RESTORE_SETUP, 0 );//nono 2004-10-23 15:07
#endif
        
            run_save_total_sel();
#ifdef EASTWIN
			load_customer_default();
			init_lcd_display_mode();
			init_an2526h();				// Kevin Sep 20,04 
#endif             

            #if defined(DELETE_VIDEO_ITEM)&&defined(SYBER_DVD)//liweihua add 20031218
            page=0;
            #endif
			
			#ifdef DVB_MENU_SETUP_STYLE
			if(system_state ==SYSTEM_TS)
				page = SYSPAGE;
			else
				page = SYSPAGE;
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
//          exe_setup_function(setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][1],
//                  setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][ SETUP_SPK_DOWNMIX ],0);//nono 2003-8-26 0:50

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
            AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
            #endif
            #endif //#ifdef VOLUME_RECODE


       
//3-12-23 21:02 NONO for dts-cd
        setup_SetDTSDOWNMIXConfig();
            //nono 2003-8-26 1:42 for DTS mute after setup_default
//          exe_setup_function(setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][1],
//                  setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][ SETUP_SPK_DOWNMIX ],0);//nono 2003-8-26 0:50

       

#ifndef SETUP_DONT_PAUSE    // alan, 3-8-5 17:47
#ifdef  SETUP_DEFAULT_DONT_PAUSE  
//terry,2003/12/12 04:16PM
//bbk ,empty
#else
		#ifdef DVB1000_NON_OS
		if(system_state != SYSTEM_TS)
		#endif
            AUDIF_Set_Pause();//2004AUDDRV AudioSetPause(); //Jeff 20021017
#endif          
#endif

#ifdef DVB_MENU_SETUP_STYLE     //sunzhh add 2005-3-17
    if(system_state == SYSTEM_TS)
    {
        //int i;
   		//for(i=0;i<2;i++)
   		//    memset( (BYTE *) (SDRAM_BASE + DEMUX_VIDEO_START * 1024), 0, (DEMUX_VIDEO_SZ + DEMUX_AUDIO_SZ) * 1024);
   		AVD_SetMediaTimeout();
   		//flush_cdif();
   		//restart_video_engine();
   		//restart_audio_engine();        
        ircmd_play();
		rem_osd_id=STR_OS_SPACE; //added by liuchuanyi 05/04/21
    }
#endif                

          #ifdef ARGUS_PORTABLE_DVD
          #ifdef SUPPORT_SPI
          scommand = MCU_RESET;
          #endif
           #endif
        } //if (id==STR_OS_DEFAULT_SETUP)
    }
    #ifdef SUPPORT_FUNCTION_MENU
    }
    #endif //end #ifdef SUPPORT_FUNCTION_MENU
}

#ifdef DVB_MENU_SETUP_STYLE
void dvb_func_select()
{
		if(system_state == SYSTEM_TS)
		{
			if((page == INSTALLPAGE)||(page == CHANNELPAGE))
			{
				switch(id)
				{
					case STR_OS_DVBT_CONFIG:
						ShowDvbTInstMenu();
						break;
					case STR_OS_AUTO_SCAN:
						break;
					case STR_OS_TV_CHANNEL:
						dvb_channel_func_select(STR_OS_TV_CHANNEL);
						break;
					case STR_OS_RADIO_CHANNEL:
						dvb_channel_func_select(STR_OS_RADIO_CHANNEL);
						break;
					//case STR_OS_EDIT_LIST:
					//	break;
					case STR_OS_ADD_CHANNEL:
						ShowDvbAddChannels();
						break;
					case STR_OS_EDIT_CHANNEL:
						break;
					case STR_OS_DEL_CHANNEL:
						dvb_channel_func_select(STR_OS_DEL_CHANNEL);
						break;
                                  #ifdef SUPPORT_DVB_TIMER//kehw 2005-04-15
                                   case STR_OS_TIME_ZONE://kehw timer
						ShowDvbTimerSettingMenu();
                                          break;
                                   #endif       
					case STR_OS_LOCK_CHANNEL:   //haoy add 2005-04-18 for lock channel
						dvb_channel_func_select(STR_OS_LOCK_CHANNEL);
						break;
				}
				
			}
		}
}		
#endif

#if defined(DVB_MENU_TYPE1)    //sunzhh copy for dvb temporary use
void dvb_func_select()
{
		if(system_state == SYSTEM_TS)
		{
			if((page == INSTALLPAGE)||(page == CHANNELPAGE))
			{
				switch(id)
				{
					case STR_OS_DVBT_CONFIG:
						ShowDvbTInstMenu();
						break;
					case STR_OS_AUTO_SCAN:
						break;
					case STR_OS_TV_CHANNEL:
					    printf("------------dvb_channel_func_select(STR_OS_TV_CHANNEL)----------\n");
						//dvb_channel_func_select(STR_OS_TV_CHANNEL);
						break;
					case STR_OS_RADIO_CHANNEL:
					    printf("------------dvb_channel_func_select(STR_OS_RADIO_CHANNEL)----------\n");				
						//dvb_channel_func_select(STR_OS_RADIO_CHANNEL);
						break;
					//case STR_OS_EDIT_LIST:
					//	break;
					case STR_OS_ADD_CHANNEL:
					    printf("------------ShowDvbAddChannels()----------\n");					
						//ShowDvbAddChannels();
						break;
					case STR_OS_EDIT_CHANNEL:
						break;
					case STR_OS_DEL_CHANNEL:
					    printf("------------dvb_channel_func_select(STR_OS_DEL_CHANNEL)----------\n");				
						//dvb_channel_func_select(STR_OS_DEL_CHANNEL);
						break;
				}
				
			}
		}
}		
#endif//#if defined(DVB_MENU_TYPE1)



