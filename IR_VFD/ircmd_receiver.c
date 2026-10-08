#ifdef SUPPORT_RECEIVER  //huziqin 2004-2-26

//#define DEBUG_VOLUME
#include "auddrv.h"
 #if defined(SUPPORT_RECEIVER_MODE_MEMORY)
 void save_rcvr_mode(BYTE mode);
 #endif

 void ircmd_mode_stop ()
 {
	if (t_disp) {
          DispFadeOut();
          disp_mode=0;
    	}
    	if (current_rcvr_mode == RECEIVER_MODE_DVD)
    	{
            #if defined(SAME_DISC_RESUME) 
            	RsmInfo2Flash(0);
            #endif
            #ifdef PARENT_RESUME_NEED_PASSWORD//hongfeng add  2006/3/8
	            PassWord_OK = 0;
            #endif    

		    #ifdef NEWSTYLE_WINDOW
		        if(full_scrn==MESSAGE)//xyy 2004-3-4 10:43
		            exit_browse_func();
		    #endif
		    if(full_scrn==SOUND)
		        cancel_sound();
			else if(full_scrn&PROGRAM)
		        prog_func_off(); 
         
                        
            #ifdef NEW_PARENTAL_GUI//chenzhao20060214
            extern int user_input_pwd;
            extern BYTE new_parental_gui;
            extern void ExitParentalGUI(void); 
            if(new_parental_gui)
            {
               ExitParentalGUI(); 
               user_input_pwd=2;
                    }
            #endif//#ifdef NEW_PARENTAL_GUI
            if((full_scrn&SETUP)||(full_scrn&CUSTM))//chenzhao20060224
                ExitSetupPage(1);   
            #if defined(SCALER_6500)//chenzhao 2006-3-4 13:40 .
            	extern UINT8 CSSEnable;
            	CSSEnable=0;
            #endif
            #ifdef MULTIDISC_LOADER//chenzhao20060209
            	multidisc_swith_receiver_mode_close();
            #endif
            
    	// Simon 12-15-2003
    	// This is a fake eject	
 		ircmd_post_func(CMD_FUNC | CMD_FUNC_OPEN);
		play_state = VCD_STATE_STOP;
		playmode_sel(CLEAR_ALL);
			
		#if !defined(MULTIDISC_LOADER)&&!defined(POWER_ON_SERVO_STOP)//hongfeng add 2006/3/8 
			open_tray();
		#endif
			
		stop_loader();	
	}
	else
	{
		system_state = SYSTEM_OPEN;
	}
 }

 #ifdef SUPPORT_SETUP_POPUP_MEDIA_GUI
 extern void show_setup_popup_media_gui(void);
 #endif
 void ircmd_rcvr_select_mode(int mode)
 {
     safe_srn_off();
 	//UINT8 door;
 	//door = atapi_p_mechanism_status();//chenzhao20060107
 	if ((current_rcvr_mode == RECEIVER_MODE_DVD))//&&(door == ATAPI_DOOR_OPEN))
 	{
        #ifdef SELECT_DVD_NEXT_DISC_IN_A_KEY//chenzhao20060112
        if(next_disc_func())
        {}
        else
        #endif
        #if defined(SUPPORT_SETUP_POPUP_MEDIA_GUI) && defined(SELECT_DVD_MEDIA_IN_A_KEY)
        if((full_scrn==0)&&(storage_type!=0)&&(play_state!=VCD_STATE_READTOC)&&(play_state!=VCD_STATE_CLOSE))//chenzhao20051110
        {
            need_popup_menu=2;
            show_setup_popup_media_gui();
        }
        else
        #endif
        {
 		    invalid_key();
        }
 	}
 	else
 	{
 	next_rcvr_mode = mode;
 	switch_modes_now = 1;
 	ircmd_mode_stop();
    #if defined(SUPPORT_RECEIVER_MODE_MEMORY)
    save_rcvr_mode(next_rcvr_mode);
    #endif
 }
 }

 void ircmd_rcvr_next_mode(void)
 {
 	// Find next supported mode
 	BYTE found = 0;
 	//printf("mode %d\n",next_rcvr_mode);
    printf("ircmd_rcvr_next_mode\n");

 	next_rcvr_mode = current_rcvr_mode + 1;

 	while (found == 0) {
	    	if (next_rcvr_mode == NUM_MODES_MAX) 
	    	{
	    		next_rcvr_mode = 0;
	    	}
	    	if (rcvr_support_bits & (1 << next_rcvr_mode))
	    	{
	    		found = 1;	
	    	}
	    	else
	    	{
	    		next_rcvr_mode++;
	    	}
	}
 	switch_modes_now = 1;
 	ircmd_mode_stop();
    #if defined(SUPPORT_RECEIVER_MODE_MEMORY)
    save_rcvr_mode(next_rcvr_mode);
    #endif
}
void ircmd_rcvr_function_mode(void)//chenzhao20060120
{
    BYTE found = 0;
    printf("ircmd_rcvr_function_mode\n");
    if(current_rcvr_mode == RECEIVER_MODE_DVD)
    {
        next_rcvr_mode = last_non_dvd_rcvr_mode;
    }
    else
    {
        next_rcvr_mode = current_rcvr_mode + 1;
    }
    
    while (found == 0) 
    {
        if (next_rcvr_mode == NUM_MODES_MAX) 
        {
            next_rcvr_mode = 0;
        }
        if ((rcvr_support_bits & (1 << next_rcvr_mode))&&(next_rcvr_mode != RECEIVER_MODE_DVD))
        {
            found = 1;  
        }
        else
        {
            next_rcvr_mode++;
        }
    }
 	switch_modes_now = 1;
 	ircmd_mode_stop();
    #if defined(SUPPORT_RECEIVER_MODE_MEMORY)
    save_rcvr_mode(next_rcvr_mode);
    #endif
}

