/*
 * FileName:       osd_SFM.c
 * Author:         ChenZhao  Version:    Date: 2004-9-20
 * Description:    osd fucntions added and modified for SOFT_MENU
 * Version:        
 * Function List:  
 *                 osd_changeAlpha
 *                 osd_interlace
 *                 osd_DrawSlantCorner
 *                 osd_DrawIcon_Trans
 *                 osd_draw_roundcorner
 *                 osd_StringDrawLength
 *                 osd_DrawString_ori
 * History:        
 *     <author>   <time>    <version >   <desc>
 */
void osd_changeAlpha(UINT32 a)
{
	UINT16 i;
	for(i=0;i<16;i++)
		SetOsdCol(SETUP_REGION,SETUP_REGION,i,palette_16color_setup[i]|a);
}
#ifdef TEST_INTERLACE//Modifed by ChenZhao on 2004-9-20 11:39  
void osd_interlace(int x,int y,BYTE direct,BYTE fontColor,BYTE bkColor)
{
    UINT8	*pTopLine, *pBtmLine;
    int     iRegionWidth= region[SETUP_REGION].osd_w;
	int     j,k;
	BYTE	*pp;
	BYTE	ct0,ct1,c;
	if(direct)
		{
		ct0=(fontColor<<4)|(fontColor&0x0f);
		ct1=(bkColor<<4)|(bkColor&0x0f);
		}
	else
		{
		ct0=(fontColor<<4)|(bkColor&0x0f);
		ct1=(fontColor<<4)|(bkColor&0x0f);
		}
    pTopLine = get_osdbuf_region_ptr(SETUP_REGION,0);   // region 0 top
    pBtmLine = get_osdbuf_region_ptr(SETUP_REGION,1);   // region 0 bot
    for(j=0;j<16;j++)
    	{
		pp = (y&1) ? pBtmLine : pTopLine;
		pp+=x+iRegionWidth*((p_scan) ? y : y>>1);
		c=(j&0x01)?ct1:ct0;
    	for(k=0;k<8;k++)
    		{
    		*pp=c;
    		pp++;
    		}
		y++;
    	}
}
#endif//TEST_INTERLACE
void osd_DrawSlantCorner(INT32 xStart,INT32 yStart,INT32 xEnd,INT32 yEnd,BYTE direct,BYTE lineOnly,BYTE fontColor)
{	//direct 0:fill left 1:fill right
	INT32 xs,xe,y,b;
	int i;
    int     iRegionWidth = region[SETUP_REGION].osd_w;
	UINT8 *pp;
    UINT8   *pTopLine, *pBtmLine;
    pTopLine = get_osdbuf_region_ptr(SETUP_REGION,0);   // region 0 top
    pBtmLine = get_osdbuf_region_ptr(SETUP_REGION,1);   // region 0 bot
	fontColor=(fontColor<<4)|(fontColor&0x0f);
	if(yEnd==yStart || xEnd==xStart)
		{
		osd_DrawLine(xStart/2,yStart,xEnd/2,yEnd,fontColor,1);
		return;
		}
	if((xEnd-xStart)*(yEnd-yStart)>0)
		b=1;
	else
		b=-1;
	xStart*=0x20000;
	xEnd*=0x20000;
	if(xStart>xEnd)
		{
		INT32 t;
		t=xEnd;
		xEnd=xStart;
		xStart=t;
		}
	if(yStart>yEnd)
		{
		INT32 t;
		t=yEnd;
		yEnd=yStart;
		yStart=t;
		}
	b*=(xEnd-xStart)/(yEnd-yStart);
	for(y=yStart;y<=yEnd;y++)
		{
		if(b>=0)
			{
			xs=xStart+(y-yStart)*b;
			xe=xs+b-0x10000;
			if(xe<xs)xe=xs;
			}
		else
			{
			xe=xEnd+(y-yStart)*b;
			xs=xe+b+0x10000;
			if(xs>xe)xs=xe;
			}
		if(!lineOnly)
			{if(direct)
				xe=xEnd;
			else
				xs=xStart;
			}
		if(xe>xEnd)xe=xEnd;
		if(xs<xStart)xs=xStart;
		xs=(xs<0)?0:xs;
		xe=(xe<0)?0:xe;
		xe=xe>>16;
		xs=xs>>16;
		pp = (y&1) ? pBtmLine : pTopLine;
		pp+=xs/2+iRegionWidth*((p_scan) ? y : y>>1);
		if(xs&1)
			{
			*pp=(fontColor & 0x0f)|((*pp) & 0xf0);
			pp++;
			}
		else
			{
			*pp=(fontColor & 0xf0)|((*pp) & 0x0f);
			xs--;
			}
		for(i=(xe-xs)/2;i>0;i--)
			pp[i-1]=fontColor;
		pp = (y&1) ? pBtmLine : pTopLine;
		pp+=xe/2+iRegionWidth*((p_scan) ? y : y>>1);
		if(0==(xe&1))
			*pp=(fontColor & 0xf0)|((*pp) & 0x0f);
		else// if(xs+1==xe) 
			*pp=(fontColor & 0x0f)|((*pp) & 0xf0);
		}
}
void osd_DrawIcon_Trans(int xStart, int yStart, unsigned index,BYTE mask,BYTE fontColor)
{
    const BYTE    *pIcon;//,div=4;//wanghaoying 2003-8-12 19:42 marked for "div" not used here
    UINT8   *pTopLine, *pBtmLine;
    UINT32   iDispLoc;
    int     i, j;
    int     iFontWidth, iFontHigh,iFontByteWidth;
    int     iRegionWidth = region[SETUP_REGION].osd_w;
    osd_tog_region(0, OSD_ON);  
    
    //initialize buffer start
    pTopLine = get_osdbuf_region_ptr(SETUP_REGION,0);   // region 0 top
    pBtmLine = get_osdbuf_region_ptr(SETUP_REGION,1);   // region 0 bot

    fontColor=(fontColor<<4)|(fontColor&0x0f);
    //skip n blank line on top(in pixel)
    //for interlace mode, we will skip n/2 blank lines, for example 4/2=2
    yStart+=2;
     
    {
        UINT8 pixel2;
        UINT32 pos;
		UINT8 *pp;
		unsigned curByte;
        
        pIcon = get_font_entry(2, index);

        //start to process
        pos = 3	;
        
        //get icon information
        iFontWidth  = (int)pIcon[0];
        iFontHigh   = (int)pIcon[1];
        iFontByteWidth  = ((iFontWidth+7)/8)*4;//the icon data unit is 32bit,so iFontByteWidth must be a multiple of 4.
        
        for (j=0; j<iFontHigh; j++) 
        {
			pp = (yStart&1) ? pBtmLine : pTopLine;
            iDispLoc = (xStart) + iRegionWidth*((p_scan) ? yStart : yStart>>1);
            for (i=0; i<(iFontWidth/2); i++) //every 2-pixels a byte
            	{
                pixel2 =  pp[iDispLoc+i];
                curByte = pIcon[pos+i];
	            pixel2=((curByte&0x0f)==0x06)?pixel2:(((mask?fontColor:curByte)&0x0f)|(pixel2&0xf0));
                pixel2=((curByte&0xf0)==0x60)?pixel2:(((mask?fontColor:curByte)&0xf0)|(pixel2&0x0f));
                pp[iDispLoc+i] =  pixel2;
            	}
			if(iFontWidth % 2)
				{
				pixel2 =  pp[iDispLoc+i];
                curByte = pIcon[pos+i];
                pixel2=((curByte&0xf0)==0x60)?pixel2:(((mask?fontColor:curByte)&0xf0)|(pixel2&0x0f));
                pp[iDispLoc+i] =  pixel2;
				}
			pos+=iFontByteWidth;
            yStart++;
        }//for icon heigh  
    }

    timeout_osd[0] = 0;
}
void osd_draw_roundcorner(int x,int y,BYTE direct,unsigned fontColor,unsigned bkColor)
{
	const BYTE corner[8][8]=
		{
			{0x01,0x07,0x1F,0x3F,0x3F,0x7F,0x7F,0xFF,},//left_up
			{0x80,0xE0,0xF8,0xFC,0xFC,0xFE,0xFE,0xFF,},//right_up
			{0xFF,0xFE,0xFE,0xFC,0xFC,0xF8,0xE0,0x80,},//right_down
			{0xFF,0x7F,0x7F,0x3F,0x3F,0x1F,0x07,0x01,},//letf_down
			
			{0x01,0x07,0x1E,0x38,0x30,0x60,0x60,0xC0,},//left_up
			{0x80,0xE0,0x78,0x1C,0x0C,0x06,0x06,0x03,},//right_up
			{0x03,0x06,0x06,0x0C,0x1C,0x78,0xE0,0x80,},//right_down
			{0xC0,0x60,0x60,0x30,0x38,0x1E,0x07,0x01,},//{0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,},//letf_down
		};
    UINT8	*pTopLine, *pBtmLine;
	BYTE	curByte;
	BYTE	pixel2;
    int     iRegionWidth,j,k;
	UINT8	*pp;
	BYTE	transcolor,transsw,invert;
    iRegionWidth = region[SETUP_REGION].osd_w;
	transsw =(direct&0x08)?0xff:0x00;
	invert =(direct&0x10)?0xff:0x00;
	direct&=0x07;
	transcolor=(~transsw)&((bkColor<<4)|(bkColor&0x0f));
    // initialize buffer start
    pTopLine = get_osdbuf_region_ptr(SETUP_REGION, 0);
    pBtmLine = get_osdbuf_region_ptr(SETUP_REGION, 1);
	for(j=0;j<8;j++)
		{
		pp = (y&1) ? pBtmLine : pTopLine;
		pp+=3+x+iRegionWidth*((p_scan) ? y : y>>1);
		
		curByte = invert^corner[direct][j];
		for (k=0; k<4; k++) 
			{		// for every-bit of pattern
			bkColor=(transsw & (*pp))|transcolor;
			pixel2=((1<<(2*k)) & curByte)?fontColor:(bkColor&0x0f);
			pixel2|=((1<<(2*k+1)) & curByte)?(fontColor<<4):(bkColor&0xf0);
			*pp=pixel2;
			pp--;
			}
		y++;
		}
}

