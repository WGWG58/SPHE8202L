#include "global.h"
#include "func.h" 
#include "memmap.h"
#include "util.h" 
#include "graph.h"
#include "framebuf.h"
#include "macro.h"
#include "stc.h"
#include "cfont.h"
#include "vfdfunc.h"
#include "osd.h"
#include "image.h"
#include "iop.h"
#include "memcfg.h"
#include "ircmd.h"
#include "dsp3_if.h"

#include "user_init.h"
#include "nesinit.h"
#include "fs96602.h"

#include "fsNAV.h"

#include "fsGUI.h"
#include "stdlib.h"

#include "fsgui_rgb8.inc"

void FSGUI_DecImg(BYTE *src, BYTE *dest, UINT32 iSrcLen, UINT32 *destLen)
{
	unsigned char cHeader;
	register unsigned char i;
	UINT32 iCurI, iCurO;
	BYTE *pSrc, *pDest;
	
	iCurI = iCurO = 0;
	pSrc = src;
	pDest = dest;
	
	while (iCurI < iSrcLen) {
		cHeader = *(pSrc+iCurI++);
		
		if (cHeader & 0x80) {
			unsigned char array_to_write[129];
			BYTE ch;
			unsigned char i;
			
			ch = *(pSrc+iCurI++);
			
			memset(array_to_write, ch, (cHeader & 127)+2);
			
			for (i=0; i<((cHeader & 127)+2); i++) {
				*(pDest+iCurO++) = *(array_to_write+i);
			}
		} else {
			for (i=0;i<=cHeader;i++) {
				BYTE ch;
				
				ch = *(pSrc+iCurI++);
				
				*(pDest+iCurO++) = ch;
			}
		}
	} // end of while (!end_of_data())
	
	*destLen = iCurO;
}


void FSGUI_FillFrameBuf(int x, int y, int xSize, int ySize, UINT16 color_Y, UINT16 color_CrCb)
{
    int i, j;
    for (j = y; j < y + ySize; j++)
    {
        for (i = x; i < x + xSize; i++)
        {
            *Y_XY(i, j) = (color_Y) & 0xff;
            *C_XY(i, j) = color_CrCb;
        }
    }
}


void FSGUI_ReplaceFrameBuf(int x, int y, int xSize, int ySize, UINT16 replace_Y, UINT16 replace_CrCb, UINT16 color_Y, UINT16 color_CrCb)
{
    int i,j;
    for (j=y; j<y+ySize; j++)
    {
        for (i=x; i<x+xSize; i++)
        {
            UINT8  *py = Y_XY(i,j);
            UINT16 *pc = C_XY(i,j);
            if (py[0]==(replace_Y&0xff) && pc[0]==replace_CrCb)
            {
	        py[0] = color_Y;
	        pc[0] = color_CrCb;
            }
        }
    }
}

	//freyman add 2004-4-19 19:05, to collect the public function in fsGUI1.c and fsGUI_new.c
	#include "fsGUI_pub.c"
	
	//Notes: Now most of the functions in fsGUI1. and fsGUI_new.c
	//		 have been move to fsGUI_pub.c
	//       Any question contact me, wanghaoying 2004-05-14 14:00
	#if defined (NEW_MP3_GUI) || defined(INDIGO_STYLE_FSGUI)  //zhaoyanhua add for new MP3 GUI 3-7-10 14:11
		#ifdef MP3_LARGE_GUI	//Maoyong add for new large GUI, 2003/12/19 14:47
	 	#include "fsGUI_new_large.c"
		#else    
    	#include "fsGUI_new.c"
   		#endif
    #elif defined FS_BMP_GUI//zhaoyanhua add 2004-6-8 9:52
    	#include "fsGUI_BmpUI.c"
	#else
	    #include "fsGUI1.c"
	#endif//ifdef NEW_MP3_GUI
	#if 0//def  FAT_FILE_MODE  //wthsin , 2004/10/8 09:26am//liweihua mark 2004-11-2
	    #include "filemode_GUI.c"
	#endif//ifdef FAT_FILE_MODE 
	#ifdef  FILE_MODE_WRITE  //sunzhh 20041225
	    #include "filemodeGUI_pub.c"
	#endif//ifdef FILE_MODE_WRITE    
   


