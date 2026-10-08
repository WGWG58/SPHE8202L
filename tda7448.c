#ifdef TDA7448
#define TDA7448_ADDR  0x8a
/*
  according to the TDA7448 datasheet.
  this function translate the 0--79dB to a data that TDA7448 can be accepted
  the real attenuation value = lower 3bit + (8 * higher 5 bits)
  but how about reverse????
  for example
   input: 9
   out   : 0x05
*/
BYTE coverDB(BYTE db)
{
	BYTE lower3,higher5,data;
	lower3 = db%8;
	higher5 = db/8;
	data = ((higher5<<3) | lower3);
	return data;
}

/*
channel: 1--6
 vol:0-->79dB
*/
void subvol_channel_volume(BYTE channel,BYTE vol)
{
	BYTE data1,data2;
	int res;

	vol = 79 -vol;
	data1 = channel-1;
	data2 = coverDB(vol);
	res = WriteToI2c(TDA7448_ADDR,data1,&data2,1);
}

#endif  //TDA7448

