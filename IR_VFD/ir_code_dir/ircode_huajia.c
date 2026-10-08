#include "user_init.h"
#include "global.h"
#include "ircode.h"
#include "irconfig.h"

//Zyf add the follwing 2000/10/29

#ifdef HIMAGE5900M_IR13_V2 //jason 2-10-3 18:30// 1    // test by xiaosan for HUAJIA  
const BYTE ir_mapcode[]=
{
  IRC_NULL,     IRC_PAUSEPLAY,     IRC_TITLEMENU,	IRC_NULL,    //0x00, 0x01 ,0x02, 0x03
  IRC_AUD_LANGUAGE,     IRC_EJECT,      IRC_P10, 	IRC_RIGHT,      //0x04, 0x05 ,0x06, 0x07
  IRC_NULL,     IRC_0,           IRC_CLEAR, 		IRC_NULL,      //0x08, 0x09 ,0x0a, 0x0b
  IRC_PBC,     IRC_SUBP,           IRC_NULL, 	        IRC_NEXT,      //0x0c, 0x0d ,0x0e, 0x0f
  IRC_CHANNEL,    IRC_DISPLAY,   IRC_4,        	    IRC_5,     //0x10, 0x11 ,0x12, 0x13
  IRC_6,    IRC_3,      	 IRC_ZOOM,  		IRC_SLOW,         //0x14, 0x15 ,0x16, 0x17
  IRC_2,     IRC_NULL,      	 IRC_STOP,     	    IRC_7,         //0x18, 0x19 ,0x1a, 0x1b
  IRC_1,     IRC_TIME,      	 IRC_PREV,  	    IRC_NULL,         //0x1c, 0x1d ,0x1e, 0x1f

  IRC_NULL,  IRC_NULL,		 IRC_NULL,  		IRC_NULL,    //0x20, 0x21 ,0x22, 0x23
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,    //0x24, 0x25 ,0x26, 0x27
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,    //0x28, 0x29 ,0x2a, 0x2b
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,    //0x2c, 0x2d ,0x2e, 0x2f

  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x30, 0x31 ,0x32, 0x33
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x34, 0x35 ,0x36, 0x37
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x38, 0x39 ,0x3a, 0x3b
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x3c, 0x3d ,0x3e, 0x3f

  IRC_NULL,     IRC_NULL,	 IRC_BACKWARD, 	IRC_FORWARD,    //0x40, 0x41 ,0x42, 0x43
  IRC_LEFT,     IRC_DOWN, 		IRC_PROGRAM,   	IRC_GOTO,//0x44, 0x45 ,0x46, 0x47
  IRC_UP,         IRC_NULL,		IRC_SELECT,     IRC_POWER,     //0x48, 0x49 ,0x4a, 0x4b

  IRC_SETUP,        IRC_RETURN,     IRC_PREVIEW,  	IRC_STEP,     //0x4c, 0x4d ,0x4e, 0x4f
  IRC_NULL,  IRC_NULL,           IRC_REPEAT,     IRC_ANGLE,   //0x50, 0x51 ,0x52, 0x53
  IRC_NULL,     IRC_9, 		IRC_AB,   	IRC_RESUME,   //0x54, 0x55 ,0x56, 0x57
  IRC_3D,     IRC_MUTE,    	IRC_VOLUME_DN, 	IRC_VOLUME_UP,     //0x58, 0x59 ,0x5a, 0x5b
  IRC_NULL,     IRC_NULL,	IRC_8,  	IRC_NULL, //0x5c, 0x5d ,0x5e, 0x5f

  IRC_NULL,   IRC_NULL,		IRC_NULL,  	IRC_NULL,     //0x60, 0x61 ,0x62, 0x63
  IRC_NULL,    IRC_NULL,        IRC_NULL,       IRC_NULL,//0x64, 0x65 ,0x66, 0x67 
  IRC_NULL,   IRC_NULL,         IRC_NULL,        IRC_NULL,     //0x68, 0x69 ,0x6a, 0x6b 

#ifdef HT1621_PANNEL //zyf 891108

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x6c, 0x6d ,0x6e, 0x6f
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x70, 0x71 ,0x72, 0x73
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x74, 0x75 ,0x76, 0x77
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x78, 0x79 ,0x7a, 0x7b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x7c, 0x7d ,0x7e, 0x7f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x80, 0x81 ,0x82, 0x83
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x84, 0x85 ,0x86, 0x87
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x88, 0x89 ,0x8a, 0x8b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_STOP,  //0x8c, 0x8d ,0x8e, 0x8f

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x90, 0x91 ,0x92, 0x93
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x94, 0x95 ,0x96, 0x97
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x98, 0x99 ,0x9a, 0x9b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x9c, 0x9d ,0x9e, 0x9f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa0, 0xa1 ,0xa2, 0xa3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa4, 0xa5 ,0xa6, 0xa7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa8, 0xa9 ,0xaa, 0xab
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xac, 0xad ,0xae, 0xaf

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb0, 0xb1 ,0xb2, 0xb3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb4, 0xb5 ,0xb6, 0xb7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb8, 0xb9 ,0xba, 0xbb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xbc, 0xbd ,0xbe, 0xbf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc0, 0xc1 ,0xc2, 0xc3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc4, 0xc5 ,0xc6, 0xc7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc8, 0xc9 ,0xca, 0xcb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xcc, 0xcd ,0xce, 0xcf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd0, 0xd1 ,0xd2, 0xd3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd4, 0xd5 ,0xd6, 0xd7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd8, 0xd9 ,0xda, 0xdb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xdc, 0xdd ,0xde, 0xdf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe0, 0xe1 ,0xe2, 0xe3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe4, 0xe5 ,0xe6, 0xe7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe8, 0xe9 ,0xea, 0xeb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xec, 0xed ,0xee, 0xef

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf0, 0xf1 ,0xf2, 0xf3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf4, 0xf5 ,0xf6, 0xf7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf8, 0xf9 ,0xfa, 0xfb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xfc, 0xfd ,0xfe, 0xff
#endif
};
#elif defined(HIMAGE5900_IR13_V3)
const BYTE ir_mapcode[]=
{
  IRC_NULL,     IRC_PAUSE,     IRC_TITLEMENU,	IRC_NULL,    //0x00, 0x01 ,0x02, 0x03
  IRC_AUD_LANGUAGE,     IRC_EJECT,      IRC_P10, 	IRC_RIGHT,      //0x04, 0x05 ,0x06, 0x07
  IRC_NULL,     IRC_0,           IRC_CLEAR, 		IRC_NULL,      //0x08, 0x09 ,0x0a, 0x0b
  IRC_ROOT_MENU,     IRC_SUBP,           IRC_NULL, 	        IRC_NEXT,      //0x0c, 0x0d ,0x0e, 0x0f
  IRC_CHANNEL,    IRC_ANGLE,   IRC_4,        	    IRC_5,     //0x10, 0x11 ,0x12, 0x13
  IRC_6,    IRC_3,      	 IRC_ZOOM,  		IRC_SLOW,         //0x14, 0x15 ,0x16, 0x17
  IRC_2,     IRC_NULL,      	 IRC_STOP,     	    IRC_7,         //0x18, 0x19 ,0x1a, 0x1b
  IRC_1,     IRC_TIME,      	 IRC_PREV,  	    IRC_NULL,         //0x1c, 0x1d ,0x1e, 0x1f

  IRC_NULL,  IRC_NULL,		 IRC_NULL,  		IRC_NULL,    //0x20, 0x21 ,0x22, 0x23
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,    //0x24, 0x25 ,0x26, 0x27
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,    //0x28, 0x29 ,0x2a, 0x2b
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,    //0x2c, 0x2d ,0x2e, 0x2f

  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x30, 0x31 ,0x32, 0x33
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x34, 0x35 ,0x36, 0x37
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x38, 0x39 ,0x3a, 0x3b
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x3c, 0x3d ,0x3e, 0x3f

  IRC_NULL,     IRC_NULL,	 IRC_BACKWARD, 	IRC_FORWARD,    //0x40, 0x41 ,0x42, 0x43
  IRC_LEFT,     IRC_DOWN, 		IRC_PROGRAM,   	IRC_GOTO,//0x44, 0x45 ,0x46, 0x47
  IRC_UP,         IRC_NULL,		IRC_PLAY_SELECT,     IRC_POWER,     //0x48, 0x49 ,0x4a, 0x4b

  IRC_SETUP,        IRC_RETURN,     IRC_PREVIEW,  	IRC_DISPLAY,     //0x4c, 0x4d ,0x4e, 0x4f
  IRC_NULL,  IRC_NULL,           IRC_REPEAT,     IRC_PBC,   //0x50, 0x51 ,0x52, 0x53
  IRC_NULL,     IRC_9, 		IRC_AB,   	IRC_RESUME,   //0x54, 0x55 ,0x56, 0x57
  IRC_3D,     IRC_MUTE,    	IRC_VOLUME_DN, 	IRC_VOLUME_UP,     //0x58, 0x59 ,0x5a, 0x5b
  IRC_NULL,     IRC_NULL,	IRC_8,  	IRC_NULL, //0x5c, 0x5d ,0x5e, 0x5f

  IRC_NULL,   IRC_NULL,		IRC_NULL,  	IRC_NULL,     //0x60, 0x61 ,0x62, 0x63
  IRC_NULL,    IRC_NULL,        IRC_NULL,       IRC_NULL,//0x64, 0x65 ,0x66, 0x67 
  IRC_NULL,   IRC_NULL,         IRC_NULL,        IRC_NULL,     //0x68, 0x69 ,0x6a, 0x6b 

#ifdef HT1621_PANNEL //zyf 891108

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x6c, 0x6d ,0x6e, 0x6f
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x70, 0x71 ,0x72, 0x73
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x74, 0x75 ,0x76, 0x77
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x78, 0x79 ,0x7a, 0x7b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x7c, 0x7d ,0x7e, 0x7f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x80, 0x81 ,0x82, 0x83
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x84, 0x85 ,0x86, 0x87
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x88, 0x89 ,0x8a, 0x8b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_STOP,  //0x8c, 0x8d ,0x8e, 0x8f

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x90, 0x91 ,0x92, 0x93
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x94, 0x95 ,0x96, 0x97
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x98, 0x99 ,0x9a, 0x9b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x9c, 0x9d ,0x9e, 0x9f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa0, 0xa1 ,0xa2, 0xa3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa4, 0xa5 ,0xa6, 0xa7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa8, 0xa9 ,0xaa, 0xab
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xac, 0xad ,0xae, 0xaf

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb0, 0xb1 ,0xb2, 0xb3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb4, 0xb5 ,0xb6, 0xb7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb8, 0xb9 ,0xba, 0xbb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xbc, 0xbd ,0xbe, 0xbf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc0, 0xc1 ,0xc2, 0xc3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc4, 0xc5 ,0xc6, 0xc7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc8, 0xc9 ,0xca, 0xcb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xcc, 0xcd ,0xce, 0xcf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd0, 0xd1 ,0xd2, 0xd3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd4, 0xd5 ,0xd6, 0xd7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd8, 0xd9 ,0xda, 0xdb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xdc, 0xdd ,0xde, 0xdf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe0, 0xe1 ,0xe2, 0xe3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe4, 0xe5 ,0xe6, 0xe7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe8, 0xe9 ,0xea, 0xeb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xec, 0xed ,0xee, 0xef

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf0, 0xf1 ,0xf2, 0xf3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf4, 0xf5 ,0xf6, 0xf7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf8, 0xf9 ,0xfa, 0xfb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xfc, 0xfd ,0xfe, 0xff
#endif
};

