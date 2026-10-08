#include "TestSpk.h"
UINT32 coding_mode_now_b;
UINT16  smp_rate_now_b;
UINT32 astn_b;   // benson 2005/5/3 06:28下午
int adv_search_time_b;

#ifdef SUPPORT_RECEIVER
#include "amp_gui.h"
#endif

#ifdef TESTSPK_6CHANNEL
const BYTE spk_ch_map[MAX_TEST_CHANNEL]={0,4,1,5,3,2};//FL,C,FR,SUB,SR,SL
#elif defined(TESTSPK_3CHANNEL)
const BYTE spk_ch_map[MAX_TEST_CHANNEL]={0,1,5};//FL,FR,SUB,//kingslon add for 6008 20050924
#else
const BYTE spk_ch_map[MAX_TEST_CHANNEL]={0,4,1,3,2};//FL,C,FR,SR,SL
#endif
void TestSpeaker_Demute(void)//chenzhao2005-4-29
{
    AUDIF_Demute();
    GPIO_DEMUTE();
    #if defined(USE_AMP_MUTE)
	sub_masterMute(AMP_DEMUTE);
    #endif
}
void TestSpeaker_Init(void)
{
    testspk_state=1;
    coding_mode_now_b=coding_mode_now;
    smp_rate_now_b=smp_rate_now;
    astn_b = NP_ASTN;
      adv_search_time_b = adv_search_time ;

#ifdef SUPPORT_LINE_OUT_MUTE	//FCR 2005-9-28 11:52
		mute_line_out();
		set_line_out_demute_flag(2);
#endif
#ifdef OP_SWITCH_MODE_MUTE_AMP	//fcr 2005-9-28 16:40		
    sub_masterMute(AMP_MUTE);
		set_mute_time_out(2);
		set_mute_flag(1);				
    #endif   


    if (play_state == VCD_STATE_NORMAL ) MacroPause();//ircmd_pause();
    AUDIF_Set_CodingMode(AUDIF_CODING_MODE_NOISE);//hongfeng move here for test tone in Divx state 2005-11-30
    AUDIF_Reset_DSP();//2004AUDDRV DSPReset();
    //AUDIF_Init_DSPCodingMode();     //hongfeng 2005-01-29
    AUDIF_Set_SampleRate(FS_44K);//2004AUDDRV audif_set_sample_rate(FS_44K);
    coding_mode_now=CODING_MODE_NOISE;
    #ifdef PORTABLE_POWER_ON_MUTE
    regs0->sft_cfg3 |=((0x01<<6));//CHENZZ FOR LRCK=1.for power on noise.
    #endif
    #ifdef ROM_EXT_POWER_ON_MUTE
    rom_bus_set_io(ROM_BUS_OUT_AMP_MUTE,0);
    #endif
    TestSpeaker_Demute();//chenzhao2005-4-29
}

#ifdef MP3_JPEG_COWORK
extern BYTE cowork_dsp_stop; //hongfeng 2006/4/24 17:38
#endif

void restore_speaker()
{
    #ifdef SUPPORT_LINE_OUT_MUTE	//FCR 2005-9-28 11:52
		mute_line_out();
		set_line_out_demute_flag(2);
    #endif
    testspk_state = 0;  //opv-joke: 5 disc 
    #if defined(USE_AMP_MUTE)
    if(user_amp_mute)
    {
    	sub_masterMute(AMP_MUTE);
        #ifdef OP_SWITCH_MODE_MUTE_AMP
        set_mute_time_out(2);
		set_mute_flag(1);
        #endif
    }
    #endif
    AUDIF_Set_CodingMode(coding_mode_now_b);//hongfeng move here for test tone in Divx state 2005-11-30
    AUDIF_Reset_DSP();
    //AUDIF_Init_DSPCodingMode();     //hongfeng 2005-01-29
    AUDIF_Set_SampleRate(smp_rate_now_b);
    AUDIF_Set_Channel(astn_b);     // benson 2005/5/3 06:29下午
    #ifdef DOLBY_AMP_VOLUME_CTRL //chenzhao 2006-4-17 15:7 .
    amp_testspk_restore_ch();
    #endif
    if (coding_mode_now_b == AUDIF_CODING_MODE_WMA)    // benson for wma 2005/5/3 06:49下午
        AUDIF_WMA_Init_Parm();
    if ((adv_search_time > 2)||(adv_search_time < -2))  // benson FF 2x BF 2x mute 2005/5/3 09:00下午
        AUDIF_Set_Volume(0);
    #ifdef  MP3_JPEG_COWORK 
    if((coding_mode_now_b == AUDIF_CODING_MODE_MP3)&&cowork_dsp_stop)   //hongfeng 2006/4/24 13:47
        AUDIF_Set_Stop();
    #endif    
    

}
inline void map_testspk_channel(BYTE ch)
{
    //printf("testing spk %d\n",mapped_ch);
    //ddx_test_spk(mapped_ch);
    #ifdef DOLBY_AMP_VOLUME_CTRL //chenzhao 2006-4-17 15:10 .
    amp_testspk_ch(spk_ch_map[ch]);
    #else
    //#error need map_channel function
    #endif
}

