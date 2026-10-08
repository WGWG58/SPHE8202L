#ifndef __NAVDATA_H
#define __NAVDATA_H
#include "types.h"
#include "udf_167.h"
#include "global.h"
#include "fs96602.h"
#include "fsGUI1.h"
#include "psd.h"

typedef struct {
	UINT8	dY, dCb, dCr;
} DSV_Palette;

typedef struct {
	UINT8	h, m, s, f;
	// tc_flag;
} PlayBack_Time;

typedef struct {
	UINT32 dC_CAT;
	//UINT32 dC_PBTM;
	PlayBack_Time dC_PBTM;
	UINT32 dC_FVOBU_SA, dC_LVOBU_SA;
	UINT16 dC_LVOBU_SA2EA;// dC_LVOBU_EA = dC_LVOBU_SA+dC_LVOBU_SA2EA
	//  UINT32 dC_FILVU_EA;
	//	UINT16 dC_VOB_IDN;
	//	UINT8 dC_IDN;
} DSV_Cell;

typedef struct {
	UINT32 dATS_PG_CNT;
	//UINT8 bATS_PG_EN_CN;
	//UINT32 dATS_PG_PA_TM;	
	UINT32 dATS_PG_PB_TM;
} ATS_PGI;

typedef struct {
	//UINT8 bATS_C_IXN;
	//UINT8 bATS_C_TY;
	UINT32 dATS_C_SA;
	UINT32 dATS_C_EA;
} ATS_C_PBI;

typedef struct {
	UINT8 bASVUN;
	UINT8 bASV_DMD;
	UINT16 sATS_ASV_PBI_SA;
	UINT16 sATS_ASV_PBI_EA;
} ATS_PG_ASV_PBI_SRP;

typedef struct {
	UINT8 bDlist[10];
} DLIST;

typedef struct {
	ATS_PGI pg[100];
	ATS_C_PBI cell[256];
	UINT8 asv[4096];
} ATS_PG_CELL;

typedef struct {
	UINT8 b[8];
} t_NCMD;

typedef struct {
	UINT16 PTL_ID_FLD;
} t_PTL_ID_FLD;

typedef struct {
	//UINT16 PTL_LVL;
	t_PTL_ID_FLD VTS[100];//PTL_ID_FLD_VMG + PTL_ID_FLD_VTS
} t_PTL_MAI;

typedef struct
{
	//UINT8 reserv;
	UINT8 ATT_CAT;
	UINT16 ATT_PG_Ns;		
	//UINT8 ATT_AGL_Ns;
	UINT32 ATT_PB_TM;
	UINT8 ATSN;
	//UINT32 ATS_SA;
}t_ATT_SRP_PB;

typedef struct {
	UINT8 TT_PB_TY;
	UINT16 PTT_Ns;	
	UINT16 TT_PTL_ID_FLD;
	UINT8 VTSN;
	//UINT32 MAX_TM_MAP;
} t_TT_SRP_PB;

typedef union
{
	t_TT_SRP_PB vtt;
#ifdef DVD_AUDIO	   			
	t_ATT_SRP_PB att;
#endif	
} t_AV_SRP_PB;

#define dTT_SRP_Ns_MAX        100

//#ifdef DVD_AUDIO	   	//terry,2003/8/3 06:08PM,tmp. mark it!!
#define dAST_ATRT_MAX         128
#define dVTS_MU_AST_ATRT_MAX  288
//#else
//#define dAST_ATRT_MAX         64
//#define dVTS_MU_AST_ATRT_MAX  192
//#endif

typedef struct
{
	// RSM saved info
	UINT8 dRSM_Domain;
	UINT8 dRSM_Cell;
	UINT32 dRSM_End_Addr;
	UINT32 dRSM_NV_PCK;	
	UINT8 dRSM_PGN;
	UINT8 dRSM_LoopCount;
	UINT8 dRSM_PGPlayed[13];		// for shuffle mode
	
	UINT16 dRSM_TTN;
	UINT16 dRSM_VTS_TTN;
	UINT16 dRSM_TT_PGCN;
	UINT16 dRSM_PTTN;
	UINT16 dRSM_HL_BTNN;
	UINT16 dRSM_PTL_LVL;
	UINT16 dRSM_AGLN;
	UINT16 dRSM_SPSTN;
	UINT16 dRSM_ASTN;
	UINT16 dRSM_NP_NV_TMR;//axel 0323
} t_RSM_INFO;
#include "ncmd.h"

