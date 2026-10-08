#ifndef 	_OSDISP_H_
#define   _OSDISP_H_
//#define 	enter_critical_section(n)	((regs0->tset[n])?TRUE:FALSE)
//#define 	leave_critical_section(n)	(regs0->tset[n] = 0)
//---------------------------------

//--global

enum	{
OSDISP_IGNORE,
OSDISP_INVAL,
OSDISP_NODISC,
OSDISP_ERR_DISC,

OSDISP_PLAY,
OSDISP_READ,
OSDISP_RESUME,
OSDISP_CLEAR,

OSDISP_SAVELOGO,
OSDISP_BROWSE,
OSDISP_RAN_CNL,
OSDISP_SEQPLAY,
OSDISP_RANDOM,

OSDISP_NULL=0xff
};
//---------------------------------
//dirup
enum{
	OSDISP_DIR_FULL,
		
	OSDISP_DIR_ZOOM,
	OSDISP_DIR_ROTATE,
	
	OSDISP_DIR_HL,
	OSDISP_DIR_BFUNCSTEP,
	OSDISP_DIR_KEY,
	OSDISP_DIR_PREVNEXT,
	OSDISP_DIR_PANEL,
	OSDISP_DIR_MIC,
	OSDISP_DIR_ECHO,
	OSDISP_DIR_VFD
};
//---------------------------------
//num
#define 	OSDISP_NUMPROG 		0x65
#define 	OSDISP_NUMSETUP 		0x66
#define 	OSDISP_NUMGOTO		0x67

//---------------------------------
//repeat
enum {
  	OSDISP_REP_IDLE ,
  	OSDISP_REP_TRACK ,			//DVD,repeat chapter
  	OSDISP_REP_DIRECTORY , 	// only for mp3
  	OSDISP_REP_DISC,			//DVD,repeat title
  	OSDISP_REP_DVDDISC ,		//
  	OSDISP_REP_FOLDER,		
};
//---------------------------------
//vol_lr
enum
{
	OSDISP_VOL_STEREO,
	OSDISP_VOL_CHL,
	OSDISP_VOL_CHR,
	OSDISP_VOL_AUTO_L,
	OSDISP_VOL_AUTO_R
};
//---------------------------------
//goto
enum{
	OSDISP_GOTO_CNL,
	OSDISP_GOTO_ON,		
	OSDISP_GOTO_PROGCNL,
};
//----------------------------------
//display
enum{
	OSDISP_DIS_OFF,
	OSDISP_DIS_FIR,
	OSDISP_DIS_SED,
	OSDISP_DIS_TIME,
	/*
	OSDISP_DIS1_DVD,
	OSDISP_DIS2_DVD,
	OSDISP_DIS1_CDVCD,
	OSDISP_DIS2_CDVCD,
	OSDISP_DIS1_CDROM,
	*/
	OSDISP_DIS_VFD,
};



//---------------------------------
//program
enum{
	OSDISP_PROG_ON,				//KEEP(PROG MENU)
	OSDISP_PROG_PLAY,
	OSDISP_PROG_CLEAR,
	OSDISP_PROG_CNL,				//DIS("PROG CANCEL")
	OSDISP_PROG_NUM,
	OSDISP_PROG_DIR,
	OSDISP_PROG_ENTER,

	OSDISP_PROG_JPGMODE=0x10,	//to see under info
};

/*
    "WIPE TOP",                     // 0
    "WIPE BOTTOM",                  // 1
    "WIPE LEFT",                    // 2
    "WIPE RIGHT",                   // 3
    "DIGONAL WIPE LEFT TOP",        // 4
    "DIGONAL WIPE RIGHT TOP",       // 5
    "DIGONAL WIPE LEFT BOTTOM",     // 6
    "DIGONAL WIPE RIGHT BOTTOM",    // 7
    "EXTEND FROM CENTER H",         // 8
    "EXTEND FROM CENTER V",         // 9
    "COMPRESS TO CENTER H",         // 10
    "COMPRESS TO CENTER V",         // 11
    "WINDOW H",                     // 12
    "WINDOW V",                     // 13
    "WIPE FROM EDGE TO CENTER",     // 14
    "RANDOM",                       // 15
    "NONE",                         // 16
*/
//----------------------------------

//repeatab
enum {
  	OSDISP_REP_AB_IDLE,			//DIS("A-B CANCEL")
  	OSDISP_REP_FIND_A,			//DIS("REPEAT A-")
  	OSDISP_REP_FIND_B,			//DIS("REPEAT A-B")
  };