//Don't remove the following(use the same font set as OSD)
#if 0//20020801
void FSShowChar_Bfm(UINT16 x, UINT16 y, BYTE c, BYTE iY, UINT16 iCbCr)
{	
	int     i, j, i4x, j2x;
	BYTE    *pFont;
	UINT32  my16Bits;
	
	pFont = get_font_entry(0,c+22);
	//draw a character
	for (i=0; i<12; i++) {
		BYTE    c1, c2;
		
		i4x = i << 2;
		
		c1 = pFont[3+i4x];
		c2 = pFont[4+i4x];
		
		my16Bits = (c1<<8) | c2;
		
		for (j=0; j<8; j++) {
			j2x = j << 1;
			
			if ( (1<<j2x) & my16Bits) {
				*Y_XYB( (x+8-j), (y+i) ) = iY;
				*C_XYB( (x+8-j), (y+i) ) = iCbCr;
			}
		}
	}
}

/*
void draw_char_3byte2line(unsigned char *FontBitmap, int x, int y, BYTE iY, UINT16 iCbCr)
{
	int px, py, bit, i, j;

	for(i = 0; i < 6; i++)
	{
		//3byte => 
		//1st byte-> 1st line MSB 8 pixels, 3th byte-> 2nd line MSB 8 pixels
		//2nd byte-> 1st line LSB 4 pixels,2nd line LSB 4 pixels
		py = i << 1;
		for (j = 0; j < 3; j++)
		{
			if (j == 1)
				px = 8;
			else
				px = 0;

			for (bit = 0; bit < 8; bit++, px++)
			{
				if ((j == 1) && (bit == 4))
				{
					py++;
					px = 8;
				}
				
				if (*(FontBitmap + j) & (1 << (7 - bit)))
				{
					*Y_XY((x + px), (y + py)) = iY;
					*C_XY((x + px), (y + py)) = iCbCr;
				}
			}
        }
        FontBitmap += 3;
    }
}
*/

#if defined( USE_BIG5_FONT )
extern const unsigned char JMT_BIG5_12X12_FONT_BITMAP[];
#define  big5font_table     JMT_BIG5_12X12_FONT_BITMAP

#elif defined( USE_BIG5_COMMON_FONT )
extern const unsigned char JMT_BIG5_12X12_FONT_BITMAP_COMMON[];
#define  big5font_table     JMT_BIG5_12X12_FONT_BITMAP_COMMON

#elif defined USE_GB2312_FONT
extern const unsigned char GUO_GB2312_12X12_FONT_BITMAP[];
#define  hzfont_table     GUO_GB2312_12X12_FONT_BITMAP
#endif

#ifdef USE_GB2312_FONT

