/*
** FILE
** vfd.c
**
** DESCRIPTION
** handle VFD functions.
*/
#include "user_init.h"
#include "config.h"
#include "global.h"
#include "memmap.h"
#include "sio.h"
#include "vfdfunc.h"
#include "ircode.h"
#include "ircmd.h"
#include "func.h"
#include "osd.h"
#include "avd.h"
#include "gpio.h"
#include "iop.h"
#include "cd.h"

#ifdef USE_VFDPORT_TRANDATA         //add by linrc 2004-3-24 21:56 for minidvd receive
    #include "8200_51MCU.c"     //program introduce in the /IR_VFD/8200_51MCU.c file
#endif    

#ifndef JPG_OLD_PARSER_FLOW
BYTE	bJpgVFDPause;
#endif

UINT32	get_rtc_val();

//#ifdef P9c9_Panel //jacky 2003/10/23 07:35PM
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF      //gerry,2004-1-30 18:11
int led_flash_interval=0;
int led_flash_time=0;
#endif 

#ifdef  BBK_DVD   //fengjl add  4-2-3 20:22
extern tv_output_vfd_time;  
#endif

#if defined(SUPPORT_VFD)
static UINT16  counter, index;
#endif
BYTE    vfd_state = 0;
extern UINT32 save_srn_start_t;
#ifdef SUPPORT_VFD_MESSAGE //chenzhao 20060118
BYTE vfd_message_state;
BYTE vfd_message_timeout;
#endif

#include "vfd_mod.c"

#ifdef HT1621_PANNEL//nono 4-5-9 23:56
    const BYTE vfd_keycode[]={};
#endif

#ifdef NEW_JPEG
    extern BYTE bJpgVFDPause;
#else
    #ifndef SHARE_NAV_VAR
        extern BYTE bJpgVFDPause;				//Jeff 20020523
    #else
        #define bJpgVFDPause (pFsJpeg->bJpgVFDPause)
    #endif
#endif

extern UINT16 Is_JPEG_SlideMode(void);

#if defined(SLEEP_WHEN_POWER_ON)&&defined(TONIC_DVD)//20040206
extern int power_on_flag;	//zhg 2004-1-4 15:46
#endif

#ifdef EASTWIN
UINT8 bINVERTER_POWER = 0, bEARPHONE_IN = 0,bAMP_IS_ON = 0,bLOWBAT_DISP = 0,bPOWER_LED_FLASH = 0;
UINT8 bIS_LOWBAT = 0, bPOWER_ON_MUTE_EXE = 0;				// Kevin Sep 10,04 
#endif

#ifdef NEXT_FORWARD_IN_A_KEY		//gerry move it here,3-10-29 17:50
BYTE key_data_flag=0;
#endif

//wanghaoying add 2005-9-20 14:58
//to store the dimming level of vfd display dimming quantity
//limitation: 0 ~ 7 : 0b000~0b111
#ifdef VFD_DIMMING_CONTROL
BYTE dimming_level = VFDC_DISP_CTRL_10_16;
#define DIMMING_MAX     0x03
#define DIMMING_MIN     0x00
#endif


//#define     VFD_DBG     1
//#define VFD_KEY_TEST

#ifdef TEST_VFD									//shawn add at 910131

UINT8   SC_1 = 15;
UINT8   COMMAND_MODE = 2;

void update_vfd_dot_inc(void)		//shawn add at 910131
{
	if(SC_1 < 40)
		SC_1++;
	printf("\n SC_1(BYTE_INC)=%d\n\n", SC_1);
	
#ifdef VFD2OSD_DBG_TXD
	psprintf(RegionValStr[REGION1], "SC_1 BYTE_INC: %d", SC_1);
	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
}


void update_vfd_dot_dec(void)		//shawn add at 910131
{
	UINT8   a;
	
	for(a = SC_1; a <= 25; a++)
		vfd_mem[a] = 0x00;
	if(SC_1 > 0)
		SC_1--;
	printf("\n SC_1(BYTE_DEC)=%d\n\n", SC_1);
	
#ifdef VFD2OSD_DBG_TXD					//nono 2-8-9 14:39
	psprintf(RegionValStr[REGION1], "SC_1 BYTE_DEC: %d", SC_1);
	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
}

