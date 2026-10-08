/*
** FILE
** sysmain_midi.inc
*/

#ifdef SUPPORT_MIDI //Jeff 20040827
// 
//len : return 0 -> descramble error, system will halt
UINT32  MidiPreDesc(BYTE *pSrc, BYTE *pDst, UINT32 len)
{
    int     i;
    
    for (i=0; i<len; i++) {
        *(pDst+i) = *(pSrc+i);
    }

    return len;
}
#endif


