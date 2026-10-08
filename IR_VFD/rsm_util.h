/*
*  Terry,2003/8/7 12:23AM
*  reduce function 
*  Maoyong,2004.02.20 15:41PM
   To divide POWER_RESUME, RECORD_KEY, SAME_DISC_RESUME for no confusion
    POWER_RESUME:     when power down, record the current playing pos. 
    RECORD_KEY:       when push RECORD, record the current playing pos
    SAME_DISC_RESUME: when TRAY OUT,  record the current playing pos
   Maoyong, 2004.03.05 13:22
      To move record resume relative functions from  "sysmain2.c" to this file 
   Maoyong  2004.03.18 for combinaton usage
   Maoyong  2004.04.07 fix bug: When shut down power supply, the next same type disc not recorded will do resume play,
                       which is wrong.
*/

#ifndef DVDRELEASE
#define SAVE_CDROM_DEBUG 1
#endif 

#ifdef DISC_ID_IN_FLASH

//#define RESUME_INFO_DBG

//extern int      FlashEraseSector(UINT32 unSectorNum);//for warning
//#include "io_uart0.h"
//#include "UartComm.h"
//static char debug_buffer[64]; //for debugging purpose

    #include "flash.h"
    extern int  Resume_Info_Read(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);
    extern int  Resume_Info_Write(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen);

    UINT32 rsm_flash_start_addr;
    UINT32 rsm_flash_sec_type;
    UINT32 rsm_flash_sec_size;
    UINT32 rsm_free_section_idx_array_size;
    UINT32 rsm_free_section_size;
    UINT32 rsm_flash_erasing_keyword;

/* swpong 2006 0419
*  move the following definition to total_rsm.h for rw_nvmem.h
*/
#include "total_rsm.h"    

#define SIZE_PER_ID      64   // Number of bytes storage reserved for disc resume

/*
    lijd 2005-6-6 15:23
    When make DVD 5 DISC RESUME function for HK OP, yltseng find that there is conflict
    between DIVX DRM  with DVD 5 DISC RESUME.  So,yltseng modify it, and I check it in
    vss.
*/

#define SETUP_MENU_BASE   0 
/* swpong 2006 0414 */
/*
#define TVG_MEM_BASE    98
#define DVD_INFO_BASE   110//128 6e
#define CDROM_INFO_BASE 162//180
#define CDDA_INFO_BASE  182//200
#define VCD_INFO_BASE   187//220

#ifdef SUPPORT_RECEIVER //hongfeng 2005-08-25
    #ifndef SUPPORT_TEN_DISC_RESUME
#define DVD_DISC_INFO  192//244 c0
#define CDDA_DISC_INFO 196//248
#define VCD_DISC_INFO  200//252
    #endif
#else
#define DVD_DISC_INFO  192//244
#define CDDA_DISC_INFO 196//248
#define VCD_DISC_INFO  200//252
#endif
*/
//swpong 2006 0414 #define DRM_INFO       208
#define DRM_INFO       DRM_REG_CODE_I2C_ADD_ST

typedef struct {
	BYTE disc_id[4];
	BYTE disc_info[SIZE_PER_ID];
}DISC_RESUME_INFO;

//index table of the disc resume. It will store the latest TOTAL_RESUME  disc
BYTE disc_resume_index[TOTAL_RESUME];


//store the information to flash for resume together with
//array[TOTAL_RESUME+1] stores the disc resume index table.
//array[TOTAL_RESUME+2] and array[TOTAL_RESUME+3] stores the setup information 
#ifndef RW_NVMEM

#ifdef SETUP_IN_FLASH
DISC_RESUME_INFO disc_resume[TOTAL_RESUME+4]; 
#else
DISC_RESUME_INFO disc_resume[TOTAL_RESUME+1]; 
#endif 

#endif //RW_NVMEM
//current index
int current_resume = 0;
#endif 


#ifdef	CHECK_RECORD_DISK_PARENT_LVL	//Maoyong 2004.03.04
extern UINT32 setup_CheckPasswd(void); 
extern int user_input_pwd;
extern void ShowPasswordGUI(void);
#ifdef NEW_PARENTAL_GUI//zhaoyanhua add 2003-11-28 19:50
extern void ExitParentalGUI(void);
#endif
#endif

#ifdef RECORD_KEY//zhaoyanhua add 03-11-6 15:27
extern void osd_DrawRegionString(BYTE xStart, BYTE yStart, const BYTE *str, BYTE fontColor, BYTE bkColor, BYTE r);
extern void osd_init_record(void);
extern void osd_init(void);
#define FAST2NORM    0x01<<0
#define PAUSE2NORM   0x01<<1
#define SLOW2NORM    0x01<<2
#define REALPLAY     1
//#define TRANSFER     0//nono 2004-2-17 18:05
extern void chg2normal_play(UINT8 md,UINT8 realplay);
extern void run_pause_setting(void);
#endif

#ifdef  DYNAMIC_SPECTRUM //zhaoyanhua add 03-11-6 15:26
extern void Show3dspectrum(void); 
#endif

#ifdef SAME_DISC_RESUME
extern BYTE same_disc_onoff;
#endif
/*
#ifndef DVDRELEASE
//#define RSM_DBG       1
#endif

#ifndef RSM_DBG
#undef printf
#undef print_block
#define printf(f, a...) do {} while (0)
#define print_block(x,y) do {} while (0)
#endif*/

#ifdef SUPPORT_TEN_DISC_RESUME	//linrc add for 10 disc resume play 2005-5-12 10:08
BYTE Rsume_Disc_Index;		   //use this function I2C size must up 1024 BYTE(24C08)
#define RESUME_DISC_NUMBER 3
#define TEN_DISC_INFO_ADDR 339
#define TEN_DISC_RESUME_DEBUG
const UINT16  Info_I2C_ADDR[RESUME_DISC_NUMBER] = {340,344,348,};
const UINT16  MSF_I2C_ADDR[RESUME_DISC_NUMBER]  = {353,406,459,};
#endif

#if 0//def SUPPORT_TEN_DISC_RESUME	//linrc add for 10 disc resume play 2005-5-12 10:08
BYTE Rsume_Disc_Index;		   //use this function I2C size must up 1024 BYTE(24C08)
#define RESUME_DISC_NUMBER 10
#define TEN_DISC_INFO_ADDR 257
//#define TEN_DISC_RESUME_DEBUG
const UINT16  Info_I2C_ADDR[10] = {258,262,266,270,274,278,282,286,290,294,};
const UINT16  MSF_I2C_ADDR[10]  = {299,351,403,455,507,559,611,663,715,767,};
#endif

#ifdef FLASH_HISTORY
#include "rsm_upd.h"
#endif

#ifdef RW_NVMEM
#include "rw_nvmem.h"
#endif


int is_cdg_disc(int show __UNUSED)
{
#ifdef SUPPORT_CDG	
    if( (cd_type_loaded==CDDA) && (cd_subtype==CD_DA) && bReadSubChannel && CDG_IsCDGNow())
    {
       if(show) invalid_key();  
       return 1;
    }else
#endif        
       return 0;
}

/*
 Maoyong changed for resume function define, compile will not give error message
 */
#if !defined(SAME_DISC_RESUME) && !defined(POWER_RESUME) && !defined(RECORD_KEY)
void  save_cmp_disc_info(UINT32 info1){ if(info1){} }//terry,2004/4/8 05:36PM
#endif

/*========================================================================
 basic I2C read and write function for public use in this file
 =========================================================================*/
