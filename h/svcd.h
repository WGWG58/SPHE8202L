#ifndef	__SVCD_H
#define	__SVCD_H

extern void svcd_audio_init();
extern UINT32 udf_find_anchor(void);

/*
** t_sect_info
**
** generic structure of 00:04:00 for vcd/cvd/svcd
*/
typedef	struct 
{
  char		file_id[8];			/* 1 to 8	*/
  UINT16	version;			/* 9 to 10	*/
  char		album_id[16];			/* 11 to 26	*/
  UINT16	album_no;			/* 27 to 28	*/
  UINT16	album_seq;			/* 29 to 30	*/
  BYTE		size_map_vcd[13];		/* 31 to 43	*/
  BYTE		status;				/* 44		*/
  UINT32	psd_size;			/* 45 to 48	*/
  BYTE		first_segment_mm_bcd;		/* 49 		*/
  BYTE		first_segment_ss_bcd;		/* 50 		*/
  BYTE		first_segment_ff_bcd;		/* 51 		*/
  BYTE		psd_offset_multiplier;		/* 52		*/
  UINT16	maximum_list_id;		/* 53 to 54	*/
  UINT16	maximum_segment_id;		/* 55 to 56	*/
  BYTE		segment_play_table[1980];	/* 57 to 2036	*/
  BYTE		status_extension;		/* 2037 (svcd)	*/
  BYTE		disc_type;			/* 2038	(svcd)	*/
  BYTE		reserved[10];			/* 2039 to 2048	*/
} t_sect_info;


#define	VCD_STATUS_USERDATA	0x10
#define	VCD_STATUS_LISTID_2	0x20
#define	VCD_STATUS_TRACK_3	0x40

#define	VCD_SEG_AUDIO_NONE	0x00
#define	VCD_SEG_AUDIO_SINGLE	0x01
#define	VCD_SEG_AUDIO_STEREO	0x02
#define	VCD_SEG_AUDIO_DUAL	0x03

#define	VCD_SEG_VIDEO_NONE		0x00
#define	VCD_SEG_VIDEO_LO_STILL_NTSC	0x01	/* 352x240	*/
#define	VCD_SEG_VIDEO_HI_STILL_NTSC	0x02	/* 704x480	*/
#define	VCD_SEG_VIDEO_LO_MOTION_NTSC	0x03	/* 352x240	*/
#define	VCD_SEG_VIDEO_RESERVED		0x04
#define	VCD_SEG_VIDEO_LO_STILL_PAL	0x05	/* 352x288	*/
#define	VCD_SEG_VIDEO_HI_STILL_PAL	0x06	/* 704x576	*/
#define	VCD_SEG_VIDEO_LO_MOTION_PAL	0x07	/* 352x288	*/

#define	SVCD_SEG_VIDEO_NONE		0x00
#define	SVCD_SEG_VIDEO_LO_STILL_NTSC	0x01	/* 2/3 D1 	*/
#define	SVCD_SEG_VIDEO_HI_STILL_NTSC	0x02	/* D1	 	*/
#define	SVCD_SEG_VIDEO_LO_MOTION_NTSC	0x03
#define	SVCD_SEG_VIDEO_RESERVED		0x04
#define	SVCD_SEG_VIDEO_LO_STILL_PAL	0x05
#define	SVCD_SEG_VIDEO_HI_STILL_PAL	0x06
#define	SVCD_SEG_VIDEO_LO_MOTION_PAL	0x07

#define	SVCD_SEG_AUDIO_EXT


#define	MSF_PVD		0x000210
#define	MSF_INFO	0x000400
#define	MSF_ENTRY	0x000401


#define	SEGMENT_FIRST_FLAG	(1<<5)
#define	IS_SEGMENT_FIRST(s)	((s)&SEGMENT_FIRST_FLAG)
/*
** t_sect_entries
**
** generic structure of 00:04:01 for vcd/cvd/svcd
*/
typedef	struct 
{
  char		file_id[8];
  UINT16	version;
  UINT16	entries_used;
  UINT32	entry[500];
} t_sect_entries;


UINT8	get_segment(int);
UINT32	get_segment_msf(int);
UINT32	get_entry(int);

#endif/*__SVCD_H*/

