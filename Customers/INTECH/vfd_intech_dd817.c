#include "user_init.h"
#include "config.h"
#include "global.h"
#include "vfdfunc.h"
//#include "vfd_7seg.h"
#include "stdlib.h"
#include "user_if.h"
#include "audif.h"
#include "kernel.h"

extern UINT16 Is_MP3_STATE(void);

extern UINT32 coding_mode_now;

#define OFFSET	20
#define MAX_POS	7
#define VFD_DISPLAY_SIZE   16//32
#define VFD_DISPLAY_MODE  0x0b//VFDC_SET_DISP_11D18S


#define DISC_SIZE 8
const UINT8 vfd_disc[DISC_SIZE] = {24,88,104,56,40,72,105,8}; //BYTE, BIT (11,6),(11,5).....(10,2)



#define TOTAL_SEG 8
const UINT8 vfd_7seg_p[TOTAL_SEG]={0,1,2,3,4,5,6,7};//7 seg position BYTE

const UINT8 vfd_Dig_Dot[]=
{
/*	A  B  C  D  E  F  G	*/	
    
   /* 0,  16,  32, 48,64,80,96,
	1,  17,  33, 49,65,87,103,	//TRK Hi  
	7,  23,  39, 55,71,81,97, 	//TRK LOW
	
	2,  18,  34, 50,66,82,98, 	//MM  Hi  6
	3,  19,  35,  51,  67,  83,  99,  	//MM  Low 7
	4,  20,  36,  52,  68,  84,   100,  	//SS  Hi  8
	5,  21,  37,  53,  69,  85,   101,  	//SS  Low 9
*/
       14,13,10,8,9,12,11,250,
       30,29,26,24,25,28,27,250,
       22,21,18,16,17,20,19,250,
       46,45,42,40,41,44,43,250,	
       38,37,34,32,33,36,35,250,
       62,61,58,56,57,60,59,250,
       54,53,50,48,49,52,51,250,
       70,69,66,64,65,68,67,250	
};
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

void  vfd_set_str(UINT8 id, char *s)
{
	BYTE i,j,k;
	UINT16 c=0;
	BYTE    var_data;
	if(id) {//english id
		//s=(char *)_OsdMessegeFont1[id][0];
		s=(char *)&(_OsdMessegeFont1[0][id][0]);
	}
	
	
	
	i=strlen(s);
	
/*	if (hudred)
		{
                 *(s + 2) = *(s+1);
		   *(s + 1) = * (s+0);
	       }
	*/
	//linebuf[20]=0;
	for(j=TOTAL_SEG;j>0;j--)
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
			
			//linebuf[2*j+OFFSET]=c>>8;
			//linebuf[2*j-1+OFFSET]=c&0x00ff;
			linebuf[j+OFFSET]=c&0xff;
		}else
		{
			//linebuf[2*j+OFFSET]=0x00;
			//linebuf[2*j-1+OFFSET]=0x00;
			linebuf[j+OFFSET]=0x00;
        }
	}/*for loop*/
	
//	if (hudred)
//		linebuf[4+OFFSET] = vfd_char[hudred-1 ];
	
	for(i=0,j=1;i<TOTAL_SEG;i++,j++)
	{		
		var_data=vfd_7seg_p[i];                         				
		c=linebuf[j+OFFSET];		
		for(k=0;k<8;k++)
   		{      	
      			id=vfd_Dig_Dot[var_data*8+k];
      			if (c & 0x80) vfd_set_dot(id);      		  	
   			else vfd_reset_dot(id);     			
      			c <<= 1;  // next bit
   		}   	
	}
	
	
	
}










UINT16 vfd_set_disc_run(UINT16 index)
{

    vfd_set_dot(vfd_disc[index]);                 //modify by shwan 0412
	if(adv_search_time>=0)
    {
        //vfd_set_dot(vfd_disc[index]);
		if(index>=(DISC_SIZE-1))
		{
			index=0;
		}else
			index++;
		
		//vfd_reset_dot(vfd_disc[index]);
		
    }else
    {
        //vfd_set_dot(vfd_disc[index]);
		if(index==0)
		{
			index=DISC_SIZE-1;
		}else
			index--;
		//vfd_reset_dot(vfd_disc[index]);
		
    }
	vfd_reset_dot(vfd_disc[index]);
	
    return index;
	
}



void vfd_set_cd_type(void)
{
	
	switch(cd_type_loaded)
	{
	case CDDVD:
		
		
		vfd_set_dot(VFD_DOT_DVD);
		
		
		if(get_angle_Ns()>1)
			vfd_set_dot(VFD_DOT_ANGLE);
		else
			vfd_reset_dot(VFD_DOT_ANGLE);
		
		break;
		
	case CDROM:
		
		if( (Is_MP3_STATE())&&(Mp3ReadFinish) )//nono 2-5-10 13:50
			vfd_set_dot(VFD_DOT_MP3);
		else
			vfd_reset_dot(VFD_DOT_MP3);
		
		break;
		
	case CDDA:
		
		vfd_set_dot(VFD_DOT_CD);
		
		break;
		
	case CDUNKNOWN:
		
		
		break;
		
	case CDSVCD:
		
		
		vfd_set_dot(VFD_DOT_S);
		vfd_set_dot(VFD_DOT_V);
		vfd_set_dot(VFD_DOT_CD);
		
		
		
		break;
		
		
	default://vcd
		
		vfd_set_dot(VFD_DOT_V);
		vfd_set_dot(VFD_DOT_CD);
		
		
		break;
		
		
		
		
	}
	
	
	
}




