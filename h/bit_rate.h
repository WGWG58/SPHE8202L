#ifndef _BITRATE_H_
#define _BITRATE_H_

#include "types.h"

//#define DISPLAY_DATA_BIT_RATE

typedef enum
{
    VBR_MP3_INTERVAL_N_LBA,     // For each n lba interval, we get 1 lba, so totally ( MP3Length / n ) lba
    VBR_MP3_FIRST_N_LBA,        // Get data from first n lba
    VBR_MP3_CENTER_N_LBA,
    VBR_MP3_N_LBA,              // Exactly get n lba, so interval is ( MP3Length / n )
}   VBR_MP3_LBA_TYPE;

extern void     init_bit_rate( void );
extern void     sample_bit_rate_per_sec( void );
extern UINT32   PreParseMP3BitRate( VBR_MP3_LBA_TYPE enType, UINT32 uiParam, UINT32 uiLba, UINT32 uiLen );

extern UINT32   GetBPS();

#endif
