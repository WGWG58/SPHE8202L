/*****************************************************\
Creater: Terry
Date   : 2001/5/11 12:49PM
Description: Setup menu using 
\*****************************************************/

#include "global.h"
#include "func.h"
#include "ircmd.h"
#include "memmap.h"
#include "dsp3_if.h"
#include "auddrv.h" //2004AUDDRV oliver 20041012 for using audio driver purpose
#include "stdlib.h"

#include "osd.h"
#include "osdsup.h"
#include "cchar.h"

#include "Sound_def.h"

#ifdef DVD_SETUP_REENG
#include "setup_VA.h"
#else
#include "setup_page.h"
#endif

#ifdef REMB_3DSOUND
#include "memmap_I2C.h"
#endif

#include "audcodec.h"
//#define MONE_sound
#ifdef OSD_BMP_SOUND
#include "osd_BmpUI.h"
#endif

#include "color_index_INDIGO_STYLE_OSDUI.h"

void SettingEqLevel(BYTE *);
void SettingEQType(BYTE type);
void EQ_init(void);
void sound_draw_title(BYTE ,BYTE , BYTE);
void sound_draw_tab(void);

void sound_func_set_EQ(BYTE EQitem);//nono 4-7-22 18:10
void sound_set_EQ_again(void);//nono 4-7-22 18:10
#ifdef OSD_BMP_SOUND
void ShowBmpSoundPage(void);
void sound_bmp_draw_tab(void);
void sound_bmp_draw_item_cursor(void);

void sound_bmp_func_right(void);
void sound_bmp_func_left(void);
void sound_bmp_func_up(void);
void sound_bmp_func_down(void);
void sound_bmp_func_select(void);

void OSD_LayoutSoundRegionA(void);
void OSD_LayoutSoundRegionB(void);
void OSD_LayoutSoundRegionD(void);
void OSD_LayoutSoundRegionE(void);
void OSD_LayoutSoundRegionF(void);
void show_bmp_band(void);
void EQ_bmp_init(void);
void sound_bmp_draw_key(UINT8 up_down, UINT8 refresh);


#ifdef OSD_SPECIAL_MENU 
extern UINT8 page_3d;
#endif

const OSD_REGIONA_LAYOUT_S g_aOsdSoundRegionA =
{
	//sound 3d osd
	OSD_BG_BMP_A,//Bg bmp,
	SOUND_LINE1_A, //Line Left,
	OSD_DOWN_BG_BMP_A, //Down Bg bmp,
	SOUND_LINE2_A, // Line Right,
	SOUND_SHADOW_A, // Shadow rect
};    

const OSD_REGIONB_LAYOUT_S g_aOsdSoundRegionB = 
{
	SOUND_RECT_BG_B,
	SOUND_BG_LINE_B,//Bg Line    
	SOUND_LINE1_B, //Line Left
	SOUND_DOWN_B, //Down bg
	OSD_CURSOR_1_BMP_B,//Curosr 1
	SOUND_SEL_STR_B, //selected string
	SOUND_UNSEL_STR_B, //unselected string
	SOUND_LINE2_B, //right line
	SOUND_SHADOW_B,//shadow
};

const OSD_REGIOND_LAYOUT_S g_aOsdSoundRegionD = 
{
	OSD_4_1_BMP_D,//Left bg
	OSD_4_2_BMP_D,//Middle bg   
	SOUND_LINE1_D, //Line left
	SOUND_DOWN_D, //Down bg rect
	OSD_CURSOR_2_BMP_D,//Curosr 2
	SOUND_LINE2_D, //right line
	SOUND_SHADOW_D,//shadow
	OSD_4_3_BMP_D,//RightBg
};

const OSD_REGIONE_LAYOUT_S g_aOsdSoundRegionE= 
{
	OSD_5_1_BMP_E,	//left bg
	SOUND_BG_RECT_E4,    //middle bg
	OSD_5_3_BMP_E,	//right bg
};

const OSD_REGIONF_LAYOUT_S g_aOsdSoundRegionF = 
{
	OSD_6_1_BMP_F,
	OSD_6_2_BMP_F,
	OSD_6_3_BMP_F,
};
#endif

#ifdef PROLOGICII_3D_MUTEX
BYTE soundGetSurroundType(void);
BYTE soundGetEQType(void);
BYTE soundGetEQType(void);
#endif//PROLOGICII_3D_MUTEX

#ifdef DYNAMIC_SPECTRUM 
void Show3dspectrum(void);  //fengjl 3-10-30 14:58
void ClearShowSpectrum(void);
extern void SetEQ(void);
#endif

#ifndef NEW_OSD_DRIVER

extern void InitSW_region(void);
extern void osd_print_eq_setting(UINT8 r,UINT8 unSele);
extern void osd_print_eq(UINT8 r, const BYTE *p);
extern void osd_DrawRegionLine(UINT32 xStart, UINT32 yStart, UINT32 xEnd, UINT32 yEnd, BYTE color, BYTE lineWidth, BYTE r);
extern void osd_draw_region_rect(UINT32 xStart, UINT32 yStart, UINT32 xLen, UINT32 yLen, BYTE bkColor, BYTE r);
extern void osd_draw_sound_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown);
    #ifndef OSD_BMP
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
    #endif
    
#endif

extern int IsOSDChinese();
extern UINT8 setup_sel[7][8];

extern void run_save_romChk_cmd(void);
extern void run_save_unChk_cmd(void);
extern void run_save_sel_cmd(BYTE, BYTE);

extern void setup_eq_display(UINT8 val);
/***********   Item description  **********************\

  BYTE	function
  0		mode(MSB 4bits)  ==>show direction picture	
		0x0:no effect
		0x1:basic select function		
		0x2:can enter number					
		0x3:need run function by osd id			
		
		  1		title 		---sw region 1
		  2~6		select item	---sw region 2
		  
\******************************************************/
enum
{
    SET_NE=0,
    SET_BS=0x1,
    SET_FUNC=0x2,
    SET_CHART=0x3,
    SET_SCALE=0x4
};

#ifdef SUPPORT_3DSOUND	

UINT8 sound_sel[SOUND_MAX_PAGE_ITEM]={2, 2, 0,6};//Item number

const UINT8 sound_item[SOUND_MAX_PAGE_ITEM][SOUND_MAX_ITEM_SEL]=
{
    {SET_BS,STR_OS_SURR,STR_OS_OFF,STR_OS_CONCERT,STR_OS_CHURCH,STR_OS_PASSIVE,STR_OS_WIDE, STR_OS_LIVE,0,0,0},		
#ifdef BBK_DVD
	{SET_FUNC,STR_OS_EQ,STR_OS_STANDARD,STR_OS_CLASSIC,STR_OS_ROCK,STR_OS_JAZZ,STR_OS_POP, STR_OS_ELECTRON,STR_OS_LIGHT_MUSIC,0,0},
#else
    {SET_FUNC,STR_OS_EQ,STR_OS_STANDARD,STR_OS_CLASSIC,STR_OS_ROCK,STR_OS_JAZZ,STR_OS_POP, STR_OS_USER,0,0,0},
#endif//end  BBK_DVD
    {SET_CHART,STR_OS_BAND,0,0,0,0,0,0,0,0,0},
#ifndef SOUND_NO_KEYPAGE     //wanghaoying 2003-9-10 10:59
    {SET_SCALE,STR_OS_KEY,0,0,0,0,0,0,0,0,0}
#endif
};


#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ
const UINT8 music_osd_set[MAX_MUSIC][MAX_BAND]=
{
    //These EQ setting is from WinAmp
    //   0 1 2 3 4 5
    {13,13,13,13,13},//standard
    {13,13,13,11,4},//classic
    {21,17,11,10,21},//rock
    {21,17,9,14,20},//jazz
    {16,12,13,17,12},//pop
#ifdef SEVEN_OPTIONS_IN_EQ
    {14,12,13,16,19},// electric //johnwu
    {16,12,13,18,19},// soft		//johnwu
#endif //SEVEN_OPTIONS_IN_EQ axel 2004/2/17 09:52AM    
};

UINT8 user_osd_set[MAX_BAND]={13,13,13,13,13};
#else//#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ
const UINT8 music_osd_set[MAX_MUSIC][MAX_BAND]=
{
    //These EQ setting is from WinAmp
    //   0 1 2 3 4 5 6 7
    {13,13,13,13,13,13,13},//standard
    //{23,18,7,5,7,18,23},//classic
    {13,13,13,13,13,10,3},//classic
    //{23,18,7,2,7,18,23},//rock
    //{21,21,15,13,11,13,23},//rock //WinAmp
    {21,21,15,11,7,11,23},//rock
    //{3,7,18,23,18,7,3},//jazz
    //{21,19,16,13,18,13,23},//jazz //WinAmp
    {21,19,16,9,18,9,23},//jazz
    //{18,23,18,16,7,15,18},//pop
    //{15,19,11,13,19,15,13},//pop //WinAmp
    {15,21,7,13,21,15,11},//pop
#ifdef SEVEN_OPTIONS_IN_EQ
    {14,13,12,13,15,17,19},// electric //johnwu
    {17,14,10,13,17,19,19},// soft		//johnwu
#endif //SEVEN_OPTIONS_IN_EQ axel 2004/2/17 09:52AM    
};

UINT8 user_osd_set[MAX_BAND]={13,13,13,13,13,13,13};
#endif//#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ

UINT8 id,sel;
BYTE page=0,sound_level=1;	// 0:tab       1:item selection        2:EQ adjustment

#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI) 
UINT8 draw_sound_flag ;
UINT8 draw_sound_key_flag;  
UINT8 draw_key_updown; 
UINT8 draw_key_refresh;
#endif


#ifdef REMB_3DSOUND       //define it to remember 3D Sound yanlb 2004/07/06
void run_sound_save(BYTE *p)
{
    #ifdef MONE_sound 
    UINT8 i;
    for (i=0;i<SAVE_NUM;i++)
       printf("run_sound_save:sound_save:%2d,,,,,,,,,,,\n",*(p+i));
    #endif
 
    
	//save surround&eq page,but not user setup
    //WriteToI2c(0xa0,Addr_REMB_3D,  p, SAVE_NUM);		//linrc do it 2006-2-14 10:51
	WriteToI2c(0xa0,Addr_REMB_3D,  p, Addr_REMB_3D_SIZE);
	
    #ifdef GBM_DVD
    if(1)  //modified by wangwei,2004-9-17 16:04(save 3Dsound EQ user setting whenever)
    #else
    if(p[1]==MAX_MUSIC+2)  //save user set  
    #endif
    {
		p=(UINT8 *)user_osd_set;
		//WriteToI2c(0xa0,Addr_REMB_3D+SAVE_NUM,  p, MAX_BAND);		linrc do it 2006-2-14 10:53
		WriteToI2c(0xa0,Addr_REMB_3D_BAND,  p, Addr_REMB_3D_BAND_SIZE);

		#ifdef MONE_sound
		//ReadFromI2c(0xa0,Addr_REMB_3D+SAVE_NUM, p, MAX_BAND);		linrc do it 2006-2-14 10:53
		ReadFromI2c(0xa0,Addr_REMB_3D_BAND, p, Addr_REMB_3D_BAND_SIZE);
   		for (i=0;i<MAX_MUSIC;i++)
           	printf("run_sound_save-user_osd_set:%2d,,,,,,,,,,,\n",(p+i));
        #endif
	}
}

//parameter: save_3d--user set sound;band_set--user_osd_set
//return 
int load_3Dsound(UINT8 *save_3d,UINT8 *band_set)
{
    #ifdef MONE_sound
        printf("load 3Dsound,in\n");
    #endif
    int iResult=-1;
    UINT8 *p;
    p=(BYTE *)save_3d;
	
    //load surround&eq page,but not user setup
    //iResult=ReadFromI2c(0xa0,Addr_REMB_3D, p, SAVE_NUM);	linrc do it 2006-2-14 10:58
    iResult=ReadFromI2c(0xa0,Addr_REMB_3D, p, Addr_REMB_3D_SIZE);
	#ifdef MONE_sound 
	UINT8 i;
	for (i=0;i<SAVE_NUM;i++)
           printf("load_3Dsound-sound_saved:%2d\n",save_3d[i]);
    #endif
    if (iResult==-1)
    {
    	#ifdef MONE_sound
    	    printf("load_3Dsound-ReadFromI2c fail!!\n");
    	#endif
	    return iResult;
    }
    
    #ifdef GBM_DVD
    if(1)  //modified by wangwei,2004-9-17 16:04(load 3Dsound EQ user setting whenever)
    #else
    if(save_3d[1]==MAX_MUSIC+2)  //load user setup
    #endif
    {
    	p=(UINT8 *)band_set;
    	//iResult=ReadFromI2c(0xa0,Addr_REMB_3D+SAVE_NUM, p, MAX_BAND);		linrc do it 2006-2-14 10:58
    	iResult=ReadFromI2c(0xa0,Addr_REMB_3D_BAND, p, Addr_REMB_3D_BAND_SIZE);
    }
    #ifdef MONE_sound 
	for (i=0;i<MAX_BAND;i++)
           printf("load_3Dsound-sound_saved:%2d\n",band_set[i]);
    #endif
    if (iResult==-1)
    {
    	#ifdef MONE_sound
    	    printf("load_user set-ReadFromI2c fail!!\n");
    	#endif
	    return iResult;
    }
    	return iResult=1;
}

void exe_3Dsound(UINT8 *sound_save,UINT8 *user_osd_set)
{
	    if (sound_save[0]>2){
		    AUDIF_Set_Surround(sound_save[0]-2);//2004AUDDRV AudioSetSurround(sound_save[0]-2);
		    AUDIF_Set_EQType(0);//2004AUDDRV AudioSetEQType(0);
		#ifdef MONE_sound
    	    printf("  1===============Load 3Dsound Surround!===============\n");
    	#endif 
        }
    	else if((sound_save[1]>2)&&(sound_save[1]<MAX_MUSIC+2)){
		    AUDIF_Set_EQType(sound_save[1]-2);//AudioSetEQType(sound_save[1]-2);
			AUDIF_Set_Surround(0);//2004AUDDRV AudioSetSurround(0);
		    #ifdef MONE_sound
    			printf("  2==============Load 3Dsound EQ!===============\n");
    		#endif 
	    }
    	else {
    		SettingEqLevel(user_osd_set);
    		SettingEqLevel(user_osd_set); //for cover err
    		AUDIF_Set_Surround(0);//2004AUDDRV AudioSetSurround(0);
		    #ifdef MONE_sound
    			printf("  3==============Load 3Dsound BAND!===============\n");
    		#endif 
    	}
}
#endif    //#ifdef  REMB_3DSOUND  yanlb 2004/07/07

