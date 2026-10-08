//
// FILE
// memcfg.c
//
// DESCRIPTION
// configure memory
//

#include "config.h"
#include "global.h"
#include "regmap.h"
#include "stdlib.h"
#include "kinf.h"
#include "kernel.h"

#include "memmap.h"
#include "memmap0.h"
#include "framebuf.h"

#include "avd.h"
#include "dsp3_if.h"

#include "reset.h"
#include "sdctrl.h"

#include "memcfg.h"

#include "user_init.h"
#include "fsNAV.h"
#include "mem_anchor.h" //terry,2004/1/20 01:13PM
#include "auddrv.h"

#include "atapi_if.h"
#include "pic_if.h"

#ifdef MINUS_VR_AUTH_PLAYBACK
extern INT8 bDVDminusVR;
#endif

#ifndef DVDRELEASE
#define MEMCFG_DBG    1
#endif

#define memcfg_printf(s...)     ((void)0)

#ifdef MEMCFG_DBG
#include "sio.h"
#include "emuio.h"
#define MONE_CONFIG
#undef  memcfg_printf
#define memcfg_printf           printf_w
#endif

#ifdef TURBO_DECODE    
    #define MBLINE_W352     (P_BIDIR_LUMA_SIZE*1024)/352/16
    #define MBLINE_W480     (P_BIDIR_LUMA_SIZE*1024)/480/16
    #define MBLINE_W720     (P_BIDIR_LUMA_SIZE*1024)/720/16
    #define MBLINE_W1024    (P_BIDIR_LUMA_SIZE*1024)/1024/16
    
    //kevinmonkey 050427 for ultilizing the most of bidir buffer.
    //extra buffer comes from volume file system, when playing DVD video or vcd,svcd,
    //no file system needed, so file system buffer can be used as extra frame buffer.
    #define P_MBLINE_W352         (P_BIDIR_LUMA_SIZE*1024)/352/16
    #define P_MBLINE_W480         (P_BIDIR_LUMA_SIZE*1024)/480/16
    #define P_MBLINE_W720         (P_BIDIR_LUMA_SIZE*1024)/720/16
    #define P_MBLINE_W1024        (P_BIDIR_LUMA_SIZE*1024)/1024/16
    #define EXTRA_P_MBLINE_W352   ((P_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)*1024)/352/16
    #define EXTRA_P_MBLINE_W480   ((P_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)*1024)/480/16
    #define EXTRA_P_MBLINE_W720   ((P_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)*1024)/720/16
    #define EXTRA_P_MBLINE_W1024  ((P_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)*1024)/1024/16

    #define N_MBLINE_W352           (N_BIDIR_LUMA_SIZE*1024)/352/16
    #define N_MBLINE_W480           (N_BIDIR_LUMA_SIZE*1024)/480/16
    #define N_MBLINE_W720           (N_BIDIR_LUMA_SIZE*1024)/720/16
    #define N_MBLINE_W1024          (N_BIDIR_LUMA_SIZE*1024)/1024/16    
    #define EXTRA_N_MBLINE_W352     ((N_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)*1024)/352/16
    #define EXTRA_N_MBLINE_W480     ((N_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)*1024)/480/16
    #define EXTRA_N_MBLINE_W720     ((N_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)*1024)/720/16
    #define EXTRA_N_MBLINE_W1024    ((N_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)*1024)/1024/16  
#endif

void init_gp_parameter(int w)
{
    mode_aspect = 0;
    vpp_zoom    = 0;
    line_offset = (w+31)/32*32 ;
    set_framebuf_linear_mode_width(line_offset);    
    avd_disp_intp_mode(AVD_DISP_INTP_PROGRESSIVE);  
}


#ifdef NO_BLACK_for_PIC_CD
void copy_ref1_frame_mpg2gp(void)
{
   UINT8 *mpg,*gp;
   UINT16 luma_sz;
   UINT32 sz;

   printf("regs0->ref1_luma:%d\n",regs0->ref1_luma);
   printf("regs0->bidir_luma:%d\n",regs0->bidir_luma);
   printf("GP_REF1_LUMA:%d\n",GP_REF1_LUMA);   
   mpg = (UINT8 *)(SDRAM_BASE_CACHED + regs0->ref1_luma*1024);	
   gp = (UINT8 *)(SDRAM_BASE_CACHED + GP_REF1_LUMA*1024);
   sz = (regs0->bidir_luma-regs0->ref1_luma)*1024;
   luma_sz = regs0->vppref1_chroma - regs0->vppref0_luma;
   
   printf("mpg:%x gp:%x sz:%d %d\n",mpg,gp,sz/1024,sz);
   memcpy(gp,mpg,sz);
   
   regs0->ref1_luma       = GP_REF1_LUMA;
   regs0->ref1_chroma     = GP_REF1_LUMA + LUMA_SIZE;
   regs0->vppref1_luma    = GP_REF1_LUMA;
   regs0->vppref1_chroma  = GP_REF1_LUMA + LUMA_SIZE;   
}


void init_pic_cd_first_play(void)
{
    extern void set_fbuf_size(int l, int c);
    
    copy_ref1_frame_mpg2gp();
    set_disbuf_now(1);
    
    regs0->ref0_luma       = GP_REF0_LUMA;//terry,2004/2/4 07:39PM
    regs0->ref0_chroma     = GP_REF0_CHROMA;
    regs0->vppref0_luma    = GP_REF0_LUMA;
    regs0->vppref0_chroma  = GP_REF0_CHROMA;   
     
    init_gp_parameter(720);
    
    set_fbuf_size( GP_LUMA_SIZE, GP_CHROMA_SIZE ); //terry,2004/2/18 02:40PM
    clrFrameBuffer(FRAME_REF0);    
}


void init_hw_gp_md(void)
{
    memory_config_saved = MEMORY_GRAPH_PAL;
    disable_video();
    memcfg_set_framebuf_anchor(anchor_gp);
    clrFrameBuffer(FRAME_REF1);
#ifdef SDRAM_NO_REORDER 
    setup_vpp_mapping(3,1);
#else
    setup_vpp_mapping(3,0);
#endif
    setvpp_linear_mode_width(736);
    vpp_reset_framebuf_state();
    enable_video();
}

#endif	

void SetHostDMAReadBuffer(UINT32 uPosition,UINT32 uSize)
{
#ifdef IC_8202L
    regs0->cdrya       = uPosition;
    regs0->cdrya_limit = uPosition + uSize;
#else
    regs0->cdrya       = uPosition;
    regs0->cdrya_limit = uSize;
#endif
}

void GetHostDMAReadBuffer(UINT32 *pPosition,UINT32 *pSize)
{
#ifdef IC_8202L
    if(pPosition != NULL)  *pPosition = regs0->cdrya;
    if(pSize     != NULL)  *pSize     = (regs0->cdrya_limit - regs0->cdrya);
#else
    if(pPosition != NULL)  *pPosition = regs0->cdrya;
    if(pSize     != NULL)  *pSize     = regs0->cdrya_limit;
#endif
}

