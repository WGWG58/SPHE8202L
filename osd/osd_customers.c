

//Note: Collect all osd customized-functions
//Note: please inculde "osd_customers.h" to use these functions


#include "config.h"
#include "regmap.h"
#include "global.h"

#include "osd_api.h"
#include "osd_palette.h"


#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)    //axel 2004/1/27 04:48
#include "icon_bbk.h"
#endif


//////////////////////////////////////////////////////
#if defined(LARGE_SCORES_DISPLAY)//&&defined(GBM_DVD)//wuxiaofeng copy the code from the rear 02-23
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
#ifdef	OSD_SUPPORT_256_COLOR
    case OSD_FORMAT_256COLOR:
        Bperpixel = 0; // 1
        shift_num = 8;
        break;
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
    //osd_tog_region(number, OSD_ON);
}
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

 //   iDispLoc = (yy ) * iRegionWidth  + xx;
//    bDispHalfByte = iDispLoc & 0x01;
//    xlen += bDispHalfByte;
    iDispLoc = (((yy - ((yy) & 0x01)) * iRegionWidth ) + (xx))>>1;

    colbyte =  (((colour & 0x0f) << 4) | (colour & 0x0f));
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
void osd_Clear_Region(BYTE reg, BYTE bkColor)
{
    Osd_Clear_Rect(0,0,region[reg].osd_w<<1,region[reg].osd_h,bkColor,reg);
}
#endif//#if defined(LARGE_SCORES_DISPLAY)&&defined(GBM_DVD)//wuxiaofeng copy the code from the rear 02-23

//////////////////////////////////////////////////////
#ifdef TONIC_DVD
void draw_osd_board_pscan(UINT8 r, UINT8 board_type)
{
    int     i;
    int     w=region[r].osd_w;
    int     h=region[r].osd_h;
    BYTE    *pTopLine,*pBtmLine;
    pTopLine = get_osdbuf_region_ptr(r,0);
    pBtmLine = get_osdbuf_region_ptr(r,1);
    if(p_scan==0) h>>=1;    
    if(board_type&BOARD_UP_LINE)
    {                   
        for (i=0;i<w;i++) 
        {
                pTopLine[i] =  0xff;
                pBtmLine[i] =  0xff;                   
        }
    }
    if(board_type&BOARD_DOWN_LINE)
    {   
        if (r!=1)
        {
            for (i=(h-1)*w;i<(h*w);i++) 
            {
                    pTopLine[i] =  0xff;
                    pBtmLine[i] =  0xff;                   
            }
        }
    }
    if(board_type&BOARD_LEFT_LINE)
    {   
        for(i=0;i<(h*w);i+=w) 
        {
            pTopLine[i] =  0xff;
            pBtmLine[i] =  0xff;                   
        }
    }
    if(board_type&BOARD_RIGHT_LINE)
    {   
        for(i=w-1;i<(h*w);i+=w) 
        {
            pTopLine[i] =  0xff;
            pBtmLine[i] =  0xff;                   
        }
    }
    //board_type=0;
}
void OsdShowPscan(BYTE onoff)
{
        SetOsdCol(3,7,0, __palette4F(  10, 10, 10,0xff));          
        SetOsdCol(3,7,1, __palette4F(  10, 10, 10,0xff));                               
        draw_osd_board_pscan(3,BOARD_UP_LINE);
        draw_osd_board_pscan(3,BOARD_RIGHT_LINE);
        draw_osd_board_pscan(3,BOARD_LEFT_LINE);     
        if(onoff==0)
        osd_print_region2(&region[4]," P.SCAN SWITCH OFF",0,0);       
        else
        osd_print_region2(&region[4]," P.SCAN SWITCH ON",0,0);       
        draw_osd_board_pscan(4,BOARD_LEFT_LINE); 
        draw_osd_board_pscan(4,BOARD_RIGHT_LINE);    
        osd_print_region2(&region[5]," RESTART PLAYER FOR THE",0,0);       
        draw_osd_board_pscan(5,BOARD_LEFT_LINE); 
        draw_osd_board_pscan(5,BOARD_RIGHT_LINE);
        osd_print_region2(&region[6]," CHANGE TO BE EFFECTIVE",0,0);       
        draw_osd_board_pscan(6,BOARD_LEFT_LINE); 
        draw_osd_board_pscan(6,BOARD_RIGHT_LINE);
        draw_osd_board_pscan(7,BOARD_DOWN_LINE);
        draw_osd_board_pscan(7,BOARD_RIGHT_LINE);
        draw_osd_board_pscan(7,BOARD_LEFT_LINE);                            
        osd_tog_region(3,OSD_ON);   
        osd_tog_region(4,OSD_ON);                   
        osd_tog_region(5,OSD_ON);   
        osd_tog_region(6,OSD_ON);   
        osd_tog_region(7,OSD_ON);           
}
#endif//#ifdef TONIC_DVD

