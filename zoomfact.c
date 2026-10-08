
#include "config.h"
#include "types.h"
#include "vpp.h"

//
//
//
#if 0
#define SCALE2  1.5
#define SCALE3  2
#define SCALE4  3
#define SCALE5  4
#define SCALE6  (1/1.25)
#define SCALE7  (1/1.75)
#define SCALE8  (1/2)
#endif

#ifdef TWELVE_ZOOMFACTORS//axel2004/5/3 12:35pm
#define SCALE2    1.2
#define SCALE3    1.3
#define SCALE4    1.5
#define SCALE5    1.7
#define SCALE6    2.0
#define SCALE7    2.2
#define SCALE8    2.6
#define SCALE9    3
#define SCALE10  (1/1.25)
#define SCALE11  (1/1.75)
#define SCALE12  (1/2.00)
#elif defined (HW_SUPPORT_TURBO_DECODE)       // 2005/04/01 yltseng
#define SCALE2  1.5
#define SCALE3  2
#define SCALE4  2.5
#define SCALE5  3
#define SCALE6  (1/1.15)
#define SCALE7  (1/1.25)
#define SCALE8  (1/1.45)
#else
#define SCALE2  1.5
#define SCALE3  2
#define SCALE4  2.5
#define SCALE5  3
#define SCALE6  (1/1.25)
#define SCALE7  (1/1.75)
#define SCALE8  (1/2.00)
#endif


const   UINT8   zoom_scales = VPP_ZOOM_MAX+1;

#ifdef TWELVE_ZOOMFACTORS//axel2004/5/3 12:35pm


const   UINT16  zoom_scale_w[VPP_ZOOM_MAX+1] =
{
    // 1    // 4/3(ps)  
    1024,   (1024*4)/3, 1024*SCALE2, 1024*SCALE3, 1024*SCALE4, 1024*SCALE5, 1024*SCALE6 , 1024*SCALE7, 1024*SCALE8, 1024*SCALE9, 1024*SCALE10 , 1024*SCALE11, 1024*SCALE12
};

const   UINT16  zoom_scale_h[VPP_ZOOM_MAX+1] =
{
    1024,   (1024*4)/3, 1024*SCALE2, 1024*SCALE3, 1024*SCALE4, 1024*SCALE5, 1024*SCALE6 , 1024*SCALE7, 1024*SCALE8, 1024*SCALE9, 1024*SCALE10 , 1024*SCALE11, 1024*SCALE12
};

#else

const   UINT16  zoom_scale_w[VPP_ZOOM_MAX+1] =
{
    // 1    // 4/3(ps)  
    1024,   (1024*4)/3, 1024*SCALE2, 1024*SCALE3, 1024*SCALE4, 1024*SCALE5, 1024*SCALE6 , 1024*SCALE7, 1024*SCALE8
};

const   UINT16  zoom_scale_h[VPP_ZOOM_MAX+1] =
{
    1024,   (1024*4)/3, 1024*SCALE2, 1024*SCALE3, 1024*SCALE4, 1024*SCALE5, 1024*SCALE6 , 1024*SCALE7, 1024*SCALE8
};
#endif

