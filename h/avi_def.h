#ifndef __AVI_DEF_H
#define __AVI_DEF_H

#ifndef mmioFOURCC
	#define mmioFOURCC( ch0, ch1, ch2, ch3 )				\
			( (UINT32)(BYTE)(ch0) | ( (UINT32)(BYTE)(ch1) << 8 ) |	\
			( (UINT32)(BYTE)(ch2) << 16 ) | ( (UINT32)(BYTE)(ch3) << 24 ) )
#endif

#define	RIFF_AVI		1
#define	RIFF_WAVE		2
#define	RIFF_CDXA		3

#if 0
// file_media_flag
#define AVI_STRM_FLAG_NONE		0
#define AVI_AUDIO				(1<<0)
#define AVI_VIDEO				(1<<1)
#define AVI_SUBPICTURE			(1<<2)
#define AVI_AUDIO_VBR			(1<<4)
#define AVI_AUDIO_UNSUPPORTED	(1<<5)
#define AVI_VIDEO_UNSUPPORTED	(1<<6)
#define AVI_AUDIO_WMA			(1<<7)
#endif	// #if 0

// file_flag
#define AVI_HDRL				(1<<0)
#define AVI_MOVI				(1<<1)
#define AVI_IDX1				(1<<2)
#define AVI_DIVX_DRM			(1<<3)
#define AVI_INDX				(1<<4)
#define AVI_FILE_MAND_MASK		(AVI_HDRL|AVI_MOVI/*|AVI_IDX1*/)

#define	AVI_RETRY_IDX1			(1<<31)				// if this flag is set, try to reparse idx1
#define	IS_AVI_RETRY_IDX1()		(GET_FILE_FLAG()&AVI_RETRY_IDX1)

#define AVI_ERR_CNT_THRESHOLD	20
#define AVI_CHK_SIZE_THRESHOLD	(1024*1024)

// FOURCCs
// form types, list types, and chunk types
#define	FCC_RIFF				mmioFOURCC('R', 'I', 'F', 'F')
#define	FCC_AVI					mmioFOURCC('A', 'V', 'I', ' ')
#define	FCC_WAVE				mmioFOURCC('W', 'A', 'V', 'E')
#define	FCC_CDXA				mmioFOURCC('C', 'D', 'X', 'A')
#define	FCC_AVIX				mmioFOURCC('A', 'V', 'I', 'X')
#define	FCC_LIST				mmioFOURCC('L', 'I', 'S', 'T')
#define	FCC_movi				mmioFOURCC('m', 'o', 'v', 'i')
#define	FCC_rec					mmioFOURCC('r', 'e', 'c', ' ')
#define	FCC_CSET				mmioFOURCC('C', 'S', 'E', 'T')

#define	FCC_hdrl				mmioFOURCC('h', 'd', 'r', 'l')
#define	FCC_avih				mmioFOURCC('a', 'v', 'i', 'h')
#define	FCC_strl				mmioFOURCC('s', 't', 'r', 'l')
#define	FCC_strh				mmioFOURCC('s', 't', 'r', 'h')
#define	FCC_strf				mmioFOURCC('s', 't', 'r', 'f')
#define	FCC_strd				mmioFOURCC('s', 't', 'r', 'd')
#define	FCC_strn				mmioFOURCC('s', 't', 'r', 'n')

#define	FCC_indx				mmioFOURCC('i', 'n', 'd', 'x')
#define	FCC_idx1				mmioFOURCC('i', 'd', 'x', '1')

#define	FCC_fmt 				mmioFOURCC('f', 'm', 't', ' ')

// Stream types for the <fccType> field of the stream header.
#define	FCC_vids				mmioFOURCC('v', 'i', 'd', 's')
#define	FCC_auds				mmioFOURCC('a', 'u', 'd', 's')
#define	FCC_mids				mmioFOURCC('m', 'i', 'd', 's')
#define	FCC_txts				mmioFOURCC('t', 'x', 't', 's')

////////////////////////////////////////////////////////////////////////////////////////////////////
// DivX 6 Menu FOURCCs
#define FCC_DMNU				mmioFOURCC('D', 'M', 'N', 'U')
#define FCC_MRIF				mmioFOURCC('M', 'R', 'I', 'F')