UINT32 osd_StringDrawLength(const BYTE *str)
{
	UINT32 len;
    const BYTE    *pFont;
	len=0;
    while (*str != '\0')
    	{
        if (*str == '\r') {                    //prefix characher: to use font_table2
            if (*(str++)=='\0' ) break;
            if ((pFont = get_font_entry(1,*str))==NULL) continue;
        	} 
		else {
            //get current char entry
            pFont = get_font_entry(0,*str);
        	}
        len+= (int)pFont[0];
		str++;
    	}
	len/=2;
	return len;
}
void osd_DrawString_ori(UINT32 xStart, UINT32 yStart, const BYTE *str, BYTE fontColor, BYTE bkColor)
{
    BYTE    c;
    const BYTE    *pFont;
    UINT8  *pTopLine, *pBtmLine;
    UINT32     cc;
    UINT32  iStrLoc;
    int     iRegionWidth;

    iRegionWidth = region[SETUP_REGION].osd_w;

    // initialize buffer start
    pTopLine = get_osdbuf_region_ptr(SETUP_REGION, 0);
    pBtmLine = get_osdbuf_region_ptr(SETUP_REGION, 1);
    
    // initialize start position
	#ifdef SOFT_MENU//Modifed by ChenZhao on 2004-9-8 17:38 WP
	cc = xStart; //pixels
	#else
	cc = xStart*8; //pixels
	#endif
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
            UINT8 *pp;
            int     yy;
            int     iDispLoc;

            //yy  = 4 + yStart*SETUP_BTN_HEIGHT + j;
            yy  = 4 + yStart + j;

            //For every string line = 1 blank line(in pixel) + OSD_FONT_HEIGHT-line strings + 1 blank line
            pp  = (yy&1) ? pBtmLine : pTopLine;
            if (p_scan==0) yy>>=1;      // p-scan
            //yy*iRegionWidth + cc calculate the positon as the byte.
            iDispLoc = yy*(iRegionWidth) + cc;
            
            //draw top line
            for (i=0; i<iFontWidth/8; i++) {
                unsigned curByte;
                UINT8 pixel2;
                
                curByte =pFont[++pos];
                pixel2 = 0;
                for (k=0; k<4; k++) {       // for every-bit of pattern
					pixel2=((1<<(2*k)) & curByte)?fontColor:bkColor;
					pixel2|=(((1<<(2*k+1)) & curByte)?fontColor:bkColor)<<4;
					pp[iDispLoc+i*4+3-k] = pixel2;
                }
            }
        }
        cc+=iFontWidth/2; 
    }
    timeout_osd[SETUP_REGION] = 0;
    osd_tog_region(SETUP_REGION, OSD_ON);  
}

