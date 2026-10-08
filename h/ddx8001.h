#ifndef __DDX8000_H_
#define __DDX8000_H_
/*****************************************************\
Creater: xiongyuyue
Date   : 2003/8/26 
Description: digital amp function using 
\*****************************************************/
#ifdef SUPPORT_APOGEE_AMP//xyy 2003-9-24 9:28
 


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
#define CONFIGREG_C      0x02	//Configuration Register C
#define CONFIGREG_D      0x03	//Configuration Register D
#define CONFIGREG_E      0x04	//Configuration Register E
#define CONFIGREG_F      0x05	//Configuration Register F
#define CONFIGREG_G      0x06	//Configuration Register G
#define CONFIGREG_H      0x07	//Configuration Register H
#define CONFIGREG_I      0x08	//Configuration Register I

//volume adjustment
#define MASTER_MUTE_REG  0x09	//Master Mute
#define MASTER_VOL_REG   0x0A	//Master Volume
//#define CHANEL_MUTE_REG  0x08	//WZJ 04/05/24
//#define CHANEL_VOL_REG   0x09

#define C1V_REG          0x0B	//Channel 1 Volume
#define C2V_REG          0x0C	//Channel 2 Volume
#define C3V_REG          0x0D	//Channel 3 Volume
#define C4V_REG          0x0E	//Channel 4 Volume
#define C5V_REG          0x0F	//Channel 5 Volume
#define C6V_REG          0x10	//Channel 6 Volume
#define C7V_REG          0x11	//Channel 7 Volume
#define C8V_REG          0x12	//Channel 8 Volume

//channel controls	wzj 04/05/24
#define C1MVT_REG       0x13	//Channel 1 Mute, VolBP, Trim
#define C2MVT_REG       0x14	//Channel 2 Mute, VolBP, Trim
#define C3MVT_REG       0x15	//Channel 3 Mute, VolBP, Trim
#define C4MVT_REG       0x16	//Channel 4 Mute, VolBP, Trim
#define C5MVT_REG       0x17	//Channel 5 Mute, VolBP, Trim
#define C6MVT_REG       0x18	//Channel 6 Mute, VolBP, Trim
#define C7MVT_REG       0x19	//Channel 7 Mute, VolBP, Trim
#define C8MVT_REG       0x1A	//Channel 8 Mute, VolBP, Trim

//channel mapping
#define C12MAP_REG       0x1B	//Channel 1 & 2 Mapping
#define C34MAP_REG       0x1C	//Channel 3 & 4 Mapping
#define C56MAP_REG       0x1D	//Channel 5 & 6 Mapping
#define C78MAP_REG       0x1E	//Channel 7 & 8 Mapping

//AutoMode Registers	WZJ 04/05/24
#define Auto1_REG	 0x1F	//Auto Mode DM, GC, Volume, EQ
#define Auto2_REG	 0x20	//Auto Mode Bass Management
#define Auto3_REG	 0x21	//Auto Mode AM
#define PreEQ_REG	 0x22	//Preset EQ

//graphic EQ	WZJ 04/05/24
#define Ageq_REG	 0x23	//Graphic EQ Band A
#define Bgeq_REG	 0x24	//Graphic EQ Band B
#define Cgeq_REG	 0x25	//Graphic EQ Band C
#define Dgeq_REG	 0x26	//Graphic EQ Band D
#define Egeq_REG	 0x27	//Graphic EQ Band E
// EQ Bypass Modes

#define EQ_BYPASS_REG    0x2A	//EQ Bypass
//tone control register
#define TONE_CTRL_REG    0x2B	//Channel Tone Control Bypass
#define BT_TONE_CTRL_REG 0x2C	//Bass and Treble Tone Control

//channel limiter selection
#define CLIMITER_SEL0    0x2D	//Channel 1, 2, 3, 4 Limiter Select
#define CLIMITER_SEL1    0x2E	//Channel 5, 6, 7, 8 Limiter Select

//limiter rates and thresholds
#define L1RATE_REG       0x2F	//Limiter 1 Attack/Release Rate
#define L1THRESHOLDS_REG 0x30	//Limiter 1 Attack/Release Threshold
#define L2RATE_REG       0x31	//Limiter 2 Attack/Release Rate
#define L2THRESHOLDS_REG 0x32	//Limiter 2 Attack/Release Threshold




//Bass Management(Configuration #1) for 5.1 Channels
#define FL_SCALE_FACTOR     0x16c310
#define FR_SCALE_FACTOR     0x16c310
#define SL_SCALE_FACTOR     0x16c310
#define SR_SCALE_FACTOR     0x16c310
#define CE_SCALE_FACTOR     0x16c310
//#define LFE_SCALE_FACTOR    0x47facc
#define LFE_SCALE_FACTOR   0x7fffff


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

#if 0//def AMP_SUPPORT_EQ  //xyy
BYTE ddx_EQ_sel;

//EQ types define
#define ROCK 0
#define POP 1
#define CLASSIC 2
#define JAZZ 3
#define FLAT 4
#define MAX_EQ_NUM 5 
#endif

#ifdef SUPPORT_REVERBERATION  
BYTE ddx_Revb_sel;

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
#endif

#ifdef SUPPORT_BASS_TREBLE
BYTE ddx_Bass_lev;
BYTE ddx_Treble_lev;
#define MAX_BASSCTRL_LEV 15
#define MAX_TREBLECTRL_LEV 15
#endif


void ddx_initialization(void);
void ddx_enableEPAD(void);
void ddx_disableEPAD(void);
void ddx_masterMute(BYTE mute);
BYTE test_ddx8001(void);
void ddx_set_channel_vol(BYTE ch,BYTE vol);
#ifdef SET_CHANNEL_OFFSET
void set_channel_offset(BYTE ch,BYTE offset);
#endif
#endif
void ddx_set_96k_input();
void ddx_set_48k_input();
void ddx_writeCoefVal(UINT16 regAddr,UINT32 coefVal);
#endif//#ifdef SUPPORT_APOGEE_AMP
