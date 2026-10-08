//--------------------------------------
//created by ouyang 2004.08.16
//For MIDI UI
//--------------------------------------

/*
** FILE
** osd_midi.c
**
** DESCRIPTION
** control MIDI UI  interface.
*/

#include "user_init.h"

//*************************************************
//************For Midi OSD Lyric***********************
//*************************************************
#ifdef SUPPORT_OSDLYRIC

#include "global.h"
#include "func.h"
#include "osd.h"
#include "osd_palette.h"
#include "fsmidi.h"

#ifdef SUPPORT_MIDI_MENU_SEL  //by dtb in 20040225
#include "fsMidiUI.h"
#include "fsmidiui_menu.h"
#include "fsmidiui_menuctrl.h"
#include "fsmidiui_progctrl.h"
#include "fsmidiui_prog.h"
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

#ifdef MIDI_MULTIFONT_LIB    
  typedef struct{
      int xStart;
      int yStart;
      BYTE * pfntpt;
      UINT16 size;
      BYTE fontcolor;
      BYTE NewFormatFlag;
      BYTE bgcolor; 
      BYTE FigureColor;
      BYTE FontType; 
      BYTE number;
      BYTE Lock;
  }DrawFnt_S;
  static DrawFnt_S gs_stDrawFont ={0,0,0,0,0,0,0,0,0,0,0};
  
  typedef struct{
          int xx;
          int yy;
          int margin;
          int endXEdge;
          BYTE* Lyric; 
          BYTE regNum;
          BYTE uFontBase; 
          BYTE FontType;
      }DispText_S;
  static DispText_S gs_stTestDisp;
  

  void MidiDrawFntPt(DrawFnt_S *pfntSt);
  //  void MidiDrawFntPt(int xStart,int yStart,BYTE fontcolor,BYTE * pfntpt,UINT16 size,
   //     BYTE NewFormatFlag,BYTE bgcolor, BYTE FigureColor, BYTE FontType, BYTE number);
#endif
extern const BYTE arc_tableLT[10][10];
extern const BYTE arc_tableRT[10][10];
extern const BYTE arc_tableLB[10][10];
extern const BYTE arc_tableRB[10][10];

#if 0
//move to fsmidiui_prog
#ifdef SUPPORT_PINYINGDELAY     //xlluo add 04-11-15
inline int SetPinyingDelay(void)
{
    return MIDI_PINYINGINPUT_DELAY;  //about 1.5 s
}
#endif

#ifdef SUPPORT_SANJING_SCORE        //xlluo for sanjin score 04-10-23
//#include "MidiScoreNum.c"
int ScoreDelay(void)
{
    //TODO: add your code here 
    //this func will be calling when score start
    return (10000);        //default is 2.5 second,unit millisec
}

char * SetScoreGalaStr(int score)
{
    //TODO: add your code to replase inhere 
    //this func would call when show score num
    //[out]: the return value would be use disp str
    //below scorenum and flush right 
    //max strlen is 12 chinese characters
    //return NULL to show nothing 
    //[in]score :the num of score would be display on screen,max is 100
   if(score<60)
    {char * str[] ={"Çë¼ÌÐøÅ¬Á¦",};
    printf("cur score %d\n",score);
    return str[0];
    }
    else if(score<80)
     {char * str[] ={"Äã¾ßÓÐÒ»¶¨µÄ³ª¸èËØÖÊ",};
    printf("cur score %d\n",score);
    return str[0];
     }
     else if(score<90)
      {char * str[] ={"¸èÐÇµ®Éú",};
    printf("cur score %d\n",score);
    return str[0];
}
    else 
     {char * str[] ={"ÄãÊÇ¸è³ª¾ÞÐÇ",};
    printf("cur score %d\n",score);
    return str[0];
}
}

//special score mode relase to sanjin                           //xlluo add for custormer request
                                                                                      //2004-11-06

//use macro GETSCOREMODE() to get the score mode
//you can all your code which get new score and refresh 
//display item in func. "char * SetScoreGalaStr(int score)"

//I would call the func DrawLTSUI or DrawDKSUI decording to you control.
//when you select the selection "open DKS" or "open LTS"
//I will do that
//          first: enable the score mode
//     second: call the func. below by your selection
//         thrid: set the score mode
//      at last: refresh the menu
void DrawLTSUI()
{
    //disp the title of LTSUI
    //TODO: you should rewrite or modify the ui drawfunc.
    int dispX[] ={
                        10,105,         //left column
                        200,400,       //mid column
                        400,470,       //right column
    };
    draw_midi_bitmap_HZnew(Score_Str_LTS[0], dispX[2]+10, 10, 6, 0, 2, 2, 0);
    draw_midi_bitmap_HZnew(Score_Str_LTS[1], dispX[2]+50+10, 10, 6, 0, 2, 2, 0);
    draw_midi_bitmap_HZnew(Score_Str_LTS[2], dispX[2]+100+10, 10, 6, 0, 2, 2, 0);
    //TODO: add initial draw code here
}

void DrawDKSUI()
{
    //disp the title of DKSUI
    //TODO: you should rewrite or modify the ui drawfunc.
    int dispX[] ={
                        20,85,          //left column
                        200,400,      //mid column
                        400,470,      //right column
                        };
    draw_midi_bitmap_HZnew(Score_Str_DKS[0], dispX[2]-15+24, 0, 6, 0, 2, 2, 0);
    draw_midi_bitmap_HZnew(Score_Str_DKS[1], dispX[2]-15+50+24, 0, 6, 0, 2, 2, 0);
    draw_midi_bitmap_HZnew(Score_Str_DKS[2], dispX[2]-15+100+24, 0, 6, 0, 2, 2, 0);
    //TODO: add initial draw code here
}
#endif
//++++++++++++++++++++++++++++++++++++++++++++++++++
//IF THERE IS ANY QUESTION.PLEASE CALL ME OR SEND A MAIL FOR ME 
//                                       SUNMEDIA  XLLUO
//                                       86-028-87848688-5816
//                                       MAIL: xlluo@sunplus.com.cn
//++++++++++++++++++++++++++++++++++++++++++++++++++
#endif

//BYTE LyricFontcolor, LyricBgcolor, LyricRevcolour, LyricFigureColor;
#ifdef SUPPORT_REPREGIONCOL     //ouyang 2004.07.31
void osd_updataRegion_Color(BYTE R,BYTE G,BYTE B,BYTE A,BYTE code,BYTE regNum)
{
    int i =0;
    BYTE *osdhead[2];
    BYTE *obase;
    UINT32 repCol = __palette4F(G, B, R, A);
//    osd_tog_region(regNum,OSD_OFF);
    if(osd_active_regions<=regNum) return;//error

    osdhead[0] =(UINT16*)(get_osdbuf_baseptr() + region[regNum].osd_header[0] * 32);//get osd head pos //ouyang 2004.07.31
    if (((((*(osdhead[0]))>>BIT_MD)&0x07) ==OSD_FORMAT_16COLOR)//get color format
        &&((((*(osdhead[0]+2))>>BIT_CLUT_TYPE)&0x03) ==OSDV2_CLUT_32b))//for 32 bit clut
    {
        for (i =0;i<2;i++)
        {
            osdhead[i] =(UINT16*)(get_osdbuf_baseptr() + region[regNum].osd_header[i] * 32);//get osd head pos
            obase =osdhead[i]+HEADER_SIZE;
            while (code)                    //code is base 0, colour clut index
            {   
                code --;
                obase += OSD_CLUT_SIZE;                
            }    
            wbe32(obase,repCol);                
        }//__palette4F(130,130,130,130)
    }
}
#endif

void osd_midi_init(void)
{
   //   int i;
    __osd_init();

#define MIDI_HEADER 4
    //setup region 3
    header_id = MIDI_HEADER;
    region[3].osd_w = MIDI_LYRIC_REGION >> 1;
    region[3].osd_h = MIDI_LYRIC_HEIGHT;
    osd_create_region1( 3, 20, 150 + 30, NULL, OSD_FORMAT_16COLOR,
        OSD_INTERLACED);   
    
    //setup region 2
    header_id = MIDI_HEADER;
    region[2].osd_w = MIDI_MENU_REGION >> 1;              
    region[2].osd_h = MIDI_MENU_HEIGHT;  
    osd_create_region1( 2, 20/* 50*/, 60, &region[3],
        OSD_FORMAT_16COLOR, OSD_INTERLACED);  

    //setup region 1 
    header_id = NORMAL_HEADER;
    region[1].osd_w = 36 * 4;
    region[1].osd_h = OSD_FONT_HEIGHT;
    osd_create_region1( 1, 32, 45, &region[2], OSD_FORMAT_4COLOR,
        OSD_INTERLACED);

    //setup region 0
    header_id = MIDI_HEADER;
    region[0].osd_w = 320;
    region[0].osd_h = 60;
    osd_create_region1( 0, 26, 15, &region[1], OSD_FORMAT_16COLOR,
        OSD_INTERLACED);

    osd_active_regions = 4;

#ifdef SUPPORT_SCANMODE_SWITCH
    SwitchRegionTVformat();//xlluo add 04-6-14 
#endif
#ifdef SUPPORT_REPREGIONCOL
 //   osd_updataRegion_Color(130,130,130,130,0,REGION0);
#endif
    osd_init__();
}


#ifdef HDD_MODIFY_INDEX_TEST
void osd_copy_vcd_init(void)
{
    __osd_init();

#define MIDI_HEADER 4
    //setup region 1
    header_id = MIDI_HEADER;
    region[1].osd_w = 100;
    region[1].osd_h = 90;
    osd_create_region1( 1, 20, 185, NULL, OSD_FORMAT_16COLOR,OSD_INTERLACED);  

    //setup region 0
    header_id = MIDI_HEADER;
    region[0].osd_w = 220;  
    region[0].osd_h = 200; 
    osd_create_region1( 0, 50, 40, &region[1], OSD_FORMAT_16COLOR,OSD_INTERLACED);  
    osd_active_regions =2;
    osd_init__();
}
#endif

void LyricSetColor(BYTE color, BYTE revercolour)
{
    LyricFontcolor = color;
    LyricBgcolor = FONT_BACKGROUND_COLOUR;
    if (LyricFontcolor == LYRIC_INIT_COLOUR)
        LyricFigureColor = FONT_FIGURE_COLOUR;
    else
        LyricFigureColor = FONT_FIGURE_REV_COLOUR;
    LyricRevcolour = revercolour;
}

/****************************************
 *** function :draw the font bitmap ;
 *** pFont: the pointer of the font bitmap data
 *** xStart,yStart: the coordinate
 *** fontcolor: the font color 
 *** bgcolor : the background color of the font 
 *** FigureColor: the figure color of the font
 *** FontType : the font type 
 *** number: the OSD region NO.
 ****************************************/