void sound_init(void)
{
	// initialize page and sound_level, in order to dsiplay correctly next time ShowSoundPage
    page=0;	
    sound_level=0;	
    sound_sel[3]=(UINT8)(6-audio_key);

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

#ifdef INDIGO_STYLE_OSDUI
	//show non-change background
	// draw light blue
	osd_draw_region_rect(           0, ICON_BG_HEI,         4, SOUND_HEI-ICON_BG_HEI, PAGE_BG, 2);
	osd_draw_region_rect( SOUND_WID-4, ICON_BG_HEI,         4, SOUND_HEI-ICON_BG_HEI, PAGE_BG, 2);
	osd_draw_region_rect(           0, SOUND_HEI-4, SOUND_WID,                     4, PAGE_BG, 2);

 	//draw dark blue rect
	osd_draw_region_rect(             4,    ICON_BG_HEI,            9, SOUND_HEI-ICON_BG_HEI-4, SELECT_PAGE_FONT_COLOR, 2);
	osd_draw_region_rect( SOUND_WID-4-9,   ICON_BG_HEI,             9, SOUND_HEI-ICON_BG_HEI-4, SELECT_PAGE_FONT_COLOR, 2);
	osd_draw_region_rect(             4, SOUND_HEI-4-9, SOUND_WID-4*2,                       9, SELECT_PAGE_FONT_COLOR, 2);

	// white four lines
	osd_DrawRegionLine(          4+9    , SOUND_HEI-4-9-LINE_WID,     CONTENT_BG_WID-6, SOUND_HEI-4-9-LINE_WID, 5, LINE_WID, 2); // line botton
	osd_DrawRegionLine(          4+9    ,          ICON_BG_HEI+9,                  4+9, SOUND_HEI-4-9-LINE_WID, 5, LINE_WID, 2); // line left
	osd_DrawRegionLine( CONTENT_BG_WID-6,          ICON_BG_HEI+9, CONTENT_BG_WID-(4+9), SOUND_HEI-4-9-LINE_WID, 5, LINE_WID, 2); // line right
#ifdef SUPPORT_SW_OSD_SCALING
	draw_sound_flag = 1;
#endif
#endif
}

#ifdef SOUND_NO_KEYPAGE     //wanghaoying 2003-9-10 11:00
void sound_init_2(void)
{
	// initialize page and sound_level, in order to dsiplay correctly next time ShowSoundPage
    page=1;	
    sound_level=0;	
    sound_sel[3]=(UINT8)(6-audio_key);
    
}
#endif

void show_band(void)
{
    char str[6];
    memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND);
    osd_print_eq_setting(BAND_R, index_x*2);
	
    if ((index_y-13)<-9)
        psprintf(str,"%d DB", (index_y-13));
    else if ((index_y-13)<0)
        psprintf(str,"%d DB ", (index_y-13));		
    else if ((index_y-13)>9)
        psprintf(str," %d DB", (index_y-13));
    else
        psprintf(str," %d DB ", (index_y-13));
	//osd_DrawRegionString(80,6,str,7,11,3);	

// show user keyin band value
 #ifdef INDIGO_STYLE_OSDUI
	osd_DrawRegionString(20,55,str,11,1,2); 
#else
   osd_DrawRegionString(22,6,str,7,11,3);//20050204 joshua 80->22
#endif
}

/***************************************************************************
* Function: ShowSoundPage()   
* Purposes: Show key page of 3d-sound OSD 
* Description:                    
* Arguments: None
* Return: N/A
* Create: 
* Modify: robert.chang, 2006/09/18 
* Modify Purposes: This modify only for 8202L IC.
*                           When 3d-sound OSD is turned on or 3d-sound page switching, 
*                           it maybe cause the audio interrupted.To avoid the status,
*                           the function sound_draw_key() is partitioned into several parts.
*                           Then polling_sound() will call sound_draw_key() and execute the 
*                           parts of it individually.
***************************************************************************/
#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)  
void sound_draw_key(UINT8 up_down, UINT8 refresh)
{
                        BYTE buf[15];
                        BYTE fnColor, bgColor;
                        UINT32 y;


    // trick for partitioning sound_draw_key().
    if(draw_sound_key_flag == 1) {
        draw_key_updown = up_down;
        draw_key_refresh = refresh;
    }
    else if(draw_sound_key_flag>1) {
        up_down = draw_key_updown;
        refresh = draw_key_refresh;
    }else
    {
        draw_key_updown = 0;
        draw_key_refresh = 0;
    }

                       
                        if (up_down)
                        {
                    	  #ifdef INDIGO_STYLE_OSDUI
                            fnColor=SBLACKCOLOR;
                            bgColor=SBGCOLOR;	        
                    	  #else
                            fnColor=SWHITECOLOR;
                            bgColor=SANTIBGCOLOR;		
                    	  #endif
                        }
                        else
                        {
                            fnColor=SBLACKCOLOR;
                            bgColor=SBGCOLOR;		
                        }
                        
                        if (refresh)
                        {
                    	#ifdef INDIGO_STYLE_OSDUI
                        
    if(draw_sound_key_flag == 1)      // step 1 of key page of 3d-sound OSD
    {           
    
                            psprintf(buf, "- +6");
                            osd_DrawRegionString(15, 6+12, buf, fnColor, bgColor, EQ_R);	
                            psprintf(buf, "- +4");
                            osd_DrawRegionString(15, 12+12, buf, fnColor, bgColor, EQ_R);	
                            buf[3]='2';//psprintf(buf, " -    - +2");
                            osd_DrawRegionString(15, 18+12, buf, fnColor, bgColor, EQ_R);	


        draw_sound_key_flag = 2;
        return;
    }        
    else if(draw_sound_key_flag == 2)  // step 2 of key page of 3d-sound OSD
    {
                            
                            psprintf(buf, "-  0");
                            osd_DrawRegionString(15, 24+12, buf, fnColor, bgColor, EQ_R);	
                            psprintf(buf, "- -2");
                            osd_DrawRegionString(15, 30+12, buf, fnColor, bgColor, EQ_R);	
                            buf[3]='4';//psprintf(buf, " -    - -4");
                            osd_DrawRegionString(15, 36+12, buf, fnColor, bgColor, EQ_R);


        draw_sound_key_flag = 3;
        return;
    }
    else if(draw_sound_key_flag == 3)  // step 3 of key page of 3d-sound OSD
    {
                           
                            psprintf(buf, "- -6");   // lxg 2006-6-19 11:26
                            osd_DrawRegionString(15, 42+12, buf, fnColor, bgColor, EQ_R);
                            psprintf(buf, "%s", Ch_ukey);
                            osd_DrawRegionString(15, 0+12+2, buf, fnColor, bgColor, EQ_R);	
                            psprintf(buf, "%s", Ch_dkey);
                            osd_DrawRegionString(15, 48+10, buf, fnColor, bgColor, EQ_R);


        draw_sound_key_flag = 4;
        return;        
    }        
                            
                    	#else

    if(draw_sound_key_flag == 1)   // step 1 of key page of 3d-sound OSD
    {   
    
                            osd_draw_region_rect(140, 14, 180, 194, bgColor,EQ_R);
                            osd_draw_button_outline(140,14,320,208,up_down,0x0f,EQ_R);
                            psprintf(buf, " -    %s", Ch_ukey);
                            osd_DrawRegionString(9, 6, buf, fnColor, bgColor, EQ_R);	


        draw_sound_key_flag = 2;
        return;
    }        
    else if(draw_sound_key_flag == 2)  // step 2 of key page of 3d-sound OSD
    {                            
                            psprintf(buf, " -    - +4");
                            osd_DrawRegionString(9, 12, buf, fnColor, bgColor, EQ_R);	
                            buf[9]='2';//psprintf(buf, " -    - +2");
                            osd_DrawRegionString(9, 18, buf, fnColor, bgColor, EQ_R);	
                            psprintf(buf, " -    -  0");
                            osd_DrawRegionString(9, 24, buf, fnColor, bgColor, EQ_R);	


        draw_sound_key_flag = 3;
        return;
    }
    else if(draw_sound_key_flag == 3)  // step 3 of key page of 3d-sound OSD
    {
                            
                            psprintf(buf, " -    - -2");
                            osd_DrawRegionString(9, 30, buf, fnColor, bgColor, EQ_R);	
                            buf[9]='4';//psprintf(buf, " -    - -4");
                            osd_DrawRegionString(9, 36, buf, fnColor, bgColor, EQ_R);	
                            psprintf(buf, " -    %s", Ch_dkey);
                            osd_DrawRegionString(9, 42, buf, fnColor, bgColor, EQ_R);


        draw_sound_key_flag = 4;
        return;        
    }                                    
                    	#endif
                        }
                        else
                        {

    if(draw_sound_key_flag == 1)  // trick for partitioning sound_draw_key().
    {    
                        
                            UINT32 y=35+sound_sel[page]*12;
                            // clear cursor bar
                            #ifdef INDIGO_STYLE_OSDUI
                            osd_draw_region_rect(180-8, y-14+46, 44, 40, bgColor,EQ_R);
                            #else
                            osd_draw_region_rect(188, y-14, 40, 40, bgColor,EQ_R);
                            #endif


        draw_sound_key_flag = 4;
        return;        
    }                                
                        }

    if(draw_sound_key_flag == 4) {     // step 4 of key page of 3d-sound OSD


                        #ifdef INDIGO_STYLE_OSDUI
                    	// draw central vertical bar	
                        osd_DrawRegionLine(	225,  72+13,    225,	250-20,	SBLACKCOLOR,	3,	EQ_R);	
                        osd_DrawRegionLine(	225,  72+13,	225+30,	 72+13,	SBLACKCOLOR,	3,	EQ_R);
                        osd_DrawRegionLine(	225, 250-20,	225+30,	250-20,	SBLACKCOLOR,	3,	EQ_R);
                        #else
                        osd_DrawRegionLine(202,22,202,200,SBLACKCOLOR,4,EQ_R);	// draw central vertical bar
                        #endif

                        #ifdef INDIGO_STYLE_OSDUI	
                        BYTE hLOrSelColor;
                        if (up_down)
                            hLOrSelColor = setupBGcolorSM;
                        else
                            hLOrSelColor = setupBGcolorIS;
                    		
                        y=35+sound_sel[page]*12;	
                    	  	// draw arror with multi-rect (avoid font with frame prob.)
						osd_draw_region_rect(  210-8, y+46  , 2, 15, hLOrSelColor,EQ_R);
						osd_draw_region_rect(  212-8, y+46+1, 2, 13, hLOrSelColor,EQ_R);
						osd_draw_region_rect(  214-8, y+46+2, 2, 11, hLOrSelColor,EQ_R);
						osd_draw_region_rect(  216-8, y+46+3, 2,  9, hLOrSelColor,EQ_R);
						osd_draw_region_rect(  218-8, y+46+4, 1,  7, hLOrSelColor,EQ_R);
						osd_draw_region_rect(  219-8, y+46+5, 1,  5, hLOrSelColor,EQ_R);
						osd_draw_region_rect(  220-8, y+46+6, 1,  3, hLOrSelColor,EQ_R);
						osd_draw_region_rect(  221-8, y+46+7, 1,  1, hLOrSelColor,EQ_R);
                        #endif

                        // draw horizontal selection short bar
                        y=35+sound_sel[page]*12;
                        #ifdef INDIGO_STYLE_OSDUI
                        osd_draw_region_rect(  190-8, y+46, 20, 15, hLOrSelColor,EQ_R); // show bar is HL color(#7,yellow)		
                        osd_draw_region_rect(190-8-8, y+46,  5, 15, hLOrSelColor,EQ_R); // show bar is HL color(#7,yellow)
                        #else
                        osd_draw_region_rect(188, y, 36, 8, bgColor,EQ_R);
                        osd_draw_button_outline(188,y,224,y+8,up_down,0x0f,EQ_R);
                        #endif


        draw_sound_key_flag = 0;                        
    }                        
}

#else

void sound_draw_key(UINT8 up_down, UINT8 refresh)
{
    BYTE buf[15];
    BYTE fnColor, bgColor;
	
    if (up_down)
	{
	  #ifdef INDIGO_STYLE_OSDUI
        fnColor=SBLACKCOLOR;
        bgColor=SBGCOLOR;	        
	  #else
        fnColor=SWHITECOLOR;
        bgColor=SANTIBGCOLOR;		
	  #endif
    }
	else
	{
        fnColor=SBLACKCOLOR;
        bgColor=SBGCOLOR;		
    }
	
    if (refresh)
	{
	#ifdef INDIGO_STYLE_OSDUI	
		psprintf(buf, "- +6");
		osd_DrawRegionString(15, 6+12, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, "- +4");
		osd_DrawRegionString(15, 12+12, buf, fnColor, bgColor, EQ_R);	
		buf[3]='2';//psprintf(buf, " -    - +2");
		osd_DrawRegionString(15, 18+12, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, "-  0");
		osd_DrawRegionString(15, 24+12, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, "- -2");
		osd_DrawRegionString(15, 30+12, buf, fnColor, bgColor, EQ_R);	
		buf[3]='4';//psprintf(buf, " -    - -4");
		osd_DrawRegionString(15, 36+12, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, "- -6");   // lxg 2006-6-19 11:26
		osd_DrawRegionString(15, 42+12, buf, fnColor, bgColor, EQ_R);
		psprintf(buf, "%s", Ch_ukey);
		osd_DrawRegionString(15, 0+12+2, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, "%s", Ch_dkey);
		osd_DrawRegionString(15, 48+10, buf, fnColor, bgColor, EQ_R);
	#else
		osd_draw_region_rect(140, 14, 180, 194, bgColor,EQ_R);
		osd_draw_button_outline(140,14,320,208,up_down,0x0f,EQ_R);
		psprintf(buf, " -    %s", Ch_ukey);
		osd_DrawRegionString(9, 6, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, " -    - +4");
		osd_DrawRegionString(9, 12, buf, fnColor, bgColor, EQ_R);	
		buf[9]='2';//psprintf(buf, " -    - +2");
		osd_DrawRegionString(9, 18, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, " -    -  0");
		osd_DrawRegionString(9, 24, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, " -    - -2");
		osd_DrawRegionString(9, 30, buf, fnColor, bgColor, EQ_R);	
		buf[9]='4';//psprintf(buf, " -    - -4");
		osd_DrawRegionString(9, 36, buf, fnColor, bgColor, EQ_R);	
		psprintf(buf, " -    %s", Ch_dkey);
		osd_DrawRegionString(9, 42, buf, fnColor, bgColor, EQ_R);
	#endif
    }
	else
	{
		UINT32 y=35+sound_sel[page]*12;
        // clear cursor bar
	#ifdef INDIGO_STYLE_OSDUI
		osd_draw_region_rect(180-8, y-14+46, 44, 40, bgColor,EQ_R);
	#else
		osd_draw_region_rect(188, y-14, 40, 40, bgColor,EQ_R);
	#endif
    }
	
	#ifdef INDIGO_STYLE_OSDUI
	// draw central vertical bar	
	osd_DrawRegionLine(	225,  72+13,    225,	250-20,	SBLACKCOLOR,	3,	EQ_R);	
	osd_DrawRegionLine(	225,  72+13,	225+30,	 72+13,	SBLACKCOLOR,	3,	EQ_R);
	osd_DrawRegionLine(	225, 250-20,	225+30,	250-20,	SBLACKCOLOR,	3,	EQ_R);
	#else
    osd_DrawRegionLine(202,22,202,200,SBLACKCOLOR,4,EQ_R);	// draw central vertical bar
	#endif

	#ifdef INDIGO_STYLE_OSDUI	
    BYTE hLOrSelColor;
	if (up_down)
		hLOrSelColor = setupBGcolorSM;
	else
		hLOrSelColor = setupBGcolorIS;
		
	//2006.01.20 mimitsai add for drawing arrow
    //coordinate start;
    //start.x = 207;
	//start.y = (35-4+sound_sel[page]*12)+46;
    UINT32 y=35+sound_sel[page]*12;	
//	  #ifdef SUPPORT_FONT_OUTLINE
	  	// draw arror with multi-rect (avoid font with frame prob.)
		osd_draw_region_rect(  210-8, y+46  , 2, 15, hLOrSelColor,EQ_R);
		osd_draw_region_rect(  212-8, y+46+1, 2, 13, hLOrSelColor,EQ_R);
		osd_draw_region_rect(  214-8, y+46+2, 2, 11, hLOrSelColor,EQ_R);
		osd_draw_region_rect(  216-8, y+46+3, 2,  9, hLOrSelColor,EQ_R);
		osd_draw_region_rect(  218-8, y+46+4, 1,  7, hLOrSelColor,EQ_R);
		osd_draw_region_rect(  219-8, y+46+5, 1,  5, hLOrSelColor,EQ_R);
		osd_draw_region_rect(  220-8, y+46+6, 1,  3, hLOrSelColor,EQ_R);
		osd_draw_region_rect(  221-8, y+46+7, 1,  1, hLOrSelColor,EQ_R);
//	  #else
//    	osd_draw_string(&start, Ch_arrorR, hLOrSelColor, setupBGcolorSPU, EQ_R, 0);
//	  #endif
	#endif

    // draw horizontal selection short bar
    {
        UINT32 y=35+sound_sel[page]*12;
	#ifdef INDIGO_STYLE_OSDUI
		osd_draw_region_rect(  190-8, y+46, 20, 15, hLOrSelColor,EQ_R); // show bar is HL color(#7,yellow)		
		osd_draw_region_rect(190-8-8, y+46,  5, 15, hLOrSelColor,EQ_R); // show bar is HL color(#7,yellow)
	#else
        osd_draw_region_rect(188, y, 36, 8, bgColor,EQ_R);
        osd_draw_button_outline(188,y,224,y+8,up_down,0x0f,EQ_R);
	#endif
    }
}

