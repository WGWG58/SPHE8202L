/*
** FILE
** util.c
**
** DESCRIPTION
** provide some general utilities.
**
*/
#include "global.h"
#include "fastmath.h"
#include "util.h"
#include "sinf.h"

#ifdef	USE_DIV
#include "stdlib.h"
#endif
#ifdef MIX_CDMP3_DISC_DISPLAY_REAL_CD_TRK //linrc add 2004-10-29 11:33
#include "cdxa.h"
#endif
//#define     UTIL_DBG    1

/*
** FUNCTION
** bin2bcd(BYTE x)
**
** DESCRIPTION
** transform a binary-represented number into packed BCD.
**
** 0x0c(12)	-> 0x12
** 0x20(32)	-> 0x32
**
** *NOTE*
** we used fast dividing-by-10 function to generate the result.
*/
int	bin2bcd(BYTE x)	
{
#ifdef	USE_DIV
  div_t	res;
  res = div(x,10);
  return (res.quot<<4) | (res.rem);
#else
#if 1
  int	Q = DIV10(x);
  int	R = x-10*Q;
  return  (Q<<4) | R;
#else
  return ((x/10)<<4) | (x%10);
#endif
#endif
}


/*
** FUNCTION
** bcd2bin(BYTE x)
**
** DESCRIPTION
** transform a bcd-number into binary-represented
*/
int	bcd2bin(BYTE x)
{
  /*
  ** for mips, a optimized version might be obtained using:
  **
  ** use CE (slower)
  **	li 	%1, 10
  **	shr	%2, %0, 4
  ** 	multu	%1, %2 
  **	andi	%1, %0, 0x000f
  **	mflo	%2	
  ** 	addu	%1, %2
  **
  ** or
  **	shr	%1, %0, 4	// >>4
  **	addu	%2, %1, %1	// (2) = *2
  ** 	shl	%1, %2, 2	// (1) = (2)*4
  **	addu	%1, %2		// (1) = (1)+(2)
  **	andi	%2, %0, 0x000f	// (2) = (0)&0x000f
  **	addu	%1, %2		// (1) = (1)+(2)
  ** 
  */
  return (x>>4) * 10 + (x&0x0f); 
}


/*
** FUNCTION
** l2msf(UINT32 l)
**
** DESCRIPTION
** map a linear address of CDROM into MSF addressing
**
** *NOTE*
** msf is packed 4-byte structure with format
** [CI:MM:SS:FF], where MM/SS/FF is in binary.
*/
UINT32	l2msf(UINT32 l)
{
  UINT32 ss, ff;
  UINT32 l_75, l_4500;

  l      += 150;
  l_75    = l/75;
  l_4500  = l_75/60;

  ff = l - 75*l_75;
  ss = l_75 - 60*l_4500;

  return (l_4500<<16) | (ss<<8) | (ff);
}


/*
** FUNCTION
** msf2l(UINT32 msf)
**
** DESCRIPTION
** map a MSF addressing into linear addressing
**
** *NOTE*
** (UINT32)msf is packed 4-byte structure with format
** [00:MM:SS:FF], where MM/SS/FF is in binary.
*/
UINT32	msf2l(UINT32 msf)
{
    UINT16  iMM;

    //Jeff replace, 20030814
    //return MSF2l(msf_mm(msf), msf_ss(msf), msf_ff(msf));
    //JSLin 20040915	//added CDDVD
    if ((cd_type_loaded==CDROM) || (cd_type_loaded==CDDVD)) {
        iMM = (((msf)>>16) & 0xffff);
    } else {
        iMM = msf_mm(msf);
    }

    return MSF2l(iMM, msf_ss(msf), msf_ff(msf));
}


/*
** FUNCTION
** addmsf_ss(UINT32 msf, int inc_s)
**
** DESCRIPTION
** adjust MSF address by (inc_s) seconds
*/
#define	MSF_SECONDS	60
#define	MSF_FRAMES	75

#define	FIRST_FRAME	0x000200

