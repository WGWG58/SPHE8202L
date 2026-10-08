#ifndef __ATAPI_IF_H
#define __ATAPI_IF_H

#include "types.h"
#include "user_init.h"

// 2004/07/16 yltseng
void wb_tag_init(void);
extern void atapi_dvddsp_busy_waiting(int seek);

// Register Read/Write
UINT16 atapi_reg_read(UINT8);
void atapi_reg_write(UINT8, UINT16);

int atapi_authenticate(int title, int lba);

// ATAPI Procedure
// return 1: ERR, 0: OK
void atapi_hard_rst(void);
UINT8 atapi_soft_rst(void);
UINT8 atapi_device_sel(void);
UINT8 atapi_write_block(UINT8 *);
UINT8 atapi_send_data(UINT8 *, int);
UINT8 atapi_receive_data(UINT8 *, int);
UINT8 atapi_is_error(void);
int atapi_read_error(void);

// ATA command
UINT8 atapi_do_packet(UINT8 *);
UINT8 atapi_do_set_features(void);
UINT8 atapi_do_identify_packet_device(UINT8 *);

// Packet command
UINT8 atapi_p_request_sense(UINT8 *);
UINT8 atapi_p_test_unit_ready(void);
UINT8 atapi_p_start_stop_unit(UINT8,UINT8);
UINT8 atapi_p_read_12(UINT32, UINT32);

UINT8 atapi_p_mechanism_status(void);
UINT8 atapi_p_read_capacity(UINT32 *, UINT32 *);
UINT8 atapi_p_get_disc_info(void);

#ifdef ALCO_SPECIAL_DISC_FUNCTION
UINT8 bIsMillionaire; //axel for Alco Millionaire 2005/9/14 
#endif

#define ATAPI_DOOR_OPEN    (0)
#define ATAPI_DOOR_CLOSE_ERR   (3)
#define ATAPI_DOOR_CLOSE   (2)

// high level command
// need error handle
void atapi_init(void);
UINT8 atapi_block_read(UINT32, UINT32);
void atapi_menu(void);


#define ATAPI_OK	(0)
#define ATAPI_ERROR	(1)
#define ATAPI_ILLEGAL	(2)

#define START_STOP_DO_STOP		(0)
#define START_STOP_DO_START		(1)
#define START_STOP_DO_EJECT		(2)
#define START_STOP_DO_LOAD		(3)
#define START_STOP_DO_STANDBY	(4)//terry,2003/8/22 05:47PM
#define START_STOP_DO_LOAD_POWER_OFF	(7) //robert, 2003/12/16

#define Immed_0		(0)  //axel 2005/12/29 
#define Immed_1		(1)

// generic packet command
#define CDROM_PACKET_SIZE	12


/*********define dev_status_flag*****/

#define READ_PRESENT_DATA	0x01//bit 1 data type, 1:present 0:nav or cmd
//#define NAV_RETRY_DATA  	0x02
#define ATAPI_WAIT_TIME_OUT	0x04
#define ATAPI_RETRY_READY	0x08
#define DEV_DETECT_CSS      0x10

/*****define atapi_chk_time_out state****/



#define WAIT_ALT_NO_BUSY	0x01
#define WAIT_DRQ_OK		0x02
#define WAIT_STATUS_NO_BSY	0x03
#define WAIT_DRQ_BSY_ZERO	0x04
#define WAIT_DRQ_HIGH		0x05
#define WAIT_IRQ            0x06

/*******Define request sense flag************/

#define ATAPI_NOT_READY		0x01
#define ATAPI_NO_MEDIA		0x02
#define ATAPI_MEDIA_UPSIDE_DOWN	0x04
#define ATAPI_UNKNOWN_MEDIA	0x08
#define ATAPI_ILLEGAL_MODE	0x10

/* for CDROM_PACKET_COMMAND ioctl */
struct cdrom_generic_command
{
	UINT8 	cmd[CDROM_PACKET_SIZE];
	UINT8 	*buffer;
	unsigned int 	buflen;
	int		stat;
	void		*reserved[4];
};

#define GPCMD_REPORT_KEY				(0xa4)
#define GPCMD_SEND_KEY					(0xa3)
#define GPCMD_READ_DVD_STRUCTURE		(0xad)


void init_cdrom_command(struct cdrom_generic_command *, void *, int);
int generic_packet(struct cdrom_generic_command *);

void auth_test(void);

#ifndef DVDRELEASE
void print_block(UINT8 *, int);
#endif

UINT8 do_read(UINT32 lba, UINT32 len, UINT8 *buf);


typedef struct
{
   UINT8 m, s, f;
} t_cdrom_msf0;

typedef struct
{
   UINT8 m0, s0, f0;    // start
   UINT8 m1, s1, f1;    // end
} t_cdrom_msf;


#define MAX_TRACKS 99

struct atapi_msf {
	UINT8 reserved;
	UINT8 minute;
	UINT8 second;
	UINT8 frame;
};


struct atapi_toc_header {
	UINT16 toc_length;
	UINT8 first_track;
	UINT8 last_track;
};

struct atapi_toc_entry {
	UINT8 reserved1;
   UINT8 adr_control;
	UINT8 track;
	UINT8 reserved2;
	union {
		UINT32 lba;
		struct atapi_msf msf;
	} addr;
};

#define DSP_HOST_RESET  (0x01<<0)
#define ATA_SW_RESET    (0x01<<1)
#define ATA_HW_RESET	(0x01<<2)
#define ATA_WAIT_RDY	(0x01<<3)

//define loader vendor type
#define VENDOR_UNKNOW          0x00
#define VENDOR_ALI_TD_505_SK   0x01


UINT8 atapi_read_cd(UINT32 lba, UINT32 len);
UINT8 atapi_read_cd_msf(t_cdrom_msf *pmsf);
void atapi_close_init(void);
UINT8 atapi_p_unlock(void);
BYTE atapi_chk_time_out(BYTE cmd_state,int w_time);
BYTE atapi_2_mem_read_cd(UINT32 lba,UINT32 len,BYTE user_only);
//BYTE atapi_2_mem_read_12(UINT32 lba,UINT32 len);
UINT8 atapi_rst(UINT8 mode);
//void atapi_identify(void);
UINT8 atapi_do_inquiry(void);

#ifdef DVD_SERVO_REAL_TURN_OFF//nono rename 4-12-30 11:18//NO_DVD_SERVO //ycwen 2004/08/10
extern void servo_turn_off(void);
#endif

//ycwen 2004/08/10
#if defined(DVD_SERVO_REAL_TURN_OFF)//def NO_DVD_SERVO
    #ifdef ReadServoReg
        #undef ReadServoReg
    #endif
    #define ReadServoReg(name,value)                            \
        {                                                       \
            regs0->rf_regif_addr = name;                        \
            while ((regs0->rf_regif_rdata & 0x8000) != 0x8000); \
            value = regs0->rf_regif_rdata;                      \
        }
         
    #ifdef WriteServoReg
        #undef WriteServoReg
    #endif
    #define WriteServoReg(name,value)                           \
        {                                                       \
            regs0->rf_regif_addr = name;                        \
            regs0->rf_regif_wdata = value;                      \
            while ((regs0->rf_regif_rdata & 0x8000) != 0x8000); \
        }
#endif //DVD_SERVO_REAL_TURN_OFF//NO_DVD_SERVO

#endif /*__ATAPI_IF_H*/