#ifdef SUPPORT_VIDEO_WITH_SPDIF
 void ircmd_rcvr_analog_digital(void)
 {
 	if ((current_rcvr_mode != RECEIVER_MODE_AV1) ||
 		(current_rcvr_mode != RECEIVER_MODE_AV2))
 	{
 		invalid_key();
 	}
 	else {
 	// Switch between analog and digital inputs
 	}
}
#endif


/*the amplifier function moved to amp_gui.c    xyy 2004-8-3*/

#ifdef DOLBY_AMP_VOLUME_CTRL
void  ircmd_set_treble()
{
#ifdef SUPPORT_APOGEE_AMP
//	 ddx_OSDTrebleAdjust();
#endif
}
void  ircmd_set_bass()
{
#ifdef SUPPORT_APOGEE_AMP
//    ddx_OSDBassAdjust();
#endif
}
#endif

#ifdef SUPPORT_EX_BASS_FUNC//chenzhao20060117
void ircmd_ex_bass_func(void)
{
    amp_toggle_ExBass();
}
#endif

#ifdef  NO_INTERNAL_VOLUME_CTRL
void  ircmd_volume_up(void)
{
/*Here deleted by xyy 2004-8-5*/

	subvol_vol_up();
	/*tell vfd to show volume*/
	//subvol_time_out = 10; //move to subvol_vol_up()

}

void  ircmd_volume_down(void)
{
/*Here deleted by xyy 2004-8-5*/
	subvol_vol_down();

	/*tell vfd to show volume*/
	//subvol_time_out = 10;//move to subvol_vol_down()
	
}

#endif  //NO_INTERNAL_VOLUME_CTRL


