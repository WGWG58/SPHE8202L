

  #ifdef SUPPORT_TUNER      // for tuner init 2-6-15 10:23
  init_tuner_io();
  #endif
  

  
#if defined(USE_GAMEPORT_TO_BUTTON)
  init_button_io();
#endif
  
#if defined(OURMIND_VFDPORT_TO_BUTTON)
    init_button_io_ourmind();
#endif    

/***********************/
#ifdef MIC_MUTE    
   mic_mute(0);
#endif
/**********************/



