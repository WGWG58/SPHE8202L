#ifndef __OSDSUP_H
#define __OSDSUP_H

// osd1.c
// 16-color line function
void osd_draw_hline_region(int x1, int x2, int y, unsigned color, int n, int r);
void osd_draw_vline_region(int x, int y1, int y2, unsigned color, int n, int r);
void osd_draw_button_outline(int x1, int y1, int x2, int y2, int bDown, unsigned mask, int r);

#endif

