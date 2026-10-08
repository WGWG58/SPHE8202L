#include "rommap_rom.h"
/**************************************************************************
 *  Function Name: rom_checksum                                           *
 *  Purposes:                                                             *
 *    At present, the funtion don't used                                  *
 *  Descriptions:                                                         *
 *    calculate rom check-sum (of first 512kbyte)                         *
 *  Arguments:  None                                                      *
 *  Returns: None                                                         *
 *  See also: None                                                        *
 **************************************************************************/
UINT32 rom_checksum_per_kbyte(int st,int end)
{
    int i;
    UINT32 chksum=0;
    UINT32 *p1;
    UINT32 *codesize = (UINT32 *)(ROM_BASE_UNCACHED+ROM_SIZE_ADDR);
    UINT32 *q= (UINT32 *)(ROM_BASE_UNCACHED+ORG_BOOT_ROMB_CHK_SUM);

    for (i=st;i<end; i++)
    {
        if(i*1024>*codesize) break;
        p1=(UINT32 *)( ROM_BASE_UNCACHED+(i*1024) );
        //printf("-%x: %x-\n",p1,*p1 );
        chksum += *p1;
        // delay_1ms(1000);
    }

    //printf("\n\n == chksum:%x q:%x==\n\n\\n",chksum,*q);

    if(*q==chksum) return 1;//goto boot rom
    else return 0;
}

UINT32 rom_checksum_per_kbyte1(int st,int end)
{
    int i;
    UINT32 chksum=0;    
    UINT32 chksum1=0;    
    UINT32 *p1;
    UINT32 *codesize = (UINT32 *)(ROM_BASE_UNCACHED+ROM_SIZE_ADDR);
    UINT32 *q= (UINT32 *)(ROM_BASE_UNCACHED+ORG_BOOT_ROMB_CHK_SUM);
    UINT8 *p2;    
    
    //printf("code size=%d\n",*codesize);
    for (i=st;i<end; i++)
    {
        if(i*1024>*codesize) break;
        p1=(UINT32 *)( ROM_BASE_UNCACHED+(i*1024) );        
        chksum += *p1;
        
        p2=(UINT8 *)( ROM_BASE_UNCACHED+(i*1024) );        
        chksum1 += (*(p2+3) + (*(p2+2)<<8)+(*(p2+1)<<16)+(*(p2)<<24));
        
        //printf("-i:%d %08x: %08x chksum:%08x chksum1:%08x-\n",i,p1,*p1,chksum,chksum1 );
        // delay_1ms(1000);
    }
    
    //printf("\n\n == chksum:%x *q:%x q:%x  %x ==\n\n\\n",chksum,*q,q,(*q) == chksum);
    
    
    if(*q==chksum) return 1;//goto boot rom
    else return 0;
    
    //return chksum;
    
}


