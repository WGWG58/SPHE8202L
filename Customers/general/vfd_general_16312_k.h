/*File: vfd_v.h 
creater:kenny 891109
for vfd key mapping 

*/   


//kenny add it 891109
#if 0
const BYTE vfd_keycode[40]=
{
	IRC_NEXT,             IRC_PREV ,           //1,2
	IRC_FORWARD,            IRC_BACKWARD ,       //3,4
	IRC_RETURN,             IRC_PBC ,           //5,6
	IRC_STOP,               IRC_PLAY ,     //7,8
	IRC_NULL,               IRC_NULL ,           //9,10
	IRC_NULL,               IRC_NULL ,        //11,12
	IRC_NULL,               IRC_NULL ,           //13,14
	IRC_NULL,               IRC_EJECT ,     //15,16
	IRC_NULL,               IRC_NULL ,           //17,18
	IRC_NULL,                IRC_NULL ,     //19,20
	IRC_NULL,             IRC_NULL ,           //21,22
	IRC_NULL,             IRC_NULL ,   //23,24
	IRC_NULL ,            IRC_NULL,      //25,26
	IRC_NULL,             IRC_NULL ,     //27,28
	IRC_NULL,             IRC_NULL ,     //29,30
	IRC_NULL,             IRC_NULL ,     //31,32
	IRC_NULL,             IRC_NULL ,     //33,34
	IRC_NULL,             IRC_NULL ,     //35,36
	IRC_NULL,             IRC_NULL ,     //37,38
	IRC_NULL,             IRC_NULL       //39,40
};
#elif 1
const BYTE vfd_keycode[40]=
{
	IRC_EJECT,             IRC_STOP ,           //1,2
	IRC_NEXT,             IRC_NULL ,       //3,4
	IRC_PAUSEPLAY,             IRC_PREV ,           //5,6
	IRC_PBC,               IRC_RETURN ,     //7,8
	IRC_NULL,               IRC_NULL ,           //9,10
	IRC_NULL,               IRC_NULL ,        //11,12
	IRC_NULL,               IRC_NULL ,           //13,14
	IRC_NULL,             IRC_NULL ,     //15,16
	IRC_NULL,               IRC_NULL ,           //17,18
	IRC_NULL,                IRC_NULL ,     //19,20
	IRC_NULL,             IRC_NULL ,           //21,22
	IRC_NULL,             IRC_NULL ,   //23,24
	IRC_NULL ,            IRC_NULL,      //25,26
	IRC_NULL,             IRC_NULL ,     //27,28
	IRC_NULL,             IRC_NULL ,     //29,30
	IRC_NULL,             IRC_NULL ,     //31,32
	IRC_NULL,             IRC_NULL ,     //33,34
	IRC_NULL,             IRC_NULL ,     //35,36
	IRC_NULL,             IRC_NULL ,     //37,38
	IRC_NULL,             IRC_NULL       //39,40
};//for yx-823a nono 1-12-12 21:56
#elif 0
const BYTE vfd_keycode[40]=
{
	IRC_PREV,             IRC_NULL ,           //1,2
	IRC_NULL,             IRC_PLAY_RESUME ,       //3,4
	IRC_NEXT,             IRC_NULL ,           //5,6
	IRC_NULL,             IRC_EJECT ,     //7,8
	IRC_NULL,               IRC_NULL ,           //9,10
	IRC_NULL,               IRC_NULL ,        //11,12
	IRC_STOP,               IRC_NULL ,           //13,14
	IRC_NULL,               IRC_PAUSE ,     //15,16
	IRC_NULL,               IRC_NULL ,           //17,18
	IRC_NULL,                IRC_NULL ,     //19,20
	IRC_NULL,             IRC_NULL ,           //21,22
	IRC_NULL,             IRC_NULL ,   //23,24
	IRC_NULL ,            IRC_NULL,      //25,26
	IRC_NULL,             IRC_NULL ,     //27,28
	IRC_NULL,             IRC_NULL ,     //29,30
	IRC_NULL,             IRC_NULL ,     //31,32
	IRC_NULL,             IRC_NULL ,     //33,34
	IRC_NULL,             IRC_NULL ,     //35,36
	IRC_NULL,             IRC_NULL ,     //37,38
	IRC_NULL,             IRC_NULL       //39,40
};//for yx-822A 2-4-22 17:23
#elif 0
const BYTE vfd_keycode[40]=
{
	IRC_PREV,             IRC_NEXT ,           //1,2
	IRC_FORWARD,          IRC_BACKWARD,       //3,4
	IRC_PAUSEPLAY,        IRC_STOP,           //5,6
	IRC_PBC,              IRC_EJECT,     //7,8
	IRC_RETURN,           IRC_SELECT,           //9,10
	IRC_UP,               IRC_DOWN ,        //11,12
	IRC_LEFT,             IRC_RIGHT ,           //13,14
	IRC_AUD_LANGUAGE,     IRC_SUBP ,     //15,16
	IRC_3D,            IRC_TITLEMENU,           //17,18
	IRC_CHANNEL,          IRC_FORMAT ,     //19,20
	IRC_POWER,            IRC_VOLUME_UP,           //21,22
	IRC_VOLUME_DN,        IRC_KARAOKE,   //23,24
	IRC_NULL ,            IRC_NULL,      //25,26
	IRC_NULL,             IRC_NULL ,     //27,28
	IRC_NULL,             IRC_NULL ,     //29,30
	IRC_NULL,             IRC_NULL ,     //31,32
	IRC_NULL,             IRC_NULL ,     //33,34
	IRC_NULL,             IRC_NULL ,     //35,36
	IRC_NULL,             IRC_NULL ,     //37,38
	IRC_NULL,             IRC_NULL       //39,40
};//for yx-822BC... 2-8-15 14:32
#endif
