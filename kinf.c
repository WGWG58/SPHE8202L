
#include "config.h"
#include "regmap.h"
#include "global.h"
#include "macro.h"
#include "viddec.h"
#include "kinf.h"


//
// kcall_seq_end
//
// return -1 to
//
int
kcall_seq_end(void)
{
	if (GetIntrMask() & INTR_SEQ_END)
		return -1;
	return 0; 
}

int Kcall_seq_info(UINT32 uReqInfo)
{
    int iResult=0;
    switch (uReqInfo)
    {
        case KINFO_FRAME_RATE:
        	   iResult = seq_info.frame_rate_code;
        	   break;
        	   
        case KINFO_ASPECT_RATIO:
        	   iResult = seq_info.aspect_ratio_information;
        	   break;                 
        case KINFO_HORIZONTAL_SIZE:
        	   iResult = seq_info.horizontal_size_value;
        	   break;
        case KINFO_VERTICAL_SIZE:
        	   iResult = seq_info.vertical_size_value;
        	   break;
        default:
        	   iResult = -1;
        	   break;
    }
    return iResult;   
}


