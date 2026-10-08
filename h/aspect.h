#ifndef __ASPECT_H
#define __ASPECT_H

//
// tell TV which kind of signal we are sending now.
//
#define OUTPUT_TV_ASPECT_4_3    (0<<4)
#define OUTPUT_TV_ASPECT_16_9   (1<<4)
#define OUTPUT_TV_ASPECT_14_9   (2<<4)
#define OUTPUT_TV_ASPECT_MASK   (0x0f<<4)
#define OUTPUT_SRC_ASPECT_4_3   (0<<0)
#define OUTPUT_SRC_ASPECT_16_9  (1<<0)
#define OUTPUT_SRC_ASPECT_MASK  (0x03<<0)
#define OUTPUT_ENLARGE          (1<<7)

//
// only following 4 combinations are allowed.
// OUTPUT_ASPECT_NORMAL     4:3 source, output to 4:3 TV
// OUTPUT_ASPECT_ANAMORPHIC 16:9 source, output to 16:9 TV
// OUTPUT_ASPECT_LETTERBOX  16:9 source output to 4:3 TV with letterbox
// OUTPUT_ASPECT_PANSCAN    16:9 source output to 4:3 TV with pan-scan
//
#define OUTPUT_ASPECT_NORMAL            (OUTPUT_TV_ASPECT_4_3|OUTPUT_SRC_ASPECT_4_3)
#define OUTPUT_ASPECT_ANAMORPHIC        (OUTPUT_TV_ASPECT_16_9|OUTPUT_SRC_ASPECT_16_9)
#define OUTPUT_ASPECT_LETTERBOX         (OUTPUT_TV_ASPECT_4_3|OUTPUT_SRC_ASPECT_16_9)
#define OUTPUT_ASPECT_PANSCAN           (OUTPUT_TV_ASPECT_4_3|OUTPUT_SRC_ASPECT_16_9|OUTPUT_ENLARGE)
#define OUTPUT_ASPECT_COMPRESSED        (OUTPUT_TV_ASPECT_16_9|OUTPUT_SRC_ASPECT_4_3)

extern  UINT8   output_aspect;

#define set_output_aspect(v)    (output_aspect=(v))
#define get_output_aspect(v)    (output_aspect)

//
// in NTSC, the WSS should send:
// OUTPUT_ASPECT_NORMAL     00: normal
// OUTPUT_ASPECT_ANAMORPHIC 01: anamorphic
// OUTPUT_ASPECT_LETTERBOX  10: letterbox
// OUTPUT_ASPECT_PANSCAN    00: normal (pan-scan enlarged)
//
// in PAL, the WSS should send:
// OUTPUT_ASPECT_NORMAL     1000: normal
// OUTPUT_ASPECT_ANAMORPHIC 0111: anamorphic
// OUTPUT_ASPECT_LETTERBOX  1011: letterbox
// OUTPUT_ASPECT_PANSCAN    1000: normal (pan-scan enlarged)
//
//

#endif/*__ASPECT_H*/

