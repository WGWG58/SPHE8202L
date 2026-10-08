#include "user_init.h"
#include "config.h"
#include "global.h"
#include "vfdfunc.h"
#include "vfd_7seg.h"
#include "stdlib.h"



#define OFFSET	20
#define MAX_POS	11 


const UINT8 vfd_disc[] = {0,1,2,3,4,5,6,7,8,9,10,11}; 

const UINT8 vfd_7seg_p[][2]={{6,7},{9,10},{12,13},{15,16},{18,19},{21,22},{24,25},{27,28},{30,31},{33,34}};//7 seg position BYTE

const UINT16 vfd_char[26]=
{
	VFD_7SEG_A,
	VFD_7SEG_B,
	VFD_7SEG_C,
	VFD_7SEG_D,
	VFD_7SEG_E,
	VFD_7SEG_F,
	VFD_7SEG_G,
	VFD_7SEG_H,
	VFD_7SEG_I,
	VFD_7SEG_J,
	VFD_7SEG_K,
	VFD_7SEG_L,
	VFD_7SEG_M,
	VFD_7SEG_N,
	VFD_7SEG_O,
	VFD_7SEG_P,
	VFD_7SEG_P,//q
	VFD_7SEG_R,	
	VFD_7SEG_S,
	VFD_7SEG_T,	
	VFD_7SEG_U,
	VFD_7SEG_U,//v
	VFD_7SEG_W,
	VFD_7SEG_X,
	VFD_7SEG_Y,
	VFD_7SEG_Z //z
};



const  UINT16  vfd_digit[] = 
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



/****************************************************************************************/
/*  cpy_src_len: bit 8 is 1 means that bit 8 means that only show partial string between 0 and cpy_src_len */
/*         bit 8 is 0: normal show string, that is copy total string			*/
/*         bit0~bit7 mean that copied source length					*/
/*  start_p: start position of VFD for show string(position:0~9)			*/
/****************************************************************************************/

void  vfd_set_str(UINT8 id,BYTE start_p, BYTE cpy_src_len, char *s)
{
	UINT8 i,j;
	UINT16 c=0;
	
        if(id) {//english id
		//s=(char *)_OsdMessegeFont1[id][0];
                s=(char *)_OsdMessegeFont1[0][id][0];
        }
		
		
	if(cpy_src_len&0x80)//bit 8 means that only show 0~index data	
	i=cpy_src_len&0x7F;
	else	
	i=strlen(s);	
	
	
	
	//linebuf[20]=0;
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
	
			linebuf[2*j+OFFSET]=c>>8;						
		    linebuf[2*j-1+OFFSET]=c&0x00ff;
		}else
		{
			linebuf[2*j+OFFSET]=0x00;
		    linebuf[2*j-1+OFFSET]=0x00; 
        }	
	}/*for loop*/
	 