#define NAV_DATA_ACCESS			(0)
#define BITSTREAM_ACCESS		(1)
#define SLIDE_SHOW_MD                   (0x00)
#define BROWSER_MD                      (0x01)

#ifdef MINUS_VR_AUTH_PLAYBACK

#define MAX_TM_ENT		2160	//6 Hours
#define MAX_VOBU_ENT	21600	//6 Hours

typedef struct
{
	UINT8 ENTRY[7];
	//UINT16 	VOBU_ENTN;
	//UINT8	TM_DIFF;
	//UINT32	VOBU_ADR;	
}TIME_ENTRY;



typedef struct
{
	UINT8 ENTRY[3];
}VOBU_ENTRY;

typedef struct
{
	UINT8 EP_PTM[6];
}sM_C_EPI;

//linrc move to memmap0.h
//Temporary Location for TM_ENT and VOBU_ENT
//#define TM_ENT_SA 		(SDRAM_BASE_CACHED+4002*1024)	//(15K 6 HOURs)
//#define VOBU_ENT_SA 	(SDRAM_BASE_CACHED+4017*1024)	//(127K 6 HOURs)
//#define M_C_EPI_SA 		(SDRAM_BASE_CACHED+4144*1024) //5994Bytes


#define MAX_SCENE_LIST_LEN		99
#define MAX_CHAPTER_LIST_LEN	99

typedef struct tagChapter
{
	UINT16	CN;		  		  // Cell Number
	UINT32 	PTM;			// Point
}CHAPTER_S;

typedef struct tagChapterDel
{
	UINT16	CN;		  		  // Cell Number
	UINT16 	Serial;			// Point
}CHAPTER_DEL_S;


typedef struct tagChapterLIST{
    CHAPTER_S 		pInsertList[MAX_CHAPTER_LIST_LEN]; //chapters data
    CHAPTER_DEL_S 	pDeleteList[MAX_CHAPTER_LIST_LEN];
    UINT8 	Original;		//Original Title or PLaylist Title?
    UINT8 	PG_PLN;			//PGN of original/ PLN for plalist.
    BYTE nInsert_Ns;                     //Number of Chapters
    BYTE nDelete_Ns;		//Number of deleted Chapters.
}CHAPTERLIST_S;


#endif//#ifdef MINUS_VR_AUTH_PLAYBACK

//terry,2004/12/22 06:54PM
#define SEL_AUDIO_MD                    (0x01<<0)
#define SEL_SUBTITLE_MD                 (0x01<<1)
#define USER_HL_MODE                    (0x01<<2)
#define SEL_SUBTITLE_OK                 (0x01<<3)
#define SEL_SP_VTSM                     (0x01<<4) 
#define SEL_SP_MENU_OK                  (0x01<<5) 
 
#define SUP_GET_ID_0x7F                 (0x007f) //include on/off flag (0x40)
#define SUP_GET_ID_0x3F                 (0x003f) //only id
#define SUP_OFF_DEF                     (0xffbf)
#define SUP_ON_DEF                      (0x0040)


