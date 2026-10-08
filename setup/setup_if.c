/*
*  Terry,2004/2/10 03:22PM
*/

#if (defined AUDIO_2CH_5_1CH) ||(defined OFF_PROLIGIC_WHEN_TURN_KEY)
/*
 * to set 2 channel output mode
 *
 */
void AudioSet2chOutput(void)
{
 	if(cd_type_loaded == CDDVD)
 	{
 		if (pDSV->dNs_Audio_ch!=5)//if PROLOGIC_II /2ch,turn of PROLOGIC first.
 		{
 			exe_setup_function(STR_OS_PROLOGIC,STR_OS_OFF,0);
 		}
	}
	else 
 	{
 		exe_setup_function(STR_OS_PROLOGIC,STR_OS_OFF,0);
 	}
	exe_setup_function(STR_OS_DOWNMIX_SETUP,STR_OS_STEREO,0);
	SETUP_SPK_DOWNMIX = DOWNMIXSTEREO;
	
#ifdef YI_XIAN_TONG//zhaoyanhua add 2003-12-17 9:51
	GpioStereoOutput();
#endif
}
#endif



//======================================ending===================================
