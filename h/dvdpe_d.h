//
// FILE 
// dvdpe_d.h
//
// DESCRIPTION
// DVD navigation related data structure
//
// *NOTE* all structure in big-endian format
//

#ifndef __DVDPE_D_H
#define	__DVDPE_D_H

//
// PCI 
// {
//   PCI_GI		60  PCI general information
//   NSML_AGLI		36  Angle Information for non-seamless
//   HLI		694 Highlight Information (..)
//   RECI		189 Recording Information (ISRC)
// }
//


// PCI_GI		60
// {
//   NV_PCK_LBN		4   LBN of Naviation pack
//   VOBU_CAT		2   Category of VOBU
//   <reserved>		2
//   VOBU_UOP_CTL	4   User Operation control of VOBU
//   VOBU_S_PTM		4   Start PTM of VOBU
//   VOBU_E_PTM		4   End PTM of VOBU
//   VOBU_SE_E_PTM	4   End PTM of sequence end in VOBU (??)
//   C_ELTM		4   Cell Elasped Time
//   <reserved>		32
// }
typedef	struct	{
  UINT32 	NV_PCK_LBN;             // 4
  UINT16	VOBU_CAT;               // 2
  UINT16	reserved_0[1];          // 2
  UINT32	VOBU_UOP_CTL;           // 4
  UINT32	VOBU_S_PTM;             // 4
  UINT32	VOBU_E_PTM;             // 4
  UINT32 	VOBU_SE_E_PTM;          // 4
  UINT32	C_ELTM;                 // 4
  UINT32	reserved_1[8];          // 32
} t_pci_gi;	// 60


// NSML_AGLI		36
// {
//   NSML_AGL_C_DSTA	36
// }
typedef	struct	{
  UINT32	NSML_AGL_C_DSTA[9];  
} t_nsml_agli;

// BTN_POSI		6
// {
//   POSI		6
// }
typedef	struct 	{
  UINT8		POSI[6];
} t_btn_posi;

// ADJBTN_POSI		4
// {
//   UP			1
//   DOWN		1
//   LEFT		1
//   RIGHT		1
// }
typedef	struct	{
  UINT8		DIR[4];		//up,down,left,right  
} t_ajbtn_posi;


// NAV_CMD
// {
//   CMD		8
// }
typedef	struct	{
  UINT8		CMD[8];
} t_nav_cmd;	// 8


// BTN_COLI
// {
//   SL_COLI		4   color during selected
//   AC_COLI		4   color during action
// }
typedef	struct	{
  UINT32	SL_COLI;
  UINT32	AC_COLI;
} t_btn_coli;

// BTNI			18
// {
//   BTN_POSI		6
//   AJBTN_POSI		4
//   NAV_CMD		8
// }
typedef	struct	{
  t_btn_posi	BTN_POSI	__attribute__((packed));
  t_ajbtn_posi	AJBTN_POSI	__attribute__((packed));
  t_nav_cmd	BTN_CMD		__attribute__((packed)); 
} t_btni;	// 18


// HLI			694
// {
//   HLI_GI		22
//   BTN_COLI		3*8
//   BTNI		36*18
// }
typedef	struct	{
  // hl_gi
  UINT16	HLI_SS		__attribute__((packed));
  UINT32	HLI_S_PTM	__attribute__((packed));
  UINT32	HLI_E_PTM	__attribute__((packed));
  UINT32	BTN_SL_E_PTM	__attribute__((packed));
  UINT16	BTN_MD		__attribute__((packed));
  UINT8		BTM_OFN		__attribute__((packed));
  UINT8		BTN_Ns		__attribute__((packed));
  UINT8		NSL_BTN_Ns	__attribute__((packed));
  UINT8		reserved	__attribute__((packed));
  UINT8		FOSL_BTNN	__attribute__((packed));
  UINT8		FOAC_BTNN	__attribute__((packed));

  t_btn_coli	BTN_COLI[3]	__attribute__((packed));

  t_btni	BTNI[36]	__attribute__((packed));
} t_hli;


typedef	struct	{
  t_pci_gi	PCI_GI; //		__attribute__((packed));	// 60
  t_nsml_agli	NSML_AGLI	__attribute__((packed));	// 36
  t_hli		HLI		__attribute__((packed));
} t_pci_no_reci;

#define	t_pci	t_pci_no_reci


//
// DSI
//

//
// DSI
// {
//   DSI_GI		32
//   SML_PBI		148
//   VOBU_SRI		168
//   SYNCI		144
//   <reserved>	471
// }
//

// DSI_GI		32
// {
//   NV_PCK_SCR		4
//   NV_PCK_LBN		4
//   VOBU_EA		4
//   VOBU_1STREF_EA	4
//   VOBU_2NDREF_EA	4
//   VOBU_3RDREF_EA	4
//   VOBU_VOB_IDN	2
//   <reserved>		1
//   VOBU_C_IDN		1
//   C_ELTM		4
// }
typedef	struct	{
  UINT32	NV_PCK_SCR	;	// 4
  UINT32	NV_PCK_LBN	;	// 4
  UINT32	VOBU_EA		;	// 4
  UINT32	VOBU_1STREF_EA	;	// 4
  UINT32	VOBU_2NDREF_EA	;	// 4
  UINT32	VOBU_3RDREF_EA	;	// 4
  UINT16	VOBU_VOB_IDN	;	// 2
  UINT8		reserved	;	// 1
  UINT8		VOBU_C_IDN	;	// 1
  UINT32	C_ELTM		;	// 4
} t_dsi_gi;			// 32

