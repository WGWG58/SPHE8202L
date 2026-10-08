#ifndef __MEMCFG_H
#define __MEMCFG_H

#define	MEMORY_GRAPH_NTSC       0x00            // 720x480  1 graphics buffer
#define	MEMORY_GRAPH_PAL        0x01            // 720x576  1 graphics buffer
#define	MEMORY_GRAPH_SMALL      0x02            // 352x288  1 graphics buffer

#define	MEMORY_PREVIEW	        0x03            // 720x576  2 decode buffer + 1 preview buffer

#define MEMORY_DVD_NTSC         0x04            // 720x480  3 decode buffers
#define	MEMORY_SVCD_NTSC        0x05            // 480x480  3 decode buffers
#define	MEMORY_CVD_NTSC	        0x06            // 352x480  3 decode buffers
#define	MEMORY_VCD_NTSC	        0x07            // 352x240  3 decode buffers

#define MEMORY_DVD_PAL	        0x08            // 720x576  3 decode buffers
#define	MEMORY_SVCD_PAL	        0x09            // 480x576  3 decode buffers
#define	MEMORY_CVD_PAL	        0x0a            // 352x576  3 decode buffers
#define	MEMORY_VCD_PAL	        0x0b            // 352x288  3 decode buffers

#define MEMORY_DVD_AUDIO        0x0c            // 720*576  1 decode buffer

#define MEMORY_UNKNOWN_NTSC     0x0e            // unknown-mode, have to reset to MEMORY_DVD_NTSC
#define MEMORY_UNKNOWN_PAL      0x0f            // unknown-mode, have to reset to MEMORY_DVD_PAL

#define MEMORY_MIDI             0x10            // 352x288  3 decode buffer

#define MEMORY_DVD_PAL_W352	    0x11            // 352x1168 3 decode buffers
#define MEMORY_DVD_PAL_W480	    0x12            // 480x864  3 decode buffers
#define MEMORY_DVD_PAL_W1024    0x13            // 1024x400 3 decode buffers

#define MEMORY_GRAPH_HD_720P    0x14            // 1280x720   1 graphics buffer
#define MEMORY_GRAPH_HD_1080I   0x15            // 1920x1080  1 graphics buffer

void    config_memory_size(int config, int w, int h, int force);
int 	check_video_size(int width, int height);

#ifdef  MP3_JPEG_COWORK
#define config_memory(_cfg)   config_memory_size(_cfg,0,0,0)
#else
#define config_memory(_cfg)   config_memory_size(_cfg,0,0,1)
#endif

//terry,2004/2/2 04:42PM
#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
//zhaoyanhua add 2003-12-18 10:46
BYTE GetConfigMode(int config);
extern void DrawNewWindow(void);
#endif

#if defined(SPHE8202) || defined(SPHE1000)
#define setvpp_linear_mode_width(v)  (regs0->g23_reserved[0]=(v))
#else
#define setvpp_linear_mode_width(v)  (regs0->dip_param=(v))
#endif

#define REG_OSDYA   regs0->osd_base_addr
#define REG_OSDYA2  regs0->osdya

extern int avd_is_midi(void);

#endif/*__MEMCFG_H*/

