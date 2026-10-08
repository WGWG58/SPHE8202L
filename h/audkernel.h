#ifndef __AUDKRNL_H__
#define __AUDKRNL_H__

#include "global.h"
#include "types.h"

#include "audclk.h"
#include "audcodec.h"
#include "dsp3rom.h"

#include "auddef.h"
#include "dsp3_def.h"
/***********************************************************************
 *  Define Session
 ***********************************************************************/

UINT32 pl2_init_val;

#ifdef MESSAGE_QUEUE
enum _Q_CMD_TYPE_
{
    Q_EMPTY=0,          //no command in queue
    Q_CMD_STATUSACK,    //status waiting command in queue
    Q_CMD_GENERALACK,   //general waiting command in queue
    Q_CMD_OTHER,        //other command
}Q_CMD_TYPE;

extern UINT8 cmd_in_use; // INT32 cmd_in_use;
extern INT32 wait_cmd_count;
#endif
/***********************************************************************
 *  Debug related Session
 ***********************************************************************/
#define auddbg_puts(s) ((void)0)
#define auddbg_printf(s...) ((void)0)
#ifdef AUDKRNL_DBG

#include "sio.h"
#include "emuio.h"
#define MONE_DOWNLOAD_CODEC

extern BYTE linebuf[100];

#undef  auddbg_puts
#undef  auddbg_printf
#define auddbg_puts(s)   io_write(s)
#define auddbg_printf(s...)\
        do {\
        psprintf(linebuf, ##s); io_write(linebuf);\
        } while (0)
#endif

/***********************************************************************
 *  Declaration Session
 ***********************************************************************/
void AUDKRNL_Init_AudHW_CLK(void);
void AUDKRNL_Set_AudHW_SmpRate(unsigned fs);

INT16 AUDKRNL_Download_DSP3Codec(const BYTE *rom, int len); //(int dsp3_coding_mode);
void AUDKRNL_Download_Codec(int coding_mode);

//return: 0:fail, 1:success
// 2005.04.06 Oliver #if defined(SUPPORT_SOUND_EFFECT) || defined(MESSAGE_QUEUE)
#if defined(SUPPORT_SOUND_EFFECT)
int DSP_AudioIOControl(UINT8 wCode, UINT32 cType, UINT32 wParam);
#else
//int DSP_AudioIOControl(UINT16 wCode, BYTE cType, UINT16 wParam);
int DSP_AudioIOControl(UINT8 wCode, UINT8 cType, UINT16 wParam);
#endif

#if defined(SUPPORT_MIDI) && !defined(MESSAGE_QUEUE)
//int DSP_Midi_AudioIOControl(UINT16 wCode, BYTE cType, UINT16 wParam); // MidiAudioCtrl
int DSP_Midi_AudioIOControl(UINT8 wCode, UINT8 cType, UINT16 wParam);
#endif
//return: -1: error, others
//extern int AudioIOStatus(UINT16 wCode);

#ifdef MESSAGE_QUEUE
void DSPKRNL_Reset_MQ(); // reset_cmdQ_offset
//INT32 DSPKRNL_Push_MQ(UINT16 order, UINT32 parm1, UINT32 parm2); // put_cmd_to_Q
INT32 DSPKRNL_Push_MQ(UINT8 order, UINT8 parm1, UINT16 parm2);
INT32 DSPKRNL_Rmv_cmd_from_MQ(void); // rmv_cmd_from_Q
//INT32 DSPKRNL_Chk_cmd_in_MQ(UINT16 *order, UINT32 *parm1, UINT32 *parm2); // check_cmd_in_Q
INT32 DSPKRNL_Chk_cmd_in_MQ(UINT8 *order, UINT8 *parm1, UINT16 *parm2); // check_cmd_in_Q

int exe_MidiIoCtrl(UINT16 wCode, BYTE cType, UINT16 wParam);
//int DSPKRNL_Exe_AudioIOCmd(UINT16 wCode, UINT32 cType, UINT32 wParam); // exe_audioIO_cmd
int DSPKRNL_Exe_AudioIOCmd(UINT8 wCode, UINT8 cType, UINT16 wParam);
#endif

UINT32 AUDKRNL_LPCM_Get_BitDepthParam(UINT32 bitsample);
UINT32 AUDKRNL_LPCM_Get_FrqParam(UINT32 samprate);

//ycwen 2005/11/15 use fun pointer to make auddrv.a clear!
extern void (*internal_dac_setting)();
extern void (*internal_dac_reset)();

/*============================================================*/
// To ease the control of audio clocks,
// currently PCMBCK, IECBCK, ADCBCK all source from XCK.
// as a result, when changing sampling frequency, only XCK change is need.
//
// note: if there are needs for enable/disable individual clocks
// we must increase other interfaces
/*============================================================*/
//ycwen 2005/11/14 move from audkernel.c to audkernel.h
static const UINT16 int_xck_clk_fs_table[] =
{
    AUDCLK_128XCK_04096, AUDCLK_128XCK_05644, AUDCLK_128XCK_06144, 0, 0,
    AUDCLK_128XCK_11290, AUDCLK_128XCK_12288, 0, 0,
    AUDCLK_128XCK_22579, AUDCLK_128XCK_24576, 0, 0
};	

#ifndef SPHE1000
    #ifdef SUPPORT_384_XCK //defined in user_init.h
        static const UINT16 xck_clk_fs_table[] =
        {
            AUDCLK_384XCK_12288, AUDCLK_384XCK_16934, AUDCLK_384XCK_18432, 0, 0,
            AUDCLK_384XCK_33869, AUDCLK_384XCK_36864, 0, 0,
            AUDCLK_384XCK_67736, AUDCLK_384XCK_73728, 0, 0
        };
        #define	AUD_BCK_SETTING AUDCLK_64BCK_384
        #define	AUD_IEC_SETTING	AUDCLK_128IEC_384
        #define	AUD_ADC_SETTING	AUDCLK_64ADC_384
    #else // 256fs
        static const UINT16 xck_clk_fs_table[] =
        {
            AUDCLK_256XCK_08192, AUDCLK_256XCK_11290, AUDCLK_256XCK_12288, 0, 0,
            AUDCLK_256XCK_22579, AUDCLK_256XCK_24576, 0, 0,
            AUDCLK_256XCK_45158, AUDCLK_256XCK_49152, 0, 0
        };
        #define	AUD_BCK_SETTING AUDCLK_64BCK_256
        #define	AUD_IEC_SETTING	AUDCLK_128IEC_256
        #define	AUD_ADC_SETTING	AUDCLK_64ADC_256
    #endif
#else // SPHE1000
    #ifdef	SUPPORT_384_XCK	//defined in user_init.h
        static const UINT16 xck_clk_fs_table[] =
        {
            AUDCLK_384XCK_12288, AUDCLK_384XCK_18432, AUDCLK_384XCK_18432, 0, 0,
            AUDCLK_384XCK_36864, AUDCLK_384XCK_36864, 0, 0,
            AUDCLK_384XCK_73728, AUDCLK_384XCK_73728, 0, 0
        };
        #define	AUD_BCK_SETTING	AUDCLK_64BCK_384
        #define	AUD_IEC_SETTING	AUDCLK_128IEC_384
        #define	AUD_ADC_SETTING	AUDCLK_64ADC_384
    #else		// 256fs
        static const UINT16 xck_clk_fs_table[] =
        {
            AUDCLK_256XCK_08192, AUDCLK_256XCK_12288, AUDCLK_256XCK_12288, 0, 0,
            AUDCLK_256XCK_24576, AUDCLK_256XCK_24576, 0, 0,
            AUDCLK_256XCK_49152, AUDCLK_256XCK_49152, 0, 0
        };
        #define	AUD_BCK_SETTING	AUDCLK_64BCK_256
        #define	AUD_IEC_SETTING	AUDCLK_128IEC_256
        #define	AUD_ADC_SETTING	AUDCLK_64ADC_256
    #endif //#ifdef SUPPORT_384_XCK
#endif //#ifndef SPHE1000

#define	INT_AUD_BCK_SETTING AUDCLK_64BCK_128
	  
#endif //#ifdef __AUDKRNL_H__

