#include "user_init.h"
#include "rsm_upd.h"

/// ******  New resume info write / read functions  ******

//#define RSM_UPDATE_DBG
//#define RESUME_INFO_DBG

#include "flash.h"

#define UNUSED_VALUE 0xFF

#define FIRST_LEN 2

static int find_start_addr(int low, int high)
{
  int hi, lo; //, mid;
  //BYTE tmp[3];
  BYTE tmp1;
  
  lo = low;
  hi = high;
  while (lo<=hi)
  {
  	Resume_FlashRead(hi, &tmp1, 1);
  	if (tmp1!=rsm_flash_erasing_keyword)
  	{
  	  break;
  	}
  	hi--;
  }
  
  if (hi<lo)
    return lo;
  else
    return (hi+1);    
}


//swpong 2006 0404
// Function     :   Resume_Info_Write_Update
// Description	:   re-direct writing address to free-section address
// Input        :   iStartAddr  -> the Start Address of pBuf1 where pBuf2 starts
//                  *pBuf1       -> buffer of full record, used in the first time and after sector full.
//                  iBuf1Len     -> length of pBuf1
//                  *pBuf2       -> buffer for updated data
//                  iBuf2Len     -> length of pBuf2
// Output       :   >=0         -> sucess
//                  <0          -> fail	
// Note          :  call write-funcion to write index array, 
//                  and write buffer data to destination

enum {H_MODFF=0, H_LEN, H_OFFSET_HI, H_OFFSET_LO, HEAD_SIZE};
#define W_ARRAY_SIZE 8
#define W_ALIGN 4
#define MODFF_IDX    0

