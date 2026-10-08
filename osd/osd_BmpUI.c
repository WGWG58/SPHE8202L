/**************************************************************
** FILE
** Osd_BmpUI.c
**
** DESCRIPTION
** The basic  functions of Setup_Bmp.c, build a new GUI with bmp for setup.
**
**
**   Creator: feeling,suqiaoli
**   Date:    2004-7-7 16:32
****************************************************************/
#include "config.h"
#include "regmap.h"
#include "global.h"

#include "memmap.h"
#include "func.h"
#include "fsNAV.h"
#include "osd_api.h"
//#include "stdlib.h"
//#include "cfont.h"

//#include "osd.h"
//#include "osdsup.h"
//#include "osdfont.h"
//#include "osd_str.h"
//#include "user_init.h"
//#include "endian.h"
//#include "user_if.h"
#ifdef OSD_BMP
#include "Osd_Bmp.h"
#include "Osd_BmpUI.h"
//#include "Osd_BmpPalette.h"

extern void ReverseImg(const BYTE ImgOriData[], BYTE ImgTransData[], BYTE iMode);
extern  UINT8   osd_temp_buf[];
extern  UINT8 OSD_ShowBottomDisp(void);

#ifdef OSD_BMP_DISPLAY
#define DISP_SHADOW         0x07
#define DISP_SHADOW_CDROM   0
const OSD_BITMAP_LAYOUT_S g_aOsdDispBmp[] =
{
    	//{xStart, yStart, Width, Height, xOffset, yOffset, Index in g_aBitmap, Region}

    	//display osd :bmp index from 0~15 
    	{507,	2,	    0,	    0,	   	  0,    0,     0,       0}, //angle_16.bmp	//0
    	{53,    2,    	0,	    0,   	  0,    0,     1,       0}, //cd_16.bmp	//1
    	{53,    2,    	0, 	    0,   	  0,    0,     2,   	0}, //cdrom_16.bmp 	//2
    	{458,  	7,    	0, 	    0,   	  0,    0,     3,   	0}, //clock_icon_16.bmp	//3
    	{381,  	2,    	0, 	    0,   	  0,    0,     4,   	0},//dolby_16.bmp	 //4
    	{381, 	7,    	0,	    0,   	  0,    0,     5,   	0},//dts_16.bmp	 //5
	    {53,  	2,    	0,	    0,   	  0,    0,     6,  	    0},//dvd_16.bmp 	//6
    	{143,  	7,    	0, 	    0,   	  0,    0,     7,  	    0},//language_16.bmp	//7
    	{404,  	7,    	0, 	    0,   	  0,    0,     8,   	0},//mute_icon_16.bmp	//8
    	{350, 	7,    	0, 	    0,   	  0,    0,     9,       0},//repeat-1_16.bmp 	//9
	    {350,  	7,    	0,	    0,   	  0,    0,     10,	    0},//repeat-all_16.bmp	 //10
    	{350,  	7,    	0,      0,   	  0,    0,     11, 	    0},//repeat-close_16.bmp 	 //11
    	{261,   2,   	0, 	    0,   	  0,    0,     12,	    0}, //sub_title_16.bmp	//12
    	{53,  	2,    	0,      0,   	  0,    0,     13, 	    0}, //svcd_16.bmp 	//13
    	{53, 	2,    	0, 	    0,    	  0,    0,     14,	    0},//vcd_16.bmp	//14
    	{404, 	7,    	0, 	    0,   	  0,    0,     15,	    0},//volume_icon_16.bmp	//15
};
#endif

#ifdef OSD_BMP_SOUND
const OSD_BITMAP_LAYOUT_S g_aOsdSoundBmp[] =
{
    	//{xStart, yStart, Width, Height, xOffset, yOffset, Index in g_aBitmap, Region}
	//sound 3d
	{0,		0,	    576,    14,     0,		0,      16,	    1},//OSD_BG_BMP_A		    //0
	{16,    0,	    144,    14,     134,    0,      17,	    1},//OSD_DOWN_BG_BMP_A	    //1
	{0,		0,	    0,  	0,		0,		0,	    18,	    3},//OSD_4_1_BMP_D          //2
	{14,    0,    	548,    12,     0,		0,	    19,	    3},//OSD_4_2_BMP_D          //3
	{562,	0,	    0,	    0,		0,		0,	    20,	    3},//OSD_4_3_BMP_D          //4
	{0,		0,	    16,		214, 	0,		0,	    21,	    4},//OSD_5_1_BMP_E          //5
	{560,	0,	    16,		214,    0,		0,	    22,	    4},//OSD_5_3_BMP_E		    //6
	{0,		0,	    0,		0,		0,		0,	    23,	    5},//OSD_6_1_BMP_F			//7
	{14,    0,	    546,    20,		0,		0,	    24,     5},//OSD_6_2_BMP_F			//8
	{562,	0,	    0,		0,		0,		0,	    25,	    5},//OSD_6_3_BMP_F			//9
    {20,    26,     136,    8,      134,    0,	    26,	    2},//OSD_CURSOR_1_BMP_B     //10
    {20,    0,	    136,    10,     134,    0,	    27,	    3},//OSD_CURSOR_2_BMP_D		//11
    {122,   122,	0,     	0,      26,     0,	    28,	    4},//SOUND_SLIDE_ARROW_SELECTED_BMP_E3	//12
    {122,   122,	0,     	0,	    26,     0,	    29,	    4},//SOUND_SLIDE_ARROW_CURSOR_BMP_E3	//13

};

