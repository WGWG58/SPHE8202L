/***************************************************************
*  setup_ui_util.c
*  include  in setup_tab_ui1.c   when defined DVD_SETUP_REENG
* 
* Creator: 	JSLin 
* Date:  		2004/07/28
*
* Description :	
*			function dispatcher ???
*
****************************************************************/
#ifndef _SETUP_UI_UTIL
#define _SETUP_UI_UTIL

#ifndef DVDRELEASE
    //#define MONE_SETUP_UI_UTIL
#endif


void setup_saveVal(void);
void setup_execFunc(void);
void setup_execScaleFunc(void);	
void setup_setPasswd(void);
void setup_showPasswd(BYTE num);
void setup_checkPassword(void);
void setup_VA2sel(void);
void setup_sel2VA(void);
UINT32 setup_getSelPos(UINT16 selection);       // 2005/03/29 yltseng
UINT16 setup_getItemPos(UINT16 selection);      // 2005/03/29 yltseng
#ifdef HW_REQUIRE_DOWNMIX_WHEN_PCM_ENABLED//Steven 2006/08/10 add to avoid downmix off when SPDIF PCM turn on//
UINT8 setup_downmix_if_SPDIF_PCM(UINT8 downmix_sel);
#endif


//==================================================
#ifdef HW_REQUIRE_DOWNMIX_WHEN_PCM_ENABLED//Steven 2006/08/10 add to avoid downmix off when SPDIF PCM turn on//
UINT8 setup_downmix_if_SPDIF_PCM(UINT8 downmix_sel)
{


#ifdef DVD_SETUP_REENG	
	UINT16 P=0;
	UINT16 I=0;
#endif	
#ifdef DVD_SETUP_REENG
		P=setup_getItemPos(STR_OS_AUD_OUT);
		I=P&0xff;
		P=P>>8;

    if((setup_item[P][I][setup_VA[SETUP_VA_AUD_OUT]] == STR_OS_STEREO_PCM) &&
    (coding_mode_now&(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD)) &&
    (downmix_sel == OUT_51Channel) 
    )
                        
#else
    if ( (SETUP_SPDIF==SPDIFPCM) && 
    ( coding_mode_now&(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD)) &&
    (downmix_sel == OUT_51Channel) 
    )
 
#endif	//end of DVD_SETUP_REENG    
  
        {
        downmix_sel = OUT_51DownmixL0R0;
        }
    return downmix_sel;        
}
#endif
//==================================================


//==================================================

#ifdef OSD_COLOR_ADJUST_BY_BRIGHTNESS_AND_CONTRAST  // 2004/11/12 yltseng

void UpdateSetupmenuPalette()
{
    extern void osd_update_setupmenu_palette();
    osd_update_setupmenu_palette();
}
#else

#define UpdateSetupmenuPalette()

#endif


void setup_saveVal(void)
{
	BYTE VA;
       #ifdef MONE_SETUP_UI_UTIL
	printf(">>>>>setup_saveVal<<<<<\n");
       #endif

	VA = setup_item[setup_pos[1]][setup_pos[2]][MAX_ITEM_SEL+1];
	setup_VA[VA] = setup_sel[setup_pos[1]][setup_pos[2]];
#ifdef NOT_RELOAD_BRIGHT_AND_CONTRAST
    if((VA==SETUP_VA_BRIGHTNESS) || (VA==SETUP_VA_CONTRAST))
        return;
#endif	
#ifdef DEFAULT_WIDE_SCREEN_AND_UNLOAD
    if(VA == SETUP_VA_TV_RATIO)
        return;
#endif
	
	run_save_sel_cmd(setup_VA[VA], VA);

/*
	// for CUSTM page saving corresponding valus
	if(full_scrn&CUSTM){
		int p1, p2;
		for (p1=0; p1<MAX_SETUP_PAGE; p1++){
			for (p2=0; p2<MAX_PAGE_ITEM; p2++){
				if(setup_item[p1][p2][1]==setup_item[setup_pos[1]][setup_pos[2]][1]){
					setup_sel[p1][p2] = setup_sel[setup_pos[1]][setup_pos[2]];
					//run_save_sel_cmd(p1, p2);
				}
			}
		}
	}//end of if(full_scrn&CUSTM)
*/	
}
//===================================================


