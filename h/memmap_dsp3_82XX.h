#ifndef _MEMCFG_DSP3_82XX_H_
#define _MEMCFG_DSP3_82XX_H_

// **************************************************************************************** //
// * AC3 Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.ac3.5.1ch.16M            (16M)
#define DSP3_AC3_5_1CH_16M_IM           19      // 19K
#define DSP3_AC3_5_1CH_16M_DM           37      // 36.2K
#define DSP3_AC3_5_1CH_16M_PM           9       // 9K

// dsp3rom.d16.ac3.raw.analog.2ch       (16M)
#define DSP3_AC3_RAW_ANALOG_2CH_IM      18      // 17.4K
#define DSP3_AC3_RAW_ANALOG_2CH_DM      27      // 27K
#define DSP3_AC3_RAW_ANALOG_2CH_PM      9       // 9K

// dsp3rom.d16.ac3.2ch                  (16M)
#define DSP3_AC3_2CH_IM                 17      // 16.8K
#define DSP3_AC3_2CH_DM                 18      // 18K
#define DSP3_AC3_2CH_PM                 9       // 9K

// dsp3rom.d16.945.ac3                  (32M)
#define DSP3_945_AC3_IM                 36      // 35.9K
#define DSP3_945_AC3_DM                 162     // 161.1K
#define DSP3_945_AC3_PM                 39      // 38.7K

// dsp3rom.d16.ac3                      (32M)
#define DSP3_AC3_IM                     38      // 38K
#define DSP3_AC3_DM                     169     // 161.1K
#define DSP3_AC3_PM                     39      // 38.7K

// **************************************************************************************** //
// * CD Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.cd.2ch                   (16M)
#define DSP3_CD_2CH_IM                  8       // 7.5K
#define DSP3_CD_2CH_DM                  16      // 15.8K
#define DSP3_CD_2CH_PM                  9       // 9K

// dsp3rom.d16.cd                       (32M)
#define DSP3_CD_IM                      24      // 23.6K
#define DSP3_CD_DM                      162     // 162K
#define DSP3_CD_PM                      9       // 9K

// dsp3rom.d16.cd.mp3.encoder           (16M/32M)  
#define DSP3_CD_MP3_ENCODER_IM         18      // 18K
#define DSP3_CD_MP3_ENCODER_DM         69      // 61K
#define DSP3_CD_MP3_ENCODER_PM         18      // 18K


// **************************************************************************************** //
// * LPCM Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.lpcm.2ch.eq.16M          (16M)
#define DSP3_LPCM_2CH_EQ_16M_IM         15      // 14.4K
#define DSP3_LPCM_2CH_EQ_16M_DM         34      // 33.3K
#define DSP3_LPCM_2CH_EQ_16M_PM         12       // 12k

// dsp3rom.d16.lpcm.2ch                 (16M)
#define DSP3_LPCM_2CH_IM                13      // 12.6K
#define DSP3_LPCM_2CH_DM                34      // 33.3K
#define DSP3_LPCM_2CH_PM                12       // 12K

// dsp3rom.d16.lpcm.fudo                (32M)
#define DSP3_LPCM_FUDO_IM               37      // 36.2K
#define DSP3_LPCM_FUDO_DM               4096    // 4096K
#define DSP3_LPCM_FUDO_PM               12       // 12K

// dsp3rom.d16.lpcm                     (32M)
#define DSP3_LPCM_IM                    46      // 46K
#define DSP3_LPCM_DM                    161     // 161K
#define DSP3_LPCM_PM                    12       // 12K

// **************************************************************************************** //
// * DTS Codec Setup
// **************************************************************************************** //

// ##################
// dsp3rom.d16_dts.dts                  (32M)
#define DSP3_DTS_DTS_IM                 33      // 33K
#define DSP3_DTS_DTS_DM                 48      // 48K
#define DSP3_DTS_DTS_PM                 50      // 50K

// dsp3rom.d16.945.dts(8200)            (32M)
#define DSP3_945_DTS_IM                 26      // 25.9K
#define DSP3_945_DTS_DM                 165     // 165K
#define DSP3_945_DTS_PM                 20      // 19.3K

// dsp3rom.d16.dts.8200                 (32M)
//#define DSP3_DTS_8200_IM                27      // 26.3K
//#define DSP3_DTS_8200_DM                165     // 165K
//#define DSP3_DTS_8200_PM                20      // 19.3K
#define DSP3_DTS_8200_IM                27      // 26.3K
#define DSP3_DTS_8200_DM                165     // 165K
#define DSP3_DTS_8200_PM                25      // 19.3K

