/* ----------------------------------------------------------
fs_new_app.h
Accessible functions for fs_new_app
---------------------------------------------------------- */
//qinhua move from fs_new_app.c 
enum
{
    NEW_APP_STATE_NONE = 0,
    NEW_APP_STATE_DRIVE,
    NEW_APP_STATE_FOLDER,
    NEW_APP_STATE_FILE,
    NEW_APP_STATE_WRITE,
    NEW_APP_STATE_FINISH,
    NEW_APP_STATE_CLOSE,
};

#define pWriteDrive     (pReadDrive)
#define pWriteFolder    (pReadFolder)
#define pWriteFile      (pReadFile)
//qinhua move from fs_new_app.c 

void    fs_new_app_reset(void);

void    fs_activate_rip(void);
void    fs_do_rip(void);
void    fs_set_rip_speed(int speed);
int     fs_get_rip_speed(void);
int     fs_is_activated_rip(void);
int     fs_rip_main(void);

void    fs_activate_copy(void);
int     fs_is_activated_copy(void);
int     fs_copy_main(void);

#ifdef CD_RIPPING_NO_GUI
extern  int new_app_state;
#endif
