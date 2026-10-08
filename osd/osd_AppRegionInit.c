#include "osd_AppAPI.h"

#ifdef NEW_OSD_DRIVER
#include "global.h"
#include "osd_api.h"
#include "osd_AppRegionStruct.inc"

#ifdef SUPPORT_TELETEXT
#include "kernel.h"  //tcf 2005-11-2 13:07
#endif
#ifdef NEWSTYLE_WINDOW      //xiongyuyue
    #include "kernel.h"
    #include "osd_arc.h"
#elif defined(SETUP_ADJUST_LOCATION_WHEN_PAL)
    #include "kernel.h"
#endif

#ifdef SUPPORT_DISPLAY_MENU
#include "setup_def.h"
#endif

#if defined(ALCO_MODIFY_PAL_OSD)||defined(SETUP_PAL_ADJUST_IN_INDIGO_UI)
#include "vpp.h"
#endif

#ifndef OSD_APP_DEBUG
    #define osdbuf              linebuf
    #define osd_putc(c)         ((void) 0)
    #define osd_puts(s)         ((void) 0)
    #define osd_printf(s...)    ((void) 0)

    #undef  printf
    #undef  print_block
    #define printf(f, a...)     ((void) 0)
    #define print_block(x,y)    ((void) 0)

#else
    UINT8 osdbuf[100];
    #define osd_putc            putc_w
    #define osd_puts            puts_w
    #define osd_printf          printf_w

#endif

#ifdef SUPPORT_MOVE_SUBTITLE_BY_PRO_KEY   ///YANGLI ADD FOR MOVE SUBTITLE FOR 16:9,2005-11-28 11:24
extern int move_region_sub_flag;
#endif


#ifdef  NEW_STYLE_SETUP
    #define SETUP_REGION    1
#else
    #define SETUP_REGION    0
#endif


/************************************************************
osd_init
************************************************************/
void    osd_init(void)
{
    osd_puts("osd_init()\n");
    osd_init_regions( sizeof(osd_hdr_0)/sizeof(osd_hdr_0[0]), (_t_osd_hdr *)&osd_hdr_0);
	
#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
   // reset the palette of region0 for supporting  2 color under SDRAM 16 mode.
    SetOsdCol(0, 0, 0,  __palette4F(150,210, 141, 0xe0));
    SetOsdCol(0, 0, 1, __palette4F(  243, 243, 243,0xff));
#endif

#ifdef INDIGO_STYLE_OSDUI
    SetOsdCol(0,0, 0,0x247B46ff);//set display bg color to index_1 (rgb:( 36, 123, 70))
    SetOsdCol(0,0,15,0xffffff00);
#endif

#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-22 13:17
    SetOsdCol(2,2,0,0x1e1e1e00);//region 2 transent.
    SetOsdCol(2,2,10,0x32323290);//REGION2 10 is black. Be same with REIGON1 black color.
    #ifdef NINTAUS_OSD_STR    //2004-2-17 01:31’≈”ÓM
    SetOsdCol(2,2,7,0xffffffff);
    #else
    SetOsdCol(2,2,7, 0xa22c8eff);//REGION2 7 is yellow. Be same with REGION1 yellow color. zhaoyanhua add 2003-12-24 11:07
    #endif//SetOsdCol(2,2,7,0x1e1e1ea0);
#endif//end DIV_GOTO_DISPLAY
#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_0)/sizeof(osd_hdr_0[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_0)/sizeof(osd_hdr_0[0]), 2);		
#endif
}


/************************************************************
nodisc OSD init
************************************************************/

#ifdef NODISC_SHOW_IN_DIFF_REGION
void nodisc_osd_init(void)
{
   #if 0//def ALCO_MODIFY_PAL_OSD //05/01/03 mark!
   if(old_vppsetup_tv_system == 1)//PAL 
    osd_init_regions( 2, (_t_osd_hdr *)&osd_hdr_0n_pal); 
   #endif
   osd_init_regions( 2, (_t_osd_hdr *)&osd_hdr_0n); 

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(2, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(2, 2);
#endif
   
}
#endif

/************************************************************
Program OSD
************************************************************/
void osd_init_prog(void)
{
    osd_puts("osd_init_prog()\n");
    osd_init_regions( sizeof(osd_hdr_prog)/sizeof(osd_hdr_prog[0]), (_t_osd_hdr *)&osd_hdr_prog);

#ifdef INDIGO_STYLE_OSDUI
    SetOsdCol(0,0, 0,0x247B46ff);//set display bg color to index_1 (rgb:( 36, 123, 70))
    SetOsdCol(0,0,15,0xffffff00);
#endif
	

#ifdef CD_PLAYER        //liweihua add 2003-9-11
if(cd_type_loaded == CDDA)
    {
        SetOsdCol(0,0,0,0x1e1e1e00);
        SetOsdCol(0,0,5,__palette4F(128,64,255,0xff));
        SetOsdCol(0,0,8,__palette4F(128,255,0,0xff));
        SetOsdCol(0,0,9,__palette4F(128,255,0,0xff));
    }
#endif

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_prog)/sizeof(osd_hdr_prog[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_prog)/sizeof(osd_hdr_prog[0]), 2);	
#endif

}
/************************************************************
Password OSD - OP PASSWORD CHECK UI
************************************************************/
#ifdef ORITRON_TRAY_PASSWORD//libing 2005-4-25 10:06

void osd_init_tray_password(void)
{
	printf("init OP PASSWORD osd \n");
	osd_init_regions( sizeof(osd_hdr_op_psd)/sizeof(osd_hdr_op_psd[0]), (_t_osd_hdr *)&osd_hdr_op_psd);
	/*__osd_init();

	header_id = SETUP_HEADER;
	region[0].osd_w = 14*8*2;
	region[0].osd_h = OSD_FONT_HEIGHT+14;
	osd_create_region1(&region[0], 36, 40, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);

	osd_active_regions=1;
	//osd_init__();
	ENABLE_OSD();*/		

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_op_psd)/sizeof(osd_hdr_op_psd[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_op_psd)/sizeof(osd_hdr_op_psd[0]), 2);
#endif

}
#endif

