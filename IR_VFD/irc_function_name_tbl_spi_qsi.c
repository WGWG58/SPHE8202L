//nono split from ir_parser.c 5-5-9 15:07

#ifdef SUPPORT_SPI_QSI
extern UINT8 uSpiRxData;
const SPI_CMD_FUNC spi_cmd_func_table[MAX_SPI_CMD_NUM] =
{
    spi_cmd_wakeup,                     //IRC_NULL,             0x00
    ircmd_power,                        //IRC_POWER,            0x01
    ircmd_eject_toggle,                 //IRC_EJECT,            0x02
    #ifdef SUPPORT_CARD_STORAGE
    #ifndef QSI_PLATFORM //qsi: modify by johnson 20040811
    spi_cmd_switch_2_disc,               //IRC_NULL,             0x03
    spi_cmd_switch_2_card,               //IRC_NULL,             0x04
    #else
    spi_cmd_switch_media_to_dvd,        //IRC_NULL,             0x03
    spi_cmd_switch_media_to_card,       //IRC_NULL,             0x04
    #endif
    #else
    ircmd_null,
    ircmd_null,
    #endif
    spi_cmd_play,                       //IRC_PLAY,             0x05
    spi_cmd_ssaver_on,                  //IRC_NULL,             0x06
    spi_cmd_ssaver_off,                 //IRC_NULL,             0x07
    spi_cmd_stop2eject,                 //IRC_STOP,             0x08
    spi_cmd_play_pause,                 //IRC_PAUSE,            0x09
    spi_cmd_only_pause,                      //IRC_PAUSE,            0x0a
    spi_cmd_pre_stop,                       //IRC_STOP,             0x0b
    ircmd_angle,                        //IRC_ANGLE,            0x0c
    spi_cmd_system,                     //IRC_NULL,             0x0d
    ircmd_return,                       //IRC_RETURN,           0x0e
    ircmd_audio_language,               //IRC_AUD_LANGUAGE,     0x0f
    ircmd_playmode_toggle,              //IRC_PBC,              0x10
    ircmd_zoom,                         //IRC_ZOOM,             0x11
    ircmd_mute,                         //IRC_MUTE,             0x12
    ircmd_sub_picture,                  //IRC_SUBP,             0x13
    ircmd_slowmotion,                   //IRC_SLOW              0x14
    ircmd_step,                         //IRC_STEP              0x15
    ircmd_prog,                         //IRC_PROGRAM,          0x16
    ircmd_shuffle,                      //IRC_RANDOM,           0x17
    ircmd_channel,                      //IRC_CHANNEL,          0x18
    ircmd_goto,                         //IRC_GOTO,             0x19
    ircmd_prev,                         //IRC_PREV,             0x1a
    ircmd_next,                         //IRC_NEXT,             0x1b
    ircmd_forward,                      //IRC_FORWARD,          0x1c
    ircmd_backward,                     //IRC_BACKWARD,         0x1d
    ircmd_setup,                        //IRC_SETUP,            0x1e
    ircmd_volume_up,                    //IRC_VOLUME_UP,        0x1f
    ircmd_volume_down,                  //IRC_VOLUME_DN,        0x20
    ircmd_repeat_all,                   //IRC_REPEAT,           0x21
    ircmd_repeat_ab,                    //IRC_AB,               0x22
    ircmd_clear,                        //IRC_CLEAR,            0x23
    ircmd_title_menu,                   //IRC_TITLEMENU,        0x24
    ircmd_playmode_toggle,              //IRC_PBC,              0x25
    ircmd_echo_up,                      //IRC_ECHO_UP,          0x26
    ircmd_echo_down,                    //IRC_ECHO_DOWN,        0x27
    ircmd_mic_up,                       //IRC_MIC_UP,           0x28
    ircmd_mic_down,                     //IRC_MIC_DOWN,         0x29
    ircmd_resume,                       //IRC_RESUME,           0x2a
    ircmd_display,                      //IRC_DISPLAY,          0x2b
    ircmd_null,                         //IRC_NULL,             0x2c
    ircmd_null,                         //IRC_NULL,             0x2d
    ircmd_null,                         //IRC_NULL,             0x2e
    ircmd_null,                         //IRC_NULL,             0x2f
    ircmd_0,                            //IRC_0,                0x30
    ircmd_1,                            //IRC_1,                0x31
    ircmd_2,                            //IRC_2,                0x32
    ircmd_3,                            //IRC_3,                0x33
    ircmd_4,                            //IRC_4,                0x34
    ircmd_5,                            //IRC_5,                0x35
    ircmd_6,                            //IRC_6,                0x36
    ircmd_7,                            //IRC_7,                0x37
    ircmd_8,                            //IRC_8,                0x38
    ircmd_9,                            //IRC_9,                0x39
#ifdef QSI_PLATFORM
    ircmd_p10,                           //IRC_10,               0x3a
#else    
    ircmd_10,                           //IRC_10,               0x3a
#endif    
    ircmd_up,                           //IRC_UP,               0x3b
    ircmd_down,                         //IRC_DOWN,             0x3c
    ircmd_left,                         //IRC_LEFT,             0x3d
    ircmd_right,                        //IRC_RIGHT,              0x3e
    ircmd_select,                       //IRC_SELECT,           0x3f
    ircmd_null,                         //IRC_NULL,             0x40 Reserved
    spi_cmd_tvout,                      //IRC_NULL,             0x41
    spi_cmd_tvout,                      //IRC_NULL,             0x42
    spi_cmd_tvout,                      //IRC_NULL,             0x43
    spi_cmd_tvout,                      //IRC_NULL,             0x44
    spi_cmd_tvout,                      //IRC_NULL,             0x45
    spi_cmd_tvout,                      //IRC_NULL,             0x46
    spi_cmd_tvout,                      //IRC_NULL,             0x47
    spi_cmd_tvout,                      //IRC_NULL,             0x48
    ircmd_null,                         //IRC_NULL,             0x49 Reserved
    ircmd_null,                         //IRC_NULL,             0x4a Reserved
    ircmd_null,                         //IRC_NULL,             0x4b Reserved
    ircmd_null,                         //IRC_NULL,             0x4c Reserved
    ircmd_null,                         //IRC_NULL,             0x4d Reserved
    ircmd_null,                         //IRC_NULL,             0x4e Reserved
    ircmd_null,                         //IRC_NULL,             0x4f Reserved
    spi_cmd_region,                     //IRC_NULL,             0x50
    spi_cmd_region,                     //IRC_NULL,             0x51
    spi_cmd_region,                     //IRC_NULL,             0x52
    spi_cmd_region,                     //IRC_NULL,             0x53
    spi_cmd_region,                     //IRC_NULL,             0x54
    spi_cmd_region,                     //IRC_NULL,             0x55
    spi_cmd_region,                     //IRC_NULL,             0x56
    spi_cmd_tvsys,                      //IRC_NULL,             0x57
    spi_cmd_tvsys,                      //IRC_NULL,             0x58
    spi_cmd_version_display,            //IRC_NULL,             0x59    
};