#define FCC_MENU				mmioFOURCC('M', 'E', 'N', 'U')
#define FCC_LGMN				mmioFOURCC('L', 'G', 'M', 'N')
#define FCC_WMEN				mmioFOURCC('W', 'M', 'E', 'N')
#define FCC_BMEN				mmioFOURCC('B', 'M', 'E', 'N')
#define FCC_MREC				mmioFOURCC('M', 'R', 'E', 'C')
#define FCC_PLAY				mmioFOURCC('P', 'L', 'A', 'Y')
#define FCC_PLY0				mmioFOURCC('P', 'L', 'Y', '0')
#define FCC_MNTX				mmioFOURCC('M', 'N', 'T', 'X')
#define FCC_BNTX				mmioFOURCC('B', 'N', 'T', 'X')
#define FCC_MDIA				mmioFOURCC('M', 'D', 'I', 'A')
#define FCC_MEDS				mmioFOURCC('M', 'E', 'D', 'S')
#define FCC_MEDT				mmioFOURCC('M', 'E', 'D', 'T')
#define FCC_ACTN				mmioFOURCC('A', 'C', 'T', 'N')
#define FCC_STAC				mmioFOURCC('S', 'T', 'A', 'C')
#define FCC_ASAC				mmioFOURCC('A', 'S', 'A', 'C')
#define FCC_MNTK				mmioFOURCC('M', 'N', 'T', 'K')
#define FCC_TITL				mmioFOURCC('T', 'I', 'T', 'L')
#define FCC_CHAP				mmioFOURCC('C', 'H', 'A', 'P')
#define FCC_TRTB				mmioFOURCC('T', 'R', 'T', 'B')
#define FCC_TRLK				mmioFOURCC('T', 'R', 'L', 'K')
#define FCC_TRAN				mmioFOURCC('T', 'R', 'A', 'N')



#define	FCC_1idx				mmioFOURCC('1', 'i', 'd', 'x')
////////////////////////////////////////////////////////////////////////////////////////////////////

// codecs
#define	FCC_xxxx				0
#define	FCC_mjpg				mmioFOURCC('m', 'j', 'p', 'g')
#define	FCC_MJPG				mmioFOURCC('M', 'J', 'P', 'G')
#define FCC_MSVC				mmioFOURCC('M', 'S', 'V', 'C')
#define	FCC_divx				mmioFOURCC('d', 'i', 'v', 'x')
#define	FCC_div3				mmioFOURCC('d', 'i', 'v', '3')
#define	FCC_div4				mmioFOURCC('d', 'i', 'v', '4')
#define	FCC_dx50				mmioFOURCC('d', 'x', '5', '0')
#define	FCC_DIVX				mmioFOURCC('D', 'I', 'V', 'X')
#define	FCC_DIV3				mmioFOURCC('D', 'I', 'V', '3')
#define	FCC_DIV4				mmioFOURCC('D', 'I', 'V', '4')
#define	FCC_DX50				mmioFOURCC('D', 'X', '5', '0')	
#define FCC_xvid				mmioFOURCC('x', 'v', 'i', 'd')
#define FCC_XVID				mmioFOURCC('X', 'V', 'I', 'D')
#define	FCC_rmp4				mmioFOURCC('r', 'm', 'p', '4')
#define	FCC_RMP4				mmioFOURCC('R', 'M', 'P', '4')
#define FCC_mp4v				mmioFOURCC('m', 'p', '4', 'v')
#define FCC_MP4V				mmioFOURCC('m', 'p', '4', 'v')
#define FCC_3iv0				mmioFOURCC('3', 'i', 'v', '0')
#define FCC_3iv1				mmioFOURCC('3', 'i', 'v', '1')
#define FCC_3iv2				mmioFOURCC('3', 'i', 'v', '2')
#define FCC_3ivx				mmioFOURCC('3', 'i', 'v', 'x')
#define FCC_MP43				mmioFOURCC('M', 'P', '4', '3')
#define FCC_CRAM				mmioFOURCC('C', 'R', 'A', 'M')
#define	FCC_FVFW				mmioFOURCC('F', 'V', 'F', 'W')
#define	FCC_fvfw				mmioFOURCC('f', 'v', 'f', 'w')
#define FCC_mp4a                mmioFOURCC('m', 'p', '4', 'a')
#define FCC_mp3_new             mmioFOURCC('.', 'm', 'p', '3')
#define FCC_mp3_old             mmioFOURCC(0x6D, 0x73, 0x00, 0x55)
#define FCC_mp4s                mmioFOURCC('m', 'p', '4', 's')
#define FCC_MP4S				mmioFOURCC('M', 'P', '4', 'S')//add by Roger 06-04-14 for support asf video format				
#define FCC_m4s2				mmioFOURCC('m', '4', 's', '2')
#define FCC_M4S2				mmioFOURCC('M', '4', 'S', '2')
#define FCC_MP42				mmioFOURCC('M', 'P', '4', '2')
#define FCC_NULL                mmioFOURCC(' ', ' ', ' ', ' ')