void draw_midi_bitmap_HZnew(const UINT8* pFont, int xStart, int yStart,
    BYTE fontcolor, BYTE bgcolor, BYTE  FigureColor, BYTE FontType,
    BYTE number)
{
    BYTE CurrentByte, CurrentByte1, CurrentBit, CurrentBit1;
    BYTE NewFormatFlag,bDispHalfByte;
    UINT8* p1Font;
    UINT8* pTopLine, * pBtmLine, * pLine;
    UINT32 iDispLoc, disploc = 0;
    int iRegionWidth = region[number].osd_w ;
    int osd_format = region[number].osd_format;
    unsigned int     fwidth,fhight,fbit=0;
    unsigned int     i, j, Bperpixel,shift_num,tempi;

    pTopLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[number].osd_header[0] + OSD_DATA_OFFSET(region[number].osd_format)) * 32);
    pBtmLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[number].osd_header[1] + OSD_DATA_OFFSET(region[number].osd_format)) * 32);

    yStart = (p_scan) ? yStart : yStart>>1;
    iDispLoc = (yStart ) * iRegionWidth  + xStart;
    bDispHalfByte = iDispLoc & 0x01;
    iDispLoc = (((yStart - ((yStart) & 0x01)) * iRegionWidth ) + (xStart))>>1;

    switch (osd_format)
    {
    case OSD_FORMAT_4COLOR:
        Bperpixel = 2; // 4
        shift_num = 2;
        break;
    case OSD_FORMAT_256COLOR:
#ifdef OSD_SUPPORT_256_COLOR
        Bperpixel = 0; // 1
        shift_num = 8;
        break;
#else
		return;
#endif	// #ifdef OSD_SUPPORT_256_COLOR
    case OSD_FORMAT_16COLOR:
        Bperpixel = 1; // 2
        shift_num = 4;
        break;
    default:
        Bperpixel = 1; // 2
        shift_num = 4;
        break;
    }

    //judge the format
    NewFormatFlag = pFont[0];
    if (NewFormatFlag != 0xff)
    {
        fwidth = pFont[0];
        fhight = pFont[1];
    }
    else
    {
        fhight = (pFont[4] << 8) | pFont[3];
        fwidth = (pFont[6] << 8) | pFont[5];
        fbit = fwidth * fhight;
    }

    if (NewFormatFlag != 0xff)
    {
        disploc = 0;
        for (i = 0; i < fhight; i++)
        {
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    pLine = pBtmLine;
                else
                    pLine = pTopLine;

            for (j = 0; j < fwidth; j++)
            {
                tempi = (j+bDispHalfByte) >> Bperpixel;

                if (pFont[((j + disploc) >> 3) + 3] & (0x80 >>
                    ((j + disploc) & 0x07)))
                    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] <<
                        shift_num) |
                        fontcolor;
                else
                    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] <<
                        shift_num) |
                        bgcolor;
            }
            disploc += fwidth ;        
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    iDispLoc += iRegionWidth;
            }
        }
    else
    {
        switch(FontType)
        {
            case 0:
                fontcolor=bgcolor;
                break;
            case 1:
                FigureColor=bgcolor;
                break;
            case 2:
            //  FigureColor = 11;
                break;
            default:
                break;
        }

        if (fbit & 0x07)
        {
            p1Font = (UINT8 *)pFont + (fbit >> 3) + 1;
        }
        else
        {
            p1Font = (UINT8 *)pFont + (fbit >> 3);
        }

        disploc = 0;
        for (i = 0; i < fhight; i++)
        {
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    pLine = pBtmLine;
                else
                    pLine = pTopLine;

            for (j = 0; j < fwidth; j++)
            {
                CurrentByte = pFont[((j + disploc) >> 3) + 10];
                CurrentByte1 = p1Font[((j + disploc) >> 3) + 10];
                CurrentBit = CurrentByte & (0x80 >> ((j + disploc) & 0x07));
                CurrentBit1 = CurrentByte1 & (0x80 >> ((j + disploc) & 0x07));
                tempi = (j+bDispHalfByte) >> Bperpixel;

                if (CurrentBit != 0 && CurrentBit1 != 0)
                {
                    pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                        shift_num) & 0xf0) |
                        fontcolor; //0x02;//
                }
                else if (CurrentBit == 0 && CurrentBit1 != 0)
                {
                    pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                        shift_num) & 0xf0) |
                        FigureColor;//0x0b;//
                }
                else
                {
                    pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                        shift_num) & 0xf0) |
                        bgcolor; // 0x00;//
                }
            }
            disploc += fwidth ;  
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    iDispLoc += iRegionWidth;
            }
        }
   // osd_tog_region(number, OSD_ON);
    osd_tog_region(number, OSD_ON); //ouyang 2004.07.31
}


#ifdef MIDI_MULTIFONT_LIB
/*********************************************************************
//   ** function :draw the font bitmap of the GB1 and GB2 ;support the new GB 
//font.
//   ** xStart,yStart: the X&Y start position of the coordinate
//   ** c: GB code
//   ** fontcolor: the font color 
//   ** bgcolor : the background color of the font 
//   ** FigureColor: the figure color of the font
//   ** FontType : the font type 
//   ** number: the OSD region NO.
//   ** FontBaseNo: the font database NO.
 ***********************************************************************/
void osd_midi_DrawHZ_Mem(int xStart, int yStart, UINT16 c, BYTE fontcolor,
    BYTE bgcolor, BYTE FigureColor, BYTE FontType, BYTE number,
    BYTE FontBaseNo) 
{
    BYTE NewFormatFlag = 0;//,bDispHalfByte; //ByteLow,ByteHi;
    BYTE* pFont = (void*) (0), * pFont1;
    BYTE* pGB1Font = (void*) (0), * pGB2Font =(void*) (0);
    unsigned int     fwidth = 0,fhight = 0,fbit = 0;
    int CH = ( c >> 8), CL = (c& 0xFF);
    int Hgbcode;

    if (FontBaseNo == MIDI_LYRIC_FONTDEBASE)
    {
        pGB1Font = (BYTE *) (MIDI_OSDFONT_ADDR);
        pGB2Font = (UINT8 *) upMidiGB2FontAddr;
    }
    else if (FontBaseNo == MIDI_MENU_FONTDEBASE)
    {
        pGB1Font = (BYTE *) (upMenuGB1FontAddr);
        pGB2Font = (UINT8 *) upMenuGB2FontAddr;
    }

//    printf("osd_midi_DrawHZ_Mem draw wchar %c%c\n",CH,CL);
//    printf("CH %x CL %x NewFormatFlag %d FontBaseNo %d\n",CH,CL,NewFormatFlag,FontBaseNo);
 //   printf("PGBbase pGB1Font %x pGB2Font %x\n",pGB1Font,pGB2Font);
 //   /
  //  print_block(pGB1Font,0x10);
  //  print_block(pGB2Font,0x10);
    //get the font bitmap addr
    if ((CH >= 0xA1 && CH < 0xD7 && CL >= 0xA1 && CL < 0xFF) ||
        (CH == 0xD7 && CL >= 0xA1 && CL < 0xFa))
    {
        //the following is GB1 font     
        if (CH > 0xA9)
    {
            Hgbcode = 0xA7;
    }
        else
    {
            Hgbcode = 0xA1;
    }

        pFont1 = pGB1Font;  //(BYTE *)(MIDI_OSDFONT_ADDR); 
        NewFormatFlag = pFont1[0];
        
    if (NewFormatFlag != 0xff)
    {
            fwidth = pFont1[0];
            fhight = pFont1[1];
            fbit = fwidth * fhight;
        
            if (fbit & 0x07)
            {
                pFont = (BYTE *)
                    (pGB1Font +
                    ((CH - Hgbcode) * 94 + (CL - 0xA1)) * ((fbit >> 3) + 1)); 
//MIDI_OSDFONT_ADDR
            }
            else
        {
                pFont = (BYTE *)
                    (pGB1Font +
                    ((CH - Hgbcode) * 94 + (CL - 0xA1)) * (fbit >> 3)); //MIDI_OSDFONT_ADDR
            }
        }
            else
        {
            fhight = (pFont1[4] << 8) | pFont1[3];
            fwidth = (pFont1[6] << 8) | pFont1[5];
            fbit = fwidth * fhight;

            if (fbit & 0x07)
            {
                pFont = (BYTE *)
                    (pGB1Font +
                    ((CH - Hgbcode) * 94 + (CL - 0xA1)) * ((fbit >> 3) + 1) * 2); //MIDI_OSDFONT_ADDR
            }
                else
            {
                pFont = (BYTE *)
                    (pGB1Font +
                    ((CH - Hgbcode) * 94 + (CL - 0xA1)) * (fbit >> 3) * 2); //MIDI_OSDFONT_ADDR
            }
        }
    }
    else if (CH >= 0xD8 && CH < 0xF8 && CL >= 0xA1 && CL < 0xFF)
    {
        pFont1 = (UINT8 *) pGB2Font; //upMidiGB2FontAddr;
        NewFormatFlag = pFont1[0];

        if (NewFormatFlag != 0xff)
    {
            fwidth = pFont1[0];
            fhight = pFont1[1];
        fbit = fwidth * fhight;

        if (fbit & 0x07)
        {
                //upMidiGB2FontAddr
                pFont = (BYTE *)
                    (pGB2Font +
                    ((CH - 0xd8) * 94 + (CL - 0xA1)) * ((fbit >> 3) + 1));
        }
        else
        {
                //upMidiGB2FontAddr
                pFont = (BYTE *)
                    (pGB2Font + ((CH - 0xd8) * 94 + (CL - 0xA1)) * (fbit >> 3));
            }
        }
            else
            {
            fhight = (pFont1[4] << 8) | pFont1[3];
            fwidth = (pFont1[6] << 8) | pFont1[5];
            fbit = fwidth * fhight;

            if (fbit & 0x07)
                {
                //upMidiGB2FontAddr
                pFont = (BYTE *)
                    (pGB2Font +
                    ((CH - 0xd8) * 94 + (CL - 0xA1)) * ((fbit >> 3) + 1) * 2);
                }
            else
                {
                //upMidiGB2FontAddr
                pFont = (BYTE *)
                    (pGB2Font +
                    ((CH - 0xd8) * 94 + (CL - 0xA1)) * (fbit >> 3) * 2);
                }
                }
            }

    if (NewFormatFlag == 0xff)
    {
        pFont = pFont + 10;
        NewFormatFlag = 1;
        }
    else
    {
        pFont = pFont + 3;
        NewFormatFlag = 0;//may be other
    }
    gs_stDrawFont.Lock = 1;
    gs_stDrawFont.xStart = xStart;
    gs_stDrawFont.yStart  = yStart;
    gs_stDrawFont.fontcolor = fontcolor;
    gs_stDrawFont.pfntpt = pFont;
    gs_stDrawFont.size    = ((fwidth<<8)|(fhight));
    gs_stDrawFont.NewFormatFlag =  NewFormatFlag;
    gs_stDrawFont.bgcolor = bgcolor; 
    gs_stDrawFont.FigureColor = FigureColor;
    gs_stDrawFont.FontType = FontType; 
    gs_stDrawFont.number = number;
    MidiDrawFntPt(&gs_stDrawFont);
    osd_tog_region(number ,OSD_ON);    //ouyang 2004.07.31
}