void setup_execFunc(void)
{
	UINT8 itemType;

	itemType = setup_item[setup_pos[1]][setup_pos[2]][0];

	if(itemType == SET_SCALE){
		setup_execScaleFunc();
	} else if(itemType == SET_FUNC){
#ifdef MONE_SETUP_UI_UTIL
		printf("\n\n	exe_setup_function	\n");
#endif
		exe_setup_function(setup_item[setup_pos[1]][setup_pos[2]][1], setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]], 1);
	} 
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
	else if(itemType == SET_FUNC_EX){
	    exe_setup_function_ex(setup_item[setup_pos[1]][setup_pos[2]][1], setup_item[setup_pos[1]][setup_pos[2]][setup_pos[3]], 1);
	} 
#endif
}
//===================================================


void setup_execScaleFunc(void)
{
	UINT32 funcID;

       #ifdef MONE_SETUP_UI_UTIL
	 printf("\n\n	setup_execScaleFunc\n");
       #endif
	funcID = setup_item[setup_pos[1]][setup_pos[2]][1];

	switch(funcID){		
		case STR_OS_BRIGHTNESS:
			SetBrightness(setup_pos[3]-MIN_ITEM_SEL);
			UpdateSetupmenuPalette();   // 2004/11/12 yltseng
			break;
		case STR_OS_CONTRAST:
			SetContrast(setup_pos[3]-MIN_ITEM_SEL);
			UpdateSetupmenuPalette();   // 2004/11/12 yltseng
			break;
		case STR_OS_HUE:
			SetHUE(setup_pos[3]-MIN_ITEM_SEL);
			break;
		case STR_OS_SATURATION:
			SetSaturation(setup_pos[3]-MIN_ITEM_SEL);
			break;
		#ifdef HW_SUPPORT_TV_SHARPNESS //2006-04-12, mimitsai add for IC_8202xx relative
              case STR_OS_SHARPNESS:
                     SetSharpness(setup_pos[3]-MIN_ITEM_SEL);
                     break;
        #endif             
		case STR_OS_KEY:
			audio_key = setup_pos[3]-MIN_ITEM_SEL-6;
			AUDIF_Set_Key(setup_pos[3]);//2004AUDDRV AudioSetKey(setup_pos[3]);
			//printf("\n\n>>>> audio_key:%d\n", audio_key);
			break;
		case STR_OS_ECHO:
			echo_level=setup_pos[3]-MIN_ITEM_SEL;
			#ifdef USE_MIC_ECHO_PARAM
            	AUDIF_Set_EchoPara(setup_pos[3]-MIN_ITEM_SEL);//2004AUDDRV AudioSetEchoPara(setup_pos[3]-MIN_ITEM_SEL);
			#else
            	AUDIF_Set_Echo(setup_pos[3]-MIN_ITEM_SEL, setup_pos[3]-MIN_ITEM_SEL);//2004AUDDRV AudioSetEcho(setup_pos[3]-MIN_ITEM_SEL, setup_pos[3]-MIN_ITEM_SEL);
			#endif			
			break;
		case STR_OS_MIC_VOL:
		case STR_OS_MIC_VOL_1:
			mic_volume=setup_pos[3]-MIN_ITEM_SEL;
			AUDIF_Set_MICVol(setup_pos[3]-MIN_ITEM_SEL);//2004AUDDRV AudioSetMICVol(setup_pos[3]-MIN_ITEM_SEL);
			break;
		case STR_OS_MIC_VOL_2:
			mic_volume=setup_pos[3]-MIN_ITEM_SEL;
			AUDIF_Set_MICVol2(setup_pos[3]-MIN_ITEM_SEL);//2004AUDDRV AudioSetMICVol_2(setup_pos[3]-MIN_ITEM_SEL);
			break;
		case STR_OS_CSPK_DELAY:
			AUDIF_Set_SpkDelay(1, setup_pos[3]-2);//2004AUDDRV AudioSetSpkDelay(1, setup_pos[3]-2);
			break;
		case STR_OS_SSPK_DELAY:
			AUDIF_Set_SpkDelay(2, (setup_pos[3]-2)*3);//2004AUDDRV AudioSetSpkDelay(2, (setup_pos[3]-2)*3);
			break;
		case STR_OS_DYNAMICRANGE:	//inconsistent
			ac3_dynarange=setup_pos[3]-MIN_ITEM_SEL;
			set_AC3DynamicRange();
			break;
#ifdef SUPPORT_PROLOGIC_II_ADVANCE_SETTING//chenzhao 2005-5-12
        case STR_OS_PL_CENTER_WIDTH:
            if((setup_pos[3]-MIN_ITEM_SEL)>7)
                str_os_prologic2_center_width(7);
            else
                str_os_prologic2_center_width(setup_pos[3]-MIN_ITEM_SEL);
            break;
        case STR_OS_PL_DIMENSION:
                str_os_prologic2_dimension(setup_pos[3]-MIN_ITEM_SEL);
            break;
#endif
	}
}
//===================================================