#endif

/***************************************************************************
* Function: ShowSoundPage()   
* Purposes: Show 3d-sound OSD page when users press 3d-sound button
* Description:                    
* Arguments: None
* Return: N/A
* Create: 
* Modify: robert.chang, 2006/09/18 
* Modify Purposes: This modify only for 8202L IC.
*                           When 3d-sound OSD is turned on or 3d-sound page switching, 
*                           it maybe cause the audio interrupted.To avoid the status,
*                           the function ShowSoundPage() is partitioned into several parts.
*                           Then polling_sound() will call ShowSoundPage() and execute the 
*                           parts of it individually.
***************************************************************************/
#include "osd_palette.h"
#ifdef INDIGO_STYLE_OSDUI 

#ifdef SUPPORT_SW_OSD_SCALING
void 
ShowSoundPage(void) 
{
                            extern UINT8 page_3d __attribute__((unused));
                            const char  *str;	

    if(draw_sound_flag == 1)  // step 1 of  3d-sound OSD page showing
    {
                        	// draw background
                            osd_draw_region_rect(           0,           0, SOUND_WID,   ICON_BG_HEI, PAGE_BG, 2);
                            osd_draw_region_rect(             4,   ICON_BG_HEI, SOUND_WID-4*2,                       9, SELECT_PAGE_FONT_COLOR, 2);
                            osd_DrawRegionLine(          4+9    ,          ICON_BG_HEI+9,     CONTENT_BG_WID-6,          ICON_BG_HEI+9, 5, LINE_WID, 2); // line top

                            osd_draw_region_rect( 4+9+2, ICON_BG_HEI+10, SOUND_WID-(4+9)*2-2, SOUND_HEI-ICON_BG_HEI-4-9*2-2, 6, 2);


	draw_sound_flag = 2;
	return;
    }
    else if(draw_sound_flag == 2)  // step 2 of  3d-sound OSD page showing
    {

                            if (page==3) {
                                if(draw_sound_key_flag ==0 )
                                    draw_sound_key_flag = 1;                        
                                sound_draw_key(BUTTON_UP,1);	
                            }    
                            else if (page==2)
                                osd_draw_region_rect(BAND_XSTART_PIXEL+8, BAND_YSTART-5,MAX_BAND*32-4,108,BAND_BG_COLOR,EQ_R);
                            else
                                osd_draw_region_rect(EQ_XSTART_PIXEL+8 ,EQ_YSTART-5,MAX_BAND*32-4,108,BAND_BG_COLOR,EQ_R);


        if(draw_sound_key_flag == 0) 
            draw_sound_flag = 3;
        return;
    }	
    else if(draw_sound_flag == 3)   // step 3 of  3d-sound OSD page showing
    {	
                	
                            sound_draw_tab();


        draw_sound_flag = 4;
        return;
    }
    else // step4~step7 of 3d-sound OSD page showing, trick for partitioning ShowSoundPage().
    {


                            if (page<2)
                            {
                                int item;

    if(draw_sound_flag == 4)    // step 4 of  3d-sound OSD page showing  
    {
                        
                                for (item=0;item<3;item++) // draw all button and string on it
                                {
                                    //osd_draw_sound_button(2,item,12,SBGCOLOR,BUTTON_UP);
                                    //osd_draw_region_rect(2*16, item*SETUP_BTN_HEIGHT+12, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), SBGCOLOR,2);    
                        			
                                    id=sound_item[page][2+item];
                                    str=_OsdMessegeFont1[osd_font_mode][id];	
                        		#ifdef INDIGO_STYLE_OSDUI
                                    osd_DrawRegionString(3,item*8+16,(BYTE *)str,SANTIBGCOLOR,SBGCOLOR,EQ_R);		
                        		#else
                                    osd_DrawRegionString(3,item*8+3,(BYTE *)str,SBLACKCOLOR,SBGCOLOR,EQ_R);		
                        		#endif
                                }


        draw_sound_flag = 5;
        return;
    }  
    else if(draw_sound_flag == 5)    // step 5 of  3d-sound OSD page showing
    {


                                for (item=3;item<6;item++) // draw all button and string on it
                                {                			
                                    id=sound_item[page][2+item];
                                    str=_OsdMessegeFont1[osd_font_mode][id];	
                        		#ifdef INDIGO_STYLE_OSDUI
                                    osd_DrawRegionString(3,item*8+16,(BYTE *)str,SANTIBGCOLOR,SBGCOLOR,EQ_R);		
                        		#else
                                    osd_DrawRegionString(3,item*8+3,(BYTE *)str,SBLACKCOLOR,SBGCOLOR,EQ_R);		
                        		#endif
                                }


        draw_sound_flag = 6;
        return;
    }        
    else if(draw_sound_flag == 6)   // step 6 of  3d-sound OSD page showing
    {
        
                                index_y=sound_sel[page]-2;
                        	
                                sel=sound_sel[1];
                                if(sel==MAX_MUSIC+2)  //user set
                                    memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND);
                                else
                                    memcpyS(&RegionValStr[BAND_R], &music_osd_set[sel-2], MAX_BAND);
                        		
                                osd_print_eq_setting(BAND_R, 0xff);
                        		
                                //select
                                sel=sound_sel[page];		
                                if (sel<2)
                                    sel=sound_sel[page]=2;	
                                id=sound_item[page][sel];

                                if(id)	// show highlight and hollow button
                                {
                                    str=_OsdMessegeFont1[osd_font_mode][id];
                                    if (sound_level==0)
                                    {
                                        // when sound_level=0, item region only show which one is pressed, don't need highlight
                                    #ifdef INDIGO_STYLE_OSDUI	
                                        osd_draw_region_rect(2*16, ((sel-2)*8+16)*4+4, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), SELECT_BTN_COLOR,2);    
                                        osd_DrawRegionString(3,(sel-2)*8+16,(BYTE *)str,SELECT_PAGE_FONT_COLOR,SELECT_BTN_COLOR,2);
                                    #else	
                                        osd_draw_sound_button(2,sel-2,12,SBGCOLOR,BUTTON_DOWN);
                                        osd_DrawRegionString(3,(sel-2)*8+3,(BYTE *)str,4,SBGCOLOR,3);
                                    #endif			
                                    }
                                    else
                                    {
                                    #ifdef INDIGO_STYLE_OSDUI
                                        osd_draw_region_rect(2*16, ((sel-2)*8+16)*4+4, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), HIGHLIGHT_COLOR,2);    
                                        osd_DrawRegionString(3,(sel-2)*8+16,(BYTE *)str,SELECT_PAGE_FONT_COLOR,HIGHLIGHT_COLOR,2);
                                    #else	
                                        osd_draw_sound_button(2,sel-2,12,SANTIBGCOLOR,BUTTON_DOWN);
                                        osd_DrawRegionString(3,(sel-2)*8+3,(BYTE *)str,SWHITECOLOR,SANTIBGCOLOR,3);
                                    #endif	
                                    }
                                }


        draw_sound_flag = 7;
        return;
    }

                        
                            }
                            else {   // trick for partitioning ShowSoundPage().

                        
    if(draw_sound_flag == 4)  // trick for partitioning ShowSoundPage().
    {
        draw_sound_flag = 7;
        return;
    }
    
                            }



    if(draw_sound_flag == 7) {     // step 7 of  3d-sound OSD page showing

        
                            #ifdef INDIGO_STYLE_OSDUI
                        	// 2006-03-06, mimitsai add for add cursor highlight
                            if(sound_level==0)
                                osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  7,SURROUND_R);//draw page highlight
                            else
                                osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  setupBGcolorBTB,SURROUND_R);//clear page highlight

                            #endif

        draw_sound_flag = 0;
    }

    }                    
}

#else

void
ShowSoundPage(void)
{
	extern UINT8 page_3d __attribute__((unused));
    const char  *str;	

	// draw background
	osd_draw_region_rect(           0,           0, SOUND_WID,   ICON_BG_HEI, PAGE_BG, 2);
	osd_draw_region_rect(             4,   ICON_BG_HEI, SOUND_WID-4*2,                       9, SELECT_PAGE_FONT_COLOR, 2);
	osd_DrawRegionLine(          4+9    ,          ICON_BG_HEI+9,     CONTENT_BG_WID-6,          ICON_BG_HEI+9, 5, LINE_WID, 2); // line top

	osd_draw_region_rect( 4+9+2, ICON_BG_HEI+10, SOUND_WID-(4+9)*2-2, SOUND_HEI-ICON_BG_HEI-4-9*2-2, 6, 2);

    if (page==3) 
        sound_draw_key(BUTTON_UP,1);		
	else if (page==2)
        osd_draw_region_rect(BAND_XSTART_PIXEL+8, BAND_YSTART-5,MAX_BAND*32-4,108,BAND_BG_COLOR,EQ_R);
	else
        osd_draw_region_rect(EQ_XSTART_PIXEL+8 ,EQ_YSTART-5,MAX_BAND*32-4,108,BAND_BG_COLOR,EQ_R);
	
    sound_draw_tab();


    if (page<2)
    {
        int item;
        for (item=0;item<6;item++) // draw all button and string on it
        {
            //osd_draw_sound_button(2,item,12,SBGCOLOR,BUTTON_UP);
            //osd_draw_region_rect(2*16, item*SETUP_BTN_HEIGHT+12, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), SBGCOLOR,2);    
			
            id=sound_item[page][2+item];
            str=_OsdMessegeFont1[osd_font_mode][id];	
		#ifdef INDIGO_STYLE_OSDUI
            osd_DrawRegionString(3,item*8+16,(BYTE *)str,SANTIBGCOLOR,SBGCOLOR,EQ_R);		
		#else
            osd_DrawRegionString(3,item*8+3,(BYTE *)str,SBLACKCOLOR,SBGCOLOR,EQ_R);		
		#endif
        }

        index_y=sound_sel[page]-2;
	
        sel=sound_sel[1];
        if(sel==MAX_MUSIC+2)  //user set
            memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND);
		else
            memcpyS(&RegionValStr[BAND_R], &music_osd_set[sel-2], MAX_BAND);
		
        osd_print_eq_setting(BAND_R, 0xff);
		
        //select
        sel=sound_sel[page];		
        if (sel<2)
			sel=sound_sel[page]=2;	
        id=sound_item[page][sel];

		if(id)	// show highlight and hollow button
        {
            str=_OsdMessegeFont1[osd_font_mode][id];
	    	if (sound_level==0)
			{
                // when sound_level=0, item region only show which one is pressed, don't need highlight
            #ifdef INDIGO_STYLE_OSDUI	
    			osd_draw_region_rect(2*16, ((sel-2)*8+16)*4+4, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), SELECT_BTN_COLOR,2);    
				osd_DrawRegionString(3,(sel-2)*8+16,(BYTE *)str,SELECT_PAGE_FONT_COLOR,SELECT_BTN_COLOR,2);
			#else	
				osd_draw_sound_button(2,sel-2,12,SBGCOLOR,BUTTON_DOWN);
				osd_DrawRegionString(3,(sel-2)*8+3,(BYTE *)str,4,SBGCOLOR,3);
			#endif			
			
	    	}
			else
			{
            #ifdef INDIGO_STYLE_OSDUI
    			osd_draw_region_rect(2*16, ((sel-2)*8+16)*4+4, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), HIGHLIGHT_COLOR,2);    
				osd_DrawRegionString(3,(sel-2)*8+16,(BYTE *)str,SELECT_PAGE_FONT_COLOR,HIGHLIGHT_COLOR,2);
			#else	
                osd_draw_sound_button(2,sel-2,12,SANTIBGCOLOR,BUTTON_DOWN);
                osd_DrawRegionString(3,(sel-2)*8+3,(BYTE *)str,SWHITECOLOR,SANTIBGCOLOR,3);
			#endif	
         	}
        }
    }

	#ifdef INDIGO_STYLE_OSDUI
	// 2006-03-06, mimitsai add for add cursor highlight
	if(sound_level==0)
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  7,SURROUND_R);//draw page highlight
	else
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  setupBGcolorBTB,SURROUND_R);//clear page highlight
	#endif
}

#endif

#else

