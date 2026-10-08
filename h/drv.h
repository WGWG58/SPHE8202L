#ifndef __DRV_H
#define __DRV_H

//
// FILE
// drv.h
// DESCRIPTION
// this is the driver interface to the upper control
//
// drv_init
// drv_block_read
// test_drv_rdy
// open_tray
// close_tray
// abort_play
// get_disc_info
// read_toc         CD
// authenticate         DVD
// dvddsp_busy_waiting
//

#include "pu8560.h"

#define READTOC_RETRY   6
#define READTOC_INIT    (UINT32)(-1)

extern UINT16 dvddsp_sw_busy;

#define DISC_DUMP_Y             (regs0->dvddsp_vy)
#define DISC_DUMP_X             (regs0->dvddsp_vx)
#define DISC_BARRIER_Y          (regs0->dvddsp_ry)
#define DISC_BARRIER_X          (regs0->dvddsp_rx)

#ifdef DVD_SERVO
#define is_dvddsp_hw_busy()     (dvddsp_sw_busy)
#else
#define is_dvddsp_hw_busy()     (regs0->dvddsp_function & (1<<15))
#endif


#if DISC_SYSTEM==DISC_SYSTEM_ATAPI
//
// ATAPI
//
#include "atapi_if.h"
#define drv_init()                  atapi_init()
#define drv_block_read              atapi_block_read
#define test_drv_rdy()              test_atapi_drv_rdy() 
#define open_tray()                 atapi_open_tray()
#define close_tray(x)               atapi_close_tray(x)
#define abort_play()                atapi_abort_play()
#define read_toc()                  atapi_read_toc()

#ifdef SUPPORT_CD_TEXT
#define read_cd_text()              atapi_read_cd_text()
#endif

#define get_disc_info()             atapi_p_get_disc_info()
#define dvddsp_busy_waiting(x)      atapi_dvddsp_busy_waiting(x)
#define authenticate(title,lba)     atapi_authenticate(title,lba)
#define drv_read_error()            atapi_read_error() 
#define drv_is_error()              atapi_is_error() 
#define drv_standby()               atapi_standby_mode() 
#ifdef  DVD_SERVO
#define drv_do_set_features();          
#else
#define drv_do_set_features()          atapi_do_set_features() 
#endif

#elif   DISC_SYSTEM==DISC_SYSTEM_UDE
//
// UDE
//
#include "ude_if.h"
#define drv_init()                  ude_init()
#define drv_block_read              ude_block_read
#define test_drv_rdy()              test_avb_drv_rdy() 

#elif   DISC_SYSTEM==DISC_SYSTEM_AVB
//
// AVB
//
#include "avb_if.h"
#define drv_init()                  avbTestInit()
#define test_drv_rdy()              test_avb_drv_rdy() 
#define drv_block_read              avb_block_read
#define is_tray_close()             avb_is_tray_close()
#define is_ready2play()             avb_is_ready2play()
#define is_no_disc()                avb_is_no_disc()
#define open_tray()                 avb_open_tray()
#define close_tray()                avb_close_tray()
#define abort_play()                avb_abort_play()
#define read_toc()                  avb_read_toc()

#ifdef SUPPORT_CD_TEXT
#define read_cd_text()
#endif

#define get_disc_info()             avb_disc_info()
#define dvddsp_busy_waiting(x)      avb_dvddsp_busy_waiting(x)
#define authenticate(title,lba)     avb_authenticate(title,lba)
#endif

#endif/*__DRV_H*/