void update_vfd_mod_inc(void)		//shawn add at 910131
{
	//counter++;
	
	if(COMMAND_MODE < 16)
		COMMAND_MODE++;
	
	printf("\n COMMAND_MODE(INC)=%d\n\n", COMMAND_MODE);
	
#ifdef VFD2OSD_DBG_TXD					//nono 2-8-9 14:40
	psprintf(RegionValStr[REGION3], "COMMAND_MODE INC: %d", COMMAND_MODE);
	PrintOsdMsg(STR_OS_SPACE, REGION3, 1, 1);
	
#endif
	
	reset_vfd();
}

void update_vfd_mod_dec(void)		//shawn add at 910131
{
	//counter--;
	
	if(COMMAND_MODE > 0)
		COMMAND_MODE--;
	printf("\n COMMAND_MODE(DEC)=%d\n\n", COMMAND_MODE);
	
#ifdef VFD2OSD_DBG_TXD					//nono 2-8-9 14:40
	psprintf(RegionValStr[REGION1], "COMMAND_MODE DEC: %d", COMMAND_MODE);
	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
	
	reset_vfd();
}

void update_vfd_inc(void)				//shawn modify at 910131
{
	counter++;
}

void update_vfd_dec(void)				//shawn modify at 910131
{
	counter--;
}

#endif //TEST_VFD

#ifdef SHOW_VOL_ON_VFD //huziqin 2004-4-29.if setting channel volume.
extern	BYTE subvol_time_out;
#endif