// type of compression
#define	FCC_Comp_divx			mmioFOURCC('d', 'i', 'v', 'x')
#define	FCC_Comp_div3			mmioFOURCC('d', 'i', 'v', '3')
#define	FCC_Comp_div4			mmioFOURCC('d', 'i', 'v', '4')
#define	FCC_Comp_div5			mmioFOURCC('d', 'i', 'v', '5')
#define	FCC_Comp_div6			mmioFOURCC('d', 'i', 'v', '6')
#define	FCC_Comp_dx50			mmioFOURCC('d', 'x', '5', '0')
#define	FCC_Comp_DIVX			mmioFOURCC('D', 'I', 'V', 'X')
#define	FCC_Comp_DIV3			mmioFOURCC('D', 'I', 'V', '3')
#define	FCC_Comp_DIV4			mmioFOURCC('D', 'I', 'V', '4')
#define	FCC_Comp_DIV5			mmioFOURCC('D', 'I', 'V', '5')
#define	FCC_Comp_DIV6			mmioFOURCC('D', 'I', 'V', '6')
#define	FCC_Comp_DX50			mmioFOURCC('D', 'X', '5', '0')
#define	FCC_Comp_xvid			mmioFOURCC('x', 'v', 'i', 'd')
#define	FCC_Comp_XVID			mmioFOURCC('X', 'V', 'I', 'D')
#define	FCC_Comp_rmp4			mmioFOURCC('r', 'm', 'p', '4')
#define	FCC_Comp_RMP4			mmioFOURCC('R', 'M', 'P', '4')
#define	FCC_Comp_3IV0			mmioFOURCC('3', 'I', 'V', '0')
#define	FCC_Comp_3IV1			mmioFOURCC('3', 'I', 'V', '1')
#define	FCC_Comp_3IV2			mmioFOURCC('3', 'I', 'V', '2')
#define	FCC_Comp_3IVX			mmioFOURCC('3', 'I', 'V', 'X')
#define	FCC_Comp_COL1			mmioFOURCC('C', 'O', 'L', '1')

// Basic data subchunk types
#define	FCC_xxdb				mmioFOURCC('0', '0', 'd', 'b')		// DIB bits
#define	FCC_xxdc				mmioFOURCC('0', '0', 'd', 'c')		// DIB compression
#define	FCC_xxdd				mmioFOURCC('0', '0', 'd', 'd')		// DRM key info for the video frame
#define	FCC_xxpc				mmioFOURCC('0', '0', 'p', 'c')		// palette change
#define	FCC_xxwb				mmioFOURCC('0', '0', 'w', 'b')		// waveform chunk
#define	FCC_xxst				mmioFOURCC('0', '0', 's', 't')		// subtitle (text mode)
#define	FCC_xxsb				mmioFOURCC('0', '0', 's', 'b')		// subtitle (bitmap mode)
#define	FCC_xxch				mmioFOURCC('0', '0', 'c', 'h')		// chapter

// Chunk id to use for extra chunks for padding.
#define	FCC_JUNK				mmioFOURCC('J', 'U', 'N', 'K')

// main AVI header list flags
#define	AVIF_HASINDEX			0x00000010
#define	AVIF_MUSTUSEINDEX		0x00000020
#define	AVIF_ISINTERLEAVED		0x00000100
#define	AVIF_TRUSTCKTYPE		0x00000800
#define	AVIF_WASCAPTUREFILE		0x00010000
#define	AVIF_COPYRIGHTED		0x00020000

// AVI stream header flags
#define	AVISF_DISABLED			0x00000001
#define	AVISF_VIDEO_PALCHANGES	0x00010000

// AVI idx1 flags
#define	AVIIF_LIST				0x00000001L
#define	AVIIF_KEYFRAME			0x00000010L
#define	AVIIF_FIRSTPART
#define	AVIIF_LASTPART
#define	AVIIF_NOTIME			0x00000100L
#define	AVIIF_COMPUSE			0x0FFF0000L

// AVI index type
#define	AVI_INDEX_OF_INDEXES		0x00		// when each entry in aIndex array points to an index chunk
#define	AVI_INDEX_OF_CHUNKS			0x01		// when each entry in aIndex array points to a chunk in the file
#define AVI_INDEX_OF_TIMED_CHUNKS	0x02
#define AVI_INDEX_OF_SUB_2FIELD		0x03
#define	AVI_INDEX_IS_DATA			0x80		// when each entry in aIndex is really the data

// AVI index subtype
#define AVI_INDEX_SUB_DEFAULT	0x00
#define	AVI_INDEX_2FIELD		0x01		// when fields within frames are also indexed

// avi_video_type
#define AVI_VIDEO_UNCOMPRESSED	0
#define AVI_VIDEO_MJPEG			1
#define AVI_VIDEO_DIVX			2

#endif	// __AVI_DEF_H
