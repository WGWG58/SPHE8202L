// 2005/03/29 yltsneg
// 2005/08/29 yltseng, add two more variables in t_osd_region structure

#ifndef _OSD_DRV_H_
#define _OSD_DRV_H_

#include "types.h"
#include "bufloc.h"

//define pallete format
//#define OSD_PAL_16b
//#define OSD_PAL_32b
#define OSD_PAL_RGB_32b

#ifdef DVDRELEASE
//#define OSD_AUTO_RECOVER
#endif

//use PrintOsdMsg
#define BOARD_UP_LINE    (0x01<<0)
#define BOARD_DOWN_LINE  (0x01<<1)
#define BOARD_LEFT_LINE  (0x01<<2)
#define BOARD_RIGHT_LINE (0x01<<3)
#define BOARD_FULL_LINE  (BOARD_UP_LINE|BOARD_DOWN_LINE|BOARD_LEFT_LINE|BOARD_RIGHT_LINE)
#define BOARD_LR_LINE    (BOARD_LEFT_LINE|BOARD_RIGHT_LINE)
#define BOARD_UD_LINE    (BOARD_UP_LINE|BOARD_DOWN_LINE)

#define OSD_OFF         0
#define OSD_ON          1
#define OSD_TOG         2

#define MAX_MEMORY		4192    //total 4192*32 bytes(131KB)
#define HEADER_SIZE     16  //8
#define MAX_REGION      8   //5
#define MAX_SW_REGION   4
#define MAX_SW_R_LEN    13

#define OSDSTR_ID_TOTL_BIT    9//8//nono 2-7-8 17:44

#define OSD_INTERLACED          0x08
#define OSD_NONINTERLACED       0x00    


#define OSD_FORMAT_MASK         0x07
#define OSD_FORMAT_4COLOR       0x00
#define OSD_FORMAT_16COLOR      0x01
#define OSD_FORMAT_256COLOR     0x02
#define OSD_FORMAT_2COLOR		0x03
#define OSD_FORMAT_DIRECT16_1	0x04
#define OSD_FORMAT_DIRECT16_2	0X05
#define OSD_FORMAT_DIRECT16_1B	0x06
#define OSD_FORMAT_DIRECT16_2B	0x07

#define OSD_FORMAT_DIRECT16A    0x04
#define OSD_FORMAT_DIRECT16B    0x05

/*
#define OSD_FORMAT_MASK         0x07
#define OSD_FORMAT_4COLOR       0x00
#define OSD_FORMAT_16COLOR      0x01
#define OSD_FORMAT_256COLOR     0x02
//#define OSD_FORMAT_DIRECTCOLOR  0x03
#define OSD_FORMAT_DIRECT16A    0x04
#define OSD_FORMAT_DIRECT16B    0x05
*/

#define OSDV2_CLUT_16b		0
#define OSDV2_CLUT_32b		1

#define BIT_CU			7       // [7] color-table update
#define BIT_FT			6       // [6] force-transparent
#define BIT_PR			4       // [5:4] pixel-resolution
#define BIT_MD			0       // [2:0] mode

#define BIT_SHD			4       // [7:4] shade
#define BIT_BLND		0       // [3:0] blend

#define	BIT_CLUT_TYPE	6		// [7:6] clut_type
#define	BIT_COLOR_RGB	5		// [5]
#define	BIT_SWAP_BYTE	4		// [4]
#define	BIT_SHADE_MODE	3		// [3]

#define V2_CLUT_TYPE(n)		((n)<<BIT_CLUT_TYPE)
#define V2_RGB_MODE         (1<<BIT_COLOR_RGB)
#define V2_SWAP_BYTE_OFF	(0<<BIT_SWAP_BYTE)
#define V2_SWAP_BYTE_ON		(1<<BIT_SWAP_BYTE)
#define V2_SHADE_MODE_A		(0<<BIT_SHADE_MODE)
#define V2_SHADE_MODE_B		(1<<BIT_SHADE_MODE)

typedef struct	{
	UINT16	x;
	UINT16	y;
} coordinate;

typedef struct	{
	UINT16	x_length;
	UINT16	y_length;
} dimension;