//  this a new define(PT6311)   chichang 2001 5/26
/************************       PT6311    ******************************
*                     
**               7   7   7   7   7   7   7   7   7   7  
***      _   _   _   _   _   _   _   _   _   _   _   _   _
** 
*          BYTE 6    9  12  15  18  21  24   27	 30  33 
*		     7   10  13  16  19  22  25   28  31  34 
*
*               T2  T1  T0  P1  P0  C0   M1  M0  S1  S0    
************************************************************************/

     
     for(i=start_p,j=start_p*2+3;i<10;i++,j+=2)
     {
     	
     	vfd_mem[vfd_7seg_p[i][0]] =  linebuf[j+OFFSET];
     	vfd_mem[vfd_7seg_p[i][1]] =  linebuf[(j+1)+OFFSET];
     	
     }	
     #if 0
     vfd_mem[vfd_7seg_p[3][0]] =  linebuf[9+OFFSET];
     vfd_mem[vfd_7seg_p[3][1]] =  linebuf[10+OFFSET];
     vfd_mem[vfd_7seg_p[4][0]] =  linebuf[11+OFFSET];
     vfd_mem[vfd_7seg_p[4][1]] =  linebuf[12+OFFSET];
     vfd_mem[vfd_7seg_p[5][0]] =  linebuf[13+OFFSET];
     vfd_mem[vfd_7seg_p[5][1]] =  linebuf[14+OFFSET];
     vfd_mem[vfd_7seg_p[6][0]] =  linebuf[15+OFFSET];
     vfd_mem[vfd_7seg_p[6][1]] =  linebuf[16+OFFSET];
     vfd_mem[vfd_7seg_p[7][0]] =  linebuf[17+OFFSET];
     vfd_mem[vfd_7seg_p[7][1]] =  linebuf[18+OFFSET];
     vfd_mem[vfd_7seg_p[8][0]] =  linebuf[19+OFFSET];
     vfd_mem[vfd_7seg_p[8][1]] =  linebuf[20+OFFSET];
     vfd_mem[vfd_7seg_p[9][0]] =  linebuf[21+OFFSET];
     vfd_mem[vfd_7seg_p[9][1]] =  linebuf[22+OFFSET];
    #endif
      #if 0
      vfd_mem[VFDA_T20] =  linebuf[3+OFFSET];
      vfd_mem[VFDA_T21] =  linebuf[4+OFFSET];
      vfd_mem[VFDA_T10] =  linebuf[5+OFFSET];
      vfd_mem[VFDA_T11] =  linebuf[6+OFFSET];
      vfd_mem[VFDA_T00] =  linebuf[7+OFFSET];
      vfd_mem[VFDA_T01] =  linebuf[8+OFFSET];
      vfd_mem[VFDA_P10] =  linebuf[9+OFFSET];
      vfd_mem[VFDA_P11] =  linebuf[10+OFFSET];
      vfd_mem[VFDA_P00] =  linebuf[11+OFFSET];
      vfd_mem[VFDA_P01] =  linebuf[12+OFFSET];
      vfd_mem[VFDA_CHAR00] = linebuf[13+OFFSET];
      vfd_mem[VFDA_CHAR01] = linebuf[14+OFFSET];
      vfd_mem[VFDA_M10] = linebuf[15+OFFSET];
      vfd_mem[VFDA_M11] = linebuf[16+OFFSET];
      vfd_mem[VFDA_M00] = linebuf[17+OFFSET];
      vfd_mem[VFDA_M01] = linebuf[18+OFFSET];
      vfd_mem[VFDA_S10] = linebuf[19+OFFSET];
      vfd_mem[VFDA_S11] = linebuf[20+OFFSET];
      vfd_mem[VFDA_S00] = linebuf[21+OFFSET];         /* low byte  */
      vfd_mem[VFDA_S01] = linebuf[22+OFFSET];    /* high byte */
      #endif
      
     // vfd_mem[36] = 0xff;  //kenny mark it 2001/9/24
     // vfd_mem[37] = 0xff;
     // vfd_mem[38] = 0x00; 
}



