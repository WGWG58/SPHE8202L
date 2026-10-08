// polling PS/2 interface
//created by JSLin  //20041022
//well, basically, this file will be included when you defined SUPPORT_PS2 in cfg_xxxxxx.h

//#ifdef  POLLING_DBG
#define MONE_PS2_MOUSE
//#endif

#define X_Pos_Max  340
#define Y_Pos_Max  230

#if !defined( SUPPORT_GAMEPAD_MOUSE) && !defined (SUPPORT_USB_HID) //liulifeng  for usb mouse  20050920
#define	SendInitCMD_M_0	0
#define	SendInitCMD_M_1	1
#define	InitCMD_M_End		2
#define	SendInitCMD_M_Fail	3

#define	Response_M_OK		1
#define	Response_M_Faile	0

#define	Enable_M_Read		1
#define	Disable_M_Read		0

// PS/2 mouse command
#define	RESET_M			0xff
#define	WorkMod_M			0xEA	//StreamMode 0xEA; RemoteMode 0xF0; WrapMode 0xEC
#define	Read_Dev_type		0xF2	//read mouse type, receiver 0xFA; standard mouse 0x00; other mouse ....
#define	SetSampl_M			0xF3	//set sample rate
#define	SamplRat_M			0x28	//10/sec 0x0A; 20/sec 0x14;40/sec 0x28;60/sec 0x3c;80/sec 0x50;100/sec 0x64;200/sec 0xC8
#define	Enable_M			0xF4	//enable mouse working
#define	MouseInitEnd		0x00
#endif

#ifdef SUPPORT_GAMEPAD_MOUSE
extern int ReadGamePad(void);
#elif defined (SUPPORT_USB_HID)
extern UINT8 Read_USB_Mouse(UINT8 *pData);
#else
void checkMouseEvent(void);
void resetMouse(void);
#endif

void polling_mouse(void);
void updateMouseEvent(void);

#if !defined( SUPPORT_GAMEPAD_MOUSE) && !defined (SUPPORT_USB_HID) //liulifeng  for usb mouse  20050920
typedef struct
{
    BYTE    status;
    BYTE    x;
    BYTE    y;
} MOUSE_EVENT,*pMOUSE_EVENT;

MOUSE_EVENT m;
#endif

#ifdef SUPPORT_GAMEPAD_MOUSE
BYTE GAMEPAD_DATA0;
BYTE GAMEPAD0_dir;
BYTE GAMEPAD0_btn;
BYTE MOVING_SPEED = 1;
BYTE MOVING_SPEED_UP = 1;
BYTE OLD_GAMEPAD0_dir;
#elif defined (SUPPORT_USB_HID)   //liulifeng  for usb mouse  20050920
#define MOUSE_MOVE_SPEED      6
extern BYTE usb_mouse_in_flag;
BYTE OLD_MOUSE_DATA [4];
BYTE MOUSE_DATA[4] ;
#else
int iMouseState = SendInitCMD_M_0;
BYTE *pMouseResponsebuf, *pMouseRecvPoint;
BYTE  bRtsPoint = 0;
BYTE bHostSendCmdCount = 0;
BYTE bPS2_read_flag = Enable_M_Read;

const BYTE bMouseInitCmd[] = {/*RESET_M,*/ WorkMod_M, SetSampl_M, SamplRat_M, Enable_M, MouseInitEnd};
#endif



#ifdef SUPPORT_GAMEPAD_MOUSE  // for game pad
void polling_mouse(void)
{
    if(ReadGamePad()>0)
    {
        GAMEPAD_DATA0 = regs0->iop_data[4]&0xff;
        GAMEPAD0_dir = GAMEPAD_DATA0&0xf;
        GAMEPAD0_btn = GAMEPAD_DATA0>>4;
        #ifdef MONE_PS2_MOUSE
            //printf("iop_data[4]_L : dir[%x]   btn[%x]\n", GAMEPAD0_dir, GAMEPAD0_btn);
        #endif
        updateMouseEvent();
    }
return;
}