void SetHostDMAWriteBuffer(UINT32 uPosition,UINT32 uSize)
{
#ifdef IC_8202L
    regs0->cdwya       = uPosition;
    regs0->cdwya_limit = uPosition + uSize;
#else
    regs0->cdwya       = uPosition;
    regs0->cdwya_limit = uSize;
#endif
}

//if you want to get only position or size, try CBV_YS and CBV_H
void GetHostDMAWriteBuffer(UINT32 *pPosition,UINT32 *pSize)
{
#ifdef IC_8202L

    if(pPosition != NULL)  *pPosition = regs0->cdwya;
    if(pSize     != NULL)  *pSize     = (regs0->cdwya_limit - regs0->cdwya);
#else
    if(pPosition != NULL)  *pPosition = regs0->cdwya;
    if(pSize     != NULL)  *pSize     = regs0->cdwya_limit;
#endif
}

void SetVPPBufferHorizontalStride(UINT32 uStride)
{
#ifdef IC_8202L
    regs0->g23_reserved[13] = (uStride+15)/16;
#else   //!IC_SUPPORT_MACROBLOCK_EXTENTION
    if(uStride <= 352)
        regs0->vpp_config1 = (regs0->vpp_config1 & ~0x07) | 0x02;   // 352 display
    else if(uStride <= 480)
        regs0->vpp_config1 = (regs0->vpp_config1 & ~0x07) | 0x03;   // 480 display
    else if(uStride <= 720)
        regs0->vpp_config1 = (regs0->vpp_config1 & ~0x07) | 0x00;   // 720 display
    else if(uStride <= 1024)
        regs0->vpp_config1 = (regs0->vpp_config1 & ~0x07) | 0x01;   // 1024 display
    else
        regs0->vpp_config1 = (regs0->vpp_config1 & ~0x07) | 0x04;   // 1440 display
#endif  //#ifdef IC_8202L
}

/*  // 2004/07/02 yltseng mark
#if defined( SUPPORT_JPEG_MIC ) && !defined( MOVE_PAL_AUDYA )//terry,2004/1/14 01:47PM
void set_dsp_codec_addr( int jpeg, int iConfig )
{ 
     if(jpeg)
      set_aud_buf(A_MIC_DSP24YA, A_AUDYA, A_MIC_PCM_YA);      
     else
      set_aud_buf(A_DSP24YA, A_AUDYA, A_PCMYA); 
}
#endif 
*/

/*// 2004/11/18 yltseng
// 2004/07/02 yltseng
void set_dsp_codec_addr()
{
#ifdef SUPPORT_JPEG_MIC
    if( pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG )
        set_aud_buf( A_MIC_DSP24YA, A_AUDYA, A_MIC_PCM_YA );      
    else
#endif

#ifdef MOVE_PAL_AUDYA
        set_aud_buf( A_DSP24YA, ( regs0->mc_compress != 0 ) ? P_AUDYA : A_AUDYA, A_PCMYA ); 

    if( pFsJpeg->gifsFuncBtn != FS_FUNC_JPEG )
        reset_audio_buf();        
#else
        set_aud_buf( A_DSP24YA, A_AUDYA, A_PCMYA ); 
#endif
}
*/

//
// setup other buffer start-address.  
static inline void
SetupOtherBufferPointer( void )
{ 
    // DVD DSP DMA Buffer pointer
    SetHostDMAWriteBuffer(A_CDYA,CDSIZE);

    //Audio DSP code,bit-stream,output pcm buffer pointer    
    //set_dsp_codec_addr();   // 2004/11/18 yltseng

    //iop code pointer
    regs0->iopya        = A_IOPYA;
    regs0->iop_memlimit = IOP_SIZE*4;//unit equ. 256 bytes
  
    //de-interlace paramenter
    regs0->dip_ref_base = A_DEINTLACE_YA;
}


//
// FUNCTION 
// config_Lmem(enable)
//
//  +------------------+ row_st
//  |    B     |       |
//  +----------+       |
//  |                  |
//  +------------------+ base
//
static void
config_Lmem(int enable)
{
    if (enable)
    {
        regs0->sdctrl_lmem_base = 0x1; //unit:2MB
        regs0->sdctrl_lmem_row_st = SDCTRL_L_TYPE_W_256|SDCTRL_L_TYPE_EN|(P_REF0_LUMA);
//        regs0->sdctrl_lmem_row_st = SDCTRL_L_TYPE_W_256|SDCTRL_L_TYPE_EN|281;
    }
    else
    {
        regs0->sdctrl_lmem_row_st = SDCTRL_L_TYPE_DIS;
    }   
}


static void
config_mc_compression(int enable)
{
    if (enable)
    {
#ifdef ONLY_B_PIC     
        regs0->mc_compress = 0x100;//picture type B.P.I
#else     
        regs0->mc_compress = 0x111;//picture type B.P.I
#endif    
#if defined(IC_8202D)||defined(IC_8202L)||defined(IC_8203A)
        regs0->mc_config |= (1<<2);
#endif
    }
    else
    {
        regs0->mc_compress = 0;
#if defined(IC_8202D)||defined(IC_8202L)||defined(IC_8203A)
        regs0->mc_config &= ~(1<<2);
#endif        
    }
}

void YCbCrGrapeMdCfg(int w,int h)
{
    init_gp_parameter(w);
    
    set_dis_pic_size(w,h);
    setup_display_now();

    #ifdef TURBO_DECODE      
    flddec_init(0, 0);
    #endif
    
#ifdef SDRAM_NO_REORDER 
    setup_vpp_mapping(3,1);
#else
    setup_vpp_mapping(3,0);
#endif
}


UINT16  memory_config_w_saved;
UINT16  memory_config_h_saved;

//
// FUNCTION
// reset_mem_cfg
//
// DESCRIPTION
// reset memory configuration so that next time will always setup all
// memory related registers
//
void
reset_mem_cfg(void)
{
    memory_config_saved = 0xff;
}

#ifdef SUPPORT_VIDEO_BUFFER_SWITCHING
UINT32	memcfg_buffer_number()
{
#if defined (SDRAM_32Mb_Mode)
	extern	UINT16		display_option;
	if (GetCurrentFileType() == CDROM_MP4)	return 3;
	else									return 4;
#elif defined (SDRAM_64Mb_Mode)
	return 5;
#else
	return 3;
#endif
}
#endif // #endif SUPPORT_VIDEO_BUFFER_SWITCHING

