/***************************************************************
*  setup_get_pos.c
*  include  in setup_tab_ui1.c   when defined DVD_SETUP_REENG
* 
* Creator: 	JSLin 
* Date:  		2004/07/28
*
* Description :	
*			setup menu navigator, 
*			locate new position in setup menu according to
*			1. current position 	
*			2. moving direction (IR_cmd/user input)
*
****************************************************************/

#ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for NATIVE GAME 2005-10-19 16:20
#include "..\fbuf_game\Fbuf_game_Macro_Def.h"
#endif

void setup_GetPos(UINT8 direction);
void setup_GetPosL0(UINT8 direction);
void setup_GetPosL1(UINT8 direction);
void setup_GetPosL2(UINT8 direction);
void setup_GetPosL3(UINT8 direction);
void setup_GetPosCUS(UINT8 direction); //for custm page
UINT8 setup_getItemSelect(UINT8 setup_itemStr , UINT8 setup_itemVA);//zxb 2005-05-17
extern char Clean_DRM_Web;  //helm for clean DIVX web site, 050825
extern void setup_Clean_DIVX_Web(void);

#ifdef EASTECH_DVD_DP2070_D
extern UINT8 ShowingWarningMessage;  //huhu
#endif

#ifdef POP_PAL_N_WARNING
UINT8 pop_pal_n_ui_flag = 0;
UINT8 is_ntsc_pos_on = 0;
UINT8 is_pal_pos_on = 0;
#endif

#ifdef AUTO_LOAD_MODE_SETUP //denghg add 2005-11-18 07:59     
int forcedefault=0;
void refresh_CUSTM_setup(void);
extern void display_custm_menu(void);
#endif


#ifdef SCALER_6500 //helm for NTSC <--> PAL with scaler 050727
#ifdef Simplay_warning	//eric lin,2006-07-04,for Simplay format warning message
int hdmi_lastpos;//eric lin
#endif	//#ifdef Simplay_warning 
#ifdef HDMI_FMT_RESTORE
       BYTE pre_TVA, pre_fmtVA;
#endif

extern BYTE YCbCr,YPbPr;

void Check_PSCAN_INTERLACE(void)
{
	if (setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]] == STR_OS_VIDEO)
	{
                     if (setup_VA[SETUP_VA_VIDEO] == YCbCr){
                         regs0->sft_cfg20 = 0x00;
                         regs0->sft_cfg19 = 0x0001;
                     }
                                          
                     if (setup_VA[SETUP_VA_VIDEO] == YPbPr){
                         regs0->sft_cfg20 = 0x8000;
                         regs0->sft_cfg19 = 0x0001;	
                     }
        }             		
}
#endif

void setup_GetPos(UINT8 direction)
{

	//printf("setup_GetPos	dir:%d\n", direction);
	//record last position
	setup_last_pos[SETUP_ML0] = setup_pos[SETUP_ML0];
	setup_last_pos[SETUP_ML1] = setup_pos[SETUP_ML1];
	setup_last_pos[SETUP_ML2] = setup_pos[SETUP_ML2];
	setup_last_pos[SETUP_ML3] = setup_pos[SETUP_ML3];

	setup_VA2sel();

    #ifdef SUPPORT_SETUP_POPUP_GUI//added by chenzhao 20050524
    SETUPGUI_TYPE old_setup_gui_state=setup_gui_state;

#ifdef EASTECH_DVD_DP2070_D
    if(ShowingWarningMessage ==1 ) // mimitsai
        setup_gui_state = SETUPGUI_PSCAN_WARNING;
#endif
	if(SETUPGUI_MENU!=setup_gui_state)
    {
        setup_GetPos_PopUp(direction);
    }
    else
    #endif//SUPPORT_SETUP_POPUP_GUI
	if(full_scrn&CUSTM)
	{
		//printf("custm page\n");
		setup_GetPosCUS(direction);
	}
	else	
	{
		switch(setup_pos[SETUP_ML0])	//switch by setup_level
		{
			case SETUP_ML0:
				setup_GetPosL0(direction);
				break;
			case SETUP_ML1:
				setup_GetPosL1(direction);	
				break;
			case SETUP_ML2:
				setup_GetPosL2(direction);
				break;
			case SETUP_ML3:
				setup_GetPosL3(direction);
				break;
		}
	}
	
	//page = setup_pos[setup_L1];
	//printf("\n\n================================\n");
	//printf("direction:%d	setup_level:%d	last_level:%d\n", direction, setup_pos[0], setup_last_pos[0]);
	//printf("setup_last_pos		%d %d %d\n", setup_last_pos[1], setup_last_pos[2], setup_last_pos[3]);
	//printf("setup_pos		%d %d %d\n\n", setup_pos[1], setup_pos[2], setup_pos[3]);
	//printf("==================================\n\n");
	#ifdef SUPPORT_TVG
	#include "TVGapp.h"
	if(setup_pos[1]==5&&setup_pos[2]==7&&setup_pos[3]==0&&direction==SETUP_SELECTION)
	{
		if(MessageBox_TVGHelp())
		{
			setup_pos[2] = 0;setup_pos[3] = 0;setup_pos[0] = 1;
			setup_last_pos[0] = 1;setup_last_pos[1] = 0;setup_last_pos[2] = 0;setup_last_pos[3] = 0;
			setup_ShowPageL2();
			return;
		}
	}
	#endif
	
	//show setup page via OSD
	#ifdef AFTER_DEFAULT_LOAD_RESET
	if((setup_pos[0]!=0) && full_scrn) 
	#else
	if(setup_pos[0] != 0) 
	#endif
	{
        #ifdef SUPPORT_SETUP_POPUP_GUI//added by chenzhao 20050524
        if(SETUPGUI_MENU == setup_gui_state)
        {
            if(SETUPGUI_MENU != old_setup_gui_state)
                ShowSetupPage(1);//refresh setup menu
            else
		setup_ShowPage();
        }
        #else
		if(full_scrn & SETUP)//Jack added 05/11/18.I think it is very important!
		    setup_ShowPage();
        #endif//SUPPORT_SETUP_POPUP_GUI
		//run_save_sel_cmd(setup_pos[1], setup_pos[2]);
	}

}//end of setup_GetPos
//======================================================================


void setup_GetPosL0(UINT8 direction)
{
	switch(direction)
	{
		case SETUP_ENTER:
			setup_mLevel = SETUP_ML1;
			setup_pos[SETUP_ML0] = setup_mLevel; 
			setup_pos[SETUP_ML1] = 0;
			setup_pos[SETUP_ML2] = 0;//MAX_PAGE_ITEM;
			setup_pos[SETUP_ML3] = 0;
			break;
		case SETUP_UP:
		case SETUP_DOWN:
		case SETUP_LEFT:
		case SETUP_RIGHT:
		case SETUP_SELECTION:
			break;
	}

}
//======================================================================


