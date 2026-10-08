/*
 *  libzvbi - VBI decoding library
 *
 *  Copyright (C) 2000, 2001, 2002 Michael H. Schimek
 *  Copyright (C) 2000, 2001 Iñaki García Etxebarria
 *
 *  Based on AleVT 1.5.1
 *  Copyright (C) 1998, 1999 Edgar Toernig <froese@gmx.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Generated file, do not edit! */

#ifndef __LIBZVBI_H__
#define __LIBZVBI_H__

#define VBI_VERSION_MAJOR 0
#define VBI_VERSION_MINOR 2
#define VBI_VERSION_MICRO 13

typedef struct vbi_decoder vbi_decoder;

/* misc.h */

#if 0

#ifndef DOXYGEN_SHOULD_SKIP_THIS
 
#if __GNUC__ >= 2
   /* Inline this function at -O2 and higher. */
#  define vbi_inline static __inline__
#else
#  define vbi_inline static
#endif

#if __GNUC__ >= 3
   /* Function has no side effects and return value depends
      only on parameters and non-volatile globals or
      memory pointed to by parameters. */
#  define vbi_pure __attribute__ ((pure))
   /* Function has no side effects and return value depends
      only on parameters. */
#  define vbi_const __attribute__ ((const))
   /* Function returns pointer which does not alias anything. */
#  define vbi_alloc __attribute__ ((malloc))
#else
#  define vbi_pure
#  define vbi_const
#  define vbi_alloc
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif

#undef TRUE
#undef FALSE
#define TRUE 1
#define FALSE 0

typedef int vbi_bool;


/* bcd.h */

/* XXX unsigned? */
typedef int vbi_pgno;

typedef int vbi_subno;

#define VBI_ANY_SUBNO 0x3F7F
#define VBI_NO_SUBNO 0x3F7F

/*
vbi_inline unsigned int
vbi_dec2bcd(unsigned int dec)
{
	return (dec % 10) + ((dec / 10) % 10) * 16 + ((dec / 100) % 10) * 256;
}

vbi_inline unsigned int
vbi_bcd2dec(unsigned int bcd)
{
	return (bcd & 15) + ((bcd >> 4) & 15) * 10 + ((bcd >> 8) & 15) * 100;
}

vbi_inline unsigned int
vbi_add_bcd(unsigned int a, unsigned int b)
{
	unsigned int t;

	a += 0x06666666;
	t  = a + b;
	b ^= a ^ t;
	b  = (~b & 0x11111110) >> 3;
	b |= b * 2;

	return t - b;
}

vbi_inline vbi_bool
vbi_is_bcd(unsigned int bcd)
{
	static const unsigned int x = 0x06666666;

	return (((bcd + x) ^ (bcd ^ x)) & 0x11111110) == 0;
}
*/

/* event.h */

typedef unsigned int vbi_nuid;

typedef struct {
	vbi_nuid		nuid;

	signed char		name[64];		/* descriptive name */
	signed char		call[40];		/* network call letters (XDS) */

	int			tape_delay;		/* tape delay, minutes (XDS) */

	/* Private */

	int			cni_vps;
	int			cni_8301;
	int			cni_8302;
	int			cni_x26;

	int			cycle;
} vbi_network;

/*
 *  Link
 */

typedef enum {
	VBI_LINK_NONE = 0,
	VBI_LINK_MESSAGE,
	VBI_LINK_PAGE,
	VBI_LINK_SUBPAGE,
	VBI_LINK_HTTP,
	VBI_LINK_FTP,
	VBI_LINK_EMAIL,
	
	VBI_LINK_LID,
	
	VBI_LINK_TELEWEB
} vbi_link_type;

typedef enum {
	VBI_WEBLINK_UNKNOWN = 0,
	VBI_WEBLINK_PROGRAM_RELATED,
	VBI_WEBLINK_NETWORK_RELATED,
	VBI_WEBLINK_STATION_RELATED,
	VBI_WEBLINK_SPONSOR_MESSAGE,
	VBI_WEBLINK_OPERATOR
} vbi_itv_type;

typedef struct vbi_link {
	vbi_link_type			type;
	vbi_bool			eacem;
	signed char 			name[80];
	signed char			url[256];
	signed char			script[256];
	vbi_nuid			nuid;
	vbi_pgno			pgno;
	vbi_subno			subno;
	double				expires;
	vbi_itv_type			itv_type;
	int				priority;
	vbi_bool			autoload;
} vbi_link;

/*
 *  Aspect ratio information.
 */

typedef enum {
	VBI_SUBT_NONE,		
	VBI_SUBT_ACTIVE,	
	VBI_SUBT_MATTE,		
	VBI_SUBT_UNKNOWN	
} vbi_subt;

typedef struct {
 	int			first_line;
	int			last_line;
	double			ratio;
 	vbi_bool		film_mode;
	vbi_subt		open_subtitles;
} vbi_aspect_ratio;

/*
 *  Program Info
 *
 *  ATTN this is new stuff and subject to change
 */

typedef enum {
	VBI_RATING_AUTH_NONE = 0,
	VBI_RATING_AUTH_MPAA,
	VBI_RATING_AUTH_TV_US,
	VBI_RATING_AUTH_TV_CA_EN,
	VBI_RATING_AUTH_TV_CA_FR
} vbi_rating_auth;

#define VBI_RATING_D 0x08 
#define VBI_RATING_L 0x04 
#define VBI_RATING_S 0x02 
#define VBI_RATING_V 0x01 