/************************************************************
Music OSD - 3D Sound
************************************************************/
void osd_init_music(void)
{
    osd_puts("osd_init_music\n");
    osd_init_regions( sizeof(osd_hdr_music)/sizeof(osd_hdr_music[0]), (_t_osd_hdr *)&osd_hdr_music);

#ifdef INDIGO_STYLE_OSDUI
    SetOsdCol(0,0, 0,0x247B46ff);//set display bg color to index_1 (rgb:( 36, 123, 70))
    SetOsdCol(0,0,15,0xffffff00);
#endif
	
#ifdef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-22 13:17
    SetOsdCol(2,2,0,0x1e1e1e00);//region 2 transent.
    SetOsdCol(2,2,10,0x1e1e1ee0);
#endif//end DIV_GOTO_DISPLAY

#ifdef CD_PLAYER    //liweihua add 2003-9-11
    if(cd_type_loaded == CDDA)
    {
        SetOsdCol(0,1,0,0x1e1e1e00);
        SetOsdCol(1,1,3,__palette4F(128,255,0,0xff));
        SetOsdCol(0,0,5,__palette4F(128,64,255,0xff));
        SetOsdCol(0,0,8,__palette4F(128,255,0,0xff));
        SetOsdCol(0,0,9,__palette4F(128,255,0,0xff));
    }
#endif
#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_music)/sizeof(osd_hdr_music[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_music)/sizeof(osd_hdr_music[0]), 2);	
#endif
}


/************************************************************
Media Switch OSD
************************************************************/
#ifdef DIRECT_ACCESS_MEDIA//added by wangwei, 2006-4-12 11:02
void osd_init_media_switch_gui(void)
{
    osd_init_regions( sizeof(osd_hdr_SwitchMedia)/sizeof(osd_hdr_SwitchMedia[0]), (_t_osd_hdr *)&osd_hdr_SwitchMedia);
    
    #ifdef INDIGO_STYLE_OSDUI
    SetOsdCol(3, 3, 15, CLUTE_TRANS);
    #endif//INDIGO_STYLE_OSDUI

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_SwitchMedia)/sizeof(osd_hdr_SwitchMedia[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_SwitchMedia)/sizeof(osd_hdr_SwitchMedia[0]), 2);		
#endif
    
}
#endif//DIRECT_ACCESS_MEDIA


/************************************************************
PLAYMODE OSD - PLAYMODE MENU
************************************************************/
#ifdef OP_PLAYMODE//libing
void 
osd_init_menu(void)//libing
{
	printf("init OP PLAYMODE osd \n");
	//osd_puts("osd_init_menu\n");
	osd_init_regions( sizeof(osd_hdr_menu)/sizeof(osd_hdr_menu[0]), (_t_osd_hdr *)&osd_hdr_menu);
	SetOsdCol(3,3,0,__palette4F(  38,181, 49, 0xbf));//(G,B,R,A)

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_menu)/sizeof(osd_hdr_menu[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_menu)/sizeof(osd_hdr_menu[0]), 2);		
#endif
    
}
#endif//OP_PLAYMODE
/************************************************************
OP_REGION_OSD//libing
************************************************************/
#ifdef SUPPORT_OP_REGION_UI
void 
Osd_Init_Op_Region()
{
	osd_init_regions( sizeof(osd_hdr_region_code)/sizeof(osd_hdr_region_code[0]),(_t_osd_hdr *)&osd_hdr_region_code );

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_region_code)/sizeof(osd_hdr_region_code[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_region_code)/sizeof(osd_hdr_region_code[0]), 2);
#endif

}
#endif

/************************************************************
OP_SW_Version_OSD//libing
************************************************************/
#ifdef SUPPORT_OP_SW_VERSION_UI//libing 2005-11-3 14:43
void 
Osd_Init_SW_Version()
{
	osd_init_regions( sizeof(osd_hdr_op_psd)/sizeof(osd_hdr_op_psd[0]), (_t_osd_hdr *)&osd_hdr_op_psd);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_op_psd)/sizeof(osd_hdr_op_psd[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_op_psd)/sizeof(osd_hdr_op_psd[0]), 2);
#endif

}
#endif