#ifdef MP3_LARGE_GUI	//Maoyong add for 32*24 HZ display in 720*480 GUI
#define ROW 2
#define COL  2
void FSGUI_GBShowChar(BYTE vid, int x, int y, BYTE c, BYTE c1, BYTE iY, UINT16 iCbCr)
{
	int index, i,i4x = 0;
    	UINT8 font1[24];
	BYTE cc1, cc2, cc3,cc4;


	/************************************************************
	1. get Font from 12*12 Hz Library and transfer back to 16*12, 
	even byte's low 4 bytes is all 0
	*******************************88888888**********************/
	index = 18 * ((c - 161) * 94 + c1 - 161);
	//draw a character
	for (i = 0; i < 12; i++)
	{
		if(i % 2)
		{
			i4x = i4x + 2;
			cc1 = hzfont_table[index + i4x];
			cc2 = hzfont_table[index + i4x - 1] & 0x0f;
           		 font1[i*2]=cc1;
            		font1[i*2+1]=(cc2<<4);
		}
		else
		{
			i4x = i * 3 / 2;
			cc1 = hzfont_table[index + i4x];
			cc2 = hzfont_table[index + i4x + 1] & 0xf0;
            		font1[i*2]=cc1;
            		font1[i*2+1]=(cc2);
		}
	}
    /****************************************************
	2.Transfer 16*12 to 32 *24 Font	
	*****************************************************/
	BYTE j, k, m, n;
	BYTE width,height;
    	width=16;
    	height=12;
    	UINT16 my16bits=0;
    	UINT8 font2[24*ROW*COL];

	for (i=0;i<height;i++)
       	for(n=0;n<ROW;n++)
            		for(j=0;j<(width/8);j++){
                		for(k=0;k<8;k++)
                    			for(m=0;m<COL;m++)
                        			if((font1[i*2+j]>>(7-k))&0x01)
                             			my16bits |= (1<<(width-1-(k*COL+m)));
                	font2[(i*ROW+n)*4+j*COL]=(my16bits>>8);
                	font2[(i*ROW+n)*4+j*COL+1]=my16bits&0xff;
                	my16bits=0;
            		}
		
       /****************************************************
	3. Draw every valid pixel in this Chinese Font: 
	because the Last 8 bit of a line's 32 bit is always 0, just 24*24
	*****************************************************/
	UINT32 my24Bits = 0;       
       for(i = 0; i<24; i++)	//height
       {
       	i4x = i*4;
       	cc1 = font2[i4x];
       	cc2 = font2[i4x + 1];
       	cc3 = font2[i4x + 2];
       	cc4 = font2[i4x + 3];
       	my24Bits = (cc1<<16) + (cc2<<8) + cc3;	
       	for(j = 0; j<24; j++) //width
       	{
       		if ((1 << j) & my24Bits) 
			{
				*Y_XY( (x + 24 - j),  (y+i) ) = iY;
				*C_XY( (x + 24 - j),  (y+i) ) = iCbCr;				
			}
       	}
       }       
}
#else
void FSGUI_GBShowChar(BYTE vid, int x, int y, BYTE c, BYTE c1, BYTE iY, UINT16 iCbCr)
{
	int index, i, j, i4x = 0;
	UINT32 my12Bits;

	index = 18 * ((c - 161) * 94 + c1 - 161);	//12*12 Table (12*12)/8 = 18, every  char
	//draw a character
	for (i = 0; i < 12; i++)
	{
		BYTE cc1, cc2;
		
		if(i % 2)	//odd line
		{
			i4x = i4x + 2;
			cc1 = hzfont_table[index + i4x];
			cc2 = hzfont_table[index + i4x - 1] & 0x0f;
			my12Bits = (cc1<<4) | cc2;
		}
		else		//even line
		{
			i4x = i * 3 / 2;
			cc1 = hzfont_table[index + i4x];
			cc2 = hzfont_table[index + i4x + 1] & 0xf0;
			my12Bits = (cc1<<4) | (cc2>>4);
		}
		
		for (j = 0; j < 12; j++)
		{
			if ((1 << j) & my12Bits) 
			{
				if (vid == 2)  //Jeff 20020823
				{
					*Y_XYB( (x+14-j), (y+i) ) = iY;
					*C_XYB( (x+14-j), (y+i) ) = iCbCr;
				}
				else
				{
					*Y_XY( (x+14-j), (y+i) ) = iY;
					*C_XY( (x+14-j), (y+i) ) = iCbCr;
				}
			}
		}
	}
}

#endif   //USE_GB2312_FONT
#endif	//end MP3_LARGE_GUI