int Resume_Info_Write_Update(UINT32 iStartAddr, BYTE *pBuf1, UINT32 iBuf1Len, BYTE *pBuf2, UINT32 iBuf2Len)
{
    #ifdef  RESUME_INFO_DBG
        printf_w("---Resume_Info_Write_Update---\n");
    #endif    


    int     iRes =0;    
    BYTE FirstMark[FIRST_LEN];
    UINT32 i, j, size;
    BYTE w_array[W_ARRAY_SIZE];
    BYTE w_head[HEAD_SIZE];
    UINT32 ExtraInfoSize, total_len, current_start;
    BYTE *p;
    
    #ifdef  RESUME_INFO_DBG
    printf_w("Resume info write Update\n");
    FlashDelay(10000);
    #endif

    //swpong 2006 0502 Resume_FlashRead(SPI_START, FirstMark, FIRST_LEN);
    Resume_FlashRead(rsm_flash_start_addr, FirstMark, FIRST_LEN);
    if (FirstMark[0] == rsm_flash_erasing_keyword) //the first time written, write full structure.
    {
        FirstMark[0] = (iBuf1Len+FIRST_LEN)>>8;
        FirstMark[1] = (iBuf1Len+FIRST_LEN)&0xff;
        
    	Resume_FlashWrite(rsm_flash_start_addr, FirstMark, FIRST_LEN);    	
    	Resume_FlashWrite(rsm_flash_start_addr+FIRST_LEN,pBuf1,iBuf1Len);

        #ifdef  RESUME_INFO_DBG
    	printf_w("Write initial %x, %x, %d\n", FirstMark[0], FirstMark[1], iBuf1Len);
    	FlashDelay(10000);
    	#endif
    }
    else //for difference history
    {
        Resume_FlashRead(rsm_flash_start_addr, FirstMark, FIRST_LEN);

        current_start = find_start_addr(rsm_flash_start_addr + ((FirstMark[0]<<8)|(FirstMark[1])), 
                                               rsm_flash_start_addr + rsm_flash_sec_size-1);
        
        if (!current_start)
        {
       	   iRes = -1;
       	   printf_w ("**SPI find start addr error***\n");
        }
        else
        {
        	//
			if(iBuf2Len % 7 == 0)                 
                ExtraInfoSize = HEAD_SIZE + (iBuf2Len)/(W_ARRAY_SIZE-1);
            else
				ExtraInfoSize = HEAD_SIZE + (iBuf2Len)/(W_ARRAY_SIZE-1) + 1;
			
       	   total_len = iBuf2Len + ExtraInfoSize;

#ifdef RSM_UPDATE_DBG      	       	  	  
       	   printf_w("Write at 0x%x, len = %d, extra = %d\n", current_start, total_len, ExtraInfoSize);
       	   FlashDelay(10000);
#endif       	   

       	  
       	   if ((current_start + total_len) >= (rsm_flash_start_addr+rsm_flash_sec_size))
       	   {
       	     printf_w("Sector full, erasing ... \n");
       	     FlashDelay(10000);

       	  	 //sector full, erase and update all.
       	  	 Resume_FlashEraseSector(rsm_flash_sec_type, rsm_flash_start_addr);

             FirstMark[0] = (iBuf1Len+FIRST_LEN)>>8;
             FirstMark[1] = (iBuf1Len+FIRST_LEN)&0xff;

    	     Resume_FlashWrite(rsm_flash_start_addr, FirstMark, FIRST_LEN);
    	     iRes = Resume_FlashWrite(rsm_flash_start_addr+FIRST_LEN,pBuf1,iBuf1Len);
    	     
   			 return iRes;	
       	   }
       	   else  //Update history
       	   {
       	  	 //swpong 2006 0505 w_head[H_MODFF] = 0;
       	  	 w_head[H_MODFF] = (rsm_flash_erasing_keyword&0x80)^0x80;
       	  	   
       	  	 if (total_len == rsm_flash_erasing_keyword) //swpong 2006 0505, 0xff)
       	  	 {
       	  		w_head[H_MODFF] |= (1<<H_LEN);
       	  		w_head[H_LEN] = 0;
       	     }
       	     else
       	  	    w_head[H_LEN] = total_len&0xff;
       	  	  
       	  	 if ((iStartAddr&0xff) == rsm_flash_erasing_keyword) //swpong 2006 0505, 0xff)
       	  	 {
       	  		w_head[H_MODFF] |= (1<<H_OFFSET_LO);
       	  		w_head[H_OFFSET_LO] = 0;
       	     }
       	     else
       	  	    w_head[H_OFFSET_LO] = iStartAddr&0xff;
       	  	  
       	  	 if ((iStartAddr>>8) == rsm_flash_erasing_keyword) //swpong 2006 0505, 0xff)
       	  	 {
       	  		w_head[H_MODFF] |= (1<<H_OFFSET_HI);
       	  		w_head[H_OFFSET_HI] = 0;
       	     }
       	     else
       	  	    w_head[H_OFFSET_HI] = (iStartAddr>>8)&0xff;
       	  	  
#ifdef RSM_UPDATE_DBG      	       	  	  
       	  	//printf_w("Write cur = %d HEAD(%x,%x,%x,%x)\n",current_start, w_head[H_MODFF], w_head[H_OFFSET_HI], w_head[H_OFFSET_LO], w_head[H_LEN]);       	  	
       	  	//FlashDelay(10000);
#endif       	  	
       	  	
       	  	Resume_FlashWrite(current_start, w_head, HEAD_SIZE);
       	  	current_start += HEAD_SIZE;

#ifdef RSM_UPDATE_DBG      	
       	  printf_w("Write offset = 0x%x, len = %d\n", w_head[H_OFFSET_LO]|((w_head[H_OFFSET_HI])<<8), w_head[H_LEN]);
       	  FlashDelay(10000);
#endif       	  
       	  	
       	  	size = iBuf2Len;
       	  	j = 0;
       	  	p = pBuf2;
       	  	while (size)
       	  	{
       	  		if (j==0)
       	  		  //swpong2006 0505 w_array[MODFF_IDX] = 0;
       	  		  w_array[MODFF_IDX] = (rsm_flash_erasing_keyword&0x80)^0x80;
       	  		if (*p == 0xff)
       	  		{
       	  		  w_array[MODFF_IDX] |= (1<<j);
       	  		  w_array[j+1] = 0;
       	  		}
       	  		else
       	  		  w_array[j+1] = *p;
       	  		  
       	  		//printf_w("%x ", *p);
       	  		j++;
       	  		j%=(W_ARRAY_SIZE - 1);
       	  		if (j==0)
       	  		{
#ifdef RSM_UPDATE_DBG      	       	  			
       	  			printf_w("WriteTo:0x%x, left : %d\n", current_start, size);
#endif       	  			
       	  			Resume_FlashWrite(current_start, w_array, W_ARRAY_SIZE);
       	  			current_start += W_ARRAY_SIZE;
       	  		}
       	  		  
       	  		size--;
       	  		p++;
       	    }
       	    //printf_w("\n");
       	  	if (j)
       	  	{
                  for (i=j+1;i<W_ARRAY_SIZE;i++)
                    w_array[i] = 0x00;
                  
                  
                  if (j<(W_ALIGN-1))
                  {
                    Resume_FlashWrite(current_start, w_array, W_ALIGN);
                    current_start += W_ALIGN;
                  }
                  else
                  {
                    Resume_FlashWrite(current_start, w_array, W_ARRAY_SIZE);
                    current_start += W_ARRAY_SIZE;                  	
                  }
       	  		  //current_start += (j+1);
       	    }

#ifdef RSM_UPDATE_DBG      	       	    
       	    printf_w ("Write next start = 0x%x\n", current_start);
       	    FlashDelay(10000);
#endif       	    
       	    
       	  }
       }
    }
    return iRes;    
}