void setup_GetPosL1(UINT8 direction)
{
	UINT8 itemType, iDo;
	
	switch(direction)
	{
		case SETUP_ENTER:
			setup_mLevel = SETUP_ML0;
			setup_pos[SETUP_ML0] = setup_mLevel;
			setup_pos[SETUP_ML1] = 0;
			setup_pos[SETUP_ML2] = 0;
			setup_pos[SETUP_ML3] = 0;
			break;
        //#ifdef SOFT_MENU_REENG//chenzhao 20050520
        #if defined(SOFT_MENU_REENG)||defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
		case SETUP_LEFT:
			break;
        #else//SOFT_MENU_REENG
		case SETUP_UP:
			setup_mLevel = SETUP_ML2;
			#if defined(SCALER_6500)&&defined(ORITRON_HK_DVD)
			UINT8 itemMode;//libing 
			itemMode = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][2];			
			if(tv_format==MODE_NTSC && setup_item[setup_pos[SETUP_ML1]][0][1]==STR_OS_VIDEO_SETUP)
				setup_pos[SETUP_ML2] = MAX_PAGE_ITEM - 4;//-1;
			else
			#endif
			setup_pos[SETUP_ML2] = MAX_PAGE_ITEM;//-1;

			do
			{
				itemType = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][0];
				if(((itemType == SET_NE)||(itemType == SET_SPACE)
                    #ifdef USE_SETUP_ITEM_ENABLE_FLAG //chenzhao 2006-6-24 15:0 .Avoid goto invaild item when moving from level 1 to level 2.
                    ||((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1])
                      &&(0==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1]]))
                    #endif
                    )&&(setup_pos[SETUP_ML2] > 0))
				{
					setup_pos[SETUP_ML2]--;
					iDo = 1;
				}
				else
				{
					iDo = 0;
				}
			}while(iDo);
			
			if(setup_pos[SETUP_ML2] == 0){
				setup_mLevel = SETUP_ML1;
			}
			setup_pos[SETUP_ML0] = setup_mLevel;
			break;
        #endif//SOFT_MENU_REENG
        //#ifdef SOFT_MENU_REENG//chenzhao 20050520
        #if defined(SOFT_MENU_REENG)||defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
		case SETUP_RIGHT:
        #else//SOFT_MENU_REENG
		case SETUP_DOWN:
        #endif//SOFT_MENU_REENG
			setup_mLevel = SETUP_ML2;
			setup_pos[SETUP_ML2] = 1;

			do
			{
				itemType = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][0];
				if(((itemType == SET_NE)||(itemType == SET_SPACE)
                    #ifdef USE_SETUP_ITEM_ENABLE_FLAG //chenzhao 2006-6-24 15:0 .Avoid goto invaild item when moving from level 1 to level 2.
                    ||((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1])
                      &&(0==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1]]))
                    #endif
                    )&&(setup_pos[SETUP_ML2] <= MAX_PAGE_ITEM))
				{	
					setup_pos[SETUP_ML2]++;
					iDo = 1;
				}
				else
				{
					iDo = 0;
				}
			} while(iDo);
			
			if(setup_pos[SETUP_ML2] > MAX_PAGE_ITEM){
				setup_mLevel = SETUP_ML1;
				setup_pos[SETUP_ML2] = 0;
			}

			setup_pos[SETUP_ML0] = setup_mLevel;
			break;
        //#ifdef SOFT_MENU_REENG//chenzhao 20050520
        #if defined(SOFT_MENU_REENG)||defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
		case SETUP_UP:
        #else//SOFT_MENU_REENG
		case SETUP_LEFT:
        #endif//SOFT_MENU_REENG
			if(setup_pos[SETUP_ML1]>=setup_max_icon)
			{
				setup_pos[SETUP_ML1] = setup_item[setup_pos[1]][0][2];
			}
			if(setup_pos[SETUP_ML1] == 0)
			{
				setup_pos[SETUP_ML1] = setup_max_icon;
			}
			setup_pos[SETUP_ML1] --;
			
			#ifdef TWO_CHANNEL_ONLY  //denghg  add  for define two channel  2005-2-26 11:11
			if(setup_item[setup_pos[1]][0][1]==STR_OS_SPK_SETUP)
			setup_pos[SETUP_ML1] --;
			#endif		
			break;
        //#ifdef SOFT_MENU_REENG//chenzhao 20050520
        #if defined(SOFT_MENU_REENG)||defined(NGAILIK_MENU)	//liudan add for 1006 setup menu.
		case SETUP_DOWN:
        #else//SOFT_MENU_REENG
		case SETUP_RIGHT:
        #endif//SOFT_MENU_REENG
			if(setup_pos[SETUP_ML1]>=setup_max_icon)
			{
				setup_pos[SETUP_ML1] = setup_item[setup_pos[1]][0][2];
			}
			setup_pos[SETUP_ML1]++;
			
			#ifdef TWO_CHANNEL_ONLY   //denghg  add  for define two channel 2005-2-26 11:11
			if(setup_item[setup_pos[1]][0][1]==STR_OS_SPK_SETUP)
			setup_pos[SETUP_ML1] ++;
			#endif
			
			if(setup_pos[SETUP_ML1] >= setup_max_icon)//libing 2005-5-20 11:23 "=="  --> ">="
			{
				setup_pos[SETUP_ML1] = 0;
			}
			break;
		case SETUP_SELECTION:
			break;
	}
}
//======================================================================
#ifdef ALCO_SHOW_DRM_REGISTRATION_CODE_IN_SETUP//shenyj add for alco 2006-8-29 04:21下午
extern int  osd_divx_drm_display( int iPage, int iCode );
extern BYTE rem_osd_id ;
#endif
void setup_GetPosL2(UINT8 direction)
{
	UINT8 itemType, iDo;
	
	switch(direction)
	{
		case SETUP_ENTER:
			setup_mLevel = SETUP_ML0;
			setup_pos[SETUP_ML0] = setup_mLevel;
			setup_pos[SETUP_ML1] = 0;
			setup_pos[SETUP_ML2] = 0;
			setup_pos[SETUP_ML3] = 0;
			break;
			
		case SETUP_UP:

#ifdef DRM_CODE		
		        if (Clean_DRM_Web){ //helm for clean DIVX web site 050825
		            Clean_DRM_Web = 0;
		            setup_Clean_DIVX_Web();
		        }
#endif		        		
			#ifdef SUPPORT_TVG			//linrc add 2005-12-15 15:52
			#ifdef SETUP_EXTENSION_TABLE
			if(setup_item[setup_pos[1]][setup_pos[2]][0]==SET_SHOW_EX2)
			{
				extern unsigned char GetTVGMode(void); 
				printf( "GetTVGMode %d\n", GetTVGMode() );
				if(!GetTVGMode())
				{
					if(setup_pos[SETUP_ML2]==7 )//&& setup_pos[SETUP_ML2]<=6)
					{
						setup_pos[SETUP_ML2] = 2;
					}
				}
			}
			#endif
			#endif
			
			setup_pos[SETUP_ML2]--;

			do
			{
				itemType = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][0];
				if(((itemType == SET_NE)||(itemType == SET_SPACE)
                    #ifdef USE_SETUP_ITEM_ENABLE_FLAG//added by chenzhao on 2005-3-31 16:6  
                    ||((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1])
                      &&(0==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1]]))

                    #ifdef SUPPORT_HD_RESOLUTION
                    ||((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1])
                      &&(2==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1]]))                      
                    #endif

                    #endif
				) && (setup_pos[SETUP_ML2] > 0))
				{
					setup_pos[SETUP_ML2]--;
					iDo = 1;
				}
				else
				{
				   #if defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH) ||defined(DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF)  //zxb 2005-5-11            	
            	    UINT16 P, I;                               
            	    switch ( setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] )
            	    {   
            	    #ifdef GRAY_SUBW_BSMODE_DELAY_IN_2CH
            	        case STR_OS_SUBWOOFER :
            	        case STR_OS_BASS_MANAGEMENT :
            	        case STR_OS_CSPK_DELAY :
            	        case STR_OS_SSPK_DELAY :
            	            P=setup_getItemPos(STR_OS_DOWNMIX_SETUP);
                            I=P&0xff;
                            P=P>>8;
                        #ifdef DOWNMIX_OFF_DISP_5CH_ON
            	            if( (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]!=STR_OS_5CH_ON) )            	   
            	        #else
            	            if( (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]!=STR_OS_OFF) )       
            	        #endif
            	            {
            	                setup_pos[SETUP_ML2]--;
					            iDo = 1;
					        }
					        else
					        {
					iDo = 0;
				}
            	            break;
            	    #endif //GRAY_SUBW_BSMODE_DELAY_IN_2CH           	            
            	    #ifdef DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF
            	        case STR_OS_ECHO :
            	        case STR_OS_MIC_VOL :  
            	            P=setup_getItemPos(STR_OS_MIC_ONOFF);
                            I=P&0xff;
                            P=P>>8;
            	            if( (setup_item[P][I][setup_VA[SETUP_VA_MIC_ONOFF]]==STR_OS_OFF) )          	        
				{
					setup_pos[SETUP_ML2]--;
					iDo = 1;
				}
				else
				{
					iDo = 0;
				}
            	            break;
            	     #endif //DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF   
            	        default:
            	     #endif //defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH) ||
        	                //defined(DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF)
                            //#ifdef SOFT_MENU_REENG//chenzhao 20050520
                            #if defined(SOFT_MENU_REENG)||defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
                            if(setup_pos[SETUP_ML2] == 0)
                            {
                                setup_pos[SETUP_ML2]=MAX_PAGE_ITEM;
                                iDo = 1;
                            }
                            else
            	            iDo = 0;
                            #else//SOFT_MENU_REENG
            	            iDo = 0;
                            #endif//SOFT_MENU_REENG
            	     #if defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH) ||defined(DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF)  //zxb2005-5-11
            	            break;
            	    }       
            	    #endif
            	    
				}
			}while(iDo);

            #ifndef SOFT_MENU_REENG//chenzhao 20050520
			if(setup_pos[SETUP_ML2] == 0){
				setup_mLevel = SETUP_ML1;
			}

			setup_pos[SETUP_ML0] = setup_mLevel;
            #endif//SOFT_MENU_REENG
            
			break;
			
		case SETUP_DOWN:

