/*************************************************
* setup_newstyle_ui.c
*
*  include when NEW_STYLE_SETUP  for GBM
*
*  UI function:
*     LEFT,RIGHT, UP, DOWN,  SELECT, ShowSetupPage. 
* 
* Creator: zhaoyanhua 
* Date:  3-7-25 17:12
**************************************************/

#ifdef SDRAM_16Mb_Mode//zhaoyanhua add 2003-11-10 16:33
#include "memmap.h"
#include "memmap0.h"
#endif

void ShowCUSTMMsg(void);
void ShowCurrentPage_for_NTSC(int page);
void ShowCurrentPage_for_PAL(int page);
void draw_setup_Btn_HL(UINT8 r, int xStart, int yStart, int xLen, int yLen );

#ifdef IR_KEY_SET_VIDEO_MODE
#ifdef SET_4_VIDEO_MODE
#define VIDEO_MODE_VAL_DEFAULT 		3
#else//#ifdef SET_4_VIDEO_MODE
#define VIDEO_MODE_VAL_DEFAULT 		0
#endif//#ifdef SET_4_VIDEO_MODE
#endif//#ifdef IR_KEY_SET_VIDEO_MODE

#if defined(GBM_DVD)&&!defined(GBM_FULL_FUNCTION)&&!defined(USER_MPEG_LOGO)
#undef SAME_DISC_RESUME
#endif

#define NTSC_AUDIO_YSTART   2
#define NTSC_LAN_YSTART     163
#define NTSC_VIDEO_YSTART   4
#define NTSC_SYSTEM_YSTART  235
#define NTSC_EXIT_YSTART   221
#define PAL_AUDIO_YSTART   0
#define PAL_LAN_YSTART     185-HL_OFFSET+5+3
#define PAL_VIDEO_YSTART   5-3
#define PAL_SYSTEM_YSTART  265-HL_OFFSET+5+3
#define PAL_EXIT_YSTART    251-HL_OFFSET+15

#define HL_XSTART_OFFSET	3
#define HL_OFFSET	20
/*
** FUNC: Show the Highlight (hand icon)
**       and setup menu in current page.
**
** zhaoyanhua 
** date: 3-7-14 10:44
*/
void ShowCurrentPage_for_NTSC(int page)
{

	#ifdef MONE_SETUP
    	printf("&&&&-------SHOW CURRENt page ! page = %d\n",page);
	#endif

	if (page ==3)
	{
		osd_tog_region(0,OSD_ON);
		//osd_tog_region(2,OSD_OFF);
	}
	else if ((page == 0) || (page == 7))
	{
		osd_tog_region(0,OSD_OFF);
		//osd_tog_region(2,OSD_ON);
	}
	else
	{
		osd_tog_region(0,OSD_OFF);
		//osd_tog_region(2,OSD_OFF);
	}
	
	/*
 	char *str1 = "PRESS";
	memset(linebuf,0,100);
	osd_DrawString(0, 0, str1, 11, 0);
	*/
	switch (page)
	{
		case  SYSPAGE:
							
			draw_setup_Btn_HL(1, 227+HL_OFFSET-HL_XSTART_OFFSET,NTSC_SYSTEM_YSTART , 140-HL_OFFSET, 67);
							

			break;
			case  LANGPAGE:
		
			draw_setup_Btn_HL(1, 8+HL_OFFSET-HL_XSTART_OFFSET , NTSC_LAN_YSTART, 140-HL_OFFSET, 67);
							
			break;

		case  AUDPAGE:
							
			draw_setup_Btn_HL(1, 8+HL_OFFSET-HL_XSTART_OFFSET, NTSC_AUDIO_YSTART , 140-HL_OFFSET,67);
							
			break;

		case  MULTISPKPAGE:
							
			draw_setup_Btn_HL(1, 450+HL_OFFSET-HL_XSTART_OFFSET , NTSC_AUDIO_YSTART, 140-HL_OFFSET, 67);
							
			break;
			case  AC3DIGITALPAGE:

			draw_setup_Btn_HL(1, 450+HL_OFFSET-HL_XSTART_OFFSET, NTSC_LAN_YSTART , 140-HL_OFFSET, 67);
							
			break;
			case  VIDEOPAGE:
			
			draw_setup_Btn_HL(0, 18+HL_OFFSET-HL_XSTART_OFFSET, NTSC_VIDEO_YSTART , 140-HL_OFFSET, 67);
							
			break;
		case  EXITPAGE :
			{
				osd_draw_rect(0, 0, 38*16, 9*SETUP_BUTTON_HEIGHT+24, 0);
							 osd_DrawIcon(445, NTSC_EXIT_YSTART , 0,page);	
								
				break;
			}
		default:  break;
	}

    #ifdef ROLL_SHOW_SETUP
    if(page != EXITPAGE)//nono 20030919
    //show osd msg from BUTTON start to BUTTON end.
    MoveBuf2OSD(SETUP_MENU_XSTART+10, (SETUP_MENU_XSTART+10)+(SETUP_SUB_XSTART-SETUP_MENU_XSTART-1));   
    #endif

}


void ShowCurrentPage_for_PAL(int page)
{

	#ifdef MONE_SETUP
    	printf("&&&&-------SHOW CURRENt page ! page = %d\n",page);
	#endif

	if (page ==3)
	{
		osd_tog_region(0,OSD_ON);
		//osd_tog_region(2,OSD_OFF);
	}
	else if ((page == 0) || (page == 7))
	{
		osd_tog_region(0,OSD_OFF);
		//osd_tog_region(2,OSD_ON);
	}
	else
	{
		osd_tog_region(0,OSD_OFF);
		//osd_tog_region(2,OSD_OFF);
	}

	/*
 	char *str1 = "PRESS";
	memset(linebuf,0,100);
	osd_DrawString(0, 0, str1, 11, 0);
	*/
	switch (page)
	{
		case  SYSPAGE:
							
			draw_setup_Btn_HL(1, 227+HL_OFFSET-HL_XSTART_OFFSET, PAL_SYSTEM_YSTART, 140-HL_OFFSET, 70);
							

			break;
			case  LANGPAGE:
			
			draw_setup_Btn_HL(1, 8+HL_OFFSET-HL_XSTART_OFFSET, PAL_LAN_YSTART, 140-HL_OFFSET, 70);
							
			break;

		case  AUDPAGE:
							
			draw_setup_Btn_HL(1, 8+HL_OFFSET-HL_XSTART_OFFSET, PAL_AUDIO_YSTART, 140-HL_OFFSET,70);
							
			break;

		case  MULTISPKPAGE:
							
			draw_setup_Btn_HL(1, 450+HL_OFFSET, PAL_AUDIO_YSTART, 140-HL_OFFSET, 70);
							
			break;
			case  AC3DIGITALPAGE:
			
			draw_setup_Btn_HL(1, 450+HL_OFFSET, PAL_LAN_YSTART, 140-HL_OFFSET, 70);
							
			break;
			case  VIDEOPAGE:
			
			draw_setup_Btn_HL(0, 18+HL_OFFSET-HL_XSTART_OFFSET, PAL_VIDEO_YSTART, 140-HL_OFFSET, 70);
							
			break;
		case  EXITPAGE :
			{
				osd_draw_rect(0, 0, 38*16, 13*SETUP_BUTTON_HEIGHT+10, 0);
				osd_DrawIcon(445, PAL_EXIT_YSTART, 0,page);	
								
				break;
			}
		default:  break;							
	}
    #ifdef ROLL_SHOW_SETUP
    if(page != EXITPAGE)//nono 20030919
    MoveBuf2OSD(SETUP_MENU_XSTART+10, (SETUP_MENU_XSTART+10)+(SETUP_SUB_XSTART-SETUP_MENU_XSTART-1));   
    #endif
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
	extern const UINT8 ServoVersion[];
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

	//psprintf(buf, "%c SUM:", regs0->stamp+'A');
	//psprintf(buf, "%c SUM:", (regs0->stamp&0x7f)+'A');//4-8-26 16:06
	psprintf(buf, "%02x%03x", (regs0->stamp & 0xff),get_iop_b_status()); //2004/11/30 ycwen
	osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);

				
}