//////////////////////////////////////////////////////
//fengjl add for bbk's new setup 3-11-10 16:57
#if defined(BBK_NEW_SETUP)&&defined(BBK_DV961_DVD)       
void osd_init_bbk_setup(void)  
{   
    #define SETUP_HL_COLOR      5
    
    osd_puts("osd_init_setup\n");
    __osd_init();    
   
    header_id =SETUP_HEADER;
    region[1].osd_w = 32*8;                  //33 English Characters
    region[1].osd_h = 6*SETUP_BTN_HEIGHT;   //6 lines

    osd_create_region1(&region[1], 53, 4*SETUP_BTN_HEIGHT-9, NULL, OSD_FORMAT_16COLOR, OSD_INTERLACED);
    //SetOsdCol(1,1,0,0x1e1e1ef0);//black zhaoyanhua add 2003-12-2 14:21 
     SetOsdCol(1,1,0,0x757575f0);
    SetOsdCol(1,1,SETUP_HL_COLOR,0xa346ffff);
    //SetOsdCol(1,1,0,0x1e1e1ecd);//Initial color index is 0,but not transparent. zhaoyanhua 3-7-11 13:41
 
#ifdef OSD_SUPPORT_256_COLOR   
    header_id =BBK_SETUP_256HEADER;
    region[0].osd_w = 32*16;                  //33 English Characters
    region[0].osd_h = 5*SETUP_BTN_HEIGHT;   //6 lines
    osd_create_region1(&region[0], 53, 1*SETUP_BTN_HEIGHT+10, &region[1], OSD_FORMAT_256COLOR, OSD_INTERLACED);
    //SetOsdCol(0,0,0,0x1e1e1ecd);
    SetOsdCol(0,0,0,0x757575f0);// black zhaoyanhua add 2003-12-2 14:20
#endif	// #ifdef OSD_SUPPORT_256_COLOR

    osd_active_regions = 2;
    ENABLE_OSD(); 
    osd_init__();    
    
    osd_draw_icon_bbk(4,20,0);
    osd_draw_icon_bbk(68,23,1);         
}
void osd_draw_icon_bbk(int xStart, int yStart,int index)
{
    BYTE    *icon_bbk;
    UINT32  *pTopLine, *pBtmLine;
    UINT32  iDispLoc, iIconLoc;
    int     need_gray=0;

    int     i, j, k;
    int     iFontWidth, iFontHigh;
    int     iRegionWidth = region[0].osd_w;

    osd_tog_region(0, OSD_ON);  
    
    //initialize buffer start
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(0,0);   // region 0 top
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(0,1);   // region 0 bot

    iIconLoc = 0;
    
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    yStart+=2;
     
    {
        UINT32 pixel4;
        UINT32 pos;
        
        iIconLoc++;        
        icon_bbk = Pic_table[index];
       // icon_bbk = get_font_entry(2, index);

        //start to process
        pos = 2;
        
        //get icon information
                
        iFontWidth  =(int) icon_bbk[0];
        iFontHigh   = (int)icon_bbk[1];
               
        for (j=0; j<iFontHigh; j++) 
        {
            int yy;
            UINT32 *pp;
            yy = (p_scan) ? yStart : yStart>>1;
            pp = (yStart&1) ? pBtmLine : pTopLine;
            
            iDispLoc = (yy*iRegionWidth*2/8) + (xStart);
            for (i=0; i<(iFontWidth/4); i++) // every 4-bytes a time, every 1-pixels a byte
            {
                pixel4=0; 
               
                for (k=0;k<4;k++)
                {                    
                    unsigned curByte = icon_bbk[++pos];
                 
                    pixel4 = pixel4 | (curByte<<8*k);    
                }
                pp[iDispLoc+i] =  pixel4;
            }
            yStart++;
        }//for icon heigh  
    }

    timeout_osd[0] = 0;
}
#endif  // end bbk's new setup