#ifdef USE_PROLOGIC_II_KEY_FOR_SURROUND /*huziqin*/
#ifdef USE_PROLOGIC_II_KEY      //clead 2003-8-7
extern BYTE vfd_show_ch_msg;
extern BYTE vfd_backup_on;
extern void exe_setup_function(UINT8 tt_id, UINT8 sub_id, UINT8 exe);
extern void set_prologic_init_val(BYTE prologic_mode);
#define FIRST_PROLOGIC_MODE 0
#ifdef USE_PL2_3DSURROUND_KEY
#define FIRST_3DSOUND_MODE  3
#define MAX_3DPAGE_ITEM   4
#define MAX_3DITEM_SEL    11
extern UINT8 sound_sel[MAX_3DPAGE_ITEM];
extern const UINT8 sound_item[MAX_3DPAGE_ITEM][MAX_3DITEM_SEL];
#define surround_3d_val     sound_sel[0]
#define surround_3d_item    sound_item[0]
#define OFF_3DSOUND_MODE    2
#endif//#ifdef USE_PL2_3DSURROUND_KEY
//extern BYTE bHpPlug;
void I2c_write_surrond_mode()
{
    WriteToI2c(0xa0,SURROUND_MODE_ADDR,&surround_mode,1);
    #ifdef USE_PL2_3DSURROUND_KEY
    if(surround_mode==SURROUND_MODE_3D)
        WriteToI2c(0xa0,PROLOGIC_MODE_ADDR,&surround_3d_val,1);
    else
        WriteToI2c(0xa0,PROLOGIC_MODE_ADDR,&prologic_val,1);
    #else//#ifdef USE_PL2_3DSURROUND_KEY
    WriteToI2c(0xa0,PROLOGIC_MODE_ADDR,&prologic_val,1);
    #endif//#ifdef USE_PL2_3DSURROUND_KEY
}
void I2c_read_surround_mode()
{
    ReadFromI2c(0xa0,SURROUND_MODE_ADDR,&surround_mode,1);
    #ifdef USE_PL2_3DSURROUND_KEY
    if(surround_mode==SURROUND_MODE_3D)
    {
        ReadFromI2c(0xa0,PROLOGIC_MODE_ADDR,&surround_3d_val,1);
        prologic_val=PROLOGIC_MODE_OFF;
    }
    else
        ReadFromI2c(0xa0,PROLOGIC_MODE_ADDR,&prologic_val,1);
    #else//#ifdef USE_PL2_3DSURROUND_KEY
    ReadFromI2c(0xa0,PROLOGIC_MODE_ADDR,&prologic_val,1);
    #endif//#ifdef USE_PL2_3DSURROUND_KEY
}
inline BYTE Is_Multi_Channel_Source(void)
{
	return 
        (IS_AUDIF_CODING_MODE_DTS || IS_AUDIF_CODING_MODE_DTSCD || IS_AUDIF_CODING_MODE_SPDIFINDTS)
        ||((cd_type_loaded==CDDVD)&&(pDSV->dNs_Audio_ch>1))
        ||((cd_type_loaded==CDROM)&&IS_AUDIF_CODING_MODE_AC3)
        #if (defined(SUPPORT_SPDIF_IN)||defined(SUPPORT_COAXIAL_IN))//hongfeng add 2005-12-30
        ||(IS_AUDIF_CODING_MODE_SPDIFINAC3&&spdif_in_channel)
        #endif
        ;
}
inline BYTE Is_Speaker_All_On(void)
{
    return (speaker_center!=SPEAKER_OFF)&&(speaker_surround!=SPEAKER_OFF);
}
#ifdef SUPPORT_VFD_SHOW_SURROUND_MODE
void set_vfd_message_state(BYTE state,BYTE time);
#endif
void surround_switch()
{
    //moved to ircmd_prologic().chenzhao20060227
    switch(surround_mode)
    {
        case SURROUND_MODE_5CH:
            if(Is_Multi_Channel_Source())
            {
                #ifdef USE_PL2_KEY_SWITCH_SPEAKER
                surround_mode=SURROUND_MODE_2CH;
                prologic_val = PROLOGIC_MODE_OFF;
                #endif//#ifdef USE_PL2_KEY_SWITCH_SPEAKER
                printf("surround_switch Is_Multi_Channel_Source\n");
            }
            else
            {
                prologic_val++;
                if(prologic_val>PROLOGIC_MODE_OFF) 
                prologic_val = FIRST_PROLOGIC_MODE;

                #ifdef DETECT_SPEAKER_SIZE_TO_CHECK_PLII            
                //when center / surround speaker off, no prologic 2 mode , jump 3D effect.
                if(!Is_Speaker_All_On())
                prologic_val = PROLOGIC_MODE_OFF;
                #endif

                #ifdef USE_PL2_3DSURROUND_KEY
                if (prologic_val == PROLOGIC_MODE_OFF)
                {
                surround_mode = SURROUND_MODE_3D;
                surround_3d_val=FIRST_3DSOUND_MODE;
                }
                #else//#ifdef USE_PL2_3DSURROUND_KEY
                if (prologic_val == PROLOGIC_MODE_OFF)
                surround_mode = SURROUND_MODE_2CH;
                #endif//#ifdef USE_PL2_3DSURROUND_KEY
                printf("surround_switch SURROUND_MODE_5CH\n");
            }
            break;

        #ifdef USE_PL2_3DSURROUND_KEY
        case SURROUND_MODE_3D:
            surround_3d_val++;
            if((surround_3d_item[surround_3d_val]==0)||(surround_3d_val>=MAX_3DITEM_SEL))
            {
                surround_mode = SURROUND_MODE_2CH;
                surround_3d_val=OFF_3DSOUND_MODE;
                printf("surround_switch SURROUND_MODE_3D\n");
            }
            break;
        #endif//#ifdef USE_PL2_3DSURROUND_KEY

        case SURROUND_MODE_2CH:
        default:

            #ifdef USE_PL2_KEY_SWITCH_SPEAKER
            surround_mode=SURROUND_MODE_5CH;
            prologic_val = FIRST_PROLOGIC_MODE;
            #else
            if(!Is_Multi_Channel_Source())
            {
                #ifdef DETECT_SPEAKER_SIZE_TO_CHECK_PLII            
                if(!Is_Speaker_All_On())
                {
                    #ifdef USE_PL2_3DSURROUND_KEY
                    surround_mode = SURROUND_MODE_3D;
                    surround_3d_val=FIRST_3DSOUND_MODE;
                    #else
                    surround_mode=SURROUND_MODE_2CH;
                    prologic_val = PROLOGIC_MODE_OFF;
                    #endif//#ifdef USE_PL2_3DSURROUND_KEY
                }
                else
                #endif
                {
                    surround_mode=SURROUND_MODE_5CH;
                    prologic_val = FIRST_PROLOGIC_MODE;
                }
            }
            #endif

            break;
    }

    I2c_write_surrond_mode();
    //moved to ircmd_prologic()//chenzhao20060225
}