#else

void osd_midi_DrawHZ_Mem(int xStart, int yStart, UINT16 c, BYTE fontcolor,
    BYTE bgcolor, BYTE FigureColor, BYTE FontType, BYTE number,
    BYTE FontBaseNo) 
{
    BYTE CurrentByte, CurrentByte1, CurrentBit, CurrentBit1;
    BYTE NewFormatFlag = 0,bDispHalfByte; //ByteLow,ByteHi;
    BYTE* p1Font, * pFont = (void*) (0), * pFont1;
    BYTE* pTopLine, * pBtmLine, * pLine; 
    BYTE* pGB1Font = (void*) (0), * pGB2Font =(void*) (0);
    UINT32 iDispLoc, disploc; //, uiDispHalfByte
    int iRegionWidth = region[number].osd_w ; //>>bIsMenuFont;
    int osd_format = region[number].osd_format;
    unsigned int     fwidth = 0,fhight = 0,fbit = 0;
    unsigned int      i, j, Bperpixel,shift_num,tempi;
    int CH = ( c >> 8), CL = (c& 0xFF);
    int Hgbcode;

    if (p_scan ==1)
    {
        yStart<<=1;
    }

    pTopLine = (BYTE *) (((BYTE *) get_osdbuf_baseptr()) +
        (region[number].osd_header[0] + OSD_DATA_OFFSET(region[number].osd_format)) * 32);
    pBtmLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[number].osd_header[1] + OSD_DATA_OFFSET(region[number].osd_format)) * 32);   

    iDispLoc = (yStart ) * iRegionWidth  + xStart;
    bDispHalfByte = iDispLoc & 0x01;
    iDispLoc = (((yStart - ((yStart) & 0x01)) * iRegionWidth ) + (xStart))>>1;

    if (FontBaseNo == MIDI_LYRIC_FONTDEBASE)
    {
        pGB1Font = (BYTE *) (MIDI_OSDFONT_ADDR);
        pGB2Font = (UINT8 *) upMidiGB2FontAddr;
    }
    else if (FontBaseNo == MIDI_MENU_FONTDEBASE)
    {
        pGB1Font = (BYTE *) (upMenuGB1FontAddr);
        pGB2Font = (UINT8 *) upMenuGB2FontAddr;
    }

    switch (osd_format)
    {
    case OSD_FORMAT_4COLOR:
        Bperpixel = 2; // 4
        shift_num = 2;
        break;
    case OSD_FORMAT_256COLOR:
#ifdef OSD_SUPPORT_256_COLOR
        Bperpixel = 0; // 1
        shift_num = 8;
        break;
#else
		return;
#endif // #ifdef OSD_SUPPORT_256_COLOR
    case OSD_FORMAT_16COLOR:
        Bperpixel = 1; // 2
        shift_num = 4;
        break;
    default:
        Bperpixel = 1; // 2
        shift_num = 4;
        break;
    }

    //get the font bitmap addr
    if ((CH >= 0xA1 && CH < 0xD7 && CL >= 0xA1 && CL < 0xFF) ||
        (CH == 0xD7 && CL >= 0xA1 && CL < 0xFa))
    {
        //the following is GB1 font     
        if (CH > 0xA9)
        {
            Hgbcode = 0xA7;
        }
        else
        {
            Hgbcode = 0xA1;
        }

        pFont1 = pGB1Font;  //(BYTE *)(MIDI_OSDFONT_ADDR); 
        NewFormatFlag = pFont1[0];

        if (NewFormatFlag != 0xff)
        {
            fwidth = pFont1[0];
            fhight = pFont1[1];
            fbit = fwidth * fhight;

            if (fbit & 0x07)
            {
                pFont = (BYTE *)
                    (pGB1Font +
                    ((CH - Hgbcode) * 94 + (CL - 0xA1)) * ((fbit >> 3) + 1)); //MIDI_OSDFONT_ADDR
            }
            else
            {
                pFont = (BYTE *)
                    (pGB1Font +
                    ((CH - Hgbcode) * 94 + (CL - 0xA1)) * (fbit >> 3)); //MIDI_OSDFONT_ADDR
            }
        }
        else
        {
            fhight = (pFont1[4] << 8) | pFont1[3];
            fwidth = (pFont1[6] << 8) | pFont1[5];
            fbit = fwidth * fhight;

            if (fbit & 0x07)
            {
                pFont = (BYTE *)
                    (pGB1Font +
                    ((CH - Hgbcode) * 94 + (CL - 0xA1)) * ((fbit >> 3) + 1) * 2); //MIDI_OSDFONT_ADDR
            }
            else
            {
                pFont = (BYTE *)
                    (pGB1Font +
                    ((CH - Hgbcode) * 94 + (CL - 0xA1)) * (fbit >> 3) * 2); //MIDI_OSDFONT_ADDR
            }
        }
    }
    else if (CH >= 0xD8 && CH < 0xF8 && CL >= 0xA1 && CL < 0xFF)
    {
        pFont1 = (UINT8 *) pGB2Font; //upMidiGB2FontAddr;
        NewFormatFlag = pFont1[0];

        if (NewFormatFlag != 0xff)
        {
            fwidth = pFont1[0];
            fhight = pFont1[1];
            fbit = fwidth * fhight;

            if (fbit & 0x07)
            {
                //upMidiGB2FontAddr
                pFont = (BYTE *)
                    (pGB2Font +
                    ((CH - 0xd8) * 94 + (CL - 0xA1)) * ((fbit >> 3) + 1));
            }
            else
            {
                //upMidiGB2FontAddr
                pFont = (BYTE *)
                    (pGB2Font + ((CH - 0xd8) * 94 + (CL - 0xA1)) * (fbit >> 3));
            }
        }
        else
        {
            fhight = (pFont1[4] << 8) | pFont1[3];
            fwidth = (pFont1[6] << 8) | pFont1[5];
            fbit = fwidth * fhight;

            if (fbit & 0x07)
            {
                //upMidiGB2FontAddr
                pFont = (BYTE *)
                    (pGB2Font +
                    ((CH - 0xd8) * 94 + (CL - 0xA1)) * ((fbit >> 3) + 1) * 2);
            }
            else
            {
                //upMidiGB2FontAddr
                pFont = (BYTE *)
                    (pGB2Font +
                    ((CH - 0xd8) * 94 + (CL - 0xA1)) * (fbit >> 3) * 2);
            }
        }
    }

    //draw the GB1 font bitmap  
    if (NewFormatFlag != 0xff)
    {
        pFont = pFont + 3;
        disploc = 0;
        for (i = 0; i < fhight; i++)
        {
            if (((i + yStart) & 0x01)||(p_scan==1))
                    pLine = pBtmLine;
                else
                    pLine = pTopLine;
            
            for (j = 0; j < fwidth; j++)
            {
                tempi = (j+bDispHalfByte) >> Bperpixel;

                if (pFont[((j + disploc) >> 3)] & (0x80 >>
                    ((j + disploc) & 0x07)))
                {
                pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] <<
                    shift_num) |
                    fontcolor;
                }
                else
                    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] <<
                        shift_num) |
                        bgcolor;
            }
            disploc += fwidth ;        
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    iDispLoc += iRegionWidth;
            }
        }
    else
    {
#if 1
        switch (FontType)
        {
        case 0:
            fontcolor = bgcolor;
            break;
        case 1:
            FigureColor = bgcolor;
            break;
        case 2:
            //  FigureColor = 11;
            break;
        case 3:
            FigureColor = fontcolor;
            break;
        default:
            break;
        }
#endif  
        //  fbit=fwidth*fhight;

        pFont = pFont + 10;
        if (fbit & 0x07)
        {
            p1Font = pFont + (fbit >> 3) + 1;
        }
        else
        {
            p1Font = pFont + (fbit >> 3);
        }

        disploc = 0;
        for (i = 0; i < fhight; i++)
        {
            if (((i + yStart) & 0x01)||(p_scan==1))//xlluo 2004
                    pLine = pBtmLine;
                else
                    pLine = pTopLine;
          
            for (j = 0; j < fwidth; j++)
            {
                CurrentByte = pFont[((j + disploc) >> 3)];
                CurrentByte1 = p1Font[((j + disploc) >> 3)];
                CurrentBit = CurrentByte & (0x80 >> ((j + disploc) & 0x07));
                CurrentBit1 = CurrentByte1 & (0x80 >> ((j + disploc) & 0x07));
                tempi = (j+bDispHalfByte) >> Bperpixel;
                {
                    if (CurrentBit != 0 && CurrentBit1 != 0)
                    {
                        pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                            shift_num) & 0xf0) |
                            fontcolor; //0x02;//
                    }
                    else if (CurrentBit == 0 && CurrentBit1 != 0)
                    {
                        pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                            shift_num) & 0xf0) |
                            FigureColor;  //0x0b;//
                    }
                    else
                    {
                        pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                            shift_num) & 0xf0) |
                            bgcolor; //0x00;//
                    }
                }
            }
            disploc += fwidth ;  
            if (((i + yStart) & 0x01)||(p_scan ==1))
                    iDispLoc += iRegionWidth;
            }
        }
        osd_tog_region(number ,OSD_ON);    //ouyang 2004.07.31
    }   
#endif


//the following is 30*30 font width for number and alphabet
#define SUPPORT_BIG5ANDGB_MIDI
#ifdef SUPPORT_BIG5ANDGB_MIDI

BYTE MenuNumwidth[10] =
{
    16, 14, 16, 16, 16, 16, 16, 16, 16, 16, 
};
BYTE MenuABCwidth[26] =
{
    24, 20, 20, 20, 20, 20, 24, 24, 14, 18, 22, 20, 28, 24, 20, 20, 20, 22,
    18, 22, 24, 24, 28, 22, 24, 20, 
};
BYTE Menuabcwidth[26] =
{
    16, 16, 16, 16, 16, 16, 16, 18, 12, 14, 18, 12, 28, 20, 16, 16, 16, 16, 14,
    14, 18, 18, 24, 18, 18, 16, 
};

#else

BYTE MenuNumwidth[10] =
{
    13, 12, 15, 15, 16, 14, 15, 15, 15, 15, 
};
BYTE MenuABCwidth[26] =
{
    23, 20, 20, 20, 20, 20, 23, 23, 11, 17, 22, 19, 27, 24, 20, 20, 20, 22,
    18, 21, 23, 23, 27, 22, 23, 20, 
};
BYTE Menuabcwidth[26] =
{
    15, 16, 13, 16, 15, 15, 16, 17, 9, 12, 17, 16, 27, 19, 15, 15, 16, 13, 11,
    11, 18, 17, 23, 17, 17, 14, 
};

#endif


BYTE MenuFontcolor, MenuBgcolor, MenuFigureColor;

#define MENU_FONT_WIDTH (30)
#define MENU_OTHER_WIDTH (16)

