/***************************************************************
*  setup_OSD_util.c
*  include  in setup_tab_ui1.c   when defined DVD_SETUP_REENG
* 
* Creator:  JSLin 
* Date:         2004/07/28
*
* Description : 
*           adapterr, 
*           hookup presentation engine(setup_show_page.c) with OSD module
*
****************************************************************/


/*
 *  setup_item = setup_button + setup_string
 */
#ifndef SOFT_MENU_REENG //chenzhao20050523
void setup_draw_item(BYTE xStart, BYTE yStart, BYTE xLen, BYTE itemID, BYTE setup_itemType, BYTE itemType __attribute__ ((unused)) )//BYTE xOffset, BYTE fColor, BYTE bgColor, BYTE upDown,  BYTE itemID)
{   // 2005/03/29 yltseng
    const char *str;
    BYTE xOffset = 0;
    BYTE upDown = 0;
    BYTE  fColor = 0;
    BYTE  bgColor = 0;

    //printf(">>>>>  draw item ID:%d\n", itemID);

    switch(setup_itemType){
        case SETUP_itemNormal:
            xOffset = 1;
            upDown = 0;
            if(xStart==SETUP_MENU_XSTART)
            {
            	fColor = setupFcolorIN;
            	bgColor = setupBGcolorIN;
        	}
        	else if(xStart==SETUP_SUB_XSTART)
        	{
        		  #ifdef SELECT_MEDIA_IN_SETUPMENU //denghg add 2005-2-15 17:23
        		  if(IsSetupMediaItemDisable())
        		  fColor = SGRAYCOLOR;
        		  else
        		  #endif  //denghg end  SELECT_MEDIA_IN_SETUPMENU2005-2-15 17:23
        		fColor = setupFcolorSN;
            	bgColor = setupBGcolorSN;
        	}
        	//zxb 2005-5-11 13:50
        	#if defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH)||defined(DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF)            	
            	UINT16 P, I;                               
            	    switch ( itemID )
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
            	                fColor = 13;//SGRAYCOLOR;
            	            break;
                    #endif //GRAY_SUBW_BSMODE_DELAY_IN_2CH	            
            	    #ifdef DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF
            	        case STR_OS_ECHO :
            	        case STR_OS_MIC_VOL :  
            	            P=setup_getItemPos(STR_OS_MIC_ONOFF);
                            I=P&0xff;
                            P=P>>8;
            	            if( (setup_item[P][I][setup_VA[SETUP_VA_MIC_ONOFF]]==STR_OS_OFF) )          	        
            	                fColor = 13;//SGRAYCOLOR;
            	            break;
                    #endif //DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF            	            
            	        default:
            	            break;
            	    }       
            #endif //defined(GRAY_SUBW_BSMODE_DELAY_IN_2CH) ||
        	       //defined(DISABLE_ECHO_MICVOL_WHEN_MIC_IS_OFF)                  	    
            break;
        case SETUP_itemMark:
            xOffset = 1;
            upDown = 1;
            if(xStart==SETUP_MENU_XSTART)
            {
            	fColor = setupFcolorIM;
            	bgColor = setupBGcolorIM;
        	}
        	else if(xStart==SETUP_SUB_XSTART)
        	{
        		fColor = setupFcolorSM;
            	bgColor = setupBGcolorSM;
        	}
            break;
        case SETUP_itemSelected:
            xOffset = 1;
            upDown = 0;
            if(xStart==SETUP_MENU_XSTART)
            {
            	fColor = setupFcolorIS;
            	bgColor = setupBGcolorIS;
        	}
        	else if(xStart==SETUP_SUB_XSTART)
        	{
        		fColor = setupFcolorSS;
            	bgColor = setupBGcolorSS;
        	}
            break;
        #ifdef USE_SETUP_ITEM_ENABLE_FLAG
        case SETUP_itemDisnable:
            xOffset = 1;
            upDown = 0;
            if(xStart==SETUP_MENU_XSTART)
            {
                fColor = setupFcolorID;
                bgColor = setupBGcolorIN;
            }
            else if(xStart==SETUP_SUB_XSTART)
            {
                  #ifdef SELECT_MEDIA_IN_SETUPMENU //denghg add 2005-2-15 17:23
                  if(IsSetupMediaItemDisable())
                  fColor = SGRAYCOLOR;
                  else
                  #endif  //denghg end  SELECT_MEDIA_IN_SETUPMENU2005-2-15 17:23
                fColor = setupFcolorSN;
                bgColor = setupBGcolorSN;
            }
            break;
        #endif
    }
    
    osd_draw_setup_button(xStart,yStart,xLen, bgColor, upDown);
   /* if((setup_item[setup_pos[SETUP_ML1]][0][1] == STR_OS_LANG_SETUP) && (xStart == SETUP_SUB_XSTART))*/
    if(((setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] == STR_OS_OSD)||(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] == STR_OS_MENU_LANG_SETUP)
    ||(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] == STR_OS_AUDIO_LANG_SETUP)||(setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1]==STR_OS_SUBTITLE_LANG_SETUP)) 
    && (xStart == SETUP_SUB_XSTART))  //denghg modify if osd ,menu,audio,subtile language setup isn'n   on language setup item  denghg 2005-4-27 18:49
    {
        if (itemID==STR_OS_OFF)
            str = _OsdMessegeFont1[osd_font_mode][itemID];
        else
        #ifdef LOAD_EACH_OSD_LANGUAGE
            str = lang_names[0][itemID];
        #else
            str = lang_names[osd_font_mode][itemID];
        #endif
            
    }
    #ifdef  USE_SETUP_SELECT_FONT
    else if( (setup_item[setup_pos[SETUP_ML1]][setup_pos[SETUP_ML2]][1] == STR_OS_DIVX_FONT_CODE)
            && (xStart == SETUP_SUB_XSTART) )
    {
        str = divx_sutitle_osd_langs[itemID];
    }
    #endif    
    else
    {
#ifdef SETUP_EXTENSION_TABLE        // 2005/03/29 yltseng
        UINT8 uiExTable = ( itemType & 0xf0 ) ? TRUE : FALSE;
        if( uiExTable )
            str = GetOSDString( osd_font_mode, itemID );
        else
#endif
            str = _OsdMessegeFont1[osd_font_mode][itemID];
    }
    
    osd_DrawString(xStart+xOffset, yStart, str, fColor, bgColor);
    
}
#endif//#ifdef SOFT_MENU_REENG

