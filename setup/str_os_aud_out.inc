#include "user_init.h"
#include "global.h"
#include "osd.h"
#include "auddrv.h" //2004AUDDRV oliver 20041004 for using audio driver purpose
//#include "audif.h"
extern void setup_SetAC3PCMConfig();
extern BYTE GetCurrentFileType(void);
#if defined(ROM_BUS_EXTENT_IO) || defined(SUPPORT_LINE_OUT_MUTE)
#include "rom_bus_io.h"
#endif
void
str_os_aud_out(int sub_id)
{
#ifdef DVD_SETUP_REENG
	UINT16 P=0;
	UINT16 I=0;
#endif 

		//we use 48K SPDIF/BITSTREAM output when play 96K voide, Jeff 20020718
        AUDIF_Set_SampleRate(smp_rate_now);//2004AUDDRV audif_set_sample_rate(smp_rate_now);

                printf("setup audio out1\n");
        #ifndef HIMAGE_CANADA_CUS
        if(sub_id==STR_OS_SIMULATE)     
        {
            printf("setup audio out,spdif off\n");
            if (isSPDIFBitstream==1) {
                isSPDIFBitstream=0;
                AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
            } 
            else {
#ifndef DIVIDE_AC3_DTS_SPDIF_OUTPUTS   
                if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020415
                    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DTSCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD);
                    //AudioSetPause(); //test 20021018,terry,mark it,2004/2/9 06:26PM
                }
#endif
                
#ifdef SDRAM_16Mb_Mode//nono 20031213
                if(coding_mode_now&(AUDIF_CODING_MODE_AC3) )
                {
                    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                    AUDIF_Set_Pause();//2004AUDDRV AudioSetPause(); //test 20021018
                    AUDIF_Set_Play();//2004AUDDRV AudioSetPlay(); //test 20021018
                }
#endif//SDRAM_16Mb_Mode

                AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(0); //S-PDIF off mode command to DSP(0:off)

#ifndef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
			#ifdef DVD_SETUP_REENG
                //recover multi-spk config JSLin 20040827
                P=setup_getItemPos(STR_OS_DOWNMIX_SETUP);
                I=P&0xff;
                P=P>>8;
                if (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]==STR_OS_OFF) 
                {
                	P=setup_getItemPos(STR_OS_AUD_OUT);
                	I=P&0xff;
                	P=P>>8;	
                    if ( (setup_item[P][I][setup_VA[SETUP_VA_AUD_OUT]]==STR_OS_STEREO_PCM) && (AUDIF_CODING_MODE_DTSCD) )
                    {
                        //Force to do down-mix load when some decoders with multi-spk ability Jeff 20020415
                        AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(7, 0); //Set Output mode(7:2 channel)
                    }
                } else { //Jeff 20020822
                    if ( coding_mode_now&(AUDIF_CODING_MODE_DTSCD) ) 
                    {
                        if (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]==STR_OS_LTRT_SETUP) {
                            AUDIF_Set_OutputMode(OUT_51DownmixLtRt, 0);//2004AUDDRV AudioSetOutputMode(0x08, 0); //Set Output mode(8:AC3 downmix Lt/Rt)
                        } else if (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]==STR_OS_STEREO) {
                            AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(0x07, 0); //Set Output mode(7:AC3 downmix L0 R0)
                        } else if (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]==STR_OS_VSURROUND_SETUP) {
                            AUDIF_Set_OutputMode(OUT_51DownmixLsRs, 0);//2004AUDDRV AudioSetOutputMode(0x09, 0); //Set Output mode(9:2 channel, surround effect)
                        }
                    }
                }			
			#else
                //recover multi-spk config Jeff 20020415
                if (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) 
                {
                    if ( (SETUP_SPDIF==SPDIFPCM) && (AUDIF_CODING_MODE_DTSCD) )
                    {
                        //Force to do down-mix load when some decoders with multi-spk ability Jeff 20020415
                        AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(7, 0); //Set Output mode(7:2 channel)
                    }
                } else { //Jeff 20020822
                    if ( coding_mode_now&(AUDIF_CODING_MODE_DTSCD) ) 
                    {
                        if (SETUP_SPK_DOWNMIX==DOWNMIXLTRT) {
                            AUDIF_Set_OutputMode(OUT_51DownmixLtRt, 0);//2004AUDDRV AudioSetOutputMode(0x08, 0); //Set Output mode(8:AC3 downmix Lt/Rt)
                        } else if (SETUP_SPK_DOWNMIX==DOWNMIXSTEREO) 
                        {
                            AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(0x07, 0); //Set Output mode(7:AC3 downmix L0 R0)
                        } else if (SETUP_SPK_DOWNMIX==DOWNMIXVSRND) {
                            AUDIF_Set_OutputMode(OUT_51DownmixLsRs, 0);//2004AUDDRV AudioSetOutputMode(0x09, 0); //Set Output mode(9:2 channel, surround effect)
                        }
                    }
                }
            #endif	//end of DVD_SETUP_REENG    