const OSD_LINE_LAYOUT_S g_aOsdSoundLine[] =
{
	//{xStart, yStart, Width, Height, xOffset, yOffset, Color,  Region} 
	//sound 3d osd
	{14,    1,      2,    13,     134,      0,      7,      1},//SOUND_LINE1_A	//0
	{160,   1,      2,    13,     134,      0,      7,      1},//SOUND_LINE2_A	//1
	{14,    0,    2,    34,     134,    0,    8,    2},//SOUND_LINE1_B	//2
	{160,   0,    2,    34,     134,    0,    8,    2},//SOUND_LINE2_B	//3
	{0,     33, 576,    1,      0,      0,    9,    2},//SOUND_BG_LINE_B	//4
	{14,    0,    2,    12,     134,    0,    9,    3},//SOUND_LINE1_D	//5
	{160,   0,    2,    12,     134,    0,    9,    3},//SOUND_LINE2_D	//6
	{32,   22, 246,    1,      0,        28,    11,  4},//SOUND_CURSOR_UP_LINE_E4 //7
	{32,   49, 246,    1,      0,        28,    11,   4},//SOUND_CURSOR_DOWN_LINE_E4 //8
	{32,   22, 246,    1,      0,        28,   1,    4},//SOUND_SEL_UP_LINE_E4 //9
	{32,   49, 246,    1,      0,        28,    1,   4},//SOUND_SEL_DOWN_LINE_E4 //10
	{132, 84,  2,   20,  312, 0,   14,   4},//SOUND_SCALE_N6_LINE_E3	11
	{158, 96,  2,   8,    52,   0,   14,   4},//SOUND_SCALE_N6_N4_LINE_E3	12
	{184, 92,  2,   12,  52,   0,   14,   4},//SOUND_SCALE_N4_LINE_E3	13
	{132, 110, 314, 4,   0,   0,   14,   4},//SOUND_SCALE_LINE_E3
};


const OSD_RECT_LAYOUT_S g_aOsdSoundRect[] =
{
	//{xStart, yStart, xLen, yLen, xOffset, yOffset, bgColor, Region}
	//sound 3d osd
	{162,   1,      8,      13,     134,    0,      0,      1},//SOUND_SHADOW_A	//0
	{0,	    0,    576, 34,     0,       0,    0,    2},//SOUND_RECT_BG_B		//1
	{16,    0,      144,    34,     134,    0,      4,      2},//SOUND_DOWN_B   //2
	{162,   0,      8,      34,     134,    0,      13,     2},//SOUND_SHADOW_B	//3
	{162,   0,      8,      8,      134,    0,      4,      3},//SOUND_SHADOW_D	//4
	{16,    0,      144,    12,     134,    0,      0,      3},//SOUND_DOWN_D		//5
	{32,    23,     246,    26,     0,      28,     12,     4},//SOUND_CURSOR_RECT_E4	//6
	{32,    23,     246,    26,     0,      28,     3,      4},//SOUND_SEL_RECT_E4	//7
	{32,    22,     246,    28,     0,      28,     0,      4},//SOUND_UNSEL_RECT_E4	//8
	{16,    0,      544,    214,    0,      0,      0,      4},//SOUND_BG_RECT_E4 //9
	{294,   32,     248,    160,    0,      0,      2,      4},//SOUND_EQ_BG_RECT_E1 //10
	{164,   32,     248,    160,    0,      0,      2,      4},//SOUND_BAND_BG_RECT_E1//11
	{100,   114,    380,    80,     0,      0,      0,      4},//SOUND_KEY_BG_RECT_E3//12
	{432,   6,      110,    26,     0,      0,      2,      4},//SOUND_EQ_POPUP_BG_RECT_E4 //13
	{298,   32,     24,     160,    18,     0,      8,      4},//SOUND_EQ_CURSOR_BG_RECT_E4 //14
	{298,   32,     24,     160,    18,     0,      2,      4},//SOUND_EQ_UNSEL_BG_RECT_E4 //15

};

const OSD_STR_LAYOUT_S g_aOsdSoundStr[] =
{
	//{xStart, yStart, xOffset, yOffset, fontColor, bgColor, region}
	//sound 3d osd
	{88-32,	0,	134,	0,	8,    0,    2},//SOUND_UNSEL_STR_B	//0
	{88-32,	0,    134,	0,    7,    4,    2},//SOUND_SEL_STR_B    //1
	{42,		24,	0,	28,	14,	0,    4},//SOUND_UNHL_ITEM_STR_E4 //2
	{42,		24,	0,    28,	15,	0,	4},//SOUND_HL_ITEM_STR_E4  //3
	{436,      8,    0,     0,    8,    2,     4},//SOUND_EQ_STR_E4   4
	{92,        86,  378, 0,    14,   0,    4},//SOUND_SCALE_KEY_STR_E3	5
	{118,      50,  52,   0,    14,   0,    4},//SOUND_SCALE_N_NUM_STR_E3	6
	{280,      50,  52,   0,    14,   0,     4},//SOUND_SCALE_P_NUM_STR_E3 7
};    
#endif    

#ifdef OSD_BMP_PROG
//prog data structure:bmp data,index:0~9
const OSD_BITMAP_LAYOUT_S g_aOsdProgBmp[] =
{
  //{xStart, yStart, Width, Height, xOffset, yOffset, Index in g_aBitmap, Region}
	{0,     0,	    592,    14,     0,      0,	    16,	    1},//OSD_BG_BMP_A		        //0
    {16,    0,	    158,    14,     0,      0,	    17,	    1},//OSD_DOWN_BG_BMP_A	        //1
	{0,     0,	    0,      0,      0,      0,	    18,	    3},//OSD_4_1_BMP_D				//2
    {14,    0,    	564,    12,     0,      0,	    19,	    3},//OSD_4_2_BMP_D				//3
    {576,	0,      0,      0,      0,      0,	    20,	    3},//OSD_4_3_BMP_D				//4
	{0,     0,	    16,     262,    0,      0,	    21,	    4},//OSD_5_1_BMP_E            	//5
    {576,   0,	    16,     262,    0,		0,	    22,	    4},//OSD_5_3_BMP_E				//6
	{0,     0,	    0,      0,      0,		0,	    23,	    5},//OSD_6_1_BMP_F				//7
	{16,    0,	    560,    20,     0,      0,	    24,     5},//OSD_6_2_BMP_F				//8
	{576,	0,	    0,      0,      0,		0,	    25,	    5},//OSD_6_3_BMP_F				//9
    {60,    8,      0,      0,      140,    0,      30,     4},//PROG_CDROM_FOLDER_BMP_D    //10		
    {128,   8,      0,      0,      140,    0,      31,     4},//PROG_CDROM_FILE_BMP_D      //11		

};

