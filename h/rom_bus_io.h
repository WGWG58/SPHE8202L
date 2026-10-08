
#ifndef ROM_BUS_IO_H
#define ROM_BUS_IO_H


enum    {
    ROM_BUS_OUT_CCB_CEN,
    ROM_BUS_OUT_CCB_CLK,
    ROM_BUS_OUT_CCB_DO,
    ROM_BUS_OUT_AMP_MUTE,
    ROM_BUS_OUT_SEL_A,
    ROM_BUS_OUT_SEL_B,
    #ifdef USE_ROM_EXT_DET_HEADPHONE    //hongfeng 2005-08-01
    ROM_BUS_OUT_HEADPHONE_MUTE,
    ROM_BUS_OUT_HEADPHONE_SELECT,
    #else
    ROM_BUS_OUT_TUNER_ON,
    ROM_BUS_OUT_AMP_STB,
    #endif
}ROM_BUS_OUT;

enum{
    ROM_BUS_IN_RDS_DATA,
    ROM_BUS_IN_RDS_CLK,
    ROM_BUS_IN_CCB_DI,
    ROM_BUS_IN_TUNE_LED,
    ROM_BUS_IN_ST_LED,
    #ifdef USE_ROM_EXT_DET_HEADPHONE
    ROM_BUS_IN_PHONE_DET,   //hongfeng add for OP 2005-07-29
    ROM_BUS_IN_LINE_DET,    //hongfeng add for OP 2005-07-29
    #endif
}ROM_BUS_IN;



void rom_bus_set_io(BYTE io_id,BYTE d);
BYTE rom_bus_get_io(BYTE io_id);

void tuner_power_set(BYTE d);
void audio_sel_tuner(void);
void audio_sel_aux1(void);
void audio_sel_aux2(void);
void audio_sel_mic(void);
void audio_sel_gnd(void);
#ifdef ADC_EXT_RESET
void reset_ext_adc(void);
#endif

#ifdef USE_ROM_EXT_DET_HEADPHONE
BYTE rom_ext_detect_headphone(void);
void rom_ext_select_headphone(void);
#endif
#endif  //#define ROM_BUS_IO_H

