#ifndef	__HWIF_H
#define __HWIF_H

// 
// system reset
enum {
	HWIF_RESET_NONE,
	HWIF_RESET_GLOBAL,			// hardware reset ALL
	HWIF_RESET_RISC,
	HWIF_RESET_BR,
	HWIF_RESET_FLASHIF,			// Flash/Rom interface
	HWIF_RESET_RI,				// RISC interface
	HWIF_RESET_SDCTRL,			// SDRAM controller /SDRAM arbitrator
	HWIF_RESET_AGDC,
	HWIF_RESET_GRFX,			// Graphics hardware
	HWIF_RESET_PARM,			// Video decoding parameter
	HWIF_RESET_IDCT,
	HWIF_RESET_INVQ,
	HWIF_RESET_VLD,
	HWIF_RESET_MC,
	HWIF_RESET_TRANS,
	HWIF_RESET_MMU,
	HWIF_RESET_BUFCTL,			// Buffer control
	//
	HWIF_RESET_OGT,				// Subpicture / overlay-graphics hardware
	HWIF_RESET_VPP,
	HWIF_RESET_OSD,
	HWIF_RESET_TV,
	HWIF_RESET_IOP,
	HWIF_RESET_DSP,
	HWIF_RESET_STC,
	HWIF_RESET_CD,
	HWIF_RESET_CSS,
	HWIF_RESET_HOST,
	HWIF_RESET_LPT,				// printer port
	HWIF_RESET_UA0,
	HWIF_RESET_UA1,
	HWIF_RESET_TDM,
	HWIF_RESET_BT,				// Bootstrap
	HWIF_RESET_SRV,
};

void	hwif_reset(int sel);
void	hwif_reset_all(void);
void	hwif_reset_sleep(void);

//
// doze: slow down system clock
// 0: 1x
// 1: 1/2x
// 2~15: 1/(2^#)
//
void	hwif_doze(int n);

int     hwif_chipver(void);

#endif/*__HWIF_H*/

