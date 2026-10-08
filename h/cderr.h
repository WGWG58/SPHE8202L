#ifndef __CDERR_H
#define __CDERR_H

#define DVDDSP_BUSY_COUNT	2000

#define CDERR_DAT_DISCONTINUE 	0x0
#define CDERR_ATA_BUSY			0x1
#define CDERR_DVDDSP_BUSY		0x2
#define CDERR_ATA_NOT_READY		0x3
#define CDERR_SHOW_RECOVER		0x4

/*******For Read ERROR Retry****/
#define DVD_R_RETRY	0x01
#define DVD_DSI_FOUND	0x02


int	cderr_handler(int);
void    ServoRecoverFail(void);
void    ServoFocusFail(void);
void    StopSeek(void);
void    Release_DVDDSP_BUSY(void);
int     VcdSeekNext(UINT32 , int);
void    dvd_end_search(void);

void    atapi_dvddsp_busy_waiting(int seek);
void    avb_dvddsp_busy_waiting(int seek);

void    clear_cderr_var(void);
void    check_clear_skip_level(UINT32 lba);
int     DvdSeekNext(UINT32 ,int);
void    cderr_update_show_time(void);            
int     drv_seek_next(void);

#endif/*__CDERR_H*/