//prog data structure:line data,index:0~6
const OSD_LINE_LAYOUT_S g_aOsdProgLine[] =
{
  //{xStart, yStart, Width, Height, xOffset, yOffset, Color,  Region} 
	{14,    1,    2,    13,     0,    0,    7,    1},//PROG_LINE1_A		//0
	{174,   1,    2,    13,     0,    0,    7,    1},//PROG_LINE2_A		//1
	{14,    0,    2,    34,     0,    0,    8,    2},//PROG_LINE1_B		//2
	{174,   0,    2,    34,     0,    0,    8,    2},//PROG_LINE2_B		//3
	{0,     33,   592,    1,    0,    0,    9,    2},//PROG_BG_LINE_B	//4
	{14,    0,    2,    12,     0,    0,    9,    3},//PROG_LINE1_D		//5
	{174,   0,    2,    12,     0,    0,    9,    3},//PROG_LINE2_D		//6
};

//prog data structure:rect data,index:0~8
const OSD_RECT_LAYOUT_S g_aOsdProgRect[] =
{
  //{xStart, yStart, xLen, yLen, xOffset, yOffset, bgColor, Region}
	{176,   1,    8,  	13,     0,      0,    0,    1},//PROG_SHADOW_A		//0
	{176,   0,    8,    34,     0,      0,    13,   2},//PROG_SHADOW_B		//1
	{16,    0,    158,  34,     0,      0,    4,    2},//PROG_DOWN_B		//2	
	{176,   0,    8,    8,      0,      0,    4,    3},//PROG_SHADOW_D		//3
	{16,    0,    158,  12,     0,      0,    0,    3},//PROG_DOWN_D		//4
	{16,	226,  560,  1,      0,      0,    15,   4},//PROG_BG2_E         	//5						//5
	{16,	227,  560,  39,     0,      0,    2,    4}, //PROG_BG3_E			//6					//6
	{222,	234,  158,  22,     0,      0,    1,    4}, //PROG_PLAY_NORMAL_E 	//7			//7
	{402,	234,  158,  22,     0,      0,    1,    4}, //PROG_RESET_NORMAL_E 	//8			//8

};

//prog data structure:str data,index:0
const OSD_STR_LAYOUT_S g_aOsdProgStr[] =
{
  //{xStart, yStart, xOffset, yOffset, fontColor, bgColor, region}
	{18+23,    0,    0,    0,    14,    0,    2},      //PROG_STR_B	        //0
	{96,       8,    140,  0,    11 ,   0,    4},      		//PROG_STR_COLON     //1
    {60,       10,    140,  0,    11 ,   0,    4},      	//PROG_DVD_TT        //2
    {112+16,      10,    140,  0,    11 ,    0,    4},      //PROG_DVD_CH        //3				      
};
#endif//ifdef OSD_BMP_PROG

#endif //end ifdef OSD_BMP
/*
 *Funciton Description:  
 * 	Draw BMP on osd region r with given colors.
 *  The bmp image data and platte was made by image processing software.
 * 
 * NOTE:
 *  It can draw 4/16/256 color bmp.
 *   
 * zhaoyanhua 2004-3-12 14:16
 */
#if defined (OSD_BMP)

#ifdef NEW_OSD_DRIVER

void osd_draw_bmp_old(int xStart, int yStart,const BYTE* bmp,  BYTE r)
{    
    coordinate  start;
    
    start.x = xStart;
    start.y = yStart;
    
    osd_draw_bmp(&start, bmp,  r);
}
#else

void osd_draw_bmp_old(int xStart, int yStart,const BYTE* bmp,  BYTE r)
{
 
  UINT32  iDispLoc;
	int     i = 0, j = 0, k = 0;
	int     iBmpWidth = 0, iBmpHeight = 0;
	int  	iRegionWidth = region[r].osd_w;
	int 	iOsdFormat = region[r].osd_format;
	int 	iPixPerByte,iBitsPerPix;//Bperpixel: how many bits a pixel need.
							//shift_num: get next pixel position
		
	UINT32 uiBit32;
 	UINT32 uiPos;
 	int iYy = 0;
    UINT32 *pp;
    UINT32 *pTopLine, *pBtmLine;
	pTopLine = (UINT32 *)get_osdbuf_region_ptr(r,0);   // region r top
	pBtmLine = (UINT32 *)get_osdbuf_region_ptr(r,1);   // region r bot
   
	osd_tog_region(r, OSD_ON);

#ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF	
	OSD_GetTrueDispRegion();
	osd_tog_region(temp_region,OSD_OFF);
#endif
	
	iRegionWidth = region[r].osd_w;

	switch (iOsdFormat)
	{
		case OSD_FORMAT_4COLOR://2bit
    		iPixPerByte = 4; // 8/2
    		iBitsPerPix = 2;
    		break;
		case OSD_FORMAT_256COLOR://8bit
#ifdef OSD_SUPPORT_256_COLOR
    		iPixPerByte = 1; // 8/8
    		iBitsPerPix = 8;
    		break;
#else
			return;
#endif	// #ifdef OSD_SUPPORT_256_COLOR
		case OSD_FORMAT_16COLOR://4bit
    		iPixPerByte = 2; // 8/4
    		iBitsPerPix = 4;
    		break;
		default:
    		iPixPerByte = 2; // 8/4
    		iBitsPerPix = 4;
    		break;
	}

	//get Keyboard bmp information
	iBmpWidth  = bmp[0];
	iBmpHeight   = bmp[1];

    //start to process
    uiPos = 2;    
    
    // write how many pixles one time.
	//write 32bit one time.
	unsigned uPixPerTime = 32 / iBitsPerPix;
	unsigned uExeTimes = iBmpWidth / uPixPerTime;
 
	for (j=0; j<iBmpHeight; j++)
	{
    	unsigned uCurByte;
    	iYy = (p_scan) ? yStart : yStart>>1;
        pp = (yStart&1) ? pBtmLine : pTopLine;
    	
    	//NOTE:
    	// the following sentence is to calculate the start position 
    	//in OSD buffer with the byte unit.
    	iDispLoc = (iYy*iRegionWidth) / 4 + (xStart/iPixPerByte) / 4;

        for (i=0; i<uExeTimes; i++)
        {
		    uiBit32 = 0;
		    //bmp   :  Byte1 Byte2 Byte3 Byte4      osd buffer
		    //         0x12   0x34  0x56  0x78     ------>    0x78563412
            for (k=0;k<4;k++)
            //0x12 0x34 0x56 0x78=>0x78 0x56 0x34 0x12
            {
            	unsigned uCurByte = bmp[uiPos++];
            #ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF
            //0 of bmp is display bar's background.
            	if((uCurByte == 0)&&((r== disp_region)||(r== temp_region)))
                {
                	if(OSD_ShowBottomDisp() == 1)
        			    uCurByte = (DISP_SHADOW_CDROM<<4) | DISP_SHADOW_CDROM;
        		    else
                        uCurByte = (DISP_SHADOW << 4) | DISP_SHADOW;
                }
           #endif              
    	        uiBit32 = uiBit32 | (uCurByte<<8*k);
            }           
                pp[iDispLoc + i] =  uiBit32;
            }//end for (i=0; i<uExeTimes; i++)
	        yStart++; //next line
	    }//for bmp height ,end for (j=0; j<iBmpHeight; j++)   
	
}//end osd_draw_bmp_old