UINT32 setup_GetScaleItemPosition()     // 2005/04/11 yltseng
{
    UINT32 uiPos = setup_item[setup_pos[1]][setup_pos[2]][2];
    
    if( setup_pos[2] + uiPos > 9 )
        uiPos = 8 - uiPos;
    else
        uiPos = setup_pos[2] - 1;

    return uiPos;
}

void setup_DrawScaleString(UINT8 id, BYTE fontColor, BYTE bgColor)
{
    UINT8 xString, yString;
    t_osd_str osdstr_scale[MAX_ITEM_SEL - MIN_ITEM_SEL];
    int i;
    xString = SETUP_SUB_XSTART+1;
    yString = setup_GetScaleItemPosition() + SETUP_MENU_YSTART + 1;     // 2005/04/11 yltseng

	for (i=0; i<(MAX_ITEM_SEL - MIN_ITEM_SEL); i++)
	{
		osdstr_scale[i].xst = xString;
        osdstr_scale[i].yst = yString+i;
        osdstr_scale[i].str = NULL;	
	}


    if (id==STR_OS_ECHO) {
		osdstr_scale[0].str = " -    - 8";
		osdstr_scale[1].str = " -    - 6";
		osdstr_scale[2].str = " -    - 4";
		osdstr_scale[3].str = " -    - 2";
		osdstr_scale[4].str = " -    - OFF";
    }   
    else if (id==STR_OS_BRIGHTNESS){
    	osdstr_scale[0].str = " -    - 12";
    	osdstr_scale[1].str = " -    - 10";
    	osdstr_scale[2].str = " -    -  8";
    	osdstr_scale[3].str = " -    -  6";
    	osdstr_scale[4].str = " -    -  4";
    	osdstr_scale[5].str = " -    -  2";
    	osdstr_scale[6].str = " -    -  0";
    }
    else if (id==STR_OS_CONTRAST){
    	osdstr_scale[0].str = " -    - 12";
    	osdstr_scale[1].str = " -    - 10";
    	osdstr_scale[2].str = " -    -  8";
    	osdstr_scale[3].str = " -    -  6";
    	osdstr_scale[4].str = " -    -  4";
    	osdstr_scale[5].str = " -    -  2";
    	osdstr_scale[6].str = " -    -  0";
    }
    else if (id==STR_OS_HUE){
    	osdstr_scale[0].str = " -    - +6";
    	osdstr_scale[1].str = " -    - +4";
    	osdstr_scale[2].str = " -    - +2";
    	osdstr_scale[3].str = " -    -  0";
    	osdstr_scale[4].str = " -    - -2";
    	osdstr_scale[5].str = " -    - -4";
    	osdstr_scale[6].str = " -    - -6";
    }
    else if (id==STR_OS_SATURATION){
    	osdstr_scale[0].str = " -    - 12";
    	osdstr_scale[1].str = " -    - 10";
    	osdstr_scale[2].str = " -    -  8";
    	osdstr_scale[3].str = " -    -  6";
    	osdstr_scale[4].str = " -    -  4";
    	osdstr_scale[5].str = " -    -  2";
    	osdstr_scale[6].str = " -    -  0";
    }
    else if (id==STR_OS_SHARPNESS){ 
    	osdstr_scale[0].str = " -    -  8";
    	osdstr_scale[1].str = " -    -  6";
    	osdstr_scale[2].str = " -    -  4";
    	osdstr_scale[3].str = " -    -  2";
    	osdstr_scale[4].str = " -    -  0";
    }
    else if (id==STR_OS_KEY) {
    	osdstr_scale[0].str = " -    -  " Ch_ukey;
    	osdstr_scale[1].str = " -    - +4";
    	osdstr_scale[2].str = " -    - +2";
    	osdstr_scale[3].str = " -    -  0";
    	osdstr_scale[4].str = " -    - -2";
    	osdstr_scale[5].str = " -    - -4";
    	osdstr_scale[6].str = " -    -  " Ch_dkey;
    }
    else if (id==STR_OS_DYNAMICRANGE) {
		osdstr_scale[0].str = " -    - FULL";
		osdstr_scale[1].str = " -    - 6/8";
		osdstr_scale[2].str = " -    - 4/8";
		osdstr_scale[3].str = " -    - 2/8";
		osdstr_scale[4].str = " -    - OFF";
    }
    else if (id==STR_OS_MIC_VOL) {
		osdstr_scale[0].str = " -    - 8";
		osdstr_scale[1].str = " -    - 6";
		osdstr_scale[2].str = " -    - 4";
		osdstr_scale[3].str = " -    - 2";
		osdstr_scale[4].str = " -    - OFF";
    }
    else if (id==STR_OS_MIC_VOL_1) {         //2005-4-22 19:27 zhoulin
		osdstr_scale[0].str = " -    - 8";
		osdstr_scale[1].str = " -    - 6";
		osdstr_scale[2].str = " -    - 4";
		osdstr_scale[3].str = " -    - 2";
		osdstr_scale[4].str = " -    - OFF";
    }
    else if (id==STR_OS_MIC_VOL_2) {         //2005-4-22 19:27 zhoulin
		osdstr_scale[0].str = " -    - 8";
		osdstr_scale[1].str = " -    - 6";
		osdstr_scale[2].str = " -    - 4";
		osdstr_scale[3].str = " -    - 2";
		osdstr_scale[4].str = " -    - OFF";
    }
    
    
#ifdef DANSTANCE_DELAY_METER    //fcr 2005-10-21 17:28
    else if (id==STR_OS_CSPK_DELAY) 
    {
		osdstr_scale[0].str = " -    - +";
		osdstr_scale[1].str = " -    - 1.5M";	//osdstr_scale[1].str = " -    - 4 MS";
		osdstr_scale[2].str = " -    - 0.5M";	//osdstr_scale[2].str = " -    - 2 MS";
		osdstr_scale[3].str = " -    - 0  M";	//osdstr_scale[2].str = " -    - 0 MS";
    }
    else if (id==STR_OS_SSPK_DELAY) 
    {
		osdstr_scale[0].str = " -    - +";
		osdstr_scale[1].str = " -    - 4 M";	//osdstr_scale[1].str = " -    - 12 MS";
		osdstr_scale[2].str = " -    - 2 M";	//osdstr_scale[1].str = " -    - 6 MS";
		osdstr_scale[3].str = " -    - 0 M";  //osdstr_scale[1].str = " -    - 0 MS"; 
    }
#else
	else if (id==STR_OS_CSPK_DELAY) 
    {
		osdstr_scale[0].str = " -    - +";
		osdstr_scale[1].str = " -    - 4 FT";	//osdstr_scale[1].str = " -    - 4 MS";
		osdstr_scale[2].str = " -    - 2 FT";	//osdstr_scale[2].str = " -    - 2 MS";
		osdstr_scale[3].str = " -    - 0 FT";	//osdstr_scale[3].str = " -    - 0 MS";
    }   
    else if (id==STR_OS_SSPK_DELAY) 
    {
		osdstr_scale[0].str = " -    - +";
		osdstr_scale[1].str = " -    - 12 FT";	//osdstr_scale[1].str = " -    - 12 MS";
		osdstr_scale[2].str = " -    -  6 FT";	//osdstr_scale[2].str = " -    -  6 MS";
		osdstr_scale[3].str = " -    -  0 FT";  //osdstr_scale[3].str = " -    -  0 MS";  
    }   

#endif 
#if defined(DIP_CFG_ENABLE)//nono 5-9-23 0:22
    else if(id==STR_OS_DEINTLC){
    	osdstr_scale[0].str = " -    - 6";
    	osdstr_scale[1].str = " -    - 4";
    	osdstr_scale[2].str = " -    - 2";
    	osdstr_scale[3].str = " -    - 0";
    }
#endif
    #ifdef SUPPORT_PROLOGIC_II_ADVANCE_SETTING//chenzhao 2005-5-12
    else if(id==STR_OS_PL_CENTER_WIDTH){
    	osdstr_scale[0].str = " -    - 90";
    	osdstr_scale[1].str = " -    - 69";
    	osdstr_scale[2].str = " -    - 54";
    	osdstr_scale[3].str = " -    - 28";
    	osdstr_scale[4].str = " -    -  0";
    }
    else if(id==STR_OS_PL_DIMENSION){
    	osdstr_scale[0].str = " -    - +3";
    	osdstr_scale[1].str = " -    - +1";
    	osdstr_scale[2].str = " -    - -1";
    	osdstr_scale[3].str = " -    - -3";
    }
    #endif//SUPPORT_PROLOGIC_II_ADVANCE_SETTING
    else {  //show ERROR
		osdstr_scale[0].str = "		ERROR";
    }
	osd_DrawStrings(osdstr_scale, fontColor, bgColor);
}


