#ifndef	__BUFLOC_H
#define	__BUFLOC_H


#ifdef  FS_MEMBUF_HERE
#define EXTERN_FS
#else
#define EXTERN_FS     extern
#endif

#ifdef GLOBAL_HERE
#define EXTERN
#define INIT(x) =x
#else
#define EXTERN          extern
#define INIT(x)
#endif

#ifdef  MEMBUF_HERE
#define EXTERN_MEM
#else
#define EXTERN_MEM      extern
#endif

#ifdef  DATABUF_HERE
#define EXTERN_DATABUF
#else
#define EXTERN_DATABUF      extern
#endif

#endif/*__BUFLOC_H*/