UINT32	addmsf_ss(UINT32 msf, int inc_s)
{
  UINT32 ret_msf; 
  int 	 mm = msf_mm(msf);
  int 	 ss = msf_ss(msf) + inc_s;
  int	 ff = msf_ff(msf);

#ifdef DVD_SERVO
  if ((cd_type_loaded==CDROM) && is_svo_dvd()) { //for DVD disc containing files, Jeff 20040125
#else
  if (cd_type_loaded==CDROM) {
#endif
      mm = (((msf)>>16) & 0xffff);
  }

  while (ss<0) {
    ss += MSF_SECONDS; mm--;
  }
  while (ss>=MSF_SECONDS) {
    ss -= MSF_SECONDS; mm++;
  }
  ret_msf = MSF(mm,ss,ff);
  if (mm<0)
    ret_msf = 0x000200;
  return ret_msf;
}


/*
** FUNCTION
** addmsf(UINT32 msf, int inc_f)
**
** DESCRIPTION
** adjust MSF address by #inc_f frames
*/
UINT32	addmsf(UINT32 msf, int inc_f)
{
  UINT32 ret_msf; 
  int    mm = msf_mm(msf);
  int    ss = msf_ss(msf);
  int    ff = msf_ff(msf) + inc_f;

#ifdef DVD_SERVO
  if ((cd_type_loaded==CDROM) && is_svo_dvd()) { //for DVD disc containing files, Jeff 20040125
#else
  if (cd_type_loaded==CDROM) {
#endif
      mm = (((msf)>>16) & 0xffff);
  }

  while (ff<0) {
    ff += 75; ss--;
  }
  while (ff>=75) {
    ff -= 75; ss++;
  }
  while (ss<0) {
    ss += 60; mm--;
  }
  while (ss>=60) {
    ss -= 60; mm++;
  }

  ret_msf = MSF(mm,ss,ff);
  if (mm<0) 
    ret_msf = 0x000200;
  if (ret_msf<0x000200)
    ret_msf = 0x000200;

  return ret_msf;
}

BYTE bin2asc(BYTE pp)  /* Converte binary code(0~0xf) to ASCII */
{
 if(pp<10) pp+=0x30;
 else pp=pp+0x41-10;
 return pp;
}
BYTE adjust_trk_num(BYTE trk)   
{
//terry,mark it,2002/6/27 05:01PM
/* if(cd_type_loaded==CDDA)
 {
 	return trk;
 }else*/
//wanghaoying delete to higui\backup.c 2005-1-18 20:11
    
 {     
    return (trk + cd_trk_lo_now -1);    
 }
}

BYTE show_trk_num(BYTE trk)   
{
//terry,2002/6/27 05:01PM
/* if(cd_type_loaded==CDDA)
 {
 	return trk;
 }else*/
 #ifdef MIX_CDMP3_DISC_DISPLAY_REAL_CD_TRK  //linrc add2004-10-29 11:20
 /*when play the cd+mp3 disc(ABEX TEST CD 786),it display the real CD TRK*/
 if((cd_type_loaded == CDDA)&&((pFsJpeg->cdrom.track_info[1]&0x40000000) == 0x40000000))
 {
    return (trk - cd_trk_lo_now +1)+1;
 } 
 else
 #endif
 {     
    return (trk - cd_trk_lo_now +1);    
 }
}
UINT32 get_next_trk_msf(UINT8 trk)
{
	UINT32 msf;
	
	if(trk<cd_trk_hi)
		msf = gettrkmsf(trk+1);
	else
		msf = gettrkmsf_leadout();
		
	return msf & 0x00ffffff ;
}

#ifndef DVDRELEASE
void print_block(UINT8 *a, int n)
{
	int i;
	
	for (i = 0; i < n; i++) {
		printf("%02x%s", *(a+i), (i % 16 == 15) ? "\n" : " ");
		//if (i == 16*10) getch();
	}
	printf("\n");
	//getch();
}
#endif

