#ifndef __AUDCTRL_H
#define __AUDCTRL_H

#include "user_init.h"
#include "func.h"

/*
**  All from datasheet of the chip. If you want to know more detail, please
**  check out the datasheet. Otherwise, please look down.
**  In PT2320 and PT2322 the function command is composed of three parts:
**  first is the address of this chip(PT2320 or PT2322); second is to 
**  point out what function will be done; third is some complexed, some of it
**  is selected by user, some of it is defined already,
*/
#define I2C_ID_AUDIO_CTRL       0x88
/*
**  function subaddress 
**  the high four bit of the command word
*/
#define LEFT_FRONT              0x10
#define RIGHT_FRONT             0x20
#define CENTER              0x30
#define LEFT_REAR               0x40
#define RIGHT_REAR              0x50
#define SUBWOOFER               0x60
#define FUNC_SEL                0x70
#define NO_FUNCTION             0x80
#define BASE                    0x90
#define MIDDLE          0xa0
#define TREBLE                  0xb0
#define INPUT_SW                0xc0
#define VOLUME_1_CONTROL        0xd0
#define VOLUME_10_CONTROL       0xe0
#define SYSTEM_RESET            0xf0

/*
**  function command
**  the lowest four bit of the command word
**  some are defined already, 
**  you can't change it if you want to use the function correctly.
*/
#define SW_ON                   0x07
#define TONE_CONTROL_ON             ~(0x1<<1)
#define TONE_DEFEAT             0x1<<1
#define THREED_ON               ~(0x1<<2)
#define THREED_OFF              0x1<<2
#define PT_MUTE_OFF                ~(0x1<<3)
#define PT_MUTE_ON                 0x1<<3

/*
#define I2C_SCL_SET(d)  GPIO_O_SET(I2C_SCL,d)
#define I2C_SDA_SET(d)  GPIO_O_SET(I2C_SDA,d)
*/

#define PT2320_WRITE_SBUS(ra,d) WriteI2c(I2C_ID_AUDIO_CTRL,(ra)|(d),0,1)

void set_base(void);
void set_treble(void);
void set_middle(void);
void set_center(void);
void set_rear(void);
void set_woofer(void);
void set_volume(BYTE);
void set_front(void);
void set_mute(void);
void set_demute(void);
void set_3d_on(void);
void set_3d_off(void);
void init_pt_audio(void);
void init_volume(void);

#endif  /*__AUDCTRL_H*/