//////////////////////////////////////////////////////
#ifdef ROLL_SHOW_SETUP

#include"memmap0.h"
extern int GBM_run_setupmenu_flag;

/****************************************
FUNC:  similar to osd_draw_hline_region();
       difference: write button data to BUFFER not 
                    to SCREEN
        
Creator :zhaoyanhua 
Date:    2003-8-15 15:49
****************************************/
void MoveRect2buf(int xStart, int xEnd, int yStart, unsigned color, int yLen, int r)
{
    UINT8   *buf;
    int  i, j;
    //UINT8   *pTopLine, *pBtmLine;
    int     iRegionWidth  = region[r].osd_w;
    int     iRegionHeight = region[r].osd_h;
    UINT32   iDispLoc = 0;  
    
    
     buf = (UINT8 *)(SDRAM_BASE + P_BIDIR_LUMA*1024 + yStart*iRegionWidth );
    // setup color pixel (only support 16-color here)
    color &= 0x0f;
    //ButtonC = (color | (color<<4) | (color<<8) |color<<12)| (color<<16)|(color<<20) |(color<<24) | (color<<28));
    color =(color | (color<<4));
    
    for (j = 0; j < yLen; j++ )
    { 
        iDispLoc = j * iRegionWidth  ;
        for (i = xStart/2; i< (xEnd/2); i++) //draw one line
            buf[iDispLoc + i]= color;
    }
     
}

/***************************************
FUNC: 
      write string data to BUFFER not to SCREEN

Creator: zhaoyanhua 
Date: 2003-8-18 11:46
****************************************/
void MoveString2Buf(BYTE xStart, BYTE yStart,BYTE * str, BYTE fontColor, BYTE bkColor)
{
    BYTE    c;
    BYTE    *pFont;
    UINT32  *pTopLine, *pBtmLine;
    int     cc;
    UINT32  iStrLoc;
    int     iRegionWidth;
    UINT32  *buf;

    cc = xStart*16;//pixels.
    iRegionWidth = region[SETUP_REGION].osd_w;

    // initialize buffer start
    //pTopLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION, 0);
    //pBtmLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION, 1);
     buf= (UINT32 *)(SDRAM_BASE + P_BIDIR_LUMA*1024 + (yStart*SETUP_BTN_HEIGHT+4)*iRegionWidth+ xStart);     

    //process each charactor until string ending('\0')
    iStrLoc = 0;
    while ((c = ((BYTE *)str)[iStrLoc]) != '\0')
    {
        int     i, j, k;
        int     iFontWidth, iFontHigh;
        UINT32  pos;
        
        
        iStrLoc++;
        
        if (c == '\r') {                    //prefix characher: to use font_table2
            if ( (c = ((BYTE *)str)[iStrLoc])=='\0' ) break;
            iStrLoc++;
            if ((pFont = get_font_entry(1,c))==NULL) continue;
        } else {
            //get current char entry
            pFont = get_font_entry(0,c);
        }
        
        //start to process
        pos = 2;
        
        //get font information
        iFontWidth = (int)pFont[0];
        iFontHigh  = (int)pFont[1];
        
        //start this character
        for (j=0; j<iFontHigh; j++) {
            UINT32 *pp;
            int     yy;
            int     iDispLoc;

            yy  = j;
            iDispLoc = yy*(iRegionWidth/4) + (cc/8);
            
            //draw top line
            for (i=0; i<iFontWidth/8; i++) {
                unsigned pat;
                unsigned curByte;
                UINT32 pixel8;
                
                pat = pFont[++pos];
                curByte = ((pat&0xc0)>>6) | ((pat&0x30)>>2) | ((pat&0x0c)<<2) | ((pat&0x03)<<6);
                pixel8 = 0;
                for (k=0; k<8; k++) {       // for every-bit of pattern
                    if ( (1<<k) & curByte ) {          
                        pixel8 = pixel8 | (fontColor<<(k*4));
                    } else {
                        pixel8 = pixel8 | (bkColor<<(k*4));
                    }
                }
              //pp[iDispLoc+i] = pixel8;
               buf[iDispLoc+i] = pixel8;
            }
        }
        cc+=iFontWidth; 
    }
    
    timeout_osd[SETUP_REGION] = 0;
    osd_tog_region(SETUP_REGION, OSD_ON);   
}