#elif defined(IR_107W)  //!HIMAGE5900M_IR13_V2
const BYTE ir_mapcode[]=
{
  IRC_SLOW,     IRC_ONLY_PAUSE,     IRC_TITLEMENU,		IRC_REPEAT, //0x00, 0x01 ,0x02, 0x03
  IRC_AUD_LANGUAGE,     IRC_EJECT,      IRC_P10,/*_RESUME*/  	IRC_RIGHT,      //0x04, 0x05 ,0x06, 0x07
  IRC_DOWN,     IRC_0,           IRC_GOTO, 		IRC_GOTO,      //0x08, 0x09 ,0x0a, 0x0b
  IRC_ROOT_MENU,     IRC_SUBP,           IRC_LEFT,     		IRC_NEXT,      //0x0c, 0x0d ,0x0e, 0x0f
  IRC_CHANNEL,    IRC_ANGLE,   IRC_4,        	    IRC_5,     //0x10, 0x11 ,0x12, 0x13
  IRC_6,    IRC_3,      	 IRC_ZOOM,  		IRC_SLOW,         //0x14, 0x15 ,0x16, 0x17
  IRC_2,     IRC_SUBP,      	 IRC_STOP,     	    IRC_7,         //0x18, 0x19 ,0x1a, 0x1b
  IRC_1,     IRC_NULL,      	 IRC_PREV,  	    IRC_ANGLE,         //0x1c, 0x1d ,0x1e, 0x1f

  IRC_PBC,  IRC_LEFT,		 IRC_4,  		IRC_NULL,    //0x20, 0x21 ,0x22, 0x23
  IRC_CLEAR,     IRC_NULL,		 IRC_NULL,  		IRC_RETURN,    //0x24, 0x25 ,0x26, 0x27
  IRC_PLAY,     IRC_GOTO,		 IRC_AB,  		IRC_BACKWARD,    //0x28, 0x29 ,0x2a, 0x2b
  IRC_NULL,     IRC_NULL,		 IRC_ZOOM,  		IRC_NULL,    //0x2c, 0x2d ,0x2e, 0x2f

  IRC_PREV,     IRC_NULL,		 IRC_PREVIEW,  		IRC_DISPLAY,     //0x30, 0x31 ,0x32, 0x33
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x34, 0x35 ,0x36, 0x37
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x38, 0x39 ,0x3a, 0x3b
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x3c, 0x3d ,0x3e, 0x3f

  IRC_AB,  IRC_BOOK,	IRC_BACKWARD, 	IRC_FORWARD,    //0x40, 0x41 ,0x42, 0x43
  IRC_LEFT,   IRC_DOWN, 		IRC_PROGRAM,   	IRC_PBC,//0x44, 0x45 ,0x46, 0x47
  IRC_UP,         IRC_PROGRAM,		IRC_PLAY_SELECT,     	IRC_POWER,     //0x48, 0x49 ,0x4a, 0x4b
  IRC_SETUP,        IRC_MUTE,     IRC_RETURN,  		IRC_DISPLAY,     //0x4c, 0x4d ,0x4e, 0x4f

  IRC_RETURN,  IRC_ZOOM,           IRC_REPEAT,     IRC_STEP,   //0x50, 0x51 ,0x52, 0x53
  IRC_6,     IRC_9, 		IRC_AB,   	IRC_P_SCAN,   //0x54, 0x55 ,0x56, 0x57
  IRC_KEY_DN,     IRC_KEY_UP,    		IRC_VOLUME_DN,  		IRC_VOLUME_UP,     //0x58, 0x59 ,0x5a, 0x5b
  IRC_NULL,     IRC_NULL,	IRC_8,  	IRC_NULL, //0x5c, 0x5d ,0x5e, 0x5f

  IRC_NULL,   IRC_NULL,		IRC_NULL,  	IRC_NULL,     //0x60, 0x61 ,0x62, 0x63
  IRC_NULL,    IRC_NULL,        IRC_NULL,       IRC_NULL,//0x64, 0x65 ,0x66, 0x67 
  IRC_NULL,   IRC_NULL,         IRC_NULL,        IRC_NULL,     //0x68, 0x69 ,0x6a, 0x6b 

#ifdef HT1621_PANNEL //zyf 891108

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x6c, 0x6d ,0x6e, 0x6f
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x70, 0x71 ,0x72, 0x73
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x74, 0x75 ,0x76, 0x77
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x78, 0x79 ,0x7a, 0x7b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x7c, 0x7d ,0x7e, 0x7f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x80, 0x81 ,0x82, 0x83
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x84, 0x85 ,0x86, 0x87
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x88, 0x89 ,0x8a, 0x8b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_STOP,  //0x8c, 0x8d ,0x8e, 0x8f

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x90, 0x91 ,0x92, 0x93
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x94, 0x95 ,0x96, 0x97
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x98, 0x99 ,0x9a, 0x9b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x9c, 0x9d ,0x9e, 0x9f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa0, 0xa1 ,0xa2, 0xa3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa4, 0xa5 ,0xa6, 0xa7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa8, 0xa9 ,0xaa, 0xab
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xac, 0xad ,0xae, 0xaf

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb0, 0xb1 ,0xb2, 0xb3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb4, 0xb5 ,0xb6, 0xb7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb8, 0xb9 ,0xba, 0xbb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xbc, 0xbd ,0xbe, 0xbf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc0, 0xc1 ,0xc2, 0xc3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc4, 0xc5 ,0xc6, 0xc7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc8, 0xc9 ,0xca, 0xcb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xcc, 0xcd ,0xce, 0xcf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd0, 0xd1 ,0xd2, 0xd3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd4, 0xd5 ,0xd6, 0xd7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd8, 0xd9 ,0xda, 0xdb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xdc, 0xdd ,0xde, 0xdf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe0, 0xe1 ,0xe2, 0xe3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe4, 0xe5 ,0xe6, 0xe7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe8, 0xe9 ,0xea, 0xeb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xec, 0xed ,0xee, 0xef

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf0, 0xf1 ,0xf2, 0xf3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf4, 0xf5 ,0xf6, 0xf7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf8, 0xf9 ,0xfa, 0xfb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xfc, 0xfd ,0xfe, 0xff
#endif
};