#endif  //#ifdef NEW_OSD_DRIVER

#endif // #if defined (OSD_BMP)



#ifdef OSD_BMP_DISPLAY//feeling
/*
 *Funciton Description:  
 * 	Draw BMP on display with tempbuf operation.
 *  The bmp image data and platte was made by image processing software.
 * 
 * NOTE:
 *  It can draw 4/16/256 color bmp.
 *   
 * feeling  2004-8-19
 */
void osd_draw_bmp_display(int xStart, int yStart,const BYTE* bmp,  BYTE r)
{

	UINT32  iDispLoc;
	int     i = 0, j = 0, k = 0;
	int     iBmpWidth = 0, iBmpHeight = 0;
	int  	iRegionWidth = region[r].osd_w;
	int 	iOsdFormat = region[r].osd_format;
	int 	iPixPerByte,iBitsPerPix;//Bperpixel: how many bits a pixel need.
							//shift_num: get next pixel position
		
	UINT32 uiBit32;
 	UINT32 uiPos;
 	
 	UINT32  *buf;
    
	osd_tog_region(r, OSD_ON);
	iRegionWidth = region[r].osd_w;


	switch (iOsdFormat)
	{
		case OSD_FORMAT_4COLOR://2bit
    		iPixPerByte = 4; // 8/2
    		iBitsPerPix = 2;
    		break;
		case OSD_FORMAT_256COLOR://8bit
#ifdef OSD_SUPPORT_256_COLOR
    		iPixPerByte = 1; // 8/8
    		iBitsPerPix = 8;
    		break;
#else
			return;
#endif	// #ifdef OSD_SUPPORT_256_COLOR
		case OSD_FORMAT_16COLOR://4bit
    		iPixPerByte = 2; // 8/4
    		iBitsPerPix = 4;
    		break;
		default:
    		iPixPerByte = 2; // 8/4
    		iBitsPerPix = 4;
    		break;
	}

	buf = (UINT32 *)(osd_temp_buf);

	//get Keyboard bmp information
	iBmpWidth  = bmp[0];
	iBmpHeight   = bmp[1];

    //start to process
    uiPos = 2;    
    
    // write how many pixles one time.
	//write 32bit one time.
	int uPixPerTime = 32 / iBitsPerPix;
	int uExeTimes = iBmpWidth / uPixPerTime;
 
	for (j=0; j<iBmpHeight; j++)
	{
    	unsigned uCurByte;
    	
    	//NOTE:
    	// the following sentence is to calculate the start position 
    	//in OSD buffer with the byte unit.
    	iDispLoc = (yStart*iRegionWidth) / 4 + (xStart/iPixPerByte) / 4;

   	    for (i=0; i<uExeTimes; i++)
        {
	        uiBit32 = 0;
	        //bmp   :  Byte1 Byte2 Byte3 Byte4      osd buffer
	        //         0x12   0x34  0x56  0x78     ------>    0x78563412
            for (k=0;k < 4;k++)//32 bit one time 
            {
                uCurByte = bmp[uiPos++];
	            if(uCurByte == 0)
                {
                    #ifdef DISP_REGION_BOTTOM
                    //fill background color to transparent area of the bmp icon 
    		        if(OSD_ShowBottomDisp() == 1)
                        uCurByte = (DISP_SHADOW_CDROM<<4) | DISP_SHADOW_CDROM;
			        else
    			    #endif//DISP_VARIABLE_REGION	            
                        uCurByte = (DISP_SHADOW << 4) | DISP_SHADOW;
                }	
               // when high 4bit is 0 and low 4bit is 0 , for bmp matrix date,fill background color to transparent area of the bmp icon , because of 4bit represent a color for 16_color bmp.zhuyf 20/12/2004 15:31
		        else if((uCurByte & 0xf0) == 0)
		        {                    
		            if(OSD_ShowBottomDisp() == 1)
                        uCurByte = (DISP_SHADOW_CDROM<<4) | (uCurByte& 0x0f);
			        else
                        uCurByte = (DISP_SHADOW << 4) | (uCurByte& 0x0f);                                         
                }			                  
		        else if((uCurByte & 0x0f) == 0)
		         {                 
		            if(OSD_ShowBottomDisp() == 1)
                        uCurByte = (DISP_SHADOW_CDROM) | (uCurByte& 0xf0);
			        else
                        uCurByte = (DISP_SHADOW ) | (uCurByte& 0xf0);                                                       
                }			        

		        if(((uCurByte & 0xff) == 0)&&((uCurByte & 0x0f) == 0)&&((uCurByte & 0xf0) == 0))
		            continue;
                //there is error in the underside ,marked ,instead by the above part. zhuyf  20/12/2004 15:33
                /*
		        if((uCurByte & 0xf0) == 0)
                {
			        uiBit32 = (uiBit32 & (~( 0xf0<<k*8))) |(uCurByte<<(k*8));
		        }
		            else if((uCurByte & 0x0f) == 0)
		        {
			        uiBit32 = (uiBit32 & (~( 0x0f<<k*8))) |(uCurByte<<(k*8));
		        }
		        */
		        
		            else
                {	
                    uiBit32 = (uiBit32 & (~( 0xff <<k*8))) |(uCurByte<<(k*8));
                }
                //if curBYTE == 0x00,not dispose it.
            }//end for (k=0;k < 4;k++)
            buf[iDispLoc + i] =  uiBit32;//fill 32bits to osd temp buf
        }//end for (i=0; i<uExeTimes; i++)
	    yStart++; //next line
	}//for bmp height ,end for (j=0; j<iBmpHeight; j++)
}//end osd_draw_bmp_display()
#endif //OSD_BMP_DISPLAY