extern BYTE setupItemNum[3];
//
// Bytes/Line = 37*16*4/8 = 296
//
/****************************************
FUNC:  
        draw the data to the SCREEN from 
        BUFFER
        
        BUF: P_BIDIR_LUMA

        EFFECT MODE: h_window .
    INPUT: 
        xStart:
        xEnd  :  unit is char.
        
Creator :zhaoyanhua 
Date:    2003-8-18 11:51        
*****************************************/
void MoveBuf2OSD(UINT16 xStart, UINT16 xEnd)
{
    UINT32  *buf;
    UINT32  *pTopLine, *pBtmLine;
    BYTE    i,step;
    UINT32  j, k;   
    UINT16  ButtonHight;//one BUTTON HIGHT.
    
    osd_tog_region(SETUP_REGION, OSD_ON);  


    buf = (UINT32 *)(SDRAM_BASE + P_BIDIR_LUMA*1024 );    
    //buf = (UINT32 *)(osd_temp_buf);
    
    //initialize buffer start    
    pTopLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION,0);
    pBtmLine = (UINT32 *)get_osdbuf_region_ptr(SETUP_REGION,1);

    //end=iLine;
    ButtonHight = 32;
    step=1;
    if(p_scan==0)
    {
       
       ButtonHight = 16;
       step=2;
    }
    else
    {
        ButtonHight = 32;
        step=1;
        
    }
    #if 0 //2 BUTTON cocurrently display.
    int m;
    printf("setupItemNum=%d\n",setupItemNum[1]);
    for (i = 0; i<ButtonHight; i++)//for (i = 0; i<32/2; i++)
    {
        delay_1ms(10);
        for (m =0; m < (setupItemNum[1]-1); m+=2)  
        {
           //NOTE:  
           //      xStart*16        : pixels
           //      xStart*16*4      : bits, one pixel 4 bits.
           //      (xStart*16*4)/8  : bytes.
           //      ((xStart*16*4)/8)/4  : bytes. unit is 4 BYTES.   
            for(j = ((xStart*16*4)/8)/4; j < ((xEnd*16*4)/8)/4; j++)//for(j = ((12)*16*4)/(8*4) ; j < ((12)*16*4)/(8*4)+((15)*16*4)/(8*4) ;j++)
            {// for (j=0; j<76; j++) {
       
               k = step * (m*ButtonHight +i);
               //top area
               pTopLine[76*(m*ButtonHight +i)+j] = buf[76*k + j];
               //bottom area
               pBtmLine[76*(m*ButtonHight +i)+j] = buf[76*(k+1) + j];            
            
            }            
        }
    }
    #endif
    
    #if 1 //1 BUTTON
    int m;
       //printf("setupItemNum=%d\n",setupItemNum[1]);
    
    for (i = 0; i<ButtonHight; i++)//for (i = 0; i<32/2; i++)
    {
        delay_1ms(15);
        for (m =0; m < (setupItemNum[1]-1); m++)  
        {
            //NOTE:  
           //      xStart*16        : pixels
           //      xStart*16*4      : bits, one pixel 4 bits.
           //      (xStart*16*4)/8  : bytes.
           //      ((xStart*16*4)/8)/4  : bytes. unit is 4 BYTES.   
            for(j = ((xStart*16*4)/8)/4; j < ((xEnd*16*4)/8)/4; j++)//for(j = ((12)*16*4)/(8*4) ; j < ((12)*16*4)/(8*4)+((15)*16*4)/(8*4) ;j++)
            {// for (j=0; j<76; j++) 
                k = step * (m*ButtonHight +i);
               //top area
                pTopLine[76*(m*ButtonHight +i)+j] = buf[76*k + j];
                //bottom area
                pBtmLine[76*(m*ButtonHight +i)+j] = buf[76*(k+1) + j];            
            
            }            
        }
    }
    #endif

    
    #if 0//Roll display
    for (i=iStartLine; i<iEndLine; i++) 
    {
       // k = 24-iLine+step*i;
        k = step*i;
        //NOTE:  
           //      xStart*16        : pixels
           //      xStart*16*4      : bits, one pixel 4 bits.
           //      (xStart*16*4)/8  : bytes.
           //      ((xStart*16*4)/8)/4  : bytes. unit is 4 BYTES.   
        for(j = ((xStart*16*4)/8)/4; j < ((xEnd*16*4)/8)/4; j++)
        {// for (j=0; j<76; j++) {
            //top area
            pTopLine[76*i+j] = buf[76*k + j];
            //bottom area
            pBtmLine[76*i+j] = buf[76*(k+1) + j];
            
        }
    }
   #endif
    
    
}