void
ShowSoundPage(void)
{	
extern UINT8 page_3d __attribute__((unused));
#ifdef OSD_SPECIAL_MENU
      page_3d=page;
#endif	

#ifdef OSD_BMP_SOUND
	ShowBmpSoundPage();
#else
    const char  *str;	
	
    // draw background
#ifdef  ONLY_SHOW_3D_SPECTRUM   //only show 3d spectrum page by wangfeng,2003-10-22 09:20
	SetOsdCol(3,3,SBGCOLOR,0x78501e00);
    osd_draw_region_rect(0, 0, PAGE_WIDTH,    224, SBGCOLOR,      EQ_R);
#else
	#ifdef SETUP_COLOR_TYPE1
	SetOsdCol(3,3,SBGCOLOR,0x78501ebf);//wangfeng,2003-10-22 11:06
	#endif
    osd_draw_region_rect(0, 0, PAGE_WIDTH,    36,  SBGCOLOR,      SURROUND_R);	
    osd_draw_region_rect(6, 4, PAGE_WIDTH-12, 32,  SDISABLECOLOR, SURROUND_R);    // make whole tab region disable	
    osd_draw_region_rect(0, 0, PAGE_WIDTH,    224, SBGCOLOR,      EQ_R);
    osd_draw_region_rect(6, 0, PAGE_WIDTH-12, 4,   SDISABLECOLOR, EQ_R);          // make whole tab region disable
	
    // draw top horizontal line
    osd_draw_hline_region(6, PAGE_WIDTH-6, 5, SWHITECOLOR, 2, SURROUND_R);
    osd_draw_hline_region(6, PAGE_WIDTH-6, 4, SWHITECOLOR, 2, EQ_R);

    // draw left vertical line
    osd_draw_vline_region(6, 5, 36,  SWHITECOLOR, 2, SURROUND_R);
    osd_draw_vline_region(6, 0, 218, SWHITECOLOR, 2, EQ_R);

    // draw right vertical line
    osd_draw_vline_region(PAGE_WIDTH-6, 5, 36,  SBLACKCOLOR, 2, SURROUND_R);
    osd_draw_vline_region(PAGE_WIDTH-6, 0, 218, SBLACKCOLOR, 2, EQ_R);

    // draw bottom horizontal line
    osd_draw_hline_region(6, PAGE_WIDTH-6, 216, SBLACKCOLOR, 2, EQ_R);

    if (page==3) 
    {
        sound_draw_key(BUTTON_UP,1);		
    } else if (page==2)
    {
        osd_draw_region_rect(300,54,156,108,SBGCOLOR,EQ_R);
        osd_draw_region_rect(116+(7-MAX_BAND)*16,54,MAX_BAND*32-4,108,SBLACKCOLOR,EQ_R);
    
    } else
    {   
    	#ifdef  YADAI_DVD//2004-3-31 10:48 lijd
    	if(page)
    	{osd_draw_region_rect(236+(7-MAX_BAND)*16,54,MAX_BAND*32-4,108,SBLACKCOLOR,EQ_R);}
    	#else
        osd_draw_region_rect(236+(7-MAX_BAND)*16,54,MAX_BAND*32-4,108,SBLACKCOLOR,EQ_R);
        #endif
    }
	
#endif	
    sound_draw_tab();
#ifndef ONLY_SHOW_3D_SPECTRUM	
    if (page<2)
    {
        int item;

        for (item=0;item<6;item++) // draw all button and string on it
        {
            osd_draw_sound_button(2,item,12,SBGCOLOR,BUTTON_UP);
            id=sound_item[page][2+item];
            str=_OsdMessegeFont1[osd_font_mode][id];	
            osd_DrawRegionString(3,item*8+3,(BYTE *)str,SBLACKCOLOR,SBGCOLOR,EQ_R);		
        }

	/*********************************************************************/
        index_y=sound_sel[page]-2;
	
        //ShowSoundSel(SW_REGION_ANTI);
        sel=sound_sel[1];
        
        if(sel==MAX_MUSIC+2)  //user set
        {
            memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND);
        } else {
            memcpyS(&RegionValStr[BAND_R], &music_osd_set[sel-2], MAX_BAND);
        }
		
        //osd_tog_region(BAND_R, OSD_ON);
        #ifdef YADAI_DVD//2004-3-31 10:55 lijd
        if(page)
        {
        osd_print_eq_setting(BAND_R, 0xff);
        }
	#else
        osd_print_eq_setting(BAND_R, 0xff);
	#endif    
        //strcpy(linebuf, " 60      150     400     1K      3K      7K      15K");
        //PrintOsdMsg2(BAND_NO, 0);
		
        //select
        sel=sound_sel[page];		
        if (sel<2) sel=sound_sel[page]=2;	
        id=sound_item[page][sel];

	if(id)	// show highlight and hollow button
        {
            str=_OsdMessegeFont1[osd_font_mode][id];
	    if (sound_level==0) {
                // when sound_level=0, item region only show which one is pressed, don't need highlight
                osd_draw_sound_button(2,sel-2,12,SBGCOLOR,BUTTON_DOWN);
                osd_DrawRegionString(3,(sel-2)*8+3,(BYTE *)str,4,SBGCOLOR,3);
	    } else {
                osd_draw_sound_button(2,sel-2,12,SANTIBGCOLOR,BUTTON_DOWN);
                osd_DrawRegionString(3,(sel-2)*8+3,(BYTE *)str,SWHITECOLOR,SANTIBGCOLOR,3);
            }
        }
        
    }
#else

       EQ_init();
#endif //ONLY_SHOW_3D_SPECTRUM
#endif//osd_bmp_sound
}
#endif //INDIGO_STYLE_OSDUI


#ifdef INDIGO_STYLE_OSDUI

void sound_draw_tab(void)
{
    UINT8 i;
    BYTE fnColor,bgColor;
	
 	osd_draw_region_rect(4+9+page*PAGE_WID,          0,PAGE_WID,ICON_BG_HEI, SELECT_BTN_COLOR,SURROUND_R);
	osd_draw_region_rect(4+9+page*PAGE_WID,ICON_BG_HEI,PAGE_WID,        9+2,  6,SURROUND_R);

	// draw page outline line
    osd_DrawRegionLine(    4+9+page*PAGE_WID, 0, 4+9+(page+1)*PAGE_WID,             0, 5, 1, SURROUND_R); //top line
    osd_DrawRegionLine(    4+9+page*PAGE_WID, 0,     4+9+page*PAGE_WID, ICON_BG_HEI+9+2, 5, 1, SURROUND_R); //left line
    osd_DrawRegionLine(4+9+(page+1)*PAGE_WID, 0, 4+9+(page+1)*PAGE_WID, ICON_BG_HEI+9+2, 5, 1, SURROUND_R); //right line

    for (i=0;i<SOUND_MAX_PAGE_ITEM;i++) 
    {       
        if (page==i)
		{
            fnColor=SELECT_PAGE_FONT_COLOR;
            bgColor=SELECT_BTN_COLOR;
        }
        else
		{
            fnColor=SANTIBGCOLOR;
            bgColor=PAGE_BG;
        }
        sound_draw_title(i,fnColor,bgColor);
    }
//    if (sound_level==0)
//		sound_draw_title(page,1,12);
}

#else // INDIGO_STYLE_OSDUI

void sound_draw_tab(void)
{
    UINT8 i,line_width;
    BYTE fnColor,bgColor;
	
    if (p_scan==1) line_width=2; else line_width=1;
	
    // draw left vertical line
#ifdef ONLY_SHOW_3D_SPECTRUM //to only show 3d spectrum page by wangfeng,2003-10-22 09:24
    osd_DrawRegionLine(page*80+6, 0, page*80+6, 1,  SWHITECOLOR, 1, EQ_R);
#else
	#ifdef SETUP_COLOR_TYPE1
	SetOsdCol(2,2,SBGCOLOR,0x78501ebf);//wangfeng,2003-10-22 11:15
	SetOsdCol(2,2,SDISABLECOLOR,0xc4953cbf);//wangfeng,2003-10-22 11:15
	#endif
    osd_DrawRegionLine(page*80+6, 5, page*80+6, 36, SWHITECOLOR, 1, SURROUND_R);
    osd_DrawRegionLine(page*80+6, 0, page*80+6, 4,  SWHITECOLOR, 1, EQ_R);
	
    // draw right verticla line
    osd_DrawRegionLine(page*80+86, 5, page*80+86, 36, SBLACKCOLOR, 1, SURROUND_R);	
    osd_DrawRegionLine(page*80+86, 0, page*80+86, 4, SBLACKCOLOR, 1, EQ_R);
	
    // draw bottom horizontal line
    osd_DrawRegionLine(page*80+8, 4, page*80+86, 4, SBGCOLOR, line_width, EQ_R);
	
    osd_draw_region_rect(page*80+8,6,78,30, SBGCOLOR,SURROUND_R);   // make tab page enable	
    osd_draw_region_rect(page*80+8,0,78,4,  SBGCOLOR,EQ_R);         // make tab page enable	

    for (i=0;i<SOUND_MAX_PAGE_ITEM;i++) 
    {        
        if (page==i) {
            if (sound_level==0) {
                fnColor=SWHITECOLOR;
                bgColor=SANTIBGCOLOR;//sound_draw_title(i,SBLACKCOLOR,SANTIBGCOLOR);
            } else {
                fnColor=SBLACKCOLOR;
                bgColor=SBGCOLOR;//sound_draw_title(i,SBLACKCOLOR,SBGCOLOR);
            }
        }
        else {
            fnColor=SBLACKCOLOR;
            bgColor=SDISABLECOLOR;//sound_draw_title(i,SBLACKCOLOR,SDISABLECOLOR);
        }
        sound_draw_title(i,fnColor,bgColor);
    }
    if (sound_level==0) sound_draw_title(page,SWHITECOLOR,SANTIBGCOLOR);
#endif //ONLY_SHOW_3D_SPECTRUM
}

#endif// INDIGO_STYLE_OSDUI

//up_down : 0 -> up, 1 -> down
void sound_draw_item(UINT8 id, UINT8 up_down, BYTE draw_y)
{
	BYTE color;
	const char   *str;	
	str=_OsdMessegeFont1[osd_font_mode][id];

	if (draw_y==(sel-2))
	{
		up_down=1;	// keep button down
		color=4;	// and string color is selected color
	} else {
		color=((draw_y==index_y)?SWHITECOLOR:SBLACKCOLOR);
	}

    if (draw_y==index_y)	// highlight
    {
	#ifdef INDIGO_STYLE_OSDUI
		osd_draw_region_rect(2*16, (draw_y*8+16)*4+4, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), HIGHLIGHT_COLOR,2);    
		osd_DrawRegionString(3,draw_y*8+16,(BYTE *)str,SELECT_PAGE_FONT_COLOR,HIGHLIGHT_COLOR,2);
	#else	
	    osd_draw_sound_button(2,draw_y,12,SANTIBGCOLOR,up_down);
	    osd_DrawRegionString(3,draw_y*8+3,(BYTE *)str,SWHITECOLOR,SANTIBGCOLOR,3);
	#endif
    }
	else
	{
	#ifdef INDIGO_STYLE_OSDUI
		if (draw_y==(sel-2))
		{
			osd_draw_region_rect(2*16, (draw_y*8+16)*4+4, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), SELECT_BTN_COLOR,2);    
    		osd_DrawRegionString(3,draw_y*8+16,(BYTE *)str,SELECT_PAGE_FONT_COLOR,SELECT_BTN_COLOR,2);
		}
		else
		{
	   		osd_draw_region_rect(2*16, (draw_y*8+16)*4+4, (UINT32)(12*16), (UINT32)(SETUP_BTN_HEIGHT), SBGCOLOR,2);    
		    osd_DrawRegionString(3,draw_y*8+16,(BYTE *)str,SANTIBGCOLOR,SBGCOLOR,2);
		}
	#else	
	    osd_draw_sound_button(2,draw_y,12,SBGCOLOR,up_down);
	    osd_DrawRegionString(3,draw_y*8+3,(BYTE *)str,color,SBGCOLOR,3);
	#endif	
    }
}

#ifdef INDIGO_STYLE_OSDUI

void sound_draw_title(BYTE p,BYTE fnColor, BYTE bgColor)
{
	char *str;
	
	id=sound_item[p][1];
	str=(char *)(_OsdMessegeFont1[osd_font_mode][id]);
    osd_DrawRegionString( p*7+2,2,(BYTE *)str,fnColor,bgColor,2);
}
#else //INDIGO_STYLE_OSDUI

void sound_draw_title(BYTE p,BYTE fnColor, BYTE bgColor)
{
	char *str;
	UINT8 line_width;
	BYTE offset=0;
	
	id=sound_item[p][1];
	str=(char *)(_OsdMessegeFont1[osd_font_mode][id]);
	
	if (strlen(str)>4)	// the length of tab is only 4 words
	{
		if (((sound_level==0)&&(fnColor==SBLACKCOLOR))||page!=0)
		{
			str[4]=0;	// when this tab is disable, we show 4 words only
		} else {
			if (p_scan==1)
			{
				line_width=2;
				osd_draw_region_rect(page*80+8+72,7,76,29, SBGCOLOR,SURROUND_R);	// make tab page enable	
			} else {
				line_width=1;
				osd_draw_region_rect(page*80+8+72,7,76,30, SBGCOLOR,SURROUND_R);	// make tab page enable	
			}
			osd_draw_region_rect(page*80+8+72,0,76,4,  SBGCOLOR,EQ_R); // for exceeding length
			
			osd_DrawRegionLine(page*80+8, 5, page*80+86+70, 5, SWHITECOLOR, line_width, SURROUND_R);
			// draw right verticla line
			osd_DrawRegionLine(page*80+86+68, 5, page*80+86+68, 36, SBLACKCOLOR, 1, SURROUND_R);	
			osd_DrawRegionLine(page*80+86+68, 0, page*80+86+68, 4, SBLACKCOLOR, 1, EQ_R);
			// draw bottom horizontal line
			osd_DrawRegionLine(page*80+8, 4, page*80+86+70, 4, SBGCOLOR, line_width, EQ_R);			
		}
	} else if ((!IsOSDChinese())&&(strlen(str)==2)) offset=1;
	
    osd_DrawRegionString(p*5+1+offset,2,(BYTE *)str,fnColor,bgColor,2);	
}
#endif //INDIGO_STYLE_OSDUI


