#ifndef __MPEGSTR_H
#define __MPEGSTR_H

#ifndef	EXTERN
#ifdef	GLOBAL_HERE
#define	EXTERN	
#else
#define	EXTERN	extern
#endif
#endif

EXTERN	const   char    *profile_str[]
#ifdef GLOBAL_HERE
 = {
  "reserved",
  "High",
  "Spatially scalable",
  "SNR scalable",
  "Main",
  "Simple",
  "reserved", "reserved"
}
#endif
;

/*
** see 13818-2 table 8-3: Level identification
*/
EXTERN  const   char    *level_str[]
#ifdef GLOBAL_HERE
 = {
  "reserved", "reserved", "reserved", "reserved",
  "High",
  "reserved",
  "High 1440",
  "reserved",
  "Main",
  "reserved",
  "Low",
  "reserved",
  "reserved", "reserved", "reserved", "reserved"
}
#endif
;

/*
** see 13818-2 table 6-4: frame_rate_value
*/
EXTERN  const   char    *frame_rate_code_str[] 
#ifdef GLOBAL_HERE
= {
  "forbidden",
  "24,000/1001(23.976..)",
  "24",
  "25",
  "30,000/1001(29.97..)",
  "30",
  "50",
  "60",
  "60,000/1001(59.94..)",
  "60",
  "reserved","reserved","reserved","reserved","reserved","reserved"
}
#endif
;

/*
** see 13818-2 table 6-12: picture_coding_type
*/
EXTERN  const   char    *picture_coding_type_str[]
#ifdef GLOBAL_HERE
= {
  "forbidden-pic-code-type",
  "I-pic",
  "P-pic",
  "B-pic",
  "D-pic",
  "reserved",
  "reserved",
  "reserved"
}
#endif
;

/*
** see 13818-2 table 6-14: Meaning of picture_structure
*/
EXTERN  const   char    *picture_structure_str[] 
#ifdef GLOBAL_HERE
= {
  "reserved",
  "top_field",
  "bottom_field",
  "frame_pic",
}
#endif
;

#endif/*__MPEGSTR_H*/
