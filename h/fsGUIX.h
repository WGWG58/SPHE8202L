#ifndef __FSGUIX_H
#define __FSGUIX_H

void FSGUI_DrawPixel(unsigned x, unsigned y, unsigned luma, unsigned chroma);
void FSGUI_DrawPixel2(unsigned x, unsigned y, unsigned c);

#define FSGUI_ICON_YFLIP     (1<<0)
#define FSGUI_ICON_XFLIP     (1<<1)
#define FSGUI_ICON_MONO      (1<<2)
void FSGUI_DrawIcon(int x, int y, const UINT8 *icon, const UINT8 cluty[], const UINT16 clutc[], UINT32 opt);

#endif/*__FSGUIX_H*/