#endif//#ifndef DIVIDE_AC3_DTS_SPDIF_OUTPUTS

            }

#ifdef USE_MIC_ECHO_PARAM
            AUDIF_Set_EchoPara(echo_level);//2004AUDDRV AudioSetEchoPara(echo_level);
#else
            AUDIF_Set_Echo(echo_level, echo_level);//2004AUDDRV AudioSetEcho(echo_level, echo_level);
#endif

            AUDIF_Set_Key(audio_key+8);//2004AUDDRV AudioSetKey(audio_key+8);

#ifdef    MIC_2CHANNEL
            if(id==STR_OS_MIC_VOL_1)
            {
                //mic_volume=SETUP_MIC_VOL;//wangfeng 2003-09-12 22:01
                AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume);
            }    
            else if(id==STR_OS_MIC_VOL_2)
            {
                //mic_volume=SETUP_MIC_VOL_2;
                AUDIF_Set_MICVol2(mic_volume);//2004AUDDRV AudioSetMICVol_2(mic_volume);
            }    
#else
            AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume); //Jeff 20020619
#endif
        } else
#endif//#ifndef HIMAGE_CANADA_CUS
 
#ifndef DIVIDE_AC3_DTS_SPDIF_OUTPUTS
            if(sub_id==STR_OS_BITSTREAM)
            {
                if ( coding_mode_now&(AUDIF_CODING_MODE_AC3
                    |AUDIF_CODING_MODE_DTS
#ifdef DTS_CD_OUT_RAW_A
					|AUDIF_CODING_MODE_DTSCD
#endif                                                              
                    )
                    )
                {
                    //audif_set_SPDIF_BITSTREAM();
                    isSPDIFBitstream = 1;
                    #ifdef SUPPORT_LINE_OUT_MUTE    //hongfeng add   
                    use_rom_line_out_mute();
                    #endif 
                    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                    #ifdef SUPPORT_LINE_OUT_MUTE    //hongfeng add   
                    use_rom_line_out_demute();
                    #endif 
                    AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2);
                    
                    
                } else {
#if !defined(DTS_CD_OUT_RAW_A)//&& !defined(DIVIDE_AC3_DTS_SPDIF_OUTPUTS)
                    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020415
                        //DTS-CD SPDIF/BITSTREAM mode, load CDDA as it is DSP decoder
                        printf("DTS-CD set to BITSTREAM mode,cd_subtype:%x\n",cd_subtype);
#if defined(DTS_SPDIF_NO_OUTPUT)//nono 4-8-23 23:42 for eastech
                        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DTSCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD);
#else//#if defined(DTS_SPDIF_NO_OUTPUT)                        
                        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);
#endif//#if defined(DTS_SPDIF_NO_OUTPUT)
                        AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD BITSTREAM mode) //Jeff 20020417                        
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
                        printf("DTS-CD set to BITSTREAM mode,cd_subtype:%x\n",cd_subtype);
                    } else
#endif                    
                     {
                        //AudioSetSPDIF(1); //S-PDIF bitstream mode command to DSP(1:pcm)
                        AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2); //ycwen : 2004/09/01 : we don't need to use AudioSetSPDIF command to distinguish CDDA and DTS-CD now!
                    }
                }
            
            } else