void vfd_set_showtime(void)

{

       BYTE track_num;	
	BYTE i;
	BYTE Time_MM;
	if(cd_type_loaded==CDDVD)
		
		if(play_state==VCD_STATE_STOP)
		{
			track_num=get_tt_info(DISP_TT_Ns);//DISP_CH);
		}
		else
		{
			track_num=get_tt_info(DISP_CH);//nono 1-12-12 21:15
		}
		
		else
			track_num=disp_trk_now;

		
		//if(show_time_hh)
		//{
		
		//psprintf(linebuf,"%02d%01d%02d%02d",track_num,show_time_hh,show_time_mm,show_time_ss);
		//    	 vfd_set_str(0,linebuf);                                    // modify by shawn 0412
		//vfd_set_dot(VFD_DOT_MIN);
		
		//}
		//else
		//{
		//nono modify it for when show_time_hh==1,VFD_DOT_MIN can't be set dot.2-5-26 0:12
	/*	
		if (show_time_mm > 99)
			{
                        hudred = (show_time_mm - 100)/10 +1;
			} 
		  else
		  	hudred = 0;
*/
		//psprintf(linebuf,"%02d%01d%02d%02d",track_num,show_time_hh,show_time_mm,show_time_ss);
		if(play_state==VCD_STATE_STOP)//lihj
		{
		psprintf(linebuf,"%04d%02d%02d",show_time_hh,show_time_mm,show_time_ss);
		//       vfd_set_str(0,linebuf);
	        }
	        else
	        {
	        psprintf(linebuf,"%04d%02d%02d",track_num,show_time_mm,show_time_ss);
	        }
		
		//}
		vfd_set_str(0,linebuf);

/*		    	for (i =0; i<7; i++)
		    		{
		    		 if (track_num > 99)
                              vfd_set_dot(vfd_Dig_Dot[i]);
				 else
				   vfd_reset_dot(vfd_Dig_Dot[i]);	
		    		}
	*/	
		vfd_set_dot(VFD_DOT_COLO1);
		vfd_set_dot(VFD_DOT_COLO2);
		vfd_set_dot(VFD_DOT_MINSEC);
		vfd_set_dot(VFD_DOT_MIN);
		
		
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
	vfd_reset_dot(VFD_DOT_DTS);
	vfd_reset_dot(VFD_DOT_DOBLY);
	if( ( coding_mode_now&(AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD) )||(cd_subtype==CD_DTS) )//nono 2-7-25 16:49
	{
		#ifndef NO_NEED_SET_DTS_DOT  //liudan add this define for intech.2006-8-30 02:00ÏÂÎç
		    vfd_set_dot(VFD_DOT_DTS);
		#endif
		
	}
	else if(coding_mode_now==AUDIF_CODING_MODE_AC3)
	{
		vfd_set_dot(VFD_DOT_DOBLY);
		
	}
	
	/*   switch(cd_type_loaded)
	{
	case CDDVD:
	
	  //vfd_set_dot(VFD_DOT_DOBLY);
	  if(*get_audio_mode()==68)
	  {
	  vfd_set_dot(VFD_DOT_DTS);
	  vfd_reset_dot(VFD_DOT_DOBLY);
	  }
	  else
	  {
	  vfd_set_dot(VFD_DOT_DOBLY);
	  vfd_reset_dot(VFD_DOT_DTS);
	  }
	  
		break;
		
		  default:
		  
			
			  break;
			  
				
				  
					
					  }
					  
	*/
		
}




