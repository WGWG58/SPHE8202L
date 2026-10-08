//
// FILE 
// sbar.inc
// DESCRIPTION
// system bus access priority select
//
// *included in reset.c*
//

//
// 0 vpp
// 1 osd
// 2 agdc_sup
// 3 aud_pcm
// 4 ref
// 5 agdc_vld
// 6 mc
// 7 servo
// 8 auddsp
// 9 risc
// a agdc_host
// b graph
// c agdc_iop
// d ... (not used)
// e ... (not used)
// f ... (not used)
//

#if defined(IC_8202D)|| defined(IC_8202L)||defined(IC_8203A)
const	UINT8	sbar_prr[14] = 
//const	UINT8	sbar_prr[13] = 
{
	0x4,	// 0 vpp        
	0x4,	// 1 osd        
	0x4,	// 2 agdc_sup 
	0x4,	// 3 aud_pcm       
	0xF,	// 4 ref          
	0x2,	// 5 agdc_vld      
	0x3,	// 6 mc            // slower
	0x1,	// 7 servo   
	0x1,	// 8 auddsp        
	0x4,	// 9 risc          
	0x8,	// a agdc_host     
	0xF,	// b graph         
	0xF,	// c agdc_iop   
	0xF,    // d demux
};
#else

const	UINT8	sbar_prr[13] = 
{
	0x4,	// 0 vpp        
	0x4,	// 1 osd        
	0x0,	// 2 agdc_sup   fix sup-scaling-problem
	0x4,	// 3 aud_pcm       
	0xF,	// 4 ref          
	0x4,	// 5 agdc_vld      
	0x4,	// 6 mc            
	0x2,	// 7 servo      wells: fix servo buffer control problem
#ifdef  SPHE8202
	0x2,	// 8 auddsp        
#else
	0x4,	// 8 auddsp        
#endif
	0xA,	// 9 risc          
	0xB,	// a agdc_host     
	0xC,	// b graph         
	0xD,	// c agdc_iop      
};
#endif


