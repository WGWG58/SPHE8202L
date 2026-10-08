/*
*   Terry,2004/2/10 11:57AM
*/

#define is_not_dvd()      (cd_type_loaded != CDDVD)
#define is_src_2ch()      ((pDSV->dNs_Audio_ch<=1)&&is_dvd())

#ifndef SUPPORT_PROLOGIC_II   //fengjl add 4-1-27 16:19
#define is_not_support_pl2()     (1)
#else
#define is_not_support_pl2()     (0)
#endif

#define is_invalid_key()  (is_not_support_pl2()&&(is_not_dvd()||is_src_2ch()) )
//#define STR_OS_5_1_CHANNEL 151

void set_2ch_and_pl2(void)
{
  if(ChannelFlag==AUDIO_2CH) AudioSet2chOutput();
#ifdef  SUPPORT_PROLOGIC_II //zhaoyanhua add 2004-2-11 9:59
  else AudioSetPrologic_IIOutput();
#endif//ifndef SUPPORT_PROLOGIC_II
}

void set_downmix_onoff(void)
{
  if(ChannelFlag==AUDIO_2CH) AudioSet2chOutput();
  else AudioSet5_1chOutput();
}
/*
 *Function Description:
 *    if  only 2channel , change between 2channel and PROLOGIC II
 *    if  only 5.1Channel,change between 5channel and 2 channel
 *    else  between 2channel and 5.1 channel 
 * zhaoyanhua 03-11-1 20:04 
 */
void ircmd_2ch_5_1ch()
{
   int id;
   
   if(is_invalid_key())
   {
      invalid_key();	
      return;
   }
   
   AUDIF_Set_Volume(0);//2004AUDDRV AudioSetVolume(0);
		
   if(setup_IsSpkStereo())
   {//chg to 5.1ch
      ChannelFlag = AUDIO_5_1CH; 
      id = STR_OS_5_1_CHANNEL;
   }
   else
   {//chg to 2ch
      ChannelFlag = AUDIO_2CH; 
      id = STR_OS_STEREO;
   }
		
   if(is_dvd())
   {
      if(pDSV->dNs_Audio_ch<=1)//current audio is 2channel	//get from useif.c
          set_2ch_and_pl2();
      else//current audio is 5.1 channel
	  set_downmix_onoff();

   }else if (cd_subtype==CD_DTS)//CD_DTS
      set_downmix_onoff();
   else
     set_2ch_and_pl2();
  	
   AUDIF_Demute();//2004AUDDRV AudioDemute();
	
   // These codes is for show Spectrum correctly.
   //zhaoyanhua add 03-10-31 15:45
#ifdef DYNAMIC_SPECTRUM	
   if(bEqDisplay) ClearShowSpectrum();
#endif
	
   if(ChannelFlag == AUDIO_5_1CH)
   {
#ifdef ONLY_EQ_KEY   //fengjl add to turn off EQ and SOUND_FIELD when turn on prologicII 3-12-15 18:58
      if(EQ_type!=0)
      {
          EQ_type = 1;
          SetEQ();
          EQ_type = 0;
      }
#endif
    
#ifdef ONLY_SOUND_FIELD_KEY
      if(surround_type!=0)
      {		
	 AUDIF_Set_Surround(0);//2004AUDDRV AudioSetSurround(0);
	 surround_type = 1;   //OFF
      }
#endif
   }

   PrintOsdMsg(id, REGION1, 1, 0);
}



//===================================ending=================================================


