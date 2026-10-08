#include "user_init.h"
#include "global.h"
#include "ircode.h"
#include "irconfig.h"

//Zyf add the follwing 2000/10/29

#ifdef HJA_SVA_IR

const BYTE ir_mapcode[]=
{
    IRC_POWER,      IRC_4,              IRC_0,          IRC_SELECT,  	//  0x00, 0x01, 0x02, 0x03
    IRC_NULL,       IRC_5,              IRC_P10,        IRC_RIGHT,      	//  0x04, 0x05, 0x06, 0x07
    IRC_P_SCAN,     IRC_6,              IRC_PROGRAM,    IRC_STEP,  	//  0x08, 0x09, 0x0a, 0x0b
    IRC_EJECT,      IRC_AUD_LANGUAGE,   IRC_ANGLE,      IRC_DOWN,    	//  0x0c, 0x0d, 0x0e, 0x0f
    IRC_1,          IRC_7,              IRC_SETUP,      IRC_VOLUME_DN,          //  0x10, 0x11, 0x12, 0x13
    IRC_2,          IRC_8,              IRC_UP,         IRC_STOP,          //  0x14, 0x15, 0x16, 0x17
    IRC_3,          IRC_9,              IRC_VOLUME_UP,  IRC_ONLY_PAUSE,          //  0x18, 0x19, 0x1a, 0x1b
    IRC_FORMAT,       IRC_SUBP,           IRC_LEFT,       IRC_SLOW,		//  0x1c, 0x1d, 0x1e, 0x1f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x20, 0x21, 0x22, 0x23
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x24, 0x25, 0x26, 0x27
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x28, 0x29, 0x2a, 0x2b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x2c, 0x2d, 0x2e, 0x2f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x30, 0x31, 0x32, 0x33
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x34, 0x35, 0x36, 0x37
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x38, 0x39, 0x3a, 0x3b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       //  0x3c, 0x3d, 0x3e, 0x3f

#ifdef IR_PLAY_RESUME
    IRC_PLAY,       IRC_NULL,           IRC_ZOOM,      IRC_NULL,       //  0x40, 0x41, 0x42, 0x43
#else
    IRC_PLAY,       IRC_GOTO,           IRC_ZOOM,      IRC_NULL,       //  0x40, 0x41, 0x42, 0x43
#endif
    IRC_PREV,       IRC_MUTE,           IRC_NULL,      IRC_NULL,       //  0x44, 0x45, 0x46, 0x47
    
    IRC_NEXT,       IRC_RESUME,         IRC_NULL,      IRC_NULL,       //  0x48, 0x49, 0x4a, 0x4b
    IRC_BACKWARD,   IRC_TITLEMENU,      IRC_NULL,      IRC_NULL,       //  0x4c, 0x4d, 0x4e, 0x4f
    IRC_FORWARD,    IRC_PBC,      IRC_NULL,      IRC_NULL,       //  0x50, 0x51, 0x52, 0x53
    IRC_REPEAT,     IRC_CHANNEL,        IRC_NULL,      IRC_NULL,       //  0x54, 0x55, 0x56, 0x57
    IRC_AB,         IRC_3D,             IRC_NULL,      IRC_NULL,       //  0x58, 0x59, 0x5a, 0x5b
    IRC_DISPLAY,    IRC_PREVIEW,           IRC_NULL,      IRC_NULL,       //  0x5c, 0x5d, 0x5e, 0x5f
    IRC_NULL,       IRC_NULL,           IRC_NULL,      IRC_NULL,       //  0x60, 0x61, 0x62, 0x63
    IRC_NULL,       IRC_NULL,           IRC_NULL,      IRC_NULL,       //  0x64, 0x65, 0x66, 0x67
    IRC_NULL,       IRC_NULL,           IRC_NULL,      IRC_NULL,       //  0x68, 0x69, 0x6a, 0x6b

};
#else //HJA_SVA_IR      // test by xiaosan for HUAJIA  
const BYTE ir_mapcode[]=
{
	IRC_ROOT_MENU,     IRC_POWER,     IRC_REPEAT,		IRC_CLEAR, //0x00, 0x01 ,0x02, 0x03
#ifdef OLD_IR27
	IRC_PROGRAM,     IRC_DISPLAY,      IRC_PBC,  	IRC_UP,      //0x04, 0x05 ,0x06, 0x07
#elif defined(IR_014W)
	IRC_CLEAR,     IRC_DISPLAY,      IRC_PBC,  	IRC_UP,      //0x04, 0x05 ,0x06, 0x07
#elif defined(IR_04002)
	IRC_GOTO,     IRC_DISPLAY,      IRC_TITLE_RETURN,  	IRC_UP,      //0x04, 0x05 ,0x06, 0x07
#else
	IRC_PROGRAM,     IRC_DISPLAY,      IRC_TITLE_RETURN,  	IRC_UP,      //0x04, 0x05 ,0x06, 0x07
#endif

#ifdef IR_04002
	IRC_P10,     IRC_PBC,           IRC_RIGHT, 		IRC_DOWN,     //0x08, 0x09 ,0x0a, 0x0b
#else //IR_04002
	IRC_P10,     IRC_MUTE,           IRC_RIGHT, 		IRC_DOWN,     //0x08, 0x09 ,0x0a, 0x0b
#endif //IR_04002
#if defined(IR_014W)
	IRC_0,     IRC_EJECT,           IRC_LEFT,     		IRC_TITLEMENU,      //0x0c, 0x0d ,0x0e, 0x0f
#else
	IRC_0,     IRC_EJECT,           IRC_LEFT,     		IRC_SETUP,      //0x0c, 0x0d ,0x0e, 0x0f
#endif

#ifdef IR_04002
	IRC_MUTE,    IRC_1,      	 IRC_5,        	    IRC_SELECT,     //0x10, 0x11 ,0x12, 0x13
#else//#ifdef IR_04002
	IRC_CHANNEL,    IRC_1,      	 IRC_5,        	    IRC_SELECT,     //0x10, 0x11 ,0x12, 0x13
#endif//#ifdef IR_04002

	IRC_FORWARD,    IRC_4,      	 IRC_8,  		IRC_9,         //0x14, 0x15 ,0x16, 0x17

#ifdef OLD_IR27	
	IRC_TITLE_RETURN,     IRC_7,      	 IRC_0,     	    IRC_SETUP,         //0x18, 0x19 ,0x1a, 0x1b
#elif defined(IR_04002)
	IRC_RESUME,     IRC_7,      	 IRC_0,     	    IRC_SETUP,         //0x18, 0x19 ,0x1a, 0x1b
#elif defined(IR_014W)
	IRC_RETURN,     IRC_7,      	 IRC_0,     	    IRC_SETUP,         //0x18, 0x19 ,0x1a, 0x1b
#else
	IRC_P_SCAN,     IRC_7,      	 IRC_0,     	    IRC_SETUP,         //0x18, 0x19 ,0x1a, 0x1b
#endif
	
#if defined(IR_04002)	
	IRC_PROGRAM,     IRC_PLAY_SELECT,      	 IRC_PREV,  	    IRC_ZOOM,         //0x1c, 0x1d ,0x1e, 0x1f
#elif defined(IR_014W)
	IRC_REPEAT,     IRC_PLAY_SELECT,      	 IRC_PREV,  	    IRC_SETUP,         //0x1c, 0x1d ,0x1e, 0x1f
#else//if defined(IR_04002)
	IRC_REPEAT,     IRC_PLAY_SELECT,      	 IRC_PREV,  	    IRC_STOP,         //0x1c, 0x1d ,0x1e, 0x1f
#endif//if defined(IR_04002)
	
	IRC_PBC,  IRC_LEFT,		 IRC_4,  		IRC_NULL,    //0x20, 0x21 ,0x22, 0x23
	IRC_CLEAR,     IRC_NULL,		 IRC_NULL,  		IRC_RETURN,    //0x24, 0x25 ,0x26, 0x27
	IRC_PLAY,     IRC_GOTO,		 IRC_AB,  		IRC_BACKWARD,    //0x28, 0x29 ,0x2a, 0x2b
	IRC_NULL,     IRC_NULL,		 IRC_ZOOM,  		IRC_NULL,    //0x2c, 0x2d ,0x2e, 0x2f
	
	IRC_PREV,     IRC_NULL,		 IRC_PREVIEW,  		IRC_DISPLAY,     //0x30, 0x31 ,0x32, 0x33
	IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x34, 0x35 ,0x36, 0x37
	IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x38, 0x39 ,0x3a, 0x3b
	IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x3c, 0x3d ,0x3e, 0x3f
	
#ifdef IR_04002
	IRC_AB,  IRC_TITLEMENU,	IRC_BACKWARD, 	IRC_P_SCAN,    //0x40, 0x41 ,0x42, 0x43
#else//#ifdef IR_04002	
	IRC_AB,  IRC_TITLEMENU,	IRC_BACKWARD, 	IRC_GOTO,    //0x40, 0x41 ,0x42, 0x43
#endif//#ifdef IR_04002
	IRC_9,   IRC_6, 		IRC_3,   	IRC_ANGLE,//0x44, 0x45 ,0x46, 0x47
	IRC_8,         IRC_5,		IRC_2,     	IRC_AUD_LANGUAGE,     //0x48, 0x49 ,0x4a, 0x4b
	IRC_7,        IRC_4,     IRC_1,  		IRC_SUBP,     //0x4c, 0x4d ,0x4e, 0x4f
	
#ifdef IR_04002
	IRC_STOP,  IRC_ONLY_PAUSE,           IRC_VOLUME_UP,     IRC_VOLUME_DN,   //0x50, 0x51 ,0x52, 0x53
#elif defined(IR_014W)
	IRC_ZOOM,  IRC_STOP,           IRC_VOLUME_UP,     IRC_VOLUME_DN,   //0x50, 0x51 ,0x52, 0x53
#else//#ifdef IR_04002	
	IRC_ZOOM,  IRC_ONLY_PAUSE,           IRC_VOLUME_UP,     IRC_VOLUME_DN,   //0x50, 0x51 ,0x52, 0x53
#endif//#ifdef IR_04002

#ifdef OLD_IR27	
  #ifdef CNTR_5SPK_VOLUME
	IRC_FORWARD,     IRC_P10, 		IRC_NEXT,   	IRC_VOLUME_SWITCH,   //0x54, 0x55 ,0x56, 0x57
  #else//#ifdef CNTR_5SPK_VOLUME
	IRC_FORWARD,     IRC_P10, 		IRC_NEXT,   	IRC_PREVIEW,   //0x54, 0x55 ,0x56, 0x57
  #endif
	IRC_BACKWARD,     IRC_PLAY,  		IRC_PREV,  		IRC_3D,     //0x58, 0x59 ,0x5a, 0x5b
#elif defined(IR_04002)
	IRC_FORWARD,     IRC_P10, 		IRC_NEXT,   	IRC_3D,   //0x54, 0x55 ,0x56, 0x57
	IRC_BACKWARD,     IRC_PLAY,  		IRC_PREV,  		IRC_CHANNEL,     //0x58, 0x59 ,0x5a, 0x5b
#elif defined(IR_014W)
	IRC_FORWARD,     IRC_P10, 		IRC_NEXT,   	IRC_PROGRAM,   //0x54, 0x55 ,0x56, 0x57
	IRC_BACKWARD,     IRC_PAUSEPLAY,  		IRC_PREV,  		IRC_3D,     //0x58, 0x59 ,0x5a, 0x5b
#else
	IRC_FORWARD,     IRC_P10, 		IRC_NEXT,   	IRC_PBC,   //0x54, 0x55 ,0x56, 0x57
	IRC_BACKWARD,     IRC_PLAY,  		IRC_PREV,  		IRC_FORMAT,     //0x58, 0x59 ,0x5a, 0x5b
#endif

#ifdef IR_04002
	IRC_STEP,     IRC_SLOW,		    IRC_AB,  	IRC_REPEAT, //0x5c, 0x5d ,0x5e, 0x5f
#else//#ifdef IR_04002
	IRC_STEP,     IRC_SLOW,		    IRC_RESUME,  	IRC_AB, //0x5c, 0x5d ,0x5e, 0x5f
#endif//#ifdef IR_04002
	
	IRC_PAUSEPLAY,   IRC_NULL,		IRC_NULL,  		IRC_NULL,     //0x60, 0x61 ,0x62, 0x63
	IRC_ZOOM,        IRC_UP,     IRC_DOWN,  IRC_LEFT,//0x64, 0x65 ,0x66, 0x67 
	IRC_RIGHT,  IRC_FREEZE,      IRC_9FRAMES,    IRC_NULL,     //0x68, 0x69 ,0x6a, 0x6b 
};
#endif //HJA_SVA_IR    // test by chichang  