//--------------------------------
//tv_format
enum 
{
	OSDISP_TVMODE_NTSC,			//DIS("NTSC")
       OSDISP_TVMODE_NTSCJ,
	OSDISP_TVMODE_PAL60,			//DIS("PAL60")
	OSDISP_TVMODE_PAL,			//DIS("PAL")
       OSDISP_TVMODE_PALM,			//DIS("PAL-M")
   	OSDISP_TVMODE_PALN,			//DIS("PAL-N")
   	OSDISP_TVMODE_PALNC,			//DIS("PAL-NC")
	OSDISP_TVMODE_AUTO,			//DIS("AUTO")
   	OSDISP_TVMODE_MAX,
};
//---------------------------------
//p_scan & tv_sys_mode
enum 		
{
	OSDISP_PC_VGA,
	OSDISP_P_SCAN, 
	OSDISP_INTERLACE,
	OSDISP_TV_RGB,
	OSDISP_TV_SVIDEO,
};
//---------------------------------
//cdtype
enum    {
    	OSDISP_TYPE_UNKNOWN=0,
   	OSDISP_TYPE_CDDA=1,
   	OSDISP_TYPE_CDROM,
    	OSDISP_TYPE_VCD10,
    	OSDISP_TYPE_VCD20,
    	OSDISP_TYPE_SVCD,
    	OSDISP_TYPE_DVD,
    	OSDISP_TYPE_CVD,
    	OSDISP_TYPE_DVDROM,
};

//---------------------------------
//zoom
enum		
{
	OSDISP_ZOOM0,			//LB or Normal
	OSDISP_ZOOM1,			//ps
	OSDISP_ZOOM2,			//zoom in x1.3
	OSDISP_ZOOM3,			//zoom in x1.5
	OSDISP_ZOOM4,			//zoom in x2
	OSDISP_ZOOM5,			//reserved  zoom in x3
	OSDISP_ZOOM6,			//zoom out x0.75
	OSDISP_ZOOM7,			//zoom out x0.67
	OSDISP_ZOOM8,			//zoom out x0.5
};
//---------------------------------
//slow
enum{
	OSDISP_SF2=2,			//KEEP(SF2)
	OSDISP_SF3,
	OSDISP_SF4,
	OSDISP_SF5,
	OSDISP_SF6,
	OSDISP_SF7,
	OSDISP_SF_MAX
};
//---------------------------------
//fr/ff
enum{
 	OSDISP_off=	0,
	OSDISP_F2=2,
	OSDISP_F4=4,
	OSDISP_F8=8,
	OSDISP_F20=14
};
//---------------------------------
//stop
enum{
	OSDISP_STOP,
	OSDISP_PRE_STOP
};
//---------------------------------
//pause
enum{
	OSDISP_PAUSE,						//KEEP("PAUSE")
 	OSDISP_STEP						//KEEP("STEP")
};
//---------------------------------
//prev
enum{
	OSDISP_PREV,						//DIS("PREV")
	OSDISP_PREV_CHAPTER				//DIS("PREV CHAPTER")
};
//---------------------------------
//next
enum{
	OSDISP_NEXT,						//DIS("NEXT")
	OSDISP_NEXT_CHAPTER				//DIS("NEXT CHAPTER")
};

//menuplay

enum{
 	OSDISP_MENUPLAY,			//DIS("MENU")
	OSDISP_MENUON,			
	OSDISP_MENUOFF,		
};


//---------------------------------
//open
#define 	OSDISP_OC_CLOSE		0		//DIS("CLOSE")
#define 	OSDISP_OC_OPEN		1		//DIS("OPEN")
//---------------------------------
// 3d	&to see structure osdisp_3d_t
#define   OSDISP_3DMASK_PAGE	0xc0	//page selection : (0 : srnd  1 : EQ  2 : band  3 :  key)
#define 	OSDISP_3DMASK_LEVEL	0x30	//0: tab   1:item selection   2:EQ adjustment
#define 	OSDISP_3DMASK_SEL		0x0f	//the currently selection
#define 	OSDISP_3DOFF			0		//CLEAR
//---------------------------------
//mute
#define 	OSDISP_MUTE			0		//KEEP("MUTE")
#define 	OSDISP_DEMUTE			1		//CLEAR
//---------------------------------
//vol +/-
#define 	OSDISP_VOL_MAX 		16		//DIS(PIC&VALUE 0-15)	
//---------------------------------
//setup
#define 	OSDISP_SETUP			0		//KEEP(SETUP MENU)
//---------------------------------
//title
#define 	OSDISP_TITLE			0		//DIS("TITLE")
//---------------------------------
//return
#define 	OSDISP_RETURN    		0		//DIS("RETURN")
//---------------------------------
//enter
#define 	OSDISP_ENTER_FULL		0		//RESERVED
//---------------------------------
//sub_title
#define 	OSDISP_TITLE_OFF		0		//DIS("OFF")
#define 	OSDISP_SUBTIT_MASK	0x0f	//0-3 bit:当前字幕编码；4-7 bit:碟片包含总字幕 数										
//---------------------------------
//angle
#define 	OSDISP_ANGLE_MAST	0X0f	//0-3 bit:当前角度编码；4-7 bit:碟片包含角度 数
//---------------------------------
//language
#define 	OSDISP_LANGUAGE_MAST 0x0f