#ifdef NEW_STYLE_SETUP
/************************************************************
Setup for NEW_STYLE_SETUP
zhaoyanhua add this function to set NEW osd region for NEW_STYLE SETUP. 3-7-14 17:35
************************************************************/
void    osd_init_hand_ICON_for_NTSC(void)//NTSC
{
    osd_puts("osd_init_hand_ICON\n");
    __osd_init();

    //setup menu
    header_id = SETUP_HEADER;
    region[1].osd_w = 38*8;
    region[1].osd_h = 11*SETUP_BTN_HEIGHT;
    osd_create_region1(1, 26, 62, NULL,OSD_FORMAT_16COLOR, OSD_INTERLACED);//60//54
    SetOsdCol(1,1,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41

    //region 0
    header_id = SETUP_HEADER;
    region[0].osd_w = 160;
    region[0].osd_h = 76;
    osd_create_region1(0, 130,  24, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);
    SetOsdCol(0,0,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    osd_tog_region(0,OSD_OFF);

    osd_active_regions = 2;
    osd_init__();

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);		
#endif

    
}

void    osd_init_hand_ICON_for_PAL(void)//for PAL
{
    __osd_init();
   
    //setup menu
    header_id = SETUP_HEADER;
    region[1].osd_w = 38*8;
    region[1].osd_h = 11*SETUP_BTN_HEIGHT;

    osd_create_region1(1, 26, 78-2-2, NULL,OSD_FORMAT_16COLOR, OSD_INTERLACED);//60//54//nono 20030804
    SetOsdCol(1,1,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41

    //region 0
    header_id = SETUP_HEADER;
    region[0].osd_w = 160;
    region[0].osd_h = 76;
    osd_create_region1(0, 130,  35-5, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//nono 20030804
    SetOsdCol(0,0,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    osd_tog_region(0,OSD_OFF);

    osd_active_regions = 2;
    osd_init__();

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);		
#endif

}

void osd_init_setup(void)
{
    osd_puts("osd_init_setup\n");
    __osd_init();
    
    header_id = SETUP_HEADER;
    
    region[1].osd_w = 35*8;                  //35 English Characters
    region[1].osd_h = 12*SETUP_BTN_HEIGHT;   //12 lines

    #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL
    if(tv_format==MODE_PAL)                  //lizhx       2004/05/21
        osd_create_region1(1, 45,  (23+22), NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    else
    #endif
        osd_create_region1(1, 45,  23, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
        
    SetOsdCol(1,1,0,0x1e1e1e00);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
    
    region[0].osd_w = 8;                  //35 English Characters
    region[0].osd_h = 8+4;   //12 lines
    
    #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL
    if(tv_format==MODE_PAL)                  //lizhx       2004/05/21
            osd_create_region1(0, 38,  (2+22), &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);
    else
    #endif
            osd_create_region1(0, 38,  2,&region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);
            
    osd_tog_region(0,OSD_OFF);
    
    osd_active_regions = 2;

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);
#endif
    
    ENABLE_OSD();
}

#elif defined(SOFT_MENU)//Modifed by ChenZhao on 2004-9-2 14:23 WP
/************************************************************
Setup for SOFT_MENU
************************************************************/
#include "kernel.h"
#include "setup_def.h"

void osd_init_setup(void)
{
	UINT16 screen_h,screen_w;
    osd_puts("osd_init_setup\n");
    __osd_init();

    header_id = SETUP_HEADER;
    region[SETUP_REGION].osd_w = SETUP_REGION_WIDTH;    //35 English Characters
    region[SETUP_REGION].osd_h = SETUP_REGION_HEIGHT;   //12 lines
    if(getVPP_TVsystem())//(TV_FORMAT_PAL==tv_format)//Modifed by chenzhao on 2004-11-16 24:50   
    {
        screen_h=288;
        screen_w=352;
    }
    else
    {
        screen_h=240;
        screen_w=360;//Modifed by chenzhao on 2004-11-16 24:55   
    }

    osd_create_region1(SETUP_REGION,(screen_w-SETUP_REGION_WIDTH)/2,(screen_h-SETUP_REGION_HEIGHT/2)/2, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
	osd_draw_rect(0,0,SETUP_REGION_WIDTH<<1,SETUP_REGION_HEIGHT,SETUP_BGCOLOR);
    osd_active_regions = 1;

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);
#endif
    
    ENABLE_OSD();
}

#elif defined(SOFT_MENU_REENG)//added by ChenZhao on 20050504
/************************************************************
Setup for SOFT_MENU_REENG
************************************************************/
#include "kernel.h"
#include "setup_def.h"

void osd_init_setup(void)
{
	UINT16 screen_h,screen_w;
    osd_puts("osd_init_setup\n");
    __osd_init();

    header_id = SETUP_HEADER;
    region[SETUP_REGION].osd_w = ((SETUP_REGION_WIDTH+15)/16)*8;//make it to be multiple of 16 pixel.
    region[SETUP_REGION].osd_h = SETUP_REGION_HEIGHT;   //12 lines

 #ifndef EASTECH_STD_SETUP_MENU//20050809 mimitsai modify.
    if(getVPP_TVsystem())//(TV_FORMAT_PAL==tv_format)//Modifed by chenzhao on 2004-11-16 24:50   
    {
        screen_h=576;
        screen_w=704;
    }
    else
  #endif
    {
        screen_h=480;
        screen_w=720;//Modifed by chenzhao on 2004-11-16 24:55   
    }

    osd_create_region1(SETUP_REGION,(screen_w-SETUP_REGION_WIDTH)/4,(screen_h-SETUP_REGION_HEIGHT)/4, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
	osd_fill_region(SETUP_REGION,SETUP_BGCOLOR);
    osd_active_regions = 1;

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);
#endif
    
    ENABLE_OSD();
}
#else
/************************************************************
Setup for Noraml Condition
************************************************************/
// for supporting 16_bit OSD
    #ifdef SUPPORT_16BIT_OSD
#include "OSD_16BDC.c"
    #endif

void osd_init_setup(void)
{
    osd_puts("osd_init_setup\n");
    __osd_init();

    #ifdef QSI_SETUP_MENU_DESIGN//liweihua 2004-7-5 9:46
    header_id = QSI_SETUP_HEADER;
    #else
    header_id = SETUP_HEADER;
    #endif
    
    #ifdef NEW_SETUP_OSD         // majinping 2002-05-02 for new setup menu
        region[0].osd_w = 37*8;                  //35 English Characters    
        region[0].osd_h = 13*SETUP_BTN_HEIGHT;   //13 lines
        #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL
            if(tv_format==MODE_PAL) 
                osd_create_region1(0, 30, (15+22), NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);    
            else
        #endif
            osd_create_region1(0, 30, 15, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);    
    #else    
        #ifdef SUPPORT_FUNCTION_MENU
            #ifdef SUPPORT_DISPLAY_MENU
                if(In_Display_Menu())
                {
                    region[0].osd_w = 20*8;                 //15 English Characters
                    region[0].osd_h = 10*SETUP_BTN_HEIGHT;   //9 lines
                    osd_create_region1(0, 38,  32, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
                }
                else
            #endif
                if(full_scrn&SETUP_PLUS)
                {
                    region[0].osd_w = 32*8;                 //32 English Characters
                    region[0].osd_h = 6*SETUP_BTN_HEIGHT;   //5 lines
                    osd_create_region1(0, 38,  32, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
                }
                else
                {
        #endif  // SUPPORT_FUNCTION_MENU
        
        /*
                    region[0].osd_w = 35*8;                  //35 English Characters
                    region[0].osd_h = 12*SETUP_BTN_HEIGHT;   //12 lines
                
                    #ifdef SETUP_ADJUST_LOCATION_WHEN_PAL
                        if(tv_format==MODE_PAL)                  //lizhx       2004/05/21
                            osd_create_region1(0, 38,  (24+22), NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
                        else
                    #endif
                        osd_create_region1(0, 38,  24, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
        */
        #if defined(ALCO_MODIFY_PAL_OSD)||defined(SETUP_PAL_ADJUST_IN_INDIGO_UI) // lxg 2006-8-11 02:09  Add for auto adjust setup position when set to PAL ,with INDIGO_STYLE_OSDUI
        if(getVPP_TVsystem() == 1)
            osd_init_regions( sizeof(osd_setup_pal)/sizeof(osd_setup_pal[0]), (_t_osd_hdr *)&osd_setup_pal);
        else
        #endif        
        osd_init_regions( sizeof(osd_setup)/sizeof(osd_setup[0]), (_t_osd_hdr *)&osd_setup);
                
        #ifdef SUPPORT_FUNCTION_MENU
                }
        #endif //end #ifdef SUPPORT_FUNCTION_MENU
    #endif 

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_setup)/sizeof(osd_setup[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_setup)/sizeof(osd_setup[0]), 2);
#endif

    osd_active_regions = 1;
    ENABLE_OSD();
}
#endif //end NEW_STYLE_SETUP



/************************************************************
Media Switch GUI for FAT
************************************************************/
#if defined(FAT_Write_UI)||defined(FILE_MODE_WRITE)//sunzhh 20041120
void osd_init_MediaswitchGUI(void)
{   
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_MediaswitchGUI)/sizeof(osd_MediaswitchGUI[0]), (_t_osd_hdr *)&osd_MediaswitchGUI);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_MediaswitchGUI)/sizeof(osd_MediaswitchGUI[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_MediaswitchGUI)/sizeof(osd_MediaswitchGUI[0]), 2);		
#endif

}
#endif//#if defined(FAT_Write_UI)//sunzhh 20041120


/************************************************************
Periph GUI for FAT
************************************************************/
#if defined(CF_CARD_WRITE)||defined(FAT_Write_UI)||defined(FILE_MODE_WRITE)//liweihua add 2003-10-30 9:15
void osd_init_periphGUI(void)
{
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_periphGUI)/sizeof(osd_periphGUI[0]), (_t_osd_hdr *)&osd_periphGUI);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_periphGUI)/sizeof(osd_periphGUI[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_periphGUI)/sizeof(osd_periphGUI[0]), 2);
#endif

}
#endif