/*
*  i2c device addr : a0 
*/
void ReadFromI2cA0(UINT16 iAddr,BYTE *bBuffer,UINT16 len)
{
	
#ifndef DISC_ID_IN_FLASH
       memset(bBuffer,0,len);
	if(ReadFromI2c(0xa0, iAddr,bBuffer, len) >=0 )
	{//sucess
	    printf("read flash data:\n");
		//print_block(bBuffer,len);
	}else
	{
		printf("read flash error\n");
	}	
#else//#ifndef DISC_ID_IN_FLASH
    
	int result, j=0;
	//int result,i,k;
	//int j=0;
	//BYTE *p;
   	//i = sizeof(disc_resume);
#ifdef SETUP_IN_FLASH

    #ifndef RW_NVMEM    
    UINT32 i;
    BYTE *p;
    int k;
    
    i = sizeof(disc_resume);
    #endif

       if( iAddr >= DRM_INFO )
       {
#ifdef RW_NVMEM
/* swpong 2006 0320 */
            result = ReadFromNVMEM(TYPE_DRM, iAddr - DRM_INFO, bBuffer, len);
#else  //RW_NVMEM   	    
  #ifdef FLASH_HISTORY
             result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       	       	
              //result = Resume_Info_Read(rsm_flash_start_addr, (BYTE*)disc_resume,i);
             result = Resume_Info_Read(rsm_flash_start_addr, (BYTE*)disc_resume,i);   // 2005/12/23 yltseng
  #endif             
        	p=(BYTE*)&disc_resume[TOTAL_RESUME+3].disc_info;
        	for (k=0; k<len;k++)
        	{
			    j = iAddr - DRM_INFO + k;                                          
        		*bBuffer++ = *(p+j);
        	}
#endif //RW_NVMEM        	
       }
       else
#endif
       if (iAddr >= DVD_INFO_BASE)       	
       {
              if ((iAddr >= DVD_INFO_BASE) && (iAddr <DVD_DISC_INFO))
              {
                     if ((iAddr >= DVD_INFO_BASE) && (iAddr <CDROM_INFO_BASE))   
				j = iAddr - DVD_INFO_BASE;
                     else  if ((iAddr >= CDROM_INFO_BASE) && (iAddr <CDDA_INFO_BASE))   
				j = iAddr - CDROM_INFO_BASE;
     	       	else if ((iAddr >= CDDA_INFO_BASE) && (iAddr <VCD_INFO_BASE))   
				j = iAddr - CDDA_INFO_BASE;
     			else if ((iAddr >= VCD_INFO_BASE) && (iAddr <DVD_DISC_INFO))   
				j = iAddr - VCD_INFO_BASE;
#ifdef RW_NVMEM
/* swpong 2006 0320 */
               
               result = ReadFromNVMEM(TYPE_RESUME, j, bBuffer, len);
#else //RW_NVMEM
          	
  #ifdef FLASH_HISTORY
            result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       	         	
			result = Resume_Info_Read(rsm_flash_start_addr,(BYTE*)disc_resume,i);
  #endif			
			p= (BYTE*)&disc_resume[current_resume].disc_info;
			p+= j;
		       for (k=0; k<len;k++) *bBuffer++ = *p++;
	      		//memcpy(bBuffer,&disc_resume[current_resume].disc_info+j,len);
#endif	//RW_NVMEM		      		
              }
              else 
              {
#ifdef RW_NVMEM
/* swpong 2006/03/22 */
                result = ReadFromNVMEM(TYPE_DISC_ID, 0, bBuffer, ID_LEN);
#else //RW_NVMEM

#ifdef FLASH_HISTORY
           result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
#else  	       					
           result = Resume_Info_Read(rsm_flash_start_addr,(BYTE*)disc_resume,i);
#endif         	       
         	       p= (BYTE*)&disc_resume[current_resume].disc_id;
		       for (k=0; k<len;k++) *bBuffer++ = *p++;
		      // memcpy(bBuffer,&disc_resume[current_resume].disc_id,len);
#endif  //RW_NVMEM		
		 }
       }
#if defined( SETUP_IN_FLASH ) && defined( SUPPORT_TVG )
        else if( iAddr >= TVG_MEM_BASE )
        {
  #ifdef FLASH_HISTORY  
             result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       	        	
            result = Resume_Info_Read( rsm_flash_start_addr, disc_resume,i );
  #endif            
        	p = ((UINT8*)&disc_resume[TOTAL_RESUME+3].disc_info) + 48;
        	for (k=0; k<len;k++)
        	{
			    j = iAddr - TVG_MEM_BASE + k;
        		*bBuffer++ = *(p+j);
        	}
        }
#endif
       else
       {
 #ifdef SETUP_IN_FLASH
#ifdef RW_NVMEM
            result = ReadFromNVMEM(TYPE_SETUP, iAddr, bBuffer, len);
#else //RW_NVMEM               
  #ifdef FLASH_HISTORY
             result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       	                 
      	       result = Resume_Info_Read(rsm_flash_start_addr, (BYTE*)disc_resume,i);
  #endif      	       
        	for (k=0; k<len;k++)
        	{
			j=iAddr+k;
        		p=(BYTE*)&disc_resume[TOTAL_RESUME+1].disc_info;
        		
 			if (j>=(SETUP_MENU_BASE+SIZE_PER_ID)) 
 			//Wrap around for the next 64 (SIZE_PER_ID) bytes for setup
 			{
 				j-= SIZE_PER_ID;
 				p=(BYTE*)&disc_resume[TOTAL_RESUME+2].disc_info;

 			}
                                          
        		*bBuffer++ = *(p+j);
        	}
#endif //RW_NVMEM           	
  #else
       	     result = ReadFromI2c(0xa0, iAddr,bBuffer, len);
#endif
       }
	if(result >=0 )
	{//sucess
	    printf("read flash data:\n");
		//print_block(bBuffer,len);
	}else
	{
		printf("read flash error\n");
	}	
#endif//#ifndef DISC_ID_IN_FLASH


}
/*
*  i2c device addr : a0 , read UINT32 parameter
*/
int ReadFromI2cA0_32(UINT16 iAddr,BYTE *bBuffer,UINT16 len)
{
	UINT32 v=0;
#ifndef DISC_ID_IN_FLASH
	if(ReadFromI2c(0xa0, iAddr,bBuffer, len) >=0 )
	{//sucess
	    printf("read flash data:\n");
		//print_block(bBuffer,len);
		if(len == 4)	v = getUINT32_li(bBuffer);
		else v = getUINT16_li(bBuffer);
	}else
	{
		printf("read flash error\n");		
	}	
#else//#ifndef DISC_ID_IN_FLASH

       int result,j=0;


//	memset(bBuffer,0,len);
        
#ifdef SETUP_IN_FLASH

   #ifndef RW_NVMEM
   BYTE *p;
   UINT32 i;
   int k;

   i = sizeof(disc_resume);        
   #endif

   if( iAddr >= DRM_INFO )
   {
#ifdef RW_NVMEM
/* swpong 2006 0320 */
            result = ReadFromNVMEM(TYPE_DRM, iAddr - DRM_INFO, bBuffer, len);
#else  //RW_NVMEM
  #ifdef FLASH_HISTORY 
             result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       	   	
         result = Resume_Info_Read(rsm_flash_start_addr, (BYTE*)disc_resume,i);
  #endif         
    	
    	p=(BYTE*)&disc_resume[TOTAL_RESUME+3].disc_info;
    	for (k=0; k<len;k++)
    	{
		    j=iAddr - DRM_INFO + k;                                          
    		*bBuffer++ = *(p+j);
    	}
#endif //RW_NVMEM      	
   }
   else
#endif
   	if (iAddr >= DVD_INFO_BASE)       	
       {
       	//i = sizeof(disc_resume);

              if ((iAddr >= DVD_INFO_BASE) && (iAddr <DVD_DISC_INFO))
              {
                  	if ((iAddr >= DVD_INFO_BASE) && (iAddr <CDROM_INFO_BASE))   
				j = iAddr - DVD_INFO_BASE;
			else if ((iAddr >= CDROM_INFO_BASE) && (iAddr <CDDA_INFO_BASE))   
				j = iAddr - CDROM_INFO_BASE;
     	       	else if ((iAddr >= CDDA_INFO_BASE) && (iAddr <VCD_INFO_BASE))   
				j = iAddr - CDDA_INFO_BASE;
     			else if ((iAddr >= VCD_INFO_BASE) && (iAddr <DVD_DISC_INFO))   
				j = iAddr - VCD_INFO_BASE;
#ifdef RW_NVMEM
/* swpong 2006 0320 */
               result = ReadFromNVMEM(TYPE_RESUME, j, bBuffer, len);
#else  //RW_NVMEM        			
  #ifdef FLASH_HISTORY
             result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       					
 			result = Resume_Info_Read(rsm_flash_start_addr,(BYTE*)disc_resume,i);
  #endif 			
			p= (BYTE*)&disc_resume[current_resume].disc_info;
			p +=j;
		       for (k=0; k<len;k++) *(bBuffer+k) = *p++;
//	      		memcpy(bBuffer,&disc_resume[current_resume].disc_info+j,len);
#endif //RW_NVMEM
              }
              else
              {
#ifdef RW_NVMEM
/* swpong 2006 0320 */
                result = ReadFromNVMEM(TYPE_DISC_ID, 0, bBuffer, ID_LEN);
#else  //RW_NVMEM
  #ifdef FLASH_HISTORY
             result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       	              	
         	       result = Resume_Info_Read(rsm_flash_start_addr,(BYTE*)disc_resume,i);
  #endif         	       
         	       p= (BYTE*)&disc_resume[current_resume].disc_id;
		       for (k=0; k<len;k++) *(bBuffer+k) = *p++;
//		       memcpy(bBuffer,&disc_resume[current_resume].disc_id,len);
#endif //RW_NVMEM
		 }
       }
#if defined( SETUP_IN_FLASH ) && defined( SUPPORT_TVG )
        else if( iAddr >= TVG_MEM_BASE )
        {
  #ifdef FLASH_HISTORY
             result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       	        	
            result = Resume_Info_Read( rsm_flash_start_addr, disc_resume,i );
  #endif            
        	p = ((UINT8*)&disc_resume[TOTAL_RESUME+3].disc_info) + 48;
        	for (k=0; k<len;k++)
        	{
			    j = iAddr - TVG_MEM_BASE + k;
        		*bBuffer++ = *(p+j);
        	}
        }
#endif
       else
       {
 #ifdef SETUP_IN_FLASH
#ifdef RW_NVMEM
/* swpong 2006 0320 */
            result = ReadFromNVMEM(TYPE_SETUP, iAddr, bBuffer, len);
#else //RW_NVMEM          
  #ifdef FLASH_HISTORY
               result = Resume_Info_Read_Update((BYTE*)disc_resume, i);   //swpong 2006 0404
  #else  	       	
      	       result = Resume_Info_Read(rsm_flash_start_addr, (BYTE*)disc_resume,i);
  #endif      	       
        	for (k=0; k<len;k++)
        	{
			j=iAddr+k;
        		p=(BYTE*)&disc_resume[TOTAL_RESUME+1].disc_info;
        		
 			if (j>=(SETUP_MENU_BASE+SIZE_PER_ID)) 
 			//Wrap around for the next 64 (SIZE_PER_ID) bytes for setup
 			{
 				j-= SIZE_PER_ID;
 				p=(BYTE*)&disc_resume[TOTAL_RESUME+2].disc_info;

 			}
                                          
        		*bBuffer++ = *(p+j);
        	}
#endif //RW_NVMEM        	
  #else
       	     result = ReadFromI2c(0xa0, iAddr,bBuffer, len);
#endif
       }
       
	if(result >=0 )
	{//sucess
    	       printf("read flash data:\n");
		//print_block(bBuffer,len);
		if(len == 4)	v = getUINT32_li(bBuffer);
		else v = getUINT16_li(bBuffer);
	}else
	{
		printf("read flash error\n");		
	}	

#endif//#ifndef DISC_ID_IN_FLASH

	return v;
}
/*
*  i2c device addr : a0 , write function
*/
void WriteToI2cA0(int iAddr,BYTE *bData,UINT32 len)
{

#ifndef DISC_ID_IN_FLASH
    //printf("i2c,iAddr:%d len:%d\n",iAddr,len);
	if( WriteToI2c(0xa0,iAddr,bData,len) < 0 )
	{//write fail
		printf("!!!!  ========  write flash error  ======== !!!!!\n");
	}
#else//#ifndef DISC_ID_IN_FLASH
        int result=0, j=0;
      	UINT32  is_write_flash =1;
      	
        //joshua, 20060220, modified for enhancing read/write cycles of flash.
        //is_write_flash==0 don't write, is_write_flash==1 write
        //1.However, iAddr(setup-menu related address) from 4(SETUP_VA_I2C_YA) to 68(SETUP_CHECKSUM_I2C_YA) will be return.
        //  finally, run_save_total_userSet() will save all modified values and write into flash once.      	
        //2.About resume function, we also write once at last function call.
        if( ((iAddr>=4)&&(iAddr<=68)) 
            || (iAddr==DVD_INFO_BASE) || (iAddr==CDROM_INFO_BASE) || (iAddr==CDDA_INFO_BASE) || (iAddr==VCD_INFO_BASE) 
            || (iAddr==DVD_DISC_INFO) || (iAddr==CDDA_DISC_INFO)   || (iAddr==VCD_DISC_INFO) )
        {
            is_write_flash = 0;      	              	      	
        }    
 
#ifdef SETUP_IN_FLASH
//swpong 2006 0413
     #ifdef FLASH_HISTORY
       BYTE *pdata1;
                    
       pdata1 = bData;
     #endif

     #ifndef RW_NVMEM
       UINT32 i, k;
       BYTE *p, *q;
       
       i = sizeof(disc_resume);
     #endif
     
     #if defined(FLASH_HISTORY)&&(!defined(RW_NVMEM))
       UINT32 padr, qadr, iStart1, len1, len2;
       BYTE *pdata2;
     #endif

       if( iAddr >= (int)DRM_INFO )
       {
#ifdef RW_NVMEM
            result = WriteToNVMEM(TYPE_DRM, iAddr - DRM_INFO, bData, len);
#else  //RW_NVMEM
			//FlashEraseSector(FLASH_ERASE_SECTOR);
            
            p = (BYTE*)&disc_resume[TOTAL_RESUME+3].disc_info;

            #ifdef FLASH_HISTORY            
            padr = (UINT32)p - (UINT32)disc_resume;
            #endif            

        	for (k=0; k<len;k++)
        	{
			    j=iAddr - DRM_INFO + k;
        		*(p+j)=*bData++;
        	}
            
//swpong 2006 0404
  #ifdef FLASH_HISTORY
            result = Resume_Info_Write_Update((padr+iAddr-DRM_INFO), (BYTE*)disc_resume, i, pdata1, len);
  #else   		        
            if(is_write_flash==1)
            {
                result = Resume_Info_Write(rsm_flash_start_addr,(BYTE*)disc_resume,i);
            }     	            
  #endif //FLASH_HISTORY

#endif  //RW_NVMEM            	            
       }
       else
#endif
       if (iAddr >= (int)DVD_INFO_BASE)       	
       {
             if ((iAddr >= (int)DVD_INFO_BASE) && (iAddr <(int)DVD_DISC_INFO))
             {
                if ((iAddr >= (int)DVD_INFO_BASE) && (iAddr <(int)CDROM_INFO_BASE))   
                    j = iAddr - DVD_INFO_BASE;
                else if ((iAddr >= (int)CDROM_INFO_BASE) && (iAddr <(int)CDDA_INFO_BASE))   
                    j = iAddr - CDROM_INFO_BASE;
                else if ((iAddr >= (int)CDDA_INFO_BASE) && (iAddr <(int)VCD_INFO_BASE))   
                    j = iAddr - CDDA_INFO_BASE;
                else if ((iAddr >= (int)VCD_INFO_BASE) && (iAddr <(int)DVD_DISC_INFO))   
                    j = iAddr - VCD_INFO_BASE;
      
#ifdef RW_NVMEM       
/* swpong 2006 0320 */
            result = WriteToNVMEM(TYPE_RESUME, j, bData, len);
#else  //RW_NVMEM
    			//FlashEraseSector(FLASH_ERASE_SECTOR);
    		//    memcpy(&disc_resume[current_resume].disc_info+j,bData,len);
    			p= (BYTE*)&disc_resume[current_resume].disc_info;

#ifdef FLASH_HISTORY            
                padr = (UINT32)p - (UINT32)disc_resume;
#endif            

    			p += j;
    		        for (k=0; k<len;k++) 
    		        {
    		            *p++ = *bData++;
    		        }    

//swpong 2006 0404
#ifdef FLASH_HISTORY
           result = Resume_Info_Write_Update((padr+j), (BYTE*)disc_resume, i, pdata1, len);
#else   		            		       
                    if(is_write_flash==1)
                    {
                        result = Resume_Info_Write(rsm_flash_start_addr,(BYTE*)disc_resume,i); 
                    }              	
#endif    
            
#endif //RW_NVMEM                               	
                  }
                  else
                  {
#ifdef RW_NVMEM
/* swpong 2006 0320 */
            result = WriteToNVMEM(TYPE_DISC_ID, 0, bData, len);
#else //NV_MEM     	                
    			//FlashEraseSector(FLASH_ERASE_SECTOR);
    			p= (BYTE*)&disc_resume[current_resume].disc_id;
  #ifdef FLASH_HISTORY            
                padr = (UINT32)p - (UINT32)disc_resume;
  #endif            

    		       for (k=0; k<len;k++) *p++ = *bData++;
  //swpong 2006 0404
  #ifdef FLASH_HISTORY
               result = Resume_Info_Write_Update(padr, (BYTE*)disc_resume, i, pdata1, len);
  #endif               

                //memcpy(&disc_resume[current_resume].disc_id,bData,len);
                //update disc_resume_index;
    			p= (BYTE*)&disc_resume[TOTAL_RESUME].disc_id;
    			q= (BYTE*)disc_resume_index;
  #ifdef FLASH_HISTORY            
                pdata1 = q;
                padr = (UINT32)p - (UINT32)disc_resume;
                
  #endif                			
    		       for (k=0; k<sizeof(disc_resume_index);k++) *p++ = *q++;
    
                //memcpy(&disc_resume[TOTAL_RESUME].disc_id,disc_resume_index,sizeof(disc_resume_index));
  //swpong 2006 0404
  #ifdef FLASH_HISTORY
               result = Resume_Info_Write_Update(padr, (BYTE*)disc_resume, i, pdata1, sizeof(disc_resume_index));
  #else   		                        
                if(is_write_flash==1)
                {
    			    result = Resume_Info_Write(rsm_flash_start_addr,(BYTE*)disc_resume,i); 
                }    
  #endif            

#endif //NV_MEM    	    	
            }
       }
#if defined( SETUP_IN_FLASH ) && defined( SUPPORT_TVG )
        else if( iAddr >= TVG_MEM_BASE )
        {
			//FlashEraseSector( FLASH_ERASE_SECTOR );
            
            p = ((UINT8*)&disc_resume[TOTAL_RESUME+3].disc_info) + 48;
            padr = (UINT32)p - (UINT32)disc_resume; //swpong 2006 0414
        	for (k=0; k<len;k++)
        	{
			    j=iAddr - TVG_MEM_BASE + k;
        		*(p+j)=*bData++;
        	}
        	
            //swpong 2006 0404
            #ifdef FLASH_HOSTORY
               result = Resume_Info_Write_Update((padr+j), (BYTE*)disc_resume, i, pdata1, len);
            #else        	
        	  if(is_write_flash==1)
        	  {
        	    result = Resume_Info_Write( rsm_flash_start_addr, disc_resume, i );
        	  }    
            #endif
        }
#endif
       else
       {
#ifdef SETUP_IN_FLASH
#ifdef RW_NVMEM   
            if (iAddr > (int)SETUP_CHECKSUM_I2C_YA)
              result = WriteToNVMEM(TYPE_SETUP_W, iAddr, bData, len);
            else
              result = WriteToNVMEM(TYPE_SETUP_NW, iAddr, bData, len);
              
#else //RW_NVMEM

            //result = FlashEraseSector(FLASH_ERASE_SECTOR);

        	for (k=0; k<len;k++)
        	{
			j=iAddr+k;
        		p=(BYTE*)&disc_resume[TOTAL_RESUME+1].disc_info;
        		
 			if (j>=(SETUP_MENU_BASE+SIZE_PER_ID)) 
 			//Wrap around for the next 64 (SIZE_PER_ID) bytes for setup
 			{
 				j-= SIZE_PER_ID;
 				p=(BYTE*)&disc_resume[TOTAL_RESUME+2].disc_info;

 			}
                                          
        		*(p+j)=*bData++;
        	}

//swpong 2006 0404
#ifdef FLASH_HISTORY       
            // Process for setup info cross two blocks
            // case 1 : start in 1st, end in 1st
            // case 2 : start in 1st, end in 2nd
            // case 3 : start in 2nd, end in 2nd
            if (iAddr < (SETUP_MENU_BASE + SIZE_PER_ID))
            {
         	  p=(BYTE*)&disc_resume[TOTAL_RESUME+1].disc_info;
         	  padr = (UINT32)p;
         	  iStart1 = padr - (UINT32)disc_resume + iAddr - SETUP_MENU_BASE;

         	  if ((iAddr + len) >= (SETUP_MENU_BASE + SIZE_PER_ID))
         	  {
         		len1 = ((SETUP_MENU_BASE + SIZE_PER_ID) - iAddr);
         		len2 = len - len1;
         		p=(BYTE*)&disc_resume[TOTAL_RESUME+2].disc_info;
         		qadr = (UINT32)p - (UINT32)disc_resume;
         		pdata2 = pdata1 + len1;
         		
         	    result = Resume_Info_Write_Update(iStart1, (BYTE *)disc_resume, i, pdata1, len1);
         		result = Resume_Info_Write_Update(qadr, (BYTE *)disc_resume, i, pdata2, len2); 
         	  }         	
         	  else
         	  {
         	    result = Resume_Info_Write_Update(iStart1, (BYTE *)disc_resume, i, pdata1, len);
         	  }
            }
            else // iAddr in second block
            {
         	  p=(BYTE*)&disc_resume[TOTAL_RESUME+2].disc_info;
         	  padr = (UINT32)p - (UINT32)disc_resume + iAddr - (SETUP_MENU_BASE + SIZE_PER_ID);
         	  //iStart1 = padr - (UINT32)disc_resume + iAddr - (SETUP_MENU_BASE + SIZE_PER_ID);
         	  result = Resume_Info_Write_Update(padr, (BYTE *)disc_resume, i, pdata1, len); 
            }        
#else
            if(is_write_flash==1)
            {
 	            result = Resume_Info_Write(rsm_flash_start_addr,(BYTE*)disc_resume,i);
            }    
#endif        

#endif //RW_NVMEM
#else
             	     result = WriteToI2c(0xa0,iAddr,bData,len) ;
#endif     
       }
       
	if( result < 0 )
	{//write fail
		printf("!!!!  ========  write flash error  ======== !!!!!\n");
	}
	/*
	#ifdef DVD_SERVO    //ycwen 2004/08/10 
	extern void    ClearServoCacheBuffer();
           ClearServoCacheBuffer(); 
     #endif 
     */
#endif//#ifndef DISC_ID_IN_FLASH
}