extern const char *	vbi_rating_string(vbi_rating_auth auth, int id);

typedef enum {
	VBI_PROG_CLASSF_NONE = 0,
	VBI_PROG_CLASSF_EIA_608,
	VBI_PROG_CLASSF_ETS_300231
} vbi_prog_classf;

extern const char *	vbi_prog_type_string(vbi_prog_classf classf, int id);


/* code depends on order, don't change */
typedef enum {
	VBI_AUDIO_MODE_NONE = 0,		
	VBI_AUDIO_MODE_MONO,			
	VBI_AUDIO_MODE_STEREO,			
	VBI_AUDIO_MODE_STEREO_SURROUND,		
	VBI_AUDIO_MODE_SIMULATED_STEREO,	
	VBI_AUDIO_MODE_VIDEO_DESCRIPTIONS,
	VBI_AUDIO_MODE_NON_PROGRAM_AUDIO,

	VBI_AUDIO_MODE_SPECIAL_EFFECTS,		
	VBI_AUDIO_MODE_DATA_SERVICE,		
	VBI_AUDIO_MODE_UNKNOWN
} vbi_audio_mode;

typedef struct vbi_program_info {
	/*
	 *  Refers to the current or next program.
	 *  (No [2] to allow clients filtering current data more easily.)
	 */
	unsigned int		future	:1;

	/* 01 Program Identification Number */

	/* If unknown all these fields are -1 */
	signed char		month;		/* 0 ... 11 */
	signed char		day;		/* 0 ... 30 */
	signed char		hour;		/* 0 ... 23 */
	signed char		min;		/* 0 ... 59 */

	/*
	 *  VD: "T indicates if a program is routinely tape delayed for the
	 *  Mountain and Pacific time zones."
	 */
	signed char		tape_delayed;

	/* 02 Program Length */

	/* If unknown all these fields are -1 */
	signed char		length_hour;	/* 0 ... 63 */
	signed char		length_min;	/* 0 ... 59 */

	signed char		elapsed_hour;	/* 0 ... 63 */
	signed char		elapsed_min;	/* 0 ... 59 */
	signed char		elapsed_sec;	/* 0 ... 59 */

	/* 03 Program name */

	/* If unknown title[0] == 0 */
	signed char		title[64];	/* ASCII + '\0' */

	/* 04 Program type */

	/*
	 *  If unknown type_classf == VBI_PROG_CLASSF_NONE.
	 *  VBI_PROG_CLASSF_EIA_608 can have up to 32 tags
	 *  identifying 96 keywords. Their numerical value
	 *  is given here instead of composing a string for
	 *  easier filtering. Use vbi_prog_type_str_by_id to
	 *  get the keywords. A zero marks the end.
	 */
	vbi_prog_classf		type_classf;
	int			type_id[33];

	/* 05 Program rating */

	/*
	 *  For details STFW for "v-chip"
	 *  If unknown rating_auth == VBI_RATING_NONE
	 */
	vbi_rating_auth		rating_auth;
	int			rating_id;

	/* Only valid when auth == VBI_RATING_TV_US */
	int			rating_dlsv;

	/* 06 Program Audio Services */

	/*
	 *  BTSC audio (two independent tracks) is flagged according to XDS,
	 *  Zweiton/NICAM/EIA-J audio is flagged mono/none, stereo/none or
	 *  mono/mono for bilingual transmissions.
	 */
	struct {
		/* If unknown mode == VBI_AUDIO_MODE_UNKNOWN */
		vbi_audio_mode		mode;
		/* If unknown language == NULL */
		unsigned char *		language; /* Latin-1 */
	}			audio[2];	/* primary and secondary */

	/* 07 Program Caption Services */

	/*
	 *  Bits 0...7 corresponding to Caption page 1...8.
	 *  Note for the current program this information is also
	 *  available via vbi_classify_page().
	 *
	 *  If unknown caption_services == -1, _language[] = NULL
	 */
	int			caption_services;
	unsigned char *		caption_language[8]; /* Latin-1 */

	/* 08 Copy Generation Management System */

	/* If unknown cgms_a == -1 */
	int			cgms_a; /* XXX */

	/* 09 Aspect Ratio */

	/*
	 *  Note for the current program this information is also
	 *  available via VBI_EVENT_ASPECT.
	 *
	 *  If unknown first_line == last_line == -1, ratio == 0.0
	 */
	vbi_aspect_ratio	aspect;

	/* 10 - 17 Program Description */

	/*
	 *  8 rows of 0...32 ASCII chars + '\0',
	 *  if unknown description[0...7][0] == 0
	 */
	signed char		description[8][33];
} vbi_program_info;

extern void		vbi_reset_prog_info(vbi_program_info *pi);


/* Future */
typedef struct pfc_block {
	vbi_pgno		pgno;
	int			stream;
	int			application_id;
	int			block_size;
	UINT8			block[2048];
} pfc_block;


#define VBI_EVENT_NONE		0x0000
#define	VBI_EVENT_CLOSE		0x0001
#define	VBI_EVENT_TTX_PAGE	0x0002
#define VBI_EVENT_CAPTION	0x0004
#define	VBI_EVENT_NETWORK	0x0008
#define	VBI_EVENT_TRIGGER	0x0010
#define	VBI_EVENT_ASPECT	0x0040
#define	VBI_EVENT_PROG_INFO	0x0080