void sound_func_down(void)
{
#ifdef OSD_BMP_SOUND
	sound_bmp_func_down();
#else
	if (bEqDisplay ) return;	
	
	if (sound_level==0)
	{
		sound_level=1;		
		if (page==3)
		{
			index_y=sound_sel[page];
#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)    // for  avoiding audio interrupted to partition sound_draw_key() to several  execution.              
                    if(draw_sound_key_flag ==0 )
                        draw_sound_key_flag = 1;            
#endif                    
			sound_draw_key(BUTTON_DOWN,1);
		} else {
			index_y=0;
			sel=sound_sel[page];
			id=sound_item[page][index_y+2];
			sound_draw_item(id,BUTTON_UP,index_y);					
		}
		#ifdef INDIGO_STYLE_OSDUI
		sound_draw_title(page,SELECT_PAGE_FONT_COLOR,SELECT_BTN_COLOR);
		#else
		sound_draw_title(page,SBLACKCOLOR,SBGCOLOR);
		#endif
		
	} else if (sound_level==1)
	{
		if (page==3)
		{
			if (index_y>11) return;
			index_y++;
			sound_sel[page]=index_y;
#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)     // for  avoiding audio interrupted to partition sound_draw_key() to several  execution.              
                    if(draw_sound_key_flag ==0 )
                        draw_sound_key_flag = 1;            
#endif                    
			sound_draw_key(BUTTON_DOWN,0);
			AUDIF_Set_Key(14-index_y);//2004AUDDRV AudioSetKey(14-index_y);

			//setup_sel[2][4]=14-index_y;
			//audio_key=(INT8)(setup_sel[2][4])-8;
			//run_save_sel_cmd(2,4);
			
		#ifdef DVD_SETUP_REENG
			//JS	 20040820	//for setup_reengineering	//maybe 3D sound page should be rewritten
			setup_VA[SETUP_VA_KEY]=14-index_y;
			audio_key=setup_VA[SETUP_VA_KEY]-SOUND_MIN_ITEM_SEL-6;
			run_save_sel_cmd(setup_VA[SETUP_VA_KEY], SETUP_VA_KEY);
		#else
			//nono modify 4-2-7 15:38	
			SETUP_KEY=14-index_y;
			audio_key=SETUP_KEY-8;
			run_save_sel_cmd(AUDPAGE,KEYITEM);
		#endif

		} else {
			index_y++;
			if (index_y>5) 
			{
				index_y=0;
				sound_level=0;		
				id=sound_item[page][7];
				sound_draw_item(id,BUTTON_UP,5);
				//highlight
				#ifdef INDIGO_STYLE_OSDUI
				sound_draw_title(page,SELECT_PAGE_FONT_COLOR,SELECT_BTN_COLOR);
				#else
				sound_draw_title(page,SWHITECOLOR,SANTIBGCOLOR);
				#endif
			} else {			
				
				id=sound_item[page][index_y+2-1];
				sound_draw_item(id,BUTTON_UP,index_y-1);
							
				id=sound_item[page][index_y+2];
				sound_draw_item(id,BUTTON_UP,index_y);
			}
		}
	} else {	// sound_level=2, for EQ adjustment
		if(index_y>1) 
		{
			index_y--;
			user_osd_set[index_x]=index_y;
			show_band();
		}
		SettingEqLevel(user_osd_set);		
	}

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

#ifdef 	MONE_sound					
	printf("sound_func_down:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);	
#endif		


	#ifdef INDIGO_STYLE_OSDUI	
	// 2006-03-06, mimitsai add for add cursor highlight
	if(sound_level==0)
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  7,SURROUND_R);//draw page highlight
	else
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  setupBGcolorBTB,SURROUND_R);//clear page highlight
	#endif		

#endif//osd_bmp_sound
}

void sound_func_up(void)
{
#ifdef OSD_BMP_SOUND
	sound_bmp_func_up();
#else
	if (bEqDisplay) return;

	if (sound_level==0)
	{
		sound_level=1;
		if (page==3)
		{
			index_y=sound_sel[page];
#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)     // for  avoiding audio interrupted to partition sound_draw_key() to several  execution.              
                    if(draw_sound_key_flag ==0 )
                        draw_sound_key_flag = 1;            
#endif                    
			sound_draw_key(BUTTON_DOWN,1);
		} else {		
			index_y=5;
			id=sound_item[page][index_y+2];
			sound_draw_item(id,BUTTON_UP,index_y);		
		}
		#ifdef INDIGO_STYLE_OSDUI
			sound_draw_title(page,SELECT_PAGE_FONT_COLOR,SELECT_BTN_COLOR);
		#else
		sound_draw_title(page,SBLACKCOLOR,SBGCOLOR);
		#endif
		
	} else if (sound_level==1) {
		if (page==3)
		{
			if (index_y<1) return;
			index_y--;
			sound_sel[page]=index_y;
#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)     // for  avoiding audio interrupted to partition sound_draw_key() to several  execution.              
                    if(draw_sound_key_flag ==0 )
                        draw_sound_key_flag = 1;            
#endif                    
			sound_draw_key(BUTTON_DOWN,0);
			AUDIF_Set_Key(14-index_y);//2004AUDDRV AudioSetKey(14-index_y);
			//setup_sel[2][4]=14-index_y;
			//audio_key=(INT8)(setup_sel[2][4])-8;
			//run_save_sel_cmd(2,4);

		#ifdef DVD_SETUP_REENG
			//JS	 20040820	//for setup_reengineering	//maybe 3D sound page should be rewritten
			setup_VA[SETUP_VA_KEY]=14-index_y;
			audio_key=setup_VA[SETUP_VA_KEY]-SOUND_MIN_ITEM_SEL-6;
			run_save_sel_cmd(setup_VA[SETUP_VA_KEY], SETUP_VA_KEY);
		#else
			//nono modify 4-2-7 15:38
			SETUP_KEY=14-index_y;
			audio_key=SETUP_KEY-8;
			run_save_sel_cmd(AUDPAGE,KEYITEM);
		#endif

		} else {		
			if (index_y==0) 
			{
				index_y=5;
				sound_level=0;		
				id=sound_item[page][2];
				sound_draw_item(id,BUTTON_UP,0);
				// highlight
				#ifdef INDIGO_STYLE_OSDUI
				sound_draw_title(page,SELECT_PAGE_FONT_COLOR,SELECT_BTN_COLOR);
				#else
				sound_draw_title(page,SWHITECOLOR,SANTIBGCOLOR);
				#endif
			} else {			
				index_y--;
				
				id=sound_item[page][index_y+2+1];
				sound_draw_item(id,BUTTON_UP,index_y+1);
							
				id=sound_item[page][index_y+2];
				sound_draw_item(id,BUTTON_UP,index_y);
			}
		}
	} else {	// sound_level=2, for EQ adjustment
		if(index_y<25) 
		{
			index_y++;
			user_osd_set[index_x]=index_y;
			show_band();
		}
		SettingEqLevel(user_osd_set);		
	}	

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

#ifdef 	MONE_sound					
	printf("sound_func_up:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);
#endif	
printf_w("sound_func_up:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);


	#ifdef INDIGO_STYLE_OSDUI	
	// 2006-03-06, mimitsai add for add cursor highlight
	if(sound_level==0)
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  7,SURROUND_R);//draw page highlight
	else
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  setupBGcolorBTB,SURROUND_R);//clear page highlight
	#endif		
#endif
}

void sound_func_left(void)
{

    counter_down = 3;  // slow down the speed of switching the the pages of 3D sound 
                                 // by delaying the IR key. by robert.chang,2006-09-11           
#ifdef OSD_BMP_SOUND
	sound_bmp_func_left();
#else

	//if (bEqDisplay ) return;
	
	if (sound_level==0)	// for tab selection
	{
#ifdef SOUND_NO_KEYPAGE     //wanghaoying 2003-9-10 11:00
        if (page>0) page--; else page=2;
#else
		if (page>0) page--; else page=3;
#endif
		
		if (page==2) 
		{	
			SetOsdCol(3,3,SANTIBGCOLOR,0xa346ffff);
			EQ_init(); 
		} else { 
			SetOsdCol(3,3,SANTIBGCOLOR,0xa346ffc0);
			//bEqDisplay=0;
			setup_eq_display(0);//terry,2003/9/26 04:43PM
			sound_set_EQ_again();//nono 4-7-23 18:28
		}
#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)    // for  avoiding audio interrupted to partition ShowSoundPage() to several  execution.          
        	draw_sound_flag = 1;
#endif
		ShowSoundPage();
	} else if (sound_level==2)	// for EQ adjustment
	{
		if(index_x==0) return;
	#ifdef INDIGO_STYLE_OSDUI
			// clear rect.
			osd_draw_region_rect(15+EQ_XSTART_PIXEL+index_x*32-1, 55+50, 16+2, 108, BAND_BG_COLOR, EQ_R);
	#else
			osd_draw_region_rect(15+EQ_XSTART_PIXEL+index_x*32,    54, 16, 108, SBLACKCOLOR, EQ_R);			
	#endif
		if(id==STR_OS_ATTRIB)	
		{
			index_x--;
			index_y=user_osd_set[index_x];

		#ifdef INDIGO_STYLE_OSDUI
			//osd_draw_region_rect(15+EQ_XSTART_PIXEL+index_x*32, 55+50, 16, 108, SELECT_BTN_COLOR, EQ_R);
			int xStart 	= 15+EQ_XSTART_PIXEL+index_x*32;
			int yStart 	= 55+50;
			int xRect 	= 16;
			int yRect	= 108;
			// draw rect with four lines.
			osd_draw_horizontal_line(xStart        , xStart+xRect  , yStart        , 7, 2, EQ_R);
			osd_draw_horizontal_line(xStart        , xStart+xRect  , yStart+yRect-2, 7, 2, EQ_R);			
			osd_draw_vertical_line	(xStart        , yStart        , yStart+yRect  , 7, 2, EQ_R);	
			osd_draw_vertical_line	(xStart+xRect-2, yStart        , yStart+yRect  , 7, 2, EQ_R);	
		#else
			osd_draw_region_rect(15+EQ_XSTART_PIXEL+index_x*32,    58, 16, 102, SANTIBGCOLOR, EQ_R);	
		#endif
			show_band();
		}		
	}

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

#ifdef 	MONE_sound					
	printf("sound_func_left:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);
#endif	
	
	#ifdef INDIGO_STYLE_OSDUI
	// 2006-03-06, mimitsai add for add cursor highlight
	if(sound_level==0)
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  7,SURROUND_R);//draw page highlight
	else
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  setupBGcolorBTB,SURROUND_R);//clear page highlight
	#endif		
#endif	
}

void sound_func_right(void)
{	

    counter_down = 3; // slow down the speed of switching the the pages of 3D sound 
                                 // by delaying the IR key. by robert.chang,2006-09-11
#ifdef OSD_BMP_SOUND
	sound_bmp_func_right();
#else
	//if (bEqDisplay ) return;

	if (sound_level==0)	// for tab selection
	{
		page++;
#ifdef SOUND_NO_KEYPAGE     //wanghaoying 2003-9-10 11:00
        if (page>2) page=0;
#else
		if (page>3) page=0;
#endif
		
		if (page==2) 
		{
			SetOsdCol(3,3,SANTIBGCOLOR,0xa346ffff);
			EQ_init(); 
		} else {
			SetOsdCol(3,3,SANTIBGCOLOR,0xa346ffc0);
			//bEqDisplay=0;
			setup_eq_display(0);//terry,2003/9/26 04:43PM
			sound_set_EQ_again();//nono 4-7-23 18:28
		}
#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)     // for  avoiding audio interrupted to partition ShowSoundPage() to several  execution.         
        	draw_sound_flag = 1;
#endif
		ShowSoundPage();
	} else if (sound_level==2)	// for EQ adjustment
	{
		if(index_x>MAX_BAND-2) return;
		
	#ifdef INDIGO_STYLE_OSDUI
			// clear rect.
			osd_draw_region_rect(15+EQ_XSTART_PIXEL+index_x*32-1, 55+50, 16+2, 108, BAND_BG_COLOR, EQ_R);
	#else
			osd_draw_region_rect(15+EQ_XSTART_PIXEL+index_x*32,    54, 16, 108, SBLACKCOLOR, EQ_R);		
	#endif
		if(id==STR_OS_ATTRIB)	
		{
			index_x++;
			index_y=user_osd_set[index_x];
		#ifdef INDIGO_STYLE_OSDUI			
	 	  	//osd_draw_region_rect(15+EQ_XSTART_PIXEL+index_x*32, 55+50, 16, 108, SELECT_BTN_COLOR, EQ_R);
			int xStart 	= 15+EQ_XSTART_PIXEL+index_x*32;
			int yStart 	= 55+50;
			int xRect 	= 16;
			int yRect	= 108;
			// draw rect with four lines.
			osd_draw_horizontal_line(xStart        , xStart+xRect, yStart        , 7, 2, EQ_R);
			osd_draw_horizontal_line(xStart        , xStart+xRect, yStart+yRect-2, 7, 2, EQ_R);			
			osd_draw_vertical_line	(xStart        , yStart      , yStart+yRect  , 7, 2, EQ_R);	
			osd_draw_vertical_line	(xStart+xRect-2, yStart      , yStart+yRect  , 7, 2, EQ_R);	
		#else
				osd_draw_region_rect(15+EQ_XSTART_PIXEL+index_x*32,    58, 16, 102, SANTIBGCOLOR, EQ_R);
		#endif
			show_band(); // show user keyin band value
		}
			
	}

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

#ifdef 	MONE_sound					
		printf("sound_func_right:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);
#endif

	#ifdef INDIGO_STYLE_OSDUI
	// 2006-03-06, mimitsai add for add cursor highlight
	if(sound_level==0)
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  7,SURROUND_R);//draw page highlight
	else
		osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  setupBGcolorBTB,SURROUND_R);//clear page highlight
	#endif		
#endif		
}

void EQ_init(void)
{
    int	i;
	
    //current is test
    for(i=0;i<13;i++)
        bEqEnergyMax[i]=0;
	
//marked by wangwei,2004-9-17 16:04(now,when switch band to EQ,the EQ will comeback to the latest setting.)
		/*if (sound_sel[1]!=2) //nono 20040722 EQ is changed to STANDARD mode.
		sound_sel[1]=2;*/

	
    unEqMaxRef=0;
	
    //bEqDisplay=1;
    //setup_eq_display(1);//terry,2003/9/26 04:43PM
    setup_eq_display(0xf);//nono 2003-10-22 15:14 change for new dsp code.
        
    #ifdef DYNAMIC_SPECTRUM  //fengjl add to make background transparent for bbk 3-12-17 20:11     
    SetOsdCol(3,3,SBLACKCOLOR,0x1e1e1e90);   
    #endif
    
    #ifndef ONLY_SHOW_3D_SPECTRUM	//I don't know whether it is a bug? So i forbit this line,wangfeng,2003-10-21 15:48
    osd_draw_region_rect(300,54,156,108,SBGCOLOR,EQ_R);
    #elif defined(DYNAMIC_SPECTRUM)  //fengjl add 3-12-17 20:30
   osd_draw_region_rect(96,54,220+20+20,108,SBLACKCOLOR,EQ_R);  
    #else
    osd_draw_region_rect(116,54,220,108,SBLACKCOLOR,EQ_R);    
    #endif
}		

/***********************************************************************\
setup special functions
\***********************************************************************/

void sound_func_set_EQ(BYTE EQitem)
{
    memcpyS(&RegionValStr[BAND_R], &music_osd_set[EQitem-2], MAX_BAND);
    if ((EQitem-2) >= MAX_MUSIC) //ycwen 2005/8 check array boundary is necessary
        return;
    switch (EQitem-2) 
	{
	    case 0:
	        //SettingEqLevel((BYTE *)&music_osd_set[EQitem-2]);//Steven 2006/08/15 mark to avoid calling EQ func repeatly 
	        SettingEQType(0);
	        break;
	    default:
	        SettingEqLevel((BYTE *)&music_osd_set[EQitem-2]);
	        //SettingEqLevel((BYTE *)&music_osd_set[EQitem-2]);//Steven 2006/08/15 mark to avoid calling EQ func repeatly 
	    break;
	}		
}

