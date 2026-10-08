#define VFD_DGT0       0  // The following define is depend on PCB layout
#define VFD_DGT1       2  // address 2,3
#define VFD_DGT2       4  // address 4,5
#define VFD_DGT3       6  // address 6,7
#define VFD_DGT4       8  // address 8,9
#define VFD_DGT5       10  // address A,B
#define ADDR_LEN       12
/* define 7-segment position    */
#define DOT_1          3
#define DOT_2          2
#define DOT_3          1
#define DOT_4          0
#define DOT_5          7
#define DOT_6          6
#define DOT_7          5
#define DOT_8          4
#define DOT_9          11
#define DOT_10         10
#define DOT_11         9
#define DOT_12         8
#define DOT_13         15
#define DOT_14         14
#define DOT_15         13
#define DOT_16         12
#define DOT_OVER       22
#define DOT_A          0
#define DOT_B          1
#define DOT_C          2
#define DOT_D          3
#define DOT_E          4
#define DOT_F          5
#define DOT_G          6
#define DOT_H          7
#define DOT_LINE       12
#define DOT_COLON      31
#define DOT_MIN        23
#define DOT_SEC        7
#define DOT_TRACK      23
#define DOT_VCD        13
#define DOT_CDI        1
#define DOT_CDDA       2
#define DOT_NTSC       6
#define DOT_PAL        7
#define DOT_L          20
#define DOT_R          21
#define DOT_STEREO     0
#define DOT_MONO       3
#define DOT_FF         10
#define DOT_FB         12
#define DOT_PLAY       4
#define DOT_PAUSE      3
#define DOT_REPEAT     0
#define DOT_REPA       3
#define DOT_REPARR     3
#define DOT_REPB       4
#define DOT_REP1       1
#define DOT_REPALL     2
#define DOT_PBC        26
#define DOT_PBCOFF     16
#define DOT_INTRO      16
#define DOT_PROG       24
#define DOT_RANDOM     23
#define DOT_RESUME     31
#define DOT_KARA       18    // KARAOKE
#define DOT_KEYU       23    // KARAOKE
#define DOT_KEYR       24    // KARAOKE
#define DOT_KEYD       22    // KARAOKE
#define TRK_MAX        16
#define VFD_FTRK       VFD_DGT0
#define VFD_TRK        VFD_DGT5
#define VFD_MIN        VFD_DGT3
#define VFD_SEC        VFD_DGT2
#define VFD_PAUSE()    VFDmem[2]=(VFDmem[2]&(~(1<<DOT_PLAY)))|(1<<DOT_PAUSE); \
VFD_write(VFD_DGT4)
//mode1      
#define VFD_PLAY()     VFDmem[2]=(VFDmem[2]&(~(1<<DOT_PAUSE)))|(1<<DOT_PLAY); \
VFD_write(VFD_DGT4)
//mode2
#define VFD_MPX(x)     VFDmem[0]&=(~(1<<DOT_R)); \
	VFDmem[0]=(VFDmem[0]&(~(1<<DOT_STEREO)))|(1<<DOT_MONO); \
	VFDmem[0]&=(~(1<<DOT_L)); \
	switch(x) { \
                       case 0xf1 : VFDmem[0]|=(1<<DOT_L); break; \
                       case 0xf2 : VFDmem[0]|=(1<<DOT_R); break; \
                       case 0xf3 : VFDmem[0]&=(~(1<<DOT_MONO)); \
					   VFDmem[0]|=(1<<DOT_STEREO); \
					   break; \
                        } \
VFD_write(VFD_DGT1)
//mode3
#define VFD_KEYS(x)    {}
//mode3
#define VFD_PBC(x)     switch(x) { \
                       case 0x00 : VFDmem[0]&=(~(1<<DOT_PBC)); break; \
                       case 0x01 : VFDmem[0]|=(1<<DOT_PBC); break; \
                        } \
VFD_write(VFD_DGT1)                            
//mode4
#define VFD_FFB(x)  
//mode4
#define VFD_INTRO(x)     switch(x) { \
                       case 0x00 : VFDmem[0]&=(~(1<<DOT_INTRO)); break; \
                       case 0x01 : VFDmem[0]|=(1<<DOT_INTRO); break; \
                        } \
VFD_write(VFD_DGT1)
//mode5
#define VFD_PROG(x)    switch(x) { \
                       case 0x00 : VFDmem[0]&=(~(1<<DOT_PROG)); break; \
                       case 0x01 : VFDmem[0]|=(1<<DOT_PROG); break; \
                        } \
VFD_write(VFD_DGT4)                           
//mode6
#define VFD_NTSC_PAL(x) switch(x) { \
                        case 0x00 : VFDmem[2]=(VFDmem[2]&(~(1<<DOT_NTSC)))|(1<<DOT_PAL); break; \
                        case 0x01 : VFDmem[2]=(VFDmem[2]&(~(1<<DOT_PAL)))|(1<<DOT_NTSC); break; \
                        } \
