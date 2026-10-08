#define	CLUTE_TRANS	0x8080

/************************************************************\
 pal
\************************************************************/
//for 3d-sound menu
const	UINT16	palette_16color[] = 
{    
    __palette2F(  20, 128, 128,1,1),    //11 black //Jeff 20020404
	__palette2F(  75 , 85,  74,1,1),    //dark green    1
	__palette2F(  112, 64,  47,1,1),    //middle green  2
	__palette2F(  149, 43,  21,1,1),    //green         3
	__palette2F(  199, 15, 167,1,1),    //yellow        4
	__palette2F(  152, 41, 201,1,1),    //dark orange   5
	__palette2F(  164, 35, 192,1,1),    //bright orange 6
	__palette2F(  112, 64, 229,1,1),    //dark red      7
	__palette2F(   78, 84, 255,1,1),    //bright red    8
	__palette2F(  128,128, 128,1,1),    //gray white    9
	__palette2F(  0xa2, 0x2c, 0x8e,1,1),    //yellow-green  10
	CLUTE_TRANS,
	CLUTE_TRANS,
	CLUTE_TRANS,
	CLUTE_TRANS,
	CLUTE_TRANS,
};


//for setup menu and OSD0
//setup : 0, 1, 2, 3, 4, 5, 6, 7
//OSD0  : 0, 3, 8, 9, 10, 15
static	const	UINT16	palette_16color_setup[] = 
{
    __palette2F(  0x50, 0x70, 0x70,0,0),    //0  transparent
	__palette2F(  72, 178, 120,1,1),	    //1  gray-blue
	__palette2F(  196-30, 122, 130,1,1),	//2  near white //nono 2-3-11 14:05 for yuxing
	__palette2F(  132,144, 126,1,1),	    //3  gray white
	__palette2F(  72, 178, 120,1,1),	    //4  gray-blue
#ifndef KONKA_DVD//20020820
	__palette2F( 80, 170, 80,1,1),          //5  gray-green
	__palette2F(  112, 160, 112,1,1),	    //6  light-gray-blue
#else
	__palette2F(  80, 180, 80,1,0),         //5  gray-green
	__palette2F(  110, 170, 112,1,0),	    //6  light-gray-blue
#endif
	__palette2F(  0xa0, 0x28, 0x8c, 1, 1),  //7  yellow
	__palette2F(  180, 43,  21,1,1),        //8  green
	__palette2F(  180, 0x2c, 0x8e,1,1),     //9  yellow-green
	__palette2F(  180, 41, 201,1,1),        //10 dark orange
	__palette2F(  40+10, 128, 128,1,1),     //11 black //nono 2-3-11 14:05for yuxing
	CLUTE_TRANS, //12
	CLUTE_TRANS, //13
	CLUTE_TRANS, //14	
#ifdef GREY_OSD_DISP                                  // ych 2-7-8 17:39
		__palette2F( 100, 128, 128,1,1),      //15 gray white  
#else
	CLUTE_TRANS,                                      //15 OSD shadow color(not modify)
#endif 
};

//4 color palette
const	UINT16	palette_4color[] = 
{   
    __palette2F(  0x50, 0x70, 0x70,0,0),    //00b:background		
	CLUTE_TRANS,                                     //01b:transparent		
	__palette2F(  0x50, 0x70, 0x70,1,1),    //10b:anti background
#ifdef GREY_OSD_DISP                        
	__palette2F(  166, 122, 130,1,1),       //11b:text,white  
#else
	__palette2F(  0xa2, 0x2c, 0x8e,1,1),    //11b:text,yellow-green
#endif
};

const	UINT16 	bColorTab[]=
{ DRK_GREEN_COLOR,MID_GREEN_COLOR,BR_GREEN_COLOR,
YELLOW_COLOR,DRK_ORANGE,DRK_RED_COLOR,BR_RED_COLOR 
};  



/************************************************************\
 OSD Header Config
 config 0: color upate|force transparent|pixel resolution[1:0]|reserved|color mode[2:0](0:4 1:16 2:256 4:16bit#1 5:16bit#2)
 config 1: shade[3:0]|blend[3:0]
 config 2: CLUT entries type[1:0](0:16 bit,1:32 bit,2:27 bit)|rgb(0:YCbCr,1:RGB)|swp(0:Normal,1:BYTE swap)|shd(0:Sub,1:Ratio)|Reserved[1:0] 
\************************************************************/
const UINT8 osd_header_config[][3]=
{
      {//normal 4 color
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((0 & 0x03) << BIT_PR),
       //config 1
      	((0xf & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_16b)| V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      },
      {//eq 16 color
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((1 & 0x03) << BIT_PR),      	
       //config 1
      	((0xc & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_16b)| V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      },
      {//setup,display
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((0 & 0x03) << BIT_PR),      	
       //config 1
      	((0xf & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_16b)| V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      },
      {//nes game
       //config 0
      	((1&0x01) << BIT_CU)|((0) << BIT_FT)|((1 & 0x03) << BIT_PR),      	
       //config 1
      	((0xc & 0x0f) << BIT_SHD)| ((0xf & 0x0f) << BIT_BLND),
       //config 2
         V2_CLUT_TYPE(OSDV2_CLUT_16b)| V2_SWAP_BYTE_OFF| V2_SHADE_MODE_A
      }
};

UINT16 *osd__pal[]=
{
	  palette_4color,//normal
	  palette_16color,//eq
	  palette_16color_setup,//setup,display
	  NULL//nes game
};
/************************************************************\
 OSD Header Offset ,data block location
\************************************************************/
#define OSD_16b_BUG
#define ALIGN_32B(x) ((x+31)/32)

const	UINT8	osd_header_offset[8] = 
{
	
#ifdef OSD_16b_BUG	
    ALIGN_32B(16 + 4*4), 
	ALIGN_32B(16 + 4*16), 
	ALIGN_32B(16 + 4*256), 
#else	
    ALIGN_32B(16 + 2*4), 
    ALIGN_32B(16 + 2*16), 
    ALIGN_32B(16 + 2*256), 
#endif    

	ALIGN_32B(16),
	ALIGN_32B(16),
	ALIGN_32B(16),
	ALIGN_32B(16),
	ALIGN_32B(16)
};



