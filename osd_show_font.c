/*************************************************************
** FILE
** osd_show_font.c
**
** DESCRIPTION
** This file contains main functions for show font on OSD.
**
** NOTE:Now use OSDShowFont.c to replace this file... 20050124
**
** Create:   liweihua 2004-03-19
** Update:   suqiaoli 2004-03-26
** Update:   suqiaoli 2004-04-02  
**           add new function:srt title can display many Europe languages  
** Update:   suqiaoli 2004-4-28 
**           add new function:display lower letter in OSD_FONT_API;
**                            not to cut off a long word,it can move next line;  
**                            only display Russian language not Chinese,in order to reduce code.
** Update:   suqiaoli add new function:Support Japanese font
**************************************************************/
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "memmap.h"
#include "func.h"
#include "stdlib.h"
#include "user_init.h"


#if defined( OSD_FONT_API ) && !defined( SUPPORT_FONT_UTIL )    // 2004/09/10 yltseng

#include "font_lowercase.c" //display lower letter ,suqiaoli add 2004-4-28
extern void osd_draw_gbfont(BYTE vid, BYTE pFont[], int xStart, int yStart, unsigned int  fwidth, unsigned int  fhight, BYTE fontcolor,BYTE number);
extern const unsigned char LOWERCASE_FONT_BITMAP[];
#define	 lowercase_table	LOWERCASE_FONT_BITMAP

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

#if defined USE_RUSSIAN_LANGUAGE
extern const unsigned char GUO_GB2312_Russian_12X12_FONT_BITMAP[];
#define	 Russian_font_table	GUO_GB2312_Russian_12X12_FONT_BITMAP
#endif

#if defined EUROPE_FOREIGN_LANGUAGES //suqiaoli add 2004-4-2
extern const unsigned char ISO_8859_1_12X24_FONT_BITMAP[];
#define	 isofont_table	ISO_8859_1_12X24_FONT_BITMAP
#endif

#if defined MIDDLE_EUROPE_LANGUAGES //suqiaoli add 2004-7-13
extern const unsigned char ISO_8859_2_12X24_FONT_BITMAP[];
#define	 isofont_table	ISO_8859_2_12X24_FONT_BITMAP
#endif

#if defined SUPPORT_TURKISH_LANGUAGES //suqiaoli add 2004-9-1
extern const unsigned char ISO_8859_9_12X24_FONT_BITMAP[];
#define	 isofont_table	ISO_8859_9_12X24_FONT_BITMAP
#endif

#if defined USE_JAPANESE_FONT
extern const unsigned char  JP_JISX0213_12X12_FONT_BITMAP[];
#define Japanfont_table JP_JISX0213_12X12_FONT_BITMAP
#endif

#if defined USE_KOREAN_FONT
extern const unsigned char  KO_KSC_12X12_FONT_BITMAP[];
#define Koreanfont_table KO_KSC_12X12_FONT_BITMAP
#endif

#if defined(EUROPE_FOREIGN_LANGUAGES) || defined(MIDDLE_EUROPE_LANGUAGES) || defined (SUPPORT_TURKISH_LANGUAGES)
    #define  FONT_LEN 6
#else
    #define  FONT_LEN 9
#endif

extern void EnlargeFontSizeToDouble( UINT8 *pDest, const UINT8 *pSrc, BYTE uiWidth, BYTE uiHeight );