/* XXX network, aspect, prog_info: should only notify about
 * changes and provide functions to query current value.
 */
typedef struct vbi_event {
	int			type;
	union {
		struct {
		        int			pgno;
		        int			subno;
			UINT8 *		raw_header;
			int			pn_offset;
			unsigned int		roll_header : 1;
		        unsigned int		header_update : 1;
			unsigned int		clock_update : 1;
	        }			ttx_page;
		struct {
			int			pgno;
		}			caption;
		vbi_network		network;
                vbi_link *		trigger;
                vbi_aspect_ratio	aspect;
		vbi_program_info *	prog_info;
	}			ev;
} vbi_event;

typedef void (* vbi_event_handler)(vbi_event *event, void *user_data);

extern vbi_bool		vbi_event_handler_add(vbi_decoder *vbi, int event_mask,
					      vbi_event_handler handler,
					      void *user_data);
extern void		vbi_event_handler_remove(vbi_decoder *vbi,
						 vbi_event_handler handler);
extern vbi_bool		vbi_event_handler_register(vbi_decoder *vbi, int event_mask,
						   vbi_event_handler handler,
						   void *user_data);
extern void		vbi_event_handler_unregister(vbi_decoder *vbi,
						     vbi_event_handler handler,
						     void *user_data);


/* format.h */
/* Code depends on order, don't change. */
typedef enum {
	VBI_BLACK,
	VBI_RED,
	VBI_GREEN,
	VBI_YELLOW,
	VBI_BLUE,
	VBI_MAGENTA,
	VBI_CYAN,
	VBI_WHITE
} vbi_color;

typedef UINT32 vbi_rgba;


typedef enum {
	VBI_TRANSPARENT_SPACE,
	VBI_TRANSPARENT_FULL,
	VBI_SEMI_TRANSPARENT,
	VBI_OPAQUE
} vbi_opacity;

/* Code depends on order, don't change. */
typedef enum {
	VBI_NORMAL_SIZE, VBI_DOUBLE_WIDTH, VBI_DOUBLE_HEIGHT, VBI_DOUBLE_SIZE,
	VBI_OVER_TOP, VBI_OVER_BOTTOM, VBI_DOUBLE_HEIGHT2, VBI_DOUBLE_SIZE2
} vbi_size;

typedef struct vbi_char {
	unsigned	underline	: 1;	
	unsigned	bold		: 1;	
	unsigned	italic		: 1;	
	unsigned	flash		: 1;
	unsigned	conceal		: 1;
	unsigned	proportional	: 1;
	unsigned	link		: 1;
	unsigned	reserved	: 1;
	unsigned	size		: 8;
	unsigned	opacity		: 8;
	unsigned	foreground	: 8;
	unsigned	background	: 8;
	unsigned	drcs_clut_offs	: 8;
	unsigned	unicode		: 16;
} vbi_char;

struct vbi_font_descr;

typedef struct vbi_page {
	vbi_decoder *		vbi;

        vbi_nuid	       	nuid;
	/* FIXME this shouldn't be int */
 	int			pgno;
	/* FIXME this shouldn't be int */
	int			subno;
	int			rows;
	int			columns;
	vbi_char		text[1056];

	struct {
	     /* int			x0, x1; */
		int			y0, y1;
		int			roll;
	}			dirty;

	vbi_color		screen_color;
	vbi_opacity		screen_opacity;
	vbi_rgba 		color_map[40];

	UINT8 *		drcs_clut;		/* 64 entries */
	UINT8 *		drcs[32];

	struct {
		int			pgno, subno;
	}			nav_link[6];
	char			nav_index[64];

	struct vbi_font_descr *	font[2];
	unsigned int		double_height_lower;	/* legacy */

	vbi_opacity		page_opacity[2];
	vbi_opacity		boxed_opacity[2];
} vbi_page;

/* lang.h */

typedef struct vbi_font_descr vbi_font_descr;

/*
vbi_inline vbi_bool
vbi_is_print(unsigned int unicode)
{
	return unicode < 0xE600;
}

vbi_inline vbi_bool
vbi_is_gfx(unsigned int unicode)
{
	return unicode >= 0xEE00 && unicode <= 0xEFFF;
}

vbi_inline vbi_bool
vbi_is_drcs(unsigned int unicode)
{
	return unicode >= 0xF000;
}
*/
/* export.h */

typedef struct vbi_export vbi_export;

typedef struct vbi_export_info {
	char *			keyword;
	char *			label;
	char *			tooltip;
	char *			mime_type;
	char *			extension;
} vbi_export_info;

typedef enum {
	VBI_OPTION_BOOL = 1,

	VBI_OPTION_INT,

	VBI_OPTION_REAL,

	VBI_OPTION_STRING,

	VBI_OPTION_MENU
} vbi_option_type;

typedef union {
	int			num;
	double			dbl;
	char *			str;
} vbi_option_value;

typedef union {
	int *			num;
	double *		dbl;
	char **			str;
} vbi_option_value_ptr;

typedef struct {
  	vbi_option_type		type;	

	char *			keyword;

	char *			label;

	vbi_option_value	def;	
	vbi_option_value	min;	
	vbi_option_value	max;	
	vbi_option_value	step;	
	vbi_option_value_ptr	menu;	

	char *			tooltip;
} vbi_option_info;

extern vbi_export_info *	vbi_export_info_enum(int index);
extern vbi_export_info *	vbi_export_info_keyword(const char *keyword);
extern vbi_export_info *	vbi_export_info_export(vbi_export *);