void show_prologic(void)
{
        //UINT8 id=0;

        switch(prologic_val)
                {
                case PROLOGIC_MODE_MOVIE:
                    //vfd_set_str(0,"MOVIE  ");
                    #ifdef USE_PL2_3DSURROUND_KEY
                    psprintf(RegionValStr[REGION1],"PROLOGIC II MOVIE");
                    #else
                    psprintf(RegionValStr[REGION1],"MOVIE");
                    #endif
                    PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                    //set_prologic_val(prologic_val);
                    break;
                case PROLOGIC_MODE_MUSIC:
                    //vfd_set_str(0,"MUSIC  ");
                    #ifdef USE_PL2_3DSURROUND_KEY
                    psprintf(RegionValStr[REGION1],"PROLOGIC II MUSIC");
                    #else
                    psprintf(RegionValStr[REGION1],"MUSIC");
                    #endif
                    PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                    //set_prologic_val(prologic_val);
                    break;
                case PROLOGIC_MODE_OFF:
                    //vfd_set_str(0,"STEREO ");
                    #if 0//def USE_PL2_3DSURROUND_KEY
                    psprintf(RegionValStr[REGION1],"SURROUND OFF");
                    #else
                    psprintf(RegionValStr[REGION1],"STEREO");
                    #endif
                    PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                    //set_prologic_val(prologic_val);
                    break;
                case PROLOGIC_MODE_EMU:
                    
                    //vfd_set_str(0,"PROLOGIC");
                    psprintf(RegionValStr[REGION1],"PROLOGIC");
                    PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                    //set_prologic_val(prologic_val);
                    break;
                case PROLOGIC_MODE_VIRTUAL:
                    //vfd_set_str(0,"VIRTUAL ");
                    psprintf(RegionValStr[REGION1],"VIRTUAL");
                    PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                    //set_prologic_val(prologic_val);
                    break;
                case PROLOGIC_MODE_MATRIX:
                    //vfd_set_str(0,"MATRIX ");
                    psprintf(RegionValStr[REGION1],"MATRIX");
                    PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                    //set_prologic_val(prologic_val);
                    break;   

           } 
}

#ifdef USE_PL2_3DSURROUND_KEY
void show_3dsound(void)
{
    PrintOsdMsg(surround_3d_item[surround_3d_val],REGION1,1,0);
}
#endif//#ifdef USE_PL2_3DSURROUND_KEY