void updateMouseEvent(void)
{
	if(OLD_GAMEPAD0_dir == GAMEPAD0_dir)
	{
		if(MOVING_SPEED < 4)
		{
			MOVING_SPEED_UP ++;
			MOVING_SPEED = MOVING_SPEED<<(MOVING_SPEED_UP>>(MOVING_SPEED+4));
		}		
	}
	else
	{
		MOVING_SPEED_UP = 1;
		MOVING_SPEED = 1;
	}
    OLD_GAMEPAD0_dir = GAMEPAD0_dir;
//printf("MOVING_SPEED [%d]  [%d] \n", MOVING_SPEED, MOVING_SPEED_UP);
//mouse position
    if((~GAMEPAD0_dir)&0x8)
    {
        mouse_pos_y -=MOVING_SPEED;
    }

    if((~GAMEPAD0_dir)&0x4)
    {
        mouse_pos_y +=MOVING_SPEED;
    }

    if((~GAMEPAD0_dir)&0x2)
    {
        mouse_pos_x -=MOVING_SPEED;
    }

    if((~GAMEPAD0_dir)&0x1)
    {
        mouse_pos_x +=MOVING_SPEED;
    }

    if(mouse_pos_x > X_Pos_Max) 
        {mouse_pos_x = X_Pos_Max;}
    if(mouse_pos_x < 0) 
        {mouse_pos_x = 0;}

    if(mouse_pos_y > Y_Pos_Max) 
        {mouse_pos_y = Y_Pos_Max;}
    if(mouse_pos_y < 0) 
        {mouse_pos_y = 0;}


//mouse button
    if((~GAMEPAD0_btn)&0x8)
    {
        mouse_btn_status |=0x1;
    }

    if((~GAMEPAD0_btn)&0x4)
    {
        mouse_btn_status |=0x2;
    }

    if(GAMEPAD0_btn==0xf)
    {
        mouse_btn_status = 0x0;
    }


}

#elif defined (SUPPORT_USB_HID)  //liulifeng  for usb mouse  20050920

void polling_mouse(void)
{
    if(usb_mouse_in_flag)
    {
        UINT8 i;
        UINT8 j = 0;
        Read_USB_Mouse(MOUSE_DATA);
        //print_block (MOUSE_DATA,4);
        
        for (i = 0;i<4;i++)
        {
            if (*(OLD_MOUSE_DATA +i ) != *(MOUSE_DATA + i))
                j=1;
            *(OLD_MOUSE_DATA +i ) = *(MOUSE_DATA + i);
        }
        if (j)
            updateMouseEvent();
    }
    return;
}

//================ USB MOUSE data reporting format ===========//
//                                                            //
//          bit7    6   5   4   3   2   1   0                 //
// BYTE 0    0      0   0   0   0   M   R   L                 //
// BYTE 1    X      X   X   X   X   X   X   X                 //
// BYTE 2    Y      Y   Y   Y   Y   Y   Y   Y                 //
// BYTE 3    R      R   R   R   R   R   R  F/R                //
//                                                            //
//======================== END ===============================//