extern vbi_export *		vbi_export_new(const char *keyword, char **errstr);
extern void			vbi_export_delete(vbi_export *);

extern vbi_option_info *	vbi_export_option_info_enum(vbi_export *, int index);
extern vbi_option_info *	vbi_export_option_info_keyword(vbi_export *, const char *keyword);

extern vbi_bool			vbi_export_option_set(vbi_export *, const char *keyword, ...);
extern vbi_bool			vbi_export_option_get(vbi_export *, const char *keyword,
						      vbi_option_value *value);
extern vbi_bool			vbi_export_option_menu_set(vbi_export *, const char *keyword, int entry);
extern vbi_bool			vbi_export_option_menu_get(vbi_export *, const char *keyword, int *entry);

//extern vbi_bool			vbi_export_stdio(vbi_export *, FILE *fp, vbi_page *pg);
extern vbi_bool			vbi_export_file(vbi_export *, const char *name, vbi_page *pg);

extern char *			vbi_export_errstr(vbi_export *);


/* cache.h */

extern void		vbi_unref_page(vbi_page *pg);

extern int		vbi_is_cached(vbi_decoder *, int pgno, int subno);
extern int		vbi_cache_hi_subno(vbi_decoder *vbi, int pgno);


/* search.h */

typedef enum {
	VBI_SEARCH_ERROR = -3,
	VBI_SEARCH_CACHE_EMPTY,
	VBI_SEARCH_CANCELED,
	VBI_SEARCH_NOT_FOUND = 0,
	VBI_SEARCH_SUCCESS
} vbi_search_status;

typedef struct vbi_search vbi_search;

extern vbi_search *	vbi_search_new(vbi_decoder *vbi,
				       vbi_pgno pgno, vbi_subno subno,
				       UINT16 *pattern,
				       vbi_bool casefold, vbi_bool regexp,
				       int (* progress)(vbi_page *pg));
extern void		vbi_search_delete(vbi_search *search);
extern vbi_search_status vbi_search_next(vbi_search *search, vbi_page **pg, int dir);


/* sliced.h */

#define VBI_SLICED_NONE			0

#define VBI_SLICED_UNKNOWN              0

#define VBI_SLICED_ANTIOPE              0x00002000
#define VBI_SLICED_TELETEXT_A           0x00002000

#define VBI_SLICED_TELETEXT_B_L10_625	0x00000001
#define VBI_SLICED_TELETEXT_B_L25_625	0x00000002
#define VBI_SLICED_TELETEXT_B		(VBI_SLICED_TELETEXT_B_L10_625 | \
					 VBI_SLICED_TELETEXT_B_L25_625)
#define VBI_SLICED_TELETEXT_B_625	VBI_SLICED_TELETEXT_B

#define VBI_SLICED_TELETEXT_C_625       0x00004000

#define VBI_SLICED_TELETEXT_D_625       0x00008000

#define VBI_SLICED_VPS                  0x00000004

#define VBI_SLICED_VPS_F2               0x00001000

#define VBI_SLICED_CAPTION_625_F1       0x00000008
#define VBI_SLICED_CAPTION_625_F2       0x00000010
#define VBI_SLICED_CAPTION_625		(VBI_SLICED_CAPTION_625_F1 | \
                                         VBI_SLICED_CAPTION_625_F2)

#define VBI_SLICED_WSS_625              0x00000400

#define VBI_SLICED_CAPTION_525_F1	0x00000020
#define VBI_SLICED_CAPTION_525_F2	0x00000040
#define VBI_SLICED_CAPTION_525		(VBI_SLICED_CAPTION_525_F1 | \
					 VBI_SLICED_CAPTION_525_F2)
#define VBI_SLICED_2xCAPTION_525	0x00000080

#define VBI_SLICED_TELETEXT_B_525       0x00010000

#define VBI_SLICED_NABTS                0x00000100

#define VBI_SLICED_TELETEXT_C_525       0x00000100

#define VBI_SLICED_TELETEXT_BD_525	0x00000200

#define VBI_SLICED_TELETEXT_D_525       0x00020000


#define VBI_SLICED_WSS_CPR1204		0x00000800

#define VBI_SLICED_VBI_625		0x20000000

#define VBI_SLICED_VBI_525		0x40000000



typedef unsigned int vbi_service_set;

typedef struct {
	UINT32		id;
	UINT32		line;
	UINT8			data[56];
} vbi_sliced;

extern const char *		vbi_sliced_name(unsigned int service);
#if 0 //yuliang 05/05/02
#define TTX_SDRAM_START SDRAM_BASE + 7*1024*1024
//#define g_sliced ((vbi_sliced *)(TTX_SDRAM_START + (70+4) * 1024))

#define g_vtp (vt_page *)(SDRAM_BASE+(5*1024+500)*1024);
#endif
/* decoder.h */

 

/* Bit slicer */

