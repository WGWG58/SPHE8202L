/*****************************************************************
-- linrc creat this file,move from fs9660_util.c 2005-11-29 16:25
******************************************************************/
#include "user_init.h"
#include "global.h"
#include "fs96602.h"
#include "fsNAV.h"


const FILE_EXT_INFO_TABLE g_aFileExtInfoTable[] =//terry,2004/4/23 07:45PM
{
#ifdef	SUPPORT_ASF
    { "ASF",    CDROM_MP4,  FS_FUNC_OTHER },
#ifdef	SUPPORT_AUD_WMA
    #ifdef AUDIO_EXTENSION_USE_MP3_LIST //chenzhao on 2006-10-9 13:33 .
    { "WMA",    CDROM_MP4,  FS_FUNC_MP3 },
    #else
    { "WMA",    CDROM_MP4,  FS_FUNC_OTHER },
    #endif
    { "WMV",    CDROM_MP4,  FS_FUNC_OTHER },
#endif
#elif defined(SUPPORT_WMA)
    { "WMA",    CDROM_WMA,  FS_FUNC_MP3 },
    { "ASF",    CDROM_WMA,  FS_FUNC_MP3 },
    { "WMV",    CDROM_WMA,  FS_FUNC_MP3 },
#endif	// SUPPORT_ASF

#ifndef WITHOUT_SUPPORT_MP3
    { "MP3",    CDROM,      FS_FUNC_MP3 },
#endif

#ifdef SUPPORT_AAC
    { "AAC",	CDROM_AAC,	FS_FUNC_MP3	},
#endif

#ifdef SUPPORT_OGG
    #ifdef AUDIO_EXTENSION_USE_MP3_LIST //chenzhao on 2006-10-9 13:33 .
    { "OGG",    CDROM_MP4,  FS_FUNC_MP3 },
    #else
    { "OGG",    CDROM_MP4,  FS_FUNC_OTHER },
    #endif    
#endif    

#ifdef SUPPORT_GIF
    { "GIF",    CDROM_GIF,  FS_FUNC_JPEG },
#endif

#ifdef SUPPORT_BMP
    { "BMP",    CDROM_BMP,  FS_FUNC_JPEG },
#endif

    //joshua, 2004/10/15, cd_subtype should be CDROM_JPEG.
    //{ "JPG",    CDJPEG,     FS_FUNC_JPEG },
    { "JPG",    CDROM_JPEG,     FS_FUNC_JPEG },
    #ifdef SUPPORT_FS_LONGNAME  //hongfeng 2006/3/31 17:19
    { "JPEG",    CDROM_JPEG,     FS_FUNC_JPEG },
    #endif

#ifdef PLAY_JPE_JPEG_FILE
    { "JPE",    CDJPEG,     FS_FUNC_JPEG },
    //{ "JPG",    CDROM_JPEG,     FS_FUNC_JPEG },
#endif

#ifdef  SUPPORT_FILE_SYSTEM_MODE

    #ifdef	SUPPORT_MPG_FILE_PARSER//axelchen 2005/9/6, 2005/09/28 yltseng
    { "DAT",    CDROM_MP4,  FS_FUNC_OTHER },
    { "MPG",    CDROM_MP4,  FS_FUNC_OTHER },
    { "MPEG",   CDROM_MP4,  FS_FUNC_OTHER }, 
    { "MPA",    CDROM_MP4,  FS_FUNC_OTHER },
    { "MPE",    CDROM_MP4,  FS_FUNC_OTHER },
    #else// SUPPORT_MPG_FILE_PARSER
    { "DAT",    CDROM_MPG,  FS_FUNC_OTHER },
    { "MPG",    CDROM_MPG,  FS_FUNC_OTHER },
    { "MPEG",   CDROM_MPG,  FS_FUNC_OTHER },//nono add.20050825 for Now player can't parse *.mpeg files.    
    { "MPA",    CDROM_MPG,  FS_FUNC_OTHER },
    { "MPE",    CDROM_MPG,  FS_FUNC_OTHER },
    #endif	// SUPPORT_MPG_FILE_PARSER

    { "VOB",    CDROM_MPG,  FS_FUNC_OTHER },

    #ifdef SUPPORT_MP4
    #ifdef TELL_FROM_MP4_EXT_NAME   //Maoyong 2004.06.25
    { "AVI",    CDROM_AVI,  FS_FUNC_OTHER },
    { "MP4",    CDROM_MP4,  FS_FUNC_OTHER },
    #else
    { "AVI",    CDROM_MP4,  FS_FUNC_OTHER },
    { "MP4",    CDROM_MP4,  FS_FUNC_OTHER },
    #endif //#ifdef TELL_FROM_MP4_EXT_NAME

    { "VID",    CDROM_MP4,  FS_FUNC_OTHER },

    #if defined( SUPPORT_JOLIET_FORMAT ) || defined( SUPPORT_FONT_UTIL )    // 2005/02/16 yltseng
    { "DIVX",   CDROM_DIV,  FS_FUNC_OTHER },
    { "DIV",   CDROM_DIV,  FS_FUNC_OTHER },//????
    #else
    { "DIV",     CDROM_DIV,  FS_FUNC_OTHER },
    #endif  //#if defined( SUPPORT_JOLIET_FORMAT ) || defined( SUPPORT_FONT_UTIL )
    
#ifdef SUPPORT_QUICKTIME
    { "MP4",	CDROM_MP4, FS_FUNC_OTHER },	// stanleyc - to support ISO QuickTime MP4 format
    { "MOV",	CDROM_MP4, FS_FUNC_OTHER },	// stanleyc - to support QuickTime format with MP4
    { "3GP",	CDROM_MP4, FS_FUNC_OTHER },	// stanleyc
    { "M4A",	CDROM_M4A,	FS_FUNC_OTHER	},
#endif // #ifdef SUPPORT_QUICKTIME
	
    #endif  //#ifdef SUPPORT_MP4
#endif

#ifdef MP3_TXT_DISPLAY
    { "LRC",    CDMP3LRC,   FS_FUNC_OTHER },
#endif

#ifdef  SUPPORT_MIDI
    { "MID",    CDMIDI,     FS_FUNC_MIDI },
#endif

#ifdef  SUPPORT_WAV 
    { "WAV",    CDROM_WAV,     FS_FUNC_MP3 },
#endif

#ifdef SUPPORT_NESGAME
    { "NES",    CDROM_NES,      FS_FUNC_GAME },
    { "GUN",    CDROM_NESGUN,   FS_FUNC_GAME },
#endif

//jslin //20041022  //for FS support .SWD file type
#ifdef SUPPORT_PLAY_SWD
    { "SWD",    CDROM_SWD,  FS_FUNC_OTHER },
#endif

#ifdef SUPPORT_SPG_GAME 
    { "SPG",    CDROM_SPG,  FS_FUNC_GAME },
#endif

#ifdef SUPPORT_SMF    //xlluo //2005-7-27//for flash game support, (*.SWF)
    { "SMF",    CDROM_SMF,  FS_FUNC_OTHER },
#endif//SUPPORT_SMF

#ifdef SUPPORT_PLAYLIST		//wanghaoying 2005-9-28 19:31
    { "M3U",    CDROM_PLAYLIST, FS_FUNC_PLAYLIST },
    { "PLS",    CDROM_PLAYLIST, FS_FUNC_PLAYLIST },
#endif

};


int GetFileInfo( const char* pFileName )
{
    if( !pFileName )
        return -1;

    const char* pExtBegin = strrchr( pFileName, '.' );
    if( !pExtBegin || !( pExtBegin + 1 ) )
        return -1;

    pExtBegin++;

    int iFileInfoTableSize = sizeof( g_aFileExtInfoTable ) / sizeof( FILE_EXT_INFO_TABLE );

    int i = 0;
    for( ; i < iFileInfoTableSize; i++ )
    {
        if( strcmp( pExtBegin, g_aFileExtInfoTable[i].FileExt ) == 0 )
            return i;
    }

    return -1;
}

