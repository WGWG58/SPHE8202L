#ifndef __NAVIF_H
#define	__NAVIF_H

#include "dvdpe.h"

BYTE Get_BTN_Ns(void);	//linrc 2006-2-28 
void	update_pci_status(t_pci *);
void	update_pci_packet(t_pci *);
void	update_dsi_packet(t_dsi *);

#ifdef SUPPORT_VCR_DVD    /////////yangli
unsigned navif_CopyRightEnable(void);
#endif

#endif/*__NAVIF_H*/