void updateMouseEvent(void)
{

    BYTE temp;
    
    //X axle
    temp = MOUSE_DATA[1];
    
    if((temp & 0x80) == 0x80)
    {
        printf("x = %x   ",(BYTE)(~temp));
        if (~temp > MOUSE_MOVE_SPEED)
            mouse_pos_x -=MOUSE_MOVE_SPEED;
        else
            mouse_pos_x -=(BYTE)(~temp);
    }
    else
    {
        printf("x = %x   ",temp);
        if (temp > MOUSE_MOVE_SPEED)
            mouse_pos_x+=MOUSE_MOVE_SPEED;
        else
            mouse_pos_x+=temp;
    }

    //Y axle
    temp = MOUSE_DATA[2];
    
    if((temp & 0x80) == 0x80)
    {
        printf("y = %x   \n",(BYTE)(~temp));
        if (~temp > MOUSE_MOVE_SPEED)
            mouse_pos_y -=MOUSE_MOVE_SPEED;
        else
            mouse_pos_y -=(BYTE)(~temp);
    }
    else
    {
        printf("y = %x   \n",temp);
        if ( temp >MOUSE_MOVE_SPEED)
            mouse_pos_y += MOUSE_MOVE_SPEED;
        else
            mouse_pos_y +=temp;
    }

    //mouse position
    if(mouse_pos_x > X_Pos_Max) 
        {mouse_pos_x = X_Pos_Max;}
    if(mouse_pos_x < 0) 
        {mouse_pos_x = 0;}

    if(mouse_pos_y > Y_Pos_Max) 
        {mouse_pos_y = Y_Pos_Max;}
    if(mouse_pos_y < 0) 
        {mouse_pos_y = 0;}

    //mouse button
     mouse_btn_status = MOUSE_DATA[0] & 0x03;

    #ifdef MONE_PS2_MOUSE
        printf("==>mous  X[%d]   Y[%d]  B[%d] \n", mouse_pos_x, mouse_pos_y, mouse_btn_status);
    #endif    
}

#else    // for ps2 mouse
void polling_mouse(void)
{
    BYTE bNextSend;
    static BYTE bMouse_send_fail;

    
    pMouseResponsebuf = (BYTE *) (SDRAM_BASE_UNCACHED + (regs0->iopya*1024) + 0x302);
    pMouseRecvPoint = (BYTE *) (SDRAM_BASE_UNCACHED + (regs0->iopya*1024) + 0x300);


    switch(iMouseState)
    {
        case SendInitCMD_M_0:   //send command to mouse controller
            if(bMouseInitCmd[bHostSendCmdCount] == MouseInitEnd)
            {
                iMouseState = InitCMD_M_End;
                PS2_INIT_DONE = 0x1;
            }
            else
            {
                #ifdef MONE_PS2_MOUSE
                    printf("\n  PS2: XXX  send MouseCmd=[%x] iop_data5=[%x]\n",
                            bMouseInitCmd[bHostSendCmdCount], regs0->iop_data[5]);
                #endif
                regs0->iop_data[5]=0x8000|bMouseInitCmd[bHostSendCmdCount]; //iop_data2    
                iMouseState = SendInitCMD_M_1;
                #ifdef MONE_PS2_MOUSE
                    printf("\n  PS2: send MouseCmd=[%x] iop_data5=[%x]\n",
                            bMouseInitCmd[bHostSendCmdCount], regs0->iop_data[5]);
                #endif
            }
            break;

        case SendInitCMD_M_1:
            delay(100);
            #ifdef MONE_PS2_MOUSE
                printf("\n  PS2: SendInitCMD_M_1 [%x] [%x] [%x] [%x]\n", 
                bRtsPoint, *pMouseRecvPoint, pMouseResponsebuf[(*pMouseRecvPoint)-1], regs0->iop_data[5]);
            #endif
            
            if((bRtsPoint == *pMouseRecvPoint) || (pMouseResponsebuf[0]!=0xFA))
            {
                bMouse_send_fail++;
                if(bMouse_send_fail ==30)
                {
                    iMouseState = SendInitCMD_M_0;
                    bMouse_send_fail=0;
                    iMouseState = SendInitCMD_M_Fail;
                    regs0->iop_data[5] = 0x00;
                    #ifdef MONE_PS2_MOUSE
                        //printf("Mouse didn't connect\n");
                    #endif
                }
                break;
            }
            bMouse_send_fail = 0;

            //check response from mouse controller
            bNextSend = Response_M_Faile;
            switch(pMouseResponsebuf[0])
            {
                case 0xFA:  //ACK
                    bHostSendCmdCount++;
                    bNextSend = Response_M_OK;
                    break;
                    
                case 0xFE:  //resend
                    bNextSend = Response_M_OK;
                    break;

                default:
                      break;
            }

            //send next command to mouse controller
            if(bNextSend == Response_M_OK) 
            {
                *pMouseRecvPoint = 0;
                pMouseResponsebuf[0] = 0;
                iMouseState = SendInitCMD_M_0;
            }
            break;

        case InitCMD_M_End:
                #ifdef MONE_PS2_MOUSE
                   // printf("\n  InitCMD_M_End   \n");
                #endif
                if(*pMouseRecvPoint)
                {
                    #ifdef MONE_PS2_MOUSE   
                        //printf("pMouseRecvPoint[%x]  address[%x]\n", *pMouseRecvPoint, &(*pMouseRecvPoint));
                    #endif                
                    checkMouseEvent();//(*pMouseRecvPoint);
                 }
            break;

        case SendInitCMD_M_Fail:
        default:
            break;
    }
}