#if defined(USE_GB2312_FONT)||defined(USE_RUSSIAN_LANGUAGE)
void OSD_GBShowChar(int x, int y, BYTE c, BYTE c1, BYTE fontcolor,BYTE r)
{
	int index, i,i4x = 0;
    UINT8 font1[24];
    UINT8 font2[24*2*2];
	BYTE width,height;

    width=16;
    height=12;

	index = 18 * ((c - 161) * 94 + c1 - 161);
	//draw a character
	for (i = 0; i < 12; i++)
	{
		BYTE cc1, cc2;
		
		if(i % 2)
		{
			i4x = i4x + 2;
			
#if defined(USE_GB2312_FONT)
			cc1 = hzfont_table[index + i4x];
			cc2 = hzfont_table[index + i4x - 1] & 0x0f;
#elif  defined(USE_RUSSIAN_LANGUAGE)
            cc1 = Russian_font_table[index + i4x];
			cc2 = Russian_font_table[index + i4x - 1] & 0x0f;
#endif
            font1[i*2]=cc1;
            font1[i*2+1]=(cc2<<4);
		}
		else
		{
			i4x = i * 3 / 2;
			
#if defined(USE_GB2312_FONT)
			cc1 = hzfont_table[index + i4x];
			cc2 = hzfont_table[index + i4x + 1] & 0xf0;
#elif  defined(USE_RUSSIAN_LANGUAGE)
			cc1 = Russian_font_table[index + i4x];
			cc2 = Russian_font_table[index + i4x + 1] & 0xf0;
#endif
            font1[i*2]=cc1;
            font1[i*2+1]=(cc2);
		}
	}
    // 2004/07/21 yltseng
    //mutiply the 12*12 size font to 24*24 size font
    EnlargeFontSizeToDouble( (UINT8 *)font2, (UINT8 *)font1, width, height );
    osd_draw_gbfont( 0, (UINT8 *)font2, x, y, width*2, height*2, fontcolor, r );
}
#endif

#if defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
void OSD_Big5ShowChar(int x, int y, BYTE c, BYTE c1, BYTE fontcolor,BYTE r)
{
    // 2004/09/10 yltseng
	int index, i, i4x = 0;
    UINT8 font1[24];
	int seq;
	BYTE CL, CH;
    UINT8 font2[24*2*2];
	BYTE width,height;

    width=16;
    height=12;
	
	CL = c1;
	CH = c;
	
	seq = 0;
	CL -= (CL < 127 ? 64 : 98);
	
    seq = ( CH - 161 ) * 157 + CL;
	index = seq * 18;
   
	//draw a character
	for (i = 0; i < 12; i++)
	{
		BYTE cc1, cc2;
		
		if(i % 2)
		{
			i4x = i4x + 2;
			cc1 = big5font_table[index + i4x];
			cc2 = big5font_table[index + i4x - 1] & 0x0f;
            font1[i*2]=cc1;
            font1[i*2+1]=(cc2<<4);
		}
		else
		{
			i4x = i * 3 / 2;
			cc1 = big5font_table[index + i4x];
			cc2 = big5font_table[index + i4x+1] & 0xf0;
            font1[i*2]=cc1;
            font1[i*2+1]=(cc2);
		}
    }
    // 2004/07/21 yltseng
    //mutiply the 12*12 size font to 24*24 size font
    EnlargeFontSizeToDouble( (UINT8 *)font2, (UINT8 *)font1, width, height );
    osd_draw_gbfont( 0, (UINT8 *)font2, x, y, width*2, height*2, fontcolor, r );
}
#endif

#ifdef USE_JAPANESE_FONT
void OSD_JISShowChar(int x, int y, BYTE c, BYTE c1, BYTE fontcolor,BYTE r)
{
    // 2004/07/21 yltseng
	int     i       = 0;
    int     i4x     = 0;
    BYTE    width   = 16;
    BYTE    height  = 12;
    UINT8   font1[ 24 ];
	UINT8   font2[ 24 * 2 * 2 ];
   
    if(c >= 0xE0) c = c - 0x40;
    
    if(c1 >= 0x80) c1 = c1-1;
    
    i4x = 18 * ((c-0x81 )* 188 + c1-0x40);

    for( i = 0; i < 12; i++ )
    {
		if( i % 2 )
		{
            font1[ i * 2 ]      = Japanfont_table[ i4x ];
            font1[ i * 2 + 1 ]  = ( ( Japanfont_table[ i4x - 1 ] & 0x0f ) << 4 );
            i4x += 1;
		}
		else
		{
            font1[ i * 2 ]      = Japanfont_table[ i4x ];
            font1[ i * 2 + 1 ]  = Japanfont_table[ i4x + 1 ] & 0xf0;
            i4x += 2;
		}   
    }

    //mutiply the 12*12 size font to 24*24 size font
    EnlargeFontSizeToDouble( (UINT8 *)font2, (UINT8 *)font1, width, height );
    osd_draw_gbfont( 0,(UINT8 *)font2, x, y, width * 2, height * 2, fontcolor, r );
}
    