//when change the OSD color of the Menu font base, call it
void MidiSetMenuFontColor(BYTE FontColor, BYTE BgColor, BYTE FigureColor)
{
    MenuFontcolor = FontColor;
    MenuBgcolor = BgColor;
    MenuFigureColor = FigureColor;
}

#ifdef SUPPORT_GB_FONTBASE3
    /*********************************************************************
    //   ** function :search GB3 base font pointer; gb3font should be include in font3 base
    //   ** hzcode: GB code
    //   **FontBaseNo:for menu or lyric
     ***********************************************************************/
#define GB3_FONTBASE_FLAG   (0x10000000L) 
#define GB3_FONTBASE_NONFLAG (0x0fffffffL)//ouly use 28 bit for fontsize
#define GET_LONG_INT(p)         (((*((p)+3))<<24)|((*((p)+2))<<16)|((*((p)+1))<<8)|(*(p)))     
#define GET_SHORT_INT(p)    ((*((p)+1)<<8)|(*(p)))
#define GET_HZCODE(p)           ((UINT16)GET_SHORT_INT(p))
BYTE *midi_GetGB3Font(UINT16 hzcode,BYTE FontBaseNo)     
{
    BYTE * pfont3base =upGB3FontAddr;
    BYTE fontbase;
    BYTE *retpos;
    while ((*pfont3base)&&(upGB3FontEndPtr>pfont3base))
    {
        if ( GET_HZCODE(pfont3base)==hzcode)
        {
            fontbase = (((GET_LONG_INT(pfont3base+2))&(GB3_FONTBASE_FLAG))&&1); 
            if (!(fontbase^FontBaseNo))
            {
                retpos =pfont3base+6;
                return retpos;
            }else
            {
                pfont3base +=(GET_LONG_INT(pfont3base+2)&(GB3_FONTBASE_NONFLAG));
            }
        }else
        {
            pfont3base +=(GET_LONG_INT(pfont3base+2)&(GB3_FONTBASE_NONFLAG));
        }  
    }
    return 0;
}    
#endif


#ifdef MIDI_MULTIFONT_LIB
//extern int current_midi_osd_lang;//for menu
//extern BYTE ReadExtraFontLib(BYTE lang);
//void MidiDrawFntPt(int xStart,int yStart,BYTE fontcolor,BYTE * pfntpt,UINT16 size,
 //   BYTE NewFormatFlag,BYTE bgcolor, BYTE FigureColor, BYTE FontType, BYTE number)
 //xlluo add for release more stack
 void MidiDrawFntPt(DrawFnt_S *pfntSt)
{
    BYTE CurrentByte, CurrentByte1, CurrentBit, CurrentBit1;
    BYTE bDispHalfByte;
    UINT8* pFont;
    UINT8* p1Font;
    UINT8* pTopLine, * pBtmLine, * pLine;
    UINT32 iDispLoc, disploc = 0;
    int iRegionWidth = region[pfntSt->number].osd_w ;
    int osd_format = region[pfntSt->number].osd_format;
    unsigned int     fwidth,fhight,fbit=0;
    unsigned int     i, j, Bperpixel,shift_num,tempi;
    fwidth = (pfntSt->size>>8)&0xff;
    fhight = pfntSt->size&0xff;
    fbit = fwidth * fhight;
    pFont = pfntSt->pfntpt;
    if (!pfntSt->pfntpt)
        return;
    
    if (p_scan ==1)
    {
        pfntSt->yStart<<=1;
    }
    pTopLine = (BYTE *) (((BYTE *) get_osdbuf_baseptr()) +
        (region[pfntSt->number].osd_header[0] + OSD_DATA_OFFSET(region[pfntSt->number].osd_format)) * 32);
    pBtmLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[pfntSt->number].osd_header[1] + OSD_DATA_OFFSET(region[pfntSt->number].osd_format)) * 32);   

    iDispLoc = (pfntSt->yStart ) * iRegionWidth  + pfntSt->xStart;
    bDispHalfByte = iDispLoc & 0x01;
    iDispLoc = (((pfntSt->yStart - ((pfntSt->yStart) & 0x01)) * iRegionWidth ) + (pfntSt->xStart))>>1;

    switch (osd_format)
    {
    case OSD_FORMAT_4COLOR:
        Bperpixel = 2; // 4
        shift_num = 2;
        break;
    case OSD_FORMAT_256COLOR:
        Bperpixel = 0; // 1
        shift_num = 8;
        break;
    case OSD_FORMAT_16COLOR:
        Bperpixel = 1; // 2
        shift_num = 4;
        break;
    default:
        Bperpixel = 1; // 2
        shift_num = 4;
        break;
    }
    
    if (pfntSt->NewFormatFlag)
    {
        switch (pfntSt->FontType)
        {
            case 0:
                pfntSt->fontcolor = pfntSt->bgcolor;
                break;
            case 1:
                pfntSt->FigureColor = pfntSt->bgcolor;
                break;
            case 2:
                break;
            case 3:
                pfntSt->FigureColor = pfntSt->fontcolor;
                break;
            default:
                break;
        }

        if (fbit & 0x07)
        {
            p1Font = pFont + (fbit >> 3) + 1;
        }
        else
        {
            p1Font = pFont + (fbit >> 3);
        }
        
        disploc = 0;
        for (i = 0; i < fhight; i++)
        {
            if (((i + pfntSt->yStart) & 0x01)||(p_scan==1))//xlluo 2004
                    pLine = pBtmLine;
                else
                    pLine = pTopLine;
          
            for (j = 0; j < fwidth; j++)
            {
                CurrentByte = pFont[((j + disploc) >> 3)];
                CurrentByte1 = p1Font[((j + disploc) >> 3)];
                CurrentBit = CurrentByte & (0x80 >> ((j + disploc) & 0x07));
                CurrentBit1 = CurrentByte1 & (0x80 >> ((j + disploc) & 0x07));
                tempi = (j+bDispHalfByte) >> Bperpixel;
                {
                    if (CurrentBit != 0 && CurrentBit1 != 0)
                    {
                        pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                            shift_num) & 0xf0) |
                            pfntSt->fontcolor; //0x02;//
                    }
                    else if (CurrentBit == 0 && CurrentBit1 != 0)
                    {
                        pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                            shift_num) & 0xf0) |
                            pfntSt->FigureColor;  //0x0b;//
                    }
                    else
                    {
                        pLine[iDispLoc + tempi] = ((pLine[iDispLoc + tempi] <<
                            shift_num) & 0xf0) |
                            pfntSt->bgcolor; //0x00;//
                    }
                }
            }
            disploc += fwidth ;  
            if (((i + pfntSt->yStart) & 0x01)||(p_scan ==1))
                    iDispLoc += iRegionWidth;
            }
    }    
    else
    {
        disploc = 0;
        for (i = 0; i < fhight; i++)
        {
            if (((i + pfntSt->yStart) & 0x01)||(p_scan==1))
                pLine = pBtmLine;
            else
                pLine = pTopLine;
            if (!pLine)
            {
                //printf("waringing:pline error\n");
            }
            for (j = 0; j < fwidth; j++)
            {
                tempi = (j+bDispHalfByte) >> Bperpixel;

                if (pFont[((j + disploc) >> 3)] & (0x80 >>
                    ((j + disploc) & 0x07)))
                {
                    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] <<
                        shift_num) |
                        pfntSt->fontcolor;
                }
                else
                    pLine[iDispLoc + tempi] = (pLine[iDispLoc + tempi] <<
                        shift_num) |
                        pfntSt->bgcolor;
            }
            disploc += fwidth ;        
            if (((i + pfntSt->yStart) & 0x01)||(p_scan ==1))
                    iDispLoc += iRegionWidth;
        }
    }
}

//[in/out] pfnt
BYTE GotoNextFntPt(Font_S * pfnt)
{
    if (pfnt->pfont == 0)
    {//init
         pfnt->pfont =  g_stCurFontLibHead.pFontStart;//(BYTE *)(EXTRAN_FONT_ADDR);//
       //  printf("set fnt set\n");
       //  print_block(pfnt,sizeof(Font_S));        
       //  print_block(pfnt->pfont,0xa0);
    }
    else
    {
        pfnt->pfont  += FONTTBALE_STRUCTSIZE +
            (((pfnt->stFontPtr.bySizeX * pfnt->stFontPtr.bySizeY + 7)>>3)
                <<(pfnt->stFontPtr.dwData.context.sharp^1));        
    }
 //   print_block(pfnt,0x10);
    memcpy(&pfnt->stFontPtr,pfnt->pfont,FONTTBALE_STRUCTSIZE);
   // printf("GotoNextFntPt Find wCharCode %x\n",
    //    (pfnt->stFontPtr.wCharCode));
  //  print_block(pfnt,sizeof(Font_S));        
    //is end?
//    if ((pfnt->stFontPtr.dwData.context.pos + g_stCurFontLibHead.pFontStart) != pfnt->pfont)
    {//has reach end or font lib error
  /*      printf("pfnt->stFontPtr.dwData.context.pos %x
            pfnt->pfont %x g_stCurFontLibHead.pFontStart  %x\n",
            pfnt->stFontPtr.dwData.context.pos,pfnt->pfont,g_stCurFontLibHead.pFontStart);*/
     //   print_block(pfnt,sizeof(Font_S));        
 //       memset(pfnt,0,sizeof(Font_S));
        //printf("return 0 wheng \n");
//        return 0;
    }    
    return 1;
}

//[in]   ch/type
//[out] pfnt
BYTE SearchExFntPt(UINT16 ch,BYTE type,Font_S * pfnt)
{
    //init search
 //   BYTE* pfntlib = g_stCurFontLibHead.pFontStart;
    int i = 0;
  //  printf("SearchExFntPt %x type %d\n",ch,type);
    //fliter
    if (ch < 0x21)  //ouyang change 05.09.07
    {

        switch(g_stCurFontLibHead.byLanguage)
        {
            case VITENAM:
                if ((ch != 0x02)&&(ch!=0x05)&&(ch != 0x06)&&(ch != 0x14)
                   &&(ch != 0x1e)&&(ch!= 0x19))
                {
            //        printf("vitename before space\n");
                    break;
                }else
                    return 0;
            default:
                return 0;
        }
    }
    memset(pfnt,0,sizeof(Font_S));
    //search&compare

#ifdef DBG_MULTIFONT_LIB
      //          printf("ReadFont sz %d font num %d\n",
      //              g_stCurFontLibHead.wLibSize,g_stCurFontLibHead.wFontCount);
 //             print_block(g_stCurFontLibHead.pFontStart,0x10);
#endif//DBG_MULTIFONT_LIB
    while((GotoNextFntPt(pfnt))&&(i<g_stCurFontLibHead.wFontCount))
    {
 //       printf("cmp pfnt->stFontPtr.dwData.context.type %x type %x\n",
  //         pfnt->stFontPtr.dwData.context.type,type);
  //      printf("cmp pfnt->stFontPtr.wCharCode %x ch %x\n",
   //         pfnt->stFontPtr.wCharCode,ch);
        if ((pfnt->stFontPtr.wCharCode == ch)&&
            (pfnt->stFontPtr.dwData.context.type == type))
        {            
      //       printf("FindHz %x\n",ch);
         //    while(1);
            return 1;
        }
        i++;
    }    
   // printf("FindHz fail\n");
    return 0;
}

