#ifdef PMP_DVD
//===========================================================================
// for PMP, Support up to 1024x592
//===========================================================================
//Highest horizontal resolution (1024) that 8202D could support
//now we use original 3 720x576 as two frame buffer, so we got 
//1024x592 resolution, and need one more 1024x592 frame buffer
#define MAX_VIDEO_HORIZONTAL_RESOLUTION         (1024)
#define MAX_VIDEO_VERTICAL_RESOLUTION           (592)

#define	HD_LUMA_SIZE            ((MAX_VIDEO_PIXEL*MAX_VIDEO_LINE)>>10)
#define	HD_CHROMA_SIZE          ((HD_LUMA_SIZE+1)/2)

#define	HD_REF0_LUMA            (VFBMA + 0)  //ultilize original frame buffer
#define	HD_REF0_LUMA_END        (HD_REF0_LUMA + HD_LUMA_SIZE - 1)
#define	HD_REF0_CHROMA          (HD_REF0_LUMA_END + 1)
#define	HD_REF0_CHROMA_END      (HD_REF0_CHROMA + HD_CHROMA_SIZE - 1)

#define	HD_REF1_LUMA            (HD_REF0_CHROMA_END + 1)
#define	HD_REF1_LUMA_END        (HD_REF1_LUMA + HD_LUMA_SIZE - 1)
#define HD_REF1_CHROMA          (HD_REF1_LUMA_END + 1)
#define	HD_REF1_CHROMA_END      (HD_REF1_CHROMA + HD_CHROMA_SIZE - 1)

#define HD_BIDIR_LUMA           (4096) //<- may need to change this
#define HD_BIDIR_LUMA_END       (HD_BIDIR_LUMA+HD_LUMA_SIZE-1)
#define HD_BIDIR_CHROMA         (HD_BIDIR_LUMA_END+1)
#define HD_BIDIR_CHROMA_END     (HD_BIDIR_CHROMA + HD_CHROMA_SIZE-1)


#ifdef MVC_BUF_SIZE
    #if (MVC_BUF_SIZE < ((((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*64 + (((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*(MAX_VIDEO_VERTICAL_RESOLUTION/16)+1)/2)*32) + 1023)/1024))
        #error "Insufficient MVC buffer size. Please check MVC buffer size."
    #endif
#else   //assign mvc buffer.
    #ifdef MVC_BUF_YA
    #undef MVC_BUF_YA
    #endif
#define MVC_BUF_YA              (HD_BIDIR_CHROMA_END + 1)
#define MVC_BUF_SIZE            ((((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*64 + (((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*(MAX_VIDEO_VERTICAL_RESOLUTION/16)+1)/2)*32) + 1023)/1024)
#endif  //#ifdef MVC_BUF_SIZE

#ifndef HD_MVC_BUF_YA
#define HD_MVC_BUF_YA       (MVC_BUF_YA)
#endif  //
#ifndef HD_MVC_BUF_SIZE
#define HD_MVC_BUF_SIZE     (MVC_BUF_SIZE)
#endif  //

#ifndef HD_SUPYA
#define HD_SUPYA            (A_SUPYA)
#endif  //

#ifndef HD_EVBYA
#define HD_EVBYA            (P_EVBYA)
#endif  //

#ifndef HD_EVBYA_SIZE
#define HD_EVBYA_SIZE       (P_EVBSZ)
#endif  //

#else   //!PMP_DVD, ordinary setting, using memory from 4096 above
//===========================================================================
// If you have 64Mbits SDRAM and IC that supports 1024x1024, try this
//===========================================================================
//Highest resolution 1024x1024.
#ifndef MAX_VIDEO_HORIZONTAL_RESOLUTION
#define MAX_VIDEO_HORIZONTAL_RESOLUTION         (1024)
#endif  //highest horizontal resolution supported
#ifndef MAX_VIDEO_VERTICAL_RESOLUTION
#define MAX_VIDEO_VERTICAL_RESOLUTION           (1024)
#endif  //highest vertical resolution supported

#define	HD_LUMA_SIZE            ((MAX_VIDEO_HORIZONTAL_RESOLUTION*MAX_VIDEO_VERTICAL_RESOLUTION)>>10)
#define	HD_CHROMA_SIZE          ((HD_LUMA_SIZE+1)/2)

#ifndef HD_FRAME_BUFFER_START   
#define HD_FRAME_BUFFER_START   (4096) //if not assigned, try lower 32M
#endif  //frame buffer start address
#ifndef HD_REF0_LUMA
#define HD_REF0_LUMA            (HD_FRAME_BUFFER_START)
#endif  //
#ifndef HD_REF0_LUMA_END
#define	HD_REF0_LUMA_END        (HD_REF0_LUMA + HD_LUMA_SIZE - 1)
#endif  //
#ifndef HD_REF0_CHROMA
#define	HD_REF0_CHROMA          (HD_REF0_LUMA_END + 1)
#endif  //
#ifndef HD_REF0_CHROMA_END
#define	HD_REF0_CHROMA_END      (HD_REF0_CHROMA + HD_CHROMA_SIZE - 1)
#endif  //

#ifndef HD_REF1_LUMA
#define	HD_REF1_LUMA            (HD_REF0_CHROMA_END + 1)
#endif  //
#ifndef HD_REF1_LUMA_END
#define	HD_REF1_LUMA_END        (HD_REF1_LUMA + HD_LUMA_SIZE - 1)
#endif  //
#ifndef HD_REF1_CHROMA
#define HD_REF1_CHROMA          (HD_REF1_LUMA_END + 1)
#endif  //
#ifndef HD_REF1_CHROMA_END
#define	HD_REF1_CHROMA_END      (HD_REF1_CHROMA + HD_CHROMA_SIZE - 1)
#endif  //

#ifndef HD_BIDIR_LUMA
#define HD_BIDIR_LUMA           (HD_REF1_CHROMA_END+1)
#endif  //
#ifndef HD_BIDIR_LUMA_END
#define HD_BIDIR_LUMA_END       (HD_BIDIR_LUMA+HD_LUMA_SIZE-1)
#endif  //
#ifndef HD_BIDIR_CHROMA
#define HD_BIDIR_CHROMA         (HD_BIDIR_LUMA_END+1)
#endif  //
#ifndef HD_BIDIR_CHROMA_END
#define HD_BIDIR_CHROMA_END     (HD_BIDIR_CHROMA + HD_CHROMA_SIZE-1)
#endif  //

#ifndef HD_MVC_BUF_YA
#define HD_MVC_BUF_YA           (HD_BIDIR_CHROMA_END + 1)
#endif  //
#ifndef HD_MVC_BUF_SIZE
#define HD_MVC_BUF_SIZE         ((((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*64 + (((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*(MAX_VIDEO_VERTICAL_RESOLUTION/16)+1)/2)*32) + 1023)/1024)
#endif  //

#if (HD_MVC_BUF_SIZE < (((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*64 + (((MAX_VIDEO_HORIZONTAL_RESOLUTION/16)*(MAX_VIDEO_VERTICAL_RESOLUTION/16)+1)/2)*32) + 1023)/1024)
        #error "Insufficient MVC buffer size. Please check MVC buffer size."
#endif

#endif  //configuration switch#ifdef PMP_DVD
