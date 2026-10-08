/**************************************************************************
 *                                                                        *
 *         Copyright (c) 2002 by Sunplus Technology Co., Ltd.             *
 *                                                                        *
 *  This software is copyrighted by and is the property of Sunplus        *
 *  Technology Co., Ltd. All rights are reserved by Sunplus Technology    *
 *  Co., Ltd. This software may only be used in accordance with the       *
 *  corresponding license agreement. Any unauthorized use, duplication,   *
 *  distribution, or disclosure of this software is expressly forbidden.  *
 *                                                                        *
 *  This Copyright notice MUST not be removed or modified without prior   *
 *  written consent of Sunplus Technology Co., Ltd.                       *
 *                                                                        *
 *  Sunplus Technology Co., Ltd. reserves the right to modify this        *
 *  software without notice.                                              *
 *                                                                        *
 *  Sunplus Technology Co., Ltd.                                          *
 *  19, Innovation First Road, Science-Based Industrial Park,             *
 *  Hsin-Chu, Taiwan, R.O.C.                                              *
 **************************************************************************/
/*--------------------------------------------------------------------------
|  File Name   :  CDTextUtil.h
|
|  Description :  Interface Between CDText Module & RISC code
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/12/06      yltseng         Creating
|--------------------------------------------------------------------------------*/ 

#ifndef _CD_TEXT_UTIL_H_
#define _CD_TEXT_UTIL_H_

#include "types.h"

/**************************************************************************
 *  Function Name: PreParseCDTextData                                     *
 *  Purposes:                                                             *
 *    Parse CDText data into individual items.                            *
 *  Descriptions:                                                         *
 *    It will internally call CDText module to initial its buffer memory, *
 *    and then parse input data into CDText text items.                   *
 *  Arguments:                                                            *
 *    pData    : Pointer to CDText data from LeadIn area                  *
 *    iDataLen : Data length of pData                                     *
 *    iTrkNum  : Total track numbers of this CD                           *
 *    pAddr    : Pointer to buffer used to store parsed CDText text items *
 *    iSize    : Buffer length of pAddr                                   *
 *  Returns:                                                              *
 *    No return value.                                                    *
 *  See also:                                                             *
 *    osd_init_CDText, show_CDText, show_CDText_Title_Content             *
 **************************************************************************/
extern void PreParseCDTextData( BYTE* pData, int iDataLen, int iTrkNum, BYTE* pAddr, int iSize );


/**************************************************************************
 *  Function Name: osd_init_CDText                                        *
 *  Purposes:                                                             *
 *    Initialize osd memory for CDText, and draw some initial value on it.*
 *  Descriptions:                                                         *
 *    It create 4 regions( 0 ~ 3 ), and CDText uses region3 to show its   *
 *    contents.                                                           *
 *  Arguments:                                                            *
 *    No arguements.                                                      *
 *  Returns:                                                              *
 *    No return value.                                                    *
 *  See also:                                                             *
 *    PreParseCDTextData, show_CDText, show_CDText_Title_Content          *
 **************************************************************************/
extern void osd_init_CDText(void);


/**************************************************************************
 *  Function Name: show_CDText                                            *
 *  Purposes:                                                             *
 *    Show CDText information of current track( including tags ).         *
 *  Descriptions:                                                         *
 *    Currently, six kinds of CDText information will be show, they are   *
 *    Title, Performer, SongWriter, Composer, Arranger, and Message.      *
 *    It shows the above tags, and corresponding contents.                *
 *  Arguments:                                                            *
 *    uiTrk : Track number for showing its CDText information.            *
 *  Returns:                                                              *
 *    No return value.                                                    *
 *  See also:                                                             *
 *    PreParseCDTextData, osd_init_CDText, show_CDText_Title_Content      *
 **************************************************************************/
extern void show_CDText( UINT8 uiTrk );


/**************************************************************************
 *  Function Name: show_CDText_Title_Content                              *
 *  Purposes:                                                             *
 *    Show CDText information of current track( excluding tags ).         *
 *  Descriptions:                                                         *
 *    Currently, six kinds of CDText information will be show, they are   *
 *    Title, Performer, SongWriter, Composer, Arranger, and Message.      *
 *    It doesn't show above tags, it only shows their corresponding       *
 *    contents.                                                           *
 *  Arguments:                                                            *
 *    uiTrk : Track number for showing its CDText information.            *
 *  Returns:                                                              *
 *    No return value.                                                    *
 *  See also:                                                             *
 *    PreParseCDTextData, osd_init_CDText, show_CDText                    *
 **************************************************************************/
extern void show_CDText_Title_Content( UINT8 uiTrk );


#endif