BYTE GetExtraFontWide(UINT16 ch,BYTE type)
{
    Font_S stFontS;
    if (SearchExFntPt(ch,type,&stFontS))
    {
        return stFontS.stFontPtr.bySizeX;
    }
    return OTHER_FONT_WIDTH;
}

#if defined(MIDI_MULTIFONT_LIB)&&defined(SUPPORT_SANJING_LYRIC_SPEC)
UINT16 ModifyLyricBeforeShow(BYTE c,BYTE c1)
{
	
	return ((c&0xff)|((UINT16)c1<< 8));
}
#endif  //ouyang 050813

int Disp_ExtraText_OSD(DispText_S * pstTxtDis,//int xx, int yy, BYTE* Lyric, BYTE regNum, int margin,
                BYTE uFontBase,BYTE bLang)//, BYTE FontType,int endXEdge
{
        int iRegionWidth = region[pstTxtDis->regNum].osd_w<<1; 
//        BYTE* p;// = pstTxtDis->Lyric;
//        UINT16 ch = 0;
        UINT16 x1, y1;
        
        UINT8 uOtherWidth=0;
        BYTE Fontcolor=0, Bgcolor=0, FigureColor=0;  //,FontType
        BYTE FontHeight;//,uFontWidth;

        BYTE bIsVarWide    = 0;    //solid or changeable char wide
        BYTE bIsWideChar  = 0;//(((g_stCurFontLibHead.byFontFlg & 0x01)&&0x01)); //wchar or char
        BYTE bIsReverDisp = 0;//(g_stCurFontLibHead.byFontFlg & 0x02)&&0x01;//disp dirction

        Font_S stCurFntinf;
    //    printf("%s Lyric %s\n",__FUNCTION__,Lyric);
      //  if (!g_bIsExtFontEnable) 
        {
            //printf("g_bIsExtFontEnable is unable\n");
     //       return Disp_Text_OSD(xx,yy,Lyric,regNum,margin,
   //                                                 uFontBase,FontType,endXEdge);            
        }
       // printf("bIsWideChar %d bIsReverDisp %d\n",
           // bIsWideChar,bIsReverDisp);
//        p = pstTxtDis->Lyric;   
        if (bIsReverDisp)
        {
            if (pstTxtDis->endXEdge>pstTxtDis->xx)//end must less than xx
                pstTxtDis->endXEdge = 0;
        }else
        {
            if ((!pstTxtDis->endXEdge)||(pstTxtDis->endXEdge>(iRegionWidth -10)))
                pstTxtDis->endXEdge = iRegionWidth;
        }
        
        //printf("Disp_ExtraText_OSD %s\n",Lyric);
        //print_block(Lyric,strlen(Lyric));

        //provide the codepage error
        if (bLang != g_stCurFontLibHead.byLanguage)
        {
            //printf("error current langlib %d %d\n",bLang,
              //          g_stCurFontLibHead.byLanguage);
            if (!ReadExtraFontLib(bLang))
            {
               // printf("get font error\n");
             //   while(1);
                return 0;
            }
        }
        
        if (uFontBase == MIDI_LYRIC_FONTDEBASE)
        {
       //     uFontWidth = LYRIC_FONT_WIDTH ; 
            uOtherWidth = OTHER_FONT_WIDTH;
            FontHeight =LYRIC_FONT_HIGHT;
                
            Fontcolor = LyricFontcolor;
            Bgcolor = LyricBgcolor;
            FigureColor = LyricFigureColor;
        }
        else if (uFontBase == MIDI_MENU_FONTDEBASE)
        {
         //   uFontWidth   = MENU_FONT_WIDTH ; //LYRIC_FONT_WIDTH;
            uOtherWidth = MENU_OTHER_WIDTH;//OTHER_FONT_WIDTH;
            FontHeight = 30;
    
            Fontcolor = MenuFontcolor;
            Bgcolor = MenuBgcolor;
            FigureColor = MenuFigureColor;
        }else
        {
            //printf("error font base\n");
            return 0;
        }
   
        if (bIsReverDisp)
        {
            if ((pstTxtDis->xx < 0)||(pstTxtDis->xx > iRegionWidth))
                pstTxtDis->xx = iRegionWidth;
        }else
        {
            if (pstTxtDis->xx < 0)
                pstTxtDis->xx = 0;
        }
            
        x1 = pstTxtDis->xx;
        y1 = pstTxtDis->yy;    
        
        while (*pstTxtDis->Lyric == ' ')//jump spacep
            pstTxtDis->Lyric++;//p++;
    
        while (*pstTxtDis->Lyric)///*p)
        {
            int iRes;
            BYTE c, c1;
            #if defined(MIDI_MULTIFONT_LIB)&&defined(SUPPORT_SANJING_LYRIC_SPEC)
            UINT16 cc;
            #endif  //ouyang 050813
            iRes = 0;

            //get font char
            c = *(pstTxtDis->Lyric);
            c1 = 0;                       //xlluo 20050812

     #if defined(MIDI_MULTIFONT_LIB)&&defined(SUPPORT_SANJING_LYRIC_SPEC)
		cc = ModifyLyricBeforeShow(c,c1);
     #endif//ouyang 050813

         #if defined(MIDI_MULTIFONT_LIB)&&defined(SUPPORT_SANJING_LYRIC_SPEC)  //ouyang 050813    
            iRes =SearchExFntPt((UINT16)cc,   //((c&0xff)|((UINT16)c1<< 8)),
                            uFontBase,&stCurFntinf);
         #else
         //   iRes =SearchExFntPt((UINT16)((c&0xff)|((UINT16)c1<< 8)),
          //                  uFontBase,&stCurFntinf);
 iRes =SearchExFntPt((UINT16)((c&0xff)|(((UINT16)c1<< 8)&0xff00)),
                            uFontBase,&stCurFntinf);//ouyang change 050922
         #endif   
            printf("SearchExFntPt iRes = %d\n",iRes);
            printf("stCurFntinf.stFontPtr.bySizeX %d x1 %d \n",
                stCurFntinf.stFontPtr.bySizeX,x1);
            if (!iRes)
                c = ' ';//if fail to found bitmap, show space
            if (iRes)
            {
                //       uFontWidth =  stCurFntinf.stFontPtr.bySizeX;
                //       FontHeight  = stCurFntinf.stFontPtr.bySizeX;
                if (((pstTxtDis->endXEdge - x1) < (stCurFntinf.stFontPtr.bySizeX))
                    ||((iRegionWidth - x1) < (stCurFntinf.stFontPtr.bySizeX)))  //LYRIC_FONT_WIDTH
                {
                        //xlluo add a mend here                 //2004-11-26
                        //printf("break\n");
                        break;
                }
                //draw font
                if (bIsReverDisp)
                    x1 -= (stCurFntinf.stFontPtr.bySizeX) + pstTxtDis->margin;
         //       printf("call MidiDrawextraFont parament\n");
         //       printf("x1 %d y1 %d\n",x1,y1);
          //      print_block(&stCurFntinf,0x10);
           //     printf(" Fontcolor %d ,Bgcolor %d,FigureColor %d,FontType %d regNum %d \n",
          //          Fontcolor,Bgcolor,FigureColor,FontType,regNum);
 //               MidiDrawExtraFont(x1,y1,&stCurFntinf,Fontcolor,Bgcolor,FigureColor,FontType,regNum);  
                gs_stDrawFont.Lock =1;
                gs_stDrawFont.xStart = x1;
                gs_stDrawFont.yStart  = y1;
                gs_stDrawFont.fontcolor = Fontcolor;
                gs_stDrawFont.pfntpt = ((BYTE *)(stCurFntinf.pfont+FONTTBALE_STRUCTSIZE));
                gs_stDrawFont.size    = (((UINT16)stCurFntinf.stFontPtr.bySizeX<<8)|((UINT16)stCurFntinf.stFontPtr.bySizeY));
                gs_stDrawFont.NewFormatFlag =  stCurFntinf.stFontPtr.dwData.context.sharp^1;
                gs_stDrawFont.bgcolor = Bgcolor; 
                gs_stDrawFont.FigureColor = FigureColor;
                gs_stDrawFont.FontType = pstTxtDis->FontType; 
                gs_stDrawFont.number = pstTxtDis->regNum;
                 MidiDrawFntPt(&gs_stDrawFont);
                    /*x1,y1,Fontcolor,
                         ((BYTE *)(stCurFntinf.pfont+FONTTBALE_STRUCTSIZE)),
                             (((UINT16)stCurFntinf.stFontPtr.bySizeX<<8)|((UINT16)stCurFntinf.stFontPtr.bySizeY)),
                              stCurFntinf.stFontPtr.dwData.context.sharp^1,Bgcolor,FigureColor,FontType,regNum);*/

                if (!bIsReverDisp)
                    x1 += (stCurFntinf.stFontPtr.bySizeX) + pstTxtDis->margin;
            }
            else
            {//draw space
                if (((pstTxtDis->endXEdge - x1) < (uOtherWidth))||((iRegionWidth - x1) < (uOtherWidth)))  // LYRIC_FONT_WIDTH
                    break;   //width is not enough break
                if ((c == ' ') && (*(pstTxtDis->Lyric - 1) != ' '))
                {
                    if (uFontBase == MIDI_MENU_FONTDEBASE)   
                    {     
                        int wspace = uOtherWidth+3;
                        if (((pstTxtDis->endXEdge - x1) < (wspace))||((iRegionWidth - x1) < (wspace)))
                            wspace = pstTxtDis->endXEdge-x1;
                        if (bIsReverDisp)
                            x1 -= wspace+3; //OTHER_FONT_WIDTH
                        Osd_Clear_Rect(x1,  y1, wspace,FontHeight,Bgcolor,pstTxtDis->regNum);
                        if (!bIsReverDisp)
                            x1 += wspace-3; //OTHER_FONT_WIDTH
                    }else
                    {
                        if (bIsReverDisp)
                            x1 -= uOtherWidth; //OTHER_FONT_WIDTH
                        Osd_Clear_Rect(x1,  y1, uOtherWidth+3,FontHeight,Bgcolor,pstTxtDis->regNum);
                        if (!bIsReverDisp)
                            x1 += uOtherWidth; //OTHER_FONT_WIDTH
                    }
                }
            }
            pstTxtDis->Lyric++;
        }
        osd_tog_region(pstTxtDis->regNum, OSD_ON);
        return x1;
}

