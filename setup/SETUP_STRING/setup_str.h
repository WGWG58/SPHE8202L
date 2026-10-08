#ifndef _SETUP_STR_H_
#define _SETUP_STR_H_

#include "user_init.h"

    #ifdef SETUP_EXTENSION_TABLE

typedef enum
{

#ifdef SUPPORT_TVG
    STR_OS_TV_GUARDIAN,
    STR_OS_TVG_MODE,
    STR_OS_HELL_DAMM,
    STR_OS_RELIGIOUS,
    STR_OS_SEXUAL,
    STR_OS_CC_MODE,
    STR_OS_TVG_CHANNEL,
    STR_OS_ON_EX,
    STR_OS_OFF_EX,
    STR_OS_TOLERANT,
    STR_OS_MODERATE,
    STR_OS_STRICT,
    STR_OS_CC_OFF,
    STR_OS_ON_MUTE,
    STR_OS_CC_CONTINUOUS,
    STR_OS_CC1,
    STR_OS_CC2,
    STR_OS_TVG_HELP,
#endif

} ENUM_OSD_STRING_ID;

static inline const UINT8* GetOSDString( UINT8 uiFont, ENUM_OSD_STRING_ID enID )
{
    extern const unsigned char** g_aSetupFont[];
    return g_aSetupFont[ uiFont ][ enID ];
}

    #endif
#endif