/* Attn: keep this in sync with rte, don't change order */
typedef enum {
	VBI_PIXFMT_YUV420 = 1,
	VBI_PIXFMT_YUYV,
	VBI_PIXFMT_YVYU,
	VBI_PIXFMT_UYVY,
	VBI_PIXFMT_VYUY,
	VBI_PIXFMT_RGBA32_LE = 32,
	VBI_PIXFMT_RGBA32_BE,
	VBI_PIXFMT_BGRA32_LE,
	VBI_PIXFMT_BGRA32_BE,
	VBI_PIXFMT_ABGR32_BE = 32, /* synonyms */
	VBI_PIXFMT_ABGR32_LE,
	VBI_PIXFMT_ARGB32_BE,
	VBI_PIXFMT_ARGB32_LE,
	VBI_PIXFMT_RGB24,
	VBI_PIXFMT_BGR24,
	VBI_PIXFMT_RGB16_LE,
	VBI_PIXFMT_RGB16_BE,
	VBI_PIXFMT_BGR16_LE,
	VBI_PIXFMT_BGR16_BE,
	VBI_PIXFMT_RGBA15_LE,
	VBI_PIXFMT_RGBA15_BE,
	VBI_PIXFMT_BGRA15_LE,
	VBI_PIXFMT_BGRA15_BE,
	VBI_PIXFMT_ARGB15_LE,
	VBI_PIXFMT_ARGB15_BE,
	VBI_PIXFMT_ABGR15_LE,
	VBI_PIXFMT_ABGR15_BE
} vbi_pixfmt;


typedef enum {
	VBI_MODULATION_NRZ_LSB,
	VBI_MODULATION_NRZ_MSB,
	VBI_MODULATION_BIPHASE_LSB,
	VBI_MODULATION_BIPHASE_MSB
} vbi_modulation;

typedef struct vbi_bit_slicer {
	vbi_bool	(* func)(struct vbi_bit_slicer *slicer,
				 UINT8 *raw, UINT8 *buf);
	unsigned int	cri;
	unsigned int	cri_mask;
	int		thresh;
	int		cri_bytes;
	int		cri_rate;
	int		oversampling_rate;
	int		phase_shift;
	int		step;
	unsigned int	frc;
	int		frc_bits;
	int		payload;
	int		endian;
	int		skip;
} vbi_bit_slicer;

extern void		vbi_bit_slicer_init(vbi_bit_slicer *slicer,
					    int raw_samples, int sampling_rate,
					    int cri_rate, int bit_rate,
					    unsigned int cri_frc, unsigned int cri_mask,
					    int cri_bits, int frc_bits, int payload,
					    vbi_modulation modulation, vbi_pixfmt fmt);
/*vbi_inline vbi_bool
vbi_bit_slice(vbi_bit_slicer *slicer, UINT8 *raw, UINT8 *buf)
{
	return slicer->func(slicer, raw, buf);
}
*/

typedef struct vbi_raw_decoder {
	/* Sampling parameters */

	int			scanning;
	vbi_pixfmt		sampling_format;
	int			sampling_rate;		/* Hz */
	int			bytes_per_line;
	int			offset;			/* 0H, samples */
	int			start[2];		/* ITU-R numbering */
	int			count[2];		/* field lines */
	vbi_bool		interlaced;
	vbi_bool		synchronous;

	/*< private >*/
	unsigned int		services;
	int			num_jobs;

	INT8 *		pattern;
	struct _vbi_raw_decoder_job {
		unsigned int		id;
		int			offset;
		vbi_bit_slicer		slicer;
	}			jobs[8];
} vbi_raw_decoder;

extern void		vbi_raw_decoder_init(vbi_raw_decoder *rd);
extern void		vbi_raw_decoder_reset(vbi_raw_decoder *rd);
extern void		vbi_raw_decoder_destroy(vbi_raw_decoder *rd);
extern unsigned int	vbi_raw_decoder_add_services(vbi_raw_decoder *rd,
						     unsigned int services,
						     int strict);
extern unsigned int     vbi_raw_decoder_check_services(vbi_raw_decoder *rd,
						     unsigned int services, int strict);
extern unsigned int	vbi_raw_decoder_remove_services(vbi_raw_decoder *rd,
							unsigned int services);
extern void             vbi_raw_decoder_resize( vbi_raw_decoder *rd,
						int * start, unsigned int * count );
extern unsigned int	vbi_raw_decoder_parameters(vbi_raw_decoder *rd, unsigned int services,
						   int scanning, int *max_rate);
extern int		vbi_raw_decode(vbi_raw_decoder *rd, UINT8 *raw, vbi_sliced *out);


/* dvb_demux.h */
typedef struct _vbi_dvb_demux vbi_dvb_demux;
typedef vbi_bool
vbi_dvb_demux_cb		(/*vbi_dvb_demux *	dx,*/
				 void *			user_data,
				 const vbi_sliced *	sliced,
				 unsigned int		sliced_lines,
				 INT64		pts);

extern void
vbi_dvb_demux_reset		(vbi_dvb_demux *	dx);

#if 1//tcf mask 2005-10-26 14:02
//extern unsigned int
unsigned int
vbi_dvb_demux_cor		(vbi_dvb_demux *	dx,
				 vbi_sliced *		sliced,
				 unsigned int 		sliced_lines,
				 INT64 *		pts,
				 const UINT8 **	buffer,
				 unsigned int *		buffer_left);
#endif				 
				  				 
extern vbi_bool
vbi_dvb_demux_feed		(vbi_dvb_demux *	dx,
				 const UINT8 *	buffer,
				 unsigned int		buffer_size);

//void init_gfx(void);  //tcf 2005-10-26 14:31
/*
extern void
vbi_dvb_demux_delete		(vbi_dvb_demux *	dx);

extern vbi_dvb_demux *
vbi_dvb_pes_demux_new		(vbi_dvb_demux_cb *	callback,
				 void *			user_data);
*/
extern void  vbi_dvb_pes_demux_new(vbi_dvb_demux *dx); 


