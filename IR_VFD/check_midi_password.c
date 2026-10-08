#ifdef MIDI_CHECK_PASSWORD_PASS_MCU 
int CheckMIDIPassWordPassMCU(char *PassWord);
int WriteEncryptData2MCU(void);
void WriteOneByte2MCU(BYTE data);
int ReadEncryptDataFromMCU(void);
int ReadOneByteFromMCU(void);
extern BYTE  get_random_number(int range);
BYTE  SendDataBuf[11];
BYTE  ReceiveDataBuf[11];

#define  CHECK_MIDI_PASSWORD_DEBUG  

/*
return 0: check sucessful
return 1: check password fail
return 2: Communication with MCU fail
*/
int CheckMIDIPassWordPassMCU(char *PassWord)
{
    #ifdef CHECK_MIDI_PASSWORD_DEBUG
         printf("\n*************CheckMIDIPassWordPassMCU()*************\n");
    #endif
    int Counter=0;
    BYTE Res=0;
    watchdog_onoff(0); 
    do
    {           
        //get encrypt data package      
        if(Counter==4)
        {
            SetEncryptDataPackage(PassWord,1);
        }
        else
        {
            SetEncryptDataPackage(PassWord,0);
        }            
        //send encrypt data to MCU   
        Res=WriteEncryptData2MCU();             
        if(Res==1)  
           { 
             return 2;//write fail
             #ifdef CHECK_MIDI_PASSWORD_DEBUG
                     printf("\n====write encrypt data fail!==========\n");
             #endif
           }           
           
        //receive encrypt data from MCU
        Res=ReadEncryptDataFromMCU();     
        if(Res==1)  
           {
              return 2;//write fail
              #ifdef CHECK_MIDI_PASSWORD_DEBUG
                     printf("\n====read encrypt data fail!===========\n");
              #endif
           }
          
        //dis-encrypt
        if(Counter==4)
        {                
            if(ReceiveDataBuf[0]!=0x68)  
            {
                #ifdef CHECK_MIDI_PASSWORD_DEBUG
                    printf("\n===========START CODE not correct!==============\n");
                #endif 
                return 1;//check password fail
            }
            if(CheckPassWordFromEncryptData(PassWord)) 
              {                  
                   #ifdef CHECK_MIDI_PASSWORD_DEBUG
                     printf("\n====check password fail!==============\n");
                   #endif
                   return 1;//check password fail
              }           
        }        
        Counter++;
        //delay 1000us
        delay_1us(1000);
       
    }
    while(Counter<10); 
    watchdog_onoff(1); 
    #ifdef CHECK_MIDI_PASSWORD_DEBUG
    if(Res==0)   printf("\n====check password sucessful!==========\n");
    #endif       
    return Res; //return 0: sucessful 
}



/*
    Send Encrypt data package:
    BYTE0:  START CODE £º0xff
    BYTE1:  RANDOM_NUMBER_7
    BYTE2:  XOR_RANDOM_NUMBER_1
    BYTE3:  RANDOM_NUMBER_8
    BYTE4:  XOR_RANDOM_NUMBER_2
    BYTE5:  RANDOM_NUMBER_9    
    BYTE6:  XOR_RANDOM_NUMBER_3
    BYTE7:  RANDOM_NUMBER_1
    BYTE8:  RANDOM_NUMBER_2
    BYTE9:  RANDOM_NUMBER_3
    BYTE10: CHECK_SUM    
*/
void SetEncryptDataPackage(char *String,BYTE flag)
{
    #ifdef CHECK_MIDI_PASSWORD_DEBUG
         printf("\n**************SetEncryptDataPackage()*************\n");
    #endif
    int  i;
    unsigned char CheckSum=0;    
    BYTE Random_1=0,Random_2=0,Random_3=0;
    BYTE Random_7=0,Random_8=0,Random_9=0;
    BYTE PassWord_1=0,PassWord_2=0,PassWord_3=0;
    //random number
    Random_1=get_random_number(255); 
    Random_2=get_random_number(255); 
    Random_3=get_random_number(255); 
    Random_7=get_random_number(255); 
    Random_8=get_random_number(255); 
    Random_9=get_random_number(255); 
    #ifdef CHECK_MIDI_PASSWORD_DEBUG
         printf("\n**%x %x %x  %x  %x  %x **\n",Random_1,Random_2,Random_3,Random_7,Random_8,Random_9);         
    #endif    
    //SendDataBuf[0]
    if(flag==1)
    {
        SendDataBuf[0]=0xff; //START CODE
        PassWord_1=String[0];
        PassWord_2=String[1];
        PassWord_3=String[2];
    }
    else
    {
        SendDataBuf[0]=get_random_number(254); 
        PassWord_1=get_random_number(255); 
        PassWord_2=get_random_number(255);  
        PassWord_3=get_random_number(255); 
    }     
    //SendDataBuf[1]
    SendDataBuf[1]=Random_7;
    //SendDataBuf[2]
    SendDataBuf[2]=PassWord_1^Random_1^Random_2;
    //SendDataBuf[3]
    SendDataBuf[3]=Random_8;
    //SendDataBuf[4]
    SendDataBuf[4]=PassWord_2^Random_2^Random_3;
    //SendDataBuf[5]
    SendDataBuf[5]=Random_9;
    //SendDataBuf[6]
    SendDataBuf[6]=PassWord_3^Random_3^Random_1;
    //SendDataBuf[7]
    SendDataBuf[7]=Random_1;
    //SendDataBuf[8]
    SendDataBuf[8]=Random_2;
    //SendDataBuf[9]
    SendDataBuf[9]=Random_3;
    //SendDataBuf[10]
    for(i=0;i<10;i++)
        CheckSum+=SendDataBuf[i];
    SendDataBuf[10]=CheckSum; 
    #ifdef CHECK_MIDI_PASSWORD_DEBUG
         printf("\n**%x %x %x  %x  %x  %x %x  %x  %x  %x  %x**\n",SendDataBuf[0],
         SendDataBuf[1],SendDataBuf[2],SendDataBuf[3],SendDataBuf[4],SendDataBuf[5],
         SendDataBuf[6],SendDataBuf[7],SendDataBuf[8],SendDataBuf[9],SendDataBuf[10]);         
    #endif       
}