void setup_setPasswd(void)
{
#ifdef SUPPORT_OP_REGION_UI//libing 2005-8-26 10:12	
	extern int Region_Avoid_Ckpwd;
	if(Region_Avoid_Ckpwd) return;
#endif	
#ifdef ORITRON_TRAY_PASSWORD//libing 2005-5-13 16:00 	
	if (tray_psd_exit_flag) return;
#endif
#ifndef NEW_SOFT_PASSWORD_UI  //liumzh for eastech password input invalid 2005-6-1 16:41
	//lyc add 2005-3-12 for parental gui
	if(((setup_pos[0] == SETUP_ML1)||(setup_pos[0] == SETUP_ML2))
	#ifdef NEW_PARENTAL_GUI//Jack added 04/12/02
        && (!new_parental_gui)
    #endif
	) 
		return;
	//if(setup_pos[0] != SETUP_ML3) return;
#else
if(full_scrn&CUSTM)
	if(setup_pos[0] != SETUP_ML3) return;
#endif
	
	if(ir_select_number >= 10) return;
	
	//lyc add 2005-3-12 for parental gui
	//if(setup_item[setup_pos[1]][setup_pos[2]][0] == SET_NM)
	if(setup_item[setup_pos[1]][setup_pos[2]][0] == SET_NM ||
#ifdef NEW_SOFT_PASSWORD_UI
	   setup_item[setup_pos[1]][setup_pos[2]][0] == SET_FUNC ||
#endif
#ifdef NEW_PARENTAL_GUI//Jack added 04/12/02
       (new_parental_gui) || 
#endif
	   setup_item[setup_pos[1]][setup_pos[2]][0] ==SET_SHOW)
	{
    	id=setup_item[setup_pos[1]][setup_pos[2]][1];

		if(digit_cnt>=PASSWORD_LENGTH)
        #ifdef INPUT_2FOUR_NUM_STOP
            return;
        #else
        	digit_cnt=0;
        #endif

        digit_cnt++;
                
        setup_showPasswd(ir_select_number);
	}	
}
//===================================================