/************************************************************
ID3
************************************************************/
#ifdef SUPPORT_OSDID3//liweihua 2003-12-28
void osd_init_OSDID3(void)
{
    osd_puts("osd_init_OSDID3\n");
    osd_init_regions( sizeof(osd_OSDID3)/sizeof(osd_OSDID3[0]), (_t_osd_hdr *)&osd_OSDID3);
    SetOsdCol(3,3,0,__palette4F(85,125, 0, 0x80));
    SetOsdCol(3,3,2,__palette4F(255, 132, 255, 0xff));

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_OSDID3)/sizeof(osd_OSDID3[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_OSDID3)/sizeof(osd_OSDID3[0]), 2);
#endif
}
#endif


/************************************************************
CD/CARD/USB Switch
************************************************************/
#ifdef SWITCH_CD_CARD_USB //liweihua mod 2004-6-8 14:45
void osd_init_switchGUI(void)
{
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_switchGUI)/sizeof(osd_switchGUI[0]), (_t_osd_hdr *)&osd_switchGUI);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_switchGUI)/sizeof(osd_switchGUI[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_switchGUI)/sizeof(osd_switchGUI[0]), 2);
#endif

}
#endif


/************************************************************
MP4 Subtitle
************************************************************/
#ifdef SUPPORT_OSDSRT
#include "vpp.h"
#include "Subtitle.h"

extern void osd_move_subtitle_region()     // 2005/07/12 yltseng, 2005/10/28 yltseng Call osd_set_original_region_position to change region when PAL/NTSC switch
{
    if( IS_EXT_SUP_INITIALIZED() )
    {
        coordinate pos;
        pos.x = 26;
        pos.y = getVPP_TVsystem() ? OSD_SRT_REGION_PAL_Y : OSD_SRT_REGION_NTSC_Y;
        osd_set_original_region_position( 3, &pos );
    }
}

void osd_init_OSDSRT(void)
{   // 2005/07/12 yltseng    
    extern UINT16	IsOtherStatePlayMode(void);

    if( (full_scrn==0)||(full_scrn&GOTO)||(full_scrn&MARK)||(full_scrn&SCORE)////nono 4-7-26 10:37;
        ||(full_scrn&PROGRAM) ||(full_scrn&SOUND))//feeling 05-01-06
    #if defined(DISP_REGION_BOTTOM) && defined(SUPPORT_FILE_SYSTEM_MODE)
    	if(IsOtherStatePlayMode())
    #endif
        {
        osd_puts("osd_init_OSDSRT\n");
        osd_init_regions( sizeof(osd_OSDSRT)/sizeof(osd_OSDSRT[0]), (_t_osd_hdr *)&osd_OSDSRT);
            osd_move_subtitle_region();
        
        #ifdef SUPPORT_MOVE_SUBTITLE_BY_PRO_KEY   ///YANGLI ADD FOR MOVE SUBTITLE FOR 16:9,2005-11-28 11:24
           if( IS_EXT_SUP_INITIALIZED()&&move_region_sub_flag)
            {
            	if( getVPP_TVsystem() )
            		osd_set_region_position( 3, 26, 100 );
            	else
            		osd_set_region_position( 3, 26, 80 );
        	}
        #endif
        
            SetOsdCol(3,3,0,__palette4F(255, 132, 255, 0));//background color is transparent
            #ifndef ALCO_DVD_UI//shenyj add 2006-9-7 08:47œ¬ŒÁ
            SetOsdCol(3,3,2,__palette4F(255, 132, 255, 0xff));//font color is near to white
            #endif
		#ifdef INDIGO_STYLE_OSDUI
		    SetOsdCol(0,0, 0,0x247B46ff);//set display bg color to index_1 (rgb:( 36, 123, 70))
		    SetOsdCol(0,0,15,0xffffff00);
		#endif 
        }

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_OSDSRT)/sizeof(osd_OSDSRT[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_OSDSRT)/sizeof(osd_OSDSRT[0]), 2);
#endif
	
}
#endif  //SUPPORT_OSDSRT


/************************************************************
Record Key
*   when the disc which has been recorded is distinguished,
*   before resume play ,show message.
************************************************************/
#ifdef  RECORD_KEY//zhaoyanhua add 
void osd_init_record()
{
    osd_puts("osd_init_record()\n");
    osd_init_regions( sizeof(osd_hdr_record)/sizeof(osd_hdr_record[0]), (_t_osd_hdr *)&osd_hdr_record);
    SetOsdCol(0,0,0,0x1e1e1ef0);//3-11-21 9:25’≈”ÓP

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_record)/sizeof(osd_hdr_record[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_record)/sizeof(osd_hdr_record[0]), 2);	
#endif

}   
#endif


/************************************************************
Double Title
************************************************************/
#ifdef DOUBLE_TITLE //susu add 2003-8-20 14:43
void osd_init_double_title(void)
{
    osd_puts("osd_init_double_title\n");
    osd_init_regions( sizeof(osd_hdr_double_title)/sizeof(osd_hdr_double_title[0]), (_t_osd_hdr *)&osd_hdr_double_title);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_double_title)/sizeof(osd_hdr_double_title[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_double_title)/sizeof(osd_hdr_double_title[0]), 2);		
#endif
    
}
#endif


/************************************************************
NES OSD
************************************************************/
#ifndef NES_USE_GRAPH
    #ifdef OSD_PAL_RGB_16b                
void osd_init_NES(int x,int y,int w,int h, const UINT16 *pPalette)
    #else
void osd_init_NES(int x,int y,int w,int h, const UINT32 *pPalette)
    #endif
{    
    osd_puts("osd_init_nes\n");
    __osd_init();

    header_id = NES_HEADER;
    osd__pal[header_id] = pPalette;

#ifdef OSD_SUPPORT_256_COLOR 
    //setup region 1    
    region[1].osd_w = w;        
    region[1].osd_h = h;    
    osd_create_region1(1, x, y, NULL, OSD_FORMAT_256COLOR, OSD_NONINTERLACED);
    
    //setup region 0    
    region[0].osd_w = w;        
    region[0].osd_h = h;    
    osd_create_region1(0, x, y, &region[1], OSD_FORMAT_256COLOR, OSD_NONINTERLACED);
#endif	// #ifdef OSD_SUPPORT_256_COLOR

    osd_active_regions = 2;

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);	
#endif

    ENABLE_OSD();    
}
#endif


