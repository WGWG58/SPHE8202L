//
// FILE
// ninf.c
//
// DESCRIPTION
// navigator interface
// all access to navigator internal should use functions from this file.
//
#include "config.h"
#include "set.h"
#include "navdata.h"

#include "ninf.h"
#include "navif.h"

#ifdef NOT_SUPPORT_DVDAUDIO_NO_GUI
#include "fs.h"
#endif

extern UINT8 DVD_check_state(void);
extern UINT8 SrvReadCPRMAI(void);
//
// FUNCTION
// ninf_get_dvd_sup_clut(n)
//
// DESCRIPTION
// kernel sub-picture decoder use this function to get color-palette
// entries of current sub-picture
//
// return Y-CB-CR format
//
UINT32  ninf_get_dvd_sup_clut(int n)
{
    UINT32  v;
    v = 0x008080;
    if (pDSV!=NULL) {
        v = (((unsigned)pDSV->DSVPLT[n].dY  << 16)
          |  ((unsigned)pDSV->DSVPLT[n].dCb << 8)
          |  ((unsigned)pDSV->DSVPLT[n].dCr << 0));
    }
    return v;
}



extern  UINT8   srv_on;
//note: never change this function
UINT32  ninf_get_dvd_CPM(void)
{
#ifdef DVD_SERVO
    if (srv_on) return (SrvReadCPRMAI()>>7); 
    else
#endif
		return 1;
}

//note: never change this function
UINT32  ninf_get_dvd_CGMS(void)
{
#ifdef DVD_SERVO
    if (srv_on) return (SrvReadCPRMAI()>>4)&0x03;
#endif
    return 3;
}


UINT32  ninf_get_dvd_VMGM_V_ATR(void)
{
    return pDSV->dV_ATR;
}

//terry,2004/2/6 05:43PM,move to hear
int is_menu(void)
{
    int menu=0;
    
    if(cd_type_loaded==CDDVD)
    {
		if( (!DVD_check_state())&&(play_state!=VCD_STATE_STOP) )         
        {//terry,2-5-17 2:35
        	//when play still PIC,we do wrong judged...so I modify. linrc 2006-1-16 14:22 
            if(!((still_timer==255)&&(pDSV->CurrState==NAV_CELL_POST)&&(!Get_BTN_Ns())))
            menu=1;
        }
    }else if(IsPBCOn())
    {
        if(psd_state==(PSD_SEL_LIST|PSD_PLAY_SEG))
            menu=1;
    }
    
    return menu;
}


//
//
//
int is_dvdaudio_aob(void)
{
#ifdef  DVD_AUDIO
    return (AOB);
#else
    return 0;
#endif
}

#ifdef NOT_SUPPORT_DVDAUDIO_NO_GUI
//wanghaoying add 2004-7-15 12:02
//To: confirm wheather this disc is dvd-audio
//return: 1 -> dvdaudio disc; 0 -> not
BYTE is_dvdaudio_disc(void)
{    
    //return 0;
    //if ( DISC_IS_DVD()==1 )
    {
        if( (UDFVol.DIR_Location=search_dir("AUDIO_TS"))!=0xffffffff)
        {             
		    if(search_file("AUDIO_TS.IFO")!=0)
		    {
		        return 1;
		    }
		    else
		    {
		        return 0;
		    }
		}
	}
}
#endif