#ifdef SUPPORT_SETUP_POPUP_TESTSPK_GUI
UINT16 test_spk_cnt=0;
#include "Setup_popup_gui.h"
#include "Setup_testspk_gui.h"
void polling_testspk_100ms(BYTE reset)//1:reset timer; 0: normal
{
    if(setup_gui_state==SETUPGUI_TESTSPK)
    {
        if(reset)
            test_spk_cnt=0;
        else
        {
            test_spk_cnt +=100;
            if(test_spk_cnt>TESTSPK_SWITCH_TIME)
            {
                Set_Testspk_Channel_GUI(SETUPGUI_TESTSPK_NEXT);
                test_spk_cnt=0;
            }
        }
    }
}
#else
void Start_Test_Speaker(void)
{
    BYTE ch = 0;
    int test_spk_cnt = 0;
    static BYTE first_time;
    //watchdog_onoff(0);
    TestSpeaker_Init();
    first_time = 1;
    printf("BEG surr = %d pro = %d\n",surround_mode,prologic_val);
    while(testspk_state)
    {
        if (first_time)
        {
            test_spk_cnt = TESTSPK_SWITCH_TIME;
            first_time = 0;
        }
        if(test_spk_cnt==TESTSPK_SWITCH_TIME)
        {
            test_spk_cnt = 0;
 
            if(0)//if(bHpPlug)
            {
                if(ch>2)
                {
                    ch = 0;
                }
                if(ch == 1) /*skip center  spk*/
    {
                    ch = 2;
                }
        
            }
            else
        {
                if(ch >= MAX_TEST_CHANNEL)
        {
                    ch = 0;
                }
            }
            
            map_testspk_channel(ch);
            Show_Test_Speaker(ch);
            ch ++;
        }
        test_spk_cnt ++;
        delay_1ms(1);
        polling();
        polling_vfdr();
        polling_ir();
        //polling_headphone();
        //cust_detect_knob();        
    }
 
     
    io_write_wait("Start_Test_Speaker_exit\n");
    restore_speaker();
    if(!(full_scrn & SETUP))
    {
        osd_tog_region(TESTSPK_REGION, OSD_OFF);
        osd_tog_region(REGION1, OSD_OFF);
        //vfd_set_normal_state();
        if (play_state == VCD_STATE_NORMAL) MacroContinue();
        if (play_state == VCD_STATE_PAUSE ) ircmd_play();
    }
    //vfd_show_ch_msg=0;
 printf("END surr = %d pro = %d\n",surround_mode,prologic_val);
}

void Show_Test_Speaker(BYTE ch)
{
    io_write_wait("Show_Test_Speaker\n");
    //vfd_show_test_channel(ch);
    #ifdef TESTSPK_USE_IR
	switch(ch)
	{
		case 0: 
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_FSPK],
                    "LEFT");
			break;
		case 1:
			psprintf(linebuf, "%s",_OsdMessegeFont1[osd_font_mode][STR_OS_CSPK]);
			break;
		case 2:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_FSPK],
                    "RIGHT");
			break;
		case 3:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_SSPK],
                    "RIGHT");
			break;
		case 4:
			psprintf(linebuf, "%s %s",_OsdMessegeFont1[osd_font_mode][STR_OS_SSPK],
                    "LEFT");
			break;
		default:
			break;
	}
    #endif
    #ifdef TESTSPK_USE_IR
    if(!(full_scrn & SETUP))
    {
        psprintf(RegionValStr[REGION2], linebuf);
        PrintOsdMsg(STR_OS_SPACE, TESTSPK_REGION, 0, 1);
    }
    #elif defined(TESTSPK_IN_SETUP) && defined(DVD_SETUP_REENG)
    if(full_scrn & SETUP)
    {
        osd_draw_rect(TESTSPK_UI_X,TESTSPK_UI_Y,TESTSPK_UI_XL,TESTSPK_UI_YL,0);
        osd_DrawString(TESTSPK_UI_TX,TESTSPK_UI_TY,linebuf,7,0);
    }
    #endif// TESTSPK_IN_SETUP
}
#endif

//---------------------------

