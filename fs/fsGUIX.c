//
// FILE
// fsGUIX.c
//

#include "global.h"
#include "func.h"
#include "memmap.h"
#include "graph.h"
#include "framebuf.h"

#include "fsGUIX.h"


//
// PIXEL
//
void
FSGUI_DrawPixel(unsigned x, unsigned y, unsigned __y, unsigned __c)
{
    *Y_XY(x, y) = __y;
    *C_XY(x, y) = __c;
}

/*
void
FSGUI_DrawPixel2(unsigned x, unsigned y, unsigned c)
{
    *Y_XY(x, y) = c>>16;        // bit [23:16]
    *C_XY(x, y) = c;            // bit [15:0]
}
*/ 

//
// ICON
//
void
FSGUI_DrawIcon(int x, int y, const UINT8 *icon, const UINT8 cluty[], const UINT16 clutc[], UINT32 opt)
{
    int w = icon[0];
    int h = icon[1];
    int c = icon[2];
    int t = icon[3];
    int i, j;

    icon+=4;

    for (j=0;j<h;j++) {
        for (i=0;i<w;i++) {
            int cc, xx, yy;
            cc = *icon++;
            if (cc!=t && cc<c) {
                if (opt&FSGUI_ICON_MONO) cc=0;
                xx = x + ((opt&FSGUI_ICON_XFLIP) ? w-1-i: i);
                yy = y + ((opt&FSGUI_ICON_YFLIP) ? h-1-j: j);
                FSGUI_DrawPixel(xx, yy, cluty[cc], clutc[cc]);
            }
        }
    }
}