#ifdef OSD_BMP

/* 
 *Funciton Description:  
 * 	Draw little string on osd
 *  
 * INPUT:
 *   xStart,yStart     --> the start of string,
 *   str               --> string 
 *   fontColor,bkColor --> the string font color and background color
 *   r                 --> region
 * 
 * NOTE:
 *  its size is 1/4 size of normal string
 *  
 *  suqiaoli add 2004-11
 */

void osd_Draw_Bmp_Little_RegionString(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r)
{
    BYTE    *pFont, c;
    UINT8  *pTopLine, *pBtmLine;
    UINT32  iDispLoc, iStrLoc;
    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[r].osd_w;

    osd_tog_region(r, OSD_ON);  
    
#ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF	
	OSD_GetTrueDispRegion();
	osd_tog_region(temp_region,OSD_OFF);
#endif
    
    //initialize buffer start
    pTopLine = (UINT8 *)get_osdbuf_region_ptr(r,0);
    pBtmLine = (UINT8 *)get_osdbuf_region_ptr(r,1);
    iStrLoc = 0;
       
    if (p_scan==1)
    {
#ifdef NEWSTYLE_WINDOW   //xiongyuyue
        if(full_scrn&MESSAGE)
            iDispLoc = (yStart*iRegionWidth) + (xStart);
        else
#endif
        	//iDispLoc = (yStart*iRegionWidth) + (xStart*16/8)+(iRegionWidth/2);
        	iDispLoc = yStart*iRegionWidth + xStart/2;
    }
    else
    {
#ifdef NEWSTYLE_WINDOW   //xiongyuyue
    if(full_scrn&MESSAGE)
        iDispLoc = (yStart*iRegionWidth/2) + (xStart);
    else
#endif
	 	iDispLoc = (yStart*iRegionWidth+xStart)/2;
    }
    
    iDispLoc = iDispLoc*2;
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    //iDispLoc += (iRegionWidth/4 * 2);
    
    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)str)[iStrLoc]) != '\0' ) 
    {
        BYTE curByte = 0;
        UINT32 pixel8;
        UINT32 pos;
        
        iStrLoc++;
        
        if (c == '\r') 
        { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' )
                break;
            
            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        }

#if defined(NEWSTYLE_WINDOW)||defined(NEW_STYLE_SETUP)  || defined(SUPPORT_REP_READ) //maoyong add 0915
        else if(c == '\a')
        {
            if ( (c=((BYTE *)str)[iStrLoc])=='\0' ) break;
            
            iStrLoc++;

            if ((pFont = get_font_entry(3,c))==NULL) continue;

        }
#endif 
		else if(c>='a' && c<='z')
		{
		    pFont=get_font_entry(0,c-'a'+0xc0);
		}
	    else 
        	//get current char entry
        	pFont = get_font_entry(0,c);
  
	    //start to process
	    pos = 3;
	    //get font information
	    iFontWidth = (int)pFont[0];
	    iFontHigh = (int)pFont[1];

		if(p_scan==0)
			iFontHigh>>=1;
          
        //start to draw        
		for (j=0; j<iFontHigh; j++) 
		{
            //For every string line = 1 blank line(in pixel) + OSD_FONT_HEIGHT-line strings + 1 blank line
            //draw top line
            for (i=0; i<iFontWidth/2; i++) 
            {
				BYTE c;
				c=pFont[pos+i/4];
				pixel8 = pTopLine[iDispLoc+i];//zhao add 2004-2-27 14:41

	          	switch(i%4)
          	   	{
	          	   	case 0:
						curByte=(c&0xc0)>>6;
						break;
					case 1:
						curByte=(c&0x30)>>4;
		            	break;
					case 2:	
		            	curByte=(c&0x0c)>>2;
	              		break;
	              	case 3:	
	              		curByte=(c&0x03);
	              		break;
          		}
          	
				for (k=0; k<2; k++) 
				{
	            	if ( (1<<k) & curByte ) 
	            	{          
	            		pixel8 = (pixel8 & (~( 0x0f<<k*4))) |(fontColor<<(k*4));//zhao add 2004-2-27 14:41
	            	} 
	            	else 
	           		{
	                	if(bkColor != 0)//if color index is 0, no need to change the vlaue fo pixel8
	                	pixel8 = (pixel8 & (~( 0x0f<<k*4))) | (bkColor<<(k*4));//zhao add 2004-2-27 14:41
	           		}
				}
           		if((i % 2 == 0) &&(j % 2 == 0)) //four dots ---> one dot
             		 pTopLine[(iDispLoc+i)/2] = pixel8;
            }

        	if(iFontWidth%8)
				pos=pos+iFontWidth/8+1;
        	else
        		pos=pos+iFontWidth/8;
      
            if(p_scan==0)
            {
               //draw bottom line
               for (i=0; i<iFontWidth/2; i++) 
               {
                	BYTE c;
					c=pFont[pos+i/4];
                	pixel8 = pBtmLine[iDispLoc+i];//zhao add 2004-2-27 14:41

					switch(i%4)
					{
          			case 0:
						curByte=(c&0xc0)>>6;
						break;
					case 1:
						curByte=(c&0x30)>>4;
	                     break;
	                case 2:	
	                	curByte=(c&0x0c)>>2;
              			break;
              		case 3:	
              			curByte=(c&0x03);
              			break;
					}
					for (k=0; k<2; k++) 
					{          
						if ( (1<<k) & curByte ) 
                    	{
                			pixel8 = (pixel8 & (~( 0x0f<<k*4))) |(fontColor<<(k*4));//zhao add 2004-2-27 14:41
			  			} else
			  			{
                        	if(bkColor != 0)//if color index is 0, no need to change the vlaue fo pixel8
                        	pixel8 = (pixel8 & (~( 0x0f<<k*4))) | (bkColor<<(k*4));//zhao add 2004-2-27 14:41
                    	}
                 	 }
           			if((i % 2 == 0) &&(j % 2 == 0)) //four dots ---> one dot
        	        	pBtmLine[(iDispLoc+i)/2] = pixel8;
               }
            
   			if(iFontWidth%8)
				pos=pos+iFontWidth/8+1;
        	else
        		pos=pos+iFontWidth/8;
        		
            }
            
            iDispLoc += iRegionWidth;
            

        }//for charactor heigh  
        
         //move to next character and move up to first line of this string
        iDispLoc = iDispLoc + (iFontWidth/2) - (iRegionWidth*iFontHigh);
    
    } // end of while ( (c=((BYTE *)str)[unFontLoc])!='\0' )
    
    //timeout_osd[r] = 0;//zhaoyanhua mask it. 
}
/*
 *Funciton Description:  
 * 	Draw  string on osd
 *  
 * 
 * INPUT:
 *   xStart,yStart     --> the start of string,
 *   str               --> string 
 *   fontColor,bkColor --> the string font color and background color
 *   r                 --> region
 *   
 * suqiaoli add 2004-11
 */

