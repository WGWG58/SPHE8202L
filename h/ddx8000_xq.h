#ifndef __DDX8000_H_
#define __DDX8000_H_
/*****************************************************\
Creater: xiongyuyue
Date   : 2003/8/26 
Description: digital amp function using 
\*****************************************************/
#ifdef SUPPORT_APOGEE_AMP//xyy 2003-9-24 9:28

#define DDX8K_ADDR      0x30

//BYTE flag = 1;

typedef struct
{
	UINT32 b2;
	UINT32 b0;
	UINT32 a2;
	UINT32 a1;
	UINT32 b1;
}coef_factor;



//configuration register
#define CONFIGREG_A      0x00   //Configuration Register A
#define CONFIGREG_B      0x01   //Configuration Register B
#define CONFIGREG_C      0x02
#define CONFIGREG_D      0x03
#define CONFIGREG_E      0x04
#define CONFIGREG_F      0x05

//volume adjustment
#define MASTER_MUTE_REG  0x06
#define MASTER_VOL_REG   0x07
#define CHANEL_MUTE_REG  0x08
//#define CHANEL_VOL_REG   0x09

#define C1V_REG          0x09
#define C2V_REG          0x0a
#define C3V_REG          0x0b
#define C4V_REG          0x0c
#define C5V_REG          0x0d
#define C6V_REG          0x0e
#define C7V_REG          0x0f
#define C8V_REG          0x10

//channel mapping
#define C12MAP_REG       0x11
#define C34MAP_REG       0x12
#define C56MAP_REG       0x13
#define C78MAP_REG       0x14

//channel limiter selection
#define CLIMITER_SEL0    0x15
#define CLIMITER_SEL1    0x16

//limiter rates and thresholds
#define L1RATE_REG       0x17
#define L1THRESHOLDS_REG 0x18
#define L2RATE_REG       0x19
#define L2THRESHOLDS_REG 0x1a

//tone control register
#define TONE_CTRL_REG    0x1b


//Bass Management(Configuration #1) for 5.1 Channels
#define FL_SCALE_FACTOR     0x16c310
#define FR_SCALE_FACTOR     0x16c310
#define SL_SCALE_FACTOR     0x16c310
#define SR_SCALE_FACTOR     0x16c310
#define CE_SCALE_FACTOR     0x16c310
#define LFE_SCALE_FACTOR    0x47facc

#define HPF_COEF_B2              0x7fa51f
#define HPF_COEF_B0              0x3fd28f
#define HPF_COEF_A2              0x80b581
#define HPF_COEF_A1              0x7fa4ff
#define HPF_COEF_B1              0x805ae1

#define LPF_COEF_B2              0x000020
#define LPF_COEF_B0              0x000010
#define LPF_COEF_A2              0x80b581
#define LPF_COEF_A1              0x7fa4ff
#define LPF_COEF_B1              0x000020

//#define 

#define MV    0
#define FL    1
#define FR    2
#define SL    3
#define SR    4
#define CE    5
#define SW    6

#define Y_07   7
int y_index;

#define AMPBGCOL 10

typedef struct
{
	BYTE mainvol_level;
	BYTE mainvol;
	BYTE lfront_level;
	BYTE lfrontvol;
	BYTE rfront_level;
	BYTE rfrontvol;
	BYTE lrear_level;
	BYTE lrearvol;
	BYTE rrear_level;
	BYTE rrearvol;
	BYTE center_level;
	BYTE centervol;
	BYTE woofer_level;
	BYTE woofervol;

	BYTE ddx_Bass_lev;
	BYTE ddx_Treble_lev;
	BYTE ddx_EQ_sel;
	BYTE ddx_Revb_sel;
}s_amp_userSet;
s_amp_userSet amp_userSet;

#define AMP_I2CADDR_START 512

#define BASS_GAIN_ADDR	AMP_I2CADDR_START+14
#define TREBLE_GAIN_ADDR BASS_GAIN_ADDR+1
#define DDX_EQ_TYPE_ADDR TREBLE_GAIN_ADDR+1
#define DDX_REVB_TYPE_ADDR DDX_EQ_TYPE_ADDR+1

//EQ types define
#define NONE 0
#define ROCK 1
#define POP 2
#define PARTY 3
#define DANCE 4
#define HARD 5
#define CLASSIC 6
#define SOFT 7
#define MAX_EQ_NUM 7 

//Reverberation types define
#define OFF 0
#define CONCERT 1
#define LIVING 2
#define HALL 3
#define BATH 4
#define CAVE 5
#define ARENA 6
#define CHURCH 7
#define MAX_REVB_NUM 7 

#define MAX_BASSCTRL_LEV 15
#define MAX_TREBLECTRL_LEV 15

extern void ddx_Set_EQ(BYTE EQtype);
extern void ddx_ampvol_func_left(void);
extern void ddx_ampvol_func_right(void);
extern void ddx_ampvol_func_up(void);
extern void ddx_ampvol_func_down(void);
extern BYTE ddx_trebleCtrl(int updown);
extern BYTE  ddx_bassCtrl(int updown);
#endif

#endif//#ifdef SUPPORT_APOGEE_AMP