void setup_DrawScaleForm(UINT8 id, BYTE upDown)
{
    BYTE    eColorTL, eColorBR; 
    BYTE    fontColor, bgColor; //font, background color
    UINT32  xStart, yStart;
    UINT32  yDelta=0;
    UINT32  yOffset = 0;
    //BYTE    buf[15];
    BYTE    xWidth;
    //int val = echo_level; // give a default value
    
    if (upDown) {	//down
        eColorTL = setupEcolorSPTLD;
        eColorBR = setupEcolorSPBRD;
        fontColor = setupFcolorSSD;
        bgColor = setupBGcolorSPD;
    } else {		//up
        eColorTL = setupEcolorSPTLU;
        eColorBR = setupEcolorSPBRU;
        fontColor = setupFcolorSSU;
        bgColor = setupBGcolorSPU;
    }

    xStart = SETUP_SUB_XSTART * 16;
    xWidth = 14 *16;
    yOffset = setup_item[setup_pos[1]][setup_pos[2]][MAX_ITEM_SEL];
    yStart = (setup_GetScaleItemPosition()+ SETUP_MENU_YSTART + 1)*SETUP_BUTTON_HEIGHT; // 2005/04/11 yltseng
    yDelta = setup_item[setup_pos[1]][setup_pos[2]][2] *SETUP_BUTTON_HEIGHT;

    osd_draw_rect(xStart, yStart, xWidth, yDelta, bgColor);

    //show the string in scale form
    setup_DrawScaleString(id, fontColor, bgColor);

    //draw the edges of scale form
    if (p_scan==1)
        osd_DrawLine(xStart, yStart, xStart+xWidth, yStart, eColorTL, 2);
    else
        osd_DrawLine(xStart, yStart, xStart+xWidth, yStart, eColorTL, 1);
    //left
    osd_DrawLine(xStart, yStart, xStart, yStart+yDelta, eColorTL, 1);
    //bottom
    if (p_scan==1)
        osd_DrawLine(xStart, yStart+yDelta, xStart+xWidth, yStart+yDelta, eColorBR, 2);
    else
        osd_DrawLine(xStart, yStart+yDelta, xStart+xWidth, yStart+yDelta, eColorBR, 1);
    //right
    osd_DrawLine(xStart+xWidth, yStart, xStart+xWidth, yStart+yDelta, eColorBR, 1);   
}