#ifdef 	RECORD_PER_SECOND		//Maoyong add pre-def condition 2004.02.20 
/*
*  power resume function for record every secode
*/   
static inline void power_rsm_ps_RsmInfo2Flash(int clr)
{
    static BYTE savetemparry[50];
    BYTE    *p;             
    
    //printf("!!!run save_tuner_setup ,size:%d\n",sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
    #ifdef SUPPORT_FILE_SYSTEM_MODE		
	if ((cd_type_loaded == CDROM) && (GetCurrentFileType() == CDROM_MPG)) 
		return ;
	#endif
    if( is_menu() || clr )
    {
		resumeMSF = 0;
		resumeTRK = 0;
		pFsJpeg->fsnav_dir_now = 0;
		pFsJpeg->fsnav_trk_now = 0;
		myTime=0;
    }else
    {
        if(cd_type_loaded!=CDDVD)
        {
            resumeMSF = s_msf&0x00ffffff;
            resumeTRK = cd_trk_now;
            if( (cd_type_loaded==CDROM)&&( !Is_MP3_STATE() ) ) 
            { 							//Jeff 20021114//nono 20021123 modified
				resumeMSF = 0;			//we only support MP3, not contain JPEG/Game
                
            }
        }
        else
        {
            resumeMSF = 1;
            if(play_state!=VCD_STATE_STOP)//20021014
				RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:41 .
        }        
    }
	
  if(cd_type_loaded==CDDVD)
  	{
    	int k; 
    	int changlen=0;
    	BYTE first_flag=1;
    	p=(BYTE *)&pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM];    
    	for(k=(sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM])-1);k>=0;k--)
       		{
       	 		if(savetemparry[k] != p[k])
       	    		{
       	       			if(first_flag)
       	       				{
       	       		   			first_flag=0;
       	       		   			changlen=k;	
       	       				}	
       	    		}	
          		savetemparry[k]=p[k];
       		}
    	WriteToI2cA0(128,p,changlen+1);
    	//printf("len=%d\n",changlen+1);
    	first_flag=(BYTE)resumeMSF;		//in dvd mode resumeMSF only use flag!
   		WriteToI2cA0(128+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM])+sizeof(resumeTRK),(BYTE *)&first_flag, sizeof(first_flag));
    	 
  }
  else
  	{   
    	printf("resumeTRK=%d\n",resumeTRK);
    	WriteToI2cA0(128+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),(BYTE *)&resumeTRK, sizeof(resumeTRK));
    	printf("resumeMSF:%x\n",resumeMSF);
    	WriteToI2cA0(128+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM])+sizeof(resumeTRK),(BYTE *)&resumeMSF, sizeof(resumeMSF));
    	
    	printf("fsnav_dir_now:%d\n", pFsJpeg->fsnav_dir_now);
    	//it only cdrom need record
    	if(cd_type_loaded==CDROM)		
    	{
    	  	WriteToI2cA0(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF), 
			(BYTE *)&(pFsJpeg->fsnav_dir_now), sizeof(pFsJpeg->fsnav_dir_now));
    		printf("fsnav_trk_now:%d\n", pFsJpeg->fsnav_trk_now);
    		
    	    WriteToI2cA0(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF) + sizeof(pFsJpeg->fsnav_dir_now), 
			(BYTE *)&(pFsJpeg->fsnav_trk_now), sizeof(pFsJpeg->fsnav_trk_now));
    		printf("myTime:%d\n", myTime);
    		
    	    WriteToI2cA0(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF) + sizeof(pFsJpeg->fsnav_dir_now) + sizeof(pFsJpeg->fsnav_trk_now), 
			(BYTE *)&myTime, sizeof(myTime));
       }		
  	}	
}
#endif	//end	#ifdef 	RECORD_PER_SECOND	


#ifndef DISC_ID_IN_FLASH //put them at the beginning
/*========================================================================
 record resume play func's save and load realized functions prototypes
 =========================================================================*/
/*
*  last memory function
*/
/*
#define SETUP_MENU_BASE   0
#define DVD_INFO_BASE   128
#define CDROM_INFO_BASE 180
#define CDDA_INFO_BASE  200
#define VCD_INFO_BASE   220

//Maoyong 2004.04.07 for all resume use
#define DVD_DISC_INFO  244
#define CDDA_DISC_INFO 248
#define VCD_DISC_INFO  252
*/
//nono according to yltseng's suggestion.20050812
//Linrc move to memmap_I2C.h 2006-2-28 10:19
#define SETUP_MENU_BASE   0 
/*#define DVD_INFO_BASE   110//128
#define CDROM_INFO_BASE 162//180
#define CDDA_INFO_BASE  182//200
#define VCD_INFO_BASE   187//220*/
//denghg change resume  Addr  because resumeTRK byte -->now UINT32 2005-12-2 01:49     

//#define DVD_INFO_BASE    104//110//128
//#define CDROM_INFO_BASE  156//162//180
//#define CDDA_INFO_BASE   176//182//200
//#define VCD_INFO_BASE    184//187//220


//#define DVD_DISC_INFO  192//244
//#define CDDA_DISC_INFO 196//248
//#define VCD_DISC_INFO  200//252
#define DRM_INFO       208

#endif //#ifndef DISC_ID_IN_FLASH


#ifdef MP3_POWER_RESUME// 0//def POWER_RESUME//mp3 power resume needto be fixed later.
/**********************************************************************************************
	Function : To identify whether the current MP3 disc is the one played last time
	return 1 : yes
	       0 : no
	Created by caiyh , 17:03 , Nov 5th , 2004
**********************************************************************************************/
UINT8 IsTheSameMP3 ( void )
{
	UINT32 fsnav_dir_now = 0 , 
	       fsnav_trk_now = 0 ,
	       first_mp3_entry = 0 ,
	       MSFFlag = 0 ,
	       msf = 0 ;
	BYTE  v [ 4 ] ;

	fsnav_dir_now = ReadFromI2cA0_32 ( CDROM_INFO_BASE , v , sizeof( pFsJpeg -> fsnav_dir_now ) ) ;
	fsnav_trk_now = ReadFromI2cA0_32 ( CDROM_INFO_BASE + sizeof( pFsJpeg -> fsnav_dir_now ) ,
			v , sizeof( pFsJpeg -> fsnav_trk_now ) ) ;
	MSFFlag = ReadFromI2cA0_32 ( CDROM_INFO_BASE + sizeof( pFsJpeg -> fsnav_dir_now ) 
		  + sizeof( pFsJpeg -> fsnav_trk_now ) , v , sizeof( MSFFlag ) ) ;
	/* read the information recorded from i2c ,
	   annotated by caiyh , 17:03 , Nov 5th , 2004 */
	
	first_mp3_entry = pFsJpeg -> Dir_entry [ fsnav_dir_now ] ;
	fsnav_trk_now += first_mp3_entry ;
	msf = iso9660_file [ fsnav_trk_now ] . loc ;
	if ( msf == MSFFlag )
		return 1 ;
	else 
		return 0 ;
	/* according to the dir and trk recorded in i2c, to find the msf specified ,
	   and compare the current msf with the one read from i2c ,
	   annotated by caiyh , 17:03 , Nov 5th , 2004 */
}

/**************************************************************
	Function : read the parameters about MP3 resume
	para = 0 : dir
	       1 : trk
	       2 : msf
	       3 : myTime
	return : the value of dir trk msf or myTime
	Created by caiyh , 09:24 , Nov 22nd , 2004
**************************************************************/
UINT32 ReadSameMP3Para ( UINT8 para )
{
	UINT32 result = 0 ;
	BYTE v [ 4 ] ;
	
#if  defined(STOP_RESUME_DVD_VCD)
	return 0;
#endif

	if ( para <=2 )
		result = ReadFromI2cA0_32 ( CDROM_INFO_BASE + para * 2 , v , 2 ) ;
	else if ( para == 3 )
		result = ReadFromI2cA0_32 ( CDROM_INFO_BASE + 8 , v , 4 ) ;
	// read parameter of mp3 resume from i2c , annotated by caiyh , 09:24 , Nov 22nd , 2004
	return result ;
}