void
memcfg_set_framebuf_anchor(const UINT16 p[])
{
    // mc luma
    regs0->ref0_luma        = p[0];
    regs0->ref1_luma        = p[1];
    regs0->bidir_luma       = p[2];

    // mc chroma
    regs0->ref0_chroma      = p[3];
    regs0->ref1_chroma      = p[4];
    regs0->bidir_chroma     = p[5];

    // vpp luma
    regs0->vppref0_luma    = p[6];
    regs0->vppref1_luma    = p[7];
    regs0->vppbidir_luma   = p[8];

    // vpp chroma
    regs0->vppref0_chroma  = p[9];
    regs0->vppref1_chroma  = p[10];
    regs0->vppbidir_chroma = p[11];
    
    ///////////////////////////////////////////////////////////
	extern UINT8 buffer_switching_enable;
    #ifdef SUPPORT_VIDEO_BUFFER_SWITCHING
	set_multi_buffer_anchors(P_DEINT0_LUMA,	P_DEINT0_CHROMA,
							P_DEINT1_LUMA,	P_DEINT1_CHROMA);
	update_n_frame_buf_anchor();

	#if defined(ALLOCATE_SINGLE_DEINTERLACE_FRAME_BUFFER)
	set_multi_buffer_number(4);
	#elif defined (ALLOCATE_DOUBLE_DEINTERLACE_FRAME_BUFFER)
	set_multi_buffer_number(5);
	#endif

	if (memcfg_buffer_number() > 3)
		buffer_switching_enable = 1;
	else
		buffer_switching_enable = 0;

    #else
	buffer_switching_enable = 0;
	#endif
}


#ifdef  DVD_AUDIO
//terry,2004/2/17 02:13PM
void config_dvd_audio_memmap(void)
{
   if (regs0->dis_pic_id==1) {
   	fbuf_copy(0,1);
   }
   memcfg_set_framebuf_anchor(anchor_dvdaudio);
   //printf("\n\n**** CHANGE ANCHOR\n\n");
   //delay_srv_10ms(100);
}
#endif

// 2004/07/07 yltseng
#if defined( SDRAM_16Mb_Mode ) && defined( SUPPORT_FILE_SYSTEM_MODE )
    void ModifyFsBufAddr()
    {
        extern UINT32   _fs9660_buf;
        UINT32          uiCurFsAddr;
        if( regs0->mc_compress )
            uiCurFsAddr = SDRAM_BASE + P_FS9660YA * 1024;
        else
            uiCurFsAddr = SDRAM_BASE + N_FS9660YA * 1024;

        if( cd_type_loaded == CDROM && uiCurFsAddr != _fs9660_buf )
        {
            memcpyS( (void*)uiCurFsAddr, (void*)_fs9660_buf, FS9660_SIZE * 1024 );
            _fs9660_buf = uiCurFsAddr;
        }
    }
#else
    inline void ModifyFsBufAddr() {}    // 2004/08/26 yltseng
#endif

// 2004/07/21 yltseng
#ifdef MOVE_NAV_BUF //kevinmonkey 050427 define MOVE_NAV_BUF if nav buffer is adopted and address may change.
    #ifdef TURBO_DECODE //kevinmonkey 050405  Nav buffer position differs among DVD and File play 
    inline void ModifyNavBufAddr(int config)
    {
        extern UINT32   g_uiNavBufAddr;
        UINT32          uiCurNavBufAddr;
        if( config == MEMORY_GRAPH_SMALL )
            uiCurNavBufAddr = SDRAM_BASE + S_NAVYA * 1024;  //for CDROM, like reading volume fs structure.
        else
            uiCurNavBufAddr = SDRAM_BASE + N_NAVYA * 1024;  //for DVD(both PAL and NTSC)

        // 2005/06/19 yltseng, because NavBuffer overlaps mp4 file buffer, so we have to 
        // invalidate NavBuffer every time when mp4 is played.
        wb_tag_init();
        
        g_uiNavBufAddr = uiCurNavBufAddr;
    }    
    #else   //!TURBO_DECODE, USE_NAV_BUF_16M or USE_NAV_BUF_16M_DECREASE_SUBPICTURE,
            //nav buffer address differs among PAL and NTSC (L-men or not) configuration
    inline void ModifyNavBufAddr()
    {
        extern UINT32   g_uiNavBufAddr;
        UINT32          uiCurNavBufAddr;
        if( regs0->mc_compress )
            uiCurNavBufAddr = SDRAM_BASE + P_NAVYA * 1024;  //for PAL DVD
        else
            uiCurNavBufAddr = SDRAM_BASE + N_NAVYA * 1024;  //for NTSC DVD

        if( g_uiNavBufAddr != uiCurNavBufAddr )
            wb_tag_init();
        
        g_uiNavBufAddr = uiCurNavBufAddr;
    }
    #endif  //#ifdef TURBO_DECODE
#else   //!MOVE_NAV_BUF
    inline void ModifyNavBufAddr() {}
#endif

#ifdef SUPPORT_MP4  // 2004/08/11 yltseng
static void SetEvbyaLimit( UINT32 uiLimit )
{
    if( GetCurrentFileType() == CDROM_MP4 )
        regs0->evbya_limit  = A_AVIEVBSZ;
    else
        regs0->evbya_limit  = uiLimit;
}
#else
static inline void SetEvbyaLimit( UINT32 uiLimit )
{
    regs0->evbya_limit  = uiLimit;
}
#endif

int 
get_video_framebuf_size()
{
#ifdef SUPPORT_HIGH_DEFINITION_VIDEO
    return MAX_VIDEO_HORIZONTAL_RESOLUTION*MAX_VIDEO_VERTICAL_RESOLUTION;
#else  //!SUPPORT_HIGH_DEFINITION_VIDEO
	return (720*576);	
#endif  //#ifdef SUPPORT_HIGH_DEFINITION_VIDEO
}


