#ifndef __IMAGE_H
#define __IMAGE_H

#include "global.h"
#include "atapi_if.h"
#include "memmap0.h"

int image_init(char *);
void image_close(void);

/*
#define wb_check(p)  \
	((((UINT8 *)(p)) - ((UINT8 *)(pwb)) > 2048) ? \
	((p) -= 2048, wb_next()) : TRUE)
*/
#define MAX_NAV_TAG_SIZE    (MAX_BUF_SIZE/2)

UINT8 *wb_check(UINT8 *p);
UINT8 *wb_loc(UINT32, UINT32);
int wb_init(UINT32);
int wb_next(void);

typedef struct
{
    UINT8 *baseptr;
    UINT32 read_len;
    UINT32 buf_limit;       
} RAN_READ_FS_STRUCT;

void EnableBuffer( int );

typedef struct
{
    UINT32  uiLba;
    UINT8   uiIdx;
} NAV_TAG_STRUCT;

NAV_TAG_STRUCT  lba_tag[MAX_NAV_TAG_SIZE];

//extern UINT8 pwb[WB_SIZE];

// 2004/07/26 yltseng
extern BYTE ran_read_dma( UINT16 cdya, UINT32 lba, UINT32 len );
extern BYTE ran_read_fs(UINT8 **ptr, UINT32 start, UINT32 f_offset, UINT32 *len);
extern BYTE ran_read( UINT8 *ptr, UINT32 msf, UINT32 len );
extern BYTE ran_read_vcd( UINT8 *ptr, UINT32 msf, UINT32 len );
extern BYTE ran_read_jpeg(RAN_READ_FS_STRUCT *read_struct, UINT32 f_start, UINT32 f_offset);
#endif /* __IMAGE_H */
