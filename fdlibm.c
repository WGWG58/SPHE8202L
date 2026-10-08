# 1 "fdlibm.h"

#ifndef __IEEE_BIG_ENDIAN
#ifndef __IEEE_LITTLE_ENDIAN

#if defined(__arm__) || defined(__thumb__)
/* ARM always has big-endian words.  Within those words the byte ordering
   appears to be big or little endian.  Newlib doesn't seem to care about
   the byte ordering within words.  */
#define __IEEE_BIG_ENDIAN
#endif

#ifdef __hppa__
#define __IEEE_BIG_ENDIAN
#endif

#ifdef __sparc__
#define __IEEE_BIG_ENDIAN
#endif

//#if defined(__m68k__) || defined(__mc68000__)
//#define __IEEE_BIG_ENDIAN
//#endif

#if defined (__H8300__) || defined (__H8300H__) || defined (__H8300S__)
#define __IEEE_BIG_ENDIAN
#define __SMALL_BITFIELDS
#define _DOUBLE_IS_32BITS
#endif

#ifdef __H8500__
#define __IEEE_BIG_ENDIAN
#define __SMALL_BITFIELDS
#define _DOUBLE_IS_32BITS
#endif

#ifdef __sh__
#ifdef __LITTLE_ENDIAN__
#define __IEEE_LITTLE_ENDIAN
#else
#define __IEEE_BIG_ENDIAN
#endif
#if defined(__SH3E__) || defined(__SH4_SINGLE_ONLY__)
#define _DOUBLE_IS_32BITS
#endif
#endif

#ifdef _AM29K
#define __IEEE_BIG_ENDIAN
#endif

#ifdef __i386__
#define __IEEE_LITTLE_ENDIAN
#endif

#ifdef __i960__
#define __IEEE_LITTLE_ENDIAN
#endif

#ifdef __M32R__
#define __IEEE_BIG_ENDIAN
#endif


#ifdef __MIPSEL__
#define __IEEE_LITTLE_ENDIAN
#endif
#ifdef __MIPSEB__
#define __IEEE_BIG_ENDIAN
#endif

/* necv70 was __IEEE_LITTLE_ENDIAN. */

#ifdef __W65__
#define __IEEE_LITTLE_ENDIAN
#define __SMALL_BITFIELDS
#define _DOUBLE_IS_32BITS
#endif

#if defined(__Z8001__) || defined(__Z8002__)
#define __IEEE_BIG_ENDIAN
#endif

#ifdef __m88k__
#define __IEEE_BIG_ENDIAN
#endif

#ifdef __mn10300__
#define __IEEE_LITTLE_ENDIAN
#endif

#ifdef __mn10200__
#define __IEEE_LITTLE_ENDIAN
#define __SMALL_BITFIELDS
#define _DOUBLE_IS_32BITS
#endif

#ifdef __v800
#define __IEEE_LITTLE_ENDIAN
#endif

#ifdef __v850
#define __IEEE_LITTLE_ENDIAN
#endif

#ifdef __D10V__
#define __IEEE_BIG_ENDIAN
#define _DOUBLE_IS_32BITS
#define __SMALL_BITFIELDS
#endif

#ifdef __PPC__
#if (defined(_BIG_ENDIAN) && _BIG_ENDIAN) || (defined(_AIX) && _AIX)
#define __IEEE_BIG_ENDIAN
#else
#if (defined(_LITTLE_ENDIAN) && _LITTLE_ENDIAN) || (defined(__sun__) && __sun__) || (defined(_WIN32) && _WIN32)
#define __IEEE_LITTLE_ENDIAN
#endif
#endif
#endif

#ifdef __arc__
#ifdef __big_endian__
#define __IEEE_BIG_ENDIAN
#else
#define __IEEE_LITTLE_ENDIAN
#endif
#endif

#ifndef __IEEE_BIG_ENDIAN
#ifndef __IEEE_LITTLE_ENDIAN
#error Endianess not declared!!
#endif /* not __IEEE_LITTLE_ENDIAN */
#endif /* not __IEEE_BIG_ENDIAN */

#endif /* not __IEEE_LITTLE_ENDIAN */
#endif /* not __IEEE_BIG_ENDIAN */


 
# 1 "/home/potatooo/fcc/lib/gcc-lib/mips-ecoff/2.8.1/include/math.h" 1 3
 







# 1 "/home/potatooo/fcc/mips-ecoff/include/sys/reent.h" 1 3
 

 









# 1 "/home/potatooo/fcc/lib/gcc-lib/mips-ecoff/2.8.1/include/_ansi.h" 1 3
 

 











# 1 "/home/potatooo/fcc/mips-ecoff/include/sys/config.h" 1 3



 
 
# 14 "/home/potatooo/fcc/mips-ecoff/include/sys/config.h" 3