void osd_Draw_Bmp_RegionString(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r)
{
    BYTE    *pFont, c;
    UINT8  *pTopLine, *pBtmLine;
    UINT32  iDispLoc, iStrLoc;
    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[r].osd_w;

    osd_tog_region(r, OSD_ON);  
    
#ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF	
	OSD_GetTrueDispRegion();
	osd_tog_region(temp_region,OSD_OFF);
#endif 
    
    //initialize buffer start
    pTopLine = (UINT8 *)get_osdbuf_region_ptr(r,0);
    pBtmLine = (UINT8 *)get_osdbuf_region_ptr(r,1);
    iStrLoc = 0;
       
    if (p_scan==1)
    {
#ifdef NEWSTYLE_WINDOW   //xiongyuyue
        if(full_scrn&MESSAGE)
            iDispLoc = (yStart*iRegionWidth) + (xStart);
        else
#endif
            //iDispLoc = (yStart*iRegionWidth) + (xStart*16/8)+(iRegionWidth/2);
            iDispLoc = yStart*iRegionWidth+ xStart/2;
    }
    else
    {
#ifdef NEWSTYLE_WINDOW   //xiongyuyue
    if(full_scrn&MESSAGE)
        iDispLoc = (yStart*iRegionWidth/2) + (xStart);
    else
#endif
	    iDispLoc = (yStart*iRegionWidth+xStart)/2;
    }
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    //iDispLoc += (iRegionWidth/4 * 2);
    
    //process each charactor until string ending('\0')
    while ( (c = ((BYTE *)str)[iStrLoc]) != '\0' ) 
    {
        BYTE curByte = 0;
        UINT32 pixel8;
        UINT32 pos;
        
        iStrLoc++;
        
        if (c == '\r') 
        { //prefix characher:to use font_table2
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' )
                break;
            
            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        }

#if defined(NEWSTYLE_WINDOW)||defined(NEW_STYLE_SETUP)  || defined(SUPPORT_REP_READ) //maoyong add 0915
        else if(c == '\a')
        {
            if ( (c=((BYTE *)str)[iStrLoc])=='\0' ) break;
            
            iStrLoc++;

            if ((pFont = get_font_entry(3,c))==NULL) continue;

        }
#endif 
		else if(c>='a' && c<='z')
			pFont=get_font_entry(0,c-'a'+0xc0);
	    else
	        //get current char entry
	        pFont = get_font_entry(0,c);

   
        //start to process
        pos = 3;
        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh = (int)pFont[1];

        if(p_scan==0)
          iFontHigh>>=1;
          
        //start to draw        
        for (j=0; j<iFontHigh; j++) 
        {
            //For every string line = 1 blank line(in pixel) + OSD_FONT_HEIGHT-line strings + 1 blank line
            //draw top line
            for (i=0; i<iFontWidth/2; i++) 
            {
                BYTE c;
                c=pFont[pos+i/4];
                pixel8 = pTopLine[iDispLoc+i];//zhao add 2004-2-27 14:41
	          	
	          	switch(i%4)
          	   	{
	          	   	case 0:
					    curByte=(c&0xc0)>>6;
					    break;
				    case 1:
					    curByte=(c&0x30)>>4;
		                break;
		            case 2:	
		                curByte=(c&0x0c)>>2;
	              		break;
	              	case 3:	
	              		curByte=(c&0x03);
	              		break;
          		}
          	
                for (k=0; k<2; k++) 
                {
	                if ( (1<<k) & curByte ) 
	                    pixel8 = (pixel8 & (~( 0x0f<<k*4))) |(fontColor<<(k*4));//zhao add 2004-2-27 14:41
	                else 
	                {
	                    if(bkColor != 0)//if color index is 0, no need to change the vlaue fo pixel8
	                    pixel8 = (pixel8 & (~( 0x0f<<k*4))) | (bkColor<<(k*4));//zhao add 2004-2-27 14:41
	                }
                }
                pTopLine[iDispLoc+i] = pixel8;
            }

        	if(iFontWidth%8)
			    pos=pos+iFontWidth/8+1;
        	else
        		pos=pos+iFontWidth/8;
      
            if(p_scan==0)
            {
               //draw bottom line
               for (i=0; i<iFontWidth/2; i++) 
               {
                	BYTE c;
			        c=pFont[pos+i/4];
                	pixel8 = pBtmLine[iDispLoc+i];//zhao add 2004-2-27 14:41
	              
                    switch(i%4)
                    {
              			case 0:
    					    curByte=(c&0xc0)>>6;
    					    break;
    				    case 1:
    					    curByte=(c&0x30)>>4;
    	                    break;
    	                case 2:	
    	                    curByte=(c&0x0c)>>2;
                  			break;
                  		case 3:	
                  			curByte=(c&0x03);
                  			break;
          			}
                    for (k=0; k<2; k++) 
                    {          
                    	if ( (1<<k) & curByte ) 
                			pixel8 = (pixel8 & (~( 0x0f<<k*4))) |(fontColor<<(k*4));//zhao add 2004-2-27 14:41
                        else
			  	        {
                            if(bkColor != 0)//if color index is 0, no need to change the vlaue fo pixel8
                        		pixel8 = (pixel8 & (~( 0x0f<<k*4))) | (bkColor<<(k*4));//zhao add 2004-2-27 14:41
                        }
                 	 }

        	        pBtmLine[iDispLoc+i] = pixel8;
                }
            
   		    if(iFontWidth%8)
			    pos=pos+iFontWidth/8+1;
        	else
        		pos=pos+iFontWidth/8;
            
            }
            
            iDispLoc += iRegionWidth;
            

        }//for charactor heigh  
        
         //move to next character and move up to first line of this string
        iDispLoc = iDispLoc + (iFontWidth/2) - (iRegionWidth*iFontHigh);
   
    } // end of while ( (c=((BYTE *)str)[unFontLoc])!='\0' )

}