typedef	struct	{
  UINT32	VOB_A_STP_PTM1;
  UINT32	VOB_A_STP_PTM2;
} t_vob_a_stp_ptm;		// 8

typedef	struct	{
  UINT32	VOB_A_GAP_LEN1;
  UINT32	VOB_A_GAP_LEN2;
} t_vob_a_gap_len;		// 8

#define	VOBU_SML_CAT_PREU	(1<<15)
#define	VOBU_SML_CAT_ILVU	(1<<14)
#define	VOBU_SML_CAT_UnitStart	(1<<13)
#define	VOBU_SML_CAT_UnitEnd	(1<<12)

// SML_PBI		148
// {
//   VOBU_SML_CAT	2
//   ILVU_EA		4
//   NXT_ILVU_SA	4
//   NXT_ILVU_SZ	2
//   VOB_V_S_PTM	4
//   VOB_V_E_PTM	4
//   VOB_A_STP_PTM[8]	64
//   VOB_A_GAP_PTM[8]	64
// }
typedef	struct	{
  UINT16	VOBU_SML_CAT	__attribute__((packed));		// 2
  UINT32	ILVU_EA		__attribute__((packed));		// 4
  UINT32	NXT_ILVU_SA	__attribute__((packed));		// 4
  UINT16	NXT_ILVU_SZ	__attribute__((packed));		// 2
  UINT32	VOB_V_S_PTM	__attribute__((packed));		// 4
  UINT32	VOB_V_E_PTM	__attribute__((packed));		// 4
  t_vob_a_stp_ptm	VOB_A_STP_PTM[8]	__attribute__((packed));	// 64
  t_vob_a_gap_len	VOB_A_GAP_LEN[8]	__attribute__((packed));	// 64
} t_sml_pbi;		// 148


// SML_AGL_CN_DSTA
// {
//   AGL_C
//   AGL_C_ILVU
// }
typedef	struct	{
  UINT32	AGL_C		__attribute__((packed));
  UINT16	AGL_C_ILVU	__attribute__((packed));
} t_sml_agl_cn_dsta;	// 6

// SML_AGLI
// {
//   SML_AGL_CN_DSTA[9]
// }
typedef	struct	{
  t_sml_agl_cn_dsta	SML_AGL_C_DSTA[9] __attribute__((packed));  
} t_sml_agli;		// 54


//
// VOBU_SRI index table
// VI4-145
//
enum	{
	FWDI_VIDEO	= 0,	// 0
	FWDI_240,		// 1
	FWDI_120,		// 2
	FWDI_60,		// 3
	FWDI_20,		// 4
	FWDI_15,		// 5
	FWDI_14,		// 6
	FWDI_13,		// 7
	FWDI_12,		// 8
	FWDI_11,		// 9
	FWDI_10,		// 10
	FWDI_9,			// 11
	FWDI_8,			// 12
	FWDI_7,			// 13
	FWDI_6,			// 14
	FWDI_5,			// 15
	FWDI_4,			// 16
	FWDI_3,			// 17
	FWDI_2,			// 18
	FWDI_1,			// 19
	FWDI_NEXT,		// 20
	BWDI_PREV,		// 21
	BWDI_1,			// 22
	BWDI_2,			// 23
	BWDI_3,			// 24
	BWDI_4,			// 25
	BWDI_5,			// 26
	BWDI_6,			// 27
	BWDI_7,			// 28
	BWDI_8,			// 29
	BWDI_9,			// 30
	BWDI_10,		// 31
	BWDI_11,		// 32
	BWDI_12,		// 33
	BWDI_13,		// 34
	BWDI_14,		// 35
	BWDI_15,		// 36
	BWDI_20,		// 37
	BWDI_60,		// 38
	BWDI_120,		// 39
	BWDI_240,		// 40
	BWDI_VIDEO,		// 41
};


// VOBU_SRI
// {
//   SA[42]		168
// }
typedef	struct
{
  UINT32	SA[42];		// total 42 (*4=168b) search address
} t_vobu_sri;


// SYNCI	144
// {
//   A_SYNCA	16
//   SP_SYNCA	128
// }
typedef	struct	{
  UINT16	A_SYNCA[8];
  UINT32	SP_SYNCA[32];
} t_synci;


// DSI
// {
//   DSI_GI		32
//   SML_PBI		148
//   SML_AGLI		54
//   VOBU_SRI		168
// }
typedef	struct	{
  t_dsi_gi	DSI_GI;						// 32 	(4*8)
  t_sml_pbi	SML_PBI;					// 148	(4*37)
  t_sml_agli	SML_AGLI	__attribute__((packed));	// 54	(4*13.5)
  t_vobu_sri	VOBU_SRI	__attribute__((packed));	// 168	(4*42)
  t_synci	SYNCI		__attribute__((packed));	// 16 + 128
//  UINT16	unused		__attribute__((packed));
} t_dsi;		// 402

typedef struct
{
	UINT16	reserved_0;
	UINT8	VOBU_S_PTM[6];
	UINT8	reserved_1[3];
	UINT8	VOBU_REC_TM[5];
}t_rdi_gi;

typedef struct
{
	UINT8	reserved_0[5];
	UINT8	DCI_CCI_SS;
	UINT8	DCI;
	UINT8	CCI;
}t_dci_cci;

typedef struct
{
	t_rdi_gi 	RDI_GI;
	t_dci_cci	DCI_CCI;
}t_rdi;

#endif/*__DVDPE_D_H*/