#endif//#ifndef DIVIDE_AC3_DTS_SPDIF_OUTPUTS

	#ifdef HIMAGE_CANADA_CUS
    if ( (sub_id==STR_OS_STEREO_PCM)||(sub_id==STR_OS_SIMULATE) )
	#else
    if((sub_id==STR_OS_STEREO_PCM))    
	#endif
	{
#ifndef DIVIDE_AC3_DTS_SPDIF_OUTPUTS

#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                if ( coding_mode_now&( AUDIF_CODING_MODE_DTS
#ifdef DTS_CD_OUT_RAW_A
                   |AUDIF_CODING_MODE_DTSCD
#endif//#ifdef DTS_CD_OUT_RAW_A                                                     
                    )
                )
#else//#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) 
#endif//#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                { //Jeff 20020415
#ifndef NO_DTS_OUTPUT

    #ifdef DTS_CD_OUT_RAW_A
        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DTSCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD);
    #else
        if (!check_chipinfo(2))
            AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);   // RAW
        else
			AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DTSCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD); // PCM
    #endif

    #ifdef DTS_CD_OUT_RAW_A//terry,2004/1/9 09:57AM
                                AUDIF_Set_SPDIF(1);//2004AUDDRV AudioSetSPDIF(1); //S-PDIF bitstream mode command to DSP(1:pcm)
    #else                            
                                AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD pcm)
    #endif
#else//#ifndef NO_DTS_OUTPUT
                            //AudioSetSPDIF(2); //S-PDIF off mode command to DSP(0:off)
                            printf("setup cdda\n");
    #ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                                {
                                    //audif_set_SPDIF_BITSTREAM();
                                    isSPDIFBitstream = 1;
                                    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                                    AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2);
                                }
    
    #else//#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31

        #if defined(DTS_SPDIF_NO_OUTPUT)//nono 4-8-23 23:42 for eastech
                                AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DTSCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD);
        #else//#if defined(DTS_SPDIF_NO_OUTPUT)                        
                                AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);
        #endif//#if defined(DTS_SPDIF_NO_OUTPUT)

                            #ifdef DTS_PCM_MODE_NO_SPDIF_OUT //chenzhao on 2006-9-21 14:41 .
                            AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD BITSTREAM mode) //Jeff 20020417
                            #else
                            AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD BITSTREAM mode) //Jeff 20020417
                            #endif
                            AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
    #endif//#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
#endif//NO_DTS_OUTPUT                            
                            //AudioSetPause(); //test 20021018,terry,2004/2/9 06:26PM,mark it
                        } 
                  else 
#endif//#ifndef DIVIDE_AC3_DTS_SPDIF_OUTPUTS      
                  {
                        #ifdef NO_DTS_OUTPUT
                       // isSPDIFBitstream = 1;
                        //ycwen 2005/9/16 only reset DSP when DTS.
                        //Reset DSP would cause many problem. (e.x. WMA,LPCM, and VCD karaOK..)
                        if (coding_mode_now==AUDIF_CODING_MODE_DTS)
                        {
                            isSPDIFBitstream = 1;//nono move here.20050916
                            AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                        }
                            /*#if defined(SUPPORT_WMA)
                            if (GetCurrentFileType() == CDROM_WMA)
                                AUDIF_Init_WMA();
                            #endif*/
                        #endif

				#ifdef DVD_SETUP_REENG
					P=setup_getItemPos(STR_OS_DOWNMIX_SETUP);
					I=P&0xff;
					P=P>>8;
#ifdef HW_REQUIRE_DOWNMIX_WHEN_PCM_ENABLED	// stanleyc modified
//#if !(defined(IC_8202D)&& !defined(IC_8202L)&& !defined(IC_8203A)) //nono add #ifdef IC_8202D 20051213
                   	//if (coding_mode_now == AUDIF_CODING_MODE_AC3)//nono  4-5-26 21:49
                   	if ((coding_mode_now&(AUDIF_CODING_MODE_AC3|AUDIF_CODING_MODE_DTS|
                        AUDIF_CODING_MODE_DTSCD)))//Steven 2006/08/10 add dts and dts-cd situation//
                        {
                             exe_setup_function(setup_item[P][I][1],
                                setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]],0);//nono 2003-8-26 0:50
                        }                            					