void update_vfd_data(void)
{
#if defined(SUPPORT_VFD)&&defined(SUPPORT_VFD_PANEL)//nono 20031124//lijd 2004-12-4 11:14

#ifdef VFD_SHOW_LOAD_TOGGLE//nono 2003-10-17 18:23		
    static BYTE load_toggle_flag;
#endif

#ifdef SUPPORT_VFD_MESSAGE//chenzhao20060118
    if(vfd_message_timeout)
    {
        show_vfd_message();
        return;
    }
#else//#ifdef SUPPORT_VFD_MESSAGE//chenzhao20060118
#ifdef SHOW_VOL_ON_VFD
	if(subvol_time_out)
    {
        show_amp_vol_on_vfd();
        return;
    }
#endif//#ifdef SUPPORT_VFD_MESSAGE//chenzhao20060118
#endif
#if defined(SUPPORT_RECEIVER)//&&!defined(SUPPORT_VFD_MENU)//chenzhao20060118
    if(current_rcvr_mode!=RECEIVER_MODE_DVD)
    {
    	//vfd_set_reveiver_mode();
        return;
    }
#endif	


#ifdef TEST_VFD
	UINT8   by, bit, i;						//,j;            //shawn modify at 910131
	
	
	index++;
	if(index % 10)
		return;
	
	
	
	by = counter / 8;
	bit = counter % 8;
	
	#ifdef YADAI_PT6554_PANNEL
    	for(i = 0; i < SC_1; i++)
    	{
    		if((i==5)||(i==11)||(i==17)||(i==23))
    		{
    			vfd_mem[i] = 0x00;
    		}
    		else
    		{			
		vfd_mem[i] = 0xff;
    		}
    	}
	#else
	
	    for(i = 0; i < SC_1; i++)				
		vfd_mem[i] = 0xff;
	
	#endif	
	
	
	vfd_mem[by] = ~(0x01 << bit);
	
	
	//vfd_set_str(STR_OS_CLOSE,"");
	
	printf("BYTE:%d BIT:%d\n", by, bit);
	//psprintf(linebuf,"BYTE:%d BIT:%d",by,bit);
	
#ifdef VFD2OSD_DBG_TXD					//nono 2-8-9 14:40
	psprintf(RegionValStr[REGION1], "BYTE:%d BIT:%d", by, bit);
	PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
#endif
	//ShowOsdMsg(linebuf,0);
	return;
#endif
	
#ifdef BBK_DV961_DVD//zhaoyanhua add to show VFD Message for VGA/INTERLACE/P_SCAN  3-11-27 9:50
    if(tv_output_vfd_time != 0)
    {
        tv_output_vfd_time--; 
        switch(tv_out_id)
        {
            case INTERLACE:
                vfd_set_str(0,"1-    ");
                break;
            case PC_VGA:
                vfd_set_str(0,"2-    ");
                break;
            case P_SCAN:
                vfd_set_str(0,"3-    ");
                break;
        
        }
        
        //turn off ":"(min)":"(sec)
        vfd_reset_dot(VFD_DOT_MINSEC);
		vfd_reset_dot(VFD_DOT_MIN);
        return;
    }
#endif	//#ifdef BBK_DV961_DVD
	
	
	if(play_state != VCD_STATE_TUNER)
	{
		//===========================================
#ifdef HUAJIA_DVD
#define INTV_TM 20
#else
#define INTV_TM 10
#endif	
		counter++;
		
		
		if(adv_search_time > 0)
		{
			if(counter % (INTV_TM / adv_search_time))
				return;
		}
		else if(adv_search_time < 0)
		{
			if(counter % (INTV_TM / (-adv_search_time)))
				return;
		}
		else if(video_slow)
		{
			{
				UINT8   rate = (UINT8) video_slow;
				
				if(counter % (INTV_TM * rate))
					return;
			}
		}
		else if(play_state != VCD_STATE_CLOSE)
		{
				if(counter % INTV_TM)

					return;
		}
		else if(counter % (INTV_TM / 2))
			return;
		counter = 0;
	}
	
	/********************************************************/
	// try the function by chichang 2001 6/5
	/********************************************************/
	/*
	vfd_mem[36]=0xff;
	vfd_mem[37]=0xff;
	
	  vfd_set_dot(VFD_DOT_PLAY);
	  vfd_set_dot(vfd_disc[index]);
	  //vfd_set_str(0,"WELCOME");
	  
		
		  if(index>=11)
		  {
		  index=0;
		  }else
		  index++;
		  vfd_reset_dot(vfd_disc[index]);
	*/
	//===========================================================//
	// process the vfd display of volume and tone   2002-07-03 freyman
	/************************************************************/
#ifdef VFD_VOLUME_DISPLAY
	//  if(vfd_mode_state != DVD_NORMAL_MODE)
	if(timeout_vfd != 0)
		return;
#endif
	/************************************************************/
	// start the vfd program
	/************************************************************/

#ifdef USE_VFD_LED_AS_IO //xyy add for Oritron
	write_vfd_led(0x00);
#endif

	#ifdef VOL_LED
	write_vfd_led(0xff);
	#endif

	#ifdef GBM_USE_VFD_CONTROL_LED		//GERRY,2004/2/12 04:14¤U¤È
//	write_vfd_led(0xff);
	#ifdef GBM_USE_VFD_CONTROL_P_SCAN_LED
	if(p_scan==0)
		write_vfd_led(0xf);		//3 led are all off,2004-2-19 21:03
	else
		write_vfd_led(0xe);		//only p-san led on,2004-2-19 21:03
	#else//GBM_USE_VFD_CONTROL_P_SCAN_LED
	write_vfd_led(0xff);
	#endif//GBM_USE_VFD_CONTROL_P_SCAN_LED
	#endif//GBM_USE_VFD_CONTROL_LED

	switch (play_state)
	{
	case VCD_STATE_POWER:			//power off
		
#ifdef N701_PANNEL
		erase_vfd_mem();
		vfd_set_welcome(index);
		index = index + 1;
		if(index >= 18)
		{
			index = 18;
		}
		
#else
		
		// erase_vfd_mem();
		// index=index+1;
		
		index = vfd_set_power_state(index);
	
/*Here not used,deleted by xyy 2004-8-3*/

#endif
		
		return;
		
	case VCD_STATE_IDLE:				//no disc
		
#ifdef N701_PANNEL
		erase_vfd_mem();
		vfd_set_welcome(index);
		index = index + 1;
		if(index >= 18)
		{
			index = 18;
		}
		
#else
		
		if(system_state == SYSTEM_NODISC)
	        {
			index = vfd_set_no_disc_state(index);
//#ifdef P9c9_Panel //Jacky Led light off when NODISC 2003/10/24 11:27AM
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF          //gerry,2004-1-30 18:14
			write_vfd_led(0xff);
#endif
		}
		else
			index = vfd_set_idle_state(index);
#endif
		return;
	case VCD_STATE_CLOSE:

#ifdef VFD_SHOW_LOAD_TOGGLE
		if(load_toggle_flag<1)
		{
			write_vfd_led(0xf);
			erase_vfd_mem();
		}
		else
		{
			write_vfd_led(0);
		    index = vfd_set_close_state(index);
		}
		
		load_toggle_flag++;
		if(load_toggle_flag==2) load_toggle_flag=0;
#else//#ifdef VFD_SHOW_LOAD_TOGGLE
		index = vfd_set_close_state(index);
#endif//#ifdef VFD_SHOW_LOAD_TOGGLE

		{
//#ifdef P9c9_Panel //Jacky for p9c9 panel
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF          //gerry,2004-1-30 18:14
               extern int led_flash_interval;
		 if((led_flash_interval%5)==0)		
		    write_vfd_led(0xff);
		 else
		    write_vfd_led(0x00);
		  led_flash_interval++;
#endif //Jacky end
		 }
		return;
		
	case VCD_STATE_READTOC:		//chk disc type loading...
		
#ifdef N701_PANNEL
		erase_vfd_mem();
		//vfd_set_str(0,"WELCOME");
		
		//printf("===== set_welcome=======\n");
		//vfd_set_dot(VFD_DOT_ANGLE);
		vfd_set_welcome(index);
		index = index + 1;
		if(index >= 18)
		{
			index = 18;
		}
#else
		//erase_vfd_mem();
		//index=index+1;
#ifdef VFD_SHOW_LOAD_TOGGLE		
		if(load_toggle_flag<1)
		{
			write_vfd_led(0xf);
			erase_vfd_mem();
		}

		else
		{
			write_vfd_led(0);
			index = vfd_set_toc_state(index);
		}
		
		load_toggle_flag++;
		if(load_toggle_flag==2) load_toggle_flag=0;
#else//#ifdef VFD_SHOW_LOAD_TOGGLE
		index = vfd_set_toc_state(index);
#endif//#ifdef VFD_SHOW_LOAD_TOGGLE		
		
#endif
		return;
		
	case VCD_STATE_OPEN:
		//erase_vfd_mem();
		//vfd_set_str(STR_OS_OPEN,0,0,"");
        //Maoyong 2004.05.26 avoid vfd display error when use CMD_FUNC_OPEN to break mainloop
        if(CDOpened())
		index = vfd_set_open_state(index);
		{
//#ifdef P9c9_Panel //Jacky for p9c9 panel
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF          //gerry,2004-1-30 18:15
		  extern int led_flash_time;
		  if((led_flash_time%5)==0)		
		    write_vfd_led(0xff);
		  else
		    write_vfd_led(0x00);
		  led_flash_time++;
#endif//Jacky end
		}
		return;
		
		/*
		
		  case VCD_STATE_GAME:
		  //vfd_reset_dot(VFD_DOT_PLAY);
		  index=vfd_set_game_state(index);
		break;                  */
		
		//case VCD_STATE_STEP:
	case VCD_STATE_PAUSE:			//pause
		//vfd_reset_dot(VFD_DOT_PLAY);
		index = vfd_set_pause_state(index);
		
#ifdef GBM_USE_VFD_CONTROL_LED			//GERRY,2004/2/12 04:13¤U¤È
//		write_vfd_led(0xe);
	#ifdef GBM_USE_VFD_CONTROL_P_SCAN_LED
	if(p_scan==0)
		write_vfd_led(0xf);		//3 led are all off,2004-2-19 21:03
	else
		write_vfd_led(0xe);		//only p-san led on,2004-2-19 21:03
	#else//GBM_USE_VFD_CONTROL_P_SCAN_LED
	write_vfd_led(0xe);
	#endif//GBM_USE_VFD_CONTROL_P_SCAN_LED
#endif//GBM_USE_VFD_CONTROL_LED
		
		break;
		
	case VCD_STATE_MP3_FILELIST:	//Jeff 20010718
		//vfd_set_dot(VFD_DOT_PLAY);
		index = vfd_set_mp3_state(index);
		
		break;
		
	case VCD_STATE_STOP:
		
		//vfd_reset_dot(VFD_DOT_PLAY);
		index = vfd_set_stop_state(index);
		
		break;
		
	default:
		
#ifdef USE_VFD_CONTROL_P9C9_LED_ON_OFF          //gerry,2004-1-30 18:14
        write_vfd_led(0xff);
#endif
		
#ifdef GBM_USE_VFD_CONTROL_LED			//gerry,2004/2/12 04:13¤U¤È
//		write_vfd_led(0xd);			
	#ifdef GBM_USE_VFD_CONTROL_P_SCAN_LED
	if(p_scan==0)
		write_vfd_led(0xd);		//only play led on,2004-2-19 21:03
	else
		write_vfd_led(0xc);		//play & p-san led on,2004-2-19 21:03
	#else//GBM_USE_VFD_CONTROL_P_SCAN_LED
	write_vfd_led(0xd);			
	#endif//GBM_USE_VFD_CONTROL_P_SCAN_LED
#endif//GBM_USE_VFD_CONTROL_LED
		
		//vfd_set_dot(VFD_DOT_PLAY);
		//index=vfd_set_disc_run(index);
		index = vfd_set_normal_state(index);
		break;
		
	}															// end of switch
	
/*Here not used,deleted by xyy 2004-8-3*/


#ifdef BBK_DVD//when STOP,not show time again. zhaoyanhua add 3-11-27 10:20
    if(play_state != VCD_STATE_STOP)
#endif
	vfd_set_playback();

#endif  //#if defined(SUPPORT_VFD)&&defined(SUPPORT_VFD_PANEL)	
}


