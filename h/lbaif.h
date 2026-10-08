#ifndef __LBAIF_H
#define __LBAIF_H

//
// SEARCH: PCI/DSI
//
#define LBA_ST_IDLE 0
#define LBA_ST_FIND_NAV 3
#define LBA_ST_FREE 1
#define LBA_ST_DVD  2

//
//
//
typedef struct  {
  UINT32    rlba_s;
  UINT32        lba;        // Current LBA (absolute)
  UINT32    lba_start;  // LBA start point (absolute)
  UINT32        len;        // Playback block numbers
  int           batch;
} t_lba_st;

EXTERN  t_lba_st      lba_st;


//
//
//
EXTERN  UINT32      LBA_CELL;   // absolute LBA of CELL
EXTERN  UINT32      LBA_VOBU;   // absolute LBA of VOBU

EXTERN  UINT16      cd_data_ready;
EXTERN  UINT16      host_req;

static  inline
int drv_accessible(void)
{
#if	DISC_SYSTEM==DISC_SYSTEM_ATAPI
  return cd_data_ready;
#else
  return cd_data_ready>=8;
#endif  
}

static  inline
void    drv_access_batch(void)
{
#if	DISC_SYSTEM==DISC_SYSTEM_ATAPI	
  cd_data_ready=1;
#else
  cd_data_ready++;
#endif  
}

static  inline
void    drv_access_again(void)
{
#if	DISC_SYSTEM==DISC_SYSTEM_ATAPI		
  cd_data_ready=1;
#else
  cd_data_ready=9;
#endif  
}

static  inline
void    drv_access_begin(void)
{
  cd_data_ready=0;
  host_req=1;
}

static  inline
int    is_drv_access_begin(void)
{
  return cd_data_ready==0;
}

static inline
int is_host_request_data(void)
{
  return host_req==1;
}
static inline 
void set_host_request(void)
{
  host_req=1;
}
static inline 
void clr_host_request(void)
{
  host_req=0;
}
void    flush_atapi(void);
void    reset_atapi_intr(void);
void    start_atapi_intr(UINT32, int, int);
int lba_read_next(void);
void    intr_device_atapi(void);

#endif/*__LBAIF_H*/