VFD_write(VFD_DGT4)                         
//mode7
#define VFD_OPEN()     VFDmem[0]=0x0; \
	VFDmem[1]=0x0; \
	VFDmem[2]=0x0; \
	VFDmem[1]=((TEXT_O<<24)|(TEXT_P<<16)|(TEXT_E<<8)|(TEXT_N)); \
	VFD_write(VFD_DGT0);\
	VFD_write(VFD_DGT2);\
VFD_write(VFD_DGT4)
//mode8
#define VFD_READ()     VFDmem[0]=0x0; \
	VFDmem[1]=0x0; \
	VFDmem[2]=0x0; \
	VFDmem[1]=((TEXT_R<<24)|(TEXT_E<<16)|(TEXT_A<<8)|(TEXT_D)); \
	VFD_write(VFD_DGT0);\
	VFD_write(VFD_DGT2);\
VFD_write(VFD_DGT4)
//mode9
#define VFD_STOP()     VFDmem[0]=0x0; \
	VFDmem[1]=0x0; \
	VFDmem[2]=0x0; \
	VFDmem[1]=((TEXT_S<<24)|(TEXT_T<<16)|(TEXT_O<<8)|(TEXT_P)); \
	VFD_write(VFD_DGT0);\
	VFD_write(VFD_DGT2);\
VFD_write(VFD_DGT4)
//mode9
#define VFD_CLOSE()    VFDmem[1]=0x0; \
	VFDmem[2]=0x0; \
	VFDmem[2]=(TEXT_C<<16); \
	VFDmem[1]=((TEXT_L<<24)|(TEXT_O<<16)|(TEXT_S<<8)|(TEXT_E)); \
	VFD_write(VFD_DGT2); \
VFD_write(VFD_DGT4)
//mode10
#define VFD_NODISC()   VFDmem[1]=0x0; \
	VFDmem[2]=0x0; \
	VFDmem[0]=0x0; \
	VFDmem[2]=((TEXT_N<<24)|(TEXT_O<<16)); \
	VFDmem[1]=((TEXT_D<<24)|(TEXT_I<<16)|(TEXT_S<<8)|(TEXT_C)); \
	VFD_write(VFD_DGT0); \
	VFD_write(VFD_DGT2); \
VFD_write(VFD_DGT4)
//mode11
#define VFD_VCD20()      { }    
#define VFD_VCD()      { VFDmem[2]|=(1<<DOT_VCD);VFD_write(VFD_DGT5); }
//mode12
#define VFD_CDDA()      { }

//mode13   
#define VFD_VOCAL(x)  {} 
//  switch(x) { 
//  case 0x00 : VFDmem[2]&=(0xFFFFFFFB); break; 
//  case 0x01 : VFDmem[2]|=(1<<DOT_VOCAL); break; 
//   } 
//    VFD_write(VFD_DGT4)
//mode14
#define VFD_RESUME()   {  }
//mode15
#define VFD_IDLE()     { }                                             
//mode16
#define VFD_REPEAT(x)  switch(x) { \
                    case 0: VFDMEM(2)&=0xFFFFFFE0; \
					break; \
                    case 1: VFDMEM(2)&=0xFFFFFFE0; \
					VFDMEM(2)|=((1<<DOT_REPEAT)|(1<<DOT_REPA)); \
					break; \
                    case 2: VFDMEM(2)&=0xFFFFFFFF; \
					VFDMEM(2)|=((1<<DOT_REPEAT)|(1<<DOT_REPB)); \
					break; \
                    case 3: VFDMEM(2)&=0xFFFFFFE0; \
					VFDMEM(2)|=((1<<DOT_REP1)|(1<<DOT_REPEAT));\
					break; \
                    case 4: VFDMEM(2)&=0xFFFFFFE0; \
					VFDMEM(2)|=((1<<DOT_REPALL)|(1<<DOT_REPEAT));\
					break; \
                    } \
VFD_write(VFD_DGT2)
//mode17
#define SCAN_ZERO       0x0           // PLAY
#define SCAN_PAUSE      0x004           // PLAY
#define SCAN_EJECT      0x010           // EJECT
#define SCAN_PREV       0x110
#define SCAN_NEXT       0x101
#define SCAN_FF         0x210
#define SCAN_FB         0x201
#define SCAN_MPX        0x001
#define SCAN_STOP       0x002
#define SCAN_PLAY       0x003
#define SCAN_RETURN     0x005

#define TEXT_A          0xee
#define TEXT_B          0x3e
#define TEXT_C          0x9c
#define TEXT_D          0x7a
#define TEXT_E          0x9e
#define TEXT_F          0x8e
#define TEXT_H          0x6e
#define TEXT_I          0x60
#define TEXT_L          0x1c
#define TEXT_N          0xec
#define TEXT_N1         0x6d
#define TEXT_O          0xfc
#define TEXT_P          0xce
#define TEXT_R          0x8c
#define TEXT_S          0xb6
#define TEXT_T          0xe1
#define TEXT_U          0x73
#define TEXT_Y          0x76