#endif
				#else
                    	if (coding_mode_now == AUDIF_CODING_MODE_AC3)//nono  4-5-26 21:49
                        {
                             exe_setup_function(setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][1],
                                setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][ SETUP_SPK_DOWNMIX ],0);//nono 2003-8-26 0:50
                        }                            
                #endif	//end of DVD_SETUP_REENG
                            
                        setup_SetAC3PCMConfig();//nono 2004-8-4 11:24    

                            #ifdef ONLY_SOUND_FIELD_KEY
                            if (GetCurrentFileType() == CDROM_WMA)  //nono 2004-03-20 20:43
                                AUDIF_Reset_DSP();//2004AUDDRV DSPReset(); 
                            #endif  //ONLY_SOUND_FIELD_KEY
                            #ifdef DTS_PCM_MODE_NO_SPDIF_OUT //chenzhao on 2006-9-21 14:41 .
                            if(coding_mode_now == AUDIF_CODING_MODE_DTS)
                                AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD BITSTREAM mode) //Jeff 20020417
                            else
                            #endif
                            AUDIF_Set_SPDIF(1);//2004AUDDRV AudioSetSPDIF(1); //S-PDIF bitstream mode command to DSP(1:pcm)
                    }
            
                } else {
                    //off
                    if (isSPDIFBitstream==1) {
                        isSPDIFBitstream=0;
                        AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                    } else {
                        AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(0); //S-PDIF off mode command to DSP(0:off)
                    }
                }
                set_aud_buf_size();
                if (full_scrn & SETUP)
                    setup_ShowVolCtrlConfig();

#ifndef SETUP_ALL_VALID        // alan, 2003/7/18 10:49¤W¤È
              //  if (cd_subtype!=CD_DTS) //wangap 2004/3/3
                    if (full_scrn & SETUP)
                        ShowSetupPage(2);
#endif

}


#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS      


void
str_os_ac3_out(int sub_id)
{
  #ifdef DVD_SETUP_REENG//denghangao 20040929
	UINT16 P=0;
	UINT16 I=0;
  #endif 
       AUDIF_Set_SampleRate(smp_rate_now);//2004AUDDRV audif_set_sample_rate(smp_rate_now); //we use 48K SPDIF/BITSTREAM output when play 96K voide, Jeff 20020718

	printf("setup ac3 audio out1\n");
#ifndef HIMAGE_CANADA_CUS
        if(sub_id==STR_OS_SIMULATE)     
        {
            printf("setup audio out,spdif off\n");
            if (isSPDIFBitstream==1) {
                isSPDIFBitstream=0;
                AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                }
#ifdef SDRAM_16Mb_Mode//nono 20031213
if(coding_mode_now&(AUDIF_CODING_MODE_AC3) )
{
    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
    AUDIF_Set_Pause();//2004AUDDRV AudioSetPause(); //test 20021018
    AUDIF_Set_Play();//2004AUDDRV AudioSetPlay(); //test 20021018
            }
#endif//SDRAM_16Mb_Mode

                AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(0); //S-PDIF off mode command to DSP(0:off)


#ifdef USE_MIC_ECHO_PARAM
            AUDIF_Set_EchoPara(echo_level);//2004AUDDRV AudioSetEchoPara(echo_level);
#else
            AUDIF_Set_Echo(echo_level, echo_level);//2004AUDDRV AudioSetEcho(echo_level, echo_level);
#endif

            AUDIF_Set_Key(audio_key+8);//2004AUDDRV AudioSetKey(audio_key+8);
            #ifdef    MIC_2CHANNEL
            if(id==STR_OS_MIC_VOL_1)
            {
                //mic_volume=SETUP_MIC_VOL;//wangfeng 2003-09-12 22:01
                AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume);
            }    
            else if(id==STR_OS_MIC_VOL_2)
            {
                //mic_volume=SETUP_MIC_VOL_2;
                AUDIF_Set_MICVol2(mic_volume);//2004AUDDRV AudioSetMICVol_2(mic_volume);
            }    
            #else
            AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume); //Jeff 20020619
            #endif
        } else
        #endif//#ifndef HIMAGE_CANADA_CUS
            if (sub_id==STR_OS_BITSTREAM) {
                if ( coding_mode_now&(AUDIF_CODING_MODE_AC3|
                    AUDIF_CODING_MODE_DTS
#ifdef DTS_CD_OUT_RAW_A
                                              |AUDIF_CODING_MODE_DTSCD
#endif                                                              
                    )
                    )
                {
                    //audif_set_SPDIF_BITSTREAM();
                    isSPDIFBitstream = 1;
                    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                    AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2);
                    
                    
                } else {
#ifndef DTS_CD_OUT_RAW_A
                    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020415
                        //DTS-CD SPDIF/BITSTREAM mode, load CDDA as it is DSP decoder
                        printf("DTS-CD set to BITSTREAM mode,cd_subtype:%x\n",cd_subtype);
                        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);
                        AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD BITSTREAM mode) //Jeff 20020417                        
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
                        printf("DTS-CD set to BITSTREAM mode,cd_subtype:%x\n",cd_subtype);
                    } else