/************************************************************
CD Player
************************************************************/
#ifdef CD_PLAYER//liweihua 2003-9-3
void osd_init_cdplayer(void)
{
    __osd_init();

#ifdef OSD_SUPPORT_256_COLOR
    #ifdef VIRTUAL_KEYBOARD
    header_id = KEYBOARD_HEADER;
    region[4].osd_w = 64*3;
    region[4].osd_h = (OSD_FONT_HEIGHT+8)*6;
    osd_create_region1(4, 256, 168, NULL,OSD_FORMAT_256COLOR,OSD_INTERLACED);
    #endif
#endif	// #ifdef OSD_SUPPORT_256_COLOR
    
    //setup region 2(for cd player setting)
    header_id = EQ_HEADER;
    region[3].osd_w = 38*4-44;
    region[3].osd_h = (OSD_FONT_HEIGHT+8)*6;
    osd_create_region1(3, 32+60+37,  72, &region[4],OSD_FORMAT_16COLOR,OSD_INTERLACED);

    //region2   
    header_id = NORMAL_HEADER;
    region[2].osd_w = 36*4;
    region[2].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(2, 32,  42+4, &region[3],OSD_FORMAT_4COLOR,OSD_INTERLACED);

   // setup region 1
    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(1, 32,  34, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);
    SetOsdCol(1,1,3,__palette4F(128,255,0,0xff));
        
    // setup region 0
    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(0, 24+2,  20, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);
    SetOsdCol(0,4,0,0x1e1e1e00);
    SetOsdCol(0,0,5,__palette4F(128,64,255,0xff));
    SetOsdCol(0,0,8,__palette4F(128,255,0,0xff));
    SetOsdCol(0,0,9,__palette4F(128,255,0,0xff));
    
    osd_init__();  
}
#endif


/************************************************************
Virtual Keyboard
************************************************************/
#ifdef VIRTUAL_KEYBOARD //liweihua add 03-8-15
void osd_init_keyboard(void)
{
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_keyboard)/sizeof(osd_keyboard[0]), (_t_osd_hdr *)&osd_keyboard);
    #ifdef CD_PLAYER
    SetOsdCol(4,4,0,0x1e1e1e00);
    #else
    SetOsdCol(3,3,0,0x1e1e1e00);
    #endif

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_keyboard)/sizeof(osd_keyboard[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_keyboard)/sizeof(osd_keyboard[0]), 2);		
#endif
    
}
#endif


/************************************************************
PMP UI
************************************************************/
#ifdef PMP_UI//liweihua 204-12-28
void osd_init_pmp(void)
{
	osd_puts("osd_init_pmp\n");
    osd_init_regions( sizeof(osd_pmp)/sizeof(osd_pmp[0]), (_t_osd_hdr *)&osd_pmp); 
    SetOsdCol(2,2,0,0x1e1e1e00);   

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_pmp)/sizeof(osd_pmp[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_pmp)/sizeof(osd_pmp[0]), 2);
#endif    
}
#endif


/************************************************************
Real Color Screen Saver
************************************************************/
#ifdef REALCOLOR_SCREENSAVER
void osd_init_screensaver(void)
{
    osd_puts("osd_init_key\n");
    osd_init_regions( sizeof(osd_screensaver)/sizeof(osd_screensaver[0]), (_t_osd_hdr *)&osd_screensaver);
    SetOsdCol(0,0,0,0x000ff);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_screensaver)/sizeof(osd_screensaver[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_screensaver)/sizeof(osd_screensaver[0]), 2);
#endif
    
}
#else
void osd_init_screensaver(void)
{
    //joshua, 20050823, modified osd initial function of screensaver
    osd_puts("osd_init_screensaver\n");
    osd_init_regions( sizeof(osd_screensaver)/sizeof(osd_screensaver[0]), (_t_osd_hdr *)&osd_screensaver);
    SetOsdCol(0, 0, 0,0x000000ff);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_screensaver)/sizeof(osd_screensaver[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_screensaver)/sizeof(osd_screensaver[0]), 2);
#endif
    
}
#endif



/************************************************************
Parental GUI
************************************************************/
#ifdef NEW_PARENTAL_GUI//zhaoyanhua add for BBK DVD 2003-11-28 10:49
void osd_init_parental_gui(void)
{
    osd_init_regions( sizeof(osd_hdr_parental)/sizeof(osd_hdr_parental[0]), (_t_osd_hdr *)&osd_hdr_parental);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_parental)/sizeof(osd_hdr_parental[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_parental)/sizeof(osd_hdr_parental[0]), 2);
#endif
}
#endif


#ifdef NEWSTYLE_WINDOW
    #ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW//zhaoyanhua add for BBK_DVD
/************************************************************
Init New Style Window
************************************************************/
/*
 * when draw NEW_STYLE_WINDOW, for NTSC
 */
