#include "user_init.h"
#include "global.h"
#include "ircode.h"
#include "irconfig.h"


const BYTE ir_mapcode[]=
{
#if 0 /*def IR0310*/
    IRC_NULL,       IRC_DOWN,           IRC_UP,       	IRC_NEXT,              //  0x00, 0x01, 0x02, 0x03
    IRC_POWER,       IRC_RIGHT,          IRC_NULL,       IRC_REPEAT,        //  0x04, 0x05, 0x06, 0x07
    IRC_SUBP,       IRC_TITLEMENU,      IRC_SETUP,      IRC_GOTO,         //  0x08, 0x09, 0x0a, 0x0b
    IRC_LEFT,       IRC_NULL,           IRC_NULL,       IRC_3,                      //  0x0c, 0x0d, 0x0e, 0x0f

    IRC_SLOW,       IRC_NULL,           IRC_P10,       	IRC_DISPLAY,         //  0x10, 0x11, 0x12, 0x13
    IRC_NULL,       IRC_8,           	IRC_9,       	IRC_0,                          //  0x14, 0x15, 0x16, 0x17
    IRC_7,       	IRC_NULL,           IRC_AUD_LANGUAGE,IRC_P_SCAN,//IRC_FORMAT,  //  0x18, 0x19, 0x1a, 0x1b
    IRC_6,       	IRC_5,           	IRC_4,       	IRC_NULL,              //  0x1c, 0x1d, 0x1e, 0x1f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x20, 0x21, 0x22, 0x23
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x24, 0x25, 0x26, 0x27
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x28, 0x29, 0x2a, 0x2b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x2c, 0x2d, 0x2e, 0x2f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x30, 0x31, 0x32, 0x33
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x34, 0x35, 0x36, 0x37
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x38, 0x39, 0x3a, 0x3b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x3c, 0x3d, 0x3e, 0x3f

    IRC_RETURN,     IRC_NULL,           IRC_1,       	IRC_2,                  //  0x40, 0x41, 0x42, 0x43
    IRC_AB,       	IRC_PROGRAM,        IRC_FORWARD,    IRC_ZOOM,  //  0x44, 0x45, 0x46, 0x47
    IRC_PAUSE /*IRC_3D*/,      IRC_STOP,           IRC_ANGLE,      IRC_EJECT,         //  0x48, 0x49, 0x4a, 0x4b
    IRC_CHANNEL,    IRC_NULL,           IRC_PBC,       	IRC_VOLUME_DN,      //  0x4c, 0x4d, 0x4e, 0x4f
  
    IRC_MUTE,       IRC_NULL,           IRC_NULL,       IRC_PREV,           //  0x50, 0x51, 0x52, 0x53
    IRC_NULL,       IRC_ROOT_MENU,      IRC_NULL,       IRC_NULL,      //  0x54, 0x55, 0x56, 0x57
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,            //  0x58, 0x59, 0x5a, 0x5b
    IRC_NULL,       IRC_PLAY_SELECT/*IRC_PAUSEPLAY*/,    IRC_BACKWARD,   IRC_VOLUME_UP,       //  0x5c, 0x5d, 0x5e, 0x5f
  
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x60, 0x61, 0x62, 0x63
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x64, 0x65, 0x66, 0x67
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x68, 0x69, 0x6a, 0x6b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x6c, 0x6d, 0x6e, 0x6f
  
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0xe0, 0xe1, 0xe2, 0xe3
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0xe4, 0xe5, 0xe6, 0xe7
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0xe8, 0xe9, 0xea, 0xeb
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0xec, 0xed, 0xee, 0xef

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0xf0, 0xf1, 0xf2, 0xf3
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0xf4, 0xf5, 0xf6, 0xf7
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0xf8, 0xf9, 0xfa, 0xfb
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0xfc, 0xfd, 0xfe, 0xff
#else  //the lastest remote
#if 1
    IRC_BACKWARD,    IRC_CHANNEL,      IRC_SUBP,    IRC_TITLEMENU,    	//  0x00, 0x01, 0x02, 0x03       //the lastest remote
    IRC_NULL,              IRC_NULL,             IRC_UP,         IRC_PLAY_SELECT,      	//  0x04, 0x05, 0x06, 0x07
    IRC_ECHO_UP,       IRC_1,                  IRC_NULL,     IRC_NULL,     	    //  0x08, 0x09, 0x0a, 0x0b 10
    IRC_NULL,              IRC_4,                  IRC_NULL,     IRC_ANGLE,     	//  0x0c, 0x0d, 0x0e, 0x0f
    
    IRC_EJECT,            IRC_7,                  IRC_0,          IRC_DISPLAY,       //  0x10, 0x11, 0x12, 0x13
    IRC_SLOW,            IRC_8,                  IRC_NULL,     IRC_9,          //  0x14, 0x15, 0x16, 0x17
    IRC_VOLUME_UP,   IRC_5,                  IRC_NULL,     IRC_6,          //  0x18, 0x19, 0x1a, 0x1b 12
    IRC_NULL,             IRC_2,                  IRC_NULL,     IRC_3,      	//  0x1c, 0x1d, 0x1e, 0x1f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x20, 0x21, 0x22, 0x23
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x24, 0x25, 0x26, 0x27
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x28, 0x29, 0x2a, 0x2b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x2c, 0x2d, 0x2e, 0x2f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x30, 0x31, 0x32, 0x33
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x34, 0x35, 0x36, 0x37
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x38, 0x39, 0x3a, 0x3b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x3c, 0x3d, 0x3e, 0x3f

    IRC_RIGHT,    IRC_SETUP,         IRC_POWER,    IRC_ZOOM,  //  0x40, 0x41, 0x42, 0x43  //add by alex
    IRC_DOWN,    IRC_STOP,           IRC_AUD_LANGUAGE,       IRC_LEFT,  //  0x44, 0x45, 0x46, 0x47
    IRC_MUTE,      IRC_REPEAT,       IRC_3D,    IRC_ROOT_MENU,       //  0x48, 0x49, 0x4a, 0x4b  14
    IRC_NULL,       IRC_PROGRAM,      IRC_PBC,      IRC_NULL,      //  0x4c, 0x4d, 0x4e, 0x4f
    
    IRC_PAUSE,    IRC_P_SCAN,        IRC_RETURN,  IRC_NEXT,       //  0x50, 0x51, 0x52, 0x53
    IRC_ECHO_DOWN, IRC_PREV,     IRC_FORWARD, IRC_GOTO,       //  0x54, 0x55, 0x56, 0x57  11
    IRC_NULL,       IRC_P10,           IRC_NULL,        IRC_AB,       //  0x58, 0x59, 0x5a, 0x5b
    IRC_NULL,       IRC_NULL,         IRC_NULL,        IRC_VOLUME_DN,       //  0x5c, 0x5d, 0x5e, 0x5f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x60, 0x61, 0x62, 0x63
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x64, 0x65, 0x66, 0x67
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x68, 0x69, 0x6a, 0x6b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x6c, 0x6d, 0x6e, 0x6f
#endif
#if 0
    IRC_TITLEMENU,  IRC_LEFT,           IRC_RETURN,     IRC_AB,    		//  0x00, 0x01, 0x02, 0x03
    IRC_AUD_LANGUAGE,IRC_MUTE,          IRC_SUBP,       IRC_7,      	//  0x04, 0x05, 0x06, 0x07
    IRC_ANGLE,      IRC_4,              IRC_CHANNEL,    IRC_1,     	    //  0x08, 0x09, 0x0a, 0x0b
    IRC_PROGRAM,    IRC_SETUP,          IRC_NULL,       IRC_NULL,     	//  0x0c, 0x0d, 0x0e, 0x0f
    
    IRC_UP,         IRC_ROOT_MENU,      IRC_REPEAT,     IRC_GOTO,       //  0x10, 0x11, 0x12, 0x13
    IRC_0,          IRC_P10,            IRC_8,          IRC_9,          //  0x14, 0x15, 0x16, 0x17
    IRC_5,          IRC_6,              IRC_2,          IRC_3,          //  0x18, 0x19, 0x1a, 0x1b
    IRC_ZOOM,       IRC_PBC,            IRC_NULL,      IRC_P_SCAN, //IRC_FORMAT,  	//  0x1c, 0x1d, 0x1e, 0x1f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x20, 0x21, 0x22, 0x23
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x24, 0x25, 0x26, 0x27
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x28, 0x29, 0x2a, 0x2b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x2c, 0x2d, 0x2e, 0x2f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x30, 0x31, 0x32, 0x33
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x34, 0x35, 0x36, 0x37
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x38, 0x39, 0x3a, 0x3b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x3c, 0x3d, 0x3e, 0x3f

    IRC_PLAY_SELECT,IRC_RIGHT,       /*IRC_ONLY_PAUSE*/IRC_3D, IRC_SLOW,  //  0x40, 0x41, 0x42, 0x43  //add by alex
    IRC_BACKWARD,   IRC_VOLUME_DN,      IRC_DOWN,       IRC_VOLUME_UP,  //  0x44, 0x45, 0x46, 0x47
    IRC_STOP,       IRC_DISPLAY,        IRC_FORWARD,    IRC_NEXT,       //  0x48, 0x49, 0x4a, 0x4b
    IRC_NULL,       IRC_PREV,           IRC_EJECT,      IRC_POWER,      //  0x4c, 0x4d, 0x4e, 0x4f
    
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x50, 0x51, 0x52, 0x53
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x54, 0x55, 0x56, 0x57
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x58, 0x59, 0x5a, 0x5b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x5c, 0x5d, 0x5e, 0x5f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x60, 0x61, 0x62, 0x63
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x64, 0x65, 0x66, 0x67
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x68, 0x69, 0x6a, 0x6b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x6c, 0x6d, 0x6e, 0x6f
#endif
#endif
};