void init_vfd_clear(void)
{
#if defined(SUPPORT_VFD)&&defined(SUPPORT_VFD_PANEL)//nono 20031124//lijd 2004-12-4 11:14

	int     i;										//,j;
	BYTE    mem_count;
	#if defined(POWER_OFF_SHOW)&&defined(TONIC_DVD)||defined(KENLOON_DVD)//20040206
	UINT32  power_timer=0;
	#endif
	
	erase_vfd_mem();
#if (VFD_DRIVER==PT6554)//LIJD 2004-3-6 18:58
	regs0->iop_data[VFD_DAT0] = 0;
	regs0->iop_data[VFD_DAT1] = 0;
	regs0->iop_data[VFD_DAT2] = 0;

	WaitIopFunRdy(IOP_RDY_WAIT);
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
				(FUN_VFD_WRITE | VFD_DAT_LEN1);

	WaitIopFunRdy(IOP_RDY_WAIT);
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
				(FUN_VFD_WRITE | VFD_DAT_LEN6);

	WaitIopFunRdy(IOP_RDY_WAIT);
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
				(FUN_VFD_WRITE | VFD_DAT_LEN3);

	WaitIopFunRdy(IOP_RDY_WAIT);
	regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
				(FUN_VFD_WRITE | VFD_DAT_LEN4);
				
	return;
#endif//(VFD_DRIVER==PT6554)
	
	//send memory data to VFD

#ifdef POWER_OFF_SHOW	//wangfeng 2003-10-13 18:03
	if (system_state==SYSTEM_POWER||play_state==VCD_STATE_POWER)
	{
	#ifdef BBK_DV961_DVD     //hq add,3-11-30 14:22
                vfd_set_str(0,"OFF"); 
		vfd_set_dot(VFD_DOT_LED);    
	#elif defined(HK_ORITRON_PANNEL)
		 vfd_set_str(0,"-OFF-");
	#else
		vfd_set_str(0,"OFF");

        #if defined(TONIC_DVD)||defined(KENLOON_DVD)   //oujx 0206
	    power_timer=0x5ffffff;
        #endif//defined(TONIC_DVD)
		
	#endif
	}	
#endif// END POWER_OFF_SHOW
	
	mem_count = VFD_DISPLAY_SIZE;	//2001/10/23

#ifdef JIEKE_PANNEL_GK3800
    for(i = 0; i < mem_count; )
#else	
	for(i = 0; i < mem_count; i += 6)
#endif  //END JIEKE_PANNEL_GK3800
	{
		
#if (VFD_DRIVER==NEC16312) 
		regs0->iop_data[VFD_CMD] = (0xc0 | i);
#elif (VFD_DRIVER==HT1621)  //in ht1621 it don't send write cmd
		regs0->iop_data[VFD_CMD]=(i*2);
#elif (VFD_DRIVER==GT1128)  //wurh add 2006-2-14 16:28
		regs0->iop_data[VFD_CMD]=(i*2)<<8;		
#else //for spl10
		regs0->iop_data[VFD_CMD]=(0xA0 | i);
#endif

#if defined(BBK_PANNEL)||defined(HK_ORITRON_PANNEL)||defined(ORITRON_PANNEL)   //fengjl add 3-12-22 13:57 to avoid dot mp3 when power on every time
        for(i=0;i<VFD_DISPLAY_SIZE;i+=4)        
        {
        	regs0->iop_data[VFD_CMD] = (0xc0 | i);   // transfer  address   
        	if((VFD_DISPLAY_SIZE-i)<=4)//modefied by wangfeng,2003-11-24 10:41
        	{
        		regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
        		regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        		                     (FUN_VFD_WRITE | VFD_DAT_LEN2);
        	}
        	else
        	{
        		regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
        		regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
        		regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
        		                     (FUN_VFD_WRITE | VFD_DAT_LEN4);
        	}		
            WaitIopFunRdy(IOP_RDY_WAIT);
        }
#else
		regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
		regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
		regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];

#ifdef JIEKE_PANNEL_GK3800
        if(i<mem_count-2)
        {
    		regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
    			                 (FUN_VFD_WRITE | VFD_DAT_LEN4);
    		i+=4;
        }
    	else
    	{
            regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
    			                 (FUN_VFD_WRITE | VFD_DAT_LEN1);
    		i++;
		}
#else//#ifdef JIEKE_PANNEL_GK3800		
		regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
			                 (FUN_VFD_WRITE | VFD_DAT_LEN6);
#endif//#ifdef JIEKE_PANNEL_GK3800	
	
		WaitIopFunRdy(IOP_RDY_WAIT);
#endif
	}