void  vfd_set_welcome(int index)
{
       
       char light_str[]="WELCOME TO NINTAUS";
        
	vfd_set_str(0,0,0x80|index,light_str);//for  jingzhen scrolling vfd
	
	
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



void vfd_set_cd_type(void)
{

  switch(cd_type_loaded)
 {
   case CDDVD:
   vfd_set_dot(VFD_DOT_DVD); 
   
   break;
   
   case CDROM:
   vfd_reset_dot(VFD_DOT_DVD);
   break;
   
   case CDDA:
   vfd_reset_dot(VFD_DOT_DVD);
    vfd_set_str(0,0,0," CD       ");
   break;
   
   case CDUNKNOWN:
   vfd_reset_dot(VFD_DOT_DVD);
   
   break;
   
   default:
   vfd_reset_dot(VFD_DOT_DVD);
   vfd_set_str(0,0,0,"VCD       ");	
   
   
   break;
   
 	
 	
 	
 }
	
	
	
}	




void vfd_set_showtime(void)
{



 #ifdef VFD_DOT_REMAIN   //zyf 2000/11/16
	if(remain)
	vfd_set_dot(VFD_DOT_REMAIN);
	else
	vfd_reset_dot(VFD_DOT_REMAIN);
#endif



 #ifdef VFD_DOT_CHAPTER  
    vfd_set_dot(VFD_DOT_CHAPTER);     
#endif
#ifdef VFD_DOT_LINE          //zyf 2000/11/26
   vfd_set_dot(VFD_DOT_LINE); 
#endif



	






//********  show time by chichang 2001 5/26    ********************
       
    	if(cd_type_loaded!=CDDVD)
    	{
    	 if(show_time_hh)
    	 {	
    	  
    	 psprintf(linebuf,"%02d%01d%02d%02d",disp_trk_now,show_time_hh,show_time_mm,show_time_ss);
    	 vfd_set_str(0,3,0,linebuf);
    	 vfd_set_dot(VFD_DOT_MIN);
      
         }
         else
         {
         	
         psprintf(linebuf,"%02d %02d%02d",disp_trk_now,show_time_mm,show_time_ss);
         vfd_set_str(0,3,0,linebuf);
    		
         }	
        
         
        
         vfd_set_dot(VFD_DOT_MINSEC);	
        
        
	}
        else
        {
        psprintf(linebuf,"%02d%02d%01d%02d%02d",get_tt_info(DISP_CH_Ns),disp_trk_now,show_time_hh,show_time_mm,show_time_ss);//nono 01/12/18
        //psprintf(linebuf,"%02d%02d%01d%02d%02d",cd_total_trk(),disp_trk_now,show_time_hh,show_time_mm,show_time_ss);
    	vfd_set_str(0,0,0,linebuf);
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

	
	
	
}	



void vfd_set_audio(void)
{
 int i;
 
   switch(cd_type_loaded)
 {
   case CDDVD:
   for(i=VFD_DOT_AC3_FRAME;i<=VFD_DOT_AC3_96kHZ;i++)
   vfd_set_dot(i);
   
   break;
   
   default:
   vfd_set_dot(VFD_DOT_AC3_FRAME);
   vfd_set_dot(VFD_DOT_AC3_FL);
   vfd_set_dot(VFD_DOT_AC3_FR);
   vfd_set_dot(VFD_DOT_AC3_SW);

   
   break;
   
 	
 	
 	
 }	

 
 
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



	
	
}	




void vfd_set_playback(void)
{
  

	
	if(play_state==VCD_STATE_PAUSE)
	{	  
	    //erase_vfd_mem();
	    vfd_set_dot(VFD_DOT_PAUSE);  
	    //vfd_set_str(STR_OS_PAUSE,"");
	}else
	{		
	  	vfd_reset_dot(VFD_DOT_PAUSE);      
	}


	if(rep_mode==REPEAT_TRACK)
	{
		vfd_set_dot(VFD_DOT_REPEAT); 

	}else if(rep_mode==REPEAT_DISC)
	{
        vfd_set_dot(VFD_DOT_REPEAT); 
	}else
	{
		vfd_reset_dot(VFD_DOT_REPEAT); 
	}
	
	if(rep_ab_mode==REPEAT_FIND_A)
	{
		vfd_set_dot(VFD_DOT_REPAB);
	}else if(rep_ab_mode==REPEAT_FIND_B)
	{
		vfd_set_dot(VFD_DOT_REPAB);
	}else
	{
		vfd_reset_dot(VFD_DOT_REPAB);
		
	}



	#if 0
	if(prog_state)
	{
		if(play_state==VCD_STATE_STOP)
		vfd_set_dot(VFD_DOT_PGM);   
	}else
	{
		//vfd_set_pgm(0);
		vfd_reset_dot(VFD_DOT_PGM);   
	}
        #endif


	#ifdef VFD_DOT_PAL
	{		
		if(getVPP_TVsystem())
		{//pal
			vfd_set_dot(VFD_DOT_PAL);  
			vfd_reset_dot(VFD_DOT_NTSC);
		}else 
		{//ntsc
			vfd_set_dot(VFD_DOT_NTSC);  
			vfd_reset_dot(VFD_DOT_PAL);
		}
	}	
	#endif  
	vfd_set_cd_type();
	vfd_set_showtime();
	vfd_set_audio();
}