// dsp3rom.d16.dts.8202                 (32M)
#define DSP3_DTS_8202_IM                27      // 26.6K
#define DSP3_DTS_8202_DM                196     // 195.2K
#define DSP3_DTS_8202_PM                12      // 12K

// dsp3rom.d16.dts.5.1ch.16M(8202)      (16M)
#define DSP3_DTS_5_1CH_16M_IM           13      // 13K
#define DSP3_DTS_5_1CH_16M_DM           42      // 42K
#define DSP3_DTS_5_1CH_16M_PM           9       // 9K

// **************************************************************************************** //
// * NES Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.nes.2ch                  (16M)
#define DSP3_NES_2CH_IM                 5       // 4.9K
#define DSP3_NES_2CH_DM                 19      // 18.5K
#define DSP3_NES_2CH_PM                 9       // 9K

// dsp3rom.d16.nes                      (32M)
#define DSP3_NES_IM                     5       // 4.9K
#define DSP3_NES_DM                     48      // 47.7K
#define DSP3_NES_PM                     9       // 9K

// **************************************************************************************** //
// * SPDIF Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.spdif.dts                (16M)
#define DSP3_SPDIF_ONLY_DTS_IM          4       // 3.1K
#define DSP3_SPDIF_ONLY_DTS_DM          25      // 24.8K
#define DSP3_SPDIF_ONLY_DTS_PM          17      // 16.8K

// dsp3rom.d16.spdif.2ch                (16M)
#define DSP3_SPDIF_2CH_IM               6       // 5.5K
#define DSP3_SPDIF_2CH_DM               27      // 24.8K
#define DSP3_SPDIF_2CH_PM               17      // 16.8K
/*
// dsp3rom.d16.spdif                    (32M)
#define DSP3_SPDIF_IM                   6       // 5.5K
#define DSP3_SPDIF_DM                   25      // 24.8K
#define DSP3_SPDIF_PM                   17      // 16.8K
*/
// **************************************************************************************** //
// * DTSCD Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.raw.dtscd(8200)          (32M)
#define DSP3_RAW_DTSCD_IM               28      // 27.2K
#define DSP3_RAW_DTSCD_DM               166     // 166K
#define DSP3_RAW_DTSCD_PM               20      // 19.3K

// dsp3rom.d16.108.dtscd 
#define DSP3_108_DTSCD_IM               25      // 24.5K
#define DSP3_108_DTSCD_DM               160     // 160K
#define DSP3_108_DTSCD_PM               20      // 19.3K

// dsp3rom.d16.dtscd(8200)              (32M)
#define DSP3_DTSCD_IM                   26      // 25.8K
#define DSP3_DTSCD_DM                   146     // 145.5K
#define DSP3_DTSCD_PM                   20      // 19.3K

// **************************************************************************************** //
// * WMA Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.wma.2ch                  (16M)
#define DSP3_WMA_2CH_IM                 33      // 32.4K
#define DSP3_WMA_2CH_DM                 48      // 47.6K
#define DSP3_WMA_2CH_PM                 35      // 34.4K

// dsp3rom.d16.wma                      (32M)
#define DSP3_WMA_IM                     48      // 48K
#define DSP3_WMA_DM                     199     // 198.4K
#define DSP3_WMA_PM                     35      // 34.4k

// **************************************************************************************** //
// * PPCM Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.ppcm                     (32M)
#define DSP3_PPCM_IM                    24      // 24K
#define DSP3_PPCM_DM                    90      // 90K
#define DSP3_PPCM_PM                    9       // 9K

// **************************************************************************************** //
// * SPG Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.spg                     (32M)
#define DSP3_SPG_IM                     31      // 31K
#define DSP3_SPG_DM                     199     // 198.9K
#define DSP3_SPG_PM                     9       // 9K

// **************************************************************************************** //
// * MP3 Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.mp3.2ch.EQ.16M           (16M)
#define DSP3_MP3_2CH_EQ_16M_IM          22      // 21.6K
#define DSP3_MP3_2CH_EQ_16M_DM          32      // 31.7K
#define DSP3_MP3_2CH_EQ_16M_PM          11      // 10.5K

// dsp3rom.d16.mp3.2ch                  (16M)
#define DSP3_MP3_2CH_IM                 21      // 20.2K
#define DSP3_MP3_2CH_DM                 32      // 31.7K
#define DSP3_MP3_2CH_PM                 11      // 10.5K

// dsp3rom.d16.mp3.mix                  (32M)
#define DSP3_MP3_MIX_IM                 43      // 40.8K
#define DSP3_MP3_MIX_DM                 147     // 104.5K
#define DSP3_MP3_MIX_PM                 11      // 10.3K