/*********************************************************
	Function : clear msf about MP3 resume
	Created by caiyh , 09:34 , Nov 22nd , 2004
*********************************************************/
void ClrSameMP3Flag ( void )
{	
	UINT32 MSFFlag = 0 ;
	
	WriteToI2cA0 ( CDROM_INFO_BASE + 4 , ( BYTE * ) & MSFFlag , sizeof ( MSFFlag ) ) ;
	// clear msf of mp3 resume in i2c , annotated by caiyh , 09:34 , Nov 22nd , 2004
}
#endif   // POWER_RESUME

#if defined (POWER_RESUME)|| defined(SAME_DISC_RESUME)|| defined(RECORD_KEY)
void clr_rsm_info(void)
{//terry,2003/8/13 01:21AM    
    #ifdef DVD_5_DISC_RESUME//LIJD 2005-6-30 20:12
	if( is_cdg_disc(0) ||(cd_type_loaded==CDROM) || ((disp_trk_now==0)&&(cd_type_loaded!=CDDVD))  )
    #elif defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
    if( is_menu() || is_cdg_disc(0) || (pe_run==0) ||(play_state==VCD_STATE_OPEN)|| (!IS_DVD_VCD_DISC()) || (need_record==CLEAR_RECORD_FLAG))//shenyj add for alco177w vcd open resume
	#elif defined(POWER_OFF_NEED_DVD_RESUME)&&!defined(PARENTAL_DVD_NEDD_RESUME)//hongfeng modify 2006/2/27
	if(is_menu()||is_cdg_disc(0)||(cd_type_loaded==CDROM)||((disp_trk_now==0)&&(cd_type_loaded!=CDDVD)))
	#elif defined(POWER_OFF_NEED_DVD_RESUME)&&defined(PARENTAL_DVD_NEDD_RESUME)  //hongfeng 2006/3/31 17:53
	if(is_cdg_disc(0)||(cd_type_loaded==CDROM)||((disp_trk_now==0)&&(cd_type_loaded!=CDDVD)))	
	#else 
//	if( is_cdg_disc(0) ||(cd_type_loaded==CDROM) || ((disp_trk_now==0)&&(cd_type_loaded!=CDDVD))  )//hongfeng open.Nono mark it.20060401
    if( is_menu() || is_cdg_disc(0) || (pe_run==0) ||(cd_type_loaded==CDROM) || ((disp_trk_now==0)&&(cd_type_loaded!=CDDVD))  )
    #endif
    {
        printf("clr rsm info: %d %d %d %d\n",is_menu(),is_cdg_disc(0),pe_run,disp_trk_now);
        
        #if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
        if(need_record == REAL_RECORD_VALUE)
            return;
        #endif

        resumeMSF = 0;
        resumeTRK = 0;
        pFsJpeg->fsnav_dir_now=0;
        pFsJpeg->fsnav_trk_now=0;
        myTime=0;
        
    }
}

static inline void same_disc_RsmInfo2Flash(int clr)
{
    
#ifdef SUPPORT_WHEN_PLAY_MENU_NOT_SAVE_DISC
    if(is_menu())
    {
        if(cd_type_loaded==CDDVD)
        {
            if((disp_time ==0)||(get_tt_info(DISP_TT) == 0)
				||(get_tt_info(DISP_CH)==0))
  		        return;
        }
        else
            return;
    }
#endif//end=> #define  SUPPORT_WHEN_PLAY_MENU_NOT_SAVE_DISC

#ifdef SUPPORT_TEN_DISC_RESUME		//linrc add for 10 disc resume play 2005-5-12 10:09
	UINT32  info1;					//if you have any problem,see DOC file
	BYTE    *p;
	UINT32  MSFFlag = 0 ;
	UINT16  pos;
	BYTE    Resume_Now;
	BYTE    Resume_Index;
	BYTE    i;
   	UINT32  Rom_Info1;
	
	if(clr){};
	if(cd_type_loaded==CDUNKNOWN) return;

	#ifdef DVD_5_DISC_RESUME//lijd 2005-6-16 15:56
		if(cd_type_loaded!=DVD) return;
	#endif

    resumeMSF = s_msf&0x00ffffff;
    resumeTRK = cd_trk_now;
    
#ifndef DONT_CLR_RSM //hongfeng add 2005-11-03
#ifdef POWER_RESUME
    if(Is_MP3_STATE()==0)   // don't clear the resume info of mp3 , added by caiyh , 10:53 , Nov 2nd , 2004
#endif   // POWER_RESUME
    clr_rsm_info();
#endif
				
	if(cd_type_loaded!=CDDVD)
	{
		info1=M2I(gettrkmsf_leadout()); 
	}
    else
    {
   		info1 = same_disc_vob11_pos;   
   	} 
   	#ifdef TEN_DISC_RESUME_DEBUG
   	printf("---  info1=0x%x  ---\n",info1);
    #endif
   	ReadFromI2cA0(TEN_DISC_INFO_ADDR,&Resume_Index, sizeof(Resume_Index));
   	if(Resume_Index>=RESUME_DISC_NUMBER)//hongfeng 2005-08-25
   	{
   		Resume_Index = 0;
   	}
   	Resume_Now = Resume_Index;
   	
   	for(i=0;i<RESUME_DISC_NUMBER;i++)
	{
		ReadFromI2cA0(Info_I2C_ADDR[i],(BYTE *)&Rom_Info1,sizeof(Rom_Info1));
		if(info1==Rom_Info1)
		{
			#ifdef TEN_DISC_RESUME_DEBUG
			printf("---  Have Save Disc Resume zone  ---\n");
			#endif
			Resume_Now = i;
			if(Resume_Index!=0)
			{
				if(Resume_Now!=Resume_Index)
				{
					Resume_Index--;
				}
			}
			else
			{
				Resume_Index = (RESUME_DISC_NUMBER-1);
				if(Resume_Now==0)
				{
					Resume_Index = 0;
				}
			}
			break;
		}
	} 
	
	#ifdef TEN_DISC_RESUME_DEBUG
   	printf("\n\n---  Disc->Resume_Now=%d  ---\n",Resume_Now);
   	printf("---  Disc->Resume_Index+1=%d  ---\n",Resume_Index+1);
   	printf("---  Info_I2C_ADDR[%d]=%d  ---\n",Resume_Now,Info_I2C_ADDR[Resume_Now]);  	
   	#endif
   	
   	WriteToI2cA0(Info_I2C_ADDR[Resume_Now],(BYTE *)&info1,sizeof(info1));
    Resume_Index++;
    WriteToI2cA0(TEN_DISC_INFO_ADDR,&Resume_Index,sizeof(Resume_Index));
    
    /*ReadFromI2cA0(TEN_DISC_INFO_ADDR,&Resume_Now, sizeof(Resume_Now));   	
   	printf("---  Disc->Resume_Now=%d  ---\n",Resume_Now);
    Resume_Now--;
   	ReadFromI2cA0(Info_I2C_ADDR[Resume_Now],(BYTE *)&info1,sizeof(info1));
   	printf("---  info1=0x%x  ---\n",info1);*/
   	
   	p = (BYTE *)&pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM];
   	printf("---  Disc->Resume_Now=%x  ---\n",Resume_Now);
   	pos = MSF_I2C_ADDR[Resume_Now];
   	//printf("---  Disc->Record_Now=%d  ---\n",Disc->Record_Now);
   	printf("---  pos=%d ---\n",pos);
    if(cd_type_loaded!=CDDVD)
    {
    	if(cd_type_loaded==CDROM) 
        {//we only support MP3, not contain JPEG/Game
        	if(Is_MP3_STATE()==0) resumeMSF = 0;
                
            printf("fsnav_dir_now:%d\n",pFsJpeg->fsnav_dir_now);
            printf("fsnav_trk_now:%d\n",pFsJpeg->fsnav_trk_now);
            printf("myTime:%d\n", myTime);
                
            WriteToI2cA0(pos,(BYTE *)&pFsJpeg->fsnav_dir_now, sizeof(pFsJpeg->fsnav_dir_now));
            WriteToI2cA0(pos+sizeof(pFsJpeg->fsnav_dir_now),(BYTE *)&pFsJpeg->fsnav_trk_now, sizeof(pFsJpeg->fsnav_trk_now));
                             
            MSFFlag = mp3_file_msf ( pFsJpeg -> fsnav_trk_now ) ;
                // get the msf of current trk , added by caiyh , 15:55 , Nov 5th , 2004
                
            WriteToI2cA0 ( pos + sizeof(pFsJpeg->fsnav_dir_now)
                	+ sizeof ( pFsJpeg -> fsnav_trk_now ) , ( BYTE * ) & MSFFlag ,
                	sizeof(MSFFlag));
                // write the msf of current trk to i2c , added by caiyh , 15:55 , Nov 5th , 2004
            	
            WriteToI2cA0 ( pos + sizeof ( pFsJpeg -> fsnav_dir_now ) 
                	+ sizeof ( pFsJpeg -> fsnav_trk_now ) + sizeof ( MSFFlag ) , 
                	( BYTE * ) & myTime , sizeof ( myTime ) ) ;
			// write the myTime of current trk to i2c , modified by caiyh , 17:57 , Nov 16th , 2004
            	
            printf("MSFFlag:%d\n", MSFFlag);
        }
        else
        {                
            printf("resumeMSF:%x\n",resumeMSF);
            WriteToI2cA0(pos,(BYTE *)&resumeTRK, sizeof(resumeTRK));
            WriteToI2cA0(pos+sizeof(resumeTRK),(BYTE *)&resumeMSF, sizeof(resumeMSF));
        }
    }
    else
    {
            //resumeMSF = 1;//terry 2003-8-12 14:20
        if(play_state!=VCD_STATE_STOP)
            RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:41 .
        #ifndef DONT_CLR_RSM //hongfeng add 2005-11-03    
        clr_rsm_info();//terry,2003/8/13 01:21AM  
        #endif
                    printf("sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM])=%d\n",sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
            printf("sizeof(resumeMSF)=%d\n",sizeof(resumeMSF));  
        printf("resumeMSF:%d\n",resumeMSF);
        WriteToI2cA0(pos,p, sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));            
        WriteToI2cA0(pos+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),(BYTE *)&resumeMSF, sizeof(resumeMSF));
    }
#else//#ifdef SUPPORT_TEN_DISC_RESUME		//linrc add for 10 disc resume play 2005-5-12 10:09

    BYTE    *p;

#if defined(POWER_RESUME) || defined(SAME_DISC_RESUME)
	UINT32 MSFFlag = 0 ;
#endif   // POWER_RESUME , added by caiyh , 15:55 , Nov 5th , 2004

    if(clr){}//freyman just for warning message
    
#ifdef STOP_RESUME_DVD_VCD
    if(cd_type_loaded==CDDA)
	 return;
#endif
        
    if(cd_type_loaded==CDUNKNOWN) return;
    
    #ifdef DVD_5_DISC_RESUME//lijd 2005-8-1 11:04
	 if(cd_type_loaded!=CDDVD) 
	 return;
	#endif
	#ifndef DVD_5_DISC_RESUME//lijd 2005-6-30 22:55
    //Jack 06/10/02 added for simply release,any question pls call me:EXT 8304    
    if(!( (clr==0xf0)&&(cd_type_loaded!=CDROM)&&(cd_type_loaded!=CDDVD) ))
    resumeMSF = s_msf&0x00ffffff;
    #endif    
    //Jack 06/10/02 added for simply release,any question pls call me:EXT 8304    
    if(!( (clr==0xf0)&&(cd_type_loaded!=CDROM)&&(cd_type_loaded!=CDDVD) ))
    resumeTRK = cd_trk_now;
    
#ifdef POWER_RESUME
#ifndef STOP_RESUME_DVD_VCD//shenyj add for alco mp3 resume 050226
    if(Is_MP3_STATE()==0)   // don't clear the resume info of mp3 , added by caiyh , 10:53 , Nov 2nd , 2004
#endif
#endif   // POWER_RESUME
#ifndef DONT_CLR_RSM //hongfeng add 2005-11-03
    //Jack 06/10/02 added for simply release,any question pls call me:EXT 8304
    if(!( (clr==0xf0)&&(cd_type_loaded!=CDROM)&&(cd_type_loaded!=CDDVD) ))
    clr_rsm_info(); //terry,2003/8/13 01:21AM       
#endif
    //#ifdef RECORD_KEY//zhaoyanhua 03-11-2 18:56  //Mark by maoyong 2004.04.07
    //write DISC INFO to I2C
    UINT32 info1;
    int pos= 0;
    