#if defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
#ifdef MP3_LARGE_GUI		//Maoyong 2004.1.13
#define ROW 2
#define COL  2
void FSGUI_Big5ShowChar(BYTE vid, int x, int y, BYTE c, BYTE c1, BYTE iY, UINT16 iCbCr)
{
    // 2004/09/10 yltseng
    int index, i,i4x = 0;
    UINT8 font1[24];
    BYTE cc1, cc2, cc3,cc4;

#ifdef SUPPORT_FONT_UTIL
    UINT8 aCode[2]      = { c, c1, };
    const UINT8* pBmp   = NULL;
    GetCharacterBmp( aCode, &pBmp );
#else
	BYTE CL, CH;
	int seq;

	/****************************************************
	1. get Font from 12*12 Hz Library and transfer back to 16*12, 
	even byte's low 4 bytes is all 0
	*****************************************************/
	CL = c1;
	CH = c;
	
	seq = 0;
	CL -= (CL < 127 ? 64 : 98);
    seq = ( CH - 161 ) * 157 + CL;
	index = seq * 18;
#endif

	for (i = 0; i < 12; i++)
	{		
		if(i % 2)
		{
			i4x = i4x + 2;
#ifdef SUPPORT_FONT_UTIL
            cc1 = pBmp[i4x];
            cc2 = pBmp[i4x-1]&0x0f;
#else
			cc1 = big5font_table[index + i4x];
			cc2 = big5font_table[index + i4x - 1] & 0x0f;
#endif
           	font1[i*2]=cc1;
            font1[i*2+1]=(cc2<<4);
		}
		else
		{
			i4x = i * 3 / 2;
#ifdef SUPPORT_FONT_UTIL
            cc1 = pBmp[i4x];
            cc2 = pBmp[i4x+1]&0xf0;
#else
			cc1 = big5font_table[index + i4x];
			cc2 = big5font_table[index + i4x + 1] & 0xf0;
#endif
            font1[i*2]=cc1;
            font1[i*2+1]=(cc2);
		}
	}
    /****************************************************
	2.Transfer 16*12 to 32 *24 Font	
	*****************************************************/
	BYTE j, k, m, n;
	BYTE width,height;
    	width=16;
    	height=12;
    	UINT16 my16bits=0;
    	UINT8 font2[24*ROW*COL];

	for (i=0;i<height;i++)
       	for(n=0;n<ROW;n++)
            		for(j=0;j<(width/8);j++){
                		for(k=0;k<8;k++)
                    			for(m=0;m<COL;m++)
                        			if((font1[i*2+j]>>(7-k))&0x01)
                             			my16bits |= (1<<(width-1-(k*COL+m)));
                	font2[(i*ROW+n)*4+j*COL]=(my16bits>>8);
                	font2[(i*ROW+n)*4+j*COL+1]=my16bits&0xff;
                	my16bits=0;
            		}

       /****************************************************
	3. Draw every valid pixel in this Chinese Font: 
	because the Last 8 bit of a line's 32 bit is always 0, just 24*24
	*****************************************************/
	UINT32 my24Bits = 0;       
       for(i = 0; i<24; i++)	//height
       {
       	i4x = i*4;
       	cc1 = font2[i4x];
       	cc2 = font2[i4x + 1];
       	cc3 = font2[i4x + 2];
       	cc4 = font2[i4x + 3];
       	my24Bits = (cc1<<16) + (cc2<<8) + cc3;	
       	for(j = 0; j<24; j++) //width
       	{
       		if ((1 << j) & my24Bits) 
			{
				*Y_XY( (x + 24 - j),  (y+i) ) = iY;
				*C_XY( (x + 24 - j),  (y+i) ) = iCbCr;				
			}
       	}
       }	
}
#else
void FSGUI_Big5ShowChar(BYTE vid, int x, int y, BYTE c, BYTE c1, BYTE iY, UINT16 iCbCr)
{
    // 2004/09/10 yltseng
	int index, i, j, i4x = 0;
	UINT32 my12Bits;

#ifdef SUPPORT_FONT_UTIL
    UINT8 aCode[2]      = { c, c1, };
    const UINT8* pBmp   = NULL;
    GetCharacterBmp( aCode, &pBmp );
#else
	int seq;
	BYTE CL, CH;
	
	CL = c1;
	CH = c;
	
	seq = 0;
	CL -= (CL < 127 ? 64 : 98);

    seq = ( CH - 161 ) * 157 + CL;
	index = seq * 18;
#endif

	//draw a character
	for (i = 0; i < 12; i++)
	{
		BYTE cc1, cc2;
		
		if(i % 2)
		{
			i4x = i4x + 2;
#ifdef SUPPORT_FONT_UTIL
            cc1 = pBmp[i4x];
            cc2 = pBmp[i4x-1]&0x0f;
#else
			cc1 = big5font_table[index + i4x];
			cc2 = big5font_table[index + i4x - 1] & 0x0f;
#endif
			my12Bits = (cc1<<4) | cc2;
		}
		else
		{
			i4x = i * 3 / 2;
#ifdef SUPPORT_FONT_UTIL
            cc1 = pBmp[i4x];
            cc2 = pBmp[i4x+1]&0xf0;
#else
			cc1 = big5font_table[index + i4x];
			cc2 = big5font_table[index + i4x+1] & 0xf0;
#endif
			my12Bits = (cc1<<4) | (cc2>>4);
		}
		
		for (j = 0; j <12; j++)
		{
			if ((1 << j) & my12Bits)
			{
				if (vid == 2)  //Jeff 20020823
				{
					*Y_XYB( (x+14-j), (y+i) ) = iY;
					*C_XYB( (x+14-j), (y+i) ) = iCbCr;
				}
				else
				{
					*Y_XY( (x+14-j), (y+i) ) = iY;
					*C_XY( (x+14-j), (y+i) ) = iCbCr;
				}
			}
		}
	}
} // yhwang 20021001
#endif   //end #ifdef MP3_LARGE_GUI //Maoyong 2004.1.13
#endif	//end #ifdef USE_BIG5_FONT