# 25 "/home/potatooo/fcc/mips-ecoff/include/sys/config.h" 3


 








# 44 "/home/potatooo/fcc/mips-ecoff/include/sys/config.h" 3







































 








typedef int __int32_t;
typedef unsigned int __uint32_t;







# 15 "/home/potatooo/fcc/lib/gcc-lib/mips-ecoff/2.8.1/include/_ansi.h" 2 3


 
 

























# 61 "/home/potatooo/fcc/lib/gcc-lib/mips-ecoff/2.8.1/include/_ansi.h" 3


 








# 13 "/home/potatooo/fcc/mips-ecoff/include/sys/reent.h" 2 3


struct _glue 
{
  struct _glue *_next;
  int _niobs;
  struct __sFILE *_iobs;
};

struct _Bigint 
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  unsigned long _x[1];
};

 





struct _atexit {
	struct	_atexit *_next;			 
	int	_ind;				 
	void	(*_fns[32 ])();	 
};

 






struct __sbuf {
	unsigned char *_base;
	int	_size;
};

 




typedef long _fpos_t;		 
				 

 
























struct __sFILE {
  unsigned char *_p;	 
  int	_r;		 
  int	_w;		 
  short	_flags;		 
  short	_file;		 
  struct __sbuf _bf;	 
  int	_lbfsize;	 

   
  void * 	_cookie;	 

  int	 (*_read)   (void *  _cookie, char *_buf, int _n)  ;
  int	 (*_write)   (void *  _cookie, const char *_buf, int _n)  ;
  _fpos_t  (*_seek)   (void *  _cookie, _fpos_t _offset, int _whence)  ;
  int	 (*_close)   (void *  _cookie)  ;

   
  struct __sbuf _ub;	 
  unsigned char *_up;	 
  int	_ur;		 

   
  unsigned char _ubuf[3];	 
  unsigned char _nbuf[1];	 

   
  struct __sbuf _lb;	 

   
  int	_blksize;	 
  int	_offset;	 

  struct _reent *_data;
};

 







struct _reent
{
   
  int _errno;

   


  struct __sFILE *_stdin, *_stdout, *_stderr;

  int  _inc;			 
  char _emergency[25];
 
  int _current_category;	 
  const  char *_current_locale;

  int __sdidinit;		 

  void  (*__cleanup)   (struct _reent *)  ;

   
  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;

   
  int _cvtlen;			 
  char *_cvtbuf;

   



  unsigned char * _nextf[30 ];
  unsigned int _nmalloc[30 ];

   
  struct _atexit *_atexit;	 
  struct _atexit _atexit0;	 

   
  void (**(_sig_func))();

   


  struct _glue __sglue;			 
  struct __sFILE __sf[3];		 
};




 








extern struct _reent *_impure_ptr  ;

void _reclaim_reent  (struct _reent *)  ;

 









# 9 "/home/potatooo/fcc/lib/gcc-lib/mips-ecoff/2.8.1/include/math.h" 2 3

# 1 "/home/potatooo/fcc/mips-ecoff/include/machine/ieeefp.h" 1 3


































# 44 "/home/potatooo/fcc/mips-ecoff/include/machine/ieeefp.h" 3


























 







































# 118 "/home/potatooo/fcc/mips-ecoff/include/machine/ieeefp.h" 3



















# 10 "/home/potatooo/fcc/lib/gcc-lib/mips-ecoff/2.8.1/include/math.h" 2 3





 


union __dmath
{
  __uint32_t i[2];
  double d;
};

extern const union __dmath __infinity;







 


extern double atan  (double)  ;
extern double cos  (double)  ;
extern double sin  (double)  ;
extern double tan  (double)  ;
extern double tanh  (double)  ;
extern double frexp  (double, int *)  ;
extern double modf  (double, double *)  ;
extern double ceil  (double)  ;
extern double fabs  (double)  ;
extern double floor  (double)  ;


 



extern double acos  (double)  ;
extern double asin  (double)  ;
extern double atan2  (double, double)  ;
extern double cosh  (double)  ;
extern double sinh  (double)  ;
extern double exp  (double)  ;
extern double ldexp  (double, int)  ;
extern double log  (double)  ;
extern double log10  (double)  ;
extern double pow  (double, double)  ;
extern double sqrt  (double)  ;
extern double fmod  (double, double)  ;





 

extern double infinity  (void)  ;
extern double nan  (void)  ;
extern int isnan  (double)  ;
extern int isinf  (double)  ;
extern int finite  (double)  ;
extern double copysign  (double, double)  ;
extern int ilogb  (double)  ;

extern double asinh  (double)  ;
extern double cbrt  (double)  ;
extern double nextafter  (double, double)  ;
extern double rint  (double)  ;
extern double scalbn  (double, int)  ;


extern double log1p  (double)  ;
extern double expm1  (double)  ;



