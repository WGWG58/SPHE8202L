#ifndef	__DVDPE_H
#define	__DVDPE_H

#include "types.h"
#ifndef	EXTERN
#define	EXTERN	extern
#endif

#include "dvdpe_d.h"
#include "dvdpe_c.h"
#include "endian.h"

int	pe_button_op(int btn_op, int btn_num);
BYTE	*pe_button_cmd(int n);

//
// BUTTON CONTROL
//
#define	BTN_OP_OFF	0	// delete all button (reset)
#define	BTN_OP_SEL	1	// set #btn_num to selected
#define	BTN_OP_ACT	2	// set #btn_num to activated (only 1 can be activated)
#define	BTN_OP_UP	0x10	// 
#define	BTN_OP_DOWN	0x11	// ...
#define	BTN_OP_LEFT	0x12	// ...
#define	BTN_OP_RIGHT	0x13	// ...

#define	PE_BUTTON_OP(OP,N)		pe_button_op(OP,N)
#define	PE_BUTTON_CMD(N)		pe_button_cmd(N)


//
// dvdpe data
//

// PCI
#if defined(YADAI_DVD)||defined(WINGSUM_DVD) //axel for TCL #17 tmp solution 2004/5/14 03:07
											 //wanghaoying for wingsum one dvd test disc
#define	PCI_CNT		5
#else
#define	PCI_CNT		3
#endif
#define PCI_FLG_FAST	(1<<3)
#define PCI_FLG_NEWCELL	(1<<2)
#define PCI_FLG_NEW	(1<<1)
#define PCI_FLG_VALID	(1<<0)
EXTERN	t_pci		PCI_buf[PCI_CNT];
EXTERN  t_pci           *PCI_buf_parsed;
EXTERN	UINT8		PCI_mark[PCI_CNT];
EXTERN	UINT8		PCI_CNT_VAR;    //ycwen 2005/11/16 For flexibility, change "#define PCI_CNT" to a input vaiable "PCI_CNT_VAR".

// DSI
EXTERN	t_dsi		DSI;

// RDI
EXTERN  t_rdi       RDI;            // for MINUS_VR_AUTH_PLAYBACK

// ...
EXTERN	INT8		pci_parse_now;
EXTERN	INT8		pci_use_now;
EXTERN 	BYTE		pci_hl_enable;

#define	PCI_use		(PCI_buf[pci_use_now])
#define	PCI_parse	(PCI_buf[pci_parse_now])
#define	PCI		PCI_use

EXTERN	BYTE		dsi_guide;
EXTERN	BYTE		dsi_no_video;

EXTERN	UINT32		TS_C_ELTM;


EXTERN	BYTE		dsi_state;
#define	DSI_VIDEO_SEARCH	0
#define	DSI_SP_SEARCH   	5
#define	DSI_SP_FOUND       	6
#define	DSI_SP_JUMP		7
#define	DSI_SP_REWIND       	8
#define	DSI_VIDEO_FOUND		1
#define	DSI_VIDEO_NONE		2
#define	DSI_VIDEO_JUMP		3
#define	DSI_VIDEO_REWIND	4
#define	DSI_SP_ABORT       	9
#define DSI_ANGLE_SEARCH        10
#define DSI_ANGLE_ADJUST        11

//
//
//
#define	PE_PCI_LBA			PCI.PCI_GI.NV_PCK_LBN
#define	PE_DSI_LBA			DSI.DSI_GI.NV_PCK_LBN

#define	LBA_NULL			(0xffffffff)

void	pe_init(void);
void	pe_clr_pci(void);
void	pe_clr_dsi(void);
void	pe_clr_nav(void);
void	pe_flush_pci(int until_newcell);

void	set_timesearch_C_ELTM(UINT32);
void	pe_timesearch_clear(void);
#define	pe_timesearch_now()	(TS_C_ELTM)
#define	pe_timesearch_C_ELTM()	(TS_C_ELTM)

#define	PE_ClearPCI()			pe_clr_pci()
#define	PE_ClearDSI()			(PE_DSI_LBA = LBA_NULL)
#define	PE_ClearNav()			pe_clr_nav()

#define	PCI_buf_valid(n)		(((n)>=0) && (PCI_mark[n]&PCI_FLG_VALID))
#define	PE_PCI_valid()			(PCI_buf_valid(pci_use_now))
#define	PE_DSI_valid()			(PE_DSI_LBA!=LBA_NULL)

#define	PE_DSI_novideo()		(dsi_no_video)

#endif/*__DVDPE_H*/