/*
return 0: sucessful
return 1: fail
*/ 
int WriteEncryptData2MCU(void)
{   
    #ifdef CHECK_MIDI_PASSWORD_DEBUG
         printf("\n**************WriteEncryptData2MCU()*************\n");
    #endif
    int i;
    BYTE   num;
    UINT32 TimeOut=0;    
//-------------------------------------------------------------------------
//           Risc handshaking with MCU  
//-------------------------------------------------------------------------
    //CLK=0
    GPIO_O_SET(CLK, 0);
    //Judge if STB is low
    while((GPIO_I_GET(STB)!=0)&&(TimeOut < 100000))
    {
        TimeOut ++;
    }
    if (TimeOut >= 100000)//time out after 10ms
    {
        GPIO_O_SET(CLK, 1); //CLK=1
        #ifdef CHECK_MIDI_PASSWORD_DEBUG
            printf("\n================Write time out 1===================\n");
        #endif 
        return 1;
    }
    //Delay 100us
    delay_1us(100);
    //clear TimeOut
    TimeOut=0;
    //CLK=1
    GPIO_O_SET(CLK, 1);
    
    //Judge if STB is high
    while((GPIO_I_GET(STB)==0)&&(TimeOut < 100000))
    {
        TimeOut ++;
    }
    if (TimeOut >= 100000)//time out after 10ms
    {    
        TimeOut=0;
        #ifdef CHECK_MIDI_PASSWORD_DEBUG
         printf("\n================Write time out 2====================\n");
        #endif     
        return 1;
    }
    TimeOut=0;
//-------------------------------------------------------------------------
//                  Risc transmit data to MCU
//------------------------------------------------------------------------- 
    
     //Delay 200us
    delay_1us(200);    //very important!
    
    watchdog_onoff(0);   
    
    for(i=0;i<11;i++)
    {
        num=SendDataBuf[i];
        WriteOneByte2MCU(num);     
        delay_1us(200);    //very important!   
    }    
    
    watchdog_onoff(1);   
    
    //Set DAT Input port
    GPIO_E_SET(DAT, 0);     
    return 0;
}
/*
return 0: sucessful
return 1: fail
*/
int CheckPassWordFromEncryptData(char *string)
{
    #ifdef CHECK_MIDI_PASSWORD_DEBUG
         printf("\n*********checkPassWordFromEncryptData()************\n");
    #endif  
    BYTE PassWord1,PassWord2,PassWord3;
    BYTE RandomNumber4,RandomNumber5,RandomNumber6;
    BYTE XorRandomNum4,XorRandomNum5,XorRandomNum6;
    XorRandomNum4=ReceiveDataBuf[2];
    XorRandomNum5=ReceiveDataBuf[4];
    XorRandomNum6=ReceiveDataBuf[6];
    RandomNumber4=ReceiveDataBuf[7];
    RandomNumber5=ReceiveDataBuf[8];
    RandomNumber6=ReceiveDataBuf[9];
    PassWord1=XorRandomNum4^RandomNumber4^RandomNumber5;
    PassWord2=XorRandomNum5^RandomNumber5^RandomNumber6;
    PassWord3=XorRandomNum6^RandomNumber6^RandomNumber4;
    if((PassWord1==string[0])&&(PassWord2==string[1])&&(PassWord3==string[2]))
    {
        #ifdef CHECK_MIDI_PASSWORD_DEBUG
            printf("\n**%c %c %c **\n",PassWord1,PassWord2,PassWord3);
            printf("\n==============MIDI check password sucessful!=================\n");
        #endif
        return 0;
    }
    else
    { 
        #ifdef CHECK_MIDI_PASSWORD_DEBUG
            printf("\n==============MIDI check password fail!=================\n");
        #endif
        return 1;
    }
}
/*
    Receive Encrypt data package:
    BYTE0:  START CODE :0x68
    BYTE1:  RANDOM_NUMBER_10
    BYTE2:  XOR_RANDOM_NUMBER_4
    BYTE3:  RANDOM_NUMBER_11
    BYTE4:  XOR_RANDOM_NUMBER_5
    BYTE5:  RANDOM_NUMBER_12    
    BYTE6:  XOR_RANDOM_NUMBER_6
    BYTE7:  RANDOM_NUMBER_4
    BYTE8:  RANDOM_NUMBER_5
    BYTE9:  RANDOM_NUMBER_6
    BYTE10: CHECK_SUM   

    return 0: sucessful
    return 1: fail
*/ 
int ReadEncryptDataFromMCU(void)
{   
    int i ,num=0;
    BYTE RecData=0;
    BYTE  Sum=0,CheckSum=0;
    UINT32 TimeOut=0; 
    //Wait for STB level
    while(GPIO_I_GET(STB))  {}    
    //CLK=0
    GPIO_O_SET(CLK, 0);    
    //Judge if STB is high
    while(!GPIO_I_GET(STB)&&(TimeOut < 100000))
    {
        TimeOut ++;
    }
    if (TimeOut >= 100000)//time out after 10ms
    {        
        #ifdef CHECK_MIDI_PASSWORD_DEBUG
            printf("\n===========read time out===============\n");
        #endif
        GPIO_O_SET(CLK, 1);    //very important!
        return 1;
    }
    TimeOut=0;
    //CLK=1
    GPIO_O_SET(CLK, 1);  
    //wait STB come to low level
   	while(GPIO_I_GET(STB)!=0) {}    		
    watchdog_onoff(0);   
    for(i=0;i<11;i++)    
    {     	
        num=ReadOneByteFromMCU();
        if(num==-1)
        {
          #ifdef CHECK_MIDI_PASSWORD_DEBUG
            printf("\n===========read one byte fail !================\n");
          #endif  
          return 1;
        }  
        else
        {
          ReceiveDataBuf[i]=num;   
        }     
    }  
    //Set DAT output port
    GPIO_E_SET(DAT, 1);    
    GPIO_O_SET(DAT, 1);    
    watchdog_onoff(1);   
      
    //get Sum  
    for(i=0;i<10;i++) 
        {
            Sum+=ReceiveDataBuf[i];
        }
    //get CheckSum
    CheckSum=ReceiveDataBuf[10];    
    //judge check sum
    if(Sum!=CheckSum)
      {
        #ifdef CHECK_MIDI_PASSWORD_DEBUG
            printf("\n===========check sum not correct!==============\n");
        #endif 
        return 1;
      } 
    else
         {
            #ifdef CHECK_MIDI_PASSWORD_DEBUG
                printf("\n===========check sum sucessful!==============\n");
            #endif 
         }  
  
      #ifdef CHECK_MIDI_PASSWORD_DEBUG
         printf("\nrec %x %x %x  %x  %x  %x %x  %x  %x  %x  %x**\n",ReceiveDataBuf[0],
         ReceiveDataBuf[1],ReceiveDataBuf[2],ReceiveDataBuf[3],ReceiveDataBuf[4],ReceiveDataBuf[5],
         ReceiveDataBuf[6],ReceiveDataBuf[7],ReceiveDataBuf[8],ReceiveDataBuf[9],ReceiveDataBuf[10]);         
      #endif   
    return 0;
}
//----------------------------write------------------------------------
void WriteOneByte2MCU(BYTE data)
{    
    int i,j,bit;     
    for(i=0;i<8;i++)
    {
       //CLK=0
       GPIO_O_SET(CLK, 0);        
       bit=((data<<i)&0x80);
       if(bit==0)
       {
            //DAT LOW;              
            GPIO_O_SET(DAT, 0);
       }
       else
       {
            //DAT HIGH;             
            GPIO_O_SET(DAT, 1);  
       }   
       //Delay 100us
       delay_1us(100);
       //CLK=1
       GPIO_O_SET(CLK, 1);      
       //Delay 100us 
       delay_1us(100);  
      
    }
}

/*
return data: receive one byte data from MCU
*/
int ReadOneByteFromMCU(void)
{        
    int i;
    BYTE data=0; 
    UINT32 Timeout=0;
    
    for(i=0;i<8;i++)
    {    
        if(i==0)        
         { 
            data=data<<0;  
         }
        else   
         { 
            data=data<<1; 
         }   
        //wait for STB low level
        while(!GPIO_I_GET(STB)) {}          
        if(GPIO_I_GET(DAT))
           {     
                data=data|0x01;             
           }
        else
           {                 
           	    data=data&(~0x01);             	   	 
           }      
            //wait for STB high level
            while(GPIO_I_GET(STB)&&(Timeout < 4000)) 
            {
                Timeout++; 
                delay_1us(1); 
            }   
             if(Timeout>=4000) 
            {
                printf("\n=receive over!==\n");
                Timeout=0;
                break;                 
            }
            Timeout=0;
    }  
    
    return data;
}
#endif