#elif defined(IR_117W)  //!HIMAGE5900M_IR13_V2
const BYTE ir_mapcode[]=
{
  IRC_SLOW,     IRC_ONLY_PAUSE,     IRC_TITLE_RETURN,		IRC_REPEAT, //0x00, 0x01 ,0x02, 0x03
  IRC_DISPLAY,     IRC_EJECT,      IRC_P10,/*_RESUME*/  	IRC_RIGHT,      //0x04, 0x05 ,0x06, 0x07
  IRC_DOWN,     IRC_0,           IRC_GOTO, 		IRC_GOTO,      //0x08, 0x09 ,0x0a, 0x0b
  IRC_STEP,     IRC_SUBP,           IRC_LEFT,     		IRC_NEXT,      //0x0c, 0x0d ,0x0e, 0x0f
  IRC_CHANNEL,    IRC_ANGLE,   IRC_4,        	    IRC_5,     //0x10, 0x11 ,0x12, 0x13
  IRC_6,    IRC_3,      	 IRC_ZOOM,  		IRC_SLOW,         //0x14, 0x15 ,0x16, 0x17
  IRC_2,     IRC_SUBP,      	 IRC_STOP,     	    IRC_7,         //0x18, 0x19 ,0x1a, 0x1b
  IRC_1,     IRC_NULL,      	 IRC_PREV,  	    IRC_ANGLE,         //0x1c, 0x1d ,0x1e, 0x1f

  IRC_PBC,  IRC_LEFT,		 IRC_4,  		IRC_NULL,    //0x20, 0x21 ,0x22, 0x23
  IRC_CLEAR,     IRC_NULL,		 IRC_NULL,  		IRC_RETURN,    //0x24, 0x25 ,0x26, 0x27
  IRC_PLAY,     IRC_GOTO,		 IRC_AB,  		IRC_BACKWARD,    //0x28, 0x29 ,0x2a, 0x2b
  IRC_NULL,     IRC_NULL,		 IRC_ZOOM,  		IRC_NULL,    //0x2c, 0x2d ,0x2e, 0x2f

  IRC_PREV,     IRC_NULL,		 IRC_PREVIEW,  		IRC_DISPLAY,     //0x30, 0x31 ,0x32, 0x33
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x34, 0x35 ,0x36, 0x37
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x38, 0x39 ,0x3a, 0x3b
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x3c, 0x3d ,0x3e, 0x3f

  IRC_AB,  IRC_BOOK,	IRC_BACKWARD, 	IRC_FORWARD,    //0x40, 0x41 ,0x42, 0x43
  IRC_LEFT,   IRC_DOWN, 		IRC_PROGRAM,   	IRC_PBC,//0x44, 0x45 ,0x46, 0x47
  IRC_UP,         IRC_PROGRAM,		IRC_PLAY_SELECT,     	IRC_POWER,     //0x48, 0x49 ,0x4a, 0x4b
  IRC_SETUP,        IRC_MUTE,     IRC_PREVIEW,  		IRC_AUD_LANGUAGE,     //0x4c, 0x4d ,0x4e, 0x4f

  IRC_RETURN,  IRC_ZOOM,           IRC_REPEAT,     IRC_FORMAT,   //0x50, 0x51 ,0x52, 0x53
  IRC_6,     IRC_9, 		IRC_AB,   	IRC_P_SCAN,   //0x54, 0x55 ,0x56, 0x57
  IRC_KEY_DN,     IRC_KEY_UP,    		IRC_VOLUME_DN,  		IRC_VOLUME_UP,     //0x58, 0x59 ,0x5a, 0x5b
  IRC_NULL,     IRC_NULL,	IRC_8,  	IRC_NULL, //0x5c, 0x5d ,0x5e, 0x5f

  IRC_NULL,   IRC_NULL,		IRC_NULL,  	IRC_NULL,     //0x60, 0x61 ,0x62, 0x63
  IRC_NULL,    IRC_NULL,        IRC_NULL,       IRC_NULL,//0x64, 0x65 ,0x66, 0x67 
  IRC_NULL,   IRC_NULL,         IRC_NULL,        IRC_NULL,     //0x68, 0x69 ,0x6a, 0x6b 

#ifdef HT1621_PANNEL //zyf 891108

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x6c, 0x6d ,0x6e, 0x6f
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x70, 0x71 ,0x72, 0x73
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x74, 0x75 ,0x76, 0x77
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x78, 0x79 ,0x7a, 0x7b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x7c, 0x7d ,0x7e, 0x7f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x80, 0x81 ,0x82, 0x83
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x84, 0x85 ,0x86, 0x87
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x88, 0x89 ,0x8a, 0x8b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_STOP,  //0x8c, 0x8d ,0x8e, 0x8f

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x90, 0x91 ,0x92, 0x93
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x94, 0x95 ,0x96, 0x97
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x98, 0x99 ,0x9a, 0x9b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x9c, 0x9d ,0x9e, 0x9f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa0, 0xa1 ,0xa2, 0xa3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa4, 0xa5 ,0xa6, 0xa7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa8, 0xa9 ,0xaa, 0xab
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xac, 0xad ,0xae, 0xaf

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb0, 0xb1 ,0xb2, 0xb3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb4, 0xb5 ,0xb6, 0xb7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb8, 0xb9 ,0xba, 0xbb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xbc, 0xbd ,0xbe, 0xbf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc0, 0xc1 ,0xc2, 0xc3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc4, 0xc5 ,0xc6, 0xc7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc8, 0xc9 ,0xca, 0xcb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xcc, 0xcd ,0xce, 0xcf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd0, 0xd1 ,0xd2, 0xd3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd4, 0xd5 ,0xd6, 0xd7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd8, 0xd9 ,0xda, 0xdb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xdc, 0xdd ,0xde, 0xdf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe0, 0xe1 ,0xe2, 0xe3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe4, 0xe5 ,0xe6, 0xe7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe8, 0xe9 ,0xea, 0xeb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xec, 0xed ,0xee, 0xef

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf0, 0xf1 ,0xf2, 0xf3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf4, 0xf5 ,0xf6, 0xf7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf8, 0xf9 ,0xfa, 0xfb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xfc, 0xfd ,0xfe, 0xff
#endif
};

