#ifndef	__DMABUF_H
#define	__DMABUF_H

typedef union { 
    UINT64      l[32];
    UINT32      w[64];
    UINT16      s[128];
    BYTE        b[256];
} WorkBuf;


typedef union { 
  UINT64        l[4];
  UINT32        w[8];
  UINT16        s[16];
  UINT8         b[32];
} t_vidout_buf;

#endif/*__DMABUF_H*/