/*
**FUNC : draw a rect border to show which button is select.
**
** zhaoyanhua 
** Date: 2003-07-22 15:49
*/
void draw_setup_Btn_HL(UINT8 r, int xStart, int yStart, int xLen, int yLen )
{
	osd_draw_region_rect(xStart, yStart, xLen, yLen, BUTTON_COLOR, r);
	osd_draw_region_rect(xStart+4, yStart+4, xLen-8, yLen-8, 0, r );		
}

void setup_func_down(void)
{
    const char *str;
    int     i;
   
    reset_passwd_cnt();

	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);

    if (setupLevel==0) { //main menu page
   
/*
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

        #ifdef TWO_CHANNEL_ONLY
        if (page==MULTISPKPAGE)     page--;
        #endif//SetMovePointer(38, 15);//system Button
	
*/

		return;
    } else
	if (setupLevel==1) {
		//second level menu page
		if ( (index_y+index_y_start) < (setupItemNum[1]-1)) {
			if (full_scrn&CUSTM) {
				//CUSTM menu page
				//clear third-level menu
#ifdef  RATING_8
                if (index_y == 3) 
                {
                    osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						SETUP_MENU_YSTART,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						8*SETUP_BUTTON_HEIGHT,//(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
						SBGCOLOR);

					ShowCUSTMMsg();
						
				}
				else
#endif//end RAGING_8
				{
					osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						7*SETUP_BUTTON_HEIGHT,//(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
						SBGCOLOR);
				}
					
				id = setup_item[page][index_y][1];

				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

				index_y++;

				id = setup_item[page][index_y][1];

				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);

				//the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
                #ifdef RCD_GPIO_CONTROL                                             // alan 2002/7/26 02:08下午
				if (index_y < (4)) {
                #else
				if (index_y < (6-1)) {
                #endif
					//draw ">>" between sub-mean and it's corresponding selection area

					#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:52 clead 2003-8-6 
					if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
					#endif 							

					osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);

					submenuStart = index_y+SETUP_MENU_YSTART;

					if (setup_item[page][index_y][0]==SET_NM) {
						char buf[8];
								
#ifdef RATING_8
						osd_draw_rect((SETUP_SUB_XSTART-1)*16,
										  (SETUP_MENU_YSTART+4)*SETUP_BUTTON_HEIGHT,
										  (SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
										  5*SETUP_BUTTON_HEIGHT,
										  SBGCOLOR);
#endif		
								
						psprintf(buf, "%04d", UserSet.parent_passwd);
						osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
						osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, 4, SBGCOLOR);
					} else {
						//get select item
						sel = setup_sel[page][index_y];
#ifdef RATING_8
						if ( page!=SYSPAGE&&index_y==3 )
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
			} else {
				//normal setup second-level page

				if (index_y > (SETUP_MAX_LINE-5)) {
					index_y = SETUP_MAX_LINE-5;
					index_y_start++;
					ShowSetupPage(1);
				}

				//clear third-level menu
				osd_draw_rect((SETUP_SUB_XSTART-1)*16,
							SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT,
							(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
							10*SETUP_BUTTON_HEIGHT,
							SBGCOLOR);

				id = setup_item[page][index_y+index_y_start][1];
				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

//                    #ifndef SETUP_ALL_VALID
#if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)       //gerry,2004-1-17 0:40   
						//special case
				if ( (page==MULTISPKPAGE) &&
							(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)
							)
				{
					index_y++;
//							if ( (index_y+index_y_start) == SPKSTART) {
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
				#if defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)      //gerry,2004-1-17 0:40
				else 
				#endif//ONLY_DOWNMIXOFF_CAN_SET_CE_RE				
#endif//ONLY_DOWNMIXOFF_CAN_SET_CE_RE 

                #ifndef SETUP_ALL_VALID					
				if (page==AUDPAGE) {
                	if ( (SETUP_SPDIF==SPDIFBITSTREAM) &&
									(index_y==DIGIOUTITEM) &&
									( ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
									//AUDIF_CODING_MODE_PCM|   //DTSCD-BITSTREAM MODE, Jeff 20020719
									AUDIF_CODING_MODE_DTS)
									)||(cd_subtype==CD_DTS) )//nono 2-7-25 17:29
									)
                    {
                    	index_y += (VOLCTRLEND-VOLCTRLSTART+2);
                    } else
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
//				    index_y=AC3DYNAMICITEM1+1;
                    #endif //NO_AC3_DYNAMIC_RANGE
				} else
                #endif //SETUP_ALL_VALID
				{
					index_y++;
				}

				if (setup_item[page][index_y+index_y_start][0]==SET_SPACE)    index_y++;

				id = setup_item[page][index_y+index_y_start][1];

				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);

				//the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
				if ((index_y+index_y_start) < (setupItemNum[1]-1)) {
								//draw ">>" between sub-mean and it's corresponding selection area

					#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:52 clead 2003-8-6 
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
						osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, 4, SBGCOLOR);
					} else
					if (setup_item[page][index_y+index_y_start][0]==SET_SCALE) {
						setup_PrepareScaleItem(id, 0);
					} else {
						//special item(LANGUAGE)
                        #ifdef RATING_8
#ifdef GBM_FULL_FUNCTION
						if (page==LANGPAGE || ((page==SysNextPage) && (index_y==GRADEITEM)) ) {
#else//GBM_FULL_FUNCTION
						if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) {
#endif//GBM_FULL_FUNCTION										
						// if (page==LANGPAGE||(SETUP_GRADE==STR_OS_RATING )) {
                        #else
						if (page==LANGPAGE) {
                        #endif
							submenuStart = SETUP_MENU_YSTART; //from 0
						}

						//draw third-level menu
						for (i=2; i<MAX_ITEM_SEL; i++) {
							//get select item
							sel = setup_sel[page][index_y];

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
				return;
			}
		}
    } else
	if (setupLevel==2) {
		if (setup_item[page][index_y][0]==SET_SCALE) {
			setup_CookScaleItem(id, 0);
			run_save_sel_cmd(page,index_y);
		} else
		if ( (index_y2 < (setupItemNum[2]-1)) && (setup_item[page][index_y][0]!=SET_NM) ) {
			//third-level menu page
			sel = setup_sel[page][index_y];

			id = setup_item[page][index_y][index_y2+2];

			ShowSel(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,(index_y2+2) == sel);
			index_y2++;
			ShowSel(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2,(index_y2+2) == sel);
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

#if 1//defined(GBM_UP_DOWN_SHOW_LONG_MENU)		//gerry,2004-2-7 17:51
	//draw menu title
	if (full_scrn&CUSTM)
		show_main_title(STR_OS_MENU);
	else
	{
		if (GBM_run_setupmenu_flag)//zhaoyanhua add 3-7-14 19:32
		{
#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME	//freyman 2004-3-25 23:52
#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP			//gerry for gbm,2004-2-2 15:37
			if (page==SysNextPage)
			{
				//show_main_title(setup_MainP[0][0]);
				if(IsOSDChinese())
					show_main_title(setup_item[0][6][1]);
				else
					show_main_title(STR_OS_PREV_PAGE);
			}
			else
#else
			if (page==SysNextPage)
				show_main_title(setup_MainP[0][0]);
			else
#endif
#endif//SAME_DISC_RESUME
				show_main_title(setup_MainP[page][0]);
		}	
	}	
#endif//defined(GBM_UP_DOWN_SHOW_LONG_MENU)		//gerry,2004-2-7 17:51								

}


void setup_func_up(void)
{
    BYTE    upperbound;
    const char *str;
    int     i;
    
    SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
    reset_passwd_cnt();

    if (full_scrn&CUSTM) {
        upperbound=2;
    } else {
        upperbound=0;
    }

    if (setupLevel==0) {
    	
   		return;
    } else
	if (setupLevel==1) {
		if (index_y==0)
		{
			return ;
		
		} else
		if ( (index_y+index_y_start) > upperbound) {
			if (full_scrn&CUSTM) {
				//clear third-level menu
#ifdef  RATING_8
            	if (index_y == 3) 
                {
					osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						SETUP_MENU_YSTART,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						8*SETUP_BUTTON_HEIGHT,//(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
						SBGCOLOR);

					ShowCUSTMMsg();
						
				}
				else
#endif//end RAGING_8
				{
					osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						(SETUP_MENU_YSTART+3)*SETUP_BUTTON_HEIGHT,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						7*SETUP_BUTTON_HEIGHT,//(SETUP_MAX_LINE-SETUP_MENU_YSTART-2)*SETUP_BUTTON_HEIGHT,
						SBGCOLOR);
				}
				id = setup_item[page][index_y][1];
				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

				index_y--;

				id = setup_item[page][index_y][1];
				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);
				//draw ">>" between sub-mean and it's corresponding selection area

				#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:53 clead 2003-8-6 
				if((id!=STR_OS_NEXT_PAGE)&&(id!=STR_OS_PREV_PAGE))
				#endif 							

				osd_DrawString(SETUP_SUB_XSTART-1, index_y+SETUP_MENU_YSTART+1, Ch_arrorR, SFONTCOLOR, SBGCOLOR);
				submenuStart = index_y+SETUP_MENU_YSTART;

				if (setup_item[page][index_y][0]==SET_NM) {
					char buf[8];
                    psprintf(buf, "%04d", UserSet.parent_passwd);
                    osd_draw_setup_button(SETUP_SUB_XSTART, (submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                    osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, 4, SBGCOLOR);

				} else {
                	//get select item
                    sel = setup_sel[page][index_y];
#ifdef RATING_8
                    if ( page!=SYSPAGE&&index_y==3 ) {
                    	submenuStart = SETUP_MENU_YSTART;
                    }
                    else{
                    	submenuStart = index_y+SETUP_MENU_YSTART;
                    }
#else
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
				osd_draw_rect((SETUP_SUB_XSTART-1)*16,
						SETUP_MENU_YSTART*SETUP_BUTTON_HEIGHT,
						(SETUP_MAX_WIDTH-SETUP_SUB_XSTART-1)*16,
						10*SETUP_BUTTON_HEIGHT,
						SBGCOLOR);

				id = setup_item[page][index_y+index_y_start][1];
				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 0);

				index_y--;
				if (setup_item[page][index_y+index_y_start][0]==SET_SPACE)    index_y--;

//#ifndef SETUP_ALL_VALID
#if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)           //gerry,2004-1-17 0:39
					//special case
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
			#ifndef SETUP_ALL_VALID					
				if (page  ==AUDPAGE) {
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
                    } else
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
						( (SETUP_AC3DIGITAL_OUTMODE!=AC3DYNAMICITEM2) 
//						||(SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF)
						)
						)
				{
					index_y--;
//					index_y=AC3DYNAMICITEM1-1;
				}
#endif //NO_AC3_DYNAMIC_RANGE

#endif //#ifndef SETUP_ALL_VALID

				id = setup_item[page][index_y+index_y_start][1];

				setup_DrawItem(1, index_y+SETUP_MENU_YSTART+1, 1);

				//the last active item in sub-menu is "EXIT", so we skip it's drawing selection area
				if ( (index_y+index_y_start) < (setupItemNum[1]-1)) {
						//draw ">>" between sub-mean and it's corresponding selection area

					#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:53 clead 2003-8-6 
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
						osd_DrawString(SETUP_SUB_XSTART+1, (submenuStart)+1, str, 4, SBGCOLOR);
					} else
					if (setup_item[page][index_y+index_y_start][0]==SET_SCALE) {
						setup_PrepareScaleItem(id, 0);
					} else {
						//special item(LANGUAGE)
#ifdef RATING_8
#ifndef GBM_FULL_FUNCTION
						if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) {
#else//GBM_FULL_FUNCTION
						if (page==LANGPAGE || ((page==SysNextPage) && (index_y==GRADEITEM)) ) {
#endif//GBM_FULL_FUNCTION								
#else
						if (page==LANGPAGE) {
#endif
							submenuStart = SETUP_MENU_YSTART; //from 0
						}

						//get select item
						sel = setup_sel[page][index_y+index_y_start];
						//draw third-level menu
						for (i=2; i<MAX_ITEM_SEL; i++) {
							const char *str;
							id = setup_item[page][index_y+index_y_start][i];
							if (id==0) break;

							str = setup_SetItemString();

							if (sel == i) {
								osd_draw_setup_button(SETUP_SUB_XSTART, (i-2+submenuStart)+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
								osd_DrawString(SETUP_SUB_XSTART+1, (i-2+submenuStart)+1, str, 4, SBGCOLOR);
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
			setup_CookScaleItem(id, 1);
			run_save_sel_cmd(page,index_y);
		} else
		if ( (index_y2 > upperbound) && (setup_item[page][index_y][0]!=SET_NM) ) {
			//third-level menu page
			sel = setup_sel[page][index_y];

			id = setup_item[page][index_y][index_y2+2];
			str = setup_SetItemString();


			if ((index_y2+2) == sel) {
				//keep upper button to UP mode with SANTIBGCOLOR
				osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
				osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, 4, SBGCOLOR);
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
#if 1//defined(GBM_UP_DOWN_SHOW_LONG_MENU)		//gerry,2004-2-7 17:51
	//draw menu title
	if (full_scrn&CUSTM)
		show_main_title(STR_OS_MENU);
	else
	{
		if (GBM_run_setupmenu_flag)//zhaoyanhua add 3-7-14 19:32
		{
#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:53
#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP			//gerry for gbm,2004-2-2 15:37
			if (page==SysNextPage)
			{
				//show_main_title(setup_MainP[0][0]);
				if(IsOSDChinese())
					show_main_title(setup_item[0][6][1]);
				else
					show_main_title(STR_OS_PREV_PAGE);
			}
			else
#else
			if (page==SysNextPage)
				show_main_title(setup_MainP[0][0]);
			else
#endif
#endif//SAME_DISC_RESUME
				show_main_title(setup_MainP[page][0]);
		}	
	}	
#endif//defined(GBM_UP_DOWN_SHOW_LONG_MENU)		//gerry,2004-2-7 17:51

}

void setup_func_left(void)
{
    const char *str;

	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);


    if ( (setupLevel==0))
    {
    	#ifdef MONE_SETUP	
    	printf("-------LEFT! page = %d\n",page);
		#endif    


//terry 20030802
    		if (page >=7)
    			page = 0;
   			else
    			page++;
    		
			if (page > 5)
				page = 7; //to exit page. zhaoyanhua 3-7-14 13:07

/*

    	if (page>0)
   		{
   			if (page == 7)
   				page = page - 2;//Exit->DIRTIAL page.zhaoyanhua note 3-7-14 11:26
   			else
   				page--;
   		}
   		else
   			page = 7;//EXIT page.
  */ 			
   		
    	setupLevel=1;
   		if (page <= 5)
   			ShowSetupPage(0);
   		/*else
   		//if (page > 5)
   		{
   			osd_draw_rect(0, 0, 38*16, 9*SETUP_BUTTON_HEIGHT+24, 0);
   			//osd_draw_rect(0, 0, 22*16, 9*SETUP_BUTTON_HEIGHT, 0);
   		}	//osd_tog_region(1,OSD_OFF);
		*/

    	if (getVPP_TVsystem() ==  1)//terry,0813
		{
			
			ShowCurrentPage_for_PAL(page);
		
		}else
		{	
			
			ShowCurrentPage_for_NTSC(page);
	
		}
    	//ShowCurrentPage(page);
    	setupLevel=0;
    	/*
    	// make tab disable
    	osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+9, 1);
    	if (p_scan==1)
   			osd_DrawLine((line*page)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
   		else
   			osd_DrawLine((line*page)/6+11, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+9, SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);

   		if (page>0)
   			page--;
   		else
   			page=5;

#ifndef SETUP_ALL_VALID		// alan, 2003/7/18 10:49上午
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
  		osd_draw_rect(line*page/6+13, 11+1, line/6-4, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);

   		// highlight : draw a frame to identify which tab is enable
   		SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
		osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SANTIBGCOLOR,1);

   		setupLevel=1;
   		ShowSetupPage(0);
   		setupLevel=0;*/
    }
    
    else
    
    if (setupLevel==2) { //left operation only active when switch to selection area of sub-menu
        if (full_scrn&CUSTM) {
            if (setup_item[page][index_y][0]==SET_NM) {
				char buf[8];
                osd_draw_setup_button(SETUP_SUB_XSTART, submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 0);
                psprintf(buf, "%04d", UserSet.parent_passwd);
                osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, SFONTCOLOR, SBGCOLOR);
            } else {
                id = setup_item[page][index_y][index_y2+2];
                str = _OsdMessegeFont1[osd_font_mode][id];
                if ((index_y2+2) == sel) {
                	osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
                    osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, 4, SBGCOLOR);
                } else {
                    setup_DrawItem(2, index_y2+submenuStart+1, 0);
                }
            }
        } else {
#ifdef RATING_8
			if ( page!=SYSPAGE&&index_y==3 ) {
				submenuStart = SETUP_MENU_YSTART;}
			else{
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
            } else
				if (setup_item[page][index_y][0]==SET_SCALE) {
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
				} else {
					//special item(LANGUAGE)
#ifdef RATING_8
					//if (page==LANGPAGE||(setup_sel[page][index_y]==SETUP_GRADE )) {
#ifndef GBM_FULL_FUNCTION
					if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) {
#else//GBM_FULL_FUNCTION
					if (page==LANGPAGE || ((page==SysNextPage) && (index_y==GRADEITEM)) ) {
#endif//GBM_FULL_FUNCTION					
#else
						if (page==LANGPAGE) {
#endif
							submenuStart = SETUP_MENU_YSTART; //from 0
						}

						id = setup_item[page][index_y][index_y2+2];
						str = setup_SetItemString();

						if ((index_y2+2) == sel) {
							osd_draw_setup_button(SETUP_SUB_XSTART, index_y2+submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SBGCOLOR, 1);
							osd_DrawString(SETUP_SUB_XSTART+1, index_y2+submenuStart+1, str, 4, SBGCOLOR);
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
}

void setup_func_right(void)
{
	const char *str;
	
	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffc0);
  
    if (setupLevel==0)
    {

    	// make tab disable
    	
/*    		if (page >=7)
    			page = 0;
    		else
    			page++;
    		
			if (page > 5)
				page = 7; //to exit page. zhaoyanhua 3-7-14 13:07
*/
//terry 20030802
    	if (page>0)
   		{
   			if (page == 7)
   				page = page - 2;//Exit->DIRTIAL page.zhaoyanhua note 3-7-14 11:26
   			else
   				page--;
   		}
   		else
   			page = 7;//EXIT page.

   			
			
			setupLevel=1;
   			if (page <= 5)  //exit page not show.
   				ShowSetupPage(0);
   			/*
   			else
   			{
   				//osd_tog_region(1,OSD_OFF);
   				osd_draw_rect(0, 0, 38*16, 7*SETUP_BUTTON_HEIGHT+15, 0);
   				//osd_draw_rect(0, 0, 22*16, 9*SETUP_BUTTON_HEIGHT, 0);
   			}*/
   			setupLevel=0;
   			//ShowCurrentPage(page);
   			
    	if(getVPP_TVsystem() ==  1)//terry,0813
		{
			
			ShowCurrentPage_for_PAL(page);
		
		}else
		{	
			
			ShowCurrentPage_for_NTSC(page);
	
		}

    /*    if ( (page==MULTISPKPAGE) &&  (cd_type_loaded!=CDDVD) && ( coding_mode_now&(~(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD)) ) )
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

        #ifdef TWO_CHANNEL_ONLY
        if (page==MULTISPKPAGE)     page++;
        #endif
*/
    	
	
/*
    	// highlight : draw a frame to identify which tab is enable
    	SetOsdCol(0,0,SANTIBGCOLOR,0xa346ffff);
		osd_DrawLine(line*page/6+30,14,line*page/6+80,14,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+30,50,line*page/6+80,50,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+30,14,line*page/6+30,50,SANTIBGCOLOR,1);
		osd_DrawLine(line*page/6+80,14,line*page/6+80,50,SANTIBGCOLOR,1);

    	setupLevel=1;
    	ShowSetupPage(0);
    	setupLevel=0;
   */
    }
    else
   
	//right operation only active when switch to menu of sub-menu
	if (setupLevel==1) {

	if (index_y==(setupItemNum[1]-1)) return;

    #ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:53
    //zhaoyanhua add 2003-8-8 17:11
    //not draw 3rd menu  when turn right at NEXTPAGE/PREVPAGE, 
    if ((page == SYSPAGE)&&(index_y == NEXTPAGEITEM))
        return;
    #ifdef USER_LOGO
    else if ((page == SysNextPage)&&(index_y == PREVPAGEITEM))
    #else//#ifdef USER_LOGO
    else if ((page == SysNextPage)&&(index_y == PREVPAGEITEM-1))//PREVPAGEITEM-1=2
    #endif//#ifdef USER_LOGO
        return;
	#endif//SAME_DISC_RESUME

	//check GRADE
#ifdef GBM_FULL_FUNCTION
	if ( (page==SysNextPage) && (index_y==GRADEITEM) ) {
#else//GBM_FULL_FUNCTION
	if ( (page==SYSPAGE) && (index_y==GRADEITEM) ) {
#endif//GBM_FULL_FUNCTION	
		if (UserSet.parental_ststus==C_LOCK) return;
	}

	//change string color of current item in sub-menu
	osd_draw_setup_button(SETUP_MENU_XSTART, index_y+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, SBGCOLOR, 1);

	id = setup_item[page][index_y][1];
	str = _OsdMessegeFont1[osd_font_mode][id];
	osd_DrawString(SETUP_MENU_XSTART+1, index_y+SETUP_MENU_YSTART+1, str, 4, SBGCOLOR);

	//change string color of current selection item in selection area
	submenuStart = index_y + SETUP_MENU_YSTART;
	sel = setup_sel[page][index_y];

	index_y2 = sel-2;

	if (full_scrn&CUSTM) {
		//special item(PASSWORD), page-0, item-4
		if (setup_item[page][index_y][0]==SET_NM) {
			char buf[8];
			osd_draw_setup_button(SETUP_SUB_XSTART, submenuStart+1, SETUP_MAX_WIDTH-SETUP_SUB_XSTART-2, SANTIBGCOLOR, 1);
			psprintf(buf, "%04d", UserSet.parent_passwd);
			osd_DrawString(SETUP_SUB_XSTART+1, submenuStart+1, buf, SANTIFONTCOLOR, SANTIBGCOLOR);
		} else {
			id = setup_item[page][index_y][index_y2+2];
#ifdef RATING_8
			if ( page!=SYSPAGE&&index_y==3 ) {
				submenuStart = SETUP_MENU_YSTART;}
			else{
                submenuStart = index_y+SETUP_MENU_YSTART;
			}
#else
			submenuStart = index_y+SETUP_MENU_YSTART;
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
				//if (page==LANGPAGE||(setup_sel[page][index_y]==SETUP_GRADE )) {
#ifndef GBM_FULL_FUNCTION
				if (page==LANGPAGE || ((page==SYSPAGE) && (index_y==GRADEITEM)) ) {
#else//GBM_FULL_FUNCTION				
				if (page==LANGPAGE || ((page==SysNextPage) && (index_y==GRADEITEM)) ) {
#endif//GBM_FULL_FUNCTION
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
//			printf("======In Right\n");
			setupLevel = 2;
	}
}


void setup_func_select(void)
{
	const char *str;
	UINT8   md=setup_item[page][index_y][0];

	#if defined(DVD_AUDIO)//dingzhy add it 04-03-23 3:57PM
	if(pDSV->hid_gp_chk_pwd==2)
	{

	    check_dvd_audio_password();//nono 2004/3/2 05:40PM
              return; 
	}
	#endif//#if defined(DVD_AUDIO)

	if (setupLevel == 0)//zhaoyanhua add  3-7-14 19:13
	{
		if (page <= 5)
		{
			GBM_run_setupmenu_flag =1;
			setupLevel = 1;
			#ifndef SDRAM_16Mb_Mode
			osd_init_setup();
			#endif
			
			#ifdef MONE_SETUP	
    			printf("&&&&-------SELECT \n");
			#endif   
			
			//zoom to show setup menu. zhaoyanhua 3-7-17 13:27
			/*setVPP_OffsetMode(OFFSET_USER);
			vpp_zoom = 1;//reference : ircmd_zoom() 
			startup_vpp();    
			setVPP_DoItNow();
			//setVPP_OffsetX(-160);
			//setVPP_OffsetY(-180);
    		*/
			//setup_state = 0;//according to the customer demand. 2003-07-19 11:58
			//full_scrn=SETUP;
			//play_state = 
			#ifdef SDRAM_16Mb_Mode
		    prog_state = 2;
		    #else
			setup_state = 2;
			#endif//SDRAM_16Mb_Mode
			ShowTitle();
			//play_state = VCD_STATE_PAUSE;
			//ircmd_play();
			//ircmd_stop();
			//system_stop();
			#ifdef SDRAM_16Mb_Mode
			//NOTE:
			//when SDRAM_16M_Mode,ShowTitle() may destroyed 
			// OSD memory. So must evaluate osd_base_addr again.
			//zhaoyanhua add 2003-11-10 17:06
			regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
			#endif
			
			#ifdef SDRAM_16Mb_Mode
			osd_init_setup();
			#endif
			
			ShowSetupPage(2);
			
			return;
		}
		else  //if enter "select " on EXITPAGE,exit SETUP. zhaoyanhua note 3-7-14 19:26
		{
			GBM_run_setupmenu_flag = 0;	
			#ifdef MONE_SETUP	
    			printf("&&&&------- page = 7SELECT \n");
			#endif  
			
			ExitSetupPage(1);
			#ifdef SDRAM_16Mb_Mode
			//to avoid the bug when exit setup ,not show display
			//zhaoyanhua add 2003-11-13 18:59
		    if (old_t_disp)
		    {
			    t_disp=old_t_disp;
			    DispPolling(3);
		    }
			#endif
						
		}
	}
	else if (setupLevel == 1)
	{
		sel=setup_sel[page][index_y+index_y_start];
		id=setup_item[page][index_y+index_y_start][1];

		if (id == STR_OS_RETURN_MAIN_SETUP)
		{
#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP			//gerry,2004-2-2 20:30
			if (page==7)		//in fact it is Prev-Page,2004-2-2 20:35
			{
			page=0;
			setupLevel=1;
			index_y = 0;
			index_y_start=0;
			ShowSetupPage(1);
			return;
			}
#endif//NEXT_PAGE_SHOW_ADVANCED_SETUP
			index_y=0;
			if (full_scrn&CUSTM)
			{
				ExitSetupPage(1);

			}
			else
			{
				//ExitSetupPage(1);
			
			//zhaoyanhua add 3-7-14 19:27

			GBM_run_setupmenu_flag = 0;


			//resume to Normal. zhaoyanhua 3-7-17 13:27
			/*setVPP_OffsetMode(OFFSET_USER);
			vpp_zoom = 0;
			startup_vpp();    
			setVPP_DoItNow();
			*/
			#ifdef SDRAM_16Mb_Mode
			prog_state = 4;
			ShowTitle();
			prog_state = 5;
			#else
			setup_state = 1;
			ShowTitle();
			setup_state = 3;
			#endif//SDRAM_16Mb_Mode
			
			#ifdef SDRAM_16Mb_Mode
			//NOTE:
			//when SDRAM_16M_Mode,ShowTitle() may destroyed 
			// OSD memory. So must evaluate osd_base_addr again.
			//zhaoyanhua add 2003-11-10 17:06
			regs0->osd_base_addr=OSD_BASE_USE_ADDR;//P_BIDIR_LUMA;
			#endif
			
			//play_state = VCD_STATE_PAUSE;
            #ifdef NEXTPAGE_SYS//SAME_DISC_RESUME //freyman 2004-3-25 23:53 zhaoyanhua add 2003-8-8 16:41
			if(page==SysNextPage)
			    page = SYSPAGE;
            #endif

            //printf("getVPP_TVsystem():%x\n",getVPP_TVsystem());
			if(getVPP_TVsystem() ==  1)//terry,0813
				{
					osd_init_hand_ICON_for_PAL();
					setupLevel=1;
					ShowSetupPage(0);//must showsetuppage,because it will clear the rect.
					setupLevel=0;
					ShowCurrentPage_for_PAL(page);
		
				}
			
			else 
				{	
					osd_init_hand_ICON_for_NTSC();
					setupLevel=1;
					ShowSetupPage(0);//must showsetuppage,because it will clear the rect.
					setupLevel=0;
					ShowCurrentPage_for_NTSC(page);
	
				}

			#ifdef MONE_SETUP
    		printf("&&&&-------exit setup page ------- \n");
			#endif 
			return;
		}
		}
		else
		{

#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:53 clead 2003-8-6 
			if (id==STR_OS_NEXT_PAGE)
			{
			page=SysNextPage;
			setupLevel=1;
			index_y = 0;
			index_y_start=0;
			ShowSetupPage(1);
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
			printf("======      clead PREV       ======\n\n");
			return;
			}else 
#endif 

			setup_func_right();
		}
	}
	else if (setupLevel == 2)
	{
		sel=setup_sel[page][index_y];
		id=setup_item[page][index_y][1];

		//PASSWORD item
		if (md==SET_NM)
		{
			if(digit_cnt==4)
			{
				if (UserSet.parental_ststus==C_LOCK && (tmp_passwd==UserSet.parent_passwd ||tmp_passwd==USER_SUPER_PASSWORD) )
				{
					show_lock(C_UNLOCK,1);
				}
				else
				{
					if(UserSet.parental_ststus==C_UNLOCK)
					{
						UserSet.parent_passwd=tmp_passwd;
					}

					if (!(full_scrn&CUSTM))
						show_lock(C_LOCK,1);
				}

				if(user_input_pwd!=1)//2002-6-13 for huajia
					run_save_sel_cmd(page,index_y);
			}

			reset_passwd_cnt();
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
		if ((index_y2+2) != sel)
		{
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

			sel = setup_sel[page][index_y];
			id = setup_item[page][index_y][1];

			if ( (page==CUSTMPAGEINDEX) && (id==STR_OS_RATING) )
			{
				SETUP_GRADE = SETUP_CUSTM_GRADE;
#ifdef GBM_FULL_FUNCTION
				run_save_sel_cmd(SysNextPage, GRADEITEM);
#else//GBM_FULL_FUNCTION
				run_save_sel_cmd(SYSPAGE, GRADEITEM);
#endif//GBM_FULL_FUNCTION				
			}

			if (md==SET_FUNC)
			{
				exe_setup_function(setup_item[page][index_y][1],setup_item[page][index_y][sel],1);
				// alan, 2003/8/22 07:32PM				
#ifdef SUPPORT_PROLOGIC_II
				if ( (setup_item[page][index_y][1]==STR_OS_PROLOGIC) &&
					 (setup_item[page][index_y][sel]!=STR_OS_OFF)
				   )
				{
					SETUP_SPDIF=2;
					exe_setup_function(STR_OS_AUD_OUT,STR_OS_SIMULATE,0);
				}
				
				if ( (setup_item[page][index_y][1]==STR_OS_AUD_OUT) &&
					 (setup_item[page][index_y][sel]!=STR_OS_SIMULATE)
				   )
				{
					SETUP_PROLOGIC_II=4;    // alan, 2003/8/11 01:56PM							
					exe_setup_function(STR_OS_PROLOGIC,STR_OS_OFF,0);
				}				
#endif//SUPPORT_PROLOGIC_II
			}

			run_save_sel_cmd(page,index_y);
			//  setup_func_left();
		}

        //ShowSetupPage(2);
		setup_func_left();

		if (id==STR_OS_DEFAULT_SETUP)
		{
			set_default_value();
			run_set_variable();
			run_save_total_sel();
			setupLevel = 1;
			ShowSetupPage(2);
			//nono 2003-8-26 1:42 for DTS mute after setup_default
			exe_setup_function(setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][1],
			        setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][ SETUP_SPK_DOWNMIX ],0);//nono 2003-8-26 0:50


		#ifdef IR_KEY_SET_VIDEO_MODE
		video_mode_val=VIDEO_MODE_VAL_DEFAULT;
		set_video_val(video_mode_val);
		//WriteToI2c(0xa0, 220,(BYTE *)&video_mode_val,1);
		#endif

            #ifdef VOLUME_RECODE
			{
				int volume;
				printf("audio_volume=%d\n",audio_volume);
				audio_volume = VOL_VALUE;       //set to max volume when we default gerry 2-11-6 9:26;
				printf("audio_volume=%d\n",audio_volume);
				volume=WriteToI2c(0xa0, ADDR_I2C_VOLUME, (BYTE *)&audio_volume,sizeof(audio_volume));
			}
			AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
            #endif //#ifdef VOLUME_RECODE

            #ifdef Ti3001_OSD_UI_1    // jason 2-10-5 15:30
			    reset_amplifier_default_setup();
			    AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
			    ti_set_volume(SET_ALL_VALUE); //ti_set_volume(SET_ALL_VALUE,TI_VOL_VALUE);
            #endif //#ifdef Ti3001_OSD_UI_1

			if ((cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) //nono 2-11-9 9:19
				AUDIF_Set_OutputMode(OUT_51DownmixLsRs, 0);//2004AUDDRV AudioSetOutputMode(0x09, 0); //Set Output mode(9:2 channel, surround effect)

			AUDIF_Set_Pause();//2004AUDDRV AudioSetPause(); //Jeff 20021017
        } //if (id==STR_OS_DEFAULT_SETUP)
	}
}


void ShowSetupPage(BYTE refresh)
{
	int     i;
	BYTE    fontColor, bgColor;
	BYTE    upDown;
	const char   *str;
	
	reset_passwd_cnt();

	if (full_scrn&CUSTM)
	{ //set to CUSTM mode
		osd_init_setup();
		setupLevel = 1;
		index_y = 2;
		index_y_start = 0;
	}
	//printf("refresh=:%d,setupLevel=:%d\n",refresh,setupLevel);
	if (refresh)
	{
		//draw main rect*
		if (!(full_scrn&CUSTM))
			osd_draw_rect(0,16, (SETUP_MAX_WIDTH*16), 12*SETUP_BUTTON_HEIGHT/*(SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT)*/, SBGCOLOR);
		else//for CUSTM
		{	
			osd_draw_rect(0, 0, (SETUP_MAX_WIDTH*16), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT), SBGCOLOR);
	
		if (p_scan==1)
		{
			//draw top horizontal line
			osd_DrawLine(12, SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 2);
			//draw bottom horizontal line
			osd_DrawLine(10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 2);
		} else {
			osd_DrawLine(12, SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-10), SETUP_BUTTON_HEIGHT+20, SWHITECOLOR, 1);
			osd_DrawLine(10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), (SETUP_MAX_WIDTH*16-10), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
		}
			//draw left vertical line
			osd_DrawLine(10, SETUP_BUTTON_HEIGHT+20, 10, (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SWHITECOLOR, 1);
			//draw right vertical line
			osd_DrawLine((SETUP_MAX_WIDTH*16-12), SETUP_BUTTON_HEIGHT+20, (SETUP_MAX_WIDTH*16-12), (SETUP_MAX_LINE*SETUP_BUTTON_HEIGHT-12), SBLACKCOLOR, 1);
		}
		
		if (refresh==2)
		{
			//osd_draw_rect(10, 10, line, SETUP_BUTTON_HEIGHT+10, 1);
			//osd_draw_rect((line*page)/6+10, 10, line/6, SETUP_BUTTON_HEIGHT+10, SBGCOLOR);
			/*for (i=0;i<6;i++)
			{
				if (p_scan==1)
					osd_DrawLine((line*i)/6+11, 10, (line*(i+1))/6+10, 10, SWHITECOLOR, 2);	// top
				else
					osd_DrawLine((line*i)/6+11, 10, (line*(i+1))/6+10, 10, SWHITECOLOR, 1);	// top
				osd_DrawLine((line*i)/6+11, 10, (line*i)/6+11, SETUP_BUTTON_HEIGHT+21, SWHITECOLOR, 1); // left
				osd_DrawLine((line*(i+1))/6+8, 10, (line*(i+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBLACKCOLOR, 1); // right
			}
			)
					
			osd_DrawLine((line*page)/6+12, SETUP_BUTTON_HEIGHT+20, (line*(page+1))/6+8, SETUP_BUTTON_HEIGHT+20, SBGCOLOR, 2);
		*/
		}

	} else
	{
		if (!(full_scrn&CUSTM))
		{
		if (!GBM_run_setupmenu_flag)//zhaoyanhua add 3-7-14 19:32
			{
				#ifdef ROLL_SHOW_SETUP //zhaoyanhua add 2003-8-15 13:45
				clrFrameBuffer(FRAME_BIDIR);
				#endif
				if( getVPP_TVsystem() ==  1)//terry,0813
					osd_draw_rect(0, 0, 38*16/*22*16*/, 13*SETUP_BUTTON_HEIGHT+10, 0);//9*SETUP_BUTTON_HEIGHT
				else
					osd_draw_rect(0, 0, 38*16/*22*16*/, 9*SETUP_BUTTON_HEIGHT+24, 0);//9*SETUP_BUTTON_HEIGHT
			}
		else
			osd_draw_rect(0/*20*/, 0/*SETUP_BUTTON_HEIGHT+24*/, (SETUP_MAX_WIDTH*15), /*12*SETUP_BUTTON_HEIGHT*/11*SETUP_BUTTON_HEIGHT, SBGCOLOR);
		}

	}
/*
	if (!(full_scrn&CUSTM))
	{
		if (p_scan==1)
		{
			osd_DrawIcon(4,13,0,page);
			osd_DrawIcon(16,13,1,page);
			osd_DrawIcon(27,13,2,page);
			osd_DrawIcon(38,13,3,page);
			osd_DrawIcon(50,13,4,page);
			osd_DrawIcon(61,13,5,page);
		}
		else {
			osd_DrawIcon(4,7,0,page);
			osd_DrawIcon(16,7,1,page);
			osd_DrawIcon(27,7,2,page);
			osd_DrawIcon(38,7,3,page);
			osd_DrawIcon(50,7,4,page);
			osd_DrawIcon(61,7,5,page);
		}
	}
*/
	if (setupLevel == 0)
	{//main page menu
        BYTE oldPage=page;
	
       //draw strings in main page menu
       for (i=0; i<MAX_PAGE_ITEM; i++)
       {
           BYTE iPageStr;
           BYTE updowngray;

           iPageStr = setup_MainP[i][0];
           if (iPageStr == STR_OS_SPACE) continue;
           if (iPageStr == STR_OS_NO) break;

           if (page == setup_MainP[i][1])
           {
                 updowngray = 1;
           } else
           {
                 updowngray = 0;
           }

            #ifndef SETUP_ALL_VALID
            //special case
            if ( (i==MULTISPKPAGE) && (cd_type_loaded!=CDDVD) &&
                    ( coding_mode_now&(~(AUDIF_CODING_MODE_AC3|
                    AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD))))
            {
                updowngray = 2;
            }
           else if ( (i==MULTISPKPAGE) &&(SETUP_SPDIF!=SPDIFSIMULATE))
           {
				updowngray = 2;
           }
           else if ( (i==AC3DIGITALPAGE) && ( (SETUP_SPDIF==SPDIFBITSTREAM) ||
					(coding_mode_now!=AUDIF_CODING_MODE_AC3)) 	)
           {//terry,2-4-27 22:35 , reference down and up key
			//we should use function avoid the bug.
					updowngray = 2;
		   }
            #endif

           page = i;

           setup_DrawItem(0, i+SETUP_MENU_YSTART+1, updowngray);
           page = oldPage;
        } //for (i=0; i<MAX_PAGE_ITEM; i++)

        setupItemNum[0]=i;
        
        
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
			show_main_title(STR_OS_MENU);
		else
		{
			if (GBM_run_setupmenu_flag)//zhaoyanhua add 3-7-14 19:32
			{
#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:53
#ifdef NEXT_PAGE_SHOW_ADVANCED_SETUP			//gerry for gbm,2004-2-2 15:37
				if (page==SysNextPage)
				{
					//show_main_title(setup_MainP[0][0]);
					if(IsOSDChinese())
					show_main_title(setup_item[0][6][1]);
					else
					show_main_title(STR_OS_PREV_PAGE);
				}
				else
#else
				if (page==SysNextPage)
				show_main_title(setup_MainP[0][0]);
				else
#endif
#endif//SAME_DISC_RESUME
				show_main_title(setup_MainP[page][0]);
		}	
		}	
			
		//draw item strings in sub menu
		for (i=index_y_start; i<setupItemNum[1]; i++)
		{
			if ( (i-index_y_start+1) > (SETUP_MAX_LINE-3) ) break;

			iItemType=setup_item[page][i][0];
			if (iItemType == SET_SPACE) continue;
			if (iItemType == SET_NE) break;

			id = setup_item[page][i][1];

			if (id==STR_OS_RETURN_MAIN_SETUP)  // no main page, so this item changes to exit_setup_menu
			{
				if ((!GBM_run_setupmenu_flag) && !(full_scrn & CUSTM))//zhaoyanhua add 3-7-14 19:32
					return;
				else
					id=STR_OS_EXIT_MENU;
			}
			str = _OsdMessegeFont1[osd_font_mode][id];
			if ( (index_y+index_y_start) == i)
			{
				if (setupLevel==1)
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

//            #ifndef SETUP_ALL_VALID
#if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)       //gerry,2004-1-17 0:44
                //special case
                if ( (page==MULTISPKPAGE) && (SETUP_SPK_DOWNMIX!=AC3DOWNMIXOFF) &&
                            ( (i>=SPKSTART) && (i<=SPKEND) ))
                {
                    fontColor = SGRAYCOLOR;
                } else
#endif//    #if !defined(SETUP_ALL_VALID)||defined(ONLY_DOWNMIXOFF_CAN_SET_CE_RE)    
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
                    fontColor = SGRAYCOLOR;
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
					fontColor = SGRAYCOLOR;
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
					if (i==index_y_start) fontColor=SFONTCOLOR;
				}
				if ((!GBM_run_setupmenu_flag) && !(full_scrn&CUSTM))//zhaoyanhua add 3-7-14 19:32
				{
					
					#ifdef ROLL_SHOW_SETUP //zhaoyanhua add 2003-8-14 15:50
					if(page != EXITPAGE)//nono 20030919
					{
					osd_draw_setup_button(SETUP_MENU_XSTART+10, i-index_y_start/*+SETUP_MENU_YSTART*/, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, bgColor, upDown);
					MoveString2Buf((SETUP_MENU_XSTART+10),i,str, fontColor, bgColor );
					}
					#else
					osd_draw_setup_button(SETUP_MENU_XSTART+10, i-index_y_start/*+SETUP_MENU_YSTART*/, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, bgColor, upDown);
					osd_DrawString(SETUP_MENU_XSTART+1+10, i-index_y_start/*+SETUP_MENU_YSTART*/, str, fontColor, bgColor);
				    #endif
				}
				else
				{
					osd_draw_setup_button(SETUP_MENU_XSTART, i-index_y_start+SETUP_MENU_YSTART+1, SETUP_SUB_XSTART-SETUP_MENU_XSTART-1, bgColor, upDown);
					osd_DrawString(SETUP_MENU_XSTART+1, i-index_y_start+SETUP_MENU_YSTART+1, str, fontColor, bgColor);
				}
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

				//psprintf(buf, "%c SUM:", regs0->stamp+'A');
				psprintf(buf, "%02x%04x", (regs0->stamp & 0xff),get_iop_b_status()); //2004/11/30 ycwen
				osd_DrawString(SETUP_SUB_XSTART, SETUP_MENU_YSTART+2, buf, SFONTCOLOR, SBGCOLOR);
				#endif
				
				ShowCUSTMMsg();
				index_y = 2;
			}

			if (refresh)
			{
				draw_3rd_menu();
			}
			return;

			//draw ">" between sub-mean and it's corresponding selection area

			#ifdef NEXTPAGE_SYS//SAME_DISC_RESUME		//freyman 2004-3-25 23:54 clead 2003-8-6 
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
				sel = setup_sel[page][index_y+index_y_start];

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


extern void wait_v_blank(void); // in vpp+dvd.c
extern BYTE rem_osd_id;//nono 2-7-15 21:34
void ExitSetupPage(BYTE save) //jhuang 2001/5/18 10:30PM
{
    int play=0;
    //save==1 save and exit setup menu
    //save==-1 NOT save and exit setup menu

    set_vpp_disp_size(0,0);//terry,2003/8/13 06:18PM

    //In CUSTM page, we set UserSet.parental_ststus=C_UNLOCK, so we resync UserSet.parental_ststus here
    //if (setup_sel[0][1] == (MIN_ITEM_SEL+1) ) {
    if (SETUP_PASSWORD == (MIN_ITEM_SEL+1) ) {
        UserSet.parental_ststus=C_UNLOCK;
    } else {
        UserSet.parental_ststus=C_LOCK;
        SETUP_PASSWORD=MIN_ITEM_SEL;
    }

    safe_srn_forceOFF();
    safe_srn_off();
    osd_disable();

#ifndef QISHENG_DVD
    if( (old_play_state==VCD_STATE_NORMAL)&&(play_state==VCD_STATE_PAUSE) )
        play|=0x01;
#endif

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
   //  if (prog_state != 3)
        {
            #include "memmap0.h"

            regs0->osd_base_addr=GetOSDBackUpAddress();
            osd_init();
         full_scrn=0;
         ClearOsdMsg(0);
         psprintf(RegionValStr[REGION1], "");
         PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);

       
         
         //for SDRAM_16Mb_Mode not support other types except MP3﹜JPEG
    /*    if ((cd_type_loaded == CDROM) && (pFsJpeg->gifsFuncBtn == 2))
            {
                prog_state=255;
            //for JPEG, it will be disposed in fsNav.c zhaoyanhua note 2003-8-7 8:59
                ircmd_post_func(CMD_FUNC | CMD_FUNC_PLAY);
       
        }
        else*/ 
        {
             if( (cd_type_loaded==CDROM)&&(Is_MP3_STATE()==0) )
            {
            /*
             //some funciton has been include in FS_ForceReturn2Menu().
            //to avoid when play JPEG, draw GUI menu more than once.
            //zhaoyanhua add 3-7-25 20:39
             #ifndef NEW_MP3_GUI 
                ReturnFromOtherModeToMenu();
    #endif
            */
            //Because ReturnFromOtherModeToMenu() is only valid in SUPPORT_FILE_SYSTEM.
            //so I changed the function  FS_ForceReturn2Menu();
            //zhaoyanhua note 2003-8-26 19:38
                FS_ForceReturn2Menu();
            
            //if(Is_OTHER_STATE()==0)
            //  pFsJpeg->gifsbPreview = 1;
		    }
            else if( (cd_type_loaded == CDDA)&&(old_play_state!=VCD_STATE_STOP) )
    	    {
    	        prog_state = 0;
    	        ShowTitle();
    	        ircmd_resume();
    	    }else if( (old_play_state==VCD_STATE_STOP)||
			(system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN) )
		    {
                prog_state=0;
		        ShowTitle();
		    }else
           {
                printf("================resume\n");
			    if ((prog_state != 6))
                ircmd_resume();
			    
			}
          prog_state = 0;
            }

        
            
        }
     
#else//NOT 16M mode

    //Terry,2002/4/29 01:16AM
    //Note: Don't revise the seq. .
    full_scrn=0;
    //terry,2002/5/10 02:52下午
    //move to osd1.c
    //ClearOsdMsg(0);
    //wait_v_blank();

    //zhaoyanhua mask 2003-8-7 9:38
    //#ifdef SDRAM_16Mb_Mode
    //   regs0->osd_base_addr=GetOSDBackUpAddress();
    //#endif
	
	#ifdef MONE_SETUP
	
		printf("--------iN EXITPAGE seutp_state = %d\n",setup_state);	
	#endif
	
	
		
		osd_init();
			
	 	setup_state = 0;		
			
		#ifdef MONE_SETUP
		printf("-------old_play_state=%d,play_state=%d\n",old_play_state,play_state);
		#endif
		
   	

        if( (cd_type_loaded==CDROM)&&(Is_MP3_STATE()==0) )
        {
        //some funciton has been include in FS_ForceReturn2Menu().
        //to avoid when play JPEG, draw GUI menu more than once.
        //zhaoyanhua add 3-7-25 20:39

		#if !(defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI))
		//#ifndef NEW_MP3_GUI 
            ReturnFromOtherModeToMenu();
      	#endif	
            
#ifdef JPEG_THUMBNAIL_MENU
            pFsJpeg->g_nJpegMode=0;//nono 2004-1-7 11:45
#endif//JPEG_THUMBNAIL_MENU
            
            FS_ForceReturn2Menu();
            
            //if(Is_OTHER_STATE()==0)
            //  pFsJpeg->gifsbPreview = 1;
		}
		else if ((play&0x01))
     	{
        	ircmd_play();
			#ifdef MONE_SETUP
			printf("================play !\n");
			#endif	
		}   
   // else if ((play_state!=VCD_STATE_STOP)&&(play_state!=VCD_STATE_IDLE))
   //     PrintOsdMsg(rem_osd_id,REGION1,1,0);//show "PAUSE" & "STEP"...after "setup" 2-7-15 21:44
    

    	else if(play&0x02)
    	{ 
        	rep_run_the_menu();
    		#ifdef MONE_SETUP
			printf("================rep menu!\n");
			#endif
    	}
    	else if (is_menu())
   	 	{
    		//ircmd_return();
    		ircmd_root_menu();
    		#ifdef MONE_SETUP
			printf("================menu\n");
			#endif	
   		}
    	else
    	{
    	    if( (cd_type_loaded == CDDA)&&(old_play_state!=VCD_STATE_STOP) )
    	    {


    #ifdef USER_MPEG_LOGO
    if (
           (need_show_logo==1) &&
           (
               (play_state==VCD_STATE_STOP) || (play_state==VCD_STATE_OPEN) || (system_state==SYSTEM_NODISC)
           )
       )	// alan, 2003/9/8 06:02下午
    {
//    	ShowTitle();
    	need_show_logo=0;
//   	ircmd_resume();
    }
#endif//   #ifdef USER_MPEG_LOGO


    	       ShowTitle();
    	       ircmd_resume();


    	    }else if( (old_play_state==VCD_STATE_STOP)||
			 (system_state==SYSTEM_NODISC)||(system_state==SYSTEM_OPEN) )
		    {


    #ifdef USER_MPEG_LOGO
    if (
           (need_show_logo==1) &&
           (
               (play_state==VCD_STATE_STOP) || (play_state==VCD_STATE_OPEN) || (system_state==SYSTEM_NODISC)
           )
       )	// alan, 2003/9/8 06:02下午
    {
//    	ShowTitle();
    	need_show_logo=0;
   }
#endif//   #ifdef USER_MPEG_LOGO
		        ShowTitle();


		    }else
            {
                printf("================resume\n");
			    ircmd_resume();
			}
   		 }
#endif//SDRAM_16Mb_MODE
}


