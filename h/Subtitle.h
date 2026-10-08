#ifdef SUPPORT_MP4_SUBTITLE

    #ifndef _SUBTITLE_H_
    #define _SUBTITLE_H_

#include "types.h"

enum EXT_SUP_TYPE
{
    EXT_SUBTITLE_UNKNOWN    = 99,
    EXT_SUBTITLE_TXT        = 0,
    EXT_SUBTITLE_IMG,
};

extern void     ACTIVATE_EXT_SUP();
extern void     DISPLAY_EXT_SUP();
extern void     DEACTIVATE_EXT_SUP();
extern void     TURNOFF_EXT_SUP();

extern int      IS_EXT_SUP_INITIALIZED();
extern int      IS_EXT_SUP_ACTIVATED();
extern int      IS_EXT_SUP_INDISPLAY();
extern int      IS_EXT_SUP_NEEDDATA();

extern void     supResetSubtitleFileInfo();
extern void     supResetSubtitleMatchBuffer();
extern void     supAddVideoFileInfo( UINT32, UINT32, const char* );
extern int      supAddSubtitleFileInfo( UINT32, UINT32, const char* );

extern int      supFillSubtitleBuffer();
extern void     supRunSubtitleMatch();

extern int      supInitSubtitle();
extern int      supSetSubtitleStream( UINT32 uiStream );
extern void 	supClearSubtitle();//liumzh 20041204
extern void     supOpenSubtitle();//caoh 2005-7-18 20:41

extern int      (*g_pfnPollingSubtitle)();

    #endif  // _SUBTITLE_H_

#endif  // SUPPORT_MP4_SUBTITLE