//
// Function     :   Resume_Info_Read_Update
// Description	:   re-direct reading address to current-section address
// Input        :   
//                  *pBuf1      -> buffer for recording data
//                  iLen        -> buffer length                 
// Output       :   >=0         -> sucess
//                  <0          -> fail	
// Note         :  

int Resume_Info_Read_Update(BYTE *pBuf1, UINT32 iLen)
{
    #ifdef  RESUME_INFO_DBG
        printf_w("---Resume_Info_Read---\n");
    #endif    

    int current_addr = 0, end_addr, len;
    unsigned int cnt = 0, get_cnt;
    UINT32 offset, j;
    BYTE *p;
    BYTE FirstMark[FIRST_LEN];
    BYTE w_array[W_ARRAY_SIZE];
    BYTE w_head[HEAD_SIZE];

#ifdef RSM_UPDATE_DBG      	       	      
    printf_w("Resume info read Update\n");
    FlashDelay(10000);
#endif    

    //1 for skip first mark
    Resume_FlashRead(rsm_flash_start_addr, FirstMark, FIRST_LEN);
    Resume_FlashRead(rsm_flash_start_addr+FIRST_LEN, pBuf1, iLen);
    current_addr =  rsm_flash_start_addr + ((FirstMark[0]<<8)|(FirstMark[1]));
  
    if (FirstMark[0] == rsm_flash_erasing_keyword)
    { 
#ifdef RSM_UPDATE_DBG      	       	    	
  	printf_w("FirstMark[0] == rsm_flash_erasing\n");
  	FlashDelay(10000);
#endif      	
      end_addr = current_addr; //swpong 2006 0503
    }
    else //swpong 2006 0503
      end_addr = find_start_addr(current_addr, rsm_flash_start_addr + rsm_flash_sec_size-1);

#ifdef RSM_UPDATE_DBG      	       	  
    printf_w("Resume Update get curr = 0x%x, end = 0x%x\n", current_addr, end_addr);
    FlashDelay(10000);
#endif    


    //p = pBuf1;
    while (current_addr < end_addr)
    { 
      Resume_FlashRead(current_addr, w_head, HEAD_SIZE);

#ifdef RSM_UPDATE_DBG      	
      //printf_w("Read cur = %x HEAD(%x,%x,%x,%x)\n",current_addr, w_head[H_MODFF], w_head[H_OFFSET_HI], w_head[H_OFFSET_LO], w_head[H_LEN]);
      //FlashDelay(10000);
#endif      

      current_addr += HEAD_SIZE;
      
      if (w_head[H_MODFF]&(1<<H_LEN))
        w_head[H_LEN] = rsm_flash_erasing_keyword; //swpong 2006 0505, 0xff;
      if (w_head[H_MODFF]&(1<<H_OFFSET_LO))
        w_head[H_OFFSET_LO] = rsm_flash_erasing_keyword; //swpong 2006 0505, 0xff;
      if (w_head[H_MODFF]&(1<<H_OFFSET_HI))
        w_head[H_OFFSET_HI] = rsm_flash_erasing_keyword; //swpong 2006 0505, 0xff;
      offset = (w_head[H_OFFSET_HI]<<8) | w_head[H_OFFSET_LO];
      len = w_head[H_LEN] - HEAD_SIZE;
      
      //printf_w("Read offset : %d, len : %d\n", offset, len);
      p = pBuf1;
      p+=offset;
      
      while (len>0)
      {
        if (len >= W_ARRAY_SIZE)
        {
          cnt = W_ARRAY_SIZE;
          get_cnt = W_ARRAY_SIZE;
        }
        else if (len > (W_ARRAY_SIZE - (W_ALIGN+1)))
        {
          cnt = len;
          get_cnt = W_ARRAY_SIZE;
        }
        else
        {
          cnt = len;
          get_cnt = W_ALIGN;
        }
      	
      	Resume_FlashRead(current_addr, w_array, get_cnt);
      	current_addr += get_cnt;
      	
   		for (j=1; j<cnt; j++)
   		{
   			if (w_array[MODFF_IDX]&(1<<(j-1)))
   			  w_array[j] = rsm_flash_erasing_keyword; //swpong 2006 0505,0xff;
   			*p++ = w_array[j];
   			//printf_w("%x ",w_array[j]);
   	    }
   	    //printf_w("\n");
      	len -= cnt;      			  
      }  //while (len)
      //printf_w("\n");
    } //while (current_addr < end_addr)

    return 1;
}

