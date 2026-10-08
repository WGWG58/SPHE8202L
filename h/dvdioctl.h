#ifndef __DVDIOCTL_H_
#define __DVDIOCTL_H_

#include "types.h"

/* DVD struct types */
#define DVD_STRUCT_PHYSICAL	    0x00
#define DVD_STRUCT_COPYRIGHT	0x01
#define DVD_STRUCT_DISCKEY		0x02
#define DVD_STRUCT_BCA			0x03
#define DVD_STRUCT_MANUFACT	    0x04
#define DVD_STRUCT_MEDIA_ID     0x06
#define DVD_STRUCT_MKB          0x07  //we don't do it tmp.,because need more memory size
/*
struct dvd_media_id {
	UINT16 data_length;
	UINT8 reserved1[2];
	UINT8 ID_media[8];
	UINT8 MAC_ID_media[10];	
	UINT8 reserved2[2];
};

struct dvd_layer {
	UINT8 book_version	: 4;
	UINT8 book_type		: 4;
	UINT8 min_rate		: 4;
	UINT8 disc_size		: 4;
	UINT8 layer_type		: 4;
	UINT8 track_path		: 1;
	UINT8 nlayers		: 2;
	UINT8 track_density	: 4;
	UINT8 linear_density	: 4;
	UINT8 bca		: 1;
	UINT32 start_sector;
	UINT32 end_sector;
	UINT32 end_sector_l0;
};

struct dvd_physical {
	UINT8 type;
	UINT8 layer_num;
	struct dvd_layer layer[4];
};

struct dvd_copyright {
	UINT8 type;
	
	UINT8 layer_num;
	UINT8 cpst;
	UINT8 rmi;
};*/

struct dvd_disckey {
	UINT8 type;
	
	unsigned agid		: 2;
	UINT8 *value;
};
/*
struct dvd_bca {
	UINT8 type;
	
	int len;
	UINT8 value[188];
};

struct dvd_manufact {
	UINT8 type;
	
	UINT8 layer_num;
	int len;
	UINT8 value[2048];
};*/

typedef union {
	UINT8 type;
	
/*	struct dvd_physical	physical;
	struct dvd_copyright	copyright;*/
	struct dvd_disckey	disckey;
/*	struct dvd_bca		bca;
	struct dvd_manufact	manufact;
	struct dvd_media_id media_id;*/
} dvd_struct;

/*
* DVD authentication ioctl
*/

/* Authentication states */
#define DVD_LU_SEND_AGID	0
#define DVD_HOST_SEND_CHALLENGE	1
#define DVD_LU_SEND_KEY1	2
#define DVD_LU_SEND_CHALLENGE	3
#define DVD_HOST_SEND_KEY2	4

/* Termination states */
#define DVD_AUTH_ESTABLISHED	5
#define DVD_AUTH_FAILURE	6

/* Other functions */
#define DVD_LU_SEND_TITLE_KEY	7
#define DVD_LU_SEND_ASF		8
#define DVD_INVALIDATE_AGID	9

/* State data */
typedef UINT8 dvd_key[5];		/* 40-bit value, MSB is first elem. */
typedef UINT8 dvd_challenge[10];	/* 80-bit value, MSB is first elem. */

struct dvd_lu_send_agid {
	UINT8 type;
	unsigned agid		: 2;
};

struct dvd_host_send_challenge {
	UINT8 type;
	unsigned agid		: 2;
	
	dvd_challenge chal;
};

struct dvd_send_key {
	UINT8 type;
	unsigned agid		: 2;
	
	dvd_key key;
};

struct dvd_lu_send_challenge {
	UINT8 type;
	unsigned agid		: 2;
	
	dvd_challenge chal;
};

#define DVD_CPM_NO_COPYRIGHT	0
#define DVD_CPM_COPYRIGHTED	1

#define DVD_CP_SEC_NONE		0
#define DVD_CP_SEC_EXIST	1

#define DVD_CGMS_UNRESTRICTED	0
#define DVD_CGMS_SINGLE		2
#define DVD_CGMS_RESTRICTED	3

struct dvd_lu_send_title_key {
	UINT8 type;
	unsigned agid		: 2;
	
	dvd_key title_key;
	int lba;
	unsigned cpm		: 1;
	unsigned cp_sec		: 1;
	unsigned cgms		: 2;
};

struct dvd_lu_send_asf {
	UINT8 type;
	unsigned agid		: 2;
	
	unsigned asf		: 1;
};

typedef union {
	UINT8 type;
	
	struct dvd_lu_send_agid		lsa;
	struct dvd_host_send_challenge	hsc;
	struct dvd_send_key		lsk;
	struct dvd_lu_send_challenge	lsc;
	struct dvd_send_key		hsk;
	struct dvd_lu_send_title_key	lstk;
	struct dvd_lu_send_asf		lsasf;
} dvd_authinfo;


int dvd_read_struct(dvd_struct *);
int dvd_do_auth(dvd_authinfo *);


#endif /* DVDIOCTL */

