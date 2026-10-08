//liulifeng 2004-6-30 14:17
#include "user_init.h"

#include "global.h"
#include "avd.h"
#include "osd.h"

#include "fsNAV.h"
#include "fsGUI.h"
#include "memcfg.h"
#include "ircode.h"
#include "timer.h"
#include "kernel.h"
#include "cfont.h"

#ifdef JPG_OLD_PARSER_FLOW
    #ifdef JPG_EFFECT
    #include "jpegeffect.h"
    #endif
#else
    #include "pic_effect.h"
#endif

#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)
#include "fsGUI1.h"
#endif

#ifdef JPG_EFFECT
extern UINT16 Is_JPEG_STATE(void);

void jpeg_effect_draw_help(void)
{
#ifdef  CALL_JPGEFFECT_HELP
    UINT16 i;

    if(Is_JPEG_STATE())
    {
	#ifdef USE_TITLE_KEY_TO_CALL_JPGEFFECT_HELP
    	#ifndef MP3_LARGE_GUI
		FSGUI_ShowString(  60,  20,"PRESS  TITLE  FOR JPEG HELP", 0xc0, 0x9090);
		#else
		FSGUI_ShowString( 120,  20,"PRESS  TITLE  FOR JPEG HELP", 0xc0, 0x9090);
		#endif
	#elif defined(USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP)	
    	#ifndef MP3_LARGE_GUI
		FSGUI_ShowString(  60,  20,"PRESS PREVIEW FOR JPEG HELP", 0xc0, 0x9090);
		#else
		FSGUI_ShowString( 120,  20,"PRESS PREVIEW FOR JPEG HELP", 0xc0, 0x9090);
		#endif
	#endif

	#if !defined(MP3_LARGE_GUI)
		#ifndef AD_TCL
		for(i=60;i<280;i++)
		{
	    	FSGUI_ShowChar(0,i++,28,'-',0xc0, 0x9090);
		}
		#endif
	#endif

    }
	else
    {
	#if defined(NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)//nono 20040109
		#ifdef USE_TITLE_KEY_TO_CALL_JPGEFFECT_HELP
			#ifndef MP3_LARGE_GUI
        FSGUI_ShowString(  60,  20,"PRESS  TITLE  FOR JPEG HELP", BK_GROUNDY, BK_CRCB);
        	#else
        FSGUI_ShowString( 120,  20,"PRESS  TITLE  FOR JPEG HELP", BK_GROUNDY, BK_CRCB);
        	#endif
		#elif defined(USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP)
			#ifndef MP3_LARGE_GUI
        FSGUI_ShowString(  60,  20,"PRESS PREVIEW FOR JPEG HELP", BK_GROUNDY, BK_CRCB);
        	#else
        FSGUI_ShowString( 120,  20,"PRESS PREVIEW FOR JPEG HELP", BK_GROUNDY, BK_CRCB);
        	#endif
		#endif

		#ifndef MP3_LARGE_GUI
		for(i=60;i<280*NUMERATOE_X/DENOMINATOR_X;i++)
		{
	    	FSGUI_ShowChar(0,i++,28,'-',BK_GROUNDY,BK_CRCB);
		}
		#endif

	#else//#ifdef NEW_MP3_GUI || defined(INDIGO_STYLE_FSGUI)
		#ifdef USE_TITLE_KEY_TO_CALL_JPGEFFECT_HELP
			#ifndef MP3_LARGE_GUI
        FSGUI_ShowString(  60,  20,"PRESS  TITLE  FOR JPEG HELP", BK_GROUNDY, BK_GROUNDCRCB);
        	#else
        FSGUI_ShowString( 120,  20,"PRESS  TITLE  FOR JPEG HELP", BK_GROUNDY, BK_GROUNDCRCB);
        	#endif
		#elif defined(USE_PREVIEW_KEY_TO_CALL_JPGEFFECT_HELP)
			#ifndef MP3_LARGE_GUI
        FSGUI_ShowString(  60,  20,"PRESS PREVIEW FOR JPEG HELP", BK_GROUNDY, BK_GROUNDCRCB);
        	#else
        FSGUI_ShowString( 120,  20,"PRESS PREVIEW FOR JPEG HELP", BK_GROUNDY, BK_GROUNDCRCB);
        	#endif
		#endif//#ifdef USE_TITLE_KEY_TO_CALL_JPGEFFECT_HELP

		#ifndef MP3_LARGE_GUI
		for(i=60;i<280;i++)
		{
	            FSGUI_ShowChar(0,i++,28,'-',BK_GROUNDY,BK_GROUNDCRCB);
		}
		#endif
	#endif//#ifdef NEW_MP3_GUI || defined(INDIGO_STYLE_FSGUI)
    }
#endif//CALL_JPGEFFECT_HELP
}


