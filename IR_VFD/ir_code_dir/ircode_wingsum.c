#include "user_init.h"
#include "global.h"
#include "ircode.h"
#include "irconfig.h"


const BYTE ir_mapcode[]=
{
    IRC_0,          IRC_UP,             IRC_PREV,       IRC_AUD_LANGUAGE,    //  0x00, 0x01, 0x02, 0x03
    IRC_STOP,       IRC_NULL,           IRC_PBC,        IRC_PAUSE,      //  0x04, 0x05, 0x06, 0x07
    IRC_CLEAR,      IRC_DOWN,           IRC_NEXT,       IRC_SETUP,     //  0x08, 0x09, 0x0a, 0x0b
    IRC_RETURN,     IRC_VOLUME_UP,      IRC_FORWARD,    IRC_BACKWARD,     //  0x0c, 0x0d, 0x0e, 0x0f
    IRC_ZOOM,       IRC_RIGHT,          IRC_NULL,       IRC_VOLUME_DN,      //  0x10, 0x11, 0x12, 0x13
    IRC_ANGLE,      IRC_GOTO,           IRC_EJECT,      IRC_PLAY_RESUME,          //  0x14, 0x15, 0x16, 0x17
    IRC_DISPLAY,    IRC_LEFT,           IRC_SLOW,       IRC_3D,          //  0x18, 0x19, 0x1a, 0x1b
    IRC_MUTE,       IRC_SUBP,           IRC_TITLEMENU,  IRC_ROOT_MENU,  //  0x1c, 0x1d, 0x1e, 0x1f
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x20, 0x21, 0x22, 0x23
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x24, 0x25, 0x26, 0x27
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x28, 0x29, 0x2a, 0x2b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x2c, 0x2d, 0x2e, 0x2f
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x30, 0x31, 0x32, 0x33
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x34, 0x35, 0x36, 0x37
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x38, 0x39, 0x3a, 0x3b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x3c, 0x3d, 0x3e, 0x3f
    IRC_SELECT,     IRC_1,              IRC_4,          IRC_7,      //  0x40, 0x41, 0x42, 0x43
    IRC_NULL,       IRC_3,              IRC_6,          IRC_9,       //  0x44, 0x45, 0x46, 0x47
    IRC_NULL,       IRC_PROGRAM,        IRC_REPEAT,     IRC_AB,       //  0x48, 0x49, 0x4a, 0x4b
    IRC_NULL,       IRC_2,              IRC_5,          IRC_8,       //  0x4c, 0x4d, 0x4e, 0x4f
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,     //  0x50, 0x51, 0x52, 0x53
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,     //  0x54, 0x55, 0x56, 0x57
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x58, 0x59, 0x5a, 0x5b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,   //  0x5c, 0x5d, 0x5e, 0x5f
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x60, 0x61, 0x62, 0x63
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x64, 0x65, 0x66, 0x67
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL        //  0x68, 0x69, 0x6a, 0x6b


/*
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,    //  0x00, 0x01, 0x02, 0x03
    IRC_NULL,       IRC_NULL,          IRC_NULL,         IRC_NULL,      //  0x04, 0x05, 0x06, 0x07
    IRC_NULL,  IRC_NULL,          IRC_NULL,       IRC_NULL,     //  0x08, 0x09, 0x0a, 0x0b
    IRC_NULL,        IRC_NULL,             IRC_NULL,     IRC_NULL,     //  0x0c, 0x0d, 0x0e, 0x0f
    IRC_NULL,    IRC_NULL,              IRC_NULL,          IRC_NULL,      //  0x10, 0x11, 0x12, 0x13
    IRC_NULL,          IRC_NULL,              IRC_NULL,          IRC_NULL,          //  0x14, 0x15, 0x16, 0x17
    IRC_NULL,    IRC_NULL,      IRC_NULL,          IRC_NULL,          //  0x18, 0x19, 0x1a, 0x1b
    IRC_NULL,       IRC_NULL,          IRC_NULL,     IRC_NULL,  //  0x1c, 0x1d, 0x1e, 0x1f
    IRC_NULL,    IRC_NULL,           IRC_NULL,  IRC_NULL,       //  0x20, 0x21, 0x22, 0x23
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x24, 0x25, 0x26, 0x27
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x28, 0x29, 0x2a, 0x2b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x2c, 0x2d, 0x2e, 0x2f
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x30, 0x31, 0x32, 0x33
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x34, 0x35, 0x36, 0x37
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x38, 0x39, 0x3a, 0x3b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x3c, 0x3d, 0x3e, 0x3f
    IRC_NULL,       IRC_NULL,        IRC_NULL,     IRC_NULL,      //  0x40, 0x41, 0x42, 0x43
    IRC_NULL,    IRC_NULL,           IRC_NULL,     IRC_NULL,       //  0x44, 0x45, 0x46, 0x47
    IRC_NULL,    IRC_NULL,          IRC_NULL,       IRC_NULL,       //  0x48, 0x49, 0x4a, 0x4b
    IRC_NULL,    IRC_NULL,   IRC_NULL,       IRC_NULL,       //  0x4c, 0x4d, 0x4e, 0x4f
    IRC_NULL,       IRC_NULL,        IRC_NULL,     IRC_NULL,     //  0x50, 0x51, 0x52, 0x53
    IRC_NULL,       IRC_NULL,           IRC_NULL,         IRC_NULL,     //  0x54, 0x55, 0x56, 0x57
    IRC_NULL,       IRC_NULL,        IRC_NULL,       IRC_NULL,       //  0x58, 0x59, 0x5a, 0x5b
    IRC_NULL,   IRC_NULL,         IRC_NULL,    IRC_NULL,   //  0x5c, 0x5d, 0x5e, 0x5f
    IRC_NULL,  IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x60, 0x61, 0x62, 0x63
    IRC_NULL,       IRC_NULL,             IRC_NULL,       IRC_NULL,       //  0x64, 0x65, 0x66, 0x67
    IRC_NULL,      IRC_NULL,         IRC_NULL,    IRC_NULL        //  0x68, 0x69, 0x6a, 0x6b
*/
};