void
osd_draw_button_outline(int x1, int y1, int x2, int y2, int bDown, unsigned mask, int r)
{
    unsigned    uBorderC, xBorderC, dBorderC;

    if (bDown) {
        //button is pressed (down)
        uBorderC = C16_BLACK;       // upper border color
        xBorderC = C16_LIGHTGRAY;
        dBorderC = C16_WHITE;       // rear border color
    } else {
        //button is not-pressed (up)
        uBorderC = C16_WHITE;
        xBorderC = C16_LIGHTGRAY;
        dBorderC = C16_BLACK;
    }
    
    if ((!GBM_run_setupmenu_flag) && !(full_scrn&CUSTM) && !(full_scrn&SOUND))      //gerry modified 3D_SOUND,2004-4-12 13:35
    {
        if (mask & (1<<3)) 
        {
            //draw upper border
            MoveRect2buf(x1+0,x2-0,y1+0,xBorderC,1,r);
            MoveRect2buf(x1+1,x2-1,y1+1,uBorderC,1,r);
            MoveRect2buf(x1+2,x2-2,y1+2,uBorderC,1,r);
            MoveRect2buf(x1+3,x2-3,y1+3,xBorderC,1,r);
        }
    
        if (mask & (1<<2)) 
        {
            //draw rear border
            MoveRect2buf(x1+3,x2-3,y2-3,xBorderC,1,r);
            MoveRect2buf(x1+2,x2-2,y2-2,dBorderC,1,r);
            MoveRect2buf(x1+1,x2-1,y2-1,dBorderC,1,r);
            MoveRect2buf(x1+0,x2-0,y2-0,xBorderC,1,r);
        }
    
        //draw left border
        if (mask & (1<<1)) {
            MoveRect2buf(x1+0, y1+0, y2-0, xBorderC, 1, r);
            MoveRect2buf(x1+1, y1+1, y2-1, uBorderC, 1, r);
            MoveRect2buf(x1+2, y1+2, y2-2, uBorderC, 1, r);
            MoveRect2buf(x1+3, y1+3, y2-3, xBorderC, 1, r);
        }

        //draw right border
        if (mask & (1<<0)) {
            MoveRect2buf(x2-0, y1+0, y2-0, xBorderC, 1, r);
            MoveRect2buf(x2-1, y1+1, y2-1, dBorderC, 1, r);
            MoveRect2buf(x2-2, y1+2, y2-2, dBorderC, 1, r);
            MoveRect2buf(x2-3, y1+3, y2-3, xBorderC, 1, r);
        }
    }
    else
    {
        if (mask & (1<<3)) 
        {
        //draw upper border
        osd_draw_hline_region(x1+0,x2-0,y1+0,xBorderC,1,r);
        osd_draw_hline_region(x1+1,x2-1,y1+1,uBorderC,1,r);
        osd_draw_hline_region(x1+2,x2-2,y1+2,uBorderC,1,r);
        osd_draw_hline_region(x1+3,x2-3,y1+3,xBorderC,1,r);
    }
    
        if (mask & (1<<2)) 
        {
            //draw rear border
            osd_draw_hline_region(x1+3,x2-3,y2-3,xBorderC,1,r);
            osd_draw_hline_region(x1+2,x2-2,y2-2,dBorderC,1,r);
            osd_draw_hline_region(x1+1,x2-1,y2-1,dBorderC,1,r);
            osd_draw_hline_region(x1+0,x2-0,y2-0,xBorderC,1,r);
        }
    
        //draw left border
        if (mask & (1<<1)) {
            osd_draw_vline_region(x1+0, y1+0, y2-0, xBorderC, 1, r);
            osd_draw_vline_region(x1+1, y1+1, y2-1, uBorderC, 1, r);
            osd_draw_vline_region(x1+2, y1+2, y2-2, uBorderC, 1, r);
            osd_draw_vline_region(x1+3, y1+3, y2-3, xBorderC, 1, r);
        }

        //draw right border
        if (mask & (1<<0)) {
            osd_draw_vline_region(x2-0, y1+0, y2-0, xBorderC, 1, r);
            osd_draw_vline_region(x2-1, y1+1, y2-1, dBorderC, 1, r);
            osd_draw_vline_region(x2-2, y1+2, y2-2, dBorderC, 1, r);
            osd_draw_vline_region(x2-3, y1+3, y2-3, xBorderC, 1, r);
        }
    }
}

