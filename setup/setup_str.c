#include "user_init.h"

#ifdef SETUP_EXTENSION_TABLE

#include "SETUP_STRING/setup_str_english.inc"
#include "SETUP_STRING/setup_str_schinese.inc"
#include "SETUP_STRING/setup_str_tchinese.inc"
#include "SETUP_STRING/setup_str_german.inc"
#include "SETUP_STRING/setup_str_spanish.inc"
#include "SETUP_STRING/setup_str_french.inc"
#include "SETUP_STRING/setup_str_portuguese.inc"
#include "SETUP_STRING/setup_str_latin.inc"
#include "SETUP_STRING/setup_str_italian.inc"
#include "SETUP_STRING/setup_str_japanese.inc"
#include "SETUP_STRING/setup_str_russian.inc"
#include "SETUP_STRING/setup_str_romanian.inc"
#include "SETUP_STRING/setup_str_turkish.inc"
#include "SETUP_STRING/setup_str_dutch.inc"
#include "SETUP_STRING/setup_str_swedish.inc"
#include "SETUP_STRING/setup_str_czech.inc"
#include "SETUP_STRING/setup_str_thai.inc"

const unsigned char** g_aSetupFont[] = 
{
#ifdef USE_ENGLISH_OSD
    g_aSetupFont_English,
#endif

#ifdef USE_SCHINESE_OSD
    g_aSetupFont_SChinese,
#endif

#ifdef USE_TCHINESE_OSD
    g_aSetupFont_TChinese,
#endif

#ifdef USE_GERMAN_OSD
    g_aSetupFont_German,
#endif

#ifdef USE_SPANISH_OSD
    g_aSetupFont_Spanish,
#endif

#ifdef USE_FRENCH_OSD
    g_aSetupFont_French,
#endif

#ifdef USE_PORTUGUESE_OSD
    g_aSetupFont_Portuguese,
#endif

#ifdef USE_LATIN_OSD
    g_aSetupFont_Latin,
#endif

#ifdef USE_ITALIAN_OSD
    g_aSetupFont_Italian,
#endif

#ifdef USE_JAPANESE_OSD
    g_aSetupFont_Japanese,
#endif

#ifdef USE_RUSSIAN_OSD
    g_aSetupFont_Russian,
#endif

#ifdef USE_ROMANIAN_OSD
    g_aSetupFont_Romanian,
#endif

#ifdef USE_TURKISH_OSD
    g_aSetupFont_Turkish,
#endif

#ifdef USE_DUTCH_OSD
    g_aSetupFont_Dutch,
#endif

#ifdef USE_SWEDISH_OSD
    g_aSetupFont_Swedish,
#endif

#ifdef USE_CZECH_OSD
    g_aSetupFont_Czech,
#endif

#ifdef USE_THAI_OSD
    g_aSetupFont_Thai,
#endif
};

#endif