void sound_set_EQ_again(void)
{
    sound_func_set_EQ(sound_sel[1]);
    AUDIF_Set_Surround(sound_sel[0]-2);//2004AUDDRV AudioSetSurround(sound_sel[0]-2);
    if(sound_sel[1]==7)//id==USER
    {
    	memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND); 
    	SettingEqLevel(user_osd_set);      
    }
}

void sound_func_select(void)
{	

    counter_down = 2;  // slow down the speed of switching the the pages of 3D sound 
                                 // by delaying the IR key. by robert.chang,2006-09-11           

#ifdef OSD_BMP_SOUND
    sound_bmp_func_select();
#else
    if (bEqDisplay) return;
	
	if (sound_level==0)
	{
		if (page==3) sound_func_down();
	} else if (sound_level==1)
	{	
		UINT8 old_sel=sound_sel[page];
		if (page==3)
		{
			sound_level=0;

			#ifdef INDIGO_STYLE_OSDUI
			// 2006-03-06, mimitsai add for add cursor highlight
			if(sound_level==0)
				osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  7,SURROUND_R);//draw page highlight
			else
				osd_draw_region_rect(4+9+page*PAGE_WID+10, ICON_BG_HEI, PAGE_WID-20, 7,  setupBGcolorBTB,SURROUND_R);//clear page highlight
			#endif				
		
		#ifdef INDIGO_STYLE_OSDUI	
			sound_draw_title(page,SELECT_PAGE_FONT_COLOR,SELECT_BTN_COLOR);
		#else
			sound_draw_title(page,SBLACKCOLOR,SANTIBGCOLOR);
		#endif

#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)     // for  avoiding audio interrupted to partition sound_draw_key() to several  execution.    
                    if(draw_sound_key_flag ==0 )
                        draw_sound_key_flag = 1;
#endif                     
			sound_draw_key(BUTTON_UP,1);

            OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

			return;
		}
		
		sound_sel[page]=index_y+2;
		sel=sound_sel[page];
		
		// disable old selected item	
		id=sound_item[page][old_sel];
		sound_draw_item(id,BUTTON_UP,old_sel-2);
		
		// enable new selected item
		id=sound_item[page][sel];
		sound_draw_item(id,BUTTON_DOWN,index_y);
		
		
		if (page==0)	// in surround page
		{
			AUDIF_Set_Surround(sel-2);//2004AUDDRV AudioSetSurround(sel-2);			
			if ((sound_sel[1]!=2)&((sel-2)!=0))//Steven 2006/08/15 modify the EQ behavior when surround turn on
			{				
				sound_sel[1]=2;
				//sel=sound_sel[1];
				memcpyS(&RegionValStr[BAND_R], &music_osd_set[sound_sel[1]-2], MAX_BAND);
				osd_print_eq_setting(BAND_R, 0xff);
				//added by wangwei,2004-9-17 16:04
				//(avoid the bug when switch EQ to surround and set surround there will be no effect)
				//sound_set_EQ_again();  
                AUDIF_Set_EQType(0);
				
			} 
            //Steven 2006/08/15 mark to modify the EQ behavior when surround turn on
            //else {
			//	if ((sel-2)!=0) //Surround is open, so we should set EQ to standard mode
			//		AUDIF_Set_EQType(0);//2004AUDDRV AudioSetEQType(0);
					//sound_set_EQ_again();  //added by wangwei,2004-9-17 16:04
			//}
		} else {	// in EQ page
			if(id!=STR_OS_USER) {

/*				memcpyS(&RegionValStr[BAND_R], &music_osd_set[sel-2], MAX_BAND);
				switch (sel-2) 
				{
	                case 0:
	                    SettingEQType(0);
	                    break;
	                default:
	                    SettingEqLevel((BYTE *)&music_osd_set[sel-2]);
	                    SettingEqLevel((BYTE *)&music_osd_set[sel-2]);
	                    break;
				}				
*/
                sound_func_set_EQ(sel);
				osd_print_eq_setting(BAND_R, 0xff);
			} else {	

				//osd_user_init 
				{
					// cancel highlight, and move cursor to EQ chart
					const char   *str;	
					id=sound_item[page][index_y+2];
					str=_OsdMessegeFont1[osd_font_mode][id];
					osd_draw_sound_button(2,index_y,12,SBGCOLOR,1);			
				#ifdef INDIGO_STYLE_OSDUI	
					osd_DrawRegionString(3,index_y*8+16,(BYTE *)str,5,6,3);
				#else
					osd_DrawRegionString(3,index_y*8+3,(BYTE *)str,4,SBGCOLOR,3);
				#endif
				}
				
			#ifdef INDIGO_STYLE_OSDUI
					//osd_draw_region_rect(15+EQ_XSTART_PIXEL, 55+50, 16, 108, SELECT_BTN_COLOR, EQ_R);
					int xStart 	= 15+EQ_XSTART_PIXEL;
					int yStart 	= 55+50;
					int xRect 	= 16;
					int yRect	= 108;
					// draw rect with four lines.
					osd_draw_horizontal_line(xStart        , xStart+xRect, yStart        , 7, 2, EQ_R);
					osd_draw_horizontal_line(xStart        , xStart+xRect, yStart+yRect-2, 7, 2, EQ_R);			
					osd_draw_vertical_line	(xStart        , yStart      , yStart+yRect  , 7, 2, EQ_R);	
					osd_draw_vertical_line	(xStart+xRect-2, yStart      , yStart+yRect  , 7, 2, EQ_R);	
			#else
					osd_draw_region_rect(15+EQ_XSTART_PIXEL,    54, 16, 108, SANTIBGCOLOR, EQ_R);	// in EQ chart selection (first column)
			#endif			
				index_x=0;
				memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND); 
				SettingEqLevel(user_osd_set);      
				osd_print_eq_setting(BAND_R, index_x*2); 		
					      
				id=STR_OS_ATTRIB;	     		
				index_y=user_osd_set[index_x];
				sound_level=2;
			}		
			
			if ((sound_sel[0]!=2)&(sel!=2)) {//Steven 2006/08/15 modify the surround  behavior when EQ turn on
			    sound_sel[0]=2;
                        AUDIF_Set_Surround(sound_sel[0]-2);

			}
		}

	} else if (sound_level==2)
	{
		sound_level=1;
#if defined(SUPPORT_SW_OSD_SCALING)&&defined(INDIGO_STYLE_OSDUI)     // for  avoiding audio interrupted to partition ShowSoundPage() to several  execution.         
              draw_sound_flag = 1;
#endif
		ShowSoundPage();
	}

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

#ifdef 	MONE_sound
	printf("sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);
#endif		
//yanlb added 2004/07/07
#ifdef REMB_3DSOUND
	run_sound_save(sound_sel);    
#endif
#endif//osd_bmp_sound
}

#ifdef  DYNAMIC_SPECTRUM  //fengjl  3-10-30 15:04
void Show3dspectrum(void)    
{	          	
    
	osd_init_music();	
	SetOsdCol(3,3,SBGCOLOR,0x78501e00);   // draw background
    osd_draw_region_rect(0, 0, PAGE_WIDTH,    224, SBGCOLOR,      EQ_R);     
    //osd_DrawRegionLine(page*80+6, 0, page*80+6, 1,  SWHITECOLOR, 1, EQ_R); 
    //osd_tog_region(EQ_R, OSD_ON);    //avoid aa white dot on screen   fengjl  3-12-22 23:31
    timeout_osd[EQ_R] = 0;
    EQ_init();	
    ClearShowSpectrum();
}
/*
 *Function Description:
 *
 *     when tray out or stop, there is no spectrum to show.
 *
 * zhaoyanhua 03-11-1 15:26 
 */
void ClearShowSpectrum(void)
{
	int i;
	BYTE	bEqValue[MAX_BAND];
	
	for(i = 0;i < MAX_BAND;i++)
		bEqValue[i] = 0;
		//current is test
    for(i=0;i<13;i++)
        bEqEnergyMax[i]= 0;
    
    SetEQ();
	osd_print_eq(BAND_R, bEqValue);	
}

#endif

#ifdef _DYNAMIC_SPECRUM
//Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //
void Dynamic_Spectrum(void)
{
    		BYTE    i,j;
		BYTE	bEqValue[MAX_BAND];
		//BYTE 	*p;

            //p = get_dsp_pcm_uptr(DSP_RUNTIME_EQ_SPECTRUM,0);
            			
            for (i=0, j=0;i<MAX_BAND;i++) 
            {
                UINT32  eqSrc;
                UINT32  eqTemp;
                
                //eqSrc = (((*p)<<8) | *(p+1));                
                //p+=3;
                eqSrc = get_dsp3_pcm_value((DSP_RUNTIME_EQ_SPECTRUM+i))>>8;
                if (eqSrc > unEqMaxRef)
					unEqMaxRef = eqSrc;

                //normalize value to 0 ~ 25
                if (unEqMaxRef==0) //EQ value range check
                    eqTemp = 0;
                else
                    eqTemp = eqSrc*25/unEqMaxRef;

                bEqValue[i] = eqTemp;
				
                if (bEqValue[i]<4) {
                    j++;
                }
            }

            //adjust max refrence 
            if ( (j>=MAX_BAND-1) && (unEqMaxRef>400) )
                unEqMaxRef=unEqMaxRef-(unEqMaxRef/8);			
            osd_print_eq(BAND_R, bEqValue);			
        } 

#endif

//Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //
//display EQ chart(REGION3)
void DisplayEq(void)
{
    BYTE    i,j;
	BYTE	bEqValue[MAX_BAND];
	//BYTE 	*p;
    
    #ifdef   DYNAMIC_SPECTRUM     //  fengjl  3-10-28 18:00
    	if(bEqDisplay)
    #else
    if ( (full_scrn&SOUND) && bEqDisplay ) 
    #endif
    
    {
        
        if (bEqDisplay>=4) 
        {
            //p = get_dsp_pcm_uptr(DSP_RUNTIME_EQ_SPECTRUM,0);
            			
            for (i=0, j=0;i<MAX_BAND;i++) 
            {
                UINT32  eqSrc;
                UINT32  eqTemp;
                
                //eqSrc = (((*p)<<8) | *(p+1));                
                //p+=3;
                eqSrc = get_dsp3_pcm_value((DSP_RUNTIME_EQ_SPECTRUM+i))>>8;
                if (eqSrc > unEqMaxRef)
					unEqMaxRef = eqSrc;

                //normalize value to 0 ~ 25
                if (unEqMaxRef==0) //EQ value range check, Jeff 20021113
                    eqTemp = 0;
                else
                    eqTemp = eqSrc*25/unEqMaxRef;

                bEqValue[i] = eqTemp;
				
                if (bEqValue[i]<4) {
                    j++;
                }
            }

            //adjust max refrence 
            if ( (j>=MAX_BAND-1) && (unEqMaxRef>400) )
                unEqMaxRef=unEqMaxRef-(unEqMaxRef/8);
			
            osd_print_eq(BAND_R, bEqValue);			
            bEqDisplay=1;
        } else {
            bEqDisplay++;
        } // end of if ((bEqDisplay&0x0f)==4)

#ifdef   DYNAMIC_SPECTRUM        
        {//terry,2003/12/24 10:16PM
          UINT8 on_off;
    
#ifdef LPCM_NO_SHOW_BAND  //fengjl add 2004-03-19 18:51    
          if( (cd_type_loaded!=CDUNKNOWN)&&(Is_JPEG_STATE()==0)&&(coding_mode_now!=AUDIF_CODING_MODE_LPCM) )  on_off= OSD_ON;
#else
          if( (cd_type_loaded!=CDUNKNOWN)&&(Is_JPEG_STATE()==0) )  on_off= OSD_ON;
#endif

          else on_off= OSD_OFF;
          //printf("Is_JPEG_STATE():%d ,on_off:%x \n",Is_JPEG_STATE(),on_off);
          osd_tog_region(EQ_R, on_off); 
        }
#endif//#ifdef   DYNAMIC_SPECTRUM
    } // end of if ( (full_scrn&SOUND) && bEqDisplay )
    
    
}

//restore 3Dsound
//added by wangwei,2004-9-17 16:04
#ifdef SETUP_RESTORE_ALSO_RESTORE_3D
void restore_3Dsound(void)
{
    //restore 3D surround & EQ.
    sound_sel[0]=SURR_OFF;				
    sound_sel[1]=EQ_STANDARD;
    //restore 3D EQ user setting.
    UINT8 i;
    for(i=0;i<MAX_BAND;i++)
        user_osd_set[i] = EQ_USER_DEFAULT_VAL;
}
#endif

//set EQ type
//input:array of 7 band
void SettingEqLevel(BYTE *p)
{//Steven 2006/10/04 modify , use set_dsp3_pcm_value() instead of directly access address //
	int i;	
  	//bpcm_ya_ptr = get_dsp_pcm_uptr(0,0);//David add for avoiding bpcm_ya_ptr NULL 2005-2-16 16:31
	for (i=0;i<MAX_BAND;i++) 
	{	
		set_dsp3_pcm_value((DSP_RUNTIME_EQ_GAIN + i),p[i]);
	}
	AUDIF_Set_EQType(0x0010);//2004AUDDRV AudioSetEQType(0x0010);	
	AUDIF_Set_Surround(0);//2004AUDDRV AudioSetSurround(0);
}

//set EQ type
//input:type
//      0:NORMAL
//      The following aren't be used
//      1:CLASSIC
//      2:JAZZ
//      3:ROCK
//      4:POP
//      5:FOLK
//      6:DANCE
void SettingEQType(BYTE type)
{
	AUDIF_Set_EQType(type);//2004AUDDRV AudioSetEQType(type);	
	
	//#ifdef AVOID_3D_NOISE //ycwen 2005/8/3 to prevent EQ/SRND from pop pop noise
	if (type > 0 )//Steven 2006/08/15 mark define AVOID_3D_NOISE to avoid calling SURROUND func repeatly 
	//#endif    
	    AUDIF_Set_Surround(0);//2004AUDDRV AudioSetSurround(0);
}

#ifdef SOUND_EFFECT_MENU          //sunzhh add 2004-5-5 15:44
void SetSurround(void)                     
{    	BYTE EQ_type;
        BYTE surround_type;
        AUDIF_Set_Surround(surround_type - 1);//2004AUDDRV AudioSetSurround(surround_type - 1);
    	if(surround_type > 1)
	{	
		AUDIF_Set_EQType(0);//2004AUDDRV AudioSetEQType(0);
		EQ_type = 1;//Standard mode
	}
	//6 mode :
}
#endif

#ifdef PROLOGICII_3D_MUTEX//nono 4-2-12 0:58
BYTE soundGetSurroundType()
{
    BYTE iVal=0;	
    iVal=sound_sel[0]-2;	
    return iVal;
}
BYTE soundGetEQType()
{
    BYTE iVal=0;	
    iVal=sound_sel[1]-2;	
    return iVal;
}