typedef struct  {
    UINT16  font_color;
    UINT16  background_color; 
    UINT16  outline1_color;
    UINT16  outline2_color;
} font_palette;

// real start location of bmp for drawing. support different distance between the two fonts 
typedef struct {
    coordinate draw_start;
    dimension draw_dimension;
}DrawDimension;

// the attributes about drawing method
typedef struct {
    UINT8 is_reference_palette;
    UINT8 bits_a_pixel;  // only support 1, 2, 4, 8 bits to a pixel
    UINT8 only_fore_color;    
}DrawType;    

// include all attributes about draw font and bitmap
typedef struct {
    coordinate start;                    // draw start location of region
    dimension bmp_dimension;   
    DrawDimension bmp_offset;      
    int region_index;
    const UINT16 *p_palette;
    const UINT8 *p_bmp;
    DrawType draw_type;
}DrawAttribute;

typedef struct 
{
    UINT8  config0;
    UINT8  config1;
    UINT8  config2;
    UINT8  config3;
    UINT16 v_size;
    UINT16 h_size;
    UINT16 y;
    UINT16 x;
    UINT16 link_data;
    UINT16 link_next;
} t_osdv2_header;

typedef struct  {
  UINT16        osd_header[2];  /* virtual addr of osd header           */
  UINT16        osd_w;          /* in byte                              */
  UINT16        osd_visible_w;   /* in pixel                             */
  UINT16        osd_h;          /* in pixel                             */
  UINT16		osd_x;
  UINT16		osd_y;
  UINT16        osd_highlight;
  UINT16        osd_highlight_w;
  UINT8			osd_used;
  UINT8         osd_format;     /* pixel-per-byte                       */

  #ifdef OSD_AUTO_RECOVER
  UINT8			osd_header_id;
  UINT16		osd_link_data[2];	//	value stored is already SWAPPED
  UINT16		osd_header_chk_sum[2];
  #endif // #ifdef OSD_AUTO_RECOVER
} t_osd_region;


//
// OSD Initialization Functions
//
typedef struct {
    UINT16  width;          //in pixel
    UINT16  height;         //in pixel
    UINT16  x;              //in pixel
    UINT16  y;              //in pixel
    UINT8   header_type;
    UINT8   format;
    UINT8   type;           //please use OSD_INTERLACED
} _t_osd_hdr;

/*
** OSD free buffer control.
** this is the end packed-address of OSD buffer.
*/
EXTERN_MEM  t_osd_region    region[MAX_REGION];//kenny add it 2001/5/8
EXTERN      UINT16          timeout_osd[MAX_REGION];
EXTERN      UINT8			osd_display_list[MAX_REGION];

EXTERN      UINT16          osd_free;
EXTERN_MEM  UINT8           osd_buf[50];
EXTERN      UINT8           osd_active_regions;

EXTERN      BYTE antic_begin;
EXTERN      BYTE antic_end;

#ifdef SUPPORT_SW_OSD_SCALING
typedef struct{
	UINT16 	x_divisor;
	UINT16	x_dividend;
	UINT16	y_divisor;
	UINT16	y_dividend;
}scaling_ratio;	
typedef struct{
  UINT16        		osd_header[2];  /* virtual addr of osd header           */
  UINT16	 		osd_link_data[2];
  UINT16         	osd_w;         /* in byte                             */
  UINT16         	osd_h;          /* in pixel                             */
  scaling_ratio		ratio;
}scaling_t_osd_region;

EXTERN_MEM  scaling_t_osd_region    scaling_region[MAX_REGION];
#endif

/************************************************************\
osd1.c head file
\************************************************************/
#ifdef NEW_OSD_DRIVER
void 	osd_create_region1(UINT8 region_index, int,int,t_osd_region *,BYTE,BYTE);
#else
void 	osd_create_region1(t_osd_region *, int,int,t_osd_region *,BYTE,BYTE);
#endif
void    osd_create_region_setup(t_osd_region *p, int X, int Y, t_osd_region *prev,BYTE bColorMode,BYTE bScanMode);
//void	osd_print_regionEQ(t_osd_region *, const char *);
void	osd_print_region1(t_osd_region *, const char *);

#endif//#ifndef _OSD_DRV_H_