#if defined(POWER_OFF_SHOW)&&defined(TONIC_DVD)||defined(KENLOON_DVD)//20040206
	while(power_timer){power_timer--;}	
	
	if (system_state==SYSTEM_POWER||play_state==VCD_STATE_POWER)
	{
		erase_vfd_mem();
		mem_count = VFD_DISPLAY_SIZE;	//2001/10/23	
		for(i = 0; i < mem_count; i += 6)
		{		
			#if (VFD_DRIVER==NEC16312) 
			regs0->iop_data[VFD_CMD] = (0xc0 | i);
			#elif (VFD_DRIVER==HT1621)  //in ht1621 it don't send write cmd
			regs0->iop_data[VFD_CMD]=(i*2);
			#else //for spl10
			regs0->iop_data[VFD_CMD]=(0xA0 | i);
			#endif
			
			regs0->iop_data[VFD_DAT0] = vfd_mem[i + 1] << 8 | vfd_mem[i];
			regs0->iop_data[VFD_DAT1] = vfd_mem[i + 3] << 8 | vfd_mem[i + 2];
			regs0->iop_data[VFD_DAT2] = vfd_mem[i + 5] << 8 | vfd_mem[i + 4];		
			regs0->iop_data[0] = (regs0->iop_data[0] & VFD_DATLEN_MASK) |
			                     (FUN_VFD_WRITE | VFD_DAT_LEN6);		
			WaitIopFunRdy(IOP_RDY_WAIT);
		}
	}
	#endif//#if defined(POWER_OFF_SHOW)&&defined(TONIC_DVD)//20040206