/* 
 * Fuction:
 *	  osd_draw_repeat_bmp()
 * Description:
 *      draw the bmp repeatly.
 *
 * INPUT:
 *      uiXStart,uiYStart --> the start of bmp, 
 *      uiXWidth,uiYStart --> the width and height of the needed bmp by repeat line bmp
 *      r----> region
 *CREATOR: feeling
 * DATE: 2004-10-28 
 */
void osd_draw_repeat_bmp(UINT16 uiXStart,UINT16 uiYStart,UINT16 uiXWidth,UINT16 uiYHeight,const BYTE* bmp,BYTE r)
{
    
		UINT16 uiXRepeat = 0;
		UINT16 uiYRepeat = 0;
		UINT16 uiCurX;
	    	UINT16 uiCurY;
	    	int i,j;

		//the uiXWidth is the demand width that can be seen on the screen, and bmp[0] is the actual size of bmp
    		//i.e. uiXWidth = 576, bmp[0] = 2, it means the bmp needs to be drawn for 288 times one by one repeatly
		if(uiXWidth % bmp[0])
			uiXRepeat = uiXWidth / bmp[0] + 1;
		else
		uiXRepeat = uiXWidth / bmp[0];

		if(uiYHeight % bmp[1])
			uiYRepeat = uiYHeight / bmp[1] + 1;
		else
		uiYRepeat = uiYHeight / bmp[1];
	
		
		for (j = 0, uiCurY = uiYStart; j < uiYRepeat; j++, uiCurY += bmp[1] )
    		{
        		for (i = 0,uiCurX = uiXStart; i < uiXRepeat; i++, uiCurX += bmp[0] )
        		{
          			// printf("uiCurX = %d\n",uiCurX);
            			osd_draw_bmp_old(uiCurX, uiCurY, bmp, r);
        		}
    		}
    		           
}

/* 
 * Fuction:
 *	  OSD_LayoutBmp()
 * Description:
 *      draw the bmp defined in g_aOsdBitmapLayout[],  according to the index.
 *	if offset equals to 0 and uiOffsetIndex also equals to 0 , that means draw a single bitmap.

 * INPUT:
 *      uiLayoutBmpIndex -->index of g_aOsdBitmapLayout[]
 * 	 uiOffsetIndex --->> the offset index,such as page or level etc.
 * NOTE:
 *      the postion of the bmp is not fixed ,it can be variable,according to the offset.
*
 *CREATOR: feeling
 * DATE: 2004-07-08 15:12
  *modify: feeling 2004-10-25
 */
void OSD_LayoutBmp(UINT8 uiLayBmpIndex,UINT8 uiOffsetIndex)
{

	const OSD_BITMAP_LAYOUT_S* pLayout = 0;
	const BYTE*	bmp;
	UINT16 uiXPos = 0;
	UINT16 uiYPos = 0;
	
	//select layout bitmap infomation
	switch (full_scrn)
	{
#ifdef OSD_BMP_SOUND
		case SOUND:
		    pLayout =  &g_aOsdSoundBmp[uiLayBmpIndex];
		    break;
#endif
#ifdef OSD_BMP_PROG
		case PROGRAM:
		    pLayout =  &g_aOsdProgBmp[uiLayBmpIndex];
		    break;
#endif
	}
	

	// the actual bmp width and height
	bmp = g_aOsdBitmap[pLayout->uiIndex];

	//the pos of the bitmap according to the uiPage and offset
	uiXPos = pLayout->uiXStart + uiOffsetIndex * pLayout->uiXOffset;
	uiYPos = pLayout ->uiYStart + uiOffsetIndex * pLayout ->uiYOffset;

	
	// draw bmp no need repeat
	if (((pLayout->uiXWidth == 0) && (pLayout->uiYHeight == 0))//have not fill the width and height in array
	    ||((pLayout->uiXWidth == bmp[0]) && (pLayout->uiYHeight == bmp[1])))//fill the width and height in array
	{
		osd_draw_bmp_old(uiXPos,
            uiYPos, 
            bmp, 
            pLayout->bRegion);
	}		

	//draw bmp need  repeat
	else
	{	
		osd_draw_repeat_bmp(uiXPos, 
		    uiYPos,
            pLayout->uiXWidth,
            pLayout->uiYHeight,
            bmp,
            pLayout->bRegion);		                    
	}//end else
	
}//end Osd_LayoutBmp


/* 
 * Fuction:
 *	  OSD_LayoutLine()
 * Description:
 *      draw the bmp defined in g_aOsdLineLayout[],  according to the index.
 *	if offset equals to 0 and uiOffsetIndex also equals to 0 , that means draw a single line.

 * INPUT:
 *      uiLayoutLineIndex --> index of g_aOsdLineLayout[], 
 *	uiOffsetIndex --->index of the offset, such as page and level etc.
 *
 *CREATOR: feeling
  *DATE: 2004-10-25
 */
void OSD_LayoutLine(UINT16 uiLayLineIndex, UINT8 uiOffsetIndex)
{

	const OSD_LINE_LAYOUT_S* pLayout = 0;
	UINT16 uiXPos = 0;
	UINT16 uiYPos = 0;
	
	//pick out the layout line infomation
	switch (full_scrn)
	{
#ifdef OSD_BMP_SOUND
		case SOUND:
		    pLayout =  &g_aOsdSoundLine[uiLayLineIndex];
		    break;
#endif		    
#ifdef OSD_BMP_PROG
		case PROGRAM:
		    pLayout =  &g_aOsdProgLine[uiLayLineIndex];
		    break;
#endif		    
	}

	uiXPos = pLayout ->uiXStart + uiOffsetIndex * pLayout->uiXOffset;
	uiYPos = pLayout ->uiYStart + uiOffsetIndex * pLayout ->uiYOffset;
	    
	//draw the line according to its info structure
	osd_draw_hline_region(uiXPos, 
	    uiXPos + pLayout->uiXLen, 
	    uiYPos,
	    pLayout->uiColor, 
	    pLayout->uiYLen,
	    pLayout->bRegion);
		
}//end OSD_LayouPosVariableLine

