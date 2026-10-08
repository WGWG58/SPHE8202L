//
// FILE
// license.h
//
// ** COPYRIGHT NOTICE **
// SUNPLUS TECHNOLOGY CO., LTD.
//
// THIS FILE IS UNDER SUNPLUS CODE RELEASE COPYRIGHT PROTECTION.
//
// SUNPLUS CODE RELEASE LICENSE v0.1
//
// ANY CHANGE TO THIS FILE WILL INCLUDE VARIOUS CUSTOMER FUNCTION
// AND WILL REQUIRE PAYING SPECIFIC LICENSE FEE TO DEDICATED 
// COMPANY(S).  
//
// UPON CHANGE TO THIS FILE YOU AGREE TO ACT ACCORDING TO THE
// AGREEMENT WITH SUNPLUS TECHNOLOGY THAT YOU ARE REQUIRED TO
// FULFILL SPECIFIC LICENSE AGREEMENT CONTROL AND ROYALTY DUTY.
//

// video
#define LICENSE_ENABLE_MPEG4        (1<<0)
#define LICENSE_ENABLE_DIVX         (1<<1)
#define LICENSE_ENABLE_JPEG         (1<<2)

// audio
#define LICENSE_ENABLE_DVDAUDIO     (1<<8)
#define LICENSE_ENABLE_DTS          (1<<9)
#define LICENSE_ENABLE_MP3          (1<<10)
#define LICENSE_ENABLE_WMA          (1<<11)
#define LICENSE_ENABLE_PROLOGIC2    (1<<12)
#define LICENSE_ENABLE_HDCD         (1<<13)

extern  const   unsigned    int     license_control_flag;

#define is_license_enable_MPEG4()       (license_control_flag & LICENSE_ENABLE_MPEG4)
#define is_license_enable_DIVX()        (license_control_flag & LICENSE_ENABLE_DIVX)
#define is_license_enable_JPEG()        (license_control_flag & LICENSE_ENABLE_JPEG)
#define is_license_enable_DVDAUDIO()    (license_control_flag & LICENSE_ENABLE_DVDAUDIO)
#define is_license_enable_DTS()         (license_control_flag & LICENSE_ENABLE_DTS)
#define is_license_enable_MP3()         (license_control_flag & LICENSE_ENABLE_MP3)
#define is_license_enable_WMA()         (license_control_flag & LICENSE_ENABLE_WMA)
#define is_license_enable_PROLOGIC2()   (license_control_flag & LICENSE_ENABLE_PROLOGIC2)
#define is_license_enable_HDCD()        (license_control_flag & LICENSE_ENABLE_HDCD)



