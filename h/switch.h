#ifndef	__SWITCH_H__
#define	__SWITCH_H__
//--------------------------------
// Video input Format
//--------------------------------
#define    _1080i

#define 	K_nosignal		0x80
#define		K_NTSC			0x85// kevin 0x81
#define		K_PAL			0x84//kevin 0x82
#define 	K_SECAM			0x83	
#define 	K_DVDNTSC		0x86//kevin 0x84
#define 	K_DVDPAL		0x84//kevin 0x85
// SPV311 source port
//--------------------------------
#define 	portA			0x0
#define		portB			0x1
// Output Format
//--------------------------------
//kevin@040804
#define 	DISPVGA			0x6//kevin 0x0
#define 	DISPSVGA		0x5//kevin 0x1
#define		DISPXGA			0x4//kevin 0x2
//#define		DISPWXGA		0x3
#define 	DISPSXGA		0x3//kevin 0x4
//#define 	DISPNWXGA		0x5
#define 	DISP480P		0x2//kevin 0x6
#define 	DISP720P		0x0//kevin 0x7
#define 	DISP576P		0x1//kevin 0x8
#define 	DISP720P50		0x9//Kevin @0x9


#define		BYPASS			0xF0
//SDRAM CLOCK
#define DRAM_100M   1
#define DRAM_110M   2
#define DRAM_120M   3 
#define DRAM_135M   4
#define M16			1
#define M64			2
#define M128		3
#define M256		4
#define M16X2		5
#define M64X2		6
#define M128X2		7
#define  M256X2          8

#define SDRAM_SIZE_311		M16        //kevin change for HDMI
#define DRAM_CLOCK   DRAM_135M
#define sub_311         0x6c
//#ifdef For_TsingHua
#define _0 0x40
#define _1 0x41
#define _2 0x42
#define _3 0x43
#define _4 0x44
#define _5 0x45
#define _6 0x46
#define _7 0x47
#define _8 0x48
#define _9 0x49
#define _a 0x4a
#define _b 0x4b
#define _c 0x4c
#define _d 0x4d
#define _e 0x4e
#define _f 0x4f
#define _g 0x50
#define _h 0x51
#define _i  0x52
#define _j  0x53
#define _k 0x54
#define _l  0x55
#define _m 0x56
#define _n 0x57
#define _o 0x58
#define _p 0x59
#define _r 0x5a
#define _s 0x5b
#define _t 0x5c
#define _u 0x5d
#define _v 0x5e
#define _x 0x5f
#define _z 0x60
#define _A 0x61
#define _B 0x62
#define _C 0x63
#define _D 0x64
#define _E 0x65
#define _F 0x66
#define _G 0x67
#define _H 0x68
#define _I  0x69
#define _J 0x6a
#define _K 0x6b
#define _L 0x6c
#define _M 0x6d
#define _N 0x6e
#define _O 0x6f
#define _P 0x70
#define _R 0x71
#define _S 0x72
#define _T 0x73
#define _U 0x74
#define _V 0x75
#define _W 0x76
#define _X 0x77
#define _Z 0x78
#define _blank 0x79
#define _Nblank 0xf9
#define _solid  0x7a
#define _Nsolid  0xfa
#define _arc_left 0x7b
#define _arc_right 0x7c
#define _sun_left  0x7d
#define _sun_right 0x7e
#define _dot          0x7f
extern unsigned const char  YPbPr_output[];
extern unsigned const char  LutTable[] ;
//#endif
extern const unsigned char SPV301_tab[];
extern const unsigned char SPV311_NTSC_VGA_PLL[] ;
extern const unsigned char SPV311_NTSC_XGA_PLL[];
extern const unsigned char SPV311_NTSC_SVGA_PLL[] ;
extern const unsigned char SPV311_NTSC_480P_PLL[] ;
extern const unsigned char SPV311_NTSC_720P_PLL[];
extern const unsigned char SPV311_NTSC_SXGA_PLL[];

extern const unsigned char SPV311_PAL_VGA_PLL[];
extern const unsigned char SPV311_PAL_SVGA_PLL[];
extern const unsigned char SPV311_PAL_XGA_PLL[];
extern const unsigned char SPV311_PAL_SXGA_PLL[];
extern const unsigned char SPV311_PAL_576P_PLL[] ;
extern const unsigned char SPV311_PAL_720P50_PLL[];

//-------------------------------------------------------
extern const unsigned char NTSC_VGA_OUT[];
extern const unsigned char NTSC_SVGA_OUT[];
extern const unsigned char NTSC_XGA_OUT[];
extern const unsigned char NTSC_SXGA_OUT[];
extern const unsigned char NTSC_480P_OUT[];
extern const unsigned char NTSC_720P_OUT[];
extern const unsigned char PAL_576P_OUT[];
extern const unsigned char PAL_720P50_OUT[];
extern const unsigned char PAL_VGA_OUT[];
extern const unsigned char PAL_SVGA_OUT[];
extern const unsigned char PAL_XGA_OUT[];
extern const unsigned char PAL_SXGA_OUT[];

extern const unsigned char SPV311_NTSC_1080i_PLL[];
extern const unsigned char NTSC_1080i_OUT[];
extern const unsigned char SPV311_PAL_1080i_PLL[];
extern const unsigned char PAL_1080i_OUT[];

extern const unsigned char SPV301_DVD_pal_in[] ;
extern const unsigned char SPV301_DVD_ntsc_in[] ;
extern const unsigned char sca_tab_hermite[] ;
extern const unsigned char sca_tab_bspline[];

#ifdef SCALER_6500      //helm for scaler 050707
extern const unsigned char Video_Input_Tab[14][14];  //helm for scaler table 050707
extern const unsigned char Video_Output_H_Tab[13][12];
extern const unsigned char Video_Output_V_Tab[15][11];
extern const unsigned char Video_Output_Overflow_Tab[14][4];
extern const unsigned char Video_Output_Scale_Tab[8][6];
extern const unsigned char ScalerTBL[256][3];
extern const  unsigned char GAMMA_RGBTBL[256][4];
extern const unsigned char PLL_Tab[8][6];
extern const unsigned  char Video_Output_1080glb_Tab[3][4];
#endif

#endif

