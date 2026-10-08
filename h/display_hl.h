/*
*  Sunplus search function  
*  Creat by terry
*/

//
// DispCookOSD0
//      Prepare the content of OSD0 to temp buffer
//      (from OSD0_TEMP_YA-th KBytes in DRAM, size=38*16*1*24*4/8=7104 Bytes)
//
//      input   : bChange
//                  1 : re-generate all content
//                  0 : only update timing display parts
//                dwTime :
//                  < 0 : remain time (-00:00:00)
//                  > 0 : elapsed time( 00:00:00)
//
//      output  : none
//
//      side-effect : none
//
//      notes:
//      0     5          15  18   22  25
//      CD    TRACK      SPK PBC  REP TIME
//      VCD   TRACK      SPK PBC  REP TIME
//      SVCD  TRACK      SPK PBC  REP TIME
//      DVD   TITLE      CHAPTER      TIME
//      MP3   TRACK      SPK      REP TIME
//
//      Color table
//          palette_16color_setup(defined in osd1.c)
//
//===========================================================================================
// debug option
//===========================================================================================
#undef io_write
#define io_write(x);
#ifdef SHOW_BOOKMARK_TIME//libing 2005-6-9 9:40
UINT32  book_time;//libing 2005-6-8 13:37
BYTE    book_hour;
BYTE    book_min;
BYTE    book_sec;
extern  BYTE    bookIndex;
#endif
#ifdef SUPPORT_CDG //Jeff 20020824
#include "cdg.h"
extern UINT8   bReadSubChannel;
#endif

#include "sinf.h"
#include "kinf.h"//wangap

#ifdef MIX_CDMP3_DISC_DISPLAY_REAL_CD_TRK //linrc add 2004-10-29 11:16
#include "cdxa.h"
#endif

#if defined (DISPLAY_MP4_VER_PI) || defined(DISPLAY_MP4_AV_INFO)  //Maoyong 2004.06.29
#include "fsNav.h"
#include "avi_if.h"
#include "audcodec.h"
#endif

#ifdef OSD_BMP
#include "osd_BmpUI.h"
#include "fsNAV.h"
#endif

#ifdef MP3_2GOTO_TYPE
#include "fsNAV.h"
#endif
#ifdef SUPPORT_NERODIGITAL  //lyc add 2005-12-23
#include "file_if.h"
#include "fsNav.h"		//zhongshan for warning 2006-2-28 18:15
#endif
#ifdef  NOCHANGE_DISPLAY_WHEN_PRESTOP
#include "fsGUI.h"
#endif
#ifdef DIV_GOTO_DISPLAY   
#ifdef NINTAUS_OSD_STR   //2004-2-16 10:58张宇P
#define REGION2_FONTCOLOR    2//word color
#define REGION2_NUMCOLOR     2 //number color
#else
#define REGION2_FONTCOLOR    8//word color
#define REGION2_NUMCOLOR     7 //number color
#endif
#define REGION2_BKCOLOR      10//background color
#define REGION2_RCOLOR       10//region color
#define REGION2_HL_COLOR     4//to hilight
#endif

#ifdef  ALCO_DIVX_UI
extern BYTE record_file_extern_name_flag;
#endif

extern void mark_UpdateOSD();
//===========================================================================================
// function
//===========================================================================================

#ifndef DIV_GOTO_DISPLAY
void hi_light_time(int pos)
{

//skip the TT and CH characters
#if defined (OSD_BMP_DISPLAY_TT_TIME) || defined(OSD_BMP_DISPLAY_CH_TIME)
	if(cd_type_loaded == CDDVD)
	    pos += 3 * DISP_LITTLE_CHAR_WIDTH;
#endif

    
    int time=0,shift_base=0;
    
    if((index_x-5)<=1)
    {
		time=goto_hour;
		shift_base=4;
    }
    else if((index_x-5)<=3)
    {
		time=goto_min;
		shift_base=3;
    }
    else if((index_x-5)<=5)
    {
		time=goto_sec;
		shift_base=2;
    }
    
#ifdef OSD_BMP_DISPLAY //There is no blank in front of the time string in osd_bmp_display,feeling 20040920
	shift_base += 1;
#endif
    
    if((index_x-5)%2==0)//even
    {
		psprintf(linebuf, "%01d", time/10); 
		io_write("i");
#ifdef SDRAM_16Mb_Mode	
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR	
		do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, 0, 1);
	#else 	
		do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, 0, 2);
	#endif
#elif defined (OSD_BMP_DISPLAY)
        do_DispOSD0LittleString(pos+(index_x-shift_base)* DISP_LITTLE_CHAR_WIDTH, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,time shows little character,feeling 200408
#elif defined(PHILIPS_SETUP)
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, DISP_HLFONT, DISP_HLGROUND);
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
        hi_light_index = index_x - shift_base;
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#else
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, 2, 4);
#endif        
	}
    else
    {
		psprintf(linebuf, "%01d", time%10); 
		io_write("h");
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
		do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, 0, 1);  
	#else
		do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, 0, 2);  
	#endif
#elif defined(OSD_BMP_DISPLAY)
        do_DispOSD0LittleString(pos+(index_x-shift_base)* DISP_LITTLE_CHAR_WIDTH, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,time val shows little character,feeling200408
#elif defined(PHILIPS_SETUP)
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, DISP_HLFONT, DISP_HLGROUND);  
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
        hi_light_index = index_x - shift_base;
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#else
        do_DispOSD0String(pos+(index_x-shift_base), 0, linebuf, 2, 4);  
#endif
        
    }   
}   
   