void surround_exe(BYTE show_mode)//2:init dsp val,1 show message in OSD & VFD;0 no show message
{
    //UINT8 id=0;
    #ifdef SUPPORT_HEADPHONE
    if (bHpPlug) 
    {
        #if !defined(HEADPHONE_USE_LMRM)//chenzhao20060223
        //prologic_val = PROLOGIC_MODE_OFF;
        if(show_mode==2)
            set_prologic_init_val(PROLOGIC_MODE_OFF);
        else
        {
            set_prologic_val(PROLOGIC_MODE_OFF);
            exe_setup_function(STR_OS_DOWNMIX_SETUP,STR_OS_STEREO,1);
            AUDIF_Set_OutputMode(OUT_51DownmixL0R0,0);
        }
        #endif
        return;
    }
    #endif
    
    #define STATE_NOT_CHANGE 0
    #define RUN_PROLOGIC_ON 1
    #define RUN_PROLOGIC_OFF 2
    #define RUN_3DSOUND_ON 1
    #define RUN_3DSOUND_OFF 2
    #define RUN_SPEAKER_ALL_ON 1
    #define RUN_SPEAKER_C_S_OFF 2
    #define RUN_SWITCH_MODE_MUTE 1
    #ifdef AVOID_SURROUND_KEY_POP_NOISE//chenzhao20060225
    #define run_command_delay() if(show_mode==1)delay_srv_10ms(5);
    #else
    #define run_command_delay() {}
    #endif
    #ifdef USE_PL2_KEY_SWITCH_SPEAKER
    BYTE run_speaker=STATE_NOT_CHANGE;
    #endif//#ifdef USE_PL2_KEY_SWITCH_SPEAKER
    BYTE run_prologic=STATE_NOT_CHANGE;
    BYTE run_3dsound=STATE_NOT_CHANGE;
    BYTE run_switch_mute=(show_mode==1)?RUN_SWITCH_MODE_MUTE:STATE_NOT_CHANGE;
    if(Is_Multi_Channel_Source())
    {
        #ifdef USE_PL2_KEY_SWITCH_SPEAKER
        if(SURROUND_MODE_2CH==surround_mode)
            run_speaker=RUN_SPEAKER_C_S_OFF;
        else
            run_speaker=RUN_SPEAKER_ALL_ON;
        #else
        run_switch_mute=STATE_NOT_CHANGE;
        #endif//#ifdef USE_PL2_KEY_SWITCH_SPEAKER
        run_prologic=RUN_PROLOGIC_OFF;
        if(show_mode==1)
        {
            #ifdef USE_PL2_KEY_SWITCH_SPEAKER
            	//printf("surround_mode %d \n",surround_mode);
            	if(SURROUND_MODE_2CH==surround_mode)
                {
					 psprintf(RegionValStr[REGION1],"STEREO");
            	}
            	else
                {
                    if(IS_AUDIF_CODING_MODE_DTS || IS_AUDIF_CODING_MODE_DTSCD|| IS_AUDIF_CODING_MODE_SPDIFINDTS)
		                psprintf(RegionValStr[REGION1],"DTS");  
                    else if(IS_AUDIF_CODING_MODE_AC3|| IS_AUDIF_CODING_MODE_SPDIFINAC3)
                        psprintf(RegionValStr[REGION1],"DOBLY DIGITAL");
                    else 
                        psprintf(RegionValStr[REGION1],"5.1");
	        	}
	            PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);      
            #else
            invalid_key();
            #endif//#ifdef USE_PL2_KEY_SWITCH_SPEAKER
            run_3dsound= RUN_3DSOUND_OFF;
        }
        printf("surround_exe Is_Multi_Channel_Source\n");
    }
    else
        switch(surround_mode)
        {
            case SURROUND_MODE_5CH:
                #ifdef USE_PL2_KEY_SWITCH_SPEAKER
                    run_speaker=RUN_SPEAKER_ALL_ON;
                #endif//#ifdef USE_PL2_KEY_SWITCH_SPEAKER
                
                #ifdef DETECT_SPEAKER_SIZE_TO_CHECK_PLII            
                //when center / surround speaker off, no prologic 2 mode , jump 3D effect.
                if(!Is_Speaker_All_On()&&(show_mode!=1))
                    {
                    run_prologic=RUN_PROLOGIC_OFF;
                    printf("surround_exe not Is_Speaker_All_On\n");
                    }
                else
                #endif
                run_prologic=RUN_PROLOGIC_ON;
                
                #ifndef AVOID_SURROUND_KEY_POP_NOISE//chenzhao20060225
                run_3dsound= RUN_3DSOUND_OFF;
                #endif
                
                if(show_mode==1)
                    show_prologic();
                //moved to below.chenzhao20060225
                printf("surround_exe SURROUND_MODE_5CH\n");
                break;
                
            #ifdef USE_PL2_3DSURROUND_KEY
            case SURROUND_MODE_3D:
                run_prologic=RUN_PROLOGIC_OFF;
                run_3dsound= RUN_3DSOUND_ON;
                if(show_mode==1)
                    show_3dsound();
                printf("surround_exe SURROUND_MODE_3D\n");
                break;
            #endif//#ifdef USE_PL2_3DSURROUND_KEY
            
            case SURROUND_MODE_2CH:
            default:
                run_prologic=RUN_PROLOGIC_OFF;
                run_3dsound= RUN_3DSOUND_OFF;
                if(show_mode==1)
                {
                    psprintf(RegionValStr[REGION1],"STEREO");
                    PrintOsdMsg(STR_OS_SPACE,REGION1,1,1);
                }
                printf("surround_exe SURROUND_MODE_2CH\n");
                break;
        }
        
    if(action_click || (show_mode!=1))//chenzhao20060303
    {
        if(run_switch_mute==RUN_SWITCH_MODE_MUTE)
        {
            #if defined(AVOID_SURROUND_KEY_POP_NOISE)//chenzhao20060225
            AUDIF_RampDown_DSP(1);
            AUDIF_RampWait_DSP();
            #endif
            AUDIF_Set_Volume(0);
        }
        #ifdef USE_PL2_KEY_SWITCH_SPEAKER
        if(run_speaker!=STATE_NOT_CHANGE)
        {
            if(run_speaker==RUN_SPEAKER_C_S_OFF)
            {//downmix to 2.1
                speaker_center=SPEAKER_OFF;
                speaker_surround=SPEAKER_OFF;
                printf("surround_exe RUN_SPEAKER_C_S_OFF\n");
            }
            else if(run_speaker==RUN_SPEAKER_ALL_ON)
            {//set speaker to 5.1
                speaker_center=SPEAKER_SMALL;
                speaker_surround=SPEAKER_SMALL;
                printf("surround_exe RUN_SPEAKER_ALL_ON\n");
            }
            if(show_mode<2)
            {
                //run_save_sel_cmd(setup_VA[SETUP_VA_CSPK], SETUP_VA_CSPK);
                //run_save_sel_cmd(setup_VA[SETUP_VA_SSPK], SETUP_VA_SSPK);
                AUDIF_Set_BassConfig(0, 0);//parameter unused
            }
        }
        #endif//#ifdef USE_PL2_KEY_SWITCH_SPEAKER
        
        #if defined(AVOID_SURROUND_KEY_POP_NOISE)//chenzhao20060225
        if(run_prologic==RUN_PROLOGIC_OFF && (pl2_init_val!=PROLOGICII_OFF_DSP_INIT))
        #else
        if(run_prologic==RUN_PROLOGIC_OFF)
        #endif
        {
            if(show_mode==2)
                set_prologic_init_val(PROLOGIC_MODE_OFF);
            else
                set_prologic_val(PROLOGIC_MODE_OFF);
            run_command_delay();
            printf("surround_exe RUN_PROLOGIC_OFF\n");
        }
        else if(run_prologic==RUN_PROLOGIC_ON)
        {
            if(show_mode==0)//(show_mode<2)chenzhao20060225 avoid pop noise
            {
                exe_setup_function(STR_OS_DOWNMIX_SETUP,STR_OS_OFF,1);
                AUDIF_Set_OutputMode(OUT_51Channel,0);
            }
            if(show_mode==2)
                set_prologic_init_val(prologic_val);
            else
                set_prologic_val(prologic_val);
            run_command_delay();
            printf("surround_exe RUN_PROLOGIC_ON\n");
        }
        
        #ifdef USE_PL2_3DSURROUND_KEY
        if(run_3dsound==RUN_3DSOUND_ON)
        {
            if(show_mode!=2)
            {
                AUDIF_Set_Surround(surround_3d_val-2);
                run_command_delay();
            }
            printf("surround_exe RUN_3DSOUND_ON\n");
        }
        else if(run_3dsound == RUN_3DSOUND_OFF)
        {
            AUDIF_Set_Surround(OFF_3DSOUND_MODE-2);
            run_command_delay();
            printf("surround_exe RUN_3DSOUND_OFF\n");
        }
        #endif//#ifdef USE_PL2_3DSURROUND_KEY

        if(run_switch_mute==RUN_SWITCH_MODE_MUTE)
        {
            #if defined(AVOID_SURROUND_KEY_POP_NOISE)//chenzhao20060225
            AUDIF_RampUp_DSP(1);
            #endif
            AUDIF_Demute();
        }
    }
}