extern double acosh  (double)  ;
extern double atanh  (double)  ;
extern double remainder  (double, double)  ;
extern double gamma  (double)  ;
extern double gamma_r  (double, int *)  ;
extern double lgamma  (double)  ;
extern double lgamma_r  (double, int *)  ;
extern double erf  (double)  ;
extern double erfc  (double)  ;
extern double y0  (double)  ;
extern double y1  (double)  ;
extern double yn  (int, double)  ;
extern double j0  (double)  ;
extern double j1  (double)  ;
extern double jn  (int, double)  ;



extern double hypot  (double, double)  ;


extern double cabs();
extern double drem  (double, double)  ;



 

extern float atanf  (float)  ;
extern float cosf  (float)  ;
extern float sinf  (float)  ;
extern float tanf  (float)  ;
extern float tanhf  (float)  ;
extern float frexpf  (float, int *)  ;
extern float modff  (float, float *)  ;
extern float ceilf  (float)  ;
extern float fabsf  (float)  ;
extern float floorf  (float)  ;


extern float acosf  (float)  ;
extern float asinf  (float)  ;
extern float atan2f  (float, float)  ;
extern float coshf  (float)  ;
extern float sinhf  (float)  ;
extern float expf  (float)  ;
extern float ldexpf  (float, int)  ;
extern float logf  (float)  ;
extern float log10f  (float)  ;
extern float powf  (float, float)  ;
extern float sqrtf  (float)  ;
extern float fmodf  (float, float)  ;


 

extern float infinityf  (void)  ;
extern float nanf  (void)  ;
extern int isnanf  (float)  ;
extern int isinff  (float)  ;
extern int finitef  (float)  ;
extern float copysignf  (float, float)  ;
extern int ilogbf  (float)  ;

extern float asinhf  (float)  ;
extern float cbrtf  (float)  ;
extern float nextafterf  (float, float)  ;
extern float rintf  (float)  ;
extern float scalbnf  (float, int)  ;
extern float log1pf  (float)  ;
extern float expm1f  (float)  ;


extern float acoshf  (float)  ;
extern float atanhf  (float)  ;
extern float remainderf  (float, float)  ;
extern float gammaf  (float)  ;
extern float gammaf_r  (float, int *)  ;
extern float lgammaf  (float)  ;
extern float lgammaf_r  (float, int *)  ;
extern float erff  (float)  ;
extern float erfcf  (float)  ;
extern float y0f  (float)  ;
extern float y1f  (float)  ;
extern float ynf  (int, float)  ;
extern float j0f  (float)  ;
extern float j1f  (float)  ;
extern float jnf  (int, float)  ;

extern float hypotf  (float, float)  ;

extern float cabsf();
extern float dremf  (float, float)  ;



 

extern int signgam;




struct exception;






 










struct exception 




{
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};

# 233 "/home/potatooo/fcc/lib/gcc-lib/mips-ecoff/2.8.1/include/math.h" 3







extern int matherr  (struct exception *e)  ;











 











 
























 

enum __fdlibm_version
{
  __fdlibm_ieee = -1,
  __fdlibm_svid,
  __fdlibm_xopen,
  __fdlibm_posix
};




extern enum __fdlibm_version  __fdlib_version ;












# 15 "fdlibm.h" 2

# 1 "/home/potatooo/fcc/mips-ecoff/include/machine/ieeefp.h" 1 3


































# 44 "/home/potatooo/fcc/mips-ecoff/include/machine/ieeefp.h" 3


























 







































# 118 "/home/potatooo/fcc/mips-ecoff/include/machine/ieeefp.h" 3



















# 16 "fdlibm.h" 2


 










 






 

extern double logb  (double)  ;



extern double scalb  (double, double)  ;

extern double significand  (double)  ;

 
extern double __ieee754_sqrt  (double)  ;			
extern double __ieee754_acos  (double)  ;			
extern double __ieee754_acosh  (double)  ;			
extern double __ieee754_log  (double)  ;			
extern double __ieee754_atanh  (double)  ;			
extern double __ieee754_asin  (double)  ;			
extern double __ieee754_atan2  (double,double)  ;			
extern double __ieee754_exp  (double)  ;
extern double __ieee754_cosh  (double)  ;
extern double __ieee754_fmod  (double,double)  ;
extern double __ieee754_pow  (double,double)  ;
extern double __ieee754_lgamma_r  (double,int *)  ;
extern double __ieee754_gamma_r  (double,int *)  ;
extern double __ieee754_log10  (double)  ;
extern double __ieee754_sinh  (double)  ;
extern double __ieee754_hypot  (double,double)  ;
extern double __ieee754_j0  (double)  ;
extern double __ieee754_j1  (double)  ;
extern double __ieee754_y0  (double)  ;
extern double __ieee754_y1  (double)  ;
extern double __ieee754_jn  (int,double)  ;
extern double __ieee754_yn  (int,double)  ;
extern double __ieee754_remainder  (double,double)  ;
extern __int32_t __ieee754_rem_pio2  (double,double*)  ;



