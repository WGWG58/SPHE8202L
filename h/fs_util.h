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
|  File Name   :  Fs_util.h
|
|  Description :  Header of file system utility
|                 In face, the main purpose of this file is to seperate functions into different files,
|                 in order to be more modual, to be able to dynamically download modules.
|
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	2004/12/30      yltseng         Creating
|--------------------------------------------------------------------------------*/ 

#ifndef _CDROM_SHARECODE_H_
#define _CDROM_SHARECODE_H_

#include "types.h"

/**************************************************************************
 *  Function Name: mp3_file_count                                         *
 *  Purposes:                                                             *
 *    Get file count. Return value depends on what precompile header is   *
 *    defined.                                                            *
 *  Descriptions:                                                         *
 *    None.                                                               *
 *  Arguments:                                                            *
 *    None.                                                               *
 *  Returns:                                                              *
 *    If MP3_DIRECT_SELECT is defined, returns the total file counts of   *
 *    current selected file category( MP3/JPEG/Game/Other ) in all        *
 *    directories.                                                        *
 *    Else, returns total file counts of current select file category in  *
 *    current selected directory.                                         *
 *  See also:                                                             *
 *    None.                                                               *
 **************************************************************************/
extern UINT16   mp3_file_count( void );

/**************************************************************************
 *  Function Name: is_merge_mp3file                                       *
 *  Purposes:                                                             *
 *    Check if current file is seperated into some discontinuous blocks   *
 *    or not. If it is, it also update st_msf/s_msf/e_msf/s_len/len by    *
 *    current block infos.                                                *
 *  Descriptions:                                                         *
 *    In ISO9660, all datas of a file must be allocated continuously, so  *
 *    this function always do nothing but return FALSE.                   *
 *    But in UDF, they can be allocated discontinuously. When finishing   *
 *    current block, this function helps to change access address to next *
 *    block, thus we can play seamless.                                   *
 *  Arguments:                                                            *
 *    len : length of next block.                                         *
 *  Returns:                                                              *
 *    TRUE  : If current file is seperated into some discontinuous blocks.*
 *    FALSE : Else.                                                       *
 *  See also:                                                             *
 *    None.                                                               *
 **************************************************************************/
extern int      is_merge_mp3file( UINT32* pLen );

#endif