// dsp3rom.d16.mp3.jpg                  (32M)
#define DSP3_MP3_JPG_IM                 42      // 40.3K
#define DSP3_MP3_JPG_DM                 144     // 143.1K
#define DSP3_MP3_JPG_PM                 60      // NON_DTS_AUDIO_BITSTREAM_LEN in dsp3_config.c

// dsp3rom.d16.mp3                      (32M)
#define DSP3_MP3_IM                     42      // 39.4K
#define DSP3_MP3_DM                     147     // 104.5K
#define DSP3_MP3_PM                     14      // 10.3K

// dsp3rom.d16.mp3.6ch                  (32M)
#define DSP3_MP3_6CH_IM                  42
#define DSP3_MP3_6CH_DM                  147
#define DSP3_MP3_6CH_PM                  14
// **************************************************************************************** //
// * AAC Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.aac                      (32M)
#define DSP3_AAC_IM                     20     // 20K	//wrwu 2005/02/17, add for MPEG4AAC
#define DSP3_AAC_DM                     90      // 90K
#define DSP3_AAC_PM                     9       // 9K

// **************************************************************************************** //
// * HDCD Codec Setup
// **************************************************************************************** //

// ##################
// dsp3rom.d16.hdcd
#define DSP3_HDCD_IM                    26      // 25.8K
#define DSP3_HDCD_DM                    261     // 261K
#define DSP3_HDCD_PM                    20      // 19.2K

// **************************************************************************************** //
// * MIDI Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.midi                     (32M)
#define DSP3_MIDI_IM                    29      // 28.3K
#define DSP3_MIDI_DM                    4429    // 4429KBs = 141KBs(47K words) + 4288KBs wavetable
#define DSP3_MIDI_PM                    200     // 

// **************************************************************************************** //
// * SPI Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.cd.spi.8200             (32M)
#define DSP3_SPDIFINCD_8200_IM          22      // 21.7K
#define DSP3_SPDIFINCD_8200_DM          163     // 151.4K
#define DSP3_SPDIFINCD_8200_PM          9       // 9K

// dsp3rom.d16.cd.spi.8202             (32M)
#define DSP3_SPDIFINCD_8202_IM          DSP3_SPDIFINCD_8200_IM
#define DSP3_SPDIFINCD_8202_DM          DSP3_SPDIFINCD_8200_DM
#define DSP3_SPDIFINCD_8202_PM          DSP3_SPDIFINCD_8200_PM

// dsp3rom.d16.ac3.spi.8200             (32M)
#define DSP3_SPDIFINAC3_8200_IM         39      // 38.3K
#define DSP3_SPDIFINAC3_8200_DM         161     // 160.5K
#define DSP3_SPDIFINAC3_8200_PM         49      // 48.8K

// dsp3rom.d16.ac3.spi.8202            (32M)
#define DSP3_SPDIFINAC3_8202_IM         DSP3_SPDIFINAC3_8200_IM
#define DSP3_SPDIFINAC3_8202_DM         DSP3_SPDIFINAC3_8200_DM
#define DSP3_SPDIFINAC3_8202_PM         DSP3_SPDIFINAC3_8200_PM

// dsp3rom.d16.dts.spi.8200             (32M)
#define DSP3_SPDIFINDTS_8200_IM         29      // 28.5K
#define DSP3_SPDIFINDTS_8200_DM         185     // 185K
#define DSP3_SPDIFINDTS_8200_PM         49      // 48.8K

// dsp3rom.d16.dts.spi.8202             (32M)
#define DSP3_SPDIFINDTS_8202_IM         29      // 28.8K
#define DSP3_SPDIFINDTS_8202_DM         200     // 199.3K
#define DSP3_SPDIFINDTS_8202_PM         49      // 48.8K

// **************************************************************************************** //
// * TUNER Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.tuner                    (32M)
#define DSP3_TUNER_IM                   19      // 18.7K
#define DSP3_TUNER_DM                   170     // 170K
#define DSP3_TUNER_PM                   9       // 9K

// **************************************************************************************** //
// * NOISE Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.noise                    (32M)
#define DSP3_NOISE_IM                   5       // 4.1K
#define DSP3_NOISE_DM                   85      //84.1K
#define DSP3_NOISE_PM                   17      // 16.9K

// **************************************************************************************** //
// * NOISE Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.noise.8200                    (32M)
#define DSP3_NOISE_8200_IM                   5       // 4.1K
#define DSP3_NOISE_8200_DM                   85      //84.1K
#define DSP3_NOISE_8200_PM                   17      // 16.9K

// **************************************************************************************** //
// * OGG Codec Setup
// **************************************************************************************** //

// dsp3rom.d16.ogg                    (32M)
#define DSP3_OGG_IM                   20       // 
#define DSP3_OGG_DM                   179      //
#define DSP3_OGG_PM                   9        // 

#endif