#ifdef STOP_RESUME_DVD_VCD
    if(cd_type_loaded == CDROM)
        return;
#endif	
    
    if(cd_type_loaded==CDDVD) 
        pos = DVD_DISC_INFO;
    else if (cd_type_loaded==CDDA) 
    #ifdef ONLY_PRE_DISC_RESUME
        pos = DVD_DISC_INFO;
    #else    
    	pos = CDDA_DISC_INFO;
    #endif	
    else if (cd_type_loaded!=CDROM)
    #ifdef ONLY_PRE_DISC_RESUME 
        pos = DVD_DISC_INFO;
    #else    
    	pos = VCD_DISC_INFO;
    #endif	
     else 
    	pos = CDROM_INFO_BASE;
    #if 0//def POWER_RESUME //	qinhua,mark it,2006-7-1 03:06下午
    	else if(Is_MP3_STATE()==0)   /* to add the function of mp3 power resume , 
    				        added by caiyh , 11:05 , Nov 2nd , 2004 */
    #else
    //else 
    #endif   // POWER_RESUME
    	//return;  //qinhua,mark it,2006-7-1 03:06下午
    //Res=check_cdtype();
    if(cd_type_loaded!=CDDVD)
		info1=M2I(gettrkmsf_leadout()); //get from sysmain2.c
    else//CDDVD
   		info1 = same_disc_vob11_pos;    //search_file("VTS_01_1.VOB"); //get from atapi_if728.c
	
	WriteToI2cA0(pos,(BYTE *)&info1,sizeof(info1));
         
    //#endif
  
    
    {
        printf("save rsm info\n");
        
        p=(BYTE *)&pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM];
        if(cd_type_loaded!=CDDVD)
        {
            if(cd_type_loaded==CDROM) 
         	{
          #ifdef FS_FILE_POWER_RESUME	//qinhua,2006-6-13 05:03下午 
            
            #if defined (SUPPORT_USB)||defined (SUPPORT_CARD_STORAGE) ||defined (SPHE8202_CARD_STORAGE)   
             if(media_type==MEDIA_CD) 
           	#endif     
               { 
                if(Is_MP3_STATE())
                  	resumeMSF = myTime;
               	else if (((GetCurrentFileType() == CDROM_MP4)||(GetCurrentFileType() == CDROM_AVI ))&&!(IS_FILE_TYPE_MPG()||IS_FILE_TYPE_CDXA()))
               		resumeMSF = disp_time;
               	else
                 	resumeMSF = 0;
            	  
            	  resumeTRK= pFsJpeg -> fsnav_trk_will; 
            	  resume_fsnav_dir=pFsJpeg->fsnav_dir_will;
            	  Resume_Track_msf =iso9660_file [ resumeTRK ].loc;
            	  Resume_func_btn=pFsJpeg->gifsFuncBtn;
            	  
            	  WriteToI2cA0(CDROM_INFO_BASE,(BYTE *)&resume_fsnav_dir, sizeof(resume_fsnav_dir));
                //resume_fsnav_dir
                WriteToI2cA0(CDROM_INFO_BASE+sizeof(resume_fsnav_dir),(BYTE *)&resumeTRK, sizeof(resumeTRK));
                //resumeTRK
                WriteToI2cA0(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK),(BYTE *)&Resume_Track_msf, sizeof(Resume_Track_msf));
                //Resume_Track_msf
               	WriteToI2cA0(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK)+sizeof(Resume_Track_msf),(BYTE *)&resumeMSF, sizeof(resumeMSF));
                //resumeMSF
                WriteToI2cA0(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK)+sizeof(Resume_Track_msf)+sizeof(resumeMSF), &Resume_func_btn, sizeof(Resume_func_btn));
                //old_ControlArea
                    #if SAVE_CDROM_DEBUG
                    printf("---WRITE----resume_fsnav_dir=%d---------\n\n",resume_fsnav_dir);
				    printf("---WRITE----resumeTRK=%d---------\n\n",resumeTRK);
				    printf("---WRITE----Resume_Track_msf=%d---------\n\n",Resume_Track_msf);
				    printf("---WRITE----resumeMSF=%d---------\n\n",resumeMSF);
				    printf("---WRITE----Resume_func_btn=%d---------\n\n",Resume_func_btn);
				    #endif 
								
				#elif defined (MP3_POWER_RESUME) 
            	
            	//we only support MP3, not contain JPEG/Game
                if(Is_MP3_STATE()==0) resumeMSF = 0;
                
                printf("fsnav_dir_now:%d\n",pFsJpeg->fsnav_dir_now);
                printf("fsnav_trk_now:%d\n",pFsJpeg->fsnav_trk_now);
                printf("myTime:%d\n", myTime);
                
                WriteToI2cA0(CDROM_INFO_BASE,(BYTE *)&pFsJpeg->fsnav_dir_now, sizeof(pFsJpeg->fsnav_dir_now));
                WriteToI2cA0(CDROM_INFO_BASE+sizeof(pFsJpeg->fsnav_dir_now),(BYTE *)&pFsJpeg->fsnav_trk_now, sizeof(pFsJpeg->fsnav_trk_now));
                             
                MSFFlag = mp3_file_msf ( pFsJpeg -> fsnav_trk_now ) ;
                // get the msf of current trk , added by caiyh , 15:55 , Nov 5th , 2004
                
                WriteToI2cA0 ( CDROM_INFO_BASE + sizeof(pFsJpeg->fsnav_dir_now)
                	+ sizeof ( pFsJpeg -> fsnav_trk_now ) , ( BYTE * ) & MSFFlag ,
                	sizeof(MSFFlag));
                // write the msf of current trk to i2c , added by caiyh , 15:55 , Nov 5th , 2004
            	
                WriteToI2cA0 ( CDROM_INFO_BASE + sizeof ( pFsJpeg -> fsnav_dir_now ) 
                	+ sizeof ( pFsJpeg -> fsnav_trk_now ) + sizeof ( MSFFlag ) , 
                	( BYTE * ) & myTime , sizeof ( myTime ) ) ;
		// write the myTime of current trk to i2c , modified by caiyh , 17:57 , Nov 16th , 2004
            	
            	printf("MSFFlag:%d\n", MSFFlag);
	       
           	 }
           	 #endif//#ifdef FS_FILE_POWER_RESUME	//qinhua,2006-6-13 05:03下午 
           	} 
          	else //cd/vcd
            {
                int pos;
                
                if(cd_type_loaded==CDDA) pos=CDDA_INFO_BASE;
                else pos=VCD_INFO_BASE;
                
                printf("resumeMSF:%x\n",resumeMSF);
                //Jack 06/10/02 added for simply release,any question pls call me:EXT 8304
                if(clr == 0xf0)
                {
                    UINT32  PreresumeTRK;
                    UINT32  PreresumeMSF;
                    PreresumeTRK = resumeTRK;
                    PreresumeMSF = resumeMSF;
                    resumeTRK = 0;
                    resumeMSF = 0;
                    
                    WriteToI2cA0(pos,(BYTE *)&resumeTRK, sizeof(resumeTRK));
                    WriteToI2cA0(pos+sizeof(resumeTRK),(BYTE *)&resumeMSF, sizeof(resumeMSF));
                    
                    resumeTRK = PreresumeTRK;
                    resumeMSF = PreresumeMSF;
                }
                else
               {
                WriteToI2cA0(pos,(BYTE *)&resumeTRK, sizeof(resumeTRK));
                WriteToI2cA0(pos+sizeof(resumeTRK),(BYTE *)&resumeMSF, sizeof(resumeMSF));
            	}
        	}
        }
       	else //dvd
        {
            //resumeMSF = 1;//terry 2003-8-12 14:20
            #ifdef DVD_5_DISC_RESUME//lijd 2005-7-13 17:14
             if((play_state!=VCD_STATE_STOP)&&(StopTimes!=1)&&(clr!=0xf0))  //Jack 06/10/02 added for simply release
                 RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:41 .
            #else
            if((play_state!=VCD_STATE_STOP)&&(clr!=0xf0))   //Jack 06/10/02 added for simply release
				RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:41 .
            #endif 
            #ifndef DONT_CLR_RSM //hongfeng add 2005-11-03
            clr_rsm_info();//terry,2003/8/13 01:21AM    
            #endif
            
            #if defined(STOP_RESUME_DVD_VCD)&&defined(DISC_ID_IN_FLASH)
            if(need_record  == REAL_RECORD_VALUE)
                resumeMSF = 1;
            #endif

			#ifndef  SUPPORT_LAST_MEMERY
            clr_rsm_info();//terry,2003/8/13 01:21AM    
            #endif//end=> #ifndef  SUPPORT_LAST_MEMERY
            printf("resumeMSF:%d\n",resumeMSF);
            WriteToI2cA0(DVD_INFO_BASE,p, sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));            
            WriteToI2cA0(DVD_INFO_BASE+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),(BYTE *)&resumeMSF, sizeof(resumeMSF));
			//print_block(p,sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
    
     // psprintf(debug_buffer,"pDSV->rsm_info[i].dRSM_TTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_TTN);
     // UART0_puts(debug_buffer);
     // psprintf(debug_buffer,"pDSV->rsm_info[i].dRSM_PTTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_PTTN);
     // UART0_puts(debug_buffer);
     // psprintf(debug_buffer,"pDSV->rsm_info[i].dRSM_AGLN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_AGLN);
     // UART0_puts(debug_buffer);
     // psprintf(debug_buffer,"pDSV->rsm_info[i].dRSM_ASTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_ASTN);
     // UART0_puts(debug_buffer);
     // psprintf(debug_buffer,"resumeMSF:%x\n",resumeMSF);    
     // UART0_puts(debug_buffer);
        }
    }
#endif//endif SUPPORT_TEN_DISC_RESUME
#ifdef TURN_OFF_POWER_RESUME //zxb 2005-8-3 23:19 when play_normal resumeMSF should be 0,
	//but when turn_off_power_resume is defined,resumeMSF will not be 0 when play vcd,
	//and when press stop ,system will stop directly not pre_stop.
	if((play_state==VCD_STATE_NORMAL)
	||(play_state== VCD_STATE_FASTFORWARD)
	|| (play_state==VCD_STATE_FASTBACKWARD))
		resumeMSF=0;
#endif		
    }
    
