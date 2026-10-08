#include "user_init.h"
#include "global.h"
#include "ircode.h"
#include "irconfig.h"


#ifdef IR58_DVPX1080
const BYTE ir_mapcode[]=
{
    IRC_NULL,       IRC_NULL,           IRC_CHANNEL,      IRC_NULL,    	//  0x00, 0x01, 0x02, 0x03
    IRC_P_SCAN,       IRC_RETURN,      IRC_SETUP,        IRC_MUTE,      	//  0x04, 0x05, 0x06, 0x07
    IRC_8,          IRC_9,              IRC_PROGRAM,      IRC_7,     	//  0x08, 0x09, 0x0a, 0x0b
    IRC_5,          IRC_6,              IRC_POWER,        IRC_4,     	//  0x0c, 0x0d, 0x0e, 0x0f
    IRC_2,          IRC_3,              IRC_SUBP,         IRC_1,       //  0x10, 0x11, 0x12, 0x13
    IRC_STEP,       IRC_ONLY_PAUSE,          IRC_DISPLAY,      IRC_SLOW,       //  0x14, 0x15, 0x16, 0x17
    IRC_BACKWARD,   IRC_FORWARD,        IRC_EJECT,        IRC_PREV,       //  0x18, 0x19, 0x1a, 0x1b
    IRC_LEFT,       IRC_DOWN,           IRC_SELECT,       IRC_PBC,  	//  0x1c, 0x1d, 0x1e, 0x1f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x20, 0x21, 0x22, 0x23
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x24, 0x25, 0x26, 0x27
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x28, 0x29, 0x2a, 0x2b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x2c, 0x2d, 0x2e, 0x2f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x30, 0x31, 0x32, 0x33
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x34, 0x35, 0x36, 0x37
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x38, 0x39, 0x3a, 0x3b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x3c, 0x3d, 0x3e, 0x3f

    IRC_FORMAT,     IRC_NULL,           IRC_CLEAR,      IRC_VOLUME_UP,       //  0x40, 0x41, 0x42, 0x43
    IRC_UP,         IRC_VOLUME_DN,      IRC_NULL,       IRC_GOTO,       //  0x44, 0x45, 0x46, 0x47
    IRC_RIGHT,      IRC_0,              IRC_NULL,       IRC_RESUME,       //  0x48, 0x49, 0x4a, 0x4b
    IRC_AB,         IRC_P10,            IRC_NULL,       IRC_PREVIEW,       //  0x4c, 0x4d, 0x4e, 0x4f
    
    IRC_ANGLE,       IRC_ZOOM,           IRC_NULL,       IRC_NULL,       //  0x50, 0x51, 0x52, 0x53
    IRC_AUD_LANGUAGE,       IRC_STOP,           IRC_NULL,       IRC_NULL,       //  0x54, 0x55, 0x56, 0x57
    IRC_REPEAT,       IRC_NEXT,           IRC_NULL,       IRC_NULL,       //  0x58, 0x59, 0x5a, 0x5b
    IRC_PLAY,       IRC_TITLEMENU,           IRC_NULL,       IRC_NULL,       //  0x5c, 0x5d, 0x5e, 0x5f
    
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x60, 0x61, 0x62, 0x63
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x64, 0x65, 0x66, 0x67
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x68, 0x69, 0x6a, 0x6b

};

