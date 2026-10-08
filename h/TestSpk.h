#ifndef _TESTSPK_H
#define _TESTSPK_H

#ifdef SUPPORT_SETUP_POPUP_TESTSPK_GUI
    void polling_testspk_100ms(BYTE reset);//1:reset timer; 0: normal
    #define TESTSPK_SWITCH_TIME 2000 //ms
    #ifdef TESTSPK_6CHANNEL
        #define MAX_TEST_CHANNEL 6
    #elif defiend(TESTSPK_3CHANNEL)
        #define MAX_TEST_CHANNEL 3
    #else
        #define MAX_TEST_CHANNEL 5
    #endif
    inline void map_testspk_channel(BYTE ch);
    extern const BYTE spk_ch_map[MAX_TEST_CHANNEL];
#else
#define TESTSPK_UI_TX   7    //unit char
#define TESTSPK_UI_TY   8    //unit button height
#define TESTSPK_UI_X    (6*16) //unit pixel
#define TESTSPK_UI_Y    (7*32+16) //unit pixel
#define TESTSPK_UI_XL   (22*16)    //unit pixel
#define TESTSPK_UI_YL   (2*32)    //unit pixel
#define TESTSPK_REGION REGION2
void Start_Test_Speaker(void);
void Show_Test_Speaker(BYTE ch);
UINT32 get_dsp3_pcm_value(unsigned x_off);
#endif

void vfd_show_test_channel(BYTE ch);
void vfd_show_channel_msg(char *s);
void restore_speaker();
void TestSpeaker_Demute(void);
extern INT8 vfd_show_ch_msg;
void TestSpeaker_Init(void);

#endif//#ifndef _TESTSPK_H