#ifdef DRM_CODE		
		        if (Clean_DRM_Web){ //helm for clean DIVX web site 050825
		            Clean_DRM_Web = 0;
		            setup_Clean_DIVX_Web();
		        }
#endif	
			#ifdef SUPPORT_TVG
			#ifdef SETUP_EXTENSION_TABLE
			if(setup_item[setup_pos[1]][setup_pos[2]][0]==SET_FUNC_EX)
			{
				if(!GetTVGMode())
				{
					if(setup_pos[SETUP_ML2]>=1 && setup_pos[SETUP_ML2]<=6)
					{
						setup_pos[SETUP_ML2] = 6;
					}
				}
			}
			#endif
			#endif
		
			setup_pos[SETUP_ML2]++;						

			do
			{
				itemType = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][0];
				if(((itemType == SET_NE)||(itemType == SET_SPACE)
                    #ifdef USE_SETUP_ITEM_ENABLE_FLAG//added by chenzhao on 2005-3-31 16:6  
                    ||((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1])
                      &&(0==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1]]))

                    #ifdef SUPPORT_HD_RESOLUTION
                    ||((SETUP_VA_NONE!=setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1])
                      &&(2==setup_VA_EN[setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][MAX_ITEM_SEL+1]]))                      
                    #endif         

                    #endif
				) && (setup_pos[SETUP_ML2] <= MAX_PAGE_ITEM))
				{
					setup_pos[SETUP_ML2]++;
					iDo = 1;	
				}
				else
				{
				    #if defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH) ||defined(DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF)  //zxb 2005-5-11                	
            	    UINT16 P, I;                               
            	    switch ( setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] )
            	    {   
            	    #ifdef GRAY_SUBW_BSMODE_DELAY_IN_2CH
            	        case STR_OS_SUBWOOFER :
            	        case STR_OS_BASS_MANAGEMENT :
            	        case STR_OS_CSPK_DELAY :
            	        case STR_OS_SSPK_DELAY :
            	            P=setup_getItemPos(STR_OS_DOWNMIX_SETUP);
                            I=P&0xff;
                            P=P>>8;
                        #ifdef DOWNMIX_OFF_DISP_5CH_ON
            	            if( (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]!=STR_OS_5CH_ON) )            	   
            	        #else
            	            if( (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]!=STR_OS_OFF) )       
            	        #endif
            	            {
            	                setup_pos[SETUP_ML2]++;
					            iDo = 1;
					        }
					        else
					        {
					            iDo = 0;
					        }	
            	            break;
            	    #endif //GRAY_SUBW_BSMODE_DELAY_IN_2CH           	            
            	    #ifdef DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF    
            	        
            	        case STR_OS_ECHO :
            	        case STR_OS_MIC_VOL :  
            	            P=setup_getItemPos(STR_OS_MIC_ONOFF);
                            I=P&0xff;
                            P=P>>8;
            	            if( (setup_item[P][I][setup_VA[SETUP_VA_MIC_ONOFF]]==STR_OS_OFF) )          	        
				{
					setup_pos[SETUP_ML2]++;
					iDo = 1;	
				}
				else
				{
					iDo = 0;
				}
            	            break;
            	        #endif //DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF   
            	        default:
            	     #endif //defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH) ||
        	                //defined(DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF)
                     //#ifdef SOFT_MENU_REENG//chenzhao 20050520
                     #if defined(SOFT_MENU_REENG)||defined(NGAILIK_MENU)    //liudan add for 1006 setup menu.
                     if(setup_pos[SETUP_ML2] > MAX_PAGE_ITEM)
                     {
                         setup_pos[SETUP_ML2]=1;
                         iDo = 1;
                     }
                     else
						iDo = 0;
                     #else//SOFT_MENU_REENG
						iDo = 0;
                     #endif//SOFT_MENU_REENG
            	     #if (defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH)||defined(DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF))  //zxb 2005-5-11
            	            break;
            	    }       
            	    #endif
				}
			}while(iDo);

            #ifndef SOFT_MENU_REENG//chenzhao 20050520
            #if 0//def SCALER_6500//LIBING 2005-11-23 20:50
            itemType = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1];
            itemMode = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][2];
            #endif
			if((setup_pos[SETUP_ML2] > MAX_PAGE_ITEM)
			#if defined(SCALER_6500)&&defined(ORITRON_HK_DVD)   
               ||(tv_format==MODE_NTSC && itemMode==STR_OS_480P576P)//libing 
            #endif
            )
			{
				setup_mLevel = SETUP_ML1;
				setup_pos[SETUP_ML2] = 0;
			}

			setup_pos[SETUP_ML0] = setup_mLevel;
            #endif//SOFT_MENU_REENG
            
			break;
			
		case SETUP_LEFT:
            //#ifdef SOFT_MENU_REENG//chenzhao 20050520
            #if defined(SOFT_MENU_REENG)||defined(NGAILIK_MENU)	   //liudan add for 1006 setup menu.
			setup_mLevel = SETUP_ML1;
            setup_pos[SETUP_ML2] = 0;
			setup_pos[SETUP_ML0] = setup_mLevel;
            #endif//SOFT_MENU_REENG

 
			break;
			
		case SETUP_RIGHT:
			itemType = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][0];
			switch(itemType)
			{
				case SET_FUNC: 
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
				case SET_FUNC_EX: 
#endif
					id = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1];
					if( ( (id == STR_OS_RATING) && (UserSet.parental_ststus == C_LOCK) ) 
#ifdef DRM_CODE					
					    || (id == STR_OS_DRM_REGISTRATION_CODE)
#endif
					) //WSLEE for can show drm code, but can't select it 050615					
					{
					#if (defined(SUPPOT_SETUP_POPUP_PASSWORD_GUI) && defined(NEW_SOFT_PASSWORD_UI))
                    setup_gui_state=SETUPGUI_PASSWORD;
                    passwordstate=PASSWORDS_INPUT_INIT;
                    ShowSetupPassword("");
                    #endif
					}
					else
					{
						setup_mLevel = SETUP_ML3;
						setup_pos[SETUP_ML3] = setup_sel[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]];
						setup_pos[SETUP_ML0] = setup_mLevel;
					}
					break;		
				case SET_SCALE:
                #ifndef SUPPOT_SETUP_POPUP_PASSWORD_GUI//chenzhao20050531//chenzhao20050526
				case SET_NM:
					#ifdef  FIX_PSAAWORD_BUG
					  digit_cnt = 0;
					#endif//end=>  #ifdef  FIX_PSAAWORD_BUG
                #endif//#ifndef SUPPOT_SETUP_POPUP_PASSWORD_GUI
					reset_passwd_cnt();
					setup_mLevel = SETUP_ML3;
					setup_pos[SETUP_ML3] = setup_sel[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]];
					setup_pos[SETUP_ML0] = setup_mLevel;
					break;							
			}
			break;
			
		case SETUP_SELECTION:
			itemType = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][0];
			switch(itemType)
			{
				case SET_FUNC: 
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
				case SET_FUNC_EX: 
#endif
					id = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1];
					if( ( (id == STR_OS_RATING) && (UserSet.parental_ststus == C_LOCK) )
#ifdef DRM_CODE					
					    || (id == STR_OS_DRM_REGISTRATION_CODE)
#endif
					) //WSLEE for can show drm code, but can't select it 050615					
					{//liumzh 2005-6-1 16:03
					#if (defined(SUPPOT_SETUP_POPUP_PASSWORD_GUI) && defined(NEW_SOFT_PASSWORD_UI))
                    setup_gui_state=SETUPGUI_PASSWORD;
                    passwordstate=PASSWORDS_INPUT_INIT;
                    ShowSetupPassword("");
                    #endif
					
					}
					else
					{
						setup_mLevel = SETUP_ML3;
						setup_pos[SETUP_ML3] = setup_sel[setup_pos[1]][setup_pos[2]];
						setup_pos[SETUP_ML0] = setup_mLevel;
					}
					break;
				case SET_NM:
                    #ifdef SUPPOT_SETUP_POPUP_PASSWORD_GUI//chenzhao20050531//chenzhao20050526
                    setup_gui_state=SETUPGUI_PASSWORD;
                    passwordstate=PASSWORDS_INIT;
                    ShowSetupPassword("");
                    #endif//#ifdef SUPPOT_SETUP_POPUP_PASSWORD_GUI
					#ifdef  FIX_PSAAWORD_BUG
					  digit_cnt = 0;
					#endif//end=>  #ifdef  FIX_PSAAWORD_BUG

				case SET_SCALE:
					setup_mLevel = SETUP_ML3;
					setup_pos[SETUP_ML3] = setup_sel[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]];
					setup_pos[SETUP_ML0] = setup_mLevel;
					break;	
				case SET_SH:
					if(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] == STR_OS_EXIT_MENU)
					{
						setup_ExitPage();
					}
                    #ifdef ALCO_SHOW_DRM_REGISTRATION_CODE_IN_SETUP   //shenyj move here for alco 2006-8-29 04:16下午
                    else if(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] == STR_OS_DRM_REGISTRATION_CODE)
                    {
                        if((( cd_type_loaded == CDROM ) && (GetCurrentFileType()== CDROM_MP4) ) ||
                        		(system_state == SYSTEM_STOP) ||
                        		(system_state == SYSTEM_OPEN) ||
                        		(system_state == SYSTEM_NODISC) )
                        {                            
                            rem_osd_id = 0 ;//shenyj add for "OSD 花掉的问题"2006-9-6 04:12下午
                            setup_ExitPage();
						  if((system_state == SYSTEM_STOP) ||
                        		(system_state == SYSTEM_OPEN) ||
                        		(system_state == SYSTEM_NODISC) )
						    {
						     LoadModual(MODUAL_WMA);
                        	 LoadModual(MODUAL_MP4);
                        	}
                            if(play_state == VCD_STATE_NORMAL) 
                                    ircmd_pause(); 
                                    osd_init();                                     
                                   osd_divx_drm_display(1,0); 
                        }
					     else
					     {
					        rem_osd_id = 0 ;//shenyj add 2006-9-6 04:12下午
					     	setup_ExitPage();
					        if(play_state == VCD_STATE_NORMAL) 
                                ircmd_pause();
                                osd_init();
					        osd_divx_drm_display(1,0); //WSLEE
					     }
                    }
                    #endif//#ifdef ALCO_SHOW_DRM_REGISTRATION_CODE_IN_SETUP   //shenyj move here for alco 2006-8-29 04:16下午
                    #if defined(SUPPORT_SETUP_POPUP_TESTSPK_GUI)
                    else if(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] == STR_OS_TESTSPK_MENU)
                    {
                        setup_gui_state=SETUPGUI_TESTSPK;
                        Set_Testspk_Channel_GUI(SETUPGUI_TESTSPK_INIT);
                    }
                    #endif//#ifdef TESTSPK_IN_SETUP
 					break;
				case SET_LINK:
					setup_mLevel = SETUP_ML1;
					setup_pos[SETUP_ML0] = setup_mLevel;
					setup_pos[SETUP_ML1] = setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][2];
					setup_pos[SETUP_ML2] = 0;
					setup_pos[SETUP_ML3] = 0;
					break;
			}
			break;
	}
}
//======================================================================