BYTE SwLangLib(BYTE Lang)
{
    extern Search_S stCurSearch;
    BYTE fbase = Lang & 0x0f;
    BYTE flang = 0; 
  //  printf("%s\n",__FUNCTION__);
    if (!g_bIsExtFontEnable)
    {
        //printf("not support multilanglib\n");
        return 0;
    }
    if (fbase == MIDI_LYRIC_FONTDEBASE)
        flang = g_CurLangStatus.ucCurLyricLang;//lyric status is solid when need
    else if (fbase == MIDI_MENU_FONTDEBASE)
    {
        if ((stCurSearch.uRecordType & 0x01)||
#ifdef ABROADSINGERTYPE//xlluo 050817
            (stCurSearch.uRecordType & 0x10)||
#endif //ABROADSINGERTYPE//xlluo 050817
                (MenuState == MENU_MULTI_INDEX_SEL_PLAYLIST))//show songinfo
            flang = (Lang &0xf0)>>4;         //song info
        else
            flang = g_CurLangStatus.ucCurMenuLang;//current_midi_osd_lang;//menu
            //for test
    }else
    {//error
        //printf("error langtype\n");
        return 0;//it's unexpect
    }
    //printf("lang is %d\n",flang);
    if (flang < DEFAULT_EXTLANG)
        return 0;
    else
        return flang;
}

int DispBaseTextOsd(DispText_S * pstTxtDis,BYTE uFontBase)
{
    int iRegionWidth = region[pstTxtDis->regNum].osd_w<<1; 
    BYTE* p = pstTxtDis->Lyric;
    UINT16 ch = 0;
    UINT16 x1, y1;
    UINT8 uFontWidth=0, uOtherWidth=0;
    BYTE Fontcolor=0, Bgcolor=0, FigureColor=0;  //,FontType
    BYTE* pabc_Width, * pABC_Width, * pNum_Width;
    BYTE FontHeight;
#ifdef SUPPORT_GB_FONTBASE3
    BYTE *gb3pos =0;
#endif
    if ((!pstTxtDis->endXEdge)||(pstTxtDis->endXEdge>(iRegionWidth -10)))
        pstTxtDis->endXEdge =iRegionWidth;
    
    pabc_Width = pABC_Width = pNum_Width = (void *)(0);
    if (uFontBase == MIDI_LYRIC_FONTDEBASE)
    {
        uFontWidth = LYRIC_FONT_WIDTH ; 
        uOtherWidth = OTHER_FONT_WIDTH;
        FontHeight =LYRIC_FONT_HIGHT;

        Fontcolor = LyricFontcolor;
        Bgcolor = LyricBgcolor;
        FigureColor = LyricFigureColor;
        pabc_Width = abc_width;
        pABC_Width = ABC_width;
        pNum_Width = num_width;
    }
    else if (uFontBase == MIDI_MENU_FONTDEBASE)
    {
        uFontWidth = MENU_FONT_WIDTH ; //LYRIC_FONT_WIDTH;
        uOtherWidth = MENU_OTHER_WIDTH;//OTHER_FONT_WIDTH;
        FontHeight =30;

        Fontcolor = MenuFontcolor;
        Bgcolor = MenuBgcolor;
        FigureColor = MenuFigureColor;

        pabc_Width = Menuabcwidth;
        pABC_Width = MenuABCwidth;
        pNum_Width = MenuNumwidth;
        pstTxtDis->endXEdge -= 10;
    }else
    {
        //printf("error font base\n");
        return 0;
    }

    if (pstTxtDis->xx < 0)
        pstTxtDis->xx = 0;
    x1 = pstTxtDis->xx;
    y1 = pstTxtDis->yy;    
    while (*p == ' ')
        p++;
//printf("%s\n",__FUNCTION__);
    //  osd_tog_region(regNum, OSD_ON);
    //printf("iRes %d",iRes);
//printf("pstTxtDis FontType %d regNum %d\n", pstTxtDis->FontType, pstTxtDis->regNum);
//print_block(pstTxtDis->Lyric,0x20);
    while (*p)
    {
        int iRes;
        BYTE c, c1;
        iRes = 0;
        c = *p;
        c1 = *(p + 1);
 #ifdef SUPPORT_GB_FONTBASE3
        if (((c  >= 0xA1 && c  < 0xD7 && c1 >= 0xA1 && c1 < 0xFF) ||
            (c  == 0xD7 && c1 >= 0xA1 && c1 < 0xFa))||
             (c  >= 0xD8 && c  < 0xF8 && c1 >= 0xA1 && c1 < 0xFF))
 #else
        if (c>0x80&&c1>0x80);
#endif
        {
            iRes = 2;
            p ++;
            if (iRegionWidth - x1 < 48) //
            {
                break;   //width is not enough break
        }
        }
 #ifdef SUPPORT_GB_FONTBASE3
        else if ((c > 0x80))//&&((c1>80)||(c1<80)))
        {
            UINT16 gbcode =(c<<8|c1);
            gb3pos =midi_GetGB3Font(gbcode,uFontBase);
            if (gb3pos)
            {
                iRes = 3;
                p ++;
                if (iRegionWidth - x1 < 48) //
                    break;   //width is not enough break
            }else
            {
                //printf("search gb3base fail\n");
                p ++;
                iRes =0;
            }
        }    
#endif
        else if (((c >= 65) && (c <= 90)) ||     //A~Z
                 ((c >= 97) && (c <= 122)) ||    //a~z
                 ((c >= 192) && (c <= 223)) ||   //Europe characters
                 ((c >= 48) && (c <= 57)) || ((c >= 33) && (c <= 47)) //digit numbers //ouyang 2004.07.31
                 ||(c ==':'))      				//interpunction //ouyang 2004.07.31
        {
            c1 = c + 0x80;
            c = 0x03 + 0xa0;
            iRes = 2;
        }
        else
        {
            switch (c)
            {
            case ' ':
                iRes = 1;
                break;
            default:
                iRes = 0;
                break;
            }
        }

        if (iRes == 0)
            c = ' ';
        if (iRes == 2)
        {
            //          if (c!=0xa3)
            {
                if (((pstTxtDis->endXEdge - x1) < (uFontWidth))||((iRegionWidth - x1) < (uFontWidth)))  //LYRIC_FONT_WIDTH
                {
                    //xlluo add a mend here                 //2004-11-26
                        break;
                }
            }
            ch = (c << 8) | (c1);   
       //     printf("call osd_midi_DrawHZ_Mem %c%c \n",c,c1);
            osd_midi_DrawHZ_Mem(x1, y1, ch, Fontcolor, Bgcolor,
                FigureColor, pstTxtDis->FontType, pstTxtDis->regNum, uFontBase);  //fontcolor, bgcolor,
            if (c == 0xa3)
                    {
                        if (c1 >= 0xe1 && c1 <= 0xfa)
                    x1 += pabc_Width[c1 - 0xe1];//+margin;
                        else if ((c1 >= 0xc1) && (c1 <= 0xda))
                    x1 += pABC_Width[c1 - 0xc1];//+margin;
                        else if ((c1 > 0xaf) && (c1 < 0xba))
                        {
                    x1 += pNum_Width[c1 - 0xb0] + pstTxtDis->margin;
                        }
                        else
                        {
                    x1 += uOtherWidth;  //OTHER_FONT_WIDTH
                        }
                        }
            else
                        {
                x1 += (uFontWidth) + pstTxtDis->margin;        //LYRIC_FONT_WIDTH
            }
        }
 #ifdef SUPPORT_GB_FONTBASE3
        else if (iRes == 3)
        {
            {
                if (((pstTxtDis->endXEdge - x1) < (uFontWidth))||((iRegionWidth - x1) < (uFontWidth)))  //LYRIC_FONT_WIDTH
                {
                    break;   //width is not enough break
                }
            }        
            draw_midi_bitmap_HZnew(gb3pos,x1, y1<<1, Fontcolor, 
                Bgcolor,FigureColor, pstTxtDis->FontType, pstTxtDis->regNum);
            x1 += (uFontWidth) + pstTxtDis->margin;        //LYRIC_FONT_WIDTH
                        }    
#endif
        else
        {
            if (((pstTxtDis->endXEdge - x1) < (uOtherWidth))||((iRegionWidth - x1) < (uOtherWidth)))  // LYRIC_FONT_WIDTH
                break;   //width is not enough break
#if 0 //def SUPPORT_SANJING_WIDESAPCE                //xlluo for sj space 04-10-15
            Osd_Clear_Rect(x1,  yy, uOtherWidth+3,FontHeight,Bgcolor,regNum);
            x1 += uOtherWidth; //OTHER_FONT_WIDTH
#else
            if ((c == ' ') && (*(p - 1) != ' '))
            {
        if (pstTxtDis->uFontBase == MIDI_MENU_FONTDEBASE)   
		{     
			int wspace = uOtherWidth+3;
            if (((pstTxtDis->endXEdge - x1) < (uFontWidth))||((iRegionWidth - x1) < (uFontWidth)))
            wspace = pstTxtDis->endXEdge-x1;
            Osd_Clear_Rect(x1,  pstTxtDis->yy, wspace,FontHeight,Bgcolor,pstTxtDis->regNum);
			x1 += wspace-3; //OTHER_FONT_WIDTH
                    }else
		{
            Osd_Clear_Rect(x1,  pstTxtDis->yy, uOtherWidth+3,FontHeight,Bgcolor,pstTxtDis->regNum);
			x1 += uOtherWidth; //OTHER_FONT_WIDTH
		}
            }
#endif
        }
        p++;
    }
    osd_tog_region(pstTxtDis->regNum, OSD_ON);
    return x1;
}
#endif

/********************************************************
    //Function :  Disp_Text_OSD Display the lyric on screen by OSD
    //int xx :the x position
    //int yy :the y position
    //char *Lyric:  the string of lyric
    //BYTE regNum OSD Number
    //int margin: uint --> pixel
    //uFontBase:  the font database NO.
    //Note   :  The Font size is 40*48 color 16
 ********************************************************/