#ifndef HELP_BMP_GUI
#if 1//ndef JPG_EFFECT_ONLY_ROTATE
//
// USAGE:
// potatooo: please try to change this into command format
 
#ifdef INDIGO_STYLE_FSGUI
void Jpg_Show_Usage()
{
	if(Jpg_Show_Usage_Flag)
	{
	    if(Jpg_Show_Usage_Page==0)
	    {
	   	#ifdef MEM_GRAPH_LARGE //2006-06-02, mimitsai add for HD ui.
			set_disbuf(0);
			config_memory(MEMORY_GRAPH_NTSC);
		#else
			config_memory(MEMORY_GRAPH_SMALL);
		#endif	    
	    				
			FSGUI_FillFrameBuf(0,   		    0, BG_WID,      UP_HEI,      JPEG_HELP_BG_Y, JPEG_HELP_BG_CbCr);	 //up bg
			FSGUI_FillFrameBuf(0,		   UP_HEI, BG_WID, CONTENT_HEI, JPEG_HELP_CONTENT_Y, JPEG_HELP_CONTENT_CbCr);//content bg
			FSGUI_FillFrameBuf(0, BG_HEI-DOWN_HEI, BG_WID,    DOWN_HEI,      JPEG_HELP_BG_Y, JPEG_HELP_BG_CbCr);	 //down bg
			FSGUI_FillFrameBuf(0, UP_HEI-LINE_HEI, BG_WID,    LINE_HEI,    JPEG_HELP_LINE_Y, JPEG_HELP_LINE_CbCr);	 //up line
			FSGUI_FillFrameBuf(0, BG_HEI-DOWN_HEI, BG_WID,    LINE_HEI,    JPEG_HELP_LINE_Y, JPEG_HELP_LINE_CbCr);	 //down line

			FSGUI_ShowString( 120* NUMERATOE_X/DENOMINATOR_X,  50* NUMERATOE_Y/DENOMINATOR_Y, "JPG FUNC USAGE"             ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		    FSGUI_ShowString(  70* NUMERATOE_X/DENOMINATOR_X,  70* NUMERATOE_Y/DENOMINATOR_Y, "PROGRAM: PICTURE PLAY MODE" ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);

			int xst= 60* NUMERATOE_X/DENOMINATOR_X;	
		    FSGUI_ShowString(  xst, 100* NUMERATOE_Y/DENOMINATOR_Y, "01: LEFT<->RIGHT"			 ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
			FSGUI_ShowString(  xst, 120* NUMERATOE_Y/DENOMINATOR_Y, "02: UP<->DOWN" 			 ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 140* NUMERATOE_Y/DENOMINATOR_Y, "03: LEFT TOP<->RIGHT BOTTOM",JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 160* NUMERATOE_Y/DENOMINATOR_Y, "04: LEFT BOTTOM<->RIGHT TOP",JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 180* NUMERATOE_Y/DENOMINATOR_Y, "05: H-WINDOW"				 ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 200* NUMERATOE_Y/DENOMINATOR_Y, "06: V-WINDOW"				 ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);			

		    FSGUI_ShowString( 100* NUMERATOE_X/DENOMINATOR_X, 230* NUMERATOE_Y/DENOMINATOR_Y, "'ENTER' TO CONTINUE"        ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		    FSGUI_ShowString( 115* NUMERATOE_X/DENOMINATOR_X, 245* NUMERATOE_Y/DENOMINATOR_Y, "'STOP' TO BREAK"            ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		}
		else if(Jpg_Show_Usage_Page==1)
		{
			FSGUI_FillFrameBuf(0,		   UP_HEI, BG_WID, CONTENT_HEI, JPEG_HELP_CONTENT_Y, JPEG_HELP_CONTENT_CbCr);//content bg
			FSGUI_FillFrameBuf(0, BG_HEI-DOWN_HEI, BG_WID,    DOWN_HEI,      JPEG_HELP_BG_Y, JPEG_HELP_BG_CbCr);	 //down bg
			FSGUI_FillFrameBuf(0, BG_HEI-DOWN_HEI, BG_WID,    LINE_HEI,    JPEG_HELP_LINE_Y, JPEG_HELP_LINE_CbCr);	 //down line

			int xst= 60* NUMERATOE_X/DENOMINATOR_X;	
		    FSGUI_ShowString(  xst, 100* NUMERATOE_Y/DENOMINATOR_Y, "07: LEFT BOTTOM<->RIGHT TOP",JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 120* NUMERATOE_Y/DENOMINATOR_Y, "08: CENTER<->UP-DOWN"		 ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 140* NUMERATOE_Y/DENOMINATOR_Y, "09: CENTER<->LEFT-RIGHT"	 ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
   		    FSGUI_ShowString(  xst, 160* NUMERATOE_Y/DENOMINATOR_Y, "10: EDGE->CENTER"			 ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
   		    FSGUI_ShowString(  xst, 180* NUMERATOE_Y/DENOMINATOR_Y, "11: RANDOM  NONE"			 ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);

		    FSGUI_ShowString( 100* NUMERATOE_X/DENOMINATOR_X, 230* NUMERATOE_Y/DENOMINATOR_Y, "'ENTER' TO CONTINUE"        ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		    FSGUI_ShowString( 115* NUMERATOE_X/DENOMINATOR_X, 245* NUMERATOE_Y/DENOMINATOR_Y, "'STOP' TO BREAK"            ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		}
		else if(Jpg_Show_Usage_Page==2)
		{
			FSGUI_FillFrameBuf(0,   		    0, BG_WID,      UP_HEI,      JPEG_HELP_BG_Y, JPEG_HELP_BG_CbCr);	 //up bg
			FSGUI_FillFrameBuf(0,		   UP_HEI, BG_WID, CONTENT_HEI, JPEG_HELP_CONTENT_Y, JPEG_HELP_CONTENT_CbCr);//content bg
			FSGUI_FillFrameBuf(0, BG_HEI-DOWN_HEI, BG_WID,    DOWN_HEI,      JPEG_HELP_BG_Y, JPEG_HELP_BG_CbCr);	 //down bg
			FSGUI_FillFrameBuf(0, UP_HEI-LINE_HEI, BG_WID,    LINE_HEI,    JPEG_HELP_LINE_Y, JPEG_HELP_LINE_CbCr);	 //up line
			FSGUI_FillFrameBuf(0, BG_HEI-DOWN_HEI, BG_WID,    LINE_HEI,    JPEG_HELP_LINE_Y, JPEG_HELP_LINE_CbCr);	 //down line

			int xst= 80* NUMERATOE_X/DENOMINATOR_X;	
			FSGUI_ShowString( 120* NUMERATOE_X/DENOMINATOR_X,  70* NUMERATOE_Y/DENOMINATOR_Y, "JPG FUNC USAGE"          ,JPEG_HELP_BG_FONT_Y	   , JPEG_HELP_BG_FONT_CbCr);
		    FSGUI_ShowString(  xst, 100* NUMERATOE_Y/DENOMINATOR_Y, "STOP:  RETURN TO MENU"	  ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 120* NUMERATOE_Y/DENOMINATOR_Y, "NEXT:  NEXT PICTURE"	  ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 140* NUMERATOE_Y/DENOMINATOR_Y, "PREV:  PREVIOUS PICTURE" ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 160* NUMERATOE_Y/DENOMINATOR_Y, "PLAY:  PLAY SEQUENTIALLY",JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);

		    FSGUI_ShowString( 100* NUMERATOE_X/DENOMINATOR_X, 230* NUMERATOE_Y/DENOMINATOR_Y, "'ENTER' TO CONTINUE"        ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		    FSGUI_ShowString( 115* NUMERATOE_X/DENOMINATOR_X, 245* NUMERATOE_Y/DENOMINATOR_Y, "'STOP' TO BREAK"            ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		}

	    else if(Jpg_Show_Usage_Page==3)
	    {
			FSGUI_FillFrameBuf(0,		   UP_HEI, BG_WID, CONTENT_HEI, JPEG_HELP_CONTENT_Y, JPEG_HELP_CONTENT_CbCr);//content bg
			FSGUI_FillFrameBuf(0, BG_HEI-DOWN_HEI, BG_WID,    DOWN_HEI,      JPEG_HELP_BG_Y, JPEG_HELP_BG_CbCr);	 //down bg
			FSGUI_FillFrameBuf(0, BG_HEI-DOWN_HEI, BG_WID,    LINE_HEI,    JPEG_HELP_LINE_Y, JPEG_HELP_LINE_CbCr);	 //down line

			int xst= 80* NUMERATOE_X/DENOMINATOR_X;	
		    FSGUI_ShowString(  xst, 100* NUMERATOE_Y/DENOMINATOR_Y, "  UP:  INVERT"			  ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 120* NUMERATOE_Y/DENOMINATOR_Y, "DOWN:  MIRROR"			  ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
			#ifdef NEXT_FORWARD_IN_A_KEY
		    FSGUI_ShowString(  xst, 140, "ZOOM:  CHANGE ZOOM STATE",JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
			#else
		    FSGUI_ShowString(  xst, 140* NUMERATOE_Y/DENOMINATOR_Y, " F-F:  COUNTERCLOCKWISE" ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 160* NUMERATOE_Y/DENOMINATOR_Y, " F-B:  CLOCKWISE"		  ,JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
		    FSGUI_ShowString(  xst, 180* NUMERATOE_Y/DENOMINATOR_Y, "ZOOM:  CHANGE ZOOM STATE",JPEG_HELP_CONTENT_FONT_Y, JPEG_HELP_CONTENT_FONT_CbCr);
			#endif

		    //FSGUI_ShowString( 250, 230, "LEAVE"  ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		    FSGUI_ShowString( 100* NUMERATOE_X/DENOMINATOR_X, 230* NUMERATOE_Y/DENOMINATOR_Y, "'ENTER' TO CONTINUE"        ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
		    FSGUI_ShowString( 115* NUMERATOE_X/DENOMINATOR_X, 245* NUMERATOE_Y/DENOMINATOR_Y, "'STOP' TO BREAK"            ,JPEG_HELP_BG_FONT_Y, JPEG_HELP_BG_FONT_CbCr);
	    }
	}
}

#else //#ifdef INDIGO_STYLE_FSGUI
void Jpg_Show_Usage()//liulifeng move from "\\jpeg\jpegeffect.c" to here
{
//	#ifdef MP3_LARGE_GUI	//Maoyong 2003.12.29 for Large MP3 GUI
   	#ifdef MEM_GRAPH_LARGE //2006-06-02, mimitsai add for HD ui.
	set_disbuf(0);
	config_memory(MEMORY_GRAPH_NTSC);
	#else
	config_memory(MEMORY_GRAPH_SMALL);
	#endif

	if(Jpg_Show_Usage_Flag)
	{
	    if(Jpg_Show_Usage_Page==0)
	    {
	    #ifdef MP3_LARGE_GUI
			FSGUI_FillFrameBuf(0, 0, 720, 480, 0x50, 0x4040);		//Back Ground
		    // first line
		    FSGUI_FillFrameBuf(0, 0, 720, 100, 0x20, 0x8080);
		    FSGUI_FillFrameBuf(0, 100, 720, LINE_HEIGHT+4, WHITE_Y, WHITE_CRCB);
		    //second line
		    FSGUI_FillFrameBuf(0, 372, 720, LINE_HEIGHT+4, WHITE_Y, WHITE_CRCB);
		    FSGUI_FillFrameBuf(0, 380, 720, 100, 0x20, 0x8080);
		    //FSGUI_FillFrameBuf(0, 44, 720, 100, 0x50, 0x4040);

		    FSGUI_ShowString(260,120,"JPG FUNC USAGE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,148,"PROGRAM:  PICTURE PLAY MODE---",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,176,"  LEFT<->RIGHT     UP<->DOWN",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,204,"  LEFT TOP<->RIGHT BOTTOM",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,232,"  LEFT BOTTOM<->RIGHT TOP",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,260,"  H-WINDOW         V-WINDOW",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(196,320,"'ENTER' TO CONTINUE"  ,0x70, 0x5050);
		    FSGUI_ShowString(196,348,"'STOP' TO BREAK"  ,0x70, 0x5050);
	    #else//#ifdef MP3_LARGE_GUI
		    FSGUI_FillFrameBuf(0, 0, 352, 288, 0x50, 0x4040);
		    // first line
		    FSGUI_FillFrameBuf(0, 0, 352, 40, 0x20, 0x8080);
		    FSGUI_FillFrameBuf(0, 40, 352, LINE_HEIGHT, WHITE_Y, WHITE_CRCB);
		    //second line
		    FSGUI_FillFrameBuf(0, 250, 352, LINE_HEIGHT, WHITE_Y, WHITE_CRCB);
		    FSGUI_FillFrameBuf(0, 254, 352, 30, 0x20, 0x8080);

		    FSGUI_FillFrameBuf(0, 44, 352, 206, 0x50, 0x4040);

			FSGUI_ShowString(100,60,"JPG FUNC USAGE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,100,"PROGRAM:  PICTURE PLAY MODE---",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,120,"  LEFT<->RIGHT     UP<->DOWN",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,140,"  LEFT TOP<->RIGHT BOTTOM",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,160,"  LEFT BOTTOM<->RIGHT TOP",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,180,"  H-WINDOW         V-WINDOW",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,210,"'ENTER' TO CONTINUE"  ,0x70, 0x5050);
		    FSGUI_ShowString(100,230,"'STOP' TO BREAK"  ,0x70, 0x5050);
		#endif//#ifdef MP3_LARGE_GUI	
		}
		else if(Jpg_Show_Usage_Page==1)
		{
		#ifdef MP3_LARGE_GUI
		    FSGUI_FillFrameBuf(0, 108, 720, 264, 0x50, 0x4040);

		    FSGUI_ShowString(260,120,"JPG FUNC USAGE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,148,"PROGRAM:  PICTURE PLAY MODE---",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,176,"  LEFT BOTTOM<->RIGHT TOP",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,204,"  CENTER<->UP-DOWN",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,232,"  CENTER<->LEFT-RIGHT",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
   		    FSGUI_ShowString(100,260,"  EDGE->CENTER   RANDOM  NONE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(220,320,"CONTINUE"  ,0x70, 0x5050);	
		#else//MP3_LARGE_GUI	
		//  FSGUI_FillFrameBuf(0, 44, 352, 206, 0x30, 0x8080);
		    FSGUI_FillFrameBuf(0, 44, 352, 206, 0x50, 0x4040);

			FSGUI_ShowString(100,60,"JPG FUNC USAGE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,100,"PROGRAM:  PICTURE PLAY MODE---",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,120,"  LEFT BOTTOM<->RIGHT TOP",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,140,"  CENTER<->UP-DOWN",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,160,"  CENTER<->LEFT-RIGHT",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
   		    FSGUI_ShowString(40,180,"  EDGE->CENTER   RANDOM  NONE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(200,220,"CONTINUE"  ,0x70, 0x5050);
		#endif//MP3_LARGE_GUI
		}
		else if(Jpg_Show_Usage_Page==2)
		{
		#ifdef MP3_LARGE_GUI
		    FSGUI_FillFrameBuf(0, 108, 720, 264, 0x50, 0x4040);
		
		    FSGUI_ShowString(240,120,"JPG FUNC  KEY USAGE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,148,"STOP:     RETURN TO MENU",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,176,"NEXT:     NEXT PICTURE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,204,"PREV:     PREVIOUS PICTURE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,232,"PLAY:     PLAY SEQUENTIALLY",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(220,320,"CONTINUE"  ,0x70, 0x5050);
		#else//MP3_LARGE_GUI	
			//FSGUI_FillFrameBuf(0, 44, 352, 206, 0x30, 0x8080);
		    FSGUI_FillFrameBuf(0, 44, 352, 206, 0x50, 0x4040);

			FSGUI_ShowString(100,60,"JPG FUNC  KEY USAGE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,100,"STOP:     RETURN TO MENU",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,120,"NEXT:     NEXT PICTURE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,140,"PREV:     PREVIOUS PICTURE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,160,"PLAY:     PLAY SEQUENTIALLY",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(200,220,"CONTINUE"  ,0x70, 0x5050);
		#endif//MP3_LARGE_GUI
		}

	    else if(Jpg_Show_Usage_Page==3)
	    {
	    #ifdef MP3_LARGE_GUI
			FSGUI_FillFrameBuf(0, 108, 720, 264, 0x50, 0x4040);

		    FSGUI_ShowString(260,120,"JPG FUNC USAGE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,148,"UP:      INVERT",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,176,"DOWN:    MIRROR",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			#ifdef NEXT_FORWARD_IN_A_KEY       //gerry,2004-6-17 21:14
		    FSGUI_ShowString(100,204,"ZOOM:    CHANGE ZOOM STATE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			#else
		    FSGUI_ShowString(100,204,"F-F:     ANTI-CLOCKWISE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,232,"F-B:     CLOCKWISE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(100,260,"ZOOM:    CHANGE ZOOM STATE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			#endif//NEXT_FORWARD_IN_A_KEY

		    FSGUI_ShowString(220,320,"LEAVE"  ,0x70, 0x5050);
		#else//MP3_LARGE_GUI
			//FSGUI_FillFrameBuf(0, 44, 352, 206, 0x30, 0x8080);
		    FSGUI_FillFrameBuf(0, 44, 352, 206, 0x50, 0x4040);

			FSGUI_ShowString(100,60,"JPG FUNC USAGE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,100,"UP:      INVERT",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,120,"DOWN:    MIRROR",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			#ifdef NEXT_FORWARD_IN_A_KEY//gerry,2004-6-17 21:14
		    FSGUI_ShowString(40,140,"ZOOM:    CHANGE ZOOM STATE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			#else
		    FSGUI_ShowString(40,140,"F-F:     ANTI-CLOCKWISE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,160,"F-B:     CLOCKWISE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
		    FSGUI_ShowString(40,180,"ZOOM:    CHANGE ZOOM STATE",FS_FONTCOLOR_FILE_Y, FS_FONTCOLOR_FILE_CrCb);
			#endif//NEXT_FORWARD_IN_A_KEY

		    FSGUI_ShowString(200,220,"LEAVE"  ,0x70, 0x5050);
		#endif//MP3_LARGE_GUI 
	    }
	}
}
#endif //#ifdef INDIGO_STYLE_FSGUI

#endif//endif 1

#else //#ifndef HELP_BMP_GUI

#include "fsGUI_BmpUI.h"
#include "FrameBuf_BmpUI.h"

#define HELP_TITLE_BG_Y         RGB2Y(153, 138, 131)
#define HELP_TITLE_BG_CRCB      (RGB2Cr(153, 138, 131)<<8)|(RGB2Cb(153, 138, 131))
#define HELP_TITLE_FONT_Y       RGB2Y(49,62,68)
#define HELP_TITLE_FONT_CRCB    (RGB2Cr(49,62,68)<<8)|(RGB2Cb(49,62,68))

#define HELP_FILE_BG_Y          RGB2Y(125, 147, 170)
#define HELP_FILE_BG_CRCB       (RGB2Cr(125, 147, 170)<<8)|(RGB2Cb(125, 147, 170))
#define HELP_FILE_FONT_Y        RGB2Y(222,222,222)
#define HELP_FILE_FONT_CRCB     (RGB2Cr(222,222,222)<<8)|(RGB2Cb(222,222,222))

#define HELP_PAGE_RECT_Y            RGB2Y(81,96,153)
#define HELP_PAGE_RECT_CRCB         (RGB2Cr(81,96,153)<<8)|(RGB2Cb(81,96,153))
#define HELP_PAGE_RECT_EDGE_Y       RGB2Y(172,175,190)
#define HELP_PAGE_RECT_EDGE_CRCB    (RGB2Cr(172,175,190)<<8)|(RGB2Cb(172,175,190))
#define HELP_PAGE_FONT_Y            RGB2Y(157,157,157)
#define HELP_PAGE_FONT_CRCB         (RGB2Cr(157,157,157)<<8)|(RGB2Cb(157,157,157))

#define HELP_KEY_LEFT_X              277
#define HELP_KEY_RIGHT_X             292
#define HELP_KEY_Y                   180

#define HELP_PROGRAM_X               157
#define HELP_PROGRAM_Y               180

#define HELP_PAGE_RECT_X1            361                  
#define HELP_PAGE_RECT_Y1            426

char s[60];
UINT16 CenteredXStart;

/*
 Function: make sentences centered at x direction
 input : xWidth ----- whole line width 
         wFont  ----- displayed font width
 output: xStart ----- centered start

*/
UINT16 XStartLeft2Centered(UINT16 xWidth ,UINT16 wFont)
{
    UINT16 sLen,xStart;
    sLen = wFont * strlen(s);
    xStart = (xWidth - sLen)/2;
    return xStart;
}

/*
 Function: Draw Jpeg Help background
*/
void Jpg_Usage_bg()
{

    FSGUI_FillFrameBuf(0, 0, 720, 29, HELP_FILE_BG_Y, HELP_FILE_BG_CRCB); //title background		
    
    //show title progressive rect
    FSGUI_DrawBackGround(0, 29, 719, 1,12);
    //show title font 
    strcpy(s,"'ENTER'TO CONTINUE /'STOP'TO BREAK");
    CenteredXStart = XStartLeft2Centered(720 ,8);
    FSGUI_ShowLittleString(CenteredXStart, 48,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);
   
    FSGUI_FillFrameBuf(0, 78, 720, 87, HELP_TITLE_BG_Y, HELP_TITLE_BG_CRCB); //title background		
    FSGUI_FillFrameBuf(0, 165, 720, 253, HELP_FILE_BG_Y, HELP_FILE_BG_CRCB);	//all background	
    
    //show bottom progressive rect
    FSGUI_DrawBackGround(0, 418, 719, 1,12);
    
    FSGUI_FillFrameBuf(0, 467, 720, 12, HELP_FILE_BG_Y, HELP_FILE_BG_CRCB);	//all background	
   
    //show "help" font
    FSGUI_ShowString(344 - 4*16,430,"HELP" ,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);

    //show help page rect
    FrameBuf_DrawRect(HELP_PAGE_RECT_X1, HELP_PAGE_RECT_Y1, 94, 30, HELP_PAGE_RECT_Y, HELP_PAGE_RECT_CRCB);      
    
    //show help page rect four outlines
    FrameBuf_DrawLine(HELP_PAGE_RECT_X1, HELP_PAGE_RECT_Y1, 92, 1, HELP_PAGE_RECT_EDGE_Y, HELP_PAGE_RECT_EDGE_CRCB);
    FrameBuf_DrawLine(HELP_PAGE_RECT_X1, HELP_PAGE_RECT_Y1 + 30, 92, 1, HELP_PAGE_RECT_EDGE_Y, HELP_PAGE_RECT_EDGE_CRCB);
    FrameBuf_DrawLine(HELP_PAGE_RECT_X1, HELP_PAGE_RECT_Y1, 1, 28, HELP_PAGE_RECT_EDGE_Y, HELP_PAGE_RECT_EDGE_CRCB);
    FrameBuf_DrawLine(HELP_PAGE_RECT_X1, HELP_PAGE_RECT_Y1 + 94, 1, 28, HELP_PAGE_RECT_EDGE_Y, HELP_PAGE_RECT_EDGE_CRCB);

}

void Jpg_Show_Usage()
{
#ifdef DISP_REGION_BOTTOM //feeling add for display region bottom to up when help, 2005-01-19
    if(t_disp)
	{
	    osd_init();
	    DispCookOSD0(1);
	}
#endif
    //when enter JPEG state,use ref0 and GRAPH_NTSC memory.
    if((pFsJpeg->gifsState == FS_STATE_JPEG) && (Jpg_Show_Usage_Page==0))
	{ 
        set_disbuf(0);
	    config_memory(MEMORY_GRAPH_NTSC);
    }
	
	if(Jpg_Show_Usage_Flag)
	{
	    if(Jpg_Show_Usage_Page==0)
	    {
	        Jpg_Usage_bg();
	        
	        strcpy(s,"JPG FUNC KEY USAGE");
            CenteredXStart = XStartLeft2Centered(720 ,16);
		   	FSGUI_ShowString(CenteredXStart,108,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);
		    
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 16*5,HELP_KEY_Y,"STOP:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y,"RETURN TO MENU",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 16*5,HELP_KEY_Y + 40,"NEXT:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y +40,"NEXT PICTURE",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 16*5,HELP_KEY_Y + 80,"PREV:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y + 80,"PREVIOUS PICTURE",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 16*5,HELP_KEY_Y + 120,"PLAY:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y + 120,"PLAY SEQUENTIALLY",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		
	        strcpy(s,"1/5");
            CenteredXStart = XStartLeft2Centered(94 ,16);
		   	FSGUI_ShowString(HELP_PAGE_RECT_X1 + CenteredXStart,HELP_PAGE_RECT_Y1 + 2,s,HELP_PAGE_FONT_Y, HELP_PAGE_FONT_CRCB);
		
		}
		else if(Jpg_Show_Usage_Page==1)
		{
            Jpg_Usage_bg();
            
	        strcpy(s,"JPG FUNC KEY USAGE");
            CenteredXStart = XStartLeft2Centered(720 ,16);
		   	FSGUI_ShowString(CenteredXStart,108,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);
		    
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 3*16,HELP_KEY_Y,"UP:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y,"INVERT",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 5*16,HELP_KEY_Y + 40,"DOWN:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y + 40,"MIRROR",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 4*16,HELP_KEY_Y + 80,"F-F:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y + 80,"ANTI-CLOCKWISE",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 4*16,HELP_KEY_Y + 120,"F-B:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y + 120,"CLOCKWISE",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_KEY_LEFT_X - 5*16,HELP_KEY_Y + 160,"ZOOM:",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
	        FSGUI_ShowString(HELP_KEY_RIGHT_X,HELP_KEY_Y + 160,"CHANGE ZOOM STATE",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
	        
	        strcpy(s,"2/5");
            CenteredXStart = XStartLeft2Centered(94 ,16);
		   	FSGUI_ShowString(HELP_PAGE_RECT_X1 + CenteredXStart,HELP_PAGE_RECT_Y1 + 2,s,HELP_PAGE_FONT_Y, HELP_PAGE_FONT_CRCB);
		
		}
		else if(Jpg_Show_Usage_Page==2)
		{
            Jpg_Usage_bg();

	        strcpy(s,"JPG FUNC USAGE");
            CenteredXStart = XStartLeft2Centered(720 ,16);
		   	FSGUI_ShowString(CenteredXStart,88,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);

	        strcpy(s,"PROGRAM :PICTURE PLAY MODE");
            CenteredXStart = XStartLeft2Centered(720 ,16);
		   	FSGUI_ShowString(CenteredXStart,128,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);

		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y,"01.LEFT TOP > RIGHT BOTTOM",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 40,"02.RIGHT TOP > LEFT BOTTOM",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 80,"03.LEFT BUTTOM > RIGHT TOP",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 120,"04.UP > DOWN",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 160,"05.LEFT > RIGHT",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 200,"06.EDGE > CENTER",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);

	        strcpy(s,"3/5");
            CenteredXStart = XStartLeft2Centered(94 ,16);
		   	FSGUI_ShowString(HELP_PAGE_RECT_X1 + CenteredXStart,HELP_PAGE_RECT_Y1 + 2,s,HELP_PAGE_FONT_Y, HELP_PAGE_FONT_CRCB);

		}

	    else if(Jpg_Show_Usage_Page==3)
	    {
            Jpg_Usage_bg();

	        strcpy(s,"JPG FUNC USAGE");
            CenteredXStart = XStartLeft2Centered(720 ,16);
		   	FSGUI_ShowString(CenteredXStart,88,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);

	        strcpy(s,"PROGRAM :PICTURE PLAY MODE");
            CenteredXStart = XStartLeft2Centered(720 ,16);
		   	FSGUI_ShowString(CenteredXStart,128,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);
            
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y,"07.EXPAND VERTICALLY OUTWARDS",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 40,"08.EXPAND HORIZONTALLY OUTWARDS",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 80,"09.SHUTTER_H",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 120,"10.SHUTTER_V",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 160,"11.RANDOM",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 200,"12.NONE",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);

	        strcpy(s,"4/5");
            CenteredXStart = XStartLeft2Centered(94 ,16);
		   	FSGUI_ShowString(HELP_PAGE_RECT_X1 + CenteredXStart,HELP_PAGE_RECT_Y1 + 2,s,HELP_PAGE_FONT_Y, HELP_PAGE_FONT_CRCB);

	    }

	    else if(Jpg_Show_Usage_Page==4)
	    {
            Jpg_Usage_bg();
            
	        strcpy(s,"JPG FUNC USAGE");
            CenteredXStart = XStartLeft2Centered(720 ,16);
		   	FSGUI_ShowString(CenteredXStart,88,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);

	        strcpy(s,"PROGRAM :PICTURE PLAY MODE");
            CenteredXStart = XStartLeft2Centered(720 ,16);
		   	FSGUI_ShowString(CenteredXStart,128,s,HELP_TITLE_FONT_Y, HELP_TITLE_FONT_CRCB);

		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y ,"13.RIGHT BUTTOM > LEFT TOP",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 40,"14.PULL VERTICALLY OUTWARDS",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 80,"15.DOWN > UP",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 120,"16.UP > DOWN",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);
		    FSGUI_ShowString(HELP_PROGRAM_X,HELP_PROGRAM_Y + 160,"17.RIGHT > LEFT",HELP_FILE_FONT_Y, HELP_FILE_FONT_CRCB);

	        strcpy(s,"5/5");
            CenteredXStart = XStartLeft2Centered(94 ,16);
		   	FSGUI_ShowString(HELP_PAGE_RECT_X1 + CenteredXStart,HELP_PAGE_RECT_Y1 + 2,s,HELP_PAGE_FONT_Y, HELP_PAGE_FONT_CRCB);

	    }
    }   
}

#endif

#endif//#ifdef JPG_EFFECT
