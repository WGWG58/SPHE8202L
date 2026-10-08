/* ----------------------------------------------------------
cd_ripping.h
---------------------------------------------------------- */
void cd_ripping_reset(void);
void cd_ripping_start(void);
void cd_ripping_stop(void);
int is_cd_ripping_active(void);

void cd_ripping_ir_handler(UINT8 rx);
void rip_service_transport(void);