#define SIM_USE
/*
* All of the global variables used by Navigator are placed here.
*/
typedef struct
{		
	UINT8 dAv_AST_Ns;//display use
	UINT8 dAv_SPST_Ns;//display use
	UINT8 dAudio_coding_md;//display use,PE use ,declare in user use
	UINT8 dNs_Audio_ch;//display use
	
	// Navigator Parameters
	UINT16	GPRM_mode;	// 1: counter, 0: reg
	
#ifdef DVD_AUDIO	
	UINT16	SPRM[26];   //AU9-3
	UINT16	GPRM[17];	// GPRM[16] as a temp reg for internal usage
#else
    UINT16	SPRM[23];
    UINT16	GPRM[17];	// GPRM[16] as a temp reg for internal usage
#endif	
	UINT16  audio_language;
    UINT16  subtitle_language;
	
	// Navigator State
	UINT8		CurrState;
	UINT8		CurrDomain;
	
	// current PGC info
	// logic sector number(=LBA), start address
	UINT32	CurrPGC_LSN;
	UINT32	CurrPGC_SA; //axel , match DVD-Part III 2004/7/14 
	
	// VMGM
	UINT8	VMG_CAT_RM;//region code
	UINT32	dVMGM_VOBS_SA;//VMGM VOB Set start address
	
	UINT32  dTT_SRPT_SA;
	UINT32	dVMGM_PGCI_UT_SA;
    UINT8   dTT_SRP_Ns;    
    
	UINT32	dPTL_MAIT_SA;
	t_PTL_MAI	dPTL_MAI;
	
	// VTS info
	UINT32	dVTSM_VOBS_SA;//VTSM VOB Set start address
	UINT32	dVTSTT_VOBS_SA;//VTS VOB Set start address
	UINT32  dVTS_PTT_SRPT_SA;
	UINT32	dVTS_TMAPT_SA,d_PGCN_TM_SA;
	UINT8	TMU;
	UINT16	MAP_EN_Ns;
	UINT32	dVTS_PGCIT_SA;//VTS PGCI table start address
	UINT32	dVTSM_PGCI_UT_SA;//VTSM PGCI language unit table
	UINT32	dVTSM_TTN;//TTN of first VTSM 
	
	
    //VTS A/V/S Info   	
   	UINT8	dSPST_id;
   	
#ifdef DVD_AUDIO	   	
   UINT8  dAST_ATRT[dAST_ATRT_MAX];		// 8ch - 16byte, AU7-3
   UINT8  dVTS_MU_AST_ATRT[dVTS_MU_AST_ATRT_MAX];// 16dm - 18byte ,AU7-13
#else
   UINT8  dAST_ATRT[dAST_ATRT_MAX];		// 8ch - 8byte
   UINT8  dVTS_MU_AST_ATRT[dVTS_MU_AST_ATRT_MAX];// 8ch - 24byte ,VI4-54
#endif   	
   	UINT8	dSPST_ATRT[192];	// 32ch - 6byte   	
   	UINT8 	dPGC_AST_CTLT[16];	  // 8ch - 2 byte ,VI4-87  
   	UINT8 	dPGC_SPST_CTLT[128];	// 32ch - 4byte ,VI4-89        		  		
	
	// TT info
	t_AV_SRP_PB dTT_SRP[dTT_SRP_Ns_MAX];//use 1-99
	
	union 
	{
	       UINT8 dTT_PB_TY;//it must access real time,so mark
		   UINT8 dATT_CAT;
	}tt_info;
	
	UINT8 dVTSN;
	UINT32 dVTS_SA;	
	
	// PGC
	UINT8	dPGC_PG_Ns, dPGC_C_Ns;
	//PlayBack_Time	PGC_PB_TM;
	UINT32	dPGC_UOP_CTL;
	UINT16	dPrevPGC, dNextPGC, dGoUpPGC;
	UINT8	dPGC_PB_MODE, dPGC_STILL;
	UINT8	dPRE_CMD_Ns, dPOST_CMD_Ns, dC_CMD_Ns;
	t_NCMD	dPGC_CMD[129]; // use 1-128
	UINT8	dEN_CN[100]; // use 1-99


	union 
	{
		DSV_Cell	DSVC[256]; // use 1-255
#ifdef DVD_AUDIO	   				
		ATS_PG_CELL ats;
#endif		
	}pc_info;
	DSV_Palette	DSVPLT[16]; // use 0-15
	
	// Navigation Command Process
	//t_NCMD CurrNCMD_Code;
	UINT8 CurrNCMD_PC;		// Program Counter
	
	// PGC Playback
	UINT8 CurrPGN;
	UINT8 CurrCell;
	UINT8 CurrLoopCount;
	UINT8 PGPlayed[13];		// for shuffle mode
	UINT8 DirectPlay;			// = 1, no precommand
	UINT32 ReadRLBN;		// relative LB number for read
	PlayBack_Time Current_Cell_TM;	
	
    #ifdef DVD_PRESTOP_SEPARATE_MENU_RESUME_INFO //chenzhao 2006-9-13 11:21 .
	t_RSM_INFO rsm_info[DVD_PRESTOP_RSM_ITEM+1];
    #else
	t_RSM_INFO rsm_info[BOOK_MAX_ITEM+1];
    #endif
	
	// PE info
	UINT8 new_cell;
	
	// Pointer for current PCI and HLI	
	PlayBack_Time C_ELTM;	
	
	// for PE interface
	UINT16 dV_ATR;
	UINT16 dV_ATR_Menu;
	UINT8 dAST_Ns;
	UINT8 dSPST_Ns;    
    UINT8 dAu_stream_id;
	
	// for VOBU interface
	//PlayBack_Time
	UINT8 dAGL_Ns;
	UINT8 ChkVideo;
	UINT8 dDisc_flag;		
	//for DVD_RTN_MENU_RESUME
#ifdef DVD_RTN_MENU_RESUME
	UINT8 dMenuPgc_flag;        //a flag: 1:execute CALL SS and play a MENU PGC; 0: not, heqiang, 2004-3-5 22:36
#endif
#ifdef NEW_SEL_SUBTITLE_WAY		
	UINT8 user_selected;
	UINT32 dVTSM_VOBS_SA_old;
//	UINT16 record_subp_ttn;
#endif	

	UINT8   Old_CN;//terry,2004/2/11 12:06PM

#ifdef DVD_AUDIO	   				
	UINT32  dASVS_SA;
	UINT16  HGR_INF;	// Hidden Group Information
	
	UINT16  dATS_ASV_PBIT_SA;
	//UINT32  dASVOBS_SA;
	
	UINT8   dASVUN;
	UINT32  dASVU_SA;	
	UINT32  dASVU_LEN;
	
    UINT32 asv_loaded_len;
    UINT8  disp_timing_md; //terry,2004/2/21 06:39PM
	
	UINT8   dASVN;
	UINT16  dASV_SA;	
	UINT32  dASV_LEN;	
	
	UINT8   dASV_Ns;
	UINT16  dABS_ASVN;
	
	UINT8   CurrDLIST;
	UINT32  Disp_Timing;
	UINT32  att_tm;
	UINT8   old_gpn;
	UINT8   old_trkn;	
	UINT16  get_next_asv_tm;
	INT16   asv_buf_offset;//terry,2004/2/27 04:40PM
	UINT8	hid_gp_chk_pwd;//nono 2004-3-2 20:14

	UINT16 asv_loaded_addr;//terry,2004/2/19 03:30PM
	UINT16  asv_file_sa_addr;//terry,2004/3/18 07:00PM
	UINT8   old_asvn;
#endif
#ifdef PLUS_VR_AUTH_PLAYBACK
	UINT8 pCHPI;
	UINT8 pCHPI_BASE;		//CHPI Index for this title.
	UINT8 pVRPL;
	UINT8 bRECI_Entry;
	UINT8 bVRPL_Ns;
	UINT8 bHidden;
	UINT8 bPlayFullTitle;
	UINT32 PlusVRFullCurrentSA,PlusVRFullNextSA;
	UINT32 PlusVRNextChapterSA,/*PlusVRPreviousChapterSA,*/PlusVRCurrentChapterSA;
#endif
#ifdef MINUS_VR_AUTH_PLAYBACK

	//Start Addresses Added By Gary 92.01.26
	UINT32 M_AVFIT_SA;
	UINT32 S_AVFIT_SA;
	UINT32 ORG_PGCI_SA;
	UINT32 UD_PGCI_SA;
	
//	UINT32 TXTDT_MG_SA;		//We Currently Don't Use These Tables
//	UINT32 MNFIT_SA;			//We Currently Don't Use These Tables
	//End of Start Addresses
	//TIME_ENTRY TM_ENT[MAX_TM_ENT];
	//VOBU_ENTRY VOBU_ENT[MAX_VOBU_ENT];

	UINT8 PGFirstCell,CellsInCurrPG;
	UINT32 Cell_Elapse_Time[99];
	UINT32 Cell_Start_Time[99];
	UINT32 ADR_OFS;
	UINT16 TM_OFS;
	UINT16 TM_ENT_N,VOBU_ENT_N;

	UINT32 VOB_V_S_PTM,VOB_V_E_PTM;
	UINT32 C_V_S_PTM,C_V_E_PTM;

	UINT16 Title_C_EPI;	//Chapter Stuff...
	UINT32 Prev_Chapter_PTM,Next_Chapter_PTM,Current_Chapter_PTM;
	UINT8	Prev_Chapter_CN,Next_Chapter_CN,Current_Chapter_CN;
	UINT8   PL_Ns,ORI_PG_Ns;
	BYTE    ORI_PG_Names[99][10];	//Menu Stuff
	BYTE    PL_Names[99][10];	//Menu Stuff
#endif//#ifdef MINUS_VR_AUTH_PLAYBACK

} DataSaved;
//====================================================================================  TOC
#define TRACK_INFO_MAX      (0x66)
typedef struct
{
    UINT32  track_info[TRACK_INFO_MAX+1];
    UINT32  oko_trk_end[TRACK_INFO_MAX];
#ifdef CDDA_DEEMPHASIS
    UINT8   pre_emphasis[TRACK_INFO_MAX+1];  //axel 2005/10/20 for pre-emphasis disc
#endif
}tCDROM;