void checkMouseEvent(void)//(BYTE RX)
{
    BYTE bRtsTmp = bRtsPoint;
    int ReceiverCount;


    #ifdef MONE_PS2_MOUSE
        //printf("a [%x] [%x]\n", bRtsTmp, *pMouseRecvPoint);
    #endif

    while(1)
    {
        BYTE *m1 = (BYTE *)&m;
        for (ReceiverCount=0; ReceiverCount<3; ReceiverCount++)
        {
            if((bRtsTmp == *pMouseRecvPoint) || (bRtsTmp >12)) 
            {
                *pMouseRecvPoint = 0;
                break;
            }

            #ifdef MONE_PS2_MOUSE                    
                //printf("[%x] [%x]\t",&(pMouseResponsebuf[bRtsTmp]), pMouseResponsebuf[bRtsTmp]);
            #endif

            *m1 = pMouseResponsebuf[bRtsTmp];
            m1++;
            bRtsTmp++;
            bPS2_read_flag = Enable_M_Read;
            
        }
        if(ReceiverCount == 3)
        {
            if((m.status&0x08) == 0x08) //valid mouse event
            {
                updateMouseEvent();
            }
        }
        else 
        {        
            break;
        }
    }
}



void updateMouseEvent(void)
{
    //update mouse position and button status

    //X axle
    if((m.status & 0x10) == 0x10)
    {
        if((((m.x)^0xff)|0x01) > 8) 
            { mouse_pos_x -=8;}
        else
        { mouse_pos_x -= (((m.x)^0xff)|0x01);}
    }
    else
    {
        if(m.x > 8) 
            {mouse_pos_x+=8;}
        else
            {mouse_pos_x += m.x;}
    }

    //Y axle
    if((m.status & 0x20) == 0x20)
    {
        if((((m.y)^0xff)|0x01)>8)
            {mouse_pos_y +=8;}
        else
            {mouse_pos_y += (((m.y)^0xff)|0x01);}
    }
    else
    {
        if(m.y>8) 
            {mouse_pos_y -= 8;}
        else
            {mouse_pos_y -= m.y;}
    }

    if(mouse_pos_x > X_Pos_Max) 
        {mouse_pos_x = X_Pos_Max;}
    if(mouse_pos_x < 0) 
        {mouse_pos_x = 0;}

    if(mouse_pos_y > Y_Pos_Max) 
        {mouse_pos_y = Y_Pos_Max;}
    if(mouse_pos_y < 0) 
        {mouse_pos_y = 0;}

    //mouse button
    mouse_btn_status = (m.status & 0x07);
    
    
    #ifdef MONE_PS2_MOUSE
        printf("==>mous  X[%d]   Y[%d]  B[%d] \n", mouse_pos_x, mouse_pos_y, mouse_btn_status);
    #endif    
}


void resetMouse(void)
{
    regs0->iop_data[5]=0x8000|RESET_M;
}
#endif