//
// FUNCTION
// config_memory_size
//
// DESCRIPTON
// setup memory configuration, abort if same with previous setting
//
void
config_memory_size(int config, int w, int h, int force)
{
    extern void set_fbuf_size(int l, int c);
    
    int         blue;
#ifdef SDRAM_16Mb_Mode//terry,2003/10/21 10:03AM        
    int         osd_enable;//terry,2003/10/20 03:24PM
#endif    
    int         configX;
    unsigned    evbya_old;
    unsigned    osdya_n;
    unsigned    supya_n;

#ifdef NO_BLACK_for_PIC_CD    
    if(pic_cd_first_play) return;
#endif    

#ifdef DVD_AUDIO    
    if (AOB) config = MEMORY_DVD_AUDIO;
    else  pDSV->asv_loaded_addr=0; //terry,2004/2/19 05:02PM
#endif    

#if !defined( SDRAM_16Mb_Mode ) || defined( SUPPORT_FILE_SYSTEM_MODE )//2004/08/11 yltseng
    //config mvc buffer
#ifdef SUPPORT_HIGH_DEFINITION_VIDEO
    if(config == MEMORY_DVD_PAL_W1024)
    	regs0->mvcya = HD_MVC_BUF_YA;
    else
#endif
    	regs0->mvcya = MVC_BUF_YA;
#endif

    configX = config;

    if (force)
    {
	    if (config==MEMORY_UNKNOWN_PAL) {
	        config = MEMORY_DVD_PAL;
	        configX = 0xff;         // spepcial marker, force update next time
	    } else if (config==MEMORY_UNKNOWN_NTSC) {
	        config = MEMORY_DVD_NTSC;
	        configX = 0xff;         // spepcial marker, force update next time
	    }	    
    }
    else
	{
		if (config==MEMORY_UNKNOWN_PAL) {
			if (w==memory_config_w_saved && h==memory_config_h_saved) return;
			config = MEMORY_DVD_PAL;
    		configX = 0xff;         // spepcial marker, force update next time
		} else if (config==MEMORY_UNKNOWN_NTSC) {
    		if (w==memory_config_w_saved && h==memory_config_h_saved) return;
    		config = MEMORY_DVD_NTSC;
    		configX = 0xff;         // spepcial marker, force update next time
		} else if (config==memory_config_saved) {
#ifdef  DVD_AUDIO
    		if ( (AOB) && ((memory_config_w_saved!=w) || (memory_config_h_saved!=h))) {
        		disable_video();
        		clrFrameBuffer(FRAME_REF0|FRAME_REF1);        
        		setVPP_PictureSize(w,h);
        		enable_video();
        		memory_config_w_saved = w;
			memory_config_h_saved = h;
    		}
#endif
    return;            // abort
        }
	}

#ifdef MONE_CONFIG
    memcfg_printf("\n\n===========>config mem %x(%x)\n", config, memory_config_saved);
#endif
    //
    // check what color to fill during black
    blue = (config==MEMORY_PREVIEW);

    if (!blue)
    {
        vpp_set_bg_color(0,0x8080); //black color
    }
    else
    {
        vpp_set_bg_color(0x40,0xc07c); 
    }
    //
    // blank the display
    disable_video();

#ifdef SDRAM_16Mb_Mode//terry,2003/10/21 10:03AM    
    osd_enable = regs0->osd_en;//terry,2003/10/20 03:23PM
    osd_disable();
#endif    

    delay_srv_10ms(1);

    //vpp_set_bg_color(0,0x8080); //black color

    // 
    // enable all clocks
    setup_clock_gating(0);
    regs0->clken0 = 0xffff;         // enable
    regs0->clken1 = 0xffff;         // enable

    evbya_old   = regs0->evbya;

#ifdef  MEMCFG_MOVE_OSDSUP
    // 2004/06/12 yltseng
    osdya_n     = MN_OSDYA;
    supya_n     = MN_SUPYA;
#else
    osdya_n     = A_OSDYA;
    supya_n     = A_SUPYA;
#endif

#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
    if(full_scrn & MESSAGE)//zhaoyanhua add 2003-12-18 10:12
        DrawNewWindow();
#endif  

    switch(config)
    {
    case MEMORY_GRAPH_NTSC:     // 736x480  
    {
        memcfg_set_framebuf_anchor(anchor_gn);
        set_fbuf_size( GP_LUMA_SIZE, GP_CHROMA_SIZE );

        YCbCrGrapeMdCfg(720,480);
        setvpp_linear_mode_width(736);
    }
    break;

    case MEMORY_GRAPH_PAL:      // 736x576
    {
        memcfg_set_framebuf_anchor(anchor_gp);
        set_fbuf_size( GP_LUMA_SIZE, GP_CHROMA_SIZE);

        YCbCrGrapeMdCfg(720,576);
        setvpp_linear_mode_width(736);
    }
    break;

    case MEMORY_GRAPH_SMALL:    // 352x288
    {
        memcfg_set_framebuf_anchor(anchor_gs);
        set_fbuf_size( GS_LUMA_SIZE, GS_CHROMA_SIZE);

        YCbCrGrapeMdCfg(352,288);
        setvpp_linear_mode_width(352);
        #if defined(TURBO_DECODE) || !defined(SDRAM_16Mb_Mode)
        //kevinmonkey 050504 this delay is added due to that when turbo decodeor 32m, a lot of code
        //before enable_video is not execute comparing to Lmem. Therefore when we play clips
        //with resolution greater than 352x288, say 720x480, memory from 352x288 to 720x480
        //is shown but not cleared
        delay_srv_10ms(5);
        #endif
    }
    break;

#ifdef SUPPORT_HD_RESOLUTION

    case MEMORY_GRAPH_HD_720P:      // 1280X720
    {
        memcfg_set_framebuf_anchor(anchor_ghd_1080i);
        set_fbuf_size( HD_GP_LUMA_SIZE, HD_GP_CHROMA_SIZE);

        YCbCrGrapeMdCfg(JPEG_HD_FULLSCREEN_W_720P,JPEG_HD_FULLSCREEN_H_720P);
        setvpp_linear_mode_width(JPEG_HD_FULLSCREEN_W_720P);
    }
    break;

    case MEMORY_GRAPH_HD_1080I:      // 1920X1080
    {
        memcfg_set_framebuf_anchor(anchor_ghd_1080i);
        set_fbuf_size( HD_GP_LUMA_SIZE, HD_GP_CHROMA_SIZE);

        YCbCrGrapeMdCfg(JPEG_HD_FULLSCREEN_W_1080I,JPEG_HD_FULLSCREEN_H_1080I);
        setvpp_linear_mode_width(JPEG_HD_FULLSCREEN_W_1080I);
    }
    break;
#endif

#ifdef SUPPORT_PREVIEW_9FRAMES
    case MEMORY_PREVIEW:
        vpp_set_bg_color(0x40,0xc07c);                  // blue color
        memcfg_set_framebuf_anchor(anchor_preview);
    #ifdef  MEMCFG_COMPACT_MODE
        set_fbuf_size(M_BIDIR_LUMA_SIZE,M_BIDIR_CHROMA_SIZE); //kevinmonkey 050331 more reasonable than LUMA_SIZE,CHROMA_SIZE
        regs0->evbya            = M_EVBYA;
        SetEvbyaLimit( M_EVBSZ );

        // set decode buffer to 480x576
        regs0->mc_mbwidth   = 30;                                       // 480 decode
        set_framebuf_mb_mode_width(30);                                 // 480 source buffers
        SetVPPBufferHorizontalStride(720);                              // 720 Display
    #else   /*!defined(MEMCFG_COMPACT_MODE)*/
        set_fbuf_size( LUMA_SIZE, CHROMA_SIZE );
    
        regs0->evbya            = P_EVBYA;
        SetEvbyaLimit( P_EVBSZ );

    #endif/*!defined(MEMCFG_COMPACT_MODE)*/

    #ifdef TURBO_DECODE
        flddec_init(0, 0);
    #endif

    #ifdef SDRAM_NO_REORDER 
        setup_vpp_mapping(3,1);
    #else
        setup_vpp_mapping(3,0);
    #endif

        set_disbuf(2);
        line_offset = (720+31)/32*32 ;    
        set_framebuf_linear_mode_width(line_offset);

        // set linear mode width
        setvpp_linear_mode_width(720);

        break;
#endif
        
#ifdef DVD_AUDIO
    case MEMORY_DVD_AUDIO:
    {
        memcfg_set_framebuf_anchor(anchor_dvdaudio);
        set_fbuf_size( LUMA_SIZE, CHROMA_SIZE );

        regs0->evbya            = P_EVBYA;
        SetEvbyaLimit( P_EVBSZ );

        set_disbuf(0);              

        regs0->mc_mbwidth = 45;                                     // 720 mc
        set_framebuf_mb_mode_width(45);                             // 720 source buffer
        SetVPPBufferHorizontalStride(720);                          // 720 display

        #ifdef TURBO_DECODE      
        flddec_init(1, MBLINE_W720);        
        setup_vpp_mapping(2,0);
        #else
        setup_vpp_mapping(1,0);
        #endif
    }
    break;
#endif

#ifdef  SUPPORT_MIDI
    case MEMORY_MIDI:
    {
        regs0->ref0_luma        = D_REF0_LUMA; 
        regs0->ref0_chroma      = D_REF0_CHROMA;
        regs0->ref1_luma        = D_REF1_LUMA;
        regs0->ref1_chroma      = D_REF1_CHROMA;
        regs0->bidir_luma       = D_BIDIR_LUMA;
        regs0->bidir_chroma     = D_BIDIR_CHROMA;
       
        regs0->vppref0_luma     = regs0->ref0_luma;
        regs0->vppref1_luma     = regs0->ref1_luma;
        regs0->vppref0_chroma   = regs0->ref0_chroma;
        regs0->vppref1_chroma   = regs0->ref1_chroma;
        regs0->vppbidir_luma    = regs0->bidir_luma;
        regs0->vppbidir_chroma  = regs0->bidir_chroma;

        regs0->evbya            = D_EVBYA;
        SetEvbyaLimit( D_EVBSZ );

        set_fbuf_size( D_LUMA_SIZE, D_CHROMA_SIZE );

        set_disbuf(0);         

        regs0->mc_mbwidth = 22;                                     // 352 (22)
        set_framebuf_mb_mode_width(22);                             // 352 (22)
        SetVPPBufferHorizontalStride(352);                          // 352 (type 010)
        setVPP_PictureSize(352,288);
     
        #ifdef TURBO_DECODE      
        flddec_init(1, MBLINE_W352);        
        setup_vpp_mapping(2,0);
        #else
        setup_vpp_mapping(1,0);
        #endif
    }
    break;
#endif  // SUPPORT_MIDI

    case MEMORY_DVD_NTSC:
    case MEMORY_SVCD_NTSC:
    case MEMORY_CVD_NTSC:
    case MEMORY_VCD_NTSC:   
    case MEMORY_SVCD_PAL:
    case MEMORY_CVD_PAL:
    case MEMORY_VCD_PAL:    
#if defined( SDRAM_16Mb_Mode ) && defined( SUPPORT_FILE_SYSTEM_MODE )
    case 0xff:  // 2004/08/26 yltseng
#endif
#ifdef MEMCFG_COMPACT_MODE
    {
        memcfg_set_framebuf_anchor(anchor_compact);
        set_fbuf_size( N_LUMA_SIZE, N_CHROMA_SIZE );

        regs0->evbya            = N_EVBYA;
        SetEvbyaLimit( N_EVBSZ );

        set_disbuf(0);              
        
    #ifdef TURBO_DECODE //kevinmonkey 050427 determine turbo decoding parameter
        #if (((N_BIDIR_LUMA_SIZE + EXTRA_BIRDIR_LUMA_SIZE)<<10) < 480*480)
        #error "config_memory_size:not enough frame buffer for NTSC SVCD,turbo decode parameters needs modification."
        #endif
        
        int EnableTurboDecode = 0;
        int TurboDecodeLine   = 0;
        
        if(config == MEMORY_DVD_NTSC)
        {
            EnableTurboDecode = TRUE;            
            if(cd_type_loaded == CDDVD)
            {   //this section of code is not useful, since logo is NTSC mpeg so usually
                //we didn't reach this far when we play NTSC DVD if not forced configurate.

                //no file system, ultilize extra bidir frame buffer 
                //kevinmonkey 050427 bidir luma size enlarged, therefore anchor set 
                //for bidir chroma before is not correct.
                regs0->bidir_chroma    = N_BIDIR_CHROMA + EXTRA_BIRDIR_LUMA_SIZE;
                regs0->vppbidir_chroma = N_BIDIR_CHROMA + EXTRA_BIRDIR_LUMA_SIZE;
                TurboDecodeLine = EXTRA_N_MBLINE_W720;
            }else
            {
                TurboDecodeLine = N_MBLINE_W720;
            }
        } 
        else if(config == MEMORY_SVCD_PAL)
        {
            EnableTurboDecode = TRUE;            
            if(cd_type_loaded == CDSVCD)
            {   //no file system, ultilize extra bidir frame buffer 
                regs0->bidir_chroma    = N_BIDIR_CHROMA + EXTRA_BIRDIR_LUMA_SIZE;
                regs0->vppbidir_chroma = N_BIDIR_CHROMA + EXTRA_BIRDIR_LUMA_SIZE;
                TurboDecodeLine = EXTRA_N_MBLINE_W480;
            }else
            {
                TurboDecodeLine = N_MBLINE_W480;
            }            
        } 
        else if(config == MEMORY_SVCD_NTSC)
        {
            if(cd_type_loaded == CDSVCD)
            {   //ultilize extra bidir frame buffer. most critical case!
                regs0->bidir_chroma    = N_BIDIR_CHROMA + EXTRA_BIRDIR_LUMA_SIZE;
                regs0->vppbidir_chroma = N_BIDIR_CHROMA + EXTRA_BIRDIR_LUMA_SIZE;
                EnableTurboDecode = FALSE;  
            } else
            {
                TurboDecodeLine = N_MBLINE_W480;                
                EnableTurboDecode = TRUE;
            }
        } 
        else
        {
            EnableTurboDecode = FALSE;
        }
    #endif  //#ifdef TURBO_DECODE
        

        switch(config)
        {
            case MEMORY_DVD_NTSC:
                regs0->mc_mbwidth   = 45;                                       // 720
                set_framebuf_mb_mode_width(45);
                SetVPPBufferHorizontalStride(720);                              // 720
                setVPP_PictureSize(720,480);
                break;
            case MEMORY_VCD_NTSC:    //kevinmonkey 050525, originally, these use 480 as width,
            case MEMORY_VCD_PAL:     //but when TURBO DECODE, we don't have much memory to waste.
            case MEMORY_CVD_NTSC:    // Thus, to disable turbo decode for these config, precise 
            case MEMORY_CVD_PAL:     //configuration of mb width is necessary.
                regs0->mc_mbwidth   = 22;                                       // 352
                set_framebuf_mb_mode_width(22);
                SetVPPBufferHorizontalStride(352);                              // 352
                setVPP_PictureSize(352,480);
                break;
            default:
                regs0->mc_mbwidth   = 30;                                       // 480
                set_framebuf_mb_mode_width(30);
                SetVPPBufferHorizontalStride(480);                              // 480
                setVPP_PictureSize(480,480); 
                break;
        }
        
        #ifdef TURBO_DECODE
        flddec_init(EnableTurboDecode, TurboDecodeLine);
        if( EnableTurboDecode == TRUE)
            setup_vpp_mapping(2,0);
        else 
            setup_vpp_mapping(1,0);
        #else   //!TURBO_DECODE
        setup_vpp_mapping(1,0);
        #endif  //#ifdef TURBO_DECODE
    }
    break;
#endif/*defined(MEMCFG_COMPACT_MODE)*/

    // (PAL)
    // for typical decoding, all set to maximum size
    case MEMORY_DVD_PAL:
    case MEMORY_DVD_PAL_W352:
    case MEMORY_DVD_PAL_W480:
    case MEMORY_DVD_PAL_W1024:
    default:
    {   
        memcfg_set_framebuf_anchor(anchor_dvdpal);
        
        set_fbuf_size( LUMA_SIZE, CHROMA_SIZE );

        regs0->evbya            = P_EVBYA;
        SetEvbyaLimit( P_EVBSZ );

    #ifdef SUPPORT_HIGH_DEFINITION_VIDEO  //override previous setting
        if(config == MEMORY_DVD_PAL_W1024)
        {
            memcfg_set_framebuf_anchor(anchor_dvdHD);
            set_fbuf_size( HD_LUMA_SIZE, HD_CHROMA_SIZE );
            
            supya_n      = HD_SUPYA;
       
            regs0->mvcya = HD_MVC_BUF_YA;

            regs0->evbya = HD_EVBYA;
            SetEvbyaLimit( HD_EVBYA_SIZE );
        }
    #endif  //#ifdef SUPPORT_HIGH_DEFINITION_VIDEO

        set_disbuf(0);              
                         
        if (config == MEMORY_DVD_PAL_W352)
        {
            regs0->mc_mbwidth = 22;                                     // 352 mc
            set_framebuf_mb_mode_width(22);                             // 352 source buffer
            SetVPPBufferHorizontalStride(352);                          // 352 display                    

            #ifdef TURBO_DECODE      
            flddec_init(1, MBLINE_W352);
            #endif                                                
        }                        
        else if (config == MEMORY_DVD_PAL_W480)
        {
            regs0->mc_mbwidth = 30;                                     // 480 mc
            set_framebuf_mb_mode_width(30);                             // 480 source buffer
            SetVPPBufferHorizontalStride(480);                          // 480 display                    

            #ifdef TURBO_DECODE      
            flddec_init(1, MBLINE_W480);
            #endif                                
        }            
        else if (config == MEMORY_DVD_PAL_W1024)
        {   
        	#ifdef HW_SUPPORT_ARBITRARY_FRMEBUFFER_WIDTH                     
            regs0->vpp_config |= 4;										// disable vpp line buffer
            if(w == 1024)
            {
            	regs0->g5_reserved_1[2] &= (-2);
            	regs0->mc_mbwidth = 64;                                     // 1024 mc
            	set_framebuf_mb_mode_width(64);                             // 1024 source buffer
            	SetVPPBufferHorizontalStride(1024);                         // 1024 display
            }
            else
            {
            	regs0->g5_reserved_1[2] |= 1;	
            	regs0->mc_mbwidth = (w+15)>>4;                                     // 1024 mc
            	set_framebuf_mb_mode_width((w+15)>>4);                             // 1024 source buffer
            	SetVPPBufferHorizontalStride(w);                         // 1024 display
            }
			#else
			regs0->mc_mbwidth = 64;                                     // 1024 mc
        	set_framebuf_mb_mode_width(64);                             // 1024 source buffer
        	SetVPPBufferHorizontalStride(1024);                         // 1024 display
        	#endif
			  
            #ifdef TURBO_DECODE      
            flddec_init(1, MBLINE_W1024);
            #endif
        }        
        else
        {
            regs0->mc_mbwidth = 45;                                     // 720 mc
            set_framebuf_mb_mode_width(45);                             // 720 source buffer
            SetVPPBufferHorizontalStride(720);                          // 720 display        

            #ifdef TURBO_DECODE      
            if(cd_type_loaded == CDDVD)
            {   //kevinmonkey 050427 ultilize fs buffer as extra bidir frame buffer
                regs0->bidir_chroma    = P_BIDIR_CHROMA + EXTRA_BIRDIR_LUMA_SIZE;
                regs0->vppbidir_chroma = P_BIDIR_CHROMA + EXTRA_BIRDIR_LUMA_SIZE;
                flddec_init(1, EXTRA_P_MBLINE_W720);
            }
            else
            {
                flddec_init(1, P_MBLINE_W720);
            }
            #endif            
        }       

        #ifdef TURBO_DECODE      
        setup_vpp_mapping(2,0);
        #else
        setup_vpp_mapping(1,0);        
        #endif
        
#ifdef  MEMCFG_MOVE_OSDSUP
        osdya_n                 = P_OSDYA;
        supya_n                 = P_SUPYA;
#endif
    }
    break;
    }

#ifdef  MONE_CONFIG
    if (config==MEMORY_DVD_PAL) io_write_wait("PAL\n");
    else io_write_wait("OTHER\n");
#endif

#ifdef  MB22
    mb22_en = (config==MEMORY_DVD_PAL);    
#else
    mb22_en = 0;
#endif

#ifdef  DTH_CFG_ENABLE
    if (config==MEMORY_DVD_PAL) {
        config_mc_compression(1);
        set_dis_pic_size(720,576);  // force setting display mode
    } else {
        config_mc_compression(0);
    }
#else
    config_mc_compression(0);
#endif

#ifdef  MONE_CONFIG
    if (regs0->mc_compress) memcfg_printf("HAS compressed\n");
    else memcfg_printf("NOT compressed\n");
#endif

    /*
    ** config L-mem and also move video-bitstream buffer
    */
#define RESTORE_EVB()   memcpyS((void *)(SDRAM_BASE+regs0->evbya*1024), (void *)(SDRAM_BASE+evbya_old*1024),EVBSZ*1024)
#define MOVE_OSD()      memcpyS((void *)(SDRAM_BASE+osdya_n*1024), (void *)(SDRAM_BASE+REG_OSDYA*1024), OSDSIZE*1024)
#define MOVE_SUP()      memcpyS((void *)(SDRAM_BASE+supya_n*1024), (void *)(SDRAM_BASE+regs0->supya*1024), SUPSIZE*1024)

#ifdef  MEMCFG_PAL_LMEM
    // only use Lmem for PAL D1 mode
    if (config==MEMORY_DVD_PAL)
    {
        config_Lmem(1);

    #ifdef MOVE_PAL_AUDYA   // 2005/01/24 yltseng
        if( memory_config_saved != MEMORY_DVD_PAL )
            AUDIF_Reset_DSP();
    #endif               
        RESTORE_EVB();
        
    #ifdef  MEMCFG_MOVE_OSDSUP
        MOVE_OSD();
        MOVE_SUP();
    #endif
        ModifyFsBufAddr();
    }
    else
    {
        RESTORE_EVB();
    #ifdef  MEMCFG_MOVE_OSDSUP
        MOVE_OSD();
        MOVE_SUP();
    #endif
        ModifyFsBufAddr();

    #ifdef MOVE_PAL_AUDYA   // 2005/01/24 yltseng
        if( memory_config_saved == MEMORY_DVD_PAL )
            AUDIF_Reset_DSP();
    #endif
        config_Lmem(0);
    }

#else
    #define RESTORE_EVBX()   memcpyS((void *)(SDRAM_BASE+regs0->evbya*1024), (void *)(SDRAM_BASE+evbya_old*1024),P_EVBSZ*1024)

    if (avd_is_midi() ) { //Jeff 20031028
        if (regs0->evbya!=evbya_old) RESTORE_EVBX();
    }
    config_Lmem(0);
#endif
    
#ifdef TURBO_DECODE  //kevinmonkey 050405 Nav buffer position differs when DVD and File play 
    ModifyNavBufAddr(config);
#else
    ModifyNavBufAddr();
#endif

    //OSD Display Buffer pointer
#ifdef SPHE1000_DISABLE_ROMCODEOSD       //wjzhang  turn off romcode osd and display  lx4189 
    static int osd_memcfg_flag=0;
    //when boot and this function first called, memory addr is the same with PROMBASE, cause some bug.
    //so, add the static flag to avoid.    kehw
    if(osd_memcfg_flag)	
    {
    	REG_OSDYA                   = 0x00480000>>10;//osdya_n;
    	REG_OSDYA2                  = 0x00480000>>10;//osdya_n;
        BackUpOSDAddress(0x00480000>>10);
    }
    else
#endif		
    {
#ifdef SPHE1000_DISABLE_ROMCODEOSD
    	osd_memcfg_flag=1;
#endif
    
#ifdef SUPPORT_16BIT_OSD
        if(OSD_buffer_16bit ==1)
        {
            REG_OSDYA                   = GP_REF1_LUMA + 64;
            REG_OSDYA2                  = GP_REF1_LUMA + 64;//osdya_n;
            BackUpOSDAddress(GP_REF1_LUMA + 64);
        }
        else
        {
            REG_OSDYA                   = osdya_n;
            REG_OSDYA2                  = osdya_n;
            BackUpOSDAddress(osdya_n);
        }
#else
        REG_OSDYA                   = osdya_n;
        REG_OSDYA2                  = osdya_n;
        BackUpOSDAddress(osdya_n);
#endif
    }
    
    //Sub-picture bitstream Buffer pointer
#if defined(SDRAM_16Mb_Mode) && defined(TURBO_DECODE) && defined(AVI_INTERNAL_SUP)
//kevinmonkey 050502 under 16Mb with turbo decode, AVI subpic memory is specially defined
    if(GetCurrentFileType() == CDROM_MP4)
    {
        regs0->sup_buffer_limit     = INTERN_SUPSIZE*1024;
        regs0->supya                = INTERN_SUPYA;
        regs0->supya_limit          = INTERN_SUPSIZE;  
        set_sup_hwbuf(INTERN_SUPYA, INTERN_SUPYA+INTERN_SUPSIZE);
    }
    else    //32m, or 16m no turbo decode, or doesn't support internal subpicture
    {
        regs0->sup_buffer_limit     = SUPSIZE*1024;
        regs0->supya                = supya_n;
        regs0->supya_limit          = SUPSIZE;  
        set_sup_hwbuf(supya_n, supya_n+SUPSIZE);
    }
#else   //!AVI_INTERNAL_SUP
    regs0->sup_buffer_limit     = SUPSIZE*1024;
    regs0->supya                = supya_n;
    regs0->supya_limit          = SUPSIZE;  
    set_sup_hwbuf(supya_n, supya_n+SUPSIZE);
#endif  //#if defined(SDRAM_16Mb_Mode) && defined(TURBO_DECODE) && defined(AVI_INTERNAL_SUP)
    
    regs0->supya2               = A_SUPYA2;
    regs0->supya2_limit         = SUPSIZE2;
    
#ifdef TWO_SUBTITLE //terry,2004/7/28 01:49PM
    set_sup_hwbuf2(A_SUPYA2, A_SUPYA2+SUPSIZE2);
#endif

    SetupOtherBufferPointer();

    // clearup framebuf status
    vpp_reset_framebuf_state();

    // clearup memory
    if (blue)
    {
        clrFrameBuffer(FRAME_REF0|FRAME_REF1|FRAME_BIDIR|FRAME_FILL_BLUE);
    }
    else
    {
        clrFrameBuffer(FRAME_REF0|FRAME_REF1);        
    }

// kevinmonkey 050324, roll back this modification since this 
// invokes another problem (video in left-top corner and other place is trash)
// 2004/07/02 yltseng, for PAL/NTSC switch
#if 0
#if defined( SDRAM_16Mb_Mode ) && defined( SUPPORT_FILE_SYSTEM_MODE )
    if( pFsJpeg->gifsFuncBtn == FS_FUNC_OTHER )
        resync_video_bitstream();
#endif
#endif

    // re-enable video
    enable_video();

    // re-enable it
    setup_clock_gating(1);
#ifdef SDRAM_16Mb_Mode//terry,2003/10/21 10:03AM        
    regs0->osd_en = osd_enable;//terry,2003/10/20 03:24PM
#endif

    // 2004/06/12 yltseng move here
    memory_config_saved = configX;
    memory_config_w_saved = w;
    memory_config_h_saved = h;
}

