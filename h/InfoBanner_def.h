/*
|  Description : This file include just the following as
|
|                 1)  COLOR definition
|                 2)  location Definition
|                 3)  cd type definition
|  Version    :  0.1  
| 
| 
|  Rev	Date	        Author(s)      Status & Comments
|---------------------------------------------------------------------------------
|  0.1	20040315        feeling      creating
|
*/

#ifndef INFO_BANNER_DEF_H
#define INFO_CDDVD  0
#define INFO_CDDA   1
#define INFO_CDVCD    2
#define INFO_CDROM  3


#define INFO_BANNER_DEF_H

#define TRANSPARENT 0
#define FULL_TRANS 11
#define YELLOWGREEN 12
#define GRAY 13
#define BLACK 15
#define WHITE 14

#define BANNER_INDEX_X	36
#define BANNER_INDEX_Y	0

#define BANNER_ICON1_X	BANNER_INDEX_X+145
#define BANNER_ICON1_Y	BANNER_INDEX_Y+14

#define BANNER_ICON_W	56
#define BANNER_ICON_H	54

#define SPACE_BETWEEN_COLUMNS_W 2

#define BANNER_CDROM_PLAYMODE_X BANNER_INDEX_X+326

#define BANNER_CDROM_INFOBK6_X BANNER_INDEX_X+146
#define BANNER_CDROM_INFOBK6_Y  BANNER_INDEX_Y+14
#define BANNER_CDROM_INFOBK6_X_2    BANNER_INDEX_X+386
#define BANNER_CDROM_INFOBK6_Y_2    BANNER_INDEX_Y+14
#define BANNER_CDROM_INFOBK6_W  180
#define BANNER_CDROM_INFOBK6_H  54

#define BANNER_CDROM_SONGBAN_X    BANNER_INDEX_X+150
#define BANNER_CDROM_SONGBAN_Y    BANNER_INDEX_Y+16
#define BANNER_CDROM_PICTUBAN_X   BANNER_INDEX_X+390
#define BANNER_CDROM_PICTUBAN_Y   BANNER_INDEX_Y+16
#define BANNER_CDROM_MP3_TEXT_X   BANNER_INDEX_X+182
#define BANNER_CDROM_MP3_TEXT_Y   BANNER_INDEX_Y+22
#define BANNER_CDROM_JPEG_TEXT_X  BANNER_INDEX_X+422
#define BANNER_CDROM_JPEG_TEXT_Y  BANNER_INDEX_Y+ 22
#define BANNER_CDROM_MP3_TITLE_X  BANNER_INDEX_X+152
#define BANNER_CDROM_MP3_TITLE_Y  BANNER_INDEX_Y+50
#define BANNER_CDROM_JPEG_TITLE_X  BANNER_INDEX_X+392
#define BANNER_CDROM_JPEG_TITLE_Y  BANNER_INDEX_X+50

#define INFO_FULL   2
#define INFO_PARTIAL    1
#define INFO_NONE    0
#endif  //define INFO_BANNER_DEF_H

