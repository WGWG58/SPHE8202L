#include "user_init.h"
#include "global.h"
#include "osd.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"

extern void setup_saveVal(void);

void
str_os_downmix_setup(int sub_id)
{
#ifdef DVD_SETUP_REENG	
	UINT16 P=0;
	UINT16 I=0;
#endif	
    if (sub_id==STR_OS_LTRT_SETUP) 
    {
        #ifndef AC3_BASS_MANAGEMENT
        downmix_off=0;
        #endif 
        AUDIF_Set_OutputMode(OUT_51DownmixLtRt, 0);//2004AUDDRV AudioSetOutputMode(0x08, 0); //Set Output mode(8:AC3 downmix Lt/Rt)
        if (full_scrn & SETUP)
            setup_ShowAC3Config();

        //set front speak gain to max., bec4 now the volume is controled only by master volume
        #ifdef CNTR_5SPK_VOLUME //wangfeng 2003-11-07 17:45
        AUDIF_Set_FSPKGain(DEFAULT_VOL);//2004AUDDRV AudioSetFSPKGain(40);  //jiangxl2005-3-11 17:26  for any grade volume set front speak gain to max.
        #else
        AUDIF_Set_FSPKGain(8);//2004AUDDRV AudioSetFSPKGain(8);
        #endif
        
 	#ifdef DVD_SETUP_REENG	//jslin	//20040827
        //if (setup_VA[SETUP_VA_KEY] != MIN_ITEM_SEL) {//(SETUP_KEY!=2) {
            //recover key-status
            AUDIF_Set_Key(setup_VA[SETUP_VA_KEY]);//2004AUDDRV AudioSetKey(setup_VA[SETUP_VA_KEY]); //audio_key:-6 ~ 6, map to 1~15
        //}
        #ifdef USE_SETUP_ITEM_ENABLE_FLAG
        setup_VA_EN[SETUP_VA_CSPK]=0;
        setup_VA_EN[SETUP_VA_SSPK]=0;
        #endif//USE_SETUP_ITEM_ENABLE_FLAG
    #else
        	//if (SETUP_KEY!=2) {
                //recover key-status
                AUDIF_Set_Key(SETUP_KEY);//2004AUDDRV AudioSetKey(SETUP_KEY); //audio_key:-6 ~ 6, map to 1~15
            //}
    #endif	//end of DVD_SETUP_REENG    
    } 
    else if (sub_id==STR_OS_STEREO) 
    {
        #ifndef AC3_BASS_MANAGEMENT
        downmix_off=0;
        #endif 
        AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(0x07, 0); //Set Output mode(7:AC3 downmix L0 R0)
        if ((full_scrn & SETUP)
        #ifdef AUDIO_2CH_5_1CH//zhaoyanhua 03-11-2 20:01
            || (ChannelFlag == 0)
        #endif
            )
            setup_ShowAC3Config();
    
        //set front speak gain to max., bec4 now the volume is controled only by master volume
        #ifdef VOL_80
        AUDIF_Set_FSPKGain(40);
        #endif        
        #ifdef CNTR_5SPK_VOLUME //wangfeng 2003-11-07 17:45
        AUDIF_Set_FSPKGain(DEFAULT_VOL);//2004AUDDRV AudioSetFSPKGain(40);//jiangxl2005-3-11 17:26
        #else
        AUDIF_Set_FSPKGain(8);//2004AUDDRV AudioSetFSPKGain(8);
        #endif

    #ifdef DVD_SETUP_REENG	//jslin	//20040827
        //if (setup_VA[SETUP_VA_KEY] != MIN_ITEM_SEL) {//(SETUP_KEY!=2) {
            //recover key-status
        AUDIF_Set_Key(setup_VA[SETUP_VA_KEY]);//2004AUDDRV AudioSetKey(setup_VA[SETUP_VA_KEY]); //audio_key:-6 ~ 6, map to 1~15
        //}
        #ifdef USE_SETUP_ITEM_ENABLE_FLAG
        setup_VA_EN[SETUP_VA_CSPK]=0;
        setup_VA_EN[SETUP_VA_SSPK]=0;
        #endif//USE_SETUP_ITEM_ENABLE_FLAG
    #else
        //if (SETUP_KEY!=2) {
                //recover key-status
            AUDIF_Set_Key(SETUP_KEY);//2004AUDDRV AudioSetKey(SETUP_KEY); //audio_key:-6 ~ 6, map to 1~15
        //}
    #endif	//end of DVD_SETUP_REENG        
    } 
    else if (sub_id==STR_OS_VSURROUND_SETUP) 
    {
        #ifndef AC3_BASS_MANAGEMENT
        downmix_off=0;
        #endif 
        AUDIF_Set_OutputMode(OUT_51DownmixLsRs, 0);//2004AUDDRV AudioSetOutputMode(0x09, 0); //Set Output mode(9:2 channel, surround effect)
        if (full_scrn & SETUP)
            setup_ShowAC3Config();

        //set front speak gain to max., bec4 now the volume is controled only by master volume
        #ifdef CNTR_5SPK_VOLUME //wangfeng 2003-11-07 17:45
        AUDIF_Set_FSPKGain(DEFAULT_VOL);//2004AUDDRV AudioSetFSPKGain(40); //jiangxl2005-3-11 17:26
        #else
        AUDIF_Set_FSPKGain(8);//2004AUDDRV AudioSetFSPKGain(8);
        #endif

	#ifdef DVD_SETUP_REENG
        //if (setup_VA[SETUP_VA_KEY] != MIN_ITEM_SEL) {//(SETUP_KEY!=2) {
            //recover key-status
        AUDIF_Set_Key(setup_VA[SETUP_VA_KEY]);//2004AUDDRV AudioSetKey(setup_VA[SETUP_VA_KEY]); //audio_key:-6 ~ 6, map to 1~15
        //}							
        #ifdef USE_SETUP_ITEM_ENABLE_FLAG
        setup_VA_EN[SETUP_VA_CSPK]=0;
        setup_VA_EN[SETUP_VA_SSPK]=0;
        #endif//USE_SETUP_ITEM_ENABLE_FLAG
	#else //REENG
        //if (SETUP_KEY!=2) {
            //recover key-status
        AUDIF_Set_Key(SETUP_KEY);//2004AUDDRV AudioSetKey(SETUP_KEY); //audio_key:-6 ~ 6, map to 1~15
        //}
    #endif	//end of SETUP_DVD_REENG
    } 
    else  // DOWNMIX OFF
    {
    #ifndef AUDIO_2CH_5_1CH    //terry,2004/1/7 07:43PM        
        #ifndef AC3_BASS_MANAGEMENT
        downmix_off=1;
        #endif
        
        //added by JS	//for DVD_SETUP_REENG	//20040827
        #ifdef DVD_SETUP_REENG
			P=setup_getItemPos(STR_OS_AUD_OUT);
			I=P&0xff;
			P=P>>8;

            if ( (setup_item[P][I][setup_VA[SETUP_VA_AUD_OUT]]==STR_OS_STEREO_PCM) &&//(SETUP_SPDIF==SPDIFPCM) && //Jeff 20020521
                ( coding_mode_now&(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|AUDIF_CODING_MODE_DTSCD))
                )
            {
#ifndef HW_REQUIRE_DOWNMIX_WHEN_PCM_ENABLED
                 AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
#else
                //Force to do down-mix load when some decoders with multi-spk ability Jeff 20020415
                AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(7, 0); //Set Output mode(7:2 channel)
#endif
            }
        #else
            if ( (SETUP_SPDIF==SPDIFPCM) && //Jeff 20020521
                ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
                AUDIF_CODING_MODE_DTS|
                AUDIF_CODING_MODE_DTSCD))
                )
            {
                //Force to do down-mix load when some decoders with multi-spk ability Jeff 20020415
                AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(7, 0); //Set Output mode(7:2 channel)
            } 
        #endif	//end of DVD_SETUP_REENG      
            else 
    #endif //AUDIO_2CH_5_1CH
            {
                AUDIF_Set_OutputMode(OUT_51Channel, 0);//2004AUDDRV AudioSetOutputMode(6, 0); //Set Output mode(4:AC3 5.1 channel)
            }
            //    printf("-----------DOWMIX OFF --\n");
            if( (full_scrn & SETUP)
            #ifdef AUDIO_2CH_5_1CH
                ||(ChannelFlag)
            #endif
                )
                setup_ShowAC3Config();
		#ifdef DVD_SETUP_REENG
        	//set center speaker delay, 1:center speaker
            AUDIF_Set_SpkDelay(1, setup_VA[SETUP_VA_CSPK_DELAY]-MIN_ITEM_SEL);//2004AUDDRV AudioSetSpkDelay(1, setup_VA[SETUP_VA_CSPK_DELAY]-MIN_ITEM_SEL);
        	//set surround speaker delay, 2:surround speaker
            AUDIF_Set_SpkDelay(2, (setup_VA[SETUP_VA_SSPK_DELAY]-MIN_ITEM_SEL)*3);//2004AUDDRV AudioSetSpkDelay(2, (setup_VA[SETUP_VA_SSPK_DELAY]-MIN_ITEM_SEL)*3);

            #ifndef AC3_BASS_MANAGEMENT
        	//set front speaker gain
            AUDIF_Set_FSPKGain(setup_VA[SETUP_VA_FSPK]-MIN_ITEM_SEL);//2004AUDDRV AudioSetFSPKGain(setup_VA[SETUP_VA_FSPK]-MIN_ITEM_SEL);
            //set center speaker gain
            AUDIF_Set_CSPKGain(setup_VA[SETUP_VA_CSPK]-MIN_ITEM_SEL);//2004AUDDRV AudioSetCSPKGain(setup_VA[SETUP_VA_CSPK]-MIN_ITEM_SEL);
            //set surround speaker gain
            AUDIF_Set_SSPKGain(setup_VA[SETUP_VA_SSPK]-MIN_ITEM_SEL);//2004AUDDRV AudioSetSSPKGain(setup_VA[SETUP_VA_SSPK]-MIN_ITEM_SEL);
            #endif //#ifndef AC3_BASS_MANAGEMENT							
            #ifdef USE_SETUP_ITEM_ENABLE_FLAG
            setup_VA_EN[SETUP_VA_CSPK]=1;
            setup_VA_EN[SETUP_VA_SSPK]=1;
            #endif//USE_SETUP_ITEM_ENABLE_FLAG
		#else //REENG
        	//set center speaker delay, 1:center speaker
            AUDIF_Set_SpkDelay(1, SETUP_SPK_CENTER_DELAY-2);//2004AUDDRV AudioSetSpkDelay(1, SETUP_SPK_CENTER_DELAY-2);
            //set surround speaker delay, 2:surround speaker
            AUDIF_Set_SpkDelay(2, (SETUP_SPK_SURROUND_DELAY-2)*3);//2004AUDDRV AudioSetSpkDelay(2, (SETUP_SPK_SURROUND_DELAY-2)*3);

            #ifndef AC3_BASS_MANAGEMENT
            //set front speaker gain
            AUDIF_Set_FSPKGain(SETUP_SPK_FRONT-2);//2004AUDDRV AudioSetFSPKGain(SETUP_SPK_FRONT-2);
            //set center speaker gain
            AUDIF_Set_CSPKGain(SETUP_SPK_CENTER-2);//2004AUDDRV AudioSetCSPKGain(SETUP_SPK_CENTER-2);
            //set surround speaker gain
            AUDIF_Set_SSPKGain(SETUP_SPK_SURROUND-2);//2004AUDDRV AudioSetSSPKGain(SETUP_SPK_SURROUND-2);
            #endif //#ifndef AC3_BASS_MANAGEMENT
		#endif	//end of DVD_SETUP_REENG

            //Set AC3Digital Dynamic range
            #ifndef NO_AC3_DYNAMIC_RANGE
            set_AC3DynamicRange();
            #endif //#ifndef NO_AC3_DYNAMIC_RANGE
            #ifdef SPEAKER_CONFIG
                #ifdef DVD_SETUP_REENG
            AUDIF_Set_BassConfig(FRNT_SPK, setup_VA[SETUP_VA_FSPK]-MIN_ITEM_SEL);
                #else
            AUDIF_Set_BassConfig(FRNT_SPK, SETUP_SPK_FRONT-2);
                #endif
            #endif
     } //end of if (subid = )


    #ifdef DVD_SETUP_REENG
	//setup_saveVal();//this may need to be modified if called by IR command function
    run_save_sel_cmd(setup_VA[SETUP_VA_DOWNMIX], SETUP_VA_DOWNMIX);//replace setup_saveVal() to avoid setting setup_va[0] to 0,chenzhao on 2005-3-7 14:35  
    #else
    run_save_sel_cmd(MULTISPKPAGE, AC3DOWNMIXITEM);//nono 2003-7-31 21:59
    #endif	//end of DVD_SETUP_REENG

    #ifdef SubWoof_ONOFF_by_6CH_or_2CH  //2005-4-29 14:01 zhoulin
       if((setup_VA[SETUP_VA_DOWNMIX]-MIN_ITEM_SEL)==2)
         AUDIF_Set_SubWoof(STATUS_ON);
       else AUDIF_Set_SubWoof(STATUS_OFF);
       printf("\r\n\#############2######%d\r\n",sel);
    #endif

}