void surround_init(void)
{
    I2c_read_surround_mode();
    //surround_exe_nomsg();
    surround_exe(0);
}
void surround_reset(void)
{
#if defined(DEFAULT_PLII_PROLOGIC_MOVIE)	
	surround_mode = SURROUND_MODE_5CH; 
    prologic_val  = PROLOGIC_MODE_MOVIE;
#else
    #ifdef USE_PL2_KEY_SWITCH_SPEAKER//chenzhao20060211
    surround_mode = SURROUND_MODE_5CH; // default set to prologic off
    #else
    	surround_mode = SURROUND_MODE_2CH;
    #endif//#ifdef USE_PL2_KEY_SWITCH_SPEAKER
    
    prologic_val = PROLOGIC_MODE_OFF;
#endif    
    #ifdef USE_PL2_3DSURROUND_KEY
    	surround_3d_val=OFF_3DSOUND_MODE;
    #endif//#ifdef USE_PL2_3DSURROUND_KEY
    
    I2c_write_surrond_mode();
}

void ircmd_prologic(void)
{
    #if defined(SUPPORT_HEADPHONE)//chenzhao20060227
    if (bHpPlug) 
    {
        invalid_key();
        return;
    }
    #endif
    if(action_click)//chenzhao20060220
    surround_switch();
    
    //vfd_set_surround_mode();
    //vfd_backup();
    //erase_vfd_mem();
    #ifdef SUPPORT_VFD_SHOW_SURROUND_MODE//chenzhao20060225
    #ifndef USE_PL2_KEY_SWITCH_SPEAKER//chenzhao20060224
    if(!Is_Multi_Channel_Source())
    #endif
        set_vfd_message_state(VFD_MESSAGE_SURROUND,4);
    #endif
    surround_exe(1);
}
#endif 
#endif //USE_PROLOGIC_II_KEY_FOR_SURROUND