void setup_GetPosL3(UINT8 direction)
{
        UINT8 iDo;
        
	#ifdef Simplay_warning	//eric lin,2006-07-06,for Simplay format warning message
        hdmi_lastpos= setup_sel[3][5];//eric lin,base on HDMI_OUTPUT location.
	#endif	//#ifdef Simplay_warning  
	UINT8 itemType;
	#ifdef SELECT_MEDIA_IN_SETUPMENU
	UINT8 VAMEDIA = 0;//DENGHG ADD 2005-2-18 21:33
	#endif
	
	switch(direction)
	{
		case SETUP_ENTER:
			setup_mLevel = SETUP_ML0;
			setup_pos[SETUP_ML0] = setup_mLevel;
			setup_pos[SETUP_ML1] = 0;
			setup_pos[SETUP_ML2] = 0;
			setup_pos[SETUP_ML3] = 0;
			break;
		case SETUP_UP:
			itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
			switch(itemType)
			{
				case SET_FUNC:
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
				case SET_FUNC_EX:
#endif

                                // The behavior of selecting the setup menu item is circulating. by robert.chang, 2006-07-19
                                setup_pos[SETUP_ML3]--;
                                do{                                                                        
                                    if(setup_pos[SETUP_ML3] == (MIN_ITEM_SEL-1)) {
                                        setup_pos[SETUP_ML3]=MAX_ITEM_SEL-1;
                                        iDo = 1;
                                    }else {
                                        iDo = 0;
                                    } 
                                    
                                    if( setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]] == 0 ) {
                                        setup_pos[SETUP_ML3]--;
                                        iDo = 1;  
                                        continue;
                                    }
                                    
#ifdef SELECT_MEDIA_IN_SETUPMENU  //denghg add for  SELECT_MEDIA_IN_SETUPMENU2005-2-15 11:16
        		               if(IsSetupMediaItemDisableSel()) {
        		                   setup_pos[SETUP_ML3]--;
                                        iDo = 1; 
                                        continue;
                                    }
#endif  ///denghg end  2005-2-15 11:38	

                                    #ifdef SUPPORT_HD_RESOLUTION    // When HD, the item STR_OS_PAL60 and STR_OS_AUTO will be skipped.
                                    if((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) {                                    
                                        if( (setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_TV_SYS) 
                                         && (  (setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_PAL60)
                                              ||(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_AUTO)   ) ) 
                                        {
            		                   setup_pos[SETUP_ML3]--;
                                            iDo = 1; 
                                            continue;
                                        }
                                    }
                                    #endif                                    
                                    
                                }while(iDo);

#if 0
					if(setup_pos[SETUP_ML3] > MIN_ITEM_SEL)
					{
						setup_pos[SETUP_ML3]--;
#ifdef SELECT_MEDIA_IN_SETUPMENU  //denghg add for  SELECT_MEDIA_IN_SETUPMENU2005-2-15 11:16
        		        if (IsSetupMediaItemDisableSel())
        		        {
        		            setup_pos[SETUP_ML3]--;
        		        }
#endif  ///denghg end  2005-2-15 11:38						
						
					}
#ifdef SETUP_CIRCLE_SELECT
                    else  // 20050726 mimitsai add for circle setup menu selection
                    {
                        while(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]+1] != 0)
                            setup_pos[SETUP_ML3]++;
                    }