#else//IR58_DVPX1080
const BYTE ir_mapcode[]=
{
    IRC_SELECT,     IRC_LEFT,           IRC_PBC,       IRC_FORWARD,    //  0x00, 0x01, 0x02, 0x03

#if defined(HJ_051W) 
    IRC_STOP,       IRC_PAUSE,          IRC_PAUSEPLAY, IRC_RIGHT,      //  0x04, 0x05, 0x06, 0x07
#else
    IRC_STOP,       IRC_PAUSE,          IRC_PLAY,         IRC_RIGHT,      //  0x04, 0x05, 0x06, 0x07
#endif

    IRC_8,  IRC_9,          IRC_MUTE,       IRC_7,     //  0x08, 0x09, 0x0a, 0x0b
    IRC_5,        IRC_6,             IRC_POWER,        IRC_4,     //  0x0c, 0x0d, 0x0e, 0x0f
    IRC_2,          IRC_3,              IRC_ANGLE,          IRC_1,      //  0x10, 0x11, 0x12, 0x13

#if defined(HJ_051W)
    IRC_REPEAT,          IRC_SLOW,     IRC_TITLEMENU,  IRC_RESUME,          //  0x14, 0x15, 0x16, 0x17
#else
    IRC_REPEAT,          IRC_BOOK,              IRC_TITLEMENU,          IRC_CHANNEL,          //  0x14, 0x15, 0x16, 0x17
#endif

    IRC_ZOOM,    IRC_SETUP,      IRC_EJECT,          IRC_BACKWARD,          //  0x18, 0x19, 0x1a, 0x1b
    IRC_LEFT,       IRC_DOWN,          IRC_STOP,     IRC_PREV,  //  0x1c, 0x1d, 0x1e, 0x1f

    IRC_QUALIFY,    IRC_NULL,           IRC_RESET_DSP,  IRC_NULL,       //  0x20, 0x21, 0x22, 0x23
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x24, 0x25, 0x26, 0x27
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x28, 0x29, 0x2a, 0x2b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x2c, 0x2d, 0x2e, 0x2f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x30, 0x31, 0x32, 0x33
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x34, 0x35, 0x36, 0x37
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x38, 0x39, 0x3a, 0x3b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x3c, 0x3d, 0x3e, 0x3f

#if defined(SUPPORT_TUNER)||defined(SUPPORT_AV_INPUT) //JINPIGN 
    IRC_NULL,         IRC_POWER,          IRC_EFFECT,     IRC_INTRO,      //  0x40, 0x41, 0x42, 0x43
#elif defined(HJ_051W)
    IRC_3D,         IRC_READING,        IRC_RETURN,     IRC_VOLUME_UP,      //  0x40, 0x41, 0x42, 0x43
#elif defined(HJ_026W_KEY)
    IRC_PROGRAM,/*IRC_FORMAT,*/     IRC_READING,     IRC_RETURN,     IRC_KEY_UP,      //  0x40, 0x41, 0x42, 0x43
#else
    IRC_FORMAT,         IRC_READING,        IRC_RETURN,     IRC_VOLUME_UP,      //  0x40, 0x41, 0x42, 0x43
#endif  

    IRC_UP,    IRC_SUBP,           IRC_KEY_UP,     IRC_VOLUME_DN,       //  0x44, 0x45, 0x46, 0x47

#if defined(SVA_DVD) && defined(SUPPORT_AMP) //JINPING
    IRC_AMP_ONOFF,  IRC_ANGLE,          IRC_MUTE,       IRC_STEP,       //  0x48, 0x49, 0x4a, 0x4b
#elif defined(CNTR_5SPK_VOLUME)
    IRC_RIGHT,    IRC_0,          IRC_MUTE,       IRC_VOLUME_SWITCH,       //  0x48, 0x49, 0x4a, 0x4b
#else
    IRC_RIGHT,    IRC_0,          IRC_MUTE,       IRC_VOLUME_UP,       //  0x48, 0x49, 0x4a, 0x4b
#endif  

#if defined(HJ_051W) 
    IRC_PREVIEW,       IRC_P10,   IRC_NULL,       IRC_PROGRAM,       //  0x4c, 0x4d, 0x4e, 0x4f
    IRC_AUD_LANGUAGE,       IRC_PROGRAM,        IRC_RESUME,     IRC_RETURN,     //  0x50, 0x51, 0x52, 0x53
#elif defined(HJ_026W_KEY)
    IRC_TIME,       IRC_SLOW,   IRC_NULL,       IRC_KEY_DN,       //  0x4c, 0x4d, 0x4e, 0x4f
    IRC_AUD_LANGUAGE,       IRC_PAUSE,        IRC_RESUME,     IRC_RETURN,     //  0x50, 0x51, 0x52, 0x53
#else
    IRC_TIME,       IRC_SLOW,   IRC_NULL,       IRC_PROGRAM,       //  0x4c, 0x4d, 0x4e, 0x4f
    IRC_AUD_LANGUAGE,       IRC_PAUSE,        IRC_RESUME,     IRC_RETURN,     //  0x50, 0x51, 0x52, 0x53
#endif

    IRC_SUBP,       IRC_GOTO,           IRC_3D,         IRC_KEY_DN,     //  0x54, 0x55, 0x56, 0x57
    IRC_DISPLAY,       IRC_FORWARD,        IRC_NULL,       IRC_NULL,       //  0x58, 0x59, 0x5a, 0x5b
    IRC_SELECT,   IRC_NEXT,         IRC_CHANNEL,    IRC_LANGUAGE,   //  0x5c, 0x5d, 0x5e, 0x5f

    IRC_PAUSEPLAY,  IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x60, 0x61, 0x62, 0x63
    IRC_ZOOM,       IRC_UP,             IRC_DOWN,       IRC_LEFT,       //  0x64, 0x65, 0x66, 0x67
    IRC_RIGHT,      IRC_FREEZE,         IRC_9FRAMES,    IRC_NULL,       //  0x68, 0x69, 0x6a, 0x6b
};
#endif//IR58_DVPX1080

