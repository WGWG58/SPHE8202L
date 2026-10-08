#ifndef __CDXA_H
#define __CDXA_H

/*
** CD/CDROM/CDROM-XA information
*/

#define CNA_MASK_TYPE           0x0040  //Jeff change from 0x00d0
#define CNA_MASK_COPYABLE       0x0020

#define CNA_AUDIO_2CHANNEL              0x00
#define CNA_AUDIO_2CHANNEL_PREEMP       0x80
#define CNA_AUDIO_4CHANNEL              0x10
#define CNA_AUDIO_4CHANNEL_PREEMP       0x90
#define CNA_DATA                        0x40


#if 0
typedef	struct {
  BYTE	mm;
  BYTE	ss;
  BYTE	ff;
  BYTE	mode;
} t_cdxa_header;

typedef	struct {
  BYTE	fn;
  BYTE	cn;
  BYTE	sm;
  BYTE	ci;
} t_cdxa_subheader;

typedef	struct {
  BYTE			sync[12];
  t_cdxa_header		header;
  t_cdxa_subheader	subheader;
  BYTE			payload[2324];
  UINT32		edc;
} t_cdxa_sector;
#endif

#define	CDXA_SH_FN	0
#define	CDXA_SH_CN	1
#define	CDXA_SH_SM	2
#define	CDXA_SH_CI	3

#define	SUBMODE_EOF	0x80
#define	SUBMODE_RT	0x40
#define	SUBMODE_FORM2	0x20
#define	SUBMODE_TRIG	0x10
#define	SUBMODE_DATA	0x08
#define	SUBMODE_AUDIO	0x04
#define	SUBMODE_VIDEO	0x02
#define	SUBMODE_EOR	0x01

#endif/*__CDXA_H*/