/* io.h */

#include <sys/time.h> /* struct timeval */

typedef struct vbi_capture_buffer {
	void *			data;
	int			size;
	double			timestamp;
} vbi_capture_buffer;

typedef struct vbi_capture vbi_capture;

typedef enum {
        VBI_FD_HAS_SELECT  = 1<<0,
        VBI_FD_HAS_MMAP    = 1<<1,
        VBI_FD_IS_DEVICE   = 1<<2,
} VBI_CAPTURE_FD_FLAGS;

extern vbi_capture *	vbi_capture_v4l2_new(const char *dev_name, int buffers,
					     unsigned int *services, int strict,
					     char **errorstr, vbi_bool trace);
extern vbi_capture *	vbi_capture_v4l2k_new(const char *	dev_name,
					      int		fd,
					      int		buffers,
					      unsigned int *	services,
					      int		strict,
					      char **		errorstr,
					      vbi_bool		trace);
extern vbi_capture *	vbi_capture_v4l_new(const char *dev_name, int scanning,
					    unsigned int *services, int strict,
					    char **errorstr, vbi_bool trace);
extern vbi_capture *	vbi_capture_v4l_sidecar_new(const char *dev_name, int given_fd,
						    unsigned int *services,
						    int strict, char **errorstr, 
						    vbi_bool trace);
extern vbi_capture *	vbi_capture_bktr_new (const char *	dev_name,
					      int		scanning,
					      unsigned int *	services,
					      int		strict,
					      char **		errstr,
					      vbi_bool		trace);
extern int		vbi_capture_dvb_filter(vbi_capture *cap, int pid);
extern vbi_capture*	vbi_capture_dvb_new(char *dev, int scanning,
				        unsigned int *services, int strict,
				        char **errstr, vbi_bool trace);
extern INT64
vbi_capture_dvb_last_pts	(const vbi_capture *	cap);
extern vbi_capture *
vbi_capture_dvb_new2		(const char *		device_name,
				 unsigned int		pid,
				 char **		errstr,
				 vbi_bool		trace);

struct vbi_proxy_client;
 
extern vbi_capture *
vbi_capture_proxy_new( struct vbi_proxy_client * vpc,
                        int buffers, int scanning,
                        unsigned int *p_services, int strict,
                        char **pp_errorstr );

extern int		vbi_capture_read_raw(vbi_capture *capture, void *data,
					     double *timestamp, struct timeval *timeout);
extern int		vbi_capture_read_sliced(vbi_capture *capture, vbi_sliced *data, int *lines,
						double *timestamp, struct timeval *timeout);
extern int		vbi_capture_read(vbi_capture *capture, void *raw_data,
					 vbi_sliced *sliced_data, int *lines,
					 double *timestamp, struct timeval *timeout);
extern int		vbi_capture_pull_raw(vbi_capture *capture, vbi_capture_buffer **buffer,
					     struct timeval *timeout);
extern int		vbi_capture_pull_sliced(vbi_capture *capture, vbi_capture_buffer **buffer,
						struct timeval *timeout);
extern int		vbi_capture_pull(vbi_capture *capture, vbi_capture_buffer **raw_buffer,
					 vbi_capture_buffer **sliced_buffer, struct timeval *timeout);
extern vbi_raw_decoder *vbi_capture_parameters(vbi_capture *capture);
extern int		vbi_capture_fd(vbi_capture *capture);
extern unsigned int     vbi_capture_update_services(vbi_capture *capture,
                                                    vbi_bool reset, vbi_bool commit,
                                                    unsigned int services, int strict,
                                                    char ** errorstr);
extern int              vbi_capture_get_scanning(vbi_capture *capture);
extern void             vbi_capture_flush(vbi_capture *capture);
extern void		vbi_capture_delete(vbi_capture *capture);

extern vbi_bool         vbi_capture_set_video_path(vbi_capture *capture, const char * p_dev_video);
extern VBI_CAPTURE_FD_FLAGS vbi_capture_get_fd_flags(vbi_capture *capture);


/* proxy-msg.h */

typedef enum
{
	VBI_CHN_PRIO_BACKGROUND  = 1,
	VBI_CHN_PRIO_INTERACTIVE = 2,
	VBI_CHN_PRIO_DEFAULT     = VBI_CHN_PRIO_INTERACTIVE,
	VBI_CHN_PRIO_RECORD      = 3

} VBI_CHN_PRIO;

typedef enum
{
	VBI_CHN_SUBPRIO_MINIMAL  = 0x00,
	VBI_CHN_SUBPRIO_CHECK    = 0x10,
	VBI_CHN_SUBPRIO_UPDATE   = 0x20,
	VBI_CHN_SUBPRIO_INITIAL  = 0x30,
	VBI_CHN_SUBPRIO_VPS_PDC  = 0x40

} VBI_CHN_SUBPRIO;

typedef struct
{
	UINT8			is_valid;
	UINT8			sub_prio;
	UINT8			allow_suspend;

	UINT8			reserved0;
	time_t			min_duration;
	time_t			exp_duration;

	UINT8			reserved1[16];
} vbi_channel_profile;

typedef enum
{
        VBI_PROXY_DAEMON_NO_TIMEOUTS   = 1<<0

} VBI_PROXY_DAEMON_FLAGS;

