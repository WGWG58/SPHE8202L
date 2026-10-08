#ifndef TLV320_H
#define TLV320_H

//TLV320 IIC Address define
#define	TLV_320_ADDR		0x34

//TLV320 Register address define
#define	light_line_out_channel_volume_control_reg	0x01
#define	left_channel_headphone_volume_control_reg	0x05
#define	analog_audio_path_control_reg				0x08
#define	digital_audio_path_control_reg				0x0a
#define	power_down_control_reg						0x0c
#define digital_audio_interface_format_reg			0x0e
#define	sample_rate_control_reg						0x10
#define	digital_interface_activation_reg			0x12


void use_tlv320_mute_headphone(void);
void set_Digital_Format(int freq_index);
void init_tlv320(void);
void mute_tlv320_line_out(BYTE mute);
void set_tlv320_headphone_volume(BYTE vol);
void dac_set_fs(int freq_index);
void set_tlv320_line_out_volume(BYTE vol);


#endif