static inline void same_disc_LoadRsmInfo(void)
    {
#ifdef SUPPORT_TEN_DISC_RESUME		//linrc add for 10 disc resume play 2005-5-12 10:15
    BYTE    *p,v[4];				//if you have any problem,see DOC file

    printf("reading...\n");
    printf("---  Rsume_Disc_Index=%d  ---\n",Rsume_Disc_Index);

    p=(BYTE *)&pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM];
    
    if(cd_type_loaded==CDDVD)
    {
      ReadFromI2cA0(MSF_I2C_ADDR[Rsume_Disc_Index],p, sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
      ReadFromI2cA0(MSF_I2C_ADDR[Rsume_Disc_Index]+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),(BYTE *)&resumeMSF, sizeof(resumeMSF));
      
      printf("pDSV->rsm_info[i].dRSM_TTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_TTN);
      printf("pDSV->rsm_info[i].dRSM_PTTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_PTTN);
      printf("pDSV->rsm_info[i].dRSM_AGLN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_AGLN);
      printf("pDSV->rsm_info[i].dRSM_ASTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_ASTN);
      printf("Read resumeMSF:%x size %d %d\n",resumeMSF,sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),sizeof(resumeMSF));     
    }else if(cd_type_loaded==CDROM)
    {
    	resume_fsnav_dir = ReadFromI2cA0_32(MSF_I2C_ADDR[Rsume_Disc_Index],v, sizeof(resume_fsnav_dir));       
        resume_fsnav_trk = ReadFromI2cA0_32(MSF_I2C_ADDR[Rsume_Disc_Index]+sizeof(pFsJpeg->fsnav_dir_now),v, sizeof(resume_fsnav_trk));
        myTime = ReadFromI2cA0_32(MSF_I2C_ADDR[Rsume_Disc_Index]+sizeof(pFsJpeg->fsnav_dir_now) + sizeof(resume_fsnav_trk),v, sizeof(myTime));
            
        printf("resume_fsnav_dir:%d\n",resume_fsnav_dir);
        printf("resume_fsnav_trk:%d\n",resume_fsnav_trk);
    	printf("myTime:%d\n", myTime);
	}else
    {
        int pos;
        
        pos = MSF_I2C_ADDR[Rsume_Disc_Index];
        //if(cd_type_loaded==CDDA) pos = CDDA_INFO_BASE;
        //else pos = VCD_INFO_BASE;

        ReadFromI2cA0((UINT16)pos,(BYTE *)&resumeTRK, sizeof(resumeTRK));
        printf("resumeTRK:%x\n",resumeTRK);
        resumeMSF = ReadFromI2cA0_32(pos+sizeof(resumeTRK),v, sizeof(resumeMSF));
        printf("resumeMSF:%x %x %x %x %x\n",resumeMSF,v[0],v[1],v[2],v[3]);
    }
#else//#ifdef SUPPORT_TEN_DISC_RESUME		//linrc add for 10 disc resume play 2005-5-12 10:09
    BYTE    *p,v[4];

    printf("reading...\n");

    #ifdef STOP_RESUME_DVD_VCD
    if(cd_type_loaded==CDROM)  
        return;              
    if(!IS_DVD_VCD_DISC())
        return;
    #endif

    p=(BYTE *)&pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM];
    
    if(cd_type_loaded==CDDVD)
    {
      ReadFromI2cA0(DVD_INFO_BASE,p, sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
      ReadFromI2cA0(DVD_INFO_BASE+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),(BYTE *)&resumeMSF, sizeof(resumeMSF));
      //print_block(p,sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
	  #ifdef PARENT_PWD_DEFAULT_NULL
	  RSM_Flag = 1;
	  #endif
      printf("pDSV->rsm_info[i].dRSM_TTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_TTN);
      printf("pDSV->rsm_info[i].dRSM_PTTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_PTTN);
      printf("pDSV->rsm_info[i].dRSM_AGLN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_AGLN);
      printf("pDSV->rsm_info[i].dRSM_ASTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_ASTN);
      printf("Read resumeMSF:%x size %d %d\n",resumeMSF,sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),sizeof(resumeMSF));    

   //   psprintf(debug_buffer,"pDSV->rsm_info[i].dRSM_TTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_TTN);
   //   UART0_puts(debug_buffer);
   //   psprintf(debug_buffer,"pDSV->rsm_info[i].dRSM_PTTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_PTTN);
   //   UART0_puts(debug_buffer);
   //   psprintf(debug_buffer,"pDSV->rsm_info[i].dRSM_AGLN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_AGLN);
   //   UART0_puts(debug_buffer);
   //   psprintf(debug_buffer,"pDSV->rsm_info[i].dRSM_ASTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_ASTN);
   //   UART0_puts(debug_buffer);
   //   psprintf(debug_buffer,"Read resumeMSF:%x size %d %d\n",resumeMSF,sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),sizeof(resumeMSF));    
   //   UART0_puts(debug_buffer);

      
    }else if(cd_type_loaded==CDROM)
    {
      resume_fsnav_dir = ReadFromI2cA0_32(CDROM_INFO_BASE,v, sizeof(resume_fsnav_dir));       
      resume_fsnav_trk = ReadFromI2cA0_32(CDROM_INFO_BASE+sizeof(pFsJpeg->fsnav_dir_now),v, sizeof(resume_fsnav_trk));
      myTime = ReadFromI2cA0_32(CDROM_INFO_BASE+sizeof(pFsJpeg->fsnav_dir_now) + sizeof(resume_fsnav_trk),v, sizeof(myTime));
            
      printf("resume_fsnav_dir:%d\n",resume_fsnav_dir);
      printf("resume_fsnav_trk:%d\n",resume_fsnav_trk);
    printf("myTime:%d\n", myTime);
}else
    {
      int pos;
        
      if(cd_type_loaded==CDDA) pos = CDDA_INFO_BASE;
      else pos = VCD_INFO_BASE;

      ReadFromI2cA0(pos,(BYTE*)&resumeTRK, sizeof(resumeTRK));
      printf("resumeTRK:%x\n",resumeTRK);
      resumeMSF = ReadFromI2cA0_32(pos+sizeof(resumeTRK),v, sizeof(resumeMSF));
      printf("resumeMSF:%x %x %x %x %x\n",resumeMSF,v[0],v[1],v[2],v[3]);
    }
#endif//endif SUPPORT_TEN_DISC_RESUME
    }

void  save_cmp_disc_info(UINT32 info1)
    {
#ifdef SUPPORT_TEN_DISC_RESUME	//linrc add for 10disc resume play 2005-5-12 10:11
	int i;						//if you have any problem,see DOC file
	UINT32 Rom_Info;
	
	printf("---  info1=0x%x  ---\n",info1);
	for(i=0;i<RESUME_DISC_NUMBER;i++)
	{
		ReadFromI2cA0(Info_I2C_ADDR[i],(BYTE *)&Rom_Info,sizeof(Rom_Info));
		printf("---  Rom_Info=0x%x  ---\n",Rom_Info);
		if(info1==Rom_Info)
		{
			Rsume_Disc_Index = i;
			same_disc_flag=1;
			break;
		}
		else
		{
			resumeMSF=0;
	    	same_disc_flag=0;
		}
	}
#else//#ifdef SUPPORT_TEN_DISC_RESUME		//linrc add for 10 disc resume play 2005-5-12 10:09
    UINT8 v[4];
    UINT32 rom_info1;
    int pos;

#ifdef DISC_ID_IN_FLASH    
    int i,j,index_match,first_empty_indx;
    
  #endif
    
	printf("save & compare disc info ,in\n");
	printf("info1:%x\n",info1);
	#ifdef DVD_5_DISC_RESUME//lijd 2005-6-16 15:56
	 if(cd_type_loaded!=CDDVD) 
	 return;
	#endif
	
    if(cd_type_loaded==CDDVD) 
    pos = DVD_DISC_INFO;
    else if (cd_type_loaded==CDDA)
    #ifdef ONLY_PRE_DISC_RESUME
     pos = DVD_DISC_INFO;
    #else 
     pos = CDDA_DISC_INFO;
    #endif
    else if (cd_type_loaded!=CDROM)
    #ifdef ONLY_PRE_DISC_RESUME 
     pos = DVD_DISC_INFO;
    #else  
     pos = VCD_DISC_INFO;
    #endif 
    else return;

#ifndef DISC_ID_IN_FLASH

	rom_info1 = ReadFromI2cA0_32(pos,v,sizeof(rom_info1));
	//rom_info2 = ReadFromI2cA0_32(pos+sizeof(rom_info1),v,sizeof(rom_info2));

	//if( (rom_info1==info1)&&(rom_info2==info2) ) 
	if(rom_info1==info1) 
	{
	    same_disc_flag=1;
	}else
	{
	    resumeMSF=0;
	    same_disc_flag=0;
	    //Maoyong changed 2004.04.07. record disc info just in record action not after reading disc.
		//#ifndef RECORD_KEY
	//NOTE:
	//must mask it,else cause record error.    
	    //WriteToI2cA0(pos,(BYTE *)&info1,sizeof(info1));
		//#endif
	    //WriteToI2cA0(pos+sizeof(info1),(BYTE *)&info1,sizeof(info2));
	}
#else//#ifndef DISC_ID_IN_FLASH

   current_resume = TOTAL_RESUME;
   rom_info1 = ReadFromI2cA0_32(pos,v,sizeof(rom_info1));

#ifdef RW_NVMEM
/* swpong 2006 0320 */
   ReadFromNVMEM(TYPE_DISC_ID, 0, disc_resume_index, sizeof(disc_resume_index));
#else  //RW_NVMEM     
   memcpy(disc_resume_index,&disc_resume[current_resume].disc_id,sizeof(disc_resume_index));
#endif //RW_NVMEM   
   if ((disc_resume_index[0]==disc_resume_index[1])  || //swpong 2006 0417 (disc_resume_index[0]<0) ||
   	 (disc_resume_index[0]>= TOTAL_RESUME))
   	{
   		for (i=0; i<TOTAL_RESUME; i++)
   			disc_resume_index[i] = 0xff;
   	}

   index_match = 0;
   first_empty_indx = -1;
   current_resume = 0;

// find the current index to the disc resume information
   for (i=0; i<TOTAL_RESUME; i++)
   {
       //empty index, use it to store resume information  
   	//swpong 2006 0417 if ((disc_resume_index[i]<0) || (disc_resume_index[i]>= TOTAL_RESUME))
   	if (disc_resume_index[i]>= TOTAL_RESUME) //swpong 2006 0417
   	{
   		current_resume = i;
   		break;
   	}


   	//compare disc information with the current disc resume
   	current_resume = disc_resume_index[i];
   	rom_info1 = ReadFromI2cA0_32(pos,v,sizeof(rom_info1));

       //disc information not matches the current disc resume, continue.
  	if(rom_info1==0)
  	{
  		if (first_empty_indx <0)
  			first_empty_indx = i;
		continue;
  	}

      //disc information mateces current disc resume
	if(rom_info1==info1) 
	{
		index_match = 1;
		break;
	}
   }

   //if none of the disc resume information matches the disc information, 
  // use first exmpty index as current resume index
   if ((index_match ==0) && (first_empty_indx >=0))
   {
   	i = first_empty_indx;
   	current_resume = disc_resume_index[i];
   }


   if (i==TOTAL_RESUME) --i;


// the first index in the disc resume points to the current resume
//shift the disc resume index up by 1.
   if (i>0)
   {
   	for (j=i;j>0;j--)
   	{
   		disc_resume_index[j]=disc_resume_index[j-1];
   	}
   }

   disc_resume_index[0]=current_resume;

   		
  if(rom_info1==info1) 
  {
         same_disc_flag=1;
   }
   else 
  {
	    resumeMSF=0;
	    same_disc_flag=0;
  }

   
    
#endif//#ifndef DISC_ID_IN_FLASH
#endif//endif SUPPORT_TEN_DISC_RESUME
}
#ifdef	POLLING_10MS_SAVE_RESUME		//Maoyong 2004.03.01
extern	BYTE 	rsm_I2c_write_cnt;
//Note: Just for DVD Disc resume info save
#define RSM_INFO_SIZE	 	sizeof(same_disc_vob11_pos)
#define RSM_MSF_SIZE		sizeof(resumeMSF)
#define RSM_DSV_SIZE		sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM])
void polling_10ms_save_rsm(void)
{		
	if(rsm_I2c_write_cnt < 	DVD_RSM_WRITE_SIZE)
	{
		if( rsm_I2c_write_cnt < RSM_INFO_SIZE )
			WriteToI2cA0(DVD_DISC_INFO + rsm_I2c_write_cnt,(BYTE *)&same_disc_vob11_pos + rsm_I2c_write_cnt, 1);
		else if( rsm_I2c_write_cnt < (RSM_INFO_SIZE + RSM_DSV_SIZE))
			WriteToI2cA0(DVD_INFO_BASE + rsm_I2c_write_cnt- RSM_INFO_SIZE, 
			             (BYTE *)&pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM] + rsm_I2c_write_cnt - RSM_INFO_SIZE, 
			             1);
		else
			WriteToI2cA0(DVD_INFO_BASE + rsm_I2c_write_cnt - RSM_INFO_SIZE,
						 (BYTE *) &resumeMSF + rsm_I2c_write_cnt - RSM_INFO_SIZE - RSM_DSV_SIZE,
						 1);
		
		rsm_I2c_write_cnt++;	
	}
}	
#endif			//end ifdef	POLLING_10MS_SAVE_RESUME
#else	//else #if defined (POWER_RESUME)|| defined(SAME_DISC_RESUME)||defined (RECORD_KEY)

static inline void basic_RsmInfo2Flash(int clr)
{
    BYTE    *p;             
    
    printf("!!!run save_tuner_setup ,size:%d\n",sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
    if( is_menu() || clr )
    {
		resumeMSF = 0;
		resumeTRK = 0;
		pFsJpeg->fsnav_dir_now = 0;
		pFsJpeg->fsnav_trk_now = 0;
		myTime=0;
    }else
    {
        if(cd_type_loaded!=CDDVD)
        {
            resumeMSF = s_msf&0x00ffffff;
            resumeTRK = cd_trk_now;
            if( (cd_type_loaded==CDROM)&&( !Is_MP3_STATE() ) ) { //Jeff 20021114//nono 20021123 modified
                //we only support MP3, not contain JPEG/Game
                resumeMSF = 0;
            }
        }else
        {
            resumeMSF = 1;
            if(play_state!=VCD_STATE_STOP)//20021014
				RSM_save(0xff,DVD_PRESTOP_RSM_ITEM); //chenzhao 2006-9-13 11:41 .
        }        
    }
	
    p=(BYTE *)&pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM];    
    WriteToI2cA0(128,p, sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
    
    WriteToI2cA0(128+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),(BYTE *)&resumeTRK, sizeof(resumeTRK));
    printf("resumeMSF:%x\n",resumeMSF);
    
    WriteToI2cA0(128+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM])+sizeof(resumeTRK),(BYTE *)&resumeMSF, sizeof(resumeMSF));
    printf("save rsm msf fail\n");
    
    printf("fsnav_dir_now:%d\n", pFsJpeg->fsnav_dir_now);
    WriteToI2cA0(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF), 
		(BYTE *)&(pFsJpeg->fsnav_dir_now), sizeof(pFsJpeg->fsnav_dir_now));
    
    printf("fsnav_trk_now:%d\n", pFsJpeg->fsnav_trk_now);
    WriteToI2cA0(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF) + sizeof(pFsJpeg->fsnav_dir_now), 
		(BYTE *)&(pFsJpeg->fsnav_trk_now), sizeof(pFsJpeg->fsnav_trk_now));
    
    //Jeff 20020902
    printf("myTime:%d\n", myTime);
    WriteToI2cA0(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF) + sizeof(pFsJpeg->fsnav_dir_now) + sizeof(pFsJpeg->fsnav_trk_now), 
		(BYTE *)&myTime, sizeof(myTime));
    
}