typedef enum
{
        VBI_PROXY_CLIENT_NO_TIMEOUTS   = 1<<0,
        VBI_PROXY_CLIENT_NO_STATUS_IND = 1<<1

} VBI_PROXY_CLIENT_FLAGS;

typedef enum
{
        VBI_PROXY_CHN_RELEASE = 1<<0,
        VBI_PROXY_CHN_TOKEN   = 1<<1,
        VBI_PROXY_CHN_FLUSH   = 1<<2,
        VBI_PROXY_CHN_NORM    = 1<<3,
        VBI_PROXY_CHN_FAIL    = 1<<4,

        VBI_PROXY_CHN_NONE    = 0

} VBI_PROXY_CHN_FLAGS;

typedef enum
{
        VBI_API_UNKNOWN,
        VBI_API_V4L1,
        VBI_API_V4L2,
        VBI_API_BKTR
} VBI_DRIVER_API_REV;

#define VBIPROXY_VERSION                   0x00000100
#define VBIPROXY_COMPAT_VERSION            0x00000100

/* proxy-client.h */

#include <sys/time.h> /* struct timeval */

typedef struct vbi_proxy_client vbi_proxy_client;

typedef enum
{
   VBI_PROXY_EV_CHN_GRANTED   = 1<<0,
   VBI_PROXY_EV_CHN_CHANGED   = 1<<1,
   VBI_PROXY_EV_NORM_CHANGED  = 1<<2,
   VBI_PROXY_EV_CHN_RECLAIMED = 1<<3,
   VBI_PROXY_EV_NONE          = 0
} VBI_PROXY_EV_TYPE;

typedef void VBI_PROXY_CLIENT_CALLBACK ( void * p_client_data,
                                         VBI_PROXY_EV_TYPE ev_mask );

/* forward declaration from io.h */
struct vbi_capture_buffer;

extern vbi_proxy_client *
vbi_proxy_client_create( const char *dev_name,
                         const char *p_client_name,
                         VBI_PROXY_CLIENT_FLAGS client_flags,
                         char **pp_errorstr,
                         int trace_level );

extern void
vbi_proxy_client_destroy( vbi_proxy_client * vpc );

extern vbi_capture *
vbi_proxy_client_get_capture_if( vbi_proxy_client * vpc );

extern VBI_PROXY_CLIENT_CALLBACK *
vbi_proxy_client_set_callback( vbi_proxy_client * vpc,
                               VBI_PROXY_CLIENT_CALLBACK * p_callback,
                               void * p_data );

extern VBI_DRIVER_API_REV
vbi_proxy_client_get_driver_api( vbi_proxy_client * vpc );

extern int
vbi_proxy_client_channel_request( vbi_proxy_client * vpc,
                                  VBI_CHN_PRIO chn_prio,
                                  vbi_channel_profile * chn_profile );

extern int
vbi_proxy_client_channel_notify( vbi_proxy_client * vpc,
                                 VBI_PROXY_CHN_FLAGS notify_flags,
                                 unsigned int scanning );

typedef enum
{
   VBI_PROXY_SUSPEND_START,
   VBI_PROXY_SUSPEND_STOP
} VBI_PROXY_SUSPEND;

extern int
vbi_proxy_client_channel_suspend( vbi_proxy_client * vpc,
                                  VBI_PROXY_SUSPEND cmd );

int
vbi_proxy_client_device_ioctl( vbi_proxy_client * vpc,
                               int request,
                               void * p_arg );

extern int
vbi_proxy_client_get_channel_desc( vbi_proxy_client * vpc,
                                   unsigned int * p_scanning,
                                   vbi_bool * p_granted );

extern vbi_bool
vbi_proxy_client_has_channel_control( vbi_proxy_client * vpc );



/* exp-gfx.h */
/*
extern void		vbi_draw_vt_page_region(vbi_page *pg, vbi_pixfmt fmt,
						void *canvas, int rowstride,
						int column, int row,
						int width, int height,
						int reveal, int flash_on);
*/
extern void vbi_draw_vt_page_region(vbi_page *pg, int rowstride,		
			int column, int row, int width, int height,
			int reveal, int flash_on, int xStart, int yStart);

/*
vbi_inline void
vbi_draw_vt_page(vbi_page *pg, vbi_pixfmt fmt, void *canvas,
		 int reveal, int flash_on)
{
	vbi_draw_vt_page_region(pg, fmt, canvas, -1, 0, 0,
				pg->columns, pg->rows, reveal, flash_on);
}

extern void		vbi_draw_cc_page_region(vbi_page *pg, vbi_pixfmt fmt,
						void *canvas, int rowstride,
						int column, int row,
						int width, int height);

vbi_inline void
vbi_draw_cc_page(vbi_page *pg, vbi_pixfmt fmt, void *canvas)
{
	vbi_draw_cc_page_region(pg, fmt, canvas, -1, 0, 0, pg->columns, pg->rows);
}

extern void vbi_get_max_rendered_size(int *w, int *h);
extern void vbi_get_vt_cell_size(int *w, int *h);
*/

/* exp-txt.h */

extern int		vbi_print_page_region(vbi_page *pg, char *buf, int size,
					      const char *format, vbi_bool table, vbi_bool ltr,
					      int column, int row, int width, int height);
/*
vbi_inline int
vbi_print_page(vbi_page *pg, char *buf, int size,
	       const char *format, vbi_bool table, vbi_bool ltr)
{
	return vbi_print_page_region(pg, buf, size,
				     format, table, ltr,
				     0, 0, pg->columns, pg->rows);
}
*/