#else  //!HIMAGE5900M_IR13_V2
const BYTE ir_mapcode[]=
{
  IRC_SLOW,     IRC_PAUSE,     IRC_TITLEMENU,		IRC_REPEAT, //0x00, 0x01 ,0x02, 0x03
  IRC_AUD_LANGUAGE,     IRC_EJECT,      IRC_P10,/*_RESUME*/  	IRC_RIGHT,      //0x04, 0x05 ,0x06, 0x07
  IRC_DOWN,     IRC_0,           IRC_CLEAR/*GOTO*/, 		IRC_GOTO,      //0x08, 0x09 ,0x0a, 0x0b
  IRC_PBC,     IRC_SUBP,           IRC_LEFT,     		IRC_NEXT,      //0x0c, 0x0d ,0x0e, 0x0f
  IRC_CHANNEL,    IRC_ANGLE,      	 IRC_4,        	    IRC_5,     //0x10, 0x11 ,0x12, 0x13
  IRC_6,    IRC_3,      	 IRC_ZOOM,  		IRC_SLOW,         //0x14, 0x15 ,0x16, 0x17
  IRC_2,     IRC_SUBP,      	 IRC_STOP,     	    IRC_7,         //0x18, 0x19 ,0x1a, 0x1b
  IRC_1,     IRC_TIME,      	 IRC_PREV,  	    IRC_ANGLE,         //0x1c, 0x1d ,0x1e, 0x1f

  IRC_PBC,  IRC_LEFT,		 IRC_4,  		IRC_NULL,    //0x20, 0x21 ,0x22, 0x23
  IRC_CLEAR,     IRC_NULL,		 IRC_NULL,  		IRC_RETURN,    //0x24, 0x25 ,0x26, 0x27
  IRC_PLAY,     IRC_GOTO,		 IRC_AB,  		IRC_BACKWARD,    //0x28, 0x29 ,0x2a, 0x2b
  IRC_NULL,     IRC_NULL,		 IRC_ZOOM,  		IRC_NULL,    //0x2c, 0x2d ,0x2e, 0x2f

  IRC_PREV,     IRC_NULL,		 IRC_PREVIEW,  		IRC_DISPLAY,     //0x30, 0x31 ,0x32, 0x33
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x34, 0x35 ,0x36, 0x37
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x38, 0x39 ,0x3a, 0x3b
  IRC_NULL,     IRC_NULL,		 IRC_NULL,  		IRC_NULL,     //0x3c, 0x3d ,0x3e, 0x3f

  IRC_AB,  IRC_BOOK,	IRC_BACKWARD, 	IRC_FORWARD,    //0x40, 0x41 ,0x42, 0x43
  IRC_LEFT,   IRC_DOWN, 		IRC_PROGRAM,   	IRC_GOTO,//0x44, 0x45 ,0x46, 0x47
  IRC_UP,         IRC_PROGRAM,		IRC_PLAY_SELECT,     	IRC_POWER,     //0x48, 0x49 ,0x4a, 0x4b
  IRC_SETUP,        IRC_RETURN,     IRC_PREVIEW,  		IRC_DISPLAY,     //0x4c, 0x4d ,0x4e, 0x4f

  IRC_RETURN,  IRC_ZOOM,           IRC_REPEAT,     IRC_FORMAT,   //0x50, 0x51 ,0x52, 0x53
  IRC_6,     IRC_9, 		IRC_AB,   	IRC_RESUME,   //0x54, 0x55 ,0x56, 0x57
  IRC_3D,     IRC_MUTE,    		IRC_VOLUME_DN,  		IRC_VOLUME_UP,     //0x58, 0x59 ,0x5a, 0x5b
  IRC_AUD_LANGUAGE,     IRC_ROOT_MENU,		    IRC_8,  	IRC_LANGUAGE, //0x5c, 0x5d ,0x5e, 0x5f

  IRC_PAUSEPLAY,   IRC_NULL,		IRC_NULL,  		IRC_NULL,     //0x60, 0x61 ,0x62, 0x63
  IRC_ZOOM,        IRC_UP,     IRC_DOWN,  IRC_LEFT,//0x64, 0x65 ,0x66, 0x67 
  IRC_RIGHT,  IRC_FREEZE,      IRC_9FRAMES,    IRC_NULL,     //0x68, 0x69 ,0x6a, 0x6b 

#ifdef HT1621_PANNEL //zyf 891108

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x6c, 0x6d ,0x6e, 0x6f
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x70, 0x71 ,0x72, 0x73
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x74, 0x75 ,0x76, 0x77
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x78, 0x79 ,0x7a, 0x7b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x7c, 0x7d ,0x7e, 0x7f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x80, 0x81 ,0x82, 0x83
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x84, 0x85 ,0x86, 0x87
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x88, 0x89 ,0x8a, 0x8b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_STOP,  //0x8c, 0x8d ,0x8e, 0x8f

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x90, 0x91 ,0x92, 0x93
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x94, 0x95 ,0x96, 0x97
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x98, 0x99 ,0x9a, 0x9b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x9c, 0x9d ,0x9e, 0x9f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa0, 0xa1 ,0xa2, 0xa3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa4, 0xa5 ,0xa6, 0xa7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa8, 0xa9 ,0xaa, 0xab
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xac, 0xad ,0xae, 0xaf

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb0, 0xb1 ,0xb2, 0xb3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb4, 0xb5 ,0xb6, 0xb7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xb8, 0xb9 ,0xba, 0xbb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xbc, 0xbd ,0xbe, 0xbf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc0, 0xc1 ,0xc2, 0xc3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc4, 0xc5 ,0xc6, 0xc7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xc8, 0xc9 ,0xca, 0xcb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xcc, 0xcd ,0xce, 0xcf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd0, 0xd1 ,0xd2, 0xd3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd4, 0xd5 ,0xd6, 0xd7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xd8, 0xd9 ,0xda, 0xdb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xdc, 0xdd ,0xde, 0xdf
  
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe0, 0xe1 ,0xe2, 0xe3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe4, 0xe5 ,0xe6, 0xe7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xe8, 0xe9 ,0xea, 0xeb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xec, 0xed ,0xee, 0xef

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf0, 0xf1 ,0xf2, 0xf3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf4, 0xf5 ,0xf6, 0xf7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xf8, 0xf9 ,0xfa, 0xfb
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xfc, 0xfd ,0xfe, 0xff
#endif
};
#endif     // test by chichang  