#endif                    
                     {
                        AUDIF_Set_SPDIF(1);//2004AUDDRV AudioSetSPDIF(1); //S-PDIF bitstream mode command to DSP(1:pcm)
                    }
                }
            
            } else
	        #ifdef HIMAGE_CANADA_CUS
            if ( (sub_id==STR_OS_STEREO_PCM)||(sub_id==STR_OS_SIMULATE) ) 
	        #else
            if (sub_id==STR_OS_STEREO_PCM) 
	        #endif
            {
#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                    if ( coding_mode_now&( AUDIF_CODING_MODE_DTS
						#ifdef DTS_CD_OUT_RAW_A
                       |AUDIF_CODING_MODE_DTSCD
						#endif//#ifdef DTS_CD_OUT_RAW_A                                                     
                             )
                        )
#else//#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) 
#endif//#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
        			{ 
                    	#ifndef NO_DTS_OUTPUT

                            #ifdef DTS_CD_OUT_RAW_A
                            AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DTSCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD);
                            #else
                            if (!check_chipinfo(2))
				  				AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);   // RAW
                            else
				  				AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DTSCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD); // PCM
                            #endif

#ifdef DTS_CD_OUT_RAW_A//terry,2004/1/9 09:57AM
                            AUDIF_Set_SPDIF(1);//2004AUDDRV AudioSetSPDIF(1); //S-PDIF bitstream mode command to DSP(1:pcm)
#else                            
                            AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD pcm)
#endif
                            #else
                            //AudioSetSPDIF(2); //S-PDIF off mode command to DSP(0:off)
                            printf("setup cdda\n");
#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                            {
                                //audif_set_SPDIF_BITSTREAM();
                                isSPDIFBitstream = 1;
                                AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                                AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2);
                            }

#else//#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);
                        AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD BITSTREAM mode) //Jeff 20020417
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
#endif//#ifdef FORCE_NO_DTS_OUTPUT//nono 4-5-5 13:31
                            #endif//NO_DTS_OUTPUT                            
                            //AudioSetPause(); //test 20021018,terry,2004/2/9 06:26PM,mark it
                        } 
                        
                        else {
                            #ifdef NO_DTS_OUTPUT
                            isSPDIFBitstream = 1;
                            AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                            #endif
                    if (coding_mode_now == AUDIF_CODING_MODE_AC3)//nono  4-5-26 21:49
                        {
                        	   #ifdef DVD_SETUP_REENG     //denghg    2004-9-23 14:32  for  ac3
					                    P=setup_getItemPos(STR_OS_AUD_OUT);
					                    I=P&0xff;
					                    P=P>>8;
                        	    exe_setup_function(setup_item[P][I][1],
                              setup_item[P][I][setup_VA[SETUP_VA_AUD_OUT]],0);
                             #else   //end  DVD_SETUP_REENG
                             exe_setup_function(setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][1],
                                setup_item[MULTISPKPAGE][AC3DOWNMIXITEM][ SETUP_SPK_DOWNMIX ],0);//nono 2003-8-26 0:50
                             #endif
                        }                            
                            
                            #ifdef ONLY_SOUND_FIELD_KEY
                            if (GetCurrentFileType() == CDROM_WMA)  //nono 2004-03-20 20:43
                                AUDIF_Reset_DSP();//2004AUDDRV DSPReset(); 
                            #endif  //ONLY_SOUND_FIELD_KEY
                            AUDIF_Set_SPDIF(1);//2004AUDDRV AudioSetSPDIF(1); //S-PDIF bitstream mode command to DSP(1:pcm)
                    }
                } else {
                    //off
                    if (isSPDIFBitstream==1) {
                        isSPDIFBitstream=0;
                        AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                    } else {
                        AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(0); //S-PDIF off mode command to DSP(0:off)
                    }
                }
                set_aud_buf_size();
                if (full_scrn & SETUP)
                    setup_ShowVolCtrlConfig();