#if defined (MP3_LARGE_GUI) || defined (FS_BMP_GUI)//#ifdef MP3_LARGE_GUI
void FSGUI_ShowString(int x, int y, const char *s, BYTE iY, UINT16 iCbCr)
{
	int	i = 0;
	BYTE* p = (BYTE *)s;
	int length = 0;
	//sometime may exceed 25 chinese
	//zhaoyanhua modify. 2003-8-26 14:36
	#ifdef MP3_TXT_DISPLAY
	unsigned char ss[100];
	#else
	unsigned char ss[50];
	#endif
	unsigned char* ss_ptr = ss;

	strcpy(ss_ptr, p);
	
	while(p[i])
	{
		length++;
		i++;
	}
	i = 0;
	
	while (*p)
	{
		BYTE    c;
		BYTE    c1;
		int     iRes = 0;
        
		//  which character
		c = *p;
		c1 = *(p + 1);

#ifdef USE_GB2312_FONT
		if (((c >= 0xA1) && (c <= 0xF8)) && ((c1 >= 0xA1) && (c1 < 0xFF)))             
		 {
			// GB code
			iRes = 3;
		 }
		 else  
#endif
#if defined( USE_BIG5_FONT )        // 2004/12/23 yltseng
		if(((c >= 0xA1) && (c <= 0xF9)) && ((c1 >= 0x40 && c1 <= 0x7E) || (c1 >= 0xA1 && c1 <= 0xFE))) // yhwang for big5 20021001
		{
			// Big5 code
			iRes = 2;
		}
		else 
#endif
#ifdef USE_BIG5_COMMON_FONT         // 2004/12/23 yltseng
		if(((c >= 0xA1) && (c <= 0xC6)) && ((c1 >= 0x40 && c1 <= 0x7E) || (c1 >= 0xA1 && c1 <= 0xFE))) // yhwang for big5 20021001
		{
			// Big5 code
			iRes = 2;
		}
		else 
#endif
		if ((c >= 32) && (c <= 126)) // ASCII code
			iRes = 1;
		else
		{
			iRes = 0;
			c = '_';
		}
		
		if ((iRes == 0) || (iRes == 1))
		{
#ifdef SUPPORT_CHINESE_FONT // Clead
			if ((c == '!') || (c == '"') || (c == '#') || (c == '$') ||
				(c == '&') || (c == '\'') || (c == '(') || (c == ')') ||
				(c == ',') || (c == ';') || (c == '=') || (c == '^'))
#ifdef USE_GB2312_FONT
			{
				c1 = 0x03 + 0xa0;
				c = c + 0x80;
				FSGUI_GBShowChar(0, (x + i), y, c1, c, iY, iCbCr);
			}
			else
#elif defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )//#ifdef USE_GB2312_FONT
			{
				if(c < 114)
				{
					c1 = 0xa2;
					c = c + 0x8e;
				}
				else
				{
					c1 = 0xa3;
					c = c - 113 + 0x40;
				}
				FSGUI_Big5ShowChar(0, (x + i), y, c1, c, iY, iCbCr);
			}
			else
#endif////#ifdef USE_GB2312_FONT
				FSGUI_ShowChar(0, (x + i), y, c, iY, iCbCr);
#else//#ifdef SUPPORT_CHINESE_FONT // Clead
			FSGUI_ShowChar(0, (x + i), y, c, iY, iCbCr);
#endif//#ifdef SUPPORT_CHINESE_FONT // Clead
			i += 16;
			p++;
		}

#if defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
		else if(iRes == 2)  //BIG5 code
		{
			FSGUI_Big5ShowChar(0, (x + i), y, c, c1, iY, iCbCr);
			i += 26;
			p += 2;
		}
#endif
#ifdef USE_GB2312_FONT
		else if (iRes == 3) //GB code
		{
			FSGUI_GBShowChar(0, (x+i), y, c, c1, iY, iCbCr);
			i += 26;
			p += 2;
		} 
#endif
		else
		{
			c = '-';
			FSGUI_ShowChar(0, (x+i), y, c, iY, iCbCr); 
			i += 16;
			p++;
		}
		if (i > 540)
			break;  

	}
}
#else//#if defined (MP3_LARGE_GUI) || defined (FS_BMP_GUI)
void FSGUI_ShowString(int x, int y, const UINT8 *s, BYTE iY, UINT16 iCbCr)
{
	int	i = 0;
	BYTE* p = (BYTE *)s;
	int length = 0;
	//sometime may exceed 25 chinese
	//zhaoyanhua modify. 2003-8-26 14:36
	#ifdef MP3_TXT_DISPLAY
	unsigned char ss[100];
	#else
	unsigned char ss[50];
	#endif
	unsigned char* ss_ptr = ss;

	strcpy(ss_ptr, p);
	
	while(p[i])
	{
		length++;
		i++;
	}
	i = 0;
    
	while (*p)
	{
		BYTE    c;
		BYTE    c1;
		int     iRes = 0;
        
		//  which character
		c = *p;
		c1 = *(p + 1);

#ifdef USE_GB2312_FONT
		if (((c >= 0xA1) && (c <= 0xF8)) && ((c1 >= 0xA1) && (c1 < 0xFF)))             
		 {
			// GB code
			iRes = 3;
		 }
		 else  
#endif
#if defined( USE_BIG5_FONT )        // 2004/12/23 yltseng
		if(((c >= 0xA1) && (c <= 0xF9)) && ((c1 >= 0x40 && c1 <= 0x7E) || (c1 >= 0xA1 && c1 <= 0xFE))) // yhwang for big5 20021001
		{
			// Big5 code
			iRes = 2;
		}
		else 
#endif
#ifdef USE_BIG5_COMMON_FONT         // 2004/12/23 yltseng
		if(((c >= 0xA1) && (c <= 0xC6)) && ((c1 >= 0x40 && c1 <= 0x7E) || (c1 >= 0xA1 && c1 <= 0xFE))) // yhwang for big5 20021001
		{
			// Big5 code
			iRes = 2;
		}
		else 
#endif
		if ((c >= 32) && (c <= 126)) // ASCII code
			iRes = 1;
		else
		{
			iRes = 0;
			c = '_';
		}
		
		if ((iRes == 0) || (iRes == 1))
		{
#ifdef SUPPORT_CHINESE_FONT // Clead
			if ((c == '!') || (c == '"') || (c == '#') || (c == '$') ||
				(c == '&') || (c == '\'') || (c == '(') || (c == ')') ||
				(c == ',') || (c == ';') || (c == '=') || (c == '^'))
#ifdef USE_GB2312_FONT
			{
				c1 = 0x03 + 0xa0;
				c = c + 0x80;
				FSGUI_GBShowChar(0, (x + i), y, c1, c, iY, iCbCr);
			}
			else
#elif defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
			{
				if(c < 114)
				{
					c1 = 0xa2;
					c = c + 0x8e;
				}
				else
				{
					c1 = 0xa3;
					c = c - 113 + 0x40;
				}
				FSGUI_Big5ShowChar(0, (x + i), y, c1, c, iY, iCbCr);
			}
			else
#endif
				FSGUI_ShowChar(0, (x + i), y, c, iY, iCbCr);
#else
			FSGUI_ShowChar(0, (x + i), y, c, iY, iCbCr);
#endif
			#ifdef PULIANG_6PIC_GUI	//yaowh add 05-02-04
			if (JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode)
				i += 16;
			else
			#endif
				i += 9;
			p++;
		}

#if defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
		else if(iRes == 2)  //BIG5 code
		{
			FSGUI_Big5ShowChar(0, (x + i), y, c, c1, iY, iCbCr);
			#ifdef PULIANG_6PIC_GUI	//yaowh add 05-02-04
			if (JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode)
				i += 26;
			else
			#endif
				i += 14;
			p += 2;
		}
#endif
#ifdef USE_GB2312_FONT
		else if (iRes == 3) //GB code
		{
			FSGUI_GBShowChar(0, (x+i), y, c, c1, iY, iCbCr);

			//liweihua mod 2004-11-23
			//for display more Russian characters
			#ifdef ETON_DVD
			if(c == 0xA7)
			    i += 10;
			else 
			#endif
			#ifdef PULIANG_6PIC_GUI	//yaowh add 05-02-04
			if (JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode)
				i += 26;
			else
			#endif
				i += 14;
			p += 2;
		} 
#endif
		else
		{
			c = '-';
			FSGUI_ShowChar(0, (x+i), y, c, iY, iCbCr); 
			#ifdef PULIANG_6PIC_GUI	//yaowh add 05-02-04
			if (JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode)
				i += 16;
			else
			#endif
				i += 9;
			p++;
		}
		#ifdef PULIANG_6PIC_GUI	//yaowh add 05-02-04
		if (JPEG_THUMBNAIL_MODE == pFsJpeg->g_nJpegMode)
			if (i > 2540)
		else
		#endif
		if (i > 260)
			break;  // yhwang, for limiting the length of FSGUI_ShowString
	}
}
#endif //#if defined (MP3_LARGE_GUI) || defined (FS_BMP_GUI)