#endif  //#if defined(SUPPORT_VFD)&&defined(SUPPORT_VFD_PANEL)
}




/*
** FUNCTION
** erase_vfd_mem
**
** DESCRIPTION
** clear vfd memory.
*/


void erase_vfd_mem(void)
{
#if defined(SUPPORT_VFD)&&defined(SUPPORT_VFD_PANEL)//lijd 2004-12-4 11:15
	unsigned i;
	
	#if defined(SUPPORT_VFD_SHOW_P_SCAN)&&defined(TONIC_DVD)//20040206
	if(vfd_intr_timer)
	    return;
	#endif	

	for(i = 0; i < VFD_MEM_LEN; i++)
	{
		vfd_mem[i] = 0;
	}
	//vfd_enable=VFD_CNT; //zhyf  1-4-27 9:14
#endif
}

#ifndef SUPPORT_NEC16315_VFD //opv-joke: support 5disc
void vfd_dot(UINT32 method, UINT32 p)
{

	UINT32  A = p >> 3;
	UINT32  tag = 1 << (p & 0x07);
	BYTE   *ptr = &vfd_mem[A];
	BYTE    x = *ptr;
	
	if(method == 0)
		x |= tag;
	else if(--method == 0)
		x &= ~tag;
	else
		x ^= tag;
	
	*ptr = x;
}

