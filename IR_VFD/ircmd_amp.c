
#ifdef SUPPORT_AMP
void ircmd_amp_on()
{
    if(user_mute==1)
    {
        user_mute = 0;
		//      OSD_OnOffRegion(OSD_OFF,1);
        
    }   
    amp_onoff_flag = 1;
    AUDIF_Set_Volume(audio_volume);//2004AUDDRV AudioSetVolume(audio_volume);
    {//2002-7-29 14:09
		//      AudioSetOutputMode(6, 0); //Set Output mode(4:AC3 5.1 channel)      
		//      exe_setup_function(STR_OS_DOWNMIX_SETUP,STR_OS_6CH_SETUP,1);
    }
	//  set_volume(80);//aux_volume);
	/*  delay_1ms(20);
    set_demute();
    delay_1ms(20);*/
    AMP_MUTE_SET(0);  // tripth amp. high mute; mute amp.
    if(play_state!=VCD_STATE_POWER)
		PrintOsdMsg(AMPON,REGION1,1,0);
}
void ircmd_amp_off()
{
    AMP_MUTE_SET(1);  // tripth amp. high mute; mute amp.
	
    if(user_mute==1)
    {
        user_mute = 0;
		//      OSD_OnOffRegion(OSD_OFF,1);
    }
	/*  delay_1ms(20);
    set_mute();
    delay_1ms(20);*/
    amp_onoff_flag = 0;
    {//2002-7-29 14:09
		//      AudioSetOutputMode(0x07, 0); //Set Output mode(7:AC3 downmix L0 R0)
		//      exe_setup_function(STR_OS_DOWNMIX_SETUP,STR_OS_VSURROUND_SETUP,1);
    }
	//  AudioSetVolume(audio_volume);
    if(play_state!=VCD_STATE_POWER)
		PrintOsdMsg(AMPOFF,REGION1,1,0);
}

void ircmd_amp_onoff(void)
{
#ifdef IRCMD_DBG
    printf("=================IRCMD_AMP_ONOFF===============\n");
#endif
    //freyman add 2002-8-27 21:33
    if(play_state!=VCD_STATE_POWER)
        if( (setup_IsSet2SPDIF_Bitstream())||(setup_IsSet2SPDIF_PCM()) )
        {
            invalid_key();
            return;
        }
		//freyman add 2002-8-25
		if((full_scrn&SETUP) || (full_scrn&PROGRAM))
		{
			return;
		}
		if(amp_onoff_flag==0)
		{
			amp_onoff_flag = 1;
			ircmd_amp_on();
		}
		else if(amp_onoff_flag==1)
		{
			amp_onoff_flag = 0;
			ircmd_amp_off();
		}
}