#ifdef MIDI_MULTIFONT_LIB
int Disp_Text_OSD(int xx, int yy, BYTE* Lyric, BYTE regNum, int margin,
    BYTE uFontBase, BYTE FontType,int endXEdge)
{
    BYTE langcode = SwLangLib(uFontBase);

    gs_stTestDisp.xx = xx;
    gs_stTestDisp.yy = yy;
    gs_stTestDisp.Lyric = Lyric; 
    gs_stTestDisp.regNum = regNum;
    gs_stTestDisp.margin = margin;
    gs_stTestDisp.FontType = FontType;
    gs_stTestDisp.endXEdge = endXEdge;
    //intf("disp lang code %d\n",langcode);
 //   printf("Disp_Text_OSD g_bIsExtFontEnable %d langcode %d\n",
   //             g_bIsExtFontEnable,langcode);
  //  print_block(Lyric,0x10);
    if ((g_bIsExtFontEnable)&&(langcode >= DEFAULT_EXTLANG))
    {
        return Disp_ExtraText_OSD(&gs_stTestDisp,//xx, yy, Lyric, regNum, margin,
                                (uFontBase&0x0f),langcode);//FontType,endXEdge
    }else
    {
        return DispBaseTextOsd(&gs_stTestDisp,(uFontBase&0x0f));
    }
}
#else
int Disp_Text_OSD(int xx, int yy, BYTE* Lyric, BYTE regNum, int margin,
    BYTE uFontBase, BYTE FontType,int endXEdge)
{
    int iRegionWidth = region[regNum].osd_w<<1; 
    BYTE* p = Lyric;
    UINT16 ch = 0;
    UINT16 x1, y1;
    UINT8 uFontWidth=0, uOtherWidth=0;
    BYTE Fontcolor=0, Bgcolor=0, FigureColor=0;  //,FontType
    BYTE* pabc_Width, * pABC_Width, * pNum_Width;
    BYTE FontHeight;
#ifdef SUPPORT_GB_FONTBASE3
    BYTE *gb3pos =0;
#endif
    if ((!endXEdge)||(endXEdge>(iRegionWidth -10)))
        endXEdge =iRegionWidth;
    //printf("Disp_Text_OSD %s\n",Lyric);
    pabc_Width = pABC_Width = pNum_Width = (void *)(0);
    if (uFontBase == MIDI_LYRIC_FONTDEBASE)
    {
        uFontWidth = LYRIC_FONT_WIDTH ; 
        uOtherWidth = OTHER_FONT_WIDTH;
        FontHeight =LYRIC_FONT_HIGHT;

        Fontcolor = LyricFontcolor;
        Bgcolor = LyricBgcolor;
        FigureColor = LyricFigureColor;
        pabc_Width = abc_width;
        pABC_Width = ABC_width;
        pNum_Width = num_width;
    }
    else if (uFontBase == MIDI_MENU_FONTDEBASE)
    {
        uFontWidth = MENU_FONT_WIDTH ; //LYRIC_FONT_WIDTH;
        uOtherWidth = MENU_OTHER_WIDTH;//OTHER_FONT_WIDTH;
        FontHeight =30;

        Fontcolor = MenuFontcolor;
        Bgcolor = MenuBgcolor;
        FigureColor = MenuFigureColor;

        pabc_Width = Menuabcwidth;
        pABC_Width = MenuABCwidth;
        pNum_Width = MenuNumwidth;
	endXEdge -=10;
    }else
    {
       // printf("error font base\n");
        return 0;
    }

    if (xx < 0)
        xx = 0;
    x1 = xx;
    y1 = yy;    
    while (*p == ' ')
        p++;

    //  osd_tog_region(regNum, OSD_ON);
    while (*p)
    {
        int iRes;
        BYTE c, c1;
        iRes = 0;
        c = *p;
        c1 = *(p + 1);
 #ifdef SUPPORT_GB_FONTBASE3
        
        if (((c  >= 0xA1 && c  < 0xD7 && c1 >= 0xA1 && c1 < 0xFF) ||
            (c  == 0xD7 && c1 >= 0xA1 && c1 < 0xFa))||
             (c  >= 0xD8 && c  < 0xF8 && c1 >= 0xA1 && c1 < 0xFF))
 #else
        if (c>0x80&&c1>0x80);
#endif
        {
            iRes = 2;
            p ++;
            if (iRegionWidth - x1 < 48) //
            {
                break;   //width is not enough break
        }
        }
 #ifdef SUPPORT_GB_FONTBASE3
        else if ((c > 0x80))//&&((c1>80)||(c1<80)))
        {
            UINT16 gbcode =(c<<8|c1);
            gb3pos =midi_GetGB3Font(gbcode,uFontBase);
            if (gb3pos)
                    {
                iRes = 3;
                p ++;
                if (iRegionWidth - x1 < 48) //
                    break;   //width is not enough break
            }else
            {
                //printf("search gb3base fail\n");
                p ++;
                iRes =0;
            }
        }    
#endif
        else if (((c >= 65) && (c <= 90)) ||     //A~Z
                 ((c >= 97) && (c <= 122)) ||    //a~z
                 ((c >= 192) && (c <= 223)) ||   //Europe characters
                 ((c >= 48) && (c <= 57)) || ((c >= 33) && (c <= 47)) //digit numbers //ouyang 2004.07.31
                 ||(c ==':')||(c == '\'')||(c =='.')||((c =='/')))   //xlluo add for english interpunction 2005-9-27 9:09
        {
            c1 = c + 0x80;
            c = 0x03 + 0xa0;
            iRes = 2;
        }
        else
        {
            switch (c)
            {
            case ' ':
                iRes = 1;
                break;
            default:
                iRes = 0;
                        break;
                    }    
                }

        if (iRes == 0)
            c = ' ';
        if (iRes == 2)
        {
            //          if (c!=0xa3)
            {
                if (((endXEdge - x1) < (uFontWidth))||((iRegionWidth - x1) < (uFontWidth)))  //LYRIC_FONT_WIDTH
                {
                    //xlluo add a mend here                 //2004-11-26
                        break;
                }
            }
            ch = (c << 8) | (c1);   
            osd_midi_DrawHZ_Mem(x1, y1, ch, Fontcolor, Bgcolor,
                FigureColor, FontType, regNum, uFontBase);  
            if (c == 0xa3)
            {
                int xtemp;
               if (c1 >= 0xe1 && c1 <= 0xfa)
                    x1 += pabc_Width[c1 - 0xe1];//+margin;
                else if ((c1 >= 0xc1) && (c1 <= 0xda))
                    x1 += pABC_Width[c1 - 0xc1];//+margin;
                else if ((c1 > 0xaf) && (c1 < 0xba))
                {
                    x1 += pNum_Width[c1 - 0xb0] + margin;
                }
                else
                {
                    x1 += uOtherWidth;  //OTHER_FONT_WIDTH
                }
            }
            else if (c < 0xa3)
            {
                x1 += uOtherWidth;  //xlluo add 2005-9-27 9:10 OTHER_FONT_WIDTH
            }
            else
            {
                x1 += (uFontWidth) + margin;        //LYRIC_FONT_WIDTH
            }
        }
 #ifdef SUPPORT_GB_FONTBASE3
        else if (iRes == 3)
        {
            {
                if (((endXEdge - x1) < (uFontWidth))||((iRegionWidth - x1) < (
uFontWidth)))  //LYRIC_FONT_WIDTH
                {
                    break;   //width is not enough break
                }
            }        
            draw_midi_bitmap_HZnew(gb3pos,x1, y1<<1, Fontcolor, Bgcolor,
FigureColor, FontType, regNum);
            x1 += (uFontWidth) + margin;        //LYRIC_FONT_WIDTH
        }    
#endif
        else
        {
            if (((endXEdge - x1) < (uOtherWidth))||((iRegionWidth - x1) < (
uOtherWidth)))  // LYRIC_FONT_WIDTH
                break;   //width is not enough break
#if 0 //def SUPPORT_SANJING_WIDESAPCE                //xlluo for sj space 04-
10-15
            Osd_Clear_Rect(x1,  yy, uOtherWidth+3,FontHeight,Bgcolor,regNum);
            x1 += uOtherWidth; //OTHER_FONT_WIDTH
#else
            if ((c == ' ') && (*(p - 1) != ' '))
            {
		if (uFontBase == MIDI_MENU_FONTDEBASE)   
		{     
			int wspace = uOtherWidth+3;
			if (((endXEdge - x1) < (uFontWidth))||((iRegionWidth - x1) < (uFontWidth)))
			wspace = endXEdge-x1;
			Osd_Clear_Rect(x1,  yy, wspace,FontHeight,Bgcolor,regNum);
			x1 += wspace-3; //OTHER_FONT_WIDTH
                    }else
		{
                Osd_Clear_Rect(x1,  yy, uOtherWidth+3,FontHeight,Bgcolor,regNum);
                x1 += uOtherWidth; //OTHER_FONT_WIDTH
            }
            }
#endif
        }
        p++;
    }
    osd_tog_region(regNum, OSD_ON);
    return x1;
}

#endif //Midi_MultiLang_LIB  

//*************************************************
//***clear the Rect region
// only for OSD_FORMAT_16COLOR 
//***int xx, int yy,:the position
//***int xlen, int ylen: the x&y length 
//***BYTE colour: the color that fill in the osd region
//***BYTE regNum:the region NO.
//*************************************************
void Osd_Clear_Rect(int xx, int yy, int xlen, int ylen, BYTE colour,
    BYTE regNum)
{
    BYTE* pTopLine, * pBtmLine, * pLine;
    BYTE colbyte;//bDispHalfByte;
    UINT32 iDispLoc;
    int i, j;
    int iRegionWidth = region[regNum].osd_w;

    if (p_scan ==1)
    {
        yy<<=1;
        ylen<<=1;
    }
    
    pTopLine = (BYTE *) (((BYTE *) get_osdbuf_baseptr()) +
        (region[regNum].osd_header[0] + OSD_DATA_OFFSET(region[regNum].osd_format)) * 32);
    pBtmLine = (BYTE *)(((BYTE *) get_osdbuf_baseptr()) +
        (region[regNum].osd_header[1] + OSD_DATA_OFFSET(region[regNum].osd_format)) * 32);

    iDispLoc = (((yy - ((yy) & 0x01)) * iRegionWidth ) + (xx))>>1;

    colbyte =(BYTE)(((colour & 0x0f) << 4) | (colour & 0x0f));
    for (j = 0; j < ylen; j++)
    {
        if ((j + yy) & 0x01)
            pLine = pBtmLine;
        else
            pLine = pTopLine;
        for (i = 0; i < xlen; i++) //print one point per time
        {
           if (i & 0x01)
            {
                pLine[iDispLoc + (i >> 1)] = colbyte;//&0x0f;
            }
        }
        if ((j + yy) & 0x01)
            iDispLoc += iRegionWidth;
    }
}


/*******************************
    // clear a line of lyric 
    //BYTE Ystart :clear line y position
    //BYTE regNum OSD Number
    //
    //for height = 40
    //support the 16 color
********************************/
void ClearOSDStrLine(UINT16 fwidth, UINT16 Xstart, UINT16 Ystart, BYTE regNum)
{
    Osd_Clear_Rect(Xstart,Ystart,fwidth,(LYRIC_FONT_HIGHT),0,regNum);
}