#if 0
const BYTE ir_mapcode[]=
{
  IRC_AB,     IRC_TIME,		IRC_VOLUME_DN,  		IRC_VOLUME_UP,//0x00, 0x01 ,0x02, 0x03
  IRC_NULL,     IRC_PREVIEW,		 IRC_PREV,  		IRC_RETURN,//0x04, 0x05 ,0x06, 0x07
  IRC_7 ,       IRC_PROGRAM,		IRC_EFFECT ,  		IRC_NULL,//0x08, 0x09 ,0x0a, 0x0b
  IRC_NULL,     IRC_RESUME,		IRC_KEY_RESET, 	IRC_CHANNEL,//0x0c, 0x0d ,0x0e, 0x0f
  
  IRC_NULL,     IRC_2,  		IRC_5 ,  		IRC_PLAY,//0x10, 0x11 ,0x12, 0x13
  IRC_EJECT ,   IRC_3,  		IRC_NULL,  		IRC_4,   //0x14, 0x15 ,0x16, 0x17
  IRC_STEP,     IRC_GOTO,		IRC_KEY_UP,		IRC_1,//0x18, 0x19 ,0x1a, 0x1b
  IRC_NULL,     IRC_NULL,		IRC_PAUSE, 		IRC_NULL,//0x1c, 0x1d ,0x1e, 0x1f


  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x20, 0x21 ,0x22, 0x23
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x24, 0x25 ,0x26, 0x27
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x28, 0x29 ,0x2a, 0x2b
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x2c, 0x2d ,0x2e, 0x2f

  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x30, 0x31 ,0x32, 0x33
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x34, 0x35 ,0x36, 0x37
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x38, 0x39 ,0x3a, 0x3b
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,  //0x3c, 0x3d ,0x3e, 0x3f
  
  IRC_FORWARD,     IRC_NULL,		IRC_KEY_DN,	IRC_REPEAT,//0x40, 0x41 ,0x42, 0x43
   IRC_NEXT,     IRC_MUTE,		IRC_NULL,  		IRC_BACKWARD,//0x44, 0x45 ,0x46, 0x47
  IRC_8,        IRC_9,  		IRC_0,   		IRC_FORMAT ,   //0x48, 0x49 ,0x4a, 0x4b
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,//0x4c, 0x4d ,0x4e, 0x4f
  
  IRC_PBC,     IRC_STOP,		IRC_DISPLAY ,  		IRC_NULL,//0x50, 0x51 ,0x52, 0x53
  IRC_NULL,     IRC_RANDOM,		IRC_P10,  		IRC_NULL,//0x54, 0x55 ,0x56, 0x57
  IRC_NULL,     IRC_6,  		IRC_NULL , 		IRC_NULL,//0x58, 0x59 ,0x5a, 0x5b
  IRC_NULL,     IRC_NULL,		IRC_INTRO,  		IRC_SLOW,//0x5c, 0x5d ,0x5e, 0x5f

  IRC_NULL,     IRC_10,		IRC_LANGUAGE,  		IRC_POWER,//0x60, 0x61 ,0x62, 0x63
  IRC_ZOOM,     IRC_UP,		IRC_DOWN,      IRC_LEFT,    //0x64, 0x65 ,0x66, 0x67 
  IRC_RIGHT,IRC_FREEZE,IRC_9FRAMES,IRC_NULL,                 //0x68, 0x69 ,0x6a, 0x6b 

#if 1  //def HT1621_PANNEL

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x6c, 0x6d ,0x6e, 0x6f
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x70, 0x71 ,0x72, 0x73
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x74, 0x75 ,0x76, 0x77
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x78, 0x79 ,0x7a, 0x7b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x7c, 0x7d ,0x7e, 0x7f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x80, 0x81 ,0x82, 0x83
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x84, 0x85 ,0x86, 0x87
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x88, 0x89 ,0x8a, 0x8b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_STOP,  //0x8c, 0x8d ,0x8e, 0x8f

  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x90, 0x91 ,0x92, 0x93
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x94, 0x95 ,0x96, 0x97
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x98, 0x99 ,0x9a, 0x9b
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0x9c, 0x9d ,0x9e, 0x9f


  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa0, 0xa1 ,0xa2, 0xa3
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa4, 0xa5 ,0xa6, 0xa7
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xa8, 0xa9 ,0xaa, 0xab
  IRC_NULL,     IRC_NULL,               IRC_NULL,               IRC_NULL,  //0xac,0xad ,0xae, 0xaf


#endif

};
#endif