#endif

#ifdef USE_KOREAN_FONT
void OSD_KSCShowChar(int x, int y, BYTE c, BYTE c1, BYTE fontcolor,BYTE r)
{
    // 2004/07/21 yltseng
	int     i       = 0;
    int     i4x     = 0;
    BYTE    width   = 16;
    BYTE    height  = 12;
    UINT8   font1[ 24 ];
	UINT8   font2[ 24 * 2 * 2 ];
   
    if ((c1 >= 0x41) && (c1 <= 0x5A)) 
        i4x = 18 * ((c-0x81 )* 178 + (c1-0x41));
    else if ((c1 >= 0x61) && (c1 <= 0x7A))
        i4x = 18 * ((c-0x81 )* 178 + (c1-0x61+26));
    else if ((c1 >= 0x81) && (c1 <= 0xFE))
        i4x = 18 * ((c-0x81 )* 178 + (c1-0x81+52));

    for( i = 0; i < 12; i++ )
    {
		if( i % 2 )
		{
            font1[ i * 2 ]      = Koreanfont_table[ i4x ];
            font1[ i * 2 + 1 ]  = ( ( Koreanfont_table[ i4x - 1 ] & 0x0f ) << 4 );
            i4x += 1;
		}
		else
		{
            font1[ i * 2 ]      = Koreanfont_table[ i4x ];
            font1[ i * 2 + 1 ]  = Koreanfont_table[ i4x + 1 ] & 0xf0;
            i4x += 2;
		}   
    }
    //mutiply the 12*12 size font to 24*24 size font
    EnlargeFontSizeToDouble( (UINT8 *)font2, (UINT8 *)font1, width, height );
    osd_draw_gbfont( 0, (UINT8 *)font2, x, y, width * 2, height * 2, fontcolor, r );
}
#endif

#if defined(EUROPE_FOREIGN_LANGUAGES) || defined(MIDDLE_EUROPE_LANGUAGES) || defined (SUPPORT_TURKISH_LANGUAGES)
void OSD_ISOShowChar(int x, int y, BYTE c, BYTE fontcolor,BYTE r)
{
    BYTE 	width   = 16;
    BYTE    height  = 24;
    int     i4x     = 0;
    int     i       = 0;
    UINT8   font1[48];
    
    if ( ( c >= 32 ) && ( c <= 126 ) ) 
    	i4x = 36 * ( c - 32 );
    else if( ( c >= 160 ) && ( c <= 255 ) )
    	i4x = 36 * ( c - 65 );

	for( ; i < 24; i++ )
	{
		if( i % 2 )
		{
            font1[ i * 2 ]      = isofont_table[ i4x ];
            font1[ i * 2 + 1 ]  = ( ( isofont_table[ i4x - 1 ] & 0x0f ) << 4 );
            i4x += 1;
		}
		else
		{
            font1[ i * 2 ]      = isofont_table[ i4x ];
            font1[ i * 2 + 1 ]  = isofont_table[ i4x + 1 ] & 0xf0;
            i4x += 2;
		}   
    }

    osd_draw_gbfont( 0, (UINT8 *)font1, x, y, width, height, fontcolor, r );
}
#endif

void OSD_ShowChar(int x, int y, BYTE c, BYTE fontcolor,BYTE r) 
{
	BYTE    *pFont;
    BYTE width,height;
	
    UINT8 font1[48];
    int  	index;
    int i;
    
    if ((c >= 'a') && (c <= 'z'))//litter case 
    { 
        width = 16;
        height = 24;
        index = 48 * (c - 97);
        
        //draw a character
    	for (i = 0; i < 24; i++)
    	{
    		UINT8 cc1,cc2;
    		
    		cc1=lowercase_table[index+i*2];
    		cc2=lowercase_table[index+i*2+1];
    		
    		font1[i*2]=cc1;
    		font1[i*2+1]=cc2;
    
    	}
    	osd_draw_gbfont( 0, (UINT8 *)font1, x, y, width, height, fontcolor, r );	
    }
    
    else
    {
    	pFont = get_font_entry(0,c);
        width = pFont[0];
        height = pFont[1];
        osd_draw_gbfont( 1, (UINT8 *)pFont, x, y, width, height, fontcolor, r );	
    }
}