static inline void basic_LoadRsmInfo(void)
{
    BYTE    *p,v[4];            
	
    printf("reading...\n"); 
    
    p=(BYTE *)&pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM];    
    ReadFromI2cA0(128,p, sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]));
    {
        printf("pDSV->rsm_info[i].dRSM_TTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_TTN);
        printf("pDSV->rsm_info[i].dRSM_PTTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_PTTN);
        printf("pDSV->rsm_info[i].dRSM_AGLN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_AGLN);
        printf("pDSV->rsm_info[i].dRSM_ASTN:%x\n",pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_ASTN);
    }
    
    ReadFromI2cA0(128+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]),(BYTE *)&resumeTRK, sizeof(resumeTRK)); //terry,2005/6/20 10:02と,clear warning message
    {
        printf("resumeTRK:%x\n",resumeTRK);     
    }
    
    resumeMSF = ReadFromI2cA0_32(128+sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM])+sizeof(resumeTRK),v, sizeof(resumeMSF));
    {
        printf("resumeMSF:%x %x %x %x %x\n",resumeMSF,v[0],v[1],v[2],v[3]);             
    }      
	
    resume_fsnav_dir = ReadFromI2cA0_32(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF),
		v, sizeof(resume_fsnav_dir));
    {
        printf("resume_fsnav_dir:%d\n",resume_fsnav_dir);               
    }      
	
    resume_fsnav_trk = ReadFromI2cA0_32(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF) + sizeof(pFsJpeg->fsnav_dir_now),
		v, sizeof(resume_fsnav_trk));
    {
        printf("resume_fsnav_trk:%d\n",resume_fsnav_trk);               
    }
    
    myTime = ReadFromI2cA0_32(128 + sizeof(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM]) + sizeof(resumeTRK) + sizeof(resumeMSF) + sizeof(pFsJpeg->fsnav_dir_now) + sizeof(resume_fsnav_trk),
		v, sizeof(myTime));
    {
    	printf("myTime:%d\n",myTime);               
    }
}
#endif	//#if defined (POWER_RESUME)|| defined(SAME_DISC_RESUME)||(RECORD_KEY)

/*
record per second,we only recode the changed content!
and we also distinguish cd type
*/   
void RsmInfo2Flash(int clr)
		{
#ifdef RECORD_PER_SECOND				//lijinhai   2-12-4 9:49
    power_rsm_ps_RsmInfo2Flash(clr);
#elif defined(SAME_DISC_RESUME)	|| defined(POWER_RESUME) || defined(RECORD_KEY)
    same_disc_RsmInfo2Flash(clr);    
#else									
    basic_RsmInfo2Flash(clr);
#endif    
}
			
void LoadRsmInfo(void)
{ 
    //goto_active=1;//terry,2004/3/2 11:56AM
#if defined (SAME_DISC_RESUME) || defined(POWER_RESUME) || defined(RECORD_KEY)
    same_disc_LoadRsmInfo();
#else
    basic_LoadRsmInfo();
#endif    
}

/*========================================================================
 record resume util funcs for flow control in sysmain2.c SYSTEM_READ_TITLE
 =========================================================================*/
#ifdef RECORD_KEY
/*
 * FUNC Descrition:
 *     to check if user has entered "RECORD" 
 *     only enter"RECORD" key,then play from the recorded point.
 *     else excute its corresponding function.
 *
 *  RETURN:
 *     1:   entered RECORD 
 *     0:   other key
 *  
 *  zhaoyanhua  2003-11-29 20:12
 *
 */
static inline BYTE CheckRecordKey(void)
{
    BYTE iRes = 0;
    
//NOTE:
// if you want change the RECORD_OSD_SHOW_TIME value, 
// must change it in file ir_parser.c at the same time.
//zhaoyanhua  2003-12-12 15:18
#define RECORD_OSD_SHOW_TIME  14  

 
//to avoid SPECTRUM effect OSD    
#ifdef DYNAMIC_SPECTRUM  
    BYTE tempDisp = bEqDisplay;
#endif    
    //if the disc has recorded,Show OSD and do some operation.
    //NOTE:
    // use the flag "same_disc_flag" to calculate the time(6S)
    // (14-2) *500ms = 6s   
    osd_init_record();
    //show strings.
    #ifdef NINTAUS_OSD_STR
    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_RECORD_1]);
    osd_DrawRegionString(2,0,linebuf,0x0a,0,0);//3-11-21 9:25张宇P
    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_RECORD_2 ]);
    osd_DrawRegionString(2,7,linebuf,0x0a,0,0);//3-11-21 9:25张宇P
    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_RECORD_3]);
    osd_DrawRegionString(2,14,linebuf,0x0a,0,0);//3-11-21 9:25张宇P
    #else//NINTAUS_OSD_STR
    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_RECORD_1SENTENCE]);
    osd_DrawRegionString(2,0,linebuf,0x0a,0,0);//3-11-21 9:25张宇P
    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_RECORD_2SENTENCE]);
    osd_DrawRegionString(2,7,linebuf,0x0a,0,0);//3-11-21 9:25张宇P
    psprintf(linebuf,"%s",_OsdMessegeFont1[osd_font_mode][STR_OS_RECORD_3SENTENCE]);
    osd_DrawRegionString(2,14,linebuf,0x0a,0,0);//3-11-21 9:25张宇P
    #endif//NINTAUS_OSD_STR                         
                                    
#ifndef MODIFY_RECORD_KEY//20040217                                 
    run_pause_setting();//pause                             
#endif//MODIFY_RECORD_KEY
                                    
    while(same_disc_flag > 0)
    {
        polling();
        if(same_disc_flag == RECORD_OSD_SHOW_TIME)     
            break;
    }
                                    
#ifdef DYNAMIC_SPECTRUM//zhaoyanhua add 2003-12-2 22:25
    bEqDisplay = tempDisp;
    if(bEqDisplay)
        Show3dspectrum();
    else
#endif  
    osd_init();
    
#ifdef MODIFY_RECORD_KEY//20040217
    //chg2normal_play(PAUSE2NORM,TRANSFER);
#else//MODIFY_RECORD_KEY
    chg2normal_play(FAST2NORM|PAUSE2NORM|SLOW2NORM,REALPLAY);
#endif//MODIFY_RECORD_KEY
    
    if(same_disc_flag == RECORD_OSD_SHOW_TIME)
    {    
        same_disc_flag = 0;
        iRes = 0;
    }
    else
        iRes = 1;
    
    return iRes;                                    
}
#endif  //end   #ifdef  REOCRD_KEY

#ifdef  CHECK_RECORD_DISK_PARENT_LVL
/****************************************************************
 *  do DVD-VIDEO disk level control for a recorded disc.
 *  RETURN:
 *     1: Disc not need do level control or Level is same as user set,
 *        or input a correct password
 *     0: Level is not same as user set and input a incorrect password
 *  Maoyong 2004.02.20  16:38 
 ****************************************************************/
BYTE CheckDiscParentLvl(void)
{
    BYTE iRes = 1;
    UINT32 isPasswdRight;
    
    //check If no need to do Level Control
    if(cd_type_loaded != CDDVD)
        return iRes;
    else 
    {
    #ifdef DVD_AUDIO        //do level check just for DVD video
        if(dAMG_LSN != 0)   
            return iRes;                    
	#endif
        if(pDSV->rsm_info[DVD_PRESTOP_RSM_ITEM].dRSM_PTL_LVL <= UserSet.ParentalLvl)
            return iRes;
    }   
    #ifdef VCD_SHOW_PBC_NOT_MENUPLAY//libing 2005-7-1 18:10
    UserSet.parental_ststus=1;
    #else   
    UserSet.parental_ststus=0;	
    #endif
    isPasswdRight = setup_CheckPasswd();
             
    //password error!                                                                                                                                                   
    //if(UserSet.parental_ststus == 0)    
    if(isPasswdRight)
    {	
    	printf("-------sys_cmd = %d, system_state = %d-------------\n", sys_cmd, system_state);
    	//Maoyong 2004.03.06, IRC_POWER/IRC_EJECT special process
		if(user_input_pwd ==2)
		{
			user_input_pwd = 0;			
			//make not to change to SYSTEM_BRWOSE.  In fact, ignore POWER key.
			system_state = SYSTEM_OPEN;	
			sys_cmd = 0;			
		}
    	else
    	{	sys_cmd = 0;
    		system_state = SYSTEM_STOP;
    		play_state = VCD_STATE_STOP;    	
    		ircmd_stop();    	    		
    	}
    	iRes = 0;   
    }
    return iRes;            
}                                                    
#endif  //end #ifdef CHECK_RECORD_DISK_PARENT_LVL 2004.02.20 maoyong
		
/****************************************************************
 *  check if recorded disc need to do record resume action.
 *  RETURN:
 *     0: 	Not need,    
 *     1:   Yes, need
 *  Maoyong 2004.02.20  16:38
 ***************************************************************/ 
BYTE CheckIfRealRsm(void)
{
	#ifdef DVD_AUDIO//nono 2004-2-25 0:40
    if( (cd_type_loaded==CDDVD) && (dAMG_LSN!=0) )
        return 0;
	#endif //DVD_AUDIO
		
	#ifdef	RECORD_KEY
	if(CheckRecordKey())
		return 1;			
	else
		return 0;
	#else	
		return 1;			//No record key, direct do resume play		
	#endif	//RECORD_KEY 
}

/****************************************************************
 *  check if the disc is recorded and if need to do record resume. 
 *  RETURN:
 *     0:   should not load rsm
 *     1:   need to load 
 *  Maoyong 2004.02.20  16:38
 ****************************************************************/
BYTE CheckLoadRsmInfo(void)
{	
	#if !defined(POWER_RESUME)&& !defined(SAME_DISC_RESUME)&& !defined (RECORD_KEY)
	return 0;
	#endif

    #ifdef STOP_RESUME_DVD_VCD
    if(!IS_DVD_VCD_DISC())
        return 0;
    #ifdef DISC_ID_IN_FLASH
    else
        same_disc_onoff = 1;
    #endif
    #endif
    
	//for some customers, has eject record, but not need to choose if en/dis resume play 
	//in setup Menu, but this case is rarely used.
	#if defined(NOT_SHOW_SAME_DISC_RESUME)&&defined(SAME_DISC_RESUME)
	same_disc_onoff = 1;
	#endif

        #ifdef SUPPORT_TEN_DISC_RESUME
        printf("same_disc_onoff=%d,,,,,same_disc_flag=%d.....\n",same_disc_onoff,same_disc_flag);
        #endif


	#if 0//def SAME_DISC_RESUME   //zxb 2005-5-26 15:57
	//if not mark SAME_DISC_RESUME ,the disc will always resume.
	same_disc_onoff = 1;
	#endif

	/*===========================================================================	
	The folling pre-compile condition is for basic usage.
	(1)RECORD KEY: You need not to check same_disc_onoff. resume play is controlled
				   by user.	It can be treated as highest level
	(2)POWER_RESUME: you can add "same_disc_onoff" constrict by your own definiton	
	Please don't change sequence!	
	So, please use your owe definition to make combination of different resum func.
	=============================================================================*/
	#if defined(RECORD_KEY)	//if has "Record" on IR Panel, control resume by "Record" Key
	if(same_disc_flag)
	#elif defined(POWER_RESUME) && defined(SAME_DISC_RESUME)	//power+eject Out Record
        #ifdef DVD_5_DISC_RESUME//lijd 2005-6-16 14:19
    	    if(same_disc_flag)
    	#else 
    if(same_disc_flag && same_disc_onoff)
        #endif
    #elif defined(POWER_RESUME)			//just use power record. maybe seldom used dependently
    if(same_disc_flag)
	#elif defined(SAME_DISC_RESUME)		//just use eject out record
    if(same_disc_flag && same_disc_onoff)
	#endif
    {
    	if(CheckIfRealRsm())
    		return 1;    
    }    
   	return 0;
} 

