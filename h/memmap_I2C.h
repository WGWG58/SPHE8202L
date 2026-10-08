/******************************************************************
-------------   EEPROM memory map    ---------------  
-----   linrc creat this file 2006-2-20

	 *---------------------------------  ROMCHECKSUM_I2C_YA(0)
     |	setup menu(90~106)       |
     |                           |
     *--------------------------------- SEG_2_I2C_YA(setup_menu LEN)
     |       Resume  (100)       |
     |                           |
     *-------------------------------- RM_REG_CODE_I2C_ADD_ST(setup_menu+resume LEN)
     |      Divx DRM  (48)       |
     |                           |
     *-------------------------------- SEG_4_I2C_YA
     |           Other           |
     |    (255-setup-resume-DRM) |
     *--------------------------------- EEPROM_SIZE(255)

*******************************************************************/

#include "user_init.h"

#ifndef	__MEMMAP_I2C_H_
#define __MEMMAP_I2C_H_

#define EEPROM_SIZE					256

//**************************** Segment 1 ******************************************
//**************************** SETUP MENU ADDR IN EEPROM **************************
#define ROMCHECKSUM_I2C_YA	 		0
#define ROMCHECKSUM_I2C_SIZE		sizeof(UINT32)
#define SETUP_VA_I2C_YA		 		(ROMCHECKSUM_I2C_YA    + ROMCHECKSUM_I2C_SIZE)
#define SETUP_VA_I2C_SIZE			sizeof(setup_VA)
#define SETUP_CHECKSUM_I2C_YA		(SETUP_VA_I2C_YA       + SETUP_VA_I2C_SIZE)
#define SETUP_CHECKSUM_I2C_SIZE		sizeof(UINT16)
#define USER_SETUP_I2C_YA			(SETUP_CHECKSUM_I2C_YA + SETUP_CHECKSUM_I2C_SIZE)
#define USER_SETUP_I2C_SIZE			sizeof(t_USER_SET)

#ifdef SUPPORT_TVG_ACTIVATION
#define TVG_UNIT_ID_ADDR			(USER_SETUP_I2C_YA       + USER_SETUP_I2C_SIZE)
#define TVG_UNIT_ID_SIZE			sizeof(UINT16)
#define TVG_SHOWAD_COUNTER_ADDR		(TVG_UNIT_ID_ADDR        + TVG_UNIT_ID_SIZE)
#define TVG_SHOWAD_COUNTER_SIZE		sizeof(UINT8)
#define SEG_1_I2C_END				(TVG_SHOWAD_COUNTER_ADDR + TVG_SHOWAD_COUNTER_SIZE)
#else
#define SEG_1_I2C_END				(USER_SETUP_I2C_YA       + USER_SETUP_I2C_SIZE)						
#endif

//**************************** Segment 2 ******************************************
//*************************** Resume Information ADDR ******************************
#if defined(SAME_DISC_RESUME) || defined(POWER_RESUME) || defined(RECORD_KEY)
#define SEG_2_I2C_YA				SEG_1_I2C_END
#define DVD_INFO_BASE				SEG_2_I2C_YA
#define DVD_INFO_SIZE				52
#define CDROM_INFO_BASE				(DVD_INFO_BASE   + DVD_INFO_SIZE)
#define CDROM_INFO_SIZE				20
#define CDDA_INFO_BASE				(CDROM_INFO_BASE + CDROM_INFO_SIZE)
#define CDDA_VCD_INFO_SIZE			8
#define VCD_INFO_BASE				(CDDA_INFO_BASE  + CDDA_VCD_INFO_SIZE)

#define DISC_INFO_SIZE				4
#define DVD_DISC_INFO				(VCD_INFO_BASE   + CDDA_VCD_INFO_SIZE)
#define CDDA_DISC_INFO				(DVD_DISC_INFO   + DISC_INFO_SIZE)
#define VCD_DISC_INFO				(CDDA_DISC_INFO  + DISC_INFO_SIZE)
#define SEG_2_I2C_END				(VCD_DISC_INFO	 + DISC_INFO_SIZE)
#else
#define SEG_2_I2C_END				SEG_1_I2C_END
#endif

//**************************** Segment 3 ******************************************
//*************************** DIVX_DRM REG CODE ADDR ******************************
#ifdef DIVX_DRM
#define DRM_REG_CODE_I2C_ADD_LEN	48
#else
#define DRM_REG_CODE_I2C_ADD_LEN	0
#endif
#define DRM_REG_CODE_I2C_ADD_ST		SEG_2_I2C_END 
#define SEG_3_I2C_END				(DRM_REG_CODE_I2C_ADD_ST + DRM_REG_CODE_I2C_ADD_LEN)

//**************************** Segment 4 ******************************************
//**************************** other **************************************************
//Note:If We used segment 3 and 4,all the EEPROM space would be used,so we can not define
//other address to use... if you want to use Segment 4 in this case,PLS check SEG_4_FREE_MEM
//wether have enough memory space...

