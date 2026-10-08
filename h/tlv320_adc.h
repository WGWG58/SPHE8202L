#ifndef __TLV320_ADC
	#define __TLV320_ADC
	#ifdef USE_TLV320_ADC
		void TLV320_init(void);		//FCR 03-7-10 15:41
		void ADC_Switch_input(unsigned char Need_add_gain);
		void Unmute_lineout(unsigned char Unmute);	//8:mute DAC,0:ummute dac
	#endif
#endif