//---------------------------------
//preview
#define  	OSDISP_9FRAME			0X00
#define   OSDISP_INTRO			0x01




#define OSDISP_INFO_MAX	20

//sub_title language
typedef struct
{
	BYTE lang1;
	BYTE lang2;
	BYTE audio_ch;
}osdisp_title_lang;
//preview
typedef struct
{
	BYTE tt;
	
}osdisp_preview_t;




//display
typedef struct
{
	BYTE time_h;		//0
	BYTE time_m;
	BYTE time_s;
	union
	{
		struct 
		{
		BYTE tt;
		BYTE tt_ns;
		BYTE ch;
		BYTE ch_ns;	
		}dvd;
		struct
		{
		BYTE trk;
		BYTE trk_h;
		BYTE trk_ns;
		BYTE trk_ns_h;
		}vcd;
	};
	BYTE mute_pbc;
	BYTE rep_mod;
	BYTE angle;			//9
	
	BYTE language;		//a
	BYTE audio_lang1;	//b
	BYTE audio_lang2;	//c
	BYTE subtitle;		//d
	BYTE subtitle_lang1;	//e
	BYTE subtitle_lang2;	//f
	BYTE audio_ch;		//10
	BYTE file_type;		//11
}osdisp_disp_t;

//---3d
typedef struct
{
	BYTE index_xy;		//index-y: 0-3bit   index-x:4-7bit
	BYTE eq_ch[7];		//eq channel
}osdisp_3d_t;

//--program
typedef struct
{
	BYTE index_xy;
	BYTE prog_val;		//index-y: 0-3bit   index-x:4-7bit
	BYTE prog_index;	//dis the old value set before
	BYTE prog_tc;		// 1:dvd&cdrom  0 :others
}osdisp_prog_t;

//=============================================
#define 	  OSDIR_NULL		0xfe
#define 	  OSDIR_GLOBAL		0xfd
#define     OSDIR_CDTYPE		0xfc
//------
#define	  OSDIR_POWER         0xff
#define	  OSDIR_OPEN          0x0c
#define	  OSDIR_NUM_1         0x01
#define	  OSDIR_NUM_2         0x02
#define	  OSDIR_NUM_3         0x03
#define	  OSDIR_VOL_ADD       0x11
#define	  OSDIR_NUM_4         0x04
#define	  OSDIR_NUM_5         0x05
#define	  OSDIR_NUM_6         0x06
#define	  OSDIR_VOL_SUB       0x12
#define	  OSDIR_NUM_7         0x07
#define	  OSDIR_NUM_8         0x08
#define	  OSDIR_NUM_9         0x09
#define	  OSDIR_DISPLAY       0x1f
#define	  OSDIR_NUM_0         0x00
#define	  OSDIR_NUM_10        0x0b
#define	  OSDIR_GOTO          0x23
#define	  OSDIR_SCAN_VGA      0x5b
#define	  OSDIR_TITLE         0x49
#define	  OSDIR_MENU          0x50
#define	  OSDIR_RETURE        0x18
#define	  OSDIR_STOP          0x19
#define	  OSDIR_VOL_LR        0x2f
#define	  OSDIR_PROGRAM       0x34
#define	  OSDIR_PAL_NTSC      0x35
#define	  OSDIR_ZOOM          0x28
#define	  OSDIR_SETUP         0x4b
#define	  OSDIR_PREV          0x1d
#define	  OSDIR_NEXT          0x1e
#define	  OSDIR_PAUSE_STEP    0x15
#define	  OSDIR_UP            0x29
#define	  OSDIR_LEFT          0x2b
#define	  OSDIR_RIGHT         0x2c
#define	  OSDIR_DOWN          0x2a
#define	  OSDIR_ENTER         0x48
#define	  OSDIR_PLAY          0x16
#define	  OSDIR_SLOW          0x13
#define	  OSDIR_FR            0x1b
#define	  OSDIR_FF            0x1c
#define	  OSDIR_REPEAT        0x21
#define	  OSDIR_PREVIVE       0x32
#define	  OSDIR_AB            0x20
#define	  OSDIR_3D            0x4d
#define	  OSDIR_SUB_TITLE     0x45
#define	  OSDIR_ANGLE         0x46
#define	  OSDIR_LANGUAGE      0x47
#define	  OSDIR_MUTE          0x0d
#endif


