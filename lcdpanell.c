#include "user_init.h"
#include "config.h"
#include "global.h"
#include "sio.h"
//#include "epp.h"

//#include "fastmath.h"
//#include "auctrl.h"
//#include "user_init.h"
//#include "vfd.h"
#include "vfdfunc.h"
#include "vfd_7seg.h"
#include "vfd_p.h"
#include "ircode.h"
#include "ircmd.h"
#include "func.h"
//#include "sig.h"
#include "fs96602.h"
#include "osd.h"
 
#include "avd.h" //zyf 2000/11/22
#include "vfd_prg.h"
//#include "reverse.h"

#include "iop.h"



#define OFFSET	20
#define MAX_POS	9 

UINT16 counter,index;


const UINT8 vfd_char[26]=
{
	VFD_7SEG_A,
	VFD_7SEG_b,
	VFD_7SEG_C,
	VFD_7SEG_d,
	VFD_7SEG_E,
	VFD_7SEG_F,
	VFD_7SEG_G,
	VFD_7SEG_H,
	VFD_7SEG_I,
	VFD_7SEG_J,
	VFD_7SEG_J,//k
	VFD_7SEG_L,
	VFD_7SEG_L,//m
	VFD_7SEG_N,
	VFD_7SEG_O,
	VFD_7SEG_P,
	VFD_7SEG_P,//q
	VFD_7SEG_r,	
	VFD_7SEG_S,
	VFD_7SEG_t,	
	VFD_7SEG_U,
	VFD_7SEG_U,//v
	VFD_7SEG_Y,//x
	VFD_7SEG_Y,
	VFD_7SEG_Y//z
};




static const	BYTE	vfd_digit[] = 
{
  VFD_7SEG_0,
  VFD_7SEG_1,
  VFD_7SEG_2,
  VFD_7SEG_3,
  VFD_7SEG_4,
  VFD_7SEG_5,
  VFD_7SEG_6,
  VFD_7SEG_7,
  VFD_7SEG_8,
  VFD_7SEG_9
};


void  vfd_set_str(UINT8 id,char *s)
{
	UINT8 i,j,c;
	
        if(id) {//english id
		//s=(char *)_OsdMessegeFont1[id][0];
                s=(char *)_OsdMessegeFont1[0][id][0];
        }
		
	i=strlen(s);	
	linebuf[20]=0;
	for(j=MAX_POS;j>0;j--)
	{
		if(i>0)
		{
			i--;
			if( (s[i]>='a')&&(s[i]<='z') )
				c=vfd_char[s[i]-0x20-'A'];
			else if( (s[i]>='A')&&(s[i]<='Z') )
				c=vfd_char[s[i]-'A'];
			else if( (s[i]>='0')&&(s[i]<='9') )	
				c=vfd_digit[s[i]-'0'];
			else
			{
				if(s[i]==0x20)
				{
					c=0;
				}
			}	
			linebuf[j+OFFSET]=c;						
		}else
			linebuf[j+OFFSET]=0;
		
	}
 #if VFD_MODULE == FUT_6_BT_269GK1	
  	vfd_mem[VFDA_T0] = (vfd_mem[VFDA_T0]&(~VFD_7SEG_DIG_MASK)) | ((linebuf[1+OFFSET]>>1)&0xbf);
  	vfd_mem[VFDA_T1] = (vfd_mem[VFDA_T1]&(~VFD_7SEG_MASK)) | linebuf[2+OFFSET]|((linebuf[1+OFFSET]&0x01)<<7);  
	vfd_mem[VFDA_P0] = linebuf[3+OFFSET]>>1;
	vfd_mem[VFDA_P1] = linebuf[4+OFFSET]|((linebuf[3+OFFSET]&0x01)<<7);
	vfd_mem[VFDA_CHAR]=linebuf[5+OFFSET];
	vfd_mem[VFDA_M0] = linebuf[6+OFFSET];
	vfd_mem[VFDA_M1] = linebuf[7+OFFSET];
	vfd_mem[VFDA_S0] = (linebuf[8+OFFSET]>>1)&0x3f;
	vfd_mem[VFDA_S1] = linebuf[9+OFFSET]|((linebuf[8+OFFSET]&0x01)<<7);			
 #endif
}



void  vfd_set_welcome(int index)
{
}