void vfd_set_playback(void)
{   		
	static BYTE repeat_toggle_count=0;	
				
	if(play_state==VCD_STATE_PAUSE)
	{
		//erase_vfd_mem();
		vfd_set_dot(VFD_DOT_PAUSE);
		//vfd_set_str(STR_OS_PAUSE,"");
	}else
	{
		vfd_reset_dot(VFD_DOT_PAUSE);
	}
	
	vfd_reset_dot(VFD_DOT_PBC);
	if(IsPBCOn())
	{
		
		vfd_set_dot(VFD_DOT_PBC);
		
	}
	
	vfd_reset_dot(VFD_DOT_REPEAT);
	vfd_reset_dot(VFD_DOT_REPALL);

	
    if(rep_mode==REPEAT_TRACK)
	{
		if(repeat_toggle_count++<5)
		 vfd_set_dot(VFD_DOT_REPEAT);
		else
		  vfd_reset_dot(VFD_DOT_REPEAT);
		if(repeat_toggle_count>10)
			repeat_toggle_count=0;			
		
	}else if(rep_ab_mode==REPEAT_FIND_A||rep_ab_mode==REPEAT_FIND_B)//lihj
	{
		
		vfd_reset_dot(VFD_DOT_REPALL);
		vfd_reset_dot(VFD_DOT_REPEAT);
       
	}
	else if(rep_mode==REPEAT_DISC)
	{
		
		vfd_set_dot(VFD_DOT_REPALL);
		vfd_set_dot(VFD_DOT_REPEAT);
       
	}
	else if(rep_mode==REPEAT_DIRECTORY)
	{
	  if(repeat_toggle_count++<10)
		 vfd_set_dot(VFD_DOT_REPEAT);
	  else
		 vfd_reset_dot(VFD_DOT_REPEAT);	
	  if(repeat_toggle_count>20)
			repeat_toggle_count=0;
		
	
	}
	

    if (user_mute)
    	{
    	  vfd_set_dot(VFD_DOT_MUTE);
    	}
	else
	 {
          vfd_reset_dot(VFD_DOT_MUTE);
	}


	if (full_scrn&PROGRAM)
	 {
	  vfd_set_dot(VFD_DOT_PROGRAM);
	 }
	else
	 {
          vfd_reset_dot(VFD_DOT_PROGRAM);
	}


   if(shuffle_flag)
   	{
          vfd_set_dot(VFD_DOT_RANDOM);
       }
   else
   	{
   	  vfd_reset_dot(VFD_DOT_RANDOM);
        }
	
#if 0
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
#endif
	
	
	
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
	
	
    #ifdef MP4JPEG_STOP_OFF_VFDPLAY  //DENGHG ADD FOR intech vfd  ////denhg add
            if( ( ( play_state == VCD_STATE_MP3_FILELIST )&&(GetCurrentFileType() == CDROM_MP4))||(pFsJpeg->gifsState == FS_STATE_LIST))///denghg add 2005-7-31 19:02
          {
             vfd_reset_dot(VFD_DOT_PLAY);
          }
     #endif    //denghg add 2005-8-4 18:19
	
	
	
	if(system_state!=SYSTEM_STOP)//LIHJ
	vfd_set_cd_type();
	vfd_set_audio();
	//printf("V=%x\n",vfd_mem[3]);
	vfd_set_showtime();
	
	
	
	
	
	
	
}




UINT16	vfd_set_power_state(UINT16 index)
{
	
	// char light_str[]="CLOSE";                        //modify by shawn 0412
	
    erase_vfd_mem();
    //vfd_set_str(STR_OS_CLOSE,"");
	
	
	return index;
}


UINT16	vfd_set_idle_state(UINT16 index)
{
	
	//char light_str[]="CLOSE";
	
    erase_vfd_mem();
    vfd_set_str(STR_OS_CLOSE,"");
	
	
	return index;
}


UINT16	vfd_set_no_disc_state(UINT16 index)
{
	char light_str[]="Errdisc";
	
	
    erase_vfd_mem();
    if (bDiscType == CD_OKO)         
    {
		vfd_set_str(0,light_str);
		
    }else
        vfd_set_str(/*STR_OS_NODISC*/0,"NODISC");
	
	
	return index;
}



UINT16	vfd_set_close_state(UINT16 index)
{
	
	//char light_str[]="CLOSE";
	
	
    erase_vfd_mem();
	
    if(is_test_unit()==TRUE||system_state==SYSTEM_READ_TITLE||system_state==SYSTEM_NODISC)
        //vfd_set_str(STR_OS_READ,"");
        vfd_set_str(0,"LOAD");
	else
        vfd_set_str(STR_OS_CLOSE,"");
	
    return index;
}



UINT16	vfd_set_toc_state(UINT16 index)
{
	
	//char light_str[]="READ";
	
    erase_vfd_mem();
    //vfd_set_str(STR_OS_READ,"");
    vfd_set_str(0,"LOAD");
	
    return index;
}


UINT16	vfd_set_open_state(UINT16 index)
{
	
	//char light_str[]="OPEN";
	
    erase_vfd_mem();
	
    vfd_set_str(0,"OPEN");
	vfd_reset_dot(79);
	
    return index;
}


/*
UINT16	vfd_set_game_state(UINT16 index)
{

  
	vfd_reset_dot(VFD_DOT_PLAY);
	
	  return index;
	  }
	  
*/

UINT16	vfd_set_pause_state(UINT16 index)
{
	
	
	
	vfd_reset_dot(VFD_DOT_PLAY);
	
	return index;
}


UINT16	vfd_set_mp3_state(UINT16 index)
{
	
	vfd_set_dot(VFD_DOT_PLAY);
	index=vfd_set_disc_run(index);
	
	return index;
}


UINT16	vfd_set_stop_state(UINT16 index)
{
    int i;
    vfd_reset_dot(VFD_DOT_PLAY);
    for(i=0;i<DISC_SIZE;i++)
        vfd_set_dot(vfd_disc[i]);  //nono 1-12-12 20:55
	
    return index;
}



UINT16	vfd_set_normal_state(UINT16 index)
{
	
    vfd_set_dot(VFD_DOT_PLAY);
if(cd_type_loaded == CDDVD)
    vfd_set_showtime();
    index=vfd_set_disc_run(index);
	
    return index;
}



