#include "user_init.h"
#include "global.h"
#include "ircode.h"
#include "irconfig.h"

const BYTE ir_mapcode[]=
{
  IRC_EJECT,    IRC_3,     	    IRC_6,			IRC_9, //0x00, 0x01 ,0x02, 0x03
  IRC_NULL,     IRC_2,          IRC_5,  		IRC_8,      //0x04, 0x05 ,0x06, 0x07
  IRC_NULL,     IRC_1,          IRC_4, 			IRC_7,      //0x08, 0x09 ,0x0a, 0x0b
  IRC_NULL,    IRC_VOLUME_UP,  IRC_VOLUME_DN,  IRC_DISPLAY, //0x0c, 0x0d ,0x0e, 0x0f
  
  #if defined(TWO_KEY_SWITCH_TWO_SUBTITLE) || (defined(DVB1000_NON_OS) && defined(SUPPORT_SUBTITLE))
  IRC_PAUSE,    IRC_MUTE,    	IRC_2ND_SUBTITLE,     IRC_PREV,   //0x10, 0x11 ,0x12, 0x13
  #elif defined(MALATA_KEY)
  IRC_UP_NEXT,    IRC_DOWM_PREV,    	IRC_LEFT_FR,     IRC_RIGHT_FF,   //0x10, 0x11 ,0x12, 0x13 
  #else
  IRC_PAUSE,    IRC_MUTE,    	IRC_NULL,       IRC_PREV,   //0x10, 0x11 ,0x12, 0x13
  #endif
  
  IRC_SLOW,    	IRC_CHANNEL,    IRC_AUD_LANGUAGE,IRC_PBC,         //0x14, 0x15 ,0x16, 0x17
  IRC_AB,     	IRC_3D,         IRC_ANGLE,     	IRC_NULL,         //0x18, 0x19 ,0x1a, 0x1b
  IRC_POWER,   IRC_PREVIEW,	IRC_SUBP, 	    IRC_BACKWARD,         //0x1c, 0x1d ,0x1e, 0x1f
  
  IRC_REPEAT, IRC_SETUP,		IRC_DOWN,  	IRC_PAUSEPLAY,    //0x20, 0x21 ,0x22, 0x23

  IRC_STOP,     IRC_NULL,		IRC_NULL,  	IRC_NULL,    //0x24, 0x25 ,0x26, 0x27
  IRC_NULL,      IRC_NULL,		IRC_1,  		IRC_2,          //0x28, 0x29 ,0x2a, 0x2b
  IRC_3,           IRC_4,		       IRC_NULL,  	IRC_NULL,    //0x2c, 0x2d ,0x2e, 0x2f

#ifdef IR_SWITCH_DVD_USB_CARD_AVIN_DVB
      #ifdef  SUPPORT_DISABLE_IR_SOURCE_CHANGE
       IRC_DISPLAY,     IRC_TITLEMENU,		IRC_ZOOM,  	IRC_NULL,     //0x30, 0x31 ,0x32, 0x33	  
      #else//else=>#ifdef SUPPORT_DISABLE_IR_SOURCE_CHANGE
  IRC_DISPLAY,     IRC_TITLEMENU,		IRC_ZOOM,  		IRC_DVD_USB_CARD_AVIN_DVB,     //0x30, 0x31 ,0x32, 0x33
      #endif//end=> #ifdef SUPPORT_DISABLE_IR_SOURCE_CHANGE
#else  
  IRC_DISPLAY,     IRC_TITLEMENU,		IRC_ZOOM,  		IRC_DVB_DVD,     //0x30, 0x31 ,0x32, 0x33
 #endif
 
  IRC_NULL,     IRC_UP,		IRC_PBC,  		IRC_AB,     //0x34, 0x35 ,0x36, 0x37
  IRC_LEFT,     IRC_SELECT,		IRC_RIGHT,  		IRC_PAUSE,     //0x38, 0x39 ,0x3a, 0x3b
  IRC_NULL,     IRC_NULL,		IRC_NULL,  		IRC_NULL,     //0x3c, 0x3d ,0x3e, 0x3f

  IRC_0,  	    IRC_PROGRAM,	  IRC_RIGHT, 		IRC_RETURN,    //0x40, 0x41 ,0x42, 0x43
  IRC_P10,   	  IRC_FORMAT, 		IRC_ZOOM,     IRC_UP,//0x44, 0x45 ,0x46, 0x47
#ifdef DVB1000_NON_OS
  IRC_GOTO,     IRC_DVB_DVD,     IRC_SELECT,    IRC_DOWN,     //0x48, 0x49 ,0x4a, 0x4b
#else
  #if 0//def IR_SWITCH_CD_USB_CF_OTHER
  IRC_GOTO,     IRC_CD_USB_CF_OTHER,	        IRC_SELECT,   IRC_DOWN,     //0x48, 0x49 ,0x4a, 0x4b
  #elif defined(FILE_MODE_WRITE)
  IRC_GOTO,     IRC_FM_WRITE,	        IRC_SELECT,   IRC_DOWN,     //0x48, 0x49 ,0x4a, 0x4b
  
  #elif defined(DMA_DVD_SWITCH)
  IRC_GOTO,      IRC_SWITCH_DMA_DVD,	        IRC_SELECT,   IRC_DOWN,     //0x48, 0x49 ,0x4a, 0x4b  
 
  #else
  IRC_GOTO,     IRC_NULL,	        IRC_SELECT,   IRC_DOWN,     //0x48, 0x49 ,0x4a, 0x4b
  #endif
#endif  
  IRC_P_SCAN,   IRC_SETUP,      IRC_LEFT,		IRC_TITLEMENU,     //0x4c, 0x4d ,0x4e, 0x4f

  IRC_5,  	IRC_6,       IRC_7,     	IRC_8,   //0x50, 0x51 ,0x52, 0x53
  IRC_9,         IRC_0,       IRC_NULL,   	  IRC_AUD_LANGUAGE,   //0x54, 0x55 ,0x56, 0x57
  IRC_NULL,     IRC_NULL,    	IRC_NULL,  		IRC_NULL,     //0x58, 0x59 ,0x5a, 0x5b
  IRC_FORWARD,  IRC_NULL,		  IRC_SLOW,  		IRC_NULL, //0x5c, 0x5d ,0x5e, 0x5f

  IRC_P10,   	IRC_GOTO,		    IRC_PREV,  		IRC_NULL,     //0x60, 0x61 ,0x62, 0x63
  IRC_NULL,     IRC_NULL,       IRC_NEXT,     IRC_NULL,//0x64, 0x65 ,0x66, 0x67 
  IRC_NULL,  	  IRC_NULL,      	IRC_BACKWARD,    	IRC_NULL,     //0x68, 0x69 ,0x6a, 0x6b 

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x6c, 0x6d, 0x6e, 0x6f
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_ANGLE,       // 0x70, 0x71, 0x72, 0x73
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x74, 0x75, 0x76, 0x77
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x78, 0x79, 0x7a, 0x7b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x7c, 0x7d, 0x7e, 0x7f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x80, 0x81, 0x82, 0x83
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x84, 0x85, 0x86, 0x87
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x88, 0x89, 0x8a, 0x8b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x8c, 0x8d, 0x8e, 0x8f

    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x90, 0x91, 0x92, 0x93
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x94, 0x95, 0x96, 0x97
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x98, 0x99, 0x9a, 0x9b
    IRC_NULL,       IRC_NULL,           IRC_NULL,       IRC_NULL,       // 0x9c, 0x9d, 0x9e, 0x9f

    IRC_NULL,       IRC_NULL,           IRC_SUBP,       IRC_NULL,       // 0xa0, 0xa1, 0xa2, 0xa3

};