#ifdef FS_BMP_GUI
/*
    Function:In order to show little string in Sunplus New GUI
    Creator:Feeling
*/
void FSGUI_ShowLittleString(int x, int y, const char *s, BYTE iY, UINT16 iCbCr)
{
	int	i = 0;
	BYTE* p = (BYTE *)s;
	int length = 0;
	//sometime may exceed 25 chinese
	//zhaoyanhua modify. 2003-8-26 14:36
	#ifdef MP3_TXT_DISPLAY
	unsigned char ss[100];
	#else
	unsigned char ss[50];
	#endif
	unsigned char* ss_ptr = ss;

	strcpy(ss_ptr, p);
	
	while(p[i])
	{
		length++;
		i++;
	}
	i = 0;
	
	while (*p)
	{
		BYTE    c;
		BYTE    c1;
		int     iRes = 0;
        
		//  which character
		c = *p;
		c1 = *(p + 1);

#ifdef USE_GB2312_FONT
		if (((c >= 0xA1) && (c <= 0xF8)) && ((c1 >= 0xA1) && (c1 < 0xFF)))             
		 {
			// GB code
			iRes = 3;
		 }
		 else  
#endif
#if defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
		if(((c >= 0xA1) && (c <= 0xF9)) && ((c1 >= 0x40 && c1 <= 0x7E) || (c1 >= 0xA1 && c1 <= 0xFE))) // yhwang for big5 20021001
		{
			// Big5 code
			iRes = 2;
		}
		else 
#endif
		if ((c >= 32) && (c <= 126)) // ASCII code
			iRes = 1;
		else
		{
			iRes = 0;
			c = '_';
		}
		
		if ((iRes == 0) || (iRes == 1))
		{
#ifdef SUPPORT_CHINESE_FONT // Clead
			if ((c == '!') || (c == '"') || (c == '#') || (c == '$') ||
				(c == '&') || (c == '\'') || (c == '(') || (c == ')') ||
				(c == ',') || (c == ';') || (c == '=') || (c == '^'))
#ifdef USE_GB2312_FONT
			{
				c1 = 0x03 + 0xa0;
				c = c + 0x80;
				FSGUI_GBShowChar(0, (x + i), y, c1, c, iY, iCbCr);
			}
			else
#elif defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
			{
				if(c < 114)
				{
					c1 = 0xa2;
					c = c + 0x8e;
				}
				else
				{
					c1 = 0xa3;
					c = c - 113 + 0x40;
				}
				FSGUI_Big5ShowChar(0, (x + i), y, c1, c, iY, iCbCr);
			}
			else
#endif
				FSGUI_ShowLittleChar(0, (x + i), y, c, iY, iCbCr);
#else
			FSGUI_ShowLittleChar(0, (x + i), y, c, iY, iCbCr);
#endif
			i += 9;
			p++;
		}

#if defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
		else if(iRes == 2)  //BIG5 code
		{
			FSGUI_Big5ShowChar(0, (x + i), y, c, c1, iY, iCbCr);
			i += 14;
			p += 2;
		}
#endif
#ifdef USE_GB2312_FONT
		else if (iRes == 3) //GB code
		{
			FSGUI_GBShowChar(0, (x+i), y, c, c1, iY, iCbCr);
			i += 14;
			p += 2;
		} 
#endif
		else
		{
			c = '-';
			FSGUI_ShowLittleChar(0, (x+i), y, c, iY, iCbCr); 
		
			i += 9;
			p++;
		}
		if (i > 300)
			break;  // for limiting the length of FSGUI_ShowString
	}
}
#endif

//void FSGUI_ShowImage(BYTE* MapArray, int xStart, int yStart, int width, int height)
//{
//        int i, j,x,y;
//        UINT8 z;
//
//        for (i=0; i<height; i++) {
//                for (j=0; j<width; j++) {
//                        x=xStart+j;
//                        y=yStart+i;
//                        z=*(MapArray+i*width+j);
//                        *Y_XY(x,y) = RGB8_Y[z];
//                        *C_XY(x,y) = RGB8_CrCb[z];
//                }
//        }
//}
#endif//20020801



