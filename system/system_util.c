//
// FILE
// system_util.c
//


//
// FUNCTION
// wait_dsp_port0_5
//
BYTE wait_dsp_port0_5(int port0,int port5,int val,UINT32 risc_waiting_dsp_tm)
{
    UINT32 i;

    if(srv_on == 0) risc_waiting_dsp_tm = 0x1;//terry,2003/8/11 11:41AM
    
    for (i=0; i< risc_waiting_dsp_tm; i++) 
    {
         if ( (port0==0)||((regs0->dsp24_port[0] & 0x8000) == 0x8000) )
         {
            if( (port5==0)||(regs0->dsp24_port[5]==(UINT32)val) )//wanghaoying 2003-8-12 19:36 modified, please terry confirm
            {
              return 1;
            }
         }
        #if 0//def DVD_SERVO//servo-test 2004-5-3 16:47
        if(srv_on == 1)
            ServoDecMainLoop();// barry add for polling servo status
        #endif
    }    
    return 0;
}


//
// FUNCTION
// delay_srv_10ms(ms)
//
// DESCRIPTION
//
#define GET_RTC_15_0()  (regs0->rtc_15_0)
void delay_srv_10ms(int tms)
{
#if defined(SUPPORT_CARD_STORAGE)||defined(SUPPORT_USB)||defined(SPHE8202_CARD_STORAGE)
    if (media_type==MEDIA_CARD)  
    {
        delay_1ms(10*tms);
        return;
    }      
#endif

#ifndef DVD_SERVO
    delay_1ms(10*tms);
#else   
    if (srv_on==0)   
    {
        int i;
        for(i=0;i<tms;i++)
        {
           delay_1ms(10);
           
           //#ifdef HANYANG_SCAN_KEY
           //check_hanyang_keylight_status();
           //#endif
#if defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)
           check_minton_keylight_status();
#endif
        }
    }
    else
    { 
        int now,old = GET_RTC_15_0();
        int cnt = 0;
    
        do {
            now = GET_RTC_15_0();
            if(old!=now)
            {
                cnt++;
                old=now;
#if defined(USE_VFDPORT_TO_KEYLIGHT_MINTON)
                check_minton_keylight_status();
#endif
            
        //#ifdef HANYANG_SCAN_KEY
           //check_hanyang_keylight_status();
           //#endif
            }
        #ifdef DVD_SERVO
            ServoDecMainLoop();// barry add for polling servo status
        #endif
#ifdef HDMI
        HDCP_polling();//Modifed for avoid unknow recursion.chenzhao on 2004-12-14 16:21  
#endif
        }while(cnt<=tms);
   }
#endif   
}



#ifdef SUPPORT_DSPMUTE  // Kenny add 2005/4/21

static int mute_flag_count=0;
extern UINT32 coding_mode_now;

/**************************************************************************
 *                                                                          *
 *  Function Name: count_dsp_mute_flag                                      *
 *                                                                          *
 *  Purposes:                                                               *
 *      Count the dsp no data flag                                          *
 *  Descriptions:                                                           *
 *      This function is called in polling.c, 10 ms polling                 *
 *      regs0->dsp24_port is updated in 1 ms for 32 samples                 *           
 *      Variable mute_flag_count is as follows:                             *   
 *		 bit 10: mean mute GPIO should be active								*
 *       bit 9: mean mute flag is on                                        *
 *       bit 8: mean de-mute flag is on(De-mute GPIO should be active       *
 *       bit0~bit5: 32 samples no data count N, so total samples=N*32*10    *
 *  Arguments:                                                              *
 *      none                                                                *
 *  Returns:                                                                *
 *      None                                                                *
 *  See also:                                                               *
 *      None                                                                *
 *                                                                          *             
 *      Mute on                  _____turn on mute ?(in polling.c)          *
 *       |                      |      ___turn on de-mute?                  *
 *       |                      |     |                                     *
 *       [10*32\10*32\..........][10*32\10*32\..........]                   *
 *       |<10ms>|                |                      |                   *
 *       |<-  500ms polling    -><-  500ms polling     ->                   *
 ****************************************************************************/
void count_dsp_mute_flag(void)
{
	int no_data=0;
	int temp_count;

    //ycwen 2005/11/7 modify 1. Sepeate 8202D and 8202A/S  2. Taking care of AUDIF_CODING_MODE_NONE  
	#if defined (HW_SUPPORT_AUDIO_HW_DETECT_MUTE)
		if ( regs0->aud_pcm_bck_cfg&(1<<15))//64 samples is continous not changed
			no_data=1;
		else
			no_data=0;
	#else
	    if ( coding_mode_now == AUDIF_CODING_MODE_AC3 )    
        {            
            if ( (regs0->dsp24_port[14] & 0x3f)==0x3f)//32 samples is continous not changed
                no_data=1;
            else
                no_data=0; 
        }    
        if ((coding_mode_now == AUDIF_CODING_MODE_LPCM)||(coding_mode_now == AUDIF_CODING_MODE_PCM)||
            (coding_mode_now == AUDIF_CODING_MODE_MP3) ||(coding_mode_now == AUDIF_CODING_MODE_MP2)||
            (coding_mode_now == AUDIF_CODING_MODE_MP1) ||(coding_mode_now == AUDIF_CODING_MODE_NONE))
        {   
            if ( (regs0->dsp24_port[14] & 0x03)==0x03)
                no_data=1;
            else
                no_data=0;
        }          
	#endif

    //printf("X=%d\n",no_data);
    if(no_data)
    {
        temp_count=mute_flag_count&0xff; //bit7 is reserved for mute on flag
        if(temp_count < 0xff) //
        	temp_count++;
        else
        	temp_count=0xff;
     
		if(mute_flag_count==0)
		{
			mute_flag_count= (temp_count & 0xff )| 0x600; //set bit10 is "1" to mean GPIO mute is on,clear bit 8 de-mute flag
			//  printf("X=%x " ,mute_flag_count);
		}   
		else
		    mute_flag_count= (mute_flag_count&0x600)|(temp_count & 0xff )| 0x200; //clear bit 8 de-mute flag, set bit 9 mean mute need to be keep
    }
    else
    {
        if (mute_flag_count&0x200) //last time, it is mute
            mute_flag_count=0x100;//turn on bit 6 mean, de-mute on
        else
            mute_flag_count=0;
    }
}


int get_dsp_mute_flag_count(void)
{
    return mute_flag_count;
    
}   


void set_dsp_mute_flag_count(int i)
{
    mute_flag_count=i;
    
}   


void reset_mute_flag(void)
{
    mute_flag_count=0;
}   

#endif


