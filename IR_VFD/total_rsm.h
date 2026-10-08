#ifndef TOTAL_RSM_H
#define TOTAL_RSM_H

    #ifdef DVD_5_DISC_RESUME
        #define TOTAL_RESUME  5    //Number of disc resume 
    #else
    #ifdef STOP_RESUME_DVD_VCD
            #define TOTAL_RESUME  RESUME_DISC_NO    //Number of disc resume 
        #else
            #define TOTAL_RESUME  5    //Number of disc resume 
        #endif
    #endif

#endif
