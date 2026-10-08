#include "user_init.h"
#include "global.h"
#include "ircode.h"
#include "irconfig.h"

//Zyf add the follwing 2000/10/29
const BYTE ir_mapcode[]=
{
  IRC_10,     IRC_1,     IRC_2,		IRC_3,     //0x00, 0x01 ,0x02, 0x03
  IRC_4,     IRC_5,     IRC_6,  		IRC_7,      //0x04, 0x05 ,0x06, 0x07
  IRC_8,     IRC_9,     IRC_CHANNEL, 		IRC_GOTO,   //0x08, 0x09 ,0x0a, 0x0b
  IRC_KEY_UP,     IRC_RETURN,   IRC_PAUSEPLAY, 	IRC_AB,      //0x0c, 0x0d ,0x0e, 0x0f

  IRC_0,     IRC_REPEAT, 	IRC_FORMAT,    	IRC_PREVIEW,    //0x10, 0x11 ,0x12, 0x13
  IRC_PAUSE,     IRC_RESUME, 	IRC_DISPLAY,  		IRC_P10,        //0x14, 0x15 ,0x16, 0x17
  IRC_KEY_DN,     IRC_FORWARD, 	IRC_VOLUME_UP,    	IRC_NEXT,        //0x18, 0x19 ,0x1a, 0x1b
  IRC_MUTE,     IRC_BACKWARD, 	IRC_VOLUME_DN,  		IRC_PREV,        //0x1c, 0x1d ,0x1e, 0x1f

  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x20, 0x21 ,0x22, 0x23
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x24, 0x25 ,0x26, 0x27
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x28, 0x29 ,0x2a, 0x2b
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x2c, 0x2d ,0x2e, 0x2f

  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x30, 0x31 ,0x32, 0x33
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x34, 0x35 ,0x36, 0x37
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x38, 0x39 ,0x3a, 0x3b
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x3c, 0x3d ,0x3e, 0x3f

  IRC_PBC,     IRC_EJECT,	    IRC_SLOW, 		IRC_STEP,    //0x40, 0x41 ,0x42, 0x43
  IRC_RANDOM,     IRC_STOP, 	IRC_9FRAMES,   		IRC_LANGUAGE,//0x44, 0x45 ,0x46, 0x47
  IRC_FREEZE,     IRC_PROGRAM,		IRC_NULL,   		IRC_NULL,     //0x48, 0x49 ,0x4a, 0x4b
 };