//====================================================================================  CDG
#define gf_gen 67                //define generating poly of Galois field
				 //primitive poly is a must
				 //polynomial coef. set bitwise
#define gf_order 64              //number of element in Galois field
				 //equals to 2^(highest order of
				 //generating poly)
#define gen_power 6              //highes order of generating poly


typedef unsigned char gf2m_format;         //gf2m_format as the storage format for
				 //field elements. one may redefine it to
				 //other type for enlarging the range for
				 //presentaion of field elements.

typedef struct
{
	gf2m_format exp2vec[gf_order];   //table to covert field element of
				        //exponential form to vector form
	gf2m_format vec2exp[gf_order];   //table to convet field element of
	                   	        //vector form to exponential form
	gf2m_format generator2420[24];   //declare memory for generator poly
	gf2m_format encodedseq2420[24];  //declare memory to store encoded
				        //codeword
	gf2m_format decodedseq2420[20];  //declare memory to store decoded
				        //sequece
	gf2m_format generator42[4];       
	gf2m_format encodedseq42[4];
	gf2m_format decodedseq42[2];
	gf2m_format rootbasis2420[5];
}tCDG;

//===============================================================================  FS & JPEG
#ifndef NEW_JPEG
#include "jpeglib.h"
#endif

typedef struct
{
	tCDG    cdg;	
#ifdef SUPPORT_MULTI_PARTITION      //wanghaoying 2004-8-9 17:28
    BYTE    count_part;             //number of multi-partition in the storage (esp. HDD)
    BYTE    part_current;
    BYTE    part_will;
#ifdef FAT_FILE_MODE
    UINT16  hdd_dir_current;
    UINT16  card_dir_current;
#endif
#endif

#ifdef FILE_MODE_WRITE
    BYTE    count_media;             //number of existing media
    BYTE    media_current;
    BYTE    media_will;
    UINT16  srce_dir_current;
    UINT16  dest_dir_current;    
#endif

	// File Structure part
	UINT16	count_dir[5];
	UINT16	first_dir[5];
	UINT16	count_file[5];
	UINT16	Dir_entry[ISO_DIR_MAX];		// map to real track number
	UINT16	file_specify_in_dir;		// number of specify style file in current directory
// 2006-03-16, mimitsai add
#if 1//def DIR_SCROLL_BAR//zhongshan open it.20060414
	UINT16  dir_count_in_specity_Category;
#endif
	BYTE	gifsFuncBtn;				// indicate which button that we choose(FS_FUNC_MP3, FS_FUNC_JPEG, FS_FUNC_GAME)
	BYTE	gifsState;

	UINT16	gifsMP3Count;				// # of MP3 files in current disc
	UINT16	gifsJPEGCount;				// .jpg

#ifdef SUPPORT_NESGAME
	UINT16	gifsGAMECount;				// .nes
#endif
    
#ifdef SUPPORT_FILE_SYSTEM_MODE
	UINT16	gifsOtherCount;
#endif
    
#ifdef SUPPORT_MIDI
    UINT16  gifsMidiCount;              //.mid
#endif

#ifdef SUPPORT_PLAYLIST
    UINT16  gifsPlayListCount;
#endif

	UINT32	gifsMSFDVDRom;				//system upgrade image
	UINT32	gifsDVDRomSize;				//system-image file size

    UINT32	gbfsPictureCD;              //is Picture CD or not

    #if defined(MP4_DISC_DIRECT_PLAY) || defined(CDROM_MOVIE_DIRECT_PLAY)			//Maoyong 2004.05.12, for disc only has MP4 or/MP4+MPG files
	BYTE    gbfsSpecialMovieCD;
	#endif

/* nes driver is put into ROM, Robert 03/04/29
	UINT32	gifsMSFNESDrv;				//NES driver image
	UINT32	gifsNESDrvSize;				//NES-driver-image file size
	BYTE	bNesDrvError;
*/

	BYTE	gbfsSlide;
	BYTE	gifsbPreview;
	BYTE	gifsbZoomOK;
	BYTE	gfsnot2NormalSpeed;
	BYTE	iGraphMode;					//0:small graph, 1:NTSC graph
    BYTE    gbInJpeg;

    #ifndef JPG_OLD_PARSER_FLOW
    BYTE    gbfsJpgWillDecode;
    BYTE    gbfsJpgBreak;
    BYTE    gbfsJpgChangeNavMode;       //change between preview&fullscreen&thumbnail
    #endif

	UINT16	iso9660_dir_cnt;
	UINT16	iso9660_file_cnt;
	UINT16	fsnav_dir_cnt;

	UINT16	first_mp3_entry;
	UINT16  last_mp3_entry;
	UINT16	first_mp3_seq;				// sequece of first file in gifsFuncBtn group

	UINT16	file_array[PER_PAGE];		//store file index of iso9660_file[index], PER_PAGE defined in fsGUIx.h
	UINT16	dir_array[PER_PAGE];		//store file index of iso9660_dir[index]

	// fs GUI part
	UINT16  ControlArea;
	UINT16	scroll_len;
	UINT16	scroll_step;
	// 2006-03-16, mimitsai add
#ifdef DIR_SCROLL_BAR	
	UINT16	dir1_scroll_len;
	UINT16	dir1_scroll_step;
	//UINT16  Dir_Page_Count;			// number of file page
#endif	

	UINT16  Dir_Page_Count;			// zhongshan move here number of file page

	UINT16  File_Page_Count;			// number of file page in current directory
	UINT16  Dir_Count;
	UINT16  File_Count;					// number of file in current page
	UINT16  file_page_now;				// index of current page
	UINT16  file_page_will;				// index of file page will be, panxing,2002-4-12
	UINT16	dir_page_now;
	UINT16	dir_current;
	UINT16	file_current;				// index of current file in current page
	UINT16	file_will;					// index of file will in current page,panxing,2002-4-13

	UINT16	fsnav_trk_now;
	UINT16	fsnav_dir_now;
	UINT16	fsnav_trk_will;
	UINT16	fsnav_dir_will;
#if defined(FAT_FILE_MODE)||defined(FILE_MODE_WRITE)//liweihua 2004-11-2//zhaoyanhua add 2004-4-9 9:34//lijd2005-1-8 13:04
    UINT16  file_index_in_dir;           //index of all files and subdirs in a dir
    UINT16  file_count_in_dir;           //number of all files and subdirs in a dir
    UINT16  file_current_in_page;        //file offset in current page
    UINT16  file_page_index;
#endif
	// JPEG thumbnail slide show
	UINT16	g_nJpegMode;
	UINT16	g_nPageCount;				// the page amount
	UINT16	g_nPageIndex; 
	UINT16	g_nThumbnailIndex;
	UINT16	g_nAmountInPage;

    #ifdef SUPPORT_FILE_CHAPTER
    UINT8   g_uiFileChangeChapter; // 1:Next, 2: Prev, F: Error
    UINT8   g_uiCurChapter;
    #endif

#ifndef NEW_JPEG
	

	// JPEG part
	int     DCHuffmanTable_cw[2][16];   //DC Huffman Code Word
	int     DCHuffmanTable_cl[2][16];   //DC Huffman Code Length
	int     DCHuffmanTable_rv[2][16];   //DC Huffman Value
	int     ACHuffmanTable_cw[2][176];  //AC Huffman Code Word
	int     ACHuffmanTable_cl[2][176];  //AC Huffman Code Length
	int     ACHuffmanTable_rv[2][176];  //AC Huffman Value        
	int     QTable[2][64];  //Quantization Table
	BYTE	bufJPEG[1024];  //Temp buffer for read from origional data
	INT16	gVID;
	BYTE	bJpgBreak;
	BYTE	bJpgVFDPause; //Jeff 20020523
	BYTE	jpg_Qdl_once;
	int     gQT[2][64];
	MYJPEG	jpg;
	T_DHT	dht;
	T_SOS	sos;
	T_ECS	ecs;
	T_SOF0	sof0;
	UINT16	jpg_framesize;        
	
	//int	LastDC[3];      //for DPCM, we store previous DC values, [0]:Y  [1]:Cb  [2]:Cr
	int     LastDC[64];
	int     gbDCT[64];
	int     gbIDCT[64];
	
	JPGTEMP	p;
#endif

	UINT8 g_cgms; // get CGMS of File Entry(VTS_01_0.VOB), added by robert.chang
	
	tCDROM  cdrom;		
	union
    {
            t_selection_list      s;
            t_play_list           p;
            t_end_list        e;
    }List;
}FSJPEGDATA;


