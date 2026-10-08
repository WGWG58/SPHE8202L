/* ----------------------------------------------------------
fs_device Interface
---------------------------------------------------------- */
void fs_device_reset(UINT32 device);
void fs_polling_device(void);
void fs_device_finish_io(void);

int fs_read_sector(UINT32 device, UINT32 lba, UINT32 nSec, UINT8 *buf);
int fs_write_sector(UINT32 device, UINT32 lba, UINT32 nSec, UINT8 *buf);

/* ----------------------------------------------------------
Blocking/Non-blocking IO
---------------------------------------------------------- */
#define DEVICE_BLOCKING_IO  (0)
#define DEVICE_NBLOCKING_IO (1)

void fs_device_set_mode(UINT32 device, int mode);
