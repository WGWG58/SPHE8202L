#ifndef _CD_TEXT_H_
#define _CD_TEXT_H_

#include "types.h"

typedef enum 
{
    CDT_TITLE = 0,
    CDT_PERFORMER,
    CDT_SONGWRITER,
    CDT_COMPOSER,
    CDT_ARRANGER,
    CDT_MESSAGE,    
} CD_TEXT_TYPE;

extern int          IsCDTextExist();
extern void         ClearCDTextData();      //lizhx 2004/08/23
extern const BYTE*  GetCDText( UINT8 uiTrk, CD_TEXT_TYPE enType );
extern int          InitCDTextMemory( BYTE* pAddr, int iLen );
extern void         ParseCDTextData( const BYTE* pData, const int iLen, const int iTrkCnt );

#endif