BYTE is_EQ_SOUND_set()
{
	if(soundGetEQType()>0 ||soundGetSurroundType()>0 )
	return 1;
	else
	return 0;
}
#endif//#ifdef PROLOGICII_3D_MUTEX

#ifdef OSD_BMP_SOUND
/* 
 * Fuction:
 *	  ShowBmpSoundPage()
 * Description:
 *      draw the bmp sound page when press ir 3D key
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */
void ShowBmpSoundPage(void)
{
printf("**********ShowBmpSoundPage()*********\n");

   sound_bmp_draw_tab();//draw regionA,B,D
   OSD_LayoutSoundRegionE();
   OSD_LayoutSoundRegionF();

    const char  *str;	
    if (page == KEY_PAGE) 
    {
        sound_bmp_draw_key(BUTTON_UP,1);		
    } 
    else if (page == BAND_PAGE)
    {
     	OSD_LayoutRect(SOUND_BAND_BG_RECT_E1,0);//layout band bg
    } 
    else//srnd_page and eq_page
    {   
	OSD_LayoutRect(SOUND_EQ_BG_RECT_E1,0);//layout eq bg
    }
	
#ifndef ONLY_SHOW_3D_SPECTRUM	
    if (page < BAND_PAGE) //srnd page or eq page
    {
        UINT8 uiItem;
	//sound_bmp_draw_item_cursor();//draw cursor on the item
	
        for (uiItem=0; uiItem < ITEM_NUM; uiItem++) // draw all button and string on it
        {
            id=sound_item[page][2+uiItem];
            str=_OsdMessegeFont1[osd_font_mode][id];	
	//	if(uiItem == index_y)
	//	{
	//	    OSD_LayoutStr(str, SOUND_HL_ITEM_STR_E4, uiItem);//highlighted item string
	//	}
	//	else
	//	{
		    OSD_LayoutStr(str, SOUND_UNHL_ITEM_STR_E4, uiItem);//unhighted item string
	//	}
        }//for (item=0; item<6; item++)


        index_y=sound_sel[page]-2;
	
        sel=sound_sel[1];
        
        if(sel==MAX_MUSIC+2)  //user set
        {
            memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND);
        } 
        else
        {
            memcpyS(&RegionValStr[BAND_R], &music_osd_set[sel-2], MAX_BAND);
        }
		
        #ifdef YADAI_DVD//2004-3-31 10:55 lijd
        if(page)
        {
        osd_print_eq_setting(BAND_R, 0xff);
        }
	#else
        osd_print_eq_setting(BAND_R, 0xff);
#endif
		
        //select
        sel=sound_sel[page];		
        if (sel<2) 
            sel=sound_sel[page]=2;	
        
        id=sound_item[page][sel];

	if(id)	// show highlight and hollow button
        {
            str=_OsdMessegeFont1[osd_font_mode][id];
	    	if (sound_level==0) 
		{
                // when sound_level=0, item region only show which one is pressed, don't need highlight
			//unhighlight user item
			OSD_LayoutLine(SOUND_SEL_UP_LINE_E4, sel-2);
			OSD_LayoutRect(SOUND_SEL_RECT_E4,sel-2);
			OSD_LayoutLine(SOUND_SEL_DOWN_LINE_E4, sel-2);      	
			//unhighlight user item string
			OSD_LayoutStr(str, SOUND_HL_ITEM_STR_E4, sel-2);
            }
	    	else 
		{
		    	OSD_LayoutRect(SOUND_UNSEL_RECT_E4, sel-2);
		    	OSD_LayoutStr(str, SOUND_UNHL_ITEM_STR_E4, sel-2);
        }
        }//end if (id)
        
    }//end if page<BAND_PAGE
#else

       EQ_bmp_init();
#endif //ONLY_SHOW_3D_SPECTRUM

}

/* 
 * Fuction:
 *	  OSD_LayoutSoundRegionA()
 * Description:
 *      draw 3D menu regionA according to the index
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */

void OSD_LayoutSoundRegionA(void)
{
	const OSD_REGIONA_LAYOUT_S* pLayout = &g_aOsdSoundRegionA;

    OSD_LayoutBmp(pLayout->uiBg, 0);//draw setup1_bg.bmp in regionA
    OSD_LayoutBmp(pLayout->uiDownBg, page);//draw setup1_bg.bmp    
    OSD_LayoutLine(pLayout->uiLineLeft, page);//draw line1
    OSD_LayoutLine(pLayout->uiLineRight, page);//draw line2
    OSD_LayoutRect(pLayout->uiShadow, page);//draw shadow

}// end of OSD_LayoutSoundRegionA()

/* 
 * Fuction:
 *	  OSD_LayoutSoundRegionB()
 * Description:
 *      draw 3D menu regionB according to the index,including the string on it
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */
void OSD_LayoutSoundRegionB(void)
{
	const OSD_REGIONB_LAYOUT_S* pLayout = &g_aOsdSoundRegionB;
	UINT8 uiFontId = 0;
    	UINT8 uiStrIndex = 0;
   	char *str;
    	int i;

    OSD_LayoutRect(pLayout->uiBg, 0);
    OSD_LayoutLine(pLayout->uiBgLine, 0);//draw bg line
    OSD_LayoutRect(pLayout->uiDownBg, page);//draw down bg
    if(sound_level == 0)//highlighted
    	OSD_LayoutBmp(pLayout->uiCursor, page);//draw cursor1.bmp  
    OSD_LayoutLine(pLayout->uiLineLeft, page);//draw line1
    OSD_LayoutLine(pLayout->uiLineRight, page);//draw line2
    OSD_LayoutRect(pLayout->uiShadow, page);//draw shadow

      	//draw string
   	for (i=0;i<SOUND_MAX_PAGE_ITEM;i++) 
	{        
        	if (page==i) //selected page
        	{
            		//index str in regionB
            		uiStrIndex = pLayout->uiSelStr;//the str index is the selected mode in regionB       
        	}
        	else //unselected page
        	{
            		uiStrIndex = pLayout->uiUnselStr; //the str index is the unselected mode in regionB                             
        	}
        
        	//draw the string on the tab
        	uiFontId=sound_item[i][1];
	    	str=(char *)(_OsdMessegeFont1[osd_font_mode][uiFontId]);
        	OSD_LayoutStr(str, uiStrIndex,i);    
	}

}// end of OSD_LayoutSoundRegionB()


/* 
 * Fuction:
 *	  OSD_LayoutSoundRegionD()
 * Description:
 *      draw 3D menu regionD according to the index
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */
void OSD_LayoutSoundRegionD(void)
{
	const OSD_REGIOND_LAYOUT_S* pLayout = &g_aOsdSoundRegionD;

    OSD_LayoutBmp(pLayout->uiLeftBg, 0);//draw left bg.bmp 4-1
    OSD_LayoutBmp(pLayout->uiMiddleBg, page);//draw middle bg 4-2
    OSD_LayoutBmp(pLayout->uiRightBg, 0);//draw right bg.bmp 4-3
    OSD_LayoutRect(pLayout->uiDownBg, page);//draw down bg rect
    if(sound_level == 0)
        OSD_LayoutBmp(pLayout->uiCursor,page);
    OSD_LayoutLine(pLayout->uiLineLeft, page);//draw line1
    OSD_LayoutLine(pLayout->uiLineRight, page);//draw line2
    OSD_LayoutRect(pLayout->uiShadow, page);//draw shadow
}// end of OSD_LayoutSoundRegionD()

/* 
 * Fuction:
 *	  OSD_LayoutSoundRegionE()
 * Description:
 *      draw 3D menu regionE according to the index,only including 
 *	the left and right bmp side of the regionE. The inner str,line,rect elements
 *    can not be layout by this function.
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */

void OSD_LayoutSoundRegionE(void)
{
	const OSD_REGIONE_LAYOUT_S* pLayout = &g_aOsdSoundRegionE;

	//from left to right
    OSD_LayoutBmp(pLayout->uiLeftBg, 0);//draw left bg.bmp 5-1
    OSD_LayoutRect(pLayout->uiMiddleBg,0);//draw middle rect
    OSD_LayoutBmp(pLayout->uiRightBg, 0);//draw right bg.bmp 5-3
    
}// end of OSD_LayoutSoundRegionE()


/* 
 * Fuction:
 *	  OSD_LayoutSoundRegionF()
 * Description:
 *      draw 3D menu regionF according to the index,including the string on it
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */

void OSD_LayoutSoundRegionF(void)
{
	const OSD_REGIONF_LAYOUT_S* pLayout = &g_aOsdSoundRegionF;

	//from left to right
    OSD_LayoutBmp(pLayout->uiLeftBg, 0);//draw left bg.bmp 6-1
    OSD_LayoutBmp(pLayout->uiMiddleBg, 0);//draw middle bg 6-2
    OSD_LayoutBmp(pLayout->uiRightBg, 0);//draw right bg.bmp 6-3
    
}// end of OSD_LayoutSoundRegionF()

/* 
 * Fuction:
 *	  sound_bmp_func_right()
 * Description:
 *      press IR Right key to call this function
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */
void sound_bmp_func_right(void)
 {
 	if (sound_level==0)	// for tab selection
	{
		page++;
#ifdef SOUND_NO_KEYPAGE     //wanghaoying 2003-9-10 11:00
	if (page>BAND_PAGE) 
		page=SRND_PAGE;
#else
	if (page > KEY_PAGE) 
		page=SRND_PAGE;
#endif
		
		
		if (page == BAND_PAGE) 
		{
			EQ_bmp_init(); 
		} 
		else 
		{
			setup_eq_display(0);//terry,2003/9/26 04:43PM
			sound_set_EQ_again();//nono 4-7-23 18:28
	} 
		ShowBmpSoundPage();
	} 
 	
	else if (sound_level == 1) 
	{
		if (page == KEY_PAGE)
		{
			if (index_y>11) 
			    return;
			
			index_y++;
			sound_sel[page]=index_y;
			sound_bmp_draw_key(BUTTON_DOWN,0);
			AUDIF_Set_Key(14-index_y);//2004AUDDRV AudioSetKey(14-index_y);

		#ifdef DVD_SETUP_REENG
			//JS	 20040820	//for setup_reengineering	//maybe 3D sound page should be rewritten
			setup_VA[SETUP_VA_KEY]=14-index_y;
			audio_key=setup_VA[SETUP_VA_KEY]-SOUND_MIN_ITEM_SEL-6;
			run_save_sel_cmd(setup_VA[SETUP_VA_KEY], SETUP_VA_KEY);
		#else
			//nono modify 4-2-7 15:38	
			SETUP_KEY=14-index_y;
			audio_key=SETUP_KEY-8;
			run_save_sel_cmd(AUDPAGE,KEYITEM);
		#endif

		} //end if (page == KEY_PAGE)
	}//end if (sound_level ==1)

 	else if (sound_level==2)	// for EQ adjustment
	{
		
		if(index_x>MAX_BAND-2) 
		    return;
		
		if(id==STR_OS_ATTRIB)	
		{
			OSD_LayoutRect(SOUND_EQ_UNSEL_BG_RECT_E4,index_x*2);//clear cursor bg rect
			index_x++;
			index_y=user_osd_set[index_x];
    			OSD_LayoutRect(SOUND_EQ_CURSOR_BG_RECT_E4,index_x*2);//draw cursor bg rect			
			show_bmp_band();
		}
	}

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);
#ifdef 	MONE_sound					
	printf("sound_bmp_func_right:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);	
#endif		

 }

/* 
 * Fuction:
 *	  sound_bmp_func_left()
 * Description:
 *      press IR Left key to call this function
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */
void sound_bmp_func_left(void)
{
	if (sound_level==0)	// for tab selection
	{
#ifdef SOUND_NO_KEYPAGE     //wanghaoying 2003-9-10 11:00
        if (page > SRND_PAGE) 
            page--; 
        else 
            page=BAND_PAGE;
#else
		if (page > SRND_PAGE) 
		    page--; 
		else 
		    page = KEY_PAGE;
#endif
		
		if (page == BAND_PAGE) 
		{	
			EQ_bmp_init(); 
		} 
		else 
		{ 
			setup_eq_display(0);//terry,2003/9/26 04:43PM
			sound_set_EQ_again();//nono 4-7-23 18:28
	} 
		ShowBmpSoundPage();
	} 
	else if (sound_level ==1) //for key page
	{
		if (page == KEY_PAGE)
		{
			if (index_y<1) 
			    return;
			index_y--;
			sound_sel[page]=index_y;
			sound_bmp_draw_key(BUTTON_DOWN,0);
			AUDIF_Set_Key(14-index_y);//2004AUDDRV AudioSetKey(14-index_y);

			#ifdef DVD_SETUP_REENG
				//JS	 20040820	//for setup_reengineering	//maybe 3D sound page should be rewritten
				setup_VA[SETUP_VA_KEY]=14-index_y;
				audio_key=setup_VA[SETUP_VA_KEY]-SOUND_MIN_ITEM_SEL-6;
				run_save_sel_cmd(setup_VA[SETUP_VA_KEY], SETUP_VA_KEY);
			#else
				//nono modify 4-2-7 15:38
				SETUP_KEY=14-index_y;
				audio_key=SETUP_KEY-8;
				run_save_sel_cmd(AUDPAGE,KEYITEM);
			#endif

		} //end if(page == KEY_PAGE)
	}//end if (sound_level ==1)
	else if (sound_level==2)	// for EQ adjustment
	{
		
		if(index_x==0) 
		    return;
		
		if(id==STR_OS_ATTRIB)	
		{
			OSD_LayoutRect(SOUND_EQ_UNSEL_BG_RECT_E4,index_x*2);//clear cursor bg rect
			index_x--;
			index_y=user_osd_set[index_x];
    			OSD_LayoutRect(SOUND_EQ_CURSOR_BG_RECT_E4,index_x*2);//draw cursor bg rect			
			show_bmp_band();
		}		
		
	}

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);
#ifdef 	MONE_sound					
	printf("sound_bmp_func_left:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);	
#endif		

}