#endif//#ifdef SETUP_CIRCLE_SELECT
#endif//#if 0
					break;
				case SET_SCALE:
					if(setup_pos[SETUP_ML3] < (setup_item[setup_pos[1]][setup_pos[2]][4]+2))
					{
						setup_pos[SETUP_ML3]++;
						setup_sel[setup_pos[1]][setup_pos[2]] = setup_pos[3];
						setup_execFunc();
						setup_saveVal();
					}
					break;
			}
			break;
		case SETUP_DOWN:
			itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
			switch(itemType)
			{
				case SET_FUNC:
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
				case SET_FUNC_EX:
#endif

                                // The behavior of selecting the setup menu item is circulating. by robert.chang, 2006-07-19
                                setup_pos[SETUP_ML3]++;
                                do{                                                                        
                                    if(setup_pos[SETUP_ML3] == MAX_ITEM_SEL) {
                                        setup_pos[SETUP_ML3]=MIN_ITEM_SEL;
                                        iDo = 1;
                                    }else {
                                        iDo = 0;
                                    } 
                                    
                                    if( setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]] == 0 ) {
                                        setup_pos[SETUP_ML3]++;
                                        iDo = 1;  
                                        continue;
                                    }
                                    
#ifdef SELECT_MEDIA_IN_SETUPMENU  //denghg add  2005-2-15 11:16
        		              if(IsSetupMediaItemDisableSel())
                                   {
                                        setup_pos[SETUP_ML3]++; 
                                        iDo = 1; 
                                        continue;                                        
                                    }       		
