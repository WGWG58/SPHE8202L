/*
 *************************************************************************
 * File Name:   read.h
 * Created:     2003/8/1 12:49PM Maoyong 
 * Description: Repeat reading implement header file
 * Maintain:    Maoyong 2004.06.09 rewrite
 ************************************************************************
 */
#include "cfont.h"
#include "icon.h"

#ifdef SUPPORT_REP_READ
/* FUDO DSP Command types definition*/
enum{
    FUDO_CMD_STOP = 0,
    FUDO_CMD_REC = 1,
    FUDO_CMD_PLAY,
    FUDO_CMD_PAUSE,
    FUDO_CMD_Q_H,       //high record quality
    FUDO_CMD_Q_M,       //middle record quality
    FUDO_CMD_Q_L,       //low record quality
};

/* FUDO Operation mode definition*/
enum{
    FUDO_GENDU = 0,
    FUDO_REPEAT = 1,
    FUDO_COMPARE,  
};

/* FUDO record mode definition*/
enum{
    REC_Q_HIGH = 0,
    REC_Q_MIDDLE = 1,
    REC_Q_LOW,  
};

/*for uReadStatus: current read status */
enum
{
    READ_ST_NONE = 0,
    READ_ST_RECORDING = 1,
    READ_ST_PLAYBACK,
};

enum
{
	UNSEL_BTN_NORM = 0,     //button not selected, no Up,Down,Left,Right to this Button
	UNSEL_BTN_HL = 1,       //button not selected, Up,Down,Left,Right to this Button
	SEL_BTN_NORM,           //button is selected, no Up,Down,Left,Right to this Button	
	SEL_BTN_HL              //button isselected, Up,Down,Left,Right to this Button	
};

enum
{
    SET_NE=0,
    SET_BS=0x1,
    SET_FUNC=0x2,
    SET_CHART=0x3,
    SET_NM = 0x04,
    SET_SPACE=0x5,
    SET_SCALE=0x6,
};

//keep color style with setup and program panel
#define TRANS_CLR		    0
#define BG_CLR      		6
#define FONT_CLR  		    11
#define BLACK_CLR           11
#define WHITE_CLR           2
#define YELLOW_CLR		    7
#define ANTI_BG_CLR 	    5
#define ANTI_FONT_CLR       2
#define INFO_FONT_CLR       14
#define SEL_FONT_CLR	    4

//button up/down state definition
#define BTN_DOWN   		    1
#define BTN_UP        		0

//fudu osd main panel region
#define READ_REGION         2
#define READ_REG_W          25  //16pixel per unit
#define READ_REG_H          172   //24pixel per unit

#define ORI_EQ              0   //original EQ
#define REC_EQ              1   //record voice EQ

//menu level definition
#define MAIN_LEVEL          0
#define SUB_LEVEL           1

//page and item definition
#define MAX_READ_ITEM       4
#define MAX_ITEM_SEL        6

#define REC_MODE_ITEM       0
#define READ_MODE_ITEM      1
#define REPTIMES_ITEM       2
#define EQ_ITEM             3

#define READ_BTN_WIDTH      15  //setup rep read  button length(16pixels UNIT)
#define PB_BTN_WIDTH        4   //playback/rec control button length(16pixels UNIT)

#define READ_SUB_MENU_X     17  //for sub menu start
#define EQ_BG_START_Y       14  //for EQ bg start Y (pixel)
#define INFO_STR_X          1   //for information display
#define INFO_STR_Y          34

#define DEF_REP_TIMES       1

//used osd string releated definition 
#define MAX_READ_OSD_LANGS  2   //English and Chinese 
#define MAX_OSD_STR     15

//used string ID definition
#define STR_OS_REC_MODE     0
#define STR_OS_HIGH         1 
#define STR_OS_MIDDLE       2
#define STR_OS_LOW          3
#define STR_OS_READ_MODE    4 
#define STR_OS_GENDU        5
#define STR_OS_COMPARE      6
#define STR_OS_REPEAT       7
#define STR_OS_REP_TIMES    8
#define STR_OS_READ_EQ      9
#define STR_OS_TIME_PROMP   10

//chinese string definition
#define OS_REC_MODE         _cat4_(Ch_lu, Ch_yin, Ch_mo, Ch_shi) 
#define OS_REC_HIGH         Ch_gao
#define OS_REC_MIDDLE       Ch_zhong
#define OS_REC_LOW          Ch_di
#define OS_READ_MODE        _cat4_(Ch_fu, Ch_du, Ch_mo, Ch_shi) 
#define OS_READ_GENDU       Ch_du
#define OS_READ_COMPARE     _cat_(Ch_dui, Ch_bi1)
#define OS_READ_REPEAT      _cat_(Ch_fu, Ch_du)
#define OS_REP_TIMES       _cat3_(Ch_chong, Ch_fu, Ch_shu4)
#define OS_READ_EQ          OS_EQ

//flow control flag in mediamainloop
#define PRE_MAIN_LOOP       0
#define IN_MAIN_LOOP        1
#define POST_MAIN_LOOP      2

//some utilization marco 
#define IsReadSetPBTimes()      ( (full_scrn & READ) && \
                                (index_y == REPTIMES_ITEM)&&\
                                uReadMenuLevel )

#define SetReadRecording()      ( uReadStatus = READ_ST_RECORDING )
#define SetReadPlayback()       ( uReadStatus = READ_ST_PLAYBACK )
#define IsReadRecording()       ( uReadStatus == READ_ST_RECORDING )
#define IsReadPlayback()        ( uReadStatus == READ_ST_PLAYBACK )
#define IsReadMode()            ( (full_scrn & READ) && ( IsReadRecording()||IsReadPlayback() ) )  
                                    
#define IsReadGendu()           ( (full_scrn & READ) && (uFudoMode == FUDO_GENDU) )
#define IsReadCompare()         ( (full_scrn & READ) && (uFudoMode == FUDO_COMPARE) )
#define IsReadRepeat()          ( (full_scrn & READ) && (uFudoMode == FUDO_REPEAT) )
                                    
UINT8 	uFudoMode;              //compare/repeat/follow read(gendu)
UINT8   uRecordMode;            //record quality setting   
UINT8 	uPlaybackTimes;         //the set playback times
int     uPBTimesSetting;        //used for user input number to setting 
UINT8   uRealPBTimes;           //the real playback times used in flow control
UINT8   uPlaybackFlag;          //for playback control. 1 = paly music , 0: red/playback rec/follow read 
UINT8   uReadMenuLevel;         //read menu level
UINT8   uReadSelMaxIndex;       //the sub menu's useful selection items number
UINT8   uReadShowEq;            //the flag to show EQ in repeat mode
UINT8   uReadEqType;            //record EQ /original music EQ
UINT8   uReadStatus;            //recording or playback

extern  BYTE index_y2;      
extern  BYTE index_y_start;

//function prototype for external calling
void CancelRead(void);
void InitRead(void);
void ClearReadMode(void);
int RepReadSendCmd(UINT8 uCmdType);
void ReadShowPromptInfo(UINT8 uShowHide);
void DisplayReadEq(UINT8 type, BYTE r);
UINT32 PollingRecBufStatus(void);
UINT32 MainLoopCtrlReadMode(UINT32 uFlag);
void RepBCtrlReadMode(void);
#endif  //#ifdef SUPPORT_REP_READ