#ifdef PANEL_VOLUME_ENCODER
inline BYTE get_volumeEncode_1(void)
{
	#ifdef USE_IO_CNT_VOL_ENCODER
		if(GPIO_I_GET(11)) //pin69
	#else	
		if(rom_bus_get_io(ROM_BUS_IN_ENCODE1))
	#endif	
			return 1;
		return 0;	
}
inline BYTE get_volumeEncode_2(void)
{
	#ifdef USE_IO_CNT_VOL_ENCODER
		if(GPIO_I_GET(12)) //pin71
	#else	
		if(rom_bus_get_io(ROM_BUS_IN_ENCODE2))
	#endif	
			return 1;
		return 0;	
}
#endif

#if defined(PANEL_VOLUME_ENCODER)||(defined(TMM_VOL_PANEL)||defined(XM_PANEL_VFD16315))	//chenzhao20060207
	#ifdef OSD_SCREEN_SAVER		//fcr 2005-11-22 18:46 
	extern UINT8  safe_on;
	#endif
    #ifdef PANEL_VOLUME_ENCODER//chenzhao20060117
    #include "rom_bus_io.h"
    #endif
inline void VolumeEncoder(void)
{
    BYTE status;
    static BYTE prev = 3;
    BYTE updown = 0;
    static BYTE up_cnt = 0;
    static BYTE down_cnt = 0;
    #if (defined(TMM_VOL_PANEL)||defined(XM_PANEL_VFD16315))
	status = (GPIO_I_GET(10)<<0)|(GPIO_I_GET(11)<<1);
    #elif defined(PANEL_VOLUME_ENCODER)
	status = ((get_volumeEncode_2()<<1)|(get_volumeEncode_1())) &0x03;
#endif
    #define gpio_vol_speed 1
    if(prev != status)
    {
        switch(prev)
{
        case 3:  //for vfd 6311 hongfeng 2005-03-05
            if (status == 1)
                updown = 2;    
            else if(status == 2)
                updown = 1;    
            break;

        case 1:  //for vfd 6311 hongfeng 2005-03-05
            if(status == 0)
                updown = 2;
            else if (status == 3)
                updown = 1;    
            break;

        case 0:  //for vfd 6311 hongfeng 2005-03-05
            if(status == 2)
                updown = 2;
            else if (status == 1)
                updown = 1;    
            break;
        
        case 2:  //for vfd 6311 hongfeng 2005-03-05
            if(status == 3)
                updown = 2;
            else if (status == 0)
                updown = 1;    
            break;   

       default:
            updown = 0;
            break;     
        }

        if(updown == 2)
        {
            down_cnt++;
            up_cnt = 0;     
            if(down_cnt >gpio_vol_speed)
            {
                down_cnt = 0;       
			#ifdef TESTSPK_IN_SETUP
          		#ifndef ONLY_TEST_TONE_KEY_EXIT//chenzhao2005-4-29
                if(testspk_state)
                   {
                   testspk_state=0;
	
                   return 1;
                   }
          		#endif
			#endif//TESTSPK_IN_SETUP
			#ifdef OSD_SCREEN_SAVER
				if(safe_on)
				{
					safe_srn_off();	//fcr 2005-11-15 13:26
					if ( (full_scrn&SETUP) || (full_scrn&CUSTM) ) 
			       	{
			       	#ifdef OP_PLAYMODE
			       		ExitSetupPage(1);	//disable for 5 minutes autoplay without screensaver.
			       	#else	
			            setup_save_exit();
			        #endif    
			       	}	
		return ;
				}
			#endif 
	
			if(t_disp)//by joke fixed dpl937 thomson bug# PD-A80
			{
				t_disp=t_disp%10;
				t_disp+=10;  
			}
			#ifdef ANEBLE_AUTO_EXIT_INFOBAR
				osd_infobar_exit_cnt = 0;
			#endif
		
			#if defined(XM_PANEL_VFD16315)||defined(PANEL_VOLUME_ENCODER)//chenzhao20060207
				ircmd_volume_down(); 
			#else                
                ircmd_volume_up();   
            #endif    	
            }
        }
	
        if(updown == 1)
        {
            up_cnt++;
            down_cnt = 0;    
            if(up_cnt >gpio_vol_speed)
            {
                up_cnt = 0;               
			#ifdef TESTSPK_IN_SETUP
          		#ifndef ONLY_TEST_TONE_KEY_EXIT//chenzhao2005-4-29
                if(testspk_state)
                   {
                   testspk_state=0;
	
                   return 1;
                   }
    #endif
			#endif//TESTSPK_IN_SETUP
			#ifdef OSD_SCREEN_SAVER
				if(safe_on)
				{
					safe_srn_off();	//fcr 2005-11-15 13:26
					if ( (full_scrn&SETUP) || (full_scrn&CUSTM) ) 
			       	{
			       	#ifdef OP_PLAYMODE
			       		ExitSetupPage(1);	// disable for 5 minutes autoplay without screensaver.
			       	#else	
			            setup_save_exit();
			        #endif    
			       	}	
		return ;
				}
			#endif 
		
			if(t_disp)//by joke fixed dpl937 thomson bug# PD-A80
	{
				t_disp=t_disp%10;
				t_disp+=10;  
	}
			#ifdef ANEBLE_AUTO_EXIT_INFOBAR
				osd_infobar_exit_cnt = 0;
			#endif
			
			#if defined(XM_PANEL_VFD16315)||defined(PANEL_VOLUME_ENCODER)//chenzhao20060207
				ircmd_volume_up(); 
			#else
		ircmd_volume_down(); 
            #endif    
	}  
}
        prev = status;  

    }
    //psprintf(RegionValStr[REGION1], "fcr--KNOB STATUS:%d ", status);
	//PrintOsdMsg(STR_OS_SPACE, REGION1, 1, 1);
}
#endif
#endif //SUPPORT_RECEIVER

