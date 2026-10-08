#ifndef __CDG_H
#define __CDG_H

typedef struct
{
    UINT8 command;          //001001 : CD-G command
    UINT8 instruction;
    UINT8 parityQ[2];
    UINT8 data[16];
    UINT8 parityP[4];
} tSubCode;


void CDG_ParseCmd(tSubCode *p);
void CDG_Pause();
void CDG_Init();
void CDG_Stop();
BYTE CDG_IsCDGNow(); //Jeff 20020824

extern  BYTE    *   const   cdg_mem_start;
extern  BYTE    *   const   cdg_mem_dsp;
extern  BYTE    *   const   sub_ch_ptr;

#endif // __CDG_H

