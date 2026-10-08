#ifndef AMP_GUI_H
#define AMP_GUI_H

#ifdef DOLBY_AMP_VOLUME_CTRL
    #ifdef  SUPPORT_BASS_TREBLE
    #define MAX_VOLUM_CHANNEL 8
    #else
    #define MAX_VOLUM_CHANNEL 6
    #endif
#else
    #define MAX_VOLUM_CHANNEL 6
#endif

#define SUBVOL_TIME_OUT  8 //decrease in 500ms polling
extern BYTE  subvol_time_out;
extern BYTE current_channel;
extern char *channel_str[];
extern BYTE volum_list[];
extern BYTE channel_vol_offset[];

void init_amp(void);
void reset_amp_variable(void);
void subvol_channel_volume(BYTE channel,BYTE vol);
void save_amp_variable(BYTE ch);
void load_amp_variable();
void init_subvol();
void subvol_next_channel();
void show_channel_msg();
void polling_channel_timeout();
void subvol_main_vol();
void subvol_vol_up();
void subvol_vol_down();
#ifdef DOLBY_AMP_VOLUME_CTRL
void init_subvol();
void subvol_channel_volume(BYTE channel,BYTE vol);
#endif
#ifdef USE_AMP_MUTE
#define AMP_MUTE 1
#define AMP_DEMUTE 0
void sub_masterMute(BYTE mute);
#endif
#ifdef SUPPORT_Radio_NEW_UI  //wuzhj  2004/12/10   
void Radio_vol_up();
void Radio_vol_down();
void Radio_main_vol();
#endif//#ifdef SUPPORT_Radio_NEW_UI  //wuzhj  2004/12/10   
#ifdef AMP_SUPPORT_EQ
void init_amp_eq(void);
void amp_toggle_EQ(void);
typedef enum
{
    EQ_FLAT=0,
    EQ_ROCK,
    EQ_POP,
    EQ_CLASSIC,
    EQ_JAZZ,
    EQ_MAX,
}EQ_TYPE;
#endif
    
#ifdef SUPPORT_HEADPHONE
void amp_enable_headphone(void);
void amp_disable_headphone(void);
#endif//#ifdef SUPPORT_HEADPHONE

#ifdef SUPPORT_TESTSPK
inline void amp_testspk_ch(BYTE ch);
void amp_testspk_restore_ch(void);
    #ifdef TESTSPK_CONTROL_VOL
    void set_subvol_vol(BYTE channel,INT16 change);
    inline INT16 get_subvol_vol(BYTE channel);
    #endif//#ifdef TESTSPK_CONTROL_VOL
#endif

#ifdef SUPPORT_EX_BASS_FUNC//chenzhao20060117
void amp_toggle_ExBass(void);
BYTE GetExBassVolume(void);
void init_amp_exbass(void);
void show_exbass_msg(void);
    #ifdef SAVE_EX_BASS_MODE//chenzhao20060220
    void reset_amp_exbass(void);
    #endif
typedef enum
{
    EXBASS_SOFT=0,
    EXBASS_BALANCE,
    EXBASS_POWERFUL,
    EXBASS_MAX,
}EXBASS_TYPE;
EXBASS_TYPE amp_exbass_mode;
#endif

#endif//#ifndef AMP_GUI_H