void RecordRsmPlay(void)
{
	#ifdef DVD_5_DISC_RESUME//lijd 2005-6-16 15:54
		same_disc_flag=0;// If not clear it, play other disc also resume.
	#endif	
	if( (resumeMSF<0x3fffffff)&&(resumeMSF>0) )//nono del "=" 5-4-28 23:28//lijd for ORITRON 1M X 16bit 5 DVD DISC RESUME
	{
         //terry,2003/8/13 01:01AM
         sys_cmd=CMD_FUNC|CMD_FUNC_RESUME;
         #ifdef RECORD_KEY         //fengjl add 3-12-7 15:03
         PrintOsdMsg(STR_OS_RECORD_RESUME,REGION1,2,0);
         #else
         OSD1000ISP_STATUS(OSDISP_RESUME, OSDIR_GLOBAL);

         PrintOsdMsg(STR_OS_RESUME,REGION1,2,0);
         #endif
         printf("======= system CMD_FUNC_RESUME========\n");                                    
    }
}
#ifdef DVD_5_DISC_RESUME//lijd 2005-6-22 16:38
void Clear5DVDResumeInfo(void)
{
	BYTE *p;
	int i,j;
	LoadModual(MODUAL_CDROM); 	
	//FlashEraseSector(FLASH_ERASE_SECTOR);
	for(i=0;i<TOTAL_RESUME+4;i++)
	{
		p= &disc_resume[i].disc_info;
		for (j=0; j<68;j++) *p++ = 0;
	}
}
#endif

#ifdef SUPPORT_TEN_DISC_RESUME
void ClearDVDResumeInfo(void)   //hongfeng for set default to clear DVD resume play info
{
    int n;
    BYTE m=0;
    for(n=0;n<(RESUME_DISC_NUMBER*6);n++)
    {
    WriteToI2cA0(Info_I2C_ADDR[0]+n,&m,1);
    }   
}
#endif


#if defined(DISC_ID_IN_FLASH) && defined(SAME_DISC_RESUME)

//#####################################################
//      We use the last sector for resume information, 
//      64KB is divided into 64 sections which is 1KB, 
//      first section is occupied by array of free-section index
//f0000h-f03ffh     (free-section index array)(value is 0~62)
//f0400h-f07ffh     (Num 0 section)
//f0800h-f0bffh     (Num 1 section)
//f0c00h-f0fffh     (Num 2 section)
//...
//ff000h-ff3ffh     (Num 59 section)
//ff400h-ff7ffh     (Num 60 section)
//ff800h-ffbffh     (Num 61 section)
//ffc00h-fffffh     (Num 62 section)
//

UINT32  free_section_in_flash;

//
// Function     :   Resume_section_finder
// Description	:   find current or free sections 
// Input        :   iStartAddr  -> start address of free-section index array
//                  iLen        -> length of free-section index array
//                  isWriting   -> 1: finder for writing, 0: finder for reading
// Output       :   if isWriting==0, return current-section(last written) index
//                     isWriting==1, return free-section index( 1 section = 1KB)
// Note          :  record the lastest location of resume information
//                  E.g. 0x0, 0xff, 0xff, 0xff, 0xff....(current-section=0, free-section=1)
//                  E.g. 0x0, 0x1, 0x2, 0xff, 0xff....(current-section=2, free-section=3)
//
UINT32 Resume_section_finder(UINT32 iStartAddr, UINT32 iLen, UINT32 isWriting)
{
    #ifdef  RESUME_INFO_DBG
        printf_w("F finder: [%x, %d][%d][%d]\n", iStartAddr,iLen,free_section_in_flash,isWriting);
        FlashDelay(10000);
    #endif
    
    UINT32  free_section =0;
    UINT32  array_length = 0;
    int is_free_section_finded = 0;   

    array_length = (rsm_flash_sec_size-(1<<rsm_free_section_idx_array_size)) / (1<<rsm_free_section_size);
    
    if(((system_flash_id&0xffff)==0x1c42)||((system_flash_id&0xffff)==0x7f12))
    {
        //for Eon and Amic spi flash, no byte programming, write four byte once
        array_length *=4;     
    }    
    
    BYTE   i=0, temp[array_length];
    
    //SPI_Resume_Read(rsm_flash_start_addr, (BYTE *)temp, array_length);
    //Resume_FlashRead(rsm_flash_start_addr, (BYTE *)temp, array_length);
    Resume_FlashRead(iStartAddr, (BYTE *)temp, array_length);
    
    #ifdef  RESUME_INFO_DBG  
        printf_w("F finder, array length=%d\n", array_length);
    #endif
    
    while (array_length) 
    {   
        #ifdef  RESUME_INFO_DBG
            printf_w("F(%x)", temp[i]);     
        #endif
            
        if(temp[i]==rsm_flash_erasing_keyword)
        {
            is_free_section_finded =1;
            break;        
        }
        
        free_section++;
                
        if(((system_flash_id&0xffff)==0x1c42)||((system_flash_id&0xffff)==0x7f12))
        {
            //for Eon and Amic spi flash, no byte programming, write four byte once
            i+=4;               
            array_length-=4;    
        }
        else
        {        
            i++;                
            array_length--;
        }
    }
    
    #ifdef  RESUME_INFO_DBG
        printf_w("\n");
        FlashDelay(10000);
    #endif    
    
    if(isWriting==1)
    {
        if(is_free_section_finded!=1)
        {
            printf_w("FW memory full, Erasing\n");
            free_section = 0;            
            Resume_FlashEraseSector(rsm_flash_sec_type, rsm_flash_start_addr);
            //SPI_SEC_ERASE(rsm_flash_sec_type, rsm_flash_start_addr);
        }
        else
        {
            #ifdef  RESUME_INFO_DBG
                printf_w("FW free_section=%d\n",free_section);    
            #endif    
        }        
    }
    else
    {
        if(is_free_section_finded!=1)
        {
            #ifdef  RESUME_INFO_DBG
                printf_w("FR memory full, Reading\n");
            #endif    
            free_section = iLen-1;
        }
        else
        {
            if(free_section!=0)
            {
                free_section = free_section -1;
            }
            #ifdef  RESUME_INFO_DBG
                printf_w("FR free_section=%d\n",free_section);
            #endif    
        }               
    }
    
    return free_section;
}

//
// Function     :   Resume_Info_Write
// Description	:   re-direct writing address to free-section address
// Input        :   iStartAddr  -> writing address
//                  *pBuf       -> buffer for writing data
//                  iLen        -> writing length                 
// Output       :   >=0         -> sucess
//                  <0          -> fail	
// Note          :  call write-funcion to write index array, 
//                  and write buffer data to destination

int Resume_Info_Write(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen)
{
    #ifdef  RESUME_INFO_DBG
        printf_w("---Resume_Info_Write---\n");
    #endif    

    UINT32  index_addr =0, data_addr =0;
    UINT32  index_array_length = 0;
    BYTE    temp[1];
    
    int     iRes =0;    
    
    index_array_length = (rsm_flash_sec_size-(1<<rsm_free_section_idx_array_size)) / (1<<rsm_free_section_size);
    
    free_section_in_flash = Resume_section_finder(rsm_flash_start_addr, index_array_length, 1);
    
    temp[0]=free_section_in_flash;        
    
    if(((system_flash_id&0xffff)==0x1c42)||((system_flash_id&0xffff)==0x7f12))
    {
        //for Eon and Amic flash, no byte programming, write four byte once
        index_addr = rsm_flash_start_addr + free_section_in_flash*4;
    }
    else
    {
        index_addr = rsm_flash_start_addr + free_section_in_flash;
    }
    
    Resume_FlashWrite(index_addr,(BYTE *)temp,1);    //write free-section array
    
    #ifdef  RESUME_INFO_DBG      
        UINT32 i;
        BYTE    temp_2[index_array_length];
        Resume_FlashRead(rsm_flash_start_addr, temp_2,index_array_length);
        for(i=0;i<index_array_length;i++)
        {
            printf_w("W(%x)",temp_2[i]);    
        }
        printf_w("\n");
        FlashDelay(10000);
    #endif
    
    //iStartAddr + free-section array(occupy one section) + current section
    data_addr = iStartAddr + (1<<rsm_free_section_idx_array_size) + (free_section_in_flash<<rsm_free_section_size);
    
    #ifdef  RESUME_INFO_DBG
        printf_w("W write data: [%x, %d][%d]\n", data_addr,iLen,free_section_in_flash);
        FlashDelay(10000);
    #endif
    
    iRes = Resume_FlashWrite(data_addr, pBuf, iLen);
    
    return iRes;
    
}

//
// Function     :   Resume_Info_Read
// Description	:   re-direct reading address to current-section address
// Input        :   iStartAddr  -> reading address
//                  *pBuf       -> buffer for reading data
//                  iLen        -> reading length                 
// Output       :   >=0         -> sucess
//                  <0          -> fail	
// Note         :  


int Resume_Info_Read(UINT32 iStartAddr, BYTE *pBuf, UINT32 iLen)
{
    #ifdef  RESUME_INFO_DBG
        printf_w("---Resume_Info_Read---\n");
    #endif    

    UINT32  addr =0, read_addr = 0;
    UINT32  index_array_length = 0;
    int iRes =0;
    
    index_array_length = (rsm_flash_sec_size-(1<<rsm_free_section_idx_array_size)) / (1<<rsm_free_section_size);
    
    read_addr = Resume_section_finder(rsm_flash_start_addr, index_array_length, 0);
    
    //if(read_addr!=0)
        //read_addr = read_addr-1;
    
    //iStartAddr + free-section array(occupy one section) + current section
    addr = iStartAddr + (1<<rsm_free_section_idx_array_size) + (read_addr<<rsm_free_section_size);   
    
    #ifdef  RESUME_INFO_DBG
        printf_w("R read data: [%x, %d][%d]\n", addr,iLen,free_section_in_flash);
        FlashDelay(10000);
    #endif
    
    iRes = Resume_FlashRead(addr, pBuf, iLen);
    
    return iRes;
}

#endif

#ifdef FS_FILE_POWER_RESUME //qinhua,2006-6-13 05:03下午 
UINT8 IsTheSameDisc( void )
{  
	 printf("disc----is the same Disc ? ? ? ? \n");
   static UINT32 msf = 0 ;
   
   #if defined (SUPPORT_USB)||defined (SUPPORT_CARD_STORAGE) ||defined (SPHE8202_CARD_STORAGE)   
     if(media_type==MEDIA_CARD) 
     	return 0;
   #endif
   
   if(resume_clear==0)
 	    return 0;
  
		resume_fsnav_dir	=	ReadFromI2cA0_32(CDROM_INFO_BASE,(BYTE *)&resume_fsnav_dir, sizeof(resume_fsnav_dir));
    resumeTRK					=	ReadFromI2cA0_32(CDROM_INFO_BASE+sizeof(resume_fsnav_dir),(BYTE *)&resumeTRK, sizeof(resumeTRK));
 	  Resume_Track_msf	=	ReadFromI2cA0_32(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK),(BYTE *)&Resume_Track_msf, sizeof(Resume_Track_msf));
	  resumeMSF					=	ReadFromI2cA0_32(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK)+sizeof(Resume_Track_msf),(BYTE *)&resumeMSF, sizeof(resumeMSF));
   	Resume_func_btn		=	ReadFromI2cA0_32(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK)+sizeof(Resume_Track_msf)+sizeof(resumeMSF),&Resume_func_btn, sizeof(Resume_func_btn));
		
		msf = iso9660_file [resumeTRK ] . loc ;
		#if SAVE_CDROM_DEBUG
		printf("---READ----resume_fsnav_dir=%d---------\n\n",resume_fsnav_dir);
		printf("---READ----resumeTRK=%d---------\n\n",resumeTRK);
		printf("---READ----Resume_Track_msf=%d---------\n\n",Resume_Track_msf);
		printf("---READ----resumeMSF=%d---------\n\n",resumeMSF);
		printf("---READ----Resume_func_btn=%d---------\n\n",Resume_func_btn);
		printf("---READ-----msf=%d---------\n\n",msf);
		#endif
		
		if ( msf == Resume_Track_msf )
			return 1 ;
	  else 
		  return 0 ;
 }

void ClrSameCdromFlag (void)
{	
	printf("------clr cdrom save info-----\n\n");
   
   	resume_fsnav_dir=0;
		resumeTRK=0;
		Resume_Track_msf=0;
		resumeMSF=0;
		Resume_func_btn=0;
		WriteToI2cA0(CDROM_INFO_BASE,(BYTE *)&resume_fsnav_dir, sizeof(resume_fsnav_dir));
	  //resume_fsnav_dir
		WriteToI2cA0(CDROM_INFO_BASE+sizeof(resume_fsnav_dir),(BYTE *)&resumeTRK, sizeof(resumeTRK));
	 	//resumeTRK
	 	WriteToI2cA0(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK),(BYTE *)&Resume_Track_msf, sizeof(Resume_Track_msf));
	 	//Resume_Track_msf
	 	WriteToI2cA0(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK)+sizeof(Resume_Track_msf),(BYTE *)&resumeMSF, sizeof(resumeMSF));
  	//resumeMSF
  	WriteToI2cA0(CDROM_INFO_BASE+sizeof(resume_fsnav_dir)+sizeof(resumeTRK)+sizeof(Resume_Track_msf)+sizeof(resumeMSF), &Resume_func_btn, sizeof(Resume_func_btn));
		//Resume_func_btn  
}
#endif //#ifdef FS_FILE_POWER_RESUME







