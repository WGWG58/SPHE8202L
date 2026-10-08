#ifdef INTECH_PANEL_5600_KEY
const BYTE vfd_keycode[40]=
{
	IRC_PAUSEPLAY,          	IRC_STOP,           //1,2
	IRC_EJECT,               IRC_PREV ,       //3,4
	IRC_CHANNEL,              	IRC_FORWARD,           //5,6
	IRC_PLAY,               IRC_BACKWARD,     //7,8
	IRC_NULL,               IRC_NULL ,           //9,10
	IRC_NULL,               IRC_NULL ,        //11,12
	IRC_NULL,               IRC_NULL ,           //13,14
	IRC_NULL,               IRC_NULL ,     //15,16
	IRC_NULL,               IRC_NULL ,           //17,18
	IRC_NULL,               IRC_NULL ,     //19,20
	IRC_NULL,               IRC_NULL ,           //21,22
	IRC_NULL,               IRC_NULL ,   //23,24
	IRC_NULL ,              IRC_NULL,      //25,26
	IRC_NULL,               IRC_NULL ,     //27,28
	IRC_NULL,               IRC_NULL ,     //29,30
	IRC_NULL,               IRC_NULL ,     //31,32
	IRC_NULL,               IRC_NULL ,     //33,34
	IRC_NULL,               IRC_NULL ,     //35,36
	IRC_NULL,               IRC_NULL ,     //37,38
	IRC_NULL,               IRC_NULL       //39,40
};
#else
const BYTE vfd_keycode[40]=
{
	IRC_4,          	IRC_BACKWARD,           //1,2
	IRC_PREV,               IRC_1 ,       //3,4
	IRC_3,              	IRC_NEXT,           //5,6
	IRC_PAUSEPLAY,               IRC_2,     //7,8
	IRC_NULL,               IRC_NULL ,           //9,10
	IRC_NULL,               IRC_NULL ,        //11,12
	IRC_STOP,               IRC_EJECT ,           //13,14
	IRC_CHANNEL,               IRC_FORWARD ,     //15,16
	IRC_NULL,               IRC_NULL ,           //17,18
	IRC_NULL,               IRC_NULL ,     //19,20
	IRC_NULL,               IRC_NULL ,           //21,22
	IRC_NULL,               IRC_NULL ,   //23,24
	IRC_NULL ,              IRC_NULL,      //25,26
	IRC_NULL,               IRC_NULL ,     //27,28
	IRC_NULL,               IRC_NULL ,     //29,30
	IRC_NULL,               IRC_NULL ,     //31,32
	IRC_NULL,               IRC_NULL ,     //33,34
	IRC_NULL,               IRC_NULL ,     //35,36
	IRC_NULL,               IRC_NULL ,     //37,38
	IRC_NULL,               IRC_NULL       //39,40
};
#endif
