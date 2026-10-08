

const  BYTE encoding_system_0001[] = 
{

};

const  BYTE encoding_language_0002[] = 
{

};

const  BYTE encoding_speaker_0005[] = 
{

};


const  BYTE encoding_digit_0006[] = 
{

};

const BYTE *const Icon_table[]={
	encoding_system_0001,
	encoding_language_0002,
	encoding_audio_0003,
	encoding_video_0004,
	encoding_speaker_0005,
	encoding_digit_0006,
};


/* prev */
const BYTE encoding_prev_0000[] = 
{

};

/* next */
const BYTE encoding_next_0001[] = 
{

};

/* play */
const BYTE encoding_play_0002[] = 
{

};

/* || */
const BYTE encoding_pause_0003[] = 
{

};

/* step */
const BYTE encoding_step_0004[] = 
{

};

/* stop */
const BYTE encoding_stop_0005[] = 
{

};

/* pre-stop */
const BYTE encoding_pre_stop_0006[] = 
{

};

/* backward */
const BYTE encoding_backward_0007[] = 
{

};

/* forward */
const BYTE encoding_forward_0008[] = 
{

};

/* slow_backward */
const BYTE encoding_slow_backward_0009[] = 
{

};
//#ifdef NEW_STYLE_SETUP  //zhaoyanhua add 3-7-13 14:29
const BYTE encoding_hand_0001[] = 
{

};

const BYTE encoding_mic_0009[] = 
{


};       //xyy 2003-11-19 9:29
//#endif  //end NEW_STYLE_SETUP

const BYTE *const fn_icon[] = 
{
	encoding_prev_0000,		//0x00  prev // treat as dummy data
	encoding_next_0001,		//0x01  next
	encoding_play_0002,		//0x02  play
	encoding_pause_0003,	//0x03  ||
	encoding_step_0004,		//0x04  step
	encoding_stop_0005,		//0x05  stop
	encoding_pre_stop_0006,	//0x06  pre-stop
	encoding_backward_0007,	//0x07  backward
	encoding_forward_0008,	//0x08  forward
	encoding_slow_backward_0009,	//0x09  slow_0backward
	encoding_prev_0000,		//0x00  prev
	//zhaoyanhua add 3-7-14 13:19
	encoding_hand_0001,     //0x0b  hand for setup menu  
    encoding_mic_0009,      //0x0c     //xyy 2003-11-19 9:07
};