typedef union
{	
	FSJPEGDATA	JPEG;
	DataSaved	DSV;
} share;

// for sim only
//extern UINT8 is_pe_show;
//extern UINT8 is_pg_print;
//extern UINT8 is_bsread_print;
//extern UINT8 dKEY_Ns, CurrKEY;
//extern int dKEYS[256];

extern share *pshare;
extern DataSaved *pDSV;
extern share share_data;
extern FSJPEGDATA *pFsJpeg;
//extern tVCD *pFsJpeg.cdg;
#ifdef MINUS_VR_AUTH_PLAYBACK
extern TIME_ENTRY *TM_ENT;
extern VOBU_ENTRY *VOBU_ENT;
#endif

// param, prefix NP_ (nav param)
#define NP_GPRM(i)		(pDSV->GPRM[(i)])
#define NP_GPRM_mode		(pDSV->GPRM_mode)

#define NP_SPRM(i)		(pDSV->SPRM[(i)])

//video player
#define NP_M_LCD					(pDSV->SPRM[0])
#define NP_ASTN						(pDSV->SPRM[1])
#define NP_SPSTN					(pDSV->SPRM[2])
#define NP_AGLN						(pDSV->SPRM[3])
#define NP_TTN						(pDSV->SPRM[4])
#define NP_VTS_TTN					(pDSV->SPRM[5])
#define NP_TT_PGCN					(pDSV->SPRM[6])
#define NP_PTTN						(pDSV->SPRM[7])
#define NP_HL_BTNN					(pDSV->SPRM[8])
#define NP_NV_TMR					(pDSV->SPRM[9])
#define NP_TT_PGCN_for_NV_TMR		(pDSV->SPRM[10])
#define NP_P_AMXMD					(pDSV->SPRM[11])
#define NP_CTY_CD					(pDSV->SPRM[12])
#define NP_PTL_LVL					(pDSV->SPRM[13])
#define NP_P_CFG_for_Video			(pDSV->SPRM[14])
#define NP_P_CFG_for_Audio			(pDSV->SPRM[15])
#define NP_INI_LCD_for_AST			(pDSV->SPRM[16])
#define NP_INI_LCD_EXT_for_AST		(pDSV->SPRM[17])
#define NP_INI_LCD_for_SPST			(pDSV->SPRM[18])
#define NP_INI_LCD_EXT_for_SPST		(pDSV->SPRM[19])
#define NP_P_RCD					(pDSV->SPRM[20])