//freyman add 2002-9-3 10:46
#ifdef IR25//SVA_SAMPLE
void ircmd_amp_volume(void)
{
    if (
        #ifdef SUPPORT_NESGAME
		(Is_GAME_STATE()) || 
        #endif
		(Is_JPEG_STATE()) )
    {
        invalid_key();
        return;
    }

    if ( setup_IsSet2SPDIF_Bitstream() || setup_IsSet2SPDIF_PCM() )
    {
        invalid_key();
        return;
    }
    ampvol_func();
	/*    
    if(full_scrn&AMPVOL)
    {
	ampvol_exit();   
	//      printf("EXIT ampvol full_scrn:%x\n",full_scrn);
    }else
    {
	ampvol_init();
	//      printf("ampvol init full_scrn:%x\n",full_scrn);
}*/
}
void ircmd_downmix(void)
{
    #ifdef SUPPORT_NESGAME
    if ( Is_GAME_STATE() ) 
    {
        invalid_key();
        return;
    }
    #endif

	/* 
	if (coding_mode_now==AUDIF_CODING_MODE_DTSCD) {
    invalid_key();
    return;
	}
	*/
	/*if ( setup_IsSet2SPDIF_Bitstream() ) {//terry,2-5-12 20:43, VCD,MP3,CDDA spdif use PCM output
	invalid_key();
	return;
}*/
	
#ifdef SUPPORT_DVD_3D
    if((cd_type_loaded==CDDVD)||(cd_subtype==CD_DTS))
    {
        if((setup_IsSet2SPDIF_Bitstream()==0)&&
            (setup_IsSet2SPDIF_PCM()==0))
			
        { 
            if(action_click)
            {
                setup_DVD3DSound(1);
            } 
            else 
            {
                setup_DVD3DSound(0);
            }
        } 
        else 
        { 
            invalid_key();
            return;
        }
    }else
		
#else
		
		if( (cd_type_loaded==CDDVD)||(cd_subtype==CD_DTS) )//(coding_mode_now==AUDIF_CODING_MODE_DTSCD) )
		{
			invalid_key();
			return;
		}
		
#endif
		
		{
			if(full_scrn & SOUND)
			{
				if (bEqDisplay)
				{
					cancel_sound();
					
					// re-load setup module
					//LoadModual(MODUAL_AP2);
				}
				else
				{
				#ifdef OSD_BMP_SOUND
					EQ_bmp_init();
				#else
					EQ_init();
				#endif
				}
			} 
			else 
			{
				//LoadModual(MODUAL_AP3);

				//bEqDisplay = 0;
				setup_eq_display(0);//terry,2003/9/26 04:43PM
				full_scrn = SOUND;
				osd_init_music();
				ShowSoundPage();
			}
		}
}
#endif

/* wanghaoying marked 2004-7-1 15:40, for not use any more
#ifdef IR17

void ircmd_middle_down()
{
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = MIDDLE_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_middle(0);
#endif 
    if(middle_level<=0)
        return;
    middle_level -- ;
    set_middle();
}

void ircmd_middle_up()
{
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = MIDDLE_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_middle(0);
#endif     
    if(middle_level>=15)
        return;
    middle_level ++ ;
    set_middle();
}

void ircmd_base_down(void)
{
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = BASE_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_base(0);
#endif 
    if(base_level<=0)
        return;
    base_level -- ;
    set_base();
}

void ircmd_base_up(void)
{
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = BASE_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_base(0);
#endif 
    if(base_level>=15)
        return;
    base_level ++ ;
    set_base();
}

void ircmd_treble_down(void)
{
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = TREBLE_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_treble(0);
#endif 
    if(treble_level<=0)
        return;
    treble_level -- ;
    set_treble();
}

void ircmd_treble_up(void)
{
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = TREBLE_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_treble(0);
#endif 
    if(treble_level>=15)
        return;
    treble_level ++ ;
    set_treble();
}

void ircmd_front_down(void)
{   
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = CENTER_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_front(0);
#endif 
    if(front_level<=0)
        return;
    front_level--;
    set_front();
}

void ircmd_front_up(void)
{   
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = CENTER_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_front(0);
#endif 
    if(front_level>=15)
        return;
    front_level++;
    set_front();
}

void ircmd_center_down(void)
{   
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = CENTER_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_center(0);
#endif 
    if(center_level<=0)
        return;
    center_level--;
    set_center();
}

void ircmd_center_up(void)
{   
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = CENTER_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_center(0);
#endif 
    if(center_level>=15)
        return;
    center_level++;
    set_center();
}

void ircmd_rear_down(void)
{   
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = REAR_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_rear(0);
#endif 
    if(rear_level<=0)
        return;
    rear_level--;
    set_rear();
}
void ircmd_rear_up(void)
{   
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = REAR_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_rear(0);
#endif 
    if(rear_level>=15)
        return;
    rear_level++;
    set_rear();
}
void ircmd_woofer_down(void)
{   
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = WOOFER_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_woofer(0);
#endif 
    if(woofer_level<=0)
        return;
    woofer_level--;
    set_woofer();
}
void ircmd_woofer_up(void)
{   
    if (amp_onoff_flag==0)
    {
        invalid_key();
        return;
    }
#ifdef VFD_VOLUME_DISPLAY
	//    vfd_mode_state = WOOFER_MOD;
    timeout_vfd = 2*VFD_TIMEOUT;
    vfd_set_woofer(0);
#endif 
    if(woofer_level>=15)
        return;
    woofer_level++;
    set_woofer();
}

#endif
*/