void hi_light_chapter(int id,int pos)//kenny 2002/4/13
{
    if(index_x==2)
    {
        psprintf(linebuf, "%01d",id/100);  
        io_write("g");
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR	
		do_DispOSD0String(pos, 0, linebuf,  0, 1);
	#else
		do_DispOSD0String(pos, 0, linebuf,  0, 2);
	#endif
#elif defined(OSD_BMP_DISPLAY)
        do_DispOSD0LittleString(pos, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
        do_DispOSD0String(pos, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        do_DispOSD0String(pos, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
        do_DispOSD0String(pos, 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
        hi_light_index = 0;
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#else
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#endif
        
    }
    else if(index_x==3)
    {
        psprintf(linebuf, "%01d",(id%100)/10);     
        io_write("f");
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
		do_DispOSD0String(pos+1, 0, linebuf, 0, 1);
	#else
		do_DispOSD0String(pos+1, 0, linebuf, 0, 2);
	#endif
#elif defined (OSD_BMP_DISPLAY)
        do_DispOSD0LittleString(pos+1*DISP_LITTLE_CHAR_WIDTH, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
        do_DispOSD0String(pos+1, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);            
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        do_DispOSD0String(pos+1, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
        do_DispOSD0String(pos+1, 0, linebuf, 0, 2); 
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
        hi_light_index = 1;
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#else
        do_DispOSD0String(pos+1, 0, linebuf, 2, 4);            
#endif
        
    }
    else if(index_x==4)
    {
        psprintf(linebuf, "%01d",id%10);       
        io_write("e");
#ifdef SDRAM_16Mb_Mode   
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
	 	do_DispOSD0String(pos+2, 0, linebuf, 0, 1); 
	#else
        	do_DispOSD0String(pos+2, 0, linebuf, 0, 2);   
	#endif   
#elif defined(OSD_BMP_DISPLAY)
        do_DispOSD0LittleString(pos+2*DISP_LITTLE_CHAR_WIDTH, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
        do_DispOSD0String(pos+2, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);    
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        do_DispOSD0String(pos+2, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
        do_DispOSD0String(pos+2, 0, linebuf, 0, 2);    
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
		hi_light_index = 2;
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#else
		do_DispOSD0String(pos+2, 0, linebuf, 2, 4);    
#endif
    }
}   

//Maoyong 2004.04.28 marked MP3_DIRECT_SELECT
//#ifdef MP3_DIRECT_SELECT
//zhaoyanhua modify the function to  show 4 digits when CDROM.3-7-16 16:43
void hi_light_title(int id, int pos)
{
    if (cd_type_loaded == CDROM)
    {
    	int id0 = 0,id1= 0,id2=0,id3=0;

    	id0 = id/1000;
    	id1 = (id%1000)/100;
		id2 = ((id%1000)%100);
    	id2 = id2/10;
   		id3 = (id%1000)%100;
		id3 = id3%10;

    if(index_x==0)
    {
        	psprintf(linebuf, "%01d",id0);
        io_write("d");
			
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
		do_DispOSD0String(pos, 0, linebuf, 0, 1);
	#else
		do_DispOSD0String(pos, 0, linebuf, 0, 2);
	#endif
#elif defined(OSD_BMP_DISPLAY)
            do_DispOSD0LittleString(pos, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
        do_DispOSD0String(pos, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        do_DispOSD0String(pos, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
        do_DispOSD0String(pos, 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
        hi_light_index = 0;
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#else
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#endif
    }
    else if(index_x==1)
    {
        	psprintf(linebuf, "%01d",id1);
        io_write("c");
			
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
		do_DispOSD0String(pos+1, 0, linebuf, 0, 1);
	#else
		do_DispOSD0String(pos+1, 0, linebuf, 0, 2);
	#endif
#elif defined(OSD_BMP_DISPLAY)
            do_DispOSD0LittleString(pos+1*DISP_LITTLE_CHAR_WIDTH, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
        do_DispOSD0String(pos+1, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        do_DispOSD0String(pos+1, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
        do_DispOSD0String(pos+1, 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
        hi_light_index = 1;
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#else
        do_DispOSD0String(pos+1, 0, linebuf, 2, 4);
#endif
		}
      	else if(index_x==2)
    	{
        	psprintf(linebuf, "%01d",id2);
        	io_write("c");
			
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
		do_DispOSD0String(pos+2, 0, linebuf, 0, 1);
	#else
		do_DispOSD0String(pos+2, 0, linebuf, 0, 2);
	#endif	
#elif defined(OSD_BMP_DISPLAY)
            do_DispOSD0LittleString(pos+2*DISP_LITTLE_CHAR_WIDTH, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
            do_DispOSD0String(pos+2, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        	do_DispOSD0String(pos+2, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
        do_DispOSD0String(pos+2, 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
        hi_light_index = 2;
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
    #else
        do_DispOSD0String(pos+2, 0, linebuf, 2, 4);
#endif


     	}

     	else if(index_x==3)
    	{
        	psprintf(linebuf, "%01d",id3);
        	io_write("c");
			
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
		do_DispOSD0String(pos+3, 0, linebuf, 0, 1);
	#else
		do_DispOSD0String(pos+3, 0, linebuf, 0, 2);
	#endif
#elif defined(OSD_BMP_DISPLAY)
            do_DispOSD0LittleString(pos+3*DISP_LITTLE_CHAR_WIDTH, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
            do_DispOSD0String(pos+3, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        	do_DispOSD0String(pos+3, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
            do_DispOSD0String(pos+3, 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
            hi_light_index = 3;
            do_DispOSD0String(pos, 0, linebuf, 2, 4);
    #else
        	do_DispOSD0String(pos+3, 0, linebuf, 2, 4);
#endif
		}
	}
	else  //not CDROM
	{
		if(index_x==0)
    	{
        	psprintf(linebuf, "%01d",id/10);
        	io_write("d");
    		
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
			do_DispOSD0String(pos, 0, linebuf, 0, 1);
	#else
			do_DispOSD0String(pos, 0, linebuf, 0, 2);
	#endif
#elif defined (OSD_BMP_DISPLAY)
            do_DispOSD0LittleString(pos, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
            do_DispOSD0String(pos, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        	do_DispOSD0String(pos, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
            do_DispOSD0String(pos, 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
            hi_light_index = 0;
            do_DispOSD0String(pos, 0, linebuf, 2, 4);
    #else
       	 	do_DispOSD0String(pos, 0, linebuf, 2, 4);
#endif
    	}
    	else if(index_x==1)
    	{
        	psprintf(linebuf, "%01d",id%10);
      		io_write("c");
    		
#ifdef SDRAM_16Mb_Mode
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
		       do_DispOSD0String(pos+1, 0, linebuf, 0, 1);
	#else
			do_DispOSD0String(pos+1, 0, linebuf, 0, 2);
	#endif
#elif defined(OSD_BMP_DISPLAY)
            do_DispOSD0LittleString(pos+1*DISP_LITTLE_CHAR_WIDTH, 12, linebuf, DISP_GBLUE, DISP_GREEN);//in bmp display,title val shows little character,feeling
#elif defined(PHILIPS_SETUP)
            do_DispOSD0String(pos+1, 0, linebuf, DISP_HLFONT, DISP_HLGROUND);
#elif defined(INDIGO_STYLE_OSDUI) // 2006-03-20 mimitsai add for highlight color
        	do_DispOSD0String(pos+1, 0, linebuf, DISP_ORANGE, DISP_GBLUE);
#elif defined( ALCO_PORTABLE)
            do_DispOSD0String(pos+1, 0, linebuf, 0, 2);
#elif defined( USE_NEW_SCHINESE_OSD)//liyl modify 20060301
            hi_light_index = 1;
            do_DispOSD0String(pos, 0, linebuf, 2, 4);
    #else
       	 	do_DispOSD0String(pos+1, 0, linebuf, 2, 4);
#endif
    	}

	}

}
/*#else //not MP3_DIRECT_SELECT

void hi_light_title(int id, int pos)
{
    if(index_x==0)
    {
        psprintf(linebuf, "%01d",id/10);    
        io_write("d");
        
#ifdef SDRAM_16Mb_Mode
		do_DispOSD0String(pos, 0, linebuf, 0, 2);
#else
        do_DispOSD0String(pos, 0, linebuf, 2, 4);
#endif
        
    }
    else if(index_x==1)
    {
        psprintf(linebuf, "%01d",id%10);        
        io_write("c");
		
#ifdef SDRAM_16Mb_Mode 
		do_DispOSD0String(pos+1, 0, linebuf, 0, 2); 
#else
        do_DispOSD0String(pos+1, 0, linebuf, 2, 4); 
#endif
        
    }
}
#endif  //end MP3_DIRECT_SELECT
*/
#else//if defined DIV_GOTO_DISPLAY
void hi_light_time(int pos)
{
	BYTE buf[20];
	int time=0,shift_base=0;
    
    
   // osd_draw_region_rect(pos*8,0,8*8,24,5,2);
    if((index_x-5)<=1)
    {
		time=goto_hour;
		shift_base=5;//shift_base=4;
    }
    else if((index_x-5)<=3)
    {
		time=goto_min;
		shift_base=4;//shift_base=3;
    }
    else if((index_x-5)<=5)
    {
		time=goto_sec;
		shift_base=3;//shift_base=2;
    }
    
    if((index_x-5)%2==0)//even
    {
		psprintf(buf, "%01d", time/10); 
		io_write("i");
	}
    else
    {
		psprintf(buf, "%01d", time%10); 
		io_write("h");        
    }   
  
	osd_DrawRegionString(pos+(index_x-shift_base), 0, buf, REGION2_NUMCOLOR, REGION2_HL_COLOR, 2);
	   
}

void hi_light_chapter(int id, int pos)
{
	BYTE buf[20];
	int shift = 0;
	//osd_draw_region_rect(pos, 0,2*16, 2*16 , 5,2);
	if(index_x == 2)
	{
		psprintf(buf, "%01d",id/100);  
		shift = 0;		
	}
	else if(index_x== 3)
	{
		psprintf(buf, "%01d",(id%100)/10); 
		shift = 1;
	}
	else if(index_x==4)
	{
		psprintf(buf, "%01d",id%10); 
		shift = 2;
	}
	osd_DrawRegionString(pos+shift,0,buf,REGION2_NUMCOLOR, REGION2_HL_COLOR, 2);
}

void hi_light_title(int id, int pos)
{
	BYTE  buf[20];
	int shift = 0;
	
#ifdef MP3_DIRECT_SELECT//zhaoyanhua add 2004-2-16 11:20
    if (cd_type_loaded == CDROM)
    {
    	int id0 = 0,id1= 0,id2=0,id3=0;

    	id0 = id/1000;
    	id1 = (id%1000)/100;
		id2 = ((id%1000)%100);
    	id2 = id2/10;
   		id3 = (id%1000)%100;
		id3 = id3%10;

        if(index_x == 0)
        {
            psprintf(buf, "%01d",id0);
            shift = 0;
        }
        else if(index_x == 1)
        {
            psprintf(buf, "%01d",id1);
            shift = 1;
        }
        else if(index_x == 2)
        {
            psprintf(buf, "%01d",id2);
            shift = 2;
        }
        else if(index_x == 3)
        {
            psprintf(buf, "%01d",id3);
            shift = 3;
        }
    }
    else//cd_type_loaded != CDROM
#endif//#ifdef MP3_DIRECT_SELECT
    {
	if(index_x ==0)
	{
		psprintf(buf, "%01d",id/10); 
		shift = 0;	
	}
	//osd_draw_region_rect(pos, 0,2*16, 2*16 , 5,2);	
	else if(index_x == 1)
	{
		psprintf(buf, "%01d",id%10); 
		shift = 1;
	}
    }//if (cd_type_loaded != CDROM)

	osd_DrawRegionString(pos+shift,0,buf, REGION2_NUMCOLOR, REGION2_HL_COLOR, 2);
}
#endif//ifndef DIV_GOTO_DISPLAY

void time_trans2hms(void) //xyy 2003-7-29 11:42
{
	UINT32 time=goto_time;
	goto_time=goto_time%10000000;
	goto_sec=time%100;            
	time=time/100;
	goto_min=time%100;
	time=time/100;
	goto_hour=time%100;             
}

#ifndef OSD_BMP_DISPLAY
void Print2OSDmem(int id,int val,UINT8 pos)
{
	BYTE    fontColor, bkColor; 
    
	bkColor = DISP_SHADOW; //OSD shadow color
	fontColor = DISP_GREEN; //green
    
	if(val) {       
	#ifdef INDIGO_STYLE_OSDUI// 2006-04-04, mimitsai modify//jiangxl modify 20060918
		fontColor = DISP_GREEN; 
	#else
		fontColor = DISP_YGREEN; //yellow-green
	#endif                      
        // marked by jiangxl,can't show time play avi with subtitle 2006-9-7 11:18下午
#ifndef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-22 10:58
		if(full_scrn&GOTO) {    
#ifdef NEW_GOTO//kenny 2002/4/13
			if(val&COOK_S_TIMER) {
				if(index_x>=5)
				{
					time_trans2hms();    //xyy 2003-7-29 11:42       
					#ifdef NOT_SHOW_TIME_IN_JPG
						if(Is_JPEG_STATE())
 					    	psprintf(linebuf, "       ");
						else
							psprintf(linebuf, " %02d:%02d:%02d", goto_hour, goto_min, goto_sec);  
					#elif defined  NO_DISP_TIME_CLOCK_WHEN_KODAK               //sunzhh add 20050707//shenyj modify 
						if(pFsJpeg->gbfsPictureCD == 1)
 					    	psprintf(linebuf, "       ");
						else
							psprintf(linebuf, " %02d:%02d:%02d", goto_hour, goto_min, goto_sec);  
					#else
							psprintf(linebuf, " %02d:%02d:%02d", goto_hour, goto_min, goto_sec);   
					#endif					
					
				} else {
					#ifdef NOT_SHOW_TIME_IN_JPG
						if(Is_JPEG_STATE())
	 					    psprintf(linebuf, "       ");
						else
							psprintf(linebuf, " %02d:%02d:%02d", goto_hour, goto_min, goto_sec);  
					#elif defined NO_DISP_TIME_CLOCK_WHEN_KODAK                     //sunzhh add 20050707//shenyj modify
						if(pFsJpeg->gbfsPictureCD == 1)
	 					    psprintf(linebuf, "       ");
						else
							psprintf(linebuf, " %02d:%02d:%02d", goto_hour, goto_min, goto_sec);  
					#else
							//psprintf(linebuf, " %02d:%02d:%02d", goto_hour, goto_min, goto_sec);   
							psprintf(linebuf, " %02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss);//yaowh 2005-5-25 22:09
					#endif	
					
					if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME)) // terry 2002/6/4 09:48PM : solve time in goto mode without '-'
					linebuf[0]='-';
				}
			} else 
			{
#ifdef  NEW_DISPLAY_GOTO_OSD
                                if(pos!=POS_DVD_CHAP)
                                {
                                    //if(dvd_title)
                                    //liulifeng marked for when user goto
                                    // first enter a big number ex.124, next enter a litte ex.018
                                    // the display track not refresh immediately
                                        id=dvd_title;
                                    if(cd_type_loaded==CDDVD)
                                        psprintf(linebuf, "T %02d/%02d", id, val);
                                    else if (cd_type_loaded == CDROM)
                                        psprintf(linebuf, " TRK %04d/%d", id, val);
                                    else
                                        psprintf(linebuf, " TRK %02d/%02d",id,val);
                                }
                                else
                                {
                                    if(dvd_chapter) 
                                        id=dvd_chapter;
                                    psprintf(linebuf, "C %03d/%03d", id, val);
                                }
#else//#ifdef  NEW_DISPLAY_GOTO_OSD
				if(pos!=COOK_CHP_VAL) 
				{//title            
					//if(dvd_title)
                    //liulifeng marked for when user goto
                    // first enter a big number ex.124, next enter a litte ex.018
                    // the display track not refresh immediately
						id=dvd_title;
					
					#ifdef MP3_2GOTO_TYPE
					if((!index_x) && (cd_type_loaded==CDROM) && (pFsJpeg->ControlArea == CNT_AREA_DIR))
					    id = pFsJpeg->fsnav_dir_now+1;
                    #endif
                    
					//Maoyong 2004.04.28 marked	MP3_DIRECT_SELECT
			//#ifdef MP3_DIRECT_SELECT	//zhaoyanhua add 3-7-16 16:47
					if (cd_type_loaded == CDROM)
#ifdef NO_SHOW_CDG_ICON      //LIZHX ADD 2005-7-13 18:01
					 psprintf(linebuf, "  %02d/%02d",id,val);//lizhx modify 2005-7-13 21:40
#else
					#ifdef GOTO_NUM_MODIFY_BY_TRK_NUM//zxb for philips
					{					
						if(val>999)
						psprintf(linebuf, "%04d/%02d",id,val);
						else if(val > 99)
							psprintf(linebuf, " %03d/%02d",id,val);
						else
							psprintf(linebuf, "  %02d/%02d",id,val);
					}
					#else//#ifdef GOTO_NUM_MODIFY_BY_TRK_NUM//zxb for philips
						psprintf(linebuf, "%04d/%02d",id,val);
					#endif//#ifdef GOTO_NUM_MODIFY_BY_TRK_NUM//zxb for philips
#endif//#ifdef NO_SHOW_CDG_ICON      //LIZHX ADD 2005-7-13 18:01
					else
					psprintf(linebuf, "%02d/%02d",id,val);
			//#else
					
			//		psprintf(linebuf, "%04d/%02d",id,val);                  
			//#endif

				} else {
					#ifdef SET_CH_0_WHEN_MODIFY_GOTO_CH //zxb 060809 for philips
					if(index_x >= 2 && index_x <= 4)
					#else
					if(dvd_chapter) 
					#endif
						id=dvd_chapter;
					psprintf(linebuf, "%03d/%03d",id,val);          
				}
#endif//#ifdef  NEW_DISPLAY_GOTO_OSD
			}   
#else   //#ifdef NEW_GOTO
			if(val&COOK_S_TIMER) {
				if(index_x==2) {
					UINT32 time=goto_time;
                    
					bkColor = DISP_GBLUE;                        
					fontColor = DISP_WHITE; 
					goto_time=goto_time%10000000;
					goto_sec=time%100;            
					time=time/100;
					goto_min=time%100;
					time=time/100;
					goto_hour=time%100;             
					psprintf(linebuf, " %02d:%02d:%02d", goto_hour, goto_min, goto_sec);            
				} else {
                    psprintf(linebuf, " %02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss);
				}
			} else {
				if(pos!=COOK_CHP_VAL) {//title          
					if(index_x==0) {
						bkColor = DISP_GBLUE;                                
						fontColor = DISP_WHITE; 
					}
                    
					if(index_x!=2) {
						if(dvd_title) {
							if(dvd_title>val)
								dvd_title=dvd_title%10;
                            
							id=dvd_title;
						}
					}
					
					psprintf(linebuf, "%02d",id);                   
				} else {
					if(index_x==1) {
						bkColor = DISP_GBLUE;    
						fontColor = DISP_WHITE; 
					}
					
					if(index_x!=2) {
						if(dvd_chapter) {
							if(dvd_chapter>val)
								dvd_chapter=dvd_chapter%10;
                            
							id=dvd_chapter;
						}
					}
					psprintf(linebuf, "%03d",id);   
				}
                
                io_write("9");
#ifdef SDRAM_16Mb_Mode 
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
				do_DispOSD0String(pos, 0, linebuf, 1, 0); 
	#else
				do_DispOSD0String(pos, 0, linebuf, 2, 0); 
	#endif
#elif defined( ALCO_PORTABLE)//shenyj add for alco 2006/03/25
                do_DispOSD0String(pos, 0, linebuf, 2, 0); 
#else
				do_DispOSD0String(pos, 0, linebuf, fontColor, bkColor); 
#endif				
#ifdef DISP_REGION_BOTTOM
				if(OSD_ShowBottomDisp() == 1)
					bkColor = DISP_SHADOW_CDROM;
				else
#endif//DISP_REGION_BOTTOM				    
					bkColor = DISP_SHADOW; //OSD shadow color                
				
				if(pos==COOK_CHP_VAL) {
					pos+=3;
					psprintf(linebuf, "/%03d",val); 
				} else {
					pos+=2;
					psprintf(linebuf, "/%02d",val);
				}
			}               
#endif//NEW_GOTO
		}
			
        else 
#endif//end ifndef DIV_GOTO_DISPLAY		
			
       if(val&COOK_S_TIMER)
        {
	   #ifdef SHOW_BOOKMARK_TIME//libing 2005-6-9 9:40
	        if(full_scrn==MARK)//libing 2005-6-8 13:23
                {
                	if(book[bookIndex][0]==0)
                    {
                		psprintf(linebuf, " %02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss);                	
                	}else
                	{                	
                		UINT32 time1=book_tm[bookIndex]; 
                		book_tm[bookIndex]=book_tm[bookIndex]%10000000;
                		book_sec=time1%60;
                		time1=time1/60;
                		book_min=time1%60;
                		time1=time1/60;
                		book_hour=time1%60;           	
             	    	psprintf(linebuf, " %02d:%02d:%02d", book_hour, book_min, book_sec);           	
                	}
                }
	        else
	   #endif
	        if ((cd_type_loaded == CDROM) && (Is_JPEG_STATE()))  // Add by David for Jpeg time display bug 2003-12-1 16:28
                {
                    show_time_hh = 0;
                    show_time_mm = 0;
                    show_time_ss = 0;
                } 
                 #ifdef NOT_SHOW_TIME_IN_JPG    //axel 2004/1/8 04:58PM        
				    #ifdef NOSHOW_CDROM_WHEN_DISP  //zhangyu 2004-6-14 20:35
				    if(!(pFsJpeg->gbfsPictureCD))
				    #endif
				        if(Is_JPEG_STATE())
                    #ifdef SHOW_KODAKCD_FILENAME  //kevinmonkey 050711
                {
                    if(pFsJpeg->gbfsPictureCD)
                    {
                        pos -= 2;
                        psprintf(linebuf, "KODAK PIC CD");
                    }
                    else
 					    psprintf(linebuf, "       ");
                        //kevinmonkey 050720 no show filename T_T
                        /*strcpy(linebuf,iso9660_file[pFsJpeg->fsnav_trk_now + pFsJpeg->first_mp3_entry].name);*/
                }
                    #else  //!SHOW_KODAKCD_FILENAME
 					    psprintf(linebuf, "       ");
                    #endif  //#ifdef SHOW_KODAKCD_FILENAME
					    else
				#endif	
			#ifdef NOSHOW_CDROM_WHEN_DISP
				if(!(pFsJpeg->gbfsPictureCD))
			#endif
		#ifdef SHOW_BOOKMARK_TIME//libing 2005-6-9 9:40		
			if(full_scrn!=MARK)	
		#endif
			psprintf(linebuf, " %02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss);         

            if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME)) // terry 2002/6/4 09:48PM : solve time in goto mode without '-'
        #ifdef NOT_SHOW_TIME_IN_JPG    //Maoyong for not display "-" when jpeg 2004.02.13      
			if(!Is_JPEG_STATE())		
		#endif	
        #ifdef NO_DISP_TIME_CLOCK_WHEN_KODAK    //sunzhh for not display "-" when kodak 2005.06.27      
			if(pFsJpeg->gbfsPictureCD != 1)		
		#endif			
			linebuf[0]='-';
        }
        else if(val&COOK_S_LANG)
        {           	
        	/* alan modifide 2002/5/30 09:53PM to cut SUP-LAN fit in display */
        	UINT8 *str=get_lang_name(id);
			BYTE len=strlen(str);
			
#if 0//def ALCO_DVD_UI		//shenyj mark 2006-9-4 03:37下午	
            *(str+MAX_ENG_WORDS) = '\0';
			strcpy(linebuf,str);
#else//#ifdef ALCO_PORTABLE			
			//terry,2002/6/25 10:37AM
			//<bug> get_lang_name return const string        				
			strcpy(linebuf,str);
            if (!IsOSDChinese()||((linebuf[0]>='A')&&(linebuf[0]<='Z'))) 
            {
				linebuf[MAX_ENG_WORDS]='\0';
            } else 
            {
				if (len>4){
#if defined(USE_TCHINESE_OSD)//2-10-9 17:51
					psprintf(linebuf+2,"%s",TCh_yu);
#elif defined(USE_KOREAN_OSD)		//clead korean 2003-10-23 
					        psprintf(linebuf+2,"%s",KCh_09);
					        #else
					psprintf(linebuf+2,"%s",Ch_yu2);
#endif
				}
			}
#endif//#ifdef ALCO_DVD_UI
                        
		} else if(val&COOK_S_MODE)
		{
			psprintf(linebuf,"%s",get_audio_mode());                
			
		}else if(full_scrn&MARK)//nono 2-6-22 0:28
		{
			psprintf(linebuf, "%d",id);
			
		}
        else
		{
                    #ifdef  NEW_DISPLAY_GOTO_OSD
                            if(cd_type_loaded==CDDVD)
                            {
                                if(pos==POS_DVD_TITLE)
                                    psprintf(linebuf, "T %02d/%02d", id, val);
                                else if(pos==POS_DVD_CHAP)
                                    psprintf(linebuf, "C %03d/%03d", id, val);
                            }
                            else
                                psprintf(linebuf, " TRK %d/%d", id, val);
                    #else
			psprintf(linebuf, "%d/%d",id,val);
                    #endif
		}
        } else {
			if(id==STR_OS_ICON_REP0) {
				id+=rep_mode; 
				if(rep_mode == REPEAT_DISC)         // maybe add another icon for repeat directory,panxing, 2002-3-13
					id--;
			}
		// mimitsai merge from dp2070/dp3240
#if defined(EASTECH_DVD_DP3240_D)||defined(EASTECH_DVD_DP2070_D)||defined(SHOW_DETAIL_MUSIC_JPEG_MPEG)
                        if( id == STR_OS_CDROM && pos == COOK_CD )  // yltseng v2.3
			{
			    #include "fsNAV.h"
			    if( pFsJpeg->gifsFuncBtn == FS_FUNC_MP3 )
			        #ifdef SHOW_DETAIL_MUSIC_JPEG_MPEG    // lxg 2006-8-7 08:15
			            psprintf(linebuf,"%s"," MP3");
			        #else	
			        	psprintf(linebuf,"\t""\x04");
			        #endif
			    else if( pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG )
			    	  #ifdef SHOW_DETAIL_MUSIC_JPEG_MPEG
			             psprintf(linebuf,"%s","JPEG");
			          #else	
			        	 psprintf(linebuf,"\t""\x05");
			          #endif
			    else if( pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER )
			    	#ifdef SHOW_DETAIL_MUSIC_JPEG_MPEG
			            psprintf(linebuf,"%s","MPEG");
			        #else	
			        	psprintf(linebuf,"\t""\x06");
			        #endif
                            else
			        psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][id]);
			}
                        else
                        {
			    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][id]);
			}
#endif

   #ifndef  SHOW_DETAIL_MUSIC_JPEG_MPEG    // lxg 2006-8-7 08:15
			//psprintf(linebuf,"%s",_OsdMessegeFont1[id][osd_font_mode]);               
			psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][id]);
   #endif
			
			if( (pos==COOK_CD)&&(t_disp%10==1) ) { //Jeff 20020607
				fontColor = DISP_ORANGE;
			}
			//else if( (id==STR_OS_ANGLE)||(id==STR_OS_SUBTITLE)||(id==STR_OS_AUDIO) )
            //strcat1(linebuf,":");
			
			if(id==STR_OS_ICON_SPK) {
			#ifdef JPEG_NO_SHOW_DISP_SPK//libing 2005-7-5 16:24	
				if(Is_JPEG_STATE())
				return;
			#endif	
			
			#ifdef INDIGO_STYLE_OSDUI// 2006-04-04, mimitsai modify
				fontColor = DISP_GREEN; 
			#else
				fontColor = DISP_YGREEN; //yellow-green
			#endif
			
                #ifdef USE_AMP_MUTE     //chenzhao20060114
                if (user_amp_mute)
                #else   
				if (user_mute) 
                #endif
					fontColor = DISP_GRAY; //gray              
			} else if(id==STR_OS_PBC) {    
				if ( IsPBCOn() ) 
					fontColor = DISP_YGREEN; //yellow-green
				else 
				//if 16Mb mode,not show PBC if PBC is OFF.
				//zhaoyanhua add 2003-11-13 15:51
				#if defined(SDRAM_16Mb_Mode)||defined(NOT_SHOW_PBC_IN_DISPLAY_WHEN_PBC_OFF)
				
					linebuf[0]= '\0';
				#else
				
					fontColor = DISP_GRAY; //gray
				#endif
			}
        }
		
        {//bad designed , we maybe try other way.
			//int len=strlen(linebuf);
			//if((len+pos)>=37)
			//linebuf[len-1]=0;
			io_write("8");
#ifdef SDRAM_16Mb_Mode
    //if( id == STR_OS_CDROM && pos == COOK_CD )

	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR	
			do_DispOSD0String(pos, 0, linebuf, 1, 0);
	#else
    	    #ifndef ALCO_DVD_UI
    		if(pos == COOK_CD ) // 20050726 mimitsai modify for all type disc to show red icon
            		do_DispOSD0String(pos, 0, linebuf, 3, 0); //0:blue, 1:black, 2: white, 3:gray
    	    	else
    	   #endif	
			do_DispOSD0String(pos, 0, linebuf, 2, 0);
	#endif
#elif defined( ALCO_PORTABLE)//shenyj add for alco 2006/03/25
            do_DispOSD0String(pos, 0, linebuf, 2, 0); 
    #else
			do_DispOSD0String(pos, 0, linebuf, fontColor, bkColor);
#endif
			
#ifndef DIV_GOTO_DISPLAY		
#ifdef NEW_GOTO//kenny 2002/4/13

#ifdef  NEW_DISPLAY_GOTO_OSD
                    if(full_scrn&GOTO) {
                        if((index_x>=5)&&(val&COOK_S_TIMER))
                            hi_light_time(pos);
                        else if(pos==POS_DVD_CHAP) 
                        {   
                        if (cd_type_loaded != CDROM)
                            hi_light_chapter(id, pos+OFFSET_CHAP);
                        }
                        else if(pos==POS_DVD_TITLE)
                            if(cd_type_loaded==CDDVD)
                                hi_light_title(id, pos+OFFSET_TITLE);
                            else
                                hi_light_title(id, pos+OFFSET_TRACK);
                        }
#else//#ifdef  NEW_DISPLAY_GOTO_OSD
			if(full_scrn&GOTO) {
				if((index_x>=5)&&(val&COOK_S_TIMER))
					hi_light_time(pos);
				else if(pos==COOK_CHP_VAL) 
				{	//Maoyong 2004.04.28 marked	MP3_DIRECT_SELECT
	//#ifdef MP3_DIRECT_SELECT  //zhaoyanhua add.  not Hilight  CHAP 3-7-16 16:17
				if (cd_type_loaded != CDROM)
	//#endif
					hi_light_chapter(id,pos);
				}
				else if(pos==COOK_TRK_VAL)
					hi_light_title(id,pos);
				
			}
#endif//#ifdef  NEW_DISPLAY_GOTO_OSD
#endif
#endif//end ifndef DIV_GOTO_DISPLAY
        }
}
#else //OSD_BMP_DISPLAY
/*
 * Description;
 *      Print Bmp icon, origin size 16*24 string and little size string 8*12 to osd_temp_buf
 *
 * INPUT:
 *      id  -->  when string, string id in _OsdMessegeFont1[][]
 *      val  -->  0-->no change, COOK_S_TIME, COOK_S_LANG
 *      pos   --> the xStart of display region 0; it has been defined in disp.c; it ranges 0 to 720

 * Creator : feeling
 * Date :  2004-8-14
 *
 */

void Print2OSDmem(int id,int val,UINT32 pos)
{
	//printf("id=%d\n", id);
	//printf("pos = %d\n", pos);
	BYTE    fontColor, bkColor; 
    UINT8 disc_hour,disc_minute,disc_second;
    UINT32 display_disc_time;

	//adjust xStart for cdrom
/*	if(cd_type_loaded == CDROM)
	{
		    #undef COOK_CD
		    #undef COOK_TRK
		    #undef COOK_TRK_VAL
	//	    #undef COOK_CHP
	//	    #undef COOK_CHP_VAL
		    #undef COOK_REP
		    #undef COOK_SPK
		    #undef COOK_CLOCK
		    #undef COOK_CLOCK_VAL

		    #define COOK_CD	COOK_CDROM
		    #define COOK_TRK	COOK_TRK_CDROM
		    #define COOK_TRK_VAL	COOK_TRK_VAL_CDROM
	//	    #define COOK_CHP	COOK_CHP_CDROM
	//	    #define COOK_CHP_VAL	COOK_CHP_VAL_CDROM
		    #define COOK_REP	COOK_REP_CDROM
		    #define COOK_SPK	COOK_SPK_CDROM
		    #define COOK_CLOCK	COOK_CLOCK_CDROM
		    #define COOK_CLOCK_VAL	COOK_CLOCK_VAL_CDROM

		if(pos < COOK_CLOCK)
		{
		    pos = pos + 24;
		}
		else
		{		    
		    pos = pos +6;
		}
	}//end if cd_type_loaded == CDROM
*/

#ifdef OSD_BMP_DISPLAY_CH_TIME
	display_disc_time = dNx_pg_tm-dPg_tm;
#elif defined (OSD_BMP_DISPLAY_TT_TIME)
	display_disc_time = disc_time;
#else
	display_disc_time = disc_time;
#endif
	tm2hms(display_disc_time,&disc_hour,&disc_minute,&disc_second);
	
#ifdef DISP_REGION_BOTTOM
	if(OSD_ShowBottomDisp() == 1)
        bkColor = DISP_SHADOW_CDROM;
    else
#endif//DISP_REGION_BOTTOM  	
		bkColor = DISP_SHADOW; //OSD shadow color
	
	fontColor = DISP_FONT_GRAY; //grey 10
    
	if(val) 
	{       
		fontColor = DISP_FONT_YELLOW; //yellow                      

#ifndef DIV_GOTO_DISPLAY//zhaoyanhua add 03-10-22 10:58
		if(full_scrn&GOTO)
		{    
#ifdef NEW_GOTO//kenny 2002/4/13
			if(val&COOK_S_TIMER) 
			{
				if(index_x>=5)
				{
					time_trans2hms();    //xyy 2003-7-29 11:42       
					if(cd_type_loaded == CDDVD)
					{
					    //draw the clock val, and it can be changed in different define on customer demand       
					    #ifdef OSD_BMP_DISPLAY_TT_TIME
					    psprintf(linebuf, "TT %02d:%02d:%02d/%02d:%02d:%02d", goto_hour, goto_min, goto_sec,disc_hour,disc_minute,disc_second);            
					    #elif defined(OSD_BMP_DISPLAY_CH_TIME)
					    psprintf(linebuf, "CH %02d:%02d:%02d/%02d:%02d:%02d", goto_hour, goto_min, goto_sec,disc_hour,disc_minute,disc_second);            
					    #else
					    psprintf(linebuf, "%02d:%02d:%02d/%02d:%02d:%02d", goto_hour, goto_min, goto_sec,disc_hour,disc_minute,disc_second);            
					    #endif
					    }//if(cd_type_loaded == CDDVD)
					    else
					    {
						    psprintf(linebuf, "%02d:%02d:%02d/%02d:%02d:%02d", goto_hour, goto_min, goto_sec,disc_hour,disc_minute,disc_second);            
				    } 
				}//if(index_x>=5) 
				else
				{
					if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME)) // terry 2002/6/4 09:48PM : solve time in goto mode without '-'
					{
                        #ifdef NOT_SHOW_TIME_IN_JPG    //Maoyong for not display "-" when jpeg 2004.02.13      
                        if(!Is_JPEG_STATE())		
                        #endif	

                        #ifdef NO_DISP_TIME_CLOCK_WHEN_KODAK    //sunzhh for not display "-" when KODAK 2004.02.13      
                        if(pFsJpeg->gbfsPictureCD != 1)		
                        #endif	
                        
						//draw remain time in display page 2 or 3
                        psprintf(linebuf, "-%02d:%02d:%02d", goto_hour, goto_min, goto_sec);
                    }//if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME))
					else
					{					    
						if(cd_type_loaded == CDDVD)
						{						    
						    #ifdef OSD_BMP_DISPLAY_TT_TIME
						    psprintf(linebuf, "TT %02d:%02d:%02d/%02d:%02d:%02d", goto_hour, goto_min, goto_sec,disc_hour,disc_minute,disc_second);            
						    #elif defined(OSD_BMP_DISPLAY_CH_TIME)
						    psprintf(linebuf, "CH %02d:%02d:%02d/%02d:%02d:%02d", goto_hour, goto_min, goto_sec,disc_hour,disc_minute,disc_second);            
						    #else
						    psprintf(linebuf, "%02d:%02d:%02d/%02d:%02d:%02d", goto_hour, goto_min, goto_sec,disc_hour,disc_minute,disc_second);            
						    #endif
						    }//if(cd_type_loaded == CDDVD)
						    else
						    {						    
							    psprintf(linebuf, "%02d:%02d:%02d/%02d:%02d:%02d", goto_hour, goto_min, goto_sec,disc_hour,disc_minute,disc_second);        
					    }
					}//if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME))

				}
			} else //if(val&COOK_S_TIMER) 
			{
				if(pos!=COOK_CHP_VAL) 
				{//title            
					if(dvd_title) 
						id=dvd_title;
					if (cd_type_loaded == CDROM)
						psprintf(linebuf, "%04d/%02d",id,val);
					else
					    psprintf(linebuf, "%02d/%02d",id,val);

				} //if(pos!=COOK_CHP_VAL) 
				else 
				{
					if(dvd_chapter) 
						id=dvd_chapter;
					psprintf(linebuf, "%03d/%03d",id,val);          
				}//if(pos!=COOK_CHP_VAL) 
			}   //if(val&COOK_S_TIMER) 
#else   //#ifndef NEW_GOTO
			if(val&COOK_S_TIMER) 
			{
				if(index_x==2)
				 {
					UINT32 time=goto_time;
                    
					bkColor = DISP_GBLUE;                        
					fontColor = DISP_WHITE; 
					goto_time=goto_time%10000000;
					goto_sec=time%100;            
					time=time/100;
					goto_min=time%100;
					time=time/100;
					goto_hour=time%100;             
					psprintf(linebuf, "%02d:%02d:%02d", goto_hour, goto_min, goto_sec);            
				}//if(index_x==2)
				else 
				{
                    psprintf(linebuf, "%02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss);
                }
			} //if(val&COOK_S_TIMER) 
			else 
			{
				if(pos!=COOK_CHP_VAL)
                {
                    //title          
					if(index_x==0)
                    {
						bkColor = DISP_GBLUE;                                
						fontColor = DISP_WHITE; 
					}
                    
					if(index_x!=2) {
						if(dvd_title) {
							if(dvd_title>val)
								dvd_title=dvd_title%10;
                            
							id=dvd_title;
						}
					}//if(index_x!=2)
					
				    psprintf(linebuf, "%02d",id);                   
			    } //if(pos!=COOK_CHP_VAL)
			    else 
			    {
					if(index_x==1) 
					{
						bkColor = DISP_GBLUE;    
						fontColor = DISP_WHITE; 
					}
					
					if(index_x!=2) {
						if(dvd_chapter) {
							if(dvd_chapter>val)
								dvd_chapter=dvd_chapter%10;
                            
							id=dvd_chapter;
						}
					}//if(index_x!=2)
					psprintf(linebuf, "%03d",id);   
				}//if(pos!=COOK_CHP_VAL)
                
                io_write("9");
#ifdef SDRAM_16Mb_Mode 
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
				do_DispOSD0String(pos, 0, linebuf, 1, 0);
	#else
				do_DispOSD0String(pos, 0, linebuf, 2, 0); 
	#endif
#else
				if(cd_type_loaded != CDDVD && pos == COOK_TRK_VAL)//TRK occupy three char
					do_DispOSD0LittleString(pos+16,7,linebuf,fontColor,bkColor);
				else
					do_DispOSD0LittleString(pos,7,linebuf,fontColor,bkColor);
				
				do_DispOSD0String(pos, 2, linebuf_oriCh, fontColor, bkColor); 
#endif				
#ifdef DISP_REGION_BOTTOM
				if(OSD_ShowBottomDisp() == 1)
			        bkColor = DISP_SHADOW_CDROM;
			    else
#endif//DISP_REGION_BOTTOM			    	    
				    bkColor = DISP_SHADOW; //OSD shadow color
				
				if(pos==COOK_CHP_VAL) {
					pos+=3*DISP_LITTLE_CHAR_WIDTH;
					psprintf(linebuf, "/%03d",val); 
				} else {
					pos+=2*DISP_LITTLE_CHAR_WIDTH;
					psprintf(linebuf, "/%02d",val);
				}
			}               
#endif//NEW_GOTO
		}//end if full_scrn&GOTO
			
        else 
#endif//end ifndef DIV_GOTO_DISPLAY		
			
	if(val&COOK_S_TIMER)
	{
	        
		if ((cd_type_loaded == CDROM) && (Is_JPEG_STATE()))  // Add by David for Jpeg time display bug 2003-12-1 16:28
        {
            show_time_hh = 0;
            show_time_mm = 0;
            show_time_ss = 0;
        }            
#ifdef NOT_SHOW_TIME_IN_JPG    //axel 2004/1/8 04:58PM        
		#ifdef NOSHOW_CDROM_WHEN_DISP  //zhangyu 2004-6-14 20:35
		if(!(pFsJpeg->gbfsPictureCD))
		#endif
		if(Is_JPEG_STATE())
			psprintf(linebuf, "       ");
		else
#endif	//NOT_SHOW_TIME_IN_JPG

#ifdef NOSHOW_CDROM_WHEN_DISP
		if(!(pFsJpeg->gbfsPictureCD))		    
#endif


        if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME)) // terry 2002/6/4 09:48PM : solve time in goto mode without '-'
        {
            #if defined(NOT_SHOW_TIME_IN_JPG) && defined(NO_DISP_TIME_CLOCK_WHEN_KODAK)    //Maoyong for not display "-" when jpeg 2004.02.13      
            if(!Is_JPEG_STATE())		
            #endif	
			{	
				psprintf(linebuf, "-%02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss);
 			}
		}//if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME))
        else
		{			            	    
			if(cd_type_loaded == CDDVD)
			{
			    #ifdef OSD_BMP_DISPLAY_TT_TIME
			    psprintf(linebuf, "TT %02d:%02d:%02d/%02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss,disc_hour,disc_minute,disc_second);            
			    #elif defined(OSD_BMP_DISPLAY_CH_TIME)
			    psprintf(linebuf, "CH %02d:%02d:%02d/%02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss,disc_hour,disc_minute,disc_second);            
			    #else
			    psprintf(linebuf, "%02d:%02d:%02d/%02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss,disc_hour,disc_minute,disc_second);            
			    #endif
            }
			else
			{
				psprintf(linebuf, "%02d:%02d:%02d/%02d:%02d:%02d", show_time_hh, show_time_mm, show_time_ss,disc_hour,disc_minute,disc_second);            
			}
		}//end  if((remain==DISC_REMAIN_TIME)||(remain==TRK_REMAIN_TIME)) // terry 2002/6/4 09:48PM : solve time in goto mode without '-'

        }//end if(val&COOK_S_TIMER)

        
        else if(val&COOK_S_LANG)
        {           	
        	/* alan modifide 2002/5/30 09:53PM to cut SUP-LAN fit in display */
        	UINT8 *str=get_lang_name(id);
		    BYTE len=strlen(str);
			
			//terry,2002/6/25 10:37AM
			//<bug> get_lang_name return const string        				
		    strcpy(linebuf,str);
    		if (!IsOSDChinese()||((linebuf[0]>='A')&&(linebuf[0]<='Z'))) 
    		{
    			linebuf[MAX_ENG_WORDS]='\0';
    		} 
    		else 
    		{
    			if (len>4)
    			{
#if defined(USE_TCHINESE_OSD)//2-10-9 17:51
				    psprintf(linebuf+2,"%s",TCh_yu);
#else
			        #ifdef USE_KOREAN_OSD		//clead korean 2003-10-23 
			        psprintf(linebuf+2,"%s",KCh_09);
			        #else
				    psprintf(linebuf+2,"%s",Ch_yu2);
                    #endif
#endif //USE_TCHINESE_OSD
			}//end if(len>4)
		}//	if (!IsOSDChinese()||((linebuf[0]>='A')&&(linebuf[0]<='Z'))) 

	} //end   else if(val&COOK_S_LANG)

	else if(val&COOK_S_MODE)
	{
		psprintf(linebuf,"%s",get_audio_mode());                
			
	}else if(full_scrn&MARK)//nono 2-6-22 0:28
	{
		psprintf(linebuf, "%d",id);			
	}
    else//tt val,chapter val
	{
		if(cd_type_loaded == CDROM)
		    	psprintf(linebuf,"%03d/%03d",id,val);
		else
		psprintf(linebuf, "%02d/%02d",id,val);
	}
        
	if(cd_type_loaded != CDDVD && pos == COOK_TRK_VAL)//TRK occupy three char
		do_DispOSD0LittleString(pos+16,12,linebuf,fontColor,bkColor);
	else
		do_DispOSD0LittleString(pos,12,linebuf, fontColor, bkColor);//display title val, chapter val,  time, audio val, and audio type


}//end if val

	else 
	{
		if(id==STR_OS_ICON_REP0) 
		{
			id+=rep_mode; 
			if(rep_mode == REPEAT_DISC)         // maybe add another icon for repeat directory,panxing, 2002-3-13
				id--;
		}

		linebuf[0]= '\0';
		
		if( (pos==COOK_CD) ) //display cd type bmp
		{ 
			switch(id)
			{
				case STR_OS_CDDA:
                    OSD_LayoutBmpDisplay(CD_BMP);
                    break;
				case STR_OS_CDROM:
					#ifdef CDDA_USE_MP3_GUI
					if( is_cdda_var )
						OSD_LayoutBmpDisplay(CD_BMP);
					else
					#endif
                    OSD_LayoutBmpDisplay(CDROM_BMP);
                    break;
				case STR_OS_VCD10:
                //case STR_OS_VCD20:				    
                    OSD_LayoutBmpDisplay(VCD_BMP);
                    break;
				case STR_OS_SVCD:				    
                    OSD_LayoutBmpDisplay(SVCD_BMP);
                    break;
				case STR_OS_DVD:				    
                    OSD_LayoutBmpDisplay(DVD_BMP);
                    break;
			}//end switch    
		}//end if( (pos==COOK_CD) )


        //display TT ,CH and TRK char
		else if ( (id == STR_OS_TT) || (id == STR_OS_CHP) || (id == STR_OS_TRACK))
		{
			psprintf(linebuf_oriCh,"%s",_OsdMessegeFont1[osd_font_mode][id]);
		#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR		
			do_DispOSD0String(pos, 2, linebuf_oriCh, 1, 0);
		#else
			do_DispOSD0String(pos, 2, linebuf_oriCh, fontColor, bkColor);
		#endif			
		}

        //display little string of t_disp = 2,  but not display string icon of audio , subtitle, angle, repeat, and speak
		else if( (pos != COOK_AUDIO) && (pos != COOK_SUBTITLE)
		    && (pos != COOK_ANGLE) && (pos != COOK_REP) 
		    && (pos != COOK_SPK) && (pos != COOK_CLOCK)
		    && (pos != COOK_PBC) && (pos != COOK_TRK)
		    && (pos != COOK_CHP) && (pos != COOK_SPK_MP3))
		{
			psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][id]);
			do_DispOSD0LittleString(pos,12,linebuf, fontColor, bkColor);

		}

		
		else if(id==STR_OS_ICON_SPK)
		{
			OSD_LayoutBmpDisplay(VOLUME_ICON_BMP);
            #ifdef USE_AMP_MUTE     //chenzhao20060114
            if (user_amp_mute)
            #else   
			if (user_mute) 
            #endif
			{
			    OSD_LayoutBmpDisplay(MUTE_ICON_BMP);
			}
		} 
		else if(id==STR_OS_PBC) //show PBC
		{    
			if ( IsPBCOn() ) 
				fontColor = DISP_YGREEN; //yellow-green
			else 
				//if 16Mb mode,not show PBC if PBC is OFF.
				//zhaoyanhua add 2003-11-13 15:51
				#ifdef SDRAM_16Mb_Mode	
				linebuf[0]= '\0';
				#else
				fontColor = DISP_GRAY; //gray
				#endif

			psprintf(linebuf_oriCh,"%s",_OsdMessegeFont1[osd_font_mode][id]);
		#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR		
			do_DispOSD0String(pos, 2, linebuf_oriCh, 1, 0);
		#else
			do_DispOSD0String(pos, 2, linebuf_oriCh, fontColor, bkColor);
		#endif				
		}//end else if(id==STR_OS_PBC) 
		else if(id == STR_OS_SUBTITLE)//show subtitle icon
		{
			OSD_LayoutBmpDisplay(SUB_TITLE_BMP);
		}//end else if(id==STR_OS_SUBTITLE)
		else if(id == STR_OS_ANGLE)//show angle icon
		{
			OSD_LayoutBmpDisplay(ANGLE_BMP);
		}//end else if(id==STR_OS_ANGLE)
		else if(id == STR_OS_AUDIO)//show audio language icon
		{
			OSD_LayoutBmpDisplay(LANGUAGE_BMP);
		}//end else if(id==STR_OS_ANGLE)

		else if(id == STR_OS_ICON_REP1)//show repeat1 icon
		{
			OSD_LayoutBmpDisplay(REPEAT_1_BMP);
		}

		else if (id == STR_OS_ICON_REPD)//show repeat all icon
		{
			OSD_LayoutBmpDisplay(REPEAT_ALL_BMP);
		}

		else if (id == STR_OS_ICON_REP0)//show repeat close icon
		{
			OSD_LayoutBmpDisplay(REPEAT_CLOSE_BMP);
		}
        }
		
        {
		io_write("8");
//#ifdef SDRAM_16Mb_Mode
//		do_DispOSD0String(pos, 0, linebuf, 2, 0);
//#else
	//	do_DispOSD0String(pos, 2, linebuf_oriCh, fontColor, bkColor);
//		do_DispOSD0LittleString(pos,12,linebuf, fontColor, bkColor);
//#endif
			
#ifndef DIV_GOTO_DISPLAY		
#ifdef NEW_GOTO//kenny 2002/4/13

#ifdef  NEW_DISPLAY_GOTO_OSD
		if(full_scrn&GOTO) 
		{
			if((index_x>=5)&&(val&COOK_S_TIMER))
				hi_light_time(pos);
			else if(pos==POS_DVD_CHAP) 
			{   
                if (cd_type_loaded != CDROM)
                    hi_light_chapter(id, pos+OFFSET_CHAP);
			}
			else if(pos==POS_DVD_TITLE)
                if(cd_type_loaded==CDDVD)
                    hi_light_title(id, pos+OFFSET_TITLE);
 			else
				hi_light_title(id, pos+OFFSET_TRACK);
		}
#else//#ifdef  NEW_DISPLAY_GOTO_OSD
		if(full_scrn&GOTO)
		{
			if((index_x>=5)&&(val&COOK_S_TIMER))
			{			    
				hi_light_time(pos);
			}				
			else if(pos==COOK_CHP_VAL) 
			{	//Maoyong 2004.04.28 marked	MP3_DIRECT_SELECT
				if (cd_type_loaded != CDROM)
					hi_light_chapter(id,pos);
			}
			else if(pos==COOK_TRK_VAL)
			{	
				if(cd_type_loaded != CDDVD)
                    hi_light_title(id,pos + 16);//TRK occupy three char
			   	 else
					hi_light_title(id,pos);//TT occupy two char
			}					
		}
#endif//#ifdef  NEW_DISPLAY_GOTO_OSD
#endif//NEW_GOTO
#endif//end ifndef DIV_GOTO_DISPLAY
    }
}
#endif //OSD_BMP_DISPLAY


#ifdef DIV_GOTO_DISPLAY   

/*
 * Description:
 *      Draw informaiton to OSD.
 *
 */	
void PrintGotoInfo2OSD(int id, int val,int pos,int type,BYTE need_hi)
{
    
	memset(linebuf,0,40);
   
    //clear value 
    //zhaoyanhua add 2003-11-11 10:51
    if((index_x == 0))
        dvd_title = 0;
    else if(index_x == 2)
        dvd_chapter = 0;
    else if (index_x == 5)
        goto_time = 0;

   
	if(val!= 0)
	{
		switch(type)
		{
			case TIME: 	
				if((index_x>=5))
				{
           			time_trans2hms();    //xyy 2003-7-29 11:42       
					psprintf(linebuf, "%02d:%02d:%02d ", goto_hour, goto_min, goto_sec);            
				}
				else
				{
					psprintf(linebuf, "%02d:%02d:%02d ", goto_hour, goto_min, goto_sec);            
				}
					
				break;
		
			case TITLE:
			    //NOTE:
			    //index_x<=1  when input show correct value
			    //index_x>1 && dvd_title != id after select,show correct selected value.
			    //zhaoyanhua add 2003-11-11 11:30
			#ifdef MP3_DIRECT_SELECT//zhaoyanhua add 2004-2-16 11:01
			    if(((cd_type_loaded == CDROM) && ((index_x <= 3) || ((index_x >3) &&(dvd_title)&&(dvd_title!= id)))) 
			       ||((cd_type_loaded != CDROM) && ((index_x <= 1) || ((index_x >1) &&(dvd_title)&&(dvd_title!= id)))) 
			       )
			#else
			    if((index_x <= 1) || ((index_x >1) &&(dvd_title)&&(dvd_title!= id)))
	        #endif//#ifdef MP3_DIRECT_SELECT			     
			        id = dvd_title;        
				
			#ifdef MP3_DIRECT_SELECT	//zhaoyanhua add 3-7-16 16:47
				if (cd_type_loaded == CDROM)
					psprintf(linebuf, "%04d/%02d  ",id,val);
				else
					psprintf(linebuf, "%02d/%02d  ",id,val);
			#else
				psprintf(linebuf, "%02d/%02d  ",id,val);                  
		
			#endif
				
				break;
		
			case CHARPTER:
				
			    //NOTE:
			    //index_x>=2 && index-x<=4  when input show correct value
			    //index_x>4 && dvd_chapter != id after select,show correct selected value.
			    //zhaoyanhua add 2003-11-11 11:30
			    if (((index_x >=2)&&(index_x <=4)) || ((index_x>4)&&(dvd_chapter != id) &&(dvd_chapter))) 
					id=dvd_chapter;
			
				psprintf(linebuf, "%03d/%03d  ",id,val); 
				break;	
			default:
				break;
        }
}

	else if((!val) &&(!type))
	{
		psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][id]);
	}
	
	
	if(val == 0)//draw words. black
		osd_DrawRegionString(pos,0,linebuf, REGION2_FONTCOLOR, REGION2_BKCOLOR, 2);
	else
		osd_DrawRegionString(pos,0,linebuf, REGION2_NUMCOLOR, REGION2_BKCOLOR, 2);
	
	if((need_hi)&&(val))
	{
	    
		if(((index_x>=5)&&(index_x<=10))&&(type == TIME))
			hi_light_time(pos);
		else if(((index_x >=2)&&(index_x<=4)) &&(type == CHARPTER))
		{
	#ifdef MP3_DIRECT_SELECT  //zhaoyanhua add.  not Hilight  CHAP 3-7-16 16:17
			if (cd_type_loaded != CDROM)
	#endif
			//hi_light_chapter(id,pos);
			hi_light_chapter(dvd_chapter,pos);//
		}
    #ifdef MP3_DIRECT_SELECT//zhaoyanhua add 2004-2-16 11:08
		else if(((index_x<=3) &&(type == TITLE) && (cd_type_loaded == CDROM))
		        ||((index_x<=1) &&(type == TITLE) && (cd_type_loaded != CDROM)))
    #else
		else if((index_x<=1) &&(type == TITLE))
    #endif        		
			//hi_light_title(id,pos);	
			hi_light_title(dvd_title,pos);					
	}
}

void ClearRegion2(void)
{
    //wanghaoying modified as zhaoyanhua told, 2003-11-13 18:35
    //the forth and the fifth parameter means that to use transparence color
	//must clear osd .
	osd_DrawRegionString(GOTO_TRK0,0,"                          ",0,0,2);

}


/*
 *Description:
 *     page:
 *     need_hi: if 0:not hilight
 *              if 1: hilight   
 */
void ShowSearchPage(BYTE page,BYTE need_hi)
{
	switch(page)
	{
		case 0:
			//show charpter:title
    		//can search charpter and title
    		if(cd_type_loaded!=CDDVD) 
			{ 
				int tt;
					
				PrintGotoInfo2OSD(STR_OS_SELECT,0,GOTO_TRK0,0,need_hi); 
				PrintGotoInfo2OSD(STR_OS_TRACK,0,GOTO_TRK0+4,0,need_hi);          
				if(cd_type_loaded==CDROM) 
				{
					extern UINT16 mp3_file_count(void);
					tt=mp3_file_count();//nono 2-4-22 14:05 for fuss           
					if(play_state==VCD_STATE_STOP)                                        
						disp_trk_now=tt;//nono 2-4-22 14:05 for fuss           
				} 
				else 
				{
					tt=cd_total_trk();                                        
			
				}
				osd_DrawRegionString(GOTO_TRK0+8,0,"          ",REGION2_BKCOLOR,REGION2_BKCOLOR,2);
				PrintGotoInfo2OSD(disp_trk_now,tt,GOTO_TRK0 + 10,TITLE,need_hi);
				
			} 
			else 
			{            
				osd_DrawRegionString(GOTO_TRK0,0,"                      ",REGION2_RCOLOR,REGION2_BKCOLOR,2);
				PrintGotoInfo2OSD(STR_OS_TT,0,GOTO_TRK0,0, need_hi);	
				PrintGotoInfo2OSD(get_tt_info(DISP_TT),get_tt_info(DISP_TT_Ns),GOTO_TRK0_VAL,TITLE,need_hi);               
				PrintGotoInfo2OSD(STR_OS_CHP,0,GOTO_CHP0,0, need_hi);        
				PrintGotoInfo2OSD(get_tt_info(DISP_CH),get_tt_info(DISP_CH_Ns),GOTO_CHP0_VAL,CHARPTER, need_hi);
			}
    		break;
    	case 1:
    		//show charpter : time
    		if(cd_type_loaded == CDDVD)
    		{
    			
    			osd_DrawRegionString(GOTO_TRK0,0,"                      ",REGION2_RCOLOR,REGION2_BKCOLOR,2); //linrc add 2004-7-6 14:28 I find it is a bug.so I modyfy
    			PrintGotoInfo2OSD(STR_OS_TT,0,GOTO_TRK1,0,need_hi);  
                                  #ifndef  NINTAUS_DVD	//2004-2-24 09:31张宇M	
				PrintGotoInfo2OSD(get_tt_info(DISP_TT),get_tt_info(DISP_TT_Ns),GOTO_TRK1_VAL,TITLE, need_hi); 
                                  #endif				
				PrintGotoInfo2OSD(STR_OS_TIME,0,GOTO_S_TIMER,0,need_hi);                
				PrintGotoInfo2OSD(0,1,GOTO_TIMER_VAL,TIME,need_hi);              
    		}
    		else//VCD/CD    		
    		{
    			
    			//PrintGotoInfo2OSD(STR_OS_TRACK,0,GOTO_TRK1,0,need_hi);          
    			PrintGotoInfo2OSD(STR_OS_DISCTIME,0,GOTO_TRK1,0,need_hi);                
				osd_DrawRegionString(GOTO_TRK1+8,0,"          ",REGION2_BKCOLOR,REGION2_BKCOLOR,2);
				PrintGotoInfo2OSD(0,1,GOTO_TRK1+10,TIME,need_hi);
    		}
    		break;
    	case 2:
    		if(cd_type_loaded == CDDVD)
    		{
    			//osd_DrawRegionString(GOTO_TRK0,0,"                      ",3,3,2);
    			PrintGotoInfo2OSD(STR_OS_CHP,0,GOTO_CHP2,0, need_hi);        
                             #ifndef NINTAUS_DVD	//2004-2-24 09:31张宇M			
				PrintGotoInfo2OSD(get_tt_info(DISP_CH),get_tt_info(DISP_CH_Ns),GOTO_CHP2_VAL,CHARPTER, need_hi);
			 #endif
				PrintGotoInfo2OSD(STR_OS_TIME,0,GOTO_S_TIMER,0,need_hi);                
				PrintGotoInfo2OSD(0,1,GOTO_TIMER_VAL,TIME,need_hi);              
    		}
    		else// VCD/CD  		
    		{
    			PrintGotoInfo2OSD(STR_OS_TRACK,0,GOTO_TRK1,0,need_hi);          
    			PrintGotoInfo2OSD(STR_OS_TIME,0,GOTO_TRK1+4,0,need_hi);                
				osd_DrawRegionString(GOTO_TRK1+8,0,"        ",REGION2_BKCOLOR,REGION2_BKCOLOR,2);
				PrintGotoInfo2OSD(0,1,GOTO_TRK1+10,TIME,need_hi);  
    		}
    		break;
    	default:
    		break;
    		 
	}
	
	timeout_osd[2]= 3*OSD_TIMEOUT;
}
#endif//end DIV_GOTO_DISPLAY

#ifdef DISPLAY_MP4_VER_PI	
static inline void disp_mp4_ver_pi(void)
{   	
	int i;
   	avi_video_info info;		
   	get_avi_video_version(&info);
   	   	
   	strcpy(linebuf, "MPEG4");  
	do_DispOSD0String(COOK_CD, 0, linebuf, DISP_ORANGE, DISP_SHADOW);
	
	//version Promt symbol	& version
	strcpy(linebuf, "VER");
	do_DispOSD0String(COOK_TRK+2, 0, linebuf, DISP_WHITE, DISP_SHADOW);	
	for(i = 0; i<5; i++)
		linebuf[i] = info.version_str[i];
	linebuf[5] = '\0';		       
   	do_DispOSD0String(COOK_TRK_VAL+2, 0, linebuf, DISP_YGREEN, DISP_SHADOW);	
   	  	
   	strcpy(linebuf, "SIZE");
	do_DispOSD0String(COOK_SPK+8, 0, linebuf, DISP_WHITE, DISP_SHADOW);		        			
	psprintf(linebuf, "%dX%d", info.width,info.height);
   	do_DispOSD0String(COOK_SPK+8+5, 0, linebuf, DISP_YGREEN, DISP_SHADOW);
}
#endif

#ifdef DISPLAY_MP4_AV_INFO  //Maoyong 2004.06.29. display MP4 video codec mode and audio coding mode
static inline void disp_mp4_av_info(void)
{
    int i;
   	avi_video_info info;

   	get_avi_video_version(&info);

   	strcpy(linebuf, "MPEG4");
	do_DispOSD0String(COOK_CD+1, 0, linebuf, DISP_ORANGE, DISP_SHADOW);

	//version Promt symbol	& version
	strcpy(linebuf, "VIDEO");
	do_DispOSD0String(COOK_TRK+2, 0, linebuf, DISP_WHITE, DISP_SHADOW);
	for(i = 0; i<5; i++)
		linebuf[i] = info.version_str[i];
	linebuf[5] = '\0';
   	do_DispOSD0String(COOK_TRK+8, 0, linebuf, DISP_YGREEN, DISP_SHADOW);

	psprintf(linebuf, "%dX%d", info.width,info.height);
   	do_DispOSD0String(COOK_TRK+8+6, 0, linebuf, DISP_YGREEN, DISP_SHADOW);

    //display dsp audio code mode
    strcpy(linebuf, "AUDIO");
	do_DispOSD0String(COOK_TRK_VAL+18, 0, linebuf, DISP_WHITE, DISP_SHADOW);
	printf("=========== coding mode now : %x==============\n", coding_mode_now);
    if( coding_mode_now == AUDIF_CODING_MODE_AC3 )
        strcpy(linebuf, "AC3 ");
    else if( coding_mode_now == AUDIF_CODING_MODE_LPCM )
        strcpy(linebuf, "LPCM");
    else if( coding_mode_now == AUDIF_CODING_MODE_WMA )
        strcpy(linebuf, "WMA ");
    else if( coding_mode_now == AUDIF_CODING_MODE_DTS )
        strcpy(linebuf, "DTS ");
    else if( coding_mode_now == AUDIF_CODING_MODE_MP3 )
        strcpy(linebuf, "MP3 ");
    else
        strcpy(linebuf, "    ");
   	do_DispOSD0String(COOK_TRK_VAL+18+6, 0, linebuf, DISP_YGREEN, DISP_SHADOW);
   	
}
#endif

//Maoyong 2004.05.24 for display HDCD/DTSCD/CDG... sub cd type info
void DispCDSubtypeInfo(void)
{
#ifdef SDRAM_16Mb_Mode
    #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
	#ifdef JUST_SHOW_CD_TYPE		//Maoyong for NINTAUS not show CD ICON but type in icon pos 2004.02.11
	do_DispOSD0String(COOK_CD, 0, linebuf, 1, 0);
	#else
	do_DispOSD0String(COOK_PBC, 0, linebuf, 1, 0);
	#endif
    #else	
	#ifdef JUST_SHOW_CD_TYPE		//Maoyong for NINTAUS not show CD ICON but type in icon pos 2004.02.11
	do_DispOSD0String(COOK_CD, 0, linebuf, 2, DISP_SHADOW);
	#else
	do_DispOSD0String(COOK_PBC, 0, linebuf, 2, DISP_SHADOW);
	#endif		
    #endif			
#else
	#ifdef JUST_SHOW_CD_TYPE		
	do_DispOSD0String(COOK_CD, 0, linebuf, DISP_ORANGE, DISP_SHADOW); //Jeff 20020413
    #else
	do_DispOSD0String(COOK_PBC, 0, linebuf, DISP_YGREEN, DISP_SHADOW); //Jeff 20020413
	#endif			
#endif
} 

//Maoyong 2004.05.24 moved from DispCookOSD0 for t_disp == 0
#if defined(SUPPORT_USB)
BYTE IsUSBCardReader(void);
#endif
void DispCDTypeInfo(void)
{
    
    
    #ifndef PMP_DVD   ////////////////////////////////YANGLI   ADD   FOR HDD DISPL;AY
    //for special Card/Card reader meida type
    #if defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE) //Maoyong 2004.05.24
    #ifdef DISPLAY_MEDIA_TYPE           
    if( (cd_type_loaded == CDROM) && (media_type == MEDIA_CARD)  )
    {
        //Usb card and SD/MS/CF... treated as card, USB single device display USB
        #ifdef SUPPORT_USB
        if( (storage_type & USB_DEVICE) && (!IsUSBCardReader()) )
            strcpy(linebuf, "USB  ");           
        else
        #endif
            	strcpy(linebuf, "CARD ");   //maybe can show card type/number for CARD_STORAGE
              #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR    
        		do_DispOSD0String(0, 0, linebuf, 1, 0);  
		#else
			do_DispOSD0String(0, 0, linebuf, DISP_ORANGE, DISP_SHADOW);  
		#endif
        return; 
    } 
    #endif
    #endif
    
    #if  defined( SKYWORTH_DVD)||defined(NOSHOW_CDROM_WHEN_DISP)	//wthsin 031021
	if(cd_type_loaded==CDROM)  //CD-ROM Disk
	{
	    	if(Is_MP3_STATE())
	    	{
	        	io_write("4");	
	        	strcpy(linebuf, "MP3 ");
              #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR    
			do_DispOSD0String(0, 0, linebuf, 1, 0);
		#else			
	       	do_DispOSD0String(0, 0, linebuf, DISP_ORANGE, DISP_SHADOW);
		#endif
	    	}
	    	else if(Is_JPEG_STATE())	
		{
	         
	        	if(pFsJpeg->gbfsPictureCD) //Kodak Picture CD
	        	{	
	            	#ifndef NOSHOW_CDROM_WHEN_DISP  //zhangyu 2004-6-14 19:35
	     	    		Print2OSDmem(osd_cd_id[0],0,COOK_CD);
	            	#else
	            		strcpy(linebuf, "KODAK ");
              	   #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
				do_DispOSD0String(0, 0, linebuf, 1, 0);
			   #else
	            		do_DispOSD0String(0, 0, linebuf, DISP_ORANGE, DISP_SHADOW);
			   #endif
	     	     		io_write("4");	
	            		strcpy(linebuf, "PICTURE CD");
			   #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
				do_DispOSD0String(25, 0, linebuf, 1, 0);
			   #else				
		     		do_DispOSD0String(25, 0, linebuf, DISP_ORANGE, DISP_SHADOW);
			   #endif
	            	#endif
	       	 }
	        	else 	          
	        	{	
	            		io_write("4");	
	            		strcpy(linebuf, "JPEG");
			   #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
				do_DispOSD0String(0, 0, linebuf, 1, 0);	
			   #else
		     		do_DispOSD0String(0, 0, linebuf, DISP_ORANGE, DISP_SHADOW);	
			   #endif
		    	}  	
		}	
		else
		{
		     io_write("4");	
		     strcpy(linebuf, "MPEG");
		#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR	
		     do_DispOSD0String(0, 0, linebuf, 1, 0);	
		#else
		     do_DispOSD0String(0, 0, linebuf, DISP_ORANGE, DISP_SHADOW);	
		#endif
		}	
    	}
	else //if(cd_type_loaded==CDROM)  //CD-ROM Disk
	#endif 
		  
	#ifdef SHOW_DVD_ROM//20040210
	if( (is_svo_dvd())&&(cd_type_loaded==CDROM) ) 
	{
	    	strcpy(linebuf, "DVDROM");
	   #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
		 do_DispOSD0String(0, 0, linebuf, 1, 0);
	   #else
	   	 do_DispOSD0String(0, 0, linebuf, DISP_ORANGE, DISP_SHADOW);	
	   #endif
	}else
	#endif//SHOW_DVD_ROM
	#ifdef JUST_SHOW_CD_TYPE	
	if( cd_type_loaded != CDDA)	//Maoyong 2004.02.11
	#endif
    	{
        #ifdef DVD_SERVO
        #if 1//20040219
		if ((cd_type_loaded == CDVCD10) && (is_svo_dvd()))
		    Print2OSDmem(osd_cd_id[CDDVD],0,COOK_CD);
		else
        #endif
        #endif // DVD_SERVO
        #ifdef CDDA_USE_MP3_GUI
        	if(is_cdda_var)
			Print2OSDmem(osd_cd_id[CDDA],0,COOK_CD);
		else
	 #endif		
		#ifdef 	ALCO_DIVX_UI//shenyj add for alco 12/09	
		if((GetCurrentFileType() == CDROM_AVI)||(GetCurrentFileType() == CDROM_MP4))
		{		    
	        	if(record_file_extern_name_flag==CDROM_DIV)
	    		{
		    		strcpy(linebuf, "DIVX");
	    		}
	    		else if(record_file_extern_name_flag==CDROM_VID)
	    		{
		    		strcpy(linebuf, "XVID");
	    		}
	        	else if(record_file_extern_name_flag==CDROM_MP4)
		    	{
		        	strcpy(linebuf, "MPEG4");
	        	}     
	        	else  if(record_file_extern_name_flag==CDROM_MPG)
	        	{
		        	strcpy(linebuf, "MPEG4");
	        	}    
	    		else
	        	{
	            		strcpy(linebuf, "MPEG4");
	         	}   
	   	   #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR				
	            		do_DispOSD0String(0, 0, linebuf, 1, 0); 	
	   	   #else
				do_DispOSD0String(0, 0, linebuf, DISP_WHITE, DISP_SHADOW);
	   	   #endif
	    }
	    else
	    #endif//#ifdef 	ALCO_DIVX_UI//shenyj add for alco 12/09	
			Print2OSDmem(osd_cd_id[cd_type_loaded],0,COOK_CD);
	}
	#else//#ifndef PMP_DVD   ////////////////////////////////YANGLI   ADD   FOR HDD DISPL;AY
	
	strcpy(linebuf, " HDD ");   //maybe can show card type/number for CARD_STORAGE    
	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR	
           do_DispOSD0String(0, 0, linebuf, 1, 0);
	#else
           do_DispOSD0String(0, 0, linebuf, DISP_ORANGE, DISP_SHADOW);
	#endif
    #endif//#ifndef PMP_DVD   ////////////////////////////////YANGLI   ADD   FOR HDD DISPL;AY
    
}

// 2005/07/04 yltseng for ifdef layout modify
void DispCookOSD0(BYTE bChange)
{
#ifndef SDRAM_16Mb_Mode	
	UINT32  *buf;
#endif
	int  id;//nono 2-7-12 20:36
	
#ifdef DISP_REGION_BOTTOM
    UINT8 uiRegion = OSD_GetTrueDispRegion();
#else
	UINT8 uiRegion __attribute__((unused)) = 0;
#endif
	
#ifdef ALCO_DVD_UI //Jack added 04/12/24 for NEW_PARENTAL_GUI bug(When display menu is on,we play parental disc.If passward gui is show,then you will see...)
	if(full_scrn & SETUP)
	    return;
#endif
	
	if (t_disp==0) return;
	t_disp=t_disp%10;

	//Maoyong 2004.05.11 avoid bug, show mp4 info just for MP4 file in playing state 
#ifdef DISPLAY_MP4_VER_PI	
    if( (cd_type_loaded == CDROM) && (t_disp == 2) ) 
    {
       if( (GetCurrentFileType() != CDROM_MP4) || (pFsJpeg->gifsState != FS_STATE_OTHER) )                   		       
       		t_disp = 1;           
    }
#endif
    
#ifndef SDRAM_16Mb_Mode	
    #ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF
        //different display bar has different background color.
        temp_region_top_buf = (UINT32 *)get_osdbuf_region_ptr(temp_region,0);
        temp_region_bottom_buf = (UINT32 *)get_osdbuf_region_ptr(temp_region,1);
    #else
		buf = (UINT32 *)osd_temp_buf;
	#endif
#endif
	
	if (bChange) {
		//clear all temp-buf, Jeff 20020618
		//printf("change\n");
#ifndef SDRAM_16Mb_Mode		
	#ifdef OSD_BMP_DISPLAY
	    #ifdef DISP_REGION_BOTTOM
	if (OSD_ShowBottomDisp() == 1)
	{
    	    #ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF
    	//display bar,height:32 piexl
    	if (p_scan==1)
    	    memset(temp_region_top_buf,(DISP_SHADOW_CDROM<<12 |DISP_SHADOW_CDROM<<8 | DISP_SHADOW_CDROM << 4 | DISP_SHADOW_CDROM),32*360);
    	else    
    	{    
    	    memset(temp_region_top_buf,(DISP_SHADOW_CDROM<<12 |DISP_SHADOW_CDROM<<8 | DISP_SHADOW_CDROM << 4 | DISP_SHADOW_CDROM),28*180);
            memset(temp_region_bottom_buf,(DISP_SHADOW_CDROM<<12 |DISP_SHADOW_CDROM<<8 | DISP_SHADOW_CDROM << 4 | DISP_SHADOW_CDROM),28*180);
        }
            #else
		    memset(buf,(DISP_SHADOW_CDROM<<12 |DISP_SHADOW_CDROM<<8 | DISP_SHADOW_CDROM << 4 | DISP_SHADOW_CDROM),12*1024);
            #endif
	}
	else
	    #endif//DISP_REGION_BOTTOM
	{
		#ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF
    	if ( p_scan==1)
		{
    	    //display bar,height:28 piexl
    	    memset(temp_region_top_buf,(DISP_SHADOW<<12 |DISP_SHADOW<<8 | DISP_SHADOW << 4 | DISP_SHADOW),28*360);
            //add a gray color bar,height:4 pixel
            memset(temp_region_top_buf + 7*360,0xffff,4*360);
		}		
		else
		{
            //display bar,height:28 piexl
            memset(temp_region_top_buf,(DISP_SHADOW<<12 |DISP_SHADOW<<8 | DISP_SHADOW << 4 | DISP_SHADOW),28*180);
            memset(temp_region_bottom_buf,(DISP_SHADOW<<12 |DISP_SHADOW<<8 | DISP_SHADOW << 4 | DISP_SHADOW),28*180);
            //add a gray color bar,height:4 pixel
            memset(temp_region_top_buf + 7*180,0xffff,4*180);
            memset(temp_region_bottom_buf + 7*180,0xffff,4*180);
        }
        #else
    		memset(buf,(DISP_SHADOW<<12 |DISP_SHADOW<<8 | DISP_SHADOW << 4 | DISP_SHADOW),12*1024);    
		buf = (UINT32 *)(osd_temp_buf + (region[uiRegion].osd_h-4)*region[uiRegion].osd_w);
		memset(buf,0xffff,2*1024);//f presents display gray color
    	#endif	
	}
	#else
		memset(buf,0,8*1024);		
	#endif
#else		
		{		
	        int i,j,line=12;
       
       		if (p_scan)
       			line=24;
       		
			pTopLine = (UINT32 *)(((BYTE *)get_osdbuf_baseptr()) + (region[uiRegion].osd_header[0]+OSD_DATA_OFFSET(region[uiRegion].osd_format))*32);
			pBtmLine = (UINT32 *)(((BYTE *)get_osdbuf_baseptr()) + (region[uiRegion].osd_header[1]+OSD_DATA_OFFSET(region[uiRegion].osd_format))*32);
			
	        	for (i=0; i<line; i++) 
	        	{           
#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR	        	
	            		for (j=0; j<19; j++) 
	            		{
	                		pTopLine[19*i+j] = 0x0; //f is the color index(palette_16color_setup) of transparent color
	                		if (p_scan==0)
	                			pBtmLine[19*i+j] = 0x0; //0 is the transparent color
	            		}
#else
	            		for (j=0; j<38; j++) 
	            		{
	                		pTopLine[38*i+j] = 0x0; //f is the color index(palette_16color_setup) of transparent color
	                		if (p_scan==0)
	                			pBtmLine[38*i+j] = 0x0; //0 is the transparent color
	            		}
#endif
	        	}		
		}
#endif//SDRAM_16Mb_Mode
		if (cd_type_loaded==CDDA) 
		{//Jeff 20020619
			if (rep_ab_mode==REPEAT_AB_IDLE) 
			{ 
				//when cd_type_loaded=CDDA, system will check which cddaType(CDDA/DTSCD/HDCD),
				//to reduce " " ,  "HD/DTS" string(on OSD) change
				//we add this checking
				cddaType = 0;				
			}
			else 
			{
#ifndef NO_CHANGE_HDCD_COLOR_WHEN_REPEAT_AB//zhaoyanhua add 2003-12-12 15:12				
				if (cddaType==1) 
				{ //HDCD
					//strcpy(linebuf, "HDCD");
					io_write("4");

    #ifdef NO_SHOW_HDCD_ICON//nono 2003-10-24 13:58
                        strcpy(linebuf, "    "); //Jeff 20020413
    #else//NO_SHOW_HDCD_ICON                        
                        strcpy(linebuf, "HDCD"); //Jeff 20020413
    #endif//NO_SHOW_HDCD_ICON

//                    strcpy(linebuf, "HDCD");
                    DispCDSubtypeInfo();    //Maoyong 2004.05.24
				}
#endif//NO_CHANGE_HDCD_COLOR_WHEN_REPEAT_AB
			}
		}
        
#ifdef OSD_BMP_DISPLAY
	if(t_disp)
	    DispCDTypeInfo();
#endif//OSD_BMP_DISPLAY

		if(t_disp==1) { //Jeff 20020607
		#if !defined(OSD_BMP_DISPLAY)&& (!defined(NEW_DISPLAY_GOTO_OSD))
		    DispCDTypeInfo();   //Maoyong 2004.05.24 build function for code more clear
		#endif
		  
			if(cd_type_loaded!=CDDVD) { 
				int spk_pos,tt;
		#ifdef PMP_DVD                      ///////////////////////////////////////////////////////YANGLI   ADD   FOR HDD DISPL;AY
						Print2OSDmem(STR_OS_TRACK,0,COOK_TRK); 
		//disp_trk_now=pFsJpeg->file_index_in_dir; //kenny 2005/8/3
		//tt=pFsJpeg->file_count_in_dir-1;
		disp_trk_now=(pFsJpeg->file_index_in_dir+1)-(pFsJpeg->file_count_in_dir-pFsJpeg->file_specify_in_dir);
		if(disp_trk_now<0) disp_trk_now=0;
		tt=pFsJpeg->file_specify_in_dir;
		if((full_scrn&GOTO)&&(pFsJpeg->gifsState == 0))
		Print2OSDmem(dvd_title,tt,COOK_TRK_VAL);
		else
		Print2OSDmem(disp_trk_now,tt,COOK_TRK_VAL);
		//Print2OSDmem(STR_OS_ICON_SPK,0,spk_pos);
		Print2OSDmem(STR_OS_ICON_REP0,0,COOK_REP);
		//printf_w("kkkkkkkkkkkkkkkkkkkkkkkkkk disp_trk_now=%d, tt=%d\n",disp_trk_now,tt);
		
		
		#else//#ifdef PMP_DVD                      ///////////////////////////////////////////////////////YANGLI   ADD   FOR HDD DISPL;AY
				#ifdef MP3_2GOTO_TYPE
				if(cd_type_loaded==CDROM)
				{
					if(pFsJpeg->ControlArea == CNT_AREA_FILE) 	
						Print2OSDmem(STR_OS_TRACK,0,COOK_TRK); 
					else if(pFsJpeg->ControlArea == CNT_AREA_DIR)
						Print2OSDmem(STR_OS_DIR,0,COOK_TRK);
				}
				else 	
#endif 
				//Print2OSDmem(STR_OS_TRACK,0,COOK_TRK);          
#ifdef VCD_GAME_NO_SHOW_TRACK 		//gerry,2003-12-1 10:13	
			if (cd_type_loaded!=CDVCD20)
			{
				Print2OSDmem(STR_OS_TRACK,0,COOK_TRK);
			}
			else
			{
				if((bDiscType != NES_DISC) && (bDiscType != NES_DISC_CHKSUM))
				Print2OSDmem(STR_OS_TRACK,0,COOK_TRK);          
			}	
#else
    #if !defined(NEW_DISPLAY_GOTO_OSD)&&!defined(SUPPORT_MULTI_PARTITION)  //sunzhh add 2005-3-21
          #if defined(SUPPORT_DIVX6)
                extern UINT32 divx6_menu_exist;
                extern UINT32 divx6_menu_playback;
		  extern UINT32 is_divx6_file;
		  extern UINT32 divx6_title_key_frame_table_index;
		  if(divx6_menu_exist)
		  {
			if((!divx6_menu_playback) && (divx6_title_key_frame_table_index > 0))//in title and chapter number > 0
		       {
				        //print "CHAP" always, or some setting print chapter or something longer than 4 character, 
				        //x/x chapter indicating slot would be destroyed
                           strcpy(linebuf, "CHAP");
    				    //Print2OSDmem(STR_OS_CHAPTER,0,COOK_TRK);
		       }
			else
		       {
                           strcpy(linebuf, " DIVX");
                     }
			#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR				   
				do_DispOSD0String(COOK_TRK, 0, linebuf, 1, 0);
			#else
	                    	do_DispOSD0String(COOK_TRK, 0, linebuf, DISP_WHITE, DISP_SHADOW);
			#endif
			
		  }
		  else if (is_divx6_file == 1)
		  {
				    #if 0
                    Print2OSDmem(STR_OS_TRACK,0,COOK_TRK);  
				    #else
				    strcpy(linebuf, " DIVX");
			#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
				do_DispOSD0String(COOK_TRK, 0, linebuf, 1, 0);
			#else
	               	do_DispOSD0String(COOK_TRK, 0, linebuf, DISP_WHITE, DISP_SHADOW);
			#endif					
	                	    #endif
                }
          #elif  defined(SUPPORT_NERODIGITAL) //lyc add 2005-12-23
                if(((IS_FILE_TYPE_QT())||(IS_FILE_TYPE_ND()))&&!(audio_only && IsM4AFileType())) //qinhua,modify for m4a file reset,2006-2-18 11:39
                {
       		  	extern UINT32  QT_get_num_of_chapter();
       	  		if(QT_get_num_of_chapter())
       	   		{
       	       		strcpy(linebuf, "CHAP ");
	          		}
	        		else
	         		{
	         	   		strcpy(linebuf, "NERO ");
	         		}	
	       	#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR			
	      			do_DispOSD0String(COOK_TRK, 0, linebuf, 1, 0);	
			#else
				do_DispOSD0String(COOK_TRK, 0, linebuf, DISP_WHITE, DISP_SHADOW);
			#endif					
       	  }	
      		  else
        			Print2OSDmem(STR_OS_TRACK,0,COOK_TRK);   //qinhua,2005-12-28 21:22   
          
           #else   //!SUPPORT_DIVX6
				Print2OSDmem(STR_OS_TRACK,0,COOK_TRK);  
     	    #endif  //#ifdef SUPPORT_DIVX6
    #endif//#ifndef NEW_DISPLAY_GOTO_OSD
#endif	//#ifdef VCD_GAME_NO_SHOW_TRACK 			         
				if(cd_type_loaded==CDROM) 
				{
				    extern UINT16 mp3_file_count(void);
				    
#ifdef MP3_2GOTO_TYPE
				    if(pFsJpeg->ControlArea == CNT_AREA_FILE) 	
					    tt=mp3_file_count();//nono 2-4-22 14:05 for fuss
					else if(pFsJpeg->ControlArea == CNT_AREA_DIR)
					{
					    disp_trk_now = pFsJpeg->fsnav_dir_now+1;
					    tt = pFsJpeg->count_dir[ FS_FUNC_MP3-FS_FUNC_MP3 ]; // yltseng 2004/04/12, fix from absolutely access to relative access
				    }
#else 
					tt=mp3_file_count();//nono 2-4-22 14:05 for fuss           
#endif       
					
					if (0)//(play_state==VCD_STATE_STOP)//Maoyong 2004.03.16 sunzhh modify 20050626                                       
						disp_trk_now=tt;//nono 2-4-22 14:05 for fuss           
					
                #ifdef SUPPORT_DIVX6
                    extern UINT32 divx6_menu_exist;
                    extern UINT32 divx6_menu_playback;
                    extern UINT32 is_divx6_file;
                    
                    if (is_divx6_file == 1)
                    {
                        if ((divx6_menu_playback) || (divx6_menu_exist == 0))
                        {
                            disp_trk_now = 0;
                            tt = 0;
                        }
                        else  
                        {
                            extern UINT32 divx6_get_num_of_chapter();
                            disp_trk_now = pFsJpeg->g_uiCurChapter + 1;
                            tt = divx6_get_num_of_chapter();
                        }
                    }
                #elif  defined(SUPPORT_NERODIGITAL) //lyc add 2005-12-23
                   if(((IS_FILE_TYPE_QT())||(IS_FILE_TYPE_ND()))&&!(audio_only && IsM4AFileType())) //qinhua,modify for m4a file reset,2006-2-18 11:39
                {
                   	extern UINT32  QT_get_num_of_chapter();
                   	extern UINT32  QT_get_curchapter();
       	         if(!QT_get_num_of_chapter())
       	         {
       	             disp_trk_now = 0;
                     tt = 0;
	               }
	              else
	              {
	               UINT32 curChapter = pFsJpeg->g_uiCurChapter;
	               if(curChapter != QT_get_curchapter())  //when prev/next here will be happen
	               pFsJpeg->g_uiCurChapter = QT_get_curchapter();
	         	     disp_trk_now = pFsJpeg->g_uiCurChapter + 1;
                 tt = QT_get_num_of_chapter();
	             }	   
                }	   
                  else
                   Print2OSDmem(STR_OS_TRACK,0,COOK_TRK); //qinhua,2005-12-28 21:22      
            #endif  //#ifdef SUPPORT_DIVX6		    
               
					spk_pos=COOK_SPK_MP3;
				} else 
				{
					tt=cd_total_trk();                                        
#ifdef MIX_CDMP3_DISC_DISPLAY_REAL_CD_TRK //linrc add 2004-10-29 11:16
					/*when play the cd+mp3 disc(ABEX TEST CD 786),it display the real CD TRK*/
	                if((cd_type_loaded == CDDA)&&((pFsJpeg->cdrom.track_info[1]&0x40000000) == 0x40000000))
	                {
	                    tt += 1;
	                }         
#endif                               
					spk_pos=COOK_SPK;
#ifdef EASTWIN_PORTABLE_DVD
					if(play_state==VCD_STATE_STOP)//tulijuan040824for for stop and goto command display 1 ofcdda and vcd 
						disp_trk_now=1;
#endif	
					
				}
				
				//Print2OSDmem(disp_trk_now,tt,COOK_TRK_VAL);                
#ifdef VCD_GAME_NO_SHOW_TRACK 		//gerry,2003-12-1 10:14			
			if (cd_type_loaded!=CDVCD20)
			{
				Print2OSDmem(disp_trk_now,tt,COOK_TRK_VAL);                
			}
			else
			{
				if((bDiscType != NES_DISC) && (bDiscType != NES_DISC_CHKSUM))
					Print2OSDmem(disp_trk_now,tt,COOK_TRK_VAL);
			}	         
#else

    #ifdef	NOCHANGE_DISPLAY_WHEN_PRESTOP
				if((play_state==VCD_STATE_STOP)//get the current count of mp3 file
					&&(resumeMSF!=0))//wuxiaofeng 2004-03-04
				{
					if(cd_type_loaded==CDROM)
						disp_trk_now = FSGUI_GetDispTrack();
					//if((cd_type_loaded==CDDA)||(cd_type_loaded==CDVCD20))
					//	disp_trk_now = cd_trk_now;              
					else if(cd_type_loaded!=CDDVD)              //hq, 2004-3-7 16:20					
					{
						/*	marked by hq
						printf("<%d,%d,%d,%d,%d,%d>",v11_trk_now,cd_trk_now,cd_trk_lo,cd_trk_hi,cd_trk_lo_now,disp_trk_now);
						if(cd_trk_now >= show_trk_num(cd_trk_hi))             //hq, for CD, STOP Key-->PREVIEW Key, when finished, OSD don't display one more than cd_trk_hi. 2004-3-7 16:26
							disp_trk_now = cd_trk_hi;
						else
							disp_trk_now = cd_trk_now; 
						*/
						disp_trk_now = show_trk_num(cd_trk_now);
						//printf("<%d,%d,%d,%d,%d,%d>",v11_trk_now,cd_trk_now,cd_trk_lo,cd_trk_hi,cd_trk_lo_now,disp_trk_now);
					}
				}
    #endif          
    
    #ifdef STOP_TRK_DISP_ZERO   //Maoyong 2004.06.30
                if(play_state == VCD_STATE_STOP)
                    disp_trk_now = 0;
    #endif
    #ifdef MIX_CDMP3_DISC_DISPLAY_REAL_CD_TRK   //linrc add 2004-10-29 11:19
                /*when play the cd+mp3 disc(ABEX TEST CD 786),it display the real CD TRK*/
                if((cd_type_loaded == CDDA)&&((pFsJpeg->cdrom.track_info[1]&0x40000000) == 0x40000000)
                        &&(play_state==VCD_STATE_STOP))
	                {
	                    disp_trk_now += 1;
	                } 
	#endif

    #ifdef  NEW_DISPLAY_GOTO_OSD
                    Print2OSDmem(disp_trk_now,tt, POS_TRACK);                
    #else
                    #ifdef ALCO_DVD_UI
                    if((cd_type_loaded==CDROM) && (full_scrn&GOTO) && (index_x<4)) 
                        Print2OSDmem(dvd_title,tt,COOK_TRK_VAL); 
                    else if((cd_type_loaded!=CDROM) && (full_scrn&GOTO) && (index_x<2))
                         Print2OSDmem(dvd_title,tt,COOK_TRK_VAL); 
                    else 
                    #endif
				    Print2OSDmem(disp_trk_now,tt,COOK_TRK_VAL);                
    #endif//#ifndef NEW_DISPLAY_GOTO_OSD
#endif//#ifdef VCD_GAME_NO_SHOW_TRACK

#ifndef NEW_DISPLAY_GOTO_OSD
	#ifdef	NOT_SHOW_SOME_INFO_IN_JPEG
					if(!(Is_JPEG_STATE()))
    #endif
				{

    #ifdef SDRAM_16Mb_Mode//2004-7-3 15:10
            if(user_mute)
                Print2OSDmem(STR_OS_SPACE,0,spk_pos);
            else
    #endif//SDRAM_16Mb_Mode

				Print2OSDmem(STR_OS_ICON_SPK,0,spk_pos);

    #ifdef VALID_PROGROM_REPEAT
#if !defined(ALCO_DVD_UI)
                if( (prog_cnt)&&(rep_mode == REPEAT_IDLE) )				
	    #ifdef STOP_IN_PROG_END//zhuyanfeng 20041025//to avoid display err when use program repeat off function 
				Print2OSDmem(STR_OS_ICON_REP0,0,COOK_REP);
        #else
				Print2OSDmem(STR_OS_ICON_REPD,0,COOK_REP);
        #endif
                else
    #endif
#endif
				             
	#ifdef ICON_REPEAT_FOLDER    //zhuyf  2004-8-10 
				if( rep_mode==REPEAT_DIRECTORY)
                	Print2OSDmem(STR_OS_ICON_REPF,0,COOK_REP);
                else 
    #endif
	#ifdef SUPPORT_ALL_CDDA_DISCS_REPEAT //chenzhao 2006-4-19 17:50 .
				if( rep_mode==REPEAT_ALL_DISCS)
                	Print2OSDmem(STR_OS_ICON_REPD,0,COOK_REP);
                else 
    #endif
				Print2OSDmem(STR_OS_ICON_REP0,0,COOK_REP);

				}
				if( (cd_type_loaded!=CDDA)&&(cd_type_loaded!=CDROM) ) {
					Print2OSDmem(STR_OS_PBC,0,COOK_PBC);                    
				}           
#endif//#ifndef NEW_DISPLAY_GOTO_OSD
            #endif//#ifdef PMP_DVD                      ///////////////////////////////////////////////////////YANGLI   ADD   FOR HDD DISPL;AY
			} else {            
		   
#ifdef STOP_TRK_DISP_ZERO   //Maoyong 2004.06.30
                                if(play_state == VCD_STATE_STOP)
                                disp_trk_now = 0;
#endif      
	
#ifdef	NOCHANGE_DISPLAY_WHEN_PRESTOP       //wuxiaofeng, 2004-3-9 21:54
					if(play_state==VCD_STATE_STOP)
					{
					    if(resumeMSF)                     //Pre-stop in DVD, hq, 2004-3-9 21:58
					    {
						Print2OSDmem(STR_OS_TT,0,COOK_TRK); 	
						Print2OSDmem(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_TTN,get_tt_info(DISP_TT_Ns),COOK_TRK_VAL);				
						Print2OSDmem(STR_OS_CHP,0,COOK_CHP);		
						Print2OSDmem(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_PTTN,get_tt_info(DISP_CH_Ns),COOK_CHP_VAL);
					        
					    }else					           //Stop in DVD, hq, 2004-3-9 21:59
				    	{
				    		Print2OSDmem(STR_OS_TT,0,COOK_TRK); 	
				       		Print2OSDmem(get_tt_info(DISP_TT_Ns),get_tt_info(DISP_TT_Ns),COOK_TRK_VAL);				
						    Print2OSDmem(STR_OS_CHP,0,COOK_CHP);		
						    Print2OSDmem(get_tt_info(DISP_CH_Ns),get_tt_info(DISP_CH_Ns),COOK_CHP_VAL);
					    }
					}
					else
#endif
                {
#ifdef  NEW_DISPLAY_GOTO_OSD
                    Print2OSDmem(get_tt_info(DISP_TT),get_tt_info(DISP_TT_Ns), POS_DVD_TITLE);                
                    Print2OSDmem(get_tt_info(DISP_CH),get_tt_info(DISP_CH_Ns), POS_DVD_CHAP);
#else//#ifdef  NEW_DISPLAY_GOTO_OSD
				Print2OSDmem(STR_OS_TT,0,COOK_TRK);     
				#ifdef ALCO_DVD_UI
                if((full_scrn&GOTO) && (index_x<2)) 
                    Print2OSDmem(dvd_title,get_tt_info(DISP_TT_Ns),COOK_TRK_VAL);
                else
                #endif
				Print2OSDmem(get_tt_info(DISP_TT),get_tt_info(DISP_TT_Ns),COOK_TRK_VAL);                
				Print2OSDmem(STR_OS_CHP,0,COOK_CHP);
				#ifdef ALCO_DVD_UI
                if((full_scrn&GOTO) && ((1<index_x)&&(index_x<5))) 
                    Print2OSDmem(dvd_chapter,get_tt_info(DISP_CH_Ns),COOK_CHP_VAL);
                else
                #endif
				Print2OSDmem(get_tt_info(DISP_CH),get_tt_info(DISP_CH_Ns),COOK_CHP_VAL);
#endif//#ifdef  NEW_DISPLAY_GOTO_OSD
				}
				//Jeff 20020621
				if (full_scrn&MARK)
					mark_UpdateOSD();
			}
			
			//cook TIME icon
#ifdef REMAIN_TIME//nono 2-7-13 11:28 for fuss
			//if(t_disp==1)
			{
				//printf("disp:polling_clock=%d\n",polling_clock);
				#ifdef ALCO_DVD_UI
				if(polling_clock)
				#else
				if(polling_clock<6)
				#endif
				{ 
					if( (remain==DISC_REMAIN_TIME)||(remain==DISC_TIME) ) 
					{
    #ifdef REMIAN_TIME_SHOW_FONT
					if(IsOSDChinese())
					{
						if(cd_type_loaded==CDDVD)
							id = STR_OS_TITLE;
						else
							id = STR_OS_ALL;
				    }else//if(IsOSDChinese())
						id = STR_OS_ICON_T;
    #else//#endif//REMIAN_TIME_SHOW_FONT
						id = STR_OS_ICON_T;
    #endif//REMIAN_TIME_SHOW_FONT
					}else //if( (remain==TRK_REMAIN_TIME)||(remain==NO_REMAIN_TIME) )
					{
    #ifdef REMIAN_TIME_SHOW_FONT
					if(IsOSDChinese())
					{
						if(cd_type_loaded==CDDVD)
						id = STR_OS_CHAPTER;
						else
						id = STR_OS_TRACK;
					}else
						id = STR_OS_ICON_C;
    #else//#endif//REMIAN_TIME_SHOW_FONT						
	#ifdef DISPLAY_T_NOT_DVD //KINGSLON 20051027
				if(cd_type_loaded!=CDDVD)
						id = STR_OS_ICON_T;
	#endif
						id = STR_OS_ICON_C;
    #endif//#endif//REMIAN_TIME_SHOW_FONT						
					}
					
					//id=ClockPolling(1);
					//printf("t\n");
				}
				else //if(polling_clock>6)
				{ 
					//id=ClockPolling(0);
					id = STR_OS_ICON_CLOCK;
					//printf("clock\n");
				}
			}
			//Print2OSDmem(STR_OS_ICON_CLOCK,0,COOK_CLOCK);           
			//Print2OSDmem(id,0,COOK_CLOCK);           			//Mark by Maoyong 2004.02.13      
#else
			//Print2OSDmem(STR_OS_ICON_CLOCK,0,COOK_CLOCK);     //Mark by Maoyong 2004.02.13      
			id = STR_OS_ICON_CLOCK;
#endif
	
#ifdef NOT_SHOW_TIME_IN_JPG    //Maoyong for not display "-" when jpeg 2004.02.13      
			if(Is_JPEG_STATE())
			{
			id = STR_OS_SPACE;		
		    }	
#endif	
			#ifdef NO_DISP_TIME_CLOCK_WHEN_KODAK  //Maoyong for not display "-" when jpeg 2004.02.13      
			if(pFsJpeg->gbfsPictureCD == 1)
			{
			id = STR_OS_SPACE;		
		    }	
			#endif	

#ifndef NEW_DISPLAY_GOTO_OSD
    #ifdef OSD_BMP_DISPLAY
			OSD_LayoutBmpDisplay(CLOCK_ICON_BMP);
	#else
#if !defined(NO_DISP_CLOCK) && !defined(NO_DISP_CLOCK_WHEN_KODAK) //xyy add for Oritron 2004-11-10 			
			Print2OSDmem(id,0,COOK_CLOCK);			
        #endif
    #endif//OSD_BMP_DISPLAY
#endif//#ifndef NEW_DISPLAY_GOTO_OSD
		} else if (t_disp==2) {//Jeff 20020607
			
#ifndef NEW_DISPLAY_GOTO_OSD
    #if defined(DISPLAY_MP4_VER_PI) || defined(DISPLAY_MP4_AV_INFO)		//Maoyong 2004.06.29
            if( (GetCurrentFileType() == CDROM_MP4) && (pFsJpeg->gifsState == FS_STATE_OTHER) )
            {            		       	
        #ifdef DISPLAY_MP4_VER_PI
            	disp_mp4_ver_pi();
        #elif defined(DISPLAY_MP4_AV_INFO)
            	disp_mp4_av_info();
        #endif
            	return;
            }
    #endif
        	
			int id,show;            
			if(cd_type_loaded!=CDSVCD) {
				Print2OSDmem(STR_OS_ANGLE,0,COOK_ANGLE);
                
				if(get_angle_Ns())
					Print2OSDmem(NP_AGLN,get_angle_Ns(),COOK_ANGLE_VAL);          
				else
					Print2OSDmem(STR_OS_NONE,0,COOK_ANGLE_VAL);                      
                
				if(pDSV->CurrDomain==TT_DOM)
					show=1;
				else
					show=0;
			} else
				show=1;
            
			Print2OSDmem(STR_OS_AUDIO,0,COOK_AUDIO);                
    #ifdef DVD_AUDIO
			if (dAMG_LSN && (pDSV->tt_info.dTT_PB_TY&0x80))
			{
				if( show&&(pDSV->dAv_AST_Ns) )
					Print2OSDmem((NP_ASLN&0x0001)+1,pDSV->dAv_AST_Ns,COOK_AUDIO_VAL);
				else
					Print2OSDmem(STR_OS_NONE,0,COOK_AUDIO_VAL);
				Print2OSDmem(STR_OS_AUDIO,COOK_S_LANG,COOK_AUDIO_LANG);
				Print2OSDmem(NP_ASTN,COOK_S_MODE,COOK_AUDIO_TYPE);								
			} else
    #endif			
			if( ((NP_ASTN&0xf)<=8)&&show&&(pDSV->dAv_AST_Ns) ) {
				/* alan 02-05-27 modified */
				if (((NP_ASTN+1)>pDSV->dAv_AST_Ns)&&(pDSV->dAv_AST_Ns==1))
					Print2OSDmem(1,pDSV->dAv_AST_Ns,COOK_AUDIO_VAL);
				else 
				{//terry,2003/12/15 02:27PM,for Real time Video Format PAL, Philips 3122-783-01941
					Print2OSDmem(NP_ASTN-min_astn_id+1,pDSV->dAv_AST_Ns,COOK_AUDIO_VAL);
				}
				
				Print2OSDmem(STR_OS_AUDIO,COOK_S_LANG,COOK_AUDIO_LANG);
				Print2OSDmem(NP_ASTN,COOK_S_MODE,COOK_AUDIO_TYPE-1); //libing add "-1" 2006-5-19 for "dts 5.1ch" no "h"           
			}else 
				Print2OSDmem(STR_OS_NONE,0,COOK_AUDIO_VAL);                       
			
			Print2OSDmem(STR_OS_SUBTITLE,0,COOK_SUBTITLE);
			id=NP_SPSTN&0x3f;
			//if( (NP_SPSTN&0x40)&&(id<=pDSV->dAv_SPST_Ns)&&show ) {
			if( (NP_SPSTN&0x40)&&(pDSV->dAv_SPST_Ns)&&(id<=pDSV->dAv_SPST_Ns)&&show ) { //Jeff 20020629
				#ifdef ALCO_DVD_UI
				if((id+1)>pDSV->dAv_SPST_Ns)
				    Print2OSDmem(id,pDSV->dAv_SPST_Ns,COOK_SUBTITLE_VAL-1);    //  //shenyj mark for alco franch lang display 050228   
				else
				    Print2OSDmem(id+1,pDSV->dAv_SPST_Ns,COOK_SUBTITLE_VAL-1);    //  //shenyj mark for alco franch lang display 050228   
				Print2OSDmem(STR_OS_SUBTITLE,COOK_S_LANG,COOK_SUBTITLE_LANG-1);
				#else
                    #ifdef SVCD_DISPLAY_SUBTITLE_OFF //zxb 060809
			        if(cd_type_loaded == CDSVCD)
				        Print2OSDmem(STR_OS_OFF,0,COOK_SUBTITLE_VAL); 
			        else
			        #endif
				Print2OSDmem(id+1,pDSV->dAv_SPST_Ns,COOK_SUBTITLE_VAL);     
				Print2OSDmem(STR_OS_SUBTITLE,COOK_S_LANG,COOK_SUBTITLE_LANG);
				#endif
			} else {
				Print2OSDmem(STR_OS_OFF,0,COOK_SUBTITLE_VAL);                
			}               
			//} else if (t_disp==3) {//Jeff 20020411
#endif//#ifdef NEW_DISPLAY_GOTO_OSD
		} else if (t_disp==3) {//Jeff 20020607
			//8:gree  15:shadow color       10:bright-orange        2:yellow
			//Jeff 20020411
			io_write("3");
			psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_MARK]);
#ifdef SDRAM_16Mb_Mode
	       #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
			do_DispOSD0String(0, 0, linebuf, 1, 0);	
		#else
			do_DispOSD0String(0, 0, linebuf, 2, DISP_SHADOW);
		#endif			
#else
			do_DispOSD0String(0, 0, linebuf, 8, DISP_SHADOW);
#endif
			mark_UpdateOSD();
			
			Print2OSDmem(0,COOK_S_TIMER,COOK_CLOCK_VAL);
		}
        }   
		
        if (t_disp==1) { 
#ifndef NEW_DISPLAY_GOTO_OSD
    #ifdef	NOT_SHOW_SOME_INFO_IN_JPEG
				if((Is_JPEG_STATE()))
				{
					if(pFsJpeg->gbfsPictureCD)     //hq,2004-3-4 20:40
					{
	       		#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
						do_DispOSD0String(COOK_CLOCK, 0, "PICTURE CD", 1, 0); 
		   		#else
						do_DispOSD0String(COOK_CLOCK, 0, "PICTURE CD", DISP_YGREEN, DISP_SHADOW); 
		   		#endif					 
					}					
					else
					{
				#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR	
						do_DispOSD0String(COOK_CLOCK, 0, "JPEG PICTURE", 1, 0); 
				#else
						do_DispOSD0String(COOK_CLOCK, 0, "JPEG PICTURE", DISP_YGREEN, DISP_SHADOW); 
				#endif					 
					}
				}
                // 2004/04/15 yltseng mark, SUPPORT_OTHER_NEXT_PREVIOUS flag is no more need
				//#ifdef	SUPPORT_OTHER_NEXT_PREVIOUS
				else if(Is_OTHER_STATE())//wuxiaofeng 2004-03-17
                		{
				#ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR                		
					do_DispOSD0String(COOK_CLOCK, 0, "          AV", 1, 0); 
				#else
					do_DispOSD0String(COOK_CLOCK, 0, "          AV", DISP_YGREEN, DISP_SHADOW);
				#endif 
                		}
				//#endif//#ifdef	SUPPORT_OTHER_NEXT_PREVIOUS
				else
	#endif
			Print2OSDmem(0,COOK_S_TIMER,COOK_CLOCK_VAL);
			
			/*Maoyong 2004.02.26
			  avoid to mistake for a CDDA contain HDCD,DTS..., when stop state,
			  clear cdda subtype
			*/
	#ifdef	JUST_SHOW_CD_TYPE
			if( (cd_type_loaded==CDDA) && (play_state== VCD_STATE_STOP) )
			{
				strcpy(linebuf, "     ");  
			  #ifdef SDRAM_16Mb_Mode_OSD_SUPPORT_2_COLOR
				do_DispOSD0String(COOK_CD, 0, linebuf, 1, 0);
			  #else
				do_DispOSD0String(COOK_CD, 0, linebuf, DISP_ORANGE, DISP_SHADOW);	
			  #endif						        				       	
				return;
			}
	#endif
			
			if ( (cd_type_loaded==CDDA) &&
				(coding_mode_now!=AUDIF_CODING_MODE_DTSCD)
				)
			{
				int     myCDDAType;
				myCDDAType = getCDDAType();
				
    #if	defined(SUPPORT_CDG) && defined(JUST_SHOW_CD_TYPE)
				get_cdkit_time(0);				
				if(track_play_diff_time < 2)				
					return;	
				    	
				if( (myCDDAType == 0) && (cd_subtype == CD_DA) )
				{
				    if((bReadSubChannel != 0) &&CDG_IsCDGNow())
				    {
				        cddaType = 0;
				        strcpy(linebuf, "CDG  ");  
				        //do_DispOSD0String(COOK_CD, 0, linebuf, DISP_ORANGE, DISP_SHADOW); //Jeff 20020413				        				       
				    }
				    else 
				    {
				        cddaType = 0;				
				        strcpy(linebuf, "CD   ");				
				    }				        
							        
				    DispCDSubtypeInfo();    //Maoyong 2004.05.24
				}				
    #endif//#if	defined(SUPPORT_CDG) && defined(JUST_SHOW_CD_TYPE)
        
    #ifndef NO_CHANGE_HDCD_COLOR_WHEN_REPEAT_AB//zhaoyanhua add 2003-12-12 14:54
				if (myCDDAType!=cddaType)
    #endif
				{
					cddaType = myCDDAType; //Jeff 20020617
					if (myCDDAType==0)
					{
						//CDDA ICON
						strcpy(linebuf, "    "); //Jeff 20020617
					}
					else
					{
    #ifdef JUST_SHOW_CD_TYPE//4-2-12 3:21
					    if(cd_subtype == CDROM_UNSUPPORT)
					    {					       
					        return;
					    }
    #endif//JUST_SHOW_CD_TYPE
						//HDCD ICON
    #ifdef NO_SHOW_HDCD_ICON//nono 2003-10-24 13:58
                        strcpy(linebuf, "    "); //Jeff 20020413
	#else//NO_SHOW_HDCD_ICON                        
                        strcpy(linebuf, "HDCD"); //Jeff 20020413
	#endif//NO_SHOW_HDCD_ICON
					}
                    DispCDSubtypeInfo();    //Maoyong 2004.05.24
				}
			}
			if ( (cd_type_loaded==CDDA) && 
				(cd_subtype==CD_DTS) &&
				(coding_mode_now&(AUDIF_CODING_MODE_DTSCD|AUDIF_CODING_MODE_PCM))
				) 
			{ //Jeff 20020415
				//strcpy(linebuf, "DTS");
    #ifdef NO_SHOW_DTS_ICON//nono 2003-11-24 10:52
                strcpy(linebuf, "    ");
    #else//NO_SHOW_DTS_ICON
	    #ifdef JUST_SHOW_CD_TYPE
                strcpy(linebuf, "DTSCD");               
	    #else
                strcpy(linebuf, "DTS ");               
	    #endif   
    #endif//NO_SHOW_DTS_ICON

                DispCDSubtypeInfo();    //Maoyong 2004.05.24
			}
    #ifdef SUPPORT_CDG
			//if ((cd_subtype==CD_DA) && bReadSubChannel)//axelchen 2004/5/10 07:32pm 
			//if ((cd_type_loaded==CDDA) && bReadSubChannel)// for mis-identfy CDG in VCD 2.0
		    if ( ( (cd_type_loaded==CDDA)&&(cd_subtype==CD_DA)) && bReadSubChannel)//nono 4-5-12 22:53
		    {
				if (CDG_IsCDGNow())
			 	{
	    #ifdef PULIANG_DVD
			 	    strcpy(linebuf, "CD-G");//yaowh modify 04-12-17
		#elif defined NO_SHOW_CDG_ICON      //LIZHX ADD 2005-7-13 18:01
                    strcpy(linebuf, " ");
		#else
                    strcpy(linebuf, "CDG");
        #endif
                    DispCDSubtypeInfo();    //Maoyong 2004.05.24
				}				
			}
    #endif	
			//} else if (t_disp==3) { //Jeff 200204112
#endif//#ifdef NEW_DISPLAY_GOTO_OSD
        } else if (t_disp==3) { //Jeff 20020607
			Print2OSDmem(0,COOK_S_TIMER,COOK_CLOCK_VAL);
        }
#ifdef NEW_DISPLAY_GOTO_OSD
            else if(t_disp==2)
            {
                if(index_x<5) index_x=5;//move the cursor to the second page point time
                Print2OSDmem(0,COOK_S_TIMER, POS_TIME);
            }
#endif
}



#ifdef MP3_NO_DISPLAY
void mp3_noshow_diplay()   //2004-4-22 04:40张宇P
{
       if(Is_MP3_STATE())
		   {   
		        char linebuf[40];
		        int tt=0;
		        tt=mp3_file_count();//cd_total_trk();
		       if(disp_time != fore_disp_time)
		       {
		        FSGUI_FillFrameBuf(25,256,170,20,BK_GROUNDY, BK_GROUNDCRCB );
		        fore_disp_time=disp_time;
		       
		        psprintf(linebuf, " %02d:%02d:%02d TRK%1d/%1d", show_time_hh, show_time_mm, show_time_ss,disp_trk_now,tt);
		        FSGUI_ShowString(15,256,linebuf, FS_FONTCOLOR_FILE_Y1, FS_FONTCOLOR_FILE_CrCb1);
			   
			    hanyang_rep();//caohui 2004-4-22 21:00
			}  
}
}
//#include ".\\fs\\fsGUI1.c"
//#include ".\\fs\\fsGUI_pub.c"
void hanyang_rep(void)   //caohui 2004-4-22 21:00
{ 
	switch(rep_mode)
	{
	 case REPEAT_IDLE:
	 FSGUI_FillFrameBuf(260,256,12,12,BK_GROUNDY, BK_GROUNDCRCB);
	DrawFileIcon( 260,  256, 2);
	 break;
	    
	 case REPEAT_DISC:
	 FSGUI_FillFrameBuf(260,256,12,12,BK_GROUNDY, BK_GROUNDCRCB);
	DrawFileIcon( 260,  256, 3);
	 break;
	 
	 case REPEAT_DIRECTORY:
	 FSGUI_FillFrameBuf(260,256,12,12,BK_GROUNDY, BK_GROUNDCRCB);
	DrawFileIcon( 260,  256, 3);
     break;
	 
	 case REPEAT_TRACK:
	 FSGUI_FillFrameBuf(260,256,12,12,BK_GROUNDY, BK_GROUNDCRCB);
	DrawFileIcon(260, 256, 4);
     break;
    }

}
#endif  // #ifdef MP3_NO_DIPLAY




