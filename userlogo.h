#ifndef __USERLOGO_H
#define __USERLOGO_H

//#include "memmap.h"
//#include "memmap0.h"

#include "types.h"


UINT8 Is_Jpg_Logo();
UINT8 Is_User_Mpeg_Logo();
void  Change_User_Logo();
void  Fetch_Jpg_Logo();
void  Save_Mpeg_Logo();
void  ShowJpgTitle();
void  ShowMpegTitle();

#endif//__USERLOGO_H
