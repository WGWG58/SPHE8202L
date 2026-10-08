#ifndef ATOM_PARSER_H
#define ATOM_PARSER_H

// movie atom
int Parse_moov_Atom(void);

// movie header atom
int Parse_mvhd_Atom(void);

// track atom
int Parse_trak_Atom(void);

// track header atom
int Parse_tkhd_Atom(void);

// media atom
int Parse_mdia_Atom(void);

// media header atom
int Parse_mdhd_Atom(void);

// handler reference atom
int Parse_hdlr_Atom(void);

// media information atom
int Parse_minf_Atom(void);

// video media information header atom
int Parse_vmhd_Atom(void);

// sound media information header atom
int Parse_smhd_Atom(void);

int Parse_edts_atom(void);

int Parse_elst_atom(void);

// data information atom
int Parse_dinf_Atom(void);

// data reference atom
int Parse_dref_Atom(void);

// sample table atom
int Parse_stbl_Atom(void);

//#define DEBUG_PARSE_STSD_ATOM_SEARCH_VOL_HEADER
void
Parse_stsd_atom_search_vol_header(void);

// sample description atom
int Parse_stsd_Atom(void);

// time-to-sample atom
int Parse_stts_Atom(void);

// sync sample atom
int Parse_stss_Atom(void);

// sample to chunk atom
int Parse_stsc_Atom(void);

// sample size atom
int Parse_stsz_Atom(void);

// chunk offset atom
int Parse_stco_Atom(void);

// media data atom
int Parse_mdat_Atom(void);

// free atom
int Parse_free_Atom(void);

// user data atom
int Parse_udta_Atom(void);

int Parse_ndrm_Atom(void);

int Parse_chpl_Atom(void);

int Parse_subp_Atom(void);

int Parse_subt_Atom(void);

int Parse_ftyp_atom(void);

#endif




