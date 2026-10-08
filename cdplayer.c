/**********************************************************
**  Description: for cd player
**  Creater:liweihua
**  Date:2003-9-3
***********************************************************/
#include "global.h"
#include "memmap0.h"
#include "ircmd.h"

#ifdef CD_PLAYER

//declare the extern vars and consts
extern BYTE bEqMaxKeepTm;
extern void  osd_init_cdplayer(); 
extern UINT8 *get_osdbuf_region_ptr(int _region, int _field);
extern const UINT8 osd_header_offset[8];
#define	OSD_DATA_OFFSET(f)	    (osd_header_offset[(f)&OSD_FORMAT_MASK])
void osd_print_cdeq(UINT8 r,BYTE *p);
void DisplaycdEq(void);

//setting the band color
#define GREENCOL        0xcccc
#define BLUECOL      	0xbbbb
#define BLACKCOL        0xdddd

//setting the region of band
#define AUDBAND_R       3

//display the video in the player interface according to spectrum value(7 bands)
void show_cdplayer(void)
{
    osd_init_cdplayer();
    unEqMaxRef=0;
    //bEqDisplay=1;
    //setup_eq_display(1);//terry,2003/9/26 04:43PM
    setup_eq_display(0xf);//nono 2003-10-22 15:14 change for new dsp code.
}

//Draw EQ status on screen by OSD
// r : region for draw
// *p: input 7 band EQ value 
//Each band energy range is 0 ~ 71 
void osd_print_cdeq(UINT8 r,BYTE *p)
{
    UINT16  iWidth;
    UINT16  i,j,iBlock,step,k;
    UINT16  *pTopLine,*pBtmLine;
    UINT16  unColor;    
    BYTE    bChannelVal[14];    //byte 13 is garbage
    BYTE barlen;
    iWidth = region[r].osd_w/4;
    if(p_scan==0)
    {
    	barlen=72;    	
    }
    else
    {
    	barlen=144;
    }
    
    //calcuate the interpolate data
    //The data is mapping to 0 ~ 71    
    for (i=0;i<14;i=i+2)
    {
        bChannelVal[i]=*p;
        bChannelVal[i+1]=(*(p)+*(p+1))/2;
        p++;
    }
    
    //check the last max value
    for (i=0;i<13;i++)
    {
        if (bEqEnergyMax[i]<=bChannelVal[i])
        {
            bEqEnergyMax[i]=bChannelVal[i];
        }
        else
        {                
            if(p_scan==0)             
            {
            if ( (bEqEnergyMax[i]!=0) && (bEqMaxKeepTm==0) )
                {
                    bEqEnergyMax[i]=bEqEnergyMax[i]-1;    //reduce 1  
                } 
            }
            else
            {
            if ( (bEqEnergyMax[i]>=2) && (bEqMaxKeepTm==0) )
                {
                    bEqEnergyMax[i]=bEqEnergyMax[i]-2;    //reduce 1  
                } 
            }         
        }
    }
    
    if (bEqMaxKeepTm)
        bEqMaxKeepTm--;
    else
        bEqMaxKeepTm=1;

    //plot the background block
    if (p_scan==0) {
        pTopLine = (UINT16 *) (get_osdbuf_region_ptr(r,0)+iWidth*120/2);
        pBtmLine = (UINT16 *) (get_osdbuf_region_ptr(r,1)+iWidth*120/2);
    } else {
        pTopLine = (UINT16 *) (get_osdbuf_region_ptr(r,0)+iWidth*120);
        pBtmLine = (UINT16 *) (get_osdbuf_region_ptr(r,0)+iWidth*120);
    }
    

    //Totally has 72 block for each freq (0 ~ 71 )
    //pTopLine=pTopLine+iWidth;
    if(p_scan==0)  step=1;
    else step=1;
    
    
    for (j=barlen;j>0;j--)
    {      
        for(k=0;k<step;k++)
        {
            //pTopLine[0]=TRANS_COLOR;
            
            for (i=1,iBlock=0;iBlock<13;i=i+4,iBlock++)
            {    
                //make sure color
                if (j==bEqEnergyMax[iBlock])
                    unColor=BLUECOL;
                else {
                    if (j<bChannelVal[iBlock])
                        unColor=GREENCOL;
                    else
                        unColor=BLACKCOL;   
                }            
                                  
                pTopLine[i]   =  unColor;
                pTopLine[i+1] =  unColor;
                pTopLine[i+2] =  unColor;
                if (p_scan==0)
                {
                    pBtmLine[i]   =  unColor;
                    pBtmLine[i+1] =  unColor;
                    pBtmLine[i+2] =  unColor;
                }
            }
            pTopLine+=iWidth;    
            if (p_scan==0) pBtmLine+=iWidth;
        }
        
        //step 2 line
        pTopLine+=(iWidth*step);    
        if (p_scan==0) pBtmLine+=(iWidth*step);
       
    } 
}

//draw the lines related with the 7 spectrum values
void DisplaycdEq(void)
{
    BYTE    i,j;
	BYTE	bEqValue[7];
	//BYTE 	*p;
    //Steven 2006/10/04 modify , use get_dsp3_pcm_value() instead of directly access address //
        if (bEqDisplay>=4) 
        {
            //p = get_dsp_pcm_uptr(DSP_RUNTIME_EQ_SPECTRUM,0);
                       			
            for (i=0, j=0;i<7 ;i++) 
            {
                UINT32  eqSrc;
                UINT32  eqTemp;
                
                //eqSrc = (((*p)<<8) | *(p+1));                
                //p+=3;
                eqSrc = get_dsp3_pcm_value((DSP_RUNTIME_EQ_SPECTRUM+i))>>8;

                if (eqSrc > unEqMaxRef)
					unEqMaxRef = eqSrc;

                //normalize value to 0 ~ 25
                if (unEqMaxRef==0) 
                    eqTemp = 0;
                else
                {
                	if(p_scan==0)
                		eqTemp = eqSrc*80/unEqMaxRef;
                	else
                		eqTemp = eqSrc*160/unEqMaxRef;
                }

                bEqValue[i] = eqTemp;
				
            if (bEqValue[i]<4) 
            {
                    j++;
                }
            }

            //adjust max refrence 
            if ( (j>=6) && (unEqMaxRef>400) )
                unEqMaxRef=unEqMaxRef-(unEqMaxRef/8);
			
            osd_print_cdeq(AUDBAND_R, bEqValue);			
            bEqDisplay=1;
        } else {
            bEqDisplay++;
        } 
    } 

#endif