void OSD_ShowString(int x, int y, const char *s, BYTE fontcolor, BYTE r)
{
	int	i = 0;
	BYTE* p = (BYTE *)s;
	//sometime may exceed 25 chinese
	unsigned char ss[50];

	unsigned char* ss_ptr = ss;

	strcpy(ss_ptr, p);
	
	while (*p)
	{
		BYTE    c;
		BYTE    c1;
		int     iRes = 0;
        
		//  which character
		c = *p;
		c1 = *(p + 1);

#if defined(USE_KOREAN_FONT)
        if(((c >= 0x81) && (c <= 0xFE)) && ((c1 >= 0x41 && c1 <= 0x5A) || (c1 >= 0x61 && c1 <= 0x7A)|| (c1 >= 0x81 && c1 <= 0xFE))) 
        {
            //KSC code
			iRes = 5;
        }
        else  
#endif
            
#if defined(USE_JAPANESE_FONT)
        if (((c >= 0x81 && c <= 0x9F)||(c >= 0xE0 && c <= 0xFC)) && ((c1 >= 0x40) && (c1 <= 0xFC)))  //JIS code           
        {
            iRes = 4;
        }
        else  
#endif		

#if defined(USE_GB2312_FONT)||defined(USE_RUSSIAN_LANGUAGE)
		if (((c >= 0xA1) && (c <= 0xF8)) && ((c1 >= 0xA1) && (c1 < 0xFF))) // GB code            
		 {			
			iRes = 3;
		 }
		 else  
#endif

#if defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
		if(((c >= 0xA1) && (c <= 0xF9)) && ((c1 >= 0x40 && c1 <= 0x7E) || (c1 >= 0xA1 && c1 <= 0xFE))) // Big5 code
		{			
			iRes = 2;
		}
		else 
#endif

#if defined(EUROPE_FOREIGN_LANGUAGES) || defined(MIDDLE_EUROPE_LANGUAGES) || defined (SUPPORT_TURKISH_LANGUAGES)
		if ((c >= 32) && (c <= 255)) // ISO 8859-1 code
		{	
			iRes = 1;
		}
#else
		if ((c >= 32) && (c <= 126)) // ASC code( before 127)
		{
			iRes = 1;
		}
#endif
		else //other
		{
			iRes = 0;
			c = '_';
		}

		if ((iRes == 0) || (iRes == 1))
		{
            p++;	    
   
#if !defined(EUROPE_FOREIGN_LANGUAGES) && !defined(MIDDLE_EUROPE_LANGUAGES) && !defined (SUPPORT_TURKISH_LANGUAGES)
            i += 9;
    #if defined(SUPPORT_CHINESE_FONT)||defined(USE_RUSSIAN_LANGUAGE)||defined(USE_JAPANESE_FONT)||defined(USE_KOREAN_FONT)// Clead
			if ((c == '!') || (c == '"') || (c == '#') || (c == '$') ||
				(c == '&') || (c == '\'') || (c == '(') || (c == ')') ||
				(c == ',') || (c == ';') || (c == '=') || (c == '^'))
        #if defined(USE_GB2312_FONT)||defined(USE_RUSSIAN_LANGUAGE)
			{
				c1 = 0x03 + 0xa0;
				c = c + 0x80;
				OSD_GBShowChar((x+i), y, c1, c, fontcolor, r);
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
				OSD_Big5ShowChar((x+i), y, c1, c, fontcolor, r);
			}
			else
	    #elif defined(USE_JAPANESE_FONT)
            {
                if (c == '!') c =0x49; 
                else if (c == '#') c =0x94;
                else if (c == '$') c =0x90;
                else if (c == '(') c =0x69;
                else if (c == ')') c =0x6A;
                else if (c == ',') c =0x43;
                else if (c == ';') c =0x47;
                else if (c == '=') c =0x81;
                else if (c == '^') c =0xC8;
                else if (c == '&') c =0x95;
                
                c1 = 0x81;
                
                OSD_JISShowChar((x+i), y, c1,c, fontcolor, r);
            }
            else
        #elif defined(USE_KOREAN_FONT)
            {
                if (c == '!') c =0x49; 
                else if (c == '#') c =0x94;
                else if (c == '$') c =0x90;
                else if (c == '(') c =0x69;
                else if (c == ')') c =0x6A;
                else if (c == ',') c =0x43;
                else if (c == ';') c =0x47;
                else if (c == '=') c =0x81;
                else if (c == '^') c =0xC8;
                else if (c == '&') c =0x95;
                
                c1 = 0x81;
                
                OSD_KSCShowChar((x+i), y, c1,c, fontcolor, r);
            }
            else
        #endif
    
    #endif
				OSD_ShowChar((x+i), y, c, fontcolor, r);
    
#else//#ifndef EUROPE_FOREIGN_LANGUAGES
        i += 6;
    		OSD_ISOShowChar((x+i), y, c, fontcolor, r);
    
#endif//#ifndef EUROPE_FOREIGN_LANGUAGES
    
		}

#if defined( USE_BIG5_FONT ) || defined( USE_BIG5_COMMON_FONT )
		else if(iRes == 2)  //BIG5 code
		{
			OSD_Big5ShowChar( (x+i), y, c, c1, fontcolor, r);
			i += 14;
			p += 2;
		}
#endif

#if  defined(USE_GB2312_FONT)||defined(USE_RUSSIAN_LANGUAGE)
		else if (iRes == 3) //GB code
		{
			OSD_GBShowChar((x+i), y, c, c1, fontcolor, r);
			i += 14;
			p += 2;
		} 
#endif

#ifdef USE_JAPANESE_FONT
		else if(iRes == 4)  //JIS code
		{
			OSD_JISShowChar( (x+i), y, c, c1, fontcolor, r);
			i += 14;
			p += 2;
		}
#endif

#ifdef USE_KOREAN_FONT
		else if(iRes == 5)  //KSC code
		{
			OSD_KSCShowChar( (x+i), y, c, c1, fontcolor, r);
			i += 14;
			p += 2;
		}
#endif
        // for limiting the length of OSD_ShowString
        // the following number 14 is for limiting display half of chinese font
		if (i > (region[r].osd_w-x-14)) 
			break; 
	}
}