#endif  //#ifdef ROLL_SHOW_SETUP

//////////////////////////////////////////////////////

//////////////////////////////////////////////////////
#ifdef SUPPORT_REP_READ //Maoyong 2004.06.03
void osd_draw_read_button(BYTE xStart, BYTE yStart, BYTE xLen, BYTE color, BYTE bDown)
{
    BYTE        buttonC;
    UINT32      xNew, yNew;    
    
    buttonC = color;    
    xNew = xStart * 16;
    yNew = yStart * SETUP_BTN_HEIGHT + 8;    
    osd_draw_region_rect(xNew, yNew, (UINT32)(xLen*16), (UINT32)(SETUP_BTN_HEIGHT), buttonC,READ_REGION);    
    
    start.x = xNew;
	start.y = yNew;
	end.x = (UINT16)(xNew+xLen*16);
	end.y = (UINT16)(yNew+SETUP_BTN_HEIGHT-2);
	osd_draw_button_outline(&start, &end, bDown,0x0f,READ_REGION);
        
    //osd_draw_region_boarder(xNew,yNew,(UINT32)(xNew+xLen*16),(UINT32)(yNew+SETUP_BTN_HEIGHT-2),bDown,READ_REGION);
}
#endif
//////////////////////////////////////////////////////

//////////////////////////////////////////////////////


