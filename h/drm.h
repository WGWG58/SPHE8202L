#ifndef __DRM_H
#define __DRM_H

#include "global.h"
#include "types.h"

#define DRM_VERSION						2
#define DRM_HEADER_SIZE        			2224

#ifdef	DIVX_DRM

//============================================================================

// DrmStatus.display_type	
#define DRM_DISPLAY_NONE				0
#define DRM_DISPLAY_REGISTRATION_CODE	1
#define DRM_DISPLAY_AUTHORIZATION_ERROR	2
#define DRM_DISPLAY_RENTAL_EXPIRED		3
#define DRM_DISPLAY_RENTAL_CONFIRMATION	4
#define DRM_DISPLAY_HW_UNSUPPORTED		5
#define DRM_DISPLAY_AES_ONLY			6

// size or length
#define DRM_ENCRYPTED_CHK_MAX_LEN		128
#define OWNER_GUARD_BYTES               3
#define DRM_MEMORY_SIZE					48

//============================================================================
typedef struct DrmInfoChunkStruct
{
	UINT16	frameKeyIndex	__attribute__ ((packed));
	UINT32	offset			__attribute__ ((packed));
	UINT32	decryptSize		__attribute__ ((packed));
} DrmInfoChunk;

typedef struct DrmStatusStruct
{
	UINT16	display_type;
	UINT16	reference_code;
} DrmStatus;

//============================================================================
/*
extern int get_drm_mem(BYTE* buf, int offset, int length);
extern int save_drm_mem(BYTE* buf, int offset, int length);
*/

DrmStatus* get_drm_status();
void set_divx_drm_mode(UINT32 mode);
void set_divx_drm_model_id(UINT32 model_id);
int drm_stream_header(BYTE* ptr);
void aes_decrypt_frame(BYTE* cipher, UINT16 frameKeyIndex, UINT32 length);
void generate_registration_code(BYTE code[8+1]);
void drm_rental_count_update();
void drm_save_rental_file(int drm_enable, int nRet);

//============================================================================
#endif	// DIVX_DRM
	
#endif	// __DRM_H
