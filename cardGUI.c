/**********************************************************
**  Description: Switch interface for CDROM & CF Card ( after combined with USB) 
**  Creater:wuxiaofeng
**  Date:03-10-30  14:37
***********************************************************/

#ifdef CF_CARD_WRITE
extern void show_switch(void);

void card_copy(BYTE copy_mode)
{
	int copy_status;
//	if(CardIdentify()!=0)//very important!!!
	if(FSIdentify()!=0)//very important!!!
	{
		Message_Show(ERROR_MESSAGE);
		show_switch();
	}
	else
	{
		if(pFsJpeg->gifsFuncBtn == FS_FUNC_MP3)
		{
			sign_PFun=PFUN_WRITE;//write cf card
			AVD_SetMediaInterrupt();//stop the current mp3, Can't be used for JPEG!!
			Message_Show(PFUN_COPYING);
			osd_DrawRegionString(21, 1, "0%", 7, 0, 2);//for show the progress use!!
		}
		else if(pFsJpeg->gifsFuncBtn == FS_FUNC_JPEG)
		{
			sign_PFun=PFUN_WRITE;//write JPEG
			Message_Show(PFUN_COPYING);
//			copy_status=CardSchedule(copy_mode);
			copy_status=FSSchedule(copy_mode);
			if(copy_status==-1)
			{
				Message_Show(P_SPACEFULL);
			}
			else if(copy_status==-2)
			{
				Message_Show(P_NOMATCH);
			}
			else
			{
				Message_Show(PFUN_WRITE);
			}
			full_scrn &= (~PERIPHERAL);//for release the IR
			osd_init();
		}
	}
}

void cd2card(void)
{
	full_scrn &= (~PERIPHERAL);//for release the IR
	osd_init();

	atapi_close_tray(0);//in order to stop loader this calling is somewhat strange
	read_card_sign=1;												   //xulf0827
	flag_cd2cf=1;
	flag_cf2cd=0;
	media_type=MEDIA_CARD;
	ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);
}

void card2cd(void)
{
	full_scrn &= (~PERIPHERAL);//for release the IR
	osd_init();
	
	flag_cd2cf=0;															   //xulf
	flag_cf2cd=1;
	media_type=MEDIA_CD;
	ircmd_post_func(CMD_FUNC | CMD_FUNC_STOP);
	bDiscType=CDUNKNOWN;
	sys_cmd=CMD_FUNC_PLAY;
}

int card_delete(void)
{
//	if(CardIdentify()!=0)//very important!!!
	if(FSIdentify()!=0)//very important!!!
	{
		Message_Show(ERROR_MESSAGE);
		show_switch();
	}
	else
	{
		sign_PFun=PFUN_DELETE;//delete data
//		if(CardSchedule(0)==-1)
		if(FSSchedule(0)==-1)
		{
			Message_Show(P_SPACEEMPTY);
			//turn to CDROM
			card2cd();
			return -1;
		}
		else
		{
			Message_Show(PFUN_DELETE);
		}
	}
	return 0;
}

void format_card(void)
{
//	if(CardIdentify()!=0)//very important!!!
	if(FSIdentify()!=0)//very important!!!
	{
		Message_Show(ERROR_MESSAGE);
		show_switch();
	}
	else
	{
		sign_PFun=PFUN_FORMAT;//format card
//		CardSchedule(0);
		FSSchedule(0);
		Message_Show(PFUN_FORMAT);
	}
}

void rename_cardfile(void)
{
//	if(CardIdentify()!=0)//very important!!!
	if(FSIdentify()!=0)//very important!!!
	{
		Message_Show(ERROR_MESSAGE);
		show_switch();
	}
	else
	{
		sign_PFun=PFUN_RENAME;//Create Dir
//		CardSchedule(0);
		FSSchedule(0);
		Message_Show(PFUN_RENAME);
		cd2card();//refresh the card
	}
}

#endif	