#endif  //denghg  end  2005-2-15 15:46

                                    #ifdef SUPPORT_HD_RESOLUTION // When HD, the item STR_OS_PAL60 and STR_OS_AUTO will be skipped.
                                    if((GET_TV_RESOLUTION()  == HD_720) || (GET_TV_RESOLUTION()  == HD_1080)) {                                    
                                        if( (setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_TV_SYS) 
                                         && (  (setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_PAL60)
                                              ||(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_AUTO)   ) ) 
                                        {
            		                   setup_pos[SETUP_ML3]++;
                                            iDo = 1; 
                                            continue;
                                        }
                                    }
                                    #endif                                    
                                    
                                }while(iDo);

#if 0
					if(setup_pos[SETUP_ML3] < MAX_ITEM_SEL)
					{
						#ifdef SELECT_MEDIA_IN_SETUPMENU  //denghg add for SELECT_MEDIA_IN_SETUPMENU 2005-2-15 16:33
						UINT8 old_pos = setup_pos[SETUP_ML3];
						#endif						
						if(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]+1] != 0)
						{
							setup_pos[SETUP_ML3]++;
#ifdef SELECT_MEDIA_IN_SETUPMENU  //denghg add  2005-2-15 11:16
        		              if (IsSetupMediaItemDisableSel())
                              {
                                  setup_pos[SETUP_ML3]++; 
                                  if(IsSetupMediaItemDisableSel())
                                  {
                                    setup_pos[SETUP_ML3]++;
                                  }
                                  if (setup_item[setup_pos[1]][setup_pos[2]][setup_pos[SETUP_ML3]] == 0)
                                  { 
                                    setup_pos[SETUP_ML3] = old_pos; 
                                  }   		  
                              }       		
#endif  //denghg  end  2005-2-15 15:46
						}
#ifdef SETUP_CIRCLE_SELECT

                        else   // 20050726 mimitsai add for circle setup menu selection
                            setup_pos[SETUP_ML3] = MIN_ITEM_SEL;
#endif
					}
#endif//#if 0
					break;
				case SET_SCALE:
					if(setup_pos[SETUP_ML3] > (setup_item[setup_pos[1]][setup_pos[2]][3]+2))
					{
						setup_pos[SETUP_ML3]--;
						setup_sel[setup_pos[1]][setup_pos[2]] = setup_pos[3];
						setup_execFunc();
						setup_saveVal();
					}
					break;
			}
			break;
		case SETUP_LEFT:
			setup_mLevel = SETUP_ML2;
			setup_pos[SETUP_ML0] = setup_mLevel;
			setup_pos[SETUP_ML3] = 0;
			break;
		case SETUP_RIGHT:
			break;
		case SETUP_SELECTION:
			itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
			switch(itemType)
			{
				case SET_FUNC:
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
				case SET_FUNC_EX:
#endif
					id = setup_item[setup_pos[1]][setup_pos[2]][1];
					if(id==STR_OS_DEFAULT_SETUP){
						#ifdef DEFAULT_YES_NO_SELECT
						if(setup_pos[SETUP_ML3] == 3)
						{
                        #endif
						#ifdef MCU51_PANNEL//2005-5-12 10:14 zhoulin  sending message to MCU for reseting default settings
                        setup_VA[SET_VA_DEFAULT]=1;
                        #endif
						set_default_value();
						run_set_variable();
						run_save_total_sel();
						
						#ifdef AFTER_DEFAULT_LOAD_RESET
						ExitSetupPage(0);//setup_ExitPage();
						#else
						ShowSetupPage(1);//refresh Setup Menu
						#endif
						
					    #ifdef VOLUME_RESET_WHEN_LOAD_DEFAULT
						audio_volume = RESET_VOLUME;
						if(cd_type_loaded)
						    VolumeCHKnSet(audio_volume);
						#endif
						
						#ifdef AFTER_DEFAULT_LOAD_RESET
						regs0->reset = -1;
						return;
						#endif
						
						#ifdef DEFAULT_YES_NO_SELECT
					    }
					    #endif
					}
#ifdef SETUP_POPUP_PSCAN_WARNING_GUI
					else if(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_P_SCAN_YUV)
					{
					    setup_mLevel = SETUP_ML2;
					    setup_pos[SETUP_ML0] = setup_mLevel;
					    setup_pos[SETUP_ML3] = 0;
	    				ShowSetupPage(1);
	    				
						setup_gui_state=SETUPGUI_PSCAN_WARNING;
						show_pscan_warning();
					}
  
				#ifdef POP_PAL_N_WARNING
					else if( (setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_PAL)||
						(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_NTSC) )
					{
						pop_pal_n_ui_flag = 1;

						if(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_NTSC)
							is_ntsc_pos_on =1;
						else if(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_PAL)
							is_pal_pos_on =1;
					
					    setup_mLevel = SETUP_ML2;
					    setup_pos[SETUP_ML0] = setup_mLevel;
					    setup_pos[SETUP_ML3] = 0;
	    				ShowSetupPage(1);
	    				
						setup_gui_state=SETUPGUI_PSCAN_WARNING;
						show_pal_n_warning();
					}
				#endif//#ifdef POP_PAL_N_WARNING
#endif //SETUP_POPUP_PSCAN_WARNING_GUI
					else{
						BYTE VA;
#ifdef HDMI_FMT_RESTORE						
						if (setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]] != STR_OS_FMT_CFM)
#endif							
						{
						    setup_sel[setup_pos[1]][setup_pos[2]] = setup_pos[3];
						    VA = setup_item[setup_pos[1]][setup_pos[2]][MAX_ITEM_SEL+1];
						    setup_VA[VA] = setup_sel[setup_pos[1]][setup_pos[2]];
						}

#ifdef SCALER_6500	//helm for NTSC<-->PAL to keep selection 050728					
						Check_PSCAN_INTERLACE();
#endif	
					#ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for NATIVE GAME 2005-10-19 16:13
					extern int  DVB_SetGameType(BYTE uGameType);
					if(id==STR_OS_GAME)
					{
					
						if((play_state==VCD_STATE_STOP)||(system_state==SYSTEM_NODISC))
						{
							if(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_GAME_BOXMAN)
							{
								DVB_SetGameType(DVB_GAME_BOXMAN);
							}
							else if(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_GAME_TETRIS)
							{
								DVB_SetGameType(DVB_GAME_TETRIS);
							}
							else if(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]]==STR_OS_GAME_HITRAT)
							{
								DVB_SetGameType(DVB_GAME_HITRAT);
							}
							//ExitSetupPage(1);				
						}
					}
					#endif
                        
                        #if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
						if(id == STR_OS_OSD)
						{
						    setup_saveVal();
						    setup_execFunc();
						}
						else
						{
                        #endif

#ifdef HDMI_FMT_RESTORE                        
                                                extern BYTE FMT_CHANGE;
                                                if (setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]] == STR_OS_FMT_CFM)
                                                    FMT_CHANGE = 0;
                                                else