void vfd_set_playback(void)
{
  
  #ifdef VFD_DOT_INTRO 
	if(play_state!=VCD_STATE_INTRO)
	  vfd_reset_dot(VFD_DOT_INTRO);
	else
	  vfd_set_dot(VFD_DOT_INTRO);   
#endif
	  
#ifdef VFD_DOT_RAN 
	if(shuffle_flag)
	  vfd_set_dot(VFD_DOT_RAN);
	else
	  vfd_reset_dot(VFD_DOT_RAN);    
	
#endif
	
	if(IsAVDPaused())
	{	  
	    //erase_vfd_mem();
	    vfd_set_dot(VFD_DOT_PAUSE);  
	    //vfd_set_str(STR_OS_PAUSE,"");
	}else
	{		
	  	vfd_reset_dot(VFD_DOT_PAUSE);      
	}
#ifdef VFD_DOT_PBC 	
	if(IsPBCOn()) 
	  	vfd_set_dot(VFD_DOT_PBC);
	else  
		vfd_reset_dot(VFD_DOT_PBC);      
	
#endif

	if(rep_mode==REPEAT_TRACK)
	{
		vfd_set_dot(VFD_DOT_REPEAT); 
        vfd_set_dot(VFD_DOT_REP1); 
	}else if(rep_mode==REPEAT_DISC)
	{
		vfd_set_dot(VFD_DOT_REPALL);
        vfd_reset_dot(VFD_DOT_REP1);
        vfd_reset_dot(VFD_DOT_REPEAT); 
	}else
	{
		vfd_reset_dot(VFD_DOT_REPEAT); 
      	vfd_reset_dot(VFD_DOT_REP1); 
      	vfd_reset_dot(VFD_DOT_REPALL);
	}
	
	if(rep_ab_mode==REPEAT_FIND_A)
	{
		vfd_set_dot(VFD_DOT_PLAYA);
	}else if(rep_ab_mode==REPEAT_FIND_B)
	{
		vfd_set_dot(VFD_DOT_PLAYB);
	}else
	{
		vfd_reset_dot(VFD_DOT_PLAYA);
		vfd_reset_dot(VFD_DOT_PLAYB);
	}


#if 0
#ifdef VFD_DOT_PGM  
	if(prog_state)
	{
		if(play_state==VCD_STATE_STOP)
			//vfd_set_pgm(0);
			
		vfd_set_dot(VFD_DOT_PGM);   
	}else
	{
		//vfd_set_pgm(0);
		vfd_reset_dot(VFD_DOT_PGM);   
	}
#endif 
#endif

#ifdef VFD_DOT_PAL 
	if(tv_format==MODE_PAL)
	{
		vfd_set_dot(VFD_DOT_PAL);  
		vfd_reset_dot(VFD_DOT_NTSC);
	}
	else
	{
		vfd_set_dot(VFD_DOT_NTSC);  
		vfd_reset_dot(VFD_DOT_PAL);
	}    	 
#endif  


#ifdef VFD_DOT_REMAIN   //zyf 2000/11/16
	if(remain)
	vfd_set_dot(VFD_DOT_REMAIN);
	else
	vfd_reset_dot(VFD_DOT_REMAIN);
#endif


#if 0
#ifdef VFD_DOT_MIC1
	switch(audio_channel)
	{
		case CH_LR:
		case CH_RR:          
		case CH_LL:
		// 	vfd_reset_dot(VFD_DOT_MIC1);
        // 	vfd_reset_dot(VFD_DOT_MIC2);                  	
         	break;
         	
        case CH_AUTO_L:
        case CH_AUTO_R:
        	 vfd_set_dot(VFD_DOT_MIC1);
	      	 vfd_set_dot(VFD_DOT_MIC2);
          	 break;          	 
	}
#endif
#endif

#if 0
#ifdef VFD_DOT_1L
	switch(audio_effect)
	{
		case SE_STEREO:	
		 	vfd_reset_dot(VFD_DOT_1L);
		 	vfd_reset_dot(VFD_DOT_2R);         	
			break;
		case SE_HALL:		
		case SE_LIVE:	
		case SE_THEATER:	
		case SE_ROOM:	
		 	vfd_set_dot(VFD_DOT_1L);
		 	vfd_set_dot(VFD_DOT_2R);	
			break;		
	}
#endif	
#endif	

#ifdef VFD_DOT_CHAPTER  
    vfd_set_dot(VFD_DOT_CHAPTER);     
#endif
#ifdef VFD_DOT_LINE          //zyf 2000/11/26
   vfd_set_dot(VFD_DOT_LINE); 
#endif

//********  show time by chichang 2001 5/26    ********************
    {   
    	
    	psprintf(linebuf,"%02d%02d%01d%02d%02d",cd_total_trk(),disp_trk_now,show_time_hh,show_time_mm,show_time_ss);
    	vfd_set_str(0,0,linebuf);
        vfd_set_dot(VFD_DOT_MIN);
        vfd_set_dot(VFD_DOT_MINSEC);      
    }
//*****************************************************************

#if 0

	if(cd_type_loaded!=CDROM)  //jjding 2000/11/17
	{
			vfd_set_dot(VFD_DOT_CHAPTER);
			vfd_set_dot(VFD_DOT_TITLE);
			vfd_set_dot(VFD_DOT_VCD);
			vfd_set_dot(VFD_DOT_MINSEC);
			vfd_set_dot(VFD_DOT_H_M);
			
			//vfd_set_tt(cd_total_trk());
			//vfd_set_pp(disp_trk_now);       //VFD set min           		
	}else	if(play_state!=VCD_STATE_STOP)
	{			
			/*if(play_state==VCD_STATE_MP3_DIRLIST)
		    {
		     	vfd_set_pp(0);
		        vfd_set_mm(0);
		        vfd_set_ss(0);		        
		    }else*/
		    { 
		        if(mp3_user_select>99)
		        {
		           vfd_set_tt(mp3_user_select/100);
		           vfd_set_pp(mp3_user_select%100);
		        }
		        else
		        {
		          vfd_set_tt(0);
		          vfd_set_pp(mp3_user_select);          
		        }
		    }
	    
	}else
	{	   
	   		vfd_set_tt(mp3_total_dir);
	   		vfd_reset_dot(VFD_DOT_MINSEC);
        	vfd_set_mm(iso9660_file_cnt/100);
        	vfd_set_ss(iso9660_file_cnt%100);	   
	}		
#endif  
#endif




}



UINT16 vfd_set_disc_run(UINT16 index)
{

	if(adv_search_time>=0)
    {
        vfd_set_dot(vfd_disc[index]);
		if(index>=11)
		{				
			index=0;
		}else
		index++;			
		vfd_reset_dot(vfd_disc[index]); 	   
    }else
    {
        vfd_set_dot(vfd_disc[index]);
		if(index==0)
		{				
			index=11;
		}else
		index--;			
		vfd_reset_dot(vfd_disc[index]); 
    
    }	


    return index;
	
}	