/* alan_0417 */

#include "user_init.h"

#ifdef OSD_FONT_COMPRESS

#include "config.h"
#include "osdfont.inc"
#include "types.h"
#include "func.h"

extern  BYTE decomp_fnTable [];

inline int font_decompress()
{
	return dsp3_decompress(OSDfontbin,decomp_fnTable);	
}
#else
inline int font_decompress()
{
	return 0;	
}
#endif