#ifdef SUPPORT_OSDSRT
/*
 *Function:display text to osd,display max line:7,display max chinese font in a line:19
 *Parameter:*p:input string
 *           Size:length of string
 *Return:none      
 *Creator:suqiaoli
 *Date:2004-3-17
 *Date:2004/09/10 yltseng modify
*/
void ShowOSDText(const char *p,  UINT16 size)
{
    // 2004/09/03 yltseng
    #define MAX_WORD    50
#ifdef SDRAM_16Mb_Mode
    #define MAX_LINE    2
#else
	#define MAX_LINE	7
#endif
	
	BYTE*pStr = (BYTE *)p;
	BYTE c,c1;
	
	BYTE *old_pStr;
	int old_i_len;
	
	int  show_line = -1;
	int  show_word = 0;
	UINT16  nsize=0;
	int  i_len;
	int xstart,ystart;
	int len[MAX_LINE];
	int i;
	int count;//ASCII count in a line

	int    width;
	int    height;

	width=(int) region[3].osd_w;
	height=(int) region[3].osd_h/MAX_LINE;  // 2004/09/03 yltseng
	
	//All char will be put into this str array
	//if string long,it will newline
	BYTE str[MAX_LINE][MAX_WORD];

	osd_tog_region(3,OSD_ON);
	
	//Read and parse each char,display them on osd
	//include function:display more lines,newline,
	//when string length>276,it will newline
	while(nsize<size)
	{
		show_word = 0;
		i_len = 0;
		count = 0;
		show_line++;
        if( show_line > MAX_LINE - 1 )//most displayed line is 7 line
        {
            show_line = MAX_LINE - 1;
            break;
        }

		//read string to string buffer,except "return","next line"
		while(((*pStr) != '\r')&& ((*pStr)!='\n') ) 
		{	
			c = *pStr;
			c1 = *(pStr + 1);

//Double ASCII code			
#if defined(USE_GB2312_FONT) || defined(USE_RUSSIAN_LANGUAGE)||defined(USE_BIG5_FONT)||defined(USE_BIG5_COMMON_FONT)||defined(USE_JAPANESE_FONT)||defined(USE_KOREAN_FONT)
			
    #if defined(USE_GB2312_FONT) || defined(USE_RUSSIAN_LANGUAGE)			
			if (((c >= 0xA1) && (c <= 0xF8)) && ((c1 >= 0xA1) && (c1 < 0xFF))) 	//gb2312		

    #elif defined(USE_BIG5_FONT) || defined( USE_BIG5_COMMON_FONT )
			if(((c >= 0xA1) && (c <= 0xF9)) && ((c1 >= 0x40 && c1 <= 0x7E) || (c1 >= 0xA1 && c1 <= 0xFE))) // big5 

    #elif defined(USE_JAPANESE_FONT)
            if (((c >= 0x81 && c <= 0x9F)||(c >= 0xE0 && c <= 0xFC)) && ((c1 >= 0x40) && (c1 <= 0xFC)))             

    #elif defined(USE_KOREAN_FONT)
            if(((c >= 0x81) && (c <= 0xFE)) && ((c1 >= 0x41 && c1 <= 0x5A) || (c1 >= 0x61 && c1 <= 0x7A)|| (c1 >= 0x81 && c1 <= 0xFE)))                 

    #endif			
			{
				str[show_line][show_word]=c;
				str[show_line][show_word+1]=c1;
				show_word+= 2;
				i_len+= 14;
				nsize+= 2;
				pStr += 2;
				if((((i_len-count*9)%2==0)&&(i_len>275))||(((i_len-count*9)%2==0)&&(i_len>276)))
					break;
			}
			else
#endif

//Single ASCII code
#if defined(EUROPE_FOREIGN_LANGUAGES) || defined(MIDDLE_EUROPE_LANGUAGES) || defined (SUPPORT_TURKISH_LANGUAGES)
			if (((c >= 32) && (c <= 126)) ||((c >= 160) && (c <= 255)))// ISO 8859-1 code
#else
            if ((c >= 32) && (c <= 126))
#endif
			{
				old_pStr = pStr;
			    old_i_len = i_len;
				str[show_line][show_word]=c;
				show_word += 1;
				i_len += FONT_LEN;//len
				nsize += 1;
				pStr += 1;
				
				if(c == 32) //not to cut off a long word,according to space's position
				{
    			    do
    			    {
    			        old_pStr ++;
    			        old_i_len += FONT_LEN;//len
    			        if((*old_pStr == 32)|| (*old_pStr == '\r')||(old_i_len > 276))
    			            break;
    		    
    			    }while(1);
			    
    			    if (old_i_len > 276)
    			        break;
				}
				else
				{
				    count++;
				    if (i_len>276)
					    break;	
			    }
			}				

//other code
			else
			{
				c = '_';
				str[show_line][show_word]=c;
				show_word+= 1;
				nsize+= 1;
				i_len+= 9;
				pStr += 1;
				count++;
				if (i_len>276)
					break;
			}
				
		}//while(((*pStr) != '\r')&& ((*pStr)!='\n') )
		
		if(((*pStr) == '\r')||((*pStr) == '\n'))//count nsize,'\r':when "return",'\n':next line is blank
		{
			pStr++;
			nsize++;
		}

		len[show_line]=i_len;
		
		str[show_line][show_word]='\0';
		
		if( show_word <= 0 )//if blank line,string line will skip
			show_line--;		
	}//while(nsize<size)

    for(i=show_line;i>=0;i--)//display each line srt title
    {
        xstart=(width-len[i])/2;
        ystart=height*(MAX_LINE-(show_line-i)-1);
        OSD_ShowString(xstart,ystart,str[i],2,3);
    }
}

#endif //#ifdef SUPPORT_OSDSRT

#endif//#ifdef OSD_FONT_API
