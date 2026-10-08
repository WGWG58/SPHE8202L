#ifndef	__CDFS_H
#define	__CDFS_H

#include "types.h"

typedef	struct {
  BYTE		file_number;
  BYTE		channel_number;
  BYTE		sub_mode;
  BYTE		coding_information;		/* 20		*/
} t_cdxa_subheader;

typedef	struct {
  UINT32	sync_word[3];			/* 1 to 12	*/
  BYTE		mm_bcd;				/* 13		*/
  BYTE		ss_bcd;				/* 14		*/
  BYTE		ff_bcd;				/* 15		*/
  BYTE		mode;				/* 16		*/
  t_cdxa_subheader	subhead0;
  t_cdxa_subheader	subhead1;
} t_cdxa;

typedef	struct {
  BYTE		volume_descriptor_type;		/* 1		*/
  char		standard_id[5];			/* 2 to 6	*/
  BYTE 		version;			/* 7		*/		
  BYTE		unused_0;			/* 8		*/
  char		system_id[32];			/* 9 to 40	*/
  char		volume_id[32];			/* 41 to 72	*/
  BYTE		unused_1[8];			/* 73 to 80	*/
  BYTE		volume_space_size[8];		/* 81 to 88	*/
  BYTE		unused_2[32];			/* 89 to 120	*/
  BYTE		volume_set_size[4];		/* 121 to 124	*/
  BYTE		volume_seq_no[4];		/* 125 to 128	*/
  BYTE		logic_block_size[4];		/* 129 to 132	*/
  BYTE		path_table_size[8];		/* 133 to 140	*/
  UINT32 	path_table_L;			/* 141 to 144	*/
  UINT32 	path_table_L_optional;		/* 145 to 148	*/
  UINT32	path_table_M;			/* 149 to 152	*/
  UINT32	path_table_M_optional;		/* 153 to 156	*/
} t_primary_volume_descriptor;

#endif/*__CDFS_H*/