/*******************************************
//draw vertline and the font bitmap  reverse video
//int xx :the x position
//int yy :the y position
//short height :font hight
//BYTE columns :pels num for rev
//only for the 16 colors
********************************************/
void Disp_one_vertline(int xx, int yy, UINT16 height, UINT16 columns,
    BYTE regNum)
{
    int i, j, k;
    BYTE* pTopLine, * pBtmLine, * pLine;
    UINT32 iDispLoc, uiDispHalfByte,bDispHalfByte;
    int iRegionWidth = region[regNum].osd_w;
    UINT16 high = height;
    UINT16 width = columns;

    pTopLine = (BYTE *)((BYTE *) get_osdbuf_baseptr() +
        region[regNum].osd_header[0] * 32 +
        OSD_DATA_OFFSET(region[regNum].osd_format) * 32);
    pBtmLine = (BYTE *)((BYTE *) get_osdbuf_baseptr() +
        region[regNum].osd_header[1] * 32 +
        OSD_DATA_OFFSET(region[regNum].osd_format) * 32);

    if (p_scan ==1)
    {    
        yy<<=1;
    }
    uiDispHalfByte = (((yy) * iRegionWidth) + (xx));
    iDispLoc = (((yy - ((yy) & 0x01)) * iRegionWidth) + (xx)) >> 1;

    for (i = 0; i < high; i++)
    {
        if ((i + yy) & 0x01)
            pLine = pBtmLine;
        else
            pLine = pTopLine;
        bDispHalfByte = (uiDispHalfByte) & 0x01;

        for (j = 0; j < width; j++)
        {
            k = (((xx) & 0x01) + j) >> 1;
            bDispHalfByte ^= 1;
            if (bDispHalfByte == 0)
            {
                if ((pLine[k + iDispLoc] & 0x0f) == LyricFigureColor) 
                    pLine[k + iDispLoc] = (pLine[k + iDispLoc] & 0xf0) |
                        LyricFontcolor; 
                else if ((pLine[k + iDispLoc] & 0x0f) == LyricFontcolor)
                    pLine[k + iDispLoc] = (pLine[k + iDispLoc] & 0xf0) |
                        LyricRevcolour;
            }
            else
            {
                if ((pLine[k + iDispLoc] & 0xf0) == (LyricFigureColor << 4)) 
                    pLine[k + iDispLoc] = (pLine[k + iDispLoc] & 0x0f) |
                        (LyricFontcolor << 4); 
                else if ((pLine[k + iDispLoc] & 0xf0) == (LyricFontcolor << 4))
                    pLine[k + iDispLoc] = (pLine[k + iDispLoc] & 0x0f) |
                        (LyricRevcolour << 4);
            }
        }
        if (((i + yy) & 0x01)||(p_scan ==1))
            iDispLoc += iRegionWidth;
    }
    osd_tog_region(REGION3, OSD_ON);
}



void osd_Clear_Region(BYTE reg, BYTE bkColor)
{
    Osd_Clear_Rect(0,0,region[reg].osd_w<<1,region[reg].osd_h,bkColor,reg);
}


#ifdef MIDI_MULTI_MENU
//***************************//
//updown == 0,display °¼//
//updown == 1,display Í¹//
//updown > 1 ,normal display//
//**************************//
#define ARC_REGION_COLOUR_GROUND    (0)
#define ARC_REGION_COLOUR_FOUNT       (13)
#define ARC_REGION_COLOUR_EDGE         (13)

void midi_menu_draw_arc_region(int xStart, int yStart, int xLen, int yLen,
    BYTE regNum, BYTE Enable)
{
    BYTE* pTopLine, * pBtmLine, * pLine, radius;
    UINT32 iDispLoc;
    int i, j;
    int Region;
    int iRegionWidth = region[regNum].osd_w;
    BYTE cground, cfount, cedge, curColour, cfount1;

    cground = cfount = cedge = curColour = cfount1 =0;
    Region = regNum;

    if (p_scan ==1)
    {
        yStart<<=1;
        yLen<<=1;
    }
    
    pTopLine = (BYTE *)
        (((BYTE *) get_osdbuf_baseptr()) +
        (region[regNum].osd_header[0] + OSD_DATA_OFFSET(region[regNum].osd_format)) * 32);
    pBtmLine = (BYTE *)
        (((BYTE *) get_osdbuf_baseptr()) +
        (region[regNum].osd_header[1] + OSD_DATA_OFFSET(region[regNum].osd_format)) * 32);

    radius = sizeof(arc_tableLT[0]);
    //    printf("RADIUS ==%d\n",radius);

    iDispLoc = ((yStart - ((yStart) & 0x01)) * iRegionWidth / 2) +
        (xStart / 2);
    if (Enable)
    {
        cground = ARC_REGION_COLOUR_GROUND;
        cfount = ARC_REGION_COLOUR_FOUNT;
        cfount1 = 0x2;
        cedge = ARC_REGION_COLOUR_EDGE;
    }
    for (j = 0; j < yLen; j++)
    {
        if ((j + yStart) & 0x01)
            pLine = pBtmLine;
        else
            pLine = pTopLine;

        if (Enable)
        {
            for (i = 0; i < xLen; i++) //print one point per time
            {
                if ((i < radius) && (j < radius))//draw left-top corner
                {
                    if ((arc_tableLT[j][i] == 0))
                        curColour = cground;
                    else if ((arc_tableLT[j][i] == 1))
                        curColour = cedge;
                    else if ((arc_tableLT[j][i] == 2))
                        curColour = cfount;
                    else if ((arc_tableLT[j][i] == 3))
                        curColour = cfount1;
                }
                else if ((i >= xLen - radius) && (j < radius))//draw right-top corner
                {
                    if ((arc_tableRT[j][i - xLen + radius] == 0))
                        curColour = cground;
                    else if ((arc_tableRT[j][i - xLen + radius] == 1))
                        curColour = cedge;
                    else if ((arc_tableRT[j][i - xLen + radius] == 2))
                        curColour = cfount;
                }
                else if ((i < radius) && (j >= yLen - radius))//draw left-bottom corner
                {
                    if ((arc_tableLB[j - yLen + radius][i] == 0))
                        curColour = cground;
                    else if ((arc_tableLB[j - yLen + radius][i] == 1))
                        curColour = cedge;
                    else if ((arc_tableLB[j - yLen + radius][i] == 2))
                        curColour = cfount;
                }
                else if ((j >= yLen - radius) && (i >= xLen - radius))//draw right-bottom corner
                {
                    if (arc_tableRB[j - yLen + radius][i - xLen + radius] == 0)
                        curColour = cground;
                    else if (arc_tableRB[j - yLen + radius][i - xLen + radius] ==
                        1)
                        curColour = cedge;
                    else if (arc_tableRB[j - yLen + radius][i - xLen + radius] ==
                        2)
                        curColour = cfount;
                }
                else
                    curColour = cfount;//cfount;
                if (i & 0x01)
                {
                    pLine[iDispLoc + (i >> 1)] |= curColour & 0x0f;
                }
                else
                {
                    pLine[iDispLoc + (i >> 1)] |= (curColour << 4) & 0xf0;
                }
            }
        }
        else
        {
            for (i = 0; i < xLen; i++) //print one point per time
            {
                pLine[iDispLoc + (i >> 1)] = 0;
            }
        }
        if ((j + yStart) & 0x01)
            iDispLoc += iRegionWidth;
    }

    //    timeout_osd[Region] = 0;
    osd_tog_region(Region, OSD_ON);
}


void Midi_Draw_Rect(int xx, int yy, UINT16 xLen, UINT16 yLen, BYTE BgColor,
    BYTE FrontC, BYTE FigC, BYTE regNum)
{
    int i, j, k;
    BYTE* pTopLine, * pBtmLine, * pLine;
    UINT32 iDispLoc, uiDispHalfByte;
    int iRegionWidth = region[regNum].osd_w;
    UINT16 high = yLen;
    UINT16 width = xLen;

    if (p_scan ==1)
    {
        yy<<=1;
        yLen<<=1;
    }

    pTopLine = (BYTE *)
        ((BYTE *) get_osdbuf_baseptr() +
        region[regNum].osd_header[0] * 32 +
        OSD_DATA_OFFSET(region[regNum].osd_format) * 32);
    pBtmLine = (BYTE *)
        ((BYTE *) get_osdbuf_baseptr() +
        region[regNum].osd_header[1] * 32 +
        OSD_DATA_OFFSET(region[regNum].osd_format) * 32);
    uiDispHalfByte = (((yy - ((yy) & 0x01)) * iRegionWidth) + (xx));
    iDispLoc = (uiDispHalfByte) >> 1;

    for (i = 0; i < high; i++)
    {
        if (((i + yy) & 0x01)||(p_scan ==1))
            pLine = pBtmLine;
        else
            pLine = pTopLine;
        uiDispHalfByte = (xx) & 0x01;

        for (j = 0; j < width; j++)
        {
            k = (((xx) & 0x01) + j) >> 1;
            uiDispHalfByte ^= 1;
            if (uiDispHalfByte == 1)
            {
                if ((pLine[k + iDispLoc] & 0x0f) == MENU_BACKGROUND_COLOR)
                    pLine[k + iDispLoc] = (pLine[k + iDispLoc] & 0xf0) |
                        BgColor;
                else if ((pLine[k + iDispLoc] & 0x0f) == MENU_LINE_COLOR)
                    pLine[k + iDispLoc] = (pLine[k + iDispLoc] & 0xf0) |
                        BgColor;
            }
            else
            {
                if ((pLine[k + iDispLoc] & 0xf0) == (MENU_BACKGROUND_COLOR << 4))
                    pLine[k + iDispLoc] = (pLine[k + iDispLoc] & 0x0f) |
                        (BgColor << 4);
                else if ((pLine[k + iDispLoc] & 0xf0) == (MENU_LINE_COLOR << 4))
                    pLine[k + iDispLoc] = (pLine[k + iDispLoc] & 0x0f) |
                        (BgColor << 4);
            }
        }
        if (((i + yy) & 0x01)||(p_scan ==1))
            iDispLoc += iRegionWidth;
    }
    osd_tog_region(regNum, OSD_ON);
}

#endif  //end #ifdef MIDI_MULTI_MENU

#endif  //end #ifdef SUPPORT_OSDLYRIC

//xlluo 04-6-14
#ifdef   SUPPORT_SCANMODE_SWITCH
void MIDI_MoveRegion(BYTE r,UINT16 x,UINT16 y,UINT16 h,UINT16 w)
{
    UINT16* pOSDHeader1 = (UINT16*)(get_osdbuf_baseptr() + region[r].osd_header[0] * 32);
    UINT16* pOSDHeader2 = (UINT16*)(get_osdbuf_baseptr() + region[r].osd_header[1] * 32);   
    UINT16 nCol, nRow;
    UINT16 nHig,nWid;

 if (p_scan)//ouyang 20040930
    {
       y<<=1;
       h<<=2;
    }
    
    nRow = y & 0x3ff; 
    nCol = x & 0x3ff;
    nHig = h&0x3ff;
    nWid =w&0x3ff;

    wbe16(pOSDHeader1 + 4, nRow);
    wbe16(pOSDHeader2 + 4, nRow);
    wbe16(pOSDHeader1 + 5, nCol);
    wbe16(pOSDHeader2 + 5, nCol);
    
  /*  wbe16(pOSDHeader1 + 2, nHig);
    wbe16(pOSDHeader2 + 2, nHig);
    wbe16(pOSDHeader1 + 3, nWid);
    wbe16(pOSDHeader2 + 3, nWid);*/

}

//xlluo add for clean the sysmesssage
void CleanSysMessage(BYTE regnum)
{
    printf("CleanSysMessage \n");
     osd_tog_region(regnum,OSD_OFF);
     
     memset(osdbuf,0,sizeof(osdbuf));
     memset(osd_buf,0,sizeof(osd_buf));
     memset(RegionValStr[regnum],0,14);
}
#endif