void setup_DrawScaleCursor(UINT8 id  __attribute__((unused)), BYTE upDown)
{
    BYTE    eColorTL, eColorBR; 
    BYTE    barColor, cursorColor; //bar, cursor color
    BYTE    clrCursorColor;
    UINT32  xStart, yStart, yOffset;
    UINT32  yDelta=0;
    UINT32  yEnd;

    
        if (upDown) {	//down
            eColorTL = setupEcolorSCTLD;
            eColorBR = setupEcolorSCBRD;
            barColor = setupBGcolorSCBD;
            cursorColor = setupBGcolorSCD;
            clrCursorColor = setupBGcolorSPD;
        } else {		//up
            eColorTL = setupEcolorSCTLU;
            eColorBR = setupEcolorSCBRU;
            barColor = setupBGcolorSCBU;
            cursorColor = setupBGcolorSCU;
            clrCursorColor = setupBGcolorSPU;
        }

    xStart = SETUP_SUB_XSTART * 16 + 76;
    yOffset = setup_item[setup_pos[1]][setup_pos[2]][MAX_ITEM_SEL];
    yStart = (setup_GetScaleItemPosition()+SETUP_MENU_YSTART)*SETUP_BUTTON_HEIGHT + 40; // 2005/04/11 yltseng
    yDelta = setup_item[setup_pos[1]][setup_pos[2]][2] *SETUP_BUTTON_HEIGHT - 12;

	// flush cursor area
    //osd_draw_rect(xStart-20, yStart-1, 40, yDelta+2, clrCursorColor);
    osd_draw_rect(xStart-20, yStart-1, 20, yDelta+2, clrCursorColor);     //wangmin change for avoid flash when move cursor up or down 051231
    osd_draw_rect(xStart+5, yStart-1, 15, yDelta+2, clrCursorColor);       //wangmin change for avoid flash when move cursor up or down 051231
    // draw cursor bar
    osd_DrawLine(xStart, yStart, xStart, yStart+yDelta, barColor, 3);

	// draw cursor body
    yEnd = yStart+yDelta - (setup_sel[setup_pos[1]][setup_pos[2]]-2+1)*SETUP_BUTTON_HEIGHT/2;
    xStart = SETUP_SUB_XSTART * 16 + 60;
    osd_draw_rect(xStart, yEnd, 32, 8, cursorColor);

    //draw the edges of scale cursor
    if (p_scan==1)
        osd_DrawLine(xStart, yEnd, xStart+36, yEnd, eColorTL, 2);
    else
        osd_DrawLine(xStart, yEnd, xStart+36, yEnd, eColorTL, 1);
    //left
    osd_DrawLine(xStart, yEnd, xStart, yEnd+8, eColorTL, 1);
    //bottom
    if (p_scan==1)
        osd_DrawLine(xStart, yEnd+8, xStart+36, yEnd+8, eColorBR, 2);
    else
        osd_DrawLine(xStart, yEnd+8, xStart+36, yEnd+8, eColorBR, 1);
    //right
    osd_DrawLine(xStart+34, yEnd, xStart+34, yEnd+8, eColorBR, 1);        
}