#endif
/*
The old/new vfd driver is different on IOP program, 
on new vfd driver is auto scan vfd key on each 10ms and keep the last
key status on SDRAM buffer. ( for power key sensibility )

*/  
#ifdef SUPPORT_VFD

#if  OLD_VFD_DRV    //if use this type to control nec16312,OLD_VFD_DRV must set 1
#include ".\\vfd\vfd_drv_old.c"

#elif (VFD_DRIVER==NEC16312) 
#include ".\\vfd\vfd_drv_nec16312.c"

#elif (VFD_DRIVER==NEC16315) //OP add
#include ".\\vfd\vfd_drv_nec16315.c"

#elif (VFD_DRIVER==HT1621)
#include ".\\vfd\vfd_drv_ht1621.c"

#elif (VFD_DRIVER==MCU810)          
#include ".\\vfd\vfd_drv_mcu810.c"

#elif (VFD_DRIVER==AD7312)
#include ".\\vfd\vfd_drv_ad7312.c"

#elif (VFD_DRIVER==HC164)
#include ".\\vfd\vfd_drv_hc164.c"

#elif (VFD_DRIVER==PT6554)
#include ".\\vfd\vfd_drv_pt6554.c"

#elif (VFD_DRIVER==SP110)          
#include ".\\vfd\vfd_drv_sp110.c"

#elif (VFD_DRIVER==GT1128)           
#include ".\\vfd\vfd_drv_gt1128.c"

#elif (VFD_DRIVER==VFD_MCU51)           
#include ".\\vfd\vfd_drv_MCU51.c"

#else
#error

#endif

#else//#ifdef SUPPORT_VFD

#include ".\\vfd\vfd_drv_gpio.c"

#endif//#ifdef SUPPORT_VFD


#include ".\\vfd\vfd_util.c"

#include ".\\vfd\vfd_io_util.c"