void setup_showPasswd(BYTE num)
{
    UINT8   i;
    //BYTE    yStart;
    BYTE    buf[40];

#ifdef USE_NEW_SCHINESE_OSD
    #define CH_STAR     '*'
    #define CH_DASH     '-'
    #define CH_SPACE    ' '
    #define CH_LOCK     N_lock
    #define CH_UNLOCK   N_unlock
#else
    #define CH_STAR 0x58//X  //jhuang pending
    #define CH_DASH 0x2d//-
    #define CH_SPACE 0x20
    #define CH_LOCK   0xff
    #if defined(USE_SCHINESE_OSD)||defined(USE_JAPANESE_OSD)||defined(USE_TCHINESE_OSD)||defined(USE_THAI_OSD)||defined(USE_KOREAN_OSD)||defined(USE_HEBRAIC_OSD)||defined(USE_ARABIC_OSD)//jiangxl 2005-8-25 14:48
    #define CH_UNLOCK 0x67
    #else 
    #define CH_UNLOCK 0x7f
    #endif
#endif

    if(num == CLREAR_PASSWD) {
        reset_passwd_cnt();
    }

#ifdef SETUP_6_DIGIT_PASSWORD
	tmp_passwd=(tmp_passwd*10+num)%1000000;
#else
	tmp_passwd=(tmp_passwd*10+num)%10000;
#endif
        // fill char
        for(i=1;i<=digit_cnt;i++)
		linebuf[i-1] = CH_STAR;
        for(i=digit_cnt+1;i<=PASSWORD_LENGTH;i++)
            linebuf[i-1] = CH_DASH;

        linebuf[PASSWORD_LENGTH] = CH_SPACE;

        {
	 	 if(UserSet.parental_ststus==C_LOCK)
			 linebuf[PASSWORD_LENGTH+1] = CH_LOCK;
		  else
		 	 linebuf[PASSWORD_LENGTH+1] = CH_UNLOCK;
	}
	
	#ifdef ALCO_DVD_UI
	linebuf[PASSWORD_LENGTH+1] = 0;//shenyj modify for alco 11/22
	#else
	linebuf[PASSWORD_LENGTH+2] = 0;
    #endif
    
	if(full_scrn&CUSTM)
	{
		UserSet.parent_passwd = tmp_passwd;
		#ifdef SETUP_6_DIGIT_PASSWORD
			psprintf(buf, "%06d", UserSet.parent_passwd);
		#else
			psprintf(buf, "%04d", UserSet.parent_passwd);
		#endif
	}
	else
	{	
		psprintf(buf,"%s",linebuf);
	}

//lyc add 2005-3-12 for parental gui
#ifdef NEW_PARENTAL_GUI
  if(new_parental_gui)
   osd_DrawRegionString(PASSWORD_XSTART, PASSWORD_YSTART, buf, PASSWORD_FONT_COLOR, PASSWORD_BK_HL_COLOR, 0);
  else
#endif
#ifdef SOFT_MENU_REENG //chenzhao20050526
  {
      void ShowSetupPassword_Simple(const char *buf);
      buf[PASSWORD_LENGTH] = 0;
      #ifdef SUPPOT_SETUP_POPUP_PASSWORD_GUI
      if(!(full_scrn&CUSTM))
          ShowSetupPassword(buf);
      else
      #endif
      ShowSetupPassword_Simple(buf);
  }
#else
   osd_DrawString(SETUP_SUB_XSTART+1, SETUP_MENU_YSTART+setup_pos[2], buf, setupFcolorSM, setupBGcolorSM);
#endif
}
//===================================================


void setup_checkPassword(void)
{
    #ifdef MONE_SETUP_UI_UTIL
	printf("setup_checkPassword mark 1, tmp_passwd:%d", tmp_passwd);
    #endif
	if(digit_cnt == PASSWORD_LENGTH)
	{
		if(UserSet.parental_ststus == C_LOCK)
		{
			if((tmp_passwd == UserSet.parent_passwd)
				#ifdef ORITRON_PARENTAL_PASSWORD //libing 2005-4-28 13:48
                ||(tmp_passwd==DEFAULT_PASSWORD && op_parent_pwd_flag==1)
                #endif
				#ifdef USER_SUPER_PASSWORD
				||(tmp_passwd == USER_SUPER_PASSWORD)
				#endif
				)
			{
				UserSet.parental_ststus = C_UNLOCK;
				setup_sel[setup_pos[1]][setup_pos[2]] = 3;
				#ifdef ORITRON_PARENTAL_PASSWORD //libing 2005-4-28 13:48
				op_parent_pwd_flag = 0;
				#endif
			}
		}
		else if(UserSet.parental_ststus == C_UNLOCK)
		{
			#ifdef ALCO_DVD_UI
			if(tmp_passwd != USER_SUPER_PASSWORD)
			#endif
			UserSet.parent_passwd = tmp_passwd;
			UserSet.parental_ststus = C_LOCK;
			setup_sel[setup_pos[1]][setup_pos[2]] = 2;			
		}
	}
	reset_passwd_cnt();
}
//===================================================
void setup_VA2sel(void)
{
	int i, j, VA;

    #ifdef MONE_SETUP_UI_UTIL
	printf("setup_VA[] >>> setup_set[][]\n");
    #endif
	
	#ifdef ALCO_DVD_UI
	if((!setup_VA[SETUP_VA_OSD_LANG]) && (setup_sel[0][1]!=0)
	    #ifdef VCD_DISC_ACCORDING_REGION
	    &&(!region_code_reset)
        #endif
	  )
	    setup_sel2VA();
	#endif
	
	for(i=0; i<(MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE); i++)
	{
		for(j=1; j<=MAX_PAGE_ITEM; j++)
		{
			VA = setup_item[i][j][MAX_ITEM_SEL+1];
			if(VA < MAX_SETUP_VA)
			{
				#ifdef ALCO_DVD_UI
				if(setup_VA[VA] == 0)
				    setup_VA[VA] = setup_item[i][j][MAX_ITEM_SEL+2]+MIN_ITEM_SEL;
				#endif
				
				setup_sel[i][j] = setup_VA[VA];
			}
		}
	}
}
//===================================================