#endif                        
						setup_execFunc();
						
						
#ifdef SELECT_MEDIA_IN_SETUPMENU
				       VAMEDIA = VA;//DENGHG ADD 2005-2-18 21:33
					   if (id != STR_OS_MEDIA_TYPE)  //denghg  add  for  SELECT_MEDIA_IN_SETUPMENU 2005-2-4 14:57
#endif
						setup_saveVal();
						#if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
					    }
					    #endif
					#ifdef DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF
						if(id==STR_OS_MIC_ONOFF) //zxb 2005-5-11
                        {
                            setup_refresh = 1;     
                            setup_ShowPageL2();    
                            setup_refresh = 0;
                        }
                   #endif
                   #ifdef GRAY_SUBW_BSMODE_DELAY_IN_2CH //zxb 2005-5-11                            
                        if(id==STR_OS_DOWNMIX_SETUP) 
                        {
                            setup_refresh = 1;     
                            setup_ShowPageL2();    
                            setup_refresh = 0;
                        }
                   #endif  						
                   #ifdef SAME_DISC_RESUME                 //ZXB 2005-5-17 1:30 
                       
					    //P=setup_getItemPos(STR_OS_RESUME);
                        //I=P&0xff;
                        //P=P>>8;                              	
                        //if (setup_item[P][I][setup_VA[SETUP_VA_RESUME]]==STR_OS_OFF) 
                        if( setup_getItemSelect(STR_OS_RESUME,SETUP_VA_RESUME) == STR_OS_OFF )
			                same_disc_onoff=0;
		                else
			                same_disc_onoff=1;			                
                   #endif

                   //ycwen 2005/5/17 PrologII ON -> Downmix off , needed in all situation 
                   #if defined(SUPPORT_PROLOGIC_II)//&& defined(DOWNMIX_OFF_DISP_5CH_ON)//zxb 2005-5-12 0:20
                             //when choose downmix not off ,set prologic off.
                             //when choose prologic not off,set downmix off.
					    UINT16 P, I; 
					    P=setup_getItemPos(STR_OS_PROLOGIC);
                        I=P&0xff;
                        P=P>>8;      
                        id = setup_item[setup_pos[1]][setup_pos[2]][1];	              					
					    if ((id==STR_OS_PROLOGIC) &&
                        (setup_item[P][I][setup_VA[SETUP_VA_PROLOGIC]]!=STR_OS_OFF))
                        {//5ch out
                            setup_VA[SETUP_VA_DOWNMIX]=5;//AC3DOWNMIXOFF;                    
                            setup_VA2sel();
                            run_save_sel_cmd(setup_VA[SETUP_VA_DOWNMIX], SETUP_VA_DOWNMIX);//nono 2004-2-16 15:04                     
                            str_os_downmix_setup(STR_OS_OFF); //ycwen 2005/5/17 adjust setupmenu display, too
                        }
                    
                        P=setup_getItemPos(STR_OS_DOWNMIX_SETUP);
                        I=P&0xff;
                        P=P>>8;          
                        //ycwen 2005/5/17  PrologII ON -> Downmix off , needed in all situation 
                    #ifdef DOWNMIX_OFF_DISP_5CH_ON
					    if ((id==STR_OS_DOWNMIX_SETUP) &&
                        (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]!=STR_OS_5CH_ON))
                    #else
                        if ((id==STR_OS_DOWNMIX_SETUP) &&
                        (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]!=STR_OS_OFF))
                    #endif
                        {//2ch out                        
                            setup_VA[SETUP_VA_PROLOGIC]=4;//PROLOGIC_OFF;    // alan, 2003/8/11 01:56PM                           
                            setup_VA2sel();
                            run_save_sel_cmd(setup_VA[SETUP_VA_PROLOGIC], SETUP_VA_PROLOGIC);//nono 20031117                        
                            str_os_prologic2(STR_OS_OFF);
                        }                    
                    #endif//SUPPORT_PROLOGIC_II			
					}
					break;
				case SET_SCALE:
					break;
				case SET_NM:
					setup_checkPassword();
					setup_saveVal();
					break;
			}

			// go back to item level(setup_L2)
			setup_mLevel = SETUP_ML2;
			setup_pos[SETUP_ML0] = setup_mLevel;
			setup_pos[SETUP_ML3] = 0;
			#ifdef SUPPORT_DVD_NATIVE_GAME		//linrc for NATIVE GAME 2005-10-19 16:14
			if(system_state==SYSTEM_DVDGAME)
			{
				ExitSetupPage(1);
			}
			#endif
			
			#ifdef SELECT_MEDIA_IN_SETUPMENU
			  if ((VAMEDIA == SETUP_VA_MEDIA_TYPE) && (system_state != SYSTEM_OPEN))
			  {
			    ExitSetupPage(1);  //=ircmd_setup when exit setup menu
			    //ircmd_setup();  //denghg  add  for  exit setup menu 2005-2-4 14:57
			  }
			#endif
			
			break;
	}

}
//======================================================================