/* 
 * Fuction:
 *	  OSD_LayoutRect()
 * Description:
 *      draw the bmp defined in g_aOsdRectLayout[],  according to the index.
 *
 * INPUT:
 *      uiLayoutRectIndex --> index of g_aOsdRectLayout[], 
 *		uiOffsetIndex ----> the offset index , such as page and level, etc.
*
 *CREATOR: feeling
  *DATE: 2004-10-25
 */
void OSD_LayoutRect(UINT16 uiLayRectIndex, UINT8 uiOffsetIndex)
{

	const OSD_RECT_LAYOUT_S* pLayout = 0;
	
	//pick out the layout line infomation
	switch (full_scrn)
	{
#ifdef OSD_BMP_SOUND
		case SOUND:
		    pLayout =  &g_aOsdSoundRect[uiLayRectIndex];
		    break;
#endif		    
#ifdef OSD_BMP_PROG
		case PROGRAM:
		    pLayout =  &g_aOsdProgRect[uiLayRectIndex];
		    break;
#endif    
	}

	osd_draw_region_rect(pLayout->uiXStart + uiOffsetIndex * pLayout->uiXOffset,
	    pLayout->uiYStart + uiOffsetIndex * pLayout ->uiYOffset,
	    pLayout->uiXWidth,
        pLayout->uiYHeight,
        pLayout->uiBgColor,
        pLayout->bRegion);
		
}//end OSD_LayoutRect




/* 
 * Fuction:
 *	  OSD_LayoutStr()
 * Description:
 *      draw the bmp defined in g_aOsdStrLayout[],  according to the index.
 *		 	  if offset equals to 0 and uiOffsetIndex also equals to 0 , that means draw a single string.

 * INPUT:
 *      uiLayoutStrIndex --> index of g_aOsdStrLayout[], 
 *		str--->the str need to be showed
 *		uiOffsetIndex ----> the offset index , such as page and level, etc.
*
 *CREATOR: feeling
  *DATE: 2004-10-25
 */
void OSD_LayoutStr(const BYTE *str, UINT16 uiLayStrIndex, UINT8 uiOffsetIndex)
{

	const OSD_STR_LAYOUT_S* pLayout = 0;
	
	//pick out the layout line infomation
	switch (full_scrn)
	{
#ifdef OSD_BMP_SOUND
		case SOUND:
		    pLayout =  &g_aOsdSoundStr[uiLayStrIndex];
		    break;
#endif		    
#ifdef OSD_BMP_PROG		
		case PROGRAM:
		    pLayout =  &g_aOsdProgStr[uiLayStrIndex];
		    break;
#endif	    
	}

	osd_Draw_Bmp_RegionString(pLayout->uiXStart + uiOffsetIndex * pLayout->uiXOffset,
	    pLayout->uiYStart + uiOffsetIndex * pLayout ->uiYOffset,
	    str,
	    pLayout->uiFontColor,
	    pLayout->uiBgColor,
	    pLayout->bRegion);
		
}//end OSD_LayoutStr

/* 
 * Fuction:
 *	  OSD_LayoutLittleStr()
 * Description:
 *      draw the string defined in g_aOsdStrLayout[],  according to the index.
 *		 	  if offset equals to 0 and uiOffsetIndex also equals to 0 , that means draw a single string.

 * INPUT:
 *      uiLayoutStrIndex --> index of g_aOsdStrLayout[], 
 *		str--->the str need to be showed
 *		uiOffsetIndex ----> the offset index , such as page and level, etc.
 *
 * Note:Layout little (1/4 size of normal)string
 */

void OSD_LayoutLittleStr(const BYTE *str, UINT16 uiLayStrIndex, UINT8 uiOffsetIndex)
{
	const OSD_STR_LAYOUT_S* pLayout = 0;
	
	//pick out the layout line infomation
	switch (full_scrn)
	{
#ifdef OSD_BMP_SOUND
		case SOUND:
		    pLayout =  &g_aOsdSoundStr[uiLayStrIndex];
		    break;
#endif		    
#ifdef OSD_BMP_PROG		
		case PROGRAM:
		    pLayout =  &g_aOsdProgStr[uiLayStrIndex];
		    break;
#endif	    
	}

    osd_Draw_Bmp_Little_RegionString(pLayout->uiXStart + uiOffsetIndex * pLayout->uiXOffset,
	    pLayout->uiYStart + uiOffsetIndex * pLayout ->uiYOffset,
	    str,
	    pLayout->uiFontColor,
	    pLayout->uiBgColor,
	    pLayout->bRegion);
		
}//end OSD_LayoutStr


#ifdef OSD_BMP_DISPLAY//feeling
void OSD_LayoutBmpDisplay(UINT8 uiLayoutIndex)
{

	const OSD_BITMAP_LAYOUT_S* pLayout = 0;
	
	//select layout bitmap infomation
	pLayout =  &g_aOsdDispBmp[uiLayoutIndex];
	
	//only draw bmp no need repeat
	if ((pLayout->uiXWidth!= 0) 
       	||(pLayout->uiYHeight != 0))
		return;
 
	#ifdef OSD_VARIABLE_TEMP_DISPLAY_BUF
    	osd_draw_bmp_old(pLayout->uiXStart, pLayout->uiYStart, 
        	     g_aOsdBitmap[pLayout->uiIndex], 
        	     temp_region);
	#else
    	osd_draw_bmp_display(pLayout->uiXStart, pLayout->uiYStart, 
                 g_aOsdBitmap[pLayout->uiIndex], 
                 disp_region);
    #endif 	     

}//end Osd_LayoutBmpDisplay
#endif//#ifdef OSD_BMP_DISPLAY






#endif//ifdef OSD_BMP