/* hamm.h */
/*
extern const UINT8		_vbi_bit_reverse [256];
extern const UINT8		_vbi_hamm8_fwd [16];
extern const INT8		_vbi_hamm8_inv [256];
extern const INT8		_vbi_hamm24_inv_par [3][256];


vbi_inline unsigned int
vbi_rev8			(unsigned int		c)
{
	return _vbi_bit_reverse[(UINT8) c];
}

vbi_inline unsigned int
vbi_rev16			(unsigned int		c)
{
	return _vbi_bit_reverse[(UINT8) c] * 256
		+ _vbi_bit_reverse[(UINT8)(c >> 8)];
}

vbi_inline unsigned int
vbi_rev16p			(const UINT8 *	p)
{
	return _vbi_bit_reverse[p[0]] * 256
		+ _vbi_bit_reverse[p[1]];
}

vbi_inline unsigned int
vbi_par8			(unsigned int		c)
{
	c &= 255;

	// if 0 == (inv_par[] & 32) change bit 7 of c.  
	c ^= 128 & ~(_vbi_hamm24_inv_par[0][c] << 2);

	return c;
}

vbi_inline int
vbi_unpar8			(unsigned int		c)
{
#ifdef __GNUC__
#if #cpu (i686)
	int r = c & 127;

	// This saves cache flushes and an explicit branch. /
	__asm__ (" testb	%1,%1\n"
		 " cmovp	%2,%0\n"
		 : "+&a" (r) : "c" (c), "rm" (-1));
	return r;
#endif
#endif
	if (_vbi_hamm24_inv_par[0][(UINT8) c] & 32) {
		return c & 127;
	} else {
		// The idea is to OR results together to find a parity
		//   error in a sequence, rather than a test and branch on
		//   each byte. /
		return -1;
	}
}
 

extern void
vbi_par				(UINT8 *		p,
				 unsigned int		n);
extern int
vbi_unpar			(UINT8 *		p,
				 unsigned int		n);

vbi_inline unsigned int
vbi_ham8			(unsigned int		c)
{
	return _vbi_hamm8_fwd[c & 15];
}

vbi_inline int
vbi_unham8			(unsigned int		c)
{
	return _vbi_hamm8_inv[(UINT8) c];
}

vbi_inline int
vbi_unham16p			(const UINT8 *	p)
{
	return ((int) _vbi_hamm8_inv[p[0]])
	  | (((int) _vbi_hamm8_inv[p[1]]) << 4);
}

extern int
vbi_unham24p			(const UINT8 *	p) vbi_pure;
*/


/* cc.h */

extern vbi_bool		vbi_fetch_cc_page(vbi_decoder *vbi, vbi_page *pg,
					  vbi_pgno pgno, vbi_bool reset);


/* vt.h */

typedef enum {
	VBI_WST_LEVEL_1,   
	VBI_WST_LEVEL_1p5, 
	VBI_WST_LEVEL_2p5,
	VBI_WST_LEVEL_3p5  
} vbi_wst_level;


extern void		vbi_teletext_set_default_region(vbi_decoder *vbi, int default_region);
extern void		vbi_teletext_set_level(vbi_decoder *vbi, int level);

extern vbi_bool		vbi_fetch_vt_page(vbi_decoder *vbi, vbi_page *pg,
					  vbi_pgno pgno, vbi_subno subno,
					  vbi_wst_level max_level, int display_rows,
					  vbi_bool navigation);
extern int		vbi_page_title(vbi_decoder *vbi, int pgno, int subno, char *buf);

extern void		vbi_resolve_link(vbi_page *pg, int column, int row,
					 vbi_link *ld);
extern void		vbi_resolve_home(vbi_page *pg, vbi_link *ld);


/* tables.h */

extern const char *	vbi_rating_string(vbi_rating_auth auth, int id);
extern const char *	vbi_prog_type_string(vbi_prog_classf classf, int id);


/* vbi.h */

typedef enum {
	VBI_NO_PAGE = 0x00,
	VBI_NORMAL_PAGE = 0x01,
	VBI_SUBTITLE_PAGE = 0x70,
	VBI_SUBTITLE_INDEX = 0x78,
	VBI_NONSTD_SUBPAGES = 0x79,
	VBI_PROGR_WARNING = 0x7A,
	VBI_CURRENT_PROGR = 0x7C,
	VBI_NOW_AND_NEXT = 0x7D,
	VBI_PROGR_INDEX = 0x7F,
	VBI_PROGR_SCHEDULE = 0x81,
	VBI_UNKNOWN_PAGE = 0xFF,
} vbi_page_type;

extern void		vbi_set_brightness(vbi_decoder *vbi, int brightness);
extern void		vbi_set_contrast(vbi_decoder *vbi, int contrast);


extern /*vbi_decoder **/void	vbi_decoder_new(vbi_decoder *vbi);
extern void		vbi_decoder_delete(vbi_decoder *vbi);
extern void		vbi_decode(vbi_decoder *vbi, vbi_sliced *sliced,
				   int lines, UINT64 timestamp);
extern void             vbi_channel_switched(vbi_decoder *vbi, vbi_nuid nuid);
extern vbi_page_type	vbi_classify_page(vbi_decoder *vbi, vbi_pgno pgno,
					  vbi_subno *subno, char **language);

#ifdef __cplusplus
}
#endif

#endif /* __LIBZVBI_H__ */

