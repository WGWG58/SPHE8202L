/*
** vfd-utility file
** Creater: wanghaoying 2004-7-19 16:27
** 
**
*/



#if  defined(TWO_FUN_IN_ONE_VFD_KEY) || defined(TWO_FUNC_IN_LEFT_RIGHT_KEY)||defined(HOLD_VOL_KEY_FAST_REPEAT)  //xyy add for Oritron 2004-11-12
UINT32 keycode_to_num(UINT32 key_data)
{
	UINT32 temp;
	UINT8	i;
	
	for(i = 0; i < 24; i++)
	{
		temp = 0x01 << i;
		if(key_data & temp)
		{
			if (key_data > temp) 
			{
				return 0;
			}
			else
			{
				key_data = i + 1;
				break;
			}
		}
	}
	return key_data; 
}
#endif //TWO_FUN_IN_ONE_VFD_KEY


/*
** freyman 2002-7-4 11:27
** 
** FUNCTION
** polling_vfdtime
**
** DESCRIPTION
** checking VFD timeout, every time 'diff' RTC ticks is subtracted
** from VFD timeout.
**
** NOTES: if timeout value is 0 then this check is ignored.
**
*/
#if defined(VFD_VOLUME_DISPLAY) || defined(SUPPORT_TUNER_MV114) || defined(SUPPORT_TUNER_ALPS)
void polling_vfdtime(int diff)
{
	//      int    i;
	int     TimeToLive;
	
	if(diff < 0)
		return;
	else if(diff > 100)
		diff = 100;

	//printf("timeout : %d  diff:%d\n", timeout_vfd, diff);
	if((TimeToLive = timeout_vfd) != 0)
	{
		if((TimeToLive -= diff) <= 0)
		{
			TimeToLive = 0;
		}
		timeout_vfd = TimeToLive;
	}
}
#endif

///********VFD Volume display******** 
//wangfeng 2003-09-29 15:47
#ifdef	VFD_VOLUME_DISPLAY
UINT16 vfd_set_volume(UINT16 index)
{
	BYTE    iVolume;
    BYTE    idVolumeFont;
	erase_vfd_mem();
	
#ifdef	CNTR_5SPK_VOLUME
	if (volume_Switch>=0) {
            iVolume         = volume_5SPK[volume_Switch];
            idVolumeFont    = idVolume_5SPK[volume_Switch];
        } 
    else {
            iVolume         = audio_volume;
            idVolumeFont    = Volume_Font_ID;
        }
	if(idVolumeFont==VOL_FL_ID)
		psprintf(linebuf,"FL VOL%02d",iVolume);
	else if(idVolumeFont==VOL_FR_ID)
		psprintf(linebuf,"FR VOL%02d",iVolume);
	else if(idVolumeFont==VOL_SL_ID)
		psprintf(linebuf,"SL VOL%02d",iVolume);
	else if(idVolumeFont==VOL_SR_ID)
		psprintf(linebuf,"SR VOL%02d",iVolume);
	else if(idVolumeFont==VOL_C_ID)
		psprintf(linebuf,"CENVOL%02d",iVolume);
	else if(idVolumeFont==VOL_SW_ID)
		psprintf(linebuf,"SW VOL%02d",iVolume);//WANGFENG 2003-10-28 14:08
	else {
	    #ifdef MAIN_VOL_20// defined(HIMAGE1251) || defined(HIMAGE1250_03_185W)//wangfeng 2003-10-31 21:44
			if(volume_Switch==0)
			psprintf(linebuf,"VOL %02d",iVolume/4);
			else
	    #endif
			psprintf(linebuf,"VOL %02d",iVolume);
	    }
		
    #else   //CNTR_5SPK_VOLUME
	iVolume         = audio_volume;
    psprintf(linebuf,"VOL %02d",iVolume);//((80-5*(15-audio_volume))/5-1));
    #endif	//CNTR_5SPK_VOLUME
	vfd_set_str(0,linebuf);
	return index;	
}
#endif  //VFD_VOLUME_DISPLAY

#if defined(PCM1742)&&defined(CHECK_DAC_ZERO_FLAG_TO_GPIO_MUTE)		//gerry,3-10-20 11:36

void check_pcm1742_zero_flag(void)
{
	//printf("============= come here to mute=============\n");
	
	if((GPIO_I_GET(14))&&(setup_IsMICOff()))
	{
		//mute
		//printf("=== mute ======\n");
		GPIO_MUTE();
	}
	else
	{	
		//de-mute
		//printf("============= de mute=============\n");
		GPIO_DEMUTE();
	}
}
#endif

#ifdef SUPPORT_VFD_MESSAGE //chenzhao 20060117
    #ifdef SHOW_VOL_ON_VFD
    void exit_channel_volume(void);
    #endif
    #ifdef SUPPORT_VFD_SHOW_TONE
    void init_amp_tone_mode(void);
    #endif
    #ifdef SUPPORT_VFD_MENU
    void vfd_menu_message_restore(void);
    void vfd_menu_message_exit(void);
    #endif
void exit_last_vfd_message_state(void)
{
    switch(vfd_message_state)
    {
        #ifdef SHOW_VOL_ON_VFD
        case VFD_MESSAGE_VOL:
            exit_channel_volume();
            break;
        #endif
        
        #ifdef SUPPORT_VFD_SHOW_TONE
        case VFD_MESSAGE_EQ:
            #ifdef TREBLE_BASS_EQ_MENU_INTERFACE
            init_amp_tone_mode();
            #endif
            break;
        #endif
        
        default:
            break;
    }
}
void set_vfd_message_state(BYTE state,BYTE time)
{
    if(vfd_message_state!=state)
        exit_last_vfd_message_state();
    vfd_message_state=state;
    vfd_message_timeout=time;
}
void polling_vfd_message_time(void)
{
    if(vfd_message_timeout>0)
    {
        vfd_message_timeout--;
        if(0==vfd_message_timeout)
        {
            exit_last_vfd_message_state();
            #ifdef SUPPORT_VFD_MENU
            if(vfd_message_state == VFD_MESSAGE_MENU)
            {
                vfd_message_state = VFD_MESSAGE_IDLE;
                vfd_menu_message_exit();
            }
            else
            {
                vfd_message_state = VFD_MESSAGE_IDLE;
                vfd_menu_message_restore();
            }
            #else
            vfd_message_state = VFD_MESSAGE_IDLE;
            #endif
        }
    }
}
#endif