#define SEG_4_I2C_YA					SEG_3_I2C_END
#define SEG_4_FREE_MEM					(EEPROM_SIZE - SEG_4_I2C_YA)

#define TV_OUT_ID_ADDR					SEG_4_I2C_YA
#ifdef STORE_VIDEO_PARAMETER
#define TV_OUT_ID_SIZE					sizeof(UINT8)
#else
#define TV_OUT_ID_SIZE					0
#endif

#define VIDEO_MODE_I2C_ADDRESS			(TV_OUT_ID_ADDR + TV_OUT_ID_SIZE)
#ifdef IR_KEY_SET_VIDEO_MODE
#define VIDEO_MODE_I2C_SIZE				sizeof(UINT8)
#else
#define VIDEO_MODE_I2C_SIZE				0
#endif

#define USER_MPEG_LOGO_I2C_YA			(VIDEO_MODE_I2C_ADDRESS + VIDEO_MODE_I2C_SIZE)
#ifdef USER_MPEG_LOGO
#define USER_MPEG_LOGO_I2C_SIZE			sizeof(UINT8)
#else
#define USER_MPEG_LOGO_I2C_SIZE			0
#endif

#ifdef JPG_LOGO
#define JPG_LOGO_FLAG_I2C_SIZE			1
#define JPG_LOGO_LEN_H_I2C_SIZE			1
#define JPG_LOGO_LEN_L_I2C_SIZE			1
#else
#define JPG_LOGO_FLAG_I2C_SIZE			0
#define JPG_LOGO_LEN_H_I2C_SIZE			0
#define JPG_LOGO_LEN_L_I2C_SIZE			0
#endif
#define JPG_LOGO_FLAG_I2C_YA			(USER_MPEG_LOGO_I2C_YA + USER_MPEG_LOGO_I2C_SIZE)
#define JPG_LOGO_LEN_H_I2C_YA			(JPG_LOGO_FLAG_I2C_YA  + JPG_LOGO_FLAG_I2C_SIZE)
#define JPG_LOGO_LEN_L_I2C_YA			(JPG_LOGO_LEN_H_I2C_YA + JPG_LOGO_LEN_H_I2C_SIZE)

#define Addr_REMB_3D					(JPG_LOGO_LEN_L_I2C_YA + JPG_LOGO_LEN_L_I2C_SIZE)
#ifdef REMB_3DSOUND
#define Addr_REMB_3D_SIZE				2
#ifdef SUPPORT_MULTI_CHANNEL_5_BAND_EQ
#define Addr_REMB_3D_BAND_SIZE			5
#else
#define Addr_REMB_3D_BAND_SIZE			7
#endif
#else
#define Addr_REMB_3D_SIZE				0
#define Addr_REMB_3D_BAND_SIZE			0
#endif
#define Addr_REMB_3D_BAND				(Addr_REMB_3D + Addr_REMB_3D_SIZE)


#define	ADDR_I2C_VOLUME					(Addr_REMB_3D_BAND + Addr_REMB_3D_BAND_SIZE)
#ifdef VOLUME_RECODE
#ifdef CNTR_5SPK_VOLUME
#define	ADDR_I2C_VOLUME_SIZE			6		//if define CNTR_5SPK_VOLUME,if need 6 BYTE
#else
#define	ADDR_I2C_VOLUME_SIZE			sizeof(UINT8)
#endif
#else
#define	ADDR_I2C_VOLUME_SIZE			0
#endif

#define VIDEO_OUTPUT_ADDR				(ADDR_I2C_VOLUME + ADDR_I2C_VOLUME_SIZE)
#ifdef BBK_DVD
#define VIDEO_OUTPUT_SIZE  				sizeof(UINT8)
#else
#define VIDEO_OUTPUT_SIZE 				0
#endif

#ifdef DVB_DVD_8202           //sunzhh add 20060309
#define DVB_INFO_ADDR (VIDEO_OUTPUT_ADDR+VIDEO_OUTPUT_SIZE)
#ifdef SUPPORT_NEWDB
#define DVB_INFO_SIZE  20
#else
#define DVB_INFO_SIZE  0
#endif
#endif

#ifdef SUPPORT_TOUCH_PANEL//lichuanyue add ,used for touch_panel 2006-07-15
#ifdef DVB_DVD_8202
  #define  TOUCH_PANEL_ADDR (DVB_INFO_ADDR+DVB_INFO_SIZE)
#else
  #define  TOUCH_PANEL_ADDR (VIDEO_OUTPUT_ADDR+VIDEO_OUTPUT_SIZE)
#endif
  #define TOUCH_PANEL_SIZE  4
#endif//#ifdef SUPPORT_TOUCH_PANEL/

/*#if (VIDEO_OUTPUT_ADDR > EEPROM_SIZE) 
    #error "Out of EEPROM storage size\n"
#endif */
#endif//#ifndef	__MEMMAP_I2C_H_