/* 
 * Fuction:
 *	  sound_bmp_func_up()
 * Description:
 *      press IR Up key to call this function
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */
void sound_bmp_func_up(void)
{
	if (bEqDisplay) 
	    return;

	if (sound_level==0)
	{
		sound_level=1;
		if (page == KEY_PAGE)
		{
			index_y=sound_sel[page];
			sound_bmp_draw_key(BUTTON_DOWN,1);
		} 
		else
		{		
			index_y=5;
			id=sound_item[page][index_y+2];
			sound_bmp_draw_item(id, BUTTON_UP, index_y);		
		}
		sound_bmp_draw_tab();
	} 
	else if (sound_level==1) 
	{
		if (page == KEY_PAGE)
		{
			sound_bmp_draw_key(BUTTON_UP,0);
			sound_level=0;		
			// highlight
			sound_bmp_draw_tab();
		} //end if(page == KEY_PAGE)
		else
		{		
			if (index_y==0) 
			{
				index_y=5;
				sound_level=0;		
				id=sound_item[page][2];
				sound_bmp_draw_item(id,BUTTON_UP,0);
				// highlight
				sound_bmp_draw_tab();
			} 
			else 
			{			
				index_y--;
				
				id=sound_item[page][index_y+2+1];
				sound_bmp_draw_item(id, BUTTON_UP, index_y+1);
							
				id=sound_item[page][index_y+2];
				sound_bmp_draw_item(id, BUTTON_UP,index_y);
			}
		}//end else
		    
	} //end if sound_level ==1
	else 
	{	// sound_level=2, for EQ adjustment
		if(index_y<25) 
		{
			index_y++;
			user_osd_set[index_x]=index_y;
			OSD_LayoutRect(SOUND_EQ_CURSOR_BG_RECT_E4,index_x*2);//draw cursor bg rect			
			show_bmp_band();
		}
		SettingEqLevel(user_osd_set);		
	}	

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);
#ifdef 	MONE_sound					
	printf("sound_bmp_func_up:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);
#endif	

}

/* 
 * Fuction:
 *	  sound_bmp_func_down()
 * Description:
 *      press IR Down key to call this function
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */
void sound_bmp_func_down(void)
{
	if (bEqDisplay ) 
	    return;	
	
	if (sound_level==0)
	{
		sound_level=1;		
		if (page == KEY_PAGE)
		{
			index_y=sound_sel[page];
			sound_bmp_draw_key(BUTTON_DOWN,1);
		} 
		else 
		{
			index_y=0;
			sel=sound_sel[page];
			id=sound_item[page][index_y+2];
			sound_bmp_draw_item(id, BUTTON_UP, index_y);					
		}
		sound_bmp_draw_tab();
	} 

	else if (sound_level==1)
	{
		if (page != KEY_PAGE)
		{
			index_y++;
			if (index_y>5) 
			{
				index_y=0;
				sound_level=0;		
				id=sound_item[page][7];
				sound_bmp_draw_item(id, BUTTON_UP, 5);
				//highlight
				sound_bmp_draw_tab();
			} 
			else 
			{			
				id=sound_item[page][index_y+2-1];
				sound_bmp_draw_item(id, BUTTON_UP, index_y-1);
							
				id=sound_item[page][index_y+2];
				sound_bmp_draw_item(id, BUTTON_UP, index_y);
			}
		}
	} 
	else {	// sound_level=2, for EQ adjustment
		if(index_y>1) 
		{
			index_y--;
			user_osd_set[index_x]=index_y;
    			OSD_LayoutRect(SOUND_EQ_CURSOR_BG_RECT_E4,index_x*2);//draw cursor bg rect			
			show_bmp_band();
		}
		SettingEqLevel(user_osd_set);		
	}

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

#ifdef 	MONE_sound					
	printf("sound_bmp_func_down:sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);	
#endif		

}//end sound_bmp_func_down

/* 
 * Fuction:
 *	  sound_bmp_func_select()
 * Description:
 *      press IR Enter key to call this function
*
 *CREATOR: feeling
  *DATE: 2004-11-22
 */
void sound_bmp_func_select(void)
{
    if (bEqDisplay) 
        return;
	
	if (sound_level==0)
	{
		if (page == KEY_PAGE) 
		    sound_bmp_func_down();
		
	} 
	else if (sound_level==1)
	{	
		UINT8 old_sel=sound_sel[page];
		
		if (page == KEY_PAGE)
		{
			sound_level=0;
			sound_bmp_draw_tab();
			sound_bmp_draw_key(BUTTON_UP,1);
            		OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);
			return;
		}
		
		sound_sel[page]=index_y+2;
		sel=sound_sel[page];
		
		// disable old selected item	
		id=sound_item[page][old_sel];
		sound_bmp_draw_item(id,BUTTON_UP,old_sel-2);
		
		// enable new selected item
		id=sound_item[page][sel];
		sound_bmp_draw_item(id,BUTTON_DOWN,index_y);
		
		if (page == SRND_PAGE)	// in surround page
		{
			AUDIF_Set_Surround(sel-2);//2004AUDDRV AudioSetSurround(sel-2);			
			if (sound_sel[1]!=2) 
			{				
				sound_sel[1]=2;
				memcpyS(&RegionValStr[BAND_R], &music_osd_set[sound_sel[1]-2], MAX_BAND);
				osd_print_eq_setting(BAND_R, 0xff);
				sound_set_EQ_again();  
				
			} 
			else 
			{
				if ((sel-2)!=0) //Surround is open, so we should set EQ to standard mode
					AUDIF_Set_EQType(0);//2004AUDDRV AudioSetEQType(0);
			}
		} //end if (page == SRND_PAGE)

		else 
		{	// in EQ page
			if(id!=STR_OS_USER) 
			{
                		sound_func_set_EQ(sel);
				osd_print_eq_setting(BAND_R, 0xff);
			}
			else 
			{	
				//osd_user_init 
				{
					// cancel highlight, and move cursor to EQ chart
					const char   *str;	
				
					//unhighlight user item
					OSD_LayoutLine(SOUND_SEL_UP_LINE_E4, index_y);
	    				OSD_LayoutRect(SOUND_SEL_RECT_E4,index_y);
           				OSD_LayoutLine(SOUND_SEL_DOWN_LINE_E4, index_y);      	
           				//unhighlight user item string
           				id=sound_item[page][index_y+2];
					str=_OsdMessegeFont1[osd_font_mode][id];
		    			OSD_LayoutStr(str, SOUND_HL_ITEM_STR_E4, index_y);
		    			
		    			//sound_bmp_draw_item( id, BUTTON_DOWN, index_y);
		    			
				}
				
				OSD_LayoutRect(SOUND_EQ_CURSOR_BG_RECT_E4,0);			
						
				index_x=0;
				memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND); 
				SettingEqLevel(user_osd_set);      
				osd_print_eq_setting(BAND_R, index_x*2); 		
					      
				id=STR_OS_ATTRIB;	     		
				index_y=user_osd_set[index_x];
				sound_level=2;
			}	//end else	
			
			if (sel!=2) {
			    sound_sel[0]=2;
			}
		}//end else

	}//end else if (sound_level==1)

	else if (sound_level==2)
	{
		sound_level=1;
		ShowBmpSoundPage();

		id=sound_item[page][index_y+2];
		sound_bmp_draw_item(id, BUTTON_UP,index_y);

 	}

    OSD1000ISP_STATUS((page<<6)|(sound_level<<4)|(sound_sel[page]&0x0f), OSDIR_3D);

#ifdef 	MONE_sound
	printf("sound_level=%d, page=%d, index_y=%d, sel=%d\n",sound_level,page,index_y,sel);
#endif		
//yanlb added 2004/07/07
#ifdef REMB_3DSOUND
	run_sound_save(sound_sel);    
#endif

}
/* 
 * Fuction:
 *	  sound_bmp_draw_tab()
 * Description:
 *      draw the tab of the 3D menu,  including the strings on it.
*
 *CREATOR: feeling
  *DATE: 2004-11-17
 */
void sound_bmp_draw_tab(void)
{
   OSD_LayoutSoundRegionA();
   OSD_LayoutSoundRegionB();
   OSD_LayoutSoundRegionD();
}

/* 
 * Fuction:
 *	  sound_bmp_draw_item_cursor()
 * Description:
 *     only draw item cursor of regionE when ShowBmpSoundPage() .
 *
 * CREATOR: feeling
 * DATE: 2004-11-17
 */
void sound_bmp_draw_item_cursor(void)
{
	UINT8 uiItem;	
	for(uiItem = 0; uiItem < ITEM_NUM; uiItem++)	
	{
		if(uiItem == index_y)
		{
			if(sound_level == 0)//draw selected cursor
			{
				OSD_LayoutLine(SOUND_SEL_UP_LINE_E4, uiItem);
				OSD_LayoutRect(SOUND_SEL_RECT_E4,uiItem);
				OSD_LayoutLine(SOUND_SEL_DOWN_LINE_E4, uiItem);
  			}
			else if (sound_level == 1)//draw highlighted cursor
			{    
				OSD_LayoutLine(SOUND_CURSOR_UP_LINE_E4, uiItem);
				OSD_LayoutRect(SOUND_CURSOR_RECT_E4,uiItem);
				OSD_LayoutLine(SOUND_CURSOR_DOWN_LINE_E4, uiItem);

			}
		}//	end if(uiItem == index_y)
	}//end for(uiItem = 0; uiItem < ITEM_NUM; uiItem++)	
}//end sound_bmp_draw_item_cursor


/* 
 * Fuction:
 *	  sound_bmp_draw_item()
 * Description:
 *     redraw the item including cursor and the string, 
 *     when refresh the item when IR operation up, down,etc,.
 *
 * CREATOR: feeling
 * DATE: 2004-11-17
 */
void sound_bmp_draw_item(UINT8 id, UINT8 up_down, BYTE draw_y)
{
	BYTE color;
	const char   *str;	
	str=_OsdMessegeFont1[osd_font_mode][id];
	
	if (draw_y==(sel-2))
	{
		up_down=BUTTON_DOWN;	// keep button down
	} 

    	if (draw_y == index_y)	// draw highlighted cursor and highlighted string on it
    	{
		OSD_LayoutLine(SOUND_CURSOR_UP_LINE_E4, draw_y);
	    	OSD_LayoutRect(SOUND_CURSOR_RECT_E4,draw_y);
		OSD_LayoutLine(SOUND_CURSOR_DOWN_LINE_E4, draw_y);           
	    	OSD_LayoutStr(str, SOUND_HL_ITEM_STR_E4, draw_y);
    	} 
    	
    	else if (up_down == BUTTON_DOWN)//draw selected cursor and unhighlighted string on it
    	{    
    	   
	    	OSD_LayoutLine(SOUND_SEL_UP_LINE_E4, draw_y);
	    	OSD_LayoutRect(SOUND_SEL_RECT_E4,draw_y);
           	OSD_LayoutLine(SOUND_SEL_DOWN_LINE_E4, draw_y);           
	    	OSD_LayoutStr(str, SOUND_HL_ITEM_STR_E4, draw_y);
    	}
   
    	else//clear cursor and draw unhighted string
    	{    
	    	OSD_LayoutRect(SOUND_UNSEL_RECT_E4, draw_y);
	    	OSD_LayoutStr(str, SOUND_UNHL_ITEM_STR_E4, draw_y);
    	}
}//end sound_bmp_draw_item

/* 
 * Fuction:
 *	  show_bmp_band()
 * Description:
 *     show band string 
 *
 * CREATOR: feeling
 * DATE: 2004-11-22
 */

void show_bmp_band(void)
{
    char str[6];
    
    //OSD_LayoutRect(SOUND_EQ_BG_RECT_E1, 0);
  //  OSD_LayoutRect(SOUND_EQ_UNSEL_BG_RECT_E4,(index_x)*2);
  //  OSD_LayoutRect(SOUND_EQ_CURSOR_BG_RECT_E4,index_x*2);//draw cursor bg rect			

    memcpyS(&RegionValStr[BAND_R], user_osd_set, MAX_BAND);
    osd_print_eq_setting(BAND_R, index_x*2);


	//draw popup string
    if ((index_y-13)<-9)
        psprintf(str,"%d DB", (index_y-13));
    else if ((index_y-13)<0)
        psprintf(str,"%d DB ", (index_y-13));		
    else if ((index_y-13)>9)
        psprintf(str," %d DB", (index_y-13));
    else
        psprintf(str," %d DB ", (index_y-13));
		
	OSD_LayoutRect(SOUND_EQ_POPUP_BG_RECT_E4, 0);
	OSD_LayoutStr(str, SOUND_EQ_STR_E4,0);
}

/* 
 * Fuction:
 *	  EQ_bmp_init()
 * Description:
 *     init eq chart.
 *
 * CREATOR: feeling
 * DATE: 2004-11-22
 */

void EQ_bmp_init(void)
{
	int	i;
	
	//current is test
	for(i=0;i<13;i++)
		bEqEnergyMax[i]=0;

	unEqMaxRef=0;
	setup_eq_display(0xf);//nono 2003-10-22 15:14 change for new dsp code.
    }		

/* 
 * Fuction:
 *	  sound_bmp_draw_key()
 * Description:
 *    draw the key page , including strings,lines and cursor
 *
 * CREATOR: feeling
 * DATE: 2004-11-22
 */

void sound_bmp_draw_key(UINT8 up_down, UINT8 refresh)
{
    	BYTE buf[10];
	UINT8 uiCursorIndex, uiIndex;
    	const char *const key_n_num[] = {"-6","-4","-2"};
    	const char *const key_p_num[]={"0","2","4","6"};
        
    	if (up_down) 
	{
        	uiCursorIndex = SOUND_SLIDE_ARROW_CURSOR_BMP_E3;
    	} 
    	else
	{
        	uiCursorIndex = SOUND_SLIDE_ARROW_SELECTED_BMP_E3;
    	}
	
    	if (refresh) 
	{
		//draw b on the left of the scale
		psprintf(buf,"%s", Ch_dkey);
		OSD_LayoutStr(buf, SOUND_SCALE_KEY_STR_E3,0);

		//draw # on the right of the scale
		psprintf(buf,"%s", Ch_ukey);
              OSD_LayoutStr(buf, SOUND_SCALE_KEY_STR_E3,1);

		//draw horizontal line
		OSD_LayoutLine(SOUND_SCALE_LINE_E3,0);

		//draw the negtive num on the scale
		for(uiIndex = 0; uiIndex < 3; uiIndex++)
		{
			OSD_LayoutStr(key_n_num[uiIndex],SOUND_SCALE_N_NUM_STR_E3,uiIndex);
		}

		//draw the positive num on the scale
		for(uiIndex = 0; uiIndex < 4; uiIndex++)
		{
			OSD_LayoutStr(key_p_num[uiIndex],SOUND_SCALE_P_NUM_STR_E3,uiIndex);

		}
		
		//draw the -6, 6 scale line
		for(uiIndex = 0; uiIndex < 2; uiIndex++) 
		{
			OSD_LayoutLine(SOUND_SCALE_N6_LINE_E3, uiIndex);
		}	

		//draw the -4,-2, 0, 6 scale line
		for(uiIndex = 0; uiIndex < 5; uiIndex++) 
		{
			OSD_LayoutLine(SOUND_SCALE_N4_LINE_E3, uiIndex);
		}	

		//draw the scale line between -6 and -4
		for(uiIndex = 0; uiIndex < 6; uiIndex++)
		{
			OSD_LayoutLine(SOUND_SCALE_N6_N4_LINE_E3, uiIndex);
		}
    	} //end if refresh
    	else 
	{
		OSD_LayoutRect(SOUND_KEY_BG_RECT_E3, 0);//clear prev cursor
    	} //end if refresh
	
    // draw  selection cursor
      OSD_LayoutBmp(uiCursorIndex, sound_sel[page]);
}

#endif//OSD_BMP_SOUND

#endif//REMB_3DSOUND

