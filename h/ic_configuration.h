//============================================================
//2006-04-12, mimitsai add for IC_8202xx relative
//============================================================
//	05-05-2006	stanleyc
//		Please create unique chip number and version number to 
//		separate IC functionalities, instead of using other 
//		IC's configurations.
//	05-08-2006	stanleyc
//		Separate defines by functionalities
//============================================================

#if defined(IC_8203A)
	//////////////////////////////////////////////////////////
	//	IC
	#define HW_RESTRICTION_CHANGE_SYS_CLOCK

	//////////////////////////////////////////////////////////
	//	Video
	#define HW_SUPPORT_GMC
	#define HW_SUPPORT_QPEL
	#define HW_SUPPORT_TURBO_DECODE

	//////////////////////////////////////////////////////////
	//	Audio
	#define HW_SUPPORT_MP3_ROM_TABLE
	#define HW_SUPPORT_RAMP_DSP
	#define HW_SUPPORT_EXE_FOR_CODING_MODE_AC3	
	#define HW_SUPPORT_AUDIF_RESET_DSP
	#define HW_SUPPORT_AUDIO_HW_DETECT_MUTE
	#define HW_SUPPORT_SPDIF_IN

	//////////////////////////////////////////////////////////
	//	TV
	#define HW_ONLY_4_TV_DAC_ABCD //for the IC after QAA095, only ABCD 4 dac. 

#elif defined(IC_8202L)
	//////////////////////////////////////////////////////////
	//	IC
	#define HW_RESTRICTION_CHANGE_SYS_CLOCK
	
	//////////////////////////////////////////////////////////
	//	System
	#define HW_SWITCH_VPP_OSD_PRIORITY	// performance issue

	//////////////////////////////////////////////////////////
	//	Video
	#define HW_SUPPORT_GMC
	#define HW_SUPPORT_QPEL
	#define HW_SUPPORT_TURBO_DECODE
	#define HD_DISPLAY_CONTROLLER
	#define HW_SUPPORT_ARBITRARY_FRMEBUFFER_WIDTH
	//#define HW_SUPPORT_WIDTH_OVER_720
	
	//////////////////////////////////////////////////////////
	//	Audio
	#define HW_SUPPORT_MP3_ROM_TABLE
	#define HW_SUPPORT_RAMP_DSP
	#define HW_SUPPORT_EXE_FOR_CODING_MODE_AC3	
	#define HW_SUPPORT_AUDIF_RESET_DSP
	#define HW_SUPPORT_AUDIO_HW_DETECT_MUTE

	//////////////////////////////////////////////////////////
	//	INTERNAL DAC
	#define	IC_SINGLE_PLLA
	#define	IC_8202L_DAC

	//////////////////////////////////////////////////////////
	//	TV
	#define HW_ONLY_4_TV_DAC_ABCD //for the IC after QAA095, only ABCD 4 dac. 

    /////////////////////////////////////////////////////////
    //    OSD
    #ifdef SUPPORT_HD_RESOLUTION        
    #ifndef CUSTOMERS_8202L_32_DVD
    #define SUPPORT_SW_OSD_SCALING  //for support osd scaling , robert.chang add 20060627
    #endif
    #endif

#elif defined(IC_8202D)
	//////////////////////////////////////////////////////////
	//	IC
	#define HW_CHECK_8202D_D_BONDING
	#define HW_RESTRICTION_CHANGE_SYS_CLOCK

	//////////////////////////////////////////////////////////
	//	Video
	#define HW_SUPPORT_GMC
	#define HW_SUPPORT_QPEL
	#define HW_SUPPORT_TURBO_DECODE

	//////////////////////////////////////////////////////////
	//	Audio
	#define HW_SUPPORT_MP3_ROM_TABLE
	#define HW_SUPPORT_RAMP_DSP
	#define HW_AUDIO_ADJUST_ONE_SAMPLE
	#define HW_SUPPORT_EXE_FOR_CODING_MODE_AC3
	#define HW_SUPPORT_AUDIF_RESET_DSP
	#define HW_SUPPORT_51_CHANNEL
	#define HW_SUPPORT_AUDIO_HW_DETECT_MUTE
	#define HW_SUPPORT_SPDIF_IN
    #define HW_REQUIRE_DOWNMIX_WHEN_PCM_ENABLED//Steven 2006/08/10 add to avoid downmix off when SPDIF PCM turn on//

	//////////////////////////////////////////////////////////
	//	TV
	#define HW_SUPPORT_TV_SHARPNESS
	#define HW_ONLY_4_TV_DAC_ABCD //for the IC after QAA095, only ABCD 4 dac. 
	
	//////////////////////////////////////////////////////////
	//	OSD
	#define HW_SUPPORT_OSD_DEFLICKER

	//////////////////////////////////////////////////////////
	//	Servo
	#define IC_SUPPORT_SERVO_EXTERNAL_EQ_TABLE_8202D
	
#elif defined(IC_8104A)
	//////////////////////////////////////////////////////////
	//	IC
	#define HW_CHECK_8202D_D_BONDING
	#define HW_RESTRICTION_CHANGE_SYS_CLOCK
	
	//////////////////////////////////////////////////////////
	//	Video
	#define HW_SUPPORT_GMC
	#define HW_SUPPORT_QPEL
	#define HW_SUPPORT_TURBO_DECODE

	//////////////////////////////////////////////////////////
	//	Audio
	#define HW_SUPPORT_MP3_ROM_TABLE
	#define HW_SUPPORT_RAMP_DSP
	#define HW_AUDIO_ADJUST_ONE_SAMPLE
	#define HW_SUPPORT_EXE_FOR_CODING_MODE_AC3
	#define HW_SUPPORT_AUDIF_RESET_DSP
	#define HW_SUPPORT_51_CHANNEL
	#define HW_SUPPORT_AUDIO_HW_DETECT_MUTE
	#define HW_SUPPORT_SPDIF_IN
	
	//////////////////////////////////////////////////////////
	//	TV
	#define HW_SUPPORT_TV_SHARPNESS
	#define HW_ONLY_4_TV_DAC_ABCD //for the IC after QAA095, only ABCD 4 dac. 
	
	//////////////////////////////////////////////////////////
	//	OSD
	#define HW_SUPPORT_OSD_DEFLICKER

	//////////////////////////////////////////////////////////
	//	Servo
	#define IC_SUPPORT_SERVO_EXTERNAL_EQ_TABLE_8202D


#elif defined(IC_8202E)
	//////////////////////////////////////////////////////////
	//	Video
	#define HW_SUPPORT_FULLPEL

	//////////////////////////////////////////////////////////
	//	Audio
	#define HW_SUPPORT_ECHO_DELAY
	#define HW_HAS_6_DAC_DISABLE_2_DAC
	#define HW_REQUIRE_DOWNMIX_WHEN_PCM_ENABLED
	
	//////////////////////////////////////////////////////////
	//	Servo
	#define IC_SUPPORT_EXTERNAL_EQ_TABLE_8202E

#else	//IC before 8202D(8202A, 8202S,...)
	//////////////////////////////////////////////////////////
	//	Video
	#define HW_SUPPORT_FULLPEL

	//////////////////////////////////////////////////////////
	//	Audio
	#define HW_SUPPORT_ECHO_DELAY
	#define HW_HAS_6_DAC_DISABLE_2_DAC
	#define HW_REQUIRE_DOWNMIX_WHEN_PCM_ENABLED
	
	//////////////////////////////////////////////////////////
	//	Servo
	#define IC_SUPPORT_SERVO_EXTERNAL_EQ_TABLE_LEGACY
#endif