#ifdef DVD_AUDIO	
//audio player ,AU9-4
#define NP_AMGM_LCD           (pDSV->SPRM[0]) //AMGM Language code
#define NP_ASLN               (pDSV->SPRM[1]) // audio selection number
//#define NP_AMGM_LCD           (pDSV->SPRM[2])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[3])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[4])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[5])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[6])//reserved
#define NP_PGN                (pDSV->SPRM[7]) //PG number for TT_GP_DOM
#define NP_HL_BTNN            (pDSV->SPRM[8]) //Highlighted Button number for Selection state
//#define NP_AMGM_LCD           (pDSV->SPRM[9])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[10])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[11])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[12])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[13])//reserved
#define NP_VCAP_CFG_Video     (pDSV->SPRM[14])  //Video Capable audio player configuration for video
#define NP_VCAP_CFG_Audio     (pDSV->SPRM[15])  //Video Capable audio player configuration for audio
//#define NP_AMGM_LCD           (pDSV->SPRM[16])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[17])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[18])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[19])//reserved
//#define NP_AMGM_LCD           (pDSV->SPRM[20])//reserved
#define NP_ATT_GRN            (pDSV->SPRM[21]) //ATT Group number
#define NP_ATTN               (pDSV->SPRM[22]) //ATT number for TT_GP_DOM
#define NP_TKN                (pDSV->SPRM[23]) //Track number for TT_GP_DOM
#define NP_ASVN               (pDSV->SPRM[24]) //ASV number
//#define NP_AMGM_LCD           (pDSV->SPRM[25])//reserved