void   osd_init_newstyle_window_NTSC(void)
{
    osd_puts("osd_init_newstyle_window\n");
    __osd_init();
    
    header_id = SETUP_HEADER;

    region[2].osd_w = 38*8;
    region[2].osd_h = OSD_FONT_HEIGHT*16-10;//374
    osd_create_region1(2, 24,  32, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm//yaowh modify 2005-11-22 16:05

    SetOsdCol(2,2,0,0x1e1e1e00);
    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;

    osd_create_region1(1, 32,  20, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm//yaowh 2005-11-22 16:06


    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(0, 26,  8, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//axel 2003/11/21 07:19pm//yaowh 2005-11-22 16:06

    osd_active_regions = 3;
    osd_init__();    

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);	
#endif
    
}

/*
 *  for PAL
 */
void   osd_init_newstyle_window_PAL(void)
{
    osd_puts("osd_init_newstyle_window\n");
    __osd_init();
    
    header_id = SETUP_HEADER;

    region[2].osd_w = 38*8;
    region[2].osd_h = OSD_FONT_HEIGHT*16-9;
    osd_create_region1(2, 24, 42+10, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm

    SetOsdCol(2,2,0,0x1e1e1e00);
    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;

    osd_create_region1(1, 32,  30+4, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm//yaowh 2005-11-22 16:07


    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1(0, 26,  16+4, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//axel 2003/11/21 07:19pm//yaowh 2005-11-22 16:07

    osd_active_regions = 3;
    osd_init__();   

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);	
#endif
    
}
    #endif//MODIFY_OSD_SHOW_NEW_STYLE_WINDOW

void    osd_init_newstyle_window(void)
{
    osd_puts("osd_init_newstyle_window\n");
    __osd_init();
    
    header_id = SETUP_HEADER;

    region[2].osd_w = 38*8;
    region[2].osd_h = OSD_FONT_HEIGHT*16-10;//374

    #ifdef BBK_DVD
    osd_create_region1(2, 24,  42-4, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm
    #else
    osd_create_region1(2, 24,  42+4, NULL,OSD_FORMAT_16COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm
    #endif    

    SetOsdCol(2,2,0,0x1e1e1e00);

    header_id = NORMAL_HEADER;
    region[1].osd_w = 36*4;
    region[1].osd_h = OSD_FONT_HEIGHT;
    
    #ifdef BBK_DVD
    osd_create_region1(1, 32,  30-4, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm    
    #else
    osd_create_region1(1, 32,  30+4, &region[2],OSD_FORMAT_4COLOR,OSD_INTERLACED);//axel 2003/11/21 07:19pm    
    #endif

    header_id = SETUP_HEADER;
    region[0].osd_w = 38*8;
    region[0].osd_h = OSD_FONT_HEIGHT;
    
    #ifdef BBK_DVD
    osd_create_region1(0, 26,  16-4, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//axel 2003/11/21 07:19pm
    #else
    osd_create_region1(0, 26,  16+4, &region[1], OSD_FORMAT_16COLOR, OSD_INTERLACED);//axel 2003/11/21 07:19pm
    #endif

    osd_active_regions = 3;
    osd_init__();

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(osd_active_regions, 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(osd_active_regions, 2);	
#endif
    
}
#endif


/************************************************************
Repeat Read
************************************************************/
#ifdef SUPPORT_REP_READ
void osd_init_rep_reading(void)
{
    osd_init_regions(sizeof(osd_hdr_rep_read)/sizeof(osd_hdr_rep_read[0]), (_t_osd_hdr *)&osd_hdr_rep_read);

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_hdr_rep_read)/sizeof(osd_hdr_rep_read[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_hdr_rep_read)/sizeof(osd_hdr_rep_read[0]), 2);	
#endif

} 
#endif

#ifdef DVB1000_OSD_MENU
void osd_init_dvb_menu(void)
{
    osd_init_regions(sizeof(osd_hdr_dvb_menu)/sizeof(osd_hdr_dvb_menu[0]), (_t_osd_hdr *)&osd_hdr_dvb_menu);
    #ifdef DVB_OSD_MENU_VER1
    SetOsdCol(0, 0, 14, 0x0080fff0);
    SetOsdCol(0, 0, 8,  0xC8C8C8ff);
    SetOsdCol(0, 0, 0, 0x1e1e1e00);
    #else
    SetOsdCol(0, 0, 0, 0x1e1e1e00); //TRANS_CLR
    SetOsdCol(0, 0, 6, 0x98d28de0); //LIGHT BLUE
    SetOsdCol(0, 0, 8, 0xc0c0c0e0);//Gray CLR
    //SetOsdCol(0, 0, 8, 0xc8f589e0);//Gray CLR for Bg
    SetOsdCol(0, 0, 9, 0x808080ff);
    SetOsdCol(0, 0, 10, 0xC8C8C8ff); //List Bg
    
    #endif
    osd_tog_region(SETUP_REGION,OSD_ON);
} 
#endif

#ifdef SUPPORT_TELETEXT
extern int ttx_page_screen_opacity;
void osd_init_dvb_ttx_menu(void)
{
	//printf("init DVB teletext osd \n");
	
	if(getVPP_TVsystem() )//tcf added 2005-11-23 13:16
    	osd_init_regions(sizeof(osd_hdr_dvb_ttx_menu_pal)/sizeof(osd_hdr_dvb_ttx_menu_pal[0]), (_t_osd_hdr *)&osd_hdr_dvb_ttx_menu_pal);
    else	
   		osd_init_regions(sizeof(osd_hdr_dvb_ttx_menu_ntsc)/sizeof(osd_hdr_dvb_ttx_menu_ntsc[0]), (_t_osd_hdr *)&osd_hdr_dvb_ttx_menu_ntsc);
    if(ttx_page_screen_opacity==0)
    	SetOsdCol(0, 0, 0, CLUTE_TRANS);
} 
#endif



#if defined(DVB_DVD_8202)&&defined(SUPPORT_SUBTITLE)
void osd_init_dvb_subtitle_Regions(UINT8 uRegionNumber)
{
    osd_init_regions(uRegionNumber, (_t_osd_hdr *)&osd_hdr_dvb_subtitle_regions);
    
    //SetOsdCol(0, 0, 0, 0x00000000); 
    //SetOsdCol(1, 1, 0, 0x00000000);
}

void osd_init_dvb_subtitle_menu(void)
{
    int i=0/*,j=0*/;
    int yy=0;
    UINT8 *pp;
    UINT8  *pTopLine, *pBtmLine;

    osd_init_regions(sizeof(osd_hdr_dvb_subtitle_menu)/sizeof(osd_hdr_dvb_subtitle_menu[0]), (_t_osd_hdr *)&osd_hdr_dvb_subtitle_menu);

    pTopLine = (UINT8 *)get_osdbuf_region_ptr(0,0); 
    pBtmLine = (UINT8 *)get_osdbuf_region_ptr(0,1);

    for(i=SUBTITLE_REGION_Y;i<SUBTITLE_REGION_H;i++)
    {
            yy = (p_scan) ? i: i>>1;
            pp = (i&1) ? pBtmLine : pTopLine;

            if(p_scan)
             memset(pp+i*SUBTITLE_REGION_W/2, 0,SUBTITLE_REGION_W/2);
            else
             memset(pp+(i/2)*SUBTITLE_REGION_W/2, 0,SUBTITLE_REGION_W/2);
    }    

    osd_tog_region(0, OSD_ON);
    SetOsdCol(0, 0, 0, 0x00000000);
} 
#endif//SUPPORT_SUBTITLE

#ifdef GPS_KEYBOARD
void osd_init_gps_keyboard(void)
{
    osd_puts("osd_init_gps_keyboard\n");//frank.huang 050826
    //osd_init_regions( sizeof(osd_gps_keyboard)/sizeof(osd_gps_keyboard[0]), (_t_osd_hdr *)&osd_gps_keyboard); 
	osd_init_regions( sizeof(osd_gps_keyboard)/sizeof(osd_gps_keyboard[0]), (_t_osd_hdr *)&osd_gps_keyboard); 

	SetOsdCol (3,3,0,__palette4F(0xff,0xff,0xff,0x00)); 
	SetOsdCol (3,3,1,__palette4F(0xff,0xff,0xff,0xff)); 
	SetOsdCol (3,3,2,__palette4F(0x38,0x3a,0x37,0xff)); 
	SetOsdCol (3,3,3,__palette4F(0x70,0x72,0x6f,0xff)); 
	SetOsdCol (3,3,4,__palette4F(0xf2,0xf3,0xf1,0xff)); 
	SetOsdCol (3,3,5,__palette4F(0xb6,0xb6,0xb4,0xff)); 
	SetOsdCol (3,3,6,__palette4F(0xe8,0xd4,0xea,0xff)); 
	SetOsdCol (3,3,7,__palette4F(0x83,0x39,0x90,0xff)); 
	SetOsdCol (3,3,8,__palette4F(0x9a,0x94,0x9b,0xe0)); 
	SetOsdCol (3,3,9,__palette4F(0xd8,0x41,0xf6,0xff)); 
    SetOsdCol(3,3,10,__palette4F(0xb1,0x36,0xc9,0xff));
    SetOsdCol(3,3,11,__palette4F(0xec,0xa9,0xf8,0xff)); 
    SetOsdCol(3,3,12,__palette4F(0xec,0xa9,0xf9,0xff)); 
    SetOsdCol(3,3,13,__palette4F(0x47,0x47,0x47,0xff)); 
    SetOsdCol(3,3,14,__palette4F(0x02,0x02,0xfc,0xff));
    //SetOsdCol(3,3,15,__palette4F(0x02,0x02,0xfc,0xe0));
    
   osd_tog_region(3, OSD_ON); 

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_gps_keyboard)/sizeof(osd_gps_keyboard[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_gps_keyboard)/sizeof(osd_gps_keyboard[0]), 2);		
#endif

}

#endif
#ifdef GPS_MENU
void osd_init_gps_menu(void)
{
    osd_puts("osd_init_gps_menu\n");
    osd_init_regions( sizeof(osd_gps_menu)/sizeof(osd_gps_menu[0]), (_t_osd_hdr *)&osd_gps_menu); 

    SetOsdCol(2,2,3,__palette4F(220,220,220,0xa8)); //white,as background
    SetOsdCol(2,2,1,__palette4F( 152, 41, 212, 0xff));//orange 
    SetOsdCol(2,2,2,__palette4F(  50, 50, 50,0xff)); //black
    SetOsdCol(2,2,0,__palette4F(   100,  100, 100,  0xc8)); //gray
    
    osd_tog_region(2, OSD_ON); 

#ifdef SUPPORT_SW_OSD_SCALING
    if( GET_TV_RESOLUTION()  == HD_720 )
        osd_init_scaling(sizeof(osd_gps_menu)/sizeof(osd_gps_menu[0]), 1);	
    else if(GET_TV_RESOLUTION()  == HD_1080)
        osd_init_scaling(sizeof(osd_gps_menu)/sizeof(osd_gps_menu[0]), 2);		
#endif
    
}
#endif

#ifdef SUPPORT_DVB_GUI_NEW
/************************************************************
8202+6600 GUI(Version2 Gui with 16 color)//taolin
************************************************************/
#include "..\dvb_h\Dvb_Macro_Def.h"
#include "..\dvb_h\Dvb_menu.h"
#include "vpp.h" //for the function of getVPP_TVsystem()
void osd_init_new_dvb_menu(void)
{
	UINT16 y;
    //If TV system is Pa region y strart = DVB_MENU_REGION_START_Y_P, 
    //else region y strart = DVB_MENU_REGION_START_Y_N
   // stOSD_Header[0].y = getVPP_TVsystem() ?  DVB_MENU_REGION_START_Y_P : DVB_MENU_REGION_START_Y_N;

    //Init osd region	
    osd_init_regions(sizeof(stOSD_Header)/(sizeof(stOSD_Header[0])), (_t_osd_hdr *)&stOSD_Header);
    osd_active_regions = 1;	
    y = getVPP_TVsystem()?  DVB_MENU_REGION_START_Y_P : DVB_MENU_REGION_START_Y_N;
    osd_set_region_position(0,0,y);
}

void osd_init_new_dvb_info(void)    ////sunzhh add for Program Info display 20051027
{
	UINT16 y;
    //If TV system is Pa region y strart = DVB_MENU_REGION_START_Y_P, 
    //else region y strart = DVB_MENU_REGION_START_Y_N
   // stOSD_Header[0].y = getVPP_TVsystem() ?  DVB_MENU_REGION_START_Y_P : DVB_MENU_REGION_START_Y_N;

    //Init osd region	
    osd_init_regions(sizeof(stOSD_InfoHeader)/(sizeof(stOSD_InfoHeader[0])), (_t_osd_hdr *)&stOSD_InfoHeader);
    osd_active_regions = 1;	
    y = getVPP_TVsystem()?  DVB_MENU_REGION_START_Y_P : DVB_MENU_REGION_START_Y_N;
    osd_set_region_position(0,0,y);
}
#endif

#endif //NEW_OSD_DRIVER

#ifdef SUPPORT_SW_OSD_SCALING
//#define DEBUG_OSD_INIT_SCALING
#define osd_get_region_pointer( uiRegionIdx, uiField ) \
    (t_osdv2_header*)(get_osdbuf_baseptr() + (region[osd_display_list[uiRegionIdx]].osd_header[uiField]<< 5))

#define osd_get_region_palette_pointer( uiRegionIdx, uiField ) \
    (UINT8*)(((UINT32)osd_get_region_pointer(uiRegionIdx, uiField)) + HEADER_SIZE)
    
#define osd_get_palette_entry_size( uiRegionIdx, uiField ) \
    ((((const UINT8*) osd_get_region_pointer( uiRegionIdx, uiField ))[2] & V2_CLUT_TYPE(0x11) ) ? 4 : 2 )


int osd_init_scaling(int n,  int mode)
{
    int  uiRegionIdx, uiField;
    UINT16 osd_width, osd_high, align;
    UINT16 i, j, temp;
    UINT32 uiClutSize, uiClutCount;
    BYTE    *osdfrom    = get_osdbuf_baseptr(); 
    BYTE    *origin_osd, *scaling_osd;
    scaling_t_osd_region* scaling_region_p,  *rgnp;
    t_osd_region *region_pointer;
    t_osdv2_header *pLine;
    UINT16    linkaddr;
//	UINT16 x_divisor, x_dividend, y_divisor, y_dividend;
	
    osd_puts("osd_init_scaling()\n");

    if(osd_free == 0)
        return 0;

    DISABLE_OSD();

    rgnp = NULL;
    for(uiRegionIdx=n-1; uiRegionIdx>=0; uiRegionIdx--) {

        scaling_region_p = &scaling_region[uiRegionIdx];
        region_pointer = &region[uiRegionIdx];		

        if(mode==1) {
            scaling_region_p->ratio.x_dividend = 9;
            scaling_region_p->ratio.x_divisor = 5;
            scaling_region_p->ratio.y_dividend = 3;
            scaling_region_p->ratio.y_divisor = 2;			
        }	
        else if(mode==2) {
            scaling_region_p->ratio.x_dividend = 53;
            scaling_region_p->ratio.x_divisor = 20;
            scaling_region_p->ratio.y_dividend = 9;
            scaling_region_p->ratio.y_divisor = 4;					
        }else {      
            scaling_region_p->ratio.x_dividend = 1;
            scaling_region_p->ratio.x_divisor = 1;
            scaling_region_p->ratio.y_dividend = 2;
            scaling_region_p->ratio.y_divisor = 1;					
        }
	
        uiClutSize   = osd_get_palette_entry_size(uiRegionIdx, 0);
		
        if(region_pointer->osd_format == OSD_FORMAT_2COLOR)
            uiClutCount = 2;
        else if(region_pointer->osd_format == OSD_FORMAT_4COLOR)
            uiClutCount = 4;
        else if(region_pointer->osd_format == OSD_FORMAT_16COLOR)
            uiClutCount = 16;
        else if(region_pointer->osd_format == OSD_FORMAT_256COLOR)
            uiClutCount = 256;
        else
            uiClutCount = 0;
		

        align = (OSD_DATA_OFFSET( region_pointer->osd_format )<<5) - HEADER_SIZE - uiClutCount*uiClutSize;      
		
        for(uiField=0; uiField<2; uiField++) {		
            
            #ifdef DEBUG_OSD_INIT_SCALING            
            printf_w("osd_init_scaling in, osd_free:%x,  .......................................\n", osd_free);       
            #endif
            
            scaling_region_p->osd_header[uiField] = osd_free;
			
            origin_osd = osdfrom + (region_pointer->osd_header[uiField]<<5);
            scaling_osd = osdfrom + (scaling_region_p->osd_header[uiField]<<5);
			
            memcpy(scaling_osd ,origin_osd , (HEADER_SIZE+uiClutCount*uiClutSize));

            // modify v_size & h_size of region in mem.
            pLine = (t_osdv2_header *)scaling_osd;
            
            temp = SWAP16(pLine->h_size)*4*(scaling_region_p->ratio.x_dividend)/(scaling_region_p->ratio.x_divisor);            
            if (temp % 4 == 0)
                osd_width = temp;
            else
                osd_width = temp + (4 - (temp % 4));

            scaling_region_p->osd_w = osd_width;
            osd_width = osd_width>>2;
            wbe16( &(pLine->h_size), osd_width );			

            
            temp = SWAP16(pLine->v_size)*(scaling_region_p->ratio.y_dividend)/(scaling_region_p->ratio.y_divisor);
            osd_high = temp&(~1);
            if(p_scan)
                scaling_region_p->osd_h = osd_high;
            else
                scaling_region_p->osd_h = osd_high*2;
            wbe16( &(pLine->v_size), osd_high);

            // modify start y of region 
            temp = SWAP16(pLine->y)*(scaling_region_p->ratio.y_dividend)/(scaling_region_p->ratio.y_divisor);
            wbe16( &(pLine->y), temp);
            // modify start x of region 
            temp = SWAP16(pLine->x)*(scaling_region_p->ratio.x_dividend)/(scaling_region_p->ratio.x_divisor);
            wbe16( &(pLine->x), temp);

            #ifdef DEBUG_OSD_INIT_SCALING
            printf_w("Region:%d, scaling osd region coordinate (%x, %x) osd_width:%x, osd_high:%x\n", uiRegionIdx, SWAP16(pLine->x), SWAP16(pLine->y), osd_width, osd_high);
            t_osdv2_header * pLine0 = (t_osdv2_header *)origin_osd;
            printf_w("origin osd region coordinate (%x, %x) osd_width:%x, osd_high:%x\n", SWAP16(pLine0->x), SWAP16(pLine0->y), SWAP16(pLine0->h_size), SWAP16(pLine0->v_size));
            #endif

            //BYTE config_byte = (pLine->config0 & 0xCF) | 0x10;
            //pLine->config0 = config_byte; 
			
            scaling_osd += (HEADER_SIZE+uiClutCount*uiClutSize);			
            memset(scaling_osd, 0, align);
            scaling_osd+=align;     

            // modify link_data & link_next of region in mem.
            linkaddr = (rgnp == NULL) ? LINK_NULL : rgnp->osd_header[uiField];
            wbe16( &(pLine->link_next), linkaddr);
            osd_free = osd_free + OSD_DATA_OFFSET(region_pointer->osd_format);
            wbe16( &(pLine->link_data), osd_free);
            scaling_region_p->osd_link_data[uiField] = osd_free;

            // clear content section of scaling osd buffer 
            for (i=osd_high; i>0; i--)
            {
                for(j=0; j<osd_width; j++) ((UINT32 *)scaling_osd)[j]=0;
                //next line    
                scaling_osd+=(osd_width<<2);            
            }
             
            osd_free    = ((scaling_osd - osdfrom)+31)/32;
            
            #ifdef DEBUG_OSD_INIT_SCALING 
            printf_w("osd_init_scaling out, osd_free:%x,  .......................................\n", osd_free);   
            #endif
            
            //if on non-interface mode , display become top line= bottom line
            //if ( (bScanMode==OSD_NONINTERLACED)||p_scan )
            //we don't use OSD_NONINTERLACED varible
            if (p_scan )
            {
                scaling_region_p->osd_header[1] = scaling_region_p->osd_header[0];
                break;
            }        			
       
        }
        rgnp = &scaling_region[uiRegionIdx];

        // If origin osd region is on show, then we have to copy and scale the content of origin 
        // osd region to the corresponding scaling osd region.  by robert.chang, 2006-08-xx
        if((pLine->config0 & 0x40) == 0) {
            DrawDimension scale_section;
            scale_section.draw_start.x = 0;
            scale_section.draw_start.y = 0;        
            scale_section.draw_dimension.x_length = (region_pointer->osd_w)<<5; 
            scale_section.draw_dimension.y_length = region_pointer->osd_h;
            osd_region_scaling(uiRegionIdx, &scale_section);
        }                
        
    }
    
    SET_OSD_SCALE_BUF_FLAG(1); // when osd scaling buf is ready, then set osd_scale_buf_flag = 1.
    ENABLE_OSD(); 
    
    return 1;
}


#endif