extern double __ieee754_scalb  (double,double)  ;


 
extern double __kernel_standard  (double,double,int)  ;
extern double __kernel_sin  (double,double,int)  ;
extern double __kernel_cos  (double,double)  ;
extern double __kernel_tan  (double,double,int)  ;
extern int    __kernel_rem_pio2  (double*,double*,int,int,int,const __int32_t*)  ;

 
extern float logbf  (float)  ;



extern float scalbf  (float, float)  ;

extern float significandf  (float)  ;

 
extern float __ieee754_sqrtf  (float)  ;			
extern float __ieee754_acosf  (float)  ;			
extern float __ieee754_acoshf  (float)  ;			
extern float __ieee754_logf  (float)  ;			
extern float __ieee754_atanhf  (float)  ;			
extern float __ieee754_asinf  (float)  ;			
extern float __ieee754_atan2f  (float,float)  ;			
extern float __ieee754_expf  (float)  ;
extern float __ieee754_coshf  (float)  ;
extern float __ieee754_fmodf  (float,float)  ;
extern float __ieee754_powf  (float,float)  ;
extern float __ieee754_lgammaf_r  (float,int *)  ;
extern float __ieee754_gammaf_r  (float,int *)  ;
extern float __ieee754_log10f  (float)  ;
extern float __ieee754_sinhf  (float)  ;
extern float __ieee754_hypotf  (float,float)  ;
extern float __ieee754_j0f  (float)  ;
extern float __ieee754_j1f  (float)  ;
extern float __ieee754_y0f  (float)  ;
extern float __ieee754_y1f  (float)  ;
extern float __ieee754_jnf  (int,float)  ;
extern float __ieee754_ynf  (int,float)  ;
extern float __ieee754_remainderf  (float,float)  ;
extern __int32_t __ieee754_rem_pio2f  (float,float*)  ;



extern float __ieee754_scalbf  (float,float)  ;


 
extern float __kernel_sinf  (float,float,int)  ;
extern float __kernel_cosf  (float,float)  ;
extern float __kernel_tanf  (float,float,int)  ;
extern int   __kernel_rem_pio2f  (float*,float*,int,int,int,const __int32_t*)  ;

 



#ifdef __IEEE_BIG_ENDIAN

typedef union
{
  double value;
  struct
  {
    __uint32_t msw;
    __uint32_t lsw;
  } parts;
} ieee_double_shape_type;

#endif

#ifdef __IEEE_LITTLE_ENDIAN

typedef union
{
  double value;
  struct
  {
    __uint32_t lsw;
    __uint32_t msw;
  } parts;
} ieee_double_shape_type;

#endif

/* Get two 32 bit ints from a double.  */

#define EXTRACT_WORDS(ix0,ix1,d)                                \
do {                                                            \
  ieee_double_shape_type ew_u;                                  \
  ew_u.value = (d);                                             \
  (ix0) = ew_u.parts.msw;                                       \
  (ix1) = ew_u.parts.lsw;                                       \
} while (0)

/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)                                      \
do {                                                            \
  ieee_double_shape_type gh_u;                                  \
  gh_u.value = (d);                                             \
  (i) = gh_u.parts.msw;                                         \
} while (0)


/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)                                       \
do {                                                            \
  ieee_double_shape_type gl_u;                                  \
  gl_u.value = (d);                                             \
  (i) = gl_u.parts.lsw;                                         \
} while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)                                 \
do {                                                            \
  ieee_double_shape_type iw_u;                                  \
  iw_u.parts.msw = (ix0);                                       \
  iw_u.parts.lsw = (ix1);                                       \
  (d) = iw_u.value;                                             \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d,v)                                      \
do {                                                            \
  ieee_double_shape_type sh_u;                                  \
  sh_u.value = (d);                                             \
  sh_u.parts.msw = (v);                                         \
  (d) = sh_u.value;                                             \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d,v)                                       \
do {                                                            \
  ieee_double_shape_type sl_u;                                  \
  sl_u.value = (d);                                             \
  sl_u.parts.lsw = (v);                                         \
  (d) = sl_u.value;                                             \
} while (0)
 


typedef union
{
  float value;
  __uint32_t word;
} ieee_float_shape_type;

 
#define GET_FLOAT_WORD(i,d)                                     \
do {                                                            \
  ieee_float_shape_type gf_u;                                   \
  gf_u.value = (d);                                             \
  (i) = gf_u.word;                                              \
} while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d,i)                                     \
do {                                                            \
  ieee_float_shape_type sf_u;                                   \
  sf_u.word = (i);                                              \
  (d) = sf_u.value;                                             \
} while (0)