// this function is for CUSTM page only, can be move to another file
void setup_GetPosCUS(UINT8 direction)
{
	UINT8 itemType;
	
	switch(setup_pos[0])
	{
		case SETUP_ML0:
			setup_mLevel = SETUP_ML2;
			setup_pos[SETUP_ML0] = setup_mLevel; 
			setup_pos[SETUP_ML1] = MAX_SETUP_PAGE;
#ifdef CUSTM_MENU_REVISE	//WSLEE 20050525 for customer menu		
			setup_pos[SETUP_ML2] = REGION_REMOVE + 1;	    // 2005/06/18 terry
#else
			setup_pos[SETUP_ML2] = 3;			
#endif	//CUSTM_MENU_FIX
			setup_pos[SETUP_ML3] = 0;
			setup_last_pos[SETUP_ML2] = MAX_PAGE_ITEM;
			break;
		case SETUP_ML2:
			switch(direction)
			{
				case SETUP_ENTER:
					setup_mLevel = SETUP_ML0;
					setup_pos[SETUP_ML0] = setup_mLevel;
					setup_pos[SETUP_ML1] = 0;
					setup_pos[SETUP_ML2] = 0;//MAX_PAGE_ITEM;
					setup_pos[SETUP_ML3] = 0;
					break;
				case SETUP_UP:
#ifdef CUSTM_MENU_REVISE //WSLEE 20050525 for customer menu
				#ifdef OP_CUST_UI//libing 2005-8-22 11:39
					if(setup_pos[2] > REGION_REMOVE+1)
				#elif defined(SUPPORT_REGION_UPDATE)
				    if(setup_pos[2] > REGION_REMOVE-1)
				#else
					if(setup_pos[2] > REGION_REMOVE)
				#endif
#else				
					if(setup_pos[2]>3)
#endif	//CUSTM_MENU_FIX
					{
						do{
						    setup_pos[2]--;
						}while(setup_item[setup_pos[1]][setup_pos[2]][1] == 0);
					}
					break;
				case SETUP_DOWN:
				    #ifdef DELETE_EXIT_ITEM
				    if((setup_pos[2]<MAX_PAGE_ITEM) && (setup_item[setup_pos[1]][setup_pos[2]][1] != STR_OS_PASSWORD))
				    #else
					if((setup_pos[2]<MAX_PAGE_ITEM) && (setup_item[setup_pos[1]][setup_pos[2]][1] != STR_OS_EXIT_MENU))
					#endif
					{
						do{
						    setup_pos[2]++;
						}while(setup_item[setup_pos[1]][setup_pos[2]][1] == 0);
					}	
					break;
				case SETUP_LEFT:
					break;
				case SETUP_RIGHT:
					itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
					switch(itemType)
					{
						case SET_FUNC: 
						case SET_NM:
							setup_mLevel = SETUP_ML3;
							setup_pos[SETUP_ML0] = setup_mLevel;
							setup_pos[SETUP_ML3] = setup_sel[setup_pos[1]][setup_pos[2]];
							break;
					}
					break;
				case SETUP_SELECTION:
					itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
					switch(itemType){
						case SET_FUNC:
						case SET_NM:
							setup_mLevel = SETUP_ML3;
							setup_pos[0] = setup_mLevel;
							setup_pos[SETUP_ML3] = setup_sel[setup_pos[1]][setup_pos[2]];
							break;
						case SET_SH:
								setup_ExitPage();													
							break;
					}
					break;

			}
			break;
		case SETUP_ML3:
			switch(direction)
			{
				case SETUP_ENTER:
					setup_mLevel = SETUP_ML0;
					setup_pos[SETUP_ML0] = setup_mLevel;
					setup_pos[SETUP_ML1] = 0;
					setup_pos[SETUP_ML2] = MAX_PAGE_ITEM;
					setup_pos[SETUP_ML3] = 0;
					break;
				case SETUP_UP:
					itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
					switch(itemType)
					{
						case SET_FUNC:
							if(setup_pos[SETUP_ML3] > MIN_ITEM_SEL)
								setup_pos[SETUP_ML3]--;
							break;
					}
					break;
				case SETUP_DOWN:
					itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
					switch(itemType)
					{
						case SET_FUNC:
							#ifdef RATING_8
							if(setup_pos[SETUP_ML3] < MAX_ITEM_SEL-1)
							#else
							if(setup_pos[SETUP_ML3] < MAX_ITEM_SEL)
							#endif
							{
								if(setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]+1] != 0)
									setup_pos[SETUP_ML3]++;
							}
							break;
					}
					break;
				case SETUP_LEFT:
					setup_mLevel = SETUP_ML2;
					setup_pos[SETUP_ML0] = setup_mLevel;
					setup_pos[SETUP_ML3] = 0;
					break;
				case SETUP_RIGHT:
					break;
				case SETUP_SELECTION:
					itemType = setup_item[setup_pos[1]][setup_pos[2]][0];
					switch(itemType)
					{
						case SET_FUNC:

							#ifdef AUTO_LOAD_MODE_SETUP  //DENGHG  ADD FOR Philips 2005-11-15 04:50     
							if(setup_item[setup_pos[1]][setup_pos[2]][1]==STR_OS_MODE)
							{
						        refresh_CUSTM_setup();
        						//printf("22setup_VA[SETUP_VA_RATING]=%d\n",SETUP_VA_RATING);
							}
							else
							{
							setup_sel[setup_pos[1]][setup_pos[2]] = setup_pos[3];
    							//printf("setup_pos[3]=%d\n",setup_pos[3]);
    							setup_execFunc();
    							setup_saveVal();	
							}
							    
							#else//#ifdef AUTO_LOAD_MODE_SETUP
							
							 {
							setup_sel[setup_pos[1]][setup_pos[2]] = setup_pos[3];
							setup_execFunc();
							setup_saveVal();
							 }  
							 #endif //#ifdef AUTO_LOAD_MODE_SETUP
							
												
							break;
						case SET_NM:
							break;
					}

					// go back to item level(setup_L2)
					setup_mLevel = SETUP_ML2;
					setup_pos[SETUP_ML0] = setup_mLevel;
					setup_pos[SETUP_ML3] = 0;
					break;
			}
			break;
	}
}
//purpose : to get the string id which the item select.
//zxb2005-5-17 1:40
UINT8 setup_getItemSelect(UINT8 setup_itemStr , UINT8 setup_itemVA)
{
    UINT16 P, I;
    P=setup_getItemPos(setup_itemStr);
    I=P&0xff;
    P=P>>8;  
    return setup_item[P][I][setup_VA[setup_itemVA]];
}

#ifdef AUTO_LOAD_MODE_SETUP  //denghg add refresh_CUSTM_setup 2005-11-18 07:59     
void refresh_CUSTM_setup(void)
{
     BYTE e2prom_mode_id;
     BYTE curren_pos;
     curren_pos=setup_pos[2];
	 e2prom_mode_id=setup_pos[3]-2;
	 chg_mode_setup_item(e2prom_mode_id);
	 forcedefault=1;
	 set_default_value();
	 forcedefault=0;
     run_set_variable();
     run_save_total_sel();
     setup_sel[setup_pos[1]][setup_pos[2]] = setup_pos[3];
     setup_execFunc();
     setup_saveVal();				  
     setup_mLevel = SETUP_ML2;
	 setup_pos[SETUP_ML0] = setup_mLevel;
	 setup_pos[SETUP_ML3] = 0;
     ExitSetupPage(1);
     display_custm_menu();//refresh cstm page Menu  
     setup_pos[SETUP_ML2] = curren_pos;
     
}
#endif

void setup_first_value(void)
{
    setup_mLevel = SETUP_ML0;
	setup_pos[SETUP_ML0] = setup_mLevel;
	setup_pos[SETUP_ML1] = 0;
	setup_pos[SETUP_ML2] = 0;
	setup_pos[SETUP_ML3] = 0;
	
}
//======================================================================