// check decoding limits
int check_video_size(int width, int height)
{  
	 

#if defined(HW_SUPPORT_WIDTH_OVER_720)
	#if defined(IC_8202L)
		#define VIDEO_WIDTH_MAX	    896
    	#define VIDEO_HEIGHT_MAX	1024
    #endif
#else
    #define VIDEO_WIDTH_MAX	    720
    #define VIDEO_HEIGHT_MAX	576
#endif

    // minimum size
    #define VIDEO_WIDTH_MIN	    64
    #define VIDEO_HEIGHT_MIN	32
   
	if (width>VIDEO_WIDTH_MAX || height>VIDEO_HEIGHT_MAX)
	{
           seq_info.horizontal_size_value = width;
           seq_info.vertical_size_value = height;
        #ifdef  MONE_ERROR
            mpg_printf("seq: over-size (%dx%d)\n", width, height);
        #endif

		return 0;
	}

#ifdef  KERNEL_KILL_SMALL_PIC
	if (width<VIDEO_WIDTH_MIN || height<VIDEO_HEIGHT_MIN)
	{
           seq_info.horizontal_size_value = width;
           seq_info.vertical_size_value = height;
        #ifdef  MONE_ERROR
            mpg_printf("seq: small-size (%dx%d)\n", width, height);
        #endif
		return 0;
	}    
#endif	
	
	return 1;
}