//share varible between audio and video
//#define dTS_Ns          dVTS_Ns
#define dAMGM_VOBS_SA   dVMGM_VOBS_SA
#define dATT_SRPT_SA    dTT_SRPT_SA
#endif


#define FP_DOM				(0)
#define VMGM_DOM			(1)
#define VTSM_DOM			(2)
#define VMGM_DOM_PGCN		(3)
#define TT_DOM				(4)
#define STOP_STATE			(5)

#define TITLE_MENU			(2)
#define ROOT_MENU			(3)
#define SUB_PICTURE_MENU	(4)
#define AUDIO_MENU			(5)
#define ANGLE_MENU			(6)
#define PTT_MENU			(7)

// list of all navigator states
enum {	
	NAV_INIT=0,
	NAV_STOP=1,
	NAV_NEW_PGC,
	NAV_PGC_PLAY,
	NAV_PG_PLAY,
	NAV_CELL_PLAY,
	NAV_PE_PROC,
	NAV_CELL_POST,
	NAV_IDLE,
	NAV_PGC_POST,
	NAV_POWER,
	
#ifdef MINUS_VR_AUTH_PLAYBACK
	NAV_C_EPI_PLAY,
	NAV_VR_GOTO,
#endif
	
	NAV_PREVIEW//terry,2004/2/7 07:18PM
#ifdef PLUS_VR_AUTH_PLAYBACK
	,NAV_PLUSVR_CHPI_PLAY
#endif

};

//======================================================================

#define SYS_PARAM	0x01
#define GEN_PARAM	0x02

//======================================================================

#define set_search_video() pDSV->ChkVideo|=0x01
#define clr_search_video() pDSV->ChkVideo&=(~0x01)
#define is_search_video() (pDSV->ChkVideo&0x01)
#define set_menu_exist_hl() pDSV->ChkVideo|=0x02
#define clr_menu_exist_hl() pDSV->ChkVideo&=(~0x02)
#define is_menu_exist_hl() (pDSV->ChkVideo&0x02)

#define get_cgms()    (pFsJpeg->g_cgms)

#if (REGION_NUM == 0) //axel for setting default region number 2005/5/11 
#error  "illeagal region setting."
#endif

#ifdef PLUS_VR_AUTH_PLAYBACK
#define VRMI_SA 		(SDRAM_BASE_UNCACHED+10305*1024)	//32K
#define VRMI_SZ		(32*1024)

#endif
UINT8 RSM_CurrLoopCount; //axel for loop counter resume NF002 tt34 2006/4/4
#endif /*__NAVDATA_H*/