#ifdef NEW_UART_COMMAND   //lijinhai 2-10-22 17:25 for fuss
extern BYTE nCurrentDVDMode;
extern BYTE nCurrentVolMode;

void ircmd_av1_mode(void)
{
	nCurrentDVDMode=MODE_AV1;
	IRSwitchMode();	
}

void ircmd_av2_mode(void)
{
	nCurrentDVDMode=MODE_AV2;
	IRSwitchMode();	
}

void ircmd_tuner_mode(void)
{
	nCurrentDVDMode=MODE_TUNER;
	IRSwitchMode();	
}

void ircmd_dvd_mode(void)
{
	nCurrentDVDMode=MODE_DVD;
	IRSwitchMode();	
}

void ircmd_qsound(void)
{
	nCurrentVolMode=VOL_MODE_QS_EFFECT;
	if (action_click)
		IRAdjustVol(1);
	else
		IRSwitchVolMode();
}

void ircmd_vol_default(void)
{
	Set_Default_Vol();	
}

void ircmd_front_vol(void)
{
	nCurrentVolMode=VOL_MODE_FRONT;
	IRSwitchVolMode();	
}

void ircmd_center_vol(void)
{
	nCurrentVolMode=VOL_MODE_CENTER;
	IRSwitchVolMode();	
}

void ircmd_rear_vol(void)
{
	nCurrentVolMode=VOL_MODE_REAR;
	IRSwitchVolMode();	
}

void ircmd_subwoofer_vol(void)
{
	nCurrentVolMode=VOL_MODE_SUBWOOFER;
	IRSwitchVolMode();	
}

void ircmd_treble_vol(void)
{
	nCurrentVolMode=VOL_MODE_TREBLE;
	IRSwitchVolMode();	
}

void ircmd_bass_vol(void)
{
	nCurrentVolMode=VOL_MODE_BASS;
	IRSwitchVolMode();	
}

void ircmd_balancefront_vol(void)
{
	static BYTE nCurrentFrontMode=VOL_MODE_MAIN_BALANCE_L;
	if (action_click)//chang adjust balance front r&l
    {
		if(nCurrentFrontMode==VOL_MODE_MAIN_BALANCE_L)
			nCurrentFrontMode=VOL_MODE_MAIN_BALANCE_R;
		else
			nCurrentFrontMode=VOL_MODE_MAIN_BALANCE_L;	
    }
	nCurrentVolMode=nCurrentFrontMode;
	IRSwitchVolMode();	
	
}

void ircmd_balancerear_vol(void)
{
	static BYTE nCurrentRearMode=VOL_MODE_SUR_BALANCE_L;
	if (action_click)//chang adjust balance front r&l
    {
		if(nCurrentRearMode==VOL_MODE_SUR_BALANCE_L)
			nCurrentRearMode=VOL_MODE_SUR_BALANCE_R;
		else
			nCurrentRearMode=VOL_MODE_SUR_BALANCE_L;	
    }
	nCurrentVolMode=nCurrentRearMode;
	IRSwitchVolMode();	
}
void ircmd_alarm(void)
{
	
}
#endif

#endif //#ifdef SUPPORT_AMP




#ifdef Ti3001_OSD_UI_1 //kenny for Ti 3001 amp control
void ircmd_amp_control(void)
{
	show_amp_control(USER_KEY_INPUT);
}

#endif

#ifdef Ti5026_OSD_UI_1 //kenny for Ti5026 amp control
void ircmd_amp_control(void)
{
	show_amp_control(USER_KEY_INPUT);
}
#endif