//
//
//
#ifdef DVD_SERVO

#include "sinf.h"
UINT8 ServoDVDUserArea[200]; //extent to support DVD multi-session, Jeff 20031208

// 2005/08/09 yltseng
// for DVD, track buffer size must be multiple of 43316( ECC block size )
#define CountDVDServoTrackBufferSize( size )    ( 16 * ( ( (unsigned) size * 1024 ) / 43316 ) )
#define CountCDServoTrackBufferSize( size )     ( ( ( size * 1024 ) / 2496 ) - 1 )

//2006-08-14,mimitsai add
#define IS_OKO_DISC() ((cd_type_loaded == CDSVCD)&&(bDiscType == CD_OKO))

void
config_servo_buffer(void)
{
    unsigned tbya, size;
    extern  UINT8   DiscType;

    #ifdef SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG
    BYTE* old_user_table_address;
    #endif  //#ifdef SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG
    //2006-08-14,mimitsai modify, it need iso9660 data when playing oko disc, so reduce the servo buffer avoiding distory the iso9660 data.
    if( (cd_type_loaded == CDROM) || (cd_type_loaded == CDUNKNOWN) || IS_OKO_DISC())
    {
        //mp3/jpeg/file play
        #ifdef ARCHT16_USE_64M_ESP//shenyj add for alco 2006/02/28
        size = 4096;
        tbya = 4096;
        #else//#ifdef ARCHT16_USE_64M_ESP//shenyj add for alco 2006/02/28
            #ifdef MP3_PLAY_LONG_ESP      //Gordon 20030718
                if (Is_JPEG_STATE()) 
                    size = JPEG_SERVO_SIZE;
                else if(Is_MP3_STATE())
                    size = JPEG_SERVO_SIZE+GP_LUMA_SIZE+GP_CHROMA_SIZE;
                else 
            #endif  
            size = JPEG_SERVO_SIZE;
        	tbya = A_JPEG_SERVO_YA;     // DVD servo track-buffer pointer
        #endif//#ifdef ARCHT16_USE_64M_ESP//shenyj add for alco 2006/02/28
    
        if (DiscType == CDDVD) {
            servo_max_buffer = CountDVDServoTrackBufferSize( size );    // 2005/08/09 yltseng
        } else {
            servo_max_buffer = CountCDServoTrackBufferSize( size );
        }
    }
    else
    {
        #if defined(USE_32M_BUF_IN_64M_SDRAM_AS_ESP_BUF	)||defined(USE_48M_BUF_IN_64M_SDRAM_AS_ESP_BUF	)//we use the 64M sdram's end of 32M memory as ESP USE...
        #ifdef MINUS_VR_AUTH_PLAYBACK
        if(bDVDminusVR)
        	tbya = A_DVD_SERVO_YA_4096 + VR_SDRAM_BUF_SIZE;
        else
        #endif
        tbya = A_DVD_SERVO_YA_4096;					//define it must use 64M sdram...linrc 2005-11-18 17:10
        #elif  defined(ARCHT16_USE_64M_ESP)//shenyj add for alco 2006/02/28
        tbya = 4096  ;
        size = 4096;
        #else
        tbya = A_DVD_SERVO_YA;      // DVD servo track-buffer pointer     
        #endif
    #ifdef DVD_AUDIO
        size = dAMG_LSN ? DVDA_SERVO_SIZE : DVDV_SERVO_SIZE;
    #else
        #if defined(USE_32M_BUF_IN_64M_SDRAM_AS_ESP_BUF	)||defined(USE_48M_BUF_IN_64M_SDRAM_AS_ESP_BUF	)//linrc 2005-11-18 17:10
        #ifdef MINUS_VR_AUTH_PLAYBACK
        if(bDVDminusVR)
        	size = DVDV_SERVO_SIZE_4096 - VR_SDRAM_BUF_SIZE;
        else
        #endif
        size = DVDV_SERVO_SIZE_4096;
        #else
        size = DVDV_SERVO_SIZE;
        #endif
    #endif
        servo_max_buffer = CountDVDServoTrackBufferSize( size );        // 2005/08/09 yltseng
    }

    #if defined(PORTABLE_DVD)||defined(ALCO_PORTABLE_DVD_8202D_DVB)
    extern int is_iop_call_back(unsigned *,unsigned *,BYTE);//jhuang 2003/12/3
    is_iop_call_back(&tbya,&size,0);
    #elif defined(DESKTOP_ESP) //wthsin,2005/3/3 11:18am
        extern int DesrkTop_ESP_is_iop_call_back(unsigned *,unsigned *,BYTE);//jhuang 2003/12/3
        DesrkTop_ESP_is_iop_call_back(&tbya,&size,0);
    #endif

    #ifdef SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG
    old_user_table_address = pServoUserInfo;
    #endif  //#ifdef SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG

    if (is_svo_dvd())
    {
        pServoUserInfo = ServoDVDUserArea;
    }
    else
    {
        // cd
        pServoUserInfo = (UINT8 *)(SDRAM_BASE_CACHED + (tbya)*1024);
        tbya+=1;
    }

    #ifdef SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG
    if((old_user_table_address!=pServoUserInfo)&&(old_user_table_address != NULL))
    {
        if (!is_svo_dvd())
            memcpy(pServoUserInfo,old_user_table_address,2<<10);
    }
    #endif  //#ifdef SERVOBUF_COPY_USERTABLE_WHEN_RECONFIG

    pTrackBuf = (UINT8 *) (SDRAM_BASE_UNCACHED + (tbya)*1024);  
      
    regs0->rf_sdramif_tbya  = tbya;                 // SERVO track buffer
    SetHostDMAReadBuffer(tbya,size-1);

    #ifdef  MONE_CONFIG
    memcfg_printf("config_servo_buffer()\n");
    memcfg_printf("tbya $%x cdrya $%x cdrya_limit $%x\n", tbya, tbya, size-1);
    memcfg_printf("servo_max_buffer %d\n", servo_max_buffer);
    #endif
}
#endif


