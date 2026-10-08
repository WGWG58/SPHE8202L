//---------------------------------------------------------------------------
// game16.h
// 
// Purpose: 16-bits Game Library Include file
//
//---------------------------------------------------------------------------

#ifndef GAME16_H

#define GAME16_H

extern void	(*game16_field_start)(int is_top_field);
extern int	(*game16_field_end)();

#ifdef MP_BOARD_256_PIN_NON_SHARE
#define	SPG_GAME_CLK		99  // pin 232
#define	SPG_GAME_LAT		96  // pin 229
#define	SPG_GAME_PAD0		98  // pin 231
#define	SPG_GAME_PAD1		97  // pin 230
#else
#ifdef IC_8202E_216_PIN_NON_SHARE_CD_DVD_MP_BOARD  // chyeh 2005/01/19
#define	SPG_GAME_CLK		11  //pin 59
#define	SPG_GAME_LAT		10  //pin 58
#define	SPG_GAME_PAD0		15  //pin 65
#define	SPG_GAME_PAD1		16  //pin 66
#else
#define	SPG_GAME_CLK		11  //pin 59
#define	SPG_GAME_LAT		12  //pin 61
#define	SPG_GAME_PAD0		13  //pin 62
#define	SPG_GAME_PAD1		14  //pin 63
#endif
#endif
#endif /* GAME16_H */

