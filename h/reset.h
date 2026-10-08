#ifndef __RESET_H
#define	__RESET_H

EXTERN	BYTE	memory_config_saved;
//EXTERN	BYTE	agdc_config;

#include "memcfg.h"

void	reset_system(void);
void	reset_all(void);
void	TestIOP(void);

#endif/*__RESET_H*/