#ifdef MODIFY_OSD_SHOW_NEW_STYLE_WINDOW
/*
 *Function Description:
 *    to get the config mode is PAl or NTSC
 *
 *   zhaoyanhua add 2003-12-18 10:38
 */
/*
BYTE GetConfigMode(int config)
{
    BYTE mode = 0;
    
    switch(config)
    {
        case MEMORY_GRAPH_NTSC:
        case MEMORY_DVD_NTSC :
        case MEMORY_SVCD_NTSC:
        case MEMORY_CVD_NTSC:
        case MEMORY_VCD_NTSC:
            mode = MODE_NTSC;
            break;
        case MEMORY_GRAPH_PAL:
        case MEMORY_PREVIEW:
        case MEMORY_DVD_PAL:
        case MEMORY_SVCD_PAL:
        case MEMORY_CVD_PAL:
        case MEMORY_VCD_PAL:
        case MEMORY_DVD_AUDIO:
        default:
            mode = MODE_PAL;
    }
    return mode;

}
#endif
*/

BYTE GetConfigMode(int config)   //terry edit   fengjl upload it 3-12-24 12:59
{
     BYTE mode = 0;

     //if(tv_format!=MODE_AUTO)
     {
       if(getVPP_TVsystem()==1) mode = MODE_PAL;
       else mode = MODE_NTSC;
     }
     /*
     else
     {
       switch(config)
       {
          case MEMORY_GRAPH_NTSC:
          case MEMORY_DVD_NTSC :
          case MEMORY_SVCD_NTSC:
          case MEMORY_CVD_NTSC:
          case MEMORY_VCD_NTSC:
               mode = MODE_NTSC;
               break;          
          default:
               if(getVPP_TVsystem()==1) mode = MODE_PAL;
               else mode = MODE_NTSC;
       }
     }*/

     return mode;

}
#endif



