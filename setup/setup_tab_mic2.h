        #ifdef DVDRELEASE
            #ifndef NO_MIC
                #if defined(HIMAGE_CANADA_CUS)
                    {SET_FUNC,STR_OS_MIC_ONOFF,STR_OS_ON,STR_OS_OFF,0,0,0, 0, 0,0},
                #else
#ifdef NO_KARAOK_SETTING_IN_SETUP
#else
                    {SET_FUNC,STR_OS_MIC_ONOFF,STR_OS_AUTO,STR_OS_OFF,0,0,0, 0, 0,0},
#endif  //no karaok huziqin
                #endif
            #endif
        #else
#ifdef NO_KARAOK_SETTING_IN_SETUP
#else
            {SET_FUNC,STR_OS_MIC_ONOFF,STR_OS_AUTO,STR_OS_ON,STR_OS_OFF,0,0, 0, 0,0},
#endif
        #endif

        #ifndef NO_MIC
#ifdef NO_KARAOK_SETTING_IN_SETUP        
#else
            //item2
            {SET_SCALE,STR_OS_ECHO,0,0,0,0,0, 0, 0,0},
#endif            
		#if !defined(NO_MIC_VOL)&&defined(SUPPORT_PROLOGIC_II)			//gerry for PANDA_DVD,3-8-22 13:42
            //item3
            //{SET_SCALE,STR_OS_MIC_VOL,0,0,0,0,0, 0, 0,0},
            {SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0},
		#endif		//#ifndef NO_MIC_VOL
        #endif

        //item4
#ifdef NO_KARAOK_SETTING_IN_SETUP           
#else
        {SET_SCALE,STR_OS_KEY,0,0,0,0,0, 0, 0,0},
#endif        
        
#ifdef USE_FREQ_MASK
	#ifdef SUPPORT_PROLOGIC_II
		//item5
		{SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0},
		//item6
		{SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0},
        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
	#else
		//item5
        {SET_FUNC,STR_OS_FREQ_MASK,STR_OS_48K,STR_OS_96K,STR_OS_192K,0,0, 0, 0,0},
        //item6
        {SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
	#endif
#else
	#if 1//nono 20030918
		//item5
		//{SET_FUNC,STR_OS_PROLOGIC,STR_OS_PL_MOVIE,STR_OS_PL_MUSIC,STR_OS_OFF,0,0, 0, 0,0},
#ifdef NO_KARAOK_SETTING_IN_SETUP   		
#else
		{SET_SCALE,STR_OS_MIC_VOL_1,0,0,0,0,0, 0, 0,0},
		//item6
		//{SET_SPACE,0,0,0,0,0,0, 0, 0,0},
		{SET_SCALE,STR_OS_MIC_VOL_2,0,0,0,0,0, 0, 0,0},
#endif //#ifdef NO_KARAOK_SETTING_IN_SETUP   
		
#ifndef SUPPORT_PROLOGIC_II  //xyy 2004-3-16 23:24			
		{SET_SPACE,0,0,0,0,0,0, 0, 0,0},
#endif
        //item7
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
	#else
		//item5
		{SET_SPACE,0,0,0,0,0,0, 0, 0,0},
        //item6
        {SET_SH,STR_OS_RETURN_MAIN_SETUP,0,0,0,0,0, 0, 0,0},
        //item7
        {SET_NE,0,0,0,0,0,0, 0, 0,0},
    #endif
#endif
