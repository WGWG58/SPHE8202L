#ifndef	__STDLIB_SVCD_H
#define	__STDLIB_SVCD_H


typedef struct {
        int     quot;
        int     rem;
} div_t;

typedef struct {
        unsigned	int     quot;
        unsigned	int     rem;
} udiv_t;
 
typedef struct {
        long    quot;
        long    rem;
} ldiv_t;
 
typedef struct {
        long long       quot;
        long long       rem;
} lldiv_t;

extern	div_t	__div(int, int);
extern	udiv_t	__udiv(unsigned int, unsigned int);
extern	ldiv_t	__ldiv(long, long);


#ifdef	USE_INLINE
#define	div(numer, denom) ({						\
  div_t retval;								\
  asm ("move $4,%2; move $5,%3; jal __Xdivsi3; move %0,$4; move %1,$5"	\
    : "=r"(retval.quot), "=r"(retval.rem)				\
    : "r"(numer), "r"(denom) : "$4","$5","$8","$9","$31");		\
  retval;								\
})
#else
#define	div(numer, denom)	__div(numer, denom)
#define	udiv(numer, denom)	__udiv(numer, denom)
#define	ldiv(numer, denom)	__ldiv(numer, denom)
#endif

/*//Jack mark for warning msg
#ifndef	_SIZE_T_
typedef	unsigned	size_t;
#define	_SIZE_T_
#endif
*/

//extern	unsigned int	rand();
unsigned int	srand(unsigned int);

unsigned strlen(const char *);
char *	strcpy(char *, const char *);
char *	strcat(char *, const char *);
char *	strcat1(char *, const char *);
char *	strncpy(char *, const char *, unsigned/*size_t*/);
int	strcmp(const char *, const char *);
int	strcmpi(const char *, const char *);
int	strcmpi(const char *, const char *);
int	strncmp(const char *, const char *,  unsigned);
int	strncmpi(const char *, const char *, unsigned);

void *memcpy(void *, const void *, unsigned);
void *memcpyS(void *, const void *, int);
void *memset(void *, int, unsigned);
int	memcmp(const void *, const void *, unsigned/*size_t*/);

extern	int	__farcall(int (*func)(), void *);

#endif/*__STDLIB_SVCD_H*/


