#ifndef _DSP3CODEC_INC_
#define _DSP3CODEC_INC_

// **************************************************************************************** //

const DSP3_CODEC_INFO* g_aDSP3CodecInfo[] =
{
    //CODING_MODE_AC3
#ifdef ONLY_USE_MP3_DSP
//20050305 linrc only for make romA.bin(BootLoad).
    &DSP3Info_MP3,
#else
    &DSP3Info_AC3,  //0
    
    //CODING_MODE_PPCM
#ifdef DVD_AUDIO  
    &DSP3Info_PPCM, //1
#else
    &DSP3Info_MP3,
#endif

    //CODING_MODE_MP1   //2
    &DSP3Info_MP3,
    
    //CODING_MODE_MP2   //3
    &DSP3Info_MP3,
    
    //CODING_MODE_LPCM  //4
    &DSP3Info_LPCM,

    //CODING_MODE_JPG   //5
    &DSP3Info_MP3,
    
    //CODING_MODE_DTS   //6
#if !defined(NO_DTS_OUTPUT)||defined(FORCE_NO_DTS_OUTPUT)
    &DSP3Info_DTS,
#elif defined(DTS_SPDIF_NO_OUTPUT)
    &DSP3Info_AC3,
#else
    &DSP3Info_SPDIF,
#endif

    //CODING_MODE_SDDS  //7
    &DSP3Info_MP3,
    
    //CODING_MODE_MP3   //8
    &DSP3Info_MP3,
    
    //CODING_MODE_PCM   //9
#ifdef  USE_LPCM_REPLACE_PCM
    &DSP3Info_LPCM,
#else        
    &DSP3Info_CD,
#endif

    //CODING_MODE_MIDI  //10
#ifdef SUPPORT_MIDI
    &DSP3Info_MIDI,
#else
    &DSP3Info_MP3,
#endif

    //CODING_MODE_NES   //11
#ifdef SUPPORT_NESGAME
    &DSP3Info_NES,
#else
    &DSP3Info_MP3,
#endif

    //CODING_MODE_SPDIF //12
#if ( defined(SDRAM_16Mb_Mode) && !defined(SUPPORT_SDRAM16M_AC3_5_1CH_OUTPUT) && !defined(RAW_HAVE_ANALOG_OUTPUT) ) 
    &DSP3Info_SPDIF,
#else
    &DSP3Info_MP3,
#endif

    //CODING_MODE_DTSCD //13
#if defined(NO_DTS_OUTPUT) && !defined(FORCE_NO_DTS_OUTPUT)
    #ifdef  USE_LPCM_REPLACE_PCM
        #if defined(DTS_SPDIF_NO_OUTPUT)
    &DSP3Info_AC3,
        #else
    &DSP3Info_LPCM,
        #endif
    #else        
        #if defined(DTS_SPDIF_NO_OUTPUT)
    &DSP3Info_AC3,
        #else
    &DSP3Info_CD,
        #endif        
    #endif
#else
    #if defined(SPHE8202) || defined(SPHE1000)
    &DSP3Info_DTS,
    #else        
    &DSP3Info_DTSCD,
    #endif        
#endif
    
    //CODING_MODE_WMA   //14
#if defined(SUPPORT_WMA) || defined(SUPPORT_AUD_WMA)
    &DSP3Info_WMA,
#else
    &DSP3Info_MP3,
#endif

#ifdef SUPPORT_SPDIF_IN
    //CODING_MODE_SPDIFINCD //15
    &DSP3Info_SPDIFINCD,
    
    //CODING_MODE_SPDIFINAC3 //16
    &DSP3Info_SPDIFINAC3,
#ifdef SUPPORT_SPDIF_DTS    
    //CODING_MODE_SPDIFINDTS //17
    &DSP3Info_SPDIFINDTS,
#else
    &DSP3Info_MP3, /*huziqin add this in case of not support DTS 2006-2-27 09:49*/
#endif    
#else
    //CODING_MODE_SPDIFINCD
    &DSP3Info_MP3,
    
    //CODING_MODE_SPDIFINAC3
    &DSP3Info_MP3,
    
    //CODING_MODE_SPDIFINDTS
    &DSP3Info_MP3,
#endif
    //CODING_MODE_TUNER //18
#if defined(SUPPORT_RECEIVER) //huziqin 2006-4-19
    &DSP3Info_TUNER,
#else
    &DSP3Info_MP3,
#endif

    //CODING_MODE_NOISE //19
#ifdef SUPPORT_TESTSPK
    &DSP3Info_NOISE,
#else
    &DSP3Info_MP3,
#endif

    //CODING_MODE_AAC //20
#ifdef SUPPORT_AAC
    &DSP3Info_AAC,
#else
    &DSP3Info_MP3,
#endif

    //CODING_MODE_CD_MP3_ENCODER //21
#ifdef INCLUDE_MP3_ENCODER
    &DSP3Info_CD_MP3_ENCODER,
#else        
    &DSP3Info_MP3,  
#endif

    //CODING_MODE_OGG    //22
#ifdef SUPPORT_OGG    
    &DSP3Info_OGG,
#else        
    &DSP3Info_MP3,  
#endif    
    
    //CODING_MODE_MP3_6CH    //23
#ifdef SUPPORT_MP3_6CH    
    &DSP3Info_MP3_6CH,    
#else
    &DSP3Info_MP3,  
#endif        

//CODING_MODE_MP3_MIX    //24
#ifdef SUPPORT_SOUND_EFFECT     
    &DSP3Info_MP3_MIX,
#else        
    &DSP3Info_MP3,  
#endif    


#endif //only use mp3 dsp
};

// **************************************************************************************** //

static inline UINT32 GetDSPCodecIndex( UINT32 uiCodingMode )
{
    UINT32 i = 0;

    for( ; i < 32; i++ )
    {
        if( ( uiCodingMode >> i ) & 0x01 )
            break;
    }

    // if something wrong with our input, using MP3 codec
    return ( i >= sizeof( g_aDSP3CodecInfo ) / sizeof( DSP3_CODEC_INFO* ) ) ? CODING_MODE_MP3 : i;
}

// **************************************************************************************** //

static inline const DSP3_CODEC_INFO* GetDSPCodecInfo( UINT32 uiIndex )
{
    return g_aDSP3CodecInfo[ uiIndex ];
}

// **************************************************************************************** //

#endif