void setup_sel2VA(void)
{
	int i, j, VA;

    #ifdef MONE_SETUP_UI_UTIL
	printf("setup_VA[] <<< setup_set[][]\n");
    #endif
	
	for(i=0; i<(MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE); i++)
	{
		for(j=1; j<=MAX_PAGE_ITEM; j++)
		{
			VA = setup_item[i][j][MAX_ITEM_SEL+1];
			if(VA < MAX_SETUP_VA)
			{
				setup_VA[VA] = setup_sel[i][j];
			}
		}
	}
}
//===================================================


UINT32 setup_getSelPos(UINT16 selection)        // 2005/03/29 yltseng
{
    UINT8   P, I, S;
    UINT8   uiID    = selection & 0x00ff;
    UINT8   uiTable = selection >> 8;
    UINT32  selPos  = 0xffffff;

	for( P = 0; P < (MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE); P++ )
	{
		for( I = 1; I <= MAX_PAGE_ITEM; I++ )
		{
		    if( uiTable == ( setup_item[P][I][0] >> 4 ) )
		    {
    			for( S = 2; S < MAX_ITEM_SEL; S++ ){
    				if( uiID == setup_item[P][I][S] )
    				{
    					selPos = (P<<16) + (I<<8) + S;
    					goto EXIT_GETSELPOS;
    				}
    			}
		    }
		}
	}

EXIT_GETSELPOS:

#ifdef MONE_SETUP_UI_UTIL
	printf("\n\n====================================\n");
	printf(" 	P:%d	I:%d	S:%d\n", (selPos>>16), ((selPos>>8)&0xff), (selPos&0xff));
	printf("====================================\n\n\n");
#endif

	return selPos;
}

//===================================================

UINT16 setup_getItemPos(UINT16 selection)       // 2005/03/29 yltseng
{
	UINT8   P, I;
    UINT8   uiID    = selection & 0x00ff;
    UINT8   uiTable = selection >> 8;
    UINT16  itemPos = 0xffff;
    
	for( P=0; P < (MAX_SETUP_PAGE + MAX_CUSTM_SETUP_PAGE); P++ )
	{
		for( I = 1; I <= MAX_PAGE_ITEM; I++ )
		{
		    if( uiTable == ( setup_item[P][I][0] >> 4 ) )
		    {
    			if( uiID == setup_item[P][I][1] )
    			{
    				itemPos = (P<<8) + I;
    				goto EXIT_GETITEMPOS;
    			}
		    }
		}
	}
	
EXIT_GETITEMPOS:

#ifdef MONE_SETUP_UI_UTIL
	printf("\n\n====================================\n");
	printf(" 	P:%d	I:%d\n", (itemPos>>8),(itemPos&0xff));
	printf("====================================\n\n\n");
#endif

	return itemPos;
}

#endif




//===================================================

