/*
* share memory
*/
EXTERN  UINT8 pwb[WB_SIZE];
EXTERN  UINT8 nav_data_err;
/*
*  S/VCD global Var.
*/
EXTERN BYTE     psd_state;
EXTERN_MEM      t_psd_state psd_st;
EXTERN UINT8    oko_menu_id;
EXTERN UINT8    oko_menu_base;
EXTERN BYTE     v11_trk_now;
EXTERN BYTE     bPbcOff;
EXTERN BYTE     SessionNs;
EXTERN UINT16   SegLen;
/*
*  cdrom
*/
EXTERN UINT16   file_in_dir;
EXTERN BYTE     Mp3ReadFinish;
EXTERN int      file_played_count;

/*
*  DVD Video
*/ 
#ifdef DVD_SEQ_PLAY
EXTERN  BYTE   dvd_menu_play;//terry,2002/5/2 04:02PM,new dvd play mode
#endif
EXTERN BYTE     HL_exist; 
EXTERN UINT8    Vobu_still;  
EXTERN UINT8    chg_angle;
EXTERN UINT8    seamless_angle;
EXTERN UINT8    seamless_play;
EXTERN UINT32   force_act_tm;
EXTERN int      dvd_timer;
EXTERN int      hl_timer;
EXTERN int      still_timer;
EXTERN UINT32   play_abs_addr;
EXTERN UINT32   play_abs_end_addr;
EXTERN UINT8    bNop;
EXTERN UINT8    dvd_error;
EXTERN UINT8    bTurnOffParentalLVL;
EXTERN UINT32   dVMG_LSN;
#ifndef DVDRELEASE
EXTERN UINT8    disable_uop;
#endif
EXTERN UINT8 vobu_idx;//terry,2004/1/13 07:14PM

EXTERN UINT8 dvd_karaoke_mode;
EXTERN UINT8 min_astn_id;



/*
*  DVD-Audio
*/
EXTERN UINT8 AOB;
EXTERN UINT32 dVts_iso9600_addr;//terry,2003/8/6 04:00PM
#ifdef DVD_AUDIO
EXTERN UINT32 dAMG_LSN;
EXTERN UINT16 ASV_SPTR;//terry,2004/2/11 04:43PM
EXTERN UINT16 ASV_EPTR;
//EXTERN UINT32   ASV_BASE;
EXTERN UINT8    get_next_ASV;
EXTERN UINT8    srv_ASV;
//EXTERN UINT8    old_asvn;  //terry,2004/2/21 06:40PM
EXTERN UINT16   lba_per_sec;
EXTERN UINT32 ff_start_lba;
#endif/*DVD_AUDIO*/

//DVD-VR
#ifdef MINUS_VR_AUTH_PLAYBACK
EXTERN UINT32 dVR_MOVIE_LSN;
#endif

#ifdef PLUS_VR_AUTH_PLAYBACK
EXTERN UINT32 dVRMI_LSN;
EXTERN UINT8 PlusVRChapterChange;
EXTERN BYTE DiscIsEmptyDisc;//charles add for test
EXTERN BYTE DiscIsIncomplete ;	//For +R Unfinished Disc
EXTERN BYTE SessionIsEmpty;
EXTERN BYTE SessionIsIncomplete;
EXTERN BYTE SessionIsComplete;
EXTERN BYTE DiscIsSunplusDisc;
EXTERN BYTE DiscIsRecordable;
EXTERN BYTE FileSystemIsUDF;//charles
EXTERN BYTE FileSystemIsNotISO;
EXTERN BYTE DiscIsSunplusMP4Disc;    // AVI_TMP_ADD
#endif

#ifdef RESUME_CHECK_DSI_ERROR //chenzhao 2006-6-7 13:26 .mantis ID 5172
EXTERN BYTE b_DSI_error ;
#endif