#ifndef SETUP_ALL_VALID        // alan, 2003/7/18 10:49¤W¤È
              //  if (cd_subtype!=CD_DTS) //wangap 2004/3/3
                    if (full_scrn & SETUP)
                        ShowSetupPage(2);
#endif

}

void
str_os_dts_out(int sub_id)
{

       #ifdef DVD_SETUP_REENG   //denghg  add 2004-9-24 13:37
	       UINT16 P=0;
	       UINT16 I=0;
       #endif 
 
       AUDIF_Set_SampleRate(smp_rate_now);//2004AUDDRV audif_set_sample_rate(smp_rate_now); //we use 48K SPDIF/BITSTREAM output when play 96K voide, Jeff 20020718

                printf("setup audio out2\n");
        #ifndef HIMAGE_CANADA_CUS
        if(sub_id==STR_OS_SIMULATE)     
        {
            printf("setup audio out,spdif off\n");
            if (isSPDIFBitstream==1) {
                isSPDIFBitstream=0;
                AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
            } else {
                if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020415
                    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_DTSCD);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_DTSCD);
                    //AudioSetPause(); //test 20021018,terry,mark it,2004/2/9 06:26PM
                }
                

                AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(0); //S-PDIF off mode command to DSP(0:off)
               #ifdef DVD_SETUP_REENG  //dengh add for DVD_SETUP_REEN2004-9-24 13:32
                //recover multi-spk config JSLin 20040827
                P=setup_getItemPos(STR_OS_DOWNMIX_SETUP);
                I=P&0xff;
                P=P>>8;
                if (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]==STR_OS_OFF) 
                {
                	 P=setup_getItemPos(STR_OS_AUD_OUT);
                	 I=P&0xff;
                	 P=P>>8;	
                    if ( (setup_item[P][I][setup_VA[SETUP_VA_AUD_OUT]]==STR_OS_STEREO_PCM) && (AUDIF_CODING_MODE_DTSCD) )
                    {
                        //Force to do down-mix load when some decoders with multi-spk ability Jeff 20020415
                        AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(7, 0); //Set Output mode(7:2 channel)
                    }
                } else { //Jeff 20020822
                    if ( coding_mode_now&(AUDIF_CODING_MODE_DTSCD) ) 
                    {
                        if (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]==STR_OS_LTRT_SETUP) {
                            AUDIF_Set_OutputMode(OUT_51DownmixLtRt, 0);//2004AUDDRV AudioSetOutputMode(0x08, 0); //Set Output mode(8:AC3 downmix Lt/Rt)
                        } else if (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]==STR_OS_STEREO) 
                        {
                            AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(0x07, 0); //Set Output mode(7:AC3 downmix L0 R0)
                        } else if (setup_item[P][I][setup_VA[SETUP_VA_DOWNMIX]]==STR_OS_VSURROUND_SETUP) {
                            AUDIF_Set_OutputMode(OUT_51DownmixLsRs, 0);//2004AUDDRV AudioSetOutputMode(0x09, 0); //Set Output mode(9:2 channel, surround effect)
                        }
                    }
                }			//end    DVD_SETUP_REENG
			#else//#ifdef DVD_SETUP_REENG  //dengh add for DVD_SETUP_REEN2004-9-24 13:32
                //recover multi-spk config Jeff 20020415
                if (SETUP_SPK_DOWNMIX==AC3DOWNMIXOFF) 
                {
                    if ( (SETUP_SPDIF==SPDIFPCM) && (AUDIF_CODING_MODE_DTSCD) )
                    {
                        //Force to do down-mix load when some decoders with multi-spk ability Jeff 20020415
                        AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(7, 0); //Set Output mode(7:2 channel)
                    }
                } else { //Jeff 20020822
                    if ( coding_mode_now&(AUDIF_CODING_MODE_DTSCD) ) 
                    {
                        if (SETUP_SPK_DOWNMIX==DOWNMIXLTRT) {
                            AUDIF_Set_OutputMode(OUT_51DownmixLtRt, 0);//2004AUDDRV AudioSetOutputMode(0x08, 0); //Set Output mode(8:AC3 downmix Lt/Rt)
                        } else if (SETUP_SPK_DOWNMIX==DOWNMIXSTEREO) {
                            AUDIF_Set_OutputMode(OUT_51DownmixL0R0, 0);//2004AUDDRV AudioSetOutputMode(0x07, 0); //Set Output mode(7:AC3 downmix L0 R0)
                        } else if (SETUP_SPK_DOWNMIX==DOWNMIXVSRND) {
                            AUDIF_Set_OutputMode(OUT_51DownmixLsRs, 0);//2004AUDDRV AudioSetOutputMode(0x09, 0); //Set Output mode(9:2 channel, surround effect)
                        }
                    }
                }
            #endif	//end of DVD_SETUP_REENG//#ifdef DVD_SETUP_REENG  //dengh add for DVD_SETUP_REEN2004-9-24 13:32
                              
            }