const UINT8 SPI_IR_TRANS_TABLE[MAX_SPI_CMD_NUM] =
{
    0x00,                 //0x00
    IRC_POWER,            //0x01
    IRC_EJECT,            //0x02//EJECT
    IRC_NULL,             //0x03//SOURCE TO DISC
    IRC_NULL,             //0x04//SOURCE TO CF
    IRC_PLAY,             //0x05//PLAY
    IRC_NULL,             //0x06
    IRC_NULL,             //0x07
    IRC_EJECT,             //0x08//STOP to EJECT
    IRC_PAUSEPLAY,            //0x09//PLAY/PAUSE
    IRC_PAUSE,            //0x0a//PAUSE
    IRC_STOP,             //0x0b//STOP
    IRC_ANGLE,            //0x0c//ANGLE
    IRC_NULL,             //0x0d
    IRC_RETURN,           //0x0e//RETURN
    IRC_AUD_LANGUAGE,     //0x0f
    IRC_PBC,           //0x10//PBC
    IRC_ZOOM,         //0x11//ZOOM
    IRC_MUTE,             //0x12//MUTE
    IRC_SUBP,             //0x13
    IRC_SLOW,             //0x14//SLOW
    IRC_STEP,             //0x15//STEP
    IRC_PROGRAM,          //0x16//PROGRAM
    IRC_RANDOM,           //0x17//RANDOM
    IRC_CHANNEL,          //0x18//L/R
    IRC_GOTO,             //0x19//GOTO
    IRC_PREV,             //0x1a//PREVIOUS
    IRC_NEXT,             //0x1b//NEXT
    IRC_FORWARD,          //0x1c//FORWARD
    IRC_BACKWARD,         //0x1d//BACKWARD
    IRC_SETUP,            //0x1e//SETUP
    IRC_VOLUME_UP,        //0x1f//VOLUME UP
    IRC_VOLUME_DN,        //0x20//VOLUME DN
    IRC_REPEAT,           //0x21//REPEAT
    IRC_AB,               //0x22//REPEAT A-B
    IRC_CLEAR,            //0x23//CLEAR
    IRC_TITLEMENU,        //0x24//TITLE
    IRC_NULL,           //0x25/MENU
    IRC_ECHO_UP,          //0x26//ECHO UP
    IRC_ECHO_DOWN,        //0x27//ECHO DOWN
    IRC_MIC_UP,           //0x28
    IRC_MIC_DOWN,         //0x29
    IRC_RESUME,           //0x2a//Resume
    IRC_DISPLAY,          //0x2b//Display
    IRC_NULL,             //0x2c//Reserved
    IRC_NULL,             //0x2d//Reserved
    IRC_NULL,             //0x2e//Reserved
    IRC_NULL,             //0x2f//Reserved
    IRC_0,                //0x30//Reserved
    IRC_1,                //0x31//IRC_1
    IRC_2,                //0x32//IRC_2
    IRC_3,                //0x33//IRC_3
    IRC_4,                //0x34//IRC_4
    IRC_5,                //0x35//IRC_5
    IRC_6,                //0x36//IRC_6
    IRC_7,                //0x37//IRC_7
    IRC_8,                //0x38//IRC_8
    IRC_9,                //0x39//IRC_9
    IRC_P10,               //0x3a//IRC_10
    IRC_UP,               //0x3b//IRC_UP
    IRC_DOWN,             //0x3c//IRC_DOWN
    IRC_LEFT,             //0x3d//IRC_LEFT
    IRC_RIGHT,            //0x3e//IRC_RIGHT
    IRC_SELECT,           //0x3f//IRC_SELECT
    IRC_NULL,             //0x40 Reserved
    IRC_NULL,             //0x41//CVBS ON
    IRC_NULL,             //0x42
    IRC_NULL,             //0x43
    IRC_NULL,             //0x44
    IRC_NULL,             //0x45
    IRC_NULL,             //0x46
    IRC_NULL,             //0x47
    IRC_NULL,             //0x48
    IRC_NULL,             //0x49 Reserved
    IRC_NULL,             //0x4a Reserved
    IRC_NULL,             //0x4b Reserved
    IRC_NULL,             //0x4c Reserved
    IRC_NULL,             //0x4d Reserved
    IRC_NULL,             //0x4e Reserved
    IRC_NULL,             //0x4f Reserved
    IRC_NULL,             //0x50//Region Free
    IRC_NULL,             //0x51//Region 1
    IRC_NULL,             //0x52//Region 2
    IRC_NULL,             //0x53//Region 3
    IRC_NULL,             //0x54//Region 4
    IRC_NULL,             //0x55//Region 5
    IRC_NULL,             //0x56//Region 6
    IRC_NULL,             //0x57//Output PAL Signal
    IRC_NULL,             //0x58//Output NTSC Signal
    IRC_NULL,             //0x59//Version display   
};
#endif //#ifdef SUPPORT_SPI_QSI



