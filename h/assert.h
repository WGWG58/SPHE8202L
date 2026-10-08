#define DEBUG
#ifdef DEBUG
#define ASSERT(f,s){   \
      if(f)         \
         ;        \
      else           \
         {printf("ASSERT ");printf(s);printf("error\n");}}  
#else
#define ASSERT(f,s) 
#endif