#ifdef USE_MIC_ECHO_PARAM
            AUDIF_Set_EchoPara(echo_level);//2004AUDDRV AudioSetEchoPara(echo_level);
#else
            AUDIF_Set_Echo(echo_level, echo_level);//2004AUDDRV AudioSetEcho(echo_level, echo_level);
#endif

            AUDIF_Set_Key(audio_key+8);//2004AUDDRV AudioSetKey(audio_key+8);
            #ifdef    MIC_2CHANNEL
            if(id==STR_OS_MIC_VOL_1)
            {
                //mic_volume=SETUP_MIC_VOL;//wangfeng 2003-09-12 22:01
                AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume);
            }    
            else if(id==STR_OS_MIC_VOL_2)
            {
                //mic_volume=SETUP_MIC_VOL_2;
                AUDIF_Set_MICVol2(mic_volume);//2004AUDDRV AudioSetMICVol_2(mic_volume);
            }    
            #else
            AUDIF_Set_MICVol(mic_volume);//2004AUDDRV AudioSetMICVol(mic_volume); //Jeff 20020619
            #endif
        } else
        #endif//#ifndef HIMAGE_CANADA_CUS
    	if( (sub_id==STR_OS_BITSTREAM))                  
		{
			if ( 
				AUDIF_CODING_MODE_DTS
				#ifdef DTS_CD_OUT_RAW_A
				|AUDIF_CODING_MODE_DTSCD
				#endif                                                              
				)

                {
                    //audif_set_SPDIF_BITSTREAM();
                    isSPDIFBitstream = 1;
                    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                    AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2);
                } else {
#ifndef DTS_CD_OUT_RAW_A
                    if ( (cd_type_loaded==CDDA) && (cd_subtype==CD_DTS) ) { //Jeff 20020415
                        //DTS-CD SPDIF/BITSTREAM mode, load CDDA as it is DSP decoder
                        printf("DTS-CD set to BITSTREAM mode,cd_subtype:%x\n",cd_subtype);
                        AUDIF_Set_CodingMode(AUDIF_CODING_MODE_PCM);//2004AUDDRV audif_set_coding_mode(AUDIF_CODING_MODE_PCM);
                        AUDIF_Set_SPDIF(2);//2004AUDDRV AudioSetSPDIF(2); //S-PDIF bitstream mode command to DSP(2:DTS-CD BITSTREAM mode) //Jeff 20020417                        
                        AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
                        printf("DTS-CD set to BITSTREAM mode,cd_subtype:%x\n",cd_subtype);
                    } else
#endif                    
                     {
                        AUDIF_Set_SPDIF(1);//2004AUDDRV AudioSetSPDIF(1); //S-PDIF bitstream mode command to DSP(1:pcm)
                    }
                }
            
            }                 
            else {
                //off
                if (isSPDIFBitstream==1) {
                    isSPDIFBitstream=0;
                    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
                } else {
                    AUDIF_Set_SPDIF(0);//2004AUDDRV AudioSetSPDIF(0); //S-PDIF off mode command to DSP(0:off)
                }
            }
            set_aud_buf_size();
            if (full_scrn & SETUP)
                setup_ShowVolCtrlConfig();

#ifndef SETUP_ALL_VALID        // alan, 2003/7/18 10:49¤W¤È
      //  if (cd_subtype!=CD_DTS) //wangap 2004/3/3
            if (full_scrn & SETUP)
                ShowSetupPage(2);
#endif

}
#endif//#ifdef DIVIDE_AC3_DTS_SPDIF_OUTPUTS